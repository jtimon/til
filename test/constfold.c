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
static __attribute__((unused)) Str _til_str_lit_29 = (Str){.c_str = (void *)"Func", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_30 = (Str){.c_str = (void *)"Proc", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_31 = (Str){.c_str = (void *)"Test", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_32 = (Str){.c_str = (void *)"Macro", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_33 = (Str){.c_str = (void *)"ExtFunc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_34 = (Str){.c_str = (void *)"ExtProc", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_35 = (Str){.c_str = (void *)"LazyFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_36 = (Str){.c_str = (void *)"LazyProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_37 = (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_38 = (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_39 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_40 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_41 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_42 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_43 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_44 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};
#define hoisted__Str_7197 _til_str_lit_141
#define hoisted__Str_7199 _til_str_lit_142
#define hoisted__Str_7200 _til_str_lit_141
#define hoisted__Str_7204 _til_str_lit_141
#define hoisted__Str_7216 _til_str_lit_143
#define hoisted__Str_7217 _til_str_lit_144
#define hoisted__Str_7220 _til_str_lit_145
#define hoisted__Str_7221 _til_str_lit_146
#define hoisted__Str_7329 _til_str_lit_149
#define hoisted__Str_7337 _til_str_lit_150
#define hoisted__Str_7345 _til_str_lit_151
#define hoisted__Str_7348 _til_str_lit_152
#define hoisted__Str_7349 _til_str_lit_153
#define hoisted__Str_7377 _til_str_lit_152
#define hoisted__Str_7378 _til_str_lit_154
#define hoisted__Str_7382 _til_str_lit_155
#define hoisted__Str_7383 _til_str_lit_156
#define hoisted__Str_7406 _til_str_lit_157
#define hoisted__Str_7407 _til_str_lit_158
#define hoisted__Str_7418 _til_str_lit_159
#define hoisted__Str_7419 _til_str_lit_160
#define hoisted__Str_7432 _til_str_lit_161
#define hoisted__Str_8031 _til_str_lit_164
#define hoisted__Str_8032 _til_str_lit_165
#define hoisted__Str_8035 _til_str_lit_166
#define hoisted__Str_8039 _til_str_lit_167
#define hoisted__Str_8043 _til_str_lit_168
#define hoisted__Str_8048 _til_str_lit_169
#define hoisted__Str_8049 _til_str_lit_169
#define hoisted__Str_8050 _til_str_lit_170
#define hoisted__Str_8053 _til_str_lit_171
#define hoisted__Str_8054 _til_str_lit_171
#define hoisted__Str_8055 _til_str_lit_172
#define hoisted__Str_8095 _til_str_lit_175
#define hoisted__Str_8097 _til_str_lit_176
#define hoisted__Str_8101 _til_str_lit_177
#define hoisted__Str_8103 _til_str_lit_178
#define hoisted__Str_8144 _til_str_lit_182
#define hoisted__Str_8146 _til_str_lit_183
#define hoisted__Str_8148 _til_str_lit_184
#define hoisted__Str_8150 _til_str_lit_185
#define hoisted__Str_8202 _til_str_lit_187
#define hoisted__Str_8203 _til_str_lit_188
#define hoisted__Str_8205 _til_str_lit_189
#define hoisted__Str_8206 _til_str_lit_190
#define hoisted__Str_8208 _til_str_lit_191
#define hoisted__Str_8209 _til_str_lit_192
#define hoisted__Str_8231 _til_str_lit_196
#define hoisted__Str_8234 _til_str_lit_197
#define hoisted__Str_8290 _til_str_lit_200
#define hoisted__Str_8293 _til_str_lit_201
#define hoisted__Str_8295 _til_str_lit_202
#define hoisted__Str_8298 _til_str_lit_203
#define hoisted__Str_8302 _til_str_lit_204
#define hoisted__Str_8305 _til_str_lit_205
#define hoisted__Str_8423 _til_str_lit_206
#define hoisted__Str_8424 _til_str_lit_207
#define hoisted__Str_8427 _til_str_lit_207
#define hoisted__Str_8429 _til_str_lit_208
#define hoisted__Str_8430 _til_str_lit_207
#define hoisted__Str_8433 _til_str_lit_207
#define hoisted__Str_8435 _til_str_lit_209
#define hoisted__Str_8436 _til_str_lit_207
#define hoisted__Str_8440 _til_str_lit_206
#define hoisted__Str_8441 _til_str_lit_207
#define hoisted__Str_8444 _til_str_lit_207
#define hoisted__Str_8446 _til_str_lit_208
#define hoisted__Str_8447 _til_str_lit_207
#define hoisted__Str_8450 _til_str_lit_207
#define hoisted__Str_8452 _til_str_lit_209
#define hoisted__Str_8453 _til_str_lit_207

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
    U32 hoisted__U32_148 = 1;
    (void)hoisted__U32_148;
    U32 hoisted__U64_149 = ((U64)(n + hoisted__U32_148));
    (void)hoisted__U64_149;
    void * buf = malloc(hoisted__U64_149);
    I32 hoisted__I32_150 = 0;
    (void)hoisted__I32_150;
    U64 hoisted__U64_151 = 1ULL;
    (void)hoisted__U64_151;
    memset(buf, hoisted__I32_150, hoisted__U64_151);
    I64 hoisted__I64_152 = 0;
    (void)hoisted__I64_152;
    Str *hoisted__Str_153 = malloc(sizeof(Str));
    hoisted__Str_153->c_str = buf;
    hoisted__Str_153->count = hoisted__I64_152;
    hoisted__Str_153->cap = n;
    (void)hoisted__Str_153;
    return hoisted__Str_153;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_166 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_166;
    if (hoisted__Bool_166) {
        U32 hoisted__U32_156 = 1;
        (void)hoisted__U32_156;
        Array__Str *_va_Array_3 = Array__Str_new(hoisted__U32_156);
        (void)_va_Array_3;
        I64 _va_Array_3_ek = 0;
        (void)_va_Array_3_ek;
        OutOfBounds *_va_Array_3_eo = malloc(sizeof(OutOfBounds));
        _va_Array_3_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_3_eo;
        U32 hoisted__U32_157 = 0;
        (void)hoisted__U32_157;
        static Str hoisted__Str_158 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_158;
        static Str hoisted__Str_159 = (Str){.c_str = (void *)"./src/core/str.til:100:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_159;
        Array__Str_set(_va_Array_3, hoisted__U32_157, &hoisted__Str_158, &_va_Array_3_ek, _va_Array_3_eo, &hoisted__Str_159);
        OutOfBounds_delete(_va_Array_3_eo, 1);
        Str_delete(&hoisted__Str_159, (Bool){0});
        static Str hoisted__Str_160 = (Str){.c_str = (void *)"./src/core/str.til:100:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_160;
        panic(_va_Array_3, &hoisted__Str_160);
        Str_delete(&hoisted__Str_160, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_167 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_167;
    if (hoisted__Bool_167) {
        U32 hoisted__U32_161 = 1;
        (void)hoisted__U32_161;
        Array__Str *_va_Array_4 = Array__Str_new(hoisted__U32_161);
        (void)_va_Array_4;
        I64 _va_Array_4_ek = 0;
        (void)_va_Array_4_ek;
        OutOfBounds *_va_Array_4_eo = malloc(sizeof(OutOfBounds));
        _va_Array_4_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_4_eo;
        U32 hoisted__U32_162 = 0;
        (void)hoisted__U32_162;
        static Str hoisted__Str_163 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_163;
        static Str hoisted__Str_164 = (Str){.c_str = (void *)"./src/core/str.til:104:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_164;
        Array__Str_set(_va_Array_4, hoisted__U32_162, &hoisted__Str_163, &_va_Array_4_ek, _va_Array_4_eo, &hoisted__Str_164);
        OutOfBounds_delete(_va_Array_4_eo, 1);
        Str_delete(&hoisted__Str_164, (Bool){0});
        static Str hoisted__Str_165 = (Str){.c_str = (void *)"./src/core/str.til:104:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_165;
        panic(_va_Array_4, &hoisted__Str_165);
        Str_delete(&hoisted__Str_165, (Bool){0});
    }
    void *hoisted__v_168 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_168;
    (void)hoisted__v_168;
    memcpy(hoisted__v_168, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_169 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_169;
    (void)hoisted__v_169;
    I32 hoisted__I32_170 = 0;
    (void)hoisted__I32_170;
    U64 hoisted__U64_171 = 1ULL;
    (void)hoisted__U64_171;
    memset(hoisted__v_169, hoisted__I32_170, hoisted__U64_171);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_172 = 1;
    (void)hoisted__U32_172;
    U32 hoisted__U64_173 = ((U64)(val->count + hoisted__U32_172));
    (void)hoisted__U64_173;
    void * new_data = malloc(hoisted__U64_173);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_174 = ptr_add(new_data, val->count);
    (void)hoisted__v_174;
    (void)hoisted__v_174;
    I32 hoisted__I32_175 = 0;
    (void)hoisted__I32_175;
    U64 hoisted__U64_176 = 1ULL;
    (void)hoisted__U64_176;
    memset(hoisted__v_174, hoisted__I32_175, hoisted__U64_176);
    Str *hoisted__Str_177 = malloc(sizeof(Str));
    hoisted__Str_177->c_str = new_data;
    hoisted__Str_177->count = val->count;
    hoisted__Str_177->cap = val->count;
    (void)hoisted__Str_177;
    return hoisted__Str_177;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_178 = Str_clone(self);
    (void)hoisted__Str_178;
    return hoisted__Str_178;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_179 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_179;
    if (hoisted__Bool_179) {
        free(self->c_str);
    }
    Bool hoisted__Bool_180 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_180;
    Bool hoisted__Bool_181 = and(call_free, hoisted__Bool_180);
    (void)hoisted__Bool_181;
    if (hoisted__Bool_181) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_376 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_376;
    return hoisted__U64_376;
}

U32 Str_size(void) {
    U32 hoisted__U32_560 = 16;
    (void)hoisted__U32_560;
    return hoisted__U32_560;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_561 = Str_cmp(a, b);
    (void)hoisted__I64_561;
    I64 hoisted__I64_562 = 0;
    (void)hoisted__I64_562;
    Bool hoisted__Bool_563 = ((Bool)(hoisted__I64_561 == hoisted__I64_562));
    (void)hoisted__Bool_563;
    return hoisted__Bool_563;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_572 = Str_eq(a, b);
    (void)hoisted__Bool_572;
    Bool hoisted__Bool_573 = not(hoisted__Bool_572);
    (void)hoisted__Bool_573;
    return hoisted__Bool_573;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_664 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_664->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_664;
    return hoisted__OutOfBounds_664;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_665 = 0;
    (void)hoisted__Bool_665;
    Str_delete(&self->msg, hoisted__Bool_665);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_666 = 0;
    (void)hoisted__U32_666;
    U64 hoisted__U64_667 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_666); });
    (void)hoisted__U64_667;
    return hoisted__U64_667;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_686 = 16;
    (void)hoisted__U32_686;
    return hoisted__U32_686;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_710 = 16;
    (void)hoisted__U32_710;
    U64 hoisted__U64_711 = (U64)(cap);
    (void)hoisted__U64_711;
    U64 hoisted__U64_712 = (U64)(hoisted__U32_710);
    (void)hoisted__U64_712;
    void * hoisted__v_713 = calloc(hoisted__U64_711, hoisted__U64_712);
    (void)hoisted__v_713;
    Array__Str *hoisted__Array__Str_714 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_714->data = hoisted__v_713;
    hoisted__Array__Str_714->cap = cap;
    (void)hoisted__Array__Str_714;
    return hoisted__Array__Str_714;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_715 = 16;
    (void)hoisted__U32_715;
    U32 hoisted__U32_716 = ((U32)(DEREF(i) * hoisted__U32_715));
    (void)hoisted__U32_716;
    U64 hoisted__U64_717 = (U64)(hoisted__U32_716);
    (void)hoisted__U64_717;
    void *hoisted__v_718 = ptr_add(self->data, hoisted__U64_717);
    (void)hoisted__v_718;
    (void)hoisted__v_718;
    return hoisted__v_718;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_745 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_745;
    (void)hoisted__Str_745;
    Bool hoisted__Bool_746 = 0;
    (void)hoisted__Bool_746;
    Str_delete(hoisted__Str_745, hoisted__Bool_746);
    U32 hoisted__U32_747 = 16;
    (void)hoisted__U32_747;
    Str *hoisted__Str_748 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_748;
    (void)hoisted__Str_748;
    U64 hoisted__U64_749 = (U64)(hoisted__U32_747);
    (void)hoisted__U64_749;
    memcpy(hoisted__Str_748, val, hoisted__U64_749);
    U32 hoisted__U32_750 = 16;
    (void)hoisted__U32_750;
    I32 hoisted__I32_751 = 0;
    (void)hoisted__I32_751;
    U64 hoisted__U64_752 = (U64)(hoisted__U32_750);
    (void)hoisted__U64_752;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_751, hoisted__U64_752); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_775 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_775;
    if (hoisted__Bool_775) {
        U32 hoisted__U32_753 = 6;
        (void)hoisted__U32_753;
        Array__Str *_va_Array_16 = Array__Str_new(hoisted__U32_753);
        (void)_va_Array_16;
        I64 _va_Array_16_ek = 0;
        (void)_va_Array_16_ek;
        OutOfBounds *_va_Array_16_eo = malloc(sizeof(OutOfBounds));
        _va_Array_16_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_16_eo;
        U32 hoisted__U32_754 = 0;
        (void)hoisted__U32_754;
        Str *hoisted__Str_755 = Str_clone(loc);
        (void)hoisted__Str_755;
        static Str hoisted__Str_756 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_756;
        Array__Str_set(_va_Array_16, hoisted__U32_754, hoisted__Str_755, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_756);
        Str_delete(&hoisted__Str_756, (Bool){0});
        U32 hoisted__U32_757 = 1;
        (void)hoisted__U32_757;
        static Str hoisted__Str_758 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_758;
        static Str hoisted__Str_759 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_759;
        Array__Str_set(_va_Array_16, hoisted__U32_757, &hoisted__Str_758, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_759);
        Str_delete(&hoisted__Str_759, (Bool){0});
        U32 hoisted__U32_760 = 2;
        (void)hoisted__U32_760;
        Str *hoisted__Str_761 = U32_to_str(i);
        (void)hoisted__Str_761;
        static Str hoisted__Str_762 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_762;
        Array__Str_set(_va_Array_16, hoisted__U32_760, hoisted__Str_761, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_762);
        Str_delete(&hoisted__Str_762, (Bool){0});
        U32 hoisted__U32_763 = 3;
        (void)hoisted__U32_763;
        static Str hoisted__Str_764 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_764;
        static Str hoisted__Str_765 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_765;
        Array__Str_set(_va_Array_16, hoisted__U32_763, &hoisted__Str_764, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_765);
        Str_delete(&hoisted__Str_765, (Bool){0});
        U32 hoisted__U32_766 = 4;
        (void)hoisted__U32_766;
        Str *hoisted__Str_767 = U32_to_str(self->cap);
        (void)hoisted__Str_767;
        static Str hoisted__Str_768 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_768;
        Array__Str_set(_va_Array_16, hoisted__U32_766, hoisted__Str_767, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_768);
        Str_delete(&hoisted__Str_768, (Bool){0});
        U32 hoisted__U32_769 = 5;
        (void)hoisted__U32_769;
        static Str hoisted__Str_770 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_770;
        static Str hoisted__Str_771 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_771;
        Array__Str_set(_va_Array_16, hoisted__U32_769, &hoisted__Str_770, &_va_Array_16_ek, _va_Array_16_eo, &hoisted__Str_771);
        OutOfBounds_delete(_va_Array_16_eo, 1);
        Str_delete(&hoisted__Str_771, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_772 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_16); hoisted__OutOfBounds_772->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_772;
        U32 hoisted__U32_773 = 16;
        (void)hoisted__U32_773;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_772, hoisted__U32_773);
        OutOfBounds_delete(hoisted__OutOfBounds_772, 1);
        I64 hoisted__I64_774 = 1;
        (void)hoisted__I64_774;
        *_err_kind = hoisted__I64_774;
    }
    I64 hoisted__I64_776 = 0;
    (void)hoisted__I64_776;
    Bool hoisted__Bool_777 = ((Bool)(DEREF(_err_kind) == hoisted__I64_776));
    (void)hoisted__Bool_777;
    if (hoisted__Bool_777) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_778 = self->cap;
        (void)_re_U32_778;
        U32 _rc_U32_778 = 0;
        (void)_rc_U32_778;
        Bool hoisted__Bool_791 = ((Bool)(_rc_U32_778 <= _re_U32_778));
        (void)hoisted__Bool_791;
        if (hoisted__Bool_791) {
            while (1) {
                Bool _wcond_Bool_779 = ((Bool)(_rc_U32_778 < _re_U32_778));
                (void)_wcond_Bool_779;
                if (_wcond_Bool_779) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_778);
                U32_inc(&_rc_U32_778);
                U32 hoisted__U32_780 = 16;
                (void)hoisted__U32_780;
                U32 hoisted__U32_781 = ((U32)(i * hoisted__U32_780));
                (void)hoisted__U32_781;
                U64 hoisted__U64_782 = (U64)(hoisted__U32_781);
                (void)hoisted__U64_782;
                Str *hoisted__Str_783 = ptr_add(self->data, hoisted__U64_782);
                (void)hoisted__Str_783;
                (void)hoisted__Str_783;
                Bool hoisted__Bool_784 = 0;
                (void)hoisted__Bool_784;
                Str_delete(hoisted__Str_783, hoisted__Bool_784);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_785 = ((Bool)(_rc_U32_778 > _re_U32_778));
                (void)_wcond_Bool_785;
                if (_wcond_Bool_785) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_778);
                U32_dec(&_rc_U32_778);
                U32 hoisted__U32_786 = 16;
                (void)hoisted__U32_786;
                U32 hoisted__U32_787 = ((U32)(i * hoisted__U32_786));
                (void)hoisted__U32_787;
                U64 hoisted__U64_788 = (U64)(hoisted__U32_787);
                (void)hoisted__U64_788;
                Str *hoisted__Str_789 = ptr_add(self->data, hoisted__U64_788);
                (void)hoisted__Str_789;
                (void)hoisted__Str_789;
                Bool hoisted__Bool_790 = 0;
                (void)hoisted__Bool_790;
                Str_delete(hoisted__Str_789, hoisted__Bool_790);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_820 = 16;
    (void)hoisted__U32_820;
    U32 hoisted__U32_821 = ((U32)(self->cap * hoisted__U32_820));
    (void)hoisted__U32_821;
    U64 hoisted__U64_822 = (U64)(hoisted__U32_821);
    (void)hoisted__U64_822;
    void * new_data = malloc(hoisted__U64_822);
    {
        U32 _re_U32_792 = self->cap;
        (void)_re_U32_792;
        U32 _rc_U32_792 = 0;
        (void)_rc_U32_792;
        Bool hoisted__Bool_819 = ((Bool)(_rc_U32_792 <= _re_U32_792));
        (void)hoisted__Bool_819;
        if (hoisted__Bool_819) {
            while (1) {
                Bool _wcond_Bool_793 = ((Bool)(_rc_U32_792 < _re_U32_792));
                (void)_wcond_Bool_793;
                if (_wcond_Bool_793) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_792);
                U32_inc(&_rc_U32_792);
                U32 hoisted__U32_794 = 16;
                (void)hoisted__U32_794;
                U32 hoisted__U32_795 = ((U32)(i * hoisted__U32_794));
                (void)hoisted__U32_795;
                U64 hoisted__U64_796 = (U64)(hoisted__U32_795);
                (void)hoisted__U64_796;
                Str *src = ptr_add(self->data, hoisted__U64_796);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_797 = 16;
                (void)hoisted__U32_797;
                U32 hoisted__U32_798 = ((U32)(i * hoisted__U32_797));
                (void)hoisted__U32_798;
                U64 hoisted__U64_799 = (U64)(hoisted__U32_798);
                (void)hoisted__U64_799;
                U32 hoisted__U32_800 = 16;
                (void)hoisted__U32_800;
                void *hoisted__v_801 = ptr_add(new_data, hoisted__U64_799);
                (void)hoisted__v_801;
                (void)hoisted__v_801;
                U64 hoisted__U64_802 = (U64)(hoisted__U32_800);
                (void)hoisted__U64_802;
                memcpy(hoisted__v_801, cloned, hoisted__U64_802);
                U32 hoisted__U32_803 = 16;
                (void)hoisted__U32_803;
                I32 hoisted__I32_804 = 0;
                (void)hoisted__I32_804;
                U64 hoisted__U64_805 = (U64)(hoisted__U32_803);
                (void)hoisted__U64_805;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_804, hoisted__U64_805); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_806 = ((Bool)(_rc_U32_792 > _re_U32_792));
                (void)_wcond_Bool_806;
                if (_wcond_Bool_806) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_792);
                U32_dec(&_rc_U32_792);
                U32 hoisted__U32_807 = 16;
                (void)hoisted__U32_807;
                U32 hoisted__U32_808 = ((U32)(i * hoisted__U32_807));
                (void)hoisted__U32_808;
                U64 hoisted__U64_809 = (U64)(hoisted__U32_808);
                (void)hoisted__U64_809;
                Str *src = ptr_add(self->data, hoisted__U64_809);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_810 = 16;
                (void)hoisted__U32_810;
                U32 hoisted__U32_811 = ((U32)(i * hoisted__U32_810));
                (void)hoisted__U32_811;
                U64 hoisted__U64_812 = (U64)(hoisted__U32_811);
                (void)hoisted__U64_812;
                U32 hoisted__U32_813 = 16;
                (void)hoisted__U32_813;
                void *hoisted__v_814 = ptr_add(new_data, hoisted__U64_812);
                (void)hoisted__v_814;
                (void)hoisted__v_814;
                U64 hoisted__U64_815 = (U64)(hoisted__U32_813);
                (void)hoisted__U64_815;
                memcpy(hoisted__v_814, cloned, hoisted__U64_815);
                U32 hoisted__U32_816 = 16;
                (void)hoisted__U32_816;
                I32 hoisted__I32_817 = 0;
                (void)hoisted__I32_817;
                U64 hoisted__U64_818 = (U64)(hoisted__U32_816);
                (void)hoisted__U64_818;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_817, hoisted__U64_818); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_823 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_823->data = new_data;
    hoisted__Array__Str_823->cap = self->cap;
    (void)hoisted__Array__Str_823;
    return hoisted__Array__Str_823;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_824 = 16;
    (void)hoisted__U32_824;
    return hoisted__U32_824;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_825 = 16;
    (void)hoisted__U32_825;
    U64 hoisted__U64_826 = (U64)(hoisted__U32_825);
    (void)hoisted__U64_826;
    void * hoisted__v_827 = malloc(hoisted__U64_826);
    (void)hoisted__v_827;
    U32 hoisted__U32_828 = 0;
    (void)hoisted__U32_828;
    I64 hoisted__I64_829 = 1;
    (void)hoisted__I64_829;
    Vec__Str *hoisted__Vec__Str_830 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_830->data = hoisted__v_827;
    hoisted__Vec__Str_830->count = hoisted__U32_828;
    hoisted__Vec__Str_830->cap = hoisted__I64_829;
    (void)hoisted__Vec__Str_830;
    return hoisted__Vec__Str_830;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_840 = self->count;
        (void)_re_U32_840;
        U32 _rc_U32_840 = 0;
        (void)_rc_U32_840;
        Bool hoisted__Bool_853 = ((Bool)(_rc_U32_840 <= _re_U32_840));
        (void)hoisted__Bool_853;
        if (hoisted__Bool_853) {
            while (1) {
                Bool _wcond_Bool_841 = ((Bool)(_rc_U32_840 < _re_U32_840));
                (void)_wcond_Bool_841;
                if (_wcond_Bool_841) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_840);
                U32_inc(&_rc_U32_840);
                U32 hoisted__U32_842 = 16;
                (void)hoisted__U32_842;
                U32 hoisted__U32_843 = ((U32)(i * hoisted__U32_842));
                (void)hoisted__U32_843;
                U64 hoisted__U64_844 = (U64)(hoisted__U32_843);
                (void)hoisted__U64_844;
                Str *hoisted__Str_845 = ptr_add(self->data, hoisted__U64_844);
                (void)hoisted__Str_845;
                (void)hoisted__Str_845;
                Bool hoisted__Bool_846 = 0;
                (void)hoisted__Bool_846;
                Str_delete(hoisted__Str_845, hoisted__Bool_846);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_847 = ((Bool)(_rc_U32_840 > _re_U32_840));
                (void)_wcond_Bool_847;
                if (_wcond_Bool_847) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_840);
                U32_dec(&_rc_U32_840);
                U32 hoisted__U32_848 = 16;
                (void)hoisted__U32_848;
                U32 hoisted__U32_849 = ((U32)(i * hoisted__U32_848));
                (void)hoisted__U32_849;
                U64 hoisted__U64_850 = (U64)(hoisted__U32_849);
                (void)hoisted__U64_850;
                Str *hoisted__Str_851 = ptr_add(self->data, hoisted__U64_850);
                (void)hoisted__Str_851;
                (void)hoisted__Str_851;
                Bool hoisted__Bool_852 = 0;
                (void)hoisted__Bool_852;
                Str_delete(hoisted__Str_851, hoisted__Bool_852);
            }
        }
    }
    U32 hoisted__U32_854 = 0;
    (void)hoisted__U32_854;
    self->count = hoisted__U32_854;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1124 = 16;
    (void)hoisted__U32_1124;
    U32 hoisted__U32_1125 = ((U32)(self->cap * hoisted__U32_1124));
    (void)hoisted__U32_1125;
    U64 hoisted__U64_1126 = (U64)(hoisted__U32_1125);
    (void)hoisted__U64_1126;
    void * new_data = malloc(hoisted__U64_1126);
    {
        U32 _re_U32_1096 = self->count;
        (void)_re_U32_1096;
        U32 _rc_U32_1096 = 0;
        (void)_rc_U32_1096;
        Bool hoisted__Bool_1123 = ((Bool)(_rc_U32_1096 <= _re_U32_1096));
        (void)hoisted__Bool_1123;
        if (hoisted__Bool_1123) {
            while (1) {
                Bool _wcond_Bool_1097 = ((Bool)(_rc_U32_1096 < _re_U32_1096));
                (void)_wcond_Bool_1097;
                if (_wcond_Bool_1097) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1096);
                U32_inc(&_rc_U32_1096);
                U32 hoisted__U32_1098 = 16;
                (void)hoisted__U32_1098;
                U32 hoisted__U32_1099 = ((U32)(i * hoisted__U32_1098));
                (void)hoisted__U32_1099;
                U64 hoisted__U64_1100 = (U64)(hoisted__U32_1099);
                (void)hoisted__U64_1100;
                Str *src = ptr_add(self->data, hoisted__U64_1100);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1101 = 16;
                (void)hoisted__U32_1101;
                U32 hoisted__U32_1102 = ((U32)(i * hoisted__U32_1101));
                (void)hoisted__U32_1102;
                U64 hoisted__U64_1103 = (U64)(hoisted__U32_1102);
                (void)hoisted__U64_1103;
                U32 hoisted__U32_1104 = 16;
                (void)hoisted__U32_1104;
                void *hoisted__v_1105 = ptr_add(new_data, hoisted__U64_1103);
                (void)hoisted__v_1105;
                (void)hoisted__v_1105;
                U64 hoisted__U64_1106 = (U64)(hoisted__U32_1104);
                (void)hoisted__U64_1106;
                memcpy(hoisted__v_1105, cloned, hoisted__U64_1106);
                U32 hoisted__U32_1107 = 16;
                (void)hoisted__U32_1107;
                I32 hoisted__I32_1108 = 0;
                (void)hoisted__I32_1108;
                U64 hoisted__U64_1109 = (U64)(hoisted__U32_1107);
                (void)hoisted__U64_1109;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1108, hoisted__U64_1109); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1110 = ((Bool)(_rc_U32_1096 > _re_U32_1096));
                (void)_wcond_Bool_1110;
                if (_wcond_Bool_1110) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1096);
                U32_dec(&_rc_U32_1096);
                U32 hoisted__U32_1111 = 16;
                (void)hoisted__U32_1111;
                U32 hoisted__U32_1112 = ((U32)(i * hoisted__U32_1111));
                (void)hoisted__U32_1112;
                U64 hoisted__U64_1113 = (U64)(hoisted__U32_1112);
                (void)hoisted__U64_1113;
                Str *src = ptr_add(self->data, hoisted__U64_1113);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1114 = 16;
                (void)hoisted__U32_1114;
                U32 hoisted__U32_1115 = ((U32)(i * hoisted__U32_1114));
                (void)hoisted__U32_1115;
                U64 hoisted__U64_1116 = (U64)(hoisted__U32_1115);
                (void)hoisted__U64_1116;
                U32 hoisted__U32_1117 = 16;
                (void)hoisted__U32_1117;
                void *hoisted__v_1118 = ptr_add(new_data, hoisted__U64_1116);
                (void)hoisted__v_1118;
                (void)hoisted__v_1118;
                U64 hoisted__U64_1119 = (U64)(hoisted__U32_1117);
                (void)hoisted__U64_1119;
                memcpy(hoisted__v_1118, cloned, hoisted__U64_1119);
                U32 hoisted__U32_1120 = 16;
                (void)hoisted__U32_1120;
                I32 hoisted__I32_1121 = 0;
                (void)hoisted__I32_1121;
                U64 hoisted__U64_1122 = (U64)(hoisted__U32_1120);
                (void)hoisted__U64_1122;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1121, hoisted__U64_1122); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1127 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1127->data = new_data;
    hoisted__Vec__Str_1127->count = self->count;
    hoisted__Vec__Str_1127->cap = self->cap;
    (void)hoisted__Vec__Str_1127;
    return hoisted__Vec__Str_1127;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1128 = 16;
    (void)hoisted__U32_1128;
    return hoisted__U32_1128;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1131 = 8;
    (void)hoisted__U32_1131;
    return hoisted__U32_1131;
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
    U32 hoisted__U32_1147 = 1;
    (void)hoisted__U32_1147;
    return hoisted__U32_1147;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1232 = 0;
    (void)hoisted__U32_1232;
    U64 hoisted__U64_1233 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1232); });
    (void)hoisted__U64_1233;
    return hoisted__U64_1233;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_1333 = U32_to_i64(val);
    (void)hoisted__I64_1333;
    Str *hoisted__Str_1334 = I64_to_str(hoisted__I64_1333);
    (void)hoisted__Str_1334;
    return hoisted__Str_1334;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_1335 = 1;
    (void)hoisted__U32_1335;
    U32 hoisted__U32_1336 = ((U32)(DEREF(self) + hoisted__U32_1335));
    (void)hoisted__U32_1336;
    *self = hoisted__U32_1336;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_1337 = 1;
    (void)hoisted__U32_1337;
    U32 hoisted__U32_1338 = ((U32)(DEREF(self) - hoisted__U32_1337));
    (void)hoisted__U32_1338;
    *self = hoisted__U32_1338;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_1345 = 4;
    (void)hoisted__U32_1345;
    return hoisted__U32_1345;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1430 = 0;
    (void)hoisted__U32_1430;
    U64 hoisted__U64_1431 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1430); });
    (void)hoisted__U64_1431;
    return hoisted__U64_1431;
}

