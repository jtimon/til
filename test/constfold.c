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
    NodeType_TAG_BodyValue
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
Bool and(Bool a, Bool b);
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
Bool and(Bool a, Bool b);
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
static __attribute__((unused)) Str _til_str_lit_41 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_42 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_43 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_44 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_214 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_215 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

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
        Array__Str *_fc_Array__Str_115 = parts;
        (void)_fc_Array__Str_115;
        (void)_fc_Array__Str_115;
        U64 _fi_USize_115 = 0ULL;
        (void)_fi_USize_115;
        while (1) {
            U64 hoisted__U64_117 = (_fc_Array__Str_115->cap);
            (void)hoisted__U64_117;
            Bool _wcond_Bool_116 = ((Bool)(_fi_USize_115 < hoisted__U64_117));
            (void)_wcond_Bool_116;
            if (_wcond_Bool_116) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_115->data) + ((U64)(((U64)(_fi_USize_115 * 24ULL)))))));
            U64 hoisted__U64_118 = 1ULL;
            (void)hoisted__U64_118;
            U64 hoisted__U64_119 = ((U64)(_fi_USize_115 + hoisted__U64_118));
            (void)hoisted__U64_119;
            _fi_USize_115 = hoisted__U64_119;
            U64 hoisted__U64_120 = (s->count);
            (void)hoisted__U64_120;
            U64 hoisted__U64_121 = ((U64)(total + hoisted__U64_120));
            (void)hoisted__U64_121;
            total = hoisted__U64_121;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_122 = parts;
        (void)_fc_Array__Str_122;
        (void)_fc_Array__Str_122;
        U64 _fi_USize_122 = 0ULL;
        (void)_fi_USize_122;
        while (1) {
            U64 hoisted__U64_124 = (_fc_Array__Str_122->cap);
            (void)hoisted__U64_124;
            Bool _wcond_Bool_123 = ((Bool)(_fi_USize_122 < hoisted__U64_124));
            (void)_wcond_Bool_123;
            if (_wcond_Bool_123) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_122->data) + ((U64)(((U64)(_fi_USize_122 * 24ULL)))))));
            U64 hoisted__U64_125 = 1ULL;
            (void)hoisted__U64_125;
            U64 hoisted__U64_126 = ((U64)(_fi_USize_122 + hoisted__U64_125));
            (void)hoisted__U64_126;
            _fi_USize_122 = hoisted__U64_126;
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
    Bool hoisted__Bool_142 = ((Bool)(b->count < a->count));
    (void)hoisted__Bool_142;
    if (hoisted__Bool_142) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_143 = 0;
    (void)hoisted__I32_143;
    Bool hoisted__Bool_144 = ((Bool)(c < hoisted__I32_143));
    (void)hoisted__Bool_144;
    if (hoisted__Bool_144) {
        I64 hoisted__I64_140 = -1;
        (void)hoisted__I64_140;
        { I64 _ret_val = hoisted__I64_140;
                        return _ret_val; }
    }
    I32 hoisted__I32_145 = 0;
    (void)hoisted__I32_145;
    Bool hoisted__Bool_146 = ((Bool)(c > hoisted__I32_145));
    (void)hoisted__Bool_146;
    if (hoisted__Bool_146) {
        I64 hoisted__I64_141 = 1;
        (void)hoisted__I64_141;
        { I64 _ret_val = hoisted__I64_141;
                        return _ret_val; }
    }
    I64 hoisted__I64_147 = U64_cmp(a->count, b->count);
    (void)hoisted__I64_147;
    return hoisted__I64_147;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_150 = ((Bool)(a->count != b->count));
    (void)hoisted__Bool_150;
    if (hoisted__Bool_150) {
        Bool hoisted__Bool_148 = 0;
        (void)hoisted__Bool_148;
        { Bool _ret_val = hoisted__Bool_148;
                return _ret_val; }
    }
    Bool hoisted__Bool_151 = ptr_eq(a->c_str, b->c_str);
    (void)hoisted__Bool_151;
    if (hoisted__Bool_151) {
        Bool hoisted__Bool_149 = 1;
        (void)hoisted__Bool_149;
        { Bool _ret_val = hoisted__Bool_149;
                return _ret_val; }
    }
    I32 hoisted__I32_152 = memcmp(a->c_str, b->c_str, a->count);
    (void)hoisted__I32_152;
    I32 hoisted__I32_153 = 0;
    (void)hoisted__I32_153;
    Bool hoisted__Bool_154 = ((Bool)(hoisted__I32_152 == hoisted__I32_153));
    (void)hoisted__Bool_154;
    return hoisted__Bool_154;
    __builtin_unreachable();
}

Str * Str_with_capacity(U64 n) {
    U64 hoisted__U64_156 = 0ULL;
    (void)hoisted__U64_156;
    Bool hoisted__Bool_157 = ((Bool)(n == hoisted__U64_156));
    (void)hoisted__Bool_157;
    if (hoisted__Bool_157) {
        static Str hoisted__Str_155 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_155;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_155; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U64 hoisted__U64_158 = 1ULL;
    (void)hoisted__U64_158;
    U64 hoisted__U64_159 = ((U64)(n + hoisted__U64_158));
    (void)hoisted__U64_159;
    I8 *buf = malloc(hoisted__U64_159);
    I32 hoisted__I32_160 = 0;
    (void)hoisted__I32_160;
    U64 hoisted__U64_161 = 1ULL;
    (void)hoisted__U64_161;
    memset(buf, hoisted__I32_160, hoisted__U64_161);
    I64 hoisted__I64_162 = 0;
    (void)hoisted__I64_162;
    Str *hoisted__Str_163 = malloc(sizeof(Str));
    hoisted__Str_163->c_str = buf;
    hoisted__Str_163->count = hoisted__I64_162;
    hoisted__Str_163->cap = n;
    (void)hoisted__Str_163;
    return hoisted__Str_163;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U64 hoisted__U64_176 = 0ULL;
    (void)hoisted__U64_176;
    Bool hoisted__Bool_177 = ((Bool)(s->count == hoisted__U64_176));
    (void)hoisted__Bool_177;
    if (hoisted__Bool_177) {
        return;
    }
    Bool hoisted__Bool_178 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_178;
    if (hoisted__Bool_178) {
        U64 hoisted__U64_166 = 1ULL;
        (void)hoisted__U64_166;
        Array__Str *_va_Array_3 = Array__Str_new(hoisted__U64_166);
        (void)_va_Array_3;
        I64 _va_Array_3_ek = 0;
        (void)_va_Array_3_ek;
        OutOfBounds *_va_Array_3_eo = malloc(sizeof(OutOfBounds));
        _va_Array_3_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_3_eo;
        U64 hoisted__U64_167 = 0ULL;
        (void)hoisted__U64_167;
        static Str hoisted__Str_168 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_168;
        static Str hoisted__Str_169 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_169;
        Array__Str_set(_va_Array_3, hoisted__U64_167, &hoisted__Str_168, &_va_Array_3_ek, _va_Array_3_eo, &hoisted__Str_169);
        OutOfBounds_delete(_va_Array_3_eo, 1);
        Str_delete(&hoisted__Str_169, (Bool){0});
        static Str hoisted__Str_170 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_170;
        panic(_va_Array_3, &hoisted__Str_170);
        Str_delete(&hoisted__Str_170, (Bool){0});
    }
    U64 new_len = ((U64)(self->count + s->count));
    Bool hoisted__Bool_179 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_179;
    if (hoisted__Bool_179) {
        U64 hoisted__U64_171 = 1ULL;
        (void)hoisted__U64_171;
        Array__Str *_va_Array_4 = Array__Str_new(hoisted__U64_171);
        (void)_va_Array_4;
        I64 _va_Array_4_ek = 0;
        (void)_va_Array_4_ek;
        OutOfBounds *_va_Array_4_eo = malloc(sizeof(OutOfBounds));
        _va_Array_4_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_4_eo;
        U64 hoisted__U64_172 = 0ULL;
        (void)hoisted__U64_172;
        static Str hoisted__Str_173 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_173;
        static Str hoisted__Str_174 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_174;
        Array__Str_set(_va_Array_4, hoisted__U64_172, &hoisted__Str_173, &_va_Array_4_ek, _va_Array_4_eo, &hoisted__Str_174);
        OutOfBounds_delete(_va_Array_4_eo, 1);
        Str_delete(&hoisted__Str_174, (Bool){0});
        static Str hoisted__Str_175 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_175;
        panic(_va_Array_4, &hoisted__Str_175);
        Str_delete(&hoisted__Str_175, (Bool){0});
    }
    void *hoisted__v_180 = ((void *)((U8 *)(self->c_str) + (self->count)));
    (void)hoisted__v_180;
    (void)hoisted__v_180;
    memcpy(hoisted__v_180, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_181 = ((void *)((U8 *)(self->c_str) + (new_len)));
    (void)hoisted__v_181;
    (void)hoisted__v_181;
    I32 hoisted__I32_182 = 0;
    (void)hoisted__I32_182;
    U64 hoisted__U64_183 = 1ULL;
    (void)hoisted__U64_183;
    memset(hoisted__v_181, hoisted__I32_182, hoisted__U64_183);
}

Str * Str_clone(Str * val) {
    U64 hoisted__U64_185 = 0ULL;
    (void)hoisted__U64_185;
    Bool hoisted__Bool_186 = ((Bool)(val->count == hoisted__U64_185));
    (void)hoisted__Bool_186;
    if (hoisted__Bool_186) {
        static Str hoisted__Str_184 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_184;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_184; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U64 hoisted__U64_187 = 1ULL;
    (void)hoisted__U64_187;
    U64 hoisted__U64_188 = ((U64)(val->count + hoisted__U64_187));
    (void)hoisted__U64_188;
    I8 *new_data = malloc(hoisted__U64_188);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_189 = ((void *)((U8 *)(new_data) + (val->count)));
    (void)hoisted__v_189;
    (void)hoisted__v_189;
    I32 hoisted__I32_190 = 0;
    (void)hoisted__I32_190;
    U64 hoisted__U64_191 = 1ULL;
    (void)hoisted__U64_191;
    memset(hoisted__v_189, hoisted__I32_190, hoisted__U64_191);
    Str *hoisted__Str_192 = malloc(sizeof(Str));
    hoisted__Str_192->c_str = new_data;
    hoisted__Str_192->count = val->count;
    hoisted__Str_192->cap = val->count;
    (void)hoisted__Str_192;
    return hoisted__Str_192;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_193 = Str_clone(self);
    (void)hoisted__Str_193;
    return hoisted__Str_193;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_194 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_194;
    if (hoisted__Bool_194) {
        free(self->c_str);
    }
    Bool hoisted__Bool_195 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_195;
    Bool hoisted__Bool_196 = and(call_free, hoisted__Bool_195);
    (void)hoisted__Bool_196;
    if (hoisted__Bool_196) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_391 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U64))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_391;
    return hoisted__U64_391;
    __builtin_unreachable();
}

U64 Str_size(void) {
    U64 hoisted__U64_575 = 24ULL;
    (void)hoisted__U64_575;
    return hoisted__U64_575;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_584 = Str_eq(a, b);
    (void)hoisted__Bool_584;
    Bool hoisted__Bool_585 = ((Bool)(!(hoisted__Bool_584)));
    (void)hoisted__Bool_585;
    return hoisted__Bool_585;
    __builtin_unreachable();
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_676 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_676->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_676;
    return hoisted__OutOfBounds_676;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_677 = 0;
    (void)hoisted__Bool_677;
    Str_delete(&self->msg, hoisted__Bool_677);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U64 hoisted__U64_678 = 0ULL;
    (void)hoisted__U64_678;
    U64 hoisted__U64_679 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_678); });
    (void)hoisted__U64_679;
    return hoisted__U64_679;
    __builtin_unreachable();
}

U64 OutOfBounds_size(void) {
    U64 hoisted__U64_698 = 24ULL;
    (void)hoisted__U64_698;
    return hoisted__U64_698;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(U64 cap) {
    U64 hoisted__U64_722 = 24ULL;
    (void)hoisted__U64_722;
    U64 hoisted__U64_723 = (U64)(cap);
    (void)hoisted__U64_723;
    U64 hoisted__U64_724 = (U64)(hoisted__U64_722);
    (void)hoisted__U64_724;
    void * hoisted__v_725 = calloc(hoisted__U64_723, hoisted__U64_724);
    (void)hoisted__v_725;
    Array__Str *hoisted__Array__Str_726 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_726->data = hoisted__v_725;
    hoisted__Array__Str_726->cap = cap;
    (void)hoisted__Array__Str_726;
    return hoisted__Array__Str_726;
    __builtin_unreachable();
}

U64 Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, U64 * i) {
    U64 hoisted__U64_727 = 24ULL;
    (void)hoisted__U64_727;
    U64 hoisted__U64_728 = ((U64)(DEREF(i) * hoisted__U64_727));
    (void)hoisted__U64_728;
    U64 hoisted__U64_729 = (U64)(hoisted__U64_728);
    (void)hoisted__U64_729;
    void *hoisted__v_730 = ((void *)((U8 *)(self->data) + (hoisted__U64_729)));
    (void)hoisted__v_730;
    (void)hoisted__v_730;
    return hoisted__v_730;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, U64 i, Str * val) {
    Str *hoisted__Str_757 = (((void *)((U8 *)(self->data) + ((U64)(((U64)(i * 24ULL)))))));
    (void)hoisted__Str_757;
    (void)hoisted__Str_757;
    Bool hoisted__Bool_758 = 0;
    (void)hoisted__Bool_758;
    Str_delete(hoisted__Str_757, hoisted__Bool_758);
    U64 hoisted__U64_759 = 24ULL;
    (void)hoisted__U64_759;
    Str *hoisted__Str_760 = (((void *)((U8 *)(self->data) + ((U64)(((U64)(i * 24ULL)))))));
    (void)hoisted__Str_760;
    (void)hoisted__Str_760;
    U64 hoisted__U64_761 = (U64)(hoisted__U64_759);
    (void)hoisted__U64_761;
    memcpy(hoisted__Str_760, val, hoisted__U64_761);
    U64 hoisted__U64_762 = 24ULL;
    (void)hoisted__U64_762;
    I32 hoisted__I32_763 = 0;
    (void)hoisted__I32_763;
    U64 hoisted__U64_764 = (U64)(hoisted__U64_762);
    (void)hoisted__U64_764;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_763, hoisted__U64_764); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U64 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_787 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_787;
    if (hoisted__Bool_787) {
        U64 hoisted__U64_765 = 6ULL;
        (void)hoisted__U64_765;
        Array__Str *_va_Array_16 = Array__Str_new(hoisted__U64_765);
        (void)_va_Array_16;
        I64 _va_Array_16_ek = 0;
        (void)_va_Array_16_ek;
        OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
        _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_16_eo;
        U64 hoisted__U64_766 = 0ULL;
        (void)hoisted__U64_766;
        Str *hoisted__Str_767 = Str_clone(loc);
        (void)hoisted__Str_767;
        static Str hoisted__Str_768 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_768;
        Array__Str_set(_va_Array_16, hoisted__U64_766, hoisted__Str_767, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_768);
        Str_delete(&hoisted__Str_768, (Bool){0});
        U64 hoisted__U64_769 = 1ULL;
        (void)hoisted__U64_769;
        static Str hoisted__Str_770 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_770;
        static Str hoisted__Str_771 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_771;
        Array__Str_set(_va_Array_16, hoisted__U64_769, &hoisted__Str_770, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_771);
        Str_delete(&hoisted__Str_771, (Bool){0});
        U64 hoisted__U64_772 = 2ULL;
        (void)hoisted__U64_772;
        Str *hoisted__Str_773 = U64_to_str(i);
        (void)hoisted__Str_773;
        static Str hoisted__Str_774 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_774;
        Array__Str_set(_va_Array_16, hoisted__U64_772, hoisted__Str_773, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_774);
        Str_delete(&hoisted__Str_774, (Bool){0});
        U64 hoisted__U64_775 = 3ULL;
        (void)hoisted__U64_775;
        static Str hoisted__Str_776 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_776;
        static Str hoisted__Str_777 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_777;
        Array__Str_set(_va_Array_16, hoisted__U64_775, &hoisted__Str_776, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_777);
        Str_delete(&hoisted__Str_777, (Bool){0});
        U64 hoisted__U64_778 = 4ULL;
        (void)hoisted__U64_778;
        Str *hoisted__Str_779 = U64_to_str(self->cap);
        (void)hoisted__Str_779;
        static Str hoisted__Str_780 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_780;
        Array__Str_set(_va_Array_16, hoisted__U64_778, hoisted__Str_779, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_780);
        Str_delete(&hoisted__Str_780, (Bool){0});
        U64 hoisted__U64_781 = 5ULL;
        (void)hoisted__U64_781;
        static Str hoisted__Str_782 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_782;
        static Str hoisted__Str_783 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_783;
        Array__Str_set(_va_Array_16, hoisted__U64_781, &hoisted__Str_782, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_783);
        OutOfBounds_delete(_va_Array_16_eo, 1);
        Str_delete(&hoisted__Str_783, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_784 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_16); hoisted__OutOfBounds_784->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_784;
        U64 hoisted__U64_785 = 24ULL;
        (void)hoisted__U64_785;
        swap_bytes(_err_OutOfBounds, hoisted__OutOfBounds_784, hoisted__U64_785);
        OutOfBounds_delete(hoisted__OutOfBounds_784, 1);
        I64 hoisted__I64_786 = 1;
        (void)hoisted__I64_786;
        *_err_kind = hoisted__I64_786;
    }
    I64 hoisted__I64_788 = 0;
    (void)hoisted__I64_788;
    Bool hoisted__Bool_789 = ((Bool)(DEREF(_err_kind) == hoisted__I64_788));
    (void)hoisted__Bool_789;
    if (hoisted__Bool_789) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U64 _re_U64_790 = self->cap;
        (void)_re_U64_790;
        U64 _rc_U64_790 = 0ULL;
        (void)_rc_U64_790;
        Bool hoisted__Bool_803 = ((Bool)(_rc_U64_790 <= _re_U64_790));
        (void)hoisted__Bool_803;
        if (hoisted__Bool_803) {
            while (1) {
                Bool _wcond_Bool_791 = ((Bool)(_rc_U64_790 < _re_U64_790));
                (void)_wcond_Bool_791;
                if (_wcond_Bool_791) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_790);
                (++_rc_U64_790);
                U64 hoisted__U64_792 = 24ULL;
                (void)hoisted__U64_792;
                U64 hoisted__U64_793 = ((U64)(i * hoisted__U64_792));
                (void)hoisted__U64_793;
                U64 hoisted__U64_794 = (U64)(hoisted__U64_793);
                (void)hoisted__U64_794;
                Str *hoisted__Str_795 = ((void *)((U8 *)(self->data) + (hoisted__U64_794)));
                (void)hoisted__Str_795;
                (void)hoisted__Str_795;
                Bool hoisted__Bool_796 = 0;
                (void)hoisted__Bool_796;
                Str_delete(hoisted__Str_795, hoisted__Bool_796);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_797 = ((Bool)(_rc_U64_790 > _re_U64_790));
                (void)_wcond_Bool_797;
                if (_wcond_Bool_797) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_790);
                (--_rc_U64_790);
                U64 hoisted__U64_798 = 24ULL;
                (void)hoisted__U64_798;
                U64 hoisted__U64_799 = ((U64)(i * hoisted__U64_798));
                (void)hoisted__U64_799;
                U64 hoisted__U64_800 = (U64)(hoisted__U64_799);
                (void)hoisted__U64_800;
                Str *hoisted__Str_801 = ((void *)((U8 *)(self->data) + (hoisted__U64_800)));
                (void)hoisted__Str_801;
                (void)hoisted__Str_801;
                Bool hoisted__Bool_802 = 0;
                (void)hoisted__Bool_802;
                Str_delete(hoisted__Str_801, hoisted__Bool_802);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U64 hoisted__U64_832 = 24ULL;
    (void)hoisted__U64_832;
    U64 hoisted__U64_833 = ((U64)(self->cap * hoisted__U64_832));
    (void)hoisted__U64_833;
    U64 hoisted__U64_834 = (U64)(hoisted__U64_833);
    (void)hoisted__U64_834;
    U8 *new_data = malloc(hoisted__U64_834);
    {
        U64 _re_U64_804 = self->cap;
        (void)_re_U64_804;
        U64 _rc_U64_804 = 0ULL;
        (void)_rc_U64_804;
        Bool hoisted__Bool_831 = ((Bool)(_rc_U64_804 <= _re_U64_804));
        (void)hoisted__Bool_831;
        if (hoisted__Bool_831) {
            while (1) {
                Bool _wcond_Bool_805 = ((Bool)(_rc_U64_804 < _re_U64_804));
                (void)_wcond_Bool_805;
                if (_wcond_Bool_805) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_804);
                (++_rc_U64_804);
                U64 hoisted__U64_806 = 24ULL;
                (void)hoisted__U64_806;
                U64 hoisted__U64_807 = ((U64)(i * hoisted__U64_806));
                (void)hoisted__U64_807;
                U64 hoisted__U64_808 = (U64)(hoisted__U64_807);
                (void)hoisted__U64_808;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_808)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_809 = 24ULL;
                (void)hoisted__U64_809;
                U64 hoisted__U64_810 = ((U64)(i * hoisted__U64_809));
                (void)hoisted__U64_810;
                U64 hoisted__U64_811 = (U64)(hoisted__U64_810);
                (void)hoisted__U64_811;
                U64 hoisted__U64_812 = 24ULL;
                (void)hoisted__U64_812;
                void *hoisted__v_813 = ((void *)((U8 *)(new_data) + (hoisted__U64_811)));
                (void)hoisted__v_813;
                (void)hoisted__v_813;
                U64 hoisted__U64_814 = (U64)(hoisted__U64_812);
                (void)hoisted__U64_814;
                memcpy(hoisted__v_813, cloned, hoisted__U64_814);
                U64 hoisted__U64_815 = 24ULL;
                (void)hoisted__U64_815;
                I32 hoisted__I32_816 = 0;
                (void)hoisted__I32_816;
                U64 hoisted__U64_817 = (U64)(hoisted__U64_815);
                (void)hoisted__U64_817;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_816, hoisted__U64_817); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_818 = ((Bool)(_rc_U64_804 > _re_U64_804));
                (void)_wcond_Bool_818;
                if (_wcond_Bool_818) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_804);
                (--_rc_U64_804);
                U64 hoisted__U64_819 = 24ULL;
                (void)hoisted__U64_819;
                U64 hoisted__U64_820 = ((U64)(i * hoisted__U64_819));
                (void)hoisted__U64_820;
                U64 hoisted__U64_821 = (U64)(hoisted__U64_820);
                (void)hoisted__U64_821;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_821)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_822 = 24ULL;
                (void)hoisted__U64_822;
                U64 hoisted__U64_823 = ((U64)(i * hoisted__U64_822));
                (void)hoisted__U64_823;
                U64 hoisted__U64_824 = (U64)(hoisted__U64_823);
                (void)hoisted__U64_824;
                U64 hoisted__U64_825 = 24ULL;
                (void)hoisted__U64_825;
                void *hoisted__v_826 = ((void *)((U8 *)(new_data) + (hoisted__U64_824)));
                (void)hoisted__v_826;
                (void)hoisted__v_826;
                U64 hoisted__U64_827 = (U64)(hoisted__U64_825);
                (void)hoisted__U64_827;
                memcpy(hoisted__v_826, cloned, hoisted__U64_827);
                U64 hoisted__U64_828 = 24ULL;
                (void)hoisted__U64_828;
                I32 hoisted__I32_829 = 0;
                (void)hoisted__I32_829;
                U64 hoisted__U64_830 = (U64)(hoisted__U64_828);
                (void)hoisted__U64_830;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_829, hoisted__U64_830); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_835 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_835->data = new_data;
    hoisted__Array__Str_835->cap = self->cap;
    (void)hoisted__Array__Str_835;
    return hoisted__Array__Str_835;
    __builtin_unreachable();
}

