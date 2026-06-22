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
        Array__Str *_fc_Array__Str_727 = parts;
        (void)_fc_Array__Str_727;
        (void)_fc_Array__Str_727;
        U32 _fi_USize_727 = 0;
        (void)_fi_USize_727;
        while (1) {
            U32 hoisted__U32_729 = Array__Str_len(_fc_Array__Str_727);
            (void)hoisted__U32_729;
            Bool _wcond_Bool_728 = U32_lt(_fi_USize_727, hoisted__U32_729);
            (void)_wcond_Bool_728;
            if (_wcond_Bool_728) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_727, &_fi_USize_727);
            U32 hoisted__U32_730 = 1;
            (void)hoisted__U32_730;
            U32 hoisted__U32_731 = U32_add(_fi_USize_727, hoisted__U32_730);
            (void)hoisted__U32_731;
            _fi_USize_727 = hoisted__U32_731;
            U32 hoisted__U32_732 = Str_len(s);
            (void)hoisted__U32_732;
            U32 hoisted__U32_733 = U32_add(total, hoisted__U32_732);
            (void)hoisted__U32_733;
            total = hoisted__U32_733;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_734 = parts;
        (void)_fc_Array__Str_734;
        (void)_fc_Array__Str_734;
        U32 _fi_USize_734 = 0;
        (void)_fi_USize_734;
        while (1) {
            U32 hoisted__U32_736 = Array__Str_len(_fc_Array__Str_734);
            (void)hoisted__U32_736;
            Bool _wcond_Bool_735 = U32_lt(_fi_USize_734, hoisted__U32_736);
            (void)_wcond_Bool_735;
            if (_wcond_Bool_735) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_734, &_fi_USize_734);
            U32 hoisted__U32_737 = 1;
            (void)hoisted__U32_737;
            U32 hoisted__U32_738 = U32_add(_fi_USize_734, hoisted__U32_737);
            (void)hoisted__U32_738;
            _fi_USize_734 = hoisted__U32_738;
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
    void *hoisted__v_746 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_746;
    (void)hoisted__v_746;
    return hoisted__v_746;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_755 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_755;
    if (hoisted__Bool_755) {
        min_len = b->count;
    }
    {
        U32 _re_U32_747 = U32_clone(&min_len);
        (void)_re_U32_747;
        U32 _rc_U32_747 = 0;
        (void)_rc_U32_747;
        Bool hoisted__Bool_754 = U32_lte(_rc_U32_747, _re_U32_747);
        (void)hoisted__Bool_754;
        if (hoisted__Bool_754) {
            while (1) {
                Bool _wcond_Bool_748 = U32_lt(_rc_U32_747, _re_U32_747);
                (void)_wcond_Bool_748;
                if (_wcond_Bool_748) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_747);
                U32_inc(&_rc_U32_747);
                I8 *ab = Str_unsafe_get(a, &i);
                I8 *bb = Str_unsafe_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_749 = 0;
                (void)hoisted__I64_749;
                Bool hoisted__Bool_750 = I64_neq(c, hoisted__I64_749);
                (void)hoisted__Bool_750;
                if (hoisted__Bool_750) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_751 = U32_gt(_rc_U32_747, _re_U32_747);
                (void)_wcond_Bool_751;
                if (_wcond_Bool_751) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_747);
                U32_dec(&_rc_U32_747);
                I8 *ab = Str_unsafe_get(a, &i);
                I8 *bb = Str_unsafe_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_752 = 0;
                (void)hoisted__I64_752;
                Bool hoisted__Bool_753 = I64_neq(c, hoisted__I64_752);
                (void)hoisted__Bool_753;
                if (hoisted__Bool_753) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_756 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_756;
    return hoisted__I64_756;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_757 = 1;
    (void)hoisted__U32_757;
    U32 hoisted__U64_758 = U32_add(n, hoisted__U32_757);
    (void)hoisted__U64_758;
    void * buf = malloc(hoisted__U64_758);
    I32 hoisted__I32_759 = 0;
    (void)hoisted__I32_759;
    U64 hoisted__U64_760 = 1ULL;
    (void)hoisted__U64_760;
    memset(buf, hoisted__I32_759, hoisted__U64_760);
    I64 hoisted__I64_761 = 0;
    (void)hoisted__I64_761;
    Str *hoisted__Str_762 = malloc(sizeof(Str));
    hoisted__Str_762->c_str = buf;
    hoisted__Str_762->count = hoisted__I64_761;
    hoisted__Str_762->cap = n;
    (void)hoisted__Str_762;
    return hoisted__Str_762;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_775 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_775;
    if (hoisted__Bool_775) {
        U32 hoisted__U32_765 = 1;
        (void)hoisted__U32_765;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_765);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_766 = 0;
        (void)hoisted__U32_766;
        static Str hoisted__Str_767 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_767;
        static Str hoisted__Str_768 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_768;
        Array__Str_set(_va_Array_18, hoisted__U32_766, &hoisted__Str_767, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_768);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_768, (Bool){0});
        static Str hoisted__Str_769 = (Str){.c_str = (void *)"./src/core/str.til:83:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_769;
        panic(_va_Array_18, &hoisted__Str_769);
        Str_delete(&hoisted__Str_769, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_776 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_776;
    if (hoisted__Bool_776) {
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
        static Str hoisted__Str_772 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_772;
        static Str hoisted__Str_773 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_773;
        Array__Str_set(_va_Array_19, hoisted__U32_771, &hoisted__Str_772, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_773);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_773, (Bool){0});
        static Str hoisted__Str_774 = (Str){.c_str = (void *)"./src/core/str.til:87:13", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_774;
        panic(_va_Array_19, &hoisted__Str_774);
        Str_delete(&hoisted__Str_774, (Bool){0});
    }
    void *hoisted__v_777 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_777;
    (void)hoisted__v_777;
    memcpy(hoisted__v_777, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_778 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_778;
    (void)hoisted__v_778;
    I32 hoisted__I32_779 = 0;
    (void)hoisted__I32_779;
    U64 hoisted__U64_780 = 1ULL;
    (void)hoisted__U64_780;
    memset(hoisted__v_778, hoisted__I32_779, hoisted__U64_780);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_781 = 1;
    (void)hoisted__U32_781;
    U32 hoisted__U64_782 = U32_add(val->count, hoisted__U32_781);
    (void)hoisted__U64_782;
    void * new_data = malloc(hoisted__U64_782);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_783 = ptr_add(new_data, val->count);
    (void)hoisted__v_783;
    (void)hoisted__v_783;
    I32 hoisted__I32_784 = 0;
    (void)hoisted__I32_784;
    U64 hoisted__U64_785 = 1ULL;
    (void)hoisted__U64_785;
    memset(hoisted__v_783, hoisted__I32_784, hoisted__U64_785);
    Str *hoisted__Str_786 = malloc(sizeof(Str));
    hoisted__Str_786->c_str = new_data;
    hoisted__Str_786->count = val->count;
    hoisted__Str_786->cap = val->count;
    (void)hoisted__Str_786;
    return hoisted__Str_786;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_787 = Str_clone(self);
    (void)hoisted__Str_787;
    return hoisted__Str_787;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_788 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_788;
    if (hoisted__Bool_788) {
        free(self->c_str);
    }
    Bool hoisted__Bool_789 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_789;
    Bool hoisted__Bool_790 = and(call_free, hoisted__Bool_789);
    (void)hoisted__Bool_790;
    if (hoisted__Bool_790) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_985 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_985;
    return hoisted__U64_985;
}

U32 Str_size(void) {
    U32 hoisted__U32_1170 = 16;
    (void)hoisted__U32_1170;
    return hoisted__U32_1170;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1171 = Str_cmp(a, b);
    (void)hoisted__I64_1171;
    I64 hoisted__I64_1172 = 0;
    (void)hoisted__I64_1172;
    Bool hoisted__Bool_1173 = I64_eq(hoisted__I64_1171, hoisted__I64_1172);
    (void)hoisted__Bool_1173;
    return hoisted__Bool_1173;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1182 = Str_eq(a, b);
    (void)hoisted__Bool_1182;
    Bool hoisted__Bool_1183 = not(hoisted__Bool_1182);
    (void)hoisted__Bool_1183;
    return hoisted__Bool_1183;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1275 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1275->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1275;
    return hoisted__OutOfBounds_1275;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1276 = 0;
    (void)hoisted__Bool_1276;
    Str_delete(&self->msg, hoisted__Bool_1276);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1277 = 0;
    (void)hoisted__U32_1277;
    U64 hoisted__U64_1278 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1277); });
    (void)hoisted__U64_1278;
    return hoisted__U64_1278;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1297 = 16;
    (void)hoisted__U32_1297;
    return hoisted__U32_1297;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1321 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1321;
    U32 hoisted__U32_1322 = 16;
    (void)hoisted__U32_1322;
    Type *hoisted__Type_1323 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1323;
    U64 hoisted__U64_1324 = (U64)(cap);
    (void)hoisted__U64_1324;
    Type_delete(hoisted__Type_1321, 1);
    U64 hoisted__U64_1325 = (U64)(hoisted__U32_1322);
    (void)hoisted__U64_1325;
    Type_delete(hoisted__Type_1323, 1);
    void * hoisted__v_1326 = calloc(hoisted__U64_1324, hoisted__U64_1325);
    (void)hoisted__v_1326;
    Array__Str *hoisted__Array__Str_1327 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1327->data = hoisted__v_1326;
    hoisted__Array__Str_1327->cap = cap;
    (void)hoisted__Array__Str_1327;
    return hoisted__Array__Str_1327;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_1328 = 16;
    (void)hoisted__U32_1328;
    U32 hoisted__U32_1329 = U32_mul(DEREF(i), hoisted__U32_1328);
    (void)hoisted__U32_1329;
    Type *hoisted__Type_1330 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1330;
    U64 hoisted__U64_1331 = (U64)(hoisted__U32_1329);
    (void)hoisted__U64_1331;
    Type_delete(hoisted__Type_1330, 1);
    void *hoisted__v_1332 = ptr_add(self->data, hoisted__U64_1331);
    (void)hoisted__v_1332;
    (void)hoisted__v_1332;
    return hoisted__v_1332;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_1359 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1359;
    (void)hoisted__Str_1359;
    Bool hoisted__Bool_1360 = 0;
    (void)hoisted__Bool_1360;
    Str_delete(hoisted__Str_1359, hoisted__Bool_1360);
    U32 hoisted__U32_1361 = 16;
    (void)hoisted__U32_1361;
    Type *hoisted__Type_1362 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1362;
    Str *hoisted__Str_1363 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1363;
    (void)hoisted__Str_1363;
    U64 hoisted__U64_1364 = (U64)(hoisted__U32_1361);
    (void)hoisted__U64_1364;
    Type_delete(hoisted__Type_1362, 1);
    memcpy(hoisted__Str_1363, val, hoisted__U64_1364);
    U32 hoisted__U32_1365 = 16;
    (void)hoisted__U32_1365;
    Type *hoisted__Type_1366 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1366;
    I32 hoisted__I32_1367 = 0;
    (void)hoisted__I32_1367;
    U64 hoisted__U64_1368 = (U64)(hoisted__U32_1365);
    (void)hoisted__U64_1368;
    Type_delete(hoisted__Type_1366, 1);
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1367, hoisted__U64_1368); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1391 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1391;
    if (hoisted__Bool_1391) {
        U32 hoisted__U32_1369 = 6;
        (void)hoisted__U32_1369;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1369);
        (void)_va_Array_31;
        I64 _va_Array_31_ek = 0;
        (void)_va_Array_31_ek;
        OutOfBounds *_va_Array_31_eo = malloc(sizeof(OutOfBounds));
        _va_Array_31_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_31_eo;
        U32 hoisted__U32_1370 = 0;
        (void)hoisted__U32_1370;
        Str *hoisted__Str_1371 = Str_clone(loc);
        (void)hoisted__Str_1371;
        static Str hoisted__Str_1372 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1372;
        Array__Str_set(_va_Array_31, hoisted__U32_1370, hoisted__Str_1371, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1372);
        Str_delete(&hoisted__Str_1372, (Bool){0});
        U32 hoisted__U32_1373 = 1;
        (void)hoisted__U32_1373;
        static Str hoisted__Str_1374 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1374;
        static Str hoisted__Str_1375 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1375;
        Array__Str_set(_va_Array_31, hoisted__U32_1373, &hoisted__Str_1374, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1375);
        Str_delete(&hoisted__Str_1375, (Bool){0});
        U32 hoisted__U32_1376 = 2;
        (void)hoisted__U32_1376;
        Str *hoisted__Str_1377 = U32_to_str(i);
        (void)hoisted__Str_1377;
        static Str hoisted__Str_1378 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1378;
        Array__Str_set(_va_Array_31, hoisted__U32_1376, hoisted__Str_1377, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1378);
        Str_delete(&hoisted__Str_1378, (Bool){0});
        U32 hoisted__U32_1379 = 3;
        (void)hoisted__U32_1379;
        static Str hoisted__Str_1380 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1380;
        static Str hoisted__Str_1381 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1381;
        Array__Str_set(_va_Array_31, hoisted__U32_1379, &hoisted__Str_1380, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1381);
        Str_delete(&hoisted__Str_1381, (Bool){0});
        U32 hoisted__U32_1382 = 4;
        (void)hoisted__U32_1382;
        Str *hoisted__Str_1383 = U32_to_str(self->cap);
        (void)hoisted__Str_1383;
        static Str hoisted__Str_1384 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1384;
        Array__Str_set(_va_Array_31, hoisted__U32_1382, hoisted__Str_1383, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1384);
        Str_delete(&hoisted__Str_1384, (Bool){0});
        U32 hoisted__U32_1385 = 5;
        (void)hoisted__U32_1385;
        static Str hoisted__Str_1386 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1386;
        static Str hoisted__Str_1387 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1387;
        Array__Str_set(_va_Array_31, hoisted__U32_1385, &hoisted__Str_1386, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1387);
        OutOfBounds_delete(_va_Array_31_eo, 1);
        Str_delete(&hoisted__Str_1387, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1388 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_31); hoisted__OutOfBounds_1388->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1388;
        U32 hoisted__U32_1389 = 16;
        (void)hoisted__U32_1389;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1388, hoisted__U32_1389);
        OutOfBounds_delete(hoisted__OutOfBounds_1388, 1);
        I64 hoisted__I64_1390 = 3;
        (void)hoisted__I64_1390;
        *_err_kind = hoisted__I64_1390;
    }
    I64 hoisted__I64_1392 = 0;
    (void)hoisted__I64_1392;
    Bool hoisted__Bool_1393 = I64_eq(DEREF(_err_kind), hoisted__I64_1392);
    (void)hoisted__Bool_1393;
    if (hoisted__Bool_1393) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1394 = self->cap;
        (void)_re_U32_1394;
        U32 _rc_U32_1394 = 0;
        (void)_rc_U32_1394;
        Bool hoisted__Bool_1409 = U32_lte(_rc_U32_1394, _re_U32_1394);
        (void)hoisted__Bool_1409;
        if (hoisted__Bool_1409) {
            while (1) {
                Bool _wcond_Bool_1395 = U32_lt(_rc_U32_1394, _re_U32_1394);
                (void)_wcond_Bool_1395;
                if (_wcond_Bool_1395) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1394);
                U32_inc(&_rc_U32_1394);
                U32 hoisted__U32_1396 = 16;
                (void)hoisted__U32_1396;
                U32 hoisted__U32_1397 = U32_mul(i, hoisted__U32_1396);
                (void)hoisted__U32_1397;
                Type *hoisted__Type_1398 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1398;
                U64 hoisted__U64_1399 = (U64)(hoisted__U32_1397);
                (void)hoisted__U64_1399;
                Type_delete(hoisted__Type_1398, 1);
                Str *hoisted__Str_1400 = ptr_add(self->data, hoisted__U64_1399);
                (void)hoisted__Str_1400;
                (void)hoisted__Str_1400;
                Bool hoisted__Bool_1401 = 0;
                (void)hoisted__Bool_1401;
                Str_delete(hoisted__Str_1400, hoisted__Bool_1401);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1402 = U32_gt(_rc_U32_1394, _re_U32_1394);
                (void)_wcond_Bool_1402;
                if (_wcond_Bool_1402) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1394);
                U32_dec(&_rc_U32_1394);
                U32 hoisted__U32_1403 = 16;
                (void)hoisted__U32_1403;
                U32 hoisted__U32_1404 = U32_mul(i, hoisted__U32_1403);
                (void)hoisted__U32_1404;
                Type *hoisted__Type_1405 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1405;
                U64 hoisted__U64_1406 = (U64)(hoisted__U32_1404);
                (void)hoisted__U64_1406;
                Type_delete(hoisted__Type_1405, 1);
                Str *hoisted__Str_1407 = ptr_add(self->data, hoisted__U64_1406);
                (void)hoisted__Str_1407;
                (void)hoisted__Str_1407;
                Bool hoisted__Bool_1408 = 0;
                (void)hoisted__Bool_1408;
                Str_delete(hoisted__Str_1407, hoisted__Bool_1408);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1446 = 16;
    (void)hoisted__U32_1446;
    U32 hoisted__U32_1447 = U32_mul(self->cap, hoisted__U32_1446);
    (void)hoisted__U32_1447;
    Type *hoisted__Type_1448 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1448;
    U64 hoisted__U64_1449 = (U64)(hoisted__U32_1447);
    (void)hoisted__U64_1449;
    Type_delete(hoisted__Type_1448, 1);
    void * new_data = malloc(hoisted__U64_1449);
    {
        U32 _re_U32_1410 = self->cap;
        (void)_re_U32_1410;
        U32 _rc_U32_1410 = 0;
        (void)_rc_U32_1410;
        Bool hoisted__Bool_1445 = U32_lte(_rc_U32_1410, _re_U32_1410);
        (void)hoisted__Bool_1445;
        if (hoisted__Bool_1445) {
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
                Str *src = ptr_add(self->data, hoisted__U64_1415);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1416 = 16;
                (void)hoisted__U32_1416;
                U32 hoisted__U32_1417 = U32_mul(i, hoisted__U32_1416);
                (void)hoisted__U32_1417;
                Type *hoisted__Type_1418 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1418;
                U64 hoisted__U64_1419 = (U64)(hoisted__U32_1417);
                (void)hoisted__U64_1419;
                Type_delete(hoisted__Type_1418, 1);
                U32 hoisted__U32_1420 = 16;
                (void)hoisted__U32_1420;
                Type *hoisted__Type_1421 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1421;
                void *hoisted__v_1422 = ptr_add(new_data, hoisted__U64_1419);
                (void)hoisted__v_1422;
                (void)hoisted__v_1422;
                U64 hoisted__U64_1423 = (U64)(hoisted__U32_1420);
                (void)hoisted__U64_1423;
                Type_delete(hoisted__Type_1421, 1);
                memcpy(hoisted__v_1422, cloned, hoisted__U64_1423);
                U32 hoisted__U32_1424 = 16;
                (void)hoisted__U32_1424;
                Type *hoisted__Type_1425 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1425;
                I32 hoisted__I32_1426 = 0;
                (void)hoisted__I32_1426;
                U64 hoisted__U64_1427 = (U64)(hoisted__U32_1424);
                (void)hoisted__U64_1427;
                Type_delete(hoisted__Type_1425, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1426, hoisted__U64_1427); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1428 = U32_gt(_rc_U32_1410, _re_U32_1410);
                (void)_wcond_Bool_1428;
                if (_wcond_Bool_1428) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1410);
                U32_dec(&_rc_U32_1410);
                U32 hoisted__U32_1429 = 16;
                (void)hoisted__U32_1429;
                U32 hoisted__U32_1430 = U32_mul(i, hoisted__U32_1429);
                (void)hoisted__U32_1430;
                Type *hoisted__Type_1431 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1431;
                U64 hoisted__U64_1432 = (U64)(hoisted__U32_1430);
                (void)hoisted__U64_1432;
                Type_delete(hoisted__Type_1431, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1432);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1433 = 16;
                (void)hoisted__U32_1433;
                U32 hoisted__U32_1434 = U32_mul(i, hoisted__U32_1433);
                (void)hoisted__U32_1434;
                Type *hoisted__Type_1435 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1435;
                U64 hoisted__U64_1436 = (U64)(hoisted__U32_1434);
                (void)hoisted__U64_1436;
                Type_delete(hoisted__Type_1435, 1);
                U32 hoisted__U32_1437 = 16;
                (void)hoisted__U32_1437;
                Type *hoisted__Type_1438 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1438;
                void *hoisted__v_1439 = ptr_add(new_data, hoisted__U64_1436);
                (void)hoisted__v_1439;
                (void)hoisted__v_1439;
                U64 hoisted__U64_1440 = (U64)(hoisted__U32_1437);
                (void)hoisted__U64_1440;
                Type_delete(hoisted__Type_1438, 1);
                memcpy(hoisted__v_1439, cloned, hoisted__U64_1440);
                U32 hoisted__U32_1441 = 16;
                (void)hoisted__U32_1441;
                Type *hoisted__Type_1442 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1442;
                I32 hoisted__I32_1443 = 0;
                (void)hoisted__I32_1443;
                U64 hoisted__U64_1444 = (U64)(hoisted__U32_1441);
                (void)hoisted__U64_1444;
                Type_delete(hoisted__Type_1442, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1443, hoisted__U64_1444); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1450 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1450->data = new_data;
    hoisted__Array__Str_1450->cap = self->cap;
    (void)hoisted__Array__Str_1450;
    return hoisted__Array__Str_1450;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1451 = 16;
    (void)hoisted__U32_1451;
    return hoisted__U32_1451;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1452 = 16;
    (void)hoisted__U32_1452;
    Type *hoisted__Type_1453 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1453;
    U64 hoisted__U64_1454 = (U64)(hoisted__U32_1452);
    (void)hoisted__U64_1454;
    Type_delete(hoisted__Type_1453, 1);
    void * hoisted__v_1455 = malloc(hoisted__U64_1454);
    (void)hoisted__v_1455;
    U32 hoisted__U32_1456 = 0;
    (void)hoisted__U32_1456;
    I64 hoisted__I64_1457 = 1;
    (void)hoisted__I64_1457;
    Vec__Str *hoisted__Vec__Str_1458 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1458->data = hoisted__v_1455;
    hoisted__Vec__Str_1458->count = hoisted__U32_1456;
    hoisted__Vec__Str_1458->cap = hoisted__I64_1457;
    (void)hoisted__Vec__Str_1458;
    return hoisted__Vec__Str_1458;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1459 = self->count;
        (void)_re_U32_1459;
        U32 _rc_U32_1459 = 0;
        (void)_rc_U32_1459;
        Bool hoisted__Bool_1474 = U32_lte(_rc_U32_1459, _re_U32_1459);
        (void)hoisted__Bool_1474;
        if (hoisted__Bool_1474) {
            while (1) {
                Bool _wcond_Bool_1460 = U32_lt(_rc_U32_1459, _re_U32_1459);
                (void)_wcond_Bool_1460;
                if (_wcond_Bool_1460) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1459);
                U32_inc(&_rc_U32_1459);
                U32 hoisted__U32_1461 = 16;
                (void)hoisted__U32_1461;
                U32 hoisted__U32_1462 = U32_mul(i, hoisted__U32_1461);
                (void)hoisted__U32_1462;
                Type *hoisted__Type_1463 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1463;
                U64 hoisted__U64_1464 = (U64)(hoisted__U32_1462);
                (void)hoisted__U64_1464;
                Type_delete(hoisted__Type_1463, 1);
                Str *hoisted__Str_1465 = ptr_add(self->data, hoisted__U64_1464);
                (void)hoisted__Str_1465;
                (void)hoisted__Str_1465;
                Bool hoisted__Bool_1466 = 0;
                (void)hoisted__Bool_1466;
                Str_delete(hoisted__Str_1465, hoisted__Bool_1466);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1467 = U32_gt(_rc_U32_1459, _re_U32_1459);
                (void)_wcond_Bool_1467;
                if (_wcond_Bool_1467) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1459);
                U32_dec(&_rc_U32_1459);
                U32 hoisted__U32_1468 = 16;
                (void)hoisted__U32_1468;
                U32 hoisted__U32_1469 = U32_mul(i, hoisted__U32_1468);
                (void)hoisted__U32_1469;
                Type *hoisted__Type_1470 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1470;
                U64 hoisted__U64_1471 = (U64)(hoisted__U32_1469);
                (void)hoisted__U64_1471;
                Type_delete(hoisted__Type_1470, 1);
                Str *hoisted__Str_1472 = ptr_add(self->data, hoisted__U64_1471);
                (void)hoisted__Str_1472;
                (void)hoisted__Str_1472;
                Bool hoisted__Bool_1473 = 0;
                (void)hoisted__Bool_1473;
                Str_delete(hoisted__Str_1472, hoisted__Bool_1473);
            }
        }
    }
    U32 hoisted__U32_1475 = 0;
    (void)hoisted__U32_1475;
    self->count = hoisted__U32_1475;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1784 = 16;
    (void)hoisted__U32_1784;
    U32 hoisted__U32_1785 = U32_mul(self->cap, hoisted__U32_1784);
    (void)hoisted__U32_1785;
    Type *hoisted__Type_1786 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1786;
    U64 hoisted__U64_1787 = (U64)(hoisted__U32_1785);
    (void)hoisted__U64_1787;
    Type_delete(hoisted__Type_1786, 1);
    void * new_data = malloc(hoisted__U64_1787);
    {
        U32 _re_U32_1748 = self->count;
        (void)_re_U32_1748;
        U32 _rc_U32_1748 = 0;
        (void)_rc_U32_1748;
        Bool hoisted__Bool_1783 = U32_lte(_rc_U32_1748, _re_U32_1748);
        (void)hoisted__Bool_1783;
        if (hoisted__Bool_1783) {
            while (1) {
                Bool _wcond_Bool_1749 = U32_lt(_rc_U32_1748, _re_U32_1748);
                (void)_wcond_Bool_1749;
                if (_wcond_Bool_1749) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1748);
                U32_inc(&_rc_U32_1748);
                U32 hoisted__U32_1750 = 16;
                (void)hoisted__U32_1750;
                U32 hoisted__U32_1751 = U32_mul(i, hoisted__U32_1750);
                (void)hoisted__U32_1751;
                Type *hoisted__Type_1752 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1752;
                U64 hoisted__U64_1753 = (U64)(hoisted__U32_1751);
                (void)hoisted__U64_1753;
                Type_delete(hoisted__Type_1752, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1753);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1754 = 16;
                (void)hoisted__U32_1754;
                U32 hoisted__U32_1755 = U32_mul(i, hoisted__U32_1754);
                (void)hoisted__U32_1755;
                Type *hoisted__Type_1756 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1756;
                U64 hoisted__U64_1757 = (U64)(hoisted__U32_1755);
                (void)hoisted__U64_1757;
                Type_delete(hoisted__Type_1756, 1);
                U32 hoisted__U32_1758 = 16;
                (void)hoisted__U32_1758;
                Type *hoisted__Type_1759 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1759;
                void *hoisted__v_1760 = ptr_add(new_data, hoisted__U64_1757);
                (void)hoisted__v_1760;
                (void)hoisted__v_1760;
                U64 hoisted__U64_1761 = (U64)(hoisted__U32_1758);
                (void)hoisted__U64_1761;
                Type_delete(hoisted__Type_1759, 1);
                memcpy(hoisted__v_1760, cloned, hoisted__U64_1761);
                U32 hoisted__U32_1762 = 16;
                (void)hoisted__U32_1762;
                Type *hoisted__Type_1763 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1763;
                I32 hoisted__I32_1764 = 0;
                (void)hoisted__I32_1764;
                U64 hoisted__U64_1765 = (U64)(hoisted__U32_1762);
                (void)hoisted__U64_1765;
                Type_delete(hoisted__Type_1763, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1764, hoisted__U64_1765); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1766 = U32_gt(_rc_U32_1748, _re_U32_1748);
                (void)_wcond_Bool_1766;
                if (_wcond_Bool_1766) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1748);
                U32_dec(&_rc_U32_1748);
                U32 hoisted__U32_1767 = 16;
                (void)hoisted__U32_1767;
                U32 hoisted__U32_1768 = U32_mul(i, hoisted__U32_1767);
                (void)hoisted__U32_1768;
                Type *hoisted__Type_1769 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1769;
                U64 hoisted__U64_1770 = (U64)(hoisted__U32_1768);
                (void)hoisted__U64_1770;
                Type_delete(hoisted__Type_1769, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1770);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1771 = 16;
                (void)hoisted__U32_1771;
                U32 hoisted__U32_1772 = U32_mul(i, hoisted__U32_1771);
                (void)hoisted__U32_1772;
                Type *hoisted__Type_1773 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1773;
                U64 hoisted__U64_1774 = (U64)(hoisted__U32_1772);
                (void)hoisted__U64_1774;
                Type_delete(hoisted__Type_1773, 1);
                U32 hoisted__U32_1775 = 16;
                (void)hoisted__U32_1775;
                Type *hoisted__Type_1776 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1776;
                void *hoisted__v_1777 = ptr_add(new_data, hoisted__U64_1774);
                (void)hoisted__v_1777;
                (void)hoisted__v_1777;
                U64 hoisted__U64_1778 = (U64)(hoisted__U32_1775);
                (void)hoisted__U64_1778;
                Type_delete(hoisted__Type_1776, 1);
                memcpy(hoisted__v_1777, cloned, hoisted__U64_1778);
                U32 hoisted__U32_1779 = 16;
                (void)hoisted__U32_1779;
                Type *hoisted__Type_1780 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1780;
                I32 hoisted__I32_1781 = 0;
                (void)hoisted__I32_1781;
                U64 hoisted__U64_1782 = (U64)(hoisted__U32_1779);
                (void)hoisted__U64_1782;
                Type_delete(hoisted__Type_1780, 1);
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1781, hoisted__U64_1782); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1788 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1788->data = new_data;
    hoisted__Vec__Str_1788->count = self->count;
    hoisted__Vec__Str_1788->cap = self->cap;
    (void)hoisted__Vec__Str_1788;
    return hoisted__Vec__Str_1788;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1789 = 16;
    (void)hoisted__U32_1789;
    return hoisted__U32_1789;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1792 = 8;
    (void)hoisted__U32_1792;
    return hoisted__U32_1792;
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
    I64 hoisted__I64_2011 = 0;
    (void)hoisted__I64_2011;
    Bool hoisted__Bool_2012 = I64_eq(val, hoisted__I64_2011);
    (void)hoisted__Bool_2012;
    if (hoisted__Bool_2012) {
        U64 hoisted__U64_1981 = 2ULL;
        (void)hoisted__U64_1981;
        void * buf = malloc(hoisted__U64_1981);
        I64 hoisted__I64_1982 = 48;
        (void)hoisted__I64_1982;
        U64 hoisted__U64_1983 = 1ULL;
        (void)hoisted__U64_1983;
        memcpy(buf, &hoisted__I64_1982, hoisted__U64_1983);
        U64 hoisted__U64_1984 = 1ULL;
        (void)hoisted__U64_1984;
        void *hoisted__v_1985 = ptr_add(buf, hoisted__U64_1984);
        (void)hoisted__v_1985;
        (void)hoisted__v_1985;
        I32 hoisted__I32_1986 = 0;
        (void)hoisted__I32_1986;
        U64 hoisted__U64_1987 = 1ULL;
        (void)hoisted__U64_1987;
        memset(hoisted__v_1985, hoisted__I32_1986, hoisted__U64_1987);
        I64 hoisted__I64_1988 = 1;
        (void)hoisted__I64_1988;
        I64 hoisted__I64_1989 = 1;
        (void)hoisted__I64_1989;
        Str *hoisted__Str_1990 = malloc(sizeof(Str));
        hoisted__Str_1990->c_str = buf;
        hoisted__Str_1990->count = hoisted__I64_1988;
        hoisted__Str_1990->cap = hoisted__I64_1989;
        (void)hoisted__Str_1990;
        { Str * _ret_val = hoisted__Str_1990;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_2013 = 0;
    (void)hoisted__I64_2013;
    Bool hoisted__Bool_2014 = I64_lt(val, hoisted__I64_2013);
    (void)hoisted__Bool_2014;
    if (hoisted__Bool_2014) {
        Bool hoisted__Bool_1991 = 1;
        (void)hoisted__Bool_1991;
        is_neg = hoisted__Bool_1991;
        I64 hoisted__I64_1992 = 0;
        (void)hoisted__I64_1992;
        I64 hoisted__I64_1993 = I64_sub(hoisted__I64_1992, val);
        (void)hoisted__I64_1993;
        v = hoisted__I64_1993;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1995 = 0;
        (void)hoisted__I64_1995;
        Bool _wcond_Bool_1994 = I64_gt(tmp, hoisted__I64_1995);
        (void)_wcond_Bool_1994;
        if (_wcond_Bool_1994) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1996 = 10;
        (void)hoisted__I64_1996;
        I64 hoisted__I64_1997 = I64_div(tmp, hoisted__I64_1996);
        (void)hoisted__I64_1997;
        tmp = hoisted__I64_1997;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_2015 = 1ULL;
    (void)hoisted__U64_2015;
    U64 hoisted__U64_2016 = U64_add(total, hoisted__U64_2015);
    (void)hoisted__U64_2016;
    void * buf = malloc(hoisted__U64_2016);
    if (is_neg) {
        I64 hoisted__I64_1998 = 45;
        (void)hoisted__I64_1998;
        U64 hoisted__U64_1999 = 1ULL;
        (void)hoisted__U64_1999;
        memcpy(buf, &hoisted__I64_1998, hoisted__U64_1999);
    }
    U64 hoisted__U64_2017 = 1ULL;
    (void)hoisted__U64_2017;
    U64 i = U64_sub(total, hoisted__U64_2017);
    while (1) {
        I64 hoisted__I64_2001 = 0;
        (void)hoisted__I64_2001;
        Bool _wcond_Bool_2000 = I64_gt(v, hoisted__I64_2001);
        (void)_wcond_Bool_2000;
        if (_wcond_Bool_2000) {
        } else {
            break;
        }
        I64 hoisted__I64_2002 = 10;
        (void)hoisted__I64_2002;
        I64 hoisted__I64_2003 = I64_mod(v, hoisted__I64_2002);
        (void)hoisted__I64_2003;
        I64 hoisted__I64_2004 = 48;
        (void)hoisted__I64_2004;
        I64 hoisted__I64_2005 = I64_add(hoisted__I64_2003, hoisted__I64_2004);
        (void)hoisted__I64_2005;
        void *hoisted__v_2006 = ptr_add(buf, i);
        (void)hoisted__v_2006;
        (void)hoisted__v_2006;
        U8 hoisted__U8_2007 = I64_to_u8(hoisted__I64_2005);
        (void)hoisted__U8_2007;
        U64 hoisted__U64_2008 = 1ULL;
        (void)hoisted__U64_2008;
        memcpy(hoisted__v_2006, &hoisted__U8_2007, hoisted__U64_2008);
        I64 hoisted__I64_2009 = 10;
        (void)hoisted__I64_2009;
        I64 hoisted__I64_2010 = I64_div(v, hoisted__I64_2009);
        (void)hoisted__I64_2010;
        v = hoisted__I64_2010;
        U64_dec(&i);
    }
    void *hoisted__v_2018 = ptr_add(buf, total);
    (void)hoisted__v_2018;
    (void)hoisted__v_2018;
    I32 hoisted__I32_2019 = 0;
    (void)hoisted__I32_2019;
    U64 hoisted__U64_2020 = 1ULL;
    (void)hoisted__U64_2020;
    memset(hoisted__v_2018, hoisted__I32_2019, hoisted__U64_2020);
    Str *hoisted__Str_2021 = malloc(sizeof(Str));
    hoisted__Str_2021->c_str = buf;
    hoisted__Str_2021->count = total;
    hoisted__Str_2021->cap = total;
    (void)hoisted__Str_2021;
    return hoisted__Str_2021;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_2041 = 8;
    (void)hoisted__U32_2041;
    return hoisted__U32_2041;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2199 = 0;
    (void)hoisted__U32_2199;
    U64 hoisted__U64_2200 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2199); });
    (void)hoisted__U64_2200;
    return hoisted__U64_2200;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2203 = I64_cmp(a, b);
    (void)hoisted__I64_2203;
    I64 hoisted__I64_2204 = -1;
    (void)hoisted__I64_2204;
    Bool hoisted__Bool_2205 = I64_eq(hoisted__I64_2203, hoisted__I64_2204);
    (void)hoisted__Bool_2205;
    return hoisted__Bool_2205;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2206 = I64_cmp(a, b);
    (void)hoisted__I64_2206;
    I64 hoisted__I64_2207 = 1;
    (void)hoisted__I64_2207;
    Bool hoisted__Bool_2208 = I64_eq(hoisted__I64_2206, hoisted__I64_2207);
    (void)hoisted__Bool_2208;
    return hoisted__Bool_2208;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2209 = I64_eq(a, b);
    (void)hoisted__Bool_2209;
    Bool hoisted__Bool_2210 = not(hoisted__Bool_2209);
    (void)hoisted__Bool_2210;
    return hoisted__Bool_2210;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2261 = 0;
    (void)_m_Bool_2261;
    {
        Bool hoisted__Bool_2264 = 1;
        (void)hoisted__Bool_2264;
        Bool hoisted__Bool_2265 = Bool_eq(a, hoisted__Bool_2264);
        (void)hoisted__Bool_2265;
        if (hoisted__Bool_2265) {
            Bool hoisted__Bool_2262 = Bool_clone(&b);
            (void)hoisted__Bool_2262;
            _m_Bool_2261 = hoisted__Bool_2262;
        } else {
            Bool hoisted__Bool_2263 = 0;
            (void)hoisted__Bool_2263;
            _m_Bool_2261 = hoisted__Bool_2263;
        }
    }
    return _m_Bool_2261;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2275 = Bool_eq(a, b);
    (void)hoisted__Bool_2275;
    if (hoisted__Bool_2275) {
        I64 hoisted__I64_2273 = 0;
        (void)hoisted__I64_2273;
        { I64 _ret_val = hoisted__I64_2273;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2274 = -1;
        (void)hoisted__I64_2274;
        return hoisted__I64_2274;
    }
    I64 hoisted__I64_2276 = 1;
    (void)hoisted__I64_2276;
    return hoisted__I64_2276;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2277 = 1;
    (void)hoisted__U32_2277;
    return hoisted__U32_2277;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2278 = 0;
    (void)hoisted__U32_2278;
    U64 hoisted__U64_2279 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2278); });
    (void)hoisted__U64_2279;
    return hoisted__U64_2279;
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
    Bool hoisted__Bool_2305 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2305;
    if (hoisted__Bool_2305) {
        Bool hoisted__Bool_2295 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2295;
        { Bool _ret_val = hoisted__Bool_2295;
                return _ret_val; }
    }
    Bool hoisted__Bool_2306 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2306;
    if (hoisted__Bool_2306) {
        Bool hoisted__Bool_2296 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2296;
        { Bool _ret_val = hoisted__Bool_2296;
                return _ret_val; }
    }
    Bool hoisted__Bool_2307 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2307;
    if (hoisted__Bool_2307) {
        Bool hoisted__Bool_2297 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2297;
        { Bool _ret_val = hoisted__Bool_2297;
                return _ret_val; }
    }
    Bool hoisted__Bool_2308 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2308;
    if (hoisted__Bool_2308) {
        Bool hoisted__Bool_2298 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2298;
        { Bool _ret_val = hoisted__Bool_2298;
                return _ret_val; }
    }
    Bool hoisted__Bool_2309 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2309;
    if (hoisted__Bool_2309) {
        Bool hoisted__Bool_2299 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2299;
        { Bool _ret_val = hoisted__Bool_2299;
                return _ret_val; }
    }
    Bool hoisted__Bool_2310 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2310;
    if (hoisted__Bool_2310) {
        Bool hoisted__Bool_2300 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2300;
        { Bool _ret_val = hoisted__Bool_2300;
                return _ret_val; }
    }
    Bool hoisted__Bool_2311 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        Bool hoisted__Bool_2301 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2301;
        { Bool _ret_val = hoisted__Bool_2301;
                return _ret_val; }
    }
    Bool hoisted__Bool_2312 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2312;
    if (hoisted__Bool_2312) {
        Bool hoisted__Bool_2302 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2302;
        { Bool _ret_val = hoisted__Bool_2302;
                return _ret_val; }
    }
    Bool hoisted__Bool_2313 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        Bool hoisted__Bool_2303 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2303;
        { Bool _ret_val = hoisted__Bool_2303;
                return _ret_val; }
    }
    Bool hoisted__Bool_2314 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2314;
    if (hoisted__Bool_2314) {
        Bool hoisted__Bool_2304 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2304;
        { Bool _ret_val = hoisted__Bool_2304;
                return _ret_val; }
    }
    Bool hoisted__Bool_2315 = 0;
    (void)hoisted__Bool_2315;
    return hoisted__Bool_2315;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2337 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2337;
    if (hoisted__Bool_2337) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2338 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2338;
    if (hoisted__Bool_2338) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2339 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2339;
    if (hoisted__Bool_2339) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2340 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2340;
    if (hoisted__Bool_2340) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2341 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2342 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2342;
    if (hoisted__Bool_2342) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2343 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2343;
    if (hoisted__Bool_2343) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2344 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2344;
    if (hoisted__Bool_2344) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2345 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2345;
    if (hoisted__Bool_2345) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2346 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2346;
    if (hoisted__Bool_2346) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2347 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2347;
    UNREACHABLE(&hoisted__Str_2347);
    Str_delete(&hoisted__Str_2347, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2348 = 4;
    (void)hoisted__U32_2348;
    return hoisted__U32_2348;
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
    Bool hoisted__Bool_2400 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2400;
    if (hoisted__Bool_2400) {
        Str *hoisted__Str_2390 = get_payload(self);
        (void)hoisted__Str_2390;
        (void)hoisted__Str_2390;
        Bool hoisted__Bool_2391 = 0;
        (void)hoisted__Bool_2391;
        Str_delete(hoisted__Str_2390, hoisted__Bool_2391);
    }
    Bool hoisted__Bool_2401 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2401;
    if (hoisted__Bool_2401) {
        Str *hoisted__Str_2392 = get_payload(self);
        (void)hoisted__Str_2392;
        (void)hoisted__Str_2392;
        Bool hoisted__Bool_2393 = 0;
        (void)hoisted__Bool_2393;
        Str_delete(hoisted__Str_2392, hoisted__Bool_2393);
    }
    Bool hoisted__Bool_2402 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2402;
    if (hoisted__Bool_2402) {
        Str *hoisted__Str_2394 = get_payload(self);
        (void)hoisted__Str_2394;
        (void)hoisted__Str_2394;
        Bool hoisted__Bool_2395 = 0;
        (void)hoisted__Bool_2395;
        Str_delete(hoisted__Str_2394, hoisted__Bool_2395);
    }
    Bool hoisted__Bool_2403 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2403;
    if (hoisted__Bool_2403) {
        Primitive *hoisted__Primitive_2396 = get_payload(self);
        (void)hoisted__Primitive_2396;
        (void)hoisted__Primitive_2396;
        Bool hoisted__Bool_2397 = 0;
        (void)hoisted__Bool_2397;
        Primitive_delete(hoisted__Primitive_2396, hoisted__Bool_2397);
    }
    Bool hoisted__Bool_2404 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2404;
    if (hoisted__Bool_2404) {
        Str *hoisted__Str_2398 = get_payload(self);
        (void)hoisted__Str_2398;
        (void)hoisted__Str_2398;
        Bool hoisted__Bool_2399 = 0;
        (void)hoisted__Bool_2399;
        Str_delete(hoisted__Str_2398, hoisted__Bool_2399);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2488 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2488;
    if (hoisted__Bool_2488) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2489 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2489;
    if (hoisted__Bool_2489) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2490 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2490;
    if (hoisted__Bool_2490) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2480 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2480;
        Type *hoisted__Type_2481 = Type_Struct(hoisted__Str_2480);
        (void)hoisted__Type_2481;
        { Type * _ret_val = hoisted__Type_2481;
                return _ret_val; }
    }
    Bool hoisted__Bool_2491 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2491;
    if (hoisted__Bool_2491) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2492 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2492;
    if (hoisted__Bool_2492) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2482 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2482;
        Type *hoisted__Type_2483 = Type_Enum(hoisted__Str_2482);
        (void)hoisted__Type_2483;
        { Type * _ret_val = hoisted__Type_2483;
                return _ret_val; }
    }
    Bool hoisted__Bool_2493 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2493;
    if (hoisted__Bool_2493) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2494 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2494;
    if (hoisted__Bool_2494) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2495 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2495;
    if (hoisted__Bool_2495) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2496 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2496;
    if (hoisted__Bool_2496) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2497 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2497;
    if (hoisted__Bool_2497) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2484 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2484;
        Type *hoisted__Type_2485 = Type_Custom(hoisted__Str_2484);
        (void)hoisted__Type_2485;
        { Type * _ret_val = hoisted__Type_2485;
                return _ret_val; }
    }
    Bool hoisted__Bool_2498 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2498;
    if (hoisted__Bool_2498) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2486 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2486;
        Type *hoisted__Type_2487 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2486; _oa; }));
        (void)hoisted__Type_2487;
        { Type * _ret_val = hoisted__Type_2487;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2499 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2499;
    Type *hoisted__Type_2500 = Type_FuncPtrSig(hoisted__Str_2499);
    (void)hoisted__Type_2500;
    return hoisted__Type_2500;
}

