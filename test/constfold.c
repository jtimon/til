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
    FuncType_TAG_LazyProc
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
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
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
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
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
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
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
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
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
    U32 hoisted__U32_12 = 0;
    (void)hoisted__U32_12;
    U64 hoisted__U64_13 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_12); });
    (void)hoisted__U64_13;
    return hoisted__U64_13;
}

void U64_inc(U64 * self) {
    U64 hoisted__U64_29 = 1ULL;
    (void)hoisted__U64_29;
    U64 hoisted__U64_30 = U64_add(DEREF(self), hoisted__U64_29);
    (void)hoisted__U64_30;
    *self = hoisted__U64_30;
}

void U64_dec(U64 * self) {
    U64 hoisted__U64_31 = 1ULL;
    (void)hoisted__U64_31;
    U64 hoisted__U64_32 = U64_sub(DEREF(self), hoisted__U64_31);
    (void)hoisted__U64_32;
    *self = hoisted__U64_32;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_37 = 8;
    (void)hoisted__U32_37;
    return hoisted__U32_37;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_106 = 0;
    (void)hoisted__U32_106;
    U64 hoisted__U64_107 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_106); });
    (void)hoisted__U64_107;
    return hoisted__U64_107;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_122 = U32_to_i64(val);
    (void)hoisted__I64_122;
    Str *hoisted__Str_123 = I64_to_str(hoisted__I64_122);
    (void)hoisted__Str_123;
    return hoisted__Str_123;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_124 = 1;
    (void)hoisted__U32_124;
    U32 hoisted__U32_125 = U32_add(DEREF(self), hoisted__U32_124);
    (void)hoisted__U32_125;
    *self = hoisted__U32_125;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_126 = 1;
    (void)hoisted__U32_126;
    U32 hoisted__U32_127 = U32_sub(DEREF(self), hoisted__U32_126);
    (void)hoisted__U32_127;
    *self = hoisted__U32_127;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_136 = 4;
    (void)hoisted__U32_136;
    return hoisted__U32_136;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_203 = 0;
    (void)hoisted__U32_203;
    U64 hoisted__U64_204 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_203); });
    (void)hoisted__U64_204;
    return hoisted__U64_204;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_207 = U32_cmp(a, b);
    (void)hoisted__I64_207;
    I64 hoisted__I64_208 = -1;
    (void)hoisted__I64_208;
    Bool hoisted__Bool_209 = I64_eq(hoisted__I64_207, hoisted__I64_208);
    (void)hoisted__Bool_209;
    return hoisted__Bool_209;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_210 = U32_cmp(a, b);
    (void)hoisted__I64_210;
    I64 hoisted__I64_211 = 1;
    (void)hoisted__I64_211;
    Bool hoisted__Bool_212 = I64_eq(hoisted__I64_210, hoisted__I64_211);
    (void)hoisted__Bool_212;
    return hoisted__Bool_212;
}

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_213 = U32_eq(a, b);
    (void)hoisted__Bool_213;
    Bool hoisted__Bool_214 = not(hoisted__Bool_213);
    (void)hoisted__Bool_214;
    return hoisted__Bool_214;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_215 = U32_gt(a, b);
    (void)hoisted__Bool_215;
    Bool hoisted__Bool_216 = not(hoisted__Bool_215);
    (void)hoisted__Bool_216;
    return hoisted__Bool_216;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_217 = U32_lt(a, b);
    (void)hoisted__Bool_217;
    Bool hoisted__Bool_218 = not(hoisted__Bool_217);
    (void)hoisted__Bool_218;
    return hoisted__Bool_218;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_241 = 4;
    (void)hoisted__U32_241;
    return hoisted__U32_241;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_353 = 0;
    (void)hoisted__U32_353;
    U64 hoisted__U64_354 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_353); });
    (void)hoisted__U64_354;
    return hoisted__U64_354;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_391 = 1;
    (void)hoisted__U32_391;
    return hoisted__U32_391;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_392 = 0;
    (void)hoisted__U32_392;
    U64 hoisted__U64_393 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_392); });
    (void)hoisted__U64_393;
    return hoisted__U64_393;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_422 = 1;
    (void)hoisted__U32_422;
    return hoisted__U32_422;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_489 = 0;
    (void)hoisted__U32_489;
    U64 hoisted__U64_490 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_489); });
    (void)hoisted__U64_490;
    return hoisted__U64_490;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_631 = parts;
        (void)_fc_Array__Str_631;
        (void)_fc_Array__Str_631;
        U32 _fi_USize_631 = 0;
        (void)_fi_USize_631;
        I64 _forin_err_kind_631 = 0;
        (void)_forin_err_kind_631;
        OutOfBounds *_forin_OutOfBounds_631 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_631->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_631;
        while (1) {
            U32 hoisted__U32_639 = Array__Str_len(_fc_Array__Str_631);
            (void)hoisted__U32_639;
            Bool _wcond_Bool_632 = U32_lt(_fi_USize_631, hoisted__U32_639);
            (void)_wcond_Bool_632;
            if (_wcond_Bool_632) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_631, &_fi_USize_631, &_forin_err_kind_631, _forin_OutOfBounds_631);
            I64 hoisted__I64_640 = 0;
            (void)hoisted__I64_640;
            Bool hoisted__Bool_641 = I64_eq(_forin_err_kind_631, hoisted__I64_640);
            (void)hoisted__Bool_641;
            Bool hoisted__Bool_642 = not(hoisted__Bool_641);
            (void)hoisted__Bool_642;
            if (hoisted__Bool_642) {
                U32 hoisted__U32_633 = 2;
                (void)hoisted__U32_633;
                Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_633);
                (void)_va_Array_16;
                I64 _va_Array_16_ek = 0;
                (void)_va_Array_16_ek;
                OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
                _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_16_eo;
                U32 hoisted__U32_634 = 0;
                (void)hoisted__U32_634;
                Str hoisted__Str_635 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_635;
                Array__Str_set(_va_Array_16, hoisted__U32_634, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_635; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_16_ek, _va_Array_16_eo);
                U32 hoisted__U32_636 = 1;
                (void)hoisted__U32_636;
                Str hoisted__Str_637 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_637;
                Array__Str_set(_va_Array_16, hoisted__U32_636, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_637; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_16_ek, _va_Array_16_eo);
                OutOfBounds_delete(_va_Array_16_eo, 1);
                Str hoisted__Str_638 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_638;
                panic(_va_Array_16, &hoisted__Str_638);
                Str_delete(&hoisted__Str_638, (Bool){0});
            }
            U32 hoisted__U32_643 = 1;
            (void)hoisted__U32_643;
            U32 hoisted__U32_644 = U32_add(_fi_USize_631, hoisted__U32_643);
            (void)hoisted__U32_644;
            _fi_USize_631 = hoisted__U32_644;
            U32 hoisted__U32_645 = Str_len(s);
            (void)hoisted__U32_645;
            U32 hoisted__U32_646 = U32_add(total, hoisted__U32_645);
            (void)hoisted__U32_646;
            total = hoisted__U32_646;
        }
        OutOfBounds_delete(_forin_OutOfBounds_631, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_647 = parts;
        (void)_fc_Array__Str_647;
        (void)_fc_Array__Str_647;
        U32 _fi_USize_647 = 0;
        (void)_fi_USize_647;
        I64 _forin_err_kind_647 = 0;
        (void)_forin_err_kind_647;
        OutOfBounds *_forin_OutOfBounds_647 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_647->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_647;
        while (1) {
            U32 hoisted__U32_655 = Array__Str_len(_fc_Array__Str_647);
            (void)hoisted__U32_655;
            Bool _wcond_Bool_648 = U32_lt(_fi_USize_647, hoisted__U32_655);
            (void)_wcond_Bool_648;
            if (_wcond_Bool_648) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_647, &_fi_USize_647, &_forin_err_kind_647, _forin_OutOfBounds_647);
            I64 hoisted__I64_656 = 0;
            (void)hoisted__I64_656;
            Bool hoisted__Bool_657 = I64_eq(_forin_err_kind_647, hoisted__I64_656);
            (void)hoisted__Bool_657;
            Bool hoisted__Bool_658 = not(hoisted__Bool_657);
            (void)hoisted__Bool_658;
            if (hoisted__Bool_658) {
                U32 hoisted__U32_649 = 2;
                (void)hoisted__U32_649;
                Array__Str *_va_Array_17 = Array__Str_new(hoisted__U32_649);
                (void)_va_Array_17;
                I64 _va_Array_17_ek = 0;
                (void)_va_Array_17_ek;
                OutOfBounds *_va_Array_17_eo = malloc(sizeof(OutOfBounds));
                _va_Array_17_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_17_eo;
                U32 hoisted__U32_650 = 0;
                (void)hoisted__U32_650;
                Str hoisted__Str_651 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_651;
                Array__Str_set(_va_Array_17, hoisted__U32_650, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_651; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_17_ek, _va_Array_17_eo);
                U32 hoisted__U32_652 = 1;
                (void)hoisted__U32_652;
                Str hoisted__Str_653 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_653;
                Array__Str_set(_va_Array_17, hoisted__U32_652, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_653; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_17_ek, _va_Array_17_eo);
                OutOfBounds_delete(_va_Array_17_eo, 1);
                Str hoisted__Str_654 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_654;
                panic(_va_Array_17, &hoisted__Str_654);
                Str_delete(&hoisted__Str_654, (Bool){0});
            }
            U32 hoisted__U32_659 = 1;
            (void)hoisted__U32_659;
            U32 hoisted__U32_660 = U32_add(_fi_USize_647, hoisted__U32_659);
            (void)hoisted__U32_660;
            _fi_USize_647 = hoisted__U32_660;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_647, 1);
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_665 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_665;
    if (hoisted__Bool_665) {
        U32 hoisted__U32_661 = 1;
        (void)hoisted__U32_661;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_661);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_662 = 0;
        (void)hoisted__U32_662;
        Str hoisted__Str_663 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_663;
        Array__Str_set(_va_Array_18, hoisted__U32_662, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_663; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_18_ek, _va_Array_18_eo);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str hoisted__Str_664 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_664;
        panic(_va_Array_18, &hoisted__Str_664);
        Str_delete(&hoisted__Str_664, (Bool){0});
    }
    void *hoisted__v_666 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_666;
    (void)hoisted__v_666;
    return hoisted__v_666;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_676 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_676;
    if (hoisted__Bool_676) {
        min_len = b->count;
    }
    {
        U32 _re_U32_668 = U32_clone(&min_len);
        (void)_re_U32_668;
        U32 _rc_U32_668 = 0;
        (void)_rc_U32_668;
        Bool hoisted__Bool_675 = U32_lte(_rc_U32_668, _re_U32_668);
        (void)hoisted__Bool_675;
        if (hoisted__Bool_675) {
            while (1) {
                Bool _wcond_Bool_669 = U32_lt(_rc_U32_668, _re_U32_668);
                (void)_wcond_Bool_669;
                if (_wcond_Bool_669) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_668);
                U32_inc(&_rc_U32_668);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_670 = 0;
                (void)hoisted__I64_670;
                Bool hoisted__Bool_671 = I64_neq(c, hoisted__I64_670);
                (void)hoisted__Bool_671;
                if (hoisted__Bool_671) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_672 = U32_gt(_rc_U32_668, _re_U32_668);
                (void)_wcond_Bool_672;
                if (_wcond_Bool_672) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_668);
                U32_dec(&_rc_U32_668);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_673 = 0;
                (void)hoisted__I64_673;
                Bool hoisted__Bool_674 = I64_neq(c, hoisted__I64_673);
                (void)hoisted__Bool_674;
                if (hoisted__Bool_674) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_677 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_677;
    return hoisted__I64_677;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_678 = 1;
    (void)hoisted__U32_678;
    U32 hoisted__U64_679 = U32_add(n, hoisted__U32_678);
    (void)hoisted__U64_679;
    void * buf = malloc(hoisted__U64_679);
    I32 hoisted__I32_680 = 0;
    (void)hoisted__I32_680;
    U64 hoisted__U64_681 = 1ULL;
    (void)hoisted__U64_681;
    memset(buf, hoisted__I32_680, hoisted__U64_681);
    I64 hoisted__I64_682 = 0;
    (void)hoisted__I64_682;
    Str *hoisted__Str_683 = malloc(sizeof(Str));
    hoisted__Str_683->c_str = buf;
    hoisted__Str_683->count = hoisted__I64_682;
    hoisted__Str_683->cap = n;
    (void)hoisted__Str_683;
    return hoisted__Str_683;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_694 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_694;
    if (hoisted__Bool_694) {
        U32 hoisted__U32_686 = 1;
        (void)hoisted__U32_686;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_686);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_687 = 0;
        (void)hoisted__U32_687;
        Str hoisted__Str_688 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_688;
        Array__Str_set(_va_Array_19, hoisted__U32_687, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_688; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_19_ek, _va_Array_19_eo);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str hoisted__Str_689 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_689;
        panic(_va_Array_19, &hoisted__Str_689);
        Str_delete(&hoisted__Str_689, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_695 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_695;
    if (hoisted__Bool_695) {
        U32 hoisted__U32_690 = 1;
        (void)hoisted__U32_690;
        Array__Str *_va_Array_20 = Array__Str_new(hoisted__U32_690);
        (void)_va_Array_20;
        I64 _va_Array_20_ek = 0;
        (void)_va_Array_20_ek;
        OutOfBounds *_va_Array_20_eo = malloc(sizeof(OutOfBounds));
        _va_Array_20_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_20_eo;
        U32 hoisted__U32_691 = 0;
        (void)hoisted__U32_691;
        Str hoisted__Str_692 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_692;
        Array__Str_set(_va_Array_20, hoisted__U32_691, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_692; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_20_ek, _va_Array_20_eo);
        OutOfBounds_delete(_va_Array_20_eo, 1);
        Str hoisted__Str_693 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_693;
        panic(_va_Array_20, &hoisted__Str_693);
        Str_delete(&hoisted__Str_693, (Bool){0});
    }
    void *hoisted__v_696 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_696;
    (void)hoisted__v_696;
    memcpy(hoisted__v_696, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_697 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_697;
    (void)hoisted__v_697;
    I32 hoisted__I32_698 = 0;
    (void)hoisted__I32_698;
    U64 hoisted__U64_699 = 1ULL;
    (void)hoisted__U64_699;
    memset(hoisted__v_697, hoisted__I32_698, hoisted__U64_699);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_700 = 1;
    (void)hoisted__U32_700;
    U32 hoisted__U64_701 = U32_add(val->count, hoisted__U32_700);
    (void)hoisted__U64_701;
    void * new_data = malloc(hoisted__U64_701);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_702 = ptr_add(new_data, val->count);
    (void)hoisted__v_702;
    (void)hoisted__v_702;
    I32 hoisted__I32_703 = 0;
    (void)hoisted__I32_703;
    U64 hoisted__U64_704 = 1ULL;
    (void)hoisted__U64_704;
    memset(hoisted__v_702, hoisted__I32_703, hoisted__U64_704);
    Str *hoisted__Str_705 = malloc(sizeof(Str));
    hoisted__Str_705->c_str = new_data;
    hoisted__Str_705->count = val->count;
    hoisted__Str_705->cap = val->count;
    (void)hoisted__Str_705;
    return hoisted__Str_705;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_706 = Str_clone(self);
    (void)hoisted__Str_706;
    return hoisted__Str_706;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_707 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_707;
    if (hoisted__Bool_707) {
        free(self->c_str);
    }
    Bool hoisted__Bool_708 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_708;
    Bool hoisted__Bool_709 = and(call_free, hoisted__Bool_708);
    (void)hoisted__Bool_709;
    if (hoisted__Bool_709) {
        free(self);
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_904 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_904;
    return hoisted__U64_904;
}

U32 Str_size(void) {
    U32 hoisted__U32_1127 = 16;
    (void)hoisted__U32_1127;
    return hoisted__U32_1127;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1128 = Str_cmp(a, b);
    (void)hoisted__I64_1128;
    I64 hoisted__I64_1129 = 0;
    (void)hoisted__I64_1129;
    Bool hoisted__Bool_1130 = I64_eq(hoisted__I64_1128, hoisted__I64_1129);
    (void)hoisted__Bool_1130;
    return hoisted__Bool_1130;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1139 = Str_eq(a, b);
    (void)hoisted__Bool_1139;
    Bool hoisted__Bool_1140 = not(hoisted__Bool_1139);
    (void)hoisted__Bool_1140;
    return hoisted__Bool_1140;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1235 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1235->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1235;
    return hoisted__OutOfBounds_1235;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1236 = 0;
    (void)hoisted__Bool_1236;
    Str_delete(&self->msg, hoisted__Bool_1236);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1237 = 0;
    (void)hoisted__U32_1237;
    U64 hoisted__U64_1238 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1237); });
    (void)hoisted__U64_1238;
    return hoisted__U64_1238;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1253 = 16;
    (void)hoisted__U32_1253;
    return hoisted__U32_1253;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1292 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1292;
    U32 hoisted__U32_1293 = 16;
    (void)hoisted__U32_1293;
    Type *hoisted__Type_1294 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1294;
    U64 hoisted__U64_1295 = (U64)(cap);
    (void)hoisted__U64_1295;
    Type_delete(hoisted__Type_1292, 1);
    U64 hoisted__U64_1296 = (U64)(hoisted__U32_1293);
    (void)hoisted__U64_1296;
    Type_delete(hoisted__Type_1294, 1);
    void * hoisted__v_1297 = calloc(hoisted__U64_1295, hoisted__U64_1296);
    (void)hoisted__v_1297;
    Array__Str *hoisted__Array__Str_1298 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1298->data = hoisted__v_1297;
    hoisted__Array__Str_1298->cap = cap;
    (void)hoisted__Array__Str_1298;
    return hoisted__Array__Str_1298;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1320 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1320;
    if (hoisted__Bool_1320) {
        U32 hoisted__U32_1299 = 6;
        (void)hoisted__U32_1299;
        Array__Str *_va_Array_36 = Array__Str_new(hoisted__U32_1299);
        (void)_va_Array_36;
        I64 _va_Array_36_ek = 0;
        (void)_va_Array_36_ek;
        OutOfBounds *_va_Array_36_eo = malloc(sizeof(OutOfBounds));
        _va_Array_36_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_36_eo;
        U32 hoisted__U32_1300 = 0;
        (void)hoisted__U32_1300;
        Str hoisted__Str_1301 = (Str){.c_str = (void *)"./src/core/str.til:28:44", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1301;
        Array__Str_set(_va_Array_36, hoisted__U32_1300, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1301; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_36_ek, _va_Array_36_eo);
        U32 hoisted__U32_1302 = 1;
        (void)hoisted__U32_1302;
        Str hoisted__Str_1303 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1303;
        Array__Str_set(_va_Array_36, hoisted__U32_1302, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1303; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_36_ek, _va_Array_36_eo);
        U32 hoisted__U32_1304 = 2;
        (void)hoisted__U32_1304;
        Str *hoisted__Str_1305 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1305;
        Array__Str_set(_va_Array_36, hoisted__U32_1304, hoisted__Str_1305, &_va_Array_36_ek, _va_Array_36_eo);
        U32 hoisted__U32_1306 = 3;
        (void)hoisted__U32_1306;
        Str hoisted__Str_1307 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1307;
        Array__Str_set(_va_Array_36, hoisted__U32_1306, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1307; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_36_ek, _va_Array_36_eo);
        U32 hoisted__U32_1308 = 4;
        (void)hoisted__U32_1308;
        Str *hoisted__Str_1309 = U32_to_str(self->cap);
        (void)hoisted__Str_1309;
        Array__Str_set(_va_Array_36, hoisted__U32_1308, hoisted__Str_1309, &_va_Array_36_ek, _va_Array_36_eo);
        U32 hoisted__U32_1310 = 5;
        (void)hoisted__U32_1310;
        Str hoisted__Str_1311 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1311;
        Array__Str_set(_va_Array_36, hoisted__U32_1310, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1311; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_36_ek, _va_Array_36_eo);
        OutOfBounds_delete(_va_Array_36_eo, 1);
        OutOfBounds *hoisted__OutOfBounds_1312 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_36); hoisted__OutOfBounds_1312->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1312;
        U32 hoisted__U32_1313 = 16;
        (void)hoisted__U32_1313;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1312, hoisted__U32_1313);
        OutOfBounds_delete(hoisted__OutOfBounds_1312, 1);
        I64 hoisted__I64_1314 = 3;
        (void)hoisted__I64_1314;
        *_err_kind = hoisted__I64_1314;
    }
    I64 hoisted__I64_1321 = 0;
    (void)hoisted__I64_1321;
    Bool hoisted__Bool_1322 = I64_eq(DEREF(_err_kind), hoisted__I64_1321);
    (void)hoisted__Bool_1322;
    if (hoisted__Bool_1322) {
        U32 hoisted__U32_1315 = 16;
        (void)hoisted__U32_1315;
        U32 hoisted__U32_1316 = U32_mul(DEREF(i), hoisted__U32_1315);
        (void)hoisted__U32_1316;
        Type *hoisted__Type_1317 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1317;
        U64 hoisted__U64_1318 = (U64)(hoisted__U32_1316);
        (void)hoisted__U64_1318;
        Type_delete(hoisted__Type_1317, 1);
        void *hoisted__v_1319 = ptr_add(self->data, hoisted__U64_1318);
        (void)hoisted__v_1319;
        (void)hoisted__v_1319;
        { Str * _ret_val = hoisted__v_1319;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1357 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1357;
    if (hoisted__Bool_1357) {
        U32 hoisted__U32_1323 = 6;
        (void)hoisted__U32_1323;
        Array__Str *_va_Array_37 = Array__Str_new(hoisted__U32_1323);
        (void)_va_Array_37;
        I64 _va_Array_37_ek = 0;
        (void)_va_Array_37_ek;
        OutOfBounds *_va_Array_37_eo = malloc(sizeof(OutOfBounds));
        _va_Array_37_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_37_eo;
        U32 hoisted__U32_1324 = 0;
        (void)hoisted__U32_1324;
        Str hoisted__Str_1325 = (Str){.c_str = (void *)"./src/core/str.til:39:44", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1325;
        Array__Str_set(_va_Array_37, hoisted__U32_1324, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1325; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_37_ek, _va_Array_37_eo);
        U32 hoisted__U32_1326 = 1;
        (void)hoisted__U32_1326;
        Str hoisted__Str_1327 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1327;
        Array__Str_set(_va_Array_37, hoisted__U32_1326, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1327; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_37_ek, _va_Array_37_eo);
        U32 hoisted__U32_1328 = 2;
        (void)hoisted__U32_1328;
        Str *hoisted__Str_1329 = U32_to_str(i);
        (void)hoisted__Str_1329;
        Array__Str_set(_va_Array_37, hoisted__U32_1328, hoisted__Str_1329, &_va_Array_37_ek, _va_Array_37_eo);
        U32 hoisted__U32_1330 = 3;
        (void)hoisted__U32_1330;
        Str hoisted__Str_1331 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1331;
        Array__Str_set(_va_Array_37, hoisted__U32_1330, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1331; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_37_ek, _va_Array_37_eo);
        U32 hoisted__U32_1332 = 4;
        (void)hoisted__U32_1332;
        Str *hoisted__Str_1333 = U32_to_str(self->cap);
        (void)hoisted__Str_1333;
        Array__Str_set(_va_Array_37, hoisted__U32_1332, hoisted__Str_1333, &_va_Array_37_ek, _va_Array_37_eo);
        U32 hoisted__U32_1334 = 5;
        (void)hoisted__U32_1334;
        Str hoisted__Str_1335 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1335;
        Array__Str_set(_va_Array_37, hoisted__U32_1334, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1335; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_37_ek, _va_Array_37_eo);
        OutOfBounds_delete(_va_Array_37_eo, 1);
        OutOfBounds *hoisted__OutOfBounds_1336 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_37); hoisted__OutOfBounds_1336->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1336;
        U32 hoisted__U32_1337 = 16;
        (void)hoisted__U32_1337;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1336, hoisted__U32_1337);
        OutOfBounds_delete(hoisted__OutOfBounds_1336, 1);
        I64 hoisted__I64_1338 = 3;
        (void)hoisted__I64_1338;
        *_err_kind = hoisted__I64_1338;
    }
    I64 hoisted__I64_1358 = 0;
    (void)hoisted__I64_1358;
    Bool hoisted__Bool_1359 = I64_eq(DEREF(_err_kind), hoisted__I64_1358);
    (void)hoisted__Bool_1359;
    if (hoisted__Bool_1359) {
        U32 hoisted__U32_1339 = 16;
        (void)hoisted__U32_1339;
        U32 hoisted__U32_1340 = U32_mul(i, hoisted__U32_1339);
        (void)hoisted__U32_1340;
        Type *hoisted__Type_1341 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1341;
        U64 hoisted__U64_1342 = (U64)(hoisted__U32_1340);
        (void)hoisted__U64_1342;
        Type_delete(hoisted__Type_1341, 1);
        Str *hoisted__Str_1343 = ptr_add(self->data, hoisted__U64_1342);
        (void)hoisted__Str_1343;
        (void)hoisted__Str_1343;
        Bool hoisted__Bool_1344 = 0;
        (void)hoisted__Bool_1344;
        Str_delete(hoisted__Str_1343, hoisted__Bool_1344);
        U32 hoisted__U32_1345 = 16;
        (void)hoisted__U32_1345;
        U32 hoisted__U32_1346 = U32_mul(i, hoisted__U32_1345);
        (void)hoisted__U32_1346;
        Type *hoisted__Type_1347 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1347;
        U64 hoisted__U64_1348 = (U64)(hoisted__U32_1346);
        (void)hoisted__U64_1348;
        Type_delete(hoisted__Type_1347, 1);
        U32 hoisted__U32_1349 = 16;
        (void)hoisted__U32_1349;
        Type *hoisted__Type_1350 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1350;
        void *hoisted__v_1351 = ptr_add(self->data, hoisted__U64_1348);
        (void)hoisted__v_1351;
        (void)hoisted__v_1351;
        U64 hoisted__U64_1352 = (U64)(hoisted__U32_1349);
        (void)hoisted__U64_1352;
        Type_delete(hoisted__Type_1350, 1);
        memcpy(hoisted__v_1351, val, hoisted__U64_1352);
        U32 hoisted__U32_1353 = 16;
        (void)hoisted__U32_1353;
        Type *hoisted__Type_1354 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1354;
        I32 hoisted__I32_1355 = 0;
        (void)hoisted__I32_1355;
        U64 hoisted__U64_1356 = (U64)(hoisted__U32_1353);
        (void)hoisted__U64_1356;
        Type_delete(hoisted__Type_1354, 1);
        memset(val, hoisted__I32_1355, hoisted__U64_1356);
    }
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1360 = self->cap;
        (void)_re_U32_1360;
        U32 _rc_U32_1360 = 0;
        (void)_rc_U32_1360;
        Bool hoisted__Bool_1375 = U32_lte(_rc_U32_1360, _re_U32_1360);
        (void)hoisted__Bool_1375;
        if (hoisted__Bool_1375) {
            while (1) {
                Bool _wcond_Bool_1361 = U32_lt(_rc_U32_1360, _re_U32_1360);
                (void)_wcond_Bool_1361;
                if (_wcond_Bool_1361) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1360);
                U32_inc(&_rc_U32_1360);
                U32 hoisted__U32_1362 = 16;
                (void)hoisted__U32_1362;
                U32 hoisted__U32_1363 = U32_mul(i, hoisted__U32_1362);
                (void)hoisted__U32_1363;
                Type *hoisted__Type_1364 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1364;
                U64 hoisted__U64_1365 = (U64)(hoisted__U32_1363);
                (void)hoisted__U64_1365;
                Type_delete(hoisted__Type_1364, 1);
                Str *hoisted__Str_1366 = ptr_add(self->data, hoisted__U64_1365);
                (void)hoisted__Str_1366;
                (void)hoisted__Str_1366;
                Bool hoisted__Bool_1367 = 0;
                (void)hoisted__Bool_1367;
                Str_delete(hoisted__Str_1366, hoisted__Bool_1367);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1368 = U32_gt(_rc_U32_1360, _re_U32_1360);
                (void)_wcond_Bool_1368;
                if (_wcond_Bool_1368) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1360);
                U32_dec(&_rc_U32_1360);
                U32 hoisted__U32_1369 = 16;
                (void)hoisted__U32_1369;
                U32 hoisted__U32_1370 = U32_mul(i, hoisted__U32_1369);
                (void)hoisted__U32_1370;
                Type *hoisted__Type_1371 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1371;
                U64 hoisted__U64_1372 = (U64)(hoisted__U32_1370);
                (void)hoisted__U64_1372;
                Type_delete(hoisted__Type_1371, 1);
                Str *hoisted__Str_1373 = ptr_add(self->data, hoisted__U64_1372);
                (void)hoisted__Str_1373;
                (void)hoisted__Str_1373;
                Bool hoisted__Bool_1374 = 0;
                (void)hoisted__Bool_1374;
                Str_delete(hoisted__Str_1373, hoisted__Bool_1374);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1412 = 16;
    (void)hoisted__U32_1412;
    U32 hoisted__U32_1413 = U32_mul(self->cap, hoisted__U32_1412);
    (void)hoisted__U32_1413;
    Type *hoisted__Type_1414 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1414;
    U64 hoisted__U64_1415 = (U64)(hoisted__U32_1413);
    (void)hoisted__U64_1415;
    Type_delete(hoisted__Type_1414, 1);
    void * new_data = malloc(hoisted__U64_1415);
    {
        U32 _re_U32_1376 = self->cap;
        (void)_re_U32_1376;
        U32 _rc_U32_1376 = 0;
        (void)_rc_U32_1376;
        Bool hoisted__Bool_1411 = U32_lte(_rc_U32_1376, _re_U32_1376);
        (void)hoisted__Bool_1411;
        if (hoisted__Bool_1411) {
            while (1) {
                Bool _wcond_Bool_1377 = U32_lt(_rc_U32_1376, _re_U32_1376);
                (void)_wcond_Bool_1377;
                if (_wcond_Bool_1377) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1376);
                U32_inc(&_rc_U32_1376);
                U32 hoisted__U32_1378 = 16;
                (void)hoisted__U32_1378;
                U32 hoisted__U32_1379 = U32_mul(i, hoisted__U32_1378);
                (void)hoisted__U32_1379;
                Type *hoisted__Type_1380 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1380;
                U64 hoisted__U64_1381 = (U64)(hoisted__U32_1379);
                (void)hoisted__U64_1381;
                Type_delete(hoisted__Type_1380, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1381);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1382 = 16;
                (void)hoisted__U32_1382;
                U32 hoisted__U32_1383 = U32_mul(i, hoisted__U32_1382);
                (void)hoisted__U32_1383;
                Type *hoisted__Type_1384 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1384;
                U64 hoisted__U64_1385 = (U64)(hoisted__U32_1383);
                (void)hoisted__U64_1385;
                Type_delete(hoisted__Type_1384, 1);
                U32 hoisted__U32_1386 = 16;
                (void)hoisted__U32_1386;
                Type *hoisted__Type_1387 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1387;
                void *hoisted__v_1388 = ptr_add(new_data, hoisted__U64_1385);
                (void)hoisted__v_1388;
                (void)hoisted__v_1388;
                U64 hoisted__U64_1389 = (U64)(hoisted__U32_1386);
                (void)hoisted__U64_1389;
                Type_delete(hoisted__Type_1387, 1);
                memcpy(hoisted__v_1388, cloned, hoisted__U64_1389);
                U32 hoisted__U32_1390 = 16;
                (void)hoisted__U32_1390;
                Type *hoisted__Type_1391 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1391;
                I32 hoisted__I32_1392 = 0;
                (void)hoisted__I32_1392;
                U64 hoisted__U64_1393 = (U64)(hoisted__U32_1390);
                (void)hoisted__U64_1393;
                Type_delete(hoisted__Type_1391, 1);
                memset(cloned, hoisted__I32_1392, hoisted__U64_1393);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1394 = U32_gt(_rc_U32_1376, _re_U32_1376);
                (void)_wcond_Bool_1394;
                if (_wcond_Bool_1394) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1376);
                U32_dec(&_rc_U32_1376);
                U32 hoisted__U32_1395 = 16;
                (void)hoisted__U32_1395;
                U32 hoisted__U32_1396 = U32_mul(i, hoisted__U32_1395);
                (void)hoisted__U32_1396;
                Type *hoisted__Type_1397 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1397;
                U64 hoisted__U64_1398 = (U64)(hoisted__U32_1396);
                (void)hoisted__U64_1398;
                Type_delete(hoisted__Type_1397, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1398);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1399 = 16;
                (void)hoisted__U32_1399;
                U32 hoisted__U32_1400 = U32_mul(i, hoisted__U32_1399);
                (void)hoisted__U32_1400;
                Type *hoisted__Type_1401 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1401;
                U64 hoisted__U64_1402 = (U64)(hoisted__U32_1400);
                (void)hoisted__U64_1402;
                Type_delete(hoisted__Type_1401, 1);
                U32 hoisted__U32_1403 = 16;
                (void)hoisted__U32_1403;
                Type *hoisted__Type_1404 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1404;
                void *hoisted__v_1405 = ptr_add(new_data, hoisted__U64_1402);
                (void)hoisted__v_1405;
                (void)hoisted__v_1405;
                U64 hoisted__U64_1406 = (U64)(hoisted__U32_1403);
                (void)hoisted__U64_1406;
                Type_delete(hoisted__Type_1404, 1);
                memcpy(hoisted__v_1405, cloned, hoisted__U64_1406);
                U32 hoisted__U32_1407 = 16;
                (void)hoisted__U32_1407;
                Type *hoisted__Type_1408 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1408;
                I32 hoisted__I32_1409 = 0;
                (void)hoisted__I32_1409;
                U64 hoisted__U64_1410 = (U64)(hoisted__U32_1407);
                (void)hoisted__U64_1410;
                Type_delete(hoisted__Type_1408, 1);
                memset(cloned, hoisted__I32_1409, hoisted__U64_1410);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1416 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1416->data = new_data;
    hoisted__Array__Str_1416->cap = self->cap;
    (void)hoisted__Array__Str_1416;
    return hoisted__Array__Str_1416;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1417 = 16;
    (void)hoisted__U32_1417;
    return hoisted__U32_1417;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1418 = 16;
    (void)hoisted__U32_1418;
    Type *hoisted__Type_1419 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1419;
    U64 hoisted__U64_1420 = (U64)(hoisted__U32_1418);
    (void)hoisted__U64_1420;
    Type_delete(hoisted__Type_1419, 1);
    void * hoisted__v_1421 = malloc(hoisted__U64_1420);
    (void)hoisted__v_1421;
    U32 hoisted__U32_1422 = 0;
    (void)hoisted__U32_1422;
    I64 hoisted__I64_1423 = 1;
    (void)hoisted__I64_1423;
    Vec__Str *hoisted__Vec__Str_1424 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1424->data = hoisted__v_1421;
    hoisted__Vec__Str_1424->count = hoisted__U32_1422;
    hoisted__Vec__Str_1424->cap = hoisted__I64_1423;
    (void)hoisted__Vec__Str_1424;
    return hoisted__Vec__Str_1424;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1425 = self->count;
        (void)_re_U32_1425;
        U32 _rc_U32_1425 = 0;
        (void)_rc_U32_1425;
        Bool hoisted__Bool_1440 = U32_lte(_rc_U32_1425, _re_U32_1425);
        (void)hoisted__Bool_1440;
        if (hoisted__Bool_1440) {
            while (1) {
                Bool _wcond_Bool_1426 = U32_lt(_rc_U32_1425, _re_U32_1425);
                (void)_wcond_Bool_1426;
                if (_wcond_Bool_1426) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1425);
                U32_inc(&_rc_U32_1425);
                U32 hoisted__U32_1427 = 16;
                (void)hoisted__U32_1427;
                U32 hoisted__U32_1428 = U32_mul(i, hoisted__U32_1427);
                (void)hoisted__U32_1428;
                Type *hoisted__Type_1429 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1429;
                U64 hoisted__U64_1430 = (U64)(hoisted__U32_1428);
                (void)hoisted__U64_1430;
                Type_delete(hoisted__Type_1429, 1);
                Str *hoisted__Str_1431 = ptr_add(self->data, hoisted__U64_1430);
                (void)hoisted__Str_1431;
                (void)hoisted__Str_1431;
                Bool hoisted__Bool_1432 = 0;
                (void)hoisted__Bool_1432;
                Str_delete(hoisted__Str_1431, hoisted__Bool_1432);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1433 = U32_gt(_rc_U32_1425, _re_U32_1425);
                (void)_wcond_Bool_1433;
                if (_wcond_Bool_1433) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1425);
                U32_dec(&_rc_U32_1425);
                U32 hoisted__U32_1434 = 16;
                (void)hoisted__U32_1434;
                U32 hoisted__U32_1435 = U32_mul(i, hoisted__U32_1434);
                (void)hoisted__U32_1435;
                Type *hoisted__Type_1436 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1436;
                U64 hoisted__U64_1437 = (U64)(hoisted__U32_1435);
                (void)hoisted__U64_1437;
                Type_delete(hoisted__Type_1436, 1);
                Str *hoisted__Str_1438 = ptr_add(self->data, hoisted__U64_1437);
                (void)hoisted__Str_1438;
                (void)hoisted__Str_1438;
                Bool hoisted__Bool_1439 = 0;
                (void)hoisted__Bool_1439;
                Str_delete(hoisted__Str_1438, hoisted__Bool_1439);
            }
        }
    }
    U32 hoisted__U32_1441 = 0;
    (void)hoisted__U32_1441;
    self->count = hoisted__U32_1441;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1734 = 16;
    (void)hoisted__U32_1734;
    U32 hoisted__U32_1735 = U32_mul(self->cap, hoisted__U32_1734);
    (void)hoisted__U32_1735;
    Type *hoisted__Type_1736 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1736;
    U64 hoisted__U64_1737 = (U64)(hoisted__U32_1735);
    (void)hoisted__U64_1737;
    Type_delete(hoisted__Type_1736, 1);
    void * new_data = malloc(hoisted__U64_1737);
    {
        U32 _re_U32_1698 = self->count;
        (void)_re_U32_1698;
        U32 _rc_U32_1698 = 0;
        (void)_rc_U32_1698;
        Bool hoisted__Bool_1733 = U32_lte(_rc_U32_1698, _re_U32_1698);
        (void)hoisted__Bool_1733;
        if (hoisted__Bool_1733) {
            while (1) {
                Bool _wcond_Bool_1699 = U32_lt(_rc_U32_1698, _re_U32_1698);
                (void)_wcond_Bool_1699;
                if (_wcond_Bool_1699) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1698);
                U32_inc(&_rc_U32_1698);
                U32 hoisted__U32_1700 = 16;
                (void)hoisted__U32_1700;
                U32 hoisted__U32_1701 = U32_mul(i, hoisted__U32_1700);
                (void)hoisted__U32_1701;
                Type *hoisted__Type_1702 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1702;
                U64 hoisted__U64_1703 = (U64)(hoisted__U32_1701);
                (void)hoisted__U64_1703;
                Type_delete(hoisted__Type_1702, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1703);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1704 = 16;
                (void)hoisted__U32_1704;
                U32 hoisted__U32_1705 = U32_mul(i, hoisted__U32_1704);
                (void)hoisted__U32_1705;
                Type *hoisted__Type_1706 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1706;
                U64 hoisted__U64_1707 = (U64)(hoisted__U32_1705);
                (void)hoisted__U64_1707;
                Type_delete(hoisted__Type_1706, 1);
                U32 hoisted__U32_1708 = 16;
                (void)hoisted__U32_1708;
                Type *hoisted__Type_1709 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1709;
                void *hoisted__v_1710 = ptr_add(new_data, hoisted__U64_1707);
                (void)hoisted__v_1710;
                (void)hoisted__v_1710;
                U64 hoisted__U64_1711 = (U64)(hoisted__U32_1708);
                (void)hoisted__U64_1711;
                Type_delete(hoisted__Type_1709, 1);
                memcpy(hoisted__v_1710, cloned, hoisted__U64_1711);
                U32 hoisted__U32_1712 = 16;
                (void)hoisted__U32_1712;
                Type *hoisted__Type_1713 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1713;
                I32 hoisted__I32_1714 = 0;
                (void)hoisted__I32_1714;
                U64 hoisted__U64_1715 = (U64)(hoisted__U32_1712);
                (void)hoisted__U64_1715;
                Type_delete(hoisted__Type_1713, 1);
                memset(cloned, hoisted__I32_1714, hoisted__U64_1715);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1716 = U32_gt(_rc_U32_1698, _re_U32_1698);
                (void)_wcond_Bool_1716;
                if (_wcond_Bool_1716) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1698);
                U32_dec(&_rc_U32_1698);
                U32 hoisted__U32_1717 = 16;
                (void)hoisted__U32_1717;
                U32 hoisted__U32_1718 = U32_mul(i, hoisted__U32_1717);
                (void)hoisted__U32_1718;
                Type *hoisted__Type_1719 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1719;
                U64 hoisted__U64_1720 = (U64)(hoisted__U32_1718);
                (void)hoisted__U64_1720;
                Type_delete(hoisted__Type_1719, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1720);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1721 = 16;
                (void)hoisted__U32_1721;
                U32 hoisted__U32_1722 = U32_mul(i, hoisted__U32_1721);
                (void)hoisted__U32_1722;
                Type *hoisted__Type_1723 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1723;
                U64 hoisted__U64_1724 = (U64)(hoisted__U32_1722);
                (void)hoisted__U64_1724;
                Type_delete(hoisted__Type_1723, 1);
                U32 hoisted__U32_1725 = 16;
                (void)hoisted__U32_1725;
                Type *hoisted__Type_1726 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1726;
                void *hoisted__v_1727 = ptr_add(new_data, hoisted__U64_1724);
                (void)hoisted__v_1727;
                (void)hoisted__v_1727;
                U64 hoisted__U64_1728 = (U64)(hoisted__U32_1725);
                (void)hoisted__U64_1728;
                Type_delete(hoisted__Type_1726, 1);
                memcpy(hoisted__v_1727, cloned, hoisted__U64_1728);
                U32 hoisted__U32_1729 = 16;
                (void)hoisted__U32_1729;
                Type *hoisted__Type_1730 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1730;
                I32 hoisted__I32_1731 = 0;
                (void)hoisted__I32_1731;
                U64 hoisted__U64_1732 = (U64)(hoisted__U32_1729);
                (void)hoisted__U64_1732;
                Type_delete(hoisted__Type_1730, 1);
                memset(cloned, hoisted__I32_1731, hoisted__U64_1732);
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1738 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1738->data = new_data;
    hoisted__Vec__Str_1738->count = self->count;
    hoisted__Vec__Str_1738->cap = self->cap;
    (void)hoisted__Vec__Str_1738;
    return hoisted__Vec__Str_1738;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1739 = 16;
    (void)hoisted__U32_1739;
    return hoisted__U32_1739;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1742 = 8;
    (void)hoisted__U32_1742;
    return hoisted__U32_1742;
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
    I64 hoisted__I64_1931 = 0;
    (void)hoisted__I64_1931;
    Bool hoisted__Bool_1932 = I64_eq(val, hoisted__I64_1931);
    (void)hoisted__Bool_1932;
    if (hoisted__Bool_1932) {
        U64 hoisted__U64_1901 = 2ULL;
        (void)hoisted__U64_1901;
        void * buf = malloc(hoisted__U64_1901);
        I64 hoisted__I64_1902 = 48;
        (void)hoisted__I64_1902;
        U64 hoisted__U64_1903 = 1ULL;
        (void)hoisted__U64_1903;
        memcpy(buf, &hoisted__I64_1902, hoisted__U64_1903);
        U64 hoisted__U64_1904 = 1ULL;
        (void)hoisted__U64_1904;
        void *hoisted__v_1905 = ptr_add(buf, hoisted__U64_1904);
        (void)hoisted__v_1905;
        (void)hoisted__v_1905;
        I32 hoisted__I32_1906 = 0;
        (void)hoisted__I32_1906;
        U64 hoisted__U64_1907 = 1ULL;
        (void)hoisted__U64_1907;
        memset(hoisted__v_1905, hoisted__I32_1906, hoisted__U64_1907);
        I64 hoisted__I64_1908 = 1;
        (void)hoisted__I64_1908;
        I64 hoisted__I64_1909 = 1;
        (void)hoisted__I64_1909;
        Str *hoisted__Str_1910 = malloc(sizeof(Str));
        hoisted__Str_1910->c_str = buf;
        hoisted__Str_1910->count = hoisted__I64_1908;
        hoisted__Str_1910->cap = hoisted__I64_1909;
        (void)hoisted__Str_1910;
        { Str * _ret_val = hoisted__Str_1910;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1933 = 0;
    (void)hoisted__I64_1933;
    Bool hoisted__Bool_1934 = I64_lt(val, hoisted__I64_1933);
    (void)hoisted__Bool_1934;
    if (hoisted__Bool_1934) {
        Bool hoisted__Bool_1911 = 1;
        (void)hoisted__Bool_1911;
        is_neg = hoisted__Bool_1911;
        I64 hoisted__I64_1912 = 0;
        (void)hoisted__I64_1912;
        I64 hoisted__I64_1913 = I64_sub(hoisted__I64_1912, val);
        (void)hoisted__I64_1913;
        v = hoisted__I64_1913;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1915 = 0;
        (void)hoisted__I64_1915;
        Bool _wcond_Bool_1914 = I64_gt(tmp, hoisted__I64_1915);
        (void)_wcond_Bool_1914;
        if (_wcond_Bool_1914) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1916 = 10;
        (void)hoisted__I64_1916;
        I64 hoisted__I64_1917 = I64_div(tmp, hoisted__I64_1916);
        (void)hoisted__I64_1917;
        tmp = hoisted__I64_1917;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1935 = 1ULL;
    (void)hoisted__U64_1935;
    U64 hoisted__U64_1936 = U64_add(total, hoisted__U64_1935);
    (void)hoisted__U64_1936;
    void * buf = malloc(hoisted__U64_1936);
    if (is_neg) {
        I64 hoisted__I64_1918 = 45;
        (void)hoisted__I64_1918;
        U64 hoisted__U64_1919 = 1ULL;
        (void)hoisted__U64_1919;
        memcpy(buf, &hoisted__I64_1918, hoisted__U64_1919);
    }
    U64 hoisted__U64_1937 = 1ULL;
    (void)hoisted__U64_1937;
    U64 i = U64_sub(total, hoisted__U64_1937);
    while (1) {
        I64 hoisted__I64_1921 = 0;
        (void)hoisted__I64_1921;
        Bool _wcond_Bool_1920 = I64_gt(v, hoisted__I64_1921);
        (void)_wcond_Bool_1920;
        if (_wcond_Bool_1920) {
        } else {
            break;
        }
        I64 hoisted__I64_1922 = 10;
        (void)hoisted__I64_1922;
        I64 hoisted__I64_1923 = I64_mod(v, hoisted__I64_1922);
        (void)hoisted__I64_1923;
        I64 hoisted__I64_1924 = 48;
        (void)hoisted__I64_1924;
        I64 hoisted__I64_1925 = I64_add(hoisted__I64_1923, hoisted__I64_1924);
        (void)hoisted__I64_1925;
        void *hoisted__v_1926 = ptr_add(buf, i);
        (void)hoisted__v_1926;
        (void)hoisted__v_1926;
        U8 hoisted__U8_1927 = I64_to_u8(hoisted__I64_1925);
        (void)hoisted__U8_1927;
        U64 hoisted__U64_1928 = 1ULL;
        (void)hoisted__U64_1928;
        memcpy(hoisted__v_1926, &hoisted__U8_1927, hoisted__U64_1928);
        I64 hoisted__I64_1929 = 10;
        (void)hoisted__I64_1929;
        I64 hoisted__I64_1930 = I64_div(v, hoisted__I64_1929);
        (void)hoisted__I64_1930;
        v = hoisted__I64_1930;
        U64_dec(&i);
    }
    void *hoisted__v_1938 = ptr_add(buf, total);
    (void)hoisted__v_1938;
    (void)hoisted__v_1938;
    I32 hoisted__I32_1939 = 0;
    (void)hoisted__I32_1939;
    U64 hoisted__U64_1940 = 1ULL;
    (void)hoisted__U64_1940;
    memset(hoisted__v_1938, hoisted__I32_1939, hoisted__U64_1940);
    Str *hoisted__Str_1941 = malloc(sizeof(Str));
    hoisted__Str_1941->c_str = buf;
    hoisted__Str_1941->count = total;
    hoisted__Str_1941->cap = total;
    (void)hoisted__Str_1941;
    return hoisted__Str_1941;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1961 = 8;
    (void)hoisted__U32_1961;
    return hoisted__U32_1961;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2082 = 0;
    (void)hoisted__U32_2082;
    U64 hoisted__U64_2083 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2082); });
    (void)hoisted__U64_2083;
    return hoisted__U64_2083;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2086 = I64_cmp(a, b);
    (void)hoisted__I64_2086;
    I64 hoisted__I64_2087 = -1;
    (void)hoisted__I64_2087;
    Bool hoisted__Bool_2088 = I64_eq(hoisted__I64_2086, hoisted__I64_2087);
    (void)hoisted__Bool_2088;
    return hoisted__Bool_2088;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2089 = I64_cmp(a, b);
    (void)hoisted__I64_2089;
    I64 hoisted__I64_2090 = 1;
    (void)hoisted__I64_2090;
    Bool hoisted__Bool_2091 = I64_eq(hoisted__I64_2089, hoisted__I64_2090);
    (void)hoisted__Bool_2091;
    return hoisted__Bool_2091;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2092 = I64_eq(a, b);
    (void)hoisted__Bool_2092;
    Bool hoisted__Bool_2093 = not(hoisted__Bool_2092);
    (void)hoisted__Bool_2093;
    return hoisted__Bool_2093;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2128 = 0;
    (void)_m_Bool_2128;
    {
        Bool hoisted__Bool_2131 = 1;
        (void)hoisted__Bool_2131;
        Bool hoisted__Bool_2132 = Bool_eq(a, hoisted__Bool_2131);
        (void)hoisted__Bool_2132;
        if (hoisted__Bool_2132) {
            Bool hoisted__Bool_2129 = Bool_clone(&b);
            (void)hoisted__Bool_2129;
            _m_Bool_2128 = hoisted__Bool_2129;
        } else {
            Bool hoisted__Bool_2130 = 0;
            (void)hoisted__Bool_2130;
            _m_Bool_2128 = hoisted__Bool_2130;
        }
    }
    return _m_Bool_2128;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2142 = Bool_eq(a, b);
    (void)hoisted__Bool_2142;
    if (hoisted__Bool_2142) {
        I64 hoisted__I64_2140 = 0;
        (void)hoisted__I64_2140;
        { I64 _ret_val = hoisted__I64_2140;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2141 = -1;
        (void)hoisted__I64_2141;
        return hoisted__I64_2141;
    }
    I64 hoisted__I64_2143 = 1;
    (void)hoisted__I64_2143;
    return hoisted__I64_2143;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2144 = 1;
    (void)hoisted__U32_2144;
    return hoisted__U32_2144;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2145 = 0;
    (void)hoisted__U32_2145;
    U64 hoisted__U64_2146 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2145); });
    (void)hoisted__U64_2146;
    return hoisted__U64_2146;
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
    Bool hoisted__Bool_2172 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2172;
    if (hoisted__Bool_2172) {
        Bool hoisted__Bool_2162 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2162;
        { Bool _ret_val = hoisted__Bool_2162;
                return _ret_val; }
    }
    Bool hoisted__Bool_2173 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2173;
    if (hoisted__Bool_2173) {
        Bool hoisted__Bool_2163 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2163;
        { Bool _ret_val = hoisted__Bool_2163;
                return _ret_val; }
    }
    Bool hoisted__Bool_2174 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2174;
    if (hoisted__Bool_2174) {
        Bool hoisted__Bool_2164 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2164;
        { Bool _ret_val = hoisted__Bool_2164;
                return _ret_val; }
    }
    Bool hoisted__Bool_2175 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2175;
    if (hoisted__Bool_2175) {
        Bool hoisted__Bool_2165 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2165;
        { Bool _ret_val = hoisted__Bool_2165;
                return _ret_val; }
    }
    Bool hoisted__Bool_2176 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2176;
    if (hoisted__Bool_2176) {
        Bool hoisted__Bool_2166 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2166;
        { Bool _ret_val = hoisted__Bool_2166;
                return _ret_val; }
    }
    Bool hoisted__Bool_2177 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2177;
    if (hoisted__Bool_2177) {
        Bool hoisted__Bool_2167 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2167;
        { Bool _ret_val = hoisted__Bool_2167;
                return _ret_val; }
    }
    Bool hoisted__Bool_2178 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2178;
    if (hoisted__Bool_2178) {
        Bool hoisted__Bool_2168 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2168;
        { Bool _ret_val = hoisted__Bool_2168;
                return _ret_val; }
    }
    Bool hoisted__Bool_2179 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2179;
    if (hoisted__Bool_2179) {
        Bool hoisted__Bool_2169 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2169;
        { Bool _ret_val = hoisted__Bool_2169;
                return _ret_val; }
    }
    Bool hoisted__Bool_2180 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2180;
    if (hoisted__Bool_2180) {
        Bool hoisted__Bool_2170 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2170;
        { Bool _ret_val = hoisted__Bool_2170;
                return _ret_val; }
    }
    Bool hoisted__Bool_2181 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2181;
    if (hoisted__Bool_2181) {
        Bool hoisted__Bool_2171 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2171;
        { Bool _ret_val = hoisted__Bool_2171;
                return _ret_val; }
    }
    Bool hoisted__Bool_2182 = 0;
    (void)hoisted__Bool_2182;
    return hoisted__Bool_2182;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2204 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2204;
    if (hoisted__Bool_2204) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2205 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2206 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2206;
    if (hoisted__Bool_2206) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2207 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2207;
    if (hoisted__Bool_2207) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2208 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2208;
    if (hoisted__Bool_2208) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2209 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2209;
    if (hoisted__Bool_2209) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2210 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2210;
    if (hoisted__Bool_2210) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2211 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2211;
    if (hoisted__Bool_2211) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2212 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2212;
    if (hoisted__Bool_2212) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2213 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2213;
    if (hoisted__Bool_2213) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2214 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2214;
    UNREACHABLE(&hoisted__Str_2214);
    Str_delete(&hoisted__Str_2214, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2215 = 4;
    (void)hoisted__U32_2215;
    return hoisted__U32_2215;
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
    free(val);
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
    free(val);
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
    free(val);
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
    free(val);
    return r;
}
void Type_delete(Type * self, Bool call_free) {
    Bool hoisted__Bool_2267 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2267;
    if (hoisted__Bool_2267) {
        Str *hoisted__Str_2257 = get_payload(self);
        (void)hoisted__Str_2257;
        (void)hoisted__Str_2257;
        Bool hoisted__Bool_2258 = 0;
        (void)hoisted__Bool_2258;
        Str_delete(hoisted__Str_2257, hoisted__Bool_2258);
    }
    Bool hoisted__Bool_2268 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2268;
    if (hoisted__Bool_2268) {
        Str *hoisted__Str_2259 = get_payload(self);
        (void)hoisted__Str_2259;
        (void)hoisted__Str_2259;
        Bool hoisted__Bool_2260 = 0;
        (void)hoisted__Bool_2260;
        Str_delete(hoisted__Str_2259, hoisted__Bool_2260);
    }
    Bool hoisted__Bool_2269 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2269;
    if (hoisted__Bool_2269) {
        Str *hoisted__Str_2261 = get_payload(self);
        (void)hoisted__Str_2261;
        (void)hoisted__Str_2261;
        Bool hoisted__Bool_2262 = 0;
        (void)hoisted__Bool_2262;
        Str_delete(hoisted__Str_2261, hoisted__Bool_2262);
    }
    Bool hoisted__Bool_2270 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2270;
    if (hoisted__Bool_2270) {
        Primitive *hoisted__Primitive_2263 = get_payload(self);
        (void)hoisted__Primitive_2263;
        (void)hoisted__Primitive_2263;
        Bool hoisted__Bool_2264 = 0;
        (void)hoisted__Bool_2264;
        Primitive_delete(hoisted__Primitive_2263, hoisted__Bool_2264);
    }
    Bool hoisted__Bool_2271 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2271;
    if (hoisted__Bool_2271) {
        Str *hoisted__Str_2265 = get_payload(self);
        (void)hoisted__Str_2265;
        (void)hoisted__Str_2265;
        Bool hoisted__Bool_2266 = 0;
        (void)hoisted__Bool_2266;
        Str_delete(hoisted__Str_2265, hoisted__Bool_2266);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2340 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2340;
    if (hoisted__Bool_2340) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2341 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2342 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2342;
    if (hoisted__Bool_2342) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2332 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2332;
        Type *hoisted__Type_2333 = Type_Struct(hoisted__Str_2332);
        (void)hoisted__Type_2333;
        { Type * _ret_val = hoisted__Type_2333;
                return _ret_val; }
    }
    Bool hoisted__Bool_2343 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2343;
    if (hoisted__Bool_2343) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2344 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2344;
    if (hoisted__Bool_2344) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2334 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2334;
        Type *hoisted__Type_2335 = Type_Enum(hoisted__Str_2334);
        (void)hoisted__Type_2335;
        { Type * _ret_val = hoisted__Type_2335;
                return _ret_val; }
    }
    Bool hoisted__Bool_2345 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2345;
    if (hoisted__Bool_2345) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2346 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2346;
    if (hoisted__Bool_2346) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2347 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2347;
    if (hoisted__Bool_2347) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2348 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2348;
    if (hoisted__Bool_2348) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2349 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2349;
    if (hoisted__Bool_2349) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2336 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2336;
        Type *hoisted__Type_2337 = Type_Custom(hoisted__Str_2336);
        (void)hoisted__Type_2337;
        { Type * _ret_val = hoisted__Type_2337;
                return _ret_val; }
    }
    Bool hoisted__Bool_2350 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2350;
    if (hoisted__Bool_2350) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2338 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2338;
        Type *hoisted__Type_2339 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2338; _oa; }));
        (void)hoisted__Type_2339;
        { Type * _ret_val = hoisted__Type_2339;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2351 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2351;
    Type *hoisted__Type_2352 = Type_FuncPtrSig(hoisted__Str_2351);
    (void)hoisted__Type_2352;
    return hoisted__Type_2352;
}

