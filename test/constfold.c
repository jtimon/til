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
    U32 hoisted__U32_124 = 0;
    (void)hoisted__U32_124;
    U64 hoisted__U64_125 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_124); });
    (void)hoisted__U64_125;
    return hoisted__U64_125;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_140 = U32_to_i64(val);
    (void)hoisted__I64_140;
    Str *hoisted__Str_141 = I64_to_str(hoisted__I64_140);
    (void)hoisted__Str_141;
    return hoisted__Str_141;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_142 = 1;
    (void)hoisted__U32_142;
    U32 hoisted__U32_143 = U32_add(DEREF(self), hoisted__U32_142);
    (void)hoisted__U32_143;
    *self = hoisted__U32_143;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_144 = 1;
    (void)hoisted__U32_144;
    U32 hoisted__U32_145 = U32_sub(DEREF(self), hoisted__U32_144);
    (void)hoisted__U32_145;
    *self = hoisted__U32_145;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_154 = 4;
    (void)hoisted__U32_154;
    return hoisted__U32_154;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_239 = 0;
    (void)hoisted__U32_239;
    U64 hoisted__U64_240 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_239); });
    (void)hoisted__U64_240;
    return hoisted__U64_240;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_243 = U32_cmp(a, b);
    (void)hoisted__I64_243;
    I64 hoisted__I64_244 = -1;
    (void)hoisted__I64_244;
    Bool hoisted__Bool_245 = I64_eq(hoisted__I64_243, hoisted__I64_244);
    (void)hoisted__Bool_245;
    return hoisted__Bool_245;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_246 = U32_cmp(a, b);
    (void)hoisted__I64_246;
    I64 hoisted__I64_247 = 1;
    (void)hoisted__I64_247;
    Bool hoisted__Bool_248 = I64_eq(hoisted__I64_246, hoisted__I64_247);
    (void)hoisted__Bool_248;
    return hoisted__Bool_248;
}

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_249 = U32_eq(a, b);
    (void)hoisted__Bool_249;
    Bool hoisted__Bool_250 = not(hoisted__Bool_249);
    (void)hoisted__Bool_250;
    return hoisted__Bool_250;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_251 = U32_gt(a, b);
    (void)hoisted__Bool_251;
    Bool hoisted__Bool_252 = not(hoisted__Bool_251);
    (void)hoisted__Bool_252;
    return hoisted__Bool_252;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_253 = U32_lt(a, b);
    (void)hoisted__Bool_253;
    Bool hoisted__Bool_254 = not(hoisted__Bool_253);
    (void)hoisted__Bool_254;
    return hoisted__Bool_254;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_277 = 4;
    (void)hoisted__U32_277;
    return hoisted__U32_277;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_419 = 0;
    (void)hoisted__U32_419;
    U64 hoisted__U64_420 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_419); });
    (void)hoisted__U64_420;
    return hoisted__U64_420;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_457 = 1;
    (void)hoisted__U32_457;
    return hoisted__U32_457;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_458 = 0;
    (void)hoisted__U32_458;
    U64 hoisted__U64_459 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_458); });
    (void)hoisted__U64_459;
    return hoisted__U64_459;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_488 = 1;
    (void)hoisted__U32_488;
    return hoisted__U32_488;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_573 = 0;
    (void)hoisted__U32_573;
    U64 hoisted__U64_574 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_573); });
    (void)hoisted__U64_574;
    return hoisted__U64_574;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_727 = parts;
        (void)_fc_Array__Str_727;
        (void)_fc_Array__Str_727;
        U32 _fi_USize_727 = 0;
        (void)_fi_USize_727;
        I64 _forin_err_kind_727 = 0;
        (void)_forin_err_kind_727;
        OutOfBounds *_forin_OutOfBounds_727 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_727->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_727;
        while (1) {
            U32 hoisted__U32_737 = Array__Str_len(_fc_Array__Str_727);
            (void)hoisted__U32_737;
            Bool _wcond_Bool_728 = U32_lt(_fi_USize_727, hoisted__U32_737);
            (void)_wcond_Bool_728;
            if (_wcond_Bool_728) {
            } else {
                break;
            }
            static Str hoisted__Str_738 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
            (void)hoisted__Str_738;
            Str *s = Array__Str_get(_fc_Array__Str_727, &_fi_USize_727, &_forin_err_kind_727, _forin_OutOfBounds_727, &hoisted__Str_738);
            I64 hoisted__I64_739 = 0;
            (void)hoisted__I64_739;
            Bool hoisted__Bool_740 = I64_eq(_forin_err_kind_727, hoisted__I64_739);
            (void)hoisted__Bool_740;
            Bool hoisted__Bool_741 = not(hoisted__Bool_740);
            (void)hoisted__Bool_741;
            if (hoisted__Bool_741) {
                U32 hoisted__U32_729 = 2;
                (void)hoisted__U32_729;
                Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_729);
                (void)_va_Array_16;
                I64 _va_Array_16_ek = 0;
                (void)_va_Array_16_ek;
                OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
                _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_16_eo;
                U32 hoisted__U32_730 = 0;
                (void)hoisted__U32_730;
                static Str hoisted__Str_731 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_731;
                static Str hoisted__Str_732 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_732;
                Array__Str_set(_va_Array_16, hoisted__U32_730, &hoisted__Str_731, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_732);
                Str_delete(&hoisted__Str_732, (Bool){0});
                U32 hoisted__U32_733 = 1;
                (void)hoisted__U32_733;
                static Str hoisted__Str_734 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_734;
                static Str hoisted__Str_735 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_735;
                Array__Str_set(_va_Array_16, hoisted__U32_733, &hoisted__Str_734, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_735);
                OutOfBounds_delete(_va_Array_16_eo, 1);
                Str_delete(&hoisted__Str_735, (Bool){0});
                static Str hoisted__Str_736 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_736;
                panic(_va_Array_16, &hoisted__Str_736);
                Str_delete(&hoisted__Str_736, (Bool){0});
            }
            U32 hoisted__U32_742 = 1;
            (void)hoisted__U32_742;
            U32 hoisted__U32_743 = U32_add(_fi_USize_727, hoisted__U32_742);
            (void)hoisted__U32_743;
            _fi_USize_727 = hoisted__U32_743;
            U32 hoisted__U32_744 = Str_len(s);
            (void)hoisted__U32_744;
            Str_delete(&hoisted__Str_738, (Bool){0});
            U32 hoisted__U32_745 = U32_add(total, hoisted__U32_744);
            (void)hoisted__U32_745;
            total = hoisted__U32_745;
        }
        OutOfBounds_delete(_forin_OutOfBounds_727, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_746 = parts;
        (void)_fc_Array__Str_746;
        (void)_fc_Array__Str_746;
        U32 _fi_USize_746 = 0;
        (void)_fi_USize_746;
        I64 _forin_err_kind_746 = 0;
        (void)_forin_err_kind_746;
        OutOfBounds *_forin_OutOfBounds_746 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_746->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_746;
        while (1) {
            U32 hoisted__U32_756 = Array__Str_len(_fc_Array__Str_746);
            (void)hoisted__U32_756;
            Bool _wcond_Bool_747 = U32_lt(_fi_USize_746, hoisted__U32_756);
            (void)_wcond_Bool_747;
            if (_wcond_Bool_747) {
            } else {
                break;
            }
            static Str hoisted__Str_757 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
            (void)hoisted__Str_757;
            Str *s = Array__Str_get(_fc_Array__Str_746, &_fi_USize_746, &_forin_err_kind_746, _forin_OutOfBounds_746, &hoisted__Str_757);
            I64 hoisted__I64_758 = 0;
            (void)hoisted__I64_758;
            Bool hoisted__Bool_759 = I64_eq(_forin_err_kind_746, hoisted__I64_758);
            (void)hoisted__Bool_759;
            Bool hoisted__Bool_760 = not(hoisted__Bool_759);
            (void)hoisted__Bool_760;
            if (hoisted__Bool_760) {
                U32 hoisted__U32_748 = 2;
                (void)hoisted__U32_748;
                Array__Str *_va_Array_17 = Array__Str_new(hoisted__U32_748);
                (void)_va_Array_17;
                I64 _va_Array_17_ek = 0;
                (void)_va_Array_17_ek;
                OutOfBounds *_va_Array_17_eo = malloc(sizeof(OutOfBounds));
                _va_Array_17_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_17_eo;
                U32 hoisted__U32_749 = 0;
                (void)hoisted__U32_749;
                static Str hoisted__Str_750 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_750;
                static Str hoisted__Str_751 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_751;
                Array__Str_set(_va_Array_17, hoisted__U32_749, &hoisted__Str_750, &_va_Array_17_ek, _va_Array_17_eo, &hoisted__Str_751);
                Str_delete(&hoisted__Str_751, (Bool){0});
                U32 hoisted__U32_752 = 1;
                (void)hoisted__U32_752;
                static Str hoisted__Str_753 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_753;
                static Str hoisted__Str_754 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_754;
                Array__Str_set(_va_Array_17, hoisted__U32_752, &hoisted__Str_753, &_va_Array_17_ek, _va_Array_17_eo, &hoisted__Str_754);
                OutOfBounds_delete(_va_Array_17_eo, 1);
                Str_delete(&hoisted__Str_754, (Bool){0});
                static Str hoisted__Str_755 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_755;
                panic(_va_Array_17, &hoisted__Str_755);
                Str_delete(&hoisted__Str_755, (Bool){0});
            }
            U32 hoisted__U32_761 = 1;
            (void)hoisted__U32_761;
            U32 hoisted__U32_762 = U32_add(_fi_USize_746, hoisted__U32_761);
            (void)hoisted__U32_762;
            _fi_USize_746 = hoisted__U32_762;
            Str_push_str(out, s);
            Str_delete(&hoisted__Str_757, (Bool){0});
        }
        OutOfBounds_delete(_forin_OutOfBounds_746, 1);
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_768 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_768;
    if (hoisted__Bool_768) {
        U32 hoisted__U32_763 = 1;
        (void)hoisted__U32_763;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_763);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_764 = 0;
        (void)hoisted__U32_764;
        static Str hoisted__Str_765 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_765;
        static Str hoisted__Str_766 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_766;
        Array__Str_set(_va_Array_18, hoisted__U32_764, &hoisted__Str_765, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_766);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_766, (Bool){0});
        static Str hoisted__Str_767 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_767;
        panic(_va_Array_18, &hoisted__Str_767);
        Str_delete(&hoisted__Str_767, (Bool){0});
    }
    void *hoisted__v_769 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_769;
    (void)hoisted__v_769;
    return hoisted__v_769;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_779 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_779;
    if (hoisted__Bool_779) {
        min_len = b->count;
    }
    {
        U32 _re_U32_771 = U32_clone(&min_len);
        (void)_re_U32_771;
        U32 _rc_U32_771 = 0;
        (void)_rc_U32_771;
        Bool hoisted__Bool_778 = U32_lte(_rc_U32_771, _re_U32_771);
        (void)hoisted__Bool_778;
        if (hoisted__Bool_778) {
            while (1) {
                Bool _wcond_Bool_772 = U32_lt(_rc_U32_771, _re_U32_771);
                (void)_wcond_Bool_772;
                if (_wcond_Bool_772) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_771);
                U32_inc(&_rc_U32_771);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_773 = 0;
                (void)hoisted__I64_773;
                Bool hoisted__Bool_774 = I64_neq(c, hoisted__I64_773);
                (void)hoisted__Bool_774;
                if (hoisted__Bool_774) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_775 = U32_gt(_rc_U32_771, _re_U32_771);
                (void)_wcond_Bool_775;
                if (_wcond_Bool_775) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_771);
                U32_dec(&_rc_U32_771);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_776 = 0;
                (void)hoisted__I64_776;
                Bool hoisted__Bool_777 = I64_neq(c, hoisted__I64_776);
                (void)hoisted__Bool_777;
                if (hoisted__Bool_777) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_780 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_780;
    return hoisted__I64_780;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_781 = 1;
    (void)hoisted__U32_781;
    U32 hoisted__U64_782 = U32_add(n, hoisted__U32_781);
    (void)hoisted__U64_782;
    void * buf = malloc(hoisted__U64_782);
    I32 hoisted__I32_783 = 0;
    (void)hoisted__I32_783;
    U64 hoisted__U64_784 = 1ULL;
    (void)hoisted__U64_784;
    memset(buf, hoisted__I32_783, hoisted__U64_784);
    I64 hoisted__I64_785 = 0;
    (void)hoisted__I64_785;
    Str *hoisted__Str_786 = malloc(sizeof(Str));
    hoisted__Str_786->c_str = buf;
    hoisted__Str_786->count = hoisted__I64_785;
    hoisted__Str_786->cap = n;
    (void)hoisted__Str_786;
    return hoisted__Str_786;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_799 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_799;
    if (hoisted__Bool_799) {
        U32 hoisted__U32_789 = 1;
        (void)hoisted__U32_789;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_789);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_790 = 0;
        (void)hoisted__U32_790;
        static Str hoisted__Str_791 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_791;
        static Str hoisted__Str_792 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_792;
        Array__Str_set(_va_Array_19, hoisted__U32_790, &hoisted__Str_791, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_792);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_792, (Bool){0});
        static Str hoisted__Str_793 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_793;
        panic(_va_Array_19, &hoisted__Str_793);
        Str_delete(&hoisted__Str_793, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_800 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_800;
    if (hoisted__Bool_800) {
        U32 hoisted__U32_794 = 1;
        (void)hoisted__U32_794;
        Array__Str *_va_Array_20 = Array__Str_new(hoisted__U32_794);
        (void)_va_Array_20;
        I64 _va_Array_20_ek = 0;
        (void)_va_Array_20_ek;
        OutOfBounds *_va_Array_20_eo = malloc(sizeof(OutOfBounds));
        _va_Array_20_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_20_eo;
        U32 hoisted__U32_795 = 0;
        (void)hoisted__U32_795;
        static Str hoisted__Str_796 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_796;
        static Str hoisted__Str_797 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_797;
        Array__Str_set(_va_Array_20, hoisted__U32_795, &hoisted__Str_796, &_va_Array_20_ek, _va_Array_20_eo, &hoisted__Str_797);
        OutOfBounds_delete(_va_Array_20_eo, 1);
        Str_delete(&hoisted__Str_797, (Bool){0});
        static Str hoisted__Str_798 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_798;
        panic(_va_Array_20, &hoisted__Str_798);
        Str_delete(&hoisted__Str_798, (Bool){0});
    }
    void *hoisted__v_801 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_801;
    (void)hoisted__v_801;
    memcpy(hoisted__v_801, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_802 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_802;
    (void)hoisted__v_802;
    I32 hoisted__I32_803 = 0;
    (void)hoisted__I32_803;
    U64 hoisted__U64_804 = 1ULL;
    (void)hoisted__U64_804;
    memset(hoisted__v_802, hoisted__I32_803, hoisted__U64_804);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_805 = 1;
    (void)hoisted__U32_805;
    U32 hoisted__U64_806 = U32_add(val->count, hoisted__U32_805);
    (void)hoisted__U64_806;
    void * new_data = malloc(hoisted__U64_806);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_807 = ptr_add(new_data, val->count);
    (void)hoisted__v_807;
    (void)hoisted__v_807;
    I32 hoisted__I32_808 = 0;
    (void)hoisted__I32_808;
    U64 hoisted__U64_809 = 1ULL;
    (void)hoisted__U64_809;
    memset(hoisted__v_807, hoisted__I32_808, hoisted__U64_809);
    Str *hoisted__Str_810 = malloc(sizeof(Str));
    hoisted__Str_810->c_str = new_data;
    hoisted__Str_810->count = val->count;
    hoisted__Str_810->cap = val->count;
    (void)hoisted__Str_810;
    return hoisted__Str_810;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_811 = Str_clone(self);
    (void)hoisted__Str_811;
    return hoisted__Str_811;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_812 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_812;
    if (hoisted__Bool_812) {
        free(self->c_str);
    }
    Bool hoisted__Bool_813 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_813;
    Bool hoisted__Bool_814 = and(call_free, hoisted__Bool_813);
    (void)hoisted__Bool_814;
    if (hoisted__Bool_814) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1009 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_1009;
    return hoisted__U64_1009;
}

U32 Str_size(void) {
    U32 hoisted__U32_1194 = 16;
    (void)hoisted__U32_1194;
    return hoisted__U32_1194;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1195 = Str_cmp(a, b);
    (void)hoisted__I64_1195;
    I64 hoisted__I64_1196 = 0;
    (void)hoisted__I64_1196;
    Bool hoisted__Bool_1197 = I64_eq(hoisted__I64_1195, hoisted__I64_1196);
    (void)hoisted__Bool_1197;
    return hoisted__Bool_1197;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1206 = Str_eq(a, b);
    (void)hoisted__Bool_1206;
    Bool hoisted__Bool_1207 = not(hoisted__Bool_1206);
    (void)hoisted__Bool_1207;
    return hoisted__Bool_1207;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1311 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1311->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1311;
    return hoisted__OutOfBounds_1311;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1312 = 0;
    (void)hoisted__Bool_1312;
    Str_delete(&self->msg, hoisted__Bool_1312);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1313 = 0;
    (void)hoisted__U32_1313;
    U64 hoisted__U64_1314 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1313); });
    (void)hoisted__U64_1314;
    return hoisted__U64_1314;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1333 = 16;
    (void)hoisted__U32_1333;
    return hoisted__U32_1333;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1357 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1357;
    U32 hoisted__U32_1358 = 16;
    (void)hoisted__U32_1358;
    Type *hoisted__Type_1359 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1359;
    U64 hoisted__U64_1360 = (U64)(cap);
    (void)hoisted__U64_1360;
    Type_delete(hoisted__Type_1357, 1);
    U64 hoisted__U64_1361 = (U64)(hoisted__U32_1358);
    (void)hoisted__U64_1361;
    Type_delete(hoisted__Type_1359, 1);
    void * hoisted__v_1362 = calloc(hoisted__U64_1360, hoisted__U64_1361);
    (void)hoisted__v_1362;
    Array__Str *hoisted__Array__Str_1363 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1363->data = hoisted__v_1362;
    hoisted__Array__Str_1363->cap = cap;
    (void)hoisted__Array__Str_1363;
    return hoisted__Array__Str_1363;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1391 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1391;
    if (hoisted__Bool_1391) {
        U32 hoisted__U32_1364 = 6;
        (void)hoisted__U32_1364;
        Array__Str *_va_Array_32 = Array__Str_new(hoisted__U32_1364);
        (void)_va_Array_32;
        I64 _va_Array_32_ek = 0;
        (void)_va_Array_32_ek;
        OutOfBounds *_va_Array_32_eo = malloc(sizeof(OutOfBounds));
        _va_Array_32_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_32_eo;
        U32 hoisted__U32_1365 = 0;
        (void)hoisted__U32_1365;
        Str *hoisted__Str_1366 = Str_clone(loc);
        (void)hoisted__Str_1366;
        static Str hoisted__Str_1367 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1367;
        Array__Str_set(_va_Array_32, hoisted__U32_1365, hoisted__Str_1366, &_va_Array_32_ek, _va_Array_32_eo, &hoisted__Str_1367);
        Str_delete(&hoisted__Str_1367, (Bool){0});
        U32 hoisted__U32_1368 = 1;
        (void)hoisted__U32_1368;
        static Str hoisted__Str_1369 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1369;
        static Str hoisted__Str_1370 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1370;
        Array__Str_set(_va_Array_32, hoisted__U32_1368, &hoisted__Str_1369, &_va_Array_32_ek, _va_Array_32_eo, &hoisted__Str_1370);
        Str_delete(&hoisted__Str_1370, (Bool){0});
        U32 hoisted__U32_1371 = 2;
        (void)hoisted__U32_1371;
        Str *hoisted__Str_1372 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1372;
        static Str hoisted__Str_1373 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1373;
        Array__Str_set(_va_Array_32, hoisted__U32_1371, hoisted__Str_1372, &_va_Array_32_ek, _va_Array_32_eo, &hoisted__Str_1373);
        Str_delete(&hoisted__Str_1373, (Bool){0});
        U32 hoisted__U32_1374 = 3;
        (void)hoisted__U32_1374;
        static Str hoisted__Str_1375 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1375;
        static Str hoisted__Str_1376 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1376;
        Array__Str_set(_va_Array_32, hoisted__U32_1374, &hoisted__Str_1375, &_va_Array_32_ek, _va_Array_32_eo, &hoisted__Str_1376);
        Str_delete(&hoisted__Str_1376, (Bool){0});
        U32 hoisted__U32_1377 = 4;
        (void)hoisted__U32_1377;
        Str *hoisted__Str_1378 = U32_to_str(self->cap);
        (void)hoisted__Str_1378;
        static Str hoisted__Str_1379 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1379;
        Array__Str_set(_va_Array_32, hoisted__U32_1377, hoisted__Str_1378, &_va_Array_32_ek, _va_Array_32_eo, &hoisted__Str_1379);
        Str_delete(&hoisted__Str_1379, (Bool){0});
        U32 hoisted__U32_1380 = 5;
        (void)hoisted__U32_1380;
        static Str hoisted__Str_1381 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1381;
        static Str hoisted__Str_1382 = (Str){.c_str = (void *)"./src/core/str.til:28:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1382;
        Array__Str_set(_va_Array_32, hoisted__U32_1380, &hoisted__Str_1381, &_va_Array_32_ek, _va_Array_32_eo, &hoisted__Str_1382);
        OutOfBounds_delete(_va_Array_32_eo, 1);
        Str_delete(&hoisted__Str_1382, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1383 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_32); hoisted__OutOfBounds_1383->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1383;
        U32 hoisted__U32_1384 = 16;
        (void)hoisted__U32_1384;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1383, hoisted__U32_1384);
        OutOfBounds_delete(hoisted__OutOfBounds_1383, 1);
        I64 hoisted__I64_1385 = 3;
        (void)hoisted__I64_1385;
        *_err_kind = hoisted__I64_1385;
    }
    I64 hoisted__I64_1392 = 0;
    (void)hoisted__I64_1392;
    Bool hoisted__Bool_1393 = I64_eq(DEREF(_err_kind), hoisted__I64_1392);
    (void)hoisted__Bool_1393;
    if (hoisted__Bool_1393) {
        U32 hoisted__U32_1386 = 16;
        (void)hoisted__U32_1386;
        U32 hoisted__U32_1387 = U32_mul(DEREF(i), hoisted__U32_1386);
        (void)hoisted__U32_1387;
        Type *hoisted__Type_1388 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1388;
        U64 hoisted__U64_1389 = (U64)(hoisted__U32_1387);
        (void)hoisted__U64_1389;
        Type_delete(hoisted__Type_1388, 1);
        void *hoisted__v_1390 = ptr_add(self->data, hoisted__U64_1389);
        (void)hoisted__v_1390;
        (void)hoisted__v_1390;
        { Str * _ret_val = hoisted__v_1390;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1434 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1434;
    if (hoisted__Bool_1434) {
        U32 hoisted__U32_1394 = 6;
        (void)hoisted__U32_1394;
        Array__Str *_va_Array_33 = Array__Str_new(hoisted__U32_1394);
        (void)_va_Array_33;
        I64 _va_Array_33_ek = 0;
        (void)_va_Array_33_ek;
        OutOfBounds *_va_Array_33_eo = malloc(sizeof(OutOfBounds));
        _va_Array_33_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_33_eo;
        U32 hoisted__U32_1395 = 0;
        (void)hoisted__U32_1395;
        Str *hoisted__Str_1396 = Str_clone(loc);
        (void)hoisted__Str_1396;
        static Str hoisted__Str_1397 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1397;
        Array__Str_set(_va_Array_33, hoisted__U32_1395, hoisted__Str_1396, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1397);
        Str_delete(&hoisted__Str_1397, (Bool){0});
        U32 hoisted__U32_1398 = 1;
        (void)hoisted__U32_1398;
        static Str hoisted__Str_1399 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1399;
        static Str hoisted__Str_1400 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1400;
        Array__Str_set(_va_Array_33, hoisted__U32_1398, &hoisted__Str_1399, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1400);
        Str_delete(&hoisted__Str_1400, (Bool){0});
        U32 hoisted__U32_1401 = 2;
        (void)hoisted__U32_1401;
        Str *hoisted__Str_1402 = U32_to_str(i);
        (void)hoisted__Str_1402;
        static Str hoisted__Str_1403 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1403;
        Array__Str_set(_va_Array_33, hoisted__U32_1401, hoisted__Str_1402, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1403);
        Str_delete(&hoisted__Str_1403, (Bool){0});
        U32 hoisted__U32_1404 = 3;
        (void)hoisted__U32_1404;
        static Str hoisted__Str_1405 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1405;
        static Str hoisted__Str_1406 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1406;
        Array__Str_set(_va_Array_33, hoisted__U32_1404, &hoisted__Str_1405, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1406);
        Str_delete(&hoisted__Str_1406, (Bool){0});
        U32 hoisted__U32_1407 = 4;
        (void)hoisted__U32_1407;
        Str *hoisted__Str_1408 = U32_to_str(self->cap);
        (void)hoisted__Str_1408;
        static Str hoisted__Str_1409 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1409;
        Array__Str_set(_va_Array_33, hoisted__U32_1407, hoisted__Str_1408, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1409);
        Str_delete(&hoisted__Str_1409, (Bool){0});
        U32 hoisted__U32_1410 = 5;
        (void)hoisted__U32_1410;
        static Str hoisted__Str_1411 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1411;
        static Str hoisted__Str_1412 = (Str){.c_str = (void *)"./src/core/str.til:39:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1412;
        Array__Str_set(_va_Array_33, hoisted__U32_1410, &hoisted__Str_1411, &_va_Array_33_ek, _va_Array_33_eo, &hoisted__Str_1412);
        OutOfBounds_delete(_va_Array_33_eo, 1);
        Str_delete(&hoisted__Str_1412, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1413 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_33); hoisted__OutOfBounds_1413->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1413;
        U32 hoisted__U32_1414 = 16;
        (void)hoisted__U32_1414;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1413, hoisted__U32_1414);
        OutOfBounds_delete(hoisted__OutOfBounds_1413, 1);
        I64 hoisted__I64_1415 = 3;
        (void)hoisted__I64_1415;
        *_err_kind = hoisted__I64_1415;
    }
    I64 hoisted__I64_1435 = 0;
    (void)hoisted__I64_1435;
    Bool hoisted__Bool_1436 = I64_eq(DEREF(_err_kind), hoisted__I64_1435);
    (void)hoisted__Bool_1436;
    if (hoisted__Bool_1436) {
        U32 hoisted__U32_1416 = 16;
        (void)hoisted__U32_1416;
        U32 hoisted__U32_1417 = U32_mul(i, hoisted__U32_1416);
        (void)hoisted__U32_1417;
        Type *hoisted__Type_1418 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1418;
        U64 hoisted__U64_1419 = (U64)(hoisted__U32_1417);
        (void)hoisted__U64_1419;
        Type_delete(hoisted__Type_1418, 1);
        Str *hoisted__Str_1420 = ptr_add(self->data, hoisted__U64_1419);
        (void)hoisted__Str_1420;
        (void)hoisted__Str_1420;
        Bool hoisted__Bool_1421 = 0;
        (void)hoisted__Bool_1421;
        Str_delete(hoisted__Str_1420, hoisted__Bool_1421);
        U32 hoisted__U32_1422 = 16;
        (void)hoisted__U32_1422;
        U32 hoisted__U32_1423 = U32_mul(i, hoisted__U32_1422);
        (void)hoisted__U32_1423;
        Type *hoisted__Type_1424 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1424;
        U64 hoisted__U64_1425 = (U64)(hoisted__U32_1423);
        (void)hoisted__U64_1425;
        Type_delete(hoisted__Type_1424, 1);
        U32 hoisted__U32_1426 = 16;
        (void)hoisted__U32_1426;
        Type *hoisted__Type_1427 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1427;
        void *hoisted__v_1428 = ptr_add(self->data, hoisted__U64_1425);
        (void)hoisted__v_1428;
        (void)hoisted__v_1428;
        U64 hoisted__U64_1429 = (U64)(hoisted__U32_1426);
        (void)hoisted__U64_1429;
        Type_delete(hoisted__Type_1427, 1);
        memcpy(hoisted__v_1428, val, hoisted__U64_1429);
        U32 hoisted__U32_1430 = 16;
        (void)hoisted__U32_1430;
        Type *hoisted__Type_1431 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1431;
        I32 hoisted__I32_1432 = 0;
        (void)hoisted__I32_1432;
        U64 hoisted__U64_1433 = (U64)(hoisted__U32_1430);
        (void)hoisted__U64_1433;
        Type_delete(hoisted__Type_1431, 1);
        if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1432, hoisted__U64_1433); };
    }
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1437 = self->cap;
        (void)_re_U32_1437;
        U32 _rc_U32_1437 = 0;
        (void)_rc_U32_1437;
        Bool hoisted__Bool_1452 = U32_lte(_rc_U32_1437, _re_U32_1437);
        (void)hoisted__Bool_1452;
        if (hoisted__Bool_1452) {
            while (1) {
                Bool _wcond_Bool_1438 = U32_lt(_rc_U32_1437, _re_U32_1437);
                (void)_wcond_Bool_1438;
                if (_wcond_Bool_1438) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1437);
                U32_inc(&_rc_U32_1437);
                U32 hoisted__U32_1439 = 16;
                (void)hoisted__U32_1439;
                U32 hoisted__U32_1440 = U32_mul(i, hoisted__U32_1439);
                (void)hoisted__U32_1440;
                Type *hoisted__Type_1441 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1441;
                U64 hoisted__U64_1442 = (U64)(hoisted__U32_1440);
                (void)hoisted__U64_1442;
                Type_delete(hoisted__Type_1441, 1);
                Str *hoisted__Str_1443 = ptr_add(self->data, hoisted__U64_1442);
                (void)hoisted__Str_1443;
                (void)hoisted__Str_1443;
                Bool hoisted__Bool_1444 = 0;
                (void)hoisted__Bool_1444;
                Str_delete(hoisted__Str_1443, hoisted__Bool_1444);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1445 = U32_gt(_rc_U32_1437, _re_U32_1437);
                (void)_wcond_Bool_1445;
                if (_wcond_Bool_1445) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1437);
                U32_dec(&_rc_U32_1437);
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
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1489 = 16;
    (void)hoisted__U32_1489;
    U32 hoisted__U32_1490 = U32_mul(self->cap, hoisted__U32_1489);
    (void)hoisted__U32_1490;
    Type *hoisted__Type_1491 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1491;
    U64 hoisted__U64_1492 = (U64)(hoisted__U32_1490);
    (void)hoisted__U64_1492;
    Type_delete(hoisted__Type_1491, 1);
    void * new_data = malloc(hoisted__U64_1492);
    {
        U32 _re_U32_1453 = self->cap;
        (void)_re_U32_1453;
        U32 _rc_U32_1453 = 0;
        (void)_rc_U32_1453;
        Bool hoisted__Bool_1488 = U32_lte(_rc_U32_1453, _re_U32_1453);
        (void)hoisted__Bool_1488;
        if (hoisted__Bool_1488) {
            while (1) {
                Bool _wcond_Bool_1454 = U32_lt(_rc_U32_1453, _re_U32_1453);
                (void)_wcond_Bool_1454;
                if (_wcond_Bool_1454) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1453);
                U32_inc(&_rc_U32_1453);
                U32 hoisted__U32_1455 = 16;
                (void)hoisted__U32_1455;
                U32 hoisted__U32_1456 = U32_mul(i, hoisted__U32_1455);
                (void)hoisted__U32_1456;
                Type *hoisted__Type_1457 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1457;
                U64 hoisted__U64_1458 = (U64)(hoisted__U32_1456);
                (void)hoisted__U64_1458;
                Type_delete(hoisted__Type_1457, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1458);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1459 = 16;
                (void)hoisted__U32_1459;
                U32 hoisted__U32_1460 = U32_mul(i, hoisted__U32_1459);
                (void)hoisted__U32_1460;
                Type *hoisted__Type_1461 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1461;
                U64 hoisted__U64_1462 = (U64)(hoisted__U32_1460);
                (void)hoisted__U64_1462;
                Type_delete(hoisted__Type_1461, 1);
                U32 hoisted__U32_1463 = 16;
                (void)hoisted__U32_1463;
                Type *hoisted__Type_1464 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1464;
                void *hoisted__v_1465 = ptr_add(new_data, hoisted__U64_1462);
                (void)hoisted__v_1465;
                (void)hoisted__v_1465;
                U64 hoisted__U64_1466 = (U64)(hoisted__U32_1463);
                (void)hoisted__U64_1466;
                Type_delete(hoisted__Type_1464, 1);
                memcpy(hoisted__v_1465, cloned, hoisted__U64_1466);
                U32 hoisted__U32_1467 = 16;
                (void)hoisted__U32_1467;
                Type *hoisted__Type_1468 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1468;
                I32 hoisted__I32_1469 = 0;
                (void)hoisted__I32_1469;
                U64 hoisted__U64_1470 = (U64)(hoisted__U32_1467);
                (void)hoisted__U64_1470;
                Type_delete(hoisted__Type_1468, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1469, hoisted__U64_1470); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1471 = U32_gt(_rc_U32_1453, _re_U32_1453);
                (void)_wcond_Bool_1471;
                if (_wcond_Bool_1471) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1453);
                U32_dec(&_rc_U32_1453);
                U32 hoisted__U32_1472 = 16;
                (void)hoisted__U32_1472;
                U32 hoisted__U32_1473 = U32_mul(i, hoisted__U32_1472);
                (void)hoisted__U32_1473;
                Type *hoisted__Type_1474 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1474;
                U64 hoisted__U64_1475 = (U64)(hoisted__U32_1473);
                (void)hoisted__U64_1475;
                Type_delete(hoisted__Type_1474, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1475);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1476 = 16;
                (void)hoisted__U32_1476;
                U32 hoisted__U32_1477 = U32_mul(i, hoisted__U32_1476);
                (void)hoisted__U32_1477;
                Type *hoisted__Type_1478 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1478;
                U64 hoisted__U64_1479 = (U64)(hoisted__U32_1477);
                (void)hoisted__U64_1479;
                Type_delete(hoisted__Type_1478, 1);
                U32 hoisted__U32_1480 = 16;
                (void)hoisted__U32_1480;
                Type *hoisted__Type_1481 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1481;
                void *hoisted__v_1482 = ptr_add(new_data, hoisted__U64_1479);
                (void)hoisted__v_1482;
                (void)hoisted__v_1482;
                U64 hoisted__U64_1483 = (U64)(hoisted__U32_1480);
                (void)hoisted__U64_1483;
                Type_delete(hoisted__Type_1481, 1);
                memcpy(hoisted__v_1482, cloned, hoisted__U64_1483);
                U32 hoisted__U32_1484 = 16;
                (void)hoisted__U32_1484;
                Type *hoisted__Type_1485 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1485;
                I32 hoisted__I32_1486 = 0;
                (void)hoisted__I32_1486;
                U64 hoisted__U64_1487 = (U64)(hoisted__U32_1484);
                (void)hoisted__U64_1487;
                Type_delete(hoisted__Type_1485, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1486, hoisted__U64_1487); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1493 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1493->data = new_data;
    hoisted__Array__Str_1493->cap = self->cap;
    (void)hoisted__Array__Str_1493;
    return hoisted__Array__Str_1493;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1494 = 16;
    (void)hoisted__U32_1494;
    return hoisted__U32_1494;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1495 = 16;
    (void)hoisted__U32_1495;
    Type *hoisted__Type_1496 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1496;
    U64 hoisted__U64_1497 = (U64)(hoisted__U32_1495);
    (void)hoisted__U64_1497;
    Type_delete(hoisted__Type_1496, 1);
    void * hoisted__v_1498 = malloc(hoisted__U64_1497);
    (void)hoisted__v_1498;
    U32 hoisted__U32_1499 = 0;
    (void)hoisted__U32_1499;
    I64 hoisted__I64_1500 = 1;
    (void)hoisted__I64_1500;
    Vec__Str *hoisted__Vec__Str_1501 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1501->data = hoisted__v_1498;
    hoisted__Vec__Str_1501->count = hoisted__U32_1499;
    hoisted__Vec__Str_1501->cap = hoisted__I64_1500;
    (void)hoisted__Vec__Str_1501;
    return hoisted__Vec__Str_1501;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1502 = self->count;
        (void)_re_U32_1502;
        U32 _rc_U32_1502 = 0;
        (void)_rc_U32_1502;
        Bool hoisted__Bool_1517 = U32_lte(_rc_U32_1502, _re_U32_1502);
        (void)hoisted__Bool_1517;
        if (hoisted__Bool_1517) {
            while (1) {
                Bool _wcond_Bool_1503 = U32_lt(_rc_U32_1502, _re_U32_1502);
                (void)_wcond_Bool_1503;
                if (_wcond_Bool_1503) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1502);
                U32_inc(&_rc_U32_1502);
                U32 hoisted__U32_1504 = 16;
                (void)hoisted__U32_1504;
                U32 hoisted__U32_1505 = U32_mul(i, hoisted__U32_1504);
                (void)hoisted__U32_1505;
                Type *hoisted__Type_1506 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1506;
                U64 hoisted__U64_1507 = (U64)(hoisted__U32_1505);
                (void)hoisted__U64_1507;
                Type_delete(hoisted__Type_1506, 1);
                Str *hoisted__Str_1508 = ptr_add(self->data, hoisted__U64_1507);
                (void)hoisted__Str_1508;
                (void)hoisted__Str_1508;
                Bool hoisted__Bool_1509 = 0;
                (void)hoisted__Bool_1509;
                Str_delete(hoisted__Str_1508, hoisted__Bool_1509);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1510 = U32_gt(_rc_U32_1502, _re_U32_1502);
                (void)_wcond_Bool_1510;
                if (_wcond_Bool_1510) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1502);
                U32_dec(&_rc_U32_1502);
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
        }
    }
    U32 hoisted__U32_1518 = 0;
    (void)hoisted__U32_1518;
    self->count = hoisted__U32_1518;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1834 = 16;
    (void)hoisted__U32_1834;
    U32 hoisted__U32_1835 = U32_mul(self->cap, hoisted__U32_1834);
    (void)hoisted__U32_1835;
    Type *hoisted__Type_1836 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1836;
    U64 hoisted__U64_1837 = (U64)(hoisted__U32_1835);
    (void)hoisted__U64_1837;
    Type_delete(hoisted__Type_1836, 1);
    void * new_data = malloc(hoisted__U64_1837);
    {
        U32 _re_U32_1798 = self->count;
        (void)_re_U32_1798;
        U32 _rc_U32_1798 = 0;
        (void)_rc_U32_1798;
        Bool hoisted__Bool_1833 = U32_lte(_rc_U32_1798, _re_U32_1798);
        (void)hoisted__Bool_1833;
        if (hoisted__Bool_1833) {
            while (1) {
                Bool _wcond_Bool_1799 = U32_lt(_rc_U32_1798, _re_U32_1798);
                (void)_wcond_Bool_1799;
                if (_wcond_Bool_1799) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1798);
                U32_inc(&_rc_U32_1798);
                U32 hoisted__U32_1800 = 16;
                (void)hoisted__U32_1800;
                U32 hoisted__U32_1801 = U32_mul(i, hoisted__U32_1800);
                (void)hoisted__U32_1801;
                Type *hoisted__Type_1802 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1802;
                U64 hoisted__U64_1803 = (U64)(hoisted__U32_1801);
                (void)hoisted__U64_1803;
                Type_delete(hoisted__Type_1802, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1803);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1804 = 16;
                (void)hoisted__U32_1804;
                U32 hoisted__U32_1805 = U32_mul(i, hoisted__U32_1804);
                (void)hoisted__U32_1805;
                Type *hoisted__Type_1806 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1806;
                U64 hoisted__U64_1807 = (U64)(hoisted__U32_1805);
                (void)hoisted__U64_1807;
                Type_delete(hoisted__Type_1806, 1);
                U32 hoisted__U32_1808 = 16;
                (void)hoisted__U32_1808;
                Type *hoisted__Type_1809 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1809;
                void *hoisted__v_1810 = ptr_add(new_data, hoisted__U64_1807);
                (void)hoisted__v_1810;
                (void)hoisted__v_1810;
                U64 hoisted__U64_1811 = (U64)(hoisted__U32_1808);
                (void)hoisted__U64_1811;
                Type_delete(hoisted__Type_1809, 1);
                memcpy(hoisted__v_1810, cloned, hoisted__U64_1811);
                U32 hoisted__U32_1812 = 16;
                (void)hoisted__U32_1812;
                Type *hoisted__Type_1813 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1813;
                I32 hoisted__I32_1814 = 0;
                (void)hoisted__I32_1814;
                U64 hoisted__U64_1815 = (U64)(hoisted__U32_1812);
                (void)hoisted__U64_1815;
                Type_delete(hoisted__Type_1813, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1814, hoisted__U64_1815); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1816 = U32_gt(_rc_U32_1798, _re_U32_1798);
                (void)_wcond_Bool_1816;
                if (_wcond_Bool_1816) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1798);
                U32_dec(&_rc_U32_1798);
                U32 hoisted__U32_1817 = 16;
                (void)hoisted__U32_1817;
                U32 hoisted__U32_1818 = U32_mul(i, hoisted__U32_1817);
                (void)hoisted__U32_1818;
                Type *hoisted__Type_1819 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1819;
                U64 hoisted__U64_1820 = (U64)(hoisted__U32_1818);
                (void)hoisted__U64_1820;
                Type_delete(hoisted__Type_1819, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1820);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1821 = 16;
                (void)hoisted__U32_1821;
                U32 hoisted__U32_1822 = U32_mul(i, hoisted__U32_1821);
                (void)hoisted__U32_1822;
                Type *hoisted__Type_1823 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1823;
                U64 hoisted__U64_1824 = (U64)(hoisted__U32_1822);
                (void)hoisted__U64_1824;
                Type_delete(hoisted__Type_1823, 1);
                U32 hoisted__U32_1825 = 16;
                (void)hoisted__U32_1825;
                Type *hoisted__Type_1826 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1826;
                void *hoisted__v_1827 = ptr_add(new_data, hoisted__U64_1824);
                (void)hoisted__v_1827;
                (void)hoisted__v_1827;
                U64 hoisted__U64_1828 = (U64)(hoisted__U32_1825);
                (void)hoisted__U64_1828;
                Type_delete(hoisted__Type_1826, 1);
                memcpy(hoisted__v_1827, cloned, hoisted__U64_1828);
                U32 hoisted__U32_1829 = 16;
                (void)hoisted__U32_1829;
                Type *hoisted__Type_1830 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1830;
                I32 hoisted__I32_1831 = 0;
                (void)hoisted__I32_1831;
                U64 hoisted__U64_1832 = (U64)(hoisted__U32_1829);
                (void)hoisted__U64_1832;
                Type_delete(hoisted__Type_1830, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1831, hoisted__U64_1832); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1838 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1838->data = new_data;
    hoisted__Vec__Str_1838->count = self->count;
    hoisted__Vec__Str_1838->cap = self->cap;
    (void)hoisted__Vec__Str_1838;
    return hoisted__Vec__Str_1838;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1839 = 16;
    (void)hoisted__U32_1839;
    return hoisted__U32_1839;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1842 = 8;
    (void)hoisted__U32_1842;
    return hoisted__U32_1842;
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
    I64 hoisted__I64_2061 = 0;
    (void)hoisted__I64_2061;
    Bool hoisted__Bool_2062 = I64_eq(val, hoisted__I64_2061);
    (void)hoisted__Bool_2062;
    if (hoisted__Bool_2062) {
        U64 hoisted__U64_2031 = 2ULL;
        (void)hoisted__U64_2031;
        void * buf = malloc(hoisted__U64_2031);
        I64 hoisted__I64_2032 = 48;
        (void)hoisted__I64_2032;
        U64 hoisted__U64_2033 = 1ULL;
        (void)hoisted__U64_2033;
        memcpy(buf, &hoisted__I64_2032, hoisted__U64_2033);
        U64 hoisted__U64_2034 = 1ULL;
        (void)hoisted__U64_2034;
        void *hoisted__v_2035 = ptr_add(buf, hoisted__U64_2034);
        (void)hoisted__v_2035;
        (void)hoisted__v_2035;
        I32 hoisted__I32_2036 = 0;
        (void)hoisted__I32_2036;
        U64 hoisted__U64_2037 = 1ULL;
        (void)hoisted__U64_2037;
        memset(hoisted__v_2035, hoisted__I32_2036, hoisted__U64_2037);
        I64 hoisted__I64_2038 = 1;
        (void)hoisted__I64_2038;
        I64 hoisted__I64_2039 = 1;
        (void)hoisted__I64_2039;
        Str *hoisted__Str_2040 = malloc(sizeof(Str));
        hoisted__Str_2040->c_str = buf;
        hoisted__Str_2040->count = hoisted__I64_2038;
        hoisted__Str_2040->cap = hoisted__I64_2039;
        (void)hoisted__Str_2040;
        { Str * _ret_val = hoisted__Str_2040;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_2063 = 0;
    (void)hoisted__I64_2063;
    Bool hoisted__Bool_2064 = I64_lt(val, hoisted__I64_2063);
    (void)hoisted__Bool_2064;
    if (hoisted__Bool_2064) {
        Bool hoisted__Bool_2041 = 1;
        (void)hoisted__Bool_2041;
        is_neg = hoisted__Bool_2041;
        I64 hoisted__I64_2042 = 0;
        (void)hoisted__I64_2042;
        I64 hoisted__I64_2043 = I64_sub(hoisted__I64_2042, val);
        (void)hoisted__I64_2043;
        v = hoisted__I64_2043;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_2045 = 0;
        (void)hoisted__I64_2045;
        Bool _wcond_Bool_2044 = I64_gt(tmp, hoisted__I64_2045);
        (void)_wcond_Bool_2044;
        if (_wcond_Bool_2044) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_2046 = 10;
        (void)hoisted__I64_2046;
        I64 hoisted__I64_2047 = I64_div(tmp, hoisted__I64_2046);
        (void)hoisted__I64_2047;
        tmp = hoisted__I64_2047;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_2065 = 1ULL;
    (void)hoisted__U64_2065;
    U64 hoisted__U64_2066 = U64_add(total, hoisted__U64_2065);
    (void)hoisted__U64_2066;
    void * buf = malloc(hoisted__U64_2066);
    if (is_neg) {
        I64 hoisted__I64_2048 = 45;
        (void)hoisted__I64_2048;
        U64 hoisted__U64_2049 = 1ULL;
        (void)hoisted__U64_2049;
        memcpy(buf, &hoisted__I64_2048, hoisted__U64_2049);
    }
    U64 hoisted__U64_2067 = 1ULL;
    (void)hoisted__U64_2067;
    U64 i = U64_sub(total, hoisted__U64_2067);
    while (1) {
        I64 hoisted__I64_2051 = 0;
        (void)hoisted__I64_2051;
        Bool _wcond_Bool_2050 = I64_gt(v, hoisted__I64_2051);
        (void)_wcond_Bool_2050;
        if (_wcond_Bool_2050) {
        } else {
            break;
        }
        I64 hoisted__I64_2052 = 10;
        (void)hoisted__I64_2052;
        I64 hoisted__I64_2053 = I64_mod(v, hoisted__I64_2052);
        (void)hoisted__I64_2053;
        I64 hoisted__I64_2054 = 48;
        (void)hoisted__I64_2054;
        I64 hoisted__I64_2055 = I64_add(hoisted__I64_2053, hoisted__I64_2054);
        (void)hoisted__I64_2055;
        void *hoisted__v_2056 = ptr_add(buf, i);
        (void)hoisted__v_2056;
        (void)hoisted__v_2056;
        U8 hoisted__U8_2057 = I64_to_u8(hoisted__I64_2055);
        (void)hoisted__U8_2057;
        U64 hoisted__U64_2058 = 1ULL;
        (void)hoisted__U64_2058;
        memcpy(hoisted__v_2056, &hoisted__U8_2057, hoisted__U64_2058);
        I64 hoisted__I64_2059 = 10;
        (void)hoisted__I64_2059;
        I64 hoisted__I64_2060 = I64_div(v, hoisted__I64_2059);
        (void)hoisted__I64_2060;
        v = hoisted__I64_2060;
        U64_dec(&i);
    }
    void *hoisted__v_2068 = ptr_add(buf, total);
    (void)hoisted__v_2068;
    (void)hoisted__v_2068;
    I32 hoisted__I32_2069 = 0;
    (void)hoisted__I32_2069;
    U64 hoisted__U64_2070 = 1ULL;
    (void)hoisted__U64_2070;
    memset(hoisted__v_2068, hoisted__I32_2069, hoisted__U64_2070);
    Str *hoisted__Str_2071 = malloc(sizeof(Str));
    hoisted__Str_2071->c_str = buf;
    hoisted__Str_2071->count = total;
    hoisted__Str_2071->cap = total;
    (void)hoisted__Str_2071;
    return hoisted__Str_2071;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_2091 = 8;
    (void)hoisted__U32_2091;
    return hoisted__U32_2091;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2242 = 0;
    (void)hoisted__U32_2242;
    U64 hoisted__U64_2243 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2242); });
    (void)hoisted__U64_2243;
    return hoisted__U64_2243;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2246 = I64_cmp(a, b);
    (void)hoisted__I64_2246;
    I64 hoisted__I64_2247 = -1;
    (void)hoisted__I64_2247;
    Bool hoisted__Bool_2248 = I64_eq(hoisted__I64_2246, hoisted__I64_2247);
    (void)hoisted__Bool_2248;
    return hoisted__Bool_2248;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2249 = I64_cmp(a, b);
    (void)hoisted__I64_2249;
    I64 hoisted__I64_2250 = 1;
    (void)hoisted__I64_2250;
    Bool hoisted__Bool_2251 = I64_eq(hoisted__I64_2249, hoisted__I64_2250);
    (void)hoisted__Bool_2251;
    return hoisted__Bool_2251;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2252 = I64_eq(a, b);
    (void)hoisted__Bool_2252;
    Bool hoisted__Bool_2253 = not(hoisted__Bool_2252);
    (void)hoisted__Bool_2253;
    return hoisted__Bool_2253;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2294 = 0;
    (void)_m_Bool_2294;
    {
        Bool hoisted__Bool_2297 = 1;
        (void)hoisted__Bool_2297;
        Bool hoisted__Bool_2298 = Bool_eq(a, hoisted__Bool_2297);
        (void)hoisted__Bool_2298;
        if (hoisted__Bool_2298) {
            Bool hoisted__Bool_2295 = Bool_clone(&b);
            (void)hoisted__Bool_2295;
            _m_Bool_2294 = hoisted__Bool_2295;
        } else {
            Bool hoisted__Bool_2296 = 0;
            (void)hoisted__Bool_2296;
            _m_Bool_2294 = hoisted__Bool_2296;
        }
    }
    return _m_Bool_2294;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2308 = Bool_eq(a, b);
    (void)hoisted__Bool_2308;
    if (hoisted__Bool_2308) {
        I64 hoisted__I64_2306 = 0;
        (void)hoisted__I64_2306;
        { I64 _ret_val = hoisted__I64_2306;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2307 = -1;
        (void)hoisted__I64_2307;
        return hoisted__I64_2307;
    }
    I64 hoisted__I64_2309 = 1;
    (void)hoisted__I64_2309;
    return hoisted__I64_2309;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2310 = 1;
    (void)hoisted__U32_2310;
    return hoisted__U32_2310;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2311 = 0;
    (void)hoisted__U32_2311;
    U64 hoisted__U64_2312 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2311); });
    (void)hoisted__U64_2312;
    return hoisted__U64_2312;
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
    Bool hoisted__Bool_2338 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2338;
    if (hoisted__Bool_2338) {
        Bool hoisted__Bool_2328 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2328;
        { Bool _ret_val = hoisted__Bool_2328;
                return _ret_val; }
    }
    Bool hoisted__Bool_2339 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2339;
    if (hoisted__Bool_2339) {
        Bool hoisted__Bool_2329 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2329;
        { Bool _ret_val = hoisted__Bool_2329;
                return _ret_val; }
    }
    Bool hoisted__Bool_2340 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2340;
    if (hoisted__Bool_2340) {
        Bool hoisted__Bool_2330 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2330;
        { Bool _ret_val = hoisted__Bool_2330;
                return _ret_val; }
    }
    Bool hoisted__Bool_2341 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        Bool hoisted__Bool_2331 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2331;
        { Bool _ret_val = hoisted__Bool_2331;
                return _ret_val; }
    }
    Bool hoisted__Bool_2342 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2342;
    if (hoisted__Bool_2342) {
        Bool hoisted__Bool_2332 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2332;
        { Bool _ret_val = hoisted__Bool_2332;
                return _ret_val; }
    }
    Bool hoisted__Bool_2343 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2343;
    if (hoisted__Bool_2343) {
        Bool hoisted__Bool_2333 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2333;
        { Bool _ret_val = hoisted__Bool_2333;
                return _ret_val; }
    }
    Bool hoisted__Bool_2344 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2344;
    if (hoisted__Bool_2344) {
        Bool hoisted__Bool_2334 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2334;
        { Bool _ret_val = hoisted__Bool_2334;
                return _ret_val; }
    }
    Bool hoisted__Bool_2345 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2345;
    if (hoisted__Bool_2345) {
        Bool hoisted__Bool_2335 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2335;
        { Bool _ret_val = hoisted__Bool_2335;
                return _ret_val; }
    }
    Bool hoisted__Bool_2346 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2346;
    if (hoisted__Bool_2346) {
        Bool hoisted__Bool_2336 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2336;
        { Bool _ret_val = hoisted__Bool_2336;
                return _ret_val; }
    }
    Bool hoisted__Bool_2347 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2347;
    if (hoisted__Bool_2347) {
        Bool hoisted__Bool_2337 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2337;
        { Bool _ret_val = hoisted__Bool_2337;
                return _ret_val; }
    }
    Bool hoisted__Bool_2348 = 0;
    (void)hoisted__Bool_2348;
    return hoisted__Bool_2348;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2370 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2370;
    if (hoisted__Bool_2370) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2371 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2371;
    if (hoisted__Bool_2371) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2372 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2372;
    if (hoisted__Bool_2372) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2373 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2373;
    if (hoisted__Bool_2373) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2374 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2374;
    if (hoisted__Bool_2374) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2375 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2375;
    if (hoisted__Bool_2375) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2376 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2376;
    if (hoisted__Bool_2376) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2377 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2377;
    if (hoisted__Bool_2377) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2378 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2378;
    if (hoisted__Bool_2378) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2379 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2379;
    if (hoisted__Bool_2379) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2380 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2380;
    UNREACHABLE(&hoisted__Str_2380);
    Str_delete(&hoisted__Str_2380, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2381 = 4;
    (void)hoisted__U32_2381;
    return hoisted__U32_2381;
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
    Bool hoisted__Bool_2433 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2433;
    if (hoisted__Bool_2433) {
        Str *hoisted__Str_2423 = get_payload(self);
        (void)hoisted__Str_2423;
        (void)hoisted__Str_2423;
        Bool hoisted__Bool_2424 = 0;
        (void)hoisted__Bool_2424;
        Str_delete(hoisted__Str_2423, hoisted__Bool_2424);
    }
    Bool hoisted__Bool_2434 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2434;
    if (hoisted__Bool_2434) {
        Str *hoisted__Str_2425 = get_payload(self);
        (void)hoisted__Str_2425;
        (void)hoisted__Str_2425;
        Bool hoisted__Bool_2426 = 0;
        (void)hoisted__Bool_2426;
        Str_delete(hoisted__Str_2425, hoisted__Bool_2426);
    }
    Bool hoisted__Bool_2435 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2435;
    if (hoisted__Bool_2435) {
        Str *hoisted__Str_2427 = get_payload(self);
        (void)hoisted__Str_2427;
        (void)hoisted__Str_2427;
        Bool hoisted__Bool_2428 = 0;
        (void)hoisted__Bool_2428;
        Str_delete(hoisted__Str_2427, hoisted__Bool_2428);
    }
    Bool hoisted__Bool_2436 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2436;
    if (hoisted__Bool_2436) {
        Primitive *hoisted__Primitive_2429 = get_payload(self);
        (void)hoisted__Primitive_2429;
        (void)hoisted__Primitive_2429;
        Bool hoisted__Bool_2430 = 0;
        (void)hoisted__Bool_2430;
        Primitive_delete(hoisted__Primitive_2429, hoisted__Bool_2430);
    }
    Bool hoisted__Bool_2437 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2437;
    if (hoisted__Bool_2437) {
        Str *hoisted__Str_2431 = get_payload(self);
        (void)hoisted__Str_2431;
        (void)hoisted__Str_2431;
        Bool hoisted__Bool_2432 = 0;
        (void)hoisted__Bool_2432;
        Str_delete(hoisted__Str_2431, hoisted__Bool_2432);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2521 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2521;
    if (hoisted__Bool_2521) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2522 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2522;
    if (hoisted__Bool_2522) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2523 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2523;
    if (hoisted__Bool_2523) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2513 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2513;
        Type *hoisted__Type_2514 = Type_Struct(hoisted__Str_2513);
        (void)hoisted__Type_2514;
        { Type * _ret_val = hoisted__Type_2514;
                return _ret_val; }
    }
    Bool hoisted__Bool_2524 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2524;
    if (hoisted__Bool_2524) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2525 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2525;
    if (hoisted__Bool_2525) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2515 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2515;
        Type *hoisted__Type_2516 = Type_Enum(hoisted__Str_2515);
        (void)hoisted__Type_2516;
        { Type * _ret_val = hoisted__Type_2516;
                return _ret_val; }
    }
    Bool hoisted__Bool_2526 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2526;
    if (hoisted__Bool_2526) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2527 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2527;
    if (hoisted__Bool_2527) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2528 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2528;
    if (hoisted__Bool_2528) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2529 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2529;
    if (hoisted__Bool_2529) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2530 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2530;
    if (hoisted__Bool_2530) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2517 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2517;
        Type *hoisted__Type_2518 = Type_Custom(hoisted__Str_2517);
        (void)hoisted__Type_2518;
        { Type * _ret_val = hoisted__Type_2518;
                return _ret_val; }
    }
    Bool hoisted__Bool_2531 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2531;
    if (hoisted__Bool_2531) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2519 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2519;
        Type *hoisted__Type_2520 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2519; _oa; }));
        (void)hoisted__Type_2520;
        { Type * _ret_val = hoisted__Type_2520;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2532 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2532;
    Type *hoisted__Type_2533 = Type_FuncPtrSig(hoisted__Str_2532);
    (void)hoisted__Type_2533;
    return hoisted__Type_2533;
}

