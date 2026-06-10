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
#define TIL_CAP_STATIC ((USize)-3)
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

U32 CAP_LIT;
U32 CAP_VIEW;
U32 CAP_STATIC;
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
                Array__Str_set(_va_Array_16, hoisted__U32_628, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_629; _oa; }));
                Str hoisted__Str_630 = (Str){.c_str = (void *)"./src/core/str.til:19:9", .count = 23ULL, .cap = TIL_CAP_LIT};
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
                Array__Str_set(_va_Array_17, hoisted__U32_642, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_643; _oa; }));
                Str hoisted__Str_644 = (Str){.c_str = (void *)"./src/core/str.til:23:9", .count = 23ULL, .cap = TIL_CAP_LIT};
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
        Array__Str_set(_va_Array_18, hoisted__U32_652, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_653; _oa; }));
        Str hoisted__Str_654 = (Str){.c_str = (void *)"./src/core/str.til:43:19", .count = 24ULL, .cap = TIL_CAP_LIT};
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
        Array__Str_set(_va_Array_19, hoisted__U32_678, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_679; _oa; }));
        Str hoisted__Str_680 = (Str){.c_str = (void *)"./src/core/str.til:92:19", .count = 24ULL, .cap = TIL_CAP_LIT};
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
        Array__Str_set(_va_Array_20, hoisted__U32_682, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_683; _oa; }));
        Str hoisted__Str_684 = (Str){.c_str = (void *)"./src/core/str.til:96:19", .count = 24ULL, .cap = TIL_CAP_LIT};
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
    Bool hoisted__Bool_697 = U32_lt(self->cap, CAP_STATIC);
    (void)hoisted__Bool_697;
    if (hoisted__Bool_697) {
        free(self->c_str);
    }
    Bool hoisted__Bool_698 = U32_neq(self->cap, CAP_STATIC);
    (void)hoisted__Bool_698;
    Bool hoisted__Bool_699 = and(call_free, hoisted__Bool_698);
    (void)hoisted__Bool_699;
    if (hoisted__Bool_699) {
        free(self);
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_906 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_906;
    return hoisted__U64_906;
}

