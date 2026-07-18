#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

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
    FuncType_TAG_CoreProc,
    FuncType_TAG_CoreLazyFunc
} FuncType_tag;
typedef struct FuncType FuncType;
typedef enum {
    OwnType_TAG_Own,
    OwnType_TAG_Ref,
    OwnType_TAG_Shallow
} OwnType_tag;
typedef struct OwnType OwnType;
typedef enum {
    GcStorage_TAG_Unset,
    GcStorage_TAG_Stack,
    GcStorage_TAG_HeapBox
} GcStorage_tag;
typedef struct GcStorage GcStorage;
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
    NodeType_TAG_BodyValue,
    NodeType_TAG_ListPattern
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
    USize count;
    USize cap;
} Str;


typedef struct OutOfBounds {
    char _;
} OutOfBounds;


typedef struct Array__Str {
    U8 *data;
    USize cap;
} Array__Str;


typedef struct Vec__Str {
    U8 *data;
    USize count;
    USize cap;
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
        void *_til_payload_align;
    } data;
};

struct FuncType {
    U8 tag;
};

struct OwnType {
    U8 tag;
};

struct GcStorage {
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
    GcStorage gc_storage;
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
        void *_til_payload_align;
    } data;
};

typedef struct MatchData {
    Type til_type;
    Str result_temp;
} MatchData;


typedef struct Vec__Bool {
    U8 *data;
    USize count;
    USize cap;
} Vec__Bool;


typedef struct Vec__I64 {
    U8 *data;
    USize count;
    USize cap;
} Vec__I64;


typedef struct Vec__Declaration {
    U8 *data;
    USize count;
    USize cap;
} Vec__Declaration;


typedef struct Vec__Expr {
    U8 *data;
    USize count;
    USize cap;
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
        void *_til_payload_align;
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
        void *_til_payload_align;
    } data;
};

typedef struct Expr {
    NodeType node_type;
    Vec__Expr children;
    U32 line;
    U32 col;
} Expr;


