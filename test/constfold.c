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

static Str hoisted__Str_7097 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7099 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7100 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7104 = (Str){.c_str = (void *)"./src/core/exit.til:18:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7116 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7117 = (Str){.c_str = (void *)"./src/core/exit.til:27:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7120 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7121 = (Str){.c_str = (void *)"./src/core/exit.til:35:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7328 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7336 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7344 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7347 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7348 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7376 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7377 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7381 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7382 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7405 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7406 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7417 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7418 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_7431 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8030 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8031 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8034 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8038 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8042 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8047 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8048 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8049 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8052 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8053 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8054 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8094 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8096 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8100 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8102 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8143 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8145 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8147 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8149 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8201 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8202 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8204 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8205 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8207 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8208 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8230 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8233 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8289 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8292 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8294 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8297 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8301 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8304 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8422 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8423 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8426 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8428 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8429 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8432 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8434 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8435 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8439 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8440 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8443 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8445 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8446 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8449 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8451 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_8452 = (Str){.c_str = (void *)"test/constfold.til:47:9", .count = 23ULL, .cap = TIL_CAP_LIT};

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
    U64 hoisted__U64_22 = 1ULL;
    (void)hoisted__U64_22;
    U64 hoisted__U64_23 = ((U64)(DEREF(self) + hoisted__U64_22));
    (void)hoisted__U64_23;
    *self = hoisted__U64_23;
}

void U64_dec(U64 * self) {
    U64 hoisted__U64_24 = 1ULL;
    (void)hoisted__U64_24;
    U64 hoisted__U64_25 = ((U64)(DEREF(self) - hoisted__U64_24));
    (void)hoisted__U64_25;
    *self = hoisted__U64_25;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_30 = 8;
    (void)hoisted__U32_30;
    return hoisted__U32_30;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_115 = 0;
    (void)hoisted__U32_115;
    U64 hoisted__U64_116 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_115); });
    (void)hoisted__U64_116;
    return hoisted__U64_116;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_117 = U32_to_i64(val);
    (void)hoisted__I64_117;
    Str *hoisted__Str_118 = I64_to_str(hoisted__I64_117);
    (void)hoisted__Str_118;
    return hoisted__Str_118;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_119 = 1;
    (void)hoisted__U32_119;
    U32 hoisted__U32_120 = ((U32)(DEREF(self) + hoisted__U32_119));
    (void)hoisted__U32_120;
    *self = hoisted__U32_120;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_121 = 1;
    (void)hoisted__U32_121;
    U32 hoisted__U32_122 = ((U32)(DEREF(self) - hoisted__U32_121));
    (void)hoisted__U32_122;
    *self = hoisted__U32_122;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_129 = 4;
    (void)hoisted__U32_129;
    return hoisted__U32_129;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_214 = 0;
    (void)hoisted__U32_214;
    U64 hoisted__U64_215 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_214); });
    (void)hoisted__U64_215;
    return hoisted__U64_215;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_236 = 4;
    (void)hoisted__U32_236;
    return hoisted__U32_236;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_378 = 0;
    (void)hoisted__U32_378;
    U64 hoisted__U64_379 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_378); });
    (void)hoisted__U64_379;
    return hoisted__U64_379;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_400 = 1;
    (void)hoisted__U32_400;
    return hoisted__U32_400;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_401 = 0;
    (void)hoisted__U32_401;
    U64 hoisted__U64_402 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_401); });
    (void)hoisted__U64_402;
    return hoisted__U64_402;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_415 = 1;
    (void)hoisted__U32_415;
    return hoisted__U32_415;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_500 = 0;
    (void)hoisted__U32_500;
    U64 hoisted__U64_501 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_500); });
    (void)hoisted__U64_501;
    return hoisted__U64_501;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_617 = parts;
        (void)_fc_Array__Str_617;
        (void)_fc_Array__Str_617;
        U32 _fi_USize_617 = 0;
        (void)_fi_USize_617;
        while (1) {
            U32 hoisted__U32_619 = Array__Str_len(_fc_Array__Str_617);
            (void)hoisted__U32_619;
            Bool _wcond_Bool_618 = ((Bool)(_fi_USize_617 < hoisted__U32_619));
            (void)_wcond_Bool_618;
            if (_wcond_Bool_618) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_617, &_fi_USize_617);
            U32 hoisted__U32_620 = 1;
            (void)hoisted__U32_620;
            U32 hoisted__U32_621 = ((U32)(_fi_USize_617 + hoisted__U32_620));
            (void)hoisted__U32_621;
            _fi_USize_617 = hoisted__U32_621;
            U32 hoisted__U32_622 = Str_len(s);
            (void)hoisted__U32_622;
            U32 hoisted__U32_623 = ((U32)(total + hoisted__U32_622));
            (void)hoisted__U32_623;
            total = hoisted__U32_623;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_624 = parts;
        (void)_fc_Array__Str_624;
        (void)_fc_Array__Str_624;
        U32 _fi_USize_624 = 0;
        (void)_fi_USize_624;
        while (1) {
            U32 hoisted__U32_626 = Array__Str_len(_fc_Array__Str_624);
            (void)hoisted__U32_626;
            Bool _wcond_Bool_625 = ((Bool)(_fi_USize_624 < hoisted__U32_626));
            (void)_wcond_Bool_625;
            if (_wcond_Bool_625) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_624, &_fi_USize_624);
            U32 hoisted__U32_627 = 1;
            (void)hoisted__U32_627;
            U32 hoisted__U32_628 = ((U32)(_fi_USize_624 + hoisted__U32_627));
            (void)hoisted__U32_628;
            _fi_USize_624 = hoisted__U32_628;
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
    Bool hoisted__Bool_644 = ((Bool)(b->count < a->count));
    (void)hoisted__Bool_644;
    if (hoisted__Bool_644) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_645 = 0;
    (void)hoisted__I32_645;
    Bool hoisted__Bool_646 = ((Bool)(c < hoisted__I32_645));
    (void)hoisted__Bool_646;
    if (hoisted__Bool_646) {
        I64 hoisted__I64_642 = -1;
        (void)hoisted__I64_642;
        { I64 _ret_val = hoisted__I64_642;
                        return _ret_val; }
    }
    I32 hoisted__I32_647 = 0;
    (void)hoisted__I32_647;
    Bool hoisted__Bool_648 = ((Bool)(c > hoisted__I32_647));
    (void)hoisted__Bool_648;
    if (hoisted__Bool_648) {
        I64 hoisted__I64_643 = 1;
        (void)hoisted__I64_643;
        { I64 _ret_val = hoisted__I64_643;
                        return _ret_val; }
    }
    I64 hoisted__I64_649 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_649;
    return hoisted__I64_649;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_650 = 1;
    (void)hoisted__U32_650;
    U32 hoisted__U64_651 = ((U64)(n + hoisted__U32_650));
    (void)hoisted__U64_651;
    void * buf = malloc(hoisted__U64_651);
    I32 hoisted__I32_652 = 0;
    (void)hoisted__I32_652;
    U64 hoisted__U64_653 = 1ULL;
    (void)hoisted__U64_653;
    memset(buf, hoisted__I32_652, hoisted__U64_653);
    I64 hoisted__I64_654 = 0;
    (void)hoisted__I64_654;
    Str *hoisted__Str_655 = malloc(sizeof(Str));
    hoisted__Str_655->c_str = buf;
    hoisted__Str_655->count = hoisted__I64_654;
    hoisted__Str_655->cap = n;
    (void)hoisted__Str_655;
    return hoisted__Str_655;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_668 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_668;
    if (hoisted__Bool_668) {
        U32 hoisted__U32_658 = 1;
        (void)hoisted__U32_658;
        Array__Str *_va_Array_18 = Array__Str_new(hoisted__U32_658);
        (void)_va_Array_18;
        I64 _va_Array_18_ek = 0;
        (void)_va_Array_18_ek;
        OutOfBounds *_va_Array_18_eo = malloc(sizeof(OutOfBounds));
        _va_Array_18_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_18_eo;
        U32 hoisted__U32_659 = 0;
        (void)hoisted__U32_659;
        static Str hoisted__Str_660 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_660;
        static Str hoisted__Str_661 = (Str){.c_str = (void *)"./src/core/str.til:104:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_661;
        Array__Str_set(_va_Array_18, hoisted__U32_659, &hoisted__Str_660, &_va_Array_18_ek, _va_Array_18_eo, &hoisted__Str_661);
        OutOfBounds_delete(_va_Array_18_eo, 1);
        Str_delete(&hoisted__Str_661, (Bool){0});
        static Str hoisted__Str_662 = (Str){.c_str = (void *)"./src/core/str.til:104:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_662;
        panic(_va_Array_18, &hoisted__Str_662);
        Str_delete(&hoisted__Str_662, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_669 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_669;
    if (hoisted__Bool_669) {
        U32 hoisted__U32_663 = 1;
        (void)hoisted__U32_663;
        Array__Str *_va_Array_19 = Array__Str_new(hoisted__U32_663);
        (void)_va_Array_19;
        I64 _va_Array_19_ek = 0;
        (void)_va_Array_19_ek;
        OutOfBounds *_va_Array_19_eo = malloc(sizeof(OutOfBounds));
        _va_Array_19_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_19_eo;
        U32 hoisted__U32_664 = 0;
        (void)hoisted__U32_664;
        static Str hoisted__Str_665 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_665;
        static Str hoisted__Str_666 = (Str){.c_str = (void *)"./src/core/str.til:108:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_666;
        Array__Str_set(_va_Array_19, hoisted__U32_664, &hoisted__Str_665, &_va_Array_19_ek, _va_Array_19_eo, &hoisted__Str_666);
        OutOfBounds_delete(_va_Array_19_eo, 1);
        Str_delete(&hoisted__Str_666, (Bool){0});
        static Str hoisted__Str_667 = (Str){.c_str = (void *)"./src/core/str.til:108:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_667;
        panic(_va_Array_19, &hoisted__Str_667);
        Str_delete(&hoisted__Str_667, (Bool){0});
    }
    void *hoisted__v_670 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_670;
    (void)hoisted__v_670;
    memcpy(hoisted__v_670, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_671 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_671;
    (void)hoisted__v_671;
    I32 hoisted__I32_672 = 0;
    (void)hoisted__I32_672;
    U64 hoisted__U64_673 = 1ULL;
    (void)hoisted__U64_673;
    memset(hoisted__v_671, hoisted__I32_672, hoisted__U64_673);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_674 = 1;
    (void)hoisted__U32_674;
    U32 hoisted__U64_675 = ((U64)(val->count + hoisted__U32_674));
    (void)hoisted__U64_675;
    void * new_data = malloc(hoisted__U64_675);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_676 = ptr_add(new_data, val->count);
    (void)hoisted__v_676;
    (void)hoisted__v_676;
    I32 hoisted__I32_677 = 0;
    (void)hoisted__I32_677;
    U64 hoisted__U64_678 = 1ULL;
    (void)hoisted__U64_678;
    memset(hoisted__v_676, hoisted__I32_677, hoisted__U64_678);
    Str *hoisted__Str_679 = malloc(sizeof(Str));
    hoisted__Str_679->c_str = new_data;
    hoisted__Str_679->count = val->count;
    hoisted__Str_679->cap = val->count;
    (void)hoisted__Str_679;
    return hoisted__Str_679;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_680 = Str_clone(self);
    (void)hoisted__Str_680;
    return hoisted__Str_680;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_681 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_681;
    if (hoisted__Bool_681) {
        free(self->c_str);
    }
    Bool hoisted__Bool_682 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_682;
    Bool hoisted__Bool_683 = and(call_free, hoisted__Bool_682);
    (void)hoisted__Bool_683;
    if (hoisted__Bool_683) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_878 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_878;
    return hoisted__U64_878;
}

U32 Str_size(void) {
    U32 hoisted__U32_1062 = 16;
    (void)hoisted__U32_1062;
    return hoisted__U32_1062;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1063 = Str_cmp(a, b);
    (void)hoisted__I64_1063;
    I64 hoisted__I64_1064 = 0;
    (void)hoisted__I64_1064;
    Bool hoisted__Bool_1065 = ((Bool)(hoisted__I64_1063 == hoisted__I64_1064));
    (void)hoisted__Bool_1065;
    return hoisted__Bool_1065;
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_1074 = Str_eq(a, b);
    (void)hoisted__Bool_1074;
    Bool hoisted__Bool_1075 = not(hoisted__Bool_1074);
    (void)hoisted__Bool_1075;
    return hoisted__Bool_1075;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1166 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1166->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1166;
    return hoisted__OutOfBounds_1166;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1167 = 0;
    (void)hoisted__Bool_1167;
    Str_delete(&self->msg, hoisted__Bool_1167);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1168 = 0;
    (void)hoisted__U32_1168;
    U64 hoisted__U64_1169 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1168); });
    (void)hoisted__U64_1169;
    return hoisted__U64_1169;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1188 = 16;
    (void)hoisted__U32_1188;
    return hoisted__U32_1188;
}

Array__Str * Array__Str_new(U32 cap) {
    U32 hoisted__U32_1212 = 16;
    (void)hoisted__U32_1212;
    U64 hoisted__U64_1213 = (U64)(cap);
    (void)hoisted__U64_1213;
    U64 hoisted__U64_1214 = (U64)(hoisted__U32_1212);
    (void)hoisted__U64_1214;
    void * hoisted__v_1215 = calloc(hoisted__U64_1213, hoisted__U64_1214);
    (void)hoisted__v_1215;
    Array__Str *hoisted__Array__Str_1216 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1216->data = hoisted__v_1215;
    hoisted__Array__Str_1216->cap = cap;
    (void)hoisted__Array__Str_1216;
    return hoisted__Array__Str_1216;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_unsafe_get(Array__Str * self, U32 * i) {
    U32 hoisted__U32_1217 = 16;
    (void)hoisted__U32_1217;
    U32 hoisted__U32_1218 = ((U32)(DEREF(i) * hoisted__U32_1217));
    (void)hoisted__U32_1218;
    U64 hoisted__U64_1219 = (U64)(hoisted__U32_1218);
    (void)hoisted__U64_1219;
    void *hoisted__v_1220 = ptr_add(self->data, hoisted__U64_1219);
    (void)hoisted__v_1220;
    (void)hoisted__v_1220;
    return hoisted__v_1220;
}

void Array__Str_unsafe_set(Array__Str * self, U32 i, Str * val) {
    Str *hoisted__Str_1247 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1247;
    (void)hoisted__Str_1247;
    Bool hoisted__Bool_1248 = 0;
    (void)hoisted__Bool_1248;
    Str_delete(hoisted__Str_1247, hoisted__Bool_1248);
    U32 hoisted__U32_1249 = 16;
    (void)hoisted__U32_1249;
    Str *hoisted__Str_1250 = Array__Str_unsafe_get(self, &i);
    (void)hoisted__Str_1250;
    (void)hoisted__Str_1250;
    U64 hoisted__U64_1251 = (U64)(hoisted__U32_1249);
    (void)hoisted__U64_1251;
    memcpy(hoisted__Str_1250, val, hoisted__U64_1251);
    U32 hoisted__U32_1252 = 16;
    (void)hoisted__U32_1252;
    I32 hoisted__I32_1253 = 0;
    (void)hoisted__I32_1253;
    U64 hoisted__U64_1254 = (U64)(hoisted__U32_1252);
    (void)hoisted__U64_1254;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_1253, hoisted__U64_1254); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, U32 i, Str * val, I64 * _err_kind, OutOfBounds * _err_OutOfBounds, Str * loc) {
    Bool hoisted__Bool_1277 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_1277;
    if (hoisted__Bool_1277) {
        U32 hoisted__U32_1255 = 6;
        (void)hoisted__U32_1255;
        Array__Str *_va_Array_31 = Array__Str_new(hoisted__U32_1255);
        (void)_va_Array_31;
        I64 _va_Array_31_ek = 0;
        (void)_va_Array_31_ek;
        OutOfBounds *_va_Array_31_eo = malloc(sizeof(OutOfBounds));
        _va_Array_31_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_31_eo;
        U32 hoisted__U32_1256 = 0;
        (void)hoisted__U32_1256;
        Str *hoisted__Str_1257 = Str_clone(loc);
        (void)hoisted__Str_1257;
        static Str hoisted__Str_1258 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1258;
        Array__Str_set(_va_Array_31, hoisted__U32_1256, hoisted__Str_1257, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1258);
        Str_delete(&hoisted__Str_1258, (Bool){0});
        U32 hoisted__U32_1259 = 1;
        (void)hoisted__U32_1259;
        static Str hoisted__Str_1260 = (Str){.c_str = (void *)":Array.set: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1260;
        static Str hoisted__Str_1261 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1261;
        Array__Str_set(_va_Array_31, hoisted__U32_1259, &hoisted__Str_1260, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1261);
        Str_delete(&hoisted__Str_1261, (Bool){0});
        U32 hoisted__U32_1262 = 2;
        (void)hoisted__U32_1262;
        Str *hoisted__Str_1263 = U32_to_str(i);
        (void)hoisted__Str_1263;
        static Str hoisted__Str_1264 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1264;
        Array__Str_set(_va_Array_31, hoisted__U32_1262, hoisted__Str_1263, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1264);
        Str_delete(&hoisted__Str_1264, (Bool){0});
        U32 hoisted__U32_1265 = 3;
        (void)hoisted__U32_1265;
        static Str hoisted__Str_1266 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1266;
        static Str hoisted__Str_1267 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1267;
        Array__Str_set(_va_Array_31, hoisted__U32_1265, &hoisted__Str_1266, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1267);
        Str_delete(&hoisted__Str_1267, (Bool){0});
        U32 hoisted__U32_1268 = 4;
        (void)hoisted__U32_1268;
        Str *hoisted__Str_1269 = U32_to_str(self->cap);
        (void)hoisted__Str_1269;
        static Str hoisted__Str_1270 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1270;
        Array__Str_set(_va_Array_31, hoisted__U32_1268, hoisted__Str_1269, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1270);
        Str_delete(&hoisted__Str_1270, (Bool){0});
        U32 hoisted__U32_1271 = 5;
        (void)hoisted__U32_1271;
        static Str hoisted__Str_1272 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1272;
        static Str hoisted__Str_1273 = (Str){.c_str = (void *)"./src/core/str.til:57:37", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1273;
        Array__Str_set(_va_Array_31, hoisted__U32_1271, &hoisted__Str_1272, &_va_Array_31_ek, _va_Array_31_eo, &hoisted__Str_1273);
        OutOfBounds_delete(_va_Array_31_eo, 1);
        Str_delete(&hoisted__Str_1273, (Bool){0});
        OutOfBounds *hoisted__OutOfBounds_1274 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_31); hoisted__OutOfBounds_1274->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1274;
        U32 hoisted__U32_1275 = 16;
        (void)hoisted__U32_1275;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1274, hoisted__U32_1275);
        OutOfBounds_delete(hoisted__OutOfBounds_1274, 1);
        I64 hoisted__I64_1276 = 3;
        (void)hoisted__I64_1276;
        *_err_kind = hoisted__I64_1276;
    }
    I64 hoisted__I64_1278 = 0;
    (void)hoisted__I64_1278;
    Bool hoisted__Bool_1279 = ((Bool)(DEREF(_err_kind) == hoisted__I64_1278));
    (void)hoisted__Bool_1279;
    if (hoisted__Bool_1279) {
        Array__Str_unsafe_set(self, i, val);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1280 = self->cap;
        (void)_re_U32_1280;
        U32 _rc_U32_1280 = 0;
        (void)_rc_U32_1280;
        Bool hoisted__Bool_1293 = ((Bool)(_rc_U32_1280 <= _re_U32_1280));
        (void)hoisted__Bool_1293;
        if (hoisted__Bool_1293) {
            while (1) {
                Bool _wcond_Bool_1281 = ((Bool)(_rc_U32_1280 < _re_U32_1280));
                (void)_wcond_Bool_1281;
                if (_wcond_Bool_1281) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1280);
                U32_inc(&_rc_U32_1280);
                U32 hoisted__U32_1282 = 16;
                (void)hoisted__U32_1282;
                U32 hoisted__U32_1283 = ((U32)(i * hoisted__U32_1282));
                (void)hoisted__U32_1283;
                U64 hoisted__U64_1284 = (U64)(hoisted__U32_1283);
                (void)hoisted__U64_1284;
                Str *hoisted__Str_1285 = ptr_add(self->data, hoisted__U64_1284);
                (void)hoisted__Str_1285;
                (void)hoisted__Str_1285;
                Bool hoisted__Bool_1286 = 0;
                (void)hoisted__Bool_1286;
                Str_delete(hoisted__Str_1285, hoisted__Bool_1286);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1287 = ((Bool)(_rc_U32_1280 > _re_U32_1280));
                (void)_wcond_Bool_1287;
                if (_wcond_Bool_1287) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1280);
                U32_dec(&_rc_U32_1280);
                U32 hoisted__U32_1288 = 16;
                (void)hoisted__U32_1288;
                U32 hoisted__U32_1289 = ((U32)(i * hoisted__U32_1288));
                (void)hoisted__U32_1289;
                U64 hoisted__U64_1290 = (U64)(hoisted__U32_1289);
                (void)hoisted__U64_1290;
                Str *hoisted__Str_1291 = ptr_add(self->data, hoisted__U64_1290);
                (void)hoisted__Str_1291;
                (void)hoisted__Str_1291;
                Bool hoisted__Bool_1292 = 0;
                (void)hoisted__Bool_1292;
                Str_delete(hoisted__Str_1291, hoisted__Bool_1292);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1322 = 16;
    (void)hoisted__U32_1322;
    U32 hoisted__U32_1323 = ((U32)(self->cap * hoisted__U32_1322));
    (void)hoisted__U32_1323;
    U64 hoisted__U64_1324 = (U64)(hoisted__U32_1323);
    (void)hoisted__U64_1324;
    void * new_data = malloc(hoisted__U64_1324);
    {
        U32 _re_U32_1294 = self->cap;
        (void)_re_U32_1294;
        U32 _rc_U32_1294 = 0;
        (void)_rc_U32_1294;
        Bool hoisted__Bool_1321 = ((Bool)(_rc_U32_1294 <= _re_U32_1294));
        (void)hoisted__Bool_1321;
        if (hoisted__Bool_1321) {
            while (1) {
                Bool _wcond_Bool_1295 = ((Bool)(_rc_U32_1294 < _re_U32_1294));
                (void)_wcond_Bool_1295;
                if (_wcond_Bool_1295) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1294);
                U32_inc(&_rc_U32_1294);
                U32 hoisted__U32_1296 = 16;
                (void)hoisted__U32_1296;
                U32 hoisted__U32_1297 = ((U32)(i * hoisted__U32_1296));
                (void)hoisted__U32_1297;
                U64 hoisted__U64_1298 = (U64)(hoisted__U32_1297);
                (void)hoisted__U64_1298;
                Str *src = ptr_add(self->data, hoisted__U64_1298);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1299 = 16;
                (void)hoisted__U32_1299;
                U32 hoisted__U32_1300 = ((U32)(i * hoisted__U32_1299));
                (void)hoisted__U32_1300;
                U64 hoisted__U64_1301 = (U64)(hoisted__U32_1300);
                (void)hoisted__U64_1301;
                U32 hoisted__U32_1302 = 16;
                (void)hoisted__U32_1302;
                void *hoisted__v_1303 = ptr_add(new_data, hoisted__U64_1301);
                (void)hoisted__v_1303;
                (void)hoisted__v_1303;
                U64 hoisted__U64_1304 = (U64)(hoisted__U32_1302);
                (void)hoisted__U64_1304;
                memcpy(hoisted__v_1303, cloned, hoisted__U64_1304);
                U32 hoisted__U32_1305 = 16;
                (void)hoisted__U32_1305;
                I32 hoisted__I32_1306 = 0;
                (void)hoisted__I32_1306;
                U64 hoisted__U64_1307 = (U64)(hoisted__U32_1305);
                (void)hoisted__U64_1307;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1306, hoisted__U64_1307); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1308 = ((Bool)(_rc_U32_1294 > _re_U32_1294));
                (void)_wcond_Bool_1308;
                if (_wcond_Bool_1308) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1294);
                U32_dec(&_rc_U32_1294);
                U32 hoisted__U32_1309 = 16;
                (void)hoisted__U32_1309;
                U32 hoisted__U32_1310 = ((U32)(i * hoisted__U32_1309));
                (void)hoisted__U32_1310;
                U64 hoisted__U64_1311 = (U64)(hoisted__U32_1310);
                (void)hoisted__U64_1311;
                Str *src = ptr_add(self->data, hoisted__U64_1311);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1312 = 16;
                (void)hoisted__U32_1312;
                U32 hoisted__U32_1313 = ((U32)(i * hoisted__U32_1312));
                (void)hoisted__U32_1313;
                U64 hoisted__U64_1314 = (U64)(hoisted__U32_1313);
                (void)hoisted__U64_1314;
                U32 hoisted__U32_1315 = 16;
                (void)hoisted__U32_1315;
                void *hoisted__v_1316 = ptr_add(new_data, hoisted__U64_1314);
                (void)hoisted__v_1316;
                (void)hoisted__v_1316;
                U64 hoisted__U64_1317 = (U64)(hoisted__U32_1315);
                (void)hoisted__U64_1317;
                memcpy(hoisted__v_1316, cloned, hoisted__U64_1317);
                U32 hoisted__U32_1318 = 16;
                (void)hoisted__U32_1318;
                I32 hoisted__I32_1319 = 0;
                (void)hoisted__I32_1319;
                U64 hoisted__U64_1320 = (U64)(hoisted__U32_1318);
                (void)hoisted__U64_1320;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1319, hoisted__U64_1320); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1325 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1325->data = new_data;
    hoisted__Array__Str_1325->cap = self->cap;
    (void)hoisted__Array__Str_1325;
    return hoisted__Array__Str_1325;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1326 = 16;
    (void)hoisted__U32_1326;
    return hoisted__U32_1326;
}

Vec__Str * Vec__Str_new(void) {
    U32 hoisted__U32_1327 = 16;
    (void)hoisted__U32_1327;
    U64 hoisted__U64_1328 = (U64)(hoisted__U32_1327);
    (void)hoisted__U64_1328;
    void * hoisted__v_1329 = malloc(hoisted__U64_1328);
    (void)hoisted__v_1329;
    U32 hoisted__U32_1330 = 0;
    (void)hoisted__U32_1330;
    I64 hoisted__I64_1331 = 1;
    (void)hoisted__I64_1331;
    Vec__Str *hoisted__Vec__Str_1332 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1332->data = hoisted__v_1329;
    hoisted__Vec__Str_1332->count = hoisted__U32_1330;
    hoisted__Vec__Str_1332->cap = hoisted__I64_1331;
    (void)hoisted__Vec__Str_1332;
    return hoisted__Vec__Str_1332;
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_1342 = self->count;
        (void)_re_U32_1342;
        U32 _rc_U32_1342 = 0;
        (void)_rc_U32_1342;
        Bool hoisted__Bool_1355 = ((Bool)(_rc_U32_1342 <= _re_U32_1342));
        (void)hoisted__Bool_1355;
        if (hoisted__Bool_1355) {
            while (1) {
                Bool _wcond_Bool_1343 = ((Bool)(_rc_U32_1342 < _re_U32_1342));
                (void)_wcond_Bool_1343;
                if (_wcond_Bool_1343) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1342);
                U32_inc(&_rc_U32_1342);
                U32 hoisted__U32_1344 = 16;
                (void)hoisted__U32_1344;
                U32 hoisted__U32_1345 = ((U32)(i * hoisted__U32_1344));
                (void)hoisted__U32_1345;
                U64 hoisted__U64_1346 = (U64)(hoisted__U32_1345);
                (void)hoisted__U64_1346;
                Str *hoisted__Str_1347 = ptr_add(self->data, hoisted__U64_1346);
                (void)hoisted__Str_1347;
                (void)hoisted__Str_1347;
                Bool hoisted__Bool_1348 = 0;
                (void)hoisted__Bool_1348;
                Str_delete(hoisted__Str_1347, hoisted__Bool_1348);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1349 = ((Bool)(_rc_U32_1342 > _re_U32_1342));
                (void)_wcond_Bool_1349;
                if (_wcond_Bool_1349) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1342);
                U32_dec(&_rc_U32_1342);
                U32 hoisted__U32_1350 = 16;
                (void)hoisted__U32_1350;
                U32 hoisted__U32_1351 = ((U32)(i * hoisted__U32_1350));
                (void)hoisted__U32_1351;
                U64 hoisted__U64_1352 = (U64)(hoisted__U32_1351);
                (void)hoisted__U64_1352;
                Str *hoisted__Str_1353 = ptr_add(self->data, hoisted__U64_1352);
                (void)hoisted__Str_1353;
                (void)hoisted__Str_1353;
                Bool hoisted__Bool_1354 = 0;
                (void)hoisted__Bool_1354;
                Str_delete(hoisted__Str_1353, hoisted__Bool_1354);
            }
        }
    }
    U32 hoisted__U32_1356 = 0;
    (void)hoisted__U32_1356;
    self->count = hoisted__U32_1356;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_1626 = 16;
    (void)hoisted__U32_1626;
    U32 hoisted__U32_1627 = ((U32)(self->cap * hoisted__U32_1626));
    (void)hoisted__U32_1627;
    U64 hoisted__U64_1628 = (U64)(hoisted__U32_1627);
    (void)hoisted__U64_1628;
    void * new_data = malloc(hoisted__U64_1628);
    {
        U32 _re_U32_1598 = self->count;
        (void)_re_U32_1598;
        U32 _rc_U32_1598 = 0;
        (void)_rc_U32_1598;
        Bool hoisted__Bool_1625 = ((Bool)(_rc_U32_1598 <= _re_U32_1598));
        (void)hoisted__Bool_1625;
        if (hoisted__Bool_1625) {
            while (1) {
                Bool _wcond_Bool_1599 = ((Bool)(_rc_U32_1598 < _re_U32_1598));
                (void)_wcond_Bool_1599;
                if (_wcond_Bool_1599) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1598);
                U32_inc(&_rc_U32_1598);
                U32 hoisted__U32_1600 = 16;
                (void)hoisted__U32_1600;
                U32 hoisted__U32_1601 = ((U32)(i * hoisted__U32_1600));
                (void)hoisted__U32_1601;
                U64 hoisted__U64_1602 = (U64)(hoisted__U32_1601);
                (void)hoisted__U64_1602;
                Str *src = ptr_add(self->data, hoisted__U64_1602);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1603 = 16;
                (void)hoisted__U32_1603;
                U32 hoisted__U32_1604 = ((U32)(i * hoisted__U32_1603));
                (void)hoisted__U32_1604;
                U64 hoisted__U64_1605 = (U64)(hoisted__U32_1604);
                (void)hoisted__U64_1605;
                U32 hoisted__U32_1606 = 16;
                (void)hoisted__U32_1606;
                void *hoisted__v_1607 = ptr_add(new_data, hoisted__U64_1605);
                (void)hoisted__v_1607;
                (void)hoisted__v_1607;
                U64 hoisted__U64_1608 = (U64)(hoisted__U32_1606);
                (void)hoisted__U64_1608;
                memcpy(hoisted__v_1607, cloned, hoisted__U64_1608);
                U32 hoisted__U32_1609 = 16;
                (void)hoisted__U32_1609;
                I32 hoisted__I32_1610 = 0;
                (void)hoisted__I32_1610;
                U64 hoisted__U64_1611 = (U64)(hoisted__U32_1609);
                (void)hoisted__U64_1611;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1610, hoisted__U64_1611); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1612 = ((Bool)(_rc_U32_1598 > _re_U32_1598));
                (void)_wcond_Bool_1612;
                if (_wcond_Bool_1612) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1598);
                U32_dec(&_rc_U32_1598);
                U32 hoisted__U32_1613 = 16;
                (void)hoisted__U32_1613;
                U32 hoisted__U32_1614 = ((U32)(i * hoisted__U32_1613));
                (void)hoisted__U32_1614;
                U64 hoisted__U64_1615 = (U64)(hoisted__U32_1614);
                (void)hoisted__U64_1615;
                Str *src = ptr_add(self->data, hoisted__U64_1615);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1616 = 16;
                (void)hoisted__U32_1616;
                U32 hoisted__U32_1617 = ((U32)(i * hoisted__U32_1616));
                (void)hoisted__U32_1617;
                U64 hoisted__U64_1618 = (U64)(hoisted__U32_1617);
                (void)hoisted__U64_1618;
                U32 hoisted__U32_1619 = 16;
                (void)hoisted__U32_1619;
                void *hoisted__v_1620 = ptr_add(new_data, hoisted__U64_1618);
                (void)hoisted__v_1620;
                (void)hoisted__v_1620;
                U64 hoisted__U64_1621 = (U64)(hoisted__U32_1619);
                (void)hoisted__U64_1621;
                memcpy(hoisted__v_1620, cloned, hoisted__U64_1621);
                U32 hoisted__U32_1622 = 16;
                (void)hoisted__U32_1622;
                I32 hoisted__I32_1623 = 0;
                (void)hoisted__I32_1623;
                U64 hoisted__U64_1624 = (U64)(hoisted__U32_1622);
                (void)hoisted__U64_1624;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_1623, hoisted__U64_1624); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_1629 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_1629->data = new_data;
    hoisted__Vec__Str_1629->count = self->count;
    hoisted__Vec__Str_1629->cap = self->cap;
    (void)hoisted__Vec__Str_1629;
    return hoisted__Vec__Str_1629;
}

