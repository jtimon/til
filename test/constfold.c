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
    Type_TAG_FuncPtrSig,
    Type_TAG_Body
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
    FuncType_TAG_LazyProc,
    FuncType_TAG_CoreFunc,
    FuncType_TAG_CoreProc
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
    NodeType_TAG_Loc,
    NodeType_TAG_BodyValue
} NodeType_tag;
typedef struct NodeType NodeType;
typedef struct Expr Expr;
typedef struct Map__I64_Str Map__I64_Str;
typedef struct Vec__Bool Vec__Bool;
typedef struct Vec__I64 Vec__I64;
typedef struct Vec__Declaration Vec__Declaration;
typedef struct Vec__Expr Vec__Expr;
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
    U8 tag;
};

struct Type {
    U8 tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
        Primitive Primitive;
        Str FuncPtrSig;
    } data;
};

struct FuncType {
    U8 tag;
};

struct OwnType {
    U8 tag;
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
    U8 tag;
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


typedef struct Vec__I64 {
    U8 *data;
    U32 count;
    U32 cap;
} Vec__I64;


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
    U8 tag;
};

struct Token {
    U8 tag;
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
    Str closure_name;
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
    Vec__I64 tag_values;
} EnumDef;


struct NodeType {
    U8 tag;
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
        CaptureBlockData BodyValue;
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Vec__Expr children;
    U32 line;
    U32 col;
} Expr;


Str * format(Array__Str * parts);
U32 Str_len(Str * self);
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
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
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
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
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

Str * format(Array__Str * parts);
U32 Str_len(Str * self);
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
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
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
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
U32 Vec__I64_size(void);
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
Type *Type_Body();
Bool FuncType_eq(FuncType *, FuncType *);
FuncType *FuncType_Func();
FuncType *FuncType_Proc();
FuncType *FuncType_Test();
FuncType *FuncType_Macro();
FuncType *FuncType_ExtFunc();
FuncType *FuncType_ExtProc();
FuncType *FuncType_LazyFunc();
FuncType *FuncType_LazyProc();
FuncType *FuncType_CoreFunc();
FuncType *FuncType_CoreProc();
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
NodeType *NodeType_BodyValue(CaptureBlockData *);
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

static __attribute__((unused)) Str _til_str_lit_0 = (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_1 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_2 = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_3 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_4 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_5 = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_6 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_7 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_8 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_9 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_10 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_11 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_12 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_13 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_14 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_15 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_16 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_17 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_18 = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_19 = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_20 = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_21 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_22 = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_23 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_24 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_25 = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_26 = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_27 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_28 = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_29 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_30 = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_31 = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_32 = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_33 = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_34 = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_35 = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_36 = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_37 = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_38 = (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_39 = (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_40 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_41 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_42 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_43 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_44 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

U32 CAP_LIT;
U32 CAP_VIEW;
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;
Str __til_docs_blob__;
Str __til_info_blob__;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_115 = parts;
        (void)_fc_Array__Str_115;
        (void)_fc_Array__Str_115;
        U32 _fi_USize_115 = 0;
        (void)_fi_USize_115;
        while (1) {
            U32 hoisted__U32_117 = Array__Str_len(_fc_Array__Str_115);
            (void)hoisted__U32_117;
            Bool _wcond_Bool_116 = ((Bool)(_fi_USize_115 < hoisted__U32_117));
            (void)_wcond_Bool_116;
            if (_wcond_Bool_116) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_115, &_fi_USize_115);
            U32 hoisted__U32_118 = 1;
            (void)hoisted__U32_118;
            U32 hoisted__U32_119 = ((U32)(_fi_USize_115 + hoisted__U32_118));
            (void)hoisted__U32_119;
            _fi_USize_115 = hoisted__U32_119;
            U32 hoisted__U32_120 = Str_len(s);
            (void)hoisted__U32_120;
            U32 hoisted__U32_121 = ((U32)(total + hoisted__U32_120));
            (void)hoisted__U32_121;
            total = hoisted__U32_121;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_122 = parts;
        (void)_fc_Array__Str_122;
        (void)_fc_Array__Str_122;
        U32 _fi_USize_122 = 0;
        (void)_fi_USize_122;
        while (1) {
            U32 hoisted__U32_124 = Array__Str_len(_fc_Array__Str_122);
            (void)hoisted__U32_124;
            Bool _wcond_Bool_123 = ((Bool)(_fi_USize_122 < hoisted__U32_124));
            (void)_wcond_Bool_123;
            if (_wcond_Bool_123) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_122, &_fi_USize_122);
            U32 hoisted__U32_125 = 1;
            (void)hoisted__U32_125;
            U32 hoisted__U32_126 = ((U32)(_fi_USize_122 + hoisted__U32_125));
            (void)hoisted__U32_126;
            _fi_USize_122 = hoisted__U32_126;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_142 = ((Bool)(b->count < a->count));
    (void)hoisted__Bool_142;
    if (hoisted__Bool_142) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_143 = 0;
    (void)hoisted__I32_143;
    Bool hoisted__Bool_144 = ((Bool)(c < hoisted__I32_143));
    (void)hoisted__Bool_144;
    if (hoisted__Bool_144) {
        I64 hoisted__I64_140 = -1;
        (void)hoisted__I64_140;
        { I64 _ret_val = hoisted__I64_140;
                        return _ret_val; }
    }
    I32 hoisted__I32_145 = 0;
    (void)hoisted__I32_145;
    Bool hoisted__Bool_146 = ((Bool)(c > hoisted__I32_145));
    (void)hoisted__Bool_146;
    if (hoisted__Bool_146) {
        I64 hoisted__I64_141 = 1;
        (void)hoisted__I64_141;
        { I64 _ret_val = hoisted__I64_141;
                        return _ret_val; }
    }
    I64 hoisted__I64_147 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_147;
    return hoisted__I64_147;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_149 = 0;
    (void)hoisted__U32_149;
    Bool hoisted__Bool_150 = ((Bool)(n == hoisted__U32_149));
    (void)hoisted__Bool_150;
    if (hoisted__Bool_150) {
        static Str hoisted__Str_148 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_148;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_148; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U32 hoisted__U32_151 = 1;
    (void)hoisted__U32_151;
    U32 hoisted__U64_152 = ((U64)(n + hoisted__U32_151));
    (void)hoisted__U64_152;
    void * buf = malloc(hoisted__U64_152);
    I32 hoisted__I32_153 = 0;
    (void)hoisted__I32_153;
    U64 hoisted__U64_154 = 1ULL;
    (void)hoisted__U64_154;
    memset(buf, hoisted__I32_153, hoisted__U64_154);
    I64 hoisted__I64_155 = 0;
    (void)hoisted__I64_155;
    Str *hoisted__Str_156 = malloc(sizeof(Str));
    hoisted__Str_156->c_str = buf;
    hoisted__Str_156->count = hoisted__I64_155;
    hoisted__Str_156->cap = n;
    (void)hoisted__Str_156;
    return hoisted__Str_156;
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_169 = 0;
    (void)hoisted__U32_169;
    Bool hoisted__Bool_170 = ((Bool)(s->count == hoisted__U32_169));
    (void)hoisted__Bool_170;
    if (hoisted__Bool_170) {
        return;
    }
    Bool hoisted__Bool_171 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_171;
    if (hoisted__Bool_171) {
        U32 hoisted__U32_159 = 1;
        (void)hoisted__U32_159;
        Array__Str *_va_Array_3 = Array__Str_new(hoisted__U32_159);
        (void)_va_Array_3;
        I64 _va_Array_3_ek = 0;
        (void)_va_Array_3_ek;
        OutOfBounds *_va_Array_3_eo = malloc(sizeof(OutOfBounds));
        _va_Array_3_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_3_eo;
        U32 hoisted__U32_160 = 0;
        (void)hoisted__U32_160;
        static Str hoisted__Str_161 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_161;
        static Str hoisted__Str_162 = (Str){.c_str = (void *)"./src/core/str.til:102:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_162;
        Array__Str_set(_va_Array_3, hoisted__U32_160, &hoisted__Str_161, &_va_Array_3_ek, _va_Array_3_eo, &hoisted__Str_162);
        OutOfBounds_delete(_va_Array_3_eo, 1);
        Str_delete(&hoisted__Str_162, (Bool){0});
        static Str hoisted__Str_163 = (Str){.c_str = (void *)"./src/core/str.til:102:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_163;
        panic(_va_Array_3, &hoisted__Str_163);
        Str_delete(&hoisted__Str_163, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_172 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_172;
    if (hoisted__Bool_172) {
        U32 hoisted__U32_164 = 1;
        (void)hoisted__U32_164;
        Array__Str *_va_Array_4 = Array__Str_new(hoisted__U32_164);
        (void)_va_Array_4;
        I64 _va_Array_4_ek = 0;
        (void)_va_Array_4_ek;
        OutOfBounds *_va_Array_4_eo = malloc(sizeof(OutOfBounds));
        _va_Array_4_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_4_eo;
        U32 hoisted__U32_165 = 0;
        (void)hoisted__U32_165;
        static Str hoisted__Str_166 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_166;
        static Str hoisted__Str_167 = (Str){.c_str = (void *)"./src/core/str.til:106:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_167;
        Array__Str_set(_va_Array_4, hoisted__U32_165, &hoisted__Str_166, &_va_Array_4_ek, _va_Array_4_eo, &hoisted__Str_167);
        OutOfBounds_delete(_va_Array_4_eo, 1);
        Str_delete(&hoisted__Str_167, (Bool){0});
        static Str hoisted__Str_168 = (Str){.c_str = (void *)"./src/core/str.til:106:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_168;
        panic(_va_Array_4, &hoisted__Str_168);
        Str_delete(&hoisted__Str_168, (Bool){0});
    }
    void *hoisted__v_173 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_173;
    (void)hoisted__v_173;
    memcpy(hoisted__v_173, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_174 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_174;
    (void)hoisted__v_174;
    I32 hoisted__I32_175 = 0;
    (void)hoisted__I32_175;
    U64 hoisted__U64_176 = 1ULL;
    (void)hoisted__U64_176;
    memset(hoisted__v_174, hoisted__I32_175, hoisted__U64_176);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_178 = 0;
    (void)hoisted__U32_178;
    Bool hoisted__Bool_179 = ((Bool)(val->count == hoisted__U32_178));
    (void)hoisted__Bool_179;
    if (hoisted__Bool_179) {
        static Str hoisted__Str_177 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_177;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_177; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
                return _r; }
    }
    U32 hoisted__U32_180 = 1;
    (void)hoisted__U32_180;
    U32 hoisted__U64_181 = ((U64)(val->count + hoisted__U32_180));
    (void)hoisted__U64_181;
    void * new_data = malloc(hoisted__U64_181);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_182 = ptr_add(new_data, val->count);
    (void)hoisted__v_182;
    (void)hoisted__v_182;
    I32 hoisted__I32_183 = 0;
    (void)hoisted__I32_183;
    U64 hoisted__U64_184 = 1ULL;
    (void)hoisted__U64_184;
    memset(hoisted__v_182, hoisted__I32_183, hoisted__U64_184);
    Str *hoisted__Str_185 = malloc(sizeof(Str));
    hoisted__Str_185->c_str = new_data;
    hoisted__Str_185->count = val->count;
    hoisted__Str_185->cap = val->count;
    (void)hoisted__Str_185;
    return hoisted__Str_185;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_186 = Str_clone(self);
    (void)hoisted__Str_186;
    return hoisted__Str_186;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_187 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_187;
    if (hoisted__Bool_187) {
        free(self->c_str);
    }
    Bool hoisted__Bool_188 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_188;
    Bool hoisted__Bool_189 = and(call_free, hoisted__Bool_188);
    (void)hoisted__Bool_189;
    if (hoisted__Bool_189) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_384 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_384;
    return hoisted__U64_384;
}

U32 Str_size(void) {
    U32 hoisted__U32_568 = 16;
    (void)hoisted__U32_568;
    return hoisted__U32_568;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_569 = Str_cmp(a, b);
    (void)hoisted__I64_569;
    I64 hoisted__I64_570 = 0;
    (void)hoisted__I64_570;
    Bool hoisted__Bool_571 = ((Bool)(hoisted__I64_569 == hoisted__I64_570));
    (void)hoisted__Bool_571;
    return hoisted__Bool_571;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_580 = Str_eq(a, b);
    (void)hoisted__Bool_580;
    Bool hoisted__Bool_581 = not(hoisted__Bool_580);
    (void)hoisted__Bool_581;
    return hoisted__Bool_581;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_672 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_672->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_672;
    return hoisted__OutOfBounds_672;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_673 = 0;
    (void)hoisted__Bool_673;
    Str_delete(&self->msg, hoisted__Bool_673);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_674 = 0;
    (void)hoisted__U32_674;
    U64 hoisted__U64_675 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_674); });
    (void)hoisted__U64_675;
    return hoisted__U64_675;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_694 = 16;
    (void)hoisted__U32_694;
    return hoisted__U32_694;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_718 = 16;
    (void)hoisted__U32_718;
    U64 hoisted__U64_719 = (U64)(cap);
    (void)hoisted__U64_719;
    U64 hoisted__U64_720 = (U64)(hoisted__U32_718);
    (void)hoisted__U64_720;
    void * hoisted__v_721 = calloc(hoisted__U64_719, hoisted__U64_720);
    (void)hoisted__v_721;
    Array__Str *hoisted__Array__Str_722 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_722->data = hoisted__v_721;
    hoisted__Array__Str_722->cap = cap;
    (void)hoisted__Array__Str_722;
    return hoisted__Array__Str_722;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_723 = 16;
    (void)hoisted__U32_723;
    U32 hoisted__U32_724 = ((U32)(DEREF(i) * hoisted__U32_723));
    (void)hoisted__U32_724;
    U64 hoisted__U64_725 = (U64)(hoisted__U32_724);
    (void)hoisted__U64_725;
    void *hoisted__v_726 = ptr_add(self->data, hoisted__U64_725);
    (void)hoisted__v_726;
    (void)hoisted__v_726;
    return hoisted__v_726;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_753 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_753;
    (void)hoisted__Str_753;
    Bool hoisted__Bool_754 = 0;
    (void)hoisted__Bool_754;
    Str_delete(hoisted__Str_753, hoisted__Bool_754);
    U32 hoisted__U32_755 = 16;
    (void)hoisted__U32_755;
    Str *hoisted__Str_756 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_756;
    (void)hoisted__Str_756;
    U64 hoisted__U64_757 = (U64)(hoisted__U32_755);
    (void)hoisted__U64_757;
    memcpy(hoisted__Str_756, val, hoisted__U64_757);
    U32 hoisted__U32_758 = 16;
    (void)hoisted__U32_758;
    I32 hoisted__I32_759 = 0;
    (void)hoisted__I32_759;
    U64 hoisted__U64_760 = (U64)(hoisted__U32_758);
    (void)hoisted__U64_760;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_759, hoisted__U64_760); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_783 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_783;
    if (hoisted__Bool_783) {
        U32 hoisted__U32_761 = 6;
        (void)hoisted__U32_761;
        Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_761);
        (void)_va_Array_16;
        I64 _va_Array_16_ek = 0;
        (void)_va_Array_16_ek;
        OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
        _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_16_eo;
        U32 hoisted__U32_762 = 0;
        (void)hoisted__U32_762;
        Str *hoisted__Str_763 = Str_clone(loc);
        (void)hoisted__Str_763;
        static Str hoisted__Str_764 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_764;
        Array__Str_set(_va_Array_16, hoisted__U32_762, hoisted__Str_763, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_764);
        Str_delete(&hoisted__Str_764, (Bool){0});
        U32 hoisted__U32_765 = 1;
        (void)hoisted__U32_765;
        static Str hoisted__Str_766 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_766;
        static Str hoisted__Str_767 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_767;
        Array__Str_set(_va_Array_16, hoisted__U32_765, &hoisted__Str_766, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_767);
        Str_delete(&hoisted__Str_767, (Bool){0});
        U32 hoisted__U32_768 = 2;
        (void)hoisted__U32_768;
        Str *hoisted__Str_769 = U32_to_str(i);
        (void)hoisted__Str_769;
        static Str hoisted__Str_770 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_770;
        Array__Str_set(_va_Array_16, hoisted__U32_768, hoisted__Str_769, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_770);
        Str_delete(&hoisted__Str_770, (Bool){0});
        U32 hoisted__U32_771 = 3;
        (void)hoisted__U32_771;
        static Str hoisted__Str_772 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_772;
        static Str hoisted__Str_773 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_773;
        Array__Str_set(_va_Array_16, hoisted__U32_771, &hoisted__Str_772, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_773);
        Str_delete(&hoisted__Str_773, (Bool){0});
        U32 hoisted__U32_774 = 4;
        (void)hoisted__U32_774;
        Str *hoisted__Str_775 = U32_to_str(self->cap);
        (void)hoisted__Str_775;
        static Str hoisted__Str_776 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_776;
        Array__Str_set(_va_Array_16, hoisted__U32_774, hoisted__Str_775, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_776);
        Str_delete(&hoisted__Str_776, (Bool){0});
        U32 hoisted__U32_777 = 5;
        (void)hoisted__U32_777;
        static Str hoisted__Str_778 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_778;
        static Str hoisted__Str_779 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_779;
        Array__Str_set(_va_Array_16, hoisted__U32_777, &hoisted__Str_778, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_779);
        OutOfBounds_delete(_va_Array_16_eo, 1);
        Str_delete(&hoisted__Str_779, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_780 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_16); hoisted__OutOfBounds_780->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_780;
        U32 hoisted__U32_781 = 16;
        (void)hoisted__U32_781;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_780, hoisted__U32_781);
        OutOfBounds_delete(hoisted__OutOfBounds_780, 1);
        I64 hoisted__I64_782 = 1;
        (void)hoisted__I64_782;
        *_err_kind = hoisted__I64_782;
    }
    I64 hoisted__I64_784 = 0;
    (void)hoisted__I64_784;
    Bool hoisted__Bool_785 = ((Bool)(DEREF(_err_kind) == hoisted__I64_784));
    (void)hoisted__Bool_785;
    if (hoisted__Bool_785) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_786 = self->cap;
        (void)_re_U32_786;
        U32 _rc_U32_786 = 0;
        (void)_rc_U32_786;
        Bool hoisted__Bool_799 = ((Bool)(_rc_U32_786 <= _re_U32_786));
        (void)hoisted__Bool_799;
        if (hoisted__Bool_799) {
            while (1) {
                Bool _wcond_Bool_787 = ((Bool)(_rc_U32_786 < _re_U32_786));
                (void)_wcond_Bool_787;
                if (_wcond_Bool_787) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_786);
                U32_inc(&_rc_U32_786);
                U32 hoisted__U32_788 = 16;
                (void)hoisted__U32_788;
                U32 hoisted__U32_789 = ((U32)(i * hoisted__U32_788));
                (void)hoisted__U32_789;
                U64 hoisted__U64_790 = (U64)(hoisted__U32_789);
                (void)hoisted__U64_790;
                Str *hoisted__Str_791 = ptr_add(self->data, hoisted__U64_790);
                (void)hoisted__Str_791;
                (void)hoisted__Str_791;
                Bool hoisted__Bool_792 = 0;
                (void)hoisted__Bool_792;
                Str_delete(hoisted__Str_791, hoisted__Bool_792);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_793 = ((Bool)(_rc_U32_786 > _re_U32_786));
                (void)_wcond_Bool_793;
                if (_wcond_Bool_793) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_786);
                U32_dec(&_rc_U32_786);
                U32 hoisted__U32_794 = 16;
                (void)hoisted__U32_794;
                U32 hoisted__U32_795 = ((U32)(i * hoisted__U32_794));
                (void)hoisted__U32_795;
                U64 hoisted__U64_796 = (U64)(hoisted__U32_795);
                (void)hoisted__U64_796;
                Str *hoisted__Str_797 = ptr_add(self->data, hoisted__U64_796);
                (void)hoisted__Str_797;
                (void)hoisted__Str_797;
                Bool hoisted__Bool_798 = 0;
                (void)hoisted__Bool_798;
                Str_delete(hoisted__Str_797, hoisted__Bool_798);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_828 = 16;
    (void)hoisted__U32_828;
    U32 hoisted__U32_829 = ((U32)(self->cap * hoisted__U32_828));
    (void)hoisted__U32_829;
    U64 hoisted__U64_830 = (U64)(hoisted__U32_829);
    (void)hoisted__U64_830;
    void * new_data = malloc(hoisted__U64_830);
    {
        U32 _re_U32_800 = self->cap;
        (void)_re_U32_800;
        U32 _rc_U32_800 = 0;
        (void)_rc_U32_800;
        Bool hoisted__Bool_827 = ((Bool)(_rc_U32_800 <= _re_U32_800));
        (void)hoisted__Bool_827;
        if (hoisted__Bool_827) {
            while (1) {
                Bool _wcond_Bool_801 = ((Bool)(_rc_U32_800 < _re_U32_800));
                (void)_wcond_Bool_801;
                if (_wcond_Bool_801) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_800);
                U32_inc(&_rc_U32_800);
                U32 hoisted__U32_802 = 16;
                (void)hoisted__U32_802;
                U32 hoisted__U32_803 = ((U32)(i * hoisted__U32_802));
                (void)hoisted__U32_803;
                U64 hoisted__U64_804 = (U64)(hoisted__U32_803);
                (void)hoisted__U64_804;
                Str *src = ptr_add(self->data, hoisted__U64_804);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_805 = 16;
                (void)hoisted__U32_805;
                U32 hoisted__U32_806 = ((U32)(i * hoisted__U32_805));
                (void)hoisted__U32_806;
                U64 hoisted__U64_807 = (U64)(hoisted__U32_806);
                (void)hoisted__U64_807;
                U32 hoisted__U32_808 = 16;
                (void)hoisted__U32_808;
                void *hoisted__v_809 = ptr_add(new_data, hoisted__U64_807);
                (void)hoisted__v_809;
                (void)hoisted__v_809;
                U64 hoisted__U64_810 = (U64)(hoisted__U32_808);
                (void)hoisted__U64_810;
                memcpy(hoisted__v_809, cloned, hoisted__U64_810);
                U32 hoisted__U32_811 = 16;
                (void)hoisted__U32_811;
                I32 hoisted__I32_812 = 0;
                (void)hoisted__I32_812;
                U64 hoisted__U64_813 = (U64)(hoisted__U32_811);
                (void)hoisted__U64_813;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_812, hoisted__U64_813); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_814 = ((Bool)(_rc_U32_800 > _re_U32_800));
                (void)_wcond_Bool_814;
                if (_wcond_Bool_814) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_800);
                U32_dec(&_rc_U32_800);
                U32 hoisted__U32_815 = 16;
                (void)hoisted__U32_815;
                U32 hoisted__U32_816 = ((U32)(i * hoisted__U32_815));
                (void)hoisted__U32_816;
                U64 hoisted__U64_817 = (U64)(hoisted__U32_816);
                (void)hoisted__U64_817;
                Str *src = ptr_add(self->data, hoisted__U64_817);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_818 = 16;
                (void)hoisted__U32_818;
                U32 hoisted__U32_819 = ((U32)(i * hoisted__U32_818));
                (void)hoisted__U32_819;
                U64 hoisted__U64_820 = (U64)(hoisted__U32_819);
                (void)hoisted__U64_820;
                U32 hoisted__U32_821 = 16;
                (void)hoisted__U32_821;
                void *hoisted__v_822 = ptr_add(new_data, hoisted__U64_820);
                (void)hoisted__v_822;
                (void)hoisted__v_822;
                U64 hoisted__U64_823 = (U64)(hoisted__U32_821);
                (void)hoisted__U64_823;
                memcpy(hoisted__v_822, cloned, hoisted__U64_823);
                U32 hoisted__U32_824 = 16;
                (void)hoisted__U32_824;
                I32 hoisted__I32_825 = 0;
                (void)hoisted__I32_825;
                U64 hoisted__U64_826 = (U64)(hoisted__U32_824);
                (void)hoisted__U64_826;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_825, hoisted__U64_826); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_831 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_831->data = new_data;
    hoisted__Array__Str_831->cap = self->cap;
    (void)hoisted__Array__Str_831;
    return hoisted__Array__Str_831;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_832 = 16;
    (void)hoisted__U32_832;
    return hoisted__U32_832;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_833 = 16;
    (void)hoisted__U32_833;
    U64 hoisted__U64_834 = (U64)(hoisted__U32_833);
    (void)hoisted__U64_834;
    void * hoisted__v_835 = malloc(hoisted__U64_834);
    (void)hoisted__v_835;
    U32 hoisted__U32_836 = 0;
    (void)hoisted__U32_836;
    I64 hoisted__I64_837 = 1;
    (void)hoisted__I64_837;
    Vec__Str *hoisted__Vec__Str_838 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_838->data = hoisted__v_835;
    hoisted__Vec__Str_838->count = hoisted__U32_836;
    hoisted__Vec__Str_838->cap = hoisted__I64_837;
    (void)hoisted__Vec__Str_838;
    return hoisted__Vec__Str_838;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_848 = self->count;
        (void)_re_U32_848;
        U32 _rc_U32_848 = 0;
        (void)_rc_U32_848;
        Bool hoisted__Bool_861 = ((Bool)(_rc_U32_848 <= _re_U32_848));
        (void)hoisted__Bool_861;
        if (hoisted__Bool_861) {
            while (1) {
                Bool _wcond_Bool_849 = ((Bool)(_rc_U32_848 < _re_U32_848));
                (void)_wcond_Bool_849;
                if (_wcond_Bool_849) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_848);
                U32_inc(&_rc_U32_848);
                U32 hoisted__U32_850 = 16;
                (void)hoisted__U32_850;
                U32 hoisted__U32_851 = ((U32)(i * hoisted__U32_850));
                (void)hoisted__U32_851;
                U64 hoisted__U64_852 = (U64)(hoisted__U32_851);
                (void)hoisted__U64_852;
                Str *hoisted__Str_853 = ptr_add(self->data, hoisted__U64_852);
                (void)hoisted__Str_853;
                (void)hoisted__Str_853;
                Bool hoisted__Bool_854 = 0;
                (void)hoisted__Bool_854;
                Str_delete(hoisted__Str_853, hoisted__Bool_854);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_855 = ((Bool)(_rc_U32_848 > _re_U32_848));
                (void)_wcond_Bool_855;
                if (_wcond_Bool_855) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_848);
                U32_dec(&_rc_U32_848);
                U32 hoisted__U32_856 = 16;
                (void)hoisted__U32_856;
                U32 hoisted__U32_857 = ((U32)(i * hoisted__U32_856));
                (void)hoisted__U32_857;
                U64 hoisted__U64_858 = (U64)(hoisted__U32_857);
                (void)hoisted__U64_858;
                Str *hoisted__Str_859 = ptr_add(self->data, hoisted__U64_858);
                (void)hoisted__Str_859;
                (void)hoisted__Str_859;
                Bool hoisted__Bool_860 = 0;
                (void)hoisted__Bool_860;
                Str_delete(hoisted__Str_859, hoisted__Bool_860);
            }
        }
    }
    U32 hoisted__U32_862 = 0;
    (void)hoisted__U32_862;
    self->count = hoisted__U32_862;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1132 = 16;
    (void)hoisted__U32_1132;
    U32 hoisted__U32_1133 = ((U32)(self->cap * hoisted__U32_1132));
    (void)hoisted__U32_1133;
    U64 hoisted__U64_1134 = (U64)(hoisted__U32_1133);
    (void)hoisted__U64_1134;
    void * new_data = malloc(hoisted__U64_1134);
    {
        U32 _re_U32_1104 = self->count;
        (void)_re_U32_1104;
        U32 _rc_U32_1104 = 0;
        (void)_rc_U32_1104;
        Bool hoisted__Bool_1131 = ((Bool)(_rc_U32_1104 <= _re_U32_1104));
        (void)hoisted__Bool_1131;
        if (hoisted__Bool_1131) {
            while (1) {
                Bool _wcond_Bool_1105 = ((Bool)(_rc_U32_1104 < _re_U32_1104));
                (void)_wcond_Bool_1105;
                if (_wcond_Bool_1105) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1104);
                U32_inc(&_rc_U32_1104);
                U32 hoisted__U32_1106 = 16;
                (void)hoisted__U32_1106;
                U32 hoisted__U32_1107 = ((U32)(i * hoisted__U32_1106));
                (void)hoisted__U32_1107;
                U64 hoisted__U64_1108 = (U64)(hoisted__U32_1107);
                (void)hoisted__U64_1108;
                Str *src = ptr_add(self->data, hoisted__U64_1108);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1109 = 16;
                (void)hoisted__U32_1109;
                U32 hoisted__U32_1110 = ((U32)(i * hoisted__U32_1109));
                (void)hoisted__U32_1110;
                U64 hoisted__U64_1111 = (U64)(hoisted__U32_1110);
                (void)hoisted__U64_1111;
                U32 hoisted__U32_1112 = 16;
                (void)hoisted__U32_1112;
                void *hoisted__v_1113 = ptr_add(new_data, hoisted__U64_1111);
                (void)hoisted__v_1113;
                (void)hoisted__v_1113;
                U64 hoisted__U64_1114 = (U64)(hoisted__U32_1112);
                (void)hoisted__U64_1114;
                memcpy(hoisted__v_1113, cloned, hoisted__U64_1114);
                U32 hoisted__U32_1115 = 16;
                (void)hoisted__U32_1115;
                I32 hoisted__I32_1116 = 0;
                (void)hoisted__I32_1116;
                U64 hoisted__U64_1117 = (U64)(hoisted__U32_1115);
                (void)hoisted__U64_1117;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1116, hoisted__U64_1117); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1118 = ((Bool)(_rc_U32_1104 > _re_U32_1104));
                (void)_wcond_Bool_1118;
                if (_wcond_Bool_1118) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1104);
                U32_dec(&_rc_U32_1104);
                U32 hoisted__U32_1119 = 16;
                (void)hoisted__U32_1119;
                U32 hoisted__U32_1120 = ((U32)(i * hoisted__U32_1119));
                (void)hoisted__U32_1120;
                U64 hoisted__U64_1121 = (U64)(hoisted__U32_1120);
                (void)hoisted__U64_1121;
                Str *src = ptr_add(self->data, hoisted__U64_1121);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1122 = 16;
                (void)hoisted__U32_1122;
                U32 hoisted__U32_1123 = ((U32)(i * hoisted__U32_1122));
                (void)hoisted__U32_1123;
                U64 hoisted__U64_1124 = (U64)(hoisted__U32_1123);
                (void)hoisted__U64_1124;
                U32 hoisted__U32_1125 = 16;
                (void)hoisted__U32_1125;
                void *hoisted__v_1126 = ptr_add(new_data, hoisted__U64_1124);
                (void)hoisted__v_1126;
                (void)hoisted__v_1126;
                U64 hoisted__U64_1127 = (U64)(hoisted__U32_1125);
                (void)hoisted__U64_1127;
                memcpy(hoisted__v_1126, cloned, hoisted__U64_1127);
                U32 hoisted__U32_1128 = 16;
                (void)hoisted__U32_1128;
                I32 hoisted__I32_1129 = 0;
                (void)hoisted__I32_1129;
                U64 hoisted__U64_1130 = (U64)(hoisted__U32_1128);
                (void)hoisted__U64_1130;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1129, hoisted__U64_1130); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1135 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1135->data = new_data;
    hoisted__Vec__Str_1135->count = self->count;
    hoisted__Vec__Str_1135->cap = self->cap;
    (void)hoisted__Vec__Str_1135;
    return hoisted__Vec__Str_1135;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1136 = 16;
    (void)hoisted__U32_1136;
    return hoisted__U32_1136;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1139 = 8;
    (void)hoisted__U32_1139;
    return hoisted__U32_1139;
}

