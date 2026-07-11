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
U64 Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(U64 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U64 Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U64 OutOfBounds_size(void);
Array__Str * Array__Str_new(U64 cap);
U64 Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, U64 * i);
void Array__Str_unsafe_set(Array__Str * self, U64 i, Str * val);
void Array__Str_set(Array__Str * self, U64 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
U64 Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
U64 Vec__Str_size(void);
U64 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
U64 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
U64 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
U64 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U64 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U64 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U64 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U64 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U64 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U64 Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U64 Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
U64 FuncType_size(void);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
U64 OwnType_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
U64 Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
U64 FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
U64 FCallData_size(void);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
U64 LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
U64 IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
U64 FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
U64 StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
U64 EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
U64 AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
U64 FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
U64 ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
U64 Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
U64 MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
U64 CaptureBlockData_size(void);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
U64 NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
U64 Expr_size(void);
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
U64 Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
U64 Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U64 Vec__I64_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
U64 Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
U64 Vec__Expr_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
void swap_bytes(void * a, void * b, U64 size);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
U64 Range_size(void);
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
U64 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
U64 CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
U64 CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
U64 Color_size(void);
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
U64 Token_size(void);
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
U64 Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(U64 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U64 Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U64 OutOfBounds_size(void);
Array__Str * Array__Str_new(U64 cap);
U64 Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, U64 * i);
void Array__Str_unsafe_set(Array__Str * self, U64 i, Str * val);
void Array__Str_set(Array__Str * self, U64 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
U64 Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
U64 Vec__Str_size(void);
U64 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
U64 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
U64 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
U64 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U64 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U64 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U64 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U64 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U64 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U64 Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U64 Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
U64 FuncType_size(void);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
U64 OwnType_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
U64 Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
U64 FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
U64 FCallData_size(void);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
U64 LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
U64 IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
U64 FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
U64 StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
U64 EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
U64 AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
U64 FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
U64 ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
U64 Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
U64 MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
U64 CaptureBlockData_size(void);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
U64 NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
U64 Expr_size(void);
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
U64 Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
U64 Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U64 Vec__I64_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
U64 Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
U64 Vec__Expr_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
void swap_bytes(void * a, void * b, U64 size);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
U64 Range_size(void);
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
U64 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
U64 CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
U64 CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
U64 Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
U64 Token_size(void);
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
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"ListPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_214 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_215 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_216 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_217 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

U64 CAP_LIT;
U64 CAP_VIEW;
U64 ELEM_POD;
U64 ELEM_BOXED;
U64 ELEM_FN;
Str __til_docs_blob__;
Str __til_info_blob__;

Str * format(Array__Str * parts) {
    U64 total = 0ULL;
    {
        Array__Str *_fc_Array__Str_99 = parts;
        (void)_fc_Array__Str_99;
        (void)_fc_Array__Str_99;
        U64 _fi_USize_99 = 0ULL;
        (void)_fi_USize_99;
        while (1) {
            U64 hoisted__U64_101 = (_fc_Array__Str_99->cap);
            (void)hoisted__U64_101;
            Bool _wcond_Bool_100 = ((Bool)(_fi_USize_99 < hoisted__U64_101));
            (void)_wcond_Bool_100;
            if (_wcond_Bool_100) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_99->data) + (((U64)(_fi_USize_99 * 24ULL))))));
            U64 hoisted__U64_102 = 1ULL;
            (void)hoisted__U64_102;
            U64 hoisted__U64_103 = ((U64)(_fi_USize_99 + hoisted__U64_102));
            (void)hoisted__U64_103;
            _fi_USize_99 = hoisted__U64_103;
            U64 hoisted__U64_104 = (s->count);
            (void)hoisted__U64_104;
            U64 hoisted__U64_105 = ((U64)(total + hoisted__U64_104));
            (void)hoisted__U64_105;
            total = hoisted__U64_105;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_106 = parts;
        (void)_fc_Array__Str_106;
        (void)_fc_Array__Str_106;
        U64 _fi_USize_106 = 0ULL;
        (void)_fi_USize_106;
        while (1) {
            U64 hoisted__U64_108 = (_fc_Array__Str_106->cap);
            (void)hoisted__U64_108;
            Bool _wcond_Bool_107 = ((Bool)(_fi_USize_106 < hoisted__U64_108));
            (void)_wcond_Bool_107;
            if (_wcond_Bool_107) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_106->data) + (((U64)(_fi_USize_106 * 24ULL))))));
            U64 hoisted__U64_109 = 1ULL;
            (void)hoisted__U64_109;
            U64 hoisted__U64_110 = ((U64)(_fi_USize_106 + hoisted__U64_109));
            (void)hoisted__U64_110;
            _fi_USize_106 = hoisted__U64_110;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

U64 Str_len(Str * self) {
    return self->count;
    __builtin_unreachable();
}

I64 Str_cmp(Str * a, Str * b) {
    U64 min_len = a->count;
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
        { I64 _ret_val = hoisted__I64_124;
                                return _ret_val; }
    }
    I32 hoisted__I32_129 = 0;
    (void)hoisted__I32_129;
    Bool hoisted__Bool_130 = ((Bool)(c > hoisted__I32_129));
    (void)hoisted__Bool_130;
    if (hoisted__Bool_130) {
        I64 hoisted__I64_125 = 1;
        (void)hoisted__I64_125;
        { I64 _ret_val = hoisted__I64_125;
                                return _ret_val; }
    }
    I64 hoisted__I64_131 = U64_cmp(a->count, b->count);
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
        { Bool _ret_val = hoisted__Bool_132;
                return _ret_val; }
    }
    Bool hoisted__Bool_135 = ptr_eq(a->c_str, b->c_str);
    (void)hoisted__Bool_135;
    if (hoisted__Bool_135) {
        Bool hoisted__Bool_133 = 1;
        (void)hoisted__Bool_133;
        { Bool _ret_val = hoisted__Bool_133;
                return _ret_val; }
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

Str * Str_with_capacity(U64 n) {
    U64 hoisted__U64_140 = 0ULL;
    (void)hoisted__U64_140;
    Bool hoisted__Bool_141 = ((Bool)(n == hoisted__U64_140));
    (void)hoisted__Bool_141;
    if (hoisted__Bool_141) {
        static Str hoisted__Str_139 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_139;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_139; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U64 hoisted__U64_142 = 1ULL;
    (void)hoisted__U64_142;
    U64 hoisted__U64_143 = ((U64)(n + hoisted__U64_142));
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
    U64 hoisted__U64_160 = 0ULL;
    (void)hoisted__U64_160;
    Bool hoisted__Bool_161 = ((Bool)(s->count == hoisted__U64_160));
    (void)hoisted__Bool_161;
    if (hoisted__Bool_161) {
        return;
    }
    Bool hoisted__Bool_162 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_162;
    if (hoisted__Bool_162) {
        U64 hoisted__U64_150 = 1ULL;
        (void)hoisted__U64_150;
        Array__Str *_va_Array_3 = Array__Str_new(hoisted__U64_150);
        (void)_va_Array_3;
        I64 _va_Array_3_ek = 0;
        (void)_va_Array_3_ek;
        OutOfBounds *_va_Array_3_eo = malloc(sizeof(OutOfBounds));
        _va_Array_3_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_3_eo;
        U64 hoisted__U64_151 = 0ULL;
        (void)hoisted__U64_151;
        static Str hoisted__Str_152 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_152;
        static Str hoisted__Str_153 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_153;
        Array__Str_set(_va_Array_3, hoisted__U64_151, &hoisted__Str_152, &_va_Array_3_ek, _va_Array_3_eo, &hoisted__Str_153);
        OutOfBounds_delete(_va_Array_3_eo, 1);
        Str_delete(&hoisted__Str_153, (Bool){0});
        static Str hoisted__Str_154 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_154;
        panic(_va_Array_3, &hoisted__Str_154);
        Str_delete(&hoisted__Str_154, (Bool){0});
    }
    U64 new_len = ((U64)(self->count + s->count));
    Bool hoisted__Bool_163 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_163;
    if (hoisted__Bool_163) {
        U64 hoisted__U64_155 = 1ULL;
        (void)hoisted__U64_155;
        Array__Str *_va_Array_4 = Array__Str_new(hoisted__U64_155);
        (void)_va_Array_4;
        I64 _va_Array_4_ek = 0;
        (void)_va_Array_4_ek;
        OutOfBounds *_va_Array_4_eo = malloc(sizeof(OutOfBounds));
        _va_Array_4_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_4_eo;
        U64 hoisted__U64_156 = 0ULL;
        (void)hoisted__U64_156;
        static Str hoisted__Str_157 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_157;
        static Str hoisted__Str_158 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_158;
        Array__Str_set(_va_Array_4, hoisted__U64_156, &hoisted__Str_157, &_va_Array_4_ek, _va_Array_4_eo, &hoisted__Str_158);
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
    U64 hoisted__U64_169 = 0ULL;
    (void)hoisted__U64_169;
    Bool hoisted__Bool_170 = ((Bool)(val->count == hoisted__U64_169));
    (void)hoisted__Bool_170;
    if (hoisted__Bool_170) {
        static Str hoisted__Str_168 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_168;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_168; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U64 hoisted__U64_171 = 1ULL;
    (void)hoisted__U64_171;
    U64 hoisted__U64_172 = ((U64)(val->count + hoisted__U64_171));
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
    U64 hoisted__U64_375 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U64))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_375;
    return hoisted__U64_375;
    __builtin_unreachable();
}

U64 Str_size(void) {
    U64 hoisted__U64_558 = 24ULL;
    (void)hoisted__U64_558;
    return hoisted__U64_558;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_567 = Str_eq(a, b);
    (void)hoisted__Bool_567;
    Bool hoisted__Bool_568 = ((Bool)(!(hoisted__Bool_567)));
    (void)hoisted__Bool_568;
    return hoisted__Bool_568;
    __builtin_unreachable();
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_659 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_659->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_659;
    return hoisted__OutOfBounds_659;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_660 = 0;
    (void)hoisted__Bool_660;
    Str_delete(&self->msg, hoisted__Bool_660);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U64 hoisted__U64_661 = 0ULL;
    (void)hoisted__U64_661;
    U64 hoisted__U64_662 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_661); });
    (void)hoisted__U64_662;
    return hoisted__U64_662;
    __builtin_unreachable();
}

U64 OutOfBounds_size(void) {
    U64 hoisted__U64_681 = 24ULL;
    (void)hoisted__U64_681;
    return hoisted__U64_681;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(U64 cap) {
    U64 hoisted__U64_705 = 24ULL;
    (void)hoisted__U64_705;
    void * hoisted__v_706 = calloc(cap, hoisted__U64_705);
    (void)hoisted__v_706;
    Array__Str *hoisted__Array__Str_707 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_707->data = hoisted__v_706;
    hoisted__Array__Str_707->cap = cap;
    (void)hoisted__Array__Str_707;
    return hoisted__Array__Str_707;
    __builtin_unreachable();
}

U64 Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, U64 * i) {
    U64 hoisted__U64_708 = 24ULL;
    (void)hoisted__U64_708;
    U64 hoisted__U64_709 = ((U64)(DEREF(i) * hoisted__U64_708));
    (void)hoisted__U64_709;
    void *hoisted__v_710 = ((void *)((U8 *)(self->data) + (hoisted__U64_709)));
    (void)hoisted__v_710;
    (void)hoisted__v_710;
    return hoisted__v_710;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, U64 i, Str * val) {
    Str *hoisted__Str_737 = (((void *)((U8 *)(self->data) + (((U64)(i * 24ULL))))));
    (void)hoisted__Str_737;
    (void)hoisted__Str_737;
    Bool hoisted__Bool_738 = 0;
    (void)hoisted__Bool_738;
    Str_delete(hoisted__Str_737, hoisted__Bool_738);
    Str *hoisted__Str_739 = (((void *)((U8 *)(self->data) + (((U64)(i * 24ULL))))));
    (void)hoisted__Str_739;
    (void)hoisted__Str_739;
    U64 hoisted__U64_740 = 24ULL;
    (void)hoisted__U64_740;
    memcpy(hoisted__Str_739, val, hoisted__U64_740);
    I32 hoisted__I32_741 = 0;
    (void)hoisted__I32_741;
    U64 hoisted__U64_742 = 24ULL;
    (void)hoisted__U64_742;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_741, hoisted__U64_742); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U64 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_765 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_765;
    if (hoisted__Bool_765) {
        U64 hoisted__U64_743 = 6ULL;
        (void)hoisted__U64_743;
        Array__Str *_va_Array_16 = Array__Str_new(hoisted__U64_743);
        (void)_va_Array_16;
        I64 _va_Array_16_ek = 0;
        (void)_va_Array_16_ek;
        OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
        _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_16_eo;
        U64 hoisted__U64_744 = 0ULL;
        (void)hoisted__U64_744;
        Str *hoisted__Str_745 = Str_clone(loc);
        (void)hoisted__Str_745;
        static Str hoisted__Str_746 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_746;
        Array__Str_set(_va_Array_16, hoisted__U64_744, hoisted__Str_745, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_746);
        Str_delete(&hoisted__Str_746, (Bool){0});
        U64 hoisted__U64_747 = 1ULL;
        (void)hoisted__U64_747;
        static Str hoisted__Str_748 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_748;
        static Str hoisted__Str_749 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_749;
        Array__Str_set(_va_Array_16, hoisted__U64_747, &hoisted__Str_748, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_749);
        Str_delete(&hoisted__Str_749, (Bool){0});
        U64 hoisted__U64_750 = 2ULL;
        (void)hoisted__U64_750;
        Str *hoisted__Str_751 = U64_to_str(i);
        (void)hoisted__Str_751;
        static Str hoisted__Str_752 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_752;
        Array__Str_set(_va_Array_16, hoisted__U64_750, hoisted__Str_751, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_752);
        Str_delete(&hoisted__Str_752, (Bool){0});
        U64 hoisted__U64_753 = 3ULL;
        (void)hoisted__U64_753;
        static Str hoisted__Str_754 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_754;
        static Str hoisted__Str_755 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_755;
        Array__Str_set(_va_Array_16, hoisted__U64_753, &hoisted__Str_754, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_755);
        Str_delete(&hoisted__Str_755, (Bool){0});
        U64 hoisted__U64_756 = 4ULL;
        (void)hoisted__U64_756;
        Str *hoisted__Str_757 = U64_to_str(self->cap);
        (void)hoisted__Str_757;
        static Str hoisted__Str_758 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_758;
        Array__Str_set(_va_Array_16, hoisted__U64_756, hoisted__Str_757, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_758);
        Str_delete(&hoisted__Str_758, (Bool){0});
        U64 hoisted__U64_759 = 5ULL;
        (void)hoisted__U64_759;
        static Str hoisted__Str_760 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_760;
        static Str hoisted__Str_761 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_761;
        Array__Str_set(_va_Array_16, hoisted__U64_759, &hoisted__Str_760, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_761);
        OutOfBounds_delete(_va_Array_16_eo, 1);
        Str_delete(&hoisted__Str_761, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_762 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_16); hoisted__OutOfBounds_762->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_762;
        U64 hoisted__U64_763 = 24ULL;
        (void)hoisted__U64_763;
        swap_bytes(_err_OutOfBounds, hoisted__OutOfBounds_762, hoisted__U64_763);
        OutOfBounds_delete(hoisted__OutOfBounds_762, 1);
        I64 hoisted__I64_764 = 1;
        (void)hoisted__I64_764;
        *_err_kind = hoisted__I64_764;
    }
    I64 hoisted__I64_766 = 0;
    (void)hoisted__I64_766;
    Bool hoisted__Bool_767 = ((Bool)(DEREF(_err_kind) == hoisted__I64_766));
    (void)hoisted__Bool_767;
    if (hoisted__Bool_767) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U64 _re_U64_768 = self->cap;
        (void)_re_U64_768;
        U64 _rc_U64_768 = 0ULL;
        (void)_rc_U64_768;
        Bool hoisted__Bool_779 = ((Bool)(_rc_U64_768 <= _re_U64_768));
        (void)hoisted__Bool_779;
        if (hoisted__Bool_779) {
            while (1) {
                Bool _wcond_Bool_769 = ((Bool)(_rc_U64_768 < _re_U64_768));
                (void)_wcond_Bool_769;
                if (_wcond_Bool_769) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_768);
                (++_rc_U64_768);
                U64 hoisted__U64_770 = 24ULL;
                (void)hoisted__U64_770;
                U64 hoisted__U64_771 = ((U64)(i * hoisted__U64_770));
                (void)hoisted__U64_771;
                Str *hoisted__Str_772 = ((void *)((U8 *)(self->data) + (hoisted__U64_771)));
                (void)hoisted__Str_772;
                (void)hoisted__Str_772;
                Bool hoisted__Bool_773 = 0;
                (void)hoisted__Bool_773;
                Str_delete(hoisted__Str_772, hoisted__Bool_773);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_774 = ((Bool)(_rc_U64_768 > _re_U64_768));
                (void)_wcond_Bool_774;
                if (_wcond_Bool_774) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_768);
                (--_rc_U64_768);
                U64 hoisted__U64_775 = 24ULL;
                (void)hoisted__U64_775;
                U64 hoisted__U64_776 = ((U64)(i * hoisted__U64_775));
                (void)hoisted__U64_776;
                Str *hoisted__Str_777 = ((void *)((U8 *)(self->data) + (hoisted__U64_776)));
                (void)hoisted__Str_777;
                (void)hoisted__Str_777;
                Bool hoisted__Bool_778 = 0;
                (void)hoisted__Bool_778;
                Str_delete(hoisted__Str_777, hoisted__Bool_778);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U64 hoisted__U64_800 = 24ULL;
    (void)hoisted__U64_800;
    U64 hoisted__U64_801 = ((U64)(self->cap * hoisted__U64_800));
    (void)hoisted__U64_801;
    U8 *new_data = malloc(hoisted__U64_801);
    {
        U64 _re_U64_780 = self->cap;
        (void)_re_U64_780;
        U64 _rc_U64_780 = 0ULL;
        (void)_rc_U64_780;
        Bool hoisted__Bool_799 = ((Bool)(_rc_U64_780 <= _re_U64_780));
        (void)hoisted__Bool_799;
        if (hoisted__Bool_799) {
            while (1) {
                Bool _wcond_Bool_781 = ((Bool)(_rc_U64_780 < _re_U64_780));
                (void)_wcond_Bool_781;
                if (_wcond_Bool_781) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_780);
                (++_rc_U64_780);
                U64 hoisted__U64_782 = 24ULL;
                (void)hoisted__U64_782;
                U64 hoisted__U64_783 = ((U64)(i * hoisted__U64_782));
                (void)hoisted__U64_783;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_783)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_784 = 24ULL;
                (void)hoisted__U64_784;
                U64 hoisted__U64_785 = ((U64)(i * hoisted__U64_784));
                (void)hoisted__U64_785;
                void *hoisted__v_786 = ((void *)((U8 *)(new_data) + (hoisted__U64_785)));
                (void)hoisted__v_786;
                (void)hoisted__v_786;
                U64 hoisted__U64_787 = 24ULL;
                (void)hoisted__U64_787;
                memcpy(hoisted__v_786, cloned, hoisted__U64_787);
                I32 hoisted__I32_788 = 0;
                (void)hoisted__I32_788;
                U64 hoisted__U64_789 = 24ULL;
                (void)hoisted__U64_789;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_788, hoisted__U64_789); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_790 = ((Bool)(_rc_U64_780 > _re_U64_780));
                (void)_wcond_Bool_790;
                if (_wcond_Bool_790) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_780);
                (--_rc_U64_780);
                U64 hoisted__U64_791 = 24ULL;
                (void)hoisted__U64_791;
                U64 hoisted__U64_792 = ((U64)(i * hoisted__U64_791));
                (void)hoisted__U64_792;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_792)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_793 = 24ULL;
                (void)hoisted__U64_793;
                U64 hoisted__U64_794 = ((U64)(i * hoisted__U64_793));
                (void)hoisted__U64_794;
                void *hoisted__v_795 = ((void *)((U8 *)(new_data) + (hoisted__U64_794)));
                (void)hoisted__v_795;
                (void)hoisted__v_795;
                U64 hoisted__U64_796 = 24ULL;
                (void)hoisted__U64_796;
                memcpy(hoisted__v_795, cloned, hoisted__U64_796);
                I32 hoisted__I32_797 = 0;
                (void)hoisted__I32_797;
                U64 hoisted__U64_798 = 24ULL;
                (void)hoisted__U64_798;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_797, hoisted__U64_798); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_802 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_802->data = new_data;
    hoisted__Array__Str_802->cap = self->cap;
    (void)hoisted__Array__Str_802;
    return hoisted__Array__Str_802;
    __builtin_unreachable();
}