U32 Vec__Str_size(void) {
    U32 hoisted__U32_1630 = 16;
    (void)hoisted__U32_1630;
    return hoisted__U32_1630;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1633 = 8;
    (void)hoisted__U32_1633;
    return hoisted__U32_1633;
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
    I64 hoisted__I64_1831 = 0;
    (void)hoisted__I64_1831;
    Bool hoisted__Bool_1832 = ((Bool)(val == hoisted__I64_1831));
    (void)hoisted__Bool_1832;
    if (hoisted__Bool_1832) {
        U64 hoisted__U64_1801 = 2ULL;
        (void)hoisted__U64_1801;
        void * buf = malloc(hoisted__U64_1801);
        I64 hoisted__I64_1802 = 48;
        (void)hoisted__I64_1802;
        U64 hoisted__U64_1803 = 1ULL;
        (void)hoisted__U64_1803;
        memcpy(buf, &hoisted__I64_1802, hoisted__U64_1803);
        U64 hoisted__U64_1804 = 1ULL;
        (void)hoisted__U64_1804;
        void *hoisted__v_1805 = ptr_add(buf, hoisted__U64_1804);
        (void)hoisted__v_1805;
        (void)hoisted__v_1805;
        I32 hoisted__I32_1806 = 0;
        (void)hoisted__I32_1806;
        U64 hoisted__U64_1807 = 1ULL;
        (void)hoisted__U64_1807;
        memset(hoisted__v_1805, hoisted__I32_1806, hoisted__U64_1807);
        I64 hoisted__I64_1808 = 1;
        (void)hoisted__I64_1808;
        I64 hoisted__I64_1809 = 1;
        (void)hoisted__I64_1809;
        Str *hoisted__Str_1810 = malloc(sizeof(Str));
        hoisted__Str_1810->c_str = buf;
        hoisted__Str_1810->count = hoisted__I64_1808;
        hoisted__Str_1810->cap = hoisted__I64_1809;
        (void)hoisted__Str_1810;
        { Str * _ret_val = hoisted__Str_1810;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1833 = 0;
    (void)hoisted__I64_1833;
    Bool hoisted__Bool_1834 = ((Bool)(val < hoisted__I64_1833));
    (void)hoisted__Bool_1834;
    if (hoisted__Bool_1834) {
        Bool hoisted__Bool_1811 = 1;
        (void)hoisted__Bool_1811;
        is_neg = hoisted__Bool_1811;
        I64 hoisted__I64_1812 = 0;
        (void)hoisted__I64_1812;
        I64 hoisted__I64_1813 = ((I64)(hoisted__I64_1812 - val));
        (void)hoisted__I64_1813;
        v = hoisted__I64_1813;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1815 = 0;
        (void)hoisted__I64_1815;
        Bool _wcond_Bool_1814 = ((Bool)(tmp > hoisted__I64_1815));
        (void)_wcond_Bool_1814;
        if (_wcond_Bool_1814) {
        } else {
            break;
        }
        U64_inc(&ndigits);
        I64 hoisted__I64_1816 = 10;
        (void)hoisted__I64_1816;
        I64 hoisted__I64_1817 = ({ I64 _cf_a = tmp; I64 _cf_b = hoisted__I64_1816; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1817;
        tmp = hoisted__I64_1817;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64_inc(&total);
    }
    U64 hoisted__U64_1835 = 1ULL;
    (void)hoisted__U64_1835;
    U64 hoisted__U64_1836 = ((U64)(total + hoisted__U64_1835));
    (void)hoisted__U64_1836;
    void * buf = malloc(hoisted__U64_1836);
    if (is_neg) {
        I64 hoisted__I64_1818 = 45;
        (void)hoisted__I64_1818;
        U64 hoisted__U64_1819 = 1ULL;
        (void)hoisted__U64_1819;
        memcpy(buf, &hoisted__I64_1818, hoisted__U64_1819);
    }
    U64 hoisted__U64_1837 = 1ULL;
    (void)hoisted__U64_1837;
    U64 i = ((U64)(total - hoisted__U64_1837));
    while (1) {
        I64 hoisted__I64_1821 = 0;
        (void)hoisted__I64_1821;
        Bool _wcond_Bool_1820 = ((Bool)(v > hoisted__I64_1821));
        (void)_wcond_Bool_1820;
        if (_wcond_Bool_1820) {
        } else {
            break;
        }
        I64 hoisted__I64_1822 = 10;
        (void)hoisted__I64_1822;
        I64 hoisted__I64_1823 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1822; (I64)((_cf_b == 0) ? 0 : (_cf_a % _cf_b)); });
        (void)hoisted__I64_1823;
        I64 hoisted__I64_1824 = 48;
        (void)hoisted__I64_1824;
        I64 hoisted__I64_1825 = ((I64)(hoisted__I64_1823 + hoisted__I64_1824));
        (void)hoisted__I64_1825;
        void *hoisted__v_1826 = ptr_add(buf, i);
        (void)hoisted__v_1826;
        (void)hoisted__v_1826;
        U8 hoisted__U8_1827 = I64_to_u8(hoisted__I64_1825);
        (void)hoisted__U8_1827;
        U64 hoisted__U64_1828 = 1ULL;
        (void)hoisted__U64_1828;
        memcpy(hoisted__v_1826, &hoisted__U8_1827, hoisted__U64_1828);
        I64 hoisted__I64_1829 = 10;
        (void)hoisted__I64_1829;
        I64 hoisted__I64_1830 = ({ I64 _cf_a = v; I64 _cf_b = hoisted__I64_1829; (I64)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        (void)hoisted__I64_1830;
        v = hoisted__I64_1830;
        U64_dec(&i);
    }
    void *hoisted__v_1838 = ptr_add(buf, total);
    (void)hoisted__v_1838;
    (void)hoisted__v_1838;
    I32 hoisted__I32_1839 = 0;
    (void)hoisted__I32_1839;
    U64 hoisted__U64_1840 = 1ULL;
    (void)hoisted__U64_1840;
    memset(hoisted__v_1838, hoisted__I32_1839, hoisted__U64_1840);
    Str *hoisted__Str_1841 = malloc(sizeof(Str));
    hoisted__Str_1841->c_str = buf;
    hoisted__Str_1841->count = total;
    hoisted__Str_1841->cap = total;
    (void)hoisted__Str_1841;
    return hoisted__Str_1841;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1859 = 8;
    (void)hoisted__U32_1859;
    return hoisted__U32_1859;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_2017 = 0;
    (void)hoisted__U32_2017;
    U64 hoisted__U64_2018 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2017); });
    (void)hoisted__U64_2018;
    return hoisted__U64_2018;
}

Bool and(Bool a, Bool b) {
    Bool _m_Bool_2065 = 0;
    (void)_m_Bool_2065;
    {
        Bool hoisted__Bool_2068 = 1;
        (void)hoisted__Bool_2068;
        Bool hoisted__Bool_2069 = Bool_eq(a, hoisted__Bool_2068);
        (void)hoisted__Bool_2069;
        if (hoisted__Bool_2069) {
            Bool hoisted__Bool_2066 = Bool_clone(&b);
            (void)hoisted__Bool_2066;
            _m_Bool_2065 = hoisted__Bool_2066;
        } else {
            Bool hoisted__Bool_2067 = 0;
            (void)hoisted__Bool_2067;
            _m_Bool_2065 = hoisted__Bool_2067;
        }
    }
    return _m_Bool_2065;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_2079 = Bool_eq(a, b);
    (void)hoisted__Bool_2079;
    if (hoisted__Bool_2079) {
        I64 hoisted__I64_2077 = 0;
        (void)hoisted__I64_2077;
        { I64 _ret_val = hoisted__I64_2077;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_2078 = -1;
        (void)hoisted__I64_2078;
        return hoisted__I64_2078;
    }
    I64 hoisted__I64_2080 = 1;
    (void)hoisted__I64_2080;
    return hoisted__I64_2080;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_2081 = 1;
    (void)hoisted__U32_2081;
    return hoisted__U32_2081;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_2082 = 0;
    (void)hoisted__U32_2082;
    U64 hoisted__U64_2083 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_2082); });
    (void)hoisted__U64_2083;
    return hoisted__U64_2083;
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
    Bool hoisted__Bool_2109 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2109;
    if (hoisted__Bool_2109) {
        Bool hoisted__Bool_2099 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2099;
        { Bool _ret_val = hoisted__Bool_2099;
                return _ret_val; }
    }
    Bool hoisted__Bool_2110 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2110;
    if (hoisted__Bool_2110) {
        Bool hoisted__Bool_2100 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2100;
        { Bool _ret_val = hoisted__Bool_2100;
                return _ret_val; }
    }
    Bool hoisted__Bool_2111 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2111;
    if (hoisted__Bool_2111) {
        Bool hoisted__Bool_2101 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2101;
        { Bool _ret_val = hoisted__Bool_2101;
                return _ret_val; }
    }
    Bool hoisted__Bool_2112 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2112;
    if (hoisted__Bool_2112) {
        Bool hoisted__Bool_2102 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2102;
        { Bool _ret_val = hoisted__Bool_2102;
                return _ret_val; }
    }
    Bool hoisted__Bool_2113 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2113;
    if (hoisted__Bool_2113) {
        Bool hoisted__Bool_2103 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2103;
        { Bool _ret_val = hoisted__Bool_2103;
                return _ret_val; }
    }
    Bool hoisted__Bool_2114 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2114;
    if (hoisted__Bool_2114) {
        Bool hoisted__Bool_2104 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2104;
        { Bool _ret_val = hoisted__Bool_2104;
                return _ret_val; }
    }
    Bool hoisted__Bool_2115 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2115;
    if (hoisted__Bool_2115) {
        Bool hoisted__Bool_2105 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2105;
        { Bool _ret_val = hoisted__Bool_2105;
                return _ret_val; }
    }
    Bool hoisted__Bool_2116 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2116;
    if (hoisted__Bool_2116) {
        Bool hoisted__Bool_2106 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2106;
        { Bool _ret_val = hoisted__Bool_2106;
                return _ret_val; }
    }
    Bool hoisted__Bool_2117 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2117;
    if (hoisted__Bool_2117) {
        Bool hoisted__Bool_2107 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2107;
        { Bool _ret_val = hoisted__Bool_2107;
                return _ret_val; }
    }
    Bool hoisted__Bool_2118 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2118;
    if (hoisted__Bool_2118) {
        Bool hoisted__Bool_2108 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2108;
        { Bool _ret_val = hoisted__Bool_2108;
                return _ret_val; }
    }
    Bool hoisted__Bool_2119 = 0;
    (void)hoisted__Bool_2119;
    return hoisted__Bool_2119;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2141 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2141;
    if (hoisted__Bool_2141) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2142 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2142;
    if (hoisted__Bool_2142) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2143 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2143;
    if (hoisted__Bool_2143) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2144 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2144;
    if (hoisted__Bool_2144) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2145 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2145;
    if (hoisted__Bool_2145) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2146 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2146;
    if (hoisted__Bool_2146) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2147 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2147;
    if (hoisted__Bool_2147) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2148 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2148;
    if (hoisted__Bool_2148) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2149 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2149;
    if (hoisted__Bool_2149) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2150 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2150;
    if (hoisted__Bool_2150) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    static Str hoisted__Str_2151 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2151;
    UNREACHABLE(&hoisted__Str_2151);
    Str_delete(&hoisted__Str_2151, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2152 = 4;
    (void)hoisted__U32_2152;
    return hoisted__U32_2152;
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
    Bool hoisted__Bool_2204 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2204;
    if (hoisted__Bool_2204) {
        Str *hoisted__Str_2194 = get_payload(self);
        (void)hoisted__Str_2194;
        (void)hoisted__Str_2194;
        Bool hoisted__Bool_2195 = 0;
        (void)hoisted__Bool_2195;
        Str_delete(hoisted__Str_2194, hoisted__Bool_2195);
    }
    Bool hoisted__Bool_2205 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2205;
    if (hoisted__Bool_2205) {
        Str *hoisted__Str_2196 = get_payload(self);
        (void)hoisted__Str_2196;
        (void)hoisted__Str_2196;
        Bool hoisted__Bool_2197 = 0;
        (void)hoisted__Bool_2197;
        Str_delete(hoisted__Str_2196, hoisted__Bool_2197);
    }
    Bool hoisted__Bool_2206 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2206;
    if (hoisted__Bool_2206) {
        Str *hoisted__Str_2198 = get_payload(self);
        (void)hoisted__Str_2198;
        (void)hoisted__Str_2198;
        Bool hoisted__Bool_2199 = 0;
        (void)hoisted__Bool_2199;
        Str_delete(hoisted__Str_2198, hoisted__Bool_2199);
    }
    Bool hoisted__Bool_2207 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2207;
    if (hoisted__Bool_2207) {
        Primitive *hoisted__Primitive_2200 = get_payload(self);
        (void)hoisted__Primitive_2200;
        (void)hoisted__Primitive_2200;
        Bool hoisted__Bool_2201 = 0;
        (void)hoisted__Bool_2201;
        Primitive_delete(hoisted__Primitive_2200, hoisted__Bool_2201);
    }
    Bool hoisted__Bool_2208 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2208;
    if (hoisted__Bool_2208) {
        Str *hoisted__Str_2202 = get_payload(self);
        (void)hoisted__Str_2202;
        (void)hoisted__Str_2202;
        Bool hoisted__Bool_2203 = 0;
        (void)hoisted__Bool_2203;
        Str_delete(hoisted__Str_2202, hoisted__Bool_2203);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2292 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2292;
    if (hoisted__Bool_2292) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2293 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2293;
    if (hoisted__Bool_2293) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2294 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2294;
    if (hoisted__Bool_2294) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2284 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2284;
        Type *hoisted__Type_2285 = Type_Struct(hoisted__Str_2284);
        (void)hoisted__Type_2285;
        { Type * _ret_val = hoisted__Type_2285;
                return _ret_val; }
    }
    Bool hoisted__Bool_2295 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2295;
    if (hoisted__Bool_2295) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2296 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2296;
    if (hoisted__Bool_2296) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2286 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2286;
        Type *hoisted__Type_2287 = Type_Enum(hoisted__Str_2286);
        (void)hoisted__Type_2287;
        { Type * _ret_val = hoisted__Type_2287;
                return _ret_val; }
    }
    Bool hoisted__Bool_2297 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2297;
    if (hoisted__Bool_2297) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2298 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2298;
    if (hoisted__Bool_2298) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2299 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2299;
    if (hoisted__Bool_2299) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2300 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2300;
    if (hoisted__Bool_2300) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2301 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2301;
    if (hoisted__Bool_2301) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2288 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2288;
        Type *hoisted__Type_2289 = Type_Custom(hoisted__Str_2288);
        (void)hoisted__Type_2289;
        { Type * _ret_val = hoisted__Type_2289;
                return _ret_val; }
    }
    Bool hoisted__Bool_2302 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2302;
    if (hoisted__Bool_2302) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2290 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2290;
        Type *hoisted__Type_2291 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2290; _oa; }));
        (void)hoisted__Type_2291;
        { Type * _ret_val = hoisted__Type_2291;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2303 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2303;
    Type *hoisted__Type_2304 = Type_FuncPtrSig(hoisted__Str_2303);
    (void)hoisted__Type_2304;
    return hoisted__Type_2304;
}