void U64_inc(U64 * self) {
    U64 hoisted__U64_1433 = 1ULL;
    (void)hoisted__U64_1433;
    U64 hoisted__U64_1434 = ((U64)(DEREF(self) + hoisted__U64_1433));
    (void)hoisted__U64_1434;
    *self = hoisted__U64_1434;
}

void U64_dec(U64 * self) {
    U64 hoisted__U64_1435 = 1ULL;
    (void)hoisted__U64_1435;
    U64 hoisted__U64_1436 = ((U64)(DEREF(self) - hoisted__U64_1435));
    (void)hoisted__U64_1436;
    *self = hoisted__U64_1436;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_1441 = 8;
    (void)hoisted__U32_1441;
    return hoisted__U32_1441;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1526 = 0;
    (void)hoisted__U32_1526;
    U64 hoisted__U64_1527 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1526); });
    (void)hoisted__U64_1527;
    return hoisted__U64_1527;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_1548 = 1;
    (void)hoisted__U32_1548;
    return hoisted__U32_1548;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1549 = 0;
    (void)hoisted__U32_1549;
    U64 hoisted__U64_1550 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1549); });
    (void)hoisted__U64_1550;
    return hoisted__U64_1550;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_1735 = 4;
    (void)hoisted__U32_1735;
    return hoisted__U32_1735;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1877 = 0;
    (void)hoisted__U32_1877;
    U64 hoisted__U64_1878 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1877); });
    (void)hoisted__U64_1878;
    return hoisted__U64_1878;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1909 = 0;
    (void)hoisted__I64_1909;
    Bool hoisted__Bool_1910 = ((Bool)(val == hoisted__I64_1909));
    (void)hoisted__Bool_1910;
    if (hoisted__Bool_1910) {
        U64 hoisted__U64_1879 = 2ULL;
        (void)hoisted__U64_1879;
        void * buf = malloc(hoisted__U64_1879);
        I64 hoisted__I64_1880 = 48;
        (void)hoisted__I64_1880;
        U64 hoisted__U64_1881 = 1ULL;
        (void)hoisted__U64_1881;
        memcpy(buf, &hoisted__I64_1880, hoisted__U64_1881);
        U64 hoisted__U64_1882 = 1ULL;
        (void)hoisted__U64_1882;
        void *hoisted__v_1883 = ptr_add(buf, hoisted__U64_1882);
        (void)hoisted__v_1883;
        (void)hoisted__v_1883;
        I32 hoisted__I32_1884 = 0;
        (void)hoisted__I32_1884;
        U64 hoisted__U64_1885 = 1ULL;
        (void)hoisted__U64_1885;
        memset(hoisted__v_1883, hoisted__I32_1884, hoisted__U64_1885);
        I64 hoisted__I64_1886 = 1;
        (void)hoisted__I64_1886;
        I64 hoisted__I64_1887 = 1;
        (void)hoisted__I64_1887;
        Str *hoisted__Str_1888 = malloc(sizeof(Str));
        hoisted__Str_1888->c_str = buf;
        hoisted__Str_1888->count = hoisted__I64_1886;
        hoisted__Str_1888->cap = hoisted__I64_1887;
        (void)hoisted__Str_1888;
        { Str * _ret_val = hoisted__Str_1888;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1911 = 0;
    (void)hoisted__I64_1911;
    Bool hoisted__Bool_1912 = ((Bool)(val < hoisted__I64_1911));
    (void)hoisted__Bool_1912;
    if (hoisted__Bool_1912) {
        Bool hoisted__Bool_1889 = 1;
        (void)hoisted__Bool_1889;
        is_neg = hoisted__Bool_1889;
        I64 hoisted__I64_1890 = 0;
        (void)hoisted__I64_1890;
        I64 hoisted__I64_1891 = ((I64)(hoisted__I64_1890 - val));
        (void)hoisted__I64_1891;
        v = hoisted__I64_1891;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1893 = 0;
        (void)hoisted__I64_1893;
        Bool _wcond_Bool_1892 = ((Bool)(tmp > hoisted__I64_1893));
        (void)_wcond_Bool_1892;
        if (_wcond_Bool_1892) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1894 = 10;
        (void)hoisted__I64_1894;
        I64 hoisted__I64_1895 = ({ I64 _cf_a = tmp; I64 _cf_b = hoisted__I64_1894; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1895;
        tmp = hoisted__I64_1895;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1913 = 1ULL;
    (void)hoisted__U64_1913;
    U64 hoisted__U64_1914 = ((U64)(total + hoisted__U64_1913));
    (void)hoisted__U64_1914;
    void * buf = malloc(hoisted__U64_1914);
    if (is_neg) {
        I64 hoisted__I64_1896 = 45;
        (void)hoisted__I64_1896;
        U64 hoisted__U64_1897 = 1ULL;
        (void)hoisted__U64_1897;
        memcpy(buf, &hoisted__I64_1896, hoisted__U64_1897);
    }
    U64 hoisted__U64_1915 = 1ULL;
    (void)hoisted__U64_1915;
    U64 i = ((U64)(total - hoisted__U64_1915));
    while (1) {
        I64 hoisted__I64_1899 = 0;
        (void)hoisted__I64_1899;
        Bool _wcond_Bool_1898 = ((Bool)(v > hoisted__I64_1899));
        (void)_wcond_Bool_1898;
        if (_wcond_Bool_1898) {
        } else {
            break;
        }
        I64 hoisted__I64_1900 = 10;
        (void)hoisted__I64_1900;
        I64 hoisted__I64_1901 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1900; (I64)((_cf_b == 0) ? 0 : (_cf_a % _cf_b)); });
        (void)hoisted__I64_1901;
        I64 hoisted__I64_1902 = 48;
        (void)hoisted__I64_1902;
        I64 hoisted__I64_1903 = ((I64)(hoisted__I64_1901 + hoisted__I64_1902));
        (void)hoisted__I64_1903;
        void *hoisted__v_1904 = ptr_add(buf, i);
        (void)hoisted__v_1904;
        (void)hoisted__v_1904;
        U8 hoisted__U8_1905 = I64_to_u8(hoisted__I64_1903);
        (void)hoisted__U8_1905;
        U64 hoisted__U64_1906 = 1ULL;
        (void)hoisted__U64_1906;
        memcpy(hoisted__v_1904, &hoisted__U8_1905, hoisted__U64_1906);
        I64 hoisted__I64_1907 = 10;
        (void)hoisted__I64_1907;
        I64 hoisted__I64_1908 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1907; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1908;
        v = hoisted__I64_1908;
        U64_dec(&i);
    }
    void *hoisted__v_1916 = ptr_add(buf, total);
    (void)hoisted__v_1916;
    (void)hoisted__v_1916;
    I32 hoisted__I32_1917 = 0;
    (void)hoisted__I32_1917;
    U64 hoisted__U64_1918 = 1ULL;
    (void)hoisted__U64_1918;
    memset(hoisted__v_1916, hoisted__I32_1917, hoisted__U64_1918);
    Str *hoisted__Str_1919 = malloc(sizeof(Str));
    hoisted__Str_1919->c_str = buf;
    hoisted__Str_1919->count = total;
    hoisted__Str_1919->cap = total;
    (void)hoisted__Str_1919;
    return hoisted__Str_1919;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1937 = 8;
    (void)hoisted__U32_1937;
    return hoisted__U32_1937;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2095 = 0;
    (void)hoisted__U32_2095;
    U64 hoisted__U64_2096 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2095); });
    (void)hoisted__U64_2096;
    return hoisted__U64_2096;
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_2098 = 4;
    (void)hoisted__U32_2098;
    return hoisted__U32_2098;
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_2116 = 0;
    (void)hoisted__U32_2116;
    U64 hoisted__U64_2117 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2116); });
    (void)hoisted__U64_2117;
    return hoisted__U64_2117;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2164 = 0;
    (void)_m_Bool_2164;
    {
        Bool hoisted__Bool_2167 = 1;
        (void)hoisted__Bool_2167;
        Bool hoisted__Bool_2168 = Bool_eq(a, hoisted__Bool_2167);
        (void)hoisted__Bool_2168;
        if (hoisted__Bool_2168) {
            Bool hoisted__Bool_2165 = Bool_clone(&b);
            (void)hoisted__Bool_2165;
            _m_Bool_2164 = hoisted__Bool_2165;
        } else {
            Bool hoisted__Bool_2166 = 0;
            (void)hoisted__Bool_2166;
            _m_Bool_2164 = hoisted__Bool_2166;
        }
    }
    return _m_Bool_2164;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2178 = Bool_eq(a, b);
    (void)hoisted__Bool_2178;
    if (hoisted__Bool_2178) {
        I64 hoisted__I64_2176 = 0;
        (void)hoisted__I64_2176;
        { I64 _ret_val = hoisted__I64_2176;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2177 = -1;
        (void)hoisted__I64_2177;
        return hoisted__I64_2177;
    }
    I64 hoisted__I64_2179 = 1;
    (void)hoisted__I64_2179;
    return hoisted__I64_2179;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2180 = 1;
    (void)hoisted__U32_2180;
    return hoisted__U32_2180;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2181 = 0;
    (void)hoisted__U32_2181;
    U64 hoisted__U64_2182 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2181); });
    (void)hoisted__U64_2182;
    return hoisted__U64_2182;
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
    Bool hoisted__Bool_2208 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I16})));
    (void)hoisted__Bool_2208;
    if (hoisted__Bool_2208) {
        Bool hoisted__Bool_2198 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I16})));
        (void)hoisted__Bool_2198;
        { Bool _ret_val = hoisted__Bool_2198;
                return _ret_val; }
    }
    Bool hoisted__Bool_2209 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U16})));
    (void)hoisted__Bool_2209;
    if (hoisted__Bool_2209) {
        Bool hoisted__Bool_2199 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U16})));
        (void)hoisted__Bool_2199;
        { Bool _ret_val = hoisted__Bool_2199;
                return _ret_val; }
    }
    Bool hoisted__Bool_2210 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I8})));
    (void)hoisted__Bool_2210;
    if (hoisted__Bool_2210) {
        Bool hoisted__Bool_2200 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I8})));
        (void)hoisted__Bool_2200;
        { Bool _ret_val = hoisted__Bool_2200;
                return _ret_val; }
    }
    Bool hoisted__Bool_2211 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U8})));
    (void)hoisted__Bool_2211;
    if (hoisted__Bool_2211) {
        Bool hoisted__Bool_2201 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U8})));
        (void)hoisted__Bool_2201;
        { Bool _ret_val = hoisted__Bool_2201;
                return _ret_val; }
    }
    Bool hoisted__Bool_2212 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U32})));
    (void)hoisted__Bool_2212;
    if (hoisted__Bool_2212) {
        Bool hoisted__Bool_2202 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U32})));
        (void)hoisted__Bool_2202;
        { Bool _ret_val = hoisted__Bool_2202;
                return _ret_val; }
    }
    Bool hoisted__Bool_2213 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I32})));
    (void)hoisted__Bool_2213;
    if (hoisted__Bool_2213) {
        Bool hoisted__Bool_2203 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I32})));
        (void)hoisted__Bool_2203;
        { Bool _ret_val = hoisted__Bool_2203;
                return _ret_val; }
    }
    Bool hoisted__Bool_2214 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U64})));
    (void)hoisted__Bool_2214;
    if (hoisted__Bool_2214) {
        Bool hoisted__Bool_2204 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U64})));
        (void)hoisted__Bool_2204;
        { Bool _ret_val = hoisted__Bool_2204;
                return _ret_val; }
    }
    Bool hoisted__Bool_2215 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I64})));
    (void)hoisted__Bool_2215;
    if (hoisted__Bool_2215) {
        Bool hoisted__Bool_2205 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I64})));
        (void)hoisted__Bool_2205;
        { Bool _ret_val = hoisted__Bool_2205;
                return _ret_val; }
    }
    Bool hoisted__Bool_2216 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_F32})));
    (void)hoisted__Bool_2216;
    if (hoisted__Bool_2216) {
        Bool hoisted__Bool_2206 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_F32})));
        (void)hoisted__Bool_2206;
        { Bool _ret_val = hoisted__Bool_2206;
                return _ret_val; }
    }
    Bool hoisted__Bool_2217 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_Bool})));
    (void)hoisted__Bool_2217;
    if (hoisted__Bool_2217) {
        Bool hoisted__Bool_2207 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_Bool})));
        (void)hoisted__Bool_2207;
        { Bool _ret_val = hoisted__Bool_2207;
                return _ret_val; }
    }
    Bool hoisted__Bool_2218 = 0;
    (void)hoisted__Bool_2218;
    return hoisted__Bool_2218;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2240 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2240;
    if (hoisted__Bool_2240) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2241 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2241;
    if (hoisted__Bool_2241) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2242 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2243 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2243;
    if (hoisted__Bool_2243) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2244 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2245 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2245;
    if (hoisted__Bool_2245) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2246 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2246;
    if (hoisted__Bool_2246) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2247 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2247;
    if (hoisted__Bool_2247) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2248 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2248;
    if (hoisted__Bool_2248) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2249 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2249;
    if (hoisted__Bool_2249) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2250 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2250;
    UNREACHABLE(&hoisted__Str_2250);
    Str_delete(&hoisted__Str_2250, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2251 = 4;
    (void)hoisted__U32_2251;
    return hoisted__U32_2251;
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
    Bool hoisted__Bool_2303 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Struct})));
    (void)hoisted__Bool_2303;
    if (hoisted__Bool_2303) {
        Str *hoisted__Str_2293 = get_payload(self);
        (void)hoisted__Str_2293;
        (void)hoisted__Str_2293;
        Bool hoisted__Bool_2294 = 0;
        (void)hoisted__Bool_2294;
        Str_delete(hoisted__Str_2293, hoisted__Bool_2294);
    }
    Bool hoisted__Bool_2304 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Enum})));
    (void)hoisted__Bool_2304;
    if (hoisted__Bool_2304) {
        Str *hoisted__Str_2295 = get_payload(self);
        (void)hoisted__Str_2295;
        (void)hoisted__Str_2295;
        Bool hoisted__Bool_2296 = 0;
        (void)hoisted__Bool_2296;
        Str_delete(hoisted__Str_2295, hoisted__Bool_2296);
    }
    Bool hoisted__Bool_2305 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Custom})));
    (void)hoisted__Bool_2305;
    if (hoisted__Bool_2305) {
        Str *hoisted__Str_2297 = get_payload(self);
        (void)hoisted__Str_2297;
        (void)hoisted__Str_2297;
        Bool hoisted__Bool_2298 = 0;
        (void)hoisted__Bool_2298;
        Str_delete(hoisted__Str_2297, hoisted__Bool_2298);
    }
    Bool hoisted__Bool_2306 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Primitive})));
    (void)hoisted__Bool_2306;
    if (hoisted__Bool_2306) {
        Primitive *hoisted__Primitive_2299 = get_payload(self);
        (void)hoisted__Primitive_2299;
        (void)hoisted__Primitive_2299;
        Bool hoisted__Bool_2300 = 0;
        (void)hoisted__Bool_2300;
        Primitive_delete(hoisted__Primitive_2299, hoisted__Bool_2300);
    }
    Bool hoisted__Bool_2307 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_FuncPtrSig})));
    (void)hoisted__Bool_2307;
    if (hoisted__Bool_2307) {
        Str *hoisted__Str_2301 = get_payload(self);
        (void)hoisted__Str_2301;
        (void)hoisted__Str_2301;
        Bool hoisted__Bool_2302 = 0;
        (void)hoisted__Bool_2302;
        Str_delete(hoisted__Str_2301, hoisted__Bool_2302);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2391 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Unknown})));
    (void)hoisted__Bool_2391;
    if (hoisted__Bool_2391) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2392 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_None})));
    (void)hoisted__Bool_2392;
    if (hoisted__Bool_2392) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2393 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Struct})));
    (void)hoisted__Bool_2393;
    if (hoisted__Bool_2393) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2383 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2383;
        Type *hoisted__Type_2384 = Type_Struct(hoisted__Str_2383);
        (void)hoisted__Type_2384;
        { Type * _ret_val = hoisted__Type_2384;
                return _ret_val; }
    }
    Bool hoisted__Bool_2394 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_StructDef})));
    (void)hoisted__Bool_2394;
    if (hoisted__Bool_2394) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2395 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Enum})));
    (void)hoisted__Bool_2395;
    if (hoisted__Bool_2395) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2385 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2385;
        Type *hoisted__Type_2386 = Type_Enum(hoisted__Str_2385);
        (void)hoisted__Type_2386;
        { Type * _ret_val = hoisted__Type_2386;
                return _ret_val; }
    }
    Bool hoisted__Bool_2396 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_EnumDef})));
    (void)hoisted__Bool_2396;
    if (hoisted__Bool_2396) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2397 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_FuncDef})));
    (void)hoisted__Bool_2397;
    if (hoisted__Bool_2397) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2398 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_FuncPtr})));
    (void)hoisted__Bool_2398;
    if (hoisted__Bool_2398) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2399 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Dynamic})));
    (void)hoisted__Bool_2399;
    if (hoisted__Bool_2399) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2400 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Custom})));
    (void)hoisted__Bool_2400;
    if (hoisted__Bool_2400) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2387 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2387;
        Type *hoisted__Type_2388 = Type_Custom(hoisted__Str_2387);
        (void)hoisted__Type_2388;
        { Type * _ret_val = hoisted__Type_2388;
                return _ret_val; }
    }
    Bool hoisted__Bool_2401 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Primitive})));
    (void)hoisted__Bool_2401;
    if (hoisted__Bool_2401) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2389 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2389;
        Type *hoisted__Type_2390 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2389; _oa; }));
        (void)hoisted__Type_2390;
        { Type * _ret_val = hoisted__Type_2390;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2402 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2402;
    Type *hoisted__Type_2403 = Type_FuncPtrSig(hoisted__Str_2402);
    (void)hoisted__Type_2403;
    return hoisted__Type_2403;
}

