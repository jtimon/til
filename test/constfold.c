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
I8 * Str_unsafe_get(Str * self, U32 * i);
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
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I8 * Str_unsafe_get(Str * self, U32 * i);
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

static Str hoisted__Str_7080 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7082 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7083 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7087 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7099 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7100 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7103 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7104 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7325 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7333 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7341 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7344 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7345 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7373 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7374 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7378 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7379 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7402 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7403 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7414 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7415 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7428 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8027 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8028 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8031 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8035 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8039 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8044 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8045 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8046 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8049 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8050 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8051 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8091 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8093 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8097 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8099 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8140 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8142 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8144 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8146 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8198 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8199 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8201 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8202 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8204 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8205 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8227 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8230 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8286 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8289 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8291 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8294 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8298 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8301 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8419 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8420 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8423 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8425 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8426 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8429 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8431 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8432 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8436 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8437 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8440 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8442 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8443 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8446 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8448 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8449 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};

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
    U32 hoisted__U32_130 = 0;
    (void)hoisted__U32_130;
    U64 hoisted__U64_131 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_130); });
    (void)hoisted__U64_131;
    return hoisted__U64_131;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_146 = U32_to_i64(val);
    (void)hoisted__I64_146;
    Str *hoisted__Str_147 = I64_to_str(hoisted__I64_146);
    (void)hoisted__Str_147;
    return hoisted__Str_147;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_148 = 1;
    (void)hoisted__U32_148;
    U32 hoisted__U32_149 = U32_add(DEREF(self), hoisted__U32_148);
    (void)hoisted__U32_149;
    *self = hoisted__U32_149;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_150 = 1;
    (void)hoisted__U32_150;
    U32 hoisted__U32_151 = U32_sub(DEREF(self), hoisted__U32_150);
    (void)hoisted__U32_151;
    *self = hoisted__U32_151;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_158 = 4;
    (void)hoisted__U32_158;
    return hoisted__U32_158;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_243 = 0;
    (void)hoisted__U32_243;
    U64 hoisted__U64_244 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_243); });
    (void)hoisted__U64_244;
    return hoisted__U64_244;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_247 = U32_cmp(a, b);
    (void)hoisted__I64_247;
    I64 hoisted__I64_248 = -1;
    (void)hoisted__I64_248;
    Bool hoisted__Bool_249 = I64_eq(hoisted__I64_247, hoisted__I64_248);
    (void)hoisted__Bool_249;
    return hoisted__Bool_249;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_250 = U32_cmp(a, b);
    (void)hoisted__I64_250;
    I64 hoisted__I64_251 = 1;
    (void)hoisted__I64_251;
    Bool hoisted__Bool_252 = I64_eq(hoisted__I64_250, hoisted__I64_251);
    (void)hoisted__Bool_252;
    return hoisted__Bool_252;
}

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_253 = U32_eq(a, b);
    (void)hoisted__Bool_253;
    Bool hoisted__Bool_254 = not(hoisted__Bool_253);
    (void)hoisted__Bool_254;
    return hoisted__Bool_254;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_255 = U32_gt(a, b);
    (void)hoisted__Bool_255;
    Bool hoisted__Bool_256 = not(hoisted__Bool_255);
    (void)hoisted__Bool_256;
    return hoisted__Bool_256;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_257 = U32_lt(a, b);
    (void)hoisted__Bool_257;
    Bool hoisted__Bool_258 = not(hoisted__Bool_257);
    (void)hoisted__Bool_258;
    return hoisted__Bool_258;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_279 = 4;
    (void)hoisted__U32_279;
    return hoisted__U32_279;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_421 = 0;
    (void)hoisted__U32_421;
    U64 hoisted__U64_422 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_421); });
    (void)hoisted__U64_422;
    return hoisted__U64_422;
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
    U32 hoisted__U32_486 = 1;
    (void)hoisted__U32_486;
    return hoisted__U32_486;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_571 = 0;
    (void)hoisted__U32_571;
    U64 hoisted__U64_572 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_571); });
    (void)hoisted__U64_572;
    return hoisted__U64_572;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_702 = parts;
        (void)_fc_Array__Str_702;
        (void)_fc_Array__Str_702;
        U32 _fi_USize_702 = 0;
        (void)_fi_USize_702;
        while (1) {
            U32 hoisted__U32_704 = Array__Str_len(_fc_Array__Str_702);
            (void)hoisted__U32_704;
            Bool _wcond_Bool_703 = U32_lt(_fi_USize_702, hoisted__U32_704);
            (void)_wcond_Bool_703;
            if (_wcond_Bool_703) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_702, &_fi_USize_702);
            U32 hoisted__U32_705 = 1;
            (void)hoisted__U32_705;
            U32 hoisted__U32_706 = U32_add(_fi_USize_702, hoisted__U32_705);
            (void)hoisted__U32_706;
            _fi_USize_702 = hoisted__U32_706;
            U32 hoisted__U32_707 = Str_len(s);
            (void)hoisted__U32_707;
            U32 hoisted__U32_708 = U32_add(total, hoisted__U32_707);
            (void)hoisted__U32_708;
            total = hoisted__U32_708;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_709 = parts;
        (void)_fc_Array__Str_709;
        (void)_fc_Array__Str_709;
        U32 _fi_USize_709 = 0;
        (void)_fi_USize_709;
        while (1) {
            U32 hoisted__U32_711 = Array__Str_len(_fc_Array__Str_709);
            (void)hoisted__U32_711;
            Bool _wcond_Bool_710 = U32_lt(_fi_USize_709, hoisted__U32_711);
            (void)_wcond_Bool_710;
            if (_wcond_Bool_710) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_709, &_fi_USize_709);
            U32 hoisted__U32_712 = 1;
            (void)hoisted__U32_712;
            U32 hoisted__U32_713 = U32_add(_fi_USize_709, hoisted__U32_712);
            (void)hoisted__U32_713;
            _fi_USize_709 = hoisted__U32_713;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_unsafe_get(Str * self, U32 * i) {
    void *hoisted__v_721 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_721;
    (void)hoisted__v_721;
    return hoisted__v_721;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_730 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_730;
    if (hoisted__Bool_730) {
        min_len = b->count;
    }
    {
        U32 _re_U32_722 = U32_clone(&min_len);
        (void)_re_U32_722;
        U32 _rc_U32_722 = 0;
        (void)_rc_U32_722;
        Bool hoisted__Bool_729 = U32_lte(_rc_U32_722, _re_U32_722);
        (void)hoisted__Bool_729;
        if (hoisted__Bool_729) {
            while (1) {
                Bool _wcond_Bool_723 = U32_lt(_rc_U32_722, _re_U32_722);
                (void)_wcond_Bool_723;
                if (_wcond_Bool_723) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_722);
                U32_inc(&_rc_U32_722);
                I8 *ab = Str_unsafe_get(a, &i);
                I8 *bb = Str_unsafe_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_724 = 0;
                (void)hoisted__I64_724;
                Bool hoisted__Bool_725 = I64_neq(c, hoisted__I64_724);
                (void)hoisted__Bool_725;
                if (hoisted__Bool_725) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_726 = U32_gt(_rc_U32_722, _re_U32_722);
                (void)_wcond_Bool_726;
                if (_wcond_Bool_726) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_722);
                U32_dec(&_rc_U32_722);
                I8 *ab = Str_unsafe_get(a, &i);
                I8 *bb = Str_unsafe_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_727 = 0;
                (void)hoisted__I64_727;
                Bool hoisted__Bool_728 = I64_neq(c, hoisted__I64_727);
                (void)hoisted__Bool_728;
                if (hoisted__Bool_728) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_731 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_731;
    return hoisted__I64_731;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_732 = 1;
    (void)hoisted__U32_732;
    U32 hoisted__U64_733 = U32_add(n, hoisted__U32_732);
    (void)hoisted__U64_733;
    void * buf = malloc(hoisted__U64_733);
    I32 hoisted__I32_734 = 0;
    (void)hoisted__I32_734;
    U64 hoisted__U64_735 = 1ULL;
    (void)hoisted__U64_735;
    memset(buf, hoisted__I32_734, hoisted__U64_735);
    I64 hoisted__I64_736 = 0;
    (void)hoisted__I64_736;
    Str *hoisted__Str_737 = malloc(sizeof(Str));
    hoisted__Str_737->c_str = buf;
    hoisted__Str_737->count = hoisted__I64_736;
    hoisted__Str_737->cap = n;
    (void)hoisted__Str_737;
    return hoisted__Str_737;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_750 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_750;
    if (hoisted__Bool_750) {
        U32 hoisted__U32_740 = 1;
        (void)hoisted__U32_740;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_740);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_741 = 0;
        (void)hoisted__U32_741;
        static Str hoisted__Str_742 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_742;
        static Str hoisted__Str_743 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_743;
        Array__Str_set(_va_Array_18, hoisted__U32_741, &hoisted__Str_742, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_743);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_743, (Bool){0});
        static Str hoisted__Str_744 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_744;
        panic(_va_Array_18, &hoisted__Str_744);
        Str_delete(&hoisted__Str_744, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_751 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_751;
    if (hoisted__Bool_751) {
        U32 hoisted__U32_745 = 1;
        (void)hoisted__U32_745;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_745);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_746 = 0;
        (void)hoisted__U32_746;
        static Str hoisted__Str_747 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_747;
        static Str hoisted__Str_748 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_748;
        Array__Str_set(_va_Array_19, hoisted__U32_746, &hoisted__Str_747, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_748);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_748, (Bool){0});
        static Str hoisted__Str_749 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_749;
        panic(_va_Array_19, &hoisted__Str_749);
        Str_delete(&hoisted__Str_749, (Bool){0});
    }
    void *hoisted__v_752 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_752;
    (void)hoisted__v_752;
    memcpy(hoisted__v_752, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_753 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_753;
    (void)hoisted__v_753;
    I32 hoisted__I32_754 = 0;
    (void)hoisted__I32_754;
    U64 hoisted__U64_755 = 1ULL;
    (void)hoisted__U64_755;
    memset(hoisted__v_753, hoisted__I32_754, hoisted__U64_755);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_756 = 1;
    (void)hoisted__U32_756;
    U32 hoisted__U64_757 = U32_add(val->count, hoisted__U32_756);
    (void)hoisted__U64_757;
    void * new_data = malloc(hoisted__U64_757);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_758 = ptr_add(new_data, val->count);
    (void)hoisted__v_758;
    (void)hoisted__v_758;
    I32 hoisted__I32_759 = 0;
    (void)hoisted__I32_759;
    U64 hoisted__U64_760 = 1ULL;
    (void)hoisted__U64_760;
    memset(hoisted__v_758, hoisted__I32_759, hoisted__U64_760);
    Str *hoisted__Str_761 = malloc(sizeof(Str));
    hoisted__Str_761->c_str = new_data;
    hoisted__Str_761->count = val->count;
    hoisted__Str_761->cap = val->count;
    (void)hoisted__Str_761;
    return hoisted__Str_761;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_762 = Str_clone(self);
    (void)hoisted__Str_762;
    return hoisted__Str_762;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_763 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_763;
    if (hoisted__Bool_763) {
        free(self->c_str);
    }
    Bool hoisted__Bool_764 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_764;
    Bool hoisted__Bool_765 = and(call_free, hoisted__Bool_764);
    (void)hoisted__Bool_765;
    if (hoisted__Bool_765) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_960 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_960;
    return hoisted__U64_960;
}