Str * format(Array__Str * parts);
USize Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * _self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
USize OutOfBounds_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
USize Vec__Str_size(void);
USize Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
USize U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
USize U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
USize U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
USize I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
USize I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
USize F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
USize Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
USize Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
USize Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
USize FuncType_size(void);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
USize OwnType_size(void);
Bool GcStorage_eq(GcStorage * self, GcStorage * other);
void GcStorage_delete(GcStorage * self, Bool call_free);
GcStorage * GcStorage_clone(GcStorage * self);
USize GcStorage_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
USize Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
USize FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
USize FCallData_size(void);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
USize LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
USize IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
USize FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
USize StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
USize EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
USize AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
USize FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
USize ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
USize Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
USize MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
USize CaptureBlockData_size(void);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
USize NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
USize Expr_size(void);
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
USize Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
USize Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
USize Vec__I64_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
USize Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
USize Vec__Expr_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
USize Range_size(void);
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
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
USize CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
USize Token_size(void);
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
USize Str_len(Str * self);
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * _self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
USize OutOfBounds_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
Vec__Str * Vec__Str_new(void);
void Vec__Str_clear(Vec__Str * self);
void Vec__Str_delete(Vec__Str * self, Bool call_free);
Vec__Str * Vec__Str_clone(Vec__Str * self);
USize Vec__Str_size(void);
USize Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
USize U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
USize U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
USize U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
USize I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
USize I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
USize F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
USize Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
USize Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
USize Type_size(void);
Bool FuncType_eq(FuncType * self, FuncType * other);
void FuncType_delete(FuncType * self, Bool call_free);
FuncType * FuncType_clone(FuncType * self);
USize FuncType_size(void);
Bool OwnType_eq(OwnType * self, OwnType * other);
void OwnType_delete(OwnType * self, Bool call_free);
OwnType * OwnType_clone(OwnType * self);
USize OwnType_size(void);
Bool GcStorage_eq(GcStorage * self, GcStorage * other);
void GcStorage_delete(GcStorage * self, Bool call_free);
GcStorage * GcStorage_clone(GcStorage * self);
USize GcStorage_size(void);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool call_free);
USize Declaration_size(void);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool call_free);
U64 FunctionDef_hash(FunctionDef * self, HashFn hasher);
USize FunctionDef_size(void);
FCallData * FCallData_clone(FCallData * self);
void FCallData_delete(FCallData * self, Bool call_free);
U64 FCallData_hash(FCallData * self, HashFn hasher);
USize FCallData_size(void);
LiteralNumData * LiteralNumData_clone(LiteralNumData * self);
void LiteralNumData_delete(LiteralNumData * self, Bool call_free);
U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher);
USize LiteralNumData_size(void);
IdentData * IdentData_clone(IdentData * self);
void IdentData_delete(IdentData * self, Bool call_free);
U64 IdentData_hash(IdentData * self, HashFn hasher);
USize IdentData_size(void);
FieldAccessData * FieldAccessData_clone(FieldAccessData * self);
void FieldAccessData_delete(FieldAccessData * self, Bool call_free);
U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher);
USize FieldAccessData_size(void);
StructDef * StructDef_clone(StructDef * self);
void StructDef_delete(StructDef * self, Bool call_free);
U64 StructDef_hash(StructDef * self, HashFn hasher);
USize StructDef_size(void);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool call_free);
U64 EnumDef_hash(EnumDef * self, HashFn hasher);
USize EnumDef_size(void);
AssignData * AssignData_clone(AssignData * self);
void AssignData_delete(AssignData * self, Bool call_free);
U64 AssignData_hash(AssignData * self, HashFn hasher);
USize AssignData_size(void);
FieldAssignData * FieldAssignData_clone(FieldAssignData * self);
void FieldAssignData_delete(FieldAssignData * self, Bool call_free);
U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher);
USize FieldAssignData_size(void);
ForInData * ForInData_clone(ForInData * self);
void ForInData_delete(ForInData * self, Bool call_free);
U64 ForInData_hash(ForInData * self, HashFn hasher);
USize ForInData_size(void);
void Literal_delete(Literal * self, Bool call_free);
Literal * Literal_clone(Literal * self);
USize Literal_size(void);
MatchData * MatchData_clone(MatchData * self);
void MatchData_delete(MatchData * self, Bool call_free);
U64 MatchData_hash(MatchData * self, HashFn hasher);
USize MatchData_size(void);
CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self);
void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free);
U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher);
USize CaptureBlockData_size(void);
void NodeType_delete(NodeType * self, Bool call_free);
NodeType * NodeType_clone(NodeType * self);
USize NodeType_size(void);
void Expr_delete(Expr * self, Bool call_free);
Expr * Expr_new(NodeType * data, U32 line, U32 col);
Expr * Expr_clone(Expr * self);
U64 Expr_hash(Expr * self, HashFn hasher);
USize Expr_size(void);
Map__I64_Str * Map__I64_Str_new(void);
void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free);
Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self);
U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher);
USize Map__I64_Str_size(void);
Vec__Bool * Vec__Bool_new(void);
void Vec__Bool_clear(Vec__Bool * self);
void Vec__Bool_delete(Vec__Bool * self, Bool call_free);
Vec__Bool * Vec__Bool_clone(Vec__Bool * self);
USize Vec__Bool_size(void);
Vec__I64 * Vec__I64_new(void);
void Vec__I64_clear(Vec__I64 * self);
void Vec__I64_delete(Vec__I64 * self, Bool call_free);
Vec__I64 * Vec__I64_clone(Vec__I64 * self);
USize Vec__I64_size(void);
Vec__Declaration * Vec__Declaration_new(void);
void Vec__Declaration_clear(Vec__Declaration * self);
void Vec__Declaration_delete(Vec__Declaration * self, Bool call_free);
Vec__Declaration * Vec__Declaration_clone(Vec__Declaration * self);
USize Vec__Declaration_size(void);
Vec__Expr * Vec__Expr_new(void);
void Vec__Expr_clear(Vec__Expr * self);
void Vec__Expr_delete(Vec__Expr * self, Bool call_free);
Vec__Expr * Vec__Expr_clone(Vec__Expr * self);
USize Vec__Expr_size(void);
void panic(Array__Str * parts, Str * loc);
void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
USize Range_size(void);
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
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
USize CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
USize Token_size(void);
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
FuncType *FuncType_CoreLazyFunc();
Bool OwnType_eq(OwnType *, OwnType *);
OwnType *OwnType_Own();
OwnType *OwnType_Ref();
OwnType *OwnType_Shallow();
Bool GcStorage_eq(GcStorage *, GcStorage *);
GcStorage *GcStorage_Unset();
GcStorage *GcStorage_Stack();
GcStorage *GcStorage_HeapBox();
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
NodeType *NodeType_ListPattern();
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
static __attribute__((unused)) Str _til_str_lit_3 = (Str){.c_str = (void *)"USize", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_4 = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_5 = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_6 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_7 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_8 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_9 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_10 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_11 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_12 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_13 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_14 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_15 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_16 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_17 = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_18 = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_19 = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_20 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
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
static __attribute__((unused)) Str _til_str_lit_40 = (Str){.c_str = (void *)"CoreLazyFunc", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_41 = (Str){.c_str = (void *)"Own", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_42 = (Str){.c_str = (void *)"Ref", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_43 = (Str){.c_str = (void *)"Shallow", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_44 = (Str){.c_str = (void *)"Unset", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_45 = (Str){.c_str = (void *)"Stack", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_46 = (Str){.c_str = (void *)"HeapBox", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_47 = (Str){.c_str = (void *)"name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_48 = (Str){.c_str = (void *)"doc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_49 = (Str){.c_str = (void *)"explicit_type", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_50 = (Str){.c_str = (void *)"is_mut", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_51 = (Str){.c_str = (void *)"redundant_mut", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_52 = (Str){.c_str = (void *)"is_priv", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_53 = (Str){.c_str = (void *)"used", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_54 = (Str){.c_str = (void *)"own_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_55 = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_56 = (Str){.c_str = (void *)"til_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_57 = (Str){.c_str = (void *)"Type", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_58 = (Str){.c_str = (void *)"default_value", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_59 = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_60 = (Str){.c_str = (void *)"orig_name", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_61 = (Str){.c_str = (void *)"gc_storage", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_62 = (Str){.c_str = (void *)"GcStorage", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_63 = (Str){.c_str = (void *)"func_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_64 = (Str){.c_str = (void *)"FuncType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_65 = (Str){.c_str = (void *)"params", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_66 = (Str){.c_str = (void *)"Vec__Declaration", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_67 = (Str){.c_str = (void *)"return_type", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_68 = (Str){.c_str = (void *)"throw_types", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_69 = (Str){.c_str = (void *)"Vec__Str", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_70 = (Str){.c_str = (void *)"variadic_index", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_71 = (Str){.c_str = (void *)"kwargs_index", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_72 = (Str){.c_str = (void *)"return_own_type", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_73 = (Str){.c_str = (void *)"return_shallow_explicit", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_74 = (Str){.c_str = (void *)"auto_generated", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_75 = (Str){.c_str = (void *)"is_enum_variant_ctor", .count = 20ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_76 = (Str){.c_str = (void *)"captures", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_77 = (Str){.c_str = (void *)"closure_name", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_78 = (Str){.c_str = (void *)"is_splat", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_79 = (Str){.c_str = (void *)"does_throw", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_80 = (Str){.c_str = (void *)"is_bang", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_81 = (Str){.c_str = (void *)"own_args", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_82 = (Str){.c_str = (void *)"swap_replace", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_83 = (Str){.c_str = (void *)"text", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_84 = (Str){.c_str = (void *)"fields", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_85 = (Str){.c_str = (void *)"ns_decls", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_86 = (Str){.c_str = (void *)"c_tag", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_87 = (Str){.c_str = (void *)"is_interface", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_88 = (Str){.c_str = (void *)"interface_ns_marker", .count = 19ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_89 = (Str){.c_str = (void *)"implements_name", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_90 = (Str){.c_str = (void *)"variants", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_91 = (Str){.c_str = (void *)"payload_types", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_92 = (Str){.c_str = (void *)"Map__I64_Str", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_93 = (Str){.c_str = (void *)"payload_consts", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_94 = (Str){.c_str = (void *)"Vec__Bool", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_95 = (Str){.c_str = (void *)"tag_type", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_96 = (Str){.c_str = (void *)"tag_values", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_97 = (Str){.c_str = (void *)"Vec__I64", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_98 = (Str){.c_str = (void *)"save_old_delete", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_99 = (Str){.c_str = (void *)"is_payload_alias", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_100 = (Str){.c_str = (void *)"name2", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_101 = (Str){.c_str = (void *)"is_mut2", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_102 = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_103 = (Str){.c_str = (void *)"LiteralNumData", .count = 14ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_104 = (Str){.c_str = (void *)"Null", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_105 = (Str){.c_str = (void *)"MapLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_106 = (Str){.c_str = (void *)"SetLit", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_107 = (Str){.c_str = (void *)"result_temp", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_108 = (Str){.c_str = (void *)"Literal", .count = 7ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_109 = (Str){.c_str = (void *)"Ident", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_110 = (Str){.c_str = (void *)"IdentData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_111 = (Str){.c_str = (void *)"Decl", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_112 = (Str){.c_str = (void *)"Declaration", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_113 = (Str){.c_str = (void *)"Assign", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_114 = (Str){.c_str = (void *)"AssignData", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_115 = (Str){.c_str = (void *)"FCall", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_116 = (Str){.c_str = (void *)"FCallData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_117 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_118 = (Str){.c_str = (void *)"FieldAccess", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_119 = (Str){.c_str = (void *)"FieldAccessData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_120 = (Str){.c_str = (void *)"FieldAssign", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_121 = (Str){.c_str = (void *)"FieldAssignData", .count = 15ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_122 = (Str){.c_str = (void *)"Return", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_123 = (Str){.c_str = (void *)"If", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_124 = (Str){.c_str = (void *)"While", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_125 = (Str){.c_str = (void *)"ForIn", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_126 = (Str){.c_str = (void *)"ForInData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_127 = (Str){.c_str = (void *)"NamedArg", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_128 = (Str){.c_str = (void *)"Break", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_129 = (Str){.c_str = (void *)"Continue", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_130 = (Str){.c_str = (void *)"Switch", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_131 = (Str){.c_str = (void *)"Match", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_132 = (Str){.c_str = (void *)"MatchData", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_133 = (Str){.c_str = (void *)"Case", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_134 = (Str){.c_str = (void *)"NoDefaultArg", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_135 = (Str){.c_str = (void *)"Throw", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_136 = (Str){.c_str = (void *)"Catch", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_137 = (Str){.c_str = (void *)"RestPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_138 = (Str){.c_str = (void *)"CaptureBlock", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_139 = (Str){.c_str = (void *)"CaptureBlockData", .count = 16ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_140 = (Str){.c_str = (void *)"Loc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_141 = (Str){.c_str = (void *)"BodyValue", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_142 = (Str){.c_str = (void *)"ListPattern", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_143 = (Str){.c_str = (void *)"node_type", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_144 = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_145 = (Str){.c_str = (void *)"children", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_146 = (Str){.c_str = (void *)"Vec__Expr", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_147 = (Str){.c_str = (void *)"line", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_148 = (Str){.c_str = (void *)"col", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_149 = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_150 = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_151 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_152 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_153 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_154 = (Str){.c_str = (void *)"start", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_155 = (Str){.c_str = (void *)"end", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_156 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_157 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_158 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_159 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_160 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_161 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_162 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_163 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_164 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_165 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_166 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_167 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_168 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_169 = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_170 = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_171 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_172 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_173 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_174 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_175 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_176 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_177 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_178 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_179 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_180 = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_181 = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_182 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_183 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_184 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_185 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_186 = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_187 = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_188 = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_189 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_190 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_191 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_192 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_193 = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_194 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_195 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_196 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_197 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_198 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_199 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_200 = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_201 = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_202 = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_203 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_204 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_205 = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_206 = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_207 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_208 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_209 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_210 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_211 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_212 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_213 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_214 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_215 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_216 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
static __attribute__((unused)) Str _til_str_lit_217 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT};

U32 CAP_LIT;
U32 CAP_VIEW;
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_57 = parts;
        (void)_fc_Array__Str_57;
        (void)_fc_Array__Str_57;
        U32 _fi_USize_57 = 0;
        (void)_fi_USize_57;
        while (1) {
            USize hoisted__U32_59 = (_fc_Array__Str_57->cap);
            (void)hoisted__U32_59;
            Bool _wcond_Bool_58 = ((Bool)(_fi_USize_57 < hoisted__U32_59));
            (void)_wcond_Bool_58;
            if (_wcond_Bool_58) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_57->data) + (((U64)(_fi_USize_57 * 16))))));
            U32 hoisted__U32_60 = 1;
            (void)hoisted__U32_60;
            U32 hoisted__U32_61 = ((U32)(_fi_USize_57 + hoisted__U32_60));
            (void)hoisted__U32_61;
            _fi_USize_57 = hoisted__U32_61;
            USize hoisted__U32_62 = (s->count);
            (void)hoisted__U32_62;
            U32 hoisted__U32_63 = ((U32)(total + hoisted__U32_62));
            (void)hoisted__U32_63;
            total = hoisted__U32_63;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_64 = parts;
        (void)_fc_Array__Str_64;
        (void)_fc_Array__Str_64;
        U32 _fi_USize_64 = 0;
        (void)_fi_USize_64;
        while (1) {
            USize hoisted__U32_66 = (_fc_Array__Str_64->cap);
            (void)hoisted__U32_66;
            Bool _wcond_Bool_65 = ((Bool)(_fi_USize_64 < hoisted__U32_66));
            (void)_wcond_Bool_65;
            if (_wcond_Bool_65) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_64->data) + (((U64)(_fi_USize_64 * 16))))));
            U32 hoisted__U32_67 = 1;
            (void)hoisted__U32_67;
            U32 hoisted__U32_68 = ((U32)(_fi_USize_64 + hoisted__U32_67));
            (void)hoisted__U32_68;
            _fi_USize_64 = hoisted__U32_68;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

USize Str_len(Str * self) {
    return self->count;
    __builtin_unreachable();
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_83 = ((Bool)(b->count < a->count));
    (void)hoisted__Bool_83;
    if (hoisted__Bool_83) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_84 = 0;
    (void)hoisted__I32_84;
    Bool hoisted__Bool_85 = ((Bool)(c < hoisted__I32_84));
    (void)hoisted__Bool_85;
    if (hoisted__Bool_85) {
        I64 hoisted__I64_81 = -1;
        (void)hoisted__I64_81;
        return hoisted__I64_81;
    }
    I32 hoisted__I32_86 = 0;
    (void)hoisted__I32_86;
    Bool hoisted__Bool_87 = ((Bool)(c > hoisted__I32_86));
    (void)hoisted__Bool_87;
    if (hoisted__Bool_87) {
        I64 hoisted__I64_82 = 1;
        (void)hoisted__I64_82;
        return hoisted__I64_82;
    }
    I64 hoisted__I64_88 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_88;
    return hoisted__I64_88;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_91 = ((Bool)(a->count != b->count));
    (void)hoisted__Bool_91;
    if (hoisted__Bool_91) {
        Bool hoisted__Bool_89 = 0;
        (void)hoisted__Bool_89;
        return hoisted__Bool_89;
    }
    Bool hoisted__Bool_92 = ptr_eq(a->c_str, b->c_str);
    (void)hoisted__Bool_92;
    if (hoisted__Bool_92) {
        Bool hoisted__Bool_90 = 1;
        (void)hoisted__Bool_90;
        return hoisted__Bool_90;
    }
    I32 hoisted__I32_93 = memcmp(a->c_str, b->c_str, a->count);
    (void)hoisted__I32_93;
    I32 hoisted__I32_94 = 0;
    (void)hoisted__I32_94;
    Bool hoisted__Bool_95 = ((Bool)(hoisted__I32_93 == hoisted__I32_94));
    (void)hoisted__Bool_95;
    return hoisted__Bool_95;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_97 = 0;
    (void)hoisted__U32_97;
    Bool hoisted__Bool_98 = ((Bool)(n == hoisted__U32_97));
    (void)hoisted__Bool_98;
    if (hoisted__Bool_98) {
        static Str hoisted__Str_96 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_96;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_96; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_99 = 1;
    (void)hoisted__U32_99;
    U32 hoisted__U64_100 = ((U64)(n + hoisted__U32_99));
    (void)hoisted__U64_100;
    I8 *buf = malloc(hoisted__U64_100);
    I32 hoisted__I32_101 = 0;
    (void)hoisted__I32_101;
    U64 hoisted__U64_102 = 1ULL;
    (void)hoisted__U64_102;
    memset(buf, hoisted__I32_101, hoisted__U64_102);
    I64 hoisted__I64_103 = 0;
    (void)hoisted__I64_103;
    Str *hoisted__Str_104 = malloc(sizeof(Str));
    hoisted__Str_104->c_str = buf;
    hoisted__Str_104->count = hoisted__I64_103;
    hoisted__Str_104->cap = n;
    (void)hoisted__Str_104;
    return hoisted__Str_104;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_115 = 0;
    (void)hoisted__U32_115;
    Bool hoisted__Bool_116 = ((Bool)(s->count == hoisted__U32_115));
    (void)hoisted__Bool_116;
    if (hoisted__Bool_116) {
        return;
    }
    Bool hoisted__Bool_117 = ((Bool)(self->cap >= CAP_VIEW));
    (void)hoisted__Bool_117;
    if (hoisted__Bool_117) {
        U32 hoisted__U32_107 = 1;
        (void)hoisted__U32_107;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_107);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        U32 hoisted__U32_108 = 0;
        (void)hoisted__U32_108;
        static Str hoisted__Str_109 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_109;
        Array__Str_set(_va_Array_1, hoisted__U32_108, &hoisted__Str_109, &_va_Array_1_ek);
        static Str hoisted__Str_110 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_110;
        panic(_va_Array_1, &hoisted__Str_110);
        Str_delete(&hoisted__Str_110, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_118 = ((Bool)(new_len > self->cap));
    (void)hoisted__Bool_118;
    if (hoisted__Bool_118) {
        U32 hoisted__U32_111 = 1;
        (void)hoisted__U32_111;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_111);
        (void)_va_Array_2;
        I64 _va_Array_2_ek = 0;
        (void)_va_Array_2_ek;
        U32 hoisted__U32_112 = 0;
        (void)hoisted__U32_112;
        static Str hoisted__Str_113 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_113;
        Array__Str_set(_va_Array_2, hoisted__U32_112, &hoisted__Str_113, &_va_Array_2_ek);
        static Str hoisted__Str_114 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_114;
        panic(_va_Array_2, &hoisted__Str_114);
        Str_delete(&hoisted__Str_114, (Bool){0});
    }
    void *hoisted__v_119 = ((void *)((U8 *)(self->c_str) + (self->count)));
    (void)hoisted__v_119;
    (void)hoisted__v_119;
    memcpy(hoisted__v_119, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_120 = ((void *)((U8 *)(self->c_str) + (new_len)));
    (void)hoisted__v_120;
    (void)hoisted__v_120;
    I32 hoisted__I32_121 = 0;
    (void)hoisted__I32_121;
    U64 hoisted__U64_122 = 1ULL;
    (void)hoisted__U64_122;
    memset(hoisted__v_120, hoisted__I32_121, hoisted__U64_122);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_124 = 0;
    (void)hoisted__U32_124;
    Bool hoisted__Bool_125 = ((Bool)(val->count == hoisted__U32_124));
    (void)hoisted__Bool_125;
    if (hoisted__Bool_125) {
        static Str hoisted__Str_123 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_123;
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_123; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_126 = 1;
    (void)hoisted__U32_126;
    U32 hoisted__U64_127 = ((U64)(val->count + hoisted__U32_126));
    (void)hoisted__U64_127;
    I8 *new_data = malloc(hoisted__U64_127);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_128 = ((void *)((U8 *)(new_data) + (val->count)));
    (void)hoisted__v_128;
    (void)hoisted__v_128;
    I32 hoisted__I32_129 = 0;
    (void)hoisted__I32_129;
    U64 hoisted__U64_130 = 1ULL;
    (void)hoisted__U64_130;
    memset(hoisted__v_128, hoisted__I32_129, hoisted__U64_130);
    Str *hoisted__Str_131 = malloc(sizeof(Str));
    hoisted__Str_131->c_str = new_data;
    hoisted__Str_131->count = val->count;
    hoisted__Str_131->cap = val->count;
    (void)hoisted__Str_131;
    return hoisted__Str_131;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_132 = Str_clone(self);
    (void)hoisted__Str_132;
    return hoisted__Str_132;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_133 = ((Bool)(self->cap < CAP_VIEW));
    (void)hoisted__Bool_133;
    if (hoisted__Bool_133) {
        free(self->c_str);
    }
    Bool hoisted__Bool_134 = ((Bool)(self->cap != CAP_LIT));
    (void)hoisted__Bool_134;
    Bool hoisted__Bool_135 = ((Bool)((call_free) && (hoisted__Bool_134)));
    (void)hoisted__Bool_135;
    if (hoisted__Bool_135) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_330 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_330;
    return hoisted__U64_330;
    __builtin_unreachable();
}

USize Str_size(void) {
    U32 hoisted__U32_503 = 16;
    (void)hoisted__U32_503;
    return hoisted__U32_503;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_512 = Str_eq(a, b);
    (void)hoisted__Bool_512;
    Bool hoisted__Bool_513 = ((Bool)(!(hoisted__Bool_512)));
    (void)hoisted__Bool_513;
    return hoisted__Bool_513;
    __builtin_unreachable();
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * _self) {
    (void)_self;
    OutOfBounds *hoisted__OutOfBounds_598 = malloc(sizeof(OutOfBounds));
    (void)hoisted__OutOfBounds_598;
    return hoisted__OutOfBounds_598;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_599 = 0;
    (void)hoisted__U32_599;
    U64 hoisted__U64_600 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_599); });
    (void)hoisted__U64_600;
    return hoisted__U64_600;
    __builtin_unreachable();
}

USize OutOfBounds_size(void) {
    U32 hoisted__U32_608 = 1;
    (void)hoisted__U32_608;
    return hoisted__U32_608;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    U64 hoisted__U64_620 = 16ULL;
    (void)hoisted__U64_620;
    void * hoisted__v_621 = calloc(cap, hoisted__U64_620);
    (void)hoisted__v_621;
    Array__Str *hoisted__Array__Str_622 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_622->data = hoisted__v_621;
    hoisted__Array__Str_622->cap = cap;
    (void)hoisted__Array__Str_622;
    return hoisted__Array__Str_622;
    __builtin_unreachable();
}

USize Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, USize * i) {
    U32 hoisted__U32_623 = 16;
    (void)hoisted__U32_623;
    U32 hoisted__U64_624 = ((U64)(DEREF(i) * hoisted__U32_623));
    (void)hoisted__U64_624;
    void *hoisted__v_625 = ((void *)((U8 *)(self->data) + (hoisted__U64_624)));
    (void)hoisted__v_625;
    (void)hoisted__v_625;
    return hoisted__v_625;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_631 = (((void *)((U8 *)(self->data) + (((U64)(i * 16))))));
    (void)hoisted__Str_631;
    (void)hoisted__Str_631;
    Bool hoisted__Bool_632 = 0;
    (void)hoisted__Bool_632;
    Str_delete(hoisted__Str_631, hoisted__Bool_632);
    Str *hoisted__Str_633 = (((void *)((U8 *)(self->data) + (((U64)(i * 16))))));
    (void)hoisted__Str_633;
    (void)hoisted__Str_633;
    U64 hoisted__U64_634 = 16ULL;
    (void)hoisted__U64_634;
    memcpy(hoisted__Str_633, val, hoisted__U64_634);
    I32 hoisted__I32_635 = 0;
    (void)hoisted__I32_635;
    U64 hoisted__U64_636 = 16ULL;
    (void)hoisted__U64_636;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_635, hoisted__U64_636); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_638 = ((Bool)(i >= self->cap));
    (void)hoisted__Bool_638;
    if (hoisted__Bool_638) {
        I64 hoisted__I64_637 = 1;
        (void)hoisted__I64_637;
        *_err_kind = hoisted__I64_637;
    }
    I64 hoisted__I64_639 = 0;
    (void)hoisted__I64_639;
    Bool hoisted__Bool_640 = ((Bool)(DEREF(_err_kind) == hoisted__I64_639));
    (void)hoisted__Bool_640;
    if (hoisted__Bool_640) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_641 = self->cap;
        (void)_re_U32_641;
        U32 _rc_U32_641 = 0;
        (void)_rc_U32_641;
        Bool hoisted__Bool_652 = ((Bool)(_rc_U32_641 <= _re_U32_641));
        (void)hoisted__Bool_652;
        if (hoisted__Bool_652) {
            while (1) {
                Bool _wcond_Bool_642 = ((Bool)(_rc_U32_641 < _re_U32_641));
                (void)_wcond_Bool_642;
                if (_wcond_Bool_642) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_641);
                (++_rc_U32_641);
                U32 hoisted__U32_643 = 16;
                (void)hoisted__U32_643;
                U32 hoisted__U64_644 = ((U64)(i * hoisted__U32_643));
                (void)hoisted__U64_644;
                Str *hoisted__Str_645 = ((void *)((U8 *)(self->data) + (hoisted__U64_644)));
                (void)hoisted__Str_645;
                (void)hoisted__Str_645;
                Bool hoisted__Bool_646 = 0;
                (void)hoisted__Bool_646;
                Str_delete(hoisted__Str_645, hoisted__Bool_646);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_647 = ((Bool)(_rc_U32_641 > _re_U32_641));
                (void)_wcond_Bool_647;
                if (_wcond_Bool_647) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_641);
                (--_rc_U32_641);
                U32 hoisted__U32_648 = 16;
                (void)hoisted__U32_648;
                U32 hoisted__U64_649 = ((U64)(i * hoisted__U32_648));
                (void)hoisted__U64_649;
                Str *hoisted__Str_650 = ((void *)((U8 *)(self->data) + (hoisted__U64_649)));
                (void)hoisted__Str_650;
                (void)hoisted__Str_650;
                Bool hoisted__Bool_651 = 0;
                (void)hoisted__Bool_651;
                Str_delete(hoisted__Str_650, hoisted__Bool_651);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_673 = 16;
    (void)hoisted__U32_673;
    U32 hoisted__U64_674 = ((U64)(self->cap * hoisted__U32_673));
    (void)hoisted__U64_674;
    U8 *new_data = malloc(hoisted__U64_674);
    {
        U32 _re_U32_653 = self->cap;
        (void)_re_U32_653;
        U32 _rc_U32_653 = 0;
        (void)_rc_U32_653;
        Bool hoisted__Bool_672 = ((Bool)(_rc_U32_653 <= _re_U32_653));
        (void)hoisted__Bool_672;
        if (hoisted__Bool_672) {
            while (1) {
                Bool _wcond_Bool_654 = ((Bool)(_rc_U32_653 < _re_U32_653));
                (void)_wcond_Bool_654;
                if (_wcond_Bool_654) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_653);
                (++_rc_U32_653);
                U32 hoisted__U32_655 = 16;
                (void)hoisted__U32_655;
                U32 hoisted__U64_656 = ((U64)(i * hoisted__U32_655));
                (void)hoisted__U64_656;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_656)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_657 = 16;
                (void)hoisted__U32_657;
                U32 hoisted__U64_658 = ((U64)(i * hoisted__U32_657));
                (void)hoisted__U64_658;
                void *hoisted__v_659 = ((void *)((U8 *)(new_data) + (hoisted__U64_658)));
                (void)hoisted__v_659;
                (void)hoisted__v_659;
                U64 hoisted__U64_660 = 16ULL;
                (void)hoisted__U64_660;
                memcpy(hoisted__v_659, cloned, hoisted__U64_660);
                I32 hoisted__I32_661 = 0;
                (void)hoisted__I32_661;
                U64 hoisted__U64_662 = 16ULL;
                (void)hoisted__U64_662;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_661, hoisted__U64_662); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_663 = ((Bool)(_rc_U32_653 > _re_U32_653));
                (void)_wcond_Bool_663;
                if (_wcond_Bool_663) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_653);
                (--_rc_U32_653);
                U32 hoisted__U32_664 = 16;
                (void)hoisted__U32_664;
                U32 hoisted__U64_665 = ((U64)(i * hoisted__U32_664));
                (void)hoisted__U64_665;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_665)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_666 = 16;
                (void)hoisted__U32_666;
                U32 hoisted__U64_667 = ((U64)(i * hoisted__U32_666));
                (void)hoisted__U64_667;
                void *hoisted__v_668 = ((void *)((U8 *)(new_data) + (hoisted__U64_667)));
                (void)hoisted__v_668;
                (void)hoisted__v_668;
                U64 hoisted__U64_669 = 16ULL;
                (void)hoisted__U64_669;
                memcpy(hoisted__v_668, cloned, hoisted__U64_669);
                I32 hoisted__I32_670 = 0;
                (void)hoisted__I32_670;
                U64 hoisted__U64_671 = 16ULL;
                (void)hoisted__U64_671;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_670, hoisted__U64_671); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_675 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_675->data = new_data;
    hoisted__Array__Str_675->cap = self->cap;
    (void)hoisted__Array__Str_675;
    return hoisted__Array__Str_675;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_676 = 16;
    (void)hoisted__U32_676;
    return hoisted__U32_676;
    __builtin_unreachable();
}

Vec__Str * Vec__Str_new(void) {
    U8 *hoisted__U8_677 = malloc(sizeof(U8));
    *hoisted__U8_677 = 0;
    (void)hoisted__U8_677;
    U32 hoisted__U32_678 = 0;
    (void)hoisted__U32_678;
    I64 hoisted__I64_679 = 0;
    (void)hoisted__I64_679;
    Vec__Str *hoisted__Vec__Str_680 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_680->data = hoisted__U8_677;
    hoisted__Vec__Str_680->count = hoisted__U32_678;
    hoisted__Vec__Str_680->cap = hoisted__I64_679;
    (void)hoisted__Vec__Str_680;
    return hoisted__Vec__Str_680;
    __builtin_unreachable();
}

void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_692 = self->count;
        (void)_re_U32_692;
        U32 _rc_U32_692 = 0;
        (void)_rc_U32_692;
        Bool hoisted__Bool_703 = ((Bool)(_rc_U32_692 <= _re_U32_692));
        (void)hoisted__Bool_703;
        if (hoisted__Bool_703) {
            while (1) {
                Bool _wcond_Bool_693 = ((Bool)(_rc_U32_692 < _re_U32_692));
                (void)_wcond_Bool_693;
                if (_wcond_Bool_693) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_692);
                (++_rc_U32_692);
                U32 hoisted__U32_694 = 16;
                (void)hoisted__U32_694;
                U32 hoisted__U64_695 = ((U64)(i * hoisted__U32_694));
                (void)hoisted__U64_695;
                Str *hoisted__Str_696 = ((void *)((U8 *)(self->data) + (hoisted__U64_695)));
                (void)hoisted__Str_696;
                (void)hoisted__Str_696;
                Bool hoisted__Bool_697 = 0;
                (void)hoisted__Bool_697;
                Str_delete(hoisted__Str_696, hoisted__Bool_697);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_698 = ((Bool)(_rc_U32_692 > _re_U32_692));
                (void)_wcond_Bool_698;
                if (_wcond_Bool_698) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_692);
                (--_rc_U32_692);
                U32 hoisted__U32_699 = 16;
                (void)hoisted__U32_699;
                U32 hoisted__U64_700 = ((U64)(i * hoisted__U32_699));
                (void)hoisted__U64_700;
                Str *hoisted__Str_701 = ((void *)((U8 *)(self->data) + (hoisted__U64_700)));
                (void)hoisted__Str_701;
                (void)hoisted__Str_701;
                Bool hoisted__Bool_702 = 0;
                (void)hoisted__Bool_702;
                Str_delete(hoisted__Str_701, hoisted__Bool_702);
            }
        }
    }
    U32 hoisted__U32_704 = 0;
    (void)hoisted__U32_704;
    self->count = hoisted__U32_704;
}

void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Str * Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_943 = 0;
    (void)hoisted__U32_943;
    Bool hoisted__Bool_944 = ((Bool)(self->cap == hoisted__U32_943));
    (void)hoisted__Bool_944;
    if (hoisted__Bool_944) {
        U8 *hoisted__U8_919 = malloc(sizeof(U8));
        *hoisted__U8_919 = 0;
        (void)hoisted__U8_919;
        U32 hoisted__U32_920 = 0;
        (void)hoisted__U32_920;
        I64 hoisted__I64_921 = 0;
        (void)hoisted__I64_921;
        Vec__Str *hoisted__Vec__Str_922 = malloc(sizeof(Vec__Str));
        hoisted__Vec__Str_922->data = hoisted__U8_919;
        hoisted__Vec__Str_922->count = hoisted__U32_920;
        hoisted__Vec__Str_922->cap = hoisted__I64_921;
        (void)hoisted__Vec__Str_922;
        return hoisted__Vec__Str_922;
    }
    U32 hoisted__U32_945 = 16;
    (void)hoisted__U32_945;
    U32 hoisted__U64_946 = ((U64)(self->cap * hoisted__U32_945));
    (void)hoisted__U64_946;
    U8 *new_data = malloc(hoisted__U64_946);
    {
        U32 _re_U32_923 = self->count;
        (void)_re_U32_923;
        U32 _rc_U32_923 = 0;
        (void)_rc_U32_923;
        Bool hoisted__Bool_942 = ((Bool)(_rc_U32_923 <= _re_U32_923));
        (void)hoisted__Bool_942;
        if (hoisted__Bool_942) {
            while (1) {
                Bool _wcond_Bool_924 = ((Bool)(_rc_U32_923 < _re_U32_923));
                (void)_wcond_Bool_924;
                if (_wcond_Bool_924) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_923);
                (++_rc_U32_923);
                U32 hoisted__U32_925 = 16;
                (void)hoisted__U32_925;
                U32 hoisted__U64_926 = ((U64)(i * hoisted__U32_925));
                (void)hoisted__U64_926;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_926)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_927 = 16;
                (void)hoisted__U32_927;
                U32 hoisted__U64_928 = ((U64)(i * hoisted__U32_927));
                (void)hoisted__U64_928;
                void *hoisted__v_929 = ((void *)((U8 *)(new_data) + (hoisted__U64_928)));
                (void)hoisted__v_929;
                (void)hoisted__v_929;
                U64 hoisted__U64_930 = 16ULL;
                (void)hoisted__U64_930;
                memcpy(hoisted__v_929, cloned, hoisted__U64_930);
                I32 hoisted__I32_931 = 0;
                (void)hoisted__I32_931;
                U64 hoisted__U64_932 = 16ULL;
                (void)hoisted__U64_932;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_931, hoisted__U64_932); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_933 = ((Bool)(_rc_U32_923 > _re_U32_923));
                (void)_wcond_Bool_933;
                if (_wcond_Bool_933) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_923);
                (--_rc_U32_923);
                U32 hoisted__U32_934 = 16;
                (void)hoisted__U32_934;
                U32 hoisted__U64_935 = ((U64)(i * hoisted__U32_934));
                (void)hoisted__U64_935;
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_935)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_936 = 16;
                (void)hoisted__U32_936;
                U32 hoisted__U64_937 = ((U64)(i * hoisted__U32_936));
                (void)hoisted__U64_937;
                void *hoisted__v_938 = ((void *)((U8 *)(new_data) + (hoisted__U64_937)));
                (void)hoisted__v_938;
                (void)hoisted__v_938;
                U64 hoisted__U64_939 = 16ULL;
                (void)hoisted__U64_939;
                memcpy(hoisted__v_938, cloned, hoisted__U64_939);
                I32 hoisted__I32_940 = 0;
                (void)hoisted__I32_940;
                U64 hoisted__U64_941 = 16ULL;
                (void)hoisted__U64_941;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_940, hoisted__U64_941); };
                Str_delete(cloned, 1);
            }
        }
    }
    Vec__Str *hoisted__Vec__Str_947 = malloc(sizeof(Vec__Str));
    hoisted__Vec__Str_947->data = new_data;
    hoisted__Vec__Str_947->count = self->count;
    hoisted__Vec__Str_947->cap = self->cap;
    (void)hoisted__Vec__Str_947;
    return hoisted__Vec__Str_947;
    __builtin_unreachable();
}

USize Vec__Str_size(void) {
    U32 hoisted__U32_948 = 16;
    (void)hoisted__U32_948;
    return hoisted__U32_948;
    __builtin_unreachable();
}

USize Dynamic_size(void) {
    U32 hoisted__U32_951 = 8;
    (void)hoisted__U32_951;
    return hoisted__U32_951;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U64 hoisted__U64_952 = 8ULL;
    (void)hoisted__U64_952;
    U8 *out = malloc(hoisted__U64_952);
    U64 hoisted__U64_953 = 8ULL;
    (void)hoisted__U64_953;
    memcpy(out, self, hoisted__U64_953);
    return out;
    __builtin_unreachable();
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

USize U8_size(void) {
    U32 hoisted__U32_1041 = 1;
    (void)hoisted__U32_1041;
    return hoisted__U32_1041;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1108 = 1;
    (void)hoisted__U32_1108;
    U64 hoisted__U64_1109 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1108); });
    (void)hoisted__U64_1109;
    return hoisted__U64_1109;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U32_size(void) {
    U32 hoisted__U32_1195 = 4;
    (void)hoisted__U32_1195;
    return hoisted__U32_1195;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1262 = 4;
    (void)hoisted__U32_1262;
    U64 hoisted__U64_1263 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1262); });
    (void)hoisted__U64_1263;
    return hoisted__U64_1263;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1264 = U64_to_str_ext(val);
    (void)hoisted__Str_1264;
    return hoisted__Str_1264;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U64_size(void) {
    U32 hoisted__U32_1269 = 8;
    (void)hoisted__U32_1269;
    return hoisted__U32_1269;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1336 = 8;
    (void)hoisted__U32_1336;
    U64 hoisted__U64_1337 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1336); });
    (void)hoisted__U64_1337;
    return hoisted__U64_1337;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I8_size(void) {
    U32 hoisted__U32_1354 = 1;
    (void)hoisted__U32_1354;
    return hoisted__U32_1354;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1355 = 1;
    (void)hoisted__U32_1355;
    U64 hoisted__U64_1356 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1355); });
    (void)hoisted__U64_1356;
    return hoisted__U64_1356;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I32_size(void) {
    U32 hoisted__U32_1503 = 4;
    (void)hoisted__U32_1503;
    return hoisted__U32_1503;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1615 = 4;
    (void)hoisted__U32_1615;
    U64 hoisted__U64_1616 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1615); });
    (void)hoisted__U64_1616;
    return hoisted__U64_1616;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1625 = 0;
    (void)hoisted__I64_1625;
    Bool hoisted__Bool_1626 = ((Bool)(val < hoisted__I64_1625));
    (void)hoisted__Bool_1626;
    if (hoisted__Bool_1626) {
        U64 hoisted__U64_1617 = 0ULL;
        (void)hoisted__U64_1617;
        U64 hoisted__U64_1618 = (U64)(val);
        (void)hoisted__U64_1618;
        U64 mag = ((U64)(hoisted__U64_1617 - hoisted__U64_1618));
        U32 hoisted__U32_1619 = 2;
        (void)hoisted__U32_1619;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1619);
        (void)_va_Array_39;
        I64 _va_Array_39_ek = 0;
        (void)_va_Array_39_ek;
        U32 hoisted__U32_1620 = 0;
        (void)hoisted__U32_1620;
        static Str hoisted__Str_1621 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1621;
        Array__Str_set(_va_Array_39, hoisted__U32_1620, &hoisted__Str_1621, &_va_Array_39_ek);
        U32 hoisted__U32_1622 = 1;
        (void)hoisted__U32_1622;
        Str *hoisted__Str_1623 = U64_to_str(mag);
        (void)hoisted__Str_1623;
        Array__Str_set(_va_Array_39, hoisted__U32_1622, hoisted__Str_1623, &_va_Array_39_ek);
        Str *hoisted__Str_1624 = format(_va_Array_39);
        (void)hoisted__Str_1624;
        return hoisted__Str_1624;
    }
    U64 hoisted__U64_1627 = (U64)(val);
    (void)hoisted__U64_1627;
    Str *hoisted__Str_1628 = U64_to_str(hoisted__U64_1627);
    (void)hoisted__Str_1628;
    return hoisted__Str_1628;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1642 = 8;
    (void)hoisted__U32_1642;
    return hoisted__U32_1642;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1768 = 8;
    (void)hoisted__U32_1768;
    U64 hoisted__U64_1769 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1768); });
    (void)hoisted__U64_1769;
    return hoisted__U64_1769;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize F32_size(void) {
    U32 hoisted__U32_1771 = 4;
    (void)hoisted__U32_1771;
    return hoisted__U32_1771;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_1787 = 4;
    (void)hoisted__U32_1787;
    U64 hoisted__U64_1788 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1787); });
    (void)hoisted__U64_1788;
    return hoisted__U64_1788;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1831 = ((Bool)(a == b));
    (void)hoisted__Bool_1831;
    if (hoisted__Bool_1831) {
        I64 hoisted__I64_1829 = 0;
        (void)hoisted__I64_1829;
        return hoisted__I64_1829;
    }
    if (b) {
        I64 hoisted__I64_1830 = -1;
        (void)hoisted__I64_1830;
        return hoisted__I64_1830;
    }
    I64 hoisted__I64_1832 = 1;
    (void)hoisted__I64_1832;
    return hoisted__I64_1832;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize Bool_size(void) {
    U32 hoisted__U32_1833 = 1;
    (void)hoisted__U32_1833;
    return hoisted__U32_1833;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1834 = 1;
    (void)hoisted__U32_1834;
    U64 hoisted__U64_1835 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1834); });
    (void)hoisted__U64_1835;
    return hoisted__U64_1835;
    __builtin_unreachable();
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
    U32 hoisted__U32_1927 = 1;
    (void)hoisted__U32_1927;
    Bool hoisted__Bool_1928 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
    (void)hoisted__Bool_1928;
    if (hoisted__Bool_1928) {
        U32 hoisted__U32_1907 = 1;
        (void)hoisted__U32_1907;
        Bool hoisted__Bool_1908 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I16}))->tag));
        (void)hoisted__Bool_1908;
        return hoisted__Bool_1908;
    }
    U32 hoisted__U32_1929 = 1;
    (void)hoisted__U32_1929;
    Bool hoisted__Bool_1930 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
    (void)hoisted__Bool_1930;
    if (hoisted__Bool_1930) {
        U32 hoisted__U32_1909 = 1;
        (void)hoisted__U32_1909;
        Bool hoisted__Bool_1910 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U16}))->tag));
        (void)hoisted__Bool_1910;
        return hoisted__Bool_1910;
    }
    U32 hoisted__U32_1931 = 1;
    (void)hoisted__U32_1931;
    Bool hoisted__Bool_1932 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
    (void)hoisted__Bool_1932;
    if (hoisted__Bool_1932) {
        U32 hoisted__U32_1911 = 1;
        (void)hoisted__U32_1911;
        Bool hoisted__Bool_1912 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I8}))->tag));
        (void)hoisted__Bool_1912;
        return hoisted__Bool_1912;
    }
    U32 hoisted__U32_1933 = 1;
    (void)hoisted__U32_1933;
    Bool hoisted__Bool_1934 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
    (void)hoisted__Bool_1934;
    if (hoisted__Bool_1934) {
        U32 hoisted__U32_1913 = 1;
        (void)hoisted__U32_1913;
        Bool hoisted__Bool_1914 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U8}))->tag));
        (void)hoisted__Bool_1914;
        return hoisted__Bool_1914;
    }
    U32 hoisted__U32_1935 = 1;
    (void)hoisted__U32_1935;
    Bool hoisted__Bool_1936 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
    (void)hoisted__Bool_1936;
    if (hoisted__Bool_1936) {
        U32 hoisted__U32_1915 = 1;
        (void)hoisted__U32_1915;
        Bool hoisted__Bool_1916 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U32}))->tag));
        (void)hoisted__Bool_1916;
        return hoisted__Bool_1916;
    }
    U32 hoisted__U32_1937 = 1;
    (void)hoisted__U32_1937;
    Bool hoisted__Bool_1938 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
    (void)hoisted__Bool_1938;
    if (hoisted__Bool_1938) {
        U32 hoisted__U32_1917 = 1;
        (void)hoisted__U32_1917;
        Bool hoisted__Bool_1918 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I32}))->tag));
        (void)hoisted__Bool_1918;
        return hoisted__Bool_1918;
    }
    U32 hoisted__U32_1939 = 1;
    (void)hoisted__U32_1939;
    Bool hoisted__Bool_1940 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
    (void)hoisted__Bool_1940;
    if (hoisted__Bool_1940) {
        U32 hoisted__U32_1919 = 1;
        (void)hoisted__U32_1919;
        Bool hoisted__Bool_1920 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_U64}))->tag));
        (void)hoisted__Bool_1920;
        return hoisted__Bool_1920;
    }
    U32 hoisted__U32_1941 = 1;
    (void)hoisted__U32_1941;
    Bool hoisted__Bool_1942 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
    (void)hoisted__Bool_1942;
    if (hoisted__Bool_1942) {
        U32 hoisted__U32_1921 = 1;
        (void)hoisted__U32_1921;
        Bool hoisted__Bool_1922 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_I64}))->tag));
        (void)hoisted__Bool_1922;
        return hoisted__Bool_1922;
    }
    U32 hoisted__U32_1943 = 1;
    (void)hoisted__U32_1943;
    Bool hoisted__Bool_1944 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
    (void)hoisted__Bool_1944;
    if (hoisted__Bool_1944) {
        U32 hoisted__U32_1923 = 1;
        (void)hoisted__U32_1923;
        Bool hoisted__Bool_1924 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_F32}))->tag));
        (void)hoisted__Bool_1924;
        return hoisted__Bool_1924;
    }
    U32 hoisted__U32_1945 = 1;
    (void)hoisted__U32_1945;
    Bool hoisted__Bool_1946 = ((Bool)(((Primitive *)(self))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
    (void)hoisted__Bool_1946;
    if (hoisted__Bool_1946) {
        U32 hoisted__U32_1925 = 1;
        (void)hoisted__U32_1925;
        Bool hoisted__Bool_1926 = ((Bool)(((Primitive *)(other))->tag == ((Primitive *)(&(Primitive){.tag = Primitive_TAG_Bool}))->tag));
        (void)hoisted__Bool_1926;
        return hoisted__Bool_1926;
    }
    Bool hoisted__Bool_1947 = 0;
    (void)hoisted__Bool_1947;
    return hoisted__Bool_1947;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1969 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1969;
    if (hoisted__Bool_1969) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
        return _r; }
    }
    Bool hoisted__Bool_1970 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1970;
    if (hoisted__Bool_1970) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
        return _r; }
    }
    Bool hoisted__Bool_1971 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1971;
    if (hoisted__Bool_1971) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
        return _r; }
    }
    Bool hoisted__Bool_1972 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1972;
    if (hoisted__Bool_1972) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
        return _r; }
    }
    Bool hoisted__Bool_1973 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1973;
    if (hoisted__Bool_1973) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
        return _r; }
    }
    Bool hoisted__Bool_1974 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1974;
    if (hoisted__Bool_1974) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
        return _r; }
    }
    Bool hoisted__Bool_1975 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1975;
    if (hoisted__Bool_1975) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
        return _r; }
    }
    Bool hoisted__Bool_1976 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1976;
    if (hoisted__Bool_1976) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
        return _r; }
    }
    Bool hoisted__Bool_1977 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1977;
    if (hoisted__Bool_1977) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
        return _r; }
    }
    Bool hoisted__Bool_1978 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1978;
    if (hoisted__Bool_1978) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
        return _r; }
    }
    static Str hoisted__Str_1979 = (Str){.c_str = (void *)"Primitive.clone:15:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1979;
    UNREACHABLE(&hoisted__Str_1979);
    Str_delete(&hoisted__Str_1979, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

USize Primitive_size(void) {
    U32 hoisted__U32_1980 = 1;
    (void)hoisted__U32_1980;
    return hoisted__U32_1980;
    __builtin_unreachable();
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
    U32 hoisted__U32_2059 = 1;
    (void)hoisted__U32_2059;
    Bool hoisted__Bool_2060 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2060;
    if (hoisted__Bool_2060) {
        Str *hoisted__Str_2049 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2049;
        (void)hoisted__Str_2049;
        Bool hoisted__Bool_2050 = 0;
        (void)hoisted__Bool_2050;
        Str_delete(hoisted__Str_2049, hoisted__Bool_2050);
    }
    U32 hoisted__U32_2061 = 1;
    (void)hoisted__U32_2061;
    Bool hoisted__Bool_2062 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2062;
    if (hoisted__Bool_2062) {
        Str *hoisted__Str_2051 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2051;
        (void)hoisted__Str_2051;
        Bool hoisted__Bool_2052 = 0;
        (void)hoisted__Bool_2052;
        Str_delete(hoisted__Str_2051, hoisted__Bool_2052);
    }
    U32 hoisted__U32_2063 = 1;
    (void)hoisted__U32_2063;
    Bool hoisted__Bool_2064 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2064;
    if (hoisted__Bool_2064) {
        Str *hoisted__Str_2053 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2053;
        (void)hoisted__Str_2053;
        Bool hoisted__Bool_2054 = 0;
        (void)hoisted__Bool_2054;
        Str_delete(hoisted__Str_2053, hoisted__Bool_2054);
    }
    U32 hoisted__U32_2065 = 1;
    (void)hoisted__U32_2065;
    Bool hoisted__Bool_2066 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2066;
    if (hoisted__Bool_2066) {
        Primitive *hoisted__Primitive_2055 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Primitive_2055;
        (void)hoisted__Primitive_2055;
        Bool hoisted__Bool_2056 = 0;
        (void)hoisted__Bool_2056;
        Primitive_delete(hoisted__Primitive_2055, hoisted__Bool_2056);
    }
    U32 hoisted__U32_2067 = 1;
    (void)hoisted__U32_2067;
    Bool hoisted__Bool_2068 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2068;
    if (hoisted__Bool_2068) {
        Str *hoisted__Str_2057 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)hoisted__Str_2057;
        (void)hoisted__Str_2057;
        Bool hoisted__Bool_2058 = 0;
        (void)hoisted__Bool_2058;
        Str_delete(hoisted__Str_2057, hoisted__Bool_2058);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    U32 hoisted__U32_2154 = 1;
    (void)hoisted__U32_2154;
    Bool hoisted__Bool_2155 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag));
    (void)hoisted__Bool_2155;
    if (hoisted__Bool_2155) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
        return _r; }
    }
    U32 hoisted__U32_2156 = 1;
    (void)hoisted__U32_2156;
    Bool hoisted__Bool_2157 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_None}))->tag));
    (void)hoisted__Bool_2157;
    if (hoisted__Bool_2157) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
        return _r; }
    }
    U32 hoisted__U32_2158 = 1;
    (void)hoisted__U32_2158;
    Bool hoisted__Bool_2159 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag));
    (void)hoisted__Bool_2159;
    if (hoisted__Bool_2159) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2144 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2144;
        Type *hoisted__Type_2145 = Type_Struct(hoisted__Str_2144);
        (void)hoisted__Type_2145;
        return hoisted__Type_2145;
    }
    U32 hoisted__U32_2160 = 1;
    (void)hoisted__U32_2160;
    Bool hoisted__Bool_2161 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag));
    (void)hoisted__Bool_2161;
    if (hoisted__Bool_2161) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
        return _r; }
    }
    U32 hoisted__U32_2162 = 1;
    (void)hoisted__U32_2162;
    Bool hoisted__Bool_2163 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag));
    (void)hoisted__Bool_2163;
    if (hoisted__Bool_2163) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2146 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2146;
        Type *hoisted__Type_2147 = Type_Enum(hoisted__Str_2146);
        (void)hoisted__Type_2147;
        return hoisted__Type_2147;
    }
    U32 hoisted__U32_2164 = 1;
    (void)hoisted__U32_2164;
    Bool hoisted__Bool_2165 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_2165;
    if (hoisted__Bool_2165) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
        return _r; }
    }
    U32 hoisted__U32_2166 = 1;
    (void)hoisted__U32_2166;
    Bool hoisted__Bool_2167 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_2167;
    if (hoisted__Bool_2167) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
        return _r; }
    }
    U32 hoisted__U32_2168 = 1;
    (void)hoisted__U32_2168;
    Bool hoisted__Bool_2169 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag));
    (void)hoisted__Bool_2169;
    if (hoisted__Bool_2169) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
        return _r; }
    }
    U32 hoisted__U32_2170 = 1;
    (void)hoisted__U32_2170;
    Bool hoisted__Bool_2171 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag));
    (void)hoisted__Bool_2171;
    if (hoisted__Bool_2171) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
        return _r; }
    }
    U32 hoisted__U32_2172 = 1;
    (void)hoisted__U32_2172;
    Bool hoisted__Bool_2173 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag));
    (void)hoisted__Bool_2173;
    if (hoisted__Bool_2173) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2148 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2148;
        Type *hoisted__Type_2149 = Type_Custom(hoisted__Str_2148);
        (void)hoisted__Type_2149;
        return hoisted__Type_2149;
    }
    U32 hoisted__U32_2174 = 1;
    (void)hoisted__U32_2174;
    Bool hoisted__Bool_2175 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag));
    (void)hoisted__Bool_2175;
    if (hoisted__Bool_2175) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2150 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2150;
        Type *hoisted__Type_2151 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2150; _oa; }));
        (void)hoisted__Type_2151;
        return hoisted__Type_2151;
    }
    U32 hoisted__U32_2176 = 1;
    (void)hoisted__U32_2176;
    Bool hoisted__Bool_2177 = ((Bool)(((Type *)(self))->tag == ((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag));
    (void)hoisted__Bool_2177;
    if (hoisted__Bool_2177) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2152 = Str_clone(_clone_payload_FuncPtrSig_11);
        (void)hoisted__Str_2152;
        Type *hoisted__Type_2153 = Type_FuncPtrSig(hoisted__Str_2152);
        (void)hoisted__Type_2153;
        return hoisted__Type_2153;
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

USize Type_size(void) {
    U32 hoisted__U32_2178 = 24;
    (void)hoisted__U32_2178;
    return hoisted__U32_2178;
    __builtin_unreachable();
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
FuncType *FuncType_CoreLazyFunc() {
    FuncType *r = malloc(sizeof(FuncType));
    *r = (FuncType){ .tag = FuncType_TAG_CoreLazyFunc };
    return r;
}
Bool FuncType_eq(FuncType * self, FuncType * other) {
    U32 hoisted__U32_2212 = 1;
    (void)hoisted__U32_2212;
    Bool hoisted__Bool_2213 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
    (void)hoisted__Bool_2213;
    if (hoisted__Bool_2213) {
        U32 hoisted__U32_2190 = 1;
        (void)hoisted__U32_2190;
        Bool hoisted__Bool_2191 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Func}))->tag));
        (void)hoisted__Bool_2191;
        return hoisted__Bool_2191;
    }
    U32 hoisted__U32_2214 = 1;
    (void)hoisted__U32_2214;
    Bool hoisted__Bool_2215 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
    (void)hoisted__Bool_2215;
    if (hoisted__Bool_2215) {
        U32 hoisted__U32_2192 = 1;
        (void)hoisted__U32_2192;
        Bool hoisted__Bool_2193 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Proc}))->tag));
        (void)hoisted__Bool_2193;
        return hoisted__Bool_2193;
    }
    U32 hoisted__U32_2216 = 1;
    (void)hoisted__U32_2216;
    Bool hoisted__Bool_2217 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
    (void)hoisted__Bool_2217;
    if (hoisted__Bool_2217) {
        U32 hoisted__U32_2194 = 1;
        (void)hoisted__U32_2194;
        Bool hoisted__Bool_2195 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Test}))->tag));
        (void)hoisted__Bool_2195;
        return hoisted__Bool_2195;
    }
    U32 hoisted__U32_2218 = 1;
    (void)hoisted__U32_2218;
    Bool hoisted__Bool_2219 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
    (void)hoisted__Bool_2219;
    if (hoisted__Bool_2219) {
        U32 hoisted__U32_2196 = 1;
        (void)hoisted__U32_2196;
        Bool hoisted__Bool_2197 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_Macro}))->tag));
        (void)hoisted__Bool_2197;
        return hoisted__Bool_2197;
    }
    U32 hoisted__U32_2220 = 1;
    (void)hoisted__U32_2220;
    Bool hoisted__Bool_2221 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
    (void)hoisted__Bool_2221;
    if (hoisted__Bool_2221) {
        U32 hoisted__U32_2198 = 1;
        (void)hoisted__U32_2198;
        Bool hoisted__Bool_2199 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtFunc}))->tag));
        (void)hoisted__Bool_2199;
        return hoisted__Bool_2199;
    }
    U32 hoisted__U32_2222 = 1;
    (void)hoisted__U32_2222;
    Bool hoisted__Bool_2223 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
    (void)hoisted__Bool_2223;
    if (hoisted__Bool_2223) {
        U32 hoisted__U32_2200 = 1;
        (void)hoisted__U32_2200;
        Bool hoisted__Bool_2201 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_ExtProc}))->tag));
        (void)hoisted__Bool_2201;
        return hoisted__Bool_2201;
    }
    U32 hoisted__U32_2224 = 1;
    (void)hoisted__U32_2224;
    Bool hoisted__Bool_2225 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
    (void)hoisted__Bool_2225;
    if (hoisted__Bool_2225) {
        U32 hoisted__U32_2202 = 1;
        (void)hoisted__U32_2202;
        Bool hoisted__Bool_2203 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyFunc}))->tag));
        (void)hoisted__Bool_2203;
        return hoisted__Bool_2203;
    }
    U32 hoisted__U32_2226 = 1;
    (void)hoisted__U32_2226;
    Bool hoisted__Bool_2227 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
    (void)hoisted__Bool_2227;
    if (hoisted__Bool_2227) {
        U32 hoisted__U32_2204 = 1;
        (void)hoisted__U32_2204;
        Bool hoisted__Bool_2205 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_LazyProc}))->tag));
        (void)hoisted__Bool_2205;
        return hoisted__Bool_2205;
    }
    U32 hoisted__U32_2228 = 1;
    (void)hoisted__U32_2228;
    Bool hoisted__Bool_2229 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
    (void)hoisted__Bool_2229;
    if (hoisted__Bool_2229) {
        U32 hoisted__U32_2206 = 1;
        (void)hoisted__U32_2206;
        Bool hoisted__Bool_2207 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreFunc}))->tag));
        (void)hoisted__Bool_2207;
        return hoisted__Bool_2207;
    }
    U32 hoisted__U32_2230 = 1;
    (void)hoisted__U32_2230;
    Bool hoisted__Bool_2231 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
    (void)hoisted__Bool_2231;
    if (hoisted__Bool_2231) {
        U32 hoisted__U32_2208 = 1;
        (void)hoisted__U32_2208;
        Bool hoisted__Bool_2209 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreProc}))->tag));
        (void)hoisted__Bool_2209;
        return hoisted__Bool_2209;
    }
    U32 hoisted__U32_2232 = 1;
    (void)hoisted__U32_2232;
    Bool hoisted__Bool_2233 = ((Bool)(((FuncType *)(self))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreLazyFunc}))->tag));
    (void)hoisted__Bool_2233;
    if (hoisted__Bool_2233) {
        U32 hoisted__U32_2210 = 1;
        (void)hoisted__U32_2210;
        Bool hoisted__Bool_2211 = ((Bool)(((FuncType *)(other))->tag == ((FuncType *)(&(FuncType){.tag = FuncType_TAG_CoreLazyFunc}))->tag));
        (void)hoisted__Bool_2211;
        return hoisted__Bool_2211;
    }
    Bool hoisted__Bool_2234 = 0;
    (void)hoisted__Bool_2234;
    return hoisted__Bool_2234;
    __builtin_unreachable();
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2258 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2258;
    if (hoisted__Bool_2258) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
        return _r; }
    }
    Bool hoisted__Bool_2259 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2259;
    if (hoisted__Bool_2259) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
        return _r; }
    }
    Bool hoisted__Bool_2260 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2260;
    if (hoisted__Bool_2260) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
        return _r; }
    }
    Bool hoisted__Bool_2261 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2261;
    if (hoisted__Bool_2261) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
        return _r; }
    }
    Bool hoisted__Bool_2262 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2262;
    if (hoisted__Bool_2262) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
        return _r; }
    }
    Bool hoisted__Bool_2263 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2263;
    if (hoisted__Bool_2263) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
        return _r; }
    }
    Bool hoisted__Bool_2264 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2264;
    if (hoisted__Bool_2264) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
        return _r; }
    }
    Bool hoisted__Bool_2265 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2265;
    if (hoisted__Bool_2265) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
        return _r; }
    }
    Bool hoisted__Bool_2266 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreFunc});
    (void)hoisted__Bool_2266;
    if (hoisted__Bool_2266) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreFunc;
        return _r; }
    }
    Bool hoisted__Bool_2267 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreProc});
    (void)hoisted__Bool_2267;
    if (hoisted__Bool_2267) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreProc;
        return _r; }
    }
    Bool hoisted__Bool_2268 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_CoreLazyFunc});
    (void)hoisted__Bool_2268;
    if (hoisted__Bool_2268) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_CoreLazyFunc;
        return _r; }
    }
    static Str hoisted__Str_2269 = (Str){.c_str = (void *)"FuncType.clone:70:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2269;
    UNREACHABLE(&hoisted__Str_2269);
    Str_delete(&hoisted__Str_2269, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
    __builtin_unreachable();
}

USize FuncType_size(void) {
    U32 hoisted__U32_2270 = 1;
    (void)hoisted__U32_2270;
    return hoisted__U32_2270;
    __builtin_unreachable();
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
    U32 hoisted__U32_2277 = 1;
    (void)hoisted__U32_2277;
    Bool hoisted__Bool_2278 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
    (void)hoisted__Bool_2278;
    if (hoisted__Bool_2278) {
        U32 hoisted__U32_2271 = 1;
        (void)hoisted__U32_2271;
        Bool hoisted__Bool_2272 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Own}))->tag));
        (void)hoisted__Bool_2272;
        return hoisted__Bool_2272;
    }
    U32 hoisted__U32_2279 = 1;
    (void)hoisted__U32_2279;
    Bool hoisted__Bool_2280 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
    (void)hoisted__Bool_2280;
    if (hoisted__Bool_2280) {
        U32 hoisted__U32_2273 = 1;
        (void)hoisted__U32_2273;
        Bool hoisted__Bool_2274 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Ref}))->tag));
        (void)hoisted__Bool_2274;
        return hoisted__Bool_2274;
    }
    U32 hoisted__U32_2281 = 1;
    (void)hoisted__U32_2281;
    Bool hoisted__Bool_2282 = ((Bool)(((OwnType *)(self))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
    (void)hoisted__Bool_2282;
    if (hoisted__Bool_2282) {
        U32 hoisted__U32_2275 = 1;
        (void)hoisted__U32_2275;
        Bool hoisted__Bool_2276 = ((Bool)(((OwnType *)(other))->tag == ((OwnType *)(&(OwnType){.tag = OwnType_TAG_Shallow}))->tag));
        (void)hoisted__Bool_2276;
        return hoisted__Bool_2276;
    }
    Bool hoisted__Bool_2283 = 0;
    (void)hoisted__Bool_2283;
    return hoisted__Bool_2283;
    __builtin_unreachable();
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2291 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2291;
    if (hoisted__Bool_2291) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
        return _r; }
    }
    Bool hoisted__Bool_2292 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2292;
    if (hoisted__Bool_2292) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
        return _r; }
    }
    Bool hoisted__Bool_2293 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2293;
    if (hoisted__Bool_2293) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
        return _r; }
    }
    static Str hoisted__Str_2294 = (Str){.c_str = (void *)"OwnType.clone:108:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2294;
    UNREACHABLE(&hoisted__Str_2294);
    Str_delete(&hoisted__Str_2294, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
    __builtin_unreachable();
}

USize OwnType_size(void) {
    U32 hoisted__U32_2295 = 1;
    (void)hoisted__U32_2295;
    return hoisted__U32_2295;
    __builtin_unreachable();
}


GcStorage *GcStorage_Unset() {
    GcStorage *r = malloc(sizeof(GcStorage));
    *r = (GcStorage){ .tag = GcStorage_TAG_Unset };
    return r;
}
GcStorage *GcStorage_Stack() {
    GcStorage *r = malloc(sizeof(GcStorage));
    *r = (GcStorage){ .tag = GcStorage_TAG_Stack };
    return r;
}
GcStorage *GcStorage_HeapBox() {
    GcStorage *r = malloc(sizeof(GcStorage));
    *r = (GcStorage){ .tag = GcStorage_TAG_HeapBox };
    return r;
}
Bool GcStorage_eq(GcStorage * self, GcStorage * other) {
    U32 hoisted__U32_2302 = 1;
    (void)hoisted__U32_2302;
    Bool hoisted__Bool_2303 = ((Bool)(((GcStorage *)(self))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Unset}))->tag));
    (void)hoisted__Bool_2303;
    if (hoisted__Bool_2303) {
        U32 hoisted__U32_2296 = 1;
        (void)hoisted__U32_2296;
        Bool hoisted__Bool_2297 = ((Bool)(((GcStorage *)(other))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Unset}))->tag));
        (void)hoisted__Bool_2297;
        return hoisted__Bool_2297;
    }
    U32 hoisted__U32_2304 = 1;
    (void)hoisted__U32_2304;
    Bool hoisted__Bool_2305 = ((Bool)(((GcStorage *)(self))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Stack}))->tag));
    (void)hoisted__Bool_2305;
    if (hoisted__Bool_2305) {
        U32 hoisted__U32_2298 = 1;
        (void)hoisted__U32_2298;
        Bool hoisted__Bool_2299 = ((Bool)(((GcStorage *)(other))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_Stack}))->tag));
        (void)hoisted__Bool_2299;
        return hoisted__Bool_2299;
    }
    U32 hoisted__U32_2306 = 1;
    (void)hoisted__U32_2306;
    Bool hoisted__Bool_2307 = ((Bool)(((GcStorage *)(self))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_HeapBox}))->tag));
    (void)hoisted__Bool_2307;
    if (hoisted__Bool_2307) {
        U32 hoisted__U32_2300 = 1;
        (void)hoisted__U32_2300;
        Bool hoisted__Bool_2301 = ((Bool)(((GcStorage *)(other))->tag == ((GcStorage *)(&(GcStorage){.tag = GcStorage_TAG_HeapBox}))->tag));
        (void)hoisted__Bool_2301;
        return hoisted__Bool_2301;
    }
    Bool hoisted__Bool_2308 = 0;
    (void)hoisted__Bool_2308;
    return hoisted__Bool_2308;
    __builtin_unreachable();
}