U64 Array__Str_size(void) {
    U64 hoisted__U64_803 = 16ULL;
    (void)hoisted__U64_803;
    return hoisted__U64_803;
    __builtin_unreachable();
}

Vec__Str * Vec__Str_new(void) {
    U64 hoisted__U64_804 = 24ULL;
    (void)hoisted__U64_804;
    void * hoisted__v_805 = malloc(hoisted__U64_804);
    (void)hoisted__v_805;
    U64 hoisted__U64_806 = 0ULL;
    (void)hoisted__U64_806;
    I64 hoisted__I64_807 = 1;
    (void)hoisted__I64_807;
    Vec__Str *hoisted__Vec__Str_808 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_808->data = hoisted__v_805;
    hoisted__Vec__Str_808->count = hoisted__U64_806;
    hoisted__Vec__Str_808->cap = hoisted__I64_807;
    (void)hoisted__Vec__Str_808;
    return hoisted__Vec__Str_808;
    __builtin_unreachable();
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U64 _re_U64_817 = self->count;
        (void)_re_U64_817;
        U64 _rc_U64_817 = 0ULL;
        (void)_rc_U64_817;
        Bool hoisted__Bool_828 = ((Bool)(_rc_U64_817 <= _re_U64_817));
        (void)hoisted__Bool_828;
        if (hoisted__Bool_828) {
            while (1) {
                Bool _wcond_Bool_818 = ((Bool)(_rc_U64_817 < _re_U64_817));
                (void)_wcond_Bool_818;
                if (_wcond_Bool_818) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_817);
                (++_rc_U64_817);
                U64 hoisted__U64_819 = 24ULL;
                (void)hoisted__U64_819;
                U64 hoisted__U64_820 = ((U64)(i * hoisted__U64_819));
                (void)hoisted__U64_820;
                Str *hoisted__Str_821 = ((void *)((U8 *)(self->data) + (hoisted__U64_820)));
                (void)hoisted__Str_821;
                (void)hoisted__Str_821;
                Bool hoisted__Bool_822 = 0;
                (void)hoisted__Bool_822;
                Str_delete(hoisted__Str_821, hoisted__Bool_822);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_823 = ((Bool)(_rc_U64_817 > _re_U64_817));
                (void)_wcond_Bool_823;
                if (_wcond_Bool_823) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_817);
                (--_rc_U64_817);
                U64 hoisted__U64_824 = 24ULL;
                (void)hoisted__U64_824;
                U64 hoisted__U64_825 = ((U64)(i * hoisted__U64_824));
                (void)hoisted__U64_825;
                Str *hoisted__Str_826 = ((void *)((U8 *)(self->data) + (hoisted__U64_825)));
                (void)hoisted__Str_826;
                (void)hoisted__Str_826;
                Bool hoisted__Bool_827 = 0;
                (void)hoisted__Bool_827;
                Str_delete(hoisted__Str_826, hoisted__Bool_827);
            }
        }
    }
    U64 hoisted__U64_829 = 0ULL;
    (void)hoisted__U64_829;
    self->count = hoisted__U64_829;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U64 hoisted__U64_1060 = 24ULL;
    (void)hoisted__U64_1060;
    U64 hoisted__U64_1061 = ((U64)(self->cap * hoisted__U64_1060));
    (void)hoisted__U64_1061;
    U8 *new_data = malloc(hoisted__U64_1061);
    {
        U64 _re_U64_1040 = self->count;
        (void)_re_U64_1040;
        U64 _rc_U64_1040 = 0ULL;
        (void)_rc_U64_1040;
        Bool hoisted__Bool_1059 = ((Bool)(_rc_U64_1040 <= _re_U64_1040));
        (void)hoisted__Bool_1059;
        if (hoisted__Bool_1059) {
            while (1) {
                Bool _wcond_Bool_1041 = ((Bool)(_rc_U64_1040 < _re_U64_1040));
                (void)_wcond_Bool_1041;
                if (_wcond_Bool_1041) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_1040);
                (++_rc_U64_1040);
                U64 hoisted__U64_1042 = 24ULL;
                (void)hoisted__U64_1042;
                U64 hoisted__U64_1043 = ((U64)(i * hoisted__U64_1042));
                (void)hoisted__U64_1043;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_1043)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_1044 = 24ULL;
                (void)hoisted__U64_1044;
                U64 hoisted__U64_1045 = ((U64)(i * hoisted__U64_1044));
                (void)hoisted__U64_1045;
                void *hoisted__v_1046 = ((void *)((U8 *)(new_data) + (hoisted__U64_1045)));
                (void)hoisted__v_1046;
                (void)hoisted__v_1046;
                U64 hoisted__U64_1047 = 24ULL;
                (void)hoisted__U64_1047;
                memcpy(hoisted__v_1046, cloned, hoisted__U64_1047);
                I32 hoisted__I32_1048 = 0;
                (void)hoisted__I32_1048;
                U64 hoisted__U64_1049 = 24ULL;
                (void)hoisted__U64_1049;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1048, hoisted__U64_1049); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1050 = ((Bool)(_rc_U64_1040 > _re_U64_1040));
                (void)_wcond_Bool_1050;
                if (_wcond_Bool_1050) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_1040);
                (--_rc_U64_1040);
                U64 hoisted__U64_1051 = 24ULL;
                (void)hoisted__U64_1051;
                U64 hoisted__U64_1052 = ((U64)(i * hoisted__U64_1051));
                (void)hoisted__U64_1052;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_1052)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_1053 = 24ULL;
                (void)hoisted__U64_1053;
                U64 hoisted__U64_1054 = ((U64)(i * hoisted__U64_1053));
                (void)hoisted__U64_1054;
                void *hoisted__v_1055 = ((void *)((U8 *)(new_data) + (hoisted__U64_1054)));
                (void)hoisted__v_1055;
                (void)hoisted__v_1055;
                U64 hoisted__U64_1056 = 24ULL;
                (void)hoisted__U64_1056;
                memcpy(hoisted__v_1055, cloned, hoisted__U64_1056);
                I32 hoisted__I32_1057 = 0;
                (void)hoisted__I32_1057;
                U64 hoisted__U64_1058 = 24ULL;
                (void)hoisted__U64_1058;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1057, hoisted__U64_1058); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1062 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1062->data = new_data;
    hoisted__Vec__Str_1062->count = self->count;
    hoisted__Vec__Str_1062->cap = self->cap;
    (void)hoisted__Vec__Str_1062;
    return hoisted__Vec__Str_1062;
    __builtin_unreachable();
}

U64 Vec__Str_size(void) {
    U64 hoisted__U64_1063 = 24ULL;
    (void)hoisted__U64_1063;
    return hoisted__U64_1063;
    __builtin_unreachable();
}

U64 Dynamic_size(void) {
    U64 hoisted__U64_1066 = 8ULL;
    (void)hoisted__U64_1066;
    return hoisted__U64_1066;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U64 hoisted__U64_1067 = 8ULL;
    (void)hoisted__U64_1067;
    void * out = malloc(hoisted__U64_1067);
    U64 hoisted__U64_1068 = 8ULL;
    (void)hoisted__U64_1068;
    memcpy(out, self, hoisted__U64_1068);
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

U64 U8_size(void) {
    U64 hoisted__U64_1080 = 1ULL;
    (void)hoisted__U64_1080;
    return hoisted__U64_1080;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U64 hoisted__U64_1165 = 0ULL;
    (void)hoisted__U64_1165;
    U64 hoisted__U64_1166 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1165); });
    (void)hoisted__U64_1166;
    return hoisted__U64_1166;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 U32_size(void) {
    U64 hoisted__U64_1270 = 4ULL;
    (void)hoisted__U64_1270;
    return hoisted__U64_1270;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U64 hoisted__U64_1355 = 0ULL;
    (void)hoisted__U64_1355;
    U64 hoisted__U64_1356 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1355); });
    (void)hoisted__U64_1356;
    return hoisted__U64_1356;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1357 = U64_to_str_ext(val);
    (void)hoisted__Str_1357;
    return hoisted__Str_1357;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 U64_size(void) {
    U64 hoisted__U64_1362 = 8ULL;
    (void)hoisted__U64_1362;
    return hoisted__U64_1362;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U64 hoisted__U64_1447 = 0ULL;
    (void)hoisted__U64_1447;
    U64 hoisted__U64_1448 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1447); });
    (void)hoisted__U64_1448;
    return hoisted__U64_1448;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 I8_size(void) {
    U64 hoisted__U64_1465 = 1ULL;
    (void)hoisted__U64_1465;
    return hoisted__U64_1465;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U64 hoisted__U64_1466 = 0ULL;
    (void)hoisted__U64_1466;
    U64 hoisted__U64_1467 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1466); });
    (void)hoisted__U64_1467;
    return hoisted__U64_1467;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 I32_size(void) {
    U64 hoisted__U64_1644 = 4ULL;
    (void)hoisted__U64_1644;
    return hoisted__U64_1644;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U64 hoisted__U64_1786 = 0ULL;
    (void)hoisted__U64_1786;
    U64 hoisted__U64_1787 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1786); });
    (void)hoisted__U64_1787;
    return hoisted__U64_1787;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1798 = 0;
    (void)hoisted__I64_1798;
    Bool hoisted__Bool_1799 = ((Bool)(val < hoisted__I64_1798));
    (void)hoisted__Bool_1799;
    if (hoisted__Bool_1799) {
        U64 hoisted__U64_1788 = 0ULL;
        (void)hoisted__U64_1788;
        U64 hoisted__U64_1789 = (U64)(val);
        (void)hoisted__U64_1789;
        U64 mag = ((U64)(hoisted__U64_1788 - hoisted__U64_1789));
        U64 hoisted__U64_1790 = 2ULL;
        (void)hoisted__U64_1790;
        Array__Str *_va_Array_44 = Array__Str_new(hoisted__U64_1790);
        (void)_va_Array_44;
        I64 _va_Array_44_ek = 0;
        (void)_va_Array_44_ek;
        OutOfBounds *_va_Array_44_eo = malloc(sizeof(OutOfBounds));
        _va_Array_44_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_44_eo;
        U64 hoisted__U64_1791 = 0ULL;
        (void)hoisted__U64_1791;
        static Str hoisted__Str_1792 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1792;
        static Str hoisted__Str_1793 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1793;
        Array__Str_set(_va_Array_44, hoisted__U64_1791, &hoisted__Str_1792, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1793);
        Str_delete(&hoisted__Str_1793, (Bool){0});
        U64 hoisted__U64_1794 = 1ULL;
        (void)hoisted__U64_1794;
        Str *hoisted__Str_1795 = U64_to_str(mag);
        (void)hoisted__Str_1795;
        static Str hoisted__Str_1796 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1796;
        Array__Str_set(_va_Array_44, hoisted__U64_1794, hoisted__Str_1795, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1796);
        OutOfBounds_delete(_va_Array_44_eo, 1);
        Str_delete(&hoisted__Str_1796, (Bool){0});
        Str *hoisted__Str_1797 = format(_va_Array_44);
        (void)hoisted__Str_1797;
        { Str * _ret_val = hoisted__Str_1797;
                return _ret_val; }
    }
    U64 hoisted__U64_1800 = (U64)(val);
    (void)hoisted__U64_1800;
    Str *hoisted__Str_1801 = U64_to_str(hoisted__U64_1800);
    (void)hoisted__Str_1801;
    return hoisted__Str_1801;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 I64_size(void) {
    U64 hoisted__U64_1815 = 8ULL;
    (void)hoisted__U64_1815;
    return hoisted__U64_1815;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U64 hoisted__U64_1973 = 0ULL;
    (void)hoisted__U64_1973;
    U64 hoisted__U64_1974 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1973); });
    (void)hoisted__U64_1974;
    return hoisted__U64_1974;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 F32_size(void) {
    U64 hoisted__U64_1976 = 4ULL;
    (void)hoisted__U64_1976;
    return hoisted__U64_1976;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U64 hoisted__U64_1994 = 0ULL;
    (void)hoisted__U64_1994;
    U64 hoisted__U64_1995 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1994); });
    (void)hoisted__U64_1995;
    return hoisted__U64_1995;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2046 = ((Bool)(a == b));
    (void)hoisted__Bool_2046;
    if (hoisted__Bool_2046) {
        I64 hoisted__I64_2044 = 0;
        (void)hoisted__I64_2044;
        { I64 _ret_val = hoisted__I64_2044;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2045 = -1;
        (void)hoisted__I64_2045;
        return hoisted__I64_2045;
    }
    I64 hoisted__I64_2047 = 1;
    (void)hoisted__I64_2047;
    return hoisted__I64_2047;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Bool_size(void) {
    U64 hoisted__U64_2048 = 1ULL;
    (void)hoisted__U64_2048;
    return hoisted__U64_2048;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U64 hoisted__U64_2049 = 0ULL;
    (void)hoisted__U64_2049;
    U64 hoisted__U64_2050 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_2049); });
    (void)hoisted__U64_2050;
    return hoisted__U64_2050;
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
    U64 hoisted__U64_2184 = 1ULL;
    (void)hoisted__U64_2184;
    Bool hoisted__Bool_2185 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2185;
    if (hoisted__Bool_2185) {
        U64 hoisted__U64_2164 = 1ULL;
        (void)hoisted__U64_2164;
        Bool hoisted__Bool_2165 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2165;
        { Bool _ret_val = hoisted__Bool_2165;
                return _ret_val; }
    }
    U64 hoisted__U64_2186 = 1ULL;
    (void)hoisted__U64_2186;
    Bool hoisted__Bool_2187 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2187;
    if (hoisted__Bool_2187) {
        U64 hoisted__U64_2166 = 1ULL;
        (void)hoisted__U64_2166;
        Bool hoisted__Bool_2167 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2167;
        { Bool _ret_val = hoisted__Bool_2167;
                return _ret_val; }
    }
    U64 hoisted__U64_2188 = 1ULL;
    (void)hoisted__U64_2188;
    Bool hoisted__Bool_2189 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2189;
    if (hoisted__Bool_2189) {
        U64 hoisted__U64_2168 = 1ULL;
        (void)hoisted__U64_2168;
        Bool hoisted__Bool_2169 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2169;
        { Bool _ret_val = hoisted__Bool_2169;
                return _ret_val; }
    }
    U64 hoisted__U64_2190 = 1ULL;
    (void)hoisted__U64_2190;
    Bool hoisted__Bool_2191 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2191;
    if (hoisted__Bool_2191) {
        U64 hoisted__U64_2170 = 1ULL;
        (void)hoisted__U64_2170;
        Bool hoisted__Bool_2171 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2171;
        { Bool _ret_val = hoisted__Bool_2171;
                return _ret_val; }
    }
    U64 hoisted__U64_2192 = 1ULL;
    (void)hoisted__U64_2192;
    Bool hoisted__Bool_2193 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2193;
    if (hoisted__Bool_2193) {
        U64 hoisted__U64_2172 = 1ULL;
        (void)hoisted__U64_2172;
        Bool hoisted__Bool_2173 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2173;
        { Bool _ret_val = hoisted__Bool_2173;
                return _ret_val; }
    }
    U64 hoisted__U64_2194 = 1ULL;
    (void)hoisted__U64_2194;
    Bool hoisted__Bool_2195 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2195;
    if (hoisted__Bool_2195) {
        U64 hoisted__U64_2174 = 1ULL;
        (void)hoisted__U64_2174;
        Bool hoisted__Bool_2175 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2175;
        { Bool _ret_val = hoisted__Bool_2175;
                return _ret_val; }
    }
    U64 hoisted__U64_2196 = 1ULL;
    (void)hoisted__U64_2196;
    Bool hoisted__Bool_2197 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2197;
    if (hoisted__Bool_2197) {
        U64 hoisted__U64_2176 = 1ULL;
        (void)hoisted__U64_2176;
        Bool hoisted__Bool_2177 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2177;
        { Bool _ret_val = hoisted__Bool_2177;
                return _ret_val; }
    }
    U64 hoisted__U64_2198 = 1ULL;
    (void)hoisted__U64_2198;
    Bool hoisted__Bool_2199 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2199;
    if (hoisted__Bool_2199) {
        U64 hoisted__U64_2178 = 1ULL;
        (void)hoisted__U64_2178;
        Bool hoisted__Bool_2179 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2179;
        { Bool _ret_val = hoisted__Bool_2179;
                return _ret_val; }
    }
    U64 hoisted__U64_2200 = 1ULL;
    (void)hoisted__U64_2200;
    Bool hoisted__Bool_2201 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2201;
    if (hoisted__Bool_2201) {
        U64 hoisted__U64_2180 = 1ULL;
        (void)hoisted__U64_2180;
        Bool hoisted__Bool_2181 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2181;
        { Bool _ret_val = hoisted__Bool_2181;
                return _ret_val; }
    }
    U64 hoisted__U64_2202 = 1ULL;
    (void)hoisted__U64_2202;
    Bool hoisted__Bool_2203 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2203;
    if (hoisted__Bool_2203) {
        U64 hoisted__U64_2182 = 1ULL;
        (void)hoisted__U64_2182;
        Bool hoisted__Bool_2183 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_2183;
        { Bool _ret_val = hoisted__Bool_2183;
                return _ret_val; }
    }
    Bool hoisted__Bool_2204 = 0;
    (void)hoisted__Bool_2204;
    return hoisted__Bool_2204;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2226 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2226;
    if (hoisted__Bool_2226) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2227 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2227;
    if (hoisted__Bool_2227) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2228 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2228;
    if (hoisted__Bool_2228) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2229 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2229;
    if (hoisted__Bool_2229) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2230 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2230;
    if (hoisted__Bool_2230) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2231 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2231;
    if (hoisted__Bool_2231) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2232 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2232;
    if (hoisted__Bool_2232) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2233 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2233;
    if (hoisted__Bool_2233) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2234 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2234;
    if (hoisted__Bool_2234) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2235 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2235;
    if (hoisted__Bool_2235) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2236 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2236;
    UNREACHABLE(&hoisted__Str_2236);
    Str_delete(&hoisted__Str_2236, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

U64 Primitive_size(void) {
    U64 hoisted__U64_2237 = 1ULL;
    (void)hoisted__U64_2237;
    return hoisted__U64_2237;
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
    U64 hoisted__U64_2316 = 1ULL;
    (void)hoisted__U64_2316;
    Bool hoisted__Bool_2317 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2317;
    if (hoisted__Bool_2317) {
        Str *hoisted__Str_2306 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2306;
        (void)hoisted__Str_2306;
        Bool hoisted__Bool_2307 = 0;
        (void)hoisted__Bool_2307;
        Str_delete(hoisted__Str_2306, hoisted__Bool_2307);
    }
    U64 hoisted__U64_2318 = 1ULL;
    (void)hoisted__U64_2318;
    Bool hoisted__Bool_2319 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2319;
    if (hoisted__Bool_2319) {
        Str *hoisted__Str_2308 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2308;
        (void)hoisted__Str_2308;
        Bool hoisted__Bool_2309 = 0;
        (void)hoisted__Bool_2309;
        Str_delete(hoisted__Str_2308, hoisted__Bool_2309);
    }
    U64 hoisted__U64_2320 = 1ULL;
    (void)hoisted__U64_2320;
    Bool hoisted__Bool_2321 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2321;
    if (hoisted__Bool_2321) {
        Str *hoisted__Str_2310 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2310;
        (void)hoisted__Str_2310;
        Bool hoisted__Bool_2311 = 0;
        (void)hoisted__Bool_2311;
        Str_delete(hoisted__Str_2310, hoisted__Bool_2311);
    }
    U64 hoisted__U64_2322 = 1ULL;
    (void)hoisted__U64_2322;
    Bool hoisted__Bool_2323 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2323;
    if (hoisted__Bool_2323) {
        Primitive *hoisted__Primitive_2312 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Primitive_2312;
        (void)hoisted__Primitive_2312;
        Bool hoisted__Bool_2313 = 0;
        (void)hoisted__Bool_2313;
        Primitive_delete(hoisted__Primitive_2312, hoisted__Bool_2313);
    }
    U64 hoisted__U64_2324 = 1ULL;
    (void)hoisted__U64_2324;
    Bool hoisted__Bool_2325 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2325;
    if (hoisted__Bool_2325) {
        Str *hoisted__Str_2314 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2314;
        (void)hoisted__Str_2314;
        Bool hoisted__Bool_2315 = 0;
        (void)hoisted__Bool_2315;
        Str_delete(hoisted__Str_2314, hoisted__Bool_2315);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U64 hoisted__U64_2426 = 1ULL;
    (void)hoisted__U64_2426;
    Bool hoisted__Bool_2427 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2427;
    if (hoisted__Bool_2427) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U64 hoisted__U64_2428 = 1ULL;
    (void)hoisted__U64_2428;
    Bool hoisted__Bool_2429 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2429;
    if (hoisted__Bool_2429) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U64 hoisted__U64_2430 = 1ULL;
    (void)hoisted__U64_2430;
    Bool hoisted__Bool_2431 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2431;
    if (hoisted__Bool_2431) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2416 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2416;
        Type *hoisted__Type_2417 = Type_Struct(hoisted__Str_2416);
        (void)hoisted__Type_2417;
        { Type * _ret_val = hoisted__Type_2417;
                return _ret_val; }
    }
    U64 hoisted__U64_2432 = 1ULL;
    (void)hoisted__U64_2432;
    Bool hoisted__Bool_2433 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2433;
    if (hoisted__Bool_2433) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U64 hoisted__U64_2434 = 1ULL;
    (void)hoisted__U64_2434;
    Bool hoisted__Bool_2435 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2435;
    if (hoisted__Bool_2435) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2418 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2418;
        Type *hoisted__Type_2419 = Type_Enum(hoisted__Str_2418);
        (void)hoisted__Type_2419;
        { Type * _ret_val = hoisted__Type_2419;
                return _ret_val; }
    }
    U64 hoisted__U64_2436 = 1ULL;
    (void)hoisted__U64_2436;
    Bool hoisted__Bool_2437 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2437;
    if (hoisted__Bool_2437) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U64 hoisted__U64_2438 = 1ULL;
    (void)hoisted__U64_2438;
    Bool hoisted__Bool_2439 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2439;
    if (hoisted__Bool_2439) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U64 hoisted__U64_2440 = 1ULL;
    (void)hoisted__U64_2440;
    Bool hoisted__Bool_2441 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2441;
    if (hoisted__Bool_2441) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U64 hoisted__U64_2442 = 1ULL;
    (void)hoisted__U64_2442;
    Bool hoisted__Bool_2443 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2443;
    if (hoisted__Bool_2443) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U64 hoisted__U64_2444 = 1ULL;
    (void)hoisted__U64_2444;
    Bool hoisted__Bool_2445 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2445;
    if (hoisted__Bool_2445) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2420 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2420;
        Type *hoisted__Type_2421 = Type_Custom(hoisted__Str_2420);
        (void)hoisted__Type_2421;
        { Type * _ret_val = hoisted__Type_2421;
                return _ret_val; }
    }
    U64 hoisted__U64_2446 = 1ULL;
    (void)hoisted__U64_2446;
    Bool hoisted__Bool_2447 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2447;
    if (hoisted__Bool_2447) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2422 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2422;
        Type *hoisted__Type_2423 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2422; _oa; }));
        (void)hoisted__Type_2423;
        { Type * _ret_val = hoisted__Type_2423;
                return _ret_val; }
    }
    U64 hoisted__U64_2448 = 1ULL;
    (void)hoisted__U64_2448;
    Bool hoisted__Bool_2449 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2449;
    if (hoisted__Bool_2449) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2424 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2424;
        Type *hoisted__Type_2425 = Type_FuncPtrSig(hoisted__Str_2424);
        (void)hoisted__Type_2425;
        { Type * _ret_val = hoisted__Type_2425;
                return _ret_val; }
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