U64 Array__Str_size(void) {
    U64 hoisted__U64_836 = 16ULL;
    (void)hoisted__U64_836;
    return hoisted__U64_836;
    __builtin_unreachable();
}

Vec__Str * Vec__Str_new(void) {
    U64 hoisted__U64_837 = 24ULL;
    (void)hoisted__U64_837;
    U64 hoisted__U64_838 = (U64)(hoisted__U64_837);
    (void)hoisted__U64_838;
    void * hoisted__v_839 = malloc(hoisted__U64_838);
    (void)hoisted__v_839;
    U64 hoisted__U64_840 = 0ULL;
    (void)hoisted__U64_840;
    I64 hoisted__I64_841 = 1;
    (void)hoisted__I64_841;
    Vec__Str *hoisted__Vec__Str_842 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_842->data = hoisted__v_839;
    hoisted__Vec__Str_842->count = hoisted__U64_840;
    hoisted__Vec__Str_842->cap = hoisted__I64_841;
    (void)hoisted__Vec__Str_842;
    return hoisted__Vec__Str_842;
    __builtin_unreachable();
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U64 _re_U64_852 = self->count;
        (void)_re_U64_852;
        U64 _rc_U64_852 = 0ULL;
        (void)_rc_U64_852;
        Bool hoisted__Bool_865 = ((Bool)(_rc_U64_852 <= _re_U64_852));
        (void)hoisted__Bool_865;
        if (hoisted__Bool_865) {
            while (1) {
                Bool _wcond_Bool_853 = ((Bool)(_rc_U64_852 < _re_U64_852));
                (void)_wcond_Bool_853;
                if (_wcond_Bool_853) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_852);
                (++_rc_U64_852);
                U64 hoisted__U64_854 = 24ULL;
                (void)hoisted__U64_854;
                U64 hoisted__U64_855 = ((U64)(i * hoisted__U64_854));
                (void)hoisted__U64_855;
                U64 hoisted__U64_856 = (U64)(hoisted__U64_855);
                (void)hoisted__U64_856;
                Str *hoisted__Str_857 = ((void *)((U8 *)(self->data) + (hoisted__U64_856)));
                (void)hoisted__Str_857;
                (void)hoisted__Str_857;
                Bool hoisted__Bool_858 = 0;
                (void)hoisted__Bool_858;
                Str_delete(hoisted__Str_857, hoisted__Bool_858);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_859 = ((Bool)(_rc_U64_852 > _re_U64_852));
                (void)_wcond_Bool_859;
                if (_wcond_Bool_859) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_852);
                (--_rc_U64_852);
                U64 hoisted__U64_860 = 24ULL;
                (void)hoisted__U64_860;
                U64 hoisted__U64_861 = ((U64)(i * hoisted__U64_860));
                (void)hoisted__U64_861;
                U64 hoisted__U64_862 = (U64)(hoisted__U64_861);
                (void)hoisted__U64_862;
                Str *hoisted__Str_863 = ((void *)((U8 *)(self->data) + (hoisted__U64_862)));
                (void)hoisted__Str_863;
                (void)hoisted__Str_863;
                Bool hoisted__Bool_864 = 0;
                (void)hoisted__Bool_864;
                Str_delete(hoisted__Str_863, hoisted__Bool_864);
            }
        }
    }
    U64 hoisted__U64_866 = 0ULL;
    (void)hoisted__U64_866;
    self->count = hoisted__U64_866;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U64 hoisted__U64_1136 = 24ULL;
    (void)hoisted__U64_1136;
    U64 hoisted__U64_1137 = ((U64)(self->cap * hoisted__U64_1136));
    (void)hoisted__U64_1137;
    U64 hoisted__U64_1138 = (U64)(hoisted__U64_1137);
    (void)hoisted__U64_1138;
    U8 *new_data = malloc(hoisted__U64_1138);
    {
        U64 _re_U64_1108 = self->count;
        (void)_re_U64_1108;
        U64 _rc_U64_1108 = 0ULL;
        (void)_rc_U64_1108;
        Bool hoisted__Bool_1135 = ((Bool)(_rc_U64_1108 <= _re_U64_1108));
        (void)hoisted__Bool_1135;
        if (hoisted__Bool_1135) {
            while (1) {
                Bool _wcond_Bool_1109 = ((Bool)(_rc_U64_1108 < _re_U64_1108));
                (void)_wcond_Bool_1109;
                if (_wcond_Bool_1109) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_1108);
                (++_rc_U64_1108);
                U64 hoisted__U64_1110 = 24ULL;
                (void)hoisted__U64_1110;
                U64 hoisted__U64_1111 = ((U64)(i * hoisted__U64_1110));
                (void)hoisted__U64_1111;
                U64 hoisted__U64_1112 = (U64)(hoisted__U64_1111);
                (void)hoisted__U64_1112;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_1112)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_1113 = 24ULL;
                (void)hoisted__U64_1113;
                U64 hoisted__U64_1114 = ((U64)(i * hoisted__U64_1113));
                (void)hoisted__U64_1114;
                U64 hoisted__U64_1115 = (U64)(hoisted__U64_1114);
                (void)hoisted__U64_1115;
                U64 hoisted__U64_1116 = 24ULL;
                (void)hoisted__U64_1116;
                void *hoisted__v_1117 = ((void *)((U8 *)(new_data) + (hoisted__U64_1115)));
                (void)hoisted__v_1117;
                (void)hoisted__v_1117;
                U64 hoisted__U64_1118 = (U64)(hoisted__U64_1116);
                (void)hoisted__U64_1118;
                memcpy(hoisted__v_1117, cloned, hoisted__U64_1118);
                U64 hoisted__U64_1119 = 24ULL;
                (void)hoisted__U64_1119;
                I32 hoisted__I32_1120 = 0;
                (void)hoisted__I32_1120;
                U64 hoisted__U64_1121 = (U64)(hoisted__U64_1119);
                (void)hoisted__U64_1121;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1120, hoisted__U64_1121); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1122 = ((Bool)(_rc_U64_1108 > _re_U64_1108));
                (void)_wcond_Bool_1122;
                if (_wcond_Bool_1122) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_1108);
                (--_rc_U64_1108);
                U64 hoisted__U64_1123 = 24ULL;
                (void)hoisted__U64_1123;
                U64 hoisted__U64_1124 = ((U64)(i * hoisted__U64_1123));
                (void)hoisted__U64_1124;
                U64 hoisted__U64_1125 = (U64)(hoisted__U64_1124);
                (void)hoisted__U64_1125;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_1125)));
                Str *cloned = Str_clone(src);
                U64 hoisted__U64_1126 = 24ULL;
                (void)hoisted__U64_1126;
                U64 hoisted__U64_1127 = ((U64)(i * hoisted__U64_1126));
                (void)hoisted__U64_1127;
                U64 hoisted__U64_1128 = (U64)(hoisted__U64_1127);
                (void)hoisted__U64_1128;
                U64 hoisted__U64_1129 = 24ULL;
                (void)hoisted__U64_1129;
                void *hoisted__v_1130 = ((void *)((U8 *)(new_data) + (hoisted__U64_1128)));
                (void)hoisted__v_1130;
                (void)hoisted__v_1130;
                U64 hoisted__U64_1131 = (U64)(hoisted__U64_1129);
                (void)hoisted__U64_1131;
                memcpy(hoisted__v_1130, cloned, hoisted__U64_1131);
                U64 hoisted__U64_1132 = 24ULL;
                (void)hoisted__U64_1132;
                I32 hoisted__I32_1133 = 0;
                (void)hoisted__I32_1133;
                U64 hoisted__U64_1134 = (U64)(hoisted__U64_1132);
                (void)hoisted__U64_1134;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1133, hoisted__U64_1134); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1139 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1139->data = new_data;
    hoisted__Vec__Str_1139->count = self->count;
    hoisted__Vec__Str_1139->cap = self->cap;
    (void)hoisted__Vec__Str_1139;
    return hoisted__Vec__Str_1139;
    __builtin_unreachable();
}

U64 Vec__Str_size(void) {
    U64 hoisted__U64_1140 = 24ULL;
    (void)hoisted__U64_1140;
    return hoisted__U64_1140;
    __builtin_unreachable();
}