U32 Type_size(void) {
    U32 hoisted__U32_2353 = 24;
    (void)hoisted__U32_2353;
    return hoisted__U32_2353;
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
Bool FuncType_eq(FuncType * self, FuncType * other) {
    Bool hoisted__Bool_2454 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2454;
    if (hoisted__Bool_2454) {
        Bool hoisted__Bool_2446 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2446;
        { Bool _ret_val = hoisted__Bool_2446;
                return _ret_val; }
    }
    Bool hoisted__Bool_2455 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2455;
    if (hoisted__Bool_2455) {
        Bool hoisted__Bool_2447 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2447;
        { Bool _ret_val = hoisted__Bool_2447;
                return _ret_val; }
    }
    Bool hoisted__Bool_2456 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2456;
    if (hoisted__Bool_2456) {
        Bool hoisted__Bool_2448 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2448;
        { Bool _ret_val = hoisted__Bool_2448;
                return _ret_val; }
    }
    Bool hoisted__Bool_2457 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2457;
    if (hoisted__Bool_2457) {
        Bool hoisted__Bool_2449 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2449;
        { Bool _ret_val = hoisted__Bool_2449;
                return _ret_val; }
    }
    Bool hoisted__Bool_2458 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2458;
    if (hoisted__Bool_2458) {
        Bool hoisted__Bool_2450 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2450;
        { Bool _ret_val = hoisted__Bool_2450;
                return _ret_val; }
    }
    Bool hoisted__Bool_2459 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2459;
    if (hoisted__Bool_2459) {
        Bool hoisted__Bool_2451 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2451;
        { Bool _ret_val = hoisted__Bool_2451;
                return _ret_val; }
    }
    Bool hoisted__Bool_2460 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2460;
    if (hoisted__Bool_2460) {
        Bool hoisted__Bool_2452 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2452;
        { Bool _ret_val = hoisted__Bool_2452;
                return _ret_val; }
    }
    Bool hoisted__Bool_2461 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2461;
    if (hoisted__Bool_2461) {
        Bool hoisted__Bool_2453 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2453;
        { Bool _ret_val = hoisted__Bool_2453;
                return _ret_val; }
    }
    Bool hoisted__Bool_2462 = 0;
    (void)hoisted__Bool_2462;
    return hoisted__Bool_2462;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2480 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2480;
    if (hoisted__Bool_2480) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2481 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2481;
    if (hoisted__Bool_2481) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2482 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2482;
    if (hoisted__Bool_2482) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2483 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2483;
    if (hoisted__Bool_2483) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2484 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2484;
    if (hoisted__Bool_2484) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2485 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2485;
    if (hoisted__Bool_2485) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2486 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2486;
    if (hoisted__Bool_2486) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2487 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2487;
    if (hoisted__Bool_2487) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2488 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2488;
    UNREACHABLE(&hoisted__Str_2488);
    Str_delete(&hoisted__Str_2488, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2489 = 4;
    (void)hoisted__U32_2489;
    return hoisted__U32_2489;
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
    Bool hoisted__Bool_2494 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2494;
    if (hoisted__Bool_2494) {
        Bool hoisted__Bool_2491 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2491;
        { Bool _ret_val = hoisted__Bool_2491;
                return _ret_val; }
    }
    Bool hoisted__Bool_2495 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2495;
    if (hoisted__Bool_2495) {
        Bool hoisted__Bool_2492 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2492;
        { Bool _ret_val = hoisted__Bool_2492;
                return _ret_val; }
    }
    Bool hoisted__Bool_2496 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2496;
    if (hoisted__Bool_2496) {
        Bool hoisted__Bool_2493 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2493;
        { Bool _ret_val = hoisted__Bool_2493;
                return _ret_val; }
    }
    Bool hoisted__Bool_2497 = 0;
    (void)hoisted__Bool_2497;
    return hoisted__Bool_2497;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2505 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2505;
    if (hoisted__Bool_2505) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2506 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2506;
    if (hoisted__Bool_2506) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2507 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2507;
    if (hoisted__Bool_2507) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2508 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2508;
    UNREACHABLE(&hoisted__Str_2508);
    Str_delete(&hoisted__Str_2508, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2509 = 4;
    (void)hoisted__U32_2509;
    return hoisted__U32_2509;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2511 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2511;
    Declaration *hoisted__Declaration_2512 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2512->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2512->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2512->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2512->is_mut = self->is_mut;
    hoisted__Declaration_2512->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2512->is_priv = self->is_priv;
    hoisted__Declaration_2512->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2512->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2512->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2512->default_value = hoisted__Expr_2511;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2512->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2512;
    return hoisted__Declaration_2512;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2513 = 0;
    (void)hoisted__Bool_2513;
    Str_delete(&self->name, hoisted__Bool_2513);
    Bool hoisted__Bool_2514 = 0;
    (void)hoisted__Bool_2514;
    Str_delete(&self->doc, hoisted__Bool_2514);
    Bool hoisted__Bool_2515 = 0;
    (void)hoisted__Bool_2515;
    Str_delete(&self->explicit_type, hoisted__Bool_2515);
    Bool hoisted__Bool_2516 = 0;
    (void)hoisted__Bool_2516;
    Bool_delete(&self->is_mut, hoisted__Bool_2516);
    Bool hoisted__Bool_2517 = 0;
    (void)hoisted__Bool_2517;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2517);
    Bool hoisted__Bool_2518 = 0;
    (void)hoisted__Bool_2518;
    Bool_delete(&self->is_priv, hoisted__Bool_2518);
    Bool hoisted__Bool_2519 = 0;
    (void)hoisted__Bool_2519;
    Bool_delete(&self->used, hoisted__Bool_2519);
    Bool hoisted__Bool_2520 = 0;
    (void)hoisted__Bool_2520;
    OwnType_delete(&self->own_type, hoisted__Bool_2520);
    Bool hoisted__Bool_2521 = 0;
    (void)hoisted__Bool_2521;
    Type_delete(&self->til_type, hoisted__Bool_2521);
    Bool hoisted__Bool_2522 = 1;
    (void)hoisted__Bool_2522;
    Expr_delete(self->default_value, hoisted__Bool_2522);
    Bool hoisted__Bool_2523 = 0;
    (void)hoisted__Bool_2523;
    Str_delete(&self->orig_name, hoisted__Bool_2523);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2524 = 104;
    (void)hoisted__U32_2524;
    return hoisted__U32_2524;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2526 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2526->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2526->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2526->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2526->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2526->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2526->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2526->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2526->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2526->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2526->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2526->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2526;
    return hoisted__FunctionDef_2526;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2527 = 0;
    (void)hoisted__Bool_2527;
    FuncType_delete(&self->func_type, hoisted__Bool_2527);
    Bool hoisted__Bool_2528 = 0;
    (void)hoisted__Bool_2528;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2528);
    Bool hoisted__Bool_2529 = 0;
    (void)hoisted__Bool_2529;
    Str_delete(&self->return_type, hoisted__Bool_2529);
    Bool hoisted__Bool_2530 = 0;
    (void)hoisted__Bool_2530;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2530);
    Bool hoisted__Bool_2531 = 0;
    (void)hoisted__Bool_2531;
    I32_delete(&self->variadic_index, hoisted__Bool_2531);
    Bool hoisted__Bool_2532 = 0;
    (void)hoisted__Bool_2532;
    I32_delete(&self->kwargs_index, hoisted__Bool_2532);
    Bool hoisted__Bool_2533 = 0;
    (void)hoisted__Bool_2533;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2533);
    Bool hoisted__Bool_2534 = 0;
    (void)hoisted__Bool_2534;
    Bool_delete(&self->auto_generated, hoisted__Bool_2534);
    Bool hoisted__Bool_2535 = 0;
    (void)hoisted__Bool_2535;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2535);
    Bool hoisted__Bool_2536 = 0;
    (void)hoisted__Bool_2536;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2536);
    Bool hoisted__Bool_2537 = 0;
    (void)hoisted__Bool_2537;
    Str_delete(&self->closure_name, hoisted__Bool_2537);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2538 = 0;
    (void)hoisted__U32_2538;
    U64 hoisted__U64_2539 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2538); });
    (void)hoisted__U64_2539;
    return hoisted__U64_2539;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2540 = 104;
    (void)hoisted__U32_2540;
    return hoisted__U32_2540;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2543 = malloc(sizeof(FCallData));
    hoisted__FCallData_2543->is_splat = self->is_splat;
    hoisted__FCallData_2543->does_throw = self->does_throw;
    hoisted__FCallData_2543->is_bang = self->is_bang;
    hoisted__FCallData_2543->own_args = self->own_args;
    hoisted__FCallData_2543->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2543->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2543;
    return hoisted__FCallData_2543;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2544 = 0;
    (void)hoisted__Bool_2544;
    Bool_delete(&self->is_splat, hoisted__Bool_2544);
    Bool hoisted__Bool_2545 = 0;
    (void)hoisted__Bool_2545;
    Bool_delete(&self->does_throw, hoisted__Bool_2545);
    Bool hoisted__Bool_2546 = 0;
    (void)hoisted__Bool_2546;
    Bool_delete(&self->is_bang, hoisted__Bool_2546);
    Bool hoisted__Bool_2547 = 0;
    (void)hoisted__Bool_2547;
    U64_delete(&self->own_args, hoisted__Bool_2547);
    Bool hoisted__Bool_2548 = 0;
    (void)hoisted__Bool_2548;
    Bool_delete(&self->swap_replace, hoisted__Bool_2548);
    Bool hoisted__Bool_2549 = 0;
    (void)hoisted__Bool_2549;
    Type_delete(&self->til_type, hoisted__Bool_2549);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2550 = 0;
    (void)hoisted__U32_2550;
    U64 hoisted__U64_2551 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2550); });
    (void)hoisted__U64_2551;
    return hoisted__U64_2551;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2552 = 48;
    (void)hoisted__U32_2552;
    return hoisted__U32_2552;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2572 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2572->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2572->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2572;
    return hoisted__LiteralNumData_2572;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2573 = 0;
    (void)hoisted__Bool_2573;
    Str_delete(&self->text, hoisted__Bool_2573);
    Bool hoisted__Bool_2574 = 0;
    (void)hoisted__Bool_2574;
    Type_delete(&self->til_type, hoisted__Bool_2574);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2575 = 0;
    (void)hoisted__U32_2575;
    U64 hoisted__U64_2576 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2575); });
    (void)hoisted__U64_2576;
    return hoisted__U64_2576;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2577 = 40;
    (void)hoisted__U32_2577;
    return hoisted__U32_2577;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2593 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2593->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2593->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2593;
    return hoisted__IdentData_2593;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2594 = 0;
    (void)hoisted__Bool_2594;
    Str_delete(&self->name, hoisted__Bool_2594);
    Bool hoisted__Bool_2595 = 0;
    (void)hoisted__Bool_2595;
    Type_delete(&self->til_type, hoisted__Bool_2595);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2596 = 0;
    (void)hoisted__U32_2596;
    U64 hoisted__U64_2597 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2596); });
    (void)hoisted__U64_2597;
    return hoisted__U64_2597;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2598 = 40;
    (void)hoisted__U32_2598;
    return hoisted__U32_2598;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2610 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2610->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2610->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2610;
    return hoisted__FieldAccessData_2610;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2611 = 0;
    (void)hoisted__Bool_2611;
    Str_delete(&self->name, hoisted__Bool_2611);
    Bool hoisted__Bool_2612 = 0;
    (void)hoisted__Bool_2612;
    Type_delete(&self->til_type, hoisted__Bool_2612);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2613 = 0;
    (void)hoisted__U32_2613;
    U64 hoisted__U64_2614 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2613); });
    (void)hoisted__U64_2614;
    return hoisted__U64_2614;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2615 = 40;
    (void)hoisted__U32_2615;
    return hoisted__U32_2615;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2690 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2690->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2690->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2690->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2690->is_interface = self->is_interface;
    hoisted__StructDef_2690->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2690->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2690;
    return hoisted__StructDef_2690;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2691 = 0;
    (void)hoisted__Bool_2691;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2691);
    Bool hoisted__Bool_2692 = 0;
    (void)hoisted__Bool_2692;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2692);
    Bool hoisted__Bool_2693 = 0;
    (void)hoisted__Bool_2693;
    Str_delete(&self->c_tag, hoisted__Bool_2693);
    Bool hoisted__Bool_2694 = 0;
    (void)hoisted__Bool_2694;
    Bool_delete(&self->is_interface, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2695);
    Bool hoisted__Bool_2696 = 0;
    (void)hoisted__Bool_2696;
    Str_delete(&self->implements_name, hoisted__Bool_2696);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2697 = 0;
    (void)hoisted__U32_2697;
    U64 hoisted__U64_2698 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2697); });
    (void)hoisted__U64_2698;
    return hoisted__U64_2698;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2699 = 72;
    (void)hoisted__U32_2699;
    return hoisted__U32_2699;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2704 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2704->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2704->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2704->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2704->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2704->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2704;
    return hoisted__EnumDef_2704;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Vec__Str_delete(&self->variants, hoisted__Bool_2706);
    Bool hoisted__Bool_2707 = 0;
    (void)hoisted__Bool_2707;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2707);
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Str_delete(&self->implements_name, hoisted__Bool_2709);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2710 = 0;
    (void)hoisted__U32_2710;
    U64 hoisted__U64_2711 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2710); });
    (void)hoisted__U64_2711;
    return hoisted__U64_2711;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2712 = 96;
    (void)hoisted__U32_2712;
    return hoisted__U32_2712;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2808 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2808->name = *_ca; free(_ca); }
    hoisted__AssignData_2808->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2808->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2808->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2808;
    return hoisted__AssignData_2808;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2809 = 0;
    (void)hoisted__Bool_2809;
    Str_delete(&self->name, hoisted__Bool_2809);
    Bool hoisted__Bool_2810 = 0;
    (void)hoisted__Bool_2810;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2810);
    Bool hoisted__Bool_2811 = 0;
    (void)hoisted__Bool_2811;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2811);
    Bool hoisted__Bool_2812 = 0;
    (void)hoisted__Bool_2812;
    Bool_delete(&self->swap_replace, hoisted__Bool_2812);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2813 = 0;
    (void)hoisted__U32_2813;
    U64 hoisted__U64_2814 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2813); });
    (void)hoisted__U64_2814;
    return hoisted__U64_2814;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2815 = 24;
    (void)hoisted__U32_2815;
    return hoisted__U32_2815;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2817 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2817->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2817->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2817;
    return hoisted__FieldAssignData_2817;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2818 = 0;
    (void)hoisted__Bool_2818;
    Str_delete(&self->name, hoisted__Bool_2818);
    Bool hoisted__Bool_2819 = 0;
    (void)hoisted__Bool_2819;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2819);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2820 = 0;
    (void)hoisted__U32_2820;
    U64 hoisted__U64_2821 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2820); });
    (void)hoisted__U64_2821;
    return hoisted__U64_2821;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2822 = 24;
    (void)hoisted__U32_2822;
    return hoisted__U32_2822;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2824 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2824->name = *_ca; free(_ca); }
    hoisted__ForInData_2824->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2824->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2824;
    return hoisted__ForInData_2824;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2825 = 0;
    (void)hoisted__Bool_2825;
    Str_delete(&self->name, hoisted__Bool_2825);
    Bool hoisted__Bool_2826 = 0;
    (void)hoisted__Bool_2826;
    Bool_delete(&self->is_mut, hoisted__Bool_2826);
    Bool hoisted__Bool_2827 = 0;
    (void)hoisted__Bool_2827;
    Type_delete(&self->til_type, hoisted__Bool_2827);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2828 = 0;
    (void)hoisted__U32_2828;
    U64 hoisted__U64_2829 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2828); });
    (void)hoisted__U64_2829;
    return hoisted__U64_2829;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2830 = 48;
    (void)hoisted__U32_2830;
    return hoisted__U32_2830;
}

