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
Bool I32_neq(I32 a, I32 b);
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
Bool I32_neq(I32 a, I32 b);
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

static Str hoisted__Str_7083 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7085 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7086 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7090 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7102 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7103 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7106 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7107 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7328 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7336 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7344 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7347 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7348 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7376 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7377 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7381 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7382 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7405 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7406 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7417 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7418 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7431 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8030 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8031 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8034 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8038 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8042 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8047 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8048 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8049 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8052 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8053 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8054 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8094 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8096 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8100 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8102 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8143 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8145 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8147 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8149 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8201 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8202 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8204 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8205 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8207 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8208 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8230 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8233 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8289 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8292 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8294 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8297 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8301 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8304 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8422 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8423 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8426 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8428 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8429 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8432 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8434 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8435 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8439 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8440 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8443 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8445 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8446 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8449 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8451 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8452 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};

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
    U64 hoisted__U64_37 = U64_add(DEREF(self), hoisted__U64_36);
    (void)hoisted__U64_37;
    *self = hoisted__U64_37;
}

void U64_dec(U64 * self) {
    U64 hoisted__U64_38 = 1ULL;
    (void)hoisted__U64_38;
    U64 hoisted__U64_39 = U64_sub(DEREF(self), hoisted__U64_38);
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
    U32 hoisted__U32_148 = U32_add(DEREF(self), hoisted__U32_147);
    (void)hoisted__U32_148;
    *self = hoisted__U32_148;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_149 = 1;
    (void)hoisted__U32_149;
    U32 hoisted__U32_150 = U32_sub(DEREF(self), hoisted__U32_149);
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
    Bool hoisted__Bool_248 = I64_eq(hoisted__I64_246, hoisted__I64_247);
    (void)hoisted__Bool_248;
    return hoisted__Bool_248;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_249 = U32_cmp(a, b);
    (void)hoisted__I64_249;
    I64 hoisted__I64_250 = 1;
    (void)hoisted__I64_250;
    Bool hoisted__Bool_251 = I64_eq(hoisted__I64_249, hoisted__I64_250);
    (void)hoisted__Bool_251;
    return hoisted__Bool_251;
}

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_252 = U32_eq(a, b);
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

