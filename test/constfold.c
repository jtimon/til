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
typedef struct Vec__Declaration Vec__Declaration;
typedef struct Vec__Expr Vec__Expr;
typedef struct Vec__I64 Vec__I64;
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


typedef struct Vec__I64 {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__I64;


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
    Color_tag tag;
};

struct Token {
    Token_tag tag;
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


void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_neq(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Bool I32_lt(I32 a, I32 b);
Bool I32_gt(I32 a, I32 b);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
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
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
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
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
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

void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_neq(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Bool I32_lt(I32 a, I32 b);
Bool I32_gt(I32 a, I32 b);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
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
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
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
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
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

static Str hoisted__Str_7209 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7211 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7212 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7216 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7228 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7229 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7232 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7233 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7454 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7462 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7470 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7473 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7474 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7502 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7503 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7507 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7508 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7531 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7532 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7543 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7544 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7557 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8156 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8157 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8160 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8164 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8168 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8173 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8174 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8175 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8178 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8179 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8180 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8220 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8222 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8226 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8228 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8269 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8271 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8273 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8275 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8327 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8328 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8330 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8331 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8333 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8334 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8356 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8359 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8415 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8418 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8420 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8423 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8427 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8430 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8548 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8549 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8552 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8554 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8555 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8558 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8560 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8561 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8565 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8566 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8569 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8571 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8572 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8575 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8577 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8578 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};

U32 CAP_LIT;
U32 CAP_VIEW;
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;
Str __til_docs_blob__;
Str __til_info_blob__;

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_1 = 4;
    (void)hoisted__U32_1;
    return hoisted__U32_1;
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_19 = 0;
    (void)hoisted__U32_19;
    U64 hoisted__U64_20 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_19); });
    (void)hoisted__U64_20;
    return hoisted__U64_20;
}

void U64_inc(U64 * self) {
    U64 hoisted__U64_36 = 1ULL;
    (void)hoisted__U64_36;
    U64 hoisted__U64_37 = ((U64)(DEREF(self) + hoisted__U64_36));
    (void)hoisted__U64_37;
    *self = hoisted__U64_37;
}

void U64_dec(U64 * self) {
    U64 hoisted__U64_38 = 1ULL;
    (void)hoisted__U64_38;
    U64 hoisted__U64_39 = ((U64)(DEREF(self) - hoisted__U64_38));
    (void)hoisted__U64_39;
    *self = hoisted__U64_39;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_44 = 8;
    (void)hoisted__U32_44;
    return hoisted__U32_44;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_129 = 0;
    (void)hoisted__U32_129;
    U64 hoisted__U64_130 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_129); });
    (void)hoisted__U64_130;
    return hoisted__U64_130;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_145 = U32_to_i64(val);
    (void)hoisted__I64_145;
    Str *hoisted__Str_146 = I64_to_str(hoisted__I64_145);
    (void)hoisted__Str_146;
    return hoisted__Str_146;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_147 = 1;
    (void)hoisted__U32_147;
    U32 hoisted__U32_148 = ((U32)(DEREF(self) + hoisted__U32_147));
    (void)hoisted__U32_148;
    *self = hoisted__U32_148;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_149 = 1;
    (void)hoisted__U32_149;
    U32 hoisted__U32_150 = ((U32)(DEREF(self) - hoisted__U32_149));
    (void)hoisted__U32_150;
    *self = hoisted__U32_150;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_157 = 4;
    (void)hoisted__U32_157;
    return hoisted__U32_157;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_242 = 0;
    (void)hoisted__U32_242;
    U64 hoisted__U64_243 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_242); });
    (void)hoisted__U64_243;
    return hoisted__U64_243;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_246 = U32_cmp(a, b);
    (void)hoisted__I64_246;
    I64 hoisted__I64_247 = -1;
    (void)hoisted__I64_247;
    Bool hoisted__Bool_248 = ((Bool)(hoisted__I64_246 == hoisted__I64_247));
    (void)hoisted__Bool_248;
    return hoisted__Bool_248;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_249 = U32_cmp(a, b);
    (void)hoisted__I64_249;
    I64 hoisted__I64_250 = 1;
    (void)hoisted__I64_250;
    Bool hoisted__Bool_251 = ((Bool)(hoisted__I64_249 == hoisted__I64_250));
    (void)hoisted__Bool_251;
    return hoisted__Bool_251;
}

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_252 = ((Bool)(a == b));
    (void)hoisted__Bool_252;
    Bool hoisted__Bool_253 = not(hoisted__Bool_252);
    (void)hoisted__Bool_253;
    return hoisted__Bool_253;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_254 = U32_gt(a, b);
    (void)hoisted__Bool_254;
    Bool hoisted__Bool_255 = not(hoisted__Bool_254);
    (void)hoisted__Bool_255;
    return hoisted__Bool_255;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_256 = U32_lt(a, b);
    (void)hoisted__Bool_256;
    Bool hoisted__Bool_257 = not(hoisted__Bool_256);
    (void)hoisted__Bool_257;
    return hoisted__Bool_257;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_278 = 4;
    (void)hoisted__U32_278;
    return hoisted__U32_278;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_420 = 0;
    (void)hoisted__U32_420;
    U64 hoisted__U64_421 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_420); });
    (void)hoisted__U64_421;
    return hoisted__U64_421;
}

Bool I32_lt(I32 a, I32 b) {
    I64 hoisted__I64_424 = I32_cmp(a, b);
    (void)hoisted__I64_424;
    I64 hoisted__I64_425 = -1;
    (void)hoisted__I64_425;
    Bool hoisted__Bool_426 = ((Bool)(hoisted__I64_424 == hoisted__I64_425));
    (void)hoisted__Bool_426;
    return hoisted__Bool_426;
}

Bool I32_gt(I32 a, I32 b) {
    I64 hoisted__I64_427 = I32_cmp(a, b);
    (void)hoisted__I64_427;
    I64 hoisted__I64_428 = 1;
    (void)hoisted__I64_428;
    Bool hoisted__Bool_429 = ((Bool)(hoisted__I64_427 == hoisted__I64_428));
    (void)hoisted__Bool_429;
    return hoisted__Bool_429;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_456 = 1;
    (void)hoisted__U32_456;
    return hoisted__U32_456;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_457 = 0;
    (void)hoisted__U32_457;
    U64 hoisted__U64_458 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_457); });
    (void)hoisted__U64_458;
    return hoisted__U64_458;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_485 = 1;
    (void)hoisted__U32_485;
    return hoisted__U32_485;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_570 = 0;
    (void)hoisted__U32_570;
    U64 hoisted__U64_571 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_570); });
    (void)hoisted__U64_571;
    return hoisted__U64_571;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_701 = parts;
        (void)_fc_Array__Str_701;
        (void)_fc_Array__Str_701;
        U32 _fi_USize_701 = 0;
        (void)_fi_USize_701;
        while (1) {
            U32 hoisted__U32_703 = Array__Str_len(_fc_Array__Str_701);
            (void)hoisted__U32_703;
            Bool _wcond_Bool_702 = U32_lt(_fi_USize_701, hoisted__U32_703);
            (void)_wcond_Bool_702;
            if (_wcond_Bool_702) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_701, &_fi_USize_701);
            U32 hoisted__U32_704 = 1;
            (void)hoisted__U32_704;
            U32 hoisted__U32_705 = ((U32)(_fi_USize_701 + hoisted__U32_704));
            (void)hoisted__U32_705;
            _fi_USize_701 = hoisted__U32_705;
            U32 hoisted__U32_706 = Str_len(s);
            (void)hoisted__U32_706;
            U32 hoisted__U32_707 = ((U32)(total + hoisted__U32_706));
            (void)hoisted__U32_707;
            total = hoisted__U32_707;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_708 = parts;
        (void)_fc_Array__Str_708;
        (void)_fc_Array__Str_708;
        U32 _fi_USize_708 = 0;
        (void)_fi_USize_708;
        while (1) {
            U32 hoisted__U32_710 = Array__Str_len(_fc_Array__Str_708);
            (void)hoisted__U32_710;
            Bool _wcond_Bool_709 = U32_lt(_fi_USize_708, hoisted__U32_710);
            (void)_wcond_Bool_709;
            if (_wcond_Bool_709) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_708, &_fi_USize_708);
            U32 hoisted__U32_711 = 1;
            (void)hoisted__U32_711;
            U32 hoisted__U32_712 = ((U32)(_fi_USize_708 + hoisted__U32_711));
            (void)hoisted__U32_712;
            _fi_USize_708 = hoisted__U32_712;
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
    Bool hoisted__Bool_728 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_728;
    if (hoisted__Bool_728) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_729 = 0;
    (void)hoisted__I32_729;
    Bool hoisted__Bool_730 = I32_lt(c, hoisted__I32_729);
    (void)hoisted__Bool_730;
    if (hoisted__Bool_730) {
        I64 hoisted__I64_726 = -1;
        (void)hoisted__I64_726;
        { I64 _ret_val = hoisted__I64_726;
                        return _ret_val; }
    }
    I32 hoisted__I32_731 = 0;
    (void)hoisted__I32_731;
    Bool hoisted__Bool_732 = I32_gt(c, hoisted__I32_731);
    (void)hoisted__Bool_732;
    if (hoisted__Bool_732) {
        I64 hoisted__I64_727 = 1;
        (void)hoisted__I64_727;
        { I64 _ret_val = hoisted__I64_727;
                        return _ret_val; }
    }
    I64 hoisted__I64_733 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_733;
    return hoisted__I64_733;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_734 = 1;
    (void)hoisted__U32_734;
    U32 hoisted__U64_735 = ((U64)(n + hoisted__U32_734));
    (void)hoisted__U64_735;
    void * buf = malloc(hoisted__U64_735);
    I32 hoisted__I32_736 = 0;
    (void)hoisted__I32_736;
    U64 hoisted__U64_737 = 1ULL;
    (void)hoisted__U64_737;
    memset(buf, hoisted__I32_736, hoisted__U64_737);
    I64 hoisted__I64_738 = 0;
    (void)hoisted__I64_738;
    Str *hoisted__Str_739 = malloc(sizeof(Str));
    hoisted__Str_739->c_str = buf;
    hoisted__Str_739->count = hoisted__I64_738;
    hoisted__Str_739->cap = n;
    (void)hoisted__Str_739;
    return hoisted__Str_739;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_752 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_752;
    if (hoisted__Bool_752) {
        U32 hoisted__U32_742 = 1;
        (void)hoisted__U32_742;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_742);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_743 = 0;
        (void)hoisted__U32_743;
        static Str hoisted__Str_744 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_744;
        static Str hoisted__Str_745 = (Str){.c_str = (void *)"./src/core/str.til:104:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_745;
        Array__Str_set(_va_Array_18, hoisted__U32_743, &hoisted__Str_744, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_745);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_745, (Bool){0});
        static Str hoisted__Str_746 = (Str){.c_str = (void *)"./src/core/str.til:104:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_746;
        panic(_va_Array_18, &hoisted__Str_746);
        Str_delete(&hoisted__Str_746, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_753 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_753;
    if (hoisted__Bool_753) {
        U32 hoisted__U32_747 = 1;
        (void)hoisted__U32_747;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_747);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_748 = 0;
        (void)hoisted__U32_748;
        static Str hoisted__Str_749 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_749;
        static Str hoisted__Str_750 = (Str){.c_str = (void *)"./src/core/str.til:108:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_750;
        Array__Str_set(_va_Array_19, hoisted__U32_748, &hoisted__Str_749, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_750);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_750, (Bool){0});
        static Str hoisted__Str_751 = (Str){.c_str = (void *)"./src/core/str.til:108:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_751;
        panic(_va_Array_19, &hoisted__Str_751);
        Str_delete(&hoisted__Str_751, (Bool){0});
    }
    void *hoisted__v_754 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_754;
    (void)hoisted__v_754;
    memcpy(hoisted__v_754, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_755 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_755;
    (void)hoisted__v_755;
    I32 hoisted__I32_756 = 0;
    (void)hoisted__I32_756;
    U64 hoisted__U64_757 = 1ULL;
    (void)hoisted__U64_757;
    memset(hoisted__v_755, hoisted__I32_756, hoisted__U64_757);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_758 = 1;
    (void)hoisted__U32_758;
    U32 hoisted__U64_759 = ((U64)(val->count + hoisted__U32_758));
    (void)hoisted__U64_759;
    void * new_data = malloc(hoisted__U64_759);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_760 = ptr_add(new_data, val->count);
    (void)hoisted__v_760;
    (void)hoisted__v_760;
    I32 hoisted__I32_761 = 0;
    (void)hoisted__I32_761;
    U64 hoisted__U64_762 = 1ULL;
    (void)hoisted__U64_762;
    memset(hoisted__v_760, hoisted__I32_761, hoisted__U64_762);
    Str *hoisted__Str_763 = malloc(sizeof(Str));
    hoisted__Str_763->c_str = new_data;
    hoisted__Str_763->count = val->count;
    hoisted__Str_763->cap = val->count;
    (void)hoisted__Str_763;
    return hoisted__Str_763;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_764 = Str_clone(self);
    (void)hoisted__Str_764;
    return hoisted__Str_764;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_765 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_765;
    if (hoisted__Bool_765) {
        free(self->c_str);
    }
    Bool hoisted__Bool_766 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_766;
    Bool hoisted__Bool_767 = and(call_free, hoisted__Bool_766);
    (void)hoisted__Bool_767;
    if (hoisted__Bool_767) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_962 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_962;
    return hoisted__U64_962;
}

U32 Str_size(void) {
    U32 hoisted__U32_1146 = 16;
    (void)hoisted__U32_1146;
    return hoisted__U32_1146;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1147 = Str_cmp(a, b);
    (void)hoisted__I64_1147;
    I64 hoisted__I64_1148 = 0;
    (void)hoisted__I64_1148;
    Bool hoisted__Bool_1149 = ((Bool)(hoisted__I64_1147 == hoisted__I64_1148));
    (void)hoisted__Bool_1149;
    return hoisted__Bool_1149;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1158 = Str_eq(a, b);
    (void)hoisted__Bool_1158;
    Bool hoisted__Bool_1159 = not(hoisted__Bool_1158);
    (void)hoisted__Bool_1159;
    return hoisted__Bool_1159;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1250 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1250->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1250;
    return hoisted__OutOfBounds_1250;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1251 = 0;
    (void)hoisted__Bool_1251;
    Str_delete(&self->msg, hoisted__Bool_1251);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1252 = 0;
    (void)hoisted__U32_1252;
    U64 hoisted__U64_1253 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1252); });
    (void)hoisted__U64_1253;
    return hoisted__U64_1253;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1272 = 16;
    (void)hoisted__U32_1272;
    return hoisted__U32_1272;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_1296 = 16;
    (void)hoisted__U32_1296;
    U64 hoisted__U64_1297 = (U64)(cap);
    (void)hoisted__U64_1297;
    U64 hoisted__U64_1298 = (U64)(hoisted__U32_1296);
    (void)hoisted__U64_1298;
    void * hoisted__v_1299 = calloc(hoisted__U64_1297, hoisted__U64_1298);
    (void)hoisted__v_1299;
    Array__Str *hoisted__Array__Str_1300 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1300->data = hoisted__v_1299;
    hoisted__Array__Str_1300->cap = cap;
    (void)hoisted__Array__Str_1300;
    return hoisted__Array__Str_1300;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_1301 = 16;
    (void)hoisted__U32_1301;
    U32 hoisted__U32_1302 = ((U32)(DEREF(i) * hoisted__U32_1301));
    (void)hoisted__U32_1302;
    U64 hoisted__U64_1303 = (U64)(hoisted__U32_1302);
    (void)hoisted__U64_1303;
    void *hoisted__v_1304 = ptr_add(self->data, hoisted__U64_1303);
    (void)hoisted__v_1304;
    (void)hoisted__v_1304;
    return hoisted__v_1304;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_1331 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1331;
    (void)hoisted__Str_1331;
    Bool hoisted__Bool_1332 = 0;
    (void)hoisted__Bool_1332;
    Str_delete(hoisted__Str_1331, hoisted__Bool_1332);
    U32 hoisted__U32_1333 = 16;
    (void)hoisted__U32_1333;
    Str *hoisted__Str_1334 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1334;
    (void)hoisted__Str_1334;
    U64 hoisted__U64_1335 = (U64)(hoisted__U32_1333);
    (void)hoisted__U64_1335;
    memcpy(hoisted__Str_1334, val, hoisted__U64_1335);
    U32 hoisted__U32_1336 = 16;
    (void)hoisted__U32_1336;
    I32 hoisted__I32_1337 = 0;
    (void)hoisted__I32_1337;
    U64 hoisted__U64_1338 = (U64)(hoisted__U32_1336);
    (void)hoisted__U64_1338;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1337, hoisted__U64_1338); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1361 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1361;
    if (hoisted__Bool_1361) {
        U32 hoisted__U32_1339 = 6;
        (void)hoisted__U32_1339;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1339);
        (void)_va_Array_31;
        I64 _va_Array_31_ek = 0;
        (void)_va_Array_31_ek;
        OutOfBounds *_va_Array_31_eo = malloc(sizeof(OutOfBounds));
        _va_Array_31_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_31_eo;
        U32 hoisted__U32_1340 = 0;
        (void)hoisted__U32_1340;
        Str *hoisted__Str_1341 = Str_clone(loc);
        (void)hoisted__Str_1341;
        static Str hoisted__Str_1342 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1342;
        Array__Str_set(_va_Array_31, hoisted__U32_1340, hoisted__Str_1341, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1342);
        Str_delete(&hoisted__Str_1342, (Bool){0});
        U32 hoisted__U32_1343 = 1;
        (void)hoisted__U32_1343;
        static Str hoisted__Str_1344 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1344;
        static Str hoisted__Str_1345 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1345;
        Array__Str_set(_va_Array_31, hoisted__U32_1343, &hoisted__Str_1344, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1345);
        Str_delete(&hoisted__Str_1345, (Bool){0});
        U32 hoisted__U32_1346 = 2;
        (void)hoisted__U32_1346;
        Str *hoisted__Str_1347 = U32_to_str(i);
        (void)hoisted__Str_1347;
        static Str hoisted__Str_1348 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1348;
        Array__Str_set(_va_Array_31, hoisted__U32_1346, hoisted__Str_1347, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1348);
        Str_delete(&hoisted__Str_1348, (Bool){0});
        U32 hoisted__U32_1349 = 3;
        (void)hoisted__U32_1349;
        static Str hoisted__Str_1350 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1350;
        static Str hoisted__Str_1351 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1351;
        Array__Str_set(_va_Array_31, hoisted__U32_1349, &hoisted__Str_1350, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1351);
        Str_delete(&hoisted__Str_1351, (Bool){0});
        U32 hoisted__U32_1352 = 4;
        (void)hoisted__U32_1352;
        Str *hoisted__Str_1353 = U32_to_str(self->cap);
        (void)hoisted__Str_1353;
        static Str hoisted__Str_1354 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1354;
        Array__Str_set(_va_Array_31, hoisted__U32_1352, hoisted__Str_1353, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1354);
        Str_delete(&hoisted__Str_1354, (Bool){0});
        U32 hoisted__U32_1355 = 5;
        (void)hoisted__U32_1355;
        static Str hoisted__Str_1356 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1356;
        static Str hoisted__Str_1357 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1357;
        Array__Str_set(_va_Array_31, hoisted__U32_1355, &hoisted__Str_1356, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1357);
        OutOfBounds_delete(_va_Array_31_eo, 1);
        Str_delete(&hoisted__Str_1357, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1358 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_31); hoisted__OutOfBounds_1358->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1358;
        U32 hoisted__U32_1359 = 16;
        (void)hoisted__U32_1359;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1358, hoisted__U32_1359);
        OutOfBounds_delete(hoisted__OutOfBounds_1358, 1);
        I64 hoisted__I64_1360 = 3;
        (void)hoisted__I64_1360;
        *_err_kind = hoisted__I64_1360;
    }
    I64 hoisted__I64_1362 = 0;
    (void)hoisted__I64_1362;
    Bool hoisted__Bool_1363 = ((Bool)(DEREF(_err_kind) == hoisted__I64_1362));
    (void)hoisted__Bool_1363;
    if (hoisted__Bool_1363) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1364 = self->cap;
        (void)_re_U32_1364;
        U32 _rc_U32_1364 = 0;
        (void)_rc_U32_1364;
        Bool hoisted__Bool_1377 = U32_lte(_rc_U32_1364, _re_U32_1364);
        (void)hoisted__Bool_1377;
        if (hoisted__Bool_1377) {
            while (1) {
                Bool _wcond_Bool_1365 = U32_lt(_rc_U32_1364, _re_U32_1364);
                (void)_wcond_Bool_1365;
                if (_wcond_Bool_1365) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1364);
                U32_inc(&_rc_U32_1364);
                U32 hoisted__U32_1366 = 16;
                (void)hoisted__U32_1366;
                U32 hoisted__U32_1367 = ((U32)(i * hoisted__U32_1366));
                (void)hoisted__U32_1367;
                U64 hoisted__U64_1368 = (U64)(hoisted__U32_1367);
                (void)hoisted__U64_1368;
                Str *hoisted__Str_1369 = ptr_add(self->data, hoisted__U64_1368);
                (void)hoisted__Str_1369;
                (void)hoisted__Str_1369;
                Bool hoisted__Bool_1370 = 0;
                (void)hoisted__Bool_1370;
                Str_delete(hoisted__Str_1369, hoisted__Bool_1370);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1371 = U32_gt(_rc_U32_1364, _re_U32_1364);
                (void)_wcond_Bool_1371;
                if (_wcond_Bool_1371) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1364);
                U32_dec(&_rc_U32_1364);
                U32 hoisted__U32_1372 = 16;
                (void)hoisted__U32_1372;
                U32 hoisted__U32_1373 = ((U32)(i * hoisted__U32_1372));
                (void)hoisted__U32_1373;
                U64 hoisted__U64_1374 = (U64)(hoisted__U32_1373);
                (void)hoisted__U64_1374;
                Str *hoisted__Str_1375 = ptr_add(self->data, hoisted__U64_1374);
                (void)hoisted__Str_1375;
                (void)hoisted__Str_1375;
                Bool hoisted__Bool_1376 = 0;
                (void)hoisted__Bool_1376;
                Str_delete(hoisted__Str_1375, hoisted__Bool_1376);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1406 = 16;
    (void)hoisted__U32_1406;
    U32 hoisted__U32_1407 = ((U32)(self->cap * hoisted__U32_1406));
    (void)hoisted__U32_1407;
    U64 hoisted__U64_1408 = (U64)(hoisted__U32_1407);
    (void)hoisted__U64_1408;
    void * new_data = malloc(hoisted__U64_1408);
    {
        U32 _re_U32_1378 = self->cap;
        (void)_re_U32_1378;
        U32 _rc_U32_1378 = 0;
        (void)_rc_U32_1378;
        Bool hoisted__Bool_1405 = U32_lte(_rc_U32_1378, _re_U32_1378);
        (void)hoisted__Bool_1405;
        if (hoisted__Bool_1405) {
            while (1) {
                Bool _wcond_Bool_1379 = U32_lt(_rc_U32_1378, _re_U32_1378);
                (void)_wcond_Bool_1379;
                if (_wcond_Bool_1379) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1378);
                U32_inc(&_rc_U32_1378);
                U32 hoisted__U32_1380 = 16;
                (void)hoisted__U32_1380;
                U32 hoisted__U32_1381 = ((U32)(i * hoisted__U32_1380));
                (void)hoisted__U32_1381;
                U64 hoisted__U64_1382 = (U64)(hoisted__U32_1381);
                (void)hoisted__U64_1382;
                Str *src = ptr_add(self->data, hoisted__U64_1382);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1383 = 16;
                (void)hoisted__U32_1383;
                U32 hoisted__U32_1384 = ((U32)(i * hoisted__U32_1383));
                (void)hoisted__U32_1384;
                U64 hoisted__U64_1385 = (U64)(hoisted__U32_1384);
                (void)hoisted__U64_1385;
                U32 hoisted__U32_1386 = 16;
                (void)hoisted__U32_1386;
                void *hoisted__v_1387 = ptr_add(new_data, hoisted__U64_1385);
                (void)hoisted__v_1387;
                (void)hoisted__v_1387;
                U64 hoisted__U64_1388 = (U64)(hoisted__U32_1386);
                (void)hoisted__U64_1388;
                memcpy(hoisted__v_1387, cloned, hoisted__U64_1388);
                U32 hoisted__U32_1389 = 16;
                (void)hoisted__U32_1389;
                I32 hoisted__I32_1390 = 0;
                (void)hoisted__I32_1390;
                U64 hoisted__U64_1391 = (U64)(hoisted__U32_1389);
                (void)hoisted__U64_1391;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1390, hoisted__U64_1391); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1392 = U32_gt(_rc_U32_1378, _re_U32_1378);
                (void)_wcond_Bool_1392;
                if (_wcond_Bool_1392) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1378);
                U32_dec(&_rc_U32_1378);
                U32 hoisted__U32_1393 = 16;
                (void)hoisted__U32_1393;
                U32 hoisted__U32_1394 = ((U32)(i * hoisted__U32_1393));
                (void)hoisted__U32_1394;
                U64 hoisted__U64_1395 = (U64)(hoisted__U32_1394);
                (void)hoisted__U64_1395;
                Str *src = ptr_add(self->data, hoisted__U64_1395);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1396 = 16;
                (void)hoisted__U32_1396;
                U32 hoisted__U32_1397 = ((U32)(i * hoisted__U32_1396));
                (void)hoisted__U32_1397;
                U64 hoisted__U64_1398 = (U64)(hoisted__U32_1397);
                (void)hoisted__U64_1398;
                U32 hoisted__U32_1399 = 16;
                (void)hoisted__U32_1399;
                void *hoisted__v_1400 = ptr_add(new_data, hoisted__U64_1398);
                (void)hoisted__v_1400;
                (void)hoisted__v_1400;
                U64 hoisted__U64_1401 = (U64)(hoisted__U32_1399);
                (void)hoisted__U64_1401;
                memcpy(hoisted__v_1400, cloned, hoisted__U64_1401);
                U32 hoisted__U32_1402 = 16;
                (void)hoisted__U32_1402;
                I32 hoisted__I32_1403 = 0;
                (void)hoisted__I32_1403;
                U64 hoisted__U64_1404 = (U64)(hoisted__U32_1402);
                (void)hoisted__U64_1404;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1403, hoisted__U64_1404); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1409 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1409->data = new_data;
    hoisted__Array__Str_1409->cap = self->cap;
    (void)hoisted__Array__Str_1409;
    return hoisted__Array__Str_1409;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1410 = 16;
    (void)hoisted__U32_1410;
    return hoisted__U32_1410;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1411 = 16;
    (void)hoisted__U32_1411;
    U64 hoisted__U64_1412 = (U64)(hoisted__U32_1411);
    (void)hoisted__U64_1412;
    void * hoisted__v_1413 = malloc(hoisted__U64_1412);
    (void)hoisted__v_1413;
    U32 hoisted__U32_1414 = 0;
    (void)hoisted__U32_1414;
    I64 hoisted__I64_1415 = 1;
    (void)hoisted__I64_1415;
    Vec__Str *hoisted__Vec__Str_1416 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1416->data = hoisted__v_1413;
    hoisted__Vec__Str_1416->count = hoisted__U32_1414;
    hoisted__Vec__Str_1416->cap = hoisted__I64_1415;
    (void)hoisted__Vec__Str_1416;
    return hoisted__Vec__Str_1416;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1426 = self->count;
        (void)_re_U32_1426;
        U32 _rc_U32_1426 = 0;
        (void)_rc_U32_1426;
        Bool hoisted__Bool_1439 = U32_lte(_rc_U32_1426, _re_U32_1426);
        (void)hoisted__Bool_1439;
        if (hoisted__Bool_1439) {
            while (1) {
                Bool _wcond_Bool_1427 = U32_lt(_rc_U32_1426, _re_U32_1426);
                (void)_wcond_Bool_1427;
                if (_wcond_Bool_1427) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1426);
                U32_inc(&_rc_U32_1426);
                U32 hoisted__U32_1428 = 16;
                (void)hoisted__U32_1428;
                U32 hoisted__U32_1429 = ((U32)(i * hoisted__U32_1428));
                (void)hoisted__U32_1429;
                U64 hoisted__U64_1430 = (U64)(hoisted__U32_1429);
                (void)hoisted__U64_1430;
                Str *hoisted__Str_1431 = ptr_add(self->data, hoisted__U64_1430);
                (void)hoisted__Str_1431;
                (void)hoisted__Str_1431;
                Bool hoisted__Bool_1432 = 0;
                (void)hoisted__Bool_1432;
                Str_delete(hoisted__Str_1431, hoisted__Bool_1432);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1433 = U32_gt(_rc_U32_1426, _re_U32_1426);
                (void)_wcond_Bool_1433;
                if (_wcond_Bool_1433) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1426);
                U32_dec(&_rc_U32_1426);
                U32 hoisted__U32_1434 = 16;
                (void)hoisted__U32_1434;
                U32 hoisted__U32_1435 = ((U32)(i * hoisted__U32_1434));
                (void)hoisted__U32_1435;
                U64 hoisted__U64_1436 = (U64)(hoisted__U32_1435);
                (void)hoisted__U64_1436;
                Str *hoisted__Str_1437 = ptr_add(self->data, hoisted__U64_1436);
                (void)hoisted__Str_1437;
                (void)hoisted__Str_1437;
                Bool hoisted__Bool_1438 = 0;
                (void)hoisted__Bool_1438;
                Str_delete(hoisted__Str_1437, hoisted__Bool_1438);
            }
        }
    }
    U32 hoisted__U32_1440 = 0;
    (void)hoisted__U32_1440;
    self->count = hoisted__U32_1440;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1710 = 16;
    (void)hoisted__U32_1710;
    U32 hoisted__U32_1711 = ((U32)(self->cap * hoisted__U32_1710));
    (void)hoisted__U32_1711;
    U64 hoisted__U64_1712 = (U64)(hoisted__U32_1711);
    (void)hoisted__U64_1712;
    void * new_data = malloc(hoisted__U64_1712);
    {
        U32 _re_U32_1682 = self->count;
        (void)_re_U32_1682;
        U32 _rc_U32_1682 = 0;
        (void)_rc_U32_1682;
        Bool hoisted__Bool_1709 = U32_lte(_rc_U32_1682, _re_U32_1682);
        (void)hoisted__Bool_1709;
        if (hoisted__Bool_1709) {
            while (1) {
                Bool _wcond_Bool_1683 = U32_lt(_rc_U32_1682, _re_U32_1682);
                (void)_wcond_Bool_1683;
                if (_wcond_Bool_1683) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1682);
                U32_inc(&_rc_U32_1682);
                U32 hoisted__U32_1684 = 16;
                (void)hoisted__U32_1684;
                U32 hoisted__U32_1685 = ((U32)(i * hoisted__U32_1684));
                (void)hoisted__U32_1685;
                U64 hoisted__U64_1686 = (U64)(hoisted__U32_1685);
                (void)hoisted__U64_1686;
                Str *src = ptr_add(self->data, hoisted__U64_1686);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1687 = 16;
                (void)hoisted__U32_1687;
                U32 hoisted__U32_1688 = ((U32)(i * hoisted__U32_1687));
                (void)hoisted__U32_1688;
                U64 hoisted__U64_1689 = (U64)(hoisted__U32_1688);
                (void)hoisted__U64_1689;
                U32 hoisted__U32_1690 = 16;
                (void)hoisted__U32_1690;
                void *hoisted__v_1691 = ptr_add(new_data, hoisted__U64_1689);
                (void)hoisted__v_1691;
                (void)hoisted__v_1691;
                U64 hoisted__U64_1692 = (U64)(hoisted__U32_1690);
                (void)hoisted__U64_1692;
                memcpy(hoisted__v_1691, cloned, hoisted__U64_1692);
                U32 hoisted__U32_1693 = 16;
                (void)hoisted__U32_1693;
                I32 hoisted__I32_1694 = 0;
                (void)hoisted__I32_1694;
                U64 hoisted__U64_1695 = (U64)(hoisted__U32_1693);
                (void)hoisted__U64_1695;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1694, hoisted__U64_1695); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1696 = U32_gt(_rc_U32_1682, _re_U32_1682);
                (void)_wcond_Bool_1696;
                if (_wcond_Bool_1696) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1682);
                U32_dec(&_rc_U32_1682);
                U32 hoisted__U32_1697 = 16;
                (void)hoisted__U32_1697;
                U32 hoisted__U32_1698 = ((U32)(i * hoisted__U32_1697));
                (void)hoisted__U32_1698;
                U64 hoisted__U64_1699 = (U64)(hoisted__U32_1698);
                (void)hoisted__U64_1699;
                Str *src = ptr_add(self->data, hoisted__U64_1699);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1700 = 16;
                (void)hoisted__U32_1700;
                U32 hoisted__U32_1701 = ((U32)(i * hoisted__U32_1700));
                (void)hoisted__U32_1701;
                U64 hoisted__U64_1702 = (U64)(hoisted__U32_1701);
                (void)hoisted__U64_1702;
                U32 hoisted__U32_1703 = 16;
                (void)hoisted__U32_1703;
                void *hoisted__v_1704 = ptr_add(new_data, hoisted__U64_1702);
                (void)hoisted__v_1704;
                (void)hoisted__v_1704;
                U64 hoisted__U64_1705 = (U64)(hoisted__U32_1703);
                (void)hoisted__U64_1705;
                memcpy(hoisted__v_1704, cloned, hoisted__U64_1705);
                U32 hoisted__U32_1706 = 16;
                (void)hoisted__U32_1706;
                I32 hoisted__I32_1707 = 0;
                (void)hoisted__I32_1707;
                U64 hoisted__U64_1708 = (U64)(hoisted__U32_1706);
                (void)hoisted__U64_1708;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1707, hoisted__U64_1708); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1713 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1713->data = new_data;
    hoisted__Vec__Str_1713->count = self->count;
    hoisted__Vec__Str_1713->cap = self->cap;
    (void)hoisted__Vec__Str_1713;
    return hoisted__Vec__Str_1713;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1714 = 16;
    (void)hoisted__U32_1714;
    return hoisted__U32_1714;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1717 = 8;
    (void)hoisted__U32_1717;
    return hoisted__U32_1717;
}

