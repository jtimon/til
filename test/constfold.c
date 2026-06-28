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
    Bool return_shallow_explicit;
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
Str * U64_to_str(U64 val);
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
Str * U64_to_str(U64 val);
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
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_214 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

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

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1440 = U64_to_str_ext(val);
    (void)hoisted__Str_1440;
    return hoisted__Str_1440;
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
    I64 hoisted__I64_1897 = 0;
    (void)hoisted__I64_1897;
    Bool hoisted__Bool_1898 = ((Bool)(val < hoisted__I64_1897));
    (void)hoisted__Bool_1898;
    if (hoisted__Bool_1898) {
        U64 hoisted__U64_1887 = 0ULL;
        (void)hoisted__U64_1887;
        U64 hoisted__U64_1888 = (U64)(val);
        (void)hoisted__U64_1888;
        U64 mag = ((U64)(hoisted__U64_1887 - hoisted__U64_1888));
        U32 hoisted__U32_1889 = 2;
        (void)hoisted__U32_1889;
        Array__Str *_va_Array_44 = Array__Str_new(hoisted__U32_1889);
        (void)_va_Array_44;
        I64 _va_Array_44_ek = 0;
        (void)_va_Array_44_ek;
        OutOfBounds *_va_Array_44_eo = malloc(sizeof(OutOfBounds));
        _va_Array_44_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_44_eo;
        U32 hoisted__U32_1890 = 0;
        (void)hoisted__U32_1890;
        static Str hoisted__Str_1891 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1891;
        static Str hoisted__Str_1892 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1892;
        Array__Str_set(_va_Array_44, hoisted__U32_1890, &hoisted__Str_1891, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1892);
        Str_delete(&hoisted__Str_1892, (Bool){0});
        U32 hoisted__U32_1893 = 1;
        (void)hoisted__U32_1893;
        Str *hoisted__Str_1894 = U64_to_str(mag);
        (void)hoisted__Str_1894;
        static Str hoisted__Str_1895 = (Str){.c_str = (void *)"./src/core/numbers.til:626:20", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1895;
        Array__Str_set(_va_Array_44, hoisted__U32_1893, hoisted__Str_1894, &_va_Array_44_ek, _va_Array_44_eo, &hoisted__Str_1895);
        OutOfBounds_delete(_va_Array_44_eo, 1);
        Str_delete(&hoisted__Str_1895, (Bool){0});
        Str *hoisted__Str_1896 = format(_va_Array_44);
        (void)hoisted__Str_1896;
        { Str * _ret_val = hoisted__Str_1896;
                return _ret_val; }
    }
    U64 hoisted__U64_1899 = (U64)(val);
    (void)hoisted__U64_1899;
    Str *hoisted__Str_1900 = U64_to_str(hoisted__U64_1899);
    (void)hoisted__Str_1900;
    return hoisted__Str_1900;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1918 = 8;
    (void)hoisted__U32_1918;
    return hoisted__U32_1918;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2076 = 0;
    (void)hoisted__U32_2076;
    U64 hoisted__U64_2077 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2076); });
    (void)hoisted__U64_2077;
    return hoisted__U64_2077;
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_2079 = 4;
    (void)hoisted__U32_2079;
    return hoisted__U32_2079;
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_2097 = 0;
    (void)hoisted__U32_2097;
    U64 hoisted__U64_2098 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2097); });
    (void)hoisted__U64_2098;
    return hoisted__U64_2098;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2145 = 0;
    (void)_m_Bool_2145;
    {
        Bool hoisted__Bool_2148 = 1;
        (void)hoisted__Bool_2148;
        Bool hoisted__Bool_2149 = ((Bool)(a == hoisted__Bool_2148));
        (void)hoisted__Bool_2149;
        if (hoisted__Bool_2149) {
            Bool hoisted__Bool_2146 = Bool_clone(&b);
            (void)hoisted__Bool_2146;
            _m_Bool_2145 = hoisted__Bool_2146;
        } else {
            Bool hoisted__Bool_2147 = 0;
            (void)hoisted__Bool_2147;
            _m_Bool_2145 = hoisted__Bool_2147;
        }
    }
    return _m_Bool_2145;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2159 = ((Bool)(a == b));
    (void)hoisted__Bool_2159;
    if (hoisted__Bool_2159) {
        I64 hoisted__I64_2157 = 0;
        (void)hoisted__I64_2157;
        { I64 _ret_val = hoisted__I64_2157;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2158 = -1;
        (void)hoisted__I64_2158;
        return hoisted__I64_2158;
    }
    I64 hoisted__I64_2160 = 1;
    (void)hoisted__I64_2160;
    return hoisted__I64_2160;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2161 = 1;
    (void)hoisted__U32_2161;
    return hoisted__U32_2161;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2162 = 0;
    (void)hoisted__U32_2162;
    U64 hoisted__U64_2163 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2162); });
    (void)hoisted__U64_2163;
    return hoisted__U64_2163;
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
    U32 hoisted__U32_2200 = 1;
    (void)hoisted__U32_2200;
    Bool hoisted__Bool_2201 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2201;
    if (hoisted__Bool_2201) {
        U32 hoisted__U32_2180 = 1;
        (void)hoisted__U32_2180;
        Bool hoisted__Bool_2181 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2181;
        { Bool _ret_val = hoisted__Bool_2181;
                return _ret_val; }
    }
    U32 hoisted__U32_2202 = 1;
    (void)hoisted__U32_2202;
    Bool hoisted__Bool_2203 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2203;
    if (hoisted__Bool_2203) {
        U32 hoisted__U32_2182 = 1;
        (void)hoisted__U32_2182;
        Bool hoisted__Bool_2183 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2183;
        { Bool _ret_val = hoisted__Bool_2183;
                return _ret_val; }
    }
    U32 hoisted__U32_2204 = 1;
    (void)hoisted__U32_2204;
    Bool hoisted__Bool_2205 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        U32 hoisted__U32_2184 = 1;
        (void)hoisted__U32_2184;
        Bool hoisted__Bool_2185 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2185;
        { Bool _ret_val = hoisted__Bool_2185;
                return _ret_val; }
    }
    U32 hoisted__U32_2206 = 1;
    (void)hoisted__U32_2206;
    Bool hoisted__Bool_2207 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2207;
    if (hoisted__Bool_2207) {
        U32 hoisted__U32_2186 = 1;
        (void)hoisted__U32_2186;
        Bool hoisted__Bool_2187 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2187;
        { Bool _ret_val = hoisted__Bool_2187;
                return _ret_val; }
    }
    U32 hoisted__U32_2208 = 1;
    (void)hoisted__U32_2208;
    Bool hoisted__Bool_2209 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2209;
    if (hoisted__Bool_2209) {
        U32 hoisted__U32_2188 = 1;
        (void)hoisted__U32_2188;
        Bool hoisted__Bool_2189 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2189;
        { Bool _ret_val = hoisted__Bool_2189;
                return _ret_val; }
    }
    U32 hoisted__U32_2210 = 1;
    (void)hoisted__U32_2210;
    Bool hoisted__Bool_2211 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2211;
    if (hoisted__Bool_2211) {
        U32 hoisted__U32_2190 = 1;
        (void)hoisted__U32_2190;
        Bool hoisted__Bool_2191 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2191;
        { Bool _ret_val = hoisted__Bool_2191;
                return _ret_val; }
    }
    U32 hoisted__U32_2212 = 1;
    (void)hoisted__U32_2212;
    Bool hoisted__Bool_2213 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2213;
    if (hoisted__Bool_2213) {
        U32 hoisted__U32_2192 = 1;
        (void)hoisted__U32_2192;
        Bool hoisted__Bool_2193 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2193;
        { Bool _ret_val = hoisted__Bool_2193;
                return _ret_val; }
    }
    U32 hoisted__U32_2214 = 1;
    (void)hoisted__U32_2214;
    Bool hoisted__Bool_2215 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2215;
    if (hoisted__Bool_2215) {
        U32 hoisted__U32_2194 = 1;
        (void)hoisted__U32_2194;
        Bool hoisted__Bool_2195 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2195;
        { Bool _ret_val = hoisted__Bool_2195;
                return _ret_val; }
    }
    U32 hoisted__U32_2216 = 1;
    (void)hoisted__U32_2216;
    Bool hoisted__Bool_2217 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2217;
    if (hoisted__Bool_2217) {
        U32 hoisted__U32_2196 = 1;
        (void)hoisted__U32_2196;
        Bool hoisted__Bool_2197 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2197;
        { Bool _ret_val = hoisted__Bool_2197;
                return _ret_val; }
    }
    U32 hoisted__U32_2218 = 1;
    (void)hoisted__U32_2218;
    Bool hoisted__Bool_2219 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2219;
    if (hoisted__Bool_2219) {
        U32 hoisted__U32_2198 = 1;
        (void)hoisted__U32_2198;
        Bool hoisted__Bool_2199 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_2199;
        { Bool _ret_val = hoisted__Bool_2199;
                return _ret_val; }
    }
    Bool hoisted__Bool_2220 = 0;
    (void)hoisted__Bool_2220;
    return hoisted__Bool_2220;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2242 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2243 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2243;
    if (hoisted__Bool_2243) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2244 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2245 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2245;
    if (hoisted__Bool_2245) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2246 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2246;
    if (hoisted__Bool_2246) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2247 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2247;
    if (hoisted__Bool_2247) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2248 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2248;
    if (hoisted__Bool_2248) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2249 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2249;
    if (hoisted__Bool_2249) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2250 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2250;
    if (hoisted__Bool_2250) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2251 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2251;
    if (hoisted__Bool_2251) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2252 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2252;
    UNREACHABLE(&hoisted__Str_2252);
    Str_delete(&hoisted__Str_2252, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2253 = 1;
    (void)hoisted__U32_2253;
    return hoisted__U32_2253;
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
    U32 hoisted__U32_2334 = 1;
    (void)hoisted__U32_2334;
    Bool hoisted__Bool_2335 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2335;
    if (hoisted__Bool_2335) {
        Str *hoisted__Str_2324 = get_payload(self);
        (void)hoisted__Str_2324;
        (void)hoisted__Str_2324;
        Bool hoisted__Bool_2325 = 0;
        (void)hoisted__Bool_2325;
        Str_delete(hoisted__Str_2324, hoisted__Bool_2325);
    }
    U32 hoisted__U32_2336 = 1;
    (void)hoisted__U32_2336;
    Bool hoisted__Bool_2337 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2337;
    if (hoisted__Bool_2337) {
        Str *hoisted__Str_2326 = get_payload(self);
        (void)hoisted__Str_2326;
        (void)hoisted__Str_2326;
        Bool hoisted__Bool_2327 = 0;
        (void)hoisted__Bool_2327;
        Str_delete(hoisted__Str_2326, hoisted__Bool_2327);
    }
    U32 hoisted__U32_2338 = 1;
    (void)hoisted__U32_2338;
    Bool hoisted__Bool_2339 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2339;
    if (hoisted__Bool_2339) {
        Str *hoisted__Str_2328 = get_payload(self);
        (void)hoisted__Str_2328;
        (void)hoisted__Str_2328;
        Bool hoisted__Bool_2329 = 0;
        (void)hoisted__Bool_2329;
        Str_delete(hoisted__Str_2328, hoisted__Bool_2329);
    }
    U32 hoisted__U32_2340 = 1;
    (void)hoisted__U32_2340;
    Bool hoisted__Bool_2341 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2341;
    if (hoisted__Bool_2341) {
        Primitive *hoisted__Primitive_2330 = get_payload(self);
        (void)hoisted__Primitive_2330;
        (void)hoisted__Primitive_2330;
        Bool hoisted__Bool_2331 = 0;
        (void)hoisted__Bool_2331;
        Primitive_delete(hoisted__Primitive_2330, hoisted__Bool_2331);
    }
    U32 hoisted__U32_2342 = 1;
    (void)hoisted__U32_2342;
    Bool hoisted__Bool_2343 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2343;
    if (hoisted__Bool_2343) {
        Str *hoisted__Str_2332 = get_payload(self);
        (void)hoisted__Str_2332;
        (void)hoisted__Str_2332;
        Bool hoisted__Bool_2333 = 0;
        (void)hoisted__Bool_2333;
        Str_delete(hoisted__Str_2332, hoisted__Bool_2333);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U32 hoisted__U32_2444 = 1;
    (void)hoisted__U32_2444;
    Bool hoisted__Bool_2445 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2445;
    if (hoisted__Bool_2445) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U32 hoisted__U32_2446 = 1;
    (void)hoisted__U32_2446;
    Bool hoisted__Bool_2447 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2447;
    if (hoisted__Bool_2447) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U32 hoisted__U32_2448 = 1;
    (void)hoisted__U32_2448;
    Bool hoisted__Bool_2449 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2449;
    if (hoisted__Bool_2449) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2434 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2434;
        Type *hoisted__Type_2435 = Type_Struct(hoisted__Str_2434);
        (void)hoisted__Type_2435;
        { Type * _ret_val = hoisted__Type_2435;
                return _ret_val; }
    }
    U32 hoisted__U32_2450 = 1;
    (void)hoisted__U32_2450;
    Bool hoisted__Bool_2451 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2451;
    if (hoisted__Bool_2451) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U32 hoisted__U32_2452 = 1;
    (void)hoisted__U32_2452;
    Bool hoisted__Bool_2453 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2453;
    if (hoisted__Bool_2453) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2436 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2436;
        Type *hoisted__Type_2437 = Type_Enum(hoisted__Str_2436);
        (void)hoisted__Type_2437;
        { Type * _ret_val = hoisted__Type_2437;
                return _ret_val; }
    }
    U32 hoisted__U32_2454 = 1;
    (void)hoisted__U32_2454;
    Bool hoisted__Bool_2455 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2455;
    if (hoisted__Bool_2455) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U32 hoisted__U32_2456 = 1;
    (void)hoisted__U32_2456;
    Bool hoisted__Bool_2457 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2457;
    if (hoisted__Bool_2457) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U32 hoisted__U32_2458 = 1;
    (void)hoisted__U32_2458;
    Bool hoisted__Bool_2459 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2459;
    if (hoisted__Bool_2459) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U32 hoisted__U32_2460 = 1;
    (void)hoisted__U32_2460;
    Bool hoisted__Bool_2461 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2461;
    if (hoisted__Bool_2461) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U32 hoisted__U32_2462 = 1;
    (void)hoisted__U32_2462;
    Bool hoisted__Bool_2463 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2463;
    if (hoisted__Bool_2463) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2438 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2438;
        Type *hoisted__Type_2439 = Type_Custom(hoisted__Str_2438);
        (void)hoisted__Type_2439;
        { Type * _ret_val = hoisted__Type_2439;
                return _ret_val; }
    }
    U32 hoisted__U32_2464 = 1;
    (void)hoisted__U32_2464;
    Bool hoisted__Bool_2465 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2465;
    if (hoisted__Bool_2465) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2440 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2440;
        Type *hoisted__Type_2441 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2440; _oa; }));
        (void)hoisted__Type_2441;
        { Type * _ret_val = hoisted__Type_2441;
                return _ret_val; }
    }
    U32 hoisted__U32_2466 = 1;
    (void)hoisted__U32_2466;
    Bool hoisted__Bool_2467 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2467;
    if (hoisted__Bool_2467) {
        Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2442 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2442;
        Type *hoisted__Type_2443 = Type_FuncPtrSig(hoisted__Str_2442);
        (void)hoisted__Type_2443;
        { Type * _ret_val = hoisted__Type_2443;
                return _ret_val; }
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
}