void * Dynamic_clone(void * self) {
    return self;
}

void Dynamic_delete(void * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_1155 = 1;
    (void)hoisted__U32_1155;
    return hoisted__U32_1155;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1240 = 0;
    (void)hoisted__U32_1240;
    U64 hoisted__U64_1241 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1240); });
    (void)hoisted__U64_1241;
    return hoisted__U64_1241;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_1341 = U32_to_i64(val);
    (void)hoisted__I64_1341;
    Str *hoisted__Str_1342 = I64_to_str(hoisted__I64_1341);
    (void)hoisted__Str_1342;
    return hoisted__Str_1342;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_1343 = 1;
    (void)hoisted__U32_1343;
    U32 hoisted__U32_1344 = ((U32)(DEREF(self) + hoisted__U32_1343));
    (void)hoisted__U32_1344;
    *self = hoisted__U32_1344;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_1345 = 1;
    (void)hoisted__U32_1345;
    U32 hoisted__U32_1346 = ((U32)(DEREF(self) - hoisted__U32_1345));
    (void)hoisted__U32_1346;
    *self = hoisted__U32_1346;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_1353 = 4;
    (void)hoisted__U32_1353;
    return hoisted__U32_1353;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1438 = 0;
    (void)hoisted__U32_1438;
    U64 hoisted__U64_1439 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1438); });
    (void)hoisted__U64_1439;
    return hoisted__U64_1439;
}

void U64_inc(U64 * self) {
    U64 hoisted__U64_1441 = 1ULL;
    (void)hoisted__U64_1441;
    U64 hoisted__U64_1442 = ((U64)(DEREF(self) + hoisted__U64_1441));
    (void)hoisted__U64_1442;
    *self = hoisted__U64_1442;
}