U64 Dynamic_size(void) {
    U64 hoisted__U64_1143 = 8ULL;
    (void)hoisted__U64_1143;
    return hoisted__U64_1143;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U64 hoisted__U64_1144 = 8ULL;
    (void)hoisted__U64_1144;
    U64 hoisted__U64_1145 = (U64)(hoisted__U64_1144);
    (void)hoisted__U64_1145;
    void * out = malloc(hoisted__U64_1145);
    U64 hoisted__U64_1146 = 8ULL;
    (void)hoisted__U64_1146;
    U64 hoisted__U64_1147 = (U64)(hoisted__U64_1146);
    (void)hoisted__U64_1147;
    memcpy(out, self, hoisted__U64_1147);
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
    U64 hoisted__U64_1159 = 1ULL;
    (void)hoisted__U64_1159;
    return hoisted__U64_1159;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U64 hoisted__U64_1244 = 0ULL;
    (void)hoisted__U64_1244;
    U64 hoisted__U64_1245 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1244); });
    (void)hoisted__U64_1245;
    return hoisted__U64_1245;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 U32_size(void) {
    U64 hoisted__U64_1349 = 4ULL;
    (void)hoisted__U64_1349;
    return hoisted__U64_1349;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U64 hoisted__U64_1434 = 0ULL;
    (void)hoisted__U64_1434;
    U64 hoisted__U64_1435 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1434); });
    (void)hoisted__U64_1435;
    return hoisted__U64_1435;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1436 = U64_to_str_ext(val);
    (void)hoisted__Str_1436;
    return hoisted__Str_1436;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 U64_size(void) {
    U64 hoisted__U64_1441 = 8ULL;
    (void)hoisted__U64_1441;
    return hoisted__U64_1441;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U64 hoisted__U64_1526 = 0ULL;
    (void)hoisted__U64_1526;
    U64 hoisted__U64_1527 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1526); });
    (void)hoisted__U64_1527;
    return hoisted__U64_1527;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 I8_size(void) {
    U64 hoisted__U64_1544 = 1ULL;
    (void)hoisted__U64_1544;
    return hoisted__U64_1544;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U64 hoisted__U64_1545 = 0ULL;
    (void)hoisted__U64_1545;
    U64 hoisted__U64_1546 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1545); });
    (void)hoisted__U64_1546;
    return hoisted__U64_1546;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 I32_size(void) {
    U64 hoisted__U64_1723 = 4ULL;
    (void)hoisted__U64_1723;
    return hoisted__U64_1723;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U64 hoisted__U64_1865 = 0ULL;
    (void)hoisted__U64_1865;
    U64 hoisted__U64_1866 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_1865); });
    (void)hoisted__U64_1866;
    return hoisted__U64_1866;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1877 = 0;
    (void)hoisted__I64_1877;
    Bool hoisted__Bool_1878 = ((Bool)(val < hoisted__I64_1877));
    (void)hoisted__Bool_1878;
    if (hoisted__Bool_1878) {
        U64 hoisted__U64_1867 = 0ULL;
        (void)hoisted__U64_1867;
        U64 hoisted__U64_1868 = (U64)(val);
        (void)hoisted__U64_1868;
        U64 mag = ((U64)(hoisted__U64_1867 - hoisted__U64_1868));
        U64 hoisted__U64_1869 = 2ULL;
        (void)hoisted__U64_1869;
        Array__Str *_va_Array_44 = Array__Str_new(hoisted__U64_1869);
        (void)_va_Array_44;
        I64 _va_Array_44_ek = 0;
        (void)_va_Array_44_ek;
        OutOfBounds *_va_Array_44_eo = malloc(sizeof(OutOfBounds));
        _va_Array_44_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_44_eo;
        U64 hoisted__U64_1870 = 0ULL;
        (void)hoisted__U64_1870;
        static Str hoisted__Str_1871 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1871;
        static Str hoisted__Str_1872 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1872;
        Array__Str_set(_va_Array_44, hoisted__U64_1870, &hoisted__Str_1871, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1872);
        Str_delete(&hoisted__Str_1872, (Bool){0});
        U64 hoisted__U64_1873 = 1ULL;
        (void)hoisted__U64_1873;
        Str *hoisted__Str_1874 = U64_to_str(mag);
        (void)hoisted__Str_1874;
        static Str hoisted__Str_1875 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1875;
        Array__Str_set(_va_Array_44, hoisted__U64_1873, hoisted__Str_1874, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1875);
        OutOfBounds_delete(_va_Array_44_eo, 1);
        Str_delete(&hoisted__Str_1875, (Bool){0});
        Str *hoisted__Str_1876 = format(_va_Array_44);
        (void)hoisted__Str_1876;
        { Str * _ret_val = hoisted__Str_1876;
                return _ret_val; }
    }
    U64 hoisted__U64_1879 = (U64)(val);
    (void)hoisted__U64_1879;
    Str *hoisted__Str_1880 = U64_to_str(hoisted__U64_1879);
    (void)hoisted__Str_1880;
    return hoisted__Str_1880;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 I64_size(void) {
    U64 hoisted__U64_1894 = 8ULL;
    (void)hoisted__U64_1894;
    return hoisted__U64_1894;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U64 hoisted__U64_2052 = 0ULL;
    (void)hoisted__U64_2052;
    U64 hoisted__U64_2053 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_2052); });
    (void)hoisted__U64_2053;
    return hoisted__U64_2053;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 F32_size(void) {
    U64 hoisted__U64_2055 = 4ULL;
    (void)hoisted__U64_2055;
    return hoisted__U64_2055;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U64 hoisted__U64_2073 = 0ULL;
    (void)hoisted__U64_2073;
    U64 hoisted__U64_2074 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_2073); });
    (void)hoisted__U64_2074;
    return hoisted__U64_2074;
    __builtin_unreachable();
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2121 = 0;
    (void)_m_Bool_2121;
    {
        Bool hoisted__Bool_2124 = 1;
        (void)hoisted__Bool_2124;
        Bool hoisted__Bool_2125 = ((Bool)(a == hoisted__Bool_2124));
        (void)hoisted__Bool_2125;
        if (hoisted__Bool_2125) {
            Bool hoisted__Bool_2122 = (b);
            (void)hoisted__Bool_2122;
            _m_Bool_2121 = hoisted__Bool_2122;
        } else {
            Bool hoisted__Bool_2123 = 0;
            (void)hoisted__Bool_2123;
            _m_Bool_2121 = hoisted__Bool_2123;
        }
    }
    return _m_Bool_2121;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2150 = ((Bool)(a == b));
    (void)hoisted__Bool_2150;
    if (hoisted__Bool_2150) {
        I64 hoisted__I64_2148 = 0;
        (void)hoisted__I64_2148;
        { I64 _ret_val = hoisted__I64_2148;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2149 = -1;
        (void)hoisted__I64_2149;
        return hoisted__I64_2149;
    }
    I64 hoisted__I64_2151 = 1;
    (void)hoisted__I64_2151;
    return hoisted__I64_2151;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Bool_size(void) {
    U64 hoisted__U64_2152 = 1ULL;
    (void)hoisted__U64_2152;
    return hoisted__U64_2152;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U64 hoisted__U64_2153 = 0ULL;
    (void)hoisted__U64_2153;
    U64 hoisted__U64_2154 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_2153); });
    (void)hoisted__U64_2154;
    return hoisted__U64_2154;
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
    U64 hoisted__U64_2304 = 1ULL;
    (void)hoisted__U64_2304;
    Bool hoisted__Bool_2305 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2305;
    if (hoisted__Bool_2305) {
        U64 hoisted__U64_2284 = 1ULL;
        (void)hoisted__U64_2284;
        Bool hoisted__Bool_2285 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2285;
        { Bool _ret_val = hoisted__Bool_2285;
                return _ret_val; }
    }
    U64 hoisted__U64_2306 = 1ULL;
    (void)hoisted__U64_2306;
    Bool hoisted__Bool_2307 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2307;
    if (hoisted__Bool_2307) {
        U64 hoisted__U64_2286 = 1ULL;
        (void)hoisted__U64_2286;
        Bool hoisted__Bool_2287 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2287;
        { Bool _ret_val = hoisted__Bool_2287;
                return _ret_val; }
    }
    U64 hoisted__U64_2308 = 1ULL;
    (void)hoisted__U64_2308;
    Bool hoisted__Bool_2309 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2309;
    if (hoisted__Bool_2309) {
        U64 hoisted__U64_2288 = 1ULL;
        (void)hoisted__U64_2288;
        Bool hoisted__Bool_2289 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2289;
        { Bool _ret_val = hoisted__Bool_2289;
                return _ret_val; }
    }
    U64 hoisted__U64_2310 = 1ULL;
    (void)hoisted__U64_2310;
    Bool hoisted__Bool_2311 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        U64 hoisted__U64_2290 = 1ULL;
        (void)hoisted__U64_2290;
        Bool hoisted__Bool_2291 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2291;
        { Bool _ret_val = hoisted__Bool_2291;
                return _ret_val; }
    }
    U64 hoisted__U64_2312 = 1ULL;
    (void)hoisted__U64_2312;
    Bool hoisted__Bool_2313 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        U64 hoisted__U64_2292 = 1ULL;
        (void)hoisted__U64_2292;
        Bool hoisted__Bool_2293 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2293;
        { Bool _ret_val = hoisted__Bool_2293;
                return _ret_val; }
    }
    U64 hoisted__U64_2314 = 1ULL;
    (void)hoisted__U64_2314;
    Bool hoisted__Bool_2315 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2315;
    if (hoisted__Bool_2315) {
        U64 hoisted__U64_2294 = 1ULL;
        (void)hoisted__U64_2294;
        Bool hoisted__Bool_2295 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2295;
        { Bool _ret_val = hoisted__Bool_2295;
                return _ret_val; }
    }
    U64 hoisted__U64_2316 = 1ULL;
    (void)hoisted__U64_2316;
    Bool hoisted__Bool_2317 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2317;
    if (hoisted__Bool_2317) {
        U64 hoisted__U64_2296 = 1ULL;
        (void)hoisted__U64_2296;
        Bool hoisted__Bool_2297 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2297;
        { Bool _ret_val = hoisted__Bool_2297;
                return _ret_val; }
    }
    U64 hoisted__U64_2318 = 1ULL;
    (void)hoisted__U64_2318;
    Bool hoisted__Bool_2319 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2319;
    if (hoisted__Bool_2319) {
        U64 hoisted__U64_2298 = 1ULL;
        (void)hoisted__U64_2298;
        Bool hoisted__Bool_2299 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2299;
        { Bool _ret_val = hoisted__Bool_2299;
                return _ret_val; }
    }
    U64 hoisted__U64_2320 = 1ULL;
    (void)hoisted__U64_2320;
    Bool hoisted__Bool_2321 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2321;
    if (hoisted__Bool_2321) {
        U64 hoisted__U64_2300 = 1ULL;
        (void)hoisted__U64_2300;
        Bool hoisted__Bool_2301 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2301;
        { Bool _ret_val = hoisted__Bool_2301;
                return _ret_val; }
    }
    U64 hoisted__U64_2322 = 1ULL;
    (void)hoisted__U64_2322;
    Bool hoisted__Bool_2323 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2323;
    if (hoisted__Bool_2323) {
        U64 hoisted__U64_2302 = 1ULL;
        (void)hoisted__U64_2302;
        Bool hoisted__Bool_2303 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_2303;
        { Bool _ret_val = hoisted__Bool_2303;
                return _ret_val; }
    }
    Bool hoisted__Bool_2324 = 0;
    (void)hoisted__Bool_2324;
    return hoisted__Bool_2324;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2346 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2346;
    if (hoisted__Bool_2346) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2347 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2347;
    if (hoisted__Bool_2347) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2348 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2348;
    if (hoisted__Bool_2348) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2349 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2349;
    if (hoisted__Bool_2349) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2350 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2350;
    if (hoisted__Bool_2350) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2351 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2351;
    if (hoisted__Bool_2351) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2352 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2352;
    if (hoisted__Bool_2352) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2353 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2353;
    if (hoisted__Bool_2353) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2354 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2354;
    if (hoisted__Bool_2354) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2355 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2355;
    if (hoisted__Bool_2355) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2356 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2356;
    UNREACHABLE(&hoisted__Str_2356);
    Str_delete(&hoisted__Str_2356, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

U64 Primitive_size(void) {
    U64 hoisted__U64_2357 = 1ULL;
    (void)hoisted__U64_2357;
    return hoisted__U64_2357;
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
    U64 hoisted__U64_2436 = 1ULL;
    (void)hoisted__U64_2436;
    Bool hoisted__Bool_2437 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2437;
    if (hoisted__Bool_2437) {
        Str *hoisted__Str_2426 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2426;
        (void)hoisted__Str_2426;
        Bool hoisted__Bool_2427 = 0;
        (void)hoisted__Bool_2427;
        Str_delete(hoisted__Str_2426, hoisted__Bool_2427);
    }
    U64 hoisted__U64_2438 = 1ULL;
    (void)hoisted__U64_2438;
    Bool hoisted__Bool_2439 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2439;
    if (hoisted__Bool_2439) {
        Str *hoisted__Str_2428 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2428;
        (void)hoisted__Str_2428;
        Bool hoisted__Bool_2429 = 0;
        (void)hoisted__Bool_2429;
        Str_delete(hoisted__Str_2428, hoisted__Bool_2429);
    }
    U64 hoisted__U64_2440 = 1ULL;
    (void)hoisted__U64_2440;
    Bool hoisted__Bool_2441 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2441;
    if (hoisted__Bool_2441) {
        Str *hoisted__Str_2430 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2430;
        (void)hoisted__Str_2430;
        Bool hoisted__Bool_2431 = 0;
        (void)hoisted__Bool_2431;
        Str_delete(hoisted__Str_2430, hoisted__Bool_2431);
    }
    U64 hoisted__U64_2442 = 1ULL;
    (void)hoisted__U64_2442;
    Bool hoisted__Bool_2443 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2443;
    if (hoisted__Bool_2443) {
        Primitive *hoisted__Primitive_2432 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Primitive_2432;
        (void)hoisted__Primitive_2432;
        Bool hoisted__Bool_2433 = 0;
        (void)hoisted__Bool_2433;
        Primitive_delete(hoisted__Primitive_2432, hoisted__Bool_2433);
    }
    U64 hoisted__U64_2444 = 1ULL;
    (void)hoisted__U64_2444;
    Bool hoisted__Bool_2445 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2445;
    if (hoisted__Bool_2445) {
        Str *hoisted__Str_2434 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_2434;
        (void)hoisted__Str_2434;
        Bool hoisted__Bool_2435 = 0;
        (void)hoisted__Bool_2435;
        Str_delete(hoisted__Str_2434, hoisted__Bool_2435);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U64 hoisted__U64_2546 = 1ULL;
    (void)hoisted__U64_2546;
    Bool hoisted__Bool_2547 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2547;
    if (hoisted__Bool_2547) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U64 hoisted__U64_2548 = 1ULL;
    (void)hoisted__U64_2548;
    Bool hoisted__Bool_2549 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2549;
    if (hoisted__Bool_2549) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U64 hoisted__U64_2550 = 1ULL;
    (void)hoisted__U64_2550;
    Bool hoisted__Bool_2551 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2551;
    if (hoisted__Bool_2551) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2536 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2536;
        Type *hoisted__Type_2537 = Type_Struct(hoisted__Str_2536);
        (void)hoisted__Type_2537;
        { Type * _ret_val = hoisted__Type_2537;
                return _ret_val; }
    }
    U64 hoisted__U64_2552 = 1ULL;
    (void)hoisted__U64_2552;
    Bool hoisted__Bool_2553 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2553;
    if (hoisted__Bool_2553) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U64 hoisted__U64_2554 = 1ULL;
    (void)hoisted__U64_2554;
    Bool hoisted__Bool_2555 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2555;
    if (hoisted__Bool_2555) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2538 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2538;
        Type *hoisted__Type_2539 = Type_Enum(hoisted__Str_2538);
        (void)hoisted__Type_2539;
        { Type * _ret_val = hoisted__Type_2539;
                return _ret_val; }
    }
    U64 hoisted__U64_2556 = 1ULL;
    (void)hoisted__U64_2556;
    Bool hoisted__Bool_2557 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2557;
    if (hoisted__Bool_2557) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U64 hoisted__U64_2558 = 1ULL;
    (void)hoisted__U64_2558;
    Bool hoisted__Bool_2559 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2559;
    if (hoisted__Bool_2559) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U64 hoisted__U64_2560 = 1ULL;
    (void)hoisted__U64_2560;
    Bool hoisted__Bool_2561 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2561;
    if (hoisted__Bool_2561) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U64 hoisted__U64_2562 = 1ULL;
    (void)hoisted__U64_2562;
    Bool hoisted__Bool_2563 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2563;
    if (hoisted__Bool_2563) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U64 hoisted__U64_2564 = 1ULL;
    (void)hoisted__U64_2564;
    Bool hoisted__Bool_2565 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2565;
    if (hoisted__Bool_2565) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2540 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2540;
        Type *hoisted__Type_2541 = Type_Custom(hoisted__Str_2540);
        (void)hoisted__Type_2541;
        { Type * _ret_val = hoisted__Type_2541;
                return _ret_val; }
    }
    U64 hoisted__U64_2566 = 1ULL;
    (void)hoisted__U64_2566;
    Bool hoisted__Bool_2567 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2567;
    if (hoisted__Bool_2567) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2542 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2542;
        Type *hoisted__Type_2543 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2542; _oa; }));
        (void)hoisted__Type_2543;
        { Type * _ret_val = hoisted__Type_2543;
                return _ret_val; }
    }
    U64 hoisted__U64_2568 = 1ULL;
    (void)hoisted__U64_2568;
    Bool hoisted__Bool_2569 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2569;
    if (hoisted__Bool_2569) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2544 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2544;
        Type *hoisted__Type_2545 = Type_FuncPtrSig(hoisted__Str_2544);
        (void)hoisted__Type_2545;
        { Type * _ret_val = hoisted__Type_2545;
                return _ret_val; }
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

U64 Type_size(void) {
    U64 hoisted__U64_2570 = 32ULL;
    (void)hoisted__U64_2570;
    return hoisted__U64_2570;
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
Bool FuncType_eq(FuncType * self, FuncType * other) {
    U64 hoisted__U64_2716 = 1ULL;
    (void)hoisted__U64_2716;
    Bool hoisted__Bool_2717 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2717;
    if (hoisted__Bool_2717) {
        U64 hoisted__U64_2696 = 1ULL;
        (void)hoisted__U64_2696;
        Bool hoisted__Bool_2697 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2697;
        { Bool _ret_val = hoisted__Bool_2697;
                return _ret_val; }
    }
    U64 hoisted__U64_2718 = 1ULL;
    (void)hoisted__U64_2718;
    Bool hoisted__Bool_2719 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2719;
    if (hoisted__Bool_2719) {
        U64 hoisted__U64_2698 = 1ULL;
        (void)hoisted__U64_2698;
        Bool hoisted__Bool_2699 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2699;
        { Bool _ret_val = hoisted__Bool_2699;
                return _ret_val; }
    }
    U64 hoisted__U64_2720 = 1ULL;
    (void)hoisted__U64_2720;
    Bool hoisted__Bool_2721 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2721;
    if (hoisted__Bool_2721) {
        U64 hoisted__U64_2700 = 1ULL;
        (void)hoisted__U64_2700;
        Bool hoisted__Bool_2701 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2701;
        { Bool _ret_val = hoisted__Bool_2701;
                return _ret_val; }
    }
    U64 hoisted__U64_2722 = 1ULL;
    (void)hoisted__U64_2722;
    Bool hoisted__Bool_2723 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2723;
    if (hoisted__Bool_2723) {
        U64 hoisted__U64_2702 = 1ULL;
        (void)hoisted__U64_2702;
        Bool hoisted__Bool_2703 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2703;
        { Bool _ret_val = hoisted__Bool_2703;
                return _ret_val; }
    }
    U64 hoisted__U64_2724 = 1ULL;
    (void)hoisted__U64_2724;
    Bool hoisted__Bool_2725 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2725;
    if (hoisted__Bool_2725) {
        U64 hoisted__U64_2704 = 1ULL;
        (void)hoisted__U64_2704;
        Bool hoisted__Bool_2705 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2705;
        { Bool _ret_val = hoisted__Bool_2705;
                return _ret_val; }
    }
    U64 hoisted__U64_2726 = 1ULL;
    (void)hoisted__U64_2726;
    Bool hoisted__Bool_2727 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2727;
    if (hoisted__Bool_2727) {
        U64 hoisted__U64_2706 = 1ULL;
        (void)hoisted__U64_2706;
        Bool hoisted__Bool_2707 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2707;
        { Bool _ret_val = hoisted__Bool_2707;
                return _ret_val; }
    }
    U64 hoisted__U64_2728 = 1ULL;
    (void)hoisted__U64_2728;
    Bool hoisted__Bool_2729 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2729;
    if (hoisted__Bool_2729) {
        U64 hoisted__U64_2708 = 1ULL;
        (void)hoisted__U64_2708;
        Bool hoisted__Bool_2709 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2709;
        { Bool _ret_val = hoisted__Bool_2709;
                return _ret_val; }
    }
    U64 hoisted__U64_2730 = 1ULL;
    (void)hoisted__U64_2730;
    Bool hoisted__Bool_2731 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2731;
    if (hoisted__Bool_2731) {
        U64 hoisted__U64_2710 = 1ULL;
        (void)hoisted__U64_2710;
        Bool hoisted__Bool_2711 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2711;
        { Bool _ret_val = hoisted__Bool_2711;
                return _ret_val; }
    }
    U64 hoisted__U64_2732 = 1ULL;
    (void)hoisted__U64_2732;
    Bool hoisted__Bool_2733 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2733;
    if (hoisted__Bool_2733) {
        U64 hoisted__U64_2712 = 1ULL;
        (void)hoisted__U64_2712;
        Bool hoisted__Bool_2713 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2713;
        { Bool _ret_val = hoisted__Bool_2713;
                return _ret_val; }
    }
    U64 hoisted__U64_2734 = 1ULL;
    (void)hoisted__U64_2734;
    Bool hoisted__Bool_2735 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2735;
    if (hoisted__Bool_2735) {
        U64 hoisted__U64_2714 = 1ULL;
        (void)hoisted__U64_2714;
        Bool hoisted__Bool_2715 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2715;
        { Bool _ret_val = hoisted__Bool_2715;
                return _ret_val; }
    }
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    return hoisted__Bool_2736;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2758 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2758;
    if (hoisted__Bool_2758) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2759 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2759;
    if (hoisted__Bool_2759) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2760 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2760;
    if (hoisted__Bool_2760) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2761 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2761;
    if (hoisted__Bool_2761) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2762 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2762;
    if (hoisted__Bool_2762) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2763 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2763;
    if (hoisted__Bool_2763) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2764 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2764;
    if (hoisted__Bool_2764) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2765 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2765;
    if (hoisted__Bool_2765) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2766 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2766;
    if (hoisted__Bool_2766) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2767 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2767;
    if (hoisted__Bool_2767) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2768 = (Str){.c_str = (void *)"FuncType.clone:130:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2768;
    UNREACHABLE(&hoisted__Str_2768);
    Str_delete(&hoisted__Str_2768, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

U64 FuncType_size(void) {
    U64 hoisted__U64_2769 = 1ULL;
    (void)hoisted__U64_2769;
    return hoisted__U64_2769;
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
    U64 hoisted__U64_2776 = 1ULL;
    (void)hoisted__U64_2776;
    Bool hoisted__Bool_2777 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2777;
    if (hoisted__Bool_2777) {
        U64 hoisted__U64_2770 = 1ULL;
        (void)hoisted__U64_2770;
        Bool hoisted__Bool_2771 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2771;
        { Bool _ret_val = hoisted__Bool_2771;
                return _ret_val; }
    }
    U64 hoisted__U64_2778 = 1ULL;
    (void)hoisted__U64_2778;
    Bool hoisted__Bool_2779 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2779;
    if (hoisted__Bool_2779) {
        U64 hoisted__U64_2772 = 1ULL;
        (void)hoisted__U64_2772;
        Bool hoisted__Bool_2773 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2773;
        { Bool _ret_val = hoisted__Bool_2773;
                return _ret_val; }
    }
    U64 hoisted__U64_2780 = 1ULL;
    (void)hoisted__U64_2780;
    Bool hoisted__Bool_2781 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2781;
    if (hoisted__Bool_2781) {
        U64 hoisted__U64_2774 = 1ULL;
        (void)hoisted__U64_2774;
        Bool hoisted__Bool_2775 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2775;
        { Bool _ret_val = hoisted__Bool_2775;
                return _ret_val; }
    }
    Bool hoisted__Bool_2782 = 0;
    (void)hoisted__Bool_2782;
    return hoisted__Bool_2782;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2790 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2790;
    if (hoisted__Bool_2790) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2791 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2791;
    if (hoisted__Bool_2791) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2792 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2792;
    if (hoisted__Bool_2792) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2793 = (Str){.c_str = (void *)"OwnType.clone:142:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2793;
    UNREACHABLE(&hoisted__Str_2793);
    Str_delete(&hoisted__Str_2793, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

U64 OwnType_size(void) {
    U64 hoisted__U64_2794 = 1ULL;
    (void)hoisted__U64_2794;
    return hoisted__U64_2794;
    __builtin_unreachable();
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2796 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2796;
    Declaration *hoisted__Declaration_2797 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2797->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2797->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2797->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2797->is_mut = self->is_mut;
    hoisted__Declaration_2797->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2797->is_priv = self->is_priv;
    hoisted__Declaration_2797->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2797->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2797->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2797->default_value = hoisted__Expr_2796;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2797->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2797;
    return hoisted__Declaration_2797;
    __builtin_unreachable();
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2798 = 0;
    (void)hoisted__Bool_2798;
    Str_delete(&self->name, hoisted__Bool_2798);
    Bool hoisted__Bool_2799 = 0;
    (void)hoisted__Bool_2799;
    Str_delete(&self->doc, hoisted__Bool_2799);
    Bool hoisted__Bool_2800 = 0;
    (void)hoisted__Bool_2800;
    Str_delete(&self->explicit_type, hoisted__Bool_2800);
    Bool hoisted__Bool_2801 = 0;
    (void)hoisted__Bool_2801;
    Bool_delete(&self->is_mut, hoisted__Bool_2801);
    Bool hoisted__Bool_2802 = 0;
    (void)hoisted__Bool_2802;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2802);
    Bool hoisted__Bool_2803 = 0;
    (void)hoisted__Bool_2803;
    Bool_delete(&self->is_priv, hoisted__Bool_2803);
    Bool hoisted__Bool_2804 = 0;
    (void)hoisted__Bool_2804;
    Bool_delete(&self->used, hoisted__Bool_2804);
    Bool hoisted__Bool_2805 = 0;
    (void)hoisted__Bool_2805;
    OwnType_delete(&self->own_type, hoisted__Bool_2805);
    Bool hoisted__Bool_2806 = 0;
    (void)hoisted__Bool_2806;
    Type_delete(&self->til_type, hoisted__Bool_2806);
    Bool hoisted__Bool_2807 = 1;
    (void)hoisted__Bool_2807;
    Expr_delete(self->default_value, hoisted__Bool_2807);
    Bool hoisted__Bool_2808 = 0;
    (void)hoisted__Bool_2808;
    Str_delete(&self->orig_name, hoisted__Bool_2808);
    if (call_free) {
        free(self);
    }
}

U64 Declaration_size(void) {
    U64 hoisted__U64_2809 = 144ULL;
    (void)hoisted__U64_2809;
    return hoisted__U64_2809;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2811 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2811->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2811->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2811->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2811->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2811->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2811->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2811->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2811->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2811->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2811->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2811->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2811->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2811;
    return hoisted__FunctionDef_2811;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2812 = 0;
    (void)hoisted__Bool_2812;
    FuncType_delete(&self->func_type, hoisted__Bool_2812);
    Bool hoisted__Bool_2813 = 0;
    (void)hoisted__Bool_2813;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2813);
    Bool hoisted__Bool_2814 = 0;
    (void)hoisted__Bool_2814;
    Str_delete(&self->return_type, hoisted__Bool_2814);
    Bool hoisted__Bool_2815 = 0;
    (void)hoisted__Bool_2815;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2815);
    Bool hoisted__Bool_2816 = 0;
    (void)hoisted__Bool_2816;
    I32_delete(&self->variadic_index, hoisted__Bool_2816);
    Bool hoisted__Bool_2817 = 0;
    (void)hoisted__Bool_2817;
    I32_delete(&self->kwargs_index, hoisted__Bool_2817);
    Bool hoisted__Bool_2818 = 0;
    (void)hoisted__Bool_2818;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2818);
    Bool hoisted__Bool_2819 = 0;
    (void)hoisted__Bool_2819;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2819);
    Bool hoisted__Bool_2820 = 0;
    (void)hoisted__Bool_2820;
    Bool_delete(&self->auto_generated, hoisted__Bool_2820);
    Bool hoisted__Bool_2821 = 0;
    (void)hoisted__Bool_2821;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2821);
    Bool hoisted__Bool_2822 = 0;
    (void)hoisted__Bool_2822;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2822);
    Bool hoisted__Bool_2823 = 0;
    (void)hoisted__Bool_2823;
    Str_delete(&self->closure_name, hoisted__Bool_2823);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U64 hoisted__U64_2824 = 0ULL;
    (void)hoisted__U64_2824;
    U64 hoisted__U64_2825 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2824); });
    (void)hoisted__U64_2825;
    return hoisted__U64_2825;
    __builtin_unreachable();
}

