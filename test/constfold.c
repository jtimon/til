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
void swap(void * a, void * b, U64 size);
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
Bool Token_is(Token * self, Token * other);
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
void swap(void * a, void * b, U64 size);
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
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_115, &_fi_USize_115);
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
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_122, &_fi_USize_122);
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
    void * buf = malloc(hoisted__U64_159);
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
    void * new_data = malloc(hoisted__U64_188);
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
    Str *hoisted__Str_757 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_757;
    (void)hoisted__Str_757;
    Bool hoisted__Bool_758 = 0;
    (void)hoisted__Bool_758;
    Str_delete(hoisted__Str_757, hoisted__Bool_758);
    U64 hoisted__U64_759 = 24ULL;
    (void)hoisted__U64_759;
    Str *hoisted__Str_760 = Array__Str_unsafe_get(self, &i);
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
        swap(_err_OutOfBounds, hoisted__OutOfBounds_784, hoisted__U64_785);
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
                (_rc_U64_790 += 1);
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
                (_rc_U64_790 -= 1);
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
    void * new_data = malloc(hoisted__U64_834);
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
                (_rc_U64_804 += 1);
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
                (_rc_U64_804 -= 1);
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
                (_rc_U64_852 += 1);
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
                (_rc_U64_852 -= 1);
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
    void * new_data = malloc(hoisted__U64_1138);
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
                (_rc_U64_1108 += 1);
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
                (_rc_U64_1108 -= 1);
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
    Bool hoisted__Bool_2135 = ((Bool)(a == b));
    (void)hoisted__Bool_2135;
    if (hoisted__Bool_2135) {
        I64 hoisted__I64_2133 = 0;
        (void)hoisted__I64_2133;
        { I64 _ret_val = hoisted__I64_2133;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2134 = -1;
        (void)hoisted__I64_2134;
        return hoisted__I64_2134;
    }
    I64 hoisted__I64_2136 = 1;
    (void)hoisted__I64_2136;
    return hoisted__I64_2136;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Bool_size(void) {
    U64 hoisted__U64_2137 = 1ULL;
    (void)hoisted__U64_2137;
    return hoisted__U64_2137;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U64 hoisted__U64_2138 = 0ULL;
    (void)hoisted__U64_2138;
    U64 hoisted__U64_2139 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U64))til_closure->call)(til_closure->env, &self, hoisted__U64_2138); });
    (void)hoisted__U64_2139;
    return hoisted__U64_2139;
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
    U64 hoisted__U64_2176 = 1ULL;
    (void)hoisted__U64_2176;
    Bool hoisted__Bool_2177 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2177;
    if (hoisted__Bool_2177) {
        U64 hoisted__U64_2156 = 1ULL;
        (void)hoisted__U64_2156;
        Bool hoisted__Bool_2157 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2157;
        { Bool _ret_val = hoisted__Bool_2157;
                return _ret_val; }
    }
    U64 hoisted__U64_2178 = 1ULL;
    (void)hoisted__U64_2178;
    Bool hoisted__Bool_2179 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2179;
    if (hoisted__Bool_2179) {
        U64 hoisted__U64_2158 = 1ULL;
        (void)hoisted__U64_2158;
        Bool hoisted__Bool_2159 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2159;
        { Bool _ret_val = hoisted__Bool_2159;
                return _ret_val; }
    }
    U64 hoisted__U64_2180 = 1ULL;
    (void)hoisted__U64_2180;
    Bool hoisted__Bool_2181 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2181;
    if (hoisted__Bool_2181) {
        U64 hoisted__U64_2160 = 1ULL;
        (void)hoisted__U64_2160;
        Bool hoisted__Bool_2161 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2161;
        { Bool _ret_val = hoisted__Bool_2161;
                return _ret_val; }
    }
    U64 hoisted__U64_2182 = 1ULL;
    (void)hoisted__U64_2182;
    Bool hoisted__Bool_2183 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2183;
    if (hoisted__Bool_2183) {
        U64 hoisted__U64_2162 = 1ULL;
        (void)hoisted__U64_2162;
        Bool hoisted__Bool_2163 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2163;
        { Bool _ret_val = hoisted__Bool_2163;
                return _ret_val; }
    }
    U64 hoisted__U64_2184 = 1ULL;
    (void)hoisted__U64_2184;
    Bool hoisted__Bool_2185 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2185;
    if (hoisted__Bool_2185) {
        U64 hoisted__U64_2164 = 1ULL;
        (void)hoisted__U64_2164;
        Bool hoisted__Bool_2165 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2165;
        { Bool _ret_val = hoisted__Bool_2165;
                return _ret_val; }
    }
    U64 hoisted__U64_2186 = 1ULL;
    (void)hoisted__U64_2186;
    Bool hoisted__Bool_2187 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2187;
    if (hoisted__Bool_2187) {
        U64 hoisted__U64_2166 = 1ULL;
        (void)hoisted__U64_2166;
        Bool hoisted__Bool_2167 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2167;
        { Bool _ret_val = hoisted__Bool_2167;
                return _ret_val; }
    }
    U64 hoisted__U64_2188 = 1ULL;
    (void)hoisted__U64_2188;
    Bool hoisted__Bool_2189 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2189;
    if (hoisted__Bool_2189) {
        U64 hoisted__U64_2168 = 1ULL;
        (void)hoisted__U64_2168;
        Bool hoisted__Bool_2169 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2169;
        { Bool _ret_val = hoisted__Bool_2169;
                return _ret_val; }
    }
    U64 hoisted__U64_2190 = 1ULL;
    (void)hoisted__U64_2190;
    Bool hoisted__Bool_2191 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2191;
    if (hoisted__Bool_2191) {
        U64 hoisted__U64_2170 = 1ULL;
        (void)hoisted__U64_2170;
        Bool hoisted__Bool_2171 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2171;
        { Bool _ret_val = hoisted__Bool_2171;
                return _ret_val; }
    }
    U64 hoisted__U64_2192 = 1ULL;
    (void)hoisted__U64_2192;
    Bool hoisted__Bool_2193 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2193;
    if (hoisted__Bool_2193) {
        U64 hoisted__U64_2172 = 1ULL;
        (void)hoisted__U64_2172;
        Bool hoisted__Bool_2173 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2173;
        { Bool _ret_val = hoisted__Bool_2173;
                return _ret_val; }
    }
    U64 hoisted__U64_2194 = 1ULL;
    (void)hoisted__U64_2194;
    Bool hoisted__Bool_2195 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2195;
    if (hoisted__Bool_2195) {
        U64 hoisted__U64_2174 = 1ULL;
        (void)hoisted__U64_2174;
        Bool hoisted__Bool_2175 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_2175;
        { Bool _ret_val = hoisted__Bool_2175;
                return _ret_val; }
    }
    Bool hoisted__Bool_2196 = 0;
    (void)hoisted__Bool_2196;
    return hoisted__Bool_2196;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2218 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2218;
    if (hoisted__Bool_2218) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2219 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2219;
    if (hoisted__Bool_2219) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2220 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2220;
    if (hoisted__Bool_2220) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2221 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2222 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2222;
    if (hoisted__Bool_2222) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2223 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2224 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2224;
    if (hoisted__Bool_2224) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2225 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2225;
    if (hoisted__Bool_2225) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2226 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2226;
    if (hoisted__Bool_2226) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2227 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2227;
    if (hoisted__Bool_2227) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2228 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2228;
    UNREACHABLE(&hoisted__Str_2228);
    Str_delete(&hoisted__Str_2228, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

U64 Primitive_size(void) {
    U64 hoisted__U64_2229 = 1ULL;
    (void)hoisted__U64_2229;
    return hoisted__U64_2229;
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
    U64 hoisted__U64_2310 = 1ULL;
    (void)hoisted__U64_2310;
    Bool hoisted__Bool_2311 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        Str *hoisted__Str_2300 = get_payload(self);
        (void)hoisted__Str_2300;
        (void)hoisted__Str_2300;
        Bool hoisted__Bool_2301 = 0;
        (void)hoisted__Bool_2301;
        Str_delete(hoisted__Str_2300, hoisted__Bool_2301);
    }
    U64 hoisted__U64_2312 = 1ULL;
    (void)hoisted__U64_2312;
    Bool hoisted__Bool_2313 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        Str *hoisted__Str_2302 = get_payload(self);
        (void)hoisted__Str_2302;
        (void)hoisted__Str_2302;
        Bool hoisted__Bool_2303 = 0;
        (void)hoisted__Bool_2303;
        Str_delete(hoisted__Str_2302, hoisted__Bool_2303);
    }
    U64 hoisted__U64_2314 = 1ULL;
    (void)hoisted__U64_2314;
    Bool hoisted__Bool_2315 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2315;
    if (hoisted__Bool_2315) {
        Str *hoisted__Str_2304 = get_payload(self);
        (void)hoisted__Str_2304;
        (void)hoisted__Str_2304;
        Bool hoisted__Bool_2305 = 0;
        (void)hoisted__Bool_2305;
        Str_delete(hoisted__Str_2304, hoisted__Bool_2305);
    }
    U64 hoisted__U64_2316 = 1ULL;
    (void)hoisted__U64_2316;
    Bool hoisted__Bool_2317 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2317;
    if (hoisted__Bool_2317) {
        Primitive *hoisted__Primitive_2306 = get_payload(self);
        (void)hoisted__Primitive_2306;
        (void)hoisted__Primitive_2306;
        Bool hoisted__Bool_2307 = 0;
        (void)hoisted__Bool_2307;
        Primitive_delete(hoisted__Primitive_2306, hoisted__Bool_2307);
    }
    U64 hoisted__U64_2318 = 1ULL;
    (void)hoisted__U64_2318;
    Bool hoisted__Bool_2319 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2319;
    if (hoisted__Bool_2319) {
        Str *hoisted__Str_2308 = get_payload(self);
        (void)hoisted__Str_2308;
        (void)hoisted__Str_2308;
        Bool hoisted__Bool_2309 = 0;
        (void)hoisted__Bool_2309;
        Str_delete(hoisted__Str_2308, hoisted__Bool_2309);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U64 hoisted__U64_2420 = 1ULL;
    (void)hoisted__U64_2420;
    Bool hoisted__Bool_2421 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2421;
    if (hoisted__Bool_2421) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U64 hoisted__U64_2422 = 1ULL;
    (void)hoisted__U64_2422;
    Bool hoisted__Bool_2423 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2423;
    if (hoisted__Bool_2423) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U64 hoisted__U64_2424 = 1ULL;
    (void)hoisted__U64_2424;
    Bool hoisted__Bool_2425 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2425;
    if (hoisted__Bool_2425) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2410 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2410;
        Type *hoisted__Type_2411 = Type_Struct(hoisted__Str_2410);
        (void)hoisted__Type_2411;
        { Type * _ret_val = hoisted__Type_2411;
                return _ret_val; }
    }
    U64 hoisted__U64_2426 = 1ULL;
    (void)hoisted__U64_2426;
    Bool hoisted__Bool_2427 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2427;
    if (hoisted__Bool_2427) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U64 hoisted__U64_2428 = 1ULL;
    (void)hoisted__U64_2428;
    Bool hoisted__Bool_2429 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2429;
    if (hoisted__Bool_2429) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2412 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2412;
        Type *hoisted__Type_2413 = Type_Enum(hoisted__Str_2412);
        (void)hoisted__Type_2413;
        { Type * _ret_val = hoisted__Type_2413;
                return _ret_val; }
    }
    U64 hoisted__U64_2430 = 1ULL;
    (void)hoisted__U64_2430;
    Bool hoisted__Bool_2431 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2431;
    if (hoisted__Bool_2431) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U64 hoisted__U64_2432 = 1ULL;
    (void)hoisted__U64_2432;
    Bool hoisted__Bool_2433 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2433;
    if (hoisted__Bool_2433) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U64 hoisted__U64_2434 = 1ULL;
    (void)hoisted__U64_2434;
    Bool hoisted__Bool_2435 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2435;
    if (hoisted__Bool_2435) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U64 hoisted__U64_2436 = 1ULL;
    (void)hoisted__U64_2436;
    Bool hoisted__Bool_2437 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2437;
    if (hoisted__Bool_2437) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U64 hoisted__U64_2438 = 1ULL;
    (void)hoisted__U64_2438;
    Bool hoisted__Bool_2439 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2439;
    if (hoisted__Bool_2439) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2414 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2414;
        Type *hoisted__Type_2415 = Type_Custom(hoisted__Str_2414);
        (void)hoisted__Type_2415;
        { Type * _ret_val = hoisted__Type_2415;
                return _ret_val; }
    }
    U64 hoisted__U64_2440 = 1ULL;
    (void)hoisted__U64_2440;
    Bool hoisted__Bool_2441 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2441;
    if (hoisted__Bool_2441) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2416 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2416;
        Type *hoisted__Type_2417 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2416; _oa; }));
        (void)hoisted__Type_2417;
        { Type * _ret_val = hoisted__Type_2417;
                return _ret_val; }
    }
    U64 hoisted__U64_2442 = 1ULL;
    (void)hoisted__U64_2442;
    Bool hoisted__Bool_2443 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2443;
    if (hoisted__Bool_2443) {
        Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2418 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2418;
        Type *hoisted__Type_2419 = Type_FuncPtrSig(hoisted__Str_2418);
        (void)hoisted__Type_2419;
        { Type * _ret_val = hoisted__Type_2419;
                return _ret_val; }
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

U64 Type_size(void) {
    U64 hoisted__U64_2444 = 32ULL;
    (void)hoisted__U64_2444;
    return hoisted__U64_2444;
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
    U64 hoisted__U64_2592 = 1ULL;
    (void)hoisted__U64_2592;
    Bool hoisted__Bool_2593 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2593;
    if (hoisted__Bool_2593) {
        U64 hoisted__U64_2572 = 1ULL;
        (void)hoisted__U64_2572;
        Bool hoisted__Bool_2573 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2573;
        { Bool _ret_val = hoisted__Bool_2573;
                return _ret_val; }
    }
    U64 hoisted__U64_2594 = 1ULL;
    (void)hoisted__U64_2594;
    Bool hoisted__Bool_2595 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2595;
    if (hoisted__Bool_2595) {
        U64 hoisted__U64_2574 = 1ULL;
        (void)hoisted__U64_2574;
        Bool hoisted__Bool_2575 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2575;
        { Bool _ret_val = hoisted__Bool_2575;
                return _ret_val; }
    }
    U64 hoisted__U64_2596 = 1ULL;
    (void)hoisted__U64_2596;
    Bool hoisted__Bool_2597 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2597;
    if (hoisted__Bool_2597) {
        U64 hoisted__U64_2576 = 1ULL;
        (void)hoisted__U64_2576;
        Bool hoisted__Bool_2577 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2577;
        { Bool _ret_val = hoisted__Bool_2577;
                return _ret_val; }
    }
    U64 hoisted__U64_2598 = 1ULL;
    (void)hoisted__U64_2598;
    Bool hoisted__Bool_2599 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2599;
    if (hoisted__Bool_2599) {
        U64 hoisted__U64_2578 = 1ULL;
        (void)hoisted__U64_2578;
        Bool hoisted__Bool_2579 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2579;
        { Bool _ret_val = hoisted__Bool_2579;
                return _ret_val; }
    }
    U64 hoisted__U64_2600 = 1ULL;
    (void)hoisted__U64_2600;
    Bool hoisted__Bool_2601 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2601;
    if (hoisted__Bool_2601) {
        U64 hoisted__U64_2580 = 1ULL;
        (void)hoisted__U64_2580;
        Bool hoisted__Bool_2581 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2581;
        { Bool _ret_val = hoisted__Bool_2581;
                return _ret_val; }
    }
    U64 hoisted__U64_2602 = 1ULL;
    (void)hoisted__U64_2602;
    Bool hoisted__Bool_2603 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2603;
    if (hoisted__Bool_2603) {
        U64 hoisted__U64_2582 = 1ULL;
        (void)hoisted__U64_2582;
        Bool hoisted__Bool_2583 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2583;
        { Bool _ret_val = hoisted__Bool_2583;
                return _ret_val; }
    }
    U64 hoisted__U64_2604 = 1ULL;
    (void)hoisted__U64_2604;
    Bool hoisted__Bool_2605 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2605;
    if (hoisted__Bool_2605) {
        U64 hoisted__U64_2584 = 1ULL;
        (void)hoisted__U64_2584;
        Bool hoisted__Bool_2585 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2585;
        { Bool _ret_val = hoisted__Bool_2585;
                return _ret_val; }
    }
    U64 hoisted__U64_2606 = 1ULL;
    (void)hoisted__U64_2606;
    Bool hoisted__Bool_2607 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2607;
    if (hoisted__Bool_2607) {
        U64 hoisted__U64_2586 = 1ULL;
        (void)hoisted__U64_2586;
        Bool hoisted__Bool_2587 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2587;
        { Bool _ret_val = hoisted__Bool_2587;
                return _ret_val; }
    }
    U64 hoisted__U64_2608 = 1ULL;
    (void)hoisted__U64_2608;
    Bool hoisted__Bool_2609 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2609;
    if (hoisted__Bool_2609) {
        U64 hoisted__U64_2588 = 1ULL;
        (void)hoisted__U64_2588;
        Bool hoisted__Bool_2589 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2589;
        { Bool _ret_val = hoisted__Bool_2589;
                return _ret_val; }
    }
    U64 hoisted__U64_2610 = 1ULL;
    (void)hoisted__U64_2610;
    Bool hoisted__Bool_2611 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2611;
    if (hoisted__Bool_2611) {
        U64 hoisted__U64_2590 = 1ULL;
        (void)hoisted__U64_2590;
        Bool hoisted__Bool_2591 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2591;
        { Bool _ret_val = hoisted__Bool_2591;
                return _ret_val; }
    }
    Bool hoisted__Bool_2612 = 0;
    (void)hoisted__Bool_2612;
    return hoisted__Bool_2612;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2634 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2634;
    if (hoisted__Bool_2634) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2635 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2635;
    if (hoisted__Bool_2635) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2636 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2636;
    if (hoisted__Bool_2636) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2637 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2637;
    if (hoisted__Bool_2637) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2638 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2638;
    if (hoisted__Bool_2638) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2639 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2639;
    if (hoisted__Bool_2639) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2640 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2640;
    if (hoisted__Bool_2640) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2641 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2641;
    if (hoisted__Bool_2641) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2642 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2642;
    if (hoisted__Bool_2642) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2643 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2643;
    if (hoisted__Bool_2643) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2644 = (Str){.c_str = (void *)"FuncType.clone:130:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2644;
    UNREACHABLE(&hoisted__Str_2644);
    Str_delete(&hoisted__Str_2644, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

U64 FuncType_size(void) {
    U64 hoisted__U64_2645 = 1ULL;
    (void)hoisted__U64_2645;
    return hoisted__U64_2645;
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
    U64 hoisted__U64_2654 = 1ULL;
    (void)hoisted__U64_2654;
    Bool hoisted__Bool_2655 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2655;
    if (hoisted__Bool_2655) {
        U64 hoisted__U64_2648 = 1ULL;
        (void)hoisted__U64_2648;
        Bool hoisted__Bool_2649 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2649;
        { Bool _ret_val = hoisted__Bool_2649;
                return _ret_val; }
    }
    U64 hoisted__U64_2656 = 1ULL;
    (void)hoisted__U64_2656;
    Bool hoisted__Bool_2657 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2657;
    if (hoisted__Bool_2657) {
        U64 hoisted__U64_2650 = 1ULL;
        (void)hoisted__U64_2650;
        Bool hoisted__Bool_2651 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2651;
        { Bool _ret_val = hoisted__Bool_2651;
                return _ret_val; }
    }
    U64 hoisted__U64_2658 = 1ULL;
    (void)hoisted__U64_2658;
    Bool hoisted__Bool_2659 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2659;
    if (hoisted__Bool_2659) {
        U64 hoisted__U64_2652 = 1ULL;
        (void)hoisted__U64_2652;
        Bool hoisted__Bool_2653 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2653;
        { Bool _ret_val = hoisted__Bool_2653;
                return _ret_val; }
    }
    Bool hoisted__Bool_2660 = 0;
    (void)hoisted__Bool_2660;
    return hoisted__Bool_2660;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2668 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2668;
    if (hoisted__Bool_2668) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2669 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2669;
    if (hoisted__Bool_2669) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2670 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2670;
    if (hoisted__Bool_2670) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2671 = (Str){.c_str = (void *)"OwnType.clone:142:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2671;
    UNREACHABLE(&hoisted__Str_2671);
    Str_delete(&hoisted__Str_2671, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

U64 OwnType_size(void) {
    U64 hoisted__U64_2672 = 1ULL;
    (void)hoisted__U64_2672;
    return hoisted__U64_2672;
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
    if (call_free) {
        free(self);
    }
}

U64 Declaration_size(void) {
    U64 hoisted__U64_2687 = 144ULL;
    (void)hoisted__U64_2687;
    return hoisted__U64_2687;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2689 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2689->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2689->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2689->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2689->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2689->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2689->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2689->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2689->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2689->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2689->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2689->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2689->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2689;
    return hoisted__FunctionDef_2689;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2690 = 0;
    (void)hoisted__Bool_2690;
    FuncType_delete(&self->func_type, hoisted__Bool_2690);
    Bool hoisted__Bool_2691 = 0;
    (void)hoisted__Bool_2691;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2691);
    Bool hoisted__Bool_2692 = 0;
    (void)hoisted__Bool_2692;
    Str_delete(&self->return_type, hoisted__Bool_2692);
    Bool hoisted__Bool_2693 = 0;
    (void)hoisted__Bool_2693;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2693);
    Bool hoisted__Bool_2694 = 0;
    (void)hoisted__Bool_2694;
    I32_delete(&self->variadic_index, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    I32_delete(&self->kwargs_index, hoisted__Bool_2695);
    Bool hoisted__Bool_2696 = 0;
    (void)hoisted__Bool_2696;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2696);
    Bool hoisted__Bool_2697 = 0;
    (void)hoisted__Bool_2697;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2697);
    Bool hoisted__Bool_2698 = 0;
    (void)hoisted__Bool_2698;
    Bool_delete(&self->auto_generated, hoisted__Bool_2698);
    Bool hoisted__Bool_2699 = 0;
    (void)hoisted__Bool_2699;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2699);
    Bool hoisted__Bool_2700 = 0;
    (void)hoisted__Bool_2700;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2700);
    Bool hoisted__Bool_2701 = 0;
    (void)hoisted__Bool_2701;
    Str_delete(&self->closure_name, hoisted__Bool_2701);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U64 hoisted__U64_2702 = 0ULL;
    (void)hoisted__U64_2702;
    U64 hoisted__U64_2703 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2702); });
    (void)hoisted__U64_2703;
    return hoisted__U64_2703;
    __builtin_unreachable();
}