void U64_dec(U64 * self) {
    U64 hoisted__U64_1443 = 1ULL;
    (void)hoisted__U64_1443;
    U64 hoisted__U64_1444 = ((U64)(DEREF(self) - hoisted__U64_1443));
    (void)hoisted__U64_1444;
    *self = hoisted__U64_1444;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_1449 = 8;
    (void)hoisted__U32_1449;
    return hoisted__U32_1449;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1534 = 0;
    (void)hoisted__U32_1534;
    U64 hoisted__U64_1535 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1534); });
    (void)hoisted__U64_1535;
    return hoisted__U64_1535;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_1556 = 1;
    (void)hoisted__U32_1556;
    return hoisted__U32_1556;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1557 = 0;
    (void)hoisted__U32_1557;
    U64 hoisted__U64_1558 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1557); });
    (void)hoisted__U64_1558;
    return hoisted__U64_1558;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_1743 = 4;
    (void)hoisted__U32_1743;
    return hoisted__U32_1743;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1885 = 0;
    (void)hoisted__U32_1885;
    U64 hoisted__U64_1886 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1885); });
    (void)hoisted__U64_1886;
    return hoisted__U64_1886;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1917 = 0;
    (void)hoisted__I64_1917;
    Bool hoisted__Bool_1918 = ((Bool)(val == hoisted__I64_1917));
    (void)hoisted__Bool_1918;
    if (hoisted__Bool_1918) {
        U64 hoisted__U64_1887 = 2ULL;
        (void)hoisted__U64_1887;
        void * buf = malloc(hoisted__U64_1887);
        I64 hoisted__I64_1888 = 48;
        (void)hoisted__I64_1888;
        U64 hoisted__U64_1889 = 1ULL;
        (void)hoisted__U64_1889;
        memcpy(buf, &hoisted__I64_1888, hoisted__U64_1889);
        U64 hoisted__U64_1890 = 1ULL;
        (void)hoisted__U64_1890;
        void *hoisted__v_1891 = ptr_add(buf, hoisted__U64_1890);
        (void)hoisted__v_1891;
        (void)hoisted__v_1891;
        I32 hoisted__I32_1892 = 0;
        (void)hoisted__I32_1892;
        U64 hoisted__U64_1893 = 1ULL;
        (void)hoisted__U64_1893;
        memset(hoisted__v_1891, hoisted__I32_1892, hoisted__U64_1893);
        I64 hoisted__I64_1894 = 1;
        (void)hoisted__I64_1894;
        I64 hoisted__I64_1895 = 1;
        (void)hoisted__I64_1895;
        Str *hoisted__Str_1896 = malloc(sizeof(Str));
        hoisted__Str_1896->c_str = buf;
        hoisted__Str_1896->count = hoisted__I64_1894;
        hoisted__Str_1896->cap = hoisted__I64_1895;
        (void)hoisted__Str_1896;
        { Str * _ret_val = hoisted__Str_1896;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1919 = 0;
    (void)hoisted__I64_1919;
    Bool hoisted__Bool_1920 = ((Bool)(val < hoisted__I64_1919));
    (void)hoisted__Bool_1920;
    if (hoisted__Bool_1920) {
        Bool hoisted__Bool_1897 = 1;
        (void)hoisted__Bool_1897;
        is_neg = hoisted__Bool_1897;
        I64 hoisted__I64_1898 = 0;
        (void)hoisted__I64_1898;
        I64 hoisted__I64_1899 = ((I64)(hoisted__I64_1898 - val));
        (void)hoisted__I64_1899;
        v = hoisted__I64_1899;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1901 = 0;
        (void)hoisted__I64_1901;
        Bool _wcond_Bool_1900 = ((Bool)(tmp > hoisted__I64_1901));
        (void)_wcond_Bool_1900;
        if (_wcond_Bool_1900) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1902 = 10;
        (void)hoisted__I64_1902;
        I64 hoisted__I64_1903 = ({ I64 _cf_a = tmp; I64 _cf_b = hoisted__I64_1902; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1903;
        tmp = hoisted__I64_1903;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1921 = 1ULL;
    (void)hoisted__U64_1921;
    U64 hoisted__U64_1922 = ((U64)(total + hoisted__U64_1921));
    (void)hoisted__U64_1922;
    void * buf = malloc(hoisted__U64_1922);
    if (is_neg) {
        I64 hoisted__I64_1904 = 45;
        (void)hoisted__I64_1904;
        U64 hoisted__U64_1905 = 1ULL;
        (void)hoisted__U64_1905;
        memcpy(buf, &hoisted__I64_1904, hoisted__U64_1905);
    }
    U64 hoisted__U64_1923 = 1ULL;
    (void)hoisted__U64_1923;
    U64 i = ((U64)(total - hoisted__U64_1923));
    while (1) {
        I64 hoisted__I64_1907 = 0;
        (void)hoisted__I64_1907;
        Bool _wcond_Bool_1906 = ((Bool)(v > hoisted__I64_1907));
        (void)_wcond_Bool_1906;
        if (_wcond_Bool_1906) {
        } else {
            break;
        }
        I64 hoisted__I64_1908 = 10;
        (void)hoisted__I64_1908;
        I64 hoisted__I64_1909 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1908; (I64)((_cf_b == 0) ? 0 : (_cf_a % _cf_b)); });
        (void)hoisted__I64_1909;
        I64 hoisted__I64_1910 = 48;
        (void)hoisted__I64_1910;
        I64 hoisted__I64_1911 = ((I64)(hoisted__I64_1909 + hoisted__I64_1910));
        (void)hoisted__I64_1911;
        void *hoisted__v_1912 = ptr_add(buf, i);
        (void)hoisted__v_1912;
        (void)hoisted__v_1912;
        U8 hoisted__U8_1913 = I64_to_u8(hoisted__I64_1911);
        (void)hoisted__U8_1913;
        U64 hoisted__U64_1914 = 1ULL;
        (void)hoisted__U64_1914;
        memcpy(hoisted__v_1912, &hoisted__U8_1913, hoisted__U64_1914);
        I64 hoisted__I64_1915 = 10;
        (void)hoisted__I64_1915;
        I64 hoisted__I64_1916 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1915; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1916;
        v = hoisted__I64_1916;
        U64_dec(&i);
    }
    void *hoisted__v_1924 = ptr_add(buf, total);
    (void)hoisted__v_1924;
    (void)hoisted__v_1924;
    I32 hoisted__I32_1925 = 0;
    (void)hoisted__I32_1925;
    U64 hoisted__U64_1926 = 1ULL;
    (void)hoisted__U64_1926;
    memset(hoisted__v_1924, hoisted__I32_1925, hoisted__U64_1926);
    Str *hoisted__Str_1927 = malloc(sizeof(Str));
    hoisted__Str_1927->c_str = buf;
    hoisted__Str_1927->count = total;
    hoisted__Str_1927->cap = total;
    (void)hoisted__Str_1927;
    return hoisted__Str_1927;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1945 = 8;
    (void)hoisted__U32_1945;
    return hoisted__U32_1945;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2103 = 0;
    (void)hoisted__U32_2103;
    U64 hoisted__U64_2104 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2103); });
    (void)hoisted__U64_2104;
    return hoisted__U64_2104;
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_2106 = 4;
    (void)hoisted__U32_2106;
    return hoisted__U32_2106;
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_2124 = 0;
    (void)hoisted__U32_2124;
    U64 hoisted__U64_2125 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2124); });
    (void)hoisted__U64_2125;
    return hoisted__U64_2125;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2172 = 0;
    (void)_m_Bool_2172;
    {
        Bool hoisted__Bool_2175 = 1;
        (void)hoisted__Bool_2175;
        Bool hoisted__Bool_2176 = ((Bool)(a == hoisted__Bool_2175));
        (void)hoisted__Bool_2176;
        if (hoisted__Bool_2176) {
            Bool hoisted__Bool_2173 = Bool_clone(&b);
            (void)hoisted__Bool_2173;
            _m_Bool_2172 = hoisted__Bool_2173;
        } else {
            Bool hoisted__Bool_2174 = 0;
            (void)hoisted__Bool_2174;
            _m_Bool_2172 = hoisted__Bool_2174;
        }
    }
    return _m_Bool_2172;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2186 = ((Bool)(a == b));
    (void)hoisted__Bool_2186;
    if (hoisted__Bool_2186) {
        I64 hoisted__I64_2184 = 0;
        (void)hoisted__I64_2184;
        { I64 _ret_val = hoisted__I64_2184;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2185 = -1;
        (void)hoisted__I64_2185;
        return hoisted__I64_2185;
    }
    I64 hoisted__I64_2187 = 1;
    (void)hoisted__I64_2187;
    return hoisted__I64_2187;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2188 = 1;
    (void)hoisted__U32_2188;
    return hoisted__U32_2188;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2189 = 0;
    (void)hoisted__U32_2189;
    U64 hoisted__U64_2190 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2189); });
    (void)hoisted__U64_2190;
    return hoisted__U64_2190;
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
    U32 hoisted__U32_2227 = 1;
    (void)hoisted__U32_2227;
    Bool hoisted__Bool_2228 = is_n(self, &(Primitive){.tag = Primitive_TAG_I16}, hoisted__U32_2227);
    (void)hoisted__Bool_2228;
    if (hoisted__Bool_2228) {
        U32 hoisted__U32_2207 = 1;
        (void)hoisted__U32_2207;
        Bool hoisted__Bool_2208 = is_n(other, &(Primitive){.tag = Primitive_TAG_I16}, hoisted__U32_2207);
        (void)hoisted__Bool_2208;
        { Bool _ret_val = hoisted__Bool_2208;
                return _ret_val; }
    }
    U32 hoisted__U32_2229 = 1;
    (void)hoisted__U32_2229;
    Bool hoisted__Bool_2230 = is_n(self, &(Primitive){.tag = Primitive_TAG_U16}, hoisted__U32_2229);
    (void)hoisted__Bool_2230;
    if (hoisted__Bool_2230) {
        U32 hoisted__U32_2209 = 1;
        (void)hoisted__U32_2209;
        Bool hoisted__Bool_2210 = is_n(other, &(Primitive){.tag = Primitive_TAG_U16}, hoisted__U32_2209);
        (void)hoisted__Bool_2210;
        { Bool _ret_val = hoisted__Bool_2210;
                return _ret_val; }
    }
    U32 hoisted__U32_2231 = 1;
    (void)hoisted__U32_2231;
    Bool hoisted__Bool_2232 = is_n(self, &(Primitive){.tag = Primitive_TAG_I8}, hoisted__U32_2231);
    (void)hoisted__Bool_2232;
    if (hoisted__Bool_2232) {
        U32 hoisted__U32_2211 = 1;
        (void)hoisted__U32_2211;
        Bool hoisted__Bool_2212 = is_n(other, &(Primitive){.tag = Primitive_TAG_I8}, hoisted__U32_2211);
        (void)hoisted__Bool_2212;
        { Bool _ret_val = hoisted__Bool_2212;
                return _ret_val; }
    }
    U32 hoisted__U32_2233 = 1;
    (void)hoisted__U32_2233;
    Bool hoisted__Bool_2234 = is_n(self, &(Primitive){.tag = Primitive_TAG_U8}, hoisted__U32_2233);
    (void)hoisted__Bool_2234;
    if (hoisted__Bool_2234) {
        U32 hoisted__U32_2213 = 1;
        (void)hoisted__U32_2213;
        Bool hoisted__Bool_2214 = is_n(other, &(Primitive){.tag = Primitive_TAG_U8}, hoisted__U32_2213);
        (void)hoisted__Bool_2214;
        { Bool _ret_val = hoisted__Bool_2214;
                return _ret_val; }
    }
    U32 hoisted__U32_2235 = 1;
    (void)hoisted__U32_2235;
    Bool hoisted__Bool_2236 = is_n(self, &(Primitive){.tag = Primitive_TAG_U32}, hoisted__U32_2235);
    (void)hoisted__Bool_2236;
    if (hoisted__Bool_2236) {
        U32 hoisted__U32_2215 = 1;
        (void)hoisted__U32_2215;
        Bool hoisted__Bool_2216 = is_n(other, &(Primitive){.tag = Primitive_TAG_U32}, hoisted__U32_2215);
        (void)hoisted__Bool_2216;
        { Bool _ret_val = hoisted__Bool_2216;
                return _ret_val; }
    }
    U32 hoisted__U32_2237 = 1;
    (void)hoisted__U32_2237;
    Bool hoisted__Bool_2238 = is_n(self, &(Primitive){.tag = Primitive_TAG_I32}, hoisted__U32_2237);
    (void)hoisted__Bool_2238;
    if (hoisted__Bool_2238) {
        U32 hoisted__U32_2217 = 1;
        (void)hoisted__U32_2217;
        Bool hoisted__Bool_2218 = is_n(other, &(Primitive){.tag = Primitive_TAG_I32}, hoisted__U32_2217);
        (void)hoisted__Bool_2218;
        { Bool _ret_val = hoisted__Bool_2218;
                return _ret_val; }
    }
    U32 hoisted__U32_2239 = 1;
    (void)hoisted__U32_2239;
    Bool hoisted__Bool_2240 = is_n(self, &(Primitive){.tag = Primitive_TAG_U64}, hoisted__U32_2239);
    (void)hoisted__Bool_2240;
    if (hoisted__Bool_2240) {
        U32 hoisted__U32_2219 = 1;
        (void)hoisted__U32_2219;
        Bool hoisted__Bool_2220 = is_n(other, &(Primitive){.tag = Primitive_TAG_U64}, hoisted__U32_2219);
        (void)hoisted__Bool_2220;
        { Bool _ret_val = hoisted__Bool_2220;
                return _ret_val; }
    }
    U32 hoisted__U32_2241 = 1;
    (void)hoisted__U32_2241;
    Bool hoisted__Bool_2242 = is_n(self, &(Primitive){.tag = Primitive_TAG_I64}, hoisted__U32_2241);
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        U32 hoisted__U32_2221 = 1;
        (void)hoisted__U32_2221;
        Bool hoisted__Bool_2222 = is_n(other, &(Primitive){.tag = Primitive_TAG_I64}, hoisted__U32_2221);
        (void)hoisted__Bool_2222;
        { Bool _ret_val = hoisted__Bool_2222;
                return _ret_val; }
    }
    U32 hoisted__U32_2243 = 1;
    (void)hoisted__U32_2243;
    Bool hoisted__Bool_2244 = is_n(self, &(Primitive){.tag = Primitive_TAG_F32}, hoisted__U32_2243);
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        U32 hoisted__U32_2223 = 1;
        (void)hoisted__U32_2223;
        Bool hoisted__Bool_2224 = is_n(other, &(Primitive){.tag = Primitive_TAG_F32}, hoisted__U32_2223);
        (void)hoisted__Bool_2224;
        { Bool _ret_val = hoisted__Bool_2224;
                return _ret_val; }
    }
    U32 hoisted__U32_2245 = 1;
    (void)hoisted__U32_2245;
    Bool hoisted__Bool_2246 = is_n(self, &(Primitive){.tag = Primitive_TAG_Bool}, hoisted__U32_2245);
    (void)hoisted__Bool_2246;
    if (hoisted__Bool_2246) {
        U32 hoisted__U32_2225 = 1;
        (void)hoisted__U32_2225;
        Bool hoisted__Bool_2226 = is_n(other, &(Primitive){.tag = Primitive_TAG_Bool}, hoisted__U32_2225);
        (void)hoisted__Bool_2226;
        { Bool _ret_val = hoisted__Bool_2226;
                return _ret_val; }
    }
    Bool hoisted__Bool_2247 = 0;
    (void)hoisted__Bool_2247;
    return hoisted__Bool_2247;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2269 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2269;
    if (hoisted__Bool_2269) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2270 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2270;
    if (hoisted__Bool_2270) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2271 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2271;
    if (hoisted__Bool_2271) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2272 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2272;
    if (hoisted__Bool_2272) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2273 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2273;
    if (hoisted__Bool_2273) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2274 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2274;
    if (hoisted__Bool_2274) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2275 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2275;
    if (hoisted__Bool_2275) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2276 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2276;
    if (hoisted__Bool_2276) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2277 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2277;
    if (hoisted__Bool_2277) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2278 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2278;
    if (hoisted__Bool_2278) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2279 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2279;
    UNREACHABLE(&hoisted__Str_2279);
    Str_delete(&hoisted__Str_2279, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2280 = 1;
    (void)hoisted__U32_2280;
    return hoisted__U32_2280;
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
Type *Type_Body() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Body;
    return r;
}
void Type_delete(Type * self, Bool call_free) {
    U32 hoisted__U32_2361 = 1;
    (void)hoisted__U32_2361;
    Bool hoisted__Bool_2362 = is_n(self, &(Type){.tag = Type_TAG_Struct}, hoisted__U32_2361);
    (void)hoisted__Bool_2362;
    if (hoisted__Bool_2362) {
        Str *hoisted__Str_2351 = get_payload(self);
        (void)hoisted__Str_2351;
        (void)hoisted__Str_2351;
        Bool hoisted__Bool_2352 = 0;
        (void)hoisted__Bool_2352;
        Str_delete(hoisted__Str_2351, hoisted__Bool_2352);
    }
    U32 hoisted__U32_2363 = 1;
    (void)hoisted__U32_2363;
    Bool hoisted__Bool_2364 = is_n(self, &(Type){.tag = Type_TAG_Enum}, hoisted__U32_2363);
    (void)hoisted__Bool_2364;
    if (hoisted__Bool_2364) {
        Str *hoisted__Str_2353 = get_payload(self);
        (void)hoisted__Str_2353;
        (void)hoisted__Str_2353;
        Bool hoisted__Bool_2354 = 0;
        (void)hoisted__Bool_2354;
        Str_delete(hoisted__Str_2353, hoisted__Bool_2354);
    }
    U32 hoisted__U32_2365 = 1;
    (void)hoisted__U32_2365;
    Bool hoisted__Bool_2366 = is_n(self, &(Type){.tag = Type_TAG_Custom}, hoisted__U32_2365);
    (void)hoisted__Bool_2366;
    if (hoisted__Bool_2366) {
        Str *hoisted__Str_2355 = get_payload(self);
        (void)hoisted__Str_2355;
        (void)hoisted__Str_2355;
        Bool hoisted__Bool_2356 = 0;
        (void)hoisted__Bool_2356;
        Str_delete(hoisted__Str_2355, hoisted__Bool_2356);
    }
    U32 hoisted__U32_2367 = 1;
    (void)hoisted__U32_2367;
    Bool hoisted__Bool_2368 = is_n(self, &(Type){.tag = Type_TAG_Primitive}, hoisted__U32_2367);
    (void)hoisted__Bool_2368;
    if (hoisted__Bool_2368) {
        Primitive *hoisted__Primitive_2357 = get_payload(self);
        (void)hoisted__Primitive_2357;
        (void)hoisted__Primitive_2357;
        Bool hoisted__Bool_2358 = 0;
        (void)hoisted__Bool_2358;
        Primitive_delete(hoisted__Primitive_2357, hoisted__Bool_2358);
    }
    U32 hoisted__U32_2369 = 1;
    (void)hoisted__U32_2369;
    Bool hoisted__Bool_2370 = is_n(self, &(Type){.tag = Type_TAG_FuncPtrSig}, hoisted__U32_2369);
    (void)hoisted__Bool_2370;
    if (hoisted__Bool_2370) {
        Str *hoisted__Str_2359 = get_payload(self);
        (void)hoisted__Str_2359;
        (void)hoisted__Str_2359;
        Bool hoisted__Bool_2360 = 0;
        (void)hoisted__Bool_2360;
        Str_delete(hoisted__Str_2359, hoisted__Bool_2360);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U32 hoisted__U32_2471 = 1;
    (void)hoisted__U32_2471;
    Bool hoisted__Bool_2472 = is_n(self, &(Type){.tag = Type_TAG_Unknown}, hoisted__U32_2471);
    (void)hoisted__Bool_2472;
    if (hoisted__Bool_2472) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U32 hoisted__U32_2473 = 1;
    (void)hoisted__U32_2473;
    Bool hoisted__Bool_2474 = is_n(self, &(Type){.tag = Type_TAG_None}, hoisted__U32_2473);
    (void)hoisted__Bool_2474;
    if (hoisted__Bool_2474) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U32 hoisted__U32_2475 = 1;
    (void)hoisted__U32_2475;
    Bool hoisted__Bool_2476 = is_n(self, &(Type){.tag = Type_TAG_Struct}, hoisted__U32_2475);
    (void)hoisted__Bool_2476;
    if (hoisted__Bool_2476) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2461 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2461;
        Type *hoisted__Type_2462 = Type_Struct(hoisted__Str_2461);
        (void)hoisted__Type_2462;
        { Type * _ret_val = hoisted__Type_2462;
                return _ret_val; }
    }
    U32 hoisted__U32_2477 = 1;
    (void)hoisted__U32_2477;
    Bool hoisted__Bool_2478 = is_n(self, &(Type){.tag = Type_TAG_StructDef}, hoisted__U32_2477);
    (void)hoisted__Bool_2478;
    if (hoisted__Bool_2478) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U32 hoisted__U32_2479 = 1;
    (void)hoisted__U32_2479;
    Bool hoisted__Bool_2480 = is_n(self, &(Type){.tag = Type_TAG_Enum}, hoisted__U32_2479);
    (void)hoisted__Bool_2480;
    if (hoisted__Bool_2480) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2463 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2463;
        Type *hoisted__Type_2464 = Type_Enum(hoisted__Str_2463);
        (void)hoisted__Type_2464;
        { Type * _ret_val = hoisted__Type_2464;
                return _ret_val; }
    }
    U32 hoisted__U32_2481 = 1;
    (void)hoisted__U32_2481;
    Bool hoisted__Bool_2482 = is_n(self, &(Type){.tag = Type_TAG_EnumDef}, hoisted__U32_2481);
    (void)hoisted__Bool_2482;
    if (hoisted__Bool_2482) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U32 hoisted__U32_2483 = 1;
    (void)hoisted__U32_2483;
    Bool hoisted__Bool_2484 = is_n(self, &(Type){.tag = Type_TAG_FuncDef}, hoisted__U32_2483);
    (void)hoisted__Bool_2484;
    if (hoisted__Bool_2484) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U32 hoisted__U32_2485 = 1;
    (void)hoisted__U32_2485;
    Bool hoisted__Bool_2486 = is_n(self, &(Type){.tag = Type_TAG_FuncPtr}, hoisted__U32_2485);
    (void)hoisted__Bool_2486;
    if (hoisted__Bool_2486) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U32 hoisted__U32_2487 = 1;
    (void)hoisted__U32_2487;
    Bool hoisted__Bool_2488 = is_n(self, &(Type){.tag = Type_TAG_Dynamic}, hoisted__U32_2487);
    (void)hoisted__Bool_2488;
    if (hoisted__Bool_2488) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U32 hoisted__U32_2489 = 1;
    (void)hoisted__U32_2489;
    Bool hoisted__Bool_2490 = is_n(self, &(Type){.tag = Type_TAG_Custom}, hoisted__U32_2489);
    (void)hoisted__Bool_2490;
    if (hoisted__Bool_2490) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2465 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2465;
        Type *hoisted__Type_2466 = Type_Custom(hoisted__Str_2465);
        (void)hoisted__Type_2466;
        { Type * _ret_val = hoisted__Type_2466;
                return _ret_val; }
    }
    U32 hoisted__U32_2491 = 1;
    (void)hoisted__U32_2491;
    Bool hoisted__Bool_2492 = is_n(self, &(Type){.tag = Type_TAG_Primitive}, hoisted__U32_2491);
    (void)hoisted__Bool_2492;
    if (hoisted__Bool_2492) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2467 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2467;
        Type *hoisted__Type_2468 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2467; _oa; }));
        (void)hoisted__Type_2468;
        { Type * _ret_val = hoisted__Type_2468;
                return _ret_val; }
    }
    U32 hoisted__U32_2493 = 1;
    (void)hoisted__U32_2493;
    Bool hoisted__Bool_2494 = is_n(self, &(Type){.tag = Type_TAG_FuncPtrSig}, hoisted__U32_2493);
    (void)hoisted__Bool_2494;
    if (hoisted__Bool_2494) {
        Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2469 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2469;
        Type *hoisted__Type_2470 = Type_FuncPtrSig(hoisted__Str_2469);
        (void)hoisted__Type_2470;
        { Type * _ret_val = hoisted__Type_2470;
                return _ret_val; }
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
}

