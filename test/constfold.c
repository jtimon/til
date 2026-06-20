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
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
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
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc);
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
    U32 hoisted__U32_131 = 0;
    (void)hoisted__U32_131;
    U64 hoisted__U64_132 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_131); });
    (void)hoisted__U64_132;
    return hoisted__U64_132;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_147 = U32_to_i64(val);
    (void)hoisted__I64_147;
    Str *hoisted__Str_148 = I64_to_str(hoisted__I64_147);
    (void)hoisted__Str_148;
    return hoisted__Str_148;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_149 = 1;
    (void)hoisted__U32_149;
    U32 hoisted__U32_150 = U32_add(DEREF(self), hoisted__U32_149);
    (void)hoisted__U32_150;
    *self = hoisted__U32_150;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_151 = 1;
    (void)hoisted__U32_151;
    U32 hoisted__U32_152 = U32_sub(DEREF(self), hoisted__U32_151);
    (void)hoisted__U32_152;
    *self = hoisted__U32_152;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_161 = 4;
    (void)hoisted__U32_161;
    return hoisted__U32_161;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_246 = 0;
    (void)hoisted__U32_246;
    U64 hoisted__U64_247 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_246); });
    (void)hoisted__U64_247;
    return hoisted__U64_247;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_250 = U32_cmp(a, b);
    (void)hoisted__I64_250;
    I64 hoisted__I64_251 = -1;
    (void)hoisted__I64_251;
    Bool hoisted__Bool_252 = I64_eq(hoisted__I64_250, hoisted__I64_251);
    (void)hoisted__Bool_252;
    return hoisted__Bool_252;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_253 = U32_cmp(a, b);
    (void)hoisted__I64_253;
    I64 hoisted__I64_254 = 1;
    (void)hoisted__I64_254;
    Bool hoisted__Bool_255 = I64_eq(hoisted__I64_253, hoisted__I64_254);
    (void)hoisted__Bool_255;
    return hoisted__Bool_255;
}

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_256 = U32_eq(a, b);
    (void)hoisted__Bool_256;
    Bool hoisted__Bool_257 = not(hoisted__Bool_256);
    (void)hoisted__Bool_257;
    return hoisted__Bool_257;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_258 = U32_gt(a, b);
    (void)hoisted__Bool_258;
    Bool hoisted__Bool_259 = not(hoisted__Bool_258);
    (void)hoisted__Bool_259;
    return hoisted__Bool_259;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_260 = U32_lt(a, b);
    (void)hoisted__Bool_260;
    Bool hoisted__Bool_261 = not(hoisted__Bool_260);
    (void)hoisted__Bool_261;
    return hoisted__Bool_261;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_284 = 4;
    (void)hoisted__U32_284;
    return hoisted__U32_284;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_426 = 0;
    (void)hoisted__U32_426;
    U64 hoisted__U64_427 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_426); });
    (void)hoisted__U64_427;
    return hoisted__U64_427;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_464 = 1;
    (void)hoisted__U32_464;
    return hoisted__U32_464;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_465 = 0;
    (void)hoisted__U32_465;
    U64 hoisted__U64_466 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_465); });
    (void)hoisted__U64_466;
    return hoisted__U64_466;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_495 = 1;
    (void)hoisted__U32_495;
    return hoisted__U32_495;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_580 = 0;
    (void)hoisted__U32_580;
    U64 hoisted__U64_581 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_580); });
    (void)hoisted__U64_581;
    return hoisted__U64_581;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_734 = parts;
        (void)_fc_Array__Str_734;
        (void)_fc_Array__Str_734;
        U32 _fi_USize_734 = 0;
        (void)_fi_USize_734;
        I64 _forin_err_kind_734 = 0;
        (void)_forin_err_kind_734;
        OutOfBounds *_forin_OutOfBounds_734 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_734->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_734;
        while (1) {
            U32 hoisted__U32_744 = Array__Str_len(_fc_Array__Str_734);
            (void)hoisted__U32_744;
            Bool _wcond_Bool_735 = U32_lt(_fi_USize_734, hoisted__U32_744);
            (void)_wcond_Bool_735;
            if (_wcond_Bool_735) {
            } else {
                break;
            }
            static Str hoisted__Str_745 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
            (void)hoisted__Str_745;
            Str *s = Array__Str_get(_fc_Array__Str_734, &_fi_USize_734, &_forin_err_kind_734, _forin_OutOfBounds_734, &hoisted__Str_745);
            I64 hoisted__I64_746 = 0;
            (void)hoisted__I64_746;
            Bool hoisted__Bool_747 = I64_eq(_forin_err_kind_734, hoisted__I64_746);
            (void)hoisted__Bool_747;
            Bool hoisted__Bool_748 = not(hoisted__Bool_747);
            (void)hoisted__Bool_748;
            if (hoisted__Bool_748) {
                U32 hoisted__U32_736 = 2;
                (void)hoisted__U32_736;
                Array__Str *_va_Array_17 = Array__Str_new(hoisted__U32_736);
                (void)_va_Array_17;
                I64 _va_Array_17_ek = 0;
                (void)_va_Array_17_ek;
                OutOfBounds *_va_Array_17_eo = malloc(sizeof(OutOfBounds));
                _va_Array_17_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_17_eo;
                U32 hoisted__U32_737 = 0;
                (void)hoisted__U32_737;
                static Str hoisted__Str_738 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_738;
                static Str hoisted__Str_739 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_739;
                Array__Str_set(_va_Array_17, hoisted__U32_737, &hoisted__Str_738, &_va_Array_17_ek, _va_Array_17_eo, &hoisted__Str_739);
                Str_delete(&hoisted__Str_739, (Bool){0});
                U32 hoisted__U32_740 = 1;
                (void)hoisted__U32_740;
                static Str hoisted__Str_741 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_741;
                static Str hoisted__Str_742 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_742;
                Array__Str_set(_va_Array_17, hoisted__U32_740, &hoisted__Str_741, &_va_Array_17_ek, _va_Array_17_eo, &hoisted__Str_742);
                OutOfBounds_delete(_va_Array_17_eo, 1);
                Str_delete(&hoisted__Str_742, (Bool){0});
                static Str hoisted__Str_743 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_743;
                panic(_va_Array_17, &hoisted__Str_743);
                Str_delete(&hoisted__Str_743, (Bool){0});
            }
            U32 hoisted__U32_749 = 1;
            (void)hoisted__U32_749;
            U32 hoisted__U32_750 = U32_add(_fi_USize_734, hoisted__U32_749);
            (void)hoisted__U32_750;
            _fi_USize_734 = hoisted__U32_750;
            U32 hoisted__U32_751 = Str_len(s);
            (void)hoisted__U32_751;
            Str_delete(&hoisted__Str_745, (Bool){0});
            U32 hoisted__U32_752 = U32_add(total, hoisted__U32_751);
            (void)hoisted__U32_752;
            total = hoisted__U32_752;
        }
        OutOfBounds_delete(_forin_OutOfBounds_734, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_753 = parts;
        (void)_fc_Array__Str_753;
        (void)_fc_Array__Str_753;
        U32 _fi_USize_753 = 0;
        (void)_fi_USize_753;
        I64 _forin_err_kind_753 = 0;
        (void)_forin_err_kind_753;
        OutOfBounds *_forin_OutOfBounds_753 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_753->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_753;
        while (1) {
            U32 hoisted__U32_763 = Array__Str_len(_fc_Array__Str_753);
            (void)hoisted__U32_763;
            Bool _wcond_Bool_754 = U32_lt(_fi_USize_753, hoisted__U32_763);
            (void)_wcond_Bool_754;
            if (_wcond_Bool_754) {
            } else {
                break;
            }
            static Str hoisted__Str_764 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
            (void)hoisted__Str_764;
            Str *s = Array__Str_get(_fc_Array__Str_753, &_fi_USize_753, &_forin_err_kind_753, _forin_OutOfBounds_753, &hoisted__Str_764);
            I64 hoisted__I64_765 = 0;
            (void)hoisted__I64_765;
            Bool hoisted__Bool_766 = I64_eq(_forin_err_kind_753, hoisted__I64_765);
            (void)hoisted__Bool_766;
            Bool hoisted__Bool_767 = not(hoisted__Bool_766);
            (void)hoisted__Bool_767;
            if (hoisted__Bool_767) {
                U32 hoisted__U32_755 = 2;
                (void)hoisted__U32_755;
                Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_755);
                (void)_va_Array_18;
                I64 _va_Array_18_ek = 0;
                (void)_va_Array_18_ek;
                OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
                _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_18_eo;
                U32 hoisted__U32_756 = 0;
                (void)hoisted__U32_756;
                static Str hoisted__Str_757 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_757;
                static Str hoisted__Str_758 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_758;
                Array__Str_set(_va_Array_18, hoisted__U32_756, &hoisted__Str_757, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_758);
                Str_delete(&hoisted__Str_758, (Bool){0});
                U32 hoisted__U32_759 = 1;
                (void)hoisted__U32_759;
                static Str hoisted__Str_760 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_760;
                static Str hoisted__Str_761 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_761;
                Array__Str_set(_va_Array_18, hoisted__U32_759, &hoisted__Str_760, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_761);
                OutOfBounds_delete(_va_Array_18_eo, 1);
                Str_delete(&hoisted__Str_761, (Bool){0});
                static Str hoisted__Str_762 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_762;
                panic(_va_Array_18, &hoisted__Str_762);
                Str_delete(&hoisted__Str_762, (Bool){0});
            }
            U32 hoisted__U32_768 = 1;
            (void)hoisted__U32_768;
            U32 hoisted__U32_769 = U32_add(_fi_USize_753, hoisted__U32_768);
            (void)hoisted__U32_769;
            _fi_USize_753 = hoisted__U32_769;
            Str_push_str(out, s);
            Str_delete(&hoisted__Str_764, (Bool){0});
        }
        OutOfBounds_delete(_forin_OutOfBounds_753, 1);
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_775 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_775;
    if (hoisted__Bool_775) {
        U32 hoisted__U32_770 = 1;
        (void)hoisted__U32_770;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_770);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_771 = 0;
        (void)hoisted__U32_771;
        static Str hoisted__Str_772 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_772;
        static Str hoisted__Str_773 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_773;
        Array__Str_set(_va_Array_19, hoisted__U32_771, &hoisted__Str_772, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_773);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_773, (Bool){0});
        static Str hoisted__Str_774 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_774;
        panic(_va_Array_19, &hoisted__Str_774);
        Str_delete(&hoisted__Str_774, (Bool){0});
    }
    void *hoisted__v_776 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_776;
    (void)hoisted__v_776;
    return hoisted__v_776;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_786 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_786;
    if (hoisted__Bool_786) {
        min_len = b->count;
    }
    {
        U32 _re_U32_778 = U32_clone(&min_len);
        (void)_re_U32_778;
        U32 _rc_U32_778 = 0;
        (void)_rc_U32_778;
        Bool hoisted__Bool_785 = U32_lte(_rc_U32_778, _re_U32_778);
        (void)hoisted__Bool_785;
        if (hoisted__Bool_785) {
            while (1) {
                Bool _wcond_Bool_779 = U32_lt(_rc_U32_778, _re_U32_778);
                (void)_wcond_Bool_779;
                if (_wcond_Bool_779) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_778);
                U32_inc(&_rc_U32_778);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_780 = 0;
                (void)hoisted__I64_780;
                Bool hoisted__Bool_781 = I64_neq(c, hoisted__I64_780);
                (void)hoisted__Bool_781;
                if (hoisted__Bool_781) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_782 = U32_gt(_rc_U32_778, _re_U32_778);
                (void)_wcond_Bool_782;
                if (_wcond_Bool_782) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_778);
                U32_dec(&_rc_U32_778);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_783 = 0;
                (void)hoisted__I64_783;
                Bool hoisted__Bool_784 = I64_neq(c, hoisted__I64_783);
                (void)hoisted__Bool_784;
                if (hoisted__Bool_784) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_787 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_787;
    return hoisted__I64_787;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_788 = 1;
    (void)hoisted__U32_788;
    U32 hoisted__U64_789 = U32_add(n, hoisted__U32_788);
    (void)hoisted__U64_789;
    void * buf = malloc(hoisted__U64_789);
    I32 hoisted__I32_790 = 0;
    (void)hoisted__I32_790;
    U64 hoisted__U64_791 = 1ULL;
    (void)hoisted__U64_791;
    memset(buf, hoisted__I32_790, hoisted__U64_791);
    I64 hoisted__I64_792 = 0;
    (void)hoisted__I64_792;
    Str *hoisted__Str_793 = malloc(sizeof(Str));
    hoisted__Str_793->c_str = buf;
    hoisted__Str_793->count = hoisted__I64_792;
    hoisted__Str_793->cap = n;
    (void)hoisted__Str_793;
    return hoisted__Str_793;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_806 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_806;
    if (hoisted__Bool_806) {
        U32 hoisted__U32_796 = 1;
        (void)hoisted__U32_796;
        Array__Str *_va_Array_20 = Array__Str_new(hoisted__U32_796);
        (void)_va_Array_20;
        I64 _va_Array_20_ek = 0;
        (void)_va_Array_20_ek;
        OutOfBounds *_va_Array_20_eo = malloc(sizeof(OutOfBounds));
        _va_Array_20_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_20_eo;
        U32 hoisted__U32_797 = 0;
        (void)hoisted__U32_797;
        static Str hoisted__Str_798 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_798;
        static Str hoisted__Str_799 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_799;
        Array__Str_set(_va_Array_20, hoisted__U32_797, &hoisted__Str_798, &_va_Array_20_ek, _va_Array_20_eo, &hoisted__Str_799);
        OutOfBounds_delete(_va_Array_20_eo, 1);
        Str_delete(&hoisted__Str_799, (Bool){0});
        static Str hoisted__Str_800 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_800;
        panic(_va_Array_20, &hoisted__Str_800);
        Str_delete(&hoisted__Str_800, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_807 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_807;
    if (hoisted__Bool_807) {
        U32 hoisted__U32_801 = 1;
        (void)hoisted__U32_801;
        Array__Str *_va_Array_21 = Array__Str_new(hoisted__U32_801);
        (void)_va_Array_21;
        I64 _va_Array_21_ek = 0;
        (void)_va_Array_21_ek;
        OutOfBounds *_va_Array_21_eo = malloc(sizeof(OutOfBounds));
        _va_Array_21_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_21_eo;
        U32 hoisted__U32_802 = 0;
        (void)hoisted__U32_802;
        static Str hoisted__Str_803 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_803;
        static Str hoisted__Str_804 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_804;
        Array__Str_set(_va_Array_21, hoisted__U32_802, &hoisted__Str_803, &_va_Array_21_ek, _va_Array_21_eo, &hoisted__Str_804);
        OutOfBounds_delete(_va_Array_21_eo, 1);
        Str_delete(&hoisted__Str_804, (Bool){0});
        static Str hoisted__Str_805 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_805;
        panic(_va_Array_21, &hoisted__Str_805);
        Str_delete(&hoisted__Str_805, (Bool){0});
    }
    void *hoisted__v_808 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_808;
    (void)hoisted__v_808;
    memcpy(hoisted__v_808, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_809 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_809;
    (void)hoisted__v_809;
    I32 hoisted__I32_810 = 0;
    (void)hoisted__I32_810;
    U64 hoisted__U64_811 = 1ULL;
    (void)hoisted__U64_811;
    memset(hoisted__v_809, hoisted__I32_810, hoisted__U64_811);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_812 = 1;
    (void)hoisted__U32_812;
    U32 hoisted__U64_813 = U32_add(val->count, hoisted__U32_812);
    (void)hoisted__U64_813;
    void * new_data = malloc(hoisted__U64_813);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_814 = ptr_add(new_data, val->count);
    (void)hoisted__v_814;
    (void)hoisted__v_814;
    I32 hoisted__I32_815 = 0;
    (void)hoisted__I32_815;
    U64 hoisted__U64_816 = 1ULL;
    (void)hoisted__U64_816;
    memset(hoisted__v_814, hoisted__I32_815, hoisted__U64_816);
    Str *hoisted__Str_817 = malloc(sizeof(Str));
    hoisted__Str_817->c_str = new_data;
    hoisted__Str_817->count = val->count;
    hoisted__Str_817->cap = val->count;
    (void)hoisted__Str_817;
    return hoisted__Str_817;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_818 = Str_clone(self);
    (void)hoisted__Str_818;
    return hoisted__Str_818;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_819 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_819;
    if (hoisted__Bool_819) {
        free(self->c_str);
    }
    Bool hoisted__Bool_820 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_820;
    Bool hoisted__Bool_821 = and(call_free, hoisted__Bool_820);
    (void)hoisted__Bool_821;
    if (hoisted__Bool_821) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1016 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_1016;
    return hoisted__U64_1016;
}

U32 Str_size(void) {
    U32 hoisted__U32_1201 = 16;
    (void)hoisted__U32_1201;
    return hoisted__U32_1201;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1202 = Str_cmp(a, b);
    (void)hoisted__I64_1202;
    I64 hoisted__I64_1203 = 0;
    (void)hoisted__I64_1203;
    Bool hoisted__Bool_1204 = I64_eq(hoisted__I64_1202, hoisted__I64_1203);
    (void)hoisted__Bool_1204;
    return hoisted__Bool_1204;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1213 = Str_eq(a, b);
    (void)hoisted__Bool_1213;
    Bool hoisted__Bool_1214 = not(hoisted__Bool_1213);
    (void)hoisted__Bool_1214;
    return hoisted__Bool_1214;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1318 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1318->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1318;
    return hoisted__OutOfBounds_1318;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1319 = 0;
    (void)hoisted__Bool_1319;
    Str_delete(&self->msg, hoisted__Bool_1319);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1320 = 0;
    (void)hoisted__U32_1320;
    U64 hoisted__U64_1321 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1320); });
    (void)hoisted__U64_1321;
    return hoisted__U64_1321;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1340 = 16;
    (void)hoisted__U32_1340;
    return hoisted__U32_1340;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1364 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1364;
    U32 hoisted__U32_1365 = 16;
    (void)hoisted__U32_1365;
    Type *hoisted__Type_1366 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1366;
    U64 hoisted__U64_1367 = (U64)(cap);
    (void)hoisted__U64_1367;
    Type_delete(hoisted__Type_1364, 1);
    U64 hoisted__U64_1368 = (U64)(hoisted__U32_1365);
    (void)hoisted__U64_1368;
    Type_delete(hoisted__Type_1366, 1);
    void * hoisted__v_1369 = calloc(hoisted__U64_1367, hoisted__U64_1368);
    (void)hoisted__v_1369;
    Array__Str *hoisted__Array__Str_1370 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1370->data = hoisted__v_1369;
    hoisted__Array__Str_1370->cap = cap;
    (void)hoisted__Array__Str_1370;
    return hoisted__Array__Str_1370;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1398 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1398;
    if (hoisted__Bool_1398) {
        U32 hoisted__U32_1371 = 6;
        (void)hoisted__U32_1371;
        Array__Str *_va_Array_33 = Array__Str_new(hoisted__U32_1371);
        (void)_va_Array_33;
        I64 _va_Array_33_ek = 0;
        (void)_va_Array_33_ek;
        OutOfBounds *_va_Array_33_eo = malloc(sizeof(OutOfBounds));
        _va_Array_33_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_33_eo;
        U32 hoisted__U32_1372 = 0;
        (void)hoisted__U32_1372;
        Str *hoisted__Str_1373 = Str_clone(loc);
        (void)hoisted__Str_1373;
        static Str hoisted__Str_1374 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1374;
        Array__Str_set(_va_Array_33, hoisted__U32_1372, hoisted__Str_1373, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1374);
        Str_delete(&hoisted__Str_1374, (Bool){0});
        U32 hoisted__U32_1375 = 1;
        (void)hoisted__U32_1375;
        static Str hoisted__Str_1376 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1376;
        static Str hoisted__Str_1377 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1377;
        Array__Str_set(_va_Array_33, hoisted__U32_1375, &hoisted__Str_1376, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1377);
        Str_delete(&hoisted__Str_1377, (Bool){0});
        U32 hoisted__U32_1378 = 2;
        (void)hoisted__U32_1378;
        Str *hoisted__Str_1379 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1379;
        static Str hoisted__Str_1380 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1380;
        Array__Str_set(_va_Array_33, hoisted__U32_1378, hoisted__Str_1379, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1380);
        Str_delete(&hoisted__Str_1380, (Bool){0});
        U32 hoisted__U32_1381 = 3;
        (void)hoisted__U32_1381;
        static Str hoisted__Str_1382 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1382;
        static Str hoisted__Str_1383 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1383;
        Array__Str_set(_va_Array_33, hoisted__U32_1381, &hoisted__Str_1382, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1383);
        Str_delete(&hoisted__Str_1383, (Bool){0});
        U32 hoisted__U32_1384 = 4;
        (void)hoisted__U32_1384;
        Str *hoisted__Str_1385 = U32_to_str(self->cap);
        (void)hoisted__Str_1385;
        static Str hoisted__Str_1386 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1386;
        Array__Str_set(_va_Array_33, hoisted__U32_1384, hoisted__Str_1385, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1386);
        Str_delete(&hoisted__Str_1386, (Bool){0});
        U32 hoisted__U32_1387 = 5;
        (void)hoisted__U32_1387;
        static Str hoisted__Str_1388 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1388;
        static Str hoisted__Str_1389 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1389;
        Array__Str_set(_va_Array_33, hoisted__U32_1387, &hoisted__Str_1388, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1389);
        OutOfBounds_delete(_va_Array_33_eo, 1);
        Str_delete(&hoisted__Str_1389, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1390 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_33); hoisted__OutOfBounds_1390->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1390;
        U32 hoisted__U32_1391 = 16;
        (void)hoisted__U32_1391;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1390, hoisted__U32_1391);
        OutOfBounds_delete(hoisted__OutOfBounds_1390, 1);
        I64 hoisted__I64_1392 = 3;
        (void)hoisted__I64_1392;
        *_err_kind = hoisted__I64_1392;
    }
    I64 hoisted__I64_1399 = 0;
    (void)hoisted__I64_1399;
    Bool hoisted__Bool_1400 = I64_eq(DEREF(_err_kind), hoisted__I64_1399);
    (void)hoisted__Bool_1400;
    if (hoisted__Bool_1400) {
        U32 hoisted__U32_1393 = 16;
        (void)hoisted__U32_1393;
        U32 hoisted__U32_1394 = U32_mul(DEREF(i), hoisted__U32_1393);
        (void)hoisted__U32_1394;
        Type *hoisted__Type_1395 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1395;
        U64 hoisted__U64_1396 = (U64)(hoisted__U32_1394);
        (void)hoisted__U64_1396;
        Type_delete(hoisted__Type_1395, 1);
        void *hoisted__v_1397 = ptr_add(self->data, hoisted__U64_1396);
        (void)hoisted__v_1397;
        (void)hoisted__v_1397;
        { Str * _ret_val = hoisted__v_1397;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1441 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1441;
    if (hoisted__Bool_1441) {
        U32 hoisted__U32_1401 = 6;
        (void)hoisted__U32_1401;
        Array__Str *_va_Array_34 = Array__Str_new(hoisted__U32_1401);
        (void)_va_Array_34;
        I64 _va_Array_34_ek = 0;
        (void)_va_Array_34_ek;
        OutOfBounds *_va_Array_34_eo = malloc(sizeof(OutOfBounds));
        _va_Array_34_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_34_eo;
        U32 hoisted__U32_1402 = 0;
        (void)hoisted__U32_1402;
        Str *hoisted__Str_1403 = Str_clone(loc);
        (void)hoisted__Str_1403;
        static Str hoisted__Str_1404 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1404;
        Array__Str_set(_va_Array_34, hoisted__U32_1402, hoisted__Str_1403, &_va_Array_34_ek, _va_Array_34_eo, &hoisted__Str_1404);
        Str_delete(&hoisted__Str_1404, (Bool){0});
        U32 hoisted__U32_1405 = 1;
        (void)hoisted__U32_1405;
        static Str hoisted__Str_1406 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1406;
        static Str hoisted__Str_1407 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1407;
        Array__Str_set(_va_Array_34, hoisted__U32_1405, &hoisted__Str_1406, &_va_Array_34_ek, _va_Array_34_eo, &hoisted__Str_1407);
        Str_delete(&hoisted__Str_1407, (Bool){0});
        U32 hoisted__U32_1408 = 2;
        (void)hoisted__U32_1408;
        Str *hoisted__Str_1409 = U32_to_str(i);
        (void)hoisted__Str_1409;
        static Str hoisted__Str_1410 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1410;
        Array__Str_set(_va_Array_34, hoisted__U32_1408, hoisted__Str_1409, &_va_Array_34_ek, _va_Array_34_eo, &hoisted__Str_1410);
        Str_delete(&hoisted__Str_1410, (Bool){0});
        U32 hoisted__U32_1411 = 3;
        (void)hoisted__U32_1411;
        static Str hoisted__Str_1412 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1412;
        static Str hoisted__Str_1413 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1413;
        Array__Str_set(_va_Array_34, hoisted__U32_1411, &hoisted__Str_1412, &_va_Array_34_ek, _va_Array_34_eo, &hoisted__Str_1413);
        Str_delete(&hoisted__Str_1413, (Bool){0});
        U32 hoisted__U32_1414 = 4;
        (void)hoisted__U32_1414;
        Str *hoisted__Str_1415 = U32_to_str(self->cap);
        (void)hoisted__Str_1415;
        static Str hoisted__Str_1416 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1416;
        Array__Str_set(_va_Array_34, hoisted__U32_1414, hoisted__Str_1415, &_va_Array_34_ek, _va_Array_34_eo, &hoisted__Str_1416);
        Str_delete(&hoisted__Str_1416, (Bool){0});
        U32 hoisted__U32_1417 = 5;
        (void)hoisted__U32_1417;
        static Str hoisted__Str_1418 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1418;
        static Str hoisted__Str_1419 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1419;
        Array__Str_set(_va_Array_34, hoisted__U32_1417, &hoisted__Str_1418, &_va_Array_34_ek, _va_Array_34_eo, &hoisted__Str_1419);
        OutOfBounds_delete(_va_Array_34_eo, 1);
        Str_delete(&hoisted__Str_1419, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1420 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_34); hoisted__OutOfBounds_1420->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1420;
        U32 hoisted__U32_1421 = 16;
        (void)hoisted__U32_1421;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1420, hoisted__U32_1421);
        OutOfBounds_delete(hoisted__OutOfBounds_1420, 1);
        I64 hoisted__I64_1422 = 3;
        (void)hoisted__I64_1422;
        *_err_kind = hoisted__I64_1422;
    }
    I64 hoisted__I64_1442 = 0;
    (void)hoisted__I64_1442;
    Bool hoisted__Bool_1443 = I64_eq(DEREF(_err_kind), hoisted__I64_1442);
    (void)hoisted__Bool_1443;
    if (hoisted__Bool_1443) {
        U32 hoisted__U32_1423 = 16;
        (void)hoisted__U32_1423;
        U32 hoisted__U32_1424 = U32_mul(i, hoisted__U32_1423);
        (void)hoisted__U32_1424;
        Type *hoisted__Type_1425 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1425;
        U64 hoisted__U64_1426 = (U64)(hoisted__U32_1424);
        (void)hoisted__U64_1426;
        Type_delete(hoisted__Type_1425, 1);
        Str *hoisted__Str_1427 = ptr_add(self->data, hoisted__U64_1426);
        (void)hoisted__Str_1427;
        (void)hoisted__Str_1427;
        Bool hoisted__Bool_1428 = 0;
        (void)hoisted__Bool_1428;
        Str_delete(hoisted__Str_1427, hoisted__Bool_1428);
        U32 hoisted__U32_1429 = 16;
        (void)hoisted__U32_1429;
        U32 hoisted__U32_1430 = U32_mul(i, hoisted__U32_1429);
        (void)hoisted__U32_1430;
        Type *hoisted__Type_1431 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1431;
        U64 hoisted__U64_1432 = (U64)(hoisted__U32_1430);
        (void)hoisted__U64_1432;
        Type_delete(hoisted__Type_1431, 1);
        U32 hoisted__U32_1433 = 16;
        (void)hoisted__U32_1433;
        Type *hoisted__Type_1434 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1434;
        void *hoisted__v_1435 = ptr_add(self->data, hoisted__U64_1432);
        (void)hoisted__v_1435;
        (void)hoisted__v_1435;
        U64 hoisted__U64_1436 = (U64)(hoisted__U32_1433);
        (void)hoisted__U64_1436;
        Type_delete(hoisted__Type_1434, 1);
        memcpy(hoisted__v_1435, val, hoisted__U64_1436);
        U32 hoisted__U32_1437 = 16;
        (void)hoisted__U32_1437;
        Type *hoisted__Type_1438 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1438;
        I32 hoisted__I32_1439 = 0;
        (void)hoisted__I32_1439;
        U64 hoisted__U64_1440 = (U64)(hoisted__U32_1437);
        (void)hoisted__U64_1440;
        Type_delete(hoisted__Type_1438, 1);
        if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1439, hoisted__U64_1440); };
    }
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1444 = self->cap;
        (void)_re_U32_1444;
        U32 _rc_U32_1444 = 0;
        (void)_rc_U32_1444;
        Bool hoisted__Bool_1459 = U32_lte(_rc_U32_1444, _re_U32_1444);
        (void)hoisted__Bool_1459;
        if (hoisted__Bool_1459) {
            while (1) {
                Bool _wcond_Bool_1445 = U32_lt(_rc_U32_1444, _re_U32_1444);
                (void)_wcond_Bool_1445;
                if (_wcond_Bool_1445) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1444);
                U32_inc(&_rc_U32_1444);
                U32 hoisted__U32_1446 = 16;
                (void)hoisted__U32_1446;
                U32 hoisted__U32_1447 = U32_mul(i, hoisted__U32_1446);
                (void)hoisted__U32_1447;
                Type *hoisted__Type_1448 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1448;
                U64 hoisted__U64_1449 = (U64)(hoisted__U32_1447);
                (void)hoisted__U64_1449;
                Type_delete(hoisted__Type_1448, 1);
                Str *hoisted__Str_1450 = ptr_add(self->data, hoisted__U64_1449);
                (void)hoisted__Str_1450;
                (void)hoisted__Str_1450;
                Bool hoisted__Bool_1451 = 0;
                (void)hoisted__Bool_1451;
                Str_delete(hoisted__Str_1450, hoisted__Bool_1451);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1452 = U32_gt(_rc_U32_1444, _re_U32_1444);
                (void)_wcond_Bool_1452;
                if (_wcond_Bool_1452) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1444);
                U32_dec(&_rc_U32_1444);
                U32 hoisted__U32_1453 = 16;
                (void)hoisted__U32_1453;
                U32 hoisted__U32_1454 = U32_mul(i, hoisted__U32_1453);
                (void)hoisted__U32_1454;
                Type *hoisted__Type_1455 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1455;
                U64 hoisted__U64_1456 = (U64)(hoisted__U32_1454);
                (void)hoisted__U64_1456;
                Type_delete(hoisted__Type_1455, 1);
                Str *hoisted__Str_1457 = ptr_add(self->data, hoisted__U64_1456);
                (void)hoisted__Str_1457;
                (void)hoisted__Str_1457;
                Bool hoisted__Bool_1458 = 0;
                (void)hoisted__Bool_1458;
                Str_delete(hoisted__Str_1457, hoisted__Bool_1458);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1496 = 16;
    (void)hoisted__U32_1496;
    U32 hoisted__U32_1497 = U32_mul(self->cap, hoisted__U32_1496);
    (void)hoisted__U32_1497;
    Type *hoisted__Type_1498 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1498;
    U64 hoisted__U64_1499 = (U64)(hoisted__U32_1497);
    (void)hoisted__U64_1499;
    Type_delete(hoisted__Type_1498, 1);
    void * new_data = malloc(hoisted__U64_1499);
    {
        U32 _re_U32_1460 = self->cap;
        (void)_re_U32_1460;
        U32 _rc_U32_1460 = 0;
        (void)_rc_U32_1460;
        Bool hoisted__Bool_1495 = U32_lte(_rc_U32_1460, _re_U32_1460);
        (void)hoisted__Bool_1495;
        if (hoisted__Bool_1495) {
            while (1) {
                Bool _wcond_Bool_1461 = U32_lt(_rc_U32_1460, _re_U32_1460);
                (void)_wcond_Bool_1461;
                if (_wcond_Bool_1461) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1460);
                U32_inc(&_rc_U32_1460);
                U32 hoisted__U32_1462 = 16;
                (void)hoisted__U32_1462;
                U32 hoisted__U32_1463 = U32_mul(i, hoisted__U32_1462);
                (void)hoisted__U32_1463;
                Type *hoisted__Type_1464 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1464;
                U64 hoisted__U64_1465 = (U64)(hoisted__U32_1463);
                (void)hoisted__U64_1465;
                Type_delete(hoisted__Type_1464, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1465);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1466 = 16;
                (void)hoisted__U32_1466;
                U32 hoisted__U32_1467 = U32_mul(i, hoisted__U32_1466);
                (void)hoisted__U32_1467;
                Type *hoisted__Type_1468 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1468;
                U64 hoisted__U64_1469 = (U64)(hoisted__U32_1467);
                (void)hoisted__U64_1469;
                Type_delete(hoisted__Type_1468, 1);
                U32 hoisted__U32_1470 = 16;
                (void)hoisted__U32_1470;
                Type *hoisted__Type_1471 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1471;
                void *hoisted__v_1472 = ptr_add(new_data, hoisted__U64_1469);
                (void)hoisted__v_1472;
                (void)hoisted__v_1472;
                U64 hoisted__U64_1473 = (U64)(hoisted__U32_1470);
                (void)hoisted__U64_1473;
                Type_delete(hoisted__Type_1471, 1);
                memcpy(hoisted__v_1472, cloned, hoisted__U64_1473);
                U32 hoisted__U32_1474 = 16;
                (void)hoisted__U32_1474;
                Type *hoisted__Type_1475 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1475;
                I32 hoisted__I32_1476 = 0;
                (void)hoisted__I32_1476;
                U64 hoisted__U64_1477 = (U64)(hoisted__U32_1474);
                (void)hoisted__U64_1477;
                Type_delete(hoisted__Type_1475, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1476, hoisted__U64_1477); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1478 = U32_gt(_rc_U32_1460, _re_U32_1460);
                (void)_wcond_Bool_1478;
                if (_wcond_Bool_1478) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1460);
                U32_dec(&_rc_U32_1460);
                U32 hoisted__U32_1479 = 16;
                (void)hoisted__U32_1479;
                U32 hoisted__U32_1480 = U32_mul(i, hoisted__U32_1479);
                (void)hoisted__U32_1480;
                Type *hoisted__Type_1481 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1481;
                U64 hoisted__U64_1482 = (U64)(hoisted__U32_1480);
                (void)hoisted__U64_1482;
                Type_delete(hoisted__Type_1481, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1482);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1483 = 16;
                (void)hoisted__U32_1483;
                U32 hoisted__U32_1484 = U32_mul(i, hoisted__U32_1483);
                (void)hoisted__U32_1484;
                Type *hoisted__Type_1485 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1485;
                U64 hoisted__U64_1486 = (U64)(hoisted__U32_1484);
                (void)hoisted__U64_1486;
                Type_delete(hoisted__Type_1485, 1);
                U32 hoisted__U32_1487 = 16;
                (void)hoisted__U32_1487;
                Type *hoisted__Type_1488 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1488;
                void *hoisted__v_1489 = ptr_add(new_data, hoisted__U64_1486);
                (void)hoisted__v_1489;
                (void)hoisted__v_1489;
                U64 hoisted__U64_1490 = (U64)(hoisted__U32_1487);
                (void)hoisted__U64_1490;
                Type_delete(hoisted__Type_1488, 1);
                memcpy(hoisted__v_1489, cloned, hoisted__U64_1490);
                U32 hoisted__U32_1491 = 16;
                (void)hoisted__U32_1491;
                Type *hoisted__Type_1492 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1492;
                I32 hoisted__I32_1493 = 0;
                (void)hoisted__I32_1493;
                U64 hoisted__U64_1494 = (U64)(hoisted__U32_1491);
                (void)hoisted__U64_1494;
                Type_delete(hoisted__Type_1492, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1493, hoisted__U64_1494); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1500 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1500->data = new_data;
    hoisted__Array__Str_1500->cap = self->cap;
    (void)hoisted__Array__Str_1500;
    return hoisted__Array__Str_1500;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1501 = 16;
    (void)hoisted__U32_1501;
    return hoisted__U32_1501;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1502 = 16;
    (void)hoisted__U32_1502;
    Type *hoisted__Type_1503 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1503;
    U64 hoisted__U64_1504 = (U64)(hoisted__U32_1502);
    (void)hoisted__U64_1504;
    Type_delete(hoisted__Type_1503, 1);
    void * hoisted__v_1505 = malloc(hoisted__U64_1504);
    (void)hoisted__v_1505;
    U32 hoisted__U32_1506 = 0;
    (void)hoisted__U32_1506;
    I64 hoisted__I64_1507 = 1;
    (void)hoisted__I64_1507;
    Vec__Str *hoisted__Vec__Str_1508 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1508->data = hoisted__v_1505;
    hoisted__Vec__Str_1508->count = hoisted__U32_1506;
    hoisted__Vec__Str_1508->cap = hoisted__I64_1507;
    (void)hoisted__Vec__Str_1508;
    return hoisted__Vec__Str_1508;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1509 = self->count;
        (void)_re_U32_1509;
        U32 _rc_U32_1509 = 0;
        (void)_rc_U32_1509;
        Bool hoisted__Bool_1524 = U32_lte(_rc_U32_1509, _re_U32_1509);
        (void)hoisted__Bool_1524;
        if (hoisted__Bool_1524) {
            while (1) {
                Bool _wcond_Bool_1510 = U32_lt(_rc_U32_1509, _re_U32_1509);
                (void)_wcond_Bool_1510;
                if (_wcond_Bool_1510) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1509);
                U32_inc(&_rc_U32_1509);
                U32 hoisted__U32_1511 = 16;
                (void)hoisted__U32_1511;
                U32 hoisted__U32_1512 = U32_mul(i, hoisted__U32_1511);
                (void)hoisted__U32_1512;
                Type *hoisted__Type_1513 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1513;
                U64 hoisted__U64_1514 = (U64)(hoisted__U32_1512);
                (void)hoisted__U64_1514;
                Type_delete(hoisted__Type_1513, 1);
                Str *hoisted__Str_1515 = ptr_add(self->data, hoisted__U64_1514);
                (void)hoisted__Str_1515;
                (void)hoisted__Str_1515;
                Bool hoisted__Bool_1516 = 0;
                (void)hoisted__Bool_1516;
                Str_delete(hoisted__Str_1515, hoisted__Bool_1516);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1517 = U32_gt(_rc_U32_1509, _re_U32_1509);
                (void)_wcond_Bool_1517;
                if (_wcond_Bool_1517) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1509);
                U32_dec(&_rc_U32_1509);
                U32 hoisted__U32_1518 = 16;
                (void)hoisted__U32_1518;
                U32 hoisted__U32_1519 = U32_mul(i, hoisted__U32_1518);
                (void)hoisted__U32_1519;
                Type *hoisted__Type_1520 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1520;
                U64 hoisted__U64_1521 = (U64)(hoisted__U32_1519);
                (void)hoisted__U64_1521;
                Type_delete(hoisted__Type_1520, 1);
                Str *hoisted__Str_1522 = ptr_add(self->data, hoisted__U64_1521);
                (void)hoisted__Str_1522;
                (void)hoisted__Str_1522;
                Bool hoisted__Bool_1523 = 0;
                (void)hoisted__Bool_1523;
                Str_delete(hoisted__Str_1522, hoisted__Bool_1523);
            }
        }
    }
    U32 hoisted__U32_1525 = 0;
    (void)hoisted__U32_1525;
    self->count = hoisted__U32_1525;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1841 = 16;
    (void)hoisted__U32_1841;
    U32 hoisted__U32_1842 = U32_mul(self->cap, hoisted__U32_1841);
    (void)hoisted__U32_1842;
    Type *hoisted__Type_1843 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1843;
    U64 hoisted__U64_1844 = (U64)(hoisted__U32_1842);
    (void)hoisted__U64_1844;
    Type_delete(hoisted__Type_1843, 1);
    void * new_data = malloc(hoisted__U64_1844);
    {
        U32 _re_U32_1805 = self->count;
        (void)_re_U32_1805;
        U32 _rc_U32_1805 = 0;
        (void)_rc_U32_1805;
        Bool hoisted__Bool_1840 = U32_lte(_rc_U32_1805, _re_U32_1805);
        (void)hoisted__Bool_1840;
        if (hoisted__Bool_1840) {
            while (1) {
                Bool _wcond_Bool_1806 = U32_lt(_rc_U32_1805, _re_U32_1805);
                (void)_wcond_Bool_1806;
                if (_wcond_Bool_1806) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1805);
                U32_inc(&_rc_U32_1805);
                U32 hoisted__U32_1807 = 16;
                (void)hoisted__U32_1807;
                U32 hoisted__U32_1808 = U32_mul(i, hoisted__U32_1807);
                (void)hoisted__U32_1808;
                Type *hoisted__Type_1809 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1809;
                U64 hoisted__U64_1810 = (U64)(hoisted__U32_1808);
                (void)hoisted__U64_1810;
                Type_delete(hoisted__Type_1809, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1810);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1811 = 16;
                (void)hoisted__U32_1811;
                U32 hoisted__U32_1812 = U32_mul(i, hoisted__U32_1811);
                (void)hoisted__U32_1812;
                Type *hoisted__Type_1813 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1813;
                U64 hoisted__U64_1814 = (U64)(hoisted__U32_1812);
                (void)hoisted__U64_1814;
                Type_delete(hoisted__Type_1813, 1);
                U32 hoisted__U32_1815 = 16;
                (void)hoisted__U32_1815;
                Type *hoisted__Type_1816 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1816;
                void *hoisted__v_1817 = ptr_add(new_data, hoisted__U64_1814);
                (void)hoisted__v_1817;
                (void)hoisted__v_1817;
                U64 hoisted__U64_1818 = (U64)(hoisted__U32_1815);
                (void)hoisted__U64_1818;
                Type_delete(hoisted__Type_1816, 1);
                memcpy(hoisted__v_1817, cloned, hoisted__U64_1818);
                U32 hoisted__U32_1819 = 16;
                (void)hoisted__U32_1819;
                Type *hoisted__Type_1820 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1820;
                I32 hoisted__I32_1821 = 0;
                (void)hoisted__I32_1821;
                U64 hoisted__U64_1822 = (U64)(hoisted__U32_1819);
                (void)hoisted__U64_1822;
                Type_delete(hoisted__Type_1820, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1821, hoisted__U64_1822); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1823 = U32_gt(_rc_U32_1805, _re_U32_1805);
                (void)_wcond_Bool_1823;
                if (_wcond_Bool_1823) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1805);
                U32_dec(&_rc_U32_1805);
                U32 hoisted__U32_1824 = 16;
                (void)hoisted__U32_1824;
                U32 hoisted__U32_1825 = U32_mul(i, hoisted__U32_1824);
                (void)hoisted__U32_1825;
                Type *hoisted__Type_1826 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1826;
                U64 hoisted__U64_1827 = (U64)(hoisted__U32_1825);
                (void)hoisted__U64_1827;
                Type_delete(hoisted__Type_1826, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1827);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1828 = 16;
                (void)hoisted__U32_1828;
                U32 hoisted__U32_1829 = U32_mul(i, hoisted__U32_1828);
                (void)hoisted__U32_1829;
                Type *hoisted__Type_1830 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1830;
                U64 hoisted__U64_1831 = (U64)(hoisted__U32_1829);
                (void)hoisted__U64_1831;
                Type_delete(hoisted__Type_1830, 1);
                U32 hoisted__U32_1832 = 16;
                (void)hoisted__U32_1832;
                Type *hoisted__Type_1833 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1833;
                void *hoisted__v_1834 = ptr_add(new_data, hoisted__U64_1831);
                (void)hoisted__v_1834;
                (void)hoisted__v_1834;
                U64 hoisted__U64_1835 = (U64)(hoisted__U32_1832);
                (void)hoisted__U64_1835;
                Type_delete(hoisted__Type_1833, 1);
                memcpy(hoisted__v_1834, cloned, hoisted__U64_1835);
                U32 hoisted__U32_1836 = 16;
                (void)hoisted__U32_1836;
                Type *hoisted__Type_1837 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1837;
                I32 hoisted__I32_1838 = 0;
                (void)hoisted__I32_1838;
                U64 hoisted__U64_1839 = (U64)(hoisted__U32_1836);
                (void)hoisted__U64_1839;
                Type_delete(hoisted__Type_1837, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1838, hoisted__U64_1839); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1845 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1845->data = new_data;
    hoisted__Vec__Str_1845->count = self->count;
    hoisted__Vec__Str_1845->cap = self->cap;
    (void)hoisted__Vec__Str_1845;
    return hoisted__Vec__Str_1845;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1846 = 16;
    (void)hoisted__U32_1846;
    return hoisted__U32_1846;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1849 = 8;
    (void)hoisted__U32_1849;
    return hoisted__U32_1849;
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
    I64 hoisted__I64_2068 = 0;
    (void)hoisted__I64_2068;
    Bool hoisted__Bool_2069 = I64_eq(val, hoisted__I64_2068);
    (void)hoisted__Bool_2069;
    if (hoisted__Bool_2069) {
        U64 hoisted__U64_2038 = 2ULL;
        (void)hoisted__U64_2038;
        void * buf = malloc(hoisted__U64_2038);
        I64 hoisted__I64_2039 = 48;
        (void)hoisted__I64_2039;
        U64 hoisted__U64_2040 = 1ULL;
        (void)hoisted__U64_2040;
        memcpy(buf, &hoisted__I64_2039, hoisted__U64_2040);
        U64 hoisted__U64_2041 = 1ULL;
        (void)hoisted__U64_2041;
        void *hoisted__v_2042 = ptr_add(buf, hoisted__U64_2041);
        (void)hoisted__v_2042;
        (void)hoisted__v_2042;
        I32 hoisted__I32_2043 = 0;
        (void)hoisted__I32_2043;
        U64 hoisted__U64_2044 = 1ULL;
        (void)hoisted__U64_2044;
        memset(hoisted__v_2042, hoisted__I32_2043, hoisted__U64_2044);
        I64 hoisted__I64_2045 = 1;
        (void)hoisted__I64_2045;
        I64 hoisted__I64_2046 = 1;
        (void)hoisted__I64_2046;
        Str *hoisted__Str_2047 = malloc(sizeof(Str));
        hoisted__Str_2047->c_str = buf;
        hoisted__Str_2047->count = hoisted__I64_2045;
        hoisted__Str_2047->cap = hoisted__I64_2046;
        (void)hoisted__Str_2047;
        { Str * _ret_val = hoisted__Str_2047;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_2070 = 0;
    (void)hoisted__I64_2070;
    Bool hoisted__Bool_2071 = I64_lt(val, hoisted__I64_2070);
    (void)hoisted__Bool_2071;
    if (hoisted__Bool_2071) {
        Bool hoisted__Bool_2048 = 1;
        (void)hoisted__Bool_2048;
        is_neg = hoisted__Bool_2048;
        I64 hoisted__I64_2049 = 0;
        (void)hoisted__I64_2049;
        I64 hoisted__I64_2050 = I64_sub(hoisted__I64_2049, val);
        (void)hoisted__I64_2050;
        v = hoisted__I64_2050;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_2052 = 0;
        (void)hoisted__I64_2052;
        Bool _wcond_Bool_2051 = I64_gt(tmp, hoisted__I64_2052);
        (void)_wcond_Bool_2051;
        if (_wcond_Bool_2051) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_2053 = 10;
        (void)hoisted__I64_2053;
        I64 hoisted__I64_2054 = I64_div(tmp, hoisted__I64_2053);
        (void)hoisted__I64_2054;
        tmp = hoisted__I64_2054;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_2072 = 1ULL;
    (void)hoisted__U64_2072;
    U64 hoisted__U64_2073 = U64_add(total, hoisted__U64_2072);
    (void)hoisted__U64_2073;
    void * buf = malloc(hoisted__U64_2073);
    if (is_neg) {
        I64 hoisted__I64_2055 = 45;
        (void)hoisted__I64_2055;
        U64 hoisted__U64_2056 = 1ULL;
        (void)hoisted__U64_2056;
        memcpy(buf, &hoisted__I64_2055, hoisted__U64_2056);
    }
    U64 hoisted__U64_2074 = 1ULL;
    (void)hoisted__U64_2074;
    U64 i = U64_sub(total, hoisted__U64_2074);
    while (1) {
        I64 hoisted__I64_2058 = 0;
        (void)hoisted__I64_2058;
        Bool _wcond_Bool_2057 = I64_gt(v, hoisted__I64_2058);
        (void)_wcond_Bool_2057;
        if (_wcond_Bool_2057) {
        } else {
            break;
        }
        I64 hoisted__I64_2059 = 10;
        (void)hoisted__I64_2059;
        I64 hoisted__I64_2060 = I64_mod(v, hoisted__I64_2059);
        (void)hoisted__I64_2060;
        I64 hoisted__I64_2061 = 48;
        (void)hoisted__I64_2061;
        I64 hoisted__I64_2062 = I64_add(hoisted__I64_2060, hoisted__I64_2061);
        (void)hoisted__I64_2062;
        void *hoisted__v_2063 = ptr_add(buf, i);
        (void)hoisted__v_2063;
        (void)hoisted__v_2063;
        U8 hoisted__U8_2064 = I64_to_u8(hoisted__I64_2062);
        (void)hoisted__U8_2064;
        U64 hoisted__U64_2065 = 1ULL;
        (void)hoisted__U64_2065;
        memcpy(hoisted__v_2063, &hoisted__U8_2064, hoisted__U64_2065);
        I64 hoisted__I64_2066 = 10;
        (void)hoisted__I64_2066;
        I64 hoisted__I64_2067 = I64_div(v, hoisted__I64_2066);
        (void)hoisted__I64_2067;
        v = hoisted__I64_2067;
        U64_dec(&i);
    }
    void *hoisted__v_2075 = ptr_add(buf, total);
    (void)hoisted__v_2075;
    (void)hoisted__v_2075;
    I32 hoisted__I32_2076 = 0;
    (void)hoisted__I32_2076;
    U64 hoisted__U64_2077 = 1ULL;
    (void)hoisted__U64_2077;
    memset(hoisted__v_2075, hoisted__I32_2076, hoisted__U64_2077);
    Str *hoisted__Str_2078 = malloc(sizeof(Str));
    hoisted__Str_2078->c_str = buf;
    hoisted__Str_2078->count = total;
    hoisted__Str_2078->cap = total;
    (void)hoisted__Str_2078;
    return hoisted__Str_2078;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_2098 = 8;
    (void)hoisted__U32_2098;
    return hoisted__U32_2098;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2256 = 0;
    (void)hoisted__U32_2256;
    U64 hoisted__U64_2257 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2256); });
    (void)hoisted__U64_2257;
    return hoisted__U64_2257;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2260 = I64_cmp(a, b);
    (void)hoisted__I64_2260;
    I64 hoisted__I64_2261 = -1;
    (void)hoisted__I64_2261;
    Bool hoisted__Bool_2262 = I64_eq(hoisted__I64_2260, hoisted__I64_2261);
    (void)hoisted__Bool_2262;
    return hoisted__Bool_2262;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2263 = I64_cmp(a, b);
    (void)hoisted__I64_2263;
    I64 hoisted__I64_2264 = 1;
    (void)hoisted__I64_2264;
    Bool hoisted__Bool_2265 = I64_eq(hoisted__I64_2263, hoisted__I64_2264);
    (void)hoisted__Bool_2265;
    return hoisted__Bool_2265;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2266 = I64_eq(a, b);
    (void)hoisted__Bool_2266;
    Bool hoisted__Bool_2267 = not(hoisted__Bool_2266);
    (void)hoisted__Bool_2267;
    return hoisted__Bool_2267;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2318 = 0;
    (void)_m_Bool_2318;
    {
        Bool hoisted__Bool_2321 = 1;
        (void)hoisted__Bool_2321;
        Bool hoisted__Bool_2322 = Bool_eq(a, hoisted__Bool_2321);
        (void)hoisted__Bool_2322;
        if (hoisted__Bool_2322) {
            Bool hoisted__Bool_2319 = Bool_clone(&b);
            (void)hoisted__Bool_2319;
            _m_Bool_2318 = hoisted__Bool_2319;
        } else {
            Bool hoisted__Bool_2320 = 0;
            (void)hoisted__Bool_2320;
            _m_Bool_2318 = hoisted__Bool_2320;
        }
    }
    return _m_Bool_2318;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2332 = Bool_eq(a, b);
    (void)hoisted__Bool_2332;
    if (hoisted__Bool_2332) {
        I64 hoisted__I64_2330 = 0;
        (void)hoisted__I64_2330;
        { I64 _ret_val = hoisted__I64_2330;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2331 = -1;
        (void)hoisted__I64_2331;
        return hoisted__I64_2331;
    }
    I64 hoisted__I64_2333 = 1;
    (void)hoisted__I64_2333;
    return hoisted__I64_2333;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2334 = 1;
    (void)hoisted__U32_2334;
    return hoisted__U32_2334;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2335 = 0;
    (void)hoisted__U32_2335;
    U64 hoisted__U64_2336 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2335); });
    (void)hoisted__U64_2336;
    return hoisted__U64_2336;
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
    Bool hoisted__Bool_2362 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2362;
    if (hoisted__Bool_2362) {
        Bool hoisted__Bool_2352 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2352;
        { Bool _ret_val = hoisted__Bool_2352;
                return _ret_val; }
    }
    Bool hoisted__Bool_2363 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2363;
    if (hoisted__Bool_2363) {
        Bool hoisted__Bool_2353 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2353;
        { Bool _ret_val = hoisted__Bool_2353;
                return _ret_val; }
    }
    Bool hoisted__Bool_2364 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2364;
    if (hoisted__Bool_2364) {
        Bool hoisted__Bool_2354 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2354;
        { Bool _ret_val = hoisted__Bool_2354;
                return _ret_val; }
    }
    Bool hoisted__Bool_2365 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2365;
    if (hoisted__Bool_2365) {
        Bool hoisted__Bool_2355 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2355;
        { Bool _ret_val = hoisted__Bool_2355;
                return _ret_val; }
    }
    Bool hoisted__Bool_2366 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2366;
    if (hoisted__Bool_2366) {
        Bool hoisted__Bool_2356 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2356;
        { Bool _ret_val = hoisted__Bool_2356;
                return _ret_val; }
    }
    Bool hoisted__Bool_2367 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2367;
    if (hoisted__Bool_2367) {
        Bool hoisted__Bool_2357 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2357;
        { Bool _ret_val = hoisted__Bool_2357;
                return _ret_val; }
    }
    Bool hoisted__Bool_2368 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2368;
    if (hoisted__Bool_2368) {
        Bool hoisted__Bool_2358 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2358;
        { Bool _ret_val = hoisted__Bool_2358;
                return _ret_val; }
    }
    Bool hoisted__Bool_2369 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2369;
    if (hoisted__Bool_2369) {
        Bool hoisted__Bool_2359 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2359;
        { Bool _ret_val = hoisted__Bool_2359;
                return _ret_val; }
    }
    Bool hoisted__Bool_2370 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2370;
    if (hoisted__Bool_2370) {
        Bool hoisted__Bool_2360 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2360;
        { Bool _ret_val = hoisted__Bool_2360;
                return _ret_val; }
    }
    Bool hoisted__Bool_2371 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2371;
    if (hoisted__Bool_2371) {
        Bool hoisted__Bool_2361 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2361;
        { Bool _ret_val = hoisted__Bool_2361;
                return _ret_val; }
    }
    Bool hoisted__Bool_2372 = 0;
    (void)hoisted__Bool_2372;
    return hoisted__Bool_2372;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2394 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2394;
    if (hoisted__Bool_2394) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2395 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2395;
    if (hoisted__Bool_2395) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2396 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2396;
    if (hoisted__Bool_2396) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2397 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2397;
    if (hoisted__Bool_2397) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2398 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2398;
    if (hoisted__Bool_2398) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2399 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2399;
    if (hoisted__Bool_2399) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2400 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2400;
    if (hoisted__Bool_2400) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2401 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2401;
    if (hoisted__Bool_2401) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2402 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2402;
    if (hoisted__Bool_2402) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2403 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2403;
    if (hoisted__Bool_2403) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2404 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2404;
    UNREACHABLE(&hoisted__Str_2404);
    Str_delete(&hoisted__Str_2404, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2405 = 4;
    (void)hoisted__U32_2405;
    return hoisted__U32_2405;
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
    Bool hoisted__Bool_2457 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2457;
    if (hoisted__Bool_2457) {
        Str *hoisted__Str_2447 = get_payload(self);
        (void)hoisted__Str_2447;
        (void)hoisted__Str_2447;
        Bool hoisted__Bool_2448 = 0;
        (void)hoisted__Bool_2448;
        Str_delete(hoisted__Str_2447, hoisted__Bool_2448);
    }
    Bool hoisted__Bool_2458 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2458;
    if (hoisted__Bool_2458) {
        Str *hoisted__Str_2449 = get_payload(self);
        (void)hoisted__Str_2449;
        (void)hoisted__Str_2449;
        Bool hoisted__Bool_2450 = 0;
        (void)hoisted__Bool_2450;
        Str_delete(hoisted__Str_2449, hoisted__Bool_2450);
    }
    Bool hoisted__Bool_2459 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2459;
    if (hoisted__Bool_2459) {
        Str *hoisted__Str_2451 = get_payload(self);
        (void)hoisted__Str_2451;
        (void)hoisted__Str_2451;
        Bool hoisted__Bool_2452 = 0;
        (void)hoisted__Bool_2452;
        Str_delete(hoisted__Str_2451, hoisted__Bool_2452);
    }
    Bool hoisted__Bool_2460 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2460;
    if (hoisted__Bool_2460) {
        Primitive *hoisted__Primitive_2453 = get_payload(self);
        (void)hoisted__Primitive_2453;
        (void)hoisted__Primitive_2453;
        Bool hoisted__Bool_2454 = 0;
        (void)hoisted__Bool_2454;
        Primitive_delete(hoisted__Primitive_2453, hoisted__Bool_2454);
    }
    Bool hoisted__Bool_2461 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2461;
    if (hoisted__Bool_2461) {
        Str *hoisted__Str_2455 = get_payload(self);
        (void)hoisted__Str_2455;
        (void)hoisted__Str_2455;
        Bool hoisted__Bool_2456 = 0;
        (void)hoisted__Bool_2456;
        Str_delete(hoisted__Str_2455, hoisted__Bool_2456);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2545 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2545;
    if (hoisted__Bool_2545) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2546 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2546;
    if (hoisted__Bool_2546) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2547 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2547;
    if (hoisted__Bool_2547) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2537 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2537;
        Type *hoisted__Type_2538 = Type_Struct(hoisted__Str_2537);
        (void)hoisted__Type_2538;
        { Type * _ret_val = hoisted__Type_2538;
                return _ret_val; }
    }
    Bool hoisted__Bool_2548 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2548;
    if (hoisted__Bool_2548) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2549 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2549;
    if (hoisted__Bool_2549) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2539 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2539;
        Type *hoisted__Type_2540 = Type_Enum(hoisted__Str_2539);
        (void)hoisted__Type_2540;
        { Type * _ret_val = hoisted__Type_2540;
                return _ret_val; }
    }
    Bool hoisted__Bool_2550 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2550;
    if (hoisted__Bool_2550) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2551 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2551;
    if (hoisted__Bool_2551) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2552 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2552;
    if (hoisted__Bool_2552) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2553 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2553;
    if (hoisted__Bool_2553) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2554 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2554;
    if (hoisted__Bool_2554) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2541 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2541;
        Type *hoisted__Type_2542 = Type_Custom(hoisted__Str_2541);
        (void)hoisted__Type_2542;
        { Type * _ret_val = hoisted__Type_2542;
                return _ret_val; }
    }
    Bool hoisted__Bool_2555 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2555;
    if (hoisted__Bool_2555) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2543 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2543;
        Type *hoisted__Type_2544 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2543; _oa; }));
        (void)hoisted__Type_2544;
        { Type * _ret_val = hoisted__Type_2544;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2556 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2556;
    Type *hoisted__Type_2557 = Type_FuncPtrSig(hoisted__Str_2556);
    (void)hoisted__Type_2557;
    return hoisted__Type_2557;
}