U32 Type_size(void) {
    U32 hoisted__U32_2305 = 24;
    (void)hoisted__U32_2305;
    return hoisted__U32_2305;
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
    Bool hoisted__Bool_2408 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2408;
    if (hoisted__Bool_2408) {
        Bool hoisted__Bool_2398 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2398;
        { Bool _ret_val = hoisted__Bool_2398;
                return _ret_val; }
    }
    Bool hoisted__Bool_2409 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2409;
    if (hoisted__Bool_2409) {
        Bool hoisted__Bool_2399 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2399;
        { Bool _ret_val = hoisted__Bool_2399;
                return _ret_val; }
    }
    Bool hoisted__Bool_2410 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2410;
    if (hoisted__Bool_2410) {
        Bool hoisted__Bool_2400 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2400;
        { Bool _ret_val = hoisted__Bool_2400;
                return _ret_val; }
    }
    Bool hoisted__Bool_2411 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2411;
    if (hoisted__Bool_2411) {
        Bool hoisted__Bool_2401 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2401;
        { Bool _ret_val = hoisted__Bool_2401;
                return _ret_val; }
    }
    Bool hoisted__Bool_2412 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2412;
    if (hoisted__Bool_2412) {
        Bool hoisted__Bool_2402 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2402;
        { Bool _ret_val = hoisted__Bool_2402;
                return _ret_val; }
    }
    Bool hoisted__Bool_2413 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2413;
    if (hoisted__Bool_2413) {
        Bool hoisted__Bool_2403 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2403;
        { Bool _ret_val = hoisted__Bool_2403;
                return _ret_val; }
    }
    Bool hoisted__Bool_2414 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2414;
    if (hoisted__Bool_2414) {
        Bool hoisted__Bool_2404 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2404;
        { Bool _ret_val = hoisted__Bool_2404;
                return _ret_val; }
    }
    Bool hoisted__Bool_2415 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2415;
    if (hoisted__Bool_2415) {
        Bool hoisted__Bool_2405 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2405;
        { Bool _ret_val = hoisted__Bool_2405;
                return _ret_val; }
    }
    Bool hoisted__Bool_2416 = is(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2416;
    if (hoisted__Bool_2416) {
        Bool hoisted__Bool_2406 = is(other, &(FuncType){.tag = FuncType_TAG_CoreFunc});
        (void)hoisted__Bool_2406;
        { Bool _ret_val = hoisted__Bool_2406;
                return _ret_val; }
    }
    Bool hoisted__Bool_2417 = is(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2417;
    if (hoisted__Bool_2417) {
        Bool hoisted__Bool_2407 = is(other, &(FuncType){.tag = FuncType_TAG_CoreProc});
        (void)hoisted__Bool_2407;
        { Bool _ret_val = hoisted__Bool_2407;
                return _ret_val; }
    }
    Bool hoisted__Bool_2418 = 0;
    (void)hoisted__Bool_2418;
    return hoisted__Bool_2418;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2440 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2440;
    if (hoisted__Bool_2440) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2441 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2441;
    if (hoisted__Bool_2441) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2442 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2442;
    if (hoisted__Bool_2442) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2443 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2443;
    if (hoisted__Bool_2443) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2444 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2444;
    if (hoisted__Bool_2444) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2445 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2445;
    if (hoisted__Bool_2445) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2446 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2446;
    if (hoisted__Bool_2446) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2447 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2447;
    if (hoisted__Bool_2447) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Bool hoisted__Bool_2448 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2448;
    if (hoisted__Bool_2448) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
                return _r; }
    }
    Bool hoisted__Bool_2449 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2449;
    if (hoisted__Bool_2449) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
                return _r; }
    }
    static Str hoisted__Str_2450 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2450;
    UNREACHABLE(&hoisted__Str_2450);
    Str_delete(&hoisted__Str_2450, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2451 = 4;
    (void)hoisted__U32_2451;
    return hoisted__U32_2451;
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
    Bool hoisted__Bool_2456 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2456;
    if (hoisted__Bool_2456) {
        Bool hoisted__Bool_2453 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2453;
        { Bool _ret_val = hoisted__Bool_2453;
                return _ret_val; }
    }
    Bool hoisted__Bool_2457 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2457;
    if (hoisted__Bool_2457) {
        Bool hoisted__Bool_2454 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2454;
        { Bool _ret_val = hoisted__Bool_2454;
                return _ret_val; }
    }
    Bool hoisted__Bool_2458 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2458;
    if (hoisted__Bool_2458) {
        Bool hoisted__Bool_2455 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2455;
        { Bool _ret_val = hoisted__Bool_2455;
                return _ret_val; }
    }
    Bool hoisted__Bool_2459 = 0;
    (void)hoisted__Bool_2459;
    return hoisted__Bool_2459;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2467 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2467;
    if (hoisted__Bool_2467) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2468 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2468;
    if (hoisted__Bool_2468) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2469 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2469;
    if (hoisted__Bool_2469) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    static Str hoisted__Str_2470 = (Str){.c_str = (void *)"OwnType.clone:141:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2470;
    UNREACHABLE(&hoisted__Str_2470);
    Str_delete(&hoisted__Str_2470, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2471 = 4;
    (void)hoisted__U32_2471;
    return hoisted__U32_2471;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2473 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2473;
    Declaration *hoisted__Declaration_2474 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2474->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2474->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2474->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2474->is_mut = self->is_mut;
    hoisted__Declaration_2474->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2474->is_priv = self->is_priv;
    hoisted__Declaration_2474->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2474->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2474->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2474->default_value = hoisted__Expr_2473;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2474->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2474;
    return hoisted__Declaration_2474;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2475 = 0;
    (void)hoisted__Bool_2475;
    Str_delete(&self->name, hoisted__Bool_2475);
    Bool hoisted__Bool_2476 = 0;
    (void)hoisted__Bool_2476;
    Str_delete(&self->doc, hoisted__Bool_2476);
    Bool hoisted__Bool_2477 = 0;
    (void)hoisted__Bool_2477;
    Str_delete(&self->explicit_type, hoisted__Bool_2477);
    Bool hoisted__Bool_2478 = 0;
    (void)hoisted__Bool_2478;
    Bool_delete(&self->is_mut, hoisted__Bool_2478);
    Bool hoisted__Bool_2479 = 0;
    (void)hoisted__Bool_2479;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2479);
    Bool hoisted__Bool_2480 = 0;
    (void)hoisted__Bool_2480;
    Bool_delete(&self->is_priv, hoisted__Bool_2480);
    Bool hoisted__Bool_2481 = 0;
    (void)hoisted__Bool_2481;
    Bool_delete(&self->used, hoisted__Bool_2481);
    Bool hoisted__Bool_2482 = 0;
    (void)hoisted__Bool_2482;
    OwnType_delete(&self->own_type, hoisted__Bool_2482);
    Bool hoisted__Bool_2483 = 0;
    (void)hoisted__Bool_2483;
    Type_delete(&self->til_type, hoisted__Bool_2483);
    Bool hoisted__Bool_2484 = 1;
    (void)hoisted__Bool_2484;
    Expr_delete(self->default_value, hoisted__Bool_2484);
    Bool hoisted__Bool_2485 = 0;
    (void)hoisted__Bool_2485;
    Str_delete(&self->orig_name, hoisted__Bool_2485);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2486 = 104;
    (void)hoisted__U32_2486;
    return hoisted__U32_2486;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2488 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2488->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2488->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2488->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2488->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2488->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2488->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2488->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2488->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2488->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2488->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2488->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2488;
    return hoisted__FunctionDef_2488;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2489 = 0;
    (void)hoisted__Bool_2489;
    FuncType_delete(&self->func_type, hoisted__Bool_2489);
    Bool hoisted__Bool_2490 = 0;
    (void)hoisted__Bool_2490;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2490);
    Bool hoisted__Bool_2491 = 0;
    (void)hoisted__Bool_2491;
    Str_delete(&self->return_type, hoisted__Bool_2491);
    Bool hoisted__Bool_2492 = 0;
    (void)hoisted__Bool_2492;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2492);
    Bool hoisted__Bool_2493 = 0;
    (void)hoisted__Bool_2493;
    I32_delete(&self->variadic_index, hoisted__Bool_2493);
    Bool hoisted__Bool_2494 = 0;
    (void)hoisted__Bool_2494;
    I32_delete(&self->kwargs_index, hoisted__Bool_2494);
    Bool hoisted__Bool_2495 = 0;
    (void)hoisted__Bool_2495;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2495);
    Bool hoisted__Bool_2496 = 0;
    (void)hoisted__Bool_2496;
    Bool_delete(&self->auto_generated, hoisted__Bool_2496);
    Bool hoisted__Bool_2497 = 0;
    (void)hoisted__Bool_2497;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2497);
    Bool hoisted__Bool_2498 = 0;
    (void)hoisted__Bool_2498;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2498);
    Bool hoisted__Bool_2499 = 0;
    (void)hoisted__Bool_2499;
    Str_delete(&self->closure_name, hoisted__Bool_2499);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2500 = 0;
    (void)hoisted__U32_2500;
    U64 hoisted__U64_2501 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2500); });
    (void)hoisted__U64_2501;
    return hoisted__U64_2501;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2502 = 104;
    (void)hoisted__U32_2502;
    return hoisted__U32_2502;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2505 = malloc(sizeof(FCallData));
    hoisted__FCallData_2505->is_splat = self->is_splat;
    hoisted__FCallData_2505->does_throw = self->does_throw;
    hoisted__FCallData_2505->is_bang = self->is_bang;
    hoisted__FCallData_2505->own_args = self->own_args;
    hoisted__FCallData_2505->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2505->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2505;
    return hoisted__FCallData_2505;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2506 = 0;
    (void)hoisted__Bool_2506;
    Bool_delete(&self->is_splat, hoisted__Bool_2506);
    Bool hoisted__Bool_2507 = 0;
    (void)hoisted__Bool_2507;
    Bool_delete(&self->does_throw, hoisted__Bool_2507);
    Bool hoisted__Bool_2508 = 0;
    (void)hoisted__Bool_2508;
    Bool_delete(&self->is_bang, hoisted__Bool_2508);
    Bool hoisted__Bool_2509 = 0;
    (void)hoisted__Bool_2509;
    U64_delete(&self->own_args, hoisted__Bool_2509);
    Bool hoisted__Bool_2510 = 0;
    (void)hoisted__Bool_2510;
    Bool_delete(&self->swap_replace, hoisted__Bool_2510);
    Bool hoisted__Bool_2511 = 0;
    (void)hoisted__Bool_2511;
    Type_delete(&self->til_type, hoisted__Bool_2511);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2512 = 0;
    (void)hoisted__U32_2512;
    U64 hoisted__U64_2513 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2512); });
    (void)hoisted__U64_2513;
    return hoisted__U64_2513;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2514 = 48;
    (void)hoisted__U32_2514;
    return hoisted__U32_2514;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2526 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2526->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2526->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2526;
    return hoisted__LiteralNumData_2526;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2527 = 0;
    (void)hoisted__Bool_2527;
    Str_delete(&self->text, hoisted__Bool_2527);
    Bool hoisted__Bool_2528 = 0;
    (void)hoisted__Bool_2528;
    Type_delete(&self->til_type, hoisted__Bool_2528);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2529 = 0;
    (void)hoisted__U32_2529;
    U64 hoisted__U64_2530 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2529); });
    (void)hoisted__U64_2530;
    return hoisted__U64_2530;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2531 = 40;
    (void)hoisted__U32_2531;
    return hoisted__U32_2531;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2541 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2541->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2541->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2541;
    return hoisted__IdentData_2541;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2542 = 0;
    (void)hoisted__Bool_2542;
    Str_delete(&self->name, hoisted__Bool_2542);
    Bool hoisted__Bool_2543 = 0;
    (void)hoisted__Bool_2543;
    Type_delete(&self->til_type, hoisted__Bool_2543);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2544 = 0;
    (void)hoisted__U32_2544;
    U64 hoisted__U64_2545 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2544); });
    (void)hoisted__U64_2545;
    return hoisted__U64_2545;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2546 = 40;
    (void)hoisted__U32_2546;
    return hoisted__U32_2546;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2552 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2552->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2552->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2552;
    return hoisted__FieldAccessData_2552;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2553 = 0;
    (void)hoisted__Bool_2553;
    Str_delete(&self->name, hoisted__Bool_2553);
    Bool hoisted__Bool_2554 = 0;
    (void)hoisted__Bool_2554;
    Type_delete(&self->til_type, hoisted__Bool_2554);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2555 = 0;
    (void)hoisted__U32_2555;
    U64 hoisted__U64_2556 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2555); });
    (void)hoisted__U64_2556;
    return hoisted__U64_2556;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2557 = 40;
    (void)hoisted__U32_2557;
    return hoisted__U32_2557;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2638 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2638->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2638->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2638->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2638->is_interface = self->is_interface;
    hoisted__StructDef_2638->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2638->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2638;
    return hoisted__StructDef_2638;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2639 = 0;
    (void)hoisted__Bool_2639;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2639);
    Bool hoisted__Bool_2640 = 0;
    (void)hoisted__Bool_2640;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2640);
    Bool hoisted__Bool_2641 = 0;
    (void)hoisted__Bool_2641;
    Str_delete(&self->c_tag, hoisted__Bool_2641);
    Bool hoisted__Bool_2642 = 0;
    (void)hoisted__Bool_2642;
    Bool_delete(&self->is_interface, hoisted__Bool_2642);
    Bool hoisted__Bool_2643 = 0;
    (void)hoisted__Bool_2643;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2643);
    Bool hoisted__Bool_2644 = 0;
    (void)hoisted__Bool_2644;
    Str_delete(&self->implements_name, hoisted__Bool_2644);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2645 = 0;
    (void)hoisted__U32_2645;
    U64 hoisted__U64_2646 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2645); });
    (void)hoisted__U64_2646;
    return hoisted__U64_2646;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2647 = 72;
    (void)hoisted__U32_2647;
    return hoisted__U32_2647;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2652 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2652->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2652->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2652->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2652->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2652->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2652->tag_type = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2652;
    return hoisted__EnumDef_2652;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2653 = 0;
    (void)hoisted__Bool_2653;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2653);
    Bool hoisted__Bool_2654 = 0;
    (void)hoisted__Bool_2654;
    Vec__Str_delete(&self->variants, hoisted__Bool_2654);
    Bool hoisted__Bool_2655 = 0;
    (void)hoisted__Bool_2655;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2655);
    Bool hoisted__Bool_2656 = 0;
    (void)hoisted__Bool_2656;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2656);
    Bool hoisted__Bool_2657 = 0;
    (void)hoisted__Bool_2657;
    Str_delete(&self->implements_name, hoisted__Bool_2657);
    Bool hoisted__Bool_2658 = 0;
    (void)hoisted__Bool_2658;
    Str_delete(&self->tag_type, hoisted__Bool_2658);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2659 = 0;
    (void)hoisted__U32_2659;
    U64 hoisted__U64_2660 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2659); });
    (void)hoisted__U64_2660;
    return hoisted__U64_2660;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2661 = 112;
    (void)hoisted__U32_2661;
    return hoisted__U32_2661;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2760 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2760->name = *_ca; free(_ca); }
    hoisted__AssignData_2760->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2760->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2760->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2760;
    return hoisted__AssignData_2760;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2761 = 0;
    (void)hoisted__Bool_2761;
    Str_delete(&self->name, hoisted__Bool_2761);
    Bool hoisted__Bool_2762 = 0;
    (void)hoisted__Bool_2762;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2762);
    Bool hoisted__Bool_2763 = 0;
    (void)hoisted__Bool_2763;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2763);
    Bool hoisted__Bool_2764 = 0;
    (void)hoisted__Bool_2764;
    Bool_delete(&self->swap_replace, hoisted__Bool_2764);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2765 = 0;
    (void)hoisted__U32_2765;
    U64 hoisted__U64_2766 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2765); });
    (void)hoisted__U64_2766;
    return hoisted__U64_2766;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2767 = 24;
    (void)hoisted__U32_2767;
    return hoisted__U32_2767;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2769 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2769->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2769->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2769;
    return hoisted__FieldAssignData_2769;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2770 = 0;
    (void)hoisted__Bool_2770;
    Str_delete(&self->name, hoisted__Bool_2770);
    Bool hoisted__Bool_2771 = 0;
    (void)hoisted__Bool_2771;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2771);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2772 = 0;
    (void)hoisted__U32_2772;
    U64 hoisted__U64_2773 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2772); });
    (void)hoisted__U64_2773;
    return hoisted__U64_2773;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2774 = 24;
    (void)hoisted__U32_2774;
    return hoisted__U32_2774;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2776 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2776->name = *_ca; free(_ca); }
    hoisted__ForInData_2776->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2776->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2776->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2776->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2776;
    return hoisted__ForInData_2776;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2777 = 0;
    (void)hoisted__Bool_2777;
    Str_delete(&self->name, hoisted__Bool_2777);
    Bool hoisted__Bool_2778 = 0;
    (void)hoisted__Bool_2778;
    Bool_delete(&self->is_mut, hoisted__Bool_2778);
    Bool hoisted__Bool_2779 = 0;
    (void)hoisted__Bool_2779;
    Type_delete(&self->til_type, hoisted__Bool_2779);
    Bool hoisted__Bool_2780 = 0;
    (void)hoisted__Bool_2780;
    Str_delete(&self->name2, hoisted__Bool_2780);
    Bool hoisted__Bool_2781 = 0;
    (void)hoisted__Bool_2781;
    Bool_delete(&self->is_mut2, hoisted__Bool_2781);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2782 = 0;
    (void)hoisted__U32_2782;
    U64 hoisted__U64_2783 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2782); });
    (void)hoisted__U64_2783;
    return hoisted__U64_2783;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2784 = 72;
    (void)hoisted__U32_2784;
    return hoisted__U32_2784;
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
    Bool hoisted__Bool_2814 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2814;
    if (hoisted__Bool_2814) {
        Str *hoisted__Str_2808 = get_payload(self);
        (void)hoisted__Str_2808;
        (void)hoisted__Str_2808;
        Bool hoisted__Bool_2809 = 0;
        (void)hoisted__Bool_2809;
        Str_delete(hoisted__Str_2808, hoisted__Bool_2809);
    }
    Bool hoisted__Bool_2815 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2815;
    if (hoisted__Bool_2815) {
        LiteralNumData *hoisted__LiteralNumData_2810 = get_payload(self);
        (void)hoisted__LiteralNumData_2810;
        (void)hoisted__LiteralNumData_2810;
        Bool hoisted__Bool_2811 = 0;
        (void)hoisted__Bool_2811;
        LiteralNumData_delete(hoisted__LiteralNumData_2810, hoisted__Bool_2811);
    }
    Bool hoisted__Bool_2816 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2816;
    if (hoisted__Bool_2816) {
        Bool *hoisted__Bool_2812 = get_payload(self);
        (void)hoisted__Bool_2812;
        (void)hoisted__Bool_2812;
        Bool hoisted__Bool_2813 = 0;
        (void)hoisted__Bool_2813;
        Bool_delete(hoisted__Bool_2812, hoisted__Bool_2813);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2865 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2865;
    if (hoisted__Bool_2865) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2860 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2860;
        Literal *hoisted__Literal_2861 = Literal_Str(hoisted__Str_2860);
        (void)hoisted__Literal_2861;
        { Literal * _ret_val = hoisted__Literal_2861;
                return _ret_val; }
    }
    Bool hoisted__Bool_2866 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2866;
    if (hoisted__Bool_2866) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2862 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2862;
        Literal *hoisted__Literal_2863 = Literal_Num(hoisted__LiteralNumData_2862);
        (void)hoisted__Literal_2863;
        { Literal * _ret_val = hoisted__Literal_2863;
                return _ret_val; }
    }
    Bool hoisted__Bool_2867 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2867;
    if (hoisted__Bool_2867) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2864 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2864;
        { Literal * _ret_val = hoisted__Literal_2864;
                return _ret_val; }
    }
    Bool hoisted__Bool_2868 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2868;
    if (hoisted__Bool_2868) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2869 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2869;
    if (hoisted__Bool_2869) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2870 = 48;
    (void)hoisted__U32_2870;
    return hoisted__U32_2870;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2873 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2873->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2873->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2873;
    return hoisted__MatchData_2873;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2874 = 0;
    (void)hoisted__Bool_2874;
    Type_delete(&self->til_type, hoisted__Bool_2874);
    Bool hoisted__Bool_2875 = 0;
    (void)hoisted__Bool_2875;
    Str_delete(&self->result_temp, hoisted__Bool_2875);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2876 = 0;
    (void)hoisted__U32_2876;
    U64 hoisted__U64_2877 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2876); });
    (void)hoisted__U64_2877;
    return hoisted__U64_2877;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2878 = 40;
    (void)hoisted__U32_2878;
    return hoisted__U32_2878;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2883 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2883->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2883;
    return hoisted__CaptureBlockData_2883;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2884 = 0;
    (void)hoisted__Bool_2884;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2884);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2885 = 0;
    (void)hoisted__U32_2885;
    U64 hoisted__U64_2886 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2885); });
    (void)hoisted__U64_2886;
    return hoisted__U64_2886;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2887 = 16;
    (void)hoisted__U32_2887;
    return hoisted__U32_2887;
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
    Bool hoisted__Bool_3066 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3066;
    if (hoisted__Bool_3066) {
        Literal *hoisted__Literal_3038 = get_payload(self);
        (void)hoisted__Literal_3038;
        (void)hoisted__Literal_3038;
        Bool hoisted__Bool_3039 = 0;
        (void)hoisted__Bool_3039;
        Literal_delete(hoisted__Literal_3038, hoisted__Bool_3039);
    }
    Bool hoisted__Bool_3067 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3067;
    if (hoisted__Bool_3067) {
        IdentData *hoisted__IdentData_3040 = get_payload(self);
        (void)hoisted__IdentData_3040;
        (void)hoisted__IdentData_3040;
        Bool hoisted__Bool_3041 = 0;
        (void)hoisted__Bool_3041;
        IdentData_delete(hoisted__IdentData_3040, hoisted__Bool_3041);
    }
    Bool hoisted__Bool_3068 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3068;
    if (hoisted__Bool_3068) {
        Declaration *hoisted__Declaration_3042 = get_payload(self);
        (void)hoisted__Declaration_3042;
        (void)hoisted__Declaration_3042;
        Bool hoisted__Bool_3043 = 0;
        (void)hoisted__Bool_3043;
        Declaration_delete(hoisted__Declaration_3042, hoisted__Bool_3043);
    }
    Bool hoisted__Bool_3069 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3069;
    if (hoisted__Bool_3069) {
        AssignData *hoisted__AssignData_3044 = get_payload(self);
        (void)hoisted__AssignData_3044;
        (void)hoisted__AssignData_3044;
        Bool hoisted__Bool_3045 = 0;
        (void)hoisted__Bool_3045;
        AssignData_delete(hoisted__AssignData_3044, hoisted__Bool_3045);
    }
    Bool hoisted__Bool_3070 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3070;
    if (hoisted__Bool_3070) {
        FCallData *hoisted__FCallData_3046 = get_payload(self);
        (void)hoisted__FCallData_3046;
        (void)hoisted__FCallData_3046;
        Bool hoisted__Bool_3047 = 0;
        (void)hoisted__Bool_3047;
        FCallData_delete(hoisted__FCallData_3046, hoisted__Bool_3047);
    }
    Bool hoisted__Bool_3071 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3071;
    if (hoisted__Bool_3071) {
        FunctionDef *hoisted__FunctionDef_3048 = get_payload(self);
        (void)hoisted__FunctionDef_3048;
        (void)hoisted__FunctionDef_3048;
        Bool hoisted__Bool_3049 = 0;
        (void)hoisted__Bool_3049;
        FunctionDef_delete(hoisted__FunctionDef_3048, hoisted__Bool_3049);
    }
    Bool hoisted__Bool_3072 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3072;
    if (hoisted__Bool_3072) {
        StructDef *hoisted__StructDef_3050 = get_payload(self);
        (void)hoisted__StructDef_3050;
        (void)hoisted__StructDef_3050;
        Bool hoisted__Bool_3051 = 0;
        (void)hoisted__Bool_3051;
        StructDef_delete(hoisted__StructDef_3050, hoisted__Bool_3051);
    }
    Bool hoisted__Bool_3073 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3073;
    if (hoisted__Bool_3073) {
        EnumDef *hoisted__EnumDef_3052 = get_payload(self);
        (void)hoisted__EnumDef_3052;
        (void)hoisted__EnumDef_3052;
        Bool hoisted__Bool_3053 = 0;
        (void)hoisted__Bool_3053;
        EnumDef_delete(hoisted__EnumDef_3052, hoisted__Bool_3053);
    }
    Bool hoisted__Bool_3074 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3074;
    if (hoisted__Bool_3074) {
        FieldAccessData *hoisted__FieldAccessData_3054 = get_payload(self);
        (void)hoisted__FieldAccessData_3054;
        (void)hoisted__FieldAccessData_3054;
        Bool hoisted__Bool_3055 = 0;
        (void)hoisted__Bool_3055;
        FieldAccessData_delete(hoisted__FieldAccessData_3054, hoisted__Bool_3055);
    }
    Bool hoisted__Bool_3075 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3075;
    if (hoisted__Bool_3075) {
        FieldAssignData *hoisted__FieldAssignData_3056 = get_payload(self);
        (void)hoisted__FieldAssignData_3056;
        (void)hoisted__FieldAssignData_3056;
        Bool hoisted__Bool_3057 = 0;
        (void)hoisted__Bool_3057;
        FieldAssignData_delete(hoisted__FieldAssignData_3056, hoisted__Bool_3057);
    }
    Bool hoisted__Bool_3076 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3076;
    if (hoisted__Bool_3076) {
        ForInData *hoisted__ForInData_3058 = get_payload(self);
        (void)hoisted__ForInData_3058;
        (void)hoisted__ForInData_3058;
        Bool hoisted__Bool_3059 = 0;
        (void)hoisted__Bool_3059;
        ForInData_delete(hoisted__ForInData_3058, hoisted__Bool_3059);
    }
    Bool hoisted__Bool_3077 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3077;
    if (hoisted__Bool_3077) {
        Str *hoisted__Str_3060 = get_payload(self);
        (void)hoisted__Str_3060;
        (void)hoisted__Str_3060;
        Bool hoisted__Bool_3061 = 0;
        (void)hoisted__Bool_3061;
        Str_delete(hoisted__Str_3060, hoisted__Bool_3061);
    }
    Bool hoisted__Bool_3078 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3078;
    if (hoisted__Bool_3078) {
        MatchData *hoisted__MatchData_3062 = get_payload(self);
        (void)hoisted__MatchData_3062;
        (void)hoisted__MatchData_3062;
        Bool hoisted__Bool_3063 = 0;
        (void)hoisted__Bool_3063;
        MatchData_delete(hoisted__MatchData_3062, hoisted__Bool_3063);
    }
    Bool hoisted__Bool_3079 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3079;
    if (hoisted__Bool_3079) {
        CaptureBlockData *hoisted__CaptureBlockData_3064 = get_payload(self);
        (void)hoisted__CaptureBlockData_3064;
        (void)hoisted__CaptureBlockData_3064;
        Bool hoisted__Bool_3065 = 0;
        (void)hoisted__Bool_3065;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3064, hoisted__Bool_3065);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3303 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3303;
    if (hoisted__Bool_3303) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3304 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3304;
    if (hoisted__Bool_3304) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3275 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3275;
        NodeType *hoisted__NodeType_3276 = NodeType_Literal(hoisted__Literal_3275);
        (void)hoisted__NodeType_3276;
        { NodeType * _ret_val = hoisted__NodeType_3276;
                return _ret_val; }
    }
    Bool hoisted__Bool_3305 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3305;
    if (hoisted__Bool_3305) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3277 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3277;
        NodeType *hoisted__NodeType_3278 = NodeType_Ident(hoisted__IdentData_3277);
        (void)hoisted__NodeType_3278;
        { NodeType * _ret_val = hoisted__NodeType_3278;
                return _ret_val; }
    }
    Bool hoisted__Bool_3306 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3306;
    if (hoisted__Bool_3306) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3279 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3279;
        NodeType *hoisted__NodeType_3280 = NodeType_Decl(hoisted__Declaration_3279);
        (void)hoisted__NodeType_3280;
        { NodeType * _ret_val = hoisted__NodeType_3280;
                return _ret_val; }
    }
    Bool hoisted__Bool_3307 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3307;
    if (hoisted__Bool_3307) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3281 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3281;
        NodeType *hoisted__NodeType_3282 = NodeType_Assign(hoisted__AssignData_3281);
        (void)hoisted__NodeType_3282;
        { NodeType * _ret_val = hoisted__NodeType_3282;
                return _ret_val; }
    }
    Bool hoisted__Bool_3308 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3308;
    if (hoisted__Bool_3308) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3283 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3283;
        NodeType *hoisted__NodeType_3284 = NodeType_FCall(hoisted__FCallData_3283);
        (void)hoisted__NodeType_3284;
        { NodeType * _ret_val = hoisted__NodeType_3284;
                return _ret_val; }
    }
    Bool hoisted__Bool_3309 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3309;
    if (hoisted__Bool_3309) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3285 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3285;
        NodeType *hoisted__NodeType_3286 = NodeType_FuncDef(hoisted__FunctionDef_3285);
        (void)hoisted__NodeType_3286;
        { NodeType * _ret_val = hoisted__NodeType_3286;
                return _ret_val; }
    }
    Bool hoisted__Bool_3310 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3310;
    if (hoisted__Bool_3310) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3287 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3287;
        NodeType *hoisted__NodeType_3288 = NodeType_StructDef(hoisted__StructDef_3287);
        (void)hoisted__NodeType_3288;
        { NodeType * _ret_val = hoisted__NodeType_3288;
                return _ret_val; }
    }
    Bool hoisted__Bool_3311 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3311;
    if (hoisted__Bool_3311) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3289 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3289;
        NodeType *hoisted__NodeType_3290 = NodeType_EnumDef(hoisted__EnumDef_3289);
        (void)hoisted__NodeType_3290;
        { NodeType * _ret_val = hoisted__NodeType_3290;
                return _ret_val; }
    }
    Bool hoisted__Bool_3312 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3312;
    if (hoisted__Bool_3312) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3291 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3291;
        NodeType *hoisted__NodeType_3292 = NodeType_FieldAccess(hoisted__FieldAccessData_3291);
        (void)hoisted__NodeType_3292;
        { NodeType * _ret_val = hoisted__NodeType_3292;
                return _ret_val; }
    }
    Bool hoisted__Bool_3313 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3313;
    if (hoisted__Bool_3313) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3293 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3293;
        NodeType *hoisted__NodeType_3294 = NodeType_FieldAssign(hoisted__FieldAssignData_3293);
        (void)hoisted__NodeType_3294;
        { NodeType * _ret_val = hoisted__NodeType_3294;
                return _ret_val; }
    }
    Bool hoisted__Bool_3314 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3314;
    if (hoisted__Bool_3314) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3315 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3315;
    if (hoisted__Bool_3315) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3316 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3316;
    if (hoisted__Bool_3316) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3317 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3317;
    if (hoisted__Bool_3317) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3295 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3295;
        NodeType *hoisted__NodeType_3296 = NodeType_ForIn(hoisted__ForInData_3295);
        (void)hoisted__NodeType_3296;
        { NodeType * _ret_val = hoisted__NodeType_3296;
                return _ret_val; }
    }
    Bool hoisted__Bool_3318 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3318;
    if (hoisted__Bool_3318) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3297 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3297;
        NodeType *hoisted__NodeType_3298 = NodeType_NamedArg(hoisted__Str_3297);
        (void)hoisted__NodeType_3298;
        { NodeType * _ret_val = hoisted__NodeType_3298;
                return _ret_val; }
    }
    Bool hoisted__Bool_3319 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3319;
    if (hoisted__Bool_3319) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3320 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3320;
    if (hoisted__Bool_3320) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3321 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3321;
    if (hoisted__Bool_3321) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3322 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3322;
    if (hoisted__Bool_3322) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3299 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3299;
        NodeType *hoisted__NodeType_3300 = NodeType_Match(hoisted__MatchData_3299);
        (void)hoisted__NodeType_3300;
        { NodeType * _ret_val = hoisted__NodeType_3300;
                return _ret_val; }
    }
    Bool hoisted__Bool_3323 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3323;
    if (hoisted__Bool_3323) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3324 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3324;
    if (hoisted__Bool_3324) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3325 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3325;
    if (hoisted__Bool_3325) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3326 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3326;
    if (hoisted__Bool_3326) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3327 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3327;
    if (hoisted__Bool_3327) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    Bool hoisted__Bool_3328 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_3328;
    if (hoisted__Bool_3328) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3301 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3301;
        NodeType *hoisted__NodeType_3302 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3301);
        (void)hoisted__NodeType_3302;
        { NodeType * _ret_val = hoisted__NodeType_3302;
                return _ret_val; }
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
    return _r; }
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3329 = 120;
    (void)hoisted__U32_3329;
    return hoisted__U32_3329;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3330 = is_null(self);
    (void)hoisted__Bool_3330;
    if (hoisted__Bool_3330) {
        return;
    }
    Bool hoisted__Bool_3331 = 0;
    (void)hoisted__Bool_3331;
    NodeType_delete(&self->node_type, hoisted__Bool_3331);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3381 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3381->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3381->children = *_ca; free(_ca); }
    hoisted__Expr_3381->line = line;
    hoisted__Expr_3381->col = col;
    (void)hoisted__Expr_3381;
    return hoisted__Expr_3381;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3390 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3390->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3390->children = *_ca; free(_ca); }
    hoisted__Expr_3390->line = self->line;
    hoisted__Expr_3390->col = self->col;
    (void)hoisted__Expr_3390;
    return hoisted__Expr_3390;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3391 = 0;
    (void)hoisted__U32_3391;
    U64 hoisted__U64_3392 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3391); });
    (void)hoisted__U64_3392;
    return hoisted__U64_3392;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3393 = 144;
    (void)hoisted__U32_3393;
    return hoisted__U32_3393;
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_4337 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_4337->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_4337->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4337;
    return hoisted__Map__I64_Str_4337;
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_4450 = 0;
    (void)hoisted__Bool_4450;
    Vec__I64_delete(&self->keys, hoisted__Bool_4450);
    Bool hoisted__Bool_4451 = 0;
    (void)hoisted__Bool_4451;
    Vec__Str_delete(&self->values, hoisted__Bool_4451);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_4452 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_4452->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_4452->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_4452;
    return hoisted__Map__I64_Str_4452;
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_4453 = 0;
    (void)hoisted__U32_4453;
    U64 hoisted__U64_4454 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4453); });
    (void)hoisted__U64_4454;
    return hoisted__U64_4454;
}

