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
Str * Array__Str_unsafe_get(Array__Str * self, U32 * i);
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
Str * Array__Str_unsafe_get(Array__Str * self, U32 * i);
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
        Array__Str *_fc_Array__Str_735 = parts;
        (void)_fc_Array__Str_735;
        (void)_fc_Array__Str_735;
        U32 _fi_USize_735 = 0;
        (void)_fi_USize_735;
        while (1) {
            U32 hoisted__U32_737 = Array__Str_len(_fc_Array__Str_735);
            (void)hoisted__U32_737;
            Bool _wcond_Bool_736 = U32_lt(_fi_USize_735, hoisted__U32_737);
            (void)_wcond_Bool_736;
            if (_wcond_Bool_736) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_735, &_fi_USize_735);
            U32 hoisted__U32_738 = 1;
            (void)hoisted__U32_738;
            U32 hoisted__U32_739 = U32_add(_fi_USize_735, hoisted__U32_738);
            (void)hoisted__U32_739;
            _fi_USize_735 = hoisted__U32_739;
            U32 hoisted__U32_740 = Str_len(s);
            (void)hoisted__U32_740;
            U32 hoisted__U32_741 = U32_add(total, hoisted__U32_740);
            (void)hoisted__U32_741;
            total = hoisted__U32_741;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_742 = parts;
        (void)_fc_Array__Str_742;
        (void)_fc_Array__Str_742;
        U32 _fi_USize_742 = 0;
        (void)_fi_USize_742;
        while (1) {
            U32 hoisted__U32_744 = Array__Str_len(_fc_Array__Str_742);
            (void)hoisted__U32_744;
            Bool _wcond_Bool_743 = U32_lt(_fi_USize_742, hoisted__U32_744);
            (void)_wcond_Bool_743;
            if (_wcond_Bool_743) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_742, &_fi_USize_742);
            U32 hoisted__U32_745 = 1;
            (void)hoisted__U32_745;
            U32 hoisted__U32_746 = U32_add(_fi_USize_742, hoisted__U32_745);
            (void)hoisted__U32_746;
            _fi_USize_742 = hoisted__U32_746;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_752 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_752;
    if (hoisted__Bool_752) {
        U32 hoisted__U32_747 = 1;
        (void)hoisted__U32_747;
        Array__Str *_va_Array_17 = Array__Str_new(hoisted__U32_747);
        (void)_va_Array_17;
        I64 _va_Array_17_ek = 0;
        (void)_va_Array_17_ek;
        OutOfBounds *_va_Array_17_eo = malloc(sizeof(OutOfBounds));
        _va_Array_17_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_17_eo;
        U32 hoisted__U32_748 = 0;
        (void)hoisted__U32_748;
        static Str hoisted__Str_749 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_749;
        static Str hoisted__Str_750 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_750;
        Array__Str_set(_va_Array_17, hoisted__U32_748, &hoisted__Str_749, &_va_Array_17_ek, _va_Array_17_eo, &hoisted__Str_750);
        OutOfBounds_delete(_va_Array_17_eo, 1);
        Str_delete(&hoisted__Str_750, (Bool){0});
        static Str hoisted__Str_751 = (Str){.c_str = (void *)"./src/core/str.til:42:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_751;
        panic(_va_Array_17, &hoisted__Str_751);
        Str_delete(&hoisted__Str_751, (Bool){0});
    }
    void *hoisted__v_753 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_753;
    (void)hoisted__v_753;
    return hoisted__v_753;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_763 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_763;
    if (hoisted__Bool_763) {
        min_len = b->count;
    }
    {
        U32 _re_U32_755 = U32_clone(&min_len);
        (void)_re_U32_755;
        U32 _rc_U32_755 = 0;
        (void)_rc_U32_755;
        Bool hoisted__Bool_762 = U32_lte(_rc_U32_755, _re_U32_755);
        (void)hoisted__Bool_762;
        if (hoisted__Bool_762) {
            while (1) {
                Bool _wcond_Bool_756 = U32_lt(_rc_U32_755, _re_U32_755);
                (void)_wcond_Bool_756;
                if (_wcond_Bool_756) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_755);
                U32_inc(&_rc_U32_755);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_757 = 0;
                (void)hoisted__I64_757;
                Bool hoisted__Bool_758 = I64_neq(c, hoisted__I64_757);
                (void)hoisted__Bool_758;
                if (hoisted__Bool_758) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_759 = U32_gt(_rc_U32_755, _re_U32_755);
                (void)_wcond_Bool_759;
                if (_wcond_Bool_759) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_755);
                U32_dec(&_rc_U32_755);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_760 = 0;
                (void)hoisted__I64_760;
                Bool hoisted__Bool_761 = I64_neq(c, hoisted__I64_760);
                (void)hoisted__Bool_761;
                if (hoisted__Bool_761) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_764 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_764;
    return hoisted__I64_764;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_765 = 1;
    (void)hoisted__U32_765;
    U32 hoisted__U64_766 = U32_add(n, hoisted__U32_765);
    (void)hoisted__U64_766;
    void * buf = malloc(hoisted__U64_766);
    I32 hoisted__I32_767 = 0;
    (void)hoisted__I32_767;
    U64 hoisted__U64_768 = 1ULL;
    (void)hoisted__U64_768;
    memset(buf, hoisted__I32_767, hoisted__U64_768);
    I64 hoisted__I64_769 = 0;
    (void)hoisted__I64_769;
    Str *hoisted__Str_770 = malloc(sizeof(Str));
    hoisted__Str_770->c_str = buf;
    hoisted__Str_770->count = hoisted__I64_769;
    hoisted__Str_770->cap = n;
    (void)hoisted__Str_770;
    return hoisted__Str_770;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_783 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_783;
    if (hoisted__Bool_783) {
        U32 hoisted__U32_773 = 1;
        (void)hoisted__U32_773;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_773);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_774 = 0;
        (void)hoisted__U32_774;
        static Str hoisted__Str_775 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_775;
        static Str hoisted__Str_776 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_776;
        Array__Str_set(_va_Array_18, hoisted__U32_774, &hoisted__Str_775, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_776);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_776, (Bool){0});
        static Str hoisted__Str_777 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_777;
        panic(_va_Array_18, &hoisted__Str_777);
        Str_delete(&hoisted__Str_777, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_784 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_784;
    if (hoisted__Bool_784) {
        U32 hoisted__U32_778 = 1;
        (void)hoisted__U32_778;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_778);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_779 = 0;
        (void)hoisted__U32_779;
        static Str hoisted__Str_780 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_780;
        static Str hoisted__Str_781 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_781;
        Array__Str_set(_va_Array_19, hoisted__U32_779, &hoisted__Str_780, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_781);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_781, (Bool){0});
        static Str hoisted__Str_782 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_782;
        panic(_va_Array_19, &hoisted__Str_782);
        Str_delete(&hoisted__Str_782, (Bool){0});
    }
    void *hoisted__v_785 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_785;
    (void)hoisted__v_785;
    memcpy(hoisted__v_785, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_786 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_786;
    (void)hoisted__v_786;
    I32 hoisted__I32_787 = 0;
    (void)hoisted__I32_787;
    U64 hoisted__U64_788 = 1ULL;
    (void)hoisted__U64_788;
    memset(hoisted__v_786, hoisted__I32_787, hoisted__U64_788);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_789 = 1;
    (void)hoisted__U32_789;
    U32 hoisted__U64_790 = U32_add(val->count, hoisted__U32_789);
    (void)hoisted__U64_790;
    void * new_data = malloc(hoisted__U64_790);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_791 = ptr_add(new_data, val->count);
    (void)hoisted__v_791;
    (void)hoisted__v_791;
    I32 hoisted__I32_792 = 0;
    (void)hoisted__I32_792;
    U64 hoisted__U64_793 = 1ULL;
    (void)hoisted__U64_793;
    memset(hoisted__v_791, hoisted__I32_792, hoisted__U64_793);
    Str *hoisted__Str_794 = malloc(sizeof(Str));
    hoisted__Str_794->c_str = new_data;
    hoisted__Str_794->count = val->count;
    hoisted__Str_794->cap = val->count;
    (void)hoisted__Str_794;
    return hoisted__Str_794;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_795 = Str_clone(self);
    (void)hoisted__Str_795;
    return hoisted__Str_795;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_796 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_796;
    if (hoisted__Bool_796) {
        free(self->c_str);
    }
    Bool hoisted__Bool_797 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_797;
    Bool hoisted__Bool_798 = and(call_free, hoisted__Bool_797);
    (void)hoisted__Bool_798;
    if (hoisted__Bool_798) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_993 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_993;
    return hoisted__U64_993;
}