void GcStorage_delete(GcStorage * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

GcStorage * GcStorage_clone(GcStorage * self) {
    Bool hoisted__Bool_2316 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Unset});
    (void)hoisted__Bool_2316;
    if (hoisted__Bool_2316) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
        return _r; }
    }
    Bool hoisted__Bool_2317 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_Stack});
    (void)hoisted__Bool_2317;
    if (hoisted__Bool_2317) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Stack;
        return _r; }
    }
    Bool hoisted__Bool_2318 = GcStorage_eq(self, &(GcStorage){.tag = GcStorage_TAG_HeapBox});
    (void)hoisted__Bool_2318;
    if (hoisted__Bool_2318) {
        { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_HeapBox;
        return _r; }
    }
    static Str hoisted__Str_2319 = (Str){.c_str = (void *)"GcStorage.clone:119:1", .count = 21ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2319;
    UNREACHABLE(&hoisted__Str_2319);
    Str_delete(&hoisted__Str_2319, (Bool){0});
    { GcStorage *_r = malloc(sizeof(GcStorage)); _r->tag = GcStorage_TAG_Unset;
    return _r; }
    __builtin_unreachable();
}

USize GcStorage_size(void) {
    U32 hoisted__U32_2320 = 1;
    (void)hoisted__U32_2320;
    return hoisted__U32_2320;
    __builtin_unreachable();
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2322 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2322;
    Declaration *hoisted__Declaration_2323 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2323->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2323->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2323->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2323->is_mut = self->is_mut;
    hoisted__Declaration_2323->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2323->is_priv = self->is_priv;
    hoisted__Declaration_2323->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2323->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2323->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2323->default_value = hoisted__Expr_2322;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2323->orig_name = *_ca; free(_ca); }
    { GcStorage *_ca = GcStorage_clone(&self->gc_storage); hoisted__Declaration_2323->gc_storage = *_ca; free(_ca); }
    (void)hoisted__Declaration_2323;
    return hoisted__Declaration_2323;
    __builtin_unreachable();
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2324 = 0;
    (void)hoisted__Bool_2324;
    Str_delete(&self->name, hoisted__Bool_2324);
    Bool hoisted__Bool_2325 = 0;
    (void)hoisted__Bool_2325;
    Str_delete(&self->doc, hoisted__Bool_2325);
    Bool hoisted__Bool_2326 = 0;
    (void)hoisted__Bool_2326;
    Str_delete(&self->explicit_type, hoisted__Bool_2326);
    Bool hoisted__Bool_2327 = 0;
    (void)hoisted__Bool_2327;
    Bool_delete(&self->is_mut, hoisted__Bool_2327);
    Bool hoisted__Bool_2328 = 0;
    (void)hoisted__Bool_2328;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2328);
    Bool hoisted__Bool_2329 = 0;
    (void)hoisted__Bool_2329;
    Bool_delete(&self->is_priv, hoisted__Bool_2329);
    Bool hoisted__Bool_2330 = 0;
    (void)hoisted__Bool_2330;
    Bool_delete(&self->used, hoisted__Bool_2330);
    Bool hoisted__Bool_2331 = 0;
    (void)hoisted__Bool_2331;
    OwnType_delete(&self->own_type, hoisted__Bool_2331);
    Bool hoisted__Bool_2332 = 0;
    (void)hoisted__Bool_2332;
    Type_delete(&self->til_type, hoisted__Bool_2332);
    Bool hoisted__Bool_2333 = 1;
    (void)hoisted__Bool_2333;
    Expr_delete(self->default_value, hoisted__Bool_2333);
    Bool hoisted__Bool_2334 = 0;
    (void)hoisted__Bool_2334;
    Str_delete(&self->orig_name, hoisted__Bool_2334);
    Bool hoisted__Bool_2335 = 0;
    (void)hoisted__Bool_2335;
    GcStorage_delete(&self->gc_storage, hoisted__Bool_2335);
    if (call_free) {
        free(self);
    }
}