U64 FunctionDef_size(void) {
    U64 hoisted__U64_2704 = 144ULL;
    (void)hoisted__U64_2704;
    return hoisted__U64_2704;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2707 = malloc(sizeof(FCallData));
    hoisted__FCallData_2707->is_splat = self->is_splat;
    hoisted__FCallData_2707->does_throw = self->does_throw;
    hoisted__FCallData_2707->is_bang = self->is_bang;
    hoisted__FCallData_2707->own_args = self->own_args;
    hoisted__FCallData_2707->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2707->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2707;
    return hoisted__FCallData_2707;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    Bool_delete(&self->is_splat, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Bool_delete(&self->does_throw, hoisted__Bool_2709);
    Bool hoisted__Bool_2710 = 0;
    (void)hoisted__Bool_2710;
    Bool_delete(&self->is_bang, hoisted__Bool_2710);
    Bool hoisted__Bool_2711 = 0;
    (void)hoisted__Bool_2711;
    U64_delete(&self->own_args, hoisted__Bool_2711);
    Bool hoisted__Bool_2712 = 0;
    (void)hoisted__Bool_2712;
    Bool_delete(&self->swap_replace, hoisted__Bool_2712);
    Bool hoisted__Bool_2713 = 0;
    (void)hoisted__Bool_2713;
    Type_delete(&self->til_type, hoisted__Bool_2713);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U64 hoisted__U64_2714 = 0ULL;
    (void)hoisted__U64_2714;
    U64 hoisted__U64_2715 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2714); });
    (void)hoisted__U64_2715;
    return hoisted__U64_2715;
    __builtin_unreachable();
}

U64 FCallData_size(void) {
    U64 hoisted__U64_2716 = 56ULL;
    (void)hoisted__U64_2716;
    return hoisted__U64_2716;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2728 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2728->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2728->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2728;
    return hoisted__LiteralNumData_2728;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2729 = 0;
    (void)hoisted__Bool_2729;
    Str_delete(&self->text, hoisted__Bool_2729);
    Bool hoisted__Bool_2730 = 0;
    (void)hoisted__Bool_2730;
    Type_delete(&self->til_type, hoisted__Bool_2730);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U64 hoisted__U64_2731 = 0ULL;
    (void)hoisted__U64_2731;
    U64 hoisted__U64_2732 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2731); });
    (void)hoisted__U64_2732;
    return hoisted__U64_2732;
    __builtin_unreachable();
}

U64 LiteralNumData_size(void) {
    U64 hoisted__U64_2733 = 56ULL;
    (void)hoisted__U64_2733;
    return hoisted__U64_2733;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2743 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2743->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2743->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2743;
    return hoisted__IdentData_2743;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2744 = 0;
    (void)hoisted__Bool_2744;
    Str_delete(&self->name, hoisted__Bool_2744);
    Bool hoisted__Bool_2745 = 0;
    (void)hoisted__Bool_2745;
    Type_delete(&self->til_type, hoisted__Bool_2745);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U64 hoisted__U64_2746 = 0ULL;
    (void)hoisted__U64_2746;
    U64 hoisted__U64_2747 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2746); });
    (void)hoisted__U64_2747;
    return hoisted__U64_2747;
    __builtin_unreachable();
}

U64 IdentData_size(void) {
    U64 hoisted__U64_2748 = 56ULL;
    (void)hoisted__U64_2748;
    return hoisted__U64_2748;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2754 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2754->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2754->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2754;
    return hoisted__FieldAccessData_2754;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2755 = 0;
    (void)hoisted__Bool_2755;
    Str_delete(&self->name, hoisted__Bool_2755);
    Bool hoisted__Bool_2756 = 0;
    (void)hoisted__Bool_2756;
    Type_delete(&self->til_type, hoisted__Bool_2756);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U64 hoisted__U64_2757 = 0ULL;
    (void)hoisted__U64_2757;
    U64 hoisted__U64_2758 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2757); });
    (void)hoisted__U64_2758;
    return hoisted__U64_2758;
    __builtin_unreachable();
}

U64 FieldAccessData_size(void) {
    U64 hoisted__U64_2759 = 56ULL;
    (void)hoisted__U64_2759;
    return hoisted__U64_2759;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2838 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2838->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2838->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2838->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2838->is_interface = self->is_interface;
    hoisted__StructDef_2838->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2838->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2838;
    return hoisted__StructDef_2838;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2839 = 0;
    (void)hoisted__Bool_2839;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2839);
    Bool hoisted__Bool_2840 = 0;
    (void)hoisted__Bool_2840;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2840);
    Bool hoisted__Bool_2841 = 0;
    (void)hoisted__Bool_2841;
    Str_delete(&self->c_tag, hoisted__Bool_2841);
    Bool hoisted__Bool_2842 = 0;
    (void)hoisted__Bool_2842;
    Bool_delete(&self->is_interface, hoisted__Bool_2842);
    Bool hoisted__Bool_2843 = 0;
    (void)hoisted__Bool_2843;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2843);
    Bool hoisted__Bool_2844 = 0;
    (void)hoisted__Bool_2844;
    Str_delete(&self->implements_name, hoisted__Bool_2844);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U64 hoisted__U64_2845 = 0ULL;
    (void)hoisted__U64_2845;
    U64 hoisted__U64_2846 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2845); });
    (void)hoisted__U64_2846;
    return hoisted__U64_2846;
    __builtin_unreachable();
}