U64 Type_size(void) {
    U64 hoisted__U64_2450 = 32ULL;
    (void)hoisted__U64_2450;
    return hoisted__U64_2450;
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
    U64 hoisted__U64_2598 = 1ULL;
    (void)hoisted__U64_2598;
    Bool hoisted__Bool_2599 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2599;
    if (hoisted__Bool_2599) {
        U64 hoisted__U64_2576 = 1ULL;
        (void)hoisted__U64_2576;
        Bool hoisted__Bool_2577 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2577;
        { Bool _ret_val = hoisted__Bool_2577;
                return _ret_val; }
    }
    U64 hoisted__U64_2600 = 1ULL;
    (void)hoisted__U64_2600;
    Bool hoisted__Bool_2601 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2601;
    if (hoisted__Bool_2601) {
        U64 hoisted__U64_2578 = 1ULL;
        (void)hoisted__U64_2578;
        Bool hoisted__Bool_2579 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2579;
        { Bool _ret_val = hoisted__Bool_2579;
                return _ret_val; }
    }
    U64 hoisted__U64_2602 = 1ULL;
    (void)hoisted__U64_2602;
    Bool hoisted__Bool_2603 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2603;
    if (hoisted__Bool_2603) {
        U64 hoisted__U64_2580 = 1ULL;
        (void)hoisted__U64_2580;
        Bool hoisted__Bool_2581 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2581;
        { Bool _ret_val = hoisted__Bool_2581;
                return _ret_val; }
    }
    U64 hoisted__U64_2604 = 1ULL;
    (void)hoisted__U64_2604;
    Bool hoisted__Bool_2605 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2605;
    if (hoisted__Bool_2605) {
        U64 hoisted__U64_2582 = 1ULL;
        (void)hoisted__U64_2582;
        Bool hoisted__Bool_2583 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2583;
        { Bool _ret_val = hoisted__Bool_2583;
                return _ret_val; }
    }
    U64 hoisted__U64_2606 = 1ULL;
    (void)hoisted__U64_2606;
    Bool hoisted__Bool_2607 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2607;
    if (hoisted__Bool_2607) {
        U64 hoisted__U64_2584 = 1ULL;
        (void)hoisted__U64_2584;
        Bool hoisted__Bool_2585 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2585;
        { Bool _ret_val = hoisted__Bool_2585;
                return _ret_val; }
    }
    U64 hoisted__U64_2608 = 1ULL;
    (void)hoisted__U64_2608;
    Bool hoisted__Bool_2609 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2609;
    if (hoisted__Bool_2609) {
        U64 hoisted__U64_2586 = 1ULL;
        (void)hoisted__U64_2586;
        Bool hoisted__Bool_2587 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2587;
        { Bool _ret_val = hoisted__Bool_2587;
                return _ret_val; }
    }
    U64 hoisted__U64_2610 = 1ULL;
    (void)hoisted__U64_2610;
    Bool hoisted__Bool_2611 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2611;
    if (hoisted__Bool_2611) {
        U64 hoisted__U64_2588 = 1ULL;
        (void)hoisted__U64_2588;
        Bool hoisted__Bool_2589 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2589;
        { Bool _ret_val = hoisted__Bool_2589;
                return _ret_val; }
    }
    U64 hoisted__U64_2612 = 1ULL;
    (void)hoisted__U64_2612;
    Bool hoisted__Bool_2613 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2613;
    if (hoisted__Bool_2613) {
        U64 hoisted__U64_2590 = 1ULL;
        (void)hoisted__U64_2590;
        Bool hoisted__Bool_2591 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2591;
        { Bool _ret_val = hoisted__Bool_2591;
                return _ret_val; }
    }
    U64 hoisted__U64_2614 = 1ULL;
    (void)hoisted__U64_2614;
    Bool hoisted__Bool_2615 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2615;
    if (hoisted__Bool_2615) {
        U64 hoisted__U64_2592 = 1ULL;
        (void)hoisted__U64_2592;
        Bool hoisted__Bool_2593 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2593;
        { Bool _ret_val = hoisted__Bool_2593;
                return _ret_val; }
    }
    U64 hoisted__U64_2616 = 1ULL;
    (void)hoisted__U64_2616;
    Bool hoisted__Bool_2617 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2617;
    if (hoisted__Bool_2617) {
        U64 hoisted__U64_2594 = 1ULL;
        (void)hoisted__U64_2594;
        Bool hoisted__Bool_2595 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2595;
        { Bool _ret_val = hoisted__Bool_2595;
                return _ret_val; }
    }
    U64 hoisted__U64_2618 = 1ULL;
    (void)hoisted__U64_2618;
    Bool hoisted__Bool_2619 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreLazyFunc}))->tag));
    (void)hoisted__Bool_2619;
    if (hoisted__Bool_2619) {
        U64 hoisted__U64_2596 = 1ULL;
        (void)hoisted__U64_2596;
        Bool hoisted__Bool_2597 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreLazyFunc}))->tag));
        (void)hoisted__Bool_2597;
        { Bool _ret_val = hoisted__Bool_2597;
                return _ret_val; }
    }
    Bool hoisted__Bool_2620 = 0;
    (void)hoisted__Bool_2620;
    return hoisted__Bool_2620;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2644 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2644;
    if (hoisted__Bool_2644) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2645 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2645;
    if (hoisted__Bool_2645) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2646 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2646;
    if (hoisted__Bool_2646) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2647 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2647;
    if (hoisted__Bool_2647) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2648 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2648;
    if (hoisted__Bool_2648) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2649 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2649;
    if (hoisted__Bool_2649) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2650 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2650;
    if (hoisted__Bool_2650) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2651 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2651;
    if (hoisted__Bool_2651) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2652 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2652;
    if (hoisted__Bool_2652) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2653 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2653;
    if (hoisted__Bool_2653) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    Bool hoisted__Bool_2654 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreLazyFunc});
    (void)hoisted__Bool_2654;
    if (hoisted__Bool_2654) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreLazyFunc;
                return _r; }
    }
    static Str hoisted__Str_2655 = (Str){.c_str = (void *)"FuncType.clone:130:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2655;
    UNREACHABLE(&hoisted__Str_2655);
    Str_delete(&hoisted__Str_2655, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

U64 FuncType_size(void) {
    U64 hoisted__U64_2656 = 1ULL;
    (void)hoisted__U64_2656;
    return hoisted__U64_2656;
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
    U64 hoisted__U64_2663 = 1ULL;
    (void)hoisted__U64_2663;
    Bool hoisted__Bool_2664 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2664;
    if (hoisted__Bool_2664) {
        U64 hoisted__U64_2657 = 1ULL;
        (void)hoisted__U64_2657;
        Bool hoisted__Bool_2658 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2658;
        { Bool _ret_val = hoisted__Bool_2658;
                return _ret_val; }
    }
    U64 hoisted__U64_2665 = 1ULL;
    (void)hoisted__U64_2665;
    Bool hoisted__Bool_2666 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2666;
    if (hoisted__Bool_2666) {
        U64 hoisted__U64_2659 = 1ULL;
        (void)hoisted__U64_2659;
        Bool hoisted__Bool_2660 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2660;
        { Bool _ret_val = hoisted__Bool_2660;
                return _ret_val; }
    }
    U64 hoisted__U64_2667 = 1ULL;
    (void)hoisted__U64_2667;
    Bool hoisted__Bool_2668 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2668;
    if (hoisted__Bool_2668) {
        U64 hoisted__U64_2661 = 1ULL;
        (void)hoisted__U64_2661;
        Bool hoisted__Bool_2662 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2662;
        { Bool _ret_val = hoisted__Bool_2662;
                return _ret_val; }
    }
    Bool hoisted__Bool_2669 = 0;
    (void)hoisted__Bool_2669;
    return hoisted__Bool_2669;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2677 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2677;
    if (hoisted__Bool_2677) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2678 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2678;
    if (hoisted__Bool_2678) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2679 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2679;
    if (hoisted__Bool_2679) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2680 = (Str){.c_str = (void *)"OwnType.clone:149:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2680;
    UNREACHABLE(&hoisted__Str_2680);
    Str_delete(&hoisted__Str_2680, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

U64 OwnType_size(void) {
    U64 hoisted__U64_2681 = 1ULL;
    (void)hoisted__U64_2681;
    return hoisted__U64_2681;
    __builtin_unreachable();
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2683 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2683;
    Declaration *hoisted__Declaration_2684 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2684->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2684->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2684->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2684->is_mut = self->is_mut;
    hoisted__Declaration_2684->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2684->is_priv = self->is_priv;
    hoisted__Declaration_2684->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2684->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2684->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2684->default_value = hoisted__Expr_2683;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2684->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2684;
    return hoisted__Declaration_2684;
    __builtin_unreachable();
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2685 = 0;
    (void)hoisted__Bool_2685;
    Str_delete(&self->name, hoisted__Bool_2685);
    Bool hoisted__Bool_2686 = 0;
    (void)hoisted__Bool_2686;
    Str_delete(&self->doc, hoisted__Bool_2686);
    Bool hoisted__Bool_2687 = 0;
    (void)hoisted__Bool_2687;
    Str_delete(&self->explicit_type, hoisted__Bool_2687);
    Bool hoisted__Bool_2688 = 0;
    (void)hoisted__Bool_2688;
    Bool_delete(&self->is_mut, hoisted__Bool_2688);
    Bool hoisted__Bool_2689 = 0;
    (void)hoisted__Bool_2689;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2689);
    Bool hoisted__Bool_2690 = 0;
    (void)hoisted__Bool_2690;
    Bool_delete(&self->is_priv, hoisted__Bool_2690);
    Bool hoisted__Bool_2691 = 0;
    (void)hoisted__Bool_2691;
    Bool_delete(&self->used, hoisted__Bool_2691);
    Bool hoisted__Bool_2692 = 0;
    (void)hoisted__Bool_2692;
    OwnType_delete(&self->own_type, hoisted__Bool_2692);
    Bool hoisted__Bool_2693 = 0;
    (void)hoisted__Bool_2693;
    Type_delete(&self->til_type, hoisted__Bool_2693);
    Bool hoisted__Bool_2694 = 1;
    (void)hoisted__Bool_2694;
    Expr_delete(self->default_value, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    Str_delete(&self->orig_name, hoisted__Bool_2695);
    if (call_free) {
        free(self);
    }
}

U64 Declaration_size(void) {
    U64 hoisted__U64_2696 = 144ULL;
    (void)hoisted__U64_2696;
    return hoisted__U64_2696;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2698 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2698->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2698->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2698->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2698->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2698->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2698->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2698->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2698->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2698->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2698->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2698->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2698->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2698;
    return hoisted__FunctionDef_2698;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2699 = 0;
    (void)hoisted__Bool_2699;
    FuncType_delete(&self->func_type, hoisted__Bool_2699);
    Bool hoisted__Bool_2700 = 0;
    (void)hoisted__Bool_2700;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2700);
    Bool hoisted__Bool_2701 = 0;
    (void)hoisted__Bool_2701;
    Str_delete(&self->return_type, hoisted__Bool_2701);
    Bool hoisted__Bool_2702 = 0;
    (void)hoisted__Bool_2702;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2702);
    Bool hoisted__Bool_2703 = 0;
    (void)hoisted__Bool_2703;
    I32_delete(&self->variadic_index, hoisted__Bool_2703);
    Bool hoisted__Bool_2704 = 0;
    (void)hoisted__Bool_2704;
    I32_delete(&self->kwargs_index, hoisted__Bool_2704);
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2706);
    Bool hoisted__Bool_2707 = 0;
    (void)hoisted__Bool_2707;
    Bool_delete(&self->auto_generated, hoisted__Bool_2707);
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2709);
    Bool hoisted__Bool_2710 = 0;
    (void)hoisted__Bool_2710;
    Str_delete(&self->closure_name, hoisted__Bool_2710);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U64 hoisted__U64_2711 = 0ULL;
    (void)hoisted__U64_2711;
    U64 hoisted__U64_2712 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2711); });
    (void)hoisted__U64_2712;
    return hoisted__U64_2712;
    __builtin_unreachable();
}

U64 FunctionDef_size(void) {
    U64 hoisted__U64_2713 = 144ULL;
    (void)hoisted__U64_2713;
    return hoisted__U64_2713;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2716 = malloc(sizeof(FCallData));
    hoisted__FCallData_2716->is_splat = self->is_splat;
    hoisted__FCallData_2716->does_throw = self->does_throw;
    hoisted__FCallData_2716->is_bang = self->is_bang;
    hoisted__FCallData_2716->own_args = self->own_args;
    hoisted__FCallData_2716->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2716->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2716;
    return hoisted__FCallData_2716;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2717 = 0;
    (void)hoisted__Bool_2717;
    Bool_delete(&self->is_splat, hoisted__Bool_2717);
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    Bool_delete(&self->does_throw, hoisted__Bool_2718);
    Bool hoisted__Bool_2719 = 0;
    (void)hoisted__Bool_2719;
    Bool_delete(&self->is_bang, hoisted__Bool_2719);
    Bool hoisted__Bool_2720 = 0;
    (void)hoisted__Bool_2720;
    U64_delete(&self->own_args, hoisted__Bool_2720);
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Bool_delete(&self->swap_replace, hoisted__Bool_2721);
    Bool hoisted__Bool_2722 = 0;
    (void)hoisted__Bool_2722;
    Type_delete(&self->til_type, hoisted__Bool_2722);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U64 hoisted__U64_2723 = 0ULL;
    (void)hoisted__U64_2723;
    U64 hoisted__U64_2724 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2723); });
    (void)hoisted__U64_2724;
    return hoisted__U64_2724;
    __builtin_unreachable();
}