U32 Type_size(void) {
    U32 hoisted__U32_2468 = 24;
    (void)hoisted__U32_2468;
    return hoisted__U32_2468;
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
    U32 hoisted__U32_2616 = 1;
    (void)hoisted__U32_2616;
    Bool hoisted__Bool_2617 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2617;
    if (hoisted__Bool_2617) {
        U32 hoisted__U32_2596 = 1;
        (void)hoisted__U32_2596;
        Bool hoisted__Bool_2597 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2597;
        { Bool _ret_val = hoisted__Bool_2597;
                return _ret_val; }
    }
    U32 hoisted__U32_2618 = 1;
    (void)hoisted__U32_2618;
    Bool hoisted__Bool_2619 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2619;
    if (hoisted__Bool_2619) {
        U32 hoisted__U32_2598 = 1;
        (void)hoisted__U32_2598;
        Bool hoisted__Bool_2599 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2599;
        { Bool _ret_val = hoisted__Bool_2599;
                return _ret_val; }
    }
    U32 hoisted__U32_2620 = 1;
    (void)hoisted__U32_2620;
    Bool hoisted__Bool_2621 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2621;
    if (hoisted__Bool_2621) {
        U32 hoisted__U32_2600 = 1;
        (void)hoisted__U32_2600;
        Bool hoisted__Bool_2601 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2601;
        { Bool _ret_val = hoisted__Bool_2601;
                return _ret_val; }
    }
    U32 hoisted__U32_2622 = 1;
    (void)hoisted__U32_2622;
    Bool hoisted__Bool_2623 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2623;
    if (hoisted__Bool_2623) {
        U32 hoisted__U32_2602 = 1;
        (void)hoisted__U32_2602;
        Bool hoisted__Bool_2603 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2603;
        { Bool _ret_val = hoisted__Bool_2603;
                return _ret_val; }
    }
    U32 hoisted__U32_2624 = 1;
    (void)hoisted__U32_2624;
    Bool hoisted__Bool_2625 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2625;
    if (hoisted__Bool_2625) {
        U32 hoisted__U32_2604 = 1;
        (void)hoisted__U32_2604;
        Bool hoisted__Bool_2605 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2605;
        { Bool _ret_val = hoisted__Bool_2605;
                return _ret_val; }
    }
    U32 hoisted__U32_2626 = 1;
    (void)hoisted__U32_2626;
    Bool hoisted__Bool_2627 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2627;
    if (hoisted__Bool_2627) {
        U32 hoisted__U32_2606 = 1;
        (void)hoisted__U32_2606;
        Bool hoisted__Bool_2607 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2607;
        { Bool _ret_val = hoisted__Bool_2607;
                return _ret_val; }
    }
    U32 hoisted__U32_2628 = 1;
    (void)hoisted__U32_2628;
    Bool hoisted__Bool_2629 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2629;
    if (hoisted__Bool_2629) {
        U32 hoisted__U32_2608 = 1;
        (void)hoisted__U32_2608;
        Bool hoisted__Bool_2609 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2609;
        { Bool _ret_val = hoisted__Bool_2609;
                return _ret_val; }
    }
    U32 hoisted__U32_2630 = 1;
    (void)hoisted__U32_2630;
    Bool hoisted__Bool_2631 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2631;
    if (hoisted__Bool_2631) {
        U32 hoisted__U32_2610 = 1;
        (void)hoisted__U32_2610;
        Bool hoisted__Bool_2611 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2611;
        { Bool _ret_val = hoisted__Bool_2611;
                return _ret_val; }
    }
    U32 hoisted__U32_2632 = 1;
    (void)hoisted__U32_2632;
    Bool hoisted__Bool_2633 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2633;
    if (hoisted__Bool_2633) {
        U32 hoisted__U32_2612 = 1;
        (void)hoisted__U32_2612;
        Bool hoisted__Bool_2613 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2613;
        { Bool _ret_val = hoisted__Bool_2613;
                return _ret_val; }
    }
    U32 hoisted__U32_2634 = 1;
    (void)hoisted__U32_2634;
    Bool hoisted__Bool_2635 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2635;
    if (hoisted__Bool_2635) {
        U32 hoisted__U32_2614 = 1;
        (void)hoisted__U32_2614;
        Bool hoisted__Bool_2615 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2615;
        { Bool _ret_val = hoisted__Bool_2615;
                return _ret_val; }
    }
    Bool hoisted__Bool_2636 = 0;
    (void)hoisted__Bool_2636;
    return hoisted__Bool_2636;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2658 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2658;
    if (hoisted__Bool_2658) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2659 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2659;
    if (hoisted__Bool_2659) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2660 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2660;
    if (hoisted__Bool_2660) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2661 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2661;
    if (hoisted__Bool_2661) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2662 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2662;
    if (hoisted__Bool_2662) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2663 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2663;
    if (hoisted__Bool_2663) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2664 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2664;
    if (hoisted__Bool_2664) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2665 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2665;
    if (hoisted__Bool_2665) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2666 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2666;
    if (hoisted__Bool_2666) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2667 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2667;
    if (hoisted__Bool_2667) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2668 = (Str){.c_str = (void *)"FuncType.clone:130:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2668;
    UNREACHABLE(&hoisted__Str_2668);
    Str_delete(&hoisted__Str_2668, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2669 = 1;
    (void)hoisted__U32_2669;
    return hoisted__U32_2669;
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
    U32 hoisted__U32_2678 = 1;
    (void)hoisted__U32_2678;
    Bool hoisted__Bool_2679 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2679;
    if (hoisted__Bool_2679) {
        U32 hoisted__U32_2672 = 1;
        (void)hoisted__U32_2672;
        Bool hoisted__Bool_2673 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2673;
        { Bool _ret_val = hoisted__Bool_2673;
                return _ret_val; }
    }
    U32 hoisted__U32_2680 = 1;
    (void)hoisted__U32_2680;
    Bool hoisted__Bool_2681 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2681;
    if (hoisted__Bool_2681) {
        U32 hoisted__U32_2674 = 1;
        (void)hoisted__U32_2674;
        Bool hoisted__Bool_2675 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2675;
        { Bool _ret_val = hoisted__Bool_2675;
                return _ret_val; }
    }
    U32 hoisted__U32_2682 = 1;
    (void)hoisted__U32_2682;
    Bool hoisted__Bool_2683 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2683;
    if (hoisted__Bool_2683) {
        U32 hoisted__U32_2676 = 1;
        (void)hoisted__U32_2676;
        Bool hoisted__Bool_2677 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2677;
        { Bool _ret_val = hoisted__Bool_2677;
                return _ret_val; }
    }
    Bool hoisted__Bool_2684 = 0;
    (void)hoisted__Bool_2684;
    return hoisted__Bool_2684;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2692 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2692;
    if (hoisted__Bool_2692) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2693 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2693;
    if (hoisted__Bool_2693) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2694 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2694;
    if (hoisted__Bool_2694) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2695 = (Str){.c_str = (void *)"OwnType.clone:142:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2695;
    UNREACHABLE(&hoisted__Str_2695);
    Str_delete(&hoisted__Str_2695, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2696 = 1;
    (void)hoisted__U32_2696;
    return hoisted__U32_2696;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2698 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2698;
    Declaration *hoisted__Declaration_2699 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2699->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2699->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2699->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2699->is_mut = self->is_mut;
    hoisted__Declaration_2699->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2699->is_priv = self->is_priv;
    hoisted__Declaration_2699->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2699->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2699->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2699->default_value = hoisted__Expr_2698;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2699->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2699;
    return hoisted__Declaration_2699;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2700 = 0;
    (void)hoisted__Bool_2700;
    Str_delete(&self->name, hoisted__Bool_2700);
    Bool hoisted__Bool_2701 = 0;
    (void)hoisted__Bool_2701;
    Str_delete(&self->doc, hoisted__Bool_2701);
    Bool hoisted__Bool_2702 = 0;
    (void)hoisted__Bool_2702;
    Str_delete(&self->explicit_type, hoisted__Bool_2702);
    Bool hoisted__Bool_2703 = 0;
    (void)hoisted__Bool_2703;
    Bool_delete(&self->is_mut, hoisted__Bool_2703);
    Bool hoisted__Bool_2704 = 0;
    (void)hoisted__Bool_2704;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2704);
    Bool hoisted__Bool_2705 = 0;
    (void)hoisted__Bool_2705;
    Bool_delete(&self->is_priv, hoisted__Bool_2705);
    Bool hoisted__Bool_2706 = 0;
    (void)hoisted__Bool_2706;
    Bool_delete(&self->used, hoisted__Bool_2706);
    Bool hoisted__Bool_2707 = 0;
    (void)hoisted__Bool_2707;
    OwnType_delete(&self->own_type, hoisted__Bool_2707);
    Bool hoisted__Bool_2708 = 0;
    (void)hoisted__Bool_2708;
    Type_delete(&self->til_type, hoisted__Bool_2708);
    Bool hoisted__Bool_2709 = 1;
    (void)hoisted__Bool_2709;
    Expr_delete(self->default_value, hoisted__Bool_2709);
    Bool hoisted__Bool_2710 = 0;
    (void)hoisted__Bool_2710;
    Str_delete(&self->orig_name, hoisted__Bool_2710);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2711 = 104;
    (void)hoisted__U32_2711;
    return hoisted__U32_2711;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2713 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2713->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2713->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2713->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2713->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2713->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2713->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2713->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2713->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2713->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2713->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2713->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2713->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2713;
    return hoisted__FunctionDef_2713;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2714 = 0;
    (void)hoisted__Bool_2714;
    FuncType_delete(&self->func_type, hoisted__Bool_2714);
    Bool hoisted__Bool_2715 = 0;
    (void)hoisted__Bool_2715;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2715);
    Bool hoisted__Bool_2716 = 0;
    (void)hoisted__Bool_2716;
    Str_delete(&self->return_type, hoisted__Bool_2716);
    Bool hoisted__Bool_2717 = 0;
    (void)hoisted__Bool_2717;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2717);
    Bool hoisted__Bool_2718 = 0;
    (void)hoisted__Bool_2718;
    I32_delete(&self->variadic_index, hoisted__Bool_2718);
    Bool hoisted__Bool_2719 = 0;
    (void)hoisted__Bool_2719;
    I32_delete(&self->kwargs_index, hoisted__Bool_2719);
    Bool hoisted__Bool_2720 = 0;
    (void)hoisted__Bool_2720;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2720);
    Bool hoisted__Bool_2721 = 0;
    (void)hoisted__Bool_2721;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2721);
    Bool hoisted__Bool_2722 = 0;
    (void)hoisted__Bool_2722;
    Bool_delete(&self->auto_generated, hoisted__Bool_2722);
    Bool hoisted__Bool_2723 = 0;
    (void)hoisted__Bool_2723;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2723);
    Bool hoisted__Bool_2724 = 0;
    (void)hoisted__Bool_2724;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2724);
    Bool hoisted__Bool_2725 = 0;
    (void)hoisted__Bool_2725;
    Str_delete(&self->closure_name, hoisted__Bool_2725);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2726 = 0;
    (void)hoisted__U32_2726;
    U64 hoisted__U64_2727 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2726); });
    (void)hoisted__U64_2727;
    return hoisted__U64_2727;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2728 = 104;
    (void)hoisted__U32_2728;
    return hoisted__U32_2728;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2731 = malloc(sizeof(FCallData));
    hoisted__FCallData_2731->is_splat = self->is_splat;
    hoisted__FCallData_2731->does_throw = self->does_throw;
    hoisted__FCallData_2731->is_bang = self->is_bang;
    hoisted__FCallData_2731->own_args = self->own_args;
    hoisted__FCallData_2731->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2731->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2731;
    return hoisted__FCallData_2731;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2732 = 0;
    (void)hoisted__Bool_2732;
    Bool_delete(&self->is_splat, hoisted__Bool_2732);
    Bool hoisted__Bool_2733 = 0;
    (void)hoisted__Bool_2733;
    Bool_delete(&self->does_throw, hoisted__Bool_2733);
    Bool hoisted__Bool_2734 = 0;
    (void)hoisted__Bool_2734;
    Bool_delete(&self->is_bang, hoisted__Bool_2734);
    Bool hoisted__Bool_2735 = 0;
    (void)hoisted__Bool_2735;
    U64_delete(&self->own_args, hoisted__Bool_2735);
    Bool hoisted__Bool_2736 = 0;
    (void)hoisted__Bool_2736;
    Bool_delete(&self->swap_replace, hoisted__Bool_2736);
    Bool hoisted__Bool_2737 = 0;
    (void)hoisted__Bool_2737;
    Type_delete(&self->til_type, hoisted__Bool_2737);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2738 = 0;
    (void)hoisted__U32_2738;
    U64 hoisted__U64_2739 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2738); });
    (void)hoisted__U64_2739;
    return hoisted__U64_2739;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2740 = 48;
    (void)hoisted__U32_2740;
    return hoisted__U32_2740;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2752 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2752->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2752->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2752;
    return hoisted__LiteralNumData_2752;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Str_delete(&self->text, hoisted__Bool_2753);
    Bool hoisted__Bool_2754 = 0;
    (void)hoisted__Bool_2754;
    Type_delete(&self->til_type, hoisted__Bool_2754);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2755 = 0;
    (void)hoisted__U32_2755;
    U64 hoisted__U64_2756 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2755); });
    (void)hoisted__U64_2756;
    return hoisted__U64_2756;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2757 = 40;
    (void)hoisted__U32_2757;
    return hoisted__U32_2757;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2767 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2767->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2767->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2767;
    return hoisted__IdentData_2767;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2768 = 0;
    (void)hoisted__Bool_2768;
    Str_delete(&self->name, hoisted__Bool_2768);
    Bool hoisted__Bool_2769 = 0;
    (void)hoisted__Bool_2769;
    Type_delete(&self->til_type, hoisted__Bool_2769);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2770 = 0;
    (void)hoisted__U32_2770;
    U64 hoisted__U64_2771 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2770); });
    (void)hoisted__U64_2771;
    return hoisted__U64_2771;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2772 = 40;
    (void)hoisted__U32_2772;
    return hoisted__U32_2772;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2778 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2778->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2778->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2778;
    return hoisted__FieldAccessData_2778;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2779 = 0;
    (void)hoisted__Bool_2779;
    Str_delete(&self->name, hoisted__Bool_2779);
    Bool hoisted__Bool_2780 = 0;
    (void)hoisted__Bool_2780;
    Type_delete(&self->til_type, hoisted__Bool_2780);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2781 = 0;
    (void)hoisted__U32_2781;
    U64 hoisted__U64_2782 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2781); });
    (void)hoisted__U64_2782;
    return hoisted__U64_2782;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2783 = 40;
    (void)hoisted__U32_2783;
    return hoisted__U32_2783;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2864 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2864->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2864->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2864->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2864->is_interface = self->is_interface;
    hoisted__StructDef_2864->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2864->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2864;
    return hoisted__StructDef_2864;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2865 = 0;
    (void)hoisted__Bool_2865;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2865);
    Bool hoisted__Bool_2866 = 0;
    (void)hoisted__Bool_2866;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2866);
    Bool hoisted__Bool_2867 = 0;
    (void)hoisted__Bool_2867;
    Str_delete(&self->c_tag, hoisted__Bool_2867);
    Bool hoisted__Bool_2868 = 0;
    (void)hoisted__Bool_2868;
    Bool_delete(&self->is_interface, hoisted__Bool_2868);
    Bool hoisted__Bool_2869 = 0;
    (void)hoisted__Bool_2869;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2869);
    Bool hoisted__Bool_2870 = 0;
    (void)hoisted__Bool_2870;
    Str_delete(&self->implements_name, hoisted__Bool_2870);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2871 = 0;
    (void)hoisted__U32_2871;
    U64 hoisted__U64_2872 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2871); });
    (void)hoisted__U64_2872;
    return hoisted__U64_2872;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2873 = 72;
    (void)hoisted__U32_2873;
    return hoisted__U32_2873;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2878 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2878->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2878->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2878->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2878->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2878->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2878->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2878->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2878;
    return hoisted__EnumDef_2878;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2879 = 0;
    (void)hoisted__Bool_2879;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2879);
    Bool hoisted__Bool_2880 = 0;
    (void)hoisted__Bool_2880;
    Vec__Str_delete(&self->variants, hoisted__Bool_2880);
    Bool hoisted__Bool_2881 = 0;
    (void)hoisted__Bool_2881;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2881);
    Bool hoisted__Bool_2882 = 0;
    (void)hoisted__Bool_2882;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2882);
    Bool hoisted__Bool_2883 = 0;
    (void)hoisted__Bool_2883;
    Str_delete(&self->implements_name, hoisted__Bool_2883);
    Bool hoisted__Bool_2884 = 0;
    (void)hoisted__Bool_2884;
    Str_delete(&self->tag_type, hoisted__Bool_2884);
    Bool hoisted__Bool_2885 = 0;
    (void)hoisted__Bool_2885;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2885);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2886 = 0;
    (void)hoisted__U32_2886;
    U64 hoisted__U64_2887 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2886); });
    (void)hoisted__U64_2887;
    return hoisted__U64_2887;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2888 = 128;
    (void)hoisted__U32_2888;
    return hoisted__U32_2888;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2989 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2989->name = *_ca; free(_ca); }
    hoisted__AssignData_2989->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2989->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2989->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2989;
    return hoisted__AssignData_2989;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2990 = 0;
    (void)hoisted__Bool_2990;
    Str_delete(&self->name, hoisted__Bool_2990);
    Bool hoisted__Bool_2991 = 0;
    (void)hoisted__Bool_2991;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2991);
    Bool hoisted__Bool_2992 = 0;
    (void)hoisted__Bool_2992;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2992);
    Bool hoisted__Bool_2993 = 0;
    (void)hoisted__Bool_2993;
    Bool_delete(&self->swap_replace, hoisted__Bool_2993);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2994 = 0;
    (void)hoisted__U32_2994;
    U64 hoisted__U64_2995 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2994); });
    (void)hoisted__U64_2995;
    return hoisted__U64_2995;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2996 = 24;
    (void)hoisted__U32_2996;
    return hoisted__U32_2996;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2998 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2998->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2998->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2998;
    return hoisted__FieldAssignData_2998;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2999 = 0;
    (void)hoisted__Bool_2999;
    Str_delete(&self->name, hoisted__Bool_2999);
    Bool hoisted__Bool_3000 = 0;
    (void)hoisted__Bool_3000;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3000);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_3001 = 0;
    (void)hoisted__U32_3001;
    U64 hoisted__U64_3002 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3001); });
    (void)hoisted__U64_3002;
    return hoisted__U64_3002;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_3003 = 24;
    (void)hoisted__U32_3003;
    return hoisted__U32_3003;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_3005 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_3005->name = *_ca; free(_ca); }
    hoisted__ForInData_3005->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_3005->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_3005->name2 = *_ca; free(_ca); }
    hoisted__ForInData_3005->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_3005;
    return hoisted__ForInData_3005;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_3006 = 0;
    (void)hoisted__Bool_3006;
    Str_delete(&self->name, hoisted__Bool_3006);
    Bool hoisted__Bool_3007 = 0;
    (void)hoisted__Bool_3007;
    Bool_delete(&self->is_mut, hoisted__Bool_3007);
    Bool hoisted__Bool_3008 = 0;
    (void)hoisted__Bool_3008;
    Type_delete(&self->til_type, hoisted__Bool_3008);
    Bool hoisted__Bool_3009 = 0;
    (void)hoisted__Bool_3009;
    Str_delete(&self->name2, hoisted__Bool_3009);
    Bool hoisted__Bool_3010 = 0;
    (void)hoisted__Bool_3010;
    Bool_delete(&self->is_mut2, hoisted__Bool_3010);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_3011 = 0;
    (void)hoisted__U32_3011;
    U64 hoisted__U64_3012 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3011); });
    (void)hoisted__U64_3012;
    return hoisted__U64_3012;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_3013 = 72;
    (void)hoisted__U32_3013;
    return hoisted__U32_3013;
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
    U32 hoisted__U32_3056 = 1;
    (void)hoisted__U32_3056;
    Bool hoisted__Bool_3057 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3057;
    if (hoisted__Bool_3057) {
        Str *hoisted__Str_3050 = get_payload(self);
        (void)hoisted__Str_3050;
        (void)hoisted__Str_3050;
        Bool hoisted__Bool_3051 = 0;
        (void)hoisted__Bool_3051;
        Str_delete(hoisted__Str_3050, hoisted__Bool_3051);
    }
    U32 hoisted__U32_3058 = 1;
    (void)hoisted__U32_3058;
    Bool hoisted__Bool_3059 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3059;
    if (hoisted__Bool_3059) {
        LiteralNumData *hoisted__LiteralNumData_3052 = get_payload(self);
        (void)hoisted__LiteralNumData_3052;
        (void)hoisted__LiteralNumData_3052;
        Bool hoisted__Bool_3053 = 0;
        (void)hoisted__Bool_3053;
        LiteralNumData_delete(hoisted__LiteralNumData_3052, hoisted__Bool_3053);
    }
    U32 hoisted__U32_3060 = 1;
    (void)hoisted__U32_3060;
    Bool hoisted__Bool_3061 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3061;
    if (hoisted__Bool_3061) {
        Bool *hoisted__Bool_3054 = get_payload(self);
        (void)hoisted__Bool_3054;
        (void)hoisted__Bool_3054;
        Bool hoisted__Bool_3055 = 0;
        (void)hoisted__Bool_3055;
        Bool_delete(hoisted__Bool_3054, hoisted__Bool_3055);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_3116 = 1;
    (void)hoisted__U32_3116;
    Bool hoisted__Bool_3117 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3117;
    if (hoisted__Bool_3117) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3111 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3111;
        Literal *hoisted__Literal_3112 = Literal_Str(hoisted__Str_3111);
        (void)hoisted__Literal_3112;
        { Literal * _ret_val = hoisted__Literal_3112;
                return _ret_val; }
    }
    U32 hoisted__U32_3118 = 1;
    (void)hoisted__U32_3118;
    Bool hoisted__Bool_3119 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3119;
    if (hoisted__Bool_3119) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3113 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3113;
        Literal *hoisted__Literal_3114 = Literal_Num(hoisted__LiteralNumData_3113);
        (void)hoisted__Literal_3114;
        { Literal * _ret_val = hoisted__Literal_3114;
                return _ret_val; }
    }
    U32 hoisted__U32_3120 = 1;
    (void)hoisted__U32_3120;
    Bool hoisted__Bool_3121 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3121;
    if (hoisted__Bool_3121) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3115 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3115;
        { Literal * _ret_val = hoisted__Literal_3115;
                return _ret_val; }
    }
    U32 hoisted__U32_3122 = 1;
    (void)hoisted__U32_3122;
    Bool hoisted__Bool_3123 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_3123;
    if (hoisted__Bool_3123) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U32 hoisted__U32_3124 = 1;
    (void)hoisted__U32_3124;
    Bool hoisted__Bool_3125 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_3125;
    if (hoisted__Bool_3125) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3126 = 48;
    (void)hoisted__U32_3126;
    return hoisted__U32_3126;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3129 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3129->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3129->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3129;
    return hoisted__MatchData_3129;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3130 = 0;
    (void)hoisted__Bool_3130;
    Type_delete(&self->til_type, hoisted__Bool_3130);
    Bool hoisted__Bool_3131 = 0;
    (void)hoisted__Bool_3131;
    Str_delete(&self->result_temp, hoisted__Bool_3131);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3132 = 0;
    (void)hoisted__U32_3132;
    U64 hoisted__U64_3133 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3132); });
    (void)hoisted__U64_3133;
    return hoisted__U64_3133;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3134 = 40;
    (void)hoisted__U32_3134;
    return hoisted__U32_3134;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3139 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3139->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3139->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3139;
    return hoisted__CaptureBlockData_3139;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3140 = 0;
    (void)hoisted__Bool_3140;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3140);
    Bool hoisted__Bool_3141 = 0;
    (void)hoisted__Bool_3141;
    Str_delete(&self->closure_name, hoisted__Bool_3141);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3142 = 0;
    (void)hoisted__U32_3142;
    U64 hoisted__U64_3143 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3142); });
    (void)hoisted__U64_3143;
    return hoisted__U64_3143;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3144 = 32;
    (void)hoisted__U32_3144;
    return hoisted__U32_3144;
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
    U32 hoisted__U32_3405 = 1;
    (void)hoisted__U32_3405;
    Bool hoisted__Bool_3406 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3406;
    if (hoisted__Bool_3406) {
        Literal *hoisted__Literal_3375 = get_payload(self);
        (void)hoisted__Literal_3375;
        (void)hoisted__Literal_3375;
        Bool hoisted__Bool_3376 = 0;
        (void)hoisted__Bool_3376;
        Literal_delete(hoisted__Literal_3375, hoisted__Bool_3376);
    }
    U32 hoisted__U32_3407 = 1;
    (void)hoisted__U32_3407;
    Bool hoisted__Bool_3408 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3408;
    if (hoisted__Bool_3408) {
        IdentData *hoisted__IdentData_3377 = get_payload(self);
        (void)hoisted__IdentData_3377;
        (void)hoisted__IdentData_3377;
        Bool hoisted__Bool_3378 = 0;
        (void)hoisted__Bool_3378;
        IdentData_delete(hoisted__IdentData_3377, hoisted__Bool_3378);
    }
    U32 hoisted__U32_3409 = 1;
    (void)hoisted__U32_3409;
    Bool hoisted__Bool_3410 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3410;
    if (hoisted__Bool_3410) {
        Declaration *hoisted__Declaration_3379 = get_payload(self);
        (void)hoisted__Declaration_3379;
        (void)hoisted__Declaration_3379;
        Bool hoisted__Bool_3380 = 0;
        (void)hoisted__Bool_3380;
        Declaration_delete(hoisted__Declaration_3379, hoisted__Bool_3380);
    }
    U32 hoisted__U32_3411 = 1;
    (void)hoisted__U32_3411;
    Bool hoisted__Bool_3412 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3412;
    if (hoisted__Bool_3412) {
        AssignData *hoisted__AssignData_3381 = get_payload(self);
        (void)hoisted__AssignData_3381;
        (void)hoisted__AssignData_3381;
        Bool hoisted__Bool_3382 = 0;
        (void)hoisted__Bool_3382;
        AssignData_delete(hoisted__AssignData_3381, hoisted__Bool_3382);
    }
    U32 hoisted__U32_3413 = 1;
    (void)hoisted__U32_3413;
    Bool hoisted__Bool_3414 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3414;
    if (hoisted__Bool_3414) {
        FCallData *hoisted__FCallData_3383 = get_payload(self);
        (void)hoisted__FCallData_3383;
        (void)hoisted__FCallData_3383;
        Bool hoisted__Bool_3384 = 0;
        (void)hoisted__Bool_3384;
        FCallData_delete(hoisted__FCallData_3383, hoisted__Bool_3384);
    }
    U32 hoisted__U32_3415 = 1;
    (void)hoisted__U32_3415;
    Bool hoisted__Bool_3416 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        FunctionDef *hoisted__FunctionDef_3385 = get_payload(self);
        (void)hoisted__FunctionDef_3385;
        (void)hoisted__FunctionDef_3385;
        Bool hoisted__Bool_3386 = 0;
        (void)hoisted__Bool_3386;
        FunctionDef_delete(hoisted__FunctionDef_3385, hoisted__Bool_3386);
    }
    U32 hoisted__U32_3417 = 1;
    (void)hoisted__U32_3417;
    Bool hoisted__Bool_3418 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        StructDef *hoisted__StructDef_3387 = get_payload(self);
        (void)hoisted__StructDef_3387;
        (void)hoisted__StructDef_3387;
        Bool hoisted__Bool_3388 = 0;
        (void)hoisted__Bool_3388;
        StructDef_delete(hoisted__StructDef_3387, hoisted__Bool_3388);
    }
    U32 hoisted__U32_3419 = 1;
    (void)hoisted__U32_3419;
    Bool hoisted__Bool_3420 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        EnumDef *hoisted__EnumDef_3389 = get_payload(self);
        (void)hoisted__EnumDef_3389;
        (void)hoisted__EnumDef_3389;
        Bool hoisted__Bool_3390 = 0;
        (void)hoisted__Bool_3390;
        EnumDef_delete(hoisted__EnumDef_3389, hoisted__Bool_3390);
    }
    U32 hoisted__U32_3421 = 1;
    (void)hoisted__U32_3421;
    Bool hoisted__Bool_3422 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3422;
    if (hoisted__Bool_3422) {
        FieldAccessData *hoisted__FieldAccessData_3391 = get_payload(self);
        (void)hoisted__FieldAccessData_3391;
        (void)hoisted__FieldAccessData_3391;
        Bool hoisted__Bool_3392 = 0;
        (void)hoisted__Bool_3392;
        FieldAccessData_delete(hoisted__FieldAccessData_3391, hoisted__Bool_3392);
    }
    U32 hoisted__U32_3423 = 1;
    (void)hoisted__U32_3423;
    Bool hoisted__Bool_3424 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3424;
    if (hoisted__Bool_3424) {
        FieldAssignData *hoisted__FieldAssignData_3393 = get_payload(self);
        (void)hoisted__FieldAssignData_3393;
        (void)hoisted__FieldAssignData_3393;
        Bool hoisted__Bool_3394 = 0;
        (void)hoisted__Bool_3394;
        FieldAssignData_delete(hoisted__FieldAssignData_3393, hoisted__Bool_3394);
    }
    U32 hoisted__U32_3425 = 1;
    (void)hoisted__U32_3425;
    Bool hoisted__Bool_3426 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3426;
    if (hoisted__Bool_3426) {
        ForInData *hoisted__ForInData_3395 = get_payload(self);
        (void)hoisted__ForInData_3395;
        (void)hoisted__ForInData_3395;
        Bool hoisted__Bool_3396 = 0;
        (void)hoisted__Bool_3396;
        ForInData_delete(hoisted__ForInData_3395, hoisted__Bool_3396);
    }
    U32 hoisted__U32_3427 = 1;
    (void)hoisted__U32_3427;
    Bool hoisted__Bool_3428 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3428;
    if (hoisted__Bool_3428) {
        Str *hoisted__Str_3397 = get_payload(self);
        (void)hoisted__Str_3397;
        (void)hoisted__Str_3397;
        Bool hoisted__Bool_3398 = 0;
        (void)hoisted__Bool_3398;
        Str_delete(hoisted__Str_3397, hoisted__Bool_3398);
    }
    U32 hoisted__U32_3429 = 1;
    (void)hoisted__U32_3429;
    Bool hoisted__Bool_3430 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3430;
    if (hoisted__Bool_3430) {
        MatchData *hoisted__MatchData_3399 = get_payload(self);
        (void)hoisted__MatchData_3399;
        (void)hoisted__MatchData_3399;
        Bool hoisted__Bool_3400 = 0;
        (void)hoisted__Bool_3400;
        MatchData_delete(hoisted__MatchData_3399, hoisted__Bool_3400);
    }
    U32 hoisted__U32_3431 = 1;
    (void)hoisted__U32_3431;
    Bool hoisted__Bool_3432 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3432;
    if (hoisted__Bool_3432) {
        CaptureBlockData *hoisted__CaptureBlockData_3401 = get_payload(self);
        (void)hoisted__CaptureBlockData_3401;
        (void)hoisted__CaptureBlockData_3401;
        Bool hoisted__Bool_3402 = 0;
        (void)hoisted__Bool_3402;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3401, hoisted__Bool_3402);
    }
    U32 hoisted__U32_3433 = 1;
    (void)hoisted__U32_3433;
    Bool hoisted__Bool_3434 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3434;
    if (hoisted__Bool_3434) {
        CaptureBlockData *hoisted__CaptureBlockData_3403 = get_payload(self);
        (void)hoisted__CaptureBlockData_3403;
        (void)hoisted__CaptureBlockData_3403;
        Bool hoisted__Bool_3404 = 0;
        (void)hoisted__Bool_3404;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3403, hoisted__Bool_3404);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3698 = 1;
    (void)hoisted__U32_3698;
    Bool hoisted__Bool_3699 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3699;
    if (hoisted__Bool_3699) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U32 hoisted__U32_3700 = 1;
    (void)hoisted__U32_3700;
    Bool hoisted__Bool_3701 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3701;
    if (hoisted__Bool_3701) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3670 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3670;
        NodeType *hoisted__NodeType_3671 = NodeType_Literal(hoisted__Literal_3670);
        (void)hoisted__NodeType_3671;
        { NodeType * _ret_val = hoisted__NodeType_3671;
                return _ret_val; }
    }
    U32 hoisted__U32_3702 = 1;
    (void)hoisted__U32_3702;
    Bool hoisted__Bool_3703 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3703;
    if (hoisted__Bool_3703) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3672 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3672;
        NodeType *hoisted__NodeType_3673 = NodeType_Ident(hoisted__IdentData_3672);
        (void)hoisted__NodeType_3673;
        { NodeType * _ret_val = hoisted__NodeType_3673;
                return _ret_val; }
    }
    U32 hoisted__U32_3704 = 1;
    (void)hoisted__U32_3704;
    Bool hoisted__Bool_3705 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3705;
    if (hoisted__Bool_3705) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3674 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3674;
        NodeType *hoisted__NodeType_3675 = NodeType_Decl(hoisted__Declaration_3674);
        (void)hoisted__NodeType_3675;
        { NodeType * _ret_val = hoisted__NodeType_3675;
                return _ret_val; }
    }
    U32 hoisted__U32_3706 = 1;
    (void)hoisted__U32_3706;
    Bool hoisted__Bool_3707 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3707;
    if (hoisted__Bool_3707) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3676 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3676;
        NodeType *hoisted__NodeType_3677 = NodeType_Assign(hoisted__AssignData_3676);
        (void)hoisted__NodeType_3677;
        { NodeType * _ret_val = hoisted__NodeType_3677;
                return _ret_val; }
    }
    U32 hoisted__U32_3708 = 1;
    (void)hoisted__U32_3708;
    Bool hoisted__Bool_3709 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3709;
    if (hoisted__Bool_3709) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3678 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3678;
        NodeType *hoisted__NodeType_3679 = NodeType_FCall(hoisted__FCallData_3678);
        (void)hoisted__NodeType_3679;
        { NodeType * _ret_val = hoisted__NodeType_3679;
                return _ret_val; }
    }
    U32 hoisted__U32_3710 = 1;
    (void)hoisted__U32_3710;
    Bool hoisted__Bool_3711 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3711;
    if (hoisted__Bool_3711) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3680 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3680;
        NodeType *hoisted__NodeType_3681 = NodeType_FuncDef(hoisted__FunctionDef_3680);
        (void)hoisted__NodeType_3681;
        { NodeType * _ret_val = hoisted__NodeType_3681;
                return _ret_val; }
    }
    U32 hoisted__U32_3712 = 1;
    (void)hoisted__U32_3712;
    Bool hoisted__Bool_3713 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3713;
    if (hoisted__Bool_3713) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3682 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3682;
        NodeType *hoisted__NodeType_3683 = NodeType_StructDef(hoisted__StructDef_3682);
        (void)hoisted__NodeType_3683;
        { NodeType * _ret_val = hoisted__NodeType_3683;
                return _ret_val; }
    }
    U32 hoisted__U32_3714 = 1;
    (void)hoisted__U32_3714;
    Bool hoisted__Bool_3715 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3715;
    if (hoisted__Bool_3715) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3684 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3684;
        NodeType *hoisted__NodeType_3685 = NodeType_EnumDef(hoisted__EnumDef_3684);
        (void)hoisted__NodeType_3685;
        { NodeType * _ret_val = hoisted__NodeType_3685;
                return _ret_val; }
    }
    U32 hoisted__U32_3716 = 1;
    (void)hoisted__U32_3716;
    Bool hoisted__Bool_3717 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3717;
    if (hoisted__Bool_3717) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3686 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3686;
        NodeType *hoisted__NodeType_3687 = NodeType_FieldAccess(hoisted__FieldAccessData_3686);
        (void)hoisted__NodeType_3687;
        { NodeType * _ret_val = hoisted__NodeType_3687;
                return _ret_val; }
    }
    U32 hoisted__U32_3718 = 1;
    (void)hoisted__U32_3718;
    Bool hoisted__Bool_3719 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3719;
    if (hoisted__Bool_3719) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3688 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3688;
        NodeType *hoisted__NodeType_3689 = NodeType_FieldAssign(hoisted__FieldAssignData_3688);
        (void)hoisted__NodeType_3689;
        { NodeType * _ret_val = hoisted__NodeType_3689;
                return _ret_val; }
    }
    U32 hoisted__U32_3720 = 1;
    (void)hoisted__U32_3720;
    Bool hoisted__Bool_3721 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3721;
    if (hoisted__Bool_3721) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U32 hoisted__U32_3722 = 1;
    (void)hoisted__U32_3722;
    Bool hoisted__Bool_3723 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3723;
    if (hoisted__Bool_3723) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U32 hoisted__U32_3724 = 1;
    (void)hoisted__U32_3724;
    Bool hoisted__Bool_3725 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3725;
    if (hoisted__Bool_3725) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U32 hoisted__U32_3726 = 1;
    (void)hoisted__U32_3726;
    Bool hoisted__Bool_3727 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3727;
    if (hoisted__Bool_3727) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3690 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3690;
        NodeType *hoisted__NodeType_3691 = NodeType_ForIn(hoisted__ForInData_3690);
        (void)hoisted__NodeType_3691;
        { NodeType * _ret_val = hoisted__NodeType_3691;
                return _ret_val; }
    }
    U32 hoisted__U32_3728 = 1;
    (void)hoisted__U32_3728;
    Bool hoisted__Bool_3729 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3729;
    if (hoisted__Bool_3729) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3692 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3692;
        NodeType *hoisted__NodeType_3693 = NodeType_NamedArg(hoisted__Str_3692);
        (void)hoisted__NodeType_3693;
        { NodeType * _ret_val = hoisted__NodeType_3693;
                return _ret_val; }
    }
    U32 hoisted__U32_3730 = 1;
    (void)hoisted__U32_3730;
    Bool hoisted__Bool_3731 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3731;
    if (hoisted__Bool_3731) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U32 hoisted__U32_3732 = 1;
    (void)hoisted__U32_3732;
    Bool hoisted__Bool_3733 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3733;
    if (hoisted__Bool_3733) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U32 hoisted__U32_3734 = 1;
    (void)hoisted__U32_3734;
    Bool hoisted__Bool_3735 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3735;
    if (hoisted__Bool_3735) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U32 hoisted__U32_3736 = 1;
    (void)hoisted__U32_3736;
    Bool hoisted__Bool_3737 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3737;
    if (hoisted__Bool_3737) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3694 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3694;
        NodeType *hoisted__NodeType_3695 = NodeType_Match(hoisted__MatchData_3694);
        (void)hoisted__NodeType_3695;
        { NodeType * _ret_val = hoisted__NodeType_3695;
                return _ret_val; }
    }
    U32 hoisted__U32_3738 = 1;
    (void)hoisted__U32_3738;
    Bool hoisted__Bool_3739 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3739;
    if (hoisted__Bool_3739) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U32 hoisted__U32_3740 = 1;
    (void)hoisted__U32_3740;
    Bool hoisted__Bool_3741 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3741;
    if (hoisted__Bool_3741) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U32 hoisted__U32_3742 = 1;
    (void)hoisted__U32_3742;
    Bool hoisted__Bool_3743 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3743;
    if (hoisted__Bool_3743) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U32 hoisted__U32_3744 = 1;
    (void)hoisted__U32_3744;
    Bool hoisted__Bool_3745 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3745;
    if (hoisted__Bool_3745) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U32 hoisted__U32_3746 = 1;
    (void)hoisted__U32_3746;
    Bool hoisted__Bool_3747 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3747;
    if (hoisted__Bool_3747) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U32 hoisted__U32_3748 = 1;
    (void)hoisted__U32_3748;
    Bool hoisted__Bool_3749 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3749;
    if (hoisted__Bool_3749) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3696 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3696;
        NodeType *hoisted__NodeType_3697 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3696);
        (void)hoisted__NodeType_3697;
        { NodeType * _ret_val = hoisted__NodeType_3697;
                return _ret_val; }
    }
    U32 hoisted__U32_3750 = 1;
    (void)hoisted__U32_3750;
    Bool hoisted__Bool_3751 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3751;
    if (hoisted__Bool_3751) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    CaptureBlockData *_clone_payload_BodyValue_27 = get_payload(self);
    (void)_clone_payload_BodyValue_27;
    (void)_clone_payload_BodyValue_27;
    CaptureBlockData *hoisted__CaptureBlockData_3752 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
    (void)hoisted__CaptureBlockData_3752;
    NodeType *hoisted__NodeType_3753 = NodeType_BodyValue(hoisted__CaptureBlockData_3752);
    (void)hoisted__NodeType_3753;
    return hoisted__NodeType_3753;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3754 = 136;
    (void)hoisted__U32_3754;
    return hoisted__U32_3754;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3755 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3755;
    if (hoisted__Bool_3755) {
        return;
    }
    Bool hoisted__Bool_3756 = 0;
    (void)hoisted__Bool_3756;
    NodeType_delete(&self->node_type, hoisted__Bool_3756);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3806 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3806->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3806->children = *_ca; free(_ca); }
    hoisted__Expr_3806->line = line;
    hoisted__Expr_3806->col = col;
    (void)hoisted__Expr_3806;
    return hoisted__Expr_3806;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3815 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3815->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3815->children = *_ca; free(_ca); }
    hoisted__Expr_3815->line = self->line;
    hoisted__Expr_3815->col = self->col;
    (void)hoisted__Expr_3815;
    return hoisted__Expr_3815;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3816 = 0;
    (void)hoisted__U32_3816;
    U64 hoisted__U64_3817 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3816); });
    (void)hoisted__U64_3817;
    return hoisted__U64_3817;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3818 = 160;
    (void)hoisted__U32_3818;
    return hoisted__U32_3818;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4902 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4902->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4902->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4902;
    return hoisted__Map__I64_Str_4902;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_5015 = 0;
    (void)hoisted__Bool_5015;
    Vec__I64_delete(&self->keys, hoisted__Bool_5015);
    Bool hoisted__Bool_5016 = 0;
    (void)hoisted__Bool_5016;
    Vec__Str_delete(&self->values, hoisted__Bool_5016);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_5017 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_5017->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_5017->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_5017;
    return hoisted__Map__I64_Str_5017;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_5018 = 0;
    (void)hoisted__U32_5018;
    U64 hoisted__U64_5019 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5018); });
    (void)hoisted__U64_5019;
    return hoisted__U64_5019;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_5020 = 32;
    (void)hoisted__U32_5020;
    return hoisted__U32_5020;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_5021 = 1;
    (void)hoisted__U32_5021;
    U64 hoisted__U64_5022 = (U64)(hoisted__U32_5021);
    (void)hoisted__U64_5022;
    void * hoisted__v_5023 = malloc(hoisted__U64_5022);
    (void)hoisted__v_5023;
    U32 hoisted__U32_5024 = 0;
    (void)hoisted__U32_5024;
    I64 hoisted__I64_5025 = 1;
    (void)hoisted__I64_5025;
    Vec__Bool *hoisted__Vec__Bool_5026 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5026->data = hoisted__v_5023;
    hoisted__Vec__Bool_5026->count = hoisted__U32_5024;
    hoisted__Vec__Bool_5026->cap = hoisted__I64_5025;
    (void)hoisted__Vec__Bool_5026;
    return hoisted__Vec__Bool_5026;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_5036 = self->count;
        (void)_re_U32_5036;
        U32 _rc_U32_5036 = 0;
        (void)_rc_U32_5036;
        Bool hoisted__Bool_5049 = ((Bool)(_rc_U32_5036 <= _re_U32_5036));
        (void)hoisted__Bool_5049;
        if (hoisted__Bool_5049) {
            while (1) {
                Bool _wcond_Bool_5037 = ((Bool)(_rc_U32_5036 < _re_U32_5036));
                (void)_wcond_Bool_5037;
                if (_wcond_Bool_5037) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5036);
                U32_inc(&_rc_U32_5036);
                U32 hoisted__U32_5038 = 1;
                (void)hoisted__U32_5038;
                U32 hoisted__U32_5039 = ((U32)(i * hoisted__U32_5038));
                (void)hoisted__U32_5039;
                U64 hoisted__U64_5040 = (U64)(hoisted__U32_5039);
                (void)hoisted__U64_5040;
                Bool *hoisted__Bool_5041 = ptr_add(self->data, hoisted__U64_5040);
                (void)hoisted__Bool_5041;
                (void)hoisted__Bool_5041;
                Bool hoisted__Bool_5042 = 0;
                (void)hoisted__Bool_5042;
                Bool_delete(hoisted__Bool_5041, hoisted__Bool_5042);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5043 = ((Bool)(_rc_U32_5036 > _re_U32_5036));
                (void)_wcond_Bool_5043;
                if (_wcond_Bool_5043) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5036);
                U32_dec(&_rc_U32_5036);
                U32 hoisted__U32_5044 = 1;
                (void)hoisted__U32_5044;
                U32 hoisted__U32_5045 = ((U32)(i * hoisted__U32_5044));
                (void)hoisted__U32_5045;
                U64 hoisted__U64_5046 = (U64)(hoisted__U32_5045);
                (void)hoisted__U64_5046;
                Bool *hoisted__Bool_5047 = ptr_add(self->data, hoisted__U64_5046);
                (void)hoisted__Bool_5047;
                (void)hoisted__Bool_5047;
                Bool hoisted__Bool_5048 = 0;
                (void)hoisted__Bool_5048;
                Bool_delete(hoisted__Bool_5047, hoisted__Bool_5048);
            }
        }
    }
    U32 hoisted__U32_5050 = 0;
    (void)hoisted__U32_5050;
    self->count = hoisted__U32_5050;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_5320 = 1;
    (void)hoisted__U32_5320;
    U32 hoisted__U32_5321 = ((U32)(self->cap * hoisted__U32_5320));
    (void)hoisted__U32_5321;
    U64 hoisted__U64_5322 = (U64)(hoisted__U32_5321);
    (void)hoisted__U64_5322;
    void * new_data = malloc(hoisted__U64_5322);
    {
        U32 _re_U32_5292 = self->count;
        (void)_re_U32_5292;
        U32 _rc_U32_5292 = 0;
        (void)_rc_U32_5292;
        Bool hoisted__Bool_5319 = ((Bool)(_rc_U32_5292 <= _re_U32_5292));
        (void)hoisted__Bool_5319;
        if (hoisted__Bool_5319) {
            while (1) {
                Bool _wcond_Bool_5293 = ((Bool)(_rc_U32_5292 < _re_U32_5292));
                (void)_wcond_Bool_5293;
                if (_wcond_Bool_5293) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5292);
                U32_inc(&_rc_U32_5292);
                U32 hoisted__U32_5294 = 1;
                (void)hoisted__U32_5294;
                U32 hoisted__U32_5295 = ((U32)(i * hoisted__U32_5294));
                (void)hoisted__U32_5295;
                U64 hoisted__U64_5296 = (U64)(hoisted__U32_5295);
                (void)hoisted__U64_5296;
                Bool *src = ptr_add(self->data, hoisted__U64_5296);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_5297 = 1;
                (void)hoisted__U32_5297;
                U32 hoisted__U32_5298 = ((U32)(i * hoisted__U32_5297));
                (void)hoisted__U32_5298;
                U64 hoisted__U64_5299 = (U64)(hoisted__U32_5298);
                (void)hoisted__U64_5299;
                U32 hoisted__U32_5300 = 1;
                (void)hoisted__U32_5300;
                void *hoisted__v_5301 = ptr_add(new_data, hoisted__U64_5299);
                (void)hoisted__v_5301;
                (void)hoisted__v_5301;
                U64 hoisted__U64_5302 = (U64)(hoisted__U32_5300);
                (void)hoisted__U64_5302;
                memcpy(hoisted__v_5301, &cloned, hoisted__U64_5302);
                U32 hoisted__U32_5303 = 1;
                (void)hoisted__U32_5303;
                I32 hoisted__I32_5304 = 0;
                (void)hoisted__I32_5304;
                U64 hoisted__U64_5305 = (U64)(hoisted__U32_5303);
                (void)hoisted__U64_5305;
                memset(&cloned, hoisted__I32_5304, hoisted__U64_5305);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5306 = ((Bool)(_rc_U32_5292 > _re_U32_5292));
                (void)_wcond_Bool_5306;
                if (_wcond_Bool_5306) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5292);
                U32_dec(&_rc_U32_5292);
                U32 hoisted__U32_5307 = 1;
                (void)hoisted__U32_5307;
                U32 hoisted__U32_5308 = ((U32)(i * hoisted__U32_5307));
                (void)hoisted__U32_5308;
                U64 hoisted__U64_5309 = (U64)(hoisted__U32_5308);
                (void)hoisted__U64_5309;
                Bool *src = ptr_add(self->data, hoisted__U64_5309);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_5310 = 1;
                (void)hoisted__U32_5310;
                U32 hoisted__U32_5311 = ((U32)(i * hoisted__U32_5310));
                (void)hoisted__U32_5311;
                U64 hoisted__U64_5312 = (U64)(hoisted__U32_5311);
                (void)hoisted__U64_5312;
                U32 hoisted__U32_5313 = 1;
                (void)hoisted__U32_5313;
                void *hoisted__v_5314 = ptr_add(new_data, hoisted__U64_5312);
                (void)hoisted__v_5314;
                (void)hoisted__v_5314;
                U64 hoisted__U64_5315 = (U64)(hoisted__U32_5313);
                (void)hoisted__U64_5315;
                memcpy(hoisted__v_5314, &cloned, hoisted__U64_5315);
                U32 hoisted__U32_5316 = 1;
                (void)hoisted__U32_5316;
                I32 hoisted__I32_5317 = 0;
                (void)hoisted__I32_5317;
                U64 hoisted__U64_5318 = (U64)(hoisted__U32_5316);
                (void)hoisted__U64_5318;
                memset(&cloned, hoisted__I32_5317, hoisted__U64_5318);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5323 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5323->data = new_data;
    hoisted__Vec__Bool_5323->count = self->count;
    hoisted__Vec__Bool_5323->cap = self->cap;
    (void)hoisted__Vec__Bool_5323;
    return hoisted__Vec__Bool_5323;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_5324 = 16;
    (void)hoisted__U32_5324;
    return hoisted__U32_5324;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5325 = 8;
    (void)hoisted__U32_5325;
    U64 hoisted__U64_5326 = (U64)(hoisted__U32_5325);
    (void)hoisted__U64_5326;
    void * hoisted__v_5327 = malloc(hoisted__U64_5326);
    (void)hoisted__v_5327;
    U32 hoisted__U32_5328 = 0;
    (void)hoisted__U32_5328;
    I64 hoisted__I64_5329 = 1;
    (void)hoisted__I64_5329;
    Vec__I64 *hoisted__Vec__I64_5330 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5330->data = hoisted__v_5327;
    hoisted__Vec__I64_5330->count = hoisted__U32_5328;
    hoisted__Vec__I64_5330->cap = hoisted__I64_5329;
    (void)hoisted__Vec__I64_5330;
    return hoisted__Vec__I64_5330;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5340 = self->count;
        (void)_re_U32_5340;
        U32 _rc_U32_5340 = 0;
        (void)_rc_U32_5340;
        Bool hoisted__Bool_5353 = ((Bool)(_rc_U32_5340 <= _re_U32_5340));
        (void)hoisted__Bool_5353;
        if (hoisted__Bool_5353) {
            while (1) {
                Bool _wcond_Bool_5341 = ((Bool)(_rc_U32_5340 < _re_U32_5340));
                (void)_wcond_Bool_5341;
                if (_wcond_Bool_5341) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5340);
                U32_inc(&_rc_U32_5340);
                U32 hoisted__U32_5342 = 8;
                (void)hoisted__U32_5342;
                U32 hoisted__U32_5343 = ((U32)(i * hoisted__U32_5342));
                (void)hoisted__U32_5343;
                U64 hoisted__U64_5344 = (U64)(hoisted__U32_5343);
                (void)hoisted__U64_5344;
                I64 *hoisted__I64_5345 = ptr_add(self->data, hoisted__U64_5344);
                (void)hoisted__I64_5345;
                (void)hoisted__I64_5345;
                Bool hoisted__Bool_5346 = 0;
                (void)hoisted__Bool_5346;
                I64_delete(hoisted__I64_5345, hoisted__Bool_5346);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5347 = ((Bool)(_rc_U32_5340 > _re_U32_5340));
                (void)_wcond_Bool_5347;
                if (_wcond_Bool_5347) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5340);
                U32_dec(&_rc_U32_5340);
                U32 hoisted__U32_5348 = 8;
                (void)hoisted__U32_5348;
                U32 hoisted__U32_5349 = ((U32)(i * hoisted__U32_5348));
                (void)hoisted__U32_5349;
                U64 hoisted__U64_5350 = (U64)(hoisted__U32_5349);
                (void)hoisted__U64_5350;
                I64 *hoisted__I64_5351 = ptr_add(self->data, hoisted__U64_5350);
                (void)hoisted__I64_5351;
                (void)hoisted__I64_5351;
                Bool hoisted__Bool_5352 = 0;
                (void)hoisted__Bool_5352;
                I64_delete(hoisted__I64_5351, hoisted__Bool_5352);
            }
        }
    }
    U32 hoisted__U32_5354 = 0;
    (void)hoisted__U32_5354;
    self->count = hoisted__U32_5354;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5624 = 8;
    (void)hoisted__U32_5624;
    U32 hoisted__U32_5625 = ((U32)(self->cap * hoisted__U32_5624));
    (void)hoisted__U32_5625;
    U64 hoisted__U64_5626 = (U64)(hoisted__U32_5625);
    (void)hoisted__U64_5626;
    void * new_data = malloc(hoisted__U64_5626);
    {
        U32 _re_U32_5596 = self->count;
        (void)_re_U32_5596;
        U32 _rc_U32_5596 = 0;
        (void)_rc_U32_5596;
        Bool hoisted__Bool_5623 = ((Bool)(_rc_U32_5596 <= _re_U32_5596));
        (void)hoisted__Bool_5623;
        if (hoisted__Bool_5623) {
            while (1) {
                Bool _wcond_Bool_5597 = ((Bool)(_rc_U32_5596 < _re_U32_5596));
                (void)_wcond_Bool_5597;
                if (_wcond_Bool_5597) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5596);
                U32_inc(&_rc_U32_5596);
                U32 hoisted__U32_5598 = 8;
                (void)hoisted__U32_5598;
                U32 hoisted__U32_5599 = ((U32)(i * hoisted__U32_5598));
                (void)hoisted__U32_5599;
                U64 hoisted__U64_5600 = (U64)(hoisted__U32_5599);
                (void)hoisted__U64_5600;
                I64 *src = ptr_add(self->data, hoisted__U64_5600);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5601 = 8;
                (void)hoisted__U32_5601;
                U32 hoisted__U32_5602 = ((U32)(i * hoisted__U32_5601));
                (void)hoisted__U32_5602;
                U64 hoisted__U64_5603 = (U64)(hoisted__U32_5602);
                (void)hoisted__U64_5603;
                U32 hoisted__U32_5604 = 8;
                (void)hoisted__U32_5604;
                void *hoisted__v_5605 = ptr_add(new_data, hoisted__U64_5603);
                (void)hoisted__v_5605;
                (void)hoisted__v_5605;
                U64 hoisted__U64_5606 = (U64)(hoisted__U32_5604);
                (void)hoisted__U64_5606;
                memcpy(hoisted__v_5605, &cloned, hoisted__U64_5606);
                U32 hoisted__U32_5607 = 8;
                (void)hoisted__U32_5607;
                I32 hoisted__I32_5608 = 0;
                (void)hoisted__I32_5608;
                U64 hoisted__U64_5609 = (U64)(hoisted__U32_5607);
                (void)hoisted__U64_5609;
                memset(&cloned, hoisted__I32_5608, hoisted__U64_5609);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5610 = ((Bool)(_rc_U32_5596 > _re_U32_5596));
                (void)_wcond_Bool_5610;
                if (_wcond_Bool_5610) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5596);
                U32_dec(&_rc_U32_5596);
                U32 hoisted__U32_5611 = 8;
                (void)hoisted__U32_5611;
                U32 hoisted__U32_5612 = ((U32)(i * hoisted__U32_5611));
                (void)hoisted__U32_5612;
                U64 hoisted__U64_5613 = (U64)(hoisted__U32_5612);
                (void)hoisted__U64_5613;
                I64 *src = ptr_add(self->data, hoisted__U64_5613);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5614 = 8;
                (void)hoisted__U32_5614;
                U32 hoisted__U32_5615 = ((U32)(i * hoisted__U32_5614));
                (void)hoisted__U32_5615;
                U64 hoisted__U64_5616 = (U64)(hoisted__U32_5615);
                (void)hoisted__U64_5616;
                U32 hoisted__U32_5617 = 8;
                (void)hoisted__U32_5617;
                void *hoisted__v_5618 = ptr_add(new_data, hoisted__U64_5616);
                (void)hoisted__v_5618;
                (void)hoisted__v_5618;
                U64 hoisted__U64_5619 = (U64)(hoisted__U32_5617);
                (void)hoisted__U64_5619;
                memcpy(hoisted__v_5618, &cloned, hoisted__U64_5619);
                U32 hoisted__U32_5620 = 8;
                (void)hoisted__U32_5620;
                I32 hoisted__I32_5621 = 0;
                (void)hoisted__I32_5621;
                U64 hoisted__U64_5622 = (U64)(hoisted__U32_5620);
                (void)hoisted__U64_5622;
                memset(&cloned, hoisted__I32_5621, hoisted__U64_5622);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5627 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5627->data = new_data;
    hoisted__Vec__I64_5627->count = self->count;
    hoisted__Vec__I64_5627->cap = self->cap;
    (void)hoisted__Vec__I64_5627;
    return hoisted__Vec__I64_5627;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5628 = 16;
    (void)hoisted__U32_5628;
    return hoisted__U32_5628;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5933 = 104;
    (void)hoisted__U32_5933;
    U64 hoisted__U64_5934 = (U64)(hoisted__U32_5933);
    (void)hoisted__U64_5934;
    void * hoisted__v_5935 = malloc(hoisted__U64_5934);
    (void)hoisted__v_5935;
    U32 hoisted__U32_5936 = 0;
    (void)hoisted__U32_5936;
    I64 hoisted__I64_5937 = 1;
    (void)hoisted__I64_5937;
    Vec__Declaration *hoisted__Vec__Declaration_5938 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5938->data = hoisted__v_5935;
    hoisted__Vec__Declaration_5938->count = hoisted__U32_5936;
    hoisted__Vec__Declaration_5938->cap = hoisted__I64_5937;
    (void)hoisted__Vec__Declaration_5938;
    return hoisted__Vec__Declaration_5938;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5948 = self->count;
        (void)_re_U32_5948;
        U32 _rc_U32_5948 = 0;
        (void)_rc_U32_5948;
        Bool hoisted__Bool_5961 = ((Bool)(_rc_U32_5948 <= _re_U32_5948));
        (void)hoisted__Bool_5961;
        if (hoisted__Bool_5961) {
            while (1) {
                Bool _wcond_Bool_5949 = ((Bool)(_rc_U32_5948 < _re_U32_5948));
                (void)_wcond_Bool_5949;
                if (_wcond_Bool_5949) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5948);
                U32_inc(&_rc_U32_5948);
                U32 hoisted__U32_5950 = 104;
                (void)hoisted__U32_5950;
                U32 hoisted__U32_5951 = ((U32)(i * hoisted__U32_5950));
                (void)hoisted__U32_5951;
                U64 hoisted__U64_5952 = (U64)(hoisted__U32_5951);
                (void)hoisted__U64_5952;
                Declaration *hoisted__Declaration_5953 = ptr_add(self->data, hoisted__U64_5952);
                (void)hoisted__Declaration_5953;
                (void)hoisted__Declaration_5953;
                Bool hoisted__Bool_5954 = 0;
                (void)hoisted__Bool_5954;
                Declaration_delete(hoisted__Declaration_5953, hoisted__Bool_5954);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5955 = ((Bool)(_rc_U32_5948 > _re_U32_5948));
                (void)_wcond_Bool_5955;
                if (_wcond_Bool_5955) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5948);
                U32_dec(&_rc_U32_5948);
                U32 hoisted__U32_5956 = 104;
                (void)hoisted__U32_5956;
                U32 hoisted__U32_5957 = ((U32)(i * hoisted__U32_5956));
                (void)hoisted__U32_5957;
                U64 hoisted__U64_5958 = (U64)(hoisted__U32_5957);
                (void)hoisted__U64_5958;
                Declaration *hoisted__Declaration_5959 = ptr_add(self->data, hoisted__U64_5958);
                (void)hoisted__Declaration_5959;
                (void)hoisted__Declaration_5959;
                Bool hoisted__Bool_5960 = 0;
                (void)hoisted__Bool_5960;
                Declaration_delete(hoisted__Declaration_5959, hoisted__Bool_5960);
            }
        }
    }
    U32 hoisted__U32_5962 = 0;
    (void)hoisted__U32_5962;
    self->count = hoisted__U32_5962;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_6232 = 104;
    (void)hoisted__U32_6232;
    U32 hoisted__U32_6233 = ((U32)(self->cap * hoisted__U32_6232));
    (void)hoisted__U32_6233;
    U64 hoisted__U64_6234 = (U64)(hoisted__U32_6233);
    (void)hoisted__U64_6234;
    void * new_data = malloc(hoisted__U64_6234);
    {
        U32 _re_U32_6204 = self->count;
        (void)_re_U32_6204;
        U32 _rc_U32_6204 = 0;
        (void)_rc_U32_6204;
        Bool hoisted__Bool_6231 = ((Bool)(_rc_U32_6204 <= _re_U32_6204));
        (void)hoisted__Bool_6231;
        if (hoisted__Bool_6231) {
            while (1) {
                Bool _wcond_Bool_6205 = ((Bool)(_rc_U32_6204 < _re_U32_6204));
                (void)_wcond_Bool_6205;
                if (_wcond_Bool_6205) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6204);
                U32_inc(&_rc_U32_6204);
                U32 hoisted__U32_6206 = 104;
                (void)hoisted__U32_6206;
                U32 hoisted__U32_6207 = ((U32)(i * hoisted__U32_6206));
                (void)hoisted__U32_6207;
                U64 hoisted__U64_6208 = (U64)(hoisted__U32_6207);
                (void)hoisted__U64_6208;
                Declaration *src = ptr_add(self->data, hoisted__U64_6208);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6209 = 104;
                (void)hoisted__U32_6209;
                U32 hoisted__U32_6210 = ((U32)(i * hoisted__U32_6209));
                (void)hoisted__U32_6210;
                U64 hoisted__U64_6211 = (U64)(hoisted__U32_6210);
                (void)hoisted__U64_6211;
                U32 hoisted__U32_6212 = 104;
                (void)hoisted__U32_6212;
                void *hoisted__v_6213 = ptr_add(new_data, hoisted__U64_6211);
                (void)hoisted__v_6213;
                (void)hoisted__v_6213;
                U64 hoisted__U64_6214 = (U64)(hoisted__U32_6212);
                (void)hoisted__U64_6214;
                memcpy(hoisted__v_6213, cloned, hoisted__U64_6214);
                U32 hoisted__U32_6215 = 104;
                (void)hoisted__U32_6215;
                I32 hoisted__I32_6216 = 0;
                (void)hoisted__I32_6216;
                U64 hoisted__U64_6217 = (U64)(hoisted__U32_6215);
                (void)hoisted__U64_6217;
                memset(cloned, hoisted__I32_6216, hoisted__U64_6217);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6218 = ((Bool)(_rc_U32_6204 > _re_U32_6204));
                (void)_wcond_Bool_6218;
                if (_wcond_Bool_6218) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6204);
                U32_dec(&_rc_U32_6204);
                U32 hoisted__U32_6219 = 104;
                (void)hoisted__U32_6219;
                U32 hoisted__U32_6220 = ((U32)(i * hoisted__U32_6219));
                (void)hoisted__U32_6220;
                U64 hoisted__U64_6221 = (U64)(hoisted__U32_6220);
                (void)hoisted__U64_6221;
                Declaration *src = ptr_add(self->data, hoisted__U64_6221);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6222 = 104;
                (void)hoisted__U32_6222;
                U32 hoisted__U32_6223 = ((U32)(i * hoisted__U32_6222));
                (void)hoisted__U32_6223;
                U64 hoisted__U64_6224 = (U64)(hoisted__U32_6223);
                (void)hoisted__U64_6224;
                U32 hoisted__U32_6225 = 104;
                (void)hoisted__U32_6225;
                void *hoisted__v_6226 = ptr_add(new_data, hoisted__U64_6224);
                (void)hoisted__v_6226;
                (void)hoisted__v_6226;
                U64 hoisted__U64_6227 = (U64)(hoisted__U32_6225);
                (void)hoisted__U64_6227;
                memcpy(hoisted__v_6226, cloned, hoisted__U64_6227);
                U32 hoisted__U32_6228 = 104;
                (void)hoisted__U32_6228;
                I32 hoisted__I32_6229 = 0;
                (void)hoisted__I32_6229;
                U64 hoisted__U64_6230 = (U64)(hoisted__U32_6228);
                (void)hoisted__U64_6230;
                memset(cloned, hoisted__I32_6229, hoisted__U64_6230);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_6235 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6235->data = new_data;
    hoisted__Vec__Declaration_6235->count = self->count;
    hoisted__Vec__Declaration_6235->cap = self->cap;
    (void)hoisted__Vec__Declaration_6235;
    return hoisted__Vec__Declaration_6235;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_6236 = 16;
    (void)hoisted__U32_6236;
    return hoisted__U32_6236;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_6237 = 160;
    (void)hoisted__U32_6237;
    U64 hoisted__U64_6238 = (U64)(hoisted__U32_6237);
    (void)hoisted__U64_6238;
    void * hoisted__v_6239 = malloc(hoisted__U64_6238);
    (void)hoisted__v_6239;
    U32 hoisted__U32_6240 = 0;
    (void)hoisted__U32_6240;
    I64 hoisted__I64_6241 = 1;
    (void)hoisted__I64_6241;
    Vec__Expr *hoisted__Vec__Expr_6242 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6242->data = hoisted__v_6239;
    hoisted__Vec__Expr_6242->count = hoisted__U32_6240;
    hoisted__Vec__Expr_6242->cap = hoisted__I64_6241;
    (void)hoisted__Vec__Expr_6242;
    return hoisted__Vec__Expr_6242;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_6252 = self->count;
        (void)_re_U32_6252;
        U32 _rc_U32_6252 = 0;
        (void)_rc_U32_6252;
        Bool hoisted__Bool_6265 = ((Bool)(_rc_U32_6252 <= _re_U32_6252));
        (void)hoisted__Bool_6265;
        if (hoisted__Bool_6265) {
            while (1) {
                Bool _wcond_Bool_6253 = ((Bool)(_rc_U32_6252 < _re_U32_6252));
                (void)_wcond_Bool_6253;
                if (_wcond_Bool_6253) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6252);
                U32_inc(&_rc_U32_6252);
                U32 hoisted__U32_6254 = 160;
                (void)hoisted__U32_6254;
                U32 hoisted__U32_6255 = ((U32)(i * hoisted__U32_6254));
                (void)hoisted__U32_6255;
                U64 hoisted__U64_6256 = (U64)(hoisted__U32_6255);
                (void)hoisted__U64_6256;
                Expr *hoisted__Expr_6257 = ptr_add(self->data, hoisted__U64_6256);
                (void)hoisted__Expr_6257;
                (void)hoisted__Expr_6257;
                Bool hoisted__Bool_6258 = 0;
                (void)hoisted__Bool_6258;
                Expr_delete(hoisted__Expr_6257, hoisted__Bool_6258);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6259 = ((Bool)(_rc_U32_6252 > _re_U32_6252));
                (void)_wcond_Bool_6259;
                if (_wcond_Bool_6259) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6252);
                U32_dec(&_rc_U32_6252);
                U32 hoisted__U32_6260 = 160;
                (void)hoisted__U32_6260;
                U32 hoisted__U32_6261 = ((U32)(i * hoisted__U32_6260));
                (void)hoisted__U32_6261;
                U64 hoisted__U64_6262 = (U64)(hoisted__U32_6261);
                (void)hoisted__U64_6262;
                Expr *hoisted__Expr_6263 = ptr_add(self->data, hoisted__U64_6262);
                (void)hoisted__Expr_6263;
                (void)hoisted__Expr_6263;
                Bool hoisted__Bool_6264 = 0;
                (void)hoisted__Bool_6264;
                Expr_delete(hoisted__Expr_6263, hoisted__Bool_6264);
            }
        }
    }
    U32 hoisted__U32_6266 = 0;
    (void)hoisted__U32_6266;
    self->count = hoisted__U32_6266;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_6536 = 160;
    (void)hoisted__U32_6536;
    U32 hoisted__U32_6537 = ((U32)(self->cap * hoisted__U32_6536));
    (void)hoisted__U32_6537;
    U64 hoisted__U64_6538 = (U64)(hoisted__U32_6537);
    (void)hoisted__U64_6538;
    void * new_data = malloc(hoisted__U64_6538);
    {
        U32 _re_U32_6508 = self->count;
        (void)_re_U32_6508;
        U32 _rc_U32_6508 = 0;
        (void)_rc_U32_6508;
        Bool hoisted__Bool_6535 = ((Bool)(_rc_U32_6508 <= _re_U32_6508));
        (void)hoisted__Bool_6535;
        if (hoisted__Bool_6535) {
            while (1) {
                Bool _wcond_Bool_6509 = ((Bool)(_rc_U32_6508 < _re_U32_6508));
                (void)_wcond_Bool_6509;
                if (_wcond_Bool_6509) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6508);
                U32_inc(&_rc_U32_6508);
                U32 hoisted__U32_6510 = 160;
                (void)hoisted__U32_6510;
                U32 hoisted__U32_6511 = ((U32)(i * hoisted__U32_6510));
                (void)hoisted__U32_6511;
                U64 hoisted__U64_6512 = (U64)(hoisted__U32_6511);
                (void)hoisted__U64_6512;
                Expr *src = ptr_add(self->data, hoisted__U64_6512);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6513 = 160;
                (void)hoisted__U32_6513;
                U32 hoisted__U32_6514 = ((U32)(i * hoisted__U32_6513));
                (void)hoisted__U32_6514;
                U64 hoisted__U64_6515 = (U64)(hoisted__U32_6514);
                (void)hoisted__U64_6515;
                U32 hoisted__U32_6516 = 160;
                (void)hoisted__U32_6516;
                void *hoisted__v_6517 = ptr_add(new_data, hoisted__U64_6515);
                (void)hoisted__v_6517;
                (void)hoisted__v_6517;
                U64 hoisted__U64_6518 = (U64)(hoisted__U32_6516);
                (void)hoisted__U64_6518;
                memcpy(hoisted__v_6517, cloned, hoisted__U64_6518);
                U32 hoisted__U32_6519 = 160;
                (void)hoisted__U32_6519;
                I32 hoisted__I32_6520 = 0;
                (void)hoisted__I32_6520;
                U64 hoisted__U64_6521 = (U64)(hoisted__U32_6519);
                (void)hoisted__U64_6521;
                memset(cloned, hoisted__I32_6520, hoisted__U64_6521);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6522 = ((Bool)(_rc_U32_6508 > _re_U32_6508));
                (void)_wcond_Bool_6522;
                if (_wcond_Bool_6522) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6508);
                U32_dec(&_rc_U32_6508);
                U32 hoisted__U32_6523 = 160;
                (void)hoisted__U32_6523;
                U32 hoisted__U32_6524 = ((U32)(i * hoisted__U32_6523));
                (void)hoisted__U32_6524;
                U64 hoisted__U64_6525 = (U64)(hoisted__U32_6524);
                (void)hoisted__U64_6525;
                Expr *src = ptr_add(self->data, hoisted__U64_6525);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6526 = 160;
                (void)hoisted__U32_6526;
                U32 hoisted__U32_6527 = ((U32)(i * hoisted__U32_6526));
                (void)hoisted__U32_6527;
                U64 hoisted__U64_6528 = (U64)(hoisted__U32_6527);
                (void)hoisted__U64_6528;
                U32 hoisted__U32_6529 = 160;
                (void)hoisted__U32_6529;
                void *hoisted__v_6530 = ptr_add(new_data, hoisted__U64_6528);
                (void)hoisted__v_6530;
                (void)hoisted__v_6530;
                U64 hoisted__U64_6531 = (U64)(hoisted__U32_6529);
                (void)hoisted__U64_6531;
                memcpy(hoisted__v_6530, cloned, hoisted__U64_6531);
                U32 hoisted__U32_6532 = 160;
                (void)hoisted__U32_6532;
                I32 hoisted__I32_6533 = 0;
                (void)hoisted__I32_6533;
                U64 hoisted__U64_6534 = (U64)(hoisted__U32_6532);
                (void)hoisted__U64_6534;
                memset(cloned, hoisted__I32_6533, hoisted__U64_6534);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6539 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6539->data = new_data;
    hoisted__Vec__Expr_6539->count = self->count;
    hoisted__Vec__Expr_6539->cap = self->cap;
    (void)hoisted__Vec__Expr_6539;
    return hoisted__Vec__Expr_6539;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_6540 = 16;
    (void)hoisted__U32_6540;
    return hoisted__U32_6540;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7628 = 3;
    (void)hoisted__U32_7628;
    Array__Str *_va_Array_208 = Array__Str_new(hoisted__U32_7628);
    (void)_va_Array_208;
    I64 _va_Array_208_ek = 0;
    (void)_va_Array_208_ek;
    OutOfBounds *_va_Array_208_eo = malloc(sizeof(OutOfBounds));
    _va_Array_208_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_208_eo;
    U32 hoisted__U32_7629 = 0;
    (void)hoisted__U32_7629;
    Str *hoisted__Str_7630 = Str_clone(loc);
    (void)hoisted__Str_7630;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_208, hoisted__U32_7629, hoisted__Str_7630, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_144);
    Str_delete(&_til_str_lit_144, (Bool){0});
    U32 hoisted__U32_7632 = 1;
    (void)hoisted__U32_7632;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_208, hoisted__U32_7632, &_til_str_lit_145, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_144);
    Str_delete(&_til_str_lit_144, (Bool){0});
    Array__Str *hoisted__Array__Str_7635 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7635;
    U32 hoisted__U32_7636 = 2;
    (void)hoisted__U32_7636;
    Str *hoisted__Str_7637 = format(hoisted__Array__Str_7635);
    (void)hoisted__Str_7637;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_208, hoisted__U32_7636, hoisted__Str_7637, &_va_Array_208_ek, _va_Array_208_eo, &_til_str_lit_144);
    OutOfBounds_delete(_va_Array_208_eo, 1);
    Str_delete(&_til_str_lit_144, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_208);
    I64 hoisted__I64_7639 = 1;
    (void)hoisted__I64_7639;
    exit(hoisted__I64_7639);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7648 = 1;
    (void)hoisted__U32_7648;
    Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7648);
    (void)_va_Array_210;
    I64 _va_Array_210_ek = 0;
    (void)_va_Array_210_ek;
    OutOfBounds *_va_Array_210_eo = malloc(sizeof(OutOfBounds));
    _va_Array_210_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_210_eo;
    U32 hoisted__U32_7649 = 0;
    (void)hoisted__U32_7649;
    (void)_til_str_lit_146;
    (void)_til_str_lit_146;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    Array__Str_set(_va_Array_210, hoisted__U32_7649, &_til_str_lit_146, &_va_Array_210_ek, _va_Array_210_eo, &_til_str_lit_147);
    OutOfBounds_delete(_va_Array_210_eo, 1);
    Str_delete(&_til_str_lit_147, (Bool){0});
    panic(_va_Array_210, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7656 = not(cond);
    (void)hoisted__Bool_7656;
    if (hoisted__Bool_7656) {
        U32 hoisted__U32_7652 = 1;
        (void)hoisted__U32_7652;
        Array__Str *_va_Array_211 = Array__Str_new(hoisted__U32_7652);
        (void)_va_Array_211;
        I64 _va_Array_211_ek = 0;
        (void)_va_Array_211_ek;
        OutOfBounds *_va_Array_211_eo = malloc(sizeof(OutOfBounds));
        _va_Array_211_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_211_eo;
        U32 hoisted__U32_7653 = 0;
        (void)hoisted__U32_7653;
        (void)_til_str_lit_148;
        (void)_til_str_lit_148;
        (void)_til_str_lit_149;
        (void)_til_str_lit_149;
        Array__Str_set(_va_Array_211, hoisted__U32_7653, &_til_str_lit_148, &_va_Array_211_ek, _va_Array_211_eo, &_til_str_lit_149);
        OutOfBounds_delete(_va_Array_211_eo, 1);
        Str_delete(&_til_str_lit_149, (Bool){0});
        panic(_va_Array_211, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7666 = parts;
        (void)_fc_Array__Str_7666;
        (void)_fc_Array__Str_7666;
        U32 _fi_USize_7666 = 0;
        (void)_fi_USize_7666;
        while (1) {
            U32 hoisted__U32_7668 = Array__Str_len(_fc_Array__Str_7666);
            (void)hoisted__U32_7668;
            Bool _wcond_Bool_7667 = ((Bool)(_fi_USize_7666 < hoisted__U32_7668));
            (void)_wcond_Bool_7667;
            if (_wcond_Bool_7667) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7666, &_fi_USize_7666);
            U32 hoisted__U32_7669 = 1;
            (void)hoisted__U32_7669;
            U32 hoisted__U32_7670 = ((U32)(_fi_USize_7666 + hoisted__U32_7669));
            (void)hoisted__U32_7670;
            _fi_USize_7666 = hoisted__U32_7670;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7704 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7704;
    return hoisted__Bool_7704;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7713 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7713;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7713;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7714 = 0;
    (void)hoisted__U32_7714;
    U64 hoisted__U64_7715 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7714); });
    (void)hoisted__U64_7715;
    return hoisted__U64_7715;
}