U64 FunctionDef_size(void) {
    U64 hoisted__U64_2826 = 144ULL;
    (void)hoisted__U64_2826;
    return hoisted__U64_2826;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2829 = malloc(sizeof(FCallData));
    hoisted__FCallData_2829->is_splat = self->is_splat;
    hoisted__FCallData_2829->does_throw = self->does_throw;
    hoisted__FCallData_2829->is_bang = self->is_bang;
    hoisted__FCallData_2829->own_args = self->own_args;
    hoisted__FCallData_2829->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2829->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2829;
    return hoisted__FCallData_2829;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2830 = 0;
    (void)hoisted__Bool_2830;
    Bool_delete(&self->is_splat, hoisted__Bool_2830);
    Bool hoisted__Bool_2831 = 0;
    (void)hoisted__Bool_2831;
    Bool_delete(&self->does_throw, hoisted__Bool_2831);
    Bool hoisted__Bool_2832 = 0;
    (void)hoisted__Bool_2832;
    Bool_delete(&self->is_bang, hoisted__Bool_2832);
    Bool hoisted__Bool_2833 = 0;
    (void)hoisted__Bool_2833;
    U64_delete(&self->own_args, hoisted__Bool_2833);
    Bool hoisted__Bool_2834 = 0;
    (void)hoisted__Bool_2834;
    Bool_delete(&self->swap_replace, hoisted__Bool_2834);
    Bool hoisted__Bool_2835 = 0;
    (void)hoisted__Bool_2835;
    Type_delete(&self->til_type, hoisted__Bool_2835);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U64 hoisted__U64_2836 = 0ULL;
    (void)hoisted__U64_2836;
    U64 hoisted__U64_2837 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2836); });
    (void)hoisted__U64_2837;
    return hoisted__U64_2837;
    __builtin_unreachable();
}

U64 FCallData_size(void) {
    U64 hoisted__U64_2838 = 56ULL;
    (void)hoisted__U64_2838;
    return hoisted__U64_2838;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2850 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2850->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2850->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2850;
    return hoisted__LiteralNumData_2850;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2851 = 0;
    (void)hoisted__Bool_2851;
    Str_delete(&self->text, hoisted__Bool_2851);
    Bool hoisted__Bool_2852 = 0;
    (void)hoisted__Bool_2852;
    Type_delete(&self->til_type, hoisted__Bool_2852);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U64 hoisted__U64_2853 = 0ULL;
    (void)hoisted__U64_2853;
    U64 hoisted__U64_2854 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2853); });
    (void)hoisted__U64_2854;
    return hoisted__U64_2854;
    __builtin_unreachable();
}

U64 LiteralNumData_size(void) {
    U64 hoisted__U64_2855 = 56ULL;
    (void)hoisted__U64_2855;
    return hoisted__U64_2855;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2865 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2865->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2865->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2865;
    return hoisted__IdentData_2865;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2866 = 0;
    (void)hoisted__Bool_2866;
    Str_delete(&self->name, hoisted__Bool_2866);
    Bool hoisted__Bool_2867 = 0;
    (void)hoisted__Bool_2867;
    Type_delete(&self->til_type, hoisted__Bool_2867);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U64 hoisted__U64_2868 = 0ULL;
    (void)hoisted__U64_2868;
    U64 hoisted__U64_2869 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2868); });
    (void)hoisted__U64_2869;
    return hoisted__U64_2869;
    __builtin_unreachable();
}

U64 IdentData_size(void) {
    U64 hoisted__U64_2870 = 56ULL;
    (void)hoisted__U64_2870;
    return hoisted__U64_2870;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2876 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2876->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2876->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2876;
    return hoisted__FieldAccessData_2876;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2877 = 0;
    (void)hoisted__Bool_2877;
    Str_delete(&self->name, hoisted__Bool_2877);
    Bool hoisted__Bool_2878 = 0;
    (void)hoisted__Bool_2878;
    Type_delete(&self->til_type, hoisted__Bool_2878);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U64 hoisted__U64_2879 = 0ULL;
    (void)hoisted__U64_2879;
    U64 hoisted__U64_2880 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2879); });
    (void)hoisted__U64_2880;
    return hoisted__U64_2880;
    __builtin_unreachable();
}

U64 FieldAccessData_size(void) {
    U64 hoisted__U64_2881 = 56ULL;
    (void)hoisted__U64_2881;
    return hoisted__U64_2881;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2960 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2960->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2960->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2960->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2960->is_interface = self->is_interface;
    hoisted__StructDef_2960->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2960->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2960;
    return hoisted__StructDef_2960;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2961 = 0;
    (void)hoisted__Bool_2961;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2961);
    Bool hoisted__Bool_2962 = 0;
    (void)hoisted__Bool_2962;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2962);
    Bool hoisted__Bool_2963 = 0;
    (void)hoisted__Bool_2963;
    Str_delete(&self->c_tag, hoisted__Bool_2963);
    Bool hoisted__Bool_2964 = 0;
    (void)hoisted__Bool_2964;
    Bool_delete(&self->is_interface, hoisted__Bool_2964);
    Bool hoisted__Bool_2965 = 0;
    (void)hoisted__Bool_2965;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2965);
    Bool hoisted__Bool_2966 = 0;
    (void)hoisted__Bool_2966;
    Str_delete(&self->implements_name, hoisted__Bool_2966);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U64 hoisted__U64_2967 = 0ULL;
    (void)hoisted__U64_2967;
    U64 hoisted__U64_2968 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2967); });
    (void)hoisted__U64_2968;
    return hoisted__U64_2968;
    __builtin_unreachable();
}

U64 StructDef_size(void) {
    U64 hoisted__U64_2969 = 104ULL;
    (void)hoisted__U64_2969;
    return hoisted__U64_2969;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2974 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2974->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2974->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2974->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2974->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2974->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2974->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2974->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2974;
    return hoisted__EnumDef_2974;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2975 = 0;
    (void)hoisted__Bool_2975;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2975);
    Bool hoisted__Bool_2976 = 0;
    (void)hoisted__Bool_2976;
    Vec__Str_delete(&self->variants, hoisted__Bool_2976);
    Bool hoisted__Bool_2977 = 0;
    (void)hoisted__Bool_2977;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2977);
    Bool hoisted__Bool_2978 = 0;
    (void)hoisted__Bool_2978;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2978);
    Bool hoisted__Bool_2979 = 0;
    (void)hoisted__Bool_2979;
    Str_delete(&self->implements_name, hoisted__Bool_2979);
    Bool hoisted__Bool_2980 = 0;
    (void)hoisted__Bool_2980;
    Str_delete(&self->tag_type, hoisted__Bool_2980);
    Bool hoisted__Bool_2981 = 0;
    (void)hoisted__Bool_2981;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2981);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U64 hoisted__U64_2982 = 0ULL;
    (void)hoisted__U64_2982;
    U64 hoisted__U64_2983 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2982); });
    (void)hoisted__U64_2983;
    return hoisted__U64_2983;
    __builtin_unreachable();
}

U64 EnumDef_size(void) {
    U64 hoisted__U64_2984 = 192ULL;
    (void)hoisted__U64_2984;
    return hoisted__U64_2984;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_3085 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_3085->name = *_ca; free(_ca); }
    hoisted__AssignData_3085->save_old_delete = self->save_old_delete;
    hoisted__AssignData_3085->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_3085->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_3085;
    return hoisted__AssignData_3085;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_3086 = 0;
    (void)hoisted__Bool_3086;
    Str_delete(&self->name, hoisted__Bool_3086);
    Bool hoisted__Bool_3087 = 0;
    (void)hoisted__Bool_3087;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3087);
    Bool hoisted__Bool_3088 = 0;
    (void)hoisted__Bool_3088;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_3088);
    Bool hoisted__Bool_3089 = 0;
    (void)hoisted__Bool_3089;
    Bool_delete(&self->swap_replace, hoisted__Bool_3089);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U64 hoisted__U64_3090 = 0ULL;
    (void)hoisted__U64_3090;
    U64 hoisted__U64_3091 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3090); });
    (void)hoisted__U64_3091;
    return hoisted__U64_3091;
    __builtin_unreachable();
}

U64 AssignData_size(void) {
    U64 hoisted__U64_3092 = 32ULL;
    (void)hoisted__U64_3092;
    return hoisted__U64_3092;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_3094 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_3094->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_3094->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_3094;
    return hoisted__FieldAssignData_3094;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_3095 = 0;
    (void)hoisted__Bool_3095;
    Str_delete(&self->name, hoisted__Bool_3095);
    Bool hoisted__Bool_3096 = 0;
    (void)hoisted__Bool_3096;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3096);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U64 hoisted__U64_3097 = 0ULL;
    (void)hoisted__U64_3097;
    U64 hoisted__U64_3098 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3097); });
    (void)hoisted__U64_3098;
    return hoisted__U64_3098;
    __builtin_unreachable();
}

U64 FieldAssignData_size(void) {
    U64 hoisted__U64_3099 = 32ULL;
    (void)hoisted__U64_3099;
    return hoisted__U64_3099;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_3101 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_3101->name = *_ca; free(_ca); }
    hoisted__ForInData_3101->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_3101->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_3101->name2 = *_ca; free(_ca); }
    hoisted__ForInData_3101->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_3101;
    return hoisted__ForInData_3101;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_3102 = 0;
    (void)hoisted__Bool_3102;
    Str_delete(&self->name, hoisted__Bool_3102);
    Bool hoisted__Bool_3103 = 0;
    (void)hoisted__Bool_3103;
    Bool_delete(&self->is_mut, hoisted__Bool_3103);
    Bool hoisted__Bool_3104 = 0;
    (void)hoisted__Bool_3104;
    Type_delete(&self->til_type, hoisted__Bool_3104);
    Bool hoisted__Bool_3105 = 0;
    (void)hoisted__Bool_3105;
    Str_delete(&self->name2, hoisted__Bool_3105);
    Bool hoisted__Bool_3106 = 0;
    (void)hoisted__Bool_3106;
    Bool_delete(&self->is_mut2, hoisted__Bool_3106);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U64 hoisted__U64_3107 = 0ULL;
    (void)hoisted__U64_3107;
    U64 hoisted__U64_3108 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3107); });
    (void)hoisted__U64_3108;
    return hoisted__U64_3108;
    __builtin_unreachable();
}

U64 ForInData_size(void) {
    U64 hoisted__U64_3109 = 96ULL;
    (void)hoisted__U64_3109;
    return hoisted__U64_3109;
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
    U64 hoisted__U64_3150 = 1ULL;
    (void)hoisted__U64_3150;
    Bool hoisted__Bool_3151 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3151;
    if (hoisted__Bool_3151) {
        Str *hoisted__Str_3144 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_3144;
        (void)hoisted__Str_3144;
        Bool hoisted__Bool_3145 = 0;
        (void)hoisted__Bool_3145;
        Str_delete(hoisted__Str_3144, hoisted__Bool_3145);
    }
    U64 hoisted__U64_3152 = 1ULL;
    (void)hoisted__U64_3152;
    Bool hoisted__Bool_3153 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3153;
    if (hoisted__Bool_3153) {
        LiteralNumData *hoisted__LiteralNumData_3146 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__LiteralNumData_3146;
        (void)hoisted__LiteralNumData_3146;
        Bool hoisted__Bool_3147 = 0;
        (void)hoisted__Bool_3147;
        LiteralNumData_delete(hoisted__LiteralNumData_3146, hoisted__Bool_3147);
    }
    U64 hoisted__U64_3154 = 1ULL;
    (void)hoisted__U64_3154;
    Bool hoisted__Bool_3155 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3155;
    if (hoisted__Bool_3155) {
        Bool *hoisted__Bool_3148 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Bool_3148;
        (void)hoisted__Bool_3148;
        Bool hoisted__Bool_3149 = 0;
        (void)hoisted__Bool_3149;
        Bool_delete(hoisted__Bool_3148, hoisted__Bool_3149);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U64 hoisted__U64_3210 = 1ULL;
    (void)hoisted__U64_3210;
    Bool hoisted__Bool_3211 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3211;
    if (hoisted__Bool_3211) {
        Str *_clone_payload_Str_0 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3205 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3205;
        Literal *hoisted__Literal_3206 = Literal_Str(hoisted__Str_3205);
        (void)hoisted__Literal_3206;
        { Literal * _ret_val = hoisted__Literal_3206;
                return _ret_val; }
    }
    U64 hoisted__U64_3212 = 1ULL;
    (void)hoisted__U64_3212;
    Bool hoisted__Bool_3213 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3213;
    if (hoisted__Bool_3213) {
        LiteralNumData *_clone_payload_Num_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3207 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3207;
        Literal *hoisted__Literal_3208 = Literal_Num(hoisted__LiteralNumData_3207);
        (void)hoisted__Literal_3208;
        { Literal * _ret_val = hoisted__Literal_3208;
                return _ret_val; }
    }
    U64 hoisted__U64_3214 = 1ULL;
    (void)hoisted__U64_3214;
    Bool hoisted__Bool_3215 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3215;
    if (hoisted__Bool_3215) {
        Bool *_clone_payload_Bool_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3209 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3209;
        { Literal * _ret_val = hoisted__Literal_3209;
                return _ret_val; }
    }
    U64 hoisted__U64_3216 = 1ULL;
    (void)hoisted__U64_3216;
    Bool hoisted__Bool_3217 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_3217;
    if (hoisted__Bool_3217) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U64 hoisted__U64_3218 = 1ULL;
    (void)hoisted__U64_3218;
    Bool hoisted__Bool_3219 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_3219;
    if (hoisted__Bool_3219) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

U64 Literal_size(void) {
    U64 hoisted__U64_3220 = 64ULL;
    (void)hoisted__U64_3220;
    return hoisted__U64_3220;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3223 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3223->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3223->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3223;
    return hoisted__MatchData_3223;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3224 = 0;
    (void)hoisted__Bool_3224;
    Type_delete(&self->til_type, hoisted__Bool_3224);
    Bool hoisted__Bool_3225 = 0;
    (void)hoisted__Bool_3225;
    Str_delete(&self->result_temp, hoisted__Bool_3225);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U64 hoisted__U64_3226 = 0ULL;
    (void)hoisted__U64_3226;
    U64 hoisted__U64_3227 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3226); });
    (void)hoisted__U64_3227;
    return hoisted__U64_3227;
    __builtin_unreachable();
}

U64 MatchData_size(void) {
    U64 hoisted__U64_3228 = 56ULL;
    (void)hoisted__U64_3228;
    return hoisted__U64_3228;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3233 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3233->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3233->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3233;
    return hoisted__CaptureBlockData_3233;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3234 = 0;
    (void)hoisted__Bool_3234;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3234);
    Bool hoisted__Bool_3235 = 0;
    (void)hoisted__Bool_3235;
    Str_delete(&self->closure_name, hoisted__Bool_3235);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U64 hoisted__U64_3236 = 0ULL;
    (void)hoisted__U64_3236;
    U64 hoisted__U64_3237 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3236); });
    (void)hoisted__U64_3237;
    return hoisted__U64_3237;
    __builtin_unreachable();
}

