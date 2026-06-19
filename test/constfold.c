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
    U32 hoisted__U32_1075 = 16;
    (void)hoisted__U32_1075;
    return hoisted__U32_1075;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1076 = Str_cmp(a, b);
    (void)hoisted__I64_1076;
    I64 hoisted__I64_1077 = 0;
    (void)hoisted__I64_1077;
    Bool hoisted__Bool_1078 = I64_eq(hoisted__I64_1076, hoisted__I64_1077);
    (void)hoisted__Bool_1078;
    return hoisted__Bool_1078;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1087 = Str_eq(a, b);
    (void)hoisted__Bool_1087;
    Bool hoisted__Bool_1088 = not(hoisted__Bool_1087);
    (void)hoisted__Bool_1088;
    return hoisted__Bool_1088;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1183 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1183->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1183;
    return hoisted__OutOfBounds_1183;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1184 = 0;
    (void)hoisted__Bool_1184;
    Str_delete(&self->msg, hoisted__Bool_1184);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1185 = 0;
    (void)hoisted__U32_1185;
    U64 hoisted__U64_1186 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1185); });
    (void)hoisted__U64_1186;
    return hoisted__U64_1186;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1201 = 16;
    (void)hoisted__U32_1201;
    return hoisted__U32_1201;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1221 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1221;
    U32 hoisted__U32_1222 = 16;
    (void)hoisted__U32_1222;
    Type *hoisted__Type_1223 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1223;
    U64 hoisted__U64_1224 = (U64)(cap);
    (void)hoisted__U64_1224;
    Type_delete(hoisted__Type_1221, 1);
    U64 hoisted__U64_1225 = (U64)(hoisted__U32_1222);
    (void)hoisted__U64_1225;
    Type_delete(hoisted__Type_1223, 1);
    void * hoisted__v_1226 = calloc(hoisted__U64_1224, hoisted__U64_1225);
    (void)hoisted__v_1226;
    Array__Str *hoisted__Array__Str_1227 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1227->data = hoisted__v_1226;
    hoisted__Array__Str_1227->cap = cap;
    (void)hoisted__Array__Str_1227;
    return hoisted__Array__Str_1227;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1249 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1249;
    if (hoisted__Bool_1249) {
        U32 hoisted__U32_1228 = 6;
        (void)hoisted__U32_1228;
        Array__Str *_va_Array_32 = Array__Str_new(hoisted__U32_1228);
        (void)_va_Array_32;
        I64 _va_Array_32_ek = 0;
        (void)_va_Array_32_ek;
        OutOfBounds *_va_Array_32_eo = malloc(sizeof(OutOfBounds));
        _va_Array_32_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_32_eo;
        U32 hoisted__U32_1229 = 0;
        (void)hoisted__U32_1229;
        Str hoisted__Str_1230 = (Str){.c_str = (void *)"./src/core/str.til:28:44", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1230;
        Array__Str_set(_va_Array_32, hoisted__U32_1229, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1230; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1231 = 1;
        (void)hoisted__U32_1231;
        Str hoisted__Str_1232 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1232;
        Array__Str_set(_va_Array_32, hoisted__U32_1231, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1232; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1233 = 2;
        (void)hoisted__U32_1233;
        Str *hoisted__Str_1234 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1234;
        Array__Str_set(_va_Array_32, hoisted__U32_1233, hoisted__Str_1234, &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1235 = 3;
        (void)hoisted__U32_1235;
        Str hoisted__Str_1236 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1236;
        Array__Str_set(_va_Array_32, hoisted__U32_1235, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1236; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1237 = 4;
        (void)hoisted__U32_1237;
        Str *hoisted__Str_1238 = U32_to_str(self->cap);
        (void)hoisted__Str_1238;
        Array__Str_set(_va_Array_32, hoisted__U32_1237, hoisted__Str_1238, &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1239 = 5;
        (void)hoisted__U32_1239;
        Str hoisted__Str_1240 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1240;
        Array__Str_set(_va_Array_32, hoisted__U32_1239, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1240; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        OutOfBounds_delete(_va_Array_32_eo, 1);
        OutOfBounds *hoisted__OutOfBounds_1241 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_32); hoisted__OutOfBounds_1241->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1241;
        U32 hoisted__U32_1242 = 16;
        (void)hoisted__U32_1242;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1241, hoisted__U32_1242);
        OutOfBounds_delete(hoisted__OutOfBounds_1241, 1);
        I64 hoisted__I64_1243 = 3;
        (void)hoisted__I64_1243;
        *_err_kind = hoisted__I64_1243;
    }
    I64 hoisted__I64_1250 = 0;
    (void)hoisted__I64_1250;
    Bool hoisted__Bool_1251 = I64_eq(DEREF(_err_kind), hoisted__I64_1250);
    (void)hoisted__Bool_1251;
    if (hoisted__Bool_1251) {
        U32 hoisted__U32_1244 = 16;
        (void)hoisted__U32_1244;
        U32 hoisted__U32_1245 = U32_mul(DEREF(i), hoisted__U32_1244);
        (void)hoisted__U32_1245;
        Type *hoisted__Type_1246 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1246;
        U64 hoisted__U64_1247 = (U64)(hoisted__U32_1245);
        (void)hoisted__U64_1247;
        Type_delete(hoisted__Type_1246, 1);
        void *hoisted__v_1248 = ptr_add(self->data, hoisted__U64_1247);
        (void)hoisted__v_1248;
        (void)hoisted__v_1248;
        { Str * _ret_val = hoisted__v_1248;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1286 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1286;
    if (hoisted__Bool_1286) {
        U32 hoisted__U32_1252 = 6;
        (void)hoisted__U32_1252;
        Array__Str *_va_Array_33 = Array__Str_new(hoisted__U32_1252);
        (void)_va_Array_33;
        I64 _va_Array_33_ek = 0;
        (void)_va_Array_33_ek;
        OutOfBounds *_va_Array_33_eo = malloc(sizeof(OutOfBounds));
        _va_Array_33_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_33_eo;
        U32 hoisted__U32_1253 = 0;
        (void)hoisted__U32_1253;
        Str hoisted__Str_1254 = (Str){.c_str = (void *)"./src/core/str.til:39:44", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1254;
        Array__Str_set(_va_Array_33, hoisted__U32_1253, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1254; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1255 = 1;
        (void)hoisted__U32_1255;
        Str hoisted__Str_1256 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1256;
        Array__Str_set(_va_Array_33, hoisted__U32_1255, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1256; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1257 = 2;
        (void)hoisted__U32_1257;
        Str *hoisted__Str_1258 = U32_to_str(i);
        (void)hoisted__Str_1258;
        Array__Str_set(_va_Array_33, hoisted__U32_1257, hoisted__Str_1258, &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1259 = 3;
        (void)hoisted__U32_1259;
        Str hoisted__Str_1260 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1260;
        Array__Str_set(_va_Array_33, hoisted__U32_1259, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1260; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1261 = 4;
        (void)hoisted__U32_1261;
        Str *hoisted__Str_1262 = U32_to_str(self->cap);
        (void)hoisted__Str_1262;
        Array__Str_set(_va_Array_33, hoisted__U32_1261, hoisted__Str_1262, &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1263 = 5;
        (void)hoisted__U32_1263;
        Str hoisted__Str_1264 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1264;
        Array__Str_set(_va_Array_33, hoisted__U32_1263, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1264; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        OutOfBounds_delete(_va_Array_33_eo, 1);
        OutOfBounds *hoisted__OutOfBounds_1265 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_33); hoisted__OutOfBounds_1265->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1265;
        U32 hoisted__U32_1266 = 16;
        (void)hoisted__U32_1266;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1265, hoisted__U32_1266);
        OutOfBounds_delete(hoisted__OutOfBounds_1265, 1);
        I64 hoisted__I64_1267 = 3;
        (void)hoisted__I64_1267;
        *_err_kind = hoisted__I64_1267;
    }
    I64 hoisted__I64_1287 = 0;
    (void)hoisted__I64_1287;
    Bool hoisted__Bool_1288 = I64_eq(DEREF(_err_kind), hoisted__I64_1287);
    (void)hoisted__Bool_1288;
    if (hoisted__Bool_1288) {
        U32 hoisted__U32_1268 = 16;
        (void)hoisted__U32_1268;
        U32 hoisted__U32_1269 = U32_mul(i, hoisted__U32_1268);
        (void)hoisted__U32_1269;
        Type *hoisted__Type_1270 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1270;
        U64 hoisted__U64_1271 = (U64)(hoisted__U32_1269);
        (void)hoisted__U64_1271;
        Type_delete(hoisted__Type_1270, 1);
        Str *hoisted__Str_1272 = ptr_add(self->data, hoisted__U64_1271);
        (void)hoisted__Str_1272;
        (void)hoisted__Str_1272;
        Bool hoisted__Bool_1273 = 0;
        (void)hoisted__Bool_1273;
        Str_delete(hoisted__Str_1272, hoisted__Bool_1273);
        U32 hoisted__U32_1274 = 16;
        (void)hoisted__U32_1274;
        U32 hoisted__U32_1275 = U32_mul(i, hoisted__U32_1274);
        (void)hoisted__U32_1275;
        Type *hoisted__Type_1276 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1276;
        U64 hoisted__U64_1277 = (U64)(hoisted__U32_1275);
        (void)hoisted__U64_1277;
        Type_delete(hoisted__Type_1276, 1);
        U32 hoisted__U32_1278 = 16;
        (void)hoisted__U32_1278;
        Type *hoisted__Type_1279 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1279;
        void *hoisted__v_1280 = ptr_add(self->data, hoisted__U64_1277);
        (void)hoisted__v_1280;
        (void)hoisted__v_1280;
        U64 hoisted__U64_1281 = (U64)(hoisted__U32_1278);
        (void)hoisted__U64_1281;
        Type_delete(hoisted__Type_1279, 1);
        memcpy(hoisted__v_1280, val, hoisted__U64_1281);
        U32 hoisted__U32_1282 = 16;
        (void)hoisted__U32_1282;
        Type *hoisted__Type_1283 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1283;
        I32 hoisted__I32_1284 = 0;
        (void)hoisted__I32_1284;
        U64 hoisted__U64_1285 = (U64)(hoisted__U32_1282);
        (void)hoisted__U64_1285;
        Type_delete(hoisted__Type_1283, 1);
        memset(val, hoisted__I32_1284, hoisted__U64_1285);
    }
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1289 = self->cap;
        (void)_re_U32_1289;
        U32 _rc_U32_1289 = 0;
        (void)_rc_U32_1289;
        Bool hoisted__Bool_1304 = U32_lte(_rc_U32_1289, _re_U32_1289);
        (void)hoisted__Bool_1304;
        if (hoisted__Bool_1304) {
            while (1) {
                Bool _wcond_Bool_1290 = U32_lt(_rc_U32_1289, _re_U32_1289);
                (void)_wcond_Bool_1290;
                if (_wcond_Bool_1290) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1289);
                U32_inc(&_rc_U32_1289);
                U32 hoisted__U32_1291 = 16;
                (void)hoisted__U32_1291;
                U32 hoisted__U32_1292 = U32_mul(i, hoisted__U32_1291);
                (void)hoisted__U32_1292;
                Type *hoisted__Type_1293 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1293;
                U64 hoisted__U64_1294 = (U64)(hoisted__U32_1292);
                (void)hoisted__U64_1294;
                Type_delete(hoisted__Type_1293, 1);
                Str *hoisted__Str_1295 = ptr_add(self->data, hoisted__U64_1294);
                (void)hoisted__Str_1295;
                (void)hoisted__Str_1295;
                Bool hoisted__Bool_1296 = 0;
                (void)hoisted__Bool_1296;
                Str_delete(hoisted__Str_1295, hoisted__Bool_1296);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1297 = U32_gt(_rc_U32_1289, _re_U32_1289);
                (void)_wcond_Bool_1297;
                if (_wcond_Bool_1297) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1289);
                U32_dec(&_rc_U32_1289);
                U32 hoisted__U32_1298 = 16;
                (void)hoisted__U32_1298;
                U32 hoisted__U32_1299 = U32_mul(i, hoisted__U32_1298);
                (void)hoisted__U32_1299;
                Type *hoisted__Type_1300 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1300;
                U64 hoisted__U64_1301 = (U64)(hoisted__U32_1299);
                (void)hoisted__U64_1301;
                Type_delete(hoisted__Type_1300, 1);
                Str *hoisted__Str_1302 = ptr_add(self->data, hoisted__U64_1301);
                (void)hoisted__Str_1302;
                (void)hoisted__Str_1302;
                Bool hoisted__Bool_1303 = 0;
                (void)hoisted__Bool_1303;
                Str_delete(hoisted__Str_1302, hoisted__Bool_1303);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1341 = 16;
    (void)hoisted__U32_1341;
    U32 hoisted__U32_1342 = U32_mul(self->cap, hoisted__U32_1341);
    (void)hoisted__U32_1342;
    Type *hoisted__Type_1343 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1343;
    U64 hoisted__U64_1344 = (U64)(hoisted__U32_1342);
    (void)hoisted__U64_1344;
    Type_delete(hoisted__Type_1343, 1);
    void * new_data = malloc(hoisted__U64_1344);
    {
        U32 _re_U32_1305 = self->cap;
        (void)_re_U32_1305;
        U32 _rc_U32_1305 = 0;
        (void)_rc_U32_1305;
        Bool hoisted__Bool_1340 = U32_lte(_rc_U32_1305, _re_U32_1305);
        (void)hoisted__Bool_1340;
        if (hoisted__Bool_1340) {
            while (1) {
                Bool _wcond_Bool_1306 = U32_lt(_rc_U32_1305, _re_U32_1305);
                (void)_wcond_Bool_1306;
                if (_wcond_Bool_1306) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1305);
                U32_inc(&_rc_U32_1305);
                U32 hoisted__U32_1307 = 16;
                (void)hoisted__U32_1307;
                U32 hoisted__U32_1308 = U32_mul(i, hoisted__U32_1307);
                (void)hoisted__U32_1308;
                Type *hoisted__Type_1309 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1309;
                U64 hoisted__U64_1310 = (U64)(hoisted__U32_1308);
                (void)hoisted__U64_1310;
                Type_delete(hoisted__Type_1309, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1310);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1311 = 16;
                (void)hoisted__U32_1311;
                U32 hoisted__U32_1312 = U32_mul(i, hoisted__U32_1311);
                (void)hoisted__U32_1312;
                Type *hoisted__Type_1313 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1313;
                U64 hoisted__U64_1314 = (U64)(hoisted__U32_1312);
                (void)hoisted__U64_1314;
                Type_delete(hoisted__Type_1313, 1);
                U32 hoisted__U32_1315 = 16;
                (void)hoisted__U32_1315;
                Type *hoisted__Type_1316 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1316;
                void *hoisted__v_1317 = ptr_add(new_data, hoisted__U64_1314);
                (void)hoisted__v_1317;
                (void)hoisted__v_1317;
                U64 hoisted__U64_1318 = (U64)(hoisted__U32_1315);
                (void)hoisted__U64_1318;
                Type_delete(hoisted__Type_1316, 1);
                memcpy(hoisted__v_1317, cloned, hoisted__U64_1318);
                U32 hoisted__U32_1319 = 16;
                (void)hoisted__U32_1319;
                Type *hoisted__Type_1320 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1320;
                I32 hoisted__I32_1321 = 0;
                (void)hoisted__I32_1321;
                U64 hoisted__U64_1322 = (U64)(hoisted__U32_1319);
                (void)hoisted__U64_1322;
                Type_delete(hoisted__Type_1320, 1);
                memset(cloned, hoisted__I32_1321, hoisted__U64_1322);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1323 = U32_gt(_rc_U32_1305, _re_U32_1305);
                (void)_wcond_Bool_1323;
                if (_wcond_Bool_1323) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1305);
                U32_dec(&_rc_U32_1305);
                U32 hoisted__U32_1324 = 16;
                (void)hoisted__U32_1324;
                U32 hoisted__U32_1325 = U32_mul(i, hoisted__U32_1324);
                (void)hoisted__U32_1325;
                Type *hoisted__Type_1326 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1326;
                U64 hoisted__U64_1327 = (U64)(hoisted__U32_1325);
                (void)hoisted__U64_1327;
                Type_delete(hoisted__Type_1326, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1327);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1328 = 16;
                (void)hoisted__U32_1328;
                U32 hoisted__U32_1329 = U32_mul(i, hoisted__U32_1328);
                (void)hoisted__U32_1329;
                Type *hoisted__Type_1330 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1330;
                U64 hoisted__U64_1331 = (U64)(hoisted__U32_1329);
                (void)hoisted__U64_1331;
                Type_delete(hoisted__Type_1330, 1);
                U32 hoisted__U32_1332 = 16;
                (void)hoisted__U32_1332;
                Type *hoisted__Type_1333 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1333;
                void *hoisted__v_1334 = ptr_add(new_data, hoisted__U64_1331);
                (void)hoisted__v_1334;
                (void)hoisted__v_1334;
                U64 hoisted__U64_1335 = (U64)(hoisted__U32_1332);
                (void)hoisted__U64_1335;
                Type_delete(hoisted__Type_1333, 1);
                memcpy(hoisted__v_1334, cloned, hoisted__U64_1335);
                U32 hoisted__U32_1336 = 16;
                (void)hoisted__U32_1336;
                Type *hoisted__Type_1337 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1337;
                I32 hoisted__I32_1338 = 0;
                (void)hoisted__I32_1338;
                U64 hoisted__U64_1339 = (U64)(hoisted__U32_1336);
                (void)hoisted__U64_1339;
                Type_delete(hoisted__Type_1337, 1);
                memset(cloned, hoisted__I32_1338, hoisted__U64_1339);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1345 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1345->data = new_data;
    hoisted__Array__Str_1345->cap = self->cap;
    (void)hoisted__Array__Str_1345;
    return hoisted__Array__Str_1345;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1346 = 16;
    (void)hoisted__U32_1346;
    return hoisted__U32_1346;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1347 = 16;
    (void)hoisted__U32_1347;
    Type *hoisted__Type_1348 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1348;
    U64 hoisted__U64_1349 = (U64)(hoisted__U32_1347);
    (void)hoisted__U64_1349;
    Type_delete(hoisted__Type_1348, 1);
    void * hoisted__v_1350 = malloc(hoisted__U64_1349);
    (void)hoisted__v_1350;
    U32 hoisted__U32_1351 = 0;
    (void)hoisted__U32_1351;
    I64 hoisted__I64_1352 = 1;
    (void)hoisted__I64_1352;
    Vec__Str *hoisted__Vec__Str_1353 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1353->data = hoisted__v_1350;
    hoisted__Vec__Str_1353->count = hoisted__U32_1351;
    hoisted__Vec__Str_1353->cap = hoisted__I64_1352;
    (void)hoisted__Vec__Str_1353;
    return hoisted__Vec__Str_1353;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1354 = self->count;
        (void)_re_U32_1354;
        U32 _rc_U32_1354 = 0;
        (void)_rc_U32_1354;
        Bool hoisted__Bool_1369 = U32_lte(_rc_U32_1354, _re_U32_1354);
        (void)hoisted__Bool_1369;
        if (hoisted__Bool_1369) {
            while (1) {
                Bool _wcond_Bool_1355 = U32_lt(_rc_U32_1354, _re_U32_1354);
                (void)_wcond_Bool_1355;
                if (_wcond_Bool_1355) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1354);
                U32_inc(&_rc_U32_1354);
                U32 hoisted__U32_1356 = 16;
                (void)hoisted__U32_1356;
                U32 hoisted__U32_1357 = U32_mul(i, hoisted__U32_1356);
                (void)hoisted__U32_1357;
                Type *hoisted__Type_1358 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1358;
                U64 hoisted__U64_1359 = (U64)(hoisted__U32_1357);
                (void)hoisted__U64_1359;
                Type_delete(hoisted__Type_1358, 1);
                Str *hoisted__Str_1360 = ptr_add(self->data, hoisted__U64_1359);
                (void)hoisted__Str_1360;
                (void)hoisted__Str_1360;
                Bool hoisted__Bool_1361 = 0;
                (void)hoisted__Bool_1361;
                Str_delete(hoisted__Str_1360, hoisted__Bool_1361);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1362 = U32_gt(_rc_U32_1354, _re_U32_1354);
                (void)_wcond_Bool_1362;
                if (_wcond_Bool_1362) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1354);
                U32_dec(&_rc_U32_1354);
                U32 hoisted__U32_1363 = 16;
                (void)hoisted__U32_1363;
                U32 hoisted__U32_1364 = U32_mul(i, hoisted__U32_1363);
                (void)hoisted__U32_1364;
                Type *hoisted__Type_1365 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1365;
                U64 hoisted__U64_1366 = (U64)(hoisted__U32_1364);
                (void)hoisted__U64_1366;
                Type_delete(hoisted__Type_1365, 1);
                Str *hoisted__Str_1367 = ptr_add(self->data, hoisted__U64_1366);
                (void)hoisted__Str_1367;
                (void)hoisted__Str_1367;
                Bool hoisted__Bool_1368 = 0;
                (void)hoisted__Bool_1368;
                Str_delete(hoisted__Str_1367, hoisted__Bool_1368);
            }
        }
    }
    U32 hoisted__U32_1370 = 0;
    (void)hoisted__U32_1370;
    self->count = hoisted__U32_1370;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1663 = 16;
    (void)hoisted__U32_1663;
    U32 hoisted__U32_1664 = U32_mul(self->cap, hoisted__U32_1663);
    (void)hoisted__U32_1664;
    Type *hoisted__Type_1665 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1665;
    U64 hoisted__U64_1666 = (U64)(hoisted__U32_1664);
    (void)hoisted__U64_1666;
    Type_delete(hoisted__Type_1665, 1);
    void * new_data = malloc(hoisted__U64_1666);
    {
        U32 _re_U32_1627 = self->count;
        (void)_re_U32_1627;
        U32 _rc_U32_1627 = 0;
        (void)_rc_U32_1627;
        Bool hoisted__Bool_1662 = U32_lte(_rc_U32_1627, _re_U32_1627);
        (void)hoisted__Bool_1662;
        if (hoisted__Bool_1662) {
            while (1) {
                Bool _wcond_Bool_1628 = U32_lt(_rc_U32_1627, _re_U32_1627);
                (void)_wcond_Bool_1628;
                if (_wcond_Bool_1628) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1627);
                U32_inc(&_rc_U32_1627);
                U32 hoisted__U32_1629 = 16;
                (void)hoisted__U32_1629;
                U32 hoisted__U32_1630 = U32_mul(i, hoisted__U32_1629);
                (void)hoisted__U32_1630;
                Type *hoisted__Type_1631 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1631;
                U64 hoisted__U64_1632 = (U64)(hoisted__U32_1630);
                (void)hoisted__U64_1632;
                Type_delete(hoisted__Type_1631, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1632);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1633 = 16;
                (void)hoisted__U32_1633;
                U32 hoisted__U32_1634 = U32_mul(i, hoisted__U32_1633);
                (void)hoisted__U32_1634;
                Type *hoisted__Type_1635 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1635;
                U64 hoisted__U64_1636 = (U64)(hoisted__U32_1634);
                (void)hoisted__U64_1636;
                Type_delete(hoisted__Type_1635, 1);
                U32 hoisted__U32_1637 = 16;
                (void)hoisted__U32_1637;
                Type *hoisted__Type_1638 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1638;
                void *hoisted__v_1639 = ptr_add(new_data, hoisted__U64_1636);
                (void)hoisted__v_1639;
                (void)hoisted__v_1639;
                U64 hoisted__U64_1640 = (U64)(hoisted__U32_1637);
                (void)hoisted__U64_1640;
                Type_delete(hoisted__Type_1638, 1);
                memcpy(hoisted__v_1639, cloned, hoisted__U64_1640);
                U32 hoisted__U32_1641 = 16;
                (void)hoisted__U32_1641;
                Type *hoisted__Type_1642 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1642;
                I32 hoisted__I32_1643 = 0;
                (void)hoisted__I32_1643;
                U64 hoisted__U64_1644 = (U64)(hoisted__U32_1641);
                (void)hoisted__U64_1644;
                Type_delete(hoisted__Type_1642, 1);
                memset(cloned, hoisted__I32_1643, hoisted__U64_1644);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1645 = U32_gt(_rc_U32_1627, _re_U32_1627);
                (void)_wcond_Bool_1645;
                if (_wcond_Bool_1645) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1627);
                U32_dec(&_rc_U32_1627);
                U32 hoisted__U32_1646 = 16;
                (void)hoisted__U32_1646;
                U32 hoisted__U32_1647 = U32_mul(i, hoisted__U32_1646);
                (void)hoisted__U32_1647;
                Type *hoisted__Type_1648 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1648;
                U64 hoisted__U64_1649 = (U64)(hoisted__U32_1647);
                (void)hoisted__U64_1649;
                Type_delete(hoisted__Type_1648, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1649);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1650 = 16;
                (void)hoisted__U32_1650;
                U32 hoisted__U32_1651 = U32_mul(i, hoisted__U32_1650);
                (void)hoisted__U32_1651;
                Type *hoisted__Type_1652 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1652;
                U64 hoisted__U64_1653 = (U64)(hoisted__U32_1651);
                (void)hoisted__U64_1653;
                Type_delete(hoisted__Type_1652, 1);
                U32 hoisted__U32_1654 = 16;
                (void)hoisted__U32_1654;
                Type *hoisted__Type_1655 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1655;
                void *hoisted__v_1656 = ptr_add(new_data, hoisted__U64_1653);
                (void)hoisted__v_1656;
                (void)hoisted__v_1656;
                U64 hoisted__U64_1657 = (U64)(hoisted__U32_1654);
                (void)hoisted__U64_1657;
                Type_delete(hoisted__Type_1655, 1);
                memcpy(hoisted__v_1656, cloned, hoisted__U64_1657);
                U32 hoisted__U32_1658 = 16;
                (void)hoisted__U32_1658;
                Type *hoisted__Type_1659 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1659;
                I32 hoisted__I32_1660 = 0;
                (void)hoisted__I32_1660;
                U64 hoisted__U64_1661 = (U64)(hoisted__U32_1658);
                (void)hoisted__U64_1661;
                Type_delete(hoisted__Type_1659, 1);
                memset(cloned, hoisted__I32_1660, hoisted__U64_1661);
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1667 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1667->data = new_data;
    hoisted__Vec__Str_1667->count = self->count;
    hoisted__Vec__Str_1667->cap = self->cap;
    (void)hoisted__Vec__Str_1667;
    return hoisted__Vec__Str_1667;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1668 = 16;
    (void)hoisted__U32_1668;
    return hoisted__U32_1668;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1671 = 8;
    (void)hoisted__U32_1671;
    return hoisted__U32_1671;
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
    I64 hoisted__I64_1860 = 0;
    (void)hoisted__I64_1860;
    Bool hoisted__Bool_1861 = I64_eq(val, hoisted__I64_1860);
    (void)hoisted__Bool_1861;
    if (hoisted__Bool_1861) {
        U64 hoisted__U64_1830 = 2ULL;
        (void)hoisted__U64_1830;
        void * buf = malloc(hoisted__U64_1830);
        I64 hoisted__I64_1831 = 48;
        (void)hoisted__I64_1831;
        U64 hoisted__U64_1832 = 1ULL;
        (void)hoisted__U64_1832;
        memcpy(buf, &hoisted__I64_1831, hoisted__U64_1832);
        U64 hoisted__U64_1833 = 1ULL;
        (void)hoisted__U64_1833;
        void *hoisted__v_1834 = ptr_add(buf, hoisted__U64_1833);
        (void)hoisted__v_1834;
        (void)hoisted__v_1834;
        I32 hoisted__I32_1835 = 0;
        (void)hoisted__I32_1835;
        U64 hoisted__U64_1836 = 1ULL;
        (void)hoisted__U64_1836;
        memset(hoisted__v_1834, hoisted__I32_1835, hoisted__U64_1836);
        I64 hoisted__I64_1837 = 1;
        (void)hoisted__I64_1837;
        I64 hoisted__I64_1838 = 1;
        (void)hoisted__I64_1838;
        Str *hoisted__Str_1839 = malloc(sizeof(Str));
        hoisted__Str_1839->c_str = buf;
        hoisted__Str_1839->count = hoisted__I64_1837;
        hoisted__Str_1839->cap = hoisted__I64_1838;
        (void)hoisted__Str_1839;
        { Str * _ret_val = hoisted__Str_1839;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1862 = 0;
    (void)hoisted__I64_1862;
    Bool hoisted__Bool_1863 = I64_lt(val, hoisted__I64_1862);
    (void)hoisted__Bool_1863;
    if (hoisted__Bool_1863) {
        Bool hoisted__Bool_1840 = 1;
        (void)hoisted__Bool_1840;
        is_neg = hoisted__Bool_1840;
        I64 hoisted__I64_1841 = 0;
        (void)hoisted__I64_1841;
        I64 hoisted__I64_1842 = I64_sub(hoisted__I64_1841, val);
        (void)hoisted__I64_1842;
        v = hoisted__I64_1842;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1844 = 0;
        (void)hoisted__I64_1844;
        Bool _wcond_Bool_1843 = I64_gt(tmp, hoisted__I64_1844);
        (void)_wcond_Bool_1843;
        if (_wcond_Bool_1843) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1845 = 10;
        (void)hoisted__I64_1845;
        I64 hoisted__I64_1846 = I64_div(tmp, hoisted__I64_1845);
        (void)hoisted__I64_1846;
        tmp = hoisted__I64_1846;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1864 = 1ULL;
    (void)hoisted__U64_1864;
    U64 hoisted__U64_1865 = U64_add(total, hoisted__U64_1864);
    (void)hoisted__U64_1865;
    void * buf = malloc(hoisted__U64_1865);
    if (is_neg) {
        I64 hoisted__I64_1847 = 45;
        (void)hoisted__I64_1847;
        U64 hoisted__U64_1848 = 1ULL;
        (void)hoisted__U64_1848;
        memcpy(buf, &hoisted__I64_1847, hoisted__U64_1848);
    }
    U64 hoisted__U64_1866 = 1ULL;
    (void)hoisted__U64_1866;
    U64 i = U64_sub(total, hoisted__U64_1866);
    while (1) {
        I64 hoisted__I64_1850 = 0;
        (void)hoisted__I64_1850;
        Bool _wcond_Bool_1849 = I64_gt(v, hoisted__I64_1850);
        (void)_wcond_Bool_1849;
        if (_wcond_Bool_1849) {
        } else {
            break;
        }
        I64 hoisted__I64_1851 = 10;
        (void)hoisted__I64_1851;
        I64 hoisted__I64_1852 = I64_mod(v, hoisted__I64_1851);
        (void)hoisted__I64_1852;
        I64 hoisted__I64_1853 = 48;
        (void)hoisted__I64_1853;
        I64 hoisted__I64_1854 = I64_add(hoisted__I64_1852, hoisted__I64_1853);
        (void)hoisted__I64_1854;
        void *hoisted__v_1855 = ptr_add(buf, i);
        (void)hoisted__v_1855;
        (void)hoisted__v_1855;
        U8 hoisted__U8_1856 = I64_to_u8(hoisted__I64_1854);
        (void)hoisted__U8_1856;
        U64 hoisted__U64_1857 = 1ULL;
        (void)hoisted__U64_1857;
        memcpy(hoisted__v_1855, &hoisted__U8_1856, hoisted__U64_1857);
        I64 hoisted__I64_1858 = 10;
        (void)hoisted__I64_1858;
        I64 hoisted__I64_1859 = I64_div(v, hoisted__I64_1858);
        (void)hoisted__I64_1859;
        v = hoisted__I64_1859;
        U64_dec(&i);
    }
    void *hoisted__v_1867 = ptr_add(buf, total);
    (void)hoisted__v_1867;
    (void)hoisted__v_1867;
    I32 hoisted__I32_1868 = 0;
    (void)hoisted__I32_1868;
    U64 hoisted__U64_1869 = 1ULL;
    (void)hoisted__U64_1869;
    memset(hoisted__v_1867, hoisted__I32_1868, hoisted__U64_1869);
    Str *hoisted__Str_1870 = malloc(sizeof(Str));
    hoisted__Str_1870->c_str = buf;
    hoisted__Str_1870->count = total;
    hoisted__Str_1870->cap = total;
    (void)hoisted__Str_1870;
    return hoisted__Str_1870;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1890 = 8;
    (void)hoisted__U32_1890;
    return hoisted__U32_1890;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2011 = 0;
    (void)hoisted__U32_2011;
    U64 hoisted__U64_2012 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2011); });
    (void)hoisted__U64_2012;
    return hoisted__U64_2012;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2015 = I64_cmp(a, b);
    (void)hoisted__I64_2015;
    I64 hoisted__I64_2016 = -1;
    (void)hoisted__I64_2016;
    Bool hoisted__Bool_2017 = I64_eq(hoisted__I64_2015, hoisted__I64_2016);
    (void)hoisted__Bool_2017;
    return hoisted__Bool_2017;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2018 = I64_cmp(a, b);
    (void)hoisted__I64_2018;
    I64 hoisted__I64_2019 = 1;
    (void)hoisted__I64_2019;
    Bool hoisted__Bool_2020 = I64_eq(hoisted__I64_2018, hoisted__I64_2019);
    (void)hoisted__Bool_2020;
    return hoisted__Bool_2020;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2021 = I64_eq(a, b);
    (void)hoisted__Bool_2021;
    Bool hoisted__Bool_2022 = not(hoisted__Bool_2021);
    (void)hoisted__Bool_2022;
    return hoisted__Bool_2022;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2057 = 0;
    (void)_m_Bool_2057;
    {
        Bool hoisted__Bool_2060 = 1;
        (void)hoisted__Bool_2060;
        Bool hoisted__Bool_2061 = Bool_eq(a, hoisted__Bool_2060);
        (void)hoisted__Bool_2061;
        if (hoisted__Bool_2061) {
            Bool hoisted__Bool_2058 = Bool_clone(&b);
            (void)hoisted__Bool_2058;
            _m_Bool_2057 = hoisted__Bool_2058;
        } else {
            Bool hoisted__Bool_2059 = 0;
            (void)hoisted__Bool_2059;
            _m_Bool_2057 = hoisted__Bool_2059;
        }
    }
    return _m_Bool_2057;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2071 = Bool_eq(a, b);
    (void)hoisted__Bool_2071;
    if (hoisted__Bool_2071) {
        I64 hoisted__I64_2069 = 0;
        (void)hoisted__I64_2069;
        { I64 _ret_val = hoisted__I64_2069;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2070 = -1;
        (void)hoisted__I64_2070;
        return hoisted__I64_2070;
    }
    I64 hoisted__I64_2072 = 1;
    (void)hoisted__I64_2072;
    return hoisted__I64_2072;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2073 = 1;
    (void)hoisted__U32_2073;
    return hoisted__U32_2073;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2074 = 0;
    (void)hoisted__U32_2074;
    U64 hoisted__U64_2075 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2074); });
    (void)hoisted__U64_2075;
    return hoisted__U64_2075;
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
    Bool hoisted__Bool_2101 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2101;
    if (hoisted__Bool_2101) {
        Bool hoisted__Bool_2091 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2091;
        { Bool _ret_val = hoisted__Bool_2091;
                return _ret_val; }
    }
    Bool hoisted__Bool_2102 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2102;
    if (hoisted__Bool_2102) {
        Bool hoisted__Bool_2092 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2092;
        { Bool _ret_val = hoisted__Bool_2092;
                return _ret_val; }
    }
    Bool hoisted__Bool_2103 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2103;
    if (hoisted__Bool_2103) {
        Bool hoisted__Bool_2093 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2093;
        { Bool _ret_val = hoisted__Bool_2093;
                return _ret_val; }
    }
    Bool hoisted__Bool_2104 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2104;
    if (hoisted__Bool_2104) {
        Bool hoisted__Bool_2094 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2094;
        { Bool _ret_val = hoisted__Bool_2094;
                return _ret_val; }
    }
    Bool hoisted__Bool_2105 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2105;
    if (hoisted__Bool_2105) {
        Bool hoisted__Bool_2095 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2095;
        { Bool _ret_val = hoisted__Bool_2095;
                return _ret_val; }
    }
    Bool hoisted__Bool_2106 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2106;
    if (hoisted__Bool_2106) {
        Bool hoisted__Bool_2096 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2096;
        { Bool _ret_val = hoisted__Bool_2096;
                return _ret_val; }
    }
    Bool hoisted__Bool_2107 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2107;
    if (hoisted__Bool_2107) {
        Bool hoisted__Bool_2097 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2097;
        { Bool _ret_val = hoisted__Bool_2097;
                return _ret_val; }
    }
    Bool hoisted__Bool_2108 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2108;
    if (hoisted__Bool_2108) {
        Bool hoisted__Bool_2098 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2098;
        { Bool _ret_val = hoisted__Bool_2098;
                return _ret_val; }
    }
    Bool hoisted__Bool_2109 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2109;
    if (hoisted__Bool_2109) {
        Bool hoisted__Bool_2099 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2099;
        { Bool _ret_val = hoisted__Bool_2099;
                return _ret_val; }
    }
    Bool hoisted__Bool_2110 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2110;
    if (hoisted__Bool_2110) {
        Bool hoisted__Bool_2100 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2100;
        { Bool _ret_val = hoisted__Bool_2100;
                return _ret_val; }
    }
    Bool hoisted__Bool_2111 = 0;
    (void)hoisted__Bool_2111;
    return hoisted__Bool_2111;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2133 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2133;
    if (hoisted__Bool_2133) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2134 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2134;
    if (hoisted__Bool_2134) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2135 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2135;
    if (hoisted__Bool_2135) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2136 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2136;
    if (hoisted__Bool_2136) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2137 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2137;
    if (hoisted__Bool_2137) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2138 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2138;
    if (hoisted__Bool_2138) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2139 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2139;
    if (hoisted__Bool_2139) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2140 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2140;
    if (hoisted__Bool_2140) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2141 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2141;
    if (hoisted__Bool_2141) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2142 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2142;
    if (hoisted__Bool_2142) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2143 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2143;
    UNREACHABLE(&hoisted__Str_2143);
    Str_delete(&hoisted__Str_2143, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2144 = 4;
    (void)hoisted__U32_2144;
    return hoisted__U32_2144;
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
    Bool hoisted__Bool_2196 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2196;
    if (hoisted__Bool_2196) {
        Str *hoisted__Str_2186 = get_payload(self);
        (void)hoisted__Str_2186;
        (void)hoisted__Str_2186;
        Bool hoisted__Bool_2187 = 0;
        (void)hoisted__Bool_2187;
        Str_delete(hoisted__Str_2186, hoisted__Bool_2187);
    }
    Bool hoisted__Bool_2197 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2197;
    if (hoisted__Bool_2197) {
        Str *hoisted__Str_2188 = get_payload(self);
        (void)hoisted__Str_2188;
        (void)hoisted__Str_2188;
        Bool hoisted__Bool_2189 = 0;
        (void)hoisted__Bool_2189;
        Str_delete(hoisted__Str_2188, hoisted__Bool_2189);
    }
    Bool hoisted__Bool_2198 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2198;
    if (hoisted__Bool_2198) {
        Str *hoisted__Str_2190 = get_payload(self);
        (void)hoisted__Str_2190;
        (void)hoisted__Str_2190;
        Bool hoisted__Bool_2191 = 0;
        (void)hoisted__Bool_2191;
        Str_delete(hoisted__Str_2190, hoisted__Bool_2191);
    }
    Bool hoisted__Bool_2199 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2199;
    if (hoisted__Bool_2199) {
        Primitive *hoisted__Primitive_2192 = get_payload(self);
        (void)hoisted__Primitive_2192;
        (void)hoisted__Primitive_2192;
        Bool hoisted__Bool_2193 = 0;
        (void)hoisted__Bool_2193;
        Primitive_delete(hoisted__Primitive_2192, hoisted__Bool_2193);
    }
    Bool hoisted__Bool_2200 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2200;
    if (hoisted__Bool_2200) {
        Str *hoisted__Str_2194 = get_payload(self);
        (void)hoisted__Str_2194;
        (void)hoisted__Str_2194;
        Bool hoisted__Bool_2195 = 0;
        (void)hoisted__Bool_2195;
        Str_delete(hoisted__Str_2194, hoisted__Bool_2195);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2269 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2269;
    if (hoisted__Bool_2269) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2270 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2270;
    if (hoisted__Bool_2270) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2271 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2271;
    if (hoisted__Bool_2271) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2261 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2261;
        Type *hoisted__Type_2262 = Type_Struct(hoisted__Str_2261);
        (void)hoisted__Type_2262;
        { Type * _ret_val = hoisted__Type_2262;
                return _ret_val; }
    }
    Bool hoisted__Bool_2272 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2272;
    if (hoisted__Bool_2272) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2273 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2273;
    if (hoisted__Bool_2273) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2263 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2263;
        Type *hoisted__Type_2264 = Type_Enum(hoisted__Str_2263);
        (void)hoisted__Type_2264;
        { Type * _ret_val = hoisted__Type_2264;
                return _ret_val; }
    }
    Bool hoisted__Bool_2274 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2274;
    if (hoisted__Bool_2274) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2275 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2275;
    if (hoisted__Bool_2275) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2276 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2276;
    if (hoisted__Bool_2276) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2277 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2277;
    if (hoisted__Bool_2277) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2278 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2278;
    if (hoisted__Bool_2278) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2265 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2265;
        Type *hoisted__Type_2266 = Type_Custom(hoisted__Str_2265);
        (void)hoisted__Type_2266;
        { Type * _ret_val = hoisted__Type_2266;
                return _ret_val; }
    }
    Bool hoisted__Bool_2279 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2279;
    if (hoisted__Bool_2279) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2267 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2267;
        Type *hoisted__Type_2268 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2267; _oa; }));
        (void)hoisted__Type_2268;
        { Type * _ret_val = hoisted__Type_2268;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2280 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2280;
    Type *hoisted__Type_2281 = Type_FuncPtrSig(hoisted__Str_2280);
    (void)hoisted__Type_2281;
    return hoisted__Type_2281;
}

U32 Type_size(void) {
    U32 hoisted__U32_2282 = 24;
    (void)hoisted__U32_2282;
    return hoisted__U32_2282;
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
    Bool hoisted__Bool_2383 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2383;
    if (hoisted__Bool_2383) {
        Bool hoisted__Bool_2375 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2375;
        { Bool _ret_val = hoisted__Bool_2375;
                return _ret_val; }
    }
    Bool hoisted__Bool_2384 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2384;
    if (hoisted__Bool_2384) {
        Bool hoisted__Bool_2376 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2376;
        { Bool _ret_val = hoisted__Bool_2376;
                return _ret_val; }
    }
    Bool hoisted__Bool_2385 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2385;
    if (hoisted__Bool_2385) {
        Bool hoisted__Bool_2377 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2377;
        { Bool _ret_val = hoisted__Bool_2377;
                return _ret_val; }
    }
    Bool hoisted__Bool_2386 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2386;
    if (hoisted__Bool_2386) {
        Bool hoisted__Bool_2378 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2378;
        { Bool _ret_val = hoisted__Bool_2378;
                return _ret_val; }
    }
    Bool hoisted__Bool_2387 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2387;
    if (hoisted__Bool_2387) {
        Bool hoisted__Bool_2379 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2379;
        { Bool _ret_val = hoisted__Bool_2379;
                return _ret_val; }
    }
    Bool hoisted__Bool_2388 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2388;
    if (hoisted__Bool_2388) {
        Bool hoisted__Bool_2380 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2380;
        { Bool _ret_val = hoisted__Bool_2380;
                return _ret_val; }
    }
    Bool hoisted__Bool_2389 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2389;
    if (hoisted__Bool_2389) {
        Bool hoisted__Bool_2381 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2381;
        { Bool _ret_val = hoisted__Bool_2381;
                return _ret_val; }
    }
    Bool hoisted__Bool_2390 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2390;
    if (hoisted__Bool_2390) {
        Bool hoisted__Bool_2382 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2382;
        { Bool _ret_val = hoisted__Bool_2382;
                return _ret_val; }
    }
    Bool hoisted__Bool_2391 = 0;
    (void)hoisted__Bool_2391;
    return hoisted__Bool_2391;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2409 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2409;
    if (hoisted__Bool_2409) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2410 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2410;
    if (hoisted__Bool_2410) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2411 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2411;
    if (hoisted__Bool_2411) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2412 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2412;
    if (hoisted__Bool_2412) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2413 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2413;
    if (hoisted__Bool_2413) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2414 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2414;
    if (hoisted__Bool_2414) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2415 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2415;
    if (hoisted__Bool_2415) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2416 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2416;
    if (hoisted__Bool_2416) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2417 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2417;
    UNREACHABLE(&hoisted__Str_2417);
    Str_delete(&hoisted__Str_2417, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2418 = 4;
    (void)hoisted__U32_2418;
    return hoisted__U32_2418;
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
    Bool hoisted__Bool_2423 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2423;
    if (hoisted__Bool_2423) {
        Bool hoisted__Bool_2420 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2420;
        { Bool _ret_val = hoisted__Bool_2420;
                return _ret_val; }
    }
    Bool hoisted__Bool_2424 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2424;
    if (hoisted__Bool_2424) {
        Bool hoisted__Bool_2421 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2421;
        { Bool _ret_val = hoisted__Bool_2421;
                return _ret_val; }
    }
    Bool hoisted__Bool_2425 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2425;
    if (hoisted__Bool_2425) {
        Bool hoisted__Bool_2422 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2422;
        { Bool _ret_val = hoisted__Bool_2422;
                return _ret_val; }
    }
    Bool hoisted__Bool_2426 = 0;
    (void)hoisted__Bool_2426;
    return hoisted__Bool_2426;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2434 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2434;
    if (hoisted__Bool_2434) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2435 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2435;
    if (hoisted__Bool_2435) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2436 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2436;
    if (hoisted__Bool_2436) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2437 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2437;
    UNREACHABLE(&hoisted__Str_2437);
    Str_delete(&hoisted__Str_2437, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2438 = 4;
    (void)hoisted__U32_2438;
    return hoisted__U32_2438;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2440 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2440;
    Declaration *hoisted__Declaration_2441 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2441->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2441->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2441->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2441->is_mut = self->is_mut;
    hoisted__Declaration_2441->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2441->is_priv = self->is_priv;
    hoisted__Declaration_2441->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2441->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2441->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2441->default_value = hoisted__Expr_2440;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2441->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2441;
    return hoisted__Declaration_2441;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2442 = 0;
    (void)hoisted__Bool_2442;
    Str_delete(&self->name, hoisted__Bool_2442);
    Bool hoisted__Bool_2443 = 0;
    (void)hoisted__Bool_2443;
    Str_delete(&self->doc, hoisted__Bool_2443);
    Bool hoisted__Bool_2444 = 0;
    (void)hoisted__Bool_2444;
    Str_delete(&self->explicit_type, hoisted__Bool_2444);
    Bool hoisted__Bool_2445 = 0;
    (void)hoisted__Bool_2445;
    Bool_delete(&self->is_mut, hoisted__Bool_2445);
    Bool hoisted__Bool_2446 = 0;
    (void)hoisted__Bool_2446;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2446);
    Bool hoisted__Bool_2447 = 0;
    (void)hoisted__Bool_2447;
    Bool_delete(&self->is_priv, hoisted__Bool_2447);
    Bool hoisted__Bool_2448 = 0;
    (void)hoisted__Bool_2448;
    Bool_delete(&self->used, hoisted__Bool_2448);
    Bool hoisted__Bool_2449 = 0;
    (void)hoisted__Bool_2449;
    OwnType_delete(&self->own_type, hoisted__Bool_2449);
    Bool hoisted__Bool_2450 = 0;
    (void)hoisted__Bool_2450;
    Type_delete(&self->til_type, hoisted__Bool_2450);
    Bool hoisted__Bool_2451 = 1;
    (void)hoisted__Bool_2451;
    Expr_delete(self->default_value, hoisted__Bool_2451);
    Bool hoisted__Bool_2452 = 0;
    (void)hoisted__Bool_2452;
    Str_delete(&self->orig_name, hoisted__Bool_2452);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2453 = 104;
    (void)hoisted__U32_2453;
    return hoisted__U32_2453;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2455 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2455->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2455->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2455->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2455->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2455->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2455->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2455->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2455->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2455->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2455->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2455->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2455;
    return hoisted__FunctionDef_2455;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2456 = 0;
    (void)hoisted__Bool_2456;
    FuncType_delete(&self->func_type, hoisted__Bool_2456);
    Bool hoisted__Bool_2457 = 0;
    (void)hoisted__Bool_2457;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2457);
    Bool hoisted__Bool_2458 = 0;
    (void)hoisted__Bool_2458;
    Str_delete(&self->return_type, hoisted__Bool_2458);
    Bool hoisted__Bool_2459 = 0;
    (void)hoisted__Bool_2459;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2459);
    Bool hoisted__Bool_2460 = 0;
    (void)hoisted__Bool_2460;
    I32_delete(&self->variadic_index, hoisted__Bool_2460);
    Bool hoisted__Bool_2461 = 0;
    (void)hoisted__Bool_2461;
    I32_delete(&self->kwargs_index, hoisted__Bool_2461);
    Bool hoisted__Bool_2462 = 0;
    (void)hoisted__Bool_2462;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2462);
    Bool hoisted__Bool_2463 = 0;
    (void)hoisted__Bool_2463;
    Bool_delete(&self->auto_generated, hoisted__Bool_2463);
    Bool hoisted__Bool_2464 = 0;
    (void)hoisted__Bool_2464;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2464);
    Bool hoisted__Bool_2465 = 0;
    (void)hoisted__Bool_2465;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2465);
    Bool hoisted__Bool_2466 = 0;
    (void)hoisted__Bool_2466;
    Str_delete(&self->closure_name, hoisted__Bool_2466);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2467 = 0;
    (void)hoisted__U32_2467;
    U64 hoisted__U64_2468 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2467); });
    (void)hoisted__U64_2468;
    return hoisted__U64_2468;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2469 = 104;
    (void)hoisted__U32_2469;
    return hoisted__U32_2469;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2472 = malloc(sizeof(FCallData));
    hoisted__FCallData_2472->is_splat = self->is_splat;
    hoisted__FCallData_2472->does_throw = self->does_throw;
    hoisted__FCallData_2472->is_bang = self->is_bang;
    hoisted__FCallData_2472->own_args = self->own_args;
    hoisted__FCallData_2472->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2472->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2472;
    return hoisted__FCallData_2472;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2473 = 0;
    (void)hoisted__Bool_2473;
    Bool_delete(&self->is_splat, hoisted__Bool_2473);
    Bool hoisted__Bool_2474 = 0;
    (void)hoisted__Bool_2474;
    Bool_delete(&self->does_throw, hoisted__Bool_2474);
    Bool hoisted__Bool_2475 = 0;
    (void)hoisted__Bool_2475;
    Bool_delete(&self->is_bang, hoisted__Bool_2475);
    Bool hoisted__Bool_2476 = 0;
    (void)hoisted__Bool_2476;
    U64_delete(&self->own_args, hoisted__Bool_2476);
    Bool hoisted__Bool_2477 = 0;
    (void)hoisted__Bool_2477;
    Bool_delete(&self->swap_replace, hoisted__Bool_2477);
    Bool hoisted__Bool_2478 = 0;
    (void)hoisted__Bool_2478;
    Type_delete(&self->til_type, hoisted__Bool_2478);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2479 = 0;
    (void)hoisted__U32_2479;
    U64 hoisted__U64_2480 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2479); });
    (void)hoisted__U64_2480;
    return hoisted__U64_2480;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2481 = 48;
    (void)hoisted__U32_2481;
    return hoisted__U32_2481;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2493 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2493->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2493->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2493;
    return hoisted__LiteralNumData_2493;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2494 = 0;
    (void)hoisted__Bool_2494;
    Str_delete(&self->text, hoisted__Bool_2494);
    Bool hoisted__Bool_2495 = 0;
    (void)hoisted__Bool_2495;
    Type_delete(&self->til_type, hoisted__Bool_2495);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2496 = 0;
    (void)hoisted__U32_2496;
    U64 hoisted__U64_2497 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2496); });
    (void)hoisted__U64_2497;
    return hoisted__U64_2497;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2498 = 40;
    (void)hoisted__U32_2498;
    return hoisted__U32_2498;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2508 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2508->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2508->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2508;
    return hoisted__IdentData_2508;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2509 = 0;
    (void)hoisted__Bool_2509;
    Str_delete(&self->name, hoisted__Bool_2509);
    Bool hoisted__Bool_2510 = 0;
    (void)hoisted__Bool_2510;
    Type_delete(&self->til_type, hoisted__Bool_2510);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2511 = 0;
    (void)hoisted__U32_2511;
    U64 hoisted__U64_2512 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2511); });
    (void)hoisted__U64_2512;
    return hoisted__U64_2512;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2513 = 40;
    (void)hoisted__U32_2513;
    return hoisted__U32_2513;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2519 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2519->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2519->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2519;
    return hoisted__FieldAccessData_2519;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2520 = 0;
    (void)hoisted__Bool_2520;
    Str_delete(&self->name, hoisted__Bool_2520);
    Bool hoisted__Bool_2521 = 0;
    (void)hoisted__Bool_2521;
    Type_delete(&self->til_type, hoisted__Bool_2521);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2522 = 0;
    (void)hoisted__U32_2522;
    U64 hoisted__U64_2523 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2522); });
    (void)hoisted__U64_2523;
    return hoisted__U64_2523;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2524 = 40;
    (void)hoisted__U32_2524;
    return hoisted__U32_2524;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2599 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2599->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2599->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2599->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2599->is_interface = self->is_interface;
    hoisted__StructDef_2599->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2599->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2599;
    return hoisted__StructDef_2599;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2600 = 0;
    (void)hoisted__Bool_2600;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2600);
    Bool hoisted__Bool_2601 = 0;
    (void)hoisted__Bool_2601;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2601);
    Bool hoisted__Bool_2602 = 0;
    (void)hoisted__Bool_2602;
    Str_delete(&self->c_tag, hoisted__Bool_2602);
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Bool_delete(&self->is_interface, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    Str_delete(&self->implements_name, hoisted__Bool_2605);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2606 = 0;
    (void)hoisted__U32_2606;
    U64 hoisted__U64_2607 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2606); });
    (void)hoisted__U64_2607;
    return hoisted__U64_2607;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2608 = 72;
    (void)hoisted__U32_2608;
    return hoisted__U32_2608;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2613 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2613->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2613->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2613->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2613->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2613->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2613;
    return hoisted__EnumDef_2613;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2614 = 0;
    (void)hoisted__Bool_2614;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2614);
    Bool hoisted__Bool_2615 = 0;
    (void)hoisted__Bool_2615;
    Vec__Str_delete(&self->variants, hoisted__Bool_2615);
    Bool hoisted__Bool_2616 = 0;
    (void)hoisted__Bool_2616;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2616);
    Bool hoisted__Bool_2617 = 0;
    (void)hoisted__Bool_2617;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2617);
    Bool hoisted__Bool_2618 = 0;
    (void)hoisted__Bool_2618;
    Str_delete(&self->implements_name, hoisted__Bool_2618);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2619 = 0;
    (void)hoisted__U32_2619;
    U64 hoisted__U64_2620 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2619); });
    (void)hoisted__U64_2620;
    return hoisted__U64_2620;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2621 = 96;
    (void)hoisted__U32_2621;
    return hoisted__U32_2621;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2717 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2717->name = *_ca; free(_ca); }
    hoisted__AssignData_2717->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2717->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2717->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2717;
    return hoisted__AssignData_2717;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    Str_delete(&self->name, hoisted__Bool_2718);
    Bool hoisted__Bool_2719 = 0;
    (void)hoisted__Bool_2719;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2719);
    Bool hoisted__Bool_2720 = 0;
    (void)hoisted__Bool_2720;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2720);
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Bool_delete(&self->swap_replace, hoisted__Bool_2721);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2722 = 0;
    (void)hoisted__U32_2722;
    U64 hoisted__U64_2723 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2722); });
    (void)hoisted__U64_2723;
    return hoisted__U64_2723;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2724 = 24;
    (void)hoisted__U32_2724;
    return hoisted__U32_2724;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2726 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2726->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2726->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2726;
    return hoisted__FieldAssignData_2726;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2727 = 0;
    (void)hoisted__Bool_2727;
    Str_delete(&self->name, hoisted__Bool_2727);
    Bool hoisted__Bool_2728 = 0;
    (void)hoisted__Bool_2728;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2728);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2729 = 0;
    (void)hoisted__U32_2729;
    U64 hoisted__U64_2730 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2729); });
    (void)hoisted__U64_2730;
    return hoisted__U64_2730;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2731 = 24;
    (void)hoisted__U32_2731;
    return hoisted__U32_2731;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2733 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2733->name = *_ca; free(_ca); }
    hoisted__ForInData_2733->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2733->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2733;
    return hoisted__ForInData_2733;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2734 = 0;
    (void)hoisted__Bool_2734;
    Str_delete(&self->name, hoisted__Bool_2734);
    Bool hoisted__Bool_2735 = 0;
    (void)hoisted__Bool_2735;
    Bool_delete(&self->is_mut, hoisted__Bool_2735);
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    Type_delete(&self->til_type, hoisted__Bool_2736);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2737 = 0;
    (void)hoisted__U32_2737;
    U64 hoisted__U64_2738 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2737); });
    (void)hoisted__U64_2738;
    return hoisted__U64_2738;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2739 = 48;
    (void)hoisted__U32_2739;
    return hoisted__U32_2739;
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
    Bool hoisted__Bool_2769 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2769;
    if (hoisted__Bool_2769) {
        Str *hoisted__Str_2763 = get_payload(self);
        (void)hoisted__Str_2763;
        (void)hoisted__Str_2763;
        Bool hoisted__Bool_2764 = 0;
        (void)hoisted__Bool_2764;
        Str_delete(hoisted__Str_2763, hoisted__Bool_2764);
    }
    Bool hoisted__Bool_2770 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2770;
    if (hoisted__Bool_2770) {
        LiteralNumData *hoisted__LiteralNumData_2765 = get_payload(self);
        (void)hoisted__LiteralNumData_2765;
        (void)hoisted__LiteralNumData_2765;
        Bool hoisted__Bool_2766 = 0;
        (void)hoisted__Bool_2766;
        LiteralNumData_delete(hoisted__LiteralNumData_2765, hoisted__Bool_2766);
    }
    Bool hoisted__Bool_2771 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2771;
    if (hoisted__Bool_2771) {
        Bool *hoisted__Bool_2767 = get_payload(self);
        (void)hoisted__Bool_2767;
        (void)hoisted__Bool_2767;
        Bool hoisted__Bool_2768 = 0;
        (void)hoisted__Bool_2768;
        Bool_delete(hoisted__Bool_2767, hoisted__Bool_2768);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2811 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2811;
    if (hoisted__Bool_2811) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2806 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2806;
        Literal *hoisted__Literal_2807 = Literal_Str(hoisted__Str_2806);
        (void)hoisted__Literal_2807;
        { Literal * _ret_val = hoisted__Literal_2807;
                return _ret_val; }
    }
    Bool hoisted__Bool_2812 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2812;
    if (hoisted__Bool_2812) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2808 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2808;
        Literal *hoisted__Literal_2809 = Literal_Num(hoisted__LiteralNumData_2808);
        (void)hoisted__Literal_2809;
        { Literal * _ret_val = hoisted__Literal_2809;
                return _ret_val; }
    }
    Bool hoisted__Bool_2813 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2813;
    if (hoisted__Bool_2813) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2810 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2810;
        { Literal * _ret_val = hoisted__Literal_2810;
                return _ret_val; }
    }
    Bool hoisted__Bool_2814 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2814;
    if (hoisted__Bool_2814) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2815 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2815;
    if (hoisted__Bool_2815) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2816 = 48;
    (void)hoisted__U32_2816;
    return hoisted__U32_2816;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2819 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2819->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2819->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2819;
    return hoisted__MatchData_2819;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2820 = 0;
    (void)hoisted__Bool_2820;
    Type_delete(&self->til_type, hoisted__Bool_2820);
    Bool hoisted__Bool_2821 = 0;
    (void)hoisted__Bool_2821;
    Str_delete(&self->result_temp, hoisted__Bool_2821);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2822 = 0;
    (void)hoisted__U32_2822;
    U64 hoisted__U64_2823 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2822); });
    (void)hoisted__U64_2823;
    return hoisted__U64_2823;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2824 = 40;
    (void)hoisted__U32_2824;
    return hoisted__U32_2824;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2829 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2829->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2829;
    return hoisted__CaptureBlockData_2829;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2830 = 0;
    (void)hoisted__Bool_2830;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2830);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2831 = 0;
    (void)hoisted__U32_2831;
    U64 hoisted__U64_2832 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2831); });
    (void)hoisted__U64_2832;
    return hoisted__U64_2832;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2833 = 16;
    (void)hoisted__U32_2833;
    return hoisted__U32_2833;
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
    Bool hoisted__Bool_3012 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3012;
    if (hoisted__Bool_3012) {
        Literal *hoisted__Literal_2984 = get_payload(self);
        (void)hoisted__Literal_2984;
        (void)hoisted__Literal_2984;
        Bool hoisted__Bool_2985 = 0;
        (void)hoisted__Bool_2985;
        Literal_delete(hoisted__Literal_2984, hoisted__Bool_2985);
    }
    Bool hoisted__Bool_3013 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3013;
    if (hoisted__Bool_3013) {
        IdentData *hoisted__IdentData_2986 = get_payload(self);
        (void)hoisted__IdentData_2986;
        (void)hoisted__IdentData_2986;
        Bool hoisted__Bool_2987 = 0;
        (void)hoisted__Bool_2987;
        IdentData_delete(hoisted__IdentData_2986, hoisted__Bool_2987);
    }
    Bool hoisted__Bool_3014 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3014;
    if (hoisted__Bool_3014) {
        Declaration *hoisted__Declaration_2988 = get_payload(self);
        (void)hoisted__Declaration_2988;
        (void)hoisted__Declaration_2988;
        Bool hoisted__Bool_2989 = 0;
        (void)hoisted__Bool_2989;
        Declaration_delete(hoisted__Declaration_2988, hoisted__Bool_2989);
    }
    Bool hoisted__Bool_3015 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3015;
    if (hoisted__Bool_3015) {
        AssignData *hoisted__AssignData_2990 = get_payload(self);
        (void)hoisted__AssignData_2990;
        (void)hoisted__AssignData_2990;
        Bool hoisted__Bool_2991 = 0;
        (void)hoisted__Bool_2991;
        AssignData_delete(hoisted__AssignData_2990, hoisted__Bool_2991);
    }
    Bool hoisted__Bool_3016 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3016;
    if (hoisted__Bool_3016) {
        FCallData *hoisted__FCallData_2992 = get_payload(self);
        (void)hoisted__FCallData_2992;
        (void)hoisted__FCallData_2992;
        Bool hoisted__Bool_2993 = 0;
        (void)hoisted__Bool_2993;
        FCallData_delete(hoisted__FCallData_2992, hoisted__Bool_2993);
    }
    Bool hoisted__Bool_3017 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3017;
    if (hoisted__Bool_3017) {
        FunctionDef *hoisted__FunctionDef_2994 = get_payload(self);
        (void)hoisted__FunctionDef_2994;
        (void)hoisted__FunctionDef_2994;
        Bool hoisted__Bool_2995 = 0;
        (void)hoisted__Bool_2995;
        FunctionDef_delete(hoisted__FunctionDef_2994, hoisted__Bool_2995);
    }
    Bool hoisted__Bool_3018 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3018;
    if (hoisted__Bool_3018) {
        StructDef *hoisted__StructDef_2996 = get_payload(self);
        (void)hoisted__StructDef_2996;
        (void)hoisted__StructDef_2996;
        Bool hoisted__Bool_2997 = 0;
        (void)hoisted__Bool_2997;
        StructDef_delete(hoisted__StructDef_2996, hoisted__Bool_2997);
    }
    Bool hoisted__Bool_3019 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3019;
    if (hoisted__Bool_3019) {
        EnumDef *hoisted__EnumDef_2998 = get_payload(self);
        (void)hoisted__EnumDef_2998;
        (void)hoisted__EnumDef_2998;
        Bool hoisted__Bool_2999 = 0;
        (void)hoisted__Bool_2999;
        EnumDef_delete(hoisted__EnumDef_2998, hoisted__Bool_2999);
    }
    Bool hoisted__Bool_3020 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3020;
    if (hoisted__Bool_3020) {
        FieldAccessData *hoisted__FieldAccessData_3000 = get_payload(self);
        (void)hoisted__FieldAccessData_3000;
        (void)hoisted__FieldAccessData_3000;
        Bool hoisted__Bool_3001 = 0;
        (void)hoisted__Bool_3001;
        FieldAccessData_delete(hoisted__FieldAccessData_3000, hoisted__Bool_3001);
    }
    Bool hoisted__Bool_3021 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3021;
    if (hoisted__Bool_3021) {
        FieldAssignData *hoisted__FieldAssignData_3002 = get_payload(self);
        (void)hoisted__FieldAssignData_3002;
        (void)hoisted__FieldAssignData_3002;
        Bool hoisted__Bool_3003 = 0;
        (void)hoisted__Bool_3003;
        FieldAssignData_delete(hoisted__FieldAssignData_3002, hoisted__Bool_3003);
    }
    Bool hoisted__Bool_3022 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3022;
    if (hoisted__Bool_3022) {
        ForInData *hoisted__ForInData_3004 = get_payload(self);
        (void)hoisted__ForInData_3004;
        (void)hoisted__ForInData_3004;
        Bool hoisted__Bool_3005 = 0;
        (void)hoisted__Bool_3005;
        ForInData_delete(hoisted__ForInData_3004, hoisted__Bool_3005);
    }
    Bool hoisted__Bool_3023 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3023;
    if (hoisted__Bool_3023) {
        Str *hoisted__Str_3006 = get_payload(self);
        (void)hoisted__Str_3006;
        (void)hoisted__Str_3006;
        Bool hoisted__Bool_3007 = 0;
        (void)hoisted__Bool_3007;
        Str_delete(hoisted__Str_3006, hoisted__Bool_3007);
    }
    Bool hoisted__Bool_3024 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3024;
    if (hoisted__Bool_3024) {
        MatchData *hoisted__MatchData_3008 = get_payload(self);
        (void)hoisted__MatchData_3008;
        (void)hoisted__MatchData_3008;
        Bool hoisted__Bool_3009 = 0;
        (void)hoisted__Bool_3009;
        MatchData_delete(hoisted__MatchData_3008, hoisted__Bool_3009);
    }
    Bool hoisted__Bool_3025 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3025;
    if (hoisted__Bool_3025) {
        CaptureBlockData *hoisted__CaptureBlockData_3010 = get_payload(self);
        (void)hoisted__CaptureBlockData_3010;
        (void)hoisted__CaptureBlockData_3010;
        Bool hoisted__Bool_3011 = 0;
        (void)hoisted__Bool_3011;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3010, hoisted__Bool_3011);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3207 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3207;
    if (hoisted__Bool_3207) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3208 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3208;
    if (hoisted__Bool_3208) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3179 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3179;
        NodeType *hoisted__NodeType_3180 = NodeType_Literal(hoisted__Literal_3179);
        (void)hoisted__NodeType_3180;
        { NodeType * _ret_val = hoisted__NodeType_3180;
                return _ret_val; }
    }
    Bool hoisted__Bool_3209 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3209;
    if (hoisted__Bool_3209) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3181 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3181;
        NodeType *hoisted__NodeType_3182 = NodeType_Ident(hoisted__IdentData_3181);
        (void)hoisted__NodeType_3182;
        { NodeType * _ret_val = hoisted__NodeType_3182;
                return _ret_val; }
    }
    Bool hoisted__Bool_3210 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3210;
    if (hoisted__Bool_3210) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3183 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3183;
        NodeType *hoisted__NodeType_3184 = NodeType_Decl(hoisted__Declaration_3183);
        (void)hoisted__NodeType_3184;
        { NodeType * _ret_val = hoisted__NodeType_3184;
                return _ret_val; }
    }
    Bool hoisted__Bool_3211 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3211;
    if (hoisted__Bool_3211) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3185 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3185;
        NodeType *hoisted__NodeType_3186 = NodeType_Assign(hoisted__AssignData_3185);
        (void)hoisted__NodeType_3186;
        { NodeType * _ret_val = hoisted__NodeType_3186;
                return _ret_val; }
    }
    Bool hoisted__Bool_3212 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3212;
    if (hoisted__Bool_3212) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3187 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3187;
        NodeType *hoisted__NodeType_3188 = NodeType_FCall(hoisted__FCallData_3187);
        (void)hoisted__NodeType_3188;
        { NodeType * _ret_val = hoisted__NodeType_3188;
                return _ret_val; }
    }
    Bool hoisted__Bool_3213 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3213;
    if (hoisted__Bool_3213) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3189 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3189;
        NodeType *hoisted__NodeType_3190 = NodeType_FuncDef(hoisted__FunctionDef_3189);
        (void)hoisted__NodeType_3190;
        { NodeType * _ret_val = hoisted__NodeType_3190;
                return _ret_val; }
    }
    Bool hoisted__Bool_3214 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3214;
    if (hoisted__Bool_3214) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3191 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3191;
        NodeType *hoisted__NodeType_3192 = NodeType_StructDef(hoisted__StructDef_3191);
        (void)hoisted__NodeType_3192;
        { NodeType * _ret_val = hoisted__NodeType_3192;
                return _ret_val; }
    }
    Bool hoisted__Bool_3215 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3215;
    if (hoisted__Bool_3215) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3193 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3193;
        NodeType *hoisted__NodeType_3194 = NodeType_EnumDef(hoisted__EnumDef_3193);
        (void)hoisted__NodeType_3194;
        { NodeType * _ret_val = hoisted__NodeType_3194;
                return _ret_val; }
    }
    Bool hoisted__Bool_3216 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3216;
    if (hoisted__Bool_3216) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3195 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3195;
        NodeType *hoisted__NodeType_3196 = NodeType_FieldAccess(hoisted__FieldAccessData_3195);
        (void)hoisted__NodeType_3196;
        { NodeType * _ret_val = hoisted__NodeType_3196;
                return _ret_val; }
    }
    Bool hoisted__Bool_3217 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3217;
    if (hoisted__Bool_3217) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3197 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3197;
        NodeType *hoisted__NodeType_3198 = NodeType_FieldAssign(hoisted__FieldAssignData_3197);
        (void)hoisted__NodeType_3198;
        { NodeType * _ret_val = hoisted__NodeType_3198;
                return _ret_val; }
    }
    Bool hoisted__Bool_3218 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3218;
    if (hoisted__Bool_3218) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3219 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3219;
    if (hoisted__Bool_3219) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3220 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3220;
    if (hoisted__Bool_3220) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3221 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3221;
    if (hoisted__Bool_3221) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3199 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3199;
        NodeType *hoisted__NodeType_3200 = NodeType_ForIn(hoisted__ForInData_3199);
        (void)hoisted__NodeType_3200;
        { NodeType * _ret_val = hoisted__NodeType_3200;
                return _ret_val; }
    }
    Bool hoisted__Bool_3222 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3222;
    if (hoisted__Bool_3222) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3201 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3201;
        NodeType *hoisted__NodeType_3202 = NodeType_NamedArg(hoisted__Str_3201);
        (void)hoisted__NodeType_3202;
        { NodeType * _ret_val = hoisted__NodeType_3202;
                return _ret_val; }
    }
    Bool hoisted__Bool_3223 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3223;
    if (hoisted__Bool_3223) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3224 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3224;
    if (hoisted__Bool_3224) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3225 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3225;
    if (hoisted__Bool_3225) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3226 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3226;
    if (hoisted__Bool_3226) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3203 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3203;
        NodeType *hoisted__NodeType_3204 = NodeType_Match(hoisted__MatchData_3203);
        (void)hoisted__NodeType_3204;
        { NodeType * _ret_val = hoisted__NodeType_3204;
                return _ret_val; }
    }
    Bool hoisted__Bool_3227 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3227;
    if (hoisted__Bool_3227) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3228 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3228;
    if (hoisted__Bool_3228) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3229 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3229;
    if (hoisted__Bool_3229) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3230 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3230;
    if (hoisted__Bool_3230) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3231 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3231;
    if (hoisted__Bool_3231) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3232 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3232;
    if (hoisted__Bool_3232) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3205 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3205;
        NodeType *hoisted__NodeType_3206 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3205);
        (void)hoisted__NodeType_3206;
        { NodeType * _ret_val = hoisted__NodeType_3206;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3233 = 112;
    (void)hoisted__U32_3233;
    return hoisted__U32_3233;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3234 = is_null(self);
    (void)hoisted__Bool_3234;
    if (hoisted__Bool_3234) {
        return;
    }
    Bool hoisted__Bool_3235 = 0;
    (void)hoisted__Bool_3235;
    NodeType_delete(&self->node_type, hoisted__Bool_3235);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3279 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3279->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3279->children = *_ca; free(_ca); }
    hoisted__Expr_3279->line = line;
    hoisted__Expr_3279->col = col;
    (void)hoisted__Expr_3279;
    return hoisted__Expr_3279;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3287 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3287->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3287->children = *_ca; free(_ca); }
    hoisted__Expr_3287->line = self->line;
    hoisted__Expr_3287->col = self->col;
    (void)hoisted__Expr_3287;
    return hoisted__Expr_3287;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3288 = 0;
    (void)hoisted__U32_3288;
    U64 hoisted__U64_3289 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3288); });
    (void)hoisted__U64_3289;
    return hoisted__U64_3289;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3290 = 136;
    (void)hoisted__U32_3290;
    return hoisted__U32_3290;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_3926 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_3926->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_3926->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3926;
    return hoisted__Map__I64_Str_3926;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4071 = 0;
    (void)hoisted__Bool_4071;
    Vec__I64_delete(&self->keys, hoisted__Bool_4071);
    Bool hoisted__Bool_4072 = 0;
    (void)hoisted__Bool_4072;
    Vec__Str_delete(&self->values, hoisted__Bool_4072);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4073 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4073->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4073->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4073;
    return hoisted__Map__I64_Str_4073;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4074 = 0;
    (void)hoisted__U32_4074;
    U64 hoisted__U64_4075 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4074); });
    (void)hoisted__U64_4075;
    return hoisted__U64_4075;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4076 = 32;
    (void)hoisted__U32_4076;
    return hoisted__U32_4076;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4077 = 1;
    (void)hoisted__U32_4077;
    Type *hoisted__Type_4078 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4078;
    U64 hoisted__U64_4079 = (U64)(hoisted__U32_4077);
    (void)hoisted__U64_4079;
    Type_delete(hoisted__Type_4078, 1);
    void * hoisted__v_4080 = malloc(hoisted__U64_4079);
    (void)hoisted__v_4080;
    U32 hoisted__U32_4081 = 0;
    (void)hoisted__U32_4081;
    I64 hoisted__I64_4082 = 1;
    (void)hoisted__I64_4082;
    Vec__Bool *hoisted__Vec__Bool_4083 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4083->data = hoisted__v_4080;
    hoisted__Vec__Bool_4083->count = hoisted__U32_4081;
    hoisted__Vec__Bool_4083->cap = hoisted__I64_4082;
    (void)hoisted__Vec__Bool_4083;
    return hoisted__Vec__Bool_4083;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4084 = self->count;
        (void)_re_U32_4084;
        U32 _rc_U32_4084 = 0;
        (void)_rc_U32_4084;
        Bool hoisted__Bool_4099 = U32_lte(_rc_U32_4084, _re_U32_4084);
        (void)hoisted__Bool_4099;
        if (hoisted__Bool_4099) {
            while (1) {
                Bool _wcond_Bool_4085 = U32_lt(_rc_U32_4084, _re_U32_4084);
                (void)_wcond_Bool_4085;
                if (_wcond_Bool_4085) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4084);
                U32_inc(&_rc_U32_4084);
                U32 hoisted__U32_4086 = 1;
                (void)hoisted__U32_4086;
                U32 hoisted__U32_4087 = U32_mul(i, hoisted__U32_4086);
                (void)hoisted__U32_4087;
                Type *hoisted__Type_4088 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4088;
                U64 hoisted__U64_4089 = (U64)(hoisted__U32_4087);
                (void)hoisted__U64_4089;
                Type_delete(hoisted__Type_4088, 1);
                Bool *hoisted__Bool_4090 = ptr_add(self->data, hoisted__U64_4089);
                (void)hoisted__Bool_4090;
                (void)hoisted__Bool_4090;
                Bool hoisted__Bool_4091 = 0;
                (void)hoisted__Bool_4091;
                Bool_delete(hoisted__Bool_4090, hoisted__Bool_4091);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4092 = U32_gt(_rc_U32_4084, _re_U32_4084);
                (void)_wcond_Bool_4092;
                if (_wcond_Bool_4092) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4084);
                U32_dec(&_rc_U32_4084);
                U32 hoisted__U32_4093 = 1;
                (void)hoisted__U32_4093;
                U32 hoisted__U32_4094 = U32_mul(i, hoisted__U32_4093);
                (void)hoisted__U32_4094;
                Type *hoisted__Type_4095 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4095;
                U64 hoisted__U64_4096 = (U64)(hoisted__U32_4094);
                (void)hoisted__U64_4096;
                Type_delete(hoisted__Type_4095, 1);
                Bool *hoisted__Bool_4097 = ptr_add(self->data, hoisted__U64_4096);
                (void)hoisted__Bool_4097;
                (void)hoisted__Bool_4097;
                Bool hoisted__Bool_4098 = 0;
                (void)hoisted__Bool_4098;
                Bool_delete(hoisted__Bool_4097, hoisted__Bool_4098);
            }
        }
    }
    U32 hoisted__U32_4100 = 0;
    (void)hoisted__U32_4100;
    self->count = hoisted__U32_4100;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4393 = 1;
    (void)hoisted__U32_4393;
    U32 hoisted__U32_4394 = U32_mul(self->cap, hoisted__U32_4393);
    (void)hoisted__U32_4394;
    Type *hoisted__Type_4395 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4395;
    U64 hoisted__U64_4396 = (U64)(hoisted__U32_4394);
    (void)hoisted__U64_4396;
    Type_delete(hoisted__Type_4395, 1);
    void * new_data = malloc(hoisted__U64_4396);
    {
        U32 _re_U32_4357 = self->count;
        (void)_re_U32_4357;
        U32 _rc_U32_4357 = 0;
        (void)_rc_U32_4357;
        Bool hoisted__Bool_4392 = U32_lte(_rc_U32_4357, _re_U32_4357);
        (void)hoisted__Bool_4392;
        if (hoisted__Bool_4392) {
            while (1) {
                Bool _wcond_Bool_4358 = U32_lt(_rc_U32_4357, _re_U32_4357);
                (void)_wcond_Bool_4358;
                if (_wcond_Bool_4358) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4357);
                U32_inc(&_rc_U32_4357);
                U32 hoisted__U32_4359 = 1;
                (void)hoisted__U32_4359;
                U32 hoisted__U32_4360 = U32_mul(i, hoisted__U32_4359);
                (void)hoisted__U32_4360;
                Type *hoisted__Type_4361 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4361;
                U64 hoisted__U64_4362 = (U64)(hoisted__U32_4360);
                (void)hoisted__U64_4362;
                Type_delete(hoisted__Type_4361, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4362);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4363 = 1;
                (void)hoisted__U32_4363;
                U32 hoisted__U32_4364 = U32_mul(i, hoisted__U32_4363);
                (void)hoisted__U32_4364;
                Type *hoisted__Type_4365 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4365;
                U64 hoisted__U64_4366 = (U64)(hoisted__U32_4364);
                (void)hoisted__U64_4366;
                Type_delete(hoisted__Type_4365, 1);
                U32 hoisted__U32_4367 = 1;
                (void)hoisted__U32_4367;
                Type *hoisted__Type_4368 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4368;
                void *hoisted__v_4369 = ptr_add(new_data, hoisted__U64_4366);
                (void)hoisted__v_4369;
                (void)hoisted__v_4369;
                U64 hoisted__U64_4370 = (U64)(hoisted__U32_4367);
                (void)hoisted__U64_4370;
                Type_delete(hoisted__Type_4368, 1);
                memcpy(hoisted__v_4369, &cloned, hoisted__U64_4370);
                U32 hoisted__U32_4371 = 1;
                (void)hoisted__U32_4371;
                Type *hoisted__Type_4372 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4372;
                I32 hoisted__I32_4373 = 0;
                (void)hoisted__I32_4373;
                U64 hoisted__U64_4374 = (U64)(hoisted__U32_4371);
                (void)hoisted__U64_4374;
                Type_delete(hoisted__Type_4372, 1);
                memset(&cloned, hoisted__I32_4373, hoisted__U64_4374);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4375 = U32_gt(_rc_U32_4357, _re_U32_4357);
                (void)_wcond_Bool_4375;
                if (_wcond_Bool_4375) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4357);
                U32_dec(&_rc_U32_4357);
                U32 hoisted__U32_4376 = 1;
                (void)hoisted__U32_4376;
                U32 hoisted__U32_4377 = U32_mul(i, hoisted__U32_4376);
                (void)hoisted__U32_4377;
                Type *hoisted__Type_4378 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4378;
                U64 hoisted__U64_4379 = (U64)(hoisted__U32_4377);
                (void)hoisted__U64_4379;
                Type_delete(hoisted__Type_4378, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4379);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4380 = 1;
                (void)hoisted__U32_4380;
                U32 hoisted__U32_4381 = U32_mul(i, hoisted__U32_4380);
                (void)hoisted__U32_4381;
                Type *hoisted__Type_4382 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4382;
                U64 hoisted__U64_4383 = (U64)(hoisted__U32_4381);
                (void)hoisted__U64_4383;
                Type_delete(hoisted__Type_4382, 1);
                U32 hoisted__U32_4384 = 1;
                (void)hoisted__U32_4384;
                Type *hoisted__Type_4385 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4385;
                void *hoisted__v_4386 = ptr_add(new_data, hoisted__U64_4383);
                (void)hoisted__v_4386;
                (void)hoisted__v_4386;
                U64 hoisted__U64_4387 = (U64)(hoisted__U32_4384);
                (void)hoisted__U64_4387;
                Type_delete(hoisted__Type_4385, 1);
                memcpy(hoisted__v_4386, &cloned, hoisted__U64_4387);
                U32 hoisted__U32_4388 = 1;
                (void)hoisted__U32_4388;
                Type *hoisted__Type_4389 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4389;
                I32 hoisted__I32_4390 = 0;
                (void)hoisted__I32_4390;
                U64 hoisted__U64_4391 = (U64)(hoisted__U32_4388);
                (void)hoisted__U64_4391;
                Type_delete(hoisted__Type_4389, 1);
                memset(&cloned, hoisted__I32_4390, hoisted__U64_4391);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4397 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4397->data = new_data;
    hoisted__Vec__Bool_4397->count = self->count;
    hoisted__Vec__Bool_4397->cap = self->cap;
    (void)hoisted__Vec__Bool_4397;
    return hoisted__Vec__Bool_4397;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4398 = 16;
    (void)hoisted__U32_4398;
    return hoisted__U32_4398;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_4721 = 104;
    (void)hoisted__U32_4721;
    Type *hoisted__Type_4722 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4722;
    U64 hoisted__U64_4723 = (U64)(hoisted__U32_4721);
    (void)hoisted__U64_4723;
    Type_delete(hoisted__Type_4722, 1);
    void * hoisted__v_4724 = malloc(hoisted__U64_4723);
    (void)hoisted__v_4724;
    U32 hoisted__U32_4725 = 0;
    (void)hoisted__U32_4725;
    I64 hoisted__I64_4726 = 1;
    (void)hoisted__I64_4726;
    Vec__Declaration *hoisted__Vec__Declaration_4727 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4727->data = hoisted__v_4724;
    hoisted__Vec__Declaration_4727->count = hoisted__U32_4725;
    hoisted__Vec__Declaration_4727->cap = hoisted__I64_4726;
    (void)hoisted__Vec__Declaration_4727;
    return hoisted__Vec__Declaration_4727;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4728 = self->count;
        (void)_re_U32_4728;
        U32 _rc_U32_4728 = 0;
        (void)_rc_U32_4728;
        Bool hoisted__Bool_4743 = U32_lte(_rc_U32_4728, _re_U32_4728);
        (void)hoisted__Bool_4743;
        if (hoisted__Bool_4743) {
            while (1) {
                Bool _wcond_Bool_4729 = U32_lt(_rc_U32_4728, _re_U32_4728);
                (void)_wcond_Bool_4729;
                if (_wcond_Bool_4729) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4728);
                U32_inc(&_rc_U32_4728);
                U32 hoisted__U32_4730 = 104;
                (void)hoisted__U32_4730;
                U32 hoisted__U32_4731 = U32_mul(i, hoisted__U32_4730);
                (void)hoisted__U32_4731;
                Type *hoisted__Type_4732 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4732;
                U64 hoisted__U64_4733 = (U64)(hoisted__U32_4731);
                (void)hoisted__U64_4733;
                Type_delete(hoisted__Type_4732, 1);
                Declaration *hoisted__Declaration_4734 = ptr_add(self->data, hoisted__U64_4733);
                (void)hoisted__Declaration_4734;
                (void)hoisted__Declaration_4734;
                Bool hoisted__Bool_4735 = 0;
                (void)hoisted__Bool_4735;
                Declaration_delete(hoisted__Declaration_4734, hoisted__Bool_4735);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4736 = U32_gt(_rc_U32_4728, _re_U32_4728);
                (void)_wcond_Bool_4736;
                if (_wcond_Bool_4736) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4728);
                U32_dec(&_rc_U32_4728);
                U32 hoisted__U32_4737 = 104;
                (void)hoisted__U32_4737;
                U32 hoisted__U32_4738 = U32_mul(i, hoisted__U32_4737);
                (void)hoisted__U32_4738;
                Type *hoisted__Type_4739 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4739;
                U64 hoisted__U64_4740 = (U64)(hoisted__U32_4738);
                (void)hoisted__U64_4740;
                Type_delete(hoisted__Type_4739, 1);
                Declaration *hoisted__Declaration_4741 = ptr_add(self->data, hoisted__U64_4740);
                (void)hoisted__Declaration_4741;
                (void)hoisted__Declaration_4741;
                Bool hoisted__Bool_4742 = 0;
                (void)hoisted__Bool_4742;
                Declaration_delete(hoisted__Declaration_4741, hoisted__Bool_4742);
            }
        }
    }
    U32 hoisted__U32_4744 = 0;
    (void)hoisted__U32_4744;
    self->count = hoisted__U32_4744;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5037 = 104;
    (void)hoisted__U32_5037;
    U32 hoisted__U32_5038 = U32_mul(self->cap, hoisted__U32_5037);
    (void)hoisted__U32_5038;
    Type *hoisted__Type_5039 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5039;
    U64 hoisted__U64_5040 = (U64)(hoisted__U32_5038);
    (void)hoisted__U64_5040;
    Type_delete(hoisted__Type_5039, 1);
    void * new_data = malloc(hoisted__U64_5040);
    {
        U32 _re_U32_5001 = self->count;
        (void)_re_U32_5001;
        U32 _rc_U32_5001 = 0;
        (void)_rc_U32_5001;
        Bool hoisted__Bool_5036 = U32_lte(_rc_U32_5001, _re_U32_5001);
        (void)hoisted__Bool_5036;
        if (hoisted__Bool_5036) {
            while (1) {
                Bool _wcond_Bool_5002 = U32_lt(_rc_U32_5001, _re_U32_5001);
                (void)_wcond_Bool_5002;
                if (_wcond_Bool_5002) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5001);
                U32_inc(&_rc_U32_5001);
                U32 hoisted__U32_5003 = 104;
                (void)hoisted__U32_5003;
                U32 hoisted__U32_5004 = U32_mul(i, hoisted__U32_5003);
                (void)hoisted__U32_5004;
                Type *hoisted__Type_5005 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5005;
                U64 hoisted__U64_5006 = (U64)(hoisted__U32_5004);
                (void)hoisted__U64_5006;
                Type_delete(hoisted__Type_5005, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5006);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5007 = 104;
                (void)hoisted__U32_5007;
                U32 hoisted__U32_5008 = U32_mul(i, hoisted__U32_5007);
                (void)hoisted__U32_5008;
                Type *hoisted__Type_5009 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5009;
                U64 hoisted__U64_5010 = (U64)(hoisted__U32_5008);
                (void)hoisted__U64_5010;
                Type_delete(hoisted__Type_5009, 1);
                U32 hoisted__U32_5011 = 104;
                (void)hoisted__U32_5011;
                Type *hoisted__Type_5012 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5012;
                void *hoisted__v_5013 = ptr_add(new_data, hoisted__U64_5010);
                (void)hoisted__v_5013;
                (void)hoisted__v_5013;
                U64 hoisted__U64_5014 = (U64)(hoisted__U32_5011);
                (void)hoisted__U64_5014;
                Type_delete(hoisted__Type_5012, 1);
                memcpy(hoisted__v_5013, cloned, hoisted__U64_5014);
                U32 hoisted__U32_5015 = 104;
                (void)hoisted__U32_5015;
                Type *hoisted__Type_5016 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5016;
                I32 hoisted__I32_5017 = 0;
                (void)hoisted__I32_5017;
                U64 hoisted__U64_5018 = (U64)(hoisted__U32_5015);
                (void)hoisted__U64_5018;
                Type_delete(hoisted__Type_5016, 1);
                memset(cloned, hoisted__I32_5017, hoisted__U64_5018);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5019 = U32_gt(_rc_U32_5001, _re_U32_5001);
                (void)_wcond_Bool_5019;
                if (_wcond_Bool_5019) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5001);
                U32_dec(&_rc_U32_5001);
                U32 hoisted__U32_5020 = 104;
                (void)hoisted__U32_5020;
                U32 hoisted__U32_5021 = U32_mul(i, hoisted__U32_5020);
                (void)hoisted__U32_5021;
                Type *hoisted__Type_5022 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5022;
                U64 hoisted__U64_5023 = (U64)(hoisted__U32_5021);
                (void)hoisted__U64_5023;
                Type_delete(hoisted__Type_5022, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5023);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5024 = 104;
                (void)hoisted__U32_5024;
                U32 hoisted__U32_5025 = U32_mul(i, hoisted__U32_5024);
                (void)hoisted__U32_5025;
                Type *hoisted__Type_5026 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5026;
                U64 hoisted__U64_5027 = (U64)(hoisted__U32_5025);
                (void)hoisted__U64_5027;
                Type_delete(hoisted__Type_5026, 1);
                U32 hoisted__U32_5028 = 104;
                (void)hoisted__U32_5028;
                Type *hoisted__Type_5029 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5029;
                void *hoisted__v_5030 = ptr_add(new_data, hoisted__U64_5027);
                (void)hoisted__v_5030;
                (void)hoisted__v_5030;
                U64 hoisted__U64_5031 = (U64)(hoisted__U32_5028);
                (void)hoisted__U64_5031;
                Type_delete(hoisted__Type_5029, 1);
                memcpy(hoisted__v_5030, cloned, hoisted__U64_5031);
                U32 hoisted__U32_5032 = 104;
                (void)hoisted__U32_5032;
                Type *hoisted__Type_5033 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5033;
                I32 hoisted__I32_5034 = 0;
                (void)hoisted__I32_5034;
                U64 hoisted__U64_5035 = (U64)(hoisted__U32_5032);
                (void)hoisted__U64_5035;
                Type_delete(hoisted__Type_5033, 1);
                memset(cloned, hoisted__I32_5034, hoisted__U64_5035);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5041 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5041->data = new_data;
    hoisted__Vec__Declaration_5041->count = self->count;
    hoisted__Vec__Declaration_5041->cap = self->cap;
    (void)hoisted__Vec__Declaration_5041;
    return hoisted__Vec__Declaration_5041;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5042 = 16;
    (void)hoisted__U32_5042;
    return hoisted__U32_5042;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5043 = 136;
    (void)hoisted__U32_5043;
    Type *hoisted__Type_5044 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5044;
    U64 hoisted__U64_5045 = (U64)(hoisted__U32_5043);
    (void)hoisted__U64_5045;
    Type_delete(hoisted__Type_5044, 1);
    void * hoisted__v_5046 = malloc(hoisted__U64_5045);
    (void)hoisted__v_5046;
    U32 hoisted__U32_5047 = 0;
    (void)hoisted__U32_5047;
    I64 hoisted__I64_5048 = 1;
    (void)hoisted__I64_5048;
    Vec__Expr *hoisted__Vec__Expr_5049 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5049->data = hoisted__v_5046;
    hoisted__Vec__Expr_5049->count = hoisted__U32_5047;
    hoisted__Vec__Expr_5049->cap = hoisted__I64_5048;
    (void)hoisted__Vec__Expr_5049;
    return hoisted__Vec__Expr_5049;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5050 = self->count;
        (void)_re_U32_5050;
        U32 _rc_U32_5050 = 0;
        (void)_rc_U32_5050;
        Bool hoisted__Bool_5065 = U32_lte(_rc_U32_5050, _re_U32_5050);
        (void)hoisted__Bool_5065;
        if (hoisted__Bool_5065) {
            while (1) {
                Bool _wcond_Bool_5051 = U32_lt(_rc_U32_5050, _re_U32_5050);
                (void)_wcond_Bool_5051;
                if (_wcond_Bool_5051) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5050);
                U32_inc(&_rc_U32_5050);
                U32 hoisted__U32_5052 = 136;
                (void)hoisted__U32_5052;
                U32 hoisted__U32_5053 = U32_mul(i, hoisted__U32_5052);
                (void)hoisted__U32_5053;
                Type *hoisted__Type_5054 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5054;
                U64 hoisted__U64_5055 = (U64)(hoisted__U32_5053);
                (void)hoisted__U64_5055;
                Type_delete(hoisted__Type_5054, 1);
                Expr *hoisted__Expr_5056 = ptr_add(self->data, hoisted__U64_5055);
                (void)hoisted__Expr_5056;
                (void)hoisted__Expr_5056;
                Bool hoisted__Bool_5057 = 0;
                (void)hoisted__Bool_5057;
                Expr_delete(hoisted__Expr_5056, hoisted__Bool_5057);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5058 = U32_gt(_rc_U32_5050, _re_U32_5050);
                (void)_wcond_Bool_5058;
                if (_wcond_Bool_5058) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5050);
                U32_dec(&_rc_U32_5050);
                U32 hoisted__U32_5059 = 136;
                (void)hoisted__U32_5059;
                U32 hoisted__U32_5060 = U32_mul(i, hoisted__U32_5059);
                (void)hoisted__U32_5060;
                Type *hoisted__Type_5061 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5061;
                U64 hoisted__U64_5062 = (U64)(hoisted__U32_5060);
                (void)hoisted__U64_5062;
                Type_delete(hoisted__Type_5061, 1);
                Expr *hoisted__Expr_5063 = ptr_add(self->data, hoisted__U64_5062);
                (void)hoisted__Expr_5063;
                (void)hoisted__Expr_5063;
                Bool hoisted__Bool_5064 = 0;
                (void)hoisted__Bool_5064;
                Expr_delete(hoisted__Expr_5063, hoisted__Bool_5064);
            }
        }
    }
    U32 hoisted__U32_5066 = 0;
    (void)hoisted__U32_5066;
    self->count = hoisted__U32_5066;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5359 = 136;
    (void)hoisted__U32_5359;
    U32 hoisted__U32_5360 = U32_mul(self->cap, hoisted__U32_5359);
    (void)hoisted__U32_5360;
    Type *hoisted__Type_5361 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5361;
    U64 hoisted__U64_5362 = (U64)(hoisted__U32_5360);
    (void)hoisted__U64_5362;
    Type_delete(hoisted__Type_5361, 1);
    void * new_data = malloc(hoisted__U64_5362);
    {
        U32 _re_U32_5323 = self->count;
        (void)_re_U32_5323;
        U32 _rc_U32_5323 = 0;
        (void)_rc_U32_5323;
        Bool hoisted__Bool_5358 = U32_lte(_rc_U32_5323, _re_U32_5323);
        (void)hoisted__Bool_5358;
        if (hoisted__Bool_5358) {
            while (1) {
                Bool _wcond_Bool_5324 = U32_lt(_rc_U32_5323, _re_U32_5323);
                (void)_wcond_Bool_5324;
                if (_wcond_Bool_5324) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5323);
                U32_inc(&_rc_U32_5323);
                U32 hoisted__U32_5325 = 136;
                (void)hoisted__U32_5325;
                U32 hoisted__U32_5326 = U32_mul(i, hoisted__U32_5325);
                (void)hoisted__U32_5326;
                Type *hoisted__Type_5327 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5327;
                U64 hoisted__U64_5328 = (U64)(hoisted__U32_5326);
                (void)hoisted__U64_5328;
                Type_delete(hoisted__Type_5327, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5328);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5329 = 136;
                (void)hoisted__U32_5329;
                U32 hoisted__U32_5330 = U32_mul(i, hoisted__U32_5329);
                (void)hoisted__U32_5330;
                Type *hoisted__Type_5331 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5331;
                U64 hoisted__U64_5332 = (U64)(hoisted__U32_5330);
                (void)hoisted__U64_5332;
                Type_delete(hoisted__Type_5331, 1);
                U32 hoisted__U32_5333 = 136;
                (void)hoisted__U32_5333;
                Type *hoisted__Type_5334 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5334;
                void *hoisted__v_5335 = ptr_add(new_data, hoisted__U64_5332);
                (void)hoisted__v_5335;
                (void)hoisted__v_5335;
                U64 hoisted__U64_5336 = (U64)(hoisted__U32_5333);
                (void)hoisted__U64_5336;
                Type_delete(hoisted__Type_5334, 1);
                memcpy(hoisted__v_5335, cloned, hoisted__U64_5336);
                U32 hoisted__U32_5337 = 136;
                (void)hoisted__U32_5337;
                Type *hoisted__Type_5338 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5338;
                I32 hoisted__I32_5339 = 0;
                (void)hoisted__I32_5339;
                U64 hoisted__U64_5340 = (U64)(hoisted__U32_5337);
                (void)hoisted__U64_5340;
                Type_delete(hoisted__Type_5338, 1);
                memset(cloned, hoisted__I32_5339, hoisted__U64_5340);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5341 = U32_gt(_rc_U32_5323, _re_U32_5323);
                (void)_wcond_Bool_5341;
                if (_wcond_Bool_5341) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5323);
                U32_dec(&_rc_U32_5323);
                U32 hoisted__U32_5342 = 136;
                (void)hoisted__U32_5342;
                U32 hoisted__U32_5343 = U32_mul(i, hoisted__U32_5342);
                (void)hoisted__U32_5343;
                Type *hoisted__Type_5344 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5344;
                U64 hoisted__U64_5345 = (U64)(hoisted__U32_5343);
                (void)hoisted__U64_5345;
                Type_delete(hoisted__Type_5344, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5345);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5346 = 136;
                (void)hoisted__U32_5346;
                U32 hoisted__U32_5347 = U32_mul(i, hoisted__U32_5346);
                (void)hoisted__U32_5347;
                Type *hoisted__Type_5348 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5348;
                U64 hoisted__U64_5349 = (U64)(hoisted__U32_5347);
                (void)hoisted__U64_5349;
                Type_delete(hoisted__Type_5348, 1);
                U32 hoisted__U32_5350 = 136;
                (void)hoisted__U32_5350;
                Type *hoisted__Type_5351 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5351;
                void *hoisted__v_5352 = ptr_add(new_data, hoisted__U64_5349);
                (void)hoisted__v_5352;
                (void)hoisted__v_5352;
                U64 hoisted__U64_5353 = (U64)(hoisted__U32_5350);
                (void)hoisted__U64_5353;
                Type_delete(hoisted__Type_5351, 1);
                memcpy(hoisted__v_5352, cloned, hoisted__U64_5353);
                U32 hoisted__U32_5354 = 136;
                (void)hoisted__U32_5354;
                Type *hoisted__Type_5355 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5355;
                I32 hoisted__I32_5356 = 0;
                (void)hoisted__I32_5356;
                U64 hoisted__U64_5357 = (U64)(hoisted__U32_5354);
                (void)hoisted__U64_5357;
                Type_delete(hoisted__Type_5355, 1);
                memset(cloned, hoisted__I32_5356, hoisted__U64_5357);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5363 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5363->data = new_data;
    hoisted__Vec__Expr_5363->count = self->count;
    hoisted__Vec__Expr_5363->cap = self->cap;
    (void)hoisted__Vec__Expr_5363;
    return hoisted__Vec__Expr_5363;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5364 = 16;
    (void)hoisted__U32_5364;
    return hoisted__U32_5364;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5365 = 8;
    (void)hoisted__U32_5365;
    Type *hoisted__Type_5366 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5366;
    U64 hoisted__U64_5367 = (U64)(hoisted__U32_5365);
    (void)hoisted__U64_5367;
    Type_delete(hoisted__Type_5366, 1);
    void * hoisted__v_5368 = malloc(hoisted__U64_5367);
    (void)hoisted__v_5368;
    U32 hoisted__U32_5369 = 0;
    (void)hoisted__U32_5369;
    I64 hoisted__I64_5370 = 1;
    (void)hoisted__I64_5370;
    Vec__I64 *hoisted__Vec__I64_5371 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5371->data = hoisted__v_5368;
    hoisted__Vec__I64_5371->count = hoisted__U32_5369;
    hoisted__Vec__I64_5371->cap = hoisted__I64_5370;
    (void)hoisted__Vec__I64_5371;
    return hoisted__Vec__I64_5371;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5372 = self->count;
        (void)_re_U32_5372;
        U32 _rc_U32_5372 = 0;
        (void)_rc_U32_5372;
        Bool hoisted__Bool_5387 = U32_lte(_rc_U32_5372, _re_U32_5372);
        (void)hoisted__Bool_5387;
        if (hoisted__Bool_5387) {
            while (1) {
                Bool _wcond_Bool_5373 = U32_lt(_rc_U32_5372, _re_U32_5372);
                (void)_wcond_Bool_5373;
                if (_wcond_Bool_5373) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5372);
                U32_inc(&_rc_U32_5372);
                U32 hoisted__U32_5374 = 8;
                (void)hoisted__U32_5374;
                U32 hoisted__U32_5375 = U32_mul(i, hoisted__U32_5374);
                (void)hoisted__U32_5375;
                Type *hoisted__Type_5376 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5376;
                U64 hoisted__U64_5377 = (U64)(hoisted__U32_5375);
                (void)hoisted__U64_5377;
                Type_delete(hoisted__Type_5376, 1);
                I64 *hoisted__I64_5378 = ptr_add(self->data, hoisted__U64_5377);
                (void)hoisted__I64_5378;
                (void)hoisted__I64_5378;
                Bool hoisted__Bool_5379 = 0;
                (void)hoisted__Bool_5379;
                I64_delete(hoisted__I64_5378, hoisted__Bool_5379);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5380 = U32_gt(_rc_U32_5372, _re_U32_5372);
                (void)_wcond_Bool_5380;
                if (_wcond_Bool_5380) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5372);
                U32_dec(&_rc_U32_5372);
                U32 hoisted__U32_5381 = 8;
                (void)hoisted__U32_5381;
                U32 hoisted__U32_5382 = U32_mul(i, hoisted__U32_5381);
                (void)hoisted__U32_5382;
                Type *hoisted__Type_5383 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5383;
                U64 hoisted__U64_5384 = (U64)(hoisted__U32_5382);
                (void)hoisted__U64_5384;
                Type_delete(hoisted__Type_5383, 1);
                I64 *hoisted__I64_5385 = ptr_add(self->data, hoisted__U64_5384);
                (void)hoisted__I64_5385;
                (void)hoisted__I64_5385;
                Bool hoisted__Bool_5386 = 0;
                (void)hoisted__Bool_5386;
                I64_delete(hoisted__I64_5385, hoisted__Bool_5386);
            }
        }
    }
    U32 hoisted__U32_5388 = 0;
    (void)hoisted__U32_5388;
    self->count = hoisted__U32_5388;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5681 = 8;
    (void)hoisted__U32_5681;
    U32 hoisted__U32_5682 = U32_mul(self->cap, hoisted__U32_5681);
    (void)hoisted__U32_5682;
    Type *hoisted__Type_5683 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5683;
    U64 hoisted__U64_5684 = (U64)(hoisted__U32_5682);
    (void)hoisted__U64_5684;
    Type_delete(hoisted__Type_5683, 1);
    void * new_data = malloc(hoisted__U64_5684);
    {
        U32 _re_U32_5645 = self->count;
        (void)_re_U32_5645;
        U32 _rc_U32_5645 = 0;
        (void)_rc_U32_5645;
        Bool hoisted__Bool_5680 = U32_lte(_rc_U32_5645, _re_U32_5645);
        (void)hoisted__Bool_5680;
        if (hoisted__Bool_5680) {
            while (1) {
                Bool _wcond_Bool_5646 = U32_lt(_rc_U32_5645, _re_U32_5645);
                (void)_wcond_Bool_5646;
                if (_wcond_Bool_5646) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5645);
                U32_inc(&_rc_U32_5645);
                U32 hoisted__U32_5647 = 8;
                (void)hoisted__U32_5647;
                U32 hoisted__U32_5648 = U32_mul(i, hoisted__U32_5647);
                (void)hoisted__U32_5648;
                Type *hoisted__Type_5649 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5649;
                U64 hoisted__U64_5650 = (U64)(hoisted__U32_5648);
                (void)hoisted__U64_5650;
                Type_delete(hoisted__Type_5649, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5650);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5651 = 8;
                (void)hoisted__U32_5651;
                U32 hoisted__U32_5652 = U32_mul(i, hoisted__U32_5651);
                (void)hoisted__U32_5652;
                Type *hoisted__Type_5653 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5653;
                U64 hoisted__U64_5654 = (U64)(hoisted__U32_5652);
                (void)hoisted__U64_5654;
                Type_delete(hoisted__Type_5653, 1);
                U32 hoisted__U32_5655 = 8;
                (void)hoisted__U32_5655;
                Type *hoisted__Type_5656 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5656;
                void *hoisted__v_5657 = ptr_add(new_data, hoisted__U64_5654);
                (void)hoisted__v_5657;
                (void)hoisted__v_5657;
                U64 hoisted__U64_5658 = (U64)(hoisted__U32_5655);
                (void)hoisted__U64_5658;
                Type_delete(hoisted__Type_5656, 1);
                memcpy(hoisted__v_5657, &cloned, hoisted__U64_5658);
                U32 hoisted__U32_5659 = 8;
                (void)hoisted__U32_5659;
                Type *hoisted__Type_5660 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5660;
                I32 hoisted__I32_5661 = 0;
                (void)hoisted__I32_5661;
                U64 hoisted__U64_5662 = (U64)(hoisted__U32_5659);
                (void)hoisted__U64_5662;
                Type_delete(hoisted__Type_5660, 1);
                memset(&cloned, hoisted__I32_5661, hoisted__U64_5662);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5663 = U32_gt(_rc_U32_5645, _re_U32_5645);
                (void)_wcond_Bool_5663;
                if (_wcond_Bool_5663) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5645);
                U32_dec(&_rc_U32_5645);
                U32 hoisted__U32_5664 = 8;
                (void)hoisted__U32_5664;
                U32 hoisted__U32_5665 = U32_mul(i, hoisted__U32_5664);
                (void)hoisted__U32_5665;
                Type *hoisted__Type_5666 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5666;
                U64 hoisted__U64_5667 = (U64)(hoisted__U32_5665);
                (void)hoisted__U64_5667;
                Type_delete(hoisted__Type_5666, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5667);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5668 = 8;
                (void)hoisted__U32_5668;
                U32 hoisted__U32_5669 = U32_mul(i, hoisted__U32_5668);
                (void)hoisted__U32_5669;
                Type *hoisted__Type_5670 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5670;
                U64 hoisted__U64_5671 = (U64)(hoisted__U32_5669);
                (void)hoisted__U64_5671;
                Type_delete(hoisted__Type_5670, 1);
                U32 hoisted__U32_5672 = 8;
                (void)hoisted__U32_5672;
                Type *hoisted__Type_5673 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5673;
                void *hoisted__v_5674 = ptr_add(new_data, hoisted__U64_5671);
                (void)hoisted__v_5674;
                (void)hoisted__v_5674;
                U64 hoisted__U64_5675 = (U64)(hoisted__U32_5672);
                (void)hoisted__U64_5675;
                Type_delete(hoisted__Type_5673, 1);
                memcpy(hoisted__v_5674, &cloned, hoisted__U64_5675);
                U32 hoisted__U32_5676 = 8;
                (void)hoisted__U32_5676;
                Type *hoisted__Type_5677 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5677;
                I32 hoisted__I32_5678 = 0;
                (void)hoisted__I32_5678;
                U64 hoisted__U64_5679 = (U64)(hoisted__U32_5676);
                (void)hoisted__U64_5679;
                Type_delete(hoisted__Type_5677, 1);
                memset(&cloned, hoisted__I32_5678, hoisted__U64_5679);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5685 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5685->data = new_data;
    hoisted__Vec__I64_5685->count = self->count;
    hoisted__Vec__I64_5685->cap = self->cap;
    (void)hoisted__Vec__I64_5685;
    return hoisted__Vec__I64_5685;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5686 = 16;
    (void)hoisted__U32_5686;
    return hoisted__U32_5686;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6807 = 3;
    (void)hoisted__U32_6807;
    Array__Str *_va_Array_193 = Array__Str_new(hoisted__U32_6807);
    (void)_va_Array_193;
    I64 _va_Array_193_ek = 0;
    (void)_va_Array_193_ek;
    OutOfBounds *_va_Array_193_eo = malloc(sizeof(OutOfBounds));
    _va_Array_193_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_193_eo;
    U32 hoisted__U32_6808 = 0;
    (void)hoisted__U32_6808;
    Str *hoisted__Str_6809 = Str_clone(loc);
    (void)hoisted__Str_6809;
    Array__Str_set(_va_Array_193, hoisted__U32_6808, hoisted__Str_6809, &_va_Array_193_ek, _va_Array_193_eo);
    U32 hoisted__U32_6810 = 1;
    (void)hoisted__U32_6810;
    Str hoisted__Str_6811 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6811;
    Array__Str_set(_va_Array_193, hoisted__U32_6810, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6811; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_193_ek, _va_Array_193_eo);
    Array__Str *hoisted__Array__Str_6812 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6812;
    U32 hoisted__U32_6813 = 2;
    (void)hoisted__U32_6813;
    Str *hoisted__Str_6814 = format(hoisted__Array__Str_6812);
    (void)hoisted__Str_6814;
    Array__Str_set(_va_Array_193, hoisted__U32_6813, hoisted__Str_6814, &_va_Array_193_ek, _va_Array_193_eo);
    OutOfBounds_delete(_va_Array_193_eo, 1);
    Array__Str_delete(parts, 1);
    println(_va_Array_193);
    I64 hoisted__I64_6815 = 1;
    (void)hoisted__I64_6815;
    exit(hoisted__I64_6815);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_6822 = 1;
    (void)hoisted__U32_6822;
    Array__Str *_va_Array_195 = Array__Str_new(hoisted__U32_6822);
    (void)_va_Array_195;
    I64 _va_Array_195_ek = 0;
    (void)_va_Array_195_ek;
    OutOfBounds *_va_Array_195_eo = malloc(sizeof(OutOfBounds));
    _va_Array_195_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_195_eo;
    U32 hoisted__U32_6823 = 0;
    (void)hoisted__U32_6823;
    Str hoisted__Str_6824 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6824;
    Array__Str_set(_va_Array_195, hoisted__U32_6823, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6824; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_195_ek, _va_Array_195_eo);
    OutOfBounds_delete(_va_Array_195_eo, 1);
    panic(_va_Array_195, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6828 = not(cond);
    (void)hoisted__Bool_6828;
    if (hoisted__Bool_6828) {
        U32 hoisted__U32_6825 = 1;
        (void)hoisted__U32_6825;
        Array__Str *_va_Array_196 = Array__Str_new(hoisted__U32_6825);
        (void)_va_Array_196;
        I64 _va_Array_196_ek = 0;
        (void)_va_Array_196_ek;
        OutOfBounds *_va_Array_196_eo = malloc(sizeof(OutOfBounds));
        _va_Array_196_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_196_eo;
        U32 hoisted__U32_6826 = 0;
        (void)hoisted__U32_6826;
        Str hoisted__Str_6827 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6827;
        Array__Str_set(_va_Array_196, hoisted__U32_6826, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6827; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_196_ek, _va_Array_196_eo);
        OutOfBounds_delete(_va_Array_196_eo, 1);
        panic(_va_Array_196, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6836 = parts;
        (void)_fc_Array__Str_6836;
        (void)_fc_Array__Str_6836;
        U32 _fi_USize_6836 = 0;
        (void)_fi_USize_6836;
        I64 _forin_err_kind_6836 = 0;
        (void)_forin_err_kind_6836;
        OutOfBounds *_forin_OutOfBounds_6836 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_6836->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_6836;
        while (1) {
            U32 hoisted__U32_6844 = Array__Str_len(_fc_Array__Str_6836);
            (void)hoisted__U32_6844;
            Bool _wcond_Bool_6837 = U32_lt(_fi_USize_6836, hoisted__U32_6844);
            (void)_wcond_Bool_6837;
            if (_wcond_Bool_6837) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_6836, &_fi_USize_6836, &_forin_err_kind_6836, _forin_OutOfBounds_6836);
            I64 hoisted__I64_6845 = 0;
            (void)hoisted__I64_6845;
            Bool hoisted__Bool_6846 = I64_eq(_forin_err_kind_6836, hoisted__I64_6845);
            (void)hoisted__Bool_6846;
            Bool hoisted__Bool_6847 = not(hoisted__Bool_6846);
            (void)hoisted__Bool_6847;
            if (hoisted__Bool_6847) {
                U32 hoisted__U32_6838 = 2;
                (void)hoisted__U32_6838;
                Array__Str *_va_Array_198 = Array__Str_new(hoisted__U32_6838);
                (void)_va_Array_198;
                I64 _va_Array_198_ek = 0;
                (void)_va_Array_198_ek;
                OutOfBounds *_va_Array_198_eo = malloc(sizeof(OutOfBounds));
                _va_Array_198_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_198_eo;
                U32 hoisted__U32_6839 = 0;
                (void)hoisted__U32_6839;
                Str hoisted__Str_6840 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6840;
                Array__Str_set(_va_Array_198, hoisted__U32_6839, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6840; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_198_ek, _va_Array_198_eo);
                U32 hoisted__U32_6841 = 1;
                (void)hoisted__U32_6841;
                Str hoisted__Str_6842 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6842;
                Array__Str_set(_va_Array_198, hoisted__U32_6841, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6842; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_198_ek, _va_Array_198_eo);
                OutOfBounds_delete(_va_Array_198_eo, 1);
                Str hoisted__Str_6843 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6843;
                panic(_va_Array_198, &hoisted__Str_6843);
                Str_delete(&hoisted__Str_6843, (Bool){0});
            }
            U32 hoisted__U32_6848 = 1;
            (void)hoisted__U32_6848;
            U32 hoisted__U32_6849 = U32_add(_fi_USize_6836, hoisted__U32_6848);
            (void)hoisted__U32_6849;
            _fi_USize_6836 = hoisted__U32_6849;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_6836, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_6889 = ptr_eq(p, NULL);
    (void)hoisted__Bool_6889;
    return hoisted__Bool_6889;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6898 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6898;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6898;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6899 = 0;
    (void)hoisted__U32_6899;
    U64 hoisted__U64_6900 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6899); });
    (void)hoisted__U64_6900;
    return hoisted__U64_6900;
}