Literal *Literal_Str(Str * val) {
    Literal *r = malloc(sizeof(Literal));
    r->tag = Literal_TAG_Str;
    r->data.Str = *val;
    free(val);
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
    Bool hoisted__Bool_2860 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2860;
    if (hoisted__Bool_2860) {
        Str *hoisted__Str_2854 = get_payload(self);
        (void)hoisted__Str_2854;
        (void)hoisted__Str_2854;
        Bool hoisted__Bool_2855 = 0;
        (void)hoisted__Bool_2855;
        Str_delete(hoisted__Str_2854, hoisted__Bool_2855);
    }
    Bool hoisted__Bool_2861 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2861;
    if (hoisted__Bool_2861) {
        LiteralNumData *hoisted__LiteralNumData_2856 = get_payload(self);
        (void)hoisted__LiteralNumData_2856;
        (void)hoisted__LiteralNumData_2856;
        Bool hoisted__Bool_2857 = 0;
        (void)hoisted__Bool_2857;
        LiteralNumData_delete(hoisted__LiteralNumData_2856, hoisted__Bool_2857);
    }
    Bool hoisted__Bool_2862 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2862;
    if (hoisted__Bool_2862) {
        Bool *hoisted__Bool_2858 = get_payload(self);
        (void)hoisted__Bool_2858;
        (void)hoisted__Bool_2858;
        Bool hoisted__Bool_2859 = 0;
        (void)hoisted__Bool_2859;
        Bool_delete(hoisted__Bool_2858, hoisted__Bool_2859);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2902 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2902;
    if (hoisted__Bool_2902) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2897 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2897;
        Literal *hoisted__Literal_2898 = Literal_Str(hoisted__Str_2897);
        (void)hoisted__Literal_2898;
        { Literal * _ret_val = hoisted__Literal_2898;
                return _ret_val; }
    }
    Bool hoisted__Bool_2903 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2903;
    if (hoisted__Bool_2903) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2899 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2899;
        Literal *hoisted__Literal_2900 = Literal_Num(hoisted__LiteralNumData_2899);
        (void)hoisted__Literal_2900;
        { Literal * _ret_val = hoisted__Literal_2900;
                return _ret_val; }
    }
    Bool hoisted__Bool_2904 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2904;
    if (hoisted__Bool_2904) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2901 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2901;
        { Literal * _ret_val = hoisted__Literal_2901;
                return _ret_val; }
    }
    Bool hoisted__Bool_2905 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2905;
    if (hoisted__Bool_2905) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2906 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2906;
    if (hoisted__Bool_2906) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2907 = 48;
    (void)hoisted__U32_2907;
    return hoisted__U32_2907;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2910 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2910->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2910->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2910;
    return hoisted__MatchData_2910;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2911 = 0;
    (void)hoisted__Bool_2911;
    Type_delete(&self->til_type, hoisted__Bool_2911);
    Bool hoisted__Bool_2912 = 0;
    (void)hoisted__Bool_2912;
    Str_delete(&self->result_temp, hoisted__Bool_2912);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2913 = 0;
    (void)hoisted__U32_2913;
    U64 hoisted__U64_2914 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2913); });
    (void)hoisted__U64_2914;
    return hoisted__U64_2914;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2915 = 40;
    (void)hoisted__U32_2915;
    return hoisted__U32_2915;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2920 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2920->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2920;
    return hoisted__CaptureBlockData_2920;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2921 = 0;
    (void)hoisted__Bool_2921;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2921);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2922 = 0;
    (void)hoisted__U32_2922;
    U64 hoisted__U64_2923 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2922); });
    (void)hoisted__U64_2923;
    return hoisted__U64_2923;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2924 = 16;
    (void)hoisted__U32_2924;
    return hoisted__U32_2924;
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
    free(val);
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
    Bool hoisted__Bool_3103 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3103;
    if (hoisted__Bool_3103) {
        Literal *hoisted__Literal_3075 = get_payload(self);
        (void)hoisted__Literal_3075;
        (void)hoisted__Literal_3075;
        Bool hoisted__Bool_3076 = 0;
        (void)hoisted__Bool_3076;
        Literal_delete(hoisted__Literal_3075, hoisted__Bool_3076);
    }
    Bool hoisted__Bool_3104 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3104;
    if (hoisted__Bool_3104) {
        IdentData *hoisted__IdentData_3077 = get_payload(self);
        (void)hoisted__IdentData_3077;
        (void)hoisted__IdentData_3077;
        Bool hoisted__Bool_3078 = 0;
        (void)hoisted__Bool_3078;
        IdentData_delete(hoisted__IdentData_3077, hoisted__Bool_3078);
    }
    Bool hoisted__Bool_3105 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3105;
    if (hoisted__Bool_3105) {
        Declaration *hoisted__Declaration_3079 = get_payload(self);
        (void)hoisted__Declaration_3079;
        (void)hoisted__Declaration_3079;
        Bool hoisted__Bool_3080 = 0;
        (void)hoisted__Bool_3080;
        Declaration_delete(hoisted__Declaration_3079, hoisted__Bool_3080);
    }
    Bool hoisted__Bool_3106 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3106;
    if (hoisted__Bool_3106) {
        AssignData *hoisted__AssignData_3081 = get_payload(self);
        (void)hoisted__AssignData_3081;
        (void)hoisted__AssignData_3081;
        Bool hoisted__Bool_3082 = 0;
        (void)hoisted__Bool_3082;
        AssignData_delete(hoisted__AssignData_3081, hoisted__Bool_3082);
    }
    Bool hoisted__Bool_3107 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3107;
    if (hoisted__Bool_3107) {
        FCallData *hoisted__FCallData_3083 = get_payload(self);
        (void)hoisted__FCallData_3083;
        (void)hoisted__FCallData_3083;
        Bool hoisted__Bool_3084 = 0;
        (void)hoisted__Bool_3084;
        FCallData_delete(hoisted__FCallData_3083, hoisted__Bool_3084);
    }
    Bool hoisted__Bool_3108 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3108;
    if (hoisted__Bool_3108) {
        FunctionDef *hoisted__FunctionDef_3085 = get_payload(self);
        (void)hoisted__FunctionDef_3085;
        (void)hoisted__FunctionDef_3085;
        Bool hoisted__Bool_3086 = 0;
        (void)hoisted__Bool_3086;
        FunctionDef_delete(hoisted__FunctionDef_3085, hoisted__Bool_3086);
    }
    Bool hoisted__Bool_3109 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3109;
    if (hoisted__Bool_3109) {
        StructDef *hoisted__StructDef_3087 = get_payload(self);
        (void)hoisted__StructDef_3087;
        (void)hoisted__StructDef_3087;
        Bool hoisted__Bool_3088 = 0;
        (void)hoisted__Bool_3088;
        StructDef_delete(hoisted__StructDef_3087, hoisted__Bool_3088);
    }
    Bool hoisted__Bool_3110 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3110;
    if (hoisted__Bool_3110) {
        EnumDef *hoisted__EnumDef_3089 = get_payload(self);
        (void)hoisted__EnumDef_3089;
        (void)hoisted__EnumDef_3089;
        Bool hoisted__Bool_3090 = 0;
        (void)hoisted__Bool_3090;
        EnumDef_delete(hoisted__EnumDef_3089, hoisted__Bool_3090);
    }
    Bool hoisted__Bool_3111 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3111;
    if (hoisted__Bool_3111) {
        FieldAccessData *hoisted__FieldAccessData_3091 = get_payload(self);
        (void)hoisted__FieldAccessData_3091;
        (void)hoisted__FieldAccessData_3091;
        Bool hoisted__Bool_3092 = 0;
        (void)hoisted__Bool_3092;
        FieldAccessData_delete(hoisted__FieldAccessData_3091, hoisted__Bool_3092);
    }
    Bool hoisted__Bool_3112 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3112;
    if (hoisted__Bool_3112) {
        FieldAssignData *hoisted__FieldAssignData_3093 = get_payload(self);
        (void)hoisted__FieldAssignData_3093;
        (void)hoisted__FieldAssignData_3093;
        Bool hoisted__Bool_3094 = 0;
        (void)hoisted__Bool_3094;
        FieldAssignData_delete(hoisted__FieldAssignData_3093, hoisted__Bool_3094);
    }
    Bool hoisted__Bool_3113 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3113;
    if (hoisted__Bool_3113) {
        ForInData *hoisted__ForInData_3095 = get_payload(self);
        (void)hoisted__ForInData_3095;
        (void)hoisted__ForInData_3095;
        Bool hoisted__Bool_3096 = 0;
        (void)hoisted__Bool_3096;
        ForInData_delete(hoisted__ForInData_3095, hoisted__Bool_3096);
    }
    Bool hoisted__Bool_3114 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3114;
    if (hoisted__Bool_3114) {
        Str *hoisted__Str_3097 = get_payload(self);
        (void)hoisted__Str_3097;
        (void)hoisted__Str_3097;
        Bool hoisted__Bool_3098 = 0;
        (void)hoisted__Bool_3098;
        Str_delete(hoisted__Str_3097, hoisted__Bool_3098);
    }
    Bool hoisted__Bool_3115 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3115;
    if (hoisted__Bool_3115) {
        MatchData *hoisted__MatchData_3099 = get_payload(self);
        (void)hoisted__MatchData_3099;
        (void)hoisted__MatchData_3099;
        Bool hoisted__Bool_3100 = 0;
        (void)hoisted__Bool_3100;
        MatchData_delete(hoisted__MatchData_3099, hoisted__Bool_3100);
    }
    Bool hoisted__Bool_3116 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3116;
    if (hoisted__Bool_3116) {
        CaptureBlockData *hoisted__CaptureBlockData_3101 = get_payload(self);
        (void)hoisted__CaptureBlockData_3101;
        (void)hoisted__CaptureBlockData_3101;
        Bool hoisted__Bool_3102 = 0;
        (void)hoisted__Bool_3102;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3101, hoisted__Bool_3102);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3298 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3298;
    if (hoisted__Bool_3298) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3299 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3299;
    if (hoisted__Bool_3299) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3270 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3270;
        NodeType *hoisted__NodeType_3271 = NodeType_Literal(hoisted__Literal_3270);
        (void)hoisted__NodeType_3271;
        { NodeType * _ret_val = hoisted__NodeType_3271;
                return _ret_val; }
    }
    Bool hoisted__Bool_3300 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3300;
    if (hoisted__Bool_3300) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3272 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3272;
        NodeType *hoisted__NodeType_3273 = NodeType_Ident(hoisted__IdentData_3272);
        (void)hoisted__NodeType_3273;
        { NodeType * _ret_val = hoisted__NodeType_3273;
                return _ret_val; }
    }
    Bool hoisted__Bool_3301 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3301;
    if (hoisted__Bool_3301) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3274 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3274;
        NodeType *hoisted__NodeType_3275 = NodeType_Decl(hoisted__Declaration_3274);
        (void)hoisted__NodeType_3275;
        { NodeType * _ret_val = hoisted__NodeType_3275;
                return _ret_val; }
    }
    Bool hoisted__Bool_3302 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3302;
    if (hoisted__Bool_3302) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3276 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3276;
        NodeType *hoisted__NodeType_3277 = NodeType_Assign(hoisted__AssignData_3276);
        (void)hoisted__NodeType_3277;
        { NodeType * _ret_val = hoisted__NodeType_3277;
                return _ret_val; }
    }
    Bool hoisted__Bool_3303 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3303;
    if (hoisted__Bool_3303) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3278 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3278;
        NodeType *hoisted__NodeType_3279 = NodeType_FCall(hoisted__FCallData_3278);
        (void)hoisted__NodeType_3279;
        { NodeType * _ret_val = hoisted__NodeType_3279;
                return _ret_val; }
    }
    Bool hoisted__Bool_3304 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3304;
    if (hoisted__Bool_3304) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3280 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3280;
        NodeType *hoisted__NodeType_3281 = NodeType_FuncDef(hoisted__FunctionDef_3280);
        (void)hoisted__NodeType_3281;
        { NodeType * _ret_val = hoisted__NodeType_3281;
                return _ret_val; }
    }
    Bool hoisted__Bool_3305 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3305;
    if (hoisted__Bool_3305) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3282 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3282;
        NodeType *hoisted__NodeType_3283 = NodeType_StructDef(hoisted__StructDef_3282);
        (void)hoisted__NodeType_3283;
        { NodeType * _ret_val = hoisted__NodeType_3283;
                return _ret_val; }
    }
    Bool hoisted__Bool_3306 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3306;
    if (hoisted__Bool_3306) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3284 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3284;
        NodeType *hoisted__NodeType_3285 = NodeType_EnumDef(hoisted__EnumDef_3284);
        (void)hoisted__NodeType_3285;
        { NodeType * _ret_val = hoisted__NodeType_3285;
                return _ret_val; }
    }
    Bool hoisted__Bool_3307 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3307;
    if (hoisted__Bool_3307) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3286 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3286;
        NodeType *hoisted__NodeType_3287 = NodeType_FieldAccess(hoisted__FieldAccessData_3286);
        (void)hoisted__NodeType_3287;
        { NodeType * _ret_val = hoisted__NodeType_3287;
                return _ret_val; }
    }
    Bool hoisted__Bool_3308 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3308;
    if (hoisted__Bool_3308) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3288 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3288;
        NodeType *hoisted__NodeType_3289 = NodeType_FieldAssign(hoisted__FieldAssignData_3288);
        (void)hoisted__NodeType_3289;
        { NodeType * _ret_val = hoisted__NodeType_3289;
                return _ret_val; }
    }
    Bool hoisted__Bool_3309 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3309;
    if (hoisted__Bool_3309) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3310 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3310;
    if (hoisted__Bool_3310) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3311 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3311;
    if (hoisted__Bool_3311) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3312 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3312;
    if (hoisted__Bool_3312) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3290 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3290;
        NodeType *hoisted__NodeType_3291 = NodeType_ForIn(hoisted__ForInData_3290);
        (void)hoisted__NodeType_3291;
        { NodeType * _ret_val = hoisted__NodeType_3291;
                return _ret_val; }
    }
    Bool hoisted__Bool_3313 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3313;
    if (hoisted__Bool_3313) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3292 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3292;
        NodeType *hoisted__NodeType_3293 = NodeType_NamedArg(hoisted__Str_3292);
        (void)hoisted__NodeType_3293;
        { NodeType * _ret_val = hoisted__NodeType_3293;
                return _ret_val; }
    }
    Bool hoisted__Bool_3314 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3314;
    if (hoisted__Bool_3314) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3315 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3315;
    if (hoisted__Bool_3315) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3316 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3316;
    if (hoisted__Bool_3316) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3317 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3317;
    if (hoisted__Bool_3317) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3294 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3294;
        NodeType *hoisted__NodeType_3295 = NodeType_Match(hoisted__MatchData_3294);
        (void)hoisted__NodeType_3295;
        { NodeType * _ret_val = hoisted__NodeType_3295;
                return _ret_val; }
    }
    Bool hoisted__Bool_3318 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3318;
    if (hoisted__Bool_3318) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3319 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3319;
    if (hoisted__Bool_3319) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3320 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3320;
    if (hoisted__Bool_3320) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3321 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3321;
    if (hoisted__Bool_3321) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3322 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3322;
    if (hoisted__Bool_3322) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3323 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3323;
    if (hoisted__Bool_3323) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3296 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3296;
        NodeType *hoisted__NodeType_3297 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3296);
        (void)hoisted__NodeType_3297;
        { NodeType * _ret_val = hoisted__NodeType_3297;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3324 = 112;
    (void)hoisted__U32_3324;
    return hoisted__U32_3324;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3325 = is_null(self);
    (void)hoisted__Bool_3325;
    if (hoisted__Bool_3325) {
        return;
    }
    Bool hoisted__Bool_3326 = 0;
    (void)hoisted__Bool_3326;
    NodeType_delete(&self->node_type, hoisted__Bool_3326);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3370 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3370->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3370->children = *_ca; free(_ca); }
    hoisted__Expr_3370->line = line;
    hoisted__Expr_3370->col = col;
    (void)hoisted__Expr_3370;
    return hoisted__Expr_3370;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3378 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3378->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3378->children = *_ca; free(_ca); }
    hoisted__Expr_3378->line = self->line;
    hoisted__Expr_3378->col = self->col;
    (void)hoisted__Expr_3378;
    return hoisted__Expr_3378;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3379 = 0;
    (void)hoisted__U32_3379;
    U64 hoisted__U64_3380 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3379); });
    (void)hoisted__U64_3380;
    return hoisted__U64_3380;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3381 = 136;
    (void)hoisted__U32_3381;
    return hoisted__U32_3381;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4017 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4017->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4017->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4017;
    return hoisted__Map__I64_Str_4017;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4162 = 0;
    (void)hoisted__Bool_4162;
    Vec__I64_delete(&self->keys, hoisted__Bool_4162);
    Bool hoisted__Bool_4163 = 0;
    (void)hoisted__Bool_4163;
    Vec__Str_delete(&self->values, hoisted__Bool_4163);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4164 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4164->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4164->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4164;
    return hoisted__Map__I64_Str_4164;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4165 = 0;
    (void)hoisted__U32_4165;
    U64 hoisted__U64_4166 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4165); });
    (void)hoisted__U64_4166;
    return hoisted__U64_4166;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4167 = 32;
    (void)hoisted__U32_4167;
    return hoisted__U32_4167;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4168 = 1;
    (void)hoisted__U32_4168;
    Type *hoisted__Type_4169 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4169;
    U64 hoisted__U64_4170 = (U64)(hoisted__U32_4168);
    (void)hoisted__U64_4170;
    Type_delete(hoisted__Type_4169, 1);
    void * hoisted__v_4171 = malloc(hoisted__U64_4170);
    (void)hoisted__v_4171;
    U32 hoisted__U32_4172 = 0;
    (void)hoisted__U32_4172;
    I64 hoisted__I64_4173 = 1;
    (void)hoisted__I64_4173;
    Vec__Bool *hoisted__Vec__Bool_4174 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4174->data = hoisted__v_4171;
    hoisted__Vec__Bool_4174->count = hoisted__U32_4172;
    hoisted__Vec__Bool_4174->cap = hoisted__I64_4173;
    (void)hoisted__Vec__Bool_4174;
    return hoisted__Vec__Bool_4174;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4175 = self->count;
        (void)_re_U32_4175;
        U32 _rc_U32_4175 = 0;
        (void)_rc_U32_4175;
        Bool hoisted__Bool_4190 = U32_lte(_rc_U32_4175, _re_U32_4175);
        (void)hoisted__Bool_4190;
        if (hoisted__Bool_4190) {
            while (1) {
                Bool _wcond_Bool_4176 = U32_lt(_rc_U32_4175, _re_U32_4175);
                (void)_wcond_Bool_4176;
                if (_wcond_Bool_4176) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4175);
                U32_inc(&_rc_U32_4175);
                U32 hoisted__U32_4177 = 1;
                (void)hoisted__U32_4177;
                U32 hoisted__U32_4178 = U32_mul(i, hoisted__U32_4177);
                (void)hoisted__U32_4178;
                Type *hoisted__Type_4179 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4179;
                U64 hoisted__U64_4180 = (U64)(hoisted__U32_4178);
                (void)hoisted__U64_4180;
                Type_delete(hoisted__Type_4179, 1);
                Bool *hoisted__Bool_4181 = ptr_add(self->data, hoisted__U64_4180);
                (void)hoisted__Bool_4181;
                (void)hoisted__Bool_4181;
                Bool hoisted__Bool_4182 = 0;
                (void)hoisted__Bool_4182;
                Bool_delete(hoisted__Bool_4181, hoisted__Bool_4182);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4183 = U32_gt(_rc_U32_4175, _re_U32_4175);
                (void)_wcond_Bool_4183;
                if (_wcond_Bool_4183) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4175);
                U32_dec(&_rc_U32_4175);
                U32 hoisted__U32_4184 = 1;
                (void)hoisted__U32_4184;
                U32 hoisted__U32_4185 = U32_mul(i, hoisted__U32_4184);
                (void)hoisted__U32_4185;
                Type *hoisted__Type_4186 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4186;
                U64 hoisted__U64_4187 = (U64)(hoisted__U32_4185);
                (void)hoisted__U64_4187;
                Type_delete(hoisted__Type_4186, 1);
                Bool *hoisted__Bool_4188 = ptr_add(self->data, hoisted__U64_4187);
                (void)hoisted__Bool_4188;
                (void)hoisted__Bool_4188;
                Bool hoisted__Bool_4189 = 0;
                (void)hoisted__Bool_4189;
                Bool_delete(hoisted__Bool_4188, hoisted__Bool_4189);
            }
        }
    }
    U32 hoisted__U32_4191 = 0;
    (void)hoisted__U32_4191;
    self->count = hoisted__U32_4191;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4484 = 1;
    (void)hoisted__U32_4484;
    U32 hoisted__U32_4485 = U32_mul(self->cap, hoisted__U32_4484);
    (void)hoisted__U32_4485;
    Type *hoisted__Type_4486 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4486;
    U64 hoisted__U64_4487 = (U64)(hoisted__U32_4485);
    (void)hoisted__U64_4487;
    Type_delete(hoisted__Type_4486, 1);
    void * new_data = malloc(hoisted__U64_4487);
    {
        U32 _re_U32_4448 = self->count;
        (void)_re_U32_4448;
        U32 _rc_U32_4448 = 0;
        (void)_rc_U32_4448;
        Bool hoisted__Bool_4483 = U32_lte(_rc_U32_4448, _re_U32_4448);
        (void)hoisted__Bool_4483;
        if (hoisted__Bool_4483) {
            while (1) {
                Bool _wcond_Bool_4449 = U32_lt(_rc_U32_4448, _re_U32_4448);
                (void)_wcond_Bool_4449;
                if (_wcond_Bool_4449) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4448);
                U32_inc(&_rc_U32_4448);
                U32 hoisted__U32_4450 = 1;
                (void)hoisted__U32_4450;
                U32 hoisted__U32_4451 = U32_mul(i, hoisted__U32_4450);
                (void)hoisted__U32_4451;
                Type *hoisted__Type_4452 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4452;
                U64 hoisted__U64_4453 = (U64)(hoisted__U32_4451);
                (void)hoisted__U64_4453;
                Type_delete(hoisted__Type_4452, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4453);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4454 = 1;
                (void)hoisted__U32_4454;
                U32 hoisted__U32_4455 = U32_mul(i, hoisted__U32_4454);
                (void)hoisted__U32_4455;
                Type *hoisted__Type_4456 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4456;
                U64 hoisted__U64_4457 = (U64)(hoisted__U32_4455);
                (void)hoisted__U64_4457;
                Type_delete(hoisted__Type_4456, 1);
                U32 hoisted__U32_4458 = 1;
                (void)hoisted__U32_4458;
                Type *hoisted__Type_4459 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4459;
                void *hoisted__v_4460 = ptr_add(new_data, hoisted__U64_4457);
                (void)hoisted__v_4460;
                (void)hoisted__v_4460;
                U64 hoisted__U64_4461 = (U64)(hoisted__U32_4458);
                (void)hoisted__U64_4461;
                Type_delete(hoisted__Type_4459, 1);
                memcpy(hoisted__v_4460, &cloned, hoisted__U64_4461);
                U32 hoisted__U32_4462 = 1;
                (void)hoisted__U32_4462;
                Type *hoisted__Type_4463 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4463;
                I32 hoisted__I32_4464 = 0;
                (void)hoisted__I32_4464;
                U64 hoisted__U64_4465 = (U64)(hoisted__U32_4462);
                (void)hoisted__U64_4465;
                Type_delete(hoisted__Type_4463, 1);
                memset(&cloned, hoisted__I32_4464, hoisted__U64_4465);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4466 = U32_gt(_rc_U32_4448, _re_U32_4448);
                (void)_wcond_Bool_4466;
                if (_wcond_Bool_4466) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4448);
                U32_dec(&_rc_U32_4448);
                U32 hoisted__U32_4467 = 1;
                (void)hoisted__U32_4467;
                U32 hoisted__U32_4468 = U32_mul(i, hoisted__U32_4467);
                (void)hoisted__U32_4468;
                Type *hoisted__Type_4469 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4469;
                U64 hoisted__U64_4470 = (U64)(hoisted__U32_4468);
                (void)hoisted__U64_4470;
                Type_delete(hoisted__Type_4469, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4470);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4471 = 1;
                (void)hoisted__U32_4471;
                U32 hoisted__U32_4472 = U32_mul(i, hoisted__U32_4471);
                (void)hoisted__U32_4472;
                Type *hoisted__Type_4473 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4473;
                U64 hoisted__U64_4474 = (U64)(hoisted__U32_4472);
                (void)hoisted__U64_4474;
                Type_delete(hoisted__Type_4473, 1);
                U32 hoisted__U32_4475 = 1;
                (void)hoisted__U32_4475;
                Type *hoisted__Type_4476 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4476;
                void *hoisted__v_4477 = ptr_add(new_data, hoisted__U64_4474);
                (void)hoisted__v_4477;
                (void)hoisted__v_4477;
                U64 hoisted__U64_4478 = (U64)(hoisted__U32_4475);
                (void)hoisted__U64_4478;
                Type_delete(hoisted__Type_4476, 1);
                memcpy(hoisted__v_4477, &cloned, hoisted__U64_4478);
                U32 hoisted__U32_4479 = 1;
                (void)hoisted__U32_4479;
                Type *hoisted__Type_4480 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4480;
                I32 hoisted__I32_4481 = 0;
                (void)hoisted__I32_4481;
                U64 hoisted__U64_4482 = (U64)(hoisted__U32_4479);
                (void)hoisted__U64_4482;
                Type_delete(hoisted__Type_4480, 1);
                memset(&cloned, hoisted__I32_4481, hoisted__U64_4482);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4488 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4488->data = new_data;
    hoisted__Vec__Bool_4488->count = self->count;
    hoisted__Vec__Bool_4488->cap = self->cap;
    (void)hoisted__Vec__Bool_4488;
    return hoisted__Vec__Bool_4488;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4489 = 16;
    (void)hoisted__U32_4489;
    return hoisted__U32_4489;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_4812 = 104;
    (void)hoisted__U32_4812;
    Type *hoisted__Type_4813 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4813;
    U64 hoisted__U64_4814 = (U64)(hoisted__U32_4812);
    (void)hoisted__U64_4814;
    Type_delete(hoisted__Type_4813, 1);
    void * hoisted__v_4815 = malloc(hoisted__U64_4814);
    (void)hoisted__v_4815;
    U32 hoisted__U32_4816 = 0;
    (void)hoisted__U32_4816;
    I64 hoisted__I64_4817 = 1;
    (void)hoisted__I64_4817;
    Vec__Declaration *hoisted__Vec__Declaration_4818 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4818->data = hoisted__v_4815;
    hoisted__Vec__Declaration_4818->count = hoisted__U32_4816;
    hoisted__Vec__Declaration_4818->cap = hoisted__I64_4817;
    (void)hoisted__Vec__Declaration_4818;
    return hoisted__Vec__Declaration_4818;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4819 = self->count;
        (void)_re_U32_4819;
        U32 _rc_U32_4819 = 0;
        (void)_rc_U32_4819;
        Bool hoisted__Bool_4834 = U32_lte(_rc_U32_4819, _re_U32_4819);
        (void)hoisted__Bool_4834;
        if (hoisted__Bool_4834) {
            while (1) {
                Bool _wcond_Bool_4820 = U32_lt(_rc_U32_4819, _re_U32_4819);
                (void)_wcond_Bool_4820;
                if (_wcond_Bool_4820) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4819);
                U32_inc(&_rc_U32_4819);
                U32 hoisted__U32_4821 = 104;
                (void)hoisted__U32_4821;
                U32 hoisted__U32_4822 = U32_mul(i, hoisted__U32_4821);
                (void)hoisted__U32_4822;
                Type *hoisted__Type_4823 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4823;
                U64 hoisted__U64_4824 = (U64)(hoisted__U32_4822);
                (void)hoisted__U64_4824;
                Type_delete(hoisted__Type_4823, 1);
                Declaration *hoisted__Declaration_4825 = ptr_add(self->data, hoisted__U64_4824);
                (void)hoisted__Declaration_4825;
                (void)hoisted__Declaration_4825;
                Bool hoisted__Bool_4826 = 0;
                (void)hoisted__Bool_4826;
                Declaration_delete(hoisted__Declaration_4825, hoisted__Bool_4826);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4827 = U32_gt(_rc_U32_4819, _re_U32_4819);
                (void)_wcond_Bool_4827;
                if (_wcond_Bool_4827) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4819);
                U32_dec(&_rc_U32_4819);
                U32 hoisted__U32_4828 = 104;
                (void)hoisted__U32_4828;
                U32 hoisted__U32_4829 = U32_mul(i, hoisted__U32_4828);
                (void)hoisted__U32_4829;
                Type *hoisted__Type_4830 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4830;
                U64 hoisted__U64_4831 = (U64)(hoisted__U32_4829);
                (void)hoisted__U64_4831;
                Type_delete(hoisted__Type_4830, 1);
                Declaration *hoisted__Declaration_4832 = ptr_add(self->data, hoisted__U64_4831);
                (void)hoisted__Declaration_4832;
                (void)hoisted__Declaration_4832;
                Bool hoisted__Bool_4833 = 0;
                (void)hoisted__Bool_4833;
                Declaration_delete(hoisted__Declaration_4832, hoisted__Bool_4833);
            }
        }
    }
    U32 hoisted__U32_4835 = 0;
    (void)hoisted__U32_4835;
    self->count = hoisted__U32_4835;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5128 = 104;
    (void)hoisted__U32_5128;
    U32 hoisted__U32_5129 = U32_mul(self->cap, hoisted__U32_5128);
    (void)hoisted__U32_5129;
    Type *hoisted__Type_5130 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5130;
    U64 hoisted__U64_5131 = (U64)(hoisted__U32_5129);
    (void)hoisted__U64_5131;
    Type_delete(hoisted__Type_5130, 1);
    void * new_data = malloc(hoisted__U64_5131);
    {
        U32 _re_U32_5092 = self->count;
        (void)_re_U32_5092;
        U32 _rc_U32_5092 = 0;
        (void)_rc_U32_5092;
        Bool hoisted__Bool_5127 = U32_lte(_rc_U32_5092, _re_U32_5092);
        (void)hoisted__Bool_5127;
        if (hoisted__Bool_5127) {
            while (1) {
                Bool _wcond_Bool_5093 = U32_lt(_rc_U32_5092, _re_U32_5092);
                (void)_wcond_Bool_5093;
                if (_wcond_Bool_5093) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5092);
                U32_inc(&_rc_U32_5092);
                U32 hoisted__U32_5094 = 104;
                (void)hoisted__U32_5094;
                U32 hoisted__U32_5095 = U32_mul(i, hoisted__U32_5094);
                (void)hoisted__U32_5095;
                Type *hoisted__Type_5096 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5096;
                U64 hoisted__U64_5097 = (U64)(hoisted__U32_5095);
                (void)hoisted__U64_5097;
                Type_delete(hoisted__Type_5096, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5097);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5098 = 104;
                (void)hoisted__U32_5098;
                U32 hoisted__U32_5099 = U32_mul(i, hoisted__U32_5098);
                (void)hoisted__U32_5099;
                Type *hoisted__Type_5100 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5100;
                U64 hoisted__U64_5101 = (U64)(hoisted__U32_5099);
                (void)hoisted__U64_5101;
                Type_delete(hoisted__Type_5100, 1);
                U32 hoisted__U32_5102 = 104;
                (void)hoisted__U32_5102;
                Type *hoisted__Type_5103 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5103;
                void *hoisted__v_5104 = ptr_add(new_data, hoisted__U64_5101);
                (void)hoisted__v_5104;
                (void)hoisted__v_5104;
                U64 hoisted__U64_5105 = (U64)(hoisted__U32_5102);
                (void)hoisted__U64_5105;
                Type_delete(hoisted__Type_5103, 1);
                memcpy(hoisted__v_5104, cloned, hoisted__U64_5105);
                U32 hoisted__U32_5106 = 104;
                (void)hoisted__U32_5106;
                Type *hoisted__Type_5107 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5107;
                I32 hoisted__I32_5108 = 0;
                (void)hoisted__I32_5108;
                U64 hoisted__U64_5109 = (U64)(hoisted__U32_5106);
                (void)hoisted__U64_5109;
                Type_delete(hoisted__Type_5107, 1);
                memset(cloned, hoisted__I32_5108, hoisted__U64_5109);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5110 = U32_gt(_rc_U32_5092, _re_U32_5092);
                (void)_wcond_Bool_5110;
                if (_wcond_Bool_5110) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5092);
                U32_dec(&_rc_U32_5092);
                U32 hoisted__U32_5111 = 104;
                (void)hoisted__U32_5111;
                U32 hoisted__U32_5112 = U32_mul(i, hoisted__U32_5111);
                (void)hoisted__U32_5112;
                Type *hoisted__Type_5113 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5113;
                U64 hoisted__U64_5114 = (U64)(hoisted__U32_5112);
                (void)hoisted__U64_5114;
                Type_delete(hoisted__Type_5113, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5114);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5115 = 104;
                (void)hoisted__U32_5115;
                U32 hoisted__U32_5116 = U32_mul(i, hoisted__U32_5115);
                (void)hoisted__U32_5116;
                Type *hoisted__Type_5117 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5117;
                U64 hoisted__U64_5118 = (U64)(hoisted__U32_5116);
                (void)hoisted__U64_5118;
                Type_delete(hoisted__Type_5117, 1);
                U32 hoisted__U32_5119 = 104;
                (void)hoisted__U32_5119;
                Type *hoisted__Type_5120 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5120;
                void *hoisted__v_5121 = ptr_add(new_data, hoisted__U64_5118);
                (void)hoisted__v_5121;
                (void)hoisted__v_5121;
                U64 hoisted__U64_5122 = (U64)(hoisted__U32_5119);
                (void)hoisted__U64_5122;
                Type_delete(hoisted__Type_5120, 1);
                memcpy(hoisted__v_5121, cloned, hoisted__U64_5122);
                U32 hoisted__U32_5123 = 104;
                (void)hoisted__U32_5123;
                Type *hoisted__Type_5124 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5124;
                I32 hoisted__I32_5125 = 0;
                (void)hoisted__I32_5125;
                U64 hoisted__U64_5126 = (U64)(hoisted__U32_5123);
                (void)hoisted__U64_5126;
                Type_delete(hoisted__Type_5124, 1);
                memset(cloned, hoisted__I32_5125, hoisted__U64_5126);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5132 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5132->data = new_data;
    hoisted__Vec__Declaration_5132->count = self->count;
    hoisted__Vec__Declaration_5132->cap = self->cap;
    (void)hoisted__Vec__Declaration_5132;
    return hoisted__Vec__Declaration_5132;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5133 = 16;
    (void)hoisted__U32_5133;
    return hoisted__U32_5133;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5134 = 136;
    (void)hoisted__U32_5134;
    Type *hoisted__Type_5135 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5135;
    U64 hoisted__U64_5136 = (U64)(hoisted__U32_5134);
    (void)hoisted__U64_5136;
    Type_delete(hoisted__Type_5135, 1);
    void * hoisted__v_5137 = malloc(hoisted__U64_5136);
    (void)hoisted__v_5137;
    U32 hoisted__U32_5138 = 0;
    (void)hoisted__U32_5138;
    I64 hoisted__I64_5139 = 1;
    (void)hoisted__I64_5139;
    Vec__Expr *hoisted__Vec__Expr_5140 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5140->data = hoisted__v_5137;
    hoisted__Vec__Expr_5140->count = hoisted__U32_5138;
    hoisted__Vec__Expr_5140->cap = hoisted__I64_5139;
    (void)hoisted__Vec__Expr_5140;
    return hoisted__Vec__Expr_5140;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5141 = self->count;
        (void)_re_U32_5141;
        U32 _rc_U32_5141 = 0;
        (void)_rc_U32_5141;
        Bool hoisted__Bool_5156 = U32_lte(_rc_U32_5141, _re_U32_5141);
        (void)hoisted__Bool_5156;
        if (hoisted__Bool_5156) {
            while (1) {
                Bool _wcond_Bool_5142 = U32_lt(_rc_U32_5141, _re_U32_5141);
                (void)_wcond_Bool_5142;
                if (_wcond_Bool_5142) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5141);
                U32_inc(&_rc_U32_5141);
                U32 hoisted__U32_5143 = 136;
                (void)hoisted__U32_5143;
                U32 hoisted__U32_5144 = U32_mul(i, hoisted__U32_5143);
                (void)hoisted__U32_5144;
                Type *hoisted__Type_5145 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5145;
                U64 hoisted__U64_5146 = (U64)(hoisted__U32_5144);
                (void)hoisted__U64_5146;
                Type_delete(hoisted__Type_5145, 1);
                Expr *hoisted__Expr_5147 = ptr_add(self->data, hoisted__U64_5146);
                (void)hoisted__Expr_5147;
                (void)hoisted__Expr_5147;
                Bool hoisted__Bool_5148 = 0;
                (void)hoisted__Bool_5148;
                Expr_delete(hoisted__Expr_5147, hoisted__Bool_5148);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5149 = U32_gt(_rc_U32_5141, _re_U32_5141);
                (void)_wcond_Bool_5149;
                if (_wcond_Bool_5149) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5141);
                U32_dec(&_rc_U32_5141);
                U32 hoisted__U32_5150 = 136;
                (void)hoisted__U32_5150;
                U32 hoisted__U32_5151 = U32_mul(i, hoisted__U32_5150);
                (void)hoisted__U32_5151;
                Type *hoisted__Type_5152 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5152;
                U64 hoisted__U64_5153 = (U64)(hoisted__U32_5151);
                (void)hoisted__U64_5153;
                Type_delete(hoisted__Type_5152, 1);
                Expr *hoisted__Expr_5154 = ptr_add(self->data, hoisted__U64_5153);
                (void)hoisted__Expr_5154;
                (void)hoisted__Expr_5154;
                Bool hoisted__Bool_5155 = 0;
                (void)hoisted__Bool_5155;
                Expr_delete(hoisted__Expr_5154, hoisted__Bool_5155);
            }
        }
    }
    U32 hoisted__U32_5157 = 0;
    (void)hoisted__U32_5157;
    self->count = hoisted__U32_5157;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5450 = 136;
    (void)hoisted__U32_5450;
    U32 hoisted__U32_5451 = U32_mul(self->cap, hoisted__U32_5450);
    (void)hoisted__U32_5451;
    Type *hoisted__Type_5452 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5452;
    U64 hoisted__U64_5453 = (U64)(hoisted__U32_5451);
    (void)hoisted__U64_5453;
    Type_delete(hoisted__Type_5452, 1);
    void * new_data = malloc(hoisted__U64_5453);
    {
        U32 _re_U32_5414 = self->count;
        (void)_re_U32_5414;
        U32 _rc_U32_5414 = 0;
        (void)_rc_U32_5414;
        Bool hoisted__Bool_5449 = U32_lte(_rc_U32_5414, _re_U32_5414);
        (void)hoisted__Bool_5449;
        if (hoisted__Bool_5449) {
            while (1) {
                Bool _wcond_Bool_5415 = U32_lt(_rc_U32_5414, _re_U32_5414);
                (void)_wcond_Bool_5415;
                if (_wcond_Bool_5415) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5414);
                U32_inc(&_rc_U32_5414);
                U32 hoisted__U32_5416 = 136;
                (void)hoisted__U32_5416;
                U32 hoisted__U32_5417 = U32_mul(i, hoisted__U32_5416);
                (void)hoisted__U32_5417;
                Type *hoisted__Type_5418 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5418;
                U64 hoisted__U64_5419 = (U64)(hoisted__U32_5417);
                (void)hoisted__U64_5419;
                Type_delete(hoisted__Type_5418, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5419);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5420 = 136;
                (void)hoisted__U32_5420;
                U32 hoisted__U32_5421 = U32_mul(i, hoisted__U32_5420);
                (void)hoisted__U32_5421;
                Type *hoisted__Type_5422 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5422;
                U64 hoisted__U64_5423 = (U64)(hoisted__U32_5421);
                (void)hoisted__U64_5423;
                Type_delete(hoisted__Type_5422, 1);
                U32 hoisted__U32_5424 = 136;
                (void)hoisted__U32_5424;
                Type *hoisted__Type_5425 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5425;
                void *hoisted__v_5426 = ptr_add(new_data, hoisted__U64_5423);
                (void)hoisted__v_5426;
                (void)hoisted__v_5426;
                U64 hoisted__U64_5427 = (U64)(hoisted__U32_5424);
                (void)hoisted__U64_5427;
                Type_delete(hoisted__Type_5425, 1);
                memcpy(hoisted__v_5426, cloned, hoisted__U64_5427);
                U32 hoisted__U32_5428 = 136;
                (void)hoisted__U32_5428;
                Type *hoisted__Type_5429 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5429;
                I32 hoisted__I32_5430 = 0;
                (void)hoisted__I32_5430;
                U64 hoisted__U64_5431 = (U64)(hoisted__U32_5428);
                (void)hoisted__U64_5431;
                Type_delete(hoisted__Type_5429, 1);
                memset(cloned, hoisted__I32_5430, hoisted__U64_5431);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5432 = U32_gt(_rc_U32_5414, _re_U32_5414);
                (void)_wcond_Bool_5432;
                if (_wcond_Bool_5432) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5414);
                U32_dec(&_rc_U32_5414);
                U32 hoisted__U32_5433 = 136;
                (void)hoisted__U32_5433;
                U32 hoisted__U32_5434 = U32_mul(i, hoisted__U32_5433);
                (void)hoisted__U32_5434;
                Type *hoisted__Type_5435 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5435;
                U64 hoisted__U64_5436 = (U64)(hoisted__U32_5434);
                (void)hoisted__U64_5436;
                Type_delete(hoisted__Type_5435, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5436);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5437 = 136;
                (void)hoisted__U32_5437;
                U32 hoisted__U32_5438 = U32_mul(i, hoisted__U32_5437);
                (void)hoisted__U32_5438;
                Type *hoisted__Type_5439 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5439;
                U64 hoisted__U64_5440 = (U64)(hoisted__U32_5438);
                (void)hoisted__U64_5440;
                Type_delete(hoisted__Type_5439, 1);
                U32 hoisted__U32_5441 = 136;
                (void)hoisted__U32_5441;
                Type *hoisted__Type_5442 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5442;
                void *hoisted__v_5443 = ptr_add(new_data, hoisted__U64_5440);
                (void)hoisted__v_5443;
                (void)hoisted__v_5443;
                U64 hoisted__U64_5444 = (U64)(hoisted__U32_5441);
                (void)hoisted__U64_5444;
                Type_delete(hoisted__Type_5442, 1);
                memcpy(hoisted__v_5443, cloned, hoisted__U64_5444);
                U32 hoisted__U32_5445 = 136;
                (void)hoisted__U32_5445;
                Type *hoisted__Type_5446 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5446;
                I32 hoisted__I32_5447 = 0;
                (void)hoisted__I32_5447;
                U64 hoisted__U64_5448 = (U64)(hoisted__U32_5445);
                (void)hoisted__U64_5448;
                Type_delete(hoisted__Type_5446, 1);
                memset(cloned, hoisted__I32_5447, hoisted__U64_5448);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5454 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5454->data = new_data;
    hoisted__Vec__Expr_5454->count = self->count;
    hoisted__Vec__Expr_5454->cap = self->cap;
    (void)hoisted__Vec__Expr_5454;
    return hoisted__Vec__Expr_5454;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5455 = 16;
    (void)hoisted__U32_5455;
    return hoisted__U32_5455;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5456 = 8;
    (void)hoisted__U32_5456;
    Type *hoisted__Type_5457 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5457;
    U64 hoisted__U64_5458 = (U64)(hoisted__U32_5456);
    (void)hoisted__U64_5458;
    Type_delete(hoisted__Type_5457, 1);
    void * hoisted__v_5459 = malloc(hoisted__U64_5458);
    (void)hoisted__v_5459;
    U32 hoisted__U32_5460 = 0;
    (void)hoisted__U32_5460;
    I64 hoisted__I64_5461 = 1;
    (void)hoisted__I64_5461;
    Vec__I64 *hoisted__Vec__I64_5462 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5462->data = hoisted__v_5459;
    hoisted__Vec__I64_5462->count = hoisted__U32_5460;
    hoisted__Vec__I64_5462->cap = hoisted__I64_5461;
    (void)hoisted__Vec__I64_5462;
    return hoisted__Vec__I64_5462;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5463 = self->count;
        (void)_re_U32_5463;
        U32 _rc_U32_5463 = 0;
        (void)_rc_U32_5463;
        Bool hoisted__Bool_5478 = U32_lte(_rc_U32_5463, _re_U32_5463);
        (void)hoisted__Bool_5478;
        if (hoisted__Bool_5478) {
            while (1) {
                Bool _wcond_Bool_5464 = U32_lt(_rc_U32_5463, _re_U32_5463);
                (void)_wcond_Bool_5464;
                if (_wcond_Bool_5464) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5463);
                U32_inc(&_rc_U32_5463);
                U32 hoisted__U32_5465 = 8;
                (void)hoisted__U32_5465;
                U32 hoisted__U32_5466 = U32_mul(i, hoisted__U32_5465);
                (void)hoisted__U32_5466;
                Type *hoisted__Type_5467 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5467;
                U64 hoisted__U64_5468 = (U64)(hoisted__U32_5466);
                (void)hoisted__U64_5468;
                Type_delete(hoisted__Type_5467, 1);
                I64 *hoisted__I64_5469 = ptr_add(self->data, hoisted__U64_5468);
                (void)hoisted__I64_5469;
                (void)hoisted__I64_5469;
                Bool hoisted__Bool_5470 = 0;
                (void)hoisted__Bool_5470;
                I64_delete(hoisted__I64_5469, hoisted__Bool_5470);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5471 = U32_gt(_rc_U32_5463, _re_U32_5463);
                (void)_wcond_Bool_5471;
                if (_wcond_Bool_5471) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5463);
                U32_dec(&_rc_U32_5463);
                U32 hoisted__U32_5472 = 8;
                (void)hoisted__U32_5472;
                U32 hoisted__U32_5473 = U32_mul(i, hoisted__U32_5472);
                (void)hoisted__U32_5473;
                Type *hoisted__Type_5474 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5474;
                U64 hoisted__U64_5475 = (U64)(hoisted__U32_5473);
                (void)hoisted__U64_5475;
                Type_delete(hoisted__Type_5474, 1);
                I64 *hoisted__I64_5476 = ptr_add(self->data, hoisted__U64_5475);
                (void)hoisted__I64_5476;
                (void)hoisted__I64_5476;
                Bool hoisted__Bool_5477 = 0;
                (void)hoisted__Bool_5477;
                I64_delete(hoisted__I64_5476, hoisted__Bool_5477);
            }
        }
    }
    U32 hoisted__U32_5479 = 0;
    (void)hoisted__U32_5479;
    self->count = hoisted__U32_5479;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5772 = 8;
    (void)hoisted__U32_5772;
    U32 hoisted__U32_5773 = U32_mul(self->cap, hoisted__U32_5772);
    (void)hoisted__U32_5773;
    Type *hoisted__Type_5774 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5774;
    U64 hoisted__U64_5775 = (U64)(hoisted__U32_5773);
    (void)hoisted__U64_5775;
    Type_delete(hoisted__Type_5774, 1);
    void * new_data = malloc(hoisted__U64_5775);
    {
        U32 _re_U32_5736 = self->count;
        (void)_re_U32_5736;
        U32 _rc_U32_5736 = 0;
        (void)_rc_U32_5736;
        Bool hoisted__Bool_5771 = U32_lte(_rc_U32_5736, _re_U32_5736);
        (void)hoisted__Bool_5771;
        if (hoisted__Bool_5771) {
            while (1) {
                Bool _wcond_Bool_5737 = U32_lt(_rc_U32_5736, _re_U32_5736);
                (void)_wcond_Bool_5737;
                if (_wcond_Bool_5737) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5736);
                U32_inc(&_rc_U32_5736);
                U32 hoisted__U32_5738 = 8;
                (void)hoisted__U32_5738;
                U32 hoisted__U32_5739 = U32_mul(i, hoisted__U32_5738);
                (void)hoisted__U32_5739;
                Type *hoisted__Type_5740 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5740;
                U64 hoisted__U64_5741 = (U64)(hoisted__U32_5739);
                (void)hoisted__U64_5741;
                Type_delete(hoisted__Type_5740, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5741);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5742 = 8;
                (void)hoisted__U32_5742;
                U32 hoisted__U32_5743 = U32_mul(i, hoisted__U32_5742);
                (void)hoisted__U32_5743;
                Type *hoisted__Type_5744 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5744;
                U64 hoisted__U64_5745 = (U64)(hoisted__U32_5743);
                (void)hoisted__U64_5745;
                Type_delete(hoisted__Type_5744, 1);
                U32 hoisted__U32_5746 = 8;
                (void)hoisted__U32_5746;
                Type *hoisted__Type_5747 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5747;
                void *hoisted__v_5748 = ptr_add(new_data, hoisted__U64_5745);
                (void)hoisted__v_5748;
                (void)hoisted__v_5748;
                U64 hoisted__U64_5749 = (U64)(hoisted__U32_5746);
                (void)hoisted__U64_5749;
                Type_delete(hoisted__Type_5747, 1);
                memcpy(hoisted__v_5748, &cloned, hoisted__U64_5749);
                U32 hoisted__U32_5750 = 8;
                (void)hoisted__U32_5750;
                Type *hoisted__Type_5751 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5751;
                I32 hoisted__I32_5752 = 0;
                (void)hoisted__I32_5752;
                U64 hoisted__U64_5753 = (U64)(hoisted__U32_5750);
                (void)hoisted__U64_5753;
                Type_delete(hoisted__Type_5751, 1);
                memset(&cloned, hoisted__I32_5752, hoisted__U64_5753);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5754 = U32_gt(_rc_U32_5736, _re_U32_5736);
                (void)_wcond_Bool_5754;
                if (_wcond_Bool_5754) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5736);
                U32_dec(&_rc_U32_5736);
                U32 hoisted__U32_5755 = 8;
                (void)hoisted__U32_5755;
                U32 hoisted__U32_5756 = U32_mul(i, hoisted__U32_5755);
                (void)hoisted__U32_5756;
                Type *hoisted__Type_5757 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5757;
                U64 hoisted__U64_5758 = (U64)(hoisted__U32_5756);
                (void)hoisted__U64_5758;
                Type_delete(hoisted__Type_5757, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5758);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5759 = 8;
                (void)hoisted__U32_5759;
                U32 hoisted__U32_5760 = U32_mul(i, hoisted__U32_5759);
                (void)hoisted__U32_5760;
                Type *hoisted__Type_5761 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5761;
                U64 hoisted__U64_5762 = (U64)(hoisted__U32_5760);
                (void)hoisted__U64_5762;
                Type_delete(hoisted__Type_5761, 1);
                U32 hoisted__U32_5763 = 8;
                (void)hoisted__U32_5763;
                Type *hoisted__Type_5764 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5764;
                void *hoisted__v_5765 = ptr_add(new_data, hoisted__U64_5762);
                (void)hoisted__v_5765;
                (void)hoisted__v_5765;
                U64 hoisted__U64_5766 = (U64)(hoisted__U32_5763);
                (void)hoisted__U64_5766;
                Type_delete(hoisted__Type_5764, 1);
                memcpy(hoisted__v_5765, &cloned, hoisted__U64_5766);
                U32 hoisted__U32_5767 = 8;
                (void)hoisted__U32_5767;
                Type *hoisted__Type_5768 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5768;
                I32 hoisted__I32_5769 = 0;
                (void)hoisted__I32_5769;
                U64 hoisted__U64_5770 = (U64)(hoisted__U32_5767);
                (void)hoisted__U64_5770;
                Type_delete(hoisted__Type_5768, 1);
                memset(&cloned, hoisted__I32_5769, hoisted__U64_5770);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5776 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5776->data = new_data;
    hoisted__Vec__I64_5776->count = self->count;
    hoisted__Vec__I64_5776->cap = self->cap;
    (void)hoisted__Vec__I64_5776;
    return hoisted__Vec__I64_5776;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5777 = 16;
    (void)hoisted__U32_5777;
    return hoisted__U32_5777;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6898 = 3;
    (void)hoisted__U32_6898;
    Array__Str *_va_Array_200 = Array__Str_new(hoisted__U32_6898);
    (void)_va_Array_200;
    I64 _va_Array_200_ek = 0;
    (void)_va_Array_200_ek;
    OutOfBounds *_va_Array_200_eo = malloc(sizeof(OutOfBounds));
    _va_Array_200_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_200_eo;
    U32 hoisted__U32_6899 = 0;
    (void)hoisted__U32_6899;
    Str *hoisted__Str_6900 = Str_clone(loc);
    (void)hoisted__Str_6900;
    Array__Str_set(_va_Array_200, hoisted__U32_6899, hoisted__Str_6900, &_va_Array_200_ek, _va_Array_200_eo);
    U32 hoisted__U32_6901 = 1;
    (void)hoisted__U32_6901;
    Str hoisted__Str_6902 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6902;
    Array__Str_set(_va_Array_200, hoisted__U32_6901, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6902; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_200_ek, _va_Array_200_eo);
    Array__Str *hoisted__Array__Str_6903 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6903;
    U32 hoisted__U32_6904 = 2;
    (void)hoisted__U32_6904;
    Str *hoisted__Str_6905 = format(hoisted__Array__Str_6903);
    (void)hoisted__Str_6905;
    Array__Str_set(_va_Array_200, hoisted__U32_6904, hoisted__Str_6905, &_va_Array_200_ek, _va_Array_200_eo);
    OutOfBounds_delete(_va_Array_200_eo, 1);
    Array__Str_delete(parts, 1);
    println(_va_Array_200);
    I64 hoisted__I64_6906 = 1;
    (void)hoisted__I64_6906;
    exit(hoisted__I64_6906);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_6913 = 1;
    (void)hoisted__U32_6913;
    Array__Str *_va_Array_202 = Array__Str_new(hoisted__U32_6913);
    (void)_va_Array_202;
    I64 _va_Array_202_ek = 0;
    (void)_va_Array_202_ek;
    OutOfBounds *_va_Array_202_eo = malloc(sizeof(OutOfBounds));
    _va_Array_202_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_202_eo;
    U32 hoisted__U32_6914 = 0;
    (void)hoisted__U32_6914;
    Str hoisted__Str_6915 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6915;
    Array__Str_set(_va_Array_202, hoisted__U32_6914, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6915; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_202_ek, _va_Array_202_eo);
    OutOfBounds_delete(_va_Array_202_eo, 1);
    panic(_va_Array_202, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6919 = not(cond);
    (void)hoisted__Bool_6919;
    if (hoisted__Bool_6919) {
        U32 hoisted__U32_6916 = 1;
        (void)hoisted__U32_6916;
        Array__Str *_va_Array_203 = Array__Str_new(hoisted__U32_6916);
        (void)_va_Array_203;
        I64 _va_Array_203_ek = 0;
        (void)_va_Array_203_ek;
        OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
        _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_203_eo;
        U32 hoisted__U32_6917 = 0;
        (void)hoisted__U32_6917;
        Str hoisted__Str_6918 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6918;
        Array__Str_set(_va_Array_203, hoisted__U32_6917, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6918; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_203_ek, _va_Array_203_eo);
        OutOfBounds_delete(_va_Array_203_eo, 1);
        panic(_va_Array_203, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6927 = parts;
        (void)_fc_Array__Str_6927;
        (void)_fc_Array__Str_6927;
        U32 _fi_USize_6927 = 0;
        (void)_fi_USize_6927;
        I64 _forin_err_kind_6927 = 0;
        (void)_forin_err_kind_6927;
        OutOfBounds *_forin_OutOfBounds_6927 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_6927->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_6927;
        while (1) {
            U32 hoisted__U32_6935 = Array__Str_len(_fc_Array__Str_6927);
            (void)hoisted__U32_6935;
            Bool _wcond_Bool_6928 = U32_lt(_fi_USize_6927, hoisted__U32_6935);
            (void)_wcond_Bool_6928;
            if (_wcond_Bool_6928) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_6927, &_fi_USize_6927, &_forin_err_kind_6927, _forin_OutOfBounds_6927);
            I64 hoisted__I64_6936 = 0;
            (void)hoisted__I64_6936;
            Bool hoisted__Bool_6937 = I64_eq(_forin_err_kind_6927, hoisted__I64_6936);
            (void)hoisted__Bool_6937;
            Bool hoisted__Bool_6938 = not(hoisted__Bool_6937);
            (void)hoisted__Bool_6938;
            if (hoisted__Bool_6938) {
                U32 hoisted__U32_6929 = 2;
                (void)hoisted__U32_6929;
                Array__Str *_va_Array_205 = Array__Str_new(hoisted__U32_6929);
                (void)_va_Array_205;
                I64 _va_Array_205_ek = 0;
                (void)_va_Array_205_ek;
                OutOfBounds *_va_Array_205_eo = malloc(sizeof(OutOfBounds));
                _va_Array_205_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_205_eo;
                U32 hoisted__U32_6930 = 0;
                (void)hoisted__U32_6930;
                Str hoisted__Str_6931 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6931;
                Array__Str_set(_va_Array_205, hoisted__U32_6930, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6931; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_205_ek, _va_Array_205_eo);
                U32 hoisted__U32_6932 = 1;
                (void)hoisted__U32_6932;
                Str hoisted__Str_6933 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6933;
                Array__Str_set(_va_Array_205, hoisted__U32_6932, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6933; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_205_ek, _va_Array_205_eo);
                OutOfBounds_delete(_va_Array_205_eo, 1);
                Str hoisted__Str_6934 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6934;
                panic(_va_Array_205, &hoisted__Str_6934);
                Str_delete(&hoisted__Str_6934, (Bool){0});
            }
            U32 hoisted__U32_6939 = 1;
            (void)hoisted__U32_6939;
            U32 hoisted__U32_6940 = U32_add(_fi_USize_6927, hoisted__U32_6939);
            (void)hoisted__U32_6940;
            _fi_USize_6927 = hoisted__U32_6940;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_6927, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_6980 = ptr_eq(p, NULL);
    (void)hoisted__Bool_6980;
    return hoisted__Bool_6980;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6989 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6989;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6989;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6990 = 0;
    (void)hoisted__U32_6990;
    U64 hoisted__U64_6991 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6990); });
    (void)hoisted__U64_6991;
    return hoisted__U64_6991;
}