USize Declaration_size(void) {
    U32 hoisted__U32_2336 = 112;
    (void)hoisted__U32_2336;
    return hoisted__U32_2336;
    __builtin_unreachable();
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2338 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2338->func_type = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->params); hoisted__FunctionDef_2338->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2338->return_type = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->throw_types); hoisted__FunctionDef_2338->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2338->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2338->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2338->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2338->return_shallow_explicit = self->return_shallow_explicit;
    hoisted__FunctionDef_2338->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2338->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__FunctionDef_2338->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2338->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2338;
    return hoisted__FunctionDef_2338;
    __builtin_unreachable();
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2339 = 0;
    (void)hoisted__Bool_2339;
    FuncType_delete(&self->func_type, hoisted__Bool_2339);
    Bool hoisted__Bool_2340 = 0;
    (void)hoisted__Bool_2340;
    Vec__Declaration_delete(&self->params, hoisted__Bool_2340);
    Bool hoisted__Bool_2341 = 0;
    (void)hoisted__Bool_2341;
    Str_delete(&self->return_type, hoisted__Bool_2341);
    Bool hoisted__Bool_2342 = 0;
    (void)hoisted__Bool_2342;
    Vec__Str_delete(&self->throw_types, hoisted__Bool_2342);
    Bool hoisted__Bool_2343 = 0;
    (void)hoisted__Bool_2343;
    I32_delete(&self->variadic_index, hoisted__Bool_2343);
    Bool hoisted__Bool_2344 = 0;
    (void)hoisted__Bool_2344;
    I32_delete(&self->kwargs_index, hoisted__Bool_2344);
    Bool hoisted__Bool_2345 = 0;
    (void)hoisted__Bool_2345;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2345);
    Bool hoisted__Bool_2346 = 0;
    (void)hoisted__Bool_2346;
    Bool_delete(&self->return_shallow_explicit, hoisted__Bool_2346);
    Bool hoisted__Bool_2347 = 0;
    (void)hoisted__Bool_2347;
    Bool_delete(&self->auto_generated, hoisted__Bool_2347);
    Bool hoisted__Bool_2348 = 0;
    (void)hoisted__Bool_2348;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2348);
    Bool hoisted__Bool_2349 = 0;
    (void)hoisted__Bool_2349;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2349);
    Bool hoisted__Bool_2350 = 0;
    (void)hoisted__Bool_2350;
    Str_delete(&self->closure_name, hoisted__Bool_2350);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2351 = 0;
    (void)hoisted__U32_2351;
    U64 hoisted__U64_2352 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2351); });
    (void)hoisted__U64_2352;
    return hoisted__U64_2352;
    __builtin_unreachable();
}

USize FunctionDef_size(void) {
    U32 hoisted__U32_2353 = 104;
    (void)hoisted__U32_2353;
    return hoisted__U32_2353;
    __builtin_unreachable();
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2356 = malloc(sizeof(FCallData));
    hoisted__FCallData_2356->is_splat = self->is_splat;
    hoisted__FCallData_2356->does_throw = self->does_throw;
    hoisted__FCallData_2356->is_bang = self->is_bang;
    hoisted__FCallData_2356->own_args = self->own_args;
    hoisted__FCallData_2356->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2356->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2356;
    return hoisted__FCallData_2356;
    __builtin_unreachable();
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2357 = 0;
    (void)hoisted__Bool_2357;
    Bool_delete(&self->is_splat, hoisted__Bool_2357);
    Bool hoisted__Bool_2358 = 0;
    (void)hoisted__Bool_2358;
    Bool_delete(&self->does_throw, hoisted__Bool_2358);
    Bool hoisted__Bool_2359 = 0;
    (void)hoisted__Bool_2359;
    Bool_delete(&self->is_bang, hoisted__Bool_2359);
    Bool hoisted__Bool_2360 = 0;
    (void)hoisted__Bool_2360;
    U64_delete(&self->own_args, hoisted__Bool_2360);
    Bool hoisted__Bool_2361 = 0;
    (void)hoisted__Bool_2361;
    Bool_delete(&self->swap_replace, hoisted__Bool_2361);
    Bool hoisted__Bool_2362 = 0;
    (void)hoisted__Bool_2362;
    Type_delete(&self->til_type, hoisted__Bool_2362);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2363 = 0;
    (void)hoisted__U32_2363;
    U64 hoisted__U64_2364 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2363); });
    (void)hoisted__U64_2364;
    return hoisted__U64_2364;
    __builtin_unreachable();
}

USize FCallData_size(void) {
    U32 hoisted__U32_2365 = 48;
    (void)hoisted__U32_2365;
    return hoisted__U32_2365;
    __builtin_unreachable();
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2378 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2378->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2378->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2378;
    return hoisted__LiteralNumData_2378;
    __builtin_unreachable();
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2379 = 0;
    (void)hoisted__Bool_2379;
    Str_delete(&self->text, hoisted__Bool_2379);
    Bool hoisted__Bool_2380 = 0;
    (void)hoisted__Bool_2380;
    Type_delete(&self->til_type, hoisted__Bool_2380);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2381 = 0;
    (void)hoisted__U32_2381;
    U64 hoisted__U64_2382 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2381); });
    (void)hoisted__U64_2382;
    return hoisted__U64_2382;
    __builtin_unreachable();
}

USize LiteralNumData_size(void) {
    U32 hoisted__U32_2383 = 40;
    (void)hoisted__U32_2383;
    return hoisted__U32_2383;
    __builtin_unreachable();
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2393 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2393->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2393->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2393;
    return hoisted__IdentData_2393;
    __builtin_unreachable();
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2394 = 0;
    (void)hoisted__Bool_2394;
    Str_delete(&self->name, hoisted__Bool_2394);
    Bool hoisted__Bool_2395 = 0;
    (void)hoisted__Bool_2395;
    Type_delete(&self->til_type, hoisted__Bool_2395);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2396 = 0;
    (void)hoisted__U32_2396;
    U64 hoisted__U64_2397 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2396); });
    (void)hoisted__U64_2397;
    return hoisted__U64_2397;
    __builtin_unreachable();
}

USize IdentData_size(void) {
    U32 hoisted__U32_2398 = 40;
    (void)hoisted__U32_2398;
    return hoisted__U32_2398;
    __builtin_unreachable();
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2404 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2404->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2404->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2404;
    return hoisted__FieldAccessData_2404;
    __builtin_unreachable();
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2405 = 0;
    (void)hoisted__Bool_2405;
    Str_delete(&self->name, hoisted__Bool_2405);
    Bool hoisted__Bool_2406 = 0;
    (void)hoisted__Bool_2406;
    Type_delete(&self->til_type, hoisted__Bool_2406);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2407 = 0;
    (void)hoisted__U32_2407;
    U64 hoisted__U64_2408 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2407); });
    (void)hoisted__U64_2408;
    return hoisted__U64_2408;
    __builtin_unreachable();
}

USize FieldAccessData_size(void) {
    U32 hoisted__U32_2409 = 40;
    (void)hoisted__U32_2409;
    return hoisted__U32_2409;
    __builtin_unreachable();
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2414 = malloc(sizeof(StructDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->fields); hoisted__StructDef_2414->fields = *_ca; free(_ca); }
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__StructDef_2414->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2414->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2414->is_interface = self->is_interface;
    hoisted__StructDef_2414->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2414->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2414;
    return hoisted__StructDef_2414;
    __builtin_unreachable();
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2415 = 0;
    (void)hoisted__Bool_2415;
    Vec__Declaration_delete(&self->fields, hoisted__Bool_2415);
    Bool hoisted__Bool_2416 = 0;
    (void)hoisted__Bool_2416;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2416);
    Bool hoisted__Bool_2417 = 0;
    (void)hoisted__Bool_2417;
    Str_delete(&self->c_tag, hoisted__Bool_2417);
    Bool hoisted__Bool_2418 = 0;
    (void)hoisted__Bool_2418;
    Bool_delete(&self->is_interface, hoisted__Bool_2418);
    Bool hoisted__Bool_2419 = 0;
    (void)hoisted__Bool_2419;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2419);
    Bool hoisted__Bool_2420 = 0;
    (void)hoisted__Bool_2420;
    Str_delete(&self->implements_name, hoisted__Bool_2420);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2421 = 0;
    (void)hoisted__U32_2421;
    U64 hoisted__U64_2422 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2421); });
    (void)hoisted__U64_2422;
    return hoisted__U64_2422;
    __builtin_unreachable();
}

USize StructDef_size(void) {
    U32 hoisted__U32_2423 = 72;
    (void)hoisted__U32_2423;
    return hoisted__U32_2423;
    __builtin_unreachable();
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2428 = malloc(sizeof(EnumDef));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->ns_decls); hoisted__EnumDef_2428->ns_decls = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->variants); hoisted__EnumDef_2428->variants = *_ca; free(_ca); }
    { Map__I64_Str *_ca = Map__I64_Str_clone(&self->payload_types); hoisted__EnumDef_2428->payload_types = *_ca; free(_ca); }
    { Vec__Bool *_ca = Vec__Bool_clone(&self->payload_consts); hoisted__EnumDef_2428->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2428->implements_name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->tag_type); hoisted__EnumDef_2428->tag_type = *_ca; free(_ca); }
    { Vec__I64 *_ca = Vec__I64_clone(&self->tag_values); hoisted__EnumDef_2428->tag_values = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2428;
    return hoisted__EnumDef_2428;
    __builtin_unreachable();
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2429 = 0;
    (void)hoisted__Bool_2429;
    Vec__Declaration_delete(&self->ns_decls, hoisted__Bool_2429);
    Bool hoisted__Bool_2430 = 0;
    (void)hoisted__Bool_2430;
    Vec__Str_delete(&self->variants, hoisted__Bool_2430);
    Bool hoisted__Bool_2431 = 0;
    (void)hoisted__Bool_2431;
    Map__I64_Str_delete(&self->payload_types, hoisted__Bool_2431);
    Bool hoisted__Bool_2432 = 0;
    (void)hoisted__Bool_2432;
    Vec__Bool_delete(&self->payload_consts, hoisted__Bool_2432);
    Bool hoisted__Bool_2433 = 0;
    (void)hoisted__Bool_2433;
    Str_delete(&self->implements_name, hoisted__Bool_2433);
    Bool hoisted__Bool_2434 = 0;
    (void)hoisted__Bool_2434;
    Str_delete(&self->tag_type, hoisted__Bool_2434);
    Bool hoisted__Bool_2435 = 0;
    (void)hoisted__Bool_2435;
    Vec__I64_delete(&self->tag_values, hoisted__Bool_2435);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2436 = 0;
    (void)hoisted__U32_2436;
    U64 hoisted__U64_2437 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2436); });
    (void)hoisted__U64_2437;
    return hoisted__U64_2437;
    __builtin_unreachable();
}

USize EnumDef_size(void) {
    U32 hoisted__U32_2438 = 128;
    (void)hoisted__U32_2438;
    return hoisted__U32_2438;
    __builtin_unreachable();
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2468 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2468->name = *_ca; free(_ca); }
    hoisted__AssignData_2468->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2468->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2468->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2468;
    return hoisted__AssignData_2468;
    __builtin_unreachable();
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2469 = 0;
    (void)hoisted__Bool_2469;
    Str_delete(&self->name, hoisted__Bool_2469);
    Bool hoisted__Bool_2470 = 0;
    (void)hoisted__Bool_2470;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2470);
    Bool hoisted__Bool_2471 = 0;
    (void)hoisted__Bool_2471;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2471);
    Bool hoisted__Bool_2472 = 0;
    (void)hoisted__Bool_2472;
    Bool_delete(&self->swap_replace, hoisted__Bool_2472);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2473 = 0;
    (void)hoisted__U32_2473;
    U64 hoisted__U64_2474 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2473); });
    (void)hoisted__U64_2474;
    return hoisted__U64_2474;
    __builtin_unreachable();
}

USize AssignData_size(void) {
    U32 hoisted__U32_2475 = 24;
    (void)hoisted__U32_2475;
    return hoisted__U32_2475;
    __builtin_unreachable();
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2477 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2477->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2477->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2477;
    return hoisted__FieldAssignData_2477;
    __builtin_unreachable();
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2478 = 0;
    (void)hoisted__Bool_2478;
    Str_delete(&self->name, hoisted__Bool_2478);
    Bool hoisted__Bool_2479 = 0;
    (void)hoisted__Bool_2479;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2479);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2480 = 0;
    (void)hoisted__U32_2480;
    U64 hoisted__U64_2481 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2480); });
    (void)hoisted__U64_2481;
    return hoisted__U64_2481;
    __builtin_unreachable();
}

USize FieldAssignData_size(void) {
    U32 hoisted__U32_2482 = 24;
    (void)hoisted__U32_2482;
    return hoisted__U32_2482;
    __builtin_unreachable();
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2484 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2484->name = *_ca; free(_ca); }
    hoisted__ForInData_2484->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2484->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->name2); hoisted__ForInData_2484->name2 = *_ca; free(_ca); }
    hoisted__ForInData_2484->is_mut2 = self->is_mut2;
    (void)hoisted__ForInData_2484;
    return hoisted__ForInData_2484;
    __builtin_unreachable();
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2485 = 0;
    (void)hoisted__Bool_2485;
    Str_delete(&self->name, hoisted__Bool_2485);
    Bool hoisted__Bool_2486 = 0;
    (void)hoisted__Bool_2486;
    Bool_delete(&self->is_mut, hoisted__Bool_2486);
    Bool hoisted__Bool_2487 = 0;
    (void)hoisted__Bool_2487;
    Type_delete(&self->til_type, hoisted__Bool_2487);
    Bool hoisted__Bool_2488 = 0;
    (void)hoisted__Bool_2488;
    Str_delete(&self->name2, hoisted__Bool_2488);
    Bool hoisted__Bool_2489 = 0;
    (void)hoisted__Bool_2489;
    Bool_delete(&self->is_mut2, hoisted__Bool_2489);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2490 = 0;
    (void)hoisted__U32_2490;
    U64 hoisted__U64_2491 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2490); });
    (void)hoisted__U64_2491;
    return hoisted__U64_2491;
    __builtin_unreachable();
}

USize ForInData_size(void) {
    U32 hoisted__U32_2492 = 72;
    (void)hoisted__U32_2492;
    return hoisted__U32_2492;
    __builtin_unreachable();
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
    U32 hoisted__U32_2533 = 1;
    (void)hoisted__U32_2533;
    Bool hoisted__Bool_2534 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_2534;
    if (hoisted__Bool_2534) {
        Str *hoisted__Str_2527 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)hoisted__Str_2527;
        (void)hoisted__Str_2527;
        Bool hoisted__Bool_2528 = 0;
        (void)hoisted__Bool_2528;
        Str_delete(hoisted__Str_2527, hoisted__Bool_2528);
    }
    U32 hoisted__U32_2535 = 1;
    (void)hoisted__U32_2535;
    Bool hoisted__Bool_2536 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_2536;
    if (hoisted__Bool_2536) {
        LiteralNumData *hoisted__LiteralNumData_2529 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)hoisted__LiteralNumData_2529;
        (void)hoisted__LiteralNumData_2529;
        Bool hoisted__Bool_2530 = 0;
        (void)hoisted__Bool_2530;
        LiteralNumData_delete(hoisted__LiteralNumData_2529, hoisted__Bool_2530);
    }
    U32 hoisted__U32_2537 = 1;
    (void)hoisted__U32_2537;
    Bool hoisted__Bool_2538 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_2538;
    if (hoisted__Bool_2538) {
        Bool *hoisted__Bool_2531 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)hoisted__Bool_2531;
        (void)hoisted__Bool_2531;
        Bool hoisted__Bool_2532 = 0;
        (void)hoisted__Bool_2532;
        Bool_delete(hoisted__Bool_2531, hoisted__Bool_2532);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    U32 hoisted__U32_2584 = 1;
    (void)hoisted__U32_2584;
    Bool hoisted__Bool_2585 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Str}))->tag));
    (void)hoisted__Bool_2585;
    if (hoisted__Bool_2585) {
        Str *_clone_payload_Str_0 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2579 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2579;
        Literal *hoisted__Literal_2580 = Literal_Str(hoisted__Str_2579);
        (void)hoisted__Literal_2580;
        return hoisted__Literal_2580;
    }
    U32 hoisted__U32_2586 = 1;
    (void)hoisted__U32_2586;
    Bool hoisted__Bool_2587 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Num}))->tag));
    (void)hoisted__Bool_2587;
    if (hoisted__Bool_2587) {
        LiteralNumData *_clone_payload_Num_1 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2581 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2581;
        Literal *hoisted__Literal_2582 = Literal_Num(hoisted__LiteralNumData_2581);
        (void)hoisted__Literal_2582;
        return hoisted__Literal_2582;
    }
    U32 hoisted__U32_2588 = 1;
    (void)hoisted__U32_2588;
    Bool hoisted__Bool_2589 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Bool}))->tag));
    (void)hoisted__Bool_2589;
    if (hoisted__Bool_2589) {
        Bool *_clone_payload_Bool_2 = ((void *)((U8 *)(self) + offsetof(Literal, data)));
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2583 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2583;
        return hoisted__Literal_2583;
    }
    U32 hoisted__U32_2590 = 1;
    (void)hoisted__U32_2590;
    Bool hoisted__Bool_2591 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_Null}))->tag));
    (void)hoisted__Bool_2591;
    if (hoisted__Bool_2591) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
        return _r; }
    }
    U32 hoisted__U32_2592 = 1;
    (void)hoisted__U32_2592;
    Bool hoisted__Bool_2593 = ((Bool)(((Literal *)(self))->tag == ((Literal *)(&(Literal){.tag = Literal_TAG_MapLit}))->tag));
    (void)hoisted__Bool_2593;
    if (hoisted__Bool_2593) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
        return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
    __builtin_unreachable();
}

USize Literal_size(void) {
    U32 hoisted__U32_2594 = 48;
    (void)hoisted__U32_2594;
    return hoisted__U32_2594;
    __builtin_unreachable();
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2597 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2597->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2597->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2597;
    return hoisted__MatchData_2597;
    __builtin_unreachable();
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2598 = 0;
    (void)hoisted__Bool_2598;
    Type_delete(&self->til_type, hoisted__Bool_2598);
    Bool hoisted__Bool_2599 = 0;
    (void)hoisted__Bool_2599;
    Str_delete(&self->result_temp, hoisted__Bool_2599);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2600 = 0;
    (void)hoisted__U32_2600;
    U64 hoisted__U64_2601 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2600); });
    (void)hoisted__U64_2601;
    return hoisted__U64_2601;
    __builtin_unreachable();
}

USize MatchData_size(void) {
    U32 hoisted__U32_2602 = 40;
    (void)hoisted__U32_2602;
    return hoisted__U32_2602;
    __builtin_unreachable();
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2607 = malloc(sizeof(CaptureBlockData));
    { Vec__Declaration *_ca = Vec__Declaration_clone(&self->captures); hoisted__CaptureBlockData_2607->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__CaptureBlockData_2607->closure_name = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2607;
    return hoisted__CaptureBlockData_2607;
    __builtin_unreachable();
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2608 = 0;
    (void)hoisted__Bool_2608;
    Vec__Declaration_delete(&self->captures, hoisted__Bool_2608);
    Bool hoisted__Bool_2609 = 0;
    (void)hoisted__Bool_2609;
    Str_delete(&self->closure_name, hoisted__Bool_2609);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2610 = 0;
    (void)hoisted__U32_2610;
    U64 hoisted__U64_2611 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2610); });
    (void)hoisted__U64_2611;
    return hoisted__U64_2611;
    __builtin_unreachable();
}