U32 Str_size(void) {
    U32 hoisted__U32_1144 = 16;
    (void)hoisted__U32_1144;
    return hoisted__U32_1144;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1145 = Str_cmp(a, b);
    (void)hoisted__I64_1145;
    I64 hoisted__I64_1146 = 0;
    (void)hoisted__I64_1146;
    Bool hoisted__Bool_1147 = I64_eq(hoisted__I64_1145, hoisted__I64_1146);
    (void)hoisted__Bool_1147;
    return hoisted__Bool_1147;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1156 = Str_eq(a, b);
    (void)hoisted__Bool_1156;
    Bool hoisted__Bool_1157 = not(hoisted__Bool_1156);
    (void)hoisted__Bool_1157;
    return hoisted__Bool_1157;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1248 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1248->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1248;
    return hoisted__OutOfBounds_1248;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1249 = 0;
    (void)hoisted__Bool_1249;
    Str_delete(&self->msg, hoisted__Bool_1249);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1250 = 0;
    (void)hoisted__U32_1250;
    U64 hoisted__U64_1251 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1250); });
    (void)hoisted__U64_1251;
    return hoisted__U64_1251;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1270 = 16;
    (void)hoisted__U32_1270;
    return hoisted__U32_1270;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_1294 = 16;
    (void)hoisted__U32_1294;
    U64 hoisted__U64_1295 = (U64)(cap);
    (void)hoisted__U64_1295;
    U64 hoisted__U64_1296 = (U64)(hoisted__U32_1294);
    (void)hoisted__U64_1296;
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

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_1299 = 16;
    (void)hoisted__U32_1299;
    U32 hoisted__U32_1300 = U32_mul(DEREF(i), hoisted__U32_1299);
    (void)hoisted__U32_1300;
    U64 hoisted__U64_1301 = (U64)(hoisted__U32_1300);
    (void)hoisted__U64_1301;
    void *hoisted__v_1302 = ptr_add(self->data, hoisted__U64_1301);
    (void)hoisted__v_1302;
    (void)hoisted__v_1302;
    return hoisted__v_1302;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_1329 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1329;
    (void)hoisted__Str_1329;
    Bool hoisted__Bool_1330 = 0;
    (void)hoisted__Bool_1330;
    Str_delete(hoisted__Str_1329, hoisted__Bool_1330);
    U32 hoisted__U32_1331 = 16;
    (void)hoisted__U32_1331;
    Str *hoisted__Str_1332 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1332;
    (void)hoisted__Str_1332;
    U64 hoisted__U64_1333 = (U64)(hoisted__U32_1331);
    (void)hoisted__U64_1333;
    memcpy(hoisted__Str_1332, val, hoisted__U64_1333);
    U32 hoisted__U32_1334 = 16;
    (void)hoisted__U32_1334;
    I32 hoisted__I32_1335 = 0;
    (void)hoisted__I32_1335;
    U64 hoisted__U64_1336 = (U64)(hoisted__U32_1334);
    (void)hoisted__U64_1336;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1335, hoisted__U64_1336); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1359 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1359;
    if (hoisted__Bool_1359) {
        U32 hoisted__U32_1337 = 6;
        (void)hoisted__U32_1337;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1337);
        (void)_va_Array_31;
        I64 _va_Array_31_ek = 0;
        (void)_va_Array_31_ek;
        OutOfBounds *_va_Array_31_eo = malloc(sizeof(OutOfBounds));
        _va_Array_31_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_31_eo;
        U32 hoisted__U32_1338 = 0;
        (void)hoisted__U32_1338;
        Str *hoisted__Str_1339 = Str_clone(loc);
        (void)hoisted__Str_1339;
        static Str hoisted__Str_1340 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1340;
        Array__Str_set(_va_Array_31, hoisted__U32_1338, hoisted__Str_1339, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1340);
        Str_delete(&hoisted__Str_1340, (Bool){0});
        U32 hoisted__U32_1341 = 1;
        (void)hoisted__U32_1341;
        static Str hoisted__Str_1342 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1342;
        static Str hoisted__Str_1343 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1343;
        Array__Str_set(_va_Array_31, hoisted__U32_1341, &hoisted__Str_1342, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1343);
        Str_delete(&hoisted__Str_1343, (Bool){0});
        U32 hoisted__U32_1344 = 2;
        (void)hoisted__U32_1344;
        Str *hoisted__Str_1345 = U32_to_str(i);
        (void)hoisted__Str_1345;
        static Str hoisted__Str_1346 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1346;
        Array__Str_set(_va_Array_31, hoisted__U32_1344, hoisted__Str_1345, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1346);
        Str_delete(&hoisted__Str_1346, (Bool){0});
        U32 hoisted__U32_1347 = 3;
        (void)hoisted__U32_1347;
        static Str hoisted__Str_1348 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1348;
        static Str hoisted__Str_1349 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1349;
        Array__Str_set(_va_Array_31, hoisted__U32_1347, &hoisted__Str_1348, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1349);
        Str_delete(&hoisted__Str_1349, (Bool){0});
        U32 hoisted__U32_1350 = 4;
        (void)hoisted__U32_1350;
        Str *hoisted__Str_1351 = U32_to_str(self->cap);
        (void)hoisted__Str_1351;
        static Str hoisted__Str_1352 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1352;
        Array__Str_set(_va_Array_31, hoisted__U32_1350, hoisted__Str_1351, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1352);
        Str_delete(&hoisted__Str_1352, (Bool){0});
        U32 hoisted__U32_1353 = 5;
        (void)hoisted__U32_1353;
        static Str hoisted__Str_1354 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1354;
        static Str hoisted__Str_1355 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1355;
        Array__Str_set(_va_Array_31, hoisted__U32_1353, &hoisted__Str_1354, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1355);
        OutOfBounds_delete(_va_Array_31_eo, 1);
        Str_delete(&hoisted__Str_1355, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1356 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_31); hoisted__OutOfBounds_1356->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1356;
        U32 hoisted__U32_1357 = 16;
        (void)hoisted__U32_1357;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1356, hoisted__U32_1357);
        OutOfBounds_delete(hoisted__OutOfBounds_1356, 1);
        I64 hoisted__I64_1358 = 3;
        (void)hoisted__I64_1358;
        *_err_kind = hoisted__I64_1358;
    }
    I64 hoisted__I64_1360 = 0;
    (void)hoisted__I64_1360;
    Bool hoisted__Bool_1361 = I64_eq(DEREF(_err_kind), hoisted__I64_1360);
    (void)hoisted__Bool_1361;
    if (hoisted__Bool_1361) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1362 = self->cap;
        (void)_re_U32_1362;
        U32 _rc_U32_1362 = 0;
        (void)_rc_U32_1362;
        Bool hoisted__Bool_1375 = U32_lte(_rc_U32_1362, _re_U32_1362);
        (void)hoisted__Bool_1375;
        if (hoisted__Bool_1375) {
            while (1) {
                Bool _wcond_Bool_1363 = U32_lt(_rc_U32_1362, _re_U32_1362);
                (void)_wcond_Bool_1363;
                if (_wcond_Bool_1363) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1362);
                U32_inc(&_rc_U32_1362);
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
        } else {
            while (1) {
                Bool _wcond_Bool_1369 = U32_gt(_rc_U32_1362, _re_U32_1362);
                (void)_wcond_Bool_1369;
                if (_wcond_Bool_1369) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1362);
                U32_dec(&_rc_U32_1362);
                U32 hoisted__U32_1370 = 16;
                (void)hoisted__U32_1370;
                U32 hoisted__U32_1371 = U32_mul(i, hoisted__U32_1370);
                (void)hoisted__U32_1371;
                U64 hoisted__U64_1372 = (U64)(hoisted__U32_1371);
                (void)hoisted__U64_1372;
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
    U32 hoisted__U32_1404 = 16;
    (void)hoisted__U32_1404;
    U32 hoisted__U32_1405 = U32_mul(self->cap, hoisted__U32_1404);
    (void)hoisted__U32_1405;
    U64 hoisted__U64_1406 = (U64)(hoisted__U32_1405);
    (void)hoisted__U64_1406;
    void * new_data = malloc(hoisted__U64_1406);
    {
        U32 _re_U32_1376 = self->cap;
        (void)_re_U32_1376;
        U32 _rc_U32_1376 = 0;
        (void)_rc_U32_1376;
        Bool hoisted__Bool_1403 = U32_lte(_rc_U32_1376, _re_U32_1376);
        (void)hoisted__Bool_1403;
        if (hoisted__Bool_1403) {
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
                U64 hoisted__U64_1380 = (U64)(hoisted__U32_1379);
                (void)hoisted__U64_1380;
                Str *src = ptr_add(self->data, hoisted__U64_1380);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1381 = 16;
                (void)hoisted__U32_1381;
                U32 hoisted__U32_1382 = U32_mul(i, hoisted__U32_1381);
                (void)hoisted__U32_1382;
                U64 hoisted__U64_1383 = (U64)(hoisted__U32_1382);
                (void)hoisted__U64_1383;
                U32 hoisted__U32_1384 = 16;
                (void)hoisted__U32_1384;
                void *hoisted__v_1385 = ptr_add(new_data, hoisted__U64_1383);
                (void)hoisted__v_1385;
                (void)hoisted__v_1385;
                U64 hoisted__U64_1386 = (U64)(hoisted__U32_1384);
                (void)hoisted__U64_1386;
                memcpy(hoisted__v_1385, cloned, hoisted__U64_1386);
                U32 hoisted__U32_1387 = 16;
                (void)hoisted__U32_1387;
                I32 hoisted__I32_1388 = 0;
                (void)hoisted__I32_1388;
                U64 hoisted__U64_1389 = (U64)(hoisted__U32_1387);
                (void)hoisted__U64_1389;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1388, hoisted__U64_1389); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1390 = U32_gt(_rc_U32_1376, _re_U32_1376);
                (void)_wcond_Bool_1390;
                if (_wcond_Bool_1390) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1376);
                U32_dec(&_rc_U32_1376);
                U32 hoisted__U32_1391 = 16;
                (void)hoisted__U32_1391;
                U32 hoisted__U32_1392 = U32_mul(i, hoisted__U32_1391);
                (void)hoisted__U32_1392;
                U64 hoisted__U64_1393 = (U64)(hoisted__U32_1392);
                (void)hoisted__U64_1393;
                Str *src = ptr_add(self->data, hoisted__U64_1393);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1394 = 16;
                (void)hoisted__U32_1394;
                U32 hoisted__U32_1395 = U32_mul(i, hoisted__U32_1394);
                (void)hoisted__U32_1395;
                U64 hoisted__U64_1396 = (U64)(hoisted__U32_1395);
                (void)hoisted__U64_1396;
                U32 hoisted__U32_1397 = 16;
                (void)hoisted__U32_1397;
                void *hoisted__v_1398 = ptr_add(new_data, hoisted__U64_1396);
                (void)hoisted__v_1398;
                (void)hoisted__v_1398;
                U64 hoisted__U64_1399 = (U64)(hoisted__U32_1397);
                (void)hoisted__U64_1399;
                memcpy(hoisted__v_1398, cloned, hoisted__U64_1399);
                U32 hoisted__U32_1400 = 16;
                (void)hoisted__U32_1400;
                I32 hoisted__I32_1401 = 0;
                (void)hoisted__I32_1401;
                U64 hoisted__U64_1402 = (U64)(hoisted__U32_1400);
                (void)hoisted__U64_1402;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1401, hoisted__U64_1402); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1407 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1407->data = new_data;
    hoisted__Array__Str_1407->cap = self->cap;
    (void)hoisted__Array__Str_1407;
    return hoisted__Array__Str_1407;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1408 = 16;
    (void)hoisted__U32_1408;
    return hoisted__U32_1408;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1409 = 16;
    (void)hoisted__U32_1409;
    U64 hoisted__U64_1410 = (U64)(hoisted__U32_1409);
    (void)hoisted__U64_1410;
    void * hoisted__v_1411 = malloc(hoisted__U64_1410);
    (void)hoisted__v_1411;
    U32 hoisted__U32_1412 = 0;
    (void)hoisted__U32_1412;
    I64 hoisted__I64_1413 = 1;
    (void)hoisted__I64_1413;
    Vec__Str *hoisted__Vec__Str_1414 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1414->data = hoisted__v_1411;
    hoisted__Vec__Str_1414->count = hoisted__U32_1412;
    hoisted__Vec__Str_1414->cap = hoisted__I64_1413;
    (void)hoisted__Vec__Str_1414;
    return hoisted__Vec__Str_1414;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1415 = self->count;
        (void)_re_U32_1415;
        U32 _rc_U32_1415 = 0;
        (void)_rc_U32_1415;
        Bool hoisted__Bool_1428 = U32_lte(_rc_U32_1415, _re_U32_1415);
        (void)hoisted__Bool_1428;
        if (hoisted__Bool_1428) {
            while (1) {
                Bool _wcond_Bool_1416 = U32_lt(_rc_U32_1415, _re_U32_1415);
                (void)_wcond_Bool_1416;
                if (_wcond_Bool_1416) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1415);
                U32_inc(&_rc_U32_1415);
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
        } else {
            while (1) {
                Bool _wcond_Bool_1422 = U32_gt(_rc_U32_1415, _re_U32_1415);
                (void)_wcond_Bool_1422;
                if (_wcond_Bool_1422) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1415);
                U32_dec(&_rc_U32_1415);
                U32 hoisted__U32_1423 = 16;
                (void)hoisted__U32_1423;
                U32 hoisted__U32_1424 = U32_mul(i, hoisted__U32_1423);
                (void)hoisted__U32_1424;
                U64 hoisted__U64_1425 = (U64)(hoisted__U32_1424);
                (void)hoisted__U64_1425;
                Str *hoisted__Str_1426 = ptr_add(self->data, hoisted__U64_1425);
                (void)hoisted__Str_1426;
                (void)hoisted__Str_1426;
                Bool hoisted__Bool_1427 = 0;
                (void)hoisted__Bool_1427;
                Str_delete(hoisted__Str_1426, hoisted__Bool_1427);
            }
        }
    }
    U32 hoisted__U32_1429 = 0;
    (void)hoisted__U32_1429;
    self->count = hoisted__U32_1429;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1699 = 16;
    (void)hoisted__U32_1699;
    U32 hoisted__U32_1700 = U32_mul(self->cap, hoisted__U32_1699);
    (void)hoisted__U32_1700;
    U64 hoisted__U64_1701 = (U64)(hoisted__U32_1700);
    (void)hoisted__U64_1701;
    void * new_data = malloc(hoisted__U64_1701);
    {
        U32 _re_U32_1671 = self->count;
        (void)_re_U32_1671;
        U32 _rc_U32_1671 = 0;
        (void)_rc_U32_1671;
        Bool hoisted__Bool_1698 = U32_lte(_rc_U32_1671, _re_U32_1671);
        (void)hoisted__Bool_1698;
        if (hoisted__Bool_1698) {
            while (1) {
                Bool _wcond_Bool_1672 = U32_lt(_rc_U32_1671, _re_U32_1671);
                (void)_wcond_Bool_1672;
                if (_wcond_Bool_1672) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1671);
                U32_inc(&_rc_U32_1671);
                U32 hoisted__U32_1673 = 16;
                (void)hoisted__U32_1673;
                U32 hoisted__U32_1674 = U32_mul(i, hoisted__U32_1673);
                (void)hoisted__U32_1674;
                U64 hoisted__U64_1675 = (U64)(hoisted__U32_1674);
                (void)hoisted__U64_1675;
                Str *src = ptr_add(self->data, hoisted__U64_1675);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1676 = 16;
                (void)hoisted__U32_1676;
                U32 hoisted__U32_1677 = U32_mul(i, hoisted__U32_1676);
                (void)hoisted__U32_1677;
                U64 hoisted__U64_1678 = (U64)(hoisted__U32_1677);
                (void)hoisted__U64_1678;
                U32 hoisted__U32_1679 = 16;
                (void)hoisted__U32_1679;
                void *hoisted__v_1680 = ptr_add(new_data, hoisted__U64_1678);
                (void)hoisted__v_1680;
                (void)hoisted__v_1680;
                U64 hoisted__U64_1681 = (U64)(hoisted__U32_1679);
                (void)hoisted__U64_1681;
                memcpy(hoisted__v_1680, cloned, hoisted__U64_1681);
                U32 hoisted__U32_1682 = 16;
                (void)hoisted__U32_1682;
                I32 hoisted__I32_1683 = 0;
                (void)hoisted__I32_1683;
                U64 hoisted__U64_1684 = (U64)(hoisted__U32_1682);
                (void)hoisted__U64_1684;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1683, hoisted__U64_1684); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1685 = U32_gt(_rc_U32_1671, _re_U32_1671);
                (void)_wcond_Bool_1685;
                if (_wcond_Bool_1685) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1671);
                U32_dec(&_rc_U32_1671);
                U32 hoisted__U32_1686 = 16;
                (void)hoisted__U32_1686;
                U32 hoisted__U32_1687 = U32_mul(i, hoisted__U32_1686);
                (void)hoisted__U32_1687;
                U64 hoisted__U64_1688 = (U64)(hoisted__U32_1687);
                (void)hoisted__U64_1688;
                Str *src = ptr_add(self->data, hoisted__U64_1688);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1689 = 16;
                (void)hoisted__U32_1689;
                U32 hoisted__U32_1690 = U32_mul(i, hoisted__U32_1689);
                (void)hoisted__U32_1690;
                U64 hoisted__U64_1691 = (U64)(hoisted__U32_1690);
                (void)hoisted__U64_1691;
                U32 hoisted__U32_1692 = 16;
                (void)hoisted__U32_1692;
                void *hoisted__v_1693 = ptr_add(new_data, hoisted__U64_1691);
                (void)hoisted__v_1693;
                (void)hoisted__v_1693;
                U64 hoisted__U64_1694 = (U64)(hoisted__U32_1692);
                (void)hoisted__U64_1694;
                memcpy(hoisted__v_1693, cloned, hoisted__U64_1694);
                U32 hoisted__U32_1695 = 16;
                (void)hoisted__U32_1695;
                I32 hoisted__I32_1696 = 0;
                (void)hoisted__I32_1696;
                U64 hoisted__U64_1697 = (U64)(hoisted__U32_1695);
                (void)hoisted__U64_1697;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1696, hoisted__U64_1697); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1702 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1702->data = new_data;
    hoisted__Vec__Str_1702->count = self->count;
    hoisted__Vec__Str_1702->cap = self->cap;
    (void)hoisted__Vec__Str_1702;
    return hoisted__Vec__Str_1702;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1703 = 16;
    (void)hoisted__U32_1703;
    return hoisted__U32_1703;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1706 = 8;
    (void)hoisted__U32_1706;
    return hoisted__U32_1706;
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
    I64 hoisted__I64_1923 = 0;
    (void)hoisted__I64_1923;
    Bool hoisted__Bool_1924 = I64_eq(val, hoisted__I64_1923);
    (void)hoisted__Bool_1924;
    if (hoisted__Bool_1924) {
        U64 hoisted__U64_1893 = 2ULL;
        (void)hoisted__U64_1893;
        void * buf = malloc(hoisted__U64_1893);
        I64 hoisted__I64_1894 = 48;
        (void)hoisted__I64_1894;
        U64 hoisted__U64_1895 = 1ULL;
        (void)hoisted__U64_1895;
        memcpy(buf, &hoisted__I64_1894, hoisted__U64_1895);
        U64 hoisted__U64_1896 = 1ULL;
        (void)hoisted__U64_1896;
        void *hoisted__v_1897 = ptr_add(buf, hoisted__U64_1896);
        (void)hoisted__v_1897;
        (void)hoisted__v_1897;
        I32 hoisted__I32_1898 = 0;
        (void)hoisted__I32_1898;
        U64 hoisted__U64_1899 = 1ULL;
        (void)hoisted__U64_1899;
        memset(hoisted__v_1897, hoisted__I32_1898, hoisted__U64_1899);
        I64 hoisted__I64_1900 = 1;
        (void)hoisted__I64_1900;
        I64 hoisted__I64_1901 = 1;
        (void)hoisted__I64_1901;
        Str *hoisted__Str_1902 = malloc(sizeof(Str));
        hoisted__Str_1902->c_str = buf;
        hoisted__Str_1902->count = hoisted__I64_1900;
        hoisted__Str_1902->cap = hoisted__I64_1901;
        (void)hoisted__Str_1902;
        { Str * _ret_val = hoisted__Str_1902;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1925 = 0;
    (void)hoisted__I64_1925;
    Bool hoisted__Bool_1926 = I64_lt(val, hoisted__I64_1925);
    (void)hoisted__Bool_1926;
    if (hoisted__Bool_1926) {
        Bool hoisted__Bool_1903 = 1;
        (void)hoisted__Bool_1903;
        is_neg = hoisted__Bool_1903;
        I64 hoisted__I64_1904 = 0;
        (void)hoisted__I64_1904;
        I64 hoisted__I64_1905 = I64_sub(hoisted__I64_1904, val);
        (void)hoisted__I64_1905;
        v = hoisted__I64_1905;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1907 = 0;
        (void)hoisted__I64_1907;
        Bool _wcond_Bool_1906 = I64_gt(tmp, hoisted__I64_1907);
        (void)_wcond_Bool_1906;
        if (_wcond_Bool_1906) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1908 = 10;
        (void)hoisted__I64_1908;
        I64 hoisted__I64_1909 = I64_div(tmp, hoisted__I64_1908);
        (void)hoisted__I64_1909;
        tmp = hoisted__I64_1909;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1927 = 1ULL;
    (void)hoisted__U64_1927;
    U64 hoisted__U64_1928 = U64_add(total, hoisted__U64_1927);
    (void)hoisted__U64_1928;
    void * buf = malloc(hoisted__U64_1928);
    if (is_neg) {
        I64 hoisted__I64_1910 = 45;
        (void)hoisted__I64_1910;
        U64 hoisted__U64_1911 = 1ULL;
        (void)hoisted__U64_1911;
        memcpy(buf, &hoisted__I64_1910, hoisted__U64_1911);
    }
    U64 hoisted__U64_1929 = 1ULL;
    (void)hoisted__U64_1929;
    U64 i = U64_sub(total, hoisted__U64_1929);
    while (1) {
        I64 hoisted__I64_1913 = 0;
        (void)hoisted__I64_1913;
        Bool _wcond_Bool_1912 = I64_gt(v, hoisted__I64_1913);
        (void)_wcond_Bool_1912;
        if (_wcond_Bool_1912) {
        } else {
            break;
        }
        I64 hoisted__I64_1914 = 10;
        (void)hoisted__I64_1914;
        I64 hoisted__I64_1915 = I64_mod(v, hoisted__I64_1914);
        (void)hoisted__I64_1915;
        I64 hoisted__I64_1916 = 48;
        (void)hoisted__I64_1916;
        I64 hoisted__I64_1917 = I64_add(hoisted__I64_1915, hoisted__I64_1916);
        (void)hoisted__I64_1917;
        void *hoisted__v_1918 = ptr_add(buf, i);
        (void)hoisted__v_1918;
        (void)hoisted__v_1918;
        U8 hoisted__U8_1919 = I64_to_u8(hoisted__I64_1917);
        (void)hoisted__U8_1919;
        U64 hoisted__U64_1920 = 1ULL;
        (void)hoisted__U64_1920;
        memcpy(hoisted__v_1918, &hoisted__U8_1919, hoisted__U64_1920);
        I64 hoisted__I64_1921 = 10;
        (void)hoisted__I64_1921;
        I64 hoisted__I64_1922 = I64_div(v, hoisted__I64_1921);
        (void)hoisted__I64_1922;
        v = hoisted__I64_1922;
        U64_dec(&i);
    }
    void *hoisted__v_1930 = ptr_add(buf, total);
    (void)hoisted__v_1930;
    (void)hoisted__v_1930;
    I32 hoisted__I32_1931 = 0;
    (void)hoisted__I32_1931;
    U64 hoisted__U64_1932 = 1ULL;
    (void)hoisted__U64_1932;
    memset(hoisted__v_1930, hoisted__I32_1931, hoisted__U64_1932);
    Str *hoisted__Str_1933 = malloc(sizeof(Str));
    hoisted__Str_1933->c_str = buf;
    hoisted__Str_1933->count = total;
    hoisted__Str_1933->cap = total;
    (void)hoisted__Str_1933;
    return hoisted__Str_1933;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1951 = 8;
    (void)hoisted__U32_1951;
    return hoisted__U32_1951;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2109 = 0;
    (void)hoisted__U32_2109;
    U64 hoisted__U64_2110 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2109); });
    (void)hoisted__U64_2110;
    return hoisted__U64_2110;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2113 = I64_cmp(a, b);
    (void)hoisted__I64_2113;
    I64 hoisted__I64_2114 = -1;
    (void)hoisted__I64_2114;
    Bool hoisted__Bool_2115 = I64_eq(hoisted__I64_2113, hoisted__I64_2114);
    (void)hoisted__Bool_2115;
    return hoisted__Bool_2115;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2116 = I64_cmp(a, b);
    (void)hoisted__I64_2116;
    I64 hoisted__I64_2117 = 1;
    (void)hoisted__I64_2117;
    Bool hoisted__Bool_2118 = I64_eq(hoisted__I64_2116, hoisted__I64_2117);
    (void)hoisted__Bool_2118;
    return hoisted__Bool_2118;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2119 = I64_eq(a, b);
    (void)hoisted__Bool_2119;
    Bool hoisted__Bool_2120 = not(hoisted__Bool_2119);
    (void)hoisted__Bool_2120;
    return hoisted__Bool_2120;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2171 = 0;
    (void)_m_Bool_2171;
    {
        Bool hoisted__Bool_2174 = 1;
        (void)hoisted__Bool_2174;
        Bool hoisted__Bool_2175 = Bool_eq(a, hoisted__Bool_2174);
        (void)hoisted__Bool_2175;
        if (hoisted__Bool_2175) {
            Bool hoisted__Bool_2172 = Bool_clone(&b);
            (void)hoisted__Bool_2172;
            _m_Bool_2171 = hoisted__Bool_2172;
        } else {
            Bool hoisted__Bool_2173 = 0;
            (void)hoisted__Bool_2173;
            _m_Bool_2171 = hoisted__Bool_2173;
        }
    }
    return _m_Bool_2171;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2185 = Bool_eq(a, b);
    (void)hoisted__Bool_2185;
    if (hoisted__Bool_2185) {
        I64 hoisted__I64_2183 = 0;
        (void)hoisted__I64_2183;
        { I64 _ret_val = hoisted__I64_2183;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2184 = -1;
        (void)hoisted__I64_2184;
        return hoisted__I64_2184;
    }
    I64 hoisted__I64_2186 = 1;
    (void)hoisted__I64_2186;
    return hoisted__I64_2186;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2187 = 1;
    (void)hoisted__U32_2187;
    return hoisted__U32_2187;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2188 = 0;
    (void)hoisted__U32_2188;
    U64 hoisted__U64_2189 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2188); });
    (void)hoisted__U64_2189;
    return hoisted__U64_2189;
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
    Bool hoisted__Bool_2215 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2215;
    if (hoisted__Bool_2215) {
        Bool hoisted__Bool_2205 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2205;
        { Bool _ret_val = hoisted__Bool_2205;
                return _ret_val; }
    }
    Bool hoisted__Bool_2216 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2216;
    if (hoisted__Bool_2216) {
        Bool hoisted__Bool_2206 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2206;
        { Bool _ret_val = hoisted__Bool_2206;
                return _ret_val; }
    }
    Bool hoisted__Bool_2217 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2217;
    if (hoisted__Bool_2217) {
        Bool hoisted__Bool_2207 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2207;
        { Bool _ret_val = hoisted__Bool_2207;
                return _ret_val; }
    }
    Bool hoisted__Bool_2218 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2218;
    if (hoisted__Bool_2218) {
        Bool hoisted__Bool_2208 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2208;
        { Bool _ret_val = hoisted__Bool_2208;
                return _ret_val; }
    }
    Bool hoisted__Bool_2219 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2219;
    if (hoisted__Bool_2219) {
        Bool hoisted__Bool_2209 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2209;
        { Bool _ret_val = hoisted__Bool_2209;
                return _ret_val; }
    }
    Bool hoisted__Bool_2220 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2220;
    if (hoisted__Bool_2220) {
        Bool hoisted__Bool_2210 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2210;
        { Bool _ret_val = hoisted__Bool_2210;
                return _ret_val; }
    }
    Bool hoisted__Bool_2221 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        Bool hoisted__Bool_2211 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2211;
        { Bool _ret_val = hoisted__Bool_2211;
                return _ret_val; }
    }
    Bool hoisted__Bool_2222 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2222;
    if (hoisted__Bool_2222) {
        Bool hoisted__Bool_2212 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2212;
        { Bool _ret_val = hoisted__Bool_2212;
                return _ret_val; }
    }
    Bool hoisted__Bool_2223 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        Bool hoisted__Bool_2213 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2213;
        { Bool _ret_val = hoisted__Bool_2213;
                return _ret_val; }
    }
    Bool hoisted__Bool_2224 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2224;
    if (hoisted__Bool_2224) {
        Bool hoisted__Bool_2214 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2214;
        { Bool _ret_val = hoisted__Bool_2214;
                return _ret_val; }
    }
    Bool hoisted__Bool_2225 = 0;
    (void)hoisted__Bool_2225;
    return hoisted__Bool_2225;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2247 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2247;
    if (hoisted__Bool_2247) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2248 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2248;
    if (hoisted__Bool_2248) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2249 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2249;
    if (hoisted__Bool_2249) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2250 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2250;
    if (hoisted__Bool_2250) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2251 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2251;
    if (hoisted__Bool_2251) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2252 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2252;
    if (hoisted__Bool_2252) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2253 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2253;
    if (hoisted__Bool_2253) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2254 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2254;
    if (hoisted__Bool_2254) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2255 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2255;
    if (hoisted__Bool_2255) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2256 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2256;
    if (hoisted__Bool_2256) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2257 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2257;
    UNREACHABLE(&hoisted__Str_2257);
    Str_delete(&hoisted__Str_2257, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2258 = 4;
    (void)hoisted__U32_2258;
    return hoisted__U32_2258;
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
    Bool hoisted__Bool_2310 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2310;
    if (hoisted__Bool_2310) {
        Str *hoisted__Str_2300 = get_payload(self);
        (void)hoisted__Str_2300;
        (void)hoisted__Str_2300;
        Bool hoisted__Bool_2301 = 0;
        (void)hoisted__Bool_2301;
        Str_delete(hoisted__Str_2300, hoisted__Bool_2301);
    }
    Bool hoisted__Bool_2311 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        Str *hoisted__Str_2302 = get_payload(self);
        (void)hoisted__Str_2302;
        (void)hoisted__Str_2302;
        Bool hoisted__Bool_2303 = 0;
        (void)hoisted__Bool_2303;
        Str_delete(hoisted__Str_2302, hoisted__Bool_2303);
    }
    Bool hoisted__Bool_2312 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2312;
    if (hoisted__Bool_2312) {
        Str *hoisted__Str_2304 = get_payload(self);
        (void)hoisted__Str_2304;
        (void)hoisted__Str_2304;
        Bool hoisted__Bool_2305 = 0;
        (void)hoisted__Bool_2305;
        Str_delete(hoisted__Str_2304, hoisted__Bool_2305);
    }
    Bool hoisted__Bool_2313 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        Primitive *hoisted__Primitive_2306 = get_payload(self);
        (void)hoisted__Primitive_2306;
        (void)hoisted__Primitive_2306;
        Bool hoisted__Bool_2307 = 0;
        (void)hoisted__Bool_2307;
        Primitive_delete(hoisted__Primitive_2306, hoisted__Bool_2307);
    }
    Bool hoisted__Bool_2314 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2314;
    if (hoisted__Bool_2314) {
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
    Bool hoisted__Bool_2398 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2398;
    if (hoisted__Bool_2398) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2399 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2399;
    if (hoisted__Bool_2399) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2400 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2400;
    if (hoisted__Bool_2400) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2390 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2390;
        Type *hoisted__Type_2391 = Type_Struct(hoisted__Str_2390);
        (void)hoisted__Type_2391;
        { Type * _ret_val = hoisted__Type_2391;
                return _ret_val; }
    }
    Bool hoisted__Bool_2401 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2401;
    if (hoisted__Bool_2401) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2402 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2402;
    if (hoisted__Bool_2402) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2392 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2392;
        Type *hoisted__Type_2393 = Type_Enum(hoisted__Str_2392);
        (void)hoisted__Type_2393;
        { Type * _ret_val = hoisted__Type_2393;
                return _ret_val; }
    }
    Bool hoisted__Bool_2403 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2403;
    if (hoisted__Bool_2403) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2404 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2404;
    if (hoisted__Bool_2404) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2405 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2405;
    if (hoisted__Bool_2405) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2406 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2406;
    if (hoisted__Bool_2406) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2407 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2407;
    if (hoisted__Bool_2407) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2394 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2394;
        Type *hoisted__Type_2395 = Type_Custom(hoisted__Str_2394);
        (void)hoisted__Type_2395;
        { Type * _ret_val = hoisted__Type_2395;
                return _ret_val; }
    }
    Bool hoisted__Bool_2408 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2408;
    if (hoisted__Bool_2408) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2396 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2396;
        Type *hoisted__Type_2397 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2396; _oa; }));
        (void)hoisted__Type_2397;
        { Type * _ret_val = hoisted__Type_2397;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2409 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2409;
    Type *hoisted__Type_2410 = Type_FuncPtrSig(hoisted__Str_2409);
    (void)hoisted__Type_2410;
    return hoisted__Type_2410;
}