U32 Str_size(void) {
    U32 hoisted__U32_1079 = 16;
    (void)hoisted__U32_1079;
    return hoisted__U32_1079;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1080 = Str_cmp(a, b);
    (void)hoisted__I64_1080;
    I64 hoisted__I64_1081 = 0;
    (void)hoisted__I64_1081;
    Bool hoisted__Bool_1082 = I64_eq(hoisted__I64_1080, hoisted__I64_1081);
    (void)hoisted__Bool_1082;
    return hoisted__Bool_1082;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1174 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1174->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1174;
    return hoisted__OutOfBounds_1174;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1175 = 0;
    (void)hoisted__Bool_1175;
    Str_delete(&self->msg, hoisted__Bool_1175);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1176 = 0;
    (void)hoisted__U32_1176;
    U64 hoisted__U64_1177 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1176); });
    (void)hoisted__U64_1177;
    return hoisted__U64_1177;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1178 = 16;
    (void)hoisted__U32_1178;
    return hoisted__U32_1178;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1184 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1184;
    U32 hoisted__U32_1185 = 16;
    (void)hoisted__U32_1185;
    Type *hoisted__Type_1186 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1186;
    U64 hoisted__U64_1187 = (U64)(cap);
    (void)hoisted__U64_1187;
    Type_delete(hoisted__Type_1184, 1);
    U64 hoisted__U64_1188 = (U64)(hoisted__U32_1185);
    (void)hoisted__U64_1188;
    Type_delete(hoisted__Type_1186, 1);
    void * hoisted__v_1189 = calloc(hoisted__U64_1187, hoisted__U64_1188);
    (void)hoisted__v_1189;
    Array__Str *hoisted__Array__Str_1190 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1190->data = hoisted__v_1189;
    hoisted__Array__Str_1190->cap = cap;
    (void)hoisted__Array__Str_1190;
    return hoisted__Array__Str_1190;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1212 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1212;
    if (hoisted__Bool_1212) {
        U32 hoisted__U32_1191 = 6;
        (void)hoisted__U32_1191;
        Array__Str *_va_Array_30 = Array__Str_new(hoisted__U32_1191);
        (void)_va_Array_30;
        U32 hoisted__U32_1192 = 0;
        (void)hoisted__U32_1192;
        Str hoisted__Str_1193 = (Str){.c_str = (void *)"./src/core/array.til:28:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1193;
        Array__Str_set(_va_Array_30, hoisted__U32_1192, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1193; _oa; }));
        U32 hoisted__U32_1194 = 1;
        (void)hoisted__U32_1194;
        Str hoisted__Str_1195 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1195;
        Array__Str_set(_va_Array_30, hoisted__U32_1194, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1195; _oa; }));
        U32 hoisted__U32_1196 = 2;
        (void)hoisted__U32_1196;
        Str *hoisted__Str_1197 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1197;
        Array__Str_set(_va_Array_30, hoisted__U32_1196, hoisted__Str_1197);
        U32 hoisted__U32_1198 = 3;
        (void)hoisted__U32_1198;
        Str hoisted__Str_1199 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1199;
        Array__Str_set(_va_Array_30, hoisted__U32_1198, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1199; _oa; }));
        U32 hoisted__U32_1200 = 4;
        (void)hoisted__U32_1200;
        Str *hoisted__Str_1201 = U32_to_str(self->cap);
        (void)hoisted__Str_1201;
        Array__Str_set(_va_Array_30, hoisted__U32_1200, hoisted__Str_1201);
        U32 hoisted__U32_1202 = 5;
        (void)hoisted__U32_1202;
        Str hoisted__Str_1203 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1203;
        Array__Str_set(_va_Array_30, hoisted__U32_1202, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1203; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_1204 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_30); hoisted__OutOfBounds_1204->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1204;
        U32 hoisted__U32_1205 = 16;
        (void)hoisted__U32_1205;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1204, hoisted__U32_1205);
        OutOfBounds_delete(hoisted__OutOfBounds_1204, 1);
        I64 hoisted__I64_1206 = 3;
        (void)hoisted__I64_1206;
        *_err_kind = hoisted__I64_1206;
    }
    I64 hoisted__I64_1213 = 0;
    (void)hoisted__I64_1213;
    Bool hoisted__Bool_1214 = I64_eq(DEREF(_err_kind), hoisted__I64_1213);
    (void)hoisted__Bool_1214;
    if (hoisted__Bool_1214) {
        U32 hoisted__U32_1207 = 16;
        (void)hoisted__U32_1207;
        U32 hoisted__U32_1208 = U32_mul(DEREF(i), hoisted__U32_1207);
        (void)hoisted__U32_1208;
        Type *hoisted__Type_1209 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1209;
        U64 hoisted__U64_1210 = (U64)(hoisted__U32_1208);
        (void)hoisted__U64_1210;
        Type_delete(hoisted__Type_1209, 1);
        void *hoisted__v_1211 = ptr_add(self->data, hoisted__U64_1210);
        (void)hoisted__v_1211;
        (void)hoisted__v_1211;
        { Str * _ret_val = hoisted__v_1211;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val) {
    Bool hoisted__Bool_1227 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1227;
    if (hoisted__Bool_1227) {
        U32 hoisted__U32_1215 = 5;
        (void)hoisted__U32_1215;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1215);
        (void)_va_Array_31;
        U32 hoisted__U32_1216 = 0;
        (void)hoisted__U32_1216;
        Str hoisted__Str_1217 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1217;
        Array__Str_set(_va_Array_31, hoisted__U32_1216, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1217; _oa; }));
        U32 hoisted__U32_1218 = 1;
        (void)hoisted__U32_1218;
        Str *hoisted__Str_1219 = U32_to_str(i);
        (void)hoisted__Str_1219;
        Array__Str_set(_va_Array_31, hoisted__U32_1218, hoisted__Str_1219);
        U32 hoisted__U32_1220 = 2;
        (void)hoisted__U32_1220;
        Str hoisted__Str_1221 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1221;
        Array__Str_set(_va_Array_31, hoisted__U32_1220, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1221; _oa; }));
        U32 hoisted__U32_1222 = 3;
        (void)hoisted__U32_1222;
        Str *hoisted__Str_1223 = U32_to_str(self->cap);
        (void)hoisted__Str_1223;
        Array__Str_set(_va_Array_31, hoisted__U32_1222, hoisted__Str_1223);
        U32 hoisted__U32_1224 = 4;
        (void)hoisted__U32_1224;
        Str hoisted__Str_1225 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1225;
        Array__Str_set(_va_Array_31, hoisted__U32_1224, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1225; _oa; }));
        Str hoisted__Str_1226 = (Str){.c_str = (void *)"./src/core/array.til:37:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1226;
        panic(&hoisted__Str_1226, _va_Array_31);
        Str_delete(&hoisted__Str_1226, (Bool){0});
    }
    U32 hoisted__U32_1228 = 16;
    (void)hoisted__U32_1228;
    U32 hoisted__U32_1229 = U32_mul(i, hoisted__U32_1228);
    (void)hoisted__U32_1229;
    Type *hoisted__Type_1230 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1230;
    U64 hoisted__U64_1231 = (U64)(hoisted__U32_1229);
    (void)hoisted__U64_1231;
    Type_delete(hoisted__Type_1230, 1);
    Str *hoisted__Str_1232 = ptr_add(self->data, hoisted__U64_1231);
    (void)hoisted__Str_1232;
    (void)hoisted__Str_1232;
    Bool hoisted__Bool_1233 = 0;
    (void)hoisted__Bool_1233;
    Str_delete(hoisted__Str_1232, hoisted__Bool_1233);
    U32 hoisted__U32_1234 = 16;
    (void)hoisted__U32_1234;
    U32 hoisted__U32_1235 = U32_mul(i, hoisted__U32_1234);
    (void)hoisted__U32_1235;
    Type *hoisted__Type_1236 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1236;
    U64 hoisted__U64_1237 = (U64)(hoisted__U32_1235);
    (void)hoisted__U64_1237;
    Type_delete(hoisted__Type_1236, 1);
    U32 hoisted__U32_1238 = 16;
    (void)hoisted__U32_1238;
    Type *hoisted__Type_1239 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1239;
    void *hoisted__v_1240 = ptr_add(self->data, hoisted__U64_1237);
    (void)hoisted__v_1240;
    (void)hoisted__v_1240;
    U64 hoisted__U64_1241 = (U64)(hoisted__U32_1238);
    (void)hoisted__U64_1241;
    Type_delete(hoisted__Type_1239, 1);
    memcpy(hoisted__v_1240, val, hoisted__U64_1241);
    U32 hoisted__U32_1242 = 16;
    (void)hoisted__U32_1242;
    Type *hoisted__Type_1243 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1243;
    I32 hoisted__I32_1244 = 0;
    (void)hoisted__I32_1244;
    U64 hoisted__U64_1245 = (U64)(hoisted__U32_1242);
    (void)hoisted__U64_1245;
    Type_delete(hoisted__Type_1243, 1);
    memset(val, hoisted__I32_1244, hoisted__U64_1245);
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1246 = self->cap;
        (void)_re_U32_1246;
        U32 _rc_U32_1246 = 0;
        (void)_rc_U32_1246;
        Bool hoisted__Bool_1261 = U32_lte(_rc_U32_1246, _re_U32_1246);
        (void)hoisted__Bool_1261;
        if (hoisted__Bool_1261) {
            while (1) {
                Bool _wcond_Bool_1247 = U32_lt(_rc_U32_1246, _re_U32_1246);
                (void)_wcond_Bool_1247;
                if (_wcond_Bool_1247) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1246);
                U32_inc(&_rc_U32_1246);
                U32 hoisted__U32_1248 = 16;
                (void)hoisted__U32_1248;
                U32 hoisted__U32_1249 = U32_mul(i, hoisted__U32_1248);
                (void)hoisted__U32_1249;
                Type *hoisted__Type_1250 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1250;
                U64 hoisted__U64_1251 = (U64)(hoisted__U32_1249);
                (void)hoisted__U64_1251;
                Type_delete(hoisted__Type_1250, 1);
                Str *hoisted__Str_1252 = ptr_add(self->data, hoisted__U64_1251);
                (void)hoisted__Str_1252;
                (void)hoisted__Str_1252;
                Bool hoisted__Bool_1253 = 0;
                (void)hoisted__Bool_1253;
                Str_delete(hoisted__Str_1252, hoisted__Bool_1253);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1254 = U32_gt(_rc_U32_1246, _re_U32_1246);
                (void)_wcond_Bool_1254;
                if (_wcond_Bool_1254) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1246);
                U32_dec(&_rc_U32_1246);
                U32 hoisted__U32_1255 = 16;
                (void)hoisted__U32_1255;
                U32 hoisted__U32_1256 = U32_mul(i, hoisted__U32_1255);
                (void)hoisted__U32_1256;
                Type *hoisted__Type_1257 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1257;
                U64 hoisted__U64_1258 = (U64)(hoisted__U32_1256);
                (void)hoisted__U64_1258;
                Type_delete(hoisted__Type_1257, 1);
                Str *hoisted__Str_1259 = ptr_add(self->data, hoisted__U64_1258);
                (void)hoisted__Str_1259;
                (void)hoisted__Str_1259;
                Bool hoisted__Bool_1260 = 0;
                (void)hoisted__Bool_1260;
                Str_delete(hoisted__Str_1259, hoisted__Bool_1260);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1298 = 16;
    (void)hoisted__U32_1298;
    U32 hoisted__U32_1299 = U32_mul(self->cap, hoisted__U32_1298);
    (void)hoisted__U32_1299;
    Type *hoisted__Type_1300 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1300;
    U64 hoisted__U64_1301 = (U64)(hoisted__U32_1299);
    (void)hoisted__U64_1301;
    Type_delete(hoisted__Type_1300, 1);
    void * new_data = malloc(hoisted__U64_1301);
    {
        U32 _re_U32_1262 = self->cap;
        (void)_re_U32_1262;
        U32 _rc_U32_1262 = 0;
        (void)_rc_U32_1262;
        Bool hoisted__Bool_1297 = U32_lte(_rc_U32_1262, _re_U32_1262);
        (void)hoisted__Bool_1297;
        if (hoisted__Bool_1297) {
            while (1) {
                Bool _wcond_Bool_1263 = U32_lt(_rc_U32_1262, _re_U32_1262);
                (void)_wcond_Bool_1263;
                if (_wcond_Bool_1263) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1262);
                U32_inc(&_rc_U32_1262);
                U32 hoisted__U32_1264 = 16;
                (void)hoisted__U32_1264;
                U32 hoisted__U32_1265 = U32_mul(i, hoisted__U32_1264);
                (void)hoisted__U32_1265;
                Type *hoisted__Type_1266 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1266;
                U64 hoisted__U64_1267 = (U64)(hoisted__U32_1265);
                (void)hoisted__U64_1267;
                Type_delete(hoisted__Type_1266, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1267);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1268 = 16;
                (void)hoisted__U32_1268;
                U32 hoisted__U32_1269 = U32_mul(i, hoisted__U32_1268);
                (void)hoisted__U32_1269;
                Type *hoisted__Type_1270 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1270;
                U64 hoisted__U64_1271 = (U64)(hoisted__U32_1269);
                (void)hoisted__U64_1271;
                Type_delete(hoisted__Type_1270, 1);
                U32 hoisted__U32_1272 = 16;
                (void)hoisted__U32_1272;
                Type *hoisted__Type_1273 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1273;
                void *hoisted__v_1274 = ptr_add(new_data, hoisted__U64_1271);
                (void)hoisted__v_1274;
                (void)hoisted__v_1274;
                U64 hoisted__U64_1275 = (U64)(hoisted__U32_1272);
                (void)hoisted__U64_1275;
                Type_delete(hoisted__Type_1273, 1);
                memcpy(hoisted__v_1274, cloned, hoisted__U64_1275);
                U32 hoisted__U32_1276 = 16;
                (void)hoisted__U32_1276;
                Type *hoisted__Type_1277 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1277;
                I32 hoisted__I32_1278 = 0;
                (void)hoisted__I32_1278;
                U64 hoisted__U64_1279 = (U64)(hoisted__U32_1276);
                (void)hoisted__U64_1279;
                Type_delete(hoisted__Type_1277, 1);
                memset(cloned, hoisted__I32_1278, hoisted__U64_1279);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1280 = U32_gt(_rc_U32_1262, _re_U32_1262);
                (void)_wcond_Bool_1280;
                if (_wcond_Bool_1280) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1262);
                U32_dec(&_rc_U32_1262);
                U32 hoisted__U32_1281 = 16;
                (void)hoisted__U32_1281;
                U32 hoisted__U32_1282 = U32_mul(i, hoisted__U32_1281);
                (void)hoisted__U32_1282;
                Type *hoisted__Type_1283 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1283;
                U64 hoisted__U64_1284 = (U64)(hoisted__U32_1282);
                (void)hoisted__U64_1284;
                Type_delete(hoisted__Type_1283, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1284);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1285 = 16;
                (void)hoisted__U32_1285;
                U32 hoisted__U32_1286 = U32_mul(i, hoisted__U32_1285);
                (void)hoisted__U32_1286;
                Type *hoisted__Type_1287 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1287;
                U64 hoisted__U64_1288 = (U64)(hoisted__U32_1286);
                (void)hoisted__U64_1288;
                Type_delete(hoisted__Type_1287, 1);
                U32 hoisted__U32_1289 = 16;
                (void)hoisted__U32_1289;
                Type *hoisted__Type_1290 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1290;
                void *hoisted__v_1291 = ptr_add(new_data, hoisted__U64_1288);
                (void)hoisted__v_1291;
                (void)hoisted__v_1291;
                U64 hoisted__U64_1292 = (U64)(hoisted__U32_1289);
                (void)hoisted__U64_1292;
                Type_delete(hoisted__Type_1290, 1);
                memcpy(hoisted__v_1291, cloned, hoisted__U64_1292);
                U32 hoisted__U32_1293 = 16;
                (void)hoisted__U32_1293;
                Type *hoisted__Type_1294 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1294;
                I32 hoisted__I32_1295 = 0;
                (void)hoisted__I32_1295;
                U64 hoisted__U64_1296 = (U64)(hoisted__U32_1293);
                (void)hoisted__U64_1296;
                Type_delete(hoisted__Type_1294, 1);
                memset(cloned, hoisted__I32_1295, hoisted__U64_1296);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1302 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1302->data = new_data;
    hoisted__Array__Str_1302->cap = self->cap;
    (void)hoisted__Array__Str_1302;
    return hoisted__Array__Str_1302;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1303 = 16;
    (void)hoisted__U32_1303;
    return hoisted__U32_1303;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1304 = 16;
    (void)hoisted__U32_1304;
    Type *hoisted__Type_1305 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1305;
    U64 hoisted__U64_1306 = (U64)(hoisted__U32_1304);
    (void)hoisted__U64_1306;
    Type_delete(hoisted__Type_1305, 1);
    void * hoisted__v_1307 = malloc(hoisted__U64_1306);
    (void)hoisted__v_1307;
    U32 hoisted__U32_1308 = 0;
    (void)hoisted__U32_1308;
    I64 hoisted__I64_1309 = 1;
    (void)hoisted__I64_1309;
    Vec__Str *hoisted__Vec__Str_1310 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1310->data = hoisted__v_1307;
    hoisted__Vec__Str_1310->count = hoisted__U32_1308;
    hoisted__Vec__Str_1310->cap = hoisted__I64_1309;
    (void)hoisted__Vec__Str_1310;
    return hoisted__Vec__Str_1310;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1311 = self->count;
        (void)_re_U32_1311;
        U32 _rc_U32_1311 = 0;
        (void)_rc_U32_1311;
        Bool hoisted__Bool_1326 = U32_lte(_rc_U32_1311, _re_U32_1311);
        (void)hoisted__Bool_1326;
        if (hoisted__Bool_1326) {
            while (1) {
                Bool _wcond_Bool_1312 = U32_lt(_rc_U32_1311, _re_U32_1311);
                (void)_wcond_Bool_1312;
                if (_wcond_Bool_1312) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1311);
                U32_inc(&_rc_U32_1311);
                U32 hoisted__U32_1313 = 16;
                (void)hoisted__U32_1313;
                U32 hoisted__U32_1314 = U32_mul(i, hoisted__U32_1313);
                (void)hoisted__U32_1314;
                Type *hoisted__Type_1315 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1315;
                U64 hoisted__U64_1316 = (U64)(hoisted__U32_1314);
                (void)hoisted__U64_1316;
                Type_delete(hoisted__Type_1315, 1);
                Str *hoisted__Str_1317 = ptr_add(self->data, hoisted__U64_1316);
                (void)hoisted__Str_1317;
                (void)hoisted__Str_1317;
                Bool hoisted__Bool_1318 = 0;
                (void)hoisted__Bool_1318;
                Str_delete(hoisted__Str_1317, hoisted__Bool_1318);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1319 = U32_gt(_rc_U32_1311, _re_U32_1311);
                (void)_wcond_Bool_1319;
                if (_wcond_Bool_1319) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1311);
                U32_dec(&_rc_U32_1311);
                U32 hoisted__U32_1320 = 16;
                (void)hoisted__U32_1320;
                U32 hoisted__U32_1321 = U32_mul(i, hoisted__U32_1320);
                (void)hoisted__U32_1321;
                Type *hoisted__Type_1322 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1322;
                U64 hoisted__U64_1323 = (U64)(hoisted__U32_1321);
                (void)hoisted__U64_1323;
                Type_delete(hoisted__Type_1322, 1);
                Str *hoisted__Str_1324 = ptr_add(self->data, hoisted__U64_1323);
                (void)hoisted__Str_1324;
                (void)hoisted__Str_1324;
                Bool hoisted__Bool_1325 = 0;
                (void)hoisted__Bool_1325;
                Str_delete(hoisted__Str_1324, hoisted__Bool_1325);
            }
        }
    }
    U32 hoisted__U32_1327 = 0;
    (void)hoisted__U32_1327;
    self->count = hoisted__U32_1327;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1614 = 16;
    (void)hoisted__U32_1614;
    U32 hoisted__U32_1615 = U32_mul(self->cap, hoisted__U32_1614);
    (void)hoisted__U32_1615;
    Type *hoisted__Type_1616 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1616;
    U64 hoisted__U64_1617 = (U64)(hoisted__U32_1615);
    (void)hoisted__U64_1617;
    Type_delete(hoisted__Type_1616, 1);
    void * new_data = malloc(hoisted__U64_1617);
    {
        U32 _re_U32_1578 = self->count;
        (void)_re_U32_1578;
        U32 _rc_U32_1578 = 0;
        (void)_rc_U32_1578;
        Bool hoisted__Bool_1613 = U32_lte(_rc_U32_1578, _re_U32_1578);
        (void)hoisted__Bool_1613;
        if (hoisted__Bool_1613) {
            while (1) {
                Bool _wcond_Bool_1579 = U32_lt(_rc_U32_1578, _re_U32_1578);
                (void)_wcond_Bool_1579;
                if (_wcond_Bool_1579) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1578);
                U32_inc(&_rc_U32_1578);
                U32 hoisted__U32_1580 = 16;
                (void)hoisted__U32_1580;
                U32 hoisted__U32_1581 = U32_mul(i, hoisted__U32_1580);
                (void)hoisted__U32_1581;
                Type *hoisted__Type_1582 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1582;
                U64 hoisted__U64_1583 = (U64)(hoisted__U32_1581);
                (void)hoisted__U64_1583;
                Type_delete(hoisted__Type_1582, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1583);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1584 = 16;
                (void)hoisted__U32_1584;
                U32 hoisted__U32_1585 = U32_mul(i, hoisted__U32_1584);
                (void)hoisted__U32_1585;
                Type *hoisted__Type_1586 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1586;
                U64 hoisted__U64_1587 = (U64)(hoisted__U32_1585);
                (void)hoisted__U64_1587;
                Type_delete(hoisted__Type_1586, 1);
                U32 hoisted__U32_1588 = 16;
                (void)hoisted__U32_1588;
                Type *hoisted__Type_1589 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1589;
                void *hoisted__v_1590 = ptr_add(new_data, hoisted__U64_1587);
                (void)hoisted__v_1590;
                (void)hoisted__v_1590;
                U64 hoisted__U64_1591 = (U64)(hoisted__U32_1588);
                (void)hoisted__U64_1591;
                Type_delete(hoisted__Type_1589, 1);
                memcpy(hoisted__v_1590, cloned, hoisted__U64_1591);
                U32 hoisted__U32_1592 = 16;
                (void)hoisted__U32_1592;
                Type *hoisted__Type_1593 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1593;
                I32 hoisted__I32_1594 = 0;
                (void)hoisted__I32_1594;
                U64 hoisted__U64_1595 = (U64)(hoisted__U32_1592);
                (void)hoisted__U64_1595;
                Type_delete(hoisted__Type_1593, 1);
                memset(cloned, hoisted__I32_1594, hoisted__U64_1595);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1596 = U32_gt(_rc_U32_1578, _re_U32_1578);
                (void)_wcond_Bool_1596;
                if (_wcond_Bool_1596) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1578);
                U32_dec(&_rc_U32_1578);
                U32 hoisted__U32_1597 = 16;
                (void)hoisted__U32_1597;
                U32 hoisted__U32_1598 = U32_mul(i, hoisted__U32_1597);
                (void)hoisted__U32_1598;
                Type *hoisted__Type_1599 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1599;
                U64 hoisted__U64_1600 = (U64)(hoisted__U32_1598);
                (void)hoisted__U64_1600;
                Type_delete(hoisted__Type_1599, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1600);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1601 = 16;
                (void)hoisted__U32_1601;
                U32 hoisted__U32_1602 = U32_mul(i, hoisted__U32_1601);
                (void)hoisted__U32_1602;
                Type *hoisted__Type_1603 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1603;
                U64 hoisted__U64_1604 = (U64)(hoisted__U32_1602);
                (void)hoisted__U64_1604;
                Type_delete(hoisted__Type_1603, 1);
                U32 hoisted__U32_1605 = 16;
                (void)hoisted__U32_1605;
                Type *hoisted__Type_1606 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1606;
                void *hoisted__v_1607 = ptr_add(new_data, hoisted__U64_1604);
                (void)hoisted__v_1607;
                (void)hoisted__v_1607;
                U64 hoisted__U64_1608 = (U64)(hoisted__U32_1605);
                (void)hoisted__U64_1608;
                Type_delete(hoisted__Type_1606, 1);
                memcpy(hoisted__v_1607, cloned, hoisted__U64_1608);
                U32 hoisted__U32_1609 = 16;
                (void)hoisted__U32_1609;
                Type *hoisted__Type_1610 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1610;
                I32 hoisted__I32_1611 = 0;
                (void)hoisted__I32_1611;
                U64 hoisted__U64_1612 = (U64)(hoisted__U32_1609);
                (void)hoisted__U64_1612;
                Type_delete(hoisted__Type_1610, 1);
                memset(cloned, hoisted__I32_1611, hoisted__U64_1612);
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1618 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1618->data = new_data;
    hoisted__Vec__Str_1618->count = self->count;
    hoisted__Vec__Str_1618->cap = self->cap;
    (void)hoisted__Vec__Str_1618;
    return hoisted__Vec__Str_1618;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1619 = 16;
    (void)hoisted__U32_1619;
    return hoisted__U32_1619;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1623 = 8;
    (void)hoisted__U32_1623;
    return hoisted__U32_1623;
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
    I64 hoisted__I64_1818 = 0;
    (void)hoisted__I64_1818;
    Bool hoisted__Bool_1819 = I64_eq(val, hoisted__I64_1818);
    (void)hoisted__Bool_1819;
    if (hoisted__Bool_1819) {
        U64 hoisted__U64_1782 = 2ULL;
        (void)hoisted__U64_1782;
        void * buf = malloc(hoisted__U64_1782);
        I64 hoisted__I64_1783 = 48;
        (void)hoisted__I64_1783;
        U64 hoisted__U64_1784 = 1ULL;
        (void)hoisted__U64_1784;
        memcpy(buf, &hoisted__I64_1783, hoisted__U64_1784);
        U64 hoisted__U64_1785 = 1ULL;
        (void)hoisted__U64_1785;
        void *hoisted__v_1786 = ptr_add(buf, hoisted__U64_1785);
        (void)hoisted__v_1786;
        (void)hoisted__v_1786;
        I32 hoisted__I32_1787 = 0;
        (void)hoisted__I32_1787;
        U64 hoisted__U64_1788 = 1ULL;
        (void)hoisted__U64_1788;
        memset(hoisted__v_1786, hoisted__I32_1787, hoisted__U64_1788);
        I64 hoisted__I64_1789 = 1;
        (void)hoisted__I64_1789;
        I64 hoisted__I64_1790 = 1;
        (void)hoisted__I64_1790;
        Str *hoisted__Str_1791 = malloc(sizeof(Str));
        hoisted__Str_1791->c_str = buf;
        hoisted__Str_1791->count = hoisted__I64_1789;
        hoisted__Str_1791->cap = hoisted__I64_1790;
        (void)hoisted__Str_1791;
        { Str * _ret_val = hoisted__Str_1791;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1820 = 0;
    (void)hoisted__I64_1820;
    Bool hoisted__Bool_1821 = I64_lt(val, hoisted__I64_1820);
    (void)hoisted__Bool_1821;
    if (hoisted__Bool_1821) {
        Bool hoisted__Bool_1792 = 1;
        (void)hoisted__Bool_1792;
        is_neg = hoisted__Bool_1792;
        I64 hoisted__I64_1793 = 0;
        (void)hoisted__I64_1793;
        I64 hoisted__I64_1794 = I64_sub(hoisted__I64_1793, val);
        (void)hoisted__I64_1794;
        v = hoisted__I64_1794;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1796 = 0;
        (void)hoisted__I64_1796;
        Bool _wcond_Bool_1795 = I64_gt(tmp, hoisted__I64_1796);
        (void)_wcond_Bool_1795;
        if (_wcond_Bool_1795) {
        } else {
            break;
        }
        U64 hoisted__U64_1797 = 1ULL;
        (void)hoisted__U64_1797;
        U64 hoisted__U64_1798 = U64_add(ndigits, hoisted__U64_1797);
        (void)hoisted__U64_1798;
        ndigits = hoisted__U64_1798;
        I64 hoisted__I64_1799 = 10;
        (void)hoisted__I64_1799;
        I64 hoisted__I64_1800 = I64_div(tmp, hoisted__I64_1799);
        (void)hoisted__I64_1800;
        tmp = hoisted__I64_1800;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1801 = 1ULL;
        (void)hoisted__U64_1801;
        U64 hoisted__U64_1802 = U64_add(total, hoisted__U64_1801);
        (void)hoisted__U64_1802;
        total = hoisted__U64_1802;
    }
    U64 hoisted__U64_1822 = 1ULL;
    (void)hoisted__U64_1822;
    U64 hoisted__U64_1823 = U64_add(total, hoisted__U64_1822);
    (void)hoisted__U64_1823;
    void * buf = malloc(hoisted__U64_1823);
    if (is_neg) {
        I64 hoisted__I64_1803 = 45;
        (void)hoisted__I64_1803;
        U64 hoisted__U64_1804 = 1ULL;
        (void)hoisted__U64_1804;
        memcpy(buf, &hoisted__I64_1803, hoisted__U64_1804);
    }
    U64 hoisted__U64_1824 = 1ULL;
    (void)hoisted__U64_1824;
    U64 i = U64_sub(total, hoisted__U64_1824);
    while (1) {
        I64 hoisted__I64_1806 = 0;
        (void)hoisted__I64_1806;
        Bool _wcond_Bool_1805 = I64_gt(v, hoisted__I64_1806);
        (void)_wcond_Bool_1805;
        if (_wcond_Bool_1805) {
        } else {
            break;
        }
        I64 hoisted__I64_1807 = 10;
        (void)hoisted__I64_1807;
        I64 hoisted__I64_1808 = I64_mod(v, hoisted__I64_1807);
        (void)hoisted__I64_1808;
        I64 hoisted__I64_1809 = 48;
        (void)hoisted__I64_1809;
        I64 hoisted__I64_1810 = I64_add(hoisted__I64_1808, hoisted__I64_1809);
        (void)hoisted__I64_1810;
        void *hoisted__v_1811 = ptr_add(buf, i);
        (void)hoisted__v_1811;
        (void)hoisted__v_1811;
        U8 hoisted__U8_1812 = I64_to_u8(hoisted__I64_1810);
        (void)hoisted__U8_1812;
        U64 hoisted__U64_1813 = 1ULL;
        (void)hoisted__U64_1813;
        memcpy(hoisted__v_1811, &hoisted__U8_1812, hoisted__U64_1813);
        I64 hoisted__I64_1814 = 10;
        (void)hoisted__I64_1814;
        I64 hoisted__I64_1815 = I64_div(v, hoisted__I64_1814);
        (void)hoisted__I64_1815;
        v = hoisted__I64_1815;
        U64 hoisted__U64_1816 = 1ULL;
        (void)hoisted__U64_1816;
        U64 hoisted__U64_1817 = U64_sub(i, hoisted__U64_1816);
        (void)hoisted__U64_1817;
        i = hoisted__U64_1817;
    }
    void *hoisted__v_1825 = ptr_add(buf, total);
    (void)hoisted__v_1825;
    (void)hoisted__v_1825;
    I32 hoisted__I32_1826 = 0;
    (void)hoisted__I32_1826;
    U64 hoisted__U64_1827 = 1ULL;
    (void)hoisted__U64_1827;
    memset(hoisted__v_1825, hoisted__I32_1826, hoisted__U64_1827);
    Str *hoisted__Str_1828 = malloc(sizeof(Str));
    hoisted__Str_1828->c_str = buf;
    hoisted__Str_1828->count = total;
    hoisted__Str_1828->cap = total;
    (void)hoisted__Str_1828;
    return hoisted__Str_1828;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1848 = 8;
    (void)hoisted__U32_1848;
    return hoisted__U32_1848;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1969 = 0;
    (void)hoisted__U32_1969;
    U64 hoisted__U64_1970 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1969); });
    (void)hoisted__U64_1970;
    return hoisted__U64_1970;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1973 = I64_cmp(a, b);
    (void)hoisted__I64_1973;
    I64 hoisted__I64_1974 = -1;
    (void)hoisted__I64_1974;
    Bool hoisted__Bool_1975 = I64_eq(hoisted__I64_1973, hoisted__I64_1974);
    (void)hoisted__Bool_1975;
    return hoisted__Bool_1975;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1976 = I64_cmp(a, b);
    (void)hoisted__I64_1976;
    I64 hoisted__I64_1977 = 1;
    (void)hoisted__I64_1977;
    Bool hoisted__Bool_1978 = I64_eq(hoisted__I64_1976, hoisted__I64_1977);
    (void)hoisted__Bool_1978;
    return hoisted__Bool_1978;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1979 = I64_eq(a, b);
    (void)hoisted__Bool_1979;
    Bool hoisted__Bool_1980 = not(hoisted__Bool_1979);
    (void)hoisted__Bool_1980;
    return hoisted__Bool_1980;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1998 = Bool_eq(a, b);
    (void)hoisted__Bool_1998;
    if (hoisted__Bool_1998) {
        I64 hoisted__I64_1996 = 0;
        (void)hoisted__I64_1996;
        { I64 _ret_val = hoisted__I64_1996;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1997 = -1;
        (void)hoisted__I64_1997;
        return hoisted__I64_1997;
    }
    I64 hoisted__I64_1999 = 1;
    (void)hoisted__I64_1999;
    return hoisted__I64_1999;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2000 = 1;
    (void)hoisted__U32_2000;
    return hoisted__U32_2000;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2001 = 0;
    (void)hoisted__U32_2001;
    U64 hoisted__U64_2002 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2001); });
    (void)hoisted__U64_2002;
    return hoisted__U64_2002;
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
    Bool hoisted__Bool_2028 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2028;
    if (hoisted__Bool_2028) {
        Bool hoisted__Bool_2018 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2018;
        { Bool _ret_val = hoisted__Bool_2018;
                return _ret_val; }
    }
    Bool hoisted__Bool_2029 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2029;
    if (hoisted__Bool_2029) {
        Bool hoisted__Bool_2019 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2019;
        { Bool _ret_val = hoisted__Bool_2019;
                return _ret_val; }
    }
    Bool hoisted__Bool_2030 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2030;
    if (hoisted__Bool_2030) {
        Bool hoisted__Bool_2020 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2020;
        { Bool _ret_val = hoisted__Bool_2020;
                return _ret_val; }
    }
    Bool hoisted__Bool_2031 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2031;
    if (hoisted__Bool_2031) {
        Bool hoisted__Bool_2021 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2021;
        { Bool _ret_val = hoisted__Bool_2021;
                return _ret_val; }
    }
    Bool hoisted__Bool_2032 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2032;
    if (hoisted__Bool_2032) {
        Bool hoisted__Bool_2022 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2022;
        { Bool _ret_val = hoisted__Bool_2022;
                return _ret_val; }
    }
    Bool hoisted__Bool_2033 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2033;
    if (hoisted__Bool_2033) {
        Bool hoisted__Bool_2023 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2023;
        { Bool _ret_val = hoisted__Bool_2023;
                return _ret_val; }
    }
    Bool hoisted__Bool_2034 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2034;
    if (hoisted__Bool_2034) {
        Bool hoisted__Bool_2024 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2024;
        { Bool _ret_val = hoisted__Bool_2024;
                return _ret_val; }
    }
    Bool hoisted__Bool_2035 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2035;
    if (hoisted__Bool_2035) {
        Bool hoisted__Bool_2025 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2025;
        { Bool _ret_val = hoisted__Bool_2025;
                return _ret_val; }
    }
    Bool hoisted__Bool_2036 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2036;
    if (hoisted__Bool_2036) {
        Bool hoisted__Bool_2026 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2026;
        { Bool _ret_val = hoisted__Bool_2026;
                return _ret_val; }
    }
    Bool hoisted__Bool_2037 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2037;
    if (hoisted__Bool_2037) {
        Bool hoisted__Bool_2027 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2027;
        { Bool _ret_val = hoisted__Bool_2027;
                return _ret_val; }
    }
    Bool hoisted__Bool_2038 = 0;
    (void)hoisted__Bool_2038;
    return hoisted__Bool_2038;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2060 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2060;
    if (hoisted__Bool_2060) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2061 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2061;
    if (hoisted__Bool_2061) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2062 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2062;
    if (hoisted__Bool_2062) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2063 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2063;
    if (hoisted__Bool_2063) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2064 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2064;
    if (hoisted__Bool_2064) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2065 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2065;
    if (hoisted__Bool_2065) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2066 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2066;
    if (hoisted__Bool_2066) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2067 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2067;
    if (hoisted__Bool_2067) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2068 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2068;
    if (hoisted__Bool_2068) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2069 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2069;
    if (hoisted__Bool_2069) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2070 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2070;
    UNREACHABLE(&hoisted__Str_2070);
    Str_delete(&hoisted__Str_2070, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2071 = 4;
    (void)hoisted__U32_2071;
    return hoisted__U32_2071;
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
    Bool hoisted__Bool_2123 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2123;
    if (hoisted__Bool_2123) {
        Str *hoisted__Str_2113 = get_payload(self);
        (void)hoisted__Str_2113;
        (void)hoisted__Str_2113;
        Bool hoisted__Bool_2114 = 0;
        (void)hoisted__Bool_2114;
        Str_delete(hoisted__Str_2113, hoisted__Bool_2114);
    }
    Bool hoisted__Bool_2124 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2124;
    if (hoisted__Bool_2124) {
        Str *hoisted__Str_2115 = get_payload(self);
        (void)hoisted__Str_2115;
        (void)hoisted__Str_2115;
        Bool hoisted__Bool_2116 = 0;
        (void)hoisted__Bool_2116;
        Str_delete(hoisted__Str_2115, hoisted__Bool_2116);
    }
    Bool hoisted__Bool_2125 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2125;
    if (hoisted__Bool_2125) {
        Str *hoisted__Str_2117 = get_payload(self);
        (void)hoisted__Str_2117;
        (void)hoisted__Str_2117;
        Bool hoisted__Bool_2118 = 0;
        (void)hoisted__Bool_2118;
        Str_delete(hoisted__Str_2117, hoisted__Bool_2118);
    }
    Bool hoisted__Bool_2126 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2126;
    if (hoisted__Bool_2126) {
        Primitive *hoisted__Primitive_2119 = get_payload(self);
        (void)hoisted__Primitive_2119;
        (void)hoisted__Primitive_2119;
        Bool hoisted__Bool_2120 = 0;
        (void)hoisted__Bool_2120;
        Primitive_delete(hoisted__Primitive_2119, hoisted__Bool_2120);
    }
    Bool hoisted__Bool_2127 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2127;
    if (hoisted__Bool_2127) {
        Str *hoisted__Str_2121 = get_payload(self);
        (void)hoisted__Str_2121;
        (void)hoisted__Str_2121;
        Bool hoisted__Bool_2122 = 0;
        (void)hoisted__Bool_2122;
        Str_delete(hoisted__Str_2121, hoisted__Bool_2122);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2196 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2196;
    if (hoisted__Bool_2196) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2197 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2197;
    if (hoisted__Bool_2197) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2198 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2198;
    if (hoisted__Bool_2198) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2188 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2188;
        Type *hoisted__Type_2189 = Type_Struct(hoisted__Str_2188);
        (void)hoisted__Type_2189;
        { Type * _ret_val = hoisted__Type_2189;
                return _ret_val; }
    }
    Bool hoisted__Bool_2199 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2199;
    if (hoisted__Bool_2199) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2200 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2200;
    if (hoisted__Bool_2200) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2190 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2190;
        Type *hoisted__Type_2191 = Type_Enum(hoisted__Str_2190);
        (void)hoisted__Type_2191;
        { Type * _ret_val = hoisted__Type_2191;
                return _ret_val; }
    }
    Bool hoisted__Bool_2201 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2201;
    if (hoisted__Bool_2201) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2202 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2202;
    if (hoisted__Bool_2202) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2203 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2203;
    if (hoisted__Bool_2203) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2204 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2204;
    if (hoisted__Bool_2204) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2205 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2192 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2192;
        Type *hoisted__Type_2193 = Type_Custom(hoisted__Str_2192);
        (void)hoisted__Type_2193;
        { Type * _ret_val = hoisted__Type_2193;
                return _ret_val; }
    }
    Bool hoisted__Bool_2206 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2206;
    if (hoisted__Bool_2206) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2194 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2194;
        Type *hoisted__Type_2195 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2194; _oa; }));
        (void)hoisted__Type_2195;
        { Type * _ret_val = hoisted__Type_2195;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2207 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2207;
    Type *hoisted__Type_2208 = Type_FuncPtrSig(hoisted__Str_2207);
    (void)hoisted__Type_2208;
    return hoisted__Type_2208;
}