Bool I32_neq(I32 a, I32 b) {
    Bool hoisted__Bool_430 = I32_eq(a, b);
    (void)hoisted__Bool_430;
    Bool hoisted__Bool_431 = not(hoisted__Bool_430);
    (void)hoisted__Bool_431;
    return hoisted__Bool_431;
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
            U32 hoisted__U32_705 = U32_add(_fi_USize_701, hoisted__U32_704);
            (void)hoisted__U32_705;
            _fi_USize_701 = hoisted__U32_705;
            U32 hoisted__U32_706 = Str_len(s);
            (void)hoisted__U32_706;
            U32 hoisted__U32_707 = U32_add(total, hoisted__U32_706);
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
            U32 hoisted__U32_712 = U32_add(_fi_USize_708, hoisted__U32_711);
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
    Bool hoisted__Bool_722 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_722;
    if (hoisted__Bool_722) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_723 = 0;
    (void)hoisted__I32_723;
    Bool hoisted__Bool_724 = I32_neq(c, hoisted__I32_723);
    (void)hoisted__Bool_724;
    if (hoisted__Bool_724) {
        I64 hoisted__I64_721 = (I64)(c);
        (void)hoisted__I64_721;
        { I64 _ret_val = hoisted__I64_721;
                        return _ret_val; }
    }
    I64 hoisted__I64_725 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_725;
    return hoisted__I64_725;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_726 = 1;
    (void)hoisted__U32_726;
    U32 hoisted__U64_727 = U32_add(n, hoisted__U32_726);
    (void)hoisted__U64_727;
    void * buf = malloc(hoisted__U64_727);
    I32 hoisted__I32_728 = 0;
    (void)hoisted__I32_728;
    U64 hoisted__U64_729 = 1ULL;
    (void)hoisted__U64_729;
    memset(buf, hoisted__I32_728, hoisted__U64_729);
    I64 hoisted__I64_730 = 0;
    (void)hoisted__I64_730;
    Str *hoisted__Str_731 = malloc(sizeof(Str));
    hoisted__Str_731->c_str = buf;
    hoisted__Str_731->count = hoisted__I64_730;
    hoisted__Str_731->cap = n;
    (void)hoisted__Str_731;
    return hoisted__Str_731;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_744 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_744;
    if (hoisted__Bool_744) {
        U32 hoisted__U32_734 = 1;
        (void)hoisted__U32_734;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_734);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_735 = 0;
        (void)hoisted__U32_735;
        static Str hoisted__Str_736 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_736;
        static Str hoisted__Str_737 = (Str){.c_str = (void *)"./src/core/str.til:85:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_737;
        Array__Str_set(_va_Array_18, hoisted__U32_735, &hoisted__Str_736, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_737);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_737, (Bool){0});
        static Str hoisted__Str_738 = (Str){.c_str = (void *)"./src/core/str.til:85:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_738;
        panic(_va_Array_18, &hoisted__Str_738);
        Str_delete(&hoisted__Str_738, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_745 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_745;
    if (hoisted__Bool_745) {
        U32 hoisted__U32_739 = 1;
        (void)hoisted__U32_739;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_739);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_740 = 0;
        (void)hoisted__U32_740;
        static Str hoisted__Str_741 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_741;
        static Str hoisted__Str_742 = (Str){.c_str = (void *)"./src/core/str.til:89:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_742;
        Array__Str_set(_va_Array_19, hoisted__U32_740, &hoisted__Str_741, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_742);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_742, (Bool){0});
        static Str hoisted__Str_743 = (Str){.c_str = (void *)"./src/core/str.til:89:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_743;
        panic(_va_Array_19, &hoisted__Str_743);
        Str_delete(&hoisted__Str_743, (Bool){0});
    }
    void *hoisted__v_746 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_746;
    (void)hoisted__v_746;
    memcpy(hoisted__v_746, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_747 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_747;
    (void)hoisted__v_747;
    I32 hoisted__I32_748 = 0;
    (void)hoisted__I32_748;
    U64 hoisted__U64_749 = 1ULL;
    (void)hoisted__U64_749;
    memset(hoisted__v_747, hoisted__I32_748, hoisted__U64_749);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_750 = 1;
    (void)hoisted__U32_750;
    U32 hoisted__U64_751 = U32_add(val->count, hoisted__U32_750);
    (void)hoisted__U64_751;
    void * new_data = malloc(hoisted__U64_751);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_752 = ptr_add(new_data, val->count);
    (void)hoisted__v_752;
    (void)hoisted__v_752;
    I32 hoisted__I32_753 = 0;
    (void)hoisted__I32_753;
    U64 hoisted__U64_754 = 1ULL;
    (void)hoisted__U64_754;
    memset(hoisted__v_752, hoisted__I32_753, hoisted__U64_754);
    Str *hoisted__Str_755 = malloc(sizeof(Str));
    hoisted__Str_755->c_str = new_data;
    hoisted__Str_755->count = val->count;
    hoisted__Str_755->cap = val->count;
    (void)hoisted__Str_755;
    return hoisted__Str_755;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_756 = Str_clone(self);
    (void)hoisted__Str_756;
    return hoisted__Str_756;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_757 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_757;
    if (hoisted__Bool_757) {
        free(self->c_str);
    }
    Bool hoisted__Bool_758 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_758;
    Bool hoisted__Bool_759 = and(call_free, hoisted__Bool_758);
    (void)hoisted__Bool_759;
    if (hoisted__Bool_759) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_954 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_954;
    return hoisted__U64_954;
}

U32 Str_size(void) {
    U32 hoisted__U32_1138 = 16;
    (void)hoisted__U32_1138;
    return hoisted__U32_1138;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1139 = Str_cmp(a, b);
    (void)hoisted__I64_1139;
    I64 hoisted__I64_1140 = 0;
    (void)hoisted__I64_1140;
    Bool hoisted__Bool_1141 = I64_eq(hoisted__I64_1139, hoisted__I64_1140);
    (void)hoisted__Bool_1141;
    return hoisted__Bool_1141;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1150 = Str_eq(a, b);
    (void)hoisted__Bool_1150;
    Bool hoisted__Bool_1151 = not(hoisted__Bool_1150);
    (void)hoisted__Bool_1151;
    return hoisted__Bool_1151;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1242 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1242->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1242;
    return hoisted__OutOfBounds_1242;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1243 = 0;
    (void)hoisted__Bool_1243;
    Str_delete(&self->msg, hoisted__Bool_1243);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1244 = 0;
    (void)hoisted__U32_1244;
    U64 hoisted__U64_1245 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1244); });
    (void)hoisted__U64_1245;
    return hoisted__U64_1245;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1264 = 16;
    (void)hoisted__U32_1264;
    return hoisted__U32_1264;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_1288 = 16;
    (void)hoisted__U32_1288;
    U64 hoisted__U64_1289 = (U64)(cap);
    (void)hoisted__U64_1289;
    U64 hoisted__U64_1290 = (U64)(hoisted__U32_1288);
    (void)hoisted__U64_1290;
    void * hoisted__v_1291 = calloc(hoisted__U64_1289, hoisted__U64_1290);
    (void)hoisted__v_1291;
    Array__Str *hoisted__Array__Str_1292 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1292->data = hoisted__v_1291;
    hoisted__Array__Str_1292->cap = cap;
    (void)hoisted__Array__Str_1292;
    return hoisted__Array__Str_1292;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_1293 = 16;
    (void)hoisted__U32_1293;
    U32 hoisted__U32_1294 = U32_mul(DEREF(i), hoisted__U32_1293);
    (void)hoisted__U32_1294;
    U64 hoisted__U64_1295 = (U64)(hoisted__U32_1294);
    (void)hoisted__U64_1295;
    void *hoisted__v_1296 = ptr_add(self->data, hoisted__U64_1295);
    (void)hoisted__v_1296;
    (void)hoisted__v_1296;
    return hoisted__v_1296;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_1323 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1323;
    (void)hoisted__Str_1323;
    Bool hoisted__Bool_1324 = 0;
    (void)hoisted__Bool_1324;
    Str_delete(hoisted__Str_1323, hoisted__Bool_1324);
    U32 hoisted__U32_1325 = 16;
    (void)hoisted__U32_1325;
    Str *hoisted__Str_1326 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1326;
    (void)hoisted__Str_1326;
    U64 hoisted__U64_1327 = (U64)(hoisted__U32_1325);
    (void)hoisted__U64_1327;
    memcpy(hoisted__Str_1326, val, hoisted__U64_1327);
    U32 hoisted__U32_1328 = 16;
    (void)hoisted__U32_1328;
    I32 hoisted__I32_1329 = 0;
    (void)hoisted__I32_1329;
    U64 hoisted__U64_1330 = (U64)(hoisted__U32_1328);
    (void)hoisted__U64_1330;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1329, hoisted__U64_1330); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1353 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1353;
    if (hoisted__Bool_1353) {
        U32 hoisted__U32_1331 = 6;
        (void)hoisted__U32_1331;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1331);
        (void)_va_Array_31;
        I64 _va_Array_31_ek = 0;
        (void)_va_Array_31_ek;
        OutOfBounds *_va_Array_31_eo = malloc(sizeof(OutOfBounds));
        _va_Array_31_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_31_eo;
        U32 hoisted__U32_1332 = 0;
        (void)hoisted__U32_1332;
        Str *hoisted__Str_1333 = Str_clone(loc);
        (void)hoisted__Str_1333;
        static Str hoisted__Str_1334 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1334;
        Array__Str_set(_va_Array_31, hoisted__U32_1332, hoisted__Str_1333, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1334);
        Str_delete(&hoisted__Str_1334, (Bool){0});
        U32 hoisted__U32_1335 = 1;
        (void)hoisted__U32_1335;
        static Str hoisted__Str_1336 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1336;
        static Str hoisted__Str_1337 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1337;
        Array__Str_set(_va_Array_31, hoisted__U32_1335, &hoisted__Str_1336, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1337);
        Str_delete(&hoisted__Str_1337, (Bool){0});
        U32 hoisted__U32_1338 = 2;
        (void)hoisted__U32_1338;
        Str *hoisted__Str_1339 = U32_to_str(i);
        (void)hoisted__Str_1339;
        static Str hoisted__Str_1340 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1340;
        Array__Str_set(_va_Array_31, hoisted__U32_1338, hoisted__Str_1339, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1340);
        Str_delete(&hoisted__Str_1340, (Bool){0});
        U32 hoisted__U32_1341 = 3;
        (void)hoisted__U32_1341;
        static Str hoisted__Str_1342 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1342;
        static Str hoisted__Str_1343 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1343;
        Array__Str_set(_va_Array_31, hoisted__U32_1341, &hoisted__Str_1342, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1343);
        Str_delete(&hoisted__Str_1343, (Bool){0});
        U32 hoisted__U32_1344 = 4;
        (void)hoisted__U32_1344;
        Str *hoisted__Str_1345 = U32_to_str(self->cap);
        (void)hoisted__Str_1345;
        static Str hoisted__Str_1346 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1346;
        Array__Str_set(_va_Array_31, hoisted__U32_1344, hoisted__Str_1345, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1346);
        Str_delete(&hoisted__Str_1346, (Bool){0});
        U32 hoisted__U32_1347 = 5;
        (void)hoisted__U32_1347;
        static Str hoisted__Str_1348 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1348;
        static Str hoisted__Str_1349 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1349;
        Array__Str_set(_va_Array_31, hoisted__U32_1347, &hoisted__Str_1348, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1349);
        OutOfBounds_delete(_va_Array_31_eo, 1);
        Str_delete(&hoisted__Str_1349, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1350 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_31); hoisted__OutOfBounds_1350->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1350;
        U32 hoisted__U32_1351 = 16;
        (void)hoisted__U32_1351;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1350, hoisted__U32_1351);
        OutOfBounds_delete(hoisted__OutOfBounds_1350, 1);
        I64 hoisted__I64_1352 = 3;
        (void)hoisted__I64_1352;
        *_err_kind = hoisted__I64_1352;
    }
    I64 hoisted__I64_1354 = 0;
    (void)hoisted__I64_1354;
    Bool hoisted__Bool_1355 = I64_eq(DEREF(_err_kind), hoisted__I64_1354);
    (void)hoisted__Bool_1355;
    if (hoisted__Bool_1355) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1356 = self->cap;
        (void)_re_U32_1356;
        U32 _rc_U32_1356 = 0;
        (void)_rc_U32_1356;
        Bool hoisted__Bool_1369 = U32_lte(_rc_U32_1356, _re_U32_1356);
        (void)hoisted__Bool_1369;
        if (hoisted__Bool_1369) {
            while (1) {
                Bool _wcond_Bool_1357 = U32_lt(_rc_U32_1356, _re_U32_1356);
                (void)_wcond_Bool_1357;
                if (_wcond_Bool_1357) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1356);
                U32_inc(&_rc_U32_1356);
                U32 hoisted__U32_1358 = 16;
                (void)hoisted__U32_1358;
                U32 hoisted__U32_1359 = U32_mul(i, hoisted__U32_1358);
                (void)hoisted__U32_1359;
                U64 hoisted__U64_1360 = (U64)(hoisted__U32_1359);
                (void)hoisted__U64_1360;
                Str *hoisted__Str_1361 = ptr_add(self->data, hoisted__U64_1360);
                (void)hoisted__Str_1361;
                (void)hoisted__Str_1361;
                Bool hoisted__Bool_1362 = 0;
                (void)hoisted__Bool_1362;
                Str_delete(hoisted__Str_1361, hoisted__Bool_1362);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1363 = U32_gt(_rc_U32_1356, _re_U32_1356);
                (void)_wcond_Bool_1363;
                if (_wcond_Bool_1363) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1356);
                U32_dec(&_rc_U32_1356);
                U32 hoisted__U32_1364 = 16;
                (void)hoisted__U32_1364;
                U32 hoisted__U32_1365 = U32_mul(i, hoisted__U32_1364);
                (void)hoisted__U32_1365;
                U64 hoisted__U64_1366 = (U64)(hoisted__U32_1365);
                (void)hoisted__U64_1366;
                Str *hoisted__Str_1367 = ptr_add(self->data, hoisted__U64_1366);
                (void)hoisted__Str_1367;
                (void)hoisted__Str_1367;
                Bool hoisted__Bool_1368 = 0;
                (void)hoisted__Bool_1368;
                Str_delete(hoisted__Str_1367, hoisted__Bool_1368);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1398 = 16;
    (void)hoisted__U32_1398;
    U32 hoisted__U32_1399 = U32_mul(self->cap, hoisted__U32_1398);
    (void)hoisted__U32_1399;
    U64 hoisted__U64_1400 = (U64)(hoisted__U32_1399);
    (void)hoisted__U64_1400;
    void * new_data = malloc(hoisted__U64_1400);
    {
        U32 _re_U32_1370 = self->cap;
        (void)_re_U32_1370;
        U32 _rc_U32_1370 = 0;
        (void)_rc_U32_1370;
        Bool hoisted__Bool_1397 = U32_lte(_rc_U32_1370, _re_U32_1370);
        (void)hoisted__Bool_1397;
        if (hoisted__Bool_1397) {
            while (1) {
                Bool _wcond_Bool_1371 = U32_lt(_rc_U32_1370, _re_U32_1370);
                (void)_wcond_Bool_1371;
                if (_wcond_Bool_1371) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1370);
                U32_inc(&_rc_U32_1370);
                U32 hoisted__U32_1372 = 16;
                (void)hoisted__U32_1372;
                U32 hoisted__U32_1373 = U32_mul(i, hoisted__U32_1372);
                (void)hoisted__U32_1373;
                U64 hoisted__U64_1374 = (U64)(hoisted__U32_1373);
                (void)hoisted__U64_1374;
                Str *src = ptr_add(self->data, hoisted__U64_1374);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1375 = 16;
                (void)hoisted__U32_1375;
                U32 hoisted__U32_1376 = U32_mul(i, hoisted__U32_1375);
                (void)hoisted__U32_1376;
                U64 hoisted__U64_1377 = (U64)(hoisted__U32_1376);
                (void)hoisted__U64_1377;
                U32 hoisted__U32_1378 = 16;
                (void)hoisted__U32_1378;
                void *hoisted__v_1379 = ptr_add(new_data, hoisted__U64_1377);
                (void)hoisted__v_1379;
                (void)hoisted__v_1379;
                U64 hoisted__U64_1380 = (U64)(hoisted__U32_1378);
                (void)hoisted__U64_1380;
                memcpy(hoisted__v_1379, cloned, hoisted__U64_1380);
                U32 hoisted__U32_1381 = 16;
                (void)hoisted__U32_1381;
                I32 hoisted__I32_1382 = 0;
                (void)hoisted__I32_1382;
                U64 hoisted__U64_1383 = (U64)(hoisted__U32_1381);
                (void)hoisted__U64_1383;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1382, hoisted__U64_1383); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1384 = U32_gt(_rc_U32_1370, _re_U32_1370);
                (void)_wcond_Bool_1384;
                if (_wcond_Bool_1384) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1370);
                U32_dec(&_rc_U32_1370);
                U32 hoisted__U32_1385 = 16;
                (void)hoisted__U32_1385;
                U32 hoisted__U32_1386 = U32_mul(i, hoisted__U32_1385);
                (void)hoisted__U32_1386;
                U64 hoisted__U64_1387 = (U64)(hoisted__U32_1386);
                (void)hoisted__U64_1387;
                Str *src = ptr_add(self->data, hoisted__U64_1387);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1388 = 16;
                (void)hoisted__U32_1388;
                U32 hoisted__U32_1389 = U32_mul(i, hoisted__U32_1388);
                (void)hoisted__U32_1389;
                U64 hoisted__U64_1390 = (U64)(hoisted__U32_1389);
                (void)hoisted__U64_1390;
                U32 hoisted__U32_1391 = 16;
                (void)hoisted__U32_1391;
                void *hoisted__v_1392 = ptr_add(new_data, hoisted__U64_1390);
                (void)hoisted__v_1392;
                (void)hoisted__v_1392;
                U64 hoisted__U64_1393 = (U64)(hoisted__U32_1391);
                (void)hoisted__U64_1393;
                memcpy(hoisted__v_1392, cloned, hoisted__U64_1393);
                U32 hoisted__U32_1394 = 16;
                (void)hoisted__U32_1394;
                I32 hoisted__I32_1395 = 0;
                (void)hoisted__I32_1395;
                U64 hoisted__U64_1396 = (U64)(hoisted__U32_1394);
                (void)hoisted__U64_1396;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1395, hoisted__U64_1396); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1401 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1401->data = new_data;
    hoisted__Array__Str_1401->cap = self->cap;
    (void)hoisted__Array__Str_1401;
    return hoisted__Array__Str_1401;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1402 = 16;
    (void)hoisted__U32_1402;
    return hoisted__U32_1402;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1403 = 16;
    (void)hoisted__U32_1403;
    U64 hoisted__U64_1404 = (U64)(hoisted__U32_1403);
    (void)hoisted__U64_1404;
    void * hoisted__v_1405 = malloc(hoisted__U64_1404);
    (void)hoisted__v_1405;
    U32 hoisted__U32_1406 = 0;
    (void)hoisted__U32_1406;
    I64 hoisted__I64_1407 = 1;
    (void)hoisted__I64_1407;
    Vec__Str *hoisted__Vec__Str_1408 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1408->data = hoisted__v_1405;
    hoisted__Vec__Str_1408->count = hoisted__U32_1406;
    hoisted__Vec__Str_1408->cap = hoisted__I64_1407;
    (void)hoisted__Vec__Str_1408;
    return hoisted__Vec__Str_1408;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1409 = self->count;
        (void)_re_U32_1409;
        U32 _rc_U32_1409 = 0;
        (void)_rc_U32_1409;
        Bool hoisted__Bool_1422 = U32_lte(_rc_U32_1409, _re_U32_1409);
        (void)hoisted__Bool_1422;
        if (hoisted__Bool_1422) {
            while (1) {
                Bool _wcond_Bool_1410 = U32_lt(_rc_U32_1409, _re_U32_1409);
                (void)_wcond_Bool_1410;
                if (_wcond_Bool_1410) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1409);
                U32_inc(&_rc_U32_1409);
                U32 hoisted__U32_1411 = 16;
                (void)hoisted__U32_1411;
                U32 hoisted__U32_1412 = U32_mul(i, hoisted__U32_1411);
                (void)hoisted__U32_1412;
                U64 hoisted__U64_1413 = (U64)(hoisted__U32_1412);
                (void)hoisted__U64_1413;
                Str *hoisted__Str_1414 = ptr_add(self->data, hoisted__U64_1413);
                (void)hoisted__Str_1414;
                (void)hoisted__Str_1414;
                Bool hoisted__Bool_1415 = 0;
                (void)hoisted__Bool_1415;
                Str_delete(hoisted__Str_1414, hoisted__Bool_1415);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1416 = U32_gt(_rc_U32_1409, _re_U32_1409);
                (void)_wcond_Bool_1416;
                if (_wcond_Bool_1416) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1409);
                U32_dec(&_rc_U32_1409);
                U32 hoisted__U32_1417 = 16;
                (void)hoisted__U32_1417;
                U32 hoisted__U32_1418 = U32_mul(i, hoisted__U32_1417);
                (void)hoisted__U32_1418;
                U64 hoisted__U64_1419 = (U64)(hoisted__U32_1418);
                (void)hoisted__U64_1419;
                Str *hoisted__Str_1420 = ptr_add(self->data, hoisted__U64_1419);
                (void)hoisted__Str_1420;
                (void)hoisted__Str_1420;
                Bool hoisted__Bool_1421 = 0;
                (void)hoisted__Bool_1421;
                Str_delete(hoisted__Str_1420, hoisted__Bool_1421);
            }
        }
    }
    U32 hoisted__U32_1423 = 0;
    (void)hoisted__U32_1423;
    self->count = hoisted__U32_1423;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1693 = 16;
    (void)hoisted__U32_1693;
    U32 hoisted__U32_1694 = U32_mul(self->cap, hoisted__U32_1693);
    (void)hoisted__U32_1694;
    U64 hoisted__U64_1695 = (U64)(hoisted__U32_1694);
    (void)hoisted__U64_1695;
    void * new_data = malloc(hoisted__U64_1695);
    {
        U32 _re_U32_1665 = self->count;
        (void)_re_U32_1665;
        U32 _rc_U32_1665 = 0;
        (void)_rc_U32_1665;
        Bool hoisted__Bool_1692 = U32_lte(_rc_U32_1665, _re_U32_1665);
        (void)hoisted__Bool_1692;
        if (hoisted__Bool_1692) {
            while (1) {
                Bool _wcond_Bool_1666 = U32_lt(_rc_U32_1665, _re_U32_1665);
                (void)_wcond_Bool_1666;
                if (_wcond_Bool_1666) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1665);
                U32_inc(&_rc_U32_1665);
                U32 hoisted__U32_1667 = 16;
                (void)hoisted__U32_1667;
                U32 hoisted__U32_1668 = U32_mul(i, hoisted__U32_1667);
                (void)hoisted__U32_1668;
                U64 hoisted__U64_1669 = (U64)(hoisted__U32_1668);
                (void)hoisted__U64_1669;
                Str *src = ptr_add(self->data, hoisted__U64_1669);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1670 = 16;
                (void)hoisted__U32_1670;
                U32 hoisted__U32_1671 = U32_mul(i, hoisted__U32_1670);
                (void)hoisted__U32_1671;
                U64 hoisted__U64_1672 = (U64)(hoisted__U32_1671);
                (void)hoisted__U64_1672;
                U32 hoisted__U32_1673 = 16;
                (void)hoisted__U32_1673;
                void *hoisted__v_1674 = ptr_add(new_data, hoisted__U64_1672);
                (void)hoisted__v_1674;
                (void)hoisted__v_1674;
                U64 hoisted__U64_1675 = (U64)(hoisted__U32_1673);
                (void)hoisted__U64_1675;
                memcpy(hoisted__v_1674, cloned, hoisted__U64_1675);
                U32 hoisted__U32_1676 = 16;
                (void)hoisted__U32_1676;
                I32 hoisted__I32_1677 = 0;
                (void)hoisted__I32_1677;
                U64 hoisted__U64_1678 = (U64)(hoisted__U32_1676);
                (void)hoisted__U64_1678;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1677, hoisted__U64_1678); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1679 = U32_gt(_rc_U32_1665, _re_U32_1665);
                (void)_wcond_Bool_1679;
                if (_wcond_Bool_1679) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1665);
                U32_dec(&_rc_U32_1665);
                U32 hoisted__U32_1680 = 16;
                (void)hoisted__U32_1680;
                U32 hoisted__U32_1681 = U32_mul(i, hoisted__U32_1680);
                (void)hoisted__U32_1681;
                U64 hoisted__U64_1682 = (U64)(hoisted__U32_1681);
                (void)hoisted__U64_1682;
                Str *src = ptr_add(self->data, hoisted__U64_1682);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1683 = 16;
                (void)hoisted__U32_1683;
                U32 hoisted__U32_1684 = U32_mul(i, hoisted__U32_1683);
                (void)hoisted__U32_1684;
                U64 hoisted__U64_1685 = (U64)(hoisted__U32_1684);
                (void)hoisted__U64_1685;
                U32 hoisted__U32_1686 = 16;
                (void)hoisted__U32_1686;
                void *hoisted__v_1687 = ptr_add(new_data, hoisted__U64_1685);
                (void)hoisted__v_1687;
                (void)hoisted__v_1687;
                U64 hoisted__U64_1688 = (U64)(hoisted__U32_1686);
                (void)hoisted__U64_1688;
                memcpy(hoisted__v_1687, cloned, hoisted__U64_1688);
                U32 hoisted__U32_1689 = 16;
                (void)hoisted__U32_1689;
                I32 hoisted__I32_1690 = 0;
                (void)hoisted__I32_1690;
                U64 hoisted__U64_1691 = (U64)(hoisted__U32_1689);
                (void)hoisted__U64_1691;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1690, hoisted__U64_1691); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1696 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1696->data = new_data;
    hoisted__Vec__Str_1696->count = self->count;
    hoisted__Vec__Str_1696->cap = self->cap;
    (void)hoisted__Vec__Str_1696;
    return hoisted__Vec__Str_1696;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1697 = 16;
    (void)hoisted__U32_1697;
    return hoisted__U32_1697;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1700 = 8;
    (void)hoisted__U32_1700;
    return hoisted__U32_1700;
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
    I64 hoisted__I64_1912 = 0;
    (void)hoisted__I64_1912;
    Bool hoisted__Bool_1913 = I64_eq(val, hoisted__I64_1912);
    (void)hoisted__Bool_1913;
    if (hoisted__Bool_1913) {
        U64 hoisted__U64_1882 = 2ULL;
        (void)hoisted__U64_1882;
        void * buf = malloc(hoisted__U64_1882);
        I64 hoisted__I64_1883 = 48;
        (void)hoisted__I64_1883;
        U64 hoisted__U64_1884 = 1ULL;
        (void)hoisted__U64_1884;
        memcpy(buf, &hoisted__I64_1883, hoisted__U64_1884);
        U64 hoisted__U64_1885 = 1ULL;
        (void)hoisted__U64_1885;
        void *hoisted__v_1886 = ptr_add(buf, hoisted__U64_1885);
        (void)hoisted__v_1886;
        (void)hoisted__v_1886;
        I32 hoisted__I32_1887 = 0;
        (void)hoisted__I32_1887;
        U64 hoisted__U64_1888 = 1ULL;
        (void)hoisted__U64_1888;
        memset(hoisted__v_1886, hoisted__I32_1887, hoisted__U64_1888);
        I64 hoisted__I64_1889 = 1;
        (void)hoisted__I64_1889;
        I64 hoisted__I64_1890 = 1;
        (void)hoisted__I64_1890;
        Str *hoisted__Str_1891 = malloc(sizeof(Str));
        hoisted__Str_1891->c_str = buf;
        hoisted__Str_1891->count = hoisted__I64_1889;
        hoisted__Str_1891->cap = hoisted__I64_1890;
        (void)hoisted__Str_1891;
        { Str * _ret_val = hoisted__Str_1891;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1914 = 0;
    (void)hoisted__I64_1914;
    Bool hoisted__Bool_1915 = I64_lt(val, hoisted__I64_1914);
    (void)hoisted__Bool_1915;
    if (hoisted__Bool_1915) {
        Bool hoisted__Bool_1892 = 1;
        (void)hoisted__Bool_1892;
        is_neg = hoisted__Bool_1892;
        I64 hoisted__I64_1893 = 0;
        (void)hoisted__I64_1893;
        I64 hoisted__I64_1894 = I64_sub(hoisted__I64_1893, val);
        (void)hoisted__I64_1894;
        v = hoisted__I64_1894;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1896 = 0;
        (void)hoisted__I64_1896;
        Bool _wcond_Bool_1895 = I64_gt(tmp, hoisted__I64_1896);
        (void)_wcond_Bool_1895;
        if (_wcond_Bool_1895) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1897 = 10;
        (void)hoisted__I64_1897;
        I64 hoisted__I64_1898 = I64_div(tmp, hoisted__I64_1897);
        (void)hoisted__I64_1898;
        tmp = hoisted__I64_1898;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1916 = 1ULL;
    (void)hoisted__U64_1916;
    U64 hoisted__U64_1917 = U64_add(total, hoisted__U64_1916);
    (void)hoisted__U64_1917;
    void * buf = malloc(hoisted__U64_1917);
    if (is_neg) {
        I64 hoisted__I64_1899 = 45;
        (void)hoisted__I64_1899;
        U64 hoisted__U64_1900 = 1ULL;
        (void)hoisted__U64_1900;
        memcpy(buf, &hoisted__I64_1899, hoisted__U64_1900);
    }
    U64 hoisted__U64_1918 = 1ULL;
    (void)hoisted__U64_1918;
    U64 i = U64_sub(total, hoisted__U64_1918);
    while (1) {
        I64 hoisted__I64_1902 = 0;
        (void)hoisted__I64_1902;
        Bool _wcond_Bool_1901 = I64_gt(v, hoisted__I64_1902);
        (void)_wcond_Bool_1901;
        if (_wcond_Bool_1901) {
        } else {
            break;
        }
        I64 hoisted__I64_1903 = 10;
        (void)hoisted__I64_1903;
        I64 hoisted__I64_1904 = I64_mod(v, hoisted__I64_1903);
        (void)hoisted__I64_1904;
        I64 hoisted__I64_1905 = 48;
        (void)hoisted__I64_1905;
        I64 hoisted__I64_1906 = I64_add(hoisted__I64_1904, hoisted__I64_1905);
        (void)hoisted__I64_1906;
        void *hoisted__v_1907 = ptr_add(buf, i);
        (void)hoisted__v_1907;
        (void)hoisted__v_1907;
        U8 hoisted__U8_1908 = I64_to_u8(hoisted__I64_1906);
        (void)hoisted__U8_1908;
        U64 hoisted__U64_1909 = 1ULL;
        (void)hoisted__U64_1909;
        memcpy(hoisted__v_1907, &hoisted__U8_1908, hoisted__U64_1909);
        I64 hoisted__I64_1910 = 10;
        (void)hoisted__I64_1910;
        I64 hoisted__I64_1911 = I64_div(v, hoisted__I64_1910);
        (void)hoisted__I64_1911;
        v = hoisted__I64_1911;
        U64_dec(&i);
    }
    void *hoisted__v_1919 = ptr_add(buf, total);
    (void)hoisted__v_1919;
    (void)hoisted__v_1919;
    I32 hoisted__I32_1920 = 0;
    (void)hoisted__I32_1920;
    U64 hoisted__U64_1921 = 1ULL;
    (void)hoisted__U64_1921;
    memset(hoisted__v_1919, hoisted__I32_1920, hoisted__U64_1921);
    Str *hoisted__Str_1922 = malloc(sizeof(Str));
    hoisted__Str_1922->c_str = buf;
    hoisted__Str_1922->count = total;
    hoisted__Str_1922->cap = total;
    (void)hoisted__Str_1922;
    return hoisted__Str_1922;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1940 = 8;
    (void)hoisted__U32_1940;
    return hoisted__U32_1940;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2098 = 0;
    (void)hoisted__U32_2098;
    U64 hoisted__U64_2099 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2098); });
    (void)hoisted__U64_2099;
    return hoisted__U64_2099;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2102 = I64_cmp(a, b);
    (void)hoisted__I64_2102;
    I64 hoisted__I64_2103 = -1;
    (void)hoisted__I64_2103;
    Bool hoisted__Bool_2104 = I64_eq(hoisted__I64_2102, hoisted__I64_2103);
    (void)hoisted__Bool_2104;
    return hoisted__Bool_2104;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2105 = I64_cmp(a, b);
    (void)hoisted__I64_2105;
    I64 hoisted__I64_2106 = 1;
    (void)hoisted__I64_2106;
    Bool hoisted__Bool_2107 = I64_eq(hoisted__I64_2105, hoisted__I64_2106);
    (void)hoisted__Bool_2107;
    return hoisted__Bool_2107;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2108 = I64_eq(a, b);
    (void)hoisted__Bool_2108;
    Bool hoisted__Bool_2109 = not(hoisted__Bool_2108);
    (void)hoisted__Bool_2109;
    return hoisted__Bool_2109;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2160 = 0;
    (void)_m_Bool_2160;
    {
        Bool hoisted__Bool_2163 = 1;
        (void)hoisted__Bool_2163;
        Bool hoisted__Bool_2164 = Bool_eq(a, hoisted__Bool_2163);
        (void)hoisted__Bool_2164;
        if (hoisted__Bool_2164) {
            Bool hoisted__Bool_2161 = Bool_clone(&b);
            (void)hoisted__Bool_2161;
            _m_Bool_2160 = hoisted__Bool_2161;
        } else {
            Bool hoisted__Bool_2162 = 0;
            (void)hoisted__Bool_2162;
            _m_Bool_2160 = hoisted__Bool_2162;
        }
    }
    return _m_Bool_2160;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2174 = Bool_eq(a, b);
    (void)hoisted__Bool_2174;
    if (hoisted__Bool_2174) {
        I64 hoisted__I64_2172 = 0;
        (void)hoisted__I64_2172;
        { I64 _ret_val = hoisted__I64_2172;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2173 = -1;
        (void)hoisted__I64_2173;
        return hoisted__I64_2173;
    }
    I64 hoisted__I64_2175 = 1;
    (void)hoisted__I64_2175;
    return hoisted__I64_2175;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2176 = 1;
    (void)hoisted__U32_2176;
    return hoisted__U32_2176;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2177 = 0;
    (void)hoisted__U32_2177;
    U64 hoisted__U64_2178 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2177); });
    (void)hoisted__U64_2178;
    return hoisted__U64_2178;
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
    Bool hoisted__Bool_2204 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2204;
    if (hoisted__Bool_2204) {
        Bool hoisted__Bool_2194 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2194;
        { Bool _ret_val = hoisted__Bool_2194;
                return _ret_val; }
    }
    Bool hoisted__Bool_2205 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        Bool hoisted__Bool_2195 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2195;
        { Bool _ret_val = hoisted__Bool_2195;
                return _ret_val; }
    }
    Bool hoisted__Bool_2206 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2206;
    if (hoisted__Bool_2206) {
        Bool hoisted__Bool_2196 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2196;
        { Bool _ret_val = hoisted__Bool_2196;
                return _ret_val; }
    }
    Bool hoisted__Bool_2207 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2207;
    if (hoisted__Bool_2207) {
        Bool hoisted__Bool_2197 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2197;
        { Bool _ret_val = hoisted__Bool_2197;
                return _ret_val; }
    }
    Bool hoisted__Bool_2208 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2208;
    if (hoisted__Bool_2208) {
        Bool hoisted__Bool_2198 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2198;
        { Bool _ret_val = hoisted__Bool_2198;
                return _ret_val; }
    }
    Bool hoisted__Bool_2209 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2209;
    if (hoisted__Bool_2209) {
        Bool hoisted__Bool_2199 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2199;
        { Bool _ret_val = hoisted__Bool_2199;
                return _ret_val; }
    }
    Bool hoisted__Bool_2210 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2210;
    if (hoisted__Bool_2210) {
        Bool hoisted__Bool_2200 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2200;
        { Bool _ret_val = hoisted__Bool_2200;
                return _ret_val; }
    }
    Bool hoisted__Bool_2211 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2211;
    if (hoisted__Bool_2211) {
        Bool hoisted__Bool_2201 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2201;
        { Bool _ret_val = hoisted__Bool_2201;
                return _ret_val; }
    }
    Bool hoisted__Bool_2212 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2212;
    if (hoisted__Bool_2212) {
        Bool hoisted__Bool_2202 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2202;
        { Bool _ret_val = hoisted__Bool_2202;
                return _ret_val; }
    }
    Bool hoisted__Bool_2213 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2213;
    if (hoisted__Bool_2213) {
        Bool hoisted__Bool_2203 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2203;
        { Bool _ret_val = hoisted__Bool_2203;
                return _ret_val; }
    }
    Bool hoisted__Bool_2214 = 0;
    (void)hoisted__Bool_2214;
    return hoisted__Bool_2214;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2236 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2236;
    if (hoisted__Bool_2236) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2237 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2237;
    if (hoisted__Bool_2237) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2238 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2238;
    if (hoisted__Bool_2238) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2239 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2239;
    if (hoisted__Bool_2239) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2240 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2240;
    if (hoisted__Bool_2240) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2241 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2241;
    if (hoisted__Bool_2241) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2242 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2243 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2243;
    if (hoisted__Bool_2243) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2244 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2245 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2245;
    if (hoisted__Bool_2245) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2246 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2246;
    UNREACHABLE(&hoisted__Str_2246);
    Str_delete(&hoisted__Str_2246, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2247 = 4;
    (void)hoisted__U32_2247;
    return hoisted__U32_2247;
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
    Bool hoisted__Bool_2299 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2299;
    if (hoisted__Bool_2299) {
        Str *hoisted__Str_2289 = get_payload(self);
        (void)hoisted__Str_2289;
        (void)hoisted__Str_2289;
        Bool hoisted__Bool_2290 = 0;
        (void)hoisted__Bool_2290;
        Str_delete(hoisted__Str_2289, hoisted__Bool_2290);
    }
    Bool hoisted__Bool_2300 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2300;
    if (hoisted__Bool_2300) {
        Str *hoisted__Str_2291 = get_payload(self);
        (void)hoisted__Str_2291;
        (void)hoisted__Str_2291;
        Bool hoisted__Bool_2292 = 0;
        (void)hoisted__Bool_2292;
        Str_delete(hoisted__Str_2291, hoisted__Bool_2292);
    }
    Bool hoisted__Bool_2301 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2301;
    if (hoisted__Bool_2301) {
        Str *hoisted__Str_2293 = get_payload(self);
        (void)hoisted__Str_2293;
        (void)hoisted__Str_2293;
        Bool hoisted__Bool_2294 = 0;
        (void)hoisted__Bool_2294;
        Str_delete(hoisted__Str_2293, hoisted__Bool_2294);
    }
    Bool hoisted__Bool_2302 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2302;
    if (hoisted__Bool_2302) {
        Primitive *hoisted__Primitive_2295 = get_payload(self);
        (void)hoisted__Primitive_2295;
        (void)hoisted__Primitive_2295;
        Bool hoisted__Bool_2296 = 0;
        (void)hoisted__Bool_2296;
        Primitive_delete(hoisted__Primitive_2295, hoisted__Bool_2296);
    }
    Bool hoisted__Bool_2303 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2303;
    if (hoisted__Bool_2303) {
        Str *hoisted__Str_2297 = get_payload(self);
        (void)hoisted__Str_2297;
        (void)hoisted__Str_2297;
        Bool hoisted__Bool_2298 = 0;
        (void)hoisted__Bool_2298;
        Str_delete(hoisted__Str_2297, hoisted__Bool_2298);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2387 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2387;
    if (hoisted__Bool_2387) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2388 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2388;
    if (hoisted__Bool_2388) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2389 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2389;
    if (hoisted__Bool_2389) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2379 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2379;
        Type *hoisted__Type_2380 = Type_Struct(hoisted__Str_2379);
        (void)hoisted__Type_2380;
        { Type * _ret_val = hoisted__Type_2380;
                return _ret_val; }
    }
    Bool hoisted__Bool_2390 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2390;
    if (hoisted__Bool_2390) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2391 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2391;
    if (hoisted__Bool_2391) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2381 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2381;
        Type *hoisted__Type_2382 = Type_Enum(hoisted__Str_2381);
        (void)hoisted__Type_2382;
        { Type * _ret_val = hoisted__Type_2382;
                return _ret_val; }
    }
    Bool hoisted__Bool_2392 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2392;
    if (hoisted__Bool_2392) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2393 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2393;
    if (hoisted__Bool_2393) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2394 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2394;
    if (hoisted__Bool_2394) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2395 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2395;
    if (hoisted__Bool_2395) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2396 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2396;
    if (hoisted__Bool_2396) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2383 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2383;
        Type *hoisted__Type_2384 = Type_Custom(hoisted__Str_2383);
        (void)hoisted__Type_2384;
        { Type * _ret_val = hoisted__Type_2384;
                return _ret_val; }
    }
    Bool hoisted__Bool_2397 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2397;
    if (hoisted__Bool_2397) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2385 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2385;
        Type *hoisted__Type_2386 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2385; _oa; }));
        (void)hoisted__Type_2386;
        { Type * _ret_val = hoisted__Type_2386;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2398 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2398;
    Type *hoisted__Type_2399 = Type_FuncPtrSig(hoisted__Str_2398);
    (void)hoisted__Type_2399;
    return hoisted__Type_2399;
}