U64 FCallData_size(void) {
    U64 hoisted__U64_2725 = 56ULL;
    (void)hoisted__U64_2725;
    return hoisted__U64_2725;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2737 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2737->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2737->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2737;
    return hoisted__LiteralNumData_2737;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Str_delete(&self->text, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Type_delete(&self->til_type, hoisted__Bool_2739);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U64 hoisted__U64_2740 = 0ULL;
    (void)hoisted__U64_2740;
    U64 hoisted__U64_2741 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2740); });
    (void)hoisted__U64_2741;
    return hoisted__U64_2741;
    __builtin_unreachable();
}

U64 LiteralNumData_size(void) {
    U64 hoisted__U64_2742 = 56ULL;
    (void)hoisted__U64_2742;
    return hoisted__U64_2742;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2752 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2752->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2752->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2752;
    return hoisted__IdentData_2752;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Str_delete(&self->name, hoisted__Bool_2753);
    Bool hoisted__Bool_2754 = 0;
    (void)hoisted__Bool_2754;
    Type_delete(&self->til_type, hoisted__Bool_2754);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U64 hoisted__U64_2755 = 0ULL;
    (void)hoisted__U64_2755;
    U64 hoisted__U64_2756 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2755); });
    (void)hoisted__U64_2756;
    return hoisted__U64_2756;
    __builtin_unreachable();
}

U64 IdentData_size(void) {
    U64 hoisted__U64_2757 = 56ULL;
    (void)hoisted__U64_2757;
    return hoisted__U64_2757;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2763 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2763->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2763->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2763;
    return hoisted__FieldAccessData_2763;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2764 = 0;
    (void)hoisted__Bool_2764;
    Str_delete(&self->name, hoisted__Bool_2764);
    Bool hoisted__Bool_2765 = 0;
    (void)hoisted__Bool_2765;
    Type_delete(&self->til_type, hoisted__Bool_2765);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U64 hoisted__U64_2766 = 0ULL;
    (void)hoisted__U64_2766;
    U64 hoisted__U64_2767 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2766); });
    (void)hoisted__U64_2767;
    return hoisted__U64_2767;
    __builtin_unreachable();
}

U64 FieldAccessData_size(void) {
    U64 hoisted__U64_2768 = 56ULL;
    (void)hoisted__U64_2768;
    return hoisted__U64_2768;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2847 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2847->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2847->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2847->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2847->is_interface = self->is_interface;
    hoisted__StructDef_2847->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2847->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2847;
    return hoisted__StructDef_2847;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2848 = 0;
    (void)hoisted__Bool_2848;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2848);
    Bool hoisted__Bool_2849 = 0;
    (void)hoisted__Bool_2849;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2849);
    Bool hoisted__Bool_2850 = 0;
    (void)hoisted__Bool_2850;
    Str_delete(&self->c_tag, hoisted__Bool_2850);
    Bool hoisted__Bool_2851 = 0;
    (void)hoisted__Bool_2851;
    Bool_delete(&self->is_interface, hoisted__Bool_2851);
    Bool hoisted__Bool_2852 = 0;
    (void)hoisted__Bool_2852;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2852);
    Bool hoisted__Bool_2853 = 0;
    (void)hoisted__Bool_2853;
    Str_delete(&self->implements_name, hoisted__Bool_2853);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U64 hoisted__U64_2854 = 0ULL;
    (void)hoisted__U64_2854;
    U64 hoisted__U64_2855 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2854); });
    (void)hoisted__U64_2855;
    return hoisted__U64_2855;
    __builtin_unreachable();
}

U64 StructDef_size(void) {
    U64 hoisted__U64_2856 = 104ULL;
    (void)hoisted__U64_2856;
    return hoisted__U64_2856;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2861 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2861->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2861->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2861->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2861->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2861->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2861->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2861->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2861;
    return hoisted__EnumDef_2861;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2862 = 0;
    (void)hoisted__Bool_2862;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2862);
    Bool hoisted__Bool_2863 = 0;
    (void)hoisted__Bool_2863;
    Vec__Str_delete(&self->variants, hoisted__Bool_2863);
    Bool hoisted__Bool_2864 = 0;
    (void)hoisted__Bool_2864;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2864);
    Bool hoisted__Bool_2865 = 0;
    (void)hoisted__Bool_2865;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2865);
    Bool hoisted__Bool_2866 = 0;
    (void)hoisted__Bool_2866;
    Str_delete(&self->implements_name, hoisted__Bool_2866);
    Bool hoisted__Bool_2867 = 0;
    (void)hoisted__Bool_2867;
    Str_delete(&self->tag_type, hoisted__Bool_2867);
    Bool hoisted__Bool_2868 = 0;
    (void)hoisted__Bool_2868;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2868);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U64 hoisted__U64_2869 = 0ULL;
    (void)hoisted__U64_2869;
    U64 hoisted__U64_2870 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2869); });
    (void)hoisted__U64_2870;
    return hoisted__U64_2870;
    __builtin_unreachable();
}

U64 EnumDef_size(void) {
    U64 hoisted__U64_2871 = 192ULL;
    (void)hoisted__U64_2871;
    return hoisted__U64_2871;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2972 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2972->name = *_ca; free(_ca); }
    hoisted__AssignData_2972->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2972->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2972->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2972;
    return hoisted__AssignData_2972;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2973 = 0;
    (void)hoisted__Bool_2973;
    Str_delete(&self->name, hoisted__Bool_2973);
    Bool hoisted__Bool_2974 = 0;
    (void)hoisted__Bool_2974;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2974);
    Bool hoisted__Bool_2975 = 0;
    (void)hoisted__Bool_2975;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2975);
    Bool hoisted__Bool_2976 = 0;
    (void)hoisted__Bool_2976;
    Bool_delete(&self->swap_replace, hoisted__Bool_2976);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U64 hoisted__U64_2977 = 0ULL;
    (void)hoisted__U64_2977;
    U64 hoisted__U64_2978 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2977); });
    (void)hoisted__U64_2978;
    return hoisted__U64_2978;
    __builtin_unreachable();
}

U64 AssignData_size(void) {
    U64 hoisted__U64_2979 = 32ULL;
    (void)hoisted__U64_2979;
    return hoisted__U64_2979;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2981 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2981->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2981->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2981;
    return hoisted__FieldAssignData_2981;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2982 = 0;
    (void)hoisted__Bool_2982;
    Str_delete(&self->name, hoisted__Bool_2982);
    Bool hoisted__Bool_2983 = 0;
    (void)hoisted__Bool_2983;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2983);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U64 hoisted__U64_2984 = 0ULL;
    (void)hoisted__U64_2984;
    U64 hoisted__U64_2985 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2984); });
    (void)hoisted__U64_2985;
    return hoisted__U64_2985;
    __builtin_unreachable();
}

U64 FieldAssignData_size(void) {
    U64 hoisted__U64_2986 = 32ULL;
    (void)hoisted__U64_2986;
    return hoisted__U64_2986;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2988 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2988->name = *_ca; free(_ca); }
    hoisted__ForInData_2988->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2988->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2988->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2988->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2988;
    return hoisted__ForInData_2988;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2989 = 0;
    (void)hoisted__Bool_2989;
    Str_delete(&self->name, hoisted__Bool_2989);
    Bool hoisted__Bool_2990 = 0;
    (void)hoisted__Bool_2990;
    Bool_delete(&self->is_mut, hoisted__Bool_2990);
    Bool hoisted__Bool_2991 = 0;
    (void)hoisted__Bool_2991;
    Type_delete(&self->til_type, hoisted__Bool_2991);
    Bool hoisted__Bool_2992 = 0;
    (void)hoisted__Bool_2992;
    Str_delete(&self->name2, hoisted__Bool_2992);
    Bool hoisted__Bool_2993 = 0;
    (void)hoisted__Bool_2993;
    Bool_delete(&self->is_mut2, hoisted__Bool_2993);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U64 hoisted__U64_2994 = 0ULL;
    (void)hoisted__U64_2994;
    U64 hoisted__U64_2995 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2994); });
    (void)hoisted__U64_2995;
    return hoisted__U64_2995;
    __builtin_unreachable();
}

U64 ForInData_size(void) {
    U64 hoisted__U64_2996 = 96ULL;
    (void)hoisted__U64_2996;
    return hoisted__U64_2996;
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
    U64 hoisted__U64_3037 = 1ULL;
    (void)hoisted__U64_3037;
    Bool hoisted__Bool_3038 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3038;
    if (hoisted__Bool_3038) {
        Str *hoisted__Str_3031 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_3031;
        (void)hoisted__Str_3031;
        Bool hoisted__Bool_3032 = 0;
        (void)hoisted__Bool_3032;
        Str_delete(hoisted__Str_3031, hoisted__Bool_3032);
    }
    U64 hoisted__U64_3039 = 1ULL;
    (void)hoisted__U64_3039;
    Bool hoisted__Bool_3040 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3040;
    if (hoisted__Bool_3040) {
        LiteralNumData *hoisted__LiteralNumData_3033 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__LiteralNumData_3033;
        (void)hoisted__LiteralNumData_3033;
        Bool hoisted__Bool_3034 = 0;
        (void)hoisted__Bool_3034;
        LiteralNumData_delete(hoisted__LiteralNumData_3033, hoisted__Bool_3034);
    }
    U64 hoisted__U64_3041 = 1ULL;
    (void)hoisted__U64_3041;
    Bool hoisted__Bool_3042 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3042;
    if (hoisted__Bool_3042) {
        Bool *hoisted__Bool_3035 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Bool_3035;
        (void)hoisted__Bool_3035;
        Bool hoisted__Bool_3036 = 0;
        (void)hoisted__Bool_3036;
        Bool_delete(hoisted__Bool_3035, hoisted__Bool_3036);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U64 hoisted__U64_3097 = 1ULL;
    (void)hoisted__U64_3097;
    Bool hoisted__Bool_3098 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3098;
    if (hoisted__Bool_3098) {
        Str *_clone_payload_Str_0 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3092 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3092;
        Literal *hoisted__Literal_3093 = Literal_Str(hoisted__Str_3092);
        (void)hoisted__Literal_3093;
        { Literal * _ret_val = hoisted__Literal_3093;
                return _ret_val; }
    }
    U64 hoisted__U64_3099 = 1ULL;
    (void)hoisted__U64_3099;
    Bool hoisted__Bool_3100 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3100;
    if (hoisted__Bool_3100) {
        LiteralNumData *_clone_payload_Num_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3094 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3094;
        Literal *hoisted__Literal_3095 = Literal_Num(hoisted__LiteralNumData_3094);
        (void)hoisted__Literal_3095;
        { Literal * _ret_val = hoisted__Literal_3095;
                return _ret_val; }
    }
    U64 hoisted__U64_3101 = 1ULL;
    (void)hoisted__U64_3101;
    Bool hoisted__Bool_3102 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3102;
    if (hoisted__Bool_3102) {
        Bool *_clone_payload_Bool_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3096 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3096;
        { Literal * _ret_val = hoisted__Literal_3096;
                return _ret_val; }
    }
    U64 hoisted__U64_3103 = 1ULL;
    (void)hoisted__U64_3103;
    Bool hoisted__Bool_3104 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_3104;
    if (hoisted__Bool_3104) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U64 hoisted__U64_3105 = 1ULL;
    (void)hoisted__U64_3105;
    Bool hoisted__Bool_3106 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_3106;
    if (hoisted__Bool_3106) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

U64 Literal_size(void) {
    U64 hoisted__U64_3107 = 64ULL;
    (void)hoisted__U64_3107;
    return hoisted__U64_3107;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3110 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3110->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3110->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3110;
    return hoisted__MatchData_3110;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3111 = 0;
    (void)hoisted__Bool_3111;
    Type_delete(&self->til_type, hoisted__Bool_3111);
    Bool hoisted__Bool_3112 = 0;
    (void)hoisted__Bool_3112;
    Str_delete(&self->result_temp, hoisted__Bool_3112);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U64 hoisted__U64_3113 = 0ULL;
    (void)hoisted__U64_3113;
    U64 hoisted__U64_3114 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3113); });
    (void)hoisted__U64_3114;
    return hoisted__U64_3114;
    __builtin_unreachable();
}

U64 MatchData_size(void) {
    U64 hoisted__U64_3115 = 56ULL;
    (void)hoisted__U64_3115;
    return hoisted__U64_3115;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3120 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3120->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3120->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3120;
    return hoisted__CaptureBlockData_3120;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3121 = 0;
    (void)hoisted__Bool_3121;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3121);
    Bool hoisted__Bool_3122 = 0;
    (void)hoisted__Bool_3122;
    Str_delete(&self->closure_name, hoisted__Bool_3122);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U64 hoisted__U64_3123 = 0ULL;
    (void)hoisted__U64_3123;
    U64 hoisted__U64_3124 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3123); });
    (void)hoisted__U64_3124;
    return hoisted__U64_3124;
    __builtin_unreachable();
}