U32 Type_size(void) {
    U32 hoisted__U32_2404 = 24;
    (void)hoisted__U32_2404;
    return hoisted__U32_2404;
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
    Bool hoisted__Bool_2507 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Func})));
    (void)hoisted__Bool_2507;
    if (hoisted__Bool_2507) {
        Bool hoisted__Bool_2497 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Func})));
        (void)hoisted__Bool_2497;
        { Bool _ret_val = hoisted__Bool_2497;
                return _ret_val; }
    }
    Bool hoisted__Bool_2508 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Proc})));
    (void)hoisted__Bool_2508;
    if (hoisted__Bool_2508) {
        Bool hoisted__Bool_2498 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Proc})));
        (void)hoisted__Bool_2498;
        { Bool _ret_val = hoisted__Bool_2498;
                return _ret_val; }
    }
    Bool hoisted__Bool_2509 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Test})));
    (void)hoisted__Bool_2509;
    if (hoisted__Bool_2509) {
        Bool hoisted__Bool_2499 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Test})));
        (void)hoisted__Bool_2499;
        { Bool _ret_val = hoisted__Bool_2499;
                return _ret_val; }
    }
    Bool hoisted__Bool_2510 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Macro})));
    (void)hoisted__Bool_2510;
    if (hoisted__Bool_2510) {
        Bool hoisted__Bool_2500 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Macro})));
        (void)hoisted__Bool_2500;
        { Bool _ret_val = hoisted__Bool_2500;
                return _ret_val; }
    }
    Bool hoisted__Bool_2511 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtFunc})));
    (void)hoisted__Bool_2511;
    if (hoisted__Bool_2511) {
        Bool hoisted__Bool_2501 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtFunc})));
        (void)hoisted__Bool_2501;
        { Bool _ret_val = hoisted__Bool_2501;
                return _ret_val; }
    }
    Bool hoisted__Bool_2512 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtProc})));
    (void)hoisted__Bool_2512;
    if (hoisted__Bool_2512) {
        Bool hoisted__Bool_2502 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtProc})));
        (void)hoisted__Bool_2502;
        { Bool _ret_val = hoisted__Bool_2502;
                return _ret_val; }
    }
    Bool hoisted__Bool_2513 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyFunc})));
    (void)hoisted__Bool_2513;
    if (hoisted__Bool_2513) {
        Bool hoisted__Bool_2503 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyFunc})));
        (void)hoisted__Bool_2503;
        { Bool _ret_val = hoisted__Bool_2503;
                return _ret_val; }
    }
    Bool hoisted__Bool_2514 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyProc})));
    (void)hoisted__Bool_2514;
    if (hoisted__Bool_2514) {
        Bool hoisted__Bool_2504 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyProc})));
        (void)hoisted__Bool_2504;
        { Bool _ret_val = hoisted__Bool_2504;
                return _ret_val; }
    }
    Bool hoisted__Bool_2515 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreFunc})));
    (void)hoisted__Bool_2515;
    if (hoisted__Bool_2515) {
        Bool hoisted__Bool_2505 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreFunc})));
        (void)hoisted__Bool_2505;
        { Bool _ret_val = hoisted__Bool_2505;
                return _ret_val; }
    }
    Bool hoisted__Bool_2516 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreProc})));
    (void)hoisted__Bool_2516;
    if (hoisted__Bool_2516) {
        Bool hoisted__Bool_2506 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreProc})));
        (void)hoisted__Bool_2506;
        { Bool _ret_val = hoisted__Bool_2506;
                return _ret_val; }
    }
    Bool hoisted__Bool_2517 = 0;
    (void)hoisted__Bool_2517;
    return hoisted__Bool_2517;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2539 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2539;
    if (hoisted__Bool_2539) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2540 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2540;
    if (hoisted__Bool_2540) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2541 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2541;
    if (hoisted__Bool_2541) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2542 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2542;
    if (hoisted__Bool_2542) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2543 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2543;
    if (hoisted__Bool_2543) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2544 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2544;
    if (hoisted__Bool_2544) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2545 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2545;
    if (hoisted__Bool_2545) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2546 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2546;
    if (hoisted__Bool_2546) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2547 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2547;
    if (hoisted__Bool_2547) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2548 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2548;
    if (hoisted__Bool_2548) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2549 = (Str){.c_str = (void *)"FuncType.clone:125:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2549;
    UNREACHABLE(&hoisted__Str_2549);
    Str_delete(&hoisted__Str_2549, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2550 = 4;
    (void)hoisted__U32_2550;
    return hoisted__U32_2550;
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
    Bool hoisted__Bool_2555 = ((Bool)(*(I32*)(self) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Own})));
    (void)hoisted__Bool_2555;
    if (hoisted__Bool_2555) {
        Bool hoisted__Bool_2552 = ((Bool)(*(I32*)(other) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Own})));
        (void)hoisted__Bool_2552;
        { Bool _ret_val = hoisted__Bool_2552;
                return _ret_val; }
    }
    Bool hoisted__Bool_2556 = ((Bool)(*(I32*)(self) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Ref})));
    (void)hoisted__Bool_2556;
    if (hoisted__Bool_2556) {
        Bool hoisted__Bool_2553 = ((Bool)(*(I32*)(other) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Ref})));
        (void)hoisted__Bool_2553;
        { Bool _ret_val = hoisted__Bool_2553;
                return _ret_val; }
    }
    Bool hoisted__Bool_2557 = ((Bool)(*(I32*)(self) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Shallow})));
    (void)hoisted__Bool_2557;
    if (hoisted__Bool_2557) {
        Bool hoisted__Bool_2554 = ((Bool)(*(I32*)(other) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Shallow})));
        (void)hoisted__Bool_2554;
        { Bool _ret_val = hoisted__Bool_2554;
                return _ret_val; }
    }
    Bool hoisted__Bool_2558 = 0;
    (void)hoisted__Bool_2558;
    return hoisted__Bool_2558;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2566 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2566;
    if (hoisted__Bool_2566) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2567 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2567;
    if (hoisted__Bool_2567) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2568 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2568;
    if (hoisted__Bool_2568) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2569 = (Str){.c_str = (void *)"OwnType.clone:137:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2569;
    UNREACHABLE(&hoisted__Str_2569);
    Str_delete(&hoisted__Str_2569, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2570 = 4;
    (void)hoisted__U32_2570;
    return hoisted__U32_2570;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2572 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2572;
    Declaration *hoisted__Declaration_2573 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2573->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2573->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2573->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2573->is_mut = self->is_mut;
    hoisted__Declaration_2573->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2573->is_priv = self->is_priv;
    hoisted__Declaration_2573->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2573->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2573->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2573->default_value = hoisted__Expr_2572;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2573->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2573;
    return hoisted__Declaration_2573;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2574 = 0;
    (void)hoisted__Bool_2574;
    Str_delete(&self->name, hoisted__Bool_2574);
    Bool hoisted__Bool_2575 = 0;
    (void)hoisted__Bool_2575;
    Str_delete(&self->doc, hoisted__Bool_2575);
    Bool hoisted__Bool_2576 = 0;
    (void)hoisted__Bool_2576;
    Str_delete(&self->explicit_type, hoisted__Bool_2576);
    Bool hoisted__Bool_2577 = 0;
    (void)hoisted__Bool_2577;
    Bool_delete(&self->is_mut, hoisted__Bool_2577);
    Bool hoisted__Bool_2578 = 0;
    (void)hoisted__Bool_2578;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2578);
    Bool hoisted__Bool_2579 = 0;
    (void)hoisted__Bool_2579;
    Bool_delete(&self->is_priv, hoisted__Bool_2579);
    Bool hoisted__Bool_2580 = 0;
    (void)hoisted__Bool_2580;
    Bool_delete(&self->used, hoisted__Bool_2580);
    Bool hoisted__Bool_2581 = 0;
    (void)hoisted__Bool_2581;
    OwnType_delete(&self->own_type, hoisted__Bool_2581);
    Bool hoisted__Bool_2582 = 0;
    (void)hoisted__Bool_2582;
    Type_delete(&self->til_type, hoisted__Bool_2582);
    Bool hoisted__Bool_2583 = 1;
    (void)hoisted__Bool_2583;
    Expr_delete(self->default_value, hoisted__Bool_2583);
    Bool hoisted__Bool_2584 = 0;
    (void)hoisted__Bool_2584;
    Str_delete(&self->orig_name, hoisted__Bool_2584);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2585 = 104;
    (void)hoisted__U32_2585;
    return hoisted__U32_2585;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2587 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2587->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2587->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2587->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2587->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2587->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2587->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2587->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2587->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2587->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2587->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2587->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2587;
    return hoisted__FunctionDef_2587;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    FuncType_delete(&self->func_type, hoisted__Bool_2588);
    Bool hoisted__Bool_2589 = 0;
    (void)hoisted__Bool_2589;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2589);
    Bool hoisted__Bool_2590 = 0;
    (void)hoisted__Bool_2590;
    Str_delete(&self->return_type, hoisted__Bool_2590);
    Bool hoisted__Bool_2591 = 0;
    (void)hoisted__Bool_2591;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2591);
    Bool hoisted__Bool_2592 = 0;
    (void)hoisted__Bool_2592;
    I32_delete(&self->variadic_index, hoisted__Bool_2592);
    Bool hoisted__Bool_2593 = 0;
    (void)hoisted__Bool_2593;
    I32_delete(&self->kwargs_index, hoisted__Bool_2593);
    Bool hoisted__Bool_2594 = 0;
    (void)hoisted__Bool_2594;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2594);
    Bool hoisted__Bool_2595 = 0;
    (void)hoisted__Bool_2595;
    Bool_delete(&self->auto_generated, hoisted__Bool_2595);
    Bool hoisted__Bool_2596 = 0;
    (void)hoisted__Bool_2596;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2596);
    Bool hoisted__Bool_2597 = 0;
    (void)hoisted__Bool_2597;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2597);
    Bool hoisted__Bool_2598 = 0;
    (void)hoisted__Bool_2598;
    Str_delete(&self->closure_name, hoisted__Bool_2598);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2599 = 0;
    (void)hoisted__U32_2599;
    U64 hoisted__U64_2600 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2599); });
    (void)hoisted__U64_2600;
    return hoisted__U64_2600;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2601 = 104;
    (void)hoisted__U32_2601;
    return hoisted__U32_2601;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2604 = malloc(sizeof(FCallData));
    hoisted__FCallData_2604->is_splat = self->is_splat;
    hoisted__FCallData_2604->does_throw = self->does_throw;
    hoisted__FCallData_2604->is_bang = self->is_bang;
    hoisted__FCallData_2604->own_args = self->own_args;
    hoisted__FCallData_2604->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2604->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2604;
    return hoisted__FCallData_2604;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    Bool_delete(&self->is_splat, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    Bool_delete(&self->does_throw, hoisted__Bool_2606);
    Bool hoisted__Bool_2607 = 0;
    (void)hoisted__Bool_2607;
    Bool_delete(&self->is_bang, hoisted__Bool_2607);
    Bool hoisted__Bool_2608 = 0;
    (void)hoisted__Bool_2608;
    U64_delete(&self->own_args, hoisted__Bool_2608);
    Bool hoisted__Bool_2609 = 0;
    (void)hoisted__Bool_2609;
    Bool_delete(&self->swap_replace, hoisted__Bool_2609);
    Bool hoisted__Bool_2610 = 0;
    (void)hoisted__Bool_2610;
    Type_delete(&self->til_type, hoisted__Bool_2610);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2611 = 0;
    (void)hoisted__U32_2611;
    U64 hoisted__U64_2612 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2611); });
    (void)hoisted__U64_2612;
    return hoisted__U64_2612;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2613 = 48;
    (void)hoisted__U32_2613;
    return hoisted__U32_2613;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2625 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2625->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2625->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2625;
    return hoisted__LiteralNumData_2625;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2626 = 0;
    (void)hoisted__Bool_2626;
    Str_delete(&self->text, hoisted__Bool_2626);
    Bool hoisted__Bool_2627 = 0;
    (void)hoisted__Bool_2627;
    Type_delete(&self->til_type, hoisted__Bool_2627);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2628 = 0;
    (void)hoisted__U32_2628;
    U64 hoisted__U64_2629 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2628); });
    (void)hoisted__U64_2629;
    return hoisted__U64_2629;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2630 = 40;
    (void)hoisted__U32_2630;
    return hoisted__U32_2630;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2640 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2640->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2640->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2640;
    return hoisted__IdentData_2640;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2641 = 0;
    (void)hoisted__Bool_2641;
    Str_delete(&self->name, hoisted__Bool_2641);
    Bool hoisted__Bool_2642 = 0;
    (void)hoisted__Bool_2642;
    Type_delete(&self->til_type, hoisted__Bool_2642);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2643 = 0;
    (void)hoisted__U32_2643;
    U64 hoisted__U64_2644 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2643); });
    (void)hoisted__U64_2644;
    return hoisted__U64_2644;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2645 = 40;
    (void)hoisted__U32_2645;
    return hoisted__U32_2645;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2651 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2651->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2651->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2651;
    return hoisted__FieldAccessData_2651;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2652 = 0;
    (void)hoisted__Bool_2652;
    Str_delete(&self->name, hoisted__Bool_2652);
    Bool hoisted__Bool_2653 = 0;
    (void)hoisted__Bool_2653;
    Type_delete(&self->til_type, hoisted__Bool_2653);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2654 = 0;
    (void)hoisted__U32_2654;
    U64 hoisted__U64_2655 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2654); });
    (void)hoisted__U64_2655;
    return hoisted__U64_2655;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2656 = 40;
    (void)hoisted__U32_2656;
    return hoisted__U32_2656;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2737 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2737->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2737->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2737->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2737->is_interface = self->is_interface;
    hoisted__StructDef_2737->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2737->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2737;
    return hoisted__StructDef_2737;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2738 = 0;
    (void)hoisted__Bool_2738;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2738);
    Bool hoisted__Bool_2739 = 0;
    (void)hoisted__Bool_2739;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2739);
    Bool hoisted__Bool_2740 = 0;
    (void)hoisted__Bool_2740;
    Str_delete(&self->c_tag, hoisted__Bool_2740);
    Bool hoisted__Bool_2741 = 0;
    (void)hoisted__Bool_2741;
    Bool_delete(&self->is_interface, hoisted__Bool_2741);
    Bool hoisted__Bool_2742 = 0;
    (void)hoisted__Bool_2742;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2742);
    Bool hoisted__Bool_2743 = 0;
    (void)hoisted__Bool_2743;
    Str_delete(&self->implements_name, hoisted__Bool_2743);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2744 = 0;
    (void)hoisted__U32_2744;
    U64 hoisted__U64_2745 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2744); });
    (void)hoisted__U64_2745;
    return hoisted__U64_2745;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2746 = 72;
    (void)hoisted__U32_2746;
    return hoisted__U32_2746;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2751 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2751->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2751->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2751->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2751->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2751->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2751->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2751;
    return hoisted__EnumDef_2751;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2752 = 0;
    (void)hoisted__Bool_2752;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2752);
    Bool hoisted__Bool_2753 = 0;
    (void)hoisted__Bool_2753;
    Vec__Str_delete(&self->variants, hoisted__Bool_2753);
    Bool hoisted__Bool_2754 = 0;
    (void)hoisted__Bool_2754;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2754);
    Bool hoisted__Bool_2755 = 0;
    (void)hoisted__Bool_2755;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2755);
    Bool hoisted__Bool_2756 = 0;
    (void)hoisted__Bool_2756;
    Str_delete(&self->implements_name, hoisted__Bool_2756);
    Bool hoisted__Bool_2757 = 0;
    (void)hoisted__Bool_2757;
    Str_delete(&self->tag_type, hoisted__Bool_2757);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2758 = 0;
    (void)hoisted__U32_2758;
    U64 hoisted__U64_2759 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2758); });
    (void)hoisted__U64_2759;
    return hoisted__U64_2759;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2760 = 112;
    (void)hoisted__U32_2760;
    return hoisted__U32_2760;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2860 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2860->name = *_ca; free(_ca); }
    hoisted__AssignData_2860->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2860->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2860->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2860;
    return hoisted__AssignData_2860;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2861 = 0;
    (void)hoisted__Bool_2861;
    Str_delete(&self->name, hoisted__Bool_2861);
    Bool hoisted__Bool_2862 = 0;
    (void)hoisted__Bool_2862;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2862);
    Bool hoisted__Bool_2863 = 0;
    (void)hoisted__Bool_2863;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2863);
    Bool hoisted__Bool_2864 = 0;
    (void)hoisted__Bool_2864;
    Bool_delete(&self->swap_replace, hoisted__Bool_2864);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2865 = 0;
    (void)hoisted__U32_2865;
    U64 hoisted__U64_2866 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2865); });
    (void)hoisted__U64_2866;
    return hoisted__U64_2866;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2867 = 24;
    (void)hoisted__U32_2867;
    return hoisted__U32_2867;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2869 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2869->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2869->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2869;
    return hoisted__FieldAssignData_2869;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2870 = 0;
    (void)hoisted__Bool_2870;
    Str_delete(&self->name, hoisted__Bool_2870);
    Bool hoisted__Bool_2871 = 0;
    (void)hoisted__Bool_2871;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2871);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2872 = 0;
    (void)hoisted__U32_2872;
    U64 hoisted__U64_2873 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2872); });
    (void)hoisted__U64_2873;
    return hoisted__U64_2873;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2874 = 24;
    (void)hoisted__U32_2874;
    return hoisted__U32_2874;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2876 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2876->name = *_ca; free(_ca); }
    hoisted__ForInData_2876->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2876->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2876->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2876->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2876;
    return hoisted__ForInData_2876;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2877 = 0;
    (void)hoisted__Bool_2877;
    Str_delete(&self->name, hoisted__Bool_2877);
    Bool hoisted__Bool_2878 = 0;
    (void)hoisted__Bool_2878;
    Bool_delete(&self->is_mut, hoisted__Bool_2878);
    Bool hoisted__Bool_2879 = 0;
    (void)hoisted__Bool_2879;
    Type_delete(&self->til_type, hoisted__Bool_2879);
    Bool hoisted__Bool_2880 = 0;
    (void)hoisted__Bool_2880;
    Str_delete(&self->name2, hoisted__Bool_2880);
    Bool hoisted__Bool_2881 = 0;
    (void)hoisted__Bool_2881;
    Bool_delete(&self->is_mut2, hoisted__Bool_2881);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2882 = 0;
    (void)hoisted__U32_2882;
    U64 hoisted__U64_2883 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2882); });
    (void)hoisted__U64_2883;
    return hoisted__U64_2883;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2884 = 72;
    (void)hoisted__U32_2884;
    return hoisted__U32_2884;
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
    Bool hoisted__Bool_2914 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Str})));
    (void)hoisted__Bool_2914;
    if (hoisted__Bool_2914) {
        Str *hoisted__Str_2908 = get_payload(self);
        (void)hoisted__Str_2908;
        (void)hoisted__Str_2908;
        Bool hoisted__Bool_2909 = 0;
        (void)hoisted__Bool_2909;
        Str_delete(hoisted__Str_2908, hoisted__Bool_2909);
    }
    Bool hoisted__Bool_2915 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Num})));
    (void)hoisted__Bool_2915;
    if (hoisted__Bool_2915) {
        LiteralNumData *hoisted__LiteralNumData_2910 = get_payload(self);
        (void)hoisted__LiteralNumData_2910;
        (void)hoisted__LiteralNumData_2910;
        Bool hoisted__Bool_2911 = 0;
        (void)hoisted__Bool_2911;
        LiteralNumData_delete(hoisted__LiteralNumData_2910, hoisted__Bool_2911);
    }
    Bool hoisted__Bool_2916 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Bool})));
    (void)hoisted__Bool_2916;
    if (hoisted__Bool_2916) {
        Bool *hoisted__Bool_2912 = get_payload(self);
        (void)hoisted__Bool_2912;
        (void)hoisted__Bool_2912;
        Bool hoisted__Bool_2913 = 0;
        (void)hoisted__Bool_2913;
        Bool_delete(hoisted__Bool_2912, hoisted__Bool_2913);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2965 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Str})));
    (void)hoisted__Bool_2965;
    if (hoisted__Bool_2965) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2960 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2960;
        Literal *hoisted__Literal_2961 = Literal_Str(hoisted__Str_2960);
        (void)hoisted__Literal_2961;
        { Literal * _ret_val = hoisted__Literal_2961;
                return _ret_val; }
    }
    Bool hoisted__Bool_2966 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Num})));
    (void)hoisted__Bool_2966;
    if (hoisted__Bool_2966) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2962 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2962;
        Literal *hoisted__Literal_2963 = Literal_Num(hoisted__LiteralNumData_2962);
        (void)hoisted__Literal_2963;
        { Literal * _ret_val = hoisted__Literal_2963;
                return _ret_val; }
    }
    Bool hoisted__Bool_2967 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Bool})));
    (void)hoisted__Bool_2967;
    if (hoisted__Bool_2967) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2964 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2964;
        { Literal * _ret_val = hoisted__Literal_2964;
                return _ret_val; }
    }
    Bool hoisted__Bool_2968 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Null})));
    (void)hoisted__Bool_2968;
    if (hoisted__Bool_2968) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2969 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_MapLit})));
    (void)hoisted__Bool_2969;
    if (hoisted__Bool_2969) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2970 = 48;
    (void)hoisted__U32_2970;
    return hoisted__U32_2970;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2973 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2973->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2973->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2973;
    return hoisted__MatchData_2973;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2974 = 0;
    (void)hoisted__Bool_2974;
    Type_delete(&self->til_type, hoisted__Bool_2974);
    Bool hoisted__Bool_2975 = 0;
    (void)hoisted__Bool_2975;
    Str_delete(&self->result_temp, hoisted__Bool_2975);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2976 = 0;
    (void)hoisted__U32_2976;
    U64 hoisted__U64_2977 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2976); });
    (void)hoisted__U64_2977;
    return hoisted__U64_2977;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2978 = 40;
    (void)hoisted__U32_2978;
    return hoisted__U32_2978;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2983 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2983->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2983;
    return hoisted__CaptureBlockData_2983;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2984 = 0;
    (void)hoisted__Bool_2984;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2984);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2985 = 0;
    (void)hoisted__U32_2985;
    U64 hoisted__U64_2986 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2985); });
    (void)hoisted__U64_2986;
    return hoisted__U64_2986;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2987 = 16;
    (void)hoisted__U32_2987;
    return hoisted__U32_2987;
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
    Bool hoisted__Bool_3166 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Literal})));
    (void)hoisted__Bool_3166;
    if (hoisted__Bool_3166) {
        Literal *hoisted__Literal_3138 = get_payload(self);
        (void)hoisted__Literal_3138;
        (void)hoisted__Literal_3138;
        Bool hoisted__Bool_3139 = 0;
        (void)hoisted__Bool_3139;
        Literal_delete(hoisted__Literal_3138, hoisted__Bool_3139);
    }
    Bool hoisted__Bool_3167 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Ident})));
    (void)hoisted__Bool_3167;
    if (hoisted__Bool_3167) {
        IdentData *hoisted__IdentData_3140 = get_payload(self);
        (void)hoisted__IdentData_3140;
        (void)hoisted__IdentData_3140;
        Bool hoisted__Bool_3141 = 0;
        (void)hoisted__Bool_3141;
        IdentData_delete(hoisted__IdentData_3140, hoisted__Bool_3141);
    }
    Bool hoisted__Bool_3168 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Decl})));
    (void)hoisted__Bool_3168;
    if (hoisted__Bool_3168) {
        Declaration *hoisted__Declaration_3142 = get_payload(self);
        (void)hoisted__Declaration_3142;
        (void)hoisted__Declaration_3142;
        Bool hoisted__Bool_3143 = 0;
        (void)hoisted__Bool_3143;
        Declaration_delete(hoisted__Declaration_3142, hoisted__Bool_3143);
    }
    Bool hoisted__Bool_3169 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Assign})));
    (void)hoisted__Bool_3169;
    if (hoisted__Bool_3169) {
        AssignData *hoisted__AssignData_3144 = get_payload(self);
        (void)hoisted__AssignData_3144;
        (void)hoisted__AssignData_3144;
        Bool hoisted__Bool_3145 = 0;
        (void)hoisted__Bool_3145;
        AssignData_delete(hoisted__AssignData_3144, hoisted__Bool_3145);
    }
    Bool hoisted__Bool_3170 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FCall})));
    (void)hoisted__Bool_3170;
    if (hoisted__Bool_3170) {
        FCallData *hoisted__FCallData_3146 = get_payload(self);
        (void)hoisted__FCallData_3146;
        (void)hoisted__FCallData_3146;
        Bool hoisted__Bool_3147 = 0;
        (void)hoisted__Bool_3147;
        FCallData_delete(hoisted__FCallData_3146, hoisted__Bool_3147);
    }
    Bool hoisted__Bool_3171 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FuncDef})));
    (void)hoisted__Bool_3171;
    if (hoisted__Bool_3171) {
        FunctionDef *hoisted__FunctionDef_3148 = get_payload(self);
        (void)hoisted__FunctionDef_3148;
        (void)hoisted__FunctionDef_3148;
        Bool hoisted__Bool_3149 = 0;
        (void)hoisted__Bool_3149;
        FunctionDef_delete(hoisted__FunctionDef_3148, hoisted__Bool_3149);
    }
    Bool hoisted__Bool_3172 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_StructDef})));
    (void)hoisted__Bool_3172;
    if (hoisted__Bool_3172) {
        StructDef *hoisted__StructDef_3150 = get_payload(self);
        (void)hoisted__StructDef_3150;
        (void)hoisted__StructDef_3150;
        Bool hoisted__Bool_3151 = 0;
        (void)hoisted__Bool_3151;
        StructDef_delete(hoisted__StructDef_3150, hoisted__Bool_3151);
    }
    Bool hoisted__Bool_3173 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_EnumDef})));
    (void)hoisted__Bool_3173;
    if (hoisted__Bool_3173) {
        EnumDef *hoisted__EnumDef_3152 = get_payload(self);
        (void)hoisted__EnumDef_3152;
        (void)hoisted__EnumDef_3152;
        Bool hoisted__Bool_3153 = 0;
        (void)hoisted__Bool_3153;
        EnumDef_delete(hoisted__EnumDef_3152, hoisted__Bool_3153);
    }
    Bool hoisted__Bool_3174 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAccess})));
    (void)hoisted__Bool_3174;
    if (hoisted__Bool_3174) {
        FieldAccessData *hoisted__FieldAccessData_3154 = get_payload(self);
        (void)hoisted__FieldAccessData_3154;
        (void)hoisted__FieldAccessData_3154;
        Bool hoisted__Bool_3155 = 0;
        (void)hoisted__Bool_3155;
        FieldAccessData_delete(hoisted__FieldAccessData_3154, hoisted__Bool_3155);
    }
    Bool hoisted__Bool_3175 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAssign})));
    (void)hoisted__Bool_3175;
    if (hoisted__Bool_3175) {
        FieldAssignData *hoisted__FieldAssignData_3156 = get_payload(self);
        (void)hoisted__FieldAssignData_3156;
        (void)hoisted__FieldAssignData_3156;
        Bool hoisted__Bool_3157 = 0;
        (void)hoisted__Bool_3157;
        FieldAssignData_delete(hoisted__FieldAssignData_3156, hoisted__Bool_3157);
    }
    Bool hoisted__Bool_3176 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_ForIn})));
    (void)hoisted__Bool_3176;
    if (hoisted__Bool_3176) {
        ForInData *hoisted__ForInData_3158 = get_payload(self);
        (void)hoisted__ForInData_3158;
        (void)hoisted__ForInData_3158;
        Bool hoisted__Bool_3159 = 0;
        (void)hoisted__Bool_3159;
        ForInData_delete(hoisted__ForInData_3158, hoisted__Bool_3159);
    }
    Bool hoisted__Bool_3177 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_NamedArg})));
    (void)hoisted__Bool_3177;
    if (hoisted__Bool_3177) {
        Str *hoisted__Str_3160 = get_payload(self);
        (void)hoisted__Str_3160;
        (void)hoisted__Str_3160;
        Bool hoisted__Bool_3161 = 0;
        (void)hoisted__Bool_3161;
        Str_delete(hoisted__Str_3160, hoisted__Bool_3161);
    }
    Bool hoisted__Bool_3178 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Match})));
    (void)hoisted__Bool_3178;
    if (hoisted__Bool_3178) {
        MatchData *hoisted__MatchData_3162 = get_payload(self);
        (void)hoisted__MatchData_3162;
        (void)hoisted__MatchData_3162;
        Bool hoisted__Bool_3163 = 0;
        (void)hoisted__Bool_3163;
        MatchData_delete(hoisted__MatchData_3162, hoisted__Bool_3163);
    }
    Bool hoisted__Bool_3179 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_CaptureBlock})));
    (void)hoisted__Bool_3179;
    if (hoisted__Bool_3179) {
        CaptureBlockData *hoisted__CaptureBlockData_3164 = get_payload(self);
        (void)hoisted__CaptureBlockData_3164;
        (void)hoisted__CaptureBlockData_3164;
        Bool hoisted__Bool_3165 = 0;
        (void)hoisted__Bool_3165;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3164, hoisted__Bool_3165);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3403 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Body})));
    (void)hoisted__Bool_3403;
    if (hoisted__Bool_3403) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3404 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Literal})));
    (void)hoisted__Bool_3404;
    if (hoisted__Bool_3404) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3375 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3375;
        NodeType *hoisted__NodeType_3376 = NodeType_Literal(hoisted__Literal_3375);
        (void)hoisted__NodeType_3376;
        { NodeType * _ret_val = hoisted__NodeType_3376;
                return _ret_val; }
    }
    Bool hoisted__Bool_3405 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Ident})));
    (void)hoisted__Bool_3405;
    if (hoisted__Bool_3405) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3377 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3377;
        NodeType *hoisted__NodeType_3378 = NodeType_Ident(hoisted__IdentData_3377);
        (void)hoisted__NodeType_3378;
        { NodeType * _ret_val = hoisted__NodeType_3378;
                return _ret_val; }
    }
    Bool hoisted__Bool_3406 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Decl})));
    (void)hoisted__Bool_3406;
    if (hoisted__Bool_3406) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3379 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3379;
        NodeType *hoisted__NodeType_3380 = NodeType_Decl(hoisted__Declaration_3379);
        (void)hoisted__NodeType_3380;
        { NodeType * _ret_val = hoisted__NodeType_3380;
                return _ret_val; }
    }
    Bool hoisted__Bool_3407 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Assign})));
    (void)hoisted__Bool_3407;
    if (hoisted__Bool_3407) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3381 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3381;
        NodeType *hoisted__NodeType_3382 = NodeType_Assign(hoisted__AssignData_3381);
        (void)hoisted__NodeType_3382;
        { NodeType * _ret_val = hoisted__NodeType_3382;
                return _ret_val; }
    }
    Bool hoisted__Bool_3408 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FCall})));
    (void)hoisted__Bool_3408;
    if (hoisted__Bool_3408) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3383 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3383;
        NodeType *hoisted__NodeType_3384 = NodeType_FCall(hoisted__FCallData_3383);
        (void)hoisted__NodeType_3384;
        { NodeType * _ret_val = hoisted__NodeType_3384;
                return _ret_val; }
    }
    Bool hoisted__Bool_3409 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FuncDef})));
    (void)hoisted__Bool_3409;
    if (hoisted__Bool_3409) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3385 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3385;
        NodeType *hoisted__NodeType_3386 = NodeType_FuncDef(hoisted__FunctionDef_3385);
        (void)hoisted__NodeType_3386;
        { NodeType * _ret_val = hoisted__NodeType_3386;
                return _ret_val; }
    }
    Bool hoisted__Bool_3410 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_StructDef})));
    (void)hoisted__Bool_3410;
    if (hoisted__Bool_3410) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3387 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3387;
        NodeType *hoisted__NodeType_3388 = NodeType_StructDef(hoisted__StructDef_3387);
        (void)hoisted__NodeType_3388;
        { NodeType * _ret_val = hoisted__NodeType_3388;
                return _ret_val; }
    }
    Bool hoisted__Bool_3411 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_EnumDef})));
    (void)hoisted__Bool_3411;
    if (hoisted__Bool_3411) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3389 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3389;
        NodeType *hoisted__NodeType_3390 = NodeType_EnumDef(hoisted__EnumDef_3389);
        (void)hoisted__NodeType_3390;
        { NodeType * _ret_val = hoisted__NodeType_3390;
                return _ret_val; }
    }
    Bool hoisted__Bool_3412 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAccess})));
    (void)hoisted__Bool_3412;
    if (hoisted__Bool_3412) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3391 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3391;
        NodeType *hoisted__NodeType_3392 = NodeType_FieldAccess(hoisted__FieldAccessData_3391);
        (void)hoisted__NodeType_3392;
        { NodeType * _ret_val = hoisted__NodeType_3392;
                return _ret_val; }
    }
    Bool hoisted__Bool_3413 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAssign})));
    (void)hoisted__Bool_3413;
    if (hoisted__Bool_3413) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3393 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3393;
        NodeType *hoisted__NodeType_3394 = NodeType_FieldAssign(hoisted__FieldAssignData_3393);
        (void)hoisted__NodeType_3394;
        { NodeType * _ret_val = hoisted__NodeType_3394;
                return _ret_val; }
    }
    Bool hoisted__Bool_3414 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Return})));
    (void)hoisted__Bool_3414;
    if (hoisted__Bool_3414) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3415 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_If})));
    (void)hoisted__Bool_3415;
    if (hoisted__Bool_3415) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3416 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_While})));
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3417 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_ForIn})));
    (void)hoisted__Bool_3417;
    if (hoisted__Bool_3417) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3395 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3395;
        NodeType *hoisted__NodeType_3396 = NodeType_ForIn(hoisted__ForInData_3395);
        (void)hoisted__NodeType_3396;
        { NodeType * _ret_val = hoisted__NodeType_3396;
                return _ret_val; }
    }
    Bool hoisted__Bool_3418 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_NamedArg})));
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3397 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3397;
        NodeType *hoisted__NodeType_3398 = NodeType_NamedArg(hoisted__Str_3397);
        (void)hoisted__NodeType_3398;
        { NodeType * _ret_val = hoisted__NodeType_3398;
                return _ret_val; }
    }
    Bool hoisted__Bool_3419 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Break})));
    (void)hoisted__Bool_3419;
    if (hoisted__Bool_3419) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3420 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Continue})));
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3421 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Switch})));
    (void)hoisted__Bool_3421;
    if (hoisted__Bool_3421) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3422 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Match})));
    (void)hoisted__Bool_3422;
    if (hoisted__Bool_3422) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3399 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3399;
        NodeType *hoisted__NodeType_3400 = NodeType_Match(hoisted__MatchData_3399);
        (void)hoisted__NodeType_3400;
        { NodeType * _ret_val = hoisted__NodeType_3400;
                return _ret_val; }
    }
    Bool hoisted__Bool_3423 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Case})));
    (void)hoisted__Bool_3423;
    if (hoisted__Bool_3423) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3424 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg})));
    (void)hoisted__Bool_3424;
    if (hoisted__Bool_3424) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3425 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Throw})));
    (void)hoisted__Bool_3425;
    if (hoisted__Bool_3425) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3426 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Catch})));
    (void)hoisted__Bool_3426;
    if (hoisted__Bool_3426) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3427 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_RestPattern})));
    (void)hoisted__Bool_3427;
    if (hoisted__Bool_3427) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3428 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_CaptureBlock})));
    (void)hoisted__Bool_3428;
    if (hoisted__Bool_3428) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3401 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3401;
        NodeType *hoisted__NodeType_3402 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3401);
        (void)hoisted__NodeType_3402;
        { NodeType * _ret_val = hoisted__NodeType_3402;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3429 = 120;
    (void)hoisted__U32_3429;
    return hoisted__U32_3429;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3430 = is_null(self);
    (void)hoisted__Bool_3430;
    if (hoisted__Bool_3430) {
        return;
    }
    Bool hoisted__Bool_3431 = 0;
    (void)hoisted__Bool_3431;
    NodeType_delete(&self->node_type, hoisted__Bool_3431);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3481 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3481->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3481->children = *_ca; free(_ca); }
    hoisted__Expr_3481->line = line;
    hoisted__Expr_3481->col = col;
    (void)hoisted__Expr_3481;
    return hoisted__Expr_3481;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3490 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3490->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3490->children = *_ca; free(_ca); }
    hoisted__Expr_3490->line = self->line;
    hoisted__Expr_3490->col = self->col;
    (void)hoisted__Expr_3490;
    return hoisted__Expr_3490;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3491 = 0;
    (void)hoisted__U32_3491;
    U64 hoisted__U64_3492 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3491); });
    (void)hoisted__U64_3492;
    return hoisted__U64_3492;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3493 = 144;
    (void)hoisted__U32_3493;
    return hoisted__U32_3493;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4437 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4437->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4437->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4437;
    return hoisted__Map__I64_Str_4437;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4550 = 0;
    (void)hoisted__Bool_4550;
    Vec__I64_delete(&self->keys, hoisted__Bool_4550);
    Bool hoisted__Bool_4551 = 0;
    (void)hoisted__Bool_4551;
    Vec__Str_delete(&self->values, hoisted__Bool_4551);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4552 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4552->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4552->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4552;
    return hoisted__Map__I64_Str_4552;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4553 = 0;
    (void)hoisted__U32_4553;
    U64 hoisted__U64_4554 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4553); });
    (void)hoisted__U64_4554;
    return hoisted__U64_4554;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4555 = 32;
    (void)hoisted__U32_4555;
    return hoisted__U32_4555;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4556 = 1;
    (void)hoisted__U32_4556;
    U64 hoisted__U64_4557 = (U64)(hoisted__U32_4556);
    (void)hoisted__U64_4557;
    void * hoisted__v_4558 = malloc(hoisted__U64_4557);
    (void)hoisted__v_4558;
    U32 hoisted__U32_4559 = 0;
    (void)hoisted__U32_4559;
    I64 hoisted__I64_4560 = 1;
    (void)hoisted__I64_4560;
    Vec__Bool *hoisted__Vec__Bool_4561 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4561->data = hoisted__v_4558;
    hoisted__Vec__Bool_4561->count = hoisted__U32_4559;
    hoisted__Vec__Bool_4561->cap = hoisted__I64_4560;
    (void)hoisted__Vec__Bool_4561;
    return hoisted__Vec__Bool_4561;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4571 = self->count;
        (void)_re_U32_4571;
        U32 _rc_U32_4571 = 0;
        (void)_rc_U32_4571;
        Bool hoisted__Bool_4584 = ((Bool)(_rc_U32_4571 <= _re_U32_4571));
        (void)hoisted__Bool_4584;
        if (hoisted__Bool_4584) {
            while (1) {
                Bool _wcond_Bool_4572 = ((Bool)(_rc_U32_4571 < _re_U32_4571));
                (void)_wcond_Bool_4572;
                if (_wcond_Bool_4572) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4571);
                U32_inc(&_rc_U32_4571);
                U32 hoisted__U32_4573 = 1;
                (void)hoisted__U32_4573;
                U32 hoisted__U32_4574 = ((U32)(i * hoisted__U32_4573));
                (void)hoisted__U32_4574;
                U64 hoisted__U64_4575 = (U64)(hoisted__U32_4574);
                (void)hoisted__U64_4575;
                Bool *hoisted__Bool_4576 = ptr_add(self->data, hoisted__U64_4575);
                (void)hoisted__Bool_4576;
                (void)hoisted__Bool_4576;
                Bool hoisted__Bool_4577 = 0;
                (void)hoisted__Bool_4577;
                Bool_delete(hoisted__Bool_4576, hoisted__Bool_4577);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4578 = ((Bool)(_rc_U32_4571 > _re_U32_4571));
                (void)_wcond_Bool_4578;
                if (_wcond_Bool_4578) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4571);
                U32_dec(&_rc_U32_4571);
                U32 hoisted__U32_4579 = 1;
                (void)hoisted__U32_4579;
                U32 hoisted__U32_4580 = ((U32)(i * hoisted__U32_4579));
                (void)hoisted__U32_4580;
                U64 hoisted__U64_4581 = (U64)(hoisted__U32_4580);
                (void)hoisted__U64_4581;
                Bool *hoisted__Bool_4582 = ptr_add(self->data, hoisted__U64_4581);
                (void)hoisted__Bool_4582;
                (void)hoisted__Bool_4582;
                Bool hoisted__Bool_4583 = 0;
                (void)hoisted__Bool_4583;
                Bool_delete(hoisted__Bool_4582, hoisted__Bool_4583);
            }
        }
    }
    U32 hoisted__U32_4585 = 0;
    (void)hoisted__U32_4585;
    self->count = hoisted__U32_4585;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4855 = 1;
    (void)hoisted__U32_4855;
    U32 hoisted__U32_4856 = ((U32)(self->cap * hoisted__U32_4855));
    (void)hoisted__U32_4856;
    U64 hoisted__U64_4857 = (U64)(hoisted__U32_4856);
    (void)hoisted__U64_4857;
    void * new_data = malloc(hoisted__U64_4857);
    {
        U32 _re_U32_4827 = self->count;
        (void)_re_U32_4827;
        U32 _rc_U32_4827 = 0;
        (void)_rc_U32_4827;
        Bool hoisted__Bool_4854 = ((Bool)(_rc_U32_4827 <= _re_U32_4827));
        (void)hoisted__Bool_4854;
        if (hoisted__Bool_4854) {
            while (1) {
                Bool _wcond_Bool_4828 = ((Bool)(_rc_U32_4827 < _re_U32_4827));
                (void)_wcond_Bool_4828;
                if (_wcond_Bool_4828) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4827);
                U32_inc(&_rc_U32_4827);
                U32 hoisted__U32_4829 = 1;
                (void)hoisted__U32_4829;
                U32 hoisted__U32_4830 = ((U32)(i * hoisted__U32_4829));
                (void)hoisted__U32_4830;
                U64 hoisted__U64_4831 = (U64)(hoisted__U32_4830);
                (void)hoisted__U64_4831;
                Bool *src = ptr_add(self->data, hoisted__U64_4831);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4832 = 1;
                (void)hoisted__U32_4832;
                U32 hoisted__U32_4833 = ((U32)(i * hoisted__U32_4832));
                (void)hoisted__U32_4833;
                U64 hoisted__U64_4834 = (U64)(hoisted__U32_4833);
                (void)hoisted__U64_4834;
                U32 hoisted__U32_4835 = 1;
                (void)hoisted__U32_4835;
                void *hoisted__v_4836 = ptr_add(new_data, hoisted__U64_4834);
                (void)hoisted__v_4836;
                (void)hoisted__v_4836;
                U64 hoisted__U64_4837 = (U64)(hoisted__U32_4835);
                (void)hoisted__U64_4837;
                memcpy(hoisted__v_4836, &cloned, hoisted__U64_4837);
                U32 hoisted__U32_4838 = 1;
                (void)hoisted__U32_4838;
                I32 hoisted__I32_4839 = 0;
                (void)hoisted__I32_4839;
                U64 hoisted__U64_4840 = (U64)(hoisted__U32_4838);
                (void)hoisted__U64_4840;
                memset(&cloned, hoisted__I32_4839, hoisted__U64_4840);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4841 = ((Bool)(_rc_U32_4827 > _re_U32_4827));
                (void)_wcond_Bool_4841;
                if (_wcond_Bool_4841) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4827);
                U32_dec(&_rc_U32_4827);
                U32 hoisted__U32_4842 = 1;
                (void)hoisted__U32_4842;
                U32 hoisted__U32_4843 = ((U32)(i * hoisted__U32_4842));
                (void)hoisted__U32_4843;
                U64 hoisted__U64_4844 = (U64)(hoisted__U32_4843);
                (void)hoisted__U64_4844;
                Bool *src = ptr_add(self->data, hoisted__U64_4844);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4845 = 1;
                (void)hoisted__U32_4845;
                U32 hoisted__U32_4846 = ((U32)(i * hoisted__U32_4845));
                (void)hoisted__U32_4846;
                U64 hoisted__U64_4847 = (U64)(hoisted__U32_4846);
                (void)hoisted__U64_4847;
                U32 hoisted__U32_4848 = 1;
                (void)hoisted__U32_4848;
                void *hoisted__v_4849 = ptr_add(new_data, hoisted__U64_4847);
                (void)hoisted__v_4849;
                (void)hoisted__v_4849;
                U64 hoisted__U64_4850 = (U64)(hoisted__U32_4848);
                (void)hoisted__U64_4850;
                memcpy(hoisted__v_4849, &cloned, hoisted__U64_4850);
                U32 hoisted__U32_4851 = 1;
                (void)hoisted__U32_4851;
                I32 hoisted__I32_4852 = 0;
                (void)hoisted__I32_4852;
                U64 hoisted__U64_4853 = (U64)(hoisted__U32_4851);
                (void)hoisted__U64_4853;
                memset(&cloned, hoisted__I32_4852, hoisted__U64_4853);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4858 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4858->data = new_data;
    hoisted__Vec__Bool_4858->count = self->count;
    hoisted__Vec__Bool_4858->cap = self->cap;
    (void)hoisted__Vec__Bool_4858;
    return hoisted__Vec__Bool_4858;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4859 = 16;
    (void)hoisted__U32_4859;
    return hoisted__U32_4859;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5164 = 104;
    (void)hoisted__U32_5164;
    U64 hoisted__U64_5165 = (U64)(hoisted__U32_5164);
    (void)hoisted__U64_5165;
    void * hoisted__v_5166 = malloc(hoisted__U64_5165);
    (void)hoisted__v_5166;
    U32 hoisted__U32_5167 = 0;
    (void)hoisted__U32_5167;
    I64 hoisted__I64_5168 = 1;
    (void)hoisted__I64_5168;
    Vec__Declaration *hoisted__Vec__Declaration_5169 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5169->data = hoisted__v_5166;
    hoisted__Vec__Declaration_5169->count = hoisted__U32_5167;
    hoisted__Vec__Declaration_5169->cap = hoisted__I64_5168;
    (void)hoisted__Vec__Declaration_5169;
    return hoisted__Vec__Declaration_5169;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5179 = self->count;
        (void)_re_U32_5179;
        U32 _rc_U32_5179 = 0;
        (void)_rc_U32_5179;
        Bool hoisted__Bool_5192 = ((Bool)(_rc_U32_5179 <= _re_U32_5179));
        (void)hoisted__Bool_5192;
        if (hoisted__Bool_5192) {
            while (1) {
                Bool _wcond_Bool_5180 = ((Bool)(_rc_U32_5179 < _re_U32_5179));
                (void)_wcond_Bool_5180;
                if (_wcond_Bool_5180) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5179);
                U32_inc(&_rc_U32_5179);
                U32 hoisted__U32_5181 = 104;
                (void)hoisted__U32_5181;
                U32 hoisted__U32_5182 = ((U32)(i * hoisted__U32_5181));
                (void)hoisted__U32_5182;
                U64 hoisted__U64_5183 = (U64)(hoisted__U32_5182);
                (void)hoisted__U64_5183;
                Declaration *hoisted__Declaration_5184 = ptr_add(self->data, hoisted__U64_5183);
                (void)hoisted__Declaration_5184;
                (void)hoisted__Declaration_5184;
                Bool hoisted__Bool_5185 = 0;
                (void)hoisted__Bool_5185;
                Declaration_delete(hoisted__Declaration_5184, hoisted__Bool_5185);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5186 = ((Bool)(_rc_U32_5179 > _re_U32_5179));
                (void)_wcond_Bool_5186;
                if (_wcond_Bool_5186) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5179);
                U32_dec(&_rc_U32_5179);
                U32 hoisted__U32_5187 = 104;
                (void)hoisted__U32_5187;
                U32 hoisted__U32_5188 = ((U32)(i * hoisted__U32_5187));
                (void)hoisted__U32_5188;
                U64 hoisted__U64_5189 = (U64)(hoisted__U32_5188);
                (void)hoisted__U64_5189;
                Declaration *hoisted__Declaration_5190 = ptr_add(self->data, hoisted__U64_5189);
                (void)hoisted__Declaration_5190;
                (void)hoisted__Declaration_5190;
                Bool hoisted__Bool_5191 = 0;
                (void)hoisted__Bool_5191;
                Declaration_delete(hoisted__Declaration_5190, hoisted__Bool_5191);
            }
        }
    }
    U32 hoisted__U32_5193 = 0;
    (void)hoisted__U32_5193;
    self->count = hoisted__U32_5193;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5463 = 104;
    (void)hoisted__U32_5463;
    U32 hoisted__U32_5464 = ((U32)(self->cap * hoisted__U32_5463));
    (void)hoisted__U32_5464;
    U64 hoisted__U64_5465 = (U64)(hoisted__U32_5464);
    (void)hoisted__U64_5465;
    void * new_data = malloc(hoisted__U64_5465);
    {
        U32 _re_U32_5435 = self->count;
        (void)_re_U32_5435;
        U32 _rc_U32_5435 = 0;
        (void)_rc_U32_5435;
        Bool hoisted__Bool_5462 = ((Bool)(_rc_U32_5435 <= _re_U32_5435));
        (void)hoisted__Bool_5462;
        if (hoisted__Bool_5462) {
            while (1) {
                Bool _wcond_Bool_5436 = ((Bool)(_rc_U32_5435 < _re_U32_5435));
                (void)_wcond_Bool_5436;
                if (_wcond_Bool_5436) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5435);
                U32_inc(&_rc_U32_5435);
                U32 hoisted__U32_5437 = 104;
                (void)hoisted__U32_5437;
                U32 hoisted__U32_5438 = ((U32)(i * hoisted__U32_5437));
                (void)hoisted__U32_5438;
                U64 hoisted__U64_5439 = (U64)(hoisted__U32_5438);
                (void)hoisted__U64_5439;
                Declaration *src = ptr_add(self->data, hoisted__U64_5439);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5440 = 104;
                (void)hoisted__U32_5440;
                U32 hoisted__U32_5441 = ((U32)(i * hoisted__U32_5440));
                (void)hoisted__U32_5441;
                U64 hoisted__U64_5442 = (U64)(hoisted__U32_5441);
                (void)hoisted__U64_5442;
                U32 hoisted__U32_5443 = 104;
                (void)hoisted__U32_5443;
                void *hoisted__v_5444 = ptr_add(new_data, hoisted__U64_5442);
                (void)hoisted__v_5444;
                (void)hoisted__v_5444;
                U64 hoisted__U64_5445 = (U64)(hoisted__U32_5443);
                (void)hoisted__U64_5445;
                memcpy(hoisted__v_5444, cloned, hoisted__U64_5445);
                U32 hoisted__U32_5446 = 104;
                (void)hoisted__U32_5446;
                I32 hoisted__I32_5447 = 0;
                (void)hoisted__I32_5447;
                U64 hoisted__U64_5448 = (U64)(hoisted__U32_5446);
                (void)hoisted__U64_5448;
                memset(cloned, hoisted__I32_5447, hoisted__U64_5448);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5449 = ((Bool)(_rc_U32_5435 > _re_U32_5435));
                (void)_wcond_Bool_5449;
                if (_wcond_Bool_5449) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5435);
                U32_dec(&_rc_U32_5435);
                U32 hoisted__U32_5450 = 104;
                (void)hoisted__U32_5450;
                U32 hoisted__U32_5451 = ((U32)(i * hoisted__U32_5450));
                (void)hoisted__U32_5451;
                U64 hoisted__U64_5452 = (U64)(hoisted__U32_5451);
                (void)hoisted__U64_5452;
                Declaration *src = ptr_add(self->data, hoisted__U64_5452);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5453 = 104;
                (void)hoisted__U32_5453;
                U32 hoisted__U32_5454 = ((U32)(i * hoisted__U32_5453));
                (void)hoisted__U32_5454;
                U64 hoisted__U64_5455 = (U64)(hoisted__U32_5454);
                (void)hoisted__U64_5455;
                U32 hoisted__U32_5456 = 104;
                (void)hoisted__U32_5456;
                void *hoisted__v_5457 = ptr_add(new_data, hoisted__U64_5455);
                (void)hoisted__v_5457;
                (void)hoisted__v_5457;
                U64 hoisted__U64_5458 = (U64)(hoisted__U32_5456);
                (void)hoisted__U64_5458;
                memcpy(hoisted__v_5457, cloned, hoisted__U64_5458);
                U32 hoisted__U32_5459 = 104;
                (void)hoisted__U32_5459;
                I32 hoisted__I32_5460 = 0;
                (void)hoisted__I32_5460;
                U64 hoisted__U64_5461 = (U64)(hoisted__U32_5459);
                (void)hoisted__U64_5461;
                memset(cloned, hoisted__I32_5460, hoisted__U64_5461);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5466 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5466->data = new_data;
    hoisted__Vec__Declaration_5466->count = self->count;
    hoisted__Vec__Declaration_5466->cap = self->cap;
    (void)hoisted__Vec__Declaration_5466;
    return hoisted__Vec__Declaration_5466;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5467 = 16;
    (void)hoisted__U32_5467;
    return hoisted__U32_5467;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5468 = 144;
    (void)hoisted__U32_5468;
    U64 hoisted__U64_5469 = (U64)(hoisted__U32_5468);
    (void)hoisted__U64_5469;
    void * hoisted__v_5470 = malloc(hoisted__U64_5469);
    (void)hoisted__v_5470;
    U32 hoisted__U32_5471 = 0;
    (void)hoisted__U32_5471;
    I64 hoisted__I64_5472 = 1;
    (void)hoisted__I64_5472;
    Vec__Expr *hoisted__Vec__Expr_5473 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5473->data = hoisted__v_5470;
    hoisted__Vec__Expr_5473->count = hoisted__U32_5471;
    hoisted__Vec__Expr_5473->cap = hoisted__I64_5472;
    (void)hoisted__Vec__Expr_5473;
    return hoisted__Vec__Expr_5473;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5483 = self->count;
        (void)_re_U32_5483;
        U32 _rc_U32_5483 = 0;
        (void)_rc_U32_5483;
        Bool hoisted__Bool_5496 = ((Bool)(_rc_U32_5483 <= _re_U32_5483));
        (void)hoisted__Bool_5496;
        if (hoisted__Bool_5496) {
            while (1) {
                Bool _wcond_Bool_5484 = ((Bool)(_rc_U32_5483 < _re_U32_5483));
                (void)_wcond_Bool_5484;
                if (_wcond_Bool_5484) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5483);
                U32_inc(&_rc_U32_5483);
                U32 hoisted__U32_5485 = 144;
                (void)hoisted__U32_5485;
                U32 hoisted__U32_5486 = ((U32)(i * hoisted__U32_5485));
                (void)hoisted__U32_5486;
                U64 hoisted__U64_5487 = (U64)(hoisted__U32_5486);
                (void)hoisted__U64_5487;
                Expr *hoisted__Expr_5488 = ptr_add(self->data, hoisted__U64_5487);
                (void)hoisted__Expr_5488;
                (void)hoisted__Expr_5488;
                Bool hoisted__Bool_5489 = 0;
                (void)hoisted__Bool_5489;
                Expr_delete(hoisted__Expr_5488, hoisted__Bool_5489);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5490 = ((Bool)(_rc_U32_5483 > _re_U32_5483));
                (void)_wcond_Bool_5490;
                if (_wcond_Bool_5490) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5483);
                U32_dec(&_rc_U32_5483);
                U32 hoisted__U32_5491 = 144;
                (void)hoisted__U32_5491;
                U32 hoisted__U32_5492 = ((U32)(i * hoisted__U32_5491));
                (void)hoisted__U32_5492;
                U64 hoisted__U64_5493 = (U64)(hoisted__U32_5492);
                (void)hoisted__U64_5493;
                Expr *hoisted__Expr_5494 = ptr_add(self->data, hoisted__U64_5493);
                (void)hoisted__Expr_5494;
                (void)hoisted__Expr_5494;
                Bool hoisted__Bool_5495 = 0;
                (void)hoisted__Bool_5495;
                Expr_delete(hoisted__Expr_5494, hoisted__Bool_5495);
            }
        }
    }
    U32 hoisted__U32_5497 = 0;
    (void)hoisted__U32_5497;
    self->count = hoisted__U32_5497;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5767 = 144;
    (void)hoisted__U32_5767;
    U32 hoisted__U32_5768 = ((U32)(self->cap * hoisted__U32_5767));
    (void)hoisted__U32_5768;
    U64 hoisted__U64_5769 = (U64)(hoisted__U32_5768);
    (void)hoisted__U64_5769;
    void * new_data = malloc(hoisted__U64_5769);
    {
        U32 _re_U32_5739 = self->count;
        (void)_re_U32_5739;
        U32 _rc_U32_5739 = 0;
        (void)_rc_U32_5739;
        Bool hoisted__Bool_5766 = ((Bool)(_rc_U32_5739 <= _re_U32_5739));
        (void)hoisted__Bool_5766;
        if (hoisted__Bool_5766) {
            while (1) {
                Bool _wcond_Bool_5740 = ((Bool)(_rc_U32_5739 < _re_U32_5739));
                (void)_wcond_Bool_5740;
                if (_wcond_Bool_5740) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5739);
                U32_inc(&_rc_U32_5739);
                U32 hoisted__U32_5741 = 144;
                (void)hoisted__U32_5741;
                U32 hoisted__U32_5742 = ((U32)(i * hoisted__U32_5741));
                (void)hoisted__U32_5742;
                U64 hoisted__U64_5743 = (U64)(hoisted__U32_5742);
                (void)hoisted__U64_5743;
                Expr *src = ptr_add(self->data, hoisted__U64_5743);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5744 = 144;
                (void)hoisted__U32_5744;
                U32 hoisted__U32_5745 = ((U32)(i * hoisted__U32_5744));
                (void)hoisted__U32_5745;
                U64 hoisted__U64_5746 = (U64)(hoisted__U32_5745);
                (void)hoisted__U64_5746;
                U32 hoisted__U32_5747 = 144;
                (void)hoisted__U32_5747;
                void *hoisted__v_5748 = ptr_add(new_data, hoisted__U64_5746);
                (void)hoisted__v_5748;
                (void)hoisted__v_5748;
                U64 hoisted__U64_5749 = (U64)(hoisted__U32_5747);
                (void)hoisted__U64_5749;
                memcpy(hoisted__v_5748, cloned, hoisted__U64_5749);
                U32 hoisted__U32_5750 = 144;
                (void)hoisted__U32_5750;
                I32 hoisted__I32_5751 = 0;
                (void)hoisted__I32_5751;
                U64 hoisted__U64_5752 = (U64)(hoisted__U32_5750);
                (void)hoisted__U64_5752;
                memset(cloned, hoisted__I32_5751, hoisted__U64_5752);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5753 = ((Bool)(_rc_U32_5739 > _re_U32_5739));
                (void)_wcond_Bool_5753;
                if (_wcond_Bool_5753) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5739);
                U32_dec(&_rc_U32_5739);
                U32 hoisted__U32_5754 = 144;
                (void)hoisted__U32_5754;
                U32 hoisted__U32_5755 = ((U32)(i * hoisted__U32_5754));
                (void)hoisted__U32_5755;
                U64 hoisted__U64_5756 = (U64)(hoisted__U32_5755);
                (void)hoisted__U64_5756;
                Expr *src = ptr_add(self->data, hoisted__U64_5756);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5757 = 144;
                (void)hoisted__U32_5757;
                U32 hoisted__U32_5758 = ((U32)(i * hoisted__U32_5757));
                (void)hoisted__U32_5758;
                U64 hoisted__U64_5759 = (U64)(hoisted__U32_5758);
                (void)hoisted__U64_5759;
                U32 hoisted__U32_5760 = 144;
                (void)hoisted__U32_5760;
                void *hoisted__v_5761 = ptr_add(new_data, hoisted__U64_5759);
                (void)hoisted__v_5761;
                (void)hoisted__v_5761;
                U64 hoisted__U64_5762 = (U64)(hoisted__U32_5760);
                (void)hoisted__U64_5762;
                memcpy(hoisted__v_5761, cloned, hoisted__U64_5762);
                U32 hoisted__U32_5763 = 144;
                (void)hoisted__U32_5763;
                I32 hoisted__I32_5764 = 0;
                (void)hoisted__I32_5764;
                U64 hoisted__U64_5765 = (U64)(hoisted__U32_5763);
                (void)hoisted__U64_5765;
                memset(cloned, hoisted__I32_5764, hoisted__U64_5765);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5770 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5770->data = new_data;
    hoisted__Vec__Expr_5770->count = self->count;
    hoisted__Vec__Expr_5770->cap = self->cap;
    (void)hoisted__Vec__Expr_5770;
    return hoisted__Vec__Expr_5770;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5771 = 16;
    (void)hoisted__U32_5771;
    return hoisted__U32_5771;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5772 = 8;
    (void)hoisted__U32_5772;
    U64 hoisted__U64_5773 = (U64)(hoisted__U32_5772);
    (void)hoisted__U64_5773;
    void * hoisted__v_5774 = malloc(hoisted__U64_5773);
    (void)hoisted__v_5774;
    U32 hoisted__U32_5775 = 0;
    (void)hoisted__U32_5775;
    I64 hoisted__I64_5776 = 1;
    (void)hoisted__I64_5776;
    Vec__I64 *hoisted__Vec__I64_5777 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5777->data = hoisted__v_5774;
    hoisted__Vec__I64_5777->count = hoisted__U32_5775;
    hoisted__Vec__I64_5777->cap = hoisted__I64_5776;
    (void)hoisted__Vec__I64_5777;
    return hoisted__Vec__I64_5777;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5787 = self->count;
        (void)_re_U32_5787;
        U32 _rc_U32_5787 = 0;
        (void)_rc_U32_5787;
        Bool hoisted__Bool_5800 = ((Bool)(_rc_U32_5787 <= _re_U32_5787));
        (void)hoisted__Bool_5800;
        if (hoisted__Bool_5800) {
            while (1) {
                Bool _wcond_Bool_5788 = ((Bool)(_rc_U32_5787 < _re_U32_5787));
                (void)_wcond_Bool_5788;
                if (_wcond_Bool_5788) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5787);
                U32_inc(&_rc_U32_5787);
                U32 hoisted__U32_5789 = 8;
                (void)hoisted__U32_5789;
                U32 hoisted__U32_5790 = ((U32)(i * hoisted__U32_5789));
                (void)hoisted__U32_5790;
                U64 hoisted__U64_5791 = (U64)(hoisted__U32_5790);
                (void)hoisted__U64_5791;
                I64 *hoisted__I64_5792 = ptr_add(self->data, hoisted__U64_5791);
                (void)hoisted__I64_5792;
                (void)hoisted__I64_5792;
                Bool hoisted__Bool_5793 = 0;
                (void)hoisted__Bool_5793;
                I64_delete(hoisted__I64_5792, hoisted__Bool_5793);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5794 = ((Bool)(_rc_U32_5787 > _re_U32_5787));
                (void)_wcond_Bool_5794;
                if (_wcond_Bool_5794) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5787);
                U32_dec(&_rc_U32_5787);
                U32 hoisted__U32_5795 = 8;
                (void)hoisted__U32_5795;
                U32 hoisted__U32_5796 = ((U32)(i * hoisted__U32_5795));
                (void)hoisted__U32_5796;
                U64 hoisted__U64_5797 = (U64)(hoisted__U32_5796);
                (void)hoisted__U64_5797;
                I64 *hoisted__I64_5798 = ptr_add(self->data, hoisted__U64_5797);
                (void)hoisted__I64_5798;
                (void)hoisted__I64_5798;
                Bool hoisted__Bool_5799 = 0;
                (void)hoisted__Bool_5799;
                I64_delete(hoisted__I64_5798, hoisted__Bool_5799);
            }
        }
    }
    U32 hoisted__U32_5801 = 0;
    (void)hoisted__U32_5801;
    self->count = hoisted__U32_5801;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_6071 = 8;
    (void)hoisted__U32_6071;
    U32 hoisted__U32_6072 = ((U32)(self->cap * hoisted__U32_6071));
    (void)hoisted__U32_6072;
    U64 hoisted__U64_6073 = (U64)(hoisted__U32_6072);
    (void)hoisted__U64_6073;
    void * new_data = malloc(hoisted__U64_6073);
    {
        U32 _re_U32_6043 = self->count;
        (void)_re_U32_6043;
        U32 _rc_U32_6043 = 0;
        (void)_rc_U32_6043;
        Bool hoisted__Bool_6070 = ((Bool)(_rc_U32_6043 <= _re_U32_6043));
        (void)hoisted__Bool_6070;
        if (hoisted__Bool_6070) {
            while (1) {
                Bool _wcond_Bool_6044 = ((Bool)(_rc_U32_6043 < _re_U32_6043));
                (void)_wcond_Bool_6044;
                if (_wcond_Bool_6044) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6043);
                U32_inc(&_rc_U32_6043);
                U32 hoisted__U32_6045 = 8;
                (void)hoisted__U32_6045;
                U32 hoisted__U32_6046 = ((U32)(i * hoisted__U32_6045));
                (void)hoisted__U32_6046;
                U64 hoisted__U64_6047 = (U64)(hoisted__U32_6046);
                (void)hoisted__U64_6047;
                I64 *src = ptr_add(self->data, hoisted__U64_6047);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6048 = 8;
                (void)hoisted__U32_6048;
                U32 hoisted__U32_6049 = ((U32)(i * hoisted__U32_6048));
                (void)hoisted__U32_6049;
                U64 hoisted__U64_6050 = (U64)(hoisted__U32_6049);
                (void)hoisted__U64_6050;
                U32 hoisted__U32_6051 = 8;
                (void)hoisted__U32_6051;
                void *hoisted__v_6052 = ptr_add(new_data, hoisted__U64_6050);
                (void)hoisted__v_6052;
                (void)hoisted__v_6052;
                U64 hoisted__U64_6053 = (U64)(hoisted__U32_6051);
                (void)hoisted__U64_6053;
                memcpy(hoisted__v_6052, &cloned, hoisted__U64_6053);
                U32 hoisted__U32_6054 = 8;
                (void)hoisted__U32_6054;
                I32 hoisted__I32_6055 = 0;
                (void)hoisted__I32_6055;
                U64 hoisted__U64_6056 = (U64)(hoisted__U32_6054);
                (void)hoisted__U64_6056;
                memset(&cloned, hoisted__I32_6055, hoisted__U64_6056);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6057 = ((Bool)(_rc_U32_6043 > _re_U32_6043));
                (void)_wcond_Bool_6057;
                if (_wcond_Bool_6057) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6043);
                U32_dec(&_rc_U32_6043);
                U32 hoisted__U32_6058 = 8;
                (void)hoisted__U32_6058;
                U32 hoisted__U32_6059 = ((U32)(i * hoisted__U32_6058));
                (void)hoisted__U32_6059;
                U64 hoisted__U64_6060 = (U64)(hoisted__U32_6059);
                (void)hoisted__U64_6060;
                I64 *src = ptr_add(self->data, hoisted__U64_6060);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_6061 = 8;
                (void)hoisted__U32_6061;
                U32 hoisted__U32_6062 = ((U32)(i * hoisted__U32_6061));
                (void)hoisted__U32_6062;
                U64 hoisted__U64_6063 = (U64)(hoisted__U32_6062);
                (void)hoisted__U64_6063;
                U32 hoisted__U32_6064 = 8;
                (void)hoisted__U32_6064;
                void *hoisted__v_6065 = ptr_add(new_data, hoisted__U64_6063);
                (void)hoisted__v_6065;
                (void)hoisted__v_6065;
                U64 hoisted__U64_6066 = (U64)(hoisted__U32_6064);
                (void)hoisted__U64_6066;
                memcpy(hoisted__v_6065, &cloned, hoisted__U64_6066);
                U32 hoisted__U32_6067 = 8;
                (void)hoisted__U32_6067;
                I32 hoisted__I32_6068 = 0;
                (void)hoisted__I32_6068;
                U64 hoisted__U64_6069 = (U64)(hoisted__U32_6067);
                (void)hoisted__U64_6069;
                memset(&cloned, hoisted__I32_6068, hoisted__U64_6069);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_6074 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_6074->data = new_data;
    hoisted__Vec__I64_6074->count = self->count;
    hoisted__Vec__I64_6074->cap = self->cap;
    (void)hoisted__Vec__I64_6074;
    return hoisted__Vec__I64_6074;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_6075 = 16;
    (void)hoisted__U32_6075;
    return hoisted__U32_6075;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7194 = 3;
    (void)hoisted__U32_7194;
    Array__Str *_va_Array_204 = Array__Str_new(hoisted__U32_7194);
    (void)_va_Array_204;
    I64 _va_Array_204_ek = 0;
    (void)_va_Array_204_ek;
    OutOfBounds *_va_Array_204_eo = malloc(sizeof(OutOfBounds));
    _va_Array_204_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_204_eo;
    U32 hoisted__U32_7195 = 0;
    (void)hoisted__U32_7195;
    Str *hoisted__Str_7196 = Str_clone(loc);
    (void)hoisted__Str_7196;
    (void)hoisted__Str_7197;
    (void)hoisted__Str_7197;
    Array__Str_set(_va_Array_204, hoisted__U32_7195, hoisted__Str_7196, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7197);
    Str_delete(&hoisted__Str_7197, (Bool){0});
    U32 hoisted__U32_7198 = 1;
    (void)hoisted__U32_7198;
    (void)hoisted__Str_7199;
    (void)hoisted__Str_7199;
    (void)hoisted__Str_7200;
    (void)hoisted__Str_7200;
    Array__Str_set(_va_Array_204, hoisted__U32_7198, &hoisted__Str_7199, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7200);
    Str_delete(&hoisted__Str_7200, (Bool){0});
    Array__Str *hoisted__Array__Str_7201 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7201;
    U32 hoisted__U32_7202 = 2;
    (void)hoisted__U32_7202;
    Str *hoisted__Str_7203 = format(hoisted__Array__Str_7201);
    (void)hoisted__Str_7203;
    (void)hoisted__Str_7204;
    (void)hoisted__Str_7204;
    Array__Str_set(_va_Array_204, hoisted__U32_7202, hoisted__Str_7203, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7204);
    OutOfBounds_delete(_va_Array_204_eo, 1);
    Str_delete(&hoisted__Str_7204, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_204);
    I64 hoisted__I64_7205 = 1;
    (void)hoisted__I64_7205;
    exit(hoisted__I64_7205);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7214 = 1;
    (void)hoisted__U32_7214;
    Array__Str *_va_Array_206 = Array__Str_new(hoisted__U32_7214);
    (void)_va_Array_206;
    I64 _va_Array_206_ek = 0;
    (void)_va_Array_206_ek;
    OutOfBounds *_va_Array_206_eo = malloc(sizeof(OutOfBounds));
    _va_Array_206_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_206_eo;
    U32 hoisted__U32_7215 = 0;
    (void)hoisted__U32_7215;
    (void)hoisted__Str_7216;
    (void)hoisted__Str_7216;
    (void)hoisted__Str_7217;
    (void)hoisted__Str_7217;
    Array__Str_set(_va_Array_206, hoisted__U32_7215, &hoisted__Str_7216, &_va_Array_206_ek, _va_Array_206_eo, &hoisted__Str_7217);
    OutOfBounds_delete(_va_Array_206_eo, 1);
    Str_delete(&hoisted__Str_7217, (Bool){0});
    panic(_va_Array_206, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7222 = not(cond);
    (void)hoisted__Bool_7222;
    if (hoisted__Bool_7222) {
        U32 hoisted__U32_7218 = 1;
        (void)hoisted__U32_7218;
        Array__Str *_va_Array_207 = Array__Str_new(hoisted__U32_7218);
        (void)_va_Array_207;
        I64 _va_Array_207_ek = 0;
        (void)_va_Array_207_ek;
        OutOfBounds *_va_Array_207_eo = malloc(sizeof(OutOfBounds));
        _va_Array_207_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_207_eo;
        U32 hoisted__U32_7219 = 0;
        (void)hoisted__U32_7219;
        (void)hoisted__Str_7220;
        (void)hoisted__Str_7220;
        (void)hoisted__Str_7221;
        (void)hoisted__Str_7221;
        Array__Str_set(_va_Array_207, hoisted__U32_7219, &hoisted__Str_7220, &_va_Array_207_ek, _va_Array_207_eo, &hoisted__Str_7221);
        OutOfBounds_delete(_va_Array_207_eo, 1);
        Str_delete(&hoisted__Str_7221, (Bool){0});
        panic(_va_Array_207, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7232 = parts;
        (void)_fc_Array__Str_7232;
        (void)_fc_Array__Str_7232;
        U32 _fi_USize_7232 = 0;
        (void)_fi_USize_7232;
        while (1) {
            U32 hoisted__U32_7234 = Array__Str_len(_fc_Array__Str_7232);
            (void)hoisted__U32_7234;
            Bool _wcond_Bool_7233 = ((Bool)(_fi_USize_7232 < hoisted__U32_7234));
            (void)_wcond_Bool_7233;
            if (_wcond_Bool_7233) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7232, &_fi_USize_7232);
            U32 hoisted__U32_7235 = 1;
            (void)hoisted__U32_7235;
            U32 hoisted__U32_7236 = ((U32)(_fi_USize_7232 + hoisted__U32_7235));
            (void)hoisted__U32_7236;
            _fi_USize_7232 = hoisted__U32_7236;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7270 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7270;
    return hoisted__Bool_7270;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7279 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7279;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7279;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7280 = 0;
    (void)hoisted__U32_7280;
    U64 hoisted__U64_7281 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7280); });
    (void)hoisted__U64_7281;
    return hoisted__U64_7281;
}

