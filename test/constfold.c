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
    NodeType_TAG_CaptureBlock
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
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
Array__Str * Array__Str_new(U32 cap);
U32 Array__Str_len(Array__Str * self);
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
void Array__Str_set(Array__Str * self, U32 i, Str * val);
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
void panic(Str * loc_str, Array__Str * parts);
void UNREACHABLE(Str * loc_str);
Bool assert(Str * loc_str, Bool cond);
void assert_eq(Str * loc_str, I64 a, I64 b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
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
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
Array__Str * Array__Str_new(U32 cap);
U32 Array__Str_len(Array__Str * self);
Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
void Array__Str_set(Array__Str * self, U32 i, Str * val);
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
void panic(Str * loc_str, Array__Str * parts);
void UNREACHABLE(Str * loc_str);
Bool assert(Str * loc_str, Bool cond);
void assert_eq(Str * loc_str, I64 a, I64 b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
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
        Array__Str *_fc_Array__Str_625 = parts;
        (void)_fc_Array__Str_625;
        (void)_fc_Array__Str_625;
        U32 _fi_USize_625 = 0;
        (void)_fi_USize_625;
        I64 _forin_err_kind_625 = 0;
        (void)_forin_err_kind_625;
        OutOfBounds *_forin_OutOfBounds_625 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_625->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_625;
        while (1) {
            U32 hoisted__U32_631 = Array__Str_len(_fc_Array__Str_625);
            (void)hoisted__U32_631;
            Bool _wcond_Bool_626 = U32_lt(_fi_USize_625, hoisted__U32_631);
            (void)_wcond_Bool_626;
            if (_wcond_Bool_626) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_625, &_fi_USize_625, &_forin_err_kind_625, _forin_OutOfBounds_625);
            I64 hoisted__I64_632 = 0;
            (void)hoisted__I64_632;
            Bool hoisted__Bool_633 = I64_eq(_forin_err_kind_625, hoisted__I64_632);
            (void)hoisted__Bool_633;
            Bool hoisted__Bool_634 = not(hoisted__Bool_633);
            (void)hoisted__Bool_634;
            if (hoisted__Bool_634) {
                U32 hoisted__U32_627 = 1;
                (void)hoisted__U32_627;
                Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_627);
                (void)_va_Array_16;
                U32 hoisted__U32_628 = 0;
                (void)hoisted__U32_628;
                Str hoisted__Str_629 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_629;
                Array__Str_set(_va_Array_16, hoisted__U32_628, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_629; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
                Str hoisted__Str_630 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_630;
                panic(&hoisted__Str_630, _va_Array_16);
                Str_delete(&hoisted__Str_630, (Bool){0});
            }
            U32 hoisted__U32_635 = 1;
            (void)hoisted__U32_635;
            U32 hoisted__U32_636 = U32_add(_fi_USize_625, hoisted__U32_635);
            (void)hoisted__U32_636;
            _fi_USize_625 = hoisted__U32_636;
            U32 hoisted__U32_637 = Str_len(s);
            (void)hoisted__U32_637;
            U32 hoisted__U32_638 = U32_add(total, hoisted__U32_637);
            (void)hoisted__U32_638;
            total = hoisted__U32_638;
        }
        OutOfBounds_delete(_forin_OutOfBounds_625, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_639 = parts;
        (void)_fc_Array__Str_639;
        (void)_fc_Array__Str_639;
        U32 _fi_USize_639 = 0;
        (void)_fi_USize_639;
        I64 _forin_err_kind_639 = 0;
        (void)_forin_err_kind_639;
        OutOfBounds *_forin_OutOfBounds_639 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_639->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_639;
        while (1) {
            U32 hoisted__U32_645 = Array__Str_len(_fc_Array__Str_639);
            (void)hoisted__U32_645;
            Bool _wcond_Bool_640 = U32_lt(_fi_USize_639, hoisted__U32_645);
            (void)_wcond_Bool_640;
            if (_wcond_Bool_640) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_639, &_fi_USize_639, &_forin_err_kind_639, _forin_OutOfBounds_639);
            I64 hoisted__I64_646 = 0;
            (void)hoisted__I64_646;
            Bool hoisted__Bool_647 = I64_eq(_forin_err_kind_639, hoisted__I64_646);
            (void)hoisted__Bool_647;
            Bool hoisted__Bool_648 = not(hoisted__Bool_647);
            (void)hoisted__Bool_648;
            if (hoisted__Bool_648) {
                U32 hoisted__U32_641 = 1;
                (void)hoisted__U32_641;
                Array__Str *_va_Array_17 = Array__Str_new(hoisted__U32_641);
                (void)_va_Array_17;
                U32 hoisted__U32_642 = 0;
                (void)hoisted__U32_642;
                Str hoisted__Str_643 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_643;
                Array__Str_set(_va_Array_17, hoisted__U32_642, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_643; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
                Str hoisted__Str_644 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_644;
                panic(&hoisted__Str_644, _va_Array_17);
                Str_delete(&hoisted__Str_644, (Bool){0});
            }
            U32 hoisted__U32_649 = 1;
            (void)hoisted__U32_649;
            U32 hoisted__U32_650 = U32_add(_fi_USize_639, hoisted__U32_649);
            (void)hoisted__U32_650;
            _fi_USize_639 = hoisted__U32_650;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_639, 1);
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_655 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_655;
    if (hoisted__Bool_655) {
        U32 hoisted__U32_651 = 1;
        (void)hoisted__U32_651;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_651);
        (void)_va_Array_18;
        U32 hoisted__U32_652 = 0;
        (void)hoisted__U32_652;
        Str hoisted__Str_653 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_653;
        Array__Str_set(_va_Array_18, hoisted__U32_652, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_653; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_654 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_654;
        panic(&hoisted__Str_654, _va_Array_18);
        Str_delete(&hoisted__Str_654, (Bool){0});
    }
    void *hoisted__v_656 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_656;
    (void)hoisted__v_656;
    return hoisted__v_656;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_666 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_666;
    if (hoisted__Bool_666) {
        min_len = b->count;
    }
    {
        U32 _re_U32_658 = U32_clone(&min_len);
        (void)_re_U32_658;
        U32 _rc_U32_658 = 0;
        (void)_rc_U32_658;
        Bool hoisted__Bool_665 = U32_lte(_rc_U32_658, _re_U32_658);
        (void)hoisted__Bool_665;
        if (hoisted__Bool_665) {
            while (1) {
                Bool _wcond_Bool_659 = U32_lt(_rc_U32_658, _re_U32_658);
                (void)_wcond_Bool_659;
                if (_wcond_Bool_659) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_658);
                U32_inc(&_rc_U32_658);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_660 = 0;
                (void)hoisted__I64_660;
                Bool hoisted__Bool_661 = I64_neq(c, hoisted__I64_660);
                (void)hoisted__Bool_661;
                if (hoisted__Bool_661) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_662 = U32_gt(_rc_U32_658, _re_U32_658);
                (void)_wcond_Bool_662;
                if (_wcond_Bool_662) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_658);
                U32_dec(&_rc_U32_658);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_663 = 0;
                (void)hoisted__I64_663;
                Bool hoisted__Bool_664 = I64_neq(c, hoisted__I64_663);
                (void)hoisted__Bool_664;
                if (hoisted__Bool_664) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_667 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_667;
    return hoisted__I64_667;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_669 = 1;
    (void)hoisted__U32_669;
    U32 hoisted__U64_670 = U32_add(n, hoisted__U32_669);
    (void)hoisted__U64_670;
    void * buf = malloc(hoisted__U64_670);
    I32 hoisted__I32_671 = 0;
    (void)hoisted__I32_671;
    U64 hoisted__U64_672 = 1ULL;
    (void)hoisted__U64_672;
    memset(buf, hoisted__I32_671, hoisted__U64_672);
    I64 hoisted__I64_673 = 0;
    (void)hoisted__I64_673;
    Str *hoisted__Str_674 = malloc(sizeof(Str));
    hoisted__Str_674->c_str = buf;
    hoisted__Str_674->count = hoisted__I64_673;
    hoisted__Str_674->cap = n;
    (void)hoisted__Str_674;
    return hoisted__Str_674;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_685 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_685;
    if (hoisted__Bool_685) {
        U32 hoisted__U32_677 = 1;
        (void)hoisted__U32_677;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_677);
        (void)_va_Array_19;
        U32 hoisted__U32_678 = 0;
        (void)hoisted__U32_678;
        Str hoisted__Str_679 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_679;
        Array__Str_set(_va_Array_19, hoisted__U32_678, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_679; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_680 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_680;
        panic(&hoisted__Str_680, _va_Array_19);
        Str_delete(&hoisted__Str_680, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_686 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_686;
    if (hoisted__Bool_686) {
        U32 hoisted__U32_681 = 1;
        (void)hoisted__U32_681;
        Array__Str *_va_Array_20 = Array__Str_new(hoisted__U32_681);
        (void)_va_Array_20;
        U32 hoisted__U32_682 = 0;
        (void)hoisted__U32_682;
        Str hoisted__Str_683 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_683;
        Array__Str_set(_va_Array_20, hoisted__U32_682, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_683; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_684 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_684;
        panic(&hoisted__Str_684, _va_Array_20);
        Str_delete(&hoisted__Str_684, (Bool){0});
    }
    void *hoisted__v_687 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_687;
    (void)hoisted__v_687;
    memcpy(hoisted__v_687, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_688 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_688;
    (void)hoisted__v_688;
    I32 hoisted__I32_689 = 0;
    (void)hoisted__I32_689;
    U64 hoisted__U64_690 = 1ULL;
    (void)hoisted__U64_690;
    memset(hoisted__v_688, hoisted__I32_689, hoisted__U64_690);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_691 = 1;
    (void)hoisted__U32_691;
    U32 hoisted__U64_692 = U32_add(val->count, hoisted__U32_691);
    (void)hoisted__U64_692;
    void * new_data = malloc(hoisted__U64_692);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_693 = ptr_add(new_data, val->count);
    (void)hoisted__v_693;
    (void)hoisted__v_693;
    I32 hoisted__I32_694 = 0;
    (void)hoisted__I32_694;
    U64 hoisted__U64_695 = 1ULL;
    (void)hoisted__U64_695;
    memset(hoisted__v_693, hoisted__I32_694, hoisted__U64_695);
    Str *hoisted__Str_696 = malloc(sizeof(Str));
    hoisted__Str_696->c_str = new_data;
    hoisted__Str_696->count = val->count;
    hoisted__Str_696->cap = val->count;
    (void)hoisted__Str_696;
    return hoisted__Str_696;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_697 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_697;
    if (hoisted__Bool_697) {
        free(self->c_str);
    }
    Bool hoisted__Bool_698 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_698;
    Bool hoisted__Bool_699 = and(call_free, hoisted__Bool_698);
    (void)hoisted__Bool_699;
    if (hoisted__Bool_699) {
        free(self);
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_894 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_894;
    return hoisted__U64_894;
}

U32 Str_size(void) {
    U32 hoisted__U32_1065 = 16;
    (void)hoisted__U32_1065;
    return hoisted__U32_1065;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1066 = Str_cmp(a, b);
    (void)hoisted__I64_1066;
    I64 hoisted__I64_1067 = 0;
    (void)hoisted__I64_1067;
    Bool hoisted__Bool_1068 = I64_eq(hoisted__I64_1066, hoisted__I64_1067);
    (void)hoisted__Bool_1068;
    return hoisted__Bool_1068;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1167 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1167->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1167;
    return hoisted__OutOfBounds_1167;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1168 = 0;
    (void)hoisted__Bool_1168;
    Str_delete(&self->msg, hoisted__Bool_1168);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1169 = 0;
    (void)hoisted__U32_1169;
    U64 hoisted__U64_1170 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1169); });
    (void)hoisted__U64_1170;
    return hoisted__U64_1170;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1185 = 16;
    (void)hoisted__U32_1185;
    return hoisted__U32_1185;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1205 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1205;
    U32 hoisted__U32_1206 = 16;
    (void)hoisted__U32_1206;
    Type *hoisted__Type_1207 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1207;
    U64 hoisted__U64_1208 = (U64)(cap);
    (void)hoisted__U64_1208;
    Type_delete(hoisted__Type_1205, 1);
    U64 hoisted__U64_1209 = (U64)(hoisted__U32_1206);
    (void)hoisted__U64_1209;
    Type_delete(hoisted__Type_1207, 1);
    void * hoisted__v_1210 = calloc(hoisted__U64_1208, hoisted__U64_1209);
    (void)hoisted__v_1210;
    Array__Str *hoisted__Array__Str_1211 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1211->data = hoisted__v_1210;
    hoisted__Array__Str_1211->cap = cap;
    (void)hoisted__Array__Str_1211;
    return hoisted__Array__Str_1211;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1233 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1233;
    if (hoisted__Bool_1233) {
        U32 hoisted__U32_1212 = 6;
        (void)hoisted__U32_1212;
        Array__Str *_va_Array_32 = Array__Str_new(hoisted__U32_1212);
        (void)_va_Array_32;
        U32 hoisted__U32_1213 = 0;
        (void)hoisted__U32_1213;
        Str hoisted__Str_1214 = (Str){.c_str = (void *)"./src/core/array.til:28:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1214;
        Array__Str_set(_va_Array_32, hoisted__U32_1213, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1214; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1215 = 1;
        (void)hoisted__U32_1215;
        Str hoisted__Str_1216 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1216;
        Array__Str_set(_va_Array_32, hoisted__U32_1215, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1216; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1217 = 2;
        (void)hoisted__U32_1217;
        Str *hoisted__Str_1218 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1218;
        Array__Str_set(_va_Array_32, hoisted__U32_1217, hoisted__Str_1218);
        U32 hoisted__U32_1219 = 3;
        (void)hoisted__U32_1219;
        Str hoisted__Str_1220 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1220;
        Array__Str_set(_va_Array_32, hoisted__U32_1219, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1220; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1221 = 4;
        (void)hoisted__U32_1221;
        Str *hoisted__Str_1222 = U32_to_str(self->cap);
        (void)hoisted__Str_1222;
        Array__Str_set(_va_Array_32, hoisted__U32_1221, hoisted__Str_1222);
        U32 hoisted__U32_1223 = 5;
        (void)hoisted__U32_1223;
        Str hoisted__Str_1224 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1224;
        Array__Str_set(_va_Array_32, hoisted__U32_1223, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1224; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_1225 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_32); hoisted__OutOfBounds_1225->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1225;
        U32 hoisted__U32_1226 = 16;
        (void)hoisted__U32_1226;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1225, hoisted__U32_1226);
        OutOfBounds_delete(hoisted__OutOfBounds_1225, 1);
        I64 hoisted__I64_1227 = 3;
        (void)hoisted__I64_1227;
        *_err_kind = hoisted__I64_1227;
    }
    I64 hoisted__I64_1234 = 0;
    (void)hoisted__I64_1234;
    Bool hoisted__Bool_1235 = I64_eq(DEREF(_err_kind), hoisted__I64_1234);
    (void)hoisted__Bool_1235;
    if (hoisted__Bool_1235) {
        U32 hoisted__U32_1228 = 16;
        (void)hoisted__U32_1228;
        U32 hoisted__U32_1229 = U32_mul(DEREF(i), hoisted__U32_1228);
        (void)hoisted__U32_1229;
        Type *hoisted__Type_1230 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1230;
        U64 hoisted__U64_1231 = (U64)(hoisted__U32_1229);
        (void)hoisted__U64_1231;
        Type_delete(hoisted__Type_1230, 1);
        void *hoisted__v_1232 = ptr_add(self->data, hoisted__U64_1231);
        (void)hoisted__v_1232;
        (void)hoisted__v_1232;
        { Str * _ret_val = hoisted__v_1232;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val) {
    Bool hoisted__Bool_1248 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1248;
    if (hoisted__Bool_1248) {
        U32 hoisted__U32_1236 = 5;
        (void)hoisted__U32_1236;
        Array__Str *_va_Array_33 = Array__Str_new(hoisted__U32_1236);
        (void)_va_Array_33;
        U32 hoisted__U32_1237 = 0;
        (void)hoisted__U32_1237;
        Str hoisted__Str_1238 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1238;
        Array__Str_set(_va_Array_33, hoisted__U32_1237, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1238; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1239 = 1;
        (void)hoisted__U32_1239;
        Str *hoisted__Str_1240 = U32_to_str(i);
        (void)hoisted__Str_1240;
        Array__Str_set(_va_Array_33, hoisted__U32_1239, hoisted__Str_1240);
        U32 hoisted__U32_1241 = 2;
        (void)hoisted__U32_1241;
        Str hoisted__Str_1242 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1242;
        Array__Str_set(_va_Array_33, hoisted__U32_1241, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1242; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1243 = 3;
        (void)hoisted__U32_1243;
        Str *hoisted__Str_1244 = U32_to_str(self->cap);
        (void)hoisted__Str_1244;
        Array__Str_set(_va_Array_33, hoisted__U32_1243, hoisted__Str_1244);
        U32 hoisted__U32_1245 = 4;
        (void)hoisted__U32_1245;
        Str hoisted__Str_1246 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1246;
        Array__Str_set(_va_Array_33, hoisted__U32_1245, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1246; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_1247 = (Str){.c_str = (void *)"./src/core/array.til:37:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1247;
        panic(&hoisted__Str_1247, _va_Array_33);
        Str_delete(&hoisted__Str_1247, (Bool){0});
    }
    U32 hoisted__U32_1249 = 16;
    (void)hoisted__U32_1249;
    U32 hoisted__U32_1250 = U32_mul(i, hoisted__U32_1249);
    (void)hoisted__U32_1250;
    Type *hoisted__Type_1251 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1251;
    U64 hoisted__U64_1252 = (U64)(hoisted__U32_1250);
    (void)hoisted__U64_1252;
    Type_delete(hoisted__Type_1251, 1);
    Str *hoisted__Str_1253 = ptr_add(self->data, hoisted__U64_1252);
    (void)hoisted__Str_1253;
    (void)hoisted__Str_1253;
    Bool hoisted__Bool_1254 = 0;
    (void)hoisted__Bool_1254;
    Str_delete(hoisted__Str_1253, hoisted__Bool_1254);
    U32 hoisted__U32_1255 = 16;
    (void)hoisted__U32_1255;
    U32 hoisted__U32_1256 = U32_mul(i, hoisted__U32_1255);
    (void)hoisted__U32_1256;
    Type *hoisted__Type_1257 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1257;
    U64 hoisted__U64_1258 = (U64)(hoisted__U32_1256);
    (void)hoisted__U64_1258;
    Type_delete(hoisted__Type_1257, 1);
    U32 hoisted__U32_1259 = 16;
    (void)hoisted__U32_1259;
    Type *hoisted__Type_1260 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1260;
    void *hoisted__v_1261 = ptr_add(self->data, hoisted__U64_1258);
    (void)hoisted__v_1261;
    (void)hoisted__v_1261;
    U64 hoisted__U64_1262 = (U64)(hoisted__U32_1259);
    (void)hoisted__U64_1262;
    Type_delete(hoisted__Type_1260, 1);
    memcpy(hoisted__v_1261, val, hoisted__U64_1262);
    U32 hoisted__U32_1263 = 16;
    (void)hoisted__U32_1263;
    Type *hoisted__Type_1264 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1264;
    I32 hoisted__I32_1265 = 0;
    (void)hoisted__I32_1265;
    U64 hoisted__U64_1266 = (U64)(hoisted__U32_1263);
    (void)hoisted__U64_1266;
    Type_delete(hoisted__Type_1264, 1);
    memset(val, hoisted__I32_1265, hoisted__U64_1266);
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1267 = self->cap;
        (void)_re_U32_1267;
        U32 _rc_U32_1267 = 0;
        (void)_rc_U32_1267;
        Bool hoisted__Bool_1282 = U32_lte(_rc_U32_1267, _re_U32_1267);
        (void)hoisted__Bool_1282;
        if (hoisted__Bool_1282) {
            while (1) {
                Bool _wcond_Bool_1268 = U32_lt(_rc_U32_1267, _re_U32_1267);
                (void)_wcond_Bool_1268;
                if (_wcond_Bool_1268) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1267);
                U32_inc(&_rc_U32_1267);
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
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1275 = U32_gt(_rc_U32_1267, _re_U32_1267);
                (void)_wcond_Bool_1275;
                if (_wcond_Bool_1275) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1267);
                U32_dec(&_rc_U32_1267);
                U32 hoisted__U32_1276 = 16;
                (void)hoisted__U32_1276;
                U32 hoisted__U32_1277 = U32_mul(i, hoisted__U32_1276);
                (void)hoisted__U32_1277;
                Type *hoisted__Type_1278 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1278;
                U64 hoisted__U64_1279 = (U64)(hoisted__U32_1277);
                (void)hoisted__U64_1279;
                Type_delete(hoisted__Type_1278, 1);
                Str *hoisted__Str_1280 = ptr_add(self->data, hoisted__U64_1279);
                (void)hoisted__Str_1280;
                (void)hoisted__Str_1280;
                Bool hoisted__Bool_1281 = 0;
                (void)hoisted__Bool_1281;
                Str_delete(hoisted__Str_1280, hoisted__Bool_1281);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1319 = 16;
    (void)hoisted__U32_1319;
    U32 hoisted__U32_1320 = U32_mul(self->cap, hoisted__U32_1319);
    (void)hoisted__U32_1320;
    Type *hoisted__Type_1321 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1321;
    U64 hoisted__U64_1322 = (U64)(hoisted__U32_1320);
    (void)hoisted__U64_1322;
    Type_delete(hoisted__Type_1321, 1);
    void * new_data = malloc(hoisted__U64_1322);
    {
        U32 _re_U32_1283 = self->cap;
        (void)_re_U32_1283;
        U32 _rc_U32_1283 = 0;
        (void)_rc_U32_1283;
        Bool hoisted__Bool_1318 = U32_lte(_rc_U32_1283, _re_U32_1283);
        (void)hoisted__Bool_1318;
        if (hoisted__Bool_1318) {
            while (1) {
                Bool _wcond_Bool_1284 = U32_lt(_rc_U32_1283, _re_U32_1283);
                (void)_wcond_Bool_1284;
                if (_wcond_Bool_1284) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1283);
                U32_inc(&_rc_U32_1283);
                U32 hoisted__U32_1285 = 16;
                (void)hoisted__U32_1285;
                U32 hoisted__U32_1286 = U32_mul(i, hoisted__U32_1285);
                (void)hoisted__U32_1286;
                Type *hoisted__Type_1287 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1287;
                U64 hoisted__U64_1288 = (U64)(hoisted__U32_1286);
                (void)hoisted__U64_1288;
                Type_delete(hoisted__Type_1287, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1288);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1289 = 16;
                (void)hoisted__U32_1289;
                U32 hoisted__U32_1290 = U32_mul(i, hoisted__U32_1289);
                (void)hoisted__U32_1290;
                Type *hoisted__Type_1291 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1291;
                U64 hoisted__U64_1292 = (U64)(hoisted__U32_1290);
                (void)hoisted__U64_1292;
                Type_delete(hoisted__Type_1291, 1);
                U32 hoisted__U32_1293 = 16;
                (void)hoisted__U32_1293;
                Type *hoisted__Type_1294 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1294;
                void *hoisted__v_1295 = ptr_add(new_data, hoisted__U64_1292);
                (void)hoisted__v_1295;
                (void)hoisted__v_1295;
                U64 hoisted__U64_1296 = (U64)(hoisted__U32_1293);
                (void)hoisted__U64_1296;
                Type_delete(hoisted__Type_1294, 1);
                memcpy(hoisted__v_1295, cloned, hoisted__U64_1296);
                U32 hoisted__U32_1297 = 16;
                (void)hoisted__U32_1297;
                Type *hoisted__Type_1298 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1298;
                I32 hoisted__I32_1299 = 0;
                (void)hoisted__I32_1299;
                U64 hoisted__U64_1300 = (U64)(hoisted__U32_1297);
                (void)hoisted__U64_1300;
                Type_delete(hoisted__Type_1298, 1);
                memset(cloned, hoisted__I32_1299, hoisted__U64_1300);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1301 = U32_gt(_rc_U32_1283, _re_U32_1283);
                (void)_wcond_Bool_1301;
                if (_wcond_Bool_1301) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1283);
                U32_dec(&_rc_U32_1283);
                U32 hoisted__U32_1302 = 16;
                (void)hoisted__U32_1302;
                U32 hoisted__U32_1303 = U32_mul(i, hoisted__U32_1302);
                (void)hoisted__U32_1303;
                Type *hoisted__Type_1304 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1304;
                U64 hoisted__U64_1305 = (U64)(hoisted__U32_1303);
                (void)hoisted__U64_1305;
                Type_delete(hoisted__Type_1304, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1305);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1306 = 16;
                (void)hoisted__U32_1306;
                U32 hoisted__U32_1307 = U32_mul(i, hoisted__U32_1306);
                (void)hoisted__U32_1307;
                Type *hoisted__Type_1308 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1308;
                U64 hoisted__U64_1309 = (U64)(hoisted__U32_1307);
                (void)hoisted__U64_1309;
                Type_delete(hoisted__Type_1308, 1);
                U32 hoisted__U32_1310 = 16;
                (void)hoisted__U32_1310;
                Type *hoisted__Type_1311 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1311;
                void *hoisted__v_1312 = ptr_add(new_data, hoisted__U64_1309);
                (void)hoisted__v_1312;
                (void)hoisted__v_1312;
                U64 hoisted__U64_1313 = (U64)(hoisted__U32_1310);
                (void)hoisted__U64_1313;
                Type_delete(hoisted__Type_1311, 1);
                memcpy(hoisted__v_1312, cloned, hoisted__U64_1313);
                U32 hoisted__U32_1314 = 16;
                (void)hoisted__U32_1314;
                Type *hoisted__Type_1315 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1315;
                I32 hoisted__I32_1316 = 0;
                (void)hoisted__I32_1316;
                U64 hoisted__U64_1317 = (U64)(hoisted__U32_1314);
                (void)hoisted__U64_1317;
                Type_delete(hoisted__Type_1315, 1);
                memset(cloned, hoisted__I32_1316, hoisted__U64_1317);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1323 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1323->data = new_data;
    hoisted__Array__Str_1323->cap = self->cap;
    (void)hoisted__Array__Str_1323;
    return hoisted__Array__Str_1323;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1324 = 16;
    (void)hoisted__U32_1324;
    return hoisted__U32_1324;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1325 = 16;
    (void)hoisted__U32_1325;
    Type *hoisted__Type_1326 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1326;
    U64 hoisted__U64_1327 = (U64)(hoisted__U32_1325);
    (void)hoisted__U64_1327;
    Type_delete(hoisted__Type_1326, 1);
    void * hoisted__v_1328 = malloc(hoisted__U64_1327);
    (void)hoisted__v_1328;
    U32 hoisted__U32_1329 = 0;
    (void)hoisted__U32_1329;
    I64 hoisted__I64_1330 = 1;
    (void)hoisted__I64_1330;
    Vec__Str *hoisted__Vec__Str_1331 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1331->data = hoisted__v_1328;
    hoisted__Vec__Str_1331->count = hoisted__U32_1329;
    hoisted__Vec__Str_1331->cap = hoisted__I64_1330;
    (void)hoisted__Vec__Str_1331;
    return hoisted__Vec__Str_1331;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1332 = self->count;
        (void)_re_U32_1332;
        U32 _rc_U32_1332 = 0;
        (void)_rc_U32_1332;
        Bool hoisted__Bool_1347 = U32_lte(_rc_U32_1332, _re_U32_1332);
        (void)hoisted__Bool_1347;
        if (hoisted__Bool_1347) {
            while (1) {
                Bool _wcond_Bool_1333 = U32_lt(_rc_U32_1332, _re_U32_1332);
                (void)_wcond_Bool_1333;
                if (_wcond_Bool_1333) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1332);
                U32_inc(&_rc_U32_1332);
                U32 hoisted__U32_1334 = 16;
                (void)hoisted__U32_1334;
                U32 hoisted__U32_1335 = U32_mul(i, hoisted__U32_1334);
                (void)hoisted__U32_1335;
                Type *hoisted__Type_1336 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1336;
                U64 hoisted__U64_1337 = (U64)(hoisted__U32_1335);
                (void)hoisted__U64_1337;
                Type_delete(hoisted__Type_1336, 1);
                Str *hoisted__Str_1338 = ptr_add(self->data, hoisted__U64_1337);
                (void)hoisted__Str_1338;
                (void)hoisted__Str_1338;
                Bool hoisted__Bool_1339 = 0;
                (void)hoisted__Bool_1339;
                Str_delete(hoisted__Str_1338, hoisted__Bool_1339);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1340 = U32_gt(_rc_U32_1332, _re_U32_1332);
                (void)_wcond_Bool_1340;
                if (_wcond_Bool_1340) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1332);
                U32_dec(&_rc_U32_1332);
                U32 hoisted__U32_1341 = 16;
                (void)hoisted__U32_1341;
                U32 hoisted__U32_1342 = U32_mul(i, hoisted__U32_1341);
                (void)hoisted__U32_1342;
                Type *hoisted__Type_1343 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1343;
                U64 hoisted__U64_1344 = (U64)(hoisted__U32_1342);
                (void)hoisted__U64_1344;
                Type_delete(hoisted__Type_1343, 1);
                Str *hoisted__Str_1345 = ptr_add(self->data, hoisted__U64_1344);
                (void)hoisted__Str_1345;
                (void)hoisted__Str_1345;
                Bool hoisted__Bool_1346 = 0;
                (void)hoisted__Bool_1346;
                Str_delete(hoisted__Str_1345, hoisted__Bool_1346);
            }
        }
    }
    U32 hoisted__U32_1348 = 0;
    (void)hoisted__U32_1348;
    self->count = hoisted__U32_1348;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1635 = 16;
    (void)hoisted__U32_1635;
    U32 hoisted__U32_1636 = U32_mul(self->cap, hoisted__U32_1635);
    (void)hoisted__U32_1636;
    Type *hoisted__Type_1637 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1637;
    U64 hoisted__U64_1638 = (U64)(hoisted__U32_1636);
    (void)hoisted__U64_1638;
    Type_delete(hoisted__Type_1637, 1);
    void * new_data = malloc(hoisted__U64_1638);
    {
        U32 _re_U32_1599 = self->count;
        (void)_re_U32_1599;
        U32 _rc_U32_1599 = 0;
        (void)_rc_U32_1599;
        Bool hoisted__Bool_1634 = U32_lte(_rc_U32_1599, _re_U32_1599);
        (void)hoisted__Bool_1634;
        if (hoisted__Bool_1634) {
            while (1) {
                Bool _wcond_Bool_1600 = U32_lt(_rc_U32_1599, _re_U32_1599);
                (void)_wcond_Bool_1600;
                if (_wcond_Bool_1600) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1599);
                U32_inc(&_rc_U32_1599);
                U32 hoisted__U32_1601 = 16;
                (void)hoisted__U32_1601;
                U32 hoisted__U32_1602 = U32_mul(i, hoisted__U32_1601);
                (void)hoisted__U32_1602;
                Type *hoisted__Type_1603 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1603;
                U64 hoisted__U64_1604 = (U64)(hoisted__U32_1602);
                (void)hoisted__U64_1604;
                Type_delete(hoisted__Type_1603, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1604);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1605 = 16;
                (void)hoisted__U32_1605;
                U32 hoisted__U32_1606 = U32_mul(i, hoisted__U32_1605);
                (void)hoisted__U32_1606;
                Type *hoisted__Type_1607 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1607;
                U64 hoisted__U64_1608 = (U64)(hoisted__U32_1606);
                (void)hoisted__U64_1608;
                Type_delete(hoisted__Type_1607, 1);
                U32 hoisted__U32_1609 = 16;
                (void)hoisted__U32_1609;
                Type *hoisted__Type_1610 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1610;
                void *hoisted__v_1611 = ptr_add(new_data, hoisted__U64_1608);
                (void)hoisted__v_1611;
                (void)hoisted__v_1611;
                U64 hoisted__U64_1612 = (U64)(hoisted__U32_1609);
                (void)hoisted__U64_1612;
                Type_delete(hoisted__Type_1610, 1);
                memcpy(hoisted__v_1611, cloned, hoisted__U64_1612);
                U32 hoisted__U32_1613 = 16;
                (void)hoisted__U32_1613;
                Type *hoisted__Type_1614 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1614;
                I32 hoisted__I32_1615 = 0;
                (void)hoisted__I32_1615;
                U64 hoisted__U64_1616 = (U64)(hoisted__U32_1613);
                (void)hoisted__U64_1616;
                Type_delete(hoisted__Type_1614, 1);
                memset(cloned, hoisted__I32_1615, hoisted__U64_1616);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1617 = U32_gt(_rc_U32_1599, _re_U32_1599);
                (void)_wcond_Bool_1617;
                if (_wcond_Bool_1617) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1599);
                U32_dec(&_rc_U32_1599);
                U32 hoisted__U32_1618 = 16;
                (void)hoisted__U32_1618;
                U32 hoisted__U32_1619 = U32_mul(i, hoisted__U32_1618);
                (void)hoisted__U32_1619;
                Type *hoisted__Type_1620 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1620;
                U64 hoisted__U64_1621 = (U64)(hoisted__U32_1619);
                (void)hoisted__U64_1621;
                Type_delete(hoisted__Type_1620, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1621);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1622 = 16;
                (void)hoisted__U32_1622;
                U32 hoisted__U32_1623 = U32_mul(i, hoisted__U32_1622);
                (void)hoisted__U32_1623;
                Type *hoisted__Type_1624 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1624;
                U64 hoisted__U64_1625 = (U64)(hoisted__U32_1623);
                (void)hoisted__U64_1625;
                Type_delete(hoisted__Type_1624, 1);
                U32 hoisted__U32_1626 = 16;
                (void)hoisted__U32_1626;
                Type *hoisted__Type_1627 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1627;
                void *hoisted__v_1628 = ptr_add(new_data, hoisted__U64_1625);
                (void)hoisted__v_1628;
                (void)hoisted__v_1628;
                U64 hoisted__U64_1629 = (U64)(hoisted__U32_1626);
                (void)hoisted__U64_1629;
                Type_delete(hoisted__Type_1627, 1);
                memcpy(hoisted__v_1628, cloned, hoisted__U64_1629);
                U32 hoisted__U32_1630 = 16;
                (void)hoisted__U32_1630;
                Type *hoisted__Type_1631 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1631;
                I32 hoisted__I32_1632 = 0;
                (void)hoisted__I32_1632;
                U64 hoisted__U64_1633 = (U64)(hoisted__U32_1630);
                (void)hoisted__U64_1633;
                Type_delete(hoisted__Type_1631, 1);
                memset(cloned, hoisted__I32_1632, hoisted__U64_1633);
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1639 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1639->data = new_data;
    hoisted__Vec__Str_1639->count = self->count;
    hoisted__Vec__Str_1639->cap = self->cap;
    (void)hoisted__Vec__Str_1639;
    return hoisted__Vec__Str_1639;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1640 = 16;
    (void)hoisted__U32_1640;
    return hoisted__U32_1640;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1643 = 8;
    (void)hoisted__U32_1643;
    return hoisted__U32_1643;
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
    I64 hoisted__I64_1832 = 0;
    (void)hoisted__I64_1832;
    Bool hoisted__Bool_1833 = I64_eq(val, hoisted__I64_1832);
    (void)hoisted__Bool_1833;
    if (hoisted__Bool_1833) {
        U64 hoisted__U64_1802 = 2ULL;
        (void)hoisted__U64_1802;
        void * buf = malloc(hoisted__U64_1802);
        I64 hoisted__I64_1803 = 48;
        (void)hoisted__I64_1803;
        U64 hoisted__U64_1804 = 1ULL;
        (void)hoisted__U64_1804;
        memcpy(buf, &hoisted__I64_1803, hoisted__U64_1804);
        U64 hoisted__U64_1805 = 1ULL;
        (void)hoisted__U64_1805;
        void *hoisted__v_1806 = ptr_add(buf, hoisted__U64_1805);
        (void)hoisted__v_1806;
        (void)hoisted__v_1806;
        I32 hoisted__I32_1807 = 0;
        (void)hoisted__I32_1807;
        U64 hoisted__U64_1808 = 1ULL;
        (void)hoisted__U64_1808;
        memset(hoisted__v_1806, hoisted__I32_1807, hoisted__U64_1808);
        I64 hoisted__I64_1809 = 1;
        (void)hoisted__I64_1809;
        I64 hoisted__I64_1810 = 1;
        (void)hoisted__I64_1810;
        Str *hoisted__Str_1811 = malloc(sizeof(Str));
        hoisted__Str_1811->c_str = buf;
        hoisted__Str_1811->count = hoisted__I64_1809;
        hoisted__Str_1811->cap = hoisted__I64_1810;
        (void)hoisted__Str_1811;
        { Str * _ret_val = hoisted__Str_1811;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1834 = 0;
    (void)hoisted__I64_1834;
    Bool hoisted__Bool_1835 = I64_lt(val, hoisted__I64_1834);
    (void)hoisted__Bool_1835;
    if (hoisted__Bool_1835) {
        Bool hoisted__Bool_1812 = 1;
        (void)hoisted__Bool_1812;
        is_neg = hoisted__Bool_1812;
        I64 hoisted__I64_1813 = 0;
        (void)hoisted__I64_1813;
        I64 hoisted__I64_1814 = I64_sub(hoisted__I64_1813, val);
        (void)hoisted__I64_1814;
        v = hoisted__I64_1814;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1816 = 0;
        (void)hoisted__I64_1816;
        Bool _wcond_Bool_1815 = I64_gt(tmp, hoisted__I64_1816);
        (void)_wcond_Bool_1815;
        if (_wcond_Bool_1815) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1817 = 10;
        (void)hoisted__I64_1817;
        I64 hoisted__I64_1818 = I64_div(tmp, hoisted__I64_1817);
        (void)hoisted__I64_1818;
        tmp = hoisted__I64_1818;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1836 = 1ULL;
    (void)hoisted__U64_1836;
    U64 hoisted__U64_1837 = U64_add(total, hoisted__U64_1836);
    (void)hoisted__U64_1837;
    void * buf = malloc(hoisted__U64_1837);
    if (is_neg) {
        I64 hoisted__I64_1819 = 45;
        (void)hoisted__I64_1819;
        U64 hoisted__U64_1820 = 1ULL;
        (void)hoisted__U64_1820;
        memcpy(buf, &hoisted__I64_1819, hoisted__U64_1820);
    }
    U64 hoisted__U64_1838 = 1ULL;
    (void)hoisted__U64_1838;
    U64 i = U64_sub(total, hoisted__U64_1838);
    while (1) {
        I64 hoisted__I64_1822 = 0;
        (void)hoisted__I64_1822;
        Bool _wcond_Bool_1821 = I64_gt(v, hoisted__I64_1822);
        (void)_wcond_Bool_1821;
        if (_wcond_Bool_1821) {
        } else {
            break;
        }
        I64 hoisted__I64_1823 = 10;
        (void)hoisted__I64_1823;
        I64 hoisted__I64_1824 = I64_mod(v, hoisted__I64_1823);
        (void)hoisted__I64_1824;
        I64 hoisted__I64_1825 = 48;
        (void)hoisted__I64_1825;
        I64 hoisted__I64_1826 = I64_add(hoisted__I64_1824, hoisted__I64_1825);
        (void)hoisted__I64_1826;
        void *hoisted__v_1827 = ptr_add(buf, i);
        (void)hoisted__v_1827;
        (void)hoisted__v_1827;
        U8 hoisted__U8_1828 = I64_to_u8(hoisted__I64_1826);
        (void)hoisted__U8_1828;
        U64 hoisted__U64_1829 = 1ULL;
        (void)hoisted__U64_1829;
        memcpy(hoisted__v_1827, &hoisted__U8_1828, hoisted__U64_1829);
        I64 hoisted__I64_1830 = 10;
        (void)hoisted__I64_1830;
        I64 hoisted__I64_1831 = I64_div(v, hoisted__I64_1830);
        (void)hoisted__I64_1831;
        v = hoisted__I64_1831;
        U64_dec(&i);
    }
    void *hoisted__v_1839 = ptr_add(buf, total);
    (void)hoisted__v_1839;
    (void)hoisted__v_1839;
    I32 hoisted__I32_1840 = 0;
    (void)hoisted__I32_1840;
    U64 hoisted__U64_1841 = 1ULL;
    (void)hoisted__U64_1841;
    memset(hoisted__v_1839, hoisted__I32_1840, hoisted__U64_1841);
    Str *hoisted__Str_1842 = malloc(sizeof(Str));
    hoisted__Str_1842->c_str = buf;
    hoisted__Str_1842->count = total;
    hoisted__Str_1842->cap = total;
    (void)hoisted__Str_1842;
    return hoisted__Str_1842;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1862 = 8;
    (void)hoisted__U32_1862;
    return hoisted__U32_1862;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1983 = 0;
    (void)hoisted__U32_1983;
    U64 hoisted__U64_1984 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1983); });
    (void)hoisted__U64_1984;
    return hoisted__U64_1984;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1987 = I64_cmp(a, b);
    (void)hoisted__I64_1987;
    I64 hoisted__I64_1988 = -1;
    (void)hoisted__I64_1988;
    Bool hoisted__Bool_1989 = I64_eq(hoisted__I64_1987, hoisted__I64_1988);
    (void)hoisted__Bool_1989;
    return hoisted__Bool_1989;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1990 = I64_cmp(a, b);
    (void)hoisted__I64_1990;
    I64 hoisted__I64_1991 = 1;
    (void)hoisted__I64_1991;
    Bool hoisted__Bool_1992 = I64_eq(hoisted__I64_1990, hoisted__I64_1991);
    (void)hoisted__Bool_1992;
    return hoisted__Bool_1992;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1993 = I64_eq(a, b);
    (void)hoisted__Bool_1993;
    Bool hoisted__Bool_1994 = not(hoisted__Bool_1993);
    (void)hoisted__Bool_1994;
    return hoisted__Bool_1994;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2029 = 0;
    (void)_m_Bool_2029;
    {
        Bool hoisted__Bool_2032 = 1;
        (void)hoisted__Bool_2032;
        Bool hoisted__Bool_2033 = Bool_eq(a, hoisted__Bool_2032);
        (void)hoisted__Bool_2033;
        if (hoisted__Bool_2033) {
            Bool hoisted__Bool_2030 = Bool_clone(&b);
            (void)hoisted__Bool_2030;
            _m_Bool_2029 = hoisted__Bool_2030;
        } else {
            Bool hoisted__Bool_2031 = 0;
            (void)hoisted__Bool_2031;
            _m_Bool_2029 = hoisted__Bool_2031;
        }
    }
    return _m_Bool_2029;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2043 = Bool_eq(a, b);
    (void)hoisted__Bool_2043;
    if (hoisted__Bool_2043) {
        I64 hoisted__I64_2041 = 0;
        (void)hoisted__I64_2041;
        { I64 _ret_val = hoisted__I64_2041;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2042 = -1;
        (void)hoisted__I64_2042;
        return hoisted__I64_2042;
    }
    I64 hoisted__I64_2044 = 1;
    (void)hoisted__I64_2044;
    return hoisted__I64_2044;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2045 = 1;
    (void)hoisted__U32_2045;
    return hoisted__U32_2045;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2046 = 0;
    (void)hoisted__U32_2046;
    U64 hoisted__U64_2047 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2046); });
    (void)hoisted__U64_2047;
    return hoisted__U64_2047;
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
    Bool hoisted__Bool_2073 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2073;
    if (hoisted__Bool_2073) {
        Bool hoisted__Bool_2063 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2063;
        { Bool _ret_val = hoisted__Bool_2063;
                return _ret_val; }
    }
    Bool hoisted__Bool_2074 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2074;
    if (hoisted__Bool_2074) {
        Bool hoisted__Bool_2064 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2064;
        { Bool _ret_val = hoisted__Bool_2064;
                return _ret_val; }
    }
    Bool hoisted__Bool_2075 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2075;
    if (hoisted__Bool_2075) {
        Bool hoisted__Bool_2065 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2065;
        { Bool _ret_val = hoisted__Bool_2065;
                return _ret_val; }
    }
    Bool hoisted__Bool_2076 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2076;
    if (hoisted__Bool_2076) {
        Bool hoisted__Bool_2066 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2066;
        { Bool _ret_val = hoisted__Bool_2066;
                return _ret_val; }
    }
    Bool hoisted__Bool_2077 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2077;
    if (hoisted__Bool_2077) {
        Bool hoisted__Bool_2067 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2067;
        { Bool _ret_val = hoisted__Bool_2067;
                return _ret_val; }
    }
    Bool hoisted__Bool_2078 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2078;
    if (hoisted__Bool_2078) {
        Bool hoisted__Bool_2068 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2068;
        { Bool _ret_val = hoisted__Bool_2068;
                return _ret_val; }
    }
    Bool hoisted__Bool_2079 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2079;
    if (hoisted__Bool_2079) {
        Bool hoisted__Bool_2069 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2069;
        { Bool _ret_val = hoisted__Bool_2069;
                return _ret_val; }
    }
    Bool hoisted__Bool_2080 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2080;
    if (hoisted__Bool_2080) {
        Bool hoisted__Bool_2070 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2070;
        { Bool _ret_val = hoisted__Bool_2070;
                return _ret_val; }
    }
    Bool hoisted__Bool_2081 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2081;
    if (hoisted__Bool_2081) {
        Bool hoisted__Bool_2071 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2071;
        { Bool _ret_val = hoisted__Bool_2071;
                return _ret_val; }
    }
    Bool hoisted__Bool_2082 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2082;
    if (hoisted__Bool_2082) {
        Bool hoisted__Bool_2072 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2072;
        { Bool _ret_val = hoisted__Bool_2072;
                return _ret_val; }
    }
    Bool hoisted__Bool_2083 = 0;
    (void)hoisted__Bool_2083;
    return hoisted__Bool_2083;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2105 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2105;
    if (hoisted__Bool_2105) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2106 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2106;
    if (hoisted__Bool_2106) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2107 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2107;
    if (hoisted__Bool_2107) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2108 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2108;
    if (hoisted__Bool_2108) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2109 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2109;
    if (hoisted__Bool_2109) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2110 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2110;
    if (hoisted__Bool_2110) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2111 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2111;
    if (hoisted__Bool_2111) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2112 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2112;
    if (hoisted__Bool_2112) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2113 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2113;
    if (hoisted__Bool_2113) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2114 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2114;
    if (hoisted__Bool_2114) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2115 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2115;
    UNREACHABLE(&hoisted__Str_2115);
    Str_delete(&hoisted__Str_2115, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2116 = 4;
    (void)hoisted__U32_2116;
    return hoisted__U32_2116;
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
    Bool hoisted__Bool_2168 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2168;
    if (hoisted__Bool_2168) {
        Str *hoisted__Str_2158 = get_payload(self);
        (void)hoisted__Str_2158;
        (void)hoisted__Str_2158;
        Bool hoisted__Bool_2159 = 0;
        (void)hoisted__Bool_2159;
        Str_delete(hoisted__Str_2158, hoisted__Bool_2159);
    }
    Bool hoisted__Bool_2169 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2169;
    if (hoisted__Bool_2169) {
        Str *hoisted__Str_2160 = get_payload(self);
        (void)hoisted__Str_2160;
        (void)hoisted__Str_2160;
        Bool hoisted__Bool_2161 = 0;
        (void)hoisted__Bool_2161;
        Str_delete(hoisted__Str_2160, hoisted__Bool_2161);
    }
    Bool hoisted__Bool_2170 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2170;
    if (hoisted__Bool_2170) {
        Str *hoisted__Str_2162 = get_payload(self);
        (void)hoisted__Str_2162;
        (void)hoisted__Str_2162;
        Bool hoisted__Bool_2163 = 0;
        (void)hoisted__Bool_2163;
        Str_delete(hoisted__Str_2162, hoisted__Bool_2163);
    }
    Bool hoisted__Bool_2171 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2171;
    if (hoisted__Bool_2171) {
        Primitive *hoisted__Primitive_2164 = get_payload(self);
        (void)hoisted__Primitive_2164;
        (void)hoisted__Primitive_2164;
        Bool hoisted__Bool_2165 = 0;
        (void)hoisted__Bool_2165;
        Primitive_delete(hoisted__Primitive_2164, hoisted__Bool_2165);
    }
    Bool hoisted__Bool_2172 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2172;
    if (hoisted__Bool_2172) {
        Str *hoisted__Str_2166 = get_payload(self);
        (void)hoisted__Str_2166;
        (void)hoisted__Str_2166;
        Bool hoisted__Bool_2167 = 0;
        (void)hoisted__Bool_2167;
        Str_delete(hoisted__Str_2166, hoisted__Bool_2167);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2241 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2241;
    if (hoisted__Bool_2241) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2242 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2243 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2243;
    if (hoisted__Bool_2243) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2233 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2233;
        Type *hoisted__Type_2234 = Type_Struct(hoisted__Str_2233);
        (void)hoisted__Type_2234;
        { Type * _ret_val = hoisted__Type_2234;
                return _ret_val; }
    }
    Bool hoisted__Bool_2244 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2245 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2245;
    if (hoisted__Bool_2245) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2235 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2235;
        Type *hoisted__Type_2236 = Type_Enum(hoisted__Str_2235);
        (void)hoisted__Type_2236;
        { Type * _ret_val = hoisted__Type_2236;
                return _ret_val; }
    }
    Bool hoisted__Bool_2246 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2246;
    if (hoisted__Bool_2246) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2247 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2247;
    if (hoisted__Bool_2247) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2248 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2248;
    if (hoisted__Bool_2248) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2249 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2249;
    if (hoisted__Bool_2249) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2250 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2250;
    if (hoisted__Bool_2250) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2237 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2237;
        Type *hoisted__Type_2238 = Type_Custom(hoisted__Str_2237);
        (void)hoisted__Type_2238;
        { Type * _ret_val = hoisted__Type_2238;
                return _ret_val; }
    }
    Bool hoisted__Bool_2251 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2251;
    if (hoisted__Bool_2251) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2239 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2239;
        Type *hoisted__Type_2240 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2239; _oa; }));
        (void)hoisted__Type_2240;
        { Type * _ret_val = hoisted__Type_2240;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2252 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2252;
    Type *hoisted__Type_2253 = Type_FuncPtrSig(hoisted__Str_2252);
    (void)hoisted__Type_2253;
    return hoisted__Type_2253;
}

U32 Type_size(void) {
    U32 hoisted__U32_2254 = 24;
    (void)hoisted__U32_2254;
    return hoisted__U32_2254;
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
    Bool hoisted__Bool_2355 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2355;
    if (hoisted__Bool_2355) {
        Bool hoisted__Bool_2347 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2347;
        { Bool _ret_val = hoisted__Bool_2347;
                return _ret_val; }
    }
    Bool hoisted__Bool_2356 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2356;
    if (hoisted__Bool_2356) {
        Bool hoisted__Bool_2348 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2348;
        { Bool _ret_val = hoisted__Bool_2348;
                return _ret_val; }
    }
    Bool hoisted__Bool_2357 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2357;
    if (hoisted__Bool_2357) {
        Bool hoisted__Bool_2349 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2349;
        { Bool _ret_val = hoisted__Bool_2349;
                return _ret_val; }
    }
    Bool hoisted__Bool_2358 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2358;
    if (hoisted__Bool_2358) {
        Bool hoisted__Bool_2350 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2350;
        { Bool _ret_val = hoisted__Bool_2350;
                return _ret_val; }
    }
    Bool hoisted__Bool_2359 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2359;
    if (hoisted__Bool_2359) {
        Bool hoisted__Bool_2351 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2351;
        { Bool _ret_val = hoisted__Bool_2351;
                return _ret_val; }
    }
    Bool hoisted__Bool_2360 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2360;
    if (hoisted__Bool_2360) {
        Bool hoisted__Bool_2352 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2352;
        { Bool _ret_val = hoisted__Bool_2352;
                return _ret_val; }
    }
    Bool hoisted__Bool_2361 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2361;
    if (hoisted__Bool_2361) {
        Bool hoisted__Bool_2353 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2353;
        { Bool _ret_val = hoisted__Bool_2353;
                return _ret_val; }
    }
    Bool hoisted__Bool_2362 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2362;
    if (hoisted__Bool_2362) {
        Bool hoisted__Bool_2354 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2354;
        { Bool _ret_val = hoisted__Bool_2354;
                return _ret_val; }
    }
    Bool hoisted__Bool_2363 = 0;
    (void)hoisted__Bool_2363;
    return hoisted__Bool_2363;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2381 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2381;
    if (hoisted__Bool_2381) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2382 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2382;
    if (hoisted__Bool_2382) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2383 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2383;
    if (hoisted__Bool_2383) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2384 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2384;
    if (hoisted__Bool_2384) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2385 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2385;
    if (hoisted__Bool_2385) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2386 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2386;
    if (hoisted__Bool_2386) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2387 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2387;
    if (hoisted__Bool_2387) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2388 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2388;
    if (hoisted__Bool_2388) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2389 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2389;
    UNREACHABLE(&hoisted__Str_2389);
    Str_delete(&hoisted__Str_2389, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2390 = 4;
    (void)hoisted__U32_2390;
    return hoisted__U32_2390;
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
    Bool hoisted__Bool_2395 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2395;
    if (hoisted__Bool_2395) {
        Bool hoisted__Bool_2392 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2392;
        { Bool _ret_val = hoisted__Bool_2392;
                return _ret_val; }
    }
    Bool hoisted__Bool_2396 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2396;
    if (hoisted__Bool_2396) {
        Bool hoisted__Bool_2393 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2393;
        { Bool _ret_val = hoisted__Bool_2393;
                return _ret_val; }
    }
    Bool hoisted__Bool_2397 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2397;
    if (hoisted__Bool_2397) {
        Bool hoisted__Bool_2394 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2394;
        { Bool _ret_val = hoisted__Bool_2394;
                return _ret_val; }
    }
    Bool hoisted__Bool_2398 = 0;
    (void)hoisted__Bool_2398;
    return hoisted__Bool_2398;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2406 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2406;
    if (hoisted__Bool_2406) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2407 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2407;
    if (hoisted__Bool_2407) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2408 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2408;
    if (hoisted__Bool_2408) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2409 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2409;
    UNREACHABLE(&hoisted__Str_2409);
    Str_delete(&hoisted__Str_2409, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2410 = 4;
    (void)hoisted__U32_2410;
    return hoisted__U32_2410;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2412 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2412;
    Declaration *hoisted__Declaration_2413 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2413->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2413->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2413->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2413->is_mut = self->is_mut;
    hoisted__Declaration_2413->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2413->is_priv = self->is_priv;
    hoisted__Declaration_2413->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2413->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2413->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2413->default_value = hoisted__Expr_2412;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2413->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2413;
    return hoisted__Declaration_2413;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2414 = 0;
    (void)hoisted__Bool_2414;
    Str_delete(&self->name, hoisted__Bool_2414);
    Bool hoisted__Bool_2415 = 0;
    (void)hoisted__Bool_2415;
    Str_delete(&self->doc, hoisted__Bool_2415);
    Bool hoisted__Bool_2416 = 0;
    (void)hoisted__Bool_2416;
    Str_delete(&self->explicit_type, hoisted__Bool_2416);
    Bool hoisted__Bool_2417 = 0;
    (void)hoisted__Bool_2417;
    Bool_delete(&self->is_mut, hoisted__Bool_2417);
    Bool hoisted__Bool_2418 = 0;
    (void)hoisted__Bool_2418;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2418);
    Bool hoisted__Bool_2419 = 0;
    (void)hoisted__Bool_2419;
    Bool_delete(&self->is_priv, hoisted__Bool_2419);
    Bool hoisted__Bool_2420 = 0;
    (void)hoisted__Bool_2420;
    Bool_delete(&self->used, hoisted__Bool_2420);
    Bool hoisted__Bool_2421 = 0;
    (void)hoisted__Bool_2421;
    OwnType_delete(&self->own_type, hoisted__Bool_2421);
    Bool hoisted__Bool_2422 = 0;
    (void)hoisted__Bool_2422;
    Type_delete(&self->til_type, hoisted__Bool_2422);
    Bool hoisted__Bool_2423 = 1;
    (void)hoisted__Bool_2423;
    Expr_delete(self->default_value, hoisted__Bool_2423);
    Bool hoisted__Bool_2424 = 0;
    (void)hoisted__Bool_2424;
    Str_delete(&self->orig_name, hoisted__Bool_2424);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2425 = 104;
    (void)hoisted__U32_2425;
    return hoisted__U32_2425;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2427 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2427->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2427->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2427->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2427->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2427->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2427->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2427->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2427->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2427->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2427->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2427->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2427;
    return hoisted__FunctionDef_2427;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2428 = 0;
    (void)hoisted__Bool_2428;
    FuncType_delete(&self->func_type, hoisted__Bool_2428);
    Bool hoisted__Bool_2429 = 0;
    (void)hoisted__Bool_2429;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2429);
    Bool hoisted__Bool_2430 = 0;
    (void)hoisted__Bool_2430;
    Str_delete(&self->return_type, hoisted__Bool_2430);
    Bool hoisted__Bool_2431 = 0;
    (void)hoisted__Bool_2431;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2431);
    Bool hoisted__Bool_2432 = 0;
    (void)hoisted__Bool_2432;
    I32_delete(&self->variadic_index, hoisted__Bool_2432);
    Bool hoisted__Bool_2433 = 0;
    (void)hoisted__Bool_2433;
    I32_delete(&self->kwargs_index, hoisted__Bool_2433);
    Bool hoisted__Bool_2434 = 0;
    (void)hoisted__Bool_2434;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2434);
    Bool hoisted__Bool_2435 = 0;
    (void)hoisted__Bool_2435;
    Bool_delete(&self->auto_generated, hoisted__Bool_2435);
    Bool hoisted__Bool_2436 = 0;
    (void)hoisted__Bool_2436;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2436);
    Bool hoisted__Bool_2437 = 0;
    (void)hoisted__Bool_2437;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2437);
    Bool hoisted__Bool_2438 = 0;
    (void)hoisted__Bool_2438;
    Str_delete(&self->closure_name, hoisted__Bool_2438);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2439 = 0;
    (void)hoisted__U32_2439;
    U64 hoisted__U64_2440 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2439); });
    (void)hoisted__U64_2440;
    return hoisted__U64_2440;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2441 = 104;
    (void)hoisted__U32_2441;
    return hoisted__U32_2441;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2444 = malloc(sizeof(FCallData));
    hoisted__FCallData_2444->is_splat = self->is_splat;
    hoisted__FCallData_2444->does_throw = self->does_throw;
    hoisted__FCallData_2444->is_bang = self->is_bang;
    hoisted__FCallData_2444->own_args = self->own_args;
    hoisted__FCallData_2444->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2444->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2444;
    return hoisted__FCallData_2444;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2445 = 0;
    (void)hoisted__Bool_2445;
    Bool_delete(&self->is_splat, hoisted__Bool_2445);
    Bool hoisted__Bool_2446 = 0;
    (void)hoisted__Bool_2446;
    Bool_delete(&self->does_throw, hoisted__Bool_2446);
    Bool hoisted__Bool_2447 = 0;
    (void)hoisted__Bool_2447;
    Bool_delete(&self->is_bang, hoisted__Bool_2447);
    Bool hoisted__Bool_2448 = 0;
    (void)hoisted__Bool_2448;
    U64_delete(&self->own_args, hoisted__Bool_2448);
    Bool hoisted__Bool_2449 = 0;
    (void)hoisted__Bool_2449;
    Bool_delete(&self->swap_replace, hoisted__Bool_2449);
    Bool hoisted__Bool_2450 = 0;
    (void)hoisted__Bool_2450;
    Type_delete(&self->til_type, hoisted__Bool_2450);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2451 = 0;
    (void)hoisted__U32_2451;
    U64 hoisted__U64_2452 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2451); });
    (void)hoisted__U64_2452;
    return hoisted__U64_2452;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2453 = 48;
    (void)hoisted__U32_2453;
    return hoisted__U32_2453;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2465 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2465->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2465->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2465;
    return hoisted__LiteralNumData_2465;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2466 = 0;
    (void)hoisted__Bool_2466;
    Str_delete(&self->text, hoisted__Bool_2466);
    Bool hoisted__Bool_2467 = 0;
    (void)hoisted__Bool_2467;
    Type_delete(&self->til_type, hoisted__Bool_2467);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2468 = 0;
    (void)hoisted__U32_2468;
    U64 hoisted__U64_2469 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2468); });
    (void)hoisted__U64_2469;
    return hoisted__U64_2469;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2470 = 40;
    (void)hoisted__U32_2470;
    return hoisted__U32_2470;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2481 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2481->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2481->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2481;
    return hoisted__IdentData_2481;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2482 = 0;
    (void)hoisted__Bool_2482;
    Str_delete(&self->name, hoisted__Bool_2482);
    Bool hoisted__Bool_2483 = 0;
    (void)hoisted__Bool_2483;
    Type_delete(&self->til_type, hoisted__Bool_2483);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2484 = 0;
    (void)hoisted__U32_2484;
    U64 hoisted__U64_2485 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2484); });
    (void)hoisted__U64_2485;
    return hoisted__U64_2485;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2486 = 40;
    (void)hoisted__U32_2486;
    return hoisted__U32_2486;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2493 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2493->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2493->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2493;
    return hoisted__FieldAccessData_2493;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2494 = 0;
    (void)hoisted__Bool_2494;
    Str_delete(&self->name, hoisted__Bool_2494);
    Bool hoisted__Bool_2495 = 0;
    (void)hoisted__Bool_2495;
    Type_delete(&self->til_type, hoisted__Bool_2495);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2496 = 0;
    (void)hoisted__U32_2496;
    U64 hoisted__U64_2497 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2496); });
    (void)hoisted__U64_2497;
    return hoisted__U64_2497;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2498 = 40;
    (void)hoisted__U32_2498;
    return hoisted__U32_2498;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2569 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2569->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2569->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2569->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2569->is_interface = self->is_interface;
    hoisted__StructDef_2569->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2569->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2569;
    return hoisted__StructDef_2569;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2570 = 0;
    (void)hoisted__Bool_2570;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2570);
    Bool hoisted__Bool_2571 = 0;
    (void)hoisted__Bool_2571;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2571);
    Bool hoisted__Bool_2572 = 0;
    (void)hoisted__Bool_2572;
    Str_delete(&self->c_tag, hoisted__Bool_2572);
    Bool hoisted__Bool_2573 = 0;
    (void)hoisted__Bool_2573;
    Bool_delete(&self->is_interface, hoisted__Bool_2573);
    Bool hoisted__Bool_2574 = 0;
    (void)hoisted__Bool_2574;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2574);
    Bool hoisted__Bool_2575 = 0;
    (void)hoisted__Bool_2575;
    Str_delete(&self->implements_name, hoisted__Bool_2575);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2576 = 0;
    (void)hoisted__U32_2576;
    U64 hoisted__U64_2577 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2576); });
    (void)hoisted__U64_2577;
    return hoisted__U64_2577;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2578 = 72;
    (void)hoisted__U32_2578;
    return hoisted__U32_2578;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2583 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2583->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2583->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2583->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2583->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2583->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2583;
    return hoisted__EnumDef_2583;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2584 = 0;
    (void)hoisted__Bool_2584;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2584);
    Bool hoisted__Bool_2585 = 0;
    (void)hoisted__Bool_2585;
    Vec__Str_delete(&self->variants, hoisted__Bool_2585);
    Bool hoisted__Bool_2586 = 0;
    (void)hoisted__Bool_2586;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2586);
    Bool hoisted__Bool_2587 = 0;
    (void)hoisted__Bool_2587;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2587);
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    Str_delete(&self->implements_name, hoisted__Bool_2588);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2589 = 0;
    (void)hoisted__U32_2589;
    U64 hoisted__U64_2590 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2589); });
    (void)hoisted__U64_2590;
    return hoisted__U64_2590;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2591 = 96;
    (void)hoisted__U32_2591;
    return hoisted__U32_2591;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2687 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2687->name = *_ca; free(_ca); }
    hoisted__AssignData_2687->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2687->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2687->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2687;
    return hoisted__AssignData_2687;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2688 = 0;
    (void)hoisted__Bool_2688;
    Str_delete(&self->name, hoisted__Bool_2688);
    Bool hoisted__Bool_2689 = 0;
    (void)hoisted__Bool_2689;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2689);
    Bool hoisted__Bool_2690 = 0;
    (void)hoisted__Bool_2690;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2690);
    Bool hoisted__Bool_2691 = 0;
    (void)hoisted__Bool_2691;
    Bool_delete(&self->swap_replace, hoisted__Bool_2691);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2692 = 0;
    (void)hoisted__U32_2692;
    U64 hoisted__U64_2693 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2692); });
    (void)hoisted__U64_2693;
    return hoisted__U64_2693;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2694 = 24;
    (void)hoisted__U32_2694;
    return hoisted__U32_2694;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2696 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2696->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2696->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2696;
    return hoisted__FieldAssignData_2696;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2697 = 0;
    (void)hoisted__Bool_2697;
    Str_delete(&self->name, hoisted__Bool_2697);
    Bool hoisted__Bool_2698 = 0;
    (void)hoisted__Bool_2698;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2698);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2699 = 0;
    (void)hoisted__U32_2699;
    U64 hoisted__U64_2700 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2699); });
    (void)hoisted__U64_2700;
    return hoisted__U64_2700;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2701 = 24;
    (void)hoisted__U32_2701;
    return hoisted__U32_2701;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2703 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2703->name = *_ca; free(_ca); }
    hoisted__ForInData_2703->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2703->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2703;
    return hoisted__ForInData_2703;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2704 = 0;
    (void)hoisted__Bool_2704;
    Str_delete(&self->name, hoisted__Bool_2704);
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    Bool_delete(&self->is_mut, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Type_delete(&self->til_type, hoisted__Bool_2706);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2707 = 0;
    (void)hoisted__U32_2707;
    U64 hoisted__U64_2708 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2707); });
    (void)hoisted__U64_2708;
    return hoisted__U64_2708;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2709 = 48;
    (void)hoisted__U32_2709;
    return hoisted__U32_2709;
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
    Bool hoisted__Bool_2739 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2739;
    if (hoisted__Bool_2739) {
        Str *hoisted__Str_2733 = get_payload(self);
        (void)hoisted__Str_2733;
        (void)hoisted__Str_2733;
        Bool hoisted__Bool_2734 = 0;
        (void)hoisted__Bool_2734;
        Str_delete(hoisted__Str_2733, hoisted__Bool_2734);
    }
    Bool hoisted__Bool_2740 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2740;
    if (hoisted__Bool_2740) {
        LiteralNumData *hoisted__LiteralNumData_2735 = get_payload(self);
        (void)hoisted__LiteralNumData_2735;
        (void)hoisted__LiteralNumData_2735;
        Bool hoisted__Bool_2736 = 0;
        (void)hoisted__Bool_2736;
        LiteralNumData_delete(hoisted__LiteralNumData_2735, hoisted__Bool_2736);
    }
    Bool hoisted__Bool_2741 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2741;
    if (hoisted__Bool_2741) {
        Bool *hoisted__Bool_2737 = get_payload(self);
        (void)hoisted__Bool_2737;
        (void)hoisted__Bool_2737;
        Bool hoisted__Bool_2738 = 0;
        (void)hoisted__Bool_2738;
        Bool_delete(hoisted__Bool_2737, hoisted__Bool_2738);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2781 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2781;
    if (hoisted__Bool_2781) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2776 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2776;
        Literal *hoisted__Literal_2777 = Literal_Str(hoisted__Str_2776);
        (void)hoisted__Literal_2777;
        { Literal * _ret_val = hoisted__Literal_2777;
                return _ret_val; }
    }
    Bool hoisted__Bool_2782 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2782;
    if (hoisted__Bool_2782) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2778 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2778;
        Literal *hoisted__Literal_2779 = Literal_Num(hoisted__LiteralNumData_2778);
        (void)hoisted__Literal_2779;
        { Literal * _ret_val = hoisted__Literal_2779;
                return _ret_val; }
    }
    Bool hoisted__Bool_2783 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2783;
    if (hoisted__Bool_2783) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2780 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2780;
        { Literal * _ret_val = hoisted__Literal_2780;
                return _ret_val; }
    }
    Bool hoisted__Bool_2784 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2784;
    if (hoisted__Bool_2784) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2785 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2785;
    if (hoisted__Bool_2785) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2786 = 48;
    (void)hoisted__U32_2786;
    return hoisted__U32_2786;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2789 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2789->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2789->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2789;
    return hoisted__MatchData_2789;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2790 = 0;
    (void)hoisted__Bool_2790;
    Type_delete(&self->til_type, hoisted__Bool_2790);
    Bool hoisted__Bool_2791 = 0;
    (void)hoisted__Bool_2791;
    Str_delete(&self->result_temp, hoisted__Bool_2791);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2792 = 0;
    (void)hoisted__U32_2792;
    U64 hoisted__U64_2793 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2792); });
    (void)hoisted__U64_2793;
    return hoisted__U64_2793;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2794 = 40;
    (void)hoisted__U32_2794;
    return hoisted__U32_2794;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2799 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2799->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2799;
    return hoisted__CaptureBlockData_2799;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2800 = 0;
    (void)hoisted__Bool_2800;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2800);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2801 = 0;
    (void)hoisted__U32_2801;
    U64 hoisted__U64_2802 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2801); });
    (void)hoisted__U64_2802;
    return hoisted__U64_2802;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2803 = 16;
    (void)hoisted__U32_2803;
    return hoisted__U32_2803;
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
void NodeType_delete(NodeType * self, Bool call_free) {
    Bool hoisted__Bool_2980 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_2980;
    if (hoisted__Bool_2980) {
        Literal *hoisted__Literal_2952 = get_payload(self);
        (void)hoisted__Literal_2952;
        (void)hoisted__Literal_2952;
        Bool hoisted__Bool_2953 = 0;
        (void)hoisted__Bool_2953;
        Literal_delete(hoisted__Literal_2952, hoisted__Bool_2953);
    }
    Bool hoisted__Bool_2981 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_2981;
    if (hoisted__Bool_2981) {
        IdentData *hoisted__IdentData_2954 = get_payload(self);
        (void)hoisted__IdentData_2954;
        (void)hoisted__IdentData_2954;
        Bool hoisted__Bool_2955 = 0;
        (void)hoisted__Bool_2955;
        IdentData_delete(hoisted__IdentData_2954, hoisted__Bool_2955);
    }
    Bool hoisted__Bool_2982 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_2982;
    if (hoisted__Bool_2982) {
        Declaration *hoisted__Declaration_2956 = get_payload(self);
        (void)hoisted__Declaration_2956;
        (void)hoisted__Declaration_2956;
        Bool hoisted__Bool_2957 = 0;
        (void)hoisted__Bool_2957;
        Declaration_delete(hoisted__Declaration_2956, hoisted__Bool_2957);
    }
    Bool hoisted__Bool_2983 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_2983;
    if (hoisted__Bool_2983) {
        AssignData *hoisted__AssignData_2958 = get_payload(self);
        (void)hoisted__AssignData_2958;
        (void)hoisted__AssignData_2958;
        Bool hoisted__Bool_2959 = 0;
        (void)hoisted__Bool_2959;
        AssignData_delete(hoisted__AssignData_2958, hoisted__Bool_2959);
    }
    Bool hoisted__Bool_2984 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_2984;
    if (hoisted__Bool_2984) {
        FCallData *hoisted__FCallData_2960 = get_payload(self);
        (void)hoisted__FCallData_2960;
        (void)hoisted__FCallData_2960;
        Bool hoisted__Bool_2961 = 0;
        (void)hoisted__Bool_2961;
        FCallData_delete(hoisted__FCallData_2960, hoisted__Bool_2961);
    }
    Bool hoisted__Bool_2985 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_2985;
    if (hoisted__Bool_2985) {
        FunctionDef *hoisted__FunctionDef_2962 = get_payload(self);
        (void)hoisted__FunctionDef_2962;
        (void)hoisted__FunctionDef_2962;
        Bool hoisted__Bool_2963 = 0;
        (void)hoisted__Bool_2963;
        FunctionDef_delete(hoisted__FunctionDef_2962, hoisted__Bool_2963);
    }
    Bool hoisted__Bool_2986 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_2986;
    if (hoisted__Bool_2986) {
        StructDef *hoisted__StructDef_2964 = get_payload(self);
        (void)hoisted__StructDef_2964;
        (void)hoisted__StructDef_2964;
        Bool hoisted__Bool_2965 = 0;
        (void)hoisted__Bool_2965;
        StructDef_delete(hoisted__StructDef_2964, hoisted__Bool_2965);
    }
    Bool hoisted__Bool_2987 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_2987;
    if (hoisted__Bool_2987) {
        EnumDef *hoisted__EnumDef_2966 = get_payload(self);
        (void)hoisted__EnumDef_2966;
        (void)hoisted__EnumDef_2966;
        Bool hoisted__Bool_2967 = 0;
        (void)hoisted__Bool_2967;
        EnumDef_delete(hoisted__EnumDef_2966, hoisted__Bool_2967);
    }
    Bool hoisted__Bool_2988 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_2988;
    if (hoisted__Bool_2988) {
        FieldAccessData *hoisted__FieldAccessData_2968 = get_payload(self);
        (void)hoisted__FieldAccessData_2968;
        (void)hoisted__FieldAccessData_2968;
        Bool hoisted__Bool_2969 = 0;
        (void)hoisted__Bool_2969;
        FieldAccessData_delete(hoisted__FieldAccessData_2968, hoisted__Bool_2969);
    }
    Bool hoisted__Bool_2989 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_2989;
    if (hoisted__Bool_2989) {
        FieldAssignData *hoisted__FieldAssignData_2970 = get_payload(self);
        (void)hoisted__FieldAssignData_2970;
        (void)hoisted__FieldAssignData_2970;
        Bool hoisted__Bool_2971 = 0;
        (void)hoisted__Bool_2971;
        FieldAssignData_delete(hoisted__FieldAssignData_2970, hoisted__Bool_2971);
    }
    Bool hoisted__Bool_2990 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_2990;
    if (hoisted__Bool_2990) {
        ForInData *hoisted__ForInData_2972 = get_payload(self);
        (void)hoisted__ForInData_2972;
        (void)hoisted__ForInData_2972;
        Bool hoisted__Bool_2973 = 0;
        (void)hoisted__Bool_2973;
        ForInData_delete(hoisted__ForInData_2972, hoisted__Bool_2973);
    }
    Bool hoisted__Bool_2991 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_2991;
    if (hoisted__Bool_2991) {
        Str *hoisted__Str_2974 = get_payload(self);
        (void)hoisted__Str_2974;
        (void)hoisted__Str_2974;
        Bool hoisted__Bool_2975 = 0;
        (void)hoisted__Bool_2975;
        Str_delete(hoisted__Str_2974, hoisted__Bool_2975);
    }
    Bool hoisted__Bool_2992 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_2992;
    if (hoisted__Bool_2992) {
        MatchData *hoisted__MatchData_2976 = get_payload(self);
        (void)hoisted__MatchData_2976;
        (void)hoisted__MatchData_2976;
        Bool hoisted__Bool_2977 = 0;
        (void)hoisted__Bool_2977;
        MatchData_delete(hoisted__MatchData_2976, hoisted__Bool_2977);
    }
    Bool hoisted__Bool_2993 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_2993;
    if (hoisted__Bool_2993) {
        CaptureBlockData *hoisted__CaptureBlockData_2978 = get_payload(self);
        (void)hoisted__CaptureBlockData_2978;
        (void)hoisted__CaptureBlockData_2978;
        Bool hoisted__Bool_2979 = 0;
        (void)hoisted__Bool_2979;
        CaptureBlockData_delete(hoisted__CaptureBlockData_2978, hoisted__Bool_2979);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3171 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3171;
    if (hoisted__Bool_3171) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3172 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3172;
    if (hoisted__Bool_3172) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3145 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3145;
        NodeType *hoisted__NodeType_3146 = NodeType_Literal(hoisted__Literal_3145);
        (void)hoisted__NodeType_3146;
        { NodeType * _ret_val = hoisted__NodeType_3146;
                return _ret_val; }
    }
    Bool hoisted__Bool_3173 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3173;
    if (hoisted__Bool_3173) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3147 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3147;
        NodeType *hoisted__NodeType_3148 = NodeType_Ident(hoisted__IdentData_3147);
        (void)hoisted__NodeType_3148;
        { NodeType * _ret_val = hoisted__NodeType_3148;
                return _ret_val; }
    }
    Bool hoisted__Bool_3174 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3174;
    if (hoisted__Bool_3174) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3149 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3149;
        NodeType *hoisted__NodeType_3150 = NodeType_Decl(hoisted__Declaration_3149);
        (void)hoisted__NodeType_3150;
        { NodeType * _ret_val = hoisted__NodeType_3150;
                return _ret_val; }
    }
    Bool hoisted__Bool_3175 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3175;
    if (hoisted__Bool_3175) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3151 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3151;
        NodeType *hoisted__NodeType_3152 = NodeType_Assign(hoisted__AssignData_3151);
        (void)hoisted__NodeType_3152;
        { NodeType * _ret_val = hoisted__NodeType_3152;
                return _ret_val; }
    }
    Bool hoisted__Bool_3176 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3176;
    if (hoisted__Bool_3176) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3153 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3153;
        NodeType *hoisted__NodeType_3154 = NodeType_FCall(hoisted__FCallData_3153);
        (void)hoisted__NodeType_3154;
        { NodeType * _ret_val = hoisted__NodeType_3154;
                return _ret_val; }
    }
    Bool hoisted__Bool_3177 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3177;
    if (hoisted__Bool_3177) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3155 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3155;
        NodeType *hoisted__NodeType_3156 = NodeType_FuncDef(hoisted__FunctionDef_3155);
        (void)hoisted__NodeType_3156;
        { NodeType * _ret_val = hoisted__NodeType_3156;
                return _ret_val; }
    }
    Bool hoisted__Bool_3178 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3178;
    if (hoisted__Bool_3178) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3157 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3157;
        NodeType *hoisted__NodeType_3158 = NodeType_StructDef(hoisted__StructDef_3157);
        (void)hoisted__NodeType_3158;
        { NodeType * _ret_val = hoisted__NodeType_3158;
                return _ret_val; }
    }
    Bool hoisted__Bool_3179 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3179;
    if (hoisted__Bool_3179) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3159 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3159;
        NodeType *hoisted__NodeType_3160 = NodeType_EnumDef(hoisted__EnumDef_3159);
        (void)hoisted__NodeType_3160;
        { NodeType * _ret_val = hoisted__NodeType_3160;
                return _ret_val; }
    }
    Bool hoisted__Bool_3180 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3180;
    if (hoisted__Bool_3180) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3161 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3161;
        NodeType *hoisted__NodeType_3162 = NodeType_FieldAccess(hoisted__FieldAccessData_3161);
        (void)hoisted__NodeType_3162;
        { NodeType * _ret_val = hoisted__NodeType_3162;
                return _ret_val; }
    }
    Bool hoisted__Bool_3181 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3181;
    if (hoisted__Bool_3181) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3163 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3163;
        NodeType *hoisted__NodeType_3164 = NodeType_FieldAssign(hoisted__FieldAssignData_3163);
        (void)hoisted__NodeType_3164;
        { NodeType * _ret_val = hoisted__NodeType_3164;
                return _ret_val; }
    }
    Bool hoisted__Bool_3182 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3182;
    if (hoisted__Bool_3182) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3183 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3183;
    if (hoisted__Bool_3183) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3184 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3184;
    if (hoisted__Bool_3184) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3185 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3185;
    if (hoisted__Bool_3185) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3165 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3165;
        NodeType *hoisted__NodeType_3166 = NodeType_ForIn(hoisted__ForInData_3165);
        (void)hoisted__NodeType_3166;
        { NodeType * _ret_val = hoisted__NodeType_3166;
                return _ret_val; }
    }
    Bool hoisted__Bool_3186 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3186;
    if (hoisted__Bool_3186) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3167 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3167;
        NodeType *hoisted__NodeType_3168 = NodeType_NamedArg(hoisted__Str_3167);
        (void)hoisted__NodeType_3168;
        { NodeType * _ret_val = hoisted__NodeType_3168;
                return _ret_val; }
    }
    Bool hoisted__Bool_3187 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3187;
    if (hoisted__Bool_3187) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3188 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3188;
    if (hoisted__Bool_3188) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3189 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3189;
    if (hoisted__Bool_3189) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3190 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3190;
    if (hoisted__Bool_3190) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3169 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3169;
        NodeType *hoisted__NodeType_3170 = NodeType_Match(hoisted__MatchData_3169);
        (void)hoisted__NodeType_3170;
        { NodeType * _ret_val = hoisted__NodeType_3170;
                return _ret_val; }
    }
    Bool hoisted__Bool_3191 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3191;
    if (hoisted__Bool_3191) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3192 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3192;
    if (hoisted__Bool_3192) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3193 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3193;
    if (hoisted__Bool_3193) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3194 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3194;
    if (hoisted__Bool_3194) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3195 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3195;
    if (hoisted__Bool_3195) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
    (void)_clone_payload_CaptureBlock_25;
    (void)_clone_payload_CaptureBlock_25;
    CaptureBlockData *hoisted__CaptureBlockData_3196 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
    (void)hoisted__CaptureBlockData_3196;
    NodeType *hoisted__NodeType_3197 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3196);
    (void)hoisted__NodeType_3197;
    return hoisted__NodeType_3197;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3198 = 112;
    (void)hoisted__U32_3198;
    return hoisted__U32_3198;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3199 = is_null(self);
    (void)hoisted__Bool_3199;
    if (hoisted__Bool_3199) {
        return;
    }
    Bool hoisted__Bool_3200 = 0;
    (void)hoisted__Bool_3200;
    NodeType_delete(&self->node_type, hoisted__Bool_3200);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3244 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3244->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3244->children = *_ca; free(_ca); }
    hoisted__Expr_3244->line = line;
    hoisted__Expr_3244->col = col;
    (void)hoisted__Expr_3244;
    return hoisted__Expr_3244;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3252 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3252->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3252->children = *_ca; free(_ca); }
    hoisted__Expr_3252->line = self->line;
    hoisted__Expr_3252->col = self->col;
    (void)hoisted__Expr_3252;
    return hoisted__Expr_3252;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3253 = 0;
    (void)hoisted__U32_3253;
    U64 hoisted__U64_3254 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3253); });
    (void)hoisted__U64_3254;
    return hoisted__U64_3254;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3255 = 136;
    (void)hoisted__U32_3255;
    return hoisted__U32_3255;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_3842 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_3842->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_3842->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3842;
    return hoisted__Map__I64_Str_3842;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_3987 = 0;
    (void)hoisted__Bool_3987;
    Vec__I64_delete(&self->keys, hoisted__Bool_3987);
    Bool hoisted__Bool_3988 = 0;
    (void)hoisted__Bool_3988;
    Vec__Str_delete(&self->values, hoisted__Bool_3988);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_3989 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_3989->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_3989->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3989;
    return hoisted__Map__I64_Str_3989;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_3990 = 0;
    (void)hoisted__U32_3990;
    U64 hoisted__U64_3991 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3990); });
    (void)hoisted__U64_3991;
    return hoisted__U64_3991;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_3992 = 32;
    (void)hoisted__U32_3992;
    return hoisted__U32_3992;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_3993 = 1;
    (void)hoisted__U32_3993;
    Type *hoisted__Type_3994 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_3994;
    U64 hoisted__U64_3995 = (U64)(hoisted__U32_3993);
    (void)hoisted__U64_3995;
    Type_delete(hoisted__Type_3994, 1);
    void * hoisted__v_3996 = malloc(hoisted__U64_3995);
    (void)hoisted__v_3996;
    U32 hoisted__U32_3997 = 0;
    (void)hoisted__U32_3997;
    I64 hoisted__I64_3998 = 1;
    (void)hoisted__I64_3998;
    Vec__Bool *hoisted__Vec__Bool_3999 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_3999->data = hoisted__v_3996;
    hoisted__Vec__Bool_3999->count = hoisted__U32_3997;
    hoisted__Vec__Bool_3999->cap = hoisted__I64_3998;
    (void)hoisted__Vec__Bool_3999;
    return hoisted__Vec__Bool_3999;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4000 = self->count;
        (void)_re_U32_4000;
        U32 _rc_U32_4000 = 0;
        (void)_rc_U32_4000;
        Bool hoisted__Bool_4015 = U32_lte(_rc_U32_4000, _re_U32_4000);
        (void)hoisted__Bool_4015;
        if (hoisted__Bool_4015) {
            while (1) {
                Bool _wcond_Bool_4001 = U32_lt(_rc_U32_4000, _re_U32_4000);
                (void)_wcond_Bool_4001;
                if (_wcond_Bool_4001) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4000);
                U32_inc(&_rc_U32_4000);
                U32 hoisted__U32_4002 = 1;
                (void)hoisted__U32_4002;
                U32 hoisted__U32_4003 = U32_mul(i, hoisted__U32_4002);
                (void)hoisted__U32_4003;
                Type *hoisted__Type_4004 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4004;
                U64 hoisted__U64_4005 = (U64)(hoisted__U32_4003);
                (void)hoisted__U64_4005;
                Type_delete(hoisted__Type_4004, 1);
                Bool *hoisted__Bool_4006 = ptr_add(self->data, hoisted__U64_4005);
                (void)hoisted__Bool_4006;
                (void)hoisted__Bool_4006;
                Bool hoisted__Bool_4007 = 0;
                (void)hoisted__Bool_4007;
                Bool_delete(hoisted__Bool_4006, hoisted__Bool_4007);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4008 = U32_gt(_rc_U32_4000, _re_U32_4000);
                (void)_wcond_Bool_4008;
                if (_wcond_Bool_4008) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4000);
                U32_dec(&_rc_U32_4000);
                U32 hoisted__U32_4009 = 1;
                (void)hoisted__U32_4009;
                U32 hoisted__U32_4010 = U32_mul(i, hoisted__U32_4009);
                (void)hoisted__U32_4010;
                Type *hoisted__Type_4011 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4011;
                U64 hoisted__U64_4012 = (U64)(hoisted__U32_4010);
                (void)hoisted__U64_4012;
                Type_delete(hoisted__Type_4011, 1);
                Bool *hoisted__Bool_4013 = ptr_add(self->data, hoisted__U64_4012);
                (void)hoisted__Bool_4013;
                (void)hoisted__Bool_4013;
                Bool hoisted__Bool_4014 = 0;
                (void)hoisted__Bool_4014;
                Bool_delete(hoisted__Bool_4013, hoisted__Bool_4014);
            }
        }
    }
    U32 hoisted__U32_4016 = 0;
    (void)hoisted__U32_4016;
    self->count = hoisted__U32_4016;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4303 = 1;
    (void)hoisted__U32_4303;
    U32 hoisted__U32_4304 = U32_mul(self->cap, hoisted__U32_4303);
    (void)hoisted__U32_4304;
    Type *hoisted__Type_4305 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4305;
    U64 hoisted__U64_4306 = (U64)(hoisted__U32_4304);
    (void)hoisted__U64_4306;
    Type_delete(hoisted__Type_4305, 1);
    void * new_data = malloc(hoisted__U64_4306);
    {
        U32 _re_U32_4267 = self->count;
        (void)_re_U32_4267;
        U32 _rc_U32_4267 = 0;
        (void)_rc_U32_4267;
        Bool hoisted__Bool_4302 = U32_lte(_rc_U32_4267, _re_U32_4267);
        (void)hoisted__Bool_4302;
        if (hoisted__Bool_4302) {
            while (1) {
                Bool _wcond_Bool_4268 = U32_lt(_rc_U32_4267, _re_U32_4267);
                (void)_wcond_Bool_4268;
                if (_wcond_Bool_4268) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4267);
                U32_inc(&_rc_U32_4267);
                U32 hoisted__U32_4269 = 1;
                (void)hoisted__U32_4269;
                U32 hoisted__U32_4270 = U32_mul(i, hoisted__U32_4269);
                (void)hoisted__U32_4270;
                Type *hoisted__Type_4271 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4271;
                U64 hoisted__U64_4272 = (U64)(hoisted__U32_4270);
                (void)hoisted__U64_4272;
                Type_delete(hoisted__Type_4271, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4272);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4273 = 1;
                (void)hoisted__U32_4273;
                U32 hoisted__U32_4274 = U32_mul(i, hoisted__U32_4273);
                (void)hoisted__U32_4274;
                Type *hoisted__Type_4275 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4275;
                U64 hoisted__U64_4276 = (U64)(hoisted__U32_4274);
                (void)hoisted__U64_4276;
                Type_delete(hoisted__Type_4275, 1);
                U32 hoisted__U32_4277 = 1;
                (void)hoisted__U32_4277;
                Type *hoisted__Type_4278 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4278;
                void *hoisted__v_4279 = ptr_add(new_data, hoisted__U64_4276);
                (void)hoisted__v_4279;
                (void)hoisted__v_4279;
                U64 hoisted__U64_4280 = (U64)(hoisted__U32_4277);
                (void)hoisted__U64_4280;
                Type_delete(hoisted__Type_4278, 1);
                memcpy(hoisted__v_4279, &cloned, hoisted__U64_4280);
                U32 hoisted__U32_4281 = 1;
                (void)hoisted__U32_4281;
                Type *hoisted__Type_4282 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4282;
                I32 hoisted__I32_4283 = 0;
                (void)hoisted__I32_4283;
                U64 hoisted__U64_4284 = (U64)(hoisted__U32_4281);
                (void)hoisted__U64_4284;
                Type_delete(hoisted__Type_4282, 1);
                memset(&cloned, hoisted__I32_4283, hoisted__U64_4284);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4285 = U32_gt(_rc_U32_4267, _re_U32_4267);
                (void)_wcond_Bool_4285;
                if (_wcond_Bool_4285) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4267);
                U32_dec(&_rc_U32_4267);
                U32 hoisted__U32_4286 = 1;
                (void)hoisted__U32_4286;
                U32 hoisted__U32_4287 = U32_mul(i, hoisted__U32_4286);
                (void)hoisted__U32_4287;
                Type *hoisted__Type_4288 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4288;
                U64 hoisted__U64_4289 = (U64)(hoisted__U32_4287);
                (void)hoisted__U64_4289;
                Type_delete(hoisted__Type_4288, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4289);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4290 = 1;
                (void)hoisted__U32_4290;
                U32 hoisted__U32_4291 = U32_mul(i, hoisted__U32_4290);
                (void)hoisted__U32_4291;
                Type *hoisted__Type_4292 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4292;
                U64 hoisted__U64_4293 = (U64)(hoisted__U32_4291);
                (void)hoisted__U64_4293;
                Type_delete(hoisted__Type_4292, 1);
                U32 hoisted__U32_4294 = 1;
                (void)hoisted__U32_4294;
                Type *hoisted__Type_4295 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4295;
                void *hoisted__v_4296 = ptr_add(new_data, hoisted__U64_4293);
                (void)hoisted__v_4296;
                (void)hoisted__v_4296;
                U64 hoisted__U64_4297 = (U64)(hoisted__U32_4294);
                (void)hoisted__U64_4297;
                Type_delete(hoisted__Type_4295, 1);
                memcpy(hoisted__v_4296, &cloned, hoisted__U64_4297);
                U32 hoisted__U32_4298 = 1;
                (void)hoisted__U32_4298;
                Type *hoisted__Type_4299 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4299;
                I32 hoisted__I32_4300 = 0;
                (void)hoisted__I32_4300;
                U64 hoisted__U64_4301 = (U64)(hoisted__U32_4298);
                (void)hoisted__U64_4301;
                Type_delete(hoisted__Type_4299, 1);
                memset(&cloned, hoisted__I32_4300, hoisted__U64_4301);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4307 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4307->data = new_data;
    hoisted__Vec__Bool_4307->count = self->count;
    hoisted__Vec__Bool_4307->cap = self->cap;
    (void)hoisted__Vec__Bool_4307;
    return hoisted__Vec__Bool_4307;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4308 = 16;
    (void)hoisted__U32_4308;
    return hoisted__U32_4308;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_4625 = 104;
    (void)hoisted__U32_4625;
    Type *hoisted__Type_4626 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4626;
    U64 hoisted__U64_4627 = (U64)(hoisted__U32_4625);
    (void)hoisted__U64_4627;
    Type_delete(hoisted__Type_4626, 1);
    void * hoisted__v_4628 = malloc(hoisted__U64_4627);
    (void)hoisted__v_4628;
    U32 hoisted__U32_4629 = 0;
    (void)hoisted__U32_4629;
    I64 hoisted__I64_4630 = 1;
    (void)hoisted__I64_4630;
    Vec__Declaration *hoisted__Vec__Declaration_4631 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4631->data = hoisted__v_4628;
    hoisted__Vec__Declaration_4631->count = hoisted__U32_4629;
    hoisted__Vec__Declaration_4631->cap = hoisted__I64_4630;
    (void)hoisted__Vec__Declaration_4631;
    return hoisted__Vec__Declaration_4631;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4632 = self->count;
        (void)_re_U32_4632;
        U32 _rc_U32_4632 = 0;
        (void)_rc_U32_4632;
        Bool hoisted__Bool_4647 = U32_lte(_rc_U32_4632, _re_U32_4632);
        (void)hoisted__Bool_4647;
        if (hoisted__Bool_4647) {
            while (1) {
                Bool _wcond_Bool_4633 = U32_lt(_rc_U32_4632, _re_U32_4632);
                (void)_wcond_Bool_4633;
                if (_wcond_Bool_4633) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4632);
                U32_inc(&_rc_U32_4632);
                U32 hoisted__U32_4634 = 104;
                (void)hoisted__U32_4634;
                U32 hoisted__U32_4635 = U32_mul(i, hoisted__U32_4634);
                (void)hoisted__U32_4635;
                Type *hoisted__Type_4636 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4636;
                U64 hoisted__U64_4637 = (U64)(hoisted__U32_4635);
                (void)hoisted__U64_4637;
                Type_delete(hoisted__Type_4636, 1);
                Declaration *hoisted__Declaration_4638 = ptr_add(self->data, hoisted__U64_4637);
                (void)hoisted__Declaration_4638;
                (void)hoisted__Declaration_4638;
                Bool hoisted__Bool_4639 = 0;
                (void)hoisted__Bool_4639;
                Declaration_delete(hoisted__Declaration_4638, hoisted__Bool_4639);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4640 = U32_gt(_rc_U32_4632, _re_U32_4632);
                (void)_wcond_Bool_4640;
                if (_wcond_Bool_4640) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4632);
                U32_dec(&_rc_U32_4632);
                U32 hoisted__U32_4641 = 104;
                (void)hoisted__U32_4641;
                U32 hoisted__U32_4642 = U32_mul(i, hoisted__U32_4641);
                (void)hoisted__U32_4642;
                Type *hoisted__Type_4643 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4643;
                U64 hoisted__U64_4644 = (U64)(hoisted__U32_4642);
                (void)hoisted__U64_4644;
                Type_delete(hoisted__Type_4643, 1);
                Declaration *hoisted__Declaration_4645 = ptr_add(self->data, hoisted__U64_4644);
                (void)hoisted__Declaration_4645;
                (void)hoisted__Declaration_4645;
                Bool hoisted__Bool_4646 = 0;
                (void)hoisted__Bool_4646;
                Declaration_delete(hoisted__Declaration_4645, hoisted__Bool_4646);
            }
        }
    }
    U32 hoisted__U32_4648 = 0;
    (void)hoisted__U32_4648;
    self->count = hoisted__U32_4648;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_4935 = 104;
    (void)hoisted__U32_4935;
    U32 hoisted__U32_4936 = U32_mul(self->cap, hoisted__U32_4935);
    (void)hoisted__U32_4936;
    Type *hoisted__Type_4937 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4937;
    U64 hoisted__U64_4938 = (U64)(hoisted__U32_4936);
    (void)hoisted__U64_4938;
    Type_delete(hoisted__Type_4937, 1);
    void * new_data = malloc(hoisted__U64_4938);
    {
        U32 _re_U32_4899 = self->count;
        (void)_re_U32_4899;
        U32 _rc_U32_4899 = 0;
        (void)_rc_U32_4899;
        Bool hoisted__Bool_4934 = U32_lte(_rc_U32_4899, _re_U32_4899);
        (void)hoisted__Bool_4934;
        if (hoisted__Bool_4934) {
            while (1) {
                Bool _wcond_Bool_4900 = U32_lt(_rc_U32_4899, _re_U32_4899);
                (void)_wcond_Bool_4900;
                if (_wcond_Bool_4900) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4899);
                U32_inc(&_rc_U32_4899);
                U32 hoisted__U32_4901 = 104;
                (void)hoisted__U32_4901;
                U32 hoisted__U32_4902 = U32_mul(i, hoisted__U32_4901);
                (void)hoisted__U32_4902;
                Type *hoisted__Type_4903 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4903;
                U64 hoisted__U64_4904 = (U64)(hoisted__U32_4902);
                (void)hoisted__U64_4904;
                Type_delete(hoisted__Type_4903, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_4904);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4905 = 104;
                (void)hoisted__U32_4905;
                U32 hoisted__U32_4906 = U32_mul(i, hoisted__U32_4905);
                (void)hoisted__U32_4906;
                Type *hoisted__Type_4907 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4907;
                U64 hoisted__U64_4908 = (U64)(hoisted__U32_4906);
                (void)hoisted__U64_4908;
                Type_delete(hoisted__Type_4907, 1);
                U32 hoisted__U32_4909 = 104;
                (void)hoisted__U32_4909;
                Type *hoisted__Type_4910 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4910;
                void *hoisted__v_4911 = ptr_add(new_data, hoisted__U64_4908);
                (void)hoisted__v_4911;
                (void)hoisted__v_4911;
                U64 hoisted__U64_4912 = (U64)(hoisted__U32_4909);
                (void)hoisted__U64_4912;
                Type_delete(hoisted__Type_4910, 1);
                memcpy(hoisted__v_4911, cloned, hoisted__U64_4912);
                U32 hoisted__U32_4913 = 104;
                (void)hoisted__U32_4913;
                Type *hoisted__Type_4914 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4914;
                I32 hoisted__I32_4915 = 0;
                (void)hoisted__I32_4915;
                U64 hoisted__U64_4916 = (U64)(hoisted__U32_4913);
                (void)hoisted__U64_4916;
                Type_delete(hoisted__Type_4914, 1);
                memset(cloned, hoisted__I32_4915, hoisted__U64_4916);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4917 = U32_gt(_rc_U32_4899, _re_U32_4899);
                (void)_wcond_Bool_4917;
                if (_wcond_Bool_4917) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4899);
                U32_dec(&_rc_U32_4899);
                U32 hoisted__U32_4918 = 104;
                (void)hoisted__U32_4918;
                U32 hoisted__U32_4919 = U32_mul(i, hoisted__U32_4918);
                (void)hoisted__U32_4919;
                Type *hoisted__Type_4920 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4920;
                U64 hoisted__U64_4921 = (U64)(hoisted__U32_4919);
                (void)hoisted__U64_4921;
                Type_delete(hoisted__Type_4920, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_4921);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4922 = 104;
                (void)hoisted__U32_4922;
                U32 hoisted__U32_4923 = U32_mul(i, hoisted__U32_4922);
                (void)hoisted__U32_4923;
                Type *hoisted__Type_4924 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4924;
                U64 hoisted__U64_4925 = (U64)(hoisted__U32_4923);
                (void)hoisted__U64_4925;
                Type_delete(hoisted__Type_4924, 1);
                U32 hoisted__U32_4926 = 104;
                (void)hoisted__U32_4926;
                Type *hoisted__Type_4927 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4927;
                void *hoisted__v_4928 = ptr_add(new_data, hoisted__U64_4925);
                (void)hoisted__v_4928;
                (void)hoisted__v_4928;
                U64 hoisted__U64_4929 = (U64)(hoisted__U32_4926);
                (void)hoisted__U64_4929;
                Type_delete(hoisted__Type_4927, 1);
                memcpy(hoisted__v_4928, cloned, hoisted__U64_4929);
                U32 hoisted__U32_4930 = 104;
                (void)hoisted__U32_4930;
                Type *hoisted__Type_4931 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4931;
                I32 hoisted__I32_4932 = 0;
                (void)hoisted__I32_4932;
                U64 hoisted__U64_4933 = (U64)(hoisted__U32_4930);
                (void)hoisted__U64_4933;
                Type_delete(hoisted__Type_4931, 1);
                memset(cloned, hoisted__I32_4932, hoisted__U64_4933);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_4939 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4939->data = new_data;
    hoisted__Vec__Declaration_4939->count = self->count;
    hoisted__Vec__Declaration_4939->cap = self->cap;
    (void)hoisted__Vec__Declaration_4939;
    return hoisted__Vec__Declaration_4939;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_4940 = 16;
    (void)hoisted__U32_4940;
    return hoisted__U32_4940;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_4941 = 136;
    (void)hoisted__U32_4941;
    Type *hoisted__Type_4942 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4942;
    U64 hoisted__U64_4943 = (U64)(hoisted__U32_4941);
    (void)hoisted__U64_4943;
    Type_delete(hoisted__Type_4942, 1);
    void * hoisted__v_4944 = malloc(hoisted__U64_4943);
    (void)hoisted__v_4944;
    U32 hoisted__U32_4945 = 0;
    (void)hoisted__U32_4945;
    I64 hoisted__I64_4946 = 1;
    (void)hoisted__I64_4946;
    Vec__Expr *hoisted__Vec__Expr_4947 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4947->data = hoisted__v_4944;
    hoisted__Vec__Expr_4947->count = hoisted__U32_4945;
    hoisted__Vec__Expr_4947->cap = hoisted__I64_4946;
    (void)hoisted__Vec__Expr_4947;
    return hoisted__Vec__Expr_4947;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_4948 = self->count;
        (void)_re_U32_4948;
        U32 _rc_U32_4948 = 0;
        (void)_rc_U32_4948;
        Bool hoisted__Bool_4963 = U32_lte(_rc_U32_4948, _re_U32_4948);
        (void)hoisted__Bool_4963;
        if (hoisted__Bool_4963) {
            while (1) {
                Bool _wcond_Bool_4949 = U32_lt(_rc_U32_4948, _re_U32_4948);
                (void)_wcond_Bool_4949;
                if (_wcond_Bool_4949) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4948);
                U32_inc(&_rc_U32_4948);
                U32 hoisted__U32_4950 = 136;
                (void)hoisted__U32_4950;
                U32 hoisted__U32_4951 = U32_mul(i, hoisted__U32_4950);
                (void)hoisted__U32_4951;
                Type *hoisted__Type_4952 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4952;
                U64 hoisted__U64_4953 = (U64)(hoisted__U32_4951);
                (void)hoisted__U64_4953;
                Type_delete(hoisted__Type_4952, 1);
                Expr *hoisted__Expr_4954 = ptr_add(self->data, hoisted__U64_4953);
                (void)hoisted__Expr_4954;
                (void)hoisted__Expr_4954;
                Bool hoisted__Bool_4955 = 0;
                (void)hoisted__Bool_4955;
                Expr_delete(hoisted__Expr_4954, hoisted__Bool_4955);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4956 = U32_gt(_rc_U32_4948, _re_U32_4948);
                (void)_wcond_Bool_4956;
                if (_wcond_Bool_4956) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4948);
                U32_dec(&_rc_U32_4948);
                U32 hoisted__U32_4957 = 136;
                (void)hoisted__U32_4957;
                U32 hoisted__U32_4958 = U32_mul(i, hoisted__U32_4957);
                (void)hoisted__U32_4958;
                Type *hoisted__Type_4959 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4959;
                U64 hoisted__U64_4960 = (U64)(hoisted__U32_4958);
                (void)hoisted__U64_4960;
                Type_delete(hoisted__Type_4959, 1);
                Expr *hoisted__Expr_4961 = ptr_add(self->data, hoisted__U64_4960);
                (void)hoisted__Expr_4961;
                (void)hoisted__Expr_4961;
                Bool hoisted__Bool_4962 = 0;
                (void)hoisted__Bool_4962;
                Expr_delete(hoisted__Expr_4961, hoisted__Bool_4962);
            }
        }
    }
    U32 hoisted__U32_4964 = 0;
    (void)hoisted__U32_4964;
    self->count = hoisted__U32_4964;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5251 = 136;
    (void)hoisted__U32_5251;
    U32 hoisted__U32_5252 = U32_mul(self->cap, hoisted__U32_5251);
    (void)hoisted__U32_5252;
    Type *hoisted__Type_5253 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5253;
    U64 hoisted__U64_5254 = (U64)(hoisted__U32_5252);
    (void)hoisted__U64_5254;
    Type_delete(hoisted__Type_5253, 1);
    void * new_data = malloc(hoisted__U64_5254);
    {
        U32 _re_U32_5215 = self->count;
        (void)_re_U32_5215;
        U32 _rc_U32_5215 = 0;
        (void)_rc_U32_5215;
        Bool hoisted__Bool_5250 = U32_lte(_rc_U32_5215, _re_U32_5215);
        (void)hoisted__Bool_5250;
        if (hoisted__Bool_5250) {
            while (1) {
                Bool _wcond_Bool_5216 = U32_lt(_rc_U32_5215, _re_U32_5215);
                (void)_wcond_Bool_5216;
                if (_wcond_Bool_5216) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5215);
                U32_inc(&_rc_U32_5215);
                U32 hoisted__U32_5217 = 136;
                (void)hoisted__U32_5217;
                U32 hoisted__U32_5218 = U32_mul(i, hoisted__U32_5217);
                (void)hoisted__U32_5218;
                Type *hoisted__Type_5219 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5219;
                U64 hoisted__U64_5220 = (U64)(hoisted__U32_5218);
                (void)hoisted__U64_5220;
                Type_delete(hoisted__Type_5219, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5220);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5221 = 136;
                (void)hoisted__U32_5221;
                U32 hoisted__U32_5222 = U32_mul(i, hoisted__U32_5221);
                (void)hoisted__U32_5222;
                Type *hoisted__Type_5223 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5223;
                U64 hoisted__U64_5224 = (U64)(hoisted__U32_5222);
                (void)hoisted__U64_5224;
                Type_delete(hoisted__Type_5223, 1);
                U32 hoisted__U32_5225 = 136;
                (void)hoisted__U32_5225;
                Type *hoisted__Type_5226 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5226;
                void *hoisted__v_5227 = ptr_add(new_data, hoisted__U64_5224);
                (void)hoisted__v_5227;
                (void)hoisted__v_5227;
                U64 hoisted__U64_5228 = (U64)(hoisted__U32_5225);
                (void)hoisted__U64_5228;
                Type_delete(hoisted__Type_5226, 1);
                memcpy(hoisted__v_5227, cloned, hoisted__U64_5228);
                U32 hoisted__U32_5229 = 136;
                (void)hoisted__U32_5229;
                Type *hoisted__Type_5230 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5230;
                I32 hoisted__I32_5231 = 0;
                (void)hoisted__I32_5231;
                U64 hoisted__U64_5232 = (U64)(hoisted__U32_5229);
                (void)hoisted__U64_5232;
                Type_delete(hoisted__Type_5230, 1);
                memset(cloned, hoisted__I32_5231, hoisted__U64_5232);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5233 = U32_gt(_rc_U32_5215, _re_U32_5215);
                (void)_wcond_Bool_5233;
                if (_wcond_Bool_5233) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5215);
                U32_dec(&_rc_U32_5215);
                U32 hoisted__U32_5234 = 136;
                (void)hoisted__U32_5234;
                U32 hoisted__U32_5235 = U32_mul(i, hoisted__U32_5234);
                (void)hoisted__U32_5235;
                Type *hoisted__Type_5236 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5236;
                U64 hoisted__U64_5237 = (U64)(hoisted__U32_5235);
                (void)hoisted__U64_5237;
                Type_delete(hoisted__Type_5236, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5237);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5238 = 136;
                (void)hoisted__U32_5238;
                U32 hoisted__U32_5239 = U32_mul(i, hoisted__U32_5238);
                (void)hoisted__U32_5239;
                Type *hoisted__Type_5240 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5240;
                U64 hoisted__U64_5241 = (U64)(hoisted__U32_5239);
                (void)hoisted__U64_5241;
                Type_delete(hoisted__Type_5240, 1);
                U32 hoisted__U32_5242 = 136;
                (void)hoisted__U32_5242;
                Type *hoisted__Type_5243 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5243;
                void *hoisted__v_5244 = ptr_add(new_data, hoisted__U64_5241);
                (void)hoisted__v_5244;
                (void)hoisted__v_5244;
                U64 hoisted__U64_5245 = (U64)(hoisted__U32_5242);
                (void)hoisted__U64_5245;
                Type_delete(hoisted__Type_5243, 1);
                memcpy(hoisted__v_5244, cloned, hoisted__U64_5245);
                U32 hoisted__U32_5246 = 136;
                (void)hoisted__U32_5246;
                Type *hoisted__Type_5247 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5247;
                I32 hoisted__I32_5248 = 0;
                (void)hoisted__I32_5248;
                U64 hoisted__U64_5249 = (U64)(hoisted__U32_5246);
                (void)hoisted__U64_5249;
                Type_delete(hoisted__Type_5247, 1);
                memset(cloned, hoisted__I32_5248, hoisted__U64_5249);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5255 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5255->data = new_data;
    hoisted__Vec__Expr_5255->count = self->count;
    hoisted__Vec__Expr_5255->cap = self->cap;
    (void)hoisted__Vec__Expr_5255;
    return hoisted__Vec__Expr_5255;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5256 = 16;
    (void)hoisted__U32_5256;
    return hoisted__U32_5256;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5257 = 8;
    (void)hoisted__U32_5257;
    Type *hoisted__Type_5258 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5258;
    U64 hoisted__U64_5259 = (U64)(hoisted__U32_5257);
    (void)hoisted__U64_5259;
    Type_delete(hoisted__Type_5258, 1);
    void * hoisted__v_5260 = malloc(hoisted__U64_5259);
    (void)hoisted__v_5260;
    U32 hoisted__U32_5261 = 0;
    (void)hoisted__U32_5261;
    I64 hoisted__I64_5262 = 1;
    (void)hoisted__I64_5262;
    Vec__I64 *hoisted__Vec__I64_5263 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5263->data = hoisted__v_5260;
    hoisted__Vec__I64_5263->count = hoisted__U32_5261;
    hoisted__Vec__I64_5263->cap = hoisted__I64_5262;
    (void)hoisted__Vec__I64_5263;
    return hoisted__Vec__I64_5263;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5264 = self->count;
        (void)_re_U32_5264;
        U32 _rc_U32_5264 = 0;
        (void)_rc_U32_5264;
        Bool hoisted__Bool_5279 = U32_lte(_rc_U32_5264, _re_U32_5264);
        (void)hoisted__Bool_5279;
        if (hoisted__Bool_5279) {
            while (1) {
                Bool _wcond_Bool_5265 = U32_lt(_rc_U32_5264, _re_U32_5264);
                (void)_wcond_Bool_5265;
                if (_wcond_Bool_5265) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5264);
                U32_inc(&_rc_U32_5264);
                U32 hoisted__U32_5266 = 8;
                (void)hoisted__U32_5266;
                U32 hoisted__U32_5267 = U32_mul(i, hoisted__U32_5266);
                (void)hoisted__U32_5267;
                Type *hoisted__Type_5268 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5268;
                U64 hoisted__U64_5269 = (U64)(hoisted__U32_5267);
                (void)hoisted__U64_5269;
                Type_delete(hoisted__Type_5268, 1);
                I64 *hoisted__I64_5270 = ptr_add(self->data, hoisted__U64_5269);
                (void)hoisted__I64_5270;
                (void)hoisted__I64_5270;
                Bool hoisted__Bool_5271 = 0;
                (void)hoisted__Bool_5271;
                I64_delete(hoisted__I64_5270, hoisted__Bool_5271);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5272 = U32_gt(_rc_U32_5264, _re_U32_5264);
                (void)_wcond_Bool_5272;
                if (_wcond_Bool_5272) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5264);
                U32_dec(&_rc_U32_5264);
                U32 hoisted__U32_5273 = 8;
                (void)hoisted__U32_5273;
                U32 hoisted__U32_5274 = U32_mul(i, hoisted__U32_5273);
                (void)hoisted__U32_5274;
                Type *hoisted__Type_5275 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5275;
                U64 hoisted__U64_5276 = (U64)(hoisted__U32_5274);
                (void)hoisted__U64_5276;
                Type_delete(hoisted__Type_5275, 1);
                I64 *hoisted__I64_5277 = ptr_add(self->data, hoisted__U64_5276);
                (void)hoisted__I64_5277;
                (void)hoisted__I64_5277;
                Bool hoisted__Bool_5278 = 0;
                (void)hoisted__Bool_5278;
                I64_delete(hoisted__I64_5277, hoisted__Bool_5278);
            }
        }
    }
    U32 hoisted__U32_5280 = 0;
    (void)hoisted__U32_5280;
    self->count = hoisted__U32_5280;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5567 = 8;
    (void)hoisted__U32_5567;
    U32 hoisted__U32_5568 = U32_mul(self->cap, hoisted__U32_5567);
    (void)hoisted__U32_5568;
    Type *hoisted__Type_5569 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5569;
    U64 hoisted__U64_5570 = (U64)(hoisted__U32_5568);
    (void)hoisted__U64_5570;
    Type_delete(hoisted__Type_5569, 1);
    void * new_data = malloc(hoisted__U64_5570);
    {
        U32 _re_U32_5531 = self->count;
        (void)_re_U32_5531;
        U32 _rc_U32_5531 = 0;
        (void)_rc_U32_5531;
        Bool hoisted__Bool_5566 = U32_lte(_rc_U32_5531, _re_U32_5531);
        (void)hoisted__Bool_5566;
        if (hoisted__Bool_5566) {
            while (1) {
                Bool _wcond_Bool_5532 = U32_lt(_rc_U32_5531, _re_U32_5531);
                (void)_wcond_Bool_5532;
                if (_wcond_Bool_5532) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5531);
                U32_inc(&_rc_U32_5531);
                U32 hoisted__U32_5533 = 8;
                (void)hoisted__U32_5533;
                U32 hoisted__U32_5534 = U32_mul(i, hoisted__U32_5533);
                (void)hoisted__U32_5534;
                Type *hoisted__Type_5535 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5535;
                U64 hoisted__U64_5536 = (U64)(hoisted__U32_5534);
                (void)hoisted__U64_5536;
                Type_delete(hoisted__Type_5535, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5536);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5537 = 8;
                (void)hoisted__U32_5537;
                U32 hoisted__U32_5538 = U32_mul(i, hoisted__U32_5537);
                (void)hoisted__U32_5538;
                Type *hoisted__Type_5539 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5539;
                U64 hoisted__U64_5540 = (U64)(hoisted__U32_5538);
                (void)hoisted__U64_5540;
                Type_delete(hoisted__Type_5539, 1);
                U32 hoisted__U32_5541 = 8;
                (void)hoisted__U32_5541;
                Type *hoisted__Type_5542 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5542;
                void *hoisted__v_5543 = ptr_add(new_data, hoisted__U64_5540);
                (void)hoisted__v_5543;
                (void)hoisted__v_5543;
                U64 hoisted__U64_5544 = (U64)(hoisted__U32_5541);
                (void)hoisted__U64_5544;
                Type_delete(hoisted__Type_5542, 1);
                memcpy(hoisted__v_5543, &cloned, hoisted__U64_5544);
                U32 hoisted__U32_5545 = 8;
                (void)hoisted__U32_5545;
                Type *hoisted__Type_5546 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5546;
                I32 hoisted__I32_5547 = 0;
                (void)hoisted__I32_5547;
                U64 hoisted__U64_5548 = (U64)(hoisted__U32_5545);
                (void)hoisted__U64_5548;
                Type_delete(hoisted__Type_5546, 1);
                memset(&cloned, hoisted__I32_5547, hoisted__U64_5548);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5549 = U32_gt(_rc_U32_5531, _re_U32_5531);
                (void)_wcond_Bool_5549;
                if (_wcond_Bool_5549) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5531);
                U32_dec(&_rc_U32_5531);
                U32 hoisted__U32_5550 = 8;
                (void)hoisted__U32_5550;
                U32 hoisted__U32_5551 = U32_mul(i, hoisted__U32_5550);
                (void)hoisted__U32_5551;
                Type *hoisted__Type_5552 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5552;
                U64 hoisted__U64_5553 = (U64)(hoisted__U32_5551);
                (void)hoisted__U64_5553;
                Type_delete(hoisted__Type_5552, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5553);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5554 = 8;
                (void)hoisted__U32_5554;
                U32 hoisted__U32_5555 = U32_mul(i, hoisted__U32_5554);
                (void)hoisted__U32_5555;
                Type *hoisted__Type_5556 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5556;
                U64 hoisted__U64_5557 = (U64)(hoisted__U32_5555);
                (void)hoisted__U64_5557;
                Type_delete(hoisted__Type_5556, 1);
                U32 hoisted__U32_5558 = 8;
                (void)hoisted__U32_5558;
                Type *hoisted__Type_5559 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5559;
                void *hoisted__v_5560 = ptr_add(new_data, hoisted__U64_5557);
                (void)hoisted__v_5560;
                (void)hoisted__v_5560;
                U64 hoisted__U64_5561 = (U64)(hoisted__U32_5558);
                (void)hoisted__U64_5561;
                Type_delete(hoisted__Type_5559, 1);
                memcpy(hoisted__v_5560, &cloned, hoisted__U64_5561);
                U32 hoisted__U32_5562 = 8;
                (void)hoisted__U32_5562;
                Type *hoisted__Type_5563 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5563;
                I32 hoisted__I32_5564 = 0;
                (void)hoisted__I32_5564;
                U64 hoisted__U64_5565 = (U64)(hoisted__U32_5562);
                (void)hoisted__U64_5565;
                Type_delete(hoisted__Type_5563, 1);
                memset(&cloned, hoisted__I32_5564, hoisted__U64_5565);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5571 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5571->data = new_data;
    hoisted__Vec__I64_5571->count = self->count;
    hoisted__Vec__I64_5571->cap = self->cap;
    (void)hoisted__Vec__I64_5571;
    return hoisted__Vec__I64_5571;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5572 = 16;
    (void)hoisted__U32_5572;
    return hoisted__U32_5572;
}