U64 StructDef_size(void) {
    U64 hoisted__U64_2847 = 104ULL;
    (void)hoisted__U64_2847;
    return hoisted__U64_2847;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2852 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2852->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2852->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2852->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2852->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2852->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2852->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2852->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2852;
    return hoisted__EnumDef_2852;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2853 = 0;
    (void)hoisted__Bool_2853;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2853);
    Bool hoisted__Bool_2854 = 0;
    (void)hoisted__Bool_2854;
    Vec__Str_delete(&self->variants, hoisted__Bool_2854);
    Bool hoisted__Bool_2855 = 0;
    (void)hoisted__Bool_2855;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2855);
    Bool hoisted__Bool_2856 = 0;
    (void)hoisted__Bool_2856;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2856);
    Bool hoisted__Bool_2857 = 0;
    (void)hoisted__Bool_2857;
    Str_delete(&self->implements_name, hoisted__Bool_2857);
    Bool hoisted__Bool_2858 = 0;
    (void)hoisted__Bool_2858;
    Str_delete(&self->tag_type, hoisted__Bool_2858);
    Bool hoisted__Bool_2859 = 0;
    (void)hoisted__Bool_2859;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2859);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U64 hoisted__U64_2860 = 0ULL;
    (void)hoisted__U64_2860;
    U64 hoisted__U64_2861 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2860); });
    (void)hoisted__U64_2861;
    return hoisted__U64_2861;
    __builtin_unreachable();
}

U64 EnumDef_size(void) {
    U64 hoisted__U64_2862 = 192ULL;
    (void)hoisted__U64_2862;
    return hoisted__U64_2862;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2963 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2963->name = *_ca; free(_ca); }
    hoisted__AssignData_2963->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2963->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2963->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2963;
    return hoisted__AssignData_2963;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2964 = 0;
    (void)hoisted__Bool_2964;
    Str_delete(&self->name, hoisted__Bool_2964);
    Bool hoisted__Bool_2965 = 0;
    (void)hoisted__Bool_2965;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2965);
    Bool hoisted__Bool_2966 = 0;
    (void)hoisted__Bool_2966;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2966);
    Bool hoisted__Bool_2967 = 0;
    (void)hoisted__Bool_2967;
    Bool_delete(&self->swap_replace, hoisted__Bool_2967);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U64 hoisted__U64_2968 = 0ULL;
    (void)hoisted__U64_2968;
    U64 hoisted__U64_2969 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2968); });
    (void)hoisted__U64_2969;
    return hoisted__U64_2969;
    __builtin_unreachable();
}

U64 AssignData_size(void) {
    U64 hoisted__U64_2970 = 32ULL;
    (void)hoisted__U64_2970;
    return hoisted__U64_2970;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2972 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2972->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2972->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2972;
    return hoisted__FieldAssignData_2972;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2973 = 0;
    (void)hoisted__Bool_2973;
    Str_delete(&self->name, hoisted__Bool_2973);
    Bool hoisted__Bool_2974 = 0;
    (void)hoisted__Bool_2974;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2974);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U64 hoisted__U64_2975 = 0ULL;
    (void)hoisted__U64_2975;
    U64 hoisted__U64_2976 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2975); });
    (void)hoisted__U64_2976;
    return hoisted__U64_2976;
    __builtin_unreachable();
}

U64 FieldAssignData_size(void) {
    U64 hoisted__U64_2977 = 32ULL;
    (void)hoisted__U64_2977;
    return hoisted__U64_2977;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2979 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2979->name = *_ca; free(_ca); }
    hoisted__ForInData_2979->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2979->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2979->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2979->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2979;
    return hoisted__ForInData_2979;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2980 = 0;
    (void)hoisted__Bool_2980;
    Str_delete(&self->name, hoisted__Bool_2980);
    Bool hoisted__Bool_2981 = 0;
    (void)hoisted__Bool_2981;
    Bool_delete(&self->is_mut, hoisted__Bool_2981);
    Bool hoisted__Bool_2982 = 0;
    (void)hoisted__Bool_2982;
    Type_delete(&self->til_type, hoisted__Bool_2982);
    Bool hoisted__Bool_2983 = 0;
    (void)hoisted__Bool_2983;
    Str_delete(&self->name2, hoisted__Bool_2983);
    Bool hoisted__Bool_2984 = 0;
    (void)hoisted__Bool_2984;
    Bool_delete(&self->is_mut2, hoisted__Bool_2984);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U64 hoisted__U64_2985 = 0ULL;
    (void)hoisted__U64_2985;
    U64 hoisted__U64_2986 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_2985); });
    (void)hoisted__U64_2986;
    return hoisted__U64_2986;
    __builtin_unreachable();
}

U64 ForInData_size(void) {
    U64 hoisted__U64_2987 = 96ULL;
    (void)hoisted__U64_2987;
    return hoisted__U64_2987;
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
    U64 hoisted__U64_3030 = 1ULL;
    (void)hoisted__U64_3030;
    Bool hoisted__Bool_3031 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3031;
    if (hoisted__Bool_3031) {
        Str *hoisted__Str_3024 = get_payload(self);
        (void)hoisted__Str_3024;
        (void)hoisted__Str_3024;
        Bool hoisted__Bool_3025 = 0;
        (void)hoisted__Bool_3025;
        Str_delete(hoisted__Str_3024, hoisted__Bool_3025);
    }
    U64 hoisted__U64_3032 = 1ULL;
    (void)hoisted__U64_3032;
    Bool hoisted__Bool_3033 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3033;
    if (hoisted__Bool_3033) {
        LiteralNumData *hoisted__LiteralNumData_3026 = get_payload(self);
        (void)hoisted__LiteralNumData_3026;
        (void)hoisted__LiteralNumData_3026;
        Bool hoisted__Bool_3027 = 0;
        (void)hoisted__Bool_3027;
        LiteralNumData_delete(hoisted__LiteralNumData_3026, hoisted__Bool_3027);
    }
    U64 hoisted__U64_3034 = 1ULL;
    (void)hoisted__U64_3034;
    Bool hoisted__Bool_3035 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3035;
    if (hoisted__Bool_3035) {
        Bool *hoisted__Bool_3028 = get_payload(self);
        (void)hoisted__Bool_3028;
        (void)hoisted__Bool_3028;
        Bool hoisted__Bool_3029 = 0;
        (void)hoisted__Bool_3029;
        Bool_delete(hoisted__Bool_3028, hoisted__Bool_3029);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U64 hoisted__U64_3090 = 1ULL;
    (void)hoisted__U64_3090;
    Bool hoisted__Bool_3091 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3091;
    if (hoisted__Bool_3091) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3085 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3085;
        Literal *hoisted__Literal_3086 = Literal_Str(hoisted__Str_3085);
        (void)hoisted__Literal_3086;
        { Literal * _ret_val = hoisted__Literal_3086;
                return _ret_val; }
    }
    U64 hoisted__U64_3092 = 1ULL;
    (void)hoisted__U64_3092;
    Bool hoisted__Bool_3093 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3093;
    if (hoisted__Bool_3093) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3087 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3087;
        Literal *hoisted__Literal_3088 = Literal_Num(hoisted__LiteralNumData_3087);
        (void)hoisted__Literal_3088;
        { Literal * _ret_val = hoisted__Literal_3088;
                return _ret_val; }
    }
    U64 hoisted__U64_3094 = 1ULL;
    (void)hoisted__U64_3094;
    Bool hoisted__Bool_3095 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3095;
    if (hoisted__Bool_3095) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3089 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3089;
        { Literal * _ret_val = hoisted__Literal_3089;
                return _ret_val; }
    }
    U64 hoisted__U64_3096 = 1ULL;
    (void)hoisted__U64_3096;
    Bool hoisted__Bool_3097 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_3097;
    if (hoisted__Bool_3097) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U64 hoisted__U64_3098 = 1ULL;
    (void)hoisted__U64_3098;
    Bool hoisted__Bool_3099 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_3099;
    if (hoisted__Bool_3099) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

U64 Literal_size(void) {
    U64 hoisted__U64_3100 = 64ULL;
    (void)hoisted__U64_3100;
    return hoisted__U64_3100;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3103 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3103->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3103->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3103;
    return hoisted__MatchData_3103;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3104 = 0;
    (void)hoisted__Bool_3104;
    Type_delete(&self->til_type, hoisted__Bool_3104);
    Bool hoisted__Bool_3105 = 0;
    (void)hoisted__Bool_3105;
    Str_delete(&self->result_temp, hoisted__Bool_3105);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U64 hoisted__U64_3106 = 0ULL;
    (void)hoisted__U64_3106;
    U64 hoisted__U64_3107 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3106); });
    (void)hoisted__U64_3107;
    return hoisted__U64_3107;
    __builtin_unreachable();
}

U64 MatchData_size(void) {
    U64 hoisted__U64_3108 = 56ULL;
    (void)hoisted__U64_3108;
    return hoisted__U64_3108;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3113 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3113->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3113->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3113;
    return hoisted__CaptureBlockData_3113;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3114 = 0;
    (void)hoisted__Bool_3114;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3114);
    Bool hoisted__Bool_3115 = 0;
    (void)hoisted__Bool_3115;
    Str_delete(&self->closure_name, hoisted__Bool_3115);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U64 hoisted__U64_3116 = 0ULL;
    (void)hoisted__U64_3116;
    U64 hoisted__U64_3117 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3116); });
    (void)hoisted__U64_3117;
    return hoisted__U64_3117;
    __builtin_unreachable();
}

