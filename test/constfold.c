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
    U32 count;
    U32 cap;
} Str;


typedef struct OutOfBounds {
    Str msg;
} OutOfBounds;


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
    U32 count;
    U32 cap;
} Vec__Bool;


typedef struct Vec__I64 {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__I64;


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
U32 Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
Array__Str * Array__Str_new(U32 cap);
U32 Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, U32 * i);
void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val);
void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
U32 Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
U32 Vec__Str_size(void);
U32 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
Bool and(Bool a, Bool b);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
U32 FuncType_size(void);
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
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
U32 LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
U32 IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
U32 FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
U32 StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
U32 EnumDef_size(void);
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
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
U32 NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
U32 Expr_size(void);
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
U32 Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
U32 Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
U32 Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
U32 Vec__Expr_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Bool is_null(void * p);
void swap(void * a, void * b, U64 size);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
U32 Range_size(void);
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
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
U32 CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
U32 Token_size(void);
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
U32 Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
Array__Str * Array__Str_new(U32 cap);
U32 Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, U32 * i);
void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val);
void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
U32 Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
U32 Vec__Str_size(void);
U32 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
Bool and(Bool a, Bool b);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
U32 FuncType_size(void);
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
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
U32 LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
U32 IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
U32 FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
U32 StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
U32 EnumDef_size(void);
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
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
U32 NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
U32 Expr_size(void);
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
U32 Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
U32 Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
U32 Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
U32 Vec__Expr_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Bool is_null(void * p);
void swap(void * a, void * b, U64 size);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
U32 Range_size(void);
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
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
U32 CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
U32 Token_size(void);
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
static __attribute__((unused)) Str _til_str_lit_3 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_4 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_5 = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_6 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_7 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_8 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_9 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_10 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_11 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_12 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_13 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_14 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_15 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_16 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_17 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_18 = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_19 = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_20 = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_21 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_22 = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_23 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_24 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_25 = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_26 = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_27 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_28 = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_29 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_30 = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_31 = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_32 = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_33 = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_34 = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_35 = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_36 = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_37 = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_38 = (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_39 = (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_40 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_41 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_42 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_43 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_44 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_214 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

U32 CAP_LIT;
U32 CAP_VIEW;
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;
Str __til_docs_blob__;
Str __til_info_blob__;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_115 = parts;
        (void)_fc_Array__Str_115;
        (void)_fc_Array__Str_115;
        U32 _fi_USize_115 = 0;
        (void)_fi_USize_115;
        while (1) {
            U32 hoisted__U32_117 = Array__Str_len(_fc_Array__Str_115);
            (void)hoisted__U32_117;
            Bool _wcond_Bool_116 = ((Bool)(_fi_USize_115 < hoisted__U32_117));
            (void)_wcond_Bool_116;
            if (_wcond_Bool_116) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_115, &_fi_USize_115);
            U32 hoisted__U32_118 = 1;
            (void)hoisted__U32_118;
            U32 hoisted__U32_119 = ((U32)(_fi_USize_115 + hoisted__U32_118));
            (void)hoisted__U32_119;
            _fi_USize_115 = hoisted__U32_119;
            U32 hoisted__U32_120 = Str_len(s);
            (void)hoisted__U32_120;
            U32 hoisted__U32_121 = ((U32)(total + hoisted__U32_120));
            (void)hoisted__U32_121;
            total = hoisted__U32_121;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_122 = parts;
        (void)_fc_Array__Str_122;
        (void)_fc_Array__Str_122;
        U32 _fi_USize_122 = 0;
        (void)_fi_USize_122;
        while (1) {
            U32 hoisted__U32_124 = Array__Str_len(_fc_Array__Str_122);
            (void)hoisted__U32_124;
            Bool _wcond_Bool_123 = ((Bool)(_fi_USize_122 < hoisted__U32_124));
            (void)_wcond_Bool_123;
            if (_wcond_Bool_123) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_122, &_fi_USize_122);
            U32 hoisted__U32_125 = 1;
            (void)hoisted__U32_125;
            U32 hoisted__U32_126 = ((U32)(_fi_USize_122 + hoisted__U32_125));
            (void)hoisted__U32_126;
            _fi_USize_122 = hoisted__U32_126;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
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
    I64 hoisted__I64_147 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_147;
    return hoisted__I64_147;
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
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_156 = 0;
    (void)hoisted__U32_156;
    Bool hoisted__Bool_157 = ((Bool)(n == hoisted__U32_156));
    (void)hoisted__Bool_157;
    if (hoisted__Bool_157) {
        static Str hoisted__Str_155 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_155;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_155; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U32 hoisted__U32_158 = 1;
    (void)hoisted__U32_158;
    U32 hoisted__U64_159 = ((U64)(n + hoisted__U32_158));
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
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_176 = 0;
    (void)hoisted__U32_176;
    Bool hoisted__Bool_177 = ((Bool)(s->count == hoisted__U32_176));
    (void)hoisted__Bool_177;
    if (hoisted__Bool_177) {
        return;
    }
    Bool hoisted__Bool_178 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_178;
    if (hoisted__Bool_178) {
        U32 hoisted__U32_166 = 1;
        (void)hoisted__U32_166;
        Array__Str *_va_Array_3 = Array__Str_new(hoisted__U32_166);
        (void)_va_Array_3;
        I64 _va_Array_3_ek = 0;
        (void)_va_Array_3_ek;
        OutOfBounds *_va_Array_3_eo = malloc(sizeof(OutOfBounds));
        _va_Array_3_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_3_eo;
        U32 hoisted__U32_167 = 0;
        (void)hoisted__U32_167;
        static Str hoisted__Str_168 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_168;
        static Str hoisted__Str_169 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_169;
        Array__Str_set(_va_Array_3, hoisted__U32_167, &hoisted__Str_168, &_va_Array_3_ek, _va_Array_3_eo, &hoisted__Str_169);
        OutOfBounds_delete(_va_Array_3_eo, 1);
        Str_delete(&hoisted__Str_169, (Bool){0});
        static Str hoisted__Str_170 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_170;
        panic(_va_Array_3, &hoisted__Str_170);
        Str_delete(&hoisted__Str_170, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_179 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_179;
    if (hoisted__Bool_179) {
        U32 hoisted__U32_171 = 1;
        (void)hoisted__U32_171;
        Array__Str *_va_Array_4 = Array__Str_new(hoisted__U32_171);
        (void)_va_Array_4;
        I64 _va_Array_4_ek = 0;
        (void)_va_Array_4_ek;
        OutOfBounds *_va_Array_4_eo = malloc(sizeof(OutOfBounds));
        _va_Array_4_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_4_eo;
        U32 hoisted__U32_172 = 0;
        (void)hoisted__U32_172;
        static Str hoisted__Str_173 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_173;
        static Str hoisted__Str_174 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_174;
        Array__Str_set(_va_Array_4, hoisted__U32_172, &hoisted__Str_173, &_va_Array_4_ek, _va_Array_4_eo, &hoisted__Str_174);
        OutOfBounds_delete(_va_Array_4_eo, 1);
        Str_delete(&hoisted__Str_174, (Bool){0});
        static Str hoisted__Str_175 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_175;
        panic(_va_Array_4, &hoisted__Str_175);
        Str_delete(&hoisted__Str_175, (Bool){0});
    }
    void *hoisted__v_180 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_180;
    (void)hoisted__v_180;
    memcpy(hoisted__v_180, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_181 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_181;
    (void)hoisted__v_181;
    I32 hoisted__I32_182 = 0;
    (void)hoisted__I32_182;
    U64 hoisted__U64_183 = 1ULL;
    (void)hoisted__U64_183;
    memset(hoisted__v_181, hoisted__I32_182, hoisted__U64_183);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_185 = 0;
    (void)hoisted__U32_185;
    Bool hoisted__Bool_186 = ((Bool)(val->count == hoisted__U32_185));
    (void)hoisted__Bool_186;
    if (hoisted__Bool_186) {
        static Str hoisted__Str_184 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_184;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_184; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U32 hoisted__U32_187 = 1;
    (void)hoisted__U32_187;
    U32 hoisted__U64_188 = ((U64)(val->count + hoisted__U32_187));
    (void)hoisted__U64_188;
    void * new_data = malloc(hoisted__U64_188);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_189 = ptr_add(new_data, val->count);
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
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_193 = Str_clone(self);
    (void)hoisted__Str_193;
    return hoisted__Str_193;
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
    U64 hoisted__U64_391 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_391;
    return hoisted__U64_391;
}

U32 Str_size(void) {
    U32 hoisted__U32_575 = 16;
    (void)hoisted__U32_575;
    return hoisted__U32_575;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_584 = Str_eq(a, b);
    (void)hoisted__Bool_584;
    Bool hoisted__Bool_585 = ((Bool)(!(hoisted__Bool_584)));
    (void)hoisted__Bool_585;
    return hoisted__Bool_585;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_676 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_676->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_676;
    return hoisted__OutOfBounds_676;
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
    U32 hoisted__U32_678 = 0;
    (void)hoisted__U32_678;
    U64 hoisted__U64_679 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_678); });
    (void)hoisted__U64_679;
    return hoisted__U64_679;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_698 = 16;
    (void)hoisted__U32_698;
    return hoisted__U32_698;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_722 = 16;
    (void)hoisted__U32_722;
    U64 hoisted__U64_723 = (U64)(cap);
    (void)hoisted__U64_723;
    U64 hoisted__U64_724 = (U64)(hoisted__U32_722);
    (void)hoisted__U64_724;
    void * hoisted__v_725 = calloc(hoisted__U64_723, hoisted__U64_724);
    (void)hoisted__v_725;
    Array__Str *hoisted__Array__Str_726 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_726->data = hoisted__v_725;
    hoisted__Array__Str_726->cap = cap;
    (void)hoisted__Array__Str_726;
    return hoisted__Array__Str_726;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_727 = 16;
    (void)hoisted__U32_727;
    U32 hoisted__U32_728 = ((U32)(DEREF(i) * hoisted__U32_727));
    (void)hoisted__U32_728;
    U64 hoisted__U64_729 = (U64)(hoisted__U32_728);
    (void)hoisted__U64_729;
    void *hoisted__v_730 = ptr_add(self->data, hoisted__U64_729);
    (void)hoisted__v_730;
    (void)hoisted__v_730;
    return hoisted__v_730;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_757 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_757;
    (void)hoisted__Str_757;
    Bool hoisted__Bool_758 = 0;
    (void)hoisted__Bool_758;
    Str_delete(hoisted__Str_757, hoisted__Bool_758);
    U32 hoisted__U32_759 = 16;
    (void)hoisted__U32_759;
    Str *hoisted__Str_760 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_760;
    (void)hoisted__Str_760;
    U64 hoisted__U64_761 = (U64)(hoisted__U32_759);
    (void)hoisted__U64_761;
    memcpy(hoisted__Str_760, val, hoisted__U64_761);
    U32 hoisted__U32_762 = 16;
    (void)hoisted__U32_762;
    I32 hoisted__I32_763 = 0;
    (void)hoisted__I32_763;
    U64 hoisted__U64_764 = (U64)(hoisted__U32_762);
    (void)hoisted__U64_764;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_763, hoisted__U64_764); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_787 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_787;
    if (hoisted__Bool_787) {
        U32 hoisted__U32_765 = 6;
        (void)hoisted__U32_765;
        Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_765);
        (void)_va_Array_16;
        I64 _va_Array_16_ek = 0;
        (void)_va_Array_16_ek;
        OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
        _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_16_eo;
        U32 hoisted__U32_766 = 0;
        (void)hoisted__U32_766;
        Str *hoisted__Str_767 = Str_clone(loc);
        (void)hoisted__Str_767;
        static Str hoisted__Str_768 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_768;
        Array__Str_set(_va_Array_16, hoisted__U32_766, hoisted__Str_767, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_768);
        Str_delete(&hoisted__Str_768, (Bool){0});
        U32 hoisted__U32_769 = 1;
        (void)hoisted__U32_769;
        static Str hoisted__Str_770 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_770;
        static Str hoisted__Str_771 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_771;
        Array__Str_set(_va_Array_16, hoisted__U32_769, &hoisted__Str_770, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_771);
        Str_delete(&hoisted__Str_771, (Bool){0});
        U32 hoisted__U32_772 = 2;
        (void)hoisted__U32_772;
        Str *hoisted__Str_773 = U32_to_str(i);
        (void)hoisted__Str_773;
        static Str hoisted__Str_774 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_774;
        Array__Str_set(_va_Array_16, hoisted__U32_772, hoisted__Str_773, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_774);
        Str_delete(&hoisted__Str_774, (Bool){0});
        U32 hoisted__U32_775 = 3;
        (void)hoisted__U32_775;
        static Str hoisted__Str_776 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_776;
        static Str hoisted__Str_777 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_777;
        Array__Str_set(_va_Array_16, hoisted__U32_775, &hoisted__Str_776, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_777);
        Str_delete(&hoisted__Str_777, (Bool){0});
        U32 hoisted__U32_778 = 4;
        (void)hoisted__U32_778;
        Str *hoisted__Str_779 = U32_to_str(self->cap);
        (void)hoisted__Str_779;
        static Str hoisted__Str_780 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_780;
        Array__Str_set(_va_Array_16, hoisted__U32_778, hoisted__Str_779, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_780);
        Str_delete(&hoisted__Str_780, (Bool){0});
        U32 hoisted__U32_781 = 5;
        (void)hoisted__U32_781;
        static Str hoisted__Str_782 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_782;
        static Str hoisted__Str_783 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_783;
        Array__Str_set(_va_Array_16, hoisted__U32_781, &hoisted__Str_782, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_783);
        OutOfBounds_delete(_va_Array_16_eo, 1);
        Str_delete(&hoisted__Str_783, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_784 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_16); hoisted__OutOfBounds_784->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_784;
        U32 hoisted__U32_785 = 16;
        (void)hoisted__U32_785;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_784, hoisted__U32_785);
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
        U32 _re_U32_790 = self->cap;
        (void)_re_U32_790;
        U32 _rc_U32_790 = 0;
        (void)_rc_U32_790;
        Bool hoisted__Bool_803 = ((Bool)(_rc_U32_790 <= _re_U32_790));
        (void)hoisted__Bool_803;
        if (hoisted__Bool_803) {
            while (1) {
                Bool _wcond_Bool_791 = ((Bool)(_rc_U32_790 < _re_U32_790));
                (void)_wcond_Bool_791;
                if (_wcond_Bool_791) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_790);
                U32_inc(&_rc_U32_790);
                U32 hoisted__U32_792 = 16;
                (void)hoisted__U32_792;
                U32 hoisted__U32_793 = ((U32)(i * hoisted__U32_792));
                (void)hoisted__U32_793;
                U64 hoisted__U64_794 = (U64)(hoisted__U32_793);
                (void)hoisted__U64_794;
                Str *hoisted__Str_795 = ptr_add(self->data, hoisted__U64_794);
                (void)hoisted__Str_795;
                (void)hoisted__Str_795;
                Bool hoisted__Bool_796 = 0;
                (void)hoisted__Bool_796;
                Str_delete(hoisted__Str_795, hoisted__Bool_796);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_797 = ((Bool)(_rc_U32_790 > _re_U32_790));
                (void)_wcond_Bool_797;
                if (_wcond_Bool_797) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_790);
                U32_dec(&_rc_U32_790);
                U32 hoisted__U32_798 = 16;
                (void)hoisted__U32_798;
                U32 hoisted__U32_799 = ((U32)(i * hoisted__U32_798));
                (void)hoisted__U32_799;
                U64 hoisted__U64_800 = (U64)(hoisted__U32_799);
                (void)hoisted__U64_800;
                Str *hoisted__Str_801 = ptr_add(self->data, hoisted__U64_800);
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
    U32 hoisted__U32_832 = 16;
    (void)hoisted__U32_832;
    U32 hoisted__U32_833 = ((U32)(self->cap * hoisted__U32_832));
    (void)hoisted__U32_833;
    U64 hoisted__U64_834 = (U64)(hoisted__U32_833);
    (void)hoisted__U64_834;
    void * new_data = malloc(hoisted__U64_834);
    {
        U32 _re_U32_804 = self->cap;
        (void)_re_U32_804;
        U32 _rc_U32_804 = 0;
        (void)_rc_U32_804;
        Bool hoisted__Bool_831 = ((Bool)(_rc_U32_804 <= _re_U32_804));
        (void)hoisted__Bool_831;
        if (hoisted__Bool_831) {
            while (1) {
                Bool _wcond_Bool_805 = ((Bool)(_rc_U32_804 < _re_U32_804));
                (void)_wcond_Bool_805;
                if (_wcond_Bool_805) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_804);
                U32_inc(&_rc_U32_804);
                U32 hoisted__U32_806 = 16;
                (void)hoisted__U32_806;
                U32 hoisted__U32_807 = ((U32)(i * hoisted__U32_806));
                (void)hoisted__U32_807;
                U64 hoisted__U64_808 = (U64)(hoisted__U32_807);
                (void)hoisted__U64_808;
                Str *src = ptr_add(self->data, hoisted__U64_808);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_809 = 16;
                (void)hoisted__U32_809;
                U32 hoisted__U32_810 = ((U32)(i * hoisted__U32_809));
                (void)hoisted__U32_810;
                U64 hoisted__U64_811 = (U64)(hoisted__U32_810);
                (void)hoisted__U64_811;
                U32 hoisted__U32_812 = 16;
                (void)hoisted__U32_812;
                void *hoisted__v_813 = ptr_add(new_data, hoisted__U64_811);
                (void)hoisted__v_813;
                (void)hoisted__v_813;
                U64 hoisted__U64_814 = (U64)(hoisted__U32_812);
                (void)hoisted__U64_814;
                memcpy(hoisted__v_813, cloned, hoisted__U64_814);
                U32 hoisted__U32_815 = 16;
                (void)hoisted__U32_815;
                I32 hoisted__I32_816 = 0;
                (void)hoisted__I32_816;
                U64 hoisted__U64_817 = (U64)(hoisted__U32_815);
                (void)hoisted__U64_817;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_816, hoisted__U64_817); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_818 = ((Bool)(_rc_U32_804 > _re_U32_804));
                (void)_wcond_Bool_818;
                if (_wcond_Bool_818) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_804);
                U32_dec(&_rc_U32_804);
                U32 hoisted__U32_819 = 16;
                (void)hoisted__U32_819;
                U32 hoisted__U32_820 = ((U32)(i * hoisted__U32_819));
                (void)hoisted__U32_820;
                U64 hoisted__U64_821 = (U64)(hoisted__U32_820);
                (void)hoisted__U64_821;
                Str *src = ptr_add(self->data, hoisted__U64_821);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_822 = 16;
                (void)hoisted__U32_822;
                U32 hoisted__U32_823 = ((U32)(i * hoisted__U32_822));
                (void)hoisted__U32_823;
                U64 hoisted__U64_824 = (U64)(hoisted__U32_823);
                (void)hoisted__U64_824;
                U32 hoisted__U32_825 = 16;
                (void)hoisted__U32_825;
                void *hoisted__v_826 = ptr_add(new_data, hoisted__U64_824);
                (void)hoisted__v_826;
                (void)hoisted__v_826;
                U64 hoisted__U64_827 = (U64)(hoisted__U32_825);
                (void)hoisted__U64_827;
                memcpy(hoisted__v_826, cloned, hoisted__U64_827);
                U32 hoisted__U32_828 = 16;
                (void)hoisted__U32_828;
                I32 hoisted__I32_829 = 0;
                (void)hoisted__I32_829;
                U64 hoisted__U64_830 = (U64)(hoisted__U32_828);
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
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_836 = 16;
    (void)hoisted__U32_836;
    return hoisted__U32_836;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_837 = 16;
    (void)hoisted__U32_837;
    U64 hoisted__U64_838 = (U64)(hoisted__U32_837);
    (void)hoisted__U64_838;
    void * hoisted__v_839 = malloc(hoisted__U64_838);
    (void)hoisted__v_839;
    U32 hoisted__U32_840 = 0;
    (void)hoisted__U32_840;
    I64 hoisted__I64_841 = 1;
    (void)hoisted__I64_841;
    Vec__Str *hoisted__Vec__Str_842 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_842->data = hoisted__v_839;
    hoisted__Vec__Str_842->count = hoisted__U32_840;
    hoisted__Vec__Str_842->cap = hoisted__I64_841;
    (void)hoisted__Vec__Str_842;
    return hoisted__Vec__Str_842;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_852 = self->count;
        (void)_re_U32_852;
        U32 _rc_U32_852 = 0;
        (void)_rc_U32_852;
        Bool hoisted__Bool_865 = ((Bool)(_rc_U32_852 <= _re_U32_852));
        (void)hoisted__Bool_865;
        if (hoisted__Bool_865) {
            while (1) {
                Bool _wcond_Bool_853 = ((Bool)(_rc_U32_852 < _re_U32_852));
                (void)_wcond_Bool_853;
                if (_wcond_Bool_853) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_852);
                U32_inc(&_rc_U32_852);
                U32 hoisted__U32_854 = 16;
                (void)hoisted__U32_854;
                U32 hoisted__U32_855 = ((U32)(i * hoisted__U32_854));
                (void)hoisted__U32_855;
                U64 hoisted__U64_856 = (U64)(hoisted__U32_855);
                (void)hoisted__U64_856;
                Str *hoisted__Str_857 = ptr_add(self->data, hoisted__U64_856);
                (void)hoisted__Str_857;
                (void)hoisted__Str_857;
                Bool hoisted__Bool_858 = 0;
                (void)hoisted__Bool_858;
                Str_delete(hoisted__Str_857, hoisted__Bool_858);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_859 = ((Bool)(_rc_U32_852 > _re_U32_852));
                (void)_wcond_Bool_859;
                if (_wcond_Bool_859) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_852);
                U32_dec(&_rc_U32_852);
                U32 hoisted__U32_860 = 16;
                (void)hoisted__U32_860;
                U32 hoisted__U32_861 = ((U32)(i * hoisted__U32_860));
                (void)hoisted__U32_861;
                U64 hoisted__U64_862 = (U64)(hoisted__U32_861);
                (void)hoisted__U64_862;
                Str *hoisted__Str_863 = ptr_add(self->data, hoisted__U64_862);
                (void)hoisted__Str_863;
                (void)hoisted__Str_863;
                Bool hoisted__Bool_864 = 0;
                (void)hoisted__Bool_864;
                Str_delete(hoisted__Str_863, hoisted__Bool_864);
            }
        }
    }
    U32 hoisted__U32_866 = 0;
    (void)hoisted__U32_866;
    self->count = hoisted__U32_866;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1136 = 16;
    (void)hoisted__U32_1136;
    U32 hoisted__U32_1137 = ((U32)(self->cap * hoisted__U32_1136));
    (void)hoisted__U32_1137;
    U64 hoisted__U64_1138 = (U64)(hoisted__U32_1137);
    (void)hoisted__U64_1138;
    void * new_data = malloc(hoisted__U64_1138);
    {
        U32 _re_U32_1108 = self->count;
        (void)_re_U32_1108;
        U32 _rc_U32_1108 = 0;
        (void)_rc_U32_1108;
        Bool hoisted__Bool_1135 = ((Bool)(_rc_U32_1108 <= _re_U32_1108));
        (void)hoisted__Bool_1135;
        if (hoisted__Bool_1135) {
            while (1) {
                Bool _wcond_Bool_1109 = ((Bool)(_rc_U32_1108 < _re_U32_1108));
                (void)_wcond_Bool_1109;
                if (_wcond_Bool_1109) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1108);
                U32_inc(&_rc_U32_1108);
                U32 hoisted__U32_1110 = 16;
                (void)hoisted__U32_1110;
                U32 hoisted__U32_1111 = ((U32)(i * hoisted__U32_1110));
                (void)hoisted__U32_1111;
                U64 hoisted__U64_1112 = (U64)(hoisted__U32_1111);
                (void)hoisted__U64_1112;
                Str *src = ptr_add(self->data, hoisted__U64_1112);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1113 = 16;
                (void)hoisted__U32_1113;
                U32 hoisted__U32_1114 = ((U32)(i * hoisted__U32_1113));
                (void)hoisted__U32_1114;
                U64 hoisted__U64_1115 = (U64)(hoisted__U32_1114);
                (void)hoisted__U64_1115;
                U32 hoisted__U32_1116 = 16;
                (void)hoisted__U32_1116;
                void *hoisted__v_1117 = ptr_add(new_data, hoisted__U64_1115);
                (void)hoisted__v_1117;
                (void)hoisted__v_1117;
                U64 hoisted__U64_1118 = (U64)(hoisted__U32_1116);
                (void)hoisted__U64_1118;
                memcpy(hoisted__v_1117, cloned, hoisted__U64_1118);
                U32 hoisted__U32_1119 = 16;
                (void)hoisted__U32_1119;
                I32 hoisted__I32_1120 = 0;
                (void)hoisted__I32_1120;
                U64 hoisted__U64_1121 = (U64)(hoisted__U32_1119);
                (void)hoisted__U64_1121;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1120, hoisted__U64_1121); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1122 = ((Bool)(_rc_U32_1108 > _re_U32_1108));
                (void)_wcond_Bool_1122;
                if (_wcond_Bool_1122) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1108);
                U32_dec(&_rc_U32_1108);
                U32 hoisted__U32_1123 = 16;
                (void)hoisted__U32_1123;
                U32 hoisted__U32_1124 = ((U32)(i * hoisted__U32_1123));
                (void)hoisted__U32_1124;
                U64 hoisted__U64_1125 = (U64)(hoisted__U32_1124);
                (void)hoisted__U64_1125;
                Str *src = ptr_add(self->data, hoisted__U64_1125);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1126 = 16;
                (void)hoisted__U32_1126;
                U32 hoisted__U32_1127 = ((U32)(i * hoisted__U32_1126));
                (void)hoisted__U32_1127;
                U64 hoisted__U64_1128 = (U64)(hoisted__U32_1127);
                (void)hoisted__U64_1128;
                U32 hoisted__U32_1129 = 16;
                (void)hoisted__U32_1129;
                void *hoisted__v_1130 = ptr_add(new_data, hoisted__U64_1128);
                (void)hoisted__v_1130;
                (void)hoisted__v_1130;
                U64 hoisted__U64_1131 = (U64)(hoisted__U32_1129);
                (void)hoisted__U64_1131;
                memcpy(hoisted__v_1130, cloned, hoisted__U64_1131);
                U32 hoisted__U32_1132 = 16;
                (void)hoisted__U32_1132;
                I32 hoisted__I32_1133 = 0;
                (void)hoisted__I32_1133;
                U64 hoisted__U64_1134 = (U64)(hoisted__U32_1132);
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
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1140 = 16;
    (void)hoisted__U32_1140;
    return hoisted__U32_1140;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1143 = 8;
    (void)hoisted__U32_1143;
    return hoisted__U32_1143;
}