void * Dynamic_clone(void * self) {
    return self;
}

void Dynamic_delete(void * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1929 = 0;
    (void)hoisted__I64_1929;
    Bool hoisted__Bool_1930 = ((Bool)(val == hoisted__I64_1929));
    (void)hoisted__Bool_1930;
    if (hoisted__Bool_1930) {
        U64 hoisted__U64_1899 = 2ULL;
        (void)hoisted__U64_1899;
        void * buf = malloc(hoisted__U64_1899);
        I64 hoisted__I64_1900 = 48;
        (void)hoisted__I64_1900;
        U64 hoisted__U64_1901 = 1ULL;
        (void)hoisted__U64_1901;
        memcpy(buf, &hoisted__I64_1900, hoisted__U64_1901);
        U64 hoisted__U64_1902 = 1ULL;
        (void)hoisted__U64_1902;
        void *hoisted__v_1903 = ptr_add(buf, hoisted__U64_1902);
        (void)hoisted__v_1903;
        (void)hoisted__v_1903;
        I32 hoisted__I32_1904 = 0;
        (void)hoisted__I32_1904;
        U64 hoisted__U64_1905 = 1ULL;
        (void)hoisted__U64_1905;
        memset(hoisted__v_1903, hoisted__I32_1904, hoisted__U64_1905);
        I64 hoisted__I64_1906 = 1;
        (void)hoisted__I64_1906;
        I64 hoisted__I64_1907 = 1;
        (void)hoisted__I64_1907;
        Str *hoisted__Str_1908 = malloc(sizeof(Str));
        hoisted__Str_1908->c_str = buf;
        hoisted__Str_1908->count = hoisted__I64_1906;
        hoisted__Str_1908->cap = hoisted__I64_1907;
        (void)hoisted__Str_1908;
        { Str * _ret_val = hoisted__Str_1908;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1931 = 0;
    (void)hoisted__I64_1931;
    Bool hoisted__Bool_1932 = I64_lt(val, hoisted__I64_1931);
    (void)hoisted__Bool_1932;
    if (hoisted__Bool_1932) {
        Bool hoisted__Bool_1909 = 1;
        (void)hoisted__Bool_1909;
        is_neg = hoisted__Bool_1909;
        I64 hoisted__I64_1910 = 0;
        (void)hoisted__I64_1910;
        I64 hoisted__I64_1911 = ((I64)(hoisted__I64_1910 - val));
        (void)hoisted__I64_1911;
        v = hoisted__I64_1911;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1913 = 0;
        (void)hoisted__I64_1913;
        Bool _wcond_Bool_1912 = I64_gt(tmp, hoisted__I64_1913);
        (void)_wcond_Bool_1912;
        if (_wcond_Bool_1912) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1914 = 10;
        (void)hoisted__I64_1914;
        I64 hoisted__I64_1915 = ({ I64 _cf_a = tmp; I64 _cf_b = hoisted__I64_1914; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1915;
        tmp = hoisted__I64_1915;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1933 = 1ULL;
    (void)hoisted__U64_1933;
    U64 hoisted__U64_1934 = ((U64)(total + hoisted__U64_1933));
    (void)hoisted__U64_1934;
    void * buf = malloc(hoisted__U64_1934);
    if (is_neg) {
        I64 hoisted__I64_1916 = 45;
        (void)hoisted__I64_1916;
        U64 hoisted__U64_1917 = 1ULL;
        (void)hoisted__U64_1917;
        memcpy(buf, &hoisted__I64_1916, hoisted__U64_1917);
    }
    U64 hoisted__U64_1935 = 1ULL;
    (void)hoisted__U64_1935;
    U64 i = ((U64)(total - hoisted__U64_1935));
    while (1) {
        I64 hoisted__I64_1919 = 0;
        (void)hoisted__I64_1919;
        Bool _wcond_Bool_1918 = I64_gt(v, hoisted__I64_1919);
        (void)_wcond_Bool_1918;
        if (_wcond_Bool_1918) {
        } else {
            break;
        }
        I64 hoisted__I64_1920 = 10;
        (void)hoisted__I64_1920;
        I64 hoisted__I64_1921 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1920; (I64)((_cf_b == 0) ? 0 : (_cf_a % _cf_b)); });
        (void)hoisted__I64_1921;
        I64 hoisted__I64_1922 = 48;
        (void)hoisted__I64_1922;
        I64 hoisted__I64_1923 = ((I64)(hoisted__I64_1921 + hoisted__I64_1922));
        (void)hoisted__I64_1923;
        void *hoisted__v_1924 = ptr_add(buf, i);
        (void)hoisted__v_1924;
        (void)hoisted__v_1924;
        U8 hoisted__U8_1925 = I64_to_u8(hoisted__I64_1923);
        (void)hoisted__U8_1925;
        U64 hoisted__U64_1926 = 1ULL;
        (void)hoisted__U64_1926;
        memcpy(hoisted__v_1924, &hoisted__U8_1925, hoisted__U64_1926);
        I64 hoisted__I64_1927 = 10;
        (void)hoisted__I64_1927;
        I64 hoisted__I64_1928 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1927; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1928;
        v = hoisted__I64_1928;
        U64_dec(&i);
    }
    void *hoisted__v_1936 = ptr_add(buf, total);
    (void)hoisted__v_1936;
    (void)hoisted__v_1936;
    I32 hoisted__I32_1937 = 0;
    (void)hoisted__I32_1937;
    U64 hoisted__U64_1938 = 1ULL;
    (void)hoisted__U64_1938;
    memset(hoisted__v_1936, hoisted__I32_1937, hoisted__U64_1938);
    Str *hoisted__Str_1939 = malloc(sizeof(Str));
    hoisted__Str_1939->c_str = buf;
    hoisted__Str_1939->count = total;
    hoisted__Str_1939->cap = total;
    (void)hoisted__Str_1939;
    return hoisted__Str_1939;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1957 = 8;
    (void)hoisted__U32_1957;
    return hoisted__U32_1957;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2115 = 0;
    (void)hoisted__U32_2115;
    U64 hoisted__U64_2116 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2115); });
    (void)hoisted__U64_2116;
    return hoisted__U64_2116;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2119 = I64_cmp(a, b);
    (void)hoisted__I64_2119;
    I64 hoisted__I64_2120 = -1;
    (void)hoisted__I64_2120;
    Bool hoisted__Bool_2121 = ((Bool)(hoisted__I64_2119 == hoisted__I64_2120));
    (void)hoisted__Bool_2121;
    return hoisted__Bool_2121;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2122 = I64_cmp(a, b);
    (void)hoisted__I64_2122;
    I64 hoisted__I64_2123 = 1;
    (void)hoisted__I64_2123;
    Bool hoisted__Bool_2124 = ((Bool)(hoisted__I64_2122 == hoisted__I64_2123));
    (void)hoisted__Bool_2124;
    return hoisted__Bool_2124;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2125 = ((Bool)(a == b));
    (void)hoisted__Bool_2125;
    Bool hoisted__Bool_2126 = not(hoisted__Bool_2125);
    (void)hoisted__Bool_2126;
    return hoisted__Bool_2126;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2177 = 0;
    (void)_m_Bool_2177;
    {
        Bool hoisted__Bool_2180 = 1;
        (void)hoisted__Bool_2180;
        Bool hoisted__Bool_2181 = Bool_eq(a, hoisted__Bool_2180);
        (void)hoisted__Bool_2181;
        if (hoisted__Bool_2181) {
            Bool hoisted__Bool_2178 = Bool_clone(&b);
            (void)hoisted__Bool_2178;
            _m_Bool_2177 = hoisted__Bool_2178;
        } else {
            Bool hoisted__Bool_2179 = 0;
            (void)hoisted__Bool_2179;
            _m_Bool_2177 = hoisted__Bool_2179;
        }
    }
    return _m_Bool_2177;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2191 = Bool_eq(a, b);
    (void)hoisted__Bool_2191;
    if (hoisted__Bool_2191) {
        I64 hoisted__I64_2189 = 0;
        (void)hoisted__I64_2189;
        { I64 _ret_val = hoisted__I64_2189;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2190 = -1;
        (void)hoisted__I64_2190;
        return hoisted__I64_2190;
    }
    I64 hoisted__I64_2192 = 1;
    (void)hoisted__I64_2192;
    return hoisted__I64_2192;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2193 = 1;
    (void)hoisted__U32_2193;
    return hoisted__U32_2193;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2194 = 0;
    (void)hoisted__U32_2194;
    U64 hoisted__U64_2195 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2194); });
    (void)hoisted__U64_2195;
    return hoisted__U64_2195;
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
    Bool hoisted__Bool_2221 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        Bool hoisted__Bool_2211 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2211;
        { Bool _ret_val = hoisted__Bool_2211;
                return _ret_val; }
    }
    Bool hoisted__Bool_2222 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2222;
    if (hoisted__Bool_2222) {
        Bool hoisted__Bool_2212 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2212;
        { Bool _ret_val = hoisted__Bool_2212;
                return _ret_val; }
    }
    Bool hoisted__Bool_2223 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        Bool hoisted__Bool_2213 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2213;
        { Bool _ret_val = hoisted__Bool_2213;
                return _ret_val; }
    }
    Bool hoisted__Bool_2224 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2224;
    if (hoisted__Bool_2224) {
        Bool hoisted__Bool_2214 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2214;
        { Bool _ret_val = hoisted__Bool_2214;
                return _ret_val; }
    }
    Bool hoisted__Bool_2225 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2225;
    if (hoisted__Bool_2225) {
        Bool hoisted__Bool_2215 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2215;
        { Bool _ret_val = hoisted__Bool_2215;
                return _ret_val; }
    }
    Bool hoisted__Bool_2226 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2226;
    if (hoisted__Bool_2226) {
        Bool hoisted__Bool_2216 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2216;
        { Bool _ret_val = hoisted__Bool_2216;
                return _ret_val; }
    }
    Bool hoisted__Bool_2227 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2227;
    if (hoisted__Bool_2227) {
        Bool hoisted__Bool_2217 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2217;
        { Bool _ret_val = hoisted__Bool_2217;
                return _ret_val; }
    }
    Bool hoisted__Bool_2228 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2228;
    if (hoisted__Bool_2228) {
        Bool hoisted__Bool_2218 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2218;
        { Bool _ret_val = hoisted__Bool_2218;
                return _ret_val; }
    }
    Bool hoisted__Bool_2229 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2229;
    if (hoisted__Bool_2229) {
        Bool hoisted__Bool_2219 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2219;
        { Bool _ret_val = hoisted__Bool_2219;
                return _ret_val; }
    }
    Bool hoisted__Bool_2230 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2230;
    if (hoisted__Bool_2230) {
        Bool hoisted__Bool_2220 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2220;
        { Bool _ret_val = hoisted__Bool_2220;
                return _ret_val; }
    }
    Bool hoisted__Bool_2231 = 0;
    (void)hoisted__Bool_2231;
    return hoisted__Bool_2231;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2253 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2253;
    if (hoisted__Bool_2253) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2254 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2254;
    if (hoisted__Bool_2254) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2255 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2255;
    if (hoisted__Bool_2255) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2256 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2256;
    if (hoisted__Bool_2256) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2257 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2257;
    if (hoisted__Bool_2257) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2258 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2258;
    if (hoisted__Bool_2258) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2259 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2259;
    if (hoisted__Bool_2259) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2260 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2260;
    if (hoisted__Bool_2260) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2261 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2261;
    if (hoisted__Bool_2261) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2262 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2262;
    if (hoisted__Bool_2262) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2263 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2263;
    UNREACHABLE(&hoisted__Str_2263);
    Str_delete(&hoisted__Str_2263, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2264 = 4;
    (void)hoisted__U32_2264;
    return hoisted__U32_2264;
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
void Type_delete(Type * self, Bool call_free) {
    Bool hoisted__Bool_2316 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2316;
    if (hoisted__Bool_2316) {
        Str *hoisted__Str_2306 = get_payload(self);
        (void)hoisted__Str_2306;
        (void)hoisted__Str_2306;
        Bool hoisted__Bool_2307 = 0;
        (void)hoisted__Bool_2307;
        Str_delete(hoisted__Str_2306, hoisted__Bool_2307);
    }
    Bool hoisted__Bool_2317 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2317;
    if (hoisted__Bool_2317) {
        Str *hoisted__Str_2308 = get_payload(self);
        (void)hoisted__Str_2308;
        (void)hoisted__Str_2308;
        Bool hoisted__Bool_2309 = 0;
        (void)hoisted__Bool_2309;
        Str_delete(hoisted__Str_2308, hoisted__Bool_2309);
    }
    Bool hoisted__Bool_2318 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2318;
    if (hoisted__Bool_2318) {
        Str *hoisted__Str_2310 = get_payload(self);
        (void)hoisted__Str_2310;
        (void)hoisted__Str_2310;
        Bool hoisted__Bool_2311 = 0;
        (void)hoisted__Bool_2311;
        Str_delete(hoisted__Str_2310, hoisted__Bool_2311);
    }
    Bool hoisted__Bool_2319 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2319;
    if (hoisted__Bool_2319) {
        Primitive *hoisted__Primitive_2312 = get_payload(self);
        (void)hoisted__Primitive_2312;
        (void)hoisted__Primitive_2312;
        Bool hoisted__Bool_2313 = 0;
        (void)hoisted__Bool_2313;
        Primitive_delete(hoisted__Primitive_2312, hoisted__Bool_2313);
    }
    Bool hoisted__Bool_2320 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2320;
    if (hoisted__Bool_2320) {
        Str *hoisted__Str_2314 = get_payload(self);
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
    Bool hoisted__Bool_2404 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2404;
    if (hoisted__Bool_2404) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2405 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2405;
    if (hoisted__Bool_2405) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2406 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2406;
    if (hoisted__Bool_2406) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2396 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2396;
        Type *hoisted__Type_2397 = Type_Struct(hoisted__Str_2396);
        (void)hoisted__Type_2397;
        { Type * _ret_val = hoisted__Type_2397;
                return _ret_val; }
    }
    Bool hoisted__Bool_2407 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2407;
    if (hoisted__Bool_2407) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2408 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2408;
    if (hoisted__Bool_2408) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2398 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2398;
        Type *hoisted__Type_2399 = Type_Enum(hoisted__Str_2398);
        (void)hoisted__Type_2399;
        { Type * _ret_val = hoisted__Type_2399;
                return _ret_val; }
    }
    Bool hoisted__Bool_2409 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2409;
    if (hoisted__Bool_2409) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2410 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2410;
    if (hoisted__Bool_2410) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2411 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2411;
    if (hoisted__Bool_2411) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2412 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2412;
    if (hoisted__Bool_2412) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2413 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2413;
    if (hoisted__Bool_2413) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2400 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2400;
        Type *hoisted__Type_2401 = Type_Custom(hoisted__Str_2400);
        (void)hoisted__Type_2401;
        { Type * _ret_val = hoisted__Type_2401;
                return _ret_val; }
    }
    Bool hoisted__Bool_2414 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2414;
    if (hoisted__Bool_2414) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2402 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2402;
        Type *hoisted__Type_2403 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2402; _oa; }));
        (void)hoisted__Type_2403;
        { Type * _ret_val = hoisted__Type_2403;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2415 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2415;
    Type *hoisted__Type_2416 = Type_FuncPtrSig(hoisted__Str_2415);
    (void)hoisted__Type_2416;
    return hoisted__Type_2416;
}