U64 CaptureBlockData_size(void) {
    U64 hoisted__U64_3125 = 48ULL;
    (void)hoisted__U64_3125;
    return hoisted__U64_3125;
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
    U64 hoisted__U64_3388 = 1ULL;
    (void)hoisted__U64_3388;
    Bool hoisted__Bool_3389 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3389;
    if (hoisted__Bool_3389) {
        Literal *hoisted__Literal_3358 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Literal_3358;
        (void)hoisted__Literal_3358;
        Bool hoisted__Bool_3359 = 0;
        (void)hoisted__Bool_3359;
        Literal_delete(hoisted__Literal_3358, hoisted__Bool_3359);
    }
    U64 hoisted__U64_3390 = 1ULL;
    (void)hoisted__U64_3390;
    Bool hoisted__Bool_3391 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3391;
    if (hoisted__Bool_3391) {
        IdentData *hoisted__IdentData_3360 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__IdentData_3360;
        (void)hoisted__IdentData_3360;
        Bool hoisted__Bool_3361 = 0;
        (void)hoisted__Bool_3361;
        IdentData_delete(hoisted__IdentData_3360, hoisted__Bool_3361);
    }
    U64 hoisted__U64_3392 = 1ULL;
    (void)hoisted__U64_3392;
    Bool hoisted__Bool_3393 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3393;
    if (hoisted__Bool_3393) {
        Declaration *hoisted__Declaration_3362 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Declaration_3362;
        (void)hoisted__Declaration_3362;
        Bool hoisted__Bool_3363 = 0;
        (void)hoisted__Bool_3363;
        Declaration_delete(hoisted__Declaration_3362, hoisted__Bool_3363);
    }
    U64 hoisted__U64_3394 = 1ULL;
    (void)hoisted__U64_3394;
    Bool hoisted__Bool_3395 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3395;
    if (hoisted__Bool_3395) {
        AssignData *hoisted__AssignData_3364 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__AssignData_3364;
        (void)hoisted__AssignData_3364;
        Bool hoisted__Bool_3365 = 0;
        (void)hoisted__Bool_3365;
        AssignData_delete(hoisted__AssignData_3364, hoisted__Bool_3365);
    }
    U64 hoisted__U64_3396 = 1ULL;
    (void)hoisted__U64_3396;
    Bool hoisted__Bool_3397 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3397;
    if (hoisted__Bool_3397) {
        FCallData *hoisted__FCallData_3366 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FCallData_3366;
        (void)hoisted__FCallData_3366;
        Bool hoisted__Bool_3367 = 0;
        (void)hoisted__Bool_3367;
        FCallData_delete(hoisted__FCallData_3366, hoisted__Bool_3367);
    }
    U64 hoisted__U64_3398 = 1ULL;
    (void)hoisted__U64_3398;
    Bool hoisted__Bool_3399 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3399;
    if (hoisted__Bool_3399) {
        FunctionDef *hoisted__FunctionDef_3368 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FunctionDef_3368;
        (void)hoisted__FunctionDef_3368;
        Bool hoisted__Bool_3369 = 0;
        (void)hoisted__Bool_3369;
        FunctionDef_delete(hoisted__FunctionDef_3368, hoisted__Bool_3369);
    }
    U64 hoisted__U64_3400 = 1ULL;
    (void)hoisted__U64_3400;
    Bool hoisted__Bool_3401 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3401;
    if (hoisted__Bool_3401) {
        StructDef *hoisted__StructDef_3370 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__StructDef_3370;
        (void)hoisted__StructDef_3370;
        Bool hoisted__Bool_3371 = 0;
        (void)hoisted__Bool_3371;
        StructDef_delete(hoisted__StructDef_3370, hoisted__Bool_3371);
    }
    U64 hoisted__U64_3402 = 1ULL;
    (void)hoisted__U64_3402;
    Bool hoisted__Bool_3403 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3403;
    if (hoisted__Bool_3403) {
        EnumDef *hoisted__EnumDef_3372 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__EnumDef_3372;
        (void)hoisted__EnumDef_3372;
        Bool hoisted__Bool_3373 = 0;
        (void)hoisted__Bool_3373;
        EnumDef_delete(hoisted__EnumDef_3372, hoisted__Bool_3373);
    }
    U64 hoisted__U64_3404 = 1ULL;
    (void)hoisted__U64_3404;
    Bool hoisted__Bool_3405 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3405;
    if (hoisted__Bool_3405) {
        FieldAccessData *hoisted__FieldAccessData_3374 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FieldAccessData_3374;
        (void)hoisted__FieldAccessData_3374;
        Bool hoisted__Bool_3375 = 0;
        (void)hoisted__Bool_3375;
        FieldAccessData_delete(hoisted__FieldAccessData_3374, hoisted__Bool_3375);
    }
    U64 hoisted__U64_3406 = 1ULL;
    (void)hoisted__U64_3406;
    Bool hoisted__Bool_3407 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3407;
    if (hoisted__Bool_3407) {
        FieldAssignData *hoisted__FieldAssignData_3376 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FieldAssignData_3376;
        (void)hoisted__FieldAssignData_3376;
        Bool hoisted__Bool_3377 = 0;
        (void)hoisted__Bool_3377;
        FieldAssignData_delete(hoisted__FieldAssignData_3376, hoisted__Bool_3377);
    }
    U64 hoisted__U64_3408 = 1ULL;
    (void)hoisted__U64_3408;
    Bool hoisted__Bool_3409 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3409;
    if (hoisted__Bool_3409) {
        ForInData *hoisted__ForInData_3378 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__ForInData_3378;
        (void)hoisted__ForInData_3378;
        Bool hoisted__Bool_3379 = 0;
        (void)hoisted__Bool_3379;
        ForInData_delete(hoisted__ForInData_3378, hoisted__Bool_3379);
    }
    U64 hoisted__U64_3410 = 1ULL;
    (void)hoisted__U64_3410;
    Bool hoisted__Bool_3411 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3411;
    if (hoisted__Bool_3411) {
        Str *hoisted__Str_3380 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_3380;
        (void)hoisted__Str_3380;
        Bool hoisted__Bool_3381 = 0;
        (void)hoisted__Bool_3381;
        Str_delete(hoisted__Str_3380, hoisted__Bool_3381);
    }
    U64 hoisted__U64_3412 = 1ULL;
    (void)hoisted__U64_3412;
    Bool hoisted__Bool_3413 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3413;
    if (hoisted__Bool_3413) {
        MatchData *hoisted__MatchData_3382 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__MatchData_3382;
        (void)hoisted__MatchData_3382;
        Bool hoisted__Bool_3383 = 0;
        (void)hoisted__Bool_3383;
        MatchData_delete(hoisted__MatchData_3382, hoisted__Bool_3383);
    }
    U64 hoisted__U64_3414 = 1ULL;
    (void)hoisted__U64_3414;
    Bool hoisted__Bool_3415 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3415;
    if (hoisted__Bool_3415) {
        CaptureBlockData *hoisted__CaptureBlockData_3384 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__CaptureBlockData_3384;
        (void)hoisted__CaptureBlockData_3384;
        Bool hoisted__Bool_3385 = 0;
        (void)hoisted__Bool_3385;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3384, hoisted__Bool_3385);
    }
    U64 hoisted__U64_3416 = 1ULL;
    (void)hoisted__U64_3416;
    Bool hoisted__Bool_3417 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3417;
    if (hoisted__Bool_3417) {
        CaptureBlockData *hoisted__CaptureBlockData_3386 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__CaptureBlockData_3386;
        (void)hoisted__CaptureBlockData_3386;
        Bool hoisted__Bool_3387 = 0;
        (void)hoisted__Bool_3387;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3386, hoisted__Bool_3387);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U64 hoisted__U64_3686 = 1ULL;
    (void)hoisted__U64_3686;
    Bool hoisted__Bool_3687 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3687;
    if (hoisted__Bool_3687) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U64 hoisted__U64_3688 = 1ULL;
    (void)hoisted__U64_3688;
    Bool hoisted__Bool_3689 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3689;
    if (hoisted__Bool_3689) {
        Literal *_clone_payload_Literal_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3656 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3656;
        NodeType *hoisted__NodeType_3657 = NodeType_Literal(hoisted__Literal_3656);
        (void)hoisted__NodeType_3657;
        { NodeType * _ret_val = hoisted__NodeType_3657;
                return _ret_val; }
    }
    U64 hoisted__U64_3690 = 1ULL;
    (void)hoisted__U64_3690;
    Bool hoisted__Bool_3691 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3691;
    if (hoisted__Bool_3691) {
        IdentData *_clone_payload_Ident_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3658 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3658;
        NodeType *hoisted__NodeType_3659 = NodeType_Ident(hoisted__IdentData_3658);
        (void)hoisted__NodeType_3659;
        { NodeType * _ret_val = hoisted__NodeType_3659;
                return _ret_val; }
    }
    U64 hoisted__U64_3692 = 1ULL;
    (void)hoisted__U64_3692;
    Bool hoisted__Bool_3693 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3693;
    if (hoisted__Bool_3693) {
        Declaration *_clone_payload_Decl_3 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3660 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3660;
        NodeType *hoisted__NodeType_3661 = NodeType_Decl(hoisted__Declaration_3660);
        (void)hoisted__NodeType_3661;
        { NodeType * _ret_val = hoisted__NodeType_3661;
                return _ret_val; }
    }
    U64 hoisted__U64_3694 = 1ULL;
    (void)hoisted__U64_3694;
    Bool hoisted__Bool_3695 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3695;
    if (hoisted__Bool_3695) {
        AssignData *_clone_payload_Assign_4 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3662 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3662;
        NodeType *hoisted__NodeType_3663 = NodeType_Assign(hoisted__AssignData_3662);
        (void)hoisted__NodeType_3663;
        { NodeType * _ret_val = hoisted__NodeType_3663;
                return _ret_val; }
    }
    U64 hoisted__U64_3696 = 1ULL;
    (void)hoisted__U64_3696;
    Bool hoisted__Bool_3697 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3697;
    if (hoisted__Bool_3697) {
        FCallData *_clone_payload_FCall_5 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3664 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3664;
        NodeType *hoisted__NodeType_3665 = NodeType_FCall(hoisted__FCallData_3664);
        (void)hoisted__NodeType_3665;
        { NodeType * _ret_val = hoisted__NodeType_3665;
                return _ret_val; }
    }
    U64 hoisted__U64_3698 = 1ULL;
    (void)hoisted__U64_3698;
    Bool hoisted__Bool_3699 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3699;
    if (hoisted__Bool_3699) {
        FunctionDef *_clone_payload_FuncDef_6 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3666 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3666;
        NodeType *hoisted__NodeType_3667 = NodeType_FuncDef(hoisted__FunctionDef_3666);
        (void)hoisted__NodeType_3667;
        { NodeType * _ret_val = hoisted__NodeType_3667;
                return _ret_val; }
    }
    U64 hoisted__U64_3700 = 1ULL;
    (void)hoisted__U64_3700;
    Bool hoisted__Bool_3701 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3701;
    if (hoisted__Bool_3701) {
        StructDef *_clone_payload_StructDef_7 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3668 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3668;
        NodeType *hoisted__NodeType_3669 = NodeType_StructDef(hoisted__StructDef_3668);
        (void)hoisted__NodeType_3669;
        { NodeType * _ret_val = hoisted__NodeType_3669;
                return _ret_val; }
    }
    U64 hoisted__U64_3702 = 1ULL;
    (void)hoisted__U64_3702;
    Bool hoisted__Bool_3703 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3703;
    if (hoisted__Bool_3703) {
        EnumDef *_clone_payload_EnumDef_8 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3670 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3670;
        NodeType *hoisted__NodeType_3671 = NodeType_EnumDef(hoisted__EnumDef_3670);
        (void)hoisted__NodeType_3671;
        { NodeType * _ret_val = hoisted__NodeType_3671;
                return _ret_val; }
    }
    U64 hoisted__U64_3704 = 1ULL;
    (void)hoisted__U64_3704;
    Bool hoisted__Bool_3705 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3705;
    if (hoisted__Bool_3705) {
        FieldAccessData *_clone_payload_FieldAccess_9 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3672 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3672;
        NodeType *hoisted__NodeType_3673 = NodeType_FieldAccess(hoisted__FieldAccessData_3672);
        (void)hoisted__NodeType_3673;
        { NodeType * _ret_val = hoisted__NodeType_3673;
                return _ret_val; }
    }
    U64 hoisted__U64_3706 = 1ULL;
    (void)hoisted__U64_3706;
    Bool hoisted__Bool_3707 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3707;
    if (hoisted__Bool_3707) {
        FieldAssignData *_clone_payload_FieldAssign_10 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3674 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3674;
        NodeType *hoisted__NodeType_3675 = NodeType_FieldAssign(hoisted__FieldAssignData_3674);
        (void)hoisted__NodeType_3675;
        { NodeType * _ret_val = hoisted__NodeType_3675;
                return _ret_val; }
    }
    U64 hoisted__U64_3708 = 1ULL;
    (void)hoisted__U64_3708;
    Bool hoisted__Bool_3709 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3709;
    if (hoisted__Bool_3709) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U64 hoisted__U64_3710 = 1ULL;
    (void)hoisted__U64_3710;
    Bool hoisted__Bool_3711 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3711;
    if (hoisted__Bool_3711) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U64 hoisted__U64_3712 = 1ULL;
    (void)hoisted__U64_3712;
    Bool hoisted__Bool_3713 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3713;
    if (hoisted__Bool_3713) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U64 hoisted__U64_3714 = 1ULL;
    (void)hoisted__U64_3714;
    Bool hoisted__Bool_3715 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3715;
    if (hoisted__Bool_3715) {
        ForInData *_clone_payload_ForIn_14 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3676 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3676;
        NodeType *hoisted__NodeType_3677 = NodeType_ForIn(hoisted__ForInData_3676);
        (void)hoisted__NodeType_3677;
        { NodeType * _ret_val = hoisted__NodeType_3677;
                return _ret_val; }
    }
    U64 hoisted__U64_3716 = 1ULL;
    (void)hoisted__U64_3716;
    Bool hoisted__Bool_3717 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3717;
    if (hoisted__Bool_3717) {
        Str *_clone_payload_NamedArg_15 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3678 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3678;
        NodeType *hoisted__NodeType_3679 = NodeType_NamedArg(hoisted__Str_3678);
        (void)hoisted__NodeType_3679;
        { NodeType * _ret_val = hoisted__NodeType_3679;
                return _ret_val; }
    }
    U64 hoisted__U64_3718 = 1ULL;
    (void)hoisted__U64_3718;
    Bool hoisted__Bool_3719 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3719;
    if (hoisted__Bool_3719) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U64 hoisted__U64_3720 = 1ULL;
    (void)hoisted__U64_3720;
    Bool hoisted__Bool_3721 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3721;
    if (hoisted__Bool_3721) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U64 hoisted__U64_3722 = 1ULL;
    (void)hoisted__U64_3722;
    Bool hoisted__Bool_3723 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3723;
    if (hoisted__Bool_3723) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U64 hoisted__U64_3724 = 1ULL;
    (void)hoisted__U64_3724;
    Bool hoisted__Bool_3725 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3725;
    if (hoisted__Bool_3725) {
        MatchData *_clone_payload_Match_19 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3680 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3680;
        NodeType *hoisted__NodeType_3681 = NodeType_Match(hoisted__MatchData_3680);
        (void)hoisted__NodeType_3681;
        { NodeType * _ret_val = hoisted__NodeType_3681;
                return _ret_val; }
    }
    U64 hoisted__U64_3726 = 1ULL;
    (void)hoisted__U64_3726;
    Bool hoisted__Bool_3727 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3727;
    if (hoisted__Bool_3727) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U64 hoisted__U64_3728 = 1ULL;
    (void)hoisted__U64_3728;
    Bool hoisted__Bool_3729 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3729;
    if (hoisted__Bool_3729) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U64 hoisted__U64_3730 = 1ULL;
    (void)hoisted__U64_3730;
    Bool hoisted__Bool_3731 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3731;
    if (hoisted__Bool_3731) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U64 hoisted__U64_3732 = 1ULL;
    (void)hoisted__U64_3732;
    Bool hoisted__Bool_3733 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3733;
    if (hoisted__Bool_3733) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U64 hoisted__U64_3734 = 1ULL;
    (void)hoisted__U64_3734;
    Bool hoisted__Bool_3735 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3735;
    if (hoisted__Bool_3735) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U64 hoisted__U64_3736 = 1ULL;
    (void)hoisted__U64_3736;
    Bool hoisted__Bool_3737 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3737;
    if (hoisted__Bool_3737) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3682 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3682;
        NodeType *hoisted__NodeType_3683 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3682);
        (void)hoisted__NodeType_3683;
        { NodeType * _ret_val = hoisted__NodeType_3683;
                return _ret_val; }
    }
    U64 hoisted__U64_3738 = 1ULL;
    (void)hoisted__U64_3738;
    Bool hoisted__Bool_3739 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3739;
    if (hoisted__Bool_3739) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    U64 hoisted__U64_3740 = 1ULL;
    (void)hoisted__U64_3740;
    Bool hoisted__Bool_3741 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3741;
    if (hoisted__Bool_3741) {
        CaptureBlockData *_clone_payload_BodyValue_27 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_BodyValue_27;
        (void)_clone_payload_BodyValue_27;
        CaptureBlockData *hoisted__CaptureBlockData_3684 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
        (void)hoisted__CaptureBlockData_3684;
        NodeType *hoisted__NodeType_3685 = NodeType_BodyValue(hoisted__CaptureBlockData_3684);
        (void)hoisted__NodeType_3685;
        { NodeType * _ret_val = hoisted__NodeType_3685;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_ListPattern;
    return _r; }
    __builtin_unreachable();
}

U64 NodeType_size(void) {
    U64 hoisted__U64_3742 = 200ULL;
    (void)hoisted__U64_3742;
    return hoisted__U64_3742;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3743 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3743;
    if (hoisted__Bool_3743) {
        return;
    }
    Bool hoisted__Bool_3744 = 0;
    (void)hoisted__Bool_3744;
    NodeType_delete(&self->node_type, hoisted__Bool_3744);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3791 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3791->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3791->children = *_ca; free(_ca); }
    hoisted__Expr_3791->line = line;
    hoisted__Expr_3791->col = col;
    (void)hoisted__Expr_3791;
    return hoisted__Expr_3791;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3800 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3800->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3800->children = *_ca; free(_ca); }
    hoisted__Expr_3800->line = self->line;
    hoisted__Expr_3800->col = self->col;
    (void)hoisted__Expr_3800;
    return hoisted__Expr_3800;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U64 hoisted__U64_3801 = 0ULL;
    (void)hoisted__U64_3801;
    U64 hoisted__U64_3802 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3801); });
    (void)hoisted__U64_3802;
    return hoisted__U64_3802;
    __builtin_unreachable();
}

U64 Expr_size(void) {
    U64 hoisted__U64_3803 = 232ULL;
    (void)hoisted__U64_3803;
    return hoisted__U64_3803;
    __builtin_unreachable();
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4682 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4682->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4682->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4682;
    return hoisted__Map__I64_Str_4682;
    __builtin_unreachable();
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4781 = 0;
    (void)hoisted__Bool_4781;
    Vec__I64_delete(&self->keys, hoisted__Bool_4781);
    Bool hoisted__Bool_4782 = 0;
    (void)hoisted__Bool_4782;
    Vec__Str_delete(&self->values, hoisted__Bool_4782);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4783 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4783->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4783->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4783;
    return hoisted__Map__I64_Str_4783;
    __builtin_unreachable();
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U64 hoisted__U64_4784 = 0ULL;
    (void)hoisted__U64_4784;
    U64 hoisted__U64_4785 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_4784); });
    (void)hoisted__U64_4785;
    return hoisted__U64_4785;
    __builtin_unreachable();
}

U64 Map__I64_Str_size(void) {
    U64 hoisted__U64_4786 = 48ULL;
    (void)hoisted__U64_4786;
    return hoisted__U64_4786;
    __builtin_unreachable();
}

Vec__Bool * Vec__Bool_new(void) {
    U64 hoisted__U64_4787 = 1ULL;
    (void)hoisted__U64_4787;
    void * hoisted__v_4788 = malloc(hoisted__U64_4787);
    (void)hoisted__v_4788;
    U64 hoisted__U64_4789 = 0ULL;
    (void)hoisted__U64_4789;
    I64 hoisted__I64_4790 = 1;
    (void)hoisted__I64_4790;
    Vec__Bool *hoisted__Vec__Bool_4791 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4791->data = hoisted__v_4788;
    hoisted__Vec__Bool_4791->count = hoisted__U64_4789;
    hoisted__Vec__Bool_4791->cap = hoisted__I64_4790;
    (void)hoisted__Vec__Bool_4791;
    return hoisted__Vec__Bool_4791;
    __builtin_unreachable();
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U64 _re_U64_4800 = self->count;
        (void)_re_U64_4800;
        U64 _rc_U64_4800 = 0ULL;
        (void)_rc_U64_4800;
        Bool hoisted__Bool_4811 = ((Bool)(_rc_U64_4800 <= _re_U64_4800));
        (void)hoisted__Bool_4811;
        if (hoisted__Bool_4811) {
            while (1) {
                Bool _wcond_Bool_4801 = ((Bool)(_rc_U64_4800 < _re_U64_4800));
                (void)_wcond_Bool_4801;
                if (_wcond_Bool_4801) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_4800);
                (++_rc_U64_4800);
                U64 hoisted__U64_4802 = 1ULL;
                (void)hoisted__U64_4802;
                U64 hoisted__U64_4803 = ((U64)(i * hoisted__U64_4802));
                (void)hoisted__U64_4803;
                Bool *hoisted__Bool_4804 = ((void *)((U8 *)(self->data) + (hoisted__U64_4803)));
                (void)hoisted__Bool_4804;
                (void)hoisted__Bool_4804;
                Bool hoisted__Bool_4805 = 0;
                (void)hoisted__Bool_4805;
                Bool_delete(hoisted__Bool_4804, hoisted__Bool_4805);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4806 = ((Bool)(_rc_U64_4800 > _re_U64_4800));
                (void)_wcond_Bool_4806;
                if (_wcond_Bool_4806) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_4800);
                (--_rc_U64_4800);
                U64 hoisted__U64_4807 = 1ULL;
                (void)hoisted__U64_4807;
                U64 hoisted__U64_4808 = ((U64)(i * hoisted__U64_4807));
                (void)hoisted__U64_4808;
                Bool *hoisted__Bool_4809 = ((void *)((U8 *)(self->data) + (hoisted__U64_4808)));
                (void)hoisted__Bool_4809;
                (void)hoisted__Bool_4809;
                Bool hoisted__Bool_4810 = 0;
                (void)hoisted__Bool_4810;
                Bool_delete(hoisted__Bool_4809, hoisted__Bool_4810);
            }
        }
    }
    U64 hoisted__U64_4812 = 0ULL;
    (void)hoisted__U64_4812;
    self->count = hoisted__U64_4812;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U64 hoisted__U64_5043 = 1ULL;
    (void)hoisted__U64_5043;
    U64 hoisted__U64_5044 = ((U64)(self->cap * hoisted__U64_5043));
    (void)hoisted__U64_5044;
    U8 *new_data = malloc(hoisted__U64_5044);
    {
        U64 _re_U64_5023 = self->count;
        (void)_re_U64_5023;
        U64 _rc_U64_5023 = 0ULL;
        (void)_rc_U64_5023;
        Bool hoisted__Bool_5042 = ((Bool)(_rc_U64_5023 <= _re_U64_5023));
        (void)hoisted__Bool_5042;
        if (hoisted__Bool_5042) {
            while (1) {
                Bool _wcond_Bool_5024 = ((Bool)(_rc_U64_5023 < _re_U64_5023));
                (void)_wcond_Bool_5024;
                if (_wcond_Bool_5024) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5023);
                (++_rc_U64_5023);
                U64 hoisted__U64_5025 = 1ULL;
                (void)hoisted__U64_5025;
                U64 hoisted__U64_5026 = ((U64)(i * hoisted__U64_5025));
                (void)hoisted__U64_5026;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5026)));
                Bool cloned = (DEREF(src));
                U64 hoisted__U64_5027 = 1ULL;
                (void)hoisted__U64_5027;
                U64 hoisted__U64_5028 = ((U64)(i * hoisted__U64_5027));
                (void)hoisted__U64_5028;
                void *hoisted__v_5029 = ((void *)((U8 *)(new_data) + (hoisted__U64_5028)));
                (void)hoisted__v_5029;
                (void)hoisted__v_5029;
                U64 hoisted__U64_5030 = 1ULL;
                (void)hoisted__U64_5030;
                memcpy(hoisted__v_5029, &cloned, hoisted__U64_5030);
                I32 hoisted__I32_5031 = 0;
                (void)hoisted__I32_5031;
                U64 hoisted__U64_5032 = 1ULL;
                (void)hoisted__U64_5032;
                memset(&cloned, hoisted__I32_5031, hoisted__U64_5032);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5033 = ((Bool)(_rc_U64_5023 > _re_U64_5023));
                (void)_wcond_Bool_5033;
                if (_wcond_Bool_5033) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5023);
                (--_rc_U64_5023);
                U64 hoisted__U64_5034 = 1ULL;
                (void)hoisted__U64_5034;
                U64 hoisted__U64_5035 = ((U64)(i * hoisted__U64_5034));
                (void)hoisted__U64_5035;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5035)));
                Bool cloned = (DEREF(src));
                U64 hoisted__U64_5036 = 1ULL;
                (void)hoisted__U64_5036;
                U64 hoisted__U64_5037 = ((U64)(i * hoisted__U64_5036));
                (void)hoisted__U64_5037;
                void *hoisted__v_5038 = ((void *)((U8 *)(new_data) + (hoisted__U64_5037)));
                (void)hoisted__v_5038;
                (void)hoisted__v_5038;
                U64 hoisted__U64_5039 = 1ULL;
                (void)hoisted__U64_5039;
                memcpy(hoisted__v_5038, &cloned, hoisted__U64_5039);
                I32 hoisted__I32_5040 = 0;
                (void)hoisted__I32_5040;
                U64 hoisted__U64_5041 = 1ULL;
                (void)hoisted__U64_5041;
                memset(&cloned, hoisted__I32_5040, hoisted__U64_5041);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5045 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5045->data = new_data;
    hoisted__Vec__Bool_5045->count = self->count;
    hoisted__Vec__Bool_5045->cap = self->cap;
    (void)hoisted__Vec__Bool_5045;
    return hoisted__Vec__Bool_5045;
    __builtin_unreachable();
}