USize CaptureBlockData_size(void) {
    U32 hoisted__U32_2612 = 32;
    (void)hoisted__U32_2612;
    return hoisted__U32_2612;
    __builtin_unreachable();
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
NodeType *NodeType_ListPattern() {
    NodeType *r = malloc(sizeof(NodeType));
    r->tag = NodeType_TAG_ListPattern;
    return r;
}
void NodeType_delete(NodeType * self, Bool call_free) {
    U32 hoisted__U32_3081 = 1;
    (void)hoisted__U32_3081;
    Bool hoisted__Bool_3082 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3082;
    if (hoisted__Bool_3082) {
        Literal *hoisted__Literal_3051 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__Literal_3051;
        (void)hoisted__Literal_3051;
        Bool hoisted__Bool_3052 = 0;
        (void)hoisted__Bool_3052;
        Literal_delete(hoisted__Literal_3051, hoisted__Bool_3052);
    }
    U32 hoisted__U32_3083 = 1;
    (void)hoisted__U32_3083;
    Bool hoisted__Bool_3084 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3084;
    if (hoisted__Bool_3084) {
        IdentData *hoisted__IdentData_3053 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__IdentData_3053;
        (void)hoisted__IdentData_3053;
        Bool hoisted__Bool_3054 = 0;
        (void)hoisted__Bool_3054;
        IdentData_delete(hoisted__IdentData_3053, hoisted__Bool_3054);
    }
    U32 hoisted__U32_3085 = 1;
    (void)hoisted__U32_3085;
    Bool hoisted__Bool_3086 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3086;
    if (hoisted__Bool_3086) {
        Declaration *hoisted__Declaration_3055 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__Declaration_3055;
        (void)hoisted__Declaration_3055;
        Bool hoisted__Bool_3056 = 0;
        (void)hoisted__Bool_3056;
        Declaration_delete(hoisted__Declaration_3055, hoisted__Bool_3056);
    }
    U32 hoisted__U32_3087 = 1;
    (void)hoisted__U32_3087;
    Bool hoisted__Bool_3088 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3088;
    if (hoisted__Bool_3088) {
        AssignData *hoisted__AssignData_3057 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__AssignData_3057;
        (void)hoisted__AssignData_3057;
        Bool hoisted__Bool_3058 = 0;
        (void)hoisted__Bool_3058;
        AssignData_delete(hoisted__AssignData_3057, hoisted__Bool_3058);
    }
    U32 hoisted__U32_3089 = 1;
    (void)hoisted__U32_3089;
    Bool hoisted__Bool_3090 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3090;
    if (hoisted__Bool_3090) {
        FCallData *hoisted__FCallData_3059 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FCallData_3059;
        (void)hoisted__FCallData_3059;
        Bool hoisted__Bool_3060 = 0;
        (void)hoisted__Bool_3060;
        FCallData_delete(hoisted__FCallData_3059, hoisted__Bool_3060);
    }
    U32 hoisted__U32_3091 = 1;
    (void)hoisted__U32_3091;
    Bool hoisted__Bool_3092 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3092;
    if (hoisted__Bool_3092) {
        FunctionDef *hoisted__FunctionDef_3061 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FunctionDef_3061;
        (void)hoisted__FunctionDef_3061;
        Bool hoisted__Bool_3062 = 0;
        (void)hoisted__Bool_3062;
        FunctionDef_delete(hoisted__FunctionDef_3061, hoisted__Bool_3062);
    }
    U32 hoisted__U32_3093 = 1;
    (void)hoisted__U32_3093;
    Bool hoisted__Bool_3094 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3094;
    if (hoisted__Bool_3094) {
        StructDef *hoisted__StructDef_3063 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__StructDef_3063;
        (void)hoisted__StructDef_3063;
        Bool hoisted__Bool_3064 = 0;
        (void)hoisted__Bool_3064;
        StructDef_delete(hoisted__StructDef_3063, hoisted__Bool_3064);
    }
    U32 hoisted__U32_3095 = 1;
    (void)hoisted__U32_3095;
    Bool hoisted__Bool_3096 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3096;
    if (hoisted__Bool_3096) {
        EnumDef *hoisted__EnumDef_3065 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__EnumDef_3065;
        (void)hoisted__EnumDef_3065;
        Bool hoisted__Bool_3066 = 0;
        (void)hoisted__Bool_3066;
        EnumDef_delete(hoisted__EnumDef_3065, hoisted__Bool_3066);
    }
    U32 hoisted__U32_3097 = 1;
    (void)hoisted__U32_3097;
    Bool hoisted__Bool_3098 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3098;
    if (hoisted__Bool_3098) {
        FieldAccessData *hoisted__FieldAccessData_3067 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FieldAccessData_3067;
        (void)hoisted__FieldAccessData_3067;
        Bool hoisted__Bool_3068 = 0;
        (void)hoisted__Bool_3068;
        FieldAccessData_delete(hoisted__FieldAccessData_3067, hoisted__Bool_3068);
    }
    U32 hoisted__U32_3099 = 1;
    (void)hoisted__U32_3099;
    Bool hoisted__Bool_3100 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3100;
    if (hoisted__Bool_3100) {
        FieldAssignData *hoisted__FieldAssignData_3069 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__FieldAssignData_3069;
        (void)hoisted__FieldAssignData_3069;
        Bool hoisted__Bool_3070 = 0;
        (void)hoisted__Bool_3070;
        FieldAssignData_delete(hoisted__FieldAssignData_3069, hoisted__Bool_3070);
    }
    U32 hoisted__U32_3101 = 1;
    (void)hoisted__U32_3101;
    Bool hoisted__Bool_3102 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3102;
    if (hoisted__Bool_3102) {
        ForInData *hoisted__ForInData_3071 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__ForInData_3071;
        (void)hoisted__ForInData_3071;
        Bool hoisted__Bool_3072 = 0;
        (void)hoisted__Bool_3072;
        ForInData_delete(hoisted__ForInData_3071, hoisted__Bool_3072);
    }
    U32 hoisted__U32_3103 = 1;
    (void)hoisted__U32_3103;
    Bool hoisted__Bool_3104 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3104;
    if (hoisted__Bool_3104) {
        Str *hoisted__Str_3073 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__Str_3073;
        (void)hoisted__Str_3073;
        Bool hoisted__Bool_3074 = 0;
        (void)hoisted__Bool_3074;
        Str_delete(hoisted__Str_3073, hoisted__Bool_3074);
    }
    U32 hoisted__U32_3105 = 1;
    (void)hoisted__U32_3105;
    Bool hoisted__Bool_3106 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3106;
    if (hoisted__Bool_3106) {
        MatchData *hoisted__MatchData_3075 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__MatchData_3075;
        (void)hoisted__MatchData_3075;
        Bool hoisted__Bool_3076 = 0;
        (void)hoisted__Bool_3076;
        MatchData_delete(hoisted__MatchData_3075, hoisted__Bool_3076);
    }
    U32 hoisted__U32_3107 = 1;
    (void)hoisted__U32_3107;
    Bool hoisted__Bool_3108 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3108;
    if (hoisted__Bool_3108) {
        CaptureBlockData *hoisted__CaptureBlockData_3077 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__CaptureBlockData_3077;
        (void)hoisted__CaptureBlockData_3077;
        Bool hoisted__Bool_3078 = 0;
        (void)hoisted__Bool_3078;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3077, hoisted__Bool_3078);
    }
    U32 hoisted__U32_3109 = 1;
    (void)hoisted__U32_3109;
    Bool hoisted__Bool_3110 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3110;
    if (hoisted__Bool_3110) {
        CaptureBlockData *hoisted__CaptureBlockData_3079 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)hoisted__CaptureBlockData_3079;
        (void)hoisted__CaptureBlockData_3079;
        Bool hoisted__Bool_3080 = 0;
        (void)hoisted__Bool_3080;
        CaptureBlockData_delete(hoisted__CaptureBlockData_3079, hoisted__Bool_3080);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    U32 hoisted__U32_3334 = 1;
    (void)hoisted__U32_3334;
    Bool hoisted__Bool_3335 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Body}))->tag));
    (void)hoisted__Bool_3335;
    if (hoisted__Bool_3335) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
        return _r; }
    }
    U32 hoisted__U32_3336 = 1;
    (void)hoisted__U32_3336;
    Bool hoisted__Bool_3337 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Literal}))->tag));
    (void)hoisted__Bool_3337;
    if (hoisted__Bool_3337) {
        Literal *_clone_payload_Literal_1 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3304 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3304;
        NodeType *hoisted__NodeType_3305 = NodeType_Literal(hoisted__Literal_3304);
        (void)hoisted__NodeType_3305;
        return hoisted__NodeType_3305;
    }
    U32 hoisted__U32_3338 = 1;
    (void)hoisted__U32_3338;
    Bool hoisted__Bool_3339 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Ident}))->tag));
    (void)hoisted__Bool_3339;
    if (hoisted__Bool_3339) {
        IdentData *_clone_payload_Ident_2 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3306 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3306;
        NodeType *hoisted__NodeType_3307 = NodeType_Ident(hoisted__IdentData_3306);
        (void)hoisted__NodeType_3307;
        return hoisted__NodeType_3307;
    }
    U32 hoisted__U32_3340 = 1;
    (void)hoisted__U32_3340;
    Bool hoisted__Bool_3341 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Decl}))->tag));
    (void)hoisted__Bool_3341;
    if (hoisted__Bool_3341) {
        Declaration *_clone_payload_Decl_3 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3308 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3308;
        NodeType *hoisted__NodeType_3309 = NodeType_Decl(hoisted__Declaration_3308);
        (void)hoisted__NodeType_3309;
        return hoisted__NodeType_3309;
    }
    U32 hoisted__U32_3342 = 1;
    (void)hoisted__U32_3342;
    Bool hoisted__Bool_3343 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Assign}))->tag));
    (void)hoisted__Bool_3343;
    if (hoisted__Bool_3343) {
        AssignData *_clone_payload_Assign_4 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3310 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3310;
        NodeType *hoisted__NodeType_3311 = NodeType_Assign(hoisted__AssignData_3310);
        (void)hoisted__NodeType_3311;
        return hoisted__NodeType_3311;
    }
    U32 hoisted__U32_3344 = 1;
    (void)hoisted__U32_3344;
    Bool hoisted__Bool_3345 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FCall}))->tag));
    (void)hoisted__Bool_3345;
    if (hoisted__Bool_3345) {
        FCallData *_clone_payload_FCall_5 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3312 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3312;
        NodeType *hoisted__NodeType_3313 = NodeType_FCall(hoisted__FCallData_3312);
        (void)hoisted__NodeType_3313;
        return hoisted__NodeType_3313;
    }
    U32 hoisted__U32_3346 = 1;
    (void)hoisted__U32_3346;
    Bool hoisted__Bool_3347 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FuncDef}))->tag));
    (void)hoisted__Bool_3347;
    if (hoisted__Bool_3347) {
        FunctionDef *_clone_payload_FuncDef_6 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3314 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3314;
        NodeType *hoisted__NodeType_3315 = NodeType_FuncDef(hoisted__FunctionDef_3314);
        (void)hoisted__NodeType_3315;
        return hoisted__NodeType_3315;
    }
    U32 hoisted__U32_3348 = 1;
    (void)hoisted__U32_3348;
    Bool hoisted__Bool_3349 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_StructDef}))->tag));
    (void)hoisted__Bool_3349;
    if (hoisted__Bool_3349) {
        StructDef *_clone_payload_StructDef_7 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3316 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3316;
        NodeType *hoisted__NodeType_3317 = NodeType_StructDef(hoisted__StructDef_3316);
        (void)hoisted__NodeType_3317;
        return hoisted__NodeType_3317;
    }
    U32 hoisted__U32_3350 = 1;
    (void)hoisted__U32_3350;
    Bool hoisted__Bool_3351 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_EnumDef}))->tag));
    (void)hoisted__Bool_3351;
    if (hoisted__Bool_3351) {
        EnumDef *_clone_payload_EnumDef_8 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3318 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3318;
        NodeType *hoisted__NodeType_3319 = NodeType_EnumDef(hoisted__EnumDef_3318);
        (void)hoisted__NodeType_3319;
        return hoisted__NodeType_3319;
    }
    U32 hoisted__U32_3352 = 1;
    (void)hoisted__U32_3352;
    Bool hoisted__Bool_3353 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAccess}))->tag));
    (void)hoisted__Bool_3353;
    if (hoisted__Bool_3353) {
        FieldAccessData *_clone_payload_FieldAccess_9 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3320 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3320;
        NodeType *hoisted__NodeType_3321 = NodeType_FieldAccess(hoisted__FieldAccessData_3320);
        (void)hoisted__NodeType_3321;
        return hoisted__NodeType_3321;
    }
    U32 hoisted__U32_3354 = 1;
    (void)hoisted__U32_3354;
    Bool hoisted__Bool_3355 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_FieldAssign}))->tag));
    (void)hoisted__Bool_3355;
    if (hoisted__Bool_3355) {
        FieldAssignData *_clone_payload_FieldAssign_10 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3322 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3322;
        NodeType *hoisted__NodeType_3323 = NodeType_FieldAssign(hoisted__FieldAssignData_3322);
        (void)hoisted__NodeType_3323;
        return hoisted__NodeType_3323;
    }
    U32 hoisted__U32_3356 = 1;
    (void)hoisted__U32_3356;
    Bool hoisted__Bool_3357 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Return}))->tag));
    (void)hoisted__Bool_3357;
    if (hoisted__Bool_3357) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
        return _r; }
    }
    U32 hoisted__U32_3358 = 1;
    (void)hoisted__U32_3358;
    Bool hoisted__Bool_3359 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_If}))->tag));
    (void)hoisted__Bool_3359;
    if (hoisted__Bool_3359) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
        return _r; }
    }
    U32 hoisted__U32_3360 = 1;
    (void)hoisted__U32_3360;
    Bool hoisted__Bool_3361 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_While}))->tag));
    (void)hoisted__Bool_3361;
    if (hoisted__Bool_3361) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
        return _r; }
    }
    U32 hoisted__U32_3362 = 1;
    (void)hoisted__U32_3362;
    Bool hoisted__Bool_3363 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_ForIn}))->tag));
    (void)hoisted__Bool_3363;
    if (hoisted__Bool_3363) {
        ForInData *_clone_payload_ForIn_14 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3324 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3324;
        NodeType *hoisted__NodeType_3325 = NodeType_ForIn(hoisted__ForInData_3324);
        (void)hoisted__NodeType_3325;
        return hoisted__NodeType_3325;
    }
    U32 hoisted__U32_3364 = 1;
    (void)hoisted__U32_3364;
    Bool hoisted__Bool_3365 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NamedArg}))->tag));
    (void)hoisted__Bool_3365;
    if (hoisted__Bool_3365) {
        Str *_clone_payload_NamedArg_15 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3326 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3326;
        NodeType *hoisted__NodeType_3327 = NodeType_NamedArg(hoisted__Str_3326);
        (void)hoisted__NodeType_3327;
        return hoisted__NodeType_3327;
    }
    U32 hoisted__U32_3366 = 1;
    (void)hoisted__U32_3366;
    Bool hoisted__Bool_3367 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Break}))->tag));
    (void)hoisted__Bool_3367;
    if (hoisted__Bool_3367) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
        return _r; }
    }
    U32 hoisted__U32_3368 = 1;
    (void)hoisted__U32_3368;
    Bool hoisted__Bool_3369 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Continue}))->tag));
    (void)hoisted__Bool_3369;
    if (hoisted__Bool_3369) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
        return _r; }
    }
    U32 hoisted__U32_3370 = 1;
    (void)hoisted__U32_3370;
    Bool hoisted__Bool_3371 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Switch}))->tag));
    (void)hoisted__Bool_3371;
    if (hoisted__Bool_3371) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
        return _r; }
    }
    U32 hoisted__U32_3372 = 1;
    (void)hoisted__U32_3372;
    Bool hoisted__Bool_3373 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Match}))->tag));
    (void)hoisted__Bool_3373;
    if (hoisted__Bool_3373) {
        MatchData *_clone_payload_Match_19 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3328 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3328;
        NodeType *hoisted__NodeType_3329 = NodeType_Match(hoisted__MatchData_3328);
        (void)hoisted__NodeType_3329;
        return hoisted__NodeType_3329;
    }
    U32 hoisted__U32_3374 = 1;
    (void)hoisted__U32_3374;
    Bool hoisted__Bool_3375 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Case}))->tag));
    (void)hoisted__Bool_3375;
    if (hoisted__Bool_3375) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
        return _r; }
    }
    U32 hoisted__U32_3376 = 1;
    (void)hoisted__U32_3376;
    Bool hoisted__Bool_3377 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_NoDefaultArg}))->tag));
    (void)hoisted__Bool_3377;
    if (hoisted__Bool_3377) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
        return _r; }
    }
    U32 hoisted__U32_3378 = 1;
    (void)hoisted__U32_3378;
    Bool hoisted__Bool_3379 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Throw}))->tag));
    (void)hoisted__Bool_3379;
    if (hoisted__Bool_3379) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
        return _r; }
    }
    U32 hoisted__U32_3380 = 1;
    (void)hoisted__U32_3380;
    Bool hoisted__Bool_3381 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Catch}))->tag));
    (void)hoisted__Bool_3381;
    if (hoisted__Bool_3381) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
        return _r; }
    }
    U32 hoisted__U32_3382 = 1;
    (void)hoisted__U32_3382;
    Bool hoisted__Bool_3383 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_RestPattern}))->tag));
    (void)hoisted__Bool_3383;
    if (hoisted__Bool_3383) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
        return _r; }
    }
    U32 hoisted__U32_3384 = 1;
    (void)hoisted__U32_3384;
    Bool hoisted__Bool_3385 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_CaptureBlock}))->tag));
    (void)hoisted__Bool_3385;
    if (hoisted__Bool_3385) {
        CaptureBlockData *_clone_payload_CaptureBlock_25 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_CaptureBlock_25;
        (void)_clone_payload_CaptureBlock_25;
        CaptureBlockData *hoisted__CaptureBlockData_3330 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
        (void)hoisted__CaptureBlockData_3330;
        NodeType *hoisted__NodeType_3331 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3330);
        (void)hoisted__NodeType_3331;
        return hoisted__NodeType_3331;
    }
    U32 hoisted__U32_3386 = 1;
    (void)hoisted__U32_3386;
    Bool hoisted__Bool_3387 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_Loc}))->tag));
    (void)hoisted__Bool_3387;
    if (hoisted__Bool_3387) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Loc;
        return _r; }
    }
    U32 hoisted__U32_3388 = 1;
    (void)hoisted__U32_3388;
    Bool hoisted__Bool_3389 = ((Bool)(((NodeType *)(self))->tag == ((NodeType *)(&(NodeType){.tag = NodeType_TAG_BodyValue}))->tag));
    (void)hoisted__Bool_3389;
    if (hoisted__Bool_3389) {
        CaptureBlockData *_clone_payload_BodyValue_27 = ((void *)((U8 *)(self) + offsetof(NodeType, data)));
        (void)_clone_payload_BodyValue_27;
        (void)_clone_payload_BodyValue_27;
        CaptureBlockData *hoisted__CaptureBlockData_3332 = CaptureBlockData_clone(_clone_payload_BodyValue_27);
        (void)hoisted__CaptureBlockData_3332;
        NodeType *hoisted__NodeType_3333 = NodeType_BodyValue(hoisted__CaptureBlockData_3332);
        (void)hoisted__NodeType_3333;
        return hoisted__NodeType_3333;
    }
    { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_ListPattern;
    return _r; }
    __builtin_unreachable();
}

USize NodeType_size(void) {
    U32 hoisted__U32_3390 = 136;
    (void)hoisted__U32_3390;
    return hoisted__U32_3390;
    __builtin_unreachable();
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3391 = ((Bool)((UPtr)(self) == 0));
    (void)hoisted__Bool_3391;
    if (hoisted__Bool_3391) {
        return;
    }
    Bool hoisted__Bool_3392 = 0;
    (void)hoisted__Bool_3392;
    NodeType_delete(&self->node_type, hoisted__Bool_3392);
    Vec__Expr_clear(&self->children);
    free(self->children.data);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Expr *hoisted__Expr_3433 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3433->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_new(); hoisted__Expr_3433->children = *_ca; free(_ca); }
    hoisted__Expr_3433->line = line;
    hoisted__Expr_3433->col = col;
    (void)hoisted__Expr_3433;
    return hoisted__Expr_3433;
    __builtin_unreachable();
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3702 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3702->node_type = *_ca; free(_ca); }
    { Vec__Expr *_ca = Vec__Expr_clone(&self->children); hoisted__Expr_3702->children = *_ca; free(_ca); }
    hoisted__Expr_3702->line = self->line;
    hoisted__Expr_3702->col = self->col;
    (void)hoisted__Expr_3702;
    return hoisted__Expr_3702;
    __builtin_unreachable();
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3703 = 0;
    (void)hoisted__U32_3703;
    U64 hoisted__U64_3704 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3703); });
    (void)hoisted__U64_3704;
    return hoisted__U64_3704;
    __builtin_unreachable();
}

USize Expr_size(void) {
    U32 hoisted__U32_3705 = 160;
    (void)hoisted__U32_3705;
    return hoisted__U32_3705;
    __builtin_unreachable();
}

Map__I64_Str * Map__I64_Str_new(void) {
    Map__I64_Str *hoisted__Map__I64_Str_3706 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_new(); hoisted__Map__I64_Str_3706->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_new(); hoisted__Map__I64_Str_3706->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3706;
    return hoisted__Map__I64_Str_3706;
    __builtin_unreachable();
}

void Map__I64_Str_delete(Map__I64_Str * self, Bool call_free) {
    Bool hoisted__Bool_3799 = 0;
    (void)hoisted__Bool_3799;
    Vec__I64_delete(&self->keys, hoisted__Bool_3799);
    Bool hoisted__Bool_3800 = 0;
    (void)hoisted__Bool_3800;
    Vec__Str_delete(&self->values, hoisted__Bool_3800);
    if (call_free) {
        free(self);
    }
}

Map__I64_Str * Map__I64_Str_clone(Map__I64_Str * self) {
    Map__I64_Str *hoisted__Map__I64_Str_3801 = malloc(sizeof(Map__I64_Str));
    { Vec__I64 *_ca = Vec__I64_clone(&self->keys); hoisted__Map__I64_Str_3801->keys = *_ca; free(_ca); }
    { Vec__Str *_ca = Vec__Str_clone(&self->values); hoisted__Map__I64_Str_3801->values = *_ca; free(_ca); }
    (void)hoisted__Map__I64_Str_3801;
    return hoisted__Map__I64_Str_3801;
    __builtin_unreachable();
}

U64 Map__I64_Str_hash(Map__I64_Str * self, HashFn hasher) {
    U32 hoisted__U32_3802 = 0;
    (void)hoisted__U32_3802;
    U64 hoisted__U64_3803 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map__I64_Str *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3802); });
    (void)hoisted__U64_3803;
    return hoisted__U64_3803;
    __builtin_unreachable();
}

USize Map__I64_Str_size(void) {
    U32 hoisted__U32_3804 = 32;
    (void)hoisted__U32_3804;
    return hoisted__U32_3804;
    __builtin_unreachable();
}

Vec__Bool * Vec__Bool_new(void) {
    U8 *hoisted__U8_3805 = malloc(sizeof(U8));
    *hoisted__U8_3805 = 0;
    (void)hoisted__U8_3805;
    U32 hoisted__U32_3806 = 0;
    (void)hoisted__U32_3806;
    I64 hoisted__I64_3807 = 0;
    (void)hoisted__I64_3807;
    Vec__Bool *hoisted__Vec__Bool_3808 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_3808->data = hoisted__U8_3805;
    hoisted__Vec__Bool_3808->count = hoisted__U32_3806;
    hoisted__Vec__Bool_3808->cap = hoisted__I64_3807;
    (void)hoisted__Vec__Bool_3808;
    return hoisted__Vec__Bool_3808;
    __builtin_unreachable();
}

void Vec__Bool_clear(Vec__Bool * self) {
    {
        U32 _re_U32_3820 = self->count;
        (void)_re_U32_3820;
        U32 _rc_U32_3820 = 0;
        (void)_rc_U32_3820;
        Bool hoisted__Bool_3831 = ((Bool)(_rc_U32_3820 <= _re_U32_3820));
        (void)hoisted__Bool_3831;
        if (hoisted__Bool_3831) {
            while (1) {
                Bool _wcond_Bool_3821 = ((Bool)(_rc_U32_3820 < _re_U32_3820));
                (void)_wcond_Bool_3821;
                if (_wcond_Bool_3821) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3820);
                (++_rc_U32_3820);
                U32 hoisted__U32_3822 = 1;
                (void)hoisted__U32_3822;
                U32 hoisted__U64_3823 = ((U64)(i * hoisted__U32_3822));
                (void)hoisted__U64_3823;
                Bool *hoisted__Bool_3824 = ((void *)((U8 *)(self->data) + (hoisted__U64_3823)));
                (void)hoisted__Bool_3824;
                (void)hoisted__Bool_3824;
                Bool hoisted__Bool_3825 = 0;
                (void)hoisted__Bool_3825;
                Bool_delete(hoisted__Bool_3824, hoisted__Bool_3825);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3826 = ((Bool)(_rc_U32_3820 > _re_U32_3820));
                (void)_wcond_Bool_3826;
                if (_wcond_Bool_3826) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_3820);
                (--_rc_U32_3820);
                U32 hoisted__U32_3827 = 1;
                (void)hoisted__U32_3827;
                U32 hoisted__U64_3828 = ((U64)(i * hoisted__U32_3827));
                (void)hoisted__U64_3828;
                Bool *hoisted__Bool_3829 = ((void *)((U8 *)(self->data) + (hoisted__U64_3828)));
                (void)hoisted__Bool_3829;
                (void)hoisted__Bool_3829;
                Bool hoisted__Bool_3830 = 0;
                (void)hoisted__Bool_3830;
                Bool_delete(hoisted__Bool_3829, hoisted__Bool_3830);
            }
        }
    }
    U32 hoisted__U32_3832 = 0;
    (void)hoisted__U32_3832;
    self->count = hoisted__U32_3832;
}