U32 Range_size(void) {
    U32 hoisted__U32_7746 = 16;
    (void)hoisted__U32_7746;
    return hoisted__U32_7746;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7762 = 3;
    (void)hoisted__I64_7762;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    assert_eq__I64(result, hoisted__I64_7762, &_til_str_lit_152);
    Str_delete(&_til_str_lit_152, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7770 = 15;
    (void)hoisted__I64_7770;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    assert_eq__I64(result, hoisted__I64_7770, &_til_str_lit_153);
    Str_delete(&_til_str_lit_153, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7778 = 26;
    (void)hoisted__I64_7778;
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    assert_eq__I64(result, hoisted__I64_7778, &_til_str_lit_154);
    Str_delete(&_til_str_lit_154, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    assert_eq__Str(&result, &_til_str_lit_155, &_til_str_lit_156);
    Str_delete(&_til_str_lit_155, (Bool){0});
    Str_delete(&_til_str_lit_156, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_155;
    (void)_til_str_lit_155;
    (void)_til_str_lit_157;
    (void)_til_str_lit_157;
    assert_eq__Str(&r, &_til_str_lit_155, &_til_str_lit_157);
    Str_delete(&_til_str_lit_155, (Bool){0});
    Str_delete(&_til_str_lit_157, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    assert_eq__Str(&r2, &_til_str_lit_158, &_til_str_lit_159);
    Str_delete(&_til_str_lit_158, (Bool){0});
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    assert_eq__Str(&d, &_til_str_lit_160, &_til_str_lit_161);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_160, (Bool){0});
    Str_delete(&_til_str_lit_161, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    assert_eq__Str(&d2, &_til_str_lit_162, &_til_str_lit_163);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_162, (Bool){0});
    Str_delete(&_til_str_lit_163, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7865 = 106;
    (void)hoisted__I64_7865;
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    assert_eq__I64(d3, hoisted__I64_7865, &_til_str_lit_164);
    Str_delete(&_til_str_lit_164, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_167;
    (void)_til_str_lit_167;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_167);
    Str_delete(&_til_str_lit_167, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_168;
    (void)_til_str_lit_168;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_168);
    Str_delete(&_til_str_lit_168, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8468 = 8;
    (void)hoisted__I64_8468;
    (void)_til_str_lit_169;
    (void)_til_str_lit_169;
    assert_eq__I64(result, hoisted__I64_8468, &_til_str_lit_169);
    Str_delete(&_til_str_lit_169, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8472 = 1;
    (void)hoisted__Bool_8472;
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert(hoisted__Bool_8472, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
    Bool hoisted__Bool_8476 = 1;
    (void)hoisted__Bool_8476;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert(hoisted__Bool_8476, &_til_str_lit_171);
    Str_delete(&_til_str_lit_171, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    assert_eq__Str(&_til_str_lit_172, &_til_str_lit_172, &_til_str_lit_173);
    Str_delete(&_til_str_lit_172, (Bool){0});
    Str_delete(&_til_str_lit_172, (Bool){0});
    Str_delete(&_til_str_lit_173, (Bool){0});
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    assert_eq__Str(&_til_str_lit_174, &_til_str_lit_174, &_til_str_lit_175);
    Str_delete(&_til_str_lit_174, (Bool){0});
    Str_delete(&_til_str_lit_174, (Bool){0});
    Str_delete(&_til_str_lit_175, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8494 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8494;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8494;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8495 = 0;
    (void)hoisted__U32_8495;
    U64 hoisted__U64_8496 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8495); });
    (void)hoisted__U64_8496;
    return hoisted__U64_8496;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8527 = 16;
    (void)hoisted__U32_8527;
    return hoisted__U32_8527;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8528 = 42;
    (void)hoisted__I64_8528;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    assert_eq__I64(v.x, hoisted__I64_8528, &_til_str_lit_178);
    Str_delete(&_til_str_lit_178, (Bool){0});
    I64 hoisted__I64_8530 = 99;
    (void)hoisted__I64_8530;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__I64(v.y, hoisted__I64_8530, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8534 = 10;
    (void)hoisted__I64_8534;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    assert_eq__I64(p.x, hoisted__I64_8534, &_til_str_lit_180);
    Str_delete(&_til_str_lit_180, (Bool){0});
    I64 hoisted__I64_8536 = 20;
    (void)hoisted__I64_8536;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__I64(p.y, hoisted__I64_8536, &_til_str_lit_181);
    Str_delete(&_til_str_lit_181, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8543 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8543;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8543;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8544 = 0;
    (void)hoisted__U32_8544;
    U64 hoisted__U64_8545 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8544); });
    (void)hoisted__U64_8545;
    return hoisted__U64_8545;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8576 = 32;
    (void)hoisted__U32_8576;
    return hoisted__U32_8576;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8577 = 5;
    (void)hoisted__I64_8577;
    (void)_til_str_lit_185;
    (void)_til_str_lit_185;
    assert_eq__I64(r.top_left.x, hoisted__I64_8577, &_til_str_lit_185);
    Str_delete(&_til_str_lit_185, (Bool){0});
    I64 hoisted__I64_8579 = 10;
    (void)hoisted__I64_8579;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(r.top_left.y, hoisted__I64_8579, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_8581 = 100;
    (void)hoisted__I64_8581;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8581, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    I64 hoisted__I64_8583 = 200;
    (void)hoisted__I64_8583;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8583, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8586 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8586;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8586;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8587 = 0;
    (void)hoisted__U32_8587;
    U64 hoisted__U64_8588 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8587); });
    (void)hoisted__U64_8588;
    return hoisted__U64_8588;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8631 = 12;
    (void)hoisted__U32_8631;
    return hoisted__U32_8631;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8635 = F32_to_str(v.x);
    (void)hoisted__Str_8635;
    (void)_til_str_lit_190;
    (void)_til_str_lit_190;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    assert_eq__Str(hoisted__Str_8635, &_til_str_lit_190, &_til_str_lit_191);
    Str_delete(hoisted__Str_8635, 1);
    Str_delete(&_til_str_lit_190, (Bool){0});
    Str_delete(&_til_str_lit_191, (Bool){0});
    Str *hoisted__Str_8638 = F32_to_str(v.y);
    (void)hoisted__Str_8638;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    assert_eq__Str(hoisted__Str_8638, &_til_str_lit_192, &_til_str_lit_193);
    Str_delete(hoisted__Str_8638, 1);
    Str_delete(&_til_str_lit_192, (Bool){0});
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str *hoisted__Str_8641 = F32_to_str(v.z);
    (void)hoisted__Str_8641;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    assert_eq__Str(hoisted__Str_8641, &_til_str_lit_194, &_til_str_lit_195);
    Str_delete(hoisted__Str_8641, 1);
    Str_delete(&_til_str_lit_194, (Bool){0});
    Str_delete(&_til_str_lit_195, (Bool){0});
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
    U32 hoisted__U32_8652 = 1;
    (void)hoisted__U32_8652;
    Bool hoisted__Bool_8653 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_8653;
    if (hoisted__Bool_8653) {
        U32 hoisted__U32_8646 = 1;
        (void)hoisted__U32_8646;
        Bool hoisted__Bool_8647 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_8647;
        { Bool _ret_val = hoisted__Bool_8647;
                return _ret_val; }
    }
    U32 hoisted__U32_8654 = 1;
    (void)hoisted__U32_8654;
    Bool hoisted__Bool_8655 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_8655;
    if (hoisted__Bool_8655) {
        U32 hoisted__U32_8648 = 1;
        (void)hoisted__U32_8648;
        Bool hoisted__Bool_8649 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_8649;
        { Bool _ret_val = hoisted__Bool_8649;
                return _ret_val; }
    }
    U32 hoisted__U32_8656 = 1;
    (void)hoisted__U32_8656;
    Bool hoisted__Bool_8657 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_8657;
    if (hoisted__Bool_8657) {
        U32 hoisted__U32_8650 = 1;
        (void)hoisted__U32_8650;
        Bool hoisted__Bool_8651 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_8651;
        { Bool _ret_val = hoisted__Bool_8651;
                return _ret_val; }
    }
    Bool hoisted__Bool_8658 = 0;
    (void)hoisted__Bool_8658;
    return hoisted__Bool_8658;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8666 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8666;
    if (hoisted__Bool_8666) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8667 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8667;
    if (hoisted__Bool_8667) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8668 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8668;
    if (hoisted__Bool_8668) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8669 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8669;
    UNREACHABLE(&hoisted__Str_8669);
    Str_delete(&hoisted__Str_8669, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8670 = 1;
    (void)hoisted__U32_8670;
    return hoisted__U32_8670;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8671 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8671;
    (void)_til_str_lit_199;
    (void)_til_str_lit_199;
    assert(hoisted__Bool_8671, &_til_str_lit_199);
    Str_delete(&_til_str_lit_199, (Bool){0});
    Bool hoisted__Bool_8673 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8673;
    Bool hoisted__Bool_8674 = not(hoisted__Bool_8673);
    (void)hoisted__Bool_8674;
    (void)_til_str_lit_200;
    (void)_til_str_lit_200;
    assert(hoisted__Bool_8674, &_til_str_lit_200);
    Str_delete(&_til_str_lit_200, (Bool){0});
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
    U32 hoisted__U32_8676 = 1;
    (void)hoisted__U32_8676;
    Bool hoisted__Bool_8677 = ((Bool)(((Token *)(self))->tag == ((Token *)(other))->tag));
    (void)hoisted__Bool_8677;
    return hoisted__Bool_8677;
}

void Token_delete(Token * self, Bool call_free) {
    U32 hoisted__U32_8701 = 1;
    (void)hoisted__U32_8701;
    Bool hoisted__Bool_8702 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8702;
    if (hoisted__Bool_8702) {
        I64 *hoisted__I64_8697 = get_payload(self);
        (void)hoisted__I64_8697;
        (void)hoisted__I64_8697;
        Bool hoisted__Bool_8698 = 0;
        (void)hoisted__Bool_8698;
        I64_delete(hoisted__I64_8697, hoisted__Bool_8698);
    }
    U32 hoisted__U32_8703 = 1;
    (void)hoisted__U32_8703;
    Bool hoisted__Bool_8704 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8704;
    if (hoisted__Bool_8704) {
        Str *hoisted__Str_8699 = get_payload(self);
        (void)hoisted__Str_8699;
        (void)hoisted__Str_8699;
        Bool hoisted__Bool_8700 = 0;
        (void)hoisted__Bool_8700;
        Str_delete(hoisted__Str_8699, hoisted__Bool_8700);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_8738 = 1;
    (void)hoisted__U32_8738;
    Bool hoisted__Bool_8739 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8739;
    if (hoisted__Bool_8739) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8735 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8735;
        { Token * _ret_val = hoisted__Token_8735;
                return _ret_val; }
    }
    U32 hoisted__U32_8740 = 1;
    (void)hoisted__U32_8740;
    Bool hoisted__Bool_8741 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8741;
    if (hoisted__Bool_8741) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8736 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8736;
        Token *hoisted__Token_8737 = Token_Name(hoisted__Str_8736);
        (void)hoisted__Token_8737;
        { Token * _ret_val = hoisted__Token_8737;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8742 = 24;
    (void)hoisted__U32_8742;
    return hoisted__U32_8742;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8744 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8744;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert(hoisted__Bool_8744, &_til_str_lit_203);
    Str_delete(&_til_str_lit_203, (Bool){0});
    Bool hoisted__Bool_8746 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8746;
    Bool hoisted__Bool_8747 = not(hoisted__Bool_8746);
    (void)hoisted__Bool_8747;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_8747, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8749 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8749;
    (void)_til_str_lit_205;
    (void)_til_str_lit_205;
    assert(hoisted__Bool_8749, &_til_str_lit_205);
    Str_delete(&_til_str_lit_205, (Bool){0});
    Bool hoisted__Bool_8751 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8751;
    Bool hoisted__Bool_8752 = not(hoisted__Bool_8751);
    (void)hoisted__Bool_8752;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_8752, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8756 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8756;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_8756, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Bool hoisted__Bool_8758 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8758;
    Bool hoisted__Bool_8759 = not(hoisted__Bool_8758);
    (void)hoisted__Bool_8759;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_8759, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8892 = ((Bool)(a != b));
    (void)hoisted__Bool_8892;
    if (hoisted__Bool_8892) {
        U32 hoisted__U32_8876 = 5;
        (void)hoisted__U32_8876;
        Array__Str *_va_Array_253 = Array__Str_new(hoisted__U32_8876);
        (void)_va_Array_253;
        I64 _va_Array_253_ek = 0;
        (void)_va_Array_253_ek;
        OutOfBounds *_va_Array_253_eo = malloc(sizeof(OutOfBounds));
        _va_Array_253_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_253_eo;
        U32 hoisted__U32_8877 = 0;
        (void)hoisted__U32_8877;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8877, &_til_str_lit_209, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8880 = 1;
        (void)hoisted__U32_8880;
        Str *hoisted__Str_8881 = I64_to_str(a);
        (void)hoisted__Str_8881;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8880, hoisted__Str_8881, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8883 = 2;
        (void)hoisted__U32_8883;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8883, &_til_str_lit_211, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8886 = 3;
        (void)hoisted__U32_8886;
        Str *hoisted__Str_8887 = I64_to_str(b);
        (void)hoisted__Str_8887;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8886, hoisted__Str_8887, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8889 = 4;
        (void)hoisted__U32_8889;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8889, &_til_str_lit_212, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        OutOfBounds_delete(_va_Array_253_eo, 1);
        Str_delete(&_til_str_lit_210, (Bool){0});
        panic(_va_Array_253, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8909 = Str_neq(a, b);
    (void)hoisted__Bool_8909;
    if (hoisted__Bool_8909) {
        U32 hoisted__U32_8893 = 5;
        (void)hoisted__U32_8893;
        Array__Str *_va_Array_254 = Array__Str_new(hoisted__U32_8893);
        (void)_va_Array_254;
        I64 _va_Array_254_ek = 0;
        (void)_va_Array_254_ek;
        OutOfBounds *_va_Array_254_eo = malloc(sizeof(OutOfBounds));
        _va_Array_254_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_254_eo;
        U32 hoisted__U32_8894 = 0;
        (void)hoisted__U32_8894;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8894, &_til_str_lit_209, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8897 = 1;
        (void)hoisted__U32_8897;
        Str *hoisted__Str_8898 = Str_to_str(a);
        (void)hoisted__Str_8898;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8897, hoisted__Str_8898, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8900 = 2;
        (void)hoisted__U32_8900;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8900, &_til_str_lit_211, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8903 = 3;
        (void)hoisted__U32_8903;
        Str *hoisted__Str_8904 = Str_to_str(b);
        (void)hoisted__Str_8904;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8903, hoisted__Str_8904, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8906 = 4;
        (void)hoisted__U32_8906;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_254, hoisted__U32_8906, &_til_str_lit_212, &_va_Array_254_ek, _va_Array_254_eo, &_til_str_lit_210);
        OutOfBounds_delete(_va_Array_254_eo, 1);
        Str_delete(&_til_str_lit_210, (Bool){0});
        panic(_va_Array_254, loc);
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
void *U64_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)U64_to_str(*(U64 *)_a0);
}
static __attribute__((unused)) TilClosure U64_to_str_dyn__til_closure = { (void *)U64_to_str_dyn, NULL, NULL };
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U64_to_str_dyn__til_closure;
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
        return 12LL;
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
        if (*index == 11LL) return &_til_str_lit_71;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_72;
        if (*index == 1LL) return &_til_str_lit_73;
        if (*index == 2LL) return &_til_str_lit_74;
        if (*index == 3LL) return &_til_str_lit_75;
        if (*index == 4LL) return &_til_str_lit_76;
        if (*index == 5LL) return &_til_str_lit_52;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_77;
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
        if (*index == 0LL) return &_til_str_lit_78;
        if (*index == 1LL) return &_til_str_lit_79;
        if (*index == 2LL) return &_til_str_lit_80;
        if (*index == 3LL) return &_til_str_lit_81;
        if (*index == 4LL) return &_til_str_lit_82;
        if (*index == 5LL) return &_til_str_lit_83;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_79;
        if (*index == 1LL) return &_til_str_lit_84;
        if (*index == 2LL) return &_til_str_lit_85;
        if (*index == 3LL) return &_til_str_lit_87;
        if (*index == 4LL) return &_til_str_lit_83;
        if (*index == 5LL) return &_til_str_lit_89;
        if (*index == 6LL) return &_til_str_lit_90;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_92;
        if (*index == 2LL) return &_til_str_lit_93;
        if (*index == 3LL) return &_til_str_lit_76;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_92;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_43;
        if (*index == 1LL) return &_til_str_lit_46;
        if (*index == 2LL) return &_til_str_lit_52;
        if (*index == 3LL) return &_til_str_lit_94;
        if (*index == 4LL) return &_til_str_lit_95;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_52;
        if (*index == 1LL) return &_til_str_lit_101;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_70;
        if (*index == 1LL) return &_til_str_lit_71;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_136;
        if (*index == 1LL) return &_til_str_lit_138;
        if (*index == 2LL) return &_til_str_lit_140;
        if (*index == 3LL) return &_til_str_lit_141;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_142;
        if (*index == 1LL) return &_til_str_lit_143;
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
        if (*index == 0LL) return &_til_str_lit_150;
        if (*index == 1LL) return &_til_str_lit_151;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_176;
        if (*index == 1LL) return &_til_str_lit_177;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_182;
        if (*index == 1LL) return &_til_str_lit_184;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_176;
        if (*index == 1LL) return &_til_str_lit_177;
        if (*index == 2LL) return &_til_str_lit_189;
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
        if (*index == 11LL) return 1;
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
        if (*index == 9LL) return &_til_str_lit_16;
        if (*index == 10LL) return &_til_str_lit_60;
        if (*index == 11LL) return &_til_str_lit_6;
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
        if (*index == 2LL) return &_til_str_lit_86;
        if (*index == 3LL) return &_til_str_lit_88;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
        if (*index == 6LL) return &_til_str_lit_91;
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
        if (*index == 0LL) return &_til_str_lit_137;
        if (*index == 1LL) return &_til_str_lit_139;
        if (*index == 2LL) return &_til_str_lit_3;
        if (*index == 3LL) return &_til_str_lit_3;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_91;
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
        if (*index == 0LL) return &_til_str_lit_183;
        if (*index == 1LL) return &_til_str_lit_183;
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
        if (*index == 1LL) return &_til_str_lit_96;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_98;
        if (*index == 4LL) return &_til_str_lit_99;
        if (*index == 5LL) return &_til_str_lit_100;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_29;
        if (*index == 1LL) return &_til_str_lit_102;
        if (*index == 2LL) return &_til_str_lit_103;
        if (*index == 3LL) return &_til_str_lit_105;
        if (*index == 4LL) return &_til_str_lit_107;
        if (*index == 5LL) return &_til_str_lit_109;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_112;
        if (*index == 10LL) return &_til_str_lit_114;
        if (*index == 11LL) return &_til_str_lit_116;
        if (*index == 12LL) return &_til_str_lit_117;
        if (*index == 13LL) return &_til_str_lit_118;
        if (*index == 14LL) return &_til_str_lit_119;
        if (*index == 15LL) return &_til_str_lit_121;
        if (*index == 16LL) return &_til_str_lit_122;
        if (*index == 17LL) return &_til_str_lit_123;
        if (*index == 18LL) return &_til_str_lit_124;
        if (*index == 19LL) return &_til_str_lit_125;
        if (*index == 20LL) return &_til_str_lit_127;
        if (*index == 21LL) return &_til_str_lit_128;
        if (*index == 22LL) return &_til_str_lit_129;
        if (*index == 23LL) return &_til_str_lit_130;
        if (*index == 24LL) return &_til_str_lit_131;
        if (*index == 25LL) return &_til_str_lit_132;
        if (*index == 26LL) return &_til_str_lit_134;
        if (*index == 27LL) return &_til_str_lit_135;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_196;
        if (*index == 1LL) return &_til_str_lit_197;
        if (*index == 2LL) return &_til_str_lit_198;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_96;
        if (*index == 1LL) return &_til_str_lit_201;
        if (*index == 2LL) return &_til_str_lit_202;
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
        if (*index == 1LL) return &_til_str_lit_97;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_102;
        if (*index == 2LL) return &_til_str_lit_104;
        if (*index == 3LL) return &_til_str_lit_106;
        if (*index == 4LL) return &_til_str_lit_108;
        if (*index == 5LL) return &_til_str_lit_110;
        if (*index == 6LL) return &_til_str_lit_111;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_113;
        if (*index == 10LL) return &_til_str_lit_115;
        if (*index == 11LL) return &_til_str_lit_17;
        if (*index == 12LL) return &_til_str_lit_17;
        if (*index == 13LL) return &_til_str_lit_17;
        if (*index == 14LL) return &_til_str_lit_120;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_17;
        if (*index == 17LL) return &_til_str_lit_17;
        if (*index == 18LL) return &_til_str_lit_17;
        if (*index == 19LL) return &_til_str_lit_126;
        if (*index == 20LL) return &_til_str_lit_17;
        if (*index == 21LL) return &_til_str_lit_17;
        if (*index == 22LL) return &_til_str_lit_17;
        if (*index == 23LL) return &_til_str_lit_17;
        if (*index == 24LL) return &_til_str_lit_17;
        if (*index == 25LL) return &_til_str_lit_133;
        if (*index == 26LL) return &_til_str_lit_17;
        if (*index == 27LL) return &_til_str_lit_133;
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