U64 CaptureBlockData_size(void) {
    U64 hoisted__U64_3238 = 48ULL;
    (void)hoisted__U64_3238;
    return hoisted__U64_3238;
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
void NodeType_delete(NodeType * self, Bool call_free) {
    U64 hoisted__U64_3497 = 1ULL;
    (void)hoisted__U64_3497;
    Bool hoisted__Bool_3498 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3498;
    if (hoisted__Bool_3498) {
        Literal *hoisted__Literal_3467 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Literal_3467;
        (void)hoisted__Literal_3467;
        Bool hoisted__Bool_3468 = 0;
        (void)hoisted__Bool_3468;
        Literal_delete(hoisted__Literal_3467, hoisted__Bool_3468);
    }
    U64 hoisted__U64_3499 = 1ULL;
    (void)hoisted__U64_3499;
    Bool hoisted__Bool_3500 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3500;
    if (hoisted__Bool_3500) {
        IdentData *hoisted__IdentData_3469 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__IdentData_3469;
        (void)hoisted__IdentData_3469;
        Bool hoisted__Bool_3470 = 0;
        (void)hoisted__Bool_3470;
        IdentData_delete(hoisted__IdentData_3469, hoisted__Bool_3470);
    }
    U64 hoisted__U64_3501 = 1ULL;
    (void)hoisted__U64_3501;
    Bool hoisted__Bool_3502 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3502;
    if (hoisted__Bool_3502) {
        Declaration *hoisted__Declaration_3471 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Declaration_3471;
        (void)hoisted__Declaration_3471;
        Bool hoisted__Bool_3472 = 0;
        (void)hoisted__Bool_3472;
        Declaration_delete(hoisted__Declaration_3471, hoisted__Bool_3472);
    }
    U64 hoisted__U64_3503 = 1ULL;
    (void)hoisted__U64_3503;
    Bool hoisted__Bool_3504 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3504;
    if (hoisted__Bool_3504) {
        AssignData *hoisted__AssignData_3473 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__AssignData_3473;
        (void)hoisted__AssignData_3473;
        Bool hoisted__Bool_3474 = 0;
        (void)hoisted__Bool_3474;
        AssignData_delete(hoisted__AssignData_3473, hoisted__Bool_3474);
    }
    U64 hoisted__U64_3505 = 1ULL;
    (void)hoisted__U64_3505;
    Bool hoisted__Bool_3506 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3506;
    if (hoisted__Bool_3506) {
        FCallData *hoisted__FCallData_3475 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FCallData_3475;
        (void)hoisted__FCallData_3475;
        Bool hoisted__Bool_3476 = 0;
        (void)hoisted__Bool_3476;
        FCallData_delete(hoisted__FCallData_3475, hoisted__Bool_3476);
    }
    U64 hoisted__U64_3507 = 1ULL;
    (void)hoisted__U64_3507;
    Bool hoisted__Bool_3508 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3508;
    if (hoisted__Bool_3508) {
        FunctionDef *hoisted__FunctionDef_3477 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FunctionDef_3477;
        (void)hoisted__FunctionDef_3477;
        Bool hoisted__Bool_3478 = 0;
        (void)hoisted__Bool_3478;
        FunctionDef_delete(hoisted__FunctionDef_3477, hoisted__Bool_3478);
    }
    U64 hoisted__U64_3509 = 1ULL;
    (void)hoisted__U64_3509;
    Bool hoisted__Bool_3510 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3510;
    if (hoisted__Bool_3510) {
        StructDef *hoisted__StructDef_3479 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__StructDef_3479;
        (void)hoisted__StructDef_3479;
        Bool hoisted__Bool_3480 = 0;
        (void)hoisted__Bool_3480;
        StructDef_delete(hoisted__StructDef_3479, hoisted__Bool_3480);
    }
    U64 hoisted__U64_3511 = 1ULL;
    (void)hoisted__U64_3511;
    Bool hoisted__Bool_3512 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3512;
    if (hoisted__Bool_3512) {
        EnumDef *hoisted__EnumDef_3481 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__EnumDef_3481;
        (void)hoisted__EnumDef_3481;
        Bool hoisted__Bool_3482 = 0;
        (void)hoisted__Bool_3482;
        EnumDef_delete(hoisted__EnumDef_3481, hoisted__Bool_3482);
    }
    U64 hoisted__U64_3513 = 1ULL;
    (void)hoisted__U64_3513;
    Bool hoisted__Bool_3514 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3514;
    if (hoisted__Bool_3514) {
        FieldAccessData *hoisted__FieldAccessData_3483 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FieldAccessData_3483;
        (void)hoisted__FieldAccessData_3483;
        Bool hoisted__Bool_3484 = 0;
        (void)hoisted__Bool_3484;
        FieldAccessData_delete(hoisted__FieldAccessData_3483, hoisted__Bool_3484);
    }
    U64 hoisted__U64_3515 = 1ULL;
    (void)hoisted__U64_3515;
    Bool hoisted__Bool_3516 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3516;
    if (hoisted__Bool_3516) {
        FieldAssignData *hoisted__FieldAssignData_3485 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__FieldAssignData_3485;
        (void)hoisted__FieldAssignData_3485;
        Bool hoisted__Bool_3486 = 0;
        (void)hoisted__Bool_3486;
        FieldAssignData_delete(hoisted__FieldAssignData_3485, hoisted__Bool_3486);
    }
    U64 hoisted__U64_3517 = 1ULL;
    (void)hoisted__U64_3517;
    Bool hoisted__Bool_3518 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3518;
    if (hoisted__Bool_3518) {
        ForInData *hoisted__ForInData_3487 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__ForInData_3487;
        (void)hoisted__ForInData_3487;
        Bool hoisted__Bool_3488 = 0;
        (void)hoisted__Bool_3488;
        ForInData_delete(hoisted__ForInData_3487, hoisted__Bool_3488);
    }
    U64 hoisted__U64_3519 = 1ULL;
    (void)hoisted__U64_3519;
    Bool hoisted__Bool_3520 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3520;
    if (hoisted__Bool_3520) {
        Str *hoisted__Str_3489 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_3489;
        (void)hoisted__Str_3489;
        Bool hoisted__Bool_3490 = 0;
        (void)hoisted__Bool_3490;
        Str_delete(hoisted__Str_3489, hoisted__Bool_3490);
    }
    U64 hoisted__U64_3521 = 1ULL;
    (void)hoisted__U64_3521;
    Bool hoisted__Bool_3522 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3522;
    if (hoisted__Bool_3522) {
        MatchData *hoisted__MatchData_3491 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__MatchData_3491;
        (void)hoisted__MatchData_3491;
        Bool hoisted__Bool_3492 = 0;
        (void)hoisted__Bool_3492;
        MatchData_delete(hoisted__MatchData_3491, hoisted__Bool_3492);
    }
    U64 hoisted__U64_3523 = 1ULL;
    (void)hoisted__U64_3523;
    Bool hoisted__Bool_3524 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3524;
    if (hoisted__Bool_3524) {
        CaptureBlockData *hoisted__CaptureBlockData_3493 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__CaptureBlockData_3493;
        (void)hoisted__CaptureBlockData_3493;
        Bool hoisted__Bool_3494 = 0;
        (void)hoisted__Bool_3494;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3493, hoisted__Bool_3494);
    }
    U64 hoisted__U64_3525 = 1ULL;
    (void)hoisted__U64_3525;
    Bool hoisted__Bool_3526 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3526;
    if (hoisted__Bool_3526) {
        CaptureBlockData *hoisted__CaptureBlockData_3495 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__CaptureBlockData_3495;
        (void)hoisted__CaptureBlockData_3495;
        Bool hoisted__Bool_3496 = 0;
        (void)hoisted__Bool_3496;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3495, hoisted__Bool_3496);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U64 hoisted__U64_3790 = 1ULL;
    (void)hoisted__U64_3790;
    Bool hoisted__Bool_3791 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3791;
    if (hoisted__Bool_3791) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U64 hoisted__U64_3792 = 1ULL;
    (void)hoisted__U64_3792;
    Bool hoisted__Bool_3793 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3793;
    if (hoisted__Bool_3793) {
        Literal *_clone_payload_Literal_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3762 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3762;
        NodeType *hoisted__NodeType_3763 = NodeType_Literal(hoisted__Literal_3762);
        (void)hoisted__NodeType_3763;
        { NodeType * _ret_val = hoisted__NodeType_3763;
                return _ret_val; }
    }
    U64 hoisted__U64_3794 = 1ULL;
    (void)hoisted__U64_3794;
    Bool hoisted__Bool_3795 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3795;
    if (hoisted__Bool_3795) {
        IdentData *_clone_payload_Ident_2 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3764 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3764;
        NodeType *hoisted__NodeType_3765 = NodeType_Ident(hoisted__IdentData_3764);
        (void)hoisted__NodeType_3765;
        { NodeType * _ret_val = hoisted__NodeType_3765;
                return _ret_val; }
    }
    U64 hoisted__U64_3796 = 1ULL;
    (void)hoisted__U64_3796;
    Bool hoisted__Bool_3797 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3797;
    if (hoisted__Bool_3797) {
        Declaration *_clone_payload_Decl_3 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3766 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3766;
        NodeType *hoisted__NodeType_3767 = NodeType_Decl(hoisted__Declaration_3766);
        (void)hoisted__NodeType_3767;
        { NodeType * _ret_val = hoisted__NodeType_3767;
                return _ret_val; }
    }
    U64 hoisted__U64_3798 = 1ULL;
    (void)hoisted__U64_3798;
    Bool hoisted__Bool_3799 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3799;
    if (hoisted__Bool_3799) {
        AssignData *_clone_payload_Assign_4 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3768 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3768;
        NodeType *hoisted__NodeType_3769 = NodeType_Assign(hoisted__AssignData_3768);
        (void)hoisted__NodeType_3769;
        { NodeType * _ret_val = hoisted__NodeType_3769;
                return _ret_val; }
    }
    U64 hoisted__U64_3800 = 1ULL;
    (void)hoisted__U64_3800;
    Bool hoisted__Bool_3801 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3801;
    if (hoisted__Bool_3801) {
        FCallData *_clone_payload_FCall_5 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3770 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3770;
        NodeType *hoisted__NodeType_3771 = NodeType_FCall(hoisted__FCallData_3770);
        (void)hoisted__NodeType_3771;
        { NodeType * _ret_val = hoisted__NodeType_3771;
                return _ret_val; }
    }
    U64 hoisted__U64_3802 = 1ULL;
    (void)hoisted__U64_3802;
    Bool hoisted__Bool_3803 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3803;
    if (hoisted__Bool_3803) {
        FunctionDef *_clone_payload_FuncDef_6 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3772 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3772;
        NodeType *hoisted__NodeType_3773 = NodeType_FuncDef(hoisted__FunctionDef_3772);
        (void)hoisted__NodeType_3773;
        { NodeType * _ret_val = hoisted__NodeType_3773;
                return _ret_val; }
    }
    U64 hoisted__U64_3804 = 1ULL;
    (void)hoisted__U64_3804;
    Bool hoisted__Bool_3805 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3805;
    if (hoisted__Bool_3805) {
        StructDef *_clone_payload_StructDef_7 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3774 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3774;
        NodeType *hoisted__NodeType_3775 = NodeType_StructDef(hoisted__StructDef_3774);
        (void)hoisted__NodeType_3775;
        { NodeType * _ret_val = hoisted__NodeType_3775;
                return _ret_val; }
    }
    U64 hoisted__U64_3806 = 1ULL;
    (void)hoisted__U64_3806;
    Bool hoisted__Bool_3807 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3807;
    if (hoisted__Bool_3807) {
        EnumDef *_clone_payload_EnumDef_8 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3776 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3776;
        NodeType *hoisted__NodeType_3777 = NodeType_EnumDef(hoisted__EnumDef_3776);
        (void)hoisted__NodeType_3777;
        { NodeType * _ret_val = hoisted__NodeType_3777;
                return _ret_val; }
    }
    U64 hoisted__U64_3808 = 1ULL;
    (void)hoisted__U64_3808;
    Bool hoisted__Bool_3809 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3809;
    if (hoisted__Bool_3809) {
        FieldAccessData *_clone_payload_FieldAccess_9 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3778 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3778;
        NodeType *hoisted__NodeType_3779 = NodeType_FieldAccess(hoisted__FieldAccessData_3778);
        (void)hoisted__NodeType_3779;
        { NodeType * _ret_val = hoisted__NodeType_3779;
                return _ret_val; }
    }
    U64 hoisted__U64_3810 = 1ULL;
    (void)hoisted__U64_3810;
    Bool hoisted__Bool_3811 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3811;
    if (hoisted__Bool_3811) {
        FieldAssignData *_clone_payload_FieldAssign_10 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3780 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3780;
        NodeType *hoisted__NodeType_3781 = NodeType_FieldAssign(hoisted__FieldAssignData_3780);
        (void)hoisted__NodeType_3781;
        { NodeType * _ret_val = hoisted__NodeType_3781;
                return _ret_val; }
    }
    U64 hoisted__U64_3812 = 1ULL;
    (void)hoisted__U64_3812;
    Bool hoisted__Bool_3813 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3813;
    if (hoisted__Bool_3813) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U64 hoisted__U64_3814 = 1ULL;
    (void)hoisted__U64_3814;
    Bool hoisted__Bool_3815 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3815;
    if (hoisted__Bool_3815) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U64 hoisted__U64_3816 = 1ULL;
    (void)hoisted__U64_3816;
    Bool hoisted__Bool_3817 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3817;
    if (hoisted__Bool_3817) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U64 hoisted__U64_3818 = 1ULL;
    (void)hoisted__U64_3818;
    Bool hoisted__Bool_3819 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3819;
    if (hoisted__Bool_3819) {
        ForInData *_clone_payload_ForIn_14 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3782 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3782;
        NodeType *hoisted__NodeType_3783 = NodeType_ForIn(hoisted__ForInData_3782);
        (void)hoisted__NodeType_3783;
        { NodeType * _ret_val = hoisted__NodeType_3783;
                return _ret_val; }
    }
    U64 hoisted__U64_3820 = 1ULL;
    (void)hoisted__U64_3820;
    Bool hoisted__Bool_3821 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3821;
    if (hoisted__Bool_3821) {
        Str *_clone_payload_NamedArg_15 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3784 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3784;
        NodeType *hoisted__NodeType_3785 = NodeType_NamedArg(hoisted__Str_3784);
        (void)hoisted__NodeType_3785;
        { NodeType * _ret_val = hoisted__NodeType_3785;
                return _ret_val; }
    }
    U64 hoisted__U64_3822 = 1ULL;
    (void)hoisted__U64_3822;
    Bool hoisted__Bool_3823 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3823;
    if (hoisted__Bool_3823) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U64 hoisted__U64_3824 = 1ULL;
    (void)hoisted__U64_3824;
    Bool hoisted__Bool_3825 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3825;
    if (hoisted__Bool_3825) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U64 hoisted__U64_3826 = 1ULL;
    (void)hoisted__U64_3826;
    Bool hoisted__Bool_3827 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3827;
    if (hoisted__Bool_3827) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U64 hoisted__U64_3828 = 1ULL;
    (void)hoisted__U64_3828;
    Bool hoisted__Bool_3829 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3829;
    if (hoisted__Bool_3829) {
        MatchData *_clone_payload_Match_19 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3786 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3786;
        NodeType *hoisted__NodeType_3787 = NodeType_Match(hoisted__MatchData_3786);
        (void)hoisted__NodeType_3787;
        { NodeType * _ret_val = hoisted__NodeType_3787;
                return _ret_val; }
    }
    U64 hoisted__U64_3830 = 1ULL;
    (void)hoisted__U64_3830;
    Bool hoisted__Bool_3831 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3831;
    if (hoisted__Bool_3831) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U64 hoisted__U64_3832 = 1ULL;
    (void)hoisted__U64_3832;
    Bool hoisted__Bool_3833 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3833;
    if (hoisted__Bool_3833) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U64 hoisted__U64_3834 = 1ULL;
    (void)hoisted__U64_3834;
    Bool hoisted__Bool_3835 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3835;
    if (hoisted__Bool_3835) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U64 hoisted__U64_3836 = 1ULL;
    (void)hoisted__U64_3836;
    Bool hoisted__Bool_3837 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3837;
    if (hoisted__Bool_3837) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U64 hoisted__U64_3838 = 1ULL;
    (void)hoisted__U64_3838;
    Bool hoisted__Bool_3839 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3839;
    if (hoisted__Bool_3839) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U64 hoisted__U64_3840 = 1ULL;
    (void)hoisted__U64_3840;
    Bool hoisted__Bool_3841 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3841;
    if (hoisted__Bool_3841) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3788 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3788;
        NodeType *hoisted__NodeType_3789 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3788);
        (void)hoisted__NodeType_3789;
        { NodeType * _ret_val = hoisted__NodeType_3789;
                return _ret_val; }
    }
    U64 hoisted__U64_3842 = 1ULL;
    (void)hoisted__U64_3842;
    Bool hoisted__Bool_3843 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3843;
    if (hoisted__Bool_3843) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    CaptureBlockData *_clone_payload_BodyValue_27 = ((void *)((U8 *)(self) + sizeof(void *)));
    (void)_clone_payload_BodyValue_27;
    (void)_clone_payload_BodyValue_27;
    CaptureBlockData *hoisted__CaptureBlockData_3844 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
    (void)hoisted__CaptureBlockData_3844;
    NodeType *hoisted__NodeType_3845 = NodeType_BodyValue(hoisted__CaptureBlockData_3844);
    (void)hoisted__NodeType_3845;
    return hoisted__NodeType_3845;
    __builtin_unreachable();
}

U64 NodeType_size(void) {
    U64 hoisted__U64_3846 = 200ULL;
    (void)hoisted__U64_3846;
    return hoisted__U64_3846;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3847 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3847;
    if (hoisted__Bool_3847) {
        return;
    }
    Bool hoisted__Bool_3848 = 0;
    (void)hoisted__Bool_3848;
    NodeType_delete(&self->node_type, hoisted__Bool_3848);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3898 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3898->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3898->children = *_ca; free(_ca); }
    hoisted__Expr_3898->line = line;
    hoisted__Expr_3898->col = col;
    (void)hoisted__Expr_3898;
    return hoisted__Expr_3898;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3907 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3907->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3907->children = *_ca; free(_ca); }
    hoisted__Expr_3907->line = self->line;
    hoisted__Expr_3907->col = self->col;
    (void)hoisted__Expr_3907;
    return hoisted__Expr_3907;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U64 hoisted__U64_3908 = 0ULL;
    (void)hoisted__U64_3908;
    U64 hoisted__U64_3909 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3908); });
    (void)hoisted__U64_3909;
    return hoisted__U64_3909;
    __builtin_unreachable();
}

U64 Expr_size(void) {
    U64 hoisted__U64_3910 = 232ULL;
    (void)hoisted__U64_3910;
    return hoisted__U64_3910;
    __builtin_unreachable();
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_5303 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_5303->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_5303->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_5303;
    return hoisted__Map__I64_Str_5303;
    __builtin_unreachable();
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_5416 = 0;
    (void)hoisted__Bool_5416;
    Vec__I64_delete(&self->keys, hoisted__Bool_5416);
    Bool hoisted__Bool_5417 = 0;
    (void)hoisted__Bool_5417;
    Vec__Str_delete(&self->values, hoisted__Bool_5417);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_5418 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_5418->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_5418->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_5418;
    return hoisted__Map__I64_Str_5418;
    __builtin_unreachable();
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U64 hoisted__U64_5419 = 0ULL;
    (void)hoisted__U64_5419;
    U64 hoisted__U64_5420 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_5419); });
    (void)hoisted__U64_5420;
    return hoisted__U64_5420;
    __builtin_unreachable();
}

U64 Map__I64_Str_size(void) {
    U64 hoisted__U64_5421 = 48ULL;
    (void)hoisted__U64_5421;
    return hoisted__U64_5421;
    __builtin_unreachable();
}