U64 Vec__Bool_size(void) {
    U64 hoisted__U64_5046 = 24ULL;
    (void)hoisted__U64_5046;
    return hoisted__U64_5046;
    __builtin_unreachable();
}

Vec__I64 * Vec__I64_new(void) {
    U64 hoisted__U64_5047 = 8ULL;
    (void)hoisted__U64_5047;
    void * hoisted__v_5048 = malloc(hoisted__U64_5047);
    (void)hoisted__v_5048;
    U64 hoisted__U64_5049 = 0ULL;
    (void)hoisted__U64_5049;
    I64 hoisted__I64_5050 = 1;
    (void)hoisted__I64_5050;
    Vec__I64 *hoisted__Vec__I64_5051 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5051->data = hoisted__v_5048;
    hoisted__Vec__I64_5051->count = hoisted__U64_5049;
    hoisted__Vec__I64_5051->cap = hoisted__I64_5050;
    (void)hoisted__Vec__I64_5051;
    return hoisted__Vec__I64_5051;
    __builtin_unreachable();
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U64 _re_U64_5060 = self->count;
        (void)_re_U64_5060;
        U64 _rc_U64_5060 = 0ULL;
        (void)_rc_U64_5060;
        Bool hoisted__Bool_5071 = ((Bool)(_rc_U64_5060 <= _re_U64_5060));
        (void)hoisted__Bool_5071;
        if (hoisted__Bool_5071) {
            while (1) {
                Bool _wcond_Bool_5061 = ((Bool)(_rc_U64_5060 < _re_U64_5060));
                (void)_wcond_Bool_5061;
                if (_wcond_Bool_5061) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5060);
                (++_rc_U64_5060);
                U64 hoisted__U64_5062 = 8ULL;
                (void)hoisted__U64_5062;
                U64 hoisted__U64_5063 = ((U64)(i * hoisted__U64_5062));
                (void)hoisted__U64_5063;
                I64 *hoisted__I64_5064 = ((void *)((U8 *)(self->data) + (hoisted__U64_5063)));
                (void)hoisted__I64_5064;
                (void)hoisted__I64_5064;
                Bool hoisted__Bool_5065 = 0;
                (void)hoisted__Bool_5065;
                I64_delete(hoisted__I64_5064, hoisted__Bool_5065);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5066 = ((Bool)(_rc_U64_5060 > _re_U64_5060));
                (void)_wcond_Bool_5066;
                if (_wcond_Bool_5066) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5060);
                (--_rc_U64_5060);
                U64 hoisted__U64_5067 = 8ULL;
                (void)hoisted__U64_5067;
                U64 hoisted__U64_5068 = ((U64)(i * hoisted__U64_5067));
                (void)hoisted__U64_5068;
                I64 *hoisted__I64_5069 = ((void *)((U8 *)(self->data) + (hoisted__U64_5068)));
                (void)hoisted__I64_5069;
                (void)hoisted__I64_5069;
                Bool hoisted__Bool_5070 = 0;
                (void)hoisted__Bool_5070;
                I64_delete(hoisted__I64_5069, hoisted__Bool_5070);
            }
        }
    }
    U64 hoisted__U64_5072 = 0ULL;
    (void)hoisted__U64_5072;
    self->count = hoisted__U64_5072;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U64 hoisted__U64_5303 = 8ULL;
    (void)hoisted__U64_5303;
    U64 hoisted__U64_5304 = ((U64)(self->cap * hoisted__U64_5303));
    (void)hoisted__U64_5304;
    U8 *new_data = malloc(hoisted__U64_5304);
    {
        U64 _re_U64_5283 = self->count;
        (void)_re_U64_5283;
        U64 _rc_U64_5283 = 0ULL;
        (void)_rc_U64_5283;
        Bool hoisted__Bool_5302 = ((Bool)(_rc_U64_5283 <= _re_U64_5283));
        (void)hoisted__Bool_5302;
        if (hoisted__Bool_5302) {
            while (1) {
                Bool _wcond_Bool_5284 = ((Bool)(_rc_U64_5283 < _re_U64_5283));
                (void)_wcond_Bool_5284;
                if (_wcond_Bool_5284) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5283);
                (++_rc_U64_5283);
                U64 hoisted__U64_5285 = 8ULL;
                (void)hoisted__U64_5285;
                U64 hoisted__U64_5286 = ((U64)(i * hoisted__U64_5285));
                (void)hoisted__U64_5286;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5286)));
                I64 cloned = (DEREF(src));
                U64 hoisted__U64_5287 = 8ULL;
                (void)hoisted__U64_5287;
                U64 hoisted__U64_5288 = ((U64)(i * hoisted__U64_5287));
                (void)hoisted__U64_5288;
                void *hoisted__v_5289 = ((void *)((U8 *)(new_data) + (hoisted__U64_5288)));
                (void)hoisted__v_5289;
                (void)hoisted__v_5289;
                U64 hoisted__U64_5290 = 8ULL;
                (void)hoisted__U64_5290;
                memcpy(hoisted__v_5289, &cloned, hoisted__U64_5290);
                I32 hoisted__I32_5291 = 0;
                (void)hoisted__I32_5291;
                U64 hoisted__U64_5292 = 8ULL;
                (void)hoisted__U64_5292;
                memset(&cloned, hoisted__I32_5291, hoisted__U64_5292);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5293 = ((Bool)(_rc_U64_5283 > _re_U64_5283));
                (void)_wcond_Bool_5293;
                if (_wcond_Bool_5293) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5283);
                (--_rc_U64_5283);
                U64 hoisted__U64_5294 = 8ULL;
                (void)hoisted__U64_5294;
                U64 hoisted__U64_5295 = ((U64)(i * hoisted__U64_5294));
                (void)hoisted__U64_5295;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5295)));
                I64 cloned = (DEREF(src));
                U64 hoisted__U64_5296 = 8ULL;
                (void)hoisted__U64_5296;
                U64 hoisted__U64_5297 = ((U64)(i * hoisted__U64_5296));
                (void)hoisted__U64_5297;
                void *hoisted__v_5298 = ((void *)((U8 *)(new_data) + (hoisted__U64_5297)));
                (void)hoisted__v_5298;
                (void)hoisted__v_5298;
                U64 hoisted__U64_5299 = 8ULL;
                (void)hoisted__U64_5299;
                memcpy(hoisted__v_5298, &cloned, hoisted__U64_5299);
                I32 hoisted__I32_5300 = 0;
                (void)hoisted__I32_5300;
                U64 hoisted__U64_5301 = 8ULL;
                (void)hoisted__U64_5301;
                memset(&cloned, hoisted__I32_5300, hoisted__U64_5301);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5305 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5305->data = new_data;
    hoisted__Vec__I64_5305->count = self->count;
    hoisted__Vec__I64_5305->cap = self->cap;
    (void)hoisted__Vec__I64_5305;
    return hoisted__Vec__I64_5305;
    __builtin_unreachable();
}

U64 Vec__I64_size(void) {
    U64 hoisted__U64_5306 = 24ULL;
    (void)hoisted__U64_5306;
    return hoisted__U64_5306;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U64 hoisted__U64_5567 = 144ULL;
    (void)hoisted__U64_5567;
    void * hoisted__v_5568 = malloc(hoisted__U64_5567);
    (void)hoisted__v_5568;
    U64 hoisted__U64_5569 = 0ULL;
    (void)hoisted__U64_5569;
    I64 hoisted__I64_5570 = 1;
    (void)hoisted__I64_5570;
    Vec__Declaration *hoisted__Vec__Declaration_5571 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5571->data = hoisted__v_5568;
    hoisted__Vec__Declaration_5571->count = hoisted__U64_5569;
    hoisted__Vec__Declaration_5571->cap = hoisted__I64_5570;
    (void)hoisted__Vec__Declaration_5571;
    return hoisted__Vec__Declaration_5571;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U64 _re_U64_5580 = self->count;
        (void)_re_U64_5580;
        U64 _rc_U64_5580 = 0ULL;
        (void)_rc_U64_5580;
        Bool hoisted__Bool_5591 = ((Bool)(_rc_U64_5580 <= _re_U64_5580));
        (void)hoisted__Bool_5591;
        if (hoisted__Bool_5591) {
            while (1) {
                Bool _wcond_Bool_5581 = ((Bool)(_rc_U64_5580 < _re_U64_5580));
                (void)_wcond_Bool_5581;
                if (_wcond_Bool_5581) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5580);
                (++_rc_U64_5580);
                U64 hoisted__U64_5582 = 144ULL;
                (void)hoisted__U64_5582;
                U64 hoisted__U64_5583 = ((U64)(i * hoisted__U64_5582));
                (void)hoisted__U64_5583;
                Declaration *hoisted__Declaration_5584 = ((void *)((U8 *)(self->data) + (hoisted__U64_5583)));
                (void)hoisted__Declaration_5584;
                (void)hoisted__Declaration_5584;
                Bool hoisted__Bool_5585 = 0;
                (void)hoisted__Bool_5585;
                Declaration_delete(hoisted__Declaration_5584, hoisted__Bool_5585);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5586 = ((Bool)(_rc_U64_5580 > _re_U64_5580));
                (void)_wcond_Bool_5586;
                if (_wcond_Bool_5586) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5580);
                (--_rc_U64_5580);
                U64 hoisted__U64_5587 = 144ULL;
                (void)hoisted__U64_5587;
                U64 hoisted__U64_5588 = ((U64)(i * hoisted__U64_5587));
                (void)hoisted__U64_5588;
                Declaration *hoisted__Declaration_5589 = ((void *)((U8 *)(self->data) + (hoisted__U64_5588)));
                (void)hoisted__Declaration_5589;
                (void)hoisted__Declaration_5589;
                Bool hoisted__Bool_5590 = 0;
                (void)hoisted__Bool_5590;
                Declaration_delete(hoisted__Declaration_5589, hoisted__Bool_5590);
            }
        }
    }
    U64 hoisted__U64_5592 = 0ULL;
    (void)hoisted__U64_5592;
    self->count = hoisted__U64_5592;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U64 hoisted__U64_5823 = 144ULL;
    (void)hoisted__U64_5823;
    U64 hoisted__U64_5824 = ((U64)(self->cap * hoisted__U64_5823));
    (void)hoisted__U64_5824;
    U8 *new_data = malloc(hoisted__U64_5824);
    {
        U64 _re_U64_5803 = self->count;
        (void)_re_U64_5803;
        U64 _rc_U64_5803 = 0ULL;
        (void)_rc_U64_5803;
        Bool hoisted__Bool_5822 = ((Bool)(_rc_U64_5803 <= _re_U64_5803));
        (void)hoisted__Bool_5822;
        if (hoisted__Bool_5822) {
            while (1) {
                Bool _wcond_Bool_5804 = ((Bool)(_rc_U64_5803 < _re_U64_5803));
                (void)_wcond_Bool_5804;
                if (_wcond_Bool_5804) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5803);
                (++_rc_U64_5803);
                U64 hoisted__U64_5805 = 144ULL;
                (void)hoisted__U64_5805;
                U64 hoisted__U64_5806 = ((U64)(i * hoisted__U64_5805));
                (void)hoisted__U64_5806;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5806)));
                Declaration *cloned = Declaration_clone(src);
                U64 hoisted__U64_5807 = 144ULL;
                (void)hoisted__U64_5807;
                U64 hoisted__U64_5808 = ((U64)(i * hoisted__U64_5807));
                (void)hoisted__U64_5808;
                void *hoisted__v_5809 = ((void *)((U8 *)(new_data) + (hoisted__U64_5808)));
                (void)hoisted__v_5809;
                (void)hoisted__v_5809;
                U64 hoisted__U64_5810 = 144ULL;
                (void)hoisted__U64_5810;
                memcpy(hoisted__v_5809, cloned, hoisted__U64_5810);
                I32 hoisted__I32_5811 = 0;
                (void)hoisted__I32_5811;
                U64 hoisted__U64_5812 = 144ULL;
                (void)hoisted__U64_5812;
                memset(cloned, hoisted__I32_5811, hoisted__U64_5812);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5813 = ((Bool)(_rc_U64_5803 > _re_U64_5803));
                (void)_wcond_Bool_5813;
                if (_wcond_Bool_5813) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5803);
                (--_rc_U64_5803);
                U64 hoisted__U64_5814 = 144ULL;
                (void)hoisted__U64_5814;
                U64 hoisted__U64_5815 = ((U64)(i * hoisted__U64_5814));
                (void)hoisted__U64_5815;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5815)));
                Declaration *cloned = Declaration_clone(src);
                U64 hoisted__U64_5816 = 144ULL;
                (void)hoisted__U64_5816;
                U64 hoisted__U64_5817 = ((U64)(i * hoisted__U64_5816));
                (void)hoisted__U64_5817;
                void *hoisted__v_5818 = ((void *)((U8 *)(new_data) + (hoisted__U64_5817)));
                (void)hoisted__v_5818;
                (void)hoisted__v_5818;
                U64 hoisted__U64_5819 = 144ULL;
                (void)hoisted__U64_5819;
                memcpy(hoisted__v_5818, cloned, hoisted__U64_5819);
                I32 hoisted__I32_5820 = 0;
                (void)hoisted__I32_5820;
                U64 hoisted__U64_5821 = 144ULL;
                (void)hoisted__U64_5821;
                memset(cloned, hoisted__I32_5820, hoisted__U64_5821);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5825 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5825->data = new_data;
    hoisted__Vec__Declaration_5825->count = self->count;
    hoisted__Vec__Declaration_5825->cap = self->cap;
    (void)hoisted__Vec__Declaration_5825;
    return hoisted__Vec__Declaration_5825;
    __builtin_unreachable();
}

U64 Vec__Declaration_size(void) {
    U64 hoisted__U64_5826 = 24ULL;
    (void)hoisted__U64_5826;
    return hoisted__U64_5826;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U64 hoisted__U64_5827 = 232ULL;
    (void)hoisted__U64_5827;
    void * hoisted__v_5828 = malloc(hoisted__U64_5827);
    (void)hoisted__v_5828;
    U64 hoisted__U64_5829 = 0ULL;
    (void)hoisted__U64_5829;
    I64 hoisted__I64_5830 = 1;
    (void)hoisted__I64_5830;
    Vec__Expr *hoisted__Vec__Expr_5831 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5831->data = hoisted__v_5828;
    hoisted__Vec__Expr_5831->count = hoisted__U64_5829;
    hoisted__Vec__Expr_5831->cap = hoisted__I64_5830;
    (void)hoisted__Vec__Expr_5831;
    return hoisted__Vec__Expr_5831;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U64 _re_U64_5840 = self->count;
        (void)_re_U64_5840;
        U64 _rc_U64_5840 = 0ULL;
        (void)_rc_U64_5840;
        Bool hoisted__Bool_5851 = ((Bool)(_rc_U64_5840 <= _re_U64_5840));
        (void)hoisted__Bool_5851;
        if (hoisted__Bool_5851) {
            while (1) {
                Bool _wcond_Bool_5841 = ((Bool)(_rc_U64_5840 < _re_U64_5840));
                (void)_wcond_Bool_5841;
                if (_wcond_Bool_5841) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5840);
                (++_rc_U64_5840);
                U64 hoisted__U64_5842 = 232ULL;
                (void)hoisted__U64_5842;
                U64 hoisted__U64_5843 = ((U64)(i * hoisted__U64_5842));
                (void)hoisted__U64_5843;
                Expr *hoisted__Expr_5844 = ((void *)((U8 *)(self->data) + (hoisted__U64_5843)));
                (void)hoisted__Expr_5844;
                (void)hoisted__Expr_5844;
                Bool hoisted__Bool_5845 = 0;
                (void)hoisted__Bool_5845;
                Expr_delete(hoisted__Expr_5844, hoisted__Bool_5845);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5846 = ((Bool)(_rc_U64_5840 > _re_U64_5840));
                (void)_wcond_Bool_5846;
                if (_wcond_Bool_5846) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5840);
                (--_rc_U64_5840);
                U64 hoisted__U64_5847 = 232ULL;
                (void)hoisted__U64_5847;
                U64 hoisted__U64_5848 = ((U64)(i * hoisted__U64_5847));
                (void)hoisted__U64_5848;
                Expr *hoisted__Expr_5849 = ((void *)((U8 *)(self->data) + (hoisted__U64_5848)));
                (void)hoisted__Expr_5849;
                (void)hoisted__Expr_5849;
                Bool hoisted__Bool_5850 = 0;
                (void)hoisted__Bool_5850;
                Expr_delete(hoisted__Expr_5849, hoisted__Bool_5850);
            }
        }
    }
    U64 hoisted__U64_5852 = 0ULL;
    (void)hoisted__U64_5852;
    self->count = hoisted__U64_5852;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U64 hoisted__U64_6083 = 232ULL;
    (void)hoisted__U64_6083;
    U64 hoisted__U64_6084 = ((U64)(self->cap * hoisted__U64_6083));
    (void)hoisted__U64_6084;
    U8 *new_data = malloc(hoisted__U64_6084);
    {
        U64 _re_U64_6063 = self->count;
        (void)_re_U64_6063;
        U64 _rc_U64_6063 = 0ULL;
        (void)_rc_U64_6063;
        Bool hoisted__Bool_6082 = ((Bool)(_rc_U64_6063 <= _re_U64_6063));
        (void)hoisted__Bool_6082;
        if (hoisted__Bool_6082) {
            while (1) {
                Bool _wcond_Bool_6064 = ((Bool)(_rc_U64_6063 < _re_U64_6063));
                (void)_wcond_Bool_6064;
                if (_wcond_Bool_6064) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6063);
                (++_rc_U64_6063);
                U64 hoisted__U64_6065 = 232ULL;
                (void)hoisted__U64_6065;
                U64 hoisted__U64_6066 = ((U64)(i * hoisted__U64_6065));
                (void)hoisted__U64_6066;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6066)));
                Expr *cloned = Expr_clone(src);
                U64 hoisted__U64_6067 = 232ULL;
                (void)hoisted__U64_6067;
                U64 hoisted__U64_6068 = ((U64)(i * hoisted__U64_6067));
                (void)hoisted__U64_6068;
                void *hoisted__v_6069 = ((void *)((U8 *)(new_data) + (hoisted__U64_6068)));
                (void)hoisted__v_6069;
                (void)hoisted__v_6069;
                U64 hoisted__U64_6070 = 232ULL;
                (void)hoisted__U64_6070;
                memcpy(hoisted__v_6069, cloned, hoisted__U64_6070);
                I32 hoisted__I32_6071 = 0;
                (void)hoisted__I32_6071;
                U64 hoisted__U64_6072 = 232ULL;
                (void)hoisted__U64_6072;
                memset(cloned, hoisted__I32_6071, hoisted__U64_6072);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6073 = ((Bool)(_rc_U64_6063 > _re_U64_6063));
                (void)_wcond_Bool_6073;
                if (_wcond_Bool_6073) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6063);
                (--_rc_U64_6063);
                U64 hoisted__U64_6074 = 232ULL;
                (void)hoisted__U64_6074;
                U64 hoisted__U64_6075 = ((U64)(i * hoisted__U64_6074));
                (void)hoisted__U64_6075;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6075)));
                Expr *cloned = Expr_clone(src);
                U64 hoisted__U64_6076 = 232ULL;
                (void)hoisted__U64_6076;
                U64 hoisted__U64_6077 = ((U64)(i * hoisted__U64_6076));
                (void)hoisted__U64_6077;
                void *hoisted__v_6078 = ((void *)((U8 *)(new_data) + (hoisted__U64_6077)));
                (void)hoisted__v_6078;
                (void)hoisted__v_6078;
                U64 hoisted__U64_6079 = 232ULL;
                (void)hoisted__U64_6079;
                memcpy(hoisted__v_6078, cloned, hoisted__U64_6079);
                I32 hoisted__I32_6080 = 0;
                (void)hoisted__I32_6080;
                U64 hoisted__U64_6081 = 232ULL;
                (void)hoisted__U64_6081;
                memset(cloned, hoisted__I32_6080, hoisted__U64_6081);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6085 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6085->data = new_data;
    hoisted__Vec__Expr_6085->count = self->count;
    hoisted__Vec__Expr_6085->cap = self->cap;
    (void)hoisted__Vec__Expr_6085;
    return hoisted__Vec__Expr_6085;
    __builtin_unreachable();
}