U32 Type_size(void) {
    U32 hoisted__U32_2400 = 24;
    (void)hoisted__U32_2400;
    return hoisted__U32_2400;
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
    Bool hoisted__Bool_2503 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2503;
    if (hoisted__Bool_2503) {
        Bool hoisted__Bool_2493 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2493;
        { Bool _ret_val = hoisted__Bool_2493;
                return _ret_val; }
    }
    Bool hoisted__Bool_2504 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2504;
    if (hoisted__Bool_2504) {
        Bool hoisted__Bool_2494 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2494;
        { Bool _ret_val = hoisted__Bool_2494;
                return _ret_val; }
    }
    Bool hoisted__Bool_2505 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2505;
    if (hoisted__Bool_2505) {
        Bool hoisted__Bool_2495 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2495;
        { Bool _ret_val = hoisted__Bool_2495;
                return _ret_val; }
    }
    Bool hoisted__Bool_2506 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2506;
    if (hoisted__Bool_2506) {
        Bool hoisted__Bool_2496 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2496;
        { Bool _ret_val = hoisted__Bool_2496;
                return _ret_val; }
    }
    Bool hoisted__Bool_2507 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2507;
    if (hoisted__Bool_2507) {
        Bool hoisted__Bool_2497 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2497;
        { Bool _ret_val = hoisted__Bool_2497;
                return _ret_val; }
    }
    Bool hoisted__Bool_2508 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2508;
    if (hoisted__Bool_2508) {
        Bool hoisted__Bool_2498 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2498;
        { Bool _ret_val = hoisted__Bool_2498;
                return _ret_val; }
    }
    Bool hoisted__Bool_2509 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2509;
    if (hoisted__Bool_2509) {
        Bool hoisted__Bool_2499 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2499;
        { Bool _ret_val = hoisted__Bool_2499;
                return _ret_val; }
    }
    Bool hoisted__Bool_2510 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2510;
    if (hoisted__Bool_2510) {
        Bool hoisted__Bool_2500 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2500;
        { Bool _ret_val = hoisted__Bool_2500;
                return _ret_val; }
    }
    Bool hoisted__Bool_2511 = is(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2511;
    if (hoisted__Bool_2511) {
        Bool hoisted__Bool_2501 = is(other, &(FuncType){.tag = FuncType_TAG_CoreFunc});
        (void)hoisted__Bool_2501;
        { Bool _ret_val = hoisted__Bool_2501;
                return _ret_val; }
    }
    Bool hoisted__Bool_2512 = is(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2512;
    if (hoisted__Bool_2512) {
        Bool hoisted__Bool_2502 = is(other, &(FuncType){.tag = FuncType_TAG_CoreProc});
        (void)hoisted__Bool_2502;
        { Bool _ret_val = hoisted__Bool_2502;
                return _ret_val; }
    }
    Bool hoisted__Bool_2513 = 0;
    (void)hoisted__Bool_2513;
    return hoisted__Bool_2513;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2535 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2535;
    if (hoisted__Bool_2535) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2536 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2536;
    if (hoisted__Bool_2536) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2537 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2537;
    if (hoisted__Bool_2537) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2538 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2538;
    if (hoisted__Bool_2538) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2539 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2539;
    if (hoisted__Bool_2539) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2540 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2540;
    if (hoisted__Bool_2540) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2541 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2541;
    if (hoisted__Bool_2541) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2542 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2542;
    if (hoisted__Bool_2542) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2543 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2543;
    if (hoisted__Bool_2543) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2544 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2544;
    if (hoisted__Bool_2544) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2545 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2545;
    UNREACHABLE(&hoisted__Str_2545);
    Str_delete(&hoisted__Str_2545, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2546 = 4;
    (void)hoisted__U32_2546;
    return hoisted__U32_2546;
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
    Bool hoisted__Bool_2551 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2551;
    if (hoisted__Bool_2551) {
        Bool hoisted__Bool_2548 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2548;
        { Bool _ret_val = hoisted__Bool_2548;
                return _ret_val; }
    }
    Bool hoisted__Bool_2552 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2552;
    if (hoisted__Bool_2552) {
        Bool hoisted__Bool_2549 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2549;
        { Bool _ret_val = hoisted__Bool_2549;
                return _ret_val; }
    }
    Bool hoisted__Bool_2553 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2553;
    if (hoisted__Bool_2553) {
        Bool hoisted__Bool_2550 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2550;
        { Bool _ret_val = hoisted__Bool_2550;
                return _ret_val; }
    }
    Bool hoisted__Bool_2554 = 0;
    (void)hoisted__Bool_2554;
    return hoisted__Bool_2554;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2562 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2562;
    if (hoisted__Bool_2562) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2563 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2563;
    if (hoisted__Bool_2563) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2564 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2564;
    if (hoisted__Bool_2564) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2565 = (Str){.c_str = (void *)"OwnType.clone:141:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2565;
    UNREACHABLE(&hoisted__Str_2565);
    Str_delete(&hoisted__Str_2565, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2566 = 4;
    (void)hoisted__U32_2566;
    return hoisted__U32_2566;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2568 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2568;
    Declaration *hoisted__Declaration_2569 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2569->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2569->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2569->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2569->is_mut = self->is_mut;
    hoisted__Declaration_2569->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2569->is_priv = self->is_priv;
    hoisted__Declaration_2569->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2569->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2569->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2569->default_value = hoisted__Expr_2568;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2569->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2569;
    return hoisted__Declaration_2569;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2570 = 0;
    (void)hoisted__Bool_2570;
    Str_delete(&self->name, hoisted__Bool_2570);
    Bool hoisted__Bool_2571 = 0;
    (void)hoisted__Bool_2571;
    Str_delete(&self->doc, hoisted__Bool_2571);
    Bool hoisted__Bool_2572 = 0;
    (void)hoisted__Bool_2572;
    Str_delete(&self->explicit_type, hoisted__Bool_2572);
    Bool hoisted__Bool_2573 = 0;
    (void)hoisted__Bool_2573;
    Bool_delete(&self->is_mut, hoisted__Bool_2573);
    Bool hoisted__Bool_2574 = 0;
    (void)hoisted__Bool_2574;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2574);
    Bool hoisted__Bool_2575 = 0;
    (void)hoisted__Bool_2575;
    Bool_delete(&self->is_priv, hoisted__Bool_2575);
    Bool hoisted__Bool_2576 = 0;
    (void)hoisted__Bool_2576;
    Bool_delete(&self->used, hoisted__Bool_2576);
    Bool hoisted__Bool_2577 = 0;
    (void)hoisted__Bool_2577;
    OwnType_delete(&self->own_type, hoisted__Bool_2577);
    Bool hoisted__Bool_2578 = 0;
    (void)hoisted__Bool_2578;
    Type_delete(&self->til_type, hoisted__Bool_2578);
    Bool hoisted__Bool_2579 = 1;
    (void)hoisted__Bool_2579;
    Expr_delete(self->default_value, hoisted__Bool_2579);
    Bool hoisted__Bool_2580 = 0;
    (void)hoisted__Bool_2580;
    Str_delete(&self->orig_name, hoisted__Bool_2580);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2581 = 104;
    (void)hoisted__U32_2581;
    return hoisted__U32_2581;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2583 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2583->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2583->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2583->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2583->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2583->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2583->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2583->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2583->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2583->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2583->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2583->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2583;
    return hoisted__FunctionDef_2583;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2584 = 0;
    (void)hoisted__Bool_2584;
    FuncType_delete(&self->func_type, hoisted__Bool_2584);
    Bool hoisted__Bool_2585 = 0;
    (void)hoisted__Bool_2585;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2585);
    Bool hoisted__Bool_2586 = 0;
    (void)hoisted__Bool_2586;
    Str_delete(&self->return_type, hoisted__Bool_2586);
    Bool hoisted__Bool_2587 = 0;
    (void)hoisted__Bool_2587;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2587);
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    I32_delete(&self->variadic_index, hoisted__Bool_2588);
    Bool hoisted__Bool_2589 = 0;
    (void)hoisted__Bool_2589;
    I32_delete(&self->kwargs_index, hoisted__Bool_2589);
    Bool hoisted__Bool_2590 = 0;
    (void)hoisted__Bool_2590;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2590);
    Bool hoisted__Bool_2591 = 0;
    (void)hoisted__Bool_2591;
    Bool_delete(&self->auto_generated, hoisted__Bool_2591);
    Bool hoisted__Bool_2592 = 0;
    (void)hoisted__Bool_2592;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2592);
    Bool hoisted__Bool_2593 = 0;
    (void)hoisted__Bool_2593;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2593);
    Bool hoisted__Bool_2594 = 0;
    (void)hoisted__Bool_2594;
    Str_delete(&self->closure_name, hoisted__Bool_2594);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2595 = 0;
    (void)hoisted__U32_2595;
    U64 hoisted__U64_2596 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2595); });
    (void)hoisted__U64_2596;
    return hoisted__U64_2596;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2597 = 104;
    (void)hoisted__U32_2597;
    return hoisted__U32_2597;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2600 = malloc(sizeof(FCallData));
    hoisted__FCallData_2600->is_splat = self->is_splat;
    hoisted__FCallData_2600->does_throw = self->does_throw;
    hoisted__FCallData_2600->is_bang = self->is_bang;
    hoisted__FCallData_2600->own_args = self->own_args;
    hoisted__FCallData_2600->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2600->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2600;
    return hoisted__FCallData_2600;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2601 = 0;
    (void)hoisted__Bool_2601;
    Bool_delete(&self->is_splat, hoisted__Bool_2601);
    Bool hoisted__Bool_2602 = 0;
    (void)hoisted__Bool_2602;
    Bool_delete(&self->does_throw, hoisted__Bool_2602);
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Bool_delete(&self->is_bang, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    U64_delete(&self->own_args, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    Bool_delete(&self->swap_replace, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    Type_delete(&self->til_type, hoisted__Bool_2606);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2607 = 0;
    (void)hoisted__U32_2607;
    U64 hoisted__U64_2608 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2607); });
    (void)hoisted__U64_2608;
    return hoisted__U64_2608;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2609 = 48;
    (void)hoisted__U32_2609;
    return hoisted__U32_2609;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2621 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2621->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2621->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2621;
    return hoisted__LiteralNumData_2621;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2622 = 0;
    (void)hoisted__Bool_2622;
    Str_delete(&self->text, hoisted__Bool_2622);
    Bool hoisted__Bool_2623 = 0;
    (void)hoisted__Bool_2623;
    Type_delete(&self->til_type, hoisted__Bool_2623);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2624 = 0;
    (void)hoisted__U32_2624;
    U64 hoisted__U64_2625 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2624); });
    (void)hoisted__U64_2625;
    return hoisted__U64_2625;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2626 = 40;
    (void)hoisted__U32_2626;
    return hoisted__U32_2626;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2636 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2636->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2636->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2636;
    return hoisted__IdentData_2636;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2637 = 0;
    (void)hoisted__Bool_2637;
    Str_delete(&self->name, hoisted__Bool_2637);
    Bool hoisted__Bool_2638 = 0;
    (void)hoisted__Bool_2638;
    Type_delete(&self->til_type, hoisted__Bool_2638);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2639 = 0;
    (void)hoisted__U32_2639;
    U64 hoisted__U64_2640 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2639); });
    (void)hoisted__U64_2640;
    return hoisted__U64_2640;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2641 = 40;
    (void)hoisted__U32_2641;
    return hoisted__U32_2641;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2647 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2647->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2647->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2647;
    return hoisted__FieldAccessData_2647;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2648 = 0;
    (void)hoisted__Bool_2648;
    Str_delete(&self->name, hoisted__Bool_2648);
    Bool hoisted__Bool_2649 = 0;
    (void)hoisted__Bool_2649;
    Type_delete(&self->til_type, hoisted__Bool_2649);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2650 = 0;
    (void)hoisted__U32_2650;
    U64 hoisted__U64_2651 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2650); });
    (void)hoisted__U64_2651;
    return hoisted__U64_2651;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2652 = 40;
    (void)hoisted__U32_2652;
    return hoisted__U32_2652;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2733 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2733->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2733->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2733->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2733->is_interface = self->is_interface;
    hoisted__StructDef_2733->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2733->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2733;
    return hoisted__StructDef_2733;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2734 = 0;
    (void)hoisted__Bool_2734;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2734);
    Bool hoisted__Bool_2735 = 0;
    (void)hoisted__Bool_2735;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2735);
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    Str_delete(&self->c_tag, hoisted__Bool_2736);
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Bool_delete(&self->is_interface, hoisted__Bool_2737);
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Str_delete(&self->implements_name, hoisted__Bool_2739);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2740 = 0;
    (void)hoisted__U32_2740;
    U64 hoisted__U64_2741 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2740); });
    (void)hoisted__U64_2741;
    return hoisted__U64_2741;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2742 = 72;
    (void)hoisted__U32_2742;
    return hoisted__U32_2742;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2747 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2747->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2747->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2747->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2747->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2747->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2747->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2747;
    return hoisted__EnumDef_2747;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2748 = 0;
    (void)hoisted__Bool_2748;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2748);
    Bool hoisted__Bool_2749 = 0;
    (void)hoisted__Bool_2749;
    Vec__Str_delete(&self->variants, hoisted__Bool_2749);
    Bool hoisted__Bool_2750 = 0;
    (void)hoisted__Bool_2750;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2750);
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2751);
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    Str_delete(&self->implements_name, hoisted__Bool_2752);
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Str_delete(&self->tag_type, hoisted__Bool_2753);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2754 = 0;
    (void)hoisted__U32_2754;
    U64 hoisted__U64_2755 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2754); });
    (void)hoisted__U64_2755;
    return hoisted__U64_2755;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2756 = 112;
    (void)hoisted__U32_2756;
    return hoisted__U32_2756;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2852 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2852->name = *_ca; free(_ca); }
    hoisted__AssignData_2852->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2852->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2852->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2852;
    return hoisted__AssignData_2852;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2853 = 0;
    (void)hoisted__Bool_2853;
    Str_delete(&self->name, hoisted__Bool_2853);
    Bool hoisted__Bool_2854 = 0;
    (void)hoisted__Bool_2854;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2854);
    Bool hoisted__Bool_2855 = 0;
    (void)hoisted__Bool_2855;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2855);
    Bool hoisted__Bool_2856 = 0;
    (void)hoisted__Bool_2856;
    Bool_delete(&self->swap_replace, hoisted__Bool_2856);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2857 = 0;
    (void)hoisted__U32_2857;
    U64 hoisted__U64_2858 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2857); });
    (void)hoisted__U64_2858;
    return hoisted__U64_2858;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2859 = 24;
    (void)hoisted__U32_2859;
    return hoisted__U32_2859;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2861 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2861->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2861->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2861;
    return hoisted__FieldAssignData_2861;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2862 = 0;
    (void)hoisted__Bool_2862;
    Str_delete(&self->name, hoisted__Bool_2862);
    Bool hoisted__Bool_2863 = 0;
    (void)hoisted__Bool_2863;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2863);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2864 = 0;
    (void)hoisted__U32_2864;
    U64 hoisted__U64_2865 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2864); });
    (void)hoisted__U64_2865;
    return hoisted__U64_2865;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2866 = 24;
    (void)hoisted__U32_2866;
    return hoisted__U32_2866;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2868 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2868->name = *_ca; free(_ca); }
    hoisted__ForInData_2868->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2868->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2868->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2868->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2868;
    return hoisted__ForInData_2868;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2869 = 0;
    (void)hoisted__Bool_2869;
    Str_delete(&self->name, hoisted__Bool_2869);
    Bool hoisted__Bool_2870 = 0;
    (void)hoisted__Bool_2870;
    Bool_delete(&self->is_mut, hoisted__Bool_2870);
    Bool hoisted__Bool_2871 = 0;
    (void)hoisted__Bool_2871;
    Type_delete(&self->til_type, hoisted__Bool_2871);
    Bool hoisted__Bool_2872 = 0;
    (void)hoisted__Bool_2872;
    Str_delete(&self->name2, hoisted__Bool_2872);
    Bool hoisted__Bool_2873 = 0;
    (void)hoisted__Bool_2873;
    Bool_delete(&self->is_mut2, hoisted__Bool_2873);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2874 = 0;
    (void)hoisted__U32_2874;
    U64 hoisted__U64_2875 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2874); });
    (void)hoisted__U64_2875;
    return hoisted__U64_2875;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2876 = 72;
    (void)hoisted__U32_2876;
    return hoisted__U32_2876;
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
    Bool hoisted__Bool_2906 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2906;
    if (hoisted__Bool_2906) {
        Str *hoisted__Str_2900 = get_payload(self);
        (void)hoisted__Str_2900;
        (void)hoisted__Str_2900;
        Bool hoisted__Bool_2901 = 0;
        (void)hoisted__Bool_2901;
        Str_delete(hoisted__Str_2900, hoisted__Bool_2901);
    }
    Bool hoisted__Bool_2907 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2907;
    if (hoisted__Bool_2907) {
        LiteralNumData *hoisted__LiteralNumData_2902 = get_payload(self);
        (void)hoisted__LiteralNumData_2902;
        (void)hoisted__LiteralNumData_2902;
        Bool hoisted__Bool_2903 = 0;
        (void)hoisted__Bool_2903;
        LiteralNumData_delete(hoisted__LiteralNumData_2902, hoisted__Bool_2903);
    }
    Bool hoisted__Bool_2908 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2908;
    if (hoisted__Bool_2908) {
        Bool *hoisted__Bool_2904 = get_payload(self);
        (void)hoisted__Bool_2904;
        (void)hoisted__Bool_2904;
        Bool hoisted__Bool_2905 = 0;
        (void)hoisted__Bool_2905;
        Bool_delete(hoisted__Bool_2904, hoisted__Bool_2905);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2957 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2957;
    if (hoisted__Bool_2957) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2952 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2952;
        Literal *hoisted__Literal_2953 = Literal_Str(hoisted__Str_2952);
        (void)hoisted__Literal_2953;
        { Literal * _ret_val = hoisted__Literal_2953;
                return _ret_val; }
    }
    Bool hoisted__Bool_2958 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2958;
    if (hoisted__Bool_2958) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2954 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2954;
        Literal *hoisted__Literal_2955 = Literal_Num(hoisted__LiteralNumData_2954);
        (void)hoisted__Literal_2955;
        { Literal * _ret_val = hoisted__Literal_2955;
                return _ret_val; }
    }
    Bool hoisted__Bool_2959 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2959;
    if (hoisted__Bool_2959) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2956 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2956;
        { Literal * _ret_val = hoisted__Literal_2956;
                return _ret_val; }
    }
    Bool hoisted__Bool_2960 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2960;
    if (hoisted__Bool_2960) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2961 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2961;
    if (hoisted__Bool_2961) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2962 = 48;
    (void)hoisted__U32_2962;
    return hoisted__U32_2962;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2965 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2965->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2965->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2965;
    return hoisted__MatchData_2965;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2966 = 0;
    (void)hoisted__Bool_2966;
    Type_delete(&self->til_type, hoisted__Bool_2966);
    Bool hoisted__Bool_2967 = 0;
    (void)hoisted__Bool_2967;
    Str_delete(&self->result_temp, hoisted__Bool_2967);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2968 = 0;
    (void)hoisted__U32_2968;
    U64 hoisted__U64_2969 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2968); });
    (void)hoisted__U64_2969;
    return hoisted__U64_2969;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2970 = 40;
    (void)hoisted__U32_2970;
    return hoisted__U32_2970;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2975 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2975->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2975;
    return hoisted__CaptureBlockData_2975;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2976 = 0;
    (void)hoisted__Bool_2976;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2976);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2977 = 0;
    (void)hoisted__U32_2977;
    U64 hoisted__U64_2978 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2977); });
    (void)hoisted__U64_2978;
    return hoisted__U64_2978;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2979 = 16;
    (void)hoisted__U32_2979;
    return hoisted__U32_2979;
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
    Bool hoisted__Bool_3158 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3158;
    if (hoisted__Bool_3158) {
        Literal *hoisted__Literal_3130 = get_payload(self);
        (void)hoisted__Literal_3130;
        (void)hoisted__Literal_3130;
        Bool hoisted__Bool_3131 = 0;
        (void)hoisted__Bool_3131;
        Literal_delete(hoisted__Literal_3130, hoisted__Bool_3131);
    }
    Bool hoisted__Bool_3159 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3159;
    if (hoisted__Bool_3159) {
        IdentData *hoisted__IdentData_3132 = get_payload(self);
        (void)hoisted__IdentData_3132;
        (void)hoisted__IdentData_3132;
        Bool hoisted__Bool_3133 = 0;
        (void)hoisted__Bool_3133;
        IdentData_delete(hoisted__IdentData_3132, hoisted__Bool_3133);
    }
    Bool hoisted__Bool_3160 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3160;
    if (hoisted__Bool_3160) {
        Declaration *hoisted__Declaration_3134 = get_payload(self);
        (void)hoisted__Declaration_3134;
        (void)hoisted__Declaration_3134;
        Bool hoisted__Bool_3135 = 0;
        (void)hoisted__Bool_3135;
        Declaration_delete(hoisted__Declaration_3134, hoisted__Bool_3135);
    }
    Bool hoisted__Bool_3161 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3161;
    if (hoisted__Bool_3161) {
        AssignData *hoisted__AssignData_3136 = get_payload(self);
        (void)hoisted__AssignData_3136;
        (void)hoisted__AssignData_3136;
        Bool hoisted__Bool_3137 = 0;
        (void)hoisted__Bool_3137;
        AssignData_delete(hoisted__AssignData_3136, hoisted__Bool_3137);
    }
    Bool hoisted__Bool_3162 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3162;
    if (hoisted__Bool_3162) {
        FCallData *hoisted__FCallData_3138 = get_payload(self);
        (void)hoisted__FCallData_3138;
        (void)hoisted__FCallData_3138;
        Bool hoisted__Bool_3139 = 0;
        (void)hoisted__Bool_3139;
        FCallData_delete(hoisted__FCallData_3138, hoisted__Bool_3139);
    }
    Bool hoisted__Bool_3163 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3163;
    if (hoisted__Bool_3163) {
        FunctionDef *hoisted__FunctionDef_3140 = get_payload(self);
        (void)hoisted__FunctionDef_3140;
        (void)hoisted__FunctionDef_3140;
        Bool hoisted__Bool_3141 = 0;
        (void)hoisted__Bool_3141;
        FunctionDef_delete(hoisted__FunctionDef_3140, hoisted__Bool_3141);
    }
    Bool hoisted__Bool_3164 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3164;
    if (hoisted__Bool_3164) {
        StructDef *hoisted__StructDef_3142 = get_payload(self);
        (void)hoisted__StructDef_3142;
        (void)hoisted__StructDef_3142;
        Bool hoisted__Bool_3143 = 0;
        (void)hoisted__Bool_3143;
        StructDef_delete(hoisted__StructDef_3142, hoisted__Bool_3143);
    }
    Bool hoisted__Bool_3165 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3165;
    if (hoisted__Bool_3165) {
        EnumDef *hoisted__EnumDef_3144 = get_payload(self);
        (void)hoisted__EnumDef_3144;
        (void)hoisted__EnumDef_3144;
        Bool hoisted__Bool_3145 = 0;
        (void)hoisted__Bool_3145;
        EnumDef_delete(hoisted__EnumDef_3144, hoisted__Bool_3145);
    }
    Bool hoisted__Bool_3166 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3166;
    if (hoisted__Bool_3166) {
        FieldAccessData *hoisted__FieldAccessData_3146 = get_payload(self);
        (void)hoisted__FieldAccessData_3146;
        (void)hoisted__FieldAccessData_3146;
        Bool hoisted__Bool_3147 = 0;
        (void)hoisted__Bool_3147;
        FieldAccessData_delete(hoisted__FieldAccessData_3146, hoisted__Bool_3147);
    }
    Bool hoisted__Bool_3167 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3167;
    if (hoisted__Bool_3167) {
        FieldAssignData *hoisted__FieldAssignData_3148 = get_payload(self);
        (void)hoisted__FieldAssignData_3148;
        (void)hoisted__FieldAssignData_3148;
        Bool hoisted__Bool_3149 = 0;
        (void)hoisted__Bool_3149;
        FieldAssignData_delete(hoisted__FieldAssignData_3148, hoisted__Bool_3149);
    }
    Bool hoisted__Bool_3168 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3168;
    if (hoisted__Bool_3168) {
        ForInData *hoisted__ForInData_3150 = get_payload(self);
        (void)hoisted__ForInData_3150;
        (void)hoisted__ForInData_3150;
        Bool hoisted__Bool_3151 = 0;
        (void)hoisted__Bool_3151;
        ForInData_delete(hoisted__ForInData_3150, hoisted__Bool_3151);
    }
    Bool hoisted__Bool_3169 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3169;
    if (hoisted__Bool_3169) {
        Str *hoisted__Str_3152 = get_payload(self);
        (void)hoisted__Str_3152;
        (void)hoisted__Str_3152;
        Bool hoisted__Bool_3153 = 0;
        (void)hoisted__Bool_3153;
        Str_delete(hoisted__Str_3152, hoisted__Bool_3153);
    }
    Bool hoisted__Bool_3170 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3170;
    if (hoisted__Bool_3170) {
        MatchData *hoisted__MatchData_3154 = get_payload(self);
        (void)hoisted__MatchData_3154;
        (void)hoisted__MatchData_3154;
        Bool hoisted__Bool_3155 = 0;
        (void)hoisted__Bool_3155;
        MatchData_delete(hoisted__MatchData_3154, hoisted__Bool_3155);
    }
    Bool hoisted__Bool_3171 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3171;
    if (hoisted__Bool_3171) {
        CaptureBlockData *hoisted__CaptureBlockData_3156 = get_payload(self);
        (void)hoisted__CaptureBlockData_3156;
        (void)hoisted__CaptureBlockData_3156;
        Bool hoisted__Bool_3157 = 0;
        (void)hoisted__Bool_3157;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3156, hoisted__Bool_3157);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3395 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3395;
    if (hoisted__Bool_3395) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3396 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3396;
    if (hoisted__Bool_3396) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3367 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3367;
        NodeType *hoisted__NodeType_3368 = NodeType_Literal(hoisted__Literal_3367);
        (void)hoisted__NodeType_3368;
        { NodeType * _ret_val = hoisted__NodeType_3368;
                return _ret_val; }
    }
    Bool hoisted__Bool_3397 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3397;
    if (hoisted__Bool_3397) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3369 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3369;
        NodeType *hoisted__NodeType_3370 = NodeType_Ident(hoisted__IdentData_3369);
        (void)hoisted__NodeType_3370;
        { NodeType * _ret_val = hoisted__NodeType_3370;
                return _ret_val; }
    }
    Bool hoisted__Bool_3398 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3398;
    if (hoisted__Bool_3398) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3371 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3371;
        NodeType *hoisted__NodeType_3372 = NodeType_Decl(hoisted__Declaration_3371);
        (void)hoisted__NodeType_3372;
        { NodeType * _ret_val = hoisted__NodeType_3372;
                return _ret_val; }
    }
    Bool hoisted__Bool_3399 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3399;
    if (hoisted__Bool_3399) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3373 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3373;
        NodeType *hoisted__NodeType_3374 = NodeType_Assign(hoisted__AssignData_3373);
        (void)hoisted__NodeType_3374;
        { NodeType * _ret_val = hoisted__NodeType_3374;
                return _ret_val; }
    }
    Bool hoisted__Bool_3400 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3400;
    if (hoisted__Bool_3400) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3375 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3375;
        NodeType *hoisted__NodeType_3376 = NodeType_FCall(hoisted__FCallData_3375);
        (void)hoisted__NodeType_3376;
        { NodeType * _ret_val = hoisted__NodeType_3376;
                return _ret_val; }
    }
    Bool hoisted__Bool_3401 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3401;
    if (hoisted__Bool_3401) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3377 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3377;
        NodeType *hoisted__NodeType_3378 = NodeType_FuncDef(hoisted__FunctionDef_3377);
        (void)hoisted__NodeType_3378;
        { NodeType * _ret_val = hoisted__NodeType_3378;
                return _ret_val; }
    }
    Bool hoisted__Bool_3402 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3402;
    if (hoisted__Bool_3402) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3379 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3379;
        NodeType *hoisted__NodeType_3380 = NodeType_StructDef(hoisted__StructDef_3379);
        (void)hoisted__NodeType_3380;
        { NodeType * _ret_val = hoisted__NodeType_3380;
                return _ret_val; }
    }
    Bool hoisted__Bool_3403 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3403;
    if (hoisted__Bool_3403) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3381 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3381;
        NodeType *hoisted__NodeType_3382 = NodeType_EnumDef(hoisted__EnumDef_3381);
        (void)hoisted__NodeType_3382;
        { NodeType * _ret_val = hoisted__NodeType_3382;
                return _ret_val; }
    }
    Bool hoisted__Bool_3404 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3404;
    if (hoisted__Bool_3404) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3383 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3383;
        NodeType *hoisted__NodeType_3384 = NodeType_FieldAccess(hoisted__FieldAccessData_3383);
        (void)hoisted__NodeType_3384;
        { NodeType * _ret_val = hoisted__NodeType_3384;
                return _ret_val; }
    }
    Bool hoisted__Bool_3405 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3405;
    if (hoisted__Bool_3405) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3385 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3385;
        NodeType *hoisted__NodeType_3386 = NodeType_FieldAssign(hoisted__FieldAssignData_3385);
        (void)hoisted__NodeType_3386;
        { NodeType * _ret_val = hoisted__NodeType_3386;
                return _ret_val; }
    }
    Bool hoisted__Bool_3406 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3406;
    if (hoisted__Bool_3406) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3407 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3407;
    if (hoisted__Bool_3407) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3408 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3408;
    if (hoisted__Bool_3408) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3409 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3409;
    if (hoisted__Bool_3409) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3387 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3387;
        NodeType *hoisted__NodeType_3388 = NodeType_ForIn(hoisted__ForInData_3387);
        (void)hoisted__NodeType_3388;
        { NodeType * _ret_val = hoisted__NodeType_3388;
                return _ret_val; }
    }
    Bool hoisted__Bool_3410 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3410;
    if (hoisted__Bool_3410) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3389 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3389;
        NodeType *hoisted__NodeType_3390 = NodeType_NamedArg(hoisted__Str_3389);
        (void)hoisted__NodeType_3390;
        { NodeType * _ret_val = hoisted__NodeType_3390;
                return _ret_val; }
    }
    Bool hoisted__Bool_3411 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3411;
    if (hoisted__Bool_3411) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3412 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3412;
    if (hoisted__Bool_3412) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3413 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3413;
    if (hoisted__Bool_3413) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3414 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3414;
    if (hoisted__Bool_3414) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3391 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3391;
        NodeType *hoisted__NodeType_3392 = NodeType_Match(hoisted__MatchData_3391);
        (void)hoisted__NodeType_3392;
        { NodeType * _ret_val = hoisted__NodeType_3392;
                return _ret_val; }
    }
    Bool hoisted__Bool_3415 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3415;
    if (hoisted__Bool_3415) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3416 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3417 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3417;
    if (hoisted__Bool_3417) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3418 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3419 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3419;
    if (hoisted__Bool_3419) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3420 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3393 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3393;
        NodeType *hoisted__NodeType_3394 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3393);
        (void)hoisted__NodeType_3394;
        { NodeType * _ret_val = hoisted__NodeType_3394;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3421 = 120;
    (void)hoisted__U32_3421;
    return hoisted__U32_3421;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3422 = is_null(self);
    (void)hoisted__Bool_3422;
    if (hoisted__Bool_3422) {
        return;
    }
    Bool hoisted__Bool_3423 = 0;
    (void)hoisted__Bool_3423;
    NodeType_delete(&self->node_type, hoisted__Bool_3423);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3473 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3473->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3473->children = *_ca; free(_ca); }
    hoisted__Expr_3473->line = line;
    hoisted__Expr_3473->col = col;
    (void)hoisted__Expr_3473;
    return hoisted__Expr_3473;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3482 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3482->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3482->children = *_ca; free(_ca); }
    hoisted__Expr_3482->line = self->line;
    hoisted__Expr_3482->col = self->col;
    (void)hoisted__Expr_3482;
    return hoisted__Expr_3482;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3483 = 0;
    (void)hoisted__U32_3483;
    U64 hoisted__U64_3484 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3483); });
    (void)hoisted__U64_3484;
    return hoisted__U64_3484;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3485 = 144;
    (void)hoisted__U32_3485;
    return hoisted__U32_3485;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4386 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4386->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4386->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4386;
    return hoisted__Map__I64_Str_4386;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4499 = 0;
    (void)hoisted__Bool_4499;
    Vec__I64_delete(&self->keys, hoisted__Bool_4499);
    Bool hoisted__Bool_4500 = 0;
    (void)hoisted__Bool_4500;
    Vec__Str_delete(&self->values, hoisted__Bool_4500);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4501 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4501->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4501->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4501;
    return hoisted__Map__I64_Str_4501;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4502 = 0;
    (void)hoisted__U32_4502;
    U64 hoisted__U64_4503 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4502); });
    (void)hoisted__U64_4503;
    return hoisted__U64_4503;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4504 = 32;
    (void)hoisted__U32_4504;
    return hoisted__U32_4504;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4505 = 1;
    (void)hoisted__U32_4505;
    U64 hoisted__U64_4506 = (U64)(hoisted__U32_4505);
    (void)hoisted__U64_4506;
    void * hoisted__v_4507 = malloc(hoisted__U64_4506);
    (void)hoisted__v_4507;
    U32 hoisted__U32_4508 = 0;
    (void)hoisted__U32_4508;
    I64 hoisted__I64_4509 = 1;
    (void)hoisted__I64_4509;
    Vec__Bool *hoisted__Vec__Bool_4510 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4510->data = hoisted__v_4507;
    hoisted__Vec__Bool_4510->count = hoisted__U32_4508;
    hoisted__Vec__Bool_4510->cap = hoisted__I64_4509;
    (void)hoisted__Vec__Bool_4510;
    return hoisted__Vec__Bool_4510;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4511 = self->count;
        (void)_re_U32_4511;
        U32 _rc_U32_4511 = 0;
        (void)_rc_U32_4511;
        Bool hoisted__Bool_4524 = U32_lte(_rc_U32_4511, _re_U32_4511);
        (void)hoisted__Bool_4524;
        if (hoisted__Bool_4524) {
            while (1) {
                Bool _wcond_Bool_4512 = U32_lt(_rc_U32_4511, _re_U32_4511);
                (void)_wcond_Bool_4512;
                if (_wcond_Bool_4512) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4511);
                U32_inc(&_rc_U32_4511);
                U32 hoisted__U32_4513 = 1;
                (void)hoisted__U32_4513;
                U32 hoisted__U32_4514 = U32_mul(i, hoisted__U32_4513);
                (void)hoisted__U32_4514;
                U64 hoisted__U64_4515 = (U64)(hoisted__U32_4514);
                (void)hoisted__U64_4515;
                Bool *hoisted__Bool_4516 = ptr_add(self->data, hoisted__U64_4515);
                (void)hoisted__Bool_4516;
                (void)hoisted__Bool_4516;
                Bool hoisted__Bool_4517 = 0;
                (void)hoisted__Bool_4517;
                Bool_delete(hoisted__Bool_4516, hoisted__Bool_4517);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4518 = U32_gt(_rc_U32_4511, _re_U32_4511);
                (void)_wcond_Bool_4518;
                if (_wcond_Bool_4518) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4511);
                U32_dec(&_rc_U32_4511);
                U32 hoisted__U32_4519 = 1;
                (void)hoisted__U32_4519;
                U32 hoisted__U32_4520 = U32_mul(i, hoisted__U32_4519);
                (void)hoisted__U32_4520;
                U64 hoisted__U64_4521 = (U64)(hoisted__U32_4520);
                (void)hoisted__U64_4521;
                Bool *hoisted__Bool_4522 = ptr_add(self->data, hoisted__U64_4521);
                (void)hoisted__Bool_4522;
                (void)hoisted__Bool_4522;
                Bool hoisted__Bool_4523 = 0;
                (void)hoisted__Bool_4523;
                Bool_delete(hoisted__Bool_4522, hoisted__Bool_4523);
            }
        }
    }
    U32 hoisted__U32_4525 = 0;
    (void)hoisted__U32_4525;
    self->count = hoisted__U32_4525;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4795 = 1;
    (void)hoisted__U32_4795;
    U32 hoisted__U32_4796 = U32_mul(self->cap, hoisted__U32_4795);
    (void)hoisted__U32_4796;
    U64 hoisted__U64_4797 = (U64)(hoisted__U32_4796);
    (void)hoisted__U64_4797;
    void * new_data = malloc(hoisted__U64_4797);
    {
        U32 _re_U32_4767 = self->count;
        (void)_re_U32_4767;
        U32 _rc_U32_4767 = 0;
        (void)_rc_U32_4767;
        Bool hoisted__Bool_4794 = U32_lte(_rc_U32_4767, _re_U32_4767);
        (void)hoisted__Bool_4794;
        if (hoisted__Bool_4794) {
            while (1) {
                Bool _wcond_Bool_4768 = U32_lt(_rc_U32_4767, _re_U32_4767);
                (void)_wcond_Bool_4768;
                if (_wcond_Bool_4768) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4767);
                U32_inc(&_rc_U32_4767);
                U32 hoisted__U32_4769 = 1;
                (void)hoisted__U32_4769;
                U32 hoisted__U32_4770 = U32_mul(i, hoisted__U32_4769);
                (void)hoisted__U32_4770;
                U64 hoisted__U64_4771 = (U64)(hoisted__U32_4770);
                (void)hoisted__U64_4771;
                Bool *src = ptr_add(self->data, hoisted__U64_4771);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4772 = 1;
                (void)hoisted__U32_4772;
                U32 hoisted__U32_4773 = U32_mul(i, hoisted__U32_4772);
                (void)hoisted__U32_4773;
                U64 hoisted__U64_4774 = (U64)(hoisted__U32_4773);
                (void)hoisted__U64_4774;
                U32 hoisted__U32_4775 = 1;
                (void)hoisted__U32_4775;
                void *hoisted__v_4776 = ptr_add(new_data, hoisted__U64_4774);
                (void)hoisted__v_4776;
                (void)hoisted__v_4776;
                U64 hoisted__U64_4777 = (U64)(hoisted__U32_4775);
                (void)hoisted__U64_4777;
                memcpy(hoisted__v_4776, &cloned, hoisted__U64_4777);
                U32 hoisted__U32_4778 = 1;
                (void)hoisted__U32_4778;
                I32 hoisted__I32_4779 = 0;
                (void)hoisted__I32_4779;
                U64 hoisted__U64_4780 = (U64)(hoisted__U32_4778);
                (void)hoisted__U64_4780;
                memset(&cloned, hoisted__I32_4779, hoisted__U64_4780);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4781 = U32_gt(_rc_U32_4767, _re_U32_4767);
                (void)_wcond_Bool_4781;
                if (_wcond_Bool_4781) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4767);
                U32_dec(&_rc_U32_4767);
                U32 hoisted__U32_4782 = 1;
                (void)hoisted__U32_4782;
                U32 hoisted__U32_4783 = U32_mul(i, hoisted__U32_4782);
                (void)hoisted__U32_4783;
                U64 hoisted__U64_4784 = (U64)(hoisted__U32_4783);
                (void)hoisted__U64_4784;
                Bool *src = ptr_add(self->data, hoisted__U64_4784);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4785 = 1;
                (void)hoisted__U32_4785;
                U32 hoisted__U32_4786 = U32_mul(i, hoisted__U32_4785);
                (void)hoisted__U32_4786;
                U64 hoisted__U64_4787 = (U64)(hoisted__U32_4786);
                (void)hoisted__U64_4787;
                U32 hoisted__U32_4788 = 1;
                (void)hoisted__U32_4788;
                void *hoisted__v_4789 = ptr_add(new_data, hoisted__U64_4787);
                (void)hoisted__v_4789;
                (void)hoisted__v_4789;
                U64 hoisted__U64_4790 = (U64)(hoisted__U32_4788);
                (void)hoisted__U64_4790;
                memcpy(hoisted__v_4789, &cloned, hoisted__U64_4790);
                U32 hoisted__U32_4791 = 1;
                (void)hoisted__U32_4791;
                I32 hoisted__I32_4792 = 0;
                (void)hoisted__I32_4792;
                U64 hoisted__U64_4793 = (U64)(hoisted__U32_4791);
                (void)hoisted__U64_4793;
                memset(&cloned, hoisted__I32_4792, hoisted__U64_4793);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4798 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4798->data = new_data;
    hoisted__Vec__Bool_4798->count = self->count;
    hoisted__Vec__Bool_4798->cap = self->cap;
    (void)hoisted__Vec__Bool_4798;
    return hoisted__Vec__Bool_4798;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4799 = 16;
    (void)hoisted__U32_4799;
    return hoisted__U32_4799;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5095 = 104;
    (void)hoisted__U32_5095;
    U64 hoisted__U64_5096 = (U64)(hoisted__U32_5095);
    (void)hoisted__U64_5096;
    void * hoisted__v_5097 = malloc(hoisted__U64_5096);
    (void)hoisted__v_5097;
    U32 hoisted__U32_5098 = 0;
    (void)hoisted__U32_5098;
    I64 hoisted__I64_5099 = 1;
    (void)hoisted__I64_5099;
    Vec__Declaration *hoisted__Vec__Declaration_5100 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5100->data = hoisted__v_5097;
    hoisted__Vec__Declaration_5100->count = hoisted__U32_5098;
    hoisted__Vec__Declaration_5100->cap = hoisted__I64_5099;
    (void)hoisted__Vec__Declaration_5100;
    return hoisted__Vec__Declaration_5100;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5101 = self->count;
        (void)_re_U32_5101;
        U32 _rc_U32_5101 = 0;
        (void)_rc_U32_5101;
        Bool hoisted__Bool_5114 = U32_lte(_rc_U32_5101, _re_U32_5101);
        (void)hoisted__Bool_5114;
        if (hoisted__Bool_5114) {
            while (1) {
                Bool _wcond_Bool_5102 = U32_lt(_rc_U32_5101, _re_U32_5101);
                (void)_wcond_Bool_5102;
                if (_wcond_Bool_5102) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5101);
                U32_inc(&_rc_U32_5101);
                U32 hoisted__U32_5103 = 104;
                (void)hoisted__U32_5103;
                U32 hoisted__U32_5104 = U32_mul(i, hoisted__U32_5103);
                (void)hoisted__U32_5104;
                U64 hoisted__U64_5105 = (U64)(hoisted__U32_5104);
                (void)hoisted__U64_5105;
                Declaration *hoisted__Declaration_5106 = ptr_add(self->data, hoisted__U64_5105);
                (void)hoisted__Declaration_5106;
                (void)hoisted__Declaration_5106;
                Bool hoisted__Bool_5107 = 0;
                (void)hoisted__Bool_5107;
                Declaration_delete(hoisted__Declaration_5106, hoisted__Bool_5107);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5108 = U32_gt(_rc_U32_5101, _re_U32_5101);
                (void)_wcond_Bool_5108;
                if (_wcond_Bool_5108) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5101);
                U32_dec(&_rc_U32_5101);
                U32 hoisted__U32_5109 = 104;
                (void)hoisted__U32_5109;
                U32 hoisted__U32_5110 = U32_mul(i, hoisted__U32_5109);
                (void)hoisted__U32_5110;
                U64 hoisted__U64_5111 = (U64)(hoisted__U32_5110);
                (void)hoisted__U64_5111;
                Declaration *hoisted__Declaration_5112 = ptr_add(self->data, hoisted__U64_5111);
                (void)hoisted__Declaration_5112;
                (void)hoisted__Declaration_5112;
                Bool hoisted__Bool_5113 = 0;
                (void)hoisted__Bool_5113;
                Declaration_delete(hoisted__Declaration_5112, hoisted__Bool_5113);
            }
        }
    }
    U32 hoisted__U32_5115 = 0;
    (void)hoisted__U32_5115;
    self->count = hoisted__U32_5115;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5385 = 104;
    (void)hoisted__U32_5385;
    U32 hoisted__U32_5386 = U32_mul(self->cap, hoisted__U32_5385);
    (void)hoisted__U32_5386;
    U64 hoisted__U64_5387 = (U64)(hoisted__U32_5386);
    (void)hoisted__U64_5387;
    void * new_data = malloc(hoisted__U64_5387);
    {
        U32 _re_U32_5357 = self->count;
        (void)_re_U32_5357;
        U32 _rc_U32_5357 = 0;
        (void)_rc_U32_5357;
        Bool hoisted__Bool_5384 = U32_lte(_rc_U32_5357, _re_U32_5357);
        (void)hoisted__Bool_5384;
        if (hoisted__Bool_5384) {
            while (1) {
                Bool _wcond_Bool_5358 = U32_lt(_rc_U32_5357, _re_U32_5357);
                (void)_wcond_Bool_5358;
                if (_wcond_Bool_5358) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5357);
                U32_inc(&_rc_U32_5357);
                U32 hoisted__U32_5359 = 104;
                (void)hoisted__U32_5359;
                U32 hoisted__U32_5360 = U32_mul(i, hoisted__U32_5359);
                (void)hoisted__U32_5360;
                U64 hoisted__U64_5361 = (U64)(hoisted__U32_5360);
                (void)hoisted__U64_5361;
                Declaration *src = ptr_add(self->data, hoisted__U64_5361);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5362 = 104;
                (void)hoisted__U32_5362;
                U32 hoisted__U32_5363 = U32_mul(i, hoisted__U32_5362);
                (void)hoisted__U32_5363;
                U64 hoisted__U64_5364 = (U64)(hoisted__U32_5363);
                (void)hoisted__U64_5364;
                U32 hoisted__U32_5365 = 104;
                (void)hoisted__U32_5365;
                void *hoisted__v_5366 = ptr_add(new_data, hoisted__U64_5364);
                (void)hoisted__v_5366;
                (void)hoisted__v_5366;
                U64 hoisted__U64_5367 = (U64)(hoisted__U32_5365);
                (void)hoisted__U64_5367;
                memcpy(hoisted__v_5366, cloned, hoisted__U64_5367);
                U32 hoisted__U32_5368 = 104;
                (void)hoisted__U32_5368;
                I32 hoisted__I32_5369 = 0;
                (void)hoisted__I32_5369;
                U64 hoisted__U64_5370 = (U64)(hoisted__U32_5368);
                (void)hoisted__U64_5370;
                memset(cloned, hoisted__I32_5369, hoisted__U64_5370);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5371 = U32_gt(_rc_U32_5357, _re_U32_5357);
                (void)_wcond_Bool_5371;
                if (_wcond_Bool_5371) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5357);
                U32_dec(&_rc_U32_5357);
                U32 hoisted__U32_5372 = 104;
                (void)hoisted__U32_5372;
                U32 hoisted__U32_5373 = U32_mul(i, hoisted__U32_5372);
                (void)hoisted__U32_5373;
                U64 hoisted__U64_5374 = (U64)(hoisted__U32_5373);
                (void)hoisted__U64_5374;
                Declaration *src = ptr_add(self->data, hoisted__U64_5374);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5375 = 104;
                (void)hoisted__U32_5375;
                U32 hoisted__U32_5376 = U32_mul(i, hoisted__U32_5375);
                (void)hoisted__U32_5376;
                U64 hoisted__U64_5377 = (U64)(hoisted__U32_5376);
                (void)hoisted__U64_5377;
                U32 hoisted__U32_5378 = 104;
                (void)hoisted__U32_5378;
                void *hoisted__v_5379 = ptr_add(new_data, hoisted__U64_5377);
                (void)hoisted__v_5379;
                (void)hoisted__v_5379;
                U64 hoisted__U64_5380 = (U64)(hoisted__U32_5378);
                (void)hoisted__U64_5380;
                memcpy(hoisted__v_5379, cloned, hoisted__U64_5380);
                U32 hoisted__U32_5381 = 104;
                (void)hoisted__U32_5381;
                I32 hoisted__I32_5382 = 0;
                (void)hoisted__I32_5382;
                U64 hoisted__U64_5383 = (U64)(hoisted__U32_5381);
                (void)hoisted__U64_5383;
                memset(cloned, hoisted__I32_5382, hoisted__U64_5383);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5388 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5388->data = new_data;
    hoisted__Vec__Declaration_5388->count = self->count;
    hoisted__Vec__Declaration_5388->cap = self->cap;
    (void)hoisted__Vec__Declaration_5388;
    return hoisted__Vec__Declaration_5388;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5389 = 16;
    (void)hoisted__U32_5389;
    return hoisted__U32_5389;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5390 = 144;
    (void)hoisted__U32_5390;
    U64 hoisted__U64_5391 = (U64)(hoisted__U32_5390);
    (void)hoisted__U64_5391;
    void * hoisted__v_5392 = malloc(hoisted__U64_5391);
    (void)hoisted__v_5392;
    U32 hoisted__U32_5393 = 0;
    (void)hoisted__U32_5393;
    I64 hoisted__I64_5394 = 1;
    (void)hoisted__I64_5394;
    Vec__Expr *hoisted__Vec__Expr_5395 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5395->data = hoisted__v_5392;
    hoisted__Vec__Expr_5395->count = hoisted__U32_5393;
    hoisted__Vec__Expr_5395->cap = hoisted__I64_5394;
    (void)hoisted__Vec__Expr_5395;
    return hoisted__Vec__Expr_5395;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5396 = self->count;
        (void)_re_U32_5396;
        U32 _rc_U32_5396 = 0;
        (void)_rc_U32_5396;
        Bool hoisted__Bool_5409 = U32_lte(_rc_U32_5396, _re_U32_5396);
        (void)hoisted__Bool_5409;
        if (hoisted__Bool_5409) {
            while (1) {
                Bool _wcond_Bool_5397 = U32_lt(_rc_U32_5396, _re_U32_5396);
                (void)_wcond_Bool_5397;
                if (_wcond_Bool_5397) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5396);
                U32_inc(&_rc_U32_5396);
                U32 hoisted__U32_5398 = 144;
                (void)hoisted__U32_5398;
                U32 hoisted__U32_5399 = U32_mul(i, hoisted__U32_5398);
                (void)hoisted__U32_5399;
                U64 hoisted__U64_5400 = (U64)(hoisted__U32_5399);
                (void)hoisted__U64_5400;
                Expr *hoisted__Expr_5401 = ptr_add(self->data, hoisted__U64_5400);
                (void)hoisted__Expr_5401;
                (void)hoisted__Expr_5401;
                Bool hoisted__Bool_5402 = 0;
                (void)hoisted__Bool_5402;
                Expr_delete(hoisted__Expr_5401, hoisted__Bool_5402);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5403 = U32_gt(_rc_U32_5396, _re_U32_5396);
                (void)_wcond_Bool_5403;
                if (_wcond_Bool_5403) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5396);
                U32_dec(&_rc_U32_5396);
                U32 hoisted__U32_5404 = 144;
                (void)hoisted__U32_5404;
                U32 hoisted__U32_5405 = U32_mul(i, hoisted__U32_5404);
                (void)hoisted__U32_5405;
                U64 hoisted__U64_5406 = (U64)(hoisted__U32_5405);
                (void)hoisted__U64_5406;
                Expr *hoisted__Expr_5407 = ptr_add(self->data, hoisted__U64_5406);
                (void)hoisted__Expr_5407;
                (void)hoisted__Expr_5407;
                Bool hoisted__Bool_5408 = 0;
                (void)hoisted__Bool_5408;
                Expr_delete(hoisted__Expr_5407, hoisted__Bool_5408);
            }
        }
    }
    U32 hoisted__U32_5410 = 0;
    (void)hoisted__U32_5410;
    self->count = hoisted__U32_5410;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5680 = 144;
    (void)hoisted__U32_5680;
    U32 hoisted__U32_5681 = U32_mul(self->cap, hoisted__U32_5680);
    (void)hoisted__U32_5681;
    U64 hoisted__U64_5682 = (U64)(hoisted__U32_5681);
    (void)hoisted__U64_5682;
    void * new_data = malloc(hoisted__U64_5682);
    {
        U32 _re_U32_5652 = self->count;
        (void)_re_U32_5652;
        U32 _rc_U32_5652 = 0;
        (void)_rc_U32_5652;
        Bool hoisted__Bool_5679 = U32_lte(_rc_U32_5652, _re_U32_5652);
        (void)hoisted__Bool_5679;
        if (hoisted__Bool_5679) {
            while (1) {
                Bool _wcond_Bool_5653 = U32_lt(_rc_U32_5652, _re_U32_5652);
                (void)_wcond_Bool_5653;
                if (_wcond_Bool_5653) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5652);
                U32_inc(&_rc_U32_5652);
                U32 hoisted__U32_5654 = 144;
                (void)hoisted__U32_5654;
                U32 hoisted__U32_5655 = U32_mul(i, hoisted__U32_5654);
                (void)hoisted__U32_5655;
                U64 hoisted__U64_5656 = (U64)(hoisted__U32_5655);
                (void)hoisted__U64_5656;
                Expr *src = ptr_add(self->data, hoisted__U64_5656);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5657 = 144;
                (void)hoisted__U32_5657;
                U32 hoisted__U32_5658 = U32_mul(i, hoisted__U32_5657);
                (void)hoisted__U32_5658;
                U64 hoisted__U64_5659 = (U64)(hoisted__U32_5658);
                (void)hoisted__U64_5659;
                U32 hoisted__U32_5660 = 144;
                (void)hoisted__U32_5660;
                void *hoisted__v_5661 = ptr_add(new_data, hoisted__U64_5659);
                (void)hoisted__v_5661;
                (void)hoisted__v_5661;
                U64 hoisted__U64_5662 = (U64)(hoisted__U32_5660);
                (void)hoisted__U64_5662;
                memcpy(hoisted__v_5661, cloned, hoisted__U64_5662);
                U32 hoisted__U32_5663 = 144;
                (void)hoisted__U32_5663;
                I32 hoisted__I32_5664 = 0;
                (void)hoisted__I32_5664;
                U64 hoisted__U64_5665 = (U64)(hoisted__U32_5663);
                (void)hoisted__U64_5665;
                memset(cloned, hoisted__I32_5664, hoisted__U64_5665);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5666 = U32_gt(_rc_U32_5652, _re_U32_5652);
                (void)_wcond_Bool_5666;
                if (_wcond_Bool_5666) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5652);
                U32_dec(&_rc_U32_5652);
                U32 hoisted__U32_5667 = 144;
                (void)hoisted__U32_5667;
                U32 hoisted__U32_5668 = U32_mul(i, hoisted__U32_5667);
                (void)hoisted__U32_5668;
                U64 hoisted__U64_5669 = (U64)(hoisted__U32_5668);
                (void)hoisted__U64_5669;
                Expr *src = ptr_add(self->data, hoisted__U64_5669);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5670 = 144;
                (void)hoisted__U32_5670;
                U32 hoisted__U32_5671 = U32_mul(i, hoisted__U32_5670);
                (void)hoisted__U32_5671;
                U64 hoisted__U64_5672 = (U64)(hoisted__U32_5671);
                (void)hoisted__U64_5672;
                U32 hoisted__U32_5673 = 144;
                (void)hoisted__U32_5673;
                void *hoisted__v_5674 = ptr_add(new_data, hoisted__U64_5672);
                (void)hoisted__v_5674;
                (void)hoisted__v_5674;
                U64 hoisted__U64_5675 = (U64)(hoisted__U32_5673);
                (void)hoisted__U64_5675;
                memcpy(hoisted__v_5674, cloned, hoisted__U64_5675);
                U32 hoisted__U32_5676 = 144;
                (void)hoisted__U32_5676;
                I32 hoisted__I32_5677 = 0;
                (void)hoisted__I32_5677;
                U64 hoisted__U64_5678 = (U64)(hoisted__U32_5676);
                (void)hoisted__U64_5678;
                memset(cloned, hoisted__I32_5677, hoisted__U64_5678);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5683 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5683->data = new_data;
    hoisted__Vec__Expr_5683->count = self->count;
    hoisted__Vec__Expr_5683->cap = self->cap;
    (void)hoisted__Vec__Expr_5683;
    return hoisted__Vec__Expr_5683;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5684 = 16;
    (void)hoisted__U32_5684;
    return hoisted__U32_5684;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5685 = 8;
    (void)hoisted__U32_5685;
    U64 hoisted__U64_5686 = (U64)(hoisted__U32_5685);
    (void)hoisted__U64_5686;
    void * hoisted__v_5687 = malloc(hoisted__U64_5686);
    (void)hoisted__v_5687;
    U32 hoisted__U32_5688 = 0;
    (void)hoisted__U32_5688;
    I64 hoisted__I64_5689 = 1;
    (void)hoisted__I64_5689;
    Vec__I64 *hoisted__Vec__I64_5690 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5690->data = hoisted__v_5687;
    hoisted__Vec__I64_5690->count = hoisted__U32_5688;
    hoisted__Vec__I64_5690->cap = hoisted__I64_5689;
    (void)hoisted__Vec__I64_5690;
    return hoisted__Vec__I64_5690;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5691 = self->count;
        (void)_re_U32_5691;
        U32 _rc_U32_5691 = 0;
        (void)_rc_U32_5691;
        Bool hoisted__Bool_5704 = U32_lte(_rc_U32_5691, _re_U32_5691);
        (void)hoisted__Bool_5704;
        if (hoisted__Bool_5704) {
            while (1) {
                Bool _wcond_Bool_5692 = U32_lt(_rc_U32_5691, _re_U32_5691);
                (void)_wcond_Bool_5692;
                if (_wcond_Bool_5692) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5691);
                U32_inc(&_rc_U32_5691);
                U32 hoisted__U32_5693 = 8;
                (void)hoisted__U32_5693;
                U32 hoisted__U32_5694 = U32_mul(i, hoisted__U32_5693);
                (void)hoisted__U32_5694;
                U64 hoisted__U64_5695 = (U64)(hoisted__U32_5694);
                (void)hoisted__U64_5695;
                I64 *hoisted__I64_5696 = ptr_add(self->data, hoisted__U64_5695);
                (void)hoisted__I64_5696;
                (void)hoisted__I64_5696;
                Bool hoisted__Bool_5697 = 0;
                (void)hoisted__Bool_5697;
                I64_delete(hoisted__I64_5696, hoisted__Bool_5697);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5698 = U32_gt(_rc_U32_5691, _re_U32_5691);
                (void)_wcond_Bool_5698;
                if (_wcond_Bool_5698) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5691);
                U32_dec(&_rc_U32_5691);
                U32 hoisted__U32_5699 = 8;
                (void)hoisted__U32_5699;
                U32 hoisted__U32_5700 = U32_mul(i, hoisted__U32_5699);
                (void)hoisted__U32_5700;
                U64 hoisted__U64_5701 = (U64)(hoisted__U32_5700);
                (void)hoisted__U64_5701;
                I64 *hoisted__I64_5702 = ptr_add(self->data, hoisted__U64_5701);
                (void)hoisted__I64_5702;
                (void)hoisted__I64_5702;
                Bool hoisted__Bool_5703 = 0;
                (void)hoisted__Bool_5703;
                I64_delete(hoisted__I64_5702, hoisted__Bool_5703);
            }
        }
    }
    U32 hoisted__U32_5705 = 0;
    (void)hoisted__U32_5705;
    self->count = hoisted__U32_5705;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5975 = 8;
    (void)hoisted__U32_5975;
    U32 hoisted__U32_5976 = U32_mul(self->cap, hoisted__U32_5975);
    (void)hoisted__U32_5976;
    U64 hoisted__U64_5977 = (U64)(hoisted__U32_5976);
    (void)hoisted__U64_5977;
    void * new_data = malloc(hoisted__U64_5977);
    {
        U32 _re_U32_5947 = self->count;
        (void)_re_U32_5947;
        U32 _rc_U32_5947 = 0;
        (void)_rc_U32_5947;
        Bool hoisted__Bool_5974 = U32_lte(_rc_U32_5947, _re_U32_5947);
        (void)hoisted__Bool_5974;
        if (hoisted__Bool_5974) {
            while (1) {
                Bool _wcond_Bool_5948 = U32_lt(_rc_U32_5947, _re_U32_5947);
                (void)_wcond_Bool_5948;
                if (_wcond_Bool_5948) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5947);
                U32_inc(&_rc_U32_5947);
                U32 hoisted__U32_5949 = 8;
                (void)hoisted__U32_5949;
                U32 hoisted__U32_5950 = U32_mul(i, hoisted__U32_5949);
                (void)hoisted__U32_5950;
                U64 hoisted__U64_5951 = (U64)(hoisted__U32_5950);
                (void)hoisted__U64_5951;
                I64 *src = ptr_add(self->data, hoisted__U64_5951);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5952 = 8;
                (void)hoisted__U32_5952;
                U32 hoisted__U32_5953 = U32_mul(i, hoisted__U32_5952);
                (void)hoisted__U32_5953;
                U64 hoisted__U64_5954 = (U64)(hoisted__U32_5953);
                (void)hoisted__U64_5954;
                U32 hoisted__U32_5955 = 8;
                (void)hoisted__U32_5955;
                void *hoisted__v_5956 = ptr_add(new_data, hoisted__U64_5954);
                (void)hoisted__v_5956;
                (void)hoisted__v_5956;
                U64 hoisted__U64_5957 = (U64)(hoisted__U32_5955);
                (void)hoisted__U64_5957;
                memcpy(hoisted__v_5956, &cloned, hoisted__U64_5957);
                U32 hoisted__U32_5958 = 8;
                (void)hoisted__U32_5958;
                I32 hoisted__I32_5959 = 0;
                (void)hoisted__I32_5959;
                U64 hoisted__U64_5960 = (U64)(hoisted__U32_5958);
                (void)hoisted__U64_5960;
                memset(&cloned, hoisted__I32_5959, hoisted__U64_5960);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5961 = U32_gt(_rc_U32_5947, _re_U32_5947);
                (void)_wcond_Bool_5961;
                if (_wcond_Bool_5961) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5947);
                U32_dec(&_rc_U32_5947);
                U32 hoisted__U32_5962 = 8;
                (void)hoisted__U32_5962;
                U32 hoisted__U32_5963 = U32_mul(i, hoisted__U32_5962);
                (void)hoisted__U32_5963;
                U64 hoisted__U64_5964 = (U64)(hoisted__U32_5963);
                (void)hoisted__U64_5964;
                I64 *src = ptr_add(self->data, hoisted__U64_5964);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5965 = 8;
                (void)hoisted__U32_5965;
                U32 hoisted__U32_5966 = U32_mul(i, hoisted__U32_5965);
                (void)hoisted__U32_5966;
                U64 hoisted__U64_5967 = (U64)(hoisted__U32_5966);
                (void)hoisted__U64_5967;
                U32 hoisted__U32_5968 = 8;
                (void)hoisted__U32_5968;
                void *hoisted__v_5969 = ptr_add(new_data, hoisted__U64_5967);
                (void)hoisted__v_5969;
                (void)hoisted__v_5969;
                U64 hoisted__U64_5970 = (U64)(hoisted__U32_5968);
                (void)hoisted__U64_5970;
                memcpy(hoisted__v_5969, &cloned, hoisted__U64_5970);
                U32 hoisted__U32_5971 = 8;
                (void)hoisted__U32_5971;
                I32 hoisted__I32_5972 = 0;
                (void)hoisted__I32_5972;
                U64 hoisted__U64_5973 = (U64)(hoisted__U32_5971);
                (void)hoisted__U64_5973;
                memset(&cloned, hoisted__I32_5972, hoisted__U64_5973);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5978 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5978->data = new_data;
    hoisted__Vec__I64_5978->count = self->count;
    hoisted__Vec__I64_5978->cap = self->cap;
    (void)hoisted__Vec__I64_5978;
    return hoisted__Vec__I64_5978;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5979 = 16;
    (void)hoisted__U32_5979;
    return hoisted__U32_5979;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7080 = 3;
    (void)hoisted__U32_7080;
    Array__Str *_va_Array_200 = Array__Str_new(hoisted__U32_7080);
    (void)_va_Array_200;
    I64 _va_Array_200_ek = 0;
    (void)_va_Array_200_ek;
    OutOfBounds *_va_Array_200_eo = malloc(sizeof(OutOfBounds));
    _va_Array_200_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_200_eo;
    U32 hoisted__U32_7081 = 0;
    (void)hoisted__U32_7081;
    Str *hoisted__Str_7082 = Str_clone(loc);
    (void)hoisted__Str_7082;
    (void)hoisted__Str_7083;
    (void)hoisted__Str_7083;
    Array__Str_set(_va_Array_200, hoisted__U32_7081, hoisted__Str_7082, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7083);
    Str_delete(&hoisted__Str_7083, (Bool){0});
    U32 hoisted__U32_7084 = 1;
    (void)hoisted__U32_7084;
    (void)hoisted__Str_7085;
    (void)hoisted__Str_7085;
    (void)hoisted__Str_7086;
    (void)hoisted__Str_7086;
    Array__Str_set(_va_Array_200, hoisted__U32_7084, &hoisted__Str_7085, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7086);
    Str_delete(&hoisted__Str_7086, (Bool){0});
    Array__Str *hoisted__Array__Str_7087 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7087;
    U32 hoisted__U32_7088 = 2;
    (void)hoisted__U32_7088;
    Str *hoisted__Str_7089 = format(hoisted__Array__Str_7087);
    (void)hoisted__Str_7089;
    (void)hoisted__Str_7090;
    (void)hoisted__Str_7090;
    Array__Str_set(_va_Array_200, hoisted__U32_7088, hoisted__Str_7089, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7090);
    OutOfBounds_delete(_va_Array_200_eo, 1);
    Str_delete(&hoisted__Str_7090, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_200);
    I64 hoisted__I64_7091 = 1;
    (void)hoisted__I64_7091;
    exit(hoisted__I64_7091);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7100 = 1;
    (void)hoisted__U32_7100;
    Array__Str *_va_Array_202 = Array__Str_new(hoisted__U32_7100);
    (void)_va_Array_202;
    I64 _va_Array_202_ek = 0;
    (void)_va_Array_202_ek;
    OutOfBounds *_va_Array_202_eo = malloc(sizeof(OutOfBounds));
    _va_Array_202_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_202_eo;
    U32 hoisted__U32_7101 = 0;
    (void)hoisted__U32_7101;
    (void)hoisted__Str_7102;
    (void)hoisted__Str_7102;
    (void)hoisted__Str_7103;
    (void)hoisted__Str_7103;
    Array__Str_set(_va_Array_202, hoisted__U32_7101, &hoisted__Str_7102, &_va_Array_202_ek, _va_Array_202_eo, &hoisted__Str_7103);
    OutOfBounds_delete(_va_Array_202_eo, 1);
    Str_delete(&hoisted__Str_7103, (Bool){0});
    panic(_va_Array_202, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7108 = not(cond);
    (void)hoisted__Bool_7108;
    if (hoisted__Bool_7108) {
        U32 hoisted__U32_7104 = 1;
        (void)hoisted__U32_7104;
        Array__Str *_va_Array_203 = Array__Str_new(hoisted__U32_7104);
        (void)_va_Array_203;
        I64 _va_Array_203_ek = 0;
        (void)_va_Array_203_ek;
        OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
        _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_203_eo;
        U32 hoisted__U32_7105 = 0;
        (void)hoisted__U32_7105;
        (void)hoisted__Str_7106;
        (void)hoisted__Str_7106;
        (void)hoisted__Str_7107;
        (void)hoisted__Str_7107;
        Array__Str_set(_va_Array_203, hoisted__U32_7105, &hoisted__Str_7106, &_va_Array_203_ek, _va_Array_203_eo, &hoisted__Str_7107);
        OutOfBounds_delete(_va_Array_203_eo, 1);
        Str_delete(&hoisted__Str_7107, (Bool){0});
        panic(_va_Array_203, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7118 = parts;
        (void)_fc_Array__Str_7118;
        (void)_fc_Array__Str_7118;
        U32 _fi_USize_7118 = 0;
        (void)_fi_USize_7118;
        while (1) {
            U32 hoisted__U32_7120 = Array__Str_len(_fc_Array__Str_7118);
            (void)hoisted__U32_7120;
            Bool _wcond_Bool_7119 = U32_lt(_fi_USize_7118, hoisted__U32_7120);
            (void)_wcond_Bool_7119;
            if (_wcond_Bool_7119) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7118, &_fi_USize_7118);
            U32 hoisted__U32_7121 = 1;
            (void)hoisted__U32_7121;
            U32 hoisted__U32_7122 = U32_add(_fi_USize_7118, hoisted__U32_7121);
            (void)hoisted__U32_7122;
            _fi_USize_7118 = hoisted__U32_7122;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7156 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7156;
    return hoisted__Bool_7156;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7165 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7165;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7165;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7166 = 0;
    (void)hoisted__U32_7166;
    U64 hoisted__U64_7167 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7166); });
    (void)hoisted__U64_7167;
    return hoisted__U64_7167;
}