Vec__Bool * Vec__Bool_new(void) {
    U64 hoisted__U64_5422 = 1ULL;
    (void)hoisted__U64_5422;
    U64 hoisted__U64_5423 = (U64)(hoisted__U64_5422);
    (void)hoisted__U64_5423;
    void * hoisted__v_5424 = malloc(hoisted__U64_5423);
    (void)hoisted__v_5424;
    U64 hoisted__U64_5425 = 0ULL;
    (void)hoisted__U64_5425;
    I64 hoisted__I64_5426 = 1;
    (void)hoisted__I64_5426;
    Vec__Bool *hoisted__Vec__Bool_5427 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5427->data = hoisted__v_5424;
    hoisted__Vec__Bool_5427->count = hoisted__U64_5425;
    hoisted__Vec__Bool_5427->cap = hoisted__I64_5426;
    (void)hoisted__Vec__Bool_5427;
    return hoisted__Vec__Bool_5427;
    __builtin_unreachable();
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U64 _re_U64_5437 = self->count;
        (void)_re_U64_5437;
        U64 _rc_U64_5437 = 0ULL;
        (void)_rc_U64_5437;
        Bool hoisted__Bool_5450 = ((Bool)(_rc_U64_5437 <= _re_U64_5437));
        (void)hoisted__Bool_5450;
        if (hoisted__Bool_5450) {
            while (1) {
                Bool _wcond_Bool_5438 = ((Bool)(_rc_U64_5437 < _re_U64_5437));
                (void)_wcond_Bool_5438;
                if (_wcond_Bool_5438) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5437);
                (++_rc_U64_5437);
                U64 hoisted__U64_5439 = 1ULL;
                (void)hoisted__U64_5439;
                U64 hoisted__U64_5440 = ((U64)(i * hoisted__U64_5439));
                (void)hoisted__U64_5440;
                U64 hoisted__U64_5441 = (U64)(hoisted__U64_5440);
                (void)hoisted__U64_5441;
                Bool *hoisted__Bool_5442 = ((void *)((U8 *)(self->data) + (hoisted__U64_5441)));
                (void)hoisted__Bool_5442;
                (void)hoisted__Bool_5442;
                Bool hoisted__Bool_5443 = 0;
                (void)hoisted__Bool_5443;
                Bool_delete(hoisted__Bool_5442, hoisted__Bool_5443);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5444 = ((Bool)(_rc_U64_5437 > _re_U64_5437));
                (void)_wcond_Bool_5444;
                if (_wcond_Bool_5444) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5437);
                (--_rc_U64_5437);
                U64 hoisted__U64_5445 = 1ULL;
                (void)hoisted__U64_5445;
                U64 hoisted__U64_5446 = ((U64)(i * hoisted__U64_5445));
                (void)hoisted__U64_5446;
                U64 hoisted__U64_5447 = (U64)(hoisted__U64_5446);
                (void)hoisted__U64_5447;
                Bool *hoisted__Bool_5448 = ((void *)((U8 *)(self->data) + (hoisted__U64_5447)));
                (void)hoisted__Bool_5448;
                (void)hoisted__Bool_5448;
                Bool hoisted__Bool_5449 = 0;
                (void)hoisted__Bool_5449;
                Bool_delete(hoisted__Bool_5448, hoisted__Bool_5449);
            }
        }
    }
    U64 hoisted__U64_5451 = 0ULL;
    (void)hoisted__U64_5451;
    self->count = hoisted__U64_5451;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U64 hoisted__U64_5721 = 1ULL;
    (void)hoisted__U64_5721;
    U64 hoisted__U64_5722 = ((U64)(self->cap * hoisted__U64_5721));
    (void)hoisted__U64_5722;
    U64 hoisted__U64_5723 = (U64)(hoisted__U64_5722);
    (void)hoisted__U64_5723;
    U8 *new_data = malloc(hoisted__U64_5723);
    {
        U64 _re_U64_5693 = self->count;
        (void)_re_U64_5693;
        U64 _rc_U64_5693 = 0ULL;
        (void)_rc_U64_5693;
        Bool hoisted__Bool_5720 = ((Bool)(_rc_U64_5693 <= _re_U64_5693));
        (void)hoisted__Bool_5720;
        if (hoisted__Bool_5720) {
            while (1) {
                Bool _wcond_Bool_5694 = ((Bool)(_rc_U64_5693 < _re_U64_5693));
                (void)_wcond_Bool_5694;
                if (_wcond_Bool_5694) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5693);
                (++_rc_U64_5693);
                U64 hoisted__U64_5695 = 1ULL;
                (void)hoisted__U64_5695;
                U64 hoisted__U64_5696 = ((U64)(i * hoisted__U64_5695));
                (void)hoisted__U64_5696;
                U64 hoisted__U64_5697 = (U64)(hoisted__U64_5696);
                (void)hoisted__U64_5697;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5697)));
                Bool cloned = (DEREF(src));
                U64 hoisted__U64_5698 = 1ULL;
                (void)hoisted__U64_5698;
                U64 hoisted__U64_5699 = ((U64)(i * hoisted__U64_5698));
                (void)hoisted__U64_5699;
                U64 hoisted__U64_5700 = (U64)(hoisted__U64_5699);
                (void)hoisted__U64_5700;
                U64 hoisted__U64_5701 = 1ULL;
                (void)hoisted__U64_5701;
                void *hoisted__v_5702 = ((void *)((U8 *)(new_data) + (hoisted__U64_5700)));
                (void)hoisted__v_5702;
                (void)hoisted__v_5702;
                U64 hoisted__U64_5703 = (U64)(hoisted__U64_5701);
                (void)hoisted__U64_5703;
                memcpy(hoisted__v_5702, &cloned, hoisted__U64_5703);
                U64 hoisted__U64_5704 = 1ULL;
                (void)hoisted__U64_5704;
                I32 hoisted__I32_5705 = 0;
                (void)hoisted__I32_5705;
                U64 hoisted__U64_5706 = (U64)(hoisted__U64_5704);
                (void)hoisted__U64_5706;
                memset(&cloned, hoisted__I32_5705, hoisted__U64_5706);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5707 = ((Bool)(_rc_U64_5693 > _re_U64_5693));
                (void)_wcond_Bool_5707;
                if (_wcond_Bool_5707) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5693);
                (--_rc_U64_5693);
                U64 hoisted__U64_5708 = 1ULL;
                (void)hoisted__U64_5708;
                U64 hoisted__U64_5709 = ((U64)(i * hoisted__U64_5708));
                (void)hoisted__U64_5709;
                U64 hoisted__U64_5710 = (U64)(hoisted__U64_5709);
                (void)hoisted__U64_5710;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5710)));
                Bool cloned = (DEREF(src));
                U64 hoisted__U64_5711 = 1ULL;
                (void)hoisted__U64_5711;
                U64 hoisted__U64_5712 = ((U64)(i * hoisted__U64_5711));
                (void)hoisted__U64_5712;
                U64 hoisted__U64_5713 = (U64)(hoisted__U64_5712);
                (void)hoisted__U64_5713;
                U64 hoisted__U64_5714 = 1ULL;
                (void)hoisted__U64_5714;
                void *hoisted__v_5715 = ((void *)((U8 *)(new_data) + (hoisted__U64_5713)));
                (void)hoisted__v_5715;
                (void)hoisted__v_5715;
                U64 hoisted__U64_5716 = (U64)(hoisted__U64_5714);
                (void)hoisted__U64_5716;
                memcpy(hoisted__v_5715, &cloned, hoisted__U64_5716);
                U64 hoisted__U64_5717 = 1ULL;
                (void)hoisted__U64_5717;
                I32 hoisted__I32_5718 = 0;
                (void)hoisted__I32_5718;
                U64 hoisted__U64_5719 = (U64)(hoisted__U64_5717);
                (void)hoisted__U64_5719;
                memset(&cloned, hoisted__I32_5718, hoisted__U64_5719);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5724 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5724->data = new_data;
    hoisted__Vec__Bool_5724->count = self->count;
    hoisted__Vec__Bool_5724->cap = self->cap;
    (void)hoisted__Vec__Bool_5724;
    return hoisted__Vec__Bool_5724;
    __builtin_unreachable();
}

U64 Vec__Bool_size(void) {
    U64 hoisted__U64_5725 = 24ULL;
    (void)hoisted__U64_5725;
    return hoisted__U64_5725;
    __builtin_unreachable();
}

Vec__I64 * Vec__I64_new(void) {
    U64 hoisted__U64_5726 = 8ULL;
    (void)hoisted__U64_5726;
    U64 hoisted__U64_5727 = (U64)(hoisted__U64_5726);
    (void)hoisted__U64_5727;
    void * hoisted__v_5728 = malloc(hoisted__U64_5727);
    (void)hoisted__v_5728;
    U64 hoisted__U64_5729 = 0ULL;
    (void)hoisted__U64_5729;
    I64 hoisted__I64_5730 = 1;
    (void)hoisted__I64_5730;
    Vec__I64 *hoisted__Vec__I64_5731 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5731->data = hoisted__v_5728;
    hoisted__Vec__I64_5731->count = hoisted__U64_5729;
    hoisted__Vec__I64_5731->cap = hoisted__I64_5730;
    (void)hoisted__Vec__I64_5731;
    return hoisted__Vec__I64_5731;
    __builtin_unreachable();
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U64 _re_U64_5741 = self->count;
        (void)_re_U64_5741;
        U64 _rc_U64_5741 = 0ULL;
        (void)_rc_U64_5741;
        Bool hoisted__Bool_5754 = ((Bool)(_rc_U64_5741 <= _re_U64_5741));
        (void)hoisted__Bool_5754;
        if (hoisted__Bool_5754) {
            while (1) {
                Bool _wcond_Bool_5742 = ((Bool)(_rc_U64_5741 < _re_U64_5741));
                (void)_wcond_Bool_5742;
                if (_wcond_Bool_5742) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5741);
                (++_rc_U64_5741);
                U64 hoisted__U64_5743 = 8ULL;
                (void)hoisted__U64_5743;
                U64 hoisted__U64_5744 = ((U64)(i * hoisted__U64_5743));
                (void)hoisted__U64_5744;
                U64 hoisted__U64_5745 = (U64)(hoisted__U64_5744);
                (void)hoisted__U64_5745;
                I64 *hoisted__I64_5746 = ((void *)((U8 *)(self->data) + (hoisted__U64_5745)));
                (void)hoisted__I64_5746;
                (void)hoisted__I64_5746;
                Bool hoisted__Bool_5747 = 0;
                (void)hoisted__Bool_5747;
                I64_delete(hoisted__I64_5746, hoisted__Bool_5747);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5748 = ((Bool)(_rc_U64_5741 > _re_U64_5741));
                (void)_wcond_Bool_5748;
                if (_wcond_Bool_5748) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5741);
                (--_rc_U64_5741);
                U64 hoisted__U64_5749 = 8ULL;
                (void)hoisted__U64_5749;
                U64 hoisted__U64_5750 = ((U64)(i * hoisted__U64_5749));
                (void)hoisted__U64_5750;
                U64 hoisted__U64_5751 = (U64)(hoisted__U64_5750);
                (void)hoisted__U64_5751;
                I64 *hoisted__I64_5752 = ((void *)((U8 *)(self->data) + (hoisted__U64_5751)));
                (void)hoisted__I64_5752;
                (void)hoisted__I64_5752;
                Bool hoisted__Bool_5753 = 0;
                (void)hoisted__Bool_5753;
                I64_delete(hoisted__I64_5752, hoisted__Bool_5753);
            }
        }
    }
    U64 hoisted__U64_5755 = 0ULL;
    (void)hoisted__U64_5755;
    self->count = hoisted__U64_5755;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U64 hoisted__U64_6025 = 8ULL;
    (void)hoisted__U64_6025;
    U64 hoisted__U64_6026 = ((U64)(self->cap * hoisted__U64_6025));
    (void)hoisted__U64_6026;
    U64 hoisted__U64_6027 = (U64)(hoisted__U64_6026);
    (void)hoisted__U64_6027;
    U8 *new_data = malloc(hoisted__U64_6027);
    {
        U64 _re_U64_5997 = self->count;
        (void)_re_U64_5997;
        U64 _rc_U64_5997 = 0ULL;
        (void)_rc_U64_5997;
        Bool hoisted__Bool_6024 = ((Bool)(_rc_U64_5997 <= _re_U64_5997));
        (void)hoisted__Bool_6024;
        if (hoisted__Bool_6024) {
            while (1) {
                Bool _wcond_Bool_5998 = ((Bool)(_rc_U64_5997 < _re_U64_5997));
                (void)_wcond_Bool_5998;
                if (_wcond_Bool_5998) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5997);
                (++_rc_U64_5997);
                U64 hoisted__U64_5999 = 8ULL;
                (void)hoisted__U64_5999;
                U64 hoisted__U64_6000 = ((U64)(i * hoisted__U64_5999));
                (void)hoisted__U64_6000;
                U64 hoisted__U64_6001 = (U64)(hoisted__U64_6000);
                (void)hoisted__U64_6001;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6001)));
                I64 cloned = (DEREF(src));
                U64 hoisted__U64_6002 = 8ULL;
                (void)hoisted__U64_6002;
                U64 hoisted__U64_6003 = ((U64)(i * hoisted__U64_6002));
                (void)hoisted__U64_6003;
                U64 hoisted__U64_6004 = (U64)(hoisted__U64_6003);
                (void)hoisted__U64_6004;
                U64 hoisted__U64_6005 = 8ULL;
                (void)hoisted__U64_6005;
                void *hoisted__v_6006 = ((void *)((U8 *)(new_data) + (hoisted__U64_6004)));
                (void)hoisted__v_6006;
                (void)hoisted__v_6006;
                U64 hoisted__U64_6007 = (U64)(hoisted__U64_6005);
                (void)hoisted__U64_6007;
                memcpy(hoisted__v_6006, &cloned, hoisted__U64_6007);
                U64 hoisted__U64_6008 = 8ULL;
                (void)hoisted__U64_6008;
                I32 hoisted__I32_6009 = 0;
                (void)hoisted__I32_6009;
                U64 hoisted__U64_6010 = (U64)(hoisted__U64_6008);
                (void)hoisted__U64_6010;
                memset(&cloned, hoisted__I32_6009, hoisted__U64_6010);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6011 = ((Bool)(_rc_U64_5997 > _re_U64_5997));
                (void)_wcond_Bool_6011;
                if (_wcond_Bool_6011) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5997);
                (--_rc_U64_5997);
                U64 hoisted__U64_6012 = 8ULL;
                (void)hoisted__U64_6012;
                U64 hoisted__U64_6013 = ((U64)(i * hoisted__U64_6012));
                (void)hoisted__U64_6013;
                U64 hoisted__U64_6014 = (U64)(hoisted__U64_6013);
                (void)hoisted__U64_6014;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6014)));
                I64 cloned = (DEREF(src));
                U64 hoisted__U64_6015 = 8ULL;
                (void)hoisted__U64_6015;
                U64 hoisted__U64_6016 = ((U64)(i * hoisted__U64_6015));
                (void)hoisted__U64_6016;
                U64 hoisted__U64_6017 = (U64)(hoisted__U64_6016);
                (void)hoisted__U64_6017;
                U64 hoisted__U64_6018 = 8ULL;
                (void)hoisted__U64_6018;
                void *hoisted__v_6019 = ((void *)((U8 *)(new_data) + (hoisted__U64_6017)));
                (void)hoisted__v_6019;
                (void)hoisted__v_6019;
                U64 hoisted__U64_6020 = (U64)(hoisted__U64_6018);
                (void)hoisted__U64_6020;
                memcpy(hoisted__v_6019, &cloned, hoisted__U64_6020);
                U64 hoisted__U64_6021 = 8ULL;
                (void)hoisted__U64_6021;
                I32 hoisted__I32_6022 = 0;
                (void)hoisted__I32_6022;
                U64 hoisted__U64_6023 = (U64)(hoisted__U64_6021);
                (void)hoisted__U64_6023;
                memset(&cloned, hoisted__I32_6022, hoisted__U64_6023);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6028 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6028->data = new_data;
    hoisted__Vec__I64_6028->count = self->count;
    hoisted__Vec__I64_6028->cap = self->cap;
    (void)hoisted__Vec__I64_6028;
    return hoisted__Vec__I64_6028;
    __builtin_unreachable();
}

U64 Vec__I64_size(void) {
    U64 hoisted__U64_6029 = 24ULL;
    (void)hoisted__U64_6029;
    return hoisted__U64_6029;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U64 hoisted__U64_6334 = 144ULL;
    (void)hoisted__U64_6334;
    U64 hoisted__U64_6335 = (U64)(hoisted__U64_6334);
    (void)hoisted__U64_6335;
    void * hoisted__v_6336 = malloc(hoisted__U64_6335);
    (void)hoisted__v_6336;
    U64 hoisted__U64_6337 = 0ULL;
    (void)hoisted__U64_6337;
    I64 hoisted__I64_6338 = 1;
    (void)hoisted__I64_6338;
    Vec__Declaration *hoisted__Vec__Declaration_6339 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6339->data = hoisted__v_6336;
    hoisted__Vec__Declaration_6339->count = hoisted__U64_6337;
    hoisted__Vec__Declaration_6339->cap = hoisted__I64_6338;
    (void)hoisted__Vec__Declaration_6339;
    return hoisted__Vec__Declaration_6339;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U64 _re_U64_6349 = self->count;
        (void)_re_U64_6349;
        U64 _rc_U64_6349 = 0ULL;
        (void)_rc_U64_6349;
        Bool hoisted__Bool_6362 = ((Bool)(_rc_U64_6349 <= _re_U64_6349));
        (void)hoisted__Bool_6362;
        if (hoisted__Bool_6362) {
            while (1) {
                Bool _wcond_Bool_6350 = ((Bool)(_rc_U64_6349 < _re_U64_6349));
                (void)_wcond_Bool_6350;
                if (_wcond_Bool_6350) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6349);
                (++_rc_U64_6349);
                U64 hoisted__U64_6351 = 144ULL;
                (void)hoisted__U64_6351;
                U64 hoisted__U64_6352 = ((U64)(i * hoisted__U64_6351));
                (void)hoisted__U64_6352;
                U64 hoisted__U64_6353 = (U64)(hoisted__U64_6352);
                (void)hoisted__U64_6353;
                Declaration *hoisted__Declaration_6354 = ((void *)((U8 *)(self->data) + (hoisted__U64_6353)));
                (void)hoisted__Declaration_6354;
                (void)hoisted__Declaration_6354;
                Bool hoisted__Bool_6355 = 0;
                (void)hoisted__Bool_6355;
                Declaration_delete(hoisted__Declaration_6354, hoisted__Bool_6355);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6356 = ((Bool)(_rc_U64_6349 > _re_U64_6349));
                (void)_wcond_Bool_6356;
                if (_wcond_Bool_6356) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6349);
                (--_rc_U64_6349);
                U64 hoisted__U64_6357 = 144ULL;
                (void)hoisted__U64_6357;
                U64 hoisted__U64_6358 = ((U64)(i * hoisted__U64_6357));
                (void)hoisted__U64_6358;
                U64 hoisted__U64_6359 = (U64)(hoisted__U64_6358);
                (void)hoisted__U64_6359;
                Declaration *hoisted__Declaration_6360 = ((void *)((U8 *)(self->data) + (hoisted__U64_6359)));
                (void)hoisted__Declaration_6360;
                (void)hoisted__Declaration_6360;
                Bool hoisted__Bool_6361 = 0;
                (void)hoisted__Bool_6361;
                Declaration_delete(hoisted__Declaration_6360, hoisted__Bool_6361);
            }
        }
    }
    U64 hoisted__U64_6363 = 0ULL;
    (void)hoisted__U64_6363;
    self->count = hoisted__U64_6363;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U64 hoisted__U64_6633 = 144ULL;
    (void)hoisted__U64_6633;
    U64 hoisted__U64_6634 = ((U64)(self->cap * hoisted__U64_6633));
    (void)hoisted__U64_6634;
    U64 hoisted__U64_6635 = (U64)(hoisted__U64_6634);
    (void)hoisted__U64_6635;
    U8 *new_data = malloc(hoisted__U64_6635);
    {
        U64 _re_U64_6605 = self->count;
        (void)_re_U64_6605;
        U64 _rc_U64_6605 = 0ULL;
        (void)_rc_U64_6605;
        Bool hoisted__Bool_6632 = ((Bool)(_rc_U64_6605 <= _re_U64_6605));
        (void)hoisted__Bool_6632;
        if (hoisted__Bool_6632) {
            while (1) {
                Bool _wcond_Bool_6606 = ((Bool)(_rc_U64_6605 < _re_U64_6605));
                (void)_wcond_Bool_6606;
                if (_wcond_Bool_6606) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6605);
                (++_rc_U64_6605);
                U64 hoisted__U64_6607 = 144ULL;
                (void)hoisted__U64_6607;
                U64 hoisted__U64_6608 = ((U64)(i * hoisted__U64_6607));
                (void)hoisted__U64_6608;
                U64 hoisted__U64_6609 = (U64)(hoisted__U64_6608);
                (void)hoisted__U64_6609;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6609)));
                Declaration *cloned = Declaration_clone(src);
                U64 hoisted__U64_6610 = 144ULL;
                (void)hoisted__U64_6610;
                U64 hoisted__U64_6611 = ((U64)(i * hoisted__U64_6610));
                (void)hoisted__U64_6611;
                U64 hoisted__U64_6612 = (U64)(hoisted__U64_6611);
                (void)hoisted__U64_6612;
                U64 hoisted__U64_6613 = 144ULL;
                (void)hoisted__U64_6613;
                void *hoisted__v_6614 = ((void *)((U8 *)(new_data) + (hoisted__U64_6612)));
                (void)hoisted__v_6614;
                (void)hoisted__v_6614;
                U64 hoisted__U64_6615 = (U64)(hoisted__U64_6613);
                (void)hoisted__U64_6615;
                memcpy(hoisted__v_6614, cloned, hoisted__U64_6615);
                U64 hoisted__U64_6616 = 144ULL;
                (void)hoisted__U64_6616;
                I32 hoisted__I32_6617 = 0;
                (void)hoisted__I32_6617;
                U64 hoisted__U64_6618 = (U64)(hoisted__U64_6616);
                (void)hoisted__U64_6618;
                memset(cloned, hoisted__I32_6617, hoisted__U64_6618);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6619 = ((Bool)(_rc_U64_6605 > _re_U64_6605));
                (void)_wcond_Bool_6619;
                if (_wcond_Bool_6619) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6605);
                (--_rc_U64_6605);
                U64 hoisted__U64_6620 = 144ULL;
                (void)hoisted__U64_6620;
                U64 hoisted__U64_6621 = ((U64)(i * hoisted__U64_6620));
                (void)hoisted__U64_6621;
                U64 hoisted__U64_6622 = (U64)(hoisted__U64_6621);
                (void)hoisted__U64_6622;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6622)));
                Declaration *cloned = Declaration_clone(src);
                U64 hoisted__U64_6623 = 144ULL;
                (void)hoisted__U64_6623;
                U64 hoisted__U64_6624 = ((U64)(i * hoisted__U64_6623));
                (void)hoisted__U64_6624;
                U64 hoisted__U64_6625 = (U64)(hoisted__U64_6624);
                (void)hoisted__U64_6625;
                U64 hoisted__U64_6626 = 144ULL;
                (void)hoisted__U64_6626;
                void *hoisted__v_6627 = ((void *)((U8 *)(new_data) + (hoisted__U64_6625)));
                (void)hoisted__v_6627;
                (void)hoisted__v_6627;
                U64 hoisted__U64_6628 = (U64)(hoisted__U64_6626);
                (void)hoisted__U64_6628;
                memcpy(hoisted__v_6627, cloned, hoisted__U64_6628);
                U64 hoisted__U64_6629 = 144ULL;
                (void)hoisted__U64_6629;
                I32 hoisted__I32_6630 = 0;
                (void)hoisted__I32_6630;
                U64 hoisted__U64_6631 = (U64)(hoisted__U64_6629);
                (void)hoisted__U64_6631;
                memset(cloned, hoisted__I32_6630, hoisted__U64_6631);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_6636 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6636->data = new_data;
    hoisted__Vec__Declaration_6636->count = self->count;
    hoisted__Vec__Declaration_6636->cap = self->cap;
    (void)hoisted__Vec__Declaration_6636;
    return hoisted__Vec__Declaration_6636;
    __builtin_unreachable();
}