void Vec__Bool_delete(Vec__Bool * self, Bool call_free) {
    Vec__Bool_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Bool * Vec__Bool_clone(Vec__Bool * self) {
    U32 hoisted__U32_4071 = 0;
    (void)hoisted__U32_4071;
    Bool hoisted__Bool_4072 = ((Bool)(self->cap == hoisted__U32_4071));
    (void)hoisted__Bool_4072;
    if (hoisted__Bool_4072) {
        U8 *hoisted__U8_4047 = malloc(sizeof(U8));
        *hoisted__U8_4047 = 0;
        (void)hoisted__U8_4047;
        U32 hoisted__U32_4048 = 0;
        (void)hoisted__U32_4048;
        I64 hoisted__I64_4049 = 0;
        (void)hoisted__I64_4049;
        Vec__Bool *hoisted__Vec__Bool_4050 = malloc(sizeof(Vec__Bool));
        hoisted__Vec__Bool_4050->data = hoisted__U8_4047;
        hoisted__Vec__Bool_4050->count = hoisted__U32_4048;
        hoisted__Vec__Bool_4050->cap = hoisted__I64_4049;
        (void)hoisted__Vec__Bool_4050;
        return hoisted__Vec__Bool_4050;
    }
    U32 hoisted__U32_4073 = 1;
    (void)hoisted__U32_4073;
    U32 hoisted__U64_4074 = ((U64)(self->cap * hoisted__U32_4073));
    (void)hoisted__U64_4074;
    U8 *new_data = malloc(hoisted__U64_4074);
    {
        U32 _re_U32_4051 = self->count;
        (void)_re_U32_4051;
        U32 _rc_U32_4051 = 0;
        (void)_rc_U32_4051;
        Bool hoisted__Bool_4070 = ((Bool)(_rc_U32_4051 <= _re_U32_4051));
        (void)hoisted__Bool_4070;
        if (hoisted__Bool_4070) {
            while (1) {
                Bool _wcond_Bool_4052 = ((Bool)(_rc_U32_4051 < _re_U32_4051));
                (void)_wcond_Bool_4052;
                if (_wcond_Bool_4052) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4051);
                (++_rc_U32_4051);
                U32 hoisted__U32_4053 = 1;
                (void)hoisted__U32_4053;
                U32 hoisted__U64_4054 = ((U64)(i * hoisted__U32_4053));
                (void)hoisted__U64_4054;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4054)));
                Bool cloned = (DEREF(src));
                U32 hoisted__U32_4055 = 1;
                (void)hoisted__U32_4055;
                U32 hoisted__U64_4056 = ((U64)(i * hoisted__U32_4055));
                (void)hoisted__U64_4056;
                void *hoisted__v_4057 = ((void *)((U8 *)(new_data) + (hoisted__U64_4056)));
                (void)hoisted__v_4057;
                (void)hoisted__v_4057;
                U64 hoisted__U64_4058 = 1ULL;
                (void)hoisted__U64_4058;
                memcpy(hoisted__v_4057, &cloned, hoisted__U64_4058);
                I32 hoisted__I32_4059 = 0;
                (void)hoisted__I32_4059;
                U64 hoisted__U64_4060 = 1ULL;
                (void)hoisted__U64_4060;
                memset(&cloned, hoisted__I32_4059, hoisted__U64_4060);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4061 = ((Bool)(_rc_U32_4051 > _re_U32_4051));
                (void)_wcond_Bool_4061;
                if (_wcond_Bool_4061) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4051);
                (--_rc_U32_4051);
                U32 hoisted__U32_4062 = 1;
                (void)hoisted__U32_4062;
                U32 hoisted__U64_4063 = ((U64)(i * hoisted__U32_4062));
                (void)hoisted__U64_4063;
                Bool *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4063)));
                Bool cloned = (DEREF(src));
                U32 hoisted__U32_4064 = 1;
                (void)hoisted__U32_4064;
                U32 hoisted__U64_4065 = ((U64)(i * hoisted__U32_4064));
                (void)hoisted__U64_4065;
                void *hoisted__v_4066 = ((void *)((U8 *)(new_data) + (hoisted__U64_4065)));
                (void)hoisted__v_4066;
                (void)hoisted__v_4066;
                U64 hoisted__U64_4067 = 1ULL;
                (void)hoisted__U64_4067;
                memcpy(hoisted__v_4066, &cloned, hoisted__U64_4067);
                I32 hoisted__I32_4068 = 0;
                (void)hoisted__I32_4068;
                U64 hoisted__U64_4069 = 1ULL;
                (void)hoisted__U64_4069;
                memset(&cloned, hoisted__I32_4068, hoisted__U64_4069);
            }
        }
    }
    Vec__Bool *hoisted__Vec__Bool_4075 = malloc(sizeof(Vec__Bool));
    hoisted__Vec__Bool_4075->data = new_data;
    hoisted__Vec__Bool_4075->count = self->count;
    hoisted__Vec__Bool_4075->cap = self->cap;
    (void)hoisted__Vec__Bool_4075;
    return hoisted__Vec__Bool_4075;
    __builtin_unreachable();
}

USize Vec__Bool_size(void) {
    U32 hoisted__U32_4076 = 16;
    (void)hoisted__U32_4076;
    return hoisted__U32_4076;
    __builtin_unreachable();
}

Vec__I64 * Vec__I64_new(void) {
    U8 *hoisted__U8_4077 = malloc(sizeof(U8));
    *hoisted__U8_4077 = 0;
    (void)hoisted__U8_4077;
    U32 hoisted__U32_4078 = 0;
    (void)hoisted__U32_4078;
    I64 hoisted__I64_4079 = 0;
    (void)hoisted__I64_4079;
    Vec__I64 *hoisted__Vec__I64_4080 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_4080->data = hoisted__U8_4077;
    hoisted__Vec__I64_4080->count = hoisted__U32_4078;
    hoisted__Vec__I64_4080->cap = hoisted__I64_4079;
    (void)hoisted__Vec__I64_4080;
    return hoisted__Vec__I64_4080;
    __builtin_unreachable();
}

void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_4092 = self->count;
        (void)_re_U32_4092;
        U32 _rc_U32_4092 = 0;
        (void)_rc_U32_4092;
        Bool hoisted__Bool_4103 = ((Bool)(_rc_U32_4092 <= _re_U32_4092));
        (void)hoisted__Bool_4103;
        if (hoisted__Bool_4103) {
            while (1) {
                Bool _wcond_Bool_4093 = ((Bool)(_rc_U32_4092 < _re_U32_4092));
                (void)_wcond_Bool_4093;
                if (_wcond_Bool_4093) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4092);
                (++_rc_U32_4092);
                U32 hoisted__U32_4094 = 8;
                (void)hoisted__U32_4094;
                U32 hoisted__U64_4095 = ((U64)(i * hoisted__U32_4094));
                (void)hoisted__U64_4095;
                I64 *hoisted__I64_4096 = ((void *)((U8 *)(self->data) + (hoisted__U64_4095)));
                (void)hoisted__I64_4096;
                (void)hoisted__I64_4096;
                Bool hoisted__Bool_4097 = 0;
                (void)hoisted__Bool_4097;
                I64_delete(hoisted__I64_4096, hoisted__Bool_4097);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4098 = ((Bool)(_rc_U32_4092 > _re_U32_4092));
                (void)_wcond_Bool_4098;
                if (_wcond_Bool_4098) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4092);
                (--_rc_U32_4092);
                U32 hoisted__U32_4099 = 8;
                (void)hoisted__U32_4099;
                U32 hoisted__U64_4100 = ((U64)(i * hoisted__U32_4099));
                (void)hoisted__U64_4100;
                I64 *hoisted__I64_4101 = ((void *)((U8 *)(self->data) + (hoisted__U64_4100)));
                (void)hoisted__I64_4101;
                (void)hoisted__I64_4101;
                Bool hoisted__Bool_4102 = 0;
                (void)hoisted__Bool_4102;
                I64_delete(hoisted__I64_4101, hoisted__Bool_4102);
            }
        }
    }
    U32 hoisted__U32_4104 = 0;
    (void)hoisted__U32_4104;
    self->count = hoisted__U32_4104;
}

void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__I64 * Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_4343 = 0;
    (void)hoisted__U32_4343;
    Bool hoisted__Bool_4344 = ((Bool)(self->cap == hoisted__U32_4343));
    (void)hoisted__Bool_4344;
    if (hoisted__Bool_4344) {
        U8 *hoisted__U8_4319 = malloc(sizeof(U8));
        *hoisted__U8_4319 = 0;
        (void)hoisted__U8_4319;
        U32 hoisted__U32_4320 = 0;
        (void)hoisted__U32_4320;
        I64 hoisted__I64_4321 = 0;
        (void)hoisted__I64_4321;
        Vec__I64 *hoisted__Vec__I64_4322 = malloc(sizeof(Vec__I64));
        hoisted__Vec__I64_4322->data = hoisted__U8_4319;
        hoisted__Vec__I64_4322->count = hoisted__U32_4320;
        hoisted__Vec__I64_4322->cap = hoisted__I64_4321;
        (void)hoisted__Vec__I64_4322;
        return hoisted__Vec__I64_4322;
    }
    U32 hoisted__U32_4345 = 8;
    (void)hoisted__U32_4345;
    U32 hoisted__U64_4346 = ((U64)(self->cap * hoisted__U32_4345));
    (void)hoisted__U64_4346;
    U8 *new_data = malloc(hoisted__U64_4346);
    {
        U32 _re_U32_4323 = self->count;
        (void)_re_U32_4323;
        U32 _rc_U32_4323 = 0;
        (void)_rc_U32_4323;
        Bool hoisted__Bool_4342 = ((Bool)(_rc_U32_4323 <= _re_U32_4323));
        (void)hoisted__Bool_4342;
        if (hoisted__Bool_4342) {
            while (1) {
                Bool _wcond_Bool_4324 = ((Bool)(_rc_U32_4323 < _re_U32_4323));
                (void)_wcond_Bool_4324;
                if (_wcond_Bool_4324) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4323);
                (++_rc_U32_4323);
                U32 hoisted__U32_4325 = 8;
                (void)hoisted__U32_4325;
                U32 hoisted__U64_4326 = ((U64)(i * hoisted__U32_4325));
                (void)hoisted__U64_4326;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4326)));
                I64 cloned = (DEREF(src));
                U32 hoisted__U32_4327 = 8;
                (void)hoisted__U32_4327;
                U32 hoisted__U64_4328 = ((U64)(i * hoisted__U32_4327));
                (void)hoisted__U64_4328;
                void *hoisted__v_4329 = ((void *)((U8 *)(new_data) + (hoisted__U64_4328)));
                (void)hoisted__v_4329;
                (void)hoisted__v_4329;
                U64 hoisted__U64_4330 = 8ULL;
                (void)hoisted__U64_4330;
                memcpy(hoisted__v_4329, &cloned, hoisted__U64_4330);
                I32 hoisted__I32_4331 = 0;
                (void)hoisted__I32_4331;
                U64 hoisted__U64_4332 = 8ULL;
                (void)hoisted__U64_4332;
                memset(&cloned, hoisted__I32_4331, hoisted__U64_4332);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4333 = ((Bool)(_rc_U32_4323 > _re_U32_4323));
                (void)_wcond_Bool_4333;
                if (_wcond_Bool_4333) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4323);
                (--_rc_U32_4323);
                U32 hoisted__U32_4334 = 8;
                (void)hoisted__U32_4334;
                U32 hoisted__U64_4335 = ((U64)(i * hoisted__U32_4334));
                (void)hoisted__U64_4335;
                I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4335)));
                I64 cloned = (DEREF(src));
                U32 hoisted__U32_4336 = 8;
                (void)hoisted__U32_4336;
                U32 hoisted__U64_4337 = ((U64)(i * hoisted__U32_4336));
                (void)hoisted__U64_4337;
                void *hoisted__v_4338 = ((void *)((U8 *)(new_data) + (hoisted__U64_4337)));
                (void)hoisted__v_4338;
                (void)hoisted__v_4338;
                U64 hoisted__U64_4339 = 8ULL;
                (void)hoisted__U64_4339;
                memcpy(hoisted__v_4338, &cloned, hoisted__U64_4339);
                I32 hoisted__I32_4340 = 0;
                (void)hoisted__I32_4340;
                U64 hoisted__U64_4341 = 8ULL;
                (void)hoisted__U64_4341;
                memset(&cloned, hoisted__I32_4340, hoisted__U64_4341);
            }
        }
    }
    Vec__I64 *hoisted__Vec__I64_4347 = malloc(sizeof(Vec__I64));
    hoisted__Vec__I64_4347->data = new_data;
    hoisted__Vec__I64_4347->count = self->count;
    hoisted__Vec__I64_4347->cap = self->cap;
    (void)hoisted__Vec__I64_4347;
    return hoisted__Vec__I64_4347;
    __builtin_unreachable();
}

USize Vec__I64_size(void) {
    U32 hoisted__U32_4348 = 16;
    (void)hoisted__U32_4348;
    return hoisted__U32_4348;
    __builtin_unreachable();
}

Vec__Declaration * Vec__Declaration_new(void) {
    U8 *hoisted__U8_4621 = malloc(sizeof(U8));
    *hoisted__U8_4621 = 0;
    (void)hoisted__U8_4621;
    U32 hoisted__U32_4622 = 0;
    (void)hoisted__U32_4622;
    I64 hoisted__I64_4623 = 0;
    (void)hoisted__I64_4623;
    Vec__Declaration *hoisted__Vec__Declaration_4624 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4624->data = hoisted__U8_4621;
    hoisted__Vec__Declaration_4624->count = hoisted__U32_4622;
    hoisted__Vec__Declaration_4624->cap = hoisted__I64_4623;
    (void)hoisted__Vec__Declaration_4624;
    return hoisted__Vec__Declaration_4624;
    __builtin_unreachable();
}

void Vec__Declaration_clear(Vec__Declaration * self) {
    {
        U32 _re_U32_4636 = self->count;
        (void)_re_U32_4636;
        U32 _rc_U32_4636 = 0;
        (void)_rc_U32_4636;
        Bool hoisted__Bool_4647 = ((Bool)(_rc_U32_4636 <= _re_U32_4636));
        (void)hoisted__Bool_4647;
        if (hoisted__Bool_4647) {
            while (1) {
                Bool _wcond_Bool_4637 = ((Bool)(_rc_U32_4636 < _re_U32_4636));
                (void)_wcond_Bool_4637;
                if (_wcond_Bool_4637) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4636);
                (++_rc_U32_4636);
                U32 hoisted__U32_4638 = 112;
                (void)hoisted__U32_4638;
                U32 hoisted__U64_4639 = ((U64)(i * hoisted__U32_4638));
                (void)hoisted__U64_4639;
                Declaration *hoisted__Declaration_4640 = ((void *)((U8 *)(self->data) + (hoisted__U64_4639)));
                (void)hoisted__Declaration_4640;
                (void)hoisted__Declaration_4640;
                Bool hoisted__Bool_4641 = 0;
                (void)hoisted__Bool_4641;
                Declaration_delete(hoisted__Declaration_4640, hoisted__Bool_4641);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4642 = ((Bool)(_rc_U32_4636 > _re_U32_4636));
                (void)_wcond_Bool_4642;
                if (_wcond_Bool_4642) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4636);
                (--_rc_U32_4636);
                U32 hoisted__U32_4643 = 112;
                (void)hoisted__U32_4643;
                U32 hoisted__U64_4644 = ((U64)(i * hoisted__U32_4643));
                (void)hoisted__U64_4644;
                Declaration *hoisted__Declaration_4645 = ((void *)((U8 *)(self->data) + (hoisted__U64_4644)));
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
    U32 hoisted__U32_4887 = 0;
    (void)hoisted__U32_4887;
    Bool hoisted__Bool_4888 = ((Bool)(self->cap == hoisted__U32_4887));
    (void)hoisted__Bool_4888;
    if (hoisted__Bool_4888) {
        U8 *hoisted__U8_4863 = malloc(sizeof(U8));
        *hoisted__U8_4863 = 0;
        (void)hoisted__U8_4863;
        U32 hoisted__U32_4864 = 0;
        (void)hoisted__U32_4864;
        I64 hoisted__I64_4865 = 0;
        (void)hoisted__I64_4865;
        Vec__Declaration *hoisted__Vec__Declaration_4866 = malloc(sizeof(Vec__Declaration));
        hoisted__Vec__Declaration_4866->data = hoisted__U8_4863;
        hoisted__Vec__Declaration_4866->count = hoisted__U32_4864;
        hoisted__Vec__Declaration_4866->cap = hoisted__I64_4865;
        (void)hoisted__Vec__Declaration_4866;
        return hoisted__Vec__Declaration_4866;
    }
    U32 hoisted__U32_4889 = 112;
    (void)hoisted__U32_4889;
    U32 hoisted__U64_4890 = ((U64)(self->cap * hoisted__U32_4889));
    (void)hoisted__U64_4890;
    U8 *new_data = malloc(hoisted__U64_4890);
    {
        U32 _re_U32_4867 = self->count;
        (void)_re_U32_4867;
        U32 _rc_U32_4867 = 0;
        (void)_rc_U32_4867;
        Bool hoisted__Bool_4886 = ((Bool)(_rc_U32_4867 <= _re_U32_4867));
        (void)hoisted__Bool_4886;
        if (hoisted__Bool_4886) {
            while (1) {
                Bool _wcond_Bool_4868 = ((Bool)(_rc_U32_4867 < _re_U32_4867));
                (void)_wcond_Bool_4868;
                if (_wcond_Bool_4868) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4867);
                (++_rc_U32_4867);
                U32 hoisted__U32_4869 = 112;
                (void)hoisted__U32_4869;
                U32 hoisted__U64_4870 = ((U64)(i * hoisted__U32_4869));
                (void)hoisted__U64_4870;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4870)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4871 = 112;
                (void)hoisted__U32_4871;
                U32 hoisted__U64_4872 = ((U64)(i * hoisted__U32_4871));
                (void)hoisted__U64_4872;
                void *hoisted__v_4873 = ((void *)((U8 *)(new_data) + (hoisted__U64_4872)));
                (void)hoisted__v_4873;
                (void)hoisted__v_4873;
                U64 hoisted__U64_4874 = 112ULL;
                (void)hoisted__U64_4874;
                memcpy(hoisted__v_4873, cloned, hoisted__U64_4874);
                I32 hoisted__I32_4875 = 0;
                (void)hoisted__I32_4875;
                U64 hoisted__U64_4876 = 112ULL;
                (void)hoisted__U64_4876;
                memset(cloned, hoisted__I32_4875, hoisted__U64_4876);
                Declaration_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4877 = ((Bool)(_rc_U32_4867 > _re_U32_4867));
                (void)_wcond_Bool_4877;
                if (_wcond_Bool_4877) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4867);
                (--_rc_U32_4867);
                U32 hoisted__U32_4878 = 112;
                (void)hoisted__U32_4878;
                U32 hoisted__U64_4879 = ((U64)(i * hoisted__U32_4878));
                (void)hoisted__U64_4879;
                Declaration *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4879)));
                Declaration *cloned = Declaration_clone(src);
                U32 hoisted__U32_4880 = 112;
                (void)hoisted__U32_4880;
                U32 hoisted__U64_4881 = ((U64)(i * hoisted__U32_4880));
                (void)hoisted__U64_4881;
                void *hoisted__v_4882 = ((void *)((U8 *)(new_data) + (hoisted__U64_4881)));
                (void)hoisted__v_4882;
                (void)hoisted__v_4882;
                U64 hoisted__U64_4883 = 112ULL;
                (void)hoisted__U64_4883;
                memcpy(hoisted__v_4882, cloned, hoisted__U64_4883);
                I32 hoisted__I32_4884 = 0;
                (void)hoisted__I32_4884;
                U64 hoisted__U64_4885 = 112ULL;
                (void)hoisted__U64_4885;
                memset(cloned, hoisted__I32_4884, hoisted__U64_4885);
                Declaration_delete(cloned, 1);
            }
        }
    }
    Vec__Declaration *hoisted__Vec__Declaration_4891 = malloc(sizeof(Vec__Declaration));
    hoisted__Vec__Declaration_4891->data = new_data;
    hoisted__Vec__Declaration_4891->count = self->count;
    hoisted__Vec__Declaration_4891->cap = self->cap;
    (void)hoisted__Vec__Declaration_4891;
    return hoisted__Vec__Declaration_4891;
    __builtin_unreachable();
}

USize Vec__Declaration_size(void) {
    U32 hoisted__U32_4892 = 16;
    (void)hoisted__U32_4892;
    return hoisted__U32_4892;
    __builtin_unreachable();
}

Vec__Expr * Vec__Expr_new(void) {
    U8 *hoisted__U8_4893 = malloc(sizeof(U8));
    *hoisted__U8_4893 = 0;
    (void)hoisted__U8_4893;
    U32 hoisted__U32_4894 = 0;
    (void)hoisted__U32_4894;
    I64 hoisted__I64_4895 = 0;
    (void)hoisted__I64_4895;
    Vec__Expr *hoisted__Vec__Expr_4896 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_4896->data = hoisted__U8_4893;
    hoisted__Vec__Expr_4896->count = hoisted__U32_4894;
    hoisted__Vec__Expr_4896->cap = hoisted__I64_4895;
    (void)hoisted__Vec__Expr_4896;
    return hoisted__Vec__Expr_4896;
    __builtin_unreachable();
}

void Vec__Expr_clear(Vec__Expr * self) {
    {
        U32 _re_U32_4908 = self->count;
        (void)_re_U32_4908;
        U32 _rc_U32_4908 = 0;
        (void)_rc_U32_4908;
        Bool hoisted__Bool_4919 = ((Bool)(_rc_U32_4908 <= _re_U32_4908));
        (void)hoisted__Bool_4919;
        if (hoisted__Bool_4919) {
            while (1) {
                Bool _wcond_Bool_4909 = ((Bool)(_rc_U32_4908 < _re_U32_4908));
                (void)_wcond_Bool_4909;
                if (_wcond_Bool_4909) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4908);
                (++_rc_U32_4908);
                U32 hoisted__U32_4910 = 160;
                (void)hoisted__U32_4910;
                U32 hoisted__U64_4911 = ((U64)(i * hoisted__U32_4910));
                (void)hoisted__U64_4911;
                Expr *hoisted__Expr_4912 = ((void *)((U8 *)(self->data) + (hoisted__U64_4911)));
                (void)hoisted__Expr_4912;
                (void)hoisted__Expr_4912;
                Bool hoisted__Bool_4913 = 0;
                (void)hoisted__Bool_4913;
                Expr_delete(hoisted__Expr_4912, hoisted__Bool_4913);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_4914 = ((Bool)(_rc_U32_4908 > _re_U32_4908));
                (void)_wcond_Bool_4914;
                if (_wcond_Bool_4914) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_4908);
                (--_rc_U32_4908);
                U32 hoisted__U32_4915 = 160;
                (void)hoisted__U32_4915;
                U32 hoisted__U64_4916 = ((U64)(i * hoisted__U32_4915));
                (void)hoisted__U64_4916;
                Expr *hoisted__Expr_4917 = ((void *)((U8 *)(self->data) + (hoisted__U64_4916)));
                (void)hoisted__Expr_4917;
                (void)hoisted__Expr_4917;
                Bool hoisted__Bool_4918 = 0;
                (void)hoisted__Bool_4918;
                Expr_delete(hoisted__Expr_4917, hoisted__Bool_4918);
            }
        }
    }
    U32 hoisted__U32_4920 = 0;
    (void)hoisted__U32_4920;
    self->count = hoisted__U32_4920;
}

