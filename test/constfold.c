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
    Vec__I64 tag_values;
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
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT};
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
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};
#define hoisted__Str_7206 _til_str_lit_142
#define hoisted__Str_7208 _til_str_lit_143
#define hoisted__Str_7209 _til_str_lit_142
#define hoisted__Str_7213 _til_str_lit_142
#define hoisted__Str_7225 _til_str_lit_144
#define hoisted__Str_7226 _til_str_lit_145
#define hoisted__Str_7229 _til_str_lit_146
#define hoisted__Str_7230 _til_str_lit_147
#define hoisted__Str_7338 _til_str_lit_150
#define hoisted__Str_7346 _til_str_lit_151
#define hoisted__Str_7354 _til_str_lit_152
#define hoisted__Str_7357 _til_str_lit_153
#define hoisted__Str_7358 _til_str_lit_154
#define hoisted__Str_7386 _til_str_lit_153
#define hoisted__Str_7387 _til_str_lit_155
#define hoisted__Str_7391 _til_str_lit_156
#define hoisted__Str_7392 _til_str_lit_157
#define hoisted__Str_7415 _til_str_lit_158
#define hoisted__Str_7416 _til_str_lit_159
#define hoisted__Str_7427 _til_str_lit_160
#define hoisted__Str_7428 _til_str_lit_161
#define hoisted__Str_7441 _til_str_lit_162
#define hoisted__Str_8040 _til_str_lit_165
#define hoisted__Str_8041 _til_str_lit_166
#define hoisted__Str_8044 _til_str_lit_167
#define hoisted__Str_8048 _til_str_lit_168
#define hoisted__Str_8052 _til_str_lit_169
#define hoisted__Str_8057 _til_str_lit_170
#define hoisted__Str_8058 _til_str_lit_170
#define hoisted__Str_8059 _til_str_lit_171
#define hoisted__Str_8062 _til_str_lit_172
#define hoisted__Str_8063 _til_str_lit_172
#define hoisted__Str_8064 _til_str_lit_173
#define hoisted__Str_8104 _til_str_lit_176
#define hoisted__Str_8106 _til_str_lit_177
#define hoisted__Str_8110 _til_str_lit_178
#define hoisted__Str_8112 _til_str_lit_179
#define hoisted__Str_8153 _til_str_lit_183
#define hoisted__Str_8155 _til_str_lit_184
#define hoisted__Str_8157 _til_str_lit_185
#define hoisted__Str_8159 _til_str_lit_186
#define hoisted__Str_8211 _til_str_lit_188
#define hoisted__Str_8212 _til_str_lit_189
#define hoisted__Str_8214 _til_str_lit_190
#define hoisted__Str_8215 _til_str_lit_191
#define hoisted__Str_8217 _til_str_lit_192
#define hoisted__Str_8218 _til_str_lit_193
#define hoisted__Str_8240 _til_str_lit_197
#define hoisted__Str_8243 _til_str_lit_198
#define hoisted__Str_8299 _til_str_lit_201
#define hoisted__Str_8302 _til_str_lit_202
#define hoisted__Str_8304 _til_str_lit_203
#define hoisted__Str_8307 _til_str_lit_204
#define hoisted__Str_8311 _til_str_lit_205
#define hoisted__Str_8314 _til_str_lit_206
#define hoisted__Str_8432 _til_str_lit_207
#define hoisted__Str_8433 _til_str_lit_208
#define hoisted__Str_8436 _til_str_lit_208
#define hoisted__Str_8438 _til_str_lit_209
#define hoisted__Str_8439 _til_str_lit_208
#define hoisted__Str_8442 _til_str_lit_208
#define hoisted__Str_8444 _til_str_lit_210
#define hoisted__Str_8445 _til_str_lit_208
#define hoisted__Str_8449 _til_str_lit_207
#define hoisted__Str_8450 _til_str_lit_208
#define hoisted__Str_8453 _til_str_lit_208
#define hoisted__Str_8455 _til_str_lit_209
#define hoisted__Str_8456 _til_str_lit_208
#define hoisted__Str_8459 _til_str_lit_208
#define hoisted__Str_8461 _til_str_lit_210
#define hoisted__Str_8462 _til_str_lit_208

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
        Bool hoisted__Bool_2176 = Bool_eq(a, hoisted__Bool_2175);
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
    Bool hoisted__Bool_2186 = Bool_eq(a, b);
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
    Bool hoisted__Bool_2216 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I16})));
    (void)hoisted__Bool_2216;
    if (hoisted__Bool_2216) {
        Bool hoisted__Bool_2206 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I16})));
        (void)hoisted__Bool_2206;
        { Bool _ret_val = hoisted__Bool_2206;
                return _ret_val; }
    }
    Bool hoisted__Bool_2217 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U16})));
    (void)hoisted__Bool_2217;
    if (hoisted__Bool_2217) {
        Bool hoisted__Bool_2207 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U16})));
        (void)hoisted__Bool_2207;
        { Bool _ret_val = hoisted__Bool_2207;
                return _ret_val; }
    }
    Bool hoisted__Bool_2218 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I8})));
    (void)hoisted__Bool_2218;
    if (hoisted__Bool_2218) {
        Bool hoisted__Bool_2208 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I8})));
        (void)hoisted__Bool_2208;
        { Bool _ret_val = hoisted__Bool_2208;
                return _ret_val; }
    }
    Bool hoisted__Bool_2219 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U8})));
    (void)hoisted__Bool_2219;
    if (hoisted__Bool_2219) {
        Bool hoisted__Bool_2209 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U8})));
        (void)hoisted__Bool_2209;
        { Bool _ret_val = hoisted__Bool_2209;
                return _ret_val; }
    }
    Bool hoisted__Bool_2220 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U32})));
    (void)hoisted__Bool_2220;
    if (hoisted__Bool_2220) {
        Bool hoisted__Bool_2210 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U32})));
        (void)hoisted__Bool_2210;
        { Bool _ret_val = hoisted__Bool_2210;
                return _ret_val; }
    }
    Bool hoisted__Bool_2221 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I32})));
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        Bool hoisted__Bool_2211 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I32})));
        (void)hoisted__Bool_2211;
        { Bool _ret_val = hoisted__Bool_2211;
                return _ret_val; }
    }
    Bool hoisted__Bool_2222 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U64})));
    (void)hoisted__Bool_2222;
    if (hoisted__Bool_2222) {
        Bool hoisted__Bool_2212 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_U64})));
        (void)hoisted__Bool_2212;
        { Bool _ret_val = hoisted__Bool_2212;
                return _ret_val; }
    }
    Bool hoisted__Bool_2223 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I64})));
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        Bool hoisted__Bool_2213 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_I64})));
        (void)hoisted__Bool_2213;
        { Bool _ret_val = hoisted__Bool_2213;
                return _ret_val; }
    }
    Bool hoisted__Bool_2224 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_F32})));
    (void)hoisted__Bool_2224;
    if (hoisted__Bool_2224) {
        Bool hoisted__Bool_2214 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_F32})));
        (void)hoisted__Bool_2214;
        { Bool _ret_val = hoisted__Bool_2214;
                return _ret_val; }
    }
    Bool hoisted__Bool_2225 = ((Bool)(*(I32*)(self) == *(I32*)(&(Primitive){.tag = Primitive_TAG_Bool})));
    (void)hoisted__Bool_2225;
    if (hoisted__Bool_2225) {
        Bool hoisted__Bool_2215 = ((Bool)(*(I32*)(other) == *(I32*)(&(Primitive){.tag = Primitive_TAG_Bool})));
        (void)hoisted__Bool_2215;
        { Bool _ret_val = hoisted__Bool_2215;
                return _ret_val; }
    }
    Bool hoisted__Bool_2226 = 0;
    (void)hoisted__Bool_2226;
    return hoisted__Bool_2226;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2248 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2248;
    if (hoisted__Bool_2248) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2249 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2249;
    if (hoisted__Bool_2249) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2250 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2250;
    if (hoisted__Bool_2250) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2251 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2251;
    if (hoisted__Bool_2251) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2252 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2252;
    if (hoisted__Bool_2252) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2253 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2253;
    if (hoisted__Bool_2253) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2254 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2254;
    if (hoisted__Bool_2254) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2255 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2255;
    if (hoisted__Bool_2255) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2256 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2256;
    if (hoisted__Bool_2256) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2257 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2257;
    if (hoisted__Bool_2257) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2258 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2258;
    UNREACHABLE(&hoisted__Str_2258);
    Str_delete(&hoisted__Str_2258, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2259 = 4;
    (void)hoisted__U32_2259;
    return hoisted__U32_2259;
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
    Bool hoisted__Bool_2311 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Struct})));
    (void)hoisted__Bool_2311;
    if (hoisted__Bool_2311) {
        Str *hoisted__Str_2301 = get_payload(self);
        (void)hoisted__Str_2301;
        (void)hoisted__Str_2301;
        Bool hoisted__Bool_2302 = 0;
        (void)hoisted__Bool_2302;
        Str_delete(hoisted__Str_2301, hoisted__Bool_2302);
    }
    Bool hoisted__Bool_2312 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Enum})));
    (void)hoisted__Bool_2312;
    if (hoisted__Bool_2312) {
        Str *hoisted__Str_2303 = get_payload(self);
        (void)hoisted__Str_2303;
        (void)hoisted__Str_2303;
        Bool hoisted__Bool_2304 = 0;
        (void)hoisted__Bool_2304;
        Str_delete(hoisted__Str_2303, hoisted__Bool_2304);
    }
    Bool hoisted__Bool_2313 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Custom})));
    (void)hoisted__Bool_2313;
    if (hoisted__Bool_2313) {
        Str *hoisted__Str_2305 = get_payload(self);
        (void)hoisted__Str_2305;
        (void)hoisted__Str_2305;
        Bool hoisted__Bool_2306 = 0;
        (void)hoisted__Bool_2306;
        Str_delete(hoisted__Str_2305, hoisted__Bool_2306);
    }
    Bool hoisted__Bool_2314 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Primitive})));
    (void)hoisted__Bool_2314;
    if (hoisted__Bool_2314) {
        Primitive *hoisted__Primitive_2307 = get_payload(self);
        (void)hoisted__Primitive_2307;
        (void)hoisted__Primitive_2307;
        Bool hoisted__Bool_2308 = 0;
        (void)hoisted__Bool_2308;
        Primitive_delete(hoisted__Primitive_2307, hoisted__Bool_2308);
    }
    Bool hoisted__Bool_2315 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_FuncPtrSig})));
    (void)hoisted__Bool_2315;
    if (hoisted__Bool_2315) {
        Str *hoisted__Str_2309 = get_payload(self);
        (void)hoisted__Str_2309;
        (void)hoisted__Str_2309;
        Bool hoisted__Bool_2310 = 0;
        (void)hoisted__Bool_2310;
        Str_delete(hoisted__Str_2309, hoisted__Bool_2310);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2399 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Unknown})));
    (void)hoisted__Bool_2399;
    if (hoisted__Bool_2399) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2400 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_None})));
    (void)hoisted__Bool_2400;
    if (hoisted__Bool_2400) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2401 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Struct})));
    (void)hoisted__Bool_2401;
    if (hoisted__Bool_2401) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2391 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2391;
        Type *hoisted__Type_2392 = Type_Struct(hoisted__Str_2391);
        (void)hoisted__Type_2392;
        { Type * _ret_val = hoisted__Type_2392;
                return _ret_val; }
    }
    Bool hoisted__Bool_2402 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_StructDef})));
    (void)hoisted__Bool_2402;
    if (hoisted__Bool_2402) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2403 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Enum})));
    (void)hoisted__Bool_2403;
    if (hoisted__Bool_2403) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2393 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2393;
        Type *hoisted__Type_2394 = Type_Enum(hoisted__Str_2393);
        (void)hoisted__Type_2394;
        { Type * _ret_val = hoisted__Type_2394;
                return _ret_val; }
    }
    Bool hoisted__Bool_2404 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_EnumDef})));
    (void)hoisted__Bool_2404;
    if (hoisted__Bool_2404) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2405 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_FuncDef})));
    (void)hoisted__Bool_2405;
    if (hoisted__Bool_2405) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2406 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_FuncPtr})));
    (void)hoisted__Bool_2406;
    if (hoisted__Bool_2406) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2407 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Dynamic})));
    (void)hoisted__Bool_2407;
    if (hoisted__Bool_2407) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2408 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Custom})));
    (void)hoisted__Bool_2408;
    if (hoisted__Bool_2408) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2395 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2395;
        Type *hoisted__Type_2396 = Type_Custom(hoisted__Str_2395);
        (void)hoisted__Type_2396;
        { Type * _ret_val = hoisted__Type_2396;
                return _ret_val; }
    }
    Bool hoisted__Bool_2409 = ((Bool)(*(I32*)(self) == *(I32*)(&(Type){.tag = Type_TAG_Primitive})));
    (void)hoisted__Bool_2409;
    if (hoisted__Bool_2409) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2397 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2397;
        Type *hoisted__Type_2398 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2397; _oa; }));
        (void)hoisted__Type_2398;
        { Type * _ret_val = hoisted__Type_2398;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2410 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2410;
    Type *hoisted__Type_2411 = Type_FuncPtrSig(hoisted__Str_2410);
    (void)hoisted__Type_2411;
    return hoisted__Type_2411;
}