U64 Vec__Declaration_size(void) {
    U64 hoisted__U64_6637 = 24ULL;
    (void)hoisted__U64_6637;
    return hoisted__U64_6637;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U64 hoisted__U64_6638 = 232ULL;
    (void)hoisted__U64_6638;
    U64 hoisted__U64_6639 = (U64)(hoisted__U64_6638);
    (void)hoisted__U64_6639;
    void * hoisted__v_6640 = malloc(hoisted__U64_6639);
    (void)hoisted__v_6640;
    U64 hoisted__U64_6641 = 0ULL;
    (void)hoisted__U64_6641;
    I64 hoisted__I64_6642 = 1;
    (void)hoisted__I64_6642;
    Vec__Expr *hoisted__Vec__Expr_6643 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6643->data = hoisted__v_6640;
    hoisted__Vec__Expr_6643->count = hoisted__U64_6641;
    hoisted__Vec__Expr_6643->cap = hoisted__I64_6642;
    (void)hoisted__Vec__Expr_6643;
    return hoisted__Vec__Expr_6643;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U64 _re_U64_6653 = self->count;
        (void)_re_U64_6653;
        U64 _rc_U64_6653 = 0ULL;
        (void)_rc_U64_6653;
        Bool hoisted__Bool_6666 = ((Bool)(_rc_U64_6653 <= _re_U64_6653));
        (void)hoisted__Bool_6666;
        if (hoisted__Bool_6666) {
            while (1) {
                Bool _wcond_Bool_6654 = ((Bool)(_rc_U64_6653 < _re_U64_6653));
                (void)_wcond_Bool_6654;
                if (_wcond_Bool_6654) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6653);
                (++_rc_U64_6653);
                U64 hoisted__U64_6655 = 232ULL;
                (void)hoisted__U64_6655;
                U64 hoisted__U64_6656 = ((U64)(i * hoisted__U64_6655));
                (void)hoisted__U64_6656;
                U64 hoisted__U64_6657 = (U64)(hoisted__U64_6656);
                (void)hoisted__U64_6657;
                Expr *hoisted__Expr_6658 = ((void *)((U8 *)(self->data) + (hoisted__U64_6657)));
                (void)hoisted__Expr_6658;
                (void)hoisted__Expr_6658;
                Bool hoisted__Bool_6659 = 0;
                (void)hoisted__Bool_6659;
                Expr_delete(hoisted__Expr_6658, hoisted__Bool_6659);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6660 = ((Bool)(_rc_U64_6653 > _re_U64_6653));
                (void)_wcond_Bool_6660;
                if (_wcond_Bool_6660) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6653);
                (--_rc_U64_6653);
                U64 hoisted__U64_6661 = 232ULL;
                (void)hoisted__U64_6661;
                U64 hoisted__U64_6662 = ((U64)(i * hoisted__U64_6661));
                (void)hoisted__U64_6662;
                U64 hoisted__U64_6663 = (U64)(hoisted__U64_6662);
                (void)hoisted__U64_6663;
                Expr *hoisted__Expr_6664 = ((void *)((U8 *)(self->data) + (hoisted__U64_6663)));
                (void)hoisted__Expr_6664;
                (void)hoisted__Expr_6664;
                Bool hoisted__Bool_6665 = 0;
                (void)hoisted__Bool_6665;
                Expr_delete(hoisted__Expr_6664, hoisted__Bool_6665);
            }
        }
    }
    U64 hoisted__U64_6667 = 0ULL;
    (void)hoisted__U64_6667;
    self->count = hoisted__U64_6667;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U64 hoisted__U64_6937 = 232ULL;
    (void)hoisted__U64_6937;
    U64 hoisted__U64_6938 = ((U64)(self->cap * hoisted__U64_6937));
    (void)hoisted__U64_6938;
    U64 hoisted__U64_6939 = (U64)(hoisted__U64_6938);
    (void)hoisted__U64_6939;
    U8 *new_data = malloc(hoisted__U64_6939);
    {
        U64 _re_U64_6909 = self->count;
        (void)_re_U64_6909;
        U64 _rc_U64_6909 = 0ULL;
        (void)_rc_U64_6909;
        Bool hoisted__Bool_6936 = ((Bool)(_rc_U64_6909 <= _re_U64_6909));
        (void)hoisted__Bool_6936;
        if (hoisted__Bool_6936) {
            while (1) {
                Bool _wcond_Bool_6910 = ((Bool)(_rc_U64_6909 < _re_U64_6909));
                (void)_wcond_Bool_6910;
                if (_wcond_Bool_6910) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6909);
                (++_rc_U64_6909);
                U64 hoisted__U64_6911 = 232ULL;
                (void)hoisted__U64_6911;
                U64 hoisted__U64_6912 = ((U64)(i * hoisted__U64_6911));
                (void)hoisted__U64_6912;
                U64 hoisted__U64_6913 = (U64)(hoisted__U64_6912);
                (void)hoisted__U64_6913;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6913)));
                Expr *cloned = Expr_clone(src);
                U64 hoisted__U64_6914 = 232ULL;
                (void)hoisted__U64_6914;
                U64 hoisted__U64_6915 = ((U64)(i * hoisted__U64_6914));
                (void)hoisted__U64_6915;
                U64 hoisted__U64_6916 = (U64)(hoisted__U64_6915);
                (void)hoisted__U64_6916;
                U64 hoisted__U64_6917 = 232ULL;
                (void)hoisted__U64_6917;
                void *hoisted__v_6918 = ((void *)((U8 *)(new_data) + (hoisted__U64_6916)));
                (void)hoisted__v_6918;
                (void)hoisted__v_6918;
                U64 hoisted__U64_6919 = (U64)(hoisted__U64_6917);
                (void)hoisted__U64_6919;
                memcpy(hoisted__v_6918, cloned, hoisted__U64_6919);
                U64 hoisted__U64_6920 = 232ULL;
                (void)hoisted__U64_6920;
                I32 hoisted__I32_6921 = 0;
                (void)hoisted__I32_6921;
                U64 hoisted__U64_6922 = (U64)(hoisted__U64_6920);
                (void)hoisted__U64_6922;
                memset(cloned, hoisted__I32_6921, hoisted__U64_6922);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6923 = ((Bool)(_rc_U64_6909 > _re_U64_6909));
                (void)_wcond_Bool_6923;
                if (_wcond_Bool_6923) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6909);
                (--_rc_U64_6909);
                U64 hoisted__U64_6924 = 232ULL;
                (void)hoisted__U64_6924;
                U64 hoisted__U64_6925 = ((U64)(i * hoisted__U64_6924));
                (void)hoisted__U64_6925;
                U64 hoisted__U64_6926 = (U64)(hoisted__U64_6925);
                (void)hoisted__U64_6926;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6926)));
                Expr *cloned = Expr_clone(src);
                U64 hoisted__U64_6927 = 232ULL;
                (void)hoisted__U64_6927;
                U64 hoisted__U64_6928 = ((U64)(i * hoisted__U64_6927));
                (void)hoisted__U64_6928;
                U64 hoisted__U64_6929 = (U64)(hoisted__U64_6928);
                (void)hoisted__U64_6929;
                U64 hoisted__U64_6930 = 232ULL;
                (void)hoisted__U64_6930;
                void *hoisted__v_6931 = ((void *)((U8 *)(new_data) + (hoisted__U64_6929)));
                (void)hoisted__v_6931;
                (void)hoisted__v_6931;
                U64 hoisted__U64_6932 = (U64)(hoisted__U64_6930);
                (void)hoisted__U64_6932;
                memcpy(hoisted__v_6931, cloned, hoisted__U64_6932);
                U64 hoisted__U64_6933 = 232ULL;
                (void)hoisted__U64_6933;
                I32 hoisted__I32_6934 = 0;
                (void)hoisted__I32_6934;
                U64 hoisted__U64_6935 = (U64)(hoisted__U64_6933);
                (void)hoisted__U64_6935;
                memset(cloned, hoisted__I32_6934, hoisted__U64_6935);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6940 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6940->data = new_data;
    hoisted__Vec__Expr_6940->count = self->count;
    hoisted__Vec__Expr_6940->cap = self->cap;
    (void)hoisted__Vec__Expr_6940;
    return hoisted__Vec__Expr_6940;
    __builtin_unreachable();
}

U64 Vec__Expr_size(void) {
    U64 hoisted__U64_6941 = 24ULL;
    (void)hoisted__U64_6941;
    return hoisted__U64_6941;
    __builtin_unreachable();
}

void panic(Array__Str * parts, Str * loc) {
    U64 hoisted__U64_8029 = 3ULL;
    (void)hoisted__U64_8029;
    Array__Str *_va_Array_225 = Array__Str_new(hoisted__U64_8029);
    (void)_va_Array_225;
    I64 _va_Array_225_ek = 0;
    (void)_va_Array_225_ek;
    OutOfBounds *_va_Array_225_eo = malloc(sizeof(OutOfBounds));
    _va_Array_225_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_225_eo;
    U64 hoisted__U64_8030 = 0ULL;
    (void)hoisted__U64_8030;
    Str *hoisted__Str_8031 = Str_clone(loc);
    (void)hoisted__Str_8031;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    Array__Str_set(_va_Array_225, hoisted__U64_8030, hoisted__Str_8031, &_va_Array_225_ek, _va_Array_225_eo, &_til_str_lit_145);
    Str_delete(&_til_str_lit_145, (Bool){0});
    U64 hoisted__U64_8033 = 1ULL;
    (void)hoisted__U64_8033;
    (void)_til_str_lit_146;
    (void)_til_str_lit_146;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    Array__Str_set(_va_Array_225, hoisted__U64_8033, &_til_str_lit_146, &_va_Array_225_ek, _va_Array_225_eo, &_til_str_lit_145);
    Str_delete(&_til_str_lit_145, (Bool){0});
    Array__Str *hoisted__Array__Str_8036 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_8036;
    U64 hoisted__U64_8037 = 2ULL;
    (void)hoisted__U64_8037;
    Str *hoisted__Str_8038 = format(hoisted__Array__Str_8036);
    (void)hoisted__Str_8038;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    Array__Str_set(_va_Array_225, hoisted__U64_8037, hoisted__Str_8038, &_va_Array_225_ek, _va_Array_225_eo, &_til_str_lit_145);
    OutOfBounds_delete(_va_Array_225_eo, 1);
    Str_delete(&_til_str_lit_145, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_225);
    I64 hoisted__I64_8040 = 1;
    (void)hoisted__I64_8040;
    exit(hoisted__I64_8040);
}

void UNREACHABLE(Str * loc) {
    U64 hoisted__U64_8049 = 1ULL;
    (void)hoisted__U64_8049;
    Array__Str *_va_Array_227 = Array__Str_new(hoisted__U64_8049);
    (void)_va_Array_227;
    I64 _va_Array_227_ek = 0;
    (void)_va_Array_227_ek;
    OutOfBounds *_va_Array_227_eo = malloc(sizeof(OutOfBounds));
    _va_Array_227_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_227_eo;
    U64 hoisted__U64_8050 = 0ULL;
    (void)hoisted__U64_8050;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    (void)_til_str_lit_148;
    (void)_til_str_lit_148;
    Array__Str_set(_va_Array_227, hoisted__U64_8050, &_til_str_lit_147, &_va_Array_227_ek, _va_Array_227_eo, &_til_str_lit_148);
    OutOfBounds_delete(_va_Array_227_eo, 1);
    Str_delete(&_til_str_lit_148, (Bool){0});
    panic(_va_Array_227, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_8057 = ((Bool)(!(cond)));
    (void)hoisted__Bool_8057;
    if (hoisted__Bool_8057) {
        U64 hoisted__U64_8053 = 1ULL;
        (void)hoisted__U64_8053;
        Array__Str *_va_Array_228 = Array__Str_new(hoisted__U64_8053);
        (void)_va_Array_228;
        I64 _va_Array_228_ek = 0;
        (void)_va_Array_228_ek;
        OutOfBounds *_va_Array_228_eo = malloc(sizeof(OutOfBounds));
        _va_Array_228_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_228_eo;
        U64 hoisted__U64_8054 = 0ULL;
        (void)hoisted__U64_8054;
        (void)_til_str_lit_149;
        (void)_til_str_lit_149;
        (void)_til_str_lit_150;
        (void)_til_str_lit_150;
        Array__Str_set(_va_Array_228, hoisted__U64_8054, &_til_str_lit_149, &_va_Array_228_ek, _va_Array_228_eo, &_til_str_lit_150);
        OutOfBounds_delete(_va_Array_228_eo, 1);
        Str_delete(&_til_str_lit_150, (Bool){0});
        panic(_va_Array_228, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_8067 = parts;
        (void)_fc_Array__Str_8067;
        (void)_fc_Array__Str_8067;
        U64 _fi_USize_8067 = 0ULL;
        (void)_fi_USize_8067;
        while (1) {
            U64 hoisted__U64_8069 = (_fc_Array__Str_8067->cap);
            (void)hoisted__U64_8069;
            Bool _wcond_Bool_8068 = ((Bool)(_fi_USize_8067 < hoisted__U64_8069));
            (void)_wcond_Bool_8068;
            if (_wcond_Bool_8068) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_8067->data) + ((U64)(((U64)(_fi_USize_8067 * 24ULL)))))));
            U64 hoisted__U64_8070 = 1ULL;
            (void)hoisted__U64_8070;
            U64 hoisted__U64_8071 = ((U64)(_fi_USize_8067 + hoisted__U64_8070));
            (void)hoisted__U64_8071;
            _fi_USize_8067 = hoisted__U64_8071;
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
    Range hoisted__Range_8115 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_8115;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_8115;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U64 hoisted__U64_8116 = 0ULL;
    (void)hoisted__U64_8116;
    U64 hoisted__U64_8117 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8116); });
    (void)hoisted__U64_8117;
    return hoisted__U64_8117;
    __builtin_unreachable();
}