U32 Str_size(void) {
    U32 hoisted__U32_1178 = 16;
    (void)hoisted__U32_1178;
    return hoisted__U32_1178;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1179 = Str_cmp(a, b);
    (void)hoisted__I64_1179;
    I64 hoisted__I64_1180 = 0;
    (void)hoisted__I64_1180;
    Bool hoisted__Bool_1181 = I64_eq(hoisted__I64_1179, hoisted__I64_1180);
    (void)hoisted__Bool_1181;
    return hoisted__Bool_1181;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1190 = Str_eq(a, b);
    (void)hoisted__Bool_1190;
    Bool hoisted__Bool_1191 = not(hoisted__Bool_1190);
    (void)hoisted__Bool_1191;
    return hoisted__Bool_1191;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1283 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1283->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1283;
    return hoisted__OutOfBounds_1283;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1284 = 0;
    (void)hoisted__Bool_1284;
    Str_delete(&self->msg, hoisted__Bool_1284);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1285 = 0;
    (void)hoisted__U32_1285;
    U64 hoisted__U64_1286 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1285); });
    (void)hoisted__U64_1286;
    return hoisted__U64_1286;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1305 = 16;
    (void)hoisted__U32_1305;
    return hoisted__U32_1305;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1329 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1329;
    U32 hoisted__U32_1330 = 16;
    (void)hoisted__U32_1330;
    Type *hoisted__Type_1331 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1331;
    U64 hoisted__U64_1332 = (U64)(cap);
    (void)hoisted__U64_1332;
    Type_delete(hoisted__Type_1329, 1);
    U64 hoisted__U64_1333 = (U64)(hoisted__U32_1330);
    (void)hoisted__U64_1333;
    Type_delete(hoisted__Type_1331, 1);
    void * hoisted__v_1334 = calloc(hoisted__U64_1332, hoisted__U64_1333);
    (void)hoisted__v_1334;
    Array__Str *hoisted__Array__Str_1335 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1335->data = hoisted__v_1334;
    hoisted__Array__Str_1335->cap = cap;
    (void)hoisted__Array__Str_1335;
    return hoisted__Array__Str_1335;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_1336 = 16;
    (void)hoisted__U32_1336;
    U32 hoisted__U32_1337 = U32_mul(DEREF(i), hoisted__U32_1336);
    (void)hoisted__U32_1337;
    Type *hoisted__Type_1338 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1338;
    U64 hoisted__U64_1339 = (U64)(hoisted__U32_1337);
    (void)hoisted__U64_1339;
    Type_delete(hoisted__Type_1338, 1);
    void *hoisted__v_1340 = ptr_add(self->data, hoisted__U64_1339);
    (void)hoisted__v_1340;
    (void)hoisted__v_1340;
    return hoisted__v_1340;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1407 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1407;
    if (hoisted__Bool_1407) {
        U32 hoisted__U32_1367 = 6;
        (void)hoisted__U32_1367;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1367);
        (void)_va_Array_31;
        I64 _va_Array_31_ek = 0;
        (void)_va_Array_31_ek;
        OutOfBounds *_va_Array_31_eo = malloc(sizeof(OutOfBounds));
        _va_Array_31_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_31_eo;
        U32 hoisted__U32_1368 = 0;
        (void)hoisted__U32_1368;
        Str *hoisted__Str_1369 = Str_clone(loc);
        (void)hoisted__Str_1369;
        static Str hoisted__Str_1370 = (Str){.c_str = (void *)"./src/core/str.til:48:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1370;
        Array__Str_set(_va_Array_31, hoisted__U32_1368, hoisted__Str_1369, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1370);
        Str_delete(&hoisted__Str_1370, (Bool){0});
        U32 hoisted__U32_1371 = 1;
        (void)hoisted__U32_1371;
        static Str hoisted__Str_1372 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1372;
        static Str hoisted__Str_1373 = (Str){.c_str = (void *)"./src/core/str.til:48:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1373;
        Array__Str_set(_va_Array_31, hoisted__U32_1371, &hoisted__Str_1372, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1373);
        Str_delete(&hoisted__Str_1373, (Bool){0});
        U32 hoisted__U32_1374 = 2;
        (void)hoisted__U32_1374;
        Str *hoisted__Str_1375 = U32_to_str(i);
        (void)hoisted__Str_1375;
        static Str hoisted__Str_1376 = (Str){.c_str = (void *)"./src/core/str.til:48:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1376;
        Array__Str_set(_va_Array_31, hoisted__U32_1374, hoisted__Str_1375, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1376);
        Str_delete(&hoisted__Str_1376, (Bool){0});
        U32 hoisted__U32_1377 = 3;
        (void)hoisted__U32_1377;
        static Str hoisted__Str_1378 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1378;
        static Str hoisted__Str_1379 = (Str){.c_str = (void *)"./src/core/str.til:48:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1379;
        Array__Str_set(_va_Array_31, hoisted__U32_1377, &hoisted__Str_1378, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1379);
        Str_delete(&hoisted__Str_1379, (Bool){0});
        U32 hoisted__U32_1380 = 4;
        (void)hoisted__U32_1380;
        Str *hoisted__Str_1381 = U32_to_str(self->cap);
        (void)hoisted__Str_1381;
        static Str hoisted__Str_1382 = (Str){.c_str = (void *)"./src/core/str.til:48:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1382;
        Array__Str_set(_va_Array_31, hoisted__U32_1380, hoisted__Str_1381, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1382);
        Str_delete(&hoisted__Str_1382, (Bool){0});
        U32 hoisted__U32_1383 = 5;
        (void)hoisted__U32_1383;
        static Str hoisted__Str_1384 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1384;
        static Str hoisted__Str_1385 = (Str){.c_str = (void *)"./src/core/str.til:48:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1385;
        Array__Str_set(_va_Array_31, hoisted__U32_1383, &hoisted__Str_1384, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1385);
        OutOfBounds_delete(_va_Array_31_eo, 1);
        Str_delete(&hoisted__Str_1385, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1386 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_31); hoisted__OutOfBounds_1386->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1386;
        U32 hoisted__U32_1387 = 16;
        (void)hoisted__U32_1387;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1386, hoisted__U32_1387);
        OutOfBounds_delete(hoisted__OutOfBounds_1386, 1);
        I64 hoisted__I64_1388 = 3;
        (void)hoisted__I64_1388;
        *_err_kind = hoisted__I64_1388;
    }
    I64 hoisted__I64_1408 = 0;
    (void)hoisted__I64_1408;
    Bool hoisted__Bool_1409 = I64_eq(DEREF(_err_kind), hoisted__I64_1408);
    (void)hoisted__Bool_1409;
    if (hoisted__Bool_1409) {
        U32 hoisted__U32_1389 = 16;
        (void)hoisted__U32_1389;
        U32 hoisted__U32_1390 = U32_mul(i, hoisted__U32_1389);
        (void)hoisted__U32_1390;
        Type *hoisted__Type_1391 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1391;
        U64 hoisted__U64_1392 = (U64)(hoisted__U32_1390);
        (void)hoisted__U64_1392;
        Type_delete(hoisted__Type_1391, 1);
        Str *hoisted__Str_1393 = ptr_add(self->data, hoisted__U64_1392);
        (void)hoisted__Str_1393;
        (void)hoisted__Str_1393;
        Bool hoisted__Bool_1394 = 0;
        (void)hoisted__Bool_1394;
        Str_delete(hoisted__Str_1393, hoisted__Bool_1394);
        U32 hoisted__U32_1395 = 16;
        (void)hoisted__U32_1395;
        U32 hoisted__U32_1396 = U32_mul(i, hoisted__U32_1395);
        (void)hoisted__U32_1396;
        Type *hoisted__Type_1397 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1397;
        U64 hoisted__U64_1398 = (U64)(hoisted__U32_1396);
        (void)hoisted__U64_1398;
        Type_delete(hoisted__Type_1397, 1);
        U32 hoisted__U32_1399 = 16;
        (void)hoisted__U32_1399;
        Type *hoisted__Type_1400 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1400;
        void *hoisted__v_1401 = ptr_add(self->data, hoisted__U64_1398);
        (void)hoisted__v_1401;
        (void)hoisted__v_1401;
        U64 hoisted__U64_1402 = (U64)(hoisted__U32_1399);
        (void)hoisted__U64_1402;
        Type_delete(hoisted__Type_1400, 1);
        memcpy(hoisted__v_1401, val, hoisted__U64_1402);
        U32 hoisted__U32_1403 = 16;
        (void)hoisted__U32_1403;
        Type *hoisted__Type_1404 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1404;
        I32 hoisted__I32_1405 = 0;
        (void)hoisted__I32_1405;
        U64 hoisted__U64_1406 = (U64)(hoisted__U32_1403);
        (void)hoisted__U64_1406;
        Type_delete(hoisted__Type_1404, 1);
        if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1405, hoisted__U64_1406); };
    }
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1410 = self->cap;
        (void)_re_U32_1410;
        U32 _rc_U32_1410 = 0;
        (void)_rc_U32_1410;
        Bool hoisted__Bool_1425 = U32_lte(_rc_U32_1410, _re_U32_1410);
        (void)hoisted__Bool_1425;
        if (hoisted__Bool_1425) {
            while (1) {
                Bool _wcond_Bool_1411 = U32_lt(_rc_U32_1410, _re_U32_1410);
                (void)_wcond_Bool_1411;
                if (_wcond_Bool_1411) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1410);
                U32_inc(&_rc_U32_1410);
                U32 hoisted__U32_1412 = 16;
                (void)hoisted__U32_1412;
                U32 hoisted__U32_1413 = U32_mul(i, hoisted__U32_1412);
                (void)hoisted__U32_1413;
                Type *hoisted__Type_1414 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1414;
                U64 hoisted__U64_1415 = (U64)(hoisted__U32_1413);
                (void)hoisted__U64_1415;
                Type_delete(hoisted__Type_1414, 1);
                Str *hoisted__Str_1416 = ptr_add(self->data, hoisted__U64_1415);
                (void)hoisted__Str_1416;
                (void)hoisted__Str_1416;
                Bool hoisted__Bool_1417 = 0;
                (void)hoisted__Bool_1417;
                Str_delete(hoisted__Str_1416, hoisted__Bool_1417);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1418 = U32_gt(_rc_U32_1410, _re_U32_1410);
                (void)_wcond_Bool_1418;
                if (_wcond_Bool_1418) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1410);
                U32_dec(&_rc_U32_1410);
                U32 hoisted__U32_1419 = 16;
                (void)hoisted__U32_1419;
                U32 hoisted__U32_1420 = U32_mul(i, hoisted__U32_1419);
                (void)hoisted__U32_1420;
                Type *hoisted__Type_1421 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1421;
                U64 hoisted__U64_1422 = (U64)(hoisted__U32_1420);
                (void)hoisted__U64_1422;
                Type_delete(hoisted__Type_1421, 1);
                Str *hoisted__Str_1423 = ptr_add(self->data, hoisted__U64_1422);
                (void)hoisted__Str_1423;
                (void)hoisted__Str_1423;
                Bool hoisted__Bool_1424 = 0;
                (void)hoisted__Bool_1424;
                Str_delete(hoisted__Str_1423, hoisted__Bool_1424);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1462 = 16;
    (void)hoisted__U32_1462;
    U32 hoisted__U32_1463 = U32_mul(self->cap, hoisted__U32_1462);
    (void)hoisted__U32_1463;
    Type *hoisted__Type_1464 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1464;
    U64 hoisted__U64_1465 = (U64)(hoisted__U32_1463);
    (void)hoisted__U64_1465;
    Type_delete(hoisted__Type_1464, 1);
    void * new_data = malloc(hoisted__U64_1465);
    {
        U32 _re_U32_1426 = self->cap;
        (void)_re_U32_1426;
        U32 _rc_U32_1426 = 0;
        (void)_rc_U32_1426;
        Bool hoisted__Bool_1461 = U32_lte(_rc_U32_1426, _re_U32_1426);
        (void)hoisted__Bool_1461;
        if (hoisted__Bool_1461) {
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
                U32 hoisted__U32_1429 = U32_mul(i, hoisted__U32_1428);
                (void)hoisted__U32_1429;
                Type *hoisted__Type_1430 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1430;
                U64 hoisted__U64_1431 = (U64)(hoisted__U32_1429);
                (void)hoisted__U64_1431;
                Type_delete(hoisted__Type_1430, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1431);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1432 = 16;
                (void)hoisted__U32_1432;
                U32 hoisted__U32_1433 = U32_mul(i, hoisted__U32_1432);
                (void)hoisted__U32_1433;
                Type *hoisted__Type_1434 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1434;
                U64 hoisted__U64_1435 = (U64)(hoisted__U32_1433);
                (void)hoisted__U64_1435;
                Type_delete(hoisted__Type_1434, 1);
                U32 hoisted__U32_1436 = 16;
                (void)hoisted__U32_1436;
                Type *hoisted__Type_1437 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1437;
                void *hoisted__v_1438 = ptr_add(new_data, hoisted__U64_1435);
                (void)hoisted__v_1438;
                (void)hoisted__v_1438;
                U64 hoisted__U64_1439 = (U64)(hoisted__U32_1436);
                (void)hoisted__U64_1439;
                Type_delete(hoisted__Type_1437, 1);
                memcpy(hoisted__v_1438, cloned, hoisted__U64_1439);
                U32 hoisted__U32_1440 = 16;
                (void)hoisted__U32_1440;
                Type *hoisted__Type_1441 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1441;
                I32 hoisted__I32_1442 = 0;
                (void)hoisted__I32_1442;
                U64 hoisted__U64_1443 = (U64)(hoisted__U32_1440);
                (void)hoisted__U64_1443;
                Type_delete(hoisted__Type_1441, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1442, hoisted__U64_1443); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1444 = U32_gt(_rc_U32_1426, _re_U32_1426);
                (void)_wcond_Bool_1444;
                if (_wcond_Bool_1444) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1426);
                U32_dec(&_rc_U32_1426);
                U32 hoisted__U32_1445 = 16;
                (void)hoisted__U32_1445;
                U32 hoisted__U32_1446 = U32_mul(i, hoisted__U32_1445);
                (void)hoisted__U32_1446;
                Type *hoisted__Type_1447 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1447;
                U64 hoisted__U64_1448 = (U64)(hoisted__U32_1446);
                (void)hoisted__U64_1448;
                Type_delete(hoisted__Type_1447, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1448);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1449 = 16;
                (void)hoisted__U32_1449;
                U32 hoisted__U32_1450 = U32_mul(i, hoisted__U32_1449);
                (void)hoisted__U32_1450;
                Type *hoisted__Type_1451 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1451;
                U64 hoisted__U64_1452 = (U64)(hoisted__U32_1450);
                (void)hoisted__U64_1452;
                Type_delete(hoisted__Type_1451, 1);
                U32 hoisted__U32_1453 = 16;
                (void)hoisted__U32_1453;
                Type *hoisted__Type_1454 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1454;
                void *hoisted__v_1455 = ptr_add(new_data, hoisted__U64_1452);
                (void)hoisted__v_1455;
                (void)hoisted__v_1455;
                U64 hoisted__U64_1456 = (U64)(hoisted__U32_1453);
                (void)hoisted__U64_1456;
                Type_delete(hoisted__Type_1454, 1);
                memcpy(hoisted__v_1455, cloned, hoisted__U64_1456);
                U32 hoisted__U32_1457 = 16;
                (void)hoisted__U32_1457;
                Type *hoisted__Type_1458 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1458;
                I32 hoisted__I32_1459 = 0;
                (void)hoisted__I32_1459;
                U64 hoisted__U64_1460 = (U64)(hoisted__U32_1457);
                (void)hoisted__U64_1460;
                Type_delete(hoisted__Type_1458, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1459, hoisted__U64_1460); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1466 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1466->data = new_data;
    hoisted__Array__Str_1466->cap = self->cap;
    (void)hoisted__Array__Str_1466;
    return hoisted__Array__Str_1466;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1467 = 16;
    (void)hoisted__U32_1467;
    return hoisted__U32_1467;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1468 = 16;
    (void)hoisted__U32_1468;
    Type *hoisted__Type_1469 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1469;
    U64 hoisted__U64_1470 = (U64)(hoisted__U32_1468);
    (void)hoisted__U64_1470;
    Type_delete(hoisted__Type_1469, 1);
    void * hoisted__v_1471 = malloc(hoisted__U64_1470);
    (void)hoisted__v_1471;
    U32 hoisted__U32_1472 = 0;
    (void)hoisted__U32_1472;
    I64 hoisted__I64_1473 = 1;
    (void)hoisted__I64_1473;
    Vec__Str *hoisted__Vec__Str_1474 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1474->data = hoisted__v_1471;
    hoisted__Vec__Str_1474->count = hoisted__U32_1472;
    hoisted__Vec__Str_1474->cap = hoisted__I64_1473;
    (void)hoisted__Vec__Str_1474;
    return hoisted__Vec__Str_1474;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1475 = self->count;
        (void)_re_U32_1475;
        U32 _rc_U32_1475 = 0;
        (void)_rc_U32_1475;
        Bool hoisted__Bool_1490 = U32_lte(_rc_U32_1475, _re_U32_1475);
        (void)hoisted__Bool_1490;
        if (hoisted__Bool_1490) {
            while (1) {
                Bool _wcond_Bool_1476 = U32_lt(_rc_U32_1475, _re_U32_1475);
                (void)_wcond_Bool_1476;
                if (_wcond_Bool_1476) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1475);
                U32_inc(&_rc_U32_1475);
                U32 hoisted__U32_1477 = 16;
                (void)hoisted__U32_1477;
                U32 hoisted__U32_1478 = U32_mul(i, hoisted__U32_1477);
                (void)hoisted__U32_1478;
                Type *hoisted__Type_1479 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1479;
                U64 hoisted__U64_1480 = (U64)(hoisted__U32_1478);
                (void)hoisted__U64_1480;
                Type_delete(hoisted__Type_1479, 1);
                Str *hoisted__Str_1481 = ptr_add(self->data, hoisted__U64_1480);
                (void)hoisted__Str_1481;
                (void)hoisted__Str_1481;
                Bool hoisted__Bool_1482 = 0;
                (void)hoisted__Bool_1482;
                Str_delete(hoisted__Str_1481, hoisted__Bool_1482);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1483 = U32_gt(_rc_U32_1475, _re_U32_1475);
                (void)_wcond_Bool_1483;
                if (_wcond_Bool_1483) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1475);
                U32_dec(&_rc_U32_1475);
                U32 hoisted__U32_1484 = 16;
                (void)hoisted__U32_1484;
                U32 hoisted__U32_1485 = U32_mul(i, hoisted__U32_1484);
                (void)hoisted__U32_1485;
                Type *hoisted__Type_1486 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1486;
                U64 hoisted__U64_1487 = (U64)(hoisted__U32_1485);
                (void)hoisted__U64_1487;
                Type_delete(hoisted__Type_1486, 1);
                Str *hoisted__Str_1488 = ptr_add(self->data, hoisted__U64_1487);
                (void)hoisted__Str_1488;
                (void)hoisted__Str_1488;
                Bool hoisted__Bool_1489 = 0;
                (void)hoisted__Bool_1489;
                Str_delete(hoisted__Str_1488, hoisted__Bool_1489);
            }
        }
    }
    U32 hoisted__U32_1491 = 0;
    (void)hoisted__U32_1491;
    self->count = hoisted__U32_1491;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1808 = 16;
    (void)hoisted__U32_1808;
    U32 hoisted__U32_1809 = U32_mul(self->cap, hoisted__U32_1808);
    (void)hoisted__U32_1809;
    Type *hoisted__Type_1810 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1810;
    U64 hoisted__U64_1811 = (U64)(hoisted__U32_1809);
    (void)hoisted__U64_1811;
    Type_delete(hoisted__Type_1810, 1);
    void * new_data = malloc(hoisted__U64_1811);
    {
        U32 _re_U32_1772 = self->count;
        (void)_re_U32_1772;
        U32 _rc_U32_1772 = 0;
        (void)_rc_U32_1772;
        Bool hoisted__Bool_1807 = U32_lte(_rc_U32_1772, _re_U32_1772);
        (void)hoisted__Bool_1807;
        if (hoisted__Bool_1807) {
            while (1) {
                Bool _wcond_Bool_1773 = U32_lt(_rc_U32_1772, _re_U32_1772);
                (void)_wcond_Bool_1773;
                if (_wcond_Bool_1773) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1772);
                U32_inc(&_rc_U32_1772);
                U32 hoisted__U32_1774 = 16;
                (void)hoisted__U32_1774;
                U32 hoisted__U32_1775 = U32_mul(i, hoisted__U32_1774);
                (void)hoisted__U32_1775;
                Type *hoisted__Type_1776 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1776;
                U64 hoisted__U64_1777 = (U64)(hoisted__U32_1775);
                (void)hoisted__U64_1777;
                Type_delete(hoisted__Type_1776, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1777);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1778 = 16;
                (void)hoisted__U32_1778;
                U32 hoisted__U32_1779 = U32_mul(i, hoisted__U32_1778);
                (void)hoisted__U32_1779;
                Type *hoisted__Type_1780 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1780;
                U64 hoisted__U64_1781 = (U64)(hoisted__U32_1779);
                (void)hoisted__U64_1781;
                Type_delete(hoisted__Type_1780, 1);
                U32 hoisted__U32_1782 = 16;
                (void)hoisted__U32_1782;
                Type *hoisted__Type_1783 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1783;
                void *hoisted__v_1784 = ptr_add(new_data, hoisted__U64_1781);
                (void)hoisted__v_1784;
                (void)hoisted__v_1784;
                U64 hoisted__U64_1785 = (U64)(hoisted__U32_1782);
                (void)hoisted__U64_1785;
                Type_delete(hoisted__Type_1783, 1);
                memcpy(hoisted__v_1784, cloned, hoisted__U64_1785);
                U32 hoisted__U32_1786 = 16;
                (void)hoisted__U32_1786;
                Type *hoisted__Type_1787 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1787;
                I32 hoisted__I32_1788 = 0;
                (void)hoisted__I32_1788;
                U64 hoisted__U64_1789 = (U64)(hoisted__U32_1786);
                (void)hoisted__U64_1789;
                Type_delete(hoisted__Type_1787, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1788, hoisted__U64_1789); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1790 = U32_gt(_rc_U32_1772, _re_U32_1772);
                (void)_wcond_Bool_1790;
                if (_wcond_Bool_1790) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1772);
                U32_dec(&_rc_U32_1772);
                U32 hoisted__U32_1791 = 16;
                (void)hoisted__U32_1791;
                U32 hoisted__U32_1792 = U32_mul(i, hoisted__U32_1791);
                (void)hoisted__U32_1792;
                Type *hoisted__Type_1793 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1793;
                U64 hoisted__U64_1794 = (U64)(hoisted__U32_1792);
                (void)hoisted__U64_1794;
                Type_delete(hoisted__Type_1793, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1794);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1795 = 16;
                (void)hoisted__U32_1795;
                U32 hoisted__U32_1796 = U32_mul(i, hoisted__U32_1795);
                (void)hoisted__U32_1796;
                Type *hoisted__Type_1797 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1797;
                U64 hoisted__U64_1798 = (U64)(hoisted__U32_1796);
                (void)hoisted__U64_1798;
                Type_delete(hoisted__Type_1797, 1);
                U32 hoisted__U32_1799 = 16;
                (void)hoisted__U32_1799;
                Type *hoisted__Type_1800 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1800;
                void *hoisted__v_1801 = ptr_add(new_data, hoisted__U64_1798);
                (void)hoisted__v_1801;
                (void)hoisted__v_1801;
                U64 hoisted__U64_1802 = (U64)(hoisted__U32_1799);
                (void)hoisted__U64_1802;
                Type_delete(hoisted__Type_1800, 1);
                memcpy(hoisted__v_1801, cloned, hoisted__U64_1802);
                U32 hoisted__U32_1803 = 16;
                (void)hoisted__U32_1803;
                Type *hoisted__Type_1804 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1804;
                I32 hoisted__I32_1805 = 0;
                (void)hoisted__I32_1805;
                U64 hoisted__U64_1806 = (U64)(hoisted__U32_1803);
                (void)hoisted__U64_1806;
                Type_delete(hoisted__Type_1804, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1805, hoisted__U64_1806); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1812 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1812->data = new_data;
    hoisted__Vec__Str_1812->count = self->count;
    hoisted__Vec__Str_1812->cap = self->cap;
    (void)hoisted__Vec__Str_1812;
    return hoisted__Vec__Str_1812;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1813 = 16;
    (void)hoisted__U32_1813;
    return hoisted__U32_1813;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1816 = 8;
    (void)hoisted__U32_1816;
    return hoisted__U32_1816;
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
    I64 hoisted__I64_2035 = 0;
    (void)hoisted__I64_2035;
    Bool hoisted__Bool_2036 = I64_eq(val, hoisted__I64_2035);
    (void)hoisted__Bool_2036;
    if (hoisted__Bool_2036) {
        U64 hoisted__U64_2005 = 2ULL;
        (void)hoisted__U64_2005;
        void * buf = malloc(hoisted__U64_2005);
        I64 hoisted__I64_2006 = 48;
        (void)hoisted__I64_2006;
        U64 hoisted__U64_2007 = 1ULL;
        (void)hoisted__U64_2007;
        memcpy(buf, &hoisted__I64_2006, hoisted__U64_2007);
        U64 hoisted__U64_2008 = 1ULL;
        (void)hoisted__U64_2008;
        void *hoisted__v_2009 = ptr_add(buf, hoisted__U64_2008);
        (void)hoisted__v_2009;
        (void)hoisted__v_2009;
        I32 hoisted__I32_2010 = 0;
        (void)hoisted__I32_2010;
        U64 hoisted__U64_2011 = 1ULL;
        (void)hoisted__U64_2011;
        memset(hoisted__v_2009, hoisted__I32_2010, hoisted__U64_2011);
        I64 hoisted__I64_2012 = 1;
        (void)hoisted__I64_2012;
        I64 hoisted__I64_2013 = 1;
        (void)hoisted__I64_2013;
        Str *hoisted__Str_2014 = malloc(sizeof(Str));
        hoisted__Str_2014->c_str = buf;
        hoisted__Str_2014->count = hoisted__I64_2012;
        hoisted__Str_2014->cap = hoisted__I64_2013;
        (void)hoisted__Str_2014;
        { Str * _ret_val = hoisted__Str_2014;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_2037 = 0;
    (void)hoisted__I64_2037;
    Bool hoisted__Bool_2038 = I64_lt(val, hoisted__I64_2037);
    (void)hoisted__Bool_2038;
    if (hoisted__Bool_2038) {
        Bool hoisted__Bool_2015 = 1;
        (void)hoisted__Bool_2015;
        is_neg = hoisted__Bool_2015;
        I64 hoisted__I64_2016 = 0;
        (void)hoisted__I64_2016;
        I64 hoisted__I64_2017 = I64_sub(hoisted__I64_2016, val);
        (void)hoisted__I64_2017;
        v = hoisted__I64_2017;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_2019 = 0;
        (void)hoisted__I64_2019;
        Bool _wcond_Bool_2018 = I64_gt(tmp, hoisted__I64_2019);
        (void)_wcond_Bool_2018;
        if (_wcond_Bool_2018) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_2020 = 10;
        (void)hoisted__I64_2020;
        I64 hoisted__I64_2021 = I64_div(tmp, hoisted__I64_2020);
        (void)hoisted__I64_2021;
        tmp = hoisted__I64_2021;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_2039 = 1ULL;
    (void)hoisted__U64_2039;
    U64 hoisted__U64_2040 = U64_add(total, hoisted__U64_2039);
    (void)hoisted__U64_2040;
    void * buf = malloc(hoisted__U64_2040);
    if (is_neg) {
        I64 hoisted__I64_2022 = 45;
        (void)hoisted__I64_2022;
        U64 hoisted__U64_2023 = 1ULL;
        (void)hoisted__U64_2023;
        memcpy(buf, &hoisted__I64_2022, hoisted__U64_2023);
    }
    U64 hoisted__U64_2041 = 1ULL;
    (void)hoisted__U64_2041;
    U64 i = U64_sub(total, hoisted__U64_2041);
    while (1) {
        I64 hoisted__I64_2025 = 0;
        (void)hoisted__I64_2025;
        Bool _wcond_Bool_2024 = I64_gt(v, hoisted__I64_2025);
        (void)_wcond_Bool_2024;
        if (_wcond_Bool_2024) {
        } else {
            break;
        }
        I64 hoisted__I64_2026 = 10;
        (void)hoisted__I64_2026;
        I64 hoisted__I64_2027 = I64_mod(v, hoisted__I64_2026);
        (void)hoisted__I64_2027;
        I64 hoisted__I64_2028 = 48;
        (void)hoisted__I64_2028;
        I64 hoisted__I64_2029 = I64_add(hoisted__I64_2027, hoisted__I64_2028);
        (void)hoisted__I64_2029;
        void *hoisted__v_2030 = ptr_add(buf, i);
        (void)hoisted__v_2030;
        (void)hoisted__v_2030;
        U8 hoisted__U8_2031 = I64_to_u8(hoisted__I64_2029);
        (void)hoisted__U8_2031;
        U64 hoisted__U64_2032 = 1ULL;
        (void)hoisted__U64_2032;
        memcpy(hoisted__v_2030, &hoisted__U8_2031, hoisted__U64_2032);
        I64 hoisted__I64_2033 = 10;
        (void)hoisted__I64_2033;
        I64 hoisted__I64_2034 = I64_div(v, hoisted__I64_2033);
        (void)hoisted__I64_2034;
        v = hoisted__I64_2034;
        U64_dec(&i);
    }
    void *hoisted__v_2042 = ptr_add(buf, total);
    (void)hoisted__v_2042;
    (void)hoisted__v_2042;
    I32 hoisted__I32_2043 = 0;
    (void)hoisted__I32_2043;
    U64 hoisted__U64_2044 = 1ULL;
    (void)hoisted__U64_2044;
    memset(hoisted__v_2042, hoisted__I32_2043, hoisted__U64_2044);
    Str *hoisted__Str_2045 = malloc(sizeof(Str));
    hoisted__Str_2045->c_str = buf;
    hoisted__Str_2045->count = total;
    hoisted__Str_2045->cap = total;
    (void)hoisted__Str_2045;
    return hoisted__Str_2045;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_2065 = 8;
    (void)hoisted__U32_2065;
    return hoisted__U32_2065;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2223 = 0;
    (void)hoisted__U32_2223;
    U64 hoisted__U64_2224 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2223); });
    (void)hoisted__U64_2224;
    return hoisted__U64_2224;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2227 = I64_cmp(a, b);
    (void)hoisted__I64_2227;
    I64 hoisted__I64_2228 = -1;
    (void)hoisted__I64_2228;
    Bool hoisted__Bool_2229 = I64_eq(hoisted__I64_2227, hoisted__I64_2228);
    (void)hoisted__Bool_2229;
    return hoisted__Bool_2229;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2230 = I64_cmp(a, b);
    (void)hoisted__I64_2230;
    I64 hoisted__I64_2231 = 1;
    (void)hoisted__I64_2231;
    Bool hoisted__Bool_2232 = I64_eq(hoisted__I64_2230, hoisted__I64_2231);
    (void)hoisted__Bool_2232;
    return hoisted__Bool_2232;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2233 = I64_eq(a, b);
    (void)hoisted__Bool_2233;
    Bool hoisted__Bool_2234 = not(hoisted__Bool_2233);
    (void)hoisted__Bool_2234;
    return hoisted__Bool_2234;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2285 = 0;
    (void)_m_Bool_2285;
    {
        Bool hoisted__Bool_2288 = 1;
        (void)hoisted__Bool_2288;
        Bool hoisted__Bool_2289 = Bool_eq(a, hoisted__Bool_2288);
        (void)hoisted__Bool_2289;
        if (hoisted__Bool_2289) {
            Bool hoisted__Bool_2286 = Bool_clone(&b);
            (void)hoisted__Bool_2286;
            _m_Bool_2285 = hoisted__Bool_2286;
        } else {
            Bool hoisted__Bool_2287 = 0;
            (void)hoisted__Bool_2287;
            _m_Bool_2285 = hoisted__Bool_2287;
        }
    }
    return _m_Bool_2285;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2299 = Bool_eq(a, b);
    (void)hoisted__Bool_2299;
    if (hoisted__Bool_2299) {
        I64 hoisted__I64_2297 = 0;
        (void)hoisted__I64_2297;
        { I64 _ret_val = hoisted__I64_2297;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2298 = -1;
        (void)hoisted__I64_2298;
        return hoisted__I64_2298;
    }
    I64 hoisted__I64_2300 = 1;
    (void)hoisted__I64_2300;
    return hoisted__I64_2300;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2301 = 1;
    (void)hoisted__U32_2301;
    return hoisted__U32_2301;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2302 = 0;
    (void)hoisted__U32_2302;
    U64 hoisted__U64_2303 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2302); });
    (void)hoisted__U64_2303;
    return hoisted__U64_2303;
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
    Bool hoisted__Bool_2329 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2329;
    if (hoisted__Bool_2329) {
        Bool hoisted__Bool_2319 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2319;
        { Bool _ret_val = hoisted__Bool_2319;
                return _ret_val; }
    }
    Bool hoisted__Bool_2330 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2330;
    if (hoisted__Bool_2330) {
        Bool hoisted__Bool_2320 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2320;
        { Bool _ret_val = hoisted__Bool_2320;
                return _ret_val; }
    }
    Bool hoisted__Bool_2331 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2331;
    if (hoisted__Bool_2331) {
        Bool hoisted__Bool_2321 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2321;
        { Bool _ret_val = hoisted__Bool_2321;
                return _ret_val; }
    }
    Bool hoisted__Bool_2332 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2332;
    if (hoisted__Bool_2332) {
        Bool hoisted__Bool_2322 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2322;
        { Bool _ret_val = hoisted__Bool_2322;
                return _ret_val; }
    }
    Bool hoisted__Bool_2333 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2333;
    if (hoisted__Bool_2333) {
        Bool hoisted__Bool_2323 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2323;
        { Bool _ret_val = hoisted__Bool_2323;
                return _ret_val; }
    }
    Bool hoisted__Bool_2334 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2334;
    if (hoisted__Bool_2334) {
        Bool hoisted__Bool_2324 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2324;
        { Bool _ret_val = hoisted__Bool_2324;
                return _ret_val; }
    }
    Bool hoisted__Bool_2335 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2335;
    if (hoisted__Bool_2335) {
        Bool hoisted__Bool_2325 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2325;
        { Bool _ret_val = hoisted__Bool_2325;
                return _ret_val; }
    }
    Bool hoisted__Bool_2336 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2336;
    if (hoisted__Bool_2336) {
        Bool hoisted__Bool_2326 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2326;
        { Bool _ret_val = hoisted__Bool_2326;
                return _ret_val; }
    }
    Bool hoisted__Bool_2337 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2337;
    if (hoisted__Bool_2337) {
        Bool hoisted__Bool_2327 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2327;
        { Bool _ret_val = hoisted__Bool_2327;
                return _ret_val; }
    }
    Bool hoisted__Bool_2338 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2338;
    if (hoisted__Bool_2338) {
        Bool hoisted__Bool_2328 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2328;
        { Bool _ret_val = hoisted__Bool_2328;
                return _ret_val; }
    }
    Bool hoisted__Bool_2339 = 0;
    (void)hoisted__Bool_2339;
    return hoisted__Bool_2339;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2361 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2361;
    if (hoisted__Bool_2361) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2362 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2362;
    if (hoisted__Bool_2362) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2363 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2363;
    if (hoisted__Bool_2363) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2364 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2364;
    if (hoisted__Bool_2364) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2365 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2365;
    if (hoisted__Bool_2365) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2366 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2366;
    if (hoisted__Bool_2366) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2367 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2367;
    if (hoisted__Bool_2367) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2368 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2368;
    if (hoisted__Bool_2368) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2369 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2369;
    if (hoisted__Bool_2369) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2370 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2370;
    if (hoisted__Bool_2370) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2371 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2371;
    UNREACHABLE(&hoisted__Str_2371);
    Str_delete(&hoisted__Str_2371, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2372 = 4;
    (void)hoisted__U32_2372;
    return hoisted__U32_2372;
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
    Bool hoisted__Bool_2424 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2424;
    if (hoisted__Bool_2424) {
        Str *hoisted__Str_2414 = get_payload(self);
        (void)hoisted__Str_2414;
        (void)hoisted__Str_2414;
        Bool hoisted__Bool_2415 = 0;
        (void)hoisted__Bool_2415;
        Str_delete(hoisted__Str_2414, hoisted__Bool_2415);
    }
    Bool hoisted__Bool_2425 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2425;
    if (hoisted__Bool_2425) {
        Str *hoisted__Str_2416 = get_payload(self);
        (void)hoisted__Str_2416;
        (void)hoisted__Str_2416;
        Bool hoisted__Bool_2417 = 0;
        (void)hoisted__Bool_2417;
        Str_delete(hoisted__Str_2416, hoisted__Bool_2417);
    }
    Bool hoisted__Bool_2426 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2426;
    if (hoisted__Bool_2426) {
        Str *hoisted__Str_2418 = get_payload(self);
        (void)hoisted__Str_2418;
        (void)hoisted__Str_2418;
        Bool hoisted__Bool_2419 = 0;
        (void)hoisted__Bool_2419;
        Str_delete(hoisted__Str_2418, hoisted__Bool_2419);
    }
    Bool hoisted__Bool_2427 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2427;
    if (hoisted__Bool_2427) {
        Primitive *hoisted__Primitive_2420 = get_payload(self);
        (void)hoisted__Primitive_2420;
        (void)hoisted__Primitive_2420;
        Bool hoisted__Bool_2421 = 0;
        (void)hoisted__Bool_2421;
        Primitive_delete(hoisted__Primitive_2420, hoisted__Bool_2421);
    }
    Bool hoisted__Bool_2428 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2428;
    if (hoisted__Bool_2428) {
        Str *hoisted__Str_2422 = get_payload(self);
        (void)hoisted__Str_2422;
        (void)hoisted__Str_2422;
        Bool hoisted__Bool_2423 = 0;
        (void)hoisted__Bool_2423;
        Str_delete(hoisted__Str_2422, hoisted__Bool_2423);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2512 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2512;
    if (hoisted__Bool_2512) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2513 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2513;
    if (hoisted__Bool_2513) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2514 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2514;
    if (hoisted__Bool_2514) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2504 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2504;
        Type *hoisted__Type_2505 = Type_Struct(hoisted__Str_2504);
        (void)hoisted__Type_2505;
        { Type * _ret_val = hoisted__Type_2505;
                return _ret_val; }
    }
    Bool hoisted__Bool_2515 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2515;
    if (hoisted__Bool_2515) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2516 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2516;
    if (hoisted__Bool_2516) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2506 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2506;
        Type *hoisted__Type_2507 = Type_Enum(hoisted__Str_2506);
        (void)hoisted__Type_2507;
        { Type * _ret_val = hoisted__Type_2507;
                return _ret_val; }
    }
    Bool hoisted__Bool_2517 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2517;
    if (hoisted__Bool_2517) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2518 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2518;
    if (hoisted__Bool_2518) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2519 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2519;
    if (hoisted__Bool_2519) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2520 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2520;
    if (hoisted__Bool_2520) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2521 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2521;
    if (hoisted__Bool_2521) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2508 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2508;
        Type *hoisted__Type_2509 = Type_Custom(hoisted__Str_2508);
        (void)hoisted__Type_2509;
        { Type * _ret_val = hoisted__Type_2509;
                return _ret_val; }
    }
    Bool hoisted__Bool_2522 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2522;
    if (hoisted__Bool_2522) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2510 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2510;
        Type *hoisted__Type_2511 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2510; _oa; }));
        (void)hoisted__Type_2511;
        { Type * _ret_val = hoisted__Type_2511;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2523 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2523;
    Type *hoisted__Type_2524 = Type_FuncPtrSig(hoisted__Str_2523);
    (void)hoisted__Type_2524;
    return hoisted__Type_2524;
}