U32 Type_size(void) {
    U32 hoisted__U32_2417 = 24;
    (void)hoisted__U32_2417;
    return hoisted__U32_2417;
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
    Bool hoisted__Bool_2520 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2520;
    if (hoisted__Bool_2520) {
        Bool hoisted__Bool_2510 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2510;
        { Bool _ret_val = hoisted__Bool_2510;
                return _ret_val; }
    }
    Bool hoisted__Bool_2521 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2521;
    if (hoisted__Bool_2521) {
        Bool hoisted__Bool_2511 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2511;
        { Bool _ret_val = hoisted__Bool_2511;
                return _ret_val; }
    }
    Bool hoisted__Bool_2522 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2522;
    if (hoisted__Bool_2522) {
        Bool hoisted__Bool_2512 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2512;
        { Bool _ret_val = hoisted__Bool_2512;
                return _ret_val; }
    }
    Bool hoisted__Bool_2523 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2523;
    if (hoisted__Bool_2523) {
        Bool hoisted__Bool_2513 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2513;
        { Bool _ret_val = hoisted__Bool_2513;
                return _ret_val; }
    }
    Bool hoisted__Bool_2524 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2524;
    if (hoisted__Bool_2524) {
        Bool hoisted__Bool_2514 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2514;
        { Bool _ret_val = hoisted__Bool_2514;
                return _ret_val; }
    }
    Bool hoisted__Bool_2525 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2525;
    if (hoisted__Bool_2525) {
        Bool hoisted__Bool_2515 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2515;
        { Bool _ret_val = hoisted__Bool_2515;
                return _ret_val; }
    }
    Bool hoisted__Bool_2526 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2526;
    if (hoisted__Bool_2526) {
        Bool hoisted__Bool_2516 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2516;
        { Bool _ret_val = hoisted__Bool_2516;
                return _ret_val; }
    }
    Bool hoisted__Bool_2527 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2527;
    if (hoisted__Bool_2527) {
        Bool hoisted__Bool_2517 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2517;
        { Bool _ret_val = hoisted__Bool_2517;
                return _ret_val; }
    }
    Bool hoisted__Bool_2528 = is(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2528;
    if (hoisted__Bool_2528) {
        Bool hoisted__Bool_2518 = is(other, &(FuncType){.tag = FuncType_TAG_CoreFunc});
        (void)hoisted__Bool_2518;
        { Bool _ret_val = hoisted__Bool_2518;
                return _ret_val; }
    }
    Bool hoisted__Bool_2529 = is(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2529;
    if (hoisted__Bool_2529) {
        Bool hoisted__Bool_2519 = is(other, &(FuncType){.tag = FuncType_TAG_CoreProc});
        (void)hoisted__Bool_2519;
        { Bool _ret_val = hoisted__Bool_2519;
                return _ret_val; }
    }
    Bool hoisted__Bool_2530 = 0;
    (void)hoisted__Bool_2530;
    return hoisted__Bool_2530;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2552 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2552;
    if (hoisted__Bool_2552) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2553 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2553;
    if (hoisted__Bool_2553) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2554 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2554;
    if (hoisted__Bool_2554) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2555 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2555;
    if (hoisted__Bool_2555) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2556 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2556;
    if (hoisted__Bool_2556) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2557 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2557;
    if (hoisted__Bool_2557) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2558 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2558;
    if (hoisted__Bool_2558) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2559 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2559;
    if (hoisted__Bool_2559) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2560 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2560;
    if (hoisted__Bool_2560) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2561 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2561;
    if (hoisted__Bool_2561) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2562 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2562;
    UNREACHABLE(&hoisted__Str_2562);
    Str_delete(&hoisted__Str_2562, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2563 = 4;
    (void)hoisted__U32_2563;
    return hoisted__U32_2563;
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
    Bool hoisted__Bool_2568 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2568;
    if (hoisted__Bool_2568) {
        Bool hoisted__Bool_2565 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2565;
        { Bool _ret_val = hoisted__Bool_2565;
                return _ret_val; }
    }
    Bool hoisted__Bool_2569 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2569;
    if (hoisted__Bool_2569) {
        Bool hoisted__Bool_2566 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2566;
        { Bool _ret_val = hoisted__Bool_2566;
                return _ret_val; }
    }
    Bool hoisted__Bool_2570 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2570;
    if (hoisted__Bool_2570) {
        Bool hoisted__Bool_2567 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2567;
        { Bool _ret_val = hoisted__Bool_2567;
                return _ret_val; }
    }
    Bool hoisted__Bool_2571 = 0;
    (void)hoisted__Bool_2571;
    return hoisted__Bool_2571;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2579 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2579;
    if (hoisted__Bool_2579) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2580 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2580;
    if (hoisted__Bool_2580) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2581 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2581;
    if (hoisted__Bool_2581) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2582 = (Str){.c_str = (void *)"OwnType.clone:141:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2582;
    UNREACHABLE(&hoisted__Str_2582);
    Str_delete(&hoisted__Str_2582, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2583 = 4;
    (void)hoisted__U32_2583;
    return hoisted__U32_2583;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2585 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2585;
    Declaration *hoisted__Declaration_2586 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2586->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2586->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2586->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2586->is_mut = self->is_mut;
    hoisted__Declaration_2586->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2586->is_priv = self->is_priv;
    hoisted__Declaration_2586->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2586->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2586->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2586->default_value = hoisted__Expr_2585;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2586->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2586;
    return hoisted__Declaration_2586;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2587 = 0;
    (void)hoisted__Bool_2587;
    Str_delete(&self->name, hoisted__Bool_2587);
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    Str_delete(&self->doc, hoisted__Bool_2588);
    Bool hoisted__Bool_2589 = 0;
    (void)hoisted__Bool_2589;
    Str_delete(&self->explicit_type, hoisted__Bool_2589);
    Bool hoisted__Bool_2590 = 0;
    (void)hoisted__Bool_2590;
    Bool_delete(&self->is_mut, hoisted__Bool_2590);
    Bool hoisted__Bool_2591 = 0;
    (void)hoisted__Bool_2591;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2591);
    Bool hoisted__Bool_2592 = 0;
    (void)hoisted__Bool_2592;
    Bool_delete(&self->is_priv, hoisted__Bool_2592);
    Bool hoisted__Bool_2593 = 0;
    (void)hoisted__Bool_2593;
    Bool_delete(&self->used, hoisted__Bool_2593);
    Bool hoisted__Bool_2594 = 0;
    (void)hoisted__Bool_2594;
    OwnType_delete(&self->own_type, hoisted__Bool_2594);
    Bool hoisted__Bool_2595 = 0;
    (void)hoisted__Bool_2595;
    Type_delete(&self->til_type, hoisted__Bool_2595);
    Bool hoisted__Bool_2596 = 1;
    (void)hoisted__Bool_2596;
    Expr_delete(self->default_value, hoisted__Bool_2596);
    Bool hoisted__Bool_2597 = 0;
    (void)hoisted__Bool_2597;
    Str_delete(&self->orig_name, hoisted__Bool_2597);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2598 = 104;
    (void)hoisted__U32_2598;
    return hoisted__U32_2598;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2600 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2600->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2600->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2600->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2600->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2600->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2600->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2600->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2600->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2600->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2600->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2600->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2600;
    return hoisted__FunctionDef_2600;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2601 = 0;
    (void)hoisted__Bool_2601;
    FuncType_delete(&self->func_type, hoisted__Bool_2601);
    Bool hoisted__Bool_2602 = 0;
    (void)hoisted__Bool_2602;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2602);
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Str_delete(&self->return_type, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    I32_delete(&self->variadic_index, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    I32_delete(&self->kwargs_index, hoisted__Bool_2606);
    Bool hoisted__Bool_2607 = 0;
    (void)hoisted__Bool_2607;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2607);
    Bool hoisted__Bool_2608 = 0;
    (void)hoisted__Bool_2608;
    Bool_delete(&self->auto_generated, hoisted__Bool_2608);
    Bool hoisted__Bool_2609 = 0;
    (void)hoisted__Bool_2609;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2609);
    Bool hoisted__Bool_2610 = 0;
    (void)hoisted__Bool_2610;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2610);
    Bool hoisted__Bool_2611 = 0;
    (void)hoisted__Bool_2611;
    Str_delete(&self->closure_name, hoisted__Bool_2611);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2612 = 0;
    (void)hoisted__U32_2612;
    U64 hoisted__U64_2613 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2612); });
    (void)hoisted__U64_2613;
    return hoisted__U64_2613;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2614 = 104;
    (void)hoisted__U32_2614;
    return hoisted__U32_2614;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2617 = malloc(sizeof(FCallData));
    hoisted__FCallData_2617->is_splat = self->is_splat;
    hoisted__FCallData_2617->does_throw = self->does_throw;
    hoisted__FCallData_2617->is_bang = self->is_bang;
    hoisted__FCallData_2617->own_args = self->own_args;
    hoisted__FCallData_2617->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2617->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2617;
    return hoisted__FCallData_2617;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2618 = 0;
    (void)hoisted__Bool_2618;
    Bool_delete(&self->is_splat, hoisted__Bool_2618);
    Bool hoisted__Bool_2619 = 0;
    (void)hoisted__Bool_2619;
    Bool_delete(&self->does_throw, hoisted__Bool_2619);
    Bool hoisted__Bool_2620 = 0;
    (void)hoisted__Bool_2620;
    Bool_delete(&self->is_bang, hoisted__Bool_2620);
    Bool hoisted__Bool_2621 = 0;
    (void)hoisted__Bool_2621;
    U64_delete(&self->own_args, hoisted__Bool_2621);
    Bool hoisted__Bool_2622 = 0;
    (void)hoisted__Bool_2622;
    Bool_delete(&self->swap_replace, hoisted__Bool_2622);
    Bool hoisted__Bool_2623 = 0;
    (void)hoisted__Bool_2623;
    Type_delete(&self->til_type, hoisted__Bool_2623);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2624 = 0;
    (void)hoisted__U32_2624;
    U64 hoisted__U64_2625 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2624); });
    (void)hoisted__U64_2625;
    return hoisted__U64_2625;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2626 = 48;
    (void)hoisted__U32_2626;
    return hoisted__U32_2626;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2638 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2638->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2638->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2638;
    return hoisted__LiteralNumData_2638;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2639 = 0;
    (void)hoisted__Bool_2639;
    Str_delete(&self->text, hoisted__Bool_2639);
    Bool hoisted__Bool_2640 = 0;
    (void)hoisted__Bool_2640;
    Type_delete(&self->til_type, hoisted__Bool_2640);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2641 = 0;
    (void)hoisted__U32_2641;
    U64 hoisted__U64_2642 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2641); });
    (void)hoisted__U64_2642;
    return hoisted__U64_2642;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2643 = 40;
    (void)hoisted__U32_2643;
    return hoisted__U32_2643;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2653 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2653->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2653->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2653;
    return hoisted__IdentData_2653;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2654 = 0;
    (void)hoisted__Bool_2654;
    Str_delete(&self->name, hoisted__Bool_2654);
    Bool hoisted__Bool_2655 = 0;
    (void)hoisted__Bool_2655;
    Type_delete(&self->til_type, hoisted__Bool_2655);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2656 = 0;
    (void)hoisted__U32_2656;
    U64 hoisted__U64_2657 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2656); });
    (void)hoisted__U64_2657;
    return hoisted__U64_2657;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2658 = 40;
    (void)hoisted__U32_2658;
    return hoisted__U32_2658;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2664 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2664->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2664->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2664;
    return hoisted__FieldAccessData_2664;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2665 = 0;
    (void)hoisted__Bool_2665;
    Str_delete(&self->name, hoisted__Bool_2665);
    Bool hoisted__Bool_2666 = 0;
    (void)hoisted__Bool_2666;
    Type_delete(&self->til_type, hoisted__Bool_2666);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2667 = 0;
    (void)hoisted__U32_2667;
    U64 hoisted__U64_2668 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2667); });
    (void)hoisted__U64_2668;
    return hoisted__U64_2668;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2669 = 40;
    (void)hoisted__U32_2669;
    return hoisted__U32_2669;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2750 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2750->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2750->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2750->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2750->is_interface = self->is_interface;
    hoisted__StructDef_2750->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2750->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2750;
    return hoisted__StructDef_2750;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2751);
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2752);
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Str_delete(&self->c_tag, hoisted__Bool_2753);
    Bool hoisted__Bool_2754 = 0;
    (void)hoisted__Bool_2754;
    Bool_delete(&self->is_interface, hoisted__Bool_2754);
    Bool hoisted__Bool_2755 = 0;
    (void)hoisted__Bool_2755;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2755);
    Bool hoisted__Bool_2756 = 0;
    (void)hoisted__Bool_2756;
    Str_delete(&self->implements_name, hoisted__Bool_2756);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2757 = 0;
    (void)hoisted__U32_2757;
    U64 hoisted__U64_2758 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2757); });
    (void)hoisted__U64_2758;
    return hoisted__U64_2758;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2759 = 72;
    (void)hoisted__U32_2759;
    return hoisted__U32_2759;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2764 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2764->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2764->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2764->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2764->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2764->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2764->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2764;
    return hoisted__EnumDef_2764;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2765 = 0;
    (void)hoisted__Bool_2765;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2765);
    Bool hoisted__Bool_2766 = 0;
    (void)hoisted__Bool_2766;
    Vec__Str_delete(&self->variants, hoisted__Bool_2766);
    Bool hoisted__Bool_2767 = 0;
    (void)hoisted__Bool_2767;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2767);
    Bool hoisted__Bool_2768 = 0;
    (void)hoisted__Bool_2768;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2768);
    Bool hoisted__Bool_2769 = 0;
    (void)hoisted__Bool_2769;
    Str_delete(&self->implements_name, hoisted__Bool_2769);
    Bool hoisted__Bool_2770 = 0;
    (void)hoisted__Bool_2770;
    Str_delete(&self->tag_type, hoisted__Bool_2770);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2771 = 0;
    (void)hoisted__U32_2771;
    U64 hoisted__U64_2772 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2771); });
    (void)hoisted__U64_2772;
    return hoisted__U64_2772;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2773 = 112;
    (void)hoisted__U32_2773;
    return hoisted__U32_2773;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2872 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2872->name = *_ca; free(_ca); }
    hoisted__AssignData_2872->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2872->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2872->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2872;
    return hoisted__AssignData_2872;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2873 = 0;
    (void)hoisted__Bool_2873;
    Str_delete(&self->name, hoisted__Bool_2873);
    Bool hoisted__Bool_2874 = 0;
    (void)hoisted__Bool_2874;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2874);
    Bool hoisted__Bool_2875 = 0;
    (void)hoisted__Bool_2875;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2875);
    Bool hoisted__Bool_2876 = 0;
    (void)hoisted__Bool_2876;
    Bool_delete(&self->swap_replace, hoisted__Bool_2876);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2877 = 0;
    (void)hoisted__U32_2877;
    U64 hoisted__U64_2878 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2877); });
    (void)hoisted__U64_2878;
    return hoisted__U64_2878;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2879 = 24;
    (void)hoisted__U32_2879;
    return hoisted__U32_2879;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2881 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2881->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2881->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2881;
    return hoisted__FieldAssignData_2881;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2882 = 0;
    (void)hoisted__Bool_2882;
    Str_delete(&self->name, hoisted__Bool_2882);
    Bool hoisted__Bool_2883 = 0;
    (void)hoisted__Bool_2883;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2883);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2884 = 0;
    (void)hoisted__U32_2884;
    U64 hoisted__U64_2885 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2884); });
    (void)hoisted__U64_2885;
    return hoisted__U64_2885;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2886 = 24;
    (void)hoisted__U32_2886;
    return hoisted__U32_2886;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2888 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2888->name = *_ca; free(_ca); }
    hoisted__ForInData_2888->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2888->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2888->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2888->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2888;
    return hoisted__ForInData_2888;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2889 = 0;
    (void)hoisted__Bool_2889;
    Str_delete(&self->name, hoisted__Bool_2889);
    Bool hoisted__Bool_2890 = 0;
    (void)hoisted__Bool_2890;
    Bool_delete(&self->is_mut, hoisted__Bool_2890);
    Bool hoisted__Bool_2891 = 0;
    (void)hoisted__Bool_2891;
    Type_delete(&self->til_type, hoisted__Bool_2891);
    Bool hoisted__Bool_2892 = 0;
    (void)hoisted__Bool_2892;
    Str_delete(&self->name2, hoisted__Bool_2892);
    Bool hoisted__Bool_2893 = 0;
    (void)hoisted__Bool_2893;
    Bool_delete(&self->is_mut2, hoisted__Bool_2893);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2894 = 0;
    (void)hoisted__U32_2894;
    U64 hoisted__U64_2895 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2894); });
    (void)hoisted__U64_2895;
    return hoisted__U64_2895;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2896 = 72;
    (void)hoisted__U32_2896;
    return hoisted__U32_2896;
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
    Bool hoisted__Bool_2926 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2926;
    if (hoisted__Bool_2926) {
        Str *hoisted__Str_2920 = get_payload(self);
        (void)hoisted__Str_2920;
        (void)hoisted__Str_2920;
        Bool hoisted__Bool_2921 = 0;
        (void)hoisted__Bool_2921;
        Str_delete(hoisted__Str_2920, hoisted__Bool_2921);
    }
    Bool hoisted__Bool_2927 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2927;
    if (hoisted__Bool_2927) {
        LiteralNumData *hoisted__LiteralNumData_2922 = get_payload(self);
        (void)hoisted__LiteralNumData_2922;
        (void)hoisted__LiteralNumData_2922;
        Bool hoisted__Bool_2923 = 0;
        (void)hoisted__Bool_2923;
        LiteralNumData_delete(hoisted__LiteralNumData_2922, hoisted__Bool_2923);
    }
    Bool hoisted__Bool_2928 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2928;
    if (hoisted__Bool_2928) {
        Bool *hoisted__Bool_2924 = get_payload(self);
        (void)hoisted__Bool_2924;
        (void)hoisted__Bool_2924;
        Bool hoisted__Bool_2925 = 0;
        (void)hoisted__Bool_2925;
        Bool_delete(hoisted__Bool_2924, hoisted__Bool_2925);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2977 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2977;
    if (hoisted__Bool_2977) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2972 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2972;
        Literal *hoisted__Literal_2973 = Literal_Str(hoisted__Str_2972);
        (void)hoisted__Literal_2973;
        { Literal * _ret_val = hoisted__Literal_2973;
                return _ret_val; }
    }
    Bool hoisted__Bool_2978 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2978;
    if (hoisted__Bool_2978) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2974 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2974;
        Literal *hoisted__Literal_2975 = Literal_Num(hoisted__LiteralNumData_2974);
        (void)hoisted__Literal_2975;
        { Literal * _ret_val = hoisted__Literal_2975;
                return _ret_val; }
    }
    Bool hoisted__Bool_2979 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2979;
    if (hoisted__Bool_2979) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2976 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2976;
        { Literal * _ret_val = hoisted__Literal_2976;
                return _ret_val; }
    }
    Bool hoisted__Bool_2980 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2980;
    if (hoisted__Bool_2980) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2981 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2981;
    if (hoisted__Bool_2981) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2982 = 48;
    (void)hoisted__U32_2982;
    return hoisted__U32_2982;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2985 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2985->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2985->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2985;
    return hoisted__MatchData_2985;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2986 = 0;
    (void)hoisted__Bool_2986;
    Type_delete(&self->til_type, hoisted__Bool_2986);
    Bool hoisted__Bool_2987 = 0;
    (void)hoisted__Bool_2987;
    Str_delete(&self->result_temp, hoisted__Bool_2987);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2988 = 0;
    (void)hoisted__U32_2988;
    U64 hoisted__U64_2989 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2988); });
    (void)hoisted__U64_2989;
    return hoisted__U64_2989;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2990 = 40;
    (void)hoisted__U32_2990;
    return hoisted__U32_2990;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2995 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2995->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2995;
    return hoisted__CaptureBlockData_2995;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2996 = 0;
    (void)hoisted__Bool_2996;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2996);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2997 = 0;
    (void)hoisted__U32_2997;
    U64 hoisted__U64_2998 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2997); });
    (void)hoisted__U64_2998;
    return hoisted__U64_2998;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2999 = 16;
    (void)hoisted__U32_2999;
    return hoisted__U32_2999;
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
void NodeType_delete(NodeType * self, Bool call_free) {
    Bool hoisted__Bool_3178 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3178;
    if (hoisted__Bool_3178) {
        Literal *hoisted__Literal_3150 = get_payload(self);
        (void)hoisted__Literal_3150;
        (void)hoisted__Literal_3150;
        Bool hoisted__Bool_3151 = 0;
        (void)hoisted__Bool_3151;
        Literal_delete(hoisted__Literal_3150, hoisted__Bool_3151);
    }
    Bool hoisted__Bool_3179 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3179;
    if (hoisted__Bool_3179) {
        IdentData *hoisted__IdentData_3152 = get_payload(self);
        (void)hoisted__IdentData_3152;
        (void)hoisted__IdentData_3152;
        Bool hoisted__Bool_3153 = 0;
        (void)hoisted__Bool_3153;
        IdentData_delete(hoisted__IdentData_3152, hoisted__Bool_3153);
    }
    Bool hoisted__Bool_3180 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3180;
    if (hoisted__Bool_3180) {
        Declaration *hoisted__Declaration_3154 = get_payload(self);
        (void)hoisted__Declaration_3154;
        (void)hoisted__Declaration_3154;
        Bool hoisted__Bool_3155 = 0;
        (void)hoisted__Bool_3155;
        Declaration_delete(hoisted__Declaration_3154, hoisted__Bool_3155);
    }
    Bool hoisted__Bool_3181 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3181;
    if (hoisted__Bool_3181) {
        AssignData *hoisted__AssignData_3156 = get_payload(self);
        (void)hoisted__AssignData_3156;
        (void)hoisted__AssignData_3156;
        Bool hoisted__Bool_3157 = 0;
        (void)hoisted__Bool_3157;
        AssignData_delete(hoisted__AssignData_3156, hoisted__Bool_3157);
    }
    Bool hoisted__Bool_3182 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3182;
    if (hoisted__Bool_3182) {
        FCallData *hoisted__FCallData_3158 = get_payload(self);
        (void)hoisted__FCallData_3158;
        (void)hoisted__FCallData_3158;
        Bool hoisted__Bool_3159 = 0;
        (void)hoisted__Bool_3159;
        FCallData_delete(hoisted__FCallData_3158, hoisted__Bool_3159);
    }
    Bool hoisted__Bool_3183 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3183;
    if (hoisted__Bool_3183) {
        FunctionDef *hoisted__FunctionDef_3160 = get_payload(self);
        (void)hoisted__FunctionDef_3160;
        (void)hoisted__FunctionDef_3160;
        Bool hoisted__Bool_3161 = 0;
        (void)hoisted__Bool_3161;
        FunctionDef_delete(hoisted__FunctionDef_3160, hoisted__Bool_3161);
    }
    Bool hoisted__Bool_3184 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3184;
    if (hoisted__Bool_3184) {
        StructDef *hoisted__StructDef_3162 = get_payload(self);
        (void)hoisted__StructDef_3162;
        (void)hoisted__StructDef_3162;
        Bool hoisted__Bool_3163 = 0;
        (void)hoisted__Bool_3163;
        StructDef_delete(hoisted__StructDef_3162, hoisted__Bool_3163);
    }
    Bool hoisted__Bool_3185 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3185;
    if (hoisted__Bool_3185) {
        EnumDef *hoisted__EnumDef_3164 = get_payload(self);
        (void)hoisted__EnumDef_3164;
        (void)hoisted__EnumDef_3164;
        Bool hoisted__Bool_3165 = 0;
        (void)hoisted__Bool_3165;
        EnumDef_delete(hoisted__EnumDef_3164, hoisted__Bool_3165);
    }
    Bool hoisted__Bool_3186 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3186;
    if (hoisted__Bool_3186) {
        FieldAccessData *hoisted__FieldAccessData_3166 = get_payload(self);
        (void)hoisted__FieldAccessData_3166;
        (void)hoisted__FieldAccessData_3166;
        Bool hoisted__Bool_3167 = 0;
        (void)hoisted__Bool_3167;
        FieldAccessData_delete(hoisted__FieldAccessData_3166, hoisted__Bool_3167);
    }
    Bool hoisted__Bool_3187 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3187;
    if (hoisted__Bool_3187) {
        FieldAssignData *hoisted__FieldAssignData_3168 = get_payload(self);
        (void)hoisted__FieldAssignData_3168;
        (void)hoisted__FieldAssignData_3168;
        Bool hoisted__Bool_3169 = 0;
        (void)hoisted__Bool_3169;
        FieldAssignData_delete(hoisted__FieldAssignData_3168, hoisted__Bool_3169);
    }
    Bool hoisted__Bool_3188 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3188;
    if (hoisted__Bool_3188) {
        ForInData *hoisted__ForInData_3170 = get_payload(self);
        (void)hoisted__ForInData_3170;
        (void)hoisted__ForInData_3170;
        Bool hoisted__Bool_3171 = 0;
        (void)hoisted__Bool_3171;
        ForInData_delete(hoisted__ForInData_3170, hoisted__Bool_3171);
    }
    Bool hoisted__Bool_3189 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3189;
    if (hoisted__Bool_3189) {
        Str *hoisted__Str_3172 = get_payload(self);
        (void)hoisted__Str_3172;
        (void)hoisted__Str_3172;
        Bool hoisted__Bool_3173 = 0;
        (void)hoisted__Bool_3173;
        Str_delete(hoisted__Str_3172, hoisted__Bool_3173);
    }
    Bool hoisted__Bool_3190 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3190;
    if (hoisted__Bool_3190) {
        MatchData *hoisted__MatchData_3174 = get_payload(self);
        (void)hoisted__MatchData_3174;
        (void)hoisted__MatchData_3174;
        Bool hoisted__Bool_3175 = 0;
        (void)hoisted__Bool_3175;
        MatchData_delete(hoisted__MatchData_3174, hoisted__Bool_3175);
    }
    Bool hoisted__Bool_3191 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3191;
    if (hoisted__Bool_3191) {
        CaptureBlockData *hoisted__CaptureBlockData_3176 = get_payload(self);
        (void)hoisted__CaptureBlockData_3176;
        (void)hoisted__CaptureBlockData_3176;
        Bool hoisted__Bool_3177 = 0;
        (void)hoisted__Bool_3177;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3176, hoisted__Bool_3177);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3415 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3415;
    if (hoisted__Bool_3415) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3416 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3387 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3387;
        NodeType *hoisted__NodeType_3388 = NodeType_Literal(hoisted__Literal_3387);
        (void)hoisted__NodeType_3388;
        { NodeType * _ret_val = hoisted__NodeType_3388;
                return _ret_val; }
    }
    Bool hoisted__Bool_3417 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3417;
    if (hoisted__Bool_3417) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3389 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3389;
        NodeType *hoisted__NodeType_3390 = NodeType_Ident(hoisted__IdentData_3389);
        (void)hoisted__NodeType_3390;
        { NodeType * _ret_val = hoisted__NodeType_3390;
                return _ret_val; }
    }
    Bool hoisted__Bool_3418 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3391 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3391;
        NodeType *hoisted__NodeType_3392 = NodeType_Decl(hoisted__Declaration_3391);
        (void)hoisted__NodeType_3392;
        { NodeType * _ret_val = hoisted__NodeType_3392;
                return _ret_val; }
    }
    Bool hoisted__Bool_3419 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3419;
    if (hoisted__Bool_3419) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3393 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3393;
        NodeType *hoisted__NodeType_3394 = NodeType_Assign(hoisted__AssignData_3393);
        (void)hoisted__NodeType_3394;
        { NodeType * _ret_val = hoisted__NodeType_3394;
                return _ret_val; }
    }
    Bool hoisted__Bool_3420 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3395 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3395;
        NodeType *hoisted__NodeType_3396 = NodeType_FCall(hoisted__FCallData_3395);
        (void)hoisted__NodeType_3396;
        { NodeType * _ret_val = hoisted__NodeType_3396;
                return _ret_val; }
    }
    Bool hoisted__Bool_3421 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3421;
    if (hoisted__Bool_3421) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3397 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3397;
        NodeType *hoisted__NodeType_3398 = NodeType_FuncDef(hoisted__FunctionDef_3397);
        (void)hoisted__NodeType_3398;
        { NodeType * _ret_val = hoisted__NodeType_3398;
                return _ret_val; }
    }
    Bool hoisted__Bool_3422 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3422;
    if (hoisted__Bool_3422) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3399 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3399;
        NodeType *hoisted__NodeType_3400 = NodeType_StructDef(hoisted__StructDef_3399);
        (void)hoisted__NodeType_3400;
        { NodeType * _ret_val = hoisted__NodeType_3400;
                return _ret_val; }
    }
    Bool hoisted__Bool_3423 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3423;
    if (hoisted__Bool_3423) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3401 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3401;
        NodeType *hoisted__NodeType_3402 = NodeType_EnumDef(hoisted__EnumDef_3401);
        (void)hoisted__NodeType_3402;
        { NodeType * _ret_val = hoisted__NodeType_3402;
                return _ret_val; }
    }
    Bool hoisted__Bool_3424 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3424;
    if (hoisted__Bool_3424) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3403 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3403;
        NodeType *hoisted__NodeType_3404 = NodeType_FieldAccess(hoisted__FieldAccessData_3403);
        (void)hoisted__NodeType_3404;
        { NodeType * _ret_val = hoisted__NodeType_3404;
                return _ret_val; }
    }
    Bool hoisted__Bool_3425 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3425;
    if (hoisted__Bool_3425) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3405 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3405;
        NodeType *hoisted__NodeType_3406 = NodeType_FieldAssign(hoisted__FieldAssignData_3405);
        (void)hoisted__NodeType_3406;
        { NodeType * _ret_val = hoisted__NodeType_3406;
                return _ret_val; }
    }
    Bool hoisted__Bool_3426 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3426;
    if (hoisted__Bool_3426) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3427 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3427;
    if (hoisted__Bool_3427) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3428 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3428;
    if (hoisted__Bool_3428) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3429 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3429;
    if (hoisted__Bool_3429) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3407 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3407;
        NodeType *hoisted__NodeType_3408 = NodeType_ForIn(hoisted__ForInData_3407);
        (void)hoisted__NodeType_3408;
        { NodeType * _ret_val = hoisted__NodeType_3408;
                return _ret_val; }
    }
    Bool hoisted__Bool_3430 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3430;
    if (hoisted__Bool_3430) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3409 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3409;
        NodeType *hoisted__NodeType_3410 = NodeType_NamedArg(hoisted__Str_3409);
        (void)hoisted__NodeType_3410;
        { NodeType * _ret_val = hoisted__NodeType_3410;
                return _ret_val; }
    }
    Bool hoisted__Bool_3431 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3431;
    if (hoisted__Bool_3431) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3432 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3432;
    if (hoisted__Bool_3432) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3433 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3433;
    if (hoisted__Bool_3433) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3434 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3434;
    if (hoisted__Bool_3434) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3411 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3411;
        NodeType *hoisted__NodeType_3412 = NodeType_Match(hoisted__MatchData_3411);
        (void)hoisted__NodeType_3412;
        { NodeType * _ret_val = hoisted__NodeType_3412;
                return _ret_val; }
    }
    Bool hoisted__Bool_3435 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3435;
    if (hoisted__Bool_3435) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3436 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3436;
    if (hoisted__Bool_3436) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3437 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3437;
    if (hoisted__Bool_3437) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3438 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3438;
    if (hoisted__Bool_3438) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3439 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3439;
    if (hoisted__Bool_3439) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3440 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3440;
    if (hoisted__Bool_3440) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3413 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3413;
        NodeType *hoisted__NodeType_3414 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3413);
        (void)hoisted__NodeType_3414;
        { NodeType * _ret_val = hoisted__NodeType_3414;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3441 = 120;
    (void)hoisted__U32_3441;
    return hoisted__U32_3441;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3442 = is_null(self);
    (void)hoisted__Bool_3442;
    if (hoisted__Bool_3442) {
        return;
    }
    Bool hoisted__Bool_3443 = 0;
    (void)hoisted__Bool_3443;
    NodeType_delete(&self->node_type, hoisted__Bool_3443);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3493 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3493->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3493->children = *_ca; free(_ca); }
    hoisted__Expr_3493->line = line;
    hoisted__Expr_3493->col = col;
    (void)hoisted__Expr_3493;
    return hoisted__Expr_3493;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3502 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3502->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3502->children = *_ca; free(_ca); }
    hoisted__Expr_3502->line = self->line;
    hoisted__Expr_3502->col = self->col;
    (void)hoisted__Expr_3502;
    return hoisted__Expr_3502;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3503 = 0;
    (void)hoisted__U32_3503;
    U64 hoisted__U64_3504 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3503); });
    (void)hoisted__U64_3504;
    return hoisted__U64_3504;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3505 = 144;
    (void)hoisted__U32_3505;
    return hoisted__U32_3505;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4449 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4449->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4449->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4449;
    return hoisted__Map__I64_Str_4449;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4562 = 0;
    (void)hoisted__Bool_4562;
    Vec__I64_delete(&self->keys, hoisted__Bool_4562);
    Bool hoisted__Bool_4563 = 0;
    (void)hoisted__Bool_4563;
    Vec__Str_delete(&self->values, hoisted__Bool_4563);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4564 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4564->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4564->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4564;
    return hoisted__Map__I64_Str_4564;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4565 = 0;
    (void)hoisted__U32_4565;
    U64 hoisted__U64_4566 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4565); });
    (void)hoisted__U64_4566;
    return hoisted__U64_4566;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4567 = 32;
    (void)hoisted__U32_4567;
    return hoisted__U32_4567;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4568 = 1;
    (void)hoisted__U32_4568;
    U64 hoisted__U64_4569 = (U64)(hoisted__U32_4568);
    (void)hoisted__U64_4569;
    void * hoisted__v_4570 = malloc(hoisted__U64_4569);
    (void)hoisted__v_4570;
    U32 hoisted__U32_4571 = 0;
    (void)hoisted__U32_4571;
    I64 hoisted__I64_4572 = 1;
    (void)hoisted__I64_4572;
    Vec__Bool *hoisted__Vec__Bool_4573 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4573->data = hoisted__v_4570;
    hoisted__Vec__Bool_4573->count = hoisted__U32_4571;
    hoisted__Vec__Bool_4573->cap = hoisted__I64_4572;
    (void)hoisted__Vec__Bool_4573;
    return hoisted__Vec__Bool_4573;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4583 = self->count;
        (void)_re_U32_4583;
        U32 _rc_U32_4583 = 0;
        (void)_rc_U32_4583;
        Bool hoisted__Bool_4596 = U32_lte(_rc_U32_4583, _re_U32_4583);
        (void)hoisted__Bool_4596;
        if (hoisted__Bool_4596) {
            while (1) {
                Bool _wcond_Bool_4584 = U32_lt(_rc_U32_4583, _re_U32_4583);
                (void)_wcond_Bool_4584;
                if (_wcond_Bool_4584) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4583);
                U32_inc(&_rc_U32_4583);
                U32 hoisted__U32_4585 = 1;
                (void)hoisted__U32_4585;
                U32 hoisted__U32_4586 = ((U32)(i * hoisted__U32_4585));
                (void)hoisted__U32_4586;
                U64 hoisted__U64_4587 = (U64)(hoisted__U32_4586);
                (void)hoisted__U64_4587;
                Bool *hoisted__Bool_4588 = ptr_add(self->data, hoisted__U64_4587);
                (void)hoisted__Bool_4588;
                (void)hoisted__Bool_4588;
                Bool hoisted__Bool_4589 = 0;
                (void)hoisted__Bool_4589;
                Bool_delete(hoisted__Bool_4588, hoisted__Bool_4589);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4590 = U32_gt(_rc_U32_4583, _re_U32_4583);
                (void)_wcond_Bool_4590;
                if (_wcond_Bool_4590) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4583);
                U32_dec(&_rc_U32_4583);
                U32 hoisted__U32_4591 = 1;
                (void)hoisted__U32_4591;
                U32 hoisted__U32_4592 = ((U32)(i * hoisted__U32_4591));
                (void)hoisted__U32_4592;
                U64 hoisted__U64_4593 = (U64)(hoisted__U32_4592);
                (void)hoisted__U64_4593;
                Bool *hoisted__Bool_4594 = ptr_add(self->data, hoisted__U64_4593);
                (void)hoisted__Bool_4594;
                (void)hoisted__Bool_4594;
                Bool hoisted__Bool_4595 = 0;
                (void)hoisted__Bool_4595;
                Bool_delete(hoisted__Bool_4594, hoisted__Bool_4595);
            }
        }
    }
    U32 hoisted__U32_4597 = 0;
    (void)hoisted__U32_4597;
    self->count = hoisted__U32_4597;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4867 = 1;
    (void)hoisted__U32_4867;
    U32 hoisted__U32_4868 = ((U32)(self->cap * hoisted__U32_4867));
    (void)hoisted__U32_4868;
    U64 hoisted__U64_4869 = (U64)(hoisted__U32_4868);
    (void)hoisted__U64_4869;
    void * new_data = malloc(hoisted__U64_4869);
    {
        U32 _re_U32_4839 = self->count;
        (void)_re_U32_4839;
        U32 _rc_U32_4839 = 0;
        (void)_rc_U32_4839;
        Bool hoisted__Bool_4866 = U32_lte(_rc_U32_4839, _re_U32_4839);
        (void)hoisted__Bool_4866;
        if (hoisted__Bool_4866) {
            while (1) {
                Bool _wcond_Bool_4840 = U32_lt(_rc_U32_4839, _re_U32_4839);
                (void)_wcond_Bool_4840;
                if (_wcond_Bool_4840) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4839);
                U32_inc(&_rc_U32_4839);
                U32 hoisted__U32_4841 = 1;
                (void)hoisted__U32_4841;
                U32 hoisted__U32_4842 = ((U32)(i * hoisted__U32_4841));
                (void)hoisted__U32_4842;
                U64 hoisted__U64_4843 = (U64)(hoisted__U32_4842);
                (void)hoisted__U64_4843;
                Bool *src = ptr_add(self->data, hoisted__U64_4843);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4844 = 1;
                (void)hoisted__U32_4844;
                U32 hoisted__U32_4845 = ((U32)(i * hoisted__U32_4844));
                (void)hoisted__U32_4845;
                U64 hoisted__U64_4846 = (U64)(hoisted__U32_4845);
                (void)hoisted__U64_4846;
                U32 hoisted__U32_4847 = 1;
                (void)hoisted__U32_4847;
                void *hoisted__v_4848 = ptr_add(new_data, hoisted__U64_4846);
                (void)hoisted__v_4848;
                (void)hoisted__v_4848;
                U64 hoisted__U64_4849 = (U64)(hoisted__U32_4847);
                (void)hoisted__U64_4849;
                memcpy(hoisted__v_4848, &cloned, hoisted__U64_4849);
                U32 hoisted__U32_4850 = 1;
                (void)hoisted__U32_4850;
                I32 hoisted__I32_4851 = 0;
                (void)hoisted__I32_4851;
                U64 hoisted__U64_4852 = (U64)(hoisted__U32_4850);
                (void)hoisted__U64_4852;
                memset(&cloned, hoisted__I32_4851, hoisted__U64_4852);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4853 = U32_gt(_rc_U32_4839, _re_U32_4839);
                (void)_wcond_Bool_4853;
                if (_wcond_Bool_4853) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4839);
                U32_dec(&_rc_U32_4839);
                U32 hoisted__U32_4854 = 1;
                (void)hoisted__U32_4854;
                U32 hoisted__U32_4855 = ((U32)(i * hoisted__U32_4854));
                (void)hoisted__U32_4855;
                U64 hoisted__U64_4856 = (U64)(hoisted__U32_4855);
                (void)hoisted__U64_4856;
                Bool *src = ptr_add(self->data, hoisted__U64_4856);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4857 = 1;
                (void)hoisted__U32_4857;
                U32 hoisted__U32_4858 = ((U32)(i * hoisted__U32_4857));
                (void)hoisted__U32_4858;
                U64 hoisted__U64_4859 = (U64)(hoisted__U32_4858);
                (void)hoisted__U64_4859;
                U32 hoisted__U32_4860 = 1;
                (void)hoisted__U32_4860;
                void *hoisted__v_4861 = ptr_add(new_data, hoisted__U64_4859);
                (void)hoisted__v_4861;
                (void)hoisted__v_4861;
                U64 hoisted__U64_4862 = (U64)(hoisted__U32_4860);
                (void)hoisted__U64_4862;
                memcpy(hoisted__v_4861, &cloned, hoisted__U64_4862);
                U32 hoisted__U32_4863 = 1;
                (void)hoisted__U32_4863;
                I32 hoisted__I32_4864 = 0;
                (void)hoisted__I32_4864;
                U64 hoisted__U64_4865 = (U64)(hoisted__U32_4863);
                (void)hoisted__U64_4865;
                memset(&cloned, hoisted__I32_4864, hoisted__U64_4865);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4870 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4870->data = new_data;
    hoisted__Vec__Bool_4870->count = self->count;
    hoisted__Vec__Bool_4870->cap = self->cap;
    (void)hoisted__Vec__Bool_4870;
    return hoisted__Vec__Bool_4870;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4871 = 16;
    (void)hoisted__U32_4871;
    return hoisted__U32_4871;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5176 = 104;
    (void)hoisted__U32_5176;
    U64 hoisted__U64_5177 = (U64)(hoisted__U32_5176);
    (void)hoisted__U64_5177;
    void * hoisted__v_5178 = malloc(hoisted__U64_5177);
    (void)hoisted__v_5178;
    U32 hoisted__U32_5179 = 0;
    (void)hoisted__U32_5179;
    I64 hoisted__I64_5180 = 1;
    (void)hoisted__I64_5180;
    Vec__Declaration *hoisted__Vec__Declaration_5181 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5181->data = hoisted__v_5178;
    hoisted__Vec__Declaration_5181->count = hoisted__U32_5179;
    hoisted__Vec__Declaration_5181->cap = hoisted__I64_5180;
    (void)hoisted__Vec__Declaration_5181;
    return hoisted__Vec__Declaration_5181;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5191 = self->count;
        (void)_re_U32_5191;
        U32 _rc_U32_5191 = 0;
        (void)_rc_U32_5191;
        Bool hoisted__Bool_5204 = U32_lte(_rc_U32_5191, _re_U32_5191);
        (void)hoisted__Bool_5204;
        if (hoisted__Bool_5204) {
            while (1) {
                Bool _wcond_Bool_5192 = U32_lt(_rc_U32_5191, _re_U32_5191);
                (void)_wcond_Bool_5192;
                if (_wcond_Bool_5192) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5191);
                U32_inc(&_rc_U32_5191);
                U32 hoisted__U32_5193 = 104;
                (void)hoisted__U32_5193;
                U32 hoisted__U32_5194 = ((U32)(i * hoisted__U32_5193));
                (void)hoisted__U32_5194;
                U64 hoisted__U64_5195 = (U64)(hoisted__U32_5194);
                (void)hoisted__U64_5195;
                Declaration *hoisted__Declaration_5196 = ptr_add(self->data, hoisted__U64_5195);
                (void)hoisted__Declaration_5196;
                (void)hoisted__Declaration_5196;
                Bool hoisted__Bool_5197 = 0;
                (void)hoisted__Bool_5197;
                Declaration_delete(hoisted__Declaration_5196, hoisted__Bool_5197);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5198 = U32_gt(_rc_U32_5191, _re_U32_5191);
                (void)_wcond_Bool_5198;
                if (_wcond_Bool_5198) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5191);
                U32_dec(&_rc_U32_5191);
                U32 hoisted__U32_5199 = 104;
                (void)hoisted__U32_5199;
                U32 hoisted__U32_5200 = ((U32)(i * hoisted__U32_5199));
                (void)hoisted__U32_5200;
                U64 hoisted__U64_5201 = (U64)(hoisted__U32_5200);
                (void)hoisted__U64_5201;
                Declaration *hoisted__Declaration_5202 = ptr_add(self->data, hoisted__U64_5201);
                (void)hoisted__Declaration_5202;
                (void)hoisted__Declaration_5202;
                Bool hoisted__Bool_5203 = 0;
                (void)hoisted__Bool_5203;
                Declaration_delete(hoisted__Declaration_5202, hoisted__Bool_5203);
            }
        }
    }
    U32 hoisted__U32_5205 = 0;
    (void)hoisted__U32_5205;
    self->count = hoisted__U32_5205;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5475 = 104;
    (void)hoisted__U32_5475;
    U32 hoisted__U32_5476 = ((U32)(self->cap * hoisted__U32_5475));
    (void)hoisted__U32_5476;
    U64 hoisted__U64_5477 = (U64)(hoisted__U32_5476);
    (void)hoisted__U64_5477;
    void * new_data = malloc(hoisted__U64_5477);
    {
        U32 _re_U32_5447 = self->count;
        (void)_re_U32_5447;
        U32 _rc_U32_5447 = 0;
        (void)_rc_U32_5447;
        Bool hoisted__Bool_5474 = U32_lte(_rc_U32_5447, _re_U32_5447);
        (void)hoisted__Bool_5474;
        if (hoisted__Bool_5474) {
            while (1) {
                Bool _wcond_Bool_5448 = U32_lt(_rc_U32_5447, _re_U32_5447);
                (void)_wcond_Bool_5448;
                if (_wcond_Bool_5448) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5447);
                U32_inc(&_rc_U32_5447);
                U32 hoisted__U32_5449 = 104;
                (void)hoisted__U32_5449;
                U32 hoisted__U32_5450 = ((U32)(i * hoisted__U32_5449));
                (void)hoisted__U32_5450;
                U64 hoisted__U64_5451 = (U64)(hoisted__U32_5450);
                (void)hoisted__U64_5451;
                Declaration *src = ptr_add(self->data, hoisted__U64_5451);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5452 = 104;
                (void)hoisted__U32_5452;
                U32 hoisted__U32_5453 = ((U32)(i * hoisted__U32_5452));
                (void)hoisted__U32_5453;
                U64 hoisted__U64_5454 = (U64)(hoisted__U32_5453);
                (void)hoisted__U64_5454;
                U32 hoisted__U32_5455 = 104;
                (void)hoisted__U32_5455;
                void *hoisted__v_5456 = ptr_add(new_data, hoisted__U64_5454);
                (void)hoisted__v_5456;
                (void)hoisted__v_5456;
                U64 hoisted__U64_5457 = (U64)(hoisted__U32_5455);
                (void)hoisted__U64_5457;
                memcpy(hoisted__v_5456, cloned, hoisted__U64_5457);
                U32 hoisted__U32_5458 = 104;
                (void)hoisted__U32_5458;
                I32 hoisted__I32_5459 = 0;
                (void)hoisted__I32_5459;
                U64 hoisted__U64_5460 = (U64)(hoisted__U32_5458);
                (void)hoisted__U64_5460;
                memset(cloned, hoisted__I32_5459, hoisted__U64_5460);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5461 = U32_gt(_rc_U32_5447, _re_U32_5447);
                (void)_wcond_Bool_5461;
                if (_wcond_Bool_5461) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5447);
                U32_dec(&_rc_U32_5447);
                U32 hoisted__U32_5462 = 104;
                (void)hoisted__U32_5462;
                U32 hoisted__U32_5463 = ((U32)(i * hoisted__U32_5462));
                (void)hoisted__U32_5463;
                U64 hoisted__U64_5464 = (U64)(hoisted__U32_5463);
                (void)hoisted__U64_5464;
                Declaration *src = ptr_add(self->data, hoisted__U64_5464);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5465 = 104;
                (void)hoisted__U32_5465;
                U32 hoisted__U32_5466 = ((U32)(i * hoisted__U32_5465));
                (void)hoisted__U32_5466;
                U64 hoisted__U64_5467 = (U64)(hoisted__U32_5466);
                (void)hoisted__U64_5467;
                U32 hoisted__U32_5468 = 104;
                (void)hoisted__U32_5468;
                void *hoisted__v_5469 = ptr_add(new_data, hoisted__U64_5467);
                (void)hoisted__v_5469;
                (void)hoisted__v_5469;
                U64 hoisted__U64_5470 = (U64)(hoisted__U32_5468);
                (void)hoisted__U64_5470;
                memcpy(hoisted__v_5469, cloned, hoisted__U64_5470);
                U32 hoisted__U32_5471 = 104;
                (void)hoisted__U32_5471;
                I32 hoisted__I32_5472 = 0;
                (void)hoisted__I32_5472;
                U64 hoisted__U64_5473 = (U64)(hoisted__U32_5471);
                (void)hoisted__U64_5473;
                memset(cloned, hoisted__I32_5472, hoisted__U64_5473);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5478 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5478->data = new_data;
    hoisted__Vec__Declaration_5478->count = self->count;
    hoisted__Vec__Declaration_5478->cap = self->cap;
    (void)hoisted__Vec__Declaration_5478;
    return hoisted__Vec__Declaration_5478;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5479 = 16;
    (void)hoisted__U32_5479;
    return hoisted__U32_5479;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5480 = 144;
    (void)hoisted__U32_5480;
    U64 hoisted__U64_5481 = (U64)(hoisted__U32_5480);
    (void)hoisted__U64_5481;
    void * hoisted__v_5482 = malloc(hoisted__U64_5481);
    (void)hoisted__v_5482;
    U32 hoisted__U32_5483 = 0;
    (void)hoisted__U32_5483;
    I64 hoisted__I64_5484 = 1;
    (void)hoisted__I64_5484;
    Vec__Expr *hoisted__Vec__Expr_5485 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5485->data = hoisted__v_5482;
    hoisted__Vec__Expr_5485->count = hoisted__U32_5483;
    hoisted__Vec__Expr_5485->cap = hoisted__I64_5484;
    (void)hoisted__Vec__Expr_5485;
    return hoisted__Vec__Expr_5485;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5495 = self->count;
        (void)_re_U32_5495;
        U32 _rc_U32_5495 = 0;
        (void)_rc_U32_5495;
        Bool hoisted__Bool_5508 = U32_lte(_rc_U32_5495, _re_U32_5495);
        (void)hoisted__Bool_5508;
        if (hoisted__Bool_5508) {
            while (1) {
                Bool _wcond_Bool_5496 = U32_lt(_rc_U32_5495, _re_U32_5495);
                (void)_wcond_Bool_5496;
                if (_wcond_Bool_5496) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5495);
                U32_inc(&_rc_U32_5495);
                U32 hoisted__U32_5497 = 144;
                (void)hoisted__U32_5497;
                U32 hoisted__U32_5498 = ((U32)(i * hoisted__U32_5497));
                (void)hoisted__U32_5498;
                U64 hoisted__U64_5499 = (U64)(hoisted__U32_5498);
                (void)hoisted__U64_5499;
                Expr *hoisted__Expr_5500 = ptr_add(self->data, hoisted__U64_5499);
                (void)hoisted__Expr_5500;
                (void)hoisted__Expr_5500;
                Bool hoisted__Bool_5501 = 0;
                (void)hoisted__Bool_5501;
                Expr_delete(hoisted__Expr_5500, hoisted__Bool_5501);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5502 = U32_gt(_rc_U32_5495, _re_U32_5495);
                (void)_wcond_Bool_5502;
                if (_wcond_Bool_5502) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5495);
                U32_dec(&_rc_U32_5495);
                U32 hoisted__U32_5503 = 144;
                (void)hoisted__U32_5503;
                U32 hoisted__U32_5504 = ((U32)(i * hoisted__U32_5503));
                (void)hoisted__U32_5504;
                U64 hoisted__U64_5505 = (U64)(hoisted__U32_5504);
                (void)hoisted__U64_5505;
                Expr *hoisted__Expr_5506 = ptr_add(self->data, hoisted__U64_5505);
                (void)hoisted__Expr_5506;
                (void)hoisted__Expr_5506;
                Bool hoisted__Bool_5507 = 0;
                (void)hoisted__Bool_5507;
                Expr_delete(hoisted__Expr_5506, hoisted__Bool_5507);
            }
        }
    }
    U32 hoisted__U32_5509 = 0;
    (void)hoisted__U32_5509;
    self->count = hoisted__U32_5509;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5779 = 144;
    (void)hoisted__U32_5779;
    U32 hoisted__U32_5780 = ((U32)(self->cap * hoisted__U32_5779));
    (void)hoisted__U32_5780;
    U64 hoisted__U64_5781 = (U64)(hoisted__U32_5780);
    (void)hoisted__U64_5781;
    void * new_data = malloc(hoisted__U64_5781);
    {
        U32 _re_U32_5751 = self->count;
        (void)_re_U32_5751;
        U32 _rc_U32_5751 = 0;
        (void)_rc_U32_5751;
        Bool hoisted__Bool_5778 = U32_lte(_rc_U32_5751, _re_U32_5751);
        (void)hoisted__Bool_5778;
        if (hoisted__Bool_5778) {
            while (1) {
                Bool _wcond_Bool_5752 = U32_lt(_rc_U32_5751, _re_U32_5751);
                (void)_wcond_Bool_5752;
                if (_wcond_Bool_5752) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5751);
                U32_inc(&_rc_U32_5751);
                U32 hoisted__U32_5753 = 144;
                (void)hoisted__U32_5753;
                U32 hoisted__U32_5754 = ((U32)(i * hoisted__U32_5753));
                (void)hoisted__U32_5754;
                U64 hoisted__U64_5755 = (U64)(hoisted__U32_5754);
                (void)hoisted__U64_5755;
                Expr *src = ptr_add(self->data, hoisted__U64_5755);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5756 = 144;
                (void)hoisted__U32_5756;
                U32 hoisted__U32_5757 = ((U32)(i * hoisted__U32_5756));
                (void)hoisted__U32_5757;
                U64 hoisted__U64_5758 = (U64)(hoisted__U32_5757);
                (void)hoisted__U64_5758;
                U32 hoisted__U32_5759 = 144;
                (void)hoisted__U32_5759;
                void *hoisted__v_5760 = ptr_add(new_data, hoisted__U64_5758);
                (void)hoisted__v_5760;
                (void)hoisted__v_5760;
                U64 hoisted__U64_5761 = (U64)(hoisted__U32_5759);
                (void)hoisted__U64_5761;
                memcpy(hoisted__v_5760, cloned, hoisted__U64_5761);
                U32 hoisted__U32_5762 = 144;
                (void)hoisted__U32_5762;
                I32 hoisted__I32_5763 = 0;
                (void)hoisted__I32_5763;
                U64 hoisted__U64_5764 = (U64)(hoisted__U32_5762);
                (void)hoisted__U64_5764;
                memset(cloned, hoisted__I32_5763, hoisted__U64_5764);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5765 = U32_gt(_rc_U32_5751, _re_U32_5751);
                (void)_wcond_Bool_5765;
                if (_wcond_Bool_5765) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5751);
                U32_dec(&_rc_U32_5751);
                U32 hoisted__U32_5766 = 144;
                (void)hoisted__U32_5766;
                U32 hoisted__U32_5767 = ((U32)(i * hoisted__U32_5766));
                (void)hoisted__U32_5767;
                U64 hoisted__U64_5768 = (U64)(hoisted__U32_5767);
                (void)hoisted__U64_5768;
                Expr *src = ptr_add(self->data, hoisted__U64_5768);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5769 = 144;
                (void)hoisted__U32_5769;
                U32 hoisted__U32_5770 = ((U32)(i * hoisted__U32_5769));
                (void)hoisted__U32_5770;
                U64 hoisted__U64_5771 = (U64)(hoisted__U32_5770);
                (void)hoisted__U64_5771;
                U32 hoisted__U32_5772 = 144;
                (void)hoisted__U32_5772;
                void *hoisted__v_5773 = ptr_add(new_data, hoisted__U64_5771);
                (void)hoisted__v_5773;
                (void)hoisted__v_5773;
                U64 hoisted__U64_5774 = (U64)(hoisted__U32_5772);
                (void)hoisted__U64_5774;
                memcpy(hoisted__v_5773, cloned, hoisted__U64_5774);
                U32 hoisted__U32_5775 = 144;
                (void)hoisted__U32_5775;
                I32 hoisted__I32_5776 = 0;
                (void)hoisted__I32_5776;
                U64 hoisted__U64_5777 = (U64)(hoisted__U32_5775);
                (void)hoisted__U64_5777;
                memset(cloned, hoisted__I32_5776, hoisted__U64_5777);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5782 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5782->data = new_data;
    hoisted__Vec__Expr_5782->count = self->count;
    hoisted__Vec__Expr_5782->cap = self->cap;
    (void)hoisted__Vec__Expr_5782;
    return hoisted__Vec__Expr_5782;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5783 = 16;
    (void)hoisted__U32_5783;
    return hoisted__U32_5783;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5784 = 8;
    (void)hoisted__U32_5784;
    U64 hoisted__U64_5785 = (U64)(hoisted__U32_5784);
    (void)hoisted__U64_5785;
    void * hoisted__v_5786 = malloc(hoisted__U64_5785);
    (void)hoisted__v_5786;
    U32 hoisted__U32_5787 = 0;
    (void)hoisted__U32_5787;
    I64 hoisted__I64_5788 = 1;
    (void)hoisted__I64_5788;
    Vec__I64 *hoisted__Vec__I64_5789 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5789->data = hoisted__v_5786;
    hoisted__Vec__I64_5789->count = hoisted__U32_5787;
    hoisted__Vec__I64_5789->cap = hoisted__I64_5788;
    (void)hoisted__Vec__I64_5789;
    return hoisted__Vec__I64_5789;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5799 = self->count;
        (void)_re_U32_5799;
        U32 _rc_U32_5799 = 0;
        (void)_rc_U32_5799;
        Bool hoisted__Bool_5812 = U32_lte(_rc_U32_5799, _re_U32_5799);
        (void)hoisted__Bool_5812;
        if (hoisted__Bool_5812) {
            while (1) {
                Bool _wcond_Bool_5800 = U32_lt(_rc_U32_5799, _re_U32_5799);
                (void)_wcond_Bool_5800;
                if (_wcond_Bool_5800) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5799);
                U32_inc(&_rc_U32_5799);
                U32 hoisted__U32_5801 = 8;
                (void)hoisted__U32_5801;
                U32 hoisted__U32_5802 = ((U32)(i * hoisted__U32_5801));
                (void)hoisted__U32_5802;
                U64 hoisted__U64_5803 = (U64)(hoisted__U32_5802);
                (void)hoisted__U64_5803;
                I64 *hoisted__I64_5804 = ptr_add(self->data, hoisted__U64_5803);
                (void)hoisted__I64_5804;
                (void)hoisted__I64_5804;
                Bool hoisted__Bool_5805 = 0;
                (void)hoisted__Bool_5805;
                I64_delete(hoisted__I64_5804, hoisted__Bool_5805);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5806 = U32_gt(_rc_U32_5799, _re_U32_5799);
                (void)_wcond_Bool_5806;
                if (_wcond_Bool_5806) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5799);
                U32_dec(&_rc_U32_5799);
                U32 hoisted__U32_5807 = 8;
                (void)hoisted__U32_5807;
                U32 hoisted__U32_5808 = ((U32)(i * hoisted__U32_5807));
                (void)hoisted__U32_5808;
                U64 hoisted__U64_5809 = (U64)(hoisted__U32_5808);
                (void)hoisted__U64_5809;
                I64 *hoisted__I64_5810 = ptr_add(self->data, hoisted__U64_5809);
                (void)hoisted__I64_5810;
                (void)hoisted__I64_5810;
                Bool hoisted__Bool_5811 = 0;
                (void)hoisted__Bool_5811;
                I64_delete(hoisted__I64_5810, hoisted__Bool_5811);
            }
        }
    }
    U32 hoisted__U32_5813 = 0;
    (void)hoisted__U32_5813;
    self->count = hoisted__U32_5813;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_6083 = 8;
    (void)hoisted__U32_6083;
    U32 hoisted__U32_6084 = ((U32)(self->cap * hoisted__U32_6083));
    (void)hoisted__U32_6084;
    U64 hoisted__U64_6085 = (U64)(hoisted__U32_6084);
    (void)hoisted__U64_6085;
    void * new_data = malloc(hoisted__U64_6085);
    {
        U32 _re_U32_6055 = self->count;
        (void)_re_U32_6055;
        U32 _rc_U32_6055 = 0;
        (void)_rc_U32_6055;
        Bool hoisted__Bool_6082 = U32_lte(_rc_U32_6055, _re_U32_6055);
        (void)hoisted__Bool_6082;
        if (hoisted__Bool_6082) {
            while (1) {
                Bool _wcond_Bool_6056 = U32_lt(_rc_U32_6055, _re_U32_6055);
                (void)_wcond_Bool_6056;
                if (_wcond_Bool_6056) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6055);
                U32_inc(&_rc_U32_6055);
                U32 hoisted__U32_6057 = 8;
                (void)hoisted__U32_6057;
                U32 hoisted__U32_6058 = ((U32)(i * hoisted__U32_6057));
                (void)hoisted__U32_6058;
                U64 hoisted__U64_6059 = (U64)(hoisted__U32_6058);
                (void)hoisted__U64_6059;
                I64 *src = ptr_add(self->data, hoisted__U64_6059);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6060 = 8;
                (void)hoisted__U32_6060;
                U32 hoisted__U32_6061 = ((U32)(i * hoisted__U32_6060));
                (void)hoisted__U32_6061;
                U64 hoisted__U64_6062 = (U64)(hoisted__U32_6061);
                (void)hoisted__U64_6062;
                U32 hoisted__U32_6063 = 8;
                (void)hoisted__U32_6063;
                void *hoisted__v_6064 = ptr_add(new_data, hoisted__U64_6062);
                (void)hoisted__v_6064;
                (void)hoisted__v_6064;
                U64 hoisted__U64_6065 = (U64)(hoisted__U32_6063);
                (void)hoisted__U64_6065;
                memcpy(hoisted__v_6064, &cloned, hoisted__U64_6065);
                U32 hoisted__U32_6066 = 8;
                (void)hoisted__U32_6066;
                I32 hoisted__I32_6067 = 0;
                (void)hoisted__I32_6067;
                U64 hoisted__U64_6068 = (U64)(hoisted__U32_6066);
                (void)hoisted__U64_6068;
                memset(&cloned, hoisted__I32_6067, hoisted__U64_6068);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6069 = U32_gt(_rc_U32_6055, _re_U32_6055);
                (void)_wcond_Bool_6069;
                if (_wcond_Bool_6069) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6055);
                U32_dec(&_rc_U32_6055);
                U32 hoisted__U32_6070 = 8;
                (void)hoisted__U32_6070;
                U32 hoisted__U32_6071 = ((U32)(i * hoisted__U32_6070));
                (void)hoisted__U32_6071;
                U64 hoisted__U64_6072 = (U64)(hoisted__U32_6071);
                (void)hoisted__U64_6072;
                I64 *src = ptr_add(self->data, hoisted__U64_6072);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6073 = 8;
                (void)hoisted__U32_6073;
                U32 hoisted__U32_6074 = ((U32)(i * hoisted__U32_6073));
                (void)hoisted__U32_6074;
                U64 hoisted__U64_6075 = (U64)(hoisted__U32_6074);
                (void)hoisted__U64_6075;
                U32 hoisted__U32_6076 = 8;
                (void)hoisted__U32_6076;
                void *hoisted__v_6077 = ptr_add(new_data, hoisted__U64_6075);
                (void)hoisted__v_6077;
                (void)hoisted__v_6077;
                U64 hoisted__U64_6078 = (U64)(hoisted__U32_6076);
                (void)hoisted__U64_6078;
                memcpy(hoisted__v_6077, &cloned, hoisted__U64_6078);
                U32 hoisted__U32_6079 = 8;
                (void)hoisted__U32_6079;
                I32 hoisted__I32_6080 = 0;
                (void)hoisted__I32_6080;
                U64 hoisted__U64_6081 = (U64)(hoisted__U32_6079);
                (void)hoisted__U64_6081;
                memset(&cloned, hoisted__I32_6080, hoisted__U64_6081);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6086 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6086->data = new_data;
    hoisted__Vec__I64_6086->count = self->count;
    hoisted__Vec__I64_6086->cap = self->cap;
    (void)hoisted__Vec__I64_6086;
    return hoisted__Vec__I64_6086;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_6087 = 16;
    (void)hoisted__U32_6087;
    return hoisted__U32_6087;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7206 = 3;
    (void)hoisted__U32_7206;
    Array__Str *_va_Array_201 = Array__Str_new(hoisted__U32_7206);
    (void)_va_Array_201;
    I64 _va_Array_201_ek = 0;
    (void)_va_Array_201_ek;
    OutOfBounds *_va_Array_201_eo = malloc(sizeof(OutOfBounds));
    _va_Array_201_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_201_eo;
    U32 hoisted__U32_7207 = 0;
    (void)hoisted__U32_7207;
    Str *hoisted__Str_7208 = Str_clone(loc);
    (void)hoisted__Str_7208;
    (void)hoisted__Str_7209;
    (void)hoisted__Str_7209;
    Array__Str_set(_va_Array_201, hoisted__U32_7207, hoisted__Str_7208, &_va_Array_201_ek, _va_Array_201_eo, &hoisted__Str_7209);
    Str_delete(&hoisted__Str_7209, (Bool){0});
    U32 hoisted__U32_7210 = 1;
    (void)hoisted__U32_7210;
    (void)hoisted__Str_7211;
    (void)hoisted__Str_7211;
    (void)hoisted__Str_7212;
    (void)hoisted__Str_7212;
    Array__Str_set(_va_Array_201, hoisted__U32_7210, &hoisted__Str_7211, &_va_Array_201_ek, _va_Array_201_eo, &hoisted__Str_7212);
    Str_delete(&hoisted__Str_7212, (Bool){0});
    Array__Str *hoisted__Array__Str_7213 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7213;
    U32 hoisted__U32_7214 = 2;
    (void)hoisted__U32_7214;
    Str *hoisted__Str_7215 = format(hoisted__Array__Str_7213);
    (void)hoisted__Str_7215;
    (void)hoisted__Str_7216;
    (void)hoisted__Str_7216;
    Array__Str_set(_va_Array_201, hoisted__U32_7214, hoisted__Str_7215, &_va_Array_201_ek, _va_Array_201_eo, &hoisted__Str_7216);
    OutOfBounds_delete(_va_Array_201_eo, 1);
    Str_delete(&hoisted__Str_7216, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_201);
    I64 hoisted__I64_7217 = 1;
    (void)hoisted__I64_7217;
    exit(hoisted__I64_7217);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7226 = 1;
    (void)hoisted__U32_7226;
    Array__Str *_va_Array_203 = Array__Str_new(hoisted__U32_7226);
    (void)_va_Array_203;
    I64 _va_Array_203_ek = 0;
    (void)_va_Array_203_ek;
    OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
    _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_203_eo;
    U32 hoisted__U32_7227 = 0;
    (void)hoisted__U32_7227;
    (void)hoisted__Str_7228;
    (void)hoisted__Str_7228;
    (void)hoisted__Str_7229;
    (void)hoisted__Str_7229;
    Array__Str_set(_va_Array_203, hoisted__U32_7227, &hoisted__Str_7228, &_va_Array_203_ek, _va_Array_203_eo, &hoisted__Str_7229);
    OutOfBounds_delete(_va_Array_203_eo, 1);
    Str_delete(&hoisted__Str_7229, (Bool){0});
    panic(_va_Array_203, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7234 = not(cond);
    (void)hoisted__Bool_7234;
    if (hoisted__Bool_7234) {
        U32 hoisted__U32_7230 = 1;
        (void)hoisted__U32_7230;
        Array__Str *_va_Array_204 = Array__Str_new(hoisted__U32_7230);
        (void)_va_Array_204;
        I64 _va_Array_204_ek = 0;
        (void)_va_Array_204_ek;
        OutOfBounds *_va_Array_204_eo = malloc(sizeof(OutOfBounds));
        _va_Array_204_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_204_eo;
        U32 hoisted__U32_7231 = 0;
        (void)hoisted__U32_7231;
        (void)hoisted__Str_7232;
        (void)hoisted__Str_7232;
        (void)hoisted__Str_7233;
        (void)hoisted__Str_7233;
        Array__Str_set(_va_Array_204, hoisted__U32_7231, &hoisted__Str_7232, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7233);
        OutOfBounds_delete(_va_Array_204_eo, 1);
        Str_delete(&hoisted__Str_7233, (Bool){0});
        panic(_va_Array_204, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7244 = parts;
        (void)_fc_Array__Str_7244;
        (void)_fc_Array__Str_7244;
        U32 _fi_USize_7244 = 0;
        (void)_fi_USize_7244;
        while (1) {
            U32 hoisted__U32_7246 = Array__Str_len(_fc_Array__Str_7244);
            (void)hoisted__U32_7246;
            Bool _wcond_Bool_7245 = U32_lt(_fi_USize_7244, hoisted__U32_7246);
            (void)_wcond_Bool_7245;
            if (_wcond_Bool_7245) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7244, &_fi_USize_7244);
            U32 hoisted__U32_7247 = 1;
            (void)hoisted__U32_7247;
            U32 hoisted__U32_7248 = ((U32)(_fi_USize_7244 + hoisted__U32_7247));
            (void)hoisted__U32_7248;
            _fi_USize_7244 = hoisted__U32_7248;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7282 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7282;
    return hoisted__Bool_7282;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7291 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7291;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7291;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7292 = 0;
    (void)hoisted__U32_7292;
    U64 hoisted__U64_7293 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7292); });
    (void)hoisted__U64_7293;
    return hoisted__U64_7293;
}