U32 Range_size(void) {
    U32 hoisted__U32_7015 = 16;
    (void)hoisted__U32_7015;
    return hoisted__U32_7015;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7126 = 3;
    (void)hoisted__I64_7126;
    Str hoisted__Str_7127 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7127;
    assert_eq__I64(result, hoisted__I64_7126, &hoisted__Str_7127);
    Str_delete(&hoisted__Str_7127, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7134 = 15;
    (void)hoisted__I64_7134;
    Str hoisted__Str_7135 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7135;
    assert_eq__I64(result, hoisted__I64_7134, &hoisted__Str_7135);
    Str_delete(&hoisted__Str_7135, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7142 = 26;
    (void)hoisted__I64_7142;
    Str hoisted__Str_7143 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7143;
    assert_eq__I64(result, hoisted__I64_7142, &hoisted__Str_7143);
    Str_delete(&hoisted__Str_7143, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7146 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7146;
    Str hoisted__Str_7147 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7147;
    assert_eq__Str(&result, &hoisted__Str_7146, &hoisted__Str_7147);
    Str_delete(&hoisted__Str_7146, (Bool){0});
    Str_delete(&hoisted__Str_7147, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7168 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7168;
    Str hoisted__Str_7169 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7169;
    assert_eq__Str(&r, &hoisted__Str_7168, &hoisted__Str_7169);
    Str_delete(&hoisted__Str_7168, (Bool){0});
    Str_delete(&hoisted__Str_7169, (Bool){0});
    Str_delete(&r, (Bool){0});
    Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7173 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7173;
    Str hoisted__Str_7174 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7174;
    assert_eq__Str(&r2, &hoisted__Str_7173, &hoisted__Str_7174);
    Str_delete(&hoisted__Str_7173, (Bool){0});
    Str_delete(&hoisted__Str_7174, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7201 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7201;
    Str hoisted__Str_7202 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7202;
    assert_eq__Str(&d, &hoisted__Str_7201, &hoisted__Str_7202);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7201, (Bool){0});
    Str_delete(&hoisted__Str_7202, (Bool){0});
    Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7210 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7210;
    Str hoisted__Str_7211 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7211;
    assert_eq__Str(&d2, &hoisted__Str_7210, &hoisted__Str_7211);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7210, (Bool){0});
    Str_delete(&hoisted__Str_7211, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7220 = 106;
    (void)hoisted__I64_7220;
    Str hoisted__Str_7221 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7221;
    assert_eq__I64(d3, hoisted__I64_7220, &hoisted__Str_7221);
    Str_delete(&hoisted__Str_7221, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7710 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7710;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_7710);
    Str_delete(&hoisted__Str_7710, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_7711 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7711;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_7711);
    Str_delete(&hoisted__Str_7711, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_7713 = 8;
    (void)hoisted__I64_7713;
    Str hoisted__Str_7714 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7714;
    assert_eq__I64(result, hoisted__I64_7713, &hoisted__Str_7714);
    Str_delete(&hoisted__Str_7714, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7717 = 1;
    (void)hoisted__Bool_7717;
    Str hoisted__Str_7718 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7718;
    assert(hoisted__Bool_7717, &hoisted__Str_7718);
    Str_delete(&hoisted__Str_7718, (Bool){0});
    Bool hoisted__Bool_7721 = 1;
    (void)hoisted__Bool_7721;
    Str hoisted__Str_7722 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7722;
    assert(hoisted__Bool_7721, &hoisted__Str_7722);
    Str_delete(&hoisted__Str_7722, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_7727 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7727;
    Str hoisted__Str_7728 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7728;
    Str hoisted__Str_7729 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7729;
    assert_eq__Str(&hoisted__Str_7727, &hoisted__Str_7728, &hoisted__Str_7729);
    Str_delete(&hoisted__Str_7727, (Bool){0});
    Str_delete(&hoisted__Str_7728, (Bool){0});
    Str_delete(&hoisted__Str_7729, (Bool){0});
    Str hoisted__Str_7732 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7732;
    Str hoisted__Str_7733 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7733;
    Str hoisted__Str_7734 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7734;
    assert_eq__Str(&hoisted__Str_7732, &hoisted__Str_7733, &hoisted__Str_7734);
    Str_delete(&hoisted__Str_7732, (Bool){0});
    Str_delete(&hoisted__Str_7733, (Bool){0});
    Str_delete(&hoisted__Str_7734, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7739 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7739;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7739;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7740 = 0;
    (void)hoisted__U32_7740;
    U64 hoisted__U64_7741 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7740); });
    (void)hoisted__U64_7741;
    return hoisted__U64_7741;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_7765 = 16;
    (void)hoisted__U32_7765;
    return hoisted__U32_7765;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_7766 = 42;
    (void)hoisted__I64_7766;
    Str hoisted__Str_7767 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7767;
    assert_eq__I64(v.x, hoisted__I64_7766, &hoisted__Str_7767);
    Str_delete(&hoisted__Str_7767, (Bool){0});
    I64 hoisted__I64_7768 = 99;
    (void)hoisted__I64_7768;
    Str hoisted__Str_7769 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7769;
    assert_eq__I64(v.y, hoisted__I64_7768, &hoisted__Str_7769);
    Str_delete(&hoisted__Str_7769, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7772 = 10;
    (void)hoisted__I64_7772;
    Str hoisted__Str_7773 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7773;
    assert_eq__I64(p.x, hoisted__I64_7772, &hoisted__Str_7773);
    Str_delete(&hoisted__Str_7773, (Bool){0});
    I64 hoisted__I64_7774 = 20;
    (void)hoisted__I64_7774;
    Str hoisted__Str_7775 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7775;
    assert_eq__I64(p.y, hoisted__I64_7774, &hoisted__Str_7775);
    Str_delete(&hoisted__Str_7775, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7781 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7781;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7781;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7782 = 0;
    (void)hoisted__U32_7782;
    U64 hoisted__U64_7783 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7782); });
    (void)hoisted__U64_7783;
    return hoisted__U64_7783;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_7807 = 32;
    (void)hoisted__U32_7807;
    return hoisted__U32_7807;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_7808 = 5;
    (void)hoisted__I64_7808;
    Str hoisted__Str_7809 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7809;
    assert_eq__I64(r.top_left.x, hoisted__I64_7808, &hoisted__Str_7809);
    Str_delete(&hoisted__Str_7809, (Bool){0});
    I64 hoisted__I64_7810 = 10;
    (void)hoisted__I64_7810;
    Str hoisted__Str_7811 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7811;
    assert_eq__I64(r.top_left.y, hoisted__I64_7810, &hoisted__Str_7811);
    Str_delete(&hoisted__Str_7811, (Bool){0});
    I64 hoisted__I64_7812 = 100;
    (void)hoisted__I64_7812;
    Str hoisted__Str_7813 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7813;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7812, &hoisted__Str_7813);
    Str_delete(&hoisted__Str_7813, (Bool){0});
    I64 hoisted__I64_7814 = 200;
    (void)hoisted__I64_7814;
    Str hoisted__Str_7815 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7815;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7814, &hoisted__Str_7815);
    Str_delete(&hoisted__Str_7815, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7817 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7817;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7817;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7818 = 0;
    (void)hoisted__U32_7818;
    U64 hoisted__U64_7819 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7818); });
    (void)hoisted__U64_7819;
    return hoisted__U64_7819;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_7852 = 12;
    (void)hoisted__U32_7852;
    return hoisted__U32_7852;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_7856 = F32_to_str(v.x);
    (void)hoisted__Str_7856;
    Str hoisted__Str_7857 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7857;
    Str hoisted__Str_7858 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7858;
    assert_eq__Str(hoisted__Str_7856, &hoisted__Str_7857, &hoisted__Str_7858);
    Str_delete(hoisted__Str_7856, 1);
    Str_delete(&hoisted__Str_7857, (Bool){0});
    Str_delete(&hoisted__Str_7858, (Bool){0});
    Str *hoisted__Str_7859 = F32_to_str(v.y);
    (void)hoisted__Str_7859;
    Str hoisted__Str_7860 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7860;
    Str hoisted__Str_7861 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7861;
    assert_eq__Str(hoisted__Str_7859, &hoisted__Str_7860, &hoisted__Str_7861);
    Str_delete(hoisted__Str_7859, 1);
    Str_delete(&hoisted__Str_7860, (Bool){0});
    Str_delete(&hoisted__Str_7861, (Bool){0});
    Str *hoisted__Str_7862 = F32_to_str(v.z);
    (void)hoisted__Str_7862;
    Str hoisted__Str_7863 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7863;
    Str hoisted__Str_7864 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7864;
    assert_eq__Str(hoisted__Str_7862, &hoisted__Str_7863, &hoisted__Str_7864);
    Str_delete(hoisted__Str_7862, 1);
    Str_delete(&hoisted__Str_7863, (Bool){0});
    Str_delete(&hoisted__Str_7864, (Bool){0});
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
    Bool hoisted__Bool_7869 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7869;
    if (hoisted__Bool_7869) {
        Bool hoisted__Bool_7866 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_7866;
        { Bool _ret_val = hoisted__Bool_7866;
                return _ret_val; }
    }
    Bool hoisted__Bool_7870 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7870;
    if (hoisted__Bool_7870) {
        Bool hoisted__Bool_7867 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_7867;
        { Bool _ret_val = hoisted__Bool_7867;
                return _ret_val; }
    }
    Bool hoisted__Bool_7871 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7871;
    if (hoisted__Bool_7871) {
        Bool hoisted__Bool_7868 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_7868;
        { Bool _ret_val = hoisted__Bool_7868;
                return _ret_val; }
    }
    Bool hoisted__Bool_7872 = 0;
    (void)hoisted__Bool_7872;
    return hoisted__Bool_7872;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7880 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7880;
    if (hoisted__Bool_7880) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_7881 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7881;
    if (hoisted__Bool_7881) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_7882 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7882;
    if (hoisted__Bool_7882) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_7883 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7883;
    UNREACHABLE(&hoisted__Str_7883);
    Str_delete(&hoisted__Str_7883, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_7884 = 4;
    (void)hoisted__U32_7884;
    return hoisted__U32_7884;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7885 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7885;
    Str hoisted__Str_7886 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7886;
    assert(hoisted__Bool_7885, &hoisted__Str_7886);
    Str_delete(&hoisted__Str_7886, (Bool){0});
    Bool hoisted__Bool_7887 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7887;
    Bool hoisted__Bool_7888 = not(hoisted__Bool_7887);
    (void)hoisted__Bool_7888;
    Str hoisted__Str_7889 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7889;
    assert(hoisted__Bool_7888, &hoisted__Str_7889);
    Str_delete(&hoisted__Str_7889, (Bool){0});
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
    free(val);
    return r;
}
Token *Token_Eof() {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Eof;
    return r;
}
Bool Token_is(Token * self, Token * other) {
    Bool hoisted__Bool_7890 = is(self, other);
    (void)hoisted__Bool_7890;
    return hoisted__Bool_7890;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7908 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7908;
    if (hoisted__Bool_7908) {
        I64 *hoisted__I64_7904 = get_payload(self);
        (void)hoisted__I64_7904;
        (void)hoisted__I64_7904;
        Bool hoisted__Bool_7905 = 0;
        (void)hoisted__Bool_7905;
        I64_delete(hoisted__I64_7904, hoisted__Bool_7905);
    }
    Bool hoisted__Bool_7909 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7909;
    if (hoisted__Bool_7909) {
        Str *hoisted__Str_7906 = get_payload(self);
        (void)hoisted__Str_7906;
        (void)hoisted__Str_7906;
        Bool hoisted__Bool_7907 = 0;
        (void)hoisted__Bool_7907;
        Str_delete(hoisted__Str_7906, hoisted__Bool_7907);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_7934 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7934;
    if (hoisted__Bool_7934) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7931 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7931;
        { Token * _ret_val = hoisted__Token_7931;
                return _ret_val; }
    }
    Bool hoisted__Bool_7935 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7935;
    if (hoisted__Bool_7935) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7932 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7932;
        Token *hoisted__Token_7933 = Token_Name(hoisted__Str_7932);
        (void)hoisted__Token_7933;
        { Token * _ret_val = hoisted__Token_7933;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_7936 = 24;
    (void)hoisted__U32_7936;
    return hoisted__U32_7936;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7938 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7938;
    Str hoisted__Str_7939 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7939;
    assert(hoisted__Bool_7938, &hoisted__Str_7939);
    Str_delete(&hoisted__Str_7939, (Bool){0});
    Bool hoisted__Bool_7940 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7940;
    Bool hoisted__Bool_7941 = not(hoisted__Bool_7940);
    (void)hoisted__Bool_7941;
    Str hoisted__Str_7942 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7942;
    assert(hoisted__Bool_7941, &hoisted__Str_7942);
    Str_delete(&hoisted__Str_7942, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7943 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7943;
    Str hoisted__Str_7944 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7944;
    assert(hoisted__Bool_7943, &hoisted__Str_7944);
    Str_delete(&hoisted__Str_7944, (Bool){0});
    Bool hoisted__Bool_7945 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7945;
    Bool hoisted__Bool_7946 = not(hoisted__Bool_7945);
    (void)hoisted__Bool_7946;
    Str hoisted__Str_7947 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7947;
    assert(hoisted__Bool_7946, &hoisted__Str_7947);
    Str_delete(&hoisted__Str_7947, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7950 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7950;
    Str hoisted__Str_7951 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7951;
    assert(hoisted__Bool_7950, &hoisted__Str_7951);
    Str_delete(&hoisted__Str_7951, (Bool){0});
    Bool hoisted__Bool_7952 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7952;
    Bool hoisted__Bool_7953 = not(hoisted__Bool_7952);
    (void)hoisted__Bool_7953;
    Str hoisted__Str_7954 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7954;
    assert(hoisted__Bool_7953, &hoisted__Str_7954);
    Str_delete(&hoisted__Str_7954, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8092 = I64_neq(a, b);
    (void)hoisted__Bool_8092;
    if (hoisted__Bool_8092) {
        U32 hoisted__U32_8081 = 5;
        (void)hoisted__U32_8081;
        Array__Str *_va_Array_251 = Array__Str_new(hoisted__U32_8081);
        (void)_va_Array_251;
        I64 _va_Array_251_ek = 0;
        (void)_va_Array_251_ek;
        OutOfBounds *_va_Array_251_eo = malloc(sizeof(OutOfBounds));
        _va_Array_251_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_251_eo;
        U32 hoisted__U32_8082 = 0;
        (void)hoisted__U32_8082;
        Str hoisted__Str_8083 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8083;
        Array__Str_set(_va_Array_251, hoisted__U32_8082, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8083; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_251_ek, _va_Array_251_eo);
        U32 hoisted__U32_8084 = 1;
        (void)hoisted__U32_8084;
        Str *hoisted__Str_8085 = I64_to_str(a);
        (void)hoisted__Str_8085;
        Array__Str_set(_va_Array_251, hoisted__U32_8084, hoisted__Str_8085, &_va_Array_251_ek, _va_Array_251_eo);
        U32 hoisted__U32_8086 = 2;
        (void)hoisted__U32_8086;
        Str hoisted__Str_8087 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8087;
        Array__Str_set(_va_Array_251, hoisted__U32_8086, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8087; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_251_ek, _va_Array_251_eo);
        U32 hoisted__U32_8088 = 3;
        (void)hoisted__U32_8088;
        Str *hoisted__Str_8089 = I64_to_str(b);
        (void)hoisted__Str_8089;
        Array__Str_set(_va_Array_251, hoisted__U32_8088, hoisted__Str_8089, &_va_Array_251_ek, _va_Array_251_eo);
        U32 hoisted__U32_8090 = 4;
        (void)hoisted__U32_8090;
        Str hoisted__Str_8091 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8091;
        Array__Str_set(_va_Array_251, hoisted__U32_8090, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8091; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_251_ek, _va_Array_251_eo);
        OutOfBounds_delete(_va_Array_251_eo, 1);
        panic(_va_Array_251, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8104 = Str_neq(a, b);
    (void)hoisted__Bool_8104;
    if (hoisted__Bool_8104) {
        U32 hoisted__U32_8093 = 5;
        (void)hoisted__U32_8093;
        Array__Str *_va_Array_252 = Array__Str_new(hoisted__U32_8093);
        (void)_va_Array_252;
        I64 _va_Array_252_ek = 0;
        (void)_va_Array_252_ek;
        OutOfBounds *_va_Array_252_eo = malloc(sizeof(OutOfBounds));
        _va_Array_252_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_252_eo;
        U32 hoisted__U32_8094 = 0;
        (void)hoisted__U32_8094;
        Str hoisted__Str_8095 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8095;
        Array__Str_set(_va_Array_252, hoisted__U32_8094, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8095; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_252_ek, _va_Array_252_eo);
        U32 hoisted__U32_8096 = 1;
        (void)hoisted__U32_8096;
        Str *hoisted__Str_8097 = Str_to_str(a);
        (void)hoisted__Str_8097;
        Array__Str_set(_va_Array_252, hoisted__U32_8096, hoisted__Str_8097, &_va_Array_252_ek, _va_Array_252_eo);
        U32 hoisted__U32_8098 = 2;
        (void)hoisted__U32_8098;
        Str hoisted__Str_8099 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8099;
        Array__Str_set(_va_Array_252, hoisted__U32_8098, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8099; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_252_ek, _va_Array_252_eo);
        U32 hoisted__U32_8100 = 3;
        (void)hoisted__U32_8100;
        Str *hoisted__Str_8101 = Str_to_str(b);
        (void)hoisted__Str_8101;
        Array__Str_set(_va_Array_252, hoisted__U32_8100, hoisted__Str_8101, &_va_Array_252_ek, _va_Array_252_eo);
        U32 hoisted__U32_8102 = 4;
        (void)hoisted__U32_8102;
        Str hoisted__Str_8103 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8103;
        Array__Str_set(_va_Array_252, hoisted__U32_8102, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8103; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_252_ek, _va_Array_252_eo);
        OutOfBounds_delete(_va_Array_252_eo, 1);
        panic(_va_Array_252, loc);
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
void *Str_get_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Str_get(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_get_dyn__til_closure = { (void *)Str_get_dyn, NULL, NULL };
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
void *Array__Str_get_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3) {
    (void)til_env;
    return (void *)Array__Str_get(_a0, _a1, _a2, _a3);
}
static __attribute__((unused)) TilClosure Array__Str_get_dyn__til_closure = { (void *)Array__Str_get_dyn, NULL, NULL };
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3, void *_a4) {
    (void)til_env;
    Array__Str_set(_a0, *(U32 *)_a1, _a2, _a3, _a4);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I32_hash_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)&Str_get_dyn__til_closure;
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
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)&Array__Str_get_dyn__til_closure;
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
        return 5LL;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        return 4LL;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        return 3LL;
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
        return 8LL;
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 12LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 13LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 14LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 15LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 16LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 17LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 18LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 19LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 20LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 21LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 22LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 23LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 24LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 25LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 26LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 12LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 13LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 14LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 15LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 16LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 17LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 18LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 19LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 20LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 21LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 22LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 23LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 24LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 25LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 26LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_VIEW}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