U32 Type_size(void) {
    U32 hoisted__U32_2534 = 24;
    (void)hoisted__U32_2534;
    return hoisted__U32_2534;
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
    Bool hoisted__Bool_2635 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2635;
    if (hoisted__Bool_2635) {
        Bool hoisted__Bool_2627 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2627;
        { Bool _ret_val = hoisted__Bool_2627;
                return _ret_val; }
    }
    Bool hoisted__Bool_2636 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2636;
    if (hoisted__Bool_2636) {
        Bool hoisted__Bool_2628 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2628;
        { Bool _ret_val = hoisted__Bool_2628;
                return _ret_val; }
    }
    Bool hoisted__Bool_2637 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2637;
    if (hoisted__Bool_2637) {
        Bool hoisted__Bool_2629 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2629;
        { Bool _ret_val = hoisted__Bool_2629;
                return _ret_val; }
    }
    Bool hoisted__Bool_2638 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2638;
    if (hoisted__Bool_2638) {
        Bool hoisted__Bool_2630 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2630;
        { Bool _ret_val = hoisted__Bool_2630;
                return _ret_val; }
    }
    Bool hoisted__Bool_2639 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2639;
    if (hoisted__Bool_2639) {
        Bool hoisted__Bool_2631 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2631;
        { Bool _ret_val = hoisted__Bool_2631;
                return _ret_val; }
    }
    Bool hoisted__Bool_2640 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2640;
    if (hoisted__Bool_2640) {
        Bool hoisted__Bool_2632 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2632;
        { Bool _ret_val = hoisted__Bool_2632;
                return _ret_val; }
    }
    Bool hoisted__Bool_2641 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2641;
    if (hoisted__Bool_2641) {
        Bool hoisted__Bool_2633 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2633;
        { Bool _ret_val = hoisted__Bool_2633;
                return _ret_val; }
    }
    Bool hoisted__Bool_2642 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2642;
    if (hoisted__Bool_2642) {
        Bool hoisted__Bool_2634 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2634;
        { Bool _ret_val = hoisted__Bool_2634;
                return _ret_val; }
    }
    Bool hoisted__Bool_2643 = 0;
    (void)hoisted__Bool_2643;
    return hoisted__Bool_2643;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2661 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2661;
    if (hoisted__Bool_2661) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2662 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2662;
    if (hoisted__Bool_2662) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2663 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2663;
    if (hoisted__Bool_2663) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2664 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2664;
    if (hoisted__Bool_2664) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2665 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2665;
    if (hoisted__Bool_2665) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2666 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2666;
    if (hoisted__Bool_2666) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2667 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2667;
    if (hoisted__Bool_2667) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2668 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2668;
    if (hoisted__Bool_2668) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    static Str hoisted__Str_2669 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2669;
    UNREACHABLE(&hoisted__Str_2669);
    Str_delete(&hoisted__Str_2669, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2670 = 4;
    (void)hoisted__U32_2670;
    return hoisted__U32_2670;
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
    Bool hoisted__Bool_2675 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2675;
    if (hoisted__Bool_2675) {
        Bool hoisted__Bool_2672 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2672;
        { Bool _ret_val = hoisted__Bool_2672;
                return _ret_val; }
    }
    Bool hoisted__Bool_2676 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2676;
    if (hoisted__Bool_2676) {
        Bool hoisted__Bool_2673 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2673;
        { Bool _ret_val = hoisted__Bool_2673;
                return _ret_val; }
    }
    Bool hoisted__Bool_2677 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2677;
    if (hoisted__Bool_2677) {
        Bool hoisted__Bool_2674 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2674;
        { Bool _ret_val = hoisted__Bool_2674;
                return _ret_val; }
    }
    Bool hoisted__Bool_2678 = 0;
    (void)hoisted__Bool_2678;
    return hoisted__Bool_2678;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2686 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2686;
    if (hoisted__Bool_2686) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2687 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2687;
    if (hoisted__Bool_2687) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2688 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2688;
    if (hoisted__Bool_2688) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2689 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2689;
    UNREACHABLE(&hoisted__Str_2689);
    Str_delete(&hoisted__Str_2689, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2690 = 4;
    (void)hoisted__U32_2690;
    return hoisted__U32_2690;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2692 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2692;
    Declaration *hoisted__Declaration_2693 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2693->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2693->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2693->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2693->is_mut = self->is_mut;
    hoisted__Declaration_2693->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2693->is_priv = self->is_priv;
    hoisted__Declaration_2693->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2693->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2693->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2693->default_value = hoisted__Expr_2692;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2693->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2693;
    return hoisted__Declaration_2693;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2694 = 0;
    (void)hoisted__Bool_2694;
    Str_delete(&self->name, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    Str_delete(&self->doc, hoisted__Bool_2695);
    Bool hoisted__Bool_2696 = 0;
    (void)hoisted__Bool_2696;
    Str_delete(&self->explicit_type, hoisted__Bool_2696);
    Bool hoisted__Bool_2697 = 0;
    (void)hoisted__Bool_2697;
    Bool_delete(&self->is_mut, hoisted__Bool_2697);
    Bool hoisted__Bool_2698 = 0;
    (void)hoisted__Bool_2698;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2698);
    Bool hoisted__Bool_2699 = 0;
    (void)hoisted__Bool_2699;
    Bool_delete(&self->is_priv, hoisted__Bool_2699);
    Bool hoisted__Bool_2700 = 0;
    (void)hoisted__Bool_2700;
    Bool_delete(&self->used, hoisted__Bool_2700);
    Bool hoisted__Bool_2701 = 0;
    (void)hoisted__Bool_2701;
    OwnType_delete(&self->own_type, hoisted__Bool_2701);
    Bool hoisted__Bool_2702 = 0;
    (void)hoisted__Bool_2702;
    Type_delete(&self->til_type, hoisted__Bool_2702);
    Bool hoisted__Bool_2703 = 1;
    (void)hoisted__Bool_2703;
    Expr_delete(self->default_value, hoisted__Bool_2703);
    Bool hoisted__Bool_2704 = 0;
    (void)hoisted__Bool_2704;
    Str_delete(&self->orig_name, hoisted__Bool_2704);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2705 = 104;
    (void)hoisted__U32_2705;
    return hoisted__U32_2705;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2707 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2707->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2707->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2707->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2707->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2707->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2707->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2707->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2707->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2707->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2707->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2707->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2707;
    return hoisted__FunctionDef_2707;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    FuncType_delete(&self->func_type, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2709);
    Bool hoisted__Bool_2710 = 0;
    (void)hoisted__Bool_2710;
    Str_delete(&self->return_type, hoisted__Bool_2710);
    Bool hoisted__Bool_2711 = 0;
    (void)hoisted__Bool_2711;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2711);
    Bool hoisted__Bool_2712 = 0;
    (void)hoisted__Bool_2712;
    I32_delete(&self->variadic_index, hoisted__Bool_2712);
    Bool hoisted__Bool_2713 = 0;
    (void)hoisted__Bool_2713;
    I32_delete(&self->kwargs_index, hoisted__Bool_2713);
    Bool hoisted__Bool_2714 = 0;
    (void)hoisted__Bool_2714;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2714);
    Bool hoisted__Bool_2715 = 0;
    (void)hoisted__Bool_2715;
    Bool_delete(&self->auto_generated, hoisted__Bool_2715);
    Bool hoisted__Bool_2716 = 0;
    (void)hoisted__Bool_2716;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2716);
    Bool hoisted__Bool_2717 = 0;
    (void)hoisted__Bool_2717;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2717);
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    Str_delete(&self->closure_name, hoisted__Bool_2718);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2719 = 0;
    (void)hoisted__U32_2719;
    U64 hoisted__U64_2720 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2719); });
    (void)hoisted__U64_2720;
    return hoisted__U64_2720;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2721 = 104;
    (void)hoisted__U32_2721;
    return hoisted__U32_2721;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2724 = malloc(sizeof(FCallData));
    hoisted__FCallData_2724->is_splat = self->is_splat;
    hoisted__FCallData_2724->does_throw = self->does_throw;
    hoisted__FCallData_2724->is_bang = self->is_bang;
    hoisted__FCallData_2724->own_args = self->own_args;
    hoisted__FCallData_2724->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2724->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2724;
    return hoisted__FCallData_2724;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2725 = 0;
    (void)hoisted__Bool_2725;
    Bool_delete(&self->is_splat, hoisted__Bool_2725);
    Bool hoisted__Bool_2726 = 0;
    (void)hoisted__Bool_2726;
    Bool_delete(&self->does_throw, hoisted__Bool_2726);
    Bool hoisted__Bool_2727 = 0;
    (void)hoisted__Bool_2727;
    Bool_delete(&self->is_bang, hoisted__Bool_2727);
    Bool hoisted__Bool_2728 = 0;
    (void)hoisted__Bool_2728;
    U64_delete(&self->own_args, hoisted__Bool_2728);
    Bool hoisted__Bool_2729 = 0;
    (void)hoisted__Bool_2729;
    Bool_delete(&self->swap_replace, hoisted__Bool_2729);
    Bool hoisted__Bool_2730 = 0;
    (void)hoisted__Bool_2730;
    Type_delete(&self->til_type, hoisted__Bool_2730);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2731 = 0;
    (void)hoisted__U32_2731;
    U64 hoisted__U64_2732 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2731); });
    (void)hoisted__U64_2732;
    return hoisted__U64_2732;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2733 = 48;
    (void)hoisted__U32_2733;
    return hoisted__U32_2733;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2745 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2745->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2745->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2745;
    return hoisted__LiteralNumData_2745;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2746 = 0;
    (void)hoisted__Bool_2746;
    Str_delete(&self->text, hoisted__Bool_2746);
    Bool hoisted__Bool_2747 = 0;
    (void)hoisted__Bool_2747;
    Type_delete(&self->til_type, hoisted__Bool_2747);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2748 = 0;
    (void)hoisted__U32_2748;
    U64 hoisted__U64_2749 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2748); });
    (void)hoisted__U64_2749;
    return hoisted__U64_2749;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2750 = 40;
    (void)hoisted__U32_2750;
    return hoisted__U32_2750;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2760 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2760->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2760->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2760;
    return hoisted__IdentData_2760;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2761 = 0;
    (void)hoisted__Bool_2761;
    Str_delete(&self->name, hoisted__Bool_2761);
    Bool hoisted__Bool_2762 = 0;
    (void)hoisted__Bool_2762;
    Type_delete(&self->til_type, hoisted__Bool_2762);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2763 = 0;
    (void)hoisted__U32_2763;
    U64 hoisted__U64_2764 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2763); });
    (void)hoisted__U64_2764;
    return hoisted__U64_2764;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2765 = 40;
    (void)hoisted__U32_2765;
    return hoisted__U32_2765;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2771 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2771->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2771->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2771;
    return hoisted__FieldAccessData_2771;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
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

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2774 = 0;
    (void)hoisted__U32_2774;
    U64 hoisted__U64_2775 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2774); });
    (void)hoisted__U64_2775;
    return hoisted__U64_2775;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2776 = 40;
    (void)hoisted__U32_2776;
    return hoisted__U32_2776;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2857 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2857->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2857->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2857->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2857->is_interface = self->is_interface;
    hoisted__StructDef_2857->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2857->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2857;
    return hoisted__StructDef_2857;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2858 = 0;
    (void)hoisted__Bool_2858;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2858);
    Bool hoisted__Bool_2859 = 0;
    (void)hoisted__Bool_2859;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2859);
    Bool hoisted__Bool_2860 = 0;
    (void)hoisted__Bool_2860;
    Str_delete(&self->c_tag, hoisted__Bool_2860);
    Bool hoisted__Bool_2861 = 0;
    (void)hoisted__Bool_2861;
    Bool_delete(&self->is_interface, hoisted__Bool_2861);
    Bool hoisted__Bool_2862 = 0;
    (void)hoisted__Bool_2862;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2862);
    Bool hoisted__Bool_2863 = 0;
    (void)hoisted__Bool_2863;
    Str_delete(&self->implements_name, hoisted__Bool_2863);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2864 = 0;
    (void)hoisted__U32_2864;
    U64 hoisted__U64_2865 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2864); });
    (void)hoisted__U64_2865;
    return hoisted__U64_2865;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2866 = 72;
    (void)hoisted__U32_2866;
    return hoisted__U32_2866;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2871 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2871->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2871->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2871->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2871->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2871->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2871;
    return hoisted__EnumDef_2871;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2872 = 0;
    (void)hoisted__Bool_2872;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2872);
    Bool hoisted__Bool_2873 = 0;
    (void)hoisted__Bool_2873;
    Vec__Str_delete(&self->variants, hoisted__Bool_2873);
    Bool hoisted__Bool_2874 = 0;
    (void)hoisted__Bool_2874;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2874);
    Bool hoisted__Bool_2875 = 0;
    (void)hoisted__Bool_2875;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2875);
    Bool hoisted__Bool_2876 = 0;
    (void)hoisted__Bool_2876;
    Str_delete(&self->implements_name, hoisted__Bool_2876);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2877 = 0;
    (void)hoisted__U32_2877;
    U64 hoisted__U64_2878 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2877); });
    (void)hoisted__U64_2878;
    return hoisted__U64_2878;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2879 = 96;
    (void)hoisted__U32_2879;
    return hoisted__U32_2879;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2975 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2975->name = *_ca; free(_ca); }
    hoisted__AssignData_2975->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2975->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2975->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2975;
    return hoisted__AssignData_2975;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2976 = 0;
    (void)hoisted__Bool_2976;
    Str_delete(&self->name, hoisted__Bool_2976);
    Bool hoisted__Bool_2977 = 0;
    (void)hoisted__Bool_2977;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2977);
    Bool hoisted__Bool_2978 = 0;
    (void)hoisted__Bool_2978;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2978);
    Bool hoisted__Bool_2979 = 0;
    (void)hoisted__Bool_2979;
    Bool_delete(&self->swap_replace, hoisted__Bool_2979);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2980 = 0;
    (void)hoisted__U32_2980;
    U64 hoisted__U64_2981 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2980); });
    (void)hoisted__U64_2981;
    return hoisted__U64_2981;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2982 = 24;
    (void)hoisted__U32_2982;
    return hoisted__U32_2982;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2984 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2984->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2984->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2984;
    return hoisted__FieldAssignData_2984;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2985 = 0;
    (void)hoisted__Bool_2985;
    Str_delete(&self->name, hoisted__Bool_2985);
    Bool hoisted__Bool_2986 = 0;
    (void)hoisted__Bool_2986;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2986);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2987 = 0;
    (void)hoisted__U32_2987;
    U64 hoisted__U64_2988 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2987); });
    (void)hoisted__U64_2988;
    return hoisted__U64_2988;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2989 = 24;
    (void)hoisted__U32_2989;
    return hoisted__U32_2989;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2991 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2991->name = *_ca; free(_ca); }
    hoisted__ForInData_2991->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2991->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2991;
    return hoisted__ForInData_2991;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2992 = 0;
    (void)hoisted__Bool_2992;
    Str_delete(&self->name, hoisted__Bool_2992);
    Bool hoisted__Bool_2993 = 0;
    (void)hoisted__Bool_2993;
    Bool_delete(&self->is_mut, hoisted__Bool_2993);
    Bool hoisted__Bool_2994 = 0;
    (void)hoisted__Bool_2994;
    Type_delete(&self->til_type, hoisted__Bool_2994);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2995 = 0;
    (void)hoisted__U32_2995;
    U64 hoisted__U64_2996 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2995); });
    (void)hoisted__U64_2996;
    return hoisted__U64_2996;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2997 = 48;
    (void)hoisted__U32_2997;
    return hoisted__U32_2997;
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
    Bool hoisted__Bool_3027 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3027;
    if (hoisted__Bool_3027) {
        Str *hoisted__Str_3021 = get_payload(self);
        (void)hoisted__Str_3021;
        (void)hoisted__Str_3021;
        Bool hoisted__Bool_3022 = 0;
        (void)hoisted__Bool_3022;
        Str_delete(hoisted__Str_3021, hoisted__Bool_3022);
    }
    Bool hoisted__Bool_3028 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3028;
    if (hoisted__Bool_3028) {
        LiteralNumData *hoisted__LiteralNumData_3023 = get_payload(self);
        (void)hoisted__LiteralNumData_3023;
        (void)hoisted__LiteralNumData_3023;
        Bool hoisted__Bool_3024 = 0;
        (void)hoisted__Bool_3024;
        LiteralNumData_delete(hoisted__LiteralNumData_3023, hoisted__Bool_3024);
    }
    Bool hoisted__Bool_3029 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3029;
    if (hoisted__Bool_3029) {
        Bool *hoisted__Bool_3025 = get_payload(self);
        (void)hoisted__Bool_3025;
        (void)hoisted__Bool_3025;
        Bool hoisted__Bool_3026 = 0;
        (void)hoisted__Bool_3026;
        Bool_delete(hoisted__Bool_3025, hoisted__Bool_3026);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_3078 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3078;
    if (hoisted__Bool_3078) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3073 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3073;
        Literal *hoisted__Literal_3074 = Literal_Str(hoisted__Str_3073);
        (void)hoisted__Literal_3074;
        { Literal * _ret_val = hoisted__Literal_3074;
                return _ret_val; }
    }
    Bool hoisted__Bool_3079 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3079;
    if (hoisted__Bool_3079) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3075 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3075;
        Literal *hoisted__Literal_3076 = Literal_Num(hoisted__LiteralNumData_3075);
        (void)hoisted__Literal_3076;
        { Literal * _ret_val = hoisted__Literal_3076;
                return _ret_val; }
    }
    Bool hoisted__Bool_3080 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3080;
    if (hoisted__Bool_3080) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3077 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3077;
        { Literal * _ret_val = hoisted__Literal_3077;
                return _ret_val; }
    }
    Bool hoisted__Bool_3081 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_3081;
    if (hoisted__Bool_3081) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_3082 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_3082;
    if (hoisted__Bool_3082) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3083 = 48;
    (void)hoisted__U32_3083;
    return hoisted__U32_3083;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3086 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3086->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3086->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3086;
    return hoisted__MatchData_3086;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3087 = 0;
    (void)hoisted__Bool_3087;
    Type_delete(&self->til_type, hoisted__Bool_3087);
    Bool hoisted__Bool_3088 = 0;
    (void)hoisted__Bool_3088;
    Str_delete(&self->result_temp, hoisted__Bool_3088);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3089 = 0;
    (void)hoisted__U32_3089;
    U64 hoisted__U64_3090 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3089); });
    (void)hoisted__U64_3090;
    return hoisted__U64_3090;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3091 = 40;
    (void)hoisted__U32_3091;
    return hoisted__U32_3091;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3096 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3096->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3096;
    return hoisted__CaptureBlockData_3096;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3097 = 0;
    (void)hoisted__Bool_3097;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3097);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3098 = 0;
    (void)hoisted__U32_3098;
    U64 hoisted__U64_3099 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3098); });
    (void)hoisted__U64_3099;
    return hoisted__U64_3099;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3100 = 16;
    (void)hoisted__U32_3100;
    return hoisted__U32_3100;
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
    Bool hoisted__Bool_3279 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3279;
    if (hoisted__Bool_3279) {
        Literal *hoisted__Literal_3251 = get_payload(self);
        (void)hoisted__Literal_3251;
        (void)hoisted__Literal_3251;
        Bool hoisted__Bool_3252 = 0;
        (void)hoisted__Bool_3252;
        Literal_delete(hoisted__Literal_3251, hoisted__Bool_3252);
    }
    Bool hoisted__Bool_3280 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3280;
    if (hoisted__Bool_3280) {
        IdentData *hoisted__IdentData_3253 = get_payload(self);
        (void)hoisted__IdentData_3253;
        (void)hoisted__IdentData_3253;
        Bool hoisted__Bool_3254 = 0;
        (void)hoisted__Bool_3254;
        IdentData_delete(hoisted__IdentData_3253, hoisted__Bool_3254);
    }
    Bool hoisted__Bool_3281 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3281;
    if (hoisted__Bool_3281) {
        Declaration *hoisted__Declaration_3255 = get_payload(self);
        (void)hoisted__Declaration_3255;
        (void)hoisted__Declaration_3255;
        Bool hoisted__Bool_3256 = 0;
        (void)hoisted__Bool_3256;
        Declaration_delete(hoisted__Declaration_3255, hoisted__Bool_3256);
    }
    Bool hoisted__Bool_3282 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3282;
    if (hoisted__Bool_3282) {
        AssignData *hoisted__AssignData_3257 = get_payload(self);
        (void)hoisted__AssignData_3257;
        (void)hoisted__AssignData_3257;
        Bool hoisted__Bool_3258 = 0;
        (void)hoisted__Bool_3258;
        AssignData_delete(hoisted__AssignData_3257, hoisted__Bool_3258);
    }
    Bool hoisted__Bool_3283 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3283;
    if (hoisted__Bool_3283) {
        FCallData *hoisted__FCallData_3259 = get_payload(self);
        (void)hoisted__FCallData_3259;
        (void)hoisted__FCallData_3259;
        Bool hoisted__Bool_3260 = 0;
        (void)hoisted__Bool_3260;
        FCallData_delete(hoisted__FCallData_3259, hoisted__Bool_3260);
    }
    Bool hoisted__Bool_3284 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3284;
    if (hoisted__Bool_3284) {
        FunctionDef *hoisted__FunctionDef_3261 = get_payload(self);
        (void)hoisted__FunctionDef_3261;
        (void)hoisted__FunctionDef_3261;
        Bool hoisted__Bool_3262 = 0;
        (void)hoisted__Bool_3262;
        FunctionDef_delete(hoisted__FunctionDef_3261, hoisted__Bool_3262);
    }
    Bool hoisted__Bool_3285 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3285;
    if (hoisted__Bool_3285) {
        StructDef *hoisted__StructDef_3263 = get_payload(self);
        (void)hoisted__StructDef_3263;
        (void)hoisted__StructDef_3263;
        Bool hoisted__Bool_3264 = 0;
        (void)hoisted__Bool_3264;
        StructDef_delete(hoisted__StructDef_3263, hoisted__Bool_3264);
    }
    Bool hoisted__Bool_3286 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3286;
    if (hoisted__Bool_3286) {
        EnumDef *hoisted__EnumDef_3265 = get_payload(self);
        (void)hoisted__EnumDef_3265;
        (void)hoisted__EnumDef_3265;
        Bool hoisted__Bool_3266 = 0;
        (void)hoisted__Bool_3266;
        EnumDef_delete(hoisted__EnumDef_3265, hoisted__Bool_3266);
    }
    Bool hoisted__Bool_3287 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3287;
    if (hoisted__Bool_3287) {
        FieldAccessData *hoisted__FieldAccessData_3267 = get_payload(self);
        (void)hoisted__FieldAccessData_3267;
        (void)hoisted__FieldAccessData_3267;
        Bool hoisted__Bool_3268 = 0;
        (void)hoisted__Bool_3268;
        FieldAccessData_delete(hoisted__FieldAccessData_3267, hoisted__Bool_3268);
    }
    Bool hoisted__Bool_3288 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3288;
    if (hoisted__Bool_3288) {
        FieldAssignData *hoisted__FieldAssignData_3269 = get_payload(self);
        (void)hoisted__FieldAssignData_3269;
        (void)hoisted__FieldAssignData_3269;
        Bool hoisted__Bool_3270 = 0;
        (void)hoisted__Bool_3270;
        FieldAssignData_delete(hoisted__FieldAssignData_3269, hoisted__Bool_3270);
    }
    Bool hoisted__Bool_3289 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3289;
    if (hoisted__Bool_3289) {
        ForInData *hoisted__ForInData_3271 = get_payload(self);
        (void)hoisted__ForInData_3271;
        (void)hoisted__ForInData_3271;
        Bool hoisted__Bool_3272 = 0;
        (void)hoisted__Bool_3272;
        ForInData_delete(hoisted__ForInData_3271, hoisted__Bool_3272);
    }
    Bool hoisted__Bool_3290 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3290;
    if (hoisted__Bool_3290) {
        Str *hoisted__Str_3273 = get_payload(self);
        (void)hoisted__Str_3273;
        (void)hoisted__Str_3273;
        Bool hoisted__Bool_3274 = 0;
        (void)hoisted__Bool_3274;
        Str_delete(hoisted__Str_3273, hoisted__Bool_3274);
    }
    Bool hoisted__Bool_3291 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3291;
    if (hoisted__Bool_3291) {
        MatchData *hoisted__MatchData_3275 = get_payload(self);
        (void)hoisted__MatchData_3275;
        (void)hoisted__MatchData_3275;
        Bool hoisted__Bool_3276 = 0;
        (void)hoisted__Bool_3276;
        MatchData_delete(hoisted__MatchData_3275, hoisted__Bool_3276);
    }
    Bool hoisted__Bool_3292 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3292;
    if (hoisted__Bool_3292) {
        CaptureBlockData *hoisted__CaptureBlockData_3277 = get_payload(self);
        (void)hoisted__CaptureBlockData_3277;
        (void)hoisted__CaptureBlockData_3277;
        Bool hoisted__Bool_3278 = 0;
        (void)hoisted__Bool_3278;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3277, hoisted__Bool_3278);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3516 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3516;
    if (hoisted__Bool_3516) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3517 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3517;
    if (hoisted__Bool_3517) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3488 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3488;
        NodeType *hoisted__NodeType_3489 = NodeType_Literal(hoisted__Literal_3488);
        (void)hoisted__NodeType_3489;
        { NodeType * _ret_val = hoisted__NodeType_3489;
                return _ret_val; }
    }
    Bool hoisted__Bool_3518 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3518;
    if (hoisted__Bool_3518) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3490 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3490;
        NodeType *hoisted__NodeType_3491 = NodeType_Ident(hoisted__IdentData_3490);
        (void)hoisted__NodeType_3491;
        { NodeType * _ret_val = hoisted__NodeType_3491;
                return _ret_val; }
    }
    Bool hoisted__Bool_3519 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3519;
    if (hoisted__Bool_3519) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3492 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3492;
        NodeType *hoisted__NodeType_3493 = NodeType_Decl(hoisted__Declaration_3492);
        (void)hoisted__NodeType_3493;
        { NodeType * _ret_val = hoisted__NodeType_3493;
                return _ret_val; }
    }
    Bool hoisted__Bool_3520 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3520;
    if (hoisted__Bool_3520) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3494 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3494;
        NodeType *hoisted__NodeType_3495 = NodeType_Assign(hoisted__AssignData_3494);
        (void)hoisted__NodeType_3495;
        { NodeType * _ret_val = hoisted__NodeType_3495;
                return _ret_val; }
    }
    Bool hoisted__Bool_3521 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3521;
    if (hoisted__Bool_3521) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3496 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3496;
        NodeType *hoisted__NodeType_3497 = NodeType_FCall(hoisted__FCallData_3496);
        (void)hoisted__NodeType_3497;
        { NodeType * _ret_val = hoisted__NodeType_3497;
                return _ret_val; }
    }
    Bool hoisted__Bool_3522 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3522;
    if (hoisted__Bool_3522) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3498 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3498;
        NodeType *hoisted__NodeType_3499 = NodeType_FuncDef(hoisted__FunctionDef_3498);
        (void)hoisted__NodeType_3499;
        { NodeType * _ret_val = hoisted__NodeType_3499;
                return _ret_val; }
    }
    Bool hoisted__Bool_3523 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3523;
    if (hoisted__Bool_3523) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3500 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3500;
        NodeType *hoisted__NodeType_3501 = NodeType_StructDef(hoisted__StructDef_3500);
        (void)hoisted__NodeType_3501;
        { NodeType * _ret_val = hoisted__NodeType_3501;
                return _ret_val; }
    }
    Bool hoisted__Bool_3524 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3524;
    if (hoisted__Bool_3524) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3502 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3502;
        NodeType *hoisted__NodeType_3503 = NodeType_EnumDef(hoisted__EnumDef_3502);
        (void)hoisted__NodeType_3503;
        { NodeType * _ret_val = hoisted__NodeType_3503;
                return _ret_val; }
    }
    Bool hoisted__Bool_3525 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3525;
    if (hoisted__Bool_3525) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3504 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3504;
        NodeType *hoisted__NodeType_3505 = NodeType_FieldAccess(hoisted__FieldAccessData_3504);
        (void)hoisted__NodeType_3505;
        { NodeType * _ret_val = hoisted__NodeType_3505;
                return _ret_val; }
    }
    Bool hoisted__Bool_3526 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3526;
    if (hoisted__Bool_3526) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3506 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3506;
        NodeType *hoisted__NodeType_3507 = NodeType_FieldAssign(hoisted__FieldAssignData_3506);
        (void)hoisted__NodeType_3507;
        { NodeType * _ret_val = hoisted__NodeType_3507;
                return _ret_val; }
    }
    Bool hoisted__Bool_3527 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3527;
    if (hoisted__Bool_3527) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3528 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3528;
    if (hoisted__Bool_3528) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3529 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3529;
    if (hoisted__Bool_3529) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3530 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3530;
    if (hoisted__Bool_3530) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3508 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3508;
        NodeType *hoisted__NodeType_3509 = NodeType_ForIn(hoisted__ForInData_3508);
        (void)hoisted__NodeType_3509;
        { NodeType * _ret_val = hoisted__NodeType_3509;
                return _ret_val; }
    }
    Bool hoisted__Bool_3531 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3531;
    if (hoisted__Bool_3531) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3510 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3510;
        NodeType *hoisted__NodeType_3511 = NodeType_NamedArg(hoisted__Str_3510);
        (void)hoisted__NodeType_3511;
        { NodeType * _ret_val = hoisted__NodeType_3511;
                return _ret_val; }
    }
    Bool hoisted__Bool_3532 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3532;
    if (hoisted__Bool_3532) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3533 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3533;
    if (hoisted__Bool_3533) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3534 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3534;
    if (hoisted__Bool_3534) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3535 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3535;
    if (hoisted__Bool_3535) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3512 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3512;
        NodeType *hoisted__NodeType_3513 = NodeType_Match(hoisted__MatchData_3512);
        (void)hoisted__NodeType_3513;
        { NodeType * _ret_val = hoisted__NodeType_3513;
                return _ret_val; }
    }
    Bool hoisted__Bool_3536 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3536;
    if (hoisted__Bool_3536) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3537 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3537;
    if (hoisted__Bool_3537) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3538 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3538;
    if (hoisted__Bool_3538) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3539 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3539;
    if (hoisted__Bool_3539) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3540 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3540;
    if (hoisted__Bool_3540) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3541 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3541;
    if (hoisted__Bool_3541) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3514 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3514;
        NodeType *hoisted__NodeType_3515 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3514);
        (void)hoisted__NodeType_3515;
        { NodeType * _ret_val = hoisted__NodeType_3515;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3542 = 112;
    (void)hoisted__U32_3542;
    return hoisted__U32_3542;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3543 = is_null(self);
    (void)hoisted__Bool_3543;
    if (hoisted__Bool_3543) {
        return;
    }
    Bool hoisted__Bool_3544 = 0;
    (void)hoisted__Bool_3544;
    NodeType_delete(&self->node_type, hoisted__Bool_3544);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3597 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3597->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3597->children = *_ca; free(_ca); }
    hoisted__Expr_3597->line = line;
    hoisted__Expr_3597->col = col;
    (void)hoisted__Expr_3597;
    return hoisted__Expr_3597;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3606 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3606->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3606->children = *_ca; free(_ca); }
    hoisted__Expr_3606->line = self->line;
    hoisted__Expr_3606->col = self->col;
    (void)hoisted__Expr_3606;
    return hoisted__Expr_3606;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3607 = 0;
    (void)hoisted__U32_3607;
    U64 hoisted__U64_3608 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3607); });
    (void)hoisted__U64_3608;
    return hoisted__U64_3608;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3609 = 136;
    (void)hoisted__U32_3609;
    return hoisted__U32_3609;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4345 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4345->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4345->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4345;
    return hoisted__Map__I64_Str_4345;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4492 = 0;
    (void)hoisted__Bool_4492;
    Vec__I64_delete(&self->keys, hoisted__Bool_4492);
    Bool hoisted__Bool_4493 = 0;
    (void)hoisted__Bool_4493;
    Vec__Str_delete(&self->values, hoisted__Bool_4493);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4494 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4494->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4494->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4494;
    return hoisted__Map__I64_Str_4494;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4495 = 0;
    (void)hoisted__U32_4495;
    U64 hoisted__U64_4496 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4495); });
    (void)hoisted__U64_4496;
    return hoisted__U64_4496;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4497 = 32;
    (void)hoisted__U32_4497;
    return hoisted__U32_4497;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4498 = 1;
    (void)hoisted__U32_4498;
    Type *hoisted__Type_4499 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4499;
    U64 hoisted__U64_4500 = (U64)(hoisted__U32_4498);
    (void)hoisted__U64_4500;
    Type_delete(hoisted__Type_4499, 1);
    void * hoisted__v_4501 = malloc(hoisted__U64_4500);
    (void)hoisted__v_4501;
    U32 hoisted__U32_4502 = 0;
    (void)hoisted__U32_4502;
    I64 hoisted__I64_4503 = 1;
    (void)hoisted__I64_4503;
    Vec__Bool *hoisted__Vec__Bool_4504 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4504->data = hoisted__v_4501;
    hoisted__Vec__Bool_4504->count = hoisted__U32_4502;
    hoisted__Vec__Bool_4504->cap = hoisted__I64_4503;
    (void)hoisted__Vec__Bool_4504;
    return hoisted__Vec__Bool_4504;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4505 = self->count;
        (void)_re_U32_4505;
        U32 _rc_U32_4505 = 0;
        (void)_rc_U32_4505;
        Bool hoisted__Bool_4520 = U32_lte(_rc_U32_4505, _re_U32_4505);
        (void)hoisted__Bool_4520;
        if (hoisted__Bool_4520) {
            while (1) {
                Bool _wcond_Bool_4506 = U32_lt(_rc_U32_4505, _re_U32_4505);
                (void)_wcond_Bool_4506;
                if (_wcond_Bool_4506) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4505);
                U32_inc(&_rc_U32_4505);
                U32 hoisted__U32_4507 = 1;
                (void)hoisted__U32_4507;
                U32 hoisted__U32_4508 = U32_mul(i, hoisted__U32_4507);
                (void)hoisted__U32_4508;
                Type *hoisted__Type_4509 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4509;
                U64 hoisted__U64_4510 = (U64)(hoisted__U32_4508);
                (void)hoisted__U64_4510;
                Type_delete(hoisted__Type_4509, 1);
                Bool *hoisted__Bool_4511 = ptr_add(self->data, hoisted__U64_4510);
                (void)hoisted__Bool_4511;
                (void)hoisted__Bool_4511;
                Bool hoisted__Bool_4512 = 0;
                (void)hoisted__Bool_4512;
                Bool_delete(hoisted__Bool_4511, hoisted__Bool_4512);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4513 = U32_gt(_rc_U32_4505, _re_U32_4505);
                (void)_wcond_Bool_4513;
                if (_wcond_Bool_4513) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4505);
                U32_dec(&_rc_U32_4505);
                U32 hoisted__U32_4514 = 1;
                (void)hoisted__U32_4514;
                U32 hoisted__U32_4515 = U32_mul(i, hoisted__U32_4514);
                (void)hoisted__U32_4515;
                Type *hoisted__Type_4516 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4516;
                U64 hoisted__U64_4517 = (U64)(hoisted__U32_4515);
                (void)hoisted__U64_4517;
                Type_delete(hoisted__Type_4516, 1);
                Bool *hoisted__Bool_4518 = ptr_add(self->data, hoisted__U64_4517);
                (void)hoisted__Bool_4518;
                (void)hoisted__Bool_4518;
                Bool hoisted__Bool_4519 = 0;
                (void)hoisted__Bool_4519;
                Bool_delete(hoisted__Bool_4518, hoisted__Bool_4519);
            }
        }
    }
    U32 hoisted__U32_4521 = 0;
    (void)hoisted__U32_4521;
    self->count = hoisted__U32_4521;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4837 = 1;
    (void)hoisted__U32_4837;
    U32 hoisted__U32_4838 = U32_mul(self->cap, hoisted__U32_4837);
    (void)hoisted__U32_4838;
    Type *hoisted__Type_4839 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4839;
    U64 hoisted__U64_4840 = (U64)(hoisted__U32_4838);
    (void)hoisted__U64_4840;
    Type_delete(hoisted__Type_4839, 1);
    void * new_data = malloc(hoisted__U64_4840);
    {
        U32 _re_U32_4801 = self->count;
        (void)_re_U32_4801;
        U32 _rc_U32_4801 = 0;
        (void)_rc_U32_4801;
        Bool hoisted__Bool_4836 = U32_lte(_rc_U32_4801, _re_U32_4801);
        (void)hoisted__Bool_4836;
        if (hoisted__Bool_4836) {
            while (1) {
                Bool _wcond_Bool_4802 = U32_lt(_rc_U32_4801, _re_U32_4801);
                (void)_wcond_Bool_4802;
                if (_wcond_Bool_4802) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4801);
                U32_inc(&_rc_U32_4801);
                U32 hoisted__U32_4803 = 1;
                (void)hoisted__U32_4803;
                U32 hoisted__U32_4804 = U32_mul(i, hoisted__U32_4803);
                (void)hoisted__U32_4804;
                Type *hoisted__Type_4805 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4805;
                U64 hoisted__U64_4806 = (U64)(hoisted__U32_4804);
                (void)hoisted__U64_4806;
                Type_delete(hoisted__Type_4805, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4806);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4807 = 1;
                (void)hoisted__U32_4807;
                U32 hoisted__U32_4808 = U32_mul(i, hoisted__U32_4807);
                (void)hoisted__U32_4808;
                Type *hoisted__Type_4809 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4809;
                U64 hoisted__U64_4810 = (U64)(hoisted__U32_4808);
                (void)hoisted__U64_4810;
                Type_delete(hoisted__Type_4809, 1);
                U32 hoisted__U32_4811 = 1;
                (void)hoisted__U32_4811;
                Type *hoisted__Type_4812 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4812;
                void *hoisted__v_4813 = ptr_add(new_data, hoisted__U64_4810);
                (void)hoisted__v_4813;
                (void)hoisted__v_4813;
                U64 hoisted__U64_4814 = (U64)(hoisted__U32_4811);
                (void)hoisted__U64_4814;
                Type_delete(hoisted__Type_4812, 1);
                memcpy(hoisted__v_4813, &cloned, hoisted__U64_4814);
                U32 hoisted__U32_4815 = 1;
                (void)hoisted__U32_4815;
                Type *hoisted__Type_4816 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4816;
                I32 hoisted__I32_4817 = 0;
                (void)hoisted__I32_4817;
                U64 hoisted__U64_4818 = (U64)(hoisted__U32_4815);
                (void)hoisted__U64_4818;
                Type_delete(hoisted__Type_4816, 1);
                memset(&cloned, hoisted__I32_4817, hoisted__U64_4818);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4819 = U32_gt(_rc_U32_4801, _re_U32_4801);
                (void)_wcond_Bool_4819;
                if (_wcond_Bool_4819) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4801);
                U32_dec(&_rc_U32_4801);
                U32 hoisted__U32_4820 = 1;
                (void)hoisted__U32_4820;
                U32 hoisted__U32_4821 = U32_mul(i, hoisted__U32_4820);
                (void)hoisted__U32_4821;
                Type *hoisted__Type_4822 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4822;
                U64 hoisted__U64_4823 = (U64)(hoisted__U32_4821);
                (void)hoisted__U64_4823;
                Type_delete(hoisted__Type_4822, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4823);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4824 = 1;
                (void)hoisted__U32_4824;
                U32 hoisted__U32_4825 = U32_mul(i, hoisted__U32_4824);
                (void)hoisted__U32_4825;
                Type *hoisted__Type_4826 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4826;
                U64 hoisted__U64_4827 = (U64)(hoisted__U32_4825);
                (void)hoisted__U64_4827;
                Type_delete(hoisted__Type_4826, 1);
                U32 hoisted__U32_4828 = 1;
                (void)hoisted__U32_4828;
                Type *hoisted__Type_4829 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4829;
                void *hoisted__v_4830 = ptr_add(new_data, hoisted__U64_4827);
                (void)hoisted__v_4830;
                (void)hoisted__v_4830;
                U64 hoisted__U64_4831 = (U64)(hoisted__U32_4828);
                (void)hoisted__U64_4831;
                Type_delete(hoisted__Type_4829, 1);
                memcpy(hoisted__v_4830, &cloned, hoisted__U64_4831);
                U32 hoisted__U32_4832 = 1;
                (void)hoisted__U32_4832;
                Type *hoisted__Type_4833 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4833;
                I32 hoisted__I32_4834 = 0;
                (void)hoisted__I32_4834;
                U64 hoisted__U64_4835 = (U64)(hoisted__U32_4832);
                (void)hoisted__U64_4835;
                Type_delete(hoisted__Type_4833, 1);
                memset(&cloned, hoisted__I32_4834, hoisted__U64_4835);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4841 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4841->data = new_data;
    hoisted__Vec__Bool_4841->count = self->count;
    hoisted__Vec__Bool_4841->cap = self->cap;
    (void)hoisted__Vec__Bool_4841;
    return hoisted__Vec__Bool_4841;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4842 = 16;
    (void)hoisted__U32_4842;
    return hoisted__U32_4842;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5188 = 104;
    (void)hoisted__U32_5188;
    Type *hoisted__Type_5189 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5189;
    U64 hoisted__U64_5190 = (U64)(hoisted__U32_5188);
    (void)hoisted__U64_5190;
    Type_delete(hoisted__Type_5189, 1);
    void * hoisted__v_5191 = malloc(hoisted__U64_5190);
    (void)hoisted__v_5191;
    U32 hoisted__U32_5192 = 0;
    (void)hoisted__U32_5192;
    I64 hoisted__I64_5193 = 1;
    (void)hoisted__I64_5193;
    Vec__Declaration *hoisted__Vec__Declaration_5194 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5194->data = hoisted__v_5191;
    hoisted__Vec__Declaration_5194->count = hoisted__U32_5192;
    hoisted__Vec__Declaration_5194->cap = hoisted__I64_5193;
    (void)hoisted__Vec__Declaration_5194;
    return hoisted__Vec__Declaration_5194;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5195 = self->count;
        (void)_re_U32_5195;
        U32 _rc_U32_5195 = 0;
        (void)_rc_U32_5195;
        Bool hoisted__Bool_5210 = U32_lte(_rc_U32_5195, _re_U32_5195);
        (void)hoisted__Bool_5210;
        if (hoisted__Bool_5210) {
            while (1) {
                Bool _wcond_Bool_5196 = U32_lt(_rc_U32_5195, _re_U32_5195);
                (void)_wcond_Bool_5196;
                if (_wcond_Bool_5196) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5195);
                U32_inc(&_rc_U32_5195);
                U32 hoisted__U32_5197 = 104;
                (void)hoisted__U32_5197;
                U32 hoisted__U32_5198 = U32_mul(i, hoisted__U32_5197);
                (void)hoisted__U32_5198;
                Type *hoisted__Type_5199 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5199;
                U64 hoisted__U64_5200 = (U64)(hoisted__U32_5198);
                (void)hoisted__U64_5200;
                Type_delete(hoisted__Type_5199, 1);
                Declaration *hoisted__Declaration_5201 = ptr_add(self->data, hoisted__U64_5200);
                (void)hoisted__Declaration_5201;
                (void)hoisted__Declaration_5201;
                Bool hoisted__Bool_5202 = 0;
                (void)hoisted__Bool_5202;
                Declaration_delete(hoisted__Declaration_5201, hoisted__Bool_5202);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5203 = U32_gt(_rc_U32_5195, _re_U32_5195);
                (void)_wcond_Bool_5203;
                if (_wcond_Bool_5203) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5195);
                U32_dec(&_rc_U32_5195);
                U32 hoisted__U32_5204 = 104;
                (void)hoisted__U32_5204;
                U32 hoisted__U32_5205 = U32_mul(i, hoisted__U32_5204);
                (void)hoisted__U32_5205;
                Type *hoisted__Type_5206 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5206;
                U64 hoisted__U64_5207 = (U64)(hoisted__U32_5205);
                (void)hoisted__U64_5207;
                Type_delete(hoisted__Type_5206, 1);
                Declaration *hoisted__Declaration_5208 = ptr_add(self->data, hoisted__U64_5207);
                (void)hoisted__Declaration_5208;
                (void)hoisted__Declaration_5208;
                Bool hoisted__Bool_5209 = 0;
                (void)hoisted__Bool_5209;
                Declaration_delete(hoisted__Declaration_5208, hoisted__Bool_5209);
            }
        }
    }
    U32 hoisted__U32_5211 = 0;
    (void)hoisted__U32_5211;
    self->count = hoisted__U32_5211;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5527 = 104;
    (void)hoisted__U32_5527;
    U32 hoisted__U32_5528 = U32_mul(self->cap, hoisted__U32_5527);
    (void)hoisted__U32_5528;
    Type *hoisted__Type_5529 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5529;
    U64 hoisted__U64_5530 = (U64)(hoisted__U32_5528);
    (void)hoisted__U64_5530;
    Type_delete(hoisted__Type_5529, 1);
    void * new_data = malloc(hoisted__U64_5530);
    {
        U32 _re_U32_5491 = self->count;
        (void)_re_U32_5491;
        U32 _rc_U32_5491 = 0;
        (void)_rc_U32_5491;
        Bool hoisted__Bool_5526 = U32_lte(_rc_U32_5491, _re_U32_5491);
        (void)hoisted__Bool_5526;
        if (hoisted__Bool_5526) {
            while (1) {
                Bool _wcond_Bool_5492 = U32_lt(_rc_U32_5491, _re_U32_5491);
                (void)_wcond_Bool_5492;
                if (_wcond_Bool_5492) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5491);
                U32_inc(&_rc_U32_5491);
                U32 hoisted__U32_5493 = 104;
                (void)hoisted__U32_5493;
                U32 hoisted__U32_5494 = U32_mul(i, hoisted__U32_5493);
                (void)hoisted__U32_5494;
                Type *hoisted__Type_5495 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5495;
                U64 hoisted__U64_5496 = (U64)(hoisted__U32_5494);
                (void)hoisted__U64_5496;
                Type_delete(hoisted__Type_5495, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5496);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5497 = 104;
                (void)hoisted__U32_5497;
                U32 hoisted__U32_5498 = U32_mul(i, hoisted__U32_5497);
                (void)hoisted__U32_5498;
                Type *hoisted__Type_5499 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5499;
                U64 hoisted__U64_5500 = (U64)(hoisted__U32_5498);
                (void)hoisted__U64_5500;
                Type_delete(hoisted__Type_5499, 1);
                U32 hoisted__U32_5501 = 104;
                (void)hoisted__U32_5501;
                Type *hoisted__Type_5502 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5502;
                void *hoisted__v_5503 = ptr_add(new_data, hoisted__U64_5500);
                (void)hoisted__v_5503;
                (void)hoisted__v_5503;
                U64 hoisted__U64_5504 = (U64)(hoisted__U32_5501);
                (void)hoisted__U64_5504;
                Type_delete(hoisted__Type_5502, 1);
                memcpy(hoisted__v_5503, cloned, hoisted__U64_5504);
                U32 hoisted__U32_5505 = 104;
                (void)hoisted__U32_5505;
                Type *hoisted__Type_5506 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5506;
                I32 hoisted__I32_5507 = 0;
                (void)hoisted__I32_5507;
                U64 hoisted__U64_5508 = (U64)(hoisted__U32_5505);
                (void)hoisted__U64_5508;
                Type_delete(hoisted__Type_5506, 1);
                memset(cloned, hoisted__I32_5507, hoisted__U64_5508);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5509 = U32_gt(_rc_U32_5491, _re_U32_5491);
                (void)_wcond_Bool_5509;
                if (_wcond_Bool_5509) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5491);
                U32_dec(&_rc_U32_5491);
                U32 hoisted__U32_5510 = 104;
                (void)hoisted__U32_5510;
                U32 hoisted__U32_5511 = U32_mul(i, hoisted__U32_5510);
                (void)hoisted__U32_5511;
                Type *hoisted__Type_5512 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5512;
                U64 hoisted__U64_5513 = (U64)(hoisted__U32_5511);
                (void)hoisted__U64_5513;
                Type_delete(hoisted__Type_5512, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5513);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5514 = 104;
                (void)hoisted__U32_5514;
                U32 hoisted__U32_5515 = U32_mul(i, hoisted__U32_5514);
                (void)hoisted__U32_5515;
                Type *hoisted__Type_5516 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5516;
                U64 hoisted__U64_5517 = (U64)(hoisted__U32_5515);
                (void)hoisted__U64_5517;
                Type_delete(hoisted__Type_5516, 1);
                U32 hoisted__U32_5518 = 104;
                (void)hoisted__U32_5518;
                Type *hoisted__Type_5519 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5519;
                void *hoisted__v_5520 = ptr_add(new_data, hoisted__U64_5517);
                (void)hoisted__v_5520;
                (void)hoisted__v_5520;
                U64 hoisted__U64_5521 = (U64)(hoisted__U32_5518);
                (void)hoisted__U64_5521;
                Type_delete(hoisted__Type_5519, 1);
                memcpy(hoisted__v_5520, cloned, hoisted__U64_5521);
                U32 hoisted__U32_5522 = 104;
                (void)hoisted__U32_5522;
                Type *hoisted__Type_5523 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5523;
                I32 hoisted__I32_5524 = 0;
                (void)hoisted__I32_5524;
                U64 hoisted__U64_5525 = (U64)(hoisted__U32_5522);
                (void)hoisted__U64_5525;
                Type_delete(hoisted__Type_5523, 1);
                memset(cloned, hoisted__I32_5524, hoisted__U64_5525);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5531 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5531->data = new_data;
    hoisted__Vec__Declaration_5531->count = self->count;
    hoisted__Vec__Declaration_5531->cap = self->cap;
    (void)hoisted__Vec__Declaration_5531;
    return hoisted__Vec__Declaration_5531;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5532 = 16;
    (void)hoisted__U32_5532;
    return hoisted__U32_5532;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5533 = 136;
    (void)hoisted__U32_5533;
    Type *hoisted__Type_5534 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5534;
    U64 hoisted__U64_5535 = (U64)(hoisted__U32_5533);
    (void)hoisted__U64_5535;
    Type_delete(hoisted__Type_5534, 1);
    void * hoisted__v_5536 = malloc(hoisted__U64_5535);
    (void)hoisted__v_5536;
    U32 hoisted__U32_5537 = 0;
    (void)hoisted__U32_5537;
    I64 hoisted__I64_5538 = 1;
    (void)hoisted__I64_5538;
    Vec__Expr *hoisted__Vec__Expr_5539 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5539->data = hoisted__v_5536;
    hoisted__Vec__Expr_5539->count = hoisted__U32_5537;
    hoisted__Vec__Expr_5539->cap = hoisted__I64_5538;
    (void)hoisted__Vec__Expr_5539;
    return hoisted__Vec__Expr_5539;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5540 = self->count;
        (void)_re_U32_5540;
        U32 _rc_U32_5540 = 0;
        (void)_rc_U32_5540;
        Bool hoisted__Bool_5555 = U32_lte(_rc_U32_5540, _re_U32_5540);
        (void)hoisted__Bool_5555;
        if (hoisted__Bool_5555) {
            while (1) {
                Bool _wcond_Bool_5541 = U32_lt(_rc_U32_5540, _re_U32_5540);
                (void)_wcond_Bool_5541;
                if (_wcond_Bool_5541) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5540);
                U32_inc(&_rc_U32_5540);
                U32 hoisted__U32_5542 = 136;
                (void)hoisted__U32_5542;
                U32 hoisted__U32_5543 = U32_mul(i, hoisted__U32_5542);
                (void)hoisted__U32_5543;
                Type *hoisted__Type_5544 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5544;
                U64 hoisted__U64_5545 = (U64)(hoisted__U32_5543);
                (void)hoisted__U64_5545;
                Type_delete(hoisted__Type_5544, 1);
                Expr *hoisted__Expr_5546 = ptr_add(self->data, hoisted__U64_5545);
                (void)hoisted__Expr_5546;
                (void)hoisted__Expr_5546;
                Bool hoisted__Bool_5547 = 0;
                (void)hoisted__Bool_5547;
                Expr_delete(hoisted__Expr_5546, hoisted__Bool_5547);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5548 = U32_gt(_rc_U32_5540, _re_U32_5540);
                (void)_wcond_Bool_5548;
                if (_wcond_Bool_5548) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5540);
                U32_dec(&_rc_U32_5540);
                U32 hoisted__U32_5549 = 136;
                (void)hoisted__U32_5549;
                U32 hoisted__U32_5550 = U32_mul(i, hoisted__U32_5549);
                (void)hoisted__U32_5550;
                Type *hoisted__Type_5551 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5551;
                U64 hoisted__U64_5552 = (U64)(hoisted__U32_5550);
                (void)hoisted__U64_5552;
                Type_delete(hoisted__Type_5551, 1);
                Expr *hoisted__Expr_5553 = ptr_add(self->data, hoisted__U64_5552);
                (void)hoisted__Expr_5553;
                (void)hoisted__Expr_5553;
                Bool hoisted__Bool_5554 = 0;
                (void)hoisted__Bool_5554;
                Expr_delete(hoisted__Expr_5553, hoisted__Bool_5554);
            }
        }
    }
    U32 hoisted__U32_5556 = 0;
    (void)hoisted__U32_5556;
    self->count = hoisted__U32_5556;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5872 = 136;
    (void)hoisted__U32_5872;
    U32 hoisted__U32_5873 = U32_mul(self->cap, hoisted__U32_5872);
    (void)hoisted__U32_5873;
    Type *hoisted__Type_5874 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5874;
    U64 hoisted__U64_5875 = (U64)(hoisted__U32_5873);
    (void)hoisted__U64_5875;
    Type_delete(hoisted__Type_5874, 1);
    void * new_data = malloc(hoisted__U64_5875);
    {
        U32 _re_U32_5836 = self->count;
        (void)_re_U32_5836;
        U32 _rc_U32_5836 = 0;
        (void)_rc_U32_5836;
        Bool hoisted__Bool_5871 = U32_lte(_rc_U32_5836, _re_U32_5836);
        (void)hoisted__Bool_5871;
        if (hoisted__Bool_5871) {
            while (1) {
                Bool _wcond_Bool_5837 = U32_lt(_rc_U32_5836, _re_U32_5836);
                (void)_wcond_Bool_5837;
                if (_wcond_Bool_5837) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5836);
                U32_inc(&_rc_U32_5836);
                U32 hoisted__U32_5838 = 136;
                (void)hoisted__U32_5838;
                U32 hoisted__U32_5839 = U32_mul(i, hoisted__U32_5838);
                (void)hoisted__U32_5839;
                Type *hoisted__Type_5840 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5840;
                U64 hoisted__U64_5841 = (U64)(hoisted__U32_5839);
                (void)hoisted__U64_5841;
                Type_delete(hoisted__Type_5840, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5841);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5842 = 136;
                (void)hoisted__U32_5842;
                U32 hoisted__U32_5843 = U32_mul(i, hoisted__U32_5842);
                (void)hoisted__U32_5843;
                Type *hoisted__Type_5844 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5844;
                U64 hoisted__U64_5845 = (U64)(hoisted__U32_5843);
                (void)hoisted__U64_5845;
                Type_delete(hoisted__Type_5844, 1);
                U32 hoisted__U32_5846 = 136;
                (void)hoisted__U32_5846;
                Type *hoisted__Type_5847 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5847;
                void *hoisted__v_5848 = ptr_add(new_data, hoisted__U64_5845);
                (void)hoisted__v_5848;
                (void)hoisted__v_5848;
                U64 hoisted__U64_5849 = (U64)(hoisted__U32_5846);
                (void)hoisted__U64_5849;
                Type_delete(hoisted__Type_5847, 1);
                memcpy(hoisted__v_5848, cloned, hoisted__U64_5849);
                U32 hoisted__U32_5850 = 136;
                (void)hoisted__U32_5850;
                Type *hoisted__Type_5851 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5851;
                I32 hoisted__I32_5852 = 0;
                (void)hoisted__I32_5852;
                U64 hoisted__U64_5853 = (U64)(hoisted__U32_5850);
                (void)hoisted__U64_5853;
                Type_delete(hoisted__Type_5851, 1);
                memset(cloned, hoisted__I32_5852, hoisted__U64_5853);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5854 = U32_gt(_rc_U32_5836, _re_U32_5836);
                (void)_wcond_Bool_5854;
                if (_wcond_Bool_5854) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5836);
                U32_dec(&_rc_U32_5836);
                U32 hoisted__U32_5855 = 136;
                (void)hoisted__U32_5855;
                U32 hoisted__U32_5856 = U32_mul(i, hoisted__U32_5855);
                (void)hoisted__U32_5856;
                Type *hoisted__Type_5857 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5857;
                U64 hoisted__U64_5858 = (U64)(hoisted__U32_5856);
                (void)hoisted__U64_5858;
                Type_delete(hoisted__Type_5857, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5858);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5859 = 136;
                (void)hoisted__U32_5859;
                U32 hoisted__U32_5860 = U32_mul(i, hoisted__U32_5859);
                (void)hoisted__U32_5860;
                Type *hoisted__Type_5861 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5861;
                U64 hoisted__U64_5862 = (U64)(hoisted__U32_5860);
                (void)hoisted__U64_5862;
                Type_delete(hoisted__Type_5861, 1);
                U32 hoisted__U32_5863 = 136;
                (void)hoisted__U32_5863;
                Type *hoisted__Type_5864 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5864;
                void *hoisted__v_5865 = ptr_add(new_data, hoisted__U64_5862);
                (void)hoisted__v_5865;
                (void)hoisted__v_5865;
                U64 hoisted__U64_5866 = (U64)(hoisted__U32_5863);
                (void)hoisted__U64_5866;
                Type_delete(hoisted__Type_5864, 1);
                memcpy(hoisted__v_5865, cloned, hoisted__U64_5866);
                U32 hoisted__U32_5867 = 136;
                (void)hoisted__U32_5867;
                Type *hoisted__Type_5868 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5868;
                I32 hoisted__I32_5869 = 0;
                (void)hoisted__I32_5869;
                U64 hoisted__U64_5870 = (U64)(hoisted__U32_5867);
                (void)hoisted__U64_5870;
                Type_delete(hoisted__Type_5868, 1);
                memset(cloned, hoisted__I32_5869, hoisted__U64_5870);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5876 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5876->data = new_data;
    hoisted__Vec__Expr_5876->count = self->count;
    hoisted__Vec__Expr_5876->cap = self->cap;
    (void)hoisted__Vec__Expr_5876;
    return hoisted__Vec__Expr_5876;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5877 = 16;
    (void)hoisted__U32_5877;
    return hoisted__U32_5877;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5878 = 8;
    (void)hoisted__U32_5878;
    Type *hoisted__Type_5879 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5879;
    U64 hoisted__U64_5880 = (U64)(hoisted__U32_5878);
    (void)hoisted__U64_5880;
    Type_delete(hoisted__Type_5879, 1);
    void * hoisted__v_5881 = malloc(hoisted__U64_5880);
    (void)hoisted__v_5881;
    U32 hoisted__U32_5882 = 0;
    (void)hoisted__U32_5882;
    I64 hoisted__I64_5883 = 1;
    (void)hoisted__I64_5883;
    Vec__I64 *hoisted__Vec__I64_5884 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5884->data = hoisted__v_5881;
    hoisted__Vec__I64_5884->count = hoisted__U32_5882;
    hoisted__Vec__I64_5884->cap = hoisted__I64_5883;
    (void)hoisted__Vec__I64_5884;
    return hoisted__Vec__I64_5884;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5885 = self->count;
        (void)_re_U32_5885;
        U32 _rc_U32_5885 = 0;
        (void)_rc_U32_5885;
        Bool hoisted__Bool_5900 = U32_lte(_rc_U32_5885, _re_U32_5885);
        (void)hoisted__Bool_5900;
        if (hoisted__Bool_5900) {
            while (1) {
                Bool _wcond_Bool_5886 = U32_lt(_rc_U32_5885, _re_U32_5885);
                (void)_wcond_Bool_5886;
                if (_wcond_Bool_5886) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5885);
                U32_inc(&_rc_U32_5885);
                U32 hoisted__U32_5887 = 8;
                (void)hoisted__U32_5887;
                U32 hoisted__U32_5888 = U32_mul(i, hoisted__U32_5887);
                (void)hoisted__U32_5888;
                Type *hoisted__Type_5889 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5889;
                U64 hoisted__U64_5890 = (U64)(hoisted__U32_5888);
                (void)hoisted__U64_5890;
                Type_delete(hoisted__Type_5889, 1);
                I64 *hoisted__I64_5891 = ptr_add(self->data, hoisted__U64_5890);
                (void)hoisted__I64_5891;
                (void)hoisted__I64_5891;
                Bool hoisted__Bool_5892 = 0;
                (void)hoisted__Bool_5892;
                I64_delete(hoisted__I64_5891, hoisted__Bool_5892);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5893 = U32_gt(_rc_U32_5885, _re_U32_5885);
                (void)_wcond_Bool_5893;
                if (_wcond_Bool_5893) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5885);
                U32_dec(&_rc_U32_5885);
                U32 hoisted__U32_5894 = 8;
                (void)hoisted__U32_5894;
                U32 hoisted__U32_5895 = U32_mul(i, hoisted__U32_5894);
                (void)hoisted__U32_5895;
                Type *hoisted__Type_5896 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5896;
                U64 hoisted__U64_5897 = (U64)(hoisted__U32_5895);
                (void)hoisted__U64_5897;
                Type_delete(hoisted__Type_5896, 1);
                I64 *hoisted__I64_5898 = ptr_add(self->data, hoisted__U64_5897);
                (void)hoisted__I64_5898;
                (void)hoisted__I64_5898;
                Bool hoisted__Bool_5899 = 0;
                (void)hoisted__Bool_5899;
                I64_delete(hoisted__I64_5898, hoisted__Bool_5899);
            }
        }
    }
    U32 hoisted__U32_5901 = 0;
    (void)hoisted__U32_5901;
    self->count = hoisted__U32_5901;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_6217 = 8;
    (void)hoisted__U32_6217;
    U32 hoisted__U32_6218 = U32_mul(self->cap, hoisted__U32_6217);
    (void)hoisted__U32_6218;
    Type *hoisted__Type_6219 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_6219;
    U64 hoisted__U64_6220 = (U64)(hoisted__U32_6218);
    (void)hoisted__U64_6220;
    Type_delete(hoisted__Type_6219, 1);
    void * new_data = malloc(hoisted__U64_6220);
    {
        U32 _re_U32_6181 = self->count;
        (void)_re_U32_6181;
        U32 _rc_U32_6181 = 0;
        (void)_rc_U32_6181;
        Bool hoisted__Bool_6216 = U32_lte(_rc_U32_6181, _re_U32_6181);
        (void)hoisted__Bool_6216;
        if (hoisted__Bool_6216) {
            while (1) {
                Bool _wcond_Bool_6182 = U32_lt(_rc_U32_6181, _re_U32_6181);
                (void)_wcond_Bool_6182;
                if (_wcond_Bool_6182) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6181);
                U32_inc(&_rc_U32_6181);
                U32 hoisted__U32_6183 = 8;
                (void)hoisted__U32_6183;
                U32 hoisted__U32_6184 = U32_mul(i, hoisted__U32_6183);
                (void)hoisted__U32_6184;
                Type *hoisted__Type_6185 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6185;
                U64 hoisted__U64_6186 = (U64)(hoisted__U32_6184);
                (void)hoisted__U64_6186;
                Type_delete(hoisted__Type_6185, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6186);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6187 = 8;
                (void)hoisted__U32_6187;
                U32 hoisted__U32_6188 = U32_mul(i, hoisted__U32_6187);
                (void)hoisted__U32_6188;
                Type *hoisted__Type_6189 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6189;
                U64 hoisted__U64_6190 = (U64)(hoisted__U32_6188);
                (void)hoisted__U64_6190;
                Type_delete(hoisted__Type_6189, 1);
                U32 hoisted__U32_6191 = 8;
                (void)hoisted__U32_6191;
                Type *hoisted__Type_6192 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6192;
                void *hoisted__v_6193 = ptr_add(new_data, hoisted__U64_6190);
                (void)hoisted__v_6193;
                (void)hoisted__v_6193;
                U64 hoisted__U64_6194 = (U64)(hoisted__U32_6191);
                (void)hoisted__U64_6194;
                Type_delete(hoisted__Type_6192, 1);
                memcpy(hoisted__v_6193, &cloned, hoisted__U64_6194);
                U32 hoisted__U32_6195 = 8;
                (void)hoisted__U32_6195;
                Type *hoisted__Type_6196 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6196;
                I32 hoisted__I32_6197 = 0;
                (void)hoisted__I32_6197;
                U64 hoisted__U64_6198 = (U64)(hoisted__U32_6195);
                (void)hoisted__U64_6198;
                Type_delete(hoisted__Type_6196, 1);
                memset(&cloned, hoisted__I32_6197, hoisted__U64_6198);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6199 = U32_gt(_rc_U32_6181, _re_U32_6181);
                (void)_wcond_Bool_6199;
                if (_wcond_Bool_6199) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6181);
                U32_dec(&_rc_U32_6181);
                U32 hoisted__U32_6200 = 8;
                (void)hoisted__U32_6200;
                U32 hoisted__U32_6201 = U32_mul(i, hoisted__U32_6200);
                (void)hoisted__U32_6201;
                Type *hoisted__Type_6202 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6202;
                U64 hoisted__U64_6203 = (U64)(hoisted__U32_6201);
                (void)hoisted__U64_6203;
                Type_delete(hoisted__Type_6202, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6203);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6204 = 8;
                (void)hoisted__U32_6204;
                U32 hoisted__U32_6205 = U32_mul(i, hoisted__U32_6204);
                (void)hoisted__U32_6205;
                Type *hoisted__Type_6206 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6206;
                U64 hoisted__U64_6207 = (U64)(hoisted__U32_6205);
                (void)hoisted__U64_6207;
                Type_delete(hoisted__Type_6206, 1);
                U32 hoisted__U32_6208 = 8;
                (void)hoisted__U32_6208;
                Type *hoisted__Type_6209 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6209;
                void *hoisted__v_6210 = ptr_add(new_data, hoisted__U64_6207);
                (void)hoisted__v_6210;
                (void)hoisted__v_6210;
                U64 hoisted__U64_6211 = (U64)(hoisted__U32_6208);
                (void)hoisted__U64_6211;
                Type_delete(hoisted__Type_6209, 1);
                memcpy(hoisted__v_6210, &cloned, hoisted__U64_6211);
                U32 hoisted__U32_6212 = 8;
                (void)hoisted__U32_6212;
                Type *hoisted__Type_6213 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6213;
                I32 hoisted__I32_6214 = 0;
                (void)hoisted__I32_6214;
                U64 hoisted__U64_6215 = (U64)(hoisted__U32_6212);
                (void)hoisted__U64_6215;
                Type_delete(hoisted__Type_6213, 1);
                memset(&cloned, hoisted__I32_6214, hoisted__U64_6215);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6221 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6221->data = new_data;
    hoisted__Vec__I64_6221->count = self->count;
    hoisted__Vec__I64_6221->cap = self->cap;
    (void)hoisted__Vec__I64_6221;
    return hoisted__Vec__I64_6221;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_6222 = 16;
    (void)hoisted__U32_6222;
    return hoisted__U32_6222;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7457 = 3;
    (void)hoisted__U32_7457;
    Array__Str *_va_Array_193 = Array__Str_new(hoisted__U32_7457);
    (void)_va_Array_193;
    I64 _va_Array_193_ek = 0;
    (void)_va_Array_193_ek;
    OutOfBounds *_va_Array_193_eo = malloc(sizeof(OutOfBounds));
    _va_Array_193_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_193_eo;
    U32 hoisted__U32_7458 = 0;
    (void)hoisted__U32_7458;
    Str *hoisted__Str_7459 = Str_clone(loc);
    (void)hoisted__Str_7459;
    static Str hoisted__Str_7460 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7460;
    Array__Str_set(_va_Array_193, hoisted__U32_7458, hoisted__Str_7459, &_va_Array_193_ek, _va_Array_193_eo, &hoisted__Str_7460);
    Str_delete(&hoisted__Str_7460, (Bool){0});
    U32 hoisted__U32_7461 = 1;
    (void)hoisted__U32_7461;
    static Str hoisted__Str_7462 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7462;
    static Str hoisted__Str_7463 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7463;
    Array__Str_set(_va_Array_193, hoisted__U32_7461, &hoisted__Str_7462, &_va_Array_193_ek, _va_Array_193_eo, &hoisted__Str_7463);
    Str_delete(&hoisted__Str_7463, (Bool){0});
    Array__Str *hoisted__Array__Str_7464 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7464;
    U32 hoisted__U32_7465 = 2;
    (void)hoisted__U32_7465;
    Str *hoisted__Str_7466 = format(hoisted__Array__Str_7464);
    (void)hoisted__Str_7466;
    static Str hoisted__Str_7467 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7467;
    Array__Str_set(_va_Array_193, hoisted__U32_7465, hoisted__Str_7466, &_va_Array_193_ek, _va_Array_193_eo, &hoisted__Str_7467);
    OutOfBounds_delete(_va_Array_193_eo, 1);
    Str_delete(&hoisted__Str_7467, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_193);
    I64 hoisted__I64_7468 = 1;
    (void)hoisted__I64_7468;
    exit(hoisted__I64_7468);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7477 = 1;
    (void)hoisted__U32_7477;
    Array__Str *_va_Array_195 = Array__Str_new(hoisted__U32_7477);
    (void)_va_Array_195;
    I64 _va_Array_195_ek = 0;
    (void)_va_Array_195_ek;
    OutOfBounds *_va_Array_195_eo = malloc(sizeof(OutOfBounds));
    _va_Array_195_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_195_eo;
    U32 hoisted__U32_7478 = 0;
    (void)hoisted__U32_7478;
    static Str hoisted__Str_7479 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7479;
    static Str hoisted__Str_7480 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7480;
    Array__Str_set(_va_Array_195, hoisted__U32_7478, &hoisted__Str_7479, &_va_Array_195_ek, _va_Array_195_eo, &hoisted__Str_7480);
    OutOfBounds_delete(_va_Array_195_eo, 1);
    Str_delete(&hoisted__Str_7480, (Bool){0});
    panic(_va_Array_195, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7485 = not(cond);
    (void)hoisted__Bool_7485;
    if (hoisted__Bool_7485) {
        U32 hoisted__U32_7481 = 1;
        (void)hoisted__U32_7481;
        Array__Str *_va_Array_196 = Array__Str_new(hoisted__U32_7481);
        (void)_va_Array_196;
        I64 _va_Array_196_ek = 0;
        (void)_va_Array_196_ek;
        OutOfBounds *_va_Array_196_eo = malloc(sizeof(OutOfBounds));
        _va_Array_196_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_196_eo;
        U32 hoisted__U32_7482 = 0;
        (void)hoisted__U32_7482;
        static Str hoisted__Str_7483 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7483;
        static Str hoisted__Str_7484 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7484;
        Array__Str_set(_va_Array_196, hoisted__U32_7482, &hoisted__Str_7483, &_va_Array_196_ek, _va_Array_196_eo, &hoisted__Str_7484);
        OutOfBounds_delete(_va_Array_196_eo, 1);
        Str_delete(&hoisted__Str_7484, (Bool){0});
        panic(_va_Array_196, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7495 = parts;
        (void)_fc_Array__Str_7495;
        (void)_fc_Array__Str_7495;
        U32 _fi_USize_7495 = 0;
        (void)_fi_USize_7495;
        I64 _forin_err_kind_7495 = 0;
        (void)_forin_err_kind_7495;
        OutOfBounds *_forin_OutOfBounds_7495 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_7495->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_7495;
        while (1) {
            U32 hoisted__U32_7505 = Array__Str_len(_fc_Array__Str_7495);
            (void)hoisted__U32_7505;
            Bool _wcond_Bool_7496 = U32_lt(_fi_USize_7495, hoisted__U32_7505);
            (void)_wcond_Bool_7496;
            if (_wcond_Bool_7496) {
            } else {
                break;
            }
            static Str hoisted__Str_7506 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
            (void)hoisted__Str_7506;
            Str *s = Array__Str_get(_fc_Array__Str_7495, &_fi_USize_7495, &_forin_err_kind_7495, _forin_OutOfBounds_7495, &hoisted__Str_7506);
            I64 hoisted__I64_7507 = 0;
            (void)hoisted__I64_7507;
            Bool hoisted__Bool_7508 = I64_eq(_forin_err_kind_7495, hoisted__I64_7507);
            (void)hoisted__Bool_7508;
            Bool hoisted__Bool_7509 = not(hoisted__Bool_7508);
            (void)hoisted__Bool_7509;
            if (hoisted__Bool_7509) {
                U32 hoisted__U32_7497 = 2;
                (void)hoisted__U32_7497;
                Array__Str *_va_Array_198 = Array__Str_new(hoisted__U32_7497);
                (void)_va_Array_198;
                I64 _va_Array_198_ek = 0;
                (void)_va_Array_198_ek;
                OutOfBounds *_va_Array_198_eo = malloc(sizeof(OutOfBounds));
                _va_Array_198_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_198_eo;
                U32 hoisted__U32_7498 = 0;
                (void)hoisted__U32_7498;
                static Str hoisted__Str_7499 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7499;
                static Str hoisted__Str_7500 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7500;
                Array__Str_set(_va_Array_198, hoisted__U32_7498, &hoisted__Str_7499, &_va_Array_198_ek, _va_Array_198_eo, &hoisted__Str_7500);
                Str_delete(&hoisted__Str_7500, (Bool){0});
                U32 hoisted__U32_7501 = 1;
                (void)hoisted__U32_7501;
                static Str hoisted__Str_7502 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7502;
                static Str hoisted__Str_7503 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7503;
                Array__Str_set(_va_Array_198, hoisted__U32_7501, &hoisted__Str_7502, &_va_Array_198_ek, _va_Array_198_eo, &hoisted__Str_7503);
                OutOfBounds_delete(_va_Array_198_eo, 1);
                Str_delete(&hoisted__Str_7503, (Bool){0});
                static Str hoisted__Str_7504 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_7504;
                panic(_va_Array_198, &hoisted__Str_7504);
                Str_delete(&hoisted__Str_7504, (Bool){0});
            }
            U32 hoisted__U32_7510 = 1;
            (void)hoisted__U32_7510;
            U32 hoisted__U32_7511 = U32_add(_fi_USize_7495, hoisted__U32_7510);
            (void)hoisted__U32_7511;
            _fi_USize_7495 = hoisted__U32_7511;
            print_single(s);
            Str_delete(&hoisted__Str_7506, (Bool){0});
        }
        OutOfBounds_delete(_forin_OutOfBounds_7495, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7557 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7557;
    return hoisted__Bool_7557;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7566 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7566;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7566;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7567 = 0;
    (void)hoisted__U32_7567;
    U64 hoisted__U64_7568 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7567); });
    (void)hoisted__U64_7568;
    return hoisted__U64_7568;
}

U32 Range_size(void) {
    U32 hoisted__U32_7599 = 16;
    (void)hoisted__U32_7599;
    return hoisted__U32_7599;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7730 = 3;
    (void)hoisted__I64_7730;
    static Str hoisted__Str_7731 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7731;
    assert_eq__I64(result, hoisted__I64_7730, &hoisted__Str_7731);
    Str_delete(&hoisted__Str_7731, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7738 = 15;
    (void)hoisted__I64_7738;
    static Str hoisted__Str_7739 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7739;
    assert_eq__I64(result, hoisted__I64_7738, &hoisted__Str_7739);
    Str_delete(&hoisted__Str_7739, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7746 = 26;
    (void)hoisted__I64_7746;
    static Str hoisted__Str_7747 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7747;
    assert_eq__I64(result, hoisted__I64_7746, &hoisted__Str_7747);
    Str_delete(&hoisted__Str_7747, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7750 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7750;
    static Str hoisted__Str_7751 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7751;
    assert_eq__Str(&result, &hoisted__Str_7750, &hoisted__Str_7751);
    Str_delete(&hoisted__Str_7750, (Bool){0});
    Str_delete(&hoisted__Str_7751, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7779 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7779;
    static Str hoisted__Str_7780 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7780;
    assert_eq__Str(&r, &hoisted__Str_7779, &hoisted__Str_7780);
    Str_delete(&hoisted__Str_7779, (Bool){0});
    Str_delete(&hoisted__Str_7780, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7784 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7784;
    static Str hoisted__Str_7785 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7785;
    assert_eq__Str(&r2, &hoisted__Str_7784, &hoisted__Str_7785);
    Str_delete(&hoisted__Str_7784, (Bool){0});
    Str_delete(&hoisted__Str_7785, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7820 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7820;
    static Str hoisted__Str_7821 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7821;
    assert_eq__Str(&d, &hoisted__Str_7820, &hoisted__Str_7821);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7820, (Bool){0});
    Str_delete(&hoisted__Str_7821, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7832 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7832;
    static Str hoisted__Str_7833 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7833;
    assert_eq__Str(&d2, &hoisted__Str_7832, &hoisted__Str_7833);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7832, (Bool){0});
    Str_delete(&hoisted__Str_7833, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7845 = 106;
    (void)hoisted__I64_7845;
    static Str hoisted__Str_7846 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7846;
    assert_eq__I64(d3, hoisted__I64_7845, &hoisted__Str_7846);
    Str_delete(&hoisted__Str_7846, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_8445 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8445;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8445);
    Str_delete(&hoisted__Str_8445, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    static Str hoisted__Str_8446 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8446;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8446);
    Str_delete(&hoisted__Str_8446, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8448 = 8;
    (void)hoisted__I64_8448;
    static Str hoisted__Str_8449 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8449;
    assert_eq__I64(result, hoisted__I64_8448, &hoisted__Str_8449);
    Str_delete(&hoisted__Str_8449, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8452 = 1;
    (void)hoisted__Bool_8452;
    static Str hoisted__Str_8453 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8453;
    assert(hoisted__Bool_8452, &hoisted__Str_8453);
    Str_delete(&hoisted__Str_8453, (Bool){0});
    Bool hoisted__Bool_8456 = 1;
    (void)hoisted__Bool_8456;
    static Str hoisted__Str_8457 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8457;
    assert(hoisted__Bool_8456, &hoisted__Str_8457);
    Str_delete(&hoisted__Str_8457, (Bool){0});
}

void test_fold_f32(void) {
    static Str hoisted__Str_8462 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8462;
    static Str hoisted__Str_8463 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8463;
    static Str hoisted__Str_8464 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8464;
    assert_eq__Str(&hoisted__Str_8462, &hoisted__Str_8463, &hoisted__Str_8464);
    Str_delete(&hoisted__Str_8462, (Bool){0});
    Str_delete(&hoisted__Str_8463, (Bool){0});
    Str_delete(&hoisted__Str_8464, (Bool){0});
    static Str hoisted__Str_8467 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8467;
    static Str hoisted__Str_8468 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8468;
    static Str hoisted__Str_8469 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8469;
    assert_eq__Str(&hoisted__Str_8467, &hoisted__Str_8468, &hoisted__Str_8469);
    Str_delete(&hoisted__Str_8467, (Bool){0});
    Str_delete(&hoisted__Str_8468, (Bool){0});
    Str_delete(&hoisted__Str_8469, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8474 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8474;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8474;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8475 = 0;
    (void)hoisted__U32_8475;
    U64 hoisted__U64_8476 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8475); });
    (void)hoisted__U64_8476;
    return hoisted__U64_8476;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8507 = 16;
    (void)hoisted__U32_8507;
    return hoisted__U32_8507;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8508 = 42;
    (void)hoisted__I64_8508;
    static Str hoisted__Str_8509 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8509;
    assert_eq__I64(v.x, hoisted__I64_8508, &hoisted__Str_8509);
    Str_delete(&hoisted__Str_8509, (Bool){0});
    I64 hoisted__I64_8510 = 99;
    (void)hoisted__I64_8510;
    static Str hoisted__Str_8511 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8511;
    assert_eq__I64(v.y, hoisted__I64_8510, &hoisted__Str_8511);
    Str_delete(&hoisted__Str_8511, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8514 = 10;
    (void)hoisted__I64_8514;
    static Str hoisted__Str_8515 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8515;
    assert_eq__I64(p.x, hoisted__I64_8514, &hoisted__Str_8515);
    Str_delete(&hoisted__Str_8515, (Bool){0});
    I64 hoisted__I64_8516 = 20;
    (void)hoisted__I64_8516;
    static Str hoisted__Str_8517 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8517;
    assert_eq__I64(p.y, hoisted__I64_8516, &hoisted__Str_8517);
    Str_delete(&hoisted__Str_8517, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8523 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8523;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8523;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8524 = 0;
    (void)hoisted__U32_8524;
    U64 hoisted__U64_8525 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8524); });
    (void)hoisted__U64_8525;
    return hoisted__U64_8525;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8556 = 32;
    (void)hoisted__U32_8556;
    return hoisted__U32_8556;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8557 = 5;
    (void)hoisted__I64_8557;
    static Str hoisted__Str_8558 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8558;
    assert_eq__I64(r.top_left.x, hoisted__I64_8557, &hoisted__Str_8558);
    Str_delete(&hoisted__Str_8558, (Bool){0});
    I64 hoisted__I64_8559 = 10;
    (void)hoisted__I64_8559;
    static Str hoisted__Str_8560 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8560;
    assert_eq__I64(r.top_left.y, hoisted__I64_8559, &hoisted__Str_8560);
    Str_delete(&hoisted__Str_8560, (Bool){0});
    I64 hoisted__I64_8561 = 100;
    (void)hoisted__I64_8561;
    static Str hoisted__Str_8562 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8562;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8561, &hoisted__Str_8562);
    Str_delete(&hoisted__Str_8562, (Bool){0});
    I64 hoisted__I64_8563 = 200;
    (void)hoisted__I64_8563;
    static Str hoisted__Str_8564 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8564;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8563, &hoisted__Str_8564);
    Str_delete(&hoisted__Str_8564, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8566 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8566;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8566;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8567 = 0;
    (void)hoisted__U32_8567;
    U64 hoisted__U64_8568 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8567); });
    (void)hoisted__U64_8568;
    return hoisted__U64_8568;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8611 = 12;
    (void)hoisted__U32_8611;
    return hoisted__U32_8611;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8615 = F32_to_str(v.x);
    (void)hoisted__Str_8615;
    static Str hoisted__Str_8616 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8616;
    static Str hoisted__Str_8617 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8617;
    assert_eq__Str(hoisted__Str_8615, &hoisted__Str_8616, &hoisted__Str_8617);
    Str_delete(hoisted__Str_8615, 1);
    Str_delete(&hoisted__Str_8616, (Bool){0});
    Str_delete(&hoisted__Str_8617, (Bool){0});
    Str *hoisted__Str_8618 = F32_to_str(v.y);
    (void)hoisted__Str_8618;
    static Str hoisted__Str_8619 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8619;
    static Str hoisted__Str_8620 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8620;
    assert_eq__Str(hoisted__Str_8618, &hoisted__Str_8619, &hoisted__Str_8620);
    Str_delete(hoisted__Str_8618, 1);
    Str_delete(&hoisted__Str_8619, (Bool){0});
    Str_delete(&hoisted__Str_8620, (Bool){0});
    Str *hoisted__Str_8621 = F32_to_str(v.z);
    (void)hoisted__Str_8621;
    static Str hoisted__Str_8622 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8622;
    static Str hoisted__Str_8623 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8623;
    assert_eq__Str(hoisted__Str_8621, &hoisted__Str_8622, &hoisted__Str_8623);
    Str_delete(hoisted__Str_8621, 1);
    Str_delete(&hoisted__Str_8622, (Bool){0});
    Str_delete(&hoisted__Str_8623, (Bool){0});
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
    Bool hoisted__Bool_8628 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8628;
    if (hoisted__Bool_8628) {
        Bool hoisted__Bool_8625 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8625;
        { Bool _ret_val = hoisted__Bool_8625;
                return _ret_val; }
    }
    Bool hoisted__Bool_8629 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8629;
    if (hoisted__Bool_8629) {
        Bool hoisted__Bool_8626 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8626;
        { Bool _ret_val = hoisted__Bool_8626;
                return _ret_val; }
    }
    Bool hoisted__Bool_8630 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8630;
    if (hoisted__Bool_8630) {
        Bool hoisted__Bool_8627 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8627;
        { Bool _ret_val = hoisted__Bool_8627;
                return _ret_val; }
    }
    Bool hoisted__Bool_8631 = 0;
    (void)hoisted__Bool_8631;
    return hoisted__Bool_8631;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8639 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8639;
    if (hoisted__Bool_8639) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8640 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8640;
    if (hoisted__Bool_8640) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8641 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8641;
    if (hoisted__Bool_8641) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8642 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8642;
    UNREACHABLE(&hoisted__Str_8642);
    Str_delete(&hoisted__Str_8642, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8643 = 4;
    (void)hoisted__U32_8643;
    return hoisted__U32_8643;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8644 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8644;
    static Str hoisted__Str_8645 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8645;
    assert(hoisted__Bool_8644, &hoisted__Str_8645);
    Str_delete(&hoisted__Str_8645, (Bool){0});
    Bool hoisted__Bool_8646 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8646;
    Bool hoisted__Bool_8647 = not(hoisted__Bool_8646);
    (void)hoisted__Bool_8647;
    static Str hoisted__Str_8648 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8648;
    assert(hoisted__Bool_8647, &hoisted__Str_8648);
    Str_delete(&hoisted__Str_8648, (Bool){0});
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
    Bool hoisted__Bool_8649 = is(self, other);
    (void)hoisted__Bool_8649;
    return hoisted__Bool_8649;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8667 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8667;
    if (hoisted__Bool_8667) {
        I64 *hoisted__I64_8663 = get_payload(self);
        (void)hoisted__I64_8663;
        (void)hoisted__I64_8663;
        Bool hoisted__Bool_8664 = 0;
        (void)hoisted__Bool_8664;
        I64_delete(hoisted__I64_8663, hoisted__Bool_8664);
    }
    Bool hoisted__Bool_8668 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8668;
    if (hoisted__Bool_8668) {
        Str *hoisted__Str_8665 = get_payload(self);
        (void)hoisted__Str_8665;
        (void)hoisted__Str_8665;
        Bool hoisted__Bool_8666 = 0;
        (void)hoisted__Bool_8666;
        Str_delete(hoisted__Str_8665, hoisted__Bool_8666);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8699 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8699;
    if (hoisted__Bool_8699) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8696 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8696;
        { Token * _ret_val = hoisted__Token_8696;
                return _ret_val; }
    }
    Bool hoisted__Bool_8700 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8700;
    if (hoisted__Bool_8700) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8697 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8697;
        Token *hoisted__Token_8698 = Token_Name(hoisted__Str_8697);
        (void)hoisted__Token_8698;
        { Token * _ret_val = hoisted__Token_8698;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8701 = 24;
    (void)hoisted__U32_8701;
    return hoisted__U32_8701;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8703 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8703;
    static Str hoisted__Str_8704 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8704;
    assert(hoisted__Bool_8703, &hoisted__Str_8704);
    Str_delete(&hoisted__Str_8704, (Bool){0});
    Bool hoisted__Bool_8705 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8705;
    Bool hoisted__Bool_8706 = not(hoisted__Bool_8705);
    (void)hoisted__Bool_8706;
    static Str hoisted__Str_8707 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8707;
    assert(hoisted__Bool_8706, &hoisted__Str_8707);
    Str_delete(&hoisted__Str_8707, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8708 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8708;
    static Str hoisted__Str_8709 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8709;
    assert(hoisted__Bool_8708, &hoisted__Str_8709);
    Str_delete(&hoisted__Str_8709, (Bool){0});
    Bool hoisted__Bool_8710 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8710;
    Bool hoisted__Bool_8711 = not(hoisted__Bool_8710);
    (void)hoisted__Bool_8711;
    static Str hoisted__Str_8712 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8712;
    assert(hoisted__Bool_8711, &hoisted__Str_8712);
    Str_delete(&hoisted__Str_8712, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8715 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8715;
    static Str hoisted__Str_8716 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8716;
    assert(hoisted__Bool_8715, &hoisted__Str_8716);
    Str_delete(&hoisted__Str_8716, (Bool){0});
    Bool hoisted__Bool_8717 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8717;
    Bool hoisted__Bool_8718 = not(hoisted__Bool_8717);
    (void)hoisted__Bool_8718;
    static Str hoisted__Str_8719 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8719;
    assert(hoisted__Bool_8718, &hoisted__Str_8719);
    Str_delete(&hoisted__Str_8719, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8874 = I64_neq(a, b);
    (void)hoisted__Bool_8874;
    if (hoisted__Bool_8874) {
        U32 hoisted__U32_8858 = 5;
        (void)hoisted__U32_8858;
        Array__Str *_va_Array_244 = Array__Str_new(hoisted__U32_8858);
        (void)_va_Array_244;
        I64 _va_Array_244_ek = 0;
        (void)_va_Array_244_ek;
        OutOfBounds *_va_Array_244_eo = malloc(sizeof(OutOfBounds));
        _va_Array_244_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_244_eo;
        U32 hoisted__U32_8859 = 0;
        (void)hoisted__U32_8859;
        static Str hoisted__Str_8860 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8860;
        static Str hoisted__Str_8861 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8861;
        Array__Str_set(_va_Array_244, hoisted__U32_8859, &hoisted__Str_8860, &_va_Array_244_ek, _va_Array_244_eo, &hoisted__Str_8861);
        Str_delete(&hoisted__Str_8861, (Bool){0});
        U32 hoisted__U32_8862 = 1;
        (void)hoisted__U32_8862;
        Str *hoisted__Str_8863 = I64_to_str(a);
        (void)hoisted__Str_8863;
        static Str hoisted__Str_8864 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8864;
        Array__Str_set(_va_Array_244, hoisted__U32_8862, hoisted__Str_8863, &_va_Array_244_ek, _va_Array_244_eo, &hoisted__Str_8864);
        Str_delete(&hoisted__Str_8864, (Bool){0});
        U32 hoisted__U32_8865 = 2;
        (void)hoisted__U32_8865;
        static Str hoisted__Str_8866 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8866;
        static Str hoisted__Str_8867 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8867;
        Array__Str_set(_va_Array_244, hoisted__U32_8865, &hoisted__Str_8866, &_va_Array_244_ek, _va_Array_244_eo, &hoisted__Str_8867);
        Str_delete(&hoisted__Str_8867, (Bool){0});
        U32 hoisted__U32_8868 = 3;
        (void)hoisted__U32_8868;
        Str *hoisted__Str_8869 = I64_to_str(b);
        (void)hoisted__Str_8869;
        static Str hoisted__Str_8870 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8870;
        Array__Str_set(_va_Array_244, hoisted__U32_8868, hoisted__Str_8869, &_va_Array_244_ek, _va_Array_244_eo, &hoisted__Str_8870);
        Str_delete(&hoisted__Str_8870, (Bool){0});
        U32 hoisted__U32_8871 = 4;
        (void)hoisted__U32_8871;
        static Str hoisted__Str_8872 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8872;
        static Str hoisted__Str_8873 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8873;
        Array__Str_set(_va_Array_244, hoisted__U32_8871, &hoisted__Str_8872, &_va_Array_244_ek, _va_Array_244_eo, &hoisted__Str_8873);
        OutOfBounds_delete(_va_Array_244_eo, 1);
        Str_delete(&hoisted__Str_8873, (Bool){0});
        panic(_va_Array_244, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8891 = Str_neq(a, b);
    (void)hoisted__Bool_8891;
    if (hoisted__Bool_8891) {
        U32 hoisted__U32_8875 = 5;
        (void)hoisted__U32_8875;
        Array__Str *_va_Array_245 = Array__Str_new(hoisted__U32_8875);
        (void)_va_Array_245;
        I64 _va_Array_245_ek = 0;
        (void)_va_Array_245_ek;
        OutOfBounds *_va_Array_245_eo = malloc(sizeof(OutOfBounds));
        _va_Array_245_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_245_eo;
        U32 hoisted__U32_8876 = 0;
        (void)hoisted__U32_8876;
        static Str hoisted__Str_8877 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8877;
        static Str hoisted__Str_8878 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8878;
        Array__Str_set(_va_Array_245, hoisted__U32_8876, &hoisted__Str_8877, &_va_Array_245_ek, _va_Array_245_eo, &hoisted__Str_8878);
        Str_delete(&hoisted__Str_8878, (Bool){0});
        U32 hoisted__U32_8879 = 1;
        (void)hoisted__U32_8879;
        Str *hoisted__Str_8880 = Str_to_str(a);
        (void)hoisted__Str_8880;
        static Str hoisted__Str_8881 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8881;
        Array__Str_set(_va_Array_245, hoisted__U32_8879, hoisted__Str_8880, &_va_Array_245_ek, _va_Array_245_eo, &hoisted__Str_8881);
        Str_delete(&hoisted__Str_8881, (Bool){0});
        U32 hoisted__U32_8882 = 2;
        (void)hoisted__U32_8882;
        static Str hoisted__Str_8883 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8883;
        static Str hoisted__Str_8884 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8884;
        Array__Str_set(_va_Array_245, hoisted__U32_8882, &hoisted__Str_8883, &_va_Array_245_ek, _va_Array_245_eo, &hoisted__Str_8884);
        Str_delete(&hoisted__Str_8884, (Bool){0});
        U32 hoisted__U32_8885 = 3;
        (void)hoisted__U32_8885;
        Str *hoisted__Str_8886 = Str_to_str(b);
        (void)hoisted__Str_8886;
        static Str hoisted__Str_8887 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8887;
        Array__Str_set(_va_Array_245, hoisted__U32_8885, hoisted__Str_8886, &_va_Array_245_ek, _va_Array_245_eo, &hoisted__Str_8887);
        Str_delete(&hoisted__Str_8887, (Bool){0});
        U32 hoisted__U32_8888 = 4;
        (void)hoisted__U32_8888;
        static Str hoisted__Str_8889 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8889;
        static Str hoisted__Str_8890 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8890;
        Array__Str_set(_va_Array_245, hoisted__U32_8888, &hoisted__Str_8889, &_va_Array_245_ek, _va_Array_245_eo, &hoisted__Str_8890);
        OutOfBounds_delete(_va_Array_245_eo, 1);
        Str_delete(&hoisted__Str_8890, (Bool){0});
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