void Vec__Expr_delete(Vec__Expr * self, Bool call_free) {
    Vec__Expr_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec__Expr * Vec__Expr_clone(Vec__Expr * self) {
    U32 hoisted__U32_5159 = 0;
    (void)hoisted__U32_5159;
    Bool hoisted__Bool_5160 = ((Bool)(self->cap == hoisted__U32_5159));
    (void)hoisted__Bool_5160;
    if (hoisted__Bool_5160) {
        U8 *hoisted__U8_5135 = malloc(sizeof(U8));
        *hoisted__U8_5135 = 0;
        (void)hoisted__U8_5135;
        U32 hoisted__U32_5136 = 0;
        (void)hoisted__U32_5136;
        I64 hoisted__I64_5137 = 0;
        (void)hoisted__I64_5137;
        Vec__Expr *hoisted__Vec__Expr_5138 = malloc(sizeof(Vec__Expr));
        hoisted__Vec__Expr_5138->data = hoisted__U8_5135;
        hoisted__Vec__Expr_5138->count = hoisted__U32_5136;
        hoisted__Vec__Expr_5138->cap = hoisted__I64_5137;
        (void)hoisted__Vec__Expr_5138;
        return hoisted__Vec__Expr_5138;
    }
    U32 hoisted__U32_5161 = 160;
    (void)hoisted__U32_5161;
    U32 hoisted__U64_5162 = ((U64)(self->cap * hoisted__U32_5161));
    (void)hoisted__U64_5162;
    U8 *new_data = malloc(hoisted__U64_5162);
    {
        U32 _re_U32_5139 = self->count;
        (void)_re_U32_5139;
        U32 _rc_U32_5139 = 0;
        (void)_rc_U32_5139;
        Bool hoisted__Bool_5158 = ((Bool)(_rc_U32_5139 <= _re_U32_5139));
        (void)hoisted__Bool_5158;
        if (hoisted__Bool_5158) {
            while (1) {
                Bool _wcond_Bool_5140 = ((Bool)(_rc_U32_5139 < _re_U32_5139));
                (void)_wcond_Bool_5140;
                if (_wcond_Bool_5140) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5139);
                (++_rc_U32_5139);
                U32 hoisted__U32_5141 = 160;
                (void)hoisted__U32_5141;
                U32 hoisted__U64_5142 = ((U64)(i * hoisted__U32_5141));
                (void)hoisted__U64_5142;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5142)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5143 = 160;
                (void)hoisted__U32_5143;
                U32 hoisted__U64_5144 = ((U64)(i * hoisted__U32_5143));
                (void)hoisted__U64_5144;
                void *hoisted__v_5145 = ((void *)((U8 *)(new_data) + (hoisted__U64_5144)));
                (void)hoisted__v_5145;
                (void)hoisted__v_5145;
                U64 hoisted__U64_5146 = 160ULL;
                (void)hoisted__U64_5146;
                memcpy(hoisted__v_5145, cloned, hoisted__U64_5146);
                I32 hoisted__I32_5147 = 0;
                (void)hoisted__I32_5147;
                U64 hoisted__U64_5148 = 160ULL;
                (void)hoisted__U64_5148;
                memset(cloned, hoisted__I32_5147, hoisted__U64_5148);
                Expr_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5149 = ((Bool)(_rc_U32_5139 > _re_U32_5139));
                (void)_wcond_Bool_5149;
                if (_wcond_Bool_5149) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_5139);
                (--_rc_U32_5139);
                U32 hoisted__U32_5150 = 160;
                (void)hoisted__U32_5150;
                U32 hoisted__U64_5151 = ((U64)(i * hoisted__U32_5150));
                (void)hoisted__U64_5151;
                Expr *src = ((void *)((U8 *)(self->data) + (hoisted__U64_5151)));
                Expr *cloned = Expr_clone(src);
                U32 hoisted__U32_5152 = 160;
                (void)hoisted__U32_5152;
                U32 hoisted__U64_5153 = ((U64)(i * hoisted__U32_5152));
                (void)hoisted__U64_5153;
                void *hoisted__v_5154 = ((void *)((U8 *)(new_data) + (hoisted__U64_5153)));
                (void)hoisted__v_5154;
                (void)hoisted__v_5154;
                U64 hoisted__U64_5155 = 160ULL;
                (void)hoisted__U64_5155;
                memcpy(hoisted__v_5154, cloned, hoisted__U64_5155);
                I32 hoisted__I32_5156 = 0;
                (void)hoisted__I32_5156;
                U64 hoisted__U64_5157 = 160ULL;
                (void)hoisted__U64_5157;
                memset(cloned, hoisted__I32_5156, hoisted__U64_5157);
                Expr_delete(cloned, 1);
            }
        }
    }
    Vec__Expr *hoisted__Vec__Expr_5163 = malloc(sizeof(Vec__Expr));
    hoisted__Vec__Expr_5163->data = new_data;
    hoisted__Vec__Expr_5163->count = self->count;
    hoisted__Vec__Expr_5163->cap = self->cap;
    (void)hoisted__Vec__Expr_5163;
    return hoisted__Vec__Expr_5163;
    __builtin_unreachable();
}

USize Vec__Expr_size(void) {
    U32 hoisted__U32_5164 = 16;
    (void)hoisted__U32_5164;
    return hoisted__U32_5164;
    __builtin_unreachable();
}

void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6022 = 3;
    (void)hoisted__U32_6022;
    Array__Str *_va_Array_145 = Array__Str_new(hoisted__U32_6022);
    (void)_va_Array_145;
    I64 _va_Array_145_ek = 0;
    (void)_va_Array_145_ek;
    U32 hoisted__U32_6023 = 0;
    (void)hoisted__U32_6023;
    Str *hoisted__Str_6024 = Str_clone(loc);
    (void)hoisted__Str_6024;
    Array__Str_set(_va_Array_145, hoisted__U32_6023, hoisted__Str_6024, &_va_Array_145_ek);
    U32 hoisted__U32_6025 = 1;
    (void)hoisted__U32_6025;
    (void)_til_str_lit_151;
    (void)_til_str_lit_151;
    Array__Str_set(_va_Array_145, hoisted__U32_6025, &_til_str_lit_151, &_va_Array_145_ek);
    Array__Str *hoisted__Array__Str_6027 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_6027;
    U32 hoisted__U32_6028 = 2;
    (void)hoisted__U32_6028;
    Str *hoisted__Str_6029 = format(hoisted__Array__Str_6027);
    (void)hoisted__Str_6029;
    Array__Str_set(_va_Array_145, hoisted__U32_6028, hoisted__Str_6029, &_va_Array_145_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_145);
    I64 hoisted__I64_6030 = 1;
    (void)hoisted__I64_6030;
    exit(hoisted__I64_6030);
}

void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_6037 = 1;
    (void)hoisted__U32_6037;
    Array__Str *_va_Array_147 = Array__Str_new(hoisted__U32_6037);
    (void)_va_Array_147;
    I64 _va_Array_147_ek = 0;
    (void)_va_Array_147_ek;
    U32 hoisted__U32_6038 = 0;
    (void)hoisted__U32_6038;
    (void)_til_str_lit_152;
    (void)_til_str_lit_152;
    Array__Str_set(_va_Array_147, hoisted__U32_6038, &_til_str_lit_152, &_va_Array_147_ek);
    panic(_va_Array_147, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6043 = ((Bool)(!(cond)));
    (void)hoisted__Bool_6043;
    if (hoisted__Bool_6043) {
        U32 hoisted__U32_6040 = 1;
        (void)hoisted__U32_6040;
        Array__Str *_va_Array_148 = Array__Str_new(hoisted__U32_6040);
        (void)_va_Array_148;
        I64 _va_Array_148_ek = 0;
        (void)_va_Array_148_ek;
        U32 hoisted__U32_6041 = 0;
        (void)hoisted__U32_6041;
        (void)_til_str_lit_153;
        (void)_til_str_lit_153;
        Array__Str_set(_va_Array_148, hoisted__U32_6041, &_til_str_lit_153, &_va_Array_148_ek);
        panic(_va_Array_148, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6051 = parts;
        (void)_fc_Array__Str_6051;
        (void)_fc_Array__Str_6051;
        U32 _fi_USize_6051 = 0;
        (void)_fi_USize_6051;
        while (1) {
            USize hoisted__U32_6053 = (_fc_Array__Str_6051->cap);
            (void)hoisted__U32_6053;
            Bool _wcond_Bool_6052 = ((Bool)(_fi_USize_6051 < hoisted__U32_6053));
            (void)_wcond_Bool_6052;
            if (_wcond_Bool_6052) {
            } else {
                break;
            }
            Str *s = (((void *)((U8 *)(_fc_Array__Str_6051->data) + (((U64)(_fi_USize_6051 * 16))))));
            U32 hoisted__U32_6054 = 1;
            (void)hoisted__U32_6054;
            U32 hoisted__U32_6055 = ((U32)(_fi_USize_6051 + hoisted__U32_6054));
            (void)hoisted__U32_6055;
            _fi_USize_6051 = hoisted__U32_6055;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_6068 = (Range){.start = val->start, .end = val->end};
    (void)hoisted__Range_6068;
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_6068;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_6069 = 0;
    (void)hoisted__U32_6069;
    U64 hoisted__U64_6070 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6069); });
    (void)hoisted__U64_6070;
    return hoisted__U64_6070;
    __builtin_unreachable();
}