U32 Type_size(void) {
    U32 hoisted__U32_2411 = 24;
    (void)hoisted__U32_2411;
    return hoisted__U32_2411;
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
    Bool hoisted__Bool_2512 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2512;
    if (hoisted__Bool_2512) {
        Bool hoisted__Bool_2504 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2504;
        { Bool _ret_val = hoisted__Bool_2504;
                return _ret_val; }
    }
    Bool hoisted__Bool_2513 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2513;
    if (hoisted__Bool_2513) {
        Bool hoisted__Bool_2505 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2505;
        { Bool _ret_val = hoisted__Bool_2505;
                return _ret_val; }
    }
    Bool hoisted__Bool_2514 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2514;
    if (hoisted__Bool_2514) {
        Bool hoisted__Bool_2506 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2506;
        { Bool _ret_val = hoisted__Bool_2506;
                return _ret_val; }
    }
    Bool hoisted__Bool_2515 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2515;
    if (hoisted__Bool_2515) {
        Bool hoisted__Bool_2507 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2507;
        { Bool _ret_val = hoisted__Bool_2507;
                return _ret_val; }
    }
    Bool hoisted__Bool_2516 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2516;
    if (hoisted__Bool_2516) {
        Bool hoisted__Bool_2508 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2508;
        { Bool _ret_val = hoisted__Bool_2508;
                return _ret_val; }
    }
    Bool hoisted__Bool_2517 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2517;
    if (hoisted__Bool_2517) {
        Bool hoisted__Bool_2509 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2509;
        { Bool _ret_val = hoisted__Bool_2509;
                return _ret_val; }
    }
    Bool hoisted__Bool_2518 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2518;
    if (hoisted__Bool_2518) {
        Bool hoisted__Bool_2510 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2510;
        { Bool _ret_val = hoisted__Bool_2510;
                return _ret_val; }
    }
    Bool hoisted__Bool_2519 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2519;
    if (hoisted__Bool_2519) {
        Bool hoisted__Bool_2511 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2511;
        { Bool _ret_val = hoisted__Bool_2511;
                return _ret_val; }
    }
    Bool hoisted__Bool_2520 = 0;
    (void)hoisted__Bool_2520;
    return hoisted__Bool_2520;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2538 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2538;
    if (hoisted__Bool_2538) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2539 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2539;
    if (hoisted__Bool_2539) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2540 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2540;
    if (hoisted__Bool_2540) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2541 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2541;
    if (hoisted__Bool_2541) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2542 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2542;
    if (hoisted__Bool_2542) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2543 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2543;
    if (hoisted__Bool_2543) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2544 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2544;
    if (hoisted__Bool_2544) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2545 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2545;
    if (hoisted__Bool_2545) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    static Str hoisted__Str_2546 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2546;
    UNREACHABLE(&hoisted__Str_2546);
    Str_delete(&hoisted__Str_2546, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2547 = 4;
    (void)hoisted__U32_2547;
    return hoisted__U32_2547;
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
    Bool hoisted__Bool_2552 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2552;
    if (hoisted__Bool_2552) {
        Bool hoisted__Bool_2549 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2549;
        { Bool _ret_val = hoisted__Bool_2549;
                return _ret_val; }
    }
    Bool hoisted__Bool_2553 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2553;
    if (hoisted__Bool_2553) {
        Bool hoisted__Bool_2550 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2550;
        { Bool _ret_val = hoisted__Bool_2550;
                return _ret_val; }
    }
    Bool hoisted__Bool_2554 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2554;
    if (hoisted__Bool_2554) {
        Bool hoisted__Bool_2551 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2551;
        { Bool _ret_val = hoisted__Bool_2551;
                return _ret_val; }
    }
    Bool hoisted__Bool_2555 = 0;
    (void)hoisted__Bool_2555;
    return hoisted__Bool_2555;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2563 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2563;
    if (hoisted__Bool_2563) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2564 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2564;
    if (hoisted__Bool_2564) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2565 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2565;
    if (hoisted__Bool_2565) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2566 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2566;
    UNREACHABLE(&hoisted__Str_2566);
    Str_delete(&hoisted__Str_2566, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2567 = 4;
    (void)hoisted__U32_2567;
    return hoisted__U32_2567;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2569 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2569;
    Declaration *hoisted__Declaration_2570 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2570->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2570->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2570->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2570->is_mut = self->is_mut;
    hoisted__Declaration_2570->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2570->is_priv = self->is_priv;
    hoisted__Declaration_2570->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2570->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2570->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2570->default_value = hoisted__Expr_2569;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2570->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2570;
    return hoisted__Declaration_2570;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2571 = 0;
    (void)hoisted__Bool_2571;
    Str_delete(&self->name, hoisted__Bool_2571);
    Bool hoisted__Bool_2572 = 0;
    (void)hoisted__Bool_2572;
    Str_delete(&self->doc, hoisted__Bool_2572);
    Bool hoisted__Bool_2573 = 0;
    (void)hoisted__Bool_2573;
    Str_delete(&self->explicit_type, hoisted__Bool_2573);
    Bool hoisted__Bool_2574 = 0;
    (void)hoisted__Bool_2574;
    Bool_delete(&self->is_mut, hoisted__Bool_2574);
    Bool hoisted__Bool_2575 = 0;
    (void)hoisted__Bool_2575;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2575);
    Bool hoisted__Bool_2576 = 0;
    (void)hoisted__Bool_2576;
    Bool_delete(&self->is_priv, hoisted__Bool_2576);
    Bool hoisted__Bool_2577 = 0;
    (void)hoisted__Bool_2577;
    Bool_delete(&self->used, hoisted__Bool_2577);
    Bool hoisted__Bool_2578 = 0;
    (void)hoisted__Bool_2578;
    OwnType_delete(&self->own_type, hoisted__Bool_2578);
    Bool hoisted__Bool_2579 = 0;
    (void)hoisted__Bool_2579;
    Type_delete(&self->til_type, hoisted__Bool_2579);
    Bool hoisted__Bool_2580 = 1;
    (void)hoisted__Bool_2580;
    Expr_delete(self->default_value, hoisted__Bool_2580);
    Bool hoisted__Bool_2581 = 0;
    (void)hoisted__Bool_2581;
    Str_delete(&self->orig_name, hoisted__Bool_2581);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2582 = 104;
    (void)hoisted__U32_2582;
    return hoisted__U32_2582;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2584 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2584->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2584->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2584->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2584->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2584->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2584->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2584->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2584->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2584->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2584->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2584->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2584;
    return hoisted__FunctionDef_2584;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2585 = 0;
    (void)hoisted__Bool_2585;
    FuncType_delete(&self->func_type, hoisted__Bool_2585);
    Bool hoisted__Bool_2586 = 0;
    (void)hoisted__Bool_2586;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2586);
    Bool hoisted__Bool_2587 = 0;
    (void)hoisted__Bool_2587;
    Str_delete(&self->return_type, hoisted__Bool_2587);
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2588);
    Bool hoisted__Bool_2589 = 0;
    (void)hoisted__Bool_2589;
    I32_delete(&self->variadic_index, hoisted__Bool_2589);
    Bool hoisted__Bool_2590 = 0;
    (void)hoisted__Bool_2590;
    I32_delete(&self->kwargs_index, hoisted__Bool_2590);
    Bool hoisted__Bool_2591 = 0;
    (void)hoisted__Bool_2591;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2591);
    Bool hoisted__Bool_2592 = 0;
    (void)hoisted__Bool_2592;
    Bool_delete(&self->auto_generated, hoisted__Bool_2592);
    Bool hoisted__Bool_2593 = 0;
    (void)hoisted__Bool_2593;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2593);
    Bool hoisted__Bool_2594 = 0;
    (void)hoisted__Bool_2594;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2594);
    Bool hoisted__Bool_2595 = 0;
    (void)hoisted__Bool_2595;
    Str_delete(&self->closure_name, hoisted__Bool_2595);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2596 = 0;
    (void)hoisted__U32_2596;
    U64 hoisted__U64_2597 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2596); });
    (void)hoisted__U64_2597;
    return hoisted__U64_2597;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2598 = 104;
    (void)hoisted__U32_2598;
    return hoisted__U32_2598;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2601 = malloc(sizeof(FCallData));
    hoisted__FCallData_2601->is_splat = self->is_splat;
    hoisted__FCallData_2601->does_throw = self->does_throw;
    hoisted__FCallData_2601->is_bang = self->is_bang;
    hoisted__FCallData_2601->own_args = self->own_args;
    hoisted__FCallData_2601->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2601->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2601;
    return hoisted__FCallData_2601;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2602 = 0;
    (void)hoisted__Bool_2602;
    Bool_delete(&self->is_splat, hoisted__Bool_2602);
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Bool_delete(&self->does_throw, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    Bool_delete(&self->is_bang, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    U64_delete(&self->own_args, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    Bool_delete(&self->swap_replace, hoisted__Bool_2606);
    Bool hoisted__Bool_2607 = 0;
    (void)hoisted__Bool_2607;
    Type_delete(&self->til_type, hoisted__Bool_2607);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2608 = 0;
    (void)hoisted__U32_2608;
    U64 hoisted__U64_2609 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2608); });
    (void)hoisted__U64_2609;
    return hoisted__U64_2609;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2610 = 48;
    (void)hoisted__U32_2610;
    return hoisted__U32_2610;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2622 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2622->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2622->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2622;
    return hoisted__LiteralNumData_2622;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2623 = 0;
    (void)hoisted__Bool_2623;
    Str_delete(&self->text, hoisted__Bool_2623);
    Bool hoisted__Bool_2624 = 0;
    (void)hoisted__Bool_2624;
    Type_delete(&self->til_type, hoisted__Bool_2624);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2625 = 0;
    (void)hoisted__U32_2625;
    U64 hoisted__U64_2626 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2625); });
    (void)hoisted__U64_2626;
    return hoisted__U64_2626;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2627 = 40;
    (void)hoisted__U32_2627;
    return hoisted__U32_2627;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2637 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2637->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2637->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2637;
    return hoisted__IdentData_2637;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2638 = 0;
    (void)hoisted__Bool_2638;
    Str_delete(&self->name, hoisted__Bool_2638);
    Bool hoisted__Bool_2639 = 0;
    (void)hoisted__Bool_2639;
    Type_delete(&self->til_type, hoisted__Bool_2639);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2640 = 0;
    (void)hoisted__U32_2640;
    U64 hoisted__U64_2641 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2640); });
    (void)hoisted__U64_2641;
    return hoisted__U64_2641;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2642 = 40;
    (void)hoisted__U32_2642;
    return hoisted__U32_2642;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2648 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2648->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2648->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2648;
    return hoisted__FieldAccessData_2648;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2649 = 0;
    (void)hoisted__Bool_2649;
    Str_delete(&self->name, hoisted__Bool_2649);
    Bool hoisted__Bool_2650 = 0;
    (void)hoisted__Bool_2650;
    Type_delete(&self->til_type, hoisted__Bool_2650);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2651 = 0;
    (void)hoisted__U32_2651;
    U64 hoisted__U64_2652 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2651); });
    (void)hoisted__U64_2652;
    return hoisted__U64_2652;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2653 = 40;
    (void)hoisted__U32_2653;
    return hoisted__U32_2653;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2734 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2734->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2734->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2734->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2734->is_interface = self->is_interface;
    hoisted__StructDef_2734->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2734->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2734;
    return hoisted__StructDef_2734;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2735 = 0;
    (void)hoisted__Bool_2735;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2735);
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2736);
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Str_delete(&self->c_tag, hoisted__Bool_2737);
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Bool_delete(&self->is_interface, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2739);
    Bool hoisted__Bool_2740 = 0;
    (void)hoisted__Bool_2740;
    Str_delete(&self->implements_name, hoisted__Bool_2740);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2741 = 0;
    (void)hoisted__U32_2741;
    U64 hoisted__U64_2742 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2741); });
    (void)hoisted__U64_2742;
    return hoisted__U64_2742;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2743 = 72;
    (void)hoisted__U32_2743;
    return hoisted__U32_2743;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2748 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2748->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2748->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2748->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2748->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2748->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2748->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2748;
    return hoisted__EnumDef_2748;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2749 = 0;
    (void)hoisted__Bool_2749;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2749);
    Bool hoisted__Bool_2750 = 0;
    (void)hoisted__Bool_2750;
    Vec__Str_delete(&self->variants, hoisted__Bool_2750);
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2751);
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2752);
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Str_delete(&self->implements_name, hoisted__Bool_2753);
    Bool hoisted__Bool_2754 = 0;
    (void)hoisted__Bool_2754;
    Str_delete(&self->tag_type, hoisted__Bool_2754);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2755 = 0;
    (void)hoisted__U32_2755;
    U64 hoisted__U64_2756 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2755); });
    (void)hoisted__U64_2756;
    return hoisted__U64_2756;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2757 = 112;
    (void)hoisted__U32_2757;
    return hoisted__U32_2757;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2853 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2853->name = *_ca; free(_ca); }
    hoisted__AssignData_2853->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2853->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2853->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2853;
    return hoisted__AssignData_2853;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2854 = 0;
    (void)hoisted__Bool_2854;
    Str_delete(&self->name, hoisted__Bool_2854);
    Bool hoisted__Bool_2855 = 0;
    (void)hoisted__Bool_2855;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2855);
    Bool hoisted__Bool_2856 = 0;
    (void)hoisted__Bool_2856;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2856);
    Bool hoisted__Bool_2857 = 0;
    (void)hoisted__Bool_2857;
    Bool_delete(&self->swap_replace, hoisted__Bool_2857);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2858 = 0;
    (void)hoisted__U32_2858;
    U64 hoisted__U64_2859 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2858); });
    (void)hoisted__U64_2859;
    return hoisted__U64_2859;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2860 = 24;
    (void)hoisted__U32_2860;
    return hoisted__U32_2860;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2862 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2862->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2862->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2862;
    return hoisted__FieldAssignData_2862;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2863 = 0;
    (void)hoisted__Bool_2863;
    Str_delete(&self->name, hoisted__Bool_2863);
    Bool hoisted__Bool_2864 = 0;
    (void)hoisted__Bool_2864;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2864);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2865 = 0;
    (void)hoisted__U32_2865;
    U64 hoisted__U64_2866 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2865); });
    (void)hoisted__U64_2866;
    return hoisted__U64_2866;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2867 = 24;
    (void)hoisted__U32_2867;
    return hoisted__U32_2867;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2869 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2869->name = *_ca; free(_ca); }
    hoisted__ForInData_2869->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2869->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2869->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2869->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2869;
    return hoisted__ForInData_2869;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2870 = 0;
    (void)hoisted__Bool_2870;
    Str_delete(&self->name, hoisted__Bool_2870);
    Bool hoisted__Bool_2871 = 0;
    (void)hoisted__Bool_2871;
    Bool_delete(&self->is_mut, hoisted__Bool_2871);
    Bool hoisted__Bool_2872 = 0;
    (void)hoisted__Bool_2872;
    Type_delete(&self->til_type, hoisted__Bool_2872);
    Bool hoisted__Bool_2873 = 0;
    (void)hoisted__Bool_2873;
    Str_delete(&self->name2, hoisted__Bool_2873);
    Bool hoisted__Bool_2874 = 0;
    (void)hoisted__Bool_2874;
    Bool_delete(&self->is_mut2, hoisted__Bool_2874);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2875 = 0;
    (void)hoisted__U32_2875;
    U64 hoisted__U64_2876 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2875); });
    (void)hoisted__U64_2876;
    return hoisted__U64_2876;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2877 = 72;
    (void)hoisted__U32_2877;
    return hoisted__U32_2877;
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
    Bool hoisted__Bool_2907 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2907;
    if (hoisted__Bool_2907) {
        Str *hoisted__Str_2901 = get_payload(self);
        (void)hoisted__Str_2901;
        (void)hoisted__Str_2901;
        Bool hoisted__Bool_2902 = 0;
        (void)hoisted__Bool_2902;
        Str_delete(hoisted__Str_2901, hoisted__Bool_2902);
    }
    Bool hoisted__Bool_2908 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2908;
    if (hoisted__Bool_2908) {
        LiteralNumData *hoisted__LiteralNumData_2903 = get_payload(self);
        (void)hoisted__LiteralNumData_2903;
        (void)hoisted__LiteralNumData_2903;
        Bool hoisted__Bool_2904 = 0;
        (void)hoisted__Bool_2904;
        LiteralNumData_delete(hoisted__LiteralNumData_2903, hoisted__Bool_2904);
    }
    Bool hoisted__Bool_2909 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2909;
    if (hoisted__Bool_2909) {
        Bool *hoisted__Bool_2905 = get_payload(self);
        (void)hoisted__Bool_2905;
        (void)hoisted__Bool_2905;
        Bool hoisted__Bool_2906 = 0;
        (void)hoisted__Bool_2906;
        Bool_delete(hoisted__Bool_2905, hoisted__Bool_2906);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2958 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2958;
    if (hoisted__Bool_2958) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2953 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2953;
        Literal *hoisted__Literal_2954 = Literal_Str(hoisted__Str_2953);
        (void)hoisted__Literal_2954;
        { Literal * _ret_val = hoisted__Literal_2954;
                return _ret_val; }
    }
    Bool hoisted__Bool_2959 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2959;
    if (hoisted__Bool_2959) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2955 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2955;
        Literal *hoisted__Literal_2956 = Literal_Num(hoisted__LiteralNumData_2955);
        (void)hoisted__Literal_2956;
        { Literal * _ret_val = hoisted__Literal_2956;
                return _ret_val; }
    }
    Bool hoisted__Bool_2960 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2960;
    if (hoisted__Bool_2960) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2957 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2957;
        { Literal * _ret_val = hoisted__Literal_2957;
                return _ret_val; }
    }
    Bool hoisted__Bool_2961 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2961;
    if (hoisted__Bool_2961) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2962 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2962;
    if (hoisted__Bool_2962) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2963 = 48;
    (void)hoisted__U32_2963;
    return hoisted__U32_2963;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2966 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2966->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2966->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2966;
    return hoisted__MatchData_2966;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2967 = 0;
    (void)hoisted__Bool_2967;
    Type_delete(&self->til_type, hoisted__Bool_2967);
    Bool hoisted__Bool_2968 = 0;
    (void)hoisted__Bool_2968;
    Str_delete(&self->result_temp, hoisted__Bool_2968);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2969 = 0;
    (void)hoisted__U32_2969;
    U64 hoisted__U64_2970 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2969); });
    (void)hoisted__U64_2970;
    return hoisted__U64_2970;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2971 = 40;
    (void)hoisted__U32_2971;
    return hoisted__U32_2971;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2976 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2976->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2976;
    return hoisted__CaptureBlockData_2976;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2977 = 0;
    (void)hoisted__Bool_2977;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2977);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2978 = 0;
    (void)hoisted__U32_2978;
    U64 hoisted__U64_2979 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2978); });
    (void)hoisted__U64_2979;
    return hoisted__U64_2979;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2980 = 16;
    (void)hoisted__U32_2980;
    return hoisted__U32_2980;
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
    Bool hoisted__Bool_3159 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3159;
    if (hoisted__Bool_3159) {
        Literal *hoisted__Literal_3131 = get_payload(self);
        (void)hoisted__Literal_3131;
        (void)hoisted__Literal_3131;
        Bool hoisted__Bool_3132 = 0;
        (void)hoisted__Bool_3132;
        Literal_delete(hoisted__Literal_3131, hoisted__Bool_3132);
    }
    Bool hoisted__Bool_3160 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3160;
    if (hoisted__Bool_3160) {
        IdentData *hoisted__IdentData_3133 = get_payload(self);
        (void)hoisted__IdentData_3133;
        (void)hoisted__IdentData_3133;
        Bool hoisted__Bool_3134 = 0;
        (void)hoisted__Bool_3134;
        IdentData_delete(hoisted__IdentData_3133, hoisted__Bool_3134);
    }
    Bool hoisted__Bool_3161 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3161;
    if (hoisted__Bool_3161) {
        Declaration *hoisted__Declaration_3135 = get_payload(self);
        (void)hoisted__Declaration_3135;
        (void)hoisted__Declaration_3135;
        Bool hoisted__Bool_3136 = 0;
        (void)hoisted__Bool_3136;
        Declaration_delete(hoisted__Declaration_3135, hoisted__Bool_3136);
    }
    Bool hoisted__Bool_3162 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3162;
    if (hoisted__Bool_3162) {
        AssignData *hoisted__AssignData_3137 = get_payload(self);
        (void)hoisted__AssignData_3137;
        (void)hoisted__AssignData_3137;
        Bool hoisted__Bool_3138 = 0;
        (void)hoisted__Bool_3138;
        AssignData_delete(hoisted__AssignData_3137, hoisted__Bool_3138);
    }
    Bool hoisted__Bool_3163 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3163;
    if (hoisted__Bool_3163) {
        FCallData *hoisted__FCallData_3139 = get_payload(self);
        (void)hoisted__FCallData_3139;
        (void)hoisted__FCallData_3139;
        Bool hoisted__Bool_3140 = 0;
        (void)hoisted__Bool_3140;
        FCallData_delete(hoisted__FCallData_3139, hoisted__Bool_3140);
    }
    Bool hoisted__Bool_3164 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3164;
    if (hoisted__Bool_3164) {
        FunctionDef *hoisted__FunctionDef_3141 = get_payload(self);
        (void)hoisted__FunctionDef_3141;
        (void)hoisted__FunctionDef_3141;
        Bool hoisted__Bool_3142 = 0;
        (void)hoisted__Bool_3142;
        FunctionDef_delete(hoisted__FunctionDef_3141, hoisted__Bool_3142);
    }
    Bool hoisted__Bool_3165 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3165;
    if (hoisted__Bool_3165) {
        StructDef *hoisted__StructDef_3143 = get_payload(self);
        (void)hoisted__StructDef_3143;
        (void)hoisted__StructDef_3143;
        Bool hoisted__Bool_3144 = 0;
        (void)hoisted__Bool_3144;
        StructDef_delete(hoisted__StructDef_3143, hoisted__Bool_3144);
    }
    Bool hoisted__Bool_3166 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3166;
    if (hoisted__Bool_3166) {
        EnumDef *hoisted__EnumDef_3145 = get_payload(self);
        (void)hoisted__EnumDef_3145;
        (void)hoisted__EnumDef_3145;
        Bool hoisted__Bool_3146 = 0;
        (void)hoisted__Bool_3146;
        EnumDef_delete(hoisted__EnumDef_3145, hoisted__Bool_3146);
    }
    Bool hoisted__Bool_3167 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3167;
    if (hoisted__Bool_3167) {
        FieldAccessData *hoisted__FieldAccessData_3147 = get_payload(self);
        (void)hoisted__FieldAccessData_3147;
        (void)hoisted__FieldAccessData_3147;
        Bool hoisted__Bool_3148 = 0;
        (void)hoisted__Bool_3148;
        FieldAccessData_delete(hoisted__FieldAccessData_3147, hoisted__Bool_3148);
    }
    Bool hoisted__Bool_3168 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3168;
    if (hoisted__Bool_3168) {
        FieldAssignData *hoisted__FieldAssignData_3149 = get_payload(self);
        (void)hoisted__FieldAssignData_3149;
        (void)hoisted__FieldAssignData_3149;
        Bool hoisted__Bool_3150 = 0;
        (void)hoisted__Bool_3150;
        FieldAssignData_delete(hoisted__FieldAssignData_3149, hoisted__Bool_3150);
    }
    Bool hoisted__Bool_3169 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3169;
    if (hoisted__Bool_3169) {
        ForInData *hoisted__ForInData_3151 = get_payload(self);
        (void)hoisted__ForInData_3151;
        (void)hoisted__ForInData_3151;
        Bool hoisted__Bool_3152 = 0;
        (void)hoisted__Bool_3152;
        ForInData_delete(hoisted__ForInData_3151, hoisted__Bool_3152);
    }
    Bool hoisted__Bool_3170 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3170;
    if (hoisted__Bool_3170) {
        Str *hoisted__Str_3153 = get_payload(self);
        (void)hoisted__Str_3153;
        (void)hoisted__Str_3153;
        Bool hoisted__Bool_3154 = 0;
        (void)hoisted__Bool_3154;
        Str_delete(hoisted__Str_3153, hoisted__Bool_3154);
    }
    Bool hoisted__Bool_3171 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3171;
    if (hoisted__Bool_3171) {
        MatchData *hoisted__MatchData_3155 = get_payload(self);
        (void)hoisted__MatchData_3155;
        (void)hoisted__MatchData_3155;
        Bool hoisted__Bool_3156 = 0;
        (void)hoisted__Bool_3156;
        MatchData_delete(hoisted__MatchData_3155, hoisted__Bool_3156);
    }
    Bool hoisted__Bool_3172 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3172;
    if (hoisted__Bool_3172) {
        CaptureBlockData *hoisted__CaptureBlockData_3157 = get_payload(self);
        (void)hoisted__CaptureBlockData_3157;
        (void)hoisted__CaptureBlockData_3157;
        Bool hoisted__Bool_3158 = 0;
        (void)hoisted__Bool_3158;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3157, hoisted__Bool_3158);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3396 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3396;
    if (hoisted__Bool_3396) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3397 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3397;
    if (hoisted__Bool_3397) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3368 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3368;
        NodeType *hoisted__NodeType_3369 = NodeType_Literal(hoisted__Literal_3368);
        (void)hoisted__NodeType_3369;
        { NodeType * _ret_val = hoisted__NodeType_3369;
                return _ret_val; }
    }
    Bool hoisted__Bool_3398 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3398;
    if (hoisted__Bool_3398) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3370 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3370;
        NodeType *hoisted__NodeType_3371 = NodeType_Ident(hoisted__IdentData_3370);
        (void)hoisted__NodeType_3371;
        { NodeType * _ret_val = hoisted__NodeType_3371;
                return _ret_val; }
    }
    Bool hoisted__Bool_3399 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3399;
    if (hoisted__Bool_3399) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3372 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3372;
        NodeType *hoisted__NodeType_3373 = NodeType_Decl(hoisted__Declaration_3372);
        (void)hoisted__NodeType_3373;
        { NodeType * _ret_val = hoisted__NodeType_3373;
                return _ret_val; }
    }
    Bool hoisted__Bool_3400 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3400;
    if (hoisted__Bool_3400) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3374 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3374;
        NodeType *hoisted__NodeType_3375 = NodeType_Assign(hoisted__AssignData_3374);
        (void)hoisted__NodeType_3375;
        { NodeType * _ret_val = hoisted__NodeType_3375;
                return _ret_val; }
    }
    Bool hoisted__Bool_3401 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3401;
    if (hoisted__Bool_3401) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3376 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3376;
        NodeType *hoisted__NodeType_3377 = NodeType_FCall(hoisted__FCallData_3376);
        (void)hoisted__NodeType_3377;
        { NodeType * _ret_val = hoisted__NodeType_3377;
                return _ret_val; }
    }
    Bool hoisted__Bool_3402 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3402;
    if (hoisted__Bool_3402) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3378 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3378;
        NodeType *hoisted__NodeType_3379 = NodeType_FuncDef(hoisted__FunctionDef_3378);
        (void)hoisted__NodeType_3379;
        { NodeType * _ret_val = hoisted__NodeType_3379;
                return _ret_val; }
    }
    Bool hoisted__Bool_3403 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3403;
    if (hoisted__Bool_3403) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3380 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3380;
        NodeType *hoisted__NodeType_3381 = NodeType_StructDef(hoisted__StructDef_3380);
        (void)hoisted__NodeType_3381;
        { NodeType * _ret_val = hoisted__NodeType_3381;
                return _ret_val; }
    }
    Bool hoisted__Bool_3404 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3404;
    if (hoisted__Bool_3404) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3382 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3382;
        NodeType *hoisted__NodeType_3383 = NodeType_EnumDef(hoisted__EnumDef_3382);
        (void)hoisted__NodeType_3383;
        { NodeType * _ret_val = hoisted__NodeType_3383;
                return _ret_val; }
    }
    Bool hoisted__Bool_3405 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3405;
    if (hoisted__Bool_3405) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3384 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3384;
        NodeType *hoisted__NodeType_3385 = NodeType_FieldAccess(hoisted__FieldAccessData_3384);
        (void)hoisted__NodeType_3385;
        { NodeType * _ret_val = hoisted__NodeType_3385;
                return _ret_val; }
    }
    Bool hoisted__Bool_3406 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3406;
    if (hoisted__Bool_3406) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3386 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3386;
        NodeType *hoisted__NodeType_3387 = NodeType_FieldAssign(hoisted__FieldAssignData_3386);
        (void)hoisted__NodeType_3387;
        { NodeType * _ret_val = hoisted__NodeType_3387;
                return _ret_val; }
    }
    Bool hoisted__Bool_3407 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3407;
    if (hoisted__Bool_3407) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3408 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3408;
    if (hoisted__Bool_3408) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3409 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3409;
    if (hoisted__Bool_3409) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3410 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3410;
    if (hoisted__Bool_3410) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3388 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3388;
        NodeType *hoisted__NodeType_3389 = NodeType_ForIn(hoisted__ForInData_3388);
        (void)hoisted__NodeType_3389;
        { NodeType * _ret_val = hoisted__NodeType_3389;
                return _ret_val; }
    }
    Bool hoisted__Bool_3411 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3411;
    if (hoisted__Bool_3411) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3390 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3390;
        NodeType *hoisted__NodeType_3391 = NodeType_NamedArg(hoisted__Str_3390);
        (void)hoisted__NodeType_3391;
        { NodeType * _ret_val = hoisted__NodeType_3391;
                return _ret_val; }
    }
    Bool hoisted__Bool_3412 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3412;
    if (hoisted__Bool_3412) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3413 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3413;
    if (hoisted__Bool_3413) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3414 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3414;
    if (hoisted__Bool_3414) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3415 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3415;
    if (hoisted__Bool_3415) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3392 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3392;
        NodeType *hoisted__NodeType_3393 = NodeType_Match(hoisted__MatchData_3392);
        (void)hoisted__NodeType_3393;
        { NodeType * _ret_val = hoisted__NodeType_3393;
                return _ret_val; }
    }
    Bool hoisted__Bool_3416 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3417 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3417;
    if (hoisted__Bool_3417) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3418 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3419 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3419;
    if (hoisted__Bool_3419) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3420 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3421 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3421;
    if (hoisted__Bool_3421) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3394 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3394;
        NodeType *hoisted__NodeType_3395 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3394);
        (void)hoisted__NodeType_3395;
        { NodeType * _ret_val = hoisted__NodeType_3395;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3422 = 120;
    (void)hoisted__U32_3422;
    return hoisted__U32_3422;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3423 = is_null(self);
    (void)hoisted__Bool_3423;
    if (hoisted__Bool_3423) {
        return;
    }
    Bool hoisted__Bool_3424 = 0;
    (void)hoisted__Bool_3424;
    NodeType_delete(&self->node_type, hoisted__Bool_3424);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3474 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3474->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3474->children = *_ca; free(_ca); }
    hoisted__Expr_3474->line = line;
    hoisted__Expr_3474->col = col;
    (void)hoisted__Expr_3474;
    return hoisted__Expr_3474;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3483 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3483->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3483->children = *_ca; free(_ca); }
    hoisted__Expr_3483->line = self->line;
    hoisted__Expr_3483->col = self->col;
    (void)hoisted__Expr_3483;
    return hoisted__Expr_3483;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3484 = 0;
    (void)hoisted__U32_3484;
    U64 hoisted__U64_3485 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3484); });
    (void)hoisted__U64_3485;
    return hoisted__U64_3485;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3486 = 144;
    (void)hoisted__U32_3486;
    return hoisted__U32_3486;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4383 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4383->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4383->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4383;
    return hoisted__Map__I64_Str_4383;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4496 = 0;
    (void)hoisted__Bool_4496;
    Vec__I64_delete(&self->keys, hoisted__Bool_4496);
    Bool hoisted__Bool_4497 = 0;
    (void)hoisted__Bool_4497;
    Vec__Str_delete(&self->values, hoisted__Bool_4497);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4498 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4498->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4498->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4498;
    return hoisted__Map__I64_Str_4498;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4499 = 0;
    (void)hoisted__U32_4499;
    U64 hoisted__U64_4500 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4499); });
    (void)hoisted__U64_4500;
    return hoisted__U64_4500;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4501 = 32;
    (void)hoisted__U32_4501;
    return hoisted__U32_4501;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4502 = 1;
    (void)hoisted__U32_4502;
    U64 hoisted__U64_4503 = (U64)(hoisted__U32_4502);
    (void)hoisted__U64_4503;
    void * hoisted__v_4504 = malloc(hoisted__U64_4503);
    (void)hoisted__v_4504;
    U32 hoisted__U32_4505 = 0;
    (void)hoisted__U32_4505;
    I64 hoisted__I64_4506 = 1;
    (void)hoisted__I64_4506;
    Vec__Bool *hoisted__Vec__Bool_4507 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4507->data = hoisted__v_4504;
    hoisted__Vec__Bool_4507->count = hoisted__U32_4505;
    hoisted__Vec__Bool_4507->cap = hoisted__I64_4506;
    (void)hoisted__Vec__Bool_4507;
    return hoisted__Vec__Bool_4507;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4508 = self->count;
        (void)_re_U32_4508;
        U32 _rc_U32_4508 = 0;
        (void)_rc_U32_4508;
        Bool hoisted__Bool_4521 = U32_lte(_rc_U32_4508, _re_U32_4508);
        (void)hoisted__Bool_4521;
        if (hoisted__Bool_4521) {
            while (1) {
                Bool _wcond_Bool_4509 = U32_lt(_rc_U32_4508, _re_U32_4508);
                (void)_wcond_Bool_4509;
                if (_wcond_Bool_4509) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4508);
                U32_inc(&_rc_U32_4508);
                U32 hoisted__U32_4510 = 1;
                (void)hoisted__U32_4510;
                U32 hoisted__U32_4511 = U32_mul(i, hoisted__U32_4510);
                (void)hoisted__U32_4511;
                U64 hoisted__U64_4512 = (U64)(hoisted__U32_4511);
                (void)hoisted__U64_4512;
                Bool *hoisted__Bool_4513 = ptr_add(self->data, hoisted__U64_4512);
                (void)hoisted__Bool_4513;
                (void)hoisted__Bool_4513;
                Bool hoisted__Bool_4514 = 0;
                (void)hoisted__Bool_4514;
                Bool_delete(hoisted__Bool_4513, hoisted__Bool_4514);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4515 = U32_gt(_rc_U32_4508, _re_U32_4508);
                (void)_wcond_Bool_4515;
                if (_wcond_Bool_4515) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4508);
                U32_dec(&_rc_U32_4508);
                U32 hoisted__U32_4516 = 1;
                (void)hoisted__U32_4516;
                U32 hoisted__U32_4517 = U32_mul(i, hoisted__U32_4516);
                (void)hoisted__U32_4517;
                U64 hoisted__U64_4518 = (U64)(hoisted__U32_4517);
                (void)hoisted__U64_4518;
                Bool *hoisted__Bool_4519 = ptr_add(self->data, hoisted__U64_4518);
                (void)hoisted__Bool_4519;
                (void)hoisted__Bool_4519;
                Bool hoisted__Bool_4520 = 0;
                (void)hoisted__Bool_4520;
                Bool_delete(hoisted__Bool_4519, hoisted__Bool_4520);
            }
        }
    }
    U32 hoisted__U32_4522 = 0;
    (void)hoisted__U32_4522;
    self->count = hoisted__U32_4522;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4792 = 1;
    (void)hoisted__U32_4792;
    U32 hoisted__U32_4793 = U32_mul(self->cap, hoisted__U32_4792);
    (void)hoisted__U32_4793;
    U64 hoisted__U64_4794 = (U64)(hoisted__U32_4793);
    (void)hoisted__U64_4794;
    void * new_data = malloc(hoisted__U64_4794);
    {
        U32 _re_U32_4764 = self->count;
        (void)_re_U32_4764;
        U32 _rc_U32_4764 = 0;
        (void)_rc_U32_4764;
        Bool hoisted__Bool_4791 = U32_lte(_rc_U32_4764, _re_U32_4764);
        (void)hoisted__Bool_4791;
        if (hoisted__Bool_4791) {
            while (1) {
                Bool _wcond_Bool_4765 = U32_lt(_rc_U32_4764, _re_U32_4764);
                (void)_wcond_Bool_4765;
                if (_wcond_Bool_4765) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4764);
                U32_inc(&_rc_U32_4764);
                U32 hoisted__U32_4766 = 1;
                (void)hoisted__U32_4766;
                U32 hoisted__U32_4767 = U32_mul(i, hoisted__U32_4766);
                (void)hoisted__U32_4767;
                U64 hoisted__U64_4768 = (U64)(hoisted__U32_4767);
                (void)hoisted__U64_4768;
                Bool *src = ptr_add(self->data, hoisted__U64_4768);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4769 = 1;
                (void)hoisted__U32_4769;
                U32 hoisted__U32_4770 = U32_mul(i, hoisted__U32_4769);
                (void)hoisted__U32_4770;
                U64 hoisted__U64_4771 = (U64)(hoisted__U32_4770);
                (void)hoisted__U64_4771;
                U32 hoisted__U32_4772 = 1;
                (void)hoisted__U32_4772;
                void *hoisted__v_4773 = ptr_add(new_data, hoisted__U64_4771);
                (void)hoisted__v_4773;
                (void)hoisted__v_4773;
                U64 hoisted__U64_4774 = (U64)(hoisted__U32_4772);
                (void)hoisted__U64_4774;
                memcpy(hoisted__v_4773, &cloned, hoisted__U64_4774);
                U32 hoisted__U32_4775 = 1;
                (void)hoisted__U32_4775;
                I32 hoisted__I32_4776 = 0;
                (void)hoisted__I32_4776;
                U64 hoisted__U64_4777 = (U64)(hoisted__U32_4775);
                (void)hoisted__U64_4777;
                memset(&cloned, hoisted__I32_4776, hoisted__U64_4777);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4778 = U32_gt(_rc_U32_4764, _re_U32_4764);
                (void)_wcond_Bool_4778;
                if (_wcond_Bool_4778) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4764);
                U32_dec(&_rc_U32_4764);
                U32 hoisted__U32_4779 = 1;
                (void)hoisted__U32_4779;
                U32 hoisted__U32_4780 = U32_mul(i, hoisted__U32_4779);
                (void)hoisted__U32_4780;
                U64 hoisted__U64_4781 = (U64)(hoisted__U32_4780);
                (void)hoisted__U64_4781;
                Bool *src = ptr_add(self->data, hoisted__U64_4781);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4782 = 1;
                (void)hoisted__U32_4782;
                U32 hoisted__U32_4783 = U32_mul(i, hoisted__U32_4782);
                (void)hoisted__U32_4783;
                U64 hoisted__U64_4784 = (U64)(hoisted__U32_4783);
                (void)hoisted__U64_4784;
                U32 hoisted__U32_4785 = 1;
                (void)hoisted__U32_4785;
                void *hoisted__v_4786 = ptr_add(new_data, hoisted__U64_4784);
                (void)hoisted__v_4786;
                (void)hoisted__v_4786;
                U64 hoisted__U64_4787 = (U64)(hoisted__U32_4785);
                (void)hoisted__U64_4787;
                memcpy(hoisted__v_4786, &cloned, hoisted__U64_4787);
                U32 hoisted__U32_4788 = 1;
                (void)hoisted__U32_4788;
                I32 hoisted__I32_4789 = 0;
                (void)hoisted__I32_4789;
                U64 hoisted__U64_4790 = (U64)(hoisted__U32_4788);
                (void)hoisted__U64_4790;
                memset(&cloned, hoisted__I32_4789, hoisted__U64_4790);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4795 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4795->data = new_data;
    hoisted__Vec__Bool_4795->count = self->count;
    hoisted__Vec__Bool_4795->cap = self->cap;
    (void)hoisted__Vec__Bool_4795;
    return hoisted__Vec__Bool_4795;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4796 = 16;
    (void)hoisted__U32_4796;
    return hoisted__U32_4796;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5092 = 104;
    (void)hoisted__U32_5092;
    U64 hoisted__U64_5093 = (U64)(hoisted__U32_5092);
    (void)hoisted__U64_5093;
    void * hoisted__v_5094 = malloc(hoisted__U64_5093);
    (void)hoisted__v_5094;
    U32 hoisted__U32_5095 = 0;
    (void)hoisted__U32_5095;
    I64 hoisted__I64_5096 = 1;
    (void)hoisted__I64_5096;
    Vec__Declaration *hoisted__Vec__Declaration_5097 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5097->data = hoisted__v_5094;
    hoisted__Vec__Declaration_5097->count = hoisted__U32_5095;
    hoisted__Vec__Declaration_5097->cap = hoisted__I64_5096;
    (void)hoisted__Vec__Declaration_5097;
    return hoisted__Vec__Declaration_5097;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5098 = self->count;
        (void)_re_U32_5098;
        U32 _rc_U32_5098 = 0;
        (void)_rc_U32_5098;
        Bool hoisted__Bool_5111 = U32_lte(_rc_U32_5098, _re_U32_5098);
        (void)hoisted__Bool_5111;
        if (hoisted__Bool_5111) {
            while (1) {
                Bool _wcond_Bool_5099 = U32_lt(_rc_U32_5098, _re_U32_5098);
                (void)_wcond_Bool_5099;
                if (_wcond_Bool_5099) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5098);
                U32_inc(&_rc_U32_5098);
                U32 hoisted__U32_5100 = 104;
                (void)hoisted__U32_5100;
                U32 hoisted__U32_5101 = U32_mul(i, hoisted__U32_5100);
                (void)hoisted__U32_5101;
                U64 hoisted__U64_5102 = (U64)(hoisted__U32_5101);
                (void)hoisted__U64_5102;
                Declaration *hoisted__Declaration_5103 = ptr_add(self->data, hoisted__U64_5102);
                (void)hoisted__Declaration_5103;
                (void)hoisted__Declaration_5103;
                Bool hoisted__Bool_5104 = 0;
                (void)hoisted__Bool_5104;
                Declaration_delete(hoisted__Declaration_5103, hoisted__Bool_5104);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5105 = U32_gt(_rc_U32_5098, _re_U32_5098);
                (void)_wcond_Bool_5105;
                if (_wcond_Bool_5105) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5098);
                U32_dec(&_rc_U32_5098);
                U32 hoisted__U32_5106 = 104;
                (void)hoisted__U32_5106;
                U32 hoisted__U32_5107 = U32_mul(i, hoisted__U32_5106);
                (void)hoisted__U32_5107;
                U64 hoisted__U64_5108 = (U64)(hoisted__U32_5107);
                (void)hoisted__U64_5108;
                Declaration *hoisted__Declaration_5109 = ptr_add(self->data, hoisted__U64_5108);
                (void)hoisted__Declaration_5109;
                (void)hoisted__Declaration_5109;
                Bool hoisted__Bool_5110 = 0;
                (void)hoisted__Bool_5110;
                Declaration_delete(hoisted__Declaration_5109, hoisted__Bool_5110);
            }
        }
    }
    U32 hoisted__U32_5112 = 0;
    (void)hoisted__U32_5112;
    self->count = hoisted__U32_5112;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5382 = 104;
    (void)hoisted__U32_5382;
    U32 hoisted__U32_5383 = U32_mul(self->cap, hoisted__U32_5382);
    (void)hoisted__U32_5383;
    U64 hoisted__U64_5384 = (U64)(hoisted__U32_5383);
    (void)hoisted__U64_5384;
    void * new_data = malloc(hoisted__U64_5384);
    {
        U32 _re_U32_5354 = self->count;
        (void)_re_U32_5354;
        U32 _rc_U32_5354 = 0;
        (void)_rc_U32_5354;
        Bool hoisted__Bool_5381 = U32_lte(_rc_U32_5354, _re_U32_5354);
        (void)hoisted__Bool_5381;
        if (hoisted__Bool_5381) {
            while (1) {
                Bool _wcond_Bool_5355 = U32_lt(_rc_U32_5354, _re_U32_5354);
                (void)_wcond_Bool_5355;
                if (_wcond_Bool_5355) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5354);
                U32_inc(&_rc_U32_5354);
                U32 hoisted__U32_5356 = 104;
                (void)hoisted__U32_5356;
                U32 hoisted__U32_5357 = U32_mul(i, hoisted__U32_5356);
                (void)hoisted__U32_5357;
                U64 hoisted__U64_5358 = (U64)(hoisted__U32_5357);
                (void)hoisted__U64_5358;
                Declaration *src = ptr_add(self->data, hoisted__U64_5358);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5359 = 104;
                (void)hoisted__U32_5359;
                U32 hoisted__U32_5360 = U32_mul(i, hoisted__U32_5359);
                (void)hoisted__U32_5360;
                U64 hoisted__U64_5361 = (U64)(hoisted__U32_5360);
                (void)hoisted__U64_5361;
                U32 hoisted__U32_5362 = 104;
                (void)hoisted__U32_5362;
                void *hoisted__v_5363 = ptr_add(new_data, hoisted__U64_5361);
                (void)hoisted__v_5363;
                (void)hoisted__v_5363;
                U64 hoisted__U64_5364 = (U64)(hoisted__U32_5362);
                (void)hoisted__U64_5364;
                memcpy(hoisted__v_5363, cloned, hoisted__U64_5364);
                U32 hoisted__U32_5365 = 104;
                (void)hoisted__U32_5365;
                I32 hoisted__I32_5366 = 0;
                (void)hoisted__I32_5366;
                U64 hoisted__U64_5367 = (U64)(hoisted__U32_5365);
                (void)hoisted__U64_5367;
                memset(cloned, hoisted__I32_5366, hoisted__U64_5367);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5368 = U32_gt(_rc_U32_5354, _re_U32_5354);
                (void)_wcond_Bool_5368;
                if (_wcond_Bool_5368) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5354);
                U32_dec(&_rc_U32_5354);
                U32 hoisted__U32_5369 = 104;
                (void)hoisted__U32_5369;
                U32 hoisted__U32_5370 = U32_mul(i, hoisted__U32_5369);
                (void)hoisted__U32_5370;
                U64 hoisted__U64_5371 = (U64)(hoisted__U32_5370);
                (void)hoisted__U64_5371;
                Declaration *src = ptr_add(self->data, hoisted__U64_5371);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5372 = 104;
                (void)hoisted__U32_5372;
                U32 hoisted__U32_5373 = U32_mul(i, hoisted__U32_5372);
                (void)hoisted__U32_5373;
                U64 hoisted__U64_5374 = (U64)(hoisted__U32_5373);
                (void)hoisted__U64_5374;
                U32 hoisted__U32_5375 = 104;
                (void)hoisted__U32_5375;
                void *hoisted__v_5376 = ptr_add(new_data, hoisted__U64_5374);
                (void)hoisted__v_5376;
                (void)hoisted__v_5376;
                U64 hoisted__U64_5377 = (U64)(hoisted__U32_5375);
                (void)hoisted__U64_5377;
                memcpy(hoisted__v_5376, cloned, hoisted__U64_5377);
                U32 hoisted__U32_5378 = 104;
                (void)hoisted__U32_5378;
                I32 hoisted__I32_5379 = 0;
                (void)hoisted__I32_5379;
                U64 hoisted__U64_5380 = (U64)(hoisted__U32_5378);
                (void)hoisted__U64_5380;
                memset(cloned, hoisted__I32_5379, hoisted__U64_5380);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5385 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5385->data = new_data;
    hoisted__Vec__Declaration_5385->count = self->count;
    hoisted__Vec__Declaration_5385->cap = self->cap;
    (void)hoisted__Vec__Declaration_5385;
    return hoisted__Vec__Declaration_5385;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5386 = 16;
    (void)hoisted__U32_5386;
    return hoisted__U32_5386;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5387 = 144;
    (void)hoisted__U32_5387;
    U64 hoisted__U64_5388 = (U64)(hoisted__U32_5387);
    (void)hoisted__U64_5388;
    void * hoisted__v_5389 = malloc(hoisted__U64_5388);
    (void)hoisted__v_5389;
    U32 hoisted__U32_5390 = 0;
    (void)hoisted__U32_5390;
    I64 hoisted__I64_5391 = 1;
    (void)hoisted__I64_5391;
    Vec__Expr *hoisted__Vec__Expr_5392 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5392->data = hoisted__v_5389;
    hoisted__Vec__Expr_5392->count = hoisted__U32_5390;
    hoisted__Vec__Expr_5392->cap = hoisted__I64_5391;
    (void)hoisted__Vec__Expr_5392;
    return hoisted__Vec__Expr_5392;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5393 = self->count;
        (void)_re_U32_5393;
        U32 _rc_U32_5393 = 0;
        (void)_rc_U32_5393;
        Bool hoisted__Bool_5406 = U32_lte(_rc_U32_5393, _re_U32_5393);
        (void)hoisted__Bool_5406;
        if (hoisted__Bool_5406) {
            while (1) {
                Bool _wcond_Bool_5394 = U32_lt(_rc_U32_5393, _re_U32_5393);
                (void)_wcond_Bool_5394;
                if (_wcond_Bool_5394) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5393);
                U32_inc(&_rc_U32_5393);
                U32 hoisted__U32_5395 = 144;
                (void)hoisted__U32_5395;
                U32 hoisted__U32_5396 = U32_mul(i, hoisted__U32_5395);
                (void)hoisted__U32_5396;
                U64 hoisted__U64_5397 = (U64)(hoisted__U32_5396);
                (void)hoisted__U64_5397;
                Expr *hoisted__Expr_5398 = ptr_add(self->data, hoisted__U64_5397);
                (void)hoisted__Expr_5398;
                (void)hoisted__Expr_5398;
                Bool hoisted__Bool_5399 = 0;
                (void)hoisted__Bool_5399;
                Expr_delete(hoisted__Expr_5398, hoisted__Bool_5399);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5400 = U32_gt(_rc_U32_5393, _re_U32_5393);
                (void)_wcond_Bool_5400;
                if (_wcond_Bool_5400) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5393);
                U32_dec(&_rc_U32_5393);
                U32 hoisted__U32_5401 = 144;
                (void)hoisted__U32_5401;
                U32 hoisted__U32_5402 = U32_mul(i, hoisted__U32_5401);
                (void)hoisted__U32_5402;
                U64 hoisted__U64_5403 = (U64)(hoisted__U32_5402);
                (void)hoisted__U64_5403;
                Expr *hoisted__Expr_5404 = ptr_add(self->data, hoisted__U64_5403);
                (void)hoisted__Expr_5404;
                (void)hoisted__Expr_5404;
                Bool hoisted__Bool_5405 = 0;
                (void)hoisted__Bool_5405;
                Expr_delete(hoisted__Expr_5404, hoisted__Bool_5405);
            }
        }
    }
    U32 hoisted__U32_5407 = 0;
    (void)hoisted__U32_5407;
    self->count = hoisted__U32_5407;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5677 = 144;
    (void)hoisted__U32_5677;
    U32 hoisted__U32_5678 = U32_mul(self->cap, hoisted__U32_5677);
    (void)hoisted__U32_5678;
    U64 hoisted__U64_5679 = (U64)(hoisted__U32_5678);
    (void)hoisted__U64_5679;
    void * new_data = malloc(hoisted__U64_5679);
    {
        U32 _re_U32_5649 = self->count;
        (void)_re_U32_5649;
        U32 _rc_U32_5649 = 0;
        (void)_rc_U32_5649;
        Bool hoisted__Bool_5676 = U32_lte(_rc_U32_5649, _re_U32_5649);
        (void)hoisted__Bool_5676;
        if (hoisted__Bool_5676) {
            while (1) {
                Bool _wcond_Bool_5650 = U32_lt(_rc_U32_5649, _re_U32_5649);
                (void)_wcond_Bool_5650;
                if (_wcond_Bool_5650) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5649);
                U32_inc(&_rc_U32_5649);
                U32 hoisted__U32_5651 = 144;
                (void)hoisted__U32_5651;
                U32 hoisted__U32_5652 = U32_mul(i, hoisted__U32_5651);
                (void)hoisted__U32_5652;
                U64 hoisted__U64_5653 = (U64)(hoisted__U32_5652);
                (void)hoisted__U64_5653;
                Expr *src = ptr_add(self->data, hoisted__U64_5653);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5654 = 144;
                (void)hoisted__U32_5654;
                U32 hoisted__U32_5655 = U32_mul(i, hoisted__U32_5654);
                (void)hoisted__U32_5655;
                U64 hoisted__U64_5656 = (U64)(hoisted__U32_5655);
                (void)hoisted__U64_5656;
                U32 hoisted__U32_5657 = 144;
                (void)hoisted__U32_5657;
                void *hoisted__v_5658 = ptr_add(new_data, hoisted__U64_5656);
                (void)hoisted__v_5658;
                (void)hoisted__v_5658;
                U64 hoisted__U64_5659 = (U64)(hoisted__U32_5657);
                (void)hoisted__U64_5659;
                memcpy(hoisted__v_5658, cloned, hoisted__U64_5659);
                U32 hoisted__U32_5660 = 144;
                (void)hoisted__U32_5660;
                I32 hoisted__I32_5661 = 0;
                (void)hoisted__I32_5661;
                U64 hoisted__U64_5662 = (U64)(hoisted__U32_5660);
                (void)hoisted__U64_5662;
                memset(cloned, hoisted__I32_5661, hoisted__U64_5662);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5663 = U32_gt(_rc_U32_5649, _re_U32_5649);
                (void)_wcond_Bool_5663;
                if (_wcond_Bool_5663) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5649);
                U32_dec(&_rc_U32_5649);
                U32 hoisted__U32_5664 = 144;
                (void)hoisted__U32_5664;
                U32 hoisted__U32_5665 = U32_mul(i, hoisted__U32_5664);
                (void)hoisted__U32_5665;
                U64 hoisted__U64_5666 = (U64)(hoisted__U32_5665);
                (void)hoisted__U64_5666;
                Expr *src = ptr_add(self->data, hoisted__U64_5666);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5667 = 144;
                (void)hoisted__U32_5667;
                U32 hoisted__U32_5668 = U32_mul(i, hoisted__U32_5667);
                (void)hoisted__U32_5668;
                U64 hoisted__U64_5669 = (U64)(hoisted__U32_5668);
                (void)hoisted__U64_5669;
                U32 hoisted__U32_5670 = 144;
                (void)hoisted__U32_5670;
                void *hoisted__v_5671 = ptr_add(new_data, hoisted__U64_5669);
                (void)hoisted__v_5671;
                (void)hoisted__v_5671;
                U64 hoisted__U64_5672 = (U64)(hoisted__U32_5670);
                (void)hoisted__U64_5672;
                memcpy(hoisted__v_5671, cloned, hoisted__U64_5672);
                U32 hoisted__U32_5673 = 144;
                (void)hoisted__U32_5673;
                I32 hoisted__I32_5674 = 0;
                (void)hoisted__I32_5674;
                U64 hoisted__U64_5675 = (U64)(hoisted__U32_5673);
                (void)hoisted__U64_5675;
                memset(cloned, hoisted__I32_5674, hoisted__U64_5675);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5680 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5680->data = new_data;
    hoisted__Vec__Expr_5680->count = self->count;
    hoisted__Vec__Expr_5680->cap = self->cap;
    (void)hoisted__Vec__Expr_5680;
    return hoisted__Vec__Expr_5680;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5681 = 16;
    (void)hoisted__U32_5681;
    return hoisted__U32_5681;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5682 = 8;
    (void)hoisted__U32_5682;
    U64 hoisted__U64_5683 = (U64)(hoisted__U32_5682);
    (void)hoisted__U64_5683;
    void * hoisted__v_5684 = malloc(hoisted__U64_5683);
    (void)hoisted__v_5684;
    U32 hoisted__U32_5685 = 0;
    (void)hoisted__U32_5685;
    I64 hoisted__I64_5686 = 1;
    (void)hoisted__I64_5686;
    Vec__I64 *hoisted__Vec__I64_5687 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5687->data = hoisted__v_5684;
    hoisted__Vec__I64_5687->count = hoisted__U32_5685;
    hoisted__Vec__I64_5687->cap = hoisted__I64_5686;
    (void)hoisted__Vec__I64_5687;
    return hoisted__Vec__I64_5687;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5688 = self->count;
        (void)_re_U32_5688;
        U32 _rc_U32_5688 = 0;
        (void)_rc_U32_5688;
        Bool hoisted__Bool_5701 = U32_lte(_rc_U32_5688, _re_U32_5688);
        (void)hoisted__Bool_5701;
        if (hoisted__Bool_5701) {
            while (1) {
                Bool _wcond_Bool_5689 = U32_lt(_rc_U32_5688, _re_U32_5688);
                (void)_wcond_Bool_5689;
                if (_wcond_Bool_5689) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5688);
                U32_inc(&_rc_U32_5688);
                U32 hoisted__U32_5690 = 8;
                (void)hoisted__U32_5690;
                U32 hoisted__U32_5691 = U32_mul(i, hoisted__U32_5690);
                (void)hoisted__U32_5691;
                U64 hoisted__U64_5692 = (U64)(hoisted__U32_5691);
                (void)hoisted__U64_5692;
                I64 *hoisted__I64_5693 = ptr_add(self->data, hoisted__U64_5692);
                (void)hoisted__I64_5693;
                (void)hoisted__I64_5693;
                Bool hoisted__Bool_5694 = 0;
                (void)hoisted__Bool_5694;
                I64_delete(hoisted__I64_5693, hoisted__Bool_5694);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5695 = U32_gt(_rc_U32_5688, _re_U32_5688);
                (void)_wcond_Bool_5695;
                if (_wcond_Bool_5695) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5688);
                U32_dec(&_rc_U32_5688);
                U32 hoisted__U32_5696 = 8;
                (void)hoisted__U32_5696;
                U32 hoisted__U32_5697 = U32_mul(i, hoisted__U32_5696);
                (void)hoisted__U32_5697;
                U64 hoisted__U64_5698 = (U64)(hoisted__U32_5697);
                (void)hoisted__U64_5698;
                I64 *hoisted__I64_5699 = ptr_add(self->data, hoisted__U64_5698);
                (void)hoisted__I64_5699;
                (void)hoisted__I64_5699;
                Bool hoisted__Bool_5700 = 0;
                (void)hoisted__Bool_5700;
                I64_delete(hoisted__I64_5699, hoisted__Bool_5700);
            }
        }
    }
    U32 hoisted__U32_5702 = 0;
    (void)hoisted__U32_5702;
    self->count = hoisted__U32_5702;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5972 = 8;
    (void)hoisted__U32_5972;
    U32 hoisted__U32_5973 = U32_mul(self->cap, hoisted__U32_5972);
    (void)hoisted__U32_5973;
    U64 hoisted__U64_5974 = (U64)(hoisted__U32_5973);
    (void)hoisted__U64_5974;
    void * new_data = malloc(hoisted__U64_5974);
    {
        U32 _re_U32_5944 = self->count;
        (void)_re_U32_5944;
        U32 _rc_U32_5944 = 0;
        (void)_rc_U32_5944;
        Bool hoisted__Bool_5971 = U32_lte(_rc_U32_5944, _re_U32_5944);
        (void)hoisted__Bool_5971;
        if (hoisted__Bool_5971) {
            while (1) {
                Bool _wcond_Bool_5945 = U32_lt(_rc_U32_5944, _re_U32_5944);
                (void)_wcond_Bool_5945;
                if (_wcond_Bool_5945) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5944);
                U32_inc(&_rc_U32_5944);
                U32 hoisted__U32_5946 = 8;
                (void)hoisted__U32_5946;
                U32 hoisted__U32_5947 = U32_mul(i, hoisted__U32_5946);
                (void)hoisted__U32_5947;
                U64 hoisted__U64_5948 = (U64)(hoisted__U32_5947);
                (void)hoisted__U64_5948;
                I64 *src = ptr_add(self->data, hoisted__U64_5948);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5949 = 8;
                (void)hoisted__U32_5949;
                U32 hoisted__U32_5950 = U32_mul(i, hoisted__U32_5949);
                (void)hoisted__U32_5950;
                U64 hoisted__U64_5951 = (U64)(hoisted__U32_5950);
                (void)hoisted__U64_5951;
                U32 hoisted__U32_5952 = 8;
                (void)hoisted__U32_5952;
                void *hoisted__v_5953 = ptr_add(new_data, hoisted__U64_5951);
                (void)hoisted__v_5953;
                (void)hoisted__v_5953;
                U64 hoisted__U64_5954 = (U64)(hoisted__U32_5952);
                (void)hoisted__U64_5954;
                memcpy(hoisted__v_5953, &cloned, hoisted__U64_5954);
                U32 hoisted__U32_5955 = 8;
                (void)hoisted__U32_5955;
                I32 hoisted__I32_5956 = 0;
                (void)hoisted__I32_5956;
                U64 hoisted__U64_5957 = (U64)(hoisted__U32_5955);
                (void)hoisted__U64_5957;
                memset(&cloned, hoisted__I32_5956, hoisted__U64_5957);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5958 = U32_gt(_rc_U32_5944, _re_U32_5944);
                (void)_wcond_Bool_5958;
                if (_wcond_Bool_5958) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5944);
                U32_dec(&_rc_U32_5944);
                U32 hoisted__U32_5959 = 8;
                (void)hoisted__U32_5959;
                U32 hoisted__U32_5960 = U32_mul(i, hoisted__U32_5959);
                (void)hoisted__U32_5960;
                U64 hoisted__U64_5961 = (U64)(hoisted__U32_5960);
                (void)hoisted__U64_5961;
                I64 *src = ptr_add(self->data, hoisted__U64_5961);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5962 = 8;
                (void)hoisted__U32_5962;
                U32 hoisted__U32_5963 = U32_mul(i, hoisted__U32_5962);
                (void)hoisted__U32_5963;
                U64 hoisted__U64_5964 = (U64)(hoisted__U32_5963);
                (void)hoisted__U64_5964;
                U32 hoisted__U32_5965 = 8;
                (void)hoisted__U32_5965;
                void *hoisted__v_5966 = ptr_add(new_data, hoisted__U64_5964);
                (void)hoisted__v_5966;
                (void)hoisted__v_5966;
                U64 hoisted__U64_5967 = (U64)(hoisted__U32_5965);
                (void)hoisted__U64_5967;
                memcpy(hoisted__v_5966, &cloned, hoisted__U64_5967);
                U32 hoisted__U32_5968 = 8;
                (void)hoisted__U32_5968;
                I32 hoisted__I32_5969 = 0;
                (void)hoisted__I32_5969;
                U64 hoisted__U64_5970 = (U64)(hoisted__U32_5968);
                (void)hoisted__U64_5970;
                memset(&cloned, hoisted__I32_5969, hoisted__U64_5970);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5975 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5975->data = new_data;
    hoisted__Vec__I64_5975->count = self->count;
    hoisted__Vec__I64_5975->cap = self->cap;
    (void)hoisted__Vec__I64_5975;
    return hoisted__Vec__I64_5975;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5976 = 16;
    (void)hoisted__U32_5976;
    return hoisted__U32_5976;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7077 = 3;
    (void)hoisted__U32_7077;
    Array__Str *_va_Array_200 = Array__Str_new(hoisted__U32_7077);
    (void)_va_Array_200;
    I64 _va_Array_200_ek = 0;
    (void)_va_Array_200_ek;
    OutOfBounds *_va_Array_200_eo = malloc(sizeof(OutOfBounds));
    _va_Array_200_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_200_eo;
    U32 hoisted__U32_7078 = 0;
    (void)hoisted__U32_7078;
    Str *hoisted__Str_7079 = Str_clone(loc);
    (void)hoisted__Str_7079;
    (void)hoisted__Str_7080;
    (void)hoisted__Str_7080;
    Array__Str_set(_va_Array_200, hoisted__U32_7078, hoisted__Str_7079, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7080);
    Str_delete(&hoisted__Str_7080, (Bool){0});
    U32 hoisted__U32_7081 = 1;
    (void)hoisted__U32_7081;
    (void)hoisted__Str_7082;
    (void)hoisted__Str_7082;
    (void)hoisted__Str_7083;
    (void)hoisted__Str_7083;
    Array__Str_set(_va_Array_200, hoisted__U32_7081, &hoisted__Str_7082, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7083);
    Str_delete(&hoisted__Str_7083, (Bool){0});
    Array__Str *hoisted__Array__Str_7084 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7084;
    U32 hoisted__U32_7085 = 2;
    (void)hoisted__U32_7085;
    Str *hoisted__Str_7086 = format(hoisted__Array__Str_7084);
    (void)hoisted__Str_7086;
    (void)hoisted__Str_7087;
    (void)hoisted__Str_7087;
    Array__Str_set(_va_Array_200, hoisted__U32_7085, hoisted__Str_7086, &_va_Array_200_ek, _va_Array_200_eo, &hoisted__Str_7087);
    OutOfBounds_delete(_va_Array_200_eo, 1);
    Str_delete(&hoisted__Str_7087, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_200);
    I64 hoisted__I64_7088 = 1;
    (void)hoisted__I64_7088;
    exit(hoisted__I64_7088);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7097 = 1;
    (void)hoisted__U32_7097;
    Array__Str *_va_Array_202 = Array__Str_new(hoisted__U32_7097);
    (void)_va_Array_202;
    I64 _va_Array_202_ek = 0;
    (void)_va_Array_202_ek;
    OutOfBounds *_va_Array_202_eo = malloc(sizeof(OutOfBounds));
    _va_Array_202_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_202_eo;
    U32 hoisted__U32_7098 = 0;
    (void)hoisted__U32_7098;
    (void)hoisted__Str_7099;
    (void)hoisted__Str_7099;
    (void)hoisted__Str_7100;
    (void)hoisted__Str_7100;
    Array__Str_set(_va_Array_202, hoisted__U32_7098, &hoisted__Str_7099, &_va_Array_202_ek, _va_Array_202_eo, &hoisted__Str_7100);
    OutOfBounds_delete(_va_Array_202_eo, 1);
    Str_delete(&hoisted__Str_7100, (Bool){0});
    panic(_va_Array_202, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7105 = not(cond);
    (void)hoisted__Bool_7105;
    if (hoisted__Bool_7105) {
        U32 hoisted__U32_7101 = 1;
        (void)hoisted__U32_7101;
        Array__Str *_va_Array_203 = Array__Str_new(hoisted__U32_7101);
        (void)_va_Array_203;
        I64 _va_Array_203_ek = 0;
        (void)_va_Array_203_ek;
        OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
        _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_203_eo;
        U32 hoisted__U32_7102 = 0;
        (void)hoisted__U32_7102;
        (void)hoisted__Str_7103;
        (void)hoisted__Str_7103;
        (void)hoisted__Str_7104;
        (void)hoisted__Str_7104;
        Array__Str_set(_va_Array_203, hoisted__U32_7102, &hoisted__Str_7103, &_va_Array_203_ek, _va_Array_203_eo, &hoisted__Str_7104);
        OutOfBounds_delete(_va_Array_203_eo, 1);
        Str_delete(&hoisted__Str_7104, (Bool){0});
        panic(_va_Array_203, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7115 = parts;
        (void)_fc_Array__Str_7115;
        (void)_fc_Array__Str_7115;
        U32 _fi_USize_7115 = 0;
        (void)_fi_USize_7115;
        while (1) {
            U32 hoisted__U32_7117 = Array__Str_len(_fc_Array__Str_7115);
            (void)hoisted__U32_7117;
            Bool _wcond_Bool_7116 = U32_lt(_fi_USize_7115, hoisted__U32_7117);
            (void)_wcond_Bool_7116;
            if (_wcond_Bool_7116) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7115, &_fi_USize_7115);
            U32 hoisted__U32_7118 = 1;
            (void)hoisted__U32_7118;
            U32 hoisted__U32_7119 = U32_add(_fi_USize_7115, hoisted__U32_7118);
            (void)hoisted__U32_7119;
            _fi_USize_7115 = hoisted__U32_7119;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7153 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7153;
    return hoisted__Bool_7153;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7162 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7162;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7162;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7163 = 0;
    (void)hoisted__U32_7163;
    U64 hoisted__U64_7164 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7163); });
    (void)hoisted__U64_7164;
    return hoisted__U64_7164;
}