U32 Range_size(void) {
    U32 hoisted__U32_6924 = 16;
    (void)hoisted__U32_6924;
    return hoisted__U32_6924;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7035 = 3;
    (void)hoisted__I64_7035;
    Str hoisted__Str_7036 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7036;
    assert_eq__I64(result, hoisted__I64_7035, &hoisted__Str_7036);
    Str_delete(&hoisted__Str_7036, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7043 = 15;
    (void)hoisted__I64_7043;
    Str hoisted__Str_7044 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7044;
    assert_eq__I64(result, hoisted__I64_7043, &hoisted__Str_7044);
    Str_delete(&hoisted__Str_7044, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7051 = 26;
    (void)hoisted__I64_7051;
    Str hoisted__Str_7052 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7052;
    assert_eq__I64(result, hoisted__I64_7051, &hoisted__Str_7052);
    Str_delete(&hoisted__Str_7052, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7055 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7055;
    Str hoisted__Str_7056 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7056;
    assert_eq__Str(&result, &hoisted__Str_7055, &hoisted__Str_7056);
    Str_delete(&hoisted__Str_7055, (Bool){0});
    Str_delete(&hoisted__Str_7056, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7077 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7077;
    Str hoisted__Str_7078 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7078;
    assert_eq__Str(&r, &hoisted__Str_7077, &hoisted__Str_7078);
    Str_delete(&hoisted__Str_7077, (Bool){0});
    Str_delete(&hoisted__Str_7078, (Bool){0});
    Str_delete(&r, (Bool){0});
    Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7082 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7082;
    Str hoisted__Str_7083 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7083;
    assert_eq__Str(&r2, &hoisted__Str_7082, &hoisted__Str_7083);
    Str_delete(&hoisted__Str_7082, (Bool){0});
    Str_delete(&hoisted__Str_7083, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7110 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7110;
    Str hoisted__Str_7111 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7111;
    assert_eq__Str(&d, &hoisted__Str_7110, &hoisted__Str_7111);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7110, (Bool){0});
    Str_delete(&hoisted__Str_7111, (Bool){0});
    Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7119 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7119;
    Str hoisted__Str_7120 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7120;
    assert_eq__Str(&d2, &hoisted__Str_7119, &hoisted__Str_7120);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7119, (Bool){0});
    Str_delete(&hoisted__Str_7120, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7129 = 106;
    (void)hoisted__I64_7129;
    Str hoisted__Str_7130 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7130;
    assert_eq__I64(d3, hoisted__I64_7129, &hoisted__Str_7130);
    Str_delete(&hoisted__Str_7130, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7619 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7619;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_7619);
    Str_delete(&hoisted__Str_7619, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_7620 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7620;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_7620);
    Str_delete(&hoisted__Str_7620, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_7622 = 8;
    (void)hoisted__I64_7622;
    Str hoisted__Str_7623 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7623;
    assert_eq__I64(result, hoisted__I64_7622, &hoisted__Str_7623);
    Str_delete(&hoisted__Str_7623, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7626 = 1;
    (void)hoisted__Bool_7626;
    Str hoisted__Str_7627 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7627;
    assert(hoisted__Bool_7626, &hoisted__Str_7627);
    Str_delete(&hoisted__Str_7627, (Bool){0});
    Bool hoisted__Bool_7630 = 1;
    (void)hoisted__Bool_7630;
    Str hoisted__Str_7631 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7631;
    assert(hoisted__Bool_7630, &hoisted__Str_7631);
    Str_delete(&hoisted__Str_7631, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_7636 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7636;
    Str hoisted__Str_7637 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7637;
    Str hoisted__Str_7638 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7638;
    assert_eq__Str(&hoisted__Str_7636, &hoisted__Str_7637, &hoisted__Str_7638);
    Str_delete(&hoisted__Str_7636, (Bool){0});
    Str_delete(&hoisted__Str_7637, (Bool){0});
    Str_delete(&hoisted__Str_7638, (Bool){0});
    Str hoisted__Str_7641 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7641;
    Str hoisted__Str_7642 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7642;
    Str hoisted__Str_7643 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7643;
    assert_eq__Str(&hoisted__Str_7641, &hoisted__Str_7642, &hoisted__Str_7643);
    Str_delete(&hoisted__Str_7641, (Bool){0});
    Str_delete(&hoisted__Str_7642, (Bool){0});
    Str_delete(&hoisted__Str_7643, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7648 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7648;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7648;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7649 = 0;
    (void)hoisted__U32_7649;
    U64 hoisted__U64_7650 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7649); });
    (void)hoisted__U64_7650;
    return hoisted__U64_7650;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_7674 = 16;
    (void)hoisted__U32_7674;
    return hoisted__U32_7674;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_7675 = 42;
    (void)hoisted__I64_7675;
    Str hoisted__Str_7676 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7676;
    assert_eq__I64(v.x, hoisted__I64_7675, &hoisted__Str_7676);
    Str_delete(&hoisted__Str_7676, (Bool){0});
    I64 hoisted__I64_7677 = 99;
    (void)hoisted__I64_7677;
    Str hoisted__Str_7678 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7678;
    assert_eq__I64(v.y, hoisted__I64_7677, &hoisted__Str_7678);
    Str_delete(&hoisted__Str_7678, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7681 = 10;
    (void)hoisted__I64_7681;
    Str hoisted__Str_7682 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7682;
    assert_eq__I64(p.x, hoisted__I64_7681, &hoisted__Str_7682);
    Str_delete(&hoisted__Str_7682, (Bool){0});
    I64 hoisted__I64_7683 = 20;
    (void)hoisted__I64_7683;
    Str hoisted__Str_7684 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7684;
    assert_eq__I64(p.y, hoisted__I64_7683, &hoisted__Str_7684);
    Str_delete(&hoisted__Str_7684, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7690 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7690;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7690;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7691 = 0;
    (void)hoisted__U32_7691;
    U64 hoisted__U64_7692 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7691); });
    (void)hoisted__U64_7692;
    return hoisted__U64_7692;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_7716 = 32;
    (void)hoisted__U32_7716;
    return hoisted__U32_7716;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_7717 = 5;
    (void)hoisted__I64_7717;
    Str hoisted__Str_7718 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7718;
    assert_eq__I64(r.top_left.x, hoisted__I64_7717, &hoisted__Str_7718);
    Str_delete(&hoisted__Str_7718, (Bool){0});
    I64 hoisted__I64_7719 = 10;
    (void)hoisted__I64_7719;
    Str hoisted__Str_7720 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7720;
    assert_eq__I64(r.top_left.y, hoisted__I64_7719, &hoisted__Str_7720);
    Str_delete(&hoisted__Str_7720, (Bool){0});
    I64 hoisted__I64_7721 = 100;
    (void)hoisted__I64_7721;
    Str hoisted__Str_7722 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7722;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7721, &hoisted__Str_7722);
    Str_delete(&hoisted__Str_7722, (Bool){0});
    I64 hoisted__I64_7723 = 200;
    (void)hoisted__I64_7723;
    Str hoisted__Str_7724 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7724;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7723, &hoisted__Str_7724);
    Str_delete(&hoisted__Str_7724, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7726 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7726;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7726;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7727 = 0;
    (void)hoisted__U32_7727;
    U64 hoisted__U64_7728 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7727); });
    (void)hoisted__U64_7728;
    return hoisted__U64_7728;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_7761 = 12;
    (void)hoisted__U32_7761;
    return hoisted__U32_7761;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_7765 = F32_to_str(v.x);
    (void)hoisted__Str_7765;
    Str hoisted__Str_7766 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7766;
    Str hoisted__Str_7767 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7767;
    assert_eq__Str(hoisted__Str_7765, &hoisted__Str_7766, &hoisted__Str_7767);
    Str_delete(hoisted__Str_7765, 1);
    Str_delete(&hoisted__Str_7766, (Bool){0});
    Str_delete(&hoisted__Str_7767, (Bool){0});
    Str *hoisted__Str_7768 = F32_to_str(v.y);
    (void)hoisted__Str_7768;
    Str hoisted__Str_7769 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7769;
    Str hoisted__Str_7770 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7770;
    assert_eq__Str(hoisted__Str_7768, &hoisted__Str_7769, &hoisted__Str_7770);
    Str_delete(hoisted__Str_7768, 1);
    Str_delete(&hoisted__Str_7769, (Bool){0});
    Str_delete(&hoisted__Str_7770, (Bool){0});
    Str *hoisted__Str_7771 = F32_to_str(v.z);
    (void)hoisted__Str_7771;
    Str hoisted__Str_7772 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7772;
    Str hoisted__Str_7773 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7773;
    assert_eq__Str(hoisted__Str_7771, &hoisted__Str_7772, &hoisted__Str_7773);
    Str_delete(hoisted__Str_7771, 1);
    Str_delete(&hoisted__Str_7772, (Bool){0});
    Str_delete(&hoisted__Str_7773, (Bool){0});
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
    Bool hoisted__Bool_7778 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7778;
    if (hoisted__Bool_7778) {
        Bool hoisted__Bool_7775 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_7775;
        { Bool _ret_val = hoisted__Bool_7775;
                return _ret_val; }
    }
    Bool hoisted__Bool_7779 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7779;
    if (hoisted__Bool_7779) {
        Bool hoisted__Bool_7776 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_7776;
        { Bool _ret_val = hoisted__Bool_7776;
                return _ret_val; }
    }
    Bool hoisted__Bool_7780 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7780;
    if (hoisted__Bool_7780) {
        Bool hoisted__Bool_7777 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_7777;
        { Bool _ret_val = hoisted__Bool_7777;
                return _ret_val; }
    }
    Bool hoisted__Bool_7781 = 0;
    (void)hoisted__Bool_7781;
    return hoisted__Bool_7781;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7789 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7789;
    if (hoisted__Bool_7789) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_7790 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7790;
    if (hoisted__Bool_7790) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_7791 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7791;
    if (hoisted__Bool_7791) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_7792 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7792;
    UNREACHABLE(&hoisted__Str_7792);
    Str_delete(&hoisted__Str_7792, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_7793 = 4;
    (void)hoisted__U32_7793;
    return hoisted__U32_7793;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7794 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7794;
    Str hoisted__Str_7795 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7795;
    assert(hoisted__Bool_7794, &hoisted__Str_7795);
    Str_delete(&hoisted__Str_7795, (Bool){0});
    Bool hoisted__Bool_7796 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7796;
    Bool hoisted__Bool_7797 = not(hoisted__Bool_7796);
    (void)hoisted__Bool_7797;
    Str hoisted__Str_7798 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7798;
    assert(hoisted__Bool_7797, &hoisted__Str_7798);
    Str_delete(&hoisted__Str_7798, (Bool){0});
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
    Bool hoisted__Bool_7799 = is(self, other);
    (void)hoisted__Bool_7799;
    return hoisted__Bool_7799;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7817 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7817;
    if (hoisted__Bool_7817) {
        I64 *hoisted__I64_7813 = get_payload(self);
        (void)hoisted__I64_7813;
        (void)hoisted__I64_7813;
        Bool hoisted__Bool_7814 = 0;
        (void)hoisted__Bool_7814;
        I64_delete(hoisted__I64_7813, hoisted__Bool_7814);
    }
    Bool hoisted__Bool_7818 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7818;
    if (hoisted__Bool_7818) {
        Str *hoisted__Str_7815 = get_payload(self);
        (void)hoisted__Str_7815;
        (void)hoisted__Str_7815;
        Bool hoisted__Bool_7816 = 0;
        (void)hoisted__Bool_7816;
        Str_delete(hoisted__Str_7815, hoisted__Bool_7816);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_7843 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7843;
    if (hoisted__Bool_7843) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7840 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7840;
        { Token * _ret_val = hoisted__Token_7840;
                return _ret_val; }
    }
    Bool hoisted__Bool_7844 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7844;
    if (hoisted__Bool_7844) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7841 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7841;
        Token *hoisted__Token_7842 = Token_Name(hoisted__Str_7841);
        (void)hoisted__Token_7842;
        { Token * _ret_val = hoisted__Token_7842;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_7845 = 24;
    (void)hoisted__U32_7845;
    return hoisted__U32_7845;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7847 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7847;
    Str hoisted__Str_7848 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7848;
    assert(hoisted__Bool_7847, &hoisted__Str_7848);
    Str_delete(&hoisted__Str_7848, (Bool){0});
    Bool hoisted__Bool_7849 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7849;
    Bool hoisted__Bool_7850 = not(hoisted__Bool_7849);
    (void)hoisted__Bool_7850;
    Str hoisted__Str_7851 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7851;
    assert(hoisted__Bool_7850, &hoisted__Str_7851);
    Str_delete(&hoisted__Str_7851, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7852 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7852;
    Str hoisted__Str_7853 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7853;
    assert(hoisted__Bool_7852, &hoisted__Str_7853);
    Str_delete(&hoisted__Str_7853, (Bool){0});
    Bool hoisted__Bool_7854 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7854;
    Bool hoisted__Bool_7855 = not(hoisted__Bool_7854);
    (void)hoisted__Bool_7855;
    Str hoisted__Str_7856 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7856;
    assert(hoisted__Bool_7855, &hoisted__Str_7856);
    Str_delete(&hoisted__Str_7856, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7859 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7859;
    Str hoisted__Str_7860 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7860;
    assert(hoisted__Bool_7859, &hoisted__Str_7860);
    Str_delete(&hoisted__Str_7860, (Bool){0});
    Bool hoisted__Bool_7861 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7861;
    Bool hoisted__Bool_7862 = not(hoisted__Bool_7861);
    (void)hoisted__Bool_7862;
    Str hoisted__Str_7863 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7863;
    assert(hoisted__Bool_7862, &hoisted__Str_7863);
    Str_delete(&hoisted__Str_7863, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8001 = I64_neq(a, b);
    (void)hoisted__Bool_8001;
    if (hoisted__Bool_8001) {
        U32 hoisted__U32_7990 = 5;
        (void)hoisted__U32_7990;
        Array__Str *_va_Array_244 = Array__Str_new(hoisted__U32_7990);
        (void)_va_Array_244;
        I64 _va_Array_244_ek = 0;
        (void)_va_Array_244_ek;
        OutOfBounds *_va_Array_244_eo = malloc(sizeof(OutOfBounds));
        _va_Array_244_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_244_eo;
        U32 hoisted__U32_7991 = 0;
        (void)hoisted__U32_7991;
        Str hoisted__Str_7992 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7992;
        Array__Str_set(_va_Array_244, hoisted__U32_7991, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7992; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_244_ek, _va_Array_244_eo);
        U32 hoisted__U32_7993 = 1;
        (void)hoisted__U32_7993;
        Str *hoisted__Str_7994 = I64_to_str(a);
        (void)hoisted__Str_7994;
        Array__Str_set(_va_Array_244, hoisted__U32_7993, hoisted__Str_7994, &_va_Array_244_ek, _va_Array_244_eo);
        U32 hoisted__U32_7995 = 2;
        (void)hoisted__U32_7995;
        Str hoisted__Str_7996 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7996;
        Array__Str_set(_va_Array_244, hoisted__U32_7995, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7996; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_244_ek, _va_Array_244_eo);
        U32 hoisted__U32_7997 = 3;
        (void)hoisted__U32_7997;
        Str *hoisted__Str_7998 = I64_to_str(b);
        (void)hoisted__Str_7998;
        Array__Str_set(_va_Array_244, hoisted__U32_7997, hoisted__Str_7998, &_va_Array_244_ek, _va_Array_244_eo);
        U32 hoisted__U32_7999 = 4;
        (void)hoisted__U32_7999;
        Str hoisted__Str_8000 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8000;
        Array__Str_set(_va_Array_244, hoisted__U32_7999, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8000; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_244_ek, _va_Array_244_eo);
        OutOfBounds_delete(_va_Array_244_eo, 1);
        panic(_va_Array_244, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8013 = Str_neq(a, b);
    (void)hoisted__Bool_8013;
    if (hoisted__Bool_8013) {
        U32 hoisted__U32_8002 = 5;
        (void)hoisted__U32_8002;
        Array__Str *_va_Array_245 = Array__Str_new(hoisted__U32_8002);
        (void)_va_Array_245;
        I64 _va_Array_245_ek = 0;
        (void)_va_Array_245_ek;
        OutOfBounds *_va_Array_245_eo = malloc(sizeof(OutOfBounds));
        _va_Array_245_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_245_eo;
        U32 hoisted__U32_8003 = 0;
        (void)hoisted__U32_8003;
        Str hoisted__Str_8004 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8004;
        Array__Str_set(_va_Array_245, hoisted__U32_8003, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8004; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_245_ek, _va_Array_245_eo);
        U32 hoisted__U32_8005 = 1;
        (void)hoisted__U32_8005;
        Str *hoisted__Str_8006 = Str_to_str(a);
        (void)hoisted__Str_8006;
        Array__Str_set(_va_Array_245, hoisted__U32_8005, hoisted__Str_8006, &_va_Array_245_ek, _va_Array_245_eo);
        U32 hoisted__U32_8007 = 2;
        (void)hoisted__U32_8007;
        Str hoisted__Str_8008 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8008;
        Array__Str_set(_va_Array_245, hoisted__U32_8007, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8008; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_245_ek, _va_Array_245_eo);
        U32 hoisted__U32_8009 = 3;
        (void)hoisted__U32_8009;
        Str *hoisted__Str_8010 = Str_to_str(b);
        (void)hoisted__Str_8010;
        Array__Str_set(_va_Array_245, hoisted__U32_8009, hoisted__Str_8010, &_va_Array_245_ek, _va_Array_245_eo);
        U32 hoisted__U32_8011 = 4;
        (void)hoisted__U32_8011;
        Str hoisted__Str_8012 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8012;
        Array__Str_set(_va_Array_245, hoisted__U32_8011, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_8012; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_245_ek, _va_Array_245_eo);
        OutOfBounds_delete(_va_Array_245_eo, 1);
        panic(_va_Array_245, loc);
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