U32 Type_size(void) {
    U32 hoisted__U32_2525 = 24;
    (void)hoisted__U32_2525;
    return hoisted__U32_2525;
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
    Bool hoisted__Bool_2626 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2626;
    if (hoisted__Bool_2626) {
        Bool hoisted__Bool_2618 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2618;
        { Bool _ret_val = hoisted__Bool_2618;
                return _ret_val; }
    }
    Bool hoisted__Bool_2627 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2627;
    if (hoisted__Bool_2627) {
        Bool hoisted__Bool_2619 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2619;
        { Bool _ret_val = hoisted__Bool_2619;
                return _ret_val; }
    }
    Bool hoisted__Bool_2628 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2628;
    if (hoisted__Bool_2628) {
        Bool hoisted__Bool_2620 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2620;
        { Bool _ret_val = hoisted__Bool_2620;
                return _ret_val; }
    }
    Bool hoisted__Bool_2629 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2629;
    if (hoisted__Bool_2629) {
        Bool hoisted__Bool_2621 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2621;
        { Bool _ret_val = hoisted__Bool_2621;
                return _ret_val; }
    }
    Bool hoisted__Bool_2630 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2630;
    if (hoisted__Bool_2630) {
        Bool hoisted__Bool_2622 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2622;
        { Bool _ret_val = hoisted__Bool_2622;
                return _ret_val; }
    }
    Bool hoisted__Bool_2631 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2631;
    if (hoisted__Bool_2631) {
        Bool hoisted__Bool_2623 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2623;
        { Bool _ret_val = hoisted__Bool_2623;
                return _ret_val; }
    }
    Bool hoisted__Bool_2632 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2632;
    if (hoisted__Bool_2632) {
        Bool hoisted__Bool_2624 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2624;
        { Bool _ret_val = hoisted__Bool_2624;
                return _ret_val; }
    }
    Bool hoisted__Bool_2633 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2633;
    if (hoisted__Bool_2633) {
        Bool hoisted__Bool_2625 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2625;
        { Bool _ret_val = hoisted__Bool_2625;
                return _ret_val; }
    }
    Bool hoisted__Bool_2634 = 0;
    (void)hoisted__Bool_2634;
    return hoisted__Bool_2634;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2652 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2652;
    if (hoisted__Bool_2652) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2653 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2653;
    if (hoisted__Bool_2653) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2654 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2654;
    if (hoisted__Bool_2654) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2655 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2655;
    if (hoisted__Bool_2655) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2656 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2656;
    if (hoisted__Bool_2656) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2657 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2657;
    if (hoisted__Bool_2657) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2658 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2658;
    if (hoisted__Bool_2658) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2659 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2659;
    if (hoisted__Bool_2659) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    static Str hoisted__Str_2660 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2660;
    UNREACHABLE(&hoisted__Str_2660);
    Str_delete(&hoisted__Str_2660, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2661 = 4;
    (void)hoisted__U32_2661;
    return hoisted__U32_2661;
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
    Bool hoisted__Bool_2666 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2666;
    if (hoisted__Bool_2666) {
        Bool hoisted__Bool_2663 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2663;
        { Bool _ret_val = hoisted__Bool_2663;
                return _ret_val; }
    }
    Bool hoisted__Bool_2667 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2667;
    if (hoisted__Bool_2667) {
        Bool hoisted__Bool_2664 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2664;
        { Bool _ret_val = hoisted__Bool_2664;
                return _ret_val; }
    }
    Bool hoisted__Bool_2668 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2668;
    if (hoisted__Bool_2668) {
        Bool hoisted__Bool_2665 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2665;
        { Bool _ret_val = hoisted__Bool_2665;
                return _ret_val; }
    }
    Bool hoisted__Bool_2669 = 0;
    (void)hoisted__Bool_2669;
    return hoisted__Bool_2669;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2677 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2677;
    if (hoisted__Bool_2677) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2678 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2678;
    if (hoisted__Bool_2678) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2679 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2679;
    if (hoisted__Bool_2679) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2680 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2680;
    UNREACHABLE(&hoisted__Str_2680);
    Str_delete(&hoisted__Str_2680, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2681 = 4;
    (void)hoisted__U32_2681;
    return hoisted__U32_2681;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2683 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2683;
    Declaration *hoisted__Declaration_2684 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2684->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2684->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2684->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2684->is_mut = self->is_mut;
    hoisted__Declaration_2684->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2684->is_priv = self->is_priv;
    hoisted__Declaration_2684->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2684->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2684->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2684->default_value = hoisted__Expr_2683;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2684->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2684;
    return hoisted__Declaration_2684;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2685 = 0;
    (void)hoisted__Bool_2685;
    Str_delete(&self->name, hoisted__Bool_2685);
    Bool hoisted__Bool_2686 = 0;
    (void)hoisted__Bool_2686;
    Str_delete(&self->doc, hoisted__Bool_2686);
    Bool hoisted__Bool_2687 = 0;
    (void)hoisted__Bool_2687;
    Str_delete(&self->explicit_type, hoisted__Bool_2687);
    Bool hoisted__Bool_2688 = 0;
    (void)hoisted__Bool_2688;
    Bool_delete(&self->is_mut, hoisted__Bool_2688);
    Bool hoisted__Bool_2689 = 0;
    (void)hoisted__Bool_2689;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2689);
    Bool hoisted__Bool_2690 = 0;
    (void)hoisted__Bool_2690;
    Bool_delete(&self->is_priv, hoisted__Bool_2690);
    Bool hoisted__Bool_2691 = 0;
    (void)hoisted__Bool_2691;
    Bool_delete(&self->used, hoisted__Bool_2691);
    Bool hoisted__Bool_2692 = 0;
    (void)hoisted__Bool_2692;
    OwnType_delete(&self->own_type, hoisted__Bool_2692);
    Bool hoisted__Bool_2693 = 0;
    (void)hoisted__Bool_2693;
    Type_delete(&self->til_type, hoisted__Bool_2693);
    Bool hoisted__Bool_2694 = 1;
    (void)hoisted__Bool_2694;
    Expr_delete(self->default_value, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    Str_delete(&self->orig_name, hoisted__Bool_2695);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2696 = 104;
    (void)hoisted__U32_2696;
    return hoisted__U32_2696;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2698 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2698->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2698->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2698->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2698->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2698->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2698->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2698->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2698->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2698->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2698->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2698->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2698;
    return hoisted__FunctionDef_2698;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2699 = 0;
    (void)hoisted__Bool_2699;
    FuncType_delete(&self->func_type, hoisted__Bool_2699);
    Bool hoisted__Bool_2700 = 0;
    (void)hoisted__Bool_2700;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2700);
    Bool hoisted__Bool_2701 = 0;
    (void)hoisted__Bool_2701;
    Str_delete(&self->return_type, hoisted__Bool_2701);
    Bool hoisted__Bool_2702 = 0;
    (void)hoisted__Bool_2702;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2702);
    Bool hoisted__Bool_2703 = 0;
    (void)hoisted__Bool_2703;
    I32_delete(&self->variadic_index, hoisted__Bool_2703);
    Bool hoisted__Bool_2704 = 0;
    (void)hoisted__Bool_2704;
    I32_delete(&self->kwargs_index, hoisted__Bool_2704);
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Bool_delete(&self->auto_generated, hoisted__Bool_2706);
    Bool hoisted__Bool_2707 = 0;
    (void)hoisted__Bool_2707;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2707);
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 0;
    (void)hoisted__Bool_2709;
    Str_delete(&self->closure_name, hoisted__Bool_2709);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2710 = 0;
    (void)hoisted__U32_2710;
    U64 hoisted__U64_2711 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2710); });
    (void)hoisted__U64_2711;
    return hoisted__U64_2711;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2712 = 104;
    (void)hoisted__U32_2712;
    return hoisted__U32_2712;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2715 = malloc(sizeof(FCallData));
    hoisted__FCallData_2715->is_splat = self->is_splat;
    hoisted__FCallData_2715->does_throw = self->does_throw;
    hoisted__FCallData_2715->is_bang = self->is_bang;
    hoisted__FCallData_2715->own_args = self->own_args;
    hoisted__FCallData_2715->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2715->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2715;
    return hoisted__FCallData_2715;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2716 = 0;
    (void)hoisted__Bool_2716;
    Bool_delete(&self->is_splat, hoisted__Bool_2716);
    Bool hoisted__Bool_2717 = 0;
    (void)hoisted__Bool_2717;
    Bool_delete(&self->does_throw, hoisted__Bool_2717);
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    Bool_delete(&self->is_bang, hoisted__Bool_2718);
    Bool hoisted__Bool_2719 = 0;
    (void)hoisted__Bool_2719;
    U64_delete(&self->own_args, hoisted__Bool_2719);
    Bool hoisted__Bool_2720 = 0;
    (void)hoisted__Bool_2720;
    Bool_delete(&self->swap_replace, hoisted__Bool_2720);
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Type_delete(&self->til_type, hoisted__Bool_2721);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2722 = 0;
    (void)hoisted__U32_2722;
    U64 hoisted__U64_2723 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2722); });
    (void)hoisted__U64_2723;
    return hoisted__U64_2723;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2724 = 48;
    (void)hoisted__U32_2724;
    return hoisted__U32_2724;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2736 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2736->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2736->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2736;
    return hoisted__LiteralNumData_2736;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Str_delete(&self->text, hoisted__Bool_2737);
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Type_delete(&self->til_type, hoisted__Bool_2738);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2739 = 0;
    (void)hoisted__U32_2739;
    U64 hoisted__U64_2740 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2739); });
    (void)hoisted__U64_2740;
    return hoisted__U64_2740;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2741 = 40;
    (void)hoisted__U32_2741;
    return hoisted__U32_2741;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2751 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2751->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2751->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2751;
    return hoisted__IdentData_2751;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    Str_delete(&self->name, hoisted__Bool_2752);
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Type_delete(&self->til_type, hoisted__Bool_2753);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2754 = 0;
    (void)hoisted__U32_2754;
    U64 hoisted__U64_2755 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2754); });
    (void)hoisted__U64_2755;
    return hoisted__U64_2755;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2756 = 40;
    (void)hoisted__U32_2756;
    return hoisted__U32_2756;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2762 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2762->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2762->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2762;
    return hoisted__FieldAccessData_2762;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2763 = 0;
    (void)hoisted__Bool_2763;
    Str_delete(&self->name, hoisted__Bool_2763);
    Bool hoisted__Bool_2764 = 0;
    (void)hoisted__Bool_2764;
    Type_delete(&self->til_type, hoisted__Bool_2764);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2765 = 0;
    (void)hoisted__U32_2765;
    U64 hoisted__U64_2766 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2765); });
    (void)hoisted__U64_2766;
    return hoisted__U64_2766;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2767 = 40;
    (void)hoisted__U32_2767;
    return hoisted__U32_2767;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2848 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2848->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2848->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2848->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2848->is_interface = self->is_interface;
    hoisted__StructDef_2848->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2848->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2848;
    return hoisted__StructDef_2848;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2849 = 0;
    (void)hoisted__Bool_2849;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2849);
    Bool hoisted__Bool_2850 = 0;
    (void)hoisted__Bool_2850;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2850);
    Bool hoisted__Bool_2851 = 0;
    (void)hoisted__Bool_2851;
    Str_delete(&self->c_tag, hoisted__Bool_2851);
    Bool hoisted__Bool_2852 = 0;
    (void)hoisted__Bool_2852;
    Bool_delete(&self->is_interface, hoisted__Bool_2852);
    Bool hoisted__Bool_2853 = 0;
    (void)hoisted__Bool_2853;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2853);
    Bool hoisted__Bool_2854 = 0;
    (void)hoisted__Bool_2854;
    Str_delete(&self->implements_name, hoisted__Bool_2854);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2855 = 0;
    (void)hoisted__U32_2855;
    U64 hoisted__U64_2856 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2855); });
    (void)hoisted__U64_2856;
    return hoisted__U64_2856;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2857 = 72;
    (void)hoisted__U32_2857;
    return hoisted__U32_2857;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2862 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2862->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2862->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2862->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2862->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2862->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2862->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2862;
    return hoisted__EnumDef_2862;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2863 = 0;
    (void)hoisted__Bool_2863;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2863);
    Bool hoisted__Bool_2864 = 0;
    (void)hoisted__Bool_2864;
    Vec__Str_delete(&self->variants, hoisted__Bool_2864);
    Bool hoisted__Bool_2865 = 0;
    (void)hoisted__Bool_2865;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2865);
    Bool hoisted__Bool_2866 = 0;
    (void)hoisted__Bool_2866;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2866);
    Bool hoisted__Bool_2867 = 0;
    (void)hoisted__Bool_2867;
    Str_delete(&self->implements_name, hoisted__Bool_2867);
    Bool hoisted__Bool_2868 = 0;
    (void)hoisted__Bool_2868;
    Str_delete(&self->tag_type, hoisted__Bool_2868);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2869 = 0;
    (void)hoisted__U32_2869;
    U64 hoisted__U64_2870 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2869); });
    (void)hoisted__U64_2870;
    return hoisted__U64_2870;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2871 = 112;
    (void)hoisted__U32_2871;
    return hoisted__U32_2871;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2967 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2967->name = *_ca; free(_ca); }
    hoisted__AssignData_2967->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2967->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2967->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2967;
    return hoisted__AssignData_2967;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2968 = 0;
    (void)hoisted__Bool_2968;
    Str_delete(&self->name, hoisted__Bool_2968);
    Bool hoisted__Bool_2969 = 0;
    (void)hoisted__Bool_2969;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2969);
    Bool hoisted__Bool_2970 = 0;
    (void)hoisted__Bool_2970;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2970);
    Bool hoisted__Bool_2971 = 0;
    (void)hoisted__Bool_2971;
    Bool_delete(&self->swap_replace, hoisted__Bool_2971);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2972 = 0;
    (void)hoisted__U32_2972;
    U64 hoisted__U64_2973 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2972); });
    (void)hoisted__U64_2973;
    return hoisted__U64_2973;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2974 = 24;
    (void)hoisted__U32_2974;
    return hoisted__U32_2974;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2976 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2976->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2976->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2976;
    return hoisted__FieldAssignData_2976;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2977 = 0;
    (void)hoisted__Bool_2977;
    Str_delete(&self->name, hoisted__Bool_2977);
    Bool hoisted__Bool_2978 = 0;
    (void)hoisted__Bool_2978;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2978);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2979 = 0;
    (void)hoisted__U32_2979;
    U64 hoisted__U64_2980 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2979); });
    (void)hoisted__U64_2980;
    return hoisted__U64_2980;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2981 = 24;
    (void)hoisted__U32_2981;
    return hoisted__U32_2981;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2983 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2983->name = *_ca; free(_ca); }
    hoisted__ForInData_2983->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2983->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2983->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2983->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2983;
    return hoisted__ForInData_2983;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2984 = 0;
    (void)hoisted__Bool_2984;
    Str_delete(&self->name, hoisted__Bool_2984);
    Bool hoisted__Bool_2985 = 0;
    (void)hoisted__Bool_2985;
    Bool_delete(&self->is_mut, hoisted__Bool_2985);
    Bool hoisted__Bool_2986 = 0;
    (void)hoisted__Bool_2986;
    Type_delete(&self->til_type, hoisted__Bool_2986);
    Bool hoisted__Bool_2987 = 0;
    (void)hoisted__Bool_2987;
    Str_delete(&self->name2, hoisted__Bool_2987);
    Bool hoisted__Bool_2988 = 0;
    (void)hoisted__Bool_2988;
    Bool_delete(&self->is_mut2, hoisted__Bool_2988);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2989 = 0;
    (void)hoisted__U32_2989;
    U64 hoisted__U64_2990 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2989); });
    (void)hoisted__U64_2990;
    return hoisted__U64_2990;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2991 = 72;
    (void)hoisted__U32_2991;
    return hoisted__U32_2991;
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
    Bool hoisted__Bool_3021 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3021;
    if (hoisted__Bool_3021) {
        Str *hoisted__Str_3015 = get_payload(self);
        (void)hoisted__Str_3015;
        (void)hoisted__Str_3015;
        Bool hoisted__Bool_3016 = 0;
        (void)hoisted__Bool_3016;
        Str_delete(hoisted__Str_3015, hoisted__Bool_3016);
    }
    Bool hoisted__Bool_3022 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3022;
    if (hoisted__Bool_3022) {
        LiteralNumData *hoisted__LiteralNumData_3017 = get_payload(self);
        (void)hoisted__LiteralNumData_3017;
        (void)hoisted__LiteralNumData_3017;
        Bool hoisted__Bool_3018 = 0;
        (void)hoisted__Bool_3018;
        LiteralNumData_delete(hoisted__LiteralNumData_3017, hoisted__Bool_3018);
    }
    Bool hoisted__Bool_3023 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3023;
    if (hoisted__Bool_3023) {
        Bool *hoisted__Bool_3019 = get_payload(self);
        (void)hoisted__Bool_3019;
        (void)hoisted__Bool_3019;
        Bool hoisted__Bool_3020 = 0;
        (void)hoisted__Bool_3020;
        Bool_delete(hoisted__Bool_3019, hoisted__Bool_3020);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_3072 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3072;
    if (hoisted__Bool_3072) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3067 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3067;
        Literal *hoisted__Literal_3068 = Literal_Str(hoisted__Str_3067);
        (void)hoisted__Literal_3068;
        { Literal * _ret_val = hoisted__Literal_3068;
                return _ret_val; }
    }
    Bool hoisted__Bool_3073 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3073;
    if (hoisted__Bool_3073) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3069 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3069;
        Literal *hoisted__Literal_3070 = Literal_Num(hoisted__LiteralNumData_3069);
        (void)hoisted__Literal_3070;
        { Literal * _ret_val = hoisted__Literal_3070;
                return _ret_val; }
    }
    Bool hoisted__Bool_3074 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3074;
    if (hoisted__Bool_3074) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3071 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3071;
        { Literal * _ret_val = hoisted__Literal_3071;
                return _ret_val; }
    }
    Bool hoisted__Bool_3075 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_3075;
    if (hoisted__Bool_3075) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_3076 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_3076;
    if (hoisted__Bool_3076) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3077 = 48;
    (void)hoisted__U32_3077;
    return hoisted__U32_3077;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3080 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3080->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3080->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3080;
    return hoisted__MatchData_3080;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3081 = 0;
    (void)hoisted__Bool_3081;
    Type_delete(&self->til_type, hoisted__Bool_3081);
    Bool hoisted__Bool_3082 = 0;
    (void)hoisted__Bool_3082;
    Str_delete(&self->result_temp, hoisted__Bool_3082);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3083 = 0;
    (void)hoisted__U32_3083;
    U64 hoisted__U64_3084 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3083); });
    (void)hoisted__U64_3084;
    return hoisted__U64_3084;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3085 = 40;
    (void)hoisted__U32_3085;
    return hoisted__U32_3085;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3090 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3090->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3090;
    return hoisted__CaptureBlockData_3090;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3091 = 0;
    (void)hoisted__Bool_3091;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3091);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3092 = 0;
    (void)hoisted__U32_3092;
    U64 hoisted__U64_3093 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3092); });
    (void)hoisted__U64_3093;
    return hoisted__U64_3093;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3094 = 16;
    (void)hoisted__U32_3094;
    return hoisted__U32_3094;
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
    Bool hoisted__Bool_3273 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3273;
    if (hoisted__Bool_3273) {
        Literal *hoisted__Literal_3245 = get_payload(self);
        (void)hoisted__Literal_3245;
        (void)hoisted__Literal_3245;
        Bool hoisted__Bool_3246 = 0;
        (void)hoisted__Bool_3246;
        Literal_delete(hoisted__Literal_3245, hoisted__Bool_3246);
    }
    Bool hoisted__Bool_3274 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3274;
    if (hoisted__Bool_3274) {
        IdentData *hoisted__IdentData_3247 = get_payload(self);
        (void)hoisted__IdentData_3247;
        (void)hoisted__IdentData_3247;
        Bool hoisted__Bool_3248 = 0;
        (void)hoisted__Bool_3248;
        IdentData_delete(hoisted__IdentData_3247, hoisted__Bool_3248);
    }
    Bool hoisted__Bool_3275 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3275;
    if (hoisted__Bool_3275) {
        Declaration *hoisted__Declaration_3249 = get_payload(self);
        (void)hoisted__Declaration_3249;
        (void)hoisted__Declaration_3249;
        Bool hoisted__Bool_3250 = 0;
        (void)hoisted__Bool_3250;
        Declaration_delete(hoisted__Declaration_3249, hoisted__Bool_3250);
    }
    Bool hoisted__Bool_3276 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3276;
    if (hoisted__Bool_3276) {
        AssignData *hoisted__AssignData_3251 = get_payload(self);
        (void)hoisted__AssignData_3251;
        (void)hoisted__AssignData_3251;
        Bool hoisted__Bool_3252 = 0;
        (void)hoisted__Bool_3252;
        AssignData_delete(hoisted__AssignData_3251, hoisted__Bool_3252);
    }
    Bool hoisted__Bool_3277 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3277;
    if (hoisted__Bool_3277) {
        FCallData *hoisted__FCallData_3253 = get_payload(self);
        (void)hoisted__FCallData_3253;
        (void)hoisted__FCallData_3253;
        Bool hoisted__Bool_3254 = 0;
        (void)hoisted__Bool_3254;
        FCallData_delete(hoisted__FCallData_3253, hoisted__Bool_3254);
    }
    Bool hoisted__Bool_3278 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3278;
    if (hoisted__Bool_3278) {
        FunctionDef *hoisted__FunctionDef_3255 = get_payload(self);
        (void)hoisted__FunctionDef_3255;
        (void)hoisted__FunctionDef_3255;
        Bool hoisted__Bool_3256 = 0;
        (void)hoisted__Bool_3256;
        FunctionDef_delete(hoisted__FunctionDef_3255, hoisted__Bool_3256);
    }
    Bool hoisted__Bool_3279 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3279;
    if (hoisted__Bool_3279) {
        StructDef *hoisted__StructDef_3257 = get_payload(self);
        (void)hoisted__StructDef_3257;
        (void)hoisted__StructDef_3257;
        Bool hoisted__Bool_3258 = 0;
        (void)hoisted__Bool_3258;
        StructDef_delete(hoisted__StructDef_3257, hoisted__Bool_3258);
    }
    Bool hoisted__Bool_3280 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3280;
    if (hoisted__Bool_3280) {
        EnumDef *hoisted__EnumDef_3259 = get_payload(self);
        (void)hoisted__EnumDef_3259;
        (void)hoisted__EnumDef_3259;
        Bool hoisted__Bool_3260 = 0;
        (void)hoisted__Bool_3260;
        EnumDef_delete(hoisted__EnumDef_3259, hoisted__Bool_3260);
    }
    Bool hoisted__Bool_3281 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3281;
    if (hoisted__Bool_3281) {
        FieldAccessData *hoisted__FieldAccessData_3261 = get_payload(self);
        (void)hoisted__FieldAccessData_3261;
        (void)hoisted__FieldAccessData_3261;
        Bool hoisted__Bool_3262 = 0;
        (void)hoisted__Bool_3262;
        FieldAccessData_delete(hoisted__FieldAccessData_3261, hoisted__Bool_3262);
    }
    Bool hoisted__Bool_3282 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3282;
    if (hoisted__Bool_3282) {
        FieldAssignData *hoisted__FieldAssignData_3263 = get_payload(self);
        (void)hoisted__FieldAssignData_3263;
        (void)hoisted__FieldAssignData_3263;
        Bool hoisted__Bool_3264 = 0;
        (void)hoisted__Bool_3264;
        FieldAssignData_delete(hoisted__FieldAssignData_3263, hoisted__Bool_3264);
    }
    Bool hoisted__Bool_3283 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3283;
    if (hoisted__Bool_3283) {
        ForInData *hoisted__ForInData_3265 = get_payload(self);
        (void)hoisted__ForInData_3265;
        (void)hoisted__ForInData_3265;
        Bool hoisted__Bool_3266 = 0;
        (void)hoisted__Bool_3266;
        ForInData_delete(hoisted__ForInData_3265, hoisted__Bool_3266);
    }
    Bool hoisted__Bool_3284 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3284;
    if (hoisted__Bool_3284) {
        Str *hoisted__Str_3267 = get_payload(self);
        (void)hoisted__Str_3267;
        (void)hoisted__Str_3267;
        Bool hoisted__Bool_3268 = 0;
        (void)hoisted__Bool_3268;
        Str_delete(hoisted__Str_3267, hoisted__Bool_3268);
    }
    Bool hoisted__Bool_3285 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3285;
    if (hoisted__Bool_3285) {
        MatchData *hoisted__MatchData_3269 = get_payload(self);
        (void)hoisted__MatchData_3269;
        (void)hoisted__MatchData_3269;
        Bool hoisted__Bool_3270 = 0;
        (void)hoisted__Bool_3270;
        MatchData_delete(hoisted__MatchData_3269, hoisted__Bool_3270);
    }
    Bool hoisted__Bool_3286 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3286;
    if (hoisted__Bool_3286) {
        CaptureBlockData *hoisted__CaptureBlockData_3271 = get_payload(self);
        (void)hoisted__CaptureBlockData_3271;
        (void)hoisted__CaptureBlockData_3271;
        Bool hoisted__Bool_3272 = 0;
        (void)hoisted__Bool_3272;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3271, hoisted__Bool_3272);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3510 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3510;
    if (hoisted__Bool_3510) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3511 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3511;
    if (hoisted__Bool_3511) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3482 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3482;
        NodeType *hoisted__NodeType_3483 = NodeType_Literal(hoisted__Literal_3482);
        (void)hoisted__NodeType_3483;
        { NodeType * _ret_val = hoisted__NodeType_3483;
                return _ret_val; }
    }
    Bool hoisted__Bool_3512 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3512;
    if (hoisted__Bool_3512) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3484 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3484;
        NodeType *hoisted__NodeType_3485 = NodeType_Ident(hoisted__IdentData_3484);
        (void)hoisted__NodeType_3485;
        { NodeType * _ret_val = hoisted__NodeType_3485;
                return _ret_val; }
    }
    Bool hoisted__Bool_3513 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3513;
    if (hoisted__Bool_3513) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3486 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3486;
        NodeType *hoisted__NodeType_3487 = NodeType_Decl(hoisted__Declaration_3486);
        (void)hoisted__NodeType_3487;
        { NodeType * _ret_val = hoisted__NodeType_3487;
                return _ret_val; }
    }
    Bool hoisted__Bool_3514 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3514;
    if (hoisted__Bool_3514) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3488 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3488;
        NodeType *hoisted__NodeType_3489 = NodeType_Assign(hoisted__AssignData_3488);
        (void)hoisted__NodeType_3489;
        { NodeType * _ret_val = hoisted__NodeType_3489;
                return _ret_val; }
    }
    Bool hoisted__Bool_3515 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3515;
    if (hoisted__Bool_3515) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3490 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3490;
        NodeType *hoisted__NodeType_3491 = NodeType_FCall(hoisted__FCallData_3490);
        (void)hoisted__NodeType_3491;
        { NodeType * _ret_val = hoisted__NodeType_3491;
                return _ret_val; }
    }
    Bool hoisted__Bool_3516 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3516;
    if (hoisted__Bool_3516) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3492 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3492;
        NodeType *hoisted__NodeType_3493 = NodeType_FuncDef(hoisted__FunctionDef_3492);
        (void)hoisted__NodeType_3493;
        { NodeType * _ret_val = hoisted__NodeType_3493;
                return _ret_val; }
    }
    Bool hoisted__Bool_3517 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3517;
    if (hoisted__Bool_3517) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3494 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3494;
        NodeType *hoisted__NodeType_3495 = NodeType_StructDef(hoisted__StructDef_3494);
        (void)hoisted__NodeType_3495;
        { NodeType * _ret_val = hoisted__NodeType_3495;
                return _ret_val; }
    }
    Bool hoisted__Bool_3518 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3518;
    if (hoisted__Bool_3518) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3496 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3496;
        NodeType *hoisted__NodeType_3497 = NodeType_EnumDef(hoisted__EnumDef_3496);
        (void)hoisted__NodeType_3497;
        { NodeType * _ret_val = hoisted__NodeType_3497;
                return _ret_val; }
    }
    Bool hoisted__Bool_3519 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3519;
    if (hoisted__Bool_3519) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3498 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3498;
        NodeType *hoisted__NodeType_3499 = NodeType_FieldAccess(hoisted__FieldAccessData_3498);
        (void)hoisted__NodeType_3499;
        { NodeType * _ret_val = hoisted__NodeType_3499;
                return _ret_val; }
    }
    Bool hoisted__Bool_3520 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3520;
    if (hoisted__Bool_3520) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3500 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3500;
        NodeType *hoisted__NodeType_3501 = NodeType_FieldAssign(hoisted__FieldAssignData_3500);
        (void)hoisted__NodeType_3501;
        { NodeType * _ret_val = hoisted__NodeType_3501;
                return _ret_val; }
    }
    Bool hoisted__Bool_3521 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3521;
    if (hoisted__Bool_3521) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3522 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3522;
    if (hoisted__Bool_3522) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3523 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3523;
    if (hoisted__Bool_3523) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3524 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3524;
    if (hoisted__Bool_3524) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3502 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3502;
        NodeType *hoisted__NodeType_3503 = NodeType_ForIn(hoisted__ForInData_3502);
        (void)hoisted__NodeType_3503;
        { NodeType * _ret_val = hoisted__NodeType_3503;
                return _ret_val; }
    }
    Bool hoisted__Bool_3525 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3525;
    if (hoisted__Bool_3525) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3504 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3504;
        NodeType *hoisted__NodeType_3505 = NodeType_NamedArg(hoisted__Str_3504);
        (void)hoisted__NodeType_3505;
        { NodeType * _ret_val = hoisted__NodeType_3505;
                return _ret_val; }
    }
    Bool hoisted__Bool_3526 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3526;
    if (hoisted__Bool_3526) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3527 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3527;
    if (hoisted__Bool_3527) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3528 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3528;
    if (hoisted__Bool_3528) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3529 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3529;
    if (hoisted__Bool_3529) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3506 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3506;
        NodeType *hoisted__NodeType_3507 = NodeType_Match(hoisted__MatchData_3506);
        (void)hoisted__NodeType_3507;
        { NodeType * _ret_val = hoisted__NodeType_3507;
                return _ret_val; }
    }
    Bool hoisted__Bool_3530 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3530;
    if (hoisted__Bool_3530) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3531 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3531;
    if (hoisted__Bool_3531) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3532 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3532;
    if (hoisted__Bool_3532) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3533 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3533;
    if (hoisted__Bool_3533) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3534 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3534;
    if (hoisted__Bool_3534) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3535 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3535;
    if (hoisted__Bool_3535) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3508 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3508;
        NodeType *hoisted__NodeType_3509 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3508);
        (void)hoisted__NodeType_3509;
        { NodeType * _ret_val = hoisted__NodeType_3509;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3536 = 120;
    (void)hoisted__U32_3536;
    return hoisted__U32_3536;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3537 = is_null(self);
    (void)hoisted__Bool_3537;
    if (hoisted__Bool_3537) {
        return;
    }
    Bool hoisted__Bool_3538 = 0;
    (void)hoisted__Bool_3538;
    NodeType_delete(&self->node_type, hoisted__Bool_3538);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3591 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3591->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3591->children = *_ca; free(_ca); }
    hoisted__Expr_3591->line = line;
    hoisted__Expr_3591->col = col;
    (void)hoisted__Expr_3591;
    return hoisted__Expr_3591;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3600 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3600->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3600->children = *_ca; free(_ca); }
    hoisted__Expr_3600->line = self->line;
    hoisted__Expr_3600->col = self->col;
    (void)hoisted__Expr_3600;
    return hoisted__Expr_3600;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3601 = 0;
    (void)hoisted__U32_3601;
    U64 hoisted__U64_3602 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3601); });
    (void)hoisted__U64_3602;
    return hoisted__U64_3602;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3603 = 144;
    (void)hoisted__U32_3603;
    return hoisted__U32_3603;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4335 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4335->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4335->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4335;
    return hoisted__Map__I64_Str_4335;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4482 = 0;
    (void)hoisted__Bool_4482;
    Vec__I64_delete(&self->keys, hoisted__Bool_4482);
    Bool hoisted__Bool_4483 = 0;
    (void)hoisted__Bool_4483;
    Vec__Str_delete(&self->values, hoisted__Bool_4483);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4484 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4484->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4484->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4484;
    return hoisted__Map__I64_Str_4484;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4485 = 0;
    (void)hoisted__U32_4485;
    U64 hoisted__U64_4486 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4485); });
    (void)hoisted__U64_4486;
    return hoisted__U64_4486;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4487 = 32;
    (void)hoisted__U32_4487;
    return hoisted__U32_4487;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4488 = 1;
    (void)hoisted__U32_4488;
    Type *hoisted__Type_4489 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4489;
    U64 hoisted__U64_4490 = (U64)(hoisted__U32_4488);
    (void)hoisted__U64_4490;
    Type_delete(hoisted__Type_4489, 1);
    void * hoisted__v_4491 = malloc(hoisted__U64_4490);
    (void)hoisted__v_4491;
    U32 hoisted__U32_4492 = 0;
    (void)hoisted__U32_4492;
    I64 hoisted__I64_4493 = 1;
    (void)hoisted__I64_4493;
    Vec__Bool *hoisted__Vec__Bool_4494 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4494->data = hoisted__v_4491;
    hoisted__Vec__Bool_4494->count = hoisted__U32_4492;
    hoisted__Vec__Bool_4494->cap = hoisted__I64_4493;
    (void)hoisted__Vec__Bool_4494;
    return hoisted__Vec__Bool_4494;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4495 = self->count;
        (void)_re_U32_4495;
        U32 _rc_U32_4495 = 0;
        (void)_rc_U32_4495;
        Bool hoisted__Bool_4510 = U32_lte(_rc_U32_4495, _re_U32_4495);
        (void)hoisted__Bool_4510;
        if (hoisted__Bool_4510) {
            while (1) {
                Bool _wcond_Bool_4496 = U32_lt(_rc_U32_4495, _re_U32_4495);
                (void)_wcond_Bool_4496;
                if (_wcond_Bool_4496) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4495);
                U32_inc(&_rc_U32_4495);
                U32 hoisted__U32_4497 = 1;
                (void)hoisted__U32_4497;
                U32 hoisted__U32_4498 = U32_mul(i, hoisted__U32_4497);
                (void)hoisted__U32_4498;
                Type *hoisted__Type_4499 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4499;
                U64 hoisted__U64_4500 = (U64)(hoisted__U32_4498);
                (void)hoisted__U64_4500;
                Type_delete(hoisted__Type_4499, 1);
                Bool *hoisted__Bool_4501 = ptr_add(self->data, hoisted__U64_4500);
                (void)hoisted__Bool_4501;
                (void)hoisted__Bool_4501;
                Bool hoisted__Bool_4502 = 0;
                (void)hoisted__Bool_4502;
                Bool_delete(hoisted__Bool_4501, hoisted__Bool_4502);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4503 = U32_gt(_rc_U32_4495, _re_U32_4495);
                (void)_wcond_Bool_4503;
                if (_wcond_Bool_4503) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4495);
                U32_dec(&_rc_U32_4495);
                U32 hoisted__U32_4504 = 1;
                (void)hoisted__U32_4504;
                U32 hoisted__U32_4505 = U32_mul(i, hoisted__U32_4504);
                (void)hoisted__U32_4505;
                Type *hoisted__Type_4506 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4506;
                U64 hoisted__U64_4507 = (U64)(hoisted__U32_4505);
                (void)hoisted__U64_4507;
                Type_delete(hoisted__Type_4506, 1);
                Bool *hoisted__Bool_4508 = ptr_add(self->data, hoisted__U64_4507);
                (void)hoisted__Bool_4508;
                (void)hoisted__Bool_4508;
                Bool hoisted__Bool_4509 = 0;
                (void)hoisted__Bool_4509;
                Bool_delete(hoisted__Bool_4508, hoisted__Bool_4509);
            }
        }
    }
    U32 hoisted__U32_4511 = 0;
    (void)hoisted__U32_4511;
    self->count = hoisted__U32_4511;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4828 = 1;
    (void)hoisted__U32_4828;
    U32 hoisted__U32_4829 = U32_mul(self->cap, hoisted__U32_4828);
    (void)hoisted__U32_4829;
    Type *hoisted__Type_4830 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4830;
    U64 hoisted__U64_4831 = (U64)(hoisted__U32_4829);
    (void)hoisted__U64_4831;
    Type_delete(hoisted__Type_4830, 1);
    void * new_data = malloc(hoisted__U64_4831);
    {
        U32 _re_U32_4792 = self->count;
        (void)_re_U32_4792;
        U32 _rc_U32_4792 = 0;
        (void)_rc_U32_4792;
        Bool hoisted__Bool_4827 = U32_lte(_rc_U32_4792, _re_U32_4792);
        (void)hoisted__Bool_4827;
        if (hoisted__Bool_4827) {
            while (1) {
                Bool _wcond_Bool_4793 = U32_lt(_rc_U32_4792, _re_U32_4792);
                (void)_wcond_Bool_4793;
                if (_wcond_Bool_4793) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4792);
                U32_inc(&_rc_U32_4792);
                U32 hoisted__U32_4794 = 1;
                (void)hoisted__U32_4794;
                U32 hoisted__U32_4795 = U32_mul(i, hoisted__U32_4794);
                (void)hoisted__U32_4795;
                Type *hoisted__Type_4796 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4796;
                U64 hoisted__U64_4797 = (U64)(hoisted__U32_4795);
                (void)hoisted__U64_4797;
                Type_delete(hoisted__Type_4796, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4797);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4798 = 1;
                (void)hoisted__U32_4798;
                U32 hoisted__U32_4799 = U32_mul(i, hoisted__U32_4798);
                (void)hoisted__U32_4799;
                Type *hoisted__Type_4800 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4800;
                U64 hoisted__U64_4801 = (U64)(hoisted__U32_4799);
                (void)hoisted__U64_4801;
                Type_delete(hoisted__Type_4800, 1);
                U32 hoisted__U32_4802 = 1;
                (void)hoisted__U32_4802;
                Type *hoisted__Type_4803 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4803;
                void *hoisted__v_4804 = ptr_add(new_data, hoisted__U64_4801);
                (void)hoisted__v_4804;
                (void)hoisted__v_4804;
                U64 hoisted__U64_4805 = (U64)(hoisted__U32_4802);
                (void)hoisted__U64_4805;
                Type_delete(hoisted__Type_4803, 1);
                memcpy(hoisted__v_4804, &cloned, hoisted__U64_4805);
                U32 hoisted__U32_4806 = 1;
                (void)hoisted__U32_4806;
                Type *hoisted__Type_4807 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4807;
                I32 hoisted__I32_4808 = 0;
                (void)hoisted__I32_4808;
                U64 hoisted__U64_4809 = (U64)(hoisted__U32_4806);
                (void)hoisted__U64_4809;
                Type_delete(hoisted__Type_4807, 1);
                memset(&cloned, hoisted__I32_4808, hoisted__U64_4809);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4810 = U32_gt(_rc_U32_4792, _re_U32_4792);
                (void)_wcond_Bool_4810;
                if (_wcond_Bool_4810) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4792);
                U32_dec(&_rc_U32_4792);
                U32 hoisted__U32_4811 = 1;
                (void)hoisted__U32_4811;
                U32 hoisted__U32_4812 = U32_mul(i, hoisted__U32_4811);
                (void)hoisted__U32_4812;
                Type *hoisted__Type_4813 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4813;
                U64 hoisted__U64_4814 = (U64)(hoisted__U32_4812);
                (void)hoisted__U64_4814;
                Type_delete(hoisted__Type_4813, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4814);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4815 = 1;
                (void)hoisted__U32_4815;
                U32 hoisted__U32_4816 = U32_mul(i, hoisted__U32_4815);
                (void)hoisted__U32_4816;
                Type *hoisted__Type_4817 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4817;
                U64 hoisted__U64_4818 = (U64)(hoisted__U32_4816);
                (void)hoisted__U64_4818;
                Type_delete(hoisted__Type_4817, 1);
                U32 hoisted__U32_4819 = 1;
                (void)hoisted__U32_4819;
                Type *hoisted__Type_4820 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4820;
                void *hoisted__v_4821 = ptr_add(new_data, hoisted__U64_4818);
                (void)hoisted__v_4821;
                (void)hoisted__v_4821;
                U64 hoisted__U64_4822 = (U64)(hoisted__U32_4819);
                (void)hoisted__U64_4822;
                Type_delete(hoisted__Type_4820, 1);
                memcpy(hoisted__v_4821, &cloned, hoisted__U64_4822);
                U32 hoisted__U32_4823 = 1;
                (void)hoisted__U32_4823;
                Type *hoisted__Type_4824 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4824;
                I32 hoisted__I32_4825 = 0;
                (void)hoisted__I32_4825;
                U64 hoisted__U64_4826 = (U64)(hoisted__U32_4823);
                (void)hoisted__U64_4826;
                Type_delete(hoisted__Type_4824, 1);
                memset(&cloned, hoisted__I32_4825, hoisted__U64_4826);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4832 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4832->data = new_data;
    hoisted__Vec__Bool_4832->count = self->count;
    hoisted__Vec__Bool_4832->cap = self->cap;
    (void)hoisted__Vec__Bool_4832;
    return hoisted__Vec__Bool_4832;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4833 = 16;
    (void)hoisted__U32_4833;
    return hoisted__U32_4833;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5180 = 104;
    (void)hoisted__U32_5180;
    Type *hoisted__Type_5181 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5181;
    U64 hoisted__U64_5182 = (U64)(hoisted__U32_5180);
    (void)hoisted__U64_5182;
    Type_delete(hoisted__Type_5181, 1);
    void * hoisted__v_5183 = malloc(hoisted__U64_5182);
    (void)hoisted__v_5183;
    U32 hoisted__U32_5184 = 0;
    (void)hoisted__U32_5184;
    I64 hoisted__I64_5185 = 1;
    (void)hoisted__I64_5185;
    Vec__Declaration *hoisted__Vec__Declaration_5186 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5186->data = hoisted__v_5183;
    hoisted__Vec__Declaration_5186->count = hoisted__U32_5184;
    hoisted__Vec__Declaration_5186->cap = hoisted__I64_5185;
    (void)hoisted__Vec__Declaration_5186;
    return hoisted__Vec__Declaration_5186;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5187 = self->count;
        (void)_re_U32_5187;
        U32 _rc_U32_5187 = 0;
        (void)_rc_U32_5187;
        Bool hoisted__Bool_5202 = U32_lte(_rc_U32_5187, _re_U32_5187);
        (void)hoisted__Bool_5202;
        if (hoisted__Bool_5202) {
            while (1) {
                Bool _wcond_Bool_5188 = U32_lt(_rc_U32_5187, _re_U32_5187);
                (void)_wcond_Bool_5188;
                if (_wcond_Bool_5188) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5187);
                U32_inc(&_rc_U32_5187);
                U32 hoisted__U32_5189 = 104;
                (void)hoisted__U32_5189;
                U32 hoisted__U32_5190 = U32_mul(i, hoisted__U32_5189);
                (void)hoisted__U32_5190;
                Type *hoisted__Type_5191 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5191;
                U64 hoisted__U64_5192 = (U64)(hoisted__U32_5190);
                (void)hoisted__U64_5192;
                Type_delete(hoisted__Type_5191, 1);
                Declaration *hoisted__Declaration_5193 = ptr_add(self->data, hoisted__U64_5192);
                (void)hoisted__Declaration_5193;
                (void)hoisted__Declaration_5193;
                Bool hoisted__Bool_5194 = 0;
                (void)hoisted__Bool_5194;
                Declaration_delete(hoisted__Declaration_5193, hoisted__Bool_5194);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5195 = U32_gt(_rc_U32_5187, _re_U32_5187);
                (void)_wcond_Bool_5195;
                if (_wcond_Bool_5195) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5187);
                U32_dec(&_rc_U32_5187);
                U32 hoisted__U32_5196 = 104;
                (void)hoisted__U32_5196;
                U32 hoisted__U32_5197 = U32_mul(i, hoisted__U32_5196);
                (void)hoisted__U32_5197;
                Type *hoisted__Type_5198 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5198;
                U64 hoisted__U64_5199 = (U64)(hoisted__U32_5197);
                (void)hoisted__U64_5199;
                Type_delete(hoisted__Type_5198, 1);
                Declaration *hoisted__Declaration_5200 = ptr_add(self->data, hoisted__U64_5199);
                (void)hoisted__Declaration_5200;
                (void)hoisted__Declaration_5200;
                Bool hoisted__Bool_5201 = 0;
                (void)hoisted__Bool_5201;
                Declaration_delete(hoisted__Declaration_5200, hoisted__Bool_5201);
            }
        }
    }
    U32 hoisted__U32_5203 = 0;
    (void)hoisted__U32_5203;
    self->count = hoisted__U32_5203;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5520 = 104;
    (void)hoisted__U32_5520;
    U32 hoisted__U32_5521 = U32_mul(self->cap, hoisted__U32_5520);
    (void)hoisted__U32_5521;
    Type *hoisted__Type_5522 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5522;
    U64 hoisted__U64_5523 = (U64)(hoisted__U32_5521);
    (void)hoisted__U64_5523;
    Type_delete(hoisted__Type_5522, 1);
    void * new_data = malloc(hoisted__U64_5523);
    {
        U32 _re_U32_5484 = self->count;
        (void)_re_U32_5484;
        U32 _rc_U32_5484 = 0;
        (void)_rc_U32_5484;
        Bool hoisted__Bool_5519 = U32_lte(_rc_U32_5484, _re_U32_5484);
        (void)hoisted__Bool_5519;
        if (hoisted__Bool_5519) {
            while (1) {
                Bool _wcond_Bool_5485 = U32_lt(_rc_U32_5484, _re_U32_5484);
                (void)_wcond_Bool_5485;
                if (_wcond_Bool_5485) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5484);
                U32_inc(&_rc_U32_5484);
                U32 hoisted__U32_5486 = 104;
                (void)hoisted__U32_5486;
                U32 hoisted__U32_5487 = U32_mul(i, hoisted__U32_5486);
                (void)hoisted__U32_5487;
                Type *hoisted__Type_5488 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5488;
                U64 hoisted__U64_5489 = (U64)(hoisted__U32_5487);
                (void)hoisted__U64_5489;
                Type_delete(hoisted__Type_5488, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5489);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5490 = 104;
                (void)hoisted__U32_5490;
                U32 hoisted__U32_5491 = U32_mul(i, hoisted__U32_5490);
                (void)hoisted__U32_5491;
                Type *hoisted__Type_5492 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5492;
                U64 hoisted__U64_5493 = (U64)(hoisted__U32_5491);
                (void)hoisted__U64_5493;
                Type_delete(hoisted__Type_5492, 1);
                U32 hoisted__U32_5494 = 104;
                (void)hoisted__U32_5494;
                Type *hoisted__Type_5495 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5495;
                void *hoisted__v_5496 = ptr_add(new_data, hoisted__U64_5493);
                (void)hoisted__v_5496;
                (void)hoisted__v_5496;
                U64 hoisted__U64_5497 = (U64)(hoisted__U32_5494);
                (void)hoisted__U64_5497;
                Type_delete(hoisted__Type_5495, 1);
                memcpy(hoisted__v_5496, cloned, hoisted__U64_5497);
                U32 hoisted__U32_5498 = 104;
                (void)hoisted__U32_5498;
                Type *hoisted__Type_5499 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5499;
                I32 hoisted__I32_5500 = 0;
                (void)hoisted__I32_5500;
                U64 hoisted__U64_5501 = (U64)(hoisted__U32_5498);
                (void)hoisted__U64_5501;
                Type_delete(hoisted__Type_5499, 1);
                memset(cloned, hoisted__I32_5500, hoisted__U64_5501);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5502 = U32_gt(_rc_U32_5484, _re_U32_5484);
                (void)_wcond_Bool_5502;
                if (_wcond_Bool_5502) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5484);
                U32_dec(&_rc_U32_5484);
                U32 hoisted__U32_5503 = 104;
                (void)hoisted__U32_5503;
                U32 hoisted__U32_5504 = U32_mul(i, hoisted__U32_5503);
                (void)hoisted__U32_5504;
                Type *hoisted__Type_5505 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5505;
                U64 hoisted__U64_5506 = (U64)(hoisted__U32_5504);
                (void)hoisted__U64_5506;
                Type_delete(hoisted__Type_5505, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5506);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5507 = 104;
                (void)hoisted__U32_5507;
                U32 hoisted__U32_5508 = U32_mul(i, hoisted__U32_5507);
                (void)hoisted__U32_5508;
                Type *hoisted__Type_5509 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5509;
                U64 hoisted__U64_5510 = (U64)(hoisted__U32_5508);
                (void)hoisted__U64_5510;
                Type_delete(hoisted__Type_5509, 1);
                U32 hoisted__U32_5511 = 104;
                (void)hoisted__U32_5511;
                Type *hoisted__Type_5512 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5512;
                void *hoisted__v_5513 = ptr_add(new_data, hoisted__U64_5510);
                (void)hoisted__v_5513;
                (void)hoisted__v_5513;
                U64 hoisted__U64_5514 = (U64)(hoisted__U32_5511);
                (void)hoisted__U64_5514;
                Type_delete(hoisted__Type_5512, 1);
                memcpy(hoisted__v_5513, cloned, hoisted__U64_5514);
                U32 hoisted__U32_5515 = 104;
                (void)hoisted__U32_5515;
                Type *hoisted__Type_5516 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5516;
                I32 hoisted__I32_5517 = 0;
                (void)hoisted__I32_5517;
                U64 hoisted__U64_5518 = (U64)(hoisted__U32_5515);
                (void)hoisted__U64_5518;
                Type_delete(hoisted__Type_5516, 1);
                memset(cloned, hoisted__I32_5517, hoisted__U64_5518);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5524 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5524->data = new_data;
    hoisted__Vec__Declaration_5524->count = self->count;
    hoisted__Vec__Declaration_5524->cap = self->cap;
    (void)hoisted__Vec__Declaration_5524;
    return hoisted__Vec__Declaration_5524;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5525 = 16;
    (void)hoisted__U32_5525;
    return hoisted__U32_5525;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5526 = 144;
    (void)hoisted__U32_5526;
    Type *hoisted__Type_5527 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5527;
    U64 hoisted__U64_5528 = (U64)(hoisted__U32_5526);
    (void)hoisted__U64_5528;
    Type_delete(hoisted__Type_5527, 1);
    void * hoisted__v_5529 = malloc(hoisted__U64_5528);
    (void)hoisted__v_5529;
    U32 hoisted__U32_5530 = 0;
    (void)hoisted__U32_5530;
    I64 hoisted__I64_5531 = 1;
    (void)hoisted__I64_5531;
    Vec__Expr *hoisted__Vec__Expr_5532 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5532->data = hoisted__v_5529;
    hoisted__Vec__Expr_5532->count = hoisted__U32_5530;
    hoisted__Vec__Expr_5532->cap = hoisted__I64_5531;
    (void)hoisted__Vec__Expr_5532;
    return hoisted__Vec__Expr_5532;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5533 = self->count;
        (void)_re_U32_5533;
        U32 _rc_U32_5533 = 0;
        (void)_rc_U32_5533;
        Bool hoisted__Bool_5548 = U32_lte(_rc_U32_5533, _re_U32_5533);
        (void)hoisted__Bool_5548;
        if (hoisted__Bool_5548) {
            while (1) {
                Bool _wcond_Bool_5534 = U32_lt(_rc_U32_5533, _re_U32_5533);
                (void)_wcond_Bool_5534;
                if (_wcond_Bool_5534) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5533);
                U32_inc(&_rc_U32_5533);
                U32 hoisted__U32_5535 = 144;
                (void)hoisted__U32_5535;
                U32 hoisted__U32_5536 = U32_mul(i, hoisted__U32_5535);
                (void)hoisted__U32_5536;
                Type *hoisted__Type_5537 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5537;
                U64 hoisted__U64_5538 = (U64)(hoisted__U32_5536);
                (void)hoisted__U64_5538;
                Type_delete(hoisted__Type_5537, 1);
                Expr *hoisted__Expr_5539 = ptr_add(self->data, hoisted__U64_5538);
                (void)hoisted__Expr_5539;
                (void)hoisted__Expr_5539;
                Bool hoisted__Bool_5540 = 0;
                (void)hoisted__Bool_5540;
                Expr_delete(hoisted__Expr_5539, hoisted__Bool_5540);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5541 = U32_gt(_rc_U32_5533, _re_U32_5533);
                (void)_wcond_Bool_5541;
                if (_wcond_Bool_5541) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5533);
                U32_dec(&_rc_U32_5533);
                U32 hoisted__U32_5542 = 144;
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
        }
    }
    U32 hoisted__U32_5549 = 0;
    (void)hoisted__U32_5549;
    self->count = hoisted__U32_5549;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5866 = 144;
    (void)hoisted__U32_5866;
    U32 hoisted__U32_5867 = U32_mul(self->cap, hoisted__U32_5866);
    (void)hoisted__U32_5867;
    Type *hoisted__Type_5868 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5868;
    U64 hoisted__U64_5869 = (U64)(hoisted__U32_5867);
    (void)hoisted__U64_5869;
    Type_delete(hoisted__Type_5868, 1);
    void * new_data = malloc(hoisted__U64_5869);
    {
        U32 _re_U32_5830 = self->count;
        (void)_re_U32_5830;
        U32 _rc_U32_5830 = 0;
        (void)_rc_U32_5830;
        Bool hoisted__Bool_5865 = U32_lte(_rc_U32_5830, _re_U32_5830);
        (void)hoisted__Bool_5865;
        if (hoisted__Bool_5865) {
            while (1) {
                Bool _wcond_Bool_5831 = U32_lt(_rc_U32_5830, _re_U32_5830);
                (void)_wcond_Bool_5831;
                if (_wcond_Bool_5831) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5830);
                U32_inc(&_rc_U32_5830);
                U32 hoisted__U32_5832 = 144;
                (void)hoisted__U32_5832;
                U32 hoisted__U32_5833 = U32_mul(i, hoisted__U32_5832);
                (void)hoisted__U32_5833;
                Type *hoisted__Type_5834 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5834;
                U64 hoisted__U64_5835 = (U64)(hoisted__U32_5833);
                (void)hoisted__U64_5835;
                Type_delete(hoisted__Type_5834, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5835);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5836 = 144;
                (void)hoisted__U32_5836;
                U32 hoisted__U32_5837 = U32_mul(i, hoisted__U32_5836);
                (void)hoisted__U32_5837;
                Type *hoisted__Type_5838 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5838;
                U64 hoisted__U64_5839 = (U64)(hoisted__U32_5837);
                (void)hoisted__U64_5839;
                Type_delete(hoisted__Type_5838, 1);
                U32 hoisted__U32_5840 = 144;
                (void)hoisted__U32_5840;
                Type *hoisted__Type_5841 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5841;
                void *hoisted__v_5842 = ptr_add(new_data, hoisted__U64_5839);
                (void)hoisted__v_5842;
                (void)hoisted__v_5842;
                U64 hoisted__U64_5843 = (U64)(hoisted__U32_5840);
                (void)hoisted__U64_5843;
                Type_delete(hoisted__Type_5841, 1);
                memcpy(hoisted__v_5842, cloned, hoisted__U64_5843);
                U32 hoisted__U32_5844 = 144;
                (void)hoisted__U32_5844;
                Type *hoisted__Type_5845 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5845;
                I32 hoisted__I32_5846 = 0;
                (void)hoisted__I32_5846;
                U64 hoisted__U64_5847 = (U64)(hoisted__U32_5844);
                (void)hoisted__U64_5847;
                Type_delete(hoisted__Type_5845, 1);
                memset(cloned, hoisted__I32_5846, hoisted__U64_5847);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5848 = U32_gt(_rc_U32_5830, _re_U32_5830);
                (void)_wcond_Bool_5848;
                if (_wcond_Bool_5848) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5830);
                U32_dec(&_rc_U32_5830);
                U32 hoisted__U32_5849 = 144;
                (void)hoisted__U32_5849;
                U32 hoisted__U32_5850 = U32_mul(i, hoisted__U32_5849);
                (void)hoisted__U32_5850;
                Type *hoisted__Type_5851 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5851;
                U64 hoisted__U64_5852 = (U64)(hoisted__U32_5850);
                (void)hoisted__U64_5852;
                Type_delete(hoisted__Type_5851, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5852);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5853 = 144;
                (void)hoisted__U32_5853;
                U32 hoisted__U32_5854 = U32_mul(i, hoisted__U32_5853);
                (void)hoisted__U32_5854;
                Type *hoisted__Type_5855 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5855;
                U64 hoisted__U64_5856 = (U64)(hoisted__U32_5854);
                (void)hoisted__U64_5856;
                Type_delete(hoisted__Type_5855, 1);
                U32 hoisted__U32_5857 = 144;
                (void)hoisted__U32_5857;
                Type *hoisted__Type_5858 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5858;
                void *hoisted__v_5859 = ptr_add(new_data, hoisted__U64_5856);
                (void)hoisted__v_5859;
                (void)hoisted__v_5859;
                U64 hoisted__U64_5860 = (U64)(hoisted__U32_5857);
                (void)hoisted__U64_5860;
                Type_delete(hoisted__Type_5858, 1);
                memcpy(hoisted__v_5859, cloned, hoisted__U64_5860);
                U32 hoisted__U32_5861 = 144;
                (void)hoisted__U32_5861;
                Type *hoisted__Type_5862 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5862;
                I32 hoisted__I32_5863 = 0;
                (void)hoisted__I32_5863;
                U64 hoisted__U64_5864 = (U64)(hoisted__U32_5861);
                (void)hoisted__U64_5864;
                Type_delete(hoisted__Type_5862, 1);
                memset(cloned, hoisted__I32_5863, hoisted__U64_5864);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5870 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5870->data = new_data;
    hoisted__Vec__Expr_5870->count = self->count;
    hoisted__Vec__Expr_5870->cap = self->cap;
    (void)hoisted__Vec__Expr_5870;
    return hoisted__Vec__Expr_5870;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5871 = 16;
    (void)hoisted__U32_5871;
    return hoisted__U32_5871;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5872 = 8;
    (void)hoisted__U32_5872;
    Type *hoisted__Type_5873 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5873;
    U64 hoisted__U64_5874 = (U64)(hoisted__U32_5872);
    (void)hoisted__U64_5874;
    Type_delete(hoisted__Type_5873, 1);
    void * hoisted__v_5875 = malloc(hoisted__U64_5874);
    (void)hoisted__v_5875;
    U32 hoisted__U32_5876 = 0;
    (void)hoisted__U32_5876;
    I64 hoisted__I64_5877 = 1;
    (void)hoisted__I64_5877;
    Vec__I64 *hoisted__Vec__I64_5878 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5878->data = hoisted__v_5875;
    hoisted__Vec__I64_5878->count = hoisted__U32_5876;
    hoisted__Vec__I64_5878->cap = hoisted__I64_5877;
    (void)hoisted__Vec__I64_5878;
    return hoisted__Vec__I64_5878;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5879 = self->count;
        (void)_re_U32_5879;
        U32 _rc_U32_5879 = 0;
        (void)_rc_U32_5879;
        Bool hoisted__Bool_5894 = U32_lte(_rc_U32_5879, _re_U32_5879);
        (void)hoisted__Bool_5894;
        if (hoisted__Bool_5894) {
            while (1) {
                Bool _wcond_Bool_5880 = U32_lt(_rc_U32_5879, _re_U32_5879);
                (void)_wcond_Bool_5880;
                if (_wcond_Bool_5880) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5879);
                U32_inc(&_rc_U32_5879);
                U32 hoisted__U32_5881 = 8;
                (void)hoisted__U32_5881;
                U32 hoisted__U32_5882 = U32_mul(i, hoisted__U32_5881);
                (void)hoisted__U32_5882;
                Type *hoisted__Type_5883 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5883;
                U64 hoisted__U64_5884 = (U64)(hoisted__U32_5882);
                (void)hoisted__U64_5884;
                Type_delete(hoisted__Type_5883, 1);
                I64 *hoisted__I64_5885 = ptr_add(self->data, hoisted__U64_5884);
                (void)hoisted__I64_5885;
                (void)hoisted__I64_5885;
                Bool hoisted__Bool_5886 = 0;
                (void)hoisted__Bool_5886;
                I64_delete(hoisted__I64_5885, hoisted__Bool_5886);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5887 = U32_gt(_rc_U32_5879, _re_U32_5879);
                (void)_wcond_Bool_5887;
                if (_wcond_Bool_5887) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5879);
                U32_dec(&_rc_U32_5879);
                U32 hoisted__U32_5888 = 8;
                (void)hoisted__U32_5888;
                U32 hoisted__U32_5889 = U32_mul(i, hoisted__U32_5888);
                (void)hoisted__U32_5889;
                Type *hoisted__Type_5890 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5890;
                U64 hoisted__U64_5891 = (U64)(hoisted__U32_5889);
                (void)hoisted__U64_5891;
                Type_delete(hoisted__Type_5890, 1);
                I64 *hoisted__I64_5892 = ptr_add(self->data, hoisted__U64_5891);
                (void)hoisted__I64_5892;
                (void)hoisted__I64_5892;
                Bool hoisted__Bool_5893 = 0;
                (void)hoisted__Bool_5893;
                I64_delete(hoisted__I64_5892, hoisted__Bool_5893);
            }
        }
    }
    U32 hoisted__U32_5895 = 0;
    (void)hoisted__U32_5895;
    self->count = hoisted__U32_5895;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_6212 = 8;
    (void)hoisted__U32_6212;
    U32 hoisted__U32_6213 = U32_mul(self->cap, hoisted__U32_6212);
    (void)hoisted__U32_6213;
    Type *hoisted__Type_6214 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_6214;
    U64 hoisted__U64_6215 = (U64)(hoisted__U32_6213);
    (void)hoisted__U64_6215;
    Type_delete(hoisted__Type_6214, 1);
    void * new_data = malloc(hoisted__U64_6215);
    {
        U32 _re_U32_6176 = self->count;
        (void)_re_U32_6176;
        U32 _rc_U32_6176 = 0;
        (void)_rc_U32_6176;
        Bool hoisted__Bool_6211 = U32_lte(_rc_U32_6176, _re_U32_6176);
        (void)hoisted__Bool_6211;
        if (hoisted__Bool_6211) {
            while (1) {
                Bool _wcond_Bool_6177 = U32_lt(_rc_U32_6176, _re_U32_6176);
                (void)_wcond_Bool_6177;
                if (_wcond_Bool_6177) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6176);
                U32_inc(&_rc_U32_6176);
                U32 hoisted__U32_6178 = 8;
                (void)hoisted__U32_6178;
                U32 hoisted__U32_6179 = U32_mul(i, hoisted__U32_6178);
                (void)hoisted__U32_6179;
                Type *hoisted__Type_6180 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6180;
                U64 hoisted__U64_6181 = (U64)(hoisted__U32_6179);
                (void)hoisted__U64_6181;
                Type_delete(hoisted__Type_6180, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6181);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6182 = 8;
                (void)hoisted__U32_6182;
                U32 hoisted__U32_6183 = U32_mul(i, hoisted__U32_6182);
                (void)hoisted__U32_6183;
                Type *hoisted__Type_6184 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6184;
                U64 hoisted__U64_6185 = (U64)(hoisted__U32_6183);
                (void)hoisted__U64_6185;
                Type_delete(hoisted__Type_6184, 1);
                U32 hoisted__U32_6186 = 8;
                (void)hoisted__U32_6186;
                Type *hoisted__Type_6187 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6187;
                void *hoisted__v_6188 = ptr_add(new_data, hoisted__U64_6185);
                (void)hoisted__v_6188;
                (void)hoisted__v_6188;
                U64 hoisted__U64_6189 = (U64)(hoisted__U32_6186);
                (void)hoisted__U64_6189;
                Type_delete(hoisted__Type_6187, 1);
                memcpy(hoisted__v_6188, &cloned, hoisted__U64_6189);
                U32 hoisted__U32_6190 = 8;
                (void)hoisted__U32_6190;
                Type *hoisted__Type_6191 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6191;
                I32 hoisted__I32_6192 = 0;
                (void)hoisted__I32_6192;
                U64 hoisted__U64_6193 = (U64)(hoisted__U32_6190);
                (void)hoisted__U64_6193;
                Type_delete(hoisted__Type_6191, 1);
                memset(&cloned, hoisted__I32_6192, hoisted__U64_6193);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6194 = U32_gt(_rc_U32_6176, _re_U32_6176);
                (void)_wcond_Bool_6194;
                if (_wcond_Bool_6194) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6176);
                U32_dec(&_rc_U32_6176);
                U32 hoisted__U32_6195 = 8;
                (void)hoisted__U32_6195;
                U32 hoisted__U32_6196 = U32_mul(i, hoisted__U32_6195);
                (void)hoisted__U32_6196;
                Type *hoisted__Type_6197 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6197;
                U64 hoisted__U64_6198 = (U64)(hoisted__U32_6196);
                (void)hoisted__U64_6198;
                Type_delete(hoisted__Type_6197, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6198);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6199 = 8;
                (void)hoisted__U32_6199;
                U32 hoisted__U32_6200 = U32_mul(i, hoisted__U32_6199);
                (void)hoisted__U32_6200;
                Type *hoisted__Type_6201 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6201;
                U64 hoisted__U64_6202 = (U64)(hoisted__U32_6200);
                (void)hoisted__U64_6202;
                Type_delete(hoisted__Type_6201, 1);
                U32 hoisted__U32_6203 = 8;
                (void)hoisted__U32_6203;
                Type *hoisted__Type_6204 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6204;
                void *hoisted__v_6205 = ptr_add(new_data, hoisted__U64_6202);
                (void)hoisted__v_6205;
                (void)hoisted__v_6205;
                U64 hoisted__U64_6206 = (U64)(hoisted__U32_6203);
                (void)hoisted__U64_6206;
                Type_delete(hoisted__Type_6204, 1);
                memcpy(hoisted__v_6205, &cloned, hoisted__U64_6206);
                U32 hoisted__U32_6207 = 8;
                (void)hoisted__U32_6207;
                Type *hoisted__Type_6208 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6208;
                I32 hoisted__I32_6209 = 0;
                (void)hoisted__I32_6209;
                U64 hoisted__U64_6210 = (U64)(hoisted__U32_6207);
                (void)hoisted__U64_6210;
                Type_delete(hoisted__Type_6208, 1);
                memset(&cloned, hoisted__I32_6209, hoisted__U64_6210);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6216 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6216->data = new_data;
    hoisted__Vec__I64_6216->count = self->count;
    hoisted__Vec__I64_6216->cap = self->cap;
    (void)hoisted__Vec__I64_6216;
    return hoisted__Vec__I64_6216;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_6217 = 16;
    (void)hoisted__U32_6217;
    return hoisted__U32_6217;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7454 = 3;
    (void)hoisted__U32_7454;
    Array__Str *_va_Array_192 = Array__Str_new(hoisted__U32_7454);
    (void)_va_Array_192;
    I64 _va_Array_192_ek = 0;
    (void)_va_Array_192_ek;
    OutOfBounds *_va_Array_192_eo = malloc(sizeof(OutOfBounds));
    _va_Array_192_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_192_eo;
    U32 hoisted__U32_7455 = 0;
    (void)hoisted__U32_7455;
    Str *hoisted__Str_7456 = Str_clone(loc);
    (void)hoisted__Str_7456;
    static Str hoisted__Str_7457 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7457;
    Array__Str_set(_va_Array_192, hoisted__U32_7455, hoisted__Str_7456, &_va_Array_192_ek, _va_Array_192_eo, &hoisted__Str_7457);
    Str_delete(&hoisted__Str_7457, (Bool){0});
    U32 hoisted__U32_7458 = 1;
    (void)hoisted__U32_7458;
    static Str hoisted__Str_7459 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7459;
    static Str hoisted__Str_7460 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7460;
    Array__Str_set(_va_Array_192, hoisted__U32_7458, &hoisted__Str_7459, &_va_Array_192_ek, _va_Array_192_eo, &hoisted__Str_7460);
    Str_delete(&hoisted__Str_7460, (Bool){0});
    Array__Str *hoisted__Array__Str_7461 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7461;
    U32 hoisted__U32_7462 = 2;
    (void)hoisted__U32_7462;
    Str *hoisted__Str_7463 = format(hoisted__Array__Str_7461);
    (void)hoisted__Str_7463;
    static Str hoisted__Str_7464 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7464;
    Array__Str_set(_va_Array_192, hoisted__U32_7462, hoisted__Str_7463, &_va_Array_192_ek, _va_Array_192_eo, &hoisted__Str_7464);
    OutOfBounds_delete(_va_Array_192_eo, 1);
    Str_delete(&hoisted__Str_7464, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_192);
    I64 hoisted__I64_7465 = 1;
    (void)hoisted__I64_7465;
    exit(hoisted__I64_7465);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7474 = 1;
    (void)hoisted__U32_7474;
    Array__Str *_va_Array_194 = Array__Str_new(hoisted__U32_7474);
    (void)_va_Array_194;
    I64 _va_Array_194_ek = 0;
    (void)_va_Array_194_ek;
    OutOfBounds *_va_Array_194_eo = malloc(sizeof(OutOfBounds));
    _va_Array_194_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_194_eo;
    U32 hoisted__U32_7475 = 0;
    (void)hoisted__U32_7475;
    static Str hoisted__Str_7476 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7476;
    static Str hoisted__Str_7477 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7477;
    Array__Str_set(_va_Array_194, hoisted__U32_7475, &hoisted__Str_7476, &_va_Array_194_ek, _va_Array_194_eo, &hoisted__Str_7477);
    OutOfBounds_delete(_va_Array_194_eo, 1);
    Str_delete(&hoisted__Str_7477, (Bool){0});
    panic(_va_Array_194, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7482 = not(cond);
    (void)hoisted__Bool_7482;
    if (hoisted__Bool_7482) {
        U32 hoisted__U32_7478 = 1;
        (void)hoisted__U32_7478;
        Array__Str *_va_Array_195 = Array__Str_new(hoisted__U32_7478);
        (void)_va_Array_195;
        I64 _va_Array_195_ek = 0;
        (void)_va_Array_195_ek;
        OutOfBounds *_va_Array_195_eo = malloc(sizeof(OutOfBounds));
        _va_Array_195_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_195_eo;
        U32 hoisted__U32_7479 = 0;
        (void)hoisted__U32_7479;
        static Str hoisted__Str_7480 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7480;
        static Str hoisted__Str_7481 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7481;
        Array__Str_set(_va_Array_195, hoisted__U32_7479, &hoisted__Str_7480, &_va_Array_195_ek, _va_Array_195_eo, &hoisted__Str_7481);
        OutOfBounds_delete(_va_Array_195_eo, 1);
        Str_delete(&hoisted__Str_7481, (Bool){0});
        panic(_va_Array_195, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7492 = parts;
        (void)_fc_Array__Str_7492;
        (void)_fc_Array__Str_7492;
        U32 _fi_USize_7492 = 0;
        (void)_fi_USize_7492;
        while (1) {
            U32 hoisted__U32_7494 = Array__Str_len(_fc_Array__Str_7492);
            (void)hoisted__U32_7494;
            Bool _wcond_Bool_7493 = U32_lt(_fi_USize_7492, hoisted__U32_7494);
            (void)_wcond_Bool_7493;
            if (_wcond_Bool_7493) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7492, &_fi_USize_7492);
            U32 hoisted__U32_7495 = 1;
            (void)hoisted__U32_7495;
            U32 hoisted__U32_7496 = U32_add(_fi_USize_7492, hoisted__U32_7495);
            (void)hoisted__U32_7496;
            _fi_USize_7492 = hoisted__U32_7496;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7530 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7530;
    return hoisted__Bool_7530;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7539 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7539;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7539;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7540 = 0;
    (void)hoisted__U32_7540;
    U64 hoisted__U64_7541 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7540); });
    (void)hoisted__U64_7541;
    return hoisted__U64_7541;
}