U64 CaptureBlockData_size(void) {
    U64 hoisted__U64_3118 = 48ULL;
    (void)hoisted__U64_3118;
    return hoisted__U64_3118;
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
    U64 hoisted__U64_3379 = 1ULL;
    (void)hoisted__U64_3379;
    Bool hoisted__Bool_3380 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3380;
    if (hoisted__Bool_3380) {
        Literal *hoisted__Literal_3349 = get_payload(self);
        (void)hoisted__Literal_3349;
        (void)hoisted__Literal_3349;
        Bool hoisted__Bool_3350 = 0;
        (void)hoisted__Bool_3350;
        Literal_delete(hoisted__Literal_3349, hoisted__Bool_3350);
    }
    U64 hoisted__U64_3381 = 1ULL;
    (void)hoisted__U64_3381;
    Bool hoisted__Bool_3382 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3382;
    if (hoisted__Bool_3382) {
        IdentData *hoisted__IdentData_3351 = get_payload(self);
        (void)hoisted__IdentData_3351;
        (void)hoisted__IdentData_3351;
        Bool hoisted__Bool_3352 = 0;
        (void)hoisted__Bool_3352;
        IdentData_delete(hoisted__IdentData_3351, hoisted__Bool_3352);
    }
    U64 hoisted__U64_3383 = 1ULL;
    (void)hoisted__U64_3383;
    Bool hoisted__Bool_3384 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3384;
    if (hoisted__Bool_3384) {
        Declaration *hoisted__Declaration_3353 = get_payload(self);
        (void)hoisted__Declaration_3353;
        (void)hoisted__Declaration_3353;
        Bool hoisted__Bool_3354 = 0;
        (void)hoisted__Bool_3354;
        Declaration_delete(hoisted__Declaration_3353, hoisted__Bool_3354);
    }
    U64 hoisted__U64_3385 = 1ULL;
    (void)hoisted__U64_3385;
    Bool hoisted__Bool_3386 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3386;
    if (hoisted__Bool_3386) {
        AssignData *hoisted__AssignData_3355 = get_payload(self);
        (void)hoisted__AssignData_3355;
        (void)hoisted__AssignData_3355;
        Bool hoisted__Bool_3356 = 0;
        (void)hoisted__Bool_3356;
        AssignData_delete(hoisted__AssignData_3355, hoisted__Bool_3356);
    }
    U64 hoisted__U64_3387 = 1ULL;
    (void)hoisted__U64_3387;
    Bool hoisted__Bool_3388 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3388;
    if (hoisted__Bool_3388) {
        FCallData *hoisted__FCallData_3357 = get_payload(self);
        (void)hoisted__FCallData_3357;
        (void)hoisted__FCallData_3357;
        Bool hoisted__Bool_3358 = 0;
        (void)hoisted__Bool_3358;
        FCallData_delete(hoisted__FCallData_3357, hoisted__Bool_3358);
    }
    U64 hoisted__U64_3389 = 1ULL;
    (void)hoisted__U64_3389;
    Bool hoisted__Bool_3390 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3390;
    if (hoisted__Bool_3390) {
        FunctionDef *hoisted__FunctionDef_3359 = get_payload(self);
        (void)hoisted__FunctionDef_3359;
        (void)hoisted__FunctionDef_3359;
        Bool hoisted__Bool_3360 = 0;
        (void)hoisted__Bool_3360;
        FunctionDef_delete(hoisted__FunctionDef_3359, hoisted__Bool_3360);
    }
    U64 hoisted__U64_3391 = 1ULL;
    (void)hoisted__U64_3391;
    Bool hoisted__Bool_3392 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3392;
    if (hoisted__Bool_3392) {
        StructDef *hoisted__StructDef_3361 = get_payload(self);
        (void)hoisted__StructDef_3361;
        (void)hoisted__StructDef_3361;
        Bool hoisted__Bool_3362 = 0;
        (void)hoisted__Bool_3362;
        StructDef_delete(hoisted__StructDef_3361, hoisted__Bool_3362);
    }
    U64 hoisted__U64_3393 = 1ULL;
    (void)hoisted__U64_3393;
    Bool hoisted__Bool_3394 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3394;
    if (hoisted__Bool_3394) {
        EnumDef *hoisted__EnumDef_3363 = get_payload(self);
        (void)hoisted__EnumDef_3363;
        (void)hoisted__EnumDef_3363;
        Bool hoisted__Bool_3364 = 0;
        (void)hoisted__Bool_3364;
        EnumDef_delete(hoisted__EnumDef_3363, hoisted__Bool_3364);
    }
    U64 hoisted__U64_3395 = 1ULL;
    (void)hoisted__U64_3395;
    Bool hoisted__Bool_3396 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3396;
    if (hoisted__Bool_3396) {
        FieldAccessData *hoisted__FieldAccessData_3365 = get_payload(self);
        (void)hoisted__FieldAccessData_3365;
        (void)hoisted__FieldAccessData_3365;
        Bool hoisted__Bool_3366 = 0;
        (void)hoisted__Bool_3366;
        FieldAccessData_delete(hoisted__FieldAccessData_3365, hoisted__Bool_3366);
    }
    U64 hoisted__U64_3397 = 1ULL;
    (void)hoisted__U64_3397;
    Bool hoisted__Bool_3398 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3398;
    if (hoisted__Bool_3398) {
        FieldAssignData *hoisted__FieldAssignData_3367 = get_payload(self);
        (void)hoisted__FieldAssignData_3367;
        (void)hoisted__FieldAssignData_3367;
        Bool hoisted__Bool_3368 = 0;
        (void)hoisted__Bool_3368;
        FieldAssignData_delete(hoisted__FieldAssignData_3367, hoisted__Bool_3368);
    }
    U64 hoisted__U64_3399 = 1ULL;
    (void)hoisted__U64_3399;
    Bool hoisted__Bool_3400 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3400;
    if (hoisted__Bool_3400) {
        ForInData *hoisted__ForInData_3369 = get_payload(self);
        (void)hoisted__ForInData_3369;
        (void)hoisted__ForInData_3369;
        Bool hoisted__Bool_3370 = 0;
        (void)hoisted__Bool_3370;
        ForInData_delete(hoisted__ForInData_3369, hoisted__Bool_3370);
    }
    U64 hoisted__U64_3401 = 1ULL;
    (void)hoisted__U64_3401;
    Bool hoisted__Bool_3402 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3402;
    if (hoisted__Bool_3402) {
        Str *hoisted__Str_3371 = get_payload(self);
        (void)hoisted__Str_3371;
        (void)hoisted__Str_3371;
        Bool hoisted__Bool_3372 = 0;
        (void)hoisted__Bool_3372;
        Str_delete(hoisted__Str_3371, hoisted__Bool_3372);
    }
    U64 hoisted__U64_3403 = 1ULL;
    (void)hoisted__U64_3403;
    Bool hoisted__Bool_3404 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3404;
    if (hoisted__Bool_3404) {
        MatchData *hoisted__MatchData_3373 = get_payload(self);
        (void)hoisted__MatchData_3373;
        (void)hoisted__MatchData_3373;
        Bool hoisted__Bool_3374 = 0;
        (void)hoisted__Bool_3374;
        MatchData_delete(hoisted__MatchData_3373, hoisted__Bool_3374);
    }
    U64 hoisted__U64_3405 = 1ULL;
    (void)hoisted__U64_3405;
    Bool hoisted__Bool_3406 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3406;
    if (hoisted__Bool_3406) {
        CaptureBlockData *hoisted__CaptureBlockData_3375 = get_payload(self);
        (void)hoisted__CaptureBlockData_3375;
        (void)hoisted__CaptureBlockData_3375;
        Bool hoisted__Bool_3376 = 0;
        (void)hoisted__Bool_3376;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3375, hoisted__Bool_3376);
    }
    U64 hoisted__U64_3407 = 1ULL;
    (void)hoisted__U64_3407;
    Bool hoisted__Bool_3408 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3408;
    if (hoisted__Bool_3408) {
        CaptureBlockData *hoisted__CaptureBlockData_3377 = get_payload(self);
        (void)hoisted__CaptureBlockData_3377;
        (void)hoisted__CaptureBlockData_3377;
        Bool hoisted__Bool_3378 = 0;
        (void)hoisted__Bool_3378;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3377, hoisted__Bool_3378);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U64 hoisted__U64_3672 = 1ULL;
    (void)hoisted__U64_3672;
    Bool hoisted__Bool_3673 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3673;
    if (hoisted__Bool_3673) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U64 hoisted__U64_3674 = 1ULL;
    (void)hoisted__U64_3674;
    Bool hoisted__Bool_3675 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3675;
    if (hoisted__Bool_3675) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3644 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3644;
        NodeType *hoisted__NodeType_3645 = NodeType_Literal(hoisted__Literal_3644);
        (void)hoisted__NodeType_3645;
        { NodeType * _ret_val = hoisted__NodeType_3645;
                return _ret_val; }
    }
    U64 hoisted__U64_3676 = 1ULL;
    (void)hoisted__U64_3676;
    Bool hoisted__Bool_3677 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3677;
    if (hoisted__Bool_3677) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3646 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3646;
        NodeType *hoisted__NodeType_3647 = NodeType_Ident(hoisted__IdentData_3646);
        (void)hoisted__NodeType_3647;
        { NodeType * _ret_val = hoisted__NodeType_3647;
                return _ret_val; }
    }
    U64 hoisted__U64_3678 = 1ULL;
    (void)hoisted__U64_3678;
    Bool hoisted__Bool_3679 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3679;
    if (hoisted__Bool_3679) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3648 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3648;
        NodeType *hoisted__NodeType_3649 = NodeType_Decl(hoisted__Declaration_3648);
        (void)hoisted__NodeType_3649;
        { NodeType * _ret_val = hoisted__NodeType_3649;
                return _ret_val; }
    }
    U64 hoisted__U64_3680 = 1ULL;
    (void)hoisted__U64_3680;
    Bool hoisted__Bool_3681 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3681;
    if (hoisted__Bool_3681) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3650 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3650;
        NodeType *hoisted__NodeType_3651 = NodeType_Assign(hoisted__AssignData_3650);
        (void)hoisted__NodeType_3651;
        { NodeType * _ret_val = hoisted__NodeType_3651;
                return _ret_val; }
    }
    U64 hoisted__U64_3682 = 1ULL;
    (void)hoisted__U64_3682;
    Bool hoisted__Bool_3683 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3683;
    if (hoisted__Bool_3683) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3652 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3652;
        NodeType *hoisted__NodeType_3653 = NodeType_FCall(hoisted__FCallData_3652);
        (void)hoisted__NodeType_3653;
        { NodeType * _ret_val = hoisted__NodeType_3653;
                return _ret_val; }
    }
    U64 hoisted__U64_3684 = 1ULL;
    (void)hoisted__U64_3684;
    Bool hoisted__Bool_3685 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3685;
    if (hoisted__Bool_3685) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3654 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3654;
        NodeType *hoisted__NodeType_3655 = NodeType_FuncDef(hoisted__FunctionDef_3654);
        (void)hoisted__NodeType_3655;
        { NodeType * _ret_val = hoisted__NodeType_3655;
                return _ret_val; }
    }
    U64 hoisted__U64_3686 = 1ULL;
    (void)hoisted__U64_3686;
    Bool hoisted__Bool_3687 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3687;
    if (hoisted__Bool_3687) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3656 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3656;
        NodeType *hoisted__NodeType_3657 = NodeType_StructDef(hoisted__StructDef_3656);
        (void)hoisted__NodeType_3657;
        { NodeType * _ret_val = hoisted__NodeType_3657;
                return _ret_val; }
    }
    U64 hoisted__U64_3688 = 1ULL;
    (void)hoisted__U64_3688;
    Bool hoisted__Bool_3689 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3689;
    if (hoisted__Bool_3689) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3658 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3658;
        NodeType *hoisted__NodeType_3659 = NodeType_EnumDef(hoisted__EnumDef_3658);
        (void)hoisted__NodeType_3659;
        { NodeType * _ret_val = hoisted__NodeType_3659;
                return _ret_val; }
    }
    U64 hoisted__U64_3690 = 1ULL;
    (void)hoisted__U64_3690;
    Bool hoisted__Bool_3691 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3691;
    if (hoisted__Bool_3691) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3660 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3660;
        NodeType *hoisted__NodeType_3661 = NodeType_FieldAccess(hoisted__FieldAccessData_3660);
        (void)hoisted__NodeType_3661;
        { NodeType * _ret_val = hoisted__NodeType_3661;
                return _ret_val; }
    }
    U64 hoisted__U64_3692 = 1ULL;
    (void)hoisted__U64_3692;
    Bool hoisted__Bool_3693 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3693;
    if (hoisted__Bool_3693) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3662 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3662;
        NodeType *hoisted__NodeType_3663 = NodeType_FieldAssign(hoisted__FieldAssignData_3662);
        (void)hoisted__NodeType_3663;
        { NodeType * _ret_val = hoisted__NodeType_3663;
                return _ret_val; }
    }
    U64 hoisted__U64_3694 = 1ULL;
    (void)hoisted__U64_3694;
    Bool hoisted__Bool_3695 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3695;
    if (hoisted__Bool_3695) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U64 hoisted__U64_3696 = 1ULL;
    (void)hoisted__U64_3696;
    Bool hoisted__Bool_3697 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3697;
    if (hoisted__Bool_3697) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U64 hoisted__U64_3698 = 1ULL;
    (void)hoisted__U64_3698;
    Bool hoisted__Bool_3699 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3699;
    if (hoisted__Bool_3699) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U64 hoisted__U64_3700 = 1ULL;
    (void)hoisted__U64_3700;
    Bool hoisted__Bool_3701 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3701;
    if (hoisted__Bool_3701) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3664 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3664;
        NodeType *hoisted__NodeType_3665 = NodeType_ForIn(hoisted__ForInData_3664);
        (void)hoisted__NodeType_3665;
        { NodeType * _ret_val = hoisted__NodeType_3665;
                return _ret_val; }
    }
    U64 hoisted__U64_3702 = 1ULL;
    (void)hoisted__U64_3702;
    Bool hoisted__Bool_3703 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3703;
    if (hoisted__Bool_3703) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3666 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3666;
        NodeType *hoisted__NodeType_3667 = NodeType_NamedArg(hoisted__Str_3666);
        (void)hoisted__NodeType_3667;
        { NodeType * _ret_val = hoisted__NodeType_3667;
                return _ret_val; }
    }
    U64 hoisted__U64_3704 = 1ULL;
    (void)hoisted__U64_3704;
    Bool hoisted__Bool_3705 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3705;
    if (hoisted__Bool_3705) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U64 hoisted__U64_3706 = 1ULL;
    (void)hoisted__U64_3706;
    Bool hoisted__Bool_3707 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3707;
    if (hoisted__Bool_3707) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U64 hoisted__U64_3708 = 1ULL;
    (void)hoisted__U64_3708;
    Bool hoisted__Bool_3709 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3709;
    if (hoisted__Bool_3709) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U64 hoisted__U64_3710 = 1ULL;
    (void)hoisted__U64_3710;
    Bool hoisted__Bool_3711 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3711;
    if (hoisted__Bool_3711) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3668 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3668;
        NodeType *hoisted__NodeType_3669 = NodeType_Match(hoisted__MatchData_3668);
        (void)hoisted__NodeType_3669;
        { NodeType * _ret_val = hoisted__NodeType_3669;
                return _ret_val; }
    }
    U64 hoisted__U64_3712 = 1ULL;
    (void)hoisted__U64_3712;
    Bool hoisted__Bool_3713 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3713;
    if (hoisted__Bool_3713) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U64 hoisted__U64_3714 = 1ULL;
    (void)hoisted__U64_3714;
    Bool hoisted__Bool_3715 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3715;
    if (hoisted__Bool_3715) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U64 hoisted__U64_3716 = 1ULL;
    (void)hoisted__U64_3716;
    Bool hoisted__Bool_3717 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3717;
    if (hoisted__Bool_3717) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U64 hoisted__U64_3718 = 1ULL;
    (void)hoisted__U64_3718;
    Bool hoisted__Bool_3719 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3719;
    if (hoisted__Bool_3719) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U64 hoisted__U64_3720 = 1ULL;
    (void)hoisted__U64_3720;
    Bool hoisted__Bool_3721 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3721;
    if (hoisted__Bool_3721) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U64 hoisted__U64_3722 = 1ULL;
    (void)hoisted__U64_3722;
    Bool hoisted__Bool_3723 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3723;
    if (hoisted__Bool_3723) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3670 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3670;
        NodeType *hoisted__NodeType_3671 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3670);
        (void)hoisted__NodeType_3671;
        { NodeType * _ret_val = hoisted__NodeType_3671;
                return _ret_val; }
    }
    U64 hoisted__U64_3724 = 1ULL;
    (void)hoisted__U64_3724;
    Bool hoisted__Bool_3725 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3725;
    if (hoisted__Bool_3725) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    CaptureBlockData *_clone_payload_BodyValue_27 = get_payload(self);
    (void)_clone_payload_BodyValue_27;
    (void)_clone_payload_BodyValue_27;
    CaptureBlockData *hoisted__CaptureBlockData_3726 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
    (void)hoisted__CaptureBlockData_3726;
    NodeType *hoisted__NodeType_3727 = NodeType_BodyValue(hoisted__CaptureBlockData_3726);
    (void)hoisted__NodeType_3727;
    return hoisted__NodeType_3727;
    __builtin_unreachable();
}