U32 Type_size(void) {
    U32 hoisted__U32_2495 = 24;
    (void)hoisted__U32_2495;
    return hoisted__U32_2495;
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
FuncType *FuncType_CoreFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_CoreFunc };
    return r;
}
FuncType *FuncType_CoreProc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_CoreProc };
    return r;
}
Bool FuncType_eq(FuncType * self, FuncType * other) {
    U32 hoisted__U32_2643 = 1;
    (void)hoisted__U32_2643;
    Bool hoisted__Bool_2644 = is_n(self, &(FuncType){.tag = FuncType_TAG_Func}, hoisted__U32_2643);
    (void)hoisted__Bool_2644;
    if (hoisted__Bool_2644) {
        U32 hoisted__U32_2623 = 1;
        (void)hoisted__U32_2623;
        Bool hoisted__Bool_2624 = is_n(other, &(FuncType){.tag = FuncType_TAG_Func}, hoisted__U32_2623);
        (void)hoisted__Bool_2624;
        { Bool _ret_val = hoisted__Bool_2624;
                return _ret_val; }
    }
    U32 hoisted__U32_2645 = 1;
    (void)hoisted__U32_2645;
    Bool hoisted__Bool_2646 = is_n(self, &(FuncType){.tag = FuncType_TAG_Proc}, hoisted__U32_2645);
    (void)hoisted__Bool_2646;
    if (hoisted__Bool_2646) {
        U32 hoisted__U32_2625 = 1;
        (void)hoisted__U32_2625;
        Bool hoisted__Bool_2626 = is_n(other, &(FuncType){.tag = FuncType_TAG_Proc}, hoisted__U32_2625);
        (void)hoisted__Bool_2626;
        { Bool _ret_val = hoisted__Bool_2626;
                return _ret_val; }
    }
    U32 hoisted__U32_2647 = 1;
    (void)hoisted__U32_2647;
    Bool hoisted__Bool_2648 = is_n(self, &(FuncType){.tag = FuncType_TAG_Test}, hoisted__U32_2647);
    (void)hoisted__Bool_2648;
    if (hoisted__Bool_2648) {
        U32 hoisted__U32_2627 = 1;
        (void)hoisted__U32_2627;
        Bool hoisted__Bool_2628 = is_n(other, &(FuncType){.tag = FuncType_TAG_Test}, hoisted__U32_2627);
        (void)hoisted__Bool_2628;
        { Bool _ret_val = hoisted__Bool_2628;
                return _ret_val; }
    }
    U32 hoisted__U32_2649 = 1;
    (void)hoisted__U32_2649;
    Bool hoisted__Bool_2650 = is_n(self, &(FuncType){.tag = FuncType_TAG_Macro}, hoisted__U32_2649);
    (void)hoisted__Bool_2650;
    if (hoisted__Bool_2650) {
        U32 hoisted__U32_2629 = 1;
        (void)hoisted__U32_2629;
        Bool hoisted__Bool_2630 = is_n(other, &(FuncType){.tag = FuncType_TAG_Macro}, hoisted__U32_2629);
        (void)hoisted__Bool_2630;
        { Bool _ret_val = hoisted__Bool_2630;
                return _ret_val; }
    }
    U32 hoisted__U32_2651 = 1;
    (void)hoisted__U32_2651;
    Bool hoisted__Bool_2652 = is_n(self, &(FuncType){.tag = FuncType_TAG_ExtFunc}, hoisted__U32_2651);
    (void)hoisted__Bool_2652;
    if (hoisted__Bool_2652) {
        U32 hoisted__U32_2631 = 1;
        (void)hoisted__U32_2631;
        Bool hoisted__Bool_2632 = is_n(other, &(FuncType){.tag = FuncType_TAG_ExtFunc}, hoisted__U32_2631);
        (void)hoisted__Bool_2632;
        { Bool _ret_val = hoisted__Bool_2632;
                return _ret_val; }
    }
    U32 hoisted__U32_2653 = 1;
    (void)hoisted__U32_2653;
    Bool hoisted__Bool_2654 = is_n(self, &(FuncType){.tag = FuncType_TAG_ExtProc}, hoisted__U32_2653);
    (void)hoisted__Bool_2654;
    if (hoisted__Bool_2654) {
        U32 hoisted__U32_2633 = 1;
        (void)hoisted__U32_2633;
        Bool hoisted__Bool_2634 = is_n(other, &(FuncType){.tag = FuncType_TAG_ExtProc}, hoisted__U32_2633);
        (void)hoisted__Bool_2634;
        { Bool _ret_val = hoisted__Bool_2634;
                return _ret_val; }
    }
    U32 hoisted__U32_2655 = 1;
    (void)hoisted__U32_2655;
    Bool hoisted__Bool_2656 = is_n(self, &(FuncType){.tag = FuncType_TAG_LazyFunc}, hoisted__U32_2655);
    (void)hoisted__Bool_2656;
    if (hoisted__Bool_2656) {
        U32 hoisted__U32_2635 = 1;
        (void)hoisted__U32_2635;
        Bool hoisted__Bool_2636 = is_n(other, &(FuncType){.tag = FuncType_TAG_LazyFunc}, hoisted__U32_2635);
        (void)hoisted__Bool_2636;
        { Bool _ret_val = hoisted__Bool_2636;
                return _ret_val; }
    }
    U32 hoisted__U32_2657 = 1;
    (void)hoisted__U32_2657;
    Bool hoisted__Bool_2658 = is_n(self, &(FuncType){.tag = FuncType_TAG_LazyProc}, hoisted__U32_2657);
    (void)hoisted__Bool_2658;
    if (hoisted__Bool_2658) {
        U32 hoisted__U32_2637 = 1;
        (void)hoisted__U32_2637;
        Bool hoisted__Bool_2638 = is_n(other, &(FuncType){.tag = FuncType_TAG_LazyProc}, hoisted__U32_2637);
        (void)hoisted__Bool_2638;
        { Bool _ret_val = hoisted__Bool_2638;
                return _ret_val; }
    }
    U32 hoisted__U32_2659 = 1;
    (void)hoisted__U32_2659;
    Bool hoisted__Bool_2660 = is_n(self, &(FuncType){.tag = FuncType_TAG_CoreFunc}, hoisted__U32_2659);
    (void)hoisted__Bool_2660;
    if (hoisted__Bool_2660) {
        U32 hoisted__U32_2639 = 1;
        (void)hoisted__U32_2639;
        Bool hoisted__Bool_2640 = is_n(other, &(FuncType){.tag = FuncType_TAG_CoreFunc}, hoisted__U32_2639);
        (void)hoisted__Bool_2640;
        { Bool _ret_val = hoisted__Bool_2640;
                return _ret_val; }
    }
    U32 hoisted__U32_2661 = 1;
    (void)hoisted__U32_2661;
    Bool hoisted__Bool_2662 = is_n(self, &(FuncType){.tag = FuncType_TAG_CoreProc}, hoisted__U32_2661);
    (void)hoisted__Bool_2662;
    if (hoisted__Bool_2662) {
        U32 hoisted__U32_2641 = 1;
        (void)hoisted__U32_2641;
        Bool hoisted__Bool_2642 = is_n(other, &(FuncType){.tag = FuncType_TAG_CoreProc}, hoisted__U32_2641);
        (void)hoisted__Bool_2642;
        { Bool _ret_val = hoisted__Bool_2642;
                return _ret_val; }
    }
    Bool hoisted__Bool_2663 = 0;
    (void)hoisted__Bool_2663;
    return hoisted__Bool_2663;
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
    Bool hoisted__Bool_2693 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2693;
    if (hoisted__Bool_2693) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2694 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2694;
    if (hoisted__Bool_2694) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2695 = (Str){.c_str = (void *)"FuncType.clone:130:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2695;
    UNREACHABLE(&hoisted__Str_2695);
    Str_delete(&hoisted__Str_2695, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2696 = 1;
    (void)hoisted__U32_2696;
    return hoisted__U32_2696;
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
    U32 hoisted__U32_2705 = 1;
    (void)hoisted__U32_2705;
    Bool hoisted__Bool_2706 = is_n(self, &(OwnType){.tag = OwnType_TAG_Own}, hoisted__U32_2705);
    (void)hoisted__Bool_2706;
    if (hoisted__Bool_2706) {
        U32 hoisted__U32_2699 = 1;
        (void)hoisted__U32_2699;
        Bool hoisted__Bool_2700 = is_n(other, &(OwnType){.tag = OwnType_TAG_Own}, hoisted__U32_2699);
        (void)hoisted__Bool_2700;
        { Bool _ret_val = hoisted__Bool_2700;
                return _ret_val; }
    }
    U32 hoisted__U32_2707 = 1;
    (void)hoisted__U32_2707;
    Bool hoisted__Bool_2708 = is_n(self, &(OwnType){.tag = OwnType_TAG_Ref}, hoisted__U32_2707);
    (void)hoisted__Bool_2708;
    if (hoisted__Bool_2708) {
        U32 hoisted__U32_2701 = 1;
        (void)hoisted__U32_2701;
        Bool hoisted__Bool_2702 = is_n(other, &(OwnType){.tag = OwnType_TAG_Ref}, hoisted__U32_2701);
        (void)hoisted__Bool_2702;
        { Bool _ret_val = hoisted__Bool_2702;
                return _ret_val; }
    }
    U32 hoisted__U32_2709 = 1;
    (void)hoisted__U32_2709;
    Bool hoisted__Bool_2710 = is_n(self, &(OwnType){.tag = OwnType_TAG_Shallow}, hoisted__U32_2709);
    (void)hoisted__Bool_2710;
    if (hoisted__Bool_2710) {
        U32 hoisted__U32_2703 = 1;
        (void)hoisted__U32_2703;
        Bool hoisted__Bool_2704 = is_n(other, &(OwnType){.tag = OwnType_TAG_Shallow}, hoisted__U32_2703);
        (void)hoisted__Bool_2704;
        { Bool _ret_val = hoisted__Bool_2704;
                return _ret_val; }
    }
    Bool hoisted__Bool_2711 = 0;
    (void)hoisted__Bool_2711;
    return hoisted__Bool_2711;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2719 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2719;
    if (hoisted__Bool_2719) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2720 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2720;
    if (hoisted__Bool_2720) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2721 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2721;
    if (hoisted__Bool_2721) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2722 = (Str){.c_str = (void *)"OwnType.clone:142:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2722;
    UNREACHABLE(&hoisted__Str_2722);
    Str_delete(&hoisted__Str_2722, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2723 = 1;
    (void)hoisted__U32_2723;
    return hoisted__U32_2723;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2725 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2725;
    Declaration *hoisted__Declaration_2726 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2726->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2726->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2726->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2726->is_mut = self->is_mut;
    hoisted__Declaration_2726->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2726->is_priv = self->is_priv;
    hoisted__Declaration_2726->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2726->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2726->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2726->default_value = hoisted__Expr_2725;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2726->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2726;
    return hoisted__Declaration_2726;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2727 = 0;
    (void)hoisted__Bool_2727;
    Str_delete(&self->name, hoisted__Bool_2727);
    Bool hoisted__Bool_2728 = 0;
    (void)hoisted__Bool_2728;
    Str_delete(&self->doc, hoisted__Bool_2728);
    Bool hoisted__Bool_2729 = 0;
    (void)hoisted__Bool_2729;
    Str_delete(&self->explicit_type, hoisted__Bool_2729);
    Bool hoisted__Bool_2730 = 0;
    (void)hoisted__Bool_2730;
    Bool_delete(&self->is_mut, hoisted__Bool_2730);
    Bool hoisted__Bool_2731 = 0;
    (void)hoisted__Bool_2731;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2731);
    Bool hoisted__Bool_2732 = 0;
    (void)hoisted__Bool_2732;
    Bool_delete(&self->is_priv, hoisted__Bool_2732);
    Bool hoisted__Bool_2733 = 0;
    (void)hoisted__Bool_2733;
    Bool_delete(&self->used, hoisted__Bool_2733);
    Bool hoisted__Bool_2734 = 0;
    (void)hoisted__Bool_2734;
    OwnType_delete(&self->own_type, hoisted__Bool_2734);
    Bool hoisted__Bool_2735 = 0;
    (void)hoisted__Bool_2735;
    Type_delete(&self->til_type, hoisted__Bool_2735);
    Bool hoisted__Bool_2736 = 1;
    (void)hoisted__Bool_2736;
    Expr_delete(self->default_value, hoisted__Bool_2736);
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Str_delete(&self->orig_name, hoisted__Bool_2737);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2738 = 104;
    (void)hoisted__U32_2738;
    return hoisted__U32_2738;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2740 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2740->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2740->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2740->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2740->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2740->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2740->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2740->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2740->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2740->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2740->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2740->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2740;
    return hoisted__FunctionDef_2740;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2741 = 0;
    (void)hoisted__Bool_2741;
    FuncType_delete(&self->func_type, hoisted__Bool_2741);
    Bool hoisted__Bool_2742 = 0;
    (void)hoisted__Bool_2742;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2742);
    Bool hoisted__Bool_2743 = 0;
    (void)hoisted__Bool_2743;
    Str_delete(&self->return_type, hoisted__Bool_2743);
    Bool hoisted__Bool_2744 = 0;
    (void)hoisted__Bool_2744;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2744);
    Bool hoisted__Bool_2745 = 0;
    (void)hoisted__Bool_2745;
    I32_delete(&self->variadic_index, hoisted__Bool_2745);
    Bool hoisted__Bool_2746 = 0;
    (void)hoisted__Bool_2746;
    I32_delete(&self->kwargs_index, hoisted__Bool_2746);
    Bool hoisted__Bool_2747 = 0;
    (void)hoisted__Bool_2747;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2747);
    Bool hoisted__Bool_2748 = 0;
    (void)hoisted__Bool_2748;
    Bool_delete(&self->auto_generated, hoisted__Bool_2748);
    Bool hoisted__Bool_2749 = 0;
    (void)hoisted__Bool_2749;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2749);
    Bool hoisted__Bool_2750 = 0;
    (void)hoisted__Bool_2750;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2750);
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Str_delete(&self->closure_name, hoisted__Bool_2751);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2752 = 0;
    (void)hoisted__U32_2752;
    U64 hoisted__U64_2753 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2752); });
    (void)hoisted__U64_2753;
    return hoisted__U64_2753;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2754 = 104;
    (void)hoisted__U32_2754;
    return hoisted__U32_2754;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2757 = malloc(sizeof(FCallData));
    hoisted__FCallData_2757->is_splat = self->is_splat;
    hoisted__FCallData_2757->does_throw = self->does_throw;
    hoisted__FCallData_2757->is_bang = self->is_bang;
    hoisted__FCallData_2757->own_args = self->own_args;
    hoisted__FCallData_2757->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2757->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2757;
    return hoisted__FCallData_2757;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2758 = 0;
    (void)hoisted__Bool_2758;
    Bool_delete(&self->is_splat, hoisted__Bool_2758);
    Bool hoisted__Bool_2759 = 0;
    (void)hoisted__Bool_2759;
    Bool_delete(&self->does_throw, hoisted__Bool_2759);
    Bool hoisted__Bool_2760 = 0;
    (void)hoisted__Bool_2760;
    Bool_delete(&self->is_bang, hoisted__Bool_2760);
    Bool hoisted__Bool_2761 = 0;
    (void)hoisted__Bool_2761;
    U64_delete(&self->own_args, hoisted__Bool_2761);
    Bool hoisted__Bool_2762 = 0;
    (void)hoisted__Bool_2762;
    Bool_delete(&self->swap_replace, hoisted__Bool_2762);
    Bool hoisted__Bool_2763 = 0;
    (void)hoisted__Bool_2763;
    Type_delete(&self->til_type, hoisted__Bool_2763);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2764 = 0;
    (void)hoisted__U32_2764;
    U64 hoisted__U64_2765 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2764); });
    (void)hoisted__U64_2765;
    return hoisted__U64_2765;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2766 = 48;
    (void)hoisted__U32_2766;
    return hoisted__U32_2766;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2778 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2778->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2778->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2778;
    return hoisted__LiteralNumData_2778;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2779 = 0;
    (void)hoisted__Bool_2779;
    Str_delete(&self->text, hoisted__Bool_2779);
    Bool hoisted__Bool_2780 = 0;
    (void)hoisted__Bool_2780;
    Type_delete(&self->til_type, hoisted__Bool_2780);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2781 = 0;
    (void)hoisted__U32_2781;
    U64 hoisted__U64_2782 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2781); });
    (void)hoisted__U64_2782;
    return hoisted__U64_2782;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2783 = 40;
    (void)hoisted__U32_2783;
    return hoisted__U32_2783;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2793 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2793->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2793->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2793;
    return hoisted__IdentData_2793;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2794 = 0;
    (void)hoisted__Bool_2794;
    Str_delete(&self->name, hoisted__Bool_2794);
    Bool hoisted__Bool_2795 = 0;
    (void)hoisted__Bool_2795;
    Type_delete(&self->til_type, hoisted__Bool_2795);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2796 = 0;
    (void)hoisted__U32_2796;
    U64 hoisted__U64_2797 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2796); });
    (void)hoisted__U64_2797;
    return hoisted__U64_2797;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2798 = 40;
    (void)hoisted__U32_2798;
    return hoisted__U32_2798;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2804 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2804->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2804->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2804;
    return hoisted__FieldAccessData_2804;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2805 = 0;
    (void)hoisted__Bool_2805;
    Str_delete(&self->name, hoisted__Bool_2805);
    Bool hoisted__Bool_2806 = 0;
    (void)hoisted__Bool_2806;
    Type_delete(&self->til_type, hoisted__Bool_2806);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2807 = 0;
    (void)hoisted__U32_2807;
    U64 hoisted__U64_2808 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2807); });
    (void)hoisted__U64_2808;
    return hoisted__U64_2808;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2809 = 40;
    (void)hoisted__U32_2809;
    return hoisted__U32_2809;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2890 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2890->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2890->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2890->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2890->is_interface = self->is_interface;
    hoisted__StructDef_2890->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2890->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2890;
    return hoisted__StructDef_2890;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2891 = 0;
    (void)hoisted__Bool_2891;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2891);
    Bool hoisted__Bool_2892 = 0;
    (void)hoisted__Bool_2892;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2892);
    Bool hoisted__Bool_2893 = 0;
    (void)hoisted__Bool_2893;
    Str_delete(&self->c_tag, hoisted__Bool_2893);
    Bool hoisted__Bool_2894 = 0;
    (void)hoisted__Bool_2894;
    Bool_delete(&self->is_interface, hoisted__Bool_2894);
    Bool hoisted__Bool_2895 = 0;
    (void)hoisted__Bool_2895;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2895);
    Bool hoisted__Bool_2896 = 0;
    (void)hoisted__Bool_2896;
    Str_delete(&self->implements_name, hoisted__Bool_2896);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2897 = 0;
    (void)hoisted__U32_2897;
    U64 hoisted__U64_2898 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2897); });
    (void)hoisted__U64_2898;
    return hoisted__U64_2898;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2899 = 72;
    (void)hoisted__U32_2899;
    return hoisted__U32_2899;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2904 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2904->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2904->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2904->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2904->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2904->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2904->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2904->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2904;
    return hoisted__EnumDef_2904;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2905 = 0;
    (void)hoisted__Bool_2905;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2905);
    Bool hoisted__Bool_2906 = 0;
    (void)hoisted__Bool_2906;
    Vec__Str_delete(&self->variants, hoisted__Bool_2906);
    Bool hoisted__Bool_2907 = 0;
    (void)hoisted__Bool_2907;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2907);
    Bool hoisted__Bool_2908 = 0;
    (void)hoisted__Bool_2908;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2908);
    Bool hoisted__Bool_2909 = 0;
    (void)hoisted__Bool_2909;
    Str_delete(&self->implements_name, hoisted__Bool_2909);
    Bool hoisted__Bool_2910 = 0;
    (void)hoisted__Bool_2910;
    Str_delete(&self->tag_type, hoisted__Bool_2910);
    Bool hoisted__Bool_2911 = 0;
    (void)hoisted__Bool_2911;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2911);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2912 = 0;
    (void)hoisted__U32_2912;
    U64 hoisted__U64_2913 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2912); });
    (void)hoisted__U64_2913;
    return hoisted__U64_2913;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2914 = 128;
    (void)hoisted__U32_2914;
    return hoisted__U32_2914;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_3014 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_3014->name = *_ca; free(_ca); }
    hoisted__AssignData_3014->save_old_delete = self->save_old_delete;
    hoisted__AssignData_3014->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_3014->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_3014;
    return hoisted__AssignData_3014;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_3015 = 0;
    (void)hoisted__Bool_3015;
    Str_delete(&self->name, hoisted__Bool_3015);
    Bool hoisted__Bool_3016 = 0;
    (void)hoisted__Bool_3016;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3016);
    Bool hoisted__Bool_3017 = 0;
    (void)hoisted__Bool_3017;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_3017);
    Bool hoisted__Bool_3018 = 0;
    (void)hoisted__Bool_3018;
    Bool_delete(&self->swap_replace, hoisted__Bool_3018);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_3019 = 0;
    (void)hoisted__U32_3019;
    U64 hoisted__U64_3020 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3019); });
    (void)hoisted__U64_3020;
    return hoisted__U64_3020;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_3021 = 24;
    (void)hoisted__U32_3021;
    return hoisted__U32_3021;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_3023 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_3023->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_3023->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_3023;
    return hoisted__FieldAssignData_3023;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_3024 = 0;
    (void)hoisted__Bool_3024;
    Str_delete(&self->name, hoisted__Bool_3024);
    Bool hoisted__Bool_3025 = 0;
    (void)hoisted__Bool_3025;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3025);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_3026 = 0;
    (void)hoisted__U32_3026;
    U64 hoisted__U64_3027 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3026); });
    (void)hoisted__U64_3027;
    return hoisted__U64_3027;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_3028 = 24;
    (void)hoisted__U32_3028;
    return hoisted__U32_3028;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_3030 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_3030->name = *_ca; free(_ca); }
    hoisted__ForInData_3030->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_3030->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_3030->name2 = *_ca; free(_ca); }
    hoisted__ForInData_3030->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_3030;
    return hoisted__ForInData_3030;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_3031 = 0;
    (void)hoisted__Bool_3031;
    Str_delete(&self->name, hoisted__Bool_3031);
    Bool hoisted__Bool_3032 = 0;
    (void)hoisted__Bool_3032;
    Bool_delete(&self->is_mut, hoisted__Bool_3032);
    Bool hoisted__Bool_3033 = 0;
    (void)hoisted__Bool_3033;
    Type_delete(&self->til_type, hoisted__Bool_3033);
    Bool hoisted__Bool_3034 = 0;
    (void)hoisted__Bool_3034;
    Str_delete(&self->name2, hoisted__Bool_3034);
    Bool hoisted__Bool_3035 = 0;
    (void)hoisted__Bool_3035;
    Bool_delete(&self->is_mut2, hoisted__Bool_3035);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_3036 = 0;
    (void)hoisted__U32_3036;
    U64 hoisted__U64_3037 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3036); });
    (void)hoisted__U64_3037;
    return hoisted__U64_3037;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_3038 = 72;
    (void)hoisted__U32_3038;
    return hoisted__U32_3038;
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
    U32 hoisted__U32_3081 = 1;
    (void)hoisted__U32_3081;
    Bool hoisted__Bool_3082 = is_n(self, &(Literal){.tag = Literal_TAG_Str}, hoisted__U32_3081);
    (void)hoisted__Bool_3082;
    if (hoisted__Bool_3082) {
        Str *hoisted__Str_3075 = get_payload(self);
        (void)hoisted__Str_3075;
        (void)hoisted__Str_3075;
        Bool hoisted__Bool_3076 = 0;
        (void)hoisted__Bool_3076;
        Str_delete(hoisted__Str_3075, hoisted__Bool_3076);
    }
    U32 hoisted__U32_3083 = 1;
    (void)hoisted__U32_3083;
    Bool hoisted__Bool_3084 = is_n(self, &(Literal){.tag = Literal_TAG_Num}, hoisted__U32_3083);
    (void)hoisted__Bool_3084;
    if (hoisted__Bool_3084) {
        LiteralNumData *hoisted__LiteralNumData_3077 = get_payload(self);
        (void)hoisted__LiteralNumData_3077;
        (void)hoisted__LiteralNumData_3077;
        Bool hoisted__Bool_3078 = 0;
        (void)hoisted__Bool_3078;
        LiteralNumData_delete(hoisted__LiteralNumData_3077, hoisted__Bool_3078);
    }
    U32 hoisted__U32_3085 = 1;
    (void)hoisted__U32_3085;
    Bool hoisted__Bool_3086 = is_n(self, &(Literal){.tag = Literal_TAG_Bool}, hoisted__U32_3085);
    (void)hoisted__Bool_3086;
    if (hoisted__Bool_3086) {
        Bool *hoisted__Bool_3079 = get_payload(self);
        (void)hoisted__Bool_3079;
        (void)hoisted__Bool_3079;
        Bool hoisted__Bool_3080 = 0;
        (void)hoisted__Bool_3080;
        Bool_delete(hoisted__Bool_3079, hoisted__Bool_3080);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_3141 = 1;
    (void)hoisted__U32_3141;
    Bool hoisted__Bool_3142 = is_n(self, &(Literal){.tag = Literal_TAG_Str}, hoisted__U32_3141);
    (void)hoisted__Bool_3142;
    if (hoisted__Bool_3142) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3136 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3136;
        Literal *hoisted__Literal_3137 = Literal_Str(hoisted__Str_3136);
        (void)hoisted__Literal_3137;
        { Literal * _ret_val = hoisted__Literal_3137;
                return _ret_val; }
    }
    U32 hoisted__U32_3143 = 1;
    (void)hoisted__U32_3143;
    Bool hoisted__Bool_3144 = is_n(self, &(Literal){.tag = Literal_TAG_Num}, hoisted__U32_3143);
    (void)hoisted__Bool_3144;
    if (hoisted__Bool_3144) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3138 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3138;
        Literal *hoisted__Literal_3139 = Literal_Num(hoisted__LiteralNumData_3138);
        (void)hoisted__Literal_3139;
        { Literal * _ret_val = hoisted__Literal_3139;
                return _ret_val; }
    }
    U32 hoisted__U32_3145 = 1;
    (void)hoisted__U32_3145;
    Bool hoisted__Bool_3146 = is_n(self, &(Literal){.tag = Literal_TAG_Bool}, hoisted__U32_3145);
    (void)hoisted__Bool_3146;
    if (hoisted__Bool_3146) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3140 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3140;
        { Literal * _ret_val = hoisted__Literal_3140;
                return _ret_val; }
    }
    U32 hoisted__U32_3147 = 1;
    (void)hoisted__U32_3147;
    Bool hoisted__Bool_3148 = is_n(self, &(Literal){.tag = Literal_TAG_Null}, hoisted__U32_3147);
    (void)hoisted__Bool_3148;
    if (hoisted__Bool_3148) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U32 hoisted__U32_3149 = 1;
    (void)hoisted__U32_3149;
    Bool hoisted__Bool_3150 = is_n(self, &(Literal){.tag = Literal_TAG_MapLit}, hoisted__U32_3149);
    (void)hoisted__Bool_3150;
    if (hoisted__Bool_3150) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3151 = 48;
    (void)hoisted__U32_3151;
    return hoisted__U32_3151;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3154 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3154->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3154->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3154;
    return hoisted__MatchData_3154;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3155 = 0;
    (void)hoisted__Bool_3155;
    Type_delete(&self->til_type, hoisted__Bool_3155);
    Bool hoisted__Bool_3156 = 0;
    (void)hoisted__Bool_3156;
    Str_delete(&self->result_temp, hoisted__Bool_3156);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3157 = 0;
    (void)hoisted__U32_3157;
    U64 hoisted__U64_3158 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3157); });
    (void)hoisted__U64_3158;
    return hoisted__U64_3158;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3159 = 40;
    (void)hoisted__U32_3159;
    return hoisted__U32_3159;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3164 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3164->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3164->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3164;
    return hoisted__CaptureBlockData_3164;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3165 = 0;
    (void)hoisted__Bool_3165;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3165);
    Bool hoisted__Bool_3166 = 0;
    (void)hoisted__Bool_3166;
    Str_delete(&self->closure_name, hoisted__Bool_3166);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3167 = 0;
    (void)hoisted__U32_3167;
    U64 hoisted__U64_3168 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3167); });
    (void)hoisted__U64_3168;
    return hoisted__U64_3168;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3169 = 32;
    (void)hoisted__U32_3169;
    return hoisted__U32_3169;
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
NodeType *NodeType_BodyValue(CaptureBlockData * val) {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_BodyValue;
    r->data.BodyValue = *val;
    free(val);
    return r;
}
void NodeType_delete(NodeType * self, Bool call_free) {
    U32 hoisted__U32_3430 = 1;
    (void)hoisted__U32_3430;
    Bool hoisted__Bool_3431 = is_n(self, &(NodeType){.tag = NodeType_TAG_Literal}, hoisted__U32_3430);
    (void)hoisted__Bool_3431;
    if (hoisted__Bool_3431) {
        Literal *hoisted__Literal_3400 = get_payload(self);
        (void)hoisted__Literal_3400;
        (void)hoisted__Literal_3400;
        Bool hoisted__Bool_3401 = 0;
        (void)hoisted__Bool_3401;
        Literal_delete(hoisted__Literal_3400, hoisted__Bool_3401);
    }
    U32 hoisted__U32_3432 = 1;
    (void)hoisted__U32_3432;
    Bool hoisted__Bool_3433 = is_n(self, &(NodeType){.tag = NodeType_TAG_Ident}, hoisted__U32_3432);
    (void)hoisted__Bool_3433;
    if (hoisted__Bool_3433) {
        IdentData *hoisted__IdentData_3402 = get_payload(self);
        (void)hoisted__IdentData_3402;
        (void)hoisted__IdentData_3402;
        Bool hoisted__Bool_3403 = 0;
        (void)hoisted__Bool_3403;
        IdentData_delete(hoisted__IdentData_3402, hoisted__Bool_3403);
    }
    U32 hoisted__U32_3434 = 1;
    (void)hoisted__U32_3434;
    Bool hoisted__Bool_3435 = is_n(self, &(NodeType){.tag = NodeType_TAG_Decl}, hoisted__U32_3434);
    (void)hoisted__Bool_3435;
    if (hoisted__Bool_3435) {
        Declaration *hoisted__Declaration_3404 = get_payload(self);
        (void)hoisted__Declaration_3404;
        (void)hoisted__Declaration_3404;
        Bool hoisted__Bool_3405 = 0;
        (void)hoisted__Bool_3405;
        Declaration_delete(hoisted__Declaration_3404, hoisted__Bool_3405);
    }
    U32 hoisted__U32_3436 = 1;
    (void)hoisted__U32_3436;
    Bool hoisted__Bool_3437 = is_n(self, &(NodeType){.tag = NodeType_TAG_Assign}, hoisted__U32_3436);
    (void)hoisted__Bool_3437;
    if (hoisted__Bool_3437) {
        AssignData *hoisted__AssignData_3406 = get_payload(self);
        (void)hoisted__AssignData_3406;
        (void)hoisted__AssignData_3406;
        Bool hoisted__Bool_3407 = 0;
        (void)hoisted__Bool_3407;
        AssignData_delete(hoisted__AssignData_3406, hoisted__Bool_3407);
    }
    U32 hoisted__U32_3438 = 1;
    (void)hoisted__U32_3438;
    Bool hoisted__Bool_3439 = is_n(self, &(NodeType){.tag = NodeType_TAG_FCall}, hoisted__U32_3438);
    (void)hoisted__Bool_3439;
    if (hoisted__Bool_3439) {
        FCallData *hoisted__FCallData_3408 = get_payload(self);
        (void)hoisted__FCallData_3408;
        (void)hoisted__FCallData_3408;
        Bool hoisted__Bool_3409 = 0;
        (void)hoisted__Bool_3409;
        FCallData_delete(hoisted__FCallData_3408, hoisted__Bool_3409);
    }
    U32 hoisted__U32_3440 = 1;
    (void)hoisted__U32_3440;
    Bool hoisted__Bool_3441 = is_n(self, &(NodeType){.tag = NodeType_TAG_FuncDef}, hoisted__U32_3440);
    (void)hoisted__Bool_3441;
    if (hoisted__Bool_3441) {
        FunctionDef *hoisted__FunctionDef_3410 = get_payload(self);
        (void)hoisted__FunctionDef_3410;
        (void)hoisted__FunctionDef_3410;
        Bool hoisted__Bool_3411 = 0;
        (void)hoisted__Bool_3411;
        FunctionDef_delete(hoisted__FunctionDef_3410, hoisted__Bool_3411);
    }
    U32 hoisted__U32_3442 = 1;
    (void)hoisted__U32_3442;
    Bool hoisted__Bool_3443 = is_n(self, &(NodeType){.tag = NodeType_TAG_StructDef}, hoisted__U32_3442);
    (void)hoisted__Bool_3443;
    if (hoisted__Bool_3443) {
        StructDef *hoisted__StructDef_3412 = get_payload(self);
        (void)hoisted__StructDef_3412;
        (void)hoisted__StructDef_3412;
        Bool hoisted__Bool_3413 = 0;
        (void)hoisted__Bool_3413;
        StructDef_delete(hoisted__StructDef_3412, hoisted__Bool_3413);
    }
    U32 hoisted__U32_3444 = 1;
    (void)hoisted__U32_3444;
    Bool hoisted__Bool_3445 = is_n(self, &(NodeType){.tag = NodeType_TAG_EnumDef}, hoisted__U32_3444);
    (void)hoisted__Bool_3445;
    if (hoisted__Bool_3445) {
        EnumDef *hoisted__EnumDef_3414 = get_payload(self);
        (void)hoisted__EnumDef_3414;
        (void)hoisted__EnumDef_3414;
        Bool hoisted__Bool_3415 = 0;
        (void)hoisted__Bool_3415;
        EnumDef_delete(hoisted__EnumDef_3414, hoisted__Bool_3415);
    }
    U32 hoisted__U32_3446 = 1;
    (void)hoisted__U32_3446;
    Bool hoisted__Bool_3447 = is_n(self, &(NodeType){.tag = NodeType_TAG_FieldAccess}, hoisted__U32_3446);
    (void)hoisted__Bool_3447;
    if (hoisted__Bool_3447) {
        FieldAccessData *hoisted__FieldAccessData_3416 = get_payload(self);
        (void)hoisted__FieldAccessData_3416;
        (void)hoisted__FieldAccessData_3416;
        Bool hoisted__Bool_3417 = 0;
        (void)hoisted__Bool_3417;
        FieldAccessData_delete(hoisted__FieldAccessData_3416, hoisted__Bool_3417);
    }
    U32 hoisted__U32_3448 = 1;
    (void)hoisted__U32_3448;
    Bool hoisted__Bool_3449 = is_n(self, &(NodeType){.tag = NodeType_TAG_FieldAssign}, hoisted__U32_3448);
    (void)hoisted__Bool_3449;
    if (hoisted__Bool_3449) {
        FieldAssignData *hoisted__FieldAssignData_3418 = get_payload(self);
        (void)hoisted__FieldAssignData_3418;
        (void)hoisted__FieldAssignData_3418;
        Bool hoisted__Bool_3419 = 0;
        (void)hoisted__Bool_3419;
        FieldAssignData_delete(hoisted__FieldAssignData_3418, hoisted__Bool_3419);
    }
    U32 hoisted__U32_3450 = 1;
    (void)hoisted__U32_3450;
    Bool hoisted__Bool_3451 = is_n(self, &(NodeType){.tag = NodeType_TAG_ForIn}, hoisted__U32_3450);
    (void)hoisted__Bool_3451;
    if (hoisted__Bool_3451) {
        ForInData *hoisted__ForInData_3420 = get_payload(self);
        (void)hoisted__ForInData_3420;
        (void)hoisted__ForInData_3420;
        Bool hoisted__Bool_3421 = 0;
        (void)hoisted__Bool_3421;
        ForInData_delete(hoisted__ForInData_3420, hoisted__Bool_3421);
    }
    U32 hoisted__U32_3452 = 1;
    (void)hoisted__U32_3452;
    Bool hoisted__Bool_3453 = is_n(self, &(NodeType){.tag = NodeType_TAG_NamedArg}, hoisted__U32_3452);
    (void)hoisted__Bool_3453;
    if (hoisted__Bool_3453) {
        Str *hoisted__Str_3422 = get_payload(self);
        (void)hoisted__Str_3422;
        (void)hoisted__Str_3422;
        Bool hoisted__Bool_3423 = 0;
        (void)hoisted__Bool_3423;
        Str_delete(hoisted__Str_3422, hoisted__Bool_3423);
    }
    U32 hoisted__U32_3454 = 1;
    (void)hoisted__U32_3454;
    Bool hoisted__Bool_3455 = is_n(self, &(NodeType){.tag = NodeType_TAG_Match}, hoisted__U32_3454);
    (void)hoisted__Bool_3455;
    if (hoisted__Bool_3455) {
        MatchData *hoisted__MatchData_3424 = get_payload(self);
        (void)hoisted__MatchData_3424;
        (void)hoisted__MatchData_3424;
        Bool hoisted__Bool_3425 = 0;
        (void)hoisted__Bool_3425;
        MatchData_delete(hoisted__MatchData_3424, hoisted__Bool_3425);
    }
    U32 hoisted__U32_3456 = 1;
    (void)hoisted__U32_3456;
    Bool hoisted__Bool_3457 = is_n(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock}, hoisted__U32_3456);
    (void)hoisted__Bool_3457;
    if (hoisted__Bool_3457) {
        CaptureBlockData *hoisted__CaptureBlockData_3426 = get_payload(self);
        (void)hoisted__CaptureBlockData_3426;
        (void)hoisted__CaptureBlockData_3426;
        Bool hoisted__Bool_3427 = 0;
        (void)hoisted__Bool_3427;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3426, hoisted__Bool_3427);
    }
    U32 hoisted__U32_3458 = 1;
    (void)hoisted__U32_3458;
    Bool hoisted__Bool_3459 = is_n(self, &(NodeType){.tag = NodeType_TAG_BodyValue}, hoisted__U32_3458);
    (void)hoisted__Bool_3459;
    if (hoisted__Bool_3459) {
        CaptureBlockData *hoisted__CaptureBlockData_3428 = get_payload(self);
        (void)hoisted__CaptureBlockData_3428;
        (void)hoisted__CaptureBlockData_3428;
        Bool hoisted__Bool_3429 = 0;
        (void)hoisted__Bool_3429;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3428, hoisted__Bool_3429);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3723 = 1;
    (void)hoisted__U32_3723;
    Bool hoisted__Bool_3724 = is_n(self, &(NodeType){.tag = NodeType_TAG_Body}, hoisted__U32_3723);
    (void)hoisted__Bool_3724;
    if (hoisted__Bool_3724) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U32 hoisted__U32_3725 = 1;
    (void)hoisted__U32_3725;
    Bool hoisted__Bool_3726 = is_n(self, &(NodeType){.tag = NodeType_TAG_Literal}, hoisted__U32_3725);
    (void)hoisted__Bool_3726;
    if (hoisted__Bool_3726) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3695 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3695;
        NodeType *hoisted__NodeType_3696 = NodeType_Literal(hoisted__Literal_3695);
        (void)hoisted__NodeType_3696;
        { NodeType * _ret_val = hoisted__NodeType_3696;
                return _ret_val; }
    }
    U32 hoisted__U32_3727 = 1;
    (void)hoisted__U32_3727;
    Bool hoisted__Bool_3728 = is_n(self, &(NodeType){.tag = NodeType_TAG_Ident}, hoisted__U32_3727);
    (void)hoisted__Bool_3728;
    if (hoisted__Bool_3728) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3697 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3697;
        NodeType *hoisted__NodeType_3698 = NodeType_Ident(hoisted__IdentData_3697);
        (void)hoisted__NodeType_3698;
        { NodeType * _ret_val = hoisted__NodeType_3698;
                return _ret_val; }
    }
    U32 hoisted__U32_3729 = 1;
    (void)hoisted__U32_3729;
    Bool hoisted__Bool_3730 = is_n(self, &(NodeType){.tag = NodeType_TAG_Decl}, hoisted__U32_3729);
    (void)hoisted__Bool_3730;
    if (hoisted__Bool_3730) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3699 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3699;
        NodeType *hoisted__NodeType_3700 = NodeType_Decl(hoisted__Declaration_3699);
        (void)hoisted__NodeType_3700;
        { NodeType * _ret_val = hoisted__NodeType_3700;
                return _ret_val; }
    }
    U32 hoisted__U32_3731 = 1;
    (void)hoisted__U32_3731;
    Bool hoisted__Bool_3732 = is_n(self, &(NodeType){.tag = NodeType_TAG_Assign}, hoisted__U32_3731);
    (void)hoisted__Bool_3732;
    if (hoisted__Bool_3732) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3701 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3701;
        NodeType *hoisted__NodeType_3702 = NodeType_Assign(hoisted__AssignData_3701);
        (void)hoisted__NodeType_3702;
        { NodeType * _ret_val = hoisted__NodeType_3702;
                return _ret_val; }
    }
    U32 hoisted__U32_3733 = 1;
    (void)hoisted__U32_3733;
    Bool hoisted__Bool_3734 = is_n(self, &(NodeType){.tag = NodeType_TAG_FCall}, hoisted__U32_3733);
    (void)hoisted__Bool_3734;
    if (hoisted__Bool_3734) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3703 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3703;
        NodeType *hoisted__NodeType_3704 = NodeType_FCall(hoisted__FCallData_3703);
        (void)hoisted__NodeType_3704;
        { NodeType * _ret_val = hoisted__NodeType_3704;
                return _ret_val; }
    }
    U32 hoisted__U32_3735 = 1;
    (void)hoisted__U32_3735;
    Bool hoisted__Bool_3736 = is_n(self, &(NodeType){.tag = NodeType_TAG_FuncDef}, hoisted__U32_3735);
    (void)hoisted__Bool_3736;
    if (hoisted__Bool_3736) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3705 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3705;
        NodeType *hoisted__NodeType_3706 = NodeType_FuncDef(hoisted__FunctionDef_3705);
        (void)hoisted__NodeType_3706;
        { NodeType * _ret_val = hoisted__NodeType_3706;
                return _ret_val; }
    }
    U32 hoisted__U32_3737 = 1;
    (void)hoisted__U32_3737;
    Bool hoisted__Bool_3738 = is_n(self, &(NodeType){.tag = NodeType_TAG_StructDef}, hoisted__U32_3737);
    (void)hoisted__Bool_3738;
    if (hoisted__Bool_3738) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3707 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3707;
        NodeType *hoisted__NodeType_3708 = NodeType_StructDef(hoisted__StructDef_3707);
        (void)hoisted__NodeType_3708;
        { NodeType * _ret_val = hoisted__NodeType_3708;
                return _ret_val; }
    }
    U32 hoisted__U32_3739 = 1;
    (void)hoisted__U32_3739;
    Bool hoisted__Bool_3740 = is_n(self, &(NodeType){.tag = NodeType_TAG_EnumDef}, hoisted__U32_3739);
    (void)hoisted__Bool_3740;
    if (hoisted__Bool_3740) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3709 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3709;
        NodeType *hoisted__NodeType_3710 = NodeType_EnumDef(hoisted__EnumDef_3709);
        (void)hoisted__NodeType_3710;
        { NodeType * _ret_val = hoisted__NodeType_3710;
                return _ret_val; }
    }
    U32 hoisted__U32_3741 = 1;
    (void)hoisted__U32_3741;
    Bool hoisted__Bool_3742 = is_n(self, &(NodeType){.tag = NodeType_TAG_FieldAccess}, hoisted__U32_3741);
    (void)hoisted__Bool_3742;
    if (hoisted__Bool_3742) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3711 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3711;
        NodeType *hoisted__NodeType_3712 = NodeType_FieldAccess(hoisted__FieldAccessData_3711);
        (void)hoisted__NodeType_3712;
        { NodeType * _ret_val = hoisted__NodeType_3712;
                return _ret_val; }
    }
    U32 hoisted__U32_3743 = 1;
    (void)hoisted__U32_3743;
    Bool hoisted__Bool_3744 = is_n(self, &(NodeType){.tag = NodeType_TAG_FieldAssign}, hoisted__U32_3743);
    (void)hoisted__Bool_3744;
    if (hoisted__Bool_3744) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3713 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3713;
        NodeType *hoisted__NodeType_3714 = NodeType_FieldAssign(hoisted__FieldAssignData_3713);
        (void)hoisted__NodeType_3714;
        { NodeType * _ret_val = hoisted__NodeType_3714;
                return _ret_val; }
    }
    U32 hoisted__U32_3745 = 1;
    (void)hoisted__U32_3745;
    Bool hoisted__Bool_3746 = is_n(self, &(NodeType){.tag = NodeType_TAG_Return}, hoisted__U32_3745);
    (void)hoisted__Bool_3746;
    if (hoisted__Bool_3746) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U32 hoisted__U32_3747 = 1;
    (void)hoisted__U32_3747;
    Bool hoisted__Bool_3748 = is_n(self, &(NodeType){.tag = NodeType_TAG_If}, hoisted__U32_3747);
    (void)hoisted__Bool_3748;
    if (hoisted__Bool_3748) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U32 hoisted__U32_3749 = 1;
    (void)hoisted__U32_3749;
    Bool hoisted__Bool_3750 = is_n(self, &(NodeType){.tag = NodeType_TAG_While}, hoisted__U32_3749);
    (void)hoisted__Bool_3750;
    if (hoisted__Bool_3750) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U32 hoisted__U32_3751 = 1;
    (void)hoisted__U32_3751;
    Bool hoisted__Bool_3752 = is_n(self, &(NodeType){.tag = NodeType_TAG_ForIn}, hoisted__U32_3751);
    (void)hoisted__Bool_3752;
    if (hoisted__Bool_3752) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3715 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3715;
        NodeType *hoisted__NodeType_3716 = NodeType_ForIn(hoisted__ForInData_3715);
        (void)hoisted__NodeType_3716;
        { NodeType * _ret_val = hoisted__NodeType_3716;
                return _ret_val; }
    }
    U32 hoisted__U32_3753 = 1;
    (void)hoisted__U32_3753;
    Bool hoisted__Bool_3754 = is_n(self, &(NodeType){.tag = NodeType_TAG_NamedArg}, hoisted__U32_3753);
    (void)hoisted__Bool_3754;
    if (hoisted__Bool_3754) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3717 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3717;
        NodeType *hoisted__NodeType_3718 = NodeType_NamedArg(hoisted__Str_3717);
        (void)hoisted__NodeType_3718;
        { NodeType * _ret_val = hoisted__NodeType_3718;
                return _ret_val; }
    }
    U32 hoisted__U32_3755 = 1;
    (void)hoisted__U32_3755;
    Bool hoisted__Bool_3756 = is_n(self, &(NodeType){.tag = NodeType_TAG_Break}, hoisted__U32_3755);
    (void)hoisted__Bool_3756;
    if (hoisted__Bool_3756) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U32 hoisted__U32_3757 = 1;
    (void)hoisted__U32_3757;
    Bool hoisted__Bool_3758 = is_n(self, &(NodeType){.tag = NodeType_TAG_Continue}, hoisted__U32_3757);
    (void)hoisted__Bool_3758;
    if (hoisted__Bool_3758) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U32 hoisted__U32_3759 = 1;
    (void)hoisted__U32_3759;
    Bool hoisted__Bool_3760 = is_n(self, &(NodeType){.tag = NodeType_TAG_Switch}, hoisted__U32_3759);
    (void)hoisted__Bool_3760;
    if (hoisted__Bool_3760) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U32 hoisted__U32_3761 = 1;
    (void)hoisted__U32_3761;
    Bool hoisted__Bool_3762 = is_n(self, &(NodeType){.tag = NodeType_TAG_Match}, hoisted__U32_3761);
    (void)hoisted__Bool_3762;
    if (hoisted__Bool_3762) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3719 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3719;
        NodeType *hoisted__NodeType_3720 = NodeType_Match(hoisted__MatchData_3719);
        (void)hoisted__NodeType_3720;
        { NodeType * _ret_val = hoisted__NodeType_3720;
                return _ret_val; }
    }
    U32 hoisted__U32_3763 = 1;
    (void)hoisted__U32_3763;
    Bool hoisted__Bool_3764 = is_n(self, &(NodeType){.tag = NodeType_TAG_Case}, hoisted__U32_3763);
    (void)hoisted__Bool_3764;
    if (hoisted__Bool_3764) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U32 hoisted__U32_3765 = 1;
    (void)hoisted__U32_3765;
    Bool hoisted__Bool_3766 = is_n(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg}, hoisted__U32_3765);
    (void)hoisted__Bool_3766;
    if (hoisted__Bool_3766) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U32 hoisted__U32_3767 = 1;
    (void)hoisted__U32_3767;
    Bool hoisted__Bool_3768 = is_n(self, &(NodeType){.tag = NodeType_TAG_Throw}, hoisted__U32_3767);
    (void)hoisted__Bool_3768;
    if (hoisted__Bool_3768) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U32 hoisted__U32_3769 = 1;
    (void)hoisted__U32_3769;
    Bool hoisted__Bool_3770 = is_n(self, &(NodeType){.tag = NodeType_TAG_Catch}, hoisted__U32_3769);
    (void)hoisted__Bool_3770;
    if (hoisted__Bool_3770) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U32 hoisted__U32_3771 = 1;
    (void)hoisted__U32_3771;
    Bool hoisted__Bool_3772 = is_n(self, &(NodeType){.tag = NodeType_TAG_RestPattern}, hoisted__U32_3771);
    (void)hoisted__Bool_3772;
    if (hoisted__Bool_3772) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U32 hoisted__U32_3773 = 1;
    (void)hoisted__U32_3773;
    Bool hoisted__Bool_3774 = is_n(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock}, hoisted__U32_3773);
    (void)hoisted__Bool_3774;
    if (hoisted__Bool_3774) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3721 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3721;
        NodeType *hoisted__NodeType_3722 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3721);
        (void)hoisted__NodeType_3722;
        { NodeType * _ret_val = hoisted__NodeType_3722;
                return _ret_val; }
    }
    U32 hoisted__U32_3775 = 1;
    (void)hoisted__U32_3775;
    Bool hoisted__Bool_3776 = is_n(self, &(NodeType){.tag = NodeType_TAG_Loc}, hoisted__U32_3775);
    (void)hoisted__Bool_3776;
    if (hoisted__Bool_3776) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    CaptureBlockData *_clone_payload_BodyValue_27 = get_payload(self);
    (void)_clone_payload_BodyValue_27;
    (void)_clone_payload_BodyValue_27;
    CaptureBlockData *hoisted__CaptureBlockData_3777 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
    (void)hoisted__CaptureBlockData_3777;
    NodeType *hoisted__NodeType_3778 = NodeType_BodyValue(hoisted__CaptureBlockData_3777);
    (void)hoisted__NodeType_3778;
    return hoisted__NodeType_3778;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3779 = 136;
    (void)hoisted__U32_3779;
    return hoisted__U32_3779;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3780 = is_null(self);
    (void)hoisted__Bool_3780;
    if (hoisted__Bool_3780) {
        return;
    }
    Bool hoisted__Bool_3781 = 0;
    (void)hoisted__Bool_3781;
    NodeType_delete(&self->node_type, hoisted__Bool_3781);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3831 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3831->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3831->children = *_ca; free(_ca); }
    hoisted__Expr_3831->line = line;
    hoisted__Expr_3831->col = col;
    (void)hoisted__Expr_3831;
    return hoisted__Expr_3831;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3840 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3840->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3840->children = *_ca; free(_ca); }
    hoisted__Expr_3840->line = self->line;
    hoisted__Expr_3840->col = self->col;
    (void)hoisted__Expr_3840;
    return hoisted__Expr_3840;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3841 = 0;
    (void)hoisted__U32_3841;
    U64 hoisted__U64_3842 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3841); });
    (void)hoisted__U64_3842;
    return hoisted__U64_3842;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3843 = 160;
    (void)hoisted__U32_3843;
    return hoisted__U32_3843;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4927 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4927->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4927->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4927;
    return hoisted__Map__I64_Str_4927;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_5040 = 0;
    (void)hoisted__Bool_5040;
    Vec__I64_delete(&self->keys, hoisted__Bool_5040);
    Bool hoisted__Bool_5041 = 0;
    (void)hoisted__Bool_5041;
    Vec__Str_delete(&self->values, hoisted__Bool_5041);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_5042 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_5042->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_5042->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_5042;
    return hoisted__Map__I64_Str_5042;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_5043 = 0;
    (void)hoisted__U32_5043;
    U64 hoisted__U64_5044 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5043); });
    (void)hoisted__U64_5044;
    return hoisted__U64_5044;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_5045 = 32;
    (void)hoisted__U32_5045;
    return hoisted__U32_5045;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_5046 = 1;
    (void)hoisted__U32_5046;
    U64 hoisted__U64_5047 = (U64)(hoisted__U32_5046);
    (void)hoisted__U64_5047;
    void * hoisted__v_5048 = malloc(hoisted__U64_5047);
    (void)hoisted__v_5048;
    U32 hoisted__U32_5049 = 0;
    (void)hoisted__U32_5049;
    I64 hoisted__I64_5050 = 1;
    (void)hoisted__I64_5050;
    Vec__Bool *hoisted__Vec__Bool_5051 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5051->data = hoisted__v_5048;
    hoisted__Vec__Bool_5051->count = hoisted__U32_5049;
    hoisted__Vec__Bool_5051->cap = hoisted__I64_5050;
    (void)hoisted__Vec__Bool_5051;
    return hoisted__Vec__Bool_5051;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_5061 = self->count;
        (void)_re_U32_5061;
        U32 _rc_U32_5061 = 0;
        (void)_rc_U32_5061;
        Bool hoisted__Bool_5074 = ((Bool)(_rc_U32_5061 <= _re_U32_5061));
        (void)hoisted__Bool_5074;
        if (hoisted__Bool_5074) {
            while (1) {
                Bool _wcond_Bool_5062 = ((Bool)(_rc_U32_5061 < _re_U32_5061));
                (void)_wcond_Bool_5062;
                if (_wcond_Bool_5062) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5061);
                U32_inc(&_rc_U32_5061);
                U32 hoisted__U32_5063 = 1;
                (void)hoisted__U32_5063;
                U32 hoisted__U32_5064 = ((U32)(i * hoisted__U32_5063));
                (void)hoisted__U32_5064;
                U64 hoisted__U64_5065 = (U64)(hoisted__U32_5064);
                (void)hoisted__U64_5065;
                Bool *hoisted__Bool_5066 = ptr_add(self->data, hoisted__U64_5065);
                (void)hoisted__Bool_5066;
                (void)hoisted__Bool_5066;
                Bool hoisted__Bool_5067 = 0;
                (void)hoisted__Bool_5067;
                Bool_delete(hoisted__Bool_5066, hoisted__Bool_5067);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5068 = ((Bool)(_rc_U32_5061 > _re_U32_5061));
                (void)_wcond_Bool_5068;
                if (_wcond_Bool_5068) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5061);
                U32_dec(&_rc_U32_5061);
                U32 hoisted__U32_5069 = 1;
                (void)hoisted__U32_5069;
                U32 hoisted__U32_5070 = ((U32)(i * hoisted__U32_5069));
                (void)hoisted__U32_5070;
                U64 hoisted__U64_5071 = (U64)(hoisted__U32_5070);
                (void)hoisted__U64_5071;
                Bool *hoisted__Bool_5072 = ptr_add(self->data, hoisted__U64_5071);
                (void)hoisted__Bool_5072;
                (void)hoisted__Bool_5072;
                Bool hoisted__Bool_5073 = 0;
                (void)hoisted__Bool_5073;
                Bool_delete(hoisted__Bool_5072, hoisted__Bool_5073);
            }
        }
    }
    U32 hoisted__U32_5075 = 0;
    (void)hoisted__U32_5075;
    self->count = hoisted__U32_5075;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_5345 = 1;
    (void)hoisted__U32_5345;
    U32 hoisted__U32_5346 = ((U32)(self->cap * hoisted__U32_5345));
    (void)hoisted__U32_5346;
    U64 hoisted__U64_5347 = (U64)(hoisted__U32_5346);
    (void)hoisted__U64_5347;
    void * new_data = malloc(hoisted__U64_5347);
    {
        U32 _re_U32_5317 = self->count;
        (void)_re_U32_5317;
        U32 _rc_U32_5317 = 0;
        (void)_rc_U32_5317;
        Bool hoisted__Bool_5344 = ((Bool)(_rc_U32_5317 <= _re_U32_5317));
        (void)hoisted__Bool_5344;
        if (hoisted__Bool_5344) {
            while (1) {
                Bool _wcond_Bool_5318 = ((Bool)(_rc_U32_5317 < _re_U32_5317));
                (void)_wcond_Bool_5318;
                if (_wcond_Bool_5318) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5317);
                U32_inc(&_rc_U32_5317);
                U32 hoisted__U32_5319 = 1;
                (void)hoisted__U32_5319;
                U32 hoisted__U32_5320 = ((U32)(i * hoisted__U32_5319));
                (void)hoisted__U32_5320;
                U64 hoisted__U64_5321 = (U64)(hoisted__U32_5320);
                (void)hoisted__U64_5321;
                Bool *src = ptr_add(self->data, hoisted__U64_5321);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_5322 = 1;
                (void)hoisted__U32_5322;
                U32 hoisted__U32_5323 = ((U32)(i * hoisted__U32_5322));
                (void)hoisted__U32_5323;
                U64 hoisted__U64_5324 = (U64)(hoisted__U32_5323);
                (void)hoisted__U64_5324;
                U32 hoisted__U32_5325 = 1;
                (void)hoisted__U32_5325;
                void *hoisted__v_5326 = ptr_add(new_data, hoisted__U64_5324);
                (void)hoisted__v_5326;
                (void)hoisted__v_5326;
                U64 hoisted__U64_5327 = (U64)(hoisted__U32_5325);
                (void)hoisted__U64_5327;
                memcpy(hoisted__v_5326, &cloned, hoisted__U64_5327);
                U32 hoisted__U32_5328 = 1;
                (void)hoisted__U32_5328;
                I32 hoisted__I32_5329 = 0;
                (void)hoisted__I32_5329;
                U64 hoisted__U64_5330 = (U64)(hoisted__U32_5328);
                (void)hoisted__U64_5330;
                memset(&cloned, hoisted__I32_5329, hoisted__U64_5330);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5331 = ((Bool)(_rc_U32_5317 > _re_U32_5317));
                (void)_wcond_Bool_5331;
                if (_wcond_Bool_5331) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5317);
                U32_dec(&_rc_U32_5317);
                U32 hoisted__U32_5332 = 1;
                (void)hoisted__U32_5332;
                U32 hoisted__U32_5333 = ((U32)(i * hoisted__U32_5332));
                (void)hoisted__U32_5333;
                U64 hoisted__U64_5334 = (U64)(hoisted__U32_5333);
                (void)hoisted__U64_5334;
                Bool *src = ptr_add(self->data, hoisted__U64_5334);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_5335 = 1;
                (void)hoisted__U32_5335;
                U32 hoisted__U32_5336 = ((U32)(i * hoisted__U32_5335));
                (void)hoisted__U32_5336;
                U64 hoisted__U64_5337 = (U64)(hoisted__U32_5336);
                (void)hoisted__U64_5337;
                U32 hoisted__U32_5338 = 1;
                (void)hoisted__U32_5338;
                void *hoisted__v_5339 = ptr_add(new_data, hoisted__U64_5337);
                (void)hoisted__v_5339;
                (void)hoisted__v_5339;
                U64 hoisted__U64_5340 = (U64)(hoisted__U32_5338);
                (void)hoisted__U64_5340;
                memcpy(hoisted__v_5339, &cloned, hoisted__U64_5340);
                U32 hoisted__U32_5341 = 1;
                (void)hoisted__U32_5341;
                I32 hoisted__I32_5342 = 0;
                (void)hoisted__I32_5342;
                U64 hoisted__U64_5343 = (U64)(hoisted__U32_5341);
                (void)hoisted__U64_5343;
                memset(&cloned, hoisted__I32_5342, hoisted__U64_5343);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5348 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5348->data = new_data;
    hoisted__Vec__Bool_5348->count = self->count;
    hoisted__Vec__Bool_5348->cap = self->cap;
    (void)hoisted__Vec__Bool_5348;
    return hoisted__Vec__Bool_5348;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_5349 = 16;
    (void)hoisted__U32_5349;
    return hoisted__U32_5349;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5350 = 8;
    (void)hoisted__U32_5350;
    U64 hoisted__U64_5351 = (U64)(hoisted__U32_5350);
    (void)hoisted__U64_5351;
    void * hoisted__v_5352 = malloc(hoisted__U64_5351);
    (void)hoisted__v_5352;
    U32 hoisted__U32_5353 = 0;
    (void)hoisted__U32_5353;
    I64 hoisted__I64_5354 = 1;
    (void)hoisted__I64_5354;
    Vec__I64 *hoisted__Vec__I64_5355 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5355->data = hoisted__v_5352;
    hoisted__Vec__I64_5355->count = hoisted__U32_5353;
    hoisted__Vec__I64_5355->cap = hoisted__I64_5354;
    (void)hoisted__Vec__I64_5355;
    return hoisted__Vec__I64_5355;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5365 = self->count;
        (void)_re_U32_5365;
        U32 _rc_U32_5365 = 0;
        (void)_rc_U32_5365;
        Bool hoisted__Bool_5378 = ((Bool)(_rc_U32_5365 <= _re_U32_5365));
        (void)hoisted__Bool_5378;
        if (hoisted__Bool_5378) {
            while (1) {
                Bool _wcond_Bool_5366 = ((Bool)(_rc_U32_5365 < _re_U32_5365));
                (void)_wcond_Bool_5366;
                if (_wcond_Bool_5366) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5365);
                U32_inc(&_rc_U32_5365);
                U32 hoisted__U32_5367 = 8;
                (void)hoisted__U32_5367;
                U32 hoisted__U32_5368 = ((U32)(i * hoisted__U32_5367));
                (void)hoisted__U32_5368;
                U64 hoisted__U64_5369 = (U64)(hoisted__U32_5368);
                (void)hoisted__U64_5369;
                I64 *hoisted__I64_5370 = ptr_add(self->data, hoisted__U64_5369);
                (void)hoisted__I64_5370;
                (void)hoisted__I64_5370;
                Bool hoisted__Bool_5371 = 0;
                (void)hoisted__Bool_5371;
                I64_delete(hoisted__I64_5370, hoisted__Bool_5371);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5372 = ((Bool)(_rc_U32_5365 > _re_U32_5365));
                (void)_wcond_Bool_5372;
                if (_wcond_Bool_5372) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5365);
                U32_dec(&_rc_U32_5365);
                U32 hoisted__U32_5373 = 8;
                (void)hoisted__U32_5373;
                U32 hoisted__U32_5374 = ((U32)(i * hoisted__U32_5373));
                (void)hoisted__U32_5374;
                U64 hoisted__U64_5375 = (U64)(hoisted__U32_5374);
                (void)hoisted__U64_5375;
                I64 *hoisted__I64_5376 = ptr_add(self->data, hoisted__U64_5375);
                (void)hoisted__I64_5376;
                (void)hoisted__I64_5376;
                Bool hoisted__Bool_5377 = 0;
                (void)hoisted__Bool_5377;
                I64_delete(hoisted__I64_5376, hoisted__Bool_5377);
            }
        }
    }
    U32 hoisted__U32_5379 = 0;
    (void)hoisted__U32_5379;
    self->count = hoisted__U32_5379;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5649 = 8;
    (void)hoisted__U32_5649;
    U32 hoisted__U32_5650 = ((U32)(self->cap * hoisted__U32_5649));
    (void)hoisted__U32_5650;
    U64 hoisted__U64_5651 = (U64)(hoisted__U32_5650);
    (void)hoisted__U64_5651;
    void * new_data = malloc(hoisted__U64_5651);
    {
        U32 _re_U32_5621 = self->count;
        (void)_re_U32_5621;
        U32 _rc_U32_5621 = 0;
        (void)_rc_U32_5621;
        Bool hoisted__Bool_5648 = ((Bool)(_rc_U32_5621 <= _re_U32_5621));
        (void)hoisted__Bool_5648;
        if (hoisted__Bool_5648) {
            while (1) {
                Bool _wcond_Bool_5622 = ((Bool)(_rc_U32_5621 < _re_U32_5621));
                (void)_wcond_Bool_5622;
                if (_wcond_Bool_5622) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5621);
                U32_inc(&_rc_U32_5621);
                U32 hoisted__U32_5623 = 8;
                (void)hoisted__U32_5623;
                U32 hoisted__U32_5624 = ((U32)(i * hoisted__U32_5623));
                (void)hoisted__U32_5624;
                U64 hoisted__U64_5625 = (U64)(hoisted__U32_5624);
                (void)hoisted__U64_5625;
                I64 *src = ptr_add(self->data, hoisted__U64_5625);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5626 = 8;
                (void)hoisted__U32_5626;
                U32 hoisted__U32_5627 = ((U32)(i * hoisted__U32_5626));
                (void)hoisted__U32_5627;
                U64 hoisted__U64_5628 = (U64)(hoisted__U32_5627);
                (void)hoisted__U64_5628;
                U32 hoisted__U32_5629 = 8;
                (void)hoisted__U32_5629;
                void *hoisted__v_5630 = ptr_add(new_data, hoisted__U64_5628);
                (void)hoisted__v_5630;
                (void)hoisted__v_5630;
                U64 hoisted__U64_5631 = (U64)(hoisted__U32_5629);
                (void)hoisted__U64_5631;
                memcpy(hoisted__v_5630, &cloned, hoisted__U64_5631);
                U32 hoisted__U32_5632 = 8;
                (void)hoisted__U32_5632;
                I32 hoisted__I32_5633 = 0;
                (void)hoisted__I32_5633;
                U64 hoisted__U64_5634 = (U64)(hoisted__U32_5632);
                (void)hoisted__U64_5634;
                memset(&cloned, hoisted__I32_5633, hoisted__U64_5634);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5635 = ((Bool)(_rc_U32_5621 > _re_U32_5621));
                (void)_wcond_Bool_5635;
                if (_wcond_Bool_5635) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5621);
                U32_dec(&_rc_U32_5621);
                U32 hoisted__U32_5636 = 8;
                (void)hoisted__U32_5636;
                U32 hoisted__U32_5637 = ((U32)(i * hoisted__U32_5636));
                (void)hoisted__U32_5637;
                U64 hoisted__U64_5638 = (U64)(hoisted__U32_5637);
                (void)hoisted__U64_5638;
                I64 *src = ptr_add(self->data, hoisted__U64_5638);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5639 = 8;
                (void)hoisted__U32_5639;
                U32 hoisted__U32_5640 = ((U32)(i * hoisted__U32_5639));
                (void)hoisted__U32_5640;
                U64 hoisted__U64_5641 = (U64)(hoisted__U32_5640);
                (void)hoisted__U64_5641;
                U32 hoisted__U32_5642 = 8;
                (void)hoisted__U32_5642;
                void *hoisted__v_5643 = ptr_add(new_data, hoisted__U64_5641);
                (void)hoisted__v_5643;
                (void)hoisted__v_5643;
                U64 hoisted__U64_5644 = (U64)(hoisted__U32_5642);
                (void)hoisted__U64_5644;
                memcpy(hoisted__v_5643, &cloned, hoisted__U64_5644);
                U32 hoisted__U32_5645 = 8;
                (void)hoisted__U32_5645;
                I32 hoisted__I32_5646 = 0;
                (void)hoisted__I32_5646;
                U64 hoisted__U64_5647 = (U64)(hoisted__U32_5645);
                (void)hoisted__U64_5647;
                memset(&cloned, hoisted__I32_5646, hoisted__U64_5647);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5652 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5652->data = new_data;
    hoisted__Vec__I64_5652->count = self->count;
    hoisted__Vec__I64_5652->cap = self->cap;
    (void)hoisted__Vec__I64_5652;
    return hoisted__Vec__I64_5652;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5653 = 16;
    (void)hoisted__U32_5653;
    return hoisted__U32_5653;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5958 = 104;
    (void)hoisted__U32_5958;
    U64 hoisted__U64_5959 = (U64)(hoisted__U32_5958);
    (void)hoisted__U64_5959;
    void * hoisted__v_5960 = malloc(hoisted__U64_5959);
    (void)hoisted__v_5960;
    U32 hoisted__U32_5961 = 0;
    (void)hoisted__U32_5961;
    I64 hoisted__I64_5962 = 1;
    (void)hoisted__I64_5962;
    Vec__Declaration *hoisted__Vec__Declaration_5963 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5963->data = hoisted__v_5960;
    hoisted__Vec__Declaration_5963->count = hoisted__U32_5961;
    hoisted__Vec__Declaration_5963->cap = hoisted__I64_5962;
    (void)hoisted__Vec__Declaration_5963;
    return hoisted__Vec__Declaration_5963;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5973 = self->count;
        (void)_re_U32_5973;
        U32 _rc_U32_5973 = 0;
        (void)_rc_U32_5973;
        Bool hoisted__Bool_5986 = ((Bool)(_rc_U32_5973 <= _re_U32_5973));
        (void)hoisted__Bool_5986;
        if (hoisted__Bool_5986) {
            while (1) {
                Bool _wcond_Bool_5974 = ((Bool)(_rc_U32_5973 < _re_U32_5973));
                (void)_wcond_Bool_5974;
                if (_wcond_Bool_5974) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5973);
                U32_inc(&_rc_U32_5973);
                U32 hoisted__U32_5975 = 104;
                (void)hoisted__U32_5975;
                U32 hoisted__U32_5976 = ((U32)(i * hoisted__U32_5975));
                (void)hoisted__U32_5976;
                U64 hoisted__U64_5977 = (U64)(hoisted__U32_5976);
                (void)hoisted__U64_5977;
                Declaration *hoisted__Declaration_5978 = ptr_add(self->data, hoisted__U64_5977);
                (void)hoisted__Declaration_5978;
                (void)hoisted__Declaration_5978;
                Bool hoisted__Bool_5979 = 0;
                (void)hoisted__Bool_5979;
                Declaration_delete(hoisted__Declaration_5978, hoisted__Bool_5979);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5980 = ((Bool)(_rc_U32_5973 > _re_U32_5973));
                (void)_wcond_Bool_5980;
                if (_wcond_Bool_5980) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5973);
                U32_dec(&_rc_U32_5973);
                U32 hoisted__U32_5981 = 104;
                (void)hoisted__U32_5981;
                U32 hoisted__U32_5982 = ((U32)(i * hoisted__U32_5981));
                (void)hoisted__U32_5982;
                U64 hoisted__U64_5983 = (U64)(hoisted__U32_5982);
                (void)hoisted__U64_5983;
                Declaration *hoisted__Declaration_5984 = ptr_add(self->data, hoisted__U64_5983);
                (void)hoisted__Declaration_5984;
                (void)hoisted__Declaration_5984;
                Bool hoisted__Bool_5985 = 0;
                (void)hoisted__Bool_5985;
                Declaration_delete(hoisted__Declaration_5984, hoisted__Bool_5985);
            }
        }
    }
    U32 hoisted__U32_5987 = 0;
    (void)hoisted__U32_5987;
    self->count = hoisted__U32_5987;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_6257 = 104;
    (void)hoisted__U32_6257;
    U32 hoisted__U32_6258 = ((U32)(self->cap * hoisted__U32_6257));
    (void)hoisted__U32_6258;
    U64 hoisted__U64_6259 = (U64)(hoisted__U32_6258);
    (void)hoisted__U64_6259;
    void * new_data = malloc(hoisted__U64_6259);
    {
        U32 _re_U32_6229 = self->count;
        (void)_re_U32_6229;
        U32 _rc_U32_6229 = 0;
        (void)_rc_U32_6229;
        Bool hoisted__Bool_6256 = ((Bool)(_rc_U32_6229 <= _re_U32_6229));
        (void)hoisted__Bool_6256;
        if (hoisted__Bool_6256) {
            while (1) {
                Bool _wcond_Bool_6230 = ((Bool)(_rc_U32_6229 < _re_U32_6229));
                (void)_wcond_Bool_6230;
                if (_wcond_Bool_6230) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6229);
                U32_inc(&_rc_U32_6229);
                U32 hoisted__U32_6231 = 104;
                (void)hoisted__U32_6231;
                U32 hoisted__U32_6232 = ((U32)(i * hoisted__U32_6231));
                (void)hoisted__U32_6232;
                U64 hoisted__U64_6233 = (U64)(hoisted__U32_6232);
                (void)hoisted__U64_6233;
                Declaration *src = ptr_add(self->data, hoisted__U64_6233);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6234 = 104;
                (void)hoisted__U32_6234;
                U32 hoisted__U32_6235 = ((U32)(i * hoisted__U32_6234));
                (void)hoisted__U32_6235;
                U64 hoisted__U64_6236 = (U64)(hoisted__U32_6235);
                (void)hoisted__U64_6236;
                U32 hoisted__U32_6237 = 104;
                (void)hoisted__U32_6237;
                void *hoisted__v_6238 = ptr_add(new_data, hoisted__U64_6236);
                (void)hoisted__v_6238;
                (void)hoisted__v_6238;
                U64 hoisted__U64_6239 = (U64)(hoisted__U32_6237);
                (void)hoisted__U64_6239;
                memcpy(hoisted__v_6238, cloned, hoisted__U64_6239);
                U32 hoisted__U32_6240 = 104;
                (void)hoisted__U32_6240;
                I32 hoisted__I32_6241 = 0;
                (void)hoisted__I32_6241;
                U64 hoisted__U64_6242 = (U64)(hoisted__U32_6240);
                (void)hoisted__U64_6242;
                memset(cloned, hoisted__I32_6241, hoisted__U64_6242);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6243 = ((Bool)(_rc_U32_6229 > _re_U32_6229));
                (void)_wcond_Bool_6243;
                if (_wcond_Bool_6243) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6229);
                U32_dec(&_rc_U32_6229);
                U32 hoisted__U32_6244 = 104;
                (void)hoisted__U32_6244;
                U32 hoisted__U32_6245 = ((U32)(i * hoisted__U32_6244));
                (void)hoisted__U32_6245;
                U64 hoisted__U64_6246 = (U64)(hoisted__U32_6245);
                (void)hoisted__U64_6246;
                Declaration *src = ptr_add(self->data, hoisted__U64_6246);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6247 = 104;
                (void)hoisted__U32_6247;
                U32 hoisted__U32_6248 = ((U32)(i * hoisted__U32_6247));
                (void)hoisted__U32_6248;
                U64 hoisted__U64_6249 = (U64)(hoisted__U32_6248);
                (void)hoisted__U64_6249;
                U32 hoisted__U32_6250 = 104;
                (void)hoisted__U32_6250;
                void *hoisted__v_6251 = ptr_add(new_data, hoisted__U64_6249);
                (void)hoisted__v_6251;
                (void)hoisted__v_6251;
                U64 hoisted__U64_6252 = (U64)(hoisted__U32_6250);
                (void)hoisted__U64_6252;
                memcpy(hoisted__v_6251, cloned, hoisted__U64_6252);
                U32 hoisted__U32_6253 = 104;
                (void)hoisted__U32_6253;
                I32 hoisted__I32_6254 = 0;
                (void)hoisted__I32_6254;
                U64 hoisted__U64_6255 = (U64)(hoisted__U32_6253);
                (void)hoisted__U64_6255;
                memset(cloned, hoisted__I32_6254, hoisted__U64_6255);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_6260 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6260->data = new_data;
    hoisted__Vec__Declaration_6260->count = self->count;
    hoisted__Vec__Declaration_6260->cap = self->cap;
    (void)hoisted__Vec__Declaration_6260;
    return hoisted__Vec__Declaration_6260;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_6261 = 16;
    (void)hoisted__U32_6261;
    return hoisted__U32_6261;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_6262 = 160;
    (void)hoisted__U32_6262;
    U64 hoisted__U64_6263 = (U64)(hoisted__U32_6262);
    (void)hoisted__U64_6263;
    void * hoisted__v_6264 = malloc(hoisted__U64_6263);
    (void)hoisted__v_6264;
    U32 hoisted__U32_6265 = 0;
    (void)hoisted__U32_6265;
    I64 hoisted__I64_6266 = 1;
    (void)hoisted__I64_6266;
    Vec__Expr *hoisted__Vec__Expr_6267 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6267->data = hoisted__v_6264;
    hoisted__Vec__Expr_6267->count = hoisted__U32_6265;
    hoisted__Vec__Expr_6267->cap = hoisted__I64_6266;
    (void)hoisted__Vec__Expr_6267;
    return hoisted__Vec__Expr_6267;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_6277 = self->count;
        (void)_re_U32_6277;
        U32 _rc_U32_6277 = 0;
        (void)_rc_U32_6277;
        Bool hoisted__Bool_6290 = ((Bool)(_rc_U32_6277 <= _re_U32_6277));
        (void)hoisted__Bool_6290;
        if (hoisted__Bool_6290) {
            while (1) {
                Bool _wcond_Bool_6278 = ((Bool)(_rc_U32_6277 < _re_U32_6277));
                (void)_wcond_Bool_6278;
                if (_wcond_Bool_6278) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6277);
                U32_inc(&_rc_U32_6277);
                U32 hoisted__U32_6279 = 160;
                (void)hoisted__U32_6279;
                U32 hoisted__U32_6280 = ((U32)(i * hoisted__U32_6279));
                (void)hoisted__U32_6280;
                U64 hoisted__U64_6281 = (U64)(hoisted__U32_6280);
                (void)hoisted__U64_6281;
                Expr *hoisted__Expr_6282 = ptr_add(self->data, hoisted__U64_6281);
                (void)hoisted__Expr_6282;
                (void)hoisted__Expr_6282;
                Bool hoisted__Bool_6283 = 0;
                (void)hoisted__Bool_6283;
                Expr_delete(hoisted__Expr_6282, hoisted__Bool_6283);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6284 = ((Bool)(_rc_U32_6277 > _re_U32_6277));
                (void)_wcond_Bool_6284;
                if (_wcond_Bool_6284) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6277);
                U32_dec(&_rc_U32_6277);
                U32 hoisted__U32_6285 = 160;
                (void)hoisted__U32_6285;
                U32 hoisted__U32_6286 = ((U32)(i * hoisted__U32_6285));
                (void)hoisted__U32_6286;
                U64 hoisted__U64_6287 = (U64)(hoisted__U32_6286);
                (void)hoisted__U64_6287;
                Expr *hoisted__Expr_6288 = ptr_add(self->data, hoisted__U64_6287);
                (void)hoisted__Expr_6288;
                (void)hoisted__Expr_6288;
                Bool hoisted__Bool_6289 = 0;
                (void)hoisted__Bool_6289;
                Expr_delete(hoisted__Expr_6288, hoisted__Bool_6289);
            }
        }
    }
    U32 hoisted__U32_6291 = 0;
    (void)hoisted__U32_6291;
    self->count = hoisted__U32_6291;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_6561 = 160;
    (void)hoisted__U32_6561;
    U32 hoisted__U32_6562 = ((U32)(self->cap * hoisted__U32_6561));
    (void)hoisted__U32_6562;
    U64 hoisted__U64_6563 = (U64)(hoisted__U32_6562);
    (void)hoisted__U64_6563;
    void * new_data = malloc(hoisted__U64_6563);
    {
        U32 _re_U32_6533 = self->count;
        (void)_re_U32_6533;
        U32 _rc_U32_6533 = 0;
        (void)_rc_U32_6533;
        Bool hoisted__Bool_6560 = ((Bool)(_rc_U32_6533 <= _re_U32_6533));
        (void)hoisted__Bool_6560;
        if (hoisted__Bool_6560) {
            while (1) {
                Bool _wcond_Bool_6534 = ((Bool)(_rc_U32_6533 < _re_U32_6533));
                (void)_wcond_Bool_6534;
                if (_wcond_Bool_6534) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6533);
                U32_inc(&_rc_U32_6533);
                U32 hoisted__U32_6535 = 160;
                (void)hoisted__U32_6535;
                U32 hoisted__U32_6536 = ((U32)(i * hoisted__U32_6535));
                (void)hoisted__U32_6536;
                U64 hoisted__U64_6537 = (U64)(hoisted__U32_6536);
                (void)hoisted__U64_6537;
                Expr *src = ptr_add(self->data, hoisted__U64_6537);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6538 = 160;
                (void)hoisted__U32_6538;
                U32 hoisted__U32_6539 = ((U32)(i * hoisted__U32_6538));
                (void)hoisted__U32_6539;
                U64 hoisted__U64_6540 = (U64)(hoisted__U32_6539);
                (void)hoisted__U64_6540;
                U32 hoisted__U32_6541 = 160;
                (void)hoisted__U32_6541;
                void *hoisted__v_6542 = ptr_add(new_data, hoisted__U64_6540);
                (void)hoisted__v_6542;
                (void)hoisted__v_6542;
                U64 hoisted__U64_6543 = (U64)(hoisted__U32_6541);
                (void)hoisted__U64_6543;
                memcpy(hoisted__v_6542, cloned, hoisted__U64_6543);
                U32 hoisted__U32_6544 = 160;
                (void)hoisted__U32_6544;
                I32 hoisted__I32_6545 = 0;
                (void)hoisted__I32_6545;
                U64 hoisted__U64_6546 = (U64)(hoisted__U32_6544);
                (void)hoisted__U64_6546;
                memset(cloned, hoisted__I32_6545, hoisted__U64_6546);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6547 = ((Bool)(_rc_U32_6533 > _re_U32_6533));
                (void)_wcond_Bool_6547;
                if (_wcond_Bool_6547) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6533);
                U32_dec(&_rc_U32_6533);
                U32 hoisted__U32_6548 = 160;
                (void)hoisted__U32_6548;
                U32 hoisted__U32_6549 = ((U32)(i * hoisted__U32_6548));
                (void)hoisted__U32_6549;
                U64 hoisted__U64_6550 = (U64)(hoisted__U32_6549);
                (void)hoisted__U64_6550;
                Expr *src = ptr_add(self->data, hoisted__U64_6550);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6551 = 160;
                (void)hoisted__U32_6551;
                U32 hoisted__U32_6552 = ((U32)(i * hoisted__U32_6551));
                (void)hoisted__U32_6552;
                U64 hoisted__U64_6553 = (U64)(hoisted__U32_6552);
                (void)hoisted__U64_6553;
                U32 hoisted__U32_6554 = 160;
                (void)hoisted__U32_6554;
                void *hoisted__v_6555 = ptr_add(new_data, hoisted__U64_6553);
                (void)hoisted__v_6555;
                (void)hoisted__v_6555;
                U64 hoisted__U64_6556 = (U64)(hoisted__U32_6554);
                (void)hoisted__U64_6556;
                memcpy(hoisted__v_6555, cloned, hoisted__U64_6556);
                U32 hoisted__U32_6557 = 160;
                (void)hoisted__U32_6557;
                I32 hoisted__I32_6558 = 0;
                (void)hoisted__I32_6558;
                U64 hoisted__U64_6559 = (U64)(hoisted__U32_6557);
                (void)hoisted__U64_6559;
                memset(cloned, hoisted__I32_6558, hoisted__U64_6559);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6564 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6564->data = new_data;
    hoisted__Vec__Expr_6564->count = self->count;
    hoisted__Vec__Expr_6564->cap = self->cap;
    (void)hoisted__Vec__Expr_6564;
    return hoisted__Vec__Expr_6564;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_6565 = 16;
    (void)hoisted__U32_6565;
    return hoisted__U32_6565;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7653 = 3;
    (void)hoisted__U32_7653;
    Array__Str *_va_Array_207 = Array__Str_new(hoisted__U32_7653);
    (void)_va_Array_207;
    I64 _va_Array_207_ek = 0;
    (void)_va_Array_207_ek;
    OutOfBounds *_va_Array_207_eo = malloc(sizeof(OutOfBounds));
    _va_Array_207_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_207_eo;
    U32 hoisted__U32_7654 = 0;
    (void)hoisted__U32_7654;
    Str *hoisted__Str_7655 = Str_clone(loc);
    (void)hoisted__Str_7655;
    (void)_til_str_lit_143;
    (void)_til_str_lit_143;
    Array__Str_set(_va_Array_207, hoisted__U32_7654, hoisted__Str_7655, &_va_Array_207_ek, _va_Array_207_eo, &_til_str_lit_143);
    Str_delete(&_til_str_lit_143, (Bool){0});
    U32 hoisted__U32_7657 = 1;
    (void)hoisted__U32_7657;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    (void)_til_str_lit_143;
    (void)_til_str_lit_143;
    Array__Str_set(_va_Array_207, hoisted__U32_7657, &_til_str_lit_144, &_va_Array_207_ek, _va_Array_207_eo, &_til_str_lit_143);
    Str_delete(&_til_str_lit_143, (Bool){0});
    Array__Str *hoisted__Array__Str_7660 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7660;
    U32 hoisted__U32_7661 = 2;
    (void)hoisted__U32_7661;
    Str *hoisted__Str_7662 = format(hoisted__Array__Str_7660);
    (void)hoisted__Str_7662;
    (void)_til_str_lit_143;
    (void)_til_str_lit_143;
    Array__Str_set(_va_Array_207, hoisted__U32_7661, hoisted__Str_7662, &_va_Array_207_ek, _va_Array_207_eo, &_til_str_lit_143);
    OutOfBounds_delete(_va_Array_207_eo, 1);
    Str_delete(&_til_str_lit_143, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_207);
    I64 hoisted__I64_7664 = 1;
    (void)hoisted__I64_7664;
    exit(hoisted__I64_7664);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7673 = 1;
    (void)hoisted__U32_7673;
    Array__Str *_va_Array_209 = Array__Str_new(hoisted__U32_7673);
    (void)_va_Array_209;
    I64 _va_Array_209_ek = 0;
    (void)_va_Array_209_ek;
    OutOfBounds *_va_Array_209_eo = malloc(sizeof(OutOfBounds));
    _va_Array_209_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_209_eo;
    U32 hoisted__U32_7674 = 0;
    (void)hoisted__U32_7674;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    (void)_til_str_lit_146;
    (void)_til_str_lit_146;
    Array__Str_set(_va_Array_209, hoisted__U32_7674, &_til_str_lit_145, &_va_Array_209_ek, _va_Array_209_eo, &_til_str_lit_146);
    OutOfBounds_delete(_va_Array_209_eo, 1);
    Str_delete(&_til_str_lit_146, (Bool){0});
    panic(_va_Array_209, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7681 = not(cond);
    (void)hoisted__Bool_7681;
    if (hoisted__Bool_7681) {
        U32 hoisted__U32_7677 = 1;
        (void)hoisted__U32_7677;
        Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7677);
        (void)_va_Array_210;
        I64 _va_Array_210_ek = 0;
        (void)_va_Array_210_ek;
        OutOfBounds *_va_Array_210_eo = malloc(sizeof(OutOfBounds));
        _va_Array_210_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_210_eo;
        U32 hoisted__U32_7678 = 0;
        (void)hoisted__U32_7678;
        (void)_til_str_lit_147;
        (void)_til_str_lit_147;
        (void)_til_str_lit_148;
        (void)_til_str_lit_148;
        Array__Str_set(_va_Array_210, hoisted__U32_7678, &_til_str_lit_147, &_va_Array_210_ek, _va_Array_210_eo, &_til_str_lit_148);
        OutOfBounds_delete(_va_Array_210_eo, 1);
        Str_delete(&_til_str_lit_148, (Bool){0});
        panic(_va_Array_210, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7691 = parts;
        (void)_fc_Array__Str_7691;
        (void)_fc_Array__Str_7691;
        U32 _fi_USize_7691 = 0;
        (void)_fi_USize_7691;
        while (1) {
            U32 hoisted__U32_7693 = Array__Str_len(_fc_Array__Str_7691);
            (void)hoisted__U32_7693;
            Bool _wcond_Bool_7692 = ((Bool)(_fi_USize_7691 < hoisted__U32_7693));
            (void)_wcond_Bool_7692;
            if (_wcond_Bool_7692) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7691, &_fi_USize_7691);
            U32 hoisted__U32_7694 = 1;
            (void)hoisted__U32_7694;
            U32 hoisted__U32_7695 = ((U32)(_fi_USize_7691 + hoisted__U32_7694));
            (void)hoisted__U32_7695;
            _fi_USize_7691 = hoisted__U32_7695;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7729 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7729;
    return hoisted__Bool_7729;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7738 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7738;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7738;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7739 = 0;
    (void)hoisted__U32_7739;
    U64 hoisted__U64_7740 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7739); });
    (void)hoisted__U64_7740;
    return hoisted__U64_7740;
}