U32 Type_size(void) {
    U32 hoisted__U32_2209 = 24;
    (void)hoisted__U32_2209;
    return hoisted__U32_2209;
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
    Bool hoisted__Bool_2308 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2308;
    if (hoisted__Bool_2308) {
        Bool hoisted__Bool_2300 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2300;
        { Bool _ret_val = hoisted__Bool_2300;
                return _ret_val; }
    }
    Bool hoisted__Bool_2309 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2309;
    if (hoisted__Bool_2309) {
        Bool hoisted__Bool_2301 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2301;
        { Bool _ret_val = hoisted__Bool_2301;
                return _ret_val; }
    }
    Bool hoisted__Bool_2310 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2310;
    if (hoisted__Bool_2310) {
        Bool hoisted__Bool_2302 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2302;
        { Bool _ret_val = hoisted__Bool_2302;
                return _ret_val; }
    }
    Bool hoisted__Bool_2311 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        Bool hoisted__Bool_2303 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2303;
        { Bool _ret_val = hoisted__Bool_2303;
                return _ret_val; }
    }
    Bool hoisted__Bool_2312 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2312;
    if (hoisted__Bool_2312) {
        Bool hoisted__Bool_2304 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2304;
        { Bool _ret_val = hoisted__Bool_2304;
                return _ret_val; }
    }
    Bool hoisted__Bool_2313 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        Bool hoisted__Bool_2305 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2305;
        { Bool _ret_val = hoisted__Bool_2305;
                return _ret_val; }
    }
    Bool hoisted__Bool_2314 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2314;
    if (hoisted__Bool_2314) {
        Bool hoisted__Bool_2306 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2306;
        { Bool _ret_val = hoisted__Bool_2306;
                return _ret_val; }
    }
    Bool hoisted__Bool_2315 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2315;
    if (hoisted__Bool_2315) {
        Bool hoisted__Bool_2307 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2307;
        { Bool _ret_val = hoisted__Bool_2307;
                return _ret_val; }
    }
    Bool hoisted__Bool_2316 = 0;
    (void)hoisted__Bool_2316;
    return hoisted__Bool_2316;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2334 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2334;
    if (hoisted__Bool_2334) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2335 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2335;
    if (hoisted__Bool_2335) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2336 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2336;
    if (hoisted__Bool_2336) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2337 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2337;
    if (hoisted__Bool_2337) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2338 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2338;
    if (hoisted__Bool_2338) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2339 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2339;
    if (hoisted__Bool_2339) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2340 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2340;
    if (hoisted__Bool_2340) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2341 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2342 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2342;
    UNREACHABLE(&hoisted__Str_2342);
    Str_delete(&hoisted__Str_2342, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2343 = 4;
    (void)hoisted__U32_2343;
    return hoisted__U32_2343;
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
    Bool hoisted__Bool_2348 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2348;
    if (hoisted__Bool_2348) {
        Bool hoisted__Bool_2345 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2345;
        { Bool _ret_val = hoisted__Bool_2345;
                return _ret_val; }
    }
    Bool hoisted__Bool_2349 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2349;
    if (hoisted__Bool_2349) {
        Bool hoisted__Bool_2346 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2346;
        { Bool _ret_val = hoisted__Bool_2346;
                return _ret_val; }
    }
    Bool hoisted__Bool_2350 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2350;
    if (hoisted__Bool_2350) {
        Bool hoisted__Bool_2347 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2347;
        { Bool _ret_val = hoisted__Bool_2347;
                return _ret_val; }
    }
    Bool hoisted__Bool_2351 = 0;
    (void)hoisted__Bool_2351;
    return hoisted__Bool_2351;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2359 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2359;
    if (hoisted__Bool_2359) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2360 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2360;
    if (hoisted__Bool_2360) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2361 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2361;
    if (hoisted__Bool_2361) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2362 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2362;
    UNREACHABLE(&hoisted__Str_2362);
    Str_delete(&hoisted__Str_2362, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2363 = 4;
    (void)hoisted__U32_2363;
    return hoisted__U32_2363;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2365 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2365;
    Declaration *hoisted__Declaration_2366 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2366->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2366->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2366->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2366->is_mut = self->is_mut;
    hoisted__Declaration_2366->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2366->is_priv = self->is_priv;
    hoisted__Declaration_2366->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2366->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2366->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2366->default_value = hoisted__Expr_2365;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2366->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2366;
    return hoisted__Declaration_2366;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2367 = 0;
    (void)hoisted__Bool_2367;
    Str_delete(&self->name, hoisted__Bool_2367);
    Bool hoisted__Bool_2368 = 0;
    (void)hoisted__Bool_2368;
    Str_delete(&self->doc, hoisted__Bool_2368);
    Bool hoisted__Bool_2369 = 0;
    (void)hoisted__Bool_2369;
    Str_delete(&self->explicit_type, hoisted__Bool_2369);
    Bool hoisted__Bool_2370 = 0;
    (void)hoisted__Bool_2370;
    Bool_delete(&self->is_mut, hoisted__Bool_2370);
    Bool hoisted__Bool_2371 = 0;
    (void)hoisted__Bool_2371;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2371);
    Bool hoisted__Bool_2372 = 0;
    (void)hoisted__Bool_2372;
    Bool_delete(&self->is_priv, hoisted__Bool_2372);
    Bool hoisted__Bool_2373 = 0;
    (void)hoisted__Bool_2373;
    Bool_delete(&self->used, hoisted__Bool_2373);
    Bool hoisted__Bool_2374 = 0;
    (void)hoisted__Bool_2374;
    OwnType_delete(&self->own_type, hoisted__Bool_2374);
    Bool hoisted__Bool_2375 = 0;
    (void)hoisted__Bool_2375;
    Type_delete(&self->til_type, hoisted__Bool_2375);
    Bool hoisted__Bool_2376 = 1;
    (void)hoisted__Bool_2376;
    Expr_delete(self->default_value, hoisted__Bool_2376);
    Bool hoisted__Bool_2377 = 0;
    (void)hoisted__Bool_2377;
    Str_delete(&self->orig_name, hoisted__Bool_2377);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2378 = 104;
    (void)hoisted__U32_2378;
    return hoisted__U32_2378;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2380 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2380->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2380->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2380->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2380->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2380->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2380->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2380->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2380->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2380->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2380->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2380->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2380;
    return hoisted__FunctionDef_2380;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2381 = 0;
    (void)hoisted__Bool_2381;
    FuncType_delete(&self->func_type, hoisted__Bool_2381);
    Bool hoisted__Bool_2382 = 0;
    (void)hoisted__Bool_2382;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2382);
    Bool hoisted__Bool_2383 = 0;
    (void)hoisted__Bool_2383;
    Str_delete(&self->return_type, hoisted__Bool_2383);
    Bool hoisted__Bool_2384 = 0;
    (void)hoisted__Bool_2384;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2384);
    Bool hoisted__Bool_2385 = 0;
    (void)hoisted__Bool_2385;
    I32_delete(&self->variadic_index, hoisted__Bool_2385);
    Bool hoisted__Bool_2386 = 0;
    (void)hoisted__Bool_2386;
    I32_delete(&self->kwargs_index, hoisted__Bool_2386);
    Bool hoisted__Bool_2387 = 0;
    (void)hoisted__Bool_2387;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2387);
    Bool hoisted__Bool_2388 = 0;
    (void)hoisted__Bool_2388;
    Bool_delete(&self->auto_generated, hoisted__Bool_2388);
    Bool hoisted__Bool_2389 = 0;
    (void)hoisted__Bool_2389;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2389);
    Bool hoisted__Bool_2390 = 0;
    (void)hoisted__Bool_2390;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2390);
    Bool hoisted__Bool_2391 = 0;
    (void)hoisted__Bool_2391;
    Str_delete(&self->closure_name, hoisted__Bool_2391);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2392 = 0;
    (void)hoisted__U32_2392;
    U64 hoisted__U64_2393 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2392); });
    (void)hoisted__U64_2393;
    return hoisted__U64_2393;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2394 = 104;
    (void)hoisted__U32_2394;
    return hoisted__U32_2394;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2397 = malloc(sizeof(FCallData));
    hoisted__FCallData_2397->is_splat = self->is_splat;
    hoisted__FCallData_2397->does_throw = self->does_throw;
    hoisted__FCallData_2397->is_bang = self->is_bang;
    hoisted__FCallData_2397->own_args = self->own_args;
    hoisted__FCallData_2397->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2397->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2397;
    return hoisted__FCallData_2397;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2398 = 0;
    (void)hoisted__Bool_2398;
    Bool_delete(&self->is_splat, hoisted__Bool_2398);
    Bool hoisted__Bool_2399 = 0;
    (void)hoisted__Bool_2399;
    Bool_delete(&self->does_throw, hoisted__Bool_2399);
    Bool hoisted__Bool_2400 = 0;
    (void)hoisted__Bool_2400;
    Bool_delete(&self->is_bang, hoisted__Bool_2400);
    Bool hoisted__Bool_2401 = 0;
    (void)hoisted__Bool_2401;
    U64_delete(&self->own_args, hoisted__Bool_2401);
    Bool hoisted__Bool_2402 = 0;
    (void)hoisted__Bool_2402;
    Bool_delete(&self->swap_replace, hoisted__Bool_2402);
    Bool hoisted__Bool_2403 = 0;
    (void)hoisted__Bool_2403;
    Type_delete(&self->til_type, hoisted__Bool_2403);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2404 = 0;
    (void)hoisted__U32_2404;
    U64 hoisted__U64_2405 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2404); });
    (void)hoisted__U64_2405;
    return hoisted__U64_2405;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2406 = 48;
    (void)hoisted__U32_2406;
    return hoisted__U32_2406;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2418 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2418->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2418->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2418;
    return hoisted__LiteralNumData_2418;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2419 = 0;
    (void)hoisted__Bool_2419;
    Str_delete(&self->text, hoisted__Bool_2419);
    Bool hoisted__Bool_2420 = 0;
    (void)hoisted__Bool_2420;
    Type_delete(&self->til_type, hoisted__Bool_2420);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2421 = 0;
    (void)hoisted__U32_2421;
    U64 hoisted__U64_2422 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2421); });
    (void)hoisted__U64_2422;
    return hoisted__U64_2422;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2423 = 40;
    (void)hoisted__U32_2423;
    return hoisted__U32_2423;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2434 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2434->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2434->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2434;
    return hoisted__IdentData_2434;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2435 = 0;
    (void)hoisted__Bool_2435;
    Str_delete(&self->name, hoisted__Bool_2435);
    Bool hoisted__Bool_2436 = 0;
    (void)hoisted__Bool_2436;
    Type_delete(&self->til_type, hoisted__Bool_2436);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2437 = 0;
    (void)hoisted__U32_2437;
    U64 hoisted__U64_2438 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2437); });
    (void)hoisted__U64_2438;
    return hoisted__U64_2438;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2439 = 40;
    (void)hoisted__U32_2439;
    return hoisted__U32_2439;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2446 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2446->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2446->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2446;
    return hoisted__FieldAccessData_2446;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2447 = 0;
    (void)hoisted__Bool_2447;
    Str_delete(&self->name, hoisted__Bool_2447);
    Bool hoisted__Bool_2448 = 0;
    (void)hoisted__Bool_2448;
    Type_delete(&self->til_type, hoisted__Bool_2448);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2449 = 0;
    (void)hoisted__U32_2449;
    U64 hoisted__U64_2450 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2449); });
    (void)hoisted__U64_2450;
    return hoisted__U64_2450;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2451 = 40;
    (void)hoisted__U32_2451;
    return hoisted__U32_2451;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2484 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2484->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2484->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2484->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2484->is_interface = self->is_interface;
    hoisted__StructDef_2484->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2484->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2484;
    return hoisted__StructDef_2484;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2485 = 0;
    (void)hoisted__Bool_2485;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2485);
    Bool hoisted__Bool_2486 = 0;
    (void)hoisted__Bool_2486;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2486);
    Bool hoisted__Bool_2487 = 0;
    (void)hoisted__Bool_2487;
    Str_delete(&self->c_tag, hoisted__Bool_2487);
    Bool hoisted__Bool_2488 = 0;
    (void)hoisted__Bool_2488;
    Bool_delete(&self->is_interface, hoisted__Bool_2488);
    Bool hoisted__Bool_2489 = 0;
    (void)hoisted__Bool_2489;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2489);
    Bool hoisted__Bool_2490 = 0;
    (void)hoisted__Bool_2490;
    Str_delete(&self->implements_name, hoisted__Bool_2490);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2491 = 0;
    (void)hoisted__U32_2491;
    U64 hoisted__U64_2492 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2491); });
    (void)hoisted__U64_2492;
    return hoisted__U64_2492;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2493 = 72;
    (void)hoisted__U32_2493;
    return hoisted__U32_2493;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2498 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2498->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2498->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2498->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2498->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2498->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2498;
    return hoisted__EnumDef_2498;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2499 = 0;
    (void)hoisted__Bool_2499;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2499);
    Bool hoisted__Bool_2500 = 0;
    (void)hoisted__Bool_2500;
    Vec__Str_delete(&self->variants, hoisted__Bool_2500);
    Bool hoisted__Bool_2501 = 0;
    (void)hoisted__Bool_2501;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2501);
    Bool hoisted__Bool_2502 = 0;
    (void)hoisted__Bool_2502;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2502);
    Bool hoisted__Bool_2503 = 0;
    (void)hoisted__Bool_2503;
    Str_delete(&self->implements_name, hoisted__Bool_2503);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2504 = 0;
    (void)hoisted__U32_2504;
    U64 hoisted__U64_2505 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2504); });
    (void)hoisted__U64_2505;
    return hoisted__U64_2505;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2506 = 96;
    (void)hoisted__U32_2506;
    return hoisted__U32_2506;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2602 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2602->name = *_ca; free(_ca); }
    hoisted__AssignData_2602->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2602->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2602->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2602;
    return hoisted__AssignData_2602;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Str_delete(&self->name, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    Bool_delete(&self->swap_replace, hoisted__Bool_2606);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2607 = 0;
    (void)hoisted__U32_2607;
    U64 hoisted__U64_2608 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2607); });
    (void)hoisted__U64_2608;
    return hoisted__U64_2608;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2609 = 24;
    (void)hoisted__U32_2609;
    return hoisted__U32_2609;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2611 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2611->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2611->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2611;
    return hoisted__FieldAssignData_2611;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2612 = 0;
    (void)hoisted__Bool_2612;
    Str_delete(&self->name, hoisted__Bool_2612);
    Bool hoisted__Bool_2613 = 0;
    (void)hoisted__Bool_2613;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2613);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2614 = 0;
    (void)hoisted__U32_2614;
    U64 hoisted__U64_2615 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2614); });
    (void)hoisted__U64_2615;
    return hoisted__U64_2615;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2616 = 24;
    (void)hoisted__U32_2616;
    return hoisted__U32_2616;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2618 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2618->name = *_ca; free(_ca); }
    hoisted__ForInData_2618->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2618->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2618;
    return hoisted__ForInData_2618;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2619 = 0;
    (void)hoisted__Bool_2619;
    Str_delete(&self->name, hoisted__Bool_2619);
    Bool hoisted__Bool_2620 = 0;
    (void)hoisted__Bool_2620;
    Bool_delete(&self->is_mut, hoisted__Bool_2620);
    Bool hoisted__Bool_2621 = 0;
    (void)hoisted__Bool_2621;
    Type_delete(&self->til_type, hoisted__Bool_2621);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2622 = 0;
    (void)hoisted__U32_2622;
    U64 hoisted__U64_2623 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2622); });
    (void)hoisted__U64_2623;
    return hoisted__U64_2623;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2624 = 48;
    (void)hoisted__U32_2624;
    return hoisted__U32_2624;
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
    Bool hoisted__Bool_2654 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2654;
    if (hoisted__Bool_2654) {
        Str *hoisted__Str_2648 = get_payload(self);
        (void)hoisted__Str_2648;
        (void)hoisted__Str_2648;
        Bool hoisted__Bool_2649 = 0;
        (void)hoisted__Bool_2649;
        Str_delete(hoisted__Str_2648, hoisted__Bool_2649);
    }
    Bool hoisted__Bool_2655 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2655;
    if (hoisted__Bool_2655) {
        LiteralNumData *hoisted__LiteralNumData_2650 = get_payload(self);
        (void)hoisted__LiteralNumData_2650;
        (void)hoisted__LiteralNumData_2650;
        Bool hoisted__Bool_2651 = 0;
        (void)hoisted__Bool_2651;
        LiteralNumData_delete(hoisted__LiteralNumData_2650, hoisted__Bool_2651);
    }
    Bool hoisted__Bool_2656 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2656;
    if (hoisted__Bool_2656) {
        Bool *hoisted__Bool_2652 = get_payload(self);
        (void)hoisted__Bool_2652;
        (void)hoisted__Bool_2652;
        Bool hoisted__Bool_2653 = 0;
        (void)hoisted__Bool_2653;
        Bool_delete(hoisted__Bool_2652, hoisted__Bool_2653);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2696 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2696;
    if (hoisted__Bool_2696) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2691 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2691;
        Literal *hoisted__Literal_2692 = Literal_Str(hoisted__Str_2691);
        (void)hoisted__Literal_2692;
        { Literal * _ret_val = hoisted__Literal_2692;
                return _ret_val; }
    }
    Bool hoisted__Bool_2697 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2697;
    if (hoisted__Bool_2697) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2693 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2693;
        Literal *hoisted__Literal_2694 = Literal_Num(hoisted__LiteralNumData_2693);
        (void)hoisted__Literal_2694;
        { Literal * _ret_val = hoisted__Literal_2694;
                return _ret_val; }
    }
    Bool hoisted__Bool_2698 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2698;
    if (hoisted__Bool_2698) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2695 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2695;
        { Literal * _ret_val = hoisted__Literal_2695;
                return _ret_val; }
    }
    Bool hoisted__Bool_2699 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2699;
    if (hoisted__Bool_2699) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2700 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2700;
    if (hoisted__Bool_2700) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2701 = 48;
    (void)hoisted__U32_2701;
    return hoisted__U32_2701;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2704 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2704->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2704->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2704;
    return hoisted__MatchData_2704;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    Type_delete(&self->til_type, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Str_delete(&self->result_temp, hoisted__Bool_2706);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2707 = 0;
    (void)hoisted__U32_2707;
    U64 hoisted__U64_2708 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2707); });
    (void)hoisted__U64_2708;
    return hoisted__U64_2708;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2709 = 40;
    (void)hoisted__U32_2709;
    return hoisted__U32_2709;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2714 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2714->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2714;
    return hoisted__CaptureBlockData_2714;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2715 = 0;
    (void)hoisted__Bool_2715;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2715);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2716 = 0;
    (void)hoisted__U32_2716;
    U64 hoisted__U64_2717 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2716); });
    (void)hoisted__U64_2717;
    return hoisted__U64_2717;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2718 = 16;
    (void)hoisted__U32_2718;
    return hoisted__U32_2718;
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
    Bool hoisted__Bool_2895 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_2895;
    if (hoisted__Bool_2895) {
        Literal *hoisted__Literal_2867 = get_payload(self);
        (void)hoisted__Literal_2867;
        (void)hoisted__Literal_2867;
        Bool hoisted__Bool_2868 = 0;
        (void)hoisted__Bool_2868;
        Literal_delete(hoisted__Literal_2867, hoisted__Bool_2868);
    }
    Bool hoisted__Bool_2896 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_2896;
    if (hoisted__Bool_2896) {
        IdentData *hoisted__IdentData_2869 = get_payload(self);
        (void)hoisted__IdentData_2869;
        (void)hoisted__IdentData_2869;
        Bool hoisted__Bool_2870 = 0;
        (void)hoisted__Bool_2870;
        IdentData_delete(hoisted__IdentData_2869, hoisted__Bool_2870);
    }
    Bool hoisted__Bool_2897 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_2897;
    if (hoisted__Bool_2897) {
        Declaration *hoisted__Declaration_2871 = get_payload(self);
        (void)hoisted__Declaration_2871;
        (void)hoisted__Declaration_2871;
        Bool hoisted__Bool_2872 = 0;
        (void)hoisted__Bool_2872;
        Declaration_delete(hoisted__Declaration_2871, hoisted__Bool_2872);
    }
    Bool hoisted__Bool_2898 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_2898;
    if (hoisted__Bool_2898) {
        AssignData *hoisted__AssignData_2873 = get_payload(self);
        (void)hoisted__AssignData_2873;
        (void)hoisted__AssignData_2873;
        Bool hoisted__Bool_2874 = 0;
        (void)hoisted__Bool_2874;
        AssignData_delete(hoisted__AssignData_2873, hoisted__Bool_2874);
    }
    Bool hoisted__Bool_2899 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_2899;
    if (hoisted__Bool_2899) {
        FCallData *hoisted__FCallData_2875 = get_payload(self);
        (void)hoisted__FCallData_2875;
        (void)hoisted__FCallData_2875;
        Bool hoisted__Bool_2876 = 0;
        (void)hoisted__Bool_2876;
        FCallData_delete(hoisted__FCallData_2875, hoisted__Bool_2876);
    }
    Bool hoisted__Bool_2900 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_2900;
    if (hoisted__Bool_2900) {
        FunctionDef *hoisted__FunctionDef_2877 = get_payload(self);
        (void)hoisted__FunctionDef_2877;
        (void)hoisted__FunctionDef_2877;
        Bool hoisted__Bool_2878 = 0;
        (void)hoisted__Bool_2878;
        FunctionDef_delete(hoisted__FunctionDef_2877, hoisted__Bool_2878);
    }
    Bool hoisted__Bool_2901 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_2901;
    if (hoisted__Bool_2901) {
        StructDef *hoisted__StructDef_2879 = get_payload(self);
        (void)hoisted__StructDef_2879;
        (void)hoisted__StructDef_2879;
        Bool hoisted__Bool_2880 = 0;
        (void)hoisted__Bool_2880;
        StructDef_delete(hoisted__StructDef_2879, hoisted__Bool_2880);
    }
    Bool hoisted__Bool_2902 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_2902;
    if (hoisted__Bool_2902) {
        EnumDef *hoisted__EnumDef_2881 = get_payload(self);
        (void)hoisted__EnumDef_2881;
        (void)hoisted__EnumDef_2881;
        Bool hoisted__Bool_2882 = 0;
        (void)hoisted__Bool_2882;
        EnumDef_delete(hoisted__EnumDef_2881, hoisted__Bool_2882);
    }
    Bool hoisted__Bool_2903 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_2903;
    if (hoisted__Bool_2903) {
        FieldAccessData *hoisted__FieldAccessData_2883 = get_payload(self);
        (void)hoisted__FieldAccessData_2883;
        (void)hoisted__FieldAccessData_2883;
        Bool hoisted__Bool_2884 = 0;
        (void)hoisted__Bool_2884;
        FieldAccessData_delete(hoisted__FieldAccessData_2883, hoisted__Bool_2884);
    }
    Bool hoisted__Bool_2904 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_2904;
    if (hoisted__Bool_2904) {
        FieldAssignData *hoisted__FieldAssignData_2885 = get_payload(self);
        (void)hoisted__FieldAssignData_2885;
        (void)hoisted__FieldAssignData_2885;
        Bool hoisted__Bool_2886 = 0;
        (void)hoisted__Bool_2886;
        FieldAssignData_delete(hoisted__FieldAssignData_2885, hoisted__Bool_2886);
    }
    Bool hoisted__Bool_2905 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_2905;
    if (hoisted__Bool_2905) {
        ForInData *hoisted__ForInData_2887 = get_payload(self);
        (void)hoisted__ForInData_2887;
        (void)hoisted__ForInData_2887;
        Bool hoisted__Bool_2888 = 0;
        (void)hoisted__Bool_2888;
        ForInData_delete(hoisted__ForInData_2887, hoisted__Bool_2888);
    }
    Bool hoisted__Bool_2906 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_2906;
    if (hoisted__Bool_2906) {
        Str *hoisted__Str_2889 = get_payload(self);
        (void)hoisted__Str_2889;
        (void)hoisted__Str_2889;
        Bool hoisted__Bool_2890 = 0;
        (void)hoisted__Bool_2890;
        Str_delete(hoisted__Str_2889, hoisted__Bool_2890);
    }
    Bool hoisted__Bool_2907 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_2907;
    if (hoisted__Bool_2907) {
        MatchData *hoisted__MatchData_2891 = get_payload(self);
        (void)hoisted__MatchData_2891;
        (void)hoisted__MatchData_2891;
        Bool hoisted__Bool_2892 = 0;
        (void)hoisted__Bool_2892;
        MatchData_delete(hoisted__MatchData_2891, hoisted__Bool_2892);
    }
    Bool hoisted__Bool_2908 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_2908;
    if (hoisted__Bool_2908) {
        CaptureBlockData *hoisted__CaptureBlockData_2893 = get_payload(self);
        (void)hoisted__CaptureBlockData_2893;
        (void)hoisted__CaptureBlockData_2893;
        Bool hoisted__Bool_2894 = 0;
        (void)hoisted__Bool_2894;
        CaptureBlockData_delete(hoisted__CaptureBlockData_2893, hoisted__Bool_2894);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3086 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3086;
    if (hoisted__Bool_3086) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3087 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3087;
    if (hoisted__Bool_3087) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3060 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3060;
        NodeType *hoisted__NodeType_3061 = NodeType_Literal(hoisted__Literal_3060);
        (void)hoisted__NodeType_3061;
        { NodeType * _ret_val = hoisted__NodeType_3061;
                return _ret_val; }
    }
    Bool hoisted__Bool_3088 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3088;
    if (hoisted__Bool_3088) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3062 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3062;
        NodeType *hoisted__NodeType_3063 = NodeType_Ident(hoisted__IdentData_3062);
        (void)hoisted__NodeType_3063;
        { NodeType * _ret_val = hoisted__NodeType_3063;
                return _ret_val; }
    }
    Bool hoisted__Bool_3089 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3089;
    if (hoisted__Bool_3089) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3064 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3064;
        NodeType *hoisted__NodeType_3065 = NodeType_Decl(hoisted__Declaration_3064);
        (void)hoisted__NodeType_3065;
        { NodeType * _ret_val = hoisted__NodeType_3065;
                return _ret_val; }
    }
    Bool hoisted__Bool_3090 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3090;
    if (hoisted__Bool_3090) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3066 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3066;
        NodeType *hoisted__NodeType_3067 = NodeType_Assign(hoisted__AssignData_3066);
        (void)hoisted__NodeType_3067;
        { NodeType * _ret_val = hoisted__NodeType_3067;
                return _ret_val; }
    }
    Bool hoisted__Bool_3091 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3091;
    if (hoisted__Bool_3091) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3068 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3068;
        NodeType *hoisted__NodeType_3069 = NodeType_FCall(hoisted__FCallData_3068);
        (void)hoisted__NodeType_3069;
        { NodeType * _ret_val = hoisted__NodeType_3069;
                return _ret_val; }
    }
    Bool hoisted__Bool_3092 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3092;
    if (hoisted__Bool_3092) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3070 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3070;
        NodeType *hoisted__NodeType_3071 = NodeType_FuncDef(hoisted__FunctionDef_3070);
        (void)hoisted__NodeType_3071;
        { NodeType * _ret_val = hoisted__NodeType_3071;
                return _ret_val; }
    }
    Bool hoisted__Bool_3093 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3093;
    if (hoisted__Bool_3093) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3072 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3072;
        NodeType *hoisted__NodeType_3073 = NodeType_StructDef(hoisted__StructDef_3072);
        (void)hoisted__NodeType_3073;
        { NodeType * _ret_val = hoisted__NodeType_3073;
                return _ret_val; }
    }
    Bool hoisted__Bool_3094 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3094;
    if (hoisted__Bool_3094) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3074 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3074;
        NodeType *hoisted__NodeType_3075 = NodeType_EnumDef(hoisted__EnumDef_3074);
        (void)hoisted__NodeType_3075;
        { NodeType * _ret_val = hoisted__NodeType_3075;
                return _ret_val; }
    }
    Bool hoisted__Bool_3095 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3095;
    if (hoisted__Bool_3095) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3076 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3076;
        NodeType *hoisted__NodeType_3077 = NodeType_FieldAccess(hoisted__FieldAccessData_3076);
        (void)hoisted__NodeType_3077;
        { NodeType * _ret_val = hoisted__NodeType_3077;
                return _ret_val; }
    }
    Bool hoisted__Bool_3096 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3096;
    if (hoisted__Bool_3096) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3078 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3078;
        NodeType *hoisted__NodeType_3079 = NodeType_FieldAssign(hoisted__FieldAssignData_3078);
        (void)hoisted__NodeType_3079;
        { NodeType * _ret_val = hoisted__NodeType_3079;
                return _ret_val; }
    }
    Bool hoisted__Bool_3097 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3097;
    if (hoisted__Bool_3097) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3098 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3098;
    if (hoisted__Bool_3098) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3099 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3099;
    if (hoisted__Bool_3099) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3100 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3100;
    if (hoisted__Bool_3100) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3080 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3080;
        NodeType *hoisted__NodeType_3081 = NodeType_ForIn(hoisted__ForInData_3080);
        (void)hoisted__NodeType_3081;
        { NodeType * _ret_val = hoisted__NodeType_3081;
                return _ret_val; }
    }
    Bool hoisted__Bool_3101 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3101;
    if (hoisted__Bool_3101) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3082 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3082;
        NodeType *hoisted__NodeType_3083 = NodeType_NamedArg(hoisted__Str_3082);
        (void)hoisted__NodeType_3083;
        { NodeType * _ret_val = hoisted__NodeType_3083;
                return _ret_val; }
    }
    Bool hoisted__Bool_3102 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3102;
    if (hoisted__Bool_3102) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3103 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3103;
    if (hoisted__Bool_3103) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3104 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3104;
    if (hoisted__Bool_3104) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3105 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3105;
    if (hoisted__Bool_3105) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3084 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3084;
        NodeType *hoisted__NodeType_3085 = NodeType_Match(hoisted__MatchData_3084);
        (void)hoisted__NodeType_3085;
        { NodeType * _ret_val = hoisted__NodeType_3085;
                return _ret_val; }
    }
    Bool hoisted__Bool_3106 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3106;
    if (hoisted__Bool_3106) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3107 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3107;
    if (hoisted__Bool_3107) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3108 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3108;
    if (hoisted__Bool_3108) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3109 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3109;
    if (hoisted__Bool_3109) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3110 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3110;
    if (hoisted__Bool_3110) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
    (void)_clone_payload_CaptureBlock_25;
    (void)_clone_payload_CaptureBlock_25;
    CaptureBlockData *hoisted__CaptureBlockData_3111 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
    (void)hoisted__CaptureBlockData_3111;
    NodeType *hoisted__NodeType_3112 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3111);
    (void)hoisted__NodeType_3112;
    return hoisted__NodeType_3112;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3113 = 112;
    (void)hoisted__U32_3113;
    return hoisted__U32_3113;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3114 = is_null(self);
    (void)hoisted__Bool_3114;
    if (hoisted__Bool_3114) {
        return;
    }
    Bool hoisted__Bool_3115 = 0;
    (void)hoisted__Bool_3115;
    NodeType_delete(&self->node_type, hoisted__Bool_3115);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3174 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3174->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3174->children = *_ca; free(_ca); }
    hoisted__Expr_3174->line = line;
    hoisted__Expr_3174->col = col;
    (void)hoisted__Expr_3174;
    return hoisted__Expr_3174;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3182 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3182->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3182->children = *_ca; free(_ca); }
    hoisted__Expr_3182->line = self->line;
    hoisted__Expr_3182->col = self->col;
    (void)hoisted__Expr_3182;
    return hoisted__Expr_3182;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3183 = 0;
    (void)hoisted__U32_3183;
    U64 hoisted__U64_3184 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3183); });
    (void)hoisted__U64_3184;
    return hoisted__U64_3184;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3185 = 136;
    (void)hoisted__U32_3185;
    return hoisted__U32_3185;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_3766 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_3766->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_3766->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3766;
    return hoisted__Map__I64_Str_3766;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_3911 = 0;
    (void)hoisted__Bool_3911;
    Vec__I64_delete(&self->keys, hoisted__Bool_3911);
    Bool hoisted__Bool_3912 = 0;
    (void)hoisted__Bool_3912;
    Vec__Str_delete(&self->values, hoisted__Bool_3912);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_3913 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_3913->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_3913->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3913;
    return hoisted__Map__I64_Str_3913;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_3914 = 0;
    (void)hoisted__U32_3914;
    U64 hoisted__U64_3915 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3914); });
    (void)hoisted__U64_3915;
    return hoisted__U64_3915;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_3916 = 32;
    (void)hoisted__U32_3916;
    return hoisted__U32_3916;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_3917 = 1;
    (void)hoisted__U32_3917;
    Type *hoisted__Type_3918 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_3918;
    U64 hoisted__U64_3919 = (U64)(hoisted__U32_3917);
    (void)hoisted__U64_3919;
    Type_delete(hoisted__Type_3918, 1);
    void * hoisted__v_3920 = malloc(hoisted__U64_3919);
    (void)hoisted__v_3920;
    U32 hoisted__U32_3921 = 0;
    (void)hoisted__U32_3921;
    I64 hoisted__I64_3922 = 1;
    (void)hoisted__I64_3922;
    Vec__Bool *hoisted__Vec__Bool_3923 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_3923->data = hoisted__v_3920;
    hoisted__Vec__Bool_3923->count = hoisted__U32_3921;
    hoisted__Vec__Bool_3923->cap = hoisted__I64_3922;
    (void)hoisted__Vec__Bool_3923;
    return hoisted__Vec__Bool_3923;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_3924 = self->count;
        (void)_re_U32_3924;
        U32 _rc_U32_3924 = 0;
        (void)_rc_U32_3924;
        Bool hoisted__Bool_3939 = U32_lte(_rc_U32_3924, _re_U32_3924);
        (void)hoisted__Bool_3939;
        if (hoisted__Bool_3939) {
            while (1) {
                Bool _wcond_Bool_3925 = U32_lt(_rc_U32_3924, _re_U32_3924);
                (void)_wcond_Bool_3925;
                if (_wcond_Bool_3925) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3924);
                U32_inc(&_rc_U32_3924);
                U32 hoisted__U32_3926 = 1;
                (void)hoisted__U32_3926;
                U32 hoisted__U32_3927 = U32_mul(i, hoisted__U32_3926);
                (void)hoisted__U32_3927;
                Type *hoisted__Type_3928 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_3928;
                U64 hoisted__U64_3929 = (U64)(hoisted__U32_3927);
                (void)hoisted__U64_3929;
                Type_delete(hoisted__Type_3928, 1);
                Bool *hoisted__Bool_3930 = ptr_add(self->data, hoisted__U64_3929);
                (void)hoisted__Bool_3930;
                (void)hoisted__Bool_3930;
                Bool hoisted__Bool_3931 = 0;
                (void)hoisted__Bool_3931;
                Bool_delete(hoisted__Bool_3930, hoisted__Bool_3931);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3932 = U32_gt(_rc_U32_3924, _re_U32_3924);
                (void)_wcond_Bool_3932;
                if (_wcond_Bool_3932) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3924);
                U32_dec(&_rc_U32_3924);
                U32 hoisted__U32_3933 = 1;
                (void)hoisted__U32_3933;
                U32 hoisted__U32_3934 = U32_mul(i, hoisted__U32_3933);
                (void)hoisted__U32_3934;
                Type *hoisted__Type_3935 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_3935;
                U64 hoisted__U64_3936 = (U64)(hoisted__U32_3934);
                (void)hoisted__U64_3936;
                Type_delete(hoisted__Type_3935, 1);
                Bool *hoisted__Bool_3937 = ptr_add(self->data, hoisted__U64_3936);
                (void)hoisted__Bool_3937;
                (void)hoisted__Bool_3937;
                Bool hoisted__Bool_3938 = 0;
                (void)hoisted__Bool_3938;
                Bool_delete(hoisted__Bool_3937, hoisted__Bool_3938);
            }
        }
    }
    U32 hoisted__U32_3940 = 0;
    (void)hoisted__U32_3940;
    self->count = hoisted__U32_3940;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4227 = 1;
    (void)hoisted__U32_4227;
    U32 hoisted__U32_4228 = U32_mul(self->cap, hoisted__U32_4227);
    (void)hoisted__U32_4228;
    Type *hoisted__Type_4229 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4229;
    U64 hoisted__U64_4230 = (U64)(hoisted__U32_4228);
    (void)hoisted__U64_4230;
    Type_delete(hoisted__Type_4229, 1);
    void * new_data = malloc(hoisted__U64_4230);
    {
        U32 _re_U32_4191 = self->count;
        (void)_re_U32_4191;
        U32 _rc_U32_4191 = 0;
        (void)_rc_U32_4191;
        Bool hoisted__Bool_4226 = U32_lte(_rc_U32_4191, _re_U32_4191);
        (void)hoisted__Bool_4226;
        if (hoisted__Bool_4226) {
            while (1) {
                Bool _wcond_Bool_4192 = U32_lt(_rc_U32_4191, _re_U32_4191);
                (void)_wcond_Bool_4192;
                if (_wcond_Bool_4192) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4191);
                U32_inc(&_rc_U32_4191);
                U32 hoisted__U32_4193 = 1;
                (void)hoisted__U32_4193;
                U32 hoisted__U32_4194 = U32_mul(i, hoisted__U32_4193);
                (void)hoisted__U32_4194;
                Type *hoisted__Type_4195 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4195;
                U64 hoisted__U64_4196 = (U64)(hoisted__U32_4194);
                (void)hoisted__U64_4196;
                Type_delete(hoisted__Type_4195, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4196);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4197 = 1;
                (void)hoisted__U32_4197;
                U32 hoisted__U32_4198 = U32_mul(i, hoisted__U32_4197);
                (void)hoisted__U32_4198;
                Type *hoisted__Type_4199 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4199;
                U64 hoisted__U64_4200 = (U64)(hoisted__U32_4198);
                (void)hoisted__U64_4200;
                Type_delete(hoisted__Type_4199, 1);
                U32 hoisted__U32_4201 = 1;
                (void)hoisted__U32_4201;
                Type *hoisted__Type_4202 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4202;
                void *hoisted__v_4203 = ptr_add(new_data, hoisted__U64_4200);
                (void)hoisted__v_4203;
                (void)hoisted__v_4203;
                U64 hoisted__U64_4204 = (U64)(hoisted__U32_4201);
                (void)hoisted__U64_4204;
                Type_delete(hoisted__Type_4202, 1);
                memcpy(hoisted__v_4203, &cloned, hoisted__U64_4204);
                U32 hoisted__U32_4205 = 1;
                (void)hoisted__U32_4205;
                Type *hoisted__Type_4206 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4206;
                I32 hoisted__I32_4207 = 0;
                (void)hoisted__I32_4207;
                U64 hoisted__U64_4208 = (U64)(hoisted__U32_4205);
                (void)hoisted__U64_4208;
                Type_delete(hoisted__Type_4206, 1);
                memset(&cloned, hoisted__I32_4207, hoisted__U64_4208);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4209 = U32_gt(_rc_U32_4191, _re_U32_4191);
                (void)_wcond_Bool_4209;
                if (_wcond_Bool_4209) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4191);
                U32_dec(&_rc_U32_4191);
                U32 hoisted__U32_4210 = 1;
                (void)hoisted__U32_4210;
                U32 hoisted__U32_4211 = U32_mul(i, hoisted__U32_4210);
                (void)hoisted__U32_4211;
                Type *hoisted__Type_4212 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4212;
                U64 hoisted__U64_4213 = (U64)(hoisted__U32_4211);
                (void)hoisted__U64_4213;
                Type_delete(hoisted__Type_4212, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4213);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4214 = 1;
                (void)hoisted__U32_4214;
                U32 hoisted__U32_4215 = U32_mul(i, hoisted__U32_4214);
                (void)hoisted__U32_4215;
                Type *hoisted__Type_4216 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4216;
                U64 hoisted__U64_4217 = (U64)(hoisted__U32_4215);
                (void)hoisted__U64_4217;
                Type_delete(hoisted__Type_4216, 1);
                U32 hoisted__U32_4218 = 1;
                (void)hoisted__U32_4218;
                Type *hoisted__Type_4219 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4219;
                void *hoisted__v_4220 = ptr_add(new_data, hoisted__U64_4217);
                (void)hoisted__v_4220;
                (void)hoisted__v_4220;
                U64 hoisted__U64_4221 = (U64)(hoisted__U32_4218);
                (void)hoisted__U64_4221;
                Type_delete(hoisted__Type_4219, 1);
                memcpy(hoisted__v_4220, &cloned, hoisted__U64_4221);
                U32 hoisted__U32_4222 = 1;
                (void)hoisted__U32_4222;
                Type *hoisted__Type_4223 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4223;
                I32 hoisted__I32_4224 = 0;
                (void)hoisted__I32_4224;
                U64 hoisted__U64_4225 = (U64)(hoisted__U32_4222);
                (void)hoisted__U64_4225;
                Type_delete(hoisted__Type_4223, 1);
                memset(&cloned, hoisted__I32_4224, hoisted__U64_4225);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4231 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4231->data = new_data;
    hoisted__Vec__Bool_4231->count = self->count;
    hoisted__Vec__Bool_4231->cap = self->cap;
    (void)hoisted__Vec__Bool_4231;
    return hoisted__Vec__Bool_4231;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4232 = 16;
    (void)hoisted__U32_4232;
    return hoisted__U32_4232;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_4549 = 104;
    (void)hoisted__U32_4549;
    Type *hoisted__Type_4550 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4550;
    U64 hoisted__U64_4551 = (U64)(hoisted__U32_4549);
    (void)hoisted__U64_4551;
    Type_delete(hoisted__Type_4550, 1);
    void * hoisted__v_4552 = malloc(hoisted__U64_4551);
    (void)hoisted__v_4552;
    U32 hoisted__U32_4553 = 0;
    (void)hoisted__U32_4553;
    I64 hoisted__I64_4554 = 1;
    (void)hoisted__I64_4554;
    Vec__Declaration *hoisted__Vec__Declaration_4555 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4555->data = hoisted__v_4552;
    hoisted__Vec__Declaration_4555->count = hoisted__U32_4553;
    hoisted__Vec__Declaration_4555->cap = hoisted__I64_4554;
    (void)hoisted__Vec__Declaration_4555;
    return hoisted__Vec__Declaration_4555;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4556 = self->count;
        (void)_re_U32_4556;
        U32 _rc_U32_4556 = 0;
        (void)_rc_U32_4556;
        Bool hoisted__Bool_4571 = U32_lte(_rc_U32_4556, _re_U32_4556);
        (void)hoisted__Bool_4571;
        if (hoisted__Bool_4571) {
            while (1) {
                Bool _wcond_Bool_4557 = U32_lt(_rc_U32_4556, _re_U32_4556);
                (void)_wcond_Bool_4557;
                if (_wcond_Bool_4557) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4556);
                U32_inc(&_rc_U32_4556);
                U32 hoisted__U32_4558 = 104;
                (void)hoisted__U32_4558;
                U32 hoisted__U32_4559 = U32_mul(i, hoisted__U32_4558);
                (void)hoisted__U32_4559;
                Type *hoisted__Type_4560 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4560;
                U64 hoisted__U64_4561 = (U64)(hoisted__U32_4559);
                (void)hoisted__U64_4561;
                Type_delete(hoisted__Type_4560, 1);
                Declaration *hoisted__Declaration_4562 = ptr_add(self->data, hoisted__U64_4561);
                (void)hoisted__Declaration_4562;
                (void)hoisted__Declaration_4562;
                Bool hoisted__Bool_4563 = 0;
                (void)hoisted__Bool_4563;
                Declaration_delete(hoisted__Declaration_4562, hoisted__Bool_4563);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4564 = U32_gt(_rc_U32_4556, _re_U32_4556);
                (void)_wcond_Bool_4564;
                if (_wcond_Bool_4564) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4556);
                U32_dec(&_rc_U32_4556);
                U32 hoisted__U32_4565 = 104;
                (void)hoisted__U32_4565;
                U32 hoisted__U32_4566 = U32_mul(i, hoisted__U32_4565);
                (void)hoisted__U32_4566;
                Type *hoisted__Type_4567 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4567;
                U64 hoisted__U64_4568 = (U64)(hoisted__U32_4566);
                (void)hoisted__U64_4568;
                Type_delete(hoisted__Type_4567, 1);
                Declaration *hoisted__Declaration_4569 = ptr_add(self->data, hoisted__U64_4568);
                (void)hoisted__Declaration_4569;
                (void)hoisted__Declaration_4569;
                Bool hoisted__Bool_4570 = 0;
                (void)hoisted__Bool_4570;
                Declaration_delete(hoisted__Declaration_4569, hoisted__Bool_4570);
            }
        }
    }
    U32 hoisted__U32_4572 = 0;
    (void)hoisted__U32_4572;
    self->count = hoisted__U32_4572;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_4859 = 104;
    (void)hoisted__U32_4859;
    U32 hoisted__U32_4860 = U32_mul(self->cap, hoisted__U32_4859);
    (void)hoisted__U32_4860;
    Type *hoisted__Type_4861 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4861;
    U64 hoisted__U64_4862 = (U64)(hoisted__U32_4860);
    (void)hoisted__U64_4862;
    Type_delete(hoisted__Type_4861, 1);
    void * new_data = malloc(hoisted__U64_4862);
    {
        U32 _re_U32_4823 = self->count;
        (void)_re_U32_4823;
        U32 _rc_U32_4823 = 0;
        (void)_rc_U32_4823;
        Bool hoisted__Bool_4858 = U32_lte(_rc_U32_4823, _re_U32_4823);
        (void)hoisted__Bool_4858;
        if (hoisted__Bool_4858) {
            while (1) {
                Bool _wcond_Bool_4824 = U32_lt(_rc_U32_4823, _re_U32_4823);
                (void)_wcond_Bool_4824;
                if (_wcond_Bool_4824) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4823);
                U32_inc(&_rc_U32_4823);
                U32 hoisted__U32_4825 = 104;
                (void)hoisted__U32_4825;
                U32 hoisted__U32_4826 = U32_mul(i, hoisted__U32_4825);
                (void)hoisted__U32_4826;
                Type *hoisted__Type_4827 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4827;
                U64 hoisted__U64_4828 = (U64)(hoisted__U32_4826);
                (void)hoisted__U64_4828;
                Type_delete(hoisted__Type_4827, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_4828);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4829 = 104;
                (void)hoisted__U32_4829;
                U32 hoisted__U32_4830 = U32_mul(i, hoisted__U32_4829);
                (void)hoisted__U32_4830;
                Type *hoisted__Type_4831 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4831;
                U64 hoisted__U64_4832 = (U64)(hoisted__U32_4830);
                (void)hoisted__U64_4832;
                Type_delete(hoisted__Type_4831, 1);
                U32 hoisted__U32_4833 = 104;
                (void)hoisted__U32_4833;
                Type *hoisted__Type_4834 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4834;
                void *hoisted__v_4835 = ptr_add(new_data, hoisted__U64_4832);
                (void)hoisted__v_4835;
                (void)hoisted__v_4835;
                U64 hoisted__U64_4836 = (U64)(hoisted__U32_4833);
                (void)hoisted__U64_4836;
                Type_delete(hoisted__Type_4834, 1);
                memcpy(hoisted__v_4835, cloned, hoisted__U64_4836);
                U32 hoisted__U32_4837 = 104;
                (void)hoisted__U32_4837;
                Type *hoisted__Type_4838 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4838;
                I32 hoisted__I32_4839 = 0;
                (void)hoisted__I32_4839;
                U64 hoisted__U64_4840 = (U64)(hoisted__U32_4837);
                (void)hoisted__U64_4840;
                Type_delete(hoisted__Type_4838, 1);
                memset(cloned, hoisted__I32_4839, hoisted__U64_4840);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4841 = U32_gt(_rc_U32_4823, _re_U32_4823);
                (void)_wcond_Bool_4841;
                if (_wcond_Bool_4841) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4823);
                U32_dec(&_rc_U32_4823);
                U32 hoisted__U32_4842 = 104;
                (void)hoisted__U32_4842;
                U32 hoisted__U32_4843 = U32_mul(i, hoisted__U32_4842);
                (void)hoisted__U32_4843;
                Type *hoisted__Type_4844 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4844;
                U64 hoisted__U64_4845 = (U64)(hoisted__U32_4843);
                (void)hoisted__U64_4845;
                Type_delete(hoisted__Type_4844, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_4845);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4846 = 104;
                (void)hoisted__U32_4846;
                U32 hoisted__U32_4847 = U32_mul(i, hoisted__U32_4846);
                (void)hoisted__U32_4847;
                Type *hoisted__Type_4848 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4848;
                U64 hoisted__U64_4849 = (U64)(hoisted__U32_4847);
                (void)hoisted__U64_4849;
                Type_delete(hoisted__Type_4848, 1);
                U32 hoisted__U32_4850 = 104;
                (void)hoisted__U32_4850;
                Type *hoisted__Type_4851 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4851;
                void *hoisted__v_4852 = ptr_add(new_data, hoisted__U64_4849);
                (void)hoisted__v_4852;
                (void)hoisted__v_4852;
                U64 hoisted__U64_4853 = (U64)(hoisted__U32_4850);
                (void)hoisted__U64_4853;
                Type_delete(hoisted__Type_4851, 1);
                memcpy(hoisted__v_4852, cloned, hoisted__U64_4853);
                U32 hoisted__U32_4854 = 104;
                (void)hoisted__U32_4854;
                Type *hoisted__Type_4855 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4855;
                I32 hoisted__I32_4856 = 0;
                (void)hoisted__I32_4856;
                U64 hoisted__U64_4857 = (U64)(hoisted__U32_4854);
                (void)hoisted__U64_4857;
                Type_delete(hoisted__Type_4855, 1);
                memset(cloned, hoisted__I32_4856, hoisted__U64_4857);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_4863 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4863->data = new_data;
    hoisted__Vec__Declaration_4863->count = self->count;
    hoisted__Vec__Declaration_4863->cap = self->cap;
    (void)hoisted__Vec__Declaration_4863;
    return hoisted__Vec__Declaration_4863;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_4864 = 16;
    (void)hoisted__U32_4864;
    return hoisted__U32_4864;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_4865 = 136;
    (void)hoisted__U32_4865;
    Type *hoisted__Type_4866 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4866;
    U64 hoisted__U64_4867 = (U64)(hoisted__U32_4865);
    (void)hoisted__U64_4867;
    Type_delete(hoisted__Type_4866, 1);
    void * hoisted__v_4868 = malloc(hoisted__U64_4867);
    (void)hoisted__v_4868;
    U32 hoisted__U32_4869 = 0;
    (void)hoisted__U32_4869;
    I64 hoisted__I64_4870 = 1;
    (void)hoisted__I64_4870;
    Vec__Expr *hoisted__Vec__Expr_4871 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4871->data = hoisted__v_4868;
    hoisted__Vec__Expr_4871->count = hoisted__U32_4869;
    hoisted__Vec__Expr_4871->cap = hoisted__I64_4870;
    (void)hoisted__Vec__Expr_4871;
    return hoisted__Vec__Expr_4871;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_4872 = self->count;
        (void)_re_U32_4872;
        U32 _rc_U32_4872 = 0;
        (void)_rc_U32_4872;
        Bool hoisted__Bool_4887 = U32_lte(_rc_U32_4872, _re_U32_4872);
        (void)hoisted__Bool_4887;
        if (hoisted__Bool_4887) {
            while (1) {
                Bool _wcond_Bool_4873 = U32_lt(_rc_U32_4872, _re_U32_4872);
                (void)_wcond_Bool_4873;
                if (_wcond_Bool_4873) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4872);
                U32_inc(&_rc_U32_4872);
                U32 hoisted__U32_4874 = 136;
                (void)hoisted__U32_4874;
                U32 hoisted__U32_4875 = U32_mul(i, hoisted__U32_4874);
                (void)hoisted__U32_4875;
                Type *hoisted__Type_4876 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4876;
                U64 hoisted__U64_4877 = (U64)(hoisted__U32_4875);
                (void)hoisted__U64_4877;
                Type_delete(hoisted__Type_4876, 1);
                Expr *hoisted__Expr_4878 = ptr_add(self->data, hoisted__U64_4877);
                (void)hoisted__Expr_4878;
                (void)hoisted__Expr_4878;
                Bool hoisted__Bool_4879 = 0;
                (void)hoisted__Bool_4879;
                Expr_delete(hoisted__Expr_4878, hoisted__Bool_4879);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4880 = U32_gt(_rc_U32_4872, _re_U32_4872);
                (void)_wcond_Bool_4880;
                if (_wcond_Bool_4880) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4872);
                U32_dec(&_rc_U32_4872);
                U32 hoisted__U32_4881 = 136;
                (void)hoisted__U32_4881;
                U32 hoisted__U32_4882 = U32_mul(i, hoisted__U32_4881);
                (void)hoisted__U32_4882;
                Type *hoisted__Type_4883 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4883;
                U64 hoisted__U64_4884 = (U64)(hoisted__U32_4882);
                (void)hoisted__U64_4884;
                Type_delete(hoisted__Type_4883, 1);
                Expr *hoisted__Expr_4885 = ptr_add(self->data, hoisted__U64_4884);
                (void)hoisted__Expr_4885;
                (void)hoisted__Expr_4885;
                Bool hoisted__Bool_4886 = 0;
                (void)hoisted__Bool_4886;
                Expr_delete(hoisted__Expr_4885, hoisted__Bool_4886);
            }
        }
    }
    U32 hoisted__U32_4888 = 0;
    (void)hoisted__U32_4888;
    self->count = hoisted__U32_4888;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5175 = 136;
    (void)hoisted__U32_5175;
    U32 hoisted__U32_5176 = U32_mul(self->cap, hoisted__U32_5175);
    (void)hoisted__U32_5176;
    Type *hoisted__Type_5177 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5177;
    U64 hoisted__U64_5178 = (U64)(hoisted__U32_5176);
    (void)hoisted__U64_5178;
    Type_delete(hoisted__Type_5177, 1);
    void * new_data = malloc(hoisted__U64_5178);
    {
        U32 _re_U32_5139 = self->count;
        (void)_re_U32_5139;
        U32 _rc_U32_5139 = 0;
        (void)_rc_U32_5139;
        Bool hoisted__Bool_5174 = U32_lte(_rc_U32_5139, _re_U32_5139);
        (void)hoisted__Bool_5174;
        if (hoisted__Bool_5174) {
            while (1) {
                Bool _wcond_Bool_5140 = U32_lt(_rc_U32_5139, _re_U32_5139);
                (void)_wcond_Bool_5140;
                if (_wcond_Bool_5140) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5139);
                U32_inc(&_rc_U32_5139);
                U32 hoisted__U32_5141 = 136;
                (void)hoisted__U32_5141;
                U32 hoisted__U32_5142 = U32_mul(i, hoisted__U32_5141);
                (void)hoisted__U32_5142;
                Type *hoisted__Type_5143 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5143;
                U64 hoisted__U64_5144 = (U64)(hoisted__U32_5142);
                (void)hoisted__U64_5144;
                Type_delete(hoisted__Type_5143, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5144);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5145 = 136;
                (void)hoisted__U32_5145;
                U32 hoisted__U32_5146 = U32_mul(i, hoisted__U32_5145);
                (void)hoisted__U32_5146;
                Type *hoisted__Type_5147 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5147;
                U64 hoisted__U64_5148 = (U64)(hoisted__U32_5146);
                (void)hoisted__U64_5148;
                Type_delete(hoisted__Type_5147, 1);
                U32 hoisted__U32_5149 = 136;
                (void)hoisted__U32_5149;
                Type *hoisted__Type_5150 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5150;
                void *hoisted__v_5151 = ptr_add(new_data, hoisted__U64_5148);
                (void)hoisted__v_5151;
                (void)hoisted__v_5151;
                U64 hoisted__U64_5152 = (U64)(hoisted__U32_5149);
                (void)hoisted__U64_5152;
                Type_delete(hoisted__Type_5150, 1);
                memcpy(hoisted__v_5151, cloned, hoisted__U64_5152);
                U32 hoisted__U32_5153 = 136;
                (void)hoisted__U32_5153;
                Type *hoisted__Type_5154 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5154;
                I32 hoisted__I32_5155 = 0;
                (void)hoisted__I32_5155;
                U64 hoisted__U64_5156 = (U64)(hoisted__U32_5153);
                (void)hoisted__U64_5156;
                Type_delete(hoisted__Type_5154, 1);
                memset(cloned, hoisted__I32_5155, hoisted__U64_5156);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5157 = U32_gt(_rc_U32_5139, _re_U32_5139);
                (void)_wcond_Bool_5157;
                if (_wcond_Bool_5157) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5139);
                U32_dec(&_rc_U32_5139);
                U32 hoisted__U32_5158 = 136;
                (void)hoisted__U32_5158;
                U32 hoisted__U32_5159 = U32_mul(i, hoisted__U32_5158);
                (void)hoisted__U32_5159;
                Type *hoisted__Type_5160 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5160;
                U64 hoisted__U64_5161 = (U64)(hoisted__U32_5159);
                (void)hoisted__U64_5161;
                Type_delete(hoisted__Type_5160, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5161);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5162 = 136;
                (void)hoisted__U32_5162;
                U32 hoisted__U32_5163 = U32_mul(i, hoisted__U32_5162);
                (void)hoisted__U32_5163;
                Type *hoisted__Type_5164 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5164;
                U64 hoisted__U64_5165 = (U64)(hoisted__U32_5163);
                (void)hoisted__U64_5165;
                Type_delete(hoisted__Type_5164, 1);
                U32 hoisted__U32_5166 = 136;
                (void)hoisted__U32_5166;
                Type *hoisted__Type_5167 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5167;
                void *hoisted__v_5168 = ptr_add(new_data, hoisted__U64_5165);
                (void)hoisted__v_5168;
                (void)hoisted__v_5168;
                U64 hoisted__U64_5169 = (U64)(hoisted__U32_5166);
                (void)hoisted__U64_5169;
                Type_delete(hoisted__Type_5167, 1);
                memcpy(hoisted__v_5168, cloned, hoisted__U64_5169);
                U32 hoisted__U32_5170 = 136;
                (void)hoisted__U32_5170;
                Type *hoisted__Type_5171 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5171;
                I32 hoisted__I32_5172 = 0;
                (void)hoisted__I32_5172;
                U64 hoisted__U64_5173 = (U64)(hoisted__U32_5170);
                (void)hoisted__U64_5173;
                Type_delete(hoisted__Type_5171, 1);
                memset(cloned, hoisted__I32_5172, hoisted__U64_5173);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5179 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5179->data = new_data;
    hoisted__Vec__Expr_5179->count = self->count;
    hoisted__Vec__Expr_5179->cap = self->cap;
    (void)hoisted__Vec__Expr_5179;
    return hoisted__Vec__Expr_5179;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5180 = 16;
    (void)hoisted__U32_5180;
    return hoisted__U32_5180;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5181 = 8;
    (void)hoisted__U32_5181;
    Type *hoisted__Type_5182 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5182;
    U64 hoisted__U64_5183 = (U64)(hoisted__U32_5181);
    (void)hoisted__U64_5183;
    Type_delete(hoisted__Type_5182, 1);
    void * hoisted__v_5184 = malloc(hoisted__U64_5183);
    (void)hoisted__v_5184;
    U32 hoisted__U32_5185 = 0;
    (void)hoisted__U32_5185;
    I64 hoisted__I64_5186 = 1;
    (void)hoisted__I64_5186;
    Vec__I64 *hoisted__Vec__I64_5187 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5187->data = hoisted__v_5184;
    hoisted__Vec__I64_5187->count = hoisted__U32_5185;
    hoisted__Vec__I64_5187->cap = hoisted__I64_5186;
    (void)hoisted__Vec__I64_5187;
    return hoisted__Vec__I64_5187;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5188 = self->count;
        (void)_re_U32_5188;
        U32 _rc_U32_5188 = 0;
        (void)_rc_U32_5188;
        Bool hoisted__Bool_5203 = U32_lte(_rc_U32_5188, _re_U32_5188);
        (void)hoisted__Bool_5203;
        if (hoisted__Bool_5203) {
            while (1) {
                Bool _wcond_Bool_5189 = U32_lt(_rc_U32_5188, _re_U32_5188);
                (void)_wcond_Bool_5189;
                if (_wcond_Bool_5189) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5188);
                U32_inc(&_rc_U32_5188);
                U32 hoisted__U32_5190 = 8;
                (void)hoisted__U32_5190;
                U32 hoisted__U32_5191 = U32_mul(i, hoisted__U32_5190);
                (void)hoisted__U32_5191;
                Type *hoisted__Type_5192 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5192;
                U64 hoisted__U64_5193 = (U64)(hoisted__U32_5191);
                (void)hoisted__U64_5193;
                Type_delete(hoisted__Type_5192, 1);
                I64 *hoisted__I64_5194 = ptr_add(self->data, hoisted__U64_5193);
                (void)hoisted__I64_5194;
                (void)hoisted__I64_5194;
                Bool hoisted__Bool_5195 = 0;
                (void)hoisted__Bool_5195;
                I64_delete(hoisted__I64_5194, hoisted__Bool_5195);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5196 = U32_gt(_rc_U32_5188, _re_U32_5188);
                (void)_wcond_Bool_5196;
                if (_wcond_Bool_5196) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5188);
                U32_dec(&_rc_U32_5188);
                U32 hoisted__U32_5197 = 8;
                (void)hoisted__U32_5197;
                U32 hoisted__U32_5198 = U32_mul(i, hoisted__U32_5197);
                (void)hoisted__U32_5198;
                Type *hoisted__Type_5199 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5199;
                U64 hoisted__U64_5200 = (U64)(hoisted__U32_5198);
                (void)hoisted__U64_5200;
                Type_delete(hoisted__Type_5199, 1);
                I64 *hoisted__I64_5201 = ptr_add(self->data, hoisted__U64_5200);
                (void)hoisted__I64_5201;
                (void)hoisted__I64_5201;
                Bool hoisted__Bool_5202 = 0;
                (void)hoisted__Bool_5202;
                I64_delete(hoisted__I64_5201, hoisted__Bool_5202);
            }
        }
    }
    U32 hoisted__U32_5204 = 0;
    (void)hoisted__U32_5204;
    self->count = hoisted__U32_5204;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5491 = 8;
    (void)hoisted__U32_5491;
    U32 hoisted__U32_5492 = U32_mul(self->cap, hoisted__U32_5491);
    (void)hoisted__U32_5492;
    Type *hoisted__Type_5493 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5493;
    U64 hoisted__U64_5494 = (U64)(hoisted__U32_5492);
    (void)hoisted__U64_5494;
    Type_delete(hoisted__Type_5493, 1);
    void * new_data = malloc(hoisted__U64_5494);
    {
        U32 _re_U32_5455 = self->count;
        (void)_re_U32_5455;
        U32 _rc_U32_5455 = 0;
        (void)_rc_U32_5455;
        Bool hoisted__Bool_5490 = U32_lte(_rc_U32_5455, _re_U32_5455);
        (void)hoisted__Bool_5490;
        if (hoisted__Bool_5490) {
            while (1) {
                Bool _wcond_Bool_5456 = U32_lt(_rc_U32_5455, _re_U32_5455);
                (void)_wcond_Bool_5456;
                if (_wcond_Bool_5456) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5455);
                U32_inc(&_rc_U32_5455);
                U32 hoisted__U32_5457 = 8;
                (void)hoisted__U32_5457;
                U32 hoisted__U32_5458 = U32_mul(i, hoisted__U32_5457);
                (void)hoisted__U32_5458;
                Type *hoisted__Type_5459 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5459;
                U64 hoisted__U64_5460 = (U64)(hoisted__U32_5458);
                (void)hoisted__U64_5460;
                Type_delete(hoisted__Type_5459, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5460);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5461 = 8;
                (void)hoisted__U32_5461;
                U32 hoisted__U32_5462 = U32_mul(i, hoisted__U32_5461);
                (void)hoisted__U32_5462;
                Type *hoisted__Type_5463 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5463;
                U64 hoisted__U64_5464 = (U64)(hoisted__U32_5462);
                (void)hoisted__U64_5464;
                Type_delete(hoisted__Type_5463, 1);
                U32 hoisted__U32_5465 = 8;
                (void)hoisted__U32_5465;
                Type *hoisted__Type_5466 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5466;
                void *hoisted__v_5467 = ptr_add(new_data, hoisted__U64_5464);
                (void)hoisted__v_5467;
                (void)hoisted__v_5467;
                U64 hoisted__U64_5468 = (U64)(hoisted__U32_5465);
                (void)hoisted__U64_5468;
                Type_delete(hoisted__Type_5466, 1);
                memcpy(hoisted__v_5467, &cloned, hoisted__U64_5468);
                U32 hoisted__U32_5469 = 8;
                (void)hoisted__U32_5469;
                Type *hoisted__Type_5470 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5470;
                I32 hoisted__I32_5471 = 0;
                (void)hoisted__I32_5471;
                U64 hoisted__U64_5472 = (U64)(hoisted__U32_5469);
                (void)hoisted__U64_5472;
                Type_delete(hoisted__Type_5470, 1);
                memset(&cloned, hoisted__I32_5471, hoisted__U64_5472);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5473 = U32_gt(_rc_U32_5455, _re_U32_5455);
                (void)_wcond_Bool_5473;
                if (_wcond_Bool_5473) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5455);
                U32_dec(&_rc_U32_5455);
                U32 hoisted__U32_5474 = 8;
                (void)hoisted__U32_5474;
                U32 hoisted__U32_5475 = U32_mul(i, hoisted__U32_5474);
                (void)hoisted__U32_5475;
                Type *hoisted__Type_5476 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5476;
                U64 hoisted__U64_5477 = (U64)(hoisted__U32_5475);
                (void)hoisted__U64_5477;
                Type_delete(hoisted__Type_5476, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5477);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5478 = 8;
                (void)hoisted__U32_5478;
                U32 hoisted__U32_5479 = U32_mul(i, hoisted__U32_5478);
                (void)hoisted__U32_5479;
                Type *hoisted__Type_5480 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5480;
                U64 hoisted__U64_5481 = (U64)(hoisted__U32_5479);
                (void)hoisted__U64_5481;
                Type_delete(hoisted__Type_5480, 1);
                U32 hoisted__U32_5482 = 8;
                (void)hoisted__U32_5482;
                Type *hoisted__Type_5483 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5483;
                void *hoisted__v_5484 = ptr_add(new_data, hoisted__U64_5481);
                (void)hoisted__v_5484;
                (void)hoisted__v_5484;
                U64 hoisted__U64_5485 = (U64)(hoisted__U32_5482);
                (void)hoisted__U64_5485;
                Type_delete(hoisted__Type_5483, 1);
                memcpy(hoisted__v_5484, &cloned, hoisted__U64_5485);
                U32 hoisted__U32_5486 = 8;
                (void)hoisted__U32_5486;
                Type *hoisted__Type_5487 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5487;
                I32 hoisted__I32_5488 = 0;
                (void)hoisted__I32_5488;
                U64 hoisted__U64_5489 = (U64)(hoisted__U32_5486);
                (void)hoisted__U64_5489;
                Type_delete(hoisted__Type_5487, 1);
                memset(&cloned, hoisted__I32_5488, hoisted__U64_5489);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5495 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5495->data = new_data;
    hoisted__Vec__I64_5495->count = self->count;
    hoisted__Vec__I64_5495->cap = self->cap;
    (void)hoisted__Vec__I64_5495;
    return hoisted__Vec__I64_5495;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5496 = 16;
    (void)hoisted__U32_5496;
    return hoisted__U32_5496;
}