U64 Vec__Expr_size(void) {
    U64 hoisted__U64_6086 = 24ULL;
    (void)hoisted__U64_6086;
    return hoisted__U64_6086;
    __builtin_unreachable();
}

void panic(Array__Str * parts, Str * loc) {
    U64 hoisted__U64_7072 = 3ULL;
    (void)hoisted__U64_7072;
    Array__Str *_va_Array_201 = Array__Str_new(hoisted__U64_7072);
    (void)_va_Array_201;
    I64 _va_Array_201_ek = 0;
    (void)_va_Array_201_ek;
    OutOfBounds *_va_Array_201_eo = malloc(sizeof(OutOfBounds));
    _va_Array_201_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_201_eo;
    U64 hoisted__U64_7073 = 0ULL;
    (void)hoisted__U64_7073;
    Str *hoisted__Str_7074 = Str_clone(loc);
    (void)hoisted__Str_7074;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    Array__Str_set(_va_Array_201, hoisted__U64_7073, hoisted__Str_7074, &_va_Array_201_ek, _va_Array_201_eo, &_til_str_lit_147);
    Str_delete(&_til_str_lit_147, (Bool){0});
    U64 hoisted__U64_7076 = 1ULL;
    (void)hoisted__U64_7076;
    (void)_til_str_lit_148;
    (void)_til_str_lit_148;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    Array__Str_set(_va_Array_201, hoisted__U64_7076, &_til_str_lit_148, &_va_Array_201_ek, _va_Array_201_eo, &_til_str_lit_147);
    Str_delete(&_til_str_lit_147, (Bool){0});
    Array__Str *hoisted__Array__Str_7079 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7079;
    U64 hoisted__U64_7080 = 2ULL;
    (void)hoisted__U64_7080;
    Str *hoisted__Str_7081 = format(hoisted__Array__Str_7079);
    (void)hoisted__Str_7081;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    Array__Str_set(_va_Array_201, hoisted__U64_7080, hoisted__Str_7081, &_va_Array_201_ek, _va_Array_201_eo, &_til_str_lit_147);
    OutOfBounds_delete(_va_Array_201_eo, 1);
    Str_delete(&_til_str_lit_147, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_201);
    I64 hoisted__I64_7083 = 1;
    (void)hoisted__I64_7083;
    exit(hoisted__I64_7083);
}

void UNREACHABLE(Str * loc) {
    U64 hoisted__U64_7092 = 1ULL;
    (void)hoisted__U64_7092;
    Array__Str *_va_Array_203 = Array__Str_new(hoisted__U64_7092);
    (void)_va_Array_203;
    I64 _va_Array_203_ek = 0;
    (void)_va_Array_203_ek;
    OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
    _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_203_eo;
    U64 hoisted__U64_7093 = 0ULL;
    (void)hoisted__U64_7093;
    (void)_til_str_lit_149;
    (void)_til_str_lit_149;
    (void)_til_str_lit_150;
    (void)_til_str_lit_150;
    Array__Str_set(_va_Array_203, hoisted__U64_7093, &_til_str_lit_149, &_va_Array_203_ek, _va_Array_203_eo, &_til_str_lit_150);
    OutOfBounds_delete(_va_Array_203_eo, 1);
    Str_delete(&_til_str_lit_150, (Bool){0});
    panic(_va_Array_203, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7100 = ((Bool)(!(cond)));
    (void)hoisted__Bool_7100;
    if (hoisted__Bool_7100) {
        U64 hoisted__U64_7096 = 1ULL;
        (void)hoisted__U64_7096;
        Array__Str *_va_Array_204 = Array__Str_new(hoisted__U64_7096);
        (void)_va_Array_204;
        I64 _va_Array_204_ek = 0;
        (void)_va_Array_204_ek;
        OutOfBounds *_va_Array_204_eo = malloc(sizeof(OutOfBounds));
        _va_Array_204_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_204_eo;
        U64 hoisted__U64_7097 = 0ULL;
        (void)hoisted__U64_7097;
        (void)_til_str_lit_151;
        (void)_til_str_lit_151;
        (void)_til_str_lit_152;
        (void)_til_str_lit_152;
        Array__Str_set(_va_Array_204, hoisted__U64_7097, &_til_str_lit_151, &_va_Array_204_ek, _va_Array_204_eo, &_til_str_lit_152);
        OutOfBounds_delete(_va_Array_204_eo, 1);
        Str_delete(&_til_str_lit_152, (Bool){0});
        panic(_va_Array_204, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7110 = parts;
        (void)_fc_Array__Str_7110;
        (void)_fc_Array__Str_7110;
        U64 _fi_USize_7110 = 0ULL;
        (void)_fi_USize_7110;
        while (1) {
            U64 hoisted__U64_7112 = (_fc_Array__Str_7110->cap);
            (void)hoisted__U64_7112;
            Bool _wcond_Bool_7111 = ((Bool)(_fi_USize_7110 < hoisted__U64_7112));
            (void)_wcond_Bool_7111;
            if (_wcond_Bool_7111) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_7110->data) + (((U64)(_fi_USize_7110 * 24ULL))))));
            U64 hoisted__U64_7113 = 1ULL;
            (void)hoisted__U64_7113;
            U64 hoisted__U64_7114 = ((U64)(_fi_USize_7110 + hoisted__U64_7113));
            (void)hoisted__U64_7114;
            _fi_USize_7110 = hoisted__U64_7114;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void swap_bytes(void * a, void * b, U64 size) {
    U8 *tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7127 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7127;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7127;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U64 hoisted__U64_7128 = 0ULL;
    (void)hoisted__U64_7128;
    U64 hoisted__U64_7129 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_7128); });
    (void)hoisted__U64_7129;
    return hoisted__U64_7129;
    __builtin_unreachable();
}