U32 Type_size(void) {
    U32 hoisted__U32_2412 = 24;
    (void)hoisted__U32_2412;
    return hoisted__U32_2412;
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
    Bool hoisted__Bool_2515 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Func})));
    (void)hoisted__Bool_2515;
    if (hoisted__Bool_2515) {
        Bool hoisted__Bool_2505 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Func})));
        (void)hoisted__Bool_2505;
        { Bool _ret_val = hoisted__Bool_2505;
                return _ret_val; }
    }
    Bool hoisted__Bool_2516 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Proc})));
    (void)hoisted__Bool_2516;
    if (hoisted__Bool_2516) {
        Bool hoisted__Bool_2506 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Proc})));
        (void)hoisted__Bool_2506;
        { Bool _ret_val = hoisted__Bool_2506;
                return _ret_val; }
    }
    Bool hoisted__Bool_2517 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Test})));
    (void)hoisted__Bool_2517;
    if (hoisted__Bool_2517) {
        Bool hoisted__Bool_2507 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Test})));
        (void)hoisted__Bool_2507;
        { Bool _ret_val = hoisted__Bool_2507;
                return _ret_val; }
    }
    Bool hoisted__Bool_2518 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Macro})));
    (void)hoisted__Bool_2518;
    if (hoisted__Bool_2518) {
        Bool hoisted__Bool_2508 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_Macro})));
        (void)hoisted__Bool_2508;
        { Bool _ret_val = hoisted__Bool_2508;
                return _ret_val; }
    }
    Bool hoisted__Bool_2519 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtFunc})));
    (void)hoisted__Bool_2519;
    if (hoisted__Bool_2519) {
        Bool hoisted__Bool_2509 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtFunc})));
        (void)hoisted__Bool_2509;
        { Bool _ret_val = hoisted__Bool_2509;
                return _ret_val; }
    }
    Bool hoisted__Bool_2520 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtProc})));
    (void)hoisted__Bool_2520;
    if (hoisted__Bool_2520) {
        Bool hoisted__Bool_2510 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_ExtProc})));
        (void)hoisted__Bool_2510;
        { Bool _ret_val = hoisted__Bool_2510;
                return _ret_val; }
    }
    Bool hoisted__Bool_2521 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyFunc})));
    (void)hoisted__Bool_2521;
    if (hoisted__Bool_2521) {
        Bool hoisted__Bool_2511 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyFunc})));
        (void)hoisted__Bool_2511;
        { Bool _ret_val = hoisted__Bool_2511;
                return _ret_val; }
    }
    Bool hoisted__Bool_2522 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyProc})));
    (void)hoisted__Bool_2522;
    if (hoisted__Bool_2522) {
        Bool hoisted__Bool_2512 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_LazyProc})));
        (void)hoisted__Bool_2512;
        { Bool _ret_val = hoisted__Bool_2512;
                return _ret_val; }
    }
    Bool hoisted__Bool_2523 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreFunc})));
    (void)hoisted__Bool_2523;
    if (hoisted__Bool_2523) {
        Bool hoisted__Bool_2513 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreFunc})));
        (void)hoisted__Bool_2513;
        { Bool _ret_val = hoisted__Bool_2513;
                return _ret_val; }
    }
    Bool hoisted__Bool_2524 = ((Bool)(*(I32*)(self) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreProc})));
    (void)hoisted__Bool_2524;
    if (hoisted__Bool_2524) {
        Bool hoisted__Bool_2514 = ((Bool)(*(I32*)(other) == *(I32*)(&(FuncType){.tag = FuncType_TAG_CoreProc})));
        (void)hoisted__Bool_2514;
        { Bool _ret_val = hoisted__Bool_2514;
                return _ret_val; }
    }
    Bool hoisted__Bool_2525 = 0;
    (void)hoisted__Bool_2525;
    return hoisted__Bool_2525;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2547 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2547;
    if (hoisted__Bool_2547) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2548 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2548;
    if (hoisted__Bool_2548) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2549 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2549;
    if (hoisted__Bool_2549) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2550 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2550;
    if (hoisted__Bool_2550) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2551 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2551;
    if (hoisted__Bool_2551) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2552 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2552;
    if (hoisted__Bool_2552) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2553 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2553;
    if (hoisted__Bool_2553) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2554 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2554;
    if (hoisted__Bool_2554) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2555 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2555;
    if (hoisted__Bool_2555) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2556 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2556;
    if (hoisted__Bool_2556) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2557 = (Str){.c_str = (void *)"FuncType.clone:125:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2557;
    UNREACHABLE(&hoisted__Str_2557);
    Str_delete(&hoisted__Str_2557, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2558 = 4;
    (void)hoisted__U32_2558;
    return hoisted__U32_2558;
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
    Bool hoisted__Bool_2563 = ((Bool)(*(I32*)(self) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Own})));
    (void)hoisted__Bool_2563;
    if (hoisted__Bool_2563) {
        Bool hoisted__Bool_2560 = ((Bool)(*(I32*)(other) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Own})));
        (void)hoisted__Bool_2560;
        { Bool _ret_val = hoisted__Bool_2560;
                return _ret_val; }
    }
    Bool hoisted__Bool_2564 = ((Bool)(*(I32*)(self) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Ref})));
    (void)hoisted__Bool_2564;
    if (hoisted__Bool_2564) {
        Bool hoisted__Bool_2561 = ((Bool)(*(I32*)(other) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Ref})));
        (void)hoisted__Bool_2561;
        { Bool _ret_val = hoisted__Bool_2561;
                return _ret_val; }
    }
    Bool hoisted__Bool_2565 = ((Bool)(*(I32*)(self) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Shallow})));
    (void)hoisted__Bool_2565;
    if (hoisted__Bool_2565) {
        Bool hoisted__Bool_2562 = ((Bool)(*(I32*)(other) == *(I32*)(&(OwnType){.tag = OwnType_TAG_Shallow})));
        (void)hoisted__Bool_2562;
        { Bool _ret_val = hoisted__Bool_2562;
                return _ret_val; }
    }
    Bool hoisted__Bool_2566 = 0;
    (void)hoisted__Bool_2566;
    return hoisted__Bool_2566;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2574 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2574;
    if (hoisted__Bool_2574) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2575 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2575;
    if (hoisted__Bool_2575) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2576 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2576;
    if (hoisted__Bool_2576) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2577 = (Str){.c_str = (void *)"OwnType.clone:137:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2577;
    UNREACHABLE(&hoisted__Str_2577);
    Str_delete(&hoisted__Str_2577, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2578 = 4;
    (void)hoisted__U32_2578;
    return hoisted__U32_2578;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2580 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2580;
    Declaration *hoisted__Declaration_2581 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2581->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2581->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2581->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2581->is_mut = self->is_mut;
    hoisted__Declaration_2581->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2581->is_priv = self->is_priv;
    hoisted__Declaration_2581->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2581->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2581->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2581->default_value = hoisted__Expr_2580;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2581->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2581;
    return hoisted__Declaration_2581;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2582 = 0;
    (void)hoisted__Bool_2582;
    Str_delete(&self->name, hoisted__Bool_2582);
    Bool hoisted__Bool_2583 = 0;
    (void)hoisted__Bool_2583;
    Str_delete(&self->doc, hoisted__Bool_2583);
    Bool hoisted__Bool_2584 = 0;
    (void)hoisted__Bool_2584;
    Str_delete(&self->explicit_type, hoisted__Bool_2584);
    Bool hoisted__Bool_2585 = 0;
    (void)hoisted__Bool_2585;
    Bool_delete(&self->is_mut, hoisted__Bool_2585);
    Bool hoisted__Bool_2586 = 0;
    (void)hoisted__Bool_2586;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2586);
    Bool hoisted__Bool_2587 = 0;
    (void)hoisted__Bool_2587;
    Bool_delete(&self->is_priv, hoisted__Bool_2587);
    Bool hoisted__Bool_2588 = 0;
    (void)hoisted__Bool_2588;
    Bool_delete(&self->used, hoisted__Bool_2588);
    Bool hoisted__Bool_2589 = 0;
    (void)hoisted__Bool_2589;
    OwnType_delete(&self->own_type, hoisted__Bool_2589);
    Bool hoisted__Bool_2590 = 0;
    (void)hoisted__Bool_2590;
    Type_delete(&self->til_type, hoisted__Bool_2590);
    Bool hoisted__Bool_2591 = 1;
    (void)hoisted__Bool_2591;
    Expr_delete(self->default_value, hoisted__Bool_2591);
    Bool hoisted__Bool_2592 = 0;
    (void)hoisted__Bool_2592;
    Str_delete(&self->orig_name, hoisted__Bool_2592);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2593 = 104;
    (void)hoisted__U32_2593;
    return hoisted__U32_2593;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2595 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2595->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2595->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2595->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2595->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2595->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2595->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2595->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2595->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2595->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2595->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2595->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2595;
    return hoisted__FunctionDef_2595;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2596 = 0;
    (void)hoisted__Bool_2596;
    FuncType_delete(&self->func_type, hoisted__Bool_2596);
    Bool hoisted__Bool_2597 = 0;
    (void)hoisted__Bool_2597;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2597);
    Bool hoisted__Bool_2598 = 0;
    (void)hoisted__Bool_2598;
    Str_delete(&self->return_type, hoisted__Bool_2598);
    Bool hoisted__Bool_2599 = 0;
    (void)hoisted__Bool_2599;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2599);
    Bool hoisted__Bool_2600 = 0;
    (void)hoisted__Bool_2600;
    I32_delete(&self->variadic_index, hoisted__Bool_2600);
    Bool hoisted__Bool_2601 = 0;
    (void)hoisted__Bool_2601;
    I32_delete(&self->kwargs_index, hoisted__Bool_2601);
    Bool hoisted__Bool_2602 = 0;
    (void)hoisted__Bool_2602;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2602);
    Bool hoisted__Bool_2603 = 0;
    (void)hoisted__Bool_2603;
    Bool_delete(&self->auto_generated, hoisted__Bool_2603);
    Bool hoisted__Bool_2604 = 0;
    (void)hoisted__Bool_2604;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2604);
    Bool hoisted__Bool_2605 = 0;
    (void)hoisted__Bool_2605;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2605);
    Bool hoisted__Bool_2606 = 0;
    (void)hoisted__Bool_2606;
    Str_delete(&self->closure_name, hoisted__Bool_2606);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2607 = 0;
    (void)hoisted__U32_2607;
    U64 hoisted__U64_2608 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2607); });
    (void)hoisted__U64_2608;
    return hoisted__U64_2608;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2609 = 104;
    (void)hoisted__U32_2609;
    return hoisted__U32_2609;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2612 = malloc(sizeof(FCallData));
    hoisted__FCallData_2612->is_splat = self->is_splat;
    hoisted__FCallData_2612->does_throw = self->does_throw;
    hoisted__FCallData_2612->is_bang = self->is_bang;
    hoisted__FCallData_2612->own_args = self->own_args;
    hoisted__FCallData_2612->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2612->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2612;
    return hoisted__FCallData_2612;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2613 = 0;
    (void)hoisted__Bool_2613;
    Bool_delete(&self->is_splat, hoisted__Bool_2613);
    Bool hoisted__Bool_2614 = 0;
    (void)hoisted__Bool_2614;
    Bool_delete(&self->does_throw, hoisted__Bool_2614);
    Bool hoisted__Bool_2615 = 0;
    (void)hoisted__Bool_2615;
    Bool_delete(&self->is_bang, hoisted__Bool_2615);
    Bool hoisted__Bool_2616 = 0;
    (void)hoisted__Bool_2616;
    U64_delete(&self->own_args, hoisted__Bool_2616);
    Bool hoisted__Bool_2617 = 0;
    (void)hoisted__Bool_2617;
    Bool_delete(&self->swap_replace, hoisted__Bool_2617);
    Bool hoisted__Bool_2618 = 0;
    (void)hoisted__Bool_2618;
    Type_delete(&self->til_type, hoisted__Bool_2618);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2619 = 0;
    (void)hoisted__U32_2619;
    U64 hoisted__U64_2620 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2619); });
    (void)hoisted__U64_2620;
    return hoisted__U64_2620;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2621 = 48;
    (void)hoisted__U32_2621;
    return hoisted__U32_2621;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2633 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2633->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2633->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2633;
    return hoisted__LiteralNumData_2633;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2634 = 0;
    (void)hoisted__Bool_2634;
    Str_delete(&self->text, hoisted__Bool_2634);
    Bool hoisted__Bool_2635 = 0;
    (void)hoisted__Bool_2635;
    Type_delete(&self->til_type, hoisted__Bool_2635);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2636 = 0;
    (void)hoisted__U32_2636;
    U64 hoisted__U64_2637 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2636); });
    (void)hoisted__U64_2637;
    return hoisted__U64_2637;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2638 = 40;
    (void)hoisted__U32_2638;
    return hoisted__U32_2638;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2648 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2648->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2648->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2648;
    return hoisted__IdentData_2648;
}