U64 NodeType_size(void) {
    U64 hoisted__U64_3728 = 200ULL;
    (void)hoisted__U64_3728;
    return hoisted__U64_3728;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3729 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3729;
    if (hoisted__Bool_3729) {
        return;
    }
    Bool hoisted__Bool_3730 = 0;
    (void)hoisted__Bool_3730;
    NodeType_delete(&self->node_type, hoisted__Bool_3730);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3780 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3780->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3780->children = *_ca; free(_ca); }
    hoisted__Expr_3780->line = line;
    hoisted__Expr_3780->col = col;
    (void)hoisted__Expr_3780;
    return hoisted__Expr_3780;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3789 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3789->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3789->children = *_ca; free(_ca); }
    hoisted__Expr_3789->line = self->line;
    hoisted__Expr_3789->col = self->col;
    (void)hoisted__Expr_3789;
    return hoisted__Expr_3789;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U64 hoisted__U64_3790 = 0ULL;
    (void)hoisted__U64_3790;
    U64 hoisted__U64_3791 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_3790); });
    (void)hoisted__U64_3791;
    return hoisted__U64_3791;
    __builtin_unreachable();
}

U64 Expr_size(void) {
    U64 hoisted__U64_3792 = 232ULL;
    (void)hoisted__U64_3792;
    return hoisted__U64_3792;
    __builtin_unreachable();
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4878 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4878->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4878->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4878;
    return hoisted__Map__I64_Str_4878;
    __builtin_unreachable();
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4991 = 0;
    (void)hoisted__Bool_4991;
    Vec__I64_delete(&self->keys, hoisted__Bool_4991);
    Bool hoisted__Bool_4992 = 0;
    (void)hoisted__Bool_4992;
    Vec__Str_delete(&self->values, hoisted__Bool_4992);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4993 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4993->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4993->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4993;
    return hoisted__Map__I64_Str_4993;
    __builtin_unreachable();
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U64 hoisted__U64_4994 = 0ULL;
    (void)hoisted__U64_4994;
    U64 hoisted__U64_4995 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_4994); });
    (void)hoisted__U64_4995;
    return hoisted__U64_4995;
    __builtin_unreachable();
}

U64 Map__I64_Str_size(void) {
    U64 hoisted__U64_4996 = 48ULL;
    (void)hoisted__U64_4996;
    return hoisted__U64_4996;
    __builtin_unreachable();
}

Vec__Bool * Vec__Bool_new(void) {
    U64 hoisted__U64_4997 = 1ULL;
    (void)hoisted__U64_4997;
    U64 hoisted__U64_4998 = (U64)(hoisted__U64_4997);
    (void)hoisted__U64_4998;
    void * hoisted__v_4999 = malloc(hoisted__U64_4998);
    (void)hoisted__v_4999;
    U64 hoisted__U64_5000 = 0ULL;
    (void)hoisted__U64_5000;
    I64 hoisted__I64_5001 = 1;
    (void)hoisted__I64_5001;
    Vec__Bool *hoisted__Vec__Bool_5002 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5002->data = hoisted__v_4999;
    hoisted__Vec__Bool_5002->count = hoisted__U64_5000;
    hoisted__Vec__Bool_5002->cap = hoisted__I64_5001;
    (void)hoisted__Vec__Bool_5002;
    return hoisted__Vec__Bool_5002;
    __builtin_unreachable();
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U64 _re_U64_5012 = self->count;
        (void)_re_U64_5012;
        U64 _rc_U64_5012 = 0ULL;
        (void)_rc_U64_5012;
        Bool hoisted__Bool_5025 = ((Bool)(_rc_U64_5012 <= _re_U64_5012));
        (void)hoisted__Bool_5025;
        if (hoisted__Bool_5025) {
            while (1) {
                Bool _wcond_Bool_5013 = ((Bool)(_rc_U64_5012 < _re_U64_5012));
                (void)_wcond_Bool_5013;
                if (_wcond_Bool_5013) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5012);
                (_rc_U64_5012 += 1);
                U64 hoisted__U64_5014 = 1ULL;
                (void)hoisted__U64_5014;
                U64 hoisted__U64_5015 = ((U64)(i * hoisted__U64_5014));
                (void)hoisted__U64_5015;
                U64 hoisted__U64_5016 = (U64)(hoisted__U64_5015);
                (void)hoisted__U64_5016;
                Bool *hoisted__Bool_5017 = ((void *)((U8 *)(self->data) + (hoisted__U64_5016)));
                (void)hoisted__Bool_5017;
                (void)hoisted__Bool_5017;
                Bool hoisted__Bool_5018 = 0;
                (void)hoisted__Bool_5018;
                Bool_delete(hoisted__Bool_5017, hoisted__Bool_5018);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5019 = ((Bool)(_rc_U64_5012 > _re_U64_5012));
                (void)_wcond_Bool_5019;
                if (_wcond_Bool_5019) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5012);
                (_rc_U64_5012 -= 1);
                U64 hoisted__U64_5020 = 1ULL;
                (void)hoisted__U64_5020;
                U64 hoisted__U64_5021 = ((U64)(i * hoisted__U64_5020));
                (void)hoisted__U64_5021;
                U64 hoisted__U64_5022 = (U64)(hoisted__U64_5021);
                (void)hoisted__U64_5022;
                Bool *hoisted__Bool_5023 = ((void *)((U8 *)(self->data) + (hoisted__U64_5022)));
                (void)hoisted__Bool_5023;
                (void)hoisted__Bool_5023;
                Bool hoisted__Bool_5024 = 0;
                (void)hoisted__Bool_5024;
                Bool_delete(hoisted__Bool_5023, hoisted__Bool_5024);
            }
        }
    }
    U64 hoisted__U64_5026 = 0ULL;
    (void)hoisted__U64_5026;
    self->count = hoisted__U64_5026;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U64 hoisted__U64_5296 = 1ULL;
    (void)hoisted__U64_5296;
    U64 hoisted__U64_5297 = ((U64)(self->cap * hoisted__U64_5296));
    (void)hoisted__U64_5297;
    U64 hoisted__U64_5298 = (U64)(hoisted__U64_5297);
    (void)hoisted__U64_5298;
    void * new_data = malloc(hoisted__U64_5298);
    {
        U64 _re_U64_5268 = self->count;
        (void)_re_U64_5268;
        U64 _rc_U64_5268 = 0ULL;
        (void)_rc_U64_5268;
        Bool hoisted__Bool_5295 = ((Bool)(_rc_U64_5268 <= _re_U64_5268));
        (void)hoisted__Bool_5295;
        if (hoisted__Bool_5295) {
            while (1) {
                Bool _wcond_Bool_5269 = ((Bool)(_rc_U64_5268 < _re_U64_5268));
                (void)_wcond_Bool_5269;
                if (_wcond_Bool_5269) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5268);
                (_rc_U64_5268 += 1);
                U64 hoisted__U64_5270 = 1ULL;
                (void)hoisted__U64_5270;
                U64 hoisted__U64_5271 = ((U64)(i * hoisted__U64_5270));
                (void)hoisted__U64_5271;
                U64 hoisted__U64_5272 = (U64)(hoisted__U64_5271);
                (void)hoisted__U64_5272;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5272)));
                Bool cloned = (DEREF(src));
                U64 hoisted__U64_5273 = 1ULL;
                (void)hoisted__U64_5273;
                U64 hoisted__U64_5274 = ((U64)(i * hoisted__U64_5273));
                (void)hoisted__U64_5274;
                U64 hoisted__U64_5275 = (U64)(hoisted__U64_5274);
                (void)hoisted__U64_5275;
                U64 hoisted__U64_5276 = 1ULL;
                (void)hoisted__U64_5276;
                void *hoisted__v_5277 = ((void *)((U8 *)(new_data) + (hoisted__U64_5275)));
                (void)hoisted__v_5277;
                (void)hoisted__v_5277;
                U64 hoisted__U64_5278 = (U64)(hoisted__U64_5276);
                (void)hoisted__U64_5278;
                memcpy(hoisted__v_5277, &cloned, hoisted__U64_5278);
                U64 hoisted__U64_5279 = 1ULL;
                (void)hoisted__U64_5279;
                I32 hoisted__I32_5280 = 0;
                (void)hoisted__I32_5280;
                U64 hoisted__U64_5281 = (U64)(hoisted__U64_5279);
                (void)hoisted__U64_5281;
                memset(&cloned, hoisted__I32_5280, hoisted__U64_5281);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5282 = ((Bool)(_rc_U64_5268 > _re_U64_5268));
                (void)_wcond_Bool_5282;
                if (_wcond_Bool_5282) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5268);
                (_rc_U64_5268 -= 1);
                U64 hoisted__U64_5283 = 1ULL;
                (void)hoisted__U64_5283;
                U64 hoisted__U64_5284 = ((U64)(i * hoisted__U64_5283));
                (void)hoisted__U64_5284;
                U64 hoisted__U64_5285 = (U64)(hoisted__U64_5284);
                (void)hoisted__U64_5285;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5285)));
                Bool cloned = (DEREF(src));
                U64 hoisted__U64_5286 = 1ULL;
                (void)hoisted__U64_5286;
                U64 hoisted__U64_5287 = ((U64)(i * hoisted__U64_5286));
                (void)hoisted__U64_5287;
                U64 hoisted__U64_5288 = (U64)(hoisted__U64_5287);
                (void)hoisted__U64_5288;
                U64 hoisted__U64_5289 = 1ULL;
                (void)hoisted__U64_5289;
                void *hoisted__v_5290 = ((void *)((U8 *)(new_data) + (hoisted__U64_5288)));
                (void)hoisted__v_5290;
                (void)hoisted__v_5290;
                U64 hoisted__U64_5291 = (U64)(hoisted__U64_5289);
                (void)hoisted__U64_5291;
                memcpy(hoisted__v_5290, &cloned, hoisted__U64_5291);
                U64 hoisted__U64_5292 = 1ULL;
                (void)hoisted__U64_5292;
                I32 hoisted__I32_5293 = 0;
                (void)hoisted__I32_5293;
                U64 hoisted__U64_5294 = (U64)(hoisted__U64_5292);
                (void)hoisted__U64_5294;
                memset(&cloned, hoisted__I32_5293, hoisted__U64_5294);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5299 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5299->data = new_data;
    hoisted__Vec__Bool_5299->count = self->count;
    hoisted__Vec__Bool_5299->cap = self->cap;
    (void)hoisted__Vec__Bool_5299;
    return hoisted__Vec__Bool_5299;
    __builtin_unreachable();
}

U64 Vec__Bool_size(void) {
    U64 hoisted__U64_5300 = 24ULL;
    (void)hoisted__U64_5300;
    return hoisted__U64_5300;
    __builtin_unreachable();
}