void panic(Str * loc_str, Array__Str * parts) {
    U32 hoisted__U32_6571 = 3;
    (void)hoisted__U32_6571;
    Array__Str *_va_Array_177 = Array__Str_new(hoisted__U32_6571);
    (void)_va_Array_177;
    U32 hoisted__U32_6572 = 0;
    (void)hoisted__U32_6572;
    Str *hoisted__Str_6573 = Str_clone(loc_str);
    (void)hoisted__Str_6573;
    Array__Str_set(_va_Array_177, hoisted__U32_6572, hoisted__Str_6573);
    U32 hoisted__U32_6574 = 1;
    (void)hoisted__U32_6574;
    Str hoisted__Str_6575 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6575;
    Array__Str_set(_va_Array_177, hoisted__U32_6574, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6575; _oa; }));
    Array__Str *hoisted__Array__Str_6576 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6576;
    U32 hoisted__U32_6577 = 2;
    (void)hoisted__U32_6577;
    Str *hoisted__Str_6578 = format(hoisted__Array__Str_6576);
    (void)hoisted__Str_6578;
    Array__Str_set(_va_Array_177, hoisted__U32_6577, hoisted__Str_6578);
    Array__Str_delete(parts, 1);
    println(_va_Array_177);
    I64 hoisted__I64_6579 = 1;
    (void)hoisted__I64_6579;
    exit(hoisted__I64_6579);
}