U32 Range_size(void) {
    U32 hoisted__U32_7771 = 16;
    (void)hoisted__U32_7771;
    return hoisted__U32_7771;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7787 = 3;
    (void)hoisted__I64_7787;
    (void)_til_str_lit_151;
    (void)_til_str_lit_151;
    assert_eq__I64(result, hoisted__I64_7787, &_til_str_lit_151);
    Str_delete(&_til_str_lit_151, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7795 = 15;
    (void)hoisted__I64_7795;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    assert_eq__I64(result, hoisted__I64_7795, &_til_str_lit_152);
    Str_delete(&_til_str_lit_152, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7803 = 26;
    (void)hoisted__I64_7803;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    assert_eq__I64(result, hoisted__I64_7803, &_til_str_lit_153);
    Str_delete(&_til_str_lit_153, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    assert_eq__Str(&result, &_til_str_lit_154, &_til_str_lit_155);
    Str_delete(&_til_str_lit_154, (Bool){0});
    Str_delete(&_til_str_lit_155, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    assert_eq__Str(&r, &_til_str_lit_154, &_til_str_lit_156);
    Str_delete(&_til_str_lit_154, (Bool){0});
    Str_delete(&_til_str_lit_156, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_157;
    (void)_til_str_lit_157;
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    assert_eq__Str(&r2, &_til_str_lit_157, &_til_str_lit_158);
    Str_delete(&_til_str_lit_157, (Bool){0});
    Str_delete(&_til_str_lit_158, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    assert_eq__Str(&d, &_til_str_lit_159, &_til_str_lit_160);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&_til_str_lit_160, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    assert_eq__Str(&d2, &_til_str_lit_161, &_til_str_lit_162);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_161, (Bool){0});
    Str_delete(&_til_str_lit_162, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7890 = 106;
    (void)hoisted__I64_7890;
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    assert_eq__I64(d3, hoisted__I64_7890, &_til_str_lit_163);
    Str_delete(&_til_str_lit_163, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_166;
    (void)_til_str_lit_166;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_166);
    Str_delete(&_til_str_lit_166, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_167;
    (void)_til_str_lit_167;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_167);
    Str_delete(&_til_str_lit_167, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8493 = 8;
    (void)hoisted__I64_8493;
    (void)_til_str_lit_168;
    (void)_til_str_lit_168;
    assert_eq__I64(result, hoisted__I64_8493, &_til_str_lit_168);
    Str_delete(&_til_str_lit_168, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8497 = 1;
    (void)hoisted__Bool_8497;
    (void)_til_str_lit_169;
    (void)_til_str_lit_169;
    assert(hoisted__Bool_8497, &_til_str_lit_169);
    Str_delete(&_til_str_lit_169, (Bool){0});
    Bool hoisted__Bool_8501 = 1;
    (void)hoisted__Bool_8501;
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert(hoisted__Bool_8501, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    assert_eq__Str(&_til_str_lit_171, &_til_str_lit_171, &_til_str_lit_172);
    Str_delete(&_til_str_lit_171, (Bool){0});
    Str_delete(&_til_str_lit_171, (Bool){0});
    Str_delete(&_til_str_lit_172, (Bool){0});
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    assert_eq__Str(&_til_str_lit_173, &_til_str_lit_173, &_til_str_lit_174);
    Str_delete(&_til_str_lit_173, (Bool){0});
    Str_delete(&_til_str_lit_173, (Bool){0});
    Str_delete(&_til_str_lit_174, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8519 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8519;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8519;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8520 = 0;
    (void)hoisted__U32_8520;
    U64 hoisted__U64_8521 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8520); });
    (void)hoisted__U64_8521;
    return hoisted__U64_8521;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8552 = 16;
    (void)hoisted__U32_8552;
    return hoisted__U32_8552;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8553 = 42;
    (void)hoisted__I64_8553;
    (void)_til_str_lit_177;
    (void)_til_str_lit_177;
    assert_eq__I64(v.x, hoisted__I64_8553, &_til_str_lit_177);
    Str_delete(&_til_str_lit_177, (Bool){0});
    I64 hoisted__I64_8555 = 99;
    (void)hoisted__I64_8555;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    assert_eq__I64(v.y, hoisted__I64_8555, &_til_str_lit_178);
    Str_delete(&_til_str_lit_178, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8559 = 10;
    (void)hoisted__I64_8559;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__I64(p.x, hoisted__I64_8559, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
    I64 hoisted__I64_8561 = 20;
    (void)hoisted__I64_8561;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    assert_eq__I64(p.y, hoisted__I64_8561, &_til_str_lit_180);
    Str_delete(&_til_str_lit_180, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8568 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8568;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8568;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8569 = 0;
    (void)hoisted__U32_8569;
    U64 hoisted__U64_8570 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8569); });
    (void)hoisted__U64_8570;
    return hoisted__U64_8570;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8601 = 32;
    (void)hoisted__U32_8601;
    return hoisted__U32_8601;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8602 = 5;
    (void)hoisted__I64_8602;
    (void)_til_str_lit_184;
    (void)_til_str_lit_184;
    assert_eq__I64(r.top_left.x, hoisted__I64_8602, &_til_str_lit_184);
    Str_delete(&_til_str_lit_184, (Bool){0});
    I64 hoisted__I64_8604 = 10;
    (void)hoisted__I64_8604;
    (void)_til_str_lit_185;
    (void)_til_str_lit_185;
    assert_eq__I64(r.top_left.y, hoisted__I64_8604, &_til_str_lit_185);
    Str_delete(&_til_str_lit_185, (Bool){0});
    I64 hoisted__I64_8606 = 100;
    (void)hoisted__I64_8606;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8606, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_8608 = 200;
    (void)hoisted__I64_8608;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8608, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8611 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8611;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8611;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8612 = 0;
    (void)hoisted__U32_8612;
    U64 hoisted__U64_8613 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8612); });
    (void)hoisted__U64_8613;
    return hoisted__U64_8613;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8656 = 12;
    (void)hoisted__U32_8656;
    return hoisted__U32_8656;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8660 = F32_to_str(v.x);
    (void)hoisted__Str_8660;
    (void)_til_str_lit_189;
    (void)_til_str_lit_189;
    (void)_til_str_lit_190;
    (void)_til_str_lit_190;
    assert_eq__Str(hoisted__Str_8660, &_til_str_lit_189, &_til_str_lit_190);
    Str_delete(hoisted__Str_8660, 1);
    Str_delete(&_til_str_lit_189, (Bool){0});
    Str_delete(&_til_str_lit_190, (Bool){0});
    Str *hoisted__Str_8663 = F32_to_str(v.y);
    (void)hoisted__Str_8663;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    assert_eq__Str(hoisted__Str_8663, &_til_str_lit_191, &_til_str_lit_192);
    Str_delete(hoisted__Str_8663, 1);
    Str_delete(&_til_str_lit_191, (Bool){0});
    Str_delete(&_til_str_lit_192, (Bool){0});
    Str *hoisted__Str_8666 = F32_to_str(v.z);
    (void)hoisted__Str_8666;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    assert_eq__Str(hoisted__Str_8666, &_til_str_lit_193, &_til_str_lit_194);
    Str_delete(hoisted__Str_8666, 1);
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str_delete(&_til_str_lit_194, (Bool){0});
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
    U32 hoisted__U32_8677 = 1;
    (void)hoisted__U32_8677;
    Bool hoisted__Bool_8678 = is_n(self, &(Color){.tag = Color_TAG_Red}, hoisted__U32_8677);
    (void)hoisted__Bool_8678;
    if (hoisted__Bool_8678) {
        U32 hoisted__U32_8671 = 1;
        (void)hoisted__U32_8671;
        Bool hoisted__Bool_8672 = is_n(other, &(Color){.tag = Color_TAG_Red}, hoisted__U32_8671);
        (void)hoisted__Bool_8672;
        { Bool _ret_val = hoisted__Bool_8672;
                return _ret_val; }
    }
    U32 hoisted__U32_8679 = 1;
    (void)hoisted__U32_8679;
    Bool hoisted__Bool_8680 = is_n(self, &(Color){.tag = Color_TAG_Green}, hoisted__U32_8679);
    (void)hoisted__Bool_8680;
    if (hoisted__Bool_8680) {
        U32 hoisted__U32_8673 = 1;
        (void)hoisted__U32_8673;
        Bool hoisted__Bool_8674 = is_n(other, &(Color){.tag = Color_TAG_Green}, hoisted__U32_8673);
        (void)hoisted__Bool_8674;
        { Bool _ret_val = hoisted__Bool_8674;
                return _ret_val; }
    }
    U32 hoisted__U32_8681 = 1;
    (void)hoisted__U32_8681;
    Bool hoisted__Bool_8682 = is_n(self, &(Color){.tag = Color_TAG_Blue}, hoisted__U32_8681);
    (void)hoisted__Bool_8682;
    if (hoisted__Bool_8682) {
        U32 hoisted__U32_8675 = 1;
        (void)hoisted__U32_8675;
        Bool hoisted__Bool_8676 = is_n(other, &(Color){.tag = Color_TAG_Blue}, hoisted__U32_8675);
        (void)hoisted__Bool_8676;
        { Bool _ret_val = hoisted__Bool_8676;
                return _ret_val; }
    }
    Bool hoisted__Bool_8683 = 0;
    (void)hoisted__Bool_8683;
    return hoisted__Bool_8683;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8691 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8691;
    if (hoisted__Bool_8691) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8692 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8692;
    if (hoisted__Bool_8692) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8693 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8693;
    if (hoisted__Bool_8693) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8694 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8694;
    UNREACHABLE(&hoisted__Str_8694);
    Str_delete(&hoisted__Str_8694, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8695 = 1;
    (void)hoisted__U32_8695;
    return hoisted__U32_8695;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8696 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8696;
    (void)_til_str_lit_198;
    (void)_til_str_lit_198;
    assert(hoisted__Bool_8696, &_til_str_lit_198);
    Str_delete(&_til_str_lit_198, (Bool){0});
    Bool hoisted__Bool_8698 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8698;
    Bool hoisted__Bool_8699 = not(hoisted__Bool_8698);
    (void)hoisted__Bool_8699;
    (void)_til_str_lit_199;
    (void)_til_str_lit_199;
    assert(hoisted__Bool_8699, &_til_str_lit_199);
    Str_delete(&_til_str_lit_199, (Bool){0});
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
    U32 hoisted__U32_8701 = 1;
    (void)hoisted__U32_8701;
    Bool hoisted__Bool_8702 = is_n(self, other, hoisted__U32_8701);
    (void)hoisted__Bool_8702;
    return hoisted__Bool_8702;
}

void Token_delete(Token * self, Bool call_free) {
    U32 hoisted__U32_8726 = 1;
    (void)hoisted__U32_8726;
    Bool hoisted__Bool_8727 = is_n(self, &(Token){.tag = Token_TAG_Num}, hoisted__U32_8726);
    (void)hoisted__Bool_8727;
    if (hoisted__Bool_8727) {
        I64 *hoisted__I64_8722 = get_payload(self);
        (void)hoisted__I64_8722;
        (void)hoisted__I64_8722;
        Bool hoisted__Bool_8723 = 0;
        (void)hoisted__Bool_8723;
        I64_delete(hoisted__I64_8722, hoisted__Bool_8723);
    }
    U32 hoisted__U32_8728 = 1;
    (void)hoisted__U32_8728;
    Bool hoisted__Bool_8729 = is_n(self, &(Token){.tag = Token_TAG_Name}, hoisted__U32_8728);
    (void)hoisted__Bool_8729;
    if (hoisted__Bool_8729) {
        Str *hoisted__Str_8724 = get_payload(self);
        (void)hoisted__Str_8724;
        (void)hoisted__Str_8724;
        Bool hoisted__Bool_8725 = 0;
        (void)hoisted__Bool_8725;
        Str_delete(hoisted__Str_8724, hoisted__Bool_8725);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_8763 = 1;
    (void)hoisted__U32_8763;
    Bool hoisted__Bool_8764 = is_n(self, &(Token){.tag = Token_TAG_Num}, hoisted__U32_8763);
    (void)hoisted__Bool_8764;
    if (hoisted__Bool_8764) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8760 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8760;
        { Token * _ret_val = hoisted__Token_8760;
                return _ret_val; }
    }
    U32 hoisted__U32_8765 = 1;
    (void)hoisted__U32_8765;
    Bool hoisted__Bool_8766 = is_n(self, &(Token){.tag = Token_TAG_Name}, hoisted__U32_8765);
    (void)hoisted__Bool_8766;
    if (hoisted__Bool_8766) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8761 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8761;
        Token *hoisted__Token_8762 = Token_Name(hoisted__Str_8761);
        (void)hoisted__Token_8762;
        { Token * _ret_val = hoisted__Token_8762;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8767 = 24;
    (void)hoisted__U32_8767;
    return hoisted__U32_8767;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8769 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8769;
    (void)_til_str_lit_202;
    (void)_til_str_lit_202;
    assert(hoisted__Bool_8769, &_til_str_lit_202);
    Str_delete(&_til_str_lit_202, (Bool){0});
    Bool hoisted__Bool_8771 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8771;
    Bool hoisted__Bool_8772 = not(hoisted__Bool_8771);
    (void)hoisted__Bool_8772;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert(hoisted__Bool_8772, &_til_str_lit_203);
    Str_delete(&_til_str_lit_203, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8774 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8774;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_8774, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
    Bool hoisted__Bool_8776 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8776;
    Bool hoisted__Bool_8777 = not(hoisted__Bool_8776);
    (void)hoisted__Bool_8777;
    (void)_til_str_lit_205;
    (void)_til_str_lit_205;
    assert(hoisted__Bool_8777, &_til_str_lit_205);
    Str_delete(&_til_str_lit_205, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8781 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8781;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_8781, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
    Bool hoisted__Bool_8783 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8783;
    Bool hoisted__Bool_8784 = not(hoisted__Bool_8783);
    (void)hoisted__Bool_8784;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_8784, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8917 = ((Bool)(a != b));
    (void)hoisted__Bool_8917;
    if (hoisted__Bool_8917) {
        U32 hoisted__U32_8901 = 5;
        (void)hoisted__U32_8901;
        Array__Str *_va_Array_252 = Array__Str_new(hoisted__U32_8901);
        (void)_va_Array_252;
        I64 _va_Array_252_ek = 0;
        (void)_va_Array_252_ek;
        OutOfBounds *_va_Array_252_eo = malloc(sizeof(OutOfBounds));
        _va_Array_252_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_252_eo;
        U32 hoisted__U32_8902 = 0;
        (void)hoisted__U32_8902;
        (void)_til_str_lit_208;
        (void)_til_str_lit_208;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_252, hoisted__U32_8902, &_til_str_lit_208, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8905 = 1;
        (void)hoisted__U32_8905;
        Str *hoisted__Str_8906 = I64_to_str(a);
        (void)hoisted__Str_8906;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_252, hoisted__U32_8905, hoisted__Str_8906, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8908 = 2;
        (void)hoisted__U32_8908;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_252, hoisted__U32_8908, &_til_str_lit_210, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8911 = 3;
        (void)hoisted__U32_8911;
        Str *hoisted__Str_8912 = I64_to_str(b);
        (void)hoisted__Str_8912;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_252, hoisted__U32_8911, hoisted__Str_8912, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8914 = 4;
        (void)hoisted__U32_8914;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_252, hoisted__U32_8914, &_til_str_lit_211, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_209);
        OutOfBounds_delete(_va_Array_252_eo, 1);
        Str_delete(&_til_str_lit_209, (Bool){0});
        panic(_va_Array_252, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8934 = Str_neq(a, b);
    (void)hoisted__Bool_8934;
    if (hoisted__Bool_8934) {
        U32 hoisted__U32_8918 = 5;
        (void)hoisted__U32_8918;
        Array__Str *_va_Array_253 = Array__Str_new(hoisted__U32_8918);
        (void)_va_Array_253;
        I64 _va_Array_253_ek = 0;
        (void)_va_Array_253_ek;
        OutOfBounds *_va_Array_253_eo = malloc(sizeof(OutOfBounds));
        _va_Array_253_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_253_eo;
        U32 hoisted__U32_8919 = 0;
        (void)hoisted__U32_8919;
        (void)_til_str_lit_208;
        (void)_til_str_lit_208;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_253, hoisted__U32_8919, &_til_str_lit_208, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8922 = 1;
        (void)hoisted__U32_8922;
        Str *hoisted__Str_8923 = Str_to_str(a);
        (void)hoisted__Str_8923;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_253, hoisted__U32_8922, hoisted__Str_8923, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8925 = 2;
        (void)hoisted__U32_8925;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_253, hoisted__U32_8925, &_til_str_lit_210, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8928 = 3;
        (void)hoisted__U32_8928;
        Str *hoisted__Str_8929 = Str_to_str(b);
        (void)hoisted__Str_8929;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_253, hoisted__U32_8928, hoisted__Str_8929, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_209);
        Str_delete(&_til_str_lit_209, (Bool){0});
        U32 hoisted__U32_8931 = 4;
        (void)hoisted__U32_8931;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        Array__Str_set(_va_Array_253, hoisted__U32_8931, &_til_str_lit_211, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_209);
        OutOfBounds_delete(_va_Array_253_eo, 1);
        Str_delete(&_til_str_lit_209, (Bool){0});
        panic(_va_Array_253, loc);
    }
}

U32 Str_len_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Str_len(_a0);
}
static __attribute__((unused)) TilClosure Str_len_dyn__til_closure = { (void *)Str_len_dyn, NULL, NULL };
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
void *Type_Body_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_Body();
}
static __attribute__((unused)) TilClosure Type_Body_dyn__til_closure = { (void *)Type_Body_dyn, NULL, NULL };
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
void *NodeType_BodyValue_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)NodeType_BodyValue(_a0);
}
static __attribute__((unused)) TilClosure NodeType_BodyValue_dyn__til_closure = { (void *)NodeType_BodyValue_dyn, NULL, NULL };
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Str_len_dyn__til_closure;
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
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U8_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)&U32_to_i64_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U32_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U32_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U64_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U64_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U64_hash_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I8_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&I64_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)&I64_to_u8_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&F32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&F32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&F32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&F32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&F32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&F32_hash_dyn__til_closure;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Body", 4ULL) == 0) return (void*)&Type_Body_dyn__til_closure;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "BodyValue", 9ULL) == 0) return (void*)&NodeType_BodyValue_dyn__til_closure;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec__I64_new_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec__I64_clear_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec__I64_delete_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec__I64_clone_dyn__til_closure;
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec__I64_size_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) return sizeof(OutOfBounds);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) return sizeof(Array__Str);
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) return sizeof(Vec__Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) return sizeof(I8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return sizeof(I64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return sizeof(F32);
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) return sizeof(Vec__I64);
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) return sizeof(Vec__Declaration);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) return sizeof(Vec__Expr);
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
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
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
        return 7LL;
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
        return 2LL;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_0;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_4;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_44;
        if (*index == 2LL) return &_til_str_lit_45;
        if (*index == 3LL) return &_til_str_lit_46;
        if (*index == 4LL) return &_til_str_lit_47;
        if (*index == 5LL) return &_til_str_lit_48;
        if (*index == 6LL) return &_til_str_lit_49;
        if (*index == 7LL) return &_til_str_lit_50;
        if (*index == 8LL) return &_til_str_lit_52;
        if (*index == 9LL) return &_til_str_lit_54;
        if (*index == 10LL) return &_til_str_lit_56;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_57;
        if (*index == 1LL) return &_til_str_lit_59;
        if (*index == 2LL) return &_til_str_lit_61;
        if (*index == 3LL) return &_til_str_lit_62;
        if (*index == 4LL) return &_til_str_lit_64;
        if (*index == 5LL) return &_til_str_lit_65;
        if (*index == 6LL) return &_til_str_lit_66;
        if (*index == 7LL) return &_til_str_lit_67;
        if (*index == 8LL) return &_til_str_lit_68;
        if (*index == 9LL) return &_til_str_lit_69;
        if (*index == 10LL) return &_til_str_lit_70;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_71;
        if (*index == 1LL) return &_til_str_lit_72;
        if (*index == 2LL) return &_til_str_lit_73;
        if (*index == 3LL) return &_til_str_lit_74;
        if (*index == 4LL) return &_til_str_lit_75;
        if (*index == 5LL) return &_til_str_lit_52;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_76;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_77;
        if (*index == 1LL) return &_til_str_lit_78;
        if (*index == 2LL) return &_til_str_lit_79;
        if (*index == 3LL) return &_til_str_lit_80;
        if (*index == 4LL) return &_til_str_lit_81;
        if (*index == 5LL) return &_til_str_lit_82;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_78;
        if (*index == 1LL) return &_til_str_lit_83;
        if (*index == 2LL) return &_til_str_lit_84;
        if (*index == 3LL) return &_til_str_lit_86;
        if (*index == 4LL) return &_til_str_lit_82;
        if (*index == 5LL) return &_til_str_lit_88;
        if (*index == 6LL) return &_til_str_lit_89;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_91;
        if (*index == 2LL) return &_til_str_lit_92;
        if (*index == 3LL) return &_til_str_lit_75;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_91;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_46;
        if (*index == 2LL) return &_til_str_lit_52;
        if (*index == 3LL) return &_til_str_lit_93;
        if (*index == 4LL) return &_til_str_lit_94;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_52;
        if (*index == 1LL) return &_til_str_lit_100;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_69;
        if (*index == 1LL) return &_til_str_lit_70;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_135;
        if (*index == 1LL) return &_til_str_lit_137;
        if (*index == 2LL) return &_til_str_lit_139;
        if (*index == 3LL) return &_til_str_lit_140;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_141;
        if (*index == 1LL) return &_til_str_lit_142;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_149;
        if (*index == 1LL) return &_til_str_lit_150;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_175;
        if (*index == 1LL) return &_til_str_lit_176;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_181;
        if (*index == 1LL) return &_til_str_lit_183;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_175;
        if (*index == 1LL) return &_til_str_lit_176;
        if (*index == 2LL) return &_til_str_lit_188;
    }
    fprintf(stderr, "struct_field_name: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 struct_field_is_mut(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
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
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
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
        if (*index == 6LL) return 1;
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
        if (*index == 1LL) return 1;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_1;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "Declaration", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_6;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_16;
        if (*index == 6LL) return &_til_str_lit_16;
        if (*index == 7LL) return &_til_str_lit_51;
        if (*index == 8LL) return &_til_str_lit_53;
        if (*index == 9LL) return &_til_str_lit_55;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_58;
        if (*index == 1LL) return &_til_str_lit_60;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_63;
        if (*index == 4LL) return &_til_str_lit_13;
        if (*index == 5LL) return &_til_str_lit_13;
        if (*index == 6LL) return &_til_str_lit_51;
        if (*index == 7LL) return &_til_str_lit_16;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_60;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_10;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_53;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_53;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_60;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_6;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_63;
        if (*index == 2LL) return &_til_str_lit_85;
        if (*index == 3LL) return &_til_str_lit_87;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
        if (*index == 6LL) return &_til_str_lit_90;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_16;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_16;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_53;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_16;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_53;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_60;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_136;
        if (*index == 1LL) return &_til_str_lit_138;
        if (*index == 2LL) return &_til_str_lit_3;
        if (*index == 3LL) return &_til_str_lit_3;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_90;
        if (*index == 1LL) return &_til_str_lit_63;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_10;
        if (*index == 1LL) return &_til_str_lit_10;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_14;
        if (*index == 1LL) return &_til_str_lit_14;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_182;
        if (*index == 1LL) return &_til_str_lit_182;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_15;
        if (*index == 1LL) return &_til_str_lit_15;
        if (*index == 2LL) return &_til_str_lit_15;
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
        return 13LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        return 10LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        return 6LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        return 28LL;
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
        if (*index == 0LL) return &_til_str_lit_11;
        if (*index == 1LL) return &_til_str_lit_12;
        if (*index == 2LL) return &_til_str_lit_1;
        if (*index == 3LL) return &_til_str_lit_8;
        if (*index == 4LL) return &_til_str_lit_3;
        if (*index == 5LL) return &_til_str_lit_13;
        if (*index == 6LL) return &_til_str_lit_10;
        if (*index == 7LL) return &_til_str_lit_14;
        if (*index == 8LL) return &_til_str_lit_15;
        if (*index == 9LL) return &_til_str_lit_16;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_18;
        if (*index == 1LL) return &_til_str_lit_19;
        if (*index == 2LL) return &_til_str_lit_20;
        if (*index == 3LL) return &_til_str_lit_21;
        if (*index == 4LL) return &_til_str_lit_22;
        if (*index == 5LL) return &_til_str_lit_23;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_25;
        if (*index == 8LL) return &_til_str_lit_9;
        if (*index == 9LL) return &_til_str_lit_26;
        if (*index == 10LL) return &_til_str_lit_27;
        if (*index == 11LL) return &_til_str_lit_28;
        if (*index == 12LL) return &_til_str_lit_29;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_30;
        if (*index == 1LL) return &_til_str_lit_31;
        if (*index == 2LL) return &_til_str_lit_32;
        if (*index == 3LL) return &_til_str_lit_33;
        if (*index == 4LL) return &_til_str_lit_34;
        if (*index == 5LL) return &_til_str_lit_35;
        if (*index == 6LL) return &_til_str_lit_36;
        if (*index == 7LL) return &_til_str_lit_37;
        if (*index == 8LL) return &_til_str_lit_38;
        if (*index == 9LL) return &_til_str_lit_39;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_40;
        if (*index == 1LL) return &_til_str_lit_41;
        if (*index == 2LL) return &_til_str_lit_42;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_95;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_97;
        if (*index == 4LL) return &_til_str_lit_98;
        if (*index == 5LL) return &_til_str_lit_99;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_29;
        if (*index == 1LL) return &_til_str_lit_101;
        if (*index == 2LL) return &_til_str_lit_102;
        if (*index == 3LL) return &_til_str_lit_104;
        if (*index == 4LL) return &_til_str_lit_106;
        if (*index == 5LL) return &_til_str_lit_108;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_111;
        if (*index == 10LL) return &_til_str_lit_113;
        if (*index == 11LL) return &_til_str_lit_115;
        if (*index == 12LL) return &_til_str_lit_116;
        if (*index == 13LL) return &_til_str_lit_117;
        if (*index == 14LL) return &_til_str_lit_118;
        if (*index == 15LL) return &_til_str_lit_120;
        if (*index == 16LL) return &_til_str_lit_121;
        if (*index == 17LL) return &_til_str_lit_122;
        if (*index == 18LL) return &_til_str_lit_123;
        if (*index == 19LL) return &_til_str_lit_124;
        if (*index == 20LL) return &_til_str_lit_126;
        if (*index == 21LL) return &_til_str_lit_127;
        if (*index == 22LL) return &_til_str_lit_128;
        if (*index == 23LL) return &_til_str_lit_129;
        if (*index == 24LL) return &_til_str_lit_130;
        if (*index == 25LL) return &_til_str_lit_131;
        if (*index == 26LL) return &_til_str_lit_133;
        if (*index == 27LL) return &_til_str_lit_134;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_195;
        if (*index == 1LL) return &_til_str_lit_196;
        if (*index == 2LL) return &_til_str_lit_197;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_95;
        if (*index == 1LL) return &_til_str_lit_200;
        if (*index == 2LL) return &_til_str_lit_201;
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
        if (*index == 12LL) return 0;
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
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
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
        if (*index == 27LL) return 1;
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
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_6;
        if (*index == 10LL) return &_til_str_lit_27;
        if (*index == 11LL) return &_til_str_lit_6;
        if (*index == 12LL) return &_til_str_lit_17;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
        if (*index == 6LL) return &_til_str_lit_17;
        if (*index == 7LL) return &_til_str_lit_17;
        if (*index == 8LL) return &_til_str_lit_17;
        if (*index == 9LL) return &_til_str_lit_17;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_96;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_101;
        if (*index == 2LL) return &_til_str_lit_103;
        if (*index == 3LL) return &_til_str_lit_105;
        if (*index == 4LL) return &_til_str_lit_107;
        if (*index == 5LL) return &_til_str_lit_109;
        if (*index == 6LL) return &_til_str_lit_110;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_112;
        if (*index == 10LL) return &_til_str_lit_114;
        if (*index == 11LL) return &_til_str_lit_17;
        if (*index == 12LL) return &_til_str_lit_17;
        if (*index == 13LL) return &_til_str_lit_17;
        if (*index == 14LL) return &_til_str_lit_119;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_17;
        if (*index == 17LL) return &_til_str_lit_17;
        if (*index == 18LL) return &_til_str_lit_17;
        if (*index == 19LL) return &_til_str_lit_125;
        if (*index == 20LL) return &_til_str_lit_17;
        if (*index == 21LL) return &_til_str_lit_17;
        if (*index == 22LL) return &_til_str_lit_17;
        if (*index == 23LL) return &_til_str_lit_17;
        if (*index == 24LL) return &_til_str_lit_17;
        if (*index == 25LL) return &_til_str_lit_132;
        if (*index == 26LL) return &_til_str_lit_17;
        if (*index == 27LL) return &_til_str_lit_132;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_17;
        if (*index == 2LL) return &_til_str_lit_17;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_14;
        if (*index == 1LL) return &_til_str_lit_6;
        if (*index == 2LL) return &_til_str_lit_17;
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
        if (*index == 0LL) return &_til_str_lit_9;
        if (*index == 1LL) return &_til_str_lit_3;
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
        if (*index == 0LL) return &_til_str_lit_10;
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