U32 Type_size(void) {
    U32 hoisted__U32_2501 = 24;
    (void)hoisted__U32_2501;
    return hoisted__U32_2501;
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
    Bool hoisted__Bool_2602 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2602;
    if (hoisted__Bool_2602) {
        Bool hoisted__Bool_2594 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2594;
        { Bool _ret_val = hoisted__Bool_2594;
                return _ret_val; }
    }
    Bool hoisted__Bool_2603 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2603;
    if (hoisted__Bool_2603) {
        Bool hoisted__Bool_2595 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2595;
        { Bool _ret_val = hoisted__Bool_2595;
                return _ret_val; }
    }
    Bool hoisted__Bool_2604 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2604;
    if (hoisted__Bool_2604) {
        Bool hoisted__Bool_2596 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2596;
        { Bool _ret_val = hoisted__Bool_2596;
                return _ret_val; }
    }
    Bool hoisted__Bool_2605 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2605;
    if (hoisted__Bool_2605) {
        Bool hoisted__Bool_2597 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2597;
        { Bool _ret_val = hoisted__Bool_2597;
                return _ret_val; }
    }
    Bool hoisted__Bool_2606 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2606;
    if (hoisted__Bool_2606) {
        Bool hoisted__Bool_2598 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2598;
        { Bool _ret_val = hoisted__Bool_2598;
                return _ret_val; }
    }
    Bool hoisted__Bool_2607 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2607;
    if (hoisted__Bool_2607) {
        Bool hoisted__Bool_2599 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2599;
        { Bool _ret_val = hoisted__Bool_2599;
                return _ret_val; }
    }
    Bool hoisted__Bool_2608 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2608;
    if (hoisted__Bool_2608) {
        Bool hoisted__Bool_2600 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2600;
        { Bool _ret_val = hoisted__Bool_2600;
                return _ret_val; }
    }
    Bool hoisted__Bool_2609 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2609;
    if (hoisted__Bool_2609) {
        Bool hoisted__Bool_2601 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2601;
        { Bool _ret_val = hoisted__Bool_2601;
                return _ret_val; }
    }
    Bool hoisted__Bool_2610 = 0;
    (void)hoisted__Bool_2610;
    return hoisted__Bool_2610;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2628 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2628;
    if (hoisted__Bool_2628) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2629 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2629;
    if (hoisted__Bool_2629) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2630 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2630;
    if (hoisted__Bool_2630) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2631 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2631;
    if (hoisted__Bool_2631) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2632 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2632;
    if (hoisted__Bool_2632) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2633 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2633;
    if (hoisted__Bool_2633) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2634 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2634;
    if (hoisted__Bool_2634) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2635 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2635;
    if (hoisted__Bool_2635) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    static Str hoisted__Str_2636 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2636;
    UNREACHABLE(&hoisted__Str_2636);
    Str_delete(&hoisted__Str_2636, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2637 = 4;
    (void)hoisted__U32_2637;
    return hoisted__U32_2637;
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
    Bool hoisted__Bool_2642 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2642;
    if (hoisted__Bool_2642) {
        Bool hoisted__Bool_2639 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2639;
        { Bool _ret_val = hoisted__Bool_2639;
                return _ret_val; }
    }
    Bool hoisted__Bool_2643 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2643;
    if (hoisted__Bool_2643) {
        Bool hoisted__Bool_2640 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2640;
        { Bool _ret_val = hoisted__Bool_2640;
                return _ret_val; }
    }
    Bool hoisted__Bool_2644 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2644;
    if (hoisted__Bool_2644) {
        Bool hoisted__Bool_2641 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2641;
        { Bool _ret_val = hoisted__Bool_2641;
                return _ret_val; }
    }
    Bool hoisted__Bool_2645 = 0;
    (void)hoisted__Bool_2645;
    return hoisted__Bool_2645;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2653 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2653;
    if (hoisted__Bool_2653) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2654 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2654;
    if (hoisted__Bool_2654) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2655 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2655;
    if (hoisted__Bool_2655) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2656 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2656;
    UNREACHABLE(&hoisted__Str_2656);
    Str_delete(&hoisted__Str_2656, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2657 = 4;
    (void)hoisted__U32_2657;
    return hoisted__U32_2657;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2659 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2659;
    Declaration *hoisted__Declaration_2660 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2660->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2660->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2660->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2660->is_mut = self->is_mut;
    hoisted__Declaration_2660->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2660->is_priv = self->is_priv;
    hoisted__Declaration_2660->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2660->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2660->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2660->default_value = hoisted__Expr_2659;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2660->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2660;
    return hoisted__Declaration_2660;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2661 = 0;
    (void)hoisted__Bool_2661;
    Str_delete(&self->name, hoisted__Bool_2661);
    Bool hoisted__Bool_2662 = 0;
    (void)hoisted__Bool_2662;
    Str_delete(&self->doc, hoisted__Bool_2662);
    Bool hoisted__Bool_2663 = 0;
    (void)hoisted__Bool_2663;
    Str_delete(&self->explicit_type, hoisted__Bool_2663);
    Bool hoisted__Bool_2664 = 0;
    (void)hoisted__Bool_2664;
    Bool_delete(&self->is_mut, hoisted__Bool_2664);
    Bool hoisted__Bool_2665 = 0;
    (void)hoisted__Bool_2665;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2665);
    Bool hoisted__Bool_2666 = 0;
    (void)hoisted__Bool_2666;
    Bool_delete(&self->is_priv, hoisted__Bool_2666);
    Bool hoisted__Bool_2667 = 0;
    (void)hoisted__Bool_2667;
    Bool_delete(&self->used, hoisted__Bool_2667);
    Bool hoisted__Bool_2668 = 0;
    (void)hoisted__Bool_2668;
    OwnType_delete(&self->own_type, hoisted__Bool_2668);
    Bool hoisted__Bool_2669 = 0;
    (void)hoisted__Bool_2669;
    Type_delete(&self->til_type, hoisted__Bool_2669);
    Bool hoisted__Bool_2670 = 1;
    (void)hoisted__Bool_2670;
    Expr_delete(self->default_value, hoisted__Bool_2670);
    Bool hoisted__Bool_2671 = 0;
    (void)hoisted__Bool_2671;
    Str_delete(&self->orig_name, hoisted__Bool_2671);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2672 = 104;
    (void)hoisted__U32_2672;
    return hoisted__U32_2672;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2674 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2674->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2674->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2674->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2674->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2674->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2674->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2674->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2674->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2674->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2674->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2674->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2674;
    return hoisted__FunctionDef_2674;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2675 = 0;
    (void)hoisted__Bool_2675;
    FuncType_delete(&self->func_type, hoisted__Bool_2675);
    Bool hoisted__Bool_2676 = 0;
    (void)hoisted__Bool_2676;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2676);
    Bool hoisted__Bool_2677 = 0;
    (void)hoisted__Bool_2677;
    Str_delete(&self->return_type, hoisted__Bool_2677);
    Bool hoisted__Bool_2678 = 0;
    (void)hoisted__Bool_2678;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2678);
    Bool hoisted__Bool_2679 = 0;
    (void)hoisted__Bool_2679;
    I32_delete(&self->variadic_index, hoisted__Bool_2679);
    Bool hoisted__Bool_2680 = 0;
    (void)hoisted__Bool_2680;
    I32_delete(&self->kwargs_index, hoisted__Bool_2680);
    Bool hoisted__Bool_2681 = 0;
    (void)hoisted__Bool_2681;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2681);
    Bool hoisted__Bool_2682 = 0;
    (void)hoisted__Bool_2682;
    Bool_delete(&self->auto_generated, hoisted__Bool_2682);
    Bool hoisted__Bool_2683 = 0;
    (void)hoisted__Bool_2683;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2683);
    Bool hoisted__Bool_2684 = 0;
    (void)hoisted__Bool_2684;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2684);
    Bool hoisted__Bool_2685 = 0;
    (void)hoisted__Bool_2685;
    Str_delete(&self->closure_name, hoisted__Bool_2685);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2686 = 0;
    (void)hoisted__U32_2686;
    U64 hoisted__U64_2687 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2686); });
    (void)hoisted__U64_2687;
    return hoisted__U64_2687;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2688 = 104;
    (void)hoisted__U32_2688;
    return hoisted__U32_2688;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2691 = malloc(sizeof(FCallData));
    hoisted__FCallData_2691->is_splat = self->is_splat;
    hoisted__FCallData_2691->does_throw = self->does_throw;
    hoisted__FCallData_2691->is_bang = self->is_bang;
    hoisted__FCallData_2691->own_args = self->own_args;
    hoisted__FCallData_2691->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2691->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2691;
    return hoisted__FCallData_2691;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2692 = 0;
    (void)hoisted__Bool_2692;
    Bool_delete(&self->is_splat, hoisted__Bool_2692);
    Bool hoisted__Bool_2693 = 0;
    (void)hoisted__Bool_2693;
    Bool_delete(&self->does_throw, hoisted__Bool_2693);
    Bool hoisted__Bool_2694 = 0;
    (void)hoisted__Bool_2694;
    Bool_delete(&self->is_bang, hoisted__Bool_2694);
    Bool hoisted__Bool_2695 = 0;
    (void)hoisted__Bool_2695;
    U64_delete(&self->own_args, hoisted__Bool_2695);
    Bool hoisted__Bool_2696 = 0;
    (void)hoisted__Bool_2696;
    Bool_delete(&self->swap_replace, hoisted__Bool_2696);
    Bool hoisted__Bool_2697 = 0;
    (void)hoisted__Bool_2697;
    Type_delete(&self->til_type, hoisted__Bool_2697);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2698 = 0;
    (void)hoisted__U32_2698;
    U64 hoisted__U64_2699 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2698); });
    (void)hoisted__U64_2699;
    return hoisted__U64_2699;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2700 = 48;
    (void)hoisted__U32_2700;
    return hoisted__U32_2700;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2712 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2712->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2712->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2712;
    return hoisted__LiteralNumData_2712;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2713 = 0;
    (void)hoisted__Bool_2713;
    Str_delete(&self->text, hoisted__Bool_2713);
    Bool hoisted__Bool_2714 = 0;
    (void)hoisted__Bool_2714;
    Type_delete(&self->til_type, hoisted__Bool_2714);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2715 = 0;
    (void)hoisted__U32_2715;
    U64 hoisted__U64_2716 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2715); });
    (void)hoisted__U64_2716;
    return hoisted__U64_2716;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2717 = 40;
    (void)hoisted__U32_2717;
    return hoisted__U32_2717;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2727 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2727->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2727->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2727;
    return hoisted__IdentData_2727;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2728 = 0;
    (void)hoisted__Bool_2728;
    Str_delete(&self->name, hoisted__Bool_2728);
    Bool hoisted__Bool_2729 = 0;
    (void)hoisted__Bool_2729;
    Type_delete(&self->til_type, hoisted__Bool_2729);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2730 = 0;
    (void)hoisted__U32_2730;
    U64 hoisted__U64_2731 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2730); });
    (void)hoisted__U64_2731;
    return hoisted__U64_2731;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2732 = 40;
    (void)hoisted__U32_2732;
    return hoisted__U32_2732;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2738 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2738->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2738->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2738;
    return hoisted__FieldAccessData_2738;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Str_delete(&self->name, hoisted__Bool_2739);
    Bool hoisted__Bool_2740 = 0;
    (void)hoisted__Bool_2740;
    Type_delete(&self->til_type, hoisted__Bool_2740);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2741 = 0;
    (void)hoisted__U32_2741;
    U64 hoisted__U64_2742 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2741); });
    (void)hoisted__U64_2742;
    return hoisted__U64_2742;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2743 = 40;
    (void)hoisted__U32_2743;
    return hoisted__U32_2743;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2824 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2824->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2824->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2824->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2824->is_interface = self->is_interface;
    hoisted__StructDef_2824->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2824->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2824;
    return hoisted__StructDef_2824;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2825 = 0;
    (void)hoisted__Bool_2825;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2825);
    Bool hoisted__Bool_2826 = 0;
    (void)hoisted__Bool_2826;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2826);
    Bool hoisted__Bool_2827 = 0;
    (void)hoisted__Bool_2827;
    Str_delete(&self->c_tag, hoisted__Bool_2827);
    Bool hoisted__Bool_2828 = 0;
    (void)hoisted__Bool_2828;
    Bool_delete(&self->is_interface, hoisted__Bool_2828);
    Bool hoisted__Bool_2829 = 0;
    (void)hoisted__Bool_2829;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2829);
    Bool hoisted__Bool_2830 = 0;
    (void)hoisted__Bool_2830;
    Str_delete(&self->implements_name, hoisted__Bool_2830);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2831 = 0;
    (void)hoisted__U32_2831;
    U64 hoisted__U64_2832 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2831); });
    (void)hoisted__U64_2832;
    return hoisted__U64_2832;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2833 = 72;
    (void)hoisted__U32_2833;
    return hoisted__U32_2833;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2838 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2838->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2838->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2838->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2838->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2838->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2838->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2838;
    return hoisted__EnumDef_2838;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2839 = 0;
    (void)hoisted__Bool_2839;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2839);
    Bool hoisted__Bool_2840 = 0;
    (void)hoisted__Bool_2840;
    Vec__Str_delete(&self->variants, hoisted__Bool_2840);
    Bool hoisted__Bool_2841 = 0;
    (void)hoisted__Bool_2841;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2841);
    Bool hoisted__Bool_2842 = 0;
    (void)hoisted__Bool_2842;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2842);
    Bool hoisted__Bool_2843 = 0;
    (void)hoisted__Bool_2843;
    Str_delete(&self->implements_name, hoisted__Bool_2843);
    Bool hoisted__Bool_2844 = 0;
    (void)hoisted__Bool_2844;
    Str_delete(&self->tag_type, hoisted__Bool_2844);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2845 = 0;
    (void)hoisted__U32_2845;
    U64 hoisted__U64_2846 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2845); });
    (void)hoisted__U64_2846;
    return hoisted__U64_2846;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2847 = 112;
    (void)hoisted__U32_2847;
    return hoisted__U32_2847;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2943 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2943->name = *_ca; free(_ca); }
    hoisted__AssignData_2943->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2943->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2943->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2943;
    return hoisted__AssignData_2943;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2944 = 0;
    (void)hoisted__Bool_2944;
    Str_delete(&self->name, hoisted__Bool_2944);
    Bool hoisted__Bool_2945 = 0;
    (void)hoisted__Bool_2945;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2945);
    Bool hoisted__Bool_2946 = 0;
    (void)hoisted__Bool_2946;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2946);
    Bool hoisted__Bool_2947 = 0;
    (void)hoisted__Bool_2947;
    Bool_delete(&self->swap_replace, hoisted__Bool_2947);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2948 = 0;
    (void)hoisted__U32_2948;
    U64 hoisted__U64_2949 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2948); });
    (void)hoisted__U64_2949;
    return hoisted__U64_2949;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2950 = 24;
    (void)hoisted__U32_2950;
    return hoisted__U32_2950;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2952 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2952->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2952->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2952;
    return hoisted__FieldAssignData_2952;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2953 = 0;
    (void)hoisted__Bool_2953;
    Str_delete(&self->name, hoisted__Bool_2953);
    Bool hoisted__Bool_2954 = 0;
    (void)hoisted__Bool_2954;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2954);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2955 = 0;
    (void)hoisted__U32_2955;
    U64 hoisted__U64_2956 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2955); });
    (void)hoisted__U64_2956;
    return hoisted__U64_2956;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2957 = 24;
    (void)hoisted__U32_2957;
    return hoisted__U32_2957;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2959 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2959->name = *_ca; free(_ca); }
    hoisted__ForInData_2959->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2959->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2959->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2959->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2959;
    return hoisted__ForInData_2959;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2960 = 0;
    (void)hoisted__Bool_2960;
    Str_delete(&self->name, hoisted__Bool_2960);
    Bool hoisted__Bool_2961 = 0;
    (void)hoisted__Bool_2961;
    Bool_delete(&self->is_mut, hoisted__Bool_2961);
    Bool hoisted__Bool_2962 = 0;
    (void)hoisted__Bool_2962;
    Type_delete(&self->til_type, hoisted__Bool_2962);
    Bool hoisted__Bool_2963 = 0;
    (void)hoisted__Bool_2963;
    Str_delete(&self->name2, hoisted__Bool_2963);
    Bool hoisted__Bool_2964 = 0;
    (void)hoisted__Bool_2964;
    Bool_delete(&self->is_mut2, hoisted__Bool_2964);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2965 = 0;
    (void)hoisted__U32_2965;
    U64 hoisted__U64_2966 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2965); });
    (void)hoisted__U64_2966;
    return hoisted__U64_2966;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2967 = 72;
    (void)hoisted__U32_2967;
    return hoisted__U32_2967;
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
    Bool hoisted__Bool_2997 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2997;
    if (hoisted__Bool_2997) {
        Str *hoisted__Str_2991 = get_payload(self);
        (void)hoisted__Str_2991;
        (void)hoisted__Str_2991;
        Bool hoisted__Bool_2992 = 0;
        (void)hoisted__Bool_2992;
        Str_delete(hoisted__Str_2991, hoisted__Bool_2992);
    }
    Bool hoisted__Bool_2998 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2998;
    if (hoisted__Bool_2998) {
        LiteralNumData *hoisted__LiteralNumData_2993 = get_payload(self);
        (void)hoisted__LiteralNumData_2993;
        (void)hoisted__LiteralNumData_2993;
        Bool hoisted__Bool_2994 = 0;
        (void)hoisted__Bool_2994;
        LiteralNumData_delete(hoisted__LiteralNumData_2993, hoisted__Bool_2994);
    }
    Bool hoisted__Bool_2999 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2999;
    if (hoisted__Bool_2999) {
        Bool *hoisted__Bool_2995 = get_payload(self);
        (void)hoisted__Bool_2995;
        (void)hoisted__Bool_2995;
        Bool hoisted__Bool_2996 = 0;
        (void)hoisted__Bool_2996;
        Bool_delete(hoisted__Bool_2995, hoisted__Bool_2996);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_3048 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_3048;
    if (hoisted__Bool_3048) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3043 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3043;
        Literal *hoisted__Literal_3044 = Literal_Str(hoisted__Str_3043);
        (void)hoisted__Literal_3044;
        { Literal * _ret_val = hoisted__Literal_3044;
                return _ret_val; }
    }
    Bool hoisted__Bool_3049 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_3049;
    if (hoisted__Bool_3049) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3045 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3045;
        Literal *hoisted__Literal_3046 = Literal_Num(hoisted__LiteralNumData_3045);
        (void)hoisted__Literal_3046;
        { Literal * _ret_val = hoisted__Literal_3046;
                return _ret_val; }
    }
    Bool hoisted__Bool_3050 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_3050;
    if (hoisted__Bool_3050) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3047 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3047;
        { Literal * _ret_val = hoisted__Literal_3047;
                return _ret_val; }
    }
    Bool hoisted__Bool_3051 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_3051;
    if (hoisted__Bool_3051) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_3052 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_3052;
    if (hoisted__Bool_3052) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3053 = 48;
    (void)hoisted__U32_3053;
    return hoisted__U32_3053;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3056 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3056->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3056->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3056;
    return hoisted__MatchData_3056;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3057 = 0;
    (void)hoisted__Bool_3057;
    Type_delete(&self->til_type, hoisted__Bool_3057);
    Bool hoisted__Bool_3058 = 0;
    (void)hoisted__Bool_3058;
    Str_delete(&self->result_temp, hoisted__Bool_3058);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3059 = 0;
    (void)hoisted__U32_3059;
    U64 hoisted__U64_3060 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3059); });
    (void)hoisted__U64_3060;
    return hoisted__U64_3060;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3061 = 40;
    (void)hoisted__U32_3061;
    return hoisted__U32_3061;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3066 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3066->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3066;
    return hoisted__CaptureBlockData_3066;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3067 = 0;
    (void)hoisted__Bool_3067;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3067);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3068 = 0;
    (void)hoisted__U32_3068;
    U64 hoisted__U64_3069 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3068); });
    (void)hoisted__U64_3069;
    return hoisted__U64_3069;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3070 = 16;
    (void)hoisted__U32_3070;
    return hoisted__U32_3070;
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
    Bool hoisted__Bool_3249 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3249;
    if (hoisted__Bool_3249) {
        Literal *hoisted__Literal_3221 = get_payload(self);
        (void)hoisted__Literal_3221;
        (void)hoisted__Literal_3221;
        Bool hoisted__Bool_3222 = 0;
        (void)hoisted__Bool_3222;
        Literal_delete(hoisted__Literal_3221, hoisted__Bool_3222);
    }
    Bool hoisted__Bool_3250 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3250;
    if (hoisted__Bool_3250) {
        IdentData *hoisted__IdentData_3223 = get_payload(self);
        (void)hoisted__IdentData_3223;
        (void)hoisted__IdentData_3223;
        Bool hoisted__Bool_3224 = 0;
        (void)hoisted__Bool_3224;
        IdentData_delete(hoisted__IdentData_3223, hoisted__Bool_3224);
    }
    Bool hoisted__Bool_3251 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3251;
    if (hoisted__Bool_3251) {
        Declaration *hoisted__Declaration_3225 = get_payload(self);
        (void)hoisted__Declaration_3225;
        (void)hoisted__Declaration_3225;
        Bool hoisted__Bool_3226 = 0;
        (void)hoisted__Bool_3226;
        Declaration_delete(hoisted__Declaration_3225, hoisted__Bool_3226);
    }
    Bool hoisted__Bool_3252 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3252;
    if (hoisted__Bool_3252) {
        AssignData *hoisted__AssignData_3227 = get_payload(self);
        (void)hoisted__AssignData_3227;
        (void)hoisted__AssignData_3227;
        Bool hoisted__Bool_3228 = 0;
        (void)hoisted__Bool_3228;
        AssignData_delete(hoisted__AssignData_3227, hoisted__Bool_3228);
    }
    Bool hoisted__Bool_3253 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3253;
    if (hoisted__Bool_3253) {
        FCallData *hoisted__FCallData_3229 = get_payload(self);
        (void)hoisted__FCallData_3229;
        (void)hoisted__FCallData_3229;
        Bool hoisted__Bool_3230 = 0;
        (void)hoisted__Bool_3230;
        FCallData_delete(hoisted__FCallData_3229, hoisted__Bool_3230);
    }
    Bool hoisted__Bool_3254 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3254;
    if (hoisted__Bool_3254) {
        FunctionDef *hoisted__FunctionDef_3231 = get_payload(self);
        (void)hoisted__FunctionDef_3231;
        (void)hoisted__FunctionDef_3231;
        Bool hoisted__Bool_3232 = 0;
        (void)hoisted__Bool_3232;
        FunctionDef_delete(hoisted__FunctionDef_3231, hoisted__Bool_3232);
    }
    Bool hoisted__Bool_3255 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3255;
    if (hoisted__Bool_3255) {
        StructDef *hoisted__StructDef_3233 = get_payload(self);
        (void)hoisted__StructDef_3233;
        (void)hoisted__StructDef_3233;
        Bool hoisted__Bool_3234 = 0;
        (void)hoisted__Bool_3234;
        StructDef_delete(hoisted__StructDef_3233, hoisted__Bool_3234);
    }
    Bool hoisted__Bool_3256 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3256;
    if (hoisted__Bool_3256) {
        EnumDef *hoisted__EnumDef_3235 = get_payload(self);
        (void)hoisted__EnumDef_3235;
        (void)hoisted__EnumDef_3235;
        Bool hoisted__Bool_3236 = 0;
        (void)hoisted__Bool_3236;
        EnumDef_delete(hoisted__EnumDef_3235, hoisted__Bool_3236);
    }
    Bool hoisted__Bool_3257 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3257;
    if (hoisted__Bool_3257) {
        FieldAccessData *hoisted__FieldAccessData_3237 = get_payload(self);
        (void)hoisted__FieldAccessData_3237;
        (void)hoisted__FieldAccessData_3237;
        Bool hoisted__Bool_3238 = 0;
        (void)hoisted__Bool_3238;
        FieldAccessData_delete(hoisted__FieldAccessData_3237, hoisted__Bool_3238);
    }
    Bool hoisted__Bool_3258 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3258;
    if (hoisted__Bool_3258) {
        FieldAssignData *hoisted__FieldAssignData_3239 = get_payload(self);
        (void)hoisted__FieldAssignData_3239;
        (void)hoisted__FieldAssignData_3239;
        Bool hoisted__Bool_3240 = 0;
        (void)hoisted__Bool_3240;
        FieldAssignData_delete(hoisted__FieldAssignData_3239, hoisted__Bool_3240);
    }
    Bool hoisted__Bool_3259 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3259;
    if (hoisted__Bool_3259) {
        ForInData *hoisted__ForInData_3241 = get_payload(self);
        (void)hoisted__ForInData_3241;
        (void)hoisted__ForInData_3241;
        Bool hoisted__Bool_3242 = 0;
        (void)hoisted__Bool_3242;
        ForInData_delete(hoisted__ForInData_3241, hoisted__Bool_3242);
    }
    Bool hoisted__Bool_3260 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3260;
    if (hoisted__Bool_3260) {
        Str *hoisted__Str_3243 = get_payload(self);
        (void)hoisted__Str_3243;
        (void)hoisted__Str_3243;
        Bool hoisted__Bool_3244 = 0;
        (void)hoisted__Bool_3244;
        Str_delete(hoisted__Str_3243, hoisted__Bool_3244);
    }
    Bool hoisted__Bool_3261 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3261;
    if (hoisted__Bool_3261) {
        MatchData *hoisted__MatchData_3245 = get_payload(self);
        (void)hoisted__MatchData_3245;
        (void)hoisted__MatchData_3245;
        Bool hoisted__Bool_3246 = 0;
        (void)hoisted__Bool_3246;
        MatchData_delete(hoisted__MatchData_3245, hoisted__Bool_3246);
    }
    Bool hoisted__Bool_3262 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3262;
    if (hoisted__Bool_3262) {
        CaptureBlockData *hoisted__CaptureBlockData_3247 = get_payload(self);
        (void)hoisted__CaptureBlockData_3247;
        (void)hoisted__CaptureBlockData_3247;
        Bool hoisted__Bool_3248 = 0;
        (void)hoisted__Bool_3248;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3247, hoisted__Bool_3248);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3486 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3486;
    if (hoisted__Bool_3486) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3487 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3487;
    if (hoisted__Bool_3487) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3458 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3458;
        NodeType *hoisted__NodeType_3459 = NodeType_Literal(hoisted__Literal_3458);
        (void)hoisted__NodeType_3459;
        { NodeType * _ret_val = hoisted__NodeType_3459;
                return _ret_val; }
    }
    Bool hoisted__Bool_3488 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3488;
    if (hoisted__Bool_3488) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3460 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3460;
        NodeType *hoisted__NodeType_3461 = NodeType_Ident(hoisted__IdentData_3460);
        (void)hoisted__NodeType_3461;
        { NodeType * _ret_val = hoisted__NodeType_3461;
                return _ret_val; }
    }
    Bool hoisted__Bool_3489 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3489;
    if (hoisted__Bool_3489) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3462 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3462;
        NodeType *hoisted__NodeType_3463 = NodeType_Decl(hoisted__Declaration_3462);
        (void)hoisted__NodeType_3463;
        { NodeType * _ret_val = hoisted__NodeType_3463;
                return _ret_val; }
    }
    Bool hoisted__Bool_3490 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3490;
    if (hoisted__Bool_3490) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3464 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3464;
        NodeType *hoisted__NodeType_3465 = NodeType_Assign(hoisted__AssignData_3464);
        (void)hoisted__NodeType_3465;
        { NodeType * _ret_val = hoisted__NodeType_3465;
                return _ret_val; }
    }
    Bool hoisted__Bool_3491 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3491;
    if (hoisted__Bool_3491) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3466 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3466;
        NodeType *hoisted__NodeType_3467 = NodeType_FCall(hoisted__FCallData_3466);
        (void)hoisted__NodeType_3467;
        { NodeType * _ret_val = hoisted__NodeType_3467;
                return _ret_val; }
    }
    Bool hoisted__Bool_3492 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3492;
    if (hoisted__Bool_3492) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3468 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3468;
        NodeType *hoisted__NodeType_3469 = NodeType_FuncDef(hoisted__FunctionDef_3468);
        (void)hoisted__NodeType_3469;
        { NodeType * _ret_val = hoisted__NodeType_3469;
                return _ret_val; }
    }
    Bool hoisted__Bool_3493 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3493;
    if (hoisted__Bool_3493) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3470 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3470;
        NodeType *hoisted__NodeType_3471 = NodeType_StructDef(hoisted__StructDef_3470);
        (void)hoisted__NodeType_3471;
        { NodeType * _ret_val = hoisted__NodeType_3471;
                return _ret_val; }
    }
    Bool hoisted__Bool_3494 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3494;
    if (hoisted__Bool_3494) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3472 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3472;
        NodeType *hoisted__NodeType_3473 = NodeType_EnumDef(hoisted__EnumDef_3472);
        (void)hoisted__NodeType_3473;
        { NodeType * _ret_val = hoisted__NodeType_3473;
                return _ret_val; }
    }
    Bool hoisted__Bool_3495 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3495;
    if (hoisted__Bool_3495) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3474 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3474;
        NodeType *hoisted__NodeType_3475 = NodeType_FieldAccess(hoisted__FieldAccessData_3474);
        (void)hoisted__NodeType_3475;
        { NodeType * _ret_val = hoisted__NodeType_3475;
                return _ret_val; }
    }
    Bool hoisted__Bool_3496 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3496;
    if (hoisted__Bool_3496) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3476 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3476;
        NodeType *hoisted__NodeType_3477 = NodeType_FieldAssign(hoisted__FieldAssignData_3476);
        (void)hoisted__NodeType_3477;
        { NodeType * _ret_val = hoisted__NodeType_3477;
                return _ret_val; }
    }
    Bool hoisted__Bool_3497 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3497;
    if (hoisted__Bool_3497) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3498 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3498;
    if (hoisted__Bool_3498) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3499 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3499;
    if (hoisted__Bool_3499) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3500 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3500;
    if (hoisted__Bool_3500) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3478 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3478;
        NodeType *hoisted__NodeType_3479 = NodeType_ForIn(hoisted__ForInData_3478);
        (void)hoisted__NodeType_3479;
        { NodeType * _ret_val = hoisted__NodeType_3479;
                return _ret_val; }
    }
    Bool hoisted__Bool_3501 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3501;
    if (hoisted__Bool_3501) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3480 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3480;
        NodeType *hoisted__NodeType_3481 = NodeType_NamedArg(hoisted__Str_3480);
        (void)hoisted__NodeType_3481;
        { NodeType * _ret_val = hoisted__NodeType_3481;
                return _ret_val; }
    }
    Bool hoisted__Bool_3502 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3502;
    if (hoisted__Bool_3502) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3503 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3503;
    if (hoisted__Bool_3503) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3504 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3504;
    if (hoisted__Bool_3504) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3505 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3505;
    if (hoisted__Bool_3505) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3482 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3482;
        NodeType *hoisted__NodeType_3483 = NodeType_Match(hoisted__MatchData_3482);
        (void)hoisted__NodeType_3483;
        { NodeType * _ret_val = hoisted__NodeType_3483;
                return _ret_val; }
    }
    Bool hoisted__Bool_3506 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3506;
    if (hoisted__Bool_3506) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3507 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3507;
    if (hoisted__Bool_3507) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3508 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3508;
    if (hoisted__Bool_3508) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3509 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3509;
    if (hoisted__Bool_3509) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3510 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3510;
    if (hoisted__Bool_3510) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3511 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3511;
    if (hoisted__Bool_3511) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3484 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3484;
        NodeType *hoisted__NodeType_3485 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3484);
        (void)hoisted__NodeType_3485;
        { NodeType * _ret_val = hoisted__NodeType_3485;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3512 = 120;
    (void)hoisted__U32_3512;
    return hoisted__U32_3512;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3513 = is_null(self);
    (void)hoisted__Bool_3513;
    if (hoisted__Bool_3513) {
        return;
    }
    Bool hoisted__Bool_3514 = 0;
    (void)hoisted__Bool_3514;
    NodeType_delete(&self->node_type, hoisted__Bool_3514);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3567 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3567->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3567->children = *_ca; free(_ca); }
    hoisted__Expr_3567->line = line;
    hoisted__Expr_3567->col = col;
    (void)hoisted__Expr_3567;
    return hoisted__Expr_3567;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3576 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3576->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3576->children = *_ca; free(_ca); }
    hoisted__Expr_3576->line = self->line;
    hoisted__Expr_3576->col = self->col;
    (void)hoisted__Expr_3576;
    return hoisted__Expr_3576;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3577 = 0;
    (void)hoisted__U32_3577;
    U64 hoisted__U64_3578 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3577); });
    (void)hoisted__U64_3578;
    return hoisted__U64_3578;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3579 = 144;
    (void)hoisted__U32_3579;
    return hoisted__U32_3579;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4311 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4311->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4311->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4311;
    return hoisted__Map__I64_Str_4311;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4438 = 0;
    (void)hoisted__Bool_4438;
    Vec__I64_delete(&self->keys, hoisted__Bool_4438);
    Bool hoisted__Bool_4439 = 0;
    (void)hoisted__Bool_4439;
    Vec__Str_delete(&self->values, hoisted__Bool_4439);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4440 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4440->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4440->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4440;
    return hoisted__Map__I64_Str_4440;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4441 = 0;
    (void)hoisted__U32_4441;
    U64 hoisted__U64_4442 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4441); });
    (void)hoisted__U64_4442;
    return hoisted__U64_4442;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4443 = 32;
    (void)hoisted__U32_4443;
    return hoisted__U32_4443;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4444 = 1;
    (void)hoisted__U32_4444;
    Type *hoisted__Type_4445 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4445;
    U64 hoisted__U64_4446 = (U64)(hoisted__U32_4444);
    (void)hoisted__U64_4446;
    Type_delete(hoisted__Type_4445, 1);
    void * hoisted__v_4447 = malloc(hoisted__U64_4446);
    (void)hoisted__v_4447;
    U32 hoisted__U32_4448 = 0;
    (void)hoisted__U32_4448;
    I64 hoisted__I64_4449 = 1;
    (void)hoisted__I64_4449;
    Vec__Bool *hoisted__Vec__Bool_4450 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4450->data = hoisted__v_4447;
    hoisted__Vec__Bool_4450->count = hoisted__U32_4448;
    hoisted__Vec__Bool_4450->cap = hoisted__I64_4449;
    (void)hoisted__Vec__Bool_4450;
    return hoisted__Vec__Bool_4450;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4451 = self->count;
        (void)_re_U32_4451;
        U32 _rc_U32_4451 = 0;
        (void)_rc_U32_4451;
        Bool hoisted__Bool_4466 = U32_lte(_rc_U32_4451, _re_U32_4451);
        (void)hoisted__Bool_4466;
        if (hoisted__Bool_4466) {
            while (1) {
                Bool _wcond_Bool_4452 = U32_lt(_rc_U32_4451, _re_U32_4451);
                (void)_wcond_Bool_4452;
                if (_wcond_Bool_4452) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4451);
                U32_inc(&_rc_U32_4451);
                U32 hoisted__U32_4453 = 1;
                (void)hoisted__U32_4453;
                U32 hoisted__U32_4454 = U32_mul(i, hoisted__U32_4453);
                (void)hoisted__U32_4454;
                Type *hoisted__Type_4455 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4455;
                U64 hoisted__U64_4456 = (U64)(hoisted__U32_4454);
                (void)hoisted__U64_4456;
                Type_delete(hoisted__Type_4455, 1);
                Bool *hoisted__Bool_4457 = ptr_add(self->data, hoisted__U64_4456);
                (void)hoisted__Bool_4457;
                (void)hoisted__Bool_4457;
                Bool hoisted__Bool_4458 = 0;
                (void)hoisted__Bool_4458;
                Bool_delete(hoisted__Bool_4457, hoisted__Bool_4458);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4459 = U32_gt(_rc_U32_4451, _re_U32_4451);
                (void)_wcond_Bool_4459;
                if (_wcond_Bool_4459) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4451);
                U32_dec(&_rc_U32_4451);
                U32 hoisted__U32_4460 = 1;
                (void)hoisted__U32_4460;
                U32 hoisted__U32_4461 = U32_mul(i, hoisted__U32_4460);
                (void)hoisted__U32_4461;
                Type *hoisted__Type_4462 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4462;
                U64 hoisted__U64_4463 = (U64)(hoisted__U32_4461);
                (void)hoisted__U64_4463;
                Type_delete(hoisted__Type_4462, 1);
                Bool *hoisted__Bool_4464 = ptr_add(self->data, hoisted__U64_4463);
                (void)hoisted__Bool_4464;
                (void)hoisted__Bool_4464;
                Bool hoisted__Bool_4465 = 0;
                (void)hoisted__Bool_4465;
                Bool_delete(hoisted__Bool_4464, hoisted__Bool_4465);
            }
        }
    }
    U32 hoisted__U32_4467 = 0;
    (void)hoisted__U32_4467;
    self->count = hoisted__U32_4467;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4776 = 1;
    (void)hoisted__U32_4776;
    U32 hoisted__U32_4777 = U32_mul(self->cap, hoisted__U32_4776);
    (void)hoisted__U32_4777;
    Type *hoisted__Type_4778 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4778;
    U64 hoisted__U64_4779 = (U64)(hoisted__U32_4777);
    (void)hoisted__U64_4779;
    Type_delete(hoisted__Type_4778, 1);
    void * new_data = malloc(hoisted__U64_4779);
    {
        U32 _re_U32_4740 = self->count;
        (void)_re_U32_4740;
        U32 _rc_U32_4740 = 0;
        (void)_rc_U32_4740;
        Bool hoisted__Bool_4775 = U32_lte(_rc_U32_4740, _re_U32_4740);
        (void)hoisted__Bool_4775;
        if (hoisted__Bool_4775) {
            while (1) {
                Bool _wcond_Bool_4741 = U32_lt(_rc_U32_4740, _re_U32_4740);
                (void)_wcond_Bool_4741;
                if (_wcond_Bool_4741) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4740);
                U32_inc(&_rc_U32_4740);
                U32 hoisted__U32_4742 = 1;
                (void)hoisted__U32_4742;
                U32 hoisted__U32_4743 = U32_mul(i, hoisted__U32_4742);
                (void)hoisted__U32_4743;
                Type *hoisted__Type_4744 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4744;
                U64 hoisted__U64_4745 = (U64)(hoisted__U32_4743);
                (void)hoisted__U64_4745;
                Type_delete(hoisted__Type_4744, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4745);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4746 = 1;
                (void)hoisted__U32_4746;
                U32 hoisted__U32_4747 = U32_mul(i, hoisted__U32_4746);
                (void)hoisted__U32_4747;
                Type *hoisted__Type_4748 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4748;
                U64 hoisted__U64_4749 = (U64)(hoisted__U32_4747);
                (void)hoisted__U64_4749;
                Type_delete(hoisted__Type_4748, 1);
                U32 hoisted__U32_4750 = 1;
                (void)hoisted__U32_4750;
                Type *hoisted__Type_4751 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4751;
                void *hoisted__v_4752 = ptr_add(new_data, hoisted__U64_4749);
                (void)hoisted__v_4752;
                (void)hoisted__v_4752;
                U64 hoisted__U64_4753 = (U64)(hoisted__U32_4750);
                (void)hoisted__U64_4753;
                Type_delete(hoisted__Type_4751, 1);
                memcpy(hoisted__v_4752, &cloned, hoisted__U64_4753);
                U32 hoisted__U32_4754 = 1;
                (void)hoisted__U32_4754;
                Type *hoisted__Type_4755 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4755;
                I32 hoisted__I32_4756 = 0;
                (void)hoisted__I32_4756;
                U64 hoisted__U64_4757 = (U64)(hoisted__U32_4754);
                (void)hoisted__U64_4757;
                Type_delete(hoisted__Type_4755, 1);
                memset(&cloned, hoisted__I32_4756, hoisted__U64_4757);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4758 = U32_gt(_rc_U32_4740, _re_U32_4740);
                (void)_wcond_Bool_4758;
                if (_wcond_Bool_4758) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4740);
                U32_dec(&_rc_U32_4740);
                U32 hoisted__U32_4759 = 1;
                (void)hoisted__U32_4759;
                U32 hoisted__U32_4760 = U32_mul(i, hoisted__U32_4759);
                (void)hoisted__U32_4760;
                Type *hoisted__Type_4761 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4761;
                U64 hoisted__U64_4762 = (U64)(hoisted__U32_4760);
                (void)hoisted__U64_4762;
                Type_delete(hoisted__Type_4761, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4762);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4763 = 1;
                (void)hoisted__U32_4763;
                U32 hoisted__U32_4764 = U32_mul(i, hoisted__U32_4763);
                (void)hoisted__U32_4764;
                Type *hoisted__Type_4765 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4765;
                U64 hoisted__U64_4766 = (U64)(hoisted__U32_4764);
                (void)hoisted__U64_4766;
                Type_delete(hoisted__Type_4765, 1);
                U32 hoisted__U32_4767 = 1;
                (void)hoisted__U32_4767;
                Type *hoisted__Type_4768 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4768;
                void *hoisted__v_4769 = ptr_add(new_data, hoisted__U64_4766);
                (void)hoisted__v_4769;
                (void)hoisted__v_4769;
                U64 hoisted__U64_4770 = (U64)(hoisted__U32_4767);
                (void)hoisted__U64_4770;
                Type_delete(hoisted__Type_4768, 1);
                memcpy(hoisted__v_4769, &cloned, hoisted__U64_4770);
                U32 hoisted__U32_4771 = 1;
                (void)hoisted__U32_4771;
                Type *hoisted__Type_4772 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4772;
                I32 hoisted__I32_4773 = 0;
                (void)hoisted__I32_4773;
                U64 hoisted__U64_4774 = (U64)(hoisted__U32_4771);
                (void)hoisted__U64_4774;
                Type_delete(hoisted__Type_4772, 1);
                memset(&cloned, hoisted__I32_4773, hoisted__U64_4774);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4780 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4780->data = new_data;
    hoisted__Vec__Bool_4780->count = self->count;
    hoisted__Vec__Bool_4780->cap = self->cap;
    (void)hoisted__Vec__Bool_4780;
    return hoisted__Vec__Bool_4780;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4781 = 16;
    (void)hoisted__U32_4781;
    return hoisted__U32_4781;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5120 = 104;
    (void)hoisted__U32_5120;
    Type *hoisted__Type_5121 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5121;
    U64 hoisted__U64_5122 = (U64)(hoisted__U32_5120);
    (void)hoisted__U64_5122;
    Type_delete(hoisted__Type_5121, 1);
    void * hoisted__v_5123 = malloc(hoisted__U64_5122);
    (void)hoisted__v_5123;
    U32 hoisted__U32_5124 = 0;
    (void)hoisted__U32_5124;
    I64 hoisted__I64_5125 = 1;
    (void)hoisted__I64_5125;
    Vec__Declaration *hoisted__Vec__Declaration_5126 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5126->data = hoisted__v_5123;
    hoisted__Vec__Declaration_5126->count = hoisted__U32_5124;
    hoisted__Vec__Declaration_5126->cap = hoisted__I64_5125;
    (void)hoisted__Vec__Declaration_5126;
    return hoisted__Vec__Declaration_5126;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5127 = self->count;
        (void)_re_U32_5127;
        U32 _rc_U32_5127 = 0;
        (void)_rc_U32_5127;
        Bool hoisted__Bool_5142 = U32_lte(_rc_U32_5127, _re_U32_5127);
        (void)hoisted__Bool_5142;
        if (hoisted__Bool_5142) {
            while (1) {
                Bool _wcond_Bool_5128 = U32_lt(_rc_U32_5127, _re_U32_5127);
                (void)_wcond_Bool_5128;
                if (_wcond_Bool_5128) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5127);
                U32_inc(&_rc_U32_5127);
                U32 hoisted__U32_5129 = 104;
                (void)hoisted__U32_5129;
                U32 hoisted__U32_5130 = U32_mul(i, hoisted__U32_5129);
                (void)hoisted__U32_5130;
                Type *hoisted__Type_5131 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5131;
                U64 hoisted__U64_5132 = (U64)(hoisted__U32_5130);
                (void)hoisted__U64_5132;
                Type_delete(hoisted__Type_5131, 1);
                Declaration *hoisted__Declaration_5133 = ptr_add(self->data, hoisted__U64_5132);
                (void)hoisted__Declaration_5133;
                (void)hoisted__Declaration_5133;
                Bool hoisted__Bool_5134 = 0;
                (void)hoisted__Bool_5134;
                Declaration_delete(hoisted__Declaration_5133, hoisted__Bool_5134);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5135 = U32_gt(_rc_U32_5127, _re_U32_5127);
                (void)_wcond_Bool_5135;
                if (_wcond_Bool_5135) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5127);
                U32_dec(&_rc_U32_5127);
                U32 hoisted__U32_5136 = 104;
                (void)hoisted__U32_5136;
                U32 hoisted__U32_5137 = U32_mul(i, hoisted__U32_5136);
                (void)hoisted__U32_5137;
                Type *hoisted__Type_5138 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5138;
                U64 hoisted__U64_5139 = (U64)(hoisted__U32_5137);
                (void)hoisted__U64_5139;
                Type_delete(hoisted__Type_5138, 1);
                Declaration *hoisted__Declaration_5140 = ptr_add(self->data, hoisted__U64_5139);
                (void)hoisted__Declaration_5140;
                (void)hoisted__Declaration_5140;
                Bool hoisted__Bool_5141 = 0;
                (void)hoisted__Bool_5141;
                Declaration_delete(hoisted__Declaration_5140, hoisted__Bool_5141);
            }
        }
    }
    U32 hoisted__U32_5143 = 0;
    (void)hoisted__U32_5143;
    self->count = hoisted__U32_5143;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5452 = 104;
    (void)hoisted__U32_5452;
    U32 hoisted__U32_5453 = U32_mul(self->cap, hoisted__U32_5452);
    (void)hoisted__U32_5453;
    Type *hoisted__Type_5454 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5454;
    U64 hoisted__U64_5455 = (U64)(hoisted__U32_5453);
    (void)hoisted__U64_5455;
    Type_delete(hoisted__Type_5454, 1);
    void * new_data = malloc(hoisted__U64_5455);
    {
        U32 _re_U32_5416 = self->count;
        (void)_re_U32_5416;
        U32 _rc_U32_5416 = 0;
        (void)_rc_U32_5416;
        Bool hoisted__Bool_5451 = U32_lte(_rc_U32_5416, _re_U32_5416);
        (void)hoisted__Bool_5451;
        if (hoisted__Bool_5451) {
            while (1) {
                Bool _wcond_Bool_5417 = U32_lt(_rc_U32_5416, _re_U32_5416);
                (void)_wcond_Bool_5417;
                if (_wcond_Bool_5417) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5416);
                U32_inc(&_rc_U32_5416);
                U32 hoisted__U32_5418 = 104;
                (void)hoisted__U32_5418;
                U32 hoisted__U32_5419 = U32_mul(i, hoisted__U32_5418);
                (void)hoisted__U32_5419;
                Type *hoisted__Type_5420 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5420;
                U64 hoisted__U64_5421 = (U64)(hoisted__U32_5419);
                (void)hoisted__U64_5421;
                Type_delete(hoisted__Type_5420, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5421);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5422 = 104;
                (void)hoisted__U32_5422;
                U32 hoisted__U32_5423 = U32_mul(i, hoisted__U32_5422);
                (void)hoisted__U32_5423;
                Type *hoisted__Type_5424 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5424;
                U64 hoisted__U64_5425 = (U64)(hoisted__U32_5423);
                (void)hoisted__U64_5425;
                Type_delete(hoisted__Type_5424, 1);
                U32 hoisted__U32_5426 = 104;
                (void)hoisted__U32_5426;
                Type *hoisted__Type_5427 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5427;
                void *hoisted__v_5428 = ptr_add(new_data, hoisted__U64_5425);
                (void)hoisted__v_5428;
                (void)hoisted__v_5428;
                U64 hoisted__U64_5429 = (U64)(hoisted__U32_5426);
                (void)hoisted__U64_5429;
                Type_delete(hoisted__Type_5427, 1);
                memcpy(hoisted__v_5428, cloned, hoisted__U64_5429);
                U32 hoisted__U32_5430 = 104;
                (void)hoisted__U32_5430;
                Type *hoisted__Type_5431 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5431;
                I32 hoisted__I32_5432 = 0;
                (void)hoisted__I32_5432;
                U64 hoisted__U64_5433 = (U64)(hoisted__U32_5430);
                (void)hoisted__U64_5433;
                Type_delete(hoisted__Type_5431, 1);
                memset(cloned, hoisted__I32_5432, hoisted__U64_5433);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5434 = U32_gt(_rc_U32_5416, _re_U32_5416);
                (void)_wcond_Bool_5434;
                if (_wcond_Bool_5434) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5416);
                U32_dec(&_rc_U32_5416);
                U32 hoisted__U32_5435 = 104;
                (void)hoisted__U32_5435;
                U32 hoisted__U32_5436 = U32_mul(i, hoisted__U32_5435);
                (void)hoisted__U32_5436;
                Type *hoisted__Type_5437 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5437;
                U64 hoisted__U64_5438 = (U64)(hoisted__U32_5436);
                (void)hoisted__U64_5438;
                Type_delete(hoisted__Type_5437, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5438);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5439 = 104;
                (void)hoisted__U32_5439;
                U32 hoisted__U32_5440 = U32_mul(i, hoisted__U32_5439);
                (void)hoisted__U32_5440;
                Type *hoisted__Type_5441 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5441;
                U64 hoisted__U64_5442 = (U64)(hoisted__U32_5440);
                (void)hoisted__U64_5442;
                Type_delete(hoisted__Type_5441, 1);
                U32 hoisted__U32_5443 = 104;
                (void)hoisted__U32_5443;
                Type *hoisted__Type_5444 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5444;
                void *hoisted__v_5445 = ptr_add(new_data, hoisted__U64_5442);
                (void)hoisted__v_5445;
                (void)hoisted__v_5445;
                U64 hoisted__U64_5446 = (U64)(hoisted__U32_5443);
                (void)hoisted__U64_5446;
                Type_delete(hoisted__Type_5444, 1);
                memcpy(hoisted__v_5445, cloned, hoisted__U64_5446);
                U32 hoisted__U32_5447 = 104;
                (void)hoisted__U32_5447;
                Type *hoisted__Type_5448 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5448;
                I32 hoisted__I32_5449 = 0;
                (void)hoisted__I32_5449;
                U64 hoisted__U64_5450 = (U64)(hoisted__U32_5447);
                (void)hoisted__U64_5450;
                Type_delete(hoisted__Type_5448, 1);
                memset(cloned, hoisted__I32_5449, hoisted__U64_5450);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5456 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5456->data = new_data;
    hoisted__Vec__Declaration_5456->count = self->count;
    hoisted__Vec__Declaration_5456->cap = self->cap;
    (void)hoisted__Vec__Declaration_5456;
    return hoisted__Vec__Declaration_5456;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5457 = 16;
    (void)hoisted__U32_5457;
    return hoisted__U32_5457;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5458 = 144;
    (void)hoisted__U32_5458;
    Type *hoisted__Type_5459 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5459;
    U64 hoisted__U64_5460 = (U64)(hoisted__U32_5458);
    (void)hoisted__U64_5460;
    Type_delete(hoisted__Type_5459, 1);
    void * hoisted__v_5461 = malloc(hoisted__U64_5460);
    (void)hoisted__v_5461;
    U32 hoisted__U32_5462 = 0;
    (void)hoisted__U32_5462;
    I64 hoisted__I64_5463 = 1;
    (void)hoisted__I64_5463;
    Vec__Expr *hoisted__Vec__Expr_5464 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5464->data = hoisted__v_5461;
    hoisted__Vec__Expr_5464->count = hoisted__U32_5462;
    hoisted__Vec__Expr_5464->cap = hoisted__I64_5463;
    (void)hoisted__Vec__Expr_5464;
    return hoisted__Vec__Expr_5464;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5465 = self->count;
        (void)_re_U32_5465;
        U32 _rc_U32_5465 = 0;
        (void)_rc_U32_5465;
        Bool hoisted__Bool_5480 = U32_lte(_rc_U32_5465, _re_U32_5465);
        (void)hoisted__Bool_5480;
        if (hoisted__Bool_5480) {
            while (1) {
                Bool _wcond_Bool_5466 = U32_lt(_rc_U32_5465, _re_U32_5465);
                (void)_wcond_Bool_5466;
                if (_wcond_Bool_5466) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5465);
                U32_inc(&_rc_U32_5465);
                U32 hoisted__U32_5467 = 144;
                (void)hoisted__U32_5467;
                U32 hoisted__U32_5468 = U32_mul(i, hoisted__U32_5467);
                (void)hoisted__U32_5468;
                Type *hoisted__Type_5469 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5469;
                U64 hoisted__U64_5470 = (U64)(hoisted__U32_5468);
                (void)hoisted__U64_5470;
                Type_delete(hoisted__Type_5469, 1);
                Expr *hoisted__Expr_5471 = ptr_add(self->data, hoisted__U64_5470);
                (void)hoisted__Expr_5471;
                (void)hoisted__Expr_5471;
                Bool hoisted__Bool_5472 = 0;
                (void)hoisted__Bool_5472;
                Expr_delete(hoisted__Expr_5471, hoisted__Bool_5472);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5473 = U32_gt(_rc_U32_5465, _re_U32_5465);
                (void)_wcond_Bool_5473;
                if (_wcond_Bool_5473) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5465);
                U32_dec(&_rc_U32_5465);
                U32 hoisted__U32_5474 = 144;
                (void)hoisted__U32_5474;
                U32 hoisted__U32_5475 = U32_mul(i, hoisted__U32_5474);
                (void)hoisted__U32_5475;
                Type *hoisted__Type_5476 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5476;
                U64 hoisted__U64_5477 = (U64)(hoisted__U32_5475);
                (void)hoisted__U64_5477;
                Type_delete(hoisted__Type_5476, 1);
                Expr *hoisted__Expr_5478 = ptr_add(self->data, hoisted__U64_5477);
                (void)hoisted__Expr_5478;
                (void)hoisted__Expr_5478;
                Bool hoisted__Bool_5479 = 0;
                (void)hoisted__Bool_5479;
                Expr_delete(hoisted__Expr_5478, hoisted__Bool_5479);
            }
        }
    }
    U32 hoisted__U32_5481 = 0;
    (void)hoisted__U32_5481;
    self->count = hoisted__U32_5481;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5790 = 144;
    (void)hoisted__U32_5790;
    U32 hoisted__U32_5791 = U32_mul(self->cap, hoisted__U32_5790);
    (void)hoisted__U32_5791;
    Type *hoisted__Type_5792 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5792;
    U64 hoisted__U64_5793 = (U64)(hoisted__U32_5791);
    (void)hoisted__U64_5793;
    Type_delete(hoisted__Type_5792, 1);
    void * new_data = malloc(hoisted__U64_5793);
    {
        U32 _re_U32_5754 = self->count;
        (void)_re_U32_5754;
        U32 _rc_U32_5754 = 0;
        (void)_rc_U32_5754;
        Bool hoisted__Bool_5789 = U32_lte(_rc_U32_5754, _re_U32_5754);
        (void)hoisted__Bool_5789;
        if (hoisted__Bool_5789) {
            while (1) {
                Bool _wcond_Bool_5755 = U32_lt(_rc_U32_5754, _re_U32_5754);
                (void)_wcond_Bool_5755;
                if (_wcond_Bool_5755) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5754);
                U32_inc(&_rc_U32_5754);
                U32 hoisted__U32_5756 = 144;
                (void)hoisted__U32_5756;
                U32 hoisted__U32_5757 = U32_mul(i, hoisted__U32_5756);
                (void)hoisted__U32_5757;
                Type *hoisted__Type_5758 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5758;
                U64 hoisted__U64_5759 = (U64)(hoisted__U32_5757);
                (void)hoisted__U64_5759;
                Type_delete(hoisted__Type_5758, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5759);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5760 = 144;
                (void)hoisted__U32_5760;
                U32 hoisted__U32_5761 = U32_mul(i, hoisted__U32_5760);
                (void)hoisted__U32_5761;
                Type *hoisted__Type_5762 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5762;
                U64 hoisted__U64_5763 = (U64)(hoisted__U32_5761);
                (void)hoisted__U64_5763;
                Type_delete(hoisted__Type_5762, 1);
                U32 hoisted__U32_5764 = 144;
                (void)hoisted__U32_5764;
                Type *hoisted__Type_5765 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5765;
                void *hoisted__v_5766 = ptr_add(new_data, hoisted__U64_5763);
                (void)hoisted__v_5766;
                (void)hoisted__v_5766;
                U64 hoisted__U64_5767 = (U64)(hoisted__U32_5764);
                (void)hoisted__U64_5767;
                Type_delete(hoisted__Type_5765, 1);
                memcpy(hoisted__v_5766, cloned, hoisted__U64_5767);
                U32 hoisted__U32_5768 = 144;
                (void)hoisted__U32_5768;
                Type *hoisted__Type_5769 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5769;
                I32 hoisted__I32_5770 = 0;
                (void)hoisted__I32_5770;
                U64 hoisted__U64_5771 = (U64)(hoisted__U32_5768);
                (void)hoisted__U64_5771;
                Type_delete(hoisted__Type_5769, 1);
                memset(cloned, hoisted__I32_5770, hoisted__U64_5771);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5772 = U32_gt(_rc_U32_5754, _re_U32_5754);
                (void)_wcond_Bool_5772;
                if (_wcond_Bool_5772) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5754);
                U32_dec(&_rc_U32_5754);
                U32 hoisted__U32_5773 = 144;
                (void)hoisted__U32_5773;
                U32 hoisted__U32_5774 = U32_mul(i, hoisted__U32_5773);
                (void)hoisted__U32_5774;
                Type *hoisted__Type_5775 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5775;
                U64 hoisted__U64_5776 = (U64)(hoisted__U32_5774);
                (void)hoisted__U64_5776;
                Type_delete(hoisted__Type_5775, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5776);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5777 = 144;
                (void)hoisted__U32_5777;
                U32 hoisted__U32_5778 = U32_mul(i, hoisted__U32_5777);
                (void)hoisted__U32_5778;
                Type *hoisted__Type_5779 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5779;
                U64 hoisted__U64_5780 = (U64)(hoisted__U32_5778);
                (void)hoisted__U64_5780;
                Type_delete(hoisted__Type_5779, 1);
                U32 hoisted__U32_5781 = 144;
                (void)hoisted__U32_5781;
                Type *hoisted__Type_5782 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5782;
                void *hoisted__v_5783 = ptr_add(new_data, hoisted__U64_5780);
                (void)hoisted__v_5783;
                (void)hoisted__v_5783;
                U64 hoisted__U64_5784 = (U64)(hoisted__U32_5781);
                (void)hoisted__U64_5784;
                Type_delete(hoisted__Type_5782, 1);
                memcpy(hoisted__v_5783, cloned, hoisted__U64_5784);
                U32 hoisted__U32_5785 = 144;
                (void)hoisted__U32_5785;
                Type *hoisted__Type_5786 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5786;
                I32 hoisted__I32_5787 = 0;
                (void)hoisted__I32_5787;
                U64 hoisted__U64_5788 = (U64)(hoisted__U32_5785);
                (void)hoisted__U64_5788;
                Type_delete(hoisted__Type_5786, 1);
                memset(cloned, hoisted__I32_5787, hoisted__U64_5788);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5794 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5794->data = new_data;
    hoisted__Vec__Expr_5794->count = self->count;
    hoisted__Vec__Expr_5794->cap = self->cap;
    (void)hoisted__Vec__Expr_5794;
    return hoisted__Vec__Expr_5794;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5795 = 16;
    (void)hoisted__U32_5795;
    return hoisted__U32_5795;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5796 = 8;
    (void)hoisted__U32_5796;
    Type *hoisted__Type_5797 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5797;
    U64 hoisted__U64_5798 = (U64)(hoisted__U32_5796);
    (void)hoisted__U64_5798;
    Type_delete(hoisted__Type_5797, 1);
    void * hoisted__v_5799 = malloc(hoisted__U64_5798);
    (void)hoisted__v_5799;
    U32 hoisted__U32_5800 = 0;
    (void)hoisted__U32_5800;
    I64 hoisted__I64_5801 = 1;
    (void)hoisted__I64_5801;
    Vec__I64 *hoisted__Vec__I64_5802 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5802->data = hoisted__v_5799;
    hoisted__Vec__I64_5802->count = hoisted__U32_5800;
    hoisted__Vec__I64_5802->cap = hoisted__I64_5801;
    (void)hoisted__Vec__I64_5802;
    return hoisted__Vec__I64_5802;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5803 = self->count;
        (void)_re_U32_5803;
        U32 _rc_U32_5803 = 0;
        (void)_rc_U32_5803;
        Bool hoisted__Bool_5818 = U32_lte(_rc_U32_5803, _re_U32_5803);
        (void)hoisted__Bool_5818;
        if (hoisted__Bool_5818) {
            while (1) {
                Bool _wcond_Bool_5804 = U32_lt(_rc_U32_5803, _re_U32_5803);
                (void)_wcond_Bool_5804;
                if (_wcond_Bool_5804) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5803);
                U32_inc(&_rc_U32_5803);
                U32 hoisted__U32_5805 = 8;
                (void)hoisted__U32_5805;
                U32 hoisted__U32_5806 = U32_mul(i, hoisted__U32_5805);
                (void)hoisted__U32_5806;
                Type *hoisted__Type_5807 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5807;
                U64 hoisted__U64_5808 = (U64)(hoisted__U32_5806);
                (void)hoisted__U64_5808;
                Type_delete(hoisted__Type_5807, 1);
                I64 *hoisted__I64_5809 = ptr_add(self->data, hoisted__U64_5808);
                (void)hoisted__I64_5809;
                (void)hoisted__I64_5809;
                Bool hoisted__Bool_5810 = 0;
                (void)hoisted__Bool_5810;
                I64_delete(hoisted__I64_5809, hoisted__Bool_5810);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5811 = U32_gt(_rc_U32_5803, _re_U32_5803);
                (void)_wcond_Bool_5811;
                if (_wcond_Bool_5811) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5803);
                U32_dec(&_rc_U32_5803);
                U32 hoisted__U32_5812 = 8;
                (void)hoisted__U32_5812;
                U32 hoisted__U32_5813 = U32_mul(i, hoisted__U32_5812);
                (void)hoisted__U32_5813;
                Type *hoisted__Type_5814 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5814;
                U64 hoisted__U64_5815 = (U64)(hoisted__U32_5813);
                (void)hoisted__U64_5815;
                Type_delete(hoisted__Type_5814, 1);
                I64 *hoisted__I64_5816 = ptr_add(self->data, hoisted__U64_5815);
                (void)hoisted__I64_5816;
                (void)hoisted__I64_5816;
                Bool hoisted__Bool_5817 = 0;
                (void)hoisted__Bool_5817;
                I64_delete(hoisted__I64_5816, hoisted__Bool_5817);
            }
        }
    }
    U32 hoisted__U32_5819 = 0;
    (void)hoisted__U32_5819;
    self->count = hoisted__U32_5819;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_6128 = 8;
    (void)hoisted__U32_6128;
    U32 hoisted__U32_6129 = U32_mul(self->cap, hoisted__U32_6128);
    (void)hoisted__U32_6129;
    Type *hoisted__Type_6130 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_6130;
    U64 hoisted__U64_6131 = (U64)(hoisted__U32_6129);
    (void)hoisted__U64_6131;
    Type_delete(hoisted__Type_6130, 1);
    void * new_data = malloc(hoisted__U64_6131);
    {
        U32 _re_U32_6092 = self->count;
        (void)_re_U32_6092;
        U32 _rc_U32_6092 = 0;
        (void)_rc_U32_6092;
        Bool hoisted__Bool_6127 = U32_lte(_rc_U32_6092, _re_U32_6092);
        (void)hoisted__Bool_6127;
        if (hoisted__Bool_6127) {
            while (1) {
                Bool _wcond_Bool_6093 = U32_lt(_rc_U32_6092, _re_U32_6092);
                (void)_wcond_Bool_6093;
                if (_wcond_Bool_6093) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6092);
                U32_inc(&_rc_U32_6092);
                U32 hoisted__U32_6094 = 8;
                (void)hoisted__U32_6094;
                U32 hoisted__U32_6095 = U32_mul(i, hoisted__U32_6094);
                (void)hoisted__U32_6095;
                Type *hoisted__Type_6096 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6096;
                U64 hoisted__U64_6097 = (U64)(hoisted__U32_6095);
                (void)hoisted__U64_6097;
                Type_delete(hoisted__Type_6096, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6097);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6098 = 8;
                (void)hoisted__U32_6098;
                U32 hoisted__U32_6099 = U32_mul(i, hoisted__U32_6098);
                (void)hoisted__U32_6099;
                Type *hoisted__Type_6100 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6100;
                U64 hoisted__U64_6101 = (U64)(hoisted__U32_6099);
                (void)hoisted__U64_6101;
                Type_delete(hoisted__Type_6100, 1);
                U32 hoisted__U32_6102 = 8;
                (void)hoisted__U32_6102;
                Type *hoisted__Type_6103 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6103;
                void *hoisted__v_6104 = ptr_add(new_data, hoisted__U64_6101);
                (void)hoisted__v_6104;
                (void)hoisted__v_6104;
                U64 hoisted__U64_6105 = (U64)(hoisted__U32_6102);
                (void)hoisted__U64_6105;
                Type_delete(hoisted__Type_6103, 1);
                memcpy(hoisted__v_6104, &cloned, hoisted__U64_6105);
                U32 hoisted__U32_6106 = 8;
                (void)hoisted__U32_6106;
                Type *hoisted__Type_6107 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6107;
                I32 hoisted__I32_6108 = 0;
                (void)hoisted__I32_6108;
                U64 hoisted__U64_6109 = (U64)(hoisted__U32_6106);
                (void)hoisted__U64_6109;
                Type_delete(hoisted__Type_6107, 1);
                memset(&cloned, hoisted__I32_6108, hoisted__U64_6109);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6110 = U32_gt(_rc_U32_6092, _re_U32_6092);
                (void)_wcond_Bool_6110;
                if (_wcond_Bool_6110) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6092);
                U32_dec(&_rc_U32_6092);
                U32 hoisted__U32_6111 = 8;
                (void)hoisted__U32_6111;
                U32 hoisted__U32_6112 = U32_mul(i, hoisted__U32_6111);
                (void)hoisted__U32_6112;
                Type *hoisted__Type_6113 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6113;
                U64 hoisted__U64_6114 = (U64)(hoisted__U32_6112);
                (void)hoisted__U64_6114;
                Type_delete(hoisted__Type_6113, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_6114);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6115 = 8;
                (void)hoisted__U32_6115;
                U32 hoisted__U32_6116 = U32_mul(i, hoisted__U32_6115);
                (void)hoisted__U32_6116;
                Type *hoisted__Type_6117 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6117;
                U64 hoisted__U64_6118 = (U64)(hoisted__U32_6116);
                (void)hoisted__U64_6118;
                Type_delete(hoisted__Type_6117, 1);
                U32 hoisted__U32_6119 = 8;
                (void)hoisted__U32_6119;
                Type *hoisted__Type_6120 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6120;
                void *hoisted__v_6121 = ptr_add(new_data, hoisted__U64_6118);
                (void)hoisted__v_6121;
                (void)hoisted__v_6121;
                U64 hoisted__U64_6122 = (U64)(hoisted__U32_6119);
                (void)hoisted__U64_6122;
                Type_delete(hoisted__Type_6120, 1);
                memcpy(hoisted__v_6121, &cloned, hoisted__U64_6122);
                U32 hoisted__U32_6123 = 8;
                (void)hoisted__U32_6123;
                Type *hoisted__Type_6124 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_6124;
                I32 hoisted__I32_6125 = 0;
                (void)hoisted__I32_6125;
                U64 hoisted__U64_6126 = (U64)(hoisted__U32_6123);
                (void)hoisted__U64_6126;
                Type_delete(hoisted__Type_6124, 1);
                memset(&cloned, hoisted__I32_6125, hoisted__U64_6126);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6132 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6132->data = new_data;
    hoisted__Vec__I64_6132->count = self->count;
    hoisted__Vec__I64_6132->cap = self->cap;
    (void)hoisted__Vec__I64_6132;
    return hoisted__Vec__I64_6132;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_6133 = 16;
    (void)hoisted__U32_6133;
    return hoisted__U32_6133;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7334 = 3;
    (void)hoisted__U32_7334;
    Array__Str *_va_Array_192 = Array__Str_new(hoisted__U32_7334);
    (void)_va_Array_192;
    I64 _va_Array_192_ek = 0;
    (void)_va_Array_192_ek;
    OutOfBounds *_va_Array_192_eo = malloc(sizeof(OutOfBounds));
    _va_Array_192_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_192_eo;
    U32 hoisted__U32_7335 = 0;
    (void)hoisted__U32_7335;
    Str *hoisted__Str_7336 = Str_clone(loc);
    (void)hoisted__Str_7336;
    static Str hoisted__Str_7337 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7337;
    Array__Str_set(_va_Array_192, hoisted__U32_7335, hoisted__Str_7336, &_va_Array_192_ek, _va_Array_192_eo, &hoisted__Str_7337);
    Str_delete(&hoisted__Str_7337, (Bool){0});
    U32 hoisted__U32_7338 = 1;
    (void)hoisted__U32_7338;
    static Str hoisted__Str_7339 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7339;
    static Str hoisted__Str_7340 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7340;
    Array__Str_set(_va_Array_192, hoisted__U32_7338, &hoisted__Str_7339, &_va_Array_192_ek, _va_Array_192_eo, &hoisted__Str_7340);
    Str_delete(&hoisted__Str_7340, (Bool){0});
    Array__Str *hoisted__Array__Str_7341 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7341;
    U32 hoisted__U32_7342 = 2;
    (void)hoisted__U32_7342;
    Str *hoisted__Str_7343 = format(hoisted__Array__Str_7341);
    (void)hoisted__Str_7343;
    static Str hoisted__Str_7344 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7344;
    Array__Str_set(_va_Array_192, hoisted__U32_7342, hoisted__Str_7343, &_va_Array_192_ek, _va_Array_192_eo, &hoisted__Str_7344);
    OutOfBounds_delete(_va_Array_192_eo, 1);
    Str_delete(&hoisted__Str_7344, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_192);
    I64 hoisted__I64_7345 = 1;
    (void)hoisted__I64_7345;
    exit(hoisted__I64_7345);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7354 = 1;
    (void)hoisted__U32_7354;
    Array__Str *_va_Array_194 = Array__Str_new(hoisted__U32_7354);
    (void)_va_Array_194;
    I64 _va_Array_194_ek = 0;
    (void)_va_Array_194_ek;
    OutOfBounds *_va_Array_194_eo = malloc(sizeof(OutOfBounds));
    _va_Array_194_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_194_eo;
    U32 hoisted__U32_7355 = 0;
    (void)hoisted__U32_7355;
    static Str hoisted__Str_7356 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7356;
    static Str hoisted__Str_7357 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7357;
    Array__Str_set(_va_Array_194, hoisted__U32_7355, &hoisted__Str_7356, &_va_Array_194_ek, _va_Array_194_eo, &hoisted__Str_7357);
    OutOfBounds_delete(_va_Array_194_eo, 1);
    Str_delete(&hoisted__Str_7357, (Bool){0});
    panic(_va_Array_194, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7362 = not(cond);
    (void)hoisted__Bool_7362;
    if (hoisted__Bool_7362) {
        U32 hoisted__U32_7358 = 1;
        (void)hoisted__U32_7358;
        Array__Str *_va_Array_195 = Array__Str_new(hoisted__U32_7358);
        (void)_va_Array_195;
        I64 _va_Array_195_ek = 0;
        (void)_va_Array_195_ek;
        OutOfBounds *_va_Array_195_eo = malloc(sizeof(OutOfBounds));
        _va_Array_195_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_195_eo;
        U32 hoisted__U32_7359 = 0;
        (void)hoisted__U32_7359;
        static Str hoisted__Str_7360 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7360;
        static Str hoisted__Str_7361 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7361;
        Array__Str_set(_va_Array_195, hoisted__U32_7359, &hoisted__Str_7360, &_va_Array_195_ek, _va_Array_195_eo, &hoisted__Str_7361);
        OutOfBounds_delete(_va_Array_195_eo, 1);
        Str_delete(&hoisted__Str_7361, (Bool){0});
        panic(_va_Array_195, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7372 = parts;
        (void)_fc_Array__Str_7372;
        (void)_fc_Array__Str_7372;
        U32 _fi_USize_7372 = 0;
        (void)_fi_USize_7372;
        while (1) {
            U32 hoisted__U32_7374 = Array__Str_len(_fc_Array__Str_7372);
            (void)hoisted__U32_7374;
            Bool _wcond_Bool_7373 = U32_lt(_fi_USize_7372, hoisted__U32_7374);
            (void)_wcond_Bool_7373;
            if (_wcond_Bool_7373) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7372, &_fi_USize_7372);
            U32 hoisted__U32_7375 = 1;
            (void)hoisted__U32_7375;
            U32 hoisted__U32_7376 = U32_add(_fi_USize_7372, hoisted__U32_7375);
            (void)hoisted__U32_7376;
            _fi_USize_7372 = hoisted__U32_7376;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7410 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7410;
    return hoisted__Bool_7410;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7419 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7419;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7419;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7420 = 0;
    (void)hoisted__U32_7420;
    U64 hoisted__U64_7421 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7420); });
    (void)hoisted__U64_7421;
    return hoisted__U64_7421;
}