U32 Range_size(void) {
    U32 hoisted__U32_7572 = 16;
    (void)hoisted__U32_7572;
    return hoisted__U32_7572;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7703 = 3;
    (void)hoisted__I64_7703;
    static Str hoisted__Str_7704 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7704;
    assert_eq__I64(result, hoisted__I64_7703, &hoisted__Str_7704);
    Str_delete(&hoisted__Str_7704, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7711 = 15;
    (void)hoisted__I64_7711;
    static Str hoisted__Str_7712 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7712;
    assert_eq__I64(result, hoisted__I64_7711, &hoisted__Str_7712);
    Str_delete(&hoisted__Str_7712, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7719 = 26;
    (void)hoisted__I64_7719;
    static Str hoisted__Str_7720 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7720;
    assert_eq__I64(result, hoisted__I64_7719, &hoisted__Str_7720);
    Str_delete(&hoisted__Str_7720, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7723 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7723;
    static Str hoisted__Str_7724 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7724;
    assert_eq__Str(&result, &hoisted__Str_7723, &hoisted__Str_7724);
    Str_delete(&hoisted__Str_7723, (Bool){0});
    Str_delete(&hoisted__Str_7724, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7752 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7752;
    static Str hoisted__Str_7753 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7753;
    assert_eq__Str(&r, &hoisted__Str_7752, &hoisted__Str_7753);
    Str_delete(&hoisted__Str_7752, (Bool){0});
    Str_delete(&hoisted__Str_7753, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7757 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7757;
    static Str hoisted__Str_7758 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7758;
    assert_eq__Str(&r2, &hoisted__Str_7757, &hoisted__Str_7758);
    Str_delete(&hoisted__Str_7757, (Bool){0});
    Str_delete(&hoisted__Str_7758, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7781 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7781;
    static Str hoisted__Str_7782 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7782;
    assert_eq__Str(&d, &hoisted__Str_7781, &hoisted__Str_7782);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7781, (Bool){0});
    Str_delete(&hoisted__Str_7782, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7793 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7793;
    static Str hoisted__Str_7794 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7794;
    assert_eq__Str(&d2, &hoisted__Str_7793, &hoisted__Str_7794);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7793, (Bool){0});
    Str_delete(&hoisted__Str_7794, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7806 = 106;
    (void)hoisted__I64_7806;
    static Str hoisted__Str_7807 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7807;
    assert_eq__I64(d3, hoisted__I64_7806, &hoisted__Str_7807);
    Str_delete(&hoisted__Str_7807, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_8406 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8406;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8406);
    Str_delete(&hoisted__Str_8406, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    static Str hoisted__Str_8407 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8407;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8407);
    Str_delete(&hoisted__Str_8407, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8409 = 8;
    (void)hoisted__I64_8409;
    static Str hoisted__Str_8410 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8410;
    assert_eq__I64(result, hoisted__I64_8409, &hoisted__Str_8410);
    Str_delete(&hoisted__Str_8410, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8413 = 1;
    (void)hoisted__Bool_8413;
    static Str hoisted__Str_8414 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8414;
    assert(hoisted__Bool_8413, &hoisted__Str_8414);
    Str_delete(&hoisted__Str_8414, (Bool){0});
    Bool hoisted__Bool_8417 = 1;
    (void)hoisted__Bool_8417;
    static Str hoisted__Str_8418 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8418;
    assert(hoisted__Bool_8417, &hoisted__Str_8418);
    Str_delete(&hoisted__Str_8418, (Bool){0});
}

void test_fold_f32(void) {
    static Str hoisted__Str_8423 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8423;
    static Str hoisted__Str_8424 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8424;
    static Str hoisted__Str_8425 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8425;
    assert_eq__Str(&hoisted__Str_8423, &hoisted__Str_8424, &hoisted__Str_8425);
    Str_delete(&hoisted__Str_8423, (Bool){0});
    Str_delete(&hoisted__Str_8424, (Bool){0});
    Str_delete(&hoisted__Str_8425, (Bool){0});
    static Str hoisted__Str_8428 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8428;
    static Str hoisted__Str_8429 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8429;
    static Str hoisted__Str_8430 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8430;
    assert_eq__Str(&hoisted__Str_8428, &hoisted__Str_8429, &hoisted__Str_8430);
    Str_delete(&hoisted__Str_8428, (Bool){0});
    Str_delete(&hoisted__Str_8429, (Bool){0});
    Str_delete(&hoisted__Str_8430, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8435 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8435;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8435;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8436 = 0;
    (void)hoisted__U32_8436;
    U64 hoisted__U64_8437 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8436); });
    (void)hoisted__U64_8437;
    return hoisted__U64_8437;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8468 = 16;
    (void)hoisted__U32_8468;
    return hoisted__U32_8468;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8469 = 42;
    (void)hoisted__I64_8469;
    static Str hoisted__Str_8470 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8470;
    assert_eq__I64(v.x, hoisted__I64_8469, &hoisted__Str_8470);
    Str_delete(&hoisted__Str_8470, (Bool){0});
    I64 hoisted__I64_8471 = 99;
    (void)hoisted__I64_8471;
    static Str hoisted__Str_8472 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8472;
    assert_eq__I64(v.y, hoisted__I64_8471, &hoisted__Str_8472);
    Str_delete(&hoisted__Str_8472, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8475 = 10;
    (void)hoisted__I64_8475;
    static Str hoisted__Str_8476 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8476;
    assert_eq__I64(p.x, hoisted__I64_8475, &hoisted__Str_8476);
    Str_delete(&hoisted__Str_8476, (Bool){0});
    I64 hoisted__I64_8477 = 20;
    (void)hoisted__I64_8477;
    static Str hoisted__Str_8478 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8478;
    assert_eq__I64(p.y, hoisted__I64_8477, &hoisted__Str_8478);
    Str_delete(&hoisted__Str_8478, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8484 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8484;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8484;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8485 = 0;
    (void)hoisted__U32_8485;
    U64 hoisted__U64_8486 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8485); });
    (void)hoisted__U64_8486;
    return hoisted__U64_8486;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8517 = 32;
    (void)hoisted__U32_8517;
    return hoisted__U32_8517;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8518 = 5;
    (void)hoisted__I64_8518;
    static Str hoisted__Str_8519 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8519;
    assert_eq__I64(r.top_left.x, hoisted__I64_8518, &hoisted__Str_8519);
    Str_delete(&hoisted__Str_8519, (Bool){0});
    I64 hoisted__I64_8520 = 10;
    (void)hoisted__I64_8520;
    static Str hoisted__Str_8521 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8521;
    assert_eq__I64(r.top_left.y, hoisted__I64_8520, &hoisted__Str_8521);
    Str_delete(&hoisted__Str_8521, (Bool){0});
    I64 hoisted__I64_8522 = 100;
    (void)hoisted__I64_8522;
    static Str hoisted__Str_8523 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8523;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8522, &hoisted__Str_8523);
    Str_delete(&hoisted__Str_8523, (Bool){0});
    I64 hoisted__I64_8524 = 200;
    (void)hoisted__I64_8524;
    static Str hoisted__Str_8525 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8525;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8524, &hoisted__Str_8525);
    Str_delete(&hoisted__Str_8525, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8527 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8527;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8527;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8528 = 0;
    (void)hoisted__U32_8528;
    U64 hoisted__U64_8529 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8528); });
    (void)hoisted__U64_8529;
    return hoisted__U64_8529;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8572 = 12;
    (void)hoisted__U32_8572;
    return hoisted__U32_8572;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8576 = F32_to_str(v.x);
    (void)hoisted__Str_8576;
    static Str hoisted__Str_8577 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8577;
    static Str hoisted__Str_8578 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8578;
    assert_eq__Str(hoisted__Str_8576, &hoisted__Str_8577, &hoisted__Str_8578);
    Str_delete(hoisted__Str_8576, 1);
    Str_delete(&hoisted__Str_8577, (Bool){0});
    Str_delete(&hoisted__Str_8578, (Bool){0});
    Str *hoisted__Str_8579 = F32_to_str(v.y);
    (void)hoisted__Str_8579;
    static Str hoisted__Str_8580 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8580;
    static Str hoisted__Str_8581 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8581;
    assert_eq__Str(hoisted__Str_8579, &hoisted__Str_8580, &hoisted__Str_8581);
    Str_delete(hoisted__Str_8579, 1);
    Str_delete(&hoisted__Str_8580, (Bool){0});
    Str_delete(&hoisted__Str_8581, (Bool){0});
    Str *hoisted__Str_8582 = F32_to_str(v.z);
    (void)hoisted__Str_8582;
    static Str hoisted__Str_8583 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8583;
    static Str hoisted__Str_8584 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8584;
    assert_eq__Str(hoisted__Str_8582, &hoisted__Str_8583, &hoisted__Str_8584);
    Str_delete(hoisted__Str_8582, 1);
    Str_delete(&hoisted__Str_8583, (Bool){0});
    Str_delete(&hoisted__Str_8584, (Bool){0});
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
    Bool hoisted__Bool_8589 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8589;
    if (hoisted__Bool_8589) {
        Bool hoisted__Bool_8586 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8586;
        { Bool _ret_val = hoisted__Bool_8586;
                return _ret_val; }
    }
    Bool hoisted__Bool_8590 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8590;
    if (hoisted__Bool_8590) {
        Bool hoisted__Bool_8587 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8587;
        { Bool _ret_val = hoisted__Bool_8587;
                return _ret_val; }
    }
    Bool hoisted__Bool_8591 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8591;
    if (hoisted__Bool_8591) {
        Bool hoisted__Bool_8588 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8588;
        { Bool _ret_val = hoisted__Bool_8588;
                return _ret_val; }
    }
    Bool hoisted__Bool_8592 = 0;
    (void)hoisted__Bool_8592;
    return hoisted__Bool_8592;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8600 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8600;
    if (hoisted__Bool_8600) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8601 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8601;
    if (hoisted__Bool_8601) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8602 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8602;
    if (hoisted__Bool_8602) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8603 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8603;
    UNREACHABLE(&hoisted__Str_8603);
    Str_delete(&hoisted__Str_8603, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8604 = 4;
    (void)hoisted__U32_8604;
    return hoisted__U32_8604;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8605 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8605;
    static Str hoisted__Str_8606 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8606;
    assert(hoisted__Bool_8605, &hoisted__Str_8606);
    Str_delete(&hoisted__Str_8606, (Bool){0});
    Bool hoisted__Bool_8607 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8607;
    Bool hoisted__Bool_8608 = not(hoisted__Bool_8607);
    (void)hoisted__Bool_8608;
    static Str hoisted__Str_8609 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8609;
    assert(hoisted__Bool_8608, &hoisted__Str_8609);
    Str_delete(&hoisted__Str_8609, (Bool){0});
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
    Bool hoisted__Bool_8610 = is(self, other);
    (void)hoisted__Bool_8610;
    return hoisted__Bool_8610;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8628 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8628;
    if (hoisted__Bool_8628) {
        I64 *hoisted__I64_8624 = get_payload(self);
        (void)hoisted__I64_8624;
        (void)hoisted__I64_8624;
        Bool hoisted__Bool_8625 = 0;
        (void)hoisted__Bool_8625;
        I64_delete(hoisted__I64_8624, hoisted__Bool_8625);
    }
    Bool hoisted__Bool_8629 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8629;
    if (hoisted__Bool_8629) {
        Str *hoisted__Str_8626 = get_payload(self);
        (void)hoisted__Str_8626;
        (void)hoisted__Str_8626;
        Bool hoisted__Bool_8627 = 0;
        (void)hoisted__Bool_8627;
        Str_delete(hoisted__Str_8626, hoisted__Bool_8627);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8660 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8660;
    if (hoisted__Bool_8660) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8657 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8657;
        { Token * _ret_val = hoisted__Token_8657;
                return _ret_val; }
    }
    Bool hoisted__Bool_8661 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8661;
    if (hoisted__Bool_8661) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8658 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8658;
        Token *hoisted__Token_8659 = Token_Name(hoisted__Str_8658);
        (void)hoisted__Token_8659;
        { Token * _ret_val = hoisted__Token_8659;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8662 = 24;
    (void)hoisted__U32_8662;
    return hoisted__U32_8662;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8664 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8664;
    static Str hoisted__Str_8665 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8665;
    assert(hoisted__Bool_8664, &hoisted__Str_8665);
    Str_delete(&hoisted__Str_8665, (Bool){0});
    Bool hoisted__Bool_8666 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8666;
    Bool hoisted__Bool_8667 = not(hoisted__Bool_8666);
    (void)hoisted__Bool_8667;
    static Str hoisted__Str_8668 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8668;
    assert(hoisted__Bool_8667, &hoisted__Str_8668);
    Str_delete(&hoisted__Str_8668, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8669 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8669;
    static Str hoisted__Str_8670 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8670;
    assert(hoisted__Bool_8669, &hoisted__Str_8670);
    Str_delete(&hoisted__Str_8670, (Bool){0});
    Bool hoisted__Bool_8671 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8671;
    Bool hoisted__Bool_8672 = not(hoisted__Bool_8671);
    (void)hoisted__Bool_8672;
    static Str hoisted__Str_8673 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8673;
    assert(hoisted__Bool_8672, &hoisted__Str_8673);
    Str_delete(&hoisted__Str_8673, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8676 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8676;
    static Str hoisted__Str_8677 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8677;
    assert(hoisted__Bool_8676, &hoisted__Str_8677);
    Str_delete(&hoisted__Str_8677, (Bool){0});
    Bool hoisted__Bool_8678 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8678;
    Bool hoisted__Bool_8679 = not(hoisted__Bool_8678);
    (void)hoisted__Bool_8679;
    static Str hoisted__Str_8680 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8680;
    assert(hoisted__Bool_8679, &hoisted__Str_8680);
    Str_delete(&hoisted__Str_8680, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8836 = I64_neq(a, b);
    (void)hoisted__Bool_8836;
    if (hoisted__Bool_8836) {
        U32 hoisted__U32_8820 = 5;
        (void)hoisted__U32_8820;
        Array__Str *_va_Array_240 = Array__Str_new(hoisted__U32_8820);
        (void)_va_Array_240;
        I64 _va_Array_240_ek = 0;
        (void)_va_Array_240_ek;
        OutOfBounds *_va_Array_240_eo = malloc(sizeof(OutOfBounds));
        _va_Array_240_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_240_eo;
        U32 hoisted__U32_8821 = 0;
        (void)hoisted__U32_8821;
        static Str hoisted__Str_8822 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8822;
        static Str hoisted__Str_8823 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8823;
        Array__Str_set(_va_Array_240, hoisted__U32_8821, &hoisted__Str_8822, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8823);
        Str_delete(&hoisted__Str_8823, (Bool){0});
        U32 hoisted__U32_8824 = 1;
        (void)hoisted__U32_8824;
        Str *hoisted__Str_8825 = I64_to_str(a);
        (void)hoisted__Str_8825;
        static Str hoisted__Str_8826 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8826;
        Array__Str_set(_va_Array_240, hoisted__U32_8824, hoisted__Str_8825, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8826);
        Str_delete(&hoisted__Str_8826, (Bool){0});
        U32 hoisted__U32_8827 = 2;
        (void)hoisted__U32_8827;
        static Str hoisted__Str_8828 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8828;
        static Str hoisted__Str_8829 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8829;
        Array__Str_set(_va_Array_240, hoisted__U32_8827, &hoisted__Str_8828, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8829);
        Str_delete(&hoisted__Str_8829, (Bool){0});
        U32 hoisted__U32_8830 = 3;
        (void)hoisted__U32_8830;
        Str *hoisted__Str_8831 = I64_to_str(b);
        (void)hoisted__Str_8831;
        static Str hoisted__Str_8832 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8832;
        Array__Str_set(_va_Array_240, hoisted__U32_8830, hoisted__Str_8831, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8832);
        Str_delete(&hoisted__Str_8832, (Bool){0});
        U32 hoisted__U32_8833 = 4;
        (void)hoisted__U32_8833;
        static Str hoisted__Str_8834 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8834;
        static Str hoisted__Str_8835 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8835;
        Array__Str_set(_va_Array_240, hoisted__U32_8833, &hoisted__Str_8834, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8835);
        OutOfBounds_delete(_va_Array_240_eo, 1);
        Str_delete(&hoisted__Str_8835, (Bool){0});
        panic(_va_Array_240, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8853 = Str_neq(a, b);
    (void)hoisted__Bool_8853;
    if (hoisted__Bool_8853) {
        U32 hoisted__U32_8837 = 5;
        (void)hoisted__U32_8837;
        Array__Str *_va_Array_241 = Array__Str_new(hoisted__U32_8837);
        (void)_va_Array_241;
        I64 _va_Array_241_ek = 0;
        (void)_va_Array_241_ek;
        OutOfBounds *_va_Array_241_eo = malloc(sizeof(OutOfBounds));
        _va_Array_241_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_241_eo;
        U32 hoisted__U32_8838 = 0;
        (void)hoisted__U32_8838;
        static Str hoisted__Str_8839 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8839;
        static Str hoisted__Str_8840 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8840;
        Array__Str_set(_va_Array_241, hoisted__U32_8838, &hoisted__Str_8839, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8840);
        Str_delete(&hoisted__Str_8840, (Bool){0});
        U32 hoisted__U32_8841 = 1;
        (void)hoisted__U32_8841;
        Str *hoisted__Str_8842 = Str_to_str(a);
        (void)hoisted__Str_8842;
        static Str hoisted__Str_8843 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8843;
        Array__Str_set(_va_Array_241, hoisted__U32_8841, hoisted__Str_8842, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8843);
        Str_delete(&hoisted__Str_8843, (Bool){0});
        U32 hoisted__U32_8844 = 2;
        (void)hoisted__U32_8844;
        static Str hoisted__Str_8845 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8845;
        static Str hoisted__Str_8846 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8846;
        Array__Str_set(_va_Array_241, hoisted__U32_8844, &hoisted__Str_8845, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8846);
        Str_delete(&hoisted__Str_8846, (Bool){0});
        U32 hoisted__U32_8847 = 3;
        (void)hoisted__U32_8847;
        Str *hoisted__Str_8848 = Str_to_str(b);
        (void)hoisted__Str_8848;
        static Str hoisted__Str_8849 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8849;
        Array__Str_set(_va_Array_241, hoisted__U32_8847, hoisted__Str_8848, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8849);
        Str_delete(&hoisted__Str_8849, (Bool){0});
        U32 hoisted__U32_8850 = 4;
        (void)hoisted__U32_8850;
        static Str hoisted__Str_8851 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8851;
        static Str hoisted__Str_8852 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8852;
        Array__Str_set(_va_Array_241, hoisted__U32_8850, &hoisted__Str_8851, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8852);
        OutOfBounds_delete(_va_Array_241_eo, 1);
        Str_delete(&hoisted__Str_8852, (Bool){0});
        panic(_va_Array_241, loc);
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
void *Array__Str_unsafe_get_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Array__Str_unsafe_get(_a0, _a1);
}
static __attribute__((unused)) TilClosure Array__Str_unsafe_get_dyn__til_closure = { (void *)Array__Str_unsafe_get_dyn, NULL, NULL };
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
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "unsafe_get", 10ULL) == 0) return (void*)&Array__Str_unsafe_get_dyn__til_closure;
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
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit223 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit223; });
        if (*index == 1LL) return ({ static Str _lit224 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit224; });
        if (*index == 2LL) return ({ static Str _lit225 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit225; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit226 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit226; });
        if (*index == 1LL) return ({ static Str _lit227 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit227; });
        if (*index == 2LL) return ({ static Str _lit228 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit228; });
        if (*index == 3LL) return ({ static Str _lit229 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit229; });
        if (*index == 4LL) return ({ static Str _lit230 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit230; });
        if (*index == 5LL) return ({ static Str _lit231 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit231; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit232 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit232; });
        if (*index == 1LL) return ({ static Str _lit233 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit233; });
        if (*index == 2LL) return ({ static Str _lit234 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit234; });
        if (*index == 3LL) return ({ static Str _lit235 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit235; });
        if (*index == 4LL) return ({ static Str _lit236 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit236; });
        if (*index == 5LL) return ({ static Str _lit237 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit237; });
        if (*index == 6LL) return ({ static Str _lit238 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit238; });
        if (*index == 7LL) return ({ static Str _lit239 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit239; });
        if (*index == 8LL) return ({ static Str _lit240 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit240; });
        if (*index == 9LL) return ({ static Str _lit241 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit241; });
        if (*index == 10LL) return ({ static Str _lit242 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit242; });
        if (*index == 11LL) return ({ static Str _lit243 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit243; });
        if (*index == 12LL) return ({ static Str _lit244 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit244; });
        if (*index == 13LL) return ({ static Str _lit245 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit245; });
        if (*index == 14LL) return ({ static Str _lit246 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit246; });
        if (*index == 15LL) return ({ static Str _lit247 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit247; });
        if (*index == 16LL) return ({ static Str _lit248 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit248; });
        if (*index == 17LL) return ({ static Str _lit249 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit249; });
        if (*index == 18LL) return ({ static Str _lit250 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit250; });
        if (*index == 19LL) return ({ static Str _lit251 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit251; });
        if (*index == 20LL) return ({ static Str _lit252 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit252; });
        if (*index == 21LL) return ({ static Str _lit253 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit253; });
        if (*index == 22LL) return ({ static Str _lit254 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit254; });
        if (*index == 23LL) return ({ static Str _lit255 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit255; });
        if (*index == 24LL) return ({ static Str _lit256 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit256; });
        if (*index == 25LL) return ({ static Str _lit257 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit257; });
        if (*index == 26LL) return ({ static Str _lit258 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit258; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit259 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit259; });
        if (*index == 1LL) return ({ static Str _lit260 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit260; });
        if (*index == 2LL) return ({ static Str _lit261 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit261; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit262 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit262; });
        if (*index == 1LL) return ({ static Str _lit263 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit263; });
        if (*index == 2LL) return ({ static Str _lit264 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit264; });
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
        if (*index == 0LL) return ({ static Str _lit265 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit265; });
        if (*index == 1LL) return ({ static Str _lit266 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit266; });
        if (*index == 2LL) return ({ static Str _lit267 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit267; });
        if (*index == 3LL) return ({ static Str _lit268 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit268; });
        if (*index == 4LL) return ({ static Str _lit269 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit269; });
        if (*index == 5LL) return ({ static Str _lit270 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit270; });
        if (*index == 6LL) return ({ static Str _lit271 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit271; });
        if (*index == 7LL) return ({ static Str _lit272 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit272; });
        if (*index == 8LL) return ({ static Str _lit273 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit273; });
        if (*index == 9LL) return ({ static Str _lit274 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit274; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit275 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit275; });
        if (*index == 1LL) return ({ static Str _lit276 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit276; });
        if (*index == 2LL) return ({ static Str _lit277 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit277; });
        if (*index == 3LL) return ({ static Str _lit278 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit278; });
        if (*index == 4LL) return ({ static Str _lit279 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit279; });
        if (*index == 5LL) return ({ static Str _lit280 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit280; });
        if (*index == 6LL) return ({ static Str _lit281 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit281; });
        if (*index == 7LL) return ({ static Str _lit282 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit282; });
        if (*index == 8LL) return ({ static Str _lit283 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit283; });
        if (*index == 9LL) return ({ static Str _lit284 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit284; });
        if (*index == 10LL) return ({ static Str _lit285 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit285; });
        if (*index == 11LL) return ({ static Str _lit286 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit286; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit287 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit287; });
        if (*index == 1LL) return ({ static Str _lit288 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit288; });
        if (*index == 2LL) return ({ static Str _lit289 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit289; });
        if (*index == 3LL) return ({ static Str _lit290 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit290; });
        if (*index == 4LL) return ({ static Str _lit291 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit291; });
        if (*index == 5LL) return ({ static Str _lit292 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit292; });
        if (*index == 6LL) return ({ static Str _lit293 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit293; });
        if (*index == 7LL) return ({ static Str _lit294 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit294; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit295 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit295; });
        if (*index == 1LL) return ({ static Str _lit296 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit296; });
        if (*index == 2LL) return ({ static Str _lit297 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit297; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit298 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit298; });
        if (*index == 1LL) return ({ static Str _lit299 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit299; });
        if (*index == 2LL) return ({ static Str _lit300 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit300; });
        if (*index == 3LL) return ({ static Str _lit301 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit301; });
        if (*index == 4LL) return ({ static Str _lit302 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit302; });
        if (*index == 5LL) return ({ static Str _lit303 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit303; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit304 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit304; });
        if (*index == 1LL) return ({ static Str _lit305 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit305; });
        if (*index == 2LL) return ({ static Str _lit306 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit306; });
        if (*index == 3LL) return ({ static Str _lit307 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit307; });
        if (*index == 4LL) return ({ static Str _lit308 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit308; });
        if (*index == 5LL) return ({ static Str _lit309 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit309; });
        if (*index == 6LL) return ({ static Str _lit310 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit310; });
        if (*index == 7LL) return ({ static Str _lit311 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit311; });
        if (*index == 8LL) return ({ static Str _lit312 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit312; });
        if (*index == 9LL) return ({ static Str _lit313 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit313; });
        if (*index == 10LL) return ({ static Str _lit314 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit314; });
        if (*index == 11LL) return ({ static Str _lit315 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit315; });
        if (*index == 12LL) return ({ static Str _lit316 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit316; });
        if (*index == 13LL) return ({ static Str _lit317 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit317; });
        if (*index == 14LL) return ({ static Str _lit318 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit318; });
        if (*index == 15LL) return ({ static Str _lit319 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit319; });
        if (*index == 16LL) return ({ static Str _lit320 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit320; });
        if (*index == 17LL) return ({ static Str _lit321 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit321; });
        if (*index == 18LL) return ({ static Str _lit322 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit322; });
        if (*index == 19LL) return ({ static Str _lit323 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit323; });
        if (*index == 20LL) return ({ static Str _lit324 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit324; });
        if (*index == 21LL) return ({ static Str _lit325 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit325; });
        if (*index == 22LL) return ({ static Str _lit326 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit326; });
        if (*index == 23LL) return ({ static Str _lit327 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit327; });
        if (*index == 24LL) return ({ static Str _lit328 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit328; });
        if (*index == 25LL) return ({ static Str _lit329 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit329; });
        if (*index == 26LL) return ({ static Str _lit330 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit330; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit331 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit331; });
        if (*index == 1LL) return ({ static Str _lit332 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit332; });
        if (*index == 2LL) return ({ static Str _lit333 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit333; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit334 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit334; });
        if (*index == 1LL) return ({ static Str _lit335 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit335; });
        if (*index == 2LL) return ({ static Str _lit336 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit336; });
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
        if (*index == 0LL) return ({ static Str _lit337 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit337; });
        if (*index == 1LL) return ({ static Str _lit338 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit338; });
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
        if (*index == 0LL) return ({ static Str _lit339 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit339; });
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