Vec__I64 * Vec__I64_new(void) {
    U64 hoisted__U64_5301 = 8ULL;
    (void)hoisted__U64_5301;
    U64 hoisted__U64_5302 = (U64)(hoisted__U64_5301);
    (void)hoisted__U64_5302;
    void * hoisted__v_5303 = malloc(hoisted__U64_5302);
    (void)hoisted__v_5303;
    U64 hoisted__U64_5304 = 0ULL;
    (void)hoisted__U64_5304;
    I64 hoisted__I64_5305 = 1;
    (void)hoisted__I64_5305;
    Vec__I64 *hoisted__Vec__I64_5306 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5306->data = hoisted__v_5303;
    hoisted__Vec__I64_5306->count = hoisted__U64_5304;
    hoisted__Vec__I64_5306->cap = hoisted__I64_5305;
    (void)hoisted__Vec__I64_5306;
    return hoisted__Vec__I64_5306;
    __builtin_unreachable();
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U64 _re_U64_5316 = self->count;
        (void)_re_U64_5316;
        U64 _rc_U64_5316 = 0ULL;
        (void)_rc_U64_5316;
        Bool hoisted__Bool_5329 = ((Bool)(_rc_U64_5316 <= _re_U64_5316));
        (void)hoisted__Bool_5329;
        if (hoisted__Bool_5329) {
            while (1) {
                Bool _wcond_Bool_5317 = ((Bool)(_rc_U64_5316 < _re_U64_5316));
                (void)_wcond_Bool_5317;
                if (_wcond_Bool_5317) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5316);
                (_rc_U64_5316 += 1);
                U64 hoisted__U64_5318 = 8ULL;
                (void)hoisted__U64_5318;
                U64 hoisted__U64_5319 = ((U64)(i * hoisted__U64_5318));
                (void)hoisted__U64_5319;
                U64 hoisted__U64_5320 = (U64)(hoisted__U64_5319);
                (void)hoisted__U64_5320;
                I64 *hoisted__I64_5321 = ((void *)((U8 *)(self->data) + (hoisted__U64_5320)));
                (void)hoisted__I64_5321;
                (void)hoisted__I64_5321;
                Bool hoisted__Bool_5322 = 0;
                (void)hoisted__Bool_5322;
                I64_delete(hoisted__I64_5321, hoisted__Bool_5322);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5323 = ((Bool)(_rc_U64_5316 > _re_U64_5316));
                (void)_wcond_Bool_5323;
                if (_wcond_Bool_5323) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5316);
                (_rc_U64_5316 -= 1);
                U64 hoisted__U64_5324 = 8ULL;
                (void)hoisted__U64_5324;
                U64 hoisted__U64_5325 = ((U64)(i * hoisted__U64_5324));
                (void)hoisted__U64_5325;
                U64 hoisted__U64_5326 = (U64)(hoisted__U64_5325);
                (void)hoisted__U64_5326;
                I64 *hoisted__I64_5327 = ((void *)((U8 *)(self->data) + (hoisted__U64_5326)));
                (void)hoisted__I64_5327;
                (void)hoisted__I64_5327;
                Bool hoisted__Bool_5328 = 0;
                (void)hoisted__Bool_5328;
                I64_delete(hoisted__I64_5327, hoisted__Bool_5328);
            }
        }
    }
    U64 hoisted__U64_5330 = 0ULL;
    (void)hoisted__U64_5330;
    self->count = hoisted__U64_5330;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U64 hoisted__U64_5600 = 8ULL;
    (void)hoisted__U64_5600;
    U64 hoisted__U64_5601 = ((U64)(self->cap * hoisted__U64_5600));
    (void)hoisted__U64_5601;
    U64 hoisted__U64_5602 = (U64)(hoisted__U64_5601);
    (void)hoisted__U64_5602;
    void * new_data = malloc(hoisted__U64_5602);
    {
        U64 _re_U64_5572 = self->count;
        (void)_re_U64_5572;
        U64 _rc_U64_5572 = 0ULL;
        (void)_rc_U64_5572;
        Bool hoisted__Bool_5599 = ((Bool)(_rc_U64_5572 <= _re_U64_5572));
        (void)hoisted__Bool_5599;
        if (hoisted__Bool_5599) {
            while (1) {
                Bool _wcond_Bool_5573 = ((Bool)(_rc_U64_5572 < _re_U64_5572));
                (void)_wcond_Bool_5573;
                if (_wcond_Bool_5573) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5572);
                (_rc_U64_5572 += 1);
                U64 hoisted__U64_5574 = 8ULL;
                (void)hoisted__U64_5574;
                U64 hoisted__U64_5575 = ((U64)(i * hoisted__U64_5574));
                (void)hoisted__U64_5575;
                U64 hoisted__U64_5576 = (U64)(hoisted__U64_5575);
                (void)hoisted__U64_5576;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5576)));
                I64 cloned = (DEREF(src));
                U64 hoisted__U64_5577 = 8ULL;
                (void)hoisted__U64_5577;
                U64 hoisted__U64_5578 = ((U64)(i * hoisted__U64_5577));
                (void)hoisted__U64_5578;
                U64 hoisted__U64_5579 = (U64)(hoisted__U64_5578);
                (void)hoisted__U64_5579;
                U64 hoisted__U64_5580 = 8ULL;
                (void)hoisted__U64_5580;
                void *hoisted__v_5581 = ((void *)((U8 *)(new_data) + (hoisted__U64_5579)));
                (void)hoisted__v_5581;
                (void)hoisted__v_5581;
                U64 hoisted__U64_5582 = (U64)(hoisted__U64_5580);
                (void)hoisted__U64_5582;
                memcpy(hoisted__v_5581, &cloned, hoisted__U64_5582);
                U64 hoisted__U64_5583 = 8ULL;
                (void)hoisted__U64_5583;
                I32 hoisted__I32_5584 = 0;
                (void)hoisted__I32_5584;
                U64 hoisted__U64_5585 = (U64)(hoisted__U64_5583);
                (void)hoisted__U64_5585;
                memset(&cloned, hoisted__I32_5584, hoisted__U64_5585);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5586 = ((Bool)(_rc_U64_5572 > _re_U64_5572));
                (void)_wcond_Bool_5586;
                if (_wcond_Bool_5586) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5572);
                (_rc_U64_5572 -= 1);
                U64 hoisted__U64_5587 = 8ULL;
                (void)hoisted__U64_5587;
                U64 hoisted__U64_5588 = ((U64)(i * hoisted__U64_5587));
                (void)hoisted__U64_5588;
                U64 hoisted__U64_5589 = (U64)(hoisted__U64_5588);
                (void)hoisted__U64_5589;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5589)));
                I64 cloned = (DEREF(src));
                U64 hoisted__U64_5590 = 8ULL;
                (void)hoisted__U64_5590;
                U64 hoisted__U64_5591 = ((U64)(i * hoisted__U64_5590));
                (void)hoisted__U64_5591;
                U64 hoisted__U64_5592 = (U64)(hoisted__U64_5591);
                (void)hoisted__U64_5592;
                U64 hoisted__U64_5593 = 8ULL;
                (void)hoisted__U64_5593;
                void *hoisted__v_5594 = ((void *)((U8 *)(new_data) + (hoisted__U64_5592)));
                (void)hoisted__v_5594;
                (void)hoisted__v_5594;
                U64 hoisted__U64_5595 = (U64)(hoisted__U64_5593);
                (void)hoisted__U64_5595;
                memcpy(hoisted__v_5594, &cloned, hoisted__U64_5595);
                U64 hoisted__U64_5596 = 8ULL;
                (void)hoisted__U64_5596;
                I32 hoisted__I32_5597 = 0;
                (void)hoisted__I32_5597;
                U64 hoisted__U64_5598 = (U64)(hoisted__U64_5596);
                (void)hoisted__U64_5598;
                memset(&cloned, hoisted__I32_5597, hoisted__U64_5598);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5603 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5603->data = new_data;
    hoisted__Vec__I64_5603->count = self->count;
    hoisted__Vec__I64_5603->cap = self->cap;
    (void)hoisted__Vec__I64_5603;
    return hoisted__Vec__I64_5603;
    __builtin_unreachable();
}

U64 Vec__I64_size(void) {
    U64 hoisted__U64_5604 = 24ULL;
    (void)hoisted__U64_5604;
    return hoisted__U64_5604;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U64 hoisted__U64_5909 = 144ULL;
    (void)hoisted__U64_5909;
    U64 hoisted__U64_5910 = (U64)(hoisted__U64_5909);
    (void)hoisted__U64_5910;
    void * hoisted__v_5911 = malloc(hoisted__U64_5910);
    (void)hoisted__v_5911;
    U64 hoisted__U64_5912 = 0ULL;
    (void)hoisted__U64_5912;
    I64 hoisted__I64_5913 = 1;
    (void)hoisted__I64_5913;
    Vec__Declaration *hoisted__Vec__Declaration_5914 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5914->data = hoisted__v_5911;
    hoisted__Vec__Declaration_5914->count = hoisted__U64_5912;
    hoisted__Vec__Declaration_5914->cap = hoisted__I64_5913;
    (void)hoisted__Vec__Declaration_5914;
    return hoisted__Vec__Declaration_5914;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U64 _re_U64_5924 = self->count;
        (void)_re_U64_5924;
        U64 _rc_U64_5924 = 0ULL;
        (void)_rc_U64_5924;
        Bool hoisted__Bool_5937 = ((Bool)(_rc_U64_5924 <= _re_U64_5924));
        (void)hoisted__Bool_5937;
        if (hoisted__Bool_5937) {
            while (1) {
                Bool _wcond_Bool_5925 = ((Bool)(_rc_U64_5924 < _re_U64_5924));
                (void)_wcond_Bool_5925;
                if (_wcond_Bool_5925) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5924);
                (_rc_U64_5924 += 1);
                U64 hoisted__U64_5926 = 144ULL;
                (void)hoisted__U64_5926;
                U64 hoisted__U64_5927 = ((U64)(i * hoisted__U64_5926));
                (void)hoisted__U64_5927;
                U64 hoisted__U64_5928 = (U64)(hoisted__U64_5927);
                (void)hoisted__U64_5928;
                Declaration *hoisted__Declaration_5929 = ((void *)((U8 *)(self->data) + (hoisted__U64_5928)));
                (void)hoisted__Declaration_5929;
                (void)hoisted__Declaration_5929;
                Bool hoisted__Bool_5930 = 0;
                (void)hoisted__Bool_5930;
                Declaration_delete(hoisted__Declaration_5929, hoisted__Bool_5930);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5931 = ((Bool)(_rc_U64_5924 > _re_U64_5924));
                (void)_wcond_Bool_5931;
                if (_wcond_Bool_5931) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_5924);
                (_rc_U64_5924 -= 1);
                U64 hoisted__U64_5932 = 144ULL;
                (void)hoisted__U64_5932;
                U64 hoisted__U64_5933 = ((U64)(i * hoisted__U64_5932));
                (void)hoisted__U64_5933;
                U64 hoisted__U64_5934 = (U64)(hoisted__U64_5933);
                (void)hoisted__U64_5934;
                Declaration *hoisted__Declaration_5935 = ((void *)((U8 *)(self->data) + (hoisted__U64_5934)));
                (void)hoisted__Declaration_5935;
                (void)hoisted__Declaration_5935;
                Bool hoisted__Bool_5936 = 0;
                (void)hoisted__Bool_5936;
                Declaration_delete(hoisted__Declaration_5935, hoisted__Bool_5936);
            }
        }
    }
    U64 hoisted__U64_5938 = 0ULL;
    (void)hoisted__U64_5938;
    self->count = hoisted__U64_5938;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U64 hoisted__U64_6208 = 144ULL;
    (void)hoisted__U64_6208;
    U64 hoisted__U64_6209 = ((U64)(self->cap * hoisted__U64_6208));
    (void)hoisted__U64_6209;
    U64 hoisted__U64_6210 = (U64)(hoisted__U64_6209);
    (void)hoisted__U64_6210;
    void * new_data = malloc(hoisted__U64_6210);
    {
        U64 _re_U64_6180 = self->count;
        (void)_re_U64_6180;
        U64 _rc_U64_6180 = 0ULL;
        (void)_rc_U64_6180;
        Bool hoisted__Bool_6207 = ((Bool)(_rc_U64_6180 <= _re_U64_6180));
        (void)hoisted__Bool_6207;
        if (hoisted__Bool_6207) {
            while (1) {
                Bool _wcond_Bool_6181 = ((Bool)(_rc_U64_6180 < _re_U64_6180));
                (void)_wcond_Bool_6181;
                if (_wcond_Bool_6181) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6180);
                (_rc_U64_6180 += 1);
                U64 hoisted__U64_6182 = 144ULL;
                (void)hoisted__U64_6182;
                U64 hoisted__U64_6183 = ((U64)(i * hoisted__U64_6182));
                (void)hoisted__U64_6183;
                U64 hoisted__U64_6184 = (U64)(hoisted__U64_6183);
                (void)hoisted__U64_6184;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6184)));
                Declaration *cloned = Declaration_clone(src);
                U64 hoisted__U64_6185 = 144ULL;
                (void)hoisted__U64_6185;
                U64 hoisted__U64_6186 = ((U64)(i * hoisted__U64_6185));
                (void)hoisted__U64_6186;
                U64 hoisted__U64_6187 = (U64)(hoisted__U64_6186);
                (void)hoisted__U64_6187;
                U64 hoisted__U64_6188 = 144ULL;
                (void)hoisted__U64_6188;
                void *hoisted__v_6189 = ((void *)((U8 *)(new_data) + (hoisted__U64_6187)));
                (void)hoisted__v_6189;
                (void)hoisted__v_6189;
                U64 hoisted__U64_6190 = (U64)(hoisted__U64_6188);
                (void)hoisted__U64_6190;
                memcpy(hoisted__v_6189, cloned, hoisted__U64_6190);
                U64 hoisted__U64_6191 = 144ULL;
                (void)hoisted__U64_6191;
                I32 hoisted__I32_6192 = 0;
                (void)hoisted__I32_6192;
                U64 hoisted__U64_6193 = (U64)(hoisted__U64_6191);
                (void)hoisted__U64_6193;
                memset(cloned, hoisted__I32_6192, hoisted__U64_6193);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6194 = ((Bool)(_rc_U64_6180 > _re_U64_6180));
                (void)_wcond_Bool_6194;
                if (_wcond_Bool_6194) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6180);
                (_rc_U64_6180 -= 1);
                U64 hoisted__U64_6195 = 144ULL;
                (void)hoisted__U64_6195;
                U64 hoisted__U64_6196 = ((U64)(i * hoisted__U64_6195));
                (void)hoisted__U64_6196;
                U64 hoisted__U64_6197 = (U64)(hoisted__U64_6196);
                (void)hoisted__U64_6197;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6197)));
                Declaration *cloned = Declaration_clone(src);
                U64 hoisted__U64_6198 = 144ULL;
                (void)hoisted__U64_6198;
                U64 hoisted__U64_6199 = ((U64)(i * hoisted__U64_6198));
                (void)hoisted__U64_6199;
                U64 hoisted__U64_6200 = (U64)(hoisted__U64_6199);
                (void)hoisted__U64_6200;
                U64 hoisted__U64_6201 = 144ULL;
                (void)hoisted__U64_6201;
                void *hoisted__v_6202 = ((void *)((U8 *)(new_data) + (hoisted__U64_6200)));
                (void)hoisted__v_6202;
                (void)hoisted__v_6202;
                U64 hoisted__U64_6203 = (U64)(hoisted__U64_6201);
                (void)hoisted__U64_6203;
                memcpy(hoisted__v_6202, cloned, hoisted__U64_6203);
                U64 hoisted__U64_6204 = 144ULL;
                (void)hoisted__U64_6204;
                I32 hoisted__I32_6205 = 0;
                (void)hoisted__I32_6205;
                U64 hoisted__U64_6206 = (U64)(hoisted__U64_6204);
                (void)hoisted__U64_6206;
                memset(cloned, hoisted__I32_6205, hoisted__U64_6206);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_6211 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6211->data = new_data;
    hoisted__Vec__Declaration_6211->count = self->count;
    hoisted__Vec__Declaration_6211->cap = self->cap;
    (void)hoisted__Vec__Declaration_6211;
    return hoisted__Vec__Declaration_6211;
    __builtin_unreachable();
}