U32 Range_size(void) {
    U32 hoisted__U32_7195 = 16;
    (void)hoisted__U32_7195;
    return hoisted__U32_7195;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7324 = 3;
    (void)hoisted__I64_7324;
    (void)hoisted__Str_7325;
    (void)hoisted__Str_7325;
    assert_eq__I64(result, hoisted__I64_7324, &hoisted__Str_7325);
    Str_delete(&hoisted__Str_7325, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7332 = 15;
    (void)hoisted__I64_7332;
    (void)hoisted__Str_7333;
    (void)hoisted__Str_7333;
    assert_eq__I64(result, hoisted__I64_7332, &hoisted__Str_7333);
    Str_delete(&hoisted__Str_7333, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7340 = 26;
    (void)hoisted__I64_7340;
    (void)hoisted__Str_7341;
    (void)hoisted__Str_7341;
    assert_eq__I64(result, hoisted__I64_7340, &hoisted__Str_7341);
    Str_delete(&hoisted__Str_7341, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7344;
    (void)hoisted__Str_7344;
    (void)hoisted__Str_7345;
    (void)hoisted__Str_7345;
    assert_eq__Str(&result, &hoisted__Str_7344, &hoisted__Str_7345);
    Str_delete(&hoisted__Str_7344, (Bool){0});
    Str_delete(&hoisted__Str_7345, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7373;
    (void)hoisted__Str_7373;
    (void)hoisted__Str_7374;
    (void)hoisted__Str_7374;
    assert_eq__Str(&r, &hoisted__Str_7373, &hoisted__Str_7374);
    Str_delete(&hoisted__Str_7373, (Bool){0});
    Str_delete(&hoisted__Str_7374, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7378;
    (void)hoisted__Str_7378;
    (void)hoisted__Str_7379;
    (void)hoisted__Str_7379;
    assert_eq__Str(&r2, &hoisted__Str_7378, &hoisted__Str_7379);
    Str_delete(&hoisted__Str_7378, (Bool){0});
    Str_delete(&hoisted__Str_7379, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7402;
    (void)hoisted__Str_7402;
    (void)hoisted__Str_7403;
    (void)hoisted__Str_7403;
    assert_eq__Str(&d, &hoisted__Str_7402, &hoisted__Str_7403);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7402, (Bool){0});
    Str_delete(&hoisted__Str_7403, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7414;
    (void)hoisted__Str_7414;
    (void)hoisted__Str_7415;
    (void)hoisted__Str_7415;
    assert_eq__Str(&d2, &hoisted__Str_7414, &hoisted__Str_7415);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7414, (Bool){0});
    Str_delete(&hoisted__Str_7415, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7427 = 106;
    (void)hoisted__I64_7427;
    (void)hoisted__Str_7428;
    (void)hoisted__Str_7428;
    assert_eq__I64(d3, hoisted__I64_7427, &hoisted__Str_7428);
    Str_delete(&hoisted__Str_7428, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8027;
    (void)hoisted__Str_8027;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8027);
    Str_delete(&hoisted__Str_8027, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)hoisted__Str_8028;
    (void)hoisted__Str_8028;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8028);
    Str_delete(&hoisted__Str_8028, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8030 = 8;
    (void)hoisted__I64_8030;
    (void)hoisted__Str_8031;
    (void)hoisted__Str_8031;
    assert_eq__I64(result, hoisted__I64_8030, &hoisted__Str_8031);
    Str_delete(&hoisted__Str_8031, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8034 = 1;
    (void)hoisted__Bool_8034;
    (void)hoisted__Str_8035;
    (void)hoisted__Str_8035;
    assert(hoisted__Bool_8034, &hoisted__Str_8035);
    Str_delete(&hoisted__Str_8035, (Bool){0});
    Bool hoisted__Bool_8038 = 1;
    (void)hoisted__Bool_8038;
    (void)hoisted__Str_8039;
    (void)hoisted__Str_8039;
    assert(hoisted__Bool_8038, &hoisted__Str_8039);
    Str_delete(&hoisted__Str_8039, (Bool){0});
}

void test_fold_f32(void) {
    (void)hoisted__Str_8044;
    (void)hoisted__Str_8044;
    (void)hoisted__Str_8045;
    (void)hoisted__Str_8045;
    (void)hoisted__Str_8046;
    (void)hoisted__Str_8046;
    assert_eq__Str(&hoisted__Str_8044, &hoisted__Str_8045, &hoisted__Str_8046);
    Str_delete(&hoisted__Str_8044, (Bool){0});
    Str_delete(&hoisted__Str_8045, (Bool){0});
    Str_delete(&hoisted__Str_8046, (Bool){0});
    (void)hoisted__Str_8049;
    (void)hoisted__Str_8049;
    (void)hoisted__Str_8050;
    (void)hoisted__Str_8050;
    (void)hoisted__Str_8051;
    (void)hoisted__Str_8051;
    assert_eq__Str(&hoisted__Str_8049, &hoisted__Str_8050, &hoisted__Str_8051);
    Str_delete(&hoisted__Str_8049, (Bool){0});
    Str_delete(&hoisted__Str_8050, (Bool){0});
    Str_delete(&hoisted__Str_8051, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8056 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8056;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8056;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8057 = 0;
    (void)hoisted__U32_8057;
    U64 hoisted__U64_8058 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8057); });
    (void)hoisted__U64_8058;
    return hoisted__U64_8058;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8089 = 16;
    (void)hoisted__U32_8089;
    return hoisted__U32_8089;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8090 = 42;
    (void)hoisted__I64_8090;
    (void)hoisted__Str_8091;
    (void)hoisted__Str_8091;
    assert_eq__I64(v.x, hoisted__I64_8090, &hoisted__Str_8091);
    Str_delete(&hoisted__Str_8091, (Bool){0});
    I64 hoisted__I64_8092 = 99;
    (void)hoisted__I64_8092;
    (void)hoisted__Str_8093;
    (void)hoisted__Str_8093;
    assert_eq__I64(v.y, hoisted__I64_8092, &hoisted__Str_8093);
    Str_delete(&hoisted__Str_8093, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8096 = 10;
    (void)hoisted__I64_8096;
    (void)hoisted__Str_8097;
    (void)hoisted__Str_8097;
    assert_eq__I64(p.x, hoisted__I64_8096, &hoisted__Str_8097);
    Str_delete(&hoisted__Str_8097, (Bool){0});
    I64 hoisted__I64_8098 = 20;
    (void)hoisted__I64_8098;
    (void)hoisted__Str_8099;
    (void)hoisted__Str_8099;
    assert_eq__I64(p.y, hoisted__I64_8098, &hoisted__Str_8099);
    Str_delete(&hoisted__Str_8099, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8105 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8105;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8105;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8106 = 0;
    (void)hoisted__U32_8106;
    U64 hoisted__U64_8107 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8106); });
    (void)hoisted__U64_8107;
    return hoisted__U64_8107;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8138 = 32;
    (void)hoisted__U32_8138;
    return hoisted__U32_8138;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8139 = 5;
    (void)hoisted__I64_8139;
    (void)hoisted__Str_8140;
    (void)hoisted__Str_8140;
    assert_eq__I64(r.top_left.x, hoisted__I64_8139, &hoisted__Str_8140);
    Str_delete(&hoisted__Str_8140, (Bool){0});
    I64 hoisted__I64_8141 = 10;
    (void)hoisted__I64_8141;
    (void)hoisted__Str_8142;
    (void)hoisted__Str_8142;
    assert_eq__I64(r.top_left.y, hoisted__I64_8141, &hoisted__Str_8142);
    Str_delete(&hoisted__Str_8142, (Bool){0});
    I64 hoisted__I64_8143 = 100;
    (void)hoisted__I64_8143;
    (void)hoisted__Str_8144;
    (void)hoisted__Str_8144;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8143, &hoisted__Str_8144);
    Str_delete(&hoisted__Str_8144, (Bool){0});
    I64 hoisted__I64_8145 = 200;
    (void)hoisted__I64_8145;
    (void)hoisted__Str_8146;
    (void)hoisted__Str_8146;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8145, &hoisted__Str_8146);
    Str_delete(&hoisted__Str_8146, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8148 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8148;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8148;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8149 = 0;
    (void)hoisted__U32_8149;
    U64 hoisted__U64_8150 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8149); });
    (void)hoisted__U64_8150;
    return hoisted__U64_8150;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8193 = 12;
    (void)hoisted__U32_8193;
    return hoisted__U32_8193;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8197 = F32_to_str(v.x);
    (void)hoisted__Str_8197;
    (void)hoisted__Str_8198;
    (void)hoisted__Str_8198;
    (void)hoisted__Str_8199;
    (void)hoisted__Str_8199;
    assert_eq__Str(hoisted__Str_8197, &hoisted__Str_8198, &hoisted__Str_8199);
    Str_delete(hoisted__Str_8197, 1);
    Str_delete(&hoisted__Str_8198, (Bool){0});
    Str_delete(&hoisted__Str_8199, (Bool){0});
    Str *hoisted__Str_8200 = F32_to_str(v.y);
    (void)hoisted__Str_8200;
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8202;
    (void)hoisted__Str_8202;
    assert_eq__Str(hoisted__Str_8200, &hoisted__Str_8201, &hoisted__Str_8202);
    Str_delete(hoisted__Str_8200, 1);
    Str_delete(&hoisted__Str_8201, (Bool){0});
    Str_delete(&hoisted__Str_8202, (Bool){0});
    Str *hoisted__Str_8203 = F32_to_str(v.z);
    (void)hoisted__Str_8203;
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8205;
    (void)hoisted__Str_8205;
    assert_eq__Str(hoisted__Str_8203, &hoisted__Str_8204, &hoisted__Str_8205);
    Str_delete(hoisted__Str_8203, 1);
    Str_delete(&hoisted__Str_8204, (Bool){0});
    Str_delete(&hoisted__Str_8205, (Bool){0});
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
    Bool hoisted__Bool_8210 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8210;
    if (hoisted__Bool_8210) {
        Bool hoisted__Bool_8207 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8207;
        { Bool _ret_val = hoisted__Bool_8207;
                return _ret_val; }
    }
    Bool hoisted__Bool_8211 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8211;
    if (hoisted__Bool_8211) {
        Bool hoisted__Bool_8208 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8208;
        { Bool _ret_val = hoisted__Bool_8208;
                return _ret_val; }
    }
    Bool hoisted__Bool_8212 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8212;
    if (hoisted__Bool_8212) {
        Bool hoisted__Bool_8209 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8209;
        { Bool _ret_val = hoisted__Bool_8209;
                return _ret_val; }
    }
    Bool hoisted__Bool_8213 = 0;
    (void)hoisted__Bool_8213;
    return hoisted__Bool_8213;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8221 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8221;
    if (hoisted__Bool_8221) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8222 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8222;
    if (hoisted__Bool_8222) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8223 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8223;
    if (hoisted__Bool_8223) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8224 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8224;
    UNREACHABLE(&hoisted__Str_8224);
    Str_delete(&hoisted__Str_8224, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8225 = 4;
    (void)hoisted__U32_8225;
    return hoisted__U32_8225;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8226 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8226;
    (void)hoisted__Str_8227;
    (void)hoisted__Str_8227;
    assert(hoisted__Bool_8226, &hoisted__Str_8227);
    Str_delete(&hoisted__Str_8227, (Bool){0});
    Bool hoisted__Bool_8228 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8228;
    Bool hoisted__Bool_8229 = not(hoisted__Bool_8228);
    (void)hoisted__Bool_8229;
    (void)hoisted__Str_8230;
    (void)hoisted__Str_8230;
    assert(hoisted__Bool_8229, &hoisted__Str_8230);
    Str_delete(&hoisted__Str_8230, (Bool){0});
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
    Bool hoisted__Bool_8231 = is(self, other);
    (void)hoisted__Bool_8231;
    return hoisted__Bool_8231;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8249 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8249;
    if (hoisted__Bool_8249) {
        I64 *hoisted__I64_8245 = get_payload(self);
        (void)hoisted__I64_8245;
        (void)hoisted__I64_8245;
        Bool hoisted__Bool_8246 = 0;
        (void)hoisted__Bool_8246;
        I64_delete(hoisted__I64_8245, hoisted__Bool_8246);
    }
    Bool hoisted__Bool_8250 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8250;
    if (hoisted__Bool_8250) {
        Str *hoisted__Str_8247 = get_payload(self);
        (void)hoisted__Str_8247;
        (void)hoisted__Str_8247;
        Bool hoisted__Bool_8248 = 0;
        (void)hoisted__Bool_8248;
        Str_delete(hoisted__Str_8247, hoisted__Bool_8248);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8281 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8281;
    if (hoisted__Bool_8281) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8278 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8278;
        { Token * _ret_val = hoisted__Token_8278;
                return _ret_val; }
    }
    Bool hoisted__Bool_8282 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8282;
    if (hoisted__Bool_8282) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8279 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8279;
        Token *hoisted__Token_8280 = Token_Name(hoisted__Str_8279);
        (void)hoisted__Token_8280;
        { Token * _ret_val = hoisted__Token_8280;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8283 = 24;
    (void)hoisted__U32_8283;
    return hoisted__U32_8283;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8285 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8285;
    (void)hoisted__Str_8286;
    (void)hoisted__Str_8286;
    assert(hoisted__Bool_8285, &hoisted__Str_8286);
    Str_delete(&hoisted__Str_8286, (Bool){0});
    Bool hoisted__Bool_8287 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8287;
    Bool hoisted__Bool_8288 = not(hoisted__Bool_8287);
    (void)hoisted__Bool_8288;
    (void)hoisted__Str_8289;
    (void)hoisted__Str_8289;
    assert(hoisted__Bool_8288, &hoisted__Str_8289);
    Str_delete(&hoisted__Str_8289, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8290 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8290;
    (void)hoisted__Str_8291;
    (void)hoisted__Str_8291;
    assert(hoisted__Bool_8290, &hoisted__Str_8291);
    Str_delete(&hoisted__Str_8291, (Bool){0});
    Bool hoisted__Bool_8292 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8292;
    Bool hoisted__Bool_8293 = not(hoisted__Bool_8292);
    (void)hoisted__Bool_8293;
    (void)hoisted__Str_8294;
    (void)hoisted__Str_8294;
    assert(hoisted__Bool_8293, &hoisted__Str_8294);
    Str_delete(&hoisted__Str_8294, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8297 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8297;
    (void)hoisted__Str_8298;
    (void)hoisted__Str_8298;
    assert(hoisted__Bool_8297, &hoisted__Str_8298);
    Str_delete(&hoisted__Str_8298, (Bool){0});
    Bool hoisted__Bool_8299 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8299;
    Bool hoisted__Bool_8300 = not(hoisted__Bool_8299);
    (void)hoisted__Bool_8300;
    (void)hoisted__Str_8301;
    (void)hoisted__Str_8301;
    assert(hoisted__Bool_8300, &hoisted__Str_8301);
    Str_delete(&hoisted__Str_8301, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8433 = I64_neq(a, b);
    (void)hoisted__Bool_8433;
    if (hoisted__Bool_8433) {
        U32 hoisted__U32_8417 = 5;
        (void)hoisted__U32_8417;
        Array__Str *_va_Array_248 = Array__Str_new(hoisted__U32_8417);
        (void)_va_Array_248;
        I64 _va_Array_248_ek = 0;
        (void)_va_Array_248_ek;
        OutOfBounds *_va_Array_248_eo = malloc(sizeof(OutOfBounds));
        _va_Array_248_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_248_eo;
        U32 hoisted__U32_8418 = 0;
        (void)hoisted__U32_8418;
        (void)hoisted__Str_8419;
        (void)hoisted__Str_8419;
        (void)hoisted__Str_8420;
        (void)hoisted__Str_8420;
        Array__Str_set(_va_Array_248, hoisted__U32_8418, &hoisted__Str_8419, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8420);
        Str_delete(&hoisted__Str_8420, (Bool){0});
        U32 hoisted__U32_8421 = 1;
        (void)hoisted__U32_8421;
        Str *hoisted__Str_8422 = I64_to_str(a);
        (void)hoisted__Str_8422;
        (void)hoisted__Str_8423;
        (void)hoisted__Str_8423;
        Array__Str_set(_va_Array_248, hoisted__U32_8421, hoisted__Str_8422, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8423);
        Str_delete(&hoisted__Str_8423, (Bool){0});
        U32 hoisted__U32_8424 = 2;
        (void)hoisted__U32_8424;
        (void)hoisted__Str_8425;
        (void)hoisted__Str_8425;
        (void)hoisted__Str_8426;
        (void)hoisted__Str_8426;
        Array__Str_set(_va_Array_248, hoisted__U32_8424, &hoisted__Str_8425, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8426);
        Str_delete(&hoisted__Str_8426, (Bool){0});
        U32 hoisted__U32_8427 = 3;
        (void)hoisted__U32_8427;
        Str *hoisted__Str_8428 = I64_to_str(b);
        (void)hoisted__Str_8428;
        (void)hoisted__Str_8429;
        (void)hoisted__Str_8429;
        Array__Str_set(_va_Array_248, hoisted__U32_8427, hoisted__Str_8428, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8429);
        Str_delete(&hoisted__Str_8429, (Bool){0});
        U32 hoisted__U32_8430 = 4;
        (void)hoisted__U32_8430;
        (void)hoisted__Str_8431;
        (void)hoisted__Str_8431;
        (void)hoisted__Str_8432;
        (void)hoisted__Str_8432;
        Array__Str_set(_va_Array_248, hoisted__U32_8430, &hoisted__Str_8431, &_va_Array_248_ek, _va_Array_248_eo, &hoisted__Str_8432);
        OutOfBounds_delete(_va_Array_248_eo, 1);
        Str_delete(&hoisted__Str_8432, (Bool){0});
        panic(_va_Array_248, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8450 = Str_neq(a, b);
    (void)hoisted__Bool_8450;
    if (hoisted__Bool_8450) {
        U32 hoisted__U32_8434 = 5;
        (void)hoisted__U32_8434;
        Array__Str *_va_Array_249 = Array__Str_new(hoisted__U32_8434);
        (void)_va_Array_249;
        I64 _va_Array_249_ek = 0;
        (void)_va_Array_249_ek;
        OutOfBounds *_va_Array_249_eo = malloc(sizeof(OutOfBounds));
        _va_Array_249_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_249_eo;
        U32 hoisted__U32_8435 = 0;
        (void)hoisted__U32_8435;
        (void)hoisted__Str_8436;
        (void)hoisted__Str_8436;
        (void)hoisted__Str_8437;
        (void)hoisted__Str_8437;
        Array__Str_set(_va_Array_249, hoisted__U32_8435, &hoisted__Str_8436, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8437);
        Str_delete(&hoisted__Str_8437, (Bool){0});
        U32 hoisted__U32_8438 = 1;
        (void)hoisted__U32_8438;
        Str *hoisted__Str_8439 = Str_to_str(a);
        (void)hoisted__Str_8439;
        (void)hoisted__Str_8440;
        (void)hoisted__Str_8440;
        Array__Str_set(_va_Array_249, hoisted__U32_8438, hoisted__Str_8439, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8440);
        Str_delete(&hoisted__Str_8440, (Bool){0});
        U32 hoisted__U32_8441 = 2;
        (void)hoisted__U32_8441;
        (void)hoisted__Str_8442;
        (void)hoisted__Str_8442;
        (void)hoisted__Str_8443;
        (void)hoisted__Str_8443;
        Array__Str_set(_va_Array_249, hoisted__U32_8441, &hoisted__Str_8442, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8443);
        Str_delete(&hoisted__Str_8443, (Bool){0});
        U32 hoisted__U32_8444 = 3;
        (void)hoisted__U32_8444;
        Str *hoisted__Str_8445 = Str_to_str(b);
        (void)hoisted__Str_8445;
        (void)hoisted__Str_8446;
        (void)hoisted__Str_8446;
        Array__Str_set(_va_Array_249, hoisted__U32_8444, hoisted__Str_8445, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8446);
        Str_delete(&hoisted__Str_8446, (Bool){0});
        U32 hoisted__U32_8447 = 4;
        (void)hoisted__U32_8447;
        (void)hoisted__Str_8448;
        (void)hoisted__Str_8448;
        (void)hoisted__Str_8449;
        (void)hoisted__Str_8449;
        Array__Str_set(_va_Array_249, hoisted__U32_8447, &hoisted__Str_8448, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8449);
        OutOfBounds_delete(_va_Array_249_eo, 1);
        Str_delete(&hoisted__Str_8449, (Bool){0});
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
void *Str_unsafe_get_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Str_unsafe_get(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_unsafe_get_dyn__til_closure = { (void *)Str_unsafe_get_dyn, NULL, NULL };
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "unsafe_get", 10ULL) == 0) return (void*)&Str_unsafe_get_dyn__til_closure;
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