void * Dynamic_clone(void * self) {
    return self;
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

U32 U8_size(void) {
    U32 hoisted__U32_1159 = 1;
    (void)hoisted__U32_1159;
    return hoisted__U32_1159;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1244 = 0;
    (void)hoisted__U32_1244;
    U64 hoisted__U64_1245 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1244); });
    (void)hoisted__U64_1245;
    return hoisted__U64_1245;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_1345 = U32_to_i64(val);
    (void)hoisted__I64_1345;
    Str *hoisted__Str_1346 = I64_to_str(hoisted__I64_1345);
    (void)hoisted__Str_1346;
    return hoisted__Str_1346;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_1347 = 1;
    (void)hoisted__U32_1347;
    U32 hoisted__U32_1348 = ((U32)(DEREF(self) + hoisted__U32_1347));
    (void)hoisted__U32_1348;
    *self = hoisted__U32_1348;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_1349 = 1;
    (void)hoisted__U32_1349;
    U32 hoisted__U32_1350 = ((U32)(DEREF(self) - hoisted__U32_1349));
    (void)hoisted__U32_1350;
    *self = hoisted__U32_1350;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_1357 = 4;
    (void)hoisted__U32_1357;
    return hoisted__U32_1357;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1442 = 0;
    (void)hoisted__U32_1442;
    U64 hoisted__U64_1443 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1442); });
    (void)hoisted__U64_1443;
    return hoisted__U64_1443;
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1444 = U64_to_str_ext(val);
    (void)hoisted__Str_1444;
    return hoisted__Str_1444;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_1453 = 8;
    (void)hoisted__U32_1453;
    return hoisted__U32_1453;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1538 = 0;
    (void)hoisted__U32_1538;
    U64 hoisted__U64_1539 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1538); });
    (void)hoisted__U64_1539;
    return hoisted__U64_1539;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_1560 = 1;
    (void)hoisted__U32_1560;
    return hoisted__U32_1560;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1561 = 0;
    (void)hoisted__U32_1561;
    U64 hoisted__U64_1562 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1561); });
    (void)hoisted__U64_1562;
    return hoisted__U64_1562;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_1747 = 4;
    (void)hoisted__U32_1747;
    return hoisted__U32_1747;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1889 = 0;
    (void)hoisted__U32_1889;
    U64 hoisted__U64_1890 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1889); });
    (void)hoisted__U64_1890;
    return hoisted__U64_1890;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1901 = 0;
    (void)hoisted__I64_1901;
    Bool hoisted__Bool_1902 = ((Bool)(val < hoisted__I64_1901));
    (void)hoisted__Bool_1902;
    if (hoisted__Bool_1902) {
        U64 hoisted__U64_1891 = 0ULL;
        (void)hoisted__U64_1891;
        U64 hoisted__U64_1892 = (U64)(val);
        (void)hoisted__U64_1892;
        U64 mag = ((U64)(hoisted__U64_1891 - hoisted__U64_1892));
        U32 hoisted__U32_1893 = 2;
        (void)hoisted__U32_1893;
        Array__Str *_va_Array_44 = Array__Str_new(hoisted__U32_1893);
        (void)_va_Array_44;
        I64 _va_Array_44_ek = 0;
        (void)_va_Array_44_ek;
        OutOfBounds *_va_Array_44_eo = malloc(sizeof(OutOfBounds));
        _va_Array_44_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_44_eo;
        U32 hoisted__U32_1894 = 0;
        (void)hoisted__U32_1894;
        static Str hoisted__Str_1895 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1895;
        static Str hoisted__Str_1896 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1896;
        Array__Str_set(_va_Array_44, hoisted__U32_1894, &hoisted__Str_1895, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1896);
        Str_delete(&hoisted__Str_1896, (Bool){0});
        U32 hoisted__U32_1897 = 1;
        (void)hoisted__U32_1897;
        Str *hoisted__Str_1898 = U64_to_str(mag);
        (void)hoisted__Str_1898;
        static Str hoisted__Str_1899 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1899;
        Array__Str_set(_va_Array_44, hoisted__U32_1897, hoisted__Str_1898, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1899);
        OutOfBounds_delete(_va_Array_44_eo, 1);
        Str_delete(&hoisted__Str_1899, (Bool){0});
        Str *hoisted__Str_1900 = format(_va_Array_44);
        (void)hoisted__Str_1900;
        { Str * _ret_val = hoisted__Str_1900;
                return _ret_val; }
    }
    U64 hoisted__U64_1903 = (U64)(val);
    (void)hoisted__U64_1903;
    Str *hoisted__Str_1904 = U64_to_str(hoisted__U64_1903);
    (void)hoisted__Str_1904;
    return hoisted__Str_1904;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1922 = 8;
    (void)hoisted__U32_1922;
    return hoisted__U32_1922;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2080 = 0;
    (void)hoisted__U32_2080;
    U64 hoisted__U64_2081 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2080); });
    (void)hoisted__U64_2081;
    return hoisted__U64_2081;
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_2083 = 4;
    (void)hoisted__U32_2083;
    return hoisted__U32_2083;
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_2101 = 0;
    (void)hoisted__U32_2101;
    U64 hoisted__U64_2102 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2101); });
    (void)hoisted__U64_2102;
    return hoisted__U64_2102;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2149 = 0;
    (void)_m_Bool_2149;
    {
        Bool hoisted__Bool_2152 = 1;
        (void)hoisted__Bool_2152;
        Bool hoisted__Bool_2153 = ((Bool)(a == hoisted__Bool_2152));
        (void)hoisted__Bool_2153;
        if (hoisted__Bool_2153) {
            Bool hoisted__Bool_2150 = (b);
            (void)hoisted__Bool_2150;
            _m_Bool_2149 = hoisted__Bool_2150;
        } else {
            Bool hoisted__Bool_2151 = 0;
            (void)hoisted__Bool_2151;
            _m_Bool_2149 = hoisted__Bool_2151;
        }
    }
    return _m_Bool_2149;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2163 = ((Bool)(a == b));
    (void)hoisted__Bool_2163;
    if (hoisted__Bool_2163) {
        I64 hoisted__I64_2161 = 0;
        (void)hoisted__I64_2161;
        { I64 _ret_val = hoisted__I64_2161;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2162 = -1;
        (void)hoisted__I64_2162;
        return hoisted__I64_2162;
    }
    I64 hoisted__I64_2164 = 1;
    (void)hoisted__I64_2164;
    return hoisted__I64_2164;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2165 = 1;
    (void)hoisted__U32_2165;
    return hoisted__U32_2165;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2166 = 0;
    (void)hoisted__U32_2166;
    U64 hoisted__U64_2167 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2166); });
    (void)hoisted__U64_2167;
    return hoisted__U64_2167;
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
    U32 hoisted__U32_2204 = 1;
    (void)hoisted__U32_2204;
    Bool hoisted__Bool_2205 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        U32 hoisted__U32_2184 = 1;
        (void)hoisted__U32_2184;
        Bool hoisted__Bool_2185 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2185;
        { Bool _ret_val = hoisted__Bool_2185;
                return _ret_val; }
    }
    U32 hoisted__U32_2206 = 1;
    (void)hoisted__U32_2206;
    Bool hoisted__Bool_2207 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2207;
    if (hoisted__Bool_2207) {
        U32 hoisted__U32_2186 = 1;
        (void)hoisted__U32_2186;
        Bool hoisted__Bool_2187 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2187;
        { Bool _ret_val = hoisted__Bool_2187;
                return _ret_val; }
    }
    U32 hoisted__U32_2208 = 1;
    (void)hoisted__U32_2208;
    Bool hoisted__Bool_2209 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2209;
    if (hoisted__Bool_2209) {
        U32 hoisted__U32_2188 = 1;
        (void)hoisted__U32_2188;
        Bool hoisted__Bool_2189 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2189;
        { Bool _ret_val = hoisted__Bool_2189;
                return _ret_val; }
    }
    U32 hoisted__U32_2210 = 1;
    (void)hoisted__U32_2210;
    Bool hoisted__Bool_2211 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2211;
    if (hoisted__Bool_2211) {
        U32 hoisted__U32_2190 = 1;
        (void)hoisted__U32_2190;
        Bool hoisted__Bool_2191 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2191;
        { Bool _ret_val = hoisted__Bool_2191;
                return _ret_val; }
    }
    U32 hoisted__U32_2212 = 1;
    (void)hoisted__U32_2212;
    Bool hoisted__Bool_2213 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2213;
    if (hoisted__Bool_2213) {
        U32 hoisted__U32_2192 = 1;
        (void)hoisted__U32_2192;
        Bool hoisted__Bool_2193 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2193;
        { Bool _ret_val = hoisted__Bool_2193;
                return _ret_val; }
    }
    U32 hoisted__U32_2214 = 1;
    (void)hoisted__U32_2214;
    Bool hoisted__Bool_2215 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2215;
    if (hoisted__Bool_2215) {
        U32 hoisted__U32_2194 = 1;
        (void)hoisted__U32_2194;
        Bool hoisted__Bool_2195 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2195;
        { Bool _ret_val = hoisted__Bool_2195;
                return _ret_val; }
    }
    U32 hoisted__U32_2216 = 1;
    (void)hoisted__U32_2216;
    Bool hoisted__Bool_2217 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2217;
    if (hoisted__Bool_2217) {
        U32 hoisted__U32_2196 = 1;
        (void)hoisted__U32_2196;
        Bool hoisted__Bool_2197 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2197;
        { Bool _ret_val = hoisted__Bool_2197;
                return _ret_val; }
    }
    U32 hoisted__U32_2218 = 1;
    (void)hoisted__U32_2218;
    Bool hoisted__Bool_2219 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2219;
    if (hoisted__Bool_2219) {
        U32 hoisted__U32_2198 = 1;
        (void)hoisted__U32_2198;
        Bool hoisted__Bool_2199 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2199;
        { Bool _ret_val = hoisted__Bool_2199;
                return _ret_val; }
    }
    U32 hoisted__U32_2220 = 1;
    (void)hoisted__U32_2220;
    Bool hoisted__Bool_2221 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        U32 hoisted__U32_2200 = 1;
        (void)hoisted__U32_2200;
        Bool hoisted__Bool_2201 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2201;
        { Bool _ret_val = hoisted__Bool_2201;
                return _ret_val; }
    }
    U32 hoisted__U32_2222 = 1;
    (void)hoisted__U32_2222;
    Bool hoisted__Bool_2223 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        U32 hoisted__U32_2202 = 1;
        (void)hoisted__U32_2202;
        Bool hoisted__Bool_2203 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_2203;
        { Bool _ret_val = hoisted__Bool_2203;
                return _ret_val; }
    }
    Bool hoisted__Bool_2224 = 0;
    (void)hoisted__Bool_2224;
    return hoisted__Bool_2224;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2246 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2246;
    if (hoisted__Bool_2246) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2247 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2247;
    if (hoisted__Bool_2247) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2248 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2248;
    if (hoisted__Bool_2248) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2249 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2249;
    if (hoisted__Bool_2249) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2250 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2250;
    if (hoisted__Bool_2250) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2251 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2251;
    if (hoisted__Bool_2251) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2252 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2252;
    if (hoisted__Bool_2252) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2253 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2253;
    if (hoisted__Bool_2253) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2254 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2254;
    if (hoisted__Bool_2254) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2255 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2255;
    if (hoisted__Bool_2255) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2256 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2256;
    UNREACHABLE(&hoisted__Str_2256);
    Str_delete(&hoisted__Str_2256, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2257 = 1;
    (void)hoisted__U32_2257;
    return hoisted__U32_2257;
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
    U32 hoisted__U32_2338 = 1;
    (void)hoisted__U32_2338;
    Bool hoisted__Bool_2339 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2339;
    if (hoisted__Bool_2339) {
        Str *hoisted__Str_2328 = get_payload(self);
        (void)hoisted__Str_2328;
        (void)hoisted__Str_2328;
        Bool hoisted__Bool_2329 = 0;
        (void)hoisted__Bool_2329;
        Str_delete(hoisted__Str_2328, hoisted__Bool_2329);
    }
    U32 hoisted__U32_2340 = 1;
    (void)hoisted__U32_2340;
    Bool hoisted__Bool_2341 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        Str *hoisted__Str_2330 = get_payload(self);
        (void)hoisted__Str_2330;
        (void)hoisted__Str_2330;
        Bool hoisted__Bool_2331 = 0;
        (void)hoisted__Bool_2331;
        Str_delete(hoisted__Str_2330, hoisted__Bool_2331);
    }
    U32 hoisted__U32_2342 = 1;
    (void)hoisted__U32_2342;
    Bool hoisted__Bool_2343 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2343;
    if (hoisted__Bool_2343) {
        Str *hoisted__Str_2332 = get_payload(self);
        (void)hoisted__Str_2332;
        (void)hoisted__Str_2332;
        Bool hoisted__Bool_2333 = 0;
        (void)hoisted__Bool_2333;
        Str_delete(hoisted__Str_2332, hoisted__Bool_2333);
    }
    U32 hoisted__U32_2344 = 1;
    (void)hoisted__U32_2344;
    Bool hoisted__Bool_2345 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2345;
    if (hoisted__Bool_2345) {
        Primitive *hoisted__Primitive_2334 = get_payload(self);
        (void)hoisted__Primitive_2334;
        (void)hoisted__Primitive_2334;
        Bool hoisted__Bool_2335 = 0;
        (void)hoisted__Bool_2335;
        Primitive_delete(hoisted__Primitive_2334, hoisted__Bool_2335);
    }
    U32 hoisted__U32_2346 = 1;
    (void)hoisted__U32_2346;
    Bool hoisted__Bool_2347 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2347;
    if (hoisted__Bool_2347) {
        Str *hoisted__Str_2336 = get_payload(self);
        (void)hoisted__Str_2336;
        (void)hoisted__Str_2336;
        Bool hoisted__Bool_2337 = 0;
        (void)hoisted__Bool_2337;
        Str_delete(hoisted__Str_2336, hoisted__Bool_2337);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U32 hoisted__U32_2448 = 1;
    (void)hoisted__U32_2448;
    Bool hoisted__Bool_2449 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2449;
    if (hoisted__Bool_2449) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U32 hoisted__U32_2450 = 1;
    (void)hoisted__U32_2450;
    Bool hoisted__Bool_2451 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2451;
    if (hoisted__Bool_2451) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U32 hoisted__U32_2452 = 1;
    (void)hoisted__U32_2452;
    Bool hoisted__Bool_2453 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2453;
    if (hoisted__Bool_2453) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2438 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2438;
        Type *hoisted__Type_2439 = Type_Struct(hoisted__Str_2438);
        (void)hoisted__Type_2439;
        { Type * _ret_val = hoisted__Type_2439;
                return _ret_val; }
    }
    U32 hoisted__U32_2454 = 1;
    (void)hoisted__U32_2454;
    Bool hoisted__Bool_2455 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2455;
    if (hoisted__Bool_2455) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U32 hoisted__U32_2456 = 1;
    (void)hoisted__U32_2456;
    Bool hoisted__Bool_2457 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2457;
    if (hoisted__Bool_2457) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2440 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2440;
        Type *hoisted__Type_2441 = Type_Enum(hoisted__Str_2440);
        (void)hoisted__Type_2441;
        { Type * _ret_val = hoisted__Type_2441;
                return _ret_val; }
    }
    U32 hoisted__U32_2458 = 1;
    (void)hoisted__U32_2458;
    Bool hoisted__Bool_2459 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2459;
    if (hoisted__Bool_2459) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U32 hoisted__U32_2460 = 1;
    (void)hoisted__U32_2460;
    Bool hoisted__Bool_2461 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2461;
    if (hoisted__Bool_2461) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U32 hoisted__U32_2462 = 1;
    (void)hoisted__U32_2462;
    Bool hoisted__Bool_2463 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2463;
    if (hoisted__Bool_2463) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U32 hoisted__U32_2464 = 1;
    (void)hoisted__U32_2464;
    Bool hoisted__Bool_2465 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2465;
    if (hoisted__Bool_2465) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U32 hoisted__U32_2466 = 1;
    (void)hoisted__U32_2466;
    Bool hoisted__Bool_2467 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2467;
    if (hoisted__Bool_2467) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2442 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2442;
        Type *hoisted__Type_2443 = Type_Custom(hoisted__Str_2442);
        (void)hoisted__Type_2443;
        { Type * _ret_val = hoisted__Type_2443;
                return _ret_val; }
    }
    U32 hoisted__U32_2468 = 1;
    (void)hoisted__U32_2468;
    Bool hoisted__Bool_2469 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2469;
    if (hoisted__Bool_2469) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2444 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2444;
        Type *hoisted__Type_2445 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2444; _oa; }));
        (void)hoisted__Type_2445;
        { Type * _ret_val = hoisted__Type_2445;
                return _ret_val; }
    }
    U32 hoisted__U32_2470 = 1;
    (void)hoisted__U32_2470;
    Bool hoisted__Bool_2471 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2471;
    if (hoisted__Bool_2471) {
        Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2446 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2446;
        Type *hoisted__Type_2447 = Type_FuncPtrSig(hoisted__Str_2446);
        (void)hoisted__Type_2447;
        { Type * _ret_val = hoisted__Type_2447;
                return _ret_val; }
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
}