U64 Range_size(void) {
    U64 hoisted__U64_8148 = 16ULL;
    (void)hoisted__U64_8148;
    return hoisted__U64_8148;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_8164 = 3;
    (void)hoisted__I64_8164;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    assert_eq__I64(result, hoisted__I64_8164, &_til_str_lit_153);
    Str_delete(&_til_str_lit_153, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_8172 = 15;
    (void)hoisted__I64_8172;
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    assert_eq__I64(result, hoisted__I64_8172, &_til_str_lit_154);
    Str_delete(&_til_str_lit_154, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_8180 = 26;
    (void)hoisted__I64_8180;
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    assert_eq__I64(result, hoisted__I64_8180, &_til_str_lit_155);
    Str_delete(&_til_str_lit_155, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    (void)_til_str_lit_157;
    (void)_til_str_lit_157;
    assert_eq__Str(&result, &_til_str_lit_156, &_til_str_lit_157);
    Str_delete(&_til_str_lit_156, (Bool){0});
    Str_delete(&_til_str_lit_157, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    assert_eq__Str(&r, &_til_str_lit_156, &_til_str_lit_158);
    Str_delete(&_til_str_lit_156, (Bool){0});
    Str_delete(&_til_str_lit_158, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    assert_eq__Str(&r2, &_til_str_lit_159, &_til_str_lit_160);
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&_til_str_lit_160, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    assert_eq__Str(&d, &_til_str_lit_161, &_til_str_lit_162);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_161, (Bool){0});
    Str_delete(&_til_str_lit_162, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    assert_eq__Str(&d2, &_til_str_lit_163, &_til_str_lit_164);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_163, (Bool){0});
    Str_delete(&_til_str_lit_164, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_8267 = 106;
    (void)hoisted__I64_8267;
    (void)_til_str_lit_165;
    (void)_til_str_lit_165;
    assert_eq__I64(d3, hoisted__I64_8267, &_til_str_lit_165);
    Str_delete(&_til_str_lit_165, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_168;
    (void)_til_str_lit_168;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_168);
    Str_delete(&_til_str_lit_168, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_169;
    (void)_til_str_lit_169;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_169);
    Str_delete(&_til_str_lit_169, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8870 = 8;
    (void)hoisted__I64_8870;
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert_eq__I64(result, hoisted__I64_8870, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8874 = 1;
    (void)hoisted__Bool_8874;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert(hoisted__Bool_8874, &_til_str_lit_171);
    Str_delete(&_til_str_lit_171, (Bool){0});
    Bool hoisted__Bool_8878 = 1;
    (void)hoisted__Bool_8878;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    assert(hoisted__Bool_8878, &_til_str_lit_172);
    Str_delete(&_til_str_lit_172, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    assert_eq__Str(&_til_str_lit_173, &_til_str_lit_173, &_til_str_lit_174);
    Str_delete(&_til_str_lit_173, (Bool){0});
    Str_delete(&_til_str_lit_173, (Bool){0});
    Str_delete(&_til_str_lit_174, (Bool){0});
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
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8896 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8896;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8896;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U64 hoisted__U64_8897 = 0ULL;
    (void)hoisted__U64_8897;
    U64 hoisted__U64_8898 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8897); });
    (void)hoisted__U64_8898;
    return hoisted__U64_8898;
    __builtin_unreachable();
}

U64 CfVec2_size(void) {
    U64 hoisted__U64_8929 = 16ULL;
    (void)hoisted__U64_8929;
    return hoisted__U64_8929;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8930 = 42;
    (void)hoisted__I64_8930;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__I64(v.x, hoisted__I64_8930, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
    I64 hoisted__I64_8932 = 99;
    (void)hoisted__I64_8932;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    assert_eq__I64(v.y, hoisted__I64_8932, &_til_str_lit_180);
    Str_delete(&_til_str_lit_180, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8936 = 10;
    (void)hoisted__I64_8936;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__I64(p.x, hoisted__I64_8936, &_til_str_lit_181);
    Str_delete(&_til_str_lit_181, (Bool){0});
    I64 hoisted__I64_8938 = 20;
    (void)hoisted__I64_8938;
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    assert_eq__I64(p.y, hoisted__I64_8938, &_til_str_lit_182);
    Str_delete(&_til_str_lit_182, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8945 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8945;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8945;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U64 hoisted__U64_8946 = 0ULL;
    (void)hoisted__U64_8946;
    U64 hoisted__U64_8947 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8946); });
    (void)hoisted__U64_8947;
    return hoisted__U64_8947;
    __builtin_unreachable();
}

U64 CfRect_size(void) {
    U64 hoisted__U64_8978 = 32ULL;
    (void)hoisted__U64_8978;
    return hoisted__U64_8978;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8979 = 5;
    (void)hoisted__I64_8979;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(r.top_left.x, hoisted__I64_8979, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_8981 = 10;
    (void)hoisted__I64_8981;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(r.top_left.y, hoisted__I64_8981, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    I64 hoisted__I64_8983 = 100;
    (void)hoisted__I64_8983;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8983, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    I64 hoisted__I64_8985 = 200;
    (void)hoisted__I64_8985;
    (void)_til_str_lit_189;
    (void)_til_str_lit_189;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8985, &_til_str_lit_189);
    Str_delete(&_til_str_lit_189, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8988 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8988;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8988;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U64 hoisted__U64_8989 = 0ULL;
    (void)hoisted__U64_8989;
    U64 hoisted__U64_8990 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8989); });
    (void)hoisted__U64_8990;
    return hoisted__U64_8990;
    __builtin_unreachable();
}

U64 CfVec3f_size(void) {
    U64 hoisted__U64_9033 = 12ULL;
    (void)hoisted__U64_9033;
    return hoisted__U64_9033;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_9037 = F32_to_str(v.x);
    (void)hoisted__Str_9037;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    assert_eq__Str(hoisted__Str_9037, &_til_str_lit_191, &_til_str_lit_192);
    Str_delete(hoisted__Str_9037, 1);
    Str_delete(&_til_str_lit_191, (Bool){0});
    Str_delete(&_til_str_lit_192, (Bool){0});
    Str *hoisted__Str_9040 = F32_to_str(v.y);
    (void)hoisted__Str_9040;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    assert_eq__Str(hoisted__Str_9040, &_til_str_lit_193, &_til_str_lit_194);
    Str_delete(hoisted__Str_9040, 1);
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str_delete(&_til_str_lit_194, (Bool){0});
    Str *hoisted__Str_9043 = F32_to_str(v.z);
    (void)hoisted__Str_9043;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    (void)_til_str_lit_196;
    (void)_til_str_lit_196;
    assert_eq__Str(hoisted__Str_9043, &_til_str_lit_195, &_til_str_lit_196);
    Str_delete(hoisted__Str_9043, 1);
    Str_delete(&_til_str_lit_195, (Bool){0});
    Str_delete(&_til_str_lit_196, (Bool){0});
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
    U64 hoisted__U64_9052 = 1ULL;
    (void)hoisted__U64_9052;
    Bool hoisted__Bool_9053 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_9053;
    if (hoisted__Bool_9053) {
        U64 hoisted__U64_9046 = 1ULL;
        (void)hoisted__U64_9046;
        Bool hoisted__Bool_9047 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_9047;
        { Bool _ret_val = hoisted__Bool_9047;
                return _ret_val; }
    }
    U64 hoisted__U64_9054 = 1ULL;
    (void)hoisted__U64_9054;
    Bool hoisted__Bool_9055 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_9055;
    if (hoisted__Bool_9055) {
        U64 hoisted__U64_9048 = 1ULL;
        (void)hoisted__U64_9048;
        Bool hoisted__Bool_9049 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_9049;
        { Bool _ret_val = hoisted__Bool_9049;
                return _ret_val; }
    }
    U64 hoisted__U64_9056 = 1ULL;
    (void)hoisted__U64_9056;
    Bool hoisted__Bool_9057 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_9057;
    if (hoisted__Bool_9057) {
        U64 hoisted__U64_9050 = 1ULL;
        (void)hoisted__U64_9050;
        Bool hoisted__Bool_9051 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_9051;
        { Bool _ret_val = hoisted__Bool_9051;
                return _ret_val; }
    }
    Bool hoisted__Bool_9058 = 0;
    (void)hoisted__Bool_9058;
    return hoisted__Bool_9058;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_9066 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_9066;
    if (hoisted__Bool_9066) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_9067 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_9067;
    if (hoisted__Bool_9067) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_9068 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_9068;
    if (hoisted__Bool_9068) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_9069 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_9069;
    UNREACHABLE(&hoisted__Str_9069);
    Str_delete(&hoisted__Str_9069, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

U64 Color_size(void) {
    U64 hoisted__U64_9070 = 1ULL;
    (void)hoisted__U64_9070;
    return hoisted__U64_9070;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_9071 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_9071;
    (void)_til_str_lit_200;
    (void)_til_str_lit_200;
    assert(hoisted__Bool_9071, &_til_str_lit_200);
    Str_delete(&_til_str_lit_200, (Bool){0});
    Bool hoisted__Bool_9073 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_9073;
    Bool hoisted__Bool_9074 = ((Bool)(!(hoisted__Bool_9073)));
    (void)hoisted__Bool_9074;
    (void)_til_str_lit_201;
    (void)_til_str_lit_201;
    assert(hoisted__Bool_9074, &_til_str_lit_201);
    Str_delete(&_til_str_lit_201, (Bool){0});
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
    U64 hoisted__U64_9099 = 1ULL;
    (void)hoisted__U64_9099;
    Bool hoisted__Bool_9100 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_9100;
    if (hoisted__Bool_9100) {
        I64 *hoisted__I64_9095 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__I64_9095;
        (void)hoisted__I64_9095;
        Bool hoisted__Bool_9096 = 0;
        (void)hoisted__Bool_9096;
        I64_delete(hoisted__I64_9095, hoisted__Bool_9096);
    }
    U64 hoisted__U64_9101 = 1ULL;
    (void)hoisted__U64_9101;
    Bool hoisted__Bool_9102 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_9102;
    if (hoisted__Bool_9102) {
        Str *hoisted__Str_9097 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)hoisted__Str_9097;
        (void)hoisted__Str_9097;
        Bool hoisted__Bool_9098 = 0;
        (void)hoisted__Bool_9098;
        Str_delete(hoisted__Str_9097, hoisted__Bool_9098);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U64 hoisted__U64_9136 = 1ULL;
    (void)hoisted__U64_9136;
    Bool hoisted__Bool_9137 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_9137;
    if (hoisted__Bool_9137) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_9133 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_9133;
        { Token * _ret_val = hoisted__Token_9133;
                return _ret_val; }
    }
    U64 hoisted__U64_9138 = 1ULL;
    (void)hoisted__U64_9138;
    Bool hoisted__Bool_9139 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_9139;
    if (hoisted__Bool_9139) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + sizeof(void *)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_9134 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_9134;
        Token *hoisted__Token_9135 = Token_Name(hoisted__Str_9134);
        (void)hoisted__Token_9135;
        { Token * _ret_val = hoisted__Token_9135;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

U64 Token_size(void) {
    U64 hoisted__U64_9140 = 32ULL;
    (void)hoisted__U64_9140;
    return hoisted__U64_9140;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_9142 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_9142;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_9142, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
    Bool hoisted__Bool_9144 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_9144;
    Bool hoisted__Bool_9145 = ((Bool)(!(hoisted__Bool_9144)));
    (void)hoisted__Bool_9145;
    (void)_til_str_lit_205;
    (void)_til_str_lit_205;
    assert(hoisted__Bool_9145, &_til_str_lit_205);
    Str_delete(&_til_str_lit_205, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_9147 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_9147;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_9147, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
    Bool hoisted__Bool_9149 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_9149;
    Bool hoisted__Bool_9150 = ((Bool)(!(hoisted__Bool_9149)));
    (void)hoisted__Bool_9150;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_9150, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_9154 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_9154;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_9154, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Bool hoisted__Bool_9156 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_9156;
    Bool hoisted__Bool_9157 = ((Bool)(!(hoisted__Bool_9156)));
    (void)hoisted__Bool_9157;
    (void)_til_str_lit_209;
    (void)_til_str_lit_209;
    assert(hoisted__Bool_9157, &_til_str_lit_209);
    Str_delete(&_til_str_lit_209, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_9290 = ((Bool)(a != b));
    (void)hoisted__Bool_9290;
    if (hoisted__Bool_9290) {
        U64 hoisted__U64_9274 = 5ULL;
        (void)hoisted__U64_9274;
        Array__Str *_va_Array_270 = Array__Str_new(hoisted__U64_9274);
        (void)_va_Array_270;
        I64 _va_Array_270_ek = 0;
        (void)_va_Array_270_ek;
        OutOfBounds *_va_Array_270_eo = malloc(sizeof(OutOfBounds));
        _va_Array_270_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_270_eo;
        U64 hoisted__U64_9275 = 0ULL;
        (void)hoisted__U64_9275;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_270, hoisted__U64_9275, &_til_str_lit_210, &_va_Array_270_ek, _va_Array_270_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9278 = 1ULL;
        (void)hoisted__U64_9278;
        Str *hoisted__Str_9279 = I64_to_str(a);
        (void)hoisted__Str_9279;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_270, hoisted__U64_9278, hoisted__Str_9279, &_va_Array_270_ek, _va_Array_270_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9281 = 2ULL;
        (void)hoisted__U64_9281;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_270, hoisted__U64_9281, &_til_str_lit_212, &_va_Array_270_ek, _va_Array_270_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9284 = 3ULL;
        (void)hoisted__U64_9284;
        Str *hoisted__Str_9285 = I64_to_str(b);
        (void)hoisted__Str_9285;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_270, hoisted__U64_9284, hoisted__Str_9285, &_va_Array_270_ek, _va_Array_270_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9287 = 4ULL;
        (void)hoisted__U64_9287;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_270, hoisted__U64_9287, &_til_str_lit_213, &_va_Array_270_ek, _va_Array_270_eo, &_til_str_lit_211);
        OutOfBounds_delete(_va_Array_270_eo, 1);
        Str_delete(&_til_str_lit_211, (Bool){0});
        panic(_va_Array_270, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_9307 = Str_neq(a, b);
    (void)hoisted__Bool_9307;
    if (hoisted__Bool_9307) {
        U64 hoisted__U64_9291 = 5ULL;
        (void)hoisted__U64_9291;
        Array__Str *_va_Array_271 = Array__Str_new(hoisted__U64_9291);
        (void)_va_Array_271;
        I64 _va_Array_271_ek = 0;
        (void)_va_Array_271_ek;
        OutOfBounds *_va_Array_271_eo = malloc(sizeof(OutOfBounds));
        _va_Array_271_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_271_eo;
        U64 hoisted__U64_9292 = 0ULL;
        (void)hoisted__U64_9292;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_271, hoisted__U64_9292, &_til_str_lit_210, &_va_Array_271_ek, _va_Array_271_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9295 = 1ULL;
        (void)hoisted__U64_9295;
        Str *hoisted__Str_9296 = Str_to_str(a);
        (void)hoisted__Str_9296;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_271, hoisted__U64_9295, hoisted__Str_9296, &_va_Array_271_ek, _va_Array_271_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9298 = 2ULL;
        (void)hoisted__U64_9298;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_271, hoisted__U64_9298, &_til_str_lit_212, &_va_Array_271_ek, _va_Array_271_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9301 = 3ULL;
        (void)hoisted__U64_9301;
        Str *hoisted__Str_9302 = Str_to_str(b);
        (void)hoisted__Str_9302;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_271, hoisted__U64_9301, hoisted__Str_9302, &_va_Array_271_ek, _va_Array_271_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_9304 = 4ULL;
        (void)hoisted__U64_9304;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_271, hoisted__U64_9304, &_til_str_lit_213, &_va_Array_271_ek, _va_Array_271_eo, &_til_str_lit_211);
        OutOfBounds_delete(_va_Array_271_eo, 1);
        Str_delete(&_til_str_lit_211, (Bool){0});
        panic(_va_Array_271, loc);
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
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_45;
        if (*index == 2LL) return &_til_str_lit_46;
        if (*index == 3LL) return &_til_str_lit_47;
        if (*index == 4LL) return &_til_str_lit_48;
        if (*index == 5LL) return &_til_str_lit_49;
        if (*index == 6LL) return &_til_str_lit_50;
        if (*index == 7LL) return &_til_str_lit_51;
        if (*index == 8LL) return &_til_str_lit_53;
        if (*index == 9LL) return &_til_str_lit_55;
        if (*index == 10LL) return &_til_str_lit_57;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_58;
        if (*index == 1LL) return &_til_str_lit_60;
        if (*index == 2LL) return &_til_str_lit_62;
        if (*index == 3LL) return &_til_str_lit_63;
        if (*index == 4LL) return &_til_str_lit_65;
        if (*index == 5LL) return &_til_str_lit_66;
        if (*index == 6LL) return &_til_str_lit_67;
        if (*index == 7LL) return &_til_str_lit_68;
        if (*index == 8LL) return &_til_str_lit_69;
        if (*index == 9LL) return &_til_str_lit_70;
        if (*index == 10LL) return &_til_str_lit_71;
        if (*index == 11LL) return &_til_str_lit_72;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_73;
        if (*index == 1LL) return &_til_str_lit_74;
        if (*index == 2LL) return &_til_str_lit_75;
        if (*index == 3LL) return &_til_str_lit_76;
        if (*index == 4LL) return &_til_str_lit_77;
        if (*index == 5LL) return &_til_str_lit_53;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_78;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_79;
        if (*index == 1LL) return &_til_str_lit_80;
        if (*index == 2LL) return &_til_str_lit_81;
        if (*index == 3LL) return &_til_str_lit_82;
        if (*index == 4LL) return &_til_str_lit_83;
        if (*index == 5LL) return &_til_str_lit_84;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_80;
        if (*index == 1LL) return &_til_str_lit_85;
        if (*index == 2LL) return &_til_str_lit_86;
        if (*index == 3LL) return &_til_str_lit_88;
        if (*index == 4LL) return &_til_str_lit_84;
        if (*index == 5LL) return &_til_str_lit_90;
        if (*index == 6LL) return &_til_str_lit_91;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_93;
        if (*index == 2LL) return &_til_str_lit_94;
        if (*index == 3LL) return &_til_str_lit_77;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_93;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_47;
        if (*index == 2LL) return &_til_str_lit_53;
        if (*index == 3LL) return &_til_str_lit_95;
        if (*index == 4LL) return &_til_str_lit_96;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_53;
        if (*index == 1LL) return &_til_str_lit_102;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_71;
        if (*index == 1LL) return &_til_str_lit_72;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_137;
        if (*index == 1LL) return &_til_str_lit_139;
        if (*index == 2LL) return &_til_str_lit_141;
        if (*index == 3LL) return &_til_str_lit_142;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_143;
        if (*index == 1LL) return &_til_str_lit_144;
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
        if (*index == 0LL) return &_til_str_lit_151;
        if (*index == 1LL) return &_til_str_lit_152;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_177;
        if (*index == 1LL) return &_til_str_lit_178;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_183;
        if (*index == 1LL) return &_til_str_lit_185;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_177;
        if (*index == 1LL) return &_til_str_lit_178;
        if (*index == 2LL) return &_til_str_lit_190;
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
        if (*index == 7LL) return &_til_str_lit_52;
        if (*index == 8LL) return &_til_str_lit_54;
        if (*index == 9LL) return &_til_str_lit_56;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_59;
        if (*index == 1LL) return &_til_str_lit_61;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_64;
        if (*index == 4LL) return &_til_str_lit_14;
        if (*index == 5LL) return &_til_str_lit_14;
        if (*index == 6LL) return &_til_str_lit_52;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
        if (*index == 10LL) return &_til_str_lit_61;
        if (*index == 11LL) return &_til_str_lit_6;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_10;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_54;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_54;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_54;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_54;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_61;
        if (*index == 1LL) return &_til_str_lit_61;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_6;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_61;
        if (*index == 1LL) return &_til_str_lit_64;
        if (*index == 2LL) return &_til_str_lit_87;
        if (*index == 3LL) return &_til_str_lit_89;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
        if (*index == 6LL) return &_til_str_lit_92;
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
        if (*index == 2LL) return &_til_str_lit_54;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_17;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_54;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_61;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_138;
        if (*index == 1LL) return &_til_str_lit_140;
        if (*index == 2LL) return &_til_str_lit_13;
        if (*index == 3LL) return &_til_str_lit_13;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_92;
        if (*index == 1LL) return &_til_str_lit_64;
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
        if (*index == 0LL) return &_til_str_lit_184;
        if (*index == 1LL) return &_til_str_lit_184;
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
        return 10LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        return 6LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        return 28LL;
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
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_41;
        if (*index == 1LL) return &_til_str_lit_42;
        if (*index == 2LL) return &_til_str_lit_43;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_97;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_99;
        if (*index == 4LL) return &_til_str_lit_100;
        if (*index == 5LL) return &_til_str_lit_101;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_30;
        if (*index == 1LL) return &_til_str_lit_103;
        if (*index == 2LL) return &_til_str_lit_104;
        if (*index == 3LL) return &_til_str_lit_106;
        if (*index == 4LL) return &_til_str_lit_108;
        if (*index == 5LL) return &_til_str_lit_110;
        if (*index == 6LL) return &_til_str_lit_25;
        if (*index == 7LL) return &_til_str_lit_22;
        if (*index == 8LL) return &_til_str_lit_24;
        if (*index == 9LL) return &_til_str_lit_113;
        if (*index == 10LL) return &_til_str_lit_115;
        if (*index == 11LL) return &_til_str_lit_117;
        if (*index == 12LL) return &_til_str_lit_118;
        if (*index == 13LL) return &_til_str_lit_119;
        if (*index == 14LL) return &_til_str_lit_120;
        if (*index == 15LL) return &_til_str_lit_122;
        if (*index == 16LL) return &_til_str_lit_123;
        if (*index == 17LL) return &_til_str_lit_124;
        if (*index == 18LL) return &_til_str_lit_125;
        if (*index == 19LL) return &_til_str_lit_126;
        if (*index == 20LL) return &_til_str_lit_128;
        if (*index == 21LL) return &_til_str_lit_129;
        if (*index == 22LL) return &_til_str_lit_130;
        if (*index == 23LL) return &_til_str_lit_131;
        if (*index == 24LL) return &_til_str_lit_132;
        if (*index == 25LL) return &_til_str_lit_133;
        if (*index == 26LL) return &_til_str_lit_135;
        if (*index == 27LL) return &_til_str_lit_136;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_197;
        if (*index == 1LL) return &_til_str_lit_198;
        if (*index == 2LL) return &_til_str_lit_199;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_97;
        if (*index == 1LL) return &_til_str_lit_202;
        if (*index == 2LL) return &_til_str_lit_203;
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
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_18;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_98;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_18;
        if (*index == 4LL) return &_til_str_lit_18;
        if (*index == 5LL) return &_til_str_lit_18;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_103;
        if (*index == 2LL) return &_til_str_lit_105;
        if (*index == 3LL) return &_til_str_lit_107;
        if (*index == 4LL) return &_til_str_lit_109;
        if (*index == 5LL) return &_til_str_lit_111;
        if (*index == 6LL) return &_til_str_lit_112;
        if (*index == 7LL) return &_til_str_lit_22;
        if (*index == 8LL) return &_til_str_lit_24;
        if (*index == 9LL) return &_til_str_lit_114;
        if (*index == 10LL) return &_til_str_lit_116;
        if (*index == 11LL) return &_til_str_lit_18;
        if (*index == 12LL) return &_til_str_lit_18;
        if (*index == 13LL) return &_til_str_lit_18;
        if (*index == 14LL) return &_til_str_lit_121;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_18;
        if (*index == 17LL) return &_til_str_lit_18;
        if (*index == 18LL) return &_til_str_lit_18;
        if (*index == 19LL) return &_til_str_lit_127;
        if (*index == 20LL) return &_til_str_lit_18;
        if (*index == 21LL) return &_til_str_lit_18;
        if (*index == 22LL) return &_til_str_lit_18;
        if (*index == 23LL) return &_til_str_lit_18;
        if (*index == 24LL) return &_til_str_lit_18;
        if (*index == 25LL) return &_til_str_lit_134;
        if (*index == 26LL) return &_til_str_lit_18;
        if (*index == 27LL) return &_til_str_lit_134;
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