U32 Map__I64_Str_size(void) {
    U32 hoisted__U32_4455 = 32;
    (void)hoisted__U32_4455;
    return hoisted__U32_4455;
}

Vec__Bool * Vec__Bool_new(void) {
    U32 hoisted__U32_4456 = 1;
    (void)hoisted__U32_4456;
    U64 hoisted__U64_4457 = (U64)(hoisted__U32_4456);
    (void)hoisted__U64_4457;
    void * hoisted__v_4458 = malloc(hoisted__U64_4457);
    (void)hoisted__v_4458;
    U32 hoisted__U32_4459 = 0;
    (void)hoisted__U32_4459;
    I64 hoisted__I64_4460 = 1;
    (void)hoisted__I64_4460;
    Vec__Bool *hoisted__Vec__Bool_4461 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4461->data = hoisted__v_4458;
    hoisted__Vec__Bool_4461->count = hoisted__U32_4459;
    hoisted__Vec__Bool_4461->cap = hoisted__I64_4460;
    (void)hoisted__Vec__Bool_4461;
    return hoisted__Vec__Bool_4461;
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_4471 = self->count;
        (void)_re_U32_4471;
        U32 _rc_U32_4471 = 0;
        (void)_rc_U32_4471;
        Bool hoisted__Bool_4484 = ((Bool)(_rc_U32_4471 <= _re_U32_4471));
        (void)hoisted__Bool_4484;
        if (hoisted__Bool_4484) {
            while (1) {
                Bool _wcond_Bool_4472 = ((Bool)(_rc_U32_4471 < _re_U32_4471));
                (void)_wcond_Bool_4472;
                if (_wcond_Bool_4472) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4471);
                U32_inc(&_rc_U32_4471);
                U32 hoisted__U32_4473 = 1;
                (void)hoisted__U32_4473;
                U32 hoisted__U32_4474 = ((U32)(i * hoisted__U32_4473));
                (void)hoisted__U32_4474;
                U64 hoisted__U64_4475 = (U64)(hoisted__U32_4474);
                (void)hoisted__U64_4475;
                Bool *hoisted__Bool_4476 = ptr_add(self->data, hoisted__U64_4475);
                (void)hoisted__Bool_4476;
                (void)hoisted__Bool_4476;
                Bool hoisted__Bool_4477 = 0;
                (void)hoisted__Bool_4477;
                Bool_delete(hoisted__Bool_4476, hoisted__Bool_4477);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4478 = ((Bool)(_rc_U32_4471 > _re_U32_4471));
                (void)_wcond_Bool_4478;
                if (_wcond_Bool_4478) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4471);
                U32_dec(&_rc_U32_4471);
                U32 hoisted__U32_4479 = 1;
                (void)hoisted__U32_4479;
                U32 hoisted__U32_4480 = ((U32)(i * hoisted__U32_4479));
                (void)hoisted__U32_4480;
                U64 hoisted__U64_4481 = (U64)(hoisted__U32_4480);
                (void)hoisted__U64_4481;
                Bool *hoisted__Bool_4482 = ptr_add(self->data, hoisted__U64_4481);
                (void)hoisted__Bool_4482;
                (void)hoisted__Bool_4482;
                Bool hoisted__Bool_4483 = 0;
                (void)hoisted__Bool_4483;
                Bool_delete(hoisted__Bool_4482, hoisted__Bool_4483);
            }
        }
    }
    U32 hoisted__U32_4485 = 0;
    (void)hoisted__U32_4485;
    self->count = hoisted__U32_4485;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4755 = 1;
    (void)hoisted__U32_4755;
    U32 hoisted__U32_4756 = ((U32)(self->cap * hoisted__U32_4755));
    (void)hoisted__U32_4756;
    U64 hoisted__U64_4757 = (U64)(hoisted__U32_4756);
    (void)hoisted__U64_4757;
    void * new_data = malloc(hoisted__U64_4757);
    {
        U32 _re_U32_4727 = self->count;
        (void)_re_U32_4727;
        U32 _rc_U32_4727 = 0;
        (void)_rc_U32_4727;
        Bool hoisted__Bool_4754 = ((Bool)(_rc_U32_4727 <= _re_U32_4727));
        (void)hoisted__Bool_4754;
        if (hoisted__Bool_4754) {
            while (1) {
                Bool _wcond_Bool_4728 = ((Bool)(_rc_U32_4727 < _re_U32_4727));
                (void)_wcond_Bool_4728;
                if (_wcond_Bool_4728) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4727);
                U32_inc(&_rc_U32_4727);
                U32 hoisted__U32_4729 = 1;
                (void)hoisted__U32_4729;
                U32 hoisted__U32_4730 = ((U32)(i * hoisted__U32_4729));
                (void)hoisted__U32_4730;
                U64 hoisted__U64_4731 = (U64)(hoisted__U32_4730);
                (void)hoisted__U64_4731;
                Bool *src = ptr_add(self->data, hoisted__U64_4731);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4732 = 1;
                (void)hoisted__U32_4732;
                U32 hoisted__U32_4733 = ((U32)(i * hoisted__U32_4732));
                (void)hoisted__U32_4733;
                U64 hoisted__U64_4734 = (U64)(hoisted__U32_4733);
                (void)hoisted__U64_4734;
                U32 hoisted__U32_4735 = 1;
                (void)hoisted__U32_4735;
                void *hoisted__v_4736 = ptr_add(new_data, hoisted__U64_4734);
                (void)hoisted__v_4736;
                (void)hoisted__v_4736;
                U64 hoisted__U64_4737 = (U64)(hoisted__U32_4735);
                (void)hoisted__U64_4737;
                memcpy(hoisted__v_4736, &cloned, hoisted__U64_4737);
                U32 hoisted__U32_4738 = 1;
                (void)hoisted__U32_4738;
                I32 hoisted__I32_4739 = 0;
                (void)hoisted__I32_4739;
                U64 hoisted__U64_4740 = (U64)(hoisted__U32_4738);
                (void)hoisted__U64_4740;
                memset(&cloned, hoisted__I32_4739, hoisted__U64_4740);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4741 = ((Bool)(_rc_U32_4727 > _re_U32_4727));
                (void)_wcond_Bool_4741;
                if (_wcond_Bool_4741) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_4727);
                U32_dec(&_rc_U32_4727);
                U32 hoisted__U32_4742 = 1;
                (void)hoisted__U32_4742;
                U32 hoisted__U32_4743 = ((U32)(i * hoisted__U32_4742));
                (void)hoisted__U32_4743;
                U64 hoisted__U64_4744 = (U64)(hoisted__U32_4743);
                (void)hoisted__U64_4744;
                Bool *src = ptr_add(self->data, hoisted__U64_4744);
                Bool cloned = Bool_clone(src);
                U32 hoisted__U32_4745 = 1;
                (void)hoisted__U32_4745;
                U32 hoisted__U32_4746 = ((U32)(i * hoisted__U32_4745));
                (void)hoisted__U32_4746;
                U64 hoisted__U64_4747 = (U64)(hoisted__U32_4746);
                (void)hoisted__U64_4747;
                U32 hoisted__U32_4748 = 1;
                (void)hoisted__U32_4748;
                void *hoisted__v_4749 = ptr_add(new_data, hoisted__U64_4747);
                (void)hoisted__v_4749;
                (void)hoisted__v_4749;
                U64 hoisted__U64_4750 = (U64)(hoisted__U32_4748);
                (void)hoisted__U64_4750;
                memcpy(hoisted__v_4749, &cloned, hoisted__U64_4750);
                U32 hoisted__U32_4751 = 1;
                (void)hoisted__U32_4751;
                I32 hoisted__I32_4752 = 0;
                (void)hoisted__I32_4752;
                U64 hoisted__U64_4753 = (U64)(hoisted__U32_4751);
                (void)hoisted__U64_4753;
                memset(&cloned, hoisted__I32_4752, hoisted__U64_4753);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4758 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4758->data = new_data;
    hoisted__Vec__Bool_4758->count = self->count;
    hoisted__Vec__Bool_4758->cap = self->cap;
    (void)hoisted__Vec__Bool_4758;
    return hoisted__Vec__Bool_4758;
}