U32 Range_size(void) {
    U32 hoisted__U32_7312 = 16;
    (void)hoisted__U32_7312;
    return hoisted__U32_7312;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7328 = 3;
    (void)hoisted__I64_7328;
    (void)hoisted__Str_7329;
    (void)hoisted__Str_7329;
    assert_eq__I64(result, hoisted__I64_7328, &hoisted__Str_7329);
    Str_delete(&hoisted__Str_7329, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7336 = 15;
    (void)hoisted__I64_7336;
    (void)hoisted__Str_7337;
    (void)hoisted__Str_7337;
    assert_eq__I64(result, hoisted__I64_7336, &hoisted__Str_7337);
    Str_delete(&hoisted__Str_7337, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7344 = 26;
    (void)hoisted__I64_7344;
    (void)hoisted__Str_7345;
    (void)hoisted__Str_7345;
    assert_eq__I64(result, hoisted__I64_7344, &hoisted__Str_7345);
    Str_delete(&hoisted__Str_7345, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7348;
    (void)hoisted__Str_7348;
    (void)hoisted__Str_7349;
    (void)hoisted__Str_7349;
    assert_eq__Str(&result, &hoisted__Str_7348, &hoisted__Str_7349);
    Str_delete(&hoisted__Str_7348, (Bool){0});
    Str_delete(&hoisted__Str_7349, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7377;
    (void)hoisted__Str_7377;
    (void)hoisted__Str_7378;
    (void)hoisted__Str_7378;
    assert_eq__Str(&r, &hoisted__Str_7377, &hoisted__Str_7378);
    Str_delete(&hoisted__Str_7377, (Bool){0});
    Str_delete(&hoisted__Str_7378, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7382;
    (void)hoisted__Str_7382;
    (void)hoisted__Str_7383;
    (void)hoisted__Str_7383;
    assert_eq__Str(&r2, &hoisted__Str_7382, &hoisted__Str_7383);
    Str_delete(&hoisted__Str_7382, (Bool){0});
    Str_delete(&hoisted__Str_7383, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7406;
    (void)hoisted__Str_7406;
    (void)hoisted__Str_7407;
    (void)hoisted__Str_7407;
    assert_eq__Str(&d, &hoisted__Str_7406, &hoisted__Str_7407);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7406, (Bool){0});
    Str_delete(&hoisted__Str_7407, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7418;
    (void)hoisted__Str_7418;
    (void)hoisted__Str_7419;
    (void)hoisted__Str_7419;
    assert_eq__Str(&d2, &hoisted__Str_7418, &hoisted__Str_7419);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7418, (Bool){0});
    Str_delete(&hoisted__Str_7419, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7431 = 106;
    (void)hoisted__I64_7431;
    (void)hoisted__Str_7432;
    (void)hoisted__Str_7432;
    assert_eq__I64(d3, hoisted__I64_7431, &hoisted__Str_7432);
    Str_delete(&hoisted__Str_7432, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8031;
    (void)hoisted__Str_8031;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8031);
    Str_delete(&hoisted__Str_8031, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)hoisted__Str_8032;
    (void)hoisted__Str_8032;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8032);
    Str_delete(&hoisted__Str_8032, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8034 = 8;
    (void)hoisted__I64_8034;
    (void)hoisted__Str_8035;
    (void)hoisted__Str_8035;
    assert_eq__I64(result, hoisted__I64_8034, &hoisted__Str_8035);
    Str_delete(&hoisted__Str_8035, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8038 = 1;
    (void)hoisted__Bool_8038;
    (void)hoisted__Str_8039;
    (void)hoisted__Str_8039;
    assert(hoisted__Bool_8038, &hoisted__Str_8039);
    Str_delete(&hoisted__Str_8039, (Bool){0});
    Bool hoisted__Bool_8042 = 1;
    (void)hoisted__Bool_8042;
    (void)hoisted__Str_8043;
    (void)hoisted__Str_8043;
    assert(hoisted__Bool_8042, &hoisted__Str_8043);
    Str_delete(&hoisted__Str_8043, (Bool){0});
}

void test_fold_f32(void) {
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8049;
    (void)hoisted__Str_8049;
    (void)hoisted__Str_8050;
    (void)hoisted__Str_8050;
    assert_eq__Str(&hoisted__Str_8048, &hoisted__Str_8049, &hoisted__Str_8050);
    Str_delete(&hoisted__Str_8048, (Bool){0});
    Str_delete(&hoisted__Str_8049, (Bool){0});
    Str_delete(&hoisted__Str_8050, (Bool){0});
    (void)hoisted__Str_8053;
    (void)hoisted__Str_8053;
    (void)hoisted__Str_8054;
    (void)hoisted__Str_8054;
    (void)hoisted__Str_8055;
    (void)hoisted__Str_8055;
    assert_eq__Str(&hoisted__Str_8053, &hoisted__Str_8054, &hoisted__Str_8055);
    Str_delete(&hoisted__Str_8053, (Bool){0});
    Str_delete(&hoisted__Str_8054, (Bool){0});
    Str_delete(&hoisted__Str_8055, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8060 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8060;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8060;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8061 = 0;
    (void)hoisted__U32_8061;
    U64 hoisted__U64_8062 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8061); });
    (void)hoisted__U64_8062;
    return hoisted__U64_8062;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8093 = 16;
    (void)hoisted__U32_8093;
    return hoisted__U32_8093;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8094 = 42;
    (void)hoisted__I64_8094;
    (void)hoisted__Str_8095;
    (void)hoisted__Str_8095;
    assert_eq__I64(v.x, hoisted__I64_8094, &hoisted__Str_8095);
    Str_delete(&hoisted__Str_8095, (Bool){0});
    I64 hoisted__I64_8096 = 99;
    (void)hoisted__I64_8096;
    (void)hoisted__Str_8097;
    (void)hoisted__Str_8097;
    assert_eq__I64(v.y, hoisted__I64_8096, &hoisted__Str_8097);
    Str_delete(&hoisted__Str_8097, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8100 = 10;
    (void)hoisted__I64_8100;
    (void)hoisted__Str_8101;
    (void)hoisted__Str_8101;
    assert_eq__I64(p.x, hoisted__I64_8100, &hoisted__Str_8101);
    Str_delete(&hoisted__Str_8101, (Bool){0});
    I64 hoisted__I64_8102 = 20;
    (void)hoisted__I64_8102;
    (void)hoisted__Str_8103;
    (void)hoisted__Str_8103;
    assert_eq__I64(p.y, hoisted__I64_8102, &hoisted__Str_8103);
    Str_delete(&hoisted__Str_8103, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8109 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8109;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8109;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8110 = 0;
    (void)hoisted__U32_8110;
    U64 hoisted__U64_8111 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8110); });
    (void)hoisted__U64_8111;
    return hoisted__U64_8111;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8142 = 32;
    (void)hoisted__U32_8142;
    return hoisted__U32_8142;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8143 = 5;
    (void)hoisted__I64_8143;
    (void)hoisted__Str_8144;
    (void)hoisted__Str_8144;
    assert_eq__I64(r.top_left.x, hoisted__I64_8143, &hoisted__Str_8144);
    Str_delete(&hoisted__Str_8144, (Bool){0});
    I64 hoisted__I64_8145 = 10;
    (void)hoisted__I64_8145;
    (void)hoisted__Str_8146;
    (void)hoisted__Str_8146;
    assert_eq__I64(r.top_left.y, hoisted__I64_8145, &hoisted__Str_8146);
    Str_delete(&hoisted__Str_8146, (Bool){0});
    I64 hoisted__I64_8147 = 100;
    (void)hoisted__I64_8147;
    (void)hoisted__Str_8148;
    (void)hoisted__Str_8148;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8147, &hoisted__Str_8148);
    Str_delete(&hoisted__Str_8148, (Bool){0});
    I64 hoisted__I64_8149 = 200;
    (void)hoisted__I64_8149;
    (void)hoisted__Str_8150;
    (void)hoisted__Str_8150;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8149, &hoisted__Str_8150);
    Str_delete(&hoisted__Str_8150, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8152 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8152;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8152;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8153 = 0;
    (void)hoisted__U32_8153;
    U64 hoisted__U64_8154 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8153); });
    (void)hoisted__U64_8154;
    return hoisted__U64_8154;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8197 = 12;
    (void)hoisted__U32_8197;
    return hoisted__U32_8197;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8201 = F32_to_str(v.x);
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8202;
    (void)hoisted__Str_8202;
    (void)hoisted__Str_8203;
    (void)hoisted__Str_8203;
    assert_eq__Str(hoisted__Str_8201, &hoisted__Str_8202, &hoisted__Str_8203);
    Str_delete(hoisted__Str_8201, 1);
    Str_delete(&hoisted__Str_8202, (Bool){0});
    Str_delete(&hoisted__Str_8203, (Bool){0});
    Str *hoisted__Str_8204 = F32_to_str(v.y);
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8205;
    (void)hoisted__Str_8205;
    (void)hoisted__Str_8206;
    (void)hoisted__Str_8206;
    assert_eq__Str(hoisted__Str_8204, &hoisted__Str_8205, &hoisted__Str_8206);
    Str_delete(hoisted__Str_8204, 1);
    Str_delete(&hoisted__Str_8205, (Bool){0});
    Str_delete(&hoisted__Str_8206, (Bool){0});
    Str *hoisted__Str_8207 = F32_to_str(v.z);
    (void)hoisted__Str_8207;
    (void)hoisted__Str_8208;
    (void)hoisted__Str_8208;
    (void)hoisted__Str_8209;
    (void)hoisted__Str_8209;
    assert_eq__Str(hoisted__Str_8207, &hoisted__Str_8208, &hoisted__Str_8209);
    Str_delete(hoisted__Str_8207, 1);
    Str_delete(&hoisted__Str_8208, (Bool){0});
    Str_delete(&hoisted__Str_8209, (Bool){0});
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
    Bool hoisted__Bool_8214 = ((Bool)(*(I32*)(self) == *(I32*)(&(Color){.tag = Color_TAG_Red})));
    (void)hoisted__Bool_8214;
    if (hoisted__Bool_8214) {
        Bool hoisted__Bool_8211 = ((Bool)(*(I32*)(other) == *(I32*)(&(Color){.tag = Color_TAG_Red})));
        (void)hoisted__Bool_8211;
        { Bool _ret_val = hoisted__Bool_8211;
                return _ret_val; }
    }
    Bool hoisted__Bool_8215 = ((Bool)(*(I32*)(self) == *(I32*)(&(Color){.tag = Color_TAG_Green})));
    (void)hoisted__Bool_8215;
    if (hoisted__Bool_8215) {
        Bool hoisted__Bool_8212 = ((Bool)(*(I32*)(other) == *(I32*)(&(Color){.tag = Color_TAG_Green})));
        (void)hoisted__Bool_8212;
        { Bool _ret_val = hoisted__Bool_8212;
                return _ret_val; }
    }
    Bool hoisted__Bool_8216 = ((Bool)(*(I32*)(self) == *(I32*)(&(Color){.tag = Color_TAG_Blue})));
    (void)hoisted__Bool_8216;
    if (hoisted__Bool_8216) {
        Bool hoisted__Bool_8213 = ((Bool)(*(I32*)(other) == *(I32*)(&(Color){.tag = Color_TAG_Blue})));
        (void)hoisted__Bool_8213;
        { Bool _ret_val = hoisted__Bool_8213;
                return _ret_val; }
    }
    Bool hoisted__Bool_8217 = 0;
    (void)hoisted__Bool_8217;
    return hoisted__Bool_8217;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8225 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8225;
    if (hoisted__Bool_8225) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8226 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8226;
    if (hoisted__Bool_8226) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8227 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8227;
    if (hoisted__Bool_8227) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8228 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8228;
    UNREACHABLE(&hoisted__Str_8228);
    Str_delete(&hoisted__Str_8228, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8229 = 4;
    (void)hoisted__U32_8229;
    return hoisted__U32_8229;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8230 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8230;
    (void)hoisted__Str_8231;
    (void)hoisted__Str_8231;
    assert(hoisted__Bool_8230, &hoisted__Str_8231);
    Str_delete(&hoisted__Str_8231, (Bool){0});
    Bool hoisted__Bool_8232 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8232;
    Bool hoisted__Bool_8233 = not(hoisted__Bool_8232);
    (void)hoisted__Bool_8233;
    (void)hoisted__Str_8234;
    (void)hoisted__Str_8234;
    assert(hoisted__Bool_8233, &hoisted__Str_8234);
    Str_delete(&hoisted__Str_8234, (Bool){0});
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
    Bool hoisted__Bool_8235 = ((Bool)(*(I32*)(self) == *(I32*)(other)));
    (void)hoisted__Bool_8235;
    return hoisted__Bool_8235;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8253 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Num})));
    (void)hoisted__Bool_8253;
    if (hoisted__Bool_8253) {
        I64 *hoisted__I64_8249 = get_payload(self);
        (void)hoisted__I64_8249;
        (void)hoisted__I64_8249;
        Bool hoisted__Bool_8250 = 0;
        (void)hoisted__Bool_8250;
        I64_delete(hoisted__I64_8249, hoisted__Bool_8250);
    }
    Bool hoisted__Bool_8254 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Name})));
    (void)hoisted__Bool_8254;
    if (hoisted__Bool_8254) {
        Str *hoisted__Str_8251 = get_payload(self);
        (void)hoisted__Str_8251;
        (void)hoisted__Str_8251;
        Bool hoisted__Bool_8252 = 0;
        (void)hoisted__Bool_8252;
        Str_delete(hoisted__Str_8251, hoisted__Bool_8252);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8285 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Num})));
    (void)hoisted__Bool_8285;
    if (hoisted__Bool_8285) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8282 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8282;
        { Token * _ret_val = hoisted__Token_8282;
                return _ret_val; }
    }
    Bool hoisted__Bool_8286 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Name})));
    (void)hoisted__Bool_8286;
    if (hoisted__Bool_8286) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8283 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8283;
        Token *hoisted__Token_8284 = Token_Name(hoisted__Str_8283);
        (void)hoisted__Token_8284;
        { Token * _ret_val = hoisted__Token_8284;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8287 = 24;
    (void)hoisted__U32_8287;
    return hoisted__U32_8287;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8289 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8289;
    (void)hoisted__Str_8290;
    (void)hoisted__Str_8290;
    assert(hoisted__Bool_8289, &hoisted__Str_8290);
    Str_delete(&hoisted__Str_8290, (Bool){0});
    Bool hoisted__Bool_8291 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8291;
    Bool hoisted__Bool_8292 = not(hoisted__Bool_8291);
    (void)hoisted__Bool_8292;
    (void)hoisted__Str_8293;
    (void)hoisted__Str_8293;
    assert(hoisted__Bool_8292, &hoisted__Str_8293);
    Str_delete(&hoisted__Str_8293, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8294 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8294;
    (void)hoisted__Str_8295;
    (void)hoisted__Str_8295;
    assert(hoisted__Bool_8294, &hoisted__Str_8295);
    Str_delete(&hoisted__Str_8295, (Bool){0});
    Bool hoisted__Bool_8296 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8296;
    Bool hoisted__Bool_8297 = not(hoisted__Bool_8296);
    (void)hoisted__Bool_8297;
    (void)hoisted__Str_8298;
    (void)hoisted__Str_8298;
    assert(hoisted__Bool_8297, &hoisted__Str_8298);
    Str_delete(&hoisted__Str_8298, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8301 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8301;
    (void)hoisted__Str_8302;
    (void)hoisted__Str_8302;
    assert(hoisted__Bool_8301, &hoisted__Str_8302);
    Str_delete(&hoisted__Str_8302, (Bool){0});
    Bool hoisted__Bool_8303 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8303;
    Bool hoisted__Bool_8304 = not(hoisted__Bool_8303);
    (void)hoisted__Bool_8304;
    (void)hoisted__Str_8305;
    (void)hoisted__Str_8305;
    assert(hoisted__Bool_8304, &hoisted__Str_8305);
    Str_delete(&hoisted__Str_8305, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8437 = ((Bool)(a != b));
    (void)hoisted__Bool_8437;
    if (hoisted__Bool_8437) {
        U32 hoisted__U32_8421 = 5;
        (void)hoisted__U32_8421;
        Array__Str *_va_Array_249 = Array__Str_new(hoisted__U32_8421);
        (void)_va_Array_249;
        I64 _va_Array_249_ek = 0;
        (void)_va_Array_249_ek;
        OutOfBounds *_va_Array_249_eo = malloc(sizeof(OutOfBounds));
        _va_Array_249_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_249_eo;
        U32 hoisted__U32_8422 = 0;
        (void)hoisted__U32_8422;
        (void)hoisted__Str_8423;
        (void)hoisted__Str_8423;
        (void)hoisted__Str_8424;
        (void)hoisted__Str_8424;
        Array__Str_set(_va_Array_249, hoisted__U32_8422, &hoisted__Str_8423, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8424);
        Str_delete(&hoisted__Str_8424, (Bool){0});
        U32 hoisted__U32_8425 = 1;
        (void)hoisted__U32_8425;
        Str *hoisted__Str_8426 = I64_to_str(a);
        (void)hoisted__Str_8426;
        (void)hoisted__Str_8427;
        (void)hoisted__Str_8427;
        Array__Str_set(_va_Array_249, hoisted__U32_8425, hoisted__Str_8426, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8427);
        Str_delete(&hoisted__Str_8427, (Bool){0});
        U32 hoisted__U32_8428 = 2;
        (void)hoisted__U32_8428;
        (void)hoisted__Str_8429;
        (void)hoisted__Str_8429;
        (void)hoisted__Str_8430;
        (void)hoisted__Str_8430;
        Array__Str_set(_va_Array_249, hoisted__U32_8428, &hoisted__Str_8429, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8430);
        Str_delete(&hoisted__Str_8430, (Bool){0});
        U32 hoisted__U32_8431 = 3;
        (void)hoisted__U32_8431;
        Str *hoisted__Str_8432 = I64_to_str(b);
        (void)hoisted__Str_8432;
        (void)hoisted__Str_8433;
        (void)hoisted__Str_8433;
        Array__Str_set(_va_Array_249, hoisted__U32_8431, hoisted__Str_8432, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8433);
        Str_delete(&hoisted__Str_8433, (Bool){0});
        U32 hoisted__U32_8434 = 4;
        (void)hoisted__U32_8434;
        (void)hoisted__Str_8435;
        (void)hoisted__Str_8435;
        (void)hoisted__Str_8436;
        (void)hoisted__Str_8436;
        Array__Str_set(_va_Array_249, hoisted__U32_8434, &hoisted__Str_8435, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8436);
        OutOfBounds_delete(_va_Array_249_eo, 1);
        Str_delete(&hoisted__Str_8436, (Bool){0});
        panic(_va_Array_249, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8454 = Str_neq(a, b);
    (void)hoisted__Bool_8454;
    if (hoisted__Bool_8454) {
        U32 hoisted__U32_8438 = 5;
        (void)hoisted__U32_8438;
        Array__Str *_va_Array_250 = Array__Str_new(hoisted__U32_8438);
        (void)_va_Array_250;
        I64 _va_Array_250_ek = 0;
        (void)_va_Array_250_ek;
        OutOfBounds *_va_Array_250_eo = malloc(sizeof(OutOfBounds));
        _va_Array_250_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_250_eo;
        U32 hoisted__U32_8439 = 0;
        (void)hoisted__U32_8439;
        (void)hoisted__Str_8440;
        (void)hoisted__Str_8440;
        (void)hoisted__Str_8441;
        (void)hoisted__Str_8441;
        Array__Str_set(_va_Array_250, hoisted__U32_8439, &hoisted__Str_8440, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8441);
        Str_delete(&hoisted__Str_8441, (Bool){0});
        U32 hoisted__U32_8442 = 1;
        (void)hoisted__U32_8442;
        Str *hoisted__Str_8443 = Str_to_str(a);
        (void)hoisted__Str_8443;
        (void)hoisted__Str_8444;
        (void)hoisted__Str_8444;
        Array__Str_set(_va_Array_250, hoisted__U32_8442, hoisted__Str_8443, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8444);
        Str_delete(&hoisted__Str_8444, (Bool){0});
        U32 hoisted__U32_8445 = 2;
        (void)hoisted__U32_8445;
        (void)hoisted__Str_8446;
        (void)hoisted__Str_8446;
        (void)hoisted__Str_8447;
        (void)hoisted__Str_8447;
        Array__Str_set(_va_Array_250, hoisted__U32_8445, &hoisted__Str_8446, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8447);
        Str_delete(&hoisted__Str_8447, (Bool){0});
        U32 hoisted__U32_8448 = 3;
        (void)hoisted__U32_8448;
        Str *hoisted__Str_8449 = Str_to_str(b);
        (void)hoisted__Str_8449;
        (void)hoisted__Str_8450;
        (void)hoisted__Str_8450;
        Array__Str_set(_va_Array_250, hoisted__U32_8448, hoisted__Str_8449, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8450);
        Str_delete(&hoisted__Str_8450, (Bool){0});
        U32 hoisted__U32_8451 = 4;
        (void)hoisted__U32_8451;
        (void)hoisted__Str_8452;
        (void)hoisted__Str_8452;
        (void)hoisted__Str_8453;
        (void)hoisted__Str_8453;
        Array__Str_set(_va_Array_250, hoisted__U32_8451, &hoisted__Str_8452, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8453);
        OutOfBounds_delete(_va_Array_250_eo, 1);
        Str_delete(&hoisted__Str_8453, (Bool){0});
        panic(_va_Array_250, loc);
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
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_43;
        if (*index == 2LL) return &_til_str_lit_44;
        if (*index == 3LL) return &_til_str_lit_45;
        if (*index == 4LL) return &_til_str_lit_46;
        if (*index == 5LL) return &_til_str_lit_47;
        if (*index == 6LL) return &_til_str_lit_48;
        if (*index == 7LL) return &_til_str_lit_49;
        if (*index == 8LL) return &_til_str_lit_51;
        if (*index == 9LL) return &_til_str_lit_53;
        if (*index == 10LL) return &_til_str_lit_55;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_56;
        if (*index == 1LL) return &_til_str_lit_58;
        if (*index == 2LL) return &_til_str_lit_60;
        if (*index == 3LL) return &_til_str_lit_61;
        if (*index == 4LL) return &_til_str_lit_63;
        if (*index == 5LL) return &_til_str_lit_64;
        if (*index == 6LL) return &_til_str_lit_65;
        if (*index == 7LL) return &_til_str_lit_66;
        if (*index == 8LL) return &_til_str_lit_67;
        if (*index == 9LL) return &_til_str_lit_68;
        if (*index == 10LL) return &_til_str_lit_69;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_70;
        if (*index == 1LL) return &_til_str_lit_71;
        if (*index == 2LL) return &_til_str_lit_72;
        if (*index == 3LL) return &_til_str_lit_73;
        if (*index == 4LL) return &_til_str_lit_74;
        if (*index == 5LL) return &_til_str_lit_51;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_75;
        if (*index == 1LL) return &_til_str_lit_51;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_51;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_51;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_76;
        if (*index == 1LL) return &_til_str_lit_77;
        if (*index == 2LL) return &_til_str_lit_78;
        if (*index == 3LL) return &_til_str_lit_79;
        if (*index == 4LL) return &_til_str_lit_80;
        if (*index == 5LL) return &_til_str_lit_81;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_77;
        if (*index == 1LL) return &_til_str_lit_82;
        if (*index == 2LL) return &_til_str_lit_83;
        if (*index == 3LL) return &_til_str_lit_85;
        if (*index == 4LL) return &_til_str_lit_81;
        if (*index == 5LL) return &_til_str_lit_87;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_88;
        if (*index == 2LL) return &_til_str_lit_89;
        if (*index == 3LL) return &_til_str_lit_74;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_88;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_45;
        if (*index == 2LL) return &_til_str_lit_51;
        if (*index == 3LL) return &_til_str_lit_90;
        if (*index == 4LL) return &_til_str_lit_91;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_51;
        if (*index == 1LL) return &_til_str_lit_97;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_68;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_132;
        if (*index == 1LL) return &_til_str_lit_134;
        if (*index == 2LL) return &_til_str_lit_136;
        if (*index == 3LL) return &_til_str_lit_137;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_138;
        if (*index == 1LL) return &_til_str_lit_140;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_7;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_147;
        if (*index == 1LL) return &_til_str_lit_148;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_173;
        if (*index == 1LL) return &_til_str_lit_174;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_179;
        if (*index == 1LL) return &_til_str_lit_181;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_173;
        if (*index == 1LL) return &_til_str_lit_174;
        if (*index == 2LL) return &_til_str_lit_186;
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
        if (*index == 7LL) return &_til_str_lit_50;
        if (*index == 8LL) return &_til_str_lit_52;
        if (*index == 9LL) return &_til_str_lit_54;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_57;
        if (*index == 1LL) return &_til_str_lit_59;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_62;
        if (*index == 4LL) return &_til_str_lit_13;
        if (*index == 5LL) return &_til_str_lit_13;
        if (*index == 6LL) return &_til_str_lit_50;
        if (*index == 7LL) return &_til_str_lit_16;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_59;
        if (*index == 10LL) return &_til_str_lit_6;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_10;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_52;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_52;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_59;
        if (*index == 1LL) return &_til_str_lit_59;
        if (*index == 2LL) return &_til_str_lit_6;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_6;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_59;
        if (*index == 1LL) return &_til_str_lit_62;
        if (*index == 2LL) return &_til_str_lit_84;
        if (*index == 3LL) return &_til_str_lit_86;
        if (*index == 4LL) return &_til_str_lit_6;
        if (*index == 5LL) return &_til_str_lit_6;
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
        if (*index == 2LL) return &_til_str_lit_52;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_16;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_52;
        if (*index == 1LL) return &_til_str_lit_6;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_59;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_133;
        if (*index == 1LL) return &_til_str_lit_135;
        if (*index == 2LL) return &_til_str_lit_3;
        if (*index == 3LL) return &_til_str_lit_3;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_139;
        if (*index == 1LL) return &_til_str_lit_62;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
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
        if (*index == 0LL) return &_til_str_lit_180;
        if (*index == 1LL) return &_til_str_lit_180;
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
        return 12LL;
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
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_29;
        if (*index == 1LL) return &_til_str_lit_30;
        if (*index == 2LL) return &_til_str_lit_31;
        if (*index == 3LL) return &_til_str_lit_32;
        if (*index == 4LL) return &_til_str_lit_33;
        if (*index == 5LL) return &_til_str_lit_34;
        if (*index == 6LL) return &_til_str_lit_35;
        if (*index == 7LL) return &_til_str_lit_36;
        if (*index == 8LL) return &_til_str_lit_37;
        if (*index == 9LL) return &_til_str_lit_38;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_39;
        if (*index == 1LL) return &_til_str_lit_40;
        if (*index == 2LL) return &_til_str_lit_41;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_92;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_94;
        if (*index == 4LL) return &_til_str_lit_95;
        if (*index == 5LL) return &_til_str_lit_96;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_98;
        if (*index == 1LL) return &_til_str_lit_99;
        if (*index == 2LL) return &_til_str_lit_100;
        if (*index == 3LL) return &_til_str_lit_102;
        if (*index == 4LL) return &_til_str_lit_104;
        if (*index == 5LL) return &_til_str_lit_106;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_109;
        if (*index == 10LL) return &_til_str_lit_111;
        if (*index == 11LL) return &_til_str_lit_113;
        if (*index == 12LL) return &_til_str_lit_114;
        if (*index == 13LL) return &_til_str_lit_115;
        if (*index == 14LL) return &_til_str_lit_116;
        if (*index == 15LL) return &_til_str_lit_118;
        if (*index == 16LL) return &_til_str_lit_119;
        if (*index == 17LL) return &_til_str_lit_120;
        if (*index == 18LL) return &_til_str_lit_121;
        if (*index == 19LL) return &_til_str_lit_122;
        if (*index == 20LL) return &_til_str_lit_124;
        if (*index == 21LL) return &_til_str_lit_125;
        if (*index == 22LL) return &_til_str_lit_126;
        if (*index == 23LL) return &_til_str_lit_127;
        if (*index == 24LL) return &_til_str_lit_128;
        if (*index == 25LL) return &_til_str_lit_129;
        if (*index == 26LL) return &_til_str_lit_131;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_193;
        if (*index == 1LL) return &_til_str_lit_194;
        if (*index == 2LL) return &_til_str_lit_195;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_92;
        if (*index == 1LL) return &_til_str_lit_198;
        if (*index == 2LL) return &_til_str_lit_199;
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
        if (*index == 1LL) return &_til_str_lit_93;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_17;
        if (*index == 4LL) return &_til_str_lit_17;
        if (*index == 5LL) return &_til_str_lit_17;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_99;
        if (*index == 2LL) return &_til_str_lit_101;
        if (*index == 3LL) return &_til_str_lit_103;
        if (*index == 4LL) return &_til_str_lit_105;
        if (*index == 5LL) return &_til_str_lit_107;
        if (*index == 6LL) return &_til_str_lit_108;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_110;
        if (*index == 10LL) return &_til_str_lit_112;
        if (*index == 11LL) return &_til_str_lit_17;
        if (*index == 12LL) return &_til_str_lit_17;
        if (*index == 13LL) return &_til_str_lit_17;
        if (*index == 14LL) return &_til_str_lit_117;
        if (*index == 15LL) return &_til_str_lit_6;
        if (*index == 16LL) return &_til_str_lit_17;
        if (*index == 17LL) return &_til_str_lit_17;
        if (*index == 18LL) return &_til_str_lit_17;
        if (*index == 19LL) return &_til_str_lit_123;
        if (*index == 20LL) return &_til_str_lit_17;
        if (*index == 21LL) return &_til_str_lit_17;
        if (*index == 22LL) return &_til_str_lit_17;
        if (*index == 23LL) return &_til_str_lit_17;
        if (*index == 24LL) return &_til_str_lit_17;
        if (*index == 25LL) return &_til_str_lit_130;
        if (*index == 26LL) return &_til_str_lit_17;
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