void panic(Str * loc_str, Array__Str * parts) {
    U32 hoisted__U32_6651 = 3;
    (void)hoisted__U32_6651;
    Array__Str *_va_Array_187 = Array__Str_new(hoisted__U32_6651);
    (void)_va_Array_187;
    U32 hoisted__U32_6652 = 0;
    (void)hoisted__U32_6652;
    Str *hoisted__Str_6653 = Str_clone(loc_str);
    (void)hoisted__Str_6653;
    Array__Str_set(_va_Array_187, hoisted__U32_6652, hoisted__Str_6653);
    U32 hoisted__U32_6654 = 1;
    (void)hoisted__U32_6654;
    Str hoisted__Str_6655 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6655;
    Array__Str_set(_va_Array_187, hoisted__U32_6654, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6655; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
    Array__Str *hoisted__Array__Str_6656 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6656;
    U32 hoisted__U32_6657 = 2;
    (void)hoisted__U32_6657;
    Str *hoisted__Str_6658 = format(hoisted__Array__Str_6656);
    (void)hoisted__Str_6658;
    Array__Str_set(_va_Array_187, hoisted__U32_6657, hoisted__Str_6658);
    Array__Str_delete(parts, 1);
    println(_va_Array_187);
    I64 hoisted__I64_6659 = 1;
    (void)hoisted__I64_6659;
    exit(hoisted__I64_6659);
}

void UNREACHABLE(Str * loc_str) {
    U32 hoisted__U32_6666 = 1;
    (void)hoisted__U32_6666;
    Array__Str *_va_Array_189 = Array__Str_new(hoisted__U32_6666);
    (void)_va_Array_189;
    U32 hoisted__U32_6667 = 0;
    (void)hoisted__U32_6667;
    Str hoisted__Str_6668 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6668;
    Array__Str_set(_va_Array_189, hoisted__U32_6667, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6668; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
    panic(loc_str, _va_Array_189);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_6672 = not(cond);
    (void)hoisted__Bool_6672;
    if (hoisted__Bool_6672) {
        U32 hoisted__U32_6669 = 1;
        (void)hoisted__U32_6669;
        Array__Str *_va_Array_190 = Array__Str_new(hoisted__U32_6669);
        (void)_va_Array_190;
        U32 hoisted__U32_6670 = 0;
        (void)hoisted__U32_6670;
        Str hoisted__Str_6671 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6671;
        Array__Str_set(_va_Array_190, hoisted__U32_6670, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6671; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        panic(loc_str, _va_Array_190);
    }
    Bool hoisted__Bool_6673 = 1;
    (void)hoisted__Bool_6673;
    return hoisted__Bool_6673;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_6692 = I64_neq(a, b);
    (void)hoisted__Bool_6692;
    if (hoisted__Bool_6692) {
        U32 hoisted__U32_6681 = 5;
        (void)hoisted__U32_6681;
        Array__Str *_va_Array_192 = Array__Str_new(hoisted__U32_6681);
        (void)_va_Array_192;
        U32 hoisted__U32_6682 = 0;
        (void)hoisted__U32_6682;
        Str hoisted__Str_6683 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6683;
        Array__Str_set(_va_Array_192, hoisted__U32_6682, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6683; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_6684 = 1;
        (void)hoisted__U32_6684;
        Str *hoisted__Str_6685 = I64_to_str(a);
        (void)hoisted__Str_6685;
        Array__Str_set(_va_Array_192, hoisted__U32_6684, hoisted__Str_6685);
        U32 hoisted__U32_6686 = 2;
        (void)hoisted__U32_6686;
        Str hoisted__Str_6687 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6687;
        Array__Str_set(_va_Array_192, hoisted__U32_6686, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6687; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_6688 = 3;
        (void)hoisted__U32_6688;
        Str *hoisted__Str_6689 = I64_to_str(b);
        (void)hoisted__Str_6689;
        Array__Str_set(_va_Array_192, hoisted__U32_6688, hoisted__Str_6689);
        U32 hoisted__U32_6690 = 4;
        (void)hoisted__U32_6690;
        Str hoisted__Str_6691 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6691;
        Array__Str_set(_va_Array_192, hoisted__U32_6690, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6691; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        panic(loc_str, _va_Array_192);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_6704 = Str_eq(a, b);
    (void)hoisted__Bool_6704;
    Bool hoisted__Bool_6705 = not(hoisted__Bool_6704);
    (void)hoisted__Bool_6705;
    if (hoisted__Bool_6705) {
        U32 hoisted__U32_6693 = 5;
        (void)hoisted__U32_6693;
        Array__Str *_va_Array_193 = Array__Str_new(hoisted__U32_6693);
        (void)_va_Array_193;
        U32 hoisted__U32_6694 = 0;
        (void)hoisted__U32_6694;
        Str hoisted__Str_6695 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6695;
        Array__Str_set(_va_Array_193, hoisted__U32_6694, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6695; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_6696 = 1;
        (void)hoisted__U32_6696;
        Str *hoisted__Str_6697 = Str_clone(a);
        (void)hoisted__Str_6697;
        Array__Str_set(_va_Array_193, hoisted__U32_6696, hoisted__Str_6697);
        U32 hoisted__U32_6698 = 2;
        (void)hoisted__U32_6698;
        Str hoisted__Str_6699 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6699;
        Array__Str_set(_va_Array_193, hoisted__U32_6698, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6699; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_6700 = 3;
        (void)hoisted__U32_6700;
        Str *hoisted__Str_6701 = Str_clone(b);
        (void)hoisted__Str_6701;
        Array__Str_set(_va_Array_193, hoisted__U32_6700, hoisted__Str_6701);
        U32 hoisted__U32_6702 = 4;
        (void)hoisted__U32_6702;
        Str hoisted__Str_6703 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6703;
        Array__Str_set(_va_Array_193, hoisted__U32_6702, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6703; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        panic(loc_str, _va_Array_193);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6706 = parts;
        (void)_fc_Array__Str_6706;
        (void)_fc_Array__Str_6706;
        U32 _fi_USize_6706 = 0;
        (void)_fi_USize_6706;
        I64 _forin_err_kind_6706 = 0;
        (void)_forin_err_kind_6706;
        OutOfBounds *_forin_OutOfBounds_6706 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_6706->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_6706;
        while (1) {
            U32 hoisted__U32_6712 = Array__Str_len(_fc_Array__Str_6706);
            (void)hoisted__U32_6712;
            Bool _wcond_Bool_6707 = U32_lt(_fi_USize_6706, hoisted__U32_6712);
            (void)_wcond_Bool_6707;
            if (_wcond_Bool_6707) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_6706, &_fi_USize_6706, &_forin_err_kind_6706, _forin_OutOfBounds_6706);
            I64 hoisted__I64_6713 = 0;
            (void)hoisted__I64_6713;
            Bool hoisted__Bool_6714 = I64_eq(_forin_err_kind_6706, hoisted__I64_6713);
            (void)hoisted__Bool_6714;
            Bool hoisted__Bool_6715 = not(hoisted__Bool_6714);
            (void)hoisted__Bool_6715;
            if (hoisted__Bool_6715) {
                U32 hoisted__U32_6708 = 1;
                (void)hoisted__U32_6708;
                Array__Str *_va_Array_194 = Array__Str_new(hoisted__U32_6708);
                (void)_va_Array_194;
                U32 hoisted__U32_6709 = 0;
                (void)hoisted__U32_6709;
                Str hoisted__Str_6710 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6710;
                Array__Str_set(_va_Array_194, hoisted__U32_6709, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6710; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
                Str hoisted__Str_6711 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6711;
                panic(&hoisted__Str_6711, _va_Array_194);
                Str_delete(&hoisted__Str_6711, (Bool){0});
            }
            U32 hoisted__U32_6716 = 1;
            (void)hoisted__U32_6716;
            U32 hoisted__U32_6717 = U32_add(_fi_USize_6706, hoisted__U32_6716);
            (void)hoisted__U32_6717;
            _fi_USize_6706 = hoisted__U32_6717;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_6706, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_6755 = ptr_eq(p, NULL);
    (void)hoisted__Bool_6755;
    return hoisted__Bool_6755;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6764 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6764;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6764;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6765 = 0;
    (void)hoisted__U32_6765;
    U64 hoisted__U64_6766 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6765); });
    (void)hoisted__U64_6766;
    return hoisted__U64_6766;
}

U32 Range_size(void) {
    U32 hoisted__U32_6790 = 16;
    (void)hoisted__U32_6790;
    return hoisted__U32_6790;
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_6896 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6896;
    I64 hoisted__I64_6897 = 3;
    (void)hoisted__I64_6897;
    assert_eq(&hoisted__Str_6896, result, hoisted__I64_6897);
    Str_delete(&hoisted__Str_6896, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_6904 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6904;
    I64 hoisted__I64_6905 = 15;
    (void)hoisted__I64_6905;
    assert_eq(&hoisted__Str_6904, result, hoisted__I64_6905);
    Str_delete(&hoisted__Str_6904, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_6912 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6912;
    I64 hoisted__I64_6913 = 26;
    (void)hoisted__I64_6913;
    assert_eq(&hoisted__Str_6912, result, hoisted__I64_6913);
    Str_delete(&hoisted__Str_6912, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_6916 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6916;
    Str hoisted__Str_6917 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6917;
    assert_eq_str(&hoisted__Str_6916, &result, &hoisted__Str_6917);
    Str_delete(&hoisted__Str_6916, (Bool){0});
    Str_delete(&hoisted__Str_6917, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7248 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7248;
    assert_eq_str(&hoisted__Str_7248, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_7248, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_7249 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7249;
    assert_eq_str(&hoisted__Str_7249, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_7249, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_7251 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7251;
    I64 hoisted__I64_7252 = 8;
    (void)hoisted__I64_7252;
    assert_eq(&hoisted__Str_7251, result, hoisted__I64_7252);
    Str_delete(&hoisted__Str_7251, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_7255 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7255;
    Bool hoisted__Bool_7256 = 1;
    (void)hoisted__Bool_7256;
    assert(&hoisted__Str_7255, hoisted__Bool_7256);
    Str_delete(&hoisted__Str_7255, (Bool){0});
    Str hoisted__Str_7259 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7259;
    Bool hoisted__Bool_7260 = 1;
    (void)hoisted__Bool_7260;
    assert(&hoisted__Str_7259, hoisted__Bool_7260);
    Str_delete(&hoisted__Str_7259, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_7265 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7265;
    Str hoisted__Str_7266 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7266;
    Str hoisted__Str_7267 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7267;
    assert_eq_str(&hoisted__Str_7265, &hoisted__Str_7266, &hoisted__Str_7267);
    Str_delete(&hoisted__Str_7265, (Bool){0});
    Str_delete(&hoisted__Str_7266, (Bool){0});
    Str_delete(&hoisted__Str_7267, (Bool){0});
    Str hoisted__Str_7270 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7270;
    Str hoisted__Str_7271 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7271;
    Str hoisted__Str_7272 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7272;
    assert_eq_str(&hoisted__Str_7270, &hoisted__Str_7271, &hoisted__Str_7272);
    Str_delete(&hoisted__Str_7270, (Bool){0});
    Str_delete(&hoisted__Str_7271, (Bool){0});
    Str_delete(&hoisted__Str_7272, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7277 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7277;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7277;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7278 = 0;
    (void)hoisted__U32_7278;
    U64 hoisted__U64_7279 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7278); });
    (void)hoisted__U64_7279;
    return hoisted__U64_7279;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_7303 = 16;
    (void)hoisted__U32_7303;
    return hoisted__U32_7303;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_7304 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7304;
    I64 hoisted__I64_7305 = 42;
    (void)hoisted__I64_7305;
    assert_eq(&hoisted__Str_7304, v.x, hoisted__I64_7305);
    Str_delete(&hoisted__Str_7304, (Bool){0});
    Str hoisted__Str_7306 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7306;
    I64 hoisted__I64_7307 = 99;
    (void)hoisted__I64_7307;
    assert_eq(&hoisted__Str_7306, v.y, hoisted__I64_7307);
    Str_delete(&hoisted__Str_7306, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_7310 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7310;
    I64 hoisted__I64_7311 = 10;
    (void)hoisted__I64_7311;
    assert_eq(&hoisted__Str_7310, p.x, hoisted__I64_7311);
    Str_delete(&hoisted__Str_7310, (Bool){0});
    Str hoisted__Str_7312 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7312;
    I64 hoisted__I64_7313 = 20;
    (void)hoisted__I64_7313;
    assert_eq(&hoisted__Str_7312, p.y, hoisted__I64_7313);
    Str_delete(&hoisted__Str_7312, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7319 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7319;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7319;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7320 = 0;
    (void)hoisted__U32_7320;
    U64 hoisted__U64_7321 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7320); });
    (void)hoisted__U64_7321;
    return hoisted__U64_7321;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_7345 = 32;
    (void)hoisted__U32_7345;
    return hoisted__U32_7345;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_7346 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7346;
    I64 hoisted__I64_7347 = 5;
    (void)hoisted__I64_7347;
    assert_eq(&hoisted__Str_7346, r.top_left.x, hoisted__I64_7347);
    Str_delete(&hoisted__Str_7346, (Bool){0});
    Str hoisted__Str_7348 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7348;
    I64 hoisted__I64_7349 = 10;
    (void)hoisted__I64_7349;
    assert_eq(&hoisted__Str_7348, r.top_left.y, hoisted__I64_7349);
    Str_delete(&hoisted__Str_7348, (Bool){0});
    Str hoisted__Str_7350 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7350;
    I64 hoisted__I64_7351 = 100;
    (void)hoisted__I64_7351;
    assert_eq(&hoisted__Str_7350, r.bottom_right.x, hoisted__I64_7351);
    Str_delete(&hoisted__Str_7350, (Bool){0});
    Str hoisted__Str_7352 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7352;
    I64 hoisted__I64_7353 = 200;
    (void)hoisted__I64_7353;
    assert_eq(&hoisted__Str_7352, r.bottom_right.y, hoisted__I64_7353);
    Str_delete(&hoisted__Str_7352, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7355 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7355;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7355;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7356 = 0;
    (void)hoisted__U32_7356;
    U64 hoisted__U64_7357 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7356); });
    (void)hoisted__U64_7357;
    return hoisted__U64_7357;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_7390 = 12;
    (void)hoisted__U32_7390;
    return hoisted__U32_7390;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_7394 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7394;
    Str *hoisted__Str_7395 = F32_to_str(v.x);
    (void)hoisted__Str_7395;
    Str hoisted__Str_7396 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7396;
    assert_eq_str(&hoisted__Str_7394, hoisted__Str_7395, &hoisted__Str_7396);
    Str_delete(&hoisted__Str_7394, (Bool){0});
    Str_delete(hoisted__Str_7395, 1);
    Str_delete(&hoisted__Str_7396, (Bool){0});
    Str hoisted__Str_7397 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7397;
    Str *hoisted__Str_7398 = F32_to_str(v.y);
    (void)hoisted__Str_7398;
    Str hoisted__Str_7399 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7399;
    assert_eq_str(&hoisted__Str_7397, hoisted__Str_7398, &hoisted__Str_7399);
    Str_delete(&hoisted__Str_7397, (Bool){0});
    Str_delete(hoisted__Str_7398, 1);
    Str_delete(&hoisted__Str_7399, (Bool){0});
    Str hoisted__Str_7400 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7400;
    Str *hoisted__Str_7401 = F32_to_str(v.z);
    (void)hoisted__Str_7401;
    Str hoisted__Str_7402 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7402;
    assert_eq_str(&hoisted__Str_7400, hoisted__Str_7401, &hoisted__Str_7402);
    Str_delete(&hoisted__Str_7400, (Bool){0});
    Str_delete(hoisted__Str_7401, 1);
    Str_delete(&hoisted__Str_7402, (Bool){0});
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
    Bool hoisted__Bool_7407 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7407;
    if (hoisted__Bool_7407) {
        Bool hoisted__Bool_7404 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_7404;
        { Bool _ret_val = hoisted__Bool_7404;
                return _ret_val; }
    }
    Bool hoisted__Bool_7408 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7408;
    if (hoisted__Bool_7408) {
        Bool hoisted__Bool_7405 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_7405;
        { Bool _ret_val = hoisted__Bool_7405;
                return _ret_val; }
    }
    Bool hoisted__Bool_7409 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7409;
    if (hoisted__Bool_7409) {
        Bool hoisted__Bool_7406 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_7406;
        { Bool _ret_val = hoisted__Bool_7406;
                return _ret_val; }
    }
    Bool hoisted__Bool_7410 = 0;
    (void)hoisted__Bool_7410;
    return hoisted__Bool_7410;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7418 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7418;
    if (hoisted__Bool_7418) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_7419 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7419;
    if (hoisted__Bool_7419) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_7420 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7420;
    if (hoisted__Bool_7420) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_7421 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7421;
    UNREACHABLE(&hoisted__Str_7421);
    Str_delete(&hoisted__Str_7421, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_7422 = 4;
    (void)hoisted__U32_7422;
    return hoisted__U32_7422;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_7423 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7423;
    Bool hoisted__Bool_7424 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7424;
    assert(&hoisted__Str_7423, hoisted__Bool_7424);
    Str_delete(&hoisted__Str_7423, (Bool){0});
    Bool hoisted__Bool_7425 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7425;
    Str hoisted__Str_7426 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7426;
    Bool hoisted__Bool_7427 = not(hoisted__Bool_7425);
    (void)hoisted__Bool_7427;
    assert(&hoisted__Str_7426, hoisted__Bool_7427);
    Str_delete(&hoisted__Str_7426, (Bool){0});
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
    Bool hoisted__Bool_7428 = is(self, other);
    (void)hoisted__Bool_7428;
    return hoisted__Bool_7428;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7446 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7446;
    if (hoisted__Bool_7446) {
        I64 *hoisted__I64_7442 = get_payload(self);
        (void)hoisted__I64_7442;
        (void)hoisted__I64_7442;
        Bool hoisted__Bool_7443 = 0;
        (void)hoisted__Bool_7443;
        I64_delete(hoisted__I64_7442, hoisted__Bool_7443);
    }
    Bool hoisted__Bool_7447 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7447;
    if (hoisted__Bool_7447) {
        Str *hoisted__Str_7444 = get_payload(self);
        (void)hoisted__Str_7444;
        (void)hoisted__Str_7444;
        Bool hoisted__Bool_7445 = 0;
        (void)hoisted__Bool_7445;
        Str_delete(hoisted__Str_7444, hoisted__Bool_7445);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_7472 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7472;
    if (hoisted__Bool_7472) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7469 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7469;
        { Token * _ret_val = hoisted__Token_7469;
                return _ret_val; }
    }
    Bool hoisted__Bool_7473 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7473;
    if (hoisted__Bool_7473) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7470 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7470;
        Token *hoisted__Token_7471 = Token_Name(hoisted__Str_7470);
        (void)hoisted__Token_7471;
        { Token * _ret_val = hoisted__Token_7471;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_7474 = 24;
    (void)hoisted__U32_7474;
    return hoisted__U32_7474;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_7476 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7476;
    Bool hoisted__Bool_7477 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7477;
    assert(&hoisted__Str_7476, hoisted__Bool_7477);
    Str_delete(&hoisted__Str_7476, (Bool){0});
    Bool hoisted__Bool_7478 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7478;
    Str hoisted__Str_7479 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7479;
    Bool hoisted__Bool_7480 = not(hoisted__Bool_7478);
    (void)hoisted__Bool_7480;
    assert(&hoisted__Str_7479, hoisted__Bool_7480);
    Str_delete(&hoisted__Str_7479, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_7481 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7481;
    Bool hoisted__Bool_7482 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7482;
    assert(&hoisted__Str_7481, hoisted__Bool_7482);
    Str_delete(&hoisted__Str_7481, (Bool){0});
    Bool hoisted__Bool_7483 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7483;
    Str hoisted__Str_7484 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7484;
    Bool hoisted__Bool_7485 = not(hoisted__Bool_7483);
    (void)hoisted__Bool_7485;
    assert(&hoisted__Str_7484, hoisted__Bool_7485);
    Str_delete(&hoisted__Str_7484, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_7488 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7488;
    Bool hoisted__Bool_7489 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7489;
    assert(&hoisted__Str_7488, hoisted__Bool_7489);
    Str_delete(&hoisted__Str_7488, (Bool){0});
    Bool hoisted__Bool_7490 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7490;
    Str hoisted__Str_7491 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7491;
    Bool hoisted__Bool_7492 = not(hoisted__Bool_7490);
    (void)hoisted__Bool_7492;
    assert(&hoisted__Str_7491, hoisted__Bool_7492);
    Str_delete(&hoisted__Str_7491, (Bool){0});
    Token_delete(t, 1);
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
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2) {
    (void)til_env;
    Array__Str_set(_a0, *(U32 *)_a1, _a2);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Str_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Str_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Str_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Str_eq_dyn__til_closure;
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
        return 26LL;
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
    fprintf(stderr, "16/16 tests passed\n");
    return 0;
}