U32 Type_size(void) {
    U32 hoisted__U32_2472 = 24;
    (void)hoisted__U32_2472;
    return hoisted__U32_2472;
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
    U32 hoisted__U32_2620 = 1;
    (void)hoisted__U32_2620;
    Bool hoisted__Bool_2621 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2621;
    if (hoisted__Bool_2621) {
        U32 hoisted__U32_2600 = 1;
        (void)hoisted__U32_2600;
        Bool hoisted__Bool_2601 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2601;
        { Bool _ret_val = hoisted__Bool_2601;
                return _ret_val; }
    }
    U32 hoisted__U32_2622 = 1;
    (void)hoisted__U32_2622;
    Bool hoisted__Bool_2623 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2623;
    if (hoisted__Bool_2623) {
        U32 hoisted__U32_2602 = 1;
        (void)hoisted__U32_2602;
        Bool hoisted__Bool_2603 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2603;
        { Bool _ret_val = hoisted__Bool_2603;
                return _ret_val; }
    }
    U32 hoisted__U32_2624 = 1;
    (void)hoisted__U32_2624;
    Bool hoisted__Bool_2625 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2625;
    if (hoisted__Bool_2625) {
        U32 hoisted__U32_2604 = 1;
        (void)hoisted__U32_2604;
        Bool hoisted__Bool_2605 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2605;
        { Bool _ret_val = hoisted__Bool_2605;
                return _ret_val; }
    }
    U32 hoisted__U32_2626 = 1;
    (void)hoisted__U32_2626;
    Bool hoisted__Bool_2627 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2627;
    if (hoisted__Bool_2627) {
        U32 hoisted__U32_2606 = 1;
        (void)hoisted__U32_2606;
        Bool hoisted__Bool_2607 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2607;
        { Bool _ret_val = hoisted__Bool_2607;
                return _ret_val; }
    }
    U32 hoisted__U32_2628 = 1;
    (void)hoisted__U32_2628;
    Bool hoisted__Bool_2629 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2629;
    if (hoisted__Bool_2629) {
        U32 hoisted__U32_2608 = 1;
        (void)hoisted__U32_2608;
        Bool hoisted__Bool_2609 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2609;
        { Bool _ret_val = hoisted__Bool_2609;
                return _ret_val; }
    }
    U32 hoisted__U32_2630 = 1;
    (void)hoisted__U32_2630;
    Bool hoisted__Bool_2631 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2631;
    if (hoisted__Bool_2631) {
        U32 hoisted__U32_2610 = 1;
        (void)hoisted__U32_2610;
        Bool hoisted__Bool_2611 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2611;
        { Bool _ret_val = hoisted__Bool_2611;
                return _ret_val; }
    }
    U32 hoisted__U32_2632 = 1;
    (void)hoisted__U32_2632;
    Bool hoisted__Bool_2633 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2633;
    if (hoisted__Bool_2633) {
        U32 hoisted__U32_2612 = 1;
        (void)hoisted__U32_2612;
        Bool hoisted__Bool_2613 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2613;
        { Bool _ret_val = hoisted__Bool_2613;
                return _ret_val; }
    }
    U32 hoisted__U32_2634 = 1;
    (void)hoisted__U32_2634;
    Bool hoisted__Bool_2635 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2635;
    if (hoisted__Bool_2635) {
        U32 hoisted__U32_2614 = 1;
        (void)hoisted__U32_2614;
        Bool hoisted__Bool_2615 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2615;
        { Bool _ret_val = hoisted__Bool_2615;
                return _ret_val; }
    }
    U32 hoisted__U32_2636 = 1;
    (void)hoisted__U32_2636;
    Bool hoisted__Bool_2637 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2637;
    if (hoisted__Bool_2637) {
        U32 hoisted__U32_2616 = 1;
        (void)hoisted__U32_2616;
        Bool hoisted__Bool_2617 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2617;
        { Bool _ret_val = hoisted__Bool_2617;
                return _ret_val; }
    }
    U32 hoisted__U32_2638 = 1;
    (void)hoisted__U32_2638;
    Bool hoisted__Bool_2639 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2639;
    if (hoisted__Bool_2639) {
        U32 hoisted__U32_2618 = 1;
        (void)hoisted__U32_2618;
        Bool hoisted__Bool_2619 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2619;
        { Bool _ret_val = hoisted__Bool_2619;
                return _ret_val; }
    }
    Bool hoisted__Bool_2640 = 0;
    (void)hoisted__Bool_2640;
    return hoisted__Bool_2640;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2662 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2662;
    if (hoisted__Bool_2662) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2663 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2663;
    if (hoisted__Bool_2663) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2664 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2664;
    if (hoisted__Bool_2664) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2665 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2665;
    if (hoisted__Bool_2665) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2666 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2666;
    if (hoisted__Bool_2666) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2667 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2667;
    if (hoisted__Bool_2667) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2668 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2668;
    if (hoisted__Bool_2668) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2669 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2669;
    if (hoisted__Bool_2669) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2670 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2670;
    if (hoisted__Bool_2670) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2671 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2671;
    if (hoisted__Bool_2671) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2672 = (Str){.c_str = (void *)"FuncType.clone:130:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2672;
    UNREACHABLE(&hoisted__Str_2672);
    Str_delete(&hoisted__Str_2672, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2673 = 1;
    (void)hoisted__U32_2673;
    return hoisted__U32_2673;
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
    U32 hoisted__U32_2682 = 1;
    (void)hoisted__U32_2682;
    Bool hoisted__Bool_2683 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2683;
    if (hoisted__Bool_2683) {
        U32 hoisted__U32_2676 = 1;
        (void)hoisted__U32_2676;
        Bool hoisted__Bool_2677 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2677;
        { Bool _ret_val = hoisted__Bool_2677;
                return _ret_val; }
    }
    U32 hoisted__U32_2684 = 1;
    (void)hoisted__U32_2684;
    Bool hoisted__Bool_2685 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2685;
    if (hoisted__Bool_2685) {
        U32 hoisted__U32_2678 = 1;
        (void)hoisted__U32_2678;
        Bool hoisted__Bool_2679 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2679;
        { Bool _ret_val = hoisted__Bool_2679;
                return _ret_val; }
    }
    U32 hoisted__U32_2686 = 1;
    (void)hoisted__U32_2686;
    Bool hoisted__Bool_2687 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2687;
    if (hoisted__Bool_2687) {
        U32 hoisted__U32_2680 = 1;
        (void)hoisted__U32_2680;
        Bool hoisted__Bool_2681 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2681;
        { Bool _ret_val = hoisted__Bool_2681;
                return _ret_val; }
    }
    Bool hoisted__Bool_2688 = 0;
    (void)hoisted__Bool_2688;
    return hoisted__Bool_2688;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2696 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2696;
    if (hoisted__Bool_2696) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2697 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2697;
    if (hoisted__Bool_2697) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2698 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2698;
    if (hoisted__Bool_2698) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2699 = (Str){.c_str = (void *)"OwnType.clone:142:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2699;
    UNREACHABLE(&hoisted__Str_2699);
    Str_delete(&hoisted__Str_2699, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2700 = 1;
    (void)hoisted__U32_2700;
    return hoisted__U32_2700;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2702 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2702;
    Declaration *hoisted__Declaration_2703 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2703->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2703->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2703->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2703->is_mut = self->is_mut;
    hoisted__Declaration_2703->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2703->is_priv = self->is_priv;
    hoisted__Declaration_2703->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2703->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2703->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2703->default_value = hoisted__Expr_2702;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2703->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2703;
    return hoisted__Declaration_2703;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2704 = 0;
    (void)hoisted__Bool_2704;
    Str_delete(&self->name, hoisted__Bool_2704);
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    Str_delete(&self->doc, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Str_delete(&self->explicit_type, hoisted__Bool_2706);
    Bool hoisted__Bool_2707 = 0;
    (void)hoisted__Bool_2707;
    Bool_delete(&self->is_mut, hoisted__Bool_2707);
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Bool_delete(&self->is_priv, hoisted__Bool_2709);
    Bool hoisted__Bool_2710 = 0;
    (void)hoisted__Bool_2710;
    Bool_delete(&self->used, hoisted__Bool_2710);
    Bool hoisted__Bool_2711 = 0;
    (void)hoisted__Bool_2711;
    OwnType_delete(&self->own_type, hoisted__Bool_2711);
    Bool hoisted__Bool_2712 = 0;
    (void)hoisted__Bool_2712;
    Type_delete(&self->til_type, hoisted__Bool_2712);
    Bool hoisted__Bool_2713 = 1;
    (void)hoisted__Bool_2713;
    Expr_delete(self->default_value, hoisted__Bool_2713);
    Bool hoisted__Bool_2714 = 0;
    (void)hoisted__Bool_2714;
    Str_delete(&self->orig_name, hoisted__Bool_2714);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2715 = 104;
    (void)hoisted__U32_2715;
    return hoisted__U32_2715;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2717 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2717->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2717->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2717->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2717->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2717->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2717->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2717->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2717->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2717->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2717->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2717->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2717->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2717;
    return hoisted__FunctionDef_2717;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    FuncType_delete(&self->func_type, hoisted__Bool_2718);
    Bool hoisted__Bool_2719 = 0;
    (void)hoisted__Bool_2719;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2719);
    Bool hoisted__Bool_2720 = 0;
    (void)hoisted__Bool_2720;
    Str_delete(&self->return_type, hoisted__Bool_2720);
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2721);
    Bool hoisted__Bool_2722 = 0;
    (void)hoisted__Bool_2722;
    I32_delete(&self->variadic_index, hoisted__Bool_2722);
    Bool hoisted__Bool_2723 = 0;
    (void)hoisted__Bool_2723;
    I32_delete(&self->kwargs_index, hoisted__Bool_2723);
    Bool hoisted__Bool_2724 = 0;
    (void)hoisted__Bool_2724;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2724);
    Bool hoisted__Bool_2725 = 0;
    (void)hoisted__Bool_2725;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2725);
    Bool hoisted__Bool_2726 = 0;
    (void)hoisted__Bool_2726;
    Bool_delete(&self->auto_generated, hoisted__Bool_2726);
    Bool hoisted__Bool_2727 = 0;
    (void)hoisted__Bool_2727;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2727);
    Bool hoisted__Bool_2728 = 0;
    (void)hoisted__Bool_2728;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2728);
    Bool hoisted__Bool_2729 = 0;
    (void)hoisted__Bool_2729;
    Str_delete(&self->closure_name, hoisted__Bool_2729);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2730 = 0;
    (void)hoisted__U32_2730;
    U64 hoisted__U64_2731 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2730); });
    (void)hoisted__U64_2731;
    return hoisted__U64_2731;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2732 = 104;
    (void)hoisted__U32_2732;
    return hoisted__U32_2732;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2735 = malloc(sizeof(FCallData));
    hoisted__FCallData_2735->is_splat = self->is_splat;
    hoisted__FCallData_2735->does_throw = self->does_throw;
    hoisted__FCallData_2735->is_bang = self->is_bang;
    hoisted__FCallData_2735->own_args = self->own_args;
    hoisted__FCallData_2735->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2735->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2735;
    return hoisted__FCallData_2735;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    Bool_delete(&self->is_splat, hoisted__Bool_2736);
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Bool_delete(&self->does_throw, hoisted__Bool_2737);
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Bool_delete(&self->is_bang, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    U64_delete(&self->own_args, hoisted__Bool_2739);
    Bool hoisted__Bool_2740 = 0;
    (void)hoisted__Bool_2740;
    Bool_delete(&self->swap_replace, hoisted__Bool_2740);
    Bool hoisted__Bool_2741 = 0;
    (void)hoisted__Bool_2741;
    Type_delete(&self->til_type, hoisted__Bool_2741);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2742 = 0;
    (void)hoisted__U32_2742;
    U64 hoisted__U64_2743 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2742); });
    (void)hoisted__U64_2743;
    return hoisted__U64_2743;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2744 = 48;
    (void)hoisted__U32_2744;
    return hoisted__U32_2744;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2756 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2756->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2756->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2756;
    return hoisted__LiteralNumData_2756;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2757 = 0;
    (void)hoisted__Bool_2757;
    Str_delete(&self->text, hoisted__Bool_2757);
    Bool hoisted__Bool_2758 = 0;
    (void)hoisted__Bool_2758;
    Type_delete(&self->til_type, hoisted__Bool_2758);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2759 = 0;
    (void)hoisted__U32_2759;
    U64 hoisted__U64_2760 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2759); });
    (void)hoisted__U64_2760;
    return hoisted__U64_2760;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2761 = 40;
    (void)hoisted__U32_2761;
    return hoisted__U32_2761;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2771 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2771->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2771->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2771;
    return hoisted__IdentData_2771;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2772 = 0;
    (void)hoisted__Bool_2772;
    Str_delete(&self->name, hoisted__Bool_2772);
    Bool hoisted__Bool_2773 = 0;
    (void)hoisted__Bool_2773;
    Type_delete(&self->til_type, hoisted__Bool_2773);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2774 = 0;
    (void)hoisted__U32_2774;
    U64 hoisted__U64_2775 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2774); });
    (void)hoisted__U64_2775;
    return hoisted__U64_2775;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2776 = 40;
    (void)hoisted__U32_2776;
    return hoisted__U32_2776;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2782 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2782->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2782->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2782;
    return hoisted__FieldAccessData_2782;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2783 = 0;
    (void)hoisted__Bool_2783;
    Str_delete(&self->name, hoisted__Bool_2783);
    Bool hoisted__Bool_2784 = 0;
    (void)hoisted__Bool_2784;
    Type_delete(&self->til_type, hoisted__Bool_2784);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2785 = 0;
    (void)hoisted__U32_2785;
    U64 hoisted__U64_2786 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2785); });
    (void)hoisted__U64_2786;
    return hoisted__U64_2786;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2787 = 40;
    (void)hoisted__U32_2787;
    return hoisted__U32_2787;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2866 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2866->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2866->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2866->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2866->is_interface = self->is_interface;
    hoisted__StructDef_2866->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2866->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2866;
    return hoisted__StructDef_2866;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2867 = 0;
    (void)hoisted__Bool_2867;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2867);
    Bool hoisted__Bool_2868 = 0;
    (void)hoisted__Bool_2868;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2868);
    Bool hoisted__Bool_2869 = 0;
    (void)hoisted__Bool_2869;
    Str_delete(&self->c_tag, hoisted__Bool_2869);
    Bool hoisted__Bool_2870 = 0;
    (void)hoisted__Bool_2870;
    Bool_delete(&self->is_interface, hoisted__Bool_2870);
    Bool hoisted__Bool_2871 = 0;
    (void)hoisted__Bool_2871;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2871);
    Bool hoisted__Bool_2872 = 0;
    (void)hoisted__Bool_2872;
    Str_delete(&self->implements_name, hoisted__Bool_2872);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2873 = 0;
    (void)hoisted__U32_2873;
    U64 hoisted__U64_2874 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2873); });
    (void)hoisted__U64_2874;
    return hoisted__U64_2874;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2875 = 72;
    (void)hoisted__U32_2875;
    return hoisted__U32_2875;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2880 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2880->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2880->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2880->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2880->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2880->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2880->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2880->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2880;
    return hoisted__EnumDef_2880;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2881 = 0;
    (void)hoisted__Bool_2881;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2881);
    Bool hoisted__Bool_2882 = 0;
    (void)hoisted__Bool_2882;
    Vec__Str_delete(&self->variants, hoisted__Bool_2882);
    Bool hoisted__Bool_2883 = 0;
    (void)hoisted__Bool_2883;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2883);
    Bool hoisted__Bool_2884 = 0;
    (void)hoisted__Bool_2884;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2884);
    Bool hoisted__Bool_2885 = 0;
    (void)hoisted__Bool_2885;
    Str_delete(&self->implements_name, hoisted__Bool_2885);
    Bool hoisted__Bool_2886 = 0;
    (void)hoisted__Bool_2886;
    Str_delete(&self->tag_type, hoisted__Bool_2886);
    Bool hoisted__Bool_2887 = 0;
    (void)hoisted__Bool_2887;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2887);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2888 = 0;
    (void)hoisted__U32_2888;
    U64 hoisted__U64_2889 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2888); });
    (void)hoisted__U64_2889;
    return hoisted__U64_2889;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2890 = 128;
    (void)hoisted__U32_2890;
    return hoisted__U32_2890;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2991 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2991->name = *_ca; free(_ca); }
    hoisted__AssignData_2991->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2991->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2991->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2991;
    return hoisted__AssignData_2991;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2992 = 0;
    (void)hoisted__Bool_2992;
    Str_delete(&self->name, hoisted__Bool_2992);
    Bool hoisted__Bool_2993 = 0;
    (void)hoisted__Bool_2993;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2993);
    Bool hoisted__Bool_2994 = 0;
    (void)hoisted__Bool_2994;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2994);
    Bool hoisted__Bool_2995 = 0;
    (void)hoisted__Bool_2995;
    Bool_delete(&self->swap_replace, hoisted__Bool_2995);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2996 = 0;
    (void)hoisted__U32_2996;
    U64 hoisted__U64_2997 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2996); });
    (void)hoisted__U64_2997;
    return hoisted__U64_2997;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2998 = 24;
    (void)hoisted__U32_2998;
    return hoisted__U32_2998;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_3000 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_3000->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_3000->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_3000;
    return hoisted__FieldAssignData_3000;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_3001 = 0;
    (void)hoisted__Bool_3001;
    Str_delete(&self->name, hoisted__Bool_3001);
    Bool hoisted__Bool_3002 = 0;
    (void)hoisted__Bool_3002;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3002);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_3003 = 0;
    (void)hoisted__U32_3003;
    U64 hoisted__U64_3004 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3003); });
    (void)hoisted__U64_3004;
    return hoisted__U64_3004;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_3005 = 24;
    (void)hoisted__U32_3005;
    return hoisted__U32_3005;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_3007 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_3007->name = *_ca; free(_ca); }
    hoisted__ForInData_3007->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_3007->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_3007->name2 = *_ca; free(_ca); }
    hoisted__ForInData_3007->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_3007;
    return hoisted__ForInData_3007;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_3008 = 0;
    (void)hoisted__Bool_3008;
    Str_delete(&self->name, hoisted__Bool_3008);
    Bool hoisted__Bool_3009 = 0;
    (void)hoisted__Bool_3009;
    Bool_delete(&self->is_mut, hoisted__Bool_3009);
    Bool hoisted__Bool_3010 = 0;
    (void)hoisted__Bool_3010;
    Type_delete(&self->til_type, hoisted__Bool_3010);
    Bool hoisted__Bool_3011 = 0;
    (void)hoisted__Bool_3011;
    Str_delete(&self->name2, hoisted__Bool_3011);
    Bool hoisted__Bool_3012 = 0;
    (void)hoisted__Bool_3012;
    Bool_delete(&self->is_mut2, hoisted__Bool_3012);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_3013 = 0;
    (void)hoisted__U32_3013;
    U64 hoisted__U64_3014 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3013); });
    (void)hoisted__U64_3014;
    return hoisted__U64_3014;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_3015 = 72;
    (void)hoisted__U32_3015;
    return hoisted__U32_3015;
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
    U32 hoisted__U32_3058 = 1;
    (void)hoisted__U32_3058;
    Bool hoisted__Bool_3059 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3059;
    if (hoisted__Bool_3059) {
        Str *hoisted__Str_3052 = get_payload(self);
        (void)hoisted__Str_3052;
        (void)hoisted__Str_3052;
        Bool hoisted__Bool_3053 = 0;
        (void)hoisted__Bool_3053;
        Str_delete(hoisted__Str_3052, hoisted__Bool_3053);
    }
    U32 hoisted__U32_3060 = 1;
    (void)hoisted__U32_3060;
    Bool hoisted__Bool_3061 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3061;
    if (hoisted__Bool_3061) {
        LiteralNumData *hoisted__LiteralNumData_3054 = get_payload(self);
        (void)hoisted__LiteralNumData_3054;
        (void)hoisted__LiteralNumData_3054;
        Bool hoisted__Bool_3055 = 0;
        (void)hoisted__Bool_3055;
        LiteralNumData_delete(hoisted__LiteralNumData_3054, hoisted__Bool_3055);
    }
    U32 hoisted__U32_3062 = 1;
    (void)hoisted__U32_3062;
    Bool hoisted__Bool_3063 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3063;
    if (hoisted__Bool_3063) {
        Bool *hoisted__Bool_3056 = get_payload(self);
        (void)hoisted__Bool_3056;
        (void)hoisted__Bool_3056;
        Bool hoisted__Bool_3057 = 0;
        (void)hoisted__Bool_3057;
        Bool_delete(hoisted__Bool_3056, hoisted__Bool_3057);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_3118 = 1;
    (void)hoisted__U32_3118;
    Bool hoisted__Bool_3119 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3119;
    if (hoisted__Bool_3119) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3113 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3113;
        Literal *hoisted__Literal_3114 = Literal_Str(hoisted__Str_3113);
        (void)hoisted__Literal_3114;
        { Literal * _ret_val = hoisted__Literal_3114;
                return _ret_val; }
    }
    U32 hoisted__U32_3120 = 1;
    (void)hoisted__U32_3120;
    Bool hoisted__Bool_3121 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3121;
    if (hoisted__Bool_3121) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3115 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3115;
        Literal *hoisted__Literal_3116 = Literal_Num(hoisted__LiteralNumData_3115);
        (void)hoisted__Literal_3116;
        { Literal * _ret_val = hoisted__Literal_3116;
                return _ret_val; }
    }
    U32 hoisted__U32_3122 = 1;
    (void)hoisted__U32_3122;
    Bool hoisted__Bool_3123 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3123;
    if (hoisted__Bool_3123) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3117 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3117;
        { Literal * _ret_val = hoisted__Literal_3117;
                return _ret_val; }
    }
    U32 hoisted__U32_3124 = 1;
    (void)hoisted__U32_3124;
    Bool hoisted__Bool_3125 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_3125;
    if (hoisted__Bool_3125) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U32 hoisted__U32_3126 = 1;
    (void)hoisted__U32_3126;
    Bool hoisted__Bool_3127 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_3127;
    if (hoisted__Bool_3127) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3128 = 48;
    (void)hoisted__U32_3128;
    return hoisted__U32_3128;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3131 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3131->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3131->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3131;
    return hoisted__MatchData_3131;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3132 = 0;
    (void)hoisted__Bool_3132;
    Type_delete(&self->til_type, hoisted__Bool_3132);
    Bool hoisted__Bool_3133 = 0;
    (void)hoisted__Bool_3133;
    Str_delete(&self->result_temp, hoisted__Bool_3133);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3134 = 0;
    (void)hoisted__U32_3134;
    U64 hoisted__U64_3135 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3134); });
    (void)hoisted__U64_3135;
    return hoisted__U64_3135;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3136 = 40;
    (void)hoisted__U32_3136;
    return hoisted__U32_3136;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3141 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3141->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3141->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3141;
    return hoisted__CaptureBlockData_3141;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3142 = 0;
    (void)hoisted__Bool_3142;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3142);
    Bool hoisted__Bool_3143 = 0;
    (void)hoisted__Bool_3143;
    Str_delete(&self->closure_name, hoisted__Bool_3143);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3144 = 0;
    (void)hoisted__U32_3144;
    U64 hoisted__U64_3145 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3144); });
    (void)hoisted__U64_3145;
    return hoisted__U64_3145;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3146 = 32;
    (void)hoisted__U32_3146;
    return hoisted__U32_3146;
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
    U32 hoisted__U32_3407 = 1;
    (void)hoisted__U32_3407;
    Bool hoisted__Bool_3408 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3408;
    if (hoisted__Bool_3408) {
        Literal *hoisted__Literal_3377 = get_payload(self);
        (void)hoisted__Literal_3377;
        (void)hoisted__Literal_3377;
        Bool hoisted__Bool_3378 = 0;
        (void)hoisted__Bool_3378;
        Literal_delete(hoisted__Literal_3377, hoisted__Bool_3378);
    }
    U32 hoisted__U32_3409 = 1;
    (void)hoisted__U32_3409;
    Bool hoisted__Bool_3410 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3410;
    if (hoisted__Bool_3410) {
        IdentData *hoisted__IdentData_3379 = get_payload(self);
        (void)hoisted__IdentData_3379;
        (void)hoisted__IdentData_3379;
        Bool hoisted__Bool_3380 = 0;
        (void)hoisted__Bool_3380;
        IdentData_delete(hoisted__IdentData_3379, hoisted__Bool_3380);
    }
    U32 hoisted__U32_3411 = 1;
    (void)hoisted__U32_3411;
    Bool hoisted__Bool_3412 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3412;
    if (hoisted__Bool_3412) {
        Declaration *hoisted__Declaration_3381 = get_payload(self);
        (void)hoisted__Declaration_3381;
        (void)hoisted__Declaration_3381;
        Bool hoisted__Bool_3382 = 0;
        (void)hoisted__Bool_3382;
        Declaration_delete(hoisted__Declaration_3381, hoisted__Bool_3382);
    }
    U32 hoisted__U32_3413 = 1;
    (void)hoisted__U32_3413;
    Bool hoisted__Bool_3414 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3414;
    if (hoisted__Bool_3414) {
        AssignData *hoisted__AssignData_3383 = get_payload(self);
        (void)hoisted__AssignData_3383;
        (void)hoisted__AssignData_3383;
        Bool hoisted__Bool_3384 = 0;
        (void)hoisted__Bool_3384;
        AssignData_delete(hoisted__AssignData_3383, hoisted__Bool_3384);
    }
    U32 hoisted__U32_3415 = 1;
    (void)hoisted__U32_3415;
    Bool hoisted__Bool_3416 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        FCallData *hoisted__FCallData_3385 = get_payload(self);
        (void)hoisted__FCallData_3385;
        (void)hoisted__FCallData_3385;
        Bool hoisted__Bool_3386 = 0;
        (void)hoisted__Bool_3386;
        FCallData_delete(hoisted__FCallData_3385, hoisted__Bool_3386);
    }
    U32 hoisted__U32_3417 = 1;
    (void)hoisted__U32_3417;
    Bool hoisted__Bool_3418 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        FunctionDef *hoisted__FunctionDef_3387 = get_payload(self);
        (void)hoisted__FunctionDef_3387;
        (void)hoisted__FunctionDef_3387;
        Bool hoisted__Bool_3388 = 0;
        (void)hoisted__Bool_3388;
        FunctionDef_delete(hoisted__FunctionDef_3387, hoisted__Bool_3388);
    }
    U32 hoisted__U32_3419 = 1;
    (void)hoisted__U32_3419;
    Bool hoisted__Bool_3420 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        StructDef *hoisted__StructDef_3389 = get_payload(self);
        (void)hoisted__StructDef_3389;
        (void)hoisted__StructDef_3389;
        Bool hoisted__Bool_3390 = 0;
        (void)hoisted__Bool_3390;
        StructDef_delete(hoisted__StructDef_3389, hoisted__Bool_3390);
    }
    U32 hoisted__U32_3421 = 1;
    (void)hoisted__U32_3421;
    Bool hoisted__Bool_3422 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3422;
    if (hoisted__Bool_3422) {
        EnumDef *hoisted__EnumDef_3391 = get_payload(self);
        (void)hoisted__EnumDef_3391;
        (void)hoisted__EnumDef_3391;
        Bool hoisted__Bool_3392 = 0;
        (void)hoisted__Bool_3392;
        EnumDef_delete(hoisted__EnumDef_3391, hoisted__Bool_3392);
    }
    U32 hoisted__U32_3423 = 1;
    (void)hoisted__U32_3423;
    Bool hoisted__Bool_3424 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3424;
    if (hoisted__Bool_3424) {
        FieldAccessData *hoisted__FieldAccessData_3393 = get_payload(self);
        (void)hoisted__FieldAccessData_3393;
        (void)hoisted__FieldAccessData_3393;
        Bool hoisted__Bool_3394 = 0;
        (void)hoisted__Bool_3394;
        FieldAccessData_delete(hoisted__FieldAccessData_3393, hoisted__Bool_3394);
    }
    U32 hoisted__U32_3425 = 1;
    (void)hoisted__U32_3425;
    Bool hoisted__Bool_3426 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3426;
    if (hoisted__Bool_3426) {
        FieldAssignData *hoisted__FieldAssignData_3395 = get_payload(self);
        (void)hoisted__FieldAssignData_3395;
        (void)hoisted__FieldAssignData_3395;
        Bool hoisted__Bool_3396 = 0;
        (void)hoisted__Bool_3396;
        FieldAssignData_delete(hoisted__FieldAssignData_3395, hoisted__Bool_3396);
    }
    U32 hoisted__U32_3427 = 1;
    (void)hoisted__U32_3427;
    Bool hoisted__Bool_3428 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3428;
    if (hoisted__Bool_3428) {
        ForInData *hoisted__ForInData_3397 = get_payload(self);
        (void)hoisted__ForInData_3397;
        (void)hoisted__ForInData_3397;
        Bool hoisted__Bool_3398 = 0;
        (void)hoisted__Bool_3398;
        ForInData_delete(hoisted__ForInData_3397, hoisted__Bool_3398);
    }
    U32 hoisted__U32_3429 = 1;
    (void)hoisted__U32_3429;
    Bool hoisted__Bool_3430 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3430;
    if (hoisted__Bool_3430) {
        Str *hoisted__Str_3399 = get_payload(self);
        (void)hoisted__Str_3399;
        (void)hoisted__Str_3399;
        Bool hoisted__Bool_3400 = 0;
        (void)hoisted__Bool_3400;
        Str_delete(hoisted__Str_3399, hoisted__Bool_3400);
    }
    U32 hoisted__U32_3431 = 1;
    (void)hoisted__U32_3431;
    Bool hoisted__Bool_3432 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3432;
    if (hoisted__Bool_3432) {
        MatchData *hoisted__MatchData_3401 = get_payload(self);
        (void)hoisted__MatchData_3401;
        (void)hoisted__MatchData_3401;
        Bool hoisted__Bool_3402 = 0;
        (void)hoisted__Bool_3402;
        MatchData_delete(hoisted__MatchData_3401, hoisted__Bool_3402);
    }
    U32 hoisted__U32_3433 = 1;
    (void)hoisted__U32_3433;
    Bool hoisted__Bool_3434 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3434;
    if (hoisted__Bool_3434) {
        CaptureBlockData *hoisted__CaptureBlockData_3403 = get_payload(self);
        (void)hoisted__CaptureBlockData_3403;
        (void)hoisted__CaptureBlockData_3403;
        Bool hoisted__Bool_3404 = 0;
        (void)hoisted__Bool_3404;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3403, hoisted__Bool_3404);
    }
    U32 hoisted__U32_3435 = 1;
    (void)hoisted__U32_3435;
    Bool hoisted__Bool_3436 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3436;
    if (hoisted__Bool_3436) {
        CaptureBlockData *hoisted__CaptureBlockData_3405 = get_payload(self);
        (void)hoisted__CaptureBlockData_3405;
        (void)hoisted__CaptureBlockData_3405;
        Bool hoisted__Bool_3406 = 0;
        (void)hoisted__Bool_3406;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3405, hoisted__Bool_3406);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3700 = 1;
    (void)hoisted__U32_3700;
    Bool hoisted__Bool_3701 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3701;
    if (hoisted__Bool_3701) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U32 hoisted__U32_3702 = 1;
    (void)hoisted__U32_3702;
    Bool hoisted__Bool_3703 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3703;
    if (hoisted__Bool_3703) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3672 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3672;
        NodeType *hoisted__NodeType_3673 = NodeType_Literal(hoisted__Literal_3672);
        (void)hoisted__NodeType_3673;
        { NodeType * _ret_val = hoisted__NodeType_3673;
                return _ret_val; }
    }
    U32 hoisted__U32_3704 = 1;
    (void)hoisted__U32_3704;
    Bool hoisted__Bool_3705 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3705;
    if (hoisted__Bool_3705) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3674 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3674;
        NodeType *hoisted__NodeType_3675 = NodeType_Ident(hoisted__IdentData_3674);
        (void)hoisted__NodeType_3675;
        { NodeType * _ret_val = hoisted__NodeType_3675;
                return _ret_val; }
    }
    U32 hoisted__U32_3706 = 1;
    (void)hoisted__U32_3706;
    Bool hoisted__Bool_3707 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3707;
    if (hoisted__Bool_3707) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3676 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3676;
        NodeType *hoisted__NodeType_3677 = NodeType_Decl(hoisted__Declaration_3676);
        (void)hoisted__NodeType_3677;
        { NodeType * _ret_val = hoisted__NodeType_3677;
                return _ret_val; }
    }
    U32 hoisted__U32_3708 = 1;
    (void)hoisted__U32_3708;
    Bool hoisted__Bool_3709 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3709;
    if (hoisted__Bool_3709) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3678 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3678;
        NodeType *hoisted__NodeType_3679 = NodeType_Assign(hoisted__AssignData_3678);
        (void)hoisted__NodeType_3679;
        { NodeType * _ret_val = hoisted__NodeType_3679;
                return _ret_val; }
    }
    U32 hoisted__U32_3710 = 1;
    (void)hoisted__U32_3710;
    Bool hoisted__Bool_3711 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3711;
    if (hoisted__Bool_3711) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3680 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3680;
        NodeType *hoisted__NodeType_3681 = NodeType_FCall(hoisted__FCallData_3680);
        (void)hoisted__NodeType_3681;
        { NodeType * _ret_val = hoisted__NodeType_3681;
                return _ret_val; }
    }
    U32 hoisted__U32_3712 = 1;
    (void)hoisted__U32_3712;
    Bool hoisted__Bool_3713 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3713;
    if (hoisted__Bool_3713) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3682 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3682;
        NodeType *hoisted__NodeType_3683 = NodeType_FuncDef(hoisted__FunctionDef_3682);
        (void)hoisted__NodeType_3683;
        { NodeType * _ret_val = hoisted__NodeType_3683;
                return _ret_val; }
    }
    U32 hoisted__U32_3714 = 1;
    (void)hoisted__U32_3714;
    Bool hoisted__Bool_3715 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3715;
    if (hoisted__Bool_3715) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3684 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3684;
        NodeType *hoisted__NodeType_3685 = NodeType_StructDef(hoisted__StructDef_3684);
        (void)hoisted__NodeType_3685;
        { NodeType * _ret_val = hoisted__NodeType_3685;
                return _ret_val; }
    }
    U32 hoisted__U32_3716 = 1;
    (void)hoisted__U32_3716;
    Bool hoisted__Bool_3717 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3717;
    if (hoisted__Bool_3717) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3686 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3686;
        NodeType *hoisted__NodeType_3687 = NodeType_EnumDef(hoisted__EnumDef_3686);
        (void)hoisted__NodeType_3687;
        { NodeType * _ret_val = hoisted__NodeType_3687;
                return _ret_val; }
    }
    U32 hoisted__U32_3718 = 1;
    (void)hoisted__U32_3718;
    Bool hoisted__Bool_3719 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3719;
    if (hoisted__Bool_3719) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3688 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3688;
        NodeType *hoisted__NodeType_3689 = NodeType_FieldAccess(hoisted__FieldAccessData_3688);
        (void)hoisted__NodeType_3689;
        { NodeType * _ret_val = hoisted__NodeType_3689;
                return _ret_val; }
    }
    U32 hoisted__U32_3720 = 1;
    (void)hoisted__U32_3720;
    Bool hoisted__Bool_3721 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3721;
    if (hoisted__Bool_3721) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3690 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3690;
        NodeType *hoisted__NodeType_3691 = NodeType_FieldAssign(hoisted__FieldAssignData_3690);
        (void)hoisted__NodeType_3691;
        { NodeType * _ret_val = hoisted__NodeType_3691;
                return _ret_val; }
    }
    U32 hoisted__U32_3722 = 1;
    (void)hoisted__U32_3722;
    Bool hoisted__Bool_3723 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3723;
    if (hoisted__Bool_3723) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U32 hoisted__U32_3724 = 1;
    (void)hoisted__U32_3724;
    Bool hoisted__Bool_3725 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3725;
    if (hoisted__Bool_3725) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U32 hoisted__U32_3726 = 1;
    (void)hoisted__U32_3726;
    Bool hoisted__Bool_3727 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3727;
    if (hoisted__Bool_3727) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U32 hoisted__U32_3728 = 1;
    (void)hoisted__U32_3728;
    Bool hoisted__Bool_3729 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3729;
    if (hoisted__Bool_3729) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3692 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3692;
        NodeType *hoisted__NodeType_3693 = NodeType_ForIn(hoisted__ForInData_3692);
        (void)hoisted__NodeType_3693;
        { NodeType * _ret_val = hoisted__NodeType_3693;
                return _ret_val; }
    }
    U32 hoisted__U32_3730 = 1;
    (void)hoisted__U32_3730;
    Bool hoisted__Bool_3731 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3731;
    if (hoisted__Bool_3731) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3694 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3694;
        NodeType *hoisted__NodeType_3695 = NodeType_NamedArg(hoisted__Str_3694);
        (void)hoisted__NodeType_3695;
        { NodeType * _ret_val = hoisted__NodeType_3695;
                return _ret_val; }
    }
    U32 hoisted__U32_3732 = 1;
    (void)hoisted__U32_3732;
    Bool hoisted__Bool_3733 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3733;
    if (hoisted__Bool_3733) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U32 hoisted__U32_3734 = 1;
    (void)hoisted__U32_3734;
    Bool hoisted__Bool_3735 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3735;
    if (hoisted__Bool_3735) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U32 hoisted__U32_3736 = 1;
    (void)hoisted__U32_3736;
    Bool hoisted__Bool_3737 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3737;
    if (hoisted__Bool_3737) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U32 hoisted__U32_3738 = 1;
    (void)hoisted__U32_3738;
    Bool hoisted__Bool_3739 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3739;
    if (hoisted__Bool_3739) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3696 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3696;
        NodeType *hoisted__NodeType_3697 = NodeType_Match(hoisted__MatchData_3696);
        (void)hoisted__NodeType_3697;
        { NodeType * _ret_val = hoisted__NodeType_3697;
                return _ret_val; }
    }
    U32 hoisted__U32_3740 = 1;
    (void)hoisted__U32_3740;
    Bool hoisted__Bool_3741 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3741;
    if (hoisted__Bool_3741) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U32 hoisted__U32_3742 = 1;
    (void)hoisted__U32_3742;
    Bool hoisted__Bool_3743 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3743;
    if (hoisted__Bool_3743) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U32 hoisted__U32_3744 = 1;
    (void)hoisted__U32_3744;
    Bool hoisted__Bool_3745 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3745;
    if (hoisted__Bool_3745) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U32 hoisted__U32_3746 = 1;
    (void)hoisted__U32_3746;
    Bool hoisted__Bool_3747 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3747;
    if (hoisted__Bool_3747) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U32 hoisted__U32_3748 = 1;
    (void)hoisted__U32_3748;
    Bool hoisted__Bool_3749 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3749;
    if (hoisted__Bool_3749) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U32 hoisted__U32_3750 = 1;
    (void)hoisted__U32_3750;
    Bool hoisted__Bool_3751 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3751;
    if (hoisted__Bool_3751) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3698 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3698;
        NodeType *hoisted__NodeType_3699 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3698);
        (void)hoisted__NodeType_3699;
        { NodeType * _ret_val = hoisted__NodeType_3699;
                return _ret_val; }
    }
    U32 hoisted__U32_3752 = 1;
    (void)hoisted__U32_3752;
    Bool hoisted__Bool_3753 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3753;
    if (hoisted__Bool_3753) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    CaptureBlockData *_clone_payload_BodyValue_27 = get_payload(self);
    (void)_clone_payload_BodyValue_27;
    (void)_clone_payload_BodyValue_27;
    CaptureBlockData *hoisted__CaptureBlockData_3754 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
    (void)hoisted__CaptureBlockData_3754;
    NodeType *hoisted__NodeType_3755 = NodeType_BodyValue(hoisted__CaptureBlockData_3754);
    (void)hoisted__NodeType_3755;
    return hoisted__NodeType_3755;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3756 = 136;
    (void)hoisted__U32_3756;
    return hoisted__U32_3756;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3757 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3757;
    if (hoisted__Bool_3757) {
        return;
    }
    Bool hoisted__Bool_3758 = 0;
    (void)hoisted__Bool_3758;
    NodeType_delete(&self->node_type, hoisted__Bool_3758);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3808 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3808->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3808->children = *_ca; free(_ca); }
    hoisted__Expr_3808->line = line;
    hoisted__Expr_3808->col = col;
    (void)hoisted__Expr_3808;
    return hoisted__Expr_3808;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3817 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3817->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3817->children = *_ca; free(_ca); }
    hoisted__Expr_3817->line = self->line;
    hoisted__Expr_3817->col = self->col;
    (void)hoisted__Expr_3817;
    return hoisted__Expr_3817;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3818 = 0;
    (void)hoisted__U32_3818;
    U64 hoisted__U64_3819 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3818); });
    (void)hoisted__U64_3819;
    return hoisted__U64_3819;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3820 = 160;
    (void)hoisted__U32_3820;
    return hoisted__U32_3820;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4906 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4906->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4906->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4906;
    return hoisted__Map__I64_Str_4906;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_5019 = 0;
    (void)hoisted__Bool_5019;
    Vec__I64_delete(&self->keys, hoisted__Bool_5019);
    Bool hoisted__Bool_5020 = 0;
    (void)hoisted__Bool_5020;
    Vec__Str_delete(&self->values, hoisted__Bool_5020);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_5021 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_5021->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_5021->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_5021;
    return hoisted__Map__I64_Str_5021;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_5022 = 0;
    (void)hoisted__U32_5022;
    U64 hoisted__U64_5023 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5022); });
    (void)hoisted__U64_5023;
    return hoisted__U64_5023;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_5024 = 32;
    (void)hoisted__U32_5024;
    return hoisted__U32_5024;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_5025 = 1;
    (void)hoisted__U32_5025;
    U64 hoisted__U64_5026 = (U64)(hoisted__U32_5025);
    (void)hoisted__U64_5026;
    void * hoisted__v_5027 = malloc(hoisted__U64_5026);
    (void)hoisted__v_5027;
    U32 hoisted__U32_5028 = 0;
    (void)hoisted__U32_5028;
    I64 hoisted__I64_5029 = 1;
    (void)hoisted__I64_5029;
    Vec__Bool *hoisted__Vec__Bool_5030 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5030->data = hoisted__v_5027;
    hoisted__Vec__Bool_5030->count = hoisted__U32_5028;
    hoisted__Vec__Bool_5030->cap = hoisted__I64_5029;
    (void)hoisted__Vec__Bool_5030;
    return hoisted__Vec__Bool_5030;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_5040 = self->count;
        (void)_re_U32_5040;
        U32 _rc_U32_5040 = 0;
        (void)_rc_U32_5040;
        Bool hoisted__Bool_5053 = ((Bool)(_rc_U32_5040 <= _re_U32_5040));
        (void)hoisted__Bool_5053;
        if (hoisted__Bool_5053) {
            while (1) {
                Bool _wcond_Bool_5041 = ((Bool)(_rc_U32_5040 < _re_U32_5040));
                (void)_wcond_Bool_5041;
                if (_wcond_Bool_5041) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5040);
                U32_inc(&_rc_U32_5040);
                U32 hoisted__U32_5042 = 1;
                (void)hoisted__U32_5042;
                U32 hoisted__U32_5043 = ((U32)(i * hoisted__U32_5042));
                (void)hoisted__U32_5043;
                U64 hoisted__U64_5044 = (U64)(hoisted__U32_5043);
                (void)hoisted__U64_5044;
                Bool *hoisted__Bool_5045 = ptr_add(self->data, hoisted__U64_5044);
                (void)hoisted__Bool_5045;
                (void)hoisted__Bool_5045;
                Bool hoisted__Bool_5046 = 0;
                (void)hoisted__Bool_5046;
                Bool_delete(hoisted__Bool_5045, hoisted__Bool_5046);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5047 = ((Bool)(_rc_U32_5040 > _re_U32_5040));
                (void)_wcond_Bool_5047;
                if (_wcond_Bool_5047) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5040);
                U32_dec(&_rc_U32_5040);
                U32 hoisted__U32_5048 = 1;
                (void)hoisted__U32_5048;
                U32 hoisted__U32_5049 = ((U32)(i * hoisted__U32_5048));
                (void)hoisted__U32_5049;
                U64 hoisted__U64_5050 = (U64)(hoisted__U32_5049);
                (void)hoisted__U64_5050;
                Bool *hoisted__Bool_5051 = ptr_add(self->data, hoisted__U64_5050);
                (void)hoisted__Bool_5051;
                (void)hoisted__Bool_5051;
                Bool hoisted__Bool_5052 = 0;
                (void)hoisted__Bool_5052;
                Bool_delete(hoisted__Bool_5051, hoisted__Bool_5052);
            }
        }
    }
    U32 hoisted__U32_5054 = 0;
    (void)hoisted__U32_5054;
    self->count = hoisted__U32_5054;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_5324 = 1;
    (void)hoisted__U32_5324;
    U32 hoisted__U32_5325 = ((U32)(self->cap * hoisted__U32_5324));
    (void)hoisted__U32_5325;
    U64 hoisted__U64_5326 = (U64)(hoisted__U32_5325);
    (void)hoisted__U64_5326;
    void * new_data = malloc(hoisted__U64_5326);
    {
        U32 _re_U32_5296 = self->count;
        (void)_re_U32_5296;
        U32 _rc_U32_5296 = 0;
        (void)_rc_U32_5296;
        Bool hoisted__Bool_5323 = ((Bool)(_rc_U32_5296 <= _re_U32_5296));
        (void)hoisted__Bool_5323;
        if (hoisted__Bool_5323) {
            while (1) {
                Bool _wcond_Bool_5297 = ((Bool)(_rc_U32_5296 < _re_U32_5296));
                (void)_wcond_Bool_5297;
                if (_wcond_Bool_5297) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5296);
                U32_inc(&_rc_U32_5296);
                U32 hoisted__U32_5298 = 1;
                (void)hoisted__U32_5298;
                U32 hoisted__U32_5299 = ((U32)(i * hoisted__U32_5298));
                (void)hoisted__U32_5299;
                U64 hoisted__U64_5300 = (U64)(hoisted__U32_5299);
                (void)hoisted__U64_5300;
                Bool *src = ptr_add(self->data, hoisted__U64_5300);
                Bool cloned = (DEREF(src));
                U32 hoisted__U32_5301 = 1;
                (void)hoisted__U32_5301;
                U32 hoisted__U32_5302 = ((U32)(i * hoisted__U32_5301));
                (void)hoisted__U32_5302;
                U64 hoisted__U64_5303 = (U64)(hoisted__U32_5302);
                (void)hoisted__U64_5303;
                U32 hoisted__U32_5304 = 1;
                (void)hoisted__U32_5304;
                void *hoisted__v_5305 = ptr_add(new_data, hoisted__U64_5303);
                (void)hoisted__v_5305;
                (void)hoisted__v_5305;
                U64 hoisted__U64_5306 = (U64)(hoisted__U32_5304);
                (void)hoisted__U64_5306;
                memcpy(hoisted__v_5305, &cloned, hoisted__U64_5306);
                U32 hoisted__U32_5307 = 1;
                (void)hoisted__U32_5307;
                I32 hoisted__I32_5308 = 0;
                (void)hoisted__I32_5308;
                U64 hoisted__U64_5309 = (U64)(hoisted__U32_5307);
                (void)hoisted__U64_5309;
                memset(&cloned, hoisted__I32_5308, hoisted__U64_5309);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5310 = ((Bool)(_rc_U32_5296 > _re_U32_5296));
                (void)_wcond_Bool_5310;
                if (_wcond_Bool_5310) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5296);
                U32_dec(&_rc_U32_5296);
                U32 hoisted__U32_5311 = 1;
                (void)hoisted__U32_5311;
                U32 hoisted__U32_5312 = ((U32)(i * hoisted__U32_5311));
                (void)hoisted__U32_5312;
                U64 hoisted__U64_5313 = (U64)(hoisted__U32_5312);
                (void)hoisted__U64_5313;
                Bool *src = ptr_add(self->data, hoisted__U64_5313);
                Bool cloned = (DEREF(src));
                U32 hoisted__U32_5314 = 1;
                (void)hoisted__U32_5314;
                U32 hoisted__U32_5315 = ((U32)(i * hoisted__U32_5314));
                (void)hoisted__U32_5315;
                U64 hoisted__U64_5316 = (U64)(hoisted__U32_5315);
                (void)hoisted__U64_5316;
                U32 hoisted__U32_5317 = 1;
                (void)hoisted__U32_5317;
                void *hoisted__v_5318 = ptr_add(new_data, hoisted__U64_5316);
                (void)hoisted__v_5318;
                (void)hoisted__v_5318;
                U64 hoisted__U64_5319 = (U64)(hoisted__U32_5317);
                (void)hoisted__U64_5319;
                memcpy(hoisted__v_5318, &cloned, hoisted__U64_5319);
                U32 hoisted__U32_5320 = 1;
                (void)hoisted__U32_5320;
                I32 hoisted__I32_5321 = 0;
                (void)hoisted__I32_5321;
                U64 hoisted__U64_5322 = (U64)(hoisted__U32_5320);
                (void)hoisted__U64_5322;
                memset(&cloned, hoisted__I32_5321, hoisted__U64_5322);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5327 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5327->data = new_data;
    hoisted__Vec__Bool_5327->count = self->count;
    hoisted__Vec__Bool_5327->cap = self->cap;
    (void)hoisted__Vec__Bool_5327;
    return hoisted__Vec__Bool_5327;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_5328 = 16;
    (void)hoisted__U32_5328;
    return hoisted__U32_5328;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5329 = 8;
    (void)hoisted__U32_5329;
    U64 hoisted__U64_5330 = (U64)(hoisted__U32_5329);
    (void)hoisted__U64_5330;
    void * hoisted__v_5331 = malloc(hoisted__U64_5330);
    (void)hoisted__v_5331;
    U32 hoisted__U32_5332 = 0;
    (void)hoisted__U32_5332;
    I64 hoisted__I64_5333 = 1;
    (void)hoisted__I64_5333;
    Vec__I64 *hoisted__Vec__I64_5334 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5334->data = hoisted__v_5331;
    hoisted__Vec__I64_5334->count = hoisted__U32_5332;
    hoisted__Vec__I64_5334->cap = hoisted__I64_5333;
    (void)hoisted__Vec__I64_5334;
    return hoisted__Vec__I64_5334;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5344 = self->count;
        (void)_re_U32_5344;
        U32 _rc_U32_5344 = 0;
        (void)_rc_U32_5344;
        Bool hoisted__Bool_5357 = ((Bool)(_rc_U32_5344 <= _re_U32_5344));
        (void)hoisted__Bool_5357;
        if (hoisted__Bool_5357) {
            while (1) {
                Bool _wcond_Bool_5345 = ((Bool)(_rc_U32_5344 < _re_U32_5344));
                (void)_wcond_Bool_5345;
                if (_wcond_Bool_5345) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5344);
                U32_inc(&_rc_U32_5344);
                U32 hoisted__U32_5346 = 8;
                (void)hoisted__U32_5346;
                U32 hoisted__U32_5347 = ((U32)(i * hoisted__U32_5346));
                (void)hoisted__U32_5347;
                U64 hoisted__U64_5348 = (U64)(hoisted__U32_5347);
                (void)hoisted__U64_5348;
                I64 *hoisted__I64_5349 = ptr_add(self->data, hoisted__U64_5348);
                (void)hoisted__I64_5349;
                (void)hoisted__I64_5349;
                Bool hoisted__Bool_5350 = 0;
                (void)hoisted__Bool_5350;
                I64_delete(hoisted__I64_5349, hoisted__Bool_5350);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5351 = ((Bool)(_rc_U32_5344 > _re_U32_5344));
                (void)_wcond_Bool_5351;
                if (_wcond_Bool_5351) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5344);
                U32_dec(&_rc_U32_5344);
                U32 hoisted__U32_5352 = 8;
                (void)hoisted__U32_5352;
                U32 hoisted__U32_5353 = ((U32)(i * hoisted__U32_5352));
                (void)hoisted__U32_5353;
                U64 hoisted__U64_5354 = (U64)(hoisted__U32_5353);
                (void)hoisted__U64_5354;
                I64 *hoisted__I64_5355 = ptr_add(self->data, hoisted__U64_5354);
                (void)hoisted__I64_5355;
                (void)hoisted__I64_5355;
                Bool hoisted__Bool_5356 = 0;
                (void)hoisted__Bool_5356;
                I64_delete(hoisted__I64_5355, hoisted__Bool_5356);
            }
        }
    }
    U32 hoisted__U32_5358 = 0;
    (void)hoisted__U32_5358;
    self->count = hoisted__U32_5358;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5628 = 8;
    (void)hoisted__U32_5628;
    U32 hoisted__U32_5629 = ((U32)(self->cap * hoisted__U32_5628));
    (void)hoisted__U32_5629;
    U64 hoisted__U64_5630 = (U64)(hoisted__U32_5629);
    (void)hoisted__U64_5630;
    void * new_data = malloc(hoisted__U64_5630);
    {
        U32 _re_U32_5600 = self->count;
        (void)_re_U32_5600;
        U32 _rc_U32_5600 = 0;
        (void)_rc_U32_5600;
        Bool hoisted__Bool_5627 = ((Bool)(_rc_U32_5600 <= _re_U32_5600));
        (void)hoisted__Bool_5627;
        if (hoisted__Bool_5627) {
            while (1) {
                Bool _wcond_Bool_5601 = ((Bool)(_rc_U32_5600 < _re_U32_5600));
                (void)_wcond_Bool_5601;
                if (_wcond_Bool_5601) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5600);
                U32_inc(&_rc_U32_5600);
                U32 hoisted__U32_5602 = 8;
                (void)hoisted__U32_5602;
                U32 hoisted__U32_5603 = ((U32)(i * hoisted__U32_5602));
                (void)hoisted__U32_5603;
                U64 hoisted__U64_5604 = (U64)(hoisted__U32_5603);
                (void)hoisted__U64_5604;
                I64 *src = ptr_add(self->data, hoisted__U64_5604);
                I64 cloned = (DEREF(src));
                U32 hoisted__U32_5605 = 8;
                (void)hoisted__U32_5605;
                U32 hoisted__U32_5606 = ((U32)(i * hoisted__U32_5605));
                (void)hoisted__U32_5606;
                U64 hoisted__U64_5607 = (U64)(hoisted__U32_5606);
                (void)hoisted__U64_5607;
                U32 hoisted__U32_5608 = 8;
                (void)hoisted__U32_5608;
                void *hoisted__v_5609 = ptr_add(new_data, hoisted__U64_5607);
                (void)hoisted__v_5609;
                (void)hoisted__v_5609;
                U64 hoisted__U64_5610 = (U64)(hoisted__U32_5608);
                (void)hoisted__U64_5610;
                memcpy(hoisted__v_5609, &cloned, hoisted__U64_5610);
                U32 hoisted__U32_5611 = 8;
                (void)hoisted__U32_5611;
                I32 hoisted__I32_5612 = 0;
                (void)hoisted__I32_5612;
                U64 hoisted__U64_5613 = (U64)(hoisted__U32_5611);
                (void)hoisted__U64_5613;
                memset(&cloned, hoisted__I32_5612, hoisted__U64_5613);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5614 = ((Bool)(_rc_U32_5600 > _re_U32_5600));
                (void)_wcond_Bool_5614;
                if (_wcond_Bool_5614) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5600);
                U32_dec(&_rc_U32_5600);
                U32 hoisted__U32_5615 = 8;
                (void)hoisted__U32_5615;
                U32 hoisted__U32_5616 = ((U32)(i * hoisted__U32_5615));
                (void)hoisted__U32_5616;
                U64 hoisted__U64_5617 = (U64)(hoisted__U32_5616);
                (void)hoisted__U64_5617;
                I64 *src = ptr_add(self->data, hoisted__U64_5617);
                I64 cloned = (DEREF(src));
                U32 hoisted__U32_5618 = 8;
                (void)hoisted__U32_5618;
                U32 hoisted__U32_5619 = ((U32)(i * hoisted__U32_5618));
                (void)hoisted__U32_5619;
                U64 hoisted__U64_5620 = (U64)(hoisted__U32_5619);
                (void)hoisted__U64_5620;
                U32 hoisted__U32_5621 = 8;
                (void)hoisted__U32_5621;
                void *hoisted__v_5622 = ptr_add(new_data, hoisted__U64_5620);
                (void)hoisted__v_5622;
                (void)hoisted__v_5622;
                U64 hoisted__U64_5623 = (U64)(hoisted__U32_5621);
                (void)hoisted__U64_5623;
                memcpy(hoisted__v_5622, &cloned, hoisted__U64_5623);
                U32 hoisted__U32_5624 = 8;
                (void)hoisted__U32_5624;
                I32 hoisted__I32_5625 = 0;
                (void)hoisted__I32_5625;
                U64 hoisted__U64_5626 = (U64)(hoisted__U32_5624);
                (void)hoisted__U64_5626;
                memset(&cloned, hoisted__I32_5625, hoisted__U64_5626);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5631 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5631->data = new_data;
    hoisted__Vec__I64_5631->count = self->count;
    hoisted__Vec__I64_5631->cap = self->cap;
    (void)hoisted__Vec__I64_5631;
    return hoisted__Vec__I64_5631;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5632 = 16;
    (void)hoisted__U32_5632;
    return hoisted__U32_5632;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5937 = 104;
    (void)hoisted__U32_5937;
    U64 hoisted__U64_5938 = (U64)(hoisted__U32_5937);
    (void)hoisted__U64_5938;
    void * hoisted__v_5939 = malloc(hoisted__U64_5938);
    (void)hoisted__v_5939;
    U32 hoisted__U32_5940 = 0;
    (void)hoisted__U32_5940;
    I64 hoisted__I64_5941 = 1;
    (void)hoisted__I64_5941;
    Vec__Declaration *hoisted__Vec__Declaration_5942 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5942->data = hoisted__v_5939;
    hoisted__Vec__Declaration_5942->count = hoisted__U32_5940;
    hoisted__Vec__Declaration_5942->cap = hoisted__I64_5941;
    (void)hoisted__Vec__Declaration_5942;
    return hoisted__Vec__Declaration_5942;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5952 = self->count;
        (void)_re_U32_5952;
        U32 _rc_U32_5952 = 0;
        (void)_rc_U32_5952;
        Bool hoisted__Bool_5965 = ((Bool)(_rc_U32_5952 <= _re_U32_5952));
        (void)hoisted__Bool_5965;
        if (hoisted__Bool_5965) {
            while (1) {
                Bool _wcond_Bool_5953 = ((Bool)(_rc_U32_5952 < _re_U32_5952));
                (void)_wcond_Bool_5953;
                if (_wcond_Bool_5953) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5952);
                U32_inc(&_rc_U32_5952);
                U32 hoisted__U32_5954 = 104;
                (void)hoisted__U32_5954;
                U32 hoisted__U32_5955 = ((U32)(i * hoisted__U32_5954));
                (void)hoisted__U32_5955;
                U64 hoisted__U64_5956 = (U64)(hoisted__U32_5955);
                (void)hoisted__U64_5956;
                Declaration *hoisted__Declaration_5957 = ptr_add(self->data, hoisted__U64_5956);
                (void)hoisted__Declaration_5957;
                (void)hoisted__Declaration_5957;
                Bool hoisted__Bool_5958 = 0;
                (void)hoisted__Bool_5958;
                Declaration_delete(hoisted__Declaration_5957, hoisted__Bool_5958);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5959 = ((Bool)(_rc_U32_5952 > _re_U32_5952));
                (void)_wcond_Bool_5959;
                if (_wcond_Bool_5959) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5952);
                U32_dec(&_rc_U32_5952);
                U32 hoisted__U32_5960 = 104;
                (void)hoisted__U32_5960;
                U32 hoisted__U32_5961 = ((U32)(i * hoisted__U32_5960));
                (void)hoisted__U32_5961;
                U64 hoisted__U64_5962 = (U64)(hoisted__U32_5961);
                (void)hoisted__U64_5962;
                Declaration *hoisted__Declaration_5963 = ptr_add(self->data, hoisted__U64_5962);
                (void)hoisted__Declaration_5963;
                (void)hoisted__Declaration_5963;
                Bool hoisted__Bool_5964 = 0;
                (void)hoisted__Bool_5964;
                Declaration_delete(hoisted__Declaration_5963, hoisted__Bool_5964);
            }
        }
    }
    U32 hoisted__U32_5966 = 0;
    (void)hoisted__U32_5966;
    self->count = hoisted__U32_5966;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_6236 = 104;
    (void)hoisted__U32_6236;
    U32 hoisted__U32_6237 = ((U32)(self->cap * hoisted__U32_6236));
    (void)hoisted__U32_6237;
    U64 hoisted__U64_6238 = (U64)(hoisted__U32_6237);
    (void)hoisted__U64_6238;
    void * new_data = malloc(hoisted__U64_6238);
    {
        U32 _re_U32_6208 = self->count;
        (void)_re_U32_6208;
        U32 _rc_U32_6208 = 0;
        (void)_rc_U32_6208;
        Bool hoisted__Bool_6235 = ((Bool)(_rc_U32_6208 <= _re_U32_6208));
        (void)hoisted__Bool_6235;
        if (hoisted__Bool_6235) {
            while (1) {
                Bool _wcond_Bool_6209 = ((Bool)(_rc_U32_6208 < _re_U32_6208));
                (void)_wcond_Bool_6209;
                if (_wcond_Bool_6209) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_6208);
                U32_inc(&_rc_U32_6208);
                U32 hoisted__U32_6210 = 104;
                (void)hoisted__U32_6210;
                U32 hoisted__U32_6211 = ((U32)(i * hoisted__U32_6210));
                (void)hoisted__U32_6211;
                U64 hoisted__U64_6212 = (U64)(hoisted__U32_6211);
                (void)hoisted__U64_6212;
                Declaration *src = ptr_add(self->data, hoisted__U64_6212);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6213 = 104;
                (void)hoisted__U32_6213;
                U32 hoisted__U32_6214 = ((U32)(i * hoisted__U32_6213));
                (void)hoisted__U32_6214;
                U64 hoisted__U64_6215 = (U64)(hoisted__U32_6214);
                (void)hoisted__U64_6215;
                U32 hoisted__U32_6216 = 104;
                (void)hoisted__U32_6216;
                void *hoisted__v_6217 = ptr_add(new_data, hoisted__U64_6215);
                (void)hoisted__v_6217;
                (void)hoisted__v_6217;
                U64 hoisted__U64_6218 = (U64)(hoisted__U32_6216);
                (void)hoisted__U64_6218;
                memcpy(hoisted__v_6217, cloned, hoisted__U64_6218);
                U32 hoisted__U32_6219 = 104;
                (void)hoisted__U32_6219;
                I32 hoisted__I32_6220 = 0;
                (void)hoisted__I32_6220;
                U64 hoisted__U64_6221 = (U64)(hoisted__U32_6219);
                (void)hoisted__U64_6221;
                memset(cloned, hoisted__I32_6220, hoisted__U64_6221);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6222 = ((Bool)(_rc_U32_6208 > _re_U32_6208));
                (void)_wcond_Bool_6222;
                if (_wcond_Bool_6222) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_6208);
                U32_dec(&_rc_U32_6208);
                U32 hoisted__U32_6223 = 104;
                (void)hoisted__U32_6223;
                U32 hoisted__U32_6224 = ((U32)(i * hoisted__U32_6223));
                (void)hoisted__U32_6224;
                U64 hoisted__U64_6225 = (U64)(hoisted__U32_6224);
                (void)hoisted__U64_6225;
                Declaration *src = ptr_add(self->data, hoisted__U64_6225);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6226 = 104;
                (void)hoisted__U32_6226;
                U32 hoisted__U32_6227 = ((U32)(i * hoisted__U32_6226));
                (void)hoisted__U32_6227;
                U64 hoisted__U64_6228 = (U64)(hoisted__U32_6227);
                (void)hoisted__U64_6228;
                U32 hoisted__U32_6229 = 104;
                (void)hoisted__U32_6229;
                void *hoisted__v_6230 = ptr_add(new_data, hoisted__U64_6228);
                (void)hoisted__v_6230;
                (void)hoisted__v_6230;
                U64 hoisted__U64_6231 = (U64)(hoisted__U32_6229);
                (void)hoisted__U64_6231;
                memcpy(hoisted__v_6230, cloned, hoisted__U64_6231);
                U32 hoisted__U32_6232 = 104;
                (void)hoisted__U32_6232;
                I32 hoisted__I32_6233 = 0;
                (void)hoisted__I32_6233;
                U64 hoisted__U64_6234 = (U64)(hoisted__U32_6232);
                (void)hoisted__U64_6234;
                memset(cloned, hoisted__I32_6233, hoisted__U64_6234);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_6239 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6239->data = new_data;
    hoisted__Vec__Declaration_6239->count = self->count;
    hoisted__Vec__Declaration_6239->cap = self->cap;
    (void)hoisted__Vec__Declaration_6239;
    return hoisted__Vec__Declaration_6239;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_6240 = 16;
    (void)hoisted__U32_6240;
    return hoisted__U32_6240;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_6241 = 160;
    (void)hoisted__U32_6241;
    U64 hoisted__U64_6242 = (U64)(hoisted__U32_6241);
    (void)hoisted__U64_6242;
    void * hoisted__v_6243 = malloc(hoisted__U64_6242);
    (void)hoisted__v_6243;
    U32 hoisted__U32_6244 = 0;
    (void)hoisted__U32_6244;
    I64 hoisted__I64_6245 = 1;
    (void)hoisted__I64_6245;
    Vec__Expr *hoisted__Vec__Expr_6246 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6246->data = hoisted__v_6243;
    hoisted__Vec__Expr_6246->count = hoisted__U32_6244;
    hoisted__Vec__Expr_6246->cap = hoisted__I64_6245;
    (void)hoisted__Vec__Expr_6246;
    return hoisted__Vec__Expr_6246;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_6256 = self->count;
        (void)_re_U32_6256;
        U32 _rc_U32_6256 = 0;
        (void)_rc_U32_6256;
        Bool hoisted__Bool_6269 = ((Bool)(_rc_U32_6256 <= _re_U32_6256));
        (void)hoisted__Bool_6269;
        if (hoisted__Bool_6269) {
            while (1) {
                Bool _wcond_Bool_6257 = ((Bool)(_rc_U32_6256 < _re_U32_6256));
                (void)_wcond_Bool_6257;
                if (_wcond_Bool_6257) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_6256);
                U32_inc(&_rc_U32_6256);
                U32 hoisted__U32_6258 = 160;
                (void)hoisted__U32_6258;
                U32 hoisted__U32_6259 = ((U32)(i * hoisted__U32_6258));
                (void)hoisted__U32_6259;
                U64 hoisted__U64_6260 = (U64)(hoisted__U32_6259);
                (void)hoisted__U64_6260;
                Expr *hoisted__Expr_6261 = ptr_add(self->data, hoisted__U64_6260);
                (void)hoisted__Expr_6261;
                (void)hoisted__Expr_6261;
                Bool hoisted__Bool_6262 = 0;
                (void)hoisted__Bool_6262;
                Expr_delete(hoisted__Expr_6261, hoisted__Bool_6262);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6263 = ((Bool)(_rc_U32_6256 > _re_U32_6256));
                (void)_wcond_Bool_6263;
                if (_wcond_Bool_6263) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_6256);
                U32_dec(&_rc_U32_6256);
                U32 hoisted__U32_6264 = 160;
                (void)hoisted__U32_6264;
                U32 hoisted__U32_6265 = ((U32)(i * hoisted__U32_6264));
                (void)hoisted__U32_6265;
                U64 hoisted__U64_6266 = (U64)(hoisted__U32_6265);
                (void)hoisted__U64_6266;
                Expr *hoisted__Expr_6267 = ptr_add(self->data, hoisted__U64_6266);
                (void)hoisted__Expr_6267;
                (void)hoisted__Expr_6267;
                Bool hoisted__Bool_6268 = 0;
                (void)hoisted__Bool_6268;
                Expr_delete(hoisted__Expr_6267, hoisted__Bool_6268);
            }
        }
    }
    U32 hoisted__U32_6270 = 0;
    (void)hoisted__U32_6270;
    self->count = hoisted__U32_6270;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_6540 = 160;
    (void)hoisted__U32_6540;
    U32 hoisted__U32_6541 = ((U32)(self->cap * hoisted__U32_6540));
    (void)hoisted__U32_6541;
    U64 hoisted__U64_6542 = (U64)(hoisted__U32_6541);
    (void)hoisted__U64_6542;
    void * new_data = malloc(hoisted__U64_6542);
    {
        U32 _re_U32_6512 = self->count;
        (void)_re_U32_6512;
        U32 _rc_U32_6512 = 0;
        (void)_rc_U32_6512;
        Bool hoisted__Bool_6539 = ((Bool)(_rc_U32_6512 <= _re_U32_6512));
        (void)hoisted__Bool_6539;
        if (hoisted__Bool_6539) {
            while (1) {
                Bool _wcond_Bool_6513 = ((Bool)(_rc_U32_6512 < _re_U32_6512));
                (void)_wcond_Bool_6513;
                if (_wcond_Bool_6513) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_6512);
                U32_inc(&_rc_U32_6512);
                U32 hoisted__U32_6514 = 160;
                (void)hoisted__U32_6514;
                U32 hoisted__U32_6515 = ((U32)(i * hoisted__U32_6514));
                (void)hoisted__U32_6515;
                U64 hoisted__U64_6516 = (U64)(hoisted__U32_6515);
                (void)hoisted__U64_6516;
                Expr *src = ptr_add(self->data, hoisted__U64_6516);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6517 = 160;
                (void)hoisted__U32_6517;
                U32 hoisted__U32_6518 = ((U32)(i * hoisted__U32_6517));
                (void)hoisted__U32_6518;
                U64 hoisted__U64_6519 = (U64)(hoisted__U32_6518);
                (void)hoisted__U64_6519;
                U32 hoisted__U32_6520 = 160;
                (void)hoisted__U32_6520;
                void *hoisted__v_6521 = ptr_add(new_data, hoisted__U64_6519);
                (void)hoisted__v_6521;
                (void)hoisted__v_6521;
                U64 hoisted__U64_6522 = (U64)(hoisted__U32_6520);
                (void)hoisted__U64_6522;
                memcpy(hoisted__v_6521, cloned, hoisted__U64_6522);
                U32 hoisted__U32_6523 = 160;
                (void)hoisted__U32_6523;
                I32 hoisted__I32_6524 = 0;
                (void)hoisted__I32_6524;
                U64 hoisted__U64_6525 = (U64)(hoisted__U32_6523);
                (void)hoisted__U64_6525;
                memset(cloned, hoisted__I32_6524, hoisted__U64_6525);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6526 = ((Bool)(_rc_U32_6512 > _re_U32_6512));
                (void)_wcond_Bool_6526;
                if (_wcond_Bool_6526) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_6512);
                U32_dec(&_rc_U32_6512);
                U32 hoisted__U32_6527 = 160;
                (void)hoisted__U32_6527;
                U32 hoisted__U32_6528 = ((U32)(i * hoisted__U32_6527));
                (void)hoisted__U32_6528;
                U64 hoisted__U64_6529 = (U64)(hoisted__U32_6528);
                (void)hoisted__U64_6529;
                Expr *src = ptr_add(self->data, hoisted__U64_6529);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6530 = 160;
                (void)hoisted__U32_6530;
                U32 hoisted__U32_6531 = ((U32)(i * hoisted__U32_6530));
                (void)hoisted__U32_6531;
                U64 hoisted__U64_6532 = (U64)(hoisted__U32_6531);
                (void)hoisted__U64_6532;
                U32 hoisted__U32_6533 = 160;
                (void)hoisted__U32_6533;
                void *hoisted__v_6534 = ptr_add(new_data, hoisted__U64_6532);
                (void)hoisted__v_6534;
                (void)hoisted__v_6534;
                U64 hoisted__U64_6535 = (U64)(hoisted__U32_6533);
                (void)hoisted__U64_6535;
                memcpy(hoisted__v_6534, cloned, hoisted__U64_6535);
                U32 hoisted__U32_6536 = 160;
                (void)hoisted__U32_6536;
                I32 hoisted__I32_6537 = 0;
                (void)hoisted__I32_6537;
                U64 hoisted__U64_6538 = (U64)(hoisted__U32_6536);
                (void)hoisted__U64_6538;
                memset(cloned, hoisted__I32_6537, hoisted__U64_6538);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6543 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6543->data = new_data;
    hoisted__Vec__Expr_6543->count = self->count;
    hoisted__Vec__Expr_6543->cap = self->cap;
    (void)hoisted__Vec__Expr_6543;
    return hoisted__Vec__Expr_6543;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_6544 = 16;
    (void)hoisted__U32_6544;
    return hoisted__U32_6544;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7632 = 3;
    (void)hoisted__U32_7632;
    Array__Str *_va_Array_208 = Array__Str_new(hoisted__U32_7632);
    (void)_va_Array_208;
    I64 _va_Array_208_ek = 0;
    (void)_va_Array_208_ek;
    OutOfBounds *_va_Array_208_eo = malloc(sizeof(OutOfBounds));
    _va_Array_208_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_208_eo;
    U32 hoisted__U32_7633 = 0;
    (void)hoisted__U32_7633;
    Str *hoisted__Str_7634 = Str_clone(loc);
    (void)hoisted__Str_7634;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_208, hoisted__U32_7633, hoisted__Str_7634, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_144);
    Str_delete(&_til_str_lit_144, (Bool){0});
    U32 hoisted__U32_7636 = 1;
    (void)hoisted__U32_7636;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_208, hoisted__U32_7636, &_til_str_lit_145, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_144);
    Str_delete(&_til_str_lit_144, (Bool){0});
    Array__Str *hoisted__Array__Str_7639 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7639;
    U32 hoisted__U32_7640 = 2;
    (void)hoisted__U32_7640;
    Str *hoisted__Str_7641 = format(hoisted__Array__Str_7639);
    (void)hoisted__Str_7641;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_208, hoisted__U32_7640, hoisted__Str_7641, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_144);
    OutOfBounds_delete(_va_Array_208_eo, 1);
    Str_delete(&_til_str_lit_144, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_208);
    I64 hoisted__I64_7643 = 1;
    (void)hoisted__I64_7643;
    exit(hoisted__I64_7643);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7652 = 1;
    (void)hoisted__U32_7652;
    Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7652);
    (void)_va_Array_210;
    I64 _va_Array_210_ek = 0;
    (void)_va_Array_210_ek;
    OutOfBounds *_va_Array_210_eo = malloc(sizeof(OutOfBounds));
    _va_Array_210_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_210_eo;
    U32 hoisted__U32_7653 = 0;
    (void)hoisted__U32_7653;
    (void)_til_str_lit_146;
    (void)_til_str_lit_146;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    Array__Str_set(_va_Array_210, hoisted__U32_7653, &_til_str_lit_146, &_va_Array_210_ek, _va_Array_210_eo, &_til_str_lit_147);
    OutOfBounds_delete(_va_Array_210_eo, 1);
    Str_delete(&_til_str_lit_147, (Bool){0});
    panic(_va_Array_210, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7660 = ((Bool)(!(cond)));
    (void)hoisted__Bool_7660;
    if (hoisted__Bool_7660) {
        U32 hoisted__U32_7656 = 1;
        (void)hoisted__U32_7656;
        Array__Str *_va_Array_211 = Array__Str_new(hoisted__U32_7656);
        (void)_va_Array_211;
        I64 _va_Array_211_ek = 0;
        (void)_va_Array_211_ek;
        OutOfBounds *_va_Array_211_eo = malloc(sizeof(OutOfBounds));
        _va_Array_211_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_211_eo;
        U32 hoisted__U32_7657 = 0;
        (void)hoisted__U32_7657;
        (void)_til_str_lit_148;
        (void)_til_str_lit_148;
        (void)_til_str_lit_149;
        (void)_til_str_lit_149;
        Array__Str_set(_va_Array_211, hoisted__U32_7657, &_til_str_lit_148, &_va_Array_211_ek, _va_Array_211_eo, &_til_str_lit_149);
        OutOfBounds_delete(_va_Array_211_eo, 1);
        Str_delete(&_til_str_lit_149, (Bool){0});
        panic(_va_Array_211, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7670 = parts;
        (void)_fc_Array__Str_7670;
        (void)_fc_Array__Str_7670;
        U32 _fi_USize_7670 = 0;
        (void)_fi_USize_7670;
        while (1) {
            U32 hoisted__U32_7672 = Array__Str_len(_fc_Array__Str_7670);
            (void)hoisted__U32_7672;
            Bool _wcond_Bool_7671 = ((Bool)(_fi_USize_7670 < hoisted__U32_7672));
            (void)_wcond_Bool_7671;
            if (_wcond_Bool_7671) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7670, &_fi_USize_7670);
            U32 hoisted__U32_7673 = 1;
            (void)hoisted__U32_7673;
            U32 hoisted__U32_7674 = ((U32)(_fi_USize_7670 + hoisted__U32_7673));
            (void)hoisted__U32_7674;
            _fi_USize_7670 = hoisted__U32_7674;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7714 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7714;
    return hoisted__Bool_7714;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7723 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7723;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7723;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7724 = 0;
    (void)hoisted__U32_7724;
    U64 hoisted__U64_7725 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7724); });
    (void)hoisted__U64_7725;
    return hoisted__U64_7725;
}