U32 Range_size(void) {
    U32 hoisted__U32_7452 = 16;
    (void)hoisted__U32_7452;
    return hoisted__U32_7452;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7583 = 3;
    (void)hoisted__I64_7583;
    static Str hoisted__Str_7584 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7584;
    assert_eq__I64(result, hoisted__I64_7583, &hoisted__Str_7584);
    Str_delete(&hoisted__Str_7584, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7591 = 15;
    (void)hoisted__I64_7591;
    static Str hoisted__Str_7592 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7592;
    assert_eq__I64(result, hoisted__I64_7591, &hoisted__Str_7592);
    Str_delete(&hoisted__Str_7592, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7599 = 26;
    (void)hoisted__I64_7599;
    static Str hoisted__Str_7600 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7600;
    assert_eq__I64(result, hoisted__I64_7599, &hoisted__Str_7600);
    Str_delete(&hoisted__Str_7600, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7603 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7603;
    static Str hoisted__Str_7604 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7604;
    assert_eq__Str(&result, &hoisted__Str_7603, &hoisted__Str_7604);
    Str_delete(&hoisted__Str_7603, (Bool){0});
    Str_delete(&hoisted__Str_7604, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7632 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7632;
    static Str hoisted__Str_7633 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7633;
    assert_eq__Str(&r, &hoisted__Str_7632, &hoisted__Str_7633);
    Str_delete(&hoisted__Str_7632, (Bool){0});
    Str_delete(&hoisted__Str_7633, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7637 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7637;
    static Str hoisted__Str_7638 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7638;
    assert_eq__Str(&r2, &hoisted__Str_7637, &hoisted__Str_7638);
    Str_delete(&hoisted__Str_7637, (Bool){0});
    Str_delete(&hoisted__Str_7638, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7661 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7661;
    static Str hoisted__Str_7662 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7662;
    assert_eq__Str(&d, &hoisted__Str_7661, &hoisted__Str_7662);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7661, (Bool){0});
    Str_delete(&hoisted__Str_7662, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_7673 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7673;
    static Str hoisted__Str_7674 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7674;
    assert_eq__Str(&d2, &hoisted__Str_7673, &hoisted__Str_7674);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7673, (Bool){0});
    Str_delete(&hoisted__Str_7674, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7686 = 106;
    (void)hoisted__I64_7686;
    static Str hoisted__Str_7687 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7687;
    assert_eq__I64(d3, hoisted__I64_7686, &hoisted__Str_7687);
    Str_delete(&hoisted__Str_7687, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_8286 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8286;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8286);
    Str_delete(&hoisted__Str_8286, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    static Str hoisted__Str_8287 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8287;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8287);
    Str_delete(&hoisted__Str_8287, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8289 = 8;
    (void)hoisted__I64_8289;
    static Str hoisted__Str_8290 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8290;
    assert_eq__I64(result, hoisted__I64_8289, &hoisted__Str_8290);
    Str_delete(&hoisted__Str_8290, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8293 = 1;
    (void)hoisted__Bool_8293;
    static Str hoisted__Str_8294 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8294;
    assert(hoisted__Bool_8293, &hoisted__Str_8294);
    Str_delete(&hoisted__Str_8294, (Bool){0});
    Bool hoisted__Bool_8297 = 1;
    (void)hoisted__Bool_8297;
    static Str hoisted__Str_8298 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8298;
    assert(hoisted__Bool_8297, &hoisted__Str_8298);
    Str_delete(&hoisted__Str_8298, (Bool){0});
}

void test_fold_f32(void) {
    static Str hoisted__Str_8303 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8303;
    static Str hoisted__Str_8304 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8304;
    static Str hoisted__Str_8305 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8305;
    assert_eq__Str(&hoisted__Str_8303, &hoisted__Str_8304, &hoisted__Str_8305);
    Str_delete(&hoisted__Str_8303, (Bool){0});
    Str_delete(&hoisted__Str_8304, (Bool){0});
    Str_delete(&hoisted__Str_8305, (Bool){0});
    static Str hoisted__Str_8308 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8308;
    static Str hoisted__Str_8309 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8309;
    static Str hoisted__Str_8310 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8310;
    assert_eq__Str(&hoisted__Str_8308, &hoisted__Str_8309, &hoisted__Str_8310);
    Str_delete(&hoisted__Str_8308, (Bool){0});
    Str_delete(&hoisted__Str_8309, (Bool){0});
    Str_delete(&hoisted__Str_8310, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8315 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8315;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8315;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8316 = 0;
    (void)hoisted__U32_8316;
    U64 hoisted__U64_8317 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8316); });
    (void)hoisted__U64_8317;
    return hoisted__U64_8317;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8348 = 16;
    (void)hoisted__U32_8348;
    return hoisted__U32_8348;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8349 = 42;
    (void)hoisted__I64_8349;
    static Str hoisted__Str_8350 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8350;
    assert_eq__I64(v.x, hoisted__I64_8349, &hoisted__Str_8350);
    Str_delete(&hoisted__Str_8350, (Bool){0});
    I64 hoisted__I64_8351 = 99;
    (void)hoisted__I64_8351;
    static Str hoisted__Str_8352 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8352;
    assert_eq__I64(v.y, hoisted__I64_8351, &hoisted__Str_8352);
    Str_delete(&hoisted__Str_8352, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8355 = 10;
    (void)hoisted__I64_8355;
    static Str hoisted__Str_8356 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8356;
    assert_eq__I64(p.x, hoisted__I64_8355, &hoisted__Str_8356);
    Str_delete(&hoisted__Str_8356, (Bool){0});
    I64 hoisted__I64_8357 = 20;
    (void)hoisted__I64_8357;
    static Str hoisted__Str_8358 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8358;
    assert_eq__I64(p.y, hoisted__I64_8357, &hoisted__Str_8358);
    Str_delete(&hoisted__Str_8358, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8364 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8364;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8364;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8365 = 0;
    (void)hoisted__U32_8365;
    U64 hoisted__U64_8366 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8365); });
    (void)hoisted__U64_8366;
    return hoisted__U64_8366;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8397 = 32;
    (void)hoisted__U32_8397;
    return hoisted__U32_8397;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8398 = 5;
    (void)hoisted__I64_8398;
    static Str hoisted__Str_8399 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8399;
    assert_eq__I64(r.top_left.x, hoisted__I64_8398, &hoisted__Str_8399);
    Str_delete(&hoisted__Str_8399, (Bool){0});
    I64 hoisted__I64_8400 = 10;
    (void)hoisted__I64_8400;
    static Str hoisted__Str_8401 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8401;
    assert_eq__I64(r.top_left.y, hoisted__I64_8400, &hoisted__Str_8401);
    Str_delete(&hoisted__Str_8401, (Bool){0});
    I64 hoisted__I64_8402 = 100;
    (void)hoisted__I64_8402;
    static Str hoisted__Str_8403 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8403;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8402, &hoisted__Str_8403);
    Str_delete(&hoisted__Str_8403, (Bool){0});
    I64 hoisted__I64_8404 = 200;
    (void)hoisted__I64_8404;
    static Str hoisted__Str_8405 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8405;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8404, &hoisted__Str_8405);
    Str_delete(&hoisted__Str_8405, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8407 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8407;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8407;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8408 = 0;
    (void)hoisted__U32_8408;
    U64 hoisted__U64_8409 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8408); });
    (void)hoisted__U64_8409;
    return hoisted__U64_8409;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8452 = 12;
    (void)hoisted__U32_8452;
    return hoisted__U32_8452;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8456 = F32_to_str(v.x);
    (void)hoisted__Str_8456;
    static Str hoisted__Str_8457 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8457;
    static Str hoisted__Str_8458 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8458;
    assert_eq__Str(hoisted__Str_8456, &hoisted__Str_8457, &hoisted__Str_8458);
    Str_delete(hoisted__Str_8456, 1);
    Str_delete(&hoisted__Str_8457, (Bool){0});
    Str_delete(&hoisted__Str_8458, (Bool){0});
    Str *hoisted__Str_8459 = F32_to_str(v.y);
    (void)hoisted__Str_8459;
    static Str hoisted__Str_8460 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8460;
    static Str hoisted__Str_8461 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8461;
    assert_eq__Str(hoisted__Str_8459, &hoisted__Str_8460, &hoisted__Str_8461);
    Str_delete(hoisted__Str_8459, 1);
    Str_delete(&hoisted__Str_8460, (Bool){0});
    Str_delete(&hoisted__Str_8461, (Bool){0});
    Str *hoisted__Str_8462 = F32_to_str(v.z);
    (void)hoisted__Str_8462;
    static Str hoisted__Str_8463 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8463;
    static Str hoisted__Str_8464 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8464;
    assert_eq__Str(hoisted__Str_8462, &hoisted__Str_8463, &hoisted__Str_8464);
    Str_delete(hoisted__Str_8462, 1);
    Str_delete(&hoisted__Str_8463, (Bool){0});
    Str_delete(&hoisted__Str_8464, (Bool){0});
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
    Bool hoisted__Bool_8469 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8469;
    if (hoisted__Bool_8469) {
        Bool hoisted__Bool_8466 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8466;
        { Bool _ret_val = hoisted__Bool_8466;
                return _ret_val; }
    }
    Bool hoisted__Bool_8470 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8470;
    if (hoisted__Bool_8470) {
        Bool hoisted__Bool_8467 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8467;
        { Bool _ret_val = hoisted__Bool_8467;
                return _ret_val; }
    }
    Bool hoisted__Bool_8471 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8471;
    if (hoisted__Bool_8471) {
        Bool hoisted__Bool_8468 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8468;
        { Bool _ret_val = hoisted__Bool_8468;
                return _ret_val; }
    }
    Bool hoisted__Bool_8472 = 0;
    (void)hoisted__Bool_8472;
    return hoisted__Bool_8472;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8480 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8480;
    if (hoisted__Bool_8480) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8481 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8481;
    if (hoisted__Bool_8481) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8482 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8482;
    if (hoisted__Bool_8482) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8483 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8483;
    UNREACHABLE(&hoisted__Str_8483);
    Str_delete(&hoisted__Str_8483, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8484 = 4;
    (void)hoisted__U32_8484;
    return hoisted__U32_8484;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8485 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8485;
    static Str hoisted__Str_8486 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8486;
    assert(hoisted__Bool_8485, &hoisted__Str_8486);
    Str_delete(&hoisted__Str_8486, (Bool){0});
    Bool hoisted__Bool_8487 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8487;
    Bool hoisted__Bool_8488 = not(hoisted__Bool_8487);
    (void)hoisted__Bool_8488;
    static Str hoisted__Str_8489 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8489;
    assert(hoisted__Bool_8488, &hoisted__Str_8489);
    Str_delete(&hoisted__Str_8489, (Bool){0});
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
    Bool hoisted__Bool_8490 = is(self, other);
    (void)hoisted__Bool_8490;
    return hoisted__Bool_8490;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8508 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8508;
    if (hoisted__Bool_8508) {
        I64 *hoisted__I64_8504 = get_payload(self);
        (void)hoisted__I64_8504;
        (void)hoisted__I64_8504;
        Bool hoisted__Bool_8505 = 0;
        (void)hoisted__Bool_8505;
        I64_delete(hoisted__I64_8504, hoisted__Bool_8505);
    }
    Bool hoisted__Bool_8509 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8509;
    if (hoisted__Bool_8509) {
        Str *hoisted__Str_8506 = get_payload(self);
        (void)hoisted__Str_8506;
        (void)hoisted__Str_8506;
        Bool hoisted__Bool_8507 = 0;
        (void)hoisted__Bool_8507;
        Str_delete(hoisted__Str_8506, hoisted__Bool_8507);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8540 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8540;
    if (hoisted__Bool_8540) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8537 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8537;
        { Token * _ret_val = hoisted__Token_8537;
                return _ret_val; }
    }
    Bool hoisted__Bool_8541 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8541;
    if (hoisted__Bool_8541) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8538 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8538;
        Token *hoisted__Token_8539 = Token_Name(hoisted__Str_8538);
        (void)hoisted__Token_8539;
        { Token * _ret_val = hoisted__Token_8539;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8542 = 24;
    (void)hoisted__U32_8542;
    return hoisted__U32_8542;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8544 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8544;
    static Str hoisted__Str_8545 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8545;
    assert(hoisted__Bool_8544, &hoisted__Str_8545);
    Str_delete(&hoisted__Str_8545, (Bool){0});
    Bool hoisted__Bool_8546 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8546;
    Bool hoisted__Bool_8547 = not(hoisted__Bool_8546);
    (void)hoisted__Bool_8547;
    static Str hoisted__Str_8548 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8548;
    assert(hoisted__Bool_8547, &hoisted__Str_8548);
    Str_delete(&hoisted__Str_8548, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8549 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8549;
    static Str hoisted__Str_8550 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8550;
    assert(hoisted__Bool_8549, &hoisted__Str_8550);
    Str_delete(&hoisted__Str_8550, (Bool){0});
    Bool hoisted__Bool_8551 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8551;
    Bool hoisted__Bool_8552 = not(hoisted__Bool_8551);
    (void)hoisted__Bool_8552;
    static Str hoisted__Str_8553 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8553;
    assert(hoisted__Bool_8552, &hoisted__Str_8553);
    Str_delete(&hoisted__Str_8553, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8556 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8556;
    static Str hoisted__Str_8557 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8557;
    assert(hoisted__Bool_8556, &hoisted__Str_8557);
    Str_delete(&hoisted__Str_8557, (Bool){0});
    Bool hoisted__Bool_8558 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8558;
    Bool hoisted__Bool_8559 = not(hoisted__Bool_8558);
    (void)hoisted__Bool_8559;
    static Str hoisted__Str_8560 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8560;
    assert(hoisted__Bool_8559, &hoisted__Str_8560);
    Str_delete(&hoisted__Str_8560, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8708 = I64_neq(a, b);
    (void)hoisted__Bool_8708;
    if (hoisted__Bool_8708) {
        U32 hoisted__U32_8692 = 5;
        (void)hoisted__U32_8692;
        Array__Str *_va_Array_240 = Array__Str_new(hoisted__U32_8692);
        (void)_va_Array_240;
        I64 _va_Array_240_ek = 0;
        (void)_va_Array_240_ek;
        OutOfBounds *_va_Array_240_eo = malloc(sizeof(OutOfBounds));
        _va_Array_240_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_240_eo;
        U32 hoisted__U32_8693 = 0;
        (void)hoisted__U32_8693;
        static Str hoisted__Str_8694 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8694;
        static Str hoisted__Str_8695 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8695;
        Array__Str_set(_va_Array_240, hoisted__U32_8693, &hoisted__Str_8694, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8695);
        Str_delete(&hoisted__Str_8695, (Bool){0});
        U32 hoisted__U32_8696 = 1;
        (void)hoisted__U32_8696;
        Str *hoisted__Str_8697 = I64_to_str(a);
        (void)hoisted__Str_8697;
        static Str hoisted__Str_8698 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8698;
        Array__Str_set(_va_Array_240, hoisted__U32_8696, hoisted__Str_8697, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8698);
        Str_delete(&hoisted__Str_8698, (Bool){0});
        U32 hoisted__U32_8699 = 2;
        (void)hoisted__U32_8699;
        static Str hoisted__Str_8700 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8700;
        static Str hoisted__Str_8701 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8701;
        Array__Str_set(_va_Array_240, hoisted__U32_8699, &hoisted__Str_8700, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8701);
        Str_delete(&hoisted__Str_8701, (Bool){0});
        U32 hoisted__U32_8702 = 3;
        (void)hoisted__U32_8702;
        Str *hoisted__Str_8703 = I64_to_str(b);
        (void)hoisted__Str_8703;
        static Str hoisted__Str_8704 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8704;
        Array__Str_set(_va_Array_240, hoisted__U32_8702, hoisted__Str_8703, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8704);
        Str_delete(&hoisted__Str_8704, (Bool){0});
        U32 hoisted__U32_8705 = 4;
        (void)hoisted__U32_8705;
        static Str hoisted__Str_8706 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8706;
        static Str hoisted__Str_8707 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8707;
        Array__Str_set(_va_Array_240, hoisted__U32_8705, &hoisted__Str_8706, &_va_Array_240_ek, _va_Array_240_eo, &hoisted__Str_8707);
        OutOfBounds_delete(_va_Array_240_eo, 1);
        Str_delete(&hoisted__Str_8707, (Bool){0});
        panic(_va_Array_240, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8725 = Str_neq(a, b);
    (void)hoisted__Bool_8725;
    if (hoisted__Bool_8725) {
        U32 hoisted__U32_8709 = 5;
        (void)hoisted__U32_8709;
        Array__Str *_va_Array_241 = Array__Str_new(hoisted__U32_8709);
        (void)_va_Array_241;
        I64 _va_Array_241_ek = 0;
        (void)_va_Array_241_ek;
        OutOfBounds *_va_Array_241_eo = malloc(sizeof(OutOfBounds));
        _va_Array_241_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_241_eo;
        U32 hoisted__U32_8710 = 0;
        (void)hoisted__U32_8710;
        static Str hoisted__Str_8711 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8711;
        static Str hoisted__Str_8712 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8712;
        Array__Str_set(_va_Array_241, hoisted__U32_8710, &hoisted__Str_8711, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8712);
        Str_delete(&hoisted__Str_8712, (Bool){0});
        U32 hoisted__U32_8713 = 1;
        (void)hoisted__U32_8713;
        Str *hoisted__Str_8714 = Str_to_str(a);
        (void)hoisted__Str_8714;
        static Str hoisted__Str_8715 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8715;
        Array__Str_set(_va_Array_241, hoisted__U32_8713, hoisted__Str_8714, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8715);
        Str_delete(&hoisted__Str_8715, (Bool){0});
        U32 hoisted__U32_8716 = 2;
        (void)hoisted__U32_8716;
        static Str hoisted__Str_8717 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8717;
        static Str hoisted__Str_8718 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8718;
        Array__Str_set(_va_Array_241, hoisted__U32_8716, &hoisted__Str_8717, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8718);
        Str_delete(&hoisted__Str_8718, (Bool){0});
        U32 hoisted__U32_8719 = 3;
        (void)hoisted__U32_8719;
        Str *hoisted__Str_8720 = Str_to_str(b);
        (void)hoisted__Str_8720;
        static Str hoisted__Str_8721 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8721;
        Array__Str_set(_va_Array_241, hoisted__U32_8719, hoisted__Str_8720, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8721);
        Str_delete(&hoisted__Str_8721, (Bool){0});
        U32 hoisted__U32_8722 = 4;
        (void)hoisted__U32_8722;
        static Str hoisted__Str_8723 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8723;
        static Str hoisted__Str_8724 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_8724;
        Array__Str_set(_va_Array_241, hoisted__U32_8722, &hoisted__Str_8723, &_va_Array_241_ek, _va_Array_241_eo, &hoisted__Str_8724);
        OutOfBounds_delete(_va_Array_241_eo, 1);
        Str_delete(&hoisted__Str_8724, (Bool){0});
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