U32 Vec__Bool_size(void) {
    U32 hoisted__U32_4759 = 16;
    (void)hoisted__U32_4759;
    return hoisted__U32_4759;
}

Vec__Declaration * Vec__Declaration_new(void) {
    U32 hoisted__U32_5064 = 104;
    (void)hoisted__U32_5064;
    U64 hoisted__U64_5065 = (U64)(hoisted__U32_5064);
    (void)hoisted__U64_5065;
    void * hoisted__v_5066 = malloc(hoisted__U64_5065);
    (void)hoisted__v_5066;
    U32 hoisted__U32_5067 = 0;
    (void)hoisted__U32_5067;
    I64 hoisted__I64_5068 = 1;
    (void)hoisted__I64_5068;
    Vec__Declaration *hoisted__Vec__Declaration_5069 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5069->data = hoisted__v_5066;
    hoisted__Vec__Declaration_5069->count = hoisted__U32_5067;
    hoisted__Vec__Declaration_5069->cap = hoisted__I64_5068;
    (void)hoisted__Vec__Declaration_5069;
    return hoisted__Vec__Declaration_5069;
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_5079 = self->count;
        (void)_re_U32_5079;
        U32 _rc_U32_5079 = 0;
        (void)_rc_U32_5079;
        Bool hoisted__Bool_5092 = ((Bool)(_rc_U32_5079 <= _re_U32_5079));
        (void)hoisted__Bool_5092;
        if (hoisted__Bool_5092) {
            while (1) {
                Bool _wcond_Bool_5080 = ((Bool)(_rc_U32_5079 < _re_U32_5079));
                (void)_wcond_Bool_5080;
                if (_wcond_Bool_5080) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5079);
                U32_inc(&_rc_U32_5079);
                U32 hoisted__U32_5081 = 104;
                (void)hoisted__U32_5081;
                U32 hoisted__U32_5082 = ((U32)(i * hoisted__U32_5081));
                (void)hoisted__U32_5082;
                U64 hoisted__U64_5083 = (U64)(hoisted__U32_5082);
                (void)hoisted__U64_5083;
                Declaration *hoisted__Declaration_5084 = ptr_add(self->data, hoisted__U64_5083);
                (void)hoisted__Declaration_5084;
                (void)hoisted__Declaration_5084;
                Bool hoisted__Bool_5085 = 0;
                (void)hoisted__Bool_5085;
                Declaration_delete(hoisted__Declaration_5084, hoisted__Bool_5085);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5086 = ((Bool)(_rc_U32_5079 > _re_U32_5079));
                (void)_wcond_Bool_5086;
                if (_wcond_Bool_5086) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5079);
                U32_dec(&_rc_U32_5079);
                U32 hoisted__U32_5087 = 104;
                (void)hoisted__U32_5087;
                U32 hoisted__U32_5088 = ((U32)(i * hoisted__U32_5087));
                (void)hoisted__U32_5088;
                U64 hoisted__U64_5089 = (U64)(hoisted__U32_5088);
                (void)hoisted__U64_5089;
                Declaration *hoisted__Declaration_5090 = ptr_add(self->data, hoisted__U64_5089);
                (void)hoisted__Declaration_5090;
                (void)hoisted__Declaration_5090;
                Bool hoisted__Bool_5091 = 0;
                (void)hoisted__Bool_5091;
                Declaration_delete(hoisted__Declaration_5090, hoisted__Bool_5091);
            }
        }
    }
    U32 hoisted__U32_5093 = 0;
    (void)hoisted__U32_5093;
    self->count = hoisted__U32_5093;
}