U32 Range_size(void) {
    U32 hoisted__U32_7756 = 16;
    (void)hoisted__U32_7756;
    return hoisted__U32_7756;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7772 = 3;
    (void)hoisted__I64_7772;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    assert_eq__I64(result, hoisted__I64_7772, &_til_str_lit_152);
    Str_delete(&_til_str_lit_152, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7780 = 15;
    (void)hoisted__I64_7780;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    assert_eq__I64(result, hoisted__I64_7780, &_til_str_lit_153);
    Str_delete(&_til_str_lit_153, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7788 = 26;
    (void)hoisted__I64_7788;
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    assert_eq__I64(result, hoisted__I64_7788, &_til_str_lit_154);
    Str_delete(&_til_str_lit_154, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    assert_eq__Str(&result, &_til_str_lit_155, &_til_str_lit_156);
    Str_delete(&_til_str_lit_155, (Bool){0});
    Str_delete(&_til_str_lit_156, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    (void)_til_str_lit_157;
    (void)_til_str_lit_157;
    assert_eq__Str(&r, &_til_str_lit_155, &_til_str_lit_157);
    Str_delete(&_til_str_lit_155, (Bool){0});
    Str_delete(&_til_str_lit_157, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    assert_eq__Str(&r2, &_til_str_lit_158, &_til_str_lit_159);
    Str_delete(&_til_str_lit_158, (Bool){0});
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    assert_eq__Str(&d, &_til_str_lit_160, &_til_str_lit_161);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_160, (Bool){0});
    Str_delete(&_til_str_lit_161, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    assert_eq__Str(&d2, &_til_str_lit_162, &_til_str_lit_163);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_162, (Bool){0});
    Str_delete(&_til_str_lit_163, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7875 = 106;
    (void)hoisted__I64_7875;
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    assert_eq__I64(d3, hoisted__I64_7875, &_til_str_lit_164);
    Str_delete(&_til_str_lit_164, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_167;
    (void)_til_str_lit_167;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_167);
    Str_delete(&_til_str_lit_167, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_168;
    (void)_til_str_lit_168;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_168);
    Str_delete(&_til_str_lit_168, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8478 = 8;
    (void)hoisted__I64_8478;
    (void)_til_str_lit_169;
    (void)_til_str_lit_169;
    assert_eq__I64(result, hoisted__I64_8478, &_til_str_lit_169);
    Str_delete(&_til_str_lit_169, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8482 = 1;
    (void)hoisted__Bool_8482;
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert(hoisted__Bool_8482, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
    Bool hoisted__Bool_8486 = 1;
    (void)hoisted__Bool_8486;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert(hoisted__Bool_8486, &_til_str_lit_171);
    Str_delete(&_til_str_lit_171, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    assert_eq__Str(&_til_str_lit_172, &_til_str_lit_172, &_til_str_lit_173);
    Str_delete(&_til_str_lit_172, (Bool){0});
    Str_delete(&_til_str_lit_172, (Bool){0});
    Str_delete(&_til_str_lit_173, (Bool){0});
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    assert_eq__Str(&_til_str_lit_174, &_til_str_lit_174, &_til_str_lit_175);
    Str_delete(&_til_str_lit_174, (Bool){0});
    Str_delete(&_til_str_lit_174, (Bool){0});
    Str_delete(&_til_str_lit_175, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8504 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8504;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8504;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8505 = 0;
    (void)hoisted__U32_8505;
    U64 hoisted__U64_8506 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8505); });
    (void)hoisted__U64_8506;
    return hoisted__U64_8506;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8537 = 16;
    (void)hoisted__U32_8537;
    return hoisted__U32_8537;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8538 = 42;
    (void)hoisted__I64_8538;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    assert_eq__I64(v.x, hoisted__I64_8538, &_til_str_lit_178);
    Str_delete(&_til_str_lit_178, (Bool){0});
    I64 hoisted__I64_8540 = 99;
    (void)hoisted__I64_8540;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__I64(v.y, hoisted__I64_8540, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8544 = 10;
    (void)hoisted__I64_8544;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    assert_eq__I64(p.x, hoisted__I64_8544, &_til_str_lit_180);
    Str_delete(&_til_str_lit_180, (Bool){0});
    I64 hoisted__I64_8546 = 20;
    (void)hoisted__I64_8546;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__I64(p.y, hoisted__I64_8546, &_til_str_lit_181);
    Str_delete(&_til_str_lit_181, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8553 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8553;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8553;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8554 = 0;
    (void)hoisted__U32_8554;
    U64 hoisted__U64_8555 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8554); });
    (void)hoisted__U64_8555;
    return hoisted__U64_8555;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8586 = 32;
    (void)hoisted__U32_8586;
    return hoisted__U32_8586;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8587 = 5;
    (void)hoisted__I64_8587;
    (void)_til_str_lit_185;
    (void)_til_str_lit_185;
    assert_eq__I64(r.top_left.x, hoisted__I64_8587, &_til_str_lit_185);
    Str_delete(&_til_str_lit_185, (Bool){0});
    I64 hoisted__I64_8589 = 10;
    (void)hoisted__I64_8589;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(r.top_left.y, hoisted__I64_8589, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_8591 = 100;
    (void)hoisted__I64_8591;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8591, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    I64 hoisted__I64_8593 = 200;
    (void)hoisted__I64_8593;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8593, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8596 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8596;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8596;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8597 = 0;
    (void)hoisted__U32_8597;
    U64 hoisted__U64_8598 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8597); });
    (void)hoisted__U64_8598;
    return hoisted__U64_8598;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8641 = 12;
    (void)hoisted__U32_8641;
    return hoisted__U32_8641;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8645 = F32_to_str(v.x);
    (void)hoisted__Str_8645;
    (void)_til_str_lit_190;
    (void)_til_str_lit_190;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    assert_eq__Str(hoisted__Str_8645, &_til_str_lit_190, &_til_str_lit_191);
    Str_delete(hoisted__Str_8645, 1);
    Str_delete(&_til_str_lit_190, (Bool){0});
    Str_delete(&_til_str_lit_191, (Bool){0});
    Str *hoisted__Str_8648 = F32_to_str(v.y);
    (void)hoisted__Str_8648;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    assert_eq__Str(hoisted__Str_8648, &_til_str_lit_192, &_til_str_lit_193);
    Str_delete(hoisted__Str_8648, 1);
    Str_delete(&_til_str_lit_192, (Bool){0});
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str *hoisted__Str_8651 = F32_to_str(v.z);
    (void)hoisted__Str_8651;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    assert_eq__Str(hoisted__Str_8651, &_til_str_lit_194, &_til_str_lit_195);
    Str_delete(hoisted__Str_8651, 1);
    Str_delete(&_til_str_lit_194, (Bool){0});
    Str_delete(&_til_str_lit_195, (Bool){0});
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
    U32 hoisted__U32_8662 = 1;
    (void)hoisted__U32_8662;
    Bool hoisted__Bool_8663 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_8663;
    if (hoisted__Bool_8663) {
        U32 hoisted__U32_8656 = 1;
        (void)hoisted__U32_8656;
        Bool hoisted__Bool_8657 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_8657;
        { Bool _ret_val = hoisted__Bool_8657;
                return _ret_val; }
    }
    U32 hoisted__U32_8664 = 1;
    (void)hoisted__U32_8664;
    Bool hoisted__Bool_8665 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_8665;
    if (hoisted__Bool_8665) {
        U32 hoisted__U32_8658 = 1;
        (void)hoisted__U32_8658;
        Bool hoisted__Bool_8659 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_8659;
        { Bool _ret_val = hoisted__Bool_8659;
                return _ret_val; }
    }
    U32 hoisted__U32_8666 = 1;
    (void)hoisted__U32_8666;
    Bool hoisted__Bool_8667 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_8667;
    if (hoisted__Bool_8667) {
        U32 hoisted__U32_8660 = 1;
        (void)hoisted__U32_8660;
        Bool hoisted__Bool_8661 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_8661;
        { Bool _ret_val = hoisted__Bool_8661;
                return _ret_val; }
    }
    Bool hoisted__Bool_8668 = 0;
    (void)hoisted__Bool_8668;
    return hoisted__Bool_8668;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8676 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8676;
    if (hoisted__Bool_8676) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8677 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8677;
    if (hoisted__Bool_8677) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8678 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8678;
    if (hoisted__Bool_8678) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8679 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8679;
    UNREACHABLE(&hoisted__Str_8679);
    Str_delete(&hoisted__Str_8679, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8680 = 1;
    (void)hoisted__U32_8680;
    return hoisted__U32_8680;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8681 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8681;
    (void)_til_str_lit_199;
    (void)_til_str_lit_199;
    assert(hoisted__Bool_8681, &_til_str_lit_199);
    Str_delete(&_til_str_lit_199, (Bool){0});
    Bool hoisted__Bool_8683 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8683;
    Bool hoisted__Bool_8684 = ((Bool)(!(hoisted__Bool_8683)));
    (void)hoisted__Bool_8684;
    (void)_til_str_lit_200;
    (void)_til_str_lit_200;
    assert(hoisted__Bool_8684, &_til_str_lit_200);
    Str_delete(&_til_str_lit_200, (Bool){0});
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
    U32 hoisted__U32_8686 = 1;
    (void)hoisted__U32_8686;
    Bool hoisted__Bool_8687 = ((Bool)(((Token *)(self))->tag == ((Token *)(other))->tag));
    (void)hoisted__Bool_8687;
    return hoisted__Bool_8687;
}

void Token_delete(Token * self, Bool call_free) {
    U32 hoisted__U32_8711 = 1;
    (void)hoisted__U32_8711;
    Bool hoisted__Bool_8712 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8712;
    if (hoisted__Bool_8712) {
        I64 *hoisted__I64_8707 = get_payload(self);
        (void)hoisted__I64_8707;
        (void)hoisted__I64_8707;
        Bool hoisted__Bool_8708 = 0;
        (void)hoisted__Bool_8708;
        I64_delete(hoisted__I64_8707, hoisted__Bool_8708);
    }
    U32 hoisted__U32_8713 = 1;
    (void)hoisted__U32_8713;
    Bool hoisted__Bool_8714 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8714;
    if (hoisted__Bool_8714) {
        Str *hoisted__Str_8709 = get_payload(self);
        (void)hoisted__Str_8709;
        (void)hoisted__Str_8709;
        Bool hoisted__Bool_8710 = 0;
        (void)hoisted__Bool_8710;
        Str_delete(hoisted__Str_8709, hoisted__Bool_8710);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_8748 = 1;
    (void)hoisted__U32_8748;
    Bool hoisted__Bool_8749 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8749;
    if (hoisted__Bool_8749) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8745 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8745;
        { Token * _ret_val = hoisted__Token_8745;
                return _ret_val; }
    }
    U32 hoisted__U32_8750 = 1;
    (void)hoisted__U32_8750;
    Bool hoisted__Bool_8751 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8751;
    if (hoisted__Bool_8751) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8746 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8746;
        Token *hoisted__Token_8747 = Token_Name(hoisted__Str_8746);
        (void)hoisted__Token_8747;
        { Token * _ret_val = hoisted__Token_8747;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8752 = 24;
    (void)hoisted__U32_8752;
    return hoisted__U32_8752;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8754 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8754;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert(hoisted__Bool_8754, &_til_str_lit_203);
    Str_delete(&_til_str_lit_203, (Bool){0});
    Bool hoisted__Bool_8756 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8756;
    Bool hoisted__Bool_8757 = ((Bool)(!(hoisted__Bool_8756)));
    (void)hoisted__Bool_8757;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_8757, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8759 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8759;
    (void)_til_str_lit_205;
    (void)_til_str_lit_205;
    assert(hoisted__Bool_8759, &_til_str_lit_205);
    Str_delete(&_til_str_lit_205, (Bool){0});
    Bool hoisted__Bool_8761 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8761;
    Bool hoisted__Bool_8762 = ((Bool)(!(hoisted__Bool_8761)));
    (void)hoisted__Bool_8762;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_8762, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8766 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8766;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_8766, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Bool hoisted__Bool_8768 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8768;
    Bool hoisted__Bool_8769 = ((Bool)(!(hoisted__Bool_8768)));
    (void)hoisted__Bool_8769;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_8769, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8902 = ((Bool)(a != b));
    (void)hoisted__Bool_8902;
    if (hoisted__Bool_8902) {
        U32 hoisted__U32_8886 = 5;
        (void)hoisted__U32_8886;
        Array__Str *_va_Array_253 = Array__Str_new(hoisted__U32_8886);
        (void)_va_Array_253;
        I64 _va_Array_253_ek = 0;
        (void)_va_Array_253_ek;
        OutOfBounds *_va_Array_253_eo = malloc(sizeof(OutOfBounds));
        _va_Array_253_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_253_eo;
        U32 hoisted__U32_8887 = 0;
        (void)hoisted__U32_8887;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8887, &_til_str_lit_209, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8890 = 1;
        (void)hoisted__U32_8890;
        Str *hoisted__Str_8891 = I64_to_str(a);
        (void)hoisted__Str_8891;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8890, hoisted__Str_8891, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8893 = 2;
        (void)hoisted__U32_8893;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8893, &_til_str_lit_211, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8896 = 3;
        (void)hoisted__U32_8896;
        Str *hoisted__Str_8897 = I64_to_str(b);
        (void)hoisted__Str_8897;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8896, hoisted__Str_8897, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8899 = 4;
        (void)hoisted__U32_8899;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8899, &_til_str_lit_212, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        OutOfBounds_delete(_va_Array_253_eo, 1);
        Str_delete(&_til_str_lit_210, (Bool){0});
        panic(_va_Array_253, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8919 = Str_neq(a, b);
    (void)hoisted__Bool_8919;
    if (hoisted__Bool_8919) {
        U32 hoisted__U32_8903 = 5;
        (void)hoisted__U32_8903;
        Array__Str *_va_Array_254 = Array__Str_new(hoisted__U32_8903);
        (void)_va_Array_254;
        I64 _va_Array_254_ek = 0;
        (void)_va_Array_254_ek;
        OutOfBounds *_va_Array_254_eo = malloc(sizeof(OutOfBounds));
        _va_Array_254_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_254_eo;
        U32 hoisted__U32_8904 = 0;
        (void)hoisted__U32_8904;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8904, &_til_str_lit_209, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8907 = 1;
        (void)hoisted__U32_8907;
        Str *hoisted__Str_8908 = Str_to_str(a);
        (void)hoisted__Str_8908;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8907, hoisted__Str_8908, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8910 = 2;
        (void)hoisted__U32_8910;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8910, &_til_str_lit_211, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8913 = 3;
        (void)hoisted__U32_8913;
        Str *hoisted__Str_8914 = Str_to_str(b);
        (void)hoisted__Str_8914;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8913, hoisted__Str_8914, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8916 = 4;
        (void)hoisted__U32_8916;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8916, &_til_str_lit_212, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        OutOfBounds_delete(_va_Array_254_eo, 1);
        Str_delete(&_til_str_lit_210, (Bool){0});
        panic(_va_Array_254, loc);
    }
}

U32 Str_len_dyn(void *til_env, void *_a0) {
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
    return (void *)Str_with_capacity(*(U32 *)_a0);
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
U32 Str_size_dyn(void *til_env) {
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
U32 OutOfBounds_size_dyn(void *til_env) {
    (void)til_env;
    return OutOfBounds_size();
}
static __attribute__((unused)) TilClosure OutOfBounds_size_dyn__til_closure = { (void *)OutOfBounds_size_dyn, NULL, NULL };
void *Array__Str_new_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Array__Str_new(*(U32 *)_a0);
}
static __attribute__((unused)) TilClosure Array__Str_new_dyn__til_closure = { (void *)Array__Str_new_dyn, NULL, NULL };
U32 Array__Str_len_dyn(void *til_env, void *_a0) {
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
    Array__Str_unsafe_set(_a0, *(U32 *)_a1, _a2);
}
static __attribute__((unused)) TilClosure Array__Str_unsafe_set_dyn__til_closure = { (void *)Array__Str_unsafe_set_dyn, NULL, NULL };
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3, void *_a4, void *_a5) {
    (void)til_env;
    Array__Str_set(_a0, *(U32 *)_a1, _a2, _a3, _a4, _a5);
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
U32 Array__Str_size_dyn(void *til_env) {
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
U32 Vec__Str_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Str_size();
}
static __attribute__((unused)) TilClosure Vec__Str_size_dyn__til_closure = { (void *)Vec__Str_size_dyn, NULL, NULL };
U32 Dynamic_size_dyn(void *til_env) {
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
U32 U8_size_dyn(void *til_env) {
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
void U32_inc_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U32_inc(_a0);
}
static __attribute__((unused)) TilClosure U32_inc_dyn__til_closure = { (void *)U32_inc_dyn, NULL, NULL };
void U32_dec_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U32_dec(_a0);
}
static __attribute__((unused)) TilClosure U32_dec_dyn__til_closure = { (void *)U32_dec_dyn, NULL, NULL };
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
U32 U32_size_dyn(void *til_env) {
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
U32 U64_size_dyn(void *til_env) {
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
U32 I8_size_dyn(void *til_env) {
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
U32 I32_size_dyn(void *til_env) {
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
U32 I64_size_dyn(void *til_env) {
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
U32 F32_size_dyn(void *til_env) {
    (void)til_env;
    return F32_size();
}
static __attribute__((unused)) TilClosure F32_size_dyn__til_closure = { (void *)F32_size_dyn, NULL, NULL };
U64 F32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return F32_hash(*(F32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure F32_hash_dyn__til_closure = { (void *)F32_hash_dyn, NULL, NULL };
Bool Bool_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Bool_eq(*(Bool *)_a0, *(Bool *)_a1);
}
static __attribute__((unused)) TilClosure Bool_eq_dyn__til_closure = { (void *)Bool_eq_dyn, NULL, NULL };
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
U32 Bool_size_dyn(void *til_env) {
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
U32 Primitive_size_dyn(void *til_env) {
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
U32 Type_size_dyn(void *til_env) {
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
U32 FuncType_size_dyn(void *til_env) {
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
U32 OwnType_size_dyn(void *til_env) {
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
U32 Declaration_size_dyn(void *til_env) {
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
U32 FunctionDef_size_dyn(void *til_env) {
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
U32 FCallData_size_dyn(void *til_env) {
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
U32 LiteralNumData_size_dyn(void *til_env) {
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
U32 IdentData_size_dyn(void *til_env) {
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
U32 FieldAccessData_size_dyn(void *til_env) {
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
U32 StructDef_size_dyn(void *til_env) {
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
U32 EnumDef_size_dyn(void *til_env) {
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
U32 AssignData_size_dyn(void *til_env) {
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
U32 FieldAssignData_size_dyn(void *til_env) {
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
U32 ForInData_size_dyn(void *til_env) {
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
U32 Literal_size_dyn(void *til_env) {
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
U32 MatchData_size_dyn(void *til_env) {
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
U32 CaptureBlockData_size_dyn(void *til_env) {
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
U32 NodeType_size_dyn(void *til_env) {
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
U32 Expr_size_dyn(void *til_env) {
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
U32 Map__I64_Str_size_dyn(void *til_env) {
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
U32 Vec__Bool_size_dyn(void *til_env) {
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
U32 Vec__I64_size_dyn(void *til_env) {
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
U32 Vec__Declaration_size_dyn(void *til_env) {
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
U32 Vec__Expr_size_dyn(void *til_env) {
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
U32 Range_size_dyn(void *til_env) {
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
U32 CfVec2_size_dyn(void *til_env) {
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
U32 CfRect_size_dyn(void *til_env) {
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
U32 CfVec3f_size_dyn(void *til_env) {
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
U32 Color_size_dyn(void *til_env) {
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
U32 Token_size_dyn(void *til_env) {
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U32_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U32_dec_dyn__til_closure;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Bool_eq_dyn__til_closure;
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
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_44;
        if (*index == 2LL) return &_til_str_lit_45;
        if (*index == 3LL) return &_til_str_lit_46;
        if (*index == 4LL) return &_til_str_lit_47;
        if (*index == 5LL) return &_til_str_lit_48;
        if (*index == 6LL) return &_til_str_lit_49;
        if (*index == 7LL) return &_til_str_lit_50;
        if (*index == 8LL) return &_til_str_lit_52;
        if (*index == 9LL) return &_til_str_lit_54;
        if (*index == 10LL) return &_til_str_lit_56;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_57;
        if (*index == 1LL) return &_til_str_lit_59;
        if (*index == 2LL) return &_til_str_lit_61;
        if (*index == 3LL) return &_til_str_lit_62;
        if (*index == 4LL) return &_til_str_lit_64;
        if (*index == 5LL) return &_til_str_lit_65;
        if (*index == 6LL) return &_til_str_lit_66;
        if (*index == 7LL) return &_til_str_lit_67;
        if (*index == 8LL) return &_til_str_lit_68;
        if (*index == 9LL) return &_til_str_lit_69;
        if (*index == 10LL) return &_til_str_lit_70;
        if (*index == 11LL) return &_til_str_lit_71;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_72;
        if (*index == 1LL) return &_til_str_lit_73;
        if (*index == 2LL) return &_til_str_lit_74;
        if (*index == 3LL) return &_til_str_lit_75;
        if (*index == 4LL) return &_til_str_lit_76;
        if (*index == 5LL) return &_til_str_lit_52;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_77;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_78;
        if (*index == 1LL) return &_til_str_lit_79;
        if (*index == 2LL) return &_til_str_lit_80;
        if (*index == 3LL) return &_til_str_lit_81;
        if (*index == 4LL) return &_til_str_lit_82;
        if (*index == 5LL) return &_til_str_lit_83;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_79;
        if (*index == 1LL) return &_til_str_lit_84;
        if (*index == 2LL) return &_til_str_lit_85;
        if (*index == 3LL) return &_til_str_lit_87;
        if (*index == 4LL) return &_til_str_lit_83;
        if (*index == 5LL) return &_til_str_lit_89;
        if (*index == 6LL) return &_til_str_lit_90;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_92;
        if (*index == 2LL) return &_til_str_lit_93;
        if (*index == 3LL) return &_til_str_lit_76;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_92;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_46;
        if (*index == 2LL) return &_til_str_lit_52;
        if (*index == 3LL) return &_til_str_lit_94;
        if (*index == 4LL) return &_til_str_lit_95;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_52;
        if (*index == 1LL) return &_til_str_lit_101;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_70;
        if (*index == 1LL) return &_til_str_lit_71;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_136;
        if (*index == 1LL) return &_til_str_lit_138;
        if (*index == 2LL) return &_til_str_lit_140;
        if (*index == 3LL) return &_til_str_lit_141;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_142;
        if (*index == 1LL) return &_til_str_lit_143;
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
        if (*index == 0LL) return &_til_str_lit_150;
        if (*index == 1LL) return &_til_str_lit_151;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_176;
        if (*index == 1LL) return &_til_str_lit_177;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_182;
        if (*index == 1LL) return &_til_str_lit_184;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_176;
        if (*index == 1LL) return &_til_str_lit_177;
        if (*index == 2LL) return &_til_str_lit_189;
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
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_16;
        if (*index == 6LL) return &_til_str_lit_16;
        if (*index == 7LL) return &_til_str_lit_51;
        if (*index == 8LL) return &_til_str_lit_53;
        if (*index == 9LL) return &_til_str_lit_55;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_58;
        if (*index == 1LL) return &_til_str_lit_60;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_63;
        if (*index == 4LL) return &_til_str_lit_13;
        if (*index == 5LL) return &_til_str_lit_13;
        if (*index == 6LL) return &_til_str_lit_51;
        if (*index == 7LL) return &_til_str_lit_16;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_16;
        if (*index == 10LL) return &_til_str_lit_60;
        if (*index == 11LL) return &_til_str_lit_6;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_10;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_53;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_60;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_6;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_63;
        if (*index == 2LL) return &_til_str_lit_86;
        if (*index == 3LL) return &_til_str_lit_88;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
        if (*index == 6LL) return &_til_str_lit_91;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_16;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_16;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_53;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_16;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_53;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_137;
        if (*index == 1LL) return &_til_str_lit_139;
        if (*index == 2LL) return &_til_str_lit_3;
        if (*index == 3LL) return &_til_str_lit_3;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_91;
        if (*index == 1LL) return &_til_str_lit_63;
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
        if (*index == 0LL) return &_til_str_lit_14;
        if (*index == 1LL) return &_til_str_lit_14;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_183;
        if (*index == 1LL) return &_til_str_lit_183;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_15;
        if (*index == 1LL) return &_til_str_lit_15;
        if (*index == 2LL) return &_til_str_lit_15;
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
        if (*index == 4LL) return &_til_str_lit_3;
        if (*index == 5LL) return &_til_str_lit_13;
        if (*index == 6LL) return &_til_str_lit_10;
        if (*index == 7LL) return &_til_str_lit_14;
        if (*index == 8LL) return &_til_str_lit_15;
        if (*index == 9LL) return &_til_str_lit_16;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_19;
        if (*index == 2LL) return &_til_str_lit_20;
        if (*index == 3LL) return &_til_str_lit_21;
        if (*index == 4LL) return &_til_str_lit_22;
        if (*index == 5LL) return &_til_str_lit_23;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_25;
        if (*index == 8LL) return &_til_str_lit_9;
        if (*index == 9LL) return &_til_str_lit_26;
        if (*index == 10LL) return &_til_str_lit_27;
        if (*index == 11LL) return &_til_str_lit_28;
        if (*index == 12LL) return &_til_str_lit_29;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_30;
        if (*index == 1LL) return &_til_str_lit_31;
        if (*index == 2LL) return &_til_str_lit_32;
        if (*index == 3LL) return &_til_str_lit_33;
        if (*index == 4LL) return &_til_str_lit_34;
        if (*index == 5LL) return &_til_str_lit_35;
        if (*index == 6LL) return &_til_str_lit_36;
        if (*index == 7LL) return &_til_str_lit_37;
        if (*index == 8LL) return &_til_str_lit_38;
        if (*index == 9LL) return &_til_str_lit_39;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_40;
        if (*index == 1LL) return &_til_str_lit_41;
        if (*index == 2LL) return &_til_str_lit_42;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_96;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_98;
        if (*index == 4LL) return &_til_str_lit_99;
        if (*index == 5LL) return &_til_str_lit_100;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_29;
        if (*index == 1LL) return &_til_str_lit_102;
        if (*index == 2LL) return &_til_str_lit_103;
        if (*index == 3LL) return &_til_str_lit_105;
        if (*index == 4LL) return &_til_str_lit_107;
        if (*index == 5LL) return &_til_str_lit_109;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_112;
        if (*index == 10LL) return &_til_str_lit_114;
        if (*index == 11LL) return &_til_str_lit_116;
        if (*index == 12LL) return &_til_str_lit_117;
        if (*index == 13LL) return &_til_str_lit_118;
        if (*index == 14LL) return &_til_str_lit_119;
        if (*index == 15LL) return &_til_str_lit_121;
        if (*index == 16LL) return &_til_str_lit_122;
        if (*index == 17LL) return &_til_str_lit_123;
        if (*index == 18LL) return &_til_str_lit_124;
        if (*index == 19LL) return &_til_str_lit_125;
        if (*index == 20LL) return &_til_str_lit_127;
        if (*index == 21LL) return &_til_str_lit_128;
        if (*index == 22LL) return &_til_str_lit_129;
        if (*index == 23LL) return &_til_str_lit_130;
        if (*index == 24LL) return &_til_str_lit_131;
        if (*index == 25LL) return &_til_str_lit_132;
        if (*index == 26LL) return &_til_str_lit_134;
        if (*index == 27LL) return &_til_str_lit_135;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_196;
        if (*index == 1LL) return &_til_str_lit_197;
        if (*index == 2LL) return &_til_str_lit_198;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_96;
        if (*index == 1LL) return &_til_str_lit_201;
        if (*index == 2LL) return &_til_str_lit_202;
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
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_6;
        if (*index == 10LL) return &_til_str_lit_27;
        if (*index == 11LL) return &_til_str_lit_6;
        if (*index == 12LL) return &_til_str_lit_17;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_97;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_102;
        if (*index == 2LL) return &_til_str_lit_104;
        if (*index == 3LL) return &_til_str_lit_106;
        if (*index == 4LL) return &_til_str_lit_108;
        if (*index == 5LL) return &_til_str_lit_110;
        if (*index == 6LL) return &_til_str_lit_111;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_113;
        if (*index == 10LL) return &_til_str_lit_115;
        if (*index == 11LL) return &_til_str_lit_17;
        if (*index == 12LL) return &_til_str_lit_17;
        if (*index == 13LL) return &_til_str_lit_17;
        if (*index == 14LL) return &_til_str_lit_120;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_17;
        if (*index == 17LL) return &_til_str_lit_17;
        if (*index == 18LL) return &_til_str_lit_17;
        if (*index == 19LL) return &_til_str_lit_126;
        if (*index == 20LL) return &_til_str_lit_17;
        if (*index == 21LL) return &_til_str_lit_17;
        if (*index == 22LL) return &_til_str_lit_17;
        if (*index == 23LL) return &_til_str_lit_17;
        if (*index == 24LL) return &_til_str_lit_17;
        if (*index == 25LL) return &_til_str_lit_133;
        if (*index == 26LL) return &_til_str_lit_17;
        if (*index == 27LL) return &_til_str_lit_133;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_14;
        if (*index == 1LL) return &_til_str_lit_6;
        if (*index == 2LL) return &_til_str_lit_17;
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
