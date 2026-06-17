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
    NodeType_TAG_CallerLoc
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
void Array__Str_set_init(Array__Str * self, U32 i, Str * val);
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
void assert_eq__I64(Str * loc_str, I64 a, I64 b);
void assert_eq__Str(Str * loc_str, Str * a, Str * b);
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
void Array__Str_set_init(Array__Str * self, U32 i, Str * val);
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
void assert_eq__I64(Str * loc_str, I64 a, I64 b);
void assert_eq__Str(Str * loc_str, Str * a, Str * b);
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
NodeType *NodeType_CallerLoc();
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
        Array__Str *_fc_Array__Str_666 = parts;
        (void)_fc_Array__Str_666;
        (void)_fc_Array__Str_666;
        U32 _fi_USize_666 = 0;
        (void)_fi_USize_666;
        I64 _forin_err_kind_666 = 0;
        (void)_forin_err_kind_666;
        OutOfBounds *_forin_OutOfBounds_666 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_666->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_666;
        while (1) {
            U32 hoisted__U32_672 = Array__Str_len(_fc_Array__Str_666);
            (void)hoisted__U32_672;
            Bool _wcond_Bool_667 = U32_lt(_fi_USize_666, hoisted__U32_672);
            (void)_wcond_Bool_667;
            if (_wcond_Bool_667) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_666, &_fi_USize_666, &_forin_err_kind_666, _forin_OutOfBounds_666);
            I64 hoisted__I64_673 = 0;
            (void)hoisted__I64_673;
            Bool hoisted__Bool_674 = I64_eq(_forin_err_kind_666, hoisted__I64_673);
            (void)hoisted__Bool_674;
            Bool hoisted__Bool_675 = not(hoisted__Bool_674);
            (void)hoisted__Bool_675;
            if (hoisted__Bool_675) {
                U32 hoisted__U32_668 = 1;
                (void)hoisted__U32_668;
                Array__Str *_va_Array_17 = Array__Str_new(hoisted__U32_668);
                (void)_va_Array_17;
                U32 hoisted__U32_669 = 0;
                (void)hoisted__U32_669;
                Str hoisted__Str_670 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_670;
                Array__Str_set_init(_va_Array_17, hoisted__U32_669, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_670; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
                Str hoisted__Str_671 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_671;
                panic(&hoisted__Str_671, _va_Array_17);
                Str_delete(&hoisted__Str_671, (Bool){0});
            }
            U32 hoisted__U32_676 = 1;
            (void)hoisted__U32_676;
            U32 hoisted__U32_677 = U32_add(_fi_USize_666, hoisted__U32_676);
            (void)hoisted__U32_677;
            _fi_USize_666 = hoisted__U32_677;
            U32 hoisted__U32_678 = Str_len(s);
            (void)hoisted__U32_678;
            U32 hoisted__U32_679 = U32_add(total, hoisted__U32_678);
            (void)hoisted__U32_679;
            total = hoisted__U32_679;
        }
        OutOfBounds_delete(_forin_OutOfBounds_666, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_680 = parts;
        (void)_fc_Array__Str_680;
        (void)_fc_Array__Str_680;
        U32 _fi_USize_680 = 0;
        (void)_fi_USize_680;
        I64 _forin_err_kind_680 = 0;
        (void)_forin_err_kind_680;
        OutOfBounds *_forin_OutOfBounds_680 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_680->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_680;
        while (1) {
            U32 hoisted__U32_686 = Array__Str_len(_fc_Array__Str_680);
            (void)hoisted__U32_686;
            Bool _wcond_Bool_681 = U32_lt(_fi_USize_680, hoisted__U32_686);
            (void)_wcond_Bool_681;
            if (_wcond_Bool_681) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_680, &_fi_USize_680, &_forin_err_kind_680, _forin_OutOfBounds_680);
            I64 hoisted__I64_687 = 0;
            (void)hoisted__I64_687;
            Bool hoisted__Bool_688 = I64_eq(_forin_err_kind_680, hoisted__I64_687);
            (void)hoisted__Bool_688;
            Bool hoisted__Bool_689 = not(hoisted__Bool_688);
            (void)hoisted__Bool_689;
            if (hoisted__Bool_689) {
                U32 hoisted__U32_682 = 1;
                (void)hoisted__U32_682;
                Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_682);
                (void)_va_Array_18;
                U32 hoisted__U32_683 = 0;
                (void)hoisted__U32_683;
                Str hoisted__Str_684 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_684;
                Array__Str_set_init(_va_Array_18, hoisted__U32_683, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_684; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
                Str hoisted__Str_685 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_685;
                panic(&hoisted__Str_685, _va_Array_18);
                Str_delete(&hoisted__Str_685, (Bool){0});
            }
            U32 hoisted__U32_690 = 1;
            (void)hoisted__U32_690;
            U32 hoisted__U32_691 = U32_add(_fi_USize_680, hoisted__U32_690);
            (void)hoisted__U32_691;
            _fi_USize_680 = hoisted__U32_691;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_680, 1);
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_696 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_696;
    if (hoisted__Bool_696) {
        U32 hoisted__U32_692 = 1;
        (void)hoisted__U32_692;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_692);
        (void)_va_Array_19;
        U32 hoisted__U32_693 = 0;
        (void)hoisted__U32_693;
        Str hoisted__Str_694 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_694;
        Array__Str_set_init(_va_Array_19, hoisted__U32_693, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_694; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_695 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_695;
        panic(&hoisted__Str_695, _va_Array_19);
        Str_delete(&hoisted__Str_695, (Bool){0});
    }
    void *hoisted__v_697 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_697;
    (void)hoisted__v_697;
    return hoisted__v_697;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_707 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_707;
    if (hoisted__Bool_707) {
        min_len = b->count;
    }
    {
        U32 _re_U32_699 = U32_clone(&min_len);
        (void)_re_U32_699;
        U32 _rc_U32_699 = 0;
        (void)_rc_U32_699;
        Bool hoisted__Bool_706 = U32_lte(_rc_U32_699, _re_U32_699);
        (void)hoisted__Bool_706;
        if (hoisted__Bool_706) {
            while (1) {
                Bool _wcond_Bool_700 = U32_lt(_rc_U32_699, _re_U32_699);
                (void)_wcond_Bool_700;
                if (_wcond_Bool_700) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_699);
                U32_inc(&_rc_U32_699);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_701 = 0;
                (void)hoisted__I64_701;
                Bool hoisted__Bool_702 = I64_neq(c, hoisted__I64_701);
                (void)hoisted__Bool_702;
                if (hoisted__Bool_702) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_703 = U32_gt(_rc_U32_699, _re_U32_699);
                (void)_wcond_Bool_703;
                if (_wcond_Bool_703) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_699);
                U32_dec(&_rc_U32_699);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_704 = 0;
                (void)hoisted__I64_704;
                Bool hoisted__Bool_705 = I64_neq(c, hoisted__I64_704);
                (void)hoisted__Bool_705;
                if (hoisted__Bool_705) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_708 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_708;
    return hoisted__I64_708;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_710 = 1;
    (void)hoisted__U32_710;
    U32 hoisted__U64_711 = U32_add(n, hoisted__U32_710);
    (void)hoisted__U64_711;
    void * buf = malloc(hoisted__U64_711);
    I32 hoisted__I32_712 = 0;
    (void)hoisted__I32_712;
    U64 hoisted__U64_713 = 1ULL;
    (void)hoisted__U64_713;
    memset(buf, hoisted__I32_712, hoisted__U64_713);
    I64 hoisted__I64_714 = 0;
    (void)hoisted__I64_714;
    Str *hoisted__Str_715 = malloc(sizeof(Str));
    hoisted__Str_715->c_str = buf;
    hoisted__Str_715->count = hoisted__I64_714;
    hoisted__Str_715->cap = n;
    (void)hoisted__Str_715;
    return hoisted__Str_715;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_726 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_726;
    if (hoisted__Bool_726) {
        U32 hoisted__U32_718 = 1;
        (void)hoisted__U32_718;
        Array__Str *_va_Array_20 = Array__Str_new(hoisted__U32_718);
        (void)_va_Array_20;
        U32 hoisted__U32_719 = 0;
        (void)hoisted__U32_719;
        Str hoisted__Str_720 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_720;
        Array__Str_set_init(_va_Array_20, hoisted__U32_719, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_720; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_721 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_721;
        panic(&hoisted__Str_721, _va_Array_20);
        Str_delete(&hoisted__Str_721, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_727 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_727;
    if (hoisted__Bool_727) {
        U32 hoisted__U32_722 = 1;
        (void)hoisted__U32_722;
        Array__Str *_va_Array_21 = Array__Str_new(hoisted__U32_722);
        (void)_va_Array_21;
        U32 hoisted__U32_723 = 0;
        (void)hoisted__U32_723;
        Str hoisted__Str_724 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_724;
        Array__Str_set_init(_va_Array_21, hoisted__U32_723, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_724; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_725 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_725;
        panic(&hoisted__Str_725, _va_Array_21);
        Str_delete(&hoisted__Str_725, (Bool){0});
    }
    void *hoisted__v_728 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_728;
    (void)hoisted__v_728;
    memcpy(hoisted__v_728, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_729 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_729;
    (void)hoisted__v_729;
    I32 hoisted__I32_730 = 0;
    (void)hoisted__I32_730;
    U64 hoisted__U64_731 = 1ULL;
    (void)hoisted__U64_731;
    memset(hoisted__v_729, hoisted__I32_730, hoisted__U64_731);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_732 = 1;
    (void)hoisted__U32_732;
    U32 hoisted__U64_733 = U32_add(val->count, hoisted__U32_732);
    (void)hoisted__U64_733;
    void * new_data = malloc(hoisted__U64_733);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_734 = ptr_add(new_data, val->count);
    (void)hoisted__v_734;
    (void)hoisted__v_734;
    I32 hoisted__I32_735 = 0;
    (void)hoisted__I32_735;
    U64 hoisted__U64_736 = 1ULL;
    (void)hoisted__U64_736;
    memset(hoisted__v_734, hoisted__I32_735, hoisted__U64_736);
    Str *hoisted__Str_737 = malloc(sizeof(Str));
    hoisted__Str_737->c_str = new_data;
    hoisted__Str_737->count = val->count;
    hoisted__Str_737->cap = val->count;
    (void)hoisted__Str_737;
    return hoisted__Str_737;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_738 = Str_clone(self);
    (void)hoisted__Str_738;
    return hoisted__Str_738;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_739 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_739;
    if (hoisted__Bool_739) {
        free(self->c_str);
    }
    Bool hoisted__Bool_740 = U32_neq(self->cap, CAP_LIT);
    (void)hoisted__Bool_740;
    Bool hoisted__Bool_741 = and(call_free, hoisted__Bool_740);
    (void)hoisted__Bool_741;
    if (hoisted__Bool_741) {
        free(self);
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_936 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_936;
    return hoisted__U64_936;
}

U32 Str_size(void) {
    U32 hoisted__U32_1107 = 16;
    (void)hoisted__U32_1107;
    return hoisted__U32_1107;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1108 = Str_cmp(a, b);
    (void)hoisted__I64_1108;
    I64 hoisted__I64_1109 = 0;
    (void)hoisted__I64_1109;
    Bool hoisted__Bool_1110 = I64_eq(hoisted__I64_1108, hoisted__I64_1109);
    (void)hoisted__Bool_1110;
    return hoisted__Bool_1110;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1119 = Str_eq(a, b);
    (void)hoisted__Bool_1119;
    Bool hoisted__Bool_1120 = not(hoisted__Bool_1119);
    (void)hoisted__Bool_1120;
    return hoisted__Bool_1120;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1209 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1209->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1209;
    return hoisted__OutOfBounds_1209;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1210 = 0;
    (void)hoisted__Bool_1210;
    Str_delete(&self->msg, hoisted__Bool_1210);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1211 = 0;
    (void)hoisted__U32_1211;
    U64 hoisted__U64_1212 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1211); });
    (void)hoisted__U64_1212;
    return hoisted__U64_1212;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1227 = 16;
    (void)hoisted__U32_1227;
    return hoisted__U32_1227;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1247 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1247;
    U32 hoisted__U32_1248 = 16;
    (void)hoisted__U32_1248;
    Type *hoisted__Type_1249 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1249;
    U64 hoisted__U64_1250 = (U64)(cap);
    (void)hoisted__U64_1250;
    Type_delete(hoisted__Type_1247, 1);
    U64 hoisted__U64_1251 = (U64)(hoisted__U32_1248);
    (void)hoisted__U64_1251;
    Type_delete(hoisted__Type_1249, 1);
    void * hoisted__v_1252 = calloc(hoisted__U64_1250, hoisted__U64_1251);
    (void)hoisted__v_1252;
    Array__Str *hoisted__Array__Str_1253 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1253->data = hoisted__v_1252;
    hoisted__Array__Str_1253->cap = cap;
    (void)hoisted__Array__Str_1253;
    return hoisted__Array__Str_1253;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1275 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1275;
    if (hoisted__Bool_1275) {
        U32 hoisted__U32_1254 = 6;
        (void)hoisted__U32_1254;
        Array__Str *_va_Array_33 = Array__Str_new(hoisted__U32_1254);
        (void)_va_Array_33;
        U32 hoisted__U32_1255 = 0;
        (void)hoisted__U32_1255;
        Str hoisted__Str_1256 = (Str){.c_str = (void *)"./src/core/array.til:28:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1256;
        Array__Str_set_init(_va_Array_33, hoisted__U32_1255, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1256; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1257 = 1;
        (void)hoisted__U32_1257;
        Str hoisted__Str_1258 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1258;
        Array__Str_set_init(_va_Array_33, hoisted__U32_1257, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1258; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1259 = 2;
        (void)hoisted__U32_1259;
        Str *hoisted__Str_1260 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1260;
        Array__Str_set_init(_va_Array_33, hoisted__U32_1259, hoisted__Str_1260);
        U32 hoisted__U32_1261 = 3;
        (void)hoisted__U32_1261;
        Str hoisted__Str_1262 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1262;
        Array__Str_set_init(_va_Array_33, hoisted__U32_1261, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1262; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1263 = 4;
        (void)hoisted__U32_1263;
        Str *hoisted__Str_1264 = U32_to_str(self->cap);
        (void)hoisted__Str_1264;
        Array__Str_set_init(_va_Array_33, hoisted__U32_1263, hoisted__Str_1264);
        U32 hoisted__U32_1265 = 5;
        (void)hoisted__U32_1265;
        Str hoisted__Str_1266 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1266;
        Array__Str_set_init(_va_Array_33, hoisted__U32_1265, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1266; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_1267 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_33); hoisted__OutOfBounds_1267->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1267;
        U32 hoisted__U32_1268 = 16;
        (void)hoisted__U32_1268;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1267, hoisted__U32_1268);
        OutOfBounds_delete(hoisted__OutOfBounds_1267, 1);
        I64 hoisted__I64_1269 = 3;
        (void)hoisted__I64_1269;
        *_err_kind = hoisted__I64_1269;
    }
    I64 hoisted__I64_1276 = 0;
    (void)hoisted__I64_1276;
    Bool hoisted__Bool_1277 = I64_eq(DEREF(_err_kind), hoisted__I64_1276);
    (void)hoisted__Bool_1277;
    if (hoisted__Bool_1277) {
        U32 hoisted__U32_1270 = 16;
        (void)hoisted__U32_1270;
        U32 hoisted__U32_1271 = U32_mul(DEREF(i), hoisted__U32_1270);
        (void)hoisted__U32_1271;
        Type *hoisted__Type_1272 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1272;
        U64 hoisted__U64_1273 = (U64)(hoisted__U32_1271);
        (void)hoisted__U64_1273;
        Type_delete(hoisted__Type_1272, 1);
        void *hoisted__v_1274 = ptr_add(self->data, hoisted__U64_1273);
        (void)hoisted__v_1274;
        (void)hoisted__v_1274;
        { Str * _ret_val = hoisted__v_1274;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set_init(Array__Str * self, U32 i, Str * val) {
    Bool hoisted__Bool_1331 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1331;
    if (hoisted__Bool_1331) {
        U32 hoisted__U32_1319 = 5;
        (void)hoisted__U32_1319;
        Array__Str *_va_Array_35 = Array__Str_new(hoisted__U32_1319);
        (void)_va_Array_35;
        U32 hoisted__U32_1320 = 0;
        (void)hoisted__U32_1320;
        Str hoisted__Str_1321 = (Str){.c_str = (void *)"Array.set_init: index ", .count = 22ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1321;
        Array__Str_set_init(_va_Array_35, hoisted__U32_1320, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1321; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1322 = 1;
        (void)hoisted__U32_1322;
        Str *hoisted__Str_1323 = U32_to_str(i);
        (void)hoisted__Str_1323;
        Array__Str_set_init(_va_Array_35, hoisted__U32_1322, hoisted__Str_1323);
        U32 hoisted__U32_1324 = 2;
        (void)hoisted__U32_1324;
        Str hoisted__Str_1325 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1325;
        Array__Str_set_init(_va_Array_35, hoisted__U32_1324, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1325; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_1326 = 3;
        (void)hoisted__U32_1326;
        Str *hoisted__Str_1327 = U32_to_str(self->cap);
        (void)hoisted__Str_1327;
        Array__Str_set_init(_va_Array_35, hoisted__U32_1326, hoisted__Str_1327);
        U32 hoisted__U32_1328 = 4;
        (void)hoisted__U32_1328;
        Str hoisted__Str_1329 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1329;
        Array__Str_set_init(_va_Array_35, hoisted__U32_1328, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1329; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        Str hoisted__Str_1330 = (Str){.c_str = (void *)"./src/core/array.til:58:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1330;
        panic(&hoisted__Str_1330, _va_Array_35);
        Str_delete(&hoisted__Str_1330, (Bool){0});
    }
    U32 hoisted__U32_1332 = 16;
    (void)hoisted__U32_1332;
    U32 hoisted__U32_1333 = U32_mul(i, hoisted__U32_1332);
    (void)hoisted__U32_1333;
    Type *hoisted__Type_1334 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1334;
    U64 hoisted__U64_1335 = (U64)(hoisted__U32_1333);
    (void)hoisted__U64_1335;
    Type_delete(hoisted__Type_1334, 1);
    Str *hoisted__Str_1336 = ptr_add(self->data, hoisted__U64_1335);
    (void)hoisted__Str_1336;
    (void)hoisted__Str_1336;
    Bool hoisted__Bool_1337 = 0;
    (void)hoisted__Bool_1337;
    Str_delete(hoisted__Str_1336, hoisted__Bool_1337);
    U32 hoisted__U32_1338 = 16;
    (void)hoisted__U32_1338;
    U32 hoisted__U32_1339 = U32_mul(i, hoisted__U32_1338);
    (void)hoisted__U32_1339;
    Type *hoisted__Type_1340 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1340;
    U64 hoisted__U64_1341 = (U64)(hoisted__U32_1339);
    (void)hoisted__U64_1341;
    Type_delete(hoisted__Type_1340, 1);
    U32 hoisted__U32_1342 = 16;
    (void)hoisted__U32_1342;
    Type *hoisted__Type_1343 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1343;
    void *hoisted__v_1344 = ptr_add(self->data, hoisted__U64_1341);
    (void)hoisted__v_1344;
    (void)hoisted__v_1344;
    U64 hoisted__U64_1345 = (U64)(hoisted__U32_1342);
    (void)hoisted__U64_1345;
    Type_delete(hoisted__Type_1343, 1);
    memcpy(hoisted__v_1344, val, hoisted__U64_1345);
    U32 hoisted__U32_1346 = 16;
    (void)hoisted__U32_1346;
    Type *hoisted__Type_1347 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1347;
    I32 hoisted__I32_1348 = 0;
    (void)hoisted__I32_1348;
    U64 hoisted__U64_1349 = (U64)(hoisted__U32_1346);
    (void)hoisted__U64_1349;
    Type_delete(hoisted__Type_1347, 1);
    memset(val, hoisted__I32_1348, hoisted__U64_1349);
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1350 = self->cap;
        (void)_re_U32_1350;
        U32 _rc_U32_1350 = 0;
        (void)_rc_U32_1350;
        Bool hoisted__Bool_1365 = U32_lte(_rc_U32_1350, _re_U32_1350);
        (void)hoisted__Bool_1365;
        if (hoisted__Bool_1365) {
            while (1) {
                Bool _wcond_Bool_1351 = U32_lt(_rc_U32_1350, _re_U32_1350);
                (void)_wcond_Bool_1351;
                if (_wcond_Bool_1351) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1350);
                U32_inc(&_rc_U32_1350);
                U32 hoisted__U32_1352 = 16;
                (void)hoisted__U32_1352;
                U32 hoisted__U32_1353 = U32_mul(i, hoisted__U32_1352);
                (void)hoisted__U32_1353;
                Type *hoisted__Type_1354 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1354;
                U64 hoisted__U64_1355 = (U64)(hoisted__U32_1353);
                (void)hoisted__U64_1355;
                Type_delete(hoisted__Type_1354, 1);
                Str *hoisted__Str_1356 = ptr_add(self->data, hoisted__U64_1355);
                (void)hoisted__Str_1356;
                (void)hoisted__Str_1356;
                Bool hoisted__Bool_1357 = 0;
                (void)hoisted__Bool_1357;
                Str_delete(hoisted__Str_1356, hoisted__Bool_1357);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1358 = U32_gt(_rc_U32_1350, _re_U32_1350);
                (void)_wcond_Bool_1358;
                if (_wcond_Bool_1358) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1350);
                U32_dec(&_rc_U32_1350);
                U32 hoisted__U32_1359 = 16;
                (void)hoisted__U32_1359;
                U32 hoisted__U32_1360 = U32_mul(i, hoisted__U32_1359);
                (void)hoisted__U32_1360;
                Type *hoisted__Type_1361 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1361;
                U64 hoisted__U64_1362 = (U64)(hoisted__U32_1360);
                (void)hoisted__U64_1362;
                Type_delete(hoisted__Type_1361, 1);
                Str *hoisted__Str_1363 = ptr_add(self->data, hoisted__U64_1362);
                (void)hoisted__Str_1363;
                (void)hoisted__Str_1363;
                Bool hoisted__Bool_1364 = 0;
                (void)hoisted__Bool_1364;
                Str_delete(hoisted__Str_1363, hoisted__Bool_1364);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1402 = 16;
    (void)hoisted__U32_1402;
    U32 hoisted__U32_1403 = U32_mul(self->cap, hoisted__U32_1402);
    (void)hoisted__U32_1403;
    Type *hoisted__Type_1404 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1404;
    U64 hoisted__U64_1405 = (U64)(hoisted__U32_1403);
    (void)hoisted__U64_1405;
    Type_delete(hoisted__Type_1404, 1);
    void * new_data = malloc(hoisted__U64_1405);
    {
        U32 _re_U32_1366 = self->cap;
        (void)_re_U32_1366;
        U32 _rc_U32_1366 = 0;
        (void)_rc_U32_1366;
        Bool hoisted__Bool_1401 = U32_lte(_rc_U32_1366, _re_U32_1366);
        (void)hoisted__Bool_1401;
        if (hoisted__Bool_1401) {
            while (1) {
                Bool _wcond_Bool_1367 = U32_lt(_rc_U32_1366, _re_U32_1366);
                (void)_wcond_Bool_1367;
                if (_wcond_Bool_1367) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1366);
                U32_inc(&_rc_U32_1366);
                U32 hoisted__U32_1368 = 16;
                (void)hoisted__U32_1368;
                U32 hoisted__U32_1369 = U32_mul(i, hoisted__U32_1368);
                (void)hoisted__U32_1369;
                Type *hoisted__Type_1370 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1370;
                U64 hoisted__U64_1371 = (U64)(hoisted__U32_1369);
                (void)hoisted__U64_1371;
                Type_delete(hoisted__Type_1370, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1371);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1372 = 16;
                (void)hoisted__U32_1372;
                U32 hoisted__U32_1373 = U32_mul(i, hoisted__U32_1372);
                (void)hoisted__U32_1373;
                Type *hoisted__Type_1374 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1374;
                U64 hoisted__U64_1375 = (U64)(hoisted__U32_1373);
                (void)hoisted__U64_1375;
                Type_delete(hoisted__Type_1374, 1);
                U32 hoisted__U32_1376 = 16;
                (void)hoisted__U32_1376;
                Type *hoisted__Type_1377 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1377;
                void *hoisted__v_1378 = ptr_add(new_data, hoisted__U64_1375);
                (void)hoisted__v_1378;
                (void)hoisted__v_1378;
                U64 hoisted__U64_1379 = (U64)(hoisted__U32_1376);
                (void)hoisted__U64_1379;
                Type_delete(hoisted__Type_1377, 1);
                memcpy(hoisted__v_1378, cloned, hoisted__U64_1379);
                U32 hoisted__U32_1380 = 16;
                (void)hoisted__U32_1380;
                Type *hoisted__Type_1381 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1381;
                I32 hoisted__I32_1382 = 0;
                (void)hoisted__I32_1382;
                U64 hoisted__U64_1383 = (U64)(hoisted__U32_1380);
                (void)hoisted__U64_1383;
                Type_delete(hoisted__Type_1381, 1);
                memset(cloned, hoisted__I32_1382, hoisted__U64_1383);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1384 = U32_gt(_rc_U32_1366, _re_U32_1366);
                (void)_wcond_Bool_1384;
                if (_wcond_Bool_1384) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1366);
                U32_dec(&_rc_U32_1366);
                U32 hoisted__U32_1385 = 16;
                (void)hoisted__U32_1385;
                U32 hoisted__U32_1386 = U32_mul(i, hoisted__U32_1385);
                (void)hoisted__U32_1386;
                Type *hoisted__Type_1387 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1387;
                U64 hoisted__U64_1388 = (U64)(hoisted__U32_1386);
                (void)hoisted__U64_1388;
                Type_delete(hoisted__Type_1387, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1388);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1389 = 16;
                (void)hoisted__U32_1389;
                U32 hoisted__U32_1390 = U32_mul(i, hoisted__U32_1389);
                (void)hoisted__U32_1390;
                Type *hoisted__Type_1391 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1391;
                U64 hoisted__U64_1392 = (U64)(hoisted__U32_1390);
                (void)hoisted__U64_1392;
                Type_delete(hoisted__Type_1391, 1);
                U32 hoisted__U32_1393 = 16;
                (void)hoisted__U32_1393;
                Type *hoisted__Type_1394 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1394;
                void *hoisted__v_1395 = ptr_add(new_data, hoisted__U64_1392);
                (void)hoisted__v_1395;
                (void)hoisted__v_1395;
                U64 hoisted__U64_1396 = (U64)(hoisted__U32_1393);
                (void)hoisted__U64_1396;
                Type_delete(hoisted__Type_1394, 1);
                memcpy(hoisted__v_1395, cloned, hoisted__U64_1396);
                U32 hoisted__U32_1397 = 16;
                (void)hoisted__U32_1397;
                Type *hoisted__Type_1398 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1398;
                I32 hoisted__I32_1399 = 0;
                (void)hoisted__I32_1399;
                U64 hoisted__U64_1400 = (U64)(hoisted__U32_1397);
                (void)hoisted__U64_1400;
                Type_delete(hoisted__Type_1398, 1);
                memset(cloned, hoisted__I32_1399, hoisted__U64_1400);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1406 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1406->data = new_data;
    hoisted__Array__Str_1406->cap = self->cap;
    (void)hoisted__Array__Str_1406;
    return hoisted__Array__Str_1406;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1407 = 16;
    (void)hoisted__U32_1407;
    return hoisted__U32_1407;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1408 = 16;
    (void)hoisted__U32_1408;
    Type *hoisted__Type_1409 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1409;
    U64 hoisted__U64_1410 = (U64)(hoisted__U32_1408);
    (void)hoisted__U64_1410;
    Type_delete(hoisted__Type_1409, 1);
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
        Bool hoisted__Bool_1430 = U32_lte(_rc_U32_1415, _re_U32_1415);
        (void)hoisted__Bool_1430;
        if (hoisted__Bool_1430) {
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
                Type *hoisted__Type_1419 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1419;
                U64 hoisted__U64_1420 = (U64)(hoisted__U32_1418);
                (void)hoisted__U64_1420;
                Type_delete(hoisted__Type_1419, 1);
                Str *hoisted__Str_1421 = ptr_add(self->data, hoisted__U64_1420);
                (void)hoisted__Str_1421;
                (void)hoisted__Str_1421;
                Bool hoisted__Bool_1422 = 0;
                (void)hoisted__Bool_1422;
                Str_delete(hoisted__Str_1421, hoisted__Bool_1422);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1423 = U32_gt(_rc_U32_1415, _re_U32_1415);
                (void)_wcond_Bool_1423;
                if (_wcond_Bool_1423) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1415);
                U32_dec(&_rc_U32_1415);
                U32 hoisted__U32_1424 = 16;
                (void)hoisted__U32_1424;
                U32 hoisted__U32_1425 = U32_mul(i, hoisted__U32_1424);
                (void)hoisted__U32_1425;
                Type *hoisted__Type_1426 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1426;
                U64 hoisted__U64_1427 = (U64)(hoisted__U32_1425);
                (void)hoisted__U64_1427;
                Type_delete(hoisted__Type_1426, 1);
                Str *hoisted__Str_1428 = ptr_add(self->data, hoisted__U64_1427);
                (void)hoisted__Str_1428;
                (void)hoisted__Str_1428;
                Bool hoisted__Bool_1429 = 0;
                (void)hoisted__Bool_1429;
                Str_delete(hoisted__Str_1428, hoisted__Bool_1429);
            }
        }
    }
    U32 hoisted__U32_1431 = 0;
    (void)hoisted__U32_1431;
    self->count = hoisted__U32_1431;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1728 = 16;
    (void)hoisted__U32_1728;
    U32 hoisted__U32_1729 = U32_mul(self->cap, hoisted__U32_1728);
    (void)hoisted__U32_1729;
    Type *hoisted__Type_1730 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1730;
    U64 hoisted__U64_1731 = (U64)(hoisted__U32_1729);
    (void)hoisted__U64_1731;
    Type_delete(hoisted__Type_1730, 1);
    void * new_data = malloc(hoisted__U64_1731);
    {
        U32 _re_U32_1692 = self->count;
        (void)_re_U32_1692;
        U32 _rc_U32_1692 = 0;
        (void)_rc_U32_1692;
        Bool hoisted__Bool_1727 = U32_lte(_rc_U32_1692, _re_U32_1692);
        (void)hoisted__Bool_1727;
        if (hoisted__Bool_1727) {
            while (1) {
                Bool _wcond_Bool_1693 = U32_lt(_rc_U32_1692, _re_U32_1692);
                (void)_wcond_Bool_1693;
                if (_wcond_Bool_1693) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1692);
                U32_inc(&_rc_U32_1692);
                U32 hoisted__U32_1694 = 16;
                (void)hoisted__U32_1694;
                U32 hoisted__U32_1695 = U32_mul(i, hoisted__U32_1694);
                (void)hoisted__U32_1695;
                Type *hoisted__Type_1696 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1696;
                U64 hoisted__U64_1697 = (U64)(hoisted__U32_1695);
                (void)hoisted__U64_1697;
                Type_delete(hoisted__Type_1696, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1697);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1698 = 16;
                (void)hoisted__U32_1698;
                U32 hoisted__U32_1699 = U32_mul(i, hoisted__U32_1698);
                (void)hoisted__U32_1699;
                Type *hoisted__Type_1700 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1700;
                U64 hoisted__U64_1701 = (U64)(hoisted__U32_1699);
                (void)hoisted__U64_1701;
                Type_delete(hoisted__Type_1700, 1);
                U32 hoisted__U32_1702 = 16;
                (void)hoisted__U32_1702;
                Type *hoisted__Type_1703 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1703;
                void *hoisted__v_1704 = ptr_add(new_data, hoisted__U64_1701);
                (void)hoisted__v_1704;
                (void)hoisted__v_1704;
                U64 hoisted__U64_1705 = (U64)(hoisted__U32_1702);
                (void)hoisted__U64_1705;
                Type_delete(hoisted__Type_1703, 1);
                memcpy(hoisted__v_1704, cloned, hoisted__U64_1705);
                U32 hoisted__U32_1706 = 16;
                (void)hoisted__U32_1706;
                Type *hoisted__Type_1707 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1707;
                I32 hoisted__I32_1708 = 0;
                (void)hoisted__I32_1708;
                U64 hoisted__U64_1709 = (U64)(hoisted__U32_1706);
                (void)hoisted__U64_1709;
                Type_delete(hoisted__Type_1707, 1);
                memset(cloned, hoisted__I32_1708, hoisted__U64_1709);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1710 = U32_gt(_rc_U32_1692, _re_U32_1692);
                (void)_wcond_Bool_1710;
                if (_wcond_Bool_1710) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1692);
                U32_dec(&_rc_U32_1692);
                U32 hoisted__U32_1711 = 16;
                (void)hoisted__U32_1711;
                U32 hoisted__U32_1712 = U32_mul(i, hoisted__U32_1711);
                (void)hoisted__U32_1712;
                Type *hoisted__Type_1713 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1713;
                U64 hoisted__U64_1714 = (U64)(hoisted__U32_1712);
                (void)hoisted__U64_1714;
                Type_delete(hoisted__Type_1713, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1714);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1715 = 16;
                (void)hoisted__U32_1715;
                U32 hoisted__U32_1716 = U32_mul(i, hoisted__U32_1715);
                (void)hoisted__U32_1716;
                Type *hoisted__Type_1717 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1717;
                U64 hoisted__U64_1718 = (U64)(hoisted__U32_1716);
                (void)hoisted__U64_1718;
                Type_delete(hoisted__Type_1717, 1);
                U32 hoisted__U32_1719 = 16;
                (void)hoisted__U32_1719;
                Type *hoisted__Type_1720 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1720;
                void *hoisted__v_1721 = ptr_add(new_data, hoisted__U64_1718);
                (void)hoisted__v_1721;
                (void)hoisted__v_1721;
                U64 hoisted__U64_1722 = (U64)(hoisted__U32_1719);
                (void)hoisted__U64_1722;
                Type_delete(hoisted__Type_1720, 1);
                memcpy(hoisted__v_1721, cloned, hoisted__U64_1722);
                U32 hoisted__U32_1723 = 16;
                (void)hoisted__U32_1723;
                Type *hoisted__Type_1724 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1724;
                I32 hoisted__I32_1725 = 0;
                (void)hoisted__I32_1725;
                U64 hoisted__U64_1726 = (U64)(hoisted__U32_1723);
                (void)hoisted__U64_1726;
                Type_delete(hoisted__Type_1724, 1);
                memset(cloned, hoisted__I32_1725, hoisted__U64_1726);
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1732 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1732->data = new_data;
    hoisted__Vec__Str_1732->count = self->count;
    hoisted__Vec__Str_1732->cap = self->cap;
    (void)hoisted__Vec__Str_1732;
    return hoisted__Vec__Str_1732;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1733 = 16;
    (void)hoisted__U32_1733;
    return hoisted__U32_1733;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1736 = 8;
    (void)hoisted__U32_1736;
    return hoisted__U32_1736;
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
    I64 hoisted__I64_1925 = 0;
    (void)hoisted__I64_1925;
    Bool hoisted__Bool_1926 = I64_eq(val, hoisted__I64_1925);
    (void)hoisted__Bool_1926;
    if (hoisted__Bool_1926) {
        U64 hoisted__U64_1895 = 2ULL;
        (void)hoisted__U64_1895;
        void * buf = malloc(hoisted__U64_1895);
        I64 hoisted__I64_1896 = 48;
        (void)hoisted__I64_1896;
        U64 hoisted__U64_1897 = 1ULL;
        (void)hoisted__U64_1897;
        memcpy(buf, &hoisted__I64_1896, hoisted__U64_1897);
        U64 hoisted__U64_1898 = 1ULL;
        (void)hoisted__U64_1898;
        void *hoisted__v_1899 = ptr_add(buf, hoisted__U64_1898);
        (void)hoisted__v_1899;
        (void)hoisted__v_1899;
        I32 hoisted__I32_1900 = 0;
        (void)hoisted__I32_1900;
        U64 hoisted__U64_1901 = 1ULL;
        (void)hoisted__U64_1901;
        memset(hoisted__v_1899, hoisted__I32_1900, hoisted__U64_1901);
        I64 hoisted__I64_1902 = 1;
        (void)hoisted__I64_1902;
        I64 hoisted__I64_1903 = 1;
        (void)hoisted__I64_1903;
        Str *hoisted__Str_1904 = malloc(sizeof(Str));
        hoisted__Str_1904->c_str = buf;
        hoisted__Str_1904->count = hoisted__I64_1902;
        hoisted__Str_1904->cap = hoisted__I64_1903;
        (void)hoisted__Str_1904;
        { Str * _ret_val = hoisted__Str_1904;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1927 = 0;
    (void)hoisted__I64_1927;
    Bool hoisted__Bool_1928 = I64_lt(val, hoisted__I64_1927);
    (void)hoisted__Bool_1928;
    if (hoisted__Bool_1928) {
        Bool hoisted__Bool_1905 = 1;
        (void)hoisted__Bool_1905;
        is_neg = hoisted__Bool_1905;
        I64 hoisted__I64_1906 = 0;
        (void)hoisted__I64_1906;
        I64 hoisted__I64_1907 = I64_sub(hoisted__I64_1906, val);
        (void)hoisted__I64_1907;
        v = hoisted__I64_1907;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1909 = 0;
        (void)hoisted__I64_1909;
        Bool _wcond_Bool_1908 = I64_gt(tmp, hoisted__I64_1909);
        (void)_wcond_Bool_1908;
        if (_wcond_Bool_1908) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1910 = 10;
        (void)hoisted__I64_1910;
        I64 hoisted__I64_1911 = I64_div(tmp, hoisted__I64_1910);
        (void)hoisted__I64_1911;
        tmp = hoisted__I64_1911;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1929 = 1ULL;
    (void)hoisted__U64_1929;
    U64 hoisted__U64_1930 = U64_add(total, hoisted__U64_1929);
    (void)hoisted__U64_1930;
    void * buf = malloc(hoisted__U64_1930);
    if (is_neg) {
        I64 hoisted__I64_1912 = 45;
        (void)hoisted__I64_1912;
        U64 hoisted__U64_1913 = 1ULL;
        (void)hoisted__U64_1913;
        memcpy(buf, &hoisted__I64_1912, hoisted__U64_1913);
    }
    U64 hoisted__U64_1931 = 1ULL;
    (void)hoisted__U64_1931;
    U64 i = U64_sub(total, hoisted__U64_1931);
    while (1) {
        I64 hoisted__I64_1915 = 0;
        (void)hoisted__I64_1915;
        Bool _wcond_Bool_1914 = I64_gt(v, hoisted__I64_1915);
        (void)_wcond_Bool_1914;
        if (_wcond_Bool_1914) {
        } else {
            break;
        }
        I64 hoisted__I64_1916 = 10;
        (void)hoisted__I64_1916;
        I64 hoisted__I64_1917 = I64_mod(v, hoisted__I64_1916);
        (void)hoisted__I64_1917;
        I64 hoisted__I64_1918 = 48;
        (void)hoisted__I64_1918;
        I64 hoisted__I64_1919 = I64_add(hoisted__I64_1917, hoisted__I64_1918);
        (void)hoisted__I64_1919;
        void *hoisted__v_1920 = ptr_add(buf, i);
        (void)hoisted__v_1920;
        (void)hoisted__v_1920;
        U8 hoisted__U8_1921 = I64_to_u8(hoisted__I64_1919);
        (void)hoisted__U8_1921;
        U64 hoisted__U64_1922 = 1ULL;
        (void)hoisted__U64_1922;
        memcpy(hoisted__v_1920, &hoisted__U8_1921, hoisted__U64_1922);
        I64 hoisted__I64_1923 = 10;
        (void)hoisted__I64_1923;
        I64 hoisted__I64_1924 = I64_div(v, hoisted__I64_1923);
        (void)hoisted__I64_1924;
        v = hoisted__I64_1924;
        U64_dec(&i);
    }
    void *hoisted__v_1932 = ptr_add(buf, total);
    (void)hoisted__v_1932;
    (void)hoisted__v_1932;
    I32 hoisted__I32_1933 = 0;
    (void)hoisted__I32_1933;
    U64 hoisted__U64_1934 = 1ULL;
    (void)hoisted__U64_1934;
    memset(hoisted__v_1932, hoisted__I32_1933, hoisted__U64_1934);
    Str *hoisted__Str_1935 = malloc(sizeof(Str));
    hoisted__Str_1935->c_str = buf;
    hoisted__Str_1935->count = total;
    hoisted__Str_1935->cap = total;
    (void)hoisted__Str_1935;
    return hoisted__Str_1935;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1955 = 8;
    (void)hoisted__U32_1955;
    return hoisted__U32_1955;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2076 = 0;
    (void)hoisted__U32_2076;
    U64 hoisted__U64_2077 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2076); });
    (void)hoisted__U64_2077;
    return hoisted__U64_2077;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_2080 = I64_cmp(a, b);
    (void)hoisted__I64_2080;
    I64 hoisted__I64_2081 = -1;
    (void)hoisted__I64_2081;
    Bool hoisted__Bool_2082 = I64_eq(hoisted__I64_2080, hoisted__I64_2081);
    (void)hoisted__Bool_2082;
    return hoisted__Bool_2082;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_2083 = I64_cmp(a, b);
    (void)hoisted__I64_2083;
    I64 hoisted__I64_2084 = 1;
    (void)hoisted__I64_2084;
    Bool hoisted__Bool_2085 = I64_eq(hoisted__I64_2083, hoisted__I64_2084);
    (void)hoisted__Bool_2085;
    return hoisted__Bool_2085;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_2086 = I64_eq(a, b);
    (void)hoisted__Bool_2086;
    Bool hoisted__Bool_2087 = not(hoisted__Bool_2086);
    (void)hoisted__Bool_2087;
    return hoisted__Bool_2087;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2122 = 0;
    (void)_m_Bool_2122;
    {
        Bool hoisted__Bool_2125 = 1;
        (void)hoisted__Bool_2125;
        Bool hoisted__Bool_2126 = Bool_eq(a, hoisted__Bool_2125);
        (void)hoisted__Bool_2126;
        if (hoisted__Bool_2126) {
            Bool hoisted__Bool_2123 = Bool_clone(&b);
            (void)hoisted__Bool_2123;
            _m_Bool_2122 = hoisted__Bool_2123;
        } else {
            Bool hoisted__Bool_2124 = 0;
            (void)hoisted__Bool_2124;
            _m_Bool_2122 = hoisted__Bool_2124;
        }
    }
    return _m_Bool_2122;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2136 = Bool_eq(a, b);
    (void)hoisted__Bool_2136;
    if (hoisted__Bool_2136) {
        I64 hoisted__I64_2134 = 0;
        (void)hoisted__I64_2134;
        { I64 _ret_val = hoisted__I64_2134;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2135 = -1;
        (void)hoisted__I64_2135;
        return hoisted__I64_2135;
    }
    I64 hoisted__I64_2137 = 1;
    (void)hoisted__I64_2137;
    return hoisted__I64_2137;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2138 = 1;
    (void)hoisted__U32_2138;
    return hoisted__U32_2138;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2139 = 0;
    (void)hoisted__U32_2139;
    U64 hoisted__U64_2140 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2139); });
    (void)hoisted__U64_2140;
    return hoisted__U64_2140;
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
    Bool hoisted__Bool_2166 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2166;
    if (hoisted__Bool_2166) {
        Bool hoisted__Bool_2156 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2156;
        { Bool _ret_val = hoisted__Bool_2156;
                return _ret_val; }
    }
    Bool hoisted__Bool_2167 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2167;
    if (hoisted__Bool_2167) {
        Bool hoisted__Bool_2157 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2157;
        { Bool _ret_val = hoisted__Bool_2157;
                return _ret_val; }
    }
    Bool hoisted__Bool_2168 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2168;
    if (hoisted__Bool_2168) {
        Bool hoisted__Bool_2158 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2158;
        { Bool _ret_val = hoisted__Bool_2158;
                return _ret_val; }
    }
    Bool hoisted__Bool_2169 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2169;
    if (hoisted__Bool_2169) {
        Bool hoisted__Bool_2159 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2159;
        { Bool _ret_val = hoisted__Bool_2159;
                return _ret_val; }
    }
    Bool hoisted__Bool_2170 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2170;
    if (hoisted__Bool_2170) {
        Bool hoisted__Bool_2160 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2160;
        { Bool _ret_val = hoisted__Bool_2160;
                return _ret_val; }
    }
    Bool hoisted__Bool_2171 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2171;
    if (hoisted__Bool_2171) {
        Bool hoisted__Bool_2161 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2161;
        { Bool _ret_val = hoisted__Bool_2161;
                return _ret_val; }
    }
    Bool hoisted__Bool_2172 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2172;
    if (hoisted__Bool_2172) {
        Bool hoisted__Bool_2162 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2162;
        { Bool _ret_val = hoisted__Bool_2162;
                return _ret_val; }
    }
    Bool hoisted__Bool_2173 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2173;
    if (hoisted__Bool_2173) {
        Bool hoisted__Bool_2163 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2163;
        { Bool _ret_val = hoisted__Bool_2163;
                return _ret_val; }
    }
    Bool hoisted__Bool_2174 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2174;
    if (hoisted__Bool_2174) {
        Bool hoisted__Bool_2164 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2164;
        { Bool _ret_val = hoisted__Bool_2164;
                return _ret_val; }
    }
    Bool hoisted__Bool_2175 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2175;
    if (hoisted__Bool_2175) {
        Bool hoisted__Bool_2165 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2165;
        { Bool _ret_val = hoisted__Bool_2165;
                return _ret_val; }
    }
    Bool hoisted__Bool_2176 = 0;
    (void)hoisted__Bool_2176;
    return hoisted__Bool_2176;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2198 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2198;
    if (hoisted__Bool_2198) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2199 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2199;
    if (hoisted__Bool_2199) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2200 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2200;
    if (hoisted__Bool_2200) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2201 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2201;
    if (hoisted__Bool_2201) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2202 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2202;
    if (hoisted__Bool_2202) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2203 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2203;
    if (hoisted__Bool_2203) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2204 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2204;
    if (hoisted__Bool_2204) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2205 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2206 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2206;
    if (hoisted__Bool_2206) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2207 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2207;
    if (hoisted__Bool_2207) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2208 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2208;
    UNREACHABLE(&hoisted__Str_2208);
    Str_delete(&hoisted__Str_2208, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2209 = 4;
    (void)hoisted__U32_2209;
    return hoisted__U32_2209;
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
    Bool hoisted__Bool_2261 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2261;
    if (hoisted__Bool_2261) {
        Str *hoisted__Str_2251 = get_payload(self);
        (void)hoisted__Str_2251;
        (void)hoisted__Str_2251;
        Bool hoisted__Bool_2252 = 0;
        (void)hoisted__Bool_2252;
        Str_delete(hoisted__Str_2251, hoisted__Bool_2252);
    }
    Bool hoisted__Bool_2262 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2262;
    if (hoisted__Bool_2262) {
        Str *hoisted__Str_2253 = get_payload(self);
        (void)hoisted__Str_2253;
        (void)hoisted__Str_2253;
        Bool hoisted__Bool_2254 = 0;
        (void)hoisted__Bool_2254;
        Str_delete(hoisted__Str_2253, hoisted__Bool_2254);
    }
    Bool hoisted__Bool_2263 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2263;
    if (hoisted__Bool_2263) {
        Str *hoisted__Str_2255 = get_payload(self);
        (void)hoisted__Str_2255;
        (void)hoisted__Str_2255;
        Bool hoisted__Bool_2256 = 0;
        (void)hoisted__Bool_2256;
        Str_delete(hoisted__Str_2255, hoisted__Bool_2256);
    }
    Bool hoisted__Bool_2264 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2264;
    if (hoisted__Bool_2264) {
        Primitive *hoisted__Primitive_2257 = get_payload(self);
        (void)hoisted__Primitive_2257;
        (void)hoisted__Primitive_2257;
        Bool hoisted__Bool_2258 = 0;
        (void)hoisted__Bool_2258;
        Primitive_delete(hoisted__Primitive_2257, hoisted__Bool_2258);
    }
    Bool hoisted__Bool_2265 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2265;
    if (hoisted__Bool_2265) {
        Str *hoisted__Str_2259 = get_payload(self);
        (void)hoisted__Str_2259;
        (void)hoisted__Str_2259;
        Bool hoisted__Bool_2260 = 0;
        (void)hoisted__Bool_2260;
        Str_delete(hoisted__Str_2259, hoisted__Bool_2260);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2334 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2334;
    if (hoisted__Bool_2334) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2335 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2335;
    if (hoisted__Bool_2335) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2336 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2336;
    if (hoisted__Bool_2336) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2326 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2326;
        Type *hoisted__Type_2327 = Type_Struct(hoisted__Str_2326);
        (void)hoisted__Type_2327;
        { Type * _ret_val = hoisted__Type_2327;
                return _ret_val; }
    }
    Bool hoisted__Bool_2337 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2337;
    if (hoisted__Bool_2337) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2338 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2338;
    if (hoisted__Bool_2338) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2328 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2328;
        Type *hoisted__Type_2329 = Type_Enum(hoisted__Str_2328);
        (void)hoisted__Type_2329;
        { Type * _ret_val = hoisted__Type_2329;
                return _ret_val; }
    }
    Bool hoisted__Bool_2339 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2339;
    if (hoisted__Bool_2339) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2340 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2340;
    if (hoisted__Bool_2340) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2341 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2342 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2342;
    if (hoisted__Bool_2342) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2343 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2343;
    if (hoisted__Bool_2343) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2330 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2330;
        Type *hoisted__Type_2331 = Type_Custom(hoisted__Str_2330);
        (void)hoisted__Type_2331;
        { Type * _ret_val = hoisted__Type_2331;
                return _ret_val; }
    }
    Bool hoisted__Bool_2344 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2344;
    if (hoisted__Bool_2344) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2332 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2332;
        Type *hoisted__Type_2333 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2332; _oa; }));
        (void)hoisted__Type_2333;
        { Type * _ret_val = hoisted__Type_2333;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2345 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2345;
    Type *hoisted__Type_2346 = Type_FuncPtrSig(hoisted__Str_2345);
    (void)hoisted__Type_2346;
    return hoisted__Type_2346;
}

U32 Type_size(void) {
    U32 hoisted__U32_2347 = 24;
    (void)hoisted__U32_2347;
    return hoisted__U32_2347;
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
    Bool hoisted__Bool_2448 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2448;
    if (hoisted__Bool_2448) {
        Bool hoisted__Bool_2440 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2440;
        { Bool _ret_val = hoisted__Bool_2440;
                return _ret_val; }
    }
    Bool hoisted__Bool_2449 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2449;
    if (hoisted__Bool_2449) {
        Bool hoisted__Bool_2441 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2441;
        { Bool _ret_val = hoisted__Bool_2441;
                return _ret_val; }
    }
    Bool hoisted__Bool_2450 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2450;
    if (hoisted__Bool_2450) {
        Bool hoisted__Bool_2442 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2442;
        { Bool _ret_val = hoisted__Bool_2442;
                return _ret_val; }
    }
    Bool hoisted__Bool_2451 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2451;
    if (hoisted__Bool_2451) {
        Bool hoisted__Bool_2443 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2443;
        { Bool _ret_val = hoisted__Bool_2443;
                return _ret_val; }
    }
    Bool hoisted__Bool_2452 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2452;
    if (hoisted__Bool_2452) {
        Bool hoisted__Bool_2444 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2444;
        { Bool _ret_val = hoisted__Bool_2444;
                return _ret_val; }
    }
    Bool hoisted__Bool_2453 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2453;
    if (hoisted__Bool_2453) {
        Bool hoisted__Bool_2445 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2445;
        { Bool _ret_val = hoisted__Bool_2445;
                return _ret_val; }
    }
    Bool hoisted__Bool_2454 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2454;
    if (hoisted__Bool_2454) {
        Bool hoisted__Bool_2446 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2446;
        { Bool _ret_val = hoisted__Bool_2446;
                return _ret_val; }
    }
    Bool hoisted__Bool_2455 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2455;
    if (hoisted__Bool_2455) {
        Bool hoisted__Bool_2447 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2447;
        { Bool _ret_val = hoisted__Bool_2447;
                return _ret_val; }
    }
    Bool hoisted__Bool_2456 = 0;
    (void)hoisted__Bool_2456;
    return hoisted__Bool_2456;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2474 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2474;
    if (hoisted__Bool_2474) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2475 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2475;
    if (hoisted__Bool_2475) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2476 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2476;
    if (hoisted__Bool_2476) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2477 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2477;
    if (hoisted__Bool_2477) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2478 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2478;
    if (hoisted__Bool_2478) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2479 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2479;
    if (hoisted__Bool_2479) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2480 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2480;
    if (hoisted__Bool_2480) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2481 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2481;
    if (hoisted__Bool_2481) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2482 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2482;
    UNREACHABLE(&hoisted__Str_2482);
    Str_delete(&hoisted__Str_2482, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2483 = 4;
    (void)hoisted__U32_2483;
    return hoisted__U32_2483;
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
    Bool hoisted__Bool_2488 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2488;
    if (hoisted__Bool_2488) {
        Bool hoisted__Bool_2485 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2485;
        { Bool _ret_val = hoisted__Bool_2485;
                return _ret_val; }
    }
    Bool hoisted__Bool_2489 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2489;
    if (hoisted__Bool_2489) {
        Bool hoisted__Bool_2486 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2486;
        { Bool _ret_val = hoisted__Bool_2486;
                return _ret_val; }
    }
    Bool hoisted__Bool_2490 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2490;
    if (hoisted__Bool_2490) {
        Bool hoisted__Bool_2487 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2487;
        { Bool _ret_val = hoisted__Bool_2487;
                return _ret_val; }
    }
    Bool hoisted__Bool_2491 = 0;
    (void)hoisted__Bool_2491;
    return hoisted__Bool_2491;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2499 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2499;
    if (hoisted__Bool_2499) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2500 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2500;
    if (hoisted__Bool_2500) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2501 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2501;
    if (hoisted__Bool_2501) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2502 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2502;
    UNREACHABLE(&hoisted__Str_2502);
    Str_delete(&hoisted__Str_2502, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2503 = 4;
    (void)hoisted__U32_2503;
    return hoisted__U32_2503;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2505 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2505;
    Declaration *hoisted__Declaration_2506 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2506->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2506->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2506->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2506->is_mut = self->is_mut;
    hoisted__Declaration_2506->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2506->is_priv = self->is_priv;
    hoisted__Declaration_2506->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2506->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2506->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2506->default_value = hoisted__Expr_2505;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2506->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2506;
    return hoisted__Declaration_2506;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2507 = 0;
    (void)hoisted__Bool_2507;
    Str_delete(&self->name, hoisted__Bool_2507);
    Bool hoisted__Bool_2508 = 0;
    (void)hoisted__Bool_2508;
    Str_delete(&self->doc, hoisted__Bool_2508);
    Bool hoisted__Bool_2509 = 0;
    (void)hoisted__Bool_2509;
    Str_delete(&self->explicit_type, hoisted__Bool_2509);
    Bool hoisted__Bool_2510 = 0;
    (void)hoisted__Bool_2510;
    Bool_delete(&self->is_mut, hoisted__Bool_2510);
    Bool hoisted__Bool_2511 = 0;
    (void)hoisted__Bool_2511;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2511);
    Bool hoisted__Bool_2512 = 0;
    (void)hoisted__Bool_2512;
    Bool_delete(&self->is_priv, hoisted__Bool_2512);
    Bool hoisted__Bool_2513 = 0;
    (void)hoisted__Bool_2513;
    Bool_delete(&self->used, hoisted__Bool_2513);
    Bool hoisted__Bool_2514 = 0;
    (void)hoisted__Bool_2514;
    OwnType_delete(&self->own_type, hoisted__Bool_2514);
    Bool hoisted__Bool_2515 = 0;
    (void)hoisted__Bool_2515;
    Type_delete(&self->til_type, hoisted__Bool_2515);
    Bool hoisted__Bool_2516 = 1;
    (void)hoisted__Bool_2516;
    Expr_delete(self->default_value, hoisted__Bool_2516);
    Bool hoisted__Bool_2517 = 0;
    (void)hoisted__Bool_2517;
    Str_delete(&self->orig_name, hoisted__Bool_2517);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2518 = 104;
    (void)hoisted__U32_2518;
    return hoisted__U32_2518;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2520 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2520->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2520->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2520->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2520->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2520->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2520->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2520->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2520->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2520->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2520->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2520->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2520;
    return hoisted__FunctionDef_2520;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2521 = 0;
    (void)hoisted__Bool_2521;
    FuncType_delete(&self->func_type, hoisted__Bool_2521);
    Bool hoisted__Bool_2522 = 0;
    (void)hoisted__Bool_2522;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2522);
    Bool hoisted__Bool_2523 = 0;
    (void)hoisted__Bool_2523;
    Str_delete(&self->return_type, hoisted__Bool_2523);
    Bool hoisted__Bool_2524 = 0;
    (void)hoisted__Bool_2524;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2524);
    Bool hoisted__Bool_2525 = 0;
    (void)hoisted__Bool_2525;
    I32_delete(&self->variadic_index, hoisted__Bool_2525);
    Bool hoisted__Bool_2526 = 0;
    (void)hoisted__Bool_2526;
    I32_delete(&self->kwargs_index, hoisted__Bool_2526);
    Bool hoisted__Bool_2527 = 0;
    (void)hoisted__Bool_2527;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2527);
    Bool hoisted__Bool_2528 = 0;
    (void)hoisted__Bool_2528;
    Bool_delete(&self->auto_generated, hoisted__Bool_2528);
    Bool hoisted__Bool_2529 = 0;
    (void)hoisted__Bool_2529;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2529);
    Bool hoisted__Bool_2530 = 0;
    (void)hoisted__Bool_2530;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2530);
    Bool hoisted__Bool_2531 = 0;
    (void)hoisted__Bool_2531;
    Str_delete(&self->closure_name, hoisted__Bool_2531);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2532 = 0;
    (void)hoisted__U32_2532;
    U64 hoisted__U64_2533 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2532); });
    (void)hoisted__U64_2533;
    return hoisted__U64_2533;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2534 = 104;
    (void)hoisted__U32_2534;
    return hoisted__U32_2534;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2537 = malloc(sizeof(FCallData));
    hoisted__FCallData_2537->is_splat = self->is_splat;
    hoisted__FCallData_2537->does_throw = self->does_throw;
    hoisted__FCallData_2537->is_bang = self->is_bang;
    hoisted__FCallData_2537->own_args = self->own_args;
    hoisted__FCallData_2537->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2537->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2537;
    return hoisted__FCallData_2537;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2538 = 0;
    (void)hoisted__Bool_2538;
    Bool_delete(&self->is_splat, hoisted__Bool_2538);
    Bool hoisted__Bool_2539 = 0;
    (void)hoisted__Bool_2539;
    Bool_delete(&self->does_throw, hoisted__Bool_2539);
    Bool hoisted__Bool_2540 = 0;
    (void)hoisted__Bool_2540;
    Bool_delete(&self->is_bang, hoisted__Bool_2540);
    Bool hoisted__Bool_2541 = 0;
    (void)hoisted__Bool_2541;
    U64_delete(&self->own_args, hoisted__Bool_2541);
    Bool hoisted__Bool_2542 = 0;
    (void)hoisted__Bool_2542;
    Bool_delete(&self->swap_replace, hoisted__Bool_2542);
    Bool hoisted__Bool_2543 = 0;
    (void)hoisted__Bool_2543;
    Type_delete(&self->til_type, hoisted__Bool_2543);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2544 = 0;
    (void)hoisted__U32_2544;
    U64 hoisted__U64_2545 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2544); });
    (void)hoisted__U64_2545;
    return hoisted__U64_2545;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2546 = 48;
    (void)hoisted__U32_2546;
    return hoisted__U32_2546;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2558 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2558->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2558->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2558;
    return hoisted__LiteralNumData_2558;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2559 = 0;
    (void)hoisted__Bool_2559;
    Str_delete(&self->text, hoisted__Bool_2559);
    Bool hoisted__Bool_2560 = 0;
    (void)hoisted__Bool_2560;
    Type_delete(&self->til_type, hoisted__Bool_2560);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2561 = 0;
    (void)hoisted__U32_2561;
    U64 hoisted__U64_2562 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2561); });
    (void)hoisted__U64_2562;
    return hoisted__U64_2562;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2563 = 40;
    (void)hoisted__U32_2563;
    return hoisted__U32_2563;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2574 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2574->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2574->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2574;
    return hoisted__IdentData_2574;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2575 = 0;
    (void)hoisted__Bool_2575;
    Str_delete(&self->name, hoisted__Bool_2575);
    Bool hoisted__Bool_2576 = 0;
    (void)hoisted__Bool_2576;
    Type_delete(&self->til_type, hoisted__Bool_2576);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2577 = 0;
    (void)hoisted__U32_2577;
    U64 hoisted__U64_2578 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2577); });
    (void)hoisted__U64_2578;
    return hoisted__U64_2578;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2579 = 40;
    (void)hoisted__U32_2579;
    return hoisted__U32_2579;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2586 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2586->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2586->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2586;
    return hoisted__FieldAccessData_2586;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2587 = 0;
    (void)hoisted__Bool_2587;
    Str_delete(&self->name, hoisted__Bool_2587);
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    Type_delete(&self->til_type, hoisted__Bool_2588);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2589 = 0;
    (void)hoisted__U32_2589;
    U64 hoisted__U64_2590 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2589); });
    (void)hoisted__U64_2590;
    return hoisted__U64_2590;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2591 = 40;
    (void)hoisted__U32_2591;
    return hoisted__U32_2591;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2662 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2662->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2662->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2662->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2662->is_interface = self->is_interface;
    hoisted__StructDef_2662->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2662->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2662;
    return hoisted__StructDef_2662;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2663 = 0;
    (void)hoisted__Bool_2663;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2663);
    Bool hoisted__Bool_2664 = 0;
    (void)hoisted__Bool_2664;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2664);
    Bool hoisted__Bool_2665 = 0;
    (void)hoisted__Bool_2665;
    Str_delete(&self->c_tag, hoisted__Bool_2665);
    Bool hoisted__Bool_2666 = 0;
    (void)hoisted__Bool_2666;
    Bool_delete(&self->is_interface, hoisted__Bool_2666);
    Bool hoisted__Bool_2667 = 0;
    (void)hoisted__Bool_2667;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2667);
    Bool hoisted__Bool_2668 = 0;
    (void)hoisted__Bool_2668;
    Str_delete(&self->implements_name, hoisted__Bool_2668);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2669 = 0;
    (void)hoisted__U32_2669;
    U64 hoisted__U64_2670 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2669); });
    (void)hoisted__U64_2670;
    return hoisted__U64_2670;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2671 = 72;
    (void)hoisted__U32_2671;
    return hoisted__U32_2671;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2676 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2676->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2676->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2676->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2676->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2676->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2676;
    return hoisted__EnumDef_2676;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2677 = 0;
    (void)hoisted__Bool_2677;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2677);
    Bool hoisted__Bool_2678 = 0;
    (void)hoisted__Bool_2678;
    Vec__Str_delete(&self->variants, hoisted__Bool_2678);
    Bool hoisted__Bool_2679 = 0;
    (void)hoisted__Bool_2679;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2679);
    Bool hoisted__Bool_2680 = 0;
    (void)hoisted__Bool_2680;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2680);
    Bool hoisted__Bool_2681 = 0;
    (void)hoisted__Bool_2681;
    Str_delete(&self->implements_name, hoisted__Bool_2681);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2682 = 0;
    (void)hoisted__U32_2682;
    U64 hoisted__U64_2683 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2682); });
    (void)hoisted__U64_2683;
    return hoisted__U64_2683;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2684 = 96;
    (void)hoisted__U32_2684;
    return hoisted__U32_2684;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2780 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2780->name = *_ca; free(_ca); }
    hoisted__AssignData_2780->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2780->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2780->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2780;
    return hoisted__AssignData_2780;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2781 = 0;
    (void)hoisted__Bool_2781;
    Str_delete(&self->name, hoisted__Bool_2781);
    Bool hoisted__Bool_2782 = 0;
    (void)hoisted__Bool_2782;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2782);
    Bool hoisted__Bool_2783 = 0;
    (void)hoisted__Bool_2783;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2783);
    Bool hoisted__Bool_2784 = 0;
    (void)hoisted__Bool_2784;
    Bool_delete(&self->swap_replace, hoisted__Bool_2784);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2785 = 0;
    (void)hoisted__U32_2785;
    U64 hoisted__U64_2786 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2785); });
    (void)hoisted__U64_2786;
    return hoisted__U64_2786;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2787 = 24;
    (void)hoisted__U32_2787;
    return hoisted__U32_2787;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2789 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2789->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2789->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2789;
    return hoisted__FieldAssignData_2789;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2790 = 0;
    (void)hoisted__Bool_2790;
    Str_delete(&self->name, hoisted__Bool_2790);
    Bool hoisted__Bool_2791 = 0;
    (void)hoisted__Bool_2791;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2791);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2792 = 0;
    (void)hoisted__U32_2792;
    U64 hoisted__U64_2793 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2792); });
    (void)hoisted__U64_2793;
    return hoisted__U64_2793;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2794 = 24;
    (void)hoisted__U32_2794;
    return hoisted__U32_2794;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2796 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2796->name = *_ca; free(_ca); }
    hoisted__ForInData_2796->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2796->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2796;
    return hoisted__ForInData_2796;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2797 = 0;
    (void)hoisted__Bool_2797;
    Str_delete(&self->name, hoisted__Bool_2797);
    Bool hoisted__Bool_2798 = 0;
    (void)hoisted__Bool_2798;
    Bool_delete(&self->is_mut, hoisted__Bool_2798);
    Bool hoisted__Bool_2799 = 0;
    (void)hoisted__Bool_2799;
    Type_delete(&self->til_type, hoisted__Bool_2799);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2800 = 0;
    (void)hoisted__U32_2800;
    U64 hoisted__U64_2801 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2800); });
    (void)hoisted__U64_2801;
    return hoisted__U64_2801;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2802 = 48;
    (void)hoisted__U32_2802;
    return hoisted__U32_2802;
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
    Bool hoisted__Bool_2832 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2832;
    if (hoisted__Bool_2832) {
        Str *hoisted__Str_2826 = get_payload(self);
        (void)hoisted__Str_2826;
        (void)hoisted__Str_2826;
        Bool hoisted__Bool_2827 = 0;
        (void)hoisted__Bool_2827;
        Str_delete(hoisted__Str_2826, hoisted__Bool_2827);
    }
    Bool hoisted__Bool_2833 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2833;
    if (hoisted__Bool_2833) {
        LiteralNumData *hoisted__LiteralNumData_2828 = get_payload(self);
        (void)hoisted__LiteralNumData_2828;
        (void)hoisted__LiteralNumData_2828;
        Bool hoisted__Bool_2829 = 0;
        (void)hoisted__Bool_2829;
        LiteralNumData_delete(hoisted__LiteralNumData_2828, hoisted__Bool_2829);
    }
    Bool hoisted__Bool_2834 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2834;
    if (hoisted__Bool_2834) {
        Bool *hoisted__Bool_2830 = get_payload(self);
        (void)hoisted__Bool_2830;
        (void)hoisted__Bool_2830;
        Bool hoisted__Bool_2831 = 0;
        (void)hoisted__Bool_2831;
        Bool_delete(hoisted__Bool_2830, hoisted__Bool_2831);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2874 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2874;
    if (hoisted__Bool_2874) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2869 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2869;
        Literal *hoisted__Literal_2870 = Literal_Str(hoisted__Str_2869);
        (void)hoisted__Literal_2870;
        { Literal * _ret_val = hoisted__Literal_2870;
                return _ret_val; }
    }
    Bool hoisted__Bool_2875 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2875;
    if (hoisted__Bool_2875) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2871 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2871;
        Literal *hoisted__Literal_2872 = Literal_Num(hoisted__LiteralNumData_2871);
        (void)hoisted__Literal_2872;
        { Literal * _ret_val = hoisted__Literal_2872;
                return _ret_val; }
    }
    Bool hoisted__Bool_2876 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2876;
    if (hoisted__Bool_2876) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2873 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2873;
        { Literal * _ret_val = hoisted__Literal_2873;
                return _ret_val; }
    }
    Bool hoisted__Bool_2877 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2877;
    if (hoisted__Bool_2877) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2878 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2878;
    if (hoisted__Bool_2878) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2879 = 48;
    (void)hoisted__U32_2879;
    return hoisted__U32_2879;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2882 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2882->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2882->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2882;
    return hoisted__MatchData_2882;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2883 = 0;
    (void)hoisted__Bool_2883;
    Type_delete(&self->til_type, hoisted__Bool_2883);
    Bool hoisted__Bool_2884 = 0;
    (void)hoisted__Bool_2884;
    Str_delete(&self->result_temp, hoisted__Bool_2884);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2885 = 0;
    (void)hoisted__U32_2885;
    U64 hoisted__U64_2886 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2885); });
    (void)hoisted__U64_2886;
    return hoisted__U64_2886;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2887 = 40;
    (void)hoisted__U32_2887;
    return hoisted__U32_2887;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2892 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2892->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2892;
    return hoisted__CaptureBlockData_2892;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2893 = 0;
    (void)hoisted__Bool_2893;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2893);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2894 = 0;
    (void)hoisted__U32_2894;
    U64 hoisted__U64_2895 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2894); });
    (void)hoisted__U64_2895;
    return hoisted__U64_2895;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2896 = 16;
    (void)hoisted__U32_2896;
    return hoisted__U32_2896;
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
NodeType *NodeType_CallerLoc() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_CallerLoc;
    return r;
}
void NodeType_delete(NodeType * self, Bool call_free) {
    Bool hoisted__Bool_3075 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3075;
    if (hoisted__Bool_3075) {
        Literal *hoisted__Literal_3047 = get_payload(self);
        (void)hoisted__Literal_3047;
        (void)hoisted__Literal_3047;
        Bool hoisted__Bool_3048 = 0;
        (void)hoisted__Bool_3048;
        Literal_delete(hoisted__Literal_3047, hoisted__Bool_3048);
    }
    Bool hoisted__Bool_3076 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3076;
    if (hoisted__Bool_3076) {
        IdentData *hoisted__IdentData_3049 = get_payload(self);
        (void)hoisted__IdentData_3049;
        (void)hoisted__IdentData_3049;
        Bool hoisted__Bool_3050 = 0;
        (void)hoisted__Bool_3050;
        IdentData_delete(hoisted__IdentData_3049, hoisted__Bool_3050);
    }
    Bool hoisted__Bool_3077 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3077;
    if (hoisted__Bool_3077) {
        Declaration *hoisted__Declaration_3051 = get_payload(self);
        (void)hoisted__Declaration_3051;
        (void)hoisted__Declaration_3051;
        Bool hoisted__Bool_3052 = 0;
        (void)hoisted__Bool_3052;
        Declaration_delete(hoisted__Declaration_3051, hoisted__Bool_3052);
    }
    Bool hoisted__Bool_3078 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3078;
    if (hoisted__Bool_3078) {
        AssignData *hoisted__AssignData_3053 = get_payload(self);
        (void)hoisted__AssignData_3053;
        (void)hoisted__AssignData_3053;
        Bool hoisted__Bool_3054 = 0;
        (void)hoisted__Bool_3054;
        AssignData_delete(hoisted__AssignData_3053, hoisted__Bool_3054);
    }
    Bool hoisted__Bool_3079 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3079;
    if (hoisted__Bool_3079) {
        FCallData *hoisted__FCallData_3055 = get_payload(self);
        (void)hoisted__FCallData_3055;
        (void)hoisted__FCallData_3055;
        Bool hoisted__Bool_3056 = 0;
        (void)hoisted__Bool_3056;
        FCallData_delete(hoisted__FCallData_3055, hoisted__Bool_3056);
    }
    Bool hoisted__Bool_3080 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3080;
    if (hoisted__Bool_3080) {
        FunctionDef *hoisted__FunctionDef_3057 = get_payload(self);
        (void)hoisted__FunctionDef_3057;
        (void)hoisted__FunctionDef_3057;
        Bool hoisted__Bool_3058 = 0;
        (void)hoisted__Bool_3058;
        FunctionDef_delete(hoisted__FunctionDef_3057, hoisted__Bool_3058);
    }
    Bool hoisted__Bool_3081 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3081;
    if (hoisted__Bool_3081) {
        StructDef *hoisted__StructDef_3059 = get_payload(self);
        (void)hoisted__StructDef_3059;
        (void)hoisted__StructDef_3059;
        Bool hoisted__Bool_3060 = 0;
        (void)hoisted__Bool_3060;
        StructDef_delete(hoisted__StructDef_3059, hoisted__Bool_3060);
    }
    Bool hoisted__Bool_3082 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3082;
    if (hoisted__Bool_3082) {
        EnumDef *hoisted__EnumDef_3061 = get_payload(self);
        (void)hoisted__EnumDef_3061;
        (void)hoisted__EnumDef_3061;
        Bool hoisted__Bool_3062 = 0;
        (void)hoisted__Bool_3062;
        EnumDef_delete(hoisted__EnumDef_3061, hoisted__Bool_3062);
    }
    Bool hoisted__Bool_3083 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3083;
    if (hoisted__Bool_3083) {
        FieldAccessData *hoisted__FieldAccessData_3063 = get_payload(self);
        (void)hoisted__FieldAccessData_3063;
        (void)hoisted__FieldAccessData_3063;
        Bool hoisted__Bool_3064 = 0;
        (void)hoisted__Bool_3064;
        FieldAccessData_delete(hoisted__FieldAccessData_3063, hoisted__Bool_3064);
    }
    Bool hoisted__Bool_3084 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3084;
    if (hoisted__Bool_3084) {
        FieldAssignData *hoisted__FieldAssignData_3065 = get_payload(self);
        (void)hoisted__FieldAssignData_3065;
        (void)hoisted__FieldAssignData_3065;
        Bool hoisted__Bool_3066 = 0;
        (void)hoisted__Bool_3066;
        FieldAssignData_delete(hoisted__FieldAssignData_3065, hoisted__Bool_3066);
    }
    Bool hoisted__Bool_3085 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3085;
    if (hoisted__Bool_3085) {
        ForInData *hoisted__ForInData_3067 = get_payload(self);
        (void)hoisted__ForInData_3067;
        (void)hoisted__ForInData_3067;
        Bool hoisted__Bool_3068 = 0;
        (void)hoisted__Bool_3068;
        ForInData_delete(hoisted__ForInData_3067, hoisted__Bool_3068);
    }
    Bool hoisted__Bool_3086 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3086;
    if (hoisted__Bool_3086) {
        Str *hoisted__Str_3069 = get_payload(self);
        (void)hoisted__Str_3069;
        (void)hoisted__Str_3069;
        Bool hoisted__Bool_3070 = 0;
        (void)hoisted__Bool_3070;
        Str_delete(hoisted__Str_3069, hoisted__Bool_3070);
    }
    Bool hoisted__Bool_3087 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3087;
    if (hoisted__Bool_3087) {
        MatchData *hoisted__MatchData_3071 = get_payload(self);
        (void)hoisted__MatchData_3071;
        (void)hoisted__MatchData_3071;
        Bool hoisted__Bool_3072 = 0;
        (void)hoisted__Bool_3072;
        MatchData_delete(hoisted__MatchData_3071, hoisted__Bool_3072);
    }
    Bool hoisted__Bool_3088 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3088;
    if (hoisted__Bool_3088) {
        CaptureBlockData *hoisted__CaptureBlockData_3073 = get_payload(self);
        (void)hoisted__CaptureBlockData_3073;
        (void)hoisted__CaptureBlockData_3073;
        Bool hoisted__Bool_3074 = 0;
        (void)hoisted__Bool_3074;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3073, hoisted__Bool_3074);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3270 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3270;
    if (hoisted__Bool_3270) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3271 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3271;
    if (hoisted__Bool_3271) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3242 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3242;
        NodeType *hoisted__NodeType_3243 = NodeType_Literal(hoisted__Literal_3242);
        (void)hoisted__NodeType_3243;
        { NodeType * _ret_val = hoisted__NodeType_3243;
                return _ret_val; }
    }
    Bool hoisted__Bool_3272 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3272;
    if (hoisted__Bool_3272) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3244 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3244;
        NodeType *hoisted__NodeType_3245 = NodeType_Ident(hoisted__IdentData_3244);
        (void)hoisted__NodeType_3245;
        { NodeType * _ret_val = hoisted__NodeType_3245;
                return _ret_val; }
    }
    Bool hoisted__Bool_3273 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3273;
    if (hoisted__Bool_3273) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3246 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3246;
        NodeType *hoisted__NodeType_3247 = NodeType_Decl(hoisted__Declaration_3246);
        (void)hoisted__NodeType_3247;
        { NodeType * _ret_val = hoisted__NodeType_3247;
                return _ret_val; }
    }
    Bool hoisted__Bool_3274 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3274;
    if (hoisted__Bool_3274) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3248 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3248;
        NodeType *hoisted__NodeType_3249 = NodeType_Assign(hoisted__AssignData_3248);
        (void)hoisted__NodeType_3249;
        { NodeType * _ret_val = hoisted__NodeType_3249;
                return _ret_val; }
    }
    Bool hoisted__Bool_3275 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3275;
    if (hoisted__Bool_3275) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3250 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3250;
        NodeType *hoisted__NodeType_3251 = NodeType_FCall(hoisted__FCallData_3250);
        (void)hoisted__NodeType_3251;
        { NodeType * _ret_val = hoisted__NodeType_3251;
                return _ret_val; }
    }
    Bool hoisted__Bool_3276 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3276;
    if (hoisted__Bool_3276) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3252 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3252;
        NodeType *hoisted__NodeType_3253 = NodeType_FuncDef(hoisted__FunctionDef_3252);
        (void)hoisted__NodeType_3253;
        { NodeType * _ret_val = hoisted__NodeType_3253;
                return _ret_val; }
    }
    Bool hoisted__Bool_3277 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3277;
    if (hoisted__Bool_3277) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3254 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3254;
        NodeType *hoisted__NodeType_3255 = NodeType_StructDef(hoisted__StructDef_3254);
        (void)hoisted__NodeType_3255;
        { NodeType * _ret_val = hoisted__NodeType_3255;
                return _ret_val; }
    }
    Bool hoisted__Bool_3278 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3278;
    if (hoisted__Bool_3278) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3256 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3256;
        NodeType *hoisted__NodeType_3257 = NodeType_EnumDef(hoisted__EnumDef_3256);
        (void)hoisted__NodeType_3257;
        { NodeType * _ret_val = hoisted__NodeType_3257;
                return _ret_val; }
    }
    Bool hoisted__Bool_3279 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3279;
    if (hoisted__Bool_3279) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3258 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3258;
        NodeType *hoisted__NodeType_3259 = NodeType_FieldAccess(hoisted__FieldAccessData_3258);
        (void)hoisted__NodeType_3259;
        { NodeType * _ret_val = hoisted__NodeType_3259;
                return _ret_val; }
    }
    Bool hoisted__Bool_3280 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3280;
    if (hoisted__Bool_3280) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3260 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3260;
        NodeType *hoisted__NodeType_3261 = NodeType_FieldAssign(hoisted__FieldAssignData_3260);
        (void)hoisted__NodeType_3261;
        { NodeType * _ret_val = hoisted__NodeType_3261;
                return _ret_val; }
    }
    Bool hoisted__Bool_3281 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3281;
    if (hoisted__Bool_3281) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3282 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3282;
    if (hoisted__Bool_3282) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3283 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3283;
    if (hoisted__Bool_3283) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3284 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3284;
    if (hoisted__Bool_3284) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3262 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3262;
        NodeType *hoisted__NodeType_3263 = NodeType_ForIn(hoisted__ForInData_3262);
        (void)hoisted__NodeType_3263;
        { NodeType * _ret_val = hoisted__NodeType_3263;
                return _ret_val; }
    }
    Bool hoisted__Bool_3285 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3285;
    if (hoisted__Bool_3285) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3264 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3264;
        NodeType *hoisted__NodeType_3265 = NodeType_NamedArg(hoisted__Str_3264);
        (void)hoisted__NodeType_3265;
        { NodeType * _ret_val = hoisted__NodeType_3265;
                return _ret_val; }
    }
    Bool hoisted__Bool_3286 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3286;
    if (hoisted__Bool_3286) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3287 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3287;
    if (hoisted__Bool_3287) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3288 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3288;
    if (hoisted__Bool_3288) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3289 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3289;
    if (hoisted__Bool_3289) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3266 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3266;
        NodeType *hoisted__NodeType_3267 = NodeType_Match(hoisted__MatchData_3266);
        (void)hoisted__NodeType_3267;
        { NodeType * _ret_val = hoisted__NodeType_3267;
                return _ret_val; }
    }
    Bool hoisted__Bool_3290 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3290;
    if (hoisted__Bool_3290) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3291 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3291;
    if (hoisted__Bool_3291) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3292 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3292;
    if (hoisted__Bool_3292) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3293 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3293;
    if (hoisted__Bool_3293) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3294 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3294;
    if (hoisted__Bool_3294) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3295 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3295;
    if (hoisted__Bool_3295) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3268 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3268;
        NodeType *hoisted__NodeType_3269 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3268);
        (void)hoisted__NodeType_3269;
        { NodeType * _ret_val = hoisted__NodeType_3269;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_CallerLoc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3296 = 112;
    (void)hoisted__U32_3296;
    return hoisted__U32_3296;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3297 = is_null(self);
    (void)hoisted__Bool_3297;
    if (hoisted__Bool_3297) {
        return;
    }
    Bool hoisted__Bool_3298 = 0;
    (void)hoisted__Bool_3298;
    NodeType_delete(&self->node_type, hoisted__Bool_3298);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3342 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3342->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3342->children = *_ca; free(_ca); }
    hoisted__Expr_3342->line = line;
    hoisted__Expr_3342->col = col;
    (void)hoisted__Expr_3342;
    return hoisted__Expr_3342;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3350 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3350->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3350->children = *_ca; free(_ca); }
    hoisted__Expr_3350->line = self->line;
    hoisted__Expr_3350->col = self->col;
    (void)hoisted__Expr_3350;
    return hoisted__Expr_3350;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3351 = 0;
    (void)hoisted__U32_3351;
    U64 hoisted__U64_3352 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3351); });
    (void)hoisted__U64_3352;
    return hoisted__U64_3352;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3353 = 136;
    (void)hoisted__U32_3353;
    return hoisted__U32_3353;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_3947 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_3947->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_3947->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3947;
    return hoisted__Map__I64_Str_3947;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4092 = 0;
    (void)hoisted__Bool_4092;
    Vec__I64_delete(&self->keys, hoisted__Bool_4092);
    Bool hoisted__Bool_4093 = 0;
    (void)hoisted__Bool_4093;
    Vec__Str_delete(&self->values, hoisted__Bool_4093);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4094 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4094->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4094->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4094;
    return hoisted__Map__I64_Str_4094;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4095 = 0;
    (void)hoisted__U32_4095;
    U64 hoisted__U64_4096 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4095); });
    (void)hoisted__U64_4096;
    return hoisted__U64_4096;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4097 = 32;
    (void)hoisted__U32_4097;
    return hoisted__U32_4097;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4098 = 1;
    (void)hoisted__U32_4098;
    Type *hoisted__Type_4099 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4099;
    U64 hoisted__U64_4100 = (U64)(hoisted__U32_4098);
    (void)hoisted__U64_4100;
    Type_delete(hoisted__Type_4099, 1);
    void * hoisted__v_4101 = malloc(hoisted__U64_4100);
    (void)hoisted__v_4101;
    U32 hoisted__U32_4102 = 0;
    (void)hoisted__U32_4102;
    I64 hoisted__I64_4103 = 1;
    (void)hoisted__I64_4103;
    Vec__Bool *hoisted__Vec__Bool_4104 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4104->data = hoisted__v_4101;
    hoisted__Vec__Bool_4104->count = hoisted__U32_4102;
    hoisted__Vec__Bool_4104->cap = hoisted__I64_4103;
    (void)hoisted__Vec__Bool_4104;
    return hoisted__Vec__Bool_4104;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4105 = self->count;
        (void)_re_U32_4105;
        U32 _rc_U32_4105 = 0;
        (void)_rc_U32_4105;
        Bool hoisted__Bool_4120 = U32_lte(_rc_U32_4105, _re_U32_4105);
        (void)hoisted__Bool_4120;
        if (hoisted__Bool_4120) {
            while (1) {
                Bool _wcond_Bool_4106 = U32_lt(_rc_U32_4105, _re_U32_4105);
                (void)_wcond_Bool_4106;
                if (_wcond_Bool_4106) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4105);
                U32_inc(&_rc_U32_4105);
                U32 hoisted__U32_4107 = 1;
                (void)hoisted__U32_4107;
                U32 hoisted__U32_4108 = U32_mul(i, hoisted__U32_4107);
                (void)hoisted__U32_4108;
                Type *hoisted__Type_4109 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4109;
                U64 hoisted__U64_4110 = (U64)(hoisted__U32_4108);
                (void)hoisted__U64_4110;
                Type_delete(hoisted__Type_4109, 1);
                Bool *hoisted__Bool_4111 = ptr_add(self->data, hoisted__U64_4110);
                (void)hoisted__Bool_4111;
                (void)hoisted__Bool_4111;
                Bool hoisted__Bool_4112 = 0;
                (void)hoisted__Bool_4112;
                Bool_delete(hoisted__Bool_4111, hoisted__Bool_4112);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4113 = U32_gt(_rc_U32_4105, _re_U32_4105);
                (void)_wcond_Bool_4113;
                if (_wcond_Bool_4113) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4105);
                U32_dec(&_rc_U32_4105);
                U32 hoisted__U32_4114 = 1;
                (void)hoisted__U32_4114;
                U32 hoisted__U32_4115 = U32_mul(i, hoisted__U32_4114);
                (void)hoisted__U32_4115;
                Type *hoisted__Type_4116 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4116;
                U64 hoisted__U64_4117 = (U64)(hoisted__U32_4115);
                (void)hoisted__U64_4117;
                Type_delete(hoisted__Type_4116, 1);
                Bool *hoisted__Bool_4118 = ptr_add(self->data, hoisted__U64_4117);
                (void)hoisted__Bool_4118;
                (void)hoisted__Bool_4118;
                Bool hoisted__Bool_4119 = 0;
                (void)hoisted__Bool_4119;
                Bool_delete(hoisted__Bool_4118, hoisted__Bool_4119);
            }
        }
    }
    U32 hoisted__U32_4121 = 0;
    (void)hoisted__U32_4121;
    self->count = hoisted__U32_4121;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4418 = 1;
    (void)hoisted__U32_4418;
    U32 hoisted__U32_4419 = U32_mul(self->cap, hoisted__U32_4418);
    (void)hoisted__U32_4419;
    Type *hoisted__Type_4420 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4420;
    U64 hoisted__U64_4421 = (U64)(hoisted__U32_4419);
    (void)hoisted__U64_4421;
    Type_delete(hoisted__Type_4420, 1);
    void * new_data = malloc(hoisted__U64_4421);
    {
        U32 _re_U32_4382 = self->count;
        (void)_re_U32_4382;
        U32 _rc_U32_4382 = 0;
        (void)_rc_U32_4382;
        Bool hoisted__Bool_4417 = U32_lte(_rc_U32_4382, _re_U32_4382);
        (void)hoisted__Bool_4417;
        if (hoisted__Bool_4417) {
            while (1) {
                Bool _wcond_Bool_4383 = U32_lt(_rc_U32_4382, _re_U32_4382);
                (void)_wcond_Bool_4383;
                if (_wcond_Bool_4383) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4382);
                U32_inc(&_rc_U32_4382);
                U32 hoisted__U32_4384 = 1;
                (void)hoisted__U32_4384;
                U32 hoisted__U32_4385 = U32_mul(i, hoisted__U32_4384);
                (void)hoisted__U32_4385;
                Type *hoisted__Type_4386 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4386;
                U64 hoisted__U64_4387 = (U64)(hoisted__U32_4385);
                (void)hoisted__U64_4387;
                Type_delete(hoisted__Type_4386, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4387);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4388 = 1;
                (void)hoisted__U32_4388;
                U32 hoisted__U32_4389 = U32_mul(i, hoisted__U32_4388);
                (void)hoisted__U32_4389;
                Type *hoisted__Type_4390 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4390;
                U64 hoisted__U64_4391 = (U64)(hoisted__U32_4389);
                (void)hoisted__U64_4391;
                Type_delete(hoisted__Type_4390, 1);
                U32 hoisted__U32_4392 = 1;
                (void)hoisted__U32_4392;
                Type *hoisted__Type_4393 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4393;
                void *hoisted__v_4394 = ptr_add(new_data, hoisted__U64_4391);
                (void)hoisted__v_4394;
                (void)hoisted__v_4394;
                U64 hoisted__U64_4395 = (U64)(hoisted__U32_4392);
                (void)hoisted__U64_4395;
                Type_delete(hoisted__Type_4393, 1);
                memcpy(hoisted__v_4394, &cloned, hoisted__U64_4395);
                U32 hoisted__U32_4396 = 1;
                (void)hoisted__U32_4396;
                Type *hoisted__Type_4397 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4397;
                I32 hoisted__I32_4398 = 0;
                (void)hoisted__I32_4398;
                U64 hoisted__U64_4399 = (U64)(hoisted__U32_4396);
                (void)hoisted__U64_4399;
                Type_delete(hoisted__Type_4397, 1);
                memset(&cloned, hoisted__I32_4398, hoisted__U64_4399);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4400 = U32_gt(_rc_U32_4382, _re_U32_4382);
                (void)_wcond_Bool_4400;
                if (_wcond_Bool_4400) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4382);
                U32_dec(&_rc_U32_4382);
                U32 hoisted__U32_4401 = 1;
                (void)hoisted__U32_4401;
                U32 hoisted__U32_4402 = U32_mul(i, hoisted__U32_4401);
                (void)hoisted__U32_4402;
                Type *hoisted__Type_4403 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4403;
                U64 hoisted__U64_4404 = (U64)(hoisted__U32_4402);
                (void)hoisted__U64_4404;
                Type_delete(hoisted__Type_4403, 1);
                Bool *src = ptr_add(self->data, hoisted__U64_4404);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4405 = 1;
                (void)hoisted__U32_4405;
                U32 hoisted__U32_4406 = U32_mul(i, hoisted__U32_4405);
                (void)hoisted__U32_4406;
                Type *hoisted__Type_4407 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4407;
                U64 hoisted__U64_4408 = (U64)(hoisted__U32_4406);
                (void)hoisted__U64_4408;
                Type_delete(hoisted__Type_4407, 1);
                U32 hoisted__U32_4409 = 1;
                (void)hoisted__U32_4409;
                Type *hoisted__Type_4410 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4410;
                void *hoisted__v_4411 = ptr_add(new_data, hoisted__U64_4408);
                (void)hoisted__v_4411;
                (void)hoisted__v_4411;
                U64 hoisted__U64_4412 = (U64)(hoisted__U32_4409);
                (void)hoisted__U64_4412;
                Type_delete(hoisted__Type_4410, 1);
                memcpy(hoisted__v_4411, &cloned, hoisted__U64_4412);
                U32 hoisted__U32_4413 = 1;
                (void)hoisted__U32_4413;
                Type *hoisted__Type_4414 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4414;
                I32 hoisted__I32_4415 = 0;
                (void)hoisted__I32_4415;
                U64 hoisted__U64_4416 = (U64)(hoisted__U32_4413);
                (void)hoisted__U64_4416;
                Type_delete(hoisted__Type_4414, 1);
                memset(&cloned, hoisted__I32_4415, hoisted__U64_4416);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4422 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4422->data = new_data;
    hoisted__Vec__Bool_4422->count = self->count;
    hoisted__Vec__Bool_4422->cap = self->cap;
    (void)hoisted__Vec__Bool_4422;
    return hoisted__Vec__Bool_4422;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4423 = 16;
    (void)hoisted__U32_4423;
    return hoisted__U32_4423;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_4750 = 104;
    (void)hoisted__U32_4750;
    Type *hoisted__Type_4751 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_4751;
    U64 hoisted__U64_4752 = (U64)(hoisted__U32_4750);
    (void)hoisted__U64_4752;
    Type_delete(hoisted__Type_4751, 1);
    void * hoisted__v_4753 = malloc(hoisted__U64_4752);
    (void)hoisted__v_4753;
    U32 hoisted__U32_4754 = 0;
    (void)hoisted__U32_4754;
    I64 hoisted__I64_4755 = 1;
    (void)hoisted__I64_4755;
    Vec__Declaration *hoisted__Vec__Declaration_4756 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4756->data = hoisted__v_4753;
    hoisted__Vec__Declaration_4756->count = hoisted__U32_4754;
    hoisted__Vec__Declaration_4756->cap = hoisted__I64_4755;
    (void)hoisted__Vec__Declaration_4756;
    return hoisted__Vec__Declaration_4756;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4757 = self->count;
        (void)_re_U32_4757;
        U32 _rc_U32_4757 = 0;
        (void)_rc_U32_4757;
        Bool hoisted__Bool_4772 = U32_lte(_rc_U32_4757, _re_U32_4757);
        (void)hoisted__Bool_4772;
        if (hoisted__Bool_4772) {
            while (1) {
                Bool _wcond_Bool_4758 = U32_lt(_rc_U32_4757, _re_U32_4757);
                (void)_wcond_Bool_4758;
                if (_wcond_Bool_4758) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4757);
                U32_inc(&_rc_U32_4757);
                U32 hoisted__U32_4759 = 104;
                (void)hoisted__U32_4759;
                U32 hoisted__U32_4760 = U32_mul(i, hoisted__U32_4759);
                (void)hoisted__U32_4760;
                Type *hoisted__Type_4761 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4761;
                U64 hoisted__U64_4762 = (U64)(hoisted__U32_4760);
                (void)hoisted__U64_4762;
                Type_delete(hoisted__Type_4761, 1);
                Declaration *hoisted__Declaration_4763 = ptr_add(self->data, hoisted__U64_4762);
                (void)hoisted__Declaration_4763;
                (void)hoisted__Declaration_4763;
                Bool hoisted__Bool_4764 = 0;
                (void)hoisted__Bool_4764;
                Declaration_delete(hoisted__Declaration_4763, hoisted__Bool_4764);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4765 = U32_gt(_rc_U32_4757, _re_U32_4757);
                (void)_wcond_Bool_4765;
                if (_wcond_Bool_4765) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4757);
                U32_dec(&_rc_U32_4757);
                U32 hoisted__U32_4766 = 104;
                (void)hoisted__U32_4766;
                U32 hoisted__U32_4767 = U32_mul(i, hoisted__U32_4766);
                (void)hoisted__U32_4767;
                Type *hoisted__Type_4768 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_4768;
                U64 hoisted__U64_4769 = (U64)(hoisted__U32_4767);
                (void)hoisted__U64_4769;
                Type_delete(hoisted__Type_4768, 1);
                Declaration *hoisted__Declaration_4770 = ptr_add(self->data, hoisted__U64_4769);
                (void)hoisted__Declaration_4770;
                (void)hoisted__Declaration_4770;
                Bool hoisted__Bool_4771 = 0;
                (void)hoisted__Bool_4771;
                Declaration_delete(hoisted__Declaration_4770, hoisted__Bool_4771);
            }
        }
    }
    U32 hoisted__U32_4773 = 0;
    (void)hoisted__U32_4773;
    self->count = hoisted__U32_4773;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5070 = 104;
    (void)hoisted__U32_5070;
    U32 hoisted__U32_5071 = U32_mul(self->cap, hoisted__U32_5070);
    (void)hoisted__U32_5071;
    Type *hoisted__Type_5072 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5072;
    U64 hoisted__U64_5073 = (U64)(hoisted__U32_5071);
    (void)hoisted__U64_5073;
    Type_delete(hoisted__Type_5072, 1);
    void * new_data = malloc(hoisted__U64_5073);
    {
        U32 _re_U32_5034 = self->count;
        (void)_re_U32_5034;
        U32 _rc_U32_5034 = 0;
        (void)_rc_U32_5034;
        Bool hoisted__Bool_5069 = U32_lte(_rc_U32_5034, _re_U32_5034);
        (void)hoisted__Bool_5069;
        if (hoisted__Bool_5069) {
            while (1) {
                Bool _wcond_Bool_5035 = U32_lt(_rc_U32_5034, _re_U32_5034);
                (void)_wcond_Bool_5035;
                if (_wcond_Bool_5035) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5034);
                U32_inc(&_rc_U32_5034);
                U32 hoisted__U32_5036 = 104;
                (void)hoisted__U32_5036;
                U32 hoisted__U32_5037 = U32_mul(i, hoisted__U32_5036);
                (void)hoisted__U32_5037;
                Type *hoisted__Type_5038 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5038;
                U64 hoisted__U64_5039 = (U64)(hoisted__U32_5037);
                (void)hoisted__U64_5039;
                Type_delete(hoisted__Type_5038, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5039);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5040 = 104;
                (void)hoisted__U32_5040;
                U32 hoisted__U32_5041 = U32_mul(i, hoisted__U32_5040);
                (void)hoisted__U32_5041;
                Type *hoisted__Type_5042 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5042;
                U64 hoisted__U64_5043 = (U64)(hoisted__U32_5041);
                (void)hoisted__U64_5043;
                Type_delete(hoisted__Type_5042, 1);
                U32 hoisted__U32_5044 = 104;
                (void)hoisted__U32_5044;
                Type *hoisted__Type_5045 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5045;
                void *hoisted__v_5046 = ptr_add(new_data, hoisted__U64_5043);
                (void)hoisted__v_5046;
                (void)hoisted__v_5046;
                U64 hoisted__U64_5047 = (U64)(hoisted__U32_5044);
                (void)hoisted__U64_5047;
                Type_delete(hoisted__Type_5045, 1);
                memcpy(hoisted__v_5046, cloned, hoisted__U64_5047);
                U32 hoisted__U32_5048 = 104;
                (void)hoisted__U32_5048;
                Type *hoisted__Type_5049 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5049;
                I32 hoisted__I32_5050 = 0;
                (void)hoisted__I32_5050;
                U64 hoisted__U64_5051 = (U64)(hoisted__U32_5048);
                (void)hoisted__U64_5051;
                Type_delete(hoisted__Type_5049, 1);
                memset(cloned, hoisted__I32_5050, hoisted__U64_5051);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5052 = U32_gt(_rc_U32_5034, _re_U32_5034);
                (void)_wcond_Bool_5052;
                if (_wcond_Bool_5052) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5034);
                U32_dec(&_rc_U32_5034);
                U32 hoisted__U32_5053 = 104;
                (void)hoisted__U32_5053;
                U32 hoisted__U32_5054 = U32_mul(i, hoisted__U32_5053);
                (void)hoisted__U32_5054;
                Type *hoisted__Type_5055 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5055;
                U64 hoisted__U64_5056 = (U64)(hoisted__U32_5054);
                (void)hoisted__U64_5056;
                Type_delete(hoisted__Type_5055, 1);
                Declaration *src = ptr_add(self->data, hoisted__U64_5056);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5057 = 104;
                (void)hoisted__U32_5057;
                U32 hoisted__U32_5058 = U32_mul(i, hoisted__U32_5057);
                (void)hoisted__U32_5058;
                Type *hoisted__Type_5059 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5059;
                U64 hoisted__U64_5060 = (U64)(hoisted__U32_5058);
                (void)hoisted__U64_5060;
                Type_delete(hoisted__Type_5059, 1);
                U32 hoisted__U32_5061 = 104;
                (void)hoisted__U32_5061;
                Type *hoisted__Type_5062 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5062;
                void *hoisted__v_5063 = ptr_add(new_data, hoisted__U64_5060);
                (void)hoisted__v_5063;
                (void)hoisted__v_5063;
                U64 hoisted__U64_5064 = (U64)(hoisted__U32_5061);
                (void)hoisted__U64_5064;
                Type_delete(hoisted__Type_5062, 1);
                memcpy(hoisted__v_5063, cloned, hoisted__U64_5064);
                U32 hoisted__U32_5065 = 104;
                (void)hoisted__U32_5065;
                Type *hoisted__Type_5066 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5066;
                I32 hoisted__I32_5067 = 0;
                (void)hoisted__I32_5067;
                U64 hoisted__U64_5068 = (U64)(hoisted__U32_5065);
                (void)hoisted__U64_5068;
                Type_delete(hoisted__Type_5066, 1);
                memset(cloned, hoisted__I32_5067, hoisted__U64_5068);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5074 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5074->data = new_data;
    hoisted__Vec__Declaration_5074->count = self->count;
    hoisted__Vec__Declaration_5074->cap = self->cap;
    (void)hoisted__Vec__Declaration_5074;
    return hoisted__Vec__Declaration_5074;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5075 = 16;
    (void)hoisted__U32_5075;
    return hoisted__U32_5075;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5076 = 136;
    (void)hoisted__U32_5076;
    Type *hoisted__Type_5077 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5077;
    U64 hoisted__U64_5078 = (U64)(hoisted__U32_5076);
    (void)hoisted__U64_5078;
    Type_delete(hoisted__Type_5077, 1);
    void * hoisted__v_5079 = malloc(hoisted__U64_5078);
    (void)hoisted__v_5079;
    U32 hoisted__U32_5080 = 0;
    (void)hoisted__U32_5080;
    I64 hoisted__I64_5081 = 1;
    (void)hoisted__I64_5081;
    Vec__Expr *hoisted__Vec__Expr_5082 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5082->data = hoisted__v_5079;
    hoisted__Vec__Expr_5082->count = hoisted__U32_5080;
    hoisted__Vec__Expr_5082->cap = hoisted__I64_5081;
    (void)hoisted__Vec__Expr_5082;
    return hoisted__Vec__Expr_5082;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5083 = self->count;
        (void)_re_U32_5083;
        U32 _rc_U32_5083 = 0;
        (void)_rc_U32_5083;
        Bool hoisted__Bool_5098 = U32_lte(_rc_U32_5083, _re_U32_5083);
        (void)hoisted__Bool_5098;
        if (hoisted__Bool_5098) {
            while (1) {
                Bool _wcond_Bool_5084 = U32_lt(_rc_U32_5083, _re_U32_5083);
                (void)_wcond_Bool_5084;
                if (_wcond_Bool_5084) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5083);
                U32_inc(&_rc_U32_5083);
                U32 hoisted__U32_5085 = 136;
                (void)hoisted__U32_5085;
                U32 hoisted__U32_5086 = U32_mul(i, hoisted__U32_5085);
                (void)hoisted__U32_5086;
                Type *hoisted__Type_5087 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5087;
                U64 hoisted__U64_5088 = (U64)(hoisted__U32_5086);
                (void)hoisted__U64_5088;
                Type_delete(hoisted__Type_5087, 1);
                Expr *hoisted__Expr_5089 = ptr_add(self->data, hoisted__U64_5088);
                (void)hoisted__Expr_5089;
                (void)hoisted__Expr_5089;
                Bool hoisted__Bool_5090 = 0;
                (void)hoisted__Bool_5090;
                Expr_delete(hoisted__Expr_5089, hoisted__Bool_5090);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5091 = U32_gt(_rc_U32_5083, _re_U32_5083);
                (void)_wcond_Bool_5091;
                if (_wcond_Bool_5091) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5083);
                U32_dec(&_rc_U32_5083);
                U32 hoisted__U32_5092 = 136;
                (void)hoisted__U32_5092;
                U32 hoisted__U32_5093 = U32_mul(i, hoisted__U32_5092);
                (void)hoisted__U32_5093;
                Type *hoisted__Type_5094 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5094;
                U64 hoisted__U64_5095 = (U64)(hoisted__U32_5093);
                (void)hoisted__U64_5095;
                Type_delete(hoisted__Type_5094, 1);
                Expr *hoisted__Expr_5096 = ptr_add(self->data, hoisted__U64_5095);
                (void)hoisted__Expr_5096;
                (void)hoisted__Expr_5096;
                Bool hoisted__Bool_5097 = 0;
                (void)hoisted__Bool_5097;
                Expr_delete(hoisted__Expr_5096, hoisted__Bool_5097);
            }
        }
    }
    U32 hoisted__U32_5099 = 0;
    (void)hoisted__U32_5099;
    self->count = hoisted__U32_5099;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5396 = 136;
    (void)hoisted__U32_5396;
    U32 hoisted__U32_5397 = U32_mul(self->cap, hoisted__U32_5396);
    (void)hoisted__U32_5397;
    Type *hoisted__Type_5398 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5398;
    U64 hoisted__U64_5399 = (U64)(hoisted__U32_5397);
    (void)hoisted__U64_5399;
    Type_delete(hoisted__Type_5398, 1);
    void * new_data = malloc(hoisted__U64_5399);
    {
        U32 _re_U32_5360 = self->count;
        (void)_re_U32_5360;
        U32 _rc_U32_5360 = 0;
        (void)_rc_U32_5360;
        Bool hoisted__Bool_5395 = U32_lte(_rc_U32_5360, _re_U32_5360);
        (void)hoisted__Bool_5395;
        if (hoisted__Bool_5395) {
            while (1) {
                Bool _wcond_Bool_5361 = U32_lt(_rc_U32_5360, _re_U32_5360);
                (void)_wcond_Bool_5361;
                if (_wcond_Bool_5361) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5360);
                U32_inc(&_rc_U32_5360);
                U32 hoisted__U32_5362 = 136;
                (void)hoisted__U32_5362;
                U32 hoisted__U32_5363 = U32_mul(i, hoisted__U32_5362);
                (void)hoisted__U32_5363;
                Type *hoisted__Type_5364 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5364;
                U64 hoisted__U64_5365 = (U64)(hoisted__U32_5363);
                (void)hoisted__U64_5365;
                Type_delete(hoisted__Type_5364, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5365);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5366 = 136;
                (void)hoisted__U32_5366;
                U32 hoisted__U32_5367 = U32_mul(i, hoisted__U32_5366);
                (void)hoisted__U32_5367;
                Type *hoisted__Type_5368 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5368;
                U64 hoisted__U64_5369 = (U64)(hoisted__U32_5367);
                (void)hoisted__U64_5369;
                Type_delete(hoisted__Type_5368, 1);
                U32 hoisted__U32_5370 = 136;
                (void)hoisted__U32_5370;
                Type *hoisted__Type_5371 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5371;
                void *hoisted__v_5372 = ptr_add(new_data, hoisted__U64_5369);
                (void)hoisted__v_5372;
                (void)hoisted__v_5372;
                U64 hoisted__U64_5373 = (U64)(hoisted__U32_5370);
                (void)hoisted__U64_5373;
                Type_delete(hoisted__Type_5371, 1);
                memcpy(hoisted__v_5372, cloned, hoisted__U64_5373);
                U32 hoisted__U32_5374 = 136;
                (void)hoisted__U32_5374;
                Type *hoisted__Type_5375 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5375;
                I32 hoisted__I32_5376 = 0;
                (void)hoisted__I32_5376;
                U64 hoisted__U64_5377 = (U64)(hoisted__U32_5374);
                (void)hoisted__U64_5377;
                Type_delete(hoisted__Type_5375, 1);
                memset(cloned, hoisted__I32_5376, hoisted__U64_5377);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5378 = U32_gt(_rc_U32_5360, _re_U32_5360);
                (void)_wcond_Bool_5378;
                if (_wcond_Bool_5378) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5360);
                U32_dec(&_rc_U32_5360);
                U32 hoisted__U32_5379 = 136;
                (void)hoisted__U32_5379;
                U32 hoisted__U32_5380 = U32_mul(i, hoisted__U32_5379);
                (void)hoisted__U32_5380;
                Type *hoisted__Type_5381 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5381;
                U64 hoisted__U64_5382 = (U64)(hoisted__U32_5380);
                (void)hoisted__U64_5382;
                Type_delete(hoisted__Type_5381, 1);
                Expr *src = ptr_add(self->data, hoisted__U64_5382);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5383 = 136;
                (void)hoisted__U32_5383;
                U32 hoisted__U32_5384 = U32_mul(i, hoisted__U32_5383);
                (void)hoisted__U32_5384;
                Type *hoisted__Type_5385 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5385;
                U64 hoisted__U64_5386 = (U64)(hoisted__U32_5384);
                (void)hoisted__U64_5386;
                Type_delete(hoisted__Type_5385, 1);
                U32 hoisted__U32_5387 = 136;
                (void)hoisted__U32_5387;
                Type *hoisted__Type_5388 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5388;
                void *hoisted__v_5389 = ptr_add(new_data, hoisted__U64_5386);
                (void)hoisted__v_5389;
                (void)hoisted__v_5389;
                U64 hoisted__U64_5390 = (U64)(hoisted__U32_5387);
                (void)hoisted__U64_5390;
                Type_delete(hoisted__Type_5388, 1);
                memcpy(hoisted__v_5389, cloned, hoisted__U64_5390);
                U32 hoisted__U32_5391 = 136;
                (void)hoisted__U32_5391;
                Type *hoisted__Type_5392 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5392;
                I32 hoisted__I32_5393 = 0;
                (void)hoisted__I32_5393;
                U64 hoisted__U64_5394 = (U64)(hoisted__U32_5391);
                (void)hoisted__U64_5394;
                Type_delete(hoisted__Type_5392, 1);
                memset(cloned, hoisted__I32_5393, hoisted__U64_5394);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5400 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5400->data = new_data;
    hoisted__Vec__Expr_5400->count = self->count;
    hoisted__Vec__Expr_5400->cap = self->cap;
    (void)hoisted__Vec__Expr_5400;
    return hoisted__Vec__Expr_5400;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5401 = 16;
    (void)hoisted__U32_5401;
    return hoisted__U32_5401;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5402 = 8;
    (void)hoisted__U32_5402;
    Type *hoisted__Type_5403 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5403;
    U64 hoisted__U64_5404 = (U64)(hoisted__U32_5402);
    (void)hoisted__U64_5404;
    Type_delete(hoisted__Type_5403, 1);
    void * hoisted__v_5405 = malloc(hoisted__U64_5404);
    (void)hoisted__v_5405;
    U32 hoisted__U32_5406 = 0;
    (void)hoisted__U32_5406;
    I64 hoisted__I64_5407 = 1;
    (void)hoisted__I64_5407;
    Vec__I64 *hoisted__Vec__I64_5408 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5408->data = hoisted__v_5405;
    hoisted__Vec__I64_5408->count = hoisted__U32_5406;
    hoisted__Vec__I64_5408->cap = hoisted__I64_5407;
    (void)hoisted__Vec__I64_5408;
    return hoisted__Vec__I64_5408;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5409 = self->count;
        (void)_re_U32_5409;
        U32 _rc_U32_5409 = 0;
        (void)_rc_U32_5409;
        Bool hoisted__Bool_5424 = U32_lte(_rc_U32_5409, _re_U32_5409);
        (void)hoisted__Bool_5424;
        if (hoisted__Bool_5424) {
            while (1) {
                Bool _wcond_Bool_5410 = U32_lt(_rc_U32_5409, _re_U32_5409);
                (void)_wcond_Bool_5410;
                if (_wcond_Bool_5410) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5409);
                U32_inc(&_rc_U32_5409);
                U32 hoisted__U32_5411 = 8;
                (void)hoisted__U32_5411;
                U32 hoisted__U32_5412 = U32_mul(i, hoisted__U32_5411);
                (void)hoisted__U32_5412;
                Type *hoisted__Type_5413 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5413;
                U64 hoisted__U64_5414 = (U64)(hoisted__U32_5412);
                (void)hoisted__U64_5414;
                Type_delete(hoisted__Type_5413, 1);
                I64 *hoisted__I64_5415 = ptr_add(self->data, hoisted__U64_5414);
                (void)hoisted__I64_5415;
                (void)hoisted__I64_5415;
                Bool hoisted__Bool_5416 = 0;
                (void)hoisted__Bool_5416;
                I64_delete(hoisted__I64_5415, hoisted__Bool_5416);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5417 = U32_gt(_rc_U32_5409, _re_U32_5409);
                (void)_wcond_Bool_5417;
                if (_wcond_Bool_5417) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5409);
                U32_dec(&_rc_U32_5409);
                U32 hoisted__U32_5418 = 8;
                (void)hoisted__U32_5418;
                U32 hoisted__U32_5419 = U32_mul(i, hoisted__U32_5418);
                (void)hoisted__U32_5419;
                Type *hoisted__Type_5420 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5420;
                U64 hoisted__U64_5421 = (U64)(hoisted__U32_5419);
                (void)hoisted__U64_5421;
                Type_delete(hoisted__Type_5420, 1);
                I64 *hoisted__I64_5422 = ptr_add(self->data, hoisted__U64_5421);
                (void)hoisted__I64_5422;
                (void)hoisted__I64_5422;
                Bool hoisted__Bool_5423 = 0;
                (void)hoisted__Bool_5423;
                I64_delete(hoisted__I64_5422, hoisted__Bool_5423);
            }
        }
    }
    U32 hoisted__U32_5425 = 0;
    (void)hoisted__U32_5425;
    self->count = hoisted__U32_5425;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5722 = 8;
    (void)hoisted__U32_5722;
    U32 hoisted__U32_5723 = U32_mul(self->cap, hoisted__U32_5722);
    (void)hoisted__U32_5723;
    Type *hoisted__Type_5724 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_5724;
    U64 hoisted__U64_5725 = (U64)(hoisted__U32_5723);
    (void)hoisted__U64_5725;
    Type_delete(hoisted__Type_5724, 1);
    void * new_data = malloc(hoisted__U64_5725);
    {
        U32 _re_U32_5686 = self->count;
        (void)_re_U32_5686;
        U32 _rc_U32_5686 = 0;
        (void)_rc_U32_5686;
        Bool hoisted__Bool_5721 = U32_lte(_rc_U32_5686, _re_U32_5686);
        (void)hoisted__Bool_5721;
        if (hoisted__Bool_5721) {
            while (1) {
                Bool _wcond_Bool_5687 = U32_lt(_rc_U32_5686, _re_U32_5686);
                (void)_wcond_Bool_5687;
                if (_wcond_Bool_5687) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5686);
                U32_inc(&_rc_U32_5686);
                U32 hoisted__U32_5688 = 8;
                (void)hoisted__U32_5688;
                U32 hoisted__U32_5689 = U32_mul(i, hoisted__U32_5688);
                (void)hoisted__U32_5689;
                Type *hoisted__Type_5690 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5690;
                U64 hoisted__U64_5691 = (U64)(hoisted__U32_5689);
                (void)hoisted__U64_5691;
                Type_delete(hoisted__Type_5690, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5691);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5692 = 8;
                (void)hoisted__U32_5692;
                U32 hoisted__U32_5693 = U32_mul(i, hoisted__U32_5692);
                (void)hoisted__U32_5693;
                Type *hoisted__Type_5694 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5694;
                U64 hoisted__U64_5695 = (U64)(hoisted__U32_5693);
                (void)hoisted__U64_5695;
                Type_delete(hoisted__Type_5694, 1);
                U32 hoisted__U32_5696 = 8;
                (void)hoisted__U32_5696;
                Type *hoisted__Type_5697 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5697;
                void *hoisted__v_5698 = ptr_add(new_data, hoisted__U64_5695);
                (void)hoisted__v_5698;
                (void)hoisted__v_5698;
                U64 hoisted__U64_5699 = (U64)(hoisted__U32_5696);
                (void)hoisted__U64_5699;
                Type_delete(hoisted__Type_5697, 1);
                memcpy(hoisted__v_5698, &cloned, hoisted__U64_5699);
                U32 hoisted__U32_5700 = 8;
                (void)hoisted__U32_5700;
                Type *hoisted__Type_5701 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5701;
                I32 hoisted__I32_5702 = 0;
                (void)hoisted__I32_5702;
                U64 hoisted__U64_5703 = (U64)(hoisted__U32_5700);
                (void)hoisted__U64_5703;
                Type_delete(hoisted__Type_5701, 1);
                memset(&cloned, hoisted__I32_5702, hoisted__U64_5703);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5704 = U32_gt(_rc_U32_5686, _re_U32_5686);
                (void)_wcond_Bool_5704;
                if (_wcond_Bool_5704) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5686);
                U32_dec(&_rc_U32_5686);
                U32 hoisted__U32_5705 = 8;
                (void)hoisted__U32_5705;
                U32 hoisted__U32_5706 = U32_mul(i, hoisted__U32_5705);
                (void)hoisted__U32_5706;
                Type *hoisted__Type_5707 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5707;
                U64 hoisted__U64_5708 = (U64)(hoisted__U32_5706);
                (void)hoisted__U64_5708;
                Type_delete(hoisted__Type_5707, 1);
                I64 *src = ptr_add(self->data, hoisted__U64_5708);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5709 = 8;
                (void)hoisted__U32_5709;
                U32 hoisted__U32_5710 = U32_mul(i, hoisted__U32_5709);
                (void)hoisted__U32_5710;
                Type *hoisted__Type_5711 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5711;
                U64 hoisted__U64_5712 = (U64)(hoisted__U32_5710);
                (void)hoisted__U64_5712;
                Type_delete(hoisted__Type_5711, 1);
                U32 hoisted__U32_5713 = 8;
                (void)hoisted__U32_5713;
                Type *hoisted__Type_5714 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5714;
                void *hoisted__v_5715 = ptr_add(new_data, hoisted__U64_5712);
                (void)hoisted__v_5715;
                (void)hoisted__v_5715;
                U64 hoisted__U64_5716 = (U64)(hoisted__U32_5713);
                (void)hoisted__U64_5716;
                Type_delete(hoisted__Type_5714, 1);
                memcpy(hoisted__v_5715, &cloned, hoisted__U64_5716);
                U32 hoisted__U32_5717 = 8;
                (void)hoisted__U32_5717;
                Type *hoisted__Type_5718 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_5718;
                I32 hoisted__I32_5719 = 0;
                (void)hoisted__I32_5719;
                U64 hoisted__U64_5720 = (U64)(hoisted__U32_5717);
                (void)hoisted__U64_5720;
                Type_delete(hoisted__Type_5718, 1);
                memset(&cloned, hoisted__I32_5719, hoisted__U64_5720);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5726 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5726->data = new_data;
    hoisted__Vec__I64_5726->count = self->count;
    hoisted__Vec__I64_5726->cap = self->cap;
    (void)hoisted__Vec__I64_5726;
    return hoisted__Vec__I64_5726;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5727 = 16;
    (void)hoisted__U32_5727;
    return hoisted__U32_5727;
}