U32 Range_size(void) {
    U32 hoisted__U32_7198 = 16;
    (void)hoisted__U32_7198;
    return hoisted__U32_7198;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7327 = 3;
    (void)hoisted__I64_7327;
    (void)hoisted__Str_7328;
    (void)hoisted__Str_7328;
    assert_eq__I64(result, hoisted__I64_7327, &hoisted__Str_7328);
    Str_delete(&hoisted__Str_7328, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7335 = 15;
    (void)hoisted__I64_7335;
    (void)hoisted__Str_7336;
    (void)hoisted__Str_7336;
    assert_eq__I64(result, hoisted__I64_7335, &hoisted__Str_7336);
    Str_delete(&hoisted__Str_7336, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7343 = 26;
    (void)hoisted__I64_7343;
    (void)hoisted__Str_7344;
    (void)hoisted__Str_7344;
    assert_eq__I64(result, hoisted__I64_7343, &hoisted__Str_7344);
    Str_delete(&hoisted__Str_7344, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7347;
    (void)hoisted__Str_7347;
    (void)hoisted__Str_7348;
    (void)hoisted__Str_7348;
    assert_eq__Str(&result, &hoisted__Str_7347, &hoisted__Str_7348);
    Str_delete(&hoisted__Str_7347, (Bool){0});
    Str_delete(&hoisted__Str_7348, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7376;
    (void)hoisted__Str_7376;
    (void)hoisted__Str_7377;
    (void)hoisted__Str_7377;
    assert_eq__Str(&r, &hoisted__Str_7376, &hoisted__Str_7377);
    Str_delete(&hoisted__Str_7376, (Bool){0});
    Str_delete(&hoisted__Str_7377, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7381;
    (void)hoisted__Str_7381;
    (void)hoisted__Str_7382;
    (void)hoisted__Str_7382;
    assert_eq__Str(&r2, &hoisted__Str_7381, &hoisted__Str_7382);
    Str_delete(&hoisted__Str_7381, (Bool){0});
    Str_delete(&hoisted__Str_7382, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7405;
    (void)hoisted__Str_7405;
    (void)hoisted__Str_7406;
    (void)hoisted__Str_7406;
    assert_eq__Str(&d, &hoisted__Str_7405, &hoisted__Str_7406);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7405, (Bool){0});
    Str_delete(&hoisted__Str_7406, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7417;
    (void)hoisted__Str_7417;
    (void)hoisted__Str_7418;
    (void)hoisted__Str_7418;
    assert_eq__Str(&d2, &hoisted__Str_7417, &hoisted__Str_7418);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7417, (Bool){0});
    Str_delete(&hoisted__Str_7418, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7430 = 106;
    (void)hoisted__I64_7430;
    (void)hoisted__Str_7431;
    (void)hoisted__Str_7431;
    assert_eq__I64(d3, hoisted__I64_7430, &hoisted__Str_7431);
    Str_delete(&hoisted__Str_7431, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8030;
    (void)hoisted__Str_8030;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8030);
    Str_delete(&hoisted__Str_8030, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)hoisted__Str_8031;
    (void)hoisted__Str_8031;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8031);
    Str_delete(&hoisted__Str_8031, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8033 = 8;
    (void)hoisted__I64_8033;
    (void)hoisted__Str_8034;
    (void)hoisted__Str_8034;
    assert_eq__I64(result, hoisted__I64_8033, &hoisted__Str_8034);
    Str_delete(&hoisted__Str_8034, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8037 = 1;
    (void)hoisted__Bool_8037;
    (void)hoisted__Str_8038;
    (void)hoisted__Str_8038;
    assert(hoisted__Bool_8037, &hoisted__Str_8038);
    Str_delete(&hoisted__Str_8038, (Bool){0});
    Bool hoisted__Bool_8041 = 1;
    (void)hoisted__Bool_8041;
    (void)hoisted__Str_8042;
    (void)hoisted__Str_8042;
    assert(hoisted__Bool_8041, &hoisted__Str_8042);
    Str_delete(&hoisted__Str_8042, (Bool){0});
}

void test_fold_f32(void) {
    (void)hoisted__Str_8047;
    (void)hoisted__Str_8047;
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8049;
    (void)hoisted__Str_8049;
    assert_eq__Str(&hoisted__Str_8047, &hoisted__Str_8048, &hoisted__Str_8049);
    Str_delete(&hoisted__Str_8047, (Bool){0});
    Str_delete(&hoisted__Str_8048, (Bool){0});
    Str_delete(&hoisted__Str_8049, (Bool){0});
    (void)hoisted__Str_8052;
    (void)hoisted__Str_8052;
    (void)hoisted__Str_8053;
    (void)hoisted__Str_8053;
    (void)hoisted__Str_8054;
    (void)hoisted__Str_8054;
    assert_eq__Str(&hoisted__Str_8052, &hoisted__Str_8053, &hoisted__Str_8054);
    Str_delete(&hoisted__Str_8052, (Bool){0});
    Str_delete(&hoisted__Str_8053, (Bool){0});
    Str_delete(&hoisted__Str_8054, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8059 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8059;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8059;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8060 = 0;
    (void)hoisted__U32_8060;
    U64 hoisted__U64_8061 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8060); });
    (void)hoisted__U64_8061;
    return hoisted__U64_8061;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8092 = 16;
    (void)hoisted__U32_8092;
    return hoisted__U32_8092;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8093 = 42;
    (void)hoisted__I64_8093;
    (void)hoisted__Str_8094;
    (void)hoisted__Str_8094;
    assert_eq__I64(v.x, hoisted__I64_8093, &hoisted__Str_8094);
    Str_delete(&hoisted__Str_8094, (Bool){0});
    I64 hoisted__I64_8095 = 99;
    (void)hoisted__I64_8095;
    (void)hoisted__Str_8096;
    (void)hoisted__Str_8096;
    assert_eq__I64(v.y, hoisted__I64_8095, &hoisted__Str_8096);
    Str_delete(&hoisted__Str_8096, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8099 = 10;
    (void)hoisted__I64_8099;
    (void)hoisted__Str_8100;
    (void)hoisted__Str_8100;
    assert_eq__I64(p.x, hoisted__I64_8099, &hoisted__Str_8100);
    Str_delete(&hoisted__Str_8100, (Bool){0});
    I64 hoisted__I64_8101 = 20;
    (void)hoisted__I64_8101;
    (void)hoisted__Str_8102;
    (void)hoisted__Str_8102;
    assert_eq__I64(p.y, hoisted__I64_8101, &hoisted__Str_8102);
    Str_delete(&hoisted__Str_8102, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8108 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8108;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8108;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8109 = 0;
    (void)hoisted__U32_8109;
    U64 hoisted__U64_8110 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8109); });
    (void)hoisted__U64_8110;
    return hoisted__U64_8110;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8141 = 32;
    (void)hoisted__U32_8141;
    return hoisted__U32_8141;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8142 = 5;
    (void)hoisted__I64_8142;
    (void)hoisted__Str_8143;
    (void)hoisted__Str_8143;
    assert_eq__I64(r.top_left.x, hoisted__I64_8142, &hoisted__Str_8143);
    Str_delete(&hoisted__Str_8143, (Bool){0});
    I64 hoisted__I64_8144 = 10;
    (void)hoisted__I64_8144;
    (void)hoisted__Str_8145;
    (void)hoisted__Str_8145;
    assert_eq__I64(r.top_left.y, hoisted__I64_8144, &hoisted__Str_8145);
    Str_delete(&hoisted__Str_8145, (Bool){0});
    I64 hoisted__I64_8146 = 100;
    (void)hoisted__I64_8146;
    (void)hoisted__Str_8147;
    (void)hoisted__Str_8147;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8146, &hoisted__Str_8147);
    Str_delete(&hoisted__Str_8147, (Bool){0});
    I64 hoisted__I64_8148 = 200;
    (void)hoisted__I64_8148;
    (void)hoisted__Str_8149;
    (void)hoisted__Str_8149;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8148, &hoisted__Str_8149);
    Str_delete(&hoisted__Str_8149, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8151 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8151;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8151;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8152 = 0;
    (void)hoisted__U32_8152;
    U64 hoisted__U64_8153 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8152); });
    (void)hoisted__U64_8153;
    return hoisted__U64_8153;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8196 = 12;
    (void)hoisted__U32_8196;
    return hoisted__U32_8196;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8200 = F32_to_str(v.x);
    (void)hoisted__Str_8200;
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8202;
    (void)hoisted__Str_8202;
    assert_eq__Str(hoisted__Str_8200, &hoisted__Str_8201, &hoisted__Str_8202);
    Str_delete(hoisted__Str_8200, 1);
    Str_delete(&hoisted__Str_8201, (Bool){0});
    Str_delete(&hoisted__Str_8202, (Bool){0});
    Str *hoisted__Str_8203 = F32_to_str(v.y);
    (void)hoisted__Str_8203;
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8205;
    (void)hoisted__Str_8205;
    assert_eq__Str(hoisted__Str_8203, &hoisted__Str_8204, &hoisted__Str_8205);
    Str_delete(hoisted__Str_8203, 1);
    Str_delete(&hoisted__Str_8204, (Bool){0});
    Str_delete(&hoisted__Str_8205, (Bool){0});
    Str *hoisted__Str_8206 = F32_to_str(v.z);
    (void)hoisted__Str_8206;
    (void)hoisted__Str_8207;
    (void)hoisted__Str_8207;
    (void)hoisted__Str_8208;
    (void)hoisted__Str_8208;
    assert_eq__Str(hoisted__Str_8206, &hoisted__Str_8207, &hoisted__Str_8208);
    Str_delete(hoisted__Str_8206, 1);
    Str_delete(&hoisted__Str_8207, (Bool){0});
    Str_delete(&hoisted__Str_8208, (Bool){0});
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
    Bool hoisted__Bool_8213 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8213;
    if (hoisted__Bool_8213) {
        Bool hoisted__Bool_8210 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8210;
        { Bool _ret_val = hoisted__Bool_8210;
                return _ret_val; }
    }
    Bool hoisted__Bool_8214 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8214;
    if (hoisted__Bool_8214) {
        Bool hoisted__Bool_8211 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8211;
        { Bool _ret_val = hoisted__Bool_8211;
                return _ret_val; }
    }
    Bool hoisted__Bool_8215 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8215;
    if (hoisted__Bool_8215) {
        Bool hoisted__Bool_8212 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8212;
        { Bool _ret_val = hoisted__Bool_8212;
                return _ret_val; }
    }
    Bool hoisted__Bool_8216 = 0;
    (void)hoisted__Bool_8216;
    return hoisted__Bool_8216;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8224 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8224;
    if (hoisted__Bool_8224) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8225 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8225;
    if (hoisted__Bool_8225) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8226 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8226;
    if (hoisted__Bool_8226) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8227 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8227;
    UNREACHABLE(&hoisted__Str_8227);
    Str_delete(&hoisted__Str_8227, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8228 = 4;
    (void)hoisted__U32_8228;
    return hoisted__U32_8228;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8229 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8229;
    (void)hoisted__Str_8230;
    (void)hoisted__Str_8230;
    assert(hoisted__Bool_8229, &hoisted__Str_8230);
    Str_delete(&hoisted__Str_8230, (Bool){0});
    Bool hoisted__Bool_8231 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8231;
    Bool hoisted__Bool_8232 = not(hoisted__Bool_8231);
    (void)hoisted__Bool_8232;
    (void)hoisted__Str_8233;
    (void)hoisted__Str_8233;
    assert(hoisted__Bool_8232, &hoisted__Str_8233);
    Str_delete(&hoisted__Str_8233, (Bool){0});
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
    Bool hoisted__Bool_8234 = is(self, other);
    (void)hoisted__Bool_8234;
    return hoisted__Bool_8234;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8252 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8252;
    if (hoisted__Bool_8252) {
        I64 *hoisted__I64_8248 = get_payload(self);
        (void)hoisted__I64_8248;
        (void)hoisted__I64_8248;
        Bool hoisted__Bool_8249 = 0;
        (void)hoisted__Bool_8249;
        I64_delete(hoisted__I64_8248, hoisted__Bool_8249);
    }
    Bool hoisted__Bool_8253 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8253;
    if (hoisted__Bool_8253) {
        Str *hoisted__Str_8250 = get_payload(self);
        (void)hoisted__Str_8250;
        (void)hoisted__Str_8250;
        Bool hoisted__Bool_8251 = 0;
        (void)hoisted__Bool_8251;
        Str_delete(hoisted__Str_8250, hoisted__Bool_8251);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8284 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8284;
    if (hoisted__Bool_8284) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8281 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8281;
        { Token * _ret_val = hoisted__Token_8281;
                return _ret_val; }
    }
    Bool hoisted__Bool_8285 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8285;
    if (hoisted__Bool_8285) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8282 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8282;
        Token *hoisted__Token_8283 = Token_Name(hoisted__Str_8282);
        (void)hoisted__Token_8283;
        { Token * _ret_val = hoisted__Token_8283;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8286 = 24;
    (void)hoisted__U32_8286;
    return hoisted__U32_8286;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8288 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8288;
    (void)hoisted__Str_8289;
    (void)hoisted__Str_8289;
    assert(hoisted__Bool_8288, &hoisted__Str_8289);
    Str_delete(&hoisted__Str_8289, (Bool){0});
    Bool hoisted__Bool_8290 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8290;
    Bool hoisted__Bool_8291 = not(hoisted__Bool_8290);
    (void)hoisted__Bool_8291;
    (void)hoisted__Str_8292;
    (void)hoisted__Str_8292;
    assert(hoisted__Bool_8291, &hoisted__Str_8292);
    Str_delete(&hoisted__Str_8292, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8293 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8293;
    (void)hoisted__Str_8294;
    (void)hoisted__Str_8294;
    assert(hoisted__Bool_8293, &hoisted__Str_8294);
    Str_delete(&hoisted__Str_8294, (Bool){0});
    Bool hoisted__Bool_8295 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8295;
    Bool hoisted__Bool_8296 = not(hoisted__Bool_8295);
    (void)hoisted__Bool_8296;
    (void)hoisted__Str_8297;
    (void)hoisted__Str_8297;
    assert(hoisted__Bool_8296, &hoisted__Str_8297);
    Str_delete(&hoisted__Str_8297, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8300 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8300;
    (void)hoisted__Str_8301;
    (void)hoisted__Str_8301;
    assert(hoisted__Bool_8300, &hoisted__Str_8301);
    Str_delete(&hoisted__Str_8301, (Bool){0});
    Bool hoisted__Bool_8302 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8302;
    Bool hoisted__Bool_8303 = not(hoisted__Bool_8302);
    (void)hoisted__Bool_8303;
    (void)hoisted__Str_8304;
    (void)hoisted__Str_8304;
    assert(hoisted__Bool_8303, &hoisted__Str_8304);
    Str_delete(&hoisted__Str_8304, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8436 = I64_neq(a, b);
    (void)hoisted__Bool_8436;
    if (hoisted__Bool_8436) {
        U32 hoisted__U32_8420 = 5;
        (void)hoisted__U32_8420;
        Array__Str *_va_Array_248 = Array__Str_new(hoisted__U32_8420);
        (void)_va_Array_248;
        I64 _va_Array_248_ek = 0;
        (void)_va_Array_248_ek;
        OutOfBounds *_va_Array_248_eo = malloc(sizeof(OutOfBounds));
        _va_Array_248_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_248_eo;
        U32 hoisted__U32_8421 = 0;
        (void)hoisted__U32_8421;
        (void)hoisted__Str_8422;
        (void)hoisted__Str_8422;
        (void)hoisted__Str_8423;
        (void)hoisted__Str_8423;
        Array__Str_set(_va_Array_248, hoisted__U32_8421, &hoisted__Str_8422, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8423);
        Str_delete(&hoisted__Str_8423, (Bool){0});
        U32 hoisted__U32_8424 = 1;
        (void)hoisted__U32_8424;
        Str *hoisted__Str_8425 = I64_to_str(a);
        (void)hoisted__Str_8425;
        (void)hoisted__Str_8426;
        (void)hoisted__Str_8426;
        Array__Str_set(_va_Array_248, hoisted__U32_8424, hoisted__Str_8425, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8426);
        Str_delete(&hoisted__Str_8426, (Bool){0});
        U32 hoisted__U32_8427 = 2;
        (void)hoisted__U32_8427;
        (void)hoisted__Str_8428;
        (void)hoisted__Str_8428;
        (void)hoisted__Str_8429;
        (void)hoisted__Str_8429;
        Array__Str_set(_va_Array_248, hoisted__U32_8427, &hoisted__Str_8428, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8429);
        Str_delete(&hoisted__Str_8429, (Bool){0});
        U32 hoisted__U32_8430 = 3;
        (void)hoisted__U32_8430;
        Str *hoisted__Str_8431 = I64_to_str(b);
        (void)hoisted__Str_8431;
        (void)hoisted__Str_8432;
        (void)hoisted__Str_8432;
        Array__Str_set(_va_Array_248, hoisted__U32_8430, hoisted__Str_8431, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8432);
        Str_delete(&hoisted__Str_8432, (Bool){0});
        U32 hoisted__U32_8433 = 4;
        (void)hoisted__U32_8433;
        (void)hoisted__Str_8434;
        (void)hoisted__Str_8434;
        (void)hoisted__Str_8435;
        (void)hoisted__Str_8435;
        Array__Str_set(_va_Array_248, hoisted__U32_8433, &hoisted__Str_8434, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8435);
        OutOfBounds_delete(_va_Array_248_eo, 1);
        Str_delete(&hoisted__Str_8435, (Bool){0});
        panic(_va_Array_248, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8453 = Str_neq(a, b);
    (void)hoisted__Bool_8453;
    if (hoisted__Bool_8453) {
        U32 hoisted__U32_8437 = 5;
        (void)hoisted__U32_8437;
        Array__Str *_va_Array_249 = Array__Str_new(hoisted__U32_8437);
        (void)_va_Array_249;
        I64 _va_Array_249_ek = 0;
        (void)_va_Array_249_ek;
        OutOfBounds *_va_Array_249_eo = malloc(sizeof(OutOfBounds));
        _va_Array_249_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_249_eo;
        U32 hoisted__U32_8438 = 0;
        (void)hoisted__U32_8438;
        (void)hoisted__Str_8439;
        (void)hoisted__Str_8439;
        (void)hoisted__Str_8440;
        (void)hoisted__Str_8440;
        Array__Str_set(_va_Array_249, hoisted__U32_8438, &hoisted__Str_8439, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8440);
        Str_delete(&hoisted__Str_8440, (Bool){0});
        U32 hoisted__U32_8441 = 1;
        (void)hoisted__U32_8441;
        Str *hoisted__Str_8442 = Str_to_str(a);
        (void)hoisted__Str_8442;
        (void)hoisted__Str_8443;
        (void)hoisted__Str_8443;
        Array__Str_set(_va_Array_249, hoisted__U32_8441, hoisted__Str_8442, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8443);
        Str_delete(&hoisted__Str_8443, (Bool){0});
        U32 hoisted__U32_8444 = 2;
        (void)hoisted__U32_8444;
        (void)hoisted__Str_8445;
        (void)hoisted__Str_8445;
        (void)hoisted__Str_8446;
        (void)hoisted__Str_8446;
        Array__Str_set(_va_Array_249, hoisted__U32_8444, &hoisted__Str_8445, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8446);
        Str_delete(&hoisted__Str_8446, (Bool){0});
        U32 hoisted__U32_8447 = 3;
        (void)hoisted__U32_8447;
        Str *hoisted__Str_8448 = Str_to_str(b);
        (void)hoisted__Str_8448;
        (void)hoisted__Str_8449;
        (void)hoisted__Str_8449;
        Array__Str_set(_va_Array_249, hoisted__U32_8447, hoisted__Str_8448, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8449);
        Str_delete(&hoisted__Str_8449, (Bool){0});
        U32 hoisted__U32_8450 = 4;
        (void)hoisted__U32_8450;
        (void)hoisted__Str_8451;
        (void)hoisted__Str_8451;
        (void)hoisted__Str_8452;
        (void)hoisted__Str_8452;
        Array__Str_set(_va_Array_249, hoisted__U32_8450, &hoisted__Str_8451, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8452);
        OutOfBounds_delete(_va_Array_249_eo, 1);
        Str_delete(&hoisted__Str_8452, (Bool){0});
        panic(_va_Array_249, loc);
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
U64 U64_add_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_add(*(U64 *)_a0, *(U64 *)_a1);
}
static __attribute__((unused)) TilClosure U64_add_dyn__til_closure = { (void *)U64_add_dyn, NULL, NULL };
U64 U64_sub_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_sub(*(U64 *)_a0, *(U64 *)_a1);
}
static __attribute__((unused)) TilClosure U64_sub_dyn__til_closure = { (void *)U64_sub_dyn, NULL, NULL };
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
U32 U32_add_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_add(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_add_dyn__til_closure = { (void *)U32_add_dyn, NULL, NULL };
U32 U32_sub_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_sub(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_sub_dyn__til_closure = { (void *)U32_sub_dyn, NULL, NULL };
U32 U32_mul_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_mul(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_mul_dyn__til_closure = { (void *)U32_mul_dyn, NULL, NULL };
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
Bool U32_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_eq(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_eq_dyn__til_closure = { (void *)U32_eq_dyn, NULL, NULL };
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
Bool I32_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_eq(*(I32 *)_a0, *(I32 *)_a1);
}
static __attribute__((unused)) TilClosure I32_eq_dyn__til_closure = { (void *)I32_eq_dyn, NULL, NULL };
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
Bool I32_neq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_neq(*(I32 *)_a0, *(I32 *)_a1);
}
static __attribute__((unused)) TilClosure I32_neq_dyn__til_closure = { (void *)I32_neq_dyn, NULL, NULL };
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
I64 I64_add_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_add(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_add_dyn__til_closure = { (void *)I64_add_dyn, NULL, NULL };
I64 I64_sub_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_sub(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_sub_dyn__til_closure = { (void *)I64_sub_dyn, NULL, NULL };
I64 I64_div_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_div(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_div_dyn__til_closure = { (void *)I64_div_dyn, NULL, NULL };
I64 I64_mod_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_mod(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_mod_dyn__til_closure = { (void *)I64_mod_dyn, NULL, NULL };
Bool I64_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_eq(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_eq_dyn__til_closure = { (void *)I64_eq_dyn, NULL, NULL };
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)&U64_add_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)&U64_sub_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U64_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U64_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)&U32_to_i64_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)&U32_add_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)&U32_sub_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)&U32_mul_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U32_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U32_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&U32_eq_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&I32_eq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)&I32_neq_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)&I64_add_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)&I64_sub_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)&I64_div_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)&I64_mod_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&I64_eq_dyn__til_closure;
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