U32 Range_size(void) {
    U32 hoisted__U32_7324 = 16;
    (void)hoisted__U32_7324;
    return hoisted__U32_7324;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7453 = 3;
    (void)hoisted__I64_7453;
    (void)hoisted__Str_7454;
    (void)hoisted__Str_7454;
    assert_eq__I64(result, hoisted__I64_7453, &hoisted__Str_7454);
    Str_delete(&hoisted__Str_7454, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7461 = 15;
    (void)hoisted__I64_7461;
    (void)hoisted__Str_7462;
    (void)hoisted__Str_7462;
    assert_eq__I64(result, hoisted__I64_7461, &hoisted__Str_7462);
    Str_delete(&hoisted__Str_7462, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7469 = 26;
    (void)hoisted__I64_7469;
    (void)hoisted__Str_7470;
    (void)hoisted__Str_7470;
    assert_eq__I64(result, hoisted__I64_7469, &hoisted__Str_7470);
    Str_delete(&hoisted__Str_7470, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7473;
    (void)hoisted__Str_7473;
    (void)hoisted__Str_7474;
    (void)hoisted__Str_7474;
    assert_eq__Str(&result, &hoisted__Str_7473, &hoisted__Str_7474);
    Str_delete(&hoisted__Str_7473, (Bool){0});
    Str_delete(&hoisted__Str_7474, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7502;
    (void)hoisted__Str_7502;
    (void)hoisted__Str_7503;
    (void)hoisted__Str_7503;
    assert_eq__Str(&r, &hoisted__Str_7502, &hoisted__Str_7503);
    Str_delete(&hoisted__Str_7502, (Bool){0});
    Str_delete(&hoisted__Str_7503, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7507;
    (void)hoisted__Str_7507;
    (void)hoisted__Str_7508;
    (void)hoisted__Str_7508;
    assert_eq__Str(&r2, &hoisted__Str_7507, &hoisted__Str_7508);
    Str_delete(&hoisted__Str_7507, (Bool){0});
    Str_delete(&hoisted__Str_7508, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7531;
    (void)hoisted__Str_7531;
    (void)hoisted__Str_7532;
    (void)hoisted__Str_7532;
    assert_eq__Str(&d, &hoisted__Str_7531, &hoisted__Str_7532);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7531, (Bool){0});
    Str_delete(&hoisted__Str_7532, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7543;
    (void)hoisted__Str_7543;
    (void)hoisted__Str_7544;
    (void)hoisted__Str_7544;
    assert_eq__Str(&d2, &hoisted__Str_7543, &hoisted__Str_7544);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7543, (Bool){0});
    Str_delete(&hoisted__Str_7544, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7556 = 106;
    (void)hoisted__I64_7556;
    (void)hoisted__Str_7557;
    (void)hoisted__Str_7557;
    assert_eq__I64(d3, hoisted__I64_7556, &hoisted__Str_7557);
    Str_delete(&hoisted__Str_7557, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8156;
    (void)hoisted__Str_8156;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8156);
    Str_delete(&hoisted__Str_8156, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)hoisted__Str_8157;
    (void)hoisted__Str_8157;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8157);
    Str_delete(&hoisted__Str_8157, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8159 = 8;
    (void)hoisted__I64_8159;
    (void)hoisted__Str_8160;
    (void)hoisted__Str_8160;
    assert_eq__I64(result, hoisted__I64_8159, &hoisted__Str_8160);
    Str_delete(&hoisted__Str_8160, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8163 = 1;
    (void)hoisted__Bool_8163;
    (void)hoisted__Str_8164;
    (void)hoisted__Str_8164;
    assert(hoisted__Bool_8163, &hoisted__Str_8164);
    Str_delete(&hoisted__Str_8164, (Bool){0});
    Bool hoisted__Bool_8167 = 1;
    (void)hoisted__Bool_8167;
    (void)hoisted__Str_8168;
    (void)hoisted__Str_8168;
    assert(hoisted__Bool_8167, &hoisted__Str_8168);
    Str_delete(&hoisted__Str_8168, (Bool){0});
}

void test_fold_f32(void) {
    (void)hoisted__Str_8173;
    (void)hoisted__Str_8173;
    (void)hoisted__Str_8174;
    (void)hoisted__Str_8174;
    (void)hoisted__Str_8175;
    (void)hoisted__Str_8175;
    assert_eq__Str(&hoisted__Str_8173, &hoisted__Str_8174, &hoisted__Str_8175);
    Str_delete(&hoisted__Str_8173, (Bool){0});
    Str_delete(&hoisted__Str_8174, (Bool){0});
    Str_delete(&hoisted__Str_8175, (Bool){0});
    (void)hoisted__Str_8178;
    (void)hoisted__Str_8178;
    (void)hoisted__Str_8179;
    (void)hoisted__Str_8179;
    (void)hoisted__Str_8180;
    (void)hoisted__Str_8180;
    assert_eq__Str(&hoisted__Str_8178, &hoisted__Str_8179, &hoisted__Str_8180);
    Str_delete(&hoisted__Str_8178, (Bool){0});
    Str_delete(&hoisted__Str_8179, (Bool){0});
    Str_delete(&hoisted__Str_8180, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8185 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8185;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8185;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8186 = 0;
    (void)hoisted__U32_8186;
    U64 hoisted__U64_8187 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8186); });
    (void)hoisted__U64_8187;
    return hoisted__U64_8187;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8218 = 16;
    (void)hoisted__U32_8218;
    return hoisted__U32_8218;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8219 = 42;
    (void)hoisted__I64_8219;
    (void)hoisted__Str_8220;
    (void)hoisted__Str_8220;
    assert_eq__I64(v.x, hoisted__I64_8219, &hoisted__Str_8220);
    Str_delete(&hoisted__Str_8220, (Bool){0});
    I64 hoisted__I64_8221 = 99;
    (void)hoisted__I64_8221;
    (void)hoisted__Str_8222;
    (void)hoisted__Str_8222;
    assert_eq__I64(v.y, hoisted__I64_8221, &hoisted__Str_8222);
    Str_delete(&hoisted__Str_8222, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8225 = 10;
    (void)hoisted__I64_8225;
    (void)hoisted__Str_8226;
    (void)hoisted__Str_8226;
    assert_eq__I64(p.x, hoisted__I64_8225, &hoisted__Str_8226);
    Str_delete(&hoisted__Str_8226, (Bool){0});
    I64 hoisted__I64_8227 = 20;
    (void)hoisted__I64_8227;
    (void)hoisted__Str_8228;
    (void)hoisted__Str_8228;
    assert_eq__I64(p.y, hoisted__I64_8227, &hoisted__Str_8228);
    Str_delete(&hoisted__Str_8228, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8234 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8234;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8234;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8235 = 0;
    (void)hoisted__U32_8235;
    U64 hoisted__U64_8236 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8235); });
    (void)hoisted__U64_8236;
    return hoisted__U64_8236;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8267 = 32;
    (void)hoisted__U32_8267;
    return hoisted__U32_8267;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8268 = 5;
    (void)hoisted__I64_8268;
    (void)hoisted__Str_8269;
    (void)hoisted__Str_8269;
    assert_eq__I64(r.top_left.x, hoisted__I64_8268, &hoisted__Str_8269);
    Str_delete(&hoisted__Str_8269, (Bool){0});
    I64 hoisted__I64_8270 = 10;
    (void)hoisted__I64_8270;
    (void)hoisted__Str_8271;
    (void)hoisted__Str_8271;
    assert_eq__I64(r.top_left.y, hoisted__I64_8270, &hoisted__Str_8271);
    Str_delete(&hoisted__Str_8271, (Bool){0});
    I64 hoisted__I64_8272 = 100;
    (void)hoisted__I64_8272;
    (void)hoisted__Str_8273;
    (void)hoisted__Str_8273;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8272, &hoisted__Str_8273);
    Str_delete(&hoisted__Str_8273, (Bool){0});
    I64 hoisted__I64_8274 = 200;
    (void)hoisted__I64_8274;
    (void)hoisted__Str_8275;
    (void)hoisted__Str_8275;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8274, &hoisted__Str_8275);
    Str_delete(&hoisted__Str_8275, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8277 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8277;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8277;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8278 = 0;
    (void)hoisted__U32_8278;
    U64 hoisted__U64_8279 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8278); });
    (void)hoisted__U64_8279;
    return hoisted__U64_8279;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8322 = 12;
    (void)hoisted__U32_8322;
    return hoisted__U32_8322;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8326 = F32_to_str(v.x);
    (void)hoisted__Str_8326;
    (void)hoisted__Str_8327;
    (void)hoisted__Str_8327;
    (void)hoisted__Str_8328;
    (void)hoisted__Str_8328;
    assert_eq__Str(hoisted__Str_8326, &hoisted__Str_8327, &hoisted__Str_8328);
    Str_delete(hoisted__Str_8326, 1);
    Str_delete(&hoisted__Str_8327, (Bool){0});
    Str_delete(&hoisted__Str_8328, (Bool){0});
    Str *hoisted__Str_8329 = F32_to_str(v.y);
    (void)hoisted__Str_8329;
    (void)hoisted__Str_8330;
    (void)hoisted__Str_8330;
    (void)hoisted__Str_8331;
    (void)hoisted__Str_8331;
    assert_eq__Str(hoisted__Str_8329, &hoisted__Str_8330, &hoisted__Str_8331);
    Str_delete(hoisted__Str_8329, 1);
    Str_delete(&hoisted__Str_8330, (Bool){0});
    Str_delete(&hoisted__Str_8331, (Bool){0});
    Str *hoisted__Str_8332 = F32_to_str(v.z);
    (void)hoisted__Str_8332;
    (void)hoisted__Str_8333;
    (void)hoisted__Str_8333;
    (void)hoisted__Str_8334;
    (void)hoisted__Str_8334;
    assert_eq__Str(hoisted__Str_8332, &hoisted__Str_8333, &hoisted__Str_8334);
    Str_delete(hoisted__Str_8332, 1);
    Str_delete(&hoisted__Str_8333, (Bool){0});
    Str_delete(&hoisted__Str_8334, (Bool){0});
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
    Bool hoisted__Bool_8339 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8339;
    if (hoisted__Bool_8339) {
        Bool hoisted__Bool_8336 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8336;
        { Bool _ret_val = hoisted__Bool_8336;
                return _ret_val; }
    }
    Bool hoisted__Bool_8340 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8340;
    if (hoisted__Bool_8340) {
        Bool hoisted__Bool_8337 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8337;
        { Bool _ret_val = hoisted__Bool_8337;
                return _ret_val; }
    }
    Bool hoisted__Bool_8341 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8341;
    if (hoisted__Bool_8341) {
        Bool hoisted__Bool_8338 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8338;
        { Bool _ret_val = hoisted__Bool_8338;
                return _ret_val; }
    }
    Bool hoisted__Bool_8342 = 0;
    (void)hoisted__Bool_8342;
    return hoisted__Bool_8342;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8350 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8350;
    if (hoisted__Bool_8350) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8351 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8351;
    if (hoisted__Bool_8351) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8352 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8352;
    if (hoisted__Bool_8352) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8353 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8353;
    UNREACHABLE(&hoisted__Str_8353);
    Str_delete(&hoisted__Str_8353, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8354 = 4;
    (void)hoisted__U32_8354;
    return hoisted__U32_8354;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8355 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8355;
    (void)hoisted__Str_8356;
    (void)hoisted__Str_8356;
    assert(hoisted__Bool_8355, &hoisted__Str_8356);
    Str_delete(&hoisted__Str_8356, (Bool){0});
    Bool hoisted__Bool_8357 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8357;
    Bool hoisted__Bool_8358 = not(hoisted__Bool_8357);
    (void)hoisted__Bool_8358;
    (void)hoisted__Str_8359;
    (void)hoisted__Str_8359;
    assert(hoisted__Bool_8358, &hoisted__Str_8359);
    Str_delete(&hoisted__Str_8359, (Bool){0});
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
    Bool hoisted__Bool_8360 = is(self, other);
    (void)hoisted__Bool_8360;
    return hoisted__Bool_8360;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8378 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8378;
    if (hoisted__Bool_8378) {
        I64 *hoisted__I64_8374 = get_payload(self);
        (void)hoisted__I64_8374;
        (void)hoisted__I64_8374;
        Bool hoisted__Bool_8375 = 0;
        (void)hoisted__Bool_8375;
        I64_delete(hoisted__I64_8374, hoisted__Bool_8375);
    }
    Bool hoisted__Bool_8379 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8379;
    if (hoisted__Bool_8379) {
        Str *hoisted__Str_8376 = get_payload(self);
        (void)hoisted__Str_8376;
        (void)hoisted__Str_8376;
        Bool hoisted__Bool_8377 = 0;
        (void)hoisted__Bool_8377;
        Str_delete(hoisted__Str_8376, hoisted__Bool_8377);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8410 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8410;
    if (hoisted__Bool_8410) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8407 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8407;
        { Token * _ret_val = hoisted__Token_8407;
                return _ret_val; }
    }
    Bool hoisted__Bool_8411 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8411;
    if (hoisted__Bool_8411) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8408 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8408;
        Token *hoisted__Token_8409 = Token_Name(hoisted__Str_8408);
        (void)hoisted__Token_8409;
        { Token * _ret_val = hoisted__Token_8409;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8412 = 24;
    (void)hoisted__U32_8412;
    return hoisted__U32_8412;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8414 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8414;
    (void)hoisted__Str_8415;
    (void)hoisted__Str_8415;
    assert(hoisted__Bool_8414, &hoisted__Str_8415);
    Str_delete(&hoisted__Str_8415, (Bool){0});
    Bool hoisted__Bool_8416 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8416;
    Bool hoisted__Bool_8417 = not(hoisted__Bool_8416);
    (void)hoisted__Bool_8417;
    (void)hoisted__Str_8418;
    (void)hoisted__Str_8418;
    assert(hoisted__Bool_8417, &hoisted__Str_8418);
    Str_delete(&hoisted__Str_8418, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8419 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8419;
    (void)hoisted__Str_8420;
    (void)hoisted__Str_8420;
    assert(hoisted__Bool_8419, &hoisted__Str_8420);
    Str_delete(&hoisted__Str_8420, (Bool){0});
    Bool hoisted__Bool_8421 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8421;
    Bool hoisted__Bool_8422 = not(hoisted__Bool_8421);
    (void)hoisted__Bool_8422;
    (void)hoisted__Str_8423;
    (void)hoisted__Str_8423;
    assert(hoisted__Bool_8422, &hoisted__Str_8423);
    Str_delete(&hoisted__Str_8423, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8426 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8426;
    (void)hoisted__Str_8427;
    (void)hoisted__Str_8427;
    assert(hoisted__Bool_8426, &hoisted__Str_8427);
    Str_delete(&hoisted__Str_8427, (Bool){0});
    Bool hoisted__Bool_8428 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8428;
    Bool hoisted__Bool_8429 = not(hoisted__Bool_8428);
    (void)hoisted__Bool_8429;
    (void)hoisted__Str_8430;
    (void)hoisted__Str_8430;
    assert(hoisted__Bool_8429, &hoisted__Str_8430);
    Str_delete(&hoisted__Str_8430, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8562 = I64_neq(a, b);
    (void)hoisted__Bool_8562;
    if (hoisted__Bool_8562) {
        U32 hoisted__U32_8546 = 5;
        (void)hoisted__U32_8546;
        Array__Str *_va_Array_249 = Array__Str_new(hoisted__U32_8546);
        (void)_va_Array_249;
        I64 _va_Array_249_ek = 0;
        (void)_va_Array_249_ek;
        OutOfBounds *_va_Array_249_eo = malloc(sizeof(OutOfBounds));
        _va_Array_249_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_249_eo;
        U32 hoisted__U32_8547 = 0;
        (void)hoisted__U32_8547;
        (void)hoisted__Str_8548;
        (void)hoisted__Str_8548;
        (void)hoisted__Str_8549;
        (void)hoisted__Str_8549;
        Array__Str_set(_va_Array_249, hoisted__U32_8547, &hoisted__Str_8548, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8549);
        Str_delete(&hoisted__Str_8549, (Bool){0});
        U32 hoisted__U32_8550 = 1;
        (void)hoisted__U32_8550;
        Str *hoisted__Str_8551 = I64_to_str(a);
        (void)hoisted__Str_8551;
        (void)hoisted__Str_8552;
        (void)hoisted__Str_8552;
        Array__Str_set(_va_Array_249, hoisted__U32_8550, hoisted__Str_8551, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8552);
        Str_delete(&hoisted__Str_8552, (Bool){0});
        U32 hoisted__U32_8553 = 2;
        (void)hoisted__U32_8553;
        (void)hoisted__Str_8554;
        (void)hoisted__Str_8554;
        (void)hoisted__Str_8555;
        (void)hoisted__Str_8555;
        Array__Str_set(_va_Array_249, hoisted__U32_8553, &hoisted__Str_8554, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8555);
        Str_delete(&hoisted__Str_8555, (Bool){0});
        U32 hoisted__U32_8556 = 3;
        (void)hoisted__U32_8556;
        Str *hoisted__Str_8557 = I64_to_str(b);
        (void)hoisted__Str_8557;
        (void)hoisted__Str_8558;
        (void)hoisted__Str_8558;
        Array__Str_set(_va_Array_249, hoisted__U32_8556, hoisted__Str_8557, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8558);
        Str_delete(&hoisted__Str_8558, (Bool){0});
        U32 hoisted__U32_8559 = 4;
        (void)hoisted__U32_8559;
        (void)hoisted__Str_8560;
        (void)hoisted__Str_8560;
        (void)hoisted__Str_8561;
        (void)hoisted__Str_8561;
        Array__Str_set(_va_Array_249, hoisted__U32_8559, &hoisted__Str_8560, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8561);
        OutOfBounds_delete(_va_Array_249_eo, 1);
        Str_delete(&hoisted__Str_8561, (Bool){0});
        panic(_va_Array_249, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8579 = Str_neq(a, b);
    (void)hoisted__Bool_8579;
    if (hoisted__Bool_8579) {
        U32 hoisted__U32_8563 = 5;
        (void)hoisted__U32_8563;
        Array__Str *_va_Array_250 = Array__Str_new(hoisted__U32_8563);
        (void)_va_Array_250;
        I64 _va_Array_250_ek = 0;
        (void)_va_Array_250_ek;
        OutOfBounds *_va_Array_250_eo = malloc(sizeof(OutOfBounds));
        _va_Array_250_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_250_eo;
        U32 hoisted__U32_8564 = 0;
        (void)hoisted__U32_8564;
        (void)hoisted__Str_8565;
        (void)hoisted__Str_8565;
        (void)hoisted__Str_8566;
        (void)hoisted__Str_8566;
        Array__Str_set(_va_Array_250, hoisted__U32_8564, &hoisted__Str_8565, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8566);
        Str_delete(&hoisted__Str_8566, (Bool){0});
        U32 hoisted__U32_8567 = 1;
        (void)hoisted__U32_8567;
        Str *hoisted__Str_8568 = Str_to_str(a);
        (void)hoisted__Str_8568;
        (void)hoisted__Str_8569;
        (void)hoisted__Str_8569;
        Array__Str_set(_va_Array_250, hoisted__U32_8567, hoisted__Str_8568, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8569);
        Str_delete(&hoisted__Str_8569, (Bool){0});
        U32 hoisted__U32_8570 = 2;
        (void)hoisted__U32_8570;
        (void)hoisted__Str_8571;
        (void)hoisted__Str_8571;
        (void)hoisted__Str_8572;
        (void)hoisted__Str_8572;
        Array__Str_set(_va_Array_250, hoisted__U32_8570, &hoisted__Str_8571, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8572);
        Str_delete(&hoisted__Str_8572, (Bool){0});
        U32 hoisted__U32_8573 = 3;
        (void)hoisted__U32_8573;
        Str *hoisted__Str_8574 = Str_to_str(b);
        (void)hoisted__Str_8574;
        (void)hoisted__Str_8575;
        (void)hoisted__Str_8575;
        Array__Str_set(_va_Array_250, hoisted__U32_8573, hoisted__Str_8574, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8575);
        Str_delete(&hoisted__Str_8575, (Bool){0});
        U32 hoisted__U32_8576 = 4;
        (void)hoisted__U32_8576;
        (void)hoisted__Str_8577;
        (void)hoisted__Str_8577;
        (void)hoisted__Str_8578;
        (void)hoisted__Str_8578;
        Array__Str_set(_va_Array_250, hoisted__U32_8576, &hoisted__Str_8577, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8578);
        OutOfBounds_delete(_va_Array_250_eo, 1);
        Str_delete(&hoisted__Str_8578, (Bool){0});
        panic(_va_Array_250, loc);
    }
}

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
void U64_inc_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U64_inc(_a0);
}
static __attribute__((unused)) TilClosure U64_inc_dyn__til_closure = { (void *)U64_inc_dyn, NULL, NULL };
void U64_dec_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U64_dec(_a0);
}
static __attribute__((unused)) TilClosure U64_dec_dyn__til_closure = { (void *)U64_dec_dyn, NULL, NULL };
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
Bool U32_lt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_lt(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_lt_dyn__til_closure = { (void *)U32_lt_dyn, NULL, NULL };
Bool U32_gt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_gt(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_gt_dyn__til_closure = { (void *)U32_gt_dyn, NULL, NULL };
Bool U32_neq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_neq(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_neq_dyn__til_closure = { (void *)U32_neq_dyn, NULL, NULL };
Bool U32_lte_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_lte(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_lte_dyn__til_closure = { (void *)U32_lte_dyn, NULL, NULL };
Bool U32_gte_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_gte(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_gte_dyn__til_closure = { (void *)U32_gte_dyn, NULL, NULL };
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
Bool I32_lt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_lt(*(I32 *)_a0, *(I32 *)_a1);
}
static __attribute__((unused)) TilClosure I32_lt_dyn__til_closure = { (void *)I32_lt_dyn, NULL, NULL };
Bool I32_gt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_gt(*(I32 *)_a0, *(I32 *)_a1);
}
static __attribute__((unused)) TilClosure I32_gt_dyn__til_closure = { (void *)I32_gt_dyn, NULL, NULL };
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
Bool Str_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_eq_dyn__til_closure = { (void *)Str_eq_dyn, NULL, NULL };
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
void *I64_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)I64_to_str(*(I64 *)_a0);
}
static __attribute__((unused)) TilClosure I64_to_str_dyn__til_closure = { (void *)I64_to_str_dyn, NULL, NULL };
U8 I64_to_u8_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return I64_to_u8(*(I64 *)_a0);
}
static __attribute__((unused)) TilClosure I64_to_u8_dyn__til_closure = { (void *)I64_to_u8_dyn, NULL, NULL };
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
Bool I64_lt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_lt(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_lt_dyn__til_closure = { (void *)I64_lt_dyn, NULL, NULL };
Bool I64_gt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_gt(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_gt_dyn__til_closure = { (void *)I64_gt_dyn, NULL, NULL };
Bool I64_neq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_neq(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_neq_dyn__til_closure = { (void *)I64_neq_dyn, NULL, NULL };
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&F32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&F32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&F32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&F32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&F32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&F32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U64_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U64_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)&U32_to_i64_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U32_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U32_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)&U32_lt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)&U32_gt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)&U32_neq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)&U32_lte_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)&U32_gte_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)&I32_lt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)&I32_gt_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I8_hash_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U8_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Str_len_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Str_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)&Str_with_capacity_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)&Str_push_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Str_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&Str_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Str_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Str_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Str_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Str_eq_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&I64_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)&I64_to_u8_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)&I64_lt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)&I64_gt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)&I64_neq_dyn__til_closure;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__I64_new_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__I64_clear_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__I64_delete_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__I64_clone_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__I64_size_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return sizeof(F32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) return sizeof(I8);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) return sizeof(OutOfBounds);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) return sizeof(Array__Str);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) return sizeof(Vec__Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return sizeof(I64);
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
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) return sizeof(Vec__Declaration);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) return sizeof(Vec__Expr);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) return sizeof(Vec__I64);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
        return 0LL;
    }
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        return 11LL;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        return 11LL;
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
        return 6LL;
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
        return 1LL;
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
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit1 = (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit1; });
        if (*index == 1LL) return ({ static Str _lit2 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit2; });
        if (*index == 2LL) return ({ static Str _lit3 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit3; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit4 = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit4; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit5 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit5; });
        if (*index == 1LL) return ({ static Str _lit6 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit6; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit7 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit7; });
        if (*index == 1LL) return ({ static Str _lit8 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit8; });
        if (*index == 2LL) return ({ static Str _lit9 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit9; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit10 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit10; });
        if (*index == 1LL) return ({ static Str _lit11 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit11; });
        if (*index == 2LL) return ({ static Str _lit12 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT}; &_lit12; });
        if (*index == 3LL) return ({ static Str _lit13 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit13; });
        if (*index == 4LL) return ({ static Str _lit14 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT}; &_lit14; });
        if (*index == 5LL) return ({ static Str _lit15 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit15; });
        if (*index == 6LL) return ({ static Str _lit16 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit16; });
        if (*index == 7LL) return ({ static Str _lit17 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit17; });
        if (*index == 8LL) return ({ static Str _lit18 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit18; });
        if (*index == 9LL) return ({ static Str _lit19 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT}; &_lit19; });
        if (*index == 10LL) return ({ static Str _lit20 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit20; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit21 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit21; });
        if (*index == 1LL) return ({ static Str _lit22 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit22; });
        if (*index == 2LL) return ({ static Str _lit23 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit23; });
        if (*index == 3LL) return ({ static Str _lit24 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit24; });
        if (*index == 4LL) return ({ static Str _lit25 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit25; });
        if (*index == 5LL) return ({ static Str _lit26 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit26; });
        if (*index == 6LL) return ({ static Str _lit27 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit27; });
        if (*index == 7LL) return ({ static Str _lit28 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit28; });
        if (*index == 8LL) return ({ static Str _lit29 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT}; &_lit29; });
        if (*index == 9LL) return ({ static Str _lit30 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit30; });
        if (*index == 10LL) return ({ static Str _lit31 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit31; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit32 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit32; });
        if (*index == 1LL) return ({ static Str _lit33 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit33; });
        if (*index == 2LL) return ({ static Str _lit34 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit34; });
        if (*index == 3LL) return ({ static Str _lit35 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit35; });
        if (*index == 4LL) return ({ static Str _lit36 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit36; });
        if (*index == 5LL) return ({ static Str _lit37 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit37; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit38 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit38; });
        if (*index == 1LL) return ({ static Str _lit39 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit39; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit40 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit40; });
        if (*index == 1LL) return ({ static Str _lit41 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit41; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit42 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit42; });
        if (*index == 1LL) return ({ static Str _lit43 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit43; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit44 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit44; });
        if (*index == 1LL) return ({ static Str _lit45 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit45; });
        if (*index == 2LL) return ({ static Str _lit46 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit46; });
        if (*index == 3LL) return ({ static Str _lit47 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit47; });
        if (*index == 4LL) return ({ static Str _lit48 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT}; &_lit48; });
        if (*index == 5LL) return ({ static Str _lit49 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit49; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit50 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit50; });
        if (*index == 1LL) return ({ static Str _lit51 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit51; });
        if (*index == 2LL) return ({ static Str _lit52 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT}; &_lit52; });
        if (*index == 3LL) return ({ static Str _lit53 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit53; });
        if (*index == 4LL) return ({ static Str _lit54 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit54; });
        if (*index == 5LL) return ({ static Str _lit55 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit55; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit56 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit56; });
        if (*index == 1LL) return ({ static Str _lit57 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit57; });
        if (*index == 2LL) return ({ static Str _lit58 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit58; });
        if (*index == 3LL) return ({ static Str _lit59 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit59; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit60 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit60; });
        if (*index == 1LL) return ({ static Str _lit61 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit61; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit62 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit62; });
        if (*index == 1LL) return ({ static Str _lit63 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit63; });
        if (*index == 2LL) return ({ static Str _lit64 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit64; });
        if (*index == 3LL) return ({ static Str _lit65 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit65; });
        if (*index == 4LL) return ({ static Str _lit66 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit66; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit67 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit67; });
        if (*index == 1LL) return ({ static Str _lit68 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit68; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit69 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit69; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit70 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit70; });
        if (*index == 1LL) return ({ static Str _lit71 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit71; });
        if (*index == 2LL) return ({ static Str _lit72 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit72; });
        if (*index == 3LL) return ({ static Str _lit73 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit73; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit74 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit74; });
        if (*index == 1LL) return ({ static Str _lit75 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit75; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit76 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit76; });
        if (*index == 1LL) return ({ static Str _lit77 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit77; });
        if (*index == 2LL) return ({ static Str _lit78 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit78; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit79 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit79; });
        if (*index == 1LL) return ({ static Str _lit80 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit80; });
        if (*index == 2LL) return ({ static Str _lit81 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit81; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit82 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit82; });
        if (*index == 1LL) return ({ static Str _lit83 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit83; });
        if (*index == 2LL) return ({ static Str _lit84 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit84; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit85 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit85; });
        if (*index == 1LL) return ({ static Str _lit86 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit86; });
        if (*index == 2LL) return ({ static Str _lit87 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit87; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit88 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit88; });
        if (*index == 1LL) return ({ static Str _lit89 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit89; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit90 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit90; });
        if (*index == 1LL) return ({ static Str _lit91 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit91; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit92 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit92; });
        if (*index == 1LL) return ({ static Str _lit93 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit93; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit94 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit94; });
        if (*index == 1LL) return ({ static Str _lit95 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit95; });
        if (*index == 2LL) return ({ static Str _lit96 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit96; });
    }
    fprintf(stderr, "struct_field_name: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 struct_field_is_mut(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit97 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit97; });
        if (*index == 1LL) return ({ static Str _lit98 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit98; });
        if (*index == 2LL) return ({ static Str _lit99 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit99; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit100 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit100; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit101 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit101; });
        if (*index == 1LL) return ({ static Str _lit102 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit102; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit103 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit103; });
        if (*index == 1LL) return ({ static Str _lit104 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit104; });
        if (*index == 2LL) return ({ static Str _lit105 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit105; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit106 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit106; });
        if (*index == 1LL) return ({ static Str _lit107 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit107; });
        if (*index == 2LL) return ({ static Str _lit108 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit108; });
        if (*index == 3LL) return ({ static Str _lit109 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit109; });
        if (*index == 4LL) return ({ static Str _lit110 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit110; });
        if (*index == 5LL) return ({ static Str _lit111 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit111; });
        if (*index == 6LL) return ({ static Str _lit112 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit112; });
        if (*index == 7LL) return ({ static Str _lit113 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit113; });
        if (*index == 8LL) return ({ static Str _lit114 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit114; });
        if (*index == 9LL) return ({ static Str _lit115 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit115; });
        if (*index == 10LL) return ({ static Str _lit116 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit116; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit117 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit117; });
        if (*index == 1LL) return ({ static Str _lit118 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit118; });
        if (*index == 2LL) return ({ static Str _lit119 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit119; });
        if (*index == 3LL) return ({ static Str _lit120 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit120; });
        if (*index == 4LL) return ({ static Str _lit121 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit121; });
        if (*index == 5LL) return ({ static Str _lit122 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit122; });
        if (*index == 6LL) return ({ static Str _lit123 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit123; });
        if (*index == 7LL) return ({ static Str _lit124 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit124; });
        if (*index == 8LL) return ({ static Str _lit125 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit125; });
        if (*index == 9LL) return ({ static Str _lit126 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit126; });
        if (*index == 10LL) return ({ static Str _lit127 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit127; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit128 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit128; });
        if (*index == 1LL) return ({ static Str _lit129 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit129; });
        if (*index == 2LL) return ({ static Str _lit130 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit130; });
        if (*index == 3LL) return ({ static Str _lit131 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit131; });
        if (*index == 4LL) return ({ static Str _lit132 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit132; });
        if (*index == 5LL) return ({ static Str _lit133 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit133; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit134 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit134; });
        if (*index == 1LL) return ({ static Str _lit135 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit135; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit136 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit136; });
        if (*index == 1LL) return ({ static Str _lit137 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit137; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit138 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit138; });
        if (*index == 1LL) return ({ static Str _lit139 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit139; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit140 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit140; });
        if (*index == 1LL) return ({ static Str _lit141 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit141; });
        if (*index == 2LL) return ({ static Str _lit142 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit142; });
        if (*index == 3LL) return ({ static Str _lit143 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit143; });
        if (*index == 4LL) return ({ static Str _lit144 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit144; });
        if (*index == 5LL) return ({ static Str _lit145 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit145; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit146 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit146; });
        if (*index == 1LL) return ({ static Str _lit147 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit147; });
        if (*index == 2LL) return ({ static Str _lit148 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit148; });
        if (*index == 3LL) return ({ static Str _lit149 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit149; });
        if (*index == 4LL) return ({ static Str _lit150 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit150; });
        if (*index == 5LL) return ({ static Str _lit151 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit151; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit152 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit152; });
        if (*index == 1LL) return ({ static Str _lit153 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit153; });
        if (*index == 2LL) return ({ static Str _lit154 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit154; });
        if (*index == 3LL) return ({ static Str _lit155 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit155; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit156 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit156; });
        if (*index == 1LL) return ({ static Str _lit157 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit157; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit158 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit158; });
        if (*index == 1LL) return ({ static Str _lit159 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit159; });
        if (*index == 2LL) return ({ static Str _lit160 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit160; });
        if (*index == 3LL) return ({ static Str _lit161 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit161; });
        if (*index == 4LL) return ({ static Str _lit162 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit162; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit163 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit163; });
        if (*index == 1LL) return ({ static Str _lit164 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit164; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit165 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit165; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit166 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit166; });
        if (*index == 1LL) return ({ static Str _lit167 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit167; });
        if (*index == 2LL) return ({ static Str _lit168 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit168; });
        if (*index == 3LL) return ({ static Str _lit169 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit169; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit170 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit170; });
        if (*index == 1LL) return ({ static Str _lit171 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit171; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit172 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit172; });
        if (*index == 1LL) return ({ static Str _lit173 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit173; });
        if (*index == 2LL) return ({ static Str _lit174 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit174; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit175 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit175; });
        if (*index == 1LL) return ({ static Str _lit176 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit176; });
        if (*index == 2LL) return ({ static Str _lit177 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit177; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit178 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit178; });
        if (*index == 1LL) return ({ static Str _lit179 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit179; });
        if (*index == 2LL) return ({ static Str _lit180 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit180; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit181 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit181; });
        if (*index == 1LL) return ({ static Str _lit182 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit182; });
        if (*index == 2LL) return ({ static Str _lit183 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit183; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit184 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit184; });
        if (*index == 1LL) return ({ static Str _lit185 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit185; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit186 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit186; });
        if (*index == 1LL) return ({ static Str _lit187 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit187; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit188 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit188; });
        if (*index == 1LL) return ({ static Str _lit189 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit189; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit190 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit190; });
        if (*index == 1LL) return ({ static Str _lit191 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit191; });
        if (*index == 2LL) return ({ static Str _lit192 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit192; });
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
        return 12LL;
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
        return 27LL;
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
        if (*index == 0LL) return ({ static Str _lit193 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit193; });
        if (*index == 1LL) return ({ static Str _lit194 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit194; });
        if (*index == 2LL) return ({ static Str _lit195 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit195; });
        if (*index == 3LL) return ({ static Str _lit196 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit196; });
        if (*index == 4LL) return ({ static Str _lit197 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit197; });
        if (*index == 5LL) return ({ static Str _lit198 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit198; });
        if (*index == 6LL) return ({ static Str _lit199 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit199; });
        if (*index == 7LL) return ({ static Str _lit200 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit200; });
        if (*index == 8LL) return ({ static Str _lit201 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit201; });
        if (*index == 9LL) return ({ static Str _lit202 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit202; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit203 = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit203; });
        if (*index == 1LL) return ({ static Str _lit204 = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit204; });
        if (*index == 2LL) return ({ static Str _lit205 = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit205; });
        if (*index == 3LL) return ({ static Str _lit206 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit206; });
        if (*index == 4LL) return ({ static Str _lit207 = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit207; });
        if (*index == 5LL) return ({ static Str _lit208 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit208; });
        if (*index == 6LL) return ({ static Str _lit209 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit209; });
        if (*index == 7LL) return ({ static Str _lit210 = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit210; });
        if (*index == 8LL) return ({ static Str _lit211 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit211; });
        if (*index == 9LL) return ({ static Str _lit212 = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit212; });
        if (*index == 10LL) return ({ static Str _lit213 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit213; });
        if (*index == 11LL) return ({ static Str _lit214 = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit214; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit215 = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit215; });
        if (*index == 1LL) return ({ static Str _lit216 = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit216; });
        if (*index == 2LL) return ({ static Str _lit217 = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit217; });
        if (*index == 3LL) return ({ static Str _lit218 = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit218; });
        if (*index == 4LL) return ({ static Str _lit219 = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit219; });
        if (*index == 5LL) return ({ static Str _lit220 = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit220; });
        if (*index == 6LL) return ({ static Str _lit221 = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit221; });
        if (*index == 7LL) return ({ static Str _lit222 = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit222; });
        if (*index == 8LL) return ({ static Str _lit223 = (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit223; });
        if (*index == 9LL) return ({ static Str _lit224 = (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit224; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit225 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit225; });
        if (*index == 1LL) return ({ static Str _lit226 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit226; });
        if (*index == 2LL) return ({ static Str _lit227 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit227; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit228 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit228; });
        if (*index == 1LL) return ({ static Str _lit229 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit229; });
        if (*index == 2LL) return ({ static Str _lit230 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit230; });
        if (*index == 3LL) return ({ static Str _lit231 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit231; });
        if (*index == 4LL) return ({ static Str _lit232 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit232; });
        if (*index == 5LL) return ({ static Str _lit233 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit233; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit234 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit234; });
        if (*index == 1LL) return ({ static Str _lit235 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit235; });
        if (*index == 2LL) return ({ static Str _lit236 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit236; });
        if (*index == 3LL) return ({ static Str _lit237 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit237; });
        if (*index == 4LL) return ({ static Str _lit238 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit238; });
        if (*index == 5LL) return ({ static Str _lit239 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit239; });
        if (*index == 6LL) return ({ static Str _lit240 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit240; });
        if (*index == 7LL) return ({ static Str _lit241 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit241; });
        if (*index == 8LL) return ({ static Str _lit242 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit242; });
        if (*index == 9LL) return ({ static Str _lit243 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit243; });
        if (*index == 10LL) return ({ static Str _lit244 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit244; });
        if (*index == 11LL) return ({ static Str _lit245 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit245; });
        if (*index == 12LL) return ({ static Str _lit246 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit246; });
        if (*index == 13LL) return ({ static Str _lit247 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit247; });
        if (*index == 14LL) return ({ static Str _lit248 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit248; });
        if (*index == 15LL) return ({ static Str _lit249 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit249; });
        if (*index == 16LL) return ({ static Str _lit250 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit250; });
        if (*index == 17LL) return ({ static Str _lit251 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit251; });
        if (*index == 18LL) return ({ static Str _lit252 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit252; });
        if (*index == 19LL) return ({ static Str _lit253 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit253; });
        if (*index == 20LL) return ({ static Str _lit254 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit254; });
        if (*index == 21LL) return ({ static Str _lit255 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit255; });
        if (*index == 22LL) return ({ static Str _lit256 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit256; });
        if (*index == 23LL) return ({ static Str _lit257 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit257; });
        if (*index == 24LL) return ({ static Str _lit258 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit258; });
        if (*index == 25LL) return ({ static Str _lit259 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit259; });
        if (*index == 26LL) return ({ static Str _lit260 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit260; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit261 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit261; });
        if (*index == 1LL) return ({ static Str _lit262 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit262; });
        if (*index == 2LL) return ({ static Str _lit263 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit263; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit264 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit264; });
        if (*index == 1LL) return ({ static Str _lit265 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit265; });
        if (*index == 2LL) return ({ static Str _lit266 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit266; });
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
        if (*index == 0LL) return ({ static Str _lit267 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit267; });
        if (*index == 1LL) return ({ static Str _lit268 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit268; });
        if (*index == 2LL) return ({ static Str _lit269 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit269; });
        if (*index == 3LL) return ({ static Str _lit270 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit270; });
        if (*index == 4LL) return ({ static Str _lit271 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit271; });
        if (*index == 5LL) return ({ static Str _lit272 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit272; });
        if (*index == 6LL) return ({ static Str _lit273 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit273; });
        if (*index == 7LL) return ({ static Str _lit274 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit274; });
        if (*index == 8LL) return ({ static Str _lit275 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit275; });
        if (*index == 9LL) return ({ static Str _lit276 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit276; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit277 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit277; });
        if (*index == 1LL) return ({ static Str _lit278 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit278; });
        if (*index == 2LL) return ({ static Str _lit279 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit279; });
        if (*index == 3LL) return ({ static Str _lit280 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit280; });
        if (*index == 4LL) return ({ static Str _lit281 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit281; });
        if (*index == 5LL) return ({ static Str _lit282 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit282; });
        if (*index == 6LL) return ({ static Str _lit283 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit283; });
        if (*index == 7LL) return ({ static Str _lit284 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit284; });
        if (*index == 8LL) return ({ static Str _lit285 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit285; });
        if (*index == 9LL) return ({ static Str _lit286 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit286; });
        if (*index == 10LL) return ({ static Str _lit287 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit287; });
        if (*index == 11LL) return ({ static Str _lit288 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit288; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit289 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit289; });
        if (*index == 1LL) return ({ static Str _lit290 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit290; });
        if (*index == 2LL) return ({ static Str _lit291 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit291; });
        if (*index == 3LL) return ({ static Str _lit292 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit292; });
        if (*index == 4LL) return ({ static Str _lit293 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit293; });
        if (*index == 5LL) return ({ static Str _lit294 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit294; });
        if (*index == 6LL) return ({ static Str _lit295 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit295; });
        if (*index == 7LL) return ({ static Str _lit296 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit296; });
        if (*index == 8LL) return ({ static Str _lit297 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit297; });
        if (*index == 9LL) return ({ static Str _lit298 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit298; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit299 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit299; });
        if (*index == 1LL) return ({ static Str _lit300 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit300; });
        if (*index == 2LL) return ({ static Str _lit301 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit301; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit302 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit302; });
        if (*index == 1LL) return ({ static Str _lit303 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit303; });
        if (*index == 2LL) return ({ static Str _lit304 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit304; });
        if (*index == 3LL) return ({ static Str _lit305 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit305; });
        if (*index == 4LL) return ({ static Str _lit306 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit306; });
        if (*index == 5LL) return ({ static Str _lit307 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit307; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit308 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit308; });
        if (*index == 1LL) return ({ static Str _lit309 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit309; });
        if (*index == 2LL) return ({ static Str _lit310 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit310; });
        if (*index == 3LL) return ({ static Str _lit311 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit311; });
        if (*index == 4LL) return ({ static Str _lit312 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit312; });
        if (*index == 5LL) return ({ static Str _lit313 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit313; });
        if (*index == 6LL) return ({ static Str _lit314 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit314; });
        if (*index == 7LL) return ({ static Str _lit315 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit315; });
        if (*index == 8LL) return ({ static Str _lit316 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit316; });
        if (*index == 9LL) return ({ static Str _lit317 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit317; });
        if (*index == 10LL) return ({ static Str _lit318 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit318; });
        if (*index == 11LL) return ({ static Str _lit319 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit319; });
        if (*index == 12LL) return ({ static Str _lit320 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit320; });
        if (*index == 13LL) return ({ static Str _lit321 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit321; });
        if (*index == 14LL) return ({ static Str _lit322 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit322; });
        if (*index == 15LL) return ({ static Str _lit323 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit323; });
        if (*index == 16LL) return ({ static Str _lit324 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit324; });
        if (*index == 17LL) return ({ static Str _lit325 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit325; });
        if (*index == 18LL) return ({ static Str _lit326 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit326; });
        if (*index == 19LL) return ({ static Str _lit327 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit327; });
        if (*index == 20LL) return ({ static Str _lit328 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit328; });
        if (*index == 21LL) return ({ static Str _lit329 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit329; });
        if (*index == 22LL) return ({ static Str _lit330 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit330; });
        if (*index == 23LL) return ({ static Str _lit331 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit331; });
        if (*index == 24LL) return ({ static Str _lit332 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit332; });
        if (*index == 25LL) return ({ static Str _lit333 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit333; });
        if (*index == 26LL) return ({ static Str _lit334 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit334; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit335 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit335; });
        if (*index == 1LL) return ({ static Str _lit336 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit336; });
        if (*index == 2LL) return ({ static Str _lit337 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit337; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit338 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit338; });
        if (*index == 1LL) return ({ static Str _lit339 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit339; });
        if (*index == 2LL) return ({ static Str _lit340 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit340; });
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
        if (*index == 0LL) return ({ static Str _lit341 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit341; });
        if (*index == 1LL) return ({ static Str _lit342 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit342; });
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
        if (*index == 0LL) return ({ static Str _lit343 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit343; });
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