void IdentData_delete(IdentData * self, Bool call_free) {
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

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2651 = 0;
    (void)hoisted__U32_2651;
    U64 hoisted__U64_2652 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2651); });
    (void)hoisted__U64_2652;
    return hoisted__U64_2652;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2653 = 40;
    (void)hoisted__U32_2653;
    return hoisted__U32_2653;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2659 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2659->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2659->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2659;
    return hoisted__FieldAccessData_2659;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2660 = 0;
    (void)hoisted__Bool_2660;
    Str_delete(&self->name, hoisted__Bool_2660);
    Bool hoisted__Bool_2661 = 0;
    (void)hoisted__Bool_2661;
    Type_delete(&self->til_type, hoisted__Bool_2661);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2662 = 0;
    (void)hoisted__U32_2662;
    U64 hoisted__U64_2663 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2662); });
    (void)hoisted__U64_2663;
    return hoisted__U64_2663;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2664 = 40;
    (void)hoisted__U32_2664;
    return hoisted__U32_2664;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2745 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2745->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2745->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2745->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2745->is_interface = self->is_interface;
    hoisted__StructDef_2745->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2745->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2745;
    return hoisted__StructDef_2745;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2746 = 0;
    (void)hoisted__Bool_2746;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2746);
    Bool hoisted__Bool_2747 = 0;
    (void)hoisted__Bool_2747;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2747);
    Bool hoisted__Bool_2748 = 0;
    (void)hoisted__Bool_2748;
    Str_delete(&self->c_tag, hoisted__Bool_2748);
    Bool hoisted__Bool_2749 = 0;
    (void)hoisted__Bool_2749;
    Bool_delete(&self->is_interface, hoisted__Bool_2749);
    Bool hoisted__Bool_2750 = 0;
    (void)hoisted__Bool_2750;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2750);
    Bool hoisted__Bool_2751 = 0;
    (void)hoisted__Bool_2751;
    Str_delete(&self->implements_name, hoisted__Bool_2751);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2752 = 0;
    (void)hoisted__U32_2752;
    U64 hoisted__U64_2753 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2752); });
    (void)hoisted__U64_2753;
    return hoisted__U64_2753;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2754 = 72;
    (void)hoisted__U32_2754;
    return hoisted__U32_2754;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2759 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2759->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2759->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2759->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2759->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2759->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2759->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2759->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2759;
    return hoisted__EnumDef_2759;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2760 = 0;
    (void)hoisted__Bool_2760;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2760);
    Bool hoisted__Bool_2761 = 0;
    (void)hoisted__Bool_2761;
    Vec__Str_delete(&self->variants, hoisted__Bool_2761);
    Bool hoisted__Bool_2762 = 0;
    (void)hoisted__Bool_2762;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2762);
    Bool hoisted__Bool_2763 = 0;
    (void)hoisted__Bool_2763;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2763);
    Bool hoisted__Bool_2764 = 0;
    (void)hoisted__Bool_2764;
    Str_delete(&self->implements_name, hoisted__Bool_2764);
    Bool hoisted__Bool_2765 = 0;
    (void)hoisted__Bool_2765;
    Str_delete(&self->tag_type, hoisted__Bool_2765);
    Bool hoisted__Bool_2766 = 0;
    (void)hoisted__Bool_2766;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2766);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2767 = 0;
    (void)hoisted__U32_2767;
    U64 hoisted__U64_2768 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2767); });
    (void)hoisted__U64_2768;
    return hoisted__U64_2768;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2769 = 128;
    (void)hoisted__U32_2769;
    return hoisted__U32_2769;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2869 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2869->name = *_ca; free(_ca); }
    hoisted__AssignData_2869->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2869->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2869->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2869;
    return hoisted__AssignData_2869;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2870 = 0;
    (void)hoisted__Bool_2870;
    Str_delete(&self->name, hoisted__Bool_2870);
    Bool hoisted__Bool_2871 = 0;
    (void)hoisted__Bool_2871;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2871);
    Bool hoisted__Bool_2872 = 0;
    (void)hoisted__Bool_2872;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2872);
    Bool hoisted__Bool_2873 = 0;
    (void)hoisted__Bool_2873;
    Bool_delete(&self->swap_replace, hoisted__Bool_2873);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2874 = 0;
    (void)hoisted__U32_2874;
    U64 hoisted__U64_2875 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2874); });
    (void)hoisted__U64_2875;
    return hoisted__U64_2875;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2876 = 24;
    (void)hoisted__U32_2876;
    return hoisted__U32_2876;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2878 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2878->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2878->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2878;
    return hoisted__FieldAssignData_2878;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2879 = 0;
    (void)hoisted__Bool_2879;
    Str_delete(&self->name, hoisted__Bool_2879);
    Bool hoisted__Bool_2880 = 0;
    (void)hoisted__Bool_2880;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2880);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2881 = 0;
    (void)hoisted__U32_2881;
    U64 hoisted__U64_2882 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2881); });
    (void)hoisted__U64_2882;
    return hoisted__U64_2882;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2883 = 24;
    (void)hoisted__U32_2883;
    return hoisted__U32_2883;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2885 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2885->name = *_ca; free(_ca); }
    hoisted__ForInData_2885->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2885->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2885->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2885->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2885;
    return hoisted__ForInData_2885;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2886 = 0;
    (void)hoisted__Bool_2886;
    Str_delete(&self->name, hoisted__Bool_2886);
    Bool hoisted__Bool_2887 = 0;
    (void)hoisted__Bool_2887;
    Bool_delete(&self->is_mut, hoisted__Bool_2887);
    Bool hoisted__Bool_2888 = 0;
    (void)hoisted__Bool_2888;
    Type_delete(&self->til_type, hoisted__Bool_2888);
    Bool hoisted__Bool_2889 = 0;
    (void)hoisted__Bool_2889;
    Str_delete(&self->name2, hoisted__Bool_2889);
    Bool hoisted__Bool_2890 = 0;
    (void)hoisted__Bool_2890;
    Bool_delete(&self->is_mut2, hoisted__Bool_2890);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2891 = 0;
    (void)hoisted__U32_2891;
    U64 hoisted__U64_2892 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2891); });
    (void)hoisted__U64_2892;
    return hoisted__U64_2892;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2893 = 72;
    (void)hoisted__U32_2893;
    return hoisted__U32_2893;
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
    Bool hoisted__Bool_2923 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Str})));
    (void)hoisted__Bool_2923;
    if (hoisted__Bool_2923) {
        Str *hoisted__Str_2917 = get_payload(self);
        (void)hoisted__Str_2917;
        (void)hoisted__Str_2917;
        Bool hoisted__Bool_2918 = 0;
        (void)hoisted__Bool_2918;
        Str_delete(hoisted__Str_2917, hoisted__Bool_2918);
    }
    Bool hoisted__Bool_2924 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Num})));
    (void)hoisted__Bool_2924;
    if (hoisted__Bool_2924) {
        LiteralNumData *hoisted__LiteralNumData_2919 = get_payload(self);
        (void)hoisted__LiteralNumData_2919;
        (void)hoisted__LiteralNumData_2919;
        Bool hoisted__Bool_2920 = 0;
        (void)hoisted__Bool_2920;
        LiteralNumData_delete(hoisted__LiteralNumData_2919, hoisted__Bool_2920);
    }
    Bool hoisted__Bool_2925 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Bool})));
    (void)hoisted__Bool_2925;
    if (hoisted__Bool_2925) {
        Bool *hoisted__Bool_2921 = get_payload(self);
        (void)hoisted__Bool_2921;
        (void)hoisted__Bool_2921;
        Bool hoisted__Bool_2922 = 0;
        (void)hoisted__Bool_2922;
        Bool_delete(hoisted__Bool_2921, hoisted__Bool_2922);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2974 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Str})));
    (void)hoisted__Bool_2974;
    if (hoisted__Bool_2974) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2969 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2969;
        Literal *hoisted__Literal_2970 = Literal_Str(hoisted__Str_2969);
        (void)hoisted__Literal_2970;
        { Literal * _ret_val = hoisted__Literal_2970;
                return _ret_val; }
    }
    Bool hoisted__Bool_2975 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Num})));
    (void)hoisted__Bool_2975;
    if (hoisted__Bool_2975) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2971 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2971;
        Literal *hoisted__Literal_2972 = Literal_Num(hoisted__LiteralNumData_2971);
        (void)hoisted__Literal_2972;
        { Literal * _ret_val = hoisted__Literal_2972;
                return _ret_val; }
    }
    Bool hoisted__Bool_2976 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Bool})));
    (void)hoisted__Bool_2976;
    if (hoisted__Bool_2976) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2973 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2973;
        { Literal * _ret_val = hoisted__Literal_2973;
                return _ret_val; }
    }
    Bool hoisted__Bool_2977 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_Null})));
    (void)hoisted__Bool_2977;
    if (hoisted__Bool_2977) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2978 = ((Bool)(*(I32*)(self) == *(I32*)(&(Literal){.tag = Literal_TAG_MapLit})));
    (void)hoisted__Bool_2978;
    if (hoisted__Bool_2978) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2979 = 48;
    (void)hoisted__U32_2979;
    return hoisted__U32_2979;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2982 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2982->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2982->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2982;
    return hoisted__MatchData_2982;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2983 = 0;
    (void)hoisted__Bool_2983;
    Type_delete(&self->til_type, hoisted__Bool_2983);
    Bool hoisted__Bool_2984 = 0;
    (void)hoisted__Bool_2984;
    Str_delete(&self->result_temp, hoisted__Bool_2984);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2985 = 0;
    (void)hoisted__U32_2985;
    U64 hoisted__U64_2986 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2985); });
    (void)hoisted__U64_2986;
    return hoisted__U64_2986;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2987 = 40;
    (void)hoisted__U32_2987;
    return hoisted__U32_2987;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2992 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2992->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2992;
    return hoisted__CaptureBlockData_2992;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2993 = 0;
    (void)hoisted__Bool_2993;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2993);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2994 = 0;
    (void)hoisted__U32_2994;
    U64 hoisted__U64_2995 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2994); });
    (void)hoisted__U64_2995;
    return hoisted__U64_2995;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2996 = 16;
    (void)hoisted__U32_2996;
    return hoisted__U32_2996;
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
    Bool hoisted__Bool_3175 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Literal})));
    (void)hoisted__Bool_3175;
    if (hoisted__Bool_3175) {
        Literal *hoisted__Literal_3147 = get_payload(self);
        (void)hoisted__Literal_3147;
        (void)hoisted__Literal_3147;
        Bool hoisted__Bool_3148 = 0;
        (void)hoisted__Bool_3148;
        Literal_delete(hoisted__Literal_3147, hoisted__Bool_3148);
    }
    Bool hoisted__Bool_3176 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Ident})));
    (void)hoisted__Bool_3176;
    if (hoisted__Bool_3176) {
        IdentData *hoisted__IdentData_3149 = get_payload(self);
        (void)hoisted__IdentData_3149;
        (void)hoisted__IdentData_3149;
        Bool hoisted__Bool_3150 = 0;
        (void)hoisted__Bool_3150;
        IdentData_delete(hoisted__IdentData_3149, hoisted__Bool_3150);
    }
    Bool hoisted__Bool_3177 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Decl})));
    (void)hoisted__Bool_3177;
    if (hoisted__Bool_3177) {
        Declaration *hoisted__Declaration_3151 = get_payload(self);
        (void)hoisted__Declaration_3151;
        (void)hoisted__Declaration_3151;
        Bool hoisted__Bool_3152 = 0;
        (void)hoisted__Bool_3152;
        Declaration_delete(hoisted__Declaration_3151, hoisted__Bool_3152);
    }
    Bool hoisted__Bool_3178 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Assign})));
    (void)hoisted__Bool_3178;
    if (hoisted__Bool_3178) {
        AssignData *hoisted__AssignData_3153 = get_payload(self);
        (void)hoisted__AssignData_3153;
        (void)hoisted__AssignData_3153;
        Bool hoisted__Bool_3154 = 0;
        (void)hoisted__Bool_3154;
        AssignData_delete(hoisted__AssignData_3153, hoisted__Bool_3154);
    }
    Bool hoisted__Bool_3179 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FCall})));
    (void)hoisted__Bool_3179;
    if (hoisted__Bool_3179) {
        FCallData *hoisted__FCallData_3155 = get_payload(self);
        (void)hoisted__FCallData_3155;
        (void)hoisted__FCallData_3155;
        Bool hoisted__Bool_3156 = 0;
        (void)hoisted__Bool_3156;
        FCallData_delete(hoisted__FCallData_3155, hoisted__Bool_3156);
    }
    Bool hoisted__Bool_3180 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FuncDef})));
    (void)hoisted__Bool_3180;
    if (hoisted__Bool_3180) {
        FunctionDef *hoisted__FunctionDef_3157 = get_payload(self);
        (void)hoisted__FunctionDef_3157;
        (void)hoisted__FunctionDef_3157;
        Bool hoisted__Bool_3158 = 0;
        (void)hoisted__Bool_3158;
        FunctionDef_delete(hoisted__FunctionDef_3157, hoisted__Bool_3158);
    }
    Bool hoisted__Bool_3181 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_StructDef})));
    (void)hoisted__Bool_3181;
    if (hoisted__Bool_3181) {
        StructDef *hoisted__StructDef_3159 = get_payload(self);
        (void)hoisted__StructDef_3159;
        (void)hoisted__StructDef_3159;
        Bool hoisted__Bool_3160 = 0;
        (void)hoisted__Bool_3160;
        StructDef_delete(hoisted__StructDef_3159, hoisted__Bool_3160);
    }
    Bool hoisted__Bool_3182 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_EnumDef})));
    (void)hoisted__Bool_3182;
    if (hoisted__Bool_3182) {
        EnumDef *hoisted__EnumDef_3161 = get_payload(self);
        (void)hoisted__EnumDef_3161;
        (void)hoisted__EnumDef_3161;
        Bool hoisted__Bool_3162 = 0;
        (void)hoisted__Bool_3162;
        EnumDef_delete(hoisted__EnumDef_3161, hoisted__Bool_3162);
    }
    Bool hoisted__Bool_3183 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAccess})));
    (void)hoisted__Bool_3183;
    if (hoisted__Bool_3183) {
        FieldAccessData *hoisted__FieldAccessData_3163 = get_payload(self);
        (void)hoisted__FieldAccessData_3163;
        (void)hoisted__FieldAccessData_3163;
        Bool hoisted__Bool_3164 = 0;
        (void)hoisted__Bool_3164;
        FieldAccessData_delete(hoisted__FieldAccessData_3163, hoisted__Bool_3164);
    }
    Bool hoisted__Bool_3184 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAssign})));
    (void)hoisted__Bool_3184;
    if (hoisted__Bool_3184) {
        FieldAssignData *hoisted__FieldAssignData_3165 = get_payload(self);
        (void)hoisted__FieldAssignData_3165;
        (void)hoisted__FieldAssignData_3165;
        Bool hoisted__Bool_3166 = 0;
        (void)hoisted__Bool_3166;
        FieldAssignData_delete(hoisted__FieldAssignData_3165, hoisted__Bool_3166);
    }
    Bool hoisted__Bool_3185 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_ForIn})));
    (void)hoisted__Bool_3185;
    if (hoisted__Bool_3185) {
        ForInData *hoisted__ForInData_3167 = get_payload(self);
        (void)hoisted__ForInData_3167;
        (void)hoisted__ForInData_3167;
        Bool hoisted__Bool_3168 = 0;
        (void)hoisted__Bool_3168;
        ForInData_delete(hoisted__ForInData_3167, hoisted__Bool_3168);
    }
    Bool hoisted__Bool_3186 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_NamedArg})));
    (void)hoisted__Bool_3186;
    if (hoisted__Bool_3186) {
        Str *hoisted__Str_3169 = get_payload(self);
        (void)hoisted__Str_3169;
        (void)hoisted__Str_3169;
        Bool hoisted__Bool_3170 = 0;
        (void)hoisted__Bool_3170;
        Str_delete(hoisted__Str_3169, hoisted__Bool_3170);
    }
    Bool hoisted__Bool_3187 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Match})));
    (void)hoisted__Bool_3187;
    if (hoisted__Bool_3187) {
        MatchData *hoisted__MatchData_3171 = get_payload(self);
        (void)hoisted__MatchData_3171;
        (void)hoisted__MatchData_3171;
        Bool hoisted__Bool_3172 = 0;
        (void)hoisted__Bool_3172;
        MatchData_delete(hoisted__MatchData_3171, hoisted__Bool_3172);
    }
    Bool hoisted__Bool_3188 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_CaptureBlock})));
    (void)hoisted__Bool_3188;
    if (hoisted__Bool_3188) {
        CaptureBlockData *hoisted__CaptureBlockData_3173 = get_payload(self);
        (void)hoisted__CaptureBlockData_3173;
        (void)hoisted__CaptureBlockData_3173;
        Bool hoisted__Bool_3174 = 0;
        (void)hoisted__Bool_3174;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3173, hoisted__Bool_3174);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3412 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Body})));
    (void)hoisted__Bool_3412;
    if (hoisted__Bool_3412) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3413 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Literal})));
    (void)hoisted__Bool_3413;
    if (hoisted__Bool_3413) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3384 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3384;
        NodeType *hoisted__NodeType_3385 = NodeType_Literal(hoisted__Literal_3384);
        (void)hoisted__NodeType_3385;
        { NodeType * _ret_val = hoisted__NodeType_3385;
                return _ret_val; }
    }
    Bool hoisted__Bool_3414 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Ident})));
    (void)hoisted__Bool_3414;
    if (hoisted__Bool_3414) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3386 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3386;
        NodeType *hoisted__NodeType_3387 = NodeType_Ident(hoisted__IdentData_3386);
        (void)hoisted__NodeType_3387;
        { NodeType * _ret_val = hoisted__NodeType_3387;
                return _ret_val; }
    }
    Bool hoisted__Bool_3415 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Decl})));
    (void)hoisted__Bool_3415;
    if (hoisted__Bool_3415) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3388 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3388;
        NodeType *hoisted__NodeType_3389 = NodeType_Decl(hoisted__Declaration_3388);
        (void)hoisted__NodeType_3389;
        { NodeType * _ret_val = hoisted__NodeType_3389;
                return _ret_val; }
    }
    Bool hoisted__Bool_3416 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Assign})));
    (void)hoisted__Bool_3416;
    if (hoisted__Bool_3416) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3390 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3390;
        NodeType *hoisted__NodeType_3391 = NodeType_Assign(hoisted__AssignData_3390);
        (void)hoisted__NodeType_3391;
        { NodeType * _ret_val = hoisted__NodeType_3391;
                return _ret_val; }
    }
    Bool hoisted__Bool_3417 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FCall})));
    (void)hoisted__Bool_3417;
    if (hoisted__Bool_3417) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3392 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3392;
        NodeType *hoisted__NodeType_3393 = NodeType_FCall(hoisted__FCallData_3392);
        (void)hoisted__NodeType_3393;
        { NodeType * _ret_val = hoisted__NodeType_3393;
                return _ret_val; }
    }
    Bool hoisted__Bool_3418 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FuncDef})));
    (void)hoisted__Bool_3418;
    if (hoisted__Bool_3418) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3394 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3394;
        NodeType *hoisted__NodeType_3395 = NodeType_FuncDef(hoisted__FunctionDef_3394);
        (void)hoisted__NodeType_3395;
        { NodeType * _ret_val = hoisted__NodeType_3395;
                return _ret_val; }
    }
    Bool hoisted__Bool_3419 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_StructDef})));
    (void)hoisted__Bool_3419;
    if (hoisted__Bool_3419) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3396 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3396;
        NodeType *hoisted__NodeType_3397 = NodeType_StructDef(hoisted__StructDef_3396);
        (void)hoisted__NodeType_3397;
        { NodeType * _ret_val = hoisted__NodeType_3397;
                return _ret_val; }
    }
    Bool hoisted__Bool_3420 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_EnumDef})));
    (void)hoisted__Bool_3420;
    if (hoisted__Bool_3420) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3398 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3398;
        NodeType *hoisted__NodeType_3399 = NodeType_EnumDef(hoisted__EnumDef_3398);
        (void)hoisted__NodeType_3399;
        { NodeType * _ret_val = hoisted__NodeType_3399;
                return _ret_val; }
    }
    Bool hoisted__Bool_3421 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAccess})));
    (void)hoisted__Bool_3421;
    if (hoisted__Bool_3421) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3400 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3400;
        NodeType *hoisted__NodeType_3401 = NodeType_FieldAccess(hoisted__FieldAccessData_3400);
        (void)hoisted__NodeType_3401;
        { NodeType * _ret_val = hoisted__NodeType_3401;
                return _ret_val; }
    }
    Bool hoisted__Bool_3422 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_FieldAssign})));
    (void)hoisted__Bool_3422;
    if (hoisted__Bool_3422) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3402 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3402;
        NodeType *hoisted__NodeType_3403 = NodeType_FieldAssign(hoisted__FieldAssignData_3402);
        (void)hoisted__NodeType_3403;
        { NodeType * _ret_val = hoisted__NodeType_3403;
                return _ret_val; }
    }
    Bool hoisted__Bool_3423 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Return})));
    (void)hoisted__Bool_3423;
    if (hoisted__Bool_3423) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3424 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_If})));
    (void)hoisted__Bool_3424;
    if (hoisted__Bool_3424) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3425 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_While})));
    (void)hoisted__Bool_3425;
    if (hoisted__Bool_3425) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3426 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_ForIn})));
    (void)hoisted__Bool_3426;
    if (hoisted__Bool_3426) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3404 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3404;
        NodeType *hoisted__NodeType_3405 = NodeType_ForIn(hoisted__ForInData_3404);
        (void)hoisted__NodeType_3405;
        { NodeType * _ret_val = hoisted__NodeType_3405;
                return _ret_val; }
    }
    Bool hoisted__Bool_3427 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_NamedArg})));
    (void)hoisted__Bool_3427;
    if (hoisted__Bool_3427) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3406 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3406;
        NodeType *hoisted__NodeType_3407 = NodeType_NamedArg(hoisted__Str_3406);
        (void)hoisted__NodeType_3407;
        { NodeType * _ret_val = hoisted__NodeType_3407;
                return _ret_val; }
    }
    Bool hoisted__Bool_3428 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Break})));
    (void)hoisted__Bool_3428;
    if (hoisted__Bool_3428) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3429 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Continue})));
    (void)hoisted__Bool_3429;
    if (hoisted__Bool_3429) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3430 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Switch})));
    (void)hoisted__Bool_3430;
    if (hoisted__Bool_3430) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3431 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Match})));
    (void)hoisted__Bool_3431;
    if (hoisted__Bool_3431) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3408 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3408;
        NodeType *hoisted__NodeType_3409 = NodeType_Match(hoisted__MatchData_3408);
        (void)hoisted__NodeType_3409;
        { NodeType * _ret_val = hoisted__NodeType_3409;
                return _ret_val; }
    }
    Bool hoisted__Bool_3432 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Case})));
    (void)hoisted__Bool_3432;
    if (hoisted__Bool_3432) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3433 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg})));
    (void)hoisted__Bool_3433;
    if (hoisted__Bool_3433) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3434 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Throw})));
    (void)hoisted__Bool_3434;
    if (hoisted__Bool_3434) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3435 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_Catch})));
    (void)hoisted__Bool_3435;
    if (hoisted__Bool_3435) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3436 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_RestPattern})));
    (void)hoisted__Bool_3436;
    if (hoisted__Bool_3436) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3437 = ((Bool)(*(I32*)(self) == *(I32*)(&(NodeType){.tag = NodeType_TAG_CaptureBlock})));
    (void)hoisted__Bool_3437;
    if (hoisted__Bool_3437) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3410 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3410;
        NodeType *hoisted__NodeType_3411 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3410);
        (void)hoisted__NodeType_3411;
        { NodeType * _ret_val = hoisted__NodeType_3411;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3438 = 136;
    (void)hoisted__U32_3438;
    return hoisted__U32_3438;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3439 = is_null(self);
    (void)hoisted__Bool_3439;
    if (hoisted__Bool_3439) {
        return;
    }
    Bool hoisted__Bool_3440 = 0;
    (void)hoisted__Bool_3440;
    NodeType_delete(&self->node_type, hoisted__Bool_3440);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3490 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3490->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3490->children = *_ca; free(_ca); }
    hoisted__Expr_3490->line = line;
    hoisted__Expr_3490->col = col;
    (void)hoisted__Expr_3490;
    return hoisted__Expr_3490;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3499 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3499->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3499->children = *_ca; free(_ca); }
    hoisted__Expr_3499->line = self->line;
    hoisted__Expr_3499->col = self->col;
    (void)hoisted__Expr_3499;
    return hoisted__Expr_3499;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3500 = 0;
    (void)hoisted__U32_3500;
    U64 hoisted__U64_3501 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3500); });
    (void)hoisted__U64_3501;
    return hoisted__U64_3501;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3502 = 160;
    (void)hoisted__U32_3502;
    return hoisted__U32_3502;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4446 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4446->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4446->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4446;
    return hoisted__Map__I64_Str_4446;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4559 = 0;
    (void)hoisted__Bool_4559;
    Vec__I64_delete(&self->keys, hoisted__Bool_4559);
    Bool hoisted__Bool_4560 = 0;
    (void)hoisted__Bool_4560;
    Vec__Str_delete(&self->values, hoisted__Bool_4560);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4561 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4561->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4561->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4561;
    return hoisted__Map__I64_Str_4561;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4562 = 0;
    (void)hoisted__U32_4562;
    U64 hoisted__U64_4563 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4562); });
    (void)hoisted__U64_4563;
    return hoisted__U64_4563;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4564 = 32;
    (void)hoisted__U32_4564;
    return hoisted__U32_4564;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4565 = 1;
    (void)hoisted__U32_4565;
    U64 hoisted__U64_4566 = (U64)(hoisted__U32_4565);
    (void)hoisted__U64_4566;
    void * hoisted__v_4567 = malloc(hoisted__U64_4566);
    (void)hoisted__v_4567;
    U32 hoisted__U32_4568 = 0;
    (void)hoisted__U32_4568;
    I64 hoisted__I64_4569 = 1;
    (void)hoisted__I64_4569;
    Vec__Bool *hoisted__Vec__Bool_4570 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4570->data = hoisted__v_4567;
    hoisted__Vec__Bool_4570->count = hoisted__U32_4568;
    hoisted__Vec__Bool_4570->cap = hoisted__I64_4569;
    (void)hoisted__Vec__Bool_4570;
    return hoisted__Vec__Bool_4570;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4580 = self->count;
        (void)_re_U32_4580;
        U32 _rc_U32_4580 = 0;
        (void)_rc_U32_4580;
        Bool hoisted__Bool_4593 = ((Bool)(_rc_U32_4580 <= _re_U32_4580));
        (void)hoisted__Bool_4593;
        if (hoisted__Bool_4593) {
            while (1) {
                Bool _wcond_Bool_4581 = ((Bool)(_rc_U32_4580 < _re_U32_4580));
                (void)_wcond_Bool_4581;
                if (_wcond_Bool_4581) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4580);
                U32_inc(&_rc_U32_4580);
                U32 hoisted__U32_4582 = 1;
                (void)hoisted__U32_4582;
                U32 hoisted__U32_4583 = ((U32)(i * hoisted__U32_4582));
                (void)hoisted__U32_4583;
                U64 hoisted__U64_4584 = (U64)(hoisted__U32_4583);
                (void)hoisted__U64_4584;
                Bool *hoisted__Bool_4585 = ptr_add(self->data, hoisted__U64_4584);
                (void)hoisted__Bool_4585;
                (void)hoisted__Bool_4585;
                Bool hoisted__Bool_4586 = 0;
                (void)hoisted__Bool_4586;
                Bool_delete(hoisted__Bool_4585, hoisted__Bool_4586);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4587 = ((Bool)(_rc_U32_4580 > _re_U32_4580));
                (void)_wcond_Bool_4587;
                if (_wcond_Bool_4587) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4580);
                U32_dec(&_rc_U32_4580);
                U32 hoisted__U32_4588 = 1;
                (void)hoisted__U32_4588;
                U32 hoisted__U32_4589 = ((U32)(i * hoisted__U32_4588));
                (void)hoisted__U32_4589;
                U64 hoisted__U64_4590 = (U64)(hoisted__U32_4589);
                (void)hoisted__U64_4590;
                Bool *hoisted__Bool_4591 = ptr_add(self->data, hoisted__U64_4590);
                (void)hoisted__Bool_4591;
                (void)hoisted__Bool_4591;
                Bool hoisted__Bool_4592 = 0;
                (void)hoisted__Bool_4592;
                Bool_delete(hoisted__Bool_4591, hoisted__Bool_4592);
            }
        }
    }
    U32 hoisted__U32_4594 = 0;
    (void)hoisted__U32_4594;
    self->count = hoisted__U32_4594;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4864 = 1;
    (void)hoisted__U32_4864;
    U32 hoisted__U32_4865 = ((U32)(self->cap * hoisted__U32_4864));
    (void)hoisted__U32_4865;
    U64 hoisted__U64_4866 = (U64)(hoisted__U32_4865);
    (void)hoisted__U64_4866;
    void * new_data = malloc(hoisted__U64_4866);
    {
        U32 _re_U32_4836 = self->count;
        (void)_re_U32_4836;
        U32 _rc_U32_4836 = 0;
        (void)_rc_U32_4836;
        Bool hoisted__Bool_4863 = ((Bool)(_rc_U32_4836 <= _re_U32_4836));
        (void)hoisted__Bool_4863;
        if (hoisted__Bool_4863) {
            while (1) {
                Bool _wcond_Bool_4837 = ((Bool)(_rc_U32_4836 < _re_U32_4836));
                (void)_wcond_Bool_4837;
                if (_wcond_Bool_4837) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4836);
                U32_inc(&_rc_U32_4836);
                U32 hoisted__U32_4838 = 1;
                (void)hoisted__U32_4838;
                U32 hoisted__U32_4839 = ((U32)(i * hoisted__U32_4838));
                (void)hoisted__U32_4839;
                U64 hoisted__U64_4840 = (U64)(hoisted__U32_4839);
                (void)hoisted__U64_4840;
                Bool *src = ptr_add(self->data, hoisted__U64_4840);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4841 = 1;
                (void)hoisted__U32_4841;
                U32 hoisted__U32_4842 = ((U32)(i * hoisted__U32_4841));
                (void)hoisted__U32_4842;
                U64 hoisted__U64_4843 = (U64)(hoisted__U32_4842);
                (void)hoisted__U64_4843;
                U32 hoisted__U32_4844 = 1;
                (void)hoisted__U32_4844;
                void *hoisted__v_4845 = ptr_add(new_data, hoisted__U64_4843);
                (void)hoisted__v_4845;
                (void)hoisted__v_4845;
                U64 hoisted__U64_4846 = (U64)(hoisted__U32_4844);
                (void)hoisted__U64_4846;
                memcpy(hoisted__v_4845, &cloned, hoisted__U64_4846);
                U32 hoisted__U32_4847 = 1;
                (void)hoisted__U32_4847;
                I32 hoisted__I32_4848 = 0;
                (void)hoisted__I32_4848;
                U64 hoisted__U64_4849 = (U64)(hoisted__U32_4847);
                (void)hoisted__U64_4849;
                memset(&cloned, hoisted__I32_4848, hoisted__U64_4849);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4850 = ((Bool)(_rc_U32_4836 > _re_U32_4836));
                (void)_wcond_Bool_4850;
                if (_wcond_Bool_4850) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4836);
                U32_dec(&_rc_U32_4836);
                U32 hoisted__U32_4851 = 1;
                (void)hoisted__U32_4851;
                U32 hoisted__U32_4852 = ((U32)(i * hoisted__U32_4851));
                (void)hoisted__U32_4852;
                U64 hoisted__U64_4853 = (U64)(hoisted__U32_4852);
                (void)hoisted__U64_4853;
                Bool *src = ptr_add(self->data, hoisted__U64_4853);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4854 = 1;
                (void)hoisted__U32_4854;
                U32 hoisted__U32_4855 = ((U32)(i * hoisted__U32_4854));
                (void)hoisted__U32_4855;
                U64 hoisted__U64_4856 = (U64)(hoisted__U32_4855);
                (void)hoisted__U64_4856;
                U32 hoisted__U32_4857 = 1;
                (void)hoisted__U32_4857;
                void *hoisted__v_4858 = ptr_add(new_data, hoisted__U64_4856);
                (void)hoisted__v_4858;
                (void)hoisted__v_4858;
                U64 hoisted__U64_4859 = (U64)(hoisted__U32_4857);
                (void)hoisted__U64_4859;
                memcpy(hoisted__v_4858, &cloned, hoisted__U64_4859);
                U32 hoisted__U32_4860 = 1;
                (void)hoisted__U32_4860;
                I32 hoisted__I32_4861 = 0;
                (void)hoisted__I32_4861;
                U64 hoisted__U64_4862 = (U64)(hoisted__U32_4860);
                (void)hoisted__U64_4862;
                memset(&cloned, hoisted__I32_4861, hoisted__U64_4862);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4867 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4867->data = new_data;
    hoisted__Vec__Bool_4867->count = self->count;
    hoisted__Vec__Bool_4867->cap = self->cap;
    (void)hoisted__Vec__Bool_4867;
    return hoisted__Vec__Bool_4867;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4868 = 16;
    (void)hoisted__U32_4868;
    return hoisted__U32_4868;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_4869 = 8;
    (void)hoisted__U32_4869;
    U64 hoisted__U64_4870 = (U64)(hoisted__U32_4869);
    (void)hoisted__U64_4870;
    void * hoisted__v_4871 = malloc(hoisted__U64_4870);
    (void)hoisted__v_4871;
    U32 hoisted__U32_4872 = 0;
    (void)hoisted__U32_4872;
    I64 hoisted__I64_4873 = 1;
    (void)hoisted__I64_4873;
    Vec__I64 *hoisted__Vec__I64_4874 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_4874->data = hoisted__v_4871;
    hoisted__Vec__I64_4874->count = hoisted__U32_4872;
    hoisted__Vec__I64_4874->cap = hoisted__I64_4873;
    (void)hoisted__Vec__I64_4874;
    return hoisted__Vec__I64_4874;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_4884 = self->count;
        (void)_re_U32_4884;
        U32 _rc_U32_4884 = 0;
        (void)_rc_U32_4884;
        Bool hoisted__Bool_4897 = ((Bool)(_rc_U32_4884 <= _re_U32_4884));
        (void)hoisted__Bool_4897;
        if (hoisted__Bool_4897) {
            while (1) {
                Bool _wcond_Bool_4885 = ((Bool)(_rc_U32_4884 < _re_U32_4884));
                (void)_wcond_Bool_4885;
                if (_wcond_Bool_4885) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4884);
                U32_inc(&_rc_U32_4884);
                U32 hoisted__U32_4886 = 8;
                (void)hoisted__U32_4886;
                U32 hoisted__U32_4887 = ((U32)(i * hoisted__U32_4886));
                (void)hoisted__U32_4887;
                U64 hoisted__U64_4888 = (U64)(hoisted__U32_4887);
                (void)hoisted__U64_4888;
                I64 *hoisted__I64_4889 = ptr_add(self->data, hoisted__U64_4888);
                (void)hoisted__I64_4889;
                (void)hoisted__I64_4889;
                Bool hoisted__Bool_4890 = 0;
                (void)hoisted__Bool_4890;
                I64_delete(hoisted__I64_4889, hoisted__Bool_4890);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4891 = ((Bool)(_rc_U32_4884 > _re_U32_4884));
                (void)_wcond_Bool_4891;
                if (_wcond_Bool_4891) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4884);
                U32_dec(&_rc_U32_4884);
                U32 hoisted__U32_4892 = 8;
                (void)hoisted__U32_4892;
                U32 hoisted__U32_4893 = ((U32)(i * hoisted__U32_4892));
                (void)hoisted__U32_4893;
                U64 hoisted__U64_4894 = (U64)(hoisted__U32_4893);
                (void)hoisted__U64_4894;
                I64 *hoisted__I64_4895 = ptr_add(self->data, hoisted__U64_4894);
                (void)hoisted__I64_4895;
                (void)hoisted__I64_4895;
                Bool hoisted__Bool_4896 = 0;
                (void)hoisted__Bool_4896;
                I64_delete(hoisted__I64_4895, hoisted__Bool_4896);
            }
        }
    }
    U32 hoisted__U32_4898 = 0;
    (void)hoisted__U32_4898;
    self->count = hoisted__U32_4898;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5168 = 8;
    (void)hoisted__U32_5168;
    U32 hoisted__U32_5169 = ((U32)(self->cap * hoisted__U32_5168));
    (void)hoisted__U32_5169;
    U64 hoisted__U64_5170 = (U64)(hoisted__U32_5169);
    (void)hoisted__U64_5170;
    void * new_data = malloc(hoisted__U64_5170);
    {
        U32 _re_U32_5140 = self->count;
        (void)_re_U32_5140;
        U32 _rc_U32_5140 = 0;
        (void)_rc_U32_5140;
        Bool hoisted__Bool_5167 = ((Bool)(_rc_U32_5140 <= _re_U32_5140));
        (void)hoisted__Bool_5167;
        if (hoisted__Bool_5167) {
            while (1) {
                Bool _wcond_Bool_5141 = ((Bool)(_rc_U32_5140 < _re_U32_5140));
                (void)_wcond_Bool_5141;
                if (_wcond_Bool_5141) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5140);
                U32_inc(&_rc_U32_5140);
                U32 hoisted__U32_5142 = 8;
                (void)hoisted__U32_5142;
                U32 hoisted__U32_5143 = ((U32)(i * hoisted__U32_5142));
                (void)hoisted__U32_5143;
                U64 hoisted__U64_5144 = (U64)(hoisted__U32_5143);
                (void)hoisted__U64_5144;
                I64 *src = ptr_add(self->data, hoisted__U64_5144);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5145 = 8;
                (void)hoisted__U32_5145;
                U32 hoisted__U32_5146 = ((U32)(i * hoisted__U32_5145));
                (void)hoisted__U32_5146;
                U64 hoisted__U64_5147 = (U64)(hoisted__U32_5146);
                (void)hoisted__U64_5147;
                U32 hoisted__U32_5148 = 8;
                (void)hoisted__U32_5148;
                void *hoisted__v_5149 = ptr_add(new_data, hoisted__U64_5147);
                (void)hoisted__v_5149;
                (void)hoisted__v_5149;
                U64 hoisted__U64_5150 = (U64)(hoisted__U32_5148);
                (void)hoisted__U64_5150;
                memcpy(hoisted__v_5149, &cloned, hoisted__U64_5150);
                U32 hoisted__U32_5151 = 8;
                (void)hoisted__U32_5151;
                I32 hoisted__I32_5152 = 0;
                (void)hoisted__I32_5152;
                U64 hoisted__U64_5153 = (U64)(hoisted__U32_5151);
                (void)hoisted__U64_5153;
                memset(&cloned, hoisted__I32_5152, hoisted__U64_5153);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5154 = ((Bool)(_rc_U32_5140 > _re_U32_5140));
                (void)_wcond_Bool_5154;
                if (_wcond_Bool_5154) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5140);
                U32_dec(&_rc_U32_5140);
                U32 hoisted__U32_5155 = 8;
                (void)hoisted__U32_5155;
                U32 hoisted__U32_5156 = ((U32)(i * hoisted__U32_5155));
                (void)hoisted__U32_5156;
                U64 hoisted__U64_5157 = (U64)(hoisted__U32_5156);
                (void)hoisted__U64_5157;
                I64 *src = ptr_add(self->data, hoisted__U64_5157);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5158 = 8;
                (void)hoisted__U32_5158;
                U32 hoisted__U32_5159 = ((U32)(i * hoisted__U32_5158));
                (void)hoisted__U32_5159;
                U64 hoisted__U64_5160 = (U64)(hoisted__U32_5159);
                (void)hoisted__U64_5160;
                U32 hoisted__U32_5161 = 8;
                (void)hoisted__U32_5161;
                void *hoisted__v_5162 = ptr_add(new_data, hoisted__U64_5160);
                (void)hoisted__v_5162;
                (void)hoisted__v_5162;
                U64 hoisted__U64_5163 = (U64)(hoisted__U32_5161);
                (void)hoisted__U64_5163;
                memcpy(hoisted__v_5162, &cloned, hoisted__U64_5163);
                U32 hoisted__U32_5164 = 8;
                (void)hoisted__U32_5164;
                I32 hoisted__I32_5165 = 0;
                (void)hoisted__I32_5165;
                U64 hoisted__U64_5166 = (U64)(hoisted__U32_5164);
                (void)hoisted__U64_5166;
                memset(&cloned, hoisted__I32_5165, hoisted__U64_5166);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5171 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5171->data = new_data;
    hoisted__Vec__I64_5171->count = self->count;
    hoisted__Vec__I64_5171->cap = self->cap;
    (void)hoisted__Vec__I64_5171;
    return hoisted__Vec__I64_5171;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5172 = 16;
    (void)hoisted__U32_5172;
    return hoisted__U32_5172;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5477 = 104;
    (void)hoisted__U32_5477;
    U64 hoisted__U64_5478 = (U64)(hoisted__U32_5477);
    (void)hoisted__U64_5478;
    void * hoisted__v_5479 = malloc(hoisted__U64_5478);
    (void)hoisted__v_5479;
    U32 hoisted__U32_5480 = 0;
    (void)hoisted__U32_5480;
    I64 hoisted__I64_5481 = 1;
    (void)hoisted__I64_5481;
    Vec__Declaration *hoisted__Vec__Declaration_5482 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5482->data = hoisted__v_5479;
    hoisted__Vec__Declaration_5482->count = hoisted__U32_5480;
    hoisted__Vec__Declaration_5482->cap = hoisted__I64_5481;
    (void)hoisted__Vec__Declaration_5482;
    return hoisted__Vec__Declaration_5482;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5492 = self->count;
        (void)_re_U32_5492;
        U32 _rc_U32_5492 = 0;
        (void)_rc_U32_5492;
        Bool hoisted__Bool_5505 = ((Bool)(_rc_U32_5492 <= _re_U32_5492));
        (void)hoisted__Bool_5505;
        if (hoisted__Bool_5505) {
            while (1) {
                Bool _wcond_Bool_5493 = ((Bool)(_rc_U32_5492 < _re_U32_5492));
                (void)_wcond_Bool_5493;
                if (_wcond_Bool_5493) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5492);
                U32_inc(&_rc_U32_5492);
                U32 hoisted__U32_5494 = 104;
                (void)hoisted__U32_5494;
                U32 hoisted__U32_5495 = ((U32)(i * hoisted__U32_5494));
                (void)hoisted__U32_5495;
                U64 hoisted__U64_5496 = (U64)(hoisted__U32_5495);
                (void)hoisted__U64_5496;
                Declaration *hoisted__Declaration_5497 = ptr_add(self->data, hoisted__U64_5496);
                (void)hoisted__Declaration_5497;
                (void)hoisted__Declaration_5497;
                Bool hoisted__Bool_5498 = 0;
                (void)hoisted__Bool_5498;
                Declaration_delete(hoisted__Declaration_5497, hoisted__Bool_5498);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5499 = ((Bool)(_rc_U32_5492 > _re_U32_5492));
                (void)_wcond_Bool_5499;
                if (_wcond_Bool_5499) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5492);
                U32_dec(&_rc_U32_5492);
                U32 hoisted__U32_5500 = 104;
                (void)hoisted__U32_5500;
                U32 hoisted__U32_5501 = ((U32)(i * hoisted__U32_5500));
                (void)hoisted__U32_5501;
                U64 hoisted__U64_5502 = (U64)(hoisted__U32_5501);
                (void)hoisted__U64_5502;
                Declaration *hoisted__Declaration_5503 = ptr_add(self->data, hoisted__U64_5502);
                (void)hoisted__Declaration_5503;
                (void)hoisted__Declaration_5503;
                Bool hoisted__Bool_5504 = 0;
                (void)hoisted__Bool_5504;
                Declaration_delete(hoisted__Declaration_5503, hoisted__Bool_5504);
            }
        }
    }
    U32 hoisted__U32_5506 = 0;
    (void)hoisted__U32_5506;
    self->count = hoisted__U32_5506;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5776 = 104;
    (void)hoisted__U32_5776;
    U32 hoisted__U32_5777 = ((U32)(self->cap * hoisted__U32_5776));
    (void)hoisted__U32_5777;
    U64 hoisted__U64_5778 = (U64)(hoisted__U32_5777);
    (void)hoisted__U64_5778;
    void * new_data = malloc(hoisted__U64_5778);
    {
        U32 _re_U32_5748 = self->count;
        (void)_re_U32_5748;
        U32 _rc_U32_5748 = 0;
        (void)_rc_U32_5748;
        Bool hoisted__Bool_5775 = ((Bool)(_rc_U32_5748 <= _re_U32_5748));
        (void)hoisted__Bool_5775;
        if (hoisted__Bool_5775) {
            while (1) {
                Bool _wcond_Bool_5749 = ((Bool)(_rc_U32_5748 < _re_U32_5748));
                (void)_wcond_Bool_5749;
                if (_wcond_Bool_5749) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5748);
                U32_inc(&_rc_U32_5748);
                U32 hoisted__U32_5750 = 104;
                (void)hoisted__U32_5750;
                U32 hoisted__U32_5751 = ((U32)(i * hoisted__U32_5750));
                (void)hoisted__U32_5751;
                U64 hoisted__U64_5752 = (U64)(hoisted__U32_5751);
                (void)hoisted__U64_5752;
                Declaration *src = ptr_add(self->data, hoisted__U64_5752);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5753 = 104;
                (void)hoisted__U32_5753;
                U32 hoisted__U32_5754 = ((U32)(i * hoisted__U32_5753));
                (void)hoisted__U32_5754;
                U64 hoisted__U64_5755 = (U64)(hoisted__U32_5754);
                (void)hoisted__U64_5755;
                U32 hoisted__U32_5756 = 104;
                (void)hoisted__U32_5756;
                void *hoisted__v_5757 = ptr_add(new_data, hoisted__U64_5755);
                (void)hoisted__v_5757;
                (void)hoisted__v_5757;
                U64 hoisted__U64_5758 = (U64)(hoisted__U32_5756);
                (void)hoisted__U64_5758;
                memcpy(hoisted__v_5757, cloned, hoisted__U64_5758);
                U32 hoisted__U32_5759 = 104;
                (void)hoisted__U32_5759;
                I32 hoisted__I32_5760 = 0;
                (void)hoisted__I32_5760;
                U64 hoisted__U64_5761 = (U64)(hoisted__U32_5759);
                (void)hoisted__U64_5761;
                memset(cloned, hoisted__I32_5760, hoisted__U64_5761);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5762 = ((Bool)(_rc_U32_5748 > _re_U32_5748));
                (void)_wcond_Bool_5762;
                if (_wcond_Bool_5762) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5748);
                U32_dec(&_rc_U32_5748);
                U32 hoisted__U32_5763 = 104;
                (void)hoisted__U32_5763;
                U32 hoisted__U32_5764 = ((U32)(i * hoisted__U32_5763));
                (void)hoisted__U32_5764;
                U64 hoisted__U64_5765 = (U64)(hoisted__U32_5764);
                (void)hoisted__U64_5765;
                Declaration *src = ptr_add(self->data, hoisted__U64_5765);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5766 = 104;
                (void)hoisted__U32_5766;
                U32 hoisted__U32_5767 = ((U32)(i * hoisted__U32_5766));
                (void)hoisted__U32_5767;
                U64 hoisted__U64_5768 = (U64)(hoisted__U32_5767);
                (void)hoisted__U64_5768;
                U32 hoisted__U32_5769 = 104;
                (void)hoisted__U32_5769;
                void *hoisted__v_5770 = ptr_add(new_data, hoisted__U64_5768);
                (void)hoisted__v_5770;
                (void)hoisted__v_5770;
                U64 hoisted__U64_5771 = (U64)(hoisted__U32_5769);
                (void)hoisted__U64_5771;
                memcpy(hoisted__v_5770, cloned, hoisted__U64_5771);
                U32 hoisted__U32_5772 = 104;
                (void)hoisted__U32_5772;
                I32 hoisted__I32_5773 = 0;
                (void)hoisted__I32_5773;
                U64 hoisted__U64_5774 = (U64)(hoisted__U32_5772);
                (void)hoisted__U64_5774;
                memset(cloned, hoisted__I32_5773, hoisted__U64_5774);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5779 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5779->data = new_data;
    hoisted__Vec__Declaration_5779->count = self->count;
    hoisted__Vec__Declaration_5779->cap = self->cap;
    (void)hoisted__Vec__Declaration_5779;
    return hoisted__Vec__Declaration_5779;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5780 = 16;
    (void)hoisted__U32_5780;
    return hoisted__U32_5780;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5781 = 160;
    (void)hoisted__U32_5781;
    U64 hoisted__U64_5782 = (U64)(hoisted__U32_5781);
    (void)hoisted__U64_5782;
    void * hoisted__v_5783 = malloc(hoisted__U64_5782);
    (void)hoisted__v_5783;
    U32 hoisted__U32_5784 = 0;
    (void)hoisted__U32_5784;
    I64 hoisted__I64_5785 = 1;
    (void)hoisted__I64_5785;
    Vec__Expr *hoisted__Vec__Expr_5786 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5786->data = hoisted__v_5783;
    hoisted__Vec__Expr_5786->count = hoisted__U32_5784;
    hoisted__Vec__Expr_5786->cap = hoisted__I64_5785;
    (void)hoisted__Vec__Expr_5786;
    return hoisted__Vec__Expr_5786;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5796 = self->count;
        (void)_re_U32_5796;
        U32 _rc_U32_5796 = 0;
        (void)_rc_U32_5796;
        Bool hoisted__Bool_5809 = ((Bool)(_rc_U32_5796 <= _re_U32_5796));
        (void)hoisted__Bool_5809;
        if (hoisted__Bool_5809) {
            while (1) {
                Bool _wcond_Bool_5797 = ((Bool)(_rc_U32_5796 < _re_U32_5796));
                (void)_wcond_Bool_5797;
                if (_wcond_Bool_5797) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5796);
                U32_inc(&_rc_U32_5796);
                U32 hoisted__U32_5798 = 160;
                (void)hoisted__U32_5798;
                U32 hoisted__U32_5799 = ((U32)(i * hoisted__U32_5798));
                (void)hoisted__U32_5799;
                U64 hoisted__U64_5800 = (U64)(hoisted__U32_5799);
                (void)hoisted__U64_5800;
                Expr *hoisted__Expr_5801 = ptr_add(self->data, hoisted__U64_5800);
                (void)hoisted__Expr_5801;
                (void)hoisted__Expr_5801;
                Bool hoisted__Bool_5802 = 0;
                (void)hoisted__Bool_5802;
                Expr_delete(hoisted__Expr_5801, hoisted__Bool_5802);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5803 = ((Bool)(_rc_U32_5796 > _re_U32_5796));
                (void)_wcond_Bool_5803;
                if (_wcond_Bool_5803) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5796);
                U32_dec(&_rc_U32_5796);
                U32 hoisted__U32_5804 = 160;
                (void)hoisted__U32_5804;
                U32 hoisted__U32_5805 = ((U32)(i * hoisted__U32_5804));
                (void)hoisted__U32_5805;
                U64 hoisted__U64_5806 = (U64)(hoisted__U32_5805);
                (void)hoisted__U64_5806;
                Expr *hoisted__Expr_5807 = ptr_add(self->data, hoisted__U64_5806);
                (void)hoisted__Expr_5807;
                (void)hoisted__Expr_5807;
                Bool hoisted__Bool_5808 = 0;
                (void)hoisted__Bool_5808;
                Expr_delete(hoisted__Expr_5807, hoisted__Bool_5808);
            }
        }
    }
    U32 hoisted__U32_5810 = 0;
    (void)hoisted__U32_5810;
    self->count = hoisted__U32_5810;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_6080 = 160;
    (void)hoisted__U32_6080;
    U32 hoisted__U32_6081 = ((U32)(self->cap * hoisted__U32_6080));
    (void)hoisted__U32_6081;
    U64 hoisted__U64_6082 = (U64)(hoisted__U32_6081);
    (void)hoisted__U64_6082;
    void * new_data = malloc(hoisted__U64_6082);
    {
        U32 _re_U32_6052 = self->count;
        (void)_re_U32_6052;
        U32 _rc_U32_6052 = 0;
        (void)_rc_U32_6052;
        Bool hoisted__Bool_6079 = ((Bool)(_rc_U32_6052 <= _re_U32_6052));
        (void)hoisted__Bool_6079;
        if (hoisted__Bool_6079) {
            while (1) {
                Bool _wcond_Bool_6053 = ((Bool)(_rc_U32_6052 < _re_U32_6052));
                (void)_wcond_Bool_6053;
                if (_wcond_Bool_6053) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6052);
                U32_inc(&_rc_U32_6052);
                U32 hoisted__U32_6054 = 160;
                (void)hoisted__U32_6054;
                U32 hoisted__U32_6055 = ((U32)(i * hoisted__U32_6054));
                (void)hoisted__U32_6055;
                U64 hoisted__U64_6056 = (U64)(hoisted__U32_6055);
                (void)hoisted__U64_6056;
                Expr *src = ptr_add(self->data, hoisted__U64_6056);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6057 = 160;
                (void)hoisted__U32_6057;
                U32 hoisted__U32_6058 = ((U32)(i * hoisted__U32_6057));
                (void)hoisted__U32_6058;
                U64 hoisted__U64_6059 = (U64)(hoisted__U32_6058);
                (void)hoisted__U64_6059;
                U32 hoisted__U32_6060 = 160;
                (void)hoisted__U32_6060;
                void *hoisted__v_6061 = ptr_add(new_data, hoisted__U64_6059);
                (void)hoisted__v_6061;
                (void)hoisted__v_6061;
                U64 hoisted__U64_6062 = (U64)(hoisted__U32_6060);
                (void)hoisted__U64_6062;
                memcpy(hoisted__v_6061, cloned, hoisted__U64_6062);
                U32 hoisted__U32_6063 = 160;
                (void)hoisted__U32_6063;
                I32 hoisted__I32_6064 = 0;
                (void)hoisted__I32_6064;
                U64 hoisted__U64_6065 = (U64)(hoisted__U32_6063);
                (void)hoisted__U64_6065;
                memset(cloned, hoisted__I32_6064, hoisted__U64_6065);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_6066 = ((Bool)(_rc_U32_6052 > _re_U32_6052));
                (void)_wcond_Bool_6066;
                if (_wcond_Bool_6066) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_6052);
                U32_dec(&_rc_U32_6052);
                U32 hoisted__U32_6067 = 160;
                (void)hoisted__U32_6067;
                U32 hoisted__U32_6068 = ((U32)(i * hoisted__U32_6067));
                (void)hoisted__U32_6068;
                U64 hoisted__U64_6069 = (U64)(hoisted__U32_6068);
                (void)hoisted__U64_6069;
                Expr *src = ptr_add(self->data, hoisted__U64_6069);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_6070 = 160;
                (void)hoisted__U32_6070;
                U32 hoisted__U32_6071 = ((U32)(i * hoisted__U32_6070));
                (void)hoisted__U32_6071;
                U64 hoisted__U64_6072 = (U64)(hoisted__U32_6071);
                (void)hoisted__U64_6072;
                U32 hoisted__U32_6073 = 160;
                (void)hoisted__U32_6073;
                void *hoisted__v_6074 = ptr_add(new_data, hoisted__U64_6072);
                (void)hoisted__v_6074;
                (void)hoisted__v_6074;
                U64 hoisted__U64_6075 = (U64)(hoisted__U32_6073);
                (void)hoisted__U64_6075;
                memcpy(hoisted__v_6074, cloned, hoisted__U64_6075);
                U32 hoisted__U32_6076 = 160;
                (void)hoisted__U32_6076;
                I32 hoisted__I32_6077 = 0;
                (void)hoisted__I32_6077;
                U64 hoisted__U64_6078 = (U64)(hoisted__U32_6076);
                (void)hoisted__U64_6078;
                memset(cloned, hoisted__I32_6077, hoisted__U64_6078);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_6083 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_6083->data = new_data;
    hoisted__Vec__Expr_6083->count = self->count;
    hoisted__Vec__Expr_6083->cap = self->cap;
    (void)hoisted__Vec__Expr_6083;
    return hoisted__Vec__Expr_6083;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_6084 = 16;
    (void)hoisted__U32_6084;
    return hoisted__U32_6084;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7203 = 3;
    (void)hoisted__U32_7203;
    Array__Str *_va_Array_204 = Array__Str_new(hoisted__U32_7203);
    (void)_va_Array_204;
    I64 _va_Array_204_ek = 0;
    (void)_va_Array_204_ek;
    OutOfBounds *_va_Array_204_eo = malloc(sizeof(OutOfBounds));
    _va_Array_204_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_204_eo;
    U32 hoisted__U32_7204 = 0;
    (void)hoisted__U32_7204;
    Str *hoisted__Str_7205 = Str_clone(loc);
    (void)hoisted__Str_7205;
    (void)hoisted__Str_7206;
    (void)hoisted__Str_7206;
    Array__Str_set(_va_Array_204, hoisted__U32_7204, hoisted__Str_7205, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7206);
    Str_delete(&hoisted__Str_7206, (Bool){0});
    U32 hoisted__U32_7207 = 1;
    (void)hoisted__U32_7207;
    (void)hoisted__Str_7208;
    (void)hoisted__Str_7208;
    (void)hoisted__Str_7209;
    (void)hoisted__Str_7209;
    Array__Str_set(_va_Array_204, hoisted__U32_7207, &hoisted__Str_7208, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7209);
    Str_delete(&hoisted__Str_7209, (Bool){0});
    Array__Str *hoisted__Array__Str_7210 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7210;
    U32 hoisted__U32_7211 = 2;
    (void)hoisted__U32_7211;
    Str *hoisted__Str_7212 = format(hoisted__Array__Str_7210);
    (void)hoisted__Str_7212;
    (void)hoisted__Str_7213;
    (void)hoisted__Str_7213;
    Array__Str_set(_va_Array_204, hoisted__U32_7211, hoisted__Str_7212, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7213);
    OutOfBounds_delete(_va_Array_204_eo, 1);
    Str_delete(&hoisted__Str_7213, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_204);
    I64 hoisted__I64_7214 = 1;
    (void)hoisted__I64_7214;
    exit(hoisted__I64_7214);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7223 = 1;
    (void)hoisted__U32_7223;
    Array__Str *_va_Array_206 = Array__Str_new(hoisted__U32_7223);
    (void)_va_Array_206;
    I64 _va_Array_206_ek = 0;
    (void)_va_Array_206_ek;
    OutOfBounds *_va_Array_206_eo = malloc(sizeof(OutOfBounds));
    _va_Array_206_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_206_eo;
    U32 hoisted__U32_7224 = 0;
    (void)hoisted__U32_7224;
    (void)hoisted__Str_7225;
    (void)hoisted__Str_7225;
    (void)hoisted__Str_7226;
    (void)hoisted__Str_7226;
    Array__Str_set(_va_Array_206, hoisted__U32_7224, &hoisted__Str_7225, &_va_Array_206_ek, _va_Array_206_eo, &hoisted__Str_7226);
    OutOfBounds_delete(_va_Array_206_eo, 1);
    Str_delete(&hoisted__Str_7226, (Bool){0});
    panic(_va_Array_206, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7231 = not(cond);
    (void)hoisted__Bool_7231;
    if (hoisted__Bool_7231) {
        U32 hoisted__U32_7227 = 1;
        (void)hoisted__U32_7227;
        Array__Str *_va_Array_207 = Array__Str_new(hoisted__U32_7227);
        (void)_va_Array_207;
        I64 _va_Array_207_ek = 0;
        (void)_va_Array_207_ek;
        OutOfBounds *_va_Array_207_eo = malloc(sizeof(OutOfBounds));
        _va_Array_207_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_207_eo;
        U32 hoisted__U32_7228 = 0;
        (void)hoisted__U32_7228;
        (void)hoisted__Str_7229;
        (void)hoisted__Str_7229;
        (void)hoisted__Str_7230;
        (void)hoisted__Str_7230;
        Array__Str_set(_va_Array_207, hoisted__U32_7228, &hoisted__Str_7229, &_va_Array_207_ek, _va_Array_207_eo, &hoisted__Str_7230);
        OutOfBounds_delete(_va_Array_207_eo, 1);
        Str_delete(&hoisted__Str_7230, (Bool){0});
        panic(_va_Array_207, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7241 = parts;
        (void)_fc_Array__Str_7241;
        (void)_fc_Array__Str_7241;
        U32 _fi_USize_7241 = 0;
        (void)_fi_USize_7241;
        while (1) {
            U32 hoisted__U32_7243 = Array__Str_len(_fc_Array__Str_7241);
            (void)hoisted__U32_7243;
            Bool _wcond_Bool_7242 = ((Bool)(_fi_USize_7241 < hoisted__U32_7243));
            (void)_wcond_Bool_7242;
            if (_wcond_Bool_7242) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7241, &_fi_USize_7241);
            U32 hoisted__U32_7244 = 1;
            (void)hoisted__U32_7244;
            U32 hoisted__U32_7245 = ((U32)(_fi_USize_7241 + hoisted__U32_7244));
            (void)hoisted__U32_7245;
            _fi_USize_7241 = hoisted__U32_7245;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7279 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7279;
    return hoisted__Bool_7279;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7288 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7288;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7288;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7289 = 0;
    (void)hoisted__U32_7289;
    U64 hoisted__U64_7290 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7289); });
    (void)hoisted__U64_7290;
    return hoisted__U64_7290;
}