U32 Type_size(void) {
    U32 hoisted__U32_2558 = 24;
    (void)hoisted__U32_2558;
    return hoisted__U32_2558;
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
    Bool hoisted__Bool_2659 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2659;
    if (hoisted__Bool_2659) {
        Bool hoisted__Bool_2651 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2651;
        { Bool _ret_val = hoisted__Bool_2651;
                return _ret_val; }
    }
    Bool hoisted__Bool_2660 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2660;
    if (hoisted__Bool_2660) {
        Bool hoisted__Bool_2652 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2652;
        { Bool _ret_val = hoisted__Bool_2652;
                return _ret_val; }
    }
    Bool hoisted__Bool_2661 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2661;
    if (hoisted__Bool_2661) {
        Bool hoisted__Bool_2653 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2653;
        { Bool _ret_val = hoisted__Bool_2653;
                return _ret_val; }
    }
    Bool hoisted__Bool_2662 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2662;
    if (hoisted__Bool_2662) {
        Bool hoisted__Bool_2654 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2654;
        { Bool _ret_val = hoisted__Bool_2654;
                return _ret_val; }
    }
    Bool hoisted__Bool_2663 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2663;
    if (hoisted__Bool_2663) {
        Bool hoisted__Bool_2655 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2655;
        { Bool _ret_val = hoisted__Bool_2655;
                return _ret_val; }
    }
    Bool hoisted__Bool_2664 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2664;
    if (hoisted__Bool_2664) {
        Bool hoisted__Bool_2656 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2656;
        { Bool _ret_val = hoisted__Bool_2656;
                return _ret_val; }
    }
    Bool hoisted__Bool_2665 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2665;
    if (hoisted__Bool_2665) {
        Bool hoisted__Bool_2657 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2657;
        { Bool _ret_val = hoisted__Bool_2657;
                return _ret_val; }
    }
    Bool hoisted__Bool_2666 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2666;
    if (hoisted__Bool_2666) {
        Bool hoisted__Bool_2658 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2658;
        { Bool _ret_val = hoisted__Bool_2658;
                return _ret_val; }
    }
    Bool hoisted__Bool_2667 = 0;
    (void)hoisted__Bool_2667;
    return hoisted__Bool_2667;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2685 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2685;
    if (hoisted__Bool_2685) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2686 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2686;
    if (hoisted__Bool_2686) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2687 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2687;
    if (hoisted__Bool_2687) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2688 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2688;
    if (hoisted__Bool_2688) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2689 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2689;
    if (hoisted__Bool_2689) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2690 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2690;
    if (hoisted__Bool_2690) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2691 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2691;
    if (hoisted__Bool_2691) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2692 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2692;
    if (hoisted__Bool_2692) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    static Str hoisted__Str_2693 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2693;
    UNREACHABLE(&hoisted__Str_2693);
    Str_delete(&hoisted__Str_2693, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2694 = 4;
    (void)hoisted__U32_2694;
    return hoisted__U32_2694;
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
    Bool hoisted__Bool_2699 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2699;
    if (hoisted__Bool_2699) {
        Bool hoisted__Bool_2696 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2696;
        { Bool _ret_val = hoisted__Bool_2696;
                return _ret_val; }
    }
    Bool hoisted__Bool_2700 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2700;
    if (hoisted__Bool_2700) {
        Bool hoisted__Bool_2697 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2697;
        { Bool _ret_val = hoisted__Bool_2697;
                return _ret_val; }
    }
    Bool hoisted__Bool_2701 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2701;
    if (hoisted__Bool_2701) {
        Bool hoisted__Bool_2698 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2698;
        { Bool _ret_val = hoisted__Bool_2698;
                return _ret_val; }
    }
    Bool hoisted__Bool_2702 = 0;
    (void)hoisted__Bool_2702;
    return hoisted__Bool_2702;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2710 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2710;
    if (hoisted__Bool_2710) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2711 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2711;
    if (hoisted__Bool_2711) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2712 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2712;
    if (hoisted__Bool_2712) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2713 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2713;
    UNREACHABLE(&hoisted__Str_2713);
    Str_delete(&hoisted__Str_2713, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2714 = 4;
    (void)hoisted__U32_2714;
    return hoisted__U32_2714;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2716 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2716;
    Declaration *hoisted__Declaration_2717 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2717->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2717->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2717->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2717->is_mut = self->is_mut;
    hoisted__Declaration_2717->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2717->is_priv = self->is_priv;
    hoisted__Declaration_2717->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2717->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2717->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2717->default_value = hoisted__Expr_2716;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2717->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2717;
    return hoisted__Declaration_2717;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    Str_delete(&self->name, hoisted__Bool_2718);
    Bool hoisted__Bool_2719 = 0;
    (void)hoisted__Bool_2719;
    Str_delete(&self->doc, hoisted__Bool_2719);
    Bool hoisted__Bool_2720 = 0;
    (void)hoisted__Bool_2720;
    Str_delete(&self->explicit_type, hoisted__Bool_2720);
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Bool_delete(&self->is_mut, hoisted__Bool_2721);
    Bool hoisted__Bool_2722 = 0;
    (void)hoisted__Bool_2722;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2722);
    Bool hoisted__Bool_2723 = 0;
    (void)hoisted__Bool_2723;
    Bool_delete(&self->is_priv, hoisted__Bool_2723);
    Bool hoisted__Bool_2724 = 0;
    (void)hoisted__Bool_2724;
    Bool_delete(&self->used, hoisted__Bool_2724);
    Bool hoisted__Bool_2725 = 0;
    (void)hoisted__Bool_2725;
    OwnType_delete(&self->own_type, hoisted__Bool_2725);
    Bool hoisted__Bool_2726 = 0;
    (void)hoisted__Bool_2726;
    Type_delete(&self->til_type, hoisted__Bool_2726);
    Bool hoisted__Bool_2727 = 1;
    (void)hoisted__Bool_2727;
    Expr_delete(self->default_value, hoisted__Bool_2727);
    Bool hoisted__Bool_2728 = 0;
    (void)hoisted__Bool_2728;
    Str_delete(&self->orig_name, hoisted__Bool_2728);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2729 = 104;
    (void)hoisted__U32_2729;
    return hoisted__U32_2729;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2731 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2731->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2731->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2731->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2731->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2731->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2731->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2731->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2731->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2731->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2731->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2731->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2731;
    return hoisted__FunctionDef_2731;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2732 = 0;
    (void)hoisted__Bool_2732;
    FuncType_delete(&self->func_type, hoisted__Bool_2732);
    Bool hoisted__Bool_2733 = 0;
    (void)hoisted__Bool_2733;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2733);
    Bool hoisted__Bool_2734 = 0;
    (void)hoisted__Bool_2734;
    Str_delete(&self->return_type, hoisted__Bool_2734);
    Bool hoisted__Bool_2735 = 0;
    (void)hoisted__Bool_2735;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2735);
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    I32_delete(&self->variadic_index, hoisted__Bool_2736);
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    I32_delete(&self->kwargs_index, hoisted__Bool_2737);
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Bool_delete(&self->auto_generated, hoisted__Bool_2739);
    Bool hoisted__Bool_2740 = 0;
    (void)hoisted__Bool_2740;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2740);
    Bool hoisted__Bool_2741 = 0;
    (void)hoisted__Bool_2741;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2741);
    Bool hoisted__Bool_2742 = 0;
    (void)hoisted__Bool_2742;
    Str_delete(&self->closure_name, hoisted__Bool_2742);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2743 = 0;
    (void)hoisted__U32_2743;
    U64 hoisted__U64_2744 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2743); });
    (void)hoisted__U64_2744;
    return hoisted__U64_2744;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2745 = 104;
    (void)hoisted__U32_2745;
    return hoisted__U32_2745;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2748 = malloc(sizeof(FCallData));
    hoisted__FCallData_2748->is_splat = self->is_splat;
    hoisted__FCallData_2748->does_throw = self->does_throw;
    hoisted__FCallData_2748->is_bang = self->is_bang;
    hoisted__FCallData_2748->own_args = self->own_args;
    hoisted__FCallData_2748->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2748->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2748;
    return hoisted__FCallData_2748;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2749 = 0;
    (void)hoisted__Bool_2749;
    Bool_delete(&self->is_splat, hoisted__Bool_2749);
    Bool hoisted__Bool_2750 = 0;
    (void)hoisted__Bool_2750;
    Bool_delete(&self->does_throw, hoisted__Bool_2750);
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Bool_delete(&self->is_bang, hoisted__Bool_2751);
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    U64_delete(&self->own_args, hoisted__Bool_2752);
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Bool_delete(&self->swap_replace, hoisted__Bool_2753);
    Bool hoisted__Bool_2754 = 0;
    (void)hoisted__Bool_2754;
    Type_delete(&self->til_type, hoisted__Bool_2754);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2755 = 0;
    (void)hoisted__U32_2755;
    U64 hoisted__U64_2756 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2755); });
    (void)hoisted__U64_2756;
    return hoisted__U64_2756;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2757 = 48;
    (void)hoisted__U32_2757;
    return hoisted__U32_2757;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2769 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2769->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2769->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2769;
    return hoisted__LiteralNumData_2769;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2770 = 0;
    (void)hoisted__Bool_2770;
    Str_delete(&self->text, hoisted__Bool_2770);
    Bool hoisted__Bool_2771 = 0;
    (void)hoisted__Bool_2771;
    Type_delete(&self->til_type, hoisted__Bool_2771);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2772 = 0;
    (void)hoisted__U32_2772;
    U64 hoisted__U64_2773 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2772); });
    (void)hoisted__U64_2773;
    return hoisted__U64_2773;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2774 = 40;
    (void)hoisted__U32_2774;
    return hoisted__U32_2774;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2784 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2784->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2784->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2784;
    return hoisted__IdentData_2784;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2785 = 0;
    (void)hoisted__Bool_2785;
    Str_delete(&self->name, hoisted__Bool_2785);
    Bool hoisted__Bool_2786 = 0;
    (void)hoisted__Bool_2786;
    Type_delete(&self->til_type, hoisted__Bool_2786);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2787 = 0;
    (void)hoisted__U32_2787;
    U64 hoisted__U64_2788 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2787); });
    (void)hoisted__U64_2788;
    return hoisted__U64_2788;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2789 = 40;
    (void)hoisted__U32_2789;
    return hoisted__U32_2789;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2795 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2795->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2795->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2795;
    return hoisted__FieldAccessData_2795;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2796 = 0;
    (void)hoisted__Bool_2796;
    Str_delete(&self->name, hoisted__Bool_2796);
    Bool hoisted__Bool_2797 = 0;
    (void)hoisted__Bool_2797;
    Type_delete(&self->til_type, hoisted__Bool_2797);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2798 = 0;
    (void)hoisted__U32_2798;
    U64 hoisted__U64_2799 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2798); });
    (void)hoisted__U64_2799;
    return hoisted__U64_2799;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2800 = 40;
    (void)hoisted__U32_2800;
    return hoisted__U32_2800;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2881 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2881->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2881->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2881->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2881->is_interface = self->is_interface;
    hoisted__StructDef_2881->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2881->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2881;
    return hoisted__StructDef_2881;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2882 = 0;
    (void)hoisted__Bool_2882;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2882);
    Bool hoisted__Bool_2883 = 0;
    (void)hoisted__Bool_2883;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2883);
    Bool hoisted__Bool_2884 = 0;
    (void)hoisted__Bool_2884;
    Str_delete(&self->c_tag, hoisted__Bool_2884);
    Bool hoisted__Bool_2885 = 0;
    (void)hoisted__Bool_2885;
    Bool_delete(&self->is_interface, hoisted__Bool_2885);
    Bool hoisted__Bool_2886 = 0;
    (void)hoisted__Bool_2886;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2886);
    Bool hoisted__Bool_2887 = 0;
    (void)hoisted__Bool_2887;
    Str_delete(&self->implements_name, hoisted__Bool_2887);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2888 = 0;
    (void)hoisted__U32_2888;
    U64 hoisted__U64_2889 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2888); });
    (void)hoisted__U64_2889;
    return hoisted__U64_2889;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2890 = 72;
    (void)hoisted__U32_2890;
    return hoisted__U32_2890;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2895 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2895->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2895->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2895->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2895->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2895->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2895;
    return hoisted__EnumDef_2895;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2896 = 0;
    (void)hoisted__Bool_2896;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2896);
    Bool hoisted__Bool_2897 = 0;
    (void)hoisted__Bool_2897;
    Vec__Str_delete(&self->variants, hoisted__Bool_2897);
    Bool hoisted__Bool_2898 = 0;
    (void)hoisted__Bool_2898;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2898);
    Bool hoisted__Bool_2899 = 0;
    (void)hoisted__Bool_2899;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2899);
    Bool hoisted__Bool_2900 = 0;
    (void)hoisted__Bool_2900;
    Str_delete(&self->implements_name, hoisted__Bool_2900);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2901 = 0;
    (void)hoisted__U32_2901;
    U64 hoisted__U64_2902 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2901); });
    (void)hoisted__U64_2902;
    return hoisted__U64_2902;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2903 = 96;
    (void)hoisted__U32_2903;
    return hoisted__U32_2903;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2999 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2999->name = *_ca; free(_ca); }
    hoisted__AssignData_2999->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2999->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2999->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2999;
    return hoisted__AssignData_2999;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_3000 = 0;
    (void)hoisted__Bool_3000;
    Str_delete(&self->name, hoisted__Bool_3000);
    Bool hoisted__Bool_3001 = 0;
    (void)hoisted__Bool_3001;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3001);
    Bool hoisted__Bool_3002 = 0;
    (void)hoisted__Bool_3002;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_3002);
    Bool hoisted__Bool_3003 = 0;
    (void)hoisted__Bool_3003;
    Bool_delete(&self->swap_replace, hoisted__Bool_3003);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_3004 = 0;
    (void)hoisted__U32_3004;
    U64 hoisted__U64_3005 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3004); });
    (void)hoisted__U64_3005;
    return hoisted__U64_3005;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_3006 = 24;
    (void)hoisted__U32_3006;
    return hoisted__U32_3006;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_3008 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_3008->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_3008->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_3008;
    return hoisted__FieldAssignData_3008;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_3009 = 0;
    (void)hoisted__Bool_3009;
    Str_delete(&self->name, hoisted__Bool_3009);
    Bool hoisted__Bool_3010 = 0;
    (void)hoisted__Bool_3010;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3010);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_3011 = 0;
    (void)hoisted__U32_3011;
    U64 hoisted__U64_3012 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3011); });
    (void)hoisted__U64_3012;
    return hoisted__U64_3012;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_3013 = 24;
    (void)hoisted__U32_3013;
    return hoisted__U32_3013;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_3015 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_3015->name = *_ca; free(_ca); }
    hoisted__ForInData_3015->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_3015->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_3015;
    return hoisted__ForInData_3015;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_3016 = 0;
    (void)hoisted__Bool_3016;
    Str_delete(&self->name, hoisted__Bool_3016);
    Bool hoisted__Bool_3017 = 0;
    (void)hoisted__Bool_3017;
    Bool_delete(&self->is_mut, hoisted__Bool_3017);
    Bool hoisted__Bool_3018 = 0;
    (void)hoisted__Bool_3018;
    Type_delete(&self->til_type, hoisted__Bool_3018);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_3019 = 0;
    (void)hoisted__U32_3019;
    U64 hoisted__U64_3020 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3019); });
    (void)hoisted__U64_3020;
    return hoisted__U64_3020;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_3021 = 48;
    (void)hoisted__U32_3021;
    return hoisted__U32_3021;
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
    Bool hoisted__Bool_3051 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3051;
    if (hoisted__Bool_3051) {
        Str *hoisted__Str_3045 = get_payload(self);
        (void)hoisted__Str_3045;
        (void)hoisted__Str_3045;
        Bool hoisted__Bool_3046 = 0;
        (void)hoisted__Bool_3046;
        Str_delete(hoisted__Str_3045, hoisted__Bool_3046);
    }
    Bool hoisted__Bool_3052 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3052;
    if (hoisted__Bool_3052) {
        LiteralNumData *hoisted__LiteralNumData_3047 = get_payload(self);
        (void)hoisted__LiteralNumData_3047;
        (void)hoisted__LiteralNumData_3047;
        Bool hoisted__Bool_3048 = 0;
        (void)hoisted__Bool_3048;
        LiteralNumData_delete(hoisted__LiteralNumData_3047, hoisted__Bool_3048);
    }
    Bool hoisted__Bool_3053 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3053;
    if (hoisted__Bool_3053) {
        Bool *hoisted__Bool_3049 = get_payload(self);
        (void)hoisted__Bool_3049;
        (void)hoisted__Bool_3049;
        Bool hoisted__Bool_3050 = 0;
        (void)hoisted__Bool_3050;
        Bool_delete(hoisted__Bool_3049, hoisted__Bool_3050);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_3102 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3102;
    if (hoisted__Bool_3102) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3097 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3097;
        Literal *hoisted__Literal_3098 = Literal_Str(hoisted__Str_3097);
        (void)hoisted__Literal_3098;
        { Literal * _ret_val = hoisted__Literal_3098;
                return _ret_val; }
    }
    Bool hoisted__Bool_3103 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3103;
    if (hoisted__Bool_3103) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3099 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3099;
        Literal *hoisted__Literal_3100 = Literal_Num(hoisted__LiteralNumData_3099);
        (void)hoisted__Literal_3100;
        { Literal * _ret_val = hoisted__Literal_3100;
                return _ret_val; }
    }
    Bool hoisted__Bool_3104 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3104;
    if (hoisted__Bool_3104) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3101 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3101;
        { Literal * _ret_val = hoisted__Literal_3101;
                return _ret_val; }
    }
    Bool hoisted__Bool_3105 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_3105;
    if (hoisted__Bool_3105) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_3106 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_3106;
    if (hoisted__Bool_3106) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3107 = 48;
    (void)hoisted__U32_3107;
    return hoisted__U32_3107;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3110 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3110->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3110->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3110;
    return hoisted__MatchData_3110;
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
    U32 hoisted__U32_3113 = 0;
    (void)hoisted__U32_3113;
    U64 hoisted__U64_3114 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3113); });
    (void)hoisted__U64_3114;
    return hoisted__U64_3114;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3115 = 40;
    (void)hoisted__U32_3115;
    return hoisted__U32_3115;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3120 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3120->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3120;
    return hoisted__CaptureBlockData_3120;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3121 = 0;
    (void)hoisted__Bool_3121;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3121);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3122 = 0;
    (void)hoisted__U32_3122;
    U64 hoisted__U64_3123 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3122); });
    (void)hoisted__U64_3123;
    return hoisted__U64_3123;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3124 = 16;
    (void)hoisted__U32_3124;
    return hoisted__U32_3124;
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
    Bool hoisted__Bool_3303 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3303;
    if (hoisted__Bool_3303) {
        Literal *hoisted__Literal_3275 = get_payload(self);
        (void)hoisted__Literal_3275;
        (void)hoisted__Literal_3275;
        Bool hoisted__Bool_3276 = 0;
        (void)hoisted__Bool_3276;
        Literal_delete(hoisted__Literal_3275, hoisted__Bool_3276);
    }
    Bool hoisted__Bool_3304 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3304;
    if (hoisted__Bool_3304) {
        IdentData *hoisted__IdentData_3277 = get_payload(self);
        (void)hoisted__IdentData_3277;
        (void)hoisted__IdentData_3277;
        Bool hoisted__Bool_3278 = 0;
        (void)hoisted__Bool_3278;
        IdentData_delete(hoisted__IdentData_3277, hoisted__Bool_3278);
    }
    Bool hoisted__Bool_3305 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3305;
    if (hoisted__Bool_3305) {
        Declaration *hoisted__Declaration_3279 = get_payload(self);
        (void)hoisted__Declaration_3279;
        (void)hoisted__Declaration_3279;
        Bool hoisted__Bool_3280 = 0;
        (void)hoisted__Bool_3280;
        Declaration_delete(hoisted__Declaration_3279, hoisted__Bool_3280);
    }
    Bool hoisted__Bool_3306 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3306;
    if (hoisted__Bool_3306) {
        AssignData *hoisted__AssignData_3281 = get_payload(self);
        (void)hoisted__AssignData_3281;
        (void)hoisted__AssignData_3281;
        Bool hoisted__Bool_3282 = 0;
        (void)hoisted__Bool_3282;
        AssignData_delete(hoisted__AssignData_3281, hoisted__Bool_3282);
    }
    Bool hoisted__Bool_3307 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3307;
    if (hoisted__Bool_3307) {
        FCallData *hoisted__FCallData_3283 = get_payload(self);
        (void)hoisted__FCallData_3283;
        (void)hoisted__FCallData_3283;
        Bool hoisted__Bool_3284 = 0;
        (void)hoisted__Bool_3284;
        FCallData_delete(hoisted__FCallData_3283, hoisted__Bool_3284);
    }
    Bool hoisted__Bool_3308 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3308;
    if (hoisted__Bool_3308) {
        FunctionDef *hoisted__FunctionDef_3285 = get_payload(self);
        (void)hoisted__FunctionDef_3285;
        (void)hoisted__FunctionDef_3285;
        Bool hoisted__Bool_3286 = 0;
        (void)hoisted__Bool_3286;
        FunctionDef_delete(hoisted__FunctionDef_3285, hoisted__Bool_3286);
    }
    Bool hoisted__Bool_3309 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3309;
    if (hoisted__Bool_3309) {
        StructDef *hoisted__StructDef_3287 = get_payload(self);
        (void)hoisted__StructDef_3287;
        (void)hoisted__StructDef_3287;
        Bool hoisted__Bool_3288 = 0;
        (void)hoisted__Bool_3288;
        StructDef_delete(hoisted__StructDef_3287, hoisted__Bool_3288);
    }
    Bool hoisted__Bool_3310 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3310;
    if (hoisted__Bool_3310) {
        EnumDef *hoisted__EnumDef_3289 = get_payload(self);
        (void)hoisted__EnumDef_3289;
        (void)hoisted__EnumDef_3289;
        Bool hoisted__Bool_3290 = 0;
        (void)hoisted__Bool_3290;
        EnumDef_delete(hoisted__EnumDef_3289, hoisted__Bool_3290);
    }
    Bool hoisted__Bool_3311 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3311;
    if (hoisted__Bool_3311) {
        FieldAccessData *hoisted__FieldAccessData_3291 = get_payload(self);
        (void)hoisted__FieldAccessData_3291;
        (void)hoisted__FieldAccessData_3291;
        Bool hoisted__Bool_3292 = 0;
        (void)hoisted__Bool_3292;
        FieldAccessData_delete(hoisted__FieldAccessData_3291, hoisted__Bool_3292);
    }
    Bool hoisted__Bool_3312 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3312;
    if (hoisted__Bool_3312) {
        FieldAssignData *hoisted__FieldAssignData_3293 = get_payload(self);
        (void)hoisted__FieldAssignData_3293;
        (void)hoisted__FieldAssignData_3293;
        Bool hoisted__Bool_3294 = 0;
        (void)hoisted__Bool_3294;
        FieldAssignData_delete(hoisted__FieldAssignData_3293, hoisted__Bool_3294);
    }
    Bool hoisted__Bool_3313 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3313;
    if (hoisted__Bool_3313) {
        ForInData *hoisted__ForInData_3295 = get_payload(self);
        (void)hoisted__ForInData_3295;
        (void)hoisted__ForInData_3295;
        Bool hoisted__Bool_3296 = 0;
        (void)hoisted__Bool_3296;
        ForInData_delete(hoisted__ForInData_3295, hoisted__Bool_3296);
    }
    Bool hoisted__Bool_3314 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3314;
    if (hoisted__Bool_3314) {
        Str *hoisted__Str_3297 = get_payload(self);
        (void)hoisted__Str_3297;
        (void)hoisted__Str_3297;
        Bool hoisted__Bool_3298 = 0;
        (void)hoisted__Bool_3298;
        Str_delete(hoisted__Str_3297, hoisted__Bool_3298);
    }
    Bool hoisted__Bool_3315 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3315;
    if (hoisted__Bool_3315) {
        MatchData *hoisted__MatchData_3299 = get_payload(self);
        (void)hoisted__MatchData_3299;
        (void)hoisted__MatchData_3299;
        Bool hoisted__Bool_3300 = 0;
        (void)hoisted__Bool_3300;
        MatchData_delete(hoisted__MatchData_3299, hoisted__Bool_3300);
    }
    Bool hoisted__Bool_3316 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3316;
    if (hoisted__Bool_3316) {
        CaptureBlockData *hoisted__CaptureBlockData_3301 = get_payload(self);
        (void)hoisted__CaptureBlockData_3301;
        (void)hoisted__CaptureBlockData_3301;
        Bool hoisted__Bool_3302 = 0;
        (void)hoisted__Bool_3302;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3301, hoisted__Bool_3302);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3540 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3540;
    if (hoisted__Bool_3540) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3541 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3541;
    if (hoisted__Bool_3541) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3512 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3512;
        NodeType *hoisted__NodeType_3513 = NodeType_Literal(hoisted__Literal_3512);
        (void)hoisted__NodeType_3513;
        { NodeType * _ret_val = hoisted__NodeType_3513;
                return _ret_val; }
    }
    Bool hoisted__Bool_3542 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3542;
    if (hoisted__Bool_3542) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3514 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3514;
        NodeType *hoisted__NodeType_3515 = NodeType_Ident(hoisted__IdentData_3514);
        (void)hoisted__NodeType_3515;
        { NodeType * _ret_val = hoisted__NodeType_3515;
                return _ret_val; }
    }
    Bool hoisted__Bool_3543 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3543;
    if (hoisted__Bool_3543) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3516 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3516;
        NodeType *hoisted__NodeType_3517 = NodeType_Decl(hoisted__Declaration_3516);
        (void)hoisted__NodeType_3517;
        { NodeType * _ret_val = hoisted__NodeType_3517;
                return _ret_val; }
    }
    Bool hoisted__Bool_3544 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3544;
    if (hoisted__Bool_3544) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3518 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3518;
        NodeType *hoisted__NodeType_3519 = NodeType_Assign(hoisted__AssignData_3518);
        (void)hoisted__NodeType_3519;
        { NodeType * _ret_val = hoisted__NodeType_3519;
                return _ret_val; }
    }
    Bool hoisted__Bool_3545 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3545;
    if (hoisted__Bool_3545) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3520 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3520;
        NodeType *hoisted__NodeType_3521 = NodeType_FCall(hoisted__FCallData_3520);
        (void)hoisted__NodeType_3521;
        { NodeType * _ret_val = hoisted__NodeType_3521;
                return _ret_val; }
    }
    Bool hoisted__Bool_3546 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3546;
    if (hoisted__Bool_3546) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3522 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3522;
        NodeType *hoisted__NodeType_3523 = NodeType_FuncDef(hoisted__FunctionDef_3522);
        (void)hoisted__NodeType_3523;
        { NodeType * _ret_val = hoisted__NodeType_3523;
                return _ret_val; }
    }
    Bool hoisted__Bool_3547 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3547;
    if (hoisted__Bool_3547) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3524 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3524;
        NodeType *hoisted__NodeType_3525 = NodeType_StructDef(hoisted__StructDef_3524);
        (void)hoisted__NodeType_3525;
        { NodeType * _ret_val = hoisted__NodeType_3525;
                return _ret_val; }
    }
    Bool hoisted__Bool_3548 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3548;
    if (hoisted__Bool_3548) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3526 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3526;
        NodeType *hoisted__NodeType_3527 = NodeType_EnumDef(hoisted__EnumDef_3526);
        (void)hoisted__NodeType_3527;
        { NodeType * _ret_val = hoisted__NodeType_3527;
                return _ret_val; }
    }
    Bool hoisted__Bool_3549 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3549;
    if (hoisted__Bool_3549) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3528 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3528;
        NodeType *hoisted__NodeType_3529 = NodeType_FieldAccess(hoisted__FieldAccessData_3528);
        (void)hoisted__NodeType_3529;
        { NodeType * _ret_val = hoisted__NodeType_3529;
                return _ret_val; }
    }
    Bool hoisted__Bool_3550 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3550;
    if (hoisted__Bool_3550) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3530 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3530;
        NodeType *hoisted__NodeType_3531 = NodeType_FieldAssign(hoisted__FieldAssignData_3530);
        (void)hoisted__NodeType_3531;
        { NodeType * _ret_val = hoisted__NodeType_3531;
                return _ret_val; }
    }
    Bool hoisted__Bool_3551 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3551;
    if (hoisted__Bool_3551) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3552 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3552;
    if (hoisted__Bool_3552) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3553 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3553;
    if (hoisted__Bool_3553) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3554 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3554;
    if (hoisted__Bool_3554) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3532 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3532;
        NodeType *hoisted__NodeType_3533 = NodeType_ForIn(hoisted__ForInData_3532);
        (void)hoisted__NodeType_3533;
        { NodeType * _ret_val = hoisted__NodeType_3533;
                return _ret_val; }
    }
    Bool hoisted__Bool_3555 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3555;
    if (hoisted__Bool_3555) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3534 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3534;
        NodeType *hoisted__NodeType_3535 = NodeType_NamedArg(hoisted__Str_3534);
        (void)hoisted__NodeType_3535;
        { NodeType * _ret_val = hoisted__NodeType_3535;
                return _ret_val; }
    }
    Bool hoisted__Bool_3556 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3556;
    if (hoisted__Bool_3556) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3557 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3557;
    if (hoisted__Bool_3557) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3558 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3558;
    if (hoisted__Bool_3558) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3559 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3559;
    if (hoisted__Bool_3559) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3536 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3536;
        NodeType *hoisted__NodeType_3537 = NodeType_Match(hoisted__MatchData_3536);
        (void)hoisted__NodeType_3537;
        { NodeType * _ret_val = hoisted__NodeType_3537;
                return _ret_val; }
    }
    Bool hoisted__Bool_3560 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3560;
    if (hoisted__Bool_3560) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3561 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3561;
    if (hoisted__Bool_3561) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3562 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3562;
    if (hoisted__Bool_3562) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3563 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3563;
    if (hoisted__Bool_3563) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3564 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3564;
    if (hoisted__Bool_3564) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3565 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3565;
    if (hoisted__Bool_3565) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3538 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3538;
        NodeType *hoisted__NodeType_3539 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3538);
        (void)hoisted__NodeType_3539;
        { NodeType * _ret_val = hoisted__NodeType_3539;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3566 = 112;
    (void)hoisted__U32_3566;
    return hoisted__U32_3566;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3567 = is_null(self);
    (void)hoisted__Bool_3567;
    if (hoisted__Bool_3567) {
        return;
    }
    Bool hoisted__Bool_3568 = 0;
    (void)hoisted__Bool_3568;
    NodeType_delete(&self->node_type, hoisted__Bool_3568);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3621 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3621->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3621->children = *_ca; free(_ca); }
    hoisted__Expr_3621->line = line;
    hoisted__Expr_3621->col = col;
    (void)hoisted__Expr_3621;
    return hoisted__Expr_3621;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3630 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3630->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3630->children = *_ca; free(_ca); }
    hoisted__Expr_3630->line = self->line;
    hoisted__Expr_3630->col = self->col;
    (void)hoisted__Expr_3630;
    return hoisted__Expr_3630;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3631 = 0;
    (void)hoisted__U32_3631;
    U64 hoisted__U64_3632 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3631); });
    (void)hoisted__U64_3632;
    return hoisted__U64_3632;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3633 = 136;
    (void)hoisted__U32_3633;
    return hoisted__U32_3633;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4369 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4369->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4369->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4369;
    return hoisted__Map__I64_Str_4369;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4516 = 0;
    (void)hoisted__Bool_4516;
    Vec__I64_delete(&self->keys, hoisted__Bool_4516);
    Bool hoisted__Bool_4517 = 0;
    (void)hoisted__Bool_4517;
    Vec__Str_delete(&self->values, hoisted__Bool_4517);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4518 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4518->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4518->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4518;
    return hoisted__Map__I64_Str_4518;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4519 = 0;
    (void)hoisted__U32_4519;
    U64 hoisted__U64_4520 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4519); });
    (void)hoisted__U64_4520;
    return hoisted__U64_4520;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4521 = 32;
    (void)hoisted__U32_4521;
    return hoisted__U32_4521;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4522 = 1;
    (void)hoisted__U32_4522;
    Type *hoisted__Type_4523 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4523;
    U64 hoisted__U64_4524 = (U64)(hoisted__U32_4522);
    (void)hoisted__U64_4524;
    Type_delete(hoisted__Type_4523, 1);
    void * hoisted__v_4525 = malloc(hoisted__U64_4524);
    (void)hoisted__v_4525;
    U32 hoisted__U32_4526 = 0;
    (void)hoisted__U32_4526;
    I64 hoisted__I64_4527 = 1;
    (void)hoisted__I64_4527;
    Vec__Bool *hoisted__Vec__Bool_4528 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4528->data = hoisted__v_4525;
    hoisted__Vec__Bool_4528->count = hoisted__U32_4526;
    hoisted__Vec__Bool_4528->cap = hoisted__I64_4527;
    (void)hoisted__Vec__Bool_4528;
    return hoisted__Vec__Bool_4528;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4529 = self->count;
        (void)_re_U32_4529;
        U32 _rc_U32_4529 = 0;
        (void)_rc_U32_4529;
        Bool hoisted__Bool_4544 = U32_lte(_rc_U32_4529, _re_U32_4529);
        (void)hoisted__Bool_4544;
        if (hoisted__Bool_4544) {
            while (1) {
                Bool _wcond_Bool_4530 = U32_lt(_rc_U32_4529, _re_U32_4529);
                (void)_wcond_Bool_4530;
                if (_wcond_Bool_4530) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4529);
                U32_inc(&_rc_U32_4529);
                U32 hoisted__U32_4531 = 1;
                (void)hoisted__U32_4531;
                U32 hoisted__U32_4532 = U32_mul(i, hoisted__U32_4531);
                (void)hoisted__U32_4532;
                Type *hoisted__Type_4533 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4533;
                U64 hoisted__U64_4534 = (U64)(hoisted__U32_4532);
                (void)hoisted__U64_4534;
                Type_delete(hoisted__Type_4533, 1);
                Bool *hoisted__Bool_4535 = ptr_add(self->data, hoisted__U64_4534);
                (void)hoisted__Bool_4535;
                (void)hoisted__Bool_4535;
                Bool hoisted__Bool_4536 = 0;
                (void)hoisted__Bool_4536;
                Bool_delete(hoisted__Bool_4535, hoisted__Bool_4536);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4537 = U32_gt(_rc_U32_4529, _re_U32_4529);
                (void)_wcond_Bool_4537;
                if (_wcond_Bool_4537) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4529);
                U32_dec(&_rc_U32_4529);
                U32 hoisted__U32_4538 = 1;
                (void)hoisted__U32_4538;
                U32 hoisted__U32_4539 = U32_mul(i, hoisted__U32_4538);
                (void)hoisted__U32_4539;
                Type *hoisted__Type_4540 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4540;
                U64 hoisted__U64_4541 = (U64)(hoisted__U32_4539);
                (void)hoisted__U64_4541;
                Type_delete(hoisted__Type_4540, 1);
                Bool *hoisted__Bool_4542 = ptr_add(self->data, hoisted__U64_4541);
                (void)hoisted__Bool_4542;
                (void)hoisted__Bool_4542;
                Bool hoisted__Bool_4543 = 0;
                (void)hoisted__Bool_4543;
                Bool_delete(hoisted__Bool_4542, hoisted__Bool_4543);
            }
        }
    }
    U32 hoisted__U32_4545 = 0;
    (void)hoisted__U32_4545;
    self->count = hoisted__U32_4545;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4861 = 1;
    (void)hoisted__U32_4861;
    U32 hoisted__U32_4862 = U32_mul(self->cap, hoisted__U32_4861);
    (void)hoisted__U32_4862;
    Type *hoisted__Type_4863 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4863;
    U64 hoisted__U64_4864 = (U64)(hoisted__U32_4862);
    (void)hoisted__U64_4864;
    Type_delete(hoisted__Type_4863, 1);
    void * new_data = malloc(hoisted__U64_4864);
    {
        U32 _re_U32_4825 = self->count;
        (void)_re_U32_4825;
        U32 _rc_U32_4825 = 0;
        (void)_rc_U32_4825;
        Bool hoisted__Bool_4860 = U32_lte(_rc_U32_4825, _re_U32_4825);
        (void)hoisted__Bool_4860;
        if (hoisted__Bool_4860) {
            while (1) {
                Bool _wcond_Bool_4826 = U32_lt(_rc_U32_4825, _re_U32_4825);
                (void)_wcond_Bool_4826;
                if (_wcond_Bool_4826) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4825);
                U32_inc(&_rc_U32_4825);
                U32 hoisted__U32_4827 = 1;
                (void)hoisted__U32_4827;
                U32 hoisted__U32_4828 = U32_mul(i, hoisted__U32_4827);
                (void)hoisted__U32_4828;
                Type *hoisted__Type_4829 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4829;
                U64 hoisted__U64_4830 = (U64)(hoisted__U32_4828);
                (void)hoisted__U64_4830;
                Type_delete(hoisted__Type_4829, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4830);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4831 = 1;
                (void)hoisted__U32_4831;
                U32 hoisted__U32_4832 = U32_mul(i, hoisted__U32_4831);
                (void)hoisted__U32_4832;
                Type *hoisted__Type_4833 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4833;
                U64 hoisted__U64_4834 = (U64)(hoisted__U32_4832);
                (void)hoisted__U64_4834;
                Type_delete(hoisted__Type_4833, 1);
                U32 hoisted__U32_4835 = 1;
                (void)hoisted__U32_4835;
                Type *hoisted__Type_4836 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4836;
                void *hoisted__v_4837 = ptr_add(new_data, hoisted__U64_4834);
                (void)hoisted__v_4837;
                (void)hoisted__v_4837;
                U64 hoisted__U64_4838 = (U64)(hoisted__U32_4835);
                (void)hoisted__U64_4838;
                Type_delete(hoisted__Type_4836, 1);
                memcpy(hoisted__v_4837, &cloned, hoisted__U64_4838);
                U32 hoisted__U32_4839 = 1;
                (void)hoisted__U32_4839;
                Type *hoisted__Type_4840 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4840;
                I32 hoisted__I32_4841 = 0;
                (void)hoisted__I32_4841;
                U64 hoisted__U64_4842 = (U64)(hoisted__U32_4839);
                (void)hoisted__U64_4842;
                Type_delete(hoisted__Type_4840, 1);
                memset(&cloned, hoisted__I32_4841, hoisted__U64_4842);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4843 = U32_gt(_rc_U32_4825, _re_U32_4825);
                (void)_wcond_Bool_4843;
                if (_wcond_Bool_4843) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4825);
                U32_dec(&_rc_U32_4825);
                U32 hoisted__U32_4844 = 1;
                (void)hoisted__U32_4844;
                U32 hoisted__U32_4845 = U32_mul(i, hoisted__U32_4844);
                (void)hoisted__U32_4845;
                Type *hoisted__Type_4846 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4846;
                U64 hoisted__U64_4847 = (U64)(hoisted__U32_4845);
                (void)hoisted__U64_4847;
                Type_delete(hoisted__Type_4846, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4847);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4848 = 1;
                (void)hoisted__U32_4848;
                U32 hoisted__U32_4849 = U32_mul(i, hoisted__U32_4848);
                (void)hoisted__U32_4849;
                Type *hoisted__Type_4850 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4850;
                U64 hoisted__U64_4851 = (U64)(hoisted__U32_4849);
                (void)hoisted__U64_4851;
                Type_delete(hoisted__Type_4850, 1);
                U32 hoisted__U32_4852 = 1;
                (void)hoisted__U32_4852;
                Type *hoisted__Type_4853 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4853;
                void *hoisted__v_4854 = ptr_add(new_data, hoisted__U64_4851);
                (void)hoisted__v_4854;
                (void)hoisted__v_4854;
                U64 hoisted__U64_4855 = (U64)(hoisted__U32_4852);
                (void)hoisted__U64_4855;
                Type_delete(hoisted__Type_4853, 1);
                memcpy(hoisted__v_4854, &cloned, hoisted__U64_4855);
                U32 hoisted__U32_4856 = 1;
                (void)hoisted__U32_4856;
                Type *hoisted__Type_4857 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4857;
                I32 hoisted__I32_4858 = 0;
                (void)hoisted__I32_4858;
                U64 hoisted__U64_4859 = (U64)(hoisted__U32_4856);
                (void)hoisted__U64_4859;
                Type_delete(hoisted__Type_4857, 1);
                memset(&cloned, hoisted__I32_4858, hoisted__U64_4859);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4865 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4865->data = new_data;
    hoisted__Vec__Bool_4865->count = self->count;
    hoisted__Vec__Bool_4865->cap = self->cap;
    (void)hoisted__Vec__Bool_4865;
    return hoisted__Vec__Bool_4865;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4866 = 16;
    (void)hoisted__U32_4866;
    return hoisted__U32_4866;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5212 = 104;
    (void)hoisted__U32_5212;
    Type *hoisted__Type_5213 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5213;
    U64 hoisted__U64_5214 = (U64)(hoisted__U32_5212);
    (void)hoisted__U64_5214;
    Type_delete(hoisted__Type_5213, 1);
    void * hoisted__v_5215 = malloc(hoisted__U64_5214);
    (void)hoisted__v_5215;
    U32 hoisted__U32_5216 = 0;
    (void)hoisted__U32_5216;
    I64 hoisted__I64_5217 = 1;
    (void)hoisted__I64_5217;
    Vec__Declaration *hoisted__Vec__Declaration_5218 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5218->data = hoisted__v_5215;
    hoisted__Vec__Declaration_5218->count = hoisted__U32_5216;
    hoisted__Vec__Declaration_5218->cap = hoisted__I64_5217;
    (void)hoisted__Vec__Declaration_5218;
    return hoisted__Vec__Declaration_5218;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5219 = self->count;
        (void)_re_U32_5219;
        U32 _rc_U32_5219 = 0;
        (void)_rc_U32_5219;
        Bool hoisted__Bool_5234 = U32_lte(_rc_U32_5219, _re_U32_5219);
        (void)hoisted__Bool_5234;
        if (hoisted__Bool_5234) {
            while (1) {
                Bool _wcond_Bool_5220 = U32_lt(_rc_U32_5219, _re_U32_5219);
                (void)_wcond_Bool_5220;
                if (_wcond_Bool_5220) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5219);
                U32_inc(&_rc_U32_5219);
                U32 hoisted__U32_5221 = 104;
                (void)hoisted__U32_5221;
                U32 hoisted__U32_5222 = U32_mul(i, hoisted__U32_5221);
                (void)hoisted__U32_5222;
                Type *hoisted__Type_5223 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5223;
                U64 hoisted__U64_5224 = (U64)(hoisted__U32_5222);
                (void)hoisted__U64_5224;
                Type_delete(hoisted__Type_5223, 1);
                Declaration *hoisted__Declaration_5225 = ptr_add(self->data, hoisted__U64_5224);
                (void)hoisted__Declaration_5225;
                (void)hoisted__Declaration_5225;
                Bool hoisted__Bool_5226 = 0;
                (void)hoisted__Bool_5226;
                Declaration_delete(hoisted__Declaration_5225, hoisted__Bool_5226);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5227 = U32_gt(_rc_U32_5219, _re_U32_5219);
                (void)_wcond_Bool_5227;
                if (_wcond_Bool_5227) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5219);
                U32_dec(&_rc_U32_5219);
                U32 hoisted__U32_5228 = 104;
                (void)hoisted__U32_5228;
                U32 hoisted__U32_5229 = U32_mul(i, hoisted__U32_5228);
                (void)hoisted__U32_5229;
                Type *hoisted__Type_5230 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5230;
                U64 hoisted__U64_5231 = (U64)(hoisted__U32_5229);
                (void)hoisted__U64_5231;
                Type_delete(hoisted__Type_5230, 1);
                Declaration *hoisted__Declaration_5232 = ptr_add(self->data, hoisted__U64_5231);
                (void)hoisted__Declaration_5232;
                (void)hoisted__Declaration_5232;
                Bool hoisted__Bool_5233 = 0;
                (void)hoisted__Bool_5233;
                Declaration_delete(hoisted__Declaration_5232, hoisted__Bool_5233);
            }
        }
    }
    U32 hoisted__U32_5235 = 0;
    (void)hoisted__U32_5235;
    self->count = hoisted__U32_5235;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5551 = 104;
    (void)hoisted__U32_5551;
    U32 hoisted__U32_5552 = U32_mul(self->cap, hoisted__U32_5551);
    (void)hoisted__U32_5552;
    Type *hoisted__Type_5553 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5553;
    U64 hoisted__U64_5554 = (U64)(hoisted__U32_5552);
    (void)hoisted__U64_5554;
    Type_delete(hoisted__Type_5553, 1);
    void * new_data = malloc(hoisted__U64_5554);
    {
        U32 _re_U32_5515 = self->count;
        (void)_re_U32_5515;
        U32 _rc_U32_5515 = 0;
        (void)_rc_U32_5515;
        Bool hoisted__Bool_5550 = U32_lte(_rc_U32_5515, _re_U32_5515);
        (void)hoisted__Bool_5550;
        if (hoisted__Bool_5550) {
            while (1) {
                Bool _wcond_Bool_5516 = U32_lt(_rc_U32_5515, _re_U32_5515);
                (void)_wcond_Bool_5516;
                if (_wcond_Bool_5516) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5515);
                U32_inc(&_rc_U32_5515);
                U32 hoisted__U32_5517 = 104;
                (void)hoisted__U32_5517;
                U32 hoisted__U32_5518 = U32_mul(i, hoisted__U32_5517);
                (void)hoisted__U32_5518;
                Type *hoisted__Type_5519 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5519;
                U64 hoisted__U64_5520 = (U64)(hoisted__U32_5518);
                (void)hoisted__U64_5520;
                Type_delete(hoisted__Type_5519, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5520);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5521 = 104;
                (void)hoisted__U32_5521;
                U32 hoisted__U32_5522 = U32_mul(i, hoisted__U32_5521);
                (void)hoisted__U32_5522;
                Type *hoisted__Type_5523 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5523;
                U64 hoisted__U64_5524 = (U64)(hoisted__U32_5522);
                (void)hoisted__U64_5524;
                Type_delete(hoisted__Type_5523, 1);
                U32 hoisted__U32_5525 = 104;
                (void)hoisted__U32_5525;
                Type *hoisted__Type_5526 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5526;
                void *hoisted__v_5527 = ptr_add(new_data, hoisted__U64_5524);
                (void)hoisted__v_5527;
                (void)hoisted__v_5527;
                U64 hoisted__U64_5528 = (U64)(hoisted__U32_5525);
                (void)hoisted__U64_5528;
                Type_delete(hoisted__Type_5526, 1);
                memcpy(hoisted__v_5527, cloned, hoisted__U64_5528);
                U32 hoisted__U32_5529 = 104;
                (void)hoisted__U32_5529;
                Type *hoisted__Type_5530 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5530;
                I32 hoisted__I32_5531 = 0;
                (void)hoisted__I32_5531;
                U64 hoisted__U64_5532 = (U64)(hoisted__U32_5529);
                (void)hoisted__U64_5532;
                Type_delete(hoisted__Type_5530, 1);
                memset(cloned, hoisted__I32_5531, hoisted__U64_5532);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5533 = U32_gt(_rc_U32_5515, _re_U32_5515);
                (void)_wcond_Bool_5533;
                if (_wcond_Bool_5533) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5515);
                U32_dec(&_rc_U32_5515);
                U32 hoisted__U32_5534 = 104;
                (void)hoisted__U32_5534;
                U32 hoisted__U32_5535 = U32_mul(i, hoisted__U32_5534);
                (void)hoisted__U32_5535;
                Type *hoisted__Type_5536 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5536;
                U64 hoisted__U64_5537 = (U64)(hoisted__U32_5535);
                (void)hoisted__U64_5537;
                Type_delete(hoisted__Type_5536, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5537);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5538 = 104;
                (void)hoisted__U32_5538;
                U32 hoisted__U32_5539 = U32_mul(i, hoisted__U32_5538);
                (void)hoisted__U32_5539;
                Type *hoisted__Type_5540 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5540;
                U64 hoisted__U64_5541 = (U64)(hoisted__U32_5539);
                (void)hoisted__U64_5541;
                Type_delete(hoisted__Type_5540, 1);
                U32 hoisted__U32_5542 = 104;
                (void)hoisted__U32_5542;
                Type *hoisted__Type_5543 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5543;
                void *hoisted__v_5544 = ptr_add(new_data, hoisted__U64_5541);
                (void)hoisted__v_5544;
                (void)hoisted__v_5544;
                U64 hoisted__U64_5545 = (U64)(hoisted__U32_5542);
                (void)hoisted__U64_5545;
                Type_delete(hoisted__Type_5543, 1);
                memcpy(hoisted__v_5544, cloned, hoisted__U64_5545);
                U32 hoisted__U32_5546 = 104;
                (void)hoisted__U32_5546;
                Type *hoisted__Type_5547 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5547;
                I32 hoisted__I32_5548 = 0;
                (void)hoisted__I32_5548;
                U64 hoisted__U64_5549 = (U64)(hoisted__U32_5546);
                (void)hoisted__U64_5549;
                Type_delete(hoisted__Type_5547, 1);
                memset(cloned, hoisted__I32_5548, hoisted__U64_5549);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5555 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5555->data = new_data;
    hoisted__Vec__Declaration_5555->count = self->count;
    hoisted__Vec__Declaration_5555->cap = self->cap;
    (void)hoisted__Vec__Declaration_5555;
    return hoisted__Vec__Declaration_5555;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5556 = 16;
    (void)hoisted__U32_5556;
    return hoisted__U32_5556;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5557 = 136;
    (void)hoisted__U32_5557;
    Type *hoisted__Type_5558 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5558;
    U64 hoisted__U64_5559 = (U64)(hoisted__U32_5557);
    (void)hoisted__U64_5559;
    Type_delete(hoisted__Type_5558, 1);
    void * hoisted__v_5560 = malloc(hoisted__U64_5559);
    (void)hoisted__v_5560;
    U32 hoisted__U32_5561 = 0;
    (void)hoisted__U32_5561;
    I64 hoisted__I64_5562 = 1;
    (void)hoisted__I64_5562;
    Vec__Expr *hoisted__Vec__Expr_5563 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5563->data = hoisted__v_5560;
    hoisted__Vec__Expr_5563->count = hoisted__U32_5561;
    hoisted__Vec__Expr_5563->cap = hoisted__I64_5562;
    (void)hoisted__Vec__Expr_5563;
    return hoisted__Vec__Expr_5563;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5564 = self->count;
        (void)_re_U32_5564;
        U32 _rc_U32_5564 = 0;
        (void)_rc_U32_5564;
        Bool hoisted__Bool_5579 = U32_lte(_rc_U32_5564, _re_U32_5564);
        (void)hoisted__Bool_5579;
        if (hoisted__Bool_5579) {
            while (1) {
                Bool _wcond_Bool_5565 = U32_lt(_rc_U32_5564, _re_U32_5564);
                (void)_wcond_Bool_5565;
                if (_wcond_Bool_5565) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5564);
                U32_inc(&_rc_U32_5564);
                U32 hoisted__U32_5566 = 136;
                (void)hoisted__U32_5566;
                U32 hoisted__U32_5567 = U32_mul(i, hoisted__U32_5566);
                (void)hoisted__U32_5567;
                Type *hoisted__Type_5568 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5568;
                U64 hoisted__U64_5569 = (U64)(hoisted__U32_5567);
                (void)hoisted__U64_5569;
                Type_delete(hoisted__Type_5568, 1);
                Expr *hoisted__Expr_5570 = ptr_add(self->data, hoisted__U64_5569);
                (void)hoisted__Expr_5570;
                (void)hoisted__Expr_5570;
                Bool hoisted__Bool_5571 = 0;
                (void)hoisted__Bool_5571;
                Expr_delete(hoisted__Expr_5570, hoisted__Bool_5571);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5572 = U32_gt(_rc_U32_5564, _re_U32_5564);
                (void)_wcond_Bool_5572;
                if (_wcond_Bool_5572) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5564);
                U32_dec(&_rc_U32_5564);
                U32 hoisted__U32_5573 = 136;
                (void)hoisted__U32_5573;
                U32 hoisted__U32_5574 = U32_mul(i, hoisted__U32_5573);
                (void)hoisted__U32_5574;
                Type *hoisted__Type_5575 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5575;
                U64 hoisted__U64_5576 = (U64)(hoisted__U32_5574);
                (void)hoisted__U64_5576;
                Type_delete(hoisted__Type_5575, 1);
                Expr *hoisted__Expr_5577 = ptr_add(self->data, hoisted__U64_5576);
                (void)hoisted__Expr_5577;
                (void)hoisted__Expr_5577;
                Bool hoisted__Bool_5578 = 0;
                (void)hoisted__Bool_5578;
                Expr_delete(hoisted__Expr_5577, hoisted__Bool_5578);
            }
        }
    }
    U32 hoisted__U32_5580 = 0;
    (void)hoisted__U32_5580;
    self->count = hoisted__U32_5580;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5896 = 136;
    (void)hoisted__U32_5896;
    U32 hoisted__U32_5897 = U32_mul(self->cap, hoisted__U32_5896);
    (void)hoisted__U32_5897;
    Type *hoisted__Type_5898 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5898;
    U64 hoisted__U64_5899 = (U64)(hoisted__U32_5897);
    (void)hoisted__U64_5899;
    Type_delete(hoisted__Type_5898, 1);
    void * new_data = malloc(hoisted__U64_5899);
    {
        U32 _re_U32_5860 = self->count;
        (void)_re_U32_5860;
        U32 _rc_U32_5860 = 0;
        (void)_rc_U32_5860;
        Bool hoisted__Bool_5895 = U32_lte(_rc_U32_5860, _re_U32_5860);
        (void)hoisted__Bool_5895;
        if (hoisted__Bool_5895) {
            while (1) {
                Bool _wcond_Bool_5861 = U32_lt(_rc_U32_5860, _re_U32_5860);
                (void)_wcond_Bool_5861;
                if (_wcond_Bool_5861) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5860);
                U32_inc(&_rc_U32_5860);
                U32 hoisted__U32_5862 = 136;
                (void)hoisted__U32_5862;
                U32 hoisted__U32_5863 = U32_mul(i, hoisted__U32_5862);
                (void)hoisted__U32_5863;
                Type *hoisted__Type_5864 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5864;
                U64 hoisted__U64_5865 = (U64)(hoisted__U32_5863);
                (void)hoisted__U64_5865;
                Type_delete(hoisted__Type_5864, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5865);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5866 = 136;
                (void)hoisted__U32_5866;
                U32 hoisted__U32_5867 = U32_mul(i, hoisted__U32_5866);
                (void)hoisted__U32_5867;
                Type *hoisted__Type_5868 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5868;
                U64 hoisted__U64_5869 = (U64)(hoisted__U32_5867);
                (void)hoisted__U64_5869;
                Type_delete(hoisted__Type_5868, 1);
                U32 hoisted__U32_5870 = 136;
                (void)hoisted__U32_5870;
                Type *hoisted__Type_5871 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5871;
                void *hoisted__v_5872 = ptr_add(new_data, hoisted__U64_5869);
                (void)hoisted__v_5872;
                (void)hoisted__v_5872;
                U64 hoisted__U64_5873 = (U64)(hoisted__U32_5870);
                (void)hoisted__U64_5873;
                Type_delete(hoisted__Type_5871, 1);
                memcpy(hoisted__v_5872, cloned, hoisted__U64_5873);
                U32 hoisted__U32_5874 = 136;
                (void)hoisted__U32_5874;
                Type *hoisted__Type_5875 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5875;
                I32 hoisted__I32_5876 = 0;
                (void)hoisted__I32_5876;
                U64 hoisted__U64_5877 = (U64)(hoisted__U32_5874);
                (void)hoisted__U64_5877;
                Type_delete(hoisted__Type_5875, 1);
                memset(cloned, hoisted__I32_5876, hoisted__U64_5877);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5878 = U32_gt(_rc_U32_5860, _re_U32_5860);
                (void)_wcond_Bool_5878;
                if (_wcond_Bool_5878) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5860);
                U32_dec(&_rc_U32_5860);
                U32 hoisted__U32_5879 = 136;
                (void)hoisted__U32_5879;
                U32 hoisted__U32_5880 = U32_mul(i, hoisted__U32_5879);
                (void)hoisted__U32_5880;
                Type *hoisted__Type_5881 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5881;
                U64 hoisted__U64_5882 = (U64)(hoisted__U32_5880);
                (void)hoisted__U64_5882;
                Type_delete(hoisted__Type_5881, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5882);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5883 = 136;
                (void)hoisted__U32_5883;
                U32 hoisted__U32_5884 = U32_mul(i, hoisted__U32_5883);
                (void)hoisted__U32_5884;
                Type *hoisted__Type_5885 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5885;
                U64 hoisted__U64_5886 = (U64)(hoisted__U32_5884);
                (void)hoisted__U64_5886;
                Type_delete(hoisted__Type_5885, 1);
                U32 hoisted__U32_5887 = 136;
                (void)hoisted__U32_5887;
                Type *hoisted__Type_5888 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5888;
                void *hoisted__v_5889 = ptr_add(new_data, hoisted__U64_5886);
                (void)hoisted__v_5889;
                (void)hoisted__v_5889;
                U64 hoisted__U64_5890 = (U64)(hoisted__U32_5887);
                (void)hoisted__U64_5890;
                Type_delete(hoisted__Type_5888, 1);
                memcpy(hoisted__v_5889, cloned, hoisted__U64_5890);
                U32 hoisted__U32_5891 = 136;
                (void)hoisted__U32_5891;
                Type *hoisted__Type_5892 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5892;
                I32 hoisted__I32_5893 = 0;
                (void)hoisted__I32_5893;
                U64 hoisted__U64_5894 = (U64)(hoisted__U32_5891);
                (void)hoisted__U64_5894;
                Type_delete(hoisted__Type_5892, 1);
                memset(cloned, hoisted__I32_5893, hoisted__U64_5894);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5900 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5900->data = new_data;
    hoisted__Vec__Expr_5900->count = self->count;
    hoisted__Vec__Expr_5900->cap = self->cap;
    (void)hoisted__Vec__Expr_5900;
    return hoisted__Vec__Expr_5900;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5901 = 16;
    (void)hoisted__U32_5901;
    return hoisted__U32_5901;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5902 = 8;
    (void)hoisted__U32_5902;
    Type *hoisted__Type_5903 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5903;
    U64 hoisted__U64_5904 = (U64)(hoisted__U32_5902);
    (void)hoisted__U64_5904;
    Type_delete(hoisted__Type_5903, 1);
    void * hoisted__v_5905 = malloc(hoisted__U64_5904);
    (void)hoisted__v_5905;
    U32 hoisted__U32_5906 = 0;
    (void)hoisted__U32_5906;
    I64 hoisted__I64_5907 = 1;
    (void)hoisted__I64_5907;
    Vec__I64 *hoisted__Vec__I64_5908 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5908->data = hoisted__v_5905;
    hoisted__Vec__I64_5908->count = hoisted__U32_5906;
    hoisted__Vec__I64_5908->cap = hoisted__I64_5907;
    (void)hoisted__Vec__I64_5908;
    return hoisted__Vec__I64_5908;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5909 = self->count;
        (void)_re_U32_5909;
        U32 _rc_U32_5909 = 0;
        (void)_rc_U32_5909;
        Bool hoisted__Bool_5924 = U32_lte(_rc_U32_5909, _re_U32_5909);
        (void)hoisted__Bool_5924;
        if (hoisted__Bool_5924) {
            while (1) {
                Bool _wcond_Bool_5910 = U32_lt(_rc_U32_5909, _re_U32_5909);
                (void)_wcond_Bool_5910;
                if (_wcond_Bool_5910) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5909);
                U32_inc(&_rc_U32_5909);
                U32 hoisted__U32_5911 = 8;
                (void)hoisted__U32_5911;
                U32 hoisted__U32_5912 = U32_mul(i, hoisted__U32_5911);
                (void)hoisted__U32_5912;
                Type *hoisted__Type_5913 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5913;
                U64 hoisted__U64_5914 = (U64)(hoisted__U32_5912);
                (void)hoisted__U64_5914;
                Type_delete(hoisted__Type_5913, 1);
                I64 *hoisted__I64_5915 = ptr_add(self->data, hoisted__U64_5914);
                (void)hoisted__I64_5915;
                (void)hoisted__I64_5915;
                Bool hoisted__Bool_5916 = 0;
                (void)hoisted__Bool_5916;
                I64_delete(hoisted__I64_5915, hoisted__Bool_5916);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5917 = U32_gt(_rc_U32_5909, _re_U32_5909);
                (void)_wcond_Bool_5917;
                if (_wcond_Bool_5917) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5909);
                U32_dec(&_rc_U32_5909);
                U32 hoisted__U32_5918 = 8;
                (void)hoisted__U32_5918;
                U32 hoisted__U32_5919 = U32_mul(i, hoisted__U32_5918);
                (void)hoisted__U32_5919;
                Type *hoisted__Type_5920 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5920;
                U64 hoisted__U64_5921 = (U64)(hoisted__U32_5919);
                (void)hoisted__U64_5921;
                Type_delete(hoisted__Type_5920, 1);
                I64 *hoisted__I64_5922 = ptr_add(self->data, hoisted__U64_5921);
                (void)hoisted__I64_5922;
                (void)hoisted__I64_5922;
                Bool hoisted__Bool_5923 = 0;
                (void)hoisted__Bool_5923;
                I64_delete(hoisted__I64_5922, hoisted__Bool_5923);
            }
        }
    }
    U32 hoisted__U32_5925 = 0;
    (void)hoisted__U32_5925;
    self->count = hoisted__U32_5925;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_6241 = 8;
    (void)hoisted__U32_6241;
    U32 hoisted__U32_6242 = U32_mul(self->cap, hoisted__U32_6241);
    (void)hoisted__U32_6242;
    Type *hoisted__Type_6243 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_6243;
    U64 hoisted__U64_6244 = (U64)(hoisted__U32_6242);
    (void)hoisted__U64_6244;
    Type_delete(hoisted__Type_6243, 1);
    void * new_data = malloc(hoisted__U64_6244);
    {
        U32 _re_U32_6205 = self->count;
        (void)_re_U32_6205;
        U32 _rc_U32_6205 = 0;
        (void)_rc_U32_6205;
        Bool hoisted__Bool_6240 = U32_lte(_rc_U32_6205, _re_U32_6205);
        (void)hoisted__Bool_6240;
        if (hoisted__Bool_6240) {
            while (1) {
                Bool _wcond_Bool_6206 = U32_lt(_rc_U32_6205, _re_U32_6205);
                (void)_wcond_Bool_6206;
                if (_wcond_Bool_6206) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6205);
                U32_inc(&_rc_U32_6205);
                U32 hoisted__U32_6207 = 8;
                (void)hoisted__U32_6207;
                U32 hoisted__U32_6208 = U32_mul(i, hoisted__U32_6207);
                (void)hoisted__U32_6208;
                Type *hoisted__Type_6209 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6209;
                U64 hoisted__U64_6210 = (U64)(hoisted__U32_6208);
                (void)hoisted__U64_6210;
                Type_delete(hoisted__Type_6209, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6210);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6211 = 8;
                (void)hoisted__U32_6211;
                U32 hoisted__U32_6212 = U32_mul(i, hoisted__U32_6211);
                (void)hoisted__U32_6212;
                Type *hoisted__Type_6213 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6213;
                U64 hoisted__U64_6214 = (U64)(hoisted__U32_6212);
                (void)hoisted__U64_6214;
                Type_delete(hoisted__Type_6213, 1);
                U32 hoisted__U32_6215 = 8;
                (void)hoisted__U32_6215;
                Type *hoisted__Type_6216 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6216;
                void *hoisted__v_6217 = ptr_add(new_data, hoisted__U64_6214);
                (void)hoisted__v_6217;
                (void)hoisted__v_6217;
                U64 hoisted__U64_6218 = (U64)(hoisted__U32_6215);
                (void)hoisted__U64_6218;
                Type_delete(hoisted__Type_6216, 1);
                memcpy(hoisted__v_6217, &cloned, hoisted__U64_6218);
                U32 hoisted__U32_6219 = 8;
                (void)hoisted__U32_6219;
                Type *hoisted__Type_6220 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6220;
                I32 hoisted__I32_6221 = 0;
                (void)hoisted__I32_6221;
                U64 hoisted__U64_6222 = (U64)(hoisted__U32_6219);
                (void)hoisted__U64_6222;
                Type_delete(hoisted__Type_6220, 1);
                memset(&cloned, hoisted__I32_6221, hoisted__U64_6222);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6223 = U32_gt(_rc_U32_6205, _re_U32_6205);
                (void)_wcond_Bool_6223;
                if (_wcond_Bool_6223) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6205);
                U32_dec(&_rc_U32_6205);
                U32 hoisted__U32_6224 = 8;
                (void)hoisted__U32_6224;
                U32 hoisted__U32_6225 = U32_mul(i, hoisted__U32_6224);
                (void)hoisted__U32_6225;
                Type *hoisted__Type_6226 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6226;
                U64 hoisted__U64_6227 = (U64)(hoisted__U32_6225);
                (void)hoisted__U64_6227;
                Type_delete(hoisted__Type_6226, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6227);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6228 = 8;
                (void)hoisted__U32_6228;
                U32 hoisted__U32_6229 = U32_mul(i, hoisted__U32_6228);
                (void)hoisted__U32_6229;
                Type *hoisted__Type_6230 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6230;
                U64 hoisted__U64_6231 = (U64)(hoisted__U32_6229);
                (void)hoisted__U64_6231;
                Type_delete(hoisted__Type_6230, 1);
                U32 hoisted__U32_6232 = 8;
                (void)hoisted__U32_6232;
                Type *hoisted__Type_6233 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6233;
                void *hoisted__v_6234 = ptr_add(new_data, hoisted__U64_6231);
                (void)hoisted__v_6234;
                (void)hoisted__v_6234;
                U64 hoisted__U64_6235 = (U64)(hoisted__U32_6232);
                (void)hoisted__U64_6235;
                Type_delete(hoisted__Type_6233, 1);
                memcpy(hoisted__v_6234, &cloned, hoisted__U64_6235);
                U32 hoisted__U32_6236 = 8;
                (void)hoisted__U32_6236;
                Type *hoisted__Type_6237 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6237;
                I32 hoisted__I32_6238 = 0;
                (void)hoisted__I32_6238;
                U64 hoisted__U64_6239 = (U64)(hoisted__U32_6236);
                (void)hoisted__U64_6239;
                Type_delete(hoisted__Type_6237, 1);
                memset(&cloned, hoisted__I32_6238, hoisted__U64_6239);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6245 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6245->data = new_data;
    hoisted__Vec__I64_6245->count = self->count;
    hoisted__Vec__I64_6245->cap = self->cap;
    (void)hoisted__Vec__I64_6245;
    return hoisted__Vec__I64_6245;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_6246 = 16;
    (void)hoisted__U32_6246;
    return hoisted__U32_6246;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7481 = 3;
    (void)hoisted__U32_7481;
    Array__Str *_va_Array_195 = Array__Str_new(hoisted__U32_7481);
    (void)_va_Array_195;
    I64 _va_Array_195_ek = 0;
    (void)_va_Array_195_ek;
    OutOfBounds *_va_Array_195_eo = malloc(sizeof(OutOfBounds));
    _va_Array_195_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_195_eo;
    U32 hoisted__U32_7482 = 0;
    (void)hoisted__U32_7482;
    Str *hoisted__Str_7483 = Str_clone(loc);
    (void)hoisted__Str_7483;
    static Str hoisted__Str_7484 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7484;
    Array__Str_set(_va_Array_195, hoisted__U32_7482, hoisted__Str_7483, &_va_Array_195_ek, _va_Array_195_eo, &hoisted__Str_7484);
    Str_delete(&hoisted__Str_7484, (Bool){0});
    U32 hoisted__U32_7485 = 1;
    (void)hoisted__U32_7485;
    static Str hoisted__Str_7486 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7486;
    static Str hoisted__Str_7487 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7487;
    Array__Str_set(_va_Array_195, hoisted__U32_7485, &hoisted__Str_7486, &_va_Array_195_ek, _va_Array_195_eo, &hoisted__Str_7487);
    Str_delete(&hoisted__Str_7487, (Bool){0});
    Array__Str *hoisted__Array__Str_7488 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7488;
    U32 hoisted__U32_7489 = 2;
    (void)hoisted__U32_7489;
    Str *hoisted__Str_7490 = format(hoisted__Array__Str_7488);
    (void)hoisted__Str_7490;
    static Str hoisted__Str_7491 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7491;
    Array__Str_set(_va_Array_195, hoisted__U32_7489, hoisted__Str_7490, &_va_Array_195_ek, _va_Array_195_eo, &hoisted__Str_7491);
    OutOfBounds_delete(_va_Array_195_eo, 1);
    Str_delete(&hoisted__Str_7491, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_195);
    I64 hoisted__I64_7492 = 1;
    (void)hoisted__I64_7492;
    exit(hoisted__I64_7492);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7501 = 1;
    (void)hoisted__U32_7501;
    Array__Str *_va_Array_197 = Array__Str_new(hoisted__U32_7501);
    (void)_va_Array_197;
    I64 _va_Array_197_ek = 0;
    (void)_va_Array_197_ek;
    OutOfBounds *_va_Array_197_eo = malloc(sizeof(OutOfBounds));
    _va_Array_197_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_197_eo;
    U32 hoisted__U32_7502 = 0;
    (void)hoisted__U32_7502;
    static Str hoisted__Str_7503 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7503;
    static Str hoisted__Str_7504 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7504;
    Array__Str_set(_va_Array_197, hoisted__U32_7502, &hoisted__Str_7503, &_va_Array_197_ek, _va_Array_197_eo, &hoisted__Str_7504);
    OutOfBounds_delete(_va_Array_197_eo, 1);
    Str_delete(&hoisted__Str_7504, (Bool){0});
    panic(_va_Array_197, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7509 = not(cond);
    (void)hoisted__Bool_7509;
    if (hoisted__Bool_7509) {
        U32 hoisted__U32_7505 = 1;
        (void)hoisted__U32_7505;
        Array__Str *_va_Array_198 = Array__Str_new(hoisted__U32_7505);
        (void)_va_Array_198;
        I64 _va_Array_198_ek = 0;
        (void)_va_Array_198_ek;
        OutOfBounds *_va_Array_198_eo = malloc(sizeof(OutOfBounds));
        _va_Array_198_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_198_eo;
        U32 hoisted__U32_7506 = 0;
        (void)hoisted__U32_7506;
        static Str hoisted__Str_7507 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7507;
        static Str hoisted__Str_7508 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7508;
        Array__Str_set(_va_Array_198, hoisted__U32_7506, &hoisted__Str_7507, &_va_Array_198_ek, _va_Array_198_eo, &hoisted__Str_7508);
        OutOfBounds_delete(_va_Array_198_eo, 1);
        Str_delete(&hoisted__Str_7508, (Bool){0});
        panic(_va_Array_198, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7519 = parts;
        (void)_fc_Array__Str_7519;
        (void)_fc_Array__Str_7519;
        U32 _fi_USize_7519 = 0;
        (void)_fi_USize_7519;
        I64 _forin_err_kind_7519 = 0;
        (void)_forin_err_kind_7519;
        OutOfBounds *_forin_OutOfBounds_7519 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_7519->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_7519;
        while (1) {
            U32 hoisted__U32_7529 = Array__Str_len(_fc_Array__Str_7519);
            (void)hoisted__U32_7529;
            Bool _wcond_Bool_7520 = U32_lt(_fi_USize_7519, hoisted__U32_7529);
            (void)_wcond_Bool_7520;
            if (_wcond_Bool_7520) {
            } else {
                break;
            }
            static Str hoisted__Str_7530 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
            (void)hoisted__Str_7530;
            Str *s = Array__Str_get(_fc_Array__Str_7519, &_fi_USize_7519, &_forin_err_kind_7519, _forin_OutOfBounds_7519, &hoisted__Str_7530);
            I64 hoisted__I64_7531 = 0;
            (void)hoisted__I64_7531;
            Bool hoisted__Bool_7532 = I64_eq(_forin_err_kind_7519, hoisted__I64_7531);
            (void)hoisted__Bool_7532;
            Bool hoisted__Bool_7533 = not(hoisted__Bool_7532);
            (void)hoisted__Bool_7533;
            if (hoisted__Bool_7533) {
                U32 hoisted__U32_7521 = 2;
                (void)hoisted__U32_7521;
                Array__Str *_va_Array_200 = Array__Str_new(hoisted__U32_7521);
                (void)_va_Array_200;
                I64 _va_Array_200_ek = 0;
                (void)_va_Array_200_ek;
                OutOfBounds *_va_Array_200_eo = malloc(sizeof(OutOfBounds));
                _va_Array_200_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_200_eo;
                U32 hoisted__U32_7522 = 0;
                (void)hoisted__U32_7522;
                static Str hoisted__Str_7523 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7523;
                static Str hoisted__Str_7524 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7524;
                Array__Str_set(_va_Array_200, hoisted__U32_7522, &hoisted__Str_7523, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7524);
                Str_delete(&hoisted__Str_7524, (Bool){0});
                U32 hoisted__U32_7525 = 1;
                (void)hoisted__U32_7525;
                static Str hoisted__Str_7526 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7526;
                static Str hoisted__Str_7527 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7527;
                Array__Str_set(_va_Array_200, hoisted__U32_7525, &hoisted__Str_7526, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7527);
                OutOfBounds_delete(_va_Array_200_eo, 1);
                Str_delete(&hoisted__Str_7527, (Bool){0});
                static Str hoisted__Str_7528 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7528;
                panic(_va_Array_200, &hoisted__Str_7528);
                Str_delete(&hoisted__Str_7528, (Bool){0});
            }
            U32 hoisted__U32_7534 = 1;
            (void)hoisted__U32_7534;
            U32 hoisted__U32_7535 = U32_add(_fi_USize_7519, hoisted__U32_7534);
            (void)hoisted__U32_7535;
            _fi_USize_7519 = hoisted__U32_7535;
            print_single(s);
            Str_delete(&hoisted__Str_7530, (Bool){0});
        }
        OutOfBounds_delete(_forin_OutOfBounds_7519, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7581 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7581;
    return hoisted__Bool_7581;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7590 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7590;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7590;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7591 = 0;
    (void)hoisted__U32_7591;
    U64 hoisted__U64_7592 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7591); });
    (void)hoisted__U64_7592;
    return hoisted__U64_7592;
}

U32 Range_size(void) {
    U32 hoisted__U32_7623 = 16;
    (void)hoisted__U32_7623;
    return hoisted__U32_7623;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7754 = 3;
    (void)hoisted__I64_7754;
    static Str hoisted__Str_7755 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7755;
    assert_eq__I64(result, hoisted__I64_7754, &hoisted__Str_7755);
    Str_delete(&hoisted__Str_7755, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7762 = 15;
    (void)hoisted__I64_7762;
    static Str hoisted__Str_7763 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7763;
    assert_eq__I64(result, hoisted__I64_7762, &hoisted__Str_7763);
    Str_delete(&hoisted__Str_7763, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7770 = 26;
    (void)hoisted__I64_7770;
    static Str hoisted__Str_7771 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7771;
    assert_eq__I64(result, hoisted__I64_7770, &hoisted__Str_7771);
    Str_delete(&hoisted__Str_7771, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7774 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7774;
    static Str hoisted__Str_7775 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7775;
    assert_eq__Str(&result, &hoisted__Str_7774, &hoisted__Str_7775);
    Str_delete(&hoisted__Str_7774, (Bool){0});
    Str_delete(&hoisted__Str_7775, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7803 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7803;
    static Str hoisted__Str_7804 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7804;
    assert_eq__Str(&r, &hoisted__Str_7803, &hoisted__Str_7804);
    Str_delete(&hoisted__Str_7803, (Bool){0});
    Str_delete(&hoisted__Str_7804, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7808 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7808;
    static Str hoisted__Str_7809 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7809;
    assert_eq__Str(&r2, &hoisted__Str_7808, &hoisted__Str_7809);
    Str_delete(&hoisted__Str_7808, (Bool){0});
    Str_delete(&hoisted__Str_7809, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7844 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7844;
    static Str hoisted__Str_7845 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7845;
    assert_eq__Str(&d, &hoisted__Str_7844, &hoisted__Str_7845);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7844, (Bool){0});
    Str_delete(&hoisted__Str_7845, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7856 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7856;
    static Str hoisted__Str_7857 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7857;
    assert_eq__Str(&d2, &hoisted__Str_7856, &hoisted__Str_7857);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7856, (Bool){0});
    Str_delete(&hoisted__Str_7857, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7869 = 106;
    (void)hoisted__I64_7869;
    static Str hoisted__Str_7870 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7870;
    assert_eq__I64(d3, hoisted__I64_7869, &hoisted__Str_7870);
    Str_delete(&hoisted__Str_7870, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_8469 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8469;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8469);
    Str_delete(&hoisted__Str_8469, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    static Str hoisted__Str_8470 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8470;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8470);
    Str_delete(&hoisted__Str_8470, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8472 = 8;
    (void)hoisted__I64_8472;
    static Str hoisted__Str_8473 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8473;
    assert_eq__I64(result, hoisted__I64_8472, &hoisted__Str_8473);
    Str_delete(&hoisted__Str_8473, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8476 = 1;
    (void)hoisted__Bool_8476;
    static Str hoisted__Str_8477 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8477;
    assert(hoisted__Bool_8476, &hoisted__Str_8477);
    Str_delete(&hoisted__Str_8477, (Bool){0});
    Bool hoisted__Bool_8480 = 1;
    (void)hoisted__Bool_8480;
    static Str hoisted__Str_8481 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8481;
    assert(hoisted__Bool_8480, &hoisted__Str_8481);
    Str_delete(&hoisted__Str_8481, (Bool){0});
}

void test_fold_f32(void) {
    static Str hoisted__Str_8486 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8486;
    static Str hoisted__Str_8487 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8487;
    static Str hoisted__Str_8488 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8488;
    assert_eq__Str(&hoisted__Str_8486, &hoisted__Str_8487, &hoisted__Str_8488);
    Str_delete(&hoisted__Str_8486, (Bool){0});
    Str_delete(&hoisted__Str_8487, (Bool){0});
    Str_delete(&hoisted__Str_8488, (Bool){0});
    static Str hoisted__Str_8491 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8491;
    static Str hoisted__Str_8492 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8492;
    static Str hoisted__Str_8493 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8493;
    assert_eq__Str(&hoisted__Str_8491, &hoisted__Str_8492, &hoisted__Str_8493);
    Str_delete(&hoisted__Str_8491, (Bool){0});
    Str_delete(&hoisted__Str_8492, (Bool){0});
    Str_delete(&hoisted__Str_8493, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8498 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8498;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8498;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8499 = 0;
    (void)hoisted__U32_8499;
    U64 hoisted__U64_8500 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8499); });
    (void)hoisted__U64_8500;
    return hoisted__U64_8500;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8531 = 16;
    (void)hoisted__U32_8531;
    return hoisted__U32_8531;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8532 = 42;
    (void)hoisted__I64_8532;
    static Str hoisted__Str_8533 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8533;
    assert_eq__I64(v.x, hoisted__I64_8532, &hoisted__Str_8533);
    Str_delete(&hoisted__Str_8533, (Bool){0});
    I64 hoisted__I64_8534 = 99;
    (void)hoisted__I64_8534;
    static Str hoisted__Str_8535 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8535;
    assert_eq__I64(v.y, hoisted__I64_8534, &hoisted__Str_8535);
    Str_delete(&hoisted__Str_8535, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8538 = 10;
    (void)hoisted__I64_8538;
    static Str hoisted__Str_8539 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8539;
    assert_eq__I64(p.x, hoisted__I64_8538, &hoisted__Str_8539);
    Str_delete(&hoisted__Str_8539, (Bool){0});
    I64 hoisted__I64_8540 = 20;
    (void)hoisted__I64_8540;
    static Str hoisted__Str_8541 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8541;
    assert_eq__I64(p.y, hoisted__I64_8540, &hoisted__Str_8541);
    Str_delete(&hoisted__Str_8541, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8547 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8547;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8547;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8548 = 0;
    (void)hoisted__U32_8548;
    U64 hoisted__U64_8549 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8548); });
    (void)hoisted__U64_8549;
    return hoisted__U64_8549;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8580 = 32;
    (void)hoisted__U32_8580;
    return hoisted__U32_8580;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8581 = 5;
    (void)hoisted__I64_8581;
    static Str hoisted__Str_8582 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8582;
    assert_eq__I64(r.top_left.x, hoisted__I64_8581, &hoisted__Str_8582);
    Str_delete(&hoisted__Str_8582, (Bool){0});
    I64 hoisted__I64_8583 = 10;
    (void)hoisted__I64_8583;
    static Str hoisted__Str_8584 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8584;
    assert_eq__I64(r.top_left.y, hoisted__I64_8583, &hoisted__Str_8584);
    Str_delete(&hoisted__Str_8584, (Bool){0});
    I64 hoisted__I64_8585 = 100;
    (void)hoisted__I64_8585;
    static Str hoisted__Str_8586 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8586;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8585, &hoisted__Str_8586);
    Str_delete(&hoisted__Str_8586, (Bool){0});
    I64 hoisted__I64_8587 = 200;
    (void)hoisted__I64_8587;
    static Str hoisted__Str_8588 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8588;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8587, &hoisted__Str_8588);
    Str_delete(&hoisted__Str_8588, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8590 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8590;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8590;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8591 = 0;
    (void)hoisted__U32_8591;
    U64 hoisted__U64_8592 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8591); });
    (void)hoisted__U64_8592;
    return hoisted__U64_8592;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8635 = 12;
    (void)hoisted__U32_8635;
    return hoisted__U32_8635;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8639 = F32_to_str(v.x);
    (void)hoisted__Str_8639;
    static Str hoisted__Str_8640 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8640;
    static Str hoisted__Str_8641 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8641;
    assert_eq__Str(hoisted__Str_8639, &hoisted__Str_8640, &hoisted__Str_8641);
    Str_delete(hoisted__Str_8639, 1);
    Str_delete(&hoisted__Str_8640, (Bool){0});
    Str_delete(&hoisted__Str_8641, (Bool){0});
    Str *hoisted__Str_8642 = F32_to_str(v.y);
    (void)hoisted__Str_8642;
    static Str hoisted__Str_8643 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8643;
    static Str hoisted__Str_8644 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8644;
    assert_eq__Str(hoisted__Str_8642, &hoisted__Str_8643, &hoisted__Str_8644);
    Str_delete(hoisted__Str_8642, 1);
    Str_delete(&hoisted__Str_8643, (Bool){0});
    Str_delete(&hoisted__Str_8644, (Bool){0});
    Str *hoisted__Str_8645 = F32_to_str(v.z);
    (void)hoisted__Str_8645;
    static Str hoisted__Str_8646 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8646;
    static Str hoisted__Str_8647 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8647;
    assert_eq__Str(hoisted__Str_8645, &hoisted__Str_8646, &hoisted__Str_8647);
    Str_delete(hoisted__Str_8645, 1);
    Str_delete(&hoisted__Str_8646, (Bool){0});
    Str_delete(&hoisted__Str_8647, (Bool){0});
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
    Bool hoisted__Bool_8652 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8652;
    if (hoisted__Bool_8652) {
        Bool hoisted__Bool_8649 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8649;
        { Bool _ret_val = hoisted__Bool_8649;
                return _ret_val; }
    }
    Bool hoisted__Bool_8653 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8653;
    if (hoisted__Bool_8653) {
        Bool hoisted__Bool_8650 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8650;
        { Bool _ret_val = hoisted__Bool_8650;
                return _ret_val; }
    }
    Bool hoisted__Bool_8654 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8654;
    if (hoisted__Bool_8654) {
        Bool hoisted__Bool_8651 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8651;
        { Bool _ret_val = hoisted__Bool_8651;
                return _ret_val; }
    }
    Bool hoisted__Bool_8655 = 0;
    (void)hoisted__Bool_8655;
    return hoisted__Bool_8655;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8663 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8663;
    if (hoisted__Bool_8663) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8664 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8664;
    if (hoisted__Bool_8664) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8665 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8665;
    if (hoisted__Bool_8665) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8666 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8666;
    UNREACHABLE(&hoisted__Str_8666);
    Str_delete(&hoisted__Str_8666, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8667 = 4;
    (void)hoisted__U32_8667;
    return hoisted__U32_8667;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8668 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8668;
    static Str hoisted__Str_8669 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8669;
    assert(hoisted__Bool_8668, &hoisted__Str_8669);
    Str_delete(&hoisted__Str_8669, (Bool){0});
    Bool hoisted__Bool_8670 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8670;
    Bool hoisted__Bool_8671 = not(hoisted__Bool_8670);
    (void)hoisted__Bool_8671;
    static Str hoisted__Str_8672 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8672;
    assert(hoisted__Bool_8671, &hoisted__Str_8672);
    Str_delete(&hoisted__Str_8672, (Bool){0});
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
    Bool hoisted__Bool_8673 = is(self, other);
    (void)hoisted__Bool_8673;
    return hoisted__Bool_8673;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8691 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8691;
    if (hoisted__Bool_8691) {
        I64 *hoisted__I64_8687 = get_payload(self);
        (void)hoisted__I64_8687;
        (void)hoisted__I64_8687;
        Bool hoisted__Bool_8688 = 0;
        (void)hoisted__Bool_8688;
        I64_delete(hoisted__I64_8687, hoisted__Bool_8688);
    }
    Bool hoisted__Bool_8692 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8692;
    if (hoisted__Bool_8692) {
        Str *hoisted__Str_8689 = get_payload(self);
        (void)hoisted__Str_8689;
        (void)hoisted__Str_8689;
        Bool hoisted__Bool_8690 = 0;
        (void)hoisted__Bool_8690;
        Str_delete(hoisted__Str_8689, hoisted__Bool_8690);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8723 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8723;
    if (hoisted__Bool_8723) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8720 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8720;
        { Token * _ret_val = hoisted__Token_8720;
                return _ret_val; }
    }
    Bool hoisted__Bool_8724 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8724;
    if (hoisted__Bool_8724) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8721 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8721;
        Token *hoisted__Token_8722 = Token_Name(hoisted__Str_8721);
        (void)hoisted__Token_8722;
        { Token * _ret_val = hoisted__Token_8722;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8725 = 24;
    (void)hoisted__U32_8725;
    return hoisted__U32_8725;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8727 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8727;
    static Str hoisted__Str_8728 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8728;
    assert(hoisted__Bool_8727, &hoisted__Str_8728);
    Str_delete(&hoisted__Str_8728, (Bool){0});
    Bool hoisted__Bool_8729 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8729;
    Bool hoisted__Bool_8730 = not(hoisted__Bool_8729);
    (void)hoisted__Bool_8730;
    static Str hoisted__Str_8731 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8731;
    assert(hoisted__Bool_8730, &hoisted__Str_8731);
    Str_delete(&hoisted__Str_8731, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8732 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8732;
    static Str hoisted__Str_8733 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8733;
    assert(hoisted__Bool_8732, &hoisted__Str_8733);
    Str_delete(&hoisted__Str_8733, (Bool){0});
    Bool hoisted__Bool_8734 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8734;
    Bool hoisted__Bool_8735 = not(hoisted__Bool_8734);
    (void)hoisted__Bool_8735;
    static Str hoisted__Str_8736 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8736;
    assert(hoisted__Bool_8735, &hoisted__Str_8736);
    Str_delete(&hoisted__Str_8736, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8739 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8739;
    static Str hoisted__Str_8740 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8740;
    assert(hoisted__Bool_8739, &hoisted__Str_8740);
    Str_delete(&hoisted__Str_8740, (Bool){0});
    Bool hoisted__Bool_8741 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8741;
    Bool hoisted__Bool_8742 = not(hoisted__Bool_8741);
    (void)hoisted__Bool_8742;
    static Str hoisted__Str_8743 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8743;
    assert(hoisted__Bool_8742, &hoisted__Str_8743);
    Str_delete(&hoisted__Str_8743, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8898 = I64_neq(a, b);
    (void)hoisted__Bool_8898;
    if (hoisted__Bool_8898) {
        U32 hoisted__U32_8882 = 5;
        (void)hoisted__U32_8882;
        Array__Str *_va_Array_246 = Array__Str_new(hoisted__U32_8882);
        (void)_va_Array_246;
        I64 _va_Array_246_ek = 0;
        (void)_va_Array_246_ek;
        OutOfBounds *_va_Array_246_eo = malloc(sizeof(OutOfBounds));
        _va_Array_246_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_246_eo;
        U32 hoisted__U32_8883 = 0;
        (void)hoisted__U32_8883;
        static Str hoisted__Str_8884 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8884;
        static Str hoisted__Str_8885 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8885;
        Array__Str_set(_va_Array_246, hoisted__U32_8883, &hoisted__Str_8884, &_va_Array_246_ek, _va_Array_246_eo, &hoisted__Str_8885);
        Str_delete(&hoisted__Str_8885, (Bool){0});
        U32 hoisted__U32_8886 = 1;
        (void)hoisted__U32_8886;
        Str *hoisted__Str_8887 = I64_to_str(a);
        (void)hoisted__Str_8887;
        static Str hoisted__Str_8888 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8888;
        Array__Str_set(_va_Array_246, hoisted__U32_8886, hoisted__Str_8887, &_va_Array_246_ek, _va_Array_246_eo, &hoisted__Str_8888);
        Str_delete(&hoisted__Str_8888, (Bool){0});
        U32 hoisted__U32_8889 = 2;
        (void)hoisted__U32_8889;
        static Str hoisted__Str_8890 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8890;
        static Str hoisted__Str_8891 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8891;
        Array__Str_set(_va_Array_246, hoisted__U32_8889, &hoisted__Str_8890, &_va_Array_246_ek, _va_Array_246_eo, &hoisted__Str_8891);
        Str_delete(&hoisted__Str_8891, (Bool){0});
        U32 hoisted__U32_8892 = 3;
        (void)hoisted__U32_8892;
        Str *hoisted__Str_8893 = I64_to_str(b);
        (void)hoisted__Str_8893;
        static Str hoisted__Str_8894 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8894;
        Array__Str_set(_va_Array_246, hoisted__U32_8892, hoisted__Str_8893, &_va_Array_246_ek, _va_Array_246_eo, &hoisted__Str_8894);
        Str_delete(&hoisted__Str_8894, (Bool){0});
        U32 hoisted__U32_8895 = 4;
        (void)hoisted__U32_8895;
        static Str hoisted__Str_8896 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8896;
        static Str hoisted__Str_8897 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8897;
        Array__Str_set(_va_Array_246, hoisted__U32_8895, &hoisted__Str_8896, &_va_Array_246_ek, _va_Array_246_eo, &hoisted__Str_8897);
        OutOfBounds_delete(_va_Array_246_eo, 1);
        Str_delete(&hoisted__Str_8897, (Bool){0});
        panic(_va_Array_246, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8915 = Str_neq(a, b);
    (void)hoisted__Bool_8915;
    if (hoisted__Bool_8915) {
        U32 hoisted__U32_8899 = 5;
        (void)hoisted__U32_8899;
        Array__Str *_va_Array_247 = Array__Str_new(hoisted__U32_8899);
        (void)_va_Array_247;
        I64 _va_Array_247_ek = 0;
        (void)_va_Array_247_ek;
        OutOfBounds *_va_Array_247_eo = malloc(sizeof(OutOfBounds));
        _va_Array_247_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_247_eo;
        U32 hoisted__U32_8900 = 0;
        (void)hoisted__U32_8900;
        static Str hoisted__Str_8901 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8901;
        static Str hoisted__Str_8902 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8902;
        Array__Str_set(_va_Array_247, hoisted__U32_8900, &hoisted__Str_8901, &_va_Array_247_ek, _va_Array_247_eo, &hoisted__Str_8902);
        Str_delete(&hoisted__Str_8902, (Bool){0});
        U32 hoisted__U32_8903 = 1;
        (void)hoisted__U32_8903;
        Str *hoisted__Str_8904 = Str_to_str(a);
        (void)hoisted__Str_8904;
        static Str hoisted__Str_8905 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8905;
        Array__Str_set(_va_Array_247, hoisted__U32_8903, hoisted__Str_8904, &_va_Array_247_ek, _va_Array_247_eo, &hoisted__Str_8905);
        Str_delete(&hoisted__Str_8905, (Bool){0});
        U32 hoisted__U32_8906 = 2;
        (void)hoisted__U32_8906;
        static Str hoisted__Str_8907 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8907;
        static Str hoisted__Str_8908 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8908;
        Array__Str_set(_va_Array_247, hoisted__U32_8906, &hoisted__Str_8907, &_va_Array_247_ek, _va_Array_247_eo, &hoisted__Str_8908);
        Str_delete(&hoisted__Str_8908, (Bool){0});
        U32 hoisted__U32_8909 = 3;
        (void)hoisted__U32_8909;
        Str *hoisted__Str_8910 = Str_to_str(b);
        (void)hoisted__Str_8910;
        static Str hoisted__Str_8911 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8911;
        Array__Str_set(_va_Array_247, hoisted__U32_8909, hoisted__Str_8910, &_va_Array_247_ek, _va_Array_247_eo, &hoisted__Str_8911);
        Str_delete(&hoisted__Str_8911, (Bool){0});
        U32 hoisted__U32_8912 = 4;
        (void)hoisted__U32_8912;
        static Str hoisted__Str_8913 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8913;
        static Str hoisted__Str_8914 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8914;
        Array__Str_set(_va_Array_247, hoisted__U32_8912, &hoisted__Str_8913, &_va_Array_247_ek, _va_Array_247_eo, &hoisted__Str_8914);
        OutOfBounds_delete(_va_Array_247_eo, 1);
        Str_delete(&hoisted__Str_8914, (Bool){0});
        panic(_va_Array_247, loc);
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
void *Array__Str_get_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3, void *_a4) {
    (void)til_env;
    return (void *)Array__Str_get(_a0, _a1, _a2, _a3, _a4);
}
static __attribute__((unused)) TilClosure Array__Str_get_dyn__til_closure = { (void *)Array__Str_get_dyn, NULL, NULL };
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
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit55 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit55; });
        if (*index == 1LL) return ({ static Str _lit56 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit56; });
        if (*index == 2LL) return ({ static Str _lit57 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit57; });
        if (*index == 3LL) return ({ static Str _lit58 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit58; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit59 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit59; });
        if (*index == 1LL) return ({ static Str _lit60 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit60; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit61 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit61; });
        if (*index == 1LL) return ({ static Str _lit62 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit62; });
        if (*index == 2LL) return ({ static Str _lit63 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit63; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit64 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit64; });
        if (*index == 1LL) return ({ static Str _lit65 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit65; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit66 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit66; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit67 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit67; });
        if (*index == 1LL) return ({ static Str _lit68 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit68; });
        if (*index == 2LL) return ({ static Str _lit69 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit69; });
        if (*index == 3LL) return ({ static Str _lit70 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit70; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit71 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit71; });
        if (*index == 1LL) return ({ static Str _lit72 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit72; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit73 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit73; });
        if (*index == 1LL) return ({ static Str _lit74 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit74; });
        if (*index == 2LL) return ({ static Str _lit75 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit75; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit76 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit76; });
        if (*index == 1LL) return ({ static Str _lit77 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit77; });
        if (*index == 2LL) return ({ static Str _lit78 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit78; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit79 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit79; });
        if (*index == 1LL) return ({ static Str _lit80 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit80; });
        if (*index == 2LL) return ({ static Str _lit81 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit81; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit82 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit82; });
        if (*index == 1LL) return ({ static Str _lit83 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit83; });
        if (*index == 2LL) return ({ static Str _lit84 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit84; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit85 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit85; });
        if (*index == 1LL) return ({ static Str _lit86 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit86; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit87 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit87; });
        if (*index == 1LL) return ({ static Str _lit88 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit88; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit89 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit89; });
        if (*index == 1LL) return ({ static Str _lit90 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit90; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit91 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit91; });
        if (*index == 1LL) return ({ static Str _lit92 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit92; });
        if (*index == 2LL) return ({ static Str _lit93 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT}; &_lit93; });
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
        if (*index == 0LL) return ({ static Str _lit94 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit94; });
        if (*index == 1LL) return ({ static Str _lit95 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit95; });
        if (*index == 2LL) return ({ static Str _lit96 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit96; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit97 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit97; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit98 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit98; });
        if (*index == 1LL) return ({ static Str _lit99 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit99; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit100 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit100; });
        if (*index == 1LL) return ({ static Str _lit101 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit101; });
        if (*index == 2LL) return ({ static Str _lit102 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit102; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit103 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit103; });
        if (*index == 1LL) return ({ static Str _lit104 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit104; });
        if (*index == 2LL) return ({ static Str _lit105 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit105; });
        if (*index == 3LL) return ({ static Str _lit106 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit106; });
        if (*index == 4LL) return ({ static Str _lit107 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit107; });
        if (*index == 5LL) return ({ static Str _lit108 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit108; });
        if (*index == 6LL) return ({ static Str _lit109 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit109; });
        if (*index == 7LL) return ({ static Str _lit110 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit110; });
        if (*index == 8LL) return ({ static Str _lit111 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit111; });
        if (*index == 9LL) return ({ static Str _lit112 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit112; });
        if (*index == 10LL) return ({ static Str _lit113 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit113; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit114 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit114; });
        if (*index == 1LL) return ({ static Str _lit115 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit115; });
        if (*index == 2LL) return ({ static Str _lit116 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit116; });
        if (*index == 3LL) return ({ static Str _lit117 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit117; });
        if (*index == 4LL) return ({ static Str _lit118 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit118; });
        if (*index == 5LL) return ({ static Str _lit119 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit119; });
        if (*index == 6LL) return ({ static Str _lit120 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit120; });
        if (*index == 7LL) return ({ static Str _lit121 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit121; });
        if (*index == 8LL) return ({ static Str _lit122 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit122; });
        if (*index == 9LL) return ({ static Str _lit123 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit123; });
        if (*index == 10LL) return ({ static Str _lit124 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit124; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit125 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit125; });
        if (*index == 1LL) return ({ static Str _lit126 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit126; });
        if (*index == 2LL) return ({ static Str _lit127 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit127; });
        if (*index == 3LL) return ({ static Str _lit128 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit128; });
        if (*index == 4LL) return ({ static Str _lit129 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit129; });
        if (*index == 5LL) return ({ static Str _lit130 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit130; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit131 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit131; });
        if (*index == 1LL) return ({ static Str _lit132 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit132; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit133 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit133; });
        if (*index == 1LL) return ({ static Str _lit134 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit134; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit135 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit135; });
        if (*index == 1LL) return ({ static Str _lit136 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit136; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit137 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit137; });
        if (*index == 1LL) return ({ static Str _lit138 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit138; });
        if (*index == 2LL) return ({ static Str _lit139 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit139; });
        if (*index == 3LL) return ({ static Str _lit140 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit140; });
        if (*index == 4LL) return ({ static Str _lit141 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit141; });
        if (*index == 5LL) return ({ static Str _lit142 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit142; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit143 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit143; });
        if (*index == 1LL) return ({ static Str _lit144 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit144; });
        if (*index == 2LL) return ({ static Str _lit145 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit145; });
        if (*index == 3LL) return ({ static Str _lit146 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit146; });
        if (*index == 4LL) return ({ static Str _lit147 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit147; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit148 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit148; });
        if (*index == 1LL) return ({ static Str _lit149 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit149; });
        if (*index == 2LL) return ({ static Str _lit150 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit150; });
        if (*index == 3LL) return ({ static Str _lit151 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit151; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit152 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit152; });
        if (*index == 1LL) return ({ static Str _lit153 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit153; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit154 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit154; });
        if (*index == 1LL) return ({ static Str _lit155 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit155; });
        if (*index == 2LL) return ({ static Str _lit156 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit156; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit157 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit157; });
        if (*index == 1LL) return ({ static Str _lit158 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit158; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit159 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit159; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit160 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit160; });
        if (*index == 1LL) return ({ static Str _lit161 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit161; });
        if (*index == 2LL) return ({ static Str _lit162 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit162; });
        if (*index == 3LL) return ({ static Str _lit163 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit163; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit164 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit164; });
        if (*index == 1LL) return ({ static Str _lit165 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit165; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit166 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit166; });
        if (*index == 1LL) return ({ static Str _lit167 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit167; });
        if (*index == 2LL) return ({ static Str _lit168 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit168; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit169 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit169; });
        if (*index == 1LL) return ({ static Str _lit170 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit170; });
        if (*index == 2LL) return ({ static Str _lit171 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit171; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit172 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit172; });
        if (*index == 1LL) return ({ static Str _lit173 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit173; });
        if (*index == 2LL) return ({ static Str _lit174 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit174; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit175 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit175; });
        if (*index == 1LL) return ({ static Str _lit176 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit176; });
        if (*index == 2LL) return ({ static Str _lit177 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit177; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit178 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit178; });
        if (*index == 1LL) return ({ static Str _lit179 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit179; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit180 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit180; });
        if (*index == 1LL) return ({ static Str _lit181 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit181; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit182 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit182; });
        if (*index == 1LL) return ({ static Str _lit183 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit183; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit184 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit184; });
        if (*index == 1LL) return ({ static Str _lit185 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit185; });
        if (*index == 2LL) return ({ static Str _lit186 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit186; });
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
        if (*index == 0LL) return ({ static Str _lit187 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit187; });
        if (*index == 1LL) return ({ static Str _lit188 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit188; });
        if (*index == 2LL) return ({ static Str _lit189 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit189; });
        if (*index == 3LL) return ({ static Str _lit190 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit190; });
        if (*index == 4LL) return ({ static Str _lit191 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit191; });
        if (*index == 5LL) return ({ static Str _lit192 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit192; });
        if (*index == 6LL) return ({ static Str _lit193 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit193; });
        if (*index == 7LL) return ({ static Str _lit194 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit194; });
        if (*index == 8LL) return ({ static Str _lit195 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit195; });
        if (*index == 9LL) return ({ static Str _lit196 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit196; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit197 = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit197; });
        if (*index == 1LL) return ({ static Str _lit198 = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit198; });
        if (*index == 2LL) return ({ static Str _lit199 = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit199; });
        if (*index == 3LL) return ({ static Str _lit200 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit200; });
        if (*index == 4LL) return ({ static Str _lit201 = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit201; });
        if (*index == 5LL) return ({ static Str _lit202 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit202; });
        if (*index == 6LL) return ({ static Str _lit203 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit203; });
        if (*index == 7LL) return ({ static Str _lit204 = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit204; });
        if (*index == 8LL) return ({ static Str _lit205 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit205; });
        if (*index == 9LL) return ({ static Str _lit206 = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit206; });
        if (*index == 10LL) return ({ static Str _lit207 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit207; });
        if (*index == 11LL) return ({ static Str _lit208 = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit208; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit209 = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit209; });
        if (*index == 1LL) return ({ static Str _lit210 = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit210; });
        if (*index == 2LL) return ({ static Str _lit211 = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit211; });
        if (*index == 3LL) return ({ static Str _lit212 = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit212; });
        if (*index == 4LL) return ({ static Str _lit213 = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit213; });
        if (*index == 5LL) return ({ static Str _lit214 = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit214; });
        if (*index == 6LL) return ({ static Str _lit215 = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit215; });
        if (*index == 7LL) return ({ static Str _lit216 = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit216; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit217 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit217; });
        if (*index == 1LL) return ({ static Str _lit218 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit218; });
        if (*index == 2LL) return ({ static Str _lit219 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit219; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit220 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit220; });
        if (*index == 1LL) return ({ static Str _lit221 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit221; });
        if (*index == 2LL) return ({ static Str _lit222 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit222; });
        if (*index == 3LL) return ({ static Str _lit223 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit223; });
        if (*index == 4LL) return ({ static Str _lit224 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit224; });
        if (*index == 5LL) return ({ static Str _lit225 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit225; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit226 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit226; });
        if (*index == 1LL) return ({ static Str _lit227 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit227; });
        if (*index == 2LL) return ({ static Str _lit228 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit228; });
        if (*index == 3LL) return ({ static Str _lit229 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit229; });
        if (*index == 4LL) return ({ static Str _lit230 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit230; });
        if (*index == 5LL) return ({ static Str _lit231 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit231; });
        if (*index == 6LL) return ({ static Str _lit232 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit232; });
        if (*index == 7LL) return ({ static Str _lit233 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit233; });
        if (*index == 8LL) return ({ static Str _lit234 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit234; });
        if (*index == 9LL) return ({ static Str _lit235 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit235; });
        if (*index == 10LL) return ({ static Str _lit236 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit236; });
        if (*index == 11LL) return ({ static Str _lit237 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit237; });
        if (*index == 12LL) return ({ static Str _lit238 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit238; });
        if (*index == 13LL) return ({ static Str _lit239 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit239; });
        if (*index == 14LL) return ({ static Str _lit240 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit240; });
        if (*index == 15LL) return ({ static Str _lit241 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit241; });
        if (*index == 16LL) return ({ static Str _lit242 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit242; });
        if (*index == 17LL) return ({ static Str _lit243 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit243; });
        if (*index == 18LL) return ({ static Str _lit244 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit244; });
        if (*index == 19LL) return ({ static Str _lit245 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit245; });
        if (*index == 20LL) return ({ static Str _lit246 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit246; });
        if (*index == 21LL) return ({ static Str _lit247 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit247; });
        if (*index == 22LL) return ({ static Str _lit248 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit248; });
        if (*index == 23LL) return ({ static Str _lit249 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit249; });
        if (*index == 24LL) return ({ static Str _lit250 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit250; });
        if (*index == 25LL) return ({ static Str _lit251 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit251; });
        if (*index == 26LL) return ({ static Str _lit252 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit252; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit253 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit253; });
        if (*index == 1LL) return ({ static Str _lit254 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit254; });
        if (*index == 2LL) return ({ static Str _lit255 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit255; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit256 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit256; });
        if (*index == 1LL) return ({ static Str _lit257 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit257; });
        if (*index == 2LL) return ({ static Str _lit258 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit258; });
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
        if (*index == 0LL) return ({ static Str _lit259 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit259; });
        if (*index == 1LL) return ({ static Str _lit260 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit260; });
        if (*index == 2LL) return ({ static Str _lit261 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit261; });
        if (*index == 3LL) return ({ static Str _lit262 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit262; });
        if (*index == 4LL) return ({ static Str _lit263 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit263; });
        if (*index == 5LL) return ({ static Str _lit264 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit264; });
        if (*index == 6LL) return ({ static Str _lit265 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit265; });
        if (*index == 7LL) return ({ static Str _lit266 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit266; });
        if (*index == 8LL) return ({ static Str _lit267 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit267; });
        if (*index == 9LL) return ({ static Str _lit268 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit268; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit269 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit269; });
        if (*index == 1LL) return ({ static Str _lit270 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit270; });
        if (*index == 2LL) return ({ static Str _lit271 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit271; });
        if (*index == 3LL) return ({ static Str _lit272 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit272; });
        if (*index == 4LL) return ({ static Str _lit273 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit273; });
        if (*index == 5LL) return ({ static Str _lit274 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit274; });
        if (*index == 6LL) return ({ static Str _lit275 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit275; });
        if (*index == 7LL) return ({ static Str _lit276 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit276; });
        if (*index == 8LL) return ({ static Str _lit277 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit277; });
        if (*index == 9LL) return ({ static Str _lit278 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit278; });
        if (*index == 10LL) return ({ static Str _lit279 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit279; });
        if (*index == 11LL) return ({ static Str _lit280 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit280; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit281 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit281; });
        if (*index == 1LL) return ({ static Str _lit282 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit282; });
        if (*index == 2LL) return ({ static Str _lit283 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit283; });
        if (*index == 3LL) return ({ static Str _lit284 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit284; });
        if (*index == 4LL) return ({ static Str _lit285 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit285; });
        if (*index == 5LL) return ({ static Str _lit286 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit286; });
        if (*index == 6LL) return ({ static Str _lit287 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit287; });
        if (*index == 7LL) return ({ static Str _lit288 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit288; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit289 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit289; });
        if (*index == 1LL) return ({ static Str _lit290 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit290; });
        if (*index == 2LL) return ({ static Str _lit291 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit291; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit292 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit292; });
        if (*index == 1LL) return ({ static Str _lit293 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit293; });
        if (*index == 2LL) return ({ static Str _lit294 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit294; });
        if (*index == 3LL) return ({ static Str _lit295 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit295; });
        if (*index == 4LL) return ({ static Str _lit296 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit296; });
        if (*index == 5LL) return ({ static Str _lit297 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit297; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit298 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit298; });
        if (*index == 1LL) return ({ static Str _lit299 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit299; });
        if (*index == 2LL) return ({ static Str _lit300 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit300; });
        if (*index == 3LL) return ({ static Str _lit301 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit301; });
        if (*index == 4LL) return ({ static Str _lit302 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit302; });
        if (*index == 5LL) return ({ static Str _lit303 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit303; });
        if (*index == 6LL) return ({ static Str _lit304 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit304; });
        if (*index == 7LL) return ({ static Str _lit305 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit305; });
        if (*index == 8LL) return ({ static Str _lit306 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit306; });
        if (*index == 9LL) return ({ static Str _lit307 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit307; });
        if (*index == 10LL) return ({ static Str _lit308 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit308; });
        if (*index == 11LL) return ({ static Str _lit309 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit309; });
        if (*index == 12LL) return ({ static Str _lit310 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit310; });
        if (*index == 13LL) return ({ static Str _lit311 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit311; });
        if (*index == 14LL) return ({ static Str _lit312 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit312; });
        if (*index == 15LL) return ({ static Str _lit313 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit313; });
        if (*index == 16LL) return ({ static Str _lit314 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit314; });
        if (*index == 17LL) return ({ static Str _lit315 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit315; });
        if (*index == 18LL) return ({ static Str _lit316 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit316; });
        if (*index == 19LL) return ({ static Str _lit317 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit317; });
        if (*index == 20LL) return ({ static Str _lit318 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit318; });
        if (*index == 21LL) return ({ static Str _lit319 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit319; });
        if (*index == 22LL) return ({ static Str _lit320 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit320; });
        if (*index == 23LL) return ({ static Str _lit321 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit321; });
        if (*index == 24LL) return ({ static Str _lit322 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit322; });
        if (*index == 25LL) return ({ static Str _lit323 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit323; });
        if (*index == 26LL) return ({ static Str _lit324 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit324; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit325 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit325; });
        if (*index == 1LL) return ({ static Str _lit326 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit326; });
        if (*index == 2LL) return ({ static Str _lit327 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit327; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit328 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit328; });
        if (*index == 1LL) return ({ static Str _lit329 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit329; });
        if (*index == 2LL) return ({ static Str _lit330 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit330; });
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
        if (*index == 0LL) return ({ static Str _lit331 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit331; });
        if (*index == 1LL) return ({ static Str _lit332 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit332; });
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
        if (*index == 0LL) return ({ static Str _lit333 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit333; });
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