void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free) {
    Vec__Declaration_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self) {
    U32 hoisted__U32_5363 = 104;
    (void)hoisted__U32_5363;
    U32 hoisted__U32_5364 = ((U32)(self->cap * hoisted__U32_5363));
    (void)hoisted__U32_5364;
    U64 hoisted__U64_5365 = (U64)(hoisted__U32_5364);
    (void)hoisted__U64_5365;
    void * new_data = malloc(hoisted__U64_5365);
    {
        U32 _re_U32_5335 = self->count;
        (void)_re_U32_5335;
        U32 _rc_U32_5335 = 0;
        (void)_rc_U32_5335;
        Bool hoisted__Bool_5362 = ((Bool)(_rc_U32_5335 <= _re_U32_5335));
        (void)hoisted__Bool_5362;
        if (hoisted__Bool_5362) {
            while (1) {
                Bool _wcond_Bool_5336 = ((Bool)(_rc_U32_5335 < _re_U32_5335));
                (void)_wcond_Bool_5336;
                if (_wcond_Bool_5336) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5335);
                U32_inc(&_rc_U32_5335);
                U32 hoisted__U32_5337 = 104;
                (void)hoisted__U32_5337;
                U32 hoisted__U32_5338 = ((U32)(i * hoisted__U32_5337));
                (void)hoisted__U32_5338;
                U64 hoisted__U64_5339 = (U64)(hoisted__U32_5338);
                (void)hoisted__U64_5339;
                Declaration *src = ptr_add(self->data, hoisted__U64_5339);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5340 = 104;
                (void)hoisted__U32_5340;
                U32 hoisted__U32_5341 = ((U32)(i * hoisted__U32_5340));
                (void)hoisted__U32_5341;
                U64 hoisted__U64_5342 = (U64)(hoisted__U32_5341);
                (void)hoisted__U64_5342;
                U32 hoisted__U32_5343 = 104;
                (void)hoisted__U32_5343;
                void *hoisted__v_5344 = ptr_add(new_data, hoisted__U64_5342);
                (void)hoisted__v_5344;
                (void)hoisted__v_5344;
                U64 hoisted__U64_5345 = (U64)(hoisted__U32_5343);
                (void)hoisted__U64_5345;
                memcpy(hoisted__v_5344, cloned, hoisted__U64_5345);
                U32 hoisted__U32_5346 = 104;
                (void)hoisted__U32_5346;
                I32 hoisted__I32_5347 = 0;
                (void)hoisted__I32_5347;
                U64 hoisted__U64_5348 = (U64)(hoisted__U32_5346);
                (void)hoisted__U64_5348;
                memset(cloned, hoisted__I32_5347, hoisted__U64_5348);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5349 = ((Bool)(_rc_U32_5335 > _re_U32_5335));
                (void)_wcond_Bool_5349;
                if (_wcond_Bool_5349) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5335);
                U32_dec(&_rc_U32_5335);
                U32 hoisted__U32_5350 = 104;
                (void)hoisted__U32_5350;
                U32 hoisted__U32_5351 = ((U32)(i * hoisted__U32_5350));
                (void)hoisted__U32_5351;
                U64 hoisted__U64_5352 = (U64)(hoisted__U32_5351);
                (void)hoisted__U64_5352;
                Declaration *src = ptr_add(self->data, hoisted__U64_5352);
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_5353 = 104;
                (void)hoisted__U32_5353;
                U32 hoisted__U32_5354 = ((U32)(i * hoisted__U32_5353));
                (void)hoisted__U32_5354;
                U64 hoisted__U64_5355 = (U64)(hoisted__U32_5354);
                (void)hoisted__U64_5355;
                U32 hoisted__U32_5356 = 104;
                (void)hoisted__U32_5356;
                void *hoisted__v_5357 = ptr_add(new_data, hoisted__U64_5355);
                (void)hoisted__v_5357;
                (void)hoisted__v_5357;
                U64 hoisted__U64_5358 = (U64)(hoisted__U32_5356);
                (void)hoisted__U64_5358;
                memcpy(hoisted__v_5357, cloned, hoisted__U64_5358);
                U32 hoisted__U32_5359 = 104;
                (void)hoisted__U32_5359;
                I32 hoisted__I32_5360 = 0;
                (void)hoisted__I32_5360;
                U64 hoisted__U64_5361 = (U64)(hoisted__U32_5359);
                (void)hoisted__U64_5361;
                memset(cloned, hoisted__I32_5360, hoisted__U64_5361);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_5366 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_5366->data = new_data;
    hoisted__Vec__Declaration_5366->count = self->count;
    hoisted__Vec__Declaration_5366->cap = self->cap;
    (void)hoisted__Vec__Declaration_5366;
    return hoisted__Vec__Declaration_5366;
}

U32 Vec__Declaration_size(void) {
    U32 hoisted__U32_5367 = 16;
    (void)hoisted__U32_5367;
    return hoisted__U32_5367;
}

Vec__Expr * Vec__Expr_new(void) {
    U32 hoisted__U32_5368 = 144;
    (void)hoisted__U32_5368;
    U64 hoisted__U64_5369 = (U64)(hoisted__U32_5368);
    (void)hoisted__U64_5369;
    void * hoisted__v_5370 = malloc(hoisted__U64_5369);
    (void)hoisted__v_5370;
    U32 hoisted__U32_5371 = 0;
    (void)hoisted__U32_5371;
    I64 hoisted__I64_5372 = 1;
    (void)hoisted__I64_5372;
    Vec__Expr *hoisted__Vec__Expr_5373 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5373->data = hoisted__v_5370;
    hoisted__Vec__Expr_5373->count = hoisted__U32_5371;
    hoisted__Vec__Expr_5373->cap = hoisted__I64_5372;
    (void)hoisted__Vec__Expr_5373;
    return hoisted__Vec__Expr_5373;
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_5383 = self->count;
        (void)_re_U32_5383;
        U32 _rc_U32_5383 = 0;
        (void)_rc_U32_5383;
        Bool hoisted__Bool_5396 = ((Bool)(_rc_U32_5383 <= _re_U32_5383));
        (void)hoisted__Bool_5396;
        if (hoisted__Bool_5396) {
            while (1) {
                Bool _wcond_Bool_5384 = ((Bool)(_rc_U32_5383 < _re_U32_5383));
                (void)_wcond_Bool_5384;
                if (_wcond_Bool_5384) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5383);
                U32_inc(&_rc_U32_5383);
                U32 hoisted__U32_5385 = 144;
                (void)hoisted__U32_5385;
                U32 hoisted__U32_5386 = ((U32)(i * hoisted__U32_5385));
                (void)hoisted__U32_5386;
                U64 hoisted__U64_5387 = (U64)(hoisted__U32_5386);
                (void)hoisted__U64_5387;
                Expr *hoisted__Expr_5388 = ptr_add(self->data, hoisted__U64_5387);
                (void)hoisted__Expr_5388;
                (void)hoisted__Expr_5388;
                Bool hoisted__Bool_5389 = 0;
                (void)hoisted__Bool_5389;
                Expr_delete(hoisted__Expr_5388, hoisted__Bool_5389);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5390 = ((Bool)(_rc_U32_5383 > _re_U32_5383));
                (void)_wcond_Bool_5390;
                if (_wcond_Bool_5390) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5383);
                U32_dec(&_rc_U32_5383);
                U32 hoisted__U32_5391 = 144;
                (void)hoisted__U32_5391;
                U32 hoisted__U32_5392 = ((U32)(i * hoisted__U32_5391));
                (void)hoisted__U32_5392;
                U64 hoisted__U64_5393 = (U64)(hoisted__U32_5392);
                (void)hoisted__U64_5393;
                Expr *hoisted__Expr_5394 = ptr_add(self->data, hoisted__U64_5393);
                (void)hoisted__Expr_5394;
                (void)hoisted__Expr_5394;
                Bool hoisted__Bool_5395 = 0;
                (void)hoisted__Bool_5395;
                Expr_delete(hoisted__Expr_5394, hoisted__Bool_5395);
            }
        }
    }
    U32 hoisted__U32_5397 = 0;
    (void)hoisted__U32_5397;
    self->count = hoisted__U32_5397;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5667 = 144;
    (void)hoisted__U32_5667;
    U32 hoisted__U32_5668 = ((U32)(self->cap * hoisted__U32_5667));
    (void)hoisted__U32_5668;
    U64 hoisted__U64_5669 = (U64)(hoisted__U32_5668);
    (void)hoisted__U64_5669;
    void * new_data = malloc(hoisted__U64_5669);
    {
        U32 _re_U32_5639 = self->count;
        (void)_re_U32_5639;
        U32 _rc_U32_5639 = 0;
        (void)_rc_U32_5639;
        Bool hoisted__Bool_5666 = ((Bool)(_rc_U32_5639 <= _re_U32_5639));
        (void)hoisted__Bool_5666;
        if (hoisted__Bool_5666) {
            while (1) {
                Bool _wcond_Bool_5640 = ((Bool)(_rc_U32_5639 < _re_U32_5639));
                (void)_wcond_Bool_5640;
                if (_wcond_Bool_5640) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5639);
                U32_inc(&_rc_U32_5639);
                U32 hoisted__U32_5641 = 144;
                (void)hoisted__U32_5641;
                U32 hoisted__U32_5642 = ((U32)(i * hoisted__U32_5641));
                (void)hoisted__U32_5642;
                U64 hoisted__U64_5643 = (U64)(hoisted__U32_5642);
                (void)hoisted__U64_5643;
                Expr *src = ptr_add(self->data, hoisted__U64_5643);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5644 = 144;
                (void)hoisted__U32_5644;
                U32 hoisted__U32_5645 = ((U32)(i * hoisted__U32_5644));
                (void)hoisted__U32_5645;
                U64 hoisted__U64_5646 = (U64)(hoisted__U32_5645);
                (void)hoisted__U64_5646;
                U32 hoisted__U32_5647 = 144;
                (void)hoisted__U32_5647;
                void *hoisted__v_5648 = ptr_add(new_data, hoisted__U64_5646);
                (void)hoisted__v_5648;
                (void)hoisted__v_5648;
                U64 hoisted__U64_5649 = (U64)(hoisted__U32_5647);
                (void)hoisted__U64_5649;
                memcpy(hoisted__v_5648, cloned, hoisted__U64_5649);
                U32 hoisted__U32_5650 = 144;
                (void)hoisted__U32_5650;
                I32 hoisted__I32_5651 = 0;
                (void)hoisted__I32_5651;
                U64 hoisted__U64_5652 = (U64)(hoisted__U32_5650);
                (void)hoisted__U64_5652;
                memset(cloned, hoisted__I32_5651, hoisted__U64_5652);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5653 = ((Bool)(_rc_U32_5639 > _re_U32_5639));
                (void)_wcond_Bool_5653;
                if (_wcond_Bool_5653) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5639);
                U32_dec(&_rc_U32_5639);
                U32 hoisted__U32_5654 = 144;
                (void)hoisted__U32_5654;
                U32 hoisted__U32_5655 = ((U32)(i * hoisted__U32_5654));
                (void)hoisted__U32_5655;
                U64 hoisted__U64_5656 = (U64)(hoisted__U32_5655);
                (void)hoisted__U64_5656;
                Expr *src = ptr_add(self->data, hoisted__U64_5656);
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5657 = 144;
                (void)hoisted__U32_5657;
                U32 hoisted__U32_5658 = ((U32)(i * hoisted__U32_5657));
                (void)hoisted__U32_5658;
                U64 hoisted__U64_5659 = (U64)(hoisted__U32_5658);
                (void)hoisted__U64_5659;
                U32 hoisted__U32_5660 = 144;
                (void)hoisted__U32_5660;
                void *hoisted__v_5661 = ptr_add(new_data, hoisted__U64_5659);
                (void)hoisted__v_5661;
                (void)hoisted__v_5661;
                U64 hoisted__U64_5662 = (U64)(hoisted__U32_5660);
                (void)hoisted__U64_5662;
                memcpy(hoisted__v_5661, cloned, hoisted__U64_5662);
                U32 hoisted__U32_5663 = 144;
                (void)hoisted__U32_5663;
                I32 hoisted__I32_5664 = 0;
                (void)hoisted__I32_5664;
                U64 hoisted__U64_5665 = (U64)(hoisted__U32_5663);
                (void)hoisted__U64_5665;
                memset(cloned, hoisted__I32_5664, hoisted__U64_5665);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5670 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5670->data = new_data;
    hoisted__Vec__Expr_5670->count = self->count;
    hoisted__Vec__Expr_5670->cap = self->cap;
    (void)hoisted__Vec__Expr_5670;
    return hoisted__Vec__Expr_5670;
}

U32 Vec__Expr_size(void) {
    U32 hoisted__U32_5671 = 16;
    (void)hoisted__U32_5671;
    return hoisted__U32_5671;
}

Vec__I64 * Vec__I64_new(void) {
    U32 hoisted__U32_5672 = 8;
    (void)hoisted__U32_5672;
    U64 hoisted__U64_5673 = (U64)(hoisted__U32_5672);
    (void)hoisted__U64_5673;
    void * hoisted__v_5674 = malloc(hoisted__U64_5673);
    (void)hoisted__v_5674;
    U32 hoisted__U32_5675 = 0;
    (void)hoisted__U32_5675;
    I64 hoisted__I64_5676 = 1;
    (void)hoisted__I64_5676;
    Vec__I64 *hoisted__Vec__I64_5677 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5677->data = hoisted__v_5674;
    hoisted__Vec__I64_5677->count = hoisted__U32_5675;
    hoisted__Vec__I64_5677->cap = hoisted__I64_5676;
    (void)hoisted__Vec__I64_5677;
    return hoisted__Vec__I64_5677;
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_5687 = self->count;
        (void)_re_U32_5687;
        U32 _rc_U32_5687 = 0;
        (void)_rc_U32_5687;
        Bool hoisted__Bool_5700 = ((Bool)(_rc_U32_5687 <= _re_U32_5687));
        (void)hoisted__Bool_5700;
        if (hoisted__Bool_5700) {
            while (1) {
                Bool _wcond_Bool_5688 = ((Bool)(_rc_U32_5687 < _re_U32_5687));
                (void)_wcond_Bool_5688;
                if (_wcond_Bool_5688) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5687);
                U32_inc(&_rc_U32_5687);
                U32 hoisted__U32_5689 = 8;
                (void)hoisted__U32_5689;
                U32 hoisted__U32_5690 = ((U32)(i * hoisted__U32_5689));
                (void)hoisted__U32_5690;
                U64 hoisted__U64_5691 = (U64)(hoisted__U32_5690);
                (void)hoisted__U64_5691;
                I64 *hoisted__I64_5692 = ptr_add(self->data, hoisted__U64_5691);
                (void)hoisted__I64_5692;
                (void)hoisted__I64_5692;
                Bool hoisted__Bool_5693 = 0;
                (void)hoisted__Bool_5693;
                I64_delete(hoisted__I64_5692, hoisted__Bool_5693);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5694 = ((Bool)(_rc_U32_5687 > _re_U32_5687));
                (void)_wcond_Bool_5694;
                if (_wcond_Bool_5694) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5687);
                U32_dec(&_rc_U32_5687);
                U32 hoisted__U32_5695 = 8;
                (void)hoisted__U32_5695;
                U32 hoisted__U32_5696 = ((U32)(i * hoisted__U32_5695));
                (void)hoisted__U32_5696;
                U64 hoisted__U64_5697 = (U64)(hoisted__U32_5696);
                (void)hoisted__U64_5697;
                I64 *hoisted__I64_5698 = ptr_add(self->data, hoisted__U64_5697);
                (void)hoisted__I64_5698;
                (void)hoisted__I64_5698;
                Bool hoisted__Bool_5699 = 0;
                (void)hoisted__Bool_5699;
                I64_delete(hoisted__I64_5698, hoisted__Bool_5699);
            }
        }
    }
    U32 hoisted__U32_5701 = 0;
    (void)hoisted__U32_5701;
    self->count = hoisted__U32_5701;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_5971 = 8;
    (void)hoisted__U32_5971;
    U32 hoisted__U32_5972 = ((U32)(self->cap * hoisted__U32_5971));
    (void)hoisted__U32_5972;
    U64 hoisted__U64_5973 = (U64)(hoisted__U32_5972);
    (void)hoisted__U64_5973;
    void * new_data = malloc(hoisted__U64_5973);
    {
        U32 _re_U32_5943 = self->count;
        (void)_re_U32_5943;
        U32 _rc_U32_5943 = 0;
        (void)_rc_U32_5943;
        Bool hoisted__Bool_5970 = ((Bool)(_rc_U32_5943 <= _re_U32_5943));
        (void)hoisted__Bool_5970;
        if (hoisted__Bool_5970) {
            while (1) {
                Bool _wcond_Bool_5944 = ((Bool)(_rc_U32_5943 < _re_U32_5943));
                (void)_wcond_Bool_5944;
                if (_wcond_Bool_5944) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5943);
                U32_inc(&_rc_U32_5943);
                U32 hoisted__U32_5945 = 8;
                (void)hoisted__U32_5945;
                U32 hoisted__U32_5946 = ((U32)(i * hoisted__U32_5945));
                (void)hoisted__U32_5946;
                U64 hoisted__U64_5947 = (U64)(hoisted__U32_5946);
                (void)hoisted__U64_5947;
                I64 *src = ptr_add(self->data, hoisted__U64_5947);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5948 = 8;
                (void)hoisted__U32_5948;
                U32 hoisted__U32_5949 = ((U32)(i * hoisted__U32_5948));
                (void)hoisted__U32_5949;
                U64 hoisted__U64_5950 = (U64)(hoisted__U32_5949);
                (void)hoisted__U64_5950;
                U32 hoisted__U32_5951 = 8;
                (void)hoisted__U32_5951;
                void *hoisted__v_5952 = ptr_add(new_data, hoisted__U64_5950);
                (void)hoisted__v_5952;
                (void)hoisted__v_5952;
                U64 hoisted__U64_5953 = (U64)(hoisted__U32_5951);
                (void)hoisted__U64_5953;
                memcpy(hoisted__v_5952, &cloned, hoisted__U64_5953);
                U32 hoisted__U32_5954 = 8;
                (void)hoisted__U32_5954;
                I32 hoisted__I32_5955 = 0;
                (void)hoisted__I32_5955;
                U64 hoisted__U64_5956 = (U64)(hoisted__U32_5954);
                (void)hoisted__U64_5956;
                memset(&cloned, hoisted__I32_5955, hoisted__U64_5956);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5957 = ((Bool)(_rc_U32_5943 > _re_U32_5943));
                (void)_wcond_Bool_5957;
                if (_wcond_Bool_5957) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_5943);
                U32_dec(&_rc_U32_5943);
                U32 hoisted__U32_5958 = 8;
                (void)hoisted__U32_5958;
                U32 hoisted__U32_5959 = ((U32)(i * hoisted__U32_5958));
                (void)hoisted__U32_5959;
                U64 hoisted__U64_5960 = (U64)(hoisted__U32_5959);
                (void)hoisted__U64_5960;
                I64 *src = ptr_add(self->data, hoisted__U64_5960);
                I64 cloned = I64_clone(src);
                U32 hoisted__U32_5961 = 8;
                (void)hoisted__U32_5961;
                U32 hoisted__U32_5962 = ((U32)(i * hoisted__U32_5961));
                (void)hoisted__U32_5962;
                U64 hoisted__U64_5963 = (U64)(hoisted__U32_5962);
                (void)hoisted__U64_5963;
                U32 hoisted__U32_5964 = 8;
                (void)hoisted__U32_5964;
                void *hoisted__v_5965 = ptr_add(new_data, hoisted__U64_5963);
                (void)hoisted__v_5965;
                (void)hoisted__v_5965;
                U64 hoisted__U64_5966 = (U64)(hoisted__U32_5964);
                (void)hoisted__U64_5966;
                memcpy(hoisted__v_5965, &cloned, hoisted__U64_5966);
                U32 hoisted__U32_5967 = 8;
                (void)hoisted__U32_5967;
                I32 hoisted__I32_5968 = 0;
                (void)hoisted__I32_5968;
                U64 hoisted__U64_5969 = (U64)(hoisted__U32_5967);
                (void)hoisted__U64_5969;
                memset(&cloned, hoisted__I32_5968, hoisted__U64_5969);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_5974 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_5974->data = new_data;
    hoisted__Vec__I64_5974->count = self->count;
    hoisted__Vec__I64_5974->cap = self->cap;
    (void)hoisted__Vec__I64_5974;
    return hoisted__Vec__I64_5974;
}

