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
    U32 hoisted__U32_679 = 1;
    (void)hoisted__U32_679;
    U32 hoisted__U64_680 = U32_add(n, hoisted__U32_679);
    (void)hoisted__U64_680;
    void * buf = malloc(hoisted__U64_680);
    I32 hoisted__I32_681 = 0;
    (void)hoisted__I32_681;
    U64 hoisted__U64_682 = 1ULL;
    (void)hoisted__U64_682;
    memset(buf, hoisted__I32_681, hoisted__U64_682);
    I64 hoisted__I64_683 = 0;
    (void)hoisted__I64_683;
    Str *hoisted__Str_684 = malloc(sizeof(Str));
    hoisted__Str_684->c_str = buf;
    hoisted__Str_684->count = hoisted__I64_683;
    hoisted__Str_684->cap = n;
    (void)hoisted__Str_684;
    return hoisted__Str_684;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_695 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_695;
    if (hoisted__Bool_695) {
        U32 hoisted__U32_687 = 1;
        (void)hoisted__U32_687;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_687);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_688 = 0;
        (void)hoisted__U32_688;
        Str hoisted__Str_689 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_689;
        Array__Str_set(_va_Array_19, hoisted__U32_688, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_689; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_19_ek, _va_Array_19_eo);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str hoisted__Str_690 = (Str){.c_str = (void *)"./src/core/str.til:91:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_690;
        panic(_va_Array_19, &hoisted__Str_690);
        Str_delete(&hoisted__Str_690, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_696 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_696;
    if (hoisted__Bool_696) {
        U32 hoisted__U32_691 = 1;
        (void)hoisted__U32_691;
        Array__Str *_va_Array_20 = Array__Str_new(hoisted__U32_691);
        (void)_va_Array_20;
        I64 _va_Array_20_ek = 0;
        (void)_va_Array_20_ek;
        OutOfBounds *_va_Array_20_eo = malloc(sizeof(OutOfBounds));
        _va_Array_20_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_20_eo;
        U32 hoisted__U32_692 = 0;
        (void)hoisted__U32_692;
        Str hoisted__Str_693 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_693;
        Array__Str_set(_va_Array_20, hoisted__U32_692, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_693; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_20_ek, _va_Array_20_eo);
        OutOfBounds_delete(_va_Array_20_eo, 1);
        Str hoisted__Str_694 = (Str){.c_str = (void *)"./src/core/str.til:95:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_694;
        panic(_va_Array_20, &hoisted__Str_694);
        Str_delete(&hoisted__Str_694, (Bool){0});
    }
    void *hoisted__v_697 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_697;
    (void)hoisted__v_697;
    memcpy(hoisted__v_697, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_698 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_698;
    (void)hoisted__v_698;
    I32 hoisted__I32_699 = 0;
    (void)hoisted__I32_699;
    U64 hoisted__U64_700 = 1ULL;
    (void)hoisted__U64_700;
    memset(hoisted__v_698, hoisted__I32_699, hoisted__U64_700);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_701 = 1;
    (void)hoisted__U32_701;
    U32 hoisted__U64_702 = U32_add(val->count, hoisted__U32_701);
    (void)hoisted__U64_702;
    void * new_data = malloc(hoisted__U64_702);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_703 = ptr_add(new_data, val->count);
    (void)hoisted__v_703;
    (void)hoisted__v_703;
    I32 hoisted__I32_704 = 0;
    (void)hoisted__I32_704;
    U64 hoisted__U64_705 = 1ULL;
    (void)hoisted__U64_705;
    memset(hoisted__v_703, hoisted__I32_704, hoisted__U64_705);
    Str *hoisted__Str_706 = malloc(sizeof(Str));
    hoisted__Str_706->c_str = new_data;
    hoisted__Str_706->count = val->count;
    hoisted__Str_706->cap = val->count;
    (void)hoisted__Str_706;
    return hoisted__Str_706;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_707 = Str_clone(self);
    (void)hoisted__Str_707;
    return hoisted__Str_707;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_708 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_708;
    if (hoisted__Bool_708) {
        free(self->c_str);
    }
    Bool hoisted__Bool_709 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_709;
    Bool hoisted__Bool_710 = and(call_free, hoisted__Bool_709);
    (void)hoisted__Bool_710;
    if (hoisted__Bool_710) {
        free(self);
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_905 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_905;
    return hoisted__U64_905;
}

U32 Str_size(void) {
    U32 hoisted__U32_1076 = 16;
    (void)hoisted__U32_1076;
    return hoisted__U32_1076;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1077 = Str_cmp(a, b);
    (void)hoisted__I64_1077;
    I64 hoisted__I64_1078 = 0;
    (void)hoisted__I64_1078;
    Bool hoisted__Bool_1079 = I64_eq(hoisted__I64_1077, hoisted__I64_1078);
    (void)hoisted__Bool_1079;
    return hoisted__Bool_1079;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1088 = Str_eq(a, b);
    (void)hoisted__Bool_1088;
    Bool hoisted__Bool_1089 = not(hoisted__Bool_1088);
    (void)hoisted__Bool_1089;
    return hoisted__Bool_1089;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1184 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1184->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1184;
    return hoisted__OutOfBounds_1184;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1185 = 0;
    (void)hoisted__Bool_1185;
    Str_delete(&self->msg, hoisted__Bool_1185);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1186 = 0;
    (void)hoisted__U32_1186;
    U64 hoisted__U64_1187 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1186); });
    (void)hoisted__U64_1187;
    return hoisted__U64_1187;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1202 = 16;
    (void)hoisted__U32_1202;
    return hoisted__U32_1202;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1222 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1222;
    U32 hoisted__U32_1223 = 16;
    (void)hoisted__U32_1223;
    Type *hoisted__Type_1224 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1224;
    U64 hoisted__U64_1225 = (U64)(cap);
    (void)hoisted__U64_1225;
    Type_delete(hoisted__Type_1222, 1);
    U64 hoisted__U64_1226 = (U64)(hoisted__U32_1223);
    (void)hoisted__U64_1226;
    Type_delete(hoisted__Type_1224, 1);
    void * hoisted__v_1227 = calloc(hoisted__U64_1225, hoisted__U64_1226);
    (void)hoisted__v_1227;
    Array__Str *hoisted__Array__Str_1228 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1228->data = hoisted__v_1227;
    hoisted__Array__Str_1228->cap = cap;
    (void)hoisted__Array__Str_1228;
    return hoisted__Array__Str_1228;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1250 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1250;
    if (hoisted__Bool_1250) {
        U32 hoisted__U32_1229 = 6;
        (void)hoisted__U32_1229;
        Array__Str *_va_Array_32 = Array__Str_new(hoisted__U32_1229);
        (void)_va_Array_32;
        I64 _va_Array_32_ek = 0;
        (void)_va_Array_32_ek;
        OutOfBounds *_va_Array_32_eo = malloc(sizeof(OutOfBounds));
        _va_Array_32_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_32_eo;
        U32 hoisted__U32_1230 = 0;
        (void)hoisted__U32_1230;
        Str hoisted__Str_1231 = (Str){.c_str = (void *)"./src/core/str.til:28:44", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1231;
        Array__Str_set(_va_Array_32, hoisted__U32_1230, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1231; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1232 = 1;
        (void)hoisted__U32_1232;
        Str hoisted__Str_1233 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1233;
        Array__Str_set(_va_Array_32, hoisted__U32_1232, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1233; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1234 = 2;
        (void)hoisted__U32_1234;
        Str *hoisted__Str_1235 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1235;
        Array__Str_set(_va_Array_32, hoisted__U32_1234, hoisted__Str_1235, &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1236 = 3;
        (void)hoisted__U32_1236;
        Str hoisted__Str_1237 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1237;
        Array__Str_set(_va_Array_32, hoisted__U32_1236, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1237; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1238 = 4;
        (void)hoisted__U32_1238;
        Str *hoisted__Str_1239 = U32_to_str(self->cap);
        (void)hoisted__Str_1239;
        Array__Str_set(_va_Array_32, hoisted__U32_1238, hoisted__Str_1239, &_va_Array_32_ek, _va_Array_32_eo);
        U32 hoisted__U32_1240 = 5;
        (void)hoisted__U32_1240;
        Str hoisted__Str_1241 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1241;
        Array__Str_set(_va_Array_32, hoisted__U32_1240, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1241; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_32_ek, _va_Array_32_eo);
        OutOfBounds_delete(_va_Array_32_eo, 1);
        OutOfBounds *hoisted__OutOfBounds_1242 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_32); hoisted__OutOfBounds_1242->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1242;
        U32 hoisted__U32_1243 = 16;
        (void)hoisted__U32_1243;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1242, hoisted__U32_1243);
        OutOfBounds_delete(hoisted__OutOfBounds_1242, 1);
        I64 hoisted__I64_1244 = 3;
        (void)hoisted__I64_1244;
        *_err_kind = hoisted__I64_1244;
    }
    I64 hoisted__I64_1251 = 0;
    (void)hoisted__I64_1251;
    Bool hoisted__Bool_1252 = I64_eq(DEREF(_err_kind), hoisted__I64_1251);
    (void)hoisted__Bool_1252;
    if (hoisted__Bool_1252) {
        U32 hoisted__U32_1245 = 16;
        (void)hoisted__U32_1245;
        U32 hoisted__U32_1246 = U32_mul(DEREF(i), hoisted__U32_1245);
        (void)hoisted__U32_1246;
        Type *hoisted__Type_1247 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1247;
        U64 hoisted__U64_1248 = (U64)(hoisted__U32_1246);
        (void)hoisted__U64_1248;
        Type_delete(hoisted__Type_1247, 1);
        void *hoisted__v_1249 = ptr_add(self->data, hoisted__U64_1248);
        (void)hoisted__v_1249;
        (void)hoisted__v_1249;
        { Str * _ret_val = hoisted__v_1249;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1287 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1287;
    if (hoisted__Bool_1287) {
        U32 hoisted__U32_1253 = 6;
        (void)hoisted__U32_1253;
        Array__Str *_va_Array_33 = Array__Str_new(hoisted__U32_1253);
        (void)_va_Array_33;
        I64 _va_Array_33_ek = 0;
        (void)_va_Array_33_ek;
        OutOfBounds *_va_Array_33_eo = malloc(sizeof(OutOfBounds));
        _va_Array_33_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_33_eo;
        U32 hoisted__U32_1254 = 0;
        (void)hoisted__U32_1254;
        Str hoisted__Str_1255 = (Str){.c_str = (void *)"./src/core/str.til:39:44", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1255;
        Array__Str_set(_va_Array_33, hoisted__U32_1254, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1255; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1256 = 1;
        (void)hoisted__U32_1256;
        Str hoisted__Str_1257 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1257;
        Array__Str_set(_va_Array_33, hoisted__U32_1256, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1257; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1258 = 2;
        (void)hoisted__U32_1258;
        Str *hoisted__Str_1259 = U32_to_str(i);
        (void)hoisted__Str_1259;
        Array__Str_set(_va_Array_33, hoisted__U32_1258, hoisted__Str_1259, &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1260 = 3;
        (void)hoisted__U32_1260;
        Str hoisted__Str_1261 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1261;
        Array__Str_set(_va_Array_33, hoisted__U32_1260, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1261; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1262 = 4;
        (void)hoisted__U32_1262;
        Str *hoisted__Str_1263 = U32_to_str(self->cap);
        (void)hoisted__Str_1263;
        Array__Str_set(_va_Array_33, hoisted__U32_1262, hoisted__Str_1263, &_va_Array_33_ek, _va_Array_33_eo);
        U32 hoisted__U32_1264 = 5;
        (void)hoisted__U32_1264;
        Str hoisted__Str_1265 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1265;
        Array__Str_set(_va_Array_33, hoisted__U32_1264, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1265; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_33_ek, _va_Array_33_eo);
        OutOfBounds_delete(_va_Array_33_eo, 1);
        OutOfBounds *hoisted__OutOfBounds_1266 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_33); hoisted__OutOfBounds_1266->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1266;
        U32 hoisted__U32_1267 = 16;
        (void)hoisted__U32_1267;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1266, hoisted__U32_1267);
        OutOfBounds_delete(hoisted__OutOfBounds_1266, 1);
        I64 hoisted__I64_1268 = 3;
        (void)hoisted__I64_1268;
        *_err_kind = hoisted__I64_1268;
    }
    I64 hoisted__I64_1288 = 0;
    (void)hoisted__I64_1288;
    Bool hoisted__Bool_1289 = I64_eq(DEREF(_err_kind), hoisted__I64_1288);
    (void)hoisted__Bool_1289;
    if (hoisted__Bool_1289) {
        U32 hoisted__U32_1269 = 16;
        (void)hoisted__U32_1269;
        U32 hoisted__U32_1270 = U32_mul(i, hoisted__U32_1269);
        (void)hoisted__U32_1270;
        Type *hoisted__Type_1271 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1271;
        U64 hoisted__U64_1272 = (U64)(hoisted__U32_1270);
        (void)hoisted__U64_1272;
        Type_delete(hoisted__Type_1271, 1);
        Str *hoisted__Str_1273 = ptr_add(self->data, hoisted__U64_1272);
        (void)hoisted__Str_1273;
        (void)hoisted__Str_1273;
        Bool hoisted__Bool_1274 = 0;
        (void)hoisted__Bool_1274;
        Str_delete(hoisted__Str_1273, hoisted__Bool_1274);
        U32 hoisted__U32_1275 = 16;
        (void)hoisted__U32_1275;
        U32 hoisted__U32_1276 = U32_mul(i, hoisted__U32_1275);
        (void)hoisted__U32_1276;
        Type *hoisted__Type_1277 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1277;
        U64 hoisted__U64_1278 = (U64)(hoisted__U32_1276);
        (void)hoisted__U64_1278;
        Type_delete(hoisted__Type_1277, 1);
        U32 hoisted__U32_1279 = 16;
        (void)hoisted__U32_1279;
        Type *hoisted__Type_1280 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1280;
        void *hoisted__v_1281 = ptr_add(self->data, hoisted__U64_1278);
        (void)hoisted__v_1281;
        (void)hoisted__v_1281;
        U64 hoisted__U64_1282 = (U64)(hoisted__U32_1279);
        (void)hoisted__U64_1282;
        Type_delete(hoisted__Type_1280, 1);
        memcpy(hoisted__v_1281, val, hoisted__U64_1282);
        U32 hoisted__U32_1283 = 16;
        (void)hoisted__U32_1283;
        Type *hoisted__Type_1284 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1284;
        I32 hoisted__I32_1285 = 0;
        (void)hoisted__I32_1285;
        U64 hoisted__U64_1286 = (U64)(hoisted__U32_1283);
        (void)hoisted__U64_1286;
        Type_delete(hoisted__Type_1284, 1);
        memset(val, hoisted__I32_1285, hoisted__U64_1286);
    }
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1290 = self->cap;
        (void)_re_U32_1290;
        U32 _rc_U32_1290 = 0;
        (void)_rc_U32_1290;
        Bool hoisted__Bool_1305 = U32_lte(_rc_U32_1290, _re_U32_1290);
        (void)hoisted__Bool_1305;
        if (hoisted__Bool_1305) {
            while (1) {
                Bool _wcond_Bool_1291 = U32_lt(_rc_U32_1290, _re_U32_1290);
                (void)_wcond_Bool_1291;
                if (_wcond_Bool_1291) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1290);
                U32_inc(&_rc_U32_1290);
                U32 hoisted__U32_1292 = 16;
                (void)hoisted__U32_1292;
                U32 hoisted__U32_1293 = U32_mul(i, hoisted__U32_1292);
                (void)hoisted__U32_1293;
                Type *hoisted__Type_1294 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1294;
                U64 hoisted__U64_1295 = (U64)(hoisted__U32_1293);
                (void)hoisted__U64_1295;
                Type_delete(hoisted__Type_1294, 1);
                Str *hoisted__Str_1296 = ptr_add(self->data, hoisted__U64_1295);
                (void)hoisted__Str_1296;
                (void)hoisted__Str_1296;
                Bool hoisted__Bool_1297 = 0;
                (void)hoisted__Bool_1297;
                Str_delete(hoisted__Str_1296, hoisted__Bool_1297);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1298 = U32_gt(_rc_U32_1290, _re_U32_1290);
                (void)_wcond_Bool_1298;
                if (_wcond_Bool_1298) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1290);
                U32_dec(&_rc_U32_1290);
                U32 hoisted__U32_1299 = 16;
                (void)hoisted__U32_1299;
                U32 hoisted__U32_1300 = U32_mul(i, hoisted__U32_1299);
                (void)hoisted__U32_1300;
                Type *hoisted__Type_1301 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1301;
                U64 hoisted__U64_1302 = (U64)(hoisted__U32_1300);
                (void)hoisted__U64_1302;
                Type_delete(hoisted__Type_1301, 1);
                Str *hoisted__Str_1303 = ptr_add(self->data, hoisted__U64_1302);
                (void)hoisted__Str_1303;
                (void)hoisted__Str_1303;
                Bool hoisted__Bool_1304 = 0;
                (void)hoisted__Bool_1304;
                Str_delete(hoisted__Str_1303, hoisted__Bool_1304);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1342 = 16;
    (void)hoisted__U32_1342;
    U32 hoisted__U32_1343 = U32_mul(self->cap, hoisted__U32_1342);
    (void)hoisted__U32_1343;
    Type *hoisted__Type_1344 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1344;
    U64 hoisted__U64_1345 = (U64)(hoisted__U32_1343);
    (void)hoisted__U64_1345;
    Type_delete(hoisted__Type_1344, 1);
    void * new_data = malloc(hoisted__U64_1345);
    {
        U32 _re_U32_1306 = self->cap;
        (void)_re_U32_1306;
        U32 _rc_U32_1306 = 0;
        (void)_rc_U32_1306;
        Bool hoisted__Bool_1341 = U32_lte(_rc_U32_1306, _re_U32_1306);
        (void)hoisted__Bool_1341;
        if (hoisted__Bool_1341) {
            while (1) {
                Bool _wcond_Bool_1307 = U32_lt(_rc_U32_1306, _re_U32_1306);
                (void)_wcond_Bool_1307;
                if (_wcond_Bool_1307) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1306);
                U32_inc(&_rc_U32_1306);
                U32 hoisted__U32_1308 = 16;
                (void)hoisted__U32_1308;
                U32 hoisted__U32_1309 = U32_mul(i, hoisted__U32_1308);
                (void)hoisted__U32_1309;
                Type *hoisted__Type_1310 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1310;
                U64 hoisted__U64_1311 = (U64)(hoisted__U32_1309);
                (void)hoisted__U64_1311;
                Type_delete(hoisted__Type_1310, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1311);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1312 = 16;
                (void)hoisted__U32_1312;
                U32 hoisted__U32_1313 = U32_mul(i, hoisted__U32_1312);
                (void)hoisted__U32_1313;
                Type *hoisted__Type_1314 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1314;
                U64 hoisted__U64_1315 = (U64)(hoisted__U32_1313);
                (void)hoisted__U64_1315;
                Type_delete(hoisted__Type_1314, 1);
                U32 hoisted__U32_1316 = 16;
                (void)hoisted__U32_1316;
                Type *hoisted__Type_1317 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1317;
                void *hoisted__v_1318 = ptr_add(new_data, hoisted__U64_1315);
                (void)hoisted__v_1318;
                (void)hoisted__v_1318;
                U64 hoisted__U64_1319 = (U64)(hoisted__U32_1316);
                (void)hoisted__U64_1319;
                Type_delete(hoisted__Type_1317, 1);
                memcpy(hoisted__v_1318, cloned, hoisted__U64_1319);
                U32 hoisted__U32_1320 = 16;
                (void)hoisted__U32_1320;
                Type *hoisted__Type_1321 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1321;
                I32 hoisted__I32_1322 = 0;
                (void)hoisted__I32_1322;
                U64 hoisted__U64_1323 = (U64)(hoisted__U32_1320);
                (void)hoisted__U64_1323;
                Type_delete(hoisted__Type_1321, 1);
                memset(cloned, hoisted__I32_1322, hoisted__U64_1323);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1324 = U32_gt(_rc_U32_1306, _re_U32_1306);
                (void)_wcond_Bool_1324;
                if (_wcond_Bool_1324) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1306);
                U32_dec(&_rc_U32_1306);
                U32 hoisted__U32_1325 = 16;
                (void)hoisted__U32_1325;
                U32 hoisted__U32_1326 = U32_mul(i, hoisted__U32_1325);
                (void)hoisted__U32_1326;
                Type *hoisted__Type_1327 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1327;
                U64 hoisted__U64_1328 = (U64)(hoisted__U32_1326);
                (void)hoisted__U64_1328;
                Type_delete(hoisted__Type_1327, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1328);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1329 = 16;
                (void)hoisted__U32_1329;
                U32 hoisted__U32_1330 = U32_mul(i, hoisted__U32_1329);
                (void)hoisted__U32_1330;
                Type *hoisted__Type_1331 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1331;
                U64 hoisted__U64_1332 = (U64)(hoisted__U32_1330);
                (void)hoisted__U64_1332;
                Type_delete(hoisted__Type_1331, 1);
                U32 hoisted__U32_1333 = 16;
                (void)hoisted__U32_1333;
                Type *hoisted__Type_1334 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1334;
                void *hoisted__v_1335 = ptr_add(new_data, hoisted__U64_1332);
                (void)hoisted__v_1335;
                (void)hoisted__v_1335;
                U64 hoisted__U64_1336 = (U64)(hoisted__U32_1333);
                (void)hoisted__U64_1336;
                Type_delete(hoisted__Type_1334, 1);
                memcpy(hoisted__v_1335, cloned, hoisted__U64_1336);
                U32 hoisted__U32_1337 = 16;
                (void)hoisted__U32_1337;
                Type *hoisted__Type_1338 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1338;
                I32 hoisted__I32_1339 = 0;
                (void)hoisted__I32_1339;
                U64 hoisted__U64_1340 = (U64)(hoisted__U32_1337);
                (void)hoisted__U64_1340;
                Type_delete(hoisted__Type_1338, 1);
                memset(cloned, hoisted__I32_1339, hoisted__U64_1340);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1346 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1346->data = new_data;
    hoisted__Array__Str_1346->cap = self->cap;
    (void)hoisted__Array__Str_1346;
    return hoisted__Array__Str_1346;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1347 = 16;
    (void)hoisted__U32_1347;
    return hoisted__U32_1347;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1348 = 16;
    (void)hoisted__U32_1348;
    Type *hoisted__Type_1349 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1349;
    U64 hoisted__U64_1350 = (U64)(hoisted__U32_1348);
    (void)hoisted__U64_1350;
    Type_delete(hoisted__Type_1349, 1);
    void * hoisted__v_1351 = malloc(hoisted__U64_1350);
    (void)hoisted__v_1351;
    U32 hoisted__U32_1352 = 0;
    (void)hoisted__U32_1352;
    I64 hoisted__I64_1353 = 1;
    (void)hoisted__I64_1353;
    Vec__Str *hoisted__Vec__Str_1354 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1354->data = hoisted__v_1351;
    hoisted__Vec__Str_1354->count = hoisted__U32_1352;
    hoisted__Vec__Str_1354->cap = hoisted__I64_1353;
    (void)hoisted__Vec__Str_1354;
    return hoisted__Vec__Str_1354;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1355 = self->count;
        (void)_re_U32_1355;
        U32 _rc_U32_1355 = 0;
        (void)_rc_U32_1355;
        Bool hoisted__Bool_1370 = U32_lte(_rc_U32_1355, _re_U32_1355);
        (void)hoisted__Bool_1370;
        if (hoisted__Bool_1370) {
            while (1) {
                Bool _wcond_Bool_1356 = U32_lt(_rc_U32_1355, _re_U32_1355);
                (void)_wcond_Bool_1356;
                if (_wcond_Bool_1356) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1355);
                U32_inc(&_rc_U32_1355);
                U32 hoisted__U32_1357 = 16;
                (void)hoisted__U32_1357;
                U32 hoisted__U32_1358 = U32_mul(i, hoisted__U32_1357);
                (void)hoisted__U32_1358;
                Type *hoisted__Type_1359 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1359;
                U64 hoisted__U64_1360 = (U64)(hoisted__U32_1358);
                (void)hoisted__U64_1360;
                Type_delete(hoisted__Type_1359, 1);
                Str *hoisted__Str_1361 = ptr_add(self->data, hoisted__U64_1360);
                (void)hoisted__Str_1361;
                (void)hoisted__Str_1361;
                Bool hoisted__Bool_1362 = 0;
                (void)hoisted__Bool_1362;
                Str_delete(hoisted__Str_1361, hoisted__Bool_1362);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1363 = U32_gt(_rc_U32_1355, _re_U32_1355);
                (void)_wcond_Bool_1363;
                if (_wcond_Bool_1363) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1355);
                U32_dec(&_rc_U32_1355);
                U32 hoisted__U32_1364 = 16;
                (void)hoisted__U32_1364;
                U32 hoisted__U32_1365 = U32_mul(i, hoisted__U32_1364);
                (void)hoisted__U32_1365;
                Type *hoisted__Type_1366 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1366;
                U64 hoisted__U64_1367 = (U64)(hoisted__U32_1365);
                (void)hoisted__U64_1367;
                Type_delete(hoisted__Type_1366, 1);
                Str *hoisted__Str_1368 = ptr_add(self->data, hoisted__U64_1367);
                (void)hoisted__Str_1368;
                (void)hoisted__Str_1368;
                Bool hoisted__Bool_1369 = 0;
                (void)hoisted__Bool_1369;
                Str_delete(hoisted__Str_1368, hoisted__Bool_1369);
            }
        }
    }
    U32 hoisted__U32_1371 = 0;
    (void)hoisted__U32_1371;
    self->count = hoisted__U32_1371;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1664 = 16;
    (void)hoisted__U32_1664;
    U32 hoisted__U32_1665 = U32_mul(self->cap, hoisted__U32_1664);
    (void)hoisted__U32_1665;
    Type *hoisted__Type_1666 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1666;
    U64 hoisted__U64_1667 = (U64)(hoisted__U32_1665);
    (void)hoisted__U64_1667;
    Type_delete(hoisted__Type_1666, 1);
    void * new_data = malloc(hoisted__U64_1667);
    {
        U32 _re_U32_1628 = self->count;
        (void)_re_U32_1628;
        U32 _rc_U32_1628 = 0;
        (void)_rc_U32_1628;
        Bool hoisted__Bool_1663 = U32_lte(_rc_U32_1628, _re_U32_1628);
        (void)hoisted__Bool_1663;
        if (hoisted__Bool_1663) {
            while (1) {
                Bool _wcond_Bool_1629 = U32_lt(_rc_U32_1628, _re_U32_1628);
                (void)_wcond_Bool_1629;
                if (_wcond_Bool_1629) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1628);
                U32_inc(&_rc_U32_1628);
                U32 hoisted__U32_1630 = 16;
                (void)hoisted__U32_1630;
                U32 hoisted__U32_1631 = U32_mul(i, hoisted__U32_1630);
                (void)hoisted__U32_1631;
                Type *hoisted__Type_1632 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1632;
                U64 hoisted__U64_1633 = (U64)(hoisted__U32_1631);
                (void)hoisted__U64_1633;
                Type_delete(hoisted__Type_1632, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1633);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1634 = 16;
                (void)hoisted__U32_1634;
                U32 hoisted__U32_1635 = U32_mul(i, hoisted__U32_1634);
                (void)hoisted__U32_1635;
                Type *hoisted__Type_1636 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1636;
                U64 hoisted__U64_1637 = (U64)(hoisted__U32_1635);
                (void)hoisted__U64_1637;
                Type_delete(hoisted__Type_1636, 1);
                U32 hoisted__U32_1638 = 16;
                (void)hoisted__U32_1638;
                Type *hoisted__Type_1639 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1639;
                void *hoisted__v_1640 = ptr_add(new_data, hoisted__U64_1637);
                (void)hoisted__v_1640;
                (void)hoisted__v_1640;
                U64 hoisted__U64_1641 = (U64)(hoisted__U32_1638);
                (void)hoisted__U64_1641;
                Type_delete(hoisted__Type_1639, 1);
                memcpy(hoisted__v_1640, cloned, hoisted__U64_1641);
                U32 hoisted__U32_1642 = 16;
                (void)hoisted__U32_1642;
                Type *hoisted__Type_1643 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1643;
                I32 hoisted__I32_1644 = 0;
                (void)hoisted__I32_1644;
                U64 hoisted__U64_1645 = (U64)(hoisted__U32_1642);
                (void)hoisted__U64_1645;
                Type_delete(hoisted__Type_1643, 1);
                memset(cloned, hoisted__I32_1644, hoisted__U64_1645);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1646 = U32_gt(_rc_U32_1628, _re_U32_1628);
                (void)_wcond_Bool_1646;
                if (_wcond_Bool_1646) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1628);
                U32_dec(&_rc_U32_1628);
                U32 hoisted__U32_1647 = 16;
                (void)hoisted__U32_1647;
                U32 hoisted__U32_1648 = U32_mul(i, hoisted__U32_1647);
                (void)hoisted__U32_1648;
                Type *hoisted__Type_1649 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1649;
                U64 hoisted__U64_1650 = (U64)(hoisted__U32_1648);
                (void)hoisted__U64_1650;
                Type_delete(hoisted__Type_1649, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1650);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1651 = 16;
                (void)hoisted__U32_1651;
                U32 hoisted__U32_1652 = U32_mul(i, hoisted__U32_1651);
                (void)hoisted__U32_1652;
                Type *hoisted__Type_1653 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1653;
                U64 hoisted__U64_1654 = (U64)(hoisted__U32_1652);
                (void)hoisted__U64_1654;
                Type_delete(hoisted__Type_1653, 1);
                U32 hoisted__U32_1655 = 16;
                (void)hoisted__U32_1655;
                Type *hoisted__Type_1656 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1656;
                void *hoisted__v_1657 = ptr_add(new_data, hoisted__U64_1654);
                (void)hoisted__v_1657;
                (void)hoisted__v_1657;
                U64 hoisted__U64_1658 = (U64)(hoisted__U32_1655);
                (void)hoisted__U64_1658;
                Type_delete(hoisted__Type_1656, 1);
                memcpy(hoisted__v_1657, cloned, hoisted__U64_1658);
                U32 hoisted__U32_1659 = 16;
                (void)hoisted__U32_1659;
                Type *hoisted__Type_1660 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1660;
                I32 hoisted__I32_1661 = 0;
                (void)hoisted__I32_1661;
                U64 hoisted__U64_1662 = (U64)(hoisted__U32_1659);
                (void)hoisted__U64_1662;
                Type_delete(hoisted__Type_1660, 1);
                memset(cloned, hoisted__I32_1661, hoisted__U64_1662);
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1668 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1668->data = new_data;
    hoisted__Vec__Str_1668->count = self->count;
    hoisted__Vec__Str_1668->cap = self->cap;
    (void)hoisted__Vec__Str_1668;
    return hoisted__Vec__Str_1668;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1669 = 16;
    (void)hoisted__U32_1669;
    return hoisted__U32_1669;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1672 = 8;
    (void)hoisted__U32_1672;
    return hoisted__U32_1672;
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
    I64 hoisted__I64_1861 = 0;
    (void)hoisted__I64_1861;
    Bool hoisted__Bool_1862 = I64_eq(val, hoisted__I64_1861);
    (void)hoisted__Bool_1862;
    if (hoisted__Bool_1862) {
        U64 hoisted__U64_1831 = 2ULL;
        (void)hoisted__U64_1831;
        void * buf = malloc(hoisted__U64_1831);
        I64 hoisted__I64_1832 = 48;
        (void)hoisted__I64_1832;
        U64 hoisted__U64_1833 = 1ULL;
        (void)hoisted__U64_1833;
        memcpy(buf, &hoisted__I64_1832, hoisted__U64_1833);
        U64 hoisted__U64_1834 = 1ULL;
        (void)hoisted__U64_1834;
        void *hoisted__v_1835 = ptr_add(buf, hoisted__U64_1834);
        (void)hoisted__v_1835;
        (void)hoisted__v_1835;
        I32 hoisted__I32_1836 = 0;
        (void)hoisted__I32_1836;
        U64 hoisted__U64_1837 = 1ULL;
        (void)hoisted__U64_1837;
        memset(hoisted__v_1835, hoisted__I32_1836, hoisted__U64_1837);
        I64 hoisted__I64_1838 = 1;
        (void)hoisted__I64_1838;
        I64 hoisted__I64_1839 = 1;
        (void)hoisted__I64_1839;
        Str *hoisted__Str_1840 = malloc(sizeof(Str));
        hoisted__Str_1840->c_str = buf;
        hoisted__Str_1840->count = hoisted__I64_1838;
        hoisted__Str_1840->cap = hoisted__I64_1839;
        (void)hoisted__Str_1840;
        { Str * _ret_val = hoisted__Str_1840;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1863 = 0;
    (void)hoisted__I64_1863;
    Bool hoisted__Bool_1864 = I64_lt(val, hoisted__I64_1863);
    (void)hoisted__Bool_1864;
    if (hoisted__Bool_1864) {
        Bool hoisted__Bool_1841 = 1;
        (void)hoisted__Bool_1841;
        is_neg = hoisted__Bool_1841;
        I64 hoisted__I64_1842 = 0;
        (void)hoisted__I64_1842;
        I64 hoisted__I64_1843 = I64_sub(hoisted__I64_1842, val);
        (void)hoisted__I64_1843;
        v = hoisted__I64_1843;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1845 = 0;
        (void)hoisted__I64_1845;
        Bool _wcond_Bool_1844 = I64_gt(tmp, hoisted__I64_1845);
        (void)_wcond_Bool_1844;
        if (_wcond_Bool_1844) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1846 = 10;
        (void)hoisted__I64_1846;
        I64 hoisted__I64_1847 = I64_div(tmp, hoisted__I64_1846);
        (void)hoisted__I64_1847;
        tmp = hoisted__I64_1847;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1865 = 1ULL;
    (void)hoisted__U64_1865;
    U64 hoisted__U64_1866 = U64_add(total, hoisted__U64_1865);
    (void)hoisted__U64_1866;
    void * buf = malloc(hoisted__U64_1866);
    if (is_neg) {
        I64 hoisted__I64_1848 = 45;
        (void)hoisted__I64_1848;
        U64 hoisted__U64_1849 = 1ULL;
        (void)hoisted__U64_1849;
        memcpy(buf, &hoisted__I64_1848, hoisted__U64_1849);
    }
    U64 hoisted__U64_1867 = 1ULL;
    (void)hoisted__U64_1867;
    U64 i = U64_sub(total, hoisted__U64_1867);
    while (1) {
        I64 hoisted__I64_1851 = 0;
        (void)hoisted__I64_1851;
        Bool _wcond_Bool_1850 = I64_gt(v, hoisted__I64_1851);
        (void)_wcond_Bool_1850;
        if (_wcond_Bool_1850) {
        } else {
            break;
        }
        I64 hoisted__I64_1852 = 10;
        (void)hoisted__I64_1852;
        I64 hoisted__I64_1853 = I64_mod(v, hoisted__I64_1852);
        (void)hoisted__I64_1853;
        I64 hoisted__I64_1854 = 48;
        (void)hoisted__I64_1854;
        I64 hoisted__I64_1855 = I64_add(hoisted__I64_1853, hoisted__I64_1854);
        (void)hoisted__I64_1855;
        void *hoisted__v_1856 = ptr_add(buf, i);
        (void)hoisted__v_1856;
        (void)hoisted__v_1856;
        U8 hoisted__U8_1857 = I64_to_u8(hoisted__I64_1855);
        (void)hoisted__U8_1857;
        U64 hoisted__U64_1858 = 1ULL;
        (void)hoisted__U64_1858;
        memcpy(hoisted__v_1856, &hoisted__U8_1857, hoisted__U64_1858);
        I64 hoisted__I64_1859 = 10;
        (void)hoisted__I64_1859;
        I64 hoisted__I64_1860 = I64_div(v, hoisted__I64_1859);
        (void)hoisted__I64_1860;
        v = hoisted__I64_1860;
        U64_dec(&i);
    }
    void *hoisted__v_1868 = ptr_add(buf, total);
    (void)hoisted__v_1868;
    (void)hoisted__v_1868;
    I32 hoisted__I32_1869 = 0;
    (void)hoisted__I32_1869;
    U64 hoisted__U64_1870 = 1ULL;
    (void)hoisted__U64_1870;
    memset(hoisted__v_1868, hoisted__I32_1869, hoisted__U64_1870);
    Str *hoisted__Str_1871 = malloc(sizeof(Str));
    hoisted__Str_1871->c_str = buf;
    hoisted__Str_1871->count = total;
    hoisted__Str_1871->cap = total;
    (void)hoisted__Str_1871;
    return hoisted__Str_1871;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1891 = 8;
    (void)hoisted__U32_1891;
    return hoisted__U32_1891;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2012 = 0;
    (void)hoisted__U32_2012;
    U64 hoisted__U64_2013 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2012); });
    (void)hoisted__U64_2013;
    return hoisted__U64_2013;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2016 = I64_cmp(a, b);
    (void)hoisted__I64_2016;
    I64 hoisted__I64_2017 = -1;
    (void)hoisted__I64_2017;
    Bool hoisted__Bool_2018 = I64_eq(hoisted__I64_2016, hoisted__I64_2017);
    (void)hoisted__Bool_2018;
    return hoisted__Bool_2018;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2019 = I64_cmp(a, b);
    (void)hoisted__I64_2019;
    I64 hoisted__I64_2020 = 1;
    (void)hoisted__I64_2020;
    Bool hoisted__Bool_2021 = I64_eq(hoisted__I64_2019, hoisted__I64_2020);
    (void)hoisted__Bool_2021;
    return hoisted__Bool_2021;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2022 = I64_eq(a, b);
    (void)hoisted__Bool_2022;
    Bool hoisted__Bool_2023 = not(hoisted__Bool_2022);
    (void)hoisted__Bool_2023;
    return hoisted__Bool_2023;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2058 = 0;
    (void)_m_Bool_2058;
    {
        Bool hoisted__Bool_2061 = 1;
        (void)hoisted__Bool_2061;
        Bool hoisted__Bool_2062 = Bool_eq(a, hoisted__Bool_2061);
        (void)hoisted__Bool_2062;
        if (hoisted__Bool_2062) {
            Bool hoisted__Bool_2059 = Bool_clone(&b);
            (void)hoisted__Bool_2059;
            _m_Bool_2058 = hoisted__Bool_2059;
        } else {
            Bool hoisted__Bool_2060 = 0;
            (void)hoisted__Bool_2060;
            _m_Bool_2058 = hoisted__Bool_2060;
        }
    }
    return _m_Bool_2058;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2072 = Bool_eq(a, b);
    (void)hoisted__Bool_2072;
    if (hoisted__Bool_2072) {
        I64 hoisted__I64_2070 = 0;
        (void)hoisted__I64_2070;
        { I64 _ret_val = hoisted__I64_2070;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2071 = -1;
        (void)hoisted__I64_2071;
        return hoisted__I64_2071;
    }
    I64 hoisted__I64_2073 = 1;
    (void)hoisted__I64_2073;
    return hoisted__I64_2073;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2074 = 1;
    (void)hoisted__U32_2074;
    return hoisted__U32_2074;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2075 = 0;
    (void)hoisted__U32_2075;
    U64 hoisted__U64_2076 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2075); });
    (void)hoisted__U64_2076;
    return hoisted__U64_2076;
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
    Bool hoisted__Bool_2102 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2102;
    if (hoisted__Bool_2102) {
        Bool hoisted__Bool_2092 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2092;
        { Bool _ret_val = hoisted__Bool_2092;
                return _ret_val; }
    }
    Bool hoisted__Bool_2103 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2103;
    if (hoisted__Bool_2103) {
        Bool hoisted__Bool_2093 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2093;
        { Bool _ret_val = hoisted__Bool_2093;
                return _ret_val; }
    }
    Bool hoisted__Bool_2104 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2104;
    if (hoisted__Bool_2104) {
        Bool hoisted__Bool_2094 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2094;
        { Bool _ret_val = hoisted__Bool_2094;
                return _ret_val; }
    }
    Bool hoisted__Bool_2105 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2105;
    if (hoisted__Bool_2105) {
        Bool hoisted__Bool_2095 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2095;
        { Bool _ret_val = hoisted__Bool_2095;
                return _ret_val; }
    }
    Bool hoisted__Bool_2106 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2106;
    if (hoisted__Bool_2106) {
        Bool hoisted__Bool_2096 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2096;
        { Bool _ret_val = hoisted__Bool_2096;
                return _ret_val; }
    }
    Bool hoisted__Bool_2107 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2107;
    if (hoisted__Bool_2107) {
        Bool hoisted__Bool_2097 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2097;
        { Bool _ret_val = hoisted__Bool_2097;
                return _ret_val; }
    }
    Bool hoisted__Bool_2108 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2108;
    if (hoisted__Bool_2108) {
        Bool hoisted__Bool_2098 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2098;
        { Bool _ret_val = hoisted__Bool_2098;
                return _ret_val; }
    }
    Bool hoisted__Bool_2109 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2109;
    if (hoisted__Bool_2109) {
        Bool hoisted__Bool_2099 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2099;
        { Bool _ret_val = hoisted__Bool_2099;
                return _ret_val; }
    }
    Bool hoisted__Bool_2110 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2110;
    if (hoisted__Bool_2110) {
        Bool hoisted__Bool_2100 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2100;
        { Bool _ret_val = hoisted__Bool_2100;
                return _ret_val; }
    }
    Bool hoisted__Bool_2111 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2111;
    if (hoisted__Bool_2111) {
        Bool hoisted__Bool_2101 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2101;
        { Bool _ret_val = hoisted__Bool_2101;
                return _ret_val; }
    }
    Bool hoisted__Bool_2112 = 0;
    (void)hoisted__Bool_2112;
    return hoisted__Bool_2112;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2134 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2134;
    if (hoisted__Bool_2134) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2135 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2135;
    if (hoisted__Bool_2135) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2136 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2136;
    if (hoisted__Bool_2136) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2137 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2137;
    if (hoisted__Bool_2137) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2138 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2138;
    if (hoisted__Bool_2138) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2139 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2139;
    if (hoisted__Bool_2139) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2140 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2140;
    if (hoisted__Bool_2140) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2141 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2141;
    if (hoisted__Bool_2141) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2142 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2142;
    if (hoisted__Bool_2142) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2143 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2143;
    if (hoisted__Bool_2143) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2144 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2144;
    UNREACHABLE(&hoisted__Str_2144);
    Str_delete(&hoisted__Str_2144, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2145 = 4;
    (void)hoisted__U32_2145;
    return hoisted__U32_2145;
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
    Bool hoisted__Bool_2197 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2197;
    if (hoisted__Bool_2197) {
        Str *hoisted__Str_2187 = get_payload(self);
        (void)hoisted__Str_2187;
        (void)hoisted__Str_2187;
        Bool hoisted__Bool_2188 = 0;
        (void)hoisted__Bool_2188;
        Str_delete(hoisted__Str_2187, hoisted__Bool_2188);
    }
    Bool hoisted__Bool_2198 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2198;
    if (hoisted__Bool_2198) {
        Str *hoisted__Str_2189 = get_payload(self);
        (void)hoisted__Str_2189;
        (void)hoisted__Str_2189;
        Bool hoisted__Bool_2190 = 0;
        (void)hoisted__Bool_2190;
        Str_delete(hoisted__Str_2189, hoisted__Bool_2190);
    }
    Bool hoisted__Bool_2199 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2199;
    if (hoisted__Bool_2199) {
        Str *hoisted__Str_2191 = get_payload(self);
        (void)hoisted__Str_2191;
        (void)hoisted__Str_2191;
        Bool hoisted__Bool_2192 = 0;
        (void)hoisted__Bool_2192;
        Str_delete(hoisted__Str_2191, hoisted__Bool_2192);
    }
    Bool hoisted__Bool_2200 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2200;
    if (hoisted__Bool_2200) {
        Primitive *hoisted__Primitive_2193 = get_payload(self);
        (void)hoisted__Primitive_2193;
        (void)hoisted__Primitive_2193;
        Bool hoisted__Bool_2194 = 0;
        (void)hoisted__Bool_2194;
        Primitive_delete(hoisted__Primitive_2193, hoisted__Bool_2194);
    }
    Bool hoisted__Bool_2201 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2201;
    if (hoisted__Bool_2201) {
        Str *hoisted__Str_2195 = get_payload(self);
        (void)hoisted__Str_2195;
        (void)hoisted__Str_2195;
        Bool hoisted__Bool_2196 = 0;
        (void)hoisted__Bool_2196;
        Str_delete(hoisted__Str_2195, hoisted__Bool_2196);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2270 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2270;
    if (hoisted__Bool_2270) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2271 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2271;
    if (hoisted__Bool_2271) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2272 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2272;
    if (hoisted__Bool_2272) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2262 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2262;
        Type *hoisted__Type_2263 = Type_Struct(hoisted__Str_2262);
        (void)hoisted__Type_2263;
        { Type * _ret_val = hoisted__Type_2263;
                return _ret_val; }
    }
    Bool hoisted__Bool_2273 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2273;
    if (hoisted__Bool_2273) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2274 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2274;
    if (hoisted__Bool_2274) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2264 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2264;
        Type *hoisted__Type_2265 = Type_Enum(hoisted__Str_2264);
        (void)hoisted__Type_2265;
        { Type * _ret_val = hoisted__Type_2265;
                return _ret_val; }
    }
    Bool hoisted__Bool_2275 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2275;
    if (hoisted__Bool_2275) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2276 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2276;
    if (hoisted__Bool_2276) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2277 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2277;
    if (hoisted__Bool_2277) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2278 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2278;
    if (hoisted__Bool_2278) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2279 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2279;
    if (hoisted__Bool_2279) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2266 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2266;
        Type *hoisted__Type_2267 = Type_Custom(hoisted__Str_2266);
        (void)hoisted__Type_2267;
        { Type * _ret_val = hoisted__Type_2267;
                return _ret_val; }
    }
    Bool hoisted__Bool_2280 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2280;
    if (hoisted__Bool_2280) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2268 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2268;
        Type *hoisted__Type_2269 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2268; _oa; }));
        (void)hoisted__Type_2269;
        { Type * _ret_val = hoisted__Type_2269;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2281 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2281;
    Type *hoisted__Type_2282 = Type_FuncPtrSig(hoisted__Str_2281);
    (void)hoisted__Type_2282;
    return hoisted__Type_2282;
}

U32 Type_size(void) {
    U32 hoisted__U32_2283 = 24;
    (void)hoisted__U32_2283;
    return hoisted__U32_2283;
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
    Bool hoisted__Bool_2384 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2384;
    if (hoisted__Bool_2384) {
        Bool hoisted__Bool_2376 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2376;
        { Bool _ret_val = hoisted__Bool_2376;
                return _ret_val; }
    }
    Bool hoisted__Bool_2385 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2385;
    if (hoisted__Bool_2385) {
        Bool hoisted__Bool_2377 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2377;
        { Bool _ret_val = hoisted__Bool_2377;
                return _ret_val; }
    }
    Bool hoisted__Bool_2386 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2386;
    if (hoisted__Bool_2386) {
        Bool hoisted__Bool_2378 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2378;
        { Bool _ret_val = hoisted__Bool_2378;
                return _ret_val; }
    }
    Bool hoisted__Bool_2387 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2387;
    if (hoisted__Bool_2387) {
        Bool hoisted__Bool_2379 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2379;
        { Bool _ret_val = hoisted__Bool_2379;
                return _ret_val; }
    }
    Bool hoisted__Bool_2388 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2388;
    if (hoisted__Bool_2388) {
        Bool hoisted__Bool_2380 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2380;
        { Bool _ret_val = hoisted__Bool_2380;
                return _ret_val; }
    }
    Bool hoisted__Bool_2389 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2389;
    if (hoisted__Bool_2389) {
        Bool hoisted__Bool_2381 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2381;
        { Bool _ret_val = hoisted__Bool_2381;
                return _ret_val; }
    }
    Bool hoisted__Bool_2390 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2390;
    if (hoisted__Bool_2390) {
        Bool hoisted__Bool_2382 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2382;
        { Bool _ret_val = hoisted__Bool_2382;
                return _ret_val; }
    }
    Bool hoisted__Bool_2391 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2391;
    if (hoisted__Bool_2391) {
        Bool hoisted__Bool_2383 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2383;
        { Bool _ret_val = hoisted__Bool_2383;
                return _ret_val; }
    }
    Bool hoisted__Bool_2392 = 0;
    (void)hoisted__Bool_2392;
    return hoisted__Bool_2392;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2410 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2410;
    if (hoisted__Bool_2410) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2411 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2411;
    if (hoisted__Bool_2411) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2412 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2412;
    if (hoisted__Bool_2412) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2413 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2413;
    if (hoisted__Bool_2413) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2414 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2414;
    if (hoisted__Bool_2414) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2415 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2415;
    if (hoisted__Bool_2415) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2416 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2416;
    if (hoisted__Bool_2416) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2417 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2417;
    if (hoisted__Bool_2417) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2418 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2418;
    UNREACHABLE(&hoisted__Str_2418);
    Str_delete(&hoisted__Str_2418, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2419 = 4;
    (void)hoisted__U32_2419;
    return hoisted__U32_2419;
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
    Bool hoisted__Bool_2424 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2424;
    if (hoisted__Bool_2424) {
        Bool hoisted__Bool_2421 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2421;
        { Bool _ret_val = hoisted__Bool_2421;
                return _ret_val; }
    }
    Bool hoisted__Bool_2425 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2425;
    if (hoisted__Bool_2425) {
        Bool hoisted__Bool_2422 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2422;
        { Bool _ret_val = hoisted__Bool_2422;
                return _ret_val; }
    }
    Bool hoisted__Bool_2426 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2426;
    if (hoisted__Bool_2426) {
        Bool hoisted__Bool_2423 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2423;
        { Bool _ret_val = hoisted__Bool_2423;
                return _ret_val; }
    }
    Bool hoisted__Bool_2427 = 0;
    (void)hoisted__Bool_2427;
    return hoisted__Bool_2427;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2435 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2435;
    if (hoisted__Bool_2435) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2436 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2436;
    if (hoisted__Bool_2436) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2437 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2437;
    if (hoisted__Bool_2437) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2438 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2438;
    UNREACHABLE(&hoisted__Str_2438);
    Str_delete(&hoisted__Str_2438, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2439 = 4;
    (void)hoisted__U32_2439;
    return hoisted__U32_2439;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2441 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2441;
    Declaration *hoisted__Declaration_2442 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2442->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2442->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2442->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2442->is_mut = self->is_mut;
    hoisted__Declaration_2442->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2442->is_priv = self->is_priv;
    hoisted__Declaration_2442->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2442->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2442->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2442->default_value = hoisted__Expr_2441;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2442->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2442;
    return hoisted__Declaration_2442;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2443 = 0;
    (void)hoisted__Bool_2443;
    Str_delete(&self->name, hoisted__Bool_2443);
    Bool hoisted__Bool_2444 = 0;
    (void)hoisted__Bool_2444;
    Str_delete(&self->doc, hoisted__Bool_2444);
    Bool hoisted__Bool_2445 = 0;
    (void)hoisted__Bool_2445;
    Str_delete(&self->explicit_type, hoisted__Bool_2445);
    Bool hoisted__Bool_2446 = 0;
    (void)hoisted__Bool_2446;
    Bool_delete(&self->is_mut, hoisted__Bool_2446);
    Bool hoisted__Bool_2447 = 0;
    (void)hoisted__Bool_2447;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2447);
    Bool hoisted__Bool_2448 = 0;
    (void)hoisted__Bool_2448;
    Bool_delete(&self->is_priv, hoisted__Bool_2448);
    Bool hoisted__Bool_2449 = 0;
    (void)hoisted__Bool_2449;
    Bool_delete(&self->used, hoisted__Bool_2449);
    Bool hoisted__Bool_2450 = 0;
    (void)hoisted__Bool_2450;
    OwnType_delete(&self->own_type, hoisted__Bool_2450);
    Bool hoisted__Bool_2451 = 0;
    (void)hoisted__Bool_2451;
    Type_delete(&self->til_type, hoisted__Bool_2451);
    Bool hoisted__Bool_2452 = 1;
    (void)hoisted__Bool_2452;
    Expr_delete(self->default_value, hoisted__Bool_2452);
    Bool hoisted__Bool_2453 = 0;
    (void)hoisted__Bool_2453;
    Str_delete(&self->orig_name, hoisted__Bool_2453);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2454 = 104;
    (void)hoisted__U32_2454;
    return hoisted__U32_2454;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2456 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2456->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2456->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2456->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2456->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2456->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2456->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2456->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2456->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2456->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2456->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2456->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2456;
    return hoisted__FunctionDef_2456;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2457 = 0;
    (void)hoisted__Bool_2457;
    FuncType_delete(&self->func_type, hoisted__Bool_2457);
    Bool hoisted__Bool_2458 = 0;
    (void)hoisted__Bool_2458;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2458);
    Bool hoisted__Bool_2459 = 0;
    (void)hoisted__Bool_2459;
    Str_delete(&self->return_type, hoisted__Bool_2459);
    Bool hoisted__Bool_2460 = 0;
    (void)hoisted__Bool_2460;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2460);
    Bool hoisted__Bool_2461 = 0;
    (void)hoisted__Bool_2461;
    I32_delete(&self->variadic_index, hoisted__Bool_2461);
    Bool hoisted__Bool_2462 = 0;
    (void)hoisted__Bool_2462;
    I32_delete(&self->kwargs_index, hoisted__Bool_2462);
    Bool hoisted__Bool_2463 = 0;
    (void)hoisted__Bool_2463;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2463);
    Bool hoisted__Bool_2464 = 0;
    (void)hoisted__Bool_2464;
    Bool_delete(&self->auto_generated, hoisted__Bool_2464);
    Bool hoisted__Bool_2465 = 0;
    (void)hoisted__Bool_2465;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2465);
    Bool hoisted__Bool_2466 = 0;
    (void)hoisted__Bool_2466;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2466);
    Bool hoisted__Bool_2467 = 0;
    (void)hoisted__Bool_2467;
    Str_delete(&self->closure_name, hoisted__Bool_2467);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2468 = 0;
    (void)hoisted__U32_2468;
    U64 hoisted__U64_2469 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2468); });
    (void)hoisted__U64_2469;
    return hoisted__U64_2469;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2470 = 104;
    (void)hoisted__U32_2470;
    return hoisted__U32_2470;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2473 = malloc(sizeof(FCallData));
    hoisted__FCallData_2473->is_splat = self->is_splat;
    hoisted__FCallData_2473->does_throw = self->does_throw;
    hoisted__FCallData_2473->is_bang = self->is_bang;
    hoisted__FCallData_2473->own_args = self->own_args;
    hoisted__FCallData_2473->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2473->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2473;
    return hoisted__FCallData_2473;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2474 = 0;
    (void)hoisted__Bool_2474;
    Bool_delete(&self->is_splat, hoisted__Bool_2474);
    Bool hoisted__Bool_2475 = 0;
    (void)hoisted__Bool_2475;
    Bool_delete(&self->does_throw, hoisted__Bool_2475);
    Bool hoisted__Bool_2476 = 0;
    (void)hoisted__Bool_2476;
    Bool_delete(&self->is_bang, hoisted__Bool_2476);
    Bool hoisted__Bool_2477 = 0;
    (void)hoisted__Bool_2477;
    U64_delete(&self->own_args, hoisted__Bool_2477);
    Bool hoisted__Bool_2478 = 0;
    (void)hoisted__Bool_2478;
    Bool_delete(&self->swap_replace, hoisted__Bool_2478);
    Bool hoisted__Bool_2479 = 0;
    (void)hoisted__Bool_2479;
    Type_delete(&self->til_type, hoisted__Bool_2479);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2480 = 0;
    (void)hoisted__U32_2480;
    U64 hoisted__U64_2481 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2480); });
    (void)hoisted__U64_2481;
    return hoisted__U64_2481;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2482 = 48;
    (void)hoisted__U32_2482;
    return hoisted__U32_2482;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2494 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2494->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2494->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2494;
    return hoisted__LiteralNumData_2494;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2495 = 0;
    (void)hoisted__Bool_2495;
    Str_delete(&self->text, hoisted__Bool_2495);
    Bool hoisted__Bool_2496 = 0;
    (void)hoisted__Bool_2496;
    Type_delete(&self->til_type, hoisted__Bool_2496);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2497 = 0;
    (void)hoisted__U32_2497;
    U64 hoisted__U64_2498 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2497); });
    (void)hoisted__U64_2498;
    return hoisted__U64_2498;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2499 = 40;
    (void)hoisted__U32_2499;
    return hoisted__U32_2499;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2510 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2510->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2510->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2510;
    return hoisted__IdentData_2510;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2511 = 0;
    (void)hoisted__Bool_2511;
    Str_delete(&self->name, hoisted__Bool_2511);
    Bool hoisted__Bool_2512 = 0;
    (void)hoisted__Bool_2512;
    Type_delete(&self->til_type, hoisted__Bool_2512);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2513 = 0;
    (void)hoisted__U32_2513;
    U64 hoisted__U64_2514 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2513); });
    (void)hoisted__U64_2514;
    return hoisted__U64_2514;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2515 = 40;
    (void)hoisted__U32_2515;
    return hoisted__U32_2515;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2522 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2522->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2522->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2522;
    return hoisted__FieldAccessData_2522;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2523 = 0;
    (void)hoisted__Bool_2523;
    Str_delete(&self->name, hoisted__Bool_2523);
    Bool hoisted__Bool_2524 = 0;
    (void)hoisted__Bool_2524;
    Type_delete(&self->til_type, hoisted__Bool_2524);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2525 = 0;
    (void)hoisted__U32_2525;
    U64 hoisted__U64_2526 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2525); });
    (void)hoisted__U64_2526;
    return hoisted__U64_2526;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2527 = 40;
    (void)hoisted__U32_2527;
    return hoisted__U32_2527;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2602 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2602->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2602->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2602->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2602->is_interface = self->is_interface;
    hoisted__StructDef_2602->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2602->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2602;
    return hoisted__StructDef_2602;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    Str_delete(&self->c_tag, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    Bool_delete(&self->is_interface, hoisted__Bool_2606);
    Bool hoisted__Bool_2607 = 0;
    (void)hoisted__Bool_2607;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2607);
    Bool hoisted__Bool_2608 = 0;
    (void)hoisted__Bool_2608;
    Str_delete(&self->implements_name, hoisted__Bool_2608);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2609 = 0;
    (void)hoisted__U32_2609;
    U64 hoisted__U64_2610 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2609); });
    (void)hoisted__U64_2610;
    return hoisted__U64_2610;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2611 = 72;
    (void)hoisted__U32_2611;
    return hoisted__U32_2611;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2616 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2616->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2616->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2616->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2616->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2616->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2616;
    return hoisted__EnumDef_2616;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2617 = 0;
    (void)hoisted__Bool_2617;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2617);
    Bool hoisted__Bool_2618 = 0;
    (void)hoisted__Bool_2618;
    Vec__Str_delete(&self->variants, hoisted__Bool_2618);
    Bool hoisted__Bool_2619 = 0;
    (void)hoisted__Bool_2619;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2619);
    Bool hoisted__Bool_2620 = 0;
    (void)hoisted__Bool_2620;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2620);
    Bool hoisted__Bool_2621 = 0;
    (void)hoisted__Bool_2621;
    Str_delete(&self->implements_name, hoisted__Bool_2621);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2622 = 0;
    (void)hoisted__U32_2622;
    U64 hoisted__U64_2623 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2622); });
    (void)hoisted__U64_2623;
    return hoisted__U64_2623;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2624 = 96;
    (void)hoisted__U32_2624;
    return hoisted__U32_2624;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2720 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2720->name = *_ca; free(_ca); }
    hoisted__AssignData_2720->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2720->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2720->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2720;
    return hoisted__AssignData_2720;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Str_delete(&self->name, hoisted__Bool_2721);
    Bool hoisted__Bool_2722 = 0;
    (void)hoisted__Bool_2722;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2722);
    Bool hoisted__Bool_2723 = 0;
    (void)hoisted__Bool_2723;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2723);
    Bool hoisted__Bool_2724 = 0;
    (void)hoisted__Bool_2724;
    Bool_delete(&self->swap_replace, hoisted__Bool_2724);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2725 = 0;
    (void)hoisted__U32_2725;
    U64 hoisted__U64_2726 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2725); });
    (void)hoisted__U64_2726;
    return hoisted__U64_2726;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2727 = 24;
    (void)hoisted__U32_2727;
    return hoisted__U32_2727;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2729 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2729->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2729->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2729;
    return hoisted__FieldAssignData_2729;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2730 = 0;
    (void)hoisted__Bool_2730;
    Str_delete(&self->name, hoisted__Bool_2730);
    Bool hoisted__Bool_2731 = 0;
    (void)hoisted__Bool_2731;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2731);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2732 = 0;
    (void)hoisted__U32_2732;
    U64 hoisted__U64_2733 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2732); });
    (void)hoisted__U64_2733;
    return hoisted__U64_2733;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2734 = 24;
    (void)hoisted__U32_2734;
    return hoisted__U32_2734;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2736 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2736->name = *_ca; free(_ca); }
    hoisted__ForInData_2736->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2736->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2736;
    return hoisted__ForInData_2736;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Str_delete(&self->name, hoisted__Bool_2737);
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Bool_delete(&self->is_mut, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Type_delete(&self->til_type, hoisted__Bool_2739);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2740 = 0;
    (void)hoisted__U32_2740;
    U64 hoisted__U64_2741 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2740); });
    (void)hoisted__U64_2741;
    return hoisted__U64_2741;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2742 = 48;
    (void)hoisted__U32_2742;
    return hoisted__U32_2742;
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
    Bool hoisted__Bool_2772 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2772;
    if (hoisted__Bool_2772) {
        Str *hoisted__Str_2766 = get_payload(self);
        (void)hoisted__Str_2766;
        (void)hoisted__Str_2766;
        Bool hoisted__Bool_2767 = 0;
        (void)hoisted__Bool_2767;
        Str_delete(hoisted__Str_2766, hoisted__Bool_2767);
    }
    Bool hoisted__Bool_2773 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2773;
    if (hoisted__Bool_2773) {
        LiteralNumData *hoisted__LiteralNumData_2768 = get_payload(self);
        (void)hoisted__LiteralNumData_2768;
        (void)hoisted__LiteralNumData_2768;
        Bool hoisted__Bool_2769 = 0;
        (void)hoisted__Bool_2769;
        LiteralNumData_delete(hoisted__LiteralNumData_2768, hoisted__Bool_2769);
    }
    Bool hoisted__Bool_2774 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2774;
    if (hoisted__Bool_2774) {
        Bool *hoisted__Bool_2770 = get_payload(self);
        (void)hoisted__Bool_2770;
        (void)hoisted__Bool_2770;
        Bool hoisted__Bool_2771 = 0;
        (void)hoisted__Bool_2771;
        Bool_delete(hoisted__Bool_2770, hoisted__Bool_2771);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2814 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2814;
    if (hoisted__Bool_2814) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2809 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2809;
        Literal *hoisted__Literal_2810 = Literal_Str(hoisted__Str_2809);
        (void)hoisted__Literal_2810;
        { Literal * _ret_val = hoisted__Literal_2810;
                return _ret_val; }
    }
    Bool hoisted__Bool_2815 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2815;
    if (hoisted__Bool_2815) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2811 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2811;
        Literal *hoisted__Literal_2812 = Literal_Num(hoisted__LiteralNumData_2811);
        (void)hoisted__Literal_2812;
        { Literal * _ret_val = hoisted__Literal_2812;
                return _ret_val; }
    }
    Bool hoisted__Bool_2816 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2816;
    if (hoisted__Bool_2816) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2813 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2813;
        { Literal * _ret_val = hoisted__Literal_2813;
                return _ret_val; }
    }
    Bool hoisted__Bool_2817 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2817;
    if (hoisted__Bool_2817) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2818 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2818;
    if (hoisted__Bool_2818) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2819 = 48;
    (void)hoisted__U32_2819;
    return hoisted__U32_2819;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2822 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2822->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2822->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2822;
    return hoisted__MatchData_2822;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2823 = 0;
    (void)hoisted__Bool_2823;
    Type_delete(&self->til_type, hoisted__Bool_2823);
    Bool hoisted__Bool_2824 = 0;
    (void)hoisted__Bool_2824;
    Str_delete(&self->result_temp, hoisted__Bool_2824);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2825 = 0;
    (void)hoisted__U32_2825;
    U64 hoisted__U64_2826 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2825); });
    (void)hoisted__U64_2826;
    return hoisted__U64_2826;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2827 = 40;
    (void)hoisted__U32_2827;
    return hoisted__U32_2827;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2832 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2832->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2832;
    return hoisted__CaptureBlockData_2832;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2833 = 0;
    (void)hoisted__Bool_2833;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2833);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2834 = 0;
    (void)hoisted__U32_2834;
    U64 hoisted__U64_2835 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2834); });
    (void)hoisted__U64_2835;
    return hoisted__U64_2835;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2836 = 16;
    (void)hoisted__U32_2836;
    return hoisted__U32_2836;
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
    Bool hoisted__Bool_3015 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3015;
    if (hoisted__Bool_3015) {
        Literal *hoisted__Literal_2987 = get_payload(self);
        (void)hoisted__Literal_2987;
        (void)hoisted__Literal_2987;
        Bool hoisted__Bool_2988 = 0;
        (void)hoisted__Bool_2988;
        Literal_delete(hoisted__Literal_2987, hoisted__Bool_2988);
    }
    Bool hoisted__Bool_3016 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3016;
    if (hoisted__Bool_3016) {
        IdentData *hoisted__IdentData_2989 = get_payload(self);
        (void)hoisted__IdentData_2989;
        (void)hoisted__IdentData_2989;
        Bool hoisted__Bool_2990 = 0;
        (void)hoisted__Bool_2990;
        IdentData_delete(hoisted__IdentData_2989, hoisted__Bool_2990);
    }
    Bool hoisted__Bool_3017 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3017;
    if (hoisted__Bool_3017) {
        Declaration *hoisted__Declaration_2991 = get_payload(self);
        (void)hoisted__Declaration_2991;
        (void)hoisted__Declaration_2991;
        Bool hoisted__Bool_2992 = 0;
        (void)hoisted__Bool_2992;
        Declaration_delete(hoisted__Declaration_2991, hoisted__Bool_2992);
    }
    Bool hoisted__Bool_3018 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3018;
    if (hoisted__Bool_3018) {
        AssignData *hoisted__AssignData_2993 = get_payload(self);
        (void)hoisted__AssignData_2993;
        (void)hoisted__AssignData_2993;
        Bool hoisted__Bool_2994 = 0;
        (void)hoisted__Bool_2994;
        AssignData_delete(hoisted__AssignData_2993, hoisted__Bool_2994);
    }
    Bool hoisted__Bool_3019 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3019;
    if (hoisted__Bool_3019) {
        FCallData *hoisted__FCallData_2995 = get_payload(self);
        (void)hoisted__FCallData_2995;
        (void)hoisted__FCallData_2995;
        Bool hoisted__Bool_2996 = 0;
        (void)hoisted__Bool_2996;
        FCallData_delete(hoisted__FCallData_2995, hoisted__Bool_2996);
    }
    Bool hoisted__Bool_3020 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3020;
    if (hoisted__Bool_3020) {
        FunctionDef *hoisted__FunctionDef_2997 = get_payload(self);
        (void)hoisted__FunctionDef_2997;
        (void)hoisted__FunctionDef_2997;
        Bool hoisted__Bool_2998 = 0;
        (void)hoisted__Bool_2998;
        FunctionDef_delete(hoisted__FunctionDef_2997, hoisted__Bool_2998);
    }
    Bool hoisted__Bool_3021 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3021;
    if (hoisted__Bool_3021) {
        StructDef *hoisted__StructDef_2999 = get_payload(self);
        (void)hoisted__StructDef_2999;
        (void)hoisted__StructDef_2999;
        Bool hoisted__Bool_3000 = 0;
        (void)hoisted__Bool_3000;
        StructDef_delete(hoisted__StructDef_2999, hoisted__Bool_3000);
    }
    Bool hoisted__Bool_3022 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3022;
    if (hoisted__Bool_3022) {
        EnumDef *hoisted__EnumDef_3001 = get_payload(self);
        (void)hoisted__EnumDef_3001;
        (void)hoisted__EnumDef_3001;
        Bool hoisted__Bool_3002 = 0;
        (void)hoisted__Bool_3002;
        EnumDef_delete(hoisted__EnumDef_3001, hoisted__Bool_3002);
    }
    Bool hoisted__Bool_3023 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3023;
    if (hoisted__Bool_3023) {
        FieldAccessData *hoisted__FieldAccessData_3003 = get_payload(self);
        (void)hoisted__FieldAccessData_3003;
        (void)hoisted__FieldAccessData_3003;
        Bool hoisted__Bool_3004 = 0;
        (void)hoisted__Bool_3004;
        FieldAccessData_delete(hoisted__FieldAccessData_3003, hoisted__Bool_3004);
    }
    Bool hoisted__Bool_3024 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3024;
    if (hoisted__Bool_3024) {
        FieldAssignData *hoisted__FieldAssignData_3005 = get_payload(self);
        (void)hoisted__FieldAssignData_3005;
        (void)hoisted__FieldAssignData_3005;
        Bool hoisted__Bool_3006 = 0;
        (void)hoisted__Bool_3006;
        FieldAssignData_delete(hoisted__FieldAssignData_3005, hoisted__Bool_3006);
    }
    Bool hoisted__Bool_3025 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3025;
    if (hoisted__Bool_3025) {
        ForInData *hoisted__ForInData_3007 = get_payload(self);
        (void)hoisted__ForInData_3007;
        (void)hoisted__ForInData_3007;
        Bool hoisted__Bool_3008 = 0;
        (void)hoisted__Bool_3008;
        ForInData_delete(hoisted__ForInData_3007, hoisted__Bool_3008);
    }
    Bool hoisted__Bool_3026 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3026;
    if (hoisted__Bool_3026) {
        Str *hoisted__Str_3009 = get_payload(self);
        (void)hoisted__Str_3009;
        (void)hoisted__Str_3009;
        Bool hoisted__Bool_3010 = 0;
        (void)hoisted__Bool_3010;
        Str_delete(hoisted__Str_3009, hoisted__Bool_3010);
    }
    Bool hoisted__Bool_3027 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3027;
    if (hoisted__Bool_3027) {
        MatchData *hoisted__MatchData_3011 = get_payload(self);
        (void)hoisted__MatchData_3011;
        (void)hoisted__MatchData_3011;
        Bool hoisted__Bool_3012 = 0;
        (void)hoisted__Bool_3012;
        MatchData_delete(hoisted__MatchData_3011, hoisted__Bool_3012);
    }
    Bool hoisted__Bool_3028 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3028;
    if (hoisted__Bool_3028) {
        CaptureBlockData *hoisted__CaptureBlockData_3013 = get_payload(self);
        (void)hoisted__CaptureBlockData_3013;
        (void)hoisted__CaptureBlockData_3013;
        Bool hoisted__Bool_3014 = 0;
        (void)hoisted__Bool_3014;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3013, hoisted__Bool_3014);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3210 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3210;
    if (hoisted__Bool_3210) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3211 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3211;
    if (hoisted__Bool_3211) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3182 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3182;
        NodeType *hoisted__NodeType_3183 = NodeType_Literal(hoisted__Literal_3182);
        (void)hoisted__NodeType_3183;
        { NodeType * _ret_val = hoisted__NodeType_3183;
                return _ret_val; }
    }
    Bool hoisted__Bool_3212 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3212;
    if (hoisted__Bool_3212) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3184 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3184;
        NodeType *hoisted__NodeType_3185 = NodeType_Ident(hoisted__IdentData_3184);
        (void)hoisted__NodeType_3185;
        { NodeType * _ret_val = hoisted__NodeType_3185;
                return _ret_val; }
    }
    Bool hoisted__Bool_3213 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3213;
    if (hoisted__Bool_3213) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3186 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3186;
        NodeType *hoisted__NodeType_3187 = NodeType_Decl(hoisted__Declaration_3186);
        (void)hoisted__NodeType_3187;
        { NodeType * _ret_val = hoisted__NodeType_3187;
                return _ret_val; }
    }
    Bool hoisted__Bool_3214 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3214;
    if (hoisted__Bool_3214) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3188 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3188;
        NodeType *hoisted__NodeType_3189 = NodeType_Assign(hoisted__AssignData_3188);
        (void)hoisted__NodeType_3189;
        { NodeType * _ret_val = hoisted__NodeType_3189;
                return _ret_val; }
    }
    Bool hoisted__Bool_3215 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3215;
    if (hoisted__Bool_3215) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3190 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3190;
        NodeType *hoisted__NodeType_3191 = NodeType_FCall(hoisted__FCallData_3190);
        (void)hoisted__NodeType_3191;
        { NodeType * _ret_val = hoisted__NodeType_3191;
                return _ret_val; }
    }
    Bool hoisted__Bool_3216 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3216;
    if (hoisted__Bool_3216) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3192 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3192;
        NodeType *hoisted__NodeType_3193 = NodeType_FuncDef(hoisted__FunctionDef_3192);
        (void)hoisted__NodeType_3193;
        { NodeType * _ret_val = hoisted__NodeType_3193;
                return _ret_val; }
    }
    Bool hoisted__Bool_3217 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3217;
    if (hoisted__Bool_3217) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3194 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3194;
        NodeType *hoisted__NodeType_3195 = NodeType_StructDef(hoisted__StructDef_3194);
        (void)hoisted__NodeType_3195;
        { NodeType * _ret_val = hoisted__NodeType_3195;
                return _ret_val; }
    }
    Bool hoisted__Bool_3218 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3218;
    if (hoisted__Bool_3218) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3196 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3196;
        NodeType *hoisted__NodeType_3197 = NodeType_EnumDef(hoisted__EnumDef_3196);
        (void)hoisted__NodeType_3197;
        { NodeType * _ret_val = hoisted__NodeType_3197;
                return _ret_val; }
    }
    Bool hoisted__Bool_3219 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3219;
    if (hoisted__Bool_3219) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3198 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3198;
        NodeType *hoisted__NodeType_3199 = NodeType_FieldAccess(hoisted__FieldAccessData_3198);
        (void)hoisted__NodeType_3199;
        { NodeType * _ret_val = hoisted__NodeType_3199;
                return _ret_val; }
    }
    Bool hoisted__Bool_3220 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3220;
    if (hoisted__Bool_3220) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3200 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3200;
        NodeType *hoisted__NodeType_3201 = NodeType_FieldAssign(hoisted__FieldAssignData_3200);
        (void)hoisted__NodeType_3201;
        { NodeType * _ret_val = hoisted__NodeType_3201;
                return _ret_val; }
    }
    Bool hoisted__Bool_3221 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3221;
    if (hoisted__Bool_3221) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3222 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3222;
    if (hoisted__Bool_3222) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3223 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3223;
    if (hoisted__Bool_3223) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3224 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3224;
    if (hoisted__Bool_3224) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3202 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3202;
        NodeType *hoisted__NodeType_3203 = NodeType_ForIn(hoisted__ForInData_3202);
        (void)hoisted__NodeType_3203;
        { NodeType * _ret_val = hoisted__NodeType_3203;
                return _ret_val; }
    }
    Bool hoisted__Bool_3225 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3225;
    if (hoisted__Bool_3225) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3204 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3204;
        NodeType *hoisted__NodeType_3205 = NodeType_NamedArg(hoisted__Str_3204);
        (void)hoisted__NodeType_3205;
        { NodeType * _ret_val = hoisted__NodeType_3205;
                return _ret_val; }
    }
    Bool hoisted__Bool_3226 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3226;
    if (hoisted__Bool_3226) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3227 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3227;
    if (hoisted__Bool_3227) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3228 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3228;
    if (hoisted__Bool_3228) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3229 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3229;
    if (hoisted__Bool_3229) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3206 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3206;
        NodeType *hoisted__NodeType_3207 = NodeType_Match(hoisted__MatchData_3206);
        (void)hoisted__NodeType_3207;
        { NodeType * _ret_val = hoisted__NodeType_3207;
                return _ret_val; }
    }
    Bool hoisted__Bool_3230 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3230;
    if (hoisted__Bool_3230) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3231 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3231;
    if (hoisted__Bool_3231) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3232 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3232;
    if (hoisted__Bool_3232) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3233 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3233;
    if (hoisted__Bool_3233) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3234 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3234;
    if (hoisted__Bool_3234) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3235 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3235;
    if (hoisted__Bool_3235) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3208 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3208;
        NodeType *hoisted__NodeType_3209 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3208);
        (void)hoisted__NodeType_3209;
        { NodeType * _ret_val = hoisted__NodeType_3209;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3236 = 112;
    (void)hoisted__U32_3236;
    return hoisted__U32_3236;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3237 = is_null(self);
    (void)hoisted__Bool_3237;
    if (hoisted__Bool_3237) {
        return;
    }
    Bool hoisted__Bool_3238 = 0;
    (void)hoisted__Bool_3238;
    NodeType_delete(&self->node_type, hoisted__Bool_3238);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3282 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3282->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3282->children = *_ca; free(_ca); }
    hoisted__Expr_3282->line = line;
    hoisted__Expr_3282->col = col;
    (void)hoisted__Expr_3282;
    return hoisted__Expr_3282;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3290 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3290->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3290->children = *_ca; free(_ca); }
    hoisted__Expr_3290->line = self->line;
    hoisted__Expr_3290->col = self->col;
    (void)hoisted__Expr_3290;
    return hoisted__Expr_3290;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3291 = 0;
    (void)hoisted__U32_3291;
    U64 hoisted__U64_3292 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3291); });
    (void)hoisted__U64_3292;
    return hoisted__U64_3292;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3293 = 136;
    (void)hoisted__U32_3293;
    return hoisted__U32_3293;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_3903 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_3903->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_3903->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3903;
    return hoisted__Map__I64_Str_3903;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4048 = 0;
    (void)hoisted__Bool_4048;
    Vec__I64_delete(&self->keys, hoisted__Bool_4048);
    Bool hoisted__Bool_4049 = 0;
    (void)hoisted__Bool_4049;
    Vec__Str_delete(&self->values, hoisted__Bool_4049);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4050 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4050->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4050->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4050;
    return hoisted__Map__I64_Str_4050;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4051 = 0;
    (void)hoisted__U32_4051;
    U64 hoisted__U64_4052 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4051); });
    (void)hoisted__U64_4052;
    return hoisted__U64_4052;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4053 = 32;
    (void)hoisted__U32_4053;
    return hoisted__U32_4053;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4054 = 1;
    (void)hoisted__U32_4054;
    Type *hoisted__Type_4055 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4055;
    U64 hoisted__U64_4056 = (U64)(hoisted__U32_4054);
    (void)hoisted__U64_4056;
    Type_delete(hoisted__Type_4055, 1);
    void * hoisted__v_4057 = malloc(hoisted__U64_4056);
    (void)hoisted__v_4057;
    U32 hoisted__U32_4058 = 0;
    (void)hoisted__U32_4058;
    I64 hoisted__I64_4059 = 1;
    (void)hoisted__I64_4059;
    Vec__Bool *hoisted__Vec__Bool_4060 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4060->data = hoisted__v_4057;
    hoisted__Vec__Bool_4060->count = hoisted__U32_4058;
    hoisted__Vec__Bool_4060->cap = hoisted__I64_4059;
    (void)hoisted__Vec__Bool_4060;
    return hoisted__Vec__Bool_4060;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4061 = self->count;
        (void)_re_U32_4061;
        U32 _rc_U32_4061 = 0;
        (void)_rc_U32_4061;
        Bool hoisted__Bool_4076 = U32_lte(_rc_U32_4061, _re_U32_4061);
        (void)hoisted__Bool_4076;
        if (hoisted__Bool_4076) {
            while (1) {
                Bool _wcond_Bool_4062 = U32_lt(_rc_U32_4061, _re_U32_4061);
                (void)_wcond_Bool_4062;
                if (_wcond_Bool_4062) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4061);
                U32_inc(&_rc_U32_4061);
                U32 hoisted__U32_4063 = 1;
                (void)hoisted__U32_4063;
                U32 hoisted__U32_4064 = U32_mul(i, hoisted__U32_4063);
                (void)hoisted__U32_4064;
                Type *hoisted__Type_4065 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4065;
                U64 hoisted__U64_4066 = (U64)(hoisted__U32_4064);
                (void)hoisted__U64_4066;
                Type_delete(hoisted__Type_4065, 1);
                Bool *hoisted__Bool_4067 = ptr_add(self->data, hoisted__U64_4066);
                (void)hoisted__Bool_4067;
                (void)hoisted__Bool_4067;
                Bool hoisted__Bool_4068 = 0;
                (void)hoisted__Bool_4068;
                Bool_delete(hoisted__Bool_4067, hoisted__Bool_4068);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4069 = U32_gt(_rc_U32_4061, _re_U32_4061);
                (void)_wcond_Bool_4069;
                if (_wcond_Bool_4069) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4061);
                U32_dec(&_rc_U32_4061);
                U32 hoisted__U32_4070 = 1;
                (void)hoisted__U32_4070;
                U32 hoisted__U32_4071 = U32_mul(i, hoisted__U32_4070);
                (void)hoisted__U32_4071;
                Type *hoisted__Type_4072 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4072;
                U64 hoisted__U64_4073 = (U64)(hoisted__U32_4071);
                (void)hoisted__U64_4073;
                Type_delete(hoisted__Type_4072, 1);
                Bool *hoisted__Bool_4074 = ptr_add(self->data, hoisted__U64_4073);
                (void)hoisted__Bool_4074;
                (void)hoisted__Bool_4074;
                Bool hoisted__Bool_4075 = 0;
                (void)hoisted__Bool_4075;
                Bool_delete(hoisted__Bool_4074, hoisted__Bool_4075);
            }
        }
    }
    U32 hoisted__U32_4077 = 0;
    (void)hoisted__U32_4077;
    self->count = hoisted__U32_4077;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4370 = 1;
    (void)hoisted__U32_4370;
    U32 hoisted__U32_4371 = U32_mul(self->cap, hoisted__U32_4370);
    (void)hoisted__U32_4371;
    Type *hoisted__Type_4372 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4372;
    U64 hoisted__U64_4373 = (U64)(hoisted__U32_4371);
    (void)hoisted__U64_4373;
    Type_delete(hoisted__Type_4372, 1);
    void * new_data = malloc(hoisted__U64_4373);
    {
        U32 _re_U32_4334 = self->count;
        (void)_re_U32_4334;
        U32 _rc_U32_4334 = 0;
        (void)_rc_U32_4334;
        Bool hoisted__Bool_4369 = U32_lte(_rc_U32_4334, _re_U32_4334);
        (void)hoisted__Bool_4369;
        if (hoisted__Bool_4369) {
            while (1) {
                Bool _wcond_Bool_4335 = U32_lt(_rc_U32_4334, _re_U32_4334);
                (void)_wcond_Bool_4335;
                if (_wcond_Bool_4335) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4334);
                U32_inc(&_rc_U32_4334);
                U32 hoisted__U32_4336 = 1;
                (void)hoisted__U32_4336;
                U32 hoisted__U32_4337 = U32_mul(i, hoisted__U32_4336);
                (void)hoisted__U32_4337;
                Type *hoisted__Type_4338 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4338;
                U64 hoisted__U64_4339 = (U64)(hoisted__U32_4337);
                (void)hoisted__U64_4339;
                Type_delete(hoisted__Type_4338, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4339);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4340 = 1;
                (void)hoisted__U32_4340;
                U32 hoisted__U32_4341 = U32_mul(i, hoisted__U32_4340);
                (void)hoisted__U32_4341;
                Type *hoisted__Type_4342 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4342;
                U64 hoisted__U64_4343 = (U64)(hoisted__U32_4341);
                (void)hoisted__U64_4343;
                Type_delete(hoisted__Type_4342, 1);
                U32 hoisted__U32_4344 = 1;
                (void)hoisted__U32_4344;
                Type *hoisted__Type_4345 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4345;
                void *hoisted__v_4346 = ptr_add(new_data, hoisted__U64_4343);
                (void)hoisted__v_4346;
                (void)hoisted__v_4346;
                U64 hoisted__U64_4347 = (U64)(hoisted__U32_4344);
                (void)hoisted__U64_4347;
                Type_delete(hoisted__Type_4345, 1);
                memcpy(hoisted__v_4346, &cloned, hoisted__U64_4347);
                U32 hoisted__U32_4348 = 1;
                (void)hoisted__U32_4348;
                Type *hoisted__Type_4349 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4349;
                I32 hoisted__I32_4350 = 0;
                (void)hoisted__I32_4350;
                U64 hoisted__U64_4351 = (U64)(hoisted__U32_4348);
                (void)hoisted__U64_4351;
                Type_delete(hoisted__Type_4349, 1);
                memset(&cloned, hoisted__I32_4350, hoisted__U64_4351);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4352 = U32_gt(_rc_U32_4334, _re_U32_4334);
                (void)_wcond_Bool_4352;
                if (_wcond_Bool_4352) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4334);
                U32_dec(&_rc_U32_4334);
                U32 hoisted__U32_4353 = 1;
                (void)hoisted__U32_4353;
                U32 hoisted__U32_4354 = U32_mul(i, hoisted__U32_4353);
                (void)hoisted__U32_4354;
                Type *hoisted__Type_4355 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4355;
                U64 hoisted__U64_4356 = (U64)(hoisted__U32_4354);
                (void)hoisted__U64_4356;
                Type_delete(hoisted__Type_4355, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4356);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4357 = 1;
                (void)hoisted__U32_4357;
                U32 hoisted__U32_4358 = U32_mul(i, hoisted__U32_4357);
                (void)hoisted__U32_4358;
                Type *hoisted__Type_4359 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4359;
                U64 hoisted__U64_4360 = (U64)(hoisted__U32_4358);
                (void)hoisted__U64_4360;
                Type_delete(hoisted__Type_4359, 1);
                U32 hoisted__U32_4361 = 1;
                (void)hoisted__U32_4361;
                Type *hoisted__Type_4362 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4362;
                void *hoisted__v_4363 = ptr_add(new_data, hoisted__U64_4360);
                (void)hoisted__v_4363;
                (void)hoisted__v_4363;
                U64 hoisted__U64_4364 = (U64)(hoisted__U32_4361);
                (void)hoisted__U64_4364;
                Type_delete(hoisted__Type_4362, 1);
                memcpy(hoisted__v_4363, &cloned, hoisted__U64_4364);
                U32 hoisted__U32_4365 = 1;
                (void)hoisted__U32_4365;
                Type *hoisted__Type_4366 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4366;
                I32 hoisted__I32_4367 = 0;
                (void)hoisted__I32_4367;
                U64 hoisted__U64_4368 = (U64)(hoisted__U32_4365);
                (void)hoisted__U64_4368;
                Type_delete(hoisted__Type_4366, 1);
                memset(&cloned, hoisted__I32_4367, hoisted__U64_4368);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4374 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4374->data = new_data;
    hoisted__Vec__Bool_4374->count = self->count;
    hoisted__Vec__Bool_4374->cap = self->cap;
    (void)hoisted__Vec__Bool_4374;
    return hoisted__Vec__Bool_4374;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4375 = 16;
    (void)hoisted__U32_4375;
    return hoisted__U32_4375;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_4698 = 104;
    (void)hoisted__U32_4698;
    Type *hoisted__Type_4699 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4699;
    U64 hoisted__U64_4700 = (U64)(hoisted__U32_4698);
    (void)hoisted__U64_4700;
    Type_delete(hoisted__Type_4699, 1);
    void * hoisted__v_4701 = malloc(hoisted__U64_4700);
    (void)hoisted__v_4701;
    U32 hoisted__U32_4702 = 0;
    (void)hoisted__U32_4702;
    I64 hoisted__I64_4703 = 1;
    (void)hoisted__I64_4703;
    Vec__Declaration *hoisted__Vec__Declaration_4704 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4704->data = hoisted__v_4701;
    hoisted__Vec__Declaration_4704->count = hoisted__U32_4702;
    hoisted__Vec__Declaration_4704->cap = hoisted__I64_4703;
    (void)hoisted__Vec__Declaration_4704;
    return hoisted__Vec__Declaration_4704;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4705 = self->count;
        (void)_re_U32_4705;
        U32 _rc_U32_4705 = 0;
        (void)_rc_U32_4705;
        Bool hoisted__Bool_4720 = U32_lte(_rc_U32_4705, _re_U32_4705);
        (void)hoisted__Bool_4720;
        if (hoisted__Bool_4720) {
            while (1) {
                Bool _wcond_Bool_4706 = U32_lt(_rc_U32_4705, _re_U32_4705);
                (void)_wcond_Bool_4706;
                if (_wcond_Bool_4706) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4705);
                U32_inc(&_rc_U32_4705);
                U32 hoisted__U32_4707 = 104;
                (void)hoisted__U32_4707;
                U32 hoisted__U32_4708 = U32_mul(i, hoisted__U32_4707);
                (void)hoisted__U32_4708;
                Type *hoisted__Type_4709 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4709;
                U64 hoisted__U64_4710 = (U64)(hoisted__U32_4708);
                (void)hoisted__U64_4710;
                Type_delete(hoisted__Type_4709, 1);
                Declaration *hoisted__Declaration_4711 = ptr_add(self->data, hoisted__U64_4710);
                (void)hoisted__Declaration_4711;
                (void)hoisted__Declaration_4711;
                Bool hoisted__Bool_4712 = 0;
                (void)hoisted__Bool_4712;
                Declaration_delete(hoisted__Declaration_4711, hoisted__Bool_4712);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4713 = U32_gt(_rc_U32_4705, _re_U32_4705);
                (void)_wcond_Bool_4713;
                if (_wcond_Bool_4713) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4705);
                U32_dec(&_rc_U32_4705);
                U32 hoisted__U32_4714 = 104;
                (void)hoisted__U32_4714;
                U32 hoisted__U32_4715 = U32_mul(i, hoisted__U32_4714);
                (void)hoisted__U32_4715;
                Type *hoisted__Type_4716 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4716;
                U64 hoisted__U64_4717 = (U64)(hoisted__U32_4715);
                (void)hoisted__U64_4717;
                Type_delete(hoisted__Type_4716, 1);
                Declaration *hoisted__Declaration_4718 = ptr_add(self->data, hoisted__U64_4717);
                (void)hoisted__Declaration_4718;
                (void)hoisted__Declaration_4718;
                Bool hoisted__Bool_4719 = 0;
                (void)hoisted__Bool_4719;
                Declaration_delete(hoisted__Declaration_4718, hoisted__Bool_4719);
            }
        }
    }
    U32 hoisted__U32_4721 = 0;
    (void)hoisted__U32_4721;
    self->count = hoisted__U32_4721;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5014 = 104;
    (void)hoisted__U32_5014;
    U32 hoisted__U32_5015 = U32_mul(self->cap, hoisted__U32_5014);
    (void)hoisted__U32_5015;
    Type *hoisted__Type_5016 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5016;
    U64 hoisted__U64_5017 = (U64)(hoisted__U32_5015);
    (void)hoisted__U64_5017;
    Type_delete(hoisted__Type_5016, 1);
    void * new_data = malloc(hoisted__U64_5017);
    {
        U32 _re_U32_4978 = self->count;
        (void)_re_U32_4978;
        U32 _rc_U32_4978 = 0;
        (void)_rc_U32_4978;
        Bool hoisted__Bool_5013 = U32_lte(_rc_U32_4978, _re_U32_4978);
        (void)hoisted__Bool_5013;
        if (hoisted__Bool_5013) {
            while (1) {
                Bool _wcond_Bool_4979 = U32_lt(_rc_U32_4978, _re_U32_4978);
                (void)_wcond_Bool_4979;
                if (_wcond_Bool_4979) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4978);
                U32_inc(&_rc_U32_4978);
                U32 hoisted__U32_4980 = 104;
                (void)hoisted__U32_4980;
                U32 hoisted__U32_4981 = U32_mul(i, hoisted__U32_4980);
                (void)hoisted__U32_4981;
                Type *hoisted__Type_4982 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4982;
                U64 hoisted__U64_4983 = (U64)(hoisted__U32_4981);
                (void)hoisted__U64_4983;
                Type_delete(hoisted__Type_4982, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_4983);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4984 = 104;
                (void)hoisted__U32_4984;
                U32 hoisted__U32_4985 = U32_mul(i, hoisted__U32_4984);
                (void)hoisted__U32_4985;
                Type *hoisted__Type_4986 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4986;
                U64 hoisted__U64_4987 = (U64)(hoisted__U32_4985);
                (void)hoisted__U64_4987;
                Type_delete(hoisted__Type_4986, 1);
                U32 hoisted__U32_4988 = 104;
                (void)hoisted__U32_4988;
                Type *hoisted__Type_4989 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4989;
                void *hoisted__v_4990 = ptr_add(new_data, hoisted__U64_4987);
                (void)hoisted__v_4990;
                (void)hoisted__v_4990;
                U64 hoisted__U64_4991 = (U64)(hoisted__U32_4988);
                (void)hoisted__U64_4991;
                Type_delete(hoisted__Type_4989, 1);
                memcpy(hoisted__v_4990, cloned, hoisted__U64_4991);
                U32 hoisted__U32_4992 = 104;
                (void)hoisted__U32_4992;
                Type *hoisted__Type_4993 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4993;
                I32 hoisted__I32_4994 = 0;
                (void)hoisted__I32_4994;
                U64 hoisted__U64_4995 = (U64)(hoisted__U32_4992);
                (void)hoisted__U64_4995;
                Type_delete(hoisted__Type_4993, 1);
                memset(cloned, hoisted__I32_4994, hoisted__U64_4995);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4996 = U32_gt(_rc_U32_4978, _re_U32_4978);
                (void)_wcond_Bool_4996;
                if (_wcond_Bool_4996) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4978);
                U32_dec(&_rc_U32_4978);
                U32 hoisted__U32_4997 = 104;
                (void)hoisted__U32_4997;
                U32 hoisted__U32_4998 = U32_mul(i, hoisted__U32_4997);
                (void)hoisted__U32_4998;
                Type *hoisted__Type_4999 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4999;
                U64 hoisted__U64_5000 = (U64)(hoisted__U32_4998);
                (void)hoisted__U64_5000;
                Type_delete(hoisted__Type_4999, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5000);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5001 = 104;
                (void)hoisted__U32_5001;
                U32 hoisted__U32_5002 = U32_mul(i, hoisted__U32_5001);
                (void)hoisted__U32_5002;
                Type *hoisted__Type_5003 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5003;
                U64 hoisted__U64_5004 = (U64)(hoisted__U32_5002);
                (void)hoisted__U64_5004;
                Type_delete(hoisted__Type_5003, 1);
                U32 hoisted__U32_5005 = 104;
                (void)hoisted__U32_5005;
                Type *hoisted__Type_5006 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5006;
                void *hoisted__v_5007 = ptr_add(new_data, hoisted__U64_5004);
                (void)hoisted__v_5007;
                (void)hoisted__v_5007;
                U64 hoisted__U64_5008 = (U64)(hoisted__U32_5005);
                (void)hoisted__U64_5008;
                Type_delete(hoisted__Type_5006, 1);
                memcpy(hoisted__v_5007, cloned, hoisted__U64_5008);
                U32 hoisted__U32_5009 = 104;
                (void)hoisted__U32_5009;
                Type *hoisted__Type_5010 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5010;
                I32 hoisted__I32_5011 = 0;
                (void)hoisted__I32_5011;
                U64 hoisted__U64_5012 = (U64)(hoisted__U32_5009);
                (void)hoisted__U64_5012;
                Type_delete(hoisted__Type_5010, 1);
                memset(cloned, hoisted__I32_5011, hoisted__U64_5012);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5018 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5018->data = new_data;
    hoisted__Vec__Declaration_5018->count = self->count;
    hoisted__Vec__Declaration_5018->cap = self->cap;
    (void)hoisted__Vec__Declaration_5018;
    return hoisted__Vec__Declaration_5018;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5019 = 16;
    (void)hoisted__U32_5019;
    return hoisted__U32_5019;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5020 = 136;
    (void)hoisted__U32_5020;
    Type *hoisted__Type_5021 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5021;
    U64 hoisted__U64_5022 = (U64)(hoisted__U32_5020);
    (void)hoisted__U64_5022;
    Type_delete(hoisted__Type_5021, 1);
    void * hoisted__v_5023 = malloc(hoisted__U64_5022);
    (void)hoisted__v_5023;
    U32 hoisted__U32_5024 = 0;
    (void)hoisted__U32_5024;
    I64 hoisted__I64_5025 = 1;
    (void)hoisted__I64_5025;
    Vec__Expr *hoisted__Vec__Expr_5026 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5026->data = hoisted__v_5023;
    hoisted__Vec__Expr_5026->count = hoisted__U32_5024;
    hoisted__Vec__Expr_5026->cap = hoisted__I64_5025;
    (void)hoisted__Vec__Expr_5026;
    return hoisted__Vec__Expr_5026;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5027 = self->count;
        (void)_re_U32_5027;
        U32 _rc_U32_5027 = 0;
        (void)_rc_U32_5027;
        Bool hoisted__Bool_5042 = U32_lte(_rc_U32_5027, _re_U32_5027);
        (void)hoisted__Bool_5042;
        if (hoisted__Bool_5042) {
            while (1) {
                Bool _wcond_Bool_5028 = U32_lt(_rc_U32_5027, _re_U32_5027);
                (void)_wcond_Bool_5028;
                if (_wcond_Bool_5028) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5027);
                U32_inc(&_rc_U32_5027);
                U32 hoisted__U32_5029 = 136;
                (void)hoisted__U32_5029;
                U32 hoisted__U32_5030 = U32_mul(i, hoisted__U32_5029);
                (void)hoisted__U32_5030;
                Type *hoisted__Type_5031 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5031;
                U64 hoisted__U64_5032 = (U64)(hoisted__U32_5030);
                (void)hoisted__U64_5032;
                Type_delete(hoisted__Type_5031, 1);
                Expr *hoisted__Expr_5033 = ptr_add(self->data, hoisted__U64_5032);
                (void)hoisted__Expr_5033;
                (void)hoisted__Expr_5033;
                Bool hoisted__Bool_5034 = 0;
                (void)hoisted__Bool_5034;
                Expr_delete(hoisted__Expr_5033, hoisted__Bool_5034);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5035 = U32_gt(_rc_U32_5027, _re_U32_5027);
                (void)_wcond_Bool_5035;
                if (_wcond_Bool_5035) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5027);
                U32_dec(&_rc_U32_5027);
                U32 hoisted__U32_5036 = 136;
                (void)hoisted__U32_5036;
                U32 hoisted__U32_5037 = U32_mul(i, hoisted__U32_5036);
                (void)hoisted__U32_5037;
                Type *hoisted__Type_5038 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5038;
                U64 hoisted__U64_5039 = (U64)(hoisted__U32_5037);
                (void)hoisted__U64_5039;
                Type_delete(hoisted__Type_5038, 1);
                Expr *hoisted__Expr_5040 = ptr_add(self->data, hoisted__U64_5039);
                (void)hoisted__Expr_5040;
                (void)hoisted__Expr_5040;
                Bool hoisted__Bool_5041 = 0;
                (void)hoisted__Bool_5041;
                Expr_delete(hoisted__Expr_5040, hoisted__Bool_5041);
            }
        }
    }
    U32 hoisted__U32_5043 = 0;
    (void)hoisted__U32_5043;
    self->count = hoisted__U32_5043;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5336 = 136;
    (void)hoisted__U32_5336;
    U32 hoisted__U32_5337 = U32_mul(self->cap, hoisted__U32_5336);
    (void)hoisted__U32_5337;
    Type *hoisted__Type_5338 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5338;
    U64 hoisted__U64_5339 = (U64)(hoisted__U32_5337);
    (void)hoisted__U64_5339;
    Type_delete(hoisted__Type_5338, 1);
    void * new_data = malloc(hoisted__U64_5339);
    {
        U32 _re_U32_5300 = self->count;
        (void)_re_U32_5300;
        U32 _rc_U32_5300 = 0;
        (void)_rc_U32_5300;
        Bool hoisted__Bool_5335 = U32_lte(_rc_U32_5300, _re_U32_5300);
        (void)hoisted__Bool_5335;
        if (hoisted__Bool_5335) {
            while (1) {
                Bool _wcond_Bool_5301 = U32_lt(_rc_U32_5300, _re_U32_5300);
                (void)_wcond_Bool_5301;
                if (_wcond_Bool_5301) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5300);
                U32_inc(&_rc_U32_5300);
                U32 hoisted__U32_5302 = 136;
                (void)hoisted__U32_5302;
                U32 hoisted__U32_5303 = U32_mul(i, hoisted__U32_5302);
                (void)hoisted__U32_5303;
                Type *hoisted__Type_5304 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5304;
                U64 hoisted__U64_5305 = (U64)(hoisted__U32_5303);
                (void)hoisted__U64_5305;
                Type_delete(hoisted__Type_5304, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5305);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5306 = 136;
                (void)hoisted__U32_5306;
                U32 hoisted__U32_5307 = U32_mul(i, hoisted__U32_5306);
                (void)hoisted__U32_5307;
                Type *hoisted__Type_5308 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5308;
                U64 hoisted__U64_5309 = (U64)(hoisted__U32_5307);
                (void)hoisted__U64_5309;
                Type_delete(hoisted__Type_5308, 1);
                U32 hoisted__U32_5310 = 136;
                (void)hoisted__U32_5310;
                Type *hoisted__Type_5311 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5311;
                void *hoisted__v_5312 = ptr_add(new_data, hoisted__U64_5309);
                (void)hoisted__v_5312;
                (void)hoisted__v_5312;
                U64 hoisted__U64_5313 = (U64)(hoisted__U32_5310);
                (void)hoisted__U64_5313;
                Type_delete(hoisted__Type_5311, 1);
                memcpy(hoisted__v_5312, cloned, hoisted__U64_5313);
                U32 hoisted__U32_5314 = 136;
                (void)hoisted__U32_5314;
                Type *hoisted__Type_5315 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5315;
                I32 hoisted__I32_5316 = 0;
                (void)hoisted__I32_5316;
                U64 hoisted__U64_5317 = (U64)(hoisted__U32_5314);
                (void)hoisted__U64_5317;
                Type_delete(hoisted__Type_5315, 1);
                memset(cloned, hoisted__I32_5316, hoisted__U64_5317);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5318 = U32_gt(_rc_U32_5300, _re_U32_5300);
                (void)_wcond_Bool_5318;
                if (_wcond_Bool_5318) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5300);
                U32_dec(&_rc_U32_5300);
                U32 hoisted__U32_5319 = 136;
                (void)hoisted__U32_5319;
                U32 hoisted__U32_5320 = U32_mul(i, hoisted__U32_5319);
                (void)hoisted__U32_5320;
                Type *hoisted__Type_5321 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5321;
                U64 hoisted__U64_5322 = (U64)(hoisted__U32_5320);
                (void)hoisted__U64_5322;
                Type_delete(hoisted__Type_5321, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5322);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5323 = 136;
                (void)hoisted__U32_5323;
                U32 hoisted__U32_5324 = U32_mul(i, hoisted__U32_5323);
                (void)hoisted__U32_5324;
                Type *hoisted__Type_5325 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5325;
                U64 hoisted__U64_5326 = (U64)(hoisted__U32_5324);
                (void)hoisted__U64_5326;
                Type_delete(hoisted__Type_5325, 1);
                U32 hoisted__U32_5327 = 136;
                (void)hoisted__U32_5327;
                Type *hoisted__Type_5328 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5328;
                void *hoisted__v_5329 = ptr_add(new_data, hoisted__U64_5326);
                (void)hoisted__v_5329;
                (void)hoisted__v_5329;
                U64 hoisted__U64_5330 = (U64)(hoisted__U32_5327);
                (void)hoisted__U64_5330;
                Type_delete(hoisted__Type_5328, 1);
                memcpy(hoisted__v_5329, cloned, hoisted__U64_5330);
                U32 hoisted__U32_5331 = 136;
                (void)hoisted__U32_5331;
                Type *hoisted__Type_5332 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5332;
                I32 hoisted__I32_5333 = 0;
                (void)hoisted__I32_5333;
                U64 hoisted__U64_5334 = (U64)(hoisted__U32_5331);
                (void)hoisted__U64_5334;
                Type_delete(hoisted__Type_5332, 1);
                memset(cloned, hoisted__I32_5333, hoisted__U64_5334);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5340 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5340->data = new_data;
    hoisted__Vec__Expr_5340->count = self->count;
    hoisted__Vec__Expr_5340->cap = self->cap;
    (void)hoisted__Vec__Expr_5340;
    return hoisted__Vec__Expr_5340;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5341 = 16;
    (void)hoisted__U32_5341;
    return hoisted__U32_5341;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5342 = 8;
    (void)hoisted__U32_5342;
    Type *hoisted__Type_5343 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5343;
    U64 hoisted__U64_5344 = (U64)(hoisted__U32_5342);
    (void)hoisted__U64_5344;
    Type_delete(hoisted__Type_5343, 1);
    void * hoisted__v_5345 = malloc(hoisted__U64_5344);
    (void)hoisted__v_5345;
    U32 hoisted__U32_5346 = 0;
    (void)hoisted__U32_5346;
    I64 hoisted__I64_5347 = 1;
    (void)hoisted__I64_5347;
    Vec__I64 *hoisted__Vec__I64_5348 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5348->data = hoisted__v_5345;
    hoisted__Vec__I64_5348->count = hoisted__U32_5346;
    hoisted__Vec__I64_5348->cap = hoisted__I64_5347;
    (void)hoisted__Vec__I64_5348;
    return hoisted__Vec__I64_5348;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5349 = self->count;
        (void)_re_U32_5349;
        U32 _rc_U32_5349 = 0;
        (void)_rc_U32_5349;
        Bool hoisted__Bool_5364 = U32_lte(_rc_U32_5349, _re_U32_5349);
        (void)hoisted__Bool_5364;
        if (hoisted__Bool_5364) {
            while (1) {
                Bool _wcond_Bool_5350 = U32_lt(_rc_U32_5349, _re_U32_5349);
                (void)_wcond_Bool_5350;
                if (_wcond_Bool_5350) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5349);
                U32_inc(&_rc_U32_5349);
                U32 hoisted__U32_5351 = 8;
                (void)hoisted__U32_5351;
                U32 hoisted__U32_5352 = U32_mul(i, hoisted__U32_5351);
                (void)hoisted__U32_5352;
                Type *hoisted__Type_5353 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5353;
                U64 hoisted__U64_5354 = (U64)(hoisted__U32_5352);
                (void)hoisted__U64_5354;
                Type_delete(hoisted__Type_5353, 1);
                I64 *hoisted__I64_5355 = ptr_add(self->data, hoisted__U64_5354);
                (void)hoisted__I64_5355;
                (void)hoisted__I64_5355;
                Bool hoisted__Bool_5356 = 0;
                (void)hoisted__Bool_5356;
                I64_delete(hoisted__I64_5355, hoisted__Bool_5356);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5357 = U32_gt(_rc_U32_5349, _re_U32_5349);
                (void)_wcond_Bool_5357;
                if (_wcond_Bool_5357) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5349);
                U32_dec(&_rc_U32_5349);
                U32 hoisted__U32_5358 = 8;
                (void)hoisted__U32_5358;
                U32 hoisted__U32_5359 = U32_mul(i, hoisted__U32_5358);
                (void)hoisted__U32_5359;
                Type *hoisted__Type_5360 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5360;
                U64 hoisted__U64_5361 = (U64)(hoisted__U32_5359);
                (void)hoisted__U64_5361;
                Type_delete(hoisted__Type_5360, 1);
                I64 *hoisted__I64_5362 = ptr_add(self->data, hoisted__U64_5361);
                (void)hoisted__I64_5362;
                (void)hoisted__I64_5362;
                Bool hoisted__Bool_5363 = 0;
                (void)hoisted__Bool_5363;
                I64_delete(hoisted__I64_5362, hoisted__Bool_5363);
            }
        }
    }
    U32 hoisted__U32_5365 = 0;
    (void)hoisted__U32_5365;
    self->count = hoisted__U32_5365;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5658 = 8;
    (void)hoisted__U32_5658;
    U32 hoisted__U32_5659 = U32_mul(self->cap, hoisted__U32_5658);
    (void)hoisted__U32_5659;
    Type *hoisted__Type_5660 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5660;
    U64 hoisted__U64_5661 = (U64)(hoisted__U32_5659);
    (void)hoisted__U64_5661;
    Type_delete(hoisted__Type_5660, 1);
    void * new_data = malloc(hoisted__U64_5661);
    {
        U32 _re_U32_5622 = self->count;
        (void)_re_U32_5622;
        U32 _rc_U32_5622 = 0;
        (void)_rc_U32_5622;
        Bool hoisted__Bool_5657 = U32_lte(_rc_U32_5622, _re_U32_5622);
        (void)hoisted__Bool_5657;
        if (hoisted__Bool_5657) {
            while (1) {
                Bool _wcond_Bool_5623 = U32_lt(_rc_U32_5622, _re_U32_5622);
                (void)_wcond_Bool_5623;
                if (_wcond_Bool_5623) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5622);
                U32_inc(&_rc_U32_5622);
                U32 hoisted__U32_5624 = 8;
                (void)hoisted__U32_5624;
                U32 hoisted__U32_5625 = U32_mul(i, hoisted__U32_5624);
                (void)hoisted__U32_5625;
                Type *hoisted__Type_5626 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5626;
                U64 hoisted__U64_5627 = (U64)(hoisted__U32_5625);
                (void)hoisted__U64_5627;
                Type_delete(hoisted__Type_5626, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5627);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5628 = 8;
                (void)hoisted__U32_5628;
                U32 hoisted__U32_5629 = U32_mul(i, hoisted__U32_5628);
                (void)hoisted__U32_5629;
                Type *hoisted__Type_5630 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5630;
                U64 hoisted__U64_5631 = (U64)(hoisted__U32_5629);
                (void)hoisted__U64_5631;
                Type_delete(hoisted__Type_5630, 1);
                U32 hoisted__U32_5632 = 8;
                (void)hoisted__U32_5632;
                Type *hoisted__Type_5633 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5633;
                void *hoisted__v_5634 = ptr_add(new_data, hoisted__U64_5631);
                (void)hoisted__v_5634;
                (void)hoisted__v_5634;
                U64 hoisted__U64_5635 = (U64)(hoisted__U32_5632);
                (void)hoisted__U64_5635;
                Type_delete(hoisted__Type_5633, 1);
                memcpy(hoisted__v_5634, &cloned, hoisted__U64_5635);
                U32 hoisted__U32_5636 = 8;
                (void)hoisted__U32_5636;
                Type *hoisted__Type_5637 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5637;
                I32 hoisted__I32_5638 = 0;
                (void)hoisted__I32_5638;
                U64 hoisted__U64_5639 = (U64)(hoisted__U32_5636);
                (void)hoisted__U64_5639;
                Type_delete(hoisted__Type_5637, 1);
                memset(&cloned, hoisted__I32_5638, hoisted__U64_5639);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5640 = U32_gt(_rc_U32_5622, _re_U32_5622);
                (void)_wcond_Bool_5640;
                if (_wcond_Bool_5640) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5622);
                U32_dec(&_rc_U32_5622);
                U32 hoisted__U32_5641 = 8;
                (void)hoisted__U32_5641;
                U32 hoisted__U32_5642 = U32_mul(i, hoisted__U32_5641);
                (void)hoisted__U32_5642;
                Type *hoisted__Type_5643 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5643;
                U64 hoisted__U64_5644 = (U64)(hoisted__U32_5642);
                (void)hoisted__U64_5644;
                Type_delete(hoisted__Type_5643, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5644);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5645 = 8;
                (void)hoisted__U32_5645;
                U32 hoisted__U32_5646 = U32_mul(i, hoisted__U32_5645);
                (void)hoisted__U32_5646;
                Type *hoisted__Type_5647 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5647;
                U64 hoisted__U64_5648 = (U64)(hoisted__U32_5646);
                (void)hoisted__U64_5648;
                Type_delete(hoisted__Type_5647, 1);
                U32 hoisted__U32_5649 = 8;
                (void)hoisted__U32_5649;
                Type *hoisted__Type_5650 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5650;
                void *hoisted__v_5651 = ptr_add(new_data, hoisted__U64_5648);
                (void)hoisted__v_5651;
                (void)hoisted__v_5651;
                U64 hoisted__U64_5652 = (U64)(hoisted__U32_5649);
                (void)hoisted__U64_5652;
                Type_delete(hoisted__Type_5650, 1);
                memcpy(hoisted__v_5651, &cloned, hoisted__U64_5652);
                U32 hoisted__U32_5653 = 8;
                (void)hoisted__U32_5653;
                Type *hoisted__Type_5654 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5654;
                I32 hoisted__I32_5655 = 0;
                (void)hoisted__I32_5655;
                U64 hoisted__U64_5656 = (U64)(hoisted__U32_5653);
                (void)hoisted__U64_5656;
                Type_delete(hoisted__Type_5654, 1);
                memset(&cloned, hoisted__I32_5655, hoisted__U64_5656);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5662 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5662->data = new_data;
    hoisted__Vec__I64_5662->count = self->count;
    hoisted__Vec__I64_5662->cap = self->cap;
    (void)hoisted__Vec__I64_5662;
    return hoisted__Vec__I64_5662;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5663 = 16;
    (void)hoisted__U32_5663;
    return hoisted__U32_5663;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6784 = 3;
    (void)hoisted__U32_6784;
    Array__Str *_va_Array_187 = Array__Str_new(hoisted__U32_6784);
    (void)_va_Array_187;
    I64 _va_Array_187_ek = 0;
    (void)_va_Array_187_ek;
    OutOfBounds *_va_Array_187_eo = malloc(sizeof(OutOfBounds));
    _va_Array_187_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_187_eo;
    U32 hoisted__U32_6785 = 0;
    (void)hoisted__U32_6785;
    Str *hoisted__Str_6786 = Str_clone(loc);
    (void)hoisted__Str_6786;
    Array__Str_set(_va_Array_187, hoisted__U32_6785, hoisted__Str_6786, &_va_Array_187_ek, _va_Array_187_eo);
    U32 hoisted__U32_6787 = 1;
    (void)hoisted__U32_6787;
    Str hoisted__Str_6788 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6788;
    Array__Str_set(_va_Array_187, hoisted__U32_6787, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6788; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_187_ek, _va_Array_187_eo);
    Array__Str *hoisted__Array__Str_6789 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6789;
    U32 hoisted__U32_6790 = 2;
    (void)hoisted__U32_6790;
    Str *hoisted__Str_6791 = format(hoisted__Array__Str_6789);
    (void)hoisted__Str_6791;
    Array__Str_set(_va_Array_187, hoisted__U32_6790, hoisted__Str_6791, &_va_Array_187_ek, _va_Array_187_eo);
    OutOfBounds_delete(_va_Array_187_eo, 1);
    Array__Str_delete(parts, 1);
    println(_va_Array_187);
    I64 hoisted__I64_6792 = 1;
    (void)hoisted__I64_6792;
    exit(hoisted__I64_6792);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_6799 = 1;
    (void)hoisted__U32_6799;
    Array__Str *_va_Array_189 = Array__Str_new(hoisted__U32_6799);
    (void)_va_Array_189;
    I64 _va_Array_189_ek = 0;
    (void)_va_Array_189_ek;
    OutOfBounds *_va_Array_189_eo = malloc(sizeof(OutOfBounds));
    _va_Array_189_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_189_eo;
    U32 hoisted__U32_6800 = 0;
    (void)hoisted__U32_6800;
    Str hoisted__Str_6801 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6801;
    Array__Str_set(_va_Array_189, hoisted__U32_6800, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6801; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_189_ek, _va_Array_189_eo);
    OutOfBounds_delete(_va_Array_189_eo, 1);
    panic(_va_Array_189, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6805 = not(cond);
    (void)hoisted__Bool_6805;
    if (hoisted__Bool_6805) {
        U32 hoisted__U32_6802 = 1;
        (void)hoisted__U32_6802;
        Array__Str *_va_Array_190 = Array__Str_new(hoisted__U32_6802);
        (void)_va_Array_190;
        I64 _va_Array_190_ek = 0;
        (void)_va_Array_190_ek;
        OutOfBounds *_va_Array_190_eo = malloc(sizeof(OutOfBounds));
        _va_Array_190_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_190_eo;
        U32 hoisted__U32_6803 = 0;
        (void)hoisted__U32_6803;
        Str hoisted__Str_6804 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6804;
        Array__Str_set(_va_Array_190, hoisted__U32_6803, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6804; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_190_ek, _va_Array_190_eo);
        OutOfBounds_delete(_va_Array_190_eo, 1);
        panic(_va_Array_190, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6813 = parts;
        (void)_fc_Array__Str_6813;
        (void)_fc_Array__Str_6813;
        U32 _fi_USize_6813 = 0;
        (void)_fi_USize_6813;
        I64 _forin_err_kind_6813 = 0;
        (void)_forin_err_kind_6813;
        OutOfBounds *_forin_OutOfBounds_6813 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_6813->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_6813;
        while (1) {
            U32 hoisted__U32_6821 = Array__Str_len(_fc_Array__Str_6813);
            (void)hoisted__U32_6821;
            Bool _wcond_Bool_6814 = U32_lt(_fi_USize_6813, hoisted__U32_6821);
            (void)_wcond_Bool_6814;
            if (_wcond_Bool_6814) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_6813, &_fi_USize_6813, &_forin_err_kind_6813, _forin_OutOfBounds_6813);
            I64 hoisted__I64_6822 = 0;
            (void)hoisted__I64_6822;
            Bool hoisted__Bool_6823 = I64_eq(_forin_err_kind_6813, hoisted__I64_6822);
            (void)hoisted__Bool_6823;
            Bool hoisted__Bool_6824 = not(hoisted__Bool_6823);
            (void)hoisted__Bool_6824;
            if (hoisted__Bool_6824) {
                U32 hoisted__U32_6815 = 2;
                (void)hoisted__U32_6815;
                Array__Str *_va_Array_192 = Array__Str_new(hoisted__U32_6815);
                (void)_va_Array_192;
                I64 _va_Array_192_ek = 0;
                (void)_va_Array_192_ek;
                OutOfBounds *_va_Array_192_eo = malloc(sizeof(OutOfBounds));
                _va_Array_192_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
                (void)_va_Array_192_eo;
                U32 hoisted__U32_6816 = 0;
                (void)hoisted__U32_6816;
                Str hoisted__Str_6817 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6817;
                Array__Str_set(_va_Array_192, hoisted__U32_6816, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6817; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_192_ek, _va_Array_192_eo);
                U32 hoisted__U32_6818 = 1;
                (void)hoisted__U32_6818;
                Str hoisted__Str_6819 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6819;
                Array__Str_set(_va_Array_192, hoisted__U32_6818, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6819; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_192_ek, _va_Array_192_eo);
                OutOfBounds_delete(_va_Array_192_eo, 1);
                Str hoisted__Str_6820 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6820;
                panic(_va_Array_192, &hoisted__Str_6820);
                Str_delete(&hoisted__Str_6820, (Bool){0});
            }
            U32 hoisted__U32_6825 = 1;
            (void)hoisted__U32_6825;
            U32 hoisted__U32_6826 = U32_add(_fi_USize_6813, hoisted__U32_6825);
            (void)hoisted__U32_6826;
            _fi_USize_6813 = hoisted__U32_6826;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_6813, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_6866 = ptr_eq(p, NULL);
    (void)hoisted__Bool_6866;
    return hoisted__Bool_6866;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6875 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6875;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6875;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6876 = 0;
    (void)hoisted__U32_6876;
    U64 hoisted__U64_6877 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6876); });
    (void)hoisted__U64_6877;
    return hoisted__U64_6877;
}