U64 Vec__Declaration_size(void) {
    U64 hoisted__U64_6212 = 24ULL;
    (void)hoisted__U64_6212;
    return hoisted__U64_6212;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U64 hoisted__U64_6213 = 232ULL;
    (void)hoisted__U64_6213;
    U64 hoisted__U64_6214 = (U64)(hoisted__U64_6213);
    (void)hoisted__U64_6214;
    void * hoisted__v_6215 = malloc(hoisted__U64_6214);
    (void)hoisted__v_6215;
    U64 hoisted__U64_6216 = 0ULL;
    (void)hoisted__U64_6216;
    I64 hoisted__I64_6217 = 1;
    (void)hoisted__I64_6217;
    Vec__Expr *hoisted__Vec__Expr_6218 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6218->data = hoisted__v_6215;
    hoisted__Vec__Expr_6218->count = hoisted__U64_6216;
    hoisted__Vec__Expr_6218->cap = hoisted__I64_6217;
    (void)hoisted__Vec__Expr_6218;
    return hoisted__Vec__Expr_6218;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U64 _re_U64_6228 = self->count;
        (void)_re_U64_6228;
        U64 _rc_U64_6228 = 0ULL;
        (void)_rc_U64_6228;
        Bool hoisted__Bool_6241 = ((Bool)(_rc_U64_6228 <= _re_U64_6228));
        (void)hoisted__Bool_6241;
        if (hoisted__Bool_6241) {
            while (1) {
                Bool _wcond_Bool_6229 = ((Bool)(_rc_U64_6228 < _re_U64_6228));
                (void)_wcond_Bool_6229;
                if (_wcond_Bool_6229) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6228);
                (_rc_U64_6228 += 1);
                U64 hoisted__U64_6230 = 232ULL;
                (void)hoisted__U64_6230;
                U64 hoisted__U64_6231 = ((U64)(i * hoisted__U64_6230));
                (void)hoisted__U64_6231;
                U64 hoisted__U64_6232 = (U64)(hoisted__U64_6231);
                (void)hoisted__U64_6232;
                Expr *hoisted__Expr_6233 = ((void *)((U8 *)(self->data) + (hoisted__U64_6232)));
                (void)hoisted__Expr_6233;
                (void)hoisted__Expr_6233;
                Bool hoisted__Bool_6234 = 0;
                (void)hoisted__Bool_6234;
                Expr_delete(hoisted__Expr_6233, hoisted__Bool_6234);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6235 = ((Bool)(_rc_U64_6228 > _re_U64_6228));
                (void)_wcond_Bool_6235;
                if (_wcond_Bool_6235) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6228);
                (_rc_U64_6228 -= 1);
                U64 hoisted__U64_6236 = 232ULL;
                (void)hoisted__U64_6236;
                U64 hoisted__U64_6237 = ((U64)(i * hoisted__U64_6236));
                (void)hoisted__U64_6237;
                U64 hoisted__U64_6238 = (U64)(hoisted__U64_6237);
                (void)hoisted__U64_6238;
                Expr *hoisted__Expr_6239 = ((void *)((U8 *)(self->data) + (hoisted__U64_6238)));
                (void)hoisted__Expr_6239;
                (void)hoisted__Expr_6239;
                Bool hoisted__Bool_6240 = 0;
                (void)hoisted__Bool_6240;
                Expr_delete(hoisted__Expr_6239, hoisted__Bool_6240);
            }
        }
    }
    U64 hoisted__U64_6242 = 0ULL;
    (void)hoisted__U64_6242;
    self->count = hoisted__U64_6242;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U64 hoisted__U64_6512 = 232ULL;
    (void)hoisted__U64_6512;
    U64 hoisted__U64_6513 = ((U64)(self->cap * hoisted__U64_6512));
    (void)hoisted__U64_6513;
    U64 hoisted__U64_6514 = (U64)(hoisted__U64_6513);
    (void)hoisted__U64_6514;
    void * new_data = malloc(hoisted__U64_6514);
    {
        U64 _re_U64_6484 = self->count;
        (void)_re_U64_6484;
        U64 _rc_U64_6484 = 0ULL;
        (void)_rc_U64_6484;
        Bool hoisted__Bool_6511 = ((Bool)(_rc_U64_6484 <= _re_U64_6484));
        (void)hoisted__Bool_6511;
        if (hoisted__Bool_6511) {
            while (1) {
                Bool _wcond_Bool_6485 = ((Bool)(_rc_U64_6484 < _re_U64_6484));
                (void)_wcond_Bool_6485;
                if (_wcond_Bool_6485) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6484);
                (_rc_U64_6484 += 1);
                U64 hoisted__U64_6486 = 232ULL;
                (void)hoisted__U64_6486;
                U64 hoisted__U64_6487 = ((U64)(i * hoisted__U64_6486));
                (void)hoisted__U64_6487;
                U64 hoisted__U64_6488 = (U64)(hoisted__U64_6487);
                (void)hoisted__U64_6488;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6488)));
                Expr *cloned = Expr_clone(src);
                U64 hoisted__U64_6489 = 232ULL;
                (void)hoisted__U64_6489;
                U64 hoisted__U64_6490 = ((U64)(i * hoisted__U64_6489));
                (void)hoisted__U64_6490;
                U64 hoisted__U64_6491 = (U64)(hoisted__U64_6490);
                (void)hoisted__U64_6491;
                U64 hoisted__U64_6492 = 232ULL;
                (void)hoisted__U64_6492;
                void *hoisted__v_6493 = ((void *)((U8 *)(new_data) + (hoisted__U64_6491)));
                (void)hoisted__v_6493;
                (void)hoisted__v_6493;
                U64 hoisted__U64_6494 = (U64)(hoisted__U64_6492);
                (void)hoisted__U64_6494;
                memcpy(hoisted__v_6493, cloned, hoisted__U64_6494);
                U64 hoisted__U64_6495 = 232ULL;
                (void)hoisted__U64_6495;
                I32 hoisted__I32_6496 = 0;
                (void)hoisted__I32_6496;
                U64 hoisted__U64_6497 = (U64)(hoisted__U64_6495);
                (void)hoisted__U64_6497;
                memset(cloned, hoisted__I32_6496, hoisted__U64_6497);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6498 = ((Bool)(_rc_U64_6484 > _re_U64_6484));
                (void)_wcond_Bool_6498;
                if (_wcond_Bool_6498) {
                } else {
                    break;
                }
                U64 i = (_rc_U64_6484);
                (_rc_U64_6484 -= 1);
                U64 hoisted__U64_6499 = 232ULL;
                (void)hoisted__U64_6499;
                U64 hoisted__U64_6500 = ((U64)(i * hoisted__U64_6499));
                (void)hoisted__U64_6500;
                U64 hoisted__U64_6501 = (U64)(hoisted__U64_6500);
                (void)hoisted__U64_6501;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_6501)));
                Expr *cloned = Expr_clone(src);
                U64 hoisted__U64_6502 = 232ULL;
                (void)hoisted__U64_6502;
                U64 hoisted__U64_6503 = ((U64)(i * hoisted__U64_6502));
                (void)hoisted__U64_6503;
                U64 hoisted__U64_6504 = (U64)(hoisted__U64_6503);
                (void)hoisted__U64_6504;
                U64 hoisted__U64_6505 = 232ULL;
                (void)hoisted__U64_6505;
                void *hoisted__v_6506 = ((void *)((U8 *)(new_data) + (hoisted__U64_6504)));
                (void)hoisted__v_6506;
                (void)hoisted__v_6506;
                U64 hoisted__U64_6507 = (U64)(hoisted__U64_6505);
                (void)hoisted__U64_6507;
                memcpy(hoisted__v_6506, cloned, hoisted__U64_6507);
                U64 hoisted__U64_6508 = 232ULL;
                (void)hoisted__U64_6508;
                I32 hoisted__I32_6509 = 0;
                (void)hoisted__I32_6509;
                U64 hoisted__U64_6510 = (U64)(hoisted__U64_6508);
                (void)hoisted__U64_6510;
                memset(cloned, hoisted__I32_6509, hoisted__U64_6510);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6515 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6515->data = new_data;
    hoisted__Vec__Expr_6515->count = self->count;
    hoisted__Vec__Expr_6515->cap = self->cap;
    (void)hoisted__Vec__Expr_6515;
    return hoisted__Vec__Expr_6515;
    __builtin_unreachable();
}

U64 Vec__Expr_size(void) {
    U64 hoisted__U64_6516 = 24ULL;
    (void)hoisted__U64_6516;
    return hoisted__U64_6516;
    __builtin_unreachable();
}

void panic(Array__Str * parts, Str * loc) {
    U64 hoisted__U64_7604 = 3ULL;
    (void)hoisted__U64_7604;
    Array__Str *_va_Array_208 = Array__Str_new(hoisted__U64_7604);
    (void)_va_Array_208;
    I64 _va_Array_208_ek = 0;
    (void)_va_Array_208_ek;
    OutOfBounds *_va_Array_208_eo = malloc(sizeof(OutOfBounds));
    _va_Array_208_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_208_eo;
    U64 hoisted__U64_7605 = 0ULL;
    (void)hoisted__U64_7605;
    Str *hoisted__Str_7606 = Str_clone(loc);
    (void)hoisted__Str_7606;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    Array__Str_set(_va_Array_208, hoisted__U64_7605, hoisted__Str_7606, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_145);
    Str_delete(&_til_str_lit_145, (Bool){0});
    U64 hoisted__U64_7608 = 1ULL;
    (void)hoisted__U64_7608;
    (void)_til_str_lit_146;
    (void)_til_str_lit_146;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    Array__Str_set(_va_Array_208, hoisted__U64_7608, &_til_str_lit_146, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_145);
    Str_delete(&_til_str_lit_145, (Bool){0});
    Array__Str *hoisted__Array__Str_7611 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7611;
    U64 hoisted__U64_7612 = 2ULL;
    (void)hoisted__U64_7612;
    Str *hoisted__Str_7613 = format(hoisted__Array__Str_7611);
    (void)hoisted__Str_7613;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    Array__Str_set(_va_Array_208, hoisted__U64_7612, hoisted__Str_7613, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_145);
    OutOfBounds_delete(_va_Array_208_eo, 1);
    Str_delete(&_til_str_lit_145, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_208);
    I64 hoisted__I64_7615 = 1;
    (void)hoisted__I64_7615;
    exit(hoisted__I64_7615);
}

void UNREACHABLE(Str * loc) {
    U64 hoisted__U64_7624 = 1ULL;
    (void)hoisted__U64_7624;
    Array__Str *_va_Array_210 = Array__Str_new(hoisted__U64_7624);
    (void)_va_Array_210;
    I64 _va_Array_210_ek = 0;
    (void)_va_Array_210_ek;
    OutOfBounds *_va_Array_210_eo = malloc(sizeof(OutOfBounds));
    _va_Array_210_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_210_eo;
    U64 hoisted__U64_7625 = 0ULL;
    (void)hoisted__U64_7625;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    (void)_til_str_lit_148;
    (void)_til_str_lit_148;
    Array__Str_set(_va_Array_210, hoisted__U64_7625, &_til_str_lit_147, &_va_Array_210_ek, _va_Array_210_eo, &_til_str_lit_148);
    OutOfBounds_delete(_va_Array_210_eo, 1);
    Str_delete(&_til_str_lit_148, (Bool){0});
    panic(_va_Array_210, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7632 = ((Bool)(!(cond)));
    (void)hoisted__Bool_7632;
    if (hoisted__Bool_7632) {
        U64 hoisted__U64_7628 = 1ULL;
        (void)hoisted__U64_7628;
        Array__Str *_va_Array_211 = Array__Str_new(hoisted__U64_7628);
        (void)_va_Array_211;
        I64 _va_Array_211_ek = 0;
        (void)_va_Array_211_ek;
        OutOfBounds *_va_Array_211_eo = malloc(sizeof(OutOfBounds));
        _va_Array_211_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_211_eo;
        U64 hoisted__U64_7629 = 0ULL;
        (void)hoisted__U64_7629;
        (void)_til_str_lit_149;
        (void)_til_str_lit_149;
        (void)_til_str_lit_150;
        (void)_til_str_lit_150;
        Array__Str_set(_va_Array_211, hoisted__U64_7629, &_til_str_lit_149, &_va_Array_211_ek, _va_Array_211_eo, &_til_str_lit_150);
        OutOfBounds_delete(_va_Array_211_eo, 1);
        Str_delete(&_til_str_lit_150, (Bool){0});
        panic(_va_Array_211, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7642 = parts;
        (void)_fc_Array__Str_7642;
        (void)_fc_Array__Str_7642;
        U64 _fi_USize_7642 = 0ULL;
        (void)_fi_USize_7642;
        while (1) {
            U64 hoisted__U64_7644 = (_fc_Array__Str_7642->cap);
            (void)hoisted__U64_7644;
            Bool _wcond_Bool_7643 = ((Bool)(_fi_USize_7642 < hoisted__U64_7644));
            (void)_wcond_Bool_7643;
            if (_wcond_Bool_7643) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7642, &_fi_USize_7642);
            U64 hoisted__U64_7645 = 1ULL;
            (void)hoisted__U64_7645;
            U64 hoisted__U64_7646 = ((U64)(_fi_USize_7642 + hoisted__U64_7645));
            (void)hoisted__U64_7646;
            _fi_USize_7642 = hoisted__U64_7646;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7691 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7691;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7691;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U64 hoisted__U64_7692 = 0ULL;
    (void)hoisted__U64_7692;
    U64 hoisted__U64_7693 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_7692); });
    (void)hoisted__U64_7693;
    return hoisted__U64_7693;
    __builtin_unreachable();
}