U32 Range_size(void) {
    U32 hoisted__U32_7321 = 16;
    (void)hoisted__U32_7321;
    return hoisted__U32_7321;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7337 = 3;
    (void)hoisted__I64_7337;
    (void)hoisted__Str_7338;
    (void)hoisted__Str_7338;
    assert_eq__I64(result, hoisted__I64_7337, &hoisted__Str_7338);
    Str_delete(&hoisted__Str_7338, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7345 = 15;
    (void)hoisted__I64_7345;
    (void)hoisted__Str_7346;
    (void)hoisted__Str_7346;
    assert_eq__I64(result, hoisted__I64_7345, &hoisted__Str_7346);
    Str_delete(&hoisted__Str_7346, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7353 = 26;
    (void)hoisted__I64_7353;
    (void)hoisted__Str_7354;
    (void)hoisted__Str_7354;
    assert_eq__I64(result, hoisted__I64_7353, &hoisted__Str_7354);
    Str_delete(&hoisted__Str_7354, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7357;
    (void)hoisted__Str_7357;
    (void)hoisted__Str_7358;
    (void)hoisted__Str_7358;
    assert_eq__Str(&result, &hoisted__Str_7357, &hoisted__Str_7358);
    Str_delete(&hoisted__Str_7357, (Bool){0});
    Str_delete(&hoisted__Str_7358, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7386;
    (void)hoisted__Str_7386;
    (void)hoisted__Str_7387;
    (void)hoisted__Str_7387;
    assert_eq__Str(&r, &hoisted__Str_7386, &hoisted__Str_7387);
    Str_delete(&hoisted__Str_7386, (Bool){0});
    Str_delete(&hoisted__Str_7387, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7391;
    (void)hoisted__Str_7391;
    (void)hoisted__Str_7392;
    (void)hoisted__Str_7392;
    assert_eq__Str(&r2, &hoisted__Str_7391, &hoisted__Str_7392);
    Str_delete(&hoisted__Str_7391, (Bool){0});
    Str_delete(&hoisted__Str_7392, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7415;
    (void)hoisted__Str_7415;
    (void)hoisted__Str_7416;
    (void)hoisted__Str_7416;
    assert_eq__Str(&d, &hoisted__Str_7415, &hoisted__Str_7416);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7415, (Bool){0});
    Str_delete(&hoisted__Str_7416, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7427;
    (void)hoisted__Str_7427;
    (void)hoisted__Str_7428;
    (void)hoisted__Str_7428;
    assert_eq__Str(&d2, &hoisted__Str_7427, &hoisted__Str_7428);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7427, (Bool){0});
    Str_delete(&hoisted__Str_7428, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7440 = 106;
    (void)hoisted__I64_7440;
    (void)hoisted__Str_7441;
    (void)hoisted__Str_7441;
    assert_eq__I64(d3, hoisted__I64_7440, &hoisted__Str_7441);
    Str_delete(&hoisted__Str_7441, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8040;
    (void)hoisted__Str_8040;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8040);
    Str_delete(&hoisted__Str_8040, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)hoisted__Str_8041;
    (void)hoisted__Str_8041;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8041);
    Str_delete(&hoisted__Str_8041, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8043 = 8;
    (void)hoisted__I64_8043;
    (void)hoisted__Str_8044;
    (void)hoisted__Str_8044;
    assert_eq__I64(result, hoisted__I64_8043, &hoisted__Str_8044);
    Str_delete(&hoisted__Str_8044, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8047 = 1;
    (void)hoisted__Bool_8047;
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8048;
    assert(hoisted__Bool_8047, &hoisted__Str_8048);
    Str_delete(&hoisted__Str_8048, (Bool){0});
    Bool hoisted__Bool_8051 = 1;
    (void)hoisted__Bool_8051;
    (void)hoisted__Str_8052;
    (void)hoisted__Str_8052;
    assert(hoisted__Bool_8051, &hoisted__Str_8052);
    Str_delete(&hoisted__Str_8052, (Bool){0});
}

void test_fold_f32(void) {
    (void)hoisted__Str_8057;
    (void)hoisted__Str_8057;
    (void)hoisted__Str_8058;
    (void)hoisted__Str_8058;
    (void)hoisted__Str_8059;
    (void)hoisted__Str_8059;
    assert_eq__Str(&hoisted__Str_8057, &hoisted__Str_8058, &hoisted__Str_8059);
    Str_delete(&hoisted__Str_8057, (Bool){0});
    Str_delete(&hoisted__Str_8058, (Bool){0});
    Str_delete(&hoisted__Str_8059, (Bool){0});
    (void)hoisted__Str_8062;
    (void)hoisted__Str_8062;
    (void)hoisted__Str_8063;
    (void)hoisted__Str_8063;
    (void)hoisted__Str_8064;
    (void)hoisted__Str_8064;
    assert_eq__Str(&hoisted__Str_8062, &hoisted__Str_8063, &hoisted__Str_8064);
    Str_delete(&hoisted__Str_8062, (Bool){0});
    Str_delete(&hoisted__Str_8063, (Bool){0});
    Str_delete(&hoisted__Str_8064, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8069 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8069;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8069;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8070 = 0;
    (void)hoisted__U32_8070;
    U64 hoisted__U64_8071 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8070); });
    (void)hoisted__U64_8071;
    return hoisted__U64_8071;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8102 = 16;
    (void)hoisted__U32_8102;
    return hoisted__U32_8102;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8103 = 42;
    (void)hoisted__I64_8103;
    (void)hoisted__Str_8104;
    (void)hoisted__Str_8104;
    assert_eq__I64(v.x, hoisted__I64_8103, &hoisted__Str_8104);
    Str_delete(&hoisted__Str_8104, (Bool){0});
    I64 hoisted__I64_8105 = 99;
    (void)hoisted__I64_8105;
    (void)hoisted__Str_8106;
    (void)hoisted__Str_8106;
    assert_eq__I64(v.y, hoisted__I64_8105, &hoisted__Str_8106);
    Str_delete(&hoisted__Str_8106, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8109 = 10;
    (void)hoisted__I64_8109;
    (void)hoisted__Str_8110;
    (void)hoisted__Str_8110;
    assert_eq__I64(p.x, hoisted__I64_8109, &hoisted__Str_8110);
    Str_delete(&hoisted__Str_8110, (Bool){0});
    I64 hoisted__I64_8111 = 20;
    (void)hoisted__I64_8111;
    (void)hoisted__Str_8112;
    (void)hoisted__Str_8112;
    assert_eq__I64(p.y, hoisted__I64_8111, &hoisted__Str_8112);
    Str_delete(&hoisted__Str_8112, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8118 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8118;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8118;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8119 = 0;
    (void)hoisted__U32_8119;
    U64 hoisted__U64_8120 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8119); });
    (void)hoisted__U64_8120;
    return hoisted__U64_8120;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8151 = 32;
    (void)hoisted__U32_8151;
    return hoisted__U32_8151;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8152 = 5;
    (void)hoisted__I64_8152;
    (void)hoisted__Str_8153;
    (void)hoisted__Str_8153;
    assert_eq__I64(r.top_left.x, hoisted__I64_8152, &hoisted__Str_8153);
    Str_delete(&hoisted__Str_8153, (Bool){0});
    I64 hoisted__I64_8154 = 10;
    (void)hoisted__I64_8154;
    (void)hoisted__Str_8155;
    (void)hoisted__Str_8155;
    assert_eq__I64(r.top_left.y, hoisted__I64_8154, &hoisted__Str_8155);
    Str_delete(&hoisted__Str_8155, (Bool){0});
    I64 hoisted__I64_8156 = 100;
    (void)hoisted__I64_8156;
    (void)hoisted__Str_8157;
    (void)hoisted__Str_8157;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8156, &hoisted__Str_8157);
    Str_delete(&hoisted__Str_8157, (Bool){0});
    I64 hoisted__I64_8158 = 200;
    (void)hoisted__I64_8158;
    (void)hoisted__Str_8159;
    (void)hoisted__Str_8159;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8158, &hoisted__Str_8159);
    Str_delete(&hoisted__Str_8159, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8161 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8161;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8161;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8162 = 0;
    (void)hoisted__U32_8162;
    U64 hoisted__U64_8163 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8162); });
    (void)hoisted__U64_8163;
    return hoisted__U64_8163;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8206 = 12;
    (void)hoisted__U32_8206;
    return hoisted__U32_8206;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8210 = F32_to_str(v.x);
    (void)hoisted__Str_8210;
    (void)hoisted__Str_8211;
    (void)hoisted__Str_8211;
    (void)hoisted__Str_8212;
    (void)hoisted__Str_8212;
    assert_eq__Str(hoisted__Str_8210, &hoisted__Str_8211, &hoisted__Str_8212);
    Str_delete(hoisted__Str_8210, 1);
    Str_delete(&hoisted__Str_8211, (Bool){0});
    Str_delete(&hoisted__Str_8212, (Bool){0});
    Str *hoisted__Str_8213 = F32_to_str(v.y);
    (void)hoisted__Str_8213;
    (void)hoisted__Str_8214;
    (void)hoisted__Str_8214;
    (void)hoisted__Str_8215;
    (void)hoisted__Str_8215;
    assert_eq__Str(hoisted__Str_8213, &hoisted__Str_8214, &hoisted__Str_8215);
    Str_delete(hoisted__Str_8213, 1);
    Str_delete(&hoisted__Str_8214, (Bool){0});
    Str_delete(&hoisted__Str_8215, (Bool){0});
    Str *hoisted__Str_8216 = F32_to_str(v.z);
    (void)hoisted__Str_8216;
    (void)hoisted__Str_8217;
    (void)hoisted__Str_8217;
    (void)hoisted__Str_8218;
    (void)hoisted__Str_8218;
    assert_eq__Str(hoisted__Str_8216, &hoisted__Str_8217, &hoisted__Str_8218);
    Str_delete(hoisted__Str_8216, 1);
    Str_delete(&hoisted__Str_8217, (Bool){0});
    Str_delete(&hoisted__Str_8218, (Bool){0});
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
    Bool hoisted__Bool_8223 = ((Bool)(*(I32*)(self) == *(I32*)(&(Color){.tag = Color_TAG_Red})));
    (void)hoisted__Bool_8223;
    if (hoisted__Bool_8223) {
        Bool hoisted__Bool_8220 = ((Bool)(*(I32*)(other) == *(I32*)(&(Color){.tag = Color_TAG_Red})));
        (void)hoisted__Bool_8220;
        { Bool _ret_val = hoisted__Bool_8220;
                return _ret_val; }
    }
    Bool hoisted__Bool_8224 = ((Bool)(*(I32*)(self) == *(I32*)(&(Color){.tag = Color_TAG_Green})));
    (void)hoisted__Bool_8224;
    if (hoisted__Bool_8224) {
        Bool hoisted__Bool_8221 = ((Bool)(*(I32*)(other) == *(I32*)(&(Color){.tag = Color_TAG_Green})));
        (void)hoisted__Bool_8221;
        { Bool _ret_val = hoisted__Bool_8221;
                return _ret_val; }
    }
    Bool hoisted__Bool_8225 = ((Bool)(*(I32*)(self) == *(I32*)(&(Color){.tag = Color_TAG_Blue})));
    (void)hoisted__Bool_8225;
    if (hoisted__Bool_8225) {
        Bool hoisted__Bool_8222 = ((Bool)(*(I32*)(other) == *(I32*)(&(Color){.tag = Color_TAG_Blue})));
        (void)hoisted__Bool_8222;
        { Bool _ret_val = hoisted__Bool_8222;
                return _ret_val; }
    }
    Bool hoisted__Bool_8226 = 0;
    (void)hoisted__Bool_8226;
    return hoisted__Bool_8226;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8234 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8234;
    if (hoisted__Bool_8234) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8235 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8235;
    if (hoisted__Bool_8235) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8236 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8236;
    if (hoisted__Bool_8236) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8237 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8237;
    UNREACHABLE(&hoisted__Str_8237);
    Str_delete(&hoisted__Str_8237, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8238 = 4;
    (void)hoisted__U32_8238;
    return hoisted__U32_8238;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8239 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8239;
    (void)hoisted__Str_8240;
    (void)hoisted__Str_8240;
    assert(hoisted__Bool_8239, &hoisted__Str_8240);
    Str_delete(&hoisted__Str_8240, (Bool){0});
    Bool hoisted__Bool_8241 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8241;
    Bool hoisted__Bool_8242 = not(hoisted__Bool_8241);
    (void)hoisted__Bool_8242;
    (void)hoisted__Str_8243;
    (void)hoisted__Str_8243;
    assert(hoisted__Bool_8242, &hoisted__Str_8243);
    Str_delete(&hoisted__Str_8243, (Bool){0});
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
    Bool hoisted__Bool_8244 = ((Bool)(*(I32*)(self) == *(I32*)(other)));
    (void)hoisted__Bool_8244;
    return hoisted__Bool_8244;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8262 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Num})));
    (void)hoisted__Bool_8262;
    if (hoisted__Bool_8262) {
        I64 *hoisted__I64_8258 = get_payload(self);
        (void)hoisted__I64_8258;
        (void)hoisted__I64_8258;
        Bool hoisted__Bool_8259 = 0;
        (void)hoisted__Bool_8259;
        I64_delete(hoisted__I64_8258, hoisted__Bool_8259);
    }
    Bool hoisted__Bool_8263 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Name})));
    (void)hoisted__Bool_8263;
    if (hoisted__Bool_8263) {
        Str *hoisted__Str_8260 = get_payload(self);
        (void)hoisted__Str_8260;
        (void)hoisted__Str_8260;
        Bool hoisted__Bool_8261 = 0;
        (void)hoisted__Bool_8261;
        Str_delete(hoisted__Str_8260, hoisted__Bool_8261);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8294 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Num})));
    (void)hoisted__Bool_8294;
    if (hoisted__Bool_8294) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8291 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8291;
        { Token * _ret_val = hoisted__Token_8291;
                return _ret_val; }
    }
    Bool hoisted__Bool_8295 = ((Bool)(*(I32*)(self) == *(I32*)(&(Token){.tag = Token_TAG_Name})));
    (void)hoisted__Bool_8295;
    if (hoisted__Bool_8295) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8292 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8292;
        Token *hoisted__Token_8293 = Token_Name(hoisted__Str_8292);
        (void)hoisted__Token_8293;
        { Token * _ret_val = hoisted__Token_8293;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8296 = 24;
    (void)hoisted__U32_8296;
    return hoisted__U32_8296;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8298 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8298;
    (void)hoisted__Str_8299;
    (void)hoisted__Str_8299;
    assert(hoisted__Bool_8298, &hoisted__Str_8299);
    Str_delete(&hoisted__Str_8299, (Bool){0});
    Bool hoisted__Bool_8300 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8300;
    Bool hoisted__Bool_8301 = not(hoisted__Bool_8300);
    (void)hoisted__Bool_8301;
    (void)hoisted__Str_8302;
    (void)hoisted__Str_8302;
    assert(hoisted__Bool_8301, &hoisted__Str_8302);
    Str_delete(&hoisted__Str_8302, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8303 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8303;
    (void)hoisted__Str_8304;
    (void)hoisted__Str_8304;
    assert(hoisted__Bool_8303, &hoisted__Str_8304);
    Str_delete(&hoisted__Str_8304, (Bool){0});
    Bool hoisted__Bool_8305 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8305;
    Bool hoisted__Bool_8306 = not(hoisted__Bool_8305);
    (void)hoisted__Bool_8306;
    (void)hoisted__Str_8307;
    (void)hoisted__Str_8307;
    assert(hoisted__Bool_8306, &hoisted__Str_8307);
    Str_delete(&hoisted__Str_8307, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8310 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8310;
    (void)hoisted__Str_8311;
    (void)hoisted__Str_8311;
    assert(hoisted__Bool_8310, &hoisted__Str_8311);
    Str_delete(&hoisted__Str_8311, (Bool){0});
    Bool hoisted__Bool_8312 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8312;
    Bool hoisted__Bool_8313 = not(hoisted__Bool_8312);
    (void)hoisted__Bool_8313;
    (void)hoisted__Str_8314;
    (void)hoisted__Str_8314;
    assert(hoisted__Bool_8313, &hoisted__Str_8314);
    Str_delete(&hoisted__Str_8314, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8446 = ((Bool)(a != b));
    (void)hoisted__Bool_8446;
    if (hoisted__Bool_8446) {
        U32 hoisted__U32_8430 = 5;
        (void)hoisted__U32_8430;
        Array__Str *_va_Array_249 = Array__Str_new(hoisted__U32_8430);
        (void)_va_Array_249;
        I64 _va_Array_249_ek = 0;
        (void)_va_Array_249_ek;
        OutOfBounds *_va_Array_249_eo = malloc(sizeof(OutOfBounds));
        _va_Array_249_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_249_eo;
        U32 hoisted__U32_8431 = 0;
        (void)hoisted__U32_8431;
        (void)hoisted__Str_8432;
        (void)hoisted__Str_8432;
        (void)hoisted__Str_8433;
        (void)hoisted__Str_8433;
        Array__Str_set(_va_Array_249, hoisted__U32_8431, &hoisted__Str_8432, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8433);
        Str_delete(&hoisted__Str_8433, (Bool){0});
        U32 hoisted__U32_8434 = 1;
        (void)hoisted__U32_8434;
        Str *hoisted__Str_8435 = I64_to_str(a);
        (void)hoisted__Str_8435;
        (void)hoisted__Str_8436;
        (void)hoisted__Str_8436;
        Array__Str_set(_va_Array_249, hoisted__U32_8434, hoisted__Str_8435, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8436);
        Str_delete(&hoisted__Str_8436, (Bool){0});
        U32 hoisted__U32_8437 = 2;
        (void)hoisted__U32_8437;
        (void)hoisted__Str_8438;
        (void)hoisted__Str_8438;
        (void)hoisted__Str_8439;
        (void)hoisted__Str_8439;
        Array__Str_set(_va_Array_249, hoisted__U32_8437, &hoisted__Str_8438, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8439);
        Str_delete(&hoisted__Str_8439, (Bool){0});
        U32 hoisted__U32_8440 = 3;
        (void)hoisted__U32_8440;
        Str *hoisted__Str_8441 = I64_to_str(b);
        (void)hoisted__Str_8441;
        (void)hoisted__Str_8442;
        (void)hoisted__Str_8442;
        Array__Str_set(_va_Array_249, hoisted__U32_8440, hoisted__Str_8441, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8442);
        Str_delete(&hoisted__Str_8442, (Bool){0});
        U32 hoisted__U32_8443 = 4;
        (void)hoisted__U32_8443;
        (void)hoisted__Str_8444;
        (void)hoisted__Str_8444;
        (void)hoisted__Str_8445;
        (void)hoisted__Str_8445;
        Array__Str_set(_va_Array_249, hoisted__U32_8443, &hoisted__Str_8444, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8445);
        OutOfBounds_delete(_va_Array_249_eo, 1);
        Str_delete(&hoisted__Str_8445, (Bool){0});
        panic(_va_Array_249, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8463 = Str_neq(a, b);
    (void)hoisted__Bool_8463;
    if (hoisted__Bool_8463) {
        U32 hoisted__U32_8447 = 5;
        (void)hoisted__U32_8447;
        Array__Str *_va_Array_250 = Array__Str_new(hoisted__U32_8447);
        (void)_va_Array_250;
        I64 _va_Array_250_ek = 0;
        (void)_va_Array_250_ek;
        OutOfBounds *_va_Array_250_eo = malloc(sizeof(OutOfBounds));
        _va_Array_250_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_250_eo;
        U32 hoisted__U32_8448 = 0;
        (void)hoisted__U32_8448;
        (void)hoisted__Str_8449;
        (void)hoisted__Str_8449;
        (void)hoisted__Str_8450;
        (void)hoisted__Str_8450;
        Array__Str_set(_va_Array_250, hoisted__U32_8448, &hoisted__Str_8449, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8450);
        Str_delete(&hoisted__Str_8450, (Bool){0});
        U32 hoisted__U32_8451 = 1;
        (void)hoisted__U32_8451;
        Str *hoisted__Str_8452 = Str_to_str(a);
        (void)hoisted__Str_8452;
        (void)hoisted__Str_8453;
        (void)hoisted__Str_8453;
        Array__Str_set(_va_Array_250, hoisted__U32_8451, hoisted__Str_8452, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8453);
        Str_delete(&hoisted__Str_8453, (Bool){0});
        U32 hoisted__U32_8454 = 2;
        (void)hoisted__U32_8454;
        (void)hoisted__Str_8455;
        (void)hoisted__Str_8455;
        (void)hoisted__Str_8456;
        (void)hoisted__Str_8456;
        Array__Str_set(_va_Array_250, hoisted__U32_8454, &hoisted__Str_8455, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8456);
        Str_delete(&hoisted__Str_8456, (Bool){0});
        U32 hoisted__U32_8457 = 3;
        (void)hoisted__U32_8457;
        Str *hoisted__Str_8458 = Str_to_str(b);
        (void)hoisted__Str_8458;
        (void)hoisted__Str_8459;
        (void)hoisted__Str_8459;
        Array__Str_set(_va_Array_250, hoisted__U32_8457, hoisted__Str_8458, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8459);
        Str_delete(&hoisted__Str_8459, (Bool){0});
        U32 hoisted__U32_8460 = 4;
        (void)hoisted__U32_8460;
        (void)hoisted__Str_8461;
        (void)hoisted__Str_8461;
        (void)hoisted__Str_8462;
        (void)hoisted__Str_8462;
        Array__Str_set(_va_Array_250, hoisted__U32_8460, &hoisted__Str_8461, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8462);
        OutOfBounds_delete(_va_Array_250_eo, 1);
        Str_delete(&hoisted__Str_8462, (Bool){0});
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
        if (*index == 6LL) return &_til_str_lit_88;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_90;
        if (*index == 2LL) return &_til_str_lit_91;
        if (*index == 3LL) return &_til_str_lit_74;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_90;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_42;
        if (*index == 1LL) return &_til_str_lit_45;
        if (*index == 2LL) return &_til_str_lit_51;
        if (*index == 3LL) return &_til_str_lit_92;
        if (*index == 4LL) return &_til_str_lit_93;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_51;
        if (*index == 1LL) return &_til_str_lit_99;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_68;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_134;
        if (*index == 1LL) return &_til_str_lit_136;
        if (*index == 2LL) return &_til_str_lit_138;
        if (*index == 3LL) return &_til_str_lit_139;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_140;
        if (*index == 1LL) return &_til_str_lit_141;
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
        if (*index == 0LL) return &_til_str_lit_148;
        if (*index == 1LL) return &_til_str_lit_149;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_174;
        if (*index == 1LL) return &_til_str_lit_175;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_180;
        if (*index == 1LL) return &_til_str_lit_182;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_174;
        if (*index == 1LL) return &_til_str_lit_175;
        if (*index == 2LL) return &_til_str_lit_187;
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
        if (*index == 6LL) return &_til_str_lit_89;
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
        if (*index == 0LL) return &_til_str_lit_135;
        if (*index == 1LL) return &_til_str_lit_137;
        if (*index == 2LL) return &_til_str_lit_3;
        if (*index == 3LL) return &_til_str_lit_3;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_89;
        if (*index == 1LL) return &_til_str_lit_62;
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
        if (*index == 0LL) return &_til_str_lit_181;
        if (*index == 1LL) return &_til_str_lit_181;
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
        if (*index == 1LL) return &_til_str_lit_94;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_96;
        if (*index == 4LL) return &_til_str_lit_97;
        if (*index == 5LL) return &_til_str_lit_98;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_100;
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
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_194;
        if (*index == 1LL) return &_til_str_lit_195;
        if (*index == 2LL) return &_til_str_lit_196;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_94;
        if (*index == 1LL) return &_til_str_lit_199;
        if (*index == 2LL) return &_til_str_lit_200;
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
        if (*index == 1LL) return &_til_str_lit_95;
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