U32 Range_size(void) {
    U32 hoisted__U32_6901 = 16;
    (void)hoisted__U32_6901;
    return hoisted__U32_6901;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7007 = 3;
    (void)hoisted__I64_7007;
    Str hoisted__Str_7008 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7008;
    assert_eq__I64(result, hoisted__I64_7007, &hoisted__Str_7008);
    Str_delete(&hoisted__Str_7008, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7015 = 15;
    (void)hoisted__I64_7015;
    Str hoisted__Str_7016 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7016;
    assert_eq__I64(result, hoisted__I64_7015, &hoisted__Str_7016);
    Str_delete(&hoisted__Str_7016, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7023 = 26;
    (void)hoisted__I64_7023;
    Str hoisted__Str_7024 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7024;
    assert_eq__I64(result, hoisted__I64_7023, &hoisted__Str_7024);
    Str_delete(&hoisted__Str_7024, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7027 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7027;
    Str hoisted__Str_7028 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7028;
    assert_eq__Str(&result, &hoisted__Str_7027, &hoisted__Str_7028);
    Str_delete(&hoisted__Str_7027, (Bool){0});
    Str_delete(&hoisted__Str_7028, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7049 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7049;
    Str hoisted__Str_7050 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7050;
    assert_eq__Str(&r, &hoisted__Str_7049, &hoisted__Str_7050);
    Str_delete(&hoisted__Str_7049, (Bool){0});
    Str_delete(&hoisted__Str_7050, (Bool){0});
    Str_delete(&r, (Bool){0});
    Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7054 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7054;
    Str hoisted__Str_7055 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7055;
    assert_eq__Str(&r2, &hoisted__Str_7054, &hoisted__Str_7055);
    Str_delete(&hoisted__Str_7054, (Bool){0});
    Str_delete(&hoisted__Str_7055, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7386 = (Str){.c_str = (void *)"test/constfold.til:104:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7386;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_7386);
    Str_delete(&hoisted__Str_7386, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_7387 = (Str){.c_str = (void *)"test/constfold.til:105:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7387;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_7387);
    Str_delete(&hoisted__Str_7387, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_7389 = 8;
    (void)hoisted__I64_7389;
    Str hoisted__Str_7390 = (Str){.c_str = (void *)"test/constfold.til:112:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7390;
    assert_eq__I64(result, hoisted__I64_7389, &hoisted__Str_7390);
    Str_delete(&hoisted__Str_7390, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7393 = 1;
    (void)hoisted__Bool_7393;
    Str hoisted__Str_7394 = (Str){.c_str = (void *)"test/constfold.til:117:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7394;
    assert(hoisted__Bool_7393, &hoisted__Str_7394);
    Str_delete(&hoisted__Str_7394, (Bool){0});
    Bool hoisted__Bool_7397 = 1;
    (void)hoisted__Bool_7397;
    Str hoisted__Str_7398 = (Str){.c_str = (void *)"test/constfold.til:118:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7398;
    assert(hoisted__Bool_7397, &hoisted__Str_7398);
    Str_delete(&hoisted__Str_7398, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_7403 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7403;
    Str hoisted__Str_7404 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7404;
    Str hoisted__Str_7405 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7405;
    assert_eq__Str(&hoisted__Str_7403, &hoisted__Str_7404, &hoisted__Str_7405);
    Str_delete(&hoisted__Str_7403, (Bool){0});
    Str_delete(&hoisted__Str_7404, (Bool){0});
    Str_delete(&hoisted__Str_7405, (Bool){0});
    Str hoisted__Str_7408 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7408;
    Str hoisted__Str_7409 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7409;
    Str hoisted__Str_7410 = (Str){.c_str = (void *)"test/constfold.til:131:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7410;
    assert_eq__Str(&hoisted__Str_7408, &hoisted__Str_7409, &hoisted__Str_7410);
    Str_delete(&hoisted__Str_7408, (Bool){0});
    Str_delete(&hoisted__Str_7409, (Bool){0});
    Str_delete(&hoisted__Str_7410, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7415 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7415;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7415;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7416 = 0;
    (void)hoisted__U32_7416;
    U64 hoisted__U64_7417 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7416); });
    (void)hoisted__U64_7417;
    return hoisted__U64_7417;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_7441 = 16;
    (void)hoisted__U32_7441;
    return hoisted__U32_7441;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_7442 = 42;
    (void)hoisted__I64_7442;
    Str hoisted__Str_7443 = (Str){.c_str = (void *)"test/constfold.til:153:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7443;
    assert_eq__I64(v.x, hoisted__I64_7442, &hoisted__Str_7443);
    Str_delete(&hoisted__Str_7443, (Bool){0});
    I64 hoisted__I64_7444 = 99;
    (void)hoisted__I64_7444;
    Str hoisted__Str_7445 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7445;
    assert_eq__I64(v.y, hoisted__I64_7444, &hoisted__Str_7445);
    Str_delete(&hoisted__Str_7445, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7448 = 10;
    (void)hoisted__I64_7448;
    Str hoisted__Str_7449 = (Str){.c_str = (void *)"test/constfold.til:160:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7449;
    assert_eq__I64(p.x, hoisted__I64_7448, &hoisted__Str_7449);
    Str_delete(&hoisted__Str_7449, (Bool){0});
    I64 hoisted__I64_7450 = 20;
    (void)hoisted__I64_7450;
    Str hoisted__Str_7451 = (Str){.c_str = (void *)"test/constfold.til:161:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7451;
    assert_eq__I64(p.y, hoisted__I64_7450, &hoisted__Str_7451);
    Str_delete(&hoisted__Str_7451, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7457 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7457;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7457;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7458 = 0;
    (void)hoisted__U32_7458;
    U64 hoisted__U64_7459 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7458); });
    (void)hoisted__U64_7459;
    return hoisted__U64_7459;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_7483 = 32;
    (void)hoisted__U32_7483;
    return hoisted__U32_7483;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_7484 = 5;
    (void)hoisted__I64_7484;
    Str hoisted__Str_7485 = (Str){.c_str = (void *)"test/constfold.til:177:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7485;
    assert_eq__I64(r.top_left.x, hoisted__I64_7484, &hoisted__Str_7485);
    Str_delete(&hoisted__Str_7485, (Bool){0});
    I64 hoisted__I64_7486 = 10;
    (void)hoisted__I64_7486;
    Str hoisted__Str_7487 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7487;
    assert_eq__I64(r.top_left.y, hoisted__I64_7486, &hoisted__Str_7487);
    Str_delete(&hoisted__Str_7487, (Bool){0});
    I64 hoisted__I64_7488 = 100;
    (void)hoisted__I64_7488;
    Str hoisted__Str_7489 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7489;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7488, &hoisted__Str_7489);
    Str_delete(&hoisted__Str_7489, (Bool){0});
    I64 hoisted__I64_7490 = 200;
    (void)hoisted__I64_7490;
    Str hoisted__Str_7491 = (Str){.c_str = (void *)"test/constfold.til:180:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7491;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7490, &hoisted__Str_7491);
    Str_delete(&hoisted__Str_7491, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7493 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7493;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7493;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7494 = 0;
    (void)hoisted__U32_7494;
    U64 hoisted__U64_7495 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7494); });
    (void)hoisted__U64_7495;
    return hoisted__U64_7495;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_7528 = 12;
    (void)hoisted__U32_7528;
    return hoisted__U32_7528;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_7532 = F32_to_str(v.x);
    (void)hoisted__Str_7532;
    Str hoisted__Str_7533 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7533;
    Str hoisted__Str_7534 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7534;
    assert_eq__Str(hoisted__Str_7532, &hoisted__Str_7533, &hoisted__Str_7534);
    Str_delete(hoisted__Str_7532, 1);
    Str_delete(&hoisted__Str_7533, (Bool){0});
    Str_delete(&hoisted__Str_7534, (Bool){0});
    Str *hoisted__Str_7535 = F32_to_str(v.y);
    (void)hoisted__Str_7535;
    Str hoisted__Str_7536 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7536;
    Str hoisted__Str_7537 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7537;
    assert_eq__Str(hoisted__Str_7535, &hoisted__Str_7536, &hoisted__Str_7537);
    Str_delete(hoisted__Str_7535, 1);
    Str_delete(&hoisted__Str_7536, (Bool){0});
    Str_delete(&hoisted__Str_7537, (Bool){0});
    Str *hoisted__Str_7538 = F32_to_str(v.z);
    (void)hoisted__Str_7538;
    Str hoisted__Str_7539 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7539;
    Str hoisted__Str_7540 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7540;
    assert_eq__Str(hoisted__Str_7538, &hoisted__Str_7539, &hoisted__Str_7540);
    Str_delete(hoisted__Str_7538, 1);
    Str_delete(&hoisted__Str_7539, (Bool){0});
    Str_delete(&hoisted__Str_7540, (Bool){0});
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
    Bool hoisted__Bool_7545 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7545;
    if (hoisted__Bool_7545) {
        Bool hoisted__Bool_7542 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_7542;
        { Bool _ret_val = hoisted__Bool_7542;
                return _ret_val; }
    }
    Bool hoisted__Bool_7546 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7546;
    if (hoisted__Bool_7546) {
        Bool hoisted__Bool_7543 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_7543;
        { Bool _ret_val = hoisted__Bool_7543;
                return _ret_val; }
    }
    Bool hoisted__Bool_7547 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7547;
    if (hoisted__Bool_7547) {
        Bool hoisted__Bool_7544 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_7544;
        { Bool _ret_val = hoisted__Bool_7544;
                return _ret_val; }
    }
    Bool hoisted__Bool_7548 = 0;
    (void)hoisted__Bool_7548;
    return hoisted__Bool_7548;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7556 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7556;
    if (hoisted__Bool_7556) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_7557 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7557;
    if (hoisted__Bool_7557) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_7558 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7558;
    if (hoisted__Bool_7558) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_7559 = (Str){.c_str = (void *)"Color.clone:210:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7559;
    UNREACHABLE(&hoisted__Str_7559);
    Str_delete(&hoisted__Str_7559, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_7560 = 4;
    (void)hoisted__U32_7560;
    return hoisted__U32_7560;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7561 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7561;
    Str hoisted__Str_7562 = (Str){.c_str = (void *)"test/constfold.til:215:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7562;
    assert(hoisted__Bool_7561, &hoisted__Str_7562);
    Str_delete(&hoisted__Str_7562, (Bool){0});
    Bool hoisted__Bool_7563 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7563;
    Bool hoisted__Bool_7564 = not(hoisted__Bool_7563);
    (void)hoisted__Bool_7564;
    Str hoisted__Str_7565 = (Str){.c_str = (void *)"test/constfold.til:216:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7565;
    assert(hoisted__Bool_7564, &hoisted__Str_7565);
    Str_delete(&hoisted__Str_7565, (Bool){0});
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
    Bool hoisted__Bool_7566 = is(self, other);
    (void)hoisted__Bool_7566;
    return hoisted__Bool_7566;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7584 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7584;
    if (hoisted__Bool_7584) {
        I64 *hoisted__I64_7580 = get_payload(self);
        (void)hoisted__I64_7580;
        (void)hoisted__I64_7580;
        Bool hoisted__Bool_7581 = 0;
        (void)hoisted__Bool_7581;
        I64_delete(hoisted__I64_7580, hoisted__Bool_7581);
    }
    Bool hoisted__Bool_7585 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7585;
    if (hoisted__Bool_7585) {
        Str *hoisted__Str_7582 = get_payload(self);
        (void)hoisted__Str_7582;
        (void)hoisted__Str_7582;
        Bool hoisted__Bool_7583 = 0;
        (void)hoisted__Bool_7583;
        Str_delete(hoisted__Str_7582, hoisted__Bool_7583);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_7610 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7610;
    if (hoisted__Bool_7610) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7607 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7607;
        { Token * _ret_val = hoisted__Token_7607;
                return _ret_val; }
    }
    Bool hoisted__Bool_7611 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7611;
    if (hoisted__Bool_7611) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7608 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7608;
        Token *hoisted__Token_7609 = Token_Name(hoisted__Str_7608);
        (void)hoisted__Token_7609;
        { Token * _ret_val = hoisted__Token_7609;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_7612 = 24;
    (void)hoisted__U32_7612;
    return hoisted__U32_7612;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7614 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7614;
    Str hoisted__Str_7615 = (Str){.c_str = (void *)"test/constfold.til:224:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7615;
    assert(hoisted__Bool_7614, &hoisted__Str_7615);
    Str_delete(&hoisted__Str_7615, (Bool){0});
    Bool hoisted__Bool_7616 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7616;
    Bool hoisted__Bool_7617 = not(hoisted__Bool_7616);
    (void)hoisted__Bool_7617;
    Str hoisted__Str_7618 = (Str){.c_str = (void *)"test/constfold.til:225:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7618;
    assert(hoisted__Bool_7617, &hoisted__Str_7618);
    Str_delete(&hoisted__Str_7618, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7619 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7619;
    Str hoisted__Str_7620 = (Str){.c_str = (void *)"test/constfold.til:234:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7620;
    assert(hoisted__Bool_7619, &hoisted__Str_7620);
    Str_delete(&hoisted__Str_7620, (Bool){0});
    Bool hoisted__Bool_7621 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7621;
    Bool hoisted__Bool_7622 = not(hoisted__Bool_7621);
    (void)hoisted__Bool_7622;
    Str hoisted__Str_7623 = (Str){.c_str = (void *)"test/constfold.til:235:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7623;
    assert(hoisted__Bool_7622, &hoisted__Str_7623);
    Str_delete(&hoisted__Str_7623, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7626 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7626;
    Str hoisted__Str_7627 = (Str){.c_str = (void *)"test/constfold.til:246:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7627;
    assert(hoisted__Bool_7626, &hoisted__Str_7627);
    Str_delete(&hoisted__Str_7627, (Bool){0});
    Bool hoisted__Bool_7628 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7628;
    Bool hoisted__Bool_7629 = not(hoisted__Bool_7628);
    (void)hoisted__Bool_7629;
    Str hoisted__Str_7630 = (Str){.c_str = (void *)"test/constfold.til:247:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7630;
    assert(hoisted__Bool_7629, &hoisted__Str_7630);
    Str_delete(&hoisted__Str_7630, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7642 = I64_neq(a, b);
    (void)hoisted__Bool_7642;
    if (hoisted__Bool_7642) {
        U32 hoisted__U32_7631 = 5;
        (void)hoisted__U32_7631;
        Array__Str *_va_Array_208 = Array__Str_new(hoisted__U32_7631);
        (void)_va_Array_208;
        I64 _va_Array_208_ek = 0;
        (void)_va_Array_208_ek;
        OutOfBounds *_va_Array_208_eo = malloc(sizeof(OutOfBounds));
        _va_Array_208_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_208_eo;
        U32 hoisted__U32_7632 = 0;
        (void)hoisted__U32_7632;
        Str hoisted__Str_7633 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7633;
        Array__Str_set(_va_Array_208, hoisted__U32_7632, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7633; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_208_ek, _va_Array_208_eo);
        U32 hoisted__U32_7634 = 1;
        (void)hoisted__U32_7634;
        Str *hoisted__Str_7635 = I64_to_str(a);
        (void)hoisted__Str_7635;
        Array__Str_set(_va_Array_208, hoisted__U32_7634, hoisted__Str_7635, &_va_Array_208_ek, _va_Array_208_eo);
        U32 hoisted__U32_7636 = 2;
        (void)hoisted__U32_7636;
        Str hoisted__Str_7637 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7637;
        Array__Str_set(_va_Array_208, hoisted__U32_7636, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7637; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_208_ek, _va_Array_208_eo);
        U32 hoisted__U32_7638 = 3;
        (void)hoisted__U32_7638;
        Str *hoisted__Str_7639 = I64_to_str(b);
        (void)hoisted__Str_7639;
        Array__Str_set(_va_Array_208, hoisted__U32_7638, hoisted__Str_7639, &_va_Array_208_ek, _va_Array_208_eo);
        U32 hoisted__U32_7640 = 4;
        (void)hoisted__U32_7640;
        Str hoisted__Str_7641 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7641;
        Array__Str_set(_va_Array_208, hoisted__U32_7640, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7641; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_208_ek, _va_Array_208_eo);
        OutOfBounds_delete(_va_Array_208_eo, 1);
        panic(_va_Array_208, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7654 = Str_neq(a, b);
    (void)hoisted__Bool_7654;
    if (hoisted__Bool_7654) {
        U32 hoisted__U32_7643 = 5;
        (void)hoisted__U32_7643;
        Array__Str *_va_Array_209 = Array__Str_new(hoisted__U32_7643);
        (void)_va_Array_209;
        I64 _va_Array_209_ek = 0;
        (void)_va_Array_209_ek;
        OutOfBounds *_va_Array_209_eo = malloc(sizeof(OutOfBounds));
        _va_Array_209_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_209_eo;
        U32 hoisted__U32_7644 = 0;
        (void)hoisted__U32_7644;
        Str hoisted__Str_7645 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7645;
        Array__Str_set(_va_Array_209, hoisted__U32_7644, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7645; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_209_ek, _va_Array_209_eo);
        U32 hoisted__U32_7646 = 1;
        (void)hoisted__U32_7646;
        Str *hoisted__Str_7647 = Str_to_str(a);
        (void)hoisted__Str_7647;
        Array__Str_set(_va_Array_209, hoisted__U32_7646, hoisted__Str_7647, &_va_Array_209_ek, _va_Array_209_eo);
        U32 hoisted__U32_7648 = 2;
        (void)hoisted__U32_7648;
        Str hoisted__Str_7649 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7649;
        Array__Str_set(_va_Array_209, hoisted__U32_7648, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7649; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_209_ek, _va_Array_209_eo);
        U32 hoisted__U32_7650 = 3;
        (void)hoisted__U32_7650;
        Str *hoisted__Str_7651 = Str_to_str(b);
        (void)hoisted__Str_7651;
        Array__Str_set(_va_Array_209, hoisted__U32_7650, hoisted__Str_7651, &_va_Array_209_ek, _va_Array_209_eo);
        U32 hoisted__U32_7652 = 4;
        (void)hoisted__U32_7652;
        Str hoisted__Str_7653 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7653;
        Array__Str_set(_va_Array_209, hoisted__U32_7652, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7653; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }), &_va_Array_209_ek, _va_Array_209_eo);
        OutOfBounds_delete(_va_Array_209_eo, 1);
        panic(_va_Array_209, loc);
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
    fprintf(stderr, "17/17 tests passed\n");
    return 0;
}