void UNREACHABLE(Str * loc_str) {
    U32 hoisted__U32_6586 = 1;
    (void)hoisted__U32_6586;
    Array__Str *_va_Array_179 = Array__Str_new(hoisted__U32_6586);
    (void)_va_Array_179;
    U32 hoisted__U32_6587 = 0;
    (void)hoisted__U32_6587;
    Str hoisted__Str_6588 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6588;
    Array__Str_set(_va_Array_179, hoisted__U32_6587, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6588; _oa; }));
    panic(loc_str, _va_Array_179);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_6592 = not(cond);
    (void)hoisted__Bool_6592;
    if (hoisted__Bool_6592) {
        U32 hoisted__U32_6589 = 1;
        (void)hoisted__U32_6589;
        Array__Str *_va_Array_180 = Array__Str_new(hoisted__U32_6589);
        (void)_va_Array_180;
        U32 hoisted__U32_6590 = 0;
        (void)hoisted__U32_6590;
        Str hoisted__Str_6591 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6591;
        Array__Str_set(_va_Array_180, hoisted__U32_6590, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6591; _oa; }));
        panic(loc_str, _va_Array_180);
    }
    Bool hoisted__Bool_6593 = 1;
    (void)hoisted__Bool_6593;
    return hoisted__Bool_6593;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_6612 = I64_neq(a, b);
    (void)hoisted__Bool_6612;
    if (hoisted__Bool_6612) {
        U32 hoisted__U32_6601 = 5;
        (void)hoisted__U32_6601;
        Array__Str *_va_Array_182 = Array__Str_new(hoisted__U32_6601);
        (void)_va_Array_182;
        U32 hoisted__U32_6602 = 0;
        (void)hoisted__U32_6602;
        Str hoisted__Str_6603 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6603;
        Array__Str_set(_va_Array_182, hoisted__U32_6602, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6603; _oa; }));
        U32 hoisted__U32_6604 = 1;
        (void)hoisted__U32_6604;
        Str *hoisted__Str_6605 = I64_to_str(a);
        (void)hoisted__Str_6605;
        Array__Str_set(_va_Array_182, hoisted__U32_6604, hoisted__Str_6605);
        U32 hoisted__U32_6606 = 2;
        (void)hoisted__U32_6606;
        Str hoisted__Str_6607 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6607;
        Array__Str_set(_va_Array_182, hoisted__U32_6606, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6607; _oa; }));
        U32 hoisted__U32_6608 = 3;
        (void)hoisted__U32_6608;
        Str *hoisted__Str_6609 = I64_to_str(b);
        (void)hoisted__Str_6609;
        Array__Str_set(_va_Array_182, hoisted__U32_6608, hoisted__Str_6609);
        U32 hoisted__U32_6610 = 4;
        (void)hoisted__U32_6610;
        Str hoisted__Str_6611 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6611;
        Array__Str_set(_va_Array_182, hoisted__U32_6610, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6611; _oa; }));
        panic(loc_str, _va_Array_182);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_6624 = Str_eq(a, b);
    (void)hoisted__Bool_6624;
    Bool hoisted__Bool_6625 = not(hoisted__Bool_6624);
    (void)hoisted__Bool_6625;
    if (hoisted__Bool_6625) {
        U32 hoisted__U32_6613 = 5;
        (void)hoisted__U32_6613;
        Array__Str *_va_Array_183 = Array__Str_new(hoisted__U32_6613);
        (void)_va_Array_183;
        U32 hoisted__U32_6614 = 0;
        (void)hoisted__U32_6614;
        Str hoisted__Str_6615 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6615;
        Array__Str_set(_va_Array_183, hoisted__U32_6614, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6615; _oa; }));
        U32 hoisted__U32_6616 = 1;
        (void)hoisted__U32_6616;
        Str *hoisted__Str_6617 = Str_clone(a);
        (void)hoisted__Str_6617;
        Array__Str_set(_va_Array_183, hoisted__U32_6616, hoisted__Str_6617);
        U32 hoisted__U32_6618 = 2;
        (void)hoisted__U32_6618;
        Str hoisted__Str_6619 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6619;
        Array__Str_set(_va_Array_183, hoisted__U32_6618, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6619; _oa; }));
        U32 hoisted__U32_6620 = 3;
        (void)hoisted__U32_6620;
        Str *hoisted__Str_6621 = Str_clone(b);
        (void)hoisted__Str_6621;
        Array__Str_set(_va_Array_183, hoisted__U32_6620, hoisted__Str_6621);
        U32 hoisted__U32_6622 = 4;
        (void)hoisted__U32_6622;
        Str hoisted__Str_6623 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6623;
        Array__Str_set(_va_Array_183, hoisted__U32_6622, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6623; _oa; }));
        panic(loc_str, _va_Array_183);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6626 = parts;
        (void)_fc_Array__Str_6626;
        (void)_fc_Array__Str_6626;
        U32 _fi_USize_6626 = 0;
        (void)_fi_USize_6626;
        I64 _forin_err_kind_6626 = 0;
        (void)_forin_err_kind_6626;
        OutOfBounds *_forin_OutOfBounds_6626 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_6626->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_6626;
        while (1) {
            U32 hoisted__U32_6632 = Array__Str_len(_fc_Array__Str_6626);
            (void)hoisted__U32_6632;
            Bool _wcond_Bool_6627 = U32_lt(_fi_USize_6626, hoisted__U32_6632);
            (void)_wcond_Bool_6627;
            if (_wcond_Bool_6627) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_6626, &_fi_USize_6626, &_forin_err_kind_6626, _forin_OutOfBounds_6626);
            I64 hoisted__I64_6633 = 0;
            (void)hoisted__I64_6633;
            Bool hoisted__Bool_6634 = I64_eq(_forin_err_kind_6626, hoisted__I64_6633);
            (void)hoisted__Bool_6634;
            Bool hoisted__Bool_6635 = not(hoisted__Bool_6634);
            (void)hoisted__Bool_6635;
            if (hoisted__Bool_6635) {
                U32 hoisted__U32_6628 = 1;
                (void)hoisted__U32_6628;
                Array__Str *_va_Array_184 = Array__Str_new(hoisted__U32_6628);
                (void)_va_Array_184;
                U32 hoisted__U32_6629 = 0;
                (void)hoisted__U32_6629;
                Str hoisted__Str_6630 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6630;
                Array__Str_set(_va_Array_184, hoisted__U32_6629, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6630; _oa; }));
                Str hoisted__Str_6631 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6631;
                panic(&hoisted__Str_6631, _va_Array_184);
                Str_delete(&hoisted__Str_6631, (Bool){0});
            }
            U32 hoisted__U32_6636 = 1;
            (void)hoisted__U32_6636;
            U32 hoisted__U32_6637 = U32_add(_fi_USize_6626, hoisted__U32_6636);
            (void)hoisted__U32_6637;
            _fi_USize_6626 = hoisted__U32_6637;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_6626, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_6675 = ptr_eq(p, NULL);
    (void)hoisted__Bool_6675;
    return hoisted__Bool_6675;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6684 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6684;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6684;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6685 = 0;
    (void)hoisted__U32_6685;
    U64 hoisted__U64_6686 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6685); });
    (void)hoisted__U64_6686;
    return hoisted__U64_6686;
}