U64 Range_size(void) {
    U64 hoisted__U64_7724 = 16ULL;
    (void)hoisted__U64_7724;
    return hoisted__U64_7724;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7740 = 3;
    (void)hoisted__I64_7740;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    assert_eq__I64(result, hoisted__I64_7740, &_til_str_lit_153);
    Str_delete(&_til_str_lit_153, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7748 = 15;
    (void)hoisted__I64_7748;
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    assert_eq__I64(result, hoisted__I64_7748, &_til_str_lit_154);
    Str_delete(&_til_str_lit_154, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7756 = 26;
    (void)hoisted__I64_7756;
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    assert_eq__I64(result, hoisted__I64_7756, &_til_str_lit_155);
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
    I64 hoisted__I64_7843 = 106;
    (void)hoisted__I64_7843;
    (void)_til_str_lit_165;
    (void)_til_str_lit_165;
    assert_eq__I64(d3, hoisted__I64_7843, &_til_str_lit_165);
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
    I64 hoisted__I64_8446 = 8;
    (void)hoisted__I64_8446;
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert_eq__I64(result, hoisted__I64_8446, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8450 = 1;
    (void)hoisted__Bool_8450;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert(hoisted__Bool_8450, &_til_str_lit_171);
    Str_delete(&_til_str_lit_171, (Bool){0});
    Bool hoisted__Bool_8454 = 1;
    (void)hoisted__Bool_8454;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    assert(hoisted__Bool_8454, &_til_str_lit_172);
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
    CfVec2 hoisted__CfVec2_8472 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8472;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8472;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U64 hoisted__U64_8473 = 0ULL;
    (void)hoisted__U64_8473;
    U64 hoisted__U64_8474 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8473); });
    (void)hoisted__U64_8474;
    return hoisted__U64_8474;
    __builtin_unreachable();
}

U64 CfVec2_size(void) {
    U64 hoisted__U64_8505 = 16ULL;
    (void)hoisted__U64_8505;
    return hoisted__U64_8505;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8506 = 42;
    (void)hoisted__I64_8506;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__I64(v.x, hoisted__I64_8506, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
    I64 hoisted__I64_8508 = 99;
    (void)hoisted__I64_8508;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    assert_eq__I64(v.y, hoisted__I64_8508, &_til_str_lit_180);
    Str_delete(&_til_str_lit_180, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8512 = 10;
    (void)hoisted__I64_8512;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__I64(p.x, hoisted__I64_8512, &_til_str_lit_181);
    Str_delete(&_til_str_lit_181, (Bool){0});
    I64 hoisted__I64_8514 = 20;
    (void)hoisted__I64_8514;
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    assert_eq__I64(p.y, hoisted__I64_8514, &_til_str_lit_182);
    Str_delete(&_til_str_lit_182, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8521 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8521;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8521;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U64 hoisted__U64_8522 = 0ULL;
    (void)hoisted__U64_8522;
    U64 hoisted__U64_8523 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8522); });
    (void)hoisted__U64_8523;
    return hoisted__U64_8523;
    __builtin_unreachable();
}

U64 CfRect_size(void) {
    U64 hoisted__U64_8554 = 32ULL;
    (void)hoisted__U64_8554;
    return hoisted__U64_8554;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8555 = 5;
    (void)hoisted__I64_8555;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(r.top_left.x, hoisted__I64_8555, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_8557 = 10;
    (void)hoisted__I64_8557;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(r.top_left.y, hoisted__I64_8557, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    I64 hoisted__I64_8559 = 100;
    (void)hoisted__I64_8559;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8559, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    I64 hoisted__I64_8561 = 200;
    (void)hoisted__I64_8561;
    (void)_til_str_lit_189;
    (void)_til_str_lit_189;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8561, &_til_str_lit_189);
    Str_delete(&_til_str_lit_189, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8564 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8564;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8564;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U64 hoisted__U64_8565 = 0ULL;
    (void)hoisted__U64_8565;
    U64 hoisted__U64_8566 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U64))til_closure->call)(til_closure->env, self, hoisted__U64_8565); });
    (void)hoisted__U64_8566;
    return hoisted__U64_8566;
    __builtin_unreachable();
}

U64 CfVec3f_size(void) {
    U64 hoisted__U64_8609 = 12ULL;
    (void)hoisted__U64_8609;
    return hoisted__U64_8609;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8613 = F32_to_str(v.x);
    (void)hoisted__Str_8613;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    assert_eq__Str(hoisted__Str_8613, &_til_str_lit_191, &_til_str_lit_192);
    Str_delete(hoisted__Str_8613, 1);
    Str_delete(&_til_str_lit_191, (Bool){0});
    Str_delete(&_til_str_lit_192, (Bool){0});
    Str *hoisted__Str_8616 = F32_to_str(v.y);
    (void)hoisted__Str_8616;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    assert_eq__Str(hoisted__Str_8616, &_til_str_lit_193, &_til_str_lit_194);
    Str_delete(hoisted__Str_8616, 1);
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str_delete(&_til_str_lit_194, (Bool){0});
    Str *hoisted__Str_8619 = F32_to_str(v.z);
    (void)hoisted__Str_8619;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    (void)_til_str_lit_196;
    (void)_til_str_lit_196;
    assert_eq__Str(hoisted__Str_8619, &_til_str_lit_195, &_til_str_lit_196);
    Str_delete(hoisted__Str_8619, 1);
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
    U64 hoisted__U64_8630 = 1ULL;
    (void)hoisted__U64_8630;
    Bool hoisted__Bool_8631 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_8631;
    if (hoisted__Bool_8631) {
        U64 hoisted__U64_8624 = 1ULL;
        (void)hoisted__U64_8624;
        Bool hoisted__Bool_8625 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_8625;
        { Bool _ret_val = hoisted__Bool_8625;
                return _ret_val; }
    }
    U64 hoisted__U64_8632 = 1ULL;
    (void)hoisted__U64_8632;
    Bool hoisted__Bool_8633 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_8633;
    if (hoisted__Bool_8633) {
        U64 hoisted__U64_8626 = 1ULL;
        (void)hoisted__U64_8626;
        Bool hoisted__Bool_8627 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_8627;
        { Bool _ret_val = hoisted__Bool_8627;
                return _ret_val; }
    }
    U64 hoisted__U64_8634 = 1ULL;
    (void)hoisted__U64_8634;
    Bool hoisted__Bool_8635 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_8635;
    if (hoisted__Bool_8635) {
        U64 hoisted__U64_8628 = 1ULL;
        (void)hoisted__U64_8628;
        Bool hoisted__Bool_8629 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_8629;
        { Bool _ret_val = hoisted__Bool_8629;
                return _ret_val; }
    }
    Bool hoisted__Bool_8636 = 0;
    (void)hoisted__Bool_8636;
    return hoisted__Bool_8636;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8644 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8644;
    if (hoisted__Bool_8644) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8645 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8645;
    if (hoisted__Bool_8645) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8646 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8646;
    if (hoisted__Bool_8646) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8647 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8647;
    UNREACHABLE(&hoisted__Str_8647);
    Str_delete(&hoisted__Str_8647, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

U64 Color_size(void) {
    U64 hoisted__U64_8648 = 1ULL;
    (void)hoisted__U64_8648;
    return hoisted__U64_8648;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8649 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8649;
    (void)_til_str_lit_200;
    (void)_til_str_lit_200;
    assert(hoisted__Bool_8649, &_til_str_lit_200);
    Str_delete(&_til_str_lit_200, (Bool){0});
    Bool hoisted__Bool_8651 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8651;
    Bool hoisted__Bool_8652 = ((Bool)(!(hoisted__Bool_8651)));
    (void)hoisted__Bool_8652;
    (void)_til_str_lit_201;
    (void)_til_str_lit_201;
    assert(hoisted__Bool_8652, &_til_str_lit_201);
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
Bool Token_is(Token * self, Token * other) {
    U64 hoisted__U64_8654 = 1ULL;
    (void)hoisted__U64_8654;
    Bool hoisted__Bool_8655 = ((Bool)(((Token *)(self))->tag == ((Token *)(other))->tag));
    (void)hoisted__Bool_8655;
    return hoisted__Bool_8655;
    __builtin_unreachable();
}

void Token_delete(Token * self, Bool call_free) {
    U64 hoisted__U64_8679 = 1ULL;
    (void)hoisted__U64_8679;
    Bool hoisted__Bool_8680 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8680;
    if (hoisted__Bool_8680) {
        I64 *hoisted__I64_8675 = get_payload(self);
        (void)hoisted__I64_8675;
        (void)hoisted__I64_8675;
        Bool hoisted__Bool_8676 = 0;
        (void)hoisted__Bool_8676;
        I64_delete(hoisted__I64_8675, hoisted__Bool_8676);
    }
    U64 hoisted__U64_8681 = 1ULL;
    (void)hoisted__U64_8681;
    Bool hoisted__Bool_8682 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8682;
    if (hoisted__Bool_8682) {
        Str *hoisted__Str_8677 = get_payload(self);
        (void)hoisted__Str_8677;
        (void)hoisted__Str_8677;
        Bool hoisted__Bool_8678 = 0;
        (void)hoisted__Bool_8678;
        Str_delete(hoisted__Str_8677, hoisted__Bool_8678);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U64 hoisted__U64_8716 = 1ULL;
    (void)hoisted__U64_8716;
    Bool hoisted__Bool_8717 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8717;
    if (hoisted__Bool_8717) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8713 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8713;
        { Token * _ret_val = hoisted__Token_8713;
                return _ret_val; }
    }
    U64 hoisted__U64_8718 = 1ULL;
    (void)hoisted__U64_8718;
    Bool hoisted__Bool_8719 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8719;
    if (hoisted__Bool_8719) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8714 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8714;
        Token *hoisted__Token_8715 = Token_Name(hoisted__Str_8714);
        (void)hoisted__Token_8715;
        { Token * _ret_val = hoisted__Token_8715;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

U64 Token_size(void) {
    U64 hoisted__U64_8720 = 32ULL;
    (void)hoisted__U64_8720;
    return hoisted__U64_8720;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8722 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8722;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_8722, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
    Bool hoisted__Bool_8724 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8724;
    Bool hoisted__Bool_8725 = ((Bool)(!(hoisted__Bool_8724)));
    (void)hoisted__Bool_8725;
    (void)_til_str_lit_205;
    (void)_til_str_lit_205;
    assert(hoisted__Bool_8725, &_til_str_lit_205);
    Str_delete(&_til_str_lit_205, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8727 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8727;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_8727, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
    Bool hoisted__Bool_8729 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8729;
    Bool hoisted__Bool_8730 = ((Bool)(!(hoisted__Bool_8729)));
    (void)hoisted__Bool_8730;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_8730, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8734 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8734;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_8734, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Bool hoisted__Bool_8736 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8736;
    Bool hoisted__Bool_8737 = ((Bool)(!(hoisted__Bool_8736)));
    (void)hoisted__Bool_8737;
    (void)_til_str_lit_209;
    (void)_til_str_lit_209;
    assert(hoisted__Bool_8737, &_til_str_lit_209);
    Str_delete(&_til_str_lit_209, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8870 = ((Bool)(a != b));
    (void)hoisted__Bool_8870;
    if (hoisted__Bool_8870) {
        U64 hoisted__U64_8854 = 5ULL;
        (void)hoisted__U64_8854;
        Array__Str *_va_Array_253 = Array__Str_new(hoisted__U64_8854);
        (void)_va_Array_253;
        I64 _va_Array_253_ek = 0;
        (void)_va_Array_253_ek;
        OutOfBounds *_va_Array_253_eo = malloc(sizeof(OutOfBounds));
        _va_Array_253_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_253_eo;
        U64 hoisted__U64_8855 = 0ULL;
        (void)hoisted__U64_8855;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_253, hoisted__U64_8855, &_til_str_lit_210, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8858 = 1ULL;
        (void)hoisted__U64_8858;
        Str *hoisted__Str_8859 = I64_to_str(a);
        (void)hoisted__Str_8859;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_253, hoisted__U64_8858, hoisted__Str_8859, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8861 = 2ULL;
        (void)hoisted__U64_8861;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_253, hoisted__U64_8861, &_til_str_lit_212, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8864 = 3ULL;
        (void)hoisted__U64_8864;
        Str *hoisted__Str_8865 = I64_to_str(b);
        (void)hoisted__Str_8865;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_253, hoisted__U64_8864, hoisted__Str_8865, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8867 = 4ULL;
        (void)hoisted__U64_8867;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_253, hoisted__U64_8867, &_til_str_lit_213, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_211);
        OutOfBounds_delete(_va_Array_253_eo, 1);
        Str_delete(&_til_str_lit_211, (Bool){0});
        panic(_va_Array_253, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8887 = Str_neq(a, b);
    (void)hoisted__Bool_8887;
    if (hoisted__Bool_8887) {
        U64 hoisted__U64_8871 = 5ULL;
        (void)hoisted__U64_8871;
        Array__Str *_va_Array_254 = Array__Str_new(hoisted__U64_8871);
        (void)_va_Array_254;
        I64 _va_Array_254_ek = 0;
        (void)_va_Array_254_ek;
        OutOfBounds *_va_Array_254_eo = malloc(sizeof(OutOfBounds));
        _va_Array_254_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_254_eo;
        U64 hoisted__U64_8872 = 0ULL;
        (void)hoisted__U64_8872;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_254, hoisted__U64_8872, &_til_str_lit_210, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8875 = 1ULL;
        (void)hoisted__U64_8875;
        Str *hoisted__Str_8876 = Str_to_str(a);
        (void)hoisted__Str_8876;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_254, hoisted__U64_8875, hoisted__Str_8876, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8878 = 2ULL;
        (void)hoisted__U64_8878;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_254, hoisted__U64_8878, &_til_str_lit_212, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8881 = 3ULL;
        (void)hoisted__U64_8881;
        Str *hoisted__Str_8882 = Str_to_str(b);
        (void)hoisted__Str_8882;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_254, hoisted__U64_8881, hoisted__Str_8882, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_211);
        Str_delete(&_til_str_lit_211, (Bool){0});
        U64 hoisted__U64_8884 = 4ULL;
        (void)hoisted__U64_8884;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        Array__Str_set(_va_Array_254, hoisted__U64_8884, &_til_str_lit_213, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_211);
        OutOfBounds_delete(_va_Array_254_eo, 1);
        Str_delete(&_til_str_lit_211, (Bool){0});
        panic(_va_Array_254, loc);
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
Bool Token_is_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Token_is(_a0, _a1);
}
static __attribute__((unused)) TilClosure Token_is_dyn__til_closure = { (void *)Token_is_dyn, NULL, NULL };
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
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)&Token_is_dyn__til_closure;
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