U32 Vec__I64_size(void) {
    U32 hoisted__U32_5975 = 16;
    (void)hoisted__U32_5975;
    return hoisted__U32_5975;
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_7094 = 3;
    (void)hoisted__U32_7094;
    Array__Str *_va_Array_201 = Array__Str_new(hoisted__U32_7094);
    (void)_va_Array_201;
    I64 _va_Array_201_ek = 0;
    (void)_va_Array_201_ek;
    OutOfBounds *_va_Array_201_eo = malloc(sizeof(OutOfBounds));
    _va_Array_201_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_201_eo;
    U32 hoisted__U32_7095 = 0;
    (void)hoisted__U32_7095;
    Str *hoisted__Str_7096 = Str_clone(loc);
    (void)hoisted__Str_7096;
    (void)hoisted__Str_7097;
    (void)hoisted__Str_7097;
    Array__Str_set(_va_Array_201, hoisted__U32_7095, hoisted__Str_7096, &_va_Array_201_ek, _va_Array_201_eo, &hoisted__Str_7097);
    Str_delete(&hoisted__Str_7097, (Bool){0});
    U32 hoisted__U32_7098 = 1;
    (void)hoisted__U32_7098;
    (void)hoisted__Str_7099;
    (void)hoisted__Str_7099;
    (void)hoisted__Str_7100;
    (void)hoisted__Str_7100;
    Array__Str_set(_va_Array_201, hoisted__U32_7098, &hoisted__Str_7099, &_va_Array_201_ek, _va_Array_201_eo, &hoisted__Str_7100);
    Str_delete(&hoisted__Str_7100, (Bool){0});
    Array__Str *hoisted__Array__Str_7101 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_7101;
    U32 hoisted__U32_7102 = 2;
    (void)hoisted__U32_7102;
    Str *hoisted__Str_7103 = format(hoisted__Array__Str_7101);
    (void)hoisted__Str_7103;
    (void)hoisted__Str_7104;
    (void)hoisted__Str_7104;
    Array__Str_set(_va_Array_201, hoisted__U32_7102, hoisted__Str_7103, &_va_Array_201_ek, _va_Array_201_eo, &hoisted__Str_7104);
    OutOfBounds_delete(_va_Array_201_eo, 1);
    Str_delete(&hoisted__Str_7104, (Bool){0});
    Array__Str_delete(parts, 1);
    println(_va_Array_201);
    I64 hoisted__I64_7105 = 1;
    (void)hoisted__I64_7105;
    exit(hoisted__I64_7105);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_7114 = 1;
    (void)hoisted__U32_7114;
    Array__Str *_va_Array_203 = Array__Str_new(hoisted__U32_7114);
    (void)_va_Array_203;
    I64 _va_Array_203_ek = 0;
    (void)_va_Array_203_ek;
    OutOfBounds *_va_Array_203_eo = malloc(sizeof(OutOfBounds));
    _va_Array_203_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)_va_Array_203_eo;
    U32 hoisted__U32_7115 = 0;
    (void)hoisted__U32_7115;
    (void)hoisted__Str_7116;
    (void)hoisted__Str_7116;
    (void)hoisted__Str_7117;
    (void)hoisted__Str_7117;
    Array__Str_set(_va_Array_203, hoisted__U32_7115, &hoisted__Str_7116, &_va_Array_203_ek, _va_Array_203_eo, &hoisted__Str_7117);
    OutOfBounds_delete(_va_Array_203_eo, 1);
    Str_delete(&hoisted__Str_7117, (Bool){0});
    panic(_va_Array_203, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_7122 = not(cond);
    (void)hoisted__Bool_7122;
    if (hoisted__Bool_7122) {
        U32 hoisted__U32_7118 = 1;
        (void)hoisted__U32_7118;
        Array__Str *_va_Array_204 = Array__Str_new(hoisted__U32_7118);
        (void)_va_Array_204;
        I64 _va_Array_204_ek = 0;
        (void)_va_Array_204_ek;
        OutOfBounds *_va_Array_204_eo = malloc(sizeof(OutOfBounds));
        _va_Array_204_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_204_eo;
        U32 hoisted__U32_7119 = 0;
        (void)hoisted__U32_7119;
        (void)hoisted__Str_7120;
        (void)hoisted__Str_7120;
        (void)hoisted__Str_7121;
        (void)hoisted__Str_7121;
        Array__Str_set(_va_Array_204, hoisted__U32_7119, &hoisted__Str_7120, &_va_Array_204_ek, _va_Array_204_eo, &hoisted__Str_7121);
        OutOfBounds_delete(_va_Array_204_eo, 1);
        Str_delete(&hoisted__Str_7121, (Bool){0});
        panic(_va_Array_204, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_7132 = parts;
        (void)_fc_Array__Str_7132;
        (void)_fc_Array__Str_7132;
        U32 _fi_USize_7132 = 0;
        (void)_fi_USize_7132;
        while (1) {
            U32 hoisted__U32_7134 = Array__Str_len(_fc_Array__Str_7132);
            (void)hoisted__U32_7134;
            Bool _wcond_Bool_7133 = ((Bool)(_fi_USize_7132 < hoisted__U32_7134));
            (void)_wcond_Bool_7133;
            if (_wcond_Bool_7133) {
            } else {
                break;
            }
            Str *s = Array__Str_unsafe_get(_fc_Array__Str_7132, &_fi_USize_7132);
            U32 hoisted__U32_7135 = 1;
            (void)hoisted__U32_7135;
            U32 hoisted__U32_7136 = ((U32)(_fi_USize_7132 + hoisted__U32_7135));
            (void)hoisted__U32_7136;
            _fi_USize_7132 = hoisted__U32_7136;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_7170 = ptr_eq(p, NULL);
    (void)hoisted__Bool_7170;
    return hoisted__Bool_7170;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_7179 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_7179;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_7179;
    return _r; }
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_7180 = 0;
    (void)hoisted__U32_7180;
    U64 hoisted__U64_7181 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_7180); });
    (void)hoisted__U64_7181;
    return hoisted__U64_7181;
}