void panic(Str * loc_str, Array__Str * parts) {
    U32 hoisted__U32_6826 = 3;
    (void)hoisted__U32_6826;
    Array__Str *_va_Array_189 = Array__Str_new(hoisted__U32_6826);
    (void)_va_Array_189;
    U32 hoisted__U32_6827 = 0;
    (void)hoisted__U32_6827;
    Str *hoisted__Str_6828 = Str_clone(loc_str);
    (void)hoisted__Str_6828;
    Array__Str_set_init(_va_Array_189, hoisted__U32_6827, hoisted__Str_6828);
    U32 hoisted__U32_6829 = 1;
    (void)hoisted__U32_6829;
    Str hoisted__Str_6830 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6830;
    Array__Str_set_init(_va_Array_189, hoisted__U32_6829, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6830; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
    Array__Str *hoisted__Array__Str_6831 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6831;
    U32 hoisted__U32_6832 = 2;
    (void)hoisted__U32_6832;
    Str *hoisted__Str_6833 = format(hoisted__Array__Str_6831);
    (void)hoisted__Str_6833;
    Array__Str_set_init(_va_Array_189, hoisted__U32_6832, hoisted__Str_6833);
    Array__Str_delete(parts, 1);
    println(_va_Array_189);
    I64 hoisted__I64_6834 = 1;
    (void)hoisted__I64_6834;
    exit(hoisted__I64_6834);
}

void UNREACHABLE(Str * loc_str) {
    U32 hoisted__U32_6841 = 1;
    (void)hoisted__U32_6841;
    Array__Str *_va_Array_191 = Array__Str_new(hoisted__U32_6841);
    (void)_va_Array_191;
    U32 hoisted__U32_6842 = 0;
    (void)hoisted__U32_6842;
    Str hoisted__Str_6843 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6843;
    Array__Str_set_init(_va_Array_191, hoisted__U32_6842, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6843; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
    panic(loc_str, _va_Array_191);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_6847 = not(cond);
    (void)hoisted__Bool_6847;
    if (hoisted__Bool_6847) {
        U32 hoisted__U32_6844 = 1;
        (void)hoisted__U32_6844;
        Array__Str *_va_Array_192 = Array__Str_new(hoisted__U32_6844);
        (void)_va_Array_192;
        U32 hoisted__U32_6845 = 0;
        (void)hoisted__U32_6845;
        Str hoisted__Str_6846 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_6846;
        Array__Str_set_init(_va_Array_192, hoisted__U32_6845, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6846; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        panic(loc_str, _va_Array_192);
    }
    Bool hoisted__Bool_6848 = 1;
    (void)hoisted__Bool_6848;
    return hoisted__Bool_6848;
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6856 = parts;
        (void)_fc_Array__Str_6856;
        (void)_fc_Array__Str_6856;
        U32 _fi_USize_6856 = 0;
        (void)_fi_USize_6856;
        I64 _forin_err_kind_6856 = 0;
        (void)_forin_err_kind_6856;
        OutOfBounds *_forin_OutOfBounds_6856 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_6856->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_6856;
        while (1) {
            U32 hoisted__U32_6862 = Array__Str_len(_fc_Array__Str_6856);
            (void)hoisted__U32_6862;
            Bool _wcond_Bool_6857 = U32_lt(_fi_USize_6856, hoisted__U32_6862);
            (void)_wcond_Bool_6857;
            if (_wcond_Bool_6857) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_6856, &_fi_USize_6856, &_forin_err_kind_6856, _forin_OutOfBounds_6856);
            I64 hoisted__I64_6863 = 0;
            (void)hoisted__I64_6863;
            Bool hoisted__Bool_6864 = I64_eq(_forin_err_kind_6856, hoisted__I64_6863);
            (void)hoisted__Bool_6864;
            Bool hoisted__Bool_6865 = not(hoisted__Bool_6864);
            (void)hoisted__Bool_6865;
            if (hoisted__Bool_6865) {
                U32 hoisted__U32_6858 = 1;
                (void)hoisted__U32_6858;
                Array__Str *_va_Array_194 = Array__Str_new(hoisted__U32_6858);
                (void)_va_Array_194;
                U32 hoisted__U32_6859 = 0;
                (void)hoisted__U32_6859;
                Str hoisted__Str_6860 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6860;
                Array__Str_set_init(_va_Array_194, hoisted__U32_6859, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_6860; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
                Str hoisted__Str_6861 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_6861;
                panic(&hoisted__Str_6861, _va_Array_194);
                Str_delete(&hoisted__Str_6861, (Bool){0});
            }
            U32 hoisted__U32_6866 = 1;
            (void)hoisted__U32_6866;
            U32 hoisted__U32_6867 = U32_add(_fi_USize_6856, hoisted__U32_6866);
            (void)hoisted__U32_6867;
            _fi_USize_6856 = hoisted__U32_6867;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_6856, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_6905 = ptr_eq(p, NULL);
    (void)hoisted__Bool_6905;
    return hoisted__Bool_6905;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6914 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6914;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6914;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6915 = 0;
    (void)hoisted__U32_6915;
    U64 hoisted__U64_6916 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6915); });
    (void)hoisted__U64_6916;
    return hoisted__U64_6916;
}

U32 Range_size(void) {
    U32 hoisted__U32_6940 = 16;
    (void)hoisted__U32_6940;
    return hoisted__U32_6940;
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_7046 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7046;
    I64 hoisted__I64_7047 = 3;
    (void)hoisted__I64_7047;
    assert_eq__I64(&hoisted__Str_7046, result, hoisted__I64_7047);
    Str_delete(&hoisted__Str_7046, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_7054 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7054;
    I64 hoisted__I64_7055 = 15;
    (void)hoisted__I64_7055;
    assert_eq__I64(&hoisted__Str_7054, result, hoisted__I64_7055);
    Str_delete(&hoisted__Str_7054, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_7062 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7062;
    I64 hoisted__I64_7063 = 26;
    (void)hoisted__I64_7063;
    assert_eq__I64(&hoisted__Str_7062, result, hoisted__I64_7063);
    Str_delete(&hoisted__Str_7062, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7066 = (Str){.c_str = (void *)"test/constfold.til:33:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7066;
    Str hoisted__Str_7067 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7067;
    assert_eq__Str(&hoisted__Str_7066, &result, &hoisted__Str_7067);
    Str_delete(&hoisted__Str_7066, (Bool){0});
    Str_delete(&hoisted__Str_7067, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7088 = (Str){.c_str = (void *)"test/constfold.til:49:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7088;
    Str hoisted__Str_7089 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7089;
    assert_eq__Str(&hoisted__Str_7088, &r, &hoisted__Str_7089);
    Str_delete(&hoisted__Str_7088, (Bool){0});
    Str_delete(&hoisted__Str_7089, (Bool){0});
    Str_delete(&r, (Bool){0});
    Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7093 = (Str){.c_str = (void *)"test/constfold.til:51:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7093;
    Str hoisted__Str_7094 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7094;
    assert_eq__Str(&hoisted__Str_7093, &r2, &hoisted__Str_7094);
    Str_delete(&hoisted__Str_7093, (Bool){0});
    Str_delete(&hoisted__Str_7094, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_7425 = (Str){.c_str = (void *)"test/constfold.til:104:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7425;
    assert_eq__Str(&hoisted__Str_7425, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_7425, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_7426 = (Str){.c_str = (void *)"test/constfold.til:105:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7426;
    assert_eq__Str(&hoisted__Str_7426, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_7426, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_7428 = (Str){.c_str = (void *)"test/constfold.til:112:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7428;
    I64 hoisted__I64_7429 = 8;
    (void)hoisted__I64_7429;
    assert_eq__I64(&hoisted__Str_7428, result, hoisted__I64_7429);
    Str_delete(&hoisted__Str_7428, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_7432 = (Str){.c_str = (void *)"test/constfold.til:117:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7432;
    Bool hoisted__Bool_7433 = 1;
    (void)hoisted__Bool_7433;
    assert(&hoisted__Str_7432, hoisted__Bool_7433);
    Str_delete(&hoisted__Str_7432, (Bool){0});
    Str hoisted__Str_7436 = (Str){.c_str = (void *)"test/constfold.til:118:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7436;
    Bool hoisted__Bool_7437 = 1;
    (void)hoisted__Bool_7437;
    assert(&hoisted__Str_7436, hoisted__Bool_7437);
    Str_delete(&hoisted__Str_7436, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_7442 = (Str){.c_str = (void *)"test/constfold.til:129:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7442;
    Str hoisted__Str_7443 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7443;
    Str hoisted__Str_7444 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7444;
    assert_eq__Str(&hoisted__Str_7442, &hoisted__Str_7443, &hoisted__Str_7444);
    Str_delete(&hoisted__Str_7442, (Bool){0});
    Str_delete(&hoisted__Str_7443, (Bool){0});
    Str_delete(&hoisted__Str_7444, (Bool){0});
    Str hoisted__Str_7447 = (Str){.c_str = (void *)"test/constfold.til:131:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7447;
    Str hoisted__Str_7448 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7448;
    Str hoisted__Str_7449 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7449;
    assert_eq__Str(&hoisted__Str_7447, &hoisted__Str_7448, &hoisted__Str_7449);
    Str_delete(&hoisted__Str_7447, (Bool){0});
    Str_delete(&hoisted__Str_7448, (Bool){0});
    Str_delete(&hoisted__Str_7449, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_7454 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_7454;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_7454;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_7455 = 0;
    (void)hoisted__U32_7455;
    U64 hoisted__U64_7456 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7455); });
    (void)hoisted__U64_7456;
    return hoisted__U64_7456;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_7480 = 16;
    (void)hoisted__U32_7480;
    return hoisted__U32_7480;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_7481 = (Str){.c_str = (void *)"test/constfold.til:153:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7481;
    I64 hoisted__I64_7482 = 42;
    (void)hoisted__I64_7482;
    assert_eq__I64(&hoisted__Str_7481, v.x, hoisted__I64_7482);
    Str_delete(&hoisted__Str_7481, (Bool){0});
    Str hoisted__Str_7483 = (Str){.c_str = (void *)"test/constfold.til:154:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7483;
    I64 hoisted__I64_7484 = 99;
    (void)hoisted__I64_7484;
    assert_eq__I64(&hoisted__Str_7483, v.y, hoisted__I64_7484);
    Str_delete(&hoisted__Str_7483, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_7487 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7487;
    I64 hoisted__I64_7488 = 10;
    (void)hoisted__I64_7488;
    assert_eq__I64(&hoisted__Str_7487, p.x, hoisted__I64_7488);
    Str_delete(&hoisted__Str_7487, (Bool){0});
    Str hoisted__Str_7489 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7489;
    I64 hoisted__I64_7490 = 20;
    (void)hoisted__I64_7490;
    assert_eq__I64(&hoisted__Str_7489, p.y, hoisted__I64_7490);
    Str_delete(&hoisted__Str_7489, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_7496 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_7496;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_7496;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_7497 = 0;
    (void)hoisted__U32_7497;
    U64 hoisted__U64_7498 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7497); });
    (void)hoisted__U64_7498;
    return hoisted__U64_7498;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_7522 = 32;
    (void)hoisted__U32_7522;
    return hoisted__U32_7522;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_7523 = (Str){.c_str = (void *)"test/constfold.til:177:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7523;
    I64 hoisted__I64_7524 = 5;
    (void)hoisted__I64_7524;
    assert_eq__I64(&hoisted__Str_7523, r.top_left.x, hoisted__I64_7524);
    Str_delete(&hoisted__Str_7523, (Bool){0});
    Str hoisted__Str_7525 = (Str){.c_str = (void *)"test/constfold.til:178:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7525;
    I64 hoisted__I64_7526 = 10;
    (void)hoisted__I64_7526;
    assert_eq__I64(&hoisted__Str_7525, r.top_left.y, hoisted__I64_7526);
    Str_delete(&hoisted__Str_7525, (Bool){0});
    Str hoisted__Str_7527 = (Str){.c_str = (void *)"test/constfold.til:179:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7527;
    I64 hoisted__I64_7528 = 100;
    (void)hoisted__I64_7528;
    assert_eq__I64(&hoisted__Str_7527, r.bottom_right.x, hoisted__I64_7528);
    Str_delete(&hoisted__Str_7527, (Bool){0});
    Str hoisted__Str_7529 = (Str){.c_str = (void *)"test/constfold.til:180:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7529;
    I64 hoisted__I64_7530 = 200;
    (void)hoisted__I64_7530;
    assert_eq__I64(&hoisted__Str_7529, r.bottom_right.y, hoisted__I64_7530);
    Str_delete(&hoisted__Str_7529, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_7532 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_7532;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_7532;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_7533 = 0;
    (void)hoisted__U32_7533;
    U64 hoisted__U64_7534 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7533); });
    (void)hoisted__U64_7534;
    return hoisted__U64_7534;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_7567 = 12;
    (void)hoisted__U32_7567;
    return hoisted__U32_7567;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_7571 = (Str){.c_str = (void *)"test/constfold.til:203:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7571;
    Str *hoisted__Str_7572 = F32_to_str(v.x);
    (void)hoisted__Str_7572;
    Str hoisted__Str_7573 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7573;
    assert_eq__Str(&hoisted__Str_7571, hoisted__Str_7572, &hoisted__Str_7573);
    Str_delete(&hoisted__Str_7571, (Bool){0});
    Str_delete(hoisted__Str_7572, 1);
    Str_delete(&hoisted__Str_7573, (Bool){0});
    Str hoisted__Str_7574 = (Str){.c_str = (void *)"test/constfold.til:204:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7574;
    Str *hoisted__Str_7575 = F32_to_str(v.y);
    (void)hoisted__Str_7575;
    Str hoisted__Str_7576 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7576;
    assert_eq__Str(&hoisted__Str_7574, hoisted__Str_7575, &hoisted__Str_7576);
    Str_delete(&hoisted__Str_7574, (Bool){0});
    Str_delete(hoisted__Str_7575, 1);
    Str_delete(&hoisted__Str_7576, (Bool){0});
    Str hoisted__Str_7577 = (Str){.c_str = (void *)"test/constfold.til:205:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7577;
    Str *hoisted__Str_7578 = F32_to_str(v.z);
    (void)hoisted__Str_7578;
    Str hoisted__Str_7579 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7579;
    assert_eq__Str(&hoisted__Str_7577, hoisted__Str_7578, &hoisted__Str_7579);
    Str_delete(&hoisted__Str_7577, (Bool){0});
    Str_delete(hoisted__Str_7578, 1);
    Str_delete(&hoisted__Str_7579, (Bool){0});
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
    Bool hoisted__Bool_7584 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7584;
    if (hoisted__Bool_7584) {
        Bool hoisted__Bool_7581 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_7581;
        { Bool _ret_val = hoisted__Bool_7581;
                return _ret_val; }
    }
    Bool hoisted__Bool_7585 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7585;
    if (hoisted__Bool_7585) {
        Bool hoisted__Bool_7582 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_7582;
        { Bool _ret_val = hoisted__Bool_7582;
                return _ret_val; }
    }
    Bool hoisted__Bool_7586 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7586;
    if (hoisted__Bool_7586) {
        Bool hoisted__Bool_7583 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_7583;
        { Bool _ret_val = hoisted__Bool_7583;
                return _ret_val; }
    }
    Bool hoisted__Bool_7587 = 0;
    (void)hoisted__Bool_7587;
    return hoisted__Bool_7587;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_7595 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7595;
    if (hoisted__Bool_7595) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_7596 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7596;
    if (hoisted__Bool_7596) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_7597 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_7597;
    if (hoisted__Bool_7597) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_7598 = (Str){.c_str = (void *)"Color.clone:210:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7598;
    UNREACHABLE(&hoisted__Str_7598);
    Str_delete(&hoisted__Str_7598, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_7599 = 4;
    (void)hoisted__U32_7599;
    return hoisted__U32_7599;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_7600 = (Str){.c_str = (void *)"test/constfold.til:215:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7600;
    Bool hoisted__Bool_7601 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7601;
    assert(&hoisted__Str_7600, hoisted__Bool_7601);
    Str_delete(&hoisted__Str_7600, (Bool){0});
    Bool hoisted__Bool_7602 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7602;
    Str hoisted__Str_7603 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7603;
    Bool hoisted__Bool_7604 = not(hoisted__Bool_7602);
    (void)hoisted__Bool_7604;
    assert(&hoisted__Str_7603, hoisted__Bool_7604);
    Str_delete(&hoisted__Str_7603, (Bool){0});
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
    Bool hoisted__Bool_7605 = is(self, other);
    (void)hoisted__Bool_7605;
    return hoisted__Bool_7605;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7623 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7623;
    if (hoisted__Bool_7623) {
        I64 *hoisted__I64_7619 = get_payload(self);
        (void)hoisted__I64_7619;
        (void)hoisted__I64_7619;
        Bool hoisted__Bool_7620 = 0;
        (void)hoisted__Bool_7620;
        I64_delete(hoisted__I64_7619, hoisted__Bool_7620);
    }
    Bool hoisted__Bool_7624 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7624;
    if (hoisted__Bool_7624) {
        Str *hoisted__Str_7621 = get_payload(self);
        (void)hoisted__Str_7621;
        (void)hoisted__Str_7621;
        Bool hoisted__Bool_7622 = 0;
        (void)hoisted__Bool_7622;
        Str_delete(hoisted__Str_7621, hoisted__Bool_7622);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_7649 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7649;
    if (hoisted__Bool_7649) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_7646 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_7646;
        { Token * _ret_val = hoisted__Token_7646;
                return _ret_val; }
    }
    Bool hoisted__Bool_7650 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_7650;
    if (hoisted__Bool_7650) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_7647 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_7647;
        Token *hoisted__Token_7648 = Token_Name(hoisted__Str_7647);
        (void)hoisted__Token_7648;
        { Token * _ret_val = hoisted__Token_7648;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_7651 = 24;
    (void)hoisted__U32_7651;
    return hoisted__U32_7651;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_7653 = (Str){.c_str = (void *)"test/constfold.til:224:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7653;
    Bool hoisted__Bool_7654 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7654;
    assert(&hoisted__Str_7653, hoisted__Bool_7654);
    Str_delete(&hoisted__Str_7653, (Bool){0});
    Bool hoisted__Bool_7655 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7655;
    Str hoisted__Str_7656 = (Str){.c_str = (void *)"test/constfold.til:225:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7656;
    Bool hoisted__Bool_7657 = not(hoisted__Bool_7655);
    (void)hoisted__Bool_7657;
    assert(&hoisted__Str_7656, hoisted__Bool_7657);
    Str_delete(&hoisted__Str_7656, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_7658 = (Str){.c_str = (void *)"test/constfold.til:234:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7658;
    Bool hoisted__Bool_7659 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_7659;
    assert(&hoisted__Str_7658, hoisted__Bool_7659);
    Str_delete(&hoisted__Str_7658, (Bool){0});
    Bool hoisted__Bool_7660 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_7660;
    Str hoisted__Str_7661 = (Str){.c_str = (void *)"test/constfold.til:235:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7661;
    Bool hoisted__Bool_7662 = not(hoisted__Bool_7660);
    (void)hoisted__Bool_7662;
    assert(&hoisted__Str_7661, hoisted__Bool_7662);
    Str_delete(&hoisted__Str_7661, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_7665 = (Str){.c_str = (void *)"test/constfold.til:246:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7665;
    Bool hoisted__Bool_7666 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_7666;
    assert(&hoisted__Str_7665, hoisted__Bool_7666);
    Str_delete(&hoisted__Str_7665, (Bool){0});
    Bool hoisted__Bool_7667 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_7667;
    Str hoisted__Str_7668 = (Str){.c_str = (void *)"test/constfold.til:247:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7668;
    Bool hoisted__Bool_7669 = not(hoisted__Bool_7667);
    (void)hoisted__Bool_7669;
    assert(&hoisted__Str_7668, hoisted__Bool_7669);
    Str_delete(&hoisted__Str_7668, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_7681 = I64_neq(a, b);
    (void)hoisted__Bool_7681;
    if (hoisted__Bool_7681) {
        U32 hoisted__U32_7670 = 5;
        (void)hoisted__U32_7670;
        Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7670);
        (void)_va_Array_210;
        U32 hoisted__U32_7671 = 0;
        (void)hoisted__U32_7671;
        Str hoisted__Str_7672 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7672;
        Array__Str_set_init(_va_Array_210, hoisted__U32_7671, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7672; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_7673 = 1;
        (void)hoisted__U32_7673;
        Str *hoisted__Str_7674 = I64_to_str(a);
        (void)hoisted__Str_7674;
        Array__Str_set_init(_va_Array_210, hoisted__U32_7673, hoisted__Str_7674);
        U32 hoisted__U32_7675 = 2;
        (void)hoisted__U32_7675;
        Str hoisted__Str_7676 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7676;
        Array__Str_set_init(_va_Array_210, hoisted__U32_7675, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7676; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_7677 = 3;
        (void)hoisted__U32_7677;
        Str *hoisted__Str_7678 = I64_to_str(b);
        (void)hoisted__Str_7678;
        Array__Str_set_init(_va_Array_210, hoisted__U32_7677, hoisted__Str_7678);
        U32 hoisted__U32_7679 = 4;
        (void)hoisted__U32_7679;
        Str hoisted__Str_7680 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7680;
        Array__Str_set_init(_va_Array_210, hoisted__U32_7679, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7680; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        panic(loc_str, _va_Array_210);
    }
}

void assert_eq__Str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_7693 = Str_neq(a, b);
    (void)hoisted__Bool_7693;
    if (hoisted__Bool_7693) {
        U32 hoisted__U32_7682 = 5;
        (void)hoisted__U32_7682;
        Array__Str *_va_Array_211 = Array__Str_new(hoisted__U32_7682);
        (void)_va_Array_211;
        U32 hoisted__U32_7683 = 0;
        (void)hoisted__U32_7683;
        Str hoisted__Str_7684 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7684;
        Array__Str_set_init(_va_Array_211, hoisted__U32_7683, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7684; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_7685 = 1;
        (void)hoisted__U32_7685;
        Str *hoisted__Str_7686 = Str_to_str(a);
        (void)hoisted__Str_7686;
        Array__Str_set_init(_va_Array_211, hoisted__U32_7685, hoisted__Str_7686);
        U32 hoisted__U32_7687 = 2;
        (void)hoisted__U32_7687;
        Str hoisted__Str_7688 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7688;
        Array__Str_set_init(_va_Array_211, hoisted__U32_7687, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7688; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        U32 hoisted__U32_7689 = 3;
        (void)hoisted__U32_7689;
        Str *hoisted__Str_7690 = Str_to_str(b);
        (void)hoisted__Str_7690;
        Array__Str_set_init(_va_Array_211, hoisted__U32_7689, hoisted__Str_7690);
        U32 hoisted__U32_7691 = 4;
        (void)hoisted__U32_7691;
        Str hoisted__Str_7692 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_7692;
        Array__Str_set_init(_va_Array_211, hoisted__U32_7691, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_7692; if (_oa->cap == TIL_CAP_LIT) { _oa->cap = TIL_CAP_VIEW; }; _oa; }));
        panic(loc_str, _va_Array_211);
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
void Array__Str_set_init_dyn(void *til_env, void *_a0, void *_a1, void *_a2) {
    (void)til_env;
    Array__Str_set_init(_a0, *(U32 *)_a1, _a2);
}
static __attribute__((unused)) TilClosure Array__Str_set_init_dyn__til_closure = { (void *)Array__Str_set_init_dyn, NULL, NULL };
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
void *NodeType_CallerLoc_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_CallerLoc();
}
static __attribute__((unused)) TilClosure NodeType_CallerLoc_dyn__til_closure = { (void *)NodeType_CallerLoc_dyn, NULL, NULL };
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
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "set_init", 8ULL) == 0) return (void*)&Array__Str_set_init_dyn__til_closure;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "CallerLoc", 9ULL) == 0) return (void*)&NodeType_CallerLoc_dyn__til_closure;
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
        if (*index == 26LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CallerLoc", .count = 9ULL, .cap = TIL_CAP_VIEW}; _lit; });
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
