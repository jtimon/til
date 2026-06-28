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
    Bool hoisted__Bool_2228 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_2228;
    if (hoisted__Bool_2228) {
        U32 hoisted__U32_2207 = 1;
        (void)hoisted__U32_2207;
        Bool hoisted__Bool_2208 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_2208;
        { Bool _ret_val = hoisted__Bool_2208;
                return _ret_val; }
    }
    U32 hoisted__U32_2229 = 1;
    (void)hoisted__U32_2229;
    Bool hoisted__Bool_2230 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_2230;
    if (hoisted__Bool_2230) {
        U32 hoisted__U32_2209 = 1;
        (void)hoisted__U32_2209;
        Bool hoisted__Bool_2210 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_2210;
        { Bool _ret_val = hoisted__Bool_2210;
                return _ret_val; }
    }
    U32 hoisted__U32_2231 = 1;
    (void)hoisted__U32_2231;
    Bool hoisted__Bool_2232 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_2232;
    if (hoisted__Bool_2232) {
        U32 hoisted__U32_2211 = 1;
        (void)hoisted__U32_2211;
        Bool hoisted__Bool_2212 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_2212;
        { Bool _ret_val = hoisted__Bool_2212;
                return _ret_val; }
    }
    U32 hoisted__U32_2233 = 1;
    (void)hoisted__U32_2233;
    Bool hoisted__Bool_2234 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_2234;
    if (hoisted__Bool_2234) {
        U32 hoisted__U32_2213 = 1;
        (void)hoisted__U32_2213;
        Bool hoisted__Bool_2214 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_2214;
        { Bool _ret_val = hoisted__Bool_2214;
                return _ret_val; }
    }
    U32 hoisted__U32_2235 = 1;
    (void)hoisted__U32_2235;
    Bool hoisted__Bool_2236 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_2236;
    if (hoisted__Bool_2236) {
        U32 hoisted__U32_2215 = 1;
        (void)hoisted__U32_2215;
        Bool hoisted__Bool_2216 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_2216;
        { Bool _ret_val = hoisted__Bool_2216;
                return _ret_val; }
    }
    U32 hoisted__U32_2237 = 1;
    (void)hoisted__U32_2237;
    Bool hoisted__Bool_2238 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_2238;
    if (hoisted__Bool_2238) {
        U32 hoisted__U32_2217 = 1;
        (void)hoisted__U32_2217;
        Bool hoisted__Bool_2218 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_2218;
        { Bool _ret_val = hoisted__Bool_2218;
                return _ret_val; }
    }
    U32 hoisted__U32_2239 = 1;
    (void)hoisted__U32_2239;
    Bool hoisted__Bool_2240 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_2240;
    if (hoisted__Bool_2240) {
        U32 hoisted__U32_2219 = 1;
        (void)hoisted__U32_2219;
        Bool hoisted__Bool_2220 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_2220;
        { Bool _ret_val = hoisted__Bool_2220;
                return _ret_val; }
    }
    U32 hoisted__U32_2241 = 1;
    (void)hoisted__U32_2241;
    Bool hoisted__Bool_2242 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        U32 hoisted__U32_2221 = 1;
        (void)hoisted__U32_2221;
        Bool hoisted__Bool_2222 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_2222;
        { Bool _ret_val = hoisted__Bool_2222;
                return _ret_val; }
    }
    U32 hoisted__U32_2243 = 1;
    (void)hoisted__U32_2243;
    Bool hoisted__Bool_2244 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        U32 hoisted__U32_2223 = 1;
        (void)hoisted__U32_2223;
        Bool hoisted__Bool_2224 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_2224;
        { Bool _ret_val = hoisted__Bool_2224;
                return _ret_val; }
    }
    U32 hoisted__U32_2245 = 1;
    (void)hoisted__U32_2245;
    Bool hoisted__Bool_2246 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_2246;
    if (hoisted__Bool_2246) {
        U32 hoisted__U32_2225 = 1;
        (void)hoisted__U32_2225;
        Bool hoisted__Bool_2226 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
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
    Bool hoisted__Bool_2362 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
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
    Bool hoisted__Bool_2364 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
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
    Bool hoisted__Bool_2366 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
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
    Bool hoisted__Bool_2368 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
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
    Bool hoisted__Bool_2370 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
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
    Bool hoisted__Bool_2472 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2472;
    if (hoisted__Bool_2472) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    U32 hoisted__U32_2473 = 1;
    (void)hoisted__U32_2473;
    Bool hoisted__Bool_2474 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2474;
    if (hoisted__Bool_2474) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    U32 hoisted__U32_2475 = 1;
    (void)hoisted__U32_2475;
    Bool hoisted__Bool_2476 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
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
    Bool hoisted__Bool_2478 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2478;
    if (hoisted__Bool_2478) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    U32 hoisted__U32_2479 = 1;
    (void)hoisted__U32_2479;
    Bool hoisted__Bool_2480 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
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
    Bool hoisted__Bool_2482 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2482;
    if (hoisted__Bool_2482) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    U32 hoisted__U32_2483 = 1;
    (void)hoisted__U32_2483;
    Bool hoisted__Bool_2484 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2484;
    if (hoisted__Bool_2484) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    U32 hoisted__U32_2485 = 1;
    (void)hoisted__U32_2485;
    Bool hoisted__Bool_2486 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2486;
    if (hoisted__Bool_2486) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    U32 hoisted__U32_2487 = 1;
    (void)hoisted__U32_2487;
    Bool hoisted__Bool_2488 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2488;
    if (hoisted__Bool_2488) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    U32 hoisted__U32_2489 = 1;
    (void)hoisted__U32_2489;
    Bool hoisted__Bool_2490 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
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
    Bool hoisted__Bool_2492 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
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
    Bool hoisted__Bool_2494 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
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
    Bool hoisted__Bool_2644 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2644;
    if (hoisted__Bool_2644) {
        U32 hoisted__U32_2623 = 1;
        (void)hoisted__U32_2623;
        Bool hoisted__Bool_2624 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2624;
        { Bool _ret_val = hoisted__Bool_2624;
                return _ret_val; }
    }
    U32 hoisted__U32_2645 = 1;
    (void)hoisted__U32_2645;
    Bool hoisted__Bool_2646 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2646;
    if (hoisted__Bool_2646) {
        U32 hoisted__U32_2625 = 1;
        (void)hoisted__U32_2625;
        Bool hoisted__Bool_2626 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2626;
        { Bool _ret_val = hoisted__Bool_2626;
                return _ret_val; }
    }
    U32 hoisted__U32_2647 = 1;
    (void)hoisted__U32_2647;
    Bool hoisted__Bool_2648 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2648;
    if (hoisted__Bool_2648) {
        U32 hoisted__U32_2627 = 1;
        (void)hoisted__U32_2627;
        Bool hoisted__Bool_2628 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2628;
        { Bool _ret_val = hoisted__Bool_2628;
                return _ret_val; }
    }
    U32 hoisted__U32_2649 = 1;
    (void)hoisted__U32_2649;
    Bool hoisted__Bool_2650 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2650;
    if (hoisted__Bool_2650) {
        U32 hoisted__U32_2629 = 1;
        (void)hoisted__U32_2629;
        Bool hoisted__Bool_2630 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2630;
        { Bool _ret_val = hoisted__Bool_2630;
                return _ret_val; }
    }
    U32 hoisted__U32_2651 = 1;
    (void)hoisted__U32_2651;
    Bool hoisted__Bool_2652 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2652;
    if (hoisted__Bool_2652) {
        U32 hoisted__U32_2631 = 1;
        (void)hoisted__U32_2631;
        Bool hoisted__Bool_2632 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2632;
        { Bool _ret_val = hoisted__Bool_2632;
                return _ret_val; }
    }
    U32 hoisted__U32_2653 = 1;
    (void)hoisted__U32_2653;
    Bool hoisted__Bool_2654 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2654;
    if (hoisted__Bool_2654) {
        U32 hoisted__U32_2633 = 1;
        (void)hoisted__U32_2633;
        Bool hoisted__Bool_2634 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2634;
        { Bool _ret_val = hoisted__Bool_2634;
                return _ret_val; }
    }
    U32 hoisted__U32_2655 = 1;
    (void)hoisted__U32_2655;
    Bool hoisted__Bool_2656 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2656;
    if (hoisted__Bool_2656) {
        U32 hoisted__U32_2635 = 1;
        (void)hoisted__U32_2635;
        Bool hoisted__Bool_2636 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2636;
        { Bool _ret_val = hoisted__Bool_2636;
                return _ret_val; }
    }
    U32 hoisted__U32_2657 = 1;
    (void)hoisted__U32_2657;
    Bool hoisted__Bool_2658 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2658;
    if (hoisted__Bool_2658) {
        U32 hoisted__U32_2637 = 1;
        (void)hoisted__U32_2637;
        Bool hoisted__Bool_2638 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2638;
        { Bool _ret_val = hoisted__Bool_2638;
                return _ret_val; }
    }
    U32 hoisted__U32_2659 = 1;
    (void)hoisted__U32_2659;
    Bool hoisted__Bool_2660 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2660;
    if (hoisted__Bool_2660) {
        U32 hoisted__U32_2639 = 1;
        (void)hoisted__U32_2639;
        Bool hoisted__Bool_2640 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2640;
        { Bool _ret_val = hoisted__Bool_2640;
                return _ret_val; }
    }
    U32 hoisted__U32_2661 = 1;
    (void)hoisted__U32_2661;
    Bool hoisted__Bool_2662 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2662;
    if (hoisted__Bool_2662) {
        U32 hoisted__U32_2641 = 1;
        (void)hoisted__U32_2641;
        Bool hoisted__Bool_2642 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
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
    Bool hoisted__Bool_2706 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2706;
    if (hoisted__Bool_2706) {
        U32 hoisted__U32_2699 = 1;
        (void)hoisted__U32_2699;
        Bool hoisted__Bool_2700 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2700;
        { Bool _ret_val = hoisted__Bool_2700;
                return _ret_val; }
    }
    U32 hoisted__U32_2707 = 1;
    (void)hoisted__U32_2707;
    Bool hoisted__Bool_2708 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2708;
    if (hoisted__Bool_2708) {
        U32 hoisted__U32_2701 = 1;
        (void)hoisted__U32_2701;
        Bool hoisted__Bool_2702 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2702;
        { Bool _ret_val = hoisted__Bool_2702;
                return _ret_val; }
    }
    U32 hoisted__U32_2709 = 1;
    (void)hoisted__U32_2709;
    Bool hoisted__Bool_2710 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2710;
    if (hoisted__Bool_2710) {
        U32 hoisted__U32_2703 = 1;
        (void)hoisted__U32_2703;
        Bool hoisted__Bool_2704 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
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
    hoisted__FunctionDef_2740->return_shallow_explicit = self->return_shallow_explicit;
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
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2748);
    Bool hoisted__Bool_2749 = 0;
    (void)hoisted__Bool_2749;
    Bool_delete(&self->auto_generated, hoisted__Bool_2749);
    Bool hoisted__Bool_2750 = 0;
    (void)hoisted__Bool_2750;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2750);
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2751);
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    Str_delete(&self->closure_name, hoisted__Bool_2752);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2753 = 0;
    (void)hoisted__U32_2753;
    U64 hoisted__U64_2754 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2753); });
    (void)hoisted__U64_2754;
    return hoisted__U64_2754;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2755 = 104;
    (void)hoisted__U32_2755;
    return hoisted__U32_2755;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2758 = malloc(sizeof(FCallData));
    hoisted__FCallData_2758->is_splat = self->is_splat;
    hoisted__FCallData_2758->does_throw = self->does_throw;
    hoisted__FCallData_2758->is_bang = self->is_bang;
    hoisted__FCallData_2758->own_args = self->own_args;
    hoisted__FCallData_2758->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2758->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2758;
    return hoisted__FCallData_2758;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2759 = 0;
    (void)hoisted__Bool_2759;
    Bool_delete(&self->is_splat, hoisted__Bool_2759);
    Bool hoisted__Bool_2760 = 0;
    (void)hoisted__Bool_2760;
    Bool_delete(&self->does_throw, hoisted__Bool_2760);
    Bool hoisted__Bool_2761 = 0;
    (void)hoisted__Bool_2761;
    Bool_delete(&self->is_bang, hoisted__Bool_2761);
    Bool hoisted__Bool_2762 = 0;
    (void)hoisted__Bool_2762;
    U64_delete(&self->own_args, hoisted__Bool_2762);
    Bool hoisted__Bool_2763 = 0;
    (void)hoisted__Bool_2763;
    Bool_delete(&self->swap_replace, hoisted__Bool_2763);
    Bool hoisted__Bool_2764 = 0;
    (void)hoisted__Bool_2764;
    Type_delete(&self->til_type, hoisted__Bool_2764);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2765 = 0;
    (void)hoisted__U32_2765;
    U64 hoisted__U64_2766 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2765); });
    (void)hoisted__U64_2766;
    return hoisted__U64_2766;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2767 = 48;
    (void)hoisted__U32_2767;
    return hoisted__U32_2767;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2779 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2779->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2779->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2779;
    return hoisted__LiteralNumData_2779;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2780 = 0;
    (void)hoisted__Bool_2780;
    Str_delete(&self->text, hoisted__Bool_2780);
    Bool hoisted__Bool_2781 = 0;
    (void)hoisted__Bool_2781;
    Type_delete(&self->til_type, hoisted__Bool_2781);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2782 = 0;
    (void)hoisted__U32_2782;
    U64 hoisted__U64_2783 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2782); });
    (void)hoisted__U64_2783;
    return hoisted__U64_2783;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2784 = 40;
    (void)hoisted__U32_2784;
    return hoisted__U32_2784;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2794 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2794->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2794->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2794;
    return hoisted__IdentData_2794;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2795 = 0;
    (void)hoisted__Bool_2795;
    Str_delete(&self->name, hoisted__Bool_2795);
    Bool hoisted__Bool_2796 = 0;
    (void)hoisted__Bool_2796;
    Type_delete(&self->til_type, hoisted__Bool_2796);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2797 = 0;
    (void)hoisted__U32_2797;
    U64 hoisted__U64_2798 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2797); });
    (void)hoisted__U64_2798;
    return hoisted__U64_2798;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2799 = 40;
    (void)hoisted__U32_2799;
    return hoisted__U32_2799;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2805 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2805->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2805->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2805;
    return hoisted__FieldAccessData_2805;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2806 = 0;
    (void)hoisted__Bool_2806;
    Str_delete(&self->name, hoisted__Bool_2806);
    Bool hoisted__Bool_2807 = 0;
    (void)hoisted__Bool_2807;
    Type_delete(&self->til_type, hoisted__Bool_2807);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2808 = 0;
    (void)hoisted__U32_2808;
    U64 hoisted__U64_2809 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2808); });
    (void)hoisted__U64_2809;
    return hoisted__U64_2809;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2810 = 40;
    (void)hoisted__U32_2810;
    return hoisted__U32_2810;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2891 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2891->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2891->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2891->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2891->is_interface = self->is_interface;
    hoisted__StructDef_2891->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2891->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2891;
    return hoisted__StructDef_2891;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2892 = 0;
    (void)hoisted__Bool_2892;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2892);
    Bool hoisted__Bool_2893 = 0;
    (void)hoisted__Bool_2893;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2893);
    Bool hoisted__Bool_2894 = 0;
    (void)hoisted__Bool_2894;
    Str_delete(&self->c_tag, hoisted__Bool_2894);
    Bool hoisted__Bool_2895 = 0;
    (void)hoisted__Bool_2895;
    Bool_delete(&self->is_interface, hoisted__Bool_2895);
    Bool hoisted__Bool_2896 = 0;
    (void)hoisted__Bool_2896;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2896);
    Bool hoisted__Bool_2897 = 0;
    (void)hoisted__Bool_2897;
    Str_delete(&self->implements_name, hoisted__Bool_2897);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2898 = 0;
    (void)hoisted__U32_2898;
    U64 hoisted__U64_2899 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2898); });
    (void)hoisted__U64_2899;
    return hoisted__U64_2899;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2900 = 72;
    (void)hoisted__U32_2900;
    return hoisted__U32_2900;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2905 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2905->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2905->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2905->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2905->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2905->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2905->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2905->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2905;
    return hoisted__EnumDef_2905;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2906 = 0;
    (void)hoisted__Bool_2906;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2906);
    Bool hoisted__Bool_2907 = 0;
    (void)hoisted__Bool_2907;
    Vec__Str_delete(&self->variants, hoisted__Bool_2907);
    Bool hoisted__Bool_2908 = 0;
    (void)hoisted__Bool_2908;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2908);
    Bool hoisted__Bool_2909 = 0;
    (void)hoisted__Bool_2909;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2909);
    Bool hoisted__Bool_2910 = 0;
    (void)hoisted__Bool_2910;
    Str_delete(&self->implements_name, hoisted__Bool_2910);
    Bool hoisted__Bool_2911 = 0;
    (void)hoisted__Bool_2911;
    Str_delete(&self->tag_type, hoisted__Bool_2911);
    Bool hoisted__Bool_2912 = 0;
    (void)hoisted__Bool_2912;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2912);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2913 = 0;
    (void)hoisted__U32_2913;
    U64 hoisted__U64_2914 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2913); });
    (void)hoisted__U64_2914;
    return hoisted__U64_2914;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2915 = 128;
    (void)hoisted__U32_2915;
    return hoisted__U32_2915;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_3016 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_3016->name = *_ca; free(_ca); }
    hoisted__AssignData_3016->save_old_delete = self->save_old_delete;
    hoisted__AssignData_3016->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_3016->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_3016;
    return hoisted__AssignData_3016;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_3017 = 0;
    (void)hoisted__Bool_3017;
    Str_delete(&self->name, hoisted__Bool_3017);
    Bool hoisted__Bool_3018 = 0;
    (void)hoisted__Bool_3018;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3018);
    Bool hoisted__Bool_3019 = 0;
    (void)hoisted__Bool_3019;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_3019);
    Bool hoisted__Bool_3020 = 0;
    (void)hoisted__Bool_3020;
    Bool_delete(&self->swap_replace, hoisted__Bool_3020);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_3021 = 0;
    (void)hoisted__U32_3021;
    U64 hoisted__U64_3022 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3021); });
    (void)hoisted__U64_3022;
    return hoisted__U64_3022;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_3023 = 24;
    (void)hoisted__U32_3023;
    return hoisted__U32_3023;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_3025 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_3025->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_3025->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_3025;
    return hoisted__FieldAssignData_3025;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_3026 = 0;
    (void)hoisted__Bool_3026;
    Str_delete(&self->name, hoisted__Bool_3026);
    Bool hoisted__Bool_3027 = 0;
    (void)hoisted__Bool_3027;
    Bool_delete(&self->save_old_delete, hoisted__Bool_3027);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_3028 = 0;
    (void)hoisted__U32_3028;
    U64 hoisted__U64_3029 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3028); });
    (void)hoisted__U64_3029;
    return hoisted__U64_3029;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_3030 = 24;
    (void)hoisted__U32_3030;
    return hoisted__U32_3030;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_3032 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_3032->name = *_ca; free(_ca); }
    hoisted__ForInData_3032->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_3032->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_3032->name2 = *_ca; free(_ca); }
    hoisted__ForInData_3032->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_3032;
    return hoisted__ForInData_3032;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_3033 = 0;
    (void)hoisted__Bool_3033;
    Str_delete(&self->name, hoisted__Bool_3033);
    Bool hoisted__Bool_3034 = 0;
    (void)hoisted__Bool_3034;
    Bool_delete(&self->is_mut, hoisted__Bool_3034);
    Bool hoisted__Bool_3035 = 0;
    (void)hoisted__Bool_3035;
    Type_delete(&self->til_type, hoisted__Bool_3035);
    Bool hoisted__Bool_3036 = 0;
    (void)hoisted__Bool_3036;
    Str_delete(&self->name2, hoisted__Bool_3036);
    Bool hoisted__Bool_3037 = 0;
    (void)hoisted__Bool_3037;
    Bool_delete(&self->is_mut2, hoisted__Bool_3037);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_3038 = 0;
    (void)hoisted__U32_3038;
    U64 hoisted__U64_3039 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3038); });
    (void)hoisted__U64_3039;
    return hoisted__U64_3039;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_3040 = 72;
    (void)hoisted__U32_3040;
    return hoisted__U32_3040;
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
    U32 hoisted__U32_3083 = 1;
    (void)hoisted__U32_3083;
    Bool hoisted__Bool_3084 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3084;
    if (hoisted__Bool_3084) {
        Str *hoisted__Str_3077 = get_payload(self);
        (void)hoisted__Str_3077;
        (void)hoisted__Str_3077;
        Bool hoisted__Bool_3078 = 0;
        (void)hoisted__Bool_3078;
        Str_delete(hoisted__Str_3077, hoisted__Bool_3078);
    }
    U32 hoisted__U32_3085 = 1;
    (void)hoisted__U32_3085;
    Bool hoisted__Bool_3086 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3086;
    if (hoisted__Bool_3086) {
        LiteralNumData *hoisted__LiteralNumData_3079 = get_payload(self);
        (void)hoisted__LiteralNumData_3079;
        (void)hoisted__LiteralNumData_3079;
        Bool hoisted__Bool_3080 = 0;
        (void)hoisted__Bool_3080;
        LiteralNumData_delete(hoisted__LiteralNumData_3079, hoisted__Bool_3080);
    }
    U32 hoisted__U32_3087 = 1;
    (void)hoisted__U32_3087;
    Bool hoisted__Bool_3088 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3088;
    if (hoisted__Bool_3088) {
        Bool *hoisted__Bool_3081 = get_payload(self);
        (void)hoisted__Bool_3081;
        (void)hoisted__Bool_3081;
        Bool hoisted__Bool_3082 = 0;
        (void)hoisted__Bool_3082;
        Bool_delete(hoisted__Bool_3081, hoisted__Bool_3082);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_3143 = 1;
    (void)hoisted__U32_3143;
    Bool hoisted__Bool_3144 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_3144;
    if (hoisted__Bool_3144) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_3138 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_3138;
        Literal *hoisted__Literal_3139 = Literal_Str(hoisted__Str_3138);
        (void)hoisted__Literal_3139;
        { Literal * _ret_val = hoisted__Literal_3139;
                return _ret_val; }
    }
    U32 hoisted__U32_3145 = 1;
    (void)hoisted__U32_3145;
    Bool hoisted__Bool_3146 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_3146;
    if (hoisted__Bool_3146) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_3140 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_3140;
        Literal *hoisted__Literal_3141 = Literal_Num(hoisted__LiteralNumData_3140);
        (void)hoisted__Literal_3141;
        { Literal * _ret_val = hoisted__Literal_3141;
                return _ret_val; }
    }
    U32 hoisted__U32_3147 = 1;
    (void)hoisted__U32_3147;
    Bool hoisted__Bool_3148 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_3148;
    if (hoisted__Bool_3148) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_3142 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_3142;
        { Literal * _ret_val = hoisted__Literal_3142;
                return _ret_val; }
    }
    U32 hoisted__U32_3149 = 1;
    (void)hoisted__U32_3149;
    Bool hoisted__Bool_3150 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_3150;
    if (hoisted__Bool_3150) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    U32 hoisted__U32_3151 = 1;
    (void)hoisted__U32_3151;
    Bool hoisted__Bool_3152 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_3152;
    if (hoisted__Bool_3152) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_3153 = 48;
    (void)hoisted__U32_3153;
    return hoisted__U32_3153;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_3156 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_3156->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_3156->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_3156;
    return hoisted__MatchData_3156;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_3157 = 0;
    (void)hoisted__Bool_3157;
    Type_delete(&self->til_type, hoisted__Bool_3157);
    Bool hoisted__Bool_3158 = 0;
    (void)hoisted__Bool_3158;
    Str_delete(&self->result_temp, hoisted__Bool_3158);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_3159 = 0;
    (void)hoisted__U32_3159;
    U64 hoisted__U64_3160 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3159); });
    (void)hoisted__U64_3160;
    return hoisted__U64_3160;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_3161 = 40;
    (void)hoisted__U32_3161;
    return hoisted__U32_3161;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_3166 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_3166->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_3166->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_3166;
    return hoisted__CaptureBlockData_3166;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_3167 = 0;
    (void)hoisted__Bool_3167;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_3167);
    Bool hoisted__Bool_3168 = 0;
    (void)hoisted__Bool_3168;
    Str_delete(&self->closure_name, hoisted__Bool_3168);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_3169 = 0;
    (void)hoisted__U32_3169;
    U64 hoisted__U64_3170 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3169); });
    (void)hoisted__U64_3170;
    return hoisted__U64_3170;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_3171 = 32;
    (void)hoisted__U32_3171;
    return hoisted__U32_3171;
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
    U32 hoisted__U32_3432 = 1;
    (void)hoisted__U32_3432;
    Bool hoisted__Bool_3433 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3433;
    if (hoisted__Bool_3433) {
        Literal *hoisted__Literal_3402 = get_payload(self);
        (void)hoisted__Literal_3402;
        (void)hoisted__Literal_3402;
        Bool hoisted__Bool_3403 = 0;
        (void)hoisted__Bool_3403;
        Literal_delete(hoisted__Literal_3402, hoisted__Bool_3403);
    }
    U32 hoisted__U32_3434 = 1;
    (void)hoisted__U32_3434;
    Bool hoisted__Bool_3435 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3435;
    if (hoisted__Bool_3435) {
        IdentData *hoisted__IdentData_3404 = get_payload(self);
        (void)hoisted__IdentData_3404;
        (void)hoisted__IdentData_3404;
        Bool hoisted__Bool_3405 = 0;
        (void)hoisted__Bool_3405;
        IdentData_delete(hoisted__IdentData_3404, hoisted__Bool_3405);
    }
    U32 hoisted__U32_3436 = 1;
    (void)hoisted__U32_3436;
    Bool hoisted__Bool_3437 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3437;
    if (hoisted__Bool_3437) {
        Declaration *hoisted__Declaration_3406 = get_payload(self);
        (void)hoisted__Declaration_3406;
        (void)hoisted__Declaration_3406;
        Bool hoisted__Bool_3407 = 0;
        (void)hoisted__Bool_3407;
        Declaration_delete(hoisted__Declaration_3406, hoisted__Bool_3407);
    }
    U32 hoisted__U32_3438 = 1;
    (void)hoisted__U32_3438;
    Bool hoisted__Bool_3439 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3439;
    if (hoisted__Bool_3439) {
        AssignData *hoisted__AssignData_3408 = get_payload(self);
        (void)hoisted__AssignData_3408;
        (void)hoisted__AssignData_3408;
        Bool hoisted__Bool_3409 = 0;
        (void)hoisted__Bool_3409;
        AssignData_delete(hoisted__AssignData_3408, hoisted__Bool_3409);
    }
    U32 hoisted__U32_3440 = 1;
    (void)hoisted__U32_3440;
    Bool hoisted__Bool_3441 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3441;
    if (hoisted__Bool_3441) {
        FCallData *hoisted__FCallData_3410 = get_payload(self);
        (void)hoisted__FCallData_3410;
        (void)hoisted__FCallData_3410;
        Bool hoisted__Bool_3411 = 0;
        (void)hoisted__Bool_3411;
        FCallData_delete(hoisted__FCallData_3410, hoisted__Bool_3411);
    }
    U32 hoisted__U32_3442 = 1;
    (void)hoisted__U32_3442;
    Bool hoisted__Bool_3443 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3443;
    if (hoisted__Bool_3443) {
        FunctionDef *hoisted__FunctionDef_3412 = get_payload(self);
        (void)hoisted__FunctionDef_3412;
        (void)hoisted__FunctionDef_3412;
        Bool hoisted__Bool_3413 = 0;
        (void)hoisted__Bool_3413;
        FunctionDef_delete(hoisted__FunctionDef_3412, hoisted__Bool_3413);
    }
    U32 hoisted__U32_3444 = 1;
    (void)hoisted__U32_3444;
    Bool hoisted__Bool_3445 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3445;
    if (hoisted__Bool_3445) {
        StructDef *hoisted__StructDef_3414 = get_payload(self);
        (void)hoisted__StructDef_3414;
        (void)hoisted__StructDef_3414;
        Bool hoisted__Bool_3415 = 0;
        (void)hoisted__Bool_3415;
        StructDef_delete(hoisted__StructDef_3414, hoisted__Bool_3415);
    }
    U32 hoisted__U32_3446 = 1;
    (void)hoisted__U32_3446;
    Bool hoisted__Bool_3447 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3447;
    if (hoisted__Bool_3447) {
        EnumDef *hoisted__EnumDef_3416 = get_payload(self);
        (void)hoisted__EnumDef_3416;
        (void)hoisted__EnumDef_3416;
        Bool hoisted__Bool_3417 = 0;
        (void)hoisted__Bool_3417;
        EnumDef_delete(hoisted__EnumDef_3416, hoisted__Bool_3417);
    }
    U32 hoisted__U32_3448 = 1;
    (void)hoisted__U32_3448;
    Bool hoisted__Bool_3449 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3449;
    if (hoisted__Bool_3449) {
        FieldAccessData *hoisted__FieldAccessData_3418 = get_payload(self);
        (void)hoisted__FieldAccessData_3418;
        (void)hoisted__FieldAccessData_3418;
        Bool hoisted__Bool_3419 = 0;
        (void)hoisted__Bool_3419;
        FieldAccessData_delete(hoisted__FieldAccessData_3418, hoisted__Bool_3419);
    }
    U32 hoisted__U32_3450 = 1;
    (void)hoisted__U32_3450;
    Bool hoisted__Bool_3451 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3451;
    if (hoisted__Bool_3451) {
        FieldAssignData *hoisted__FieldAssignData_3420 = get_payload(self);
        (void)hoisted__FieldAssignData_3420;
        (void)hoisted__FieldAssignData_3420;
        Bool hoisted__Bool_3421 = 0;
        (void)hoisted__Bool_3421;
        FieldAssignData_delete(hoisted__FieldAssignData_3420, hoisted__Bool_3421);
    }
    U32 hoisted__U32_3452 = 1;
    (void)hoisted__U32_3452;
    Bool hoisted__Bool_3453 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3453;
    if (hoisted__Bool_3453) {
        ForInData *hoisted__ForInData_3422 = get_payload(self);
        (void)hoisted__ForInData_3422;
        (void)hoisted__ForInData_3422;
        Bool hoisted__Bool_3423 = 0;
        (void)hoisted__Bool_3423;
        ForInData_delete(hoisted__ForInData_3422, hoisted__Bool_3423);
    }
    U32 hoisted__U32_3454 = 1;
    (void)hoisted__U32_3454;
    Bool hoisted__Bool_3455 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3455;
    if (hoisted__Bool_3455) {
        Str *hoisted__Str_3424 = get_payload(self);
        (void)hoisted__Str_3424;
        (void)hoisted__Str_3424;
        Bool hoisted__Bool_3425 = 0;
        (void)hoisted__Bool_3425;
        Str_delete(hoisted__Str_3424, hoisted__Bool_3425);
    }
    U32 hoisted__U32_3456 = 1;
    (void)hoisted__U32_3456;
    Bool hoisted__Bool_3457 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3457;
    if (hoisted__Bool_3457) {
        MatchData *hoisted__MatchData_3426 = get_payload(self);
        (void)hoisted__MatchData_3426;
        (void)hoisted__MatchData_3426;
        Bool hoisted__Bool_3427 = 0;
        (void)hoisted__Bool_3427;
        MatchData_delete(hoisted__MatchData_3426, hoisted__Bool_3427);
    }
    U32 hoisted__U32_3458 = 1;
    (void)hoisted__U32_3458;
    Bool hoisted__Bool_3459 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3459;
    if (hoisted__Bool_3459) {
        CaptureBlockData *hoisted__CaptureBlockData_3428 = get_payload(self);
        (void)hoisted__CaptureBlockData_3428;
        (void)hoisted__CaptureBlockData_3428;
        Bool hoisted__Bool_3429 = 0;
        (void)hoisted__Bool_3429;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3428, hoisted__Bool_3429);
    }
    U32 hoisted__U32_3460 = 1;
    (void)hoisted__U32_3460;
    Bool hoisted__Bool_3461 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3461;
    if (hoisted__Bool_3461) {
        CaptureBlockData *hoisted__CaptureBlockData_3430 = get_payload(self);
        (void)hoisted__CaptureBlockData_3430;
        (void)hoisted__CaptureBlockData_3430;
        Bool hoisted__Bool_3431 = 0;
        (void)hoisted__Bool_3431;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3430, hoisted__Bool_3431);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3725 = 1;
    (void)hoisted__U32_3725;
    Bool hoisted__Bool_3726 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3726;
    if (hoisted__Bool_3726) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    U32 hoisted__U32_3727 = 1;
    (void)hoisted__U32_3727;
    Bool hoisted__Bool_3728 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3728;
    if (hoisted__Bool_3728) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3697 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3697;
        NodeType *hoisted__NodeType_3698 = NodeType_Literal(hoisted__Literal_3697);
        (void)hoisted__NodeType_3698;
        { NodeType * _ret_val = hoisted__NodeType_3698;
                return _ret_val; }
    }
    U32 hoisted__U32_3729 = 1;
    (void)hoisted__U32_3729;
    Bool hoisted__Bool_3730 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3730;
    if (hoisted__Bool_3730) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3699 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3699;
        NodeType *hoisted__NodeType_3700 = NodeType_Ident(hoisted__IdentData_3699);
        (void)hoisted__NodeType_3700;
        { NodeType * _ret_val = hoisted__NodeType_3700;
                return _ret_val; }
    }
    U32 hoisted__U32_3731 = 1;
    (void)hoisted__U32_3731;
    Bool hoisted__Bool_3732 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3732;
    if (hoisted__Bool_3732) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3701 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3701;
        NodeType *hoisted__NodeType_3702 = NodeType_Decl(hoisted__Declaration_3701);
        (void)hoisted__NodeType_3702;
        { NodeType * _ret_val = hoisted__NodeType_3702;
                return _ret_val; }
    }
    U32 hoisted__U32_3733 = 1;
    (void)hoisted__U32_3733;
    Bool hoisted__Bool_3734 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3734;
    if (hoisted__Bool_3734) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3703 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3703;
        NodeType *hoisted__NodeType_3704 = NodeType_Assign(hoisted__AssignData_3703);
        (void)hoisted__NodeType_3704;
        { NodeType * _ret_val = hoisted__NodeType_3704;
                return _ret_val; }
    }
    U32 hoisted__U32_3735 = 1;
    (void)hoisted__U32_3735;
    Bool hoisted__Bool_3736 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3736;
    if (hoisted__Bool_3736) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3705 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3705;
        NodeType *hoisted__NodeType_3706 = NodeType_FCall(hoisted__FCallData_3705);
        (void)hoisted__NodeType_3706;
        { NodeType * _ret_val = hoisted__NodeType_3706;
                return _ret_val; }
    }
    U32 hoisted__U32_3737 = 1;
    (void)hoisted__U32_3737;
    Bool hoisted__Bool_3738 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3738;
    if (hoisted__Bool_3738) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3707 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3707;
        NodeType *hoisted__NodeType_3708 = NodeType_FuncDef(hoisted__FunctionDef_3707);
        (void)hoisted__NodeType_3708;
        { NodeType * _ret_val = hoisted__NodeType_3708;
                return _ret_val; }
    }
    U32 hoisted__U32_3739 = 1;
    (void)hoisted__U32_3739;
    Bool hoisted__Bool_3740 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3740;
    if (hoisted__Bool_3740) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3709 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3709;
        NodeType *hoisted__NodeType_3710 = NodeType_StructDef(hoisted__StructDef_3709);
        (void)hoisted__NodeType_3710;
        { NodeType * _ret_val = hoisted__NodeType_3710;
                return _ret_val; }
    }
    U32 hoisted__U32_3741 = 1;
    (void)hoisted__U32_3741;
    Bool hoisted__Bool_3742 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3742;
    if (hoisted__Bool_3742) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3711 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3711;
        NodeType *hoisted__NodeType_3712 = NodeType_EnumDef(hoisted__EnumDef_3711);
        (void)hoisted__NodeType_3712;
        { NodeType * _ret_val = hoisted__NodeType_3712;
                return _ret_val; }
    }
    U32 hoisted__U32_3743 = 1;
    (void)hoisted__U32_3743;
    Bool hoisted__Bool_3744 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3744;
    if (hoisted__Bool_3744) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3713 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3713;
        NodeType *hoisted__NodeType_3714 = NodeType_FieldAccess(hoisted__FieldAccessData_3713);
        (void)hoisted__NodeType_3714;
        { NodeType * _ret_val = hoisted__NodeType_3714;
                return _ret_val; }
    }
    U32 hoisted__U32_3745 = 1;
    (void)hoisted__U32_3745;
    Bool hoisted__Bool_3746 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3746;
    if (hoisted__Bool_3746) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3715 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3715;
        NodeType *hoisted__NodeType_3716 = NodeType_FieldAssign(hoisted__FieldAssignData_3715);
        (void)hoisted__NodeType_3716;
        { NodeType * _ret_val = hoisted__NodeType_3716;
                return _ret_val; }
    }
    U32 hoisted__U32_3747 = 1;
    (void)hoisted__U32_3747;
    Bool hoisted__Bool_3748 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3748;
    if (hoisted__Bool_3748) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    U32 hoisted__U32_3749 = 1;
    (void)hoisted__U32_3749;
    Bool hoisted__Bool_3750 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3750;
    if (hoisted__Bool_3750) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    U32 hoisted__U32_3751 = 1;
    (void)hoisted__U32_3751;
    Bool hoisted__Bool_3752 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3752;
    if (hoisted__Bool_3752) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    U32 hoisted__U32_3753 = 1;
    (void)hoisted__U32_3753;
    Bool hoisted__Bool_3754 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3754;
    if (hoisted__Bool_3754) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3717 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3717;
        NodeType *hoisted__NodeType_3718 = NodeType_ForIn(hoisted__ForInData_3717);
        (void)hoisted__NodeType_3718;
        { NodeType * _ret_val = hoisted__NodeType_3718;
                return _ret_val; }
    }
    U32 hoisted__U32_3755 = 1;
    (void)hoisted__U32_3755;
    Bool hoisted__Bool_3756 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3756;
    if (hoisted__Bool_3756) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3719 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3719;
        NodeType *hoisted__NodeType_3720 = NodeType_NamedArg(hoisted__Str_3719);
        (void)hoisted__NodeType_3720;
        { NodeType * _ret_val = hoisted__NodeType_3720;
                return _ret_val; }
    }
    U32 hoisted__U32_3757 = 1;
    (void)hoisted__U32_3757;
    Bool hoisted__Bool_3758 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3758;
    if (hoisted__Bool_3758) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    U32 hoisted__U32_3759 = 1;
    (void)hoisted__U32_3759;
    Bool hoisted__Bool_3760 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3760;
    if (hoisted__Bool_3760) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    U32 hoisted__U32_3761 = 1;
    (void)hoisted__U32_3761;
    Bool hoisted__Bool_3762 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3762;
    if (hoisted__Bool_3762) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    U32 hoisted__U32_3763 = 1;
    (void)hoisted__U32_3763;
    Bool hoisted__Bool_3764 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3764;
    if (hoisted__Bool_3764) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3721 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3721;
        NodeType *hoisted__NodeType_3722 = NodeType_Match(hoisted__MatchData_3721);
        (void)hoisted__NodeType_3722;
        { NodeType * _ret_val = hoisted__NodeType_3722;
                return _ret_val; }
    }
    U32 hoisted__U32_3765 = 1;
    (void)hoisted__U32_3765;
    Bool hoisted__Bool_3766 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3766;
    if (hoisted__Bool_3766) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    U32 hoisted__U32_3767 = 1;
    (void)hoisted__U32_3767;
    Bool hoisted__Bool_3768 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3768;
    if (hoisted__Bool_3768) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    U32 hoisted__U32_3769 = 1;
    (void)hoisted__U32_3769;
    Bool hoisted__Bool_3770 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3770;
    if (hoisted__Bool_3770) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    U32 hoisted__U32_3771 = 1;
    (void)hoisted__U32_3771;
    Bool hoisted__Bool_3772 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3772;
    if (hoisted__Bool_3772) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    U32 hoisted__U32_3773 = 1;
    (void)hoisted__U32_3773;
    Bool hoisted__Bool_3774 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3774;
    if (hoisted__Bool_3774) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    U32 hoisted__U32_3775 = 1;
    (void)hoisted__U32_3775;
    Bool hoisted__Bool_3776 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3776;
    if (hoisted__Bool_3776) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3723 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3723;
        NodeType *hoisted__NodeType_3724 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3723);
        (void)hoisted__NodeType_3724;
        { NodeType * _ret_val = hoisted__NodeType_3724;
                return _ret_val; }
    }
    U32 hoisted__U32_3777 = 1;
    (void)hoisted__U32_3777;
    Bool hoisted__Bool_3778 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3778;
    if (hoisted__Bool_3778) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
                return _r; }
    }
    CaptureBlockData *_clone_payload_BodyValue_27 = get_payload(self);
    (void)_clone_payload_BodyValue_27;
    (void)_clone_payload_BodyValue_27;
    CaptureBlockData *hoisted__CaptureBlockData_3779 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
    (void)hoisted__CaptureBlockData_3779;
    NodeType *hoisted__NodeType_3780 = NodeType_BodyValue(hoisted__CaptureBlockData_3779);
    (void)hoisted__NodeType_3780;
    return hoisted__NodeType_3780;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3781 = 136;
    (void)hoisted__U32_3781;
    return hoisted__U32_3781;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3782 = is_null(self);
    (void)hoisted__Bool_3782;
    if (hoisted__Bool_3782) {
        return;
    }
    Bool hoisted__Bool_3783 = 0;
    (void)hoisted__Bool_3783;
    NodeType_delete(&self->node_type, hoisted__Bool_3783);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3833 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3833->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3833->children = *_ca; free(_ca); }
    hoisted__Expr_3833->line = line;
    hoisted__Expr_3833->col = col;
    (void)hoisted__Expr_3833;
    return hoisted__Expr_3833;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3842 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3842->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3842->children = *_ca; free(_ca); }
    hoisted__Expr_3842->line = self->line;
    hoisted__Expr_3842->col = self->col;
    (void)hoisted__Expr_3842;
    return hoisted__Expr_3842;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3843 = 0;
    (void)hoisted__U32_3843;
    U64 hoisted__U64_3844 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3843); });
    (void)hoisted__U64_3844;
    return hoisted__U64_3844;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3845 = 160;
    (void)hoisted__U32_3845;
    return hoisted__U32_3845;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4929 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4929->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4929->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4929;
    return hoisted__Map__I64_Str_4929;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_5042 = 0;
    (void)hoisted__Bool_5042;
    Vec__I64_delete(&self->keys, hoisted__Bool_5042);
    Bool hoisted__Bool_5043 = 0;
    (void)hoisted__Bool_5043;
    Vec__Str_delete(&self->values, hoisted__Bool_5043);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_5044 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_5044->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_5044->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_5044;
    return hoisted__Map__I64_Str_5044;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_5045 = 0;
    (void)hoisted__U32_5045;
    U64 hoisted__U64_5046 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5045); });
    (void)hoisted__U64_5046;
    return hoisted__U64_5046;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_5047 = 32;
    (void)hoisted__U32_5047;
    return hoisted__U32_5047;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_5048 = 1;
    (void)hoisted__U32_5048;
    U64 hoisted__U64_5049 = (U64)(hoisted__U32_5048);
    (void)hoisted__U64_5049;
    void * hoisted__v_5050 = malloc(hoisted__U64_5049);
    (void)hoisted__v_5050;
    U32 hoisted__U32_5051 = 0;
    (void)hoisted__U32_5051;
    I64 hoisted__I64_5052 = 1;
    (void)hoisted__I64_5052;
    Vec__Bool *hoisted__Vec__Bool_5053 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5053->data = hoisted__v_5050;
    hoisted__Vec__Bool_5053->count = hoisted__U32_5051;
    hoisted__Vec__Bool_5053->cap = hoisted__I64_5052;
    (void)hoisted__Vec__Bool_5053;
    return hoisted__Vec__Bool_5053;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_5063 = self->count;
        (void)_re_U32_5063;
        U32 _rc_U32_5063 = 0;
        (void)_rc_U32_5063;
        Bool hoisted__Bool_5076 = ((Bool)(_rc_U32_5063 <= _re_U32_5063));
        (void)hoisted__Bool_5076;
        if (hoisted__Bool_5076) {
            while (1) {
                Bool _wcond_Bool_5064 = ((Bool)(_rc_U32_5063 < _re_U32_5063));
                (void)_wcond_Bool_5064;
                if (_wcond_Bool_5064) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5063);
                U32_inc(&_rc_U32_5063);
                U32 hoisted__U32_5065 = 1;
                (void)hoisted__U32_5065;
                U32 hoisted__U32_5066 = ((U32)(i * hoisted__U32_5065));
                (void)hoisted__U32_5066;
                U64 hoisted__U64_5067 = (U64)(hoisted__U32_5066);
                (void)hoisted__U64_5067;
                Bool *hoisted__Bool_5068 = ptr_add(self->data, hoisted__U64_5067);
                (void)hoisted__Bool_5068;
                (void)hoisted__Bool_5068;
                Bool hoisted__Bool_5069 = 0;
                (void)hoisted__Bool_5069;
                Bool_delete(hoisted__Bool_5068, hoisted__Bool_5069);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5070 = ((Bool)(_rc_U32_5063 > _re_U32_5063));
                (void)_wcond_Bool_5070;
                if (_wcond_Bool_5070) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5063);
                U32_dec(&_rc_U32_5063);
                U32 hoisted__U32_5071 = 1;
                (void)hoisted__U32_5071;
                U32 hoisted__U32_5072 = ((U32)(i * hoisted__U32_5071));
                (void)hoisted__U32_5072;
                U64 hoisted__U64_5073 = (U64)(hoisted__U32_5072);
                (void)hoisted__U64_5073;
                Bool *hoisted__Bool_5074 = ptr_add(self->data, hoisted__U64_5073);
                (void)hoisted__Bool_5074;
                (void)hoisted__Bool_5074;
                Bool hoisted__Bool_5075 = 0;
                (void)hoisted__Bool_5075;
                Bool_delete(hoisted__Bool_5074, hoisted__Bool_5075);
            }
        }
    }
    U32 hoisted__U32_5077 = 0;
    (void)hoisted__U32_5077;
    self->count = hoisted__U32_5077;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_5347 = 1;
    (void)hoisted__U32_5347;
    U32 hoisted__U32_5348 = ((U32)(self->cap * hoisted__U32_5347));
    (void)hoisted__U32_5348;
    U64 hoisted__U64_5349 = (U64)(hoisted__U32_5348);
    (void)hoisted__U64_5349;
    void * new_data = malloc(hoisted__U64_5349);
    {
        U32 _re_U32_5319 = self->count;
        (void)_re_U32_5319;
        U32 _rc_U32_5319 = 0;
        (void)_rc_U32_5319;
        Bool hoisted__Bool_5346 = ((Bool)(_rc_U32_5319 <= _re_U32_5319));
        (void)hoisted__Bool_5346;
        if (hoisted__Bool_5346) {
            while (1) {
                Bool _wcond_Bool_5320 = ((Bool)(_rc_U32_5319 < _re_U32_5319));
                (void)_wcond_Bool_5320;
                if (_wcond_Bool_5320) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5319);
                U32_inc(&_rc_U32_5319);
                U32 hoisted__U32_5321 = 1;
                (void)hoisted__U32_5321;
                U32 hoisted__U32_5322 = ((U32)(i * hoisted__U32_5321));
                (void)hoisted__U32_5322;
                U64 hoisted__U64_5323 = (U64)(hoisted__U32_5322);
                (void)hoisted__U64_5323;
                Bool *src = ptr_add(self->data, hoisted__U64_5323);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_5324 = 1;
                (void)hoisted__U32_5324;
                U32 hoisted__U32_5325 = ((U32)(i * hoisted__U32_5324));
                (void)hoisted__U32_5325;
                U64 hoisted__U64_5326 = (U64)(hoisted__U32_5325);
                (void)hoisted__U64_5326;
                U32 hoisted__U32_5327 = 1;
                (void)hoisted__U32_5327;
                void *hoisted__v_5328 = ptr_add(new_data, hoisted__U64_5326);
                (void)hoisted__v_5328;
                (void)hoisted__v_5328;
                U64 hoisted__U64_5329 = (U64)(hoisted__U32_5327);
                (void)hoisted__U64_5329;
                memcpy(hoisted__v_5328, &cloned, hoisted__U64_5329);
                U32 hoisted__U32_5330 = 1;
                (void)hoisted__U32_5330;
                I32 hoisted__I32_5331 = 0;
                (void)hoisted__I32_5331;
                U64 hoisted__U64_5332 = (U64)(hoisted__U32_5330);
                (void)hoisted__U64_5332;
                memset(&cloned, hoisted__I32_5331, hoisted__U64_5332);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5333 = ((Bool)(_rc_U32_5319 > _re_U32_5319));
                (void)_wcond_Bool_5333;
                if (_wcond_Bool_5333) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5319);
                U32_dec(&_rc_U32_5319);
                U32 hoisted__U32_5334 = 1;
                (void)hoisted__U32_5334;
                U32 hoisted__U32_5335 = ((U32)(i * hoisted__U32_5334));
                (void)hoisted__U32_5335;
                U64 hoisted__U64_5336 = (U64)(hoisted__U32_5335);
                (void)hoisted__U64_5336;
                Bool *src = ptr_add(self->data, hoisted__U64_5336);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_5337 = 1;
                (void)hoisted__U32_5337;
                U32 hoisted__U32_5338 = ((U32)(i * hoisted__U32_5337));
                (void)hoisted__U32_5338;
                U64 hoisted__U64_5339 = (U64)(hoisted__U32_5338);
                (void)hoisted__U64_5339;
                U32 hoisted__U32_5340 = 1;
                (void)hoisted__U32_5340;
                void *hoisted__v_5341 = ptr_add(new_data, hoisted__U64_5339);
                (void)hoisted__v_5341;
                (void)hoisted__v_5341;
                U64 hoisted__U64_5342 = (U64)(hoisted__U32_5340);
                (void)hoisted__U64_5342;
                memcpy(hoisted__v_5341, &cloned, hoisted__U64_5342);
                U32 hoisted__U32_5343 = 1;
                (void)hoisted__U32_5343;
                I32 hoisted__I32_5344 = 0;
                (void)hoisted__I32_5344;
                U64 hoisted__U64_5345 = (U64)(hoisted__U32_5343);
                (void)hoisted__U64_5345;
                memset(&cloned, hoisted__I32_5344, hoisted__U64_5345);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_5350 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_5350->data = new_data;
    hoisted__Vec__Bool_5350->count = self->count;
    hoisted__Vec__Bool_5350->cap = self->cap;
    (void)hoisted__Vec__Bool_5350;
    return hoisted__Vec__Bool_5350;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_5351 = 16;
    (void)hoisted__U32_5351;
    return hoisted__U32_5351;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5352 = 8;
    (void)hoisted__U32_5352;
    U64 hoisted__U64_5353 = (U64)(hoisted__U32_5352);
    (void)hoisted__U64_5353;
    void * hoisted__v_5354 = malloc(hoisted__U64_5353);
    (void)hoisted__v_5354;
    U32 hoisted__U32_5355 = 0;
    (void)hoisted__U32_5355;
    I64 hoisted__I64_5356 = 1;
    (void)hoisted__I64_5356;
    Vec__I64 *hoisted__Vec__I64_5357 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5357->data = hoisted__v_5354;
    hoisted__Vec__I64_5357->count = hoisted__U32_5355;
    hoisted__Vec__I64_5357->cap = hoisted__I64_5356;
    (void)hoisted__Vec__I64_5357;
    return hoisted__Vec__I64_5357;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5367 = self->count;
        (void)_re_U32_5367;
        U32 _rc_U32_5367 = 0;
        (void)_rc_U32_5367;
        Bool hoisted__Bool_5380 = ((Bool)(_rc_U32_5367 <= _re_U32_5367));
        (void)hoisted__Bool_5380;
        if (hoisted__Bool_5380) {
            while (1) {
                Bool _wcond_Bool_5368 = ((Bool)(_rc_U32_5367 < _re_U32_5367));
                (void)_wcond_Bool_5368;
                if (_wcond_Bool_5368) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5367);
                U32_inc(&_rc_U32_5367);
                U32 hoisted__U32_5369 = 8;
                (void)hoisted__U32_5369;
                U32 hoisted__U32_5370 = ((U32)(i * hoisted__U32_5369));
                (void)hoisted__U32_5370;
                U64 hoisted__U64_5371 = (U64)(hoisted__U32_5370);
                (void)hoisted__U64_5371;
                I64 *hoisted__I64_5372 = ptr_add(self->data, hoisted__U64_5371);
                (void)hoisted__I64_5372;
                (void)hoisted__I64_5372;
                Bool hoisted__Bool_5373 = 0;
                (void)hoisted__Bool_5373;
                I64_delete(hoisted__I64_5372, hoisted__Bool_5373);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5374 = ((Bool)(_rc_U32_5367 > _re_U32_5367));
                (void)_wcond_Bool_5374;
                if (_wcond_Bool_5374) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5367);
                U32_dec(&_rc_U32_5367);
                U32 hoisted__U32_5375 = 8;
                (void)hoisted__U32_5375;
                U32 hoisted__U32_5376 = ((U32)(i * hoisted__U32_5375));
                (void)hoisted__U32_5376;
                U64 hoisted__U64_5377 = (U64)(hoisted__U32_5376);
                (void)hoisted__U64_5377;
                I64 *hoisted__I64_5378 = ptr_add(self->data, hoisted__U64_5377);
                (void)hoisted__I64_5378;
                (void)hoisted__I64_5378;
                Bool hoisted__Bool_5379 = 0;
                (void)hoisted__Bool_5379;
                I64_delete(hoisted__I64_5378, hoisted__Bool_5379);
            }
        }
    }
    U32 hoisted__U32_5381 = 0;
    (void)hoisted__U32_5381;
    self->count = hoisted__U32_5381;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5651 = 8;
    (void)hoisted__U32_5651;
    U32 hoisted__U32_5652 = ((U32)(self->cap * hoisted__U32_5651));
    (void)hoisted__U32_5652;
    U64 hoisted__U64_5653 = (U64)(hoisted__U32_5652);
    (void)hoisted__U64_5653;
    void * new_data = malloc(hoisted__U64_5653);
    {
        U32 _re_U32_5623 = self->count;
        (void)_re_U32_5623;
        U32 _rc_U32_5623 = 0;
        (void)_rc_U32_5623;
        Bool hoisted__Bool_5650 = ((Bool)(_rc_U32_5623 <= _re_U32_5623));
        (void)hoisted__Bool_5650;
        if (hoisted__Bool_5650) {
            while (1) {
                Bool _wcond_Bool_5624 = ((Bool)(_rc_U32_5623 < _re_U32_5623));
                (void)_wcond_Bool_5624;
                if (_wcond_Bool_5624) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5623);
                U32_inc(&_rc_U32_5623);
                U32 hoisted__U32_5625 = 8;
                (void)hoisted__U32_5625;
                U32 hoisted__U32_5626 = ((U32)(i * hoisted__U32_5625));
                (void)hoisted__U32_5626;
                U64 hoisted__U64_5627 = (U64)(hoisted__U32_5626);
                (void)hoisted__U64_5627;
                I64 *src = ptr_add(self->data, hoisted__U64_5627);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5628 = 8;
                (void)hoisted__U32_5628;
                U32 hoisted__U32_5629 = ((U32)(i * hoisted__U32_5628));
                (void)hoisted__U32_5629;
                U64 hoisted__U64_5630 = (U64)(hoisted__U32_5629);
                (void)hoisted__U64_5630;
                U32 hoisted__U32_5631 = 8;
                (void)hoisted__U32_5631;
                void *hoisted__v_5632 = ptr_add(new_data, hoisted__U64_5630);
                (void)hoisted__v_5632;
                (void)hoisted__v_5632;
                U64 hoisted__U64_5633 = (U64)(hoisted__U32_5631);
                (void)hoisted__U64_5633;
                memcpy(hoisted__v_5632, &cloned, hoisted__U64_5633);
                U32 hoisted__U32_5634 = 8;
                (void)hoisted__U32_5634;
                I32 hoisted__I32_5635 = 0;
                (void)hoisted__I32_5635;
                U64 hoisted__U64_5636 = (U64)(hoisted__U32_5634);
                (void)hoisted__U64_5636;
                memset(&cloned, hoisted__I32_5635, hoisted__U64_5636);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5637 = ((Bool)(_rc_U32_5623 > _re_U32_5623));
                (void)_wcond_Bool_5637;
                if (_wcond_Bool_5637) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5623);
                U32_dec(&_rc_U32_5623);
                U32 hoisted__U32_5638 = 8;
                (void)hoisted__U32_5638;
                U32 hoisted__U32_5639 = ((U32)(i * hoisted__U32_5638));
                (void)hoisted__U32_5639;
                U64 hoisted__U64_5640 = (U64)(hoisted__U32_5639);
                (void)hoisted__U64_5640;
                I64 *src = ptr_add(self->data, hoisted__U64_5640);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5641 = 8;
                (void)hoisted__U32_5641;
                U32 hoisted__U32_5642 = ((U32)(i * hoisted__U32_5641));
                (void)hoisted__U32_5642;
                U64 hoisted__U64_5643 = (U64)(hoisted__U32_5642);
                (void)hoisted__U64_5643;
                U32 hoisted__U32_5644 = 8;
                (void)hoisted__U32_5644;
                void *hoisted__v_5645 = ptr_add(new_data, hoisted__U64_5643);
                (void)hoisted__v_5645;
                (void)hoisted__v_5645;
                U64 hoisted__U64_5646 = (U64)(hoisted__U32_5644);
                (void)hoisted__U64_5646;
                memcpy(hoisted__v_5645, &cloned, hoisted__U64_5646);
                U32 hoisted__U32_5647 = 8;
                (void)hoisted__U32_5647;
                I32 hoisted__I32_5648 = 0;
                (void)hoisted__I32_5648;
                U64 hoisted__U64_5649 = (U64)(hoisted__U32_5647);
                (void)hoisted__U64_5649;
                memset(&cloned, hoisted__I32_5648, hoisted__U64_5649);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5654 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5654->data = new_data;
    hoisted__Vec__I64_5654->count = self->count;
    hoisted__Vec__I64_5654->cap = self->cap;
    (void)hoisted__Vec__I64_5654;
    return hoisted__Vec__I64_5654;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5655 = 16;
    (void)hoisted__U32_5655;
    return hoisted__U32_5655;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5960 = 104;
    (void)hoisted__U32_5960;
    U64 hoisted__U64_5961 = (U64)(hoisted__U32_5960);
    (void)hoisted__U64_5961;
    void * hoisted__v_5962 = malloc(hoisted__U64_5961);
    (void)hoisted__v_5962;
    U32 hoisted__U32_5963 = 0;
    (void)hoisted__U32_5963;
    I64 hoisted__I64_5964 = 1;
    (void)hoisted__I64_5964;
    Vec__Declaration *hoisted__Vec__Declaration_5965 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5965->data = hoisted__v_5962;
    hoisted__Vec__Declaration_5965->count = hoisted__U32_5963;
    hoisted__Vec__Declaration_5965->cap = hoisted__I64_5964;
    (void)hoisted__Vec__Declaration_5965;
    return hoisted__Vec__Declaration_5965;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5975 = self->count;
        (void)_re_U32_5975;
        U32 _rc_U32_5975 = 0;
        (void)_rc_U32_5975;
        Bool hoisted__Bool_5988 = ((Bool)(_rc_U32_5975 <= _re_U32_5975));
        (void)hoisted__Bool_5988;
        if (hoisted__Bool_5988) {
            while (1) {
                Bool _wcond_Bool_5976 = ((Bool)(_rc_U32_5975 < _re_U32_5975));
                (void)_wcond_Bool_5976;
                if (_wcond_Bool_5976) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5975);
                U32_inc(&_rc_U32_5975);
                U32 hoisted__U32_5977 = 104;
                (void)hoisted__U32_5977;
                U32 hoisted__U32_5978 = ((U32)(i * hoisted__U32_5977));
                (void)hoisted__U32_5978;
                U64 hoisted__U64_5979 = (U64)(hoisted__U32_5978);
                (void)hoisted__U64_5979;
                Declaration *hoisted__Declaration_5980 = ptr_add(self->data, hoisted__U64_5979);
                (void)hoisted__Declaration_5980;
                (void)hoisted__Declaration_5980;
                Bool hoisted__Bool_5981 = 0;
                (void)hoisted__Bool_5981;
                Declaration_delete(hoisted__Declaration_5980, hoisted__Bool_5981);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5982 = ((Bool)(_rc_U32_5975 > _re_U32_5975));
                (void)_wcond_Bool_5982;
                if (_wcond_Bool_5982) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5975);
                U32_dec(&_rc_U32_5975);
                U32 hoisted__U32_5983 = 104;
                (void)hoisted__U32_5983;
                U32 hoisted__U32_5984 = ((U32)(i * hoisted__U32_5983));
                (void)hoisted__U32_5984;
                U64 hoisted__U64_5985 = (U64)(hoisted__U32_5984);
                (void)hoisted__U64_5985;
                Declaration *hoisted__Declaration_5986 = ptr_add(self->data, hoisted__U64_5985);
                (void)hoisted__Declaration_5986;
                (void)hoisted__Declaration_5986;
                Bool hoisted__Bool_5987 = 0;
                (void)hoisted__Bool_5987;
                Declaration_delete(hoisted__Declaration_5986, hoisted__Bool_5987);
            }
        }
    }
    U32 hoisted__U32_5989 = 0;
    (void)hoisted__U32_5989;
    self->count = hoisted__U32_5989;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_6259 = 104;
    (void)hoisted__U32_6259;
    U32 hoisted__U32_6260 = ((U32)(self->cap * hoisted__U32_6259));
    (void)hoisted__U32_6260;
    U64 hoisted__U64_6261 = (U64)(hoisted__U32_6260);
    (void)hoisted__U64_6261;
    void * new_data = malloc(hoisted__U64_6261);
    {
        U32 _re_U32_6231 = self->count;
        (void)_re_U32_6231;
        U32 _rc_U32_6231 = 0;
        (void)_rc_U32_6231;
        Bool hoisted__Bool_6258 = ((Bool)(_rc_U32_6231 <= _re_U32_6231));
        (void)hoisted__Bool_6258;
        if (hoisted__Bool_6258) {
            while (1) {
                Bool _wcond_Bool_6232 = ((Bool)(_rc_U32_6231 < _re_U32_6231));
                (void)_wcond_Bool_6232;
                if (_wcond_Bool_6232) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6231);
                U32_inc(&_rc_U32_6231);
                U32 hoisted__U32_6233 = 104;
                (void)hoisted__U32_6233;
                U32 hoisted__U32_6234 = ((U32)(i * hoisted__U32_6233));
                (void)hoisted__U32_6234;
                U64 hoisted__U64_6235 = (U64)(hoisted__U32_6234);
                (void)hoisted__U64_6235;
                Declaration *src = ptr_add(self->data, hoisted__U64_6235);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6236 = 104;
                (void)hoisted__U32_6236;
                U32 hoisted__U32_6237 = ((U32)(i * hoisted__U32_6236));
                (void)hoisted__U32_6237;
                U64 hoisted__U64_6238 = (U64)(hoisted__U32_6237);
                (void)hoisted__U64_6238;
                U32 hoisted__U32_6239 = 104;
                (void)hoisted__U32_6239;
                void *hoisted__v_6240 = ptr_add(new_data, hoisted__U64_6238);
                (void)hoisted__v_6240;
                (void)hoisted__v_6240;
                U64 hoisted__U64_6241 = (U64)(hoisted__U32_6239);
                (void)hoisted__U64_6241;
                memcpy(hoisted__v_6240, cloned, hoisted__U64_6241);
                U32 hoisted__U32_6242 = 104;
                (void)hoisted__U32_6242;
                I32 hoisted__I32_6243 = 0;
                (void)hoisted__I32_6243;
                U64 hoisted__U64_6244 = (U64)(hoisted__U32_6242);
                (void)hoisted__U64_6244;
                memset(cloned, hoisted__I32_6243, hoisted__U64_6244);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6245 = ((Bool)(_rc_U32_6231 > _re_U32_6231));
                (void)_wcond_Bool_6245;
                if (_wcond_Bool_6245) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6231);
                U32_dec(&_rc_U32_6231);
                U32 hoisted__U32_6246 = 104;
                (void)hoisted__U32_6246;
                U32 hoisted__U32_6247 = ((U32)(i * hoisted__U32_6246));
                (void)hoisted__U32_6247;
                U64 hoisted__U64_6248 = (U64)(hoisted__U32_6247);
                (void)hoisted__U64_6248;
                Declaration *src = ptr_add(self->data, hoisted__U64_6248);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_6249 = 104;
                (void)hoisted__U32_6249;
                U32 hoisted__U32_6250 = ((U32)(i * hoisted__U32_6249));
                (void)hoisted__U32_6250;
                U64 hoisted__U64_6251 = (U64)(hoisted__U32_6250);
                (void)hoisted__U64_6251;
                U32 hoisted__U32_6252 = 104;
                (void)hoisted__U32_6252;
                void *hoisted__v_6253 = ptr_add(new_data, hoisted__U64_6251);
                (void)hoisted__v_6253;
                (void)hoisted__v_6253;
                U64 hoisted__U64_6254 = (U64)(hoisted__U32_6252);
                (void)hoisted__U64_6254;
                memcpy(hoisted__v_6253, cloned, hoisted__U64_6254);
                U32 hoisted__U32_6255 = 104;
                (void)hoisted__U32_6255;
                I32 hoisted__I32_6256 = 0;
                (void)hoisted__I32_6256;
                U64 hoisted__U64_6257 = (U64)(hoisted__U32_6255);
                (void)hoisted__U64_6257;
                memset(cloned, hoisted__I32_6256, hoisted__U64_6257);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_6262 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_6262->data = new_data;
    hoisted__Vec__Declaration_6262->count = self->count;
    hoisted__Vec__Declaration_6262->cap = self->cap;
    (void)hoisted__Vec__Declaration_6262;
    return hoisted__Vec__Declaration_6262;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_6263 = 16;
    (void)hoisted__U32_6263;
    return hoisted__U32_6263;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_6264 = 160;
    (void)hoisted__U32_6264;
    U64 hoisted__U64_6265 = (U64)(hoisted__U32_6264);
    (void)hoisted__U64_6265;
    void * hoisted__v_6266 = malloc(hoisted__U64_6265);
    (void)hoisted__v_6266;
    U32 hoisted__U32_6267 = 0;
    (void)hoisted__U32_6267;
    I64 hoisted__I64_6268 = 1;
    (void)hoisted__I64_6268;
    Vec__Expr *hoisted__Vec__Expr_6269 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6269->data = hoisted__v_6266;
    hoisted__Vec__Expr_6269->count = hoisted__U32_6267;
    hoisted__Vec__Expr_6269->cap = hoisted__I64_6268;
    (void)hoisted__Vec__Expr_6269;
    return hoisted__Vec__Expr_6269;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_6279 = self->count;
        (void)_re_U32_6279;
        U32 _rc_U32_6279 = 0;
        (void)_rc_U32_6279;
        Bool hoisted__Bool_6292 = ((Bool)(_rc_U32_6279 <= _re_U32_6279));
        (void)hoisted__Bool_6292;
        if (hoisted__Bool_6292) {
            while (1) {
                Bool _wcond_Bool_6280 = ((Bool)(_rc_U32_6279 < _re_U32_6279));
                (void)_wcond_Bool_6280;
                if (_wcond_Bool_6280) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6279);
                U32_inc(&_rc_U32_6279);
                U32 hoisted__U32_6281 = 160;
                (void)hoisted__U32_6281;
                U32 hoisted__U32_6282 = ((U32)(i * hoisted__U32_6281));
                (void)hoisted__U32_6282;
                U64 hoisted__U64_6283 = (U64)(hoisted__U32_6282);
                (void)hoisted__U64_6283;
                Expr *hoisted__Expr_6284 = ptr_add(self->data, hoisted__U64_6283);
                (void)hoisted__Expr_6284;
                (void)hoisted__Expr_6284;
                Bool hoisted__Bool_6285 = 0;
                (void)hoisted__Bool_6285;
                Expr_delete(hoisted__Expr_6284, hoisted__Bool_6285);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6286 = ((Bool)(_rc_U32_6279 > _re_U32_6279));
                (void)_wcond_Bool_6286;
                if (_wcond_Bool_6286) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6279);
                U32_dec(&_rc_U32_6279);
                U32 hoisted__U32_6287 = 160;
                (void)hoisted__U32_6287;
                U32 hoisted__U32_6288 = ((U32)(i * hoisted__U32_6287));
                (void)hoisted__U32_6288;
                U64 hoisted__U64_6289 = (U64)(hoisted__U32_6288);
                (void)hoisted__U64_6289;
                Expr *hoisted__Expr_6290 = ptr_add(self->data, hoisted__U64_6289);
                (void)hoisted__Expr_6290;
                (void)hoisted__Expr_6290;
                Bool hoisted__Bool_6291 = 0;
                (void)hoisted__Bool_6291;
                Expr_delete(hoisted__Expr_6290, hoisted__Bool_6291);
            }
        }
    }
    U32 hoisted__U32_6293 = 0;
    (void)hoisted__U32_6293;
    self->count = hoisted__U32_6293;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_6563 = 160;
    (void)hoisted__U32_6563;
    U32 hoisted__U32_6564 = ((U32)(self->cap * hoisted__U32_6563));
    (void)hoisted__U32_6564;
    U64 hoisted__U64_6565 = (U64)(hoisted__U32_6564);
    (void)hoisted__U64_6565;
    void * new_data = malloc(hoisted__U64_6565);
    {
        U32 _re_U32_6535 = self->count;
        (void)_re_U32_6535;
        U32 _rc_U32_6535 = 0;
        (void)_rc_U32_6535;
        Bool hoisted__Bool_6562 = ((Bool)(_rc_U32_6535 <= _re_U32_6535));
        (void)hoisted__Bool_6562;
        if (hoisted__Bool_6562) {
            while (1) {
                Bool _wcond_Bool_6536 = ((Bool)(_rc_U32_6535 < _re_U32_6535));
                (void)_wcond_Bool_6536;
                if (_wcond_Bool_6536) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6535);
                U32_inc(&_rc_U32_6535);
                U32 hoisted__U32_6537 = 160;
                (void)hoisted__U32_6537;
                U32 hoisted__U32_6538 = ((U32)(i * hoisted__U32_6537));
                (void)hoisted__U32_6538;
                U64 hoisted__U64_6539 = (U64)(hoisted__U32_6538);
                (void)hoisted__U64_6539;
                Expr *src = ptr_add(self->data, hoisted__U64_6539);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6540 = 160;
                (void)hoisted__U32_6540;
                U32 hoisted__U32_6541 = ((U32)(i * hoisted__U32_6540));
                (void)hoisted__U32_6541;
                U64 hoisted__U64_6542 = (U64)(hoisted__U32_6541);
                (void)hoisted__U64_6542;
                U32 hoisted__U32_6543 = 160;
                (void)hoisted__U32_6543;
                void *hoisted__v_6544 = ptr_add(new_data, hoisted__U64_6542);
                (void)hoisted__v_6544;
                (void)hoisted__v_6544;
                U64 hoisted__U64_6545 = (U64)(hoisted__U32_6543);
                (void)hoisted__U64_6545;
                memcpy(hoisted__v_6544, cloned, hoisted__U64_6545);
                U32 hoisted__U32_6546 = 160;
                (void)hoisted__U32_6546;
                I32 hoisted__I32_6547 = 0;
                (void)hoisted__I32_6547;
                U64 hoisted__U64_6548 = (U64)(hoisted__U32_6546);
                (void)hoisted__U64_6548;
                memset(cloned, hoisted__I32_6547, hoisted__U64_6548);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6549 = ((Bool)(_rc_U32_6535 > _re_U32_6535));
                (void)_wcond_Bool_6549;
                if (_wcond_Bool_6549) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6535);
                U32_dec(&_rc_U32_6535);
                U32 hoisted__U32_6550 = 160;
                (void)hoisted__U32_6550;
                U32 hoisted__U32_6551 = ((U32)(i * hoisted__U32_6550));
                (void)hoisted__U32_6551;
                U64 hoisted__U64_6552 = (U64)(hoisted__U32_6551);
                (void)hoisted__U64_6552;
                Expr *src = ptr_add(self->data, hoisted__U64_6552);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6553 = 160;
                (void)hoisted__U32_6553;
                U32 hoisted__U32_6554 = ((U32)(i * hoisted__U32_6553));
                (void)hoisted__U32_6554;
                U64 hoisted__U64_6555 = (U64)(hoisted__U32_6554);
                (void)hoisted__U64_6555;
                U32 hoisted__U32_6556 = 160;
                (void)hoisted__U32_6556;
                void *hoisted__v_6557 = ptr_add(new_data, hoisted__U64_6555);
                (void)hoisted__v_6557;
                (void)hoisted__v_6557;
                U64 hoisted__U64_6558 = (U64)(hoisted__U32_6556);
                (void)hoisted__U64_6558;
                memcpy(hoisted__v_6557, cloned, hoisted__U64_6558);
                U32 hoisted__U32_6559 = 160;
                (void)hoisted__U32_6559;
                I32 hoisted__I32_6560 = 0;
                (void)hoisted__I32_6560;
                U64 hoisted__U64_6561 = (U64)(hoisted__U32_6559);
                (void)hoisted__U64_6561;
                memset(cloned, hoisted__I32_6560, hoisted__U64_6561);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6566 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6566->data = new_data;
    hoisted__Vec__Expr_6566->count = self->count;
    hoisted__Vec__Expr_6566->cap = self->cap;
    (void)hoisted__Vec__Expr_6566;
    return hoisted__Vec__Expr_6566;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_6567 = 16;
    (void)hoisted__U32_6567;
    return hoisted__U32_6567;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7655 = 3;
    (void)hoisted__U32_7655;
    Array__Str *_va_Array_207 = Array__Str_new(hoisted__U32_7655);
    (void)_va_Array_207;
    I64 _va_Array_207_ek = 0;
    (void)_va_Array_207_ek;
    OutOfBounds *_va_Array_207_eo = malloc(sizeof(OutOfBounds));
    _va_Array_207_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_207_eo;
    U32 hoisted__U32_7656 = 0;
    (void)hoisted__U32_7656;
    Str *hoisted__Str_7657 = Str_clone(loc);
    (void)hoisted__Str_7657;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_207, hoisted__U32_7656, hoisted__Str_7657, &_va_Array_207_ek, _va_Array_207_eo, &_til_str_lit_144);
    Str_delete(&_til_str_lit_144, (Bool){0});
    U32 hoisted__U32_7659 = 1;
    (void)hoisted__U32_7659;
    (void)_til_str_lit_145;
    (void)_til_str_lit_145;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_207, hoisted__U32_7659, &_til_str_lit_145, &_va_Array_207_ek, _va_Array_207_eo, &_til_str_lit_144);
    Str_delete(&_til_str_lit_144, (Bool){0});
    Array__Str *hoisted__Array__Str_7662 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7662;
    U32 hoisted__U32_7663 = 2;
    (void)hoisted__U32_7663;
    Str *hoisted__Str_7664 = format(hoisted__Array__Str_7662);
    (void)hoisted__Str_7664;
    (void)_til_str_lit_144;
    (void)_til_str_lit_144;
    Array__Str_set(_va_Array_207, hoisted__U32_7663, hoisted__Str_7664, &_va_Array_207_ek, _va_Array_207_eo, &_til_str_lit_144);
    OutOfBounds_delete(_va_Array_207_eo, 1);
    Str_delete(&_til_str_lit_144, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_207);
    I64 hoisted__I64_7666 = 1;
    (void)hoisted__I64_7666;
    exit(hoisted__I64_7666);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7675 = 1;
    (void)hoisted__U32_7675;
    Array__Str *_va_Array_209 = Array__Str_new(hoisted__U32_7675);
    (void)_va_Array_209;
    I64 _va_Array_209_ek = 0;
    (void)_va_Array_209_ek;
    OutOfBounds *_va_Array_209_eo = malloc(sizeof(OutOfBounds));
    _va_Array_209_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_209_eo;
    U32 hoisted__U32_7676 = 0;
    (void)hoisted__U32_7676;
    (void)_til_str_lit_146;
    (void)_til_str_lit_146;
    (void)_til_str_lit_147;
    (void)_til_str_lit_147;
    Array__Str_set(_va_Array_209, hoisted__U32_7676, &_til_str_lit_146, &_va_Array_209_ek, _va_Array_209_eo, &_til_str_lit_147);
    OutOfBounds_delete(_va_Array_209_eo, 1);
    Str_delete(&_til_str_lit_147, (Bool){0});
    panic(_va_Array_209, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7683 = not(cond);
    (void)hoisted__Bool_7683;
    if (hoisted__Bool_7683) {
        U32 hoisted__U32_7679 = 1;
        (void)hoisted__U32_7679;
        Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7679);
        (void)_va_Array_210;
        I64 _va_Array_210_ek = 0;
        (void)_va_Array_210_ek;
        OutOfBounds *_va_Array_210_eo = malloc(sizeof(OutOfBounds));
        _va_Array_210_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_210_eo;
        U32 hoisted__U32_7680 = 0;
        (void)hoisted__U32_7680;
        (void)_til_str_lit_148;
        (void)_til_str_lit_148;
        (void)_til_str_lit_149;
        (void)_til_str_lit_149;
        Array__Str_set(_va_Array_210, hoisted__U32_7680, &_til_str_lit_148, &_va_Array_210_ek, _va_Array_210_eo, &_til_str_lit_149);
        OutOfBounds_delete(_va_Array_210_eo, 1);
        Str_delete(&_til_str_lit_149, (Bool){0});
        panic(_va_Array_210, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7693 = parts;
        (void)_fc_Array__Str_7693;
        (void)_fc_Array__Str_7693;
        U32 _fi_USize_7693 = 0;
        (void)_fi_USize_7693;
        while (1) {
            U32 hoisted__U32_7695 = Array__Str_len(_fc_Array__Str_7693);
            (void)hoisted__U32_7695;
            Bool _wcond_Bool_7694 = ((Bool)(_fi_USize_7693 < hoisted__U32_7695));
            (void)_wcond_Bool_7694;
            if (_wcond_Bool_7694) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7693, &_fi_USize_7693);
            U32 hoisted__U32_7696 = 1;
            (void)hoisted__U32_7696;
            U32 hoisted__U32_7697 = ((U32)(_fi_USize_7693 + hoisted__U32_7696));
            (void)hoisted__U32_7697;
            _fi_USize_7693 = hoisted__U32_7697;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7731 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7731;
    return hoisted__Bool_7731;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7740 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7740;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7740;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7741 = 0;
    (void)hoisted__U32_7741;
    U64 hoisted__U64_7742 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7741); });
    (void)hoisted__U64_7742;
    return hoisted__U64_7742;
}