U64 Range_size(void) {
    U64 hoisted__U64_7160 = 16ULL;
    (void)hoisted__U64_7160;
    return hoisted__U64_7160;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7176 = 3;
    (void)hoisted__I64_7176;
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    assert_eq__I64(result, hoisted__I64_7176, &_til_str_lit_155);
    Str_delete(&_til_str_lit_155, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7184 = 15;
    (void)hoisted__I64_7184;
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    assert_eq__I64(result, hoisted__I64_7184, &_til_str_lit_156);
    Str_delete(&_til_str_lit_156, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7192 = 26;
    (void)hoisted__I64_7192;
    (void)_til_str_lit_157;
    (void)_til_str_lit_157;
    assert_eq__I64(result, hoisted__I64_7192, &_til_str_lit_157);
    Str_delete(&_til_str_lit_157, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    assert_eq__Str(&result, &_til_str_lit_158, &_til_str_lit_159);
    Str_delete(&_til_str_lit_158, (Bool){0});
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    assert_eq__Str(&r, &_til_str_lit_158, &_til_str_lit_160);
    Str_delete(&_til_str_lit_158, (Bool){0});
    Str_delete(&_til_str_lit_160, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    assert_eq__Str(&r2, &_til_str_lit_161, &_til_str_lit_162);
    Str_delete(&_til_str_lit_161, (Bool){0});
    Str_delete(&_til_str_lit_162, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    assert_eq__Str(&d, &_til_str_lit_163, &_til_str_lit_164);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_163, (Bool){0});
    Str_delete(&_til_str_lit_164, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_165;
    (void)_til_str_lit_165;
    (void)_til_str_lit_166;
    (void)_til_str_lit_166;
    assert_eq__Str(&d2, &_til_str_lit_165, &_til_str_lit_166);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_165, (Bool){0});
    Str_delete(&_til_str_lit_166, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7279 = 106;
    (void)hoisted__I64_7279;
    (void)_til_str_lit_167;
    (void)_til_str_lit_167;
    assert_eq__I64(d3, hoisted__I64_7279, &_til_str_lit_167);
    Str_delete(&_til_str_lit_167, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_171);
    Str_delete(&_til_str_lit_171, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_7882 = 8;
    (void)hoisted__I64_7882;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    assert_eq__I64(result, hoisted__I64_7882, &_til_str_lit_172);
    Str_delete(&_til_str_lit_172, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7886 = 1;
    (void)hoisted__Bool_7886;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    assert(hoisted__Bool_7886, &_til_str_lit_173);
    Str_delete(&_til_str_lit_173, (Bool){0});
    Bool hoisted__Bool_7890 = 1;
    (void)hoisted__Bool_7890;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    assert(hoisted__Bool_7890, &_til_str_lit_174);
    Str_delete(&_til_str_lit_174, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    (void)_til_str_lit_176;
    (void)_til_str_lit_176;
    assert_eq__Str(&_til_str_lit_175, &_til_str_lit_175, &_til_str_lit_176);
    Str_delete(&_til_str_lit_175, (Bool){0});
    Str_delete(&_til_str_lit_175, (Bool){0});
    Str_delete(&_til_str_lit_176, (Bool){0});
    (void)_til_str_lit_177;
    (void)_til_str_lit_177;
    (void)_til_str_lit_177;
    (void)_til_str_lit_177;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    assert_eq__Str(&_til_str_lit_177, &_til_str_lit_177, &_til_str_lit_178);
    Str_delete(&_til_str_lit_177, (Bool){0});
    Str_delete(&_til_str_lit_177, (Bool){0});
    Str_delete(&_til_str_lit_178, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7908 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7908;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7908;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U64 hoisted__U64_7909 = 0ULL;
    (void)hoisted__U64_7909;
    U64 hoisted__U64_7910 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_7909); });
    (void)hoisted__U64_7910;
    return hoisted__U64_7910;
    __builtin_unreachable();
}

U64 CfVec2_size(void) {
    U64 hoisted__U64_7941 = 16ULL;
    (void)hoisted__U64_7941;
    return hoisted__U64_7941;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_7942 = 42;
    (void)hoisted__I64_7942;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__I64(v.x, hoisted__I64_7942, &_til_str_lit_181);
    Str_delete(&_til_str_lit_181, (Bool){0});
    I64 hoisted__I64_7944 = 99;
    (void)hoisted__I64_7944;
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    assert_eq__I64(v.y, hoisted__I64_7944, &_til_str_lit_182);
    Str_delete(&_til_str_lit_182, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7948 = 10;
    (void)hoisted__I64_7948;
    (void)_til_str_lit_183;
    (void)_til_str_lit_183;
    assert_eq__I64(p.x, hoisted__I64_7948, &_til_str_lit_183);
    Str_delete(&_til_str_lit_183, (Bool){0});
    I64 hoisted__I64_7950 = 20;
    (void)hoisted__I64_7950;
    (void)_til_str_lit_184;
    (void)_til_str_lit_184;
    assert_eq__I64(p.y, hoisted__I64_7950, &_til_str_lit_184);
    Str_delete(&_til_str_lit_184, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7957 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7957;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7957;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U64 hoisted__U64_7958 = 0ULL;
    (void)hoisted__U64_7958;
    U64 hoisted__U64_7959 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_7958); });
    (void)hoisted__U64_7959;
    return hoisted__U64_7959;
    __builtin_unreachable();
}

U64 CfRect_size(void) {
    U64 hoisted__U64_7990 = 32ULL;
    (void)hoisted__U64_7990;
    return hoisted__U64_7990;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_7991 = 5;
    (void)hoisted__I64_7991;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(r.top_left.x, hoisted__I64_7991, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    I64 hoisted__I64_7993 = 10;
    (void)hoisted__I64_7993;
    (void)_til_str_lit_189;
    (void)_til_str_lit_189;
    assert_eq__I64(r.top_left.y, hoisted__I64_7993, &_til_str_lit_189);
    Str_delete(&_til_str_lit_189, (Bool){0});
    I64 hoisted__I64_7995 = 100;
    (void)hoisted__I64_7995;
    (void)_til_str_lit_190;
    (void)_til_str_lit_190;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7995, &_til_str_lit_190);
    Str_delete(&_til_str_lit_190, (Bool){0});
    I64 hoisted__I64_7997 = 200;
    (void)hoisted__I64_7997;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7997, &_til_str_lit_191);
    Str_delete(&_til_str_lit_191, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8000 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8000;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8000;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U64 hoisted__U64_8001 = 0ULL;
    (void)hoisted__U64_8001;
    U64 hoisted__U64_8002 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8001); });
    (void)hoisted__U64_8002;
    return hoisted__U64_8002;
    __builtin_unreachable();
}

U64 CfVec3f_size(void) {
    U64 hoisted__U64_8045 = 12ULL;
    (void)hoisted__U64_8045;
    return hoisted__U64_8045;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8049 = F32_to_str(v.x);
    (void)hoisted__Str_8049;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    assert_eq__Str(hoisted__Str_8049, &_til_str_lit_193, &_til_str_lit_194);
    Str_delete(hoisted__Str_8049, 1);
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str_delete(&_til_str_lit_194, (Bool){0});
    Str *hoisted__Str_8052 = F32_to_str(v.y);
    (void)hoisted__Str_8052;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    (void)_til_str_lit_196;
    (void)_til_str_lit_196;
    assert_eq__Str(hoisted__Str_8052, &_til_str_lit_195, &_til_str_lit_196);
    Str_delete(hoisted__Str_8052, 1);
    Str_delete(&_til_str_lit_195, (Bool){0});
    Str_delete(&_til_str_lit_196, (Bool){0});
    Str *hoisted__Str_8055 = F32_to_str(v.z);
    (void)hoisted__Str_8055;
    (void)_til_str_lit_197;
    (void)_til_str_lit_197;
    (void)_til_str_lit_198;
    (void)_til_str_lit_198;
    assert_eq__Str(hoisted__Str_8055, &_til_str_lit_197, &_til_str_lit_198);
    Str_delete(hoisted__Str_8055, 1);
    Str_delete(&_til_str_lit_197, (Bool){0});
    Str_delete(&_til_str_lit_198, (Bool){0});
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
    U64 hoisted__U64_8064 = 1ULL;
    (void)hoisted__U64_8064;
    Bool hoisted__Bool_8065 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_8065;
    if (hoisted__Bool_8065) {
        U64 hoisted__U64_8058 = 1ULL;
        (void)hoisted__U64_8058;
        Bool hoisted__Bool_8059 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_8059;
        { Bool _ret_val = hoisted__Bool_8059;
                return _ret_val; }
    }
    U64 hoisted__U64_8066 = 1ULL;
    (void)hoisted__U64_8066;
    Bool hoisted__Bool_8067 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_8067;
    if (hoisted__Bool_8067) {
        U64 hoisted__U64_8060 = 1ULL;
        (void)hoisted__U64_8060;
        Bool hoisted__Bool_8061 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_8061;
        { Bool _ret_val = hoisted__Bool_8061;
                return _ret_val; }
    }
    U64 hoisted__U64_8068 = 1ULL;
    (void)hoisted__U64_8068;
    Bool hoisted__Bool_8069 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_8069;
    if (hoisted__Bool_8069) {
        U64 hoisted__U64_8062 = 1ULL;
        (void)hoisted__U64_8062;
        Bool hoisted__Bool_8063 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_8063;
        { Bool _ret_val = hoisted__Bool_8063;
                return _ret_val; }
    }
    Bool hoisted__Bool_8070 = 0;
    (void)hoisted__Bool_8070;
    return hoisted__Bool_8070;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8078 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8078;
    if (hoisted__Bool_8078) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8079 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8079;
    if (hoisted__Bool_8079) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8080 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8080;
    if (hoisted__Bool_8080) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8081 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8081;
    UNREACHABLE(&hoisted__Str_8081);
    Str_delete(&hoisted__Str_8081, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

U64 Color_size(void) {
    U64 hoisted__U64_8082 = 1ULL;
    (void)hoisted__U64_8082;
    return hoisted__U64_8082;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8083 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8083;
    (void)_til_str_lit_202;
    (void)_til_str_lit_202;
    assert(hoisted__Bool_8083, &_til_str_lit_202);
    Str_delete(&_til_str_lit_202, (Bool){0});
    Bool hoisted__Bool_8085 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8085;
    Bool hoisted__Bool_8086 = ((Bool)(!(hoisted__Bool_8085)));
    (void)hoisted__Bool_8086;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert(hoisted__Bool_8086, &_til_str_lit_203);
    Str_delete(&_til_str_lit_203, (Bool){0});
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
    U64 hoisted__U64_8111 = 1ULL;
    (void)hoisted__U64_8111;
    Bool hoisted__Bool_8112 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8112;
    if (hoisted__Bool_8112) {
        I64 *hoisted__I64_8107 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__I64_8107;
        (void)hoisted__I64_8107;
        Bool hoisted__Bool_8108 = 0;
        (void)hoisted__Bool_8108;
        I64_delete(hoisted__I64_8107, hoisted__Bool_8108);
    }
    U64 hoisted__U64_8113 = 1ULL;
    (void)hoisted__U64_8113;
    Bool hoisted__Bool_8114 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8114;
    if (hoisted__Bool_8114) {
        Str *hoisted__Str_8109 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_8109;
        (void)hoisted__Str_8109;
        Bool hoisted__Bool_8110 = 0;
        (void)hoisted__Bool_8110;
        Str_delete(hoisted__Str_8109, hoisted__Bool_8110);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U64 hoisted__U64_8148 = 1ULL;
    (void)hoisted__U64_8148;
    Bool hoisted__Bool_8149 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8149;
    if (hoisted__Bool_8149) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8145 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8145;
        { Token * _ret_val = hoisted__Token_8145;
                return _ret_val; }
    }
    U64 hoisted__U64_8150 = 1ULL;
    (void)hoisted__U64_8150;
    Bool hoisted__Bool_8151 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8151;
    if (hoisted__Bool_8151) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8146 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8146;
        Token *hoisted__Token_8147 = Token_Name(hoisted__Str_8146);
        (void)hoisted__Token_8147;
        { Token * _ret_val = hoisted__Token_8147;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

U64 Token_size(void) {
    U64 hoisted__U64_8152 = 32ULL;
    (void)hoisted__U64_8152;
    return hoisted__U64_8152;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8154 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8154;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_8154, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
    Bool hoisted__Bool_8156 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_8156;
    Bool hoisted__Bool_8157 = ((Bool)(!(hoisted__Bool_8156)));
    (void)hoisted__Bool_8157;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_8157, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8159 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8159;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_8159, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Bool hoisted__Bool_8161 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8161;
    Bool hoisted__Bool_8162 = ((Bool)(!(hoisted__Bool_8161)));
    (void)hoisted__Bool_8162;
    (void)_til_str_lit_209;
    (void)_til_str_lit_209;
    assert(hoisted__Bool_8162, &_til_str_lit_209);
    Str_delete(&_til_str_lit_209, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8166 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8166;
    (void)_til_str_lit_210;
    (void)_til_str_lit_210;
    assert(hoisted__Bool_8166, &_til_str_lit_210);
    Str_delete(&_til_str_lit_210, (Bool){0});
    Bool hoisted__Bool_8168 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_8168;
    Bool hoisted__Bool_8169 = ((Bool)(!(hoisted__Bool_8168)));
    (void)hoisted__Bool_8169;
    (void)_til_str_lit_211;
    (void)_til_str_lit_211;
    assert(hoisted__Bool_8169, &_til_str_lit_211);
    Str_delete(&_til_str_lit_211, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8286 = ((Bool)(a != b));
    (void)hoisted__Bool_8286;
    if (hoisted__Bool_8286) {
        U64 hoisted__U64_8270 = 5ULL;
        (void)hoisted__U64_8270;
        Array__Str *_va_Array_243 = Array__Str_new(hoisted__U64_8270);
        (void)_va_Array_243;
        I64 _va_Array_243_ek = 0;
        (void)_va_Array_243_ek;
        OutOfBounds *_va_Array_243_eo = malloc(sizeof(OutOfBounds));
        _va_Array_243_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_243_eo;
        U64 hoisted__U64_8271 = 0ULL;
        (void)hoisted__U64_8271;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_243, hoisted__U64_8271, &_til_str_lit_212, &_va_Array_243_ek, _va_Array_243_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8274 = 1ULL;
        (void)hoisted__U64_8274;
        Str *hoisted__Str_8275 = I64_to_str(a);
        (void)hoisted__Str_8275;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_243, hoisted__U64_8274, hoisted__Str_8275, &_va_Array_243_ek, _va_Array_243_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8277 = 2ULL;
        (void)hoisted__U64_8277;
        (void)_til_str_lit_214;
        (void)_til_str_lit_214;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_243, hoisted__U64_8277, &_til_str_lit_214, &_va_Array_243_ek, _va_Array_243_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8280 = 3ULL;
        (void)hoisted__U64_8280;
        Str *hoisted__Str_8281 = I64_to_str(b);
        (void)hoisted__Str_8281;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_243, hoisted__U64_8280, hoisted__Str_8281, &_va_Array_243_ek, _va_Array_243_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8283 = 4ULL;
        (void)hoisted__U64_8283;
        (void)_til_str_lit_215;
        (void)_til_str_lit_215;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_243, hoisted__U64_8283, &_til_str_lit_215, &_va_Array_243_ek, _va_Array_243_eo, &_til_str_lit_213);
        OutOfBounds_delete(_va_Array_243_eo, 1);
        Str_delete(&_til_str_lit_213, (Bool){0});
        panic(_va_Array_243, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8303 = Str_neq(a, b);
    (void)hoisted__Bool_8303;
    if (hoisted__Bool_8303) {
        U64 hoisted__U64_8287 = 5ULL;
        (void)hoisted__U64_8287;
        Array__Str *_va_Array_244 = Array__Str_new(hoisted__U64_8287);
        (void)_va_Array_244;
        I64 _va_Array_244_ek = 0;
        (void)_va_Array_244_ek;
        OutOfBounds *_va_Array_244_eo = malloc(sizeof(OutOfBounds));
        _va_Array_244_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_244_eo;
        U64 hoisted__U64_8288 = 0ULL;
        (void)hoisted__U64_8288;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_244, hoisted__U64_8288, &_til_str_lit_212, &_va_Array_244_ek, _va_Array_244_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8291 = 1ULL;
        (void)hoisted__U64_8291;
        Str *hoisted__Str_8292 = Str_to_str(a);
        (void)hoisted__Str_8292;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_244, hoisted__U64_8291, hoisted__Str_8292, &_va_Array_244_ek, _va_Array_244_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8294 = 2ULL;
        (void)hoisted__U64_8294;
        (void)_til_str_lit_214;
        (void)_til_str_lit_214;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_244, hoisted__U64_8294, &_til_str_lit_214, &_va_Array_244_ek, _va_Array_244_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8297 = 3ULL;
        (void)hoisted__U64_8297;
        Str *hoisted__Str_8298 = Str_to_str(b);
        (void)hoisted__Str_8298;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_244, hoisted__U64_8297, hoisted__Str_8298, &_va_Array_244_ek, _va_Array_244_eo, &_til_str_lit_213);
        Str_delete(&_til_str_lit_213, (Bool){0});
        U64 hoisted__U64_8300 = 4ULL;
        (void)hoisted__U64_8300;
        (void)_til_str_lit_215;
        (void)_til_str_lit_215;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_244, hoisted__U64_8300, &_til_str_lit_215, &_va_Array_244_ek, _va_Array_244_eo, &_til_str_lit_213);
        OutOfBounds_delete(_va_Array_244_eo, 1);
        Str_delete(&_til_str_lit_213, (Bool){0});
        panic(_va_Array_244, loc);
    }
}

U64 Str_len_dyn(void *til_env, void *_a0) {
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
    return (void *)Str_with_capacity(*(U64 *)_a0);
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
U64 Str_size_dyn(void *til_env) {
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
U64 OutOfBounds_size_dyn(void *til_env) {
    (void)til_env;
    return OutOfBounds_size();
}
static __attribute__((unused)) TilClosure OutOfBounds_size_dyn__til_closure = { (void *)OutOfBounds_size_dyn, NULL, NULL };
void *Array__Str_new_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Array__Str_new(*(U64 *)_a0);
}
static __attribute__((unused)) TilClosure Array__Str_new_dyn__til_closure = { (void *)Array__Str_new_dyn, NULL, NULL };
U64 Array__Str_len_dyn(void *til_env, void *_a0) {
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
    Array__Str_unsafe_set(_a0, *(U64 *)_a1, _a2);
}
static __attribute__((unused)) TilClosure Array__Str_unsafe_set_dyn__til_closure = { (void *)Array__Str_unsafe_set_dyn, NULL, NULL };
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3, void *_a4, void *_a5) {
    (void)til_env;
    Array__Str_set(_a0, *(U64 *)_a1, _a2, _a3, _a4, _a5);
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
U64 Array__Str_size_dyn(void *til_env) {
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
U64 Vec__Str_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Str_size();
}
static __attribute__((unused)) TilClosure Vec__Str_size_dyn__til_closure = { (void *)Vec__Str_size_dyn, NULL, NULL };
U64 Dynamic_size_dyn(void *til_env) {
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
U64 U8_size_dyn(void *til_env) {
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
U64 U32_size_dyn(void *til_env) {
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
U64 U64_size_dyn(void *til_env) {
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
U64 I8_size_dyn(void *til_env) {
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
U64 I32_size_dyn(void *til_env) {
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
U64 I64_size_dyn(void *til_env) {
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
U64 F32_size_dyn(void *til_env) {
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
U64 Bool_size_dyn(void *til_env) {
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
U64 Primitive_size_dyn(void *til_env) {
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
U64 Type_size_dyn(void *til_env) {
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
U64 FuncType_size_dyn(void *til_env) {
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
U64 OwnType_size_dyn(void *til_env) {
    (void)til_env;
    return OwnType_size();
}
static __attribute__((unused)) TilClosure OwnType_size_dyn__til_closure = { (void *)OwnType_size_dyn, NULL, NULL };
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
U64 Declaration_size_dyn(void *til_env) {
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
U64 FunctionDef_size_dyn(void *til_env) {
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
U64 FCallData_size_dyn(void *til_env) {
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
U64 LiteralNumData_size_dyn(void *til_env) {
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
U64 IdentData_size_dyn(void *til_env) {
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
U64 FieldAccessData_size_dyn(void *til_env) {
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
U64 StructDef_size_dyn(void *til_env) {
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
U64 EnumDef_size_dyn(void *til_env) {
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
U64 AssignData_size_dyn(void *til_env) {
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
U64 FieldAssignData_size_dyn(void *til_env) {
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
U64 ForInData_size_dyn(void *til_env) {
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
U64 Literal_size_dyn(void *til_env) {
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
U64 MatchData_size_dyn(void *til_env) {
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
U64 CaptureBlockData_size_dyn(void *til_env) {
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
U64 NodeType_size_dyn(void *til_env) {
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
U64 Expr_size_dyn(void *til_env) {
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
U64 Map__I64_Str_size_dyn(void *til_env) {
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
U64 Vec__Bool_size_dyn(void *til_env) {
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
U64 Vec__I64_size_dyn(void *til_env) {
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
U64 Vec__Declaration_size_dyn(void *til_env) {
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
U64 Vec__Expr_size_dyn(void *til_env) {
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
U64 Range_size_dyn(void *til_env) {
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
U64 CfVec2_size_dyn(void *til_env) {
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
U64 CfRect_size_dyn(void *til_env) {
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
U64 CfVec3f_size_dyn(void *til_env) {
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
U64 Color_size_dyn(void *til_env) {
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
U64 Token_size_dyn(void *til_env) {
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
        return 11LL;
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
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_46;
        if (*index == 2LL) return &_til_str_lit_47;
        if (*index == 3LL) return &_til_str_lit_48;
        if (*index == 4LL) return &_til_str_lit_49;
        if (*index == 5LL) return &_til_str_lit_50;
        if (*index == 6LL) return &_til_str_lit_51;
        if (*index == 7LL) return &_til_str_lit_52;
        if (*index == 8LL) return &_til_str_lit_54;
        if (*index == 9LL) return &_til_str_lit_56;
        if (*index == 10LL) return &_til_str_lit_58;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_59;
        if (*index == 1LL) return &_til_str_lit_61;
        if (*index == 2LL) return &_til_str_lit_63;
        if (*index == 3LL) return &_til_str_lit_64;
        if (*index == 4LL) return &_til_str_lit_66;
        if (*index == 5LL) return &_til_str_lit_67;
        if (*index == 6LL) return &_til_str_lit_68;
        if (*index == 7LL) return &_til_str_lit_69;
        if (*index == 8LL) return &_til_str_lit_70;
        if (*index == 9LL) return &_til_str_lit_71;
        if (*index == 10LL) return &_til_str_lit_72;
        if (*index == 11LL) return &_til_str_lit_73;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_74;
        if (*index == 1LL) return &_til_str_lit_75;
        if (*index == 2LL) return &_til_str_lit_76;
        if (*index == 3LL) return &_til_str_lit_77;
        if (*index == 4LL) return &_til_str_lit_78;
        if (*index == 5LL) return &_til_str_lit_54;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_79;
        if (*index == 1LL) return &_til_str_lit_54;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_54;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_54;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_80;
        if (*index == 1LL) return &_til_str_lit_81;
        if (*index == 2LL) return &_til_str_lit_82;
        if (*index == 3LL) return &_til_str_lit_83;
        if (*index == 4LL) return &_til_str_lit_84;
        if (*index == 5LL) return &_til_str_lit_85;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_81;
        if (*index == 1LL) return &_til_str_lit_86;
        if (*index == 2LL) return &_til_str_lit_87;
        if (*index == 3LL) return &_til_str_lit_89;
        if (*index == 4LL) return &_til_str_lit_85;
        if (*index == 5LL) return &_til_str_lit_91;
        if (*index == 6LL) return &_til_str_lit_92;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_94;
        if (*index == 2LL) return &_til_str_lit_95;
        if (*index == 3LL) return &_til_str_lit_78;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_94;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_45;
        if (*index == 1LL) return &_til_str_lit_48;
        if (*index == 2LL) return &_til_str_lit_54;
        if (*index == 3LL) return &_til_str_lit_96;
        if (*index == 4LL) return &_til_str_lit_97;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_54;
        if (*index == 1LL) return &_til_str_lit_103;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_72;
        if (*index == 1LL) return &_til_str_lit_73;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_139;
        if (*index == 1LL) return &_til_str_lit_141;
        if (*index == 2LL) return &_til_str_lit_143;
        if (*index == 3LL) return &_til_str_lit_144;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_145;
        if (*index == 1LL) return &_til_str_lit_146;
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
        if (*index == 0LL) return &_til_str_lit_153;
        if (*index == 1LL) return &_til_str_lit_154;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_179;
        if (*index == 1LL) return &_til_str_lit_180;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_185;
        if (*index == 1LL) return &_til_str_lit_187;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_179;
        if (*index == 1LL) return &_til_str_lit_180;
        if (*index == 2LL) return &_til_str_lit_192;
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
        if (*index == 7LL) return &_til_str_lit_53;
        if (*index == 8LL) return &_til_str_lit_55;
        if (*index == 9LL) return &_til_str_lit_57;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_62;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_65;
        if (*index == 4LL) return &_til_str_lit_14;
        if (*index == 5LL) return &_til_str_lit_14;
        if (*index == 6LL) return &_til_str_lit_53;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
        if (*index == 10LL) return &_til_str_lit_62;
        if (*index == 11LL) return &_til_str_lit_6;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_10;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_55;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_55;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_55;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_55;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_62;
        if (*index == 1LL) return &_til_str_lit_62;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_6;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_62;
        if (*index == 1LL) return &_til_str_lit_65;
        if (*index == 2LL) return &_til_str_lit_88;
        if (*index == 3LL) return &_til_str_lit_90;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
        if (*index == 6LL) return &_til_str_lit_93;
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
        if (*index == 2LL) return &_til_str_lit_55;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_17;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_55;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_62;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_140;
        if (*index == 1LL) return &_til_str_lit_142;
        if (*index == 2LL) return &_til_str_lit_13;
        if (*index == 3LL) return &_til_str_lit_13;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_93;
        if (*index == 1LL) return &_til_str_lit_65;
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
        if (*index == 0LL) return &_til_str_lit_186;
        if (*index == 1LL) return &_til_str_lit_186;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_98;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_100;
        if (*index == 4LL) return &_til_str_lit_101;
        if (*index == 5LL) return &_til_str_lit_102;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_30;
        if (*index == 1LL) return &_til_str_lit_104;
        if (*index == 2LL) return &_til_str_lit_105;
        if (*index == 3LL) return &_til_str_lit_107;
        if (*index == 4LL) return &_til_str_lit_109;
        if (*index == 5LL) return &_til_str_lit_111;
        if (*index == 6LL) return &_til_str_lit_25;
        if (*index == 7LL) return &_til_str_lit_22;
        if (*index == 8LL) return &_til_str_lit_24;
        if (*index == 9LL) return &_til_str_lit_114;
        if (*index == 10LL) return &_til_str_lit_116;
        if (*index == 11LL) return &_til_str_lit_118;
        if (*index == 12LL) return &_til_str_lit_119;
        if (*index == 13LL) return &_til_str_lit_120;
        if (*index == 14LL) return &_til_str_lit_121;
        if (*index == 15LL) return &_til_str_lit_123;
        if (*index == 16LL) return &_til_str_lit_124;
        if (*index == 17LL) return &_til_str_lit_125;
        if (*index == 18LL) return &_til_str_lit_126;
        if (*index == 19LL) return &_til_str_lit_127;
        if (*index == 20LL) return &_til_str_lit_129;
        if (*index == 21LL) return &_til_str_lit_130;
        if (*index == 22LL) return &_til_str_lit_131;
        if (*index == 23LL) return &_til_str_lit_132;
        if (*index == 24LL) return &_til_str_lit_133;
        if (*index == 25LL) return &_til_str_lit_134;
        if (*index == 26LL) return &_til_str_lit_136;
        if (*index == 27LL) return &_til_str_lit_137;
        if (*index == 28LL) return &_til_str_lit_138;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_199;
        if (*index == 1LL) return &_til_str_lit_200;
        if (*index == 2LL) return &_til_str_lit_201;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_98;
        if (*index == 1LL) return &_til_str_lit_204;
        if (*index == 2LL) return &_til_str_lit_205;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_99;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_18;
        if (*index == 4LL) return &_til_str_lit_18;
        if (*index == 5LL) return &_til_str_lit_18;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_104;
        if (*index == 2LL) return &_til_str_lit_106;
        if (*index == 3LL) return &_til_str_lit_108;
        if (*index == 4LL) return &_til_str_lit_110;
        if (*index == 5LL) return &_til_str_lit_112;
        if (*index == 6LL) return &_til_str_lit_113;
        if (*index == 7LL) return &_til_str_lit_22;
        if (*index == 8LL) return &_til_str_lit_24;
        if (*index == 9LL) return &_til_str_lit_115;
        if (*index == 10LL) return &_til_str_lit_117;
        if (*index == 11LL) return &_til_str_lit_18;
        if (*index == 12LL) return &_til_str_lit_18;
        if (*index == 13LL) return &_til_str_lit_18;
        if (*index == 14LL) return &_til_str_lit_122;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_18;
        if (*index == 17LL) return &_til_str_lit_18;
        if (*index == 18LL) return &_til_str_lit_18;
        if (*index == 19LL) return &_til_str_lit_128;
        if (*index == 20LL) return &_til_str_lit_18;
        if (*index == 21LL) return &_til_str_lit_18;
        if (*index == 22LL) return &_til_str_lit_18;
        if (*index == 23LL) return &_til_str_lit_18;
        if (*index == 24LL) return &_til_str_lit_18;
        if (*index == 25LL) return &_til_str_lit_135;
        if (*index == 26LL) return &_til_str_lit_18;
        if (*index == 27LL) return &_til_str_lit_135;
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
        if (*index == 1LL) return &_til_str_lit_10;
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
    CAP_LIT = 18446744073709551615ULL;
    CAP_VIEW = 18446744073709551614ULL;
    ELEM_POD = 0ULL;
    ELEM_BOXED = 1ULL;
    ELEM_FN = 2ULL;
    __til_docs_blob__ = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_docs_blob__;
    __til_info_blob__ = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_info_blob__;
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