USize Range_size(void) {
    U32 hoisted__U32_6094 = 16;
    (void)hoisted__U32_6094;
    return hoisted__U32_6094;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6108 = 3;
    (void)hoisted__I64_6108;
    (void)_til_str_lit_156;
    (void)_til_str_lit_156;
    assert_eq__I64(result, hoisted__I64_6108, &_til_str_lit_156);
    Str_delete(&_til_str_lit_156, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6116 = 15;
    (void)hoisted__I64_6116;
    (void)_til_str_lit_157;
    (void)_til_str_lit_157;
    assert_eq__I64(result, hoisted__I64_6116, &_til_str_lit_157);
    Str_delete(&_til_str_lit_157, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6124 = 26;
    (void)hoisted__I64_6124;
    (void)_til_str_lit_158;
    (void)_til_str_lit_158;
    assert_eq__I64(result, hoisted__I64_6124, &_til_str_lit_158);
    Str_delete(&_til_str_lit_158, (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    (void)_til_str_lit_160;
    (void)_til_str_lit_160;
    assert_eq__Str(&result, &_til_str_lit_159, &_til_str_lit_160);
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&_til_str_lit_160, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_159;
    (void)_til_str_lit_159;
    (void)_til_str_lit_161;
    (void)_til_str_lit_161;
    assert_eq__Str(&r, &_til_str_lit_159, &_til_str_lit_161);
    Str_delete(&_til_str_lit_159, (Bool){0});
    Str_delete(&_til_str_lit_161, (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_162;
    (void)_til_str_lit_162;
    (void)_til_str_lit_163;
    (void)_til_str_lit_163;
    assert_eq__Str(&r2, &_til_str_lit_162, &_til_str_lit_163);
    Str_delete(&_til_str_lit_162, (Bool){0});
    Str_delete(&_til_str_lit_163, (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_164;
    (void)_til_str_lit_164;
    (void)_til_str_lit_165;
    (void)_til_str_lit_165;
    assert_eq__Str(&d, &_til_str_lit_164, &_til_str_lit_165);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lit_164, (Bool){0});
    Str_delete(&_til_str_lit_165, (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_166;
    (void)_til_str_lit_166;
    (void)_til_str_lit_167;
    (void)_til_str_lit_167;
    assert_eq__Str(&d2, &_til_str_lit_166, &_til_str_lit_167);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lit_166, (Bool){0});
    Str_delete(&_til_str_lit_167, (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_6193 = 106;
    (void)hoisted__I64_6193;
    (void)_til_str_lit_168;
    (void)_til_str_lit_168;
    assert_eq__I64(d3, hoisted__I64_6193, &_til_str_lit_168);
    Str_delete(&_til_str_lit_168, (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    (void)_til_str_lit_171;
    (void)_til_str_lit_171;
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lit_171);
    Str_delete(&_til_str_lit_171, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    (void)_til_str_lit_172;
    (void)_til_str_lit_172;
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lit_172);
    Str_delete(&_til_str_lit_172, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_6686 = 8;
    (void)hoisted__I64_6686;
    (void)_til_str_lit_173;
    (void)_til_str_lit_173;
    assert_eq__I64(result, hoisted__I64_6686, &_til_str_lit_173);
    Str_delete(&_til_str_lit_173, (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6690 = 1;
    (void)hoisted__Bool_6690;
    (void)_til_str_lit_174;
    (void)_til_str_lit_174;
    assert(hoisted__Bool_6690, &_til_str_lit_174);
    Str_delete(&_til_str_lit_174, (Bool){0});
    Bool hoisted__Bool_6694 = 1;
    (void)hoisted__Bool_6694;
    (void)_til_str_lit_175;
    (void)_til_str_lit_175;
    assert(hoisted__Bool_6694, &_til_str_lit_175);
    Str_delete(&_til_str_lit_175, (Bool){0});
}

void test_fold_f32(void) {
    (void)_til_str_lit_176;
    (void)_til_str_lit_176;
    (void)_til_str_lit_176;
    (void)_til_str_lit_176;
    (void)_til_str_lit_177;
    (void)_til_str_lit_177;
    assert_eq__Str(&_til_str_lit_176, &_til_str_lit_176, &_til_str_lit_177);
    Str_delete(&_til_str_lit_176, (Bool){0});
    Str_delete(&_til_str_lit_176, (Bool){0});
    Str_delete(&_til_str_lit_177, (Bool){0});
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    (void)_til_str_lit_178;
    (void)_til_str_lit_179;
    (void)_til_str_lit_179;
    assert_eq__Str(&_til_str_lit_178, &_til_str_lit_178, &_til_str_lit_179);
    Str_delete(&_til_str_lit_178, (Bool){0});
    Str_delete(&_til_str_lit_178, (Bool){0});
    Str_delete(&_til_str_lit_179, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_6712 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_6712;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_6712;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_6713 = 0;
    (void)hoisted__U32_6713;
    U64 hoisted__U64_6714 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6713); });
    (void)hoisted__U64_6714;
    return hoisted__U64_6714;
    __builtin_unreachable();
}

USize CfVec2_size(void) {
    U32 hoisted__U32_6738 = 16;
    (void)hoisted__U32_6738;
    return hoisted__U32_6738;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6739 = 42;
    (void)hoisted__I64_6739;
    (void)_til_str_lit_182;
    (void)_til_str_lit_182;
    assert_eq__I64(v.x, hoisted__I64_6739, &_til_str_lit_182);
    Str_delete(&_til_str_lit_182, (Bool){0});
    I64 hoisted__I64_6741 = 99;
    (void)hoisted__I64_6741;
    (void)_til_str_lit_183;
    (void)_til_str_lit_183;
    assert_eq__I64(v.y, hoisted__I64_6741, &_til_str_lit_183);
    Str_delete(&_til_str_lit_183, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6745 = 10;
    (void)hoisted__I64_6745;
    (void)_til_str_lit_184;
    (void)_til_str_lit_184;
    assert_eq__I64(p.x, hoisted__I64_6745, &_til_str_lit_184);
    Str_delete(&_til_str_lit_184, (Bool){0});
    I64 hoisted__I64_6747 = 20;
    (void)hoisted__I64_6747;
    (void)_til_str_lit_185;
    (void)_til_str_lit_185;
    assert_eq__I64(p.y, hoisted__I64_6747, &_til_str_lit_185);
    Str_delete(&_til_str_lit_185, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_6754 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_6754;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_6754;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_6755 = 0;
    (void)hoisted__U32_6755;
    U64 hoisted__U64_6756 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6755); });
    (void)hoisted__U64_6756;
    return hoisted__U64_6756;
    __builtin_unreachable();
}

USize CfRect_size(void) {
    U32 hoisted__U32_6780 = 32;
    (void)hoisted__U32_6780;
    return hoisted__U32_6780;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6781 = 5;
    (void)hoisted__I64_6781;
    (void)_til_str_lit_189;
    (void)_til_str_lit_189;
    assert_eq__I64(r.top_left.x, hoisted__I64_6781, &_til_str_lit_189);
    Str_delete(&_til_str_lit_189, (Bool){0});
    I64 hoisted__I64_6783 = 10;
    (void)hoisted__I64_6783;
    (void)_til_str_lit_190;
    (void)_til_str_lit_190;
    assert_eq__I64(r.top_left.y, hoisted__I64_6783, &_til_str_lit_190);
    Str_delete(&_til_str_lit_190, (Bool){0});
    I64 hoisted__I64_6785 = 100;
    (void)hoisted__I64_6785;
    (void)_til_str_lit_191;
    (void)_til_str_lit_191;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6785, &_til_str_lit_191);
    Str_delete(&_til_str_lit_191, (Bool){0});
    I64 hoisted__I64_6787 = 200;
    (void)hoisted__I64_6787;
    (void)_til_str_lit_192;
    (void)_til_str_lit_192;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6787, &_til_str_lit_192);
    Str_delete(&_til_str_lit_192, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_6790 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_6790;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_6790;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_6791 = 0;
    (void)hoisted__U32_6791;
    U64 hoisted__U64_6792 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6791); });
    (void)hoisted__U64_6792;
    return hoisted__U64_6792;
    __builtin_unreachable();
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_6825 = 12;
    (void)hoisted__U32_6825;
    return hoisted__U32_6825;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6829 = F32_to_str(v.x);
    (void)hoisted__Str_6829;
    (void)_til_str_lit_194;
    (void)_til_str_lit_194;
    (void)_til_str_lit_195;
    (void)_til_str_lit_195;
    assert_eq__Str(hoisted__Str_6829, &_til_str_lit_194, &_til_str_lit_195);
    Str_delete(hoisted__Str_6829, 1);
    Str_delete(&_til_str_lit_194, (Bool){0});
    Str_delete(&_til_str_lit_195, (Bool){0});
    Str *hoisted__Str_6832 = F32_to_str(v.y);
    (void)hoisted__Str_6832;
    (void)_til_str_lit_196;
    (void)_til_str_lit_196;
    (void)_til_str_lit_197;
    (void)_til_str_lit_197;
    assert_eq__Str(hoisted__Str_6832, &_til_str_lit_196, &_til_str_lit_197);
    Str_delete(hoisted__Str_6832, 1);
    Str_delete(&_til_str_lit_196, (Bool){0});
    Str_delete(&_til_str_lit_197, (Bool){0});
    Str *hoisted__Str_6835 = F32_to_str(v.z);
    (void)hoisted__Str_6835;
    (void)_til_str_lit_198;
    (void)_til_str_lit_198;
    (void)_til_str_lit_199;
    (void)_til_str_lit_199;
    assert_eq__Str(hoisted__Str_6835, &_til_str_lit_198, &_til_str_lit_199);
    Str_delete(hoisted__Str_6835, 1);
    Str_delete(&_til_str_lit_198, (Bool){0});
    Str_delete(&_til_str_lit_199, (Bool){0});
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
    U32 hoisted__U32_6844 = 1;
    (void)hoisted__U32_6844;
    Bool hoisted__Bool_6845 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
    (void)hoisted__Bool_6845;
    if (hoisted__Bool_6845) {
        U32 hoisted__U32_6838 = 1;
        (void)hoisted__U32_6838;
        Bool hoisted__Bool_6839 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Red}))->tag));
        (void)hoisted__Bool_6839;
        return hoisted__Bool_6839;
    }
    U32 hoisted__U32_6846 = 1;
    (void)hoisted__U32_6846;
    Bool hoisted__Bool_6847 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
    (void)hoisted__Bool_6847;
    if (hoisted__Bool_6847) {
        U32 hoisted__U32_6840 = 1;
        (void)hoisted__U32_6840;
        Bool hoisted__Bool_6841 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Green}))->tag));
        (void)hoisted__Bool_6841;
        return hoisted__Bool_6841;
    }
    U32 hoisted__U32_6848 = 1;
    (void)hoisted__U32_6848;
    Bool hoisted__Bool_6849 = ((Bool)(((Color *)(self))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
    (void)hoisted__Bool_6849;
    if (hoisted__Bool_6849) {
        U32 hoisted__U32_6842 = 1;
        (void)hoisted__U32_6842;
        Bool hoisted__Bool_6843 = ((Bool)(((Color *)(other))->tag == ((Color *)(&(Color){.tag = Color_TAG_Blue}))->tag));
        (void)hoisted__Bool_6843;
        return hoisted__Bool_6843;
    }
    Bool hoisted__Bool_6850 = 0;
    (void)hoisted__Bool_6850;
    return hoisted__Bool_6850;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6858 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_6858;
    if (hoisted__Bool_6858) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6859 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_6859;
    if (hoisted__Bool_6859) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6860 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_6860;
    if (hoisted__Bool_6860) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    static Str hoisted__Str_6861 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_6861;
    UNREACHABLE(&hoisted__Str_6861);
    Str_delete(&hoisted__Str_6861, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_6862 = 1;
    (void)hoisted__U32_6862;
    return hoisted__U32_6862;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6863 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_6863;
    (void)_til_str_lit_203;
    (void)_til_str_lit_203;
    assert(hoisted__Bool_6863, &_til_str_lit_203);
    Str_delete(&_til_str_lit_203, (Bool){0});
    Bool hoisted__Bool_6865 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_6865;
    Bool hoisted__Bool_6866 = ((Bool)(!(hoisted__Bool_6865)));
    (void)hoisted__Bool_6866;
    (void)_til_str_lit_204;
    (void)_til_str_lit_204;
    assert(hoisted__Bool_6866, &_til_str_lit_204);
    Str_delete(&_til_str_lit_204, (Bool){0});
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
void Token_delete(Token * self, Bool call_free) {
    U32 hoisted__U32_6891 = 1;
    (void)hoisted__U32_6891;
    Bool hoisted__Bool_6892 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_6892;
    if (hoisted__Bool_6892) {
        I64 *hoisted__I64_6887 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)hoisted__I64_6887;
        (void)hoisted__I64_6887;
        Bool hoisted__Bool_6888 = 0;
        (void)hoisted__Bool_6888;
        I64_delete(hoisted__I64_6887, hoisted__Bool_6888);
    }
    U32 hoisted__U32_6893 = 1;
    (void)hoisted__U32_6893;
    Bool hoisted__Bool_6894 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_6894;
    if (hoisted__Bool_6894) {
        Str *hoisted__Str_6889 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)hoisted__Str_6889;
        (void)hoisted__Str_6889;
        Bool hoisted__Bool_6890 = 0;
        (void)hoisted__Bool_6890;
        Str_delete(hoisted__Str_6889, hoisted__Bool_6890);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    U32 hoisted__U32_6922 = 1;
    (void)hoisted__U32_6922;
    Bool hoisted__Bool_6923 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_6923;
    if (hoisted__Bool_6923) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_6919 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_6919;
        return hoisted__Token_6919;
    }
    U32 hoisted__U32_6924 = 1;
    (void)hoisted__U32_6924;
    Bool hoisted__Bool_6925 = ((Bool)(((Token *)(self))->tag == ((Token *)(&(Token){.tag = Token_TAG_Name}))->tag));
    (void)hoisted__Bool_6925;
    if (hoisted__Bool_6925) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_6920 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_6920;
        Token *hoisted__Token_6921 = Token_Name(hoisted__Str_6920);
        (void)hoisted__Token_6921;
        return hoisted__Token_6921;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

USize Token_size(void) {
    U32 hoisted__U32_6926 = 24;
    (void)hoisted__U32_6926;
    return hoisted__U32_6926;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6928 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_6928;
    (void)_til_str_lit_207;
    (void)_til_str_lit_207;
    assert(hoisted__Bool_6928, &_til_str_lit_207);
    Str_delete(&_til_str_lit_207, (Bool){0});
    Bool hoisted__Bool_6930 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_6930;
    Bool hoisted__Bool_6931 = ((Bool)(!(hoisted__Bool_6930)));
    (void)hoisted__Bool_6931;
    (void)_til_str_lit_208;
    (void)_til_str_lit_208;
    assert(hoisted__Bool_6931, &_til_str_lit_208);
    Str_delete(&_til_str_lit_208, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6933 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_6933;
    (void)_til_str_lit_209;
    (void)_til_str_lit_209;
    assert(hoisted__Bool_6933, &_til_str_lit_209);
    Str_delete(&_til_str_lit_209, (Bool){0});
    Bool hoisted__Bool_6935 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_6935;
    Bool hoisted__Bool_6936 = ((Bool)(!(hoisted__Bool_6935)));
    (void)hoisted__Bool_6936;
    (void)_til_str_lit_210;
    (void)_til_str_lit_210;
    assert(hoisted__Bool_6936, &_til_str_lit_210);
    Str_delete(&_til_str_lit_210, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6940 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    (void)hoisted__Bool_6940;
    (void)_til_str_lit_211;
    (void)_til_str_lit_211;
    assert(hoisted__Bool_6940, &_til_str_lit_211);
    Str_delete(&_til_str_lit_211, (Bool){0});
    Bool hoisted__Bool_6942 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    (void)hoisted__Bool_6942;
    Bool hoisted__Bool_6943 = ((Bool)(!(hoisted__Bool_6942)));
    (void)hoisted__Bool_6943;
    (void)_til_str_lit_212;
    (void)_til_str_lit_212;
    assert(hoisted__Bool_6943, &_til_str_lit_212);
    Str_delete(&_til_str_lit_212, (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7013 = ((Bool)(a != b));
    (void)hoisted__Bool_7013;
    if (hoisted__Bool_7013) {
        U32 hoisted__U32_7002 = 5;
        (void)hoisted__U32_7002;
        Array__Str *_va_Array_185 = Array__Str_new(hoisted__U32_7002);
        (void)_va_Array_185;
        I64 _va_Array_185_ek = 0;
        (void)_va_Array_185_ek;
        U32 hoisted__U32_7003 = 0;
        (void)hoisted__U32_7003;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_185, hoisted__U32_7003, &_til_str_lit_213, &_va_Array_185_ek);
        U32 hoisted__U32_7005 = 1;
        (void)hoisted__U32_7005;
        Str *hoisted__Str_7006 = I64_to_str(a);
        (void)hoisted__Str_7006;
        Array__Str_set(_va_Array_185, hoisted__U32_7005, hoisted__Str_7006, &_va_Array_185_ek);
        U32 hoisted__U32_7007 = 2;
        (void)hoisted__U32_7007;
        (void)_til_str_lit_214;
        (void)_til_str_lit_214;
        Array__Str_set(_va_Array_185, hoisted__U32_7007, &_til_str_lit_214, &_va_Array_185_ek);
        U32 hoisted__U32_7009 = 3;
        (void)hoisted__U32_7009;
        Str *hoisted__Str_7010 = I64_to_str(b);
        (void)hoisted__Str_7010;
        Array__Str_set(_va_Array_185, hoisted__U32_7009, hoisted__Str_7010, &_va_Array_185_ek);
        U32 hoisted__U32_7011 = 4;
        (void)hoisted__U32_7011;
        (void)_til_str_lit_215;
        (void)_til_str_lit_215;
        Array__Str_set(_va_Array_185, hoisted__U32_7011, &_til_str_lit_215, &_va_Array_185_ek);
        panic(_va_Array_185, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7025 = Str_neq(a, b);
    (void)hoisted__Bool_7025;
    if (hoisted__Bool_7025) {
        U32 hoisted__U32_7014 = 5;
        (void)hoisted__U32_7014;
        Array__Str *_va_Array_186 = Array__Str_new(hoisted__U32_7014);
        (void)_va_Array_186;
        I64 _va_Array_186_ek = 0;
        (void)_va_Array_186_ek;
        U32 hoisted__U32_7015 = 0;
        (void)hoisted__U32_7015;
        (void)_til_str_lit_213;
        (void)_til_str_lit_213;
        Array__Str_set(_va_Array_186, hoisted__U32_7015, &_til_str_lit_213, &_va_Array_186_ek);
        U32 hoisted__U32_7017 = 1;
        (void)hoisted__U32_7017;
        Str *hoisted__Str_7018 = Str_to_str(a);
        (void)hoisted__Str_7018;
        Array__Str_set(_va_Array_186, hoisted__U32_7017, hoisted__Str_7018, &_va_Array_186_ek);
        U32 hoisted__U32_7019 = 2;
        (void)hoisted__U32_7019;
        (void)_til_str_lit_214;
        (void)_til_str_lit_214;
        Array__Str_set(_va_Array_186, hoisted__U32_7019, &_til_str_lit_214, &_va_Array_186_ek);
        U32 hoisted__U32_7021 = 3;
        (void)hoisted__U32_7021;
        Str *hoisted__Str_7022 = Str_to_str(b);
        (void)hoisted__Str_7022;
        Array__Str_set(_va_Array_186, hoisted__U32_7021, hoisted__Str_7022, &_va_Array_186_ek);
        U32 hoisted__U32_7023 = 4;
        (void)hoisted__U32_7023;
        (void)_til_str_lit_215;
        (void)_til_str_lit_215;
        Array__Str_set(_va_Array_186, hoisted__U32_7023, &_til_str_lit_215, &_va_Array_186_ek);
        panic(_va_Array_186, loc);
    }
}

USize Str_len_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Str_len(_a0);
}
static __attribute__((unused)) TilClosure Str_len_dyn__til_closure = { (void *)Str_len_dyn, NULL, NULL };
I64 Str_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_cmp(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_cmp_dyn__til_closure = { (void *)Str_cmp_dyn, NULL, NULL };
Bool Str_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_eq_dyn__til_closure = { (void *)Str_eq_dyn, NULL, NULL };
void *Str_with_capacity_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Str_with_capacity(*(USize *)_a0);
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
USize Str_size_dyn(void *til_env) {
    (void)til_env;
    return Str_size();
}
static __attribute__((unused)) TilClosure Str_size_dyn__til_closure = { (void *)Str_size_dyn, NULL, NULL };
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
USize OutOfBounds_size_dyn(void *til_env) {
    (void)til_env;
    return OutOfBounds_size();
}
static __attribute__((unused)) TilClosure OutOfBounds_size_dyn__til_closure = { (void *)OutOfBounds_size_dyn, NULL, NULL };
void *Array__Str_new_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Array__Str_new(*(USize *)_a0);
}
static __attribute__((unused)) TilClosure Array__Str_new_dyn__til_closure = { (void *)Array__Str_new_dyn, NULL, NULL };
USize Array__Str_len_dyn(void *til_env, void *_a0) {
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
    Array__Str_unsafe_set(_a0, *(USize *)_a1, _a2);
}
static __attribute__((unused)) TilClosure Array__Str_unsafe_set_dyn__til_closure = { (void *)Array__Str_unsafe_set_dyn, NULL, NULL };
void Array__Str_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3) {
    (void)til_env;
    Array__Str_set(_a0, *(USize *)_a1, _a2, _a3);
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
USize Array__Str_size_dyn(void *til_env) {
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
USize Vec__Str_size_dyn(void *til_env) {
    (void)til_env;
    return Vec__Str_size();
}
static __attribute__((unused)) TilClosure Vec__Str_size_dyn__til_closure = { (void *)Vec__Str_size_dyn, NULL, NULL };
USize Dynamic_size_dyn(void *til_env) {
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
USize U8_size_dyn(void *til_env) {
    (void)til_env;
    return U8_size();
}
static __attribute__((unused)) TilClosure U8_size_dyn__til_closure = { (void *)U8_size_dyn, NULL, NULL };
U64 U8_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U8_hash(*(U8 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U8_hash_dyn__til_closure = { (void *)U8_hash_dyn, NULL, NULL };
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
USize U32_size_dyn(void *til_env) {
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
USize U64_size_dyn(void *til_env) {
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
USize I8_size_dyn(void *til_env) {
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
USize I32_size_dyn(void *til_env) {
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
USize I64_size_dyn(void *til_env) {
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
USize F32_size_dyn(void *til_env) {
    (void)til_env;
    return F32_size();
}
static __attribute__((unused)) TilClosure F32_size_dyn__til_closure = { (void *)F32_size_dyn, NULL, NULL };
U64 F32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return F32_hash(*(F32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure F32_hash_dyn__til_closure = { (void *)F32_hash_dyn, NULL, NULL };
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
USize Bool_size_dyn(void *til_env) {
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
USize Primitive_size_dyn(void *til_env) {
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
USize Type_size_dyn(void *til_env) {
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
USize FuncType_size_dyn(void *til_env) {
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
USize OwnType_size_dyn(void *til_env) {
    (void)til_env;
    return OwnType_size();
}
static __attribute__((unused)) TilClosure OwnType_size_dyn__til_closure = { (void *)OwnType_size_dyn, NULL, NULL };
Bool GcStorage_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return GcStorage_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure GcStorage_eq_dyn__til_closure = { (void *)GcStorage_eq_dyn, NULL, NULL };
void GcStorage_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    GcStorage_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure GcStorage_delete_dyn__til_closure = { (void *)GcStorage_delete_dyn, NULL, NULL };
void *GcStorage_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)GcStorage_clone(_a0);
}
static __attribute__((unused)) TilClosure GcStorage_clone_dyn__til_closure = { (void *)GcStorage_clone_dyn, NULL, NULL };
USize GcStorage_size_dyn(void *til_env) {
    (void)til_env;
    return GcStorage_size();
}
static __attribute__((unused)) TilClosure GcStorage_size_dyn__til_closure = { (void *)GcStorage_size_dyn, NULL, NULL };
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
USize Declaration_size_dyn(void *til_env) {
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
USize FunctionDef_size_dyn(void *til_env) {
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
USize FCallData_size_dyn(void *til_env) {
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
USize LiteralNumData_size_dyn(void *til_env) {
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
USize IdentData_size_dyn(void *til_env) {
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
USize FieldAccessData_size_dyn(void *til_env) {
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
USize StructDef_size_dyn(void *til_env) {
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
USize EnumDef_size_dyn(void *til_env) {
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
USize AssignData_size_dyn(void *til_env) {
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
USize FieldAssignData_size_dyn(void *til_env) {
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
USize ForInData_size_dyn(void *til_env) {
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
USize Literal_size_dyn(void *til_env) {
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
USize MatchData_size_dyn(void *til_env) {
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
USize CaptureBlockData_size_dyn(void *til_env) {
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
void *NodeType_ListPattern_dyn(void *til_env) {
    (void)til_env;
    return (void *)NodeType_ListPattern();
}
static __attribute__((unused)) TilClosure NodeType_ListPattern_dyn__til_closure = { (void *)NodeType_ListPattern_dyn, NULL, NULL };
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
USize NodeType_size_dyn(void *til_env) {
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
USize Expr_size_dyn(void *til_env) {
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
USize Map__I64_Str_size_dyn(void *til_env) {
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
USize Vec__Bool_size_dyn(void *til_env) {
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
USize Vec__I64_size_dyn(void *til_env) {
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
USize Vec__Declaration_size_dyn(void *til_env) {
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
USize Vec__Expr_size_dyn(void *til_env) {
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
USize Range_size_dyn(void *til_env) {
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
USize CfVec2_size_dyn(void *til_env) {
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
USize CfRect_size_dyn(void *til_env) {
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
USize CfVec3f_size_dyn(void *til_env) {
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
USize Color_size_dyn(void *til_env) {
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
USize Token_size_dyn(void *til_env) {
    (void)til_env;
    return Token_size();
}
static __attribute__((unused)) TilClosure Token_size_dyn__til_closure = { (void *)Token_size_dyn, NULL, NULL };
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Str_len_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Str_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Str_eq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)&Str_with_capacity_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)&Str_push_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Str_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&Str_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Str_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Str_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Str_size_dyn__til_closure;
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
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&GcStorage_eq_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&GcStorage_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&GcStorage_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&GcStorage_size_dyn__til_closure;
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
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "ListPattern", 11ULL) == 0) return (void*)&NodeType_ListPattern_dyn__til_closure;
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
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) return sizeof(GcStorage);
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
        return 0LL;
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
        return 12LL;
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
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
        if (*index == 1LL) return &_til_str_lit_4;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
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
        if (*index == 0LL) return &_til_str_lit_47;
        if (*index == 1LL) return &_til_str_lit_48;
        if (*index == 2LL) return &_til_str_lit_49;
        if (*index == 3LL) return &_til_str_lit_50;
        if (*index == 4LL) return &_til_str_lit_51;
        if (*index == 5LL) return &_til_str_lit_52;
        if (*index == 6LL) return &_til_str_lit_53;
        if (*index == 7LL) return &_til_str_lit_54;
        if (*index == 8LL) return &_til_str_lit_56;
        if (*index == 9LL) return &_til_str_lit_58;
        if (*index == 10LL) return &_til_str_lit_60;
        if (*index == 11LL) return &_til_str_lit_61;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_63;
        if (*index == 1LL) return &_til_str_lit_65;
        if (*index == 2LL) return &_til_str_lit_67;
        if (*index == 3LL) return &_til_str_lit_68;
        if (*index == 4LL) return &_til_str_lit_70;
        if (*index == 5LL) return &_til_str_lit_71;
        if (*index == 6LL) return &_til_str_lit_72;
        if (*index == 7LL) return &_til_str_lit_73;
        if (*index == 8LL) return &_til_str_lit_74;
        if (*index == 9LL) return &_til_str_lit_75;
        if (*index == 10LL) return &_til_str_lit_76;
        if (*index == 11LL) return &_til_str_lit_77;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_78;
        if (*index == 1LL) return &_til_str_lit_79;
        if (*index == 2LL) return &_til_str_lit_80;
        if (*index == 3LL) return &_til_str_lit_81;
        if (*index == 4LL) return &_til_str_lit_82;
        if (*index == 5LL) return &_til_str_lit_56;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_83;
        if (*index == 1LL) return &_til_str_lit_56;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_47;
        if (*index == 1LL) return &_til_str_lit_56;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_47;
        if (*index == 1LL) return &_til_str_lit_56;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_84;
        if (*index == 1LL) return &_til_str_lit_85;
        if (*index == 2LL) return &_til_str_lit_86;
        if (*index == 3LL) return &_til_str_lit_87;
        if (*index == 4LL) return &_til_str_lit_88;
        if (*index == 5LL) return &_til_str_lit_89;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_85;
        if (*index == 1LL) return &_til_str_lit_90;
        if (*index == 2LL) return &_til_str_lit_91;
        if (*index == 3LL) return &_til_str_lit_93;
        if (*index == 4LL) return &_til_str_lit_89;
        if (*index == 5LL) return &_til_str_lit_95;
        if (*index == 6LL) return &_til_str_lit_96;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_47;
        if (*index == 1LL) return &_til_str_lit_98;
        if (*index == 2LL) return &_til_str_lit_99;
        if (*index == 3LL) return &_til_str_lit_82;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_47;
        if (*index == 1LL) return &_til_str_lit_98;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_47;
        if (*index == 1LL) return &_til_str_lit_50;
        if (*index == 2LL) return &_til_str_lit_56;
        if (*index == 3LL) return &_til_str_lit_100;
        if (*index == 4LL) return &_til_str_lit_101;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_56;
        if (*index == 1LL) return &_til_str_lit_107;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_76;
        if (*index == 1LL) return &_til_str_lit_77;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_143;
        if (*index == 1LL) return &_til_str_lit_145;
        if (*index == 2LL) return &_til_str_lit_147;
        if (*index == 3LL) return &_til_str_lit_148;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_149;
        if (*index == 1LL) return &_til_str_lit_150;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_5;
        if (*index == 1LL) return &_til_str_lit_2;
        if (*index == 2LL) return &_til_str_lit_4;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_154;
        if (*index == 1LL) return &_til_str_lit_155;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_180;
        if (*index == 1LL) return &_til_str_lit_181;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_186;
        if (*index == 1LL) return &_til_str_lit_188;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_180;
        if (*index == 1LL) return &_til_str_lit_181;
        if (*index == 2LL) return &_til_str_lit_193;
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
        if (*index == 11LL) return 1;
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
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_3;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__Str", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
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
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_20;
        if (*index == 2LL) return &_til_str_lit_20;
        if (*index == 3LL) return &_til_str_lit_15;
        if (*index == 4LL) return &_til_str_lit_15;
        if (*index == 5LL) return &_til_str_lit_15;
        if (*index == 6LL) return &_til_str_lit_15;
        if (*index == 7LL) return &_til_str_lit_55;
        if (*index == 8LL) return &_til_str_lit_57;
        if (*index == 9LL) return &_til_str_lit_59;
        if (*index == 10LL) return &_til_str_lit_20;
        if (*index == 11LL) return &_til_str_lit_62;
    }
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "FunctionDef", 11ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_64;
        if (*index == 1LL) return &_til_str_lit_66;
        if (*index == 2LL) return &_til_str_lit_20;
        if (*index == 3LL) return &_til_str_lit_69;
        if (*index == 4LL) return &_til_str_lit_12;
        if (*index == 5LL) return &_til_str_lit_12;
        if (*index == 6LL) return &_til_str_lit_55;
        if (*index == 7LL) return &_til_str_lit_15;
        if (*index == 8LL) return &_til_str_lit_15;
        if (*index == 9LL) return &_til_str_lit_15;
        if (*index == 10LL) return &_til_str_lit_66;
        if (*index == 11LL) return &_til_str_lit_20;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "FCallData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_15;
        if (*index == 1LL) return &_til_str_lit_15;
        if (*index == 2LL) return &_til_str_lit_15;
        if (*index == 3LL) return &_til_str_lit_8;
        if (*index == 4LL) return &_til_str_lit_15;
        if (*index == 5LL) return &_til_str_lit_57;
    }
    if (type_name->count == 14ULL && memcmp(type_name->c_str, "LiteralNumData", 14ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_57;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "IdentData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_57;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAccessData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_57;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "StructDef", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_66;
        if (*index == 1LL) return &_til_str_lit_66;
        if (*index == 2LL) return &_til_str_lit_20;
        if (*index == 3LL) return &_til_str_lit_15;
        if (*index == 4LL) return &_til_str_lit_15;
        if (*index == 5LL) return &_til_str_lit_20;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_66;
        if (*index == 1LL) return &_til_str_lit_69;
        if (*index == 2LL) return &_til_str_lit_92;
        if (*index == 3LL) return &_til_str_lit_94;
        if (*index == 4LL) return &_til_str_lit_20;
        if (*index == 5LL) return &_til_str_lit_20;
        if (*index == 6LL) return &_til_str_lit_97;
    }
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "AssignData", 10ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_15;
        if (*index == 2LL) return &_til_str_lit_15;
        if (*index == 3LL) return &_til_str_lit_15;
    }
    if (type_name->count == 15ULL && memcmp(type_name->c_str, "FieldAssignData", 15ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_15;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "ForInData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_15;
        if (*index == 2LL) return &_til_str_lit_57;
        if (*index == 3LL) return &_til_str_lit_20;
        if (*index == 4LL) return &_til_str_lit_15;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "MatchData", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_57;
        if (*index == 1LL) return &_til_str_lit_20;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "CaptureBlockData", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_66;
        if (*index == 1LL) return &_til_str_lit_20;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_144;
        if (*index == 1LL) return &_til_str_lit_146;
        if (*index == 2LL) return &_til_str_lit_11;
        if (*index == 3LL) return &_til_str_lit_11;
    }
    if (type_name->count == 12ULL && memcmp(type_name->c_str, "Map__I64_Str", 12ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_97;
        if (*index == 1LL) return &_til_str_lit_69;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Bool", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "Vec__I64", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 16ULL && memcmp(type_name->c_str, "Vec__Declaration", 16ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Vec__Expr", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_6;
        if (*index == 1LL) return &_til_str_lit_3;
        if (*index == 2LL) return &_til_str_lit_3;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_8;
        if (*index == 1LL) return &_til_str_lit_8;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_13;
        if (*index == 1LL) return &_til_str_lit_13;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_187;
        if (*index == 1LL) return &_til_str_lit_187;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_14;
        if (*index == 1LL) return &_til_str_lit_14;
        if (*index == 2LL) return &_til_str_lit_14;
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
        return 11LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        return 6LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        return 29LL;
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
        if (*index == 0LL) return &_til_str_lit_9;
        if (*index == 1LL) return &_til_str_lit_10;
        if (*index == 2LL) return &_til_str_lit_1;
        if (*index == 3LL) return &_til_str_lit_6;
        if (*index == 4LL) return &_til_str_lit_11;
        if (*index == 5LL) return &_til_str_lit_12;
        if (*index == 6LL) return &_til_str_lit_8;
        if (*index == 7LL) return &_til_str_lit_13;
        if (*index == 8LL) return &_til_str_lit_14;
        if (*index == 9LL) return &_til_str_lit_15;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_17;
        if (*index == 1LL) return &_til_str_lit_18;
        if (*index == 2LL) return &_til_str_lit_19;
        if (*index == 3LL) return &_til_str_lit_21;
        if (*index == 4LL) return &_til_str_lit_22;
        if (*index == 5LL) return &_til_str_lit_23;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_25;
        if (*index == 8LL) return &_til_str_lit_7;
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
        if (*index == 10LL) return &_til_str_lit_40;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_41;
        if (*index == 1LL) return &_til_str_lit_42;
        if (*index == 2LL) return &_til_str_lit_43;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_44;
        if (*index == 1LL) return &_til_str_lit_45;
        if (*index == 2LL) return &_til_str_lit_46;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_102;
        if (*index == 2LL) return &_til_str_lit_15;
        if (*index == 3LL) return &_til_str_lit_104;
        if (*index == 4LL) return &_til_str_lit_105;
        if (*index == 5LL) return &_til_str_lit_106;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_29;
        if (*index == 1LL) return &_til_str_lit_108;
        if (*index == 2LL) return &_til_str_lit_109;
        if (*index == 3LL) return &_til_str_lit_111;
        if (*index == 4LL) return &_til_str_lit_113;
        if (*index == 5LL) return &_til_str_lit_115;
        if (*index == 6LL) return &_til_str_lit_24;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_118;
        if (*index == 10LL) return &_til_str_lit_120;
        if (*index == 11LL) return &_til_str_lit_122;
        if (*index == 12LL) return &_til_str_lit_123;
        if (*index == 13LL) return &_til_str_lit_124;
        if (*index == 14LL) return &_til_str_lit_125;
        if (*index == 15LL) return &_til_str_lit_127;
        if (*index == 16LL) return &_til_str_lit_128;
        if (*index == 17LL) return &_til_str_lit_129;
        if (*index == 18LL) return &_til_str_lit_130;
        if (*index == 19LL) return &_til_str_lit_131;
        if (*index == 20LL) return &_til_str_lit_133;
        if (*index == 21LL) return &_til_str_lit_134;
        if (*index == 22LL) return &_til_str_lit_135;
        if (*index == 23LL) return &_til_str_lit_136;
        if (*index == 24LL) return &_til_str_lit_137;
        if (*index == 25LL) return &_til_str_lit_138;
        if (*index == 26LL) return &_til_str_lit_140;
        if (*index == 27LL) return &_til_str_lit_141;
        if (*index == 28LL) return &_til_str_lit_142;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_200;
        if (*index == 1LL) return &_til_str_lit_201;
        if (*index == 2LL) return &_til_str_lit_202;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_102;
        if (*index == 1LL) return &_til_str_lit_205;
        if (*index == 2LL) return &_til_str_lit_206;
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
        if (*index == 10LL) return 0;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
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
        if (*index == 28LL) return 0;
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
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_16;
        if (*index == 6LL) return &_til_str_lit_16;
        if (*index == 7LL) return &_til_str_lit_16;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_16;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_20;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_20;
        if (*index == 5LL) return &_til_str_lit_16;
        if (*index == 6LL) return &_til_str_lit_16;
        if (*index == 7LL) return &_til_str_lit_16;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_20;
        if (*index == 10LL) return &_til_str_lit_27;
        if (*index == 11LL) return &_til_str_lit_20;
        if (*index == 12LL) return &_til_str_lit_16;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "FuncType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_16;
        if (*index == 6LL) return &_til_str_lit_16;
        if (*index == 7LL) return &_til_str_lit_16;
        if (*index == 8LL) return &_til_str_lit_16;
        if (*index == 9LL) return &_til_str_lit_16;
        if (*index == 10LL) return &_til_str_lit_16;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "OwnType", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
    }
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "GcStorage", 9ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Literal", 7ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_20;
        if (*index == 1LL) return &_til_str_lit_103;
        if (*index == 2LL) return &_til_str_lit_15;
        if (*index == 3LL) return &_til_str_lit_16;
        if (*index == 4LL) return &_til_str_lit_16;
        if (*index == 5LL) return &_til_str_lit_16;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "NodeType", 8ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_108;
        if (*index == 2LL) return &_til_str_lit_110;
        if (*index == 3LL) return &_til_str_lit_112;
        if (*index == 4LL) return &_til_str_lit_114;
        if (*index == 5LL) return &_til_str_lit_116;
        if (*index == 6LL) return &_til_str_lit_117;
        if (*index == 7LL) return &_til_str_lit_21;
        if (*index == 8LL) return &_til_str_lit_23;
        if (*index == 9LL) return &_til_str_lit_119;
        if (*index == 10LL) return &_til_str_lit_121;
        if (*index == 11LL) return &_til_str_lit_16;
        if (*index == 12LL) return &_til_str_lit_16;
        if (*index == 13LL) return &_til_str_lit_16;
        if (*index == 14LL) return &_til_str_lit_126;
        if (*index == 15LL) return &_til_str_lit_20;
        if (*index == 16LL) return &_til_str_lit_16;
        if (*index == 17LL) return &_til_str_lit_16;
        if (*index == 18LL) return &_til_str_lit_16;
        if (*index == 19LL) return &_til_str_lit_132;
        if (*index == 20LL) return &_til_str_lit_16;
        if (*index == 21LL) return &_til_str_lit_16;
        if (*index == 22LL) return &_til_str_lit_16;
        if (*index == 23LL) return &_til_str_lit_16;
        if (*index == 24LL) return &_til_str_lit_16;
        if (*index == 25LL) return &_til_str_lit_139;
        if (*index == 26LL) return &_til_str_lit_16;
        if (*index == 27LL) return &_til_str_lit_139;
        if (*index == 28LL) return &_til_str_lit_16;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_16;
        if (*index == 1LL) return &_til_str_lit_16;
        if (*index == 2LL) return &_til_str_lit_16;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return &_til_str_lit_13;
        if (*index == 1LL) return &_til_str_lit_20;
        if (*index == 2LL) return &_til_str_lit_16;
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
        if (*index == 0LL) return &_til_str_lit_7;
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
        if (*index == 0LL) return &_til_str_lit_8;
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