U32 Range_size(void) {
    U32 hoisted__U32_7773 = 16;
    (void)hoisted__U32_7773;
    return hoisted__U32_7773;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7789 = 3;
    (void)hoisted__I64_7789;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    assert_eq__I64(result, hoisted__I64_7789, &_til_str_lit_152);
    Str_delete(&_til_str_lit_152, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7797 = 15;
    (void)hoisted__I64_7797;
    (void)_til_str_lit_153;
    (void)_til_str_lit_153;
    assert_eq__I64(result, hoisted__I64_7797, &_til_str_lit_153);
    Str_delete(&_til_str_lit_153, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7805 = 26;
    (void)hoisted__I64_7805;
    (void)_til_str_lit_154;
    (void)_til_str_lit_154;
    assert_eq__I64(result, hoisted__I64_7805, &_til_str_lit_154);
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
    I64 hoisted__I64_7892 = 106;
    (void)hoisted__I64_7892;
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    assert_eq__I64(d3, hoisted__I64_7892, &_til_str_lit_164);
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
    I64 hoisted__I64_8495 = 8;
    (void)hoisted__I64_8495;
    (void)_til_str_lit_169;
    (void)_til_str_lit_169;
    assert_eq__I64(result, hoisted__I64_8495, &_til_str_lit_169);
    Str_delete(&_til_str_lit_169, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8499 = 1;
    (void)hoisted__Bool_8499;
    (void)_til_str_lit_170;
    (void)_til_str_lit_170;
    assert(hoisted__Bool_8499, &_til_str_lit_170);
    Str_delete(&_til_str_lit_170, (Bool){0});
    Bool hoisted__Bool_8503 = 1;
    (void)hoisted__Bool_8503;
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert(hoisted__Bool_8503, &_til_str_lit_171);
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
    CfVec2 hoisted__CfVec2_8521 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8521;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8521;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8522 = 0;
    (void)hoisted__U32_8522;
    U64 hoisted__U64_8523 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8522); });
    (void)hoisted__U64_8523;
    return hoisted__U64_8523;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8554 = 16;
    (void)hoisted__U32_8554;
    return hoisted__U32_8554;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8555 = 42;
    (void)hoisted__I64_8555;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    assert_eq__I64(v.x, hoisted__I64_8555, &_til_str_lit_178);
    Str_delete(&_til_str_lit_178, (Bool){0});
    I64 hoisted__I64_8557 = 99;
    (void)hoisted__I64_8557;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__I64(v.y, hoisted__I64_8557, &_til_str_lit_179);
    Str_delete(&_til_str_lit_179, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8561 = 10;
    (void)hoisted__I64_8561;
    (void)_til_str_lit_180;
    (void)_til_str_lit_180;
    assert_eq__I64(p.x, hoisted__I64_8561, &_til_str_lit_180);
    Str_delete(&_til_str_lit_180, (Bool){0});
    I64 hoisted__I64_8563 = 20;
    (void)hoisted__I64_8563;
    (void)_til_str_lit_181;
    (void)_til_str_lit_181;
    assert_eq__I64(p.y, hoisted__I64_8563, &_til_str_lit_181);
    Str_delete(&_til_str_lit_181, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8570 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8570;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8570;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8571 = 0;
    (void)hoisted__U32_8571;
    U64 hoisted__U64_8572 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8571); });
    (void)hoisted__U64_8572;
    return hoisted__U64_8572;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8603 = 32;
    (void)hoisted__U32_8603;
    return hoisted__U32_8603;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8604 = 5;
    (void)hoisted__I64_8604;
    (void)_til_str_lit_185;
    (void)_til_str_lit_185;
    assert_eq__I64(r.top_left.x, hoisted__I64_8604, &_til_str_lit_185);
    Str_delete(&_til_str_lit_185, (Bool){0});
    I64 hoisted__I64_8606 = 10;
    (void)hoisted__I64_8606;
    (void)_til_str_lit_186;
    (void)_til_str_lit_186;
    assert_eq__I64(r.top_left.y, hoisted__I64_8606, &_til_str_lit_186);
    Str_delete(&_til_str_lit_186, (Bool){0});
    I64 hoisted__I64_8608 = 100;
    (void)hoisted__I64_8608;
    (void)_til_str_lit_187;
    (void)_til_str_lit_187;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8608, &_til_str_lit_187);
    Str_delete(&_til_str_lit_187, (Bool){0});
    I64 hoisted__I64_8610 = 200;
    (void)hoisted__I64_8610;
    (void)_til_str_lit_188;
    (void)_til_str_lit_188;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8610, &_til_str_lit_188);
    Str_delete(&_til_str_lit_188, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8613 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8613;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8613;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8614 = 0;
    (void)hoisted__U32_8614;
    U64 hoisted__U64_8615 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8614); });
    (void)hoisted__U64_8615;
    return hoisted__U64_8615;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8658 = 12;
    (void)hoisted__U32_8658;
    return hoisted__U32_8658;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8662 = F32_to_str(v.x);
    (void)hoisted__Str_8662;
    (void)_til_str_lit_190;
    (void)_til_str_lit_190;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    assert_eq__Str(hoisted__Str_8662, &_til_str_lit_190, &_til_str_lit_191);
    Str_delete(hoisted__Str_8662, 1);
    Str_delete(&_til_str_lit_190, (Bool){0});
    Str_delete(&_til_str_lit_191, (Bool){0});
    Str *hoisted__Str_8665 = F32_to_str(v.y);
    (void)hoisted__Str_8665;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    (void)_til_str_lit_193;
    (void)_til_str_lit_193;
    assert_eq__Str(hoisted__Str_8665, &_til_str_lit_192, &_til_str_lit_193);
    Str_delete(hoisted__Str_8665, 1);
    Str_delete(&_til_str_lit_192, (Bool){0});
    Str_delete(&_til_str_lit_193, (Bool){0});
    Str *hoisted__Str_8668 = F32_to_str(v.z);
    (void)hoisted__Str_8668;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    assert_eq__Str(hoisted__Str_8668, &_til_str_lit_194, &_til_str_lit_195);
    Str_delete(hoisted__Str_8668, 1);
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
    U32 hoisted__U32_8679 = 1;
    (void)hoisted__U32_8679;
    Bool hoisted__Bool_8680 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_8680;
    if (hoisted__Bool_8680) {
        U32 hoisted__U32_8673 = 1;
        (void)hoisted__U32_8673;
        Bool hoisted__Bool_8674 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_8674;
        { Bool _ret_val = hoisted__Bool_8674;
                return _ret_val; }
    }
    U32 hoisted__U32_8681 = 1;
    (void)hoisted__U32_8681;
    Bool hoisted__Bool_8682 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_8682;
    if (hoisted__Bool_8682) {
        U32 hoisted__U32_8675 = 1;
        (void)hoisted__U32_8675;
        Bool hoisted__Bool_8676 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_8676;
        { Bool _ret_val = hoisted__Bool_8676;
                return _ret_val; }
    }
    U32 hoisted__U32_8683 = 1;
    (void)hoisted__U32_8683;
    Bool hoisted__Bool_8684 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_8684;
    if (hoisted__Bool_8684) {
        U32 hoisted__U32_8677 = 1;
        (void)hoisted__U32_8677;
        Bool hoisted__Bool_8678 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_8678;
        { Bool _ret_val = hoisted__Bool_8678;
                return _ret_val; }
    }
    Bool hoisted__Bool_8685 = 0;
    (void)hoisted__Bool_8685;
    return hoisted__Bool_8685;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8693 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8693;
    if (hoisted__Bool_8693) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8694 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8694;
    if (hoisted__Bool_8694) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8695 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8695;
    if (hoisted__Bool_8695) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8696 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8696;
    UNREACHABLE(&hoisted__Str_8696);
    Str_delete(&hoisted__Str_8696, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8697 = 1;
    (void)hoisted__U32_8697;
    return hoisted__U32_8697;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8698 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8698;
    (void)_til_str_lit_199;
    (void)_til_str_lit_199;
    assert(hoisted__Bool_8698, &_til_str_lit_199);
    Str_delete(&_til_str_lit_199, (Bool){0});
    Bool hoisted__Bool_8700 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8700;
    Bool hoisted__Bool_8701 = not(hoisted__Bool_8700);
    (void)hoisted__Bool_8701;
    (void)_til_str_lit_200;
    (void)_til_str_lit_200;
    assert(hoisted__Bool_8701, &_til_str_lit_200);
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
    U32 hoisted__U32_8703 = 1;
    (void)hoisted__U32_8703;
    Bool hoisted__Bool_8704 = ((Bool)(((Token *)(self))->tag == ((Token *)(other))->tag));
    (void)hoisted__Bool_8704;
    return hoisted__Bool_8704;
}