U32 Range_size(void) {
    U32 hoisted__U32_7212 = 16;
    (void)hoisted__U32_7212;
    return hoisted__U32_7212;
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_7327 = 3;
    (void)hoisted__I64_7327;
    (void)hoisted__Str_7328;
    (void)hoisted__Str_7328;
    assert_eq__I64(result, hoisted__I64_7327, &hoisted__Str_7328);
    Str_delete(&hoisted__Str_7328, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_7335 = 15;
    (void)hoisted__I64_7335;
    (void)hoisted__Str_7336;
    (void)hoisted__Str_7336;
    assert_eq__I64(result, hoisted__I64_7335, &hoisted__Str_7336);
    Str_delete(&hoisted__Str_7336, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_7343 = 26;
    (void)hoisted__I64_7343;
    (void)hoisted__Str_7344;
    (void)hoisted__Str_7344;
    assert_eq__I64(result, hoisted__I64_7343, &hoisted__Str_7344);
    Str_delete(&hoisted__Str_7344, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7347;
    (void)hoisted__Str_7347;
    (void)hoisted__Str_7348;
    (void)hoisted__Str_7348;
    assert_eq__Str(&result, &hoisted__Str_7347, &hoisted__Str_7348);
    Str_delete(&hoisted__Str_7347, (Bool){0});
    Str_delete(&hoisted__Str_7348, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7376;
    (void)hoisted__Str_7376;
    (void)hoisted__Str_7377;
    (void)hoisted__Str_7377;
    assert_eq__Str(&r, &hoisted__Str_7376, &hoisted__Str_7377);
    Str_delete(&hoisted__Str_7376, (Bool){0});
    Str_delete(&hoisted__Str_7377, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7381;
    (void)hoisted__Str_7381;
    (void)hoisted__Str_7382;
    (void)hoisted__Str_7382;
    assert_eq__Str(&r2, &hoisted__Str_7381, &hoisted__Str_7382);
    Str_delete(&hoisted__Str_7381, (Bool){0});
    Str_delete(&hoisted__Str_7382, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7405;
    (void)hoisted__Str_7405;
    (void)hoisted__Str_7406;
    (void)hoisted__Str_7406;
    assert_eq__Str(&d, &hoisted__Str_7405, &hoisted__Str_7406);
    Str_delete(&d, (Bool){0});
    Str_delete(&hoisted__Str_7405, (Bool){0});
    Str_delete(&hoisted__Str_7406, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_7417;
    (void)hoisted__Str_7417;
    (void)hoisted__Str_7418;
    (void)hoisted__Str_7418;
    assert_eq__Str(&d2, &hoisted__Str_7417, &hoisted__Str_7418);
    Str_delete(&d2, (Bool){0});
    Str_delete(&hoisted__Str_7417, (Bool){0});
    Str_delete(&hoisted__Str_7418, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_7430 = 106;
    (void)hoisted__I64_7430;
    (void)hoisted__Str_7431;
    (void)hoisted__Str_7431;
    assert_eq__I64(d3, hoisted__I64_7430, &hoisted__Str_7431);
    Str_delete(&hoisted__Str_7431, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8030;
    (void)hoisted__Str_8030;
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_8030);
    Str_delete(&hoisted__Str_8030, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)hoisted__Str_8031;
    (void)hoisted__Str_8031;
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_8031);
    Str_delete(&hoisted__Str_8031, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_8033 = 8;
    (void)hoisted__I64_8033;
    (void)hoisted__Str_8034;
    (void)hoisted__Str_8034;
    assert_eq__I64(result, hoisted__I64_8033, &hoisted__Str_8034);
    Str_delete(&hoisted__Str_8034, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_8037 = 1;
    (void)hoisted__Bool_8037;
    (void)hoisted__Str_8038;
    (void)hoisted__Str_8038;
    assert(hoisted__Bool_8037, &hoisted__Str_8038);
    Str_delete(&hoisted__Str_8038, (Bool){0});
    Bool hoisted__Bool_8041 = 1;
    (void)hoisted__Bool_8041;
    (void)hoisted__Str_8042;
    (void)hoisted__Str_8042;
    assert(hoisted__Bool_8041, &hoisted__Str_8042);
    Str_delete(&hoisted__Str_8042, (Bool){0});
}

void test_fold_f32(void) {
    (void)hoisted__Str_8047;
    (void)hoisted__Str_8047;
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8048;
    (void)hoisted__Str_8049;
    (void)hoisted__Str_8049;
    assert_eq__Str(&hoisted__Str_8047, &hoisted__Str_8048, &hoisted__Str_8049);
    Str_delete(&hoisted__Str_8047, (Bool){0});
    Str_delete(&hoisted__Str_8048, (Bool){0});
    Str_delete(&hoisted__Str_8049, (Bool){0});
    (void)hoisted__Str_8052;
    (void)hoisted__Str_8052;
    (void)hoisted__Str_8053;
    (void)hoisted__Str_8053;
    (void)hoisted__Str_8054;
    (void)hoisted__Str_8054;
    assert_eq__Str(&hoisted__Str_8052, &hoisted__Str_8053, &hoisted__Str_8054);
    Str_delete(&hoisted__Str_8052, (Bool){0});
    Str_delete(&hoisted__Str_8053, (Bool){0});
    Str_delete(&hoisted__Str_8054, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_8059 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_8059;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_8059;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_8060 = 0;
    (void)hoisted__U32_8060;
    U64 hoisted__U64_8061 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8060); });
    (void)hoisted__U64_8061;
    return hoisted__U64_8061;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_8092 = 16;
    (void)hoisted__U32_8092;
    return hoisted__U32_8092;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_8093 = 42;
    (void)hoisted__I64_8093;
    (void)hoisted__Str_8094;
    (void)hoisted__Str_8094;
    assert_eq__I64(v.x, hoisted__I64_8093, &hoisted__Str_8094);
    Str_delete(&hoisted__Str_8094, (Bool){0});
    I64 hoisted__I64_8095 = 99;
    (void)hoisted__I64_8095;
    (void)hoisted__Str_8096;
    (void)hoisted__Str_8096;
    assert_eq__I64(v.y, hoisted__I64_8095, &hoisted__Str_8096);
    Str_delete(&hoisted__Str_8096, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_8099 = 10;
    (void)hoisted__I64_8099;
    (void)hoisted__Str_8100;
    (void)hoisted__Str_8100;
    assert_eq__I64(p.x, hoisted__I64_8099, &hoisted__Str_8100);
    Str_delete(&hoisted__Str_8100, (Bool){0});
    I64 hoisted__I64_8101 = 20;
    (void)hoisted__I64_8101;
    (void)hoisted__Str_8102;
    (void)hoisted__Str_8102;
    assert_eq__I64(p.y, hoisted__I64_8101, &hoisted__Str_8102);
    Str_delete(&hoisted__Str_8102, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_8108 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_8108;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_8108;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_8109 = 0;
    (void)hoisted__U32_8109;
    U64 hoisted__U64_8110 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8109); });
    (void)hoisted__U64_8110;
    return hoisted__U64_8110;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_8141 = 32;
    (void)hoisted__U32_8141;
    return hoisted__U32_8141;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_8142 = 5;
    (void)hoisted__I64_8142;
    (void)hoisted__Str_8143;
    (void)hoisted__Str_8143;
    assert_eq__I64(r.top_left.x, hoisted__I64_8142, &hoisted__Str_8143);
    Str_delete(&hoisted__Str_8143, (Bool){0});
    I64 hoisted__I64_8144 = 10;
    (void)hoisted__I64_8144;
    (void)hoisted__Str_8145;
    (void)hoisted__Str_8145;
    assert_eq__I64(r.top_left.y, hoisted__I64_8144, &hoisted__Str_8145);
    Str_delete(&hoisted__Str_8145, (Bool){0});
    I64 hoisted__I64_8146 = 100;
    (void)hoisted__I64_8146;
    (void)hoisted__Str_8147;
    (void)hoisted__Str_8147;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_8146, &hoisted__Str_8147);
    Str_delete(&hoisted__Str_8147, (Bool){0});
    I64 hoisted__I64_8148 = 200;
    (void)hoisted__I64_8148;
    (void)hoisted__Str_8149;
    (void)hoisted__Str_8149;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_8148, &hoisted__Str_8149);
    Str_delete(&hoisted__Str_8149, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_8151 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_8151;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_8151;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_8152 = 0;
    (void)hoisted__U32_8152;
    U64 hoisted__U64_8153 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_8152); });
    (void)hoisted__U64_8153;
    return hoisted__U64_8153;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_8196 = 12;
    (void)hoisted__U32_8196;
    return hoisted__U32_8196;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_8200 = F32_to_str(v.x);
    (void)hoisted__Str_8200;
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8201;
    (void)hoisted__Str_8202;
    (void)hoisted__Str_8202;
    assert_eq__Str(hoisted__Str_8200, &hoisted__Str_8201, &hoisted__Str_8202);
    Str_delete(hoisted__Str_8200, 1);
    Str_delete(&hoisted__Str_8201, (Bool){0});
    Str_delete(&hoisted__Str_8202, (Bool){0});
    Str *hoisted__Str_8203 = F32_to_str(v.y);
    (void)hoisted__Str_8203;
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8204;
    (void)hoisted__Str_8205;
    (void)hoisted__Str_8205;
    assert_eq__Str(hoisted__Str_8203, &hoisted__Str_8204, &hoisted__Str_8205);
    Str_delete(hoisted__Str_8203, 1);
    Str_delete(&hoisted__Str_8204, (Bool){0});
    Str_delete(&hoisted__Str_8205, (Bool){0});
    Str *hoisted__Str_8206 = F32_to_str(v.z);
    (void)hoisted__Str_8206;
    (void)hoisted__Str_8207;
    (void)hoisted__Str_8207;
    (void)hoisted__Str_8208;
    (void)hoisted__Str_8208;
    assert_eq__Str(hoisted__Str_8206, &hoisted__Str_8207, &hoisted__Str_8208);
    Str_delete(hoisted__Str_8206, 1);
    Str_delete(&hoisted__Str_8207, (Bool){0});
    Str_delete(&hoisted__Str_8208, (Bool){0});
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
    Bool hoisted__Bool_8213 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8213;
    if (hoisted__Bool_8213) {
        Bool hoisted__Bool_8210 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_8210;
        { Bool _ret_val = hoisted__Bool_8210;
                return _ret_val; }
    }
    Bool hoisted__Bool_8214 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8214;
    if (hoisted__Bool_8214) {
        Bool hoisted__Bool_8211 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_8211;
        { Bool _ret_val = hoisted__Bool_8211;
                return _ret_val; }
    }
    Bool hoisted__Bool_8215 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8215;
    if (hoisted__Bool_8215) {
        Bool hoisted__Bool_8212 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_8212;
        { Bool _ret_val = hoisted__Bool_8212;
                return _ret_val; }
    }
    Bool hoisted__Bool_8216 = 0;
    (void)hoisted__Bool_8216;
    return hoisted__Bool_8216;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_8224 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8224;
    if (hoisted__Bool_8224) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_8225 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8225;
    if (hoisted__Bool_8225) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_8226 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_8226;
    if (hoisted__Bool_8226) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    static Str hoisted__Str_8227 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_8227;
    UNREACHABLE(&hoisted__Str_8227);
    Str_delete(&hoisted__Str_8227, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_8228 = 4;
    (void)hoisted__U32_8228;
    return hoisted__U32_8228;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_8229 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8229;
    (void)hoisted__Str_8230;
    (void)hoisted__Str_8230;
    assert(hoisted__Bool_8229, &hoisted__Str_8230);
    Str_delete(&hoisted__Str_8230, (Bool){0});
    Bool hoisted__Bool_8231 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8231;
    Bool hoisted__Bool_8232 = not(hoisted__Bool_8231);
    (void)hoisted__Bool_8232;
    (void)hoisted__Str_8233;
    (void)hoisted__Str_8233;
    assert(hoisted__Bool_8232, &hoisted__Str_8233);
    Str_delete(&hoisted__Str_8233, (Bool){0});
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
    Bool hoisted__Bool_8234 = is(self, other);
    (void)hoisted__Bool_8234;
    return hoisted__Bool_8234;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_8252 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8252;
    if (hoisted__Bool_8252) {
        I64 *hoisted__I64_8248 = get_payload(self);
        (void)hoisted__I64_8248;
        (void)hoisted__I64_8248;
        Bool hoisted__Bool_8249 = 0;
        (void)hoisted__Bool_8249;
        I64_delete(hoisted__I64_8248, hoisted__Bool_8249);
    }
    Bool hoisted__Bool_8253 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8253;
    if (hoisted__Bool_8253) {
        Str *hoisted__Str_8250 = get_payload(self);
        (void)hoisted__Str_8250;
        (void)hoisted__Str_8250;
        Bool hoisted__Bool_8251 = 0;
        (void)hoisted__Bool_8251;
        Str_delete(hoisted__Str_8250, hoisted__Bool_8251);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_8284 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8284;
    if (hoisted__Bool_8284) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_8281 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_8281;
        { Token * _ret_val = hoisted__Token_8281;
                return _ret_val; }
    }
    Bool hoisted__Bool_8285 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_8285;
    if (hoisted__Bool_8285) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_8282 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_8282;
        Token *hoisted__Token_8283 = Token_Name(hoisted__Str_8282);
        (void)hoisted__Token_8283;
        { Token * _ret_val = hoisted__Token_8283;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_8286 = 24;
    (void)hoisted__U32_8286;
    return hoisted__U32_8286;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_8288 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8288;
    (void)hoisted__Str_8289;
    (void)hoisted__Str_8289;
    assert(hoisted__Bool_8288, &hoisted__Str_8289);
    Str_delete(&hoisted__Str_8289, (Bool){0});
    Bool hoisted__Bool_8290 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8290;
    Bool hoisted__Bool_8291 = not(hoisted__Bool_8290);
    (void)hoisted__Bool_8291;
    (void)hoisted__Str_8292;
    (void)hoisted__Str_8292;
    assert(hoisted__Bool_8291, &hoisted__Str_8292);
    Str_delete(&hoisted__Str_8292, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_8293 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_8293;
    (void)hoisted__Str_8294;
    (void)hoisted__Str_8294;
    assert(hoisted__Bool_8293, &hoisted__Str_8294);
    Str_delete(&hoisted__Str_8294, (Bool){0});
    Bool hoisted__Bool_8295 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_8295;
    Bool hoisted__Bool_8296 = not(hoisted__Bool_8295);
    (void)hoisted__Bool_8296;
    (void)hoisted__Str_8297;
    (void)hoisted__Str_8297;
    assert(hoisted__Bool_8296, &hoisted__Str_8297);
    Str_delete(&hoisted__Str_8297, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_8300 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_8300;
    (void)hoisted__Str_8301;
    (void)hoisted__Str_8301;
    assert(hoisted__Bool_8300, &hoisted__Str_8301);
    Str_delete(&hoisted__Str_8301, (Bool){0});
    Bool hoisted__Bool_8302 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_8302;
    Bool hoisted__Bool_8303 = not(hoisted__Bool_8302);
    (void)hoisted__Bool_8303;
    (void)hoisted__Str_8304;
    (void)hoisted__Str_8304;
    assert(hoisted__Bool_8303, &hoisted__Str_8304);
    Str_delete(&hoisted__Str_8304, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_8436 = ((Bool)(a != b));
    (void)hoisted__Bool_8436;
    if (hoisted__Bool_8436) {
        U32 hoisted__U32_8420 = 5;
        (void)hoisted__U32_8420;
        Array__Str *_va_Array_249 = Array__Str_new(hoisted__U32_8420);
        (void)_va_Array_249;
        I64 _va_Array_249_ek = 0;
        (void)_va_Array_249_ek;
        OutOfBounds *_va_Array_249_eo = malloc(sizeof(OutOfBounds));
        _va_Array_249_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_249_eo;
        U32 hoisted__U32_8421 = 0;
        (void)hoisted__U32_8421;
        (void)hoisted__Str_8422;
        (void)hoisted__Str_8422;
        (void)hoisted__Str_8423;
        (void)hoisted__Str_8423;
        Array__Str_set(_va_Array_249, hoisted__U32_8421, &hoisted__Str_8422, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8423);
        Str_delete(&hoisted__Str_8423, (Bool){0});
        U32 hoisted__U32_8424 = 1;
        (void)hoisted__U32_8424;
        Str *hoisted__Str_8425 = I64_to_str(a);
        (void)hoisted__Str_8425;
        (void)hoisted__Str_8426;
        (void)hoisted__Str_8426;
        Array__Str_set(_va_Array_249, hoisted__U32_8424, hoisted__Str_8425, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8426);
        Str_delete(&hoisted__Str_8426, (Bool){0});
        U32 hoisted__U32_8427 = 2;
        (void)hoisted__U32_8427;
        (void)hoisted__Str_8428;
        (void)hoisted__Str_8428;
        (void)hoisted__Str_8429;
        (void)hoisted__Str_8429;
        Array__Str_set(_va_Array_249, hoisted__U32_8427, &hoisted__Str_8428, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8429);
        Str_delete(&hoisted__Str_8429, (Bool){0});
        U32 hoisted__U32_8430 = 3;
        (void)hoisted__U32_8430;
        Str *hoisted__Str_8431 = I64_to_str(b);
        (void)hoisted__Str_8431;
        (void)hoisted__Str_8432;
        (void)hoisted__Str_8432;
        Array__Str_set(_va_Array_249, hoisted__U32_8430, hoisted__Str_8431, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8432);
        Str_delete(&hoisted__Str_8432, (Bool){0});
        U32 hoisted__U32_8433 = 4;
        (void)hoisted__U32_8433;
        (void)hoisted__Str_8434;
        (void)hoisted__Str_8434;
        (void)hoisted__Str_8435;
        (void)hoisted__Str_8435;
        Array__Str_set(_va_Array_249, hoisted__U32_8433, &hoisted__Str_8434, &_va_Array_249_ek, _va_Array_249_eo, &hoisted__Str_8435);
        OutOfBounds_delete(_va_Array_249_eo, 1);
        Str_delete(&hoisted__Str_8435, (Bool){0});
        panic(_va_Array_249, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_8453 = Str_neq(a, b);
    (void)hoisted__Bool_8453;
    if (hoisted__Bool_8453) {
        U32 hoisted__U32_8437 = 5;
        (void)hoisted__U32_8437;
        Array__Str *_va_Array_250 = Array__Str_new(hoisted__U32_8437);
        (void)_va_Array_250;
        I64 _va_Array_250_ek = 0;
        (void)_va_Array_250_ek;
        OutOfBounds *_va_Array_250_eo = malloc(sizeof(OutOfBounds));
        _va_Array_250_eo->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_va_Array_250_eo;
        U32 hoisted__U32_8438 = 0;
        (void)hoisted__U32_8438;
        (void)hoisted__Str_8439;
        (void)hoisted__Str_8439;
        (void)hoisted__Str_8440;
        (void)hoisted__Str_8440;
        Array__Str_set(_va_Array_250, hoisted__U32_8438, &hoisted__Str_8439, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8440);
        Str_delete(&hoisted__Str_8440, (Bool){0});
        U32 hoisted__U32_8441 = 1;
        (void)hoisted__U32_8441;
        Str *hoisted__Str_8442 = Str_to_str(a);
        (void)hoisted__Str_8442;
        (void)hoisted__Str_8443;
        (void)hoisted__Str_8443;
        Array__Str_set(_va_Array_250, hoisted__U32_8441, hoisted__Str_8442, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8443);
        Str_delete(&hoisted__Str_8443, (Bool){0});
        U32 hoisted__U32_8444 = 2;
        (void)hoisted__U32_8444;
        (void)hoisted__Str_8445;
        (void)hoisted__Str_8445;
        (void)hoisted__Str_8446;
        (void)hoisted__Str_8446;
        Array__Str_set(_va_Array_250, hoisted__U32_8444, &hoisted__Str_8445, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8446);
        Str_delete(&hoisted__Str_8446, (Bool){0});
        U32 hoisted__U32_8447 = 3;
        (void)hoisted__U32_8447;
        Str *hoisted__Str_8448 = Str_to_str(b);
        (void)hoisted__Str_8448;
        (void)hoisted__Str_8449;
        (void)hoisted__Str_8449;
        Array__Str_set(_va_Array_250, hoisted__U32_8447, hoisted__Str_8448, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8449);
        Str_delete(&hoisted__Str_8449, (Bool){0});
        U32 hoisted__U32_8450 = 4;
        (void)hoisted__U32_8450;
        (void)hoisted__Str_8451;
        (void)hoisted__Str_8451;
        (void)hoisted__Str_8452;
        (void)hoisted__Str_8452;
        Array__Str_set(_va_Array_250, hoisted__U32_8450, &hoisted__Str_8451, &_va_Array_250_ek, _va_Array_250_eo, &hoisted__Str_8452);
        OutOfBounds_delete(_va_Array_250_eo, 1);
        Str_delete(&hoisted__Str_8452, (Bool){0});
        panic(_va_Array_250, loc);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U64_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U64_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)&U32_to_i64_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U32_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U32_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U32_hash_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I64_hash_dyn__til_closure;
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
        if (*index == 8LL) return ({ static Str _lit223 = (Str){.c_str = (void *)"CoreFunc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit223; });
        if (*index == 9LL) return ({ static Str _lit224 = (Str){.c_str = (void *)"CoreProc", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit224; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit225 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit225; });
        if (*index == 1LL) return ({ static Str _lit226 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit226; });
        if (*index == 2LL) return ({ static Str _lit227 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit227; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit228 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit228; });
        if (*index == 1LL) return ({ static Str _lit229 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit229; });
        if (*index == 2LL) return ({ static Str _lit230 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit230; });
        if (*index == 3LL) return ({ static Str _lit231 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit231; });
        if (*index == 4LL) return ({ static Str _lit232 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit232; });
        if (*index == 5LL) return ({ static Str _lit233 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit233; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit234 = (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit234; });
        if (*index == 1LL) return ({ static Str _lit235 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit235; });
        if (*index == 2LL) return ({ static Str _lit236 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit236; });
        if (*index == 3LL) return ({ static Str _lit237 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit237; });
        if (*index == 4LL) return ({ static Str _lit238 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit238; });
        if (*index == 5LL) return ({ static Str _lit239 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit239; });
        if (*index == 6LL) return ({ static Str _lit240 = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit240; });
        if (*index == 7LL) return ({ static Str _lit241 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit241; });
        if (*index == 8LL) return ({ static Str _lit242 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit242; });
        if (*index == 9LL) return ({ static Str _lit243 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit243; });
        if (*index == 10LL) return ({ static Str _lit244 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit244; });
        if (*index == 11LL) return ({ static Str _lit245 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit245; });
        if (*index == 12LL) return ({ static Str _lit246 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT}; &_lit246; });
        if (*index == 13LL) return ({ static Str _lit247 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit247; });
        if (*index == 14LL) return ({ static Str _lit248 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit248; });
        if (*index == 15LL) return ({ static Str _lit249 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit249; });
        if (*index == 16LL) return ({ static Str _lit250 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit250; });
        if (*index == 17LL) return ({ static Str _lit251 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT}; &_lit251; });
        if (*index == 18LL) return ({ static Str _lit252 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT}; &_lit252; });
        if (*index == 19LL) return ({ static Str _lit253 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit253; });
        if (*index == 20LL) return ({ static Str _lit254 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit254; });
        if (*index == 21LL) return ({ static Str _lit255 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit255; });
        if (*index == 22LL) return ({ static Str _lit256 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit256; });
        if (*index == 23LL) return ({ static Str _lit257 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit257; });
        if (*index == 24LL) return ({ static Str _lit258 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit258; });
        if (*index == 25LL) return ({ static Str _lit259 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT}; &_lit259; });
        if (*index == 26LL) return ({ static Str _lit260 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit260; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit261 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit261; });
        if (*index == 1LL) return ({ static Str _lit262 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT}; &_lit262; });
        if (*index == 2LL) return ({ static Str _lit263 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit263; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit264 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit264; });
        if (*index == 1LL) return ({ static Str _lit265 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit265; });
        if (*index == 2LL) return ({ static Str _lit266 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit266; });
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
        if (*index == 0LL) return ({ static Str _lit267 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit267; });
        if (*index == 1LL) return ({ static Str _lit268 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit268; });
        if (*index == 2LL) return ({ static Str _lit269 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit269; });
        if (*index == 3LL) return ({ static Str _lit270 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit270; });
        if (*index == 4LL) return ({ static Str _lit271 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit271; });
        if (*index == 5LL) return ({ static Str _lit272 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit272; });
        if (*index == 6LL) return ({ static Str _lit273 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit273; });
        if (*index == 7LL) return ({ static Str _lit274 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit274; });
        if (*index == 8LL) return ({ static Str _lit275 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit275; });
        if (*index == 9LL) return ({ static Str _lit276 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit276; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit277 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit277; });
        if (*index == 1LL) return ({ static Str _lit278 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit278; });
        if (*index == 2LL) return ({ static Str _lit279 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit279; });
        if (*index == 3LL) return ({ static Str _lit280 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit280; });
        if (*index == 4LL) return ({ static Str _lit281 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit281; });
        if (*index == 5LL) return ({ static Str _lit282 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit282; });
        if (*index == 6LL) return ({ static Str _lit283 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit283; });
        if (*index == 7LL) return ({ static Str _lit284 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit284; });
        if (*index == 8LL) return ({ static Str _lit285 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit285; });
        if (*index == 9LL) return ({ static Str _lit286 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit286; });
        if (*index == 10LL) return ({ static Str _lit287 = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit287; });
        if (*index == 11LL) return ({ static Str _lit288 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit288; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit289 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit289; });
        if (*index == 1LL) return ({ static Str _lit290 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit290; });
        if (*index == 2LL) return ({ static Str _lit291 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit291; });
        if (*index == 3LL) return ({ static Str _lit292 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit292; });
        if (*index == 4LL) return ({ static Str _lit293 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit293; });
        if (*index == 5LL) return ({ static Str _lit294 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit294; });
        if (*index == 6LL) return ({ static Str _lit295 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit295; });
        if (*index == 7LL) return ({ static Str _lit296 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit296; });
        if (*index == 8LL) return ({ static Str _lit297 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit297; });
        if (*index == 9LL) return ({ static Str _lit298 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit298; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit299 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit299; });
        if (*index == 1LL) return ({ static Str _lit300 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit300; });
        if (*index == 2LL) return ({ static Str _lit301 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit301; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit302 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit302; });
        if (*index == 1LL) return ({ static Str _lit303 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT}; &_lit303; });
        if (*index == 2LL) return ({ static Str _lit304 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; &_lit304; });
        if (*index == 3LL) return ({ static Str _lit305 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit305; });
        if (*index == 4LL) return ({ static Str _lit306 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit306; });
        if (*index == 5LL) return ({ static Str _lit307 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit307; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit308 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit308; });
        if (*index == 1LL) return ({ static Str _lit309 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit309; });
        if (*index == 2LL) return ({ static Str _lit310 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit310; });
        if (*index == 3LL) return ({ static Str _lit311 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit311; });
        if (*index == 4LL) return ({ static Str _lit312 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT}; &_lit312; });
        if (*index == 5LL) return ({ static Str _lit313 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit313; });
        if (*index == 6LL) return ({ static Str _lit314 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; &_lit314; });
        if (*index == 7LL) return ({ static Str _lit315 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit315; });
        if (*index == 8LL) return ({ static Str _lit316 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit316; });
        if (*index == 9LL) return ({ static Str _lit317 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit317; });
        if (*index == 10LL) return ({ static Str _lit318 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT}; &_lit318; });
        if (*index == 11LL) return ({ static Str _lit319 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit319; });
        if (*index == 12LL) return ({ static Str _lit320 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit320; });
        if (*index == 13LL) return ({ static Str _lit321 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit321; });
        if (*index == 14LL) return ({ static Str _lit322 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit322; });
        if (*index == 15LL) return ({ static Str _lit323 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit323; });
        if (*index == 16LL) return ({ static Str _lit324 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit324; });
        if (*index == 17LL) return ({ static Str _lit325 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit325; });
        if (*index == 18LL) return ({ static Str _lit326 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit326; });
        if (*index == 19LL) return ({ static Str _lit327 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT}; &_lit327; });
        if (*index == 20LL) return ({ static Str _lit328 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit328; });
        if (*index == 21LL) return ({ static Str _lit329 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit329; });
        if (*index == 22LL) return ({ static Str _lit330 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit330; });
        if (*index == 23LL) return ({ static Str _lit331 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit331; });
        if (*index == 24LL) return ({ static Str _lit332 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit332; });
        if (*index == 25LL) return ({ static Str _lit333 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT}; &_lit333; });
        if (*index == 26LL) return ({ static Str _lit334 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit334; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit335 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit335; });
        if (*index == 1LL) return ({ static Str _lit336 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit336; });
        if (*index == 2LL) return ({ static Str _lit337 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit337; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ static Str _lit338 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit338; });
        if (*index == 1LL) return ({ static Str _lit339 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit339; });
        if (*index == 2LL) return ({ static Str _lit340 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; &_lit340; });
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
        if (*index == 0LL) return ({ static Str _lit341 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; &_lit341; });
        if (*index == 1LL) return ({ static Str _lit342 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit342; });
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
        if (*index == 0LL) return ({ static Str _lit343 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; &_lit343; });
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