U32 Range_size(void) {
    U32 hoisted__U32_6687 = 16;
    (void)hoisted__U32_6687;
    return hoisted__U32_6687;
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_6793 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6793;
    I64 hoisted__I64_6794 = 3;
    (void)hoisted__I64_6794;
    assert_eq(&hoisted__Str_6793, result, hoisted__I64_6794);
    Str_delete(&hoisted__Str_6793, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_6801 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6801;
    I64 hoisted__I64_6802 = 15;
    (void)hoisted__I64_6802;
    assert_eq(&hoisted__Str_6801, result, hoisted__I64_6802);
    Str_delete(&hoisted__Str_6801, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_6809 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6809;
    I64 hoisted__I64_6810 = 26;
    (void)hoisted__I64_6810;
    assert_eq(&hoisted__Str_6809, result, hoisted__I64_6810);
    Str_delete(&hoisted__Str_6809, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_6813 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6813;
    Str hoisted__Str_6814 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6814;
    assert_eq_str(&hoisted__Str_6813, &result, &hoisted__Str_6814);
    Str_delete(&hoisted__Str_6813, (Bool){0});
    Str_delete(&hoisted__Str_6814, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7145 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7145;
    assert_eq_str(&hoisted__Str_7145, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_7145, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_7146 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7146;
    assert_eq_str(&hoisted__Str_7146, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_7146, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_7148 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7148;
    I64 hoisted__I64_7149 = 8;
    (void)hoisted__I64_7149;
    assert_eq(&hoisted__Str_7148, result, hoisted__I64_7149);
    Str_delete(&hoisted__Str_7148, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_7152 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7152;
    Bool hoisted__Bool_7153 = 1;
    (void)hoisted__Bool_7153;
    assert(&hoisted__Str_7152, hoisted__Bool_7153);
    Str_delete(&hoisted__Str_7152, (Bool){0});
    Str hoisted__Str_7156 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7156;
    Bool hoisted__Bool_7157 = 1;
    (void)hoisted__Bool_7157;
    assert(&hoisted__Str_7156, hoisted__Bool_7157);
    Str_delete(&hoisted__Str_7156, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_7162 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7162;
    Str hoisted__Str_7163 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7163;
    Str hoisted__Str_7164 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7164;
    assert_eq_str(&hoisted__Str_7162, &hoisted__Str_7163, &hoisted__Str_7164);
    Str_delete(&hoisted__Str_7162, (Bool){0});
    Str_delete(&hoisted__Str_7163, (Bool){0});
    Str_delete(&hoisted__Str_7164, (Bool){0});
    Str hoisted__Str_7167 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7167;
    Str hoisted__Str_7168 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7168;
    Str hoisted__Str_7169 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7169;
    assert_eq_str(&hoisted__Str_7167, &hoisted__Str_7168, &hoisted__Str_7169);
    Str_delete(&hoisted__Str_7167, (Bool){0});
    Str_delete(&hoisted__Str_7168, (Bool){0});
    Str_delete(&hoisted__Str_7169, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7174 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7174;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7174;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7175 = 0;
    (void)hoisted__U32_7175;
    U64 hoisted__U64_7176 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7175); });
    (void)hoisted__U64_7176;
    return hoisted__U64_7176;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_7177 = 16;
    (void)hoisted__U32_7177;
    return hoisted__U32_7177;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_7178 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7178;
    I64 hoisted__I64_7179 = 42;
    (void)hoisted__I64_7179;
    assert_eq(&hoisted__Str_7178, v.x, hoisted__I64_7179);
    Str_delete(&hoisted__Str_7178, (Bool){0});
    Str hoisted__Str_7180 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7180;
    I64 hoisted__I64_7181 = 99;
    (void)hoisted__I64_7181;
    assert_eq(&hoisted__Str_7180, v.y, hoisted__I64_7181);
    Str_delete(&hoisted__Str_7180, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_7184 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7184;
    I64 hoisted__I64_7185 = 10;
    (void)hoisted__I64_7185;
    assert_eq(&hoisted__Str_7184, p.x, hoisted__I64_7185);
    Str_delete(&hoisted__Str_7184, (Bool){0});
    Str hoisted__Str_7186 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7186;
    I64 hoisted__I64_7187 = 20;
    (void)hoisted__I64_7187;
    assert_eq(&hoisted__Str_7186, p.y, hoisted__I64_7187);
    Str_delete(&hoisted__Str_7186, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7193 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7193;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7193;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7194 = 0;
    (void)hoisted__U32_7194;
    U64 hoisted__U64_7195 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7194); });
    (void)hoisted__U64_7195;
    return hoisted__U64_7195;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_7196 = 32;
    (void)hoisted__U32_7196;
    return hoisted__U32_7196;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_7197 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7197;
    I64 hoisted__I64_7198 = 5;
    (void)hoisted__I64_7198;
    assert_eq(&hoisted__Str_7197, r.top_left.x, hoisted__I64_7198);
    Str_delete(&hoisted__Str_7197, (Bool){0});
    Str hoisted__Str_7199 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7199;
    I64 hoisted__I64_7200 = 10;
    (void)hoisted__I64_7200;
    assert_eq(&hoisted__Str_7199, r.top_left.y, hoisted__I64_7200);
    Str_delete(&hoisted__Str_7199, (Bool){0});
    Str hoisted__Str_7201 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7201;
    I64 hoisted__I64_7202 = 100;
    (void)hoisted__I64_7202;
    assert_eq(&hoisted__Str_7201, r.bottom_right.x, hoisted__I64_7202);
    Str_delete(&hoisted__Str_7201, (Bool){0});
    Str hoisted__Str_7203 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7203;
    I64 hoisted__I64_7204 = 200;
    (void)hoisted__I64_7204;
    assert_eq(&hoisted__Str_7203, r.bottom_right.y, hoisted__I64_7204);
    Str_delete(&hoisted__Str_7203, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7206 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7206;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7206;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7207 = 0;
    (void)hoisted__U32_7207;
    U64 hoisted__U64_7208 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7207); });
    (void)hoisted__U64_7208;
    return hoisted__U64_7208;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_7209 = 12;
    (void)hoisted__U32_7209;
    return hoisted__U32_7209;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_7213 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7213;
    Str *hoisted__Str_7214 = F32_to_str(v.x);
    (void)hoisted__Str_7214;
    Str hoisted__Str_7215 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7215;
    assert_eq_str(&hoisted__Str_7213, hoisted__Str_7214, &hoisted__Str_7215);
    Str_delete(&hoisted__Str_7213, (Bool){0});
    Str_delete(hoisted__Str_7214, 1);
    Str_delete(&hoisted__Str_7215, (Bool){0});
    Str hoisted__Str_7216 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7216;
    Str *hoisted__Str_7217 = F32_to_str(v.y);
    (void)hoisted__Str_7217;
    Str hoisted__Str_7218 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7218;
    assert_eq_str(&hoisted__Str_7216, hoisted__Str_7217, &hoisted__Str_7218);
    Str_delete(&hoisted__Str_7216, (Bool){0});
    Str_delete(hoisted__Str_7217, 1);
    Str_delete(&hoisted__Str_7218, (Bool){0});
    Str hoisted__Str_7219 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7219;
    Str *hoisted__Str_7220 = F32_to_str(v.z);
    (void)hoisted__Str_7220;
    Str hoisted__Str_7221 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7221;
    assert_eq_str(&hoisted__Str_7219, hoisted__Str_7220, &hoisted__Str_7221);
    Str_delete(&hoisted__Str_7219, (Bool){0});
    Str_delete(hoisted__Str_7220, 1);
    Str_delete(&hoisted__Str_7221, (Bool){0});
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
    Bool hoisted__Bool_7226 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7226;
    if (hoisted__Bool_7226) {
        Bool hoisted__Bool_7223 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_7223;
        { Bool _ret_val = hoisted__Bool_7223;
                return _ret_val; }
    }
    Bool hoisted__Bool_7227 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7227;
    if (hoisted__Bool_7227) {
        Bool hoisted__Bool_7224 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_7224;
        { Bool _ret_val = hoisted__Bool_7224;
                return _ret_val; }
    }
    Bool hoisted__Bool_7228 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7228;
    if (hoisted__Bool_7228) {
        Bool hoisted__Bool_7225 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_7225;
        { Bool _ret_val = hoisted__Bool_7225;
                return _ret_val; }
    }
    Bool hoisted__Bool_7229 = 0;
    (void)hoisted__Bool_7229;
    return hoisted__Bool_7229;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7237 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7237;
    if (hoisted__Bool_7237) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_7238 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7238;
    if (hoisted__Bool_7238) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_7239 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7239;
    if (hoisted__Bool_7239) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_7240 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7240;
    UNREACHABLE(&hoisted__Str_7240);
    Str_delete(&hoisted__Str_7240, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_7241 = 4;
    (void)hoisted__U32_7241;
    return hoisted__U32_7241;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_7242 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7242;
    Bool hoisted__Bool_7243 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7243;
    assert(&hoisted__Str_7242, hoisted__Bool_7243);
    Str_delete(&hoisted__Str_7242, (Bool){0});
    Bool hoisted__Bool_7244 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7244;
    Str hoisted__Str_7245 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7245;
    Bool hoisted__Bool_7246 = not(hoisted__Bool_7244);
    (void)hoisted__Bool_7246;
    assert(&hoisted__Str_7245, hoisted__Bool_7246);
    Str_delete(&hoisted__Str_7245, (Bool){0});
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
    Bool hoisted__Bool_7247 = is(self, other);
    (void)hoisted__Bool_7247;
    return hoisted__Bool_7247;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7265 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7265;
    if (hoisted__Bool_7265) {
        I64 *hoisted__I64_7261 = get_payload(self);
        (void)hoisted__I64_7261;
        (void)hoisted__I64_7261;
        Bool hoisted__Bool_7262 = 0;
        (void)hoisted__Bool_7262;
        I64_delete(hoisted__I64_7261, hoisted__Bool_7262);
    }
    Bool hoisted__Bool_7266 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7266;
    if (hoisted__Bool_7266) {
        Str *hoisted__Str_7263 = get_payload(self);
        (void)hoisted__Str_7263;
        (void)hoisted__Str_7263;
        Bool hoisted__Bool_7264 = 0;
        (void)hoisted__Bool_7264;
        Str_delete(hoisted__Str_7263, hoisted__Bool_7264);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_7291 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7291;
    if (hoisted__Bool_7291) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7288 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7288;
        { Token * _ret_val = hoisted__Token_7288;
                return _ret_val; }
    }
    Bool hoisted__Bool_7292 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7292;
    if (hoisted__Bool_7292) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7289 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7289;
        Token *hoisted__Token_7290 = Token_Name(hoisted__Str_7289);
        (void)hoisted__Token_7290;
        { Token * _ret_val = hoisted__Token_7290;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_7293 = 24;
    (void)hoisted__U32_7293;
    return hoisted__U32_7293;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_7295 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7295;
    Bool hoisted__Bool_7296 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7296;
    assert(&hoisted__Str_7295, hoisted__Bool_7296);
    Str_delete(&hoisted__Str_7295, (Bool){0});
    Bool hoisted__Bool_7297 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7297;
    Str hoisted__Str_7298 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7298;
    Bool hoisted__Bool_7299 = not(hoisted__Bool_7297);
    (void)hoisted__Bool_7299;
    assert(&hoisted__Str_7298, hoisted__Bool_7299);
    Str_delete(&hoisted__Str_7298, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_7300 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7300;
    Bool hoisted__Bool_7301 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7301;
    assert(&hoisted__Str_7300, hoisted__Bool_7301);
    Str_delete(&hoisted__Str_7300, (Bool){0});
    Bool hoisted__Bool_7302 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7302;
    Str hoisted__Str_7303 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7303;
    Bool hoisted__Bool_7304 = not(hoisted__Bool_7302);
    (void)hoisted__Bool_7304;
    assert(&hoisted__Str_7303, hoisted__Bool_7304);
    Str_delete(&hoisted__Str_7303, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_7307 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7307;
    Bool hoisted__Bool_7308 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7308;
    assert(&hoisted__Str_7307, hoisted__Bool_7308);
    Str_delete(&hoisted__Str_7307, (Bool){0});
    Bool hoisted__Bool_7309 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7309;
    Str hoisted__Str_7310 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7310;
    Bool hoisted__Bool_7311 = not(hoisted__Bool_7309);
    (void)hoisted__Bool_7311;
    assert(&hoisted__Str_7310, hoisted__Bool_7311);
    Str_delete(&hoisted__Str_7310, (Bool){0});
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 12LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 13LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 14LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 15LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 16LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 17LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 18LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 19LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 20LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 21LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 22LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 23LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 24LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 25LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 12LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 13LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 14LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 15LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 16LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 17LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 18LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 19LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 20LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 21LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 22LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 23LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 24LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 25LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    CAP_STATIC = 4294967293;
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