void Token_delete(Token * self, Bool call_free) {
    U32 hoisted__U32_8728 = 1;
    (void)hoisted__U32_8728;
    Bool hoisted__Bool_8729 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8729;
    if (hoisted__Bool_8729) {
        I64 *hoisted__I64_8724 = get_payload(self);
        (void)hoisted__I64_8724;
        (void)hoisted__I64_8724;
        Bool hoisted__Bool_8725 = 0;
        (void)hoisted__Bool_8725;
        I64_delete(hoisted__I64_8724, hoisted__Bool_8725);
    }
    U32 hoisted__U32_8730 = 1;
    (void)hoisted__U32_8730;
    Bool hoisted__Bool_8731 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8731;
    if (hoisted__Bool_8731) {
        Str *hoisted__Str_8726 = get_payload(self);
        (void)hoisted__Str_8726;
        (void)hoisted__Str_8726;
        Bool hoisted__Bool_8727 = 0;
        (void)hoisted__Bool_8727;
        Str_delete(hoisted__Str_8726, hoisted__Bool_8727);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_8765 = 1;
    (void)hoisted__U32_8765;
    Bool hoisted__Bool_8766 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_8766;
    if (hoisted__Bool_8766) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8762 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8762;
        { Token * _ret_val = hoisted__Token_8762;
                return _ret_val; }
    }
    U32 hoisted__U32_8767 = 1;
    (void)hoisted__U32_8767;
    Bool hoisted__Bool_8768 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_8768;
    if (hoisted__Bool_8768) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8763 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8763;
        Token *hoisted__Token_8764 = Token_Name(hoisted__Str_8763);
        (void)hoisted__Token_8764;
        { Token * _ret_val = hoisted__Token_8764;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8769 = 24;
    (void)hoisted__U32_8769;
    return hoisted__U32_8769;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8771 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8771;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert(hoisted__Bool_8771, &_til_str_lit_203);
    Str_delete(&_til_str_lit_203, (Bool){0});
    Bool hoisted__Bool_8773 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8773;
    Bool hoisted__Bool_8774 = not(hoisted__Bool_8773);
    (void)hoisted__Bool_8774;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_8774, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8776 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8776;
    (void)_til_str_lit_205;
    (void)_til_str_lit_205;
    assert(hoisted__Bool_8776, &_til_str_lit_205);
    Str_delete(&_til_str_lit_205, (Bool){0});
    Bool hoisted__Bool_8778 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8778;
    Bool hoisted__Bool_8779 = not(hoisted__Bool_8778);
    (void)hoisted__Bool_8779;
    (void)_til_str_lit_206;
    (void)_til_str_lit_206;
    assert(hoisted__Bool_8779, &_til_str_lit_206);
    Str_delete(&_til_str_lit_206, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8783 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8783;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_8783, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Bool hoisted__Bool_8785 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8785;
    Bool hoisted__Bool_8786 = not(hoisted__Bool_8785);
    (void)hoisted__Bool_8786;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_8786, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8919 = ((Bool)(a != b));
    (void)hoisted__Bool_8919;
    if (hoisted__Bool_8919) {
        U32 hoisted__U32_8903 = 5;
        (void)hoisted__U32_8903;
        Array__Str *_va_Array_252 = Array__Str_new(hoisted__U32_8903);
        (void)_va_Array_252;
        I64 _va_Array_252_ek = 0;
        (void)_va_Array_252_ek;
        OutOfBounds *_va_Array_252_eo = malloc(sizeof(OutOfBounds));
        _va_Array_252_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_252_eo;
        U32 hoisted__U32_8904 = 0;
        (void)hoisted__U32_8904;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_252, hoisted__U32_8904, &_til_str_lit_209, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8907 = 1;
        (void)hoisted__U32_8907;
        Str *hoisted__Str_8908 = I64_to_str(a);
        (void)hoisted__Str_8908;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_252, hoisted__U32_8907, hoisted__Str_8908, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8910 = 2;
        (void)hoisted__U32_8910;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_252, hoisted__U32_8910, &_til_str_lit_211, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8913 = 3;
        (void)hoisted__U32_8913;
        Str *hoisted__Str_8914 = I64_to_str(b);
        (void)hoisted__Str_8914;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_252, hoisted__U32_8913, hoisted__Str_8914, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8916 = 4;
        (void)hoisted__U32_8916;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_252, hoisted__U32_8916, &_til_str_lit_212, &_va_Array_252_ek, _va_Array_252_eo, &_til_str_lit_210);
        OutOfBounds_delete(_va_Array_252_eo, 1);
        Str_delete(&_til_str_lit_210, (Bool){0});
        panic(_va_Array_252, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8936 = Str_neq(a, b);
    (void)hoisted__Bool_8936;
    if (hoisted__Bool_8936) {
        U32 hoisted__U32_8920 = 5;
        (void)hoisted__U32_8920;
        Array__Str *_va_Array_253 = Array__Str_new(hoisted__U32_8920);
        (void)_va_Array_253;
        I64 _va_Array_253_ek = 0;
        (void)_va_Array_253_ek;
        OutOfBounds *_va_Array_253_eo = malloc(sizeof(OutOfBounds));
        _va_Array_253_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_253_eo;
        U32 hoisted__U32_8921 = 0;
        (void)hoisted__U32_8921;
        (void)_til_str_lit_209;
        (void)_til_str_lit_209;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8921, &_til_str_lit_209, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8924 = 1;
        (void)hoisted__U32_8924;
        Str *hoisted__Str_8925 = Str_to_str(a);
        (void)hoisted__Str_8925;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8924, hoisted__Str_8925, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8927 = 2;
        (void)hoisted__U32_8927;
        (void)_til_str_lit_211;
        (void)_til_str_lit_211;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8927, &_til_str_lit_211, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8930 = 3;
        (void)hoisted__U32_8930;
        Str *hoisted__Str_8931 = Str_to_str(b);
        (void)hoisted__Str_8931;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8930, hoisted__Str_8931, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        Str_delete(&_til_str_lit_210, (Bool){0});
        U32 hoisted__U32_8933 = 4;
        (void)hoisted__U32_8933;
        (void)_til_str_lit_212;
        (void)_til_str_lit_212;
        (void)_til_str_lit_210;
        (void)_til_str_lit_210;
        Array__Str_set(_va_Array_253, hoisted__U32_8933, &_til_str_lit_212, &_va_Array_253_ek, _va_Array_253_eo, &_til_str_lit_210);
        OutOfBounds_delete(_va_Array_253_eo, 1);
        Str_delete(&_til_str_lit_210, (Bool){0});
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
