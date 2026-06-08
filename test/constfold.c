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

typedef struct Vec Vec;
typedef struct Str Str;
typedef struct OutOfBounds OutOfBounds;
typedef struct Array__Str Array__Str;
typedef struct Dynamic Dynamic;
typedef struct Map Map;
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

typedef TilClosure *CloneFn;
typedef TilClosure *DeleteFn;
typedef TilClosure *CmpFn;
typedef TilClosure *HashFn;







typedef struct Vec {
    U8 *data;
    U32 count;
    U32 cap;
    U32 elem_size;
    U32 elem_kind;
    TilClosure * elem_clone;
    TilClosure * elem_delete;
} Vec;


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


typedef struct Dynamic {
    char _;
} Dynamic;




typedef struct Map {
    Vec keys;
    Vec values;
    TilClosure * key_cmp;
} Map;


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


typedef struct FunctionDef {
    FuncType func_type;
    Vec params;
    Str return_type;
    Vec throw_types;
    I32 variadic_index;
    I32 kwargs_index;
    OwnType return_own_type;
    Bool auto_generated;
    Bool is_enum_variant_ctor;
    Vec captures;
    Str closure_name;
} FunctionDef;


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


typedef struct StructDef {
    Vec fields;
    Vec ns_decls;
    Str c_tag;
    Bool is_interface;
    Bool interface_ns_marker;
    Str implements_name;
} StructDef;


typedef struct EnumDef {
    Vec ns_decls;
    Vec variants;
    Map payload_types;
    Vec payload_consts;
    Str implements_name;
} EnumDef;


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


typedef struct CaptureBlockData {
    Vec captures;
} CaptureBlockData;


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
    Vec children;
    U32 line;
    U32 col;
} Expr;


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
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(Type * T);
void Vec_clear(Vec * self);
void Vec_delete(Vec * self, Bool call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool call_free);
Bool Str_is_empty(Str * self);
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
U32 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void * default_clone(void * v);
static void * default_clone__til_closure_call(void *til_env, void * v);
static __attribute__((unused)) TilClosure default_clone__til_closure;
void default_delete(void * _v, Bool _cf);
static void default_delete__til_closure_call(void *til_env, void * _v, Bool _cf);
static __attribute__((unused)) TilClosure default_delete__til_closure;
I64 default_cmp(void * _a, void * _b);
static I64 default_cmp__til_closure_call(void *til_env, void * _a, void * _b);
static __attribute__((unused)) TilClosure default_cmp__til_closure;
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
Map * Map_new_type_names(Str * key_type, Str * val_type);
Map * Map_new(Type * K, Type * V);
void Map_clear(Map * self);
void Map_delete(Map * self, Bool call_free);
Map * Map_clone(Map * self);
U64 Map_hash(Map * self, HashFn hasher);
U32 Map_size(void);
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
void panic(Str * loc_str, Array__Str * parts);
void UNREACHABLE(Str * loc_str);
Bool assert(Str * loc_str, Bool cond);
void assert_eq(Str * loc_str, I64 a, I64 b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array__Str * parts);
Bool is_null(void * p);
void swap(void * a, void * b, U64 size);
Range Range_clone(Range val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range self, HashFn hasher);
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
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(Type * T);
void Vec_clear(Vec * self);
void Vec_delete(Vec * self, Bool call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
Str * format(Array__Str * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool call_free);
Bool Str_is_empty(Str * self);
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
U32 Dynamic_size(void);
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
I64 default_cmp(void * _a, void * _b);
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
Map * Map_new_type_names(Str * key_type, Str * val_type);
Map * Map_new(Type * K, Type * V);
void Map_clear(Map * self);
void Map_delete(Map * self, Bool call_free);
Map * Map_clone(Map * self);
U64 Map_hash(Map * self, HashFn hasher);
U32 Map_size(void);
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
void panic(Str * loc_str, Array__Str * parts);
void UNREACHABLE(Str * loc_str);
Bool assert(Str * loc_str, Bool cond);
void assert_eq(Str * loc_str, I64 a, I64 b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array__Str * parts);
Bool is_null(void * p);
void swap(void * a, void * b, U64 size);
Range Range_clone(Range val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range self, HashFn hasher);
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
Str *dyn_type_to_str(Type *type);

Bool dyn_has_cmp(Str *type_name);

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

Vec * Vec_new_type_name(Str * elem_type) {
    Bool hoisted__Bool_521 = Str_is_empty(elem_type);
    (void)hoisted__Bool_521;
    if (hoisted__Bool_521) {
        U32 hoisted__U32_505 = 1;
        (void)hoisted__U32_505;
        Array__Str *_va_Array_14 = Array__Str_new(hoisted__U32_505);
        (void)_va_Array_14;
        U32 hoisted__U32_506 = 0;
        (void)hoisted__U32_506;
        Str hoisted__Str_507 = (Str){.c_str = (void *)"Vec.new: elem_type required", .count = 27ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_507;
        Array__Str_set(_va_Array_14, hoisted__U32_506, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_507; _oa; }));
        Str hoisted__Str_508 = (Str){.c_str = (void *)"./src/core/vec.til:25:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_508;
        panic(&hoisted__Str_508, _va_Array_14);
        Str_delete(&hoisted__Str_508, (Bool){0});
    }
    Str hoisted__Str_522 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_522;
    Bool hoisted__Bool_523 = Str_eq(elem_type, &hoisted__Str_522);
    (void)hoisted__Bool_523;
    Str_delete(&hoisted__Str_522, (Bool){0});
    if (hoisted__Bool_523) {
        U64 hoisted__U64_509 = 8ULL;
        (void)hoisted__U64_509;
        void * hoisted__v_510 = malloc(hoisted__U64_509);
        (void)hoisted__v_510;
        U32 hoisted__U32_511 = 0;
        (void)hoisted__U32_511;
        I64 hoisted__I64_512 = 1;
        (void)hoisted__I64_512;
        I64 hoisted__I64_513 = 8;
        (void)hoisted__I64_513;
        Vec *hoisted__Vec_514 = malloc(sizeof(Vec));
        hoisted__Vec_514->data = hoisted__v_510;
        hoisted__Vec_514->count = hoisted__U32_511;
        hoisted__Vec_514->cap = hoisted__I64_512;
        hoisted__Vec_514->elem_size = hoisted__I64_513;
        hoisted__Vec_514->elem_kind = ELEM_POD;
        hoisted__Vec_514->elem_clone = (void *)&default_clone__til_closure;
        hoisted__Vec_514->elem_delete = (void *)&default_delete__til_closure;
        (void)hoisted__Vec_514;
        { Vec * _ret_val = hoisted__Vec_514;
                return _ret_val; }
    }
    Str hoisted__Str_524 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_524;
    Bool hoisted__Bool_525 = Str_eq(elem_type, &hoisted__Str_524);
    (void)hoisted__Bool_525;
    Str_delete(&hoisted__Str_524, (Bool){0});
    if (hoisted__Bool_525) {
        U64 hoisted__U64_515 = 8ULL;
        (void)hoisted__U64_515;
        void * hoisted__v_516 = malloc(hoisted__U64_515);
        (void)hoisted__v_516;
        U32 hoisted__U32_517 = 0;
        (void)hoisted__U32_517;
        I64 hoisted__I64_518 = 1;
        (void)hoisted__I64_518;
        I64 hoisted__I64_519 = 8;
        (void)hoisted__I64_519;
        Vec *hoisted__Vec_520 = malloc(sizeof(Vec));
        hoisted__Vec_520->data = hoisted__v_516;
        hoisted__Vec_520->count = hoisted__U32_517;
        hoisted__Vec_520->cap = hoisted__I64_518;
        hoisted__Vec_520->elem_size = hoisted__I64_519;
        hoisted__Vec_520->elem_kind = ELEM_FN;
        hoisted__Vec_520->elem_clone = (void *)&default_clone__til_closure;
        hoisted__Vec_520->elem_delete = (void *)&default_delete__til_closure;
        (void)hoisted__Vec_520;
        { Vec * _ret_val = hoisted__Vec_520;
                return _ret_val; }
    }
    U32 sz = dyn_size_of(elem_type);
    void * hoisted__v_526 = malloc(sz);
    (void)hoisted__v_526;
    U32 hoisted__U32_527 = 0;
    (void)hoisted__U32_527;
    I64 hoisted__I64_528 = 1;
    (void)hoisted__I64_528;
    void * hoisted__v_529 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_529;
    void * hoisted__v_530 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_530;
    Vec *hoisted__Vec_531 = malloc(sizeof(Vec));
    hoisted__Vec_531->data = hoisted__v_526;
    hoisted__Vec_531->count = hoisted__U32_527;
    hoisted__Vec_531->cap = hoisted__I64_528;
    hoisted__Vec_531->elem_size = sz;
    hoisted__Vec_531->elem_kind = ELEM_BOXED;
    hoisted__Vec_531->elem_clone = hoisted__v_529;
    hoisted__Vec_531->elem_delete = hoisted__v_530;
    (void)hoisted__Vec_531;
    return hoisted__Vec_531;
}

Vec * Vec_new(Type * T) {
    Str *elem_type = dyn_type_to_str(T);
    Vec *hoisted__Vec_532 = Vec_new_type_name(elem_type);
    (void)hoisted__Vec_532;
    Str_delete(elem_type, 1);
    return hoisted__Vec_532;
}

void Vec_clear(Vec * self) {
    Bool hoisted__Bool_543 = U32_eq(self->elem_kind, ELEM_BOXED);
    (void)hoisted__Bool_543;
    if (hoisted__Bool_543) {
        {
            U32 _re_U32_533 = self->count;
            (void)_re_U32_533;
            U32 _rc_U32_533 = 0;
            (void)_rc_U32_533;
            Bool hoisted__Bool_542 = U32_lte(_rc_U32_533, _re_U32_533);
            (void)hoisted__Bool_542;
            if (hoisted__Bool_542) {
                while (1) {
                    Bool _wcond_Bool_534 = U32_lt(_rc_U32_533, _re_U32_533);
                    (void)_wcond_Bool_534;
                    if (_wcond_Bool_534) {
                    } else {
                        break;
                    }
                    U32 i = U32_clone(&_rc_U32_533);
                    U32_inc(&_rc_U32_533);
                    U32 hoisted__U64_535 = U32_mul(i, self->elem_size);
                    (void)hoisted__U64_535;
                    void *hoisted__v_536 = ptr_add(self->data, hoisted__U64_535);
                    (void)hoisted__v_536;
                    (void)hoisted__v_536;
                    Bool hoisted__Bool_537 = 0;
                    (void)hoisted__Bool_537;
                    ({ TilClosure *til_closure = (TilClosure *)(self->elem_delete); ((void (*)(void *, void *, Bool))til_closure->call)(til_closure->env, hoisted__v_536, hoisted__Bool_537); });
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_538 = U32_gt(_rc_U32_533, _re_U32_533);
                    (void)_wcond_Bool_538;
                    if (_wcond_Bool_538) {
                    } else {
                        break;
                    }
                    U32 i = U32_clone(&_rc_U32_533);
                    U32_dec(&_rc_U32_533);
                    U32 hoisted__U64_539 = U32_mul(i, self->elem_size);
                    (void)hoisted__U64_539;
                    void *hoisted__v_540 = ptr_add(self->data, hoisted__U64_539);
                    (void)hoisted__v_540;
                    (void)hoisted__v_540;
                    Bool hoisted__Bool_541 = 0;
                    (void)hoisted__Bool_541;
                    ({ TilClosure *til_closure = (TilClosure *)(self->elem_delete); ((void (*)(void *, void *, Bool))til_closure->call)(til_closure->env, hoisted__v_540, hoisted__Bool_541); });
                }
            }
        }
    }
    U32 hoisted__U32_544 = 0;
    (void)hoisted__U32_544;
    self->count = hoisted__U32_544;
}

void Vec_delete(Vec * self, Bool call_free) {
    Vec_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    U32 hoisted__U64_732 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_732;
    void * new_data = malloc(hoisted__U64_732);
    Bool hoisted__Bool_733 = U32_eq(self->elem_kind, ELEM_BOXED);
    (void)hoisted__Bool_733;
    if (hoisted__Bool_733) {
        {
            U32 _re_U32_719 = self->count;
            (void)_re_U32_719;
            U32 _rc_U32_719 = 0;
            (void)_rc_U32_719;
            Bool hoisted__Bool_730 = U32_lte(_rc_U32_719, _re_U32_719);
            (void)hoisted__Bool_730;
            if (hoisted__Bool_730) {
                while (1) {
                    Bool _wcond_Bool_720 = U32_lt(_rc_U32_719, _re_U32_719);
                    (void)_wcond_Bool_720;
                    if (_wcond_Bool_720) {
                    } else {
                        break;
                    }
                    U32 i = U32_clone(&_rc_U32_719);
                    U32_inc(&_rc_U32_719);
                    U32 hoisted__U64_721 = U32_mul(i, self->elem_size);
                    (void)hoisted__U64_721;
                    void *hoisted__v_722 = ptr_add(self->data, hoisted__U64_721);
                    (void)hoisted__v_722;
                    (void)hoisted__v_722;
                    void * cloned = ({ TilClosure *til_closure = (TilClosure *)(self->elem_clone); ((void * (*)(void *, void *))til_closure->call)(til_closure->env, hoisted__v_722); });
                    U32 hoisted__U64_723 = U32_mul(i, self->elem_size);
                    (void)hoisted__U64_723;
                    void *hoisted__v_724 = ptr_add(new_data, hoisted__U64_723);
                    (void)hoisted__v_724;
                    (void)hoisted__v_724;
                    memcpy(hoisted__v_724, cloned, self->elem_size);
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_725 = U32_gt(_rc_U32_719, _re_U32_719);
                    (void)_wcond_Bool_725;
                    if (_wcond_Bool_725) {
                    } else {
                        break;
                    }
                    U32 i = U32_clone(&_rc_U32_719);
                    U32_dec(&_rc_U32_719);
                    U32 hoisted__U64_726 = U32_mul(i, self->elem_size);
                    (void)hoisted__U64_726;
                    void *hoisted__v_727 = ptr_add(self->data, hoisted__U64_726);
                    (void)hoisted__v_727;
                    (void)hoisted__v_727;
                    void * cloned = ({ TilClosure *til_closure = (TilClosure *)(self->elem_clone); ((void * (*)(void *, void *))til_closure->call)(til_closure->env, hoisted__v_727); });
                    U32 hoisted__U64_728 = U32_mul(i, self->elem_size);
                    (void)hoisted__U64_728;
                    void *hoisted__v_729 = ptr_add(new_data, hoisted__U64_728);
                    (void)hoisted__v_729;
                    (void)hoisted__v_729;
                    memcpy(hoisted__v_729, cloned, self->elem_size);
                    free(cloned);
                }
            }
        }
    } else {
        U32 hoisted__U64_731 = U32_mul(self->count, self->elem_size);
        (void)hoisted__U64_731;
        memcpy(new_data, self->data, hoisted__U64_731);
    }
    Vec *hoisted__Vec_734 = malloc(sizeof(Vec));
    hoisted__Vec_734->data = new_data;
    hoisted__Vec_734->count = self->count;
    hoisted__Vec_734->cap = self->cap;
    hoisted__Vec_734->elem_size = self->elem_size;
    hoisted__Vec_734->elem_kind = self->elem_kind;
    hoisted__Vec_734->elem_clone = (void *)self->elem_clone;
    hoisted__Vec_734->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Vec_734;
    return hoisted__Vec_734;
}

U32 Vec_size(void) {
    U32 hoisted__U32_735 = 40;
    (void)hoisted__U32_735;
    return hoisted__U32_735;
}

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_856 = parts;
        (void)_fc_Array__Str_856;
        (void)_fc_Array__Str_856;
        U32 _fi_USize_856 = 0;
        (void)_fi_USize_856;
        I64 _forin_err_kind_856 = 0;
        (void)_forin_err_kind_856;
        OutOfBounds *_forin_OutOfBounds_856 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_856->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_856;
        while (1) {
            U32 hoisted__U32_862 = Array__Str_len(_fc_Array__Str_856);
            (void)hoisted__U32_862;
            Bool _wcond_Bool_857 = U32_lt(_fi_USize_856, hoisted__U32_862);
            (void)_wcond_Bool_857;
            if (_wcond_Bool_857) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_856, &_fi_USize_856, &_forin_err_kind_856, _forin_OutOfBounds_856);
            I64 hoisted__I64_863 = 0;
            (void)hoisted__I64_863;
            Bool hoisted__Bool_864 = I64_eq(_forin_err_kind_856, hoisted__I64_863);
            (void)hoisted__Bool_864;
            Bool hoisted__Bool_865 = not(hoisted__Bool_864);
            (void)hoisted__Bool_865;
            if (hoisted__Bool_865) {
                U32 hoisted__U32_858 = 1;
                (void)hoisted__U32_858;
                Array__Str *_va_Array_25 = Array__Str_new(hoisted__U32_858);
                (void)_va_Array_25;
                U32 hoisted__U32_859 = 0;
                (void)hoisted__U32_859;
                Str hoisted__Str_860 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_860;
                Array__Str_set(_va_Array_25, hoisted__U32_859, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_860; _oa; }));
                Str hoisted__Str_861 = (Str){.c_str = (void *)"./src/core/str.til:19:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_861;
                panic(&hoisted__Str_861, _va_Array_25);
                Str_delete(&hoisted__Str_861, (Bool){0});
            }
            U32 hoisted__U32_866 = 1;
            (void)hoisted__U32_866;
            U32 hoisted__U32_867 = U32_add(_fi_USize_856, hoisted__U32_866);
            (void)hoisted__U32_867;
            _fi_USize_856 = hoisted__U32_867;
            U32 hoisted__U32_868 = Str_len(s);
            (void)hoisted__U32_868;
            U32 hoisted__U32_869 = U32_add(total, hoisted__U32_868);
            (void)hoisted__U32_869;
            total = hoisted__U32_869;
        }
        OutOfBounds_delete(_forin_OutOfBounds_856, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_870 = parts;
        (void)_fc_Array__Str_870;
        (void)_fc_Array__Str_870;
        U32 _fi_USize_870 = 0;
        (void)_fi_USize_870;
        I64 _forin_err_kind_870 = 0;
        (void)_forin_err_kind_870;
        OutOfBounds *_forin_OutOfBounds_870 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_870->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_870;
        while (1) {
            U32 hoisted__U32_876 = Array__Str_len(_fc_Array__Str_870);
            (void)hoisted__U32_876;
            Bool _wcond_Bool_871 = U32_lt(_fi_USize_870, hoisted__U32_876);
            (void)_wcond_Bool_871;
            if (_wcond_Bool_871) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_870, &_fi_USize_870, &_forin_err_kind_870, _forin_OutOfBounds_870);
            I64 hoisted__I64_877 = 0;
            (void)hoisted__I64_877;
            Bool hoisted__Bool_878 = I64_eq(_forin_err_kind_870, hoisted__I64_877);
            (void)hoisted__Bool_878;
            Bool hoisted__Bool_879 = not(hoisted__Bool_878);
            (void)hoisted__Bool_879;
            if (hoisted__Bool_879) {
                U32 hoisted__U32_872 = 1;
                (void)hoisted__U32_872;
                Array__Str *_va_Array_26 = Array__Str_new(hoisted__U32_872);
                (void)_va_Array_26;
                U32 hoisted__U32_873 = 0;
                (void)hoisted__U32_873;
                Str hoisted__Str_874 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_874;
                Array__Str_set(_va_Array_26, hoisted__U32_873, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_874; _oa; }));
                Str hoisted__Str_875 = (Str){.c_str = (void *)"./src/core/str.til:23:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_875;
                panic(&hoisted__Str_875, _va_Array_26);
                Str_delete(&hoisted__Str_875, (Bool){0});
            }
            U32 hoisted__U32_880 = 1;
            (void)hoisted__U32_880;
            U32 hoisted__U32_881 = U32_add(_fi_USize_870, hoisted__U32_880);
            (void)hoisted__U32_881;
            _fi_USize_870 = hoisted__U32_881;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_870, 1);
    }
    Array__Str_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_886 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_886;
    if (hoisted__Bool_886) {
        U32 hoisted__U32_882 = 1;
        (void)hoisted__U32_882;
        Array__Str *_va_Array_27 = Array__Str_new(hoisted__U32_882);
        (void)_va_Array_27;
        U32 hoisted__U32_883 = 0;
        (void)hoisted__U32_883;
        Str hoisted__Str_884 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_884;
        Array__Str_set(_va_Array_27, hoisted__U32_883, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_884; _oa; }));
        Str hoisted__Str_885 = (Str){.c_str = (void *)"./src/core/str.til:43:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_885;
        panic(&hoisted__Str_885, _va_Array_27);
        Str_delete(&hoisted__Str_885, (Bool){0});
    }
    void *hoisted__v_887 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_887;
    (void)hoisted__v_887;
    return hoisted__v_887;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_897 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_897;
    if (hoisted__Bool_897) {
        min_len = b->count;
    }
    {
        U32 _re_U32_889 = U32_clone(&min_len);
        (void)_re_U32_889;
        U32 _rc_U32_889 = 0;
        (void)_rc_U32_889;
        Bool hoisted__Bool_896 = U32_lte(_rc_U32_889, _re_U32_889);
        (void)hoisted__Bool_896;
        if (hoisted__Bool_896) {
            while (1) {
                Bool _wcond_Bool_890 = U32_lt(_rc_U32_889, _re_U32_889);
                (void)_wcond_Bool_890;
                if (_wcond_Bool_890) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_889);
                U32_inc(&_rc_U32_889);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_891 = 0;
                (void)hoisted__I64_891;
                Bool hoisted__Bool_892 = I64_neq(c, hoisted__I64_891);
                (void)hoisted__Bool_892;
                if (hoisted__Bool_892) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_893 = U32_gt(_rc_U32_889, _re_U32_889);
                (void)_wcond_Bool_893;
                if (_wcond_Bool_893) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_889);
                U32_dec(&_rc_U32_889);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_894 = 0;
                (void)hoisted__I64_894;
                Bool hoisted__Bool_895 = I64_neq(c, hoisted__I64_894);
                (void)hoisted__Bool_895;
                if (hoisted__Bool_895) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_898 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_898;
    return hoisted__I64_898;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_900 = 1;
    (void)hoisted__U32_900;
    U32 hoisted__U64_901 = U32_add(n, hoisted__U32_900);
    (void)hoisted__U64_901;
    void * buf = malloc(hoisted__U64_901);
    I32 hoisted__I32_902 = 0;
    (void)hoisted__I32_902;
    U64 hoisted__U64_903 = 1ULL;
    (void)hoisted__U64_903;
    memset(buf, hoisted__I32_902, hoisted__U64_903);
    I64 hoisted__I64_904 = 0;
    (void)hoisted__I64_904;
    Str *hoisted__Str_905 = malloc(sizeof(Str));
    hoisted__Str_905->c_str = buf;
    hoisted__Str_905->count = hoisted__I64_904;
    hoisted__Str_905->cap = n;
    (void)hoisted__Str_905;
    return hoisted__Str_905;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_916 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_916;
    if (hoisted__Bool_916) {
        U32 hoisted__U32_908 = 1;
        (void)hoisted__U32_908;
        Array__Str *_va_Array_28 = Array__Str_new(hoisted__U32_908);
        (void)_va_Array_28;
        U32 hoisted__U32_909 = 0;
        (void)hoisted__U32_909;
        Str hoisted__Str_910 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_910;
        Array__Str_set(_va_Array_28, hoisted__U32_909, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_910; _oa; }));
        Str hoisted__Str_911 = (Str){.c_str = (void *)"./src/core/str.til:92:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_911;
        panic(&hoisted__Str_911, _va_Array_28);
        Str_delete(&hoisted__Str_911, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_917 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_917;
    if (hoisted__Bool_917) {
        U32 hoisted__U32_912 = 1;
        (void)hoisted__U32_912;
        Array__Str *_va_Array_29 = Array__Str_new(hoisted__U32_912);
        (void)_va_Array_29;
        U32 hoisted__U32_913 = 0;
        (void)hoisted__U32_913;
        Str hoisted__Str_914 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_914;
        Array__Str_set(_va_Array_29, hoisted__U32_913, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_914; _oa; }));
        Str hoisted__Str_915 = (Str){.c_str = (void *)"./src/core/str.til:96:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_915;
        panic(&hoisted__Str_915, _va_Array_29);
        Str_delete(&hoisted__Str_915, (Bool){0});
    }
    void *hoisted__v_918 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_918;
    (void)hoisted__v_918;
    memcpy(hoisted__v_918, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_919 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_919;
    (void)hoisted__v_919;
    I32 hoisted__I32_920 = 0;
    (void)hoisted__I32_920;
    U64 hoisted__U64_921 = 1ULL;
    (void)hoisted__U64_921;
    memset(hoisted__v_919, hoisted__I32_920, hoisted__U64_921);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_922 = 1;
    (void)hoisted__U32_922;
    U32 hoisted__U64_923 = U32_add(val->count, hoisted__U32_922);
    (void)hoisted__U64_923;
    void * new_data = malloc(hoisted__U64_923);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_924 = ptr_add(new_data, val->count);
    (void)hoisted__v_924;
    (void)hoisted__v_924;
    I32 hoisted__I32_925 = 0;
    (void)hoisted__I32_925;
    U64 hoisted__U64_926 = 1ULL;
    (void)hoisted__U64_926;
    memset(hoisted__v_924, hoisted__I32_925, hoisted__U64_926);
    Str *hoisted__Str_927 = malloc(sizeof(Str));
    hoisted__Str_927->c_str = new_data;
    hoisted__Str_927->count = val->count;
    hoisted__Str_927->cap = val->count;
    (void)hoisted__Str_927;
    return hoisted__Str_927;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_928 = U32_lt(self->cap, CAP_STATIC);
    (void)hoisted__Bool_928;
    if (hoisted__Bool_928) {
        free(self->c_str);
    }
    Bool hoisted__Bool_929 = U32_neq(self->cap, CAP_STATIC);
    (void)hoisted__Bool_929;
    Bool hoisted__Bool_930 = and(call_free, hoisted__Bool_929);
    (void)hoisted__Bool_930;
    if (hoisted__Bool_930) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_1043 = 0;
    (void)hoisted__U32_1043;
    Bool hoisted__Bool_1044 = U32_eq(self->count, hoisted__U32_1043);
    (void)hoisted__Bool_1044;
    return hoisted__Bool_1044;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1137 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_1137;
    return hoisted__U64_1137;
}

U32 Str_size(void) {
    U32 hoisted__U32_1312 = 16;
    (void)hoisted__U32_1312;
    return hoisted__U32_1312;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1313 = Str_cmp(a, b);
    (void)hoisted__I64_1313;
    I64 hoisted__I64_1314 = 0;
    (void)hoisted__I64_1314;
    Bool hoisted__Bool_1315 = I64_eq(hoisted__I64_1313, hoisted__I64_1314);
    (void)hoisted__Bool_1315;
    return hoisted__Bool_1315;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1407 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1407->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1407;
    return hoisted__OutOfBounds_1407;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1408 = 0;
    (void)hoisted__Bool_1408;
    Str_delete(&self->msg, hoisted__Bool_1408);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1409 = 0;
    (void)hoisted__U32_1409;
    U64 hoisted__U64_1410 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1409); });
    (void)hoisted__U64_1410;
    return hoisted__U64_1410;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1411 = 16;
    (void)hoisted__U32_1411;
    return hoisted__U32_1411;
}

Array__Str * Array__Str_new(U32 cap) {
    Type *hoisted__Type_1417 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1417;
    U32 hoisted__U32_1418 = 16;
    (void)hoisted__U32_1418;
    Type *hoisted__Type_1419 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1419;
    U64 hoisted__U64_1420 = (U64)(cap);
    (void)hoisted__U64_1420;
    Type_delete(hoisted__Type_1417, 1);
    U64 hoisted__U64_1421 = (U64)(hoisted__U32_1418);
    (void)hoisted__U64_1421;
    Type_delete(hoisted__Type_1419, 1);
    void * hoisted__v_1422 = calloc(hoisted__U64_1420, hoisted__U64_1421);
    (void)hoisted__v_1422;
    Array__Str *hoisted__Array__Str_1423 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1423->data = hoisted__v_1422;
    hoisted__Array__Str_1423->cap = cap;
    (void)hoisted__Array__Str_1423;
    return hoisted__Array__Str_1423;
}

U32 Array__Str_len(Array__Str * self) {
    return self->cap;
}

Str * Array__Str_get(Array__Str * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_1445 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_1445;
    if (hoisted__Bool_1445) {
        U32 hoisted__U32_1424 = 6;
        (void)hoisted__U32_1424;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1424);
        (void)_va_Array_39;
        U32 hoisted__U32_1425 = 0;
        (void)hoisted__U32_1425;
        Str hoisted__Str_1426 = (Str){.c_str = (void *)"./src/core/array.til:28:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1426;
        Array__Str_set(_va_Array_39, hoisted__U32_1425, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1426; _oa; }));
        U32 hoisted__U32_1427 = 1;
        (void)hoisted__U32_1427;
        Str hoisted__Str_1428 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1428;
        Array__Str_set(_va_Array_39, hoisted__U32_1427, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1428; _oa; }));
        U32 hoisted__U32_1429 = 2;
        (void)hoisted__U32_1429;
        Str *hoisted__Str_1430 = U32_to_str(DEREF(i));
        (void)hoisted__Str_1430;
        Array__Str_set(_va_Array_39, hoisted__U32_1429, hoisted__Str_1430);
        U32 hoisted__U32_1431 = 3;
        (void)hoisted__U32_1431;
        Str hoisted__Str_1432 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1432;
        Array__Str_set(_va_Array_39, hoisted__U32_1431, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1432; _oa; }));
        U32 hoisted__U32_1433 = 4;
        (void)hoisted__U32_1433;
        Str *hoisted__Str_1434 = U32_to_str(self->cap);
        (void)hoisted__Str_1434;
        Array__Str_set(_va_Array_39, hoisted__U32_1433, hoisted__Str_1434);
        U32 hoisted__U32_1435 = 5;
        (void)hoisted__U32_1435;
        Str hoisted__Str_1436 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1436;
        Array__Str_set(_va_Array_39, hoisted__U32_1435, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1436; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_1437 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_39); hoisted__OutOfBounds_1437->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_1437;
        U32 hoisted__U32_1438 = 16;
        (void)hoisted__U32_1438;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_1437, hoisted__U32_1438);
        OutOfBounds_delete(hoisted__OutOfBounds_1437, 1);
        I64 hoisted__I64_1439 = 3;
        (void)hoisted__I64_1439;
        *_err_kind = hoisted__I64_1439;
    }
    I64 hoisted__I64_1446 = 0;
    (void)hoisted__I64_1446;
    Bool hoisted__Bool_1447 = I64_eq(DEREF(_err_kind), hoisted__I64_1446);
    (void)hoisted__Bool_1447;
    if (hoisted__Bool_1447) {
        U32 hoisted__U32_1440 = 16;
        (void)hoisted__U32_1440;
        U32 hoisted__U32_1441 = U32_mul(DEREF(i), hoisted__U32_1440);
        (void)hoisted__U32_1441;
        Type *hoisted__Type_1442 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
        (void)hoisted__Type_1442;
        U64 hoisted__U64_1443 = (U64)(hoisted__U32_1441);
        (void)hoisted__U64_1443;
        Type_delete(hoisted__Type_1442, 1);
        void *hoisted__v_1444 = ptr_add(self->data, hoisted__U64_1443);
        (void)hoisted__v_1444;
        (void)hoisted__v_1444;
        { Str * _ret_val = hoisted__v_1444;
                return _ret_val; }
    }
    return NULL;
}

void Array__Str_set(Array__Str * self, U32 i, Str * val) {
    Bool hoisted__Bool_1460 = U32_gte(i, self->cap);
    (void)hoisted__Bool_1460;
    if (hoisted__Bool_1460) {
        U32 hoisted__U32_1448 = 5;
        (void)hoisted__U32_1448;
        Array__Str *_va_Array_40 = Array__Str_new(hoisted__U32_1448);
        (void)_va_Array_40;
        U32 hoisted__U32_1449 = 0;
        (void)hoisted__U32_1449;
        Str hoisted__Str_1450 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1450;
        Array__Str_set(_va_Array_40, hoisted__U32_1449, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1450; _oa; }));
        U32 hoisted__U32_1451 = 1;
        (void)hoisted__U32_1451;
        Str *hoisted__Str_1452 = U32_to_str(i);
        (void)hoisted__Str_1452;
        Array__Str_set(_va_Array_40, hoisted__U32_1451, hoisted__Str_1452);
        U32 hoisted__U32_1453 = 2;
        (void)hoisted__U32_1453;
        Str hoisted__Str_1454 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1454;
        Array__Str_set(_va_Array_40, hoisted__U32_1453, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1454; _oa; }));
        U32 hoisted__U32_1455 = 3;
        (void)hoisted__U32_1455;
        Str *hoisted__Str_1456 = U32_to_str(self->cap);
        (void)hoisted__Str_1456;
        Array__Str_set(_va_Array_40, hoisted__U32_1455, hoisted__Str_1456);
        U32 hoisted__U32_1457 = 4;
        (void)hoisted__U32_1457;
        Str hoisted__Str_1458 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1458;
        Array__Str_set(_va_Array_40, hoisted__U32_1457, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1458; _oa; }));
        Str hoisted__Str_1459 = (Str){.c_str = (void *)"./src/core/array.til:37:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1459;
        panic(&hoisted__Str_1459, _va_Array_40);
        Str_delete(&hoisted__Str_1459, (Bool){0});
    }
    U32 hoisted__U32_1461 = 16;
    (void)hoisted__U32_1461;
    U32 hoisted__U32_1462 = U32_mul(i, hoisted__U32_1461);
    (void)hoisted__U32_1462;
    Type *hoisted__Type_1463 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1463;
    U64 hoisted__U64_1464 = (U64)(hoisted__U32_1462);
    (void)hoisted__U64_1464;
    Type_delete(hoisted__Type_1463, 1);
    Str *hoisted__Str_1465 = ptr_add(self->data, hoisted__U64_1464);
    (void)hoisted__Str_1465;
    (void)hoisted__Str_1465;
    Bool hoisted__Bool_1466 = 0;
    (void)hoisted__Bool_1466;
    Str_delete(hoisted__Str_1465, hoisted__Bool_1466);
    U32 hoisted__U32_1467 = 16;
    (void)hoisted__U32_1467;
    U32 hoisted__U32_1468 = U32_mul(i, hoisted__U32_1467);
    (void)hoisted__U32_1468;
    Type *hoisted__Type_1469 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1469;
    U64 hoisted__U64_1470 = (U64)(hoisted__U32_1468);
    (void)hoisted__U64_1470;
    Type_delete(hoisted__Type_1469, 1);
    U32 hoisted__U32_1471 = 16;
    (void)hoisted__U32_1471;
    Type *hoisted__Type_1472 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1472;
    void *hoisted__v_1473 = ptr_add(self->data, hoisted__U64_1470);
    (void)hoisted__v_1473;
    (void)hoisted__v_1473;
    U64 hoisted__U64_1474 = (U64)(hoisted__U32_1471);
    (void)hoisted__U64_1474;
    Type_delete(hoisted__Type_1472, 1);
    memcpy(hoisted__v_1473, val, hoisted__U64_1474);
    U32 hoisted__U32_1475 = 16;
    (void)hoisted__U32_1475;
    Type *hoisted__Type_1476 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1476;
    I32 hoisted__I32_1477 = 0;
    (void)hoisted__I32_1477;
    U64 hoisted__U64_1478 = (U64)(hoisted__U32_1475);
    (void)hoisted__U64_1478;
    Type_delete(hoisted__Type_1476, 1);
    memset(val, hoisted__I32_1477, hoisted__U64_1478);
    Str_delete(val, 1);
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_1479 = self->cap;
        (void)_re_U32_1479;
        U32 _rc_U32_1479 = 0;
        (void)_rc_U32_1479;
        Bool hoisted__Bool_1494 = U32_lte(_rc_U32_1479, _re_U32_1479);
        (void)hoisted__Bool_1494;
        if (hoisted__Bool_1494) {
            while (1) {
                Bool _wcond_Bool_1480 = U32_lt(_rc_U32_1479, _re_U32_1479);
                (void)_wcond_Bool_1480;
                if (_wcond_Bool_1480) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1479);
                U32_inc(&_rc_U32_1479);
                U32 hoisted__U32_1481 = 16;
                (void)hoisted__U32_1481;
                U32 hoisted__U32_1482 = U32_mul(i, hoisted__U32_1481);
                (void)hoisted__U32_1482;
                Type *hoisted__Type_1483 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1483;
                U64 hoisted__U64_1484 = (U64)(hoisted__U32_1482);
                (void)hoisted__U64_1484;
                Type_delete(hoisted__Type_1483, 1);
                Str *hoisted__Str_1485 = ptr_add(self->data, hoisted__U64_1484);
                (void)hoisted__Str_1485;
                (void)hoisted__Str_1485;
                Bool hoisted__Bool_1486 = 0;
                (void)hoisted__Bool_1486;
                Str_delete(hoisted__Str_1485, hoisted__Bool_1486);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1487 = U32_gt(_rc_U32_1479, _re_U32_1479);
                (void)_wcond_Bool_1487;
                if (_wcond_Bool_1487) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1479);
                U32_dec(&_rc_U32_1479);
                U32 hoisted__U32_1488 = 16;
                (void)hoisted__U32_1488;
                U32 hoisted__U32_1489 = U32_mul(i, hoisted__U32_1488);
                (void)hoisted__U32_1489;
                Type *hoisted__Type_1490 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1490;
                U64 hoisted__U64_1491 = (U64)(hoisted__U32_1489);
                (void)hoisted__U64_1491;
                Type_delete(hoisted__Type_1490, 1);
                Str *hoisted__Str_1492 = ptr_add(self->data, hoisted__U64_1491);
                (void)hoisted__Str_1492;
                (void)hoisted__Str_1492;
                Bool hoisted__Bool_1493 = 0;
                (void)hoisted__Bool_1493;
                Str_delete(hoisted__Str_1492, hoisted__Bool_1493);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1531 = 16;
    (void)hoisted__U32_1531;
    U32 hoisted__U32_1532 = U32_mul(self->cap, hoisted__U32_1531);
    (void)hoisted__U32_1532;
    Type *hoisted__Type_1533 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
    (void)hoisted__Type_1533;
    U64 hoisted__U64_1534 = (U64)(hoisted__U32_1532);
    (void)hoisted__U64_1534;
    Type_delete(hoisted__Type_1533, 1);
    void * new_data = malloc(hoisted__U64_1534);
    {
        U32 _re_U32_1495 = self->cap;
        (void)_re_U32_1495;
        U32 _rc_U32_1495 = 0;
        (void)_rc_U32_1495;
        Bool hoisted__Bool_1530 = U32_lte(_rc_U32_1495, _re_U32_1495);
        (void)hoisted__Bool_1530;
        if (hoisted__Bool_1530) {
            while (1) {
                Bool _wcond_Bool_1496 = U32_lt(_rc_U32_1495, _re_U32_1495);
                (void)_wcond_Bool_1496;
                if (_wcond_Bool_1496) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1495);
                U32_inc(&_rc_U32_1495);
                U32 hoisted__U32_1497 = 16;
                (void)hoisted__U32_1497;
                U32 hoisted__U32_1498 = U32_mul(i, hoisted__U32_1497);
                (void)hoisted__U32_1498;
                Type *hoisted__Type_1499 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1499;
                U64 hoisted__U64_1500 = (U64)(hoisted__U32_1498);
                (void)hoisted__U64_1500;
                Type_delete(hoisted__Type_1499, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1500);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1501 = 16;
                (void)hoisted__U32_1501;
                U32 hoisted__U32_1502 = U32_mul(i, hoisted__U32_1501);
                (void)hoisted__U32_1502;
                Type *hoisted__Type_1503 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1503;
                U64 hoisted__U64_1504 = (U64)(hoisted__U32_1502);
                (void)hoisted__U64_1504;
                Type_delete(hoisted__Type_1503, 1);
                U32 hoisted__U32_1505 = 16;
                (void)hoisted__U32_1505;
                Type *hoisted__Type_1506 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1506;
                void *hoisted__v_1507 = ptr_add(new_data, hoisted__U64_1504);
                (void)hoisted__v_1507;
                (void)hoisted__v_1507;
                U64 hoisted__U64_1508 = (U64)(hoisted__U32_1505);
                (void)hoisted__U64_1508;
                Type_delete(hoisted__Type_1506, 1);
                memcpy(hoisted__v_1507, cloned, hoisted__U64_1508);
                U32 hoisted__U32_1509 = 16;
                (void)hoisted__U32_1509;
                Type *hoisted__Type_1510 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1510;
                I32 hoisted__I32_1511 = 0;
                (void)hoisted__I32_1511;
                U64 hoisted__U64_1512 = (U64)(hoisted__U32_1509);
                (void)hoisted__U64_1512;
                Type_delete(hoisted__Type_1510, 1);
                memset(cloned, hoisted__I32_1511, hoisted__U64_1512);
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1513 = U32_gt(_rc_U32_1495, _re_U32_1495);
                (void)_wcond_Bool_1513;
                if (_wcond_Bool_1513) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_1495);
                U32_dec(&_rc_U32_1495);
                U32 hoisted__U32_1514 = 16;
                (void)hoisted__U32_1514;
                U32 hoisted__U32_1515 = U32_mul(i, hoisted__U32_1514);
                (void)hoisted__U32_1515;
                Type *hoisted__Type_1516 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1516;
                U64 hoisted__U64_1517 = (U64)(hoisted__U32_1515);
                (void)hoisted__U64_1517;
                Type_delete(hoisted__Type_1516, 1);
                Str *src = ptr_add(self->data, hoisted__U64_1517);
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1518 = 16;
                (void)hoisted__U32_1518;
                U32 hoisted__U32_1519 = U32_mul(i, hoisted__U32_1518);
                (void)hoisted__U32_1519;
                Type *hoisted__Type_1520 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1520;
                U64 hoisted__U64_1521 = (U64)(hoisted__U32_1519);
                (void)hoisted__U64_1521;
                Type_delete(hoisted__Type_1520, 1);
                U32 hoisted__U32_1522 = 16;
                (void)hoisted__U32_1522;
                Type *hoisted__Type_1523 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1523;
                void *hoisted__v_1524 = ptr_add(new_data, hoisted__U64_1521);
                (void)hoisted__v_1524;
                (void)hoisted__v_1524;
                U64 hoisted__U64_1525 = (U64)(hoisted__U32_1522);
                (void)hoisted__U64_1525;
                Type_delete(hoisted__Type_1523, 1);
                memcpy(hoisted__v_1524, cloned, hoisted__U64_1525);
                U32 hoisted__U32_1526 = 16;
                (void)hoisted__U32_1526;
                Type *hoisted__Type_1527 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = (Primitive){.tag = Primitive_TAG_U64}; _oa; }));
                (void)hoisted__Type_1527;
                I32 hoisted__I32_1528 = 0;
                (void)hoisted__I32_1528;
                U64 hoisted__U64_1529 = (U64)(hoisted__U32_1526);
                (void)hoisted__U64_1529;
                Type_delete(hoisted__Type_1527, 1);
                memset(cloned, hoisted__I32_1528, hoisted__U64_1529);
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1535 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1535->data = new_data;
    hoisted__Array__Str_1535->cap = self->cap;
    (void)hoisted__Array__Str_1535;
    return hoisted__Array__Str_1535;
}

U32 Array__Str_size(void) {
    U32 hoisted__U32_1536 = 16;
    (void)hoisted__U32_1536;
    return hoisted__U32_1536;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1540 = 8;
    (void)hoisted__U32_1540;
    return hoisted__U32_1540;
}

void * Dynamic_clone(void * self) {
    return self;
}

void Dynamic_delete(void * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void * default_clone(void * v) {
    return v;
}
static void * default_clone__til_closure_call(void *til_env, void * v) {
    (void)til_env;
    return default_clone(v);
}
static __attribute__((unused)) TilClosure default_clone__til_closure = { (void *)default_clone__til_closure_call, NULL, NULL };

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}
static void default_delete__til_closure_call(void *til_env, void * _v, Bool _cf) {
    (void)til_env;
    default_delete(_v, _cf);
}
static __attribute__((unused)) TilClosure default_delete__til_closure = { (void *)default_delete__til_closure_call, NULL, NULL };

I64 default_cmp(void * _a, void * _b) {
    (void)_a;
    (void)_b;
    I64 hoisted__I64_1541 = 0;
    (void)hoisted__I64_1541;
    return hoisted__I64_1541;
}
static I64 default_cmp__til_closure_call(void *til_env, void * _a, void * _b) {
    (void)til_env;
    return default_cmp(_a, _b);
}
static __attribute__((unused)) TilClosure default_cmp__til_closure = { (void *)default_cmp__til_closure_call, NULL, NULL };

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1735 = 0;
    (void)hoisted__I64_1735;
    Bool hoisted__Bool_1736 = I64_eq(val, hoisted__I64_1735);
    (void)hoisted__Bool_1736;
    if (hoisted__Bool_1736) {
        U64 hoisted__U64_1699 = 2ULL;
        (void)hoisted__U64_1699;
        void * buf = malloc(hoisted__U64_1699);
        I64 hoisted__I64_1700 = 48;
        (void)hoisted__I64_1700;
        U64 hoisted__U64_1701 = 1ULL;
        (void)hoisted__U64_1701;
        memcpy(buf, &hoisted__I64_1700, hoisted__U64_1701);
        U64 hoisted__U64_1702 = 1ULL;
        (void)hoisted__U64_1702;
        void *hoisted__v_1703 = ptr_add(buf, hoisted__U64_1702);
        (void)hoisted__v_1703;
        (void)hoisted__v_1703;
        I32 hoisted__I32_1704 = 0;
        (void)hoisted__I32_1704;
        U64 hoisted__U64_1705 = 1ULL;
        (void)hoisted__U64_1705;
        memset(hoisted__v_1703, hoisted__I32_1704, hoisted__U64_1705);
        I64 hoisted__I64_1706 = 1;
        (void)hoisted__I64_1706;
        I64 hoisted__I64_1707 = 1;
        (void)hoisted__I64_1707;
        Str *hoisted__Str_1708 = malloc(sizeof(Str));
        hoisted__Str_1708->c_str = buf;
        hoisted__Str_1708->count = hoisted__I64_1706;
        hoisted__Str_1708->cap = hoisted__I64_1707;
        (void)hoisted__Str_1708;
        { Str * _ret_val = hoisted__Str_1708;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1737 = 0;
    (void)hoisted__I64_1737;
    Bool hoisted__Bool_1738 = I64_lt(val, hoisted__I64_1737);
    (void)hoisted__Bool_1738;
    if (hoisted__Bool_1738) {
        Bool hoisted__Bool_1709 = 1;
        (void)hoisted__Bool_1709;
        is_neg = hoisted__Bool_1709;
        I64 hoisted__I64_1710 = 0;
        (void)hoisted__I64_1710;
        I64 hoisted__I64_1711 = I64_sub(hoisted__I64_1710, val);
        (void)hoisted__I64_1711;
        v = hoisted__I64_1711;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1713 = 0;
        (void)hoisted__I64_1713;
        Bool _wcond_Bool_1712 = I64_gt(tmp, hoisted__I64_1713);
        (void)_wcond_Bool_1712;
        if (_wcond_Bool_1712) {
        } else {
            break;
        }
        U64 hoisted__U64_1714 = 1ULL;
        (void)hoisted__U64_1714;
        U64 hoisted__U64_1715 = U64_add(ndigits, hoisted__U64_1714);
        (void)hoisted__U64_1715;
        ndigits = hoisted__U64_1715;
        I64 hoisted__I64_1716 = 10;
        (void)hoisted__I64_1716;
        I64 hoisted__I64_1717 = I64_div(tmp, hoisted__I64_1716);
        (void)hoisted__I64_1717;
        tmp = hoisted__I64_1717;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1718 = 1ULL;
        (void)hoisted__U64_1718;
        U64 hoisted__U64_1719 = U64_add(total, hoisted__U64_1718);
        (void)hoisted__U64_1719;
        total = hoisted__U64_1719;
    }
    U64 hoisted__U64_1739 = 1ULL;
    (void)hoisted__U64_1739;
    U64 hoisted__U64_1740 = U64_add(total, hoisted__U64_1739);
    (void)hoisted__U64_1740;
    void * buf = malloc(hoisted__U64_1740);
    if (is_neg) {
        I64 hoisted__I64_1720 = 45;
        (void)hoisted__I64_1720;
        U64 hoisted__U64_1721 = 1ULL;
        (void)hoisted__U64_1721;
        memcpy(buf, &hoisted__I64_1720, hoisted__U64_1721);
    }
    U64 hoisted__U64_1741 = 1ULL;
    (void)hoisted__U64_1741;
    U64 i = U64_sub(total, hoisted__U64_1741);
    while (1) {
        I64 hoisted__I64_1723 = 0;
        (void)hoisted__I64_1723;
        Bool _wcond_Bool_1722 = I64_gt(v, hoisted__I64_1723);
        (void)_wcond_Bool_1722;
        if (_wcond_Bool_1722) {
        } else {
            break;
        }
        I64 hoisted__I64_1724 = 10;
        (void)hoisted__I64_1724;
        I64 hoisted__I64_1725 = I64_mod(v, hoisted__I64_1724);
        (void)hoisted__I64_1725;
        I64 hoisted__I64_1726 = 48;
        (void)hoisted__I64_1726;
        I64 hoisted__I64_1727 = I64_add(hoisted__I64_1725, hoisted__I64_1726);
        (void)hoisted__I64_1727;
        void *hoisted__v_1728 = ptr_add(buf, i);
        (void)hoisted__v_1728;
        (void)hoisted__v_1728;
        U8 hoisted__U8_1729 = I64_to_u8(hoisted__I64_1727);
        (void)hoisted__U8_1729;
        U64 hoisted__U64_1730 = 1ULL;
        (void)hoisted__U64_1730;
        memcpy(hoisted__v_1728, &hoisted__U8_1729, hoisted__U64_1730);
        I64 hoisted__I64_1731 = 10;
        (void)hoisted__I64_1731;
        I64 hoisted__I64_1732 = I64_div(v, hoisted__I64_1731);
        (void)hoisted__I64_1732;
        v = hoisted__I64_1732;
        U64 hoisted__U64_1733 = 1ULL;
        (void)hoisted__U64_1733;
        U64 hoisted__U64_1734 = U64_sub(i, hoisted__U64_1733);
        (void)hoisted__U64_1734;
        i = hoisted__U64_1734;
    }
    void *hoisted__v_1742 = ptr_add(buf, total);
    (void)hoisted__v_1742;
    (void)hoisted__v_1742;
    I32 hoisted__I32_1743 = 0;
    (void)hoisted__I32_1743;
    U64 hoisted__U64_1744 = 1ULL;
    (void)hoisted__U64_1744;
    memset(hoisted__v_1742, hoisted__I32_1743, hoisted__U64_1744);
    Str *hoisted__Str_1745 = malloc(sizeof(Str));
    hoisted__Str_1745->c_str = buf;
    hoisted__Str_1745->count = total;
    hoisted__Str_1745->cap = total;
    (void)hoisted__Str_1745;
    return hoisted__Str_1745;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1765 = 8;
    (void)hoisted__U32_1765;
    return hoisted__U32_1765;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1886 = 0;
    (void)hoisted__U32_1886;
    U64 hoisted__U64_1887 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1886); });
    (void)hoisted__U64_1887;
    return hoisted__U64_1887;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1890 = I64_cmp(a, b);
    (void)hoisted__I64_1890;
    I64 hoisted__I64_1891 = -1;
    (void)hoisted__I64_1891;
    Bool hoisted__Bool_1892 = I64_eq(hoisted__I64_1890, hoisted__I64_1891);
    (void)hoisted__Bool_1892;
    return hoisted__Bool_1892;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1893 = I64_cmp(a, b);
    (void)hoisted__I64_1893;
    I64 hoisted__I64_1894 = 1;
    (void)hoisted__I64_1894;
    Bool hoisted__Bool_1895 = I64_eq(hoisted__I64_1893, hoisted__I64_1894);
    (void)hoisted__Bool_1895;
    return hoisted__Bool_1895;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1896 = I64_eq(a, b);
    (void)hoisted__Bool_1896;
    Bool hoisted__Bool_1897 = not(hoisted__Bool_1896);
    (void)hoisted__Bool_1897;
    return hoisted__Bool_1897;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1915 = Bool_eq(a, b);
    (void)hoisted__Bool_1915;
    if (hoisted__Bool_1915) {
        I64 hoisted__I64_1913 = 0;
        (void)hoisted__I64_1913;
        { I64 _ret_val = hoisted__I64_1913;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1914 = -1;
        (void)hoisted__I64_1914;
        return hoisted__I64_1914;
    }
    I64 hoisted__I64_1916 = 1;
    (void)hoisted__I64_1916;
    return hoisted__I64_1916;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1917 = 1;
    (void)hoisted__U32_1917;
    return hoisted__U32_1917;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1918 = 0;
    (void)hoisted__U32_1918;
    U64 hoisted__U64_1919 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1918); });
    (void)hoisted__U64_1919;
    return hoisted__U64_1919;
}

Map * Map_new_type_names(Str * key_type, Str * val_type) {
    Bool hoisted__Bool_1950 = Str_is_empty(key_type);
    (void)hoisted__Bool_1950;
    if (hoisted__Bool_1950) {
        U32 hoisted__U32_1934 = 1;
        (void)hoisted__U32_1934;
        Array__Str *_va_Array_51 = Array__Str_new(hoisted__U32_1934);
        (void)_va_Array_51;
        U32 hoisted__U32_1935 = 0;
        (void)hoisted__U32_1935;
        Str hoisted__Str_1936 = (Str){.c_str = (void *)"Map.new: key_type required", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1936;
        Array__Str_set(_va_Array_51, hoisted__U32_1935, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1936; _oa; }));
        Str hoisted__Str_1937 = (Str){.c_str = (void *)"./src/core/map.til:18:40", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1937;
        panic(&hoisted__Str_1937, _va_Array_51);
        Str_delete(&hoisted__Str_1937, (Bool){0});
    }
    Bool hoisted__Bool_1951 = dyn_has_cmp(key_type);
    (void)hoisted__Bool_1951;
    Bool hoisted__Bool_1952 = not(hoisted__Bool_1951);
    (void)hoisted__Bool_1952;
    if (hoisted__Bool_1952) {
        U32 hoisted__U32_1938 = 3;
        (void)hoisted__U32_1938;
        Array__Str *_va_Array_52 = Array__Str_new(hoisted__U32_1938);
        (void)_va_Array_52;
        U32 hoisted__U32_1939 = 0;
        (void)hoisted__U32_1939;
        Str hoisted__Str_1940 = (Str){.c_str = (void *)"Map.new: type ", .count = 14ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1940;
        Array__Str_set(_va_Array_52, hoisted__U32_1939, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1940; _oa; }));
        U32 hoisted__U32_1941 = 1;
        (void)hoisted__U32_1941;
        Str *hoisted__Str_1942 = Str_clone(key_type);
        (void)hoisted__Str_1942;
        Array__Str_set(_va_Array_52, hoisted__U32_1941, hoisted__Str_1942);
        U32 hoisted__U32_1943 = 2;
        (void)hoisted__U32_1943;
        Str hoisted__Str_1944 = (Str){.c_str = (void *)" must implement cmp", .count = 19ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1944;
        Array__Str_set(_va_Array_52, hoisted__U32_1943, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1944; _oa; }));
        Str hoisted__Str_1945 = (Str){.c_str = (void *)"./src/core/map.til:20:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1945;
        panic(&hoisted__Str_1945, _va_Array_52);
        Str_delete(&hoisted__Str_1945, (Bool){0});
    }
    Bool hoisted__Bool_1953 = Str_is_empty(val_type);
    (void)hoisted__Bool_1953;
    if (hoisted__Bool_1953) {
        U32 hoisted__U32_1946 = 1;
        (void)hoisted__U32_1946;
        Array__Str *_va_Array_53 = Array__Str_new(hoisted__U32_1946);
        (void)_va_Array_53;
        U32 hoisted__U32_1947 = 0;
        (void)hoisted__U32_1947;
        Str hoisted__Str_1948 = (Str){.c_str = (void *)"Map.new: val_type required", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1948;
        Array__Str_set(_va_Array_53, hoisted__U32_1947, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_1948; _oa; }));
        Str hoisted__Str_1949 = (Str){.c_str = (void *)"./src/core/map.til:23:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_1949;
        panic(&hoisted__Str_1949, _va_Array_53);
        Str_delete(&hoisted__Str_1949, (Bool){0});
    }
    Map *m = malloc(sizeof(Map));
    { Vec *_ca = Vec_new(&(Type){.tag = Type_TAG_Dynamic}); m->keys = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(&(Type){.tag = Type_TAG_Dynamic}); m->values = *_ca; free(_ca); }
    m->key_cmp = (void *)&default_cmp__til_closure;
    { Vec _old = m->keys;
    { Vec *_fa = Vec_new_type_name(key_type); m->keys = *_fa; free(_fa); }
    Vec_delete(&_old, (Bool){0}); }
    { Vec _old = m->values;
    { Vec *_fa = Vec_new_type_name(val_type); m->values = *_fa; free(_fa); }
    Vec_delete(&_old, (Bool){0}); }
    void * hoisted__v_1954 = dyn_fn(key_type, &(Str){.c_str=(void*)"cmp", .count=3ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_1954;
    m->key_cmp = hoisted__v_1954;
    return m;
}

Map * Map_new(Type * K, Type * V) {
    Str *key_type = dyn_type_to_str(K);
    Str *val_type = dyn_type_to_str(V);
    Map *hoisted__Map_1955 = Map_new_type_names(key_type, val_type);
    (void)hoisted__Map_1955;
    Str_delete(key_type, 1);
    Str_delete(val_type, 1);
    return hoisted__Map_1955;
}

void Map_clear(Map * self) {
    Vec_clear(&self->keys);
    Vec_clear(&self->values);
}

void Map_delete(Map * self, Bool call_free) {
    Map_clear(self);
    Bool hoisted__Bool_2050 = 0;
    (void)hoisted__Bool_2050;
    Vec_delete(&self->keys, hoisted__Bool_2050);
    Bool hoisted__Bool_2051 = 0;
    (void)hoisted__Bool_2051;
    Vec_delete(&self->values, hoisted__Bool_2051);
    if (call_free) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    Map *hoisted__Map_2052 = malloc(sizeof(Map));
    { Vec *_ca = Vec_clone(&self->keys); hoisted__Map_2052->keys = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->values); hoisted__Map_2052->values = *_ca; free(_ca); }
    hoisted__Map_2052->key_cmp = (void *)self->key_cmp;
    (void)hoisted__Map_2052;
    return hoisted__Map_2052;
}

U64 Map_hash(Map * self, HashFn hasher) {
    U32 hoisted__U32_2053 = 0;
    (void)hoisted__U32_2053;
    U64 hoisted__U64_2054 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Map *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2053); });
    (void)hoisted__U64_2054;
    return hoisted__U64_2054;
}

U32 Map_size(void) {
    U32 hoisted__U32_2055 = 88;
    (void)hoisted__U32_2055;
    return hoisted__U32_2055;
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
    Bool hoisted__Bool_2067 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2067;
    if (hoisted__Bool_2067) {
        Bool hoisted__Bool_2057 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_2057;
        { Bool _ret_val = hoisted__Bool_2057;
                return _ret_val; }
    }
    Bool hoisted__Bool_2068 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2068;
    if (hoisted__Bool_2068) {
        Bool hoisted__Bool_2058 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_2058;
        { Bool _ret_val = hoisted__Bool_2058;
                return _ret_val; }
    }
    Bool hoisted__Bool_2069 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2069;
    if (hoisted__Bool_2069) {
        Bool hoisted__Bool_2059 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_2059;
        { Bool _ret_val = hoisted__Bool_2059;
                return _ret_val; }
    }
    Bool hoisted__Bool_2070 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2070;
    if (hoisted__Bool_2070) {
        Bool hoisted__Bool_2060 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_2060;
        { Bool _ret_val = hoisted__Bool_2060;
                return _ret_val; }
    }
    Bool hoisted__Bool_2071 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2071;
    if (hoisted__Bool_2071) {
        Bool hoisted__Bool_2061 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_2061;
        { Bool _ret_val = hoisted__Bool_2061;
                return _ret_val; }
    }
    Bool hoisted__Bool_2072 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2072;
    if (hoisted__Bool_2072) {
        Bool hoisted__Bool_2062 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_2062;
        { Bool _ret_val = hoisted__Bool_2062;
                return _ret_val; }
    }
    Bool hoisted__Bool_2073 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2073;
    if (hoisted__Bool_2073) {
        Bool hoisted__Bool_2063 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_2063;
        { Bool _ret_val = hoisted__Bool_2063;
                return _ret_val; }
    }
    Bool hoisted__Bool_2074 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2074;
    if (hoisted__Bool_2074) {
        Bool hoisted__Bool_2064 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_2064;
        { Bool _ret_val = hoisted__Bool_2064;
                return _ret_val; }
    }
    Bool hoisted__Bool_2075 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2075;
    if (hoisted__Bool_2075) {
        Bool hoisted__Bool_2065 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_2065;
        { Bool _ret_val = hoisted__Bool_2065;
                return _ret_val; }
    }
    Bool hoisted__Bool_2076 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2076;
    if (hoisted__Bool_2076) {
        Bool hoisted__Bool_2066 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_2066;
        { Bool _ret_val = hoisted__Bool_2066;
                return _ret_val; }
    }
    Bool hoisted__Bool_2077 = 0;
    (void)hoisted__Bool_2077;
    return hoisted__Bool_2077;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_2099 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_2099;
    if (hoisted__Bool_2099) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_2100 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_2100;
    if (hoisted__Bool_2100) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_2101 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_2101;
    if (hoisted__Bool_2101) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_2102 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_2102;
    if (hoisted__Bool_2102) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2103 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_2103;
    if (hoisted__Bool_2103) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2104 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_2104;
    if (hoisted__Bool_2104) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2105 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_2105;
    if (hoisted__Bool_2105) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2106 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_2106;
    if (hoisted__Bool_2106) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2107 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_2107;
    if (hoisted__Bool_2107) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2108 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_2108;
    if (hoisted__Bool_2108) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_2109 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2109;
    UNREACHABLE(&hoisted__Str_2109);
    Str_delete(&hoisted__Str_2109, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_2110 = 4;
    (void)hoisted__U32_2110;
    return hoisted__U32_2110;
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
    Bool hoisted__Bool_2162 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2162;
    if (hoisted__Bool_2162) {
        Str *hoisted__Str_2152 = get_payload(self);
        (void)hoisted__Str_2152;
        (void)hoisted__Str_2152;
        Bool hoisted__Bool_2153 = 0;
        (void)hoisted__Bool_2153;
        Str_delete(hoisted__Str_2152, hoisted__Bool_2153);
    }
    Bool hoisted__Bool_2163 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2163;
    if (hoisted__Bool_2163) {
        Str *hoisted__Str_2154 = get_payload(self);
        (void)hoisted__Str_2154;
        (void)hoisted__Str_2154;
        Bool hoisted__Bool_2155 = 0;
        (void)hoisted__Bool_2155;
        Str_delete(hoisted__Str_2154, hoisted__Bool_2155);
    }
    Bool hoisted__Bool_2164 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2164;
    if (hoisted__Bool_2164) {
        Str *hoisted__Str_2156 = get_payload(self);
        (void)hoisted__Str_2156;
        (void)hoisted__Str_2156;
        Bool hoisted__Bool_2157 = 0;
        (void)hoisted__Bool_2157;
        Str_delete(hoisted__Str_2156, hoisted__Bool_2157);
    }
    Bool hoisted__Bool_2165 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2165;
    if (hoisted__Bool_2165) {
        Primitive *hoisted__Primitive_2158 = get_payload(self);
        (void)hoisted__Primitive_2158;
        (void)hoisted__Primitive_2158;
        Bool hoisted__Bool_2159 = 0;
        (void)hoisted__Bool_2159;
        Primitive_delete(hoisted__Primitive_2158, hoisted__Bool_2159);
    }
    Bool hoisted__Bool_2166 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2166;
    if (hoisted__Bool_2166) {
        Str *hoisted__Str_2160 = get_payload(self);
        (void)hoisted__Str_2160;
        (void)hoisted__Str_2160;
        Bool hoisted__Bool_2161 = 0;
        (void)hoisted__Bool_2161;
        Str_delete(hoisted__Str_2160, hoisted__Bool_2161);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2235 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2235;
    if (hoisted__Bool_2235) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2236 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2236;
    if (hoisted__Bool_2236) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2237 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2237;
    if (hoisted__Bool_2237) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2227 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2227;
        Type *hoisted__Type_2228 = Type_Struct(hoisted__Str_2227);
        (void)hoisted__Type_2228;
        { Type * _ret_val = hoisted__Type_2228;
                return _ret_val; }
    }
    Bool hoisted__Bool_2238 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2238;
    if (hoisted__Bool_2238) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2239 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2239;
    if (hoisted__Bool_2239) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2229 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2229;
        Type *hoisted__Type_2230 = Type_Enum(hoisted__Str_2229);
        (void)hoisted__Type_2230;
        { Type * _ret_val = hoisted__Type_2230;
                return _ret_val; }
    }
    Bool hoisted__Bool_2240 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2240;
    if (hoisted__Bool_2240) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2241 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2241;
    if (hoisted__Bool_2241) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2242 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2242;
    if (hoisted__Bool_2242) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2243 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2243;
    if (hoisted__Bool_2243) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2244 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2244;
    if (hoisted__Bool_2244) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2231 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2231;
        Type *hoisted__Type_2232 = Type_Custom(hoisted__Str_2231);
        (void)hoisted__Type_2232;
        { Type * _ret_val = hoisted__Type_2232;
                return _ret_val; }
    }
    Bool hoisted__Bool_2245 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2245;
    if (hoisted__Bool_2245) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2233 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2233;
        Type *hoisted__Type_2234 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2233; _oa; }));
        (void)hoisted__Type_2234;
        { Type * _ret_val = hoisted__Type_2234;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2246 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2246;
    Type *hoisted__Type_2247 = Type_FuncPtrSig(hoisted__Str_2246);
    (void)hoisted__Type_2247;
    return hoisted__Type_2247;
}

U32 Type_size(void) {
    U32 hoisted__U32_2248 = 24;
    (void)hoisted__U32_2248;
    return hoisted__U32_2248;
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
    Bool hoisted__Bool_2347 = is(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2347;
    if (hoisted__Bool_2347) {
        Bool hoisted__Bool_2339 = is(other, &(FuncType){.tag = FuncType_TAG_Func});
        (void)hoisted__Bool_2339;
        { Bool _ret_val = hoisted__Bool_2339;
                return _ret_val; }
    }
    Bool hoisted__Bool_2348 = is(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2348;
    if (hoisted__Bool_2348) {
        Bool hoisted__Bool_2340 = is(other, &(FuncType){.tag = FuncType_TAG_Proc});
        (void)hoisted__Bool_2340;
        { Bool _ret_val = hoisted__Bool_2340;
                return _ret_val; }
    }
    Bool hoisted__Bool_2349 = is(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2349;
    if (hoisted__Bool_2349) {
        Bool hoisted__Bool_2341 = is(other, &(FuncType){.tag = FuncType_TAG_Test});
        (void)hoisted__Bool_2341;
        { Bool _ret_val = hoisted__Bool_2341;
                return _ret_val; }
    }
    Bool hoisted__Bool_2350 = is(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2350;
    if (hoisted__Bool_2350) {
        Bool hoisted__Bool_2342 = is(other, &(FuncType){.tag = FuncType_TAG_Macro});
        (void)hoisted__Bool_2342;
        { Bool _ret_val = hoisted__Bool_2342;
                return _ret_val; }
    }
    Bool hoisted__Bool_2351 = is(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2351;
    if (hoisted__Bool_2351) {
        Bool hoisted__Bool_2343 = is(other, &(FuncType){.tag = FuncType_TAG_ExtFunc});
        (void)hoisted__Bool_2343;
        { Bool _ret_val = hoisted__Bool_2343;
                return _ret_val; }
    }
    Bool hoisted__Bool_2352 = is(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2352;
    if (hoisted__Bool_2352) {
        Bool hoisted__Bool_2344 = is(other, &(FuncType){.tag = FuncType_TAG_ExtProc});
        (void)hoisted__Bool_2344;
        { Bool _ret_val = hoisted__Bool_2344;
                return _ret_val; }
    }
    Bool hoisted__Bool_2353 = is(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2353;
    if (hoisted__Bool_2353) {
        Bool hoisted__Bool_2345 = is(other, &(FuncType){.tag = FuncType_TAG_LazyFunc});
        (void)hoisted__Bool_2345;
        { Bool _ret_val = hoisted__Bool_2345;
                return _ret_val; }
    }
    Bool hoisted__Bool_2354 = is(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2354;
    if (hoisted__Bool_2354) {
        Bool hoisted__Bool_2346 = is(other, &(FuncType){.tag = FuncType_TAG_LazyProc});
        (void)hoisted__Bool_2346;
        { Bool _ret_val = hoisted__Bool_2346;
                return _ret_val; }
    }
    Bool hoisted__Bool_2355 = 0;
    (void)hoisted__Bool_2355;
    return hoisted__Bool_2355;
}

void FuncType_delete(FuncType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

FuncType * FuncType_clone(FuncType * self) {
    Bool hoisted__Bool_2373 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Func});
    (void)hoisted__Bool_2373;
    if (hoisted__Bool_2373) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
                return _r; }
    }
    Bool hoisted__Bool_2374 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Proc});
    (void)hoisted__Bool_2374;
    if (hoisted__Bool_2374) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Proc;
                return _r; }
    }
    Bool hoisted__Bool_2375 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Test});
    (void)hoisted__Bool_2375;
    if (hoisted__Bool_2375) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Test;
                return _r; }
    }
    Bool hoisted__Bool_2376 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_Macro});
    (void)hoisted__Bool_2376;
    if (hoisted__Bool_2376) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Macro;
                return _r; }
    }
    Bool hoisted__Bool_2377 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtFunc});
    (void)hoisted__Bool_2377;
    if (hoisted__Bool_2377) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtFunc;
                return _r; }
    }
    Bool hoisted__Bool_2378 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_ExtProc});
    (void)hoisted__Bool_2378;
    if (hoisted__Bool_2378) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_ExtProc;
                return _r; }
    }
    Bool hoisted__Bool_2379 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyFunc});
    (void)hoisted__Bool_2379;
    if (hoisted__Bool_2379) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyFunc;
                return _r; }
    }
    Bool hoisted__Bool_2380 = FuncType_eq(self, &(FuncType){.tag = FuncType_TAG_LazyProc});
    (void)hoisted__Bool_2380;
    if (hoisted__Bool_2380) {
        { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_LazyProc;
                return _r; }
    }
    Str hoisted__Str_2381 = (Str){.c_str = (void *)"FuncType.clone:129:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2381;
    UNREACHABLE(&hoisted__Str_2381);
    Str_delete(&hoisted__Str_2381, (Bool){0});
    { FuncType *_r = malloc(sizeof(FuncType)); _r->tag = FuncType_TAG_Func;
    return _r; }
}

U32 FuncType_size(void) {
    U32 hoisted__U32_2382 = 4;
    (void)hoisted__U32_2382;
    return hoisted__U32_2382;
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
    Bool hoisted__Bool_2387 = is(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2387;
    if (hoisted__Bool_2387) {
        Bool hoisted__Bool_2384 = is(other, &(OwnType){.tag = OwnType_TAG_Own});
        (void)hoisted__Bool_2384;
        { Bool _ret_val = hoisted__Bool_2384;
                return _ret_val; }
    }
    Bool hoisted__Bool_2388 = is(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2388;
    if (hoisted__Bool_2388) {
        Bool hoisted__Bool_2385 = is(other, &(OwnType){.tag = OwnType_TAG_Ref});
        (void)hoisted__Bool_2385;
        { Bool _ret_val = hoisted__Bool_2385;
                return _ret_val; }
    }
    Bool hoisted__Bool_2389 = is(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2389;
    if (hoisted__Bool_2389) {
        Bool hoisted__Bool_2386 = is(other, &(OwnType){.tag = OwnType_TAG_Shallow});
        (void)hoisted__Bool_2386;
        { Bool _ret_val = hoisted__Bool_2386;
                return _ret_val; }
    }
    Bool hoisted__Bool_2390 = 0;
    (void)hoisted__Bool_2390;
    return hoisted__Bool_2390;
}

void OwnType_delete(OwnType * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

OwnType * OwnType_clone(OwnType * self) {
    Bool hoisted__Bool_2398 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Own});
    (void)hoisted__Bool_2398;
    if (hoisted__Bool_2398) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
                return _r; }
    }
    Bool hoisted__Bool_2399 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Ref});
    (void)hoisted__Bool_2399;
    if (hoisted__Bool_2399) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Ref;
                return _r; }
    }
    Bool hoisted__Bool_2400 = OwnType_eq(self, &(OwnType){.tag = OwnType_TAG_Shallow});
    (void)hoisted__Bool_2400;
    if (hoisted__Bool_2400) {
        { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Shallow;
                return _r; }
    }
    Str hoisted__Str_2401 = (Str){.c_str = (void *)"OwnType.clone:134:1", .count = 19ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_2401;
    UNREACHABLE(&hoisted__Str_2401);
    Str_delete(&hoisted__Str_2401, (Bool){0});
    { OwnType *_r = malloc(sizeof(OwnType)); _r->tag = OwnType_TAG_Own;
    return _r; }
}

U32 OwnType_size(void) {
    U32 hoisted__U32_2402 = 4;
    (void)hoisted__U32_2402;
    return hoisted__U32_2402;
}


Declaration * Declaration_clone(Declaration * self) {
    Expr *hoisted__Expr_2404 = Expr_clone(self->default_value);
    (void)hoisted__Expr_2404;
    Declaration *hoisted__Declaration_2405 = malloc(sizeof(Declaration));
    { Str *_ca = Str_clone(&self->name); hoisted__Declaration_2405->name = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->doc); hoisted__Declaration_2405->doc = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->explicit_type); hoisted__Declaration_2405->explicit_type = *_ca; free(_ca); }
    hoisted__Declaration_2405->is_mut = self->is_mut;
    hoisted__Declaration_2405->redundant_mut = self->redundant_mut;
    hoisted__Declaration_2405->is_priv = self->is_priv;
    hoisted__Declaration_2405->used = self->used;
    { OwnType *_ca = OwnType_clone(&self->own_type); hoisted__Declaration_2405->own_type = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__Declaration_2405->til_type = *_ca; free(_ca); }
    hoisted__Declaration_2405->default_value = hoisted__Expr_2404;
    { Str *_ca = Str_clone(&self->orig_name); hoisted__Declaration_2405->orig_name = *_ca; free(_ca); }
    (void)hoisted__Declaration_2405;
    return hoisted__Declaration_2405;
}

void Declaration_delete(Declaration * self, Bool call_free) {
    Bool hoisted__Bool_2406 = 0;
    (void)hoisted__Bool_2406;
    Str_delete(&self->name, hoisted__Bool_2406);
    Bool hoisted__Bool_2407 = 0;
    (void)hoisted__Bool_2407;
    Str_delete(&self->doc, hoisted__Bool_2407);
    Bool hoisted__Bool_2408 = 0;
    (void)hoisted__Bool_2408;
    Str_delete(&self->explicit_type, hoisted__Bool_2408);
    Bool hoisted__Bool_2409 = 0;
    (void)hoisted__Bool_2409;
    Bool_delete(&self->is_mut, hoisted__Bool_2409);
    Bool hoisted__Bool_2410 = 0;
    (void)hoisted__Bool_2410;
    Bool_delete(&self->redundant_mut, hoisted__Bool_2410);
    Bool hoisted__Bool_2411 = 0;
    (void)hoisted__Bool_2411;
    Bool_delete(&self->is_priv, hoisted__Bool_2411);
    Bool hoisted__Bool_2412 = 0;
    (void)hoisted__Bool_2412;
    Bool_delete(&self->used, hoisted__Bool_2412);
    Bool hoisted__Bool_2413 = 0;
    (void)hoisted__Bool_2413;
    OwnType_delete(&self->own_type, hoisted__Bool_2413);
    Bool hoisted__Bool_2414 = 0;
    (void)hoisted__Bool_2414;
    Type_delete(&self->til_type, hoisted__Bool_2414);
    Bool hoisted__Bool_2415 = 1;
    (void)hoisted__Bool_2415;
    Expr_delete(self->default_value, hoisted__Bool_2415);
    Bool hoisted__Bool_2416 = 0;
    (void)hoisted__Bool_2416;
    Str_delete(&self->orig_name, hoisted__Bool_2416);
    if (call_free) {
        free(self);
    }
}

U32 Declaration_size(void) {
    U32 hoisted__U32_2417 = 104;
    (void)hoisted__U32_2417;
    return hoisted__U32_2417;
}

FunctionDef * FunctionDef_clone(FunctionDef * self) {
    FunctionDef *hoisted__FunctionDef_2419 = malloc(sizeof(FunctionDef));
    { FuncType *_ca = FuncType_clone(&self->func_type); hoisted__FunctionDef_2419->func_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->params); hoisted__FunctionDef_2419->params = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->return_type); hoisted__FunctionDef_2419->return_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->throw_types); hoisted__FunctionDef_2419->throw_types = *_ca; free(_ca); }
    hoisted__FunctionDef_2419->variadic_index = self->variadic_index;
    hoisted__FunctionDef_2419->kwargs_index = self->kwargs_index;
    { OwnType *_ca = OwnType_clone(&self->return_own_type); hoisted__FunctionDef_2419->return_own_type = *_ca; free(_ca); }
    hoisted__FunctionDef_2419->auto_generated = self->auto_generated;
    hoisted__FunctionDef_2419->is_enum_variant_ctor = self->is_enum_variant_ctor;
    { Vec *_ca = Vec_clone(&self->captures); hoisted__FunctionDef_2419->captures = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->closure_name); hoisted__FunctionDef_2419->closure_name = *_ca; free(_ca); }
    (void)hoisted__FunctionDef_2419;
    return hoisted__FunctionDef_2419;
}

void FunctionDef_delete(FunctionDef * self, Bool call_free) {
    Bool hoisted__Bool_2420 = 0;
    (void)hoisted__Bool_2420;
    FuncType_delete(&self->func_type, hoisted__Bool_2420);
    Bool hoisted__Bool_2421 = 0;
    (void)hoisted__Bool_2421;
    Vec_delete(&self->params, hoisted__Bool_2421);
    Bool hoisted__Bool_2422 = 0;
    (void)hoisted__Bool_2422;
    Str_delete(&self->return_type, hoisted__Bool_2422);
    Bool hoisted__Bool_2423 = 0;
    (void)hoisted__Bool_2423;
    Vec_delete(&self->throw_types, hoisted__Bool_2423);
    Bool hoisted__Bool_2424 = 0;
    (void)hoisted__Bool_2424;
    I32_delete(&self->variadic_index, hoisted__Bool_2424);
    Bool hoisted__Bool_2425 = 0;
    (void)hoisted__Bool_2425;
    I32_delete(&self->kwargs_index, hoisted__Bool_2425);
    Bool hoisted__Bool_2426 = 0;
    (void)hoisted__Bool_2426;
    OwnType_delete(&self->return_own_type, hoisted__Bool_2426);
    Bool hoisted__Bool_2427 = 0;
    (void)hoisted__Bool_2427;
    Bool_delete(&self->auto_generated, hoisted__Bool_2427);
    Bool hoisted__Bool_2428 = 0;
    (void)hoisted__Bool_2428;
    Bool_delete(&self->is_enum_variant_ctor, hoisted__Bool_2428);
    Bool hoisted__Bool_2429 = 0;
    (void)hoisted__Bool_2429;
    Vec_delete(&self->captures, hoisted__Bool_2429);
    Bool hoisted__Bool_2430 = 0;
    (void)hoisted__Bool_2430;
    Str_delete(&self->closure_name, hoisted__Bool_2430);
    if (call_free) {
        free(self);
    }
}

U64 FunctionDef_hash(FunctionDef * self, HashFn hasher) {
    U32 hoisted__U32_2431 = 0;
    (void)hoisted__U32_2431;
    U64 hoisted__U64_2432 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FunctionDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2431); });
    (void)hoisted__U64_2432;
    return hoisted__U64_2432;
}

U32 FunctionDef_size(void) {
    U32 hoisted__U32_2433 = 176;
    (void)hoisted__U32_2433;
    return hoisted__U32_2433;
}

FCallData * FCallData_clone(FCallData * self) {
    FCallData *hoisted__FCallData_2436 = malloc(sizeof(FCallData));
    hoisted__FCallData_2436->is_splat = self->is_splat;
    hoisted__FCallData_2436->does_throw = self->does_throw;
    hoisted__FCallData_2436->is_bang = self->is_bang;
    hoisted__FCallData_2436->own_args = self->own_args;
    hoisted__FCallData_2436->swap_replace = self->swap_replace;
    { Type *_ca = Type_clone(&self->til_type); hoisted__FCallData_2436->til_type = *_ca; free(_ca); }
    (void)hoisted__FCallData_2436;
    return hoisted__FCallData_2436;
}

void FCallData_delete(FCallData * self, Bool call_free) {
    Bool hoisted__Bool_2437 = 0;
    (void)hoisted__Bool_2437;
    Bool_delete(&self->is_splat, hoisted__Bool_2437);
    Bool hoisted__Bool_2438 = 0;
    (void)hoisted__Bool_2438;
    Bool_delete(&self->does_throw, hoisted__Bool_2438);
    Bool hoisted__Bool_2439 = 0;
    (void)hoisted__Bool_2439;
    Bool_delete(&self->is_bang, hoisted__Bool_2439);
    Bool hoisted__Bool_2440 = 0;
    (void)hoisted__Bool_2440;
    U64_delete(&self->own_args, hoisted__Bool_2440);
    Bool hoisted__Bool_2441 = 0;
    (void)hoisted__Bool_2441;
    Bool_delete(&self->swap_replace, hoisted__Bool_2441);
    Bool hoisted__Bool_2442 = 0;
    (void)hoisted__Bool_2442;
    Type_delete(&self->til_type, hoisted__Bool_2442);
    if (call_free) {
        free(self);
    }
}

U64 FCallData_hash(FCallData * self, HashFn hasher) {
    U32 hoisted__U32_2443 = 0;
    (void)hoisted__U32_2443;
    U64 hoisted__U64_2444 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FCallData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2443); });
    (void)hoisted__U64_2444;
    return hoisted__U64_2444;
}

U32 FCallData_size(void) {
    U32 hoisted__U32_2445 = 32;
    (void)hoisted__U32_2445;
    return hoisted__U32_2445;
}

LiteralNumData * LiteralNumData_clone(LiteralNumData * self) {
    LiteralNumData *hoisted__LiteralNumData_2457 = malloc(sizeof(LiteralNumData));
    { Str *_ca = Str_clone(&self->text); hoisted__LiteralNumData_2457->text = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__LiteralNumData_2457->til_type = *_ca; free(_ca); }
    (void)hoisted__LiteralNumData_2457;
    return hoisted__LiteralNumData_2457;
}

void LiteralNumData_delete(LiteralNumData * self, Bool call_free) {
    Bool hoisted__Bool_2458 = 0;
    (void)hoisted__Bool_2458;
    Str_delete(&self->text, hoisted__Bool_2458);
    Bool hoisted__Bool_2459 = 0;
    (void)hoisted__Bool_2459;
    Type_delete(&self->til_type, hoisted__Bool_2459);
    if (call_free) {
        free(self);
    }
}

U64 LiteralNumData_hash(LiteralNumData * self, HashFn hasher) {
    U32 hoisted__U32_2460 = 0;
    (void)hoisted__U32_2460;
    U64 hoisted__U64_2461 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, LiteralNumData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2460); });
    (void)hoisted__U64_2461;
    return hoisted__U64_2461;
}

U32 LiteralNumData_size(void) {
    U32 hoisted__U32_2462 = 40;
    (void)hoisted__U32_2462;
    return hoisted__U32_2462;
}

IdentData * IdentData_clone(IdentData * self) {
    IdentData *hoisted__IdentData_2473 = malloc(sizeof(IdentData));
    { Str *_ca = Str_clone(&self->name); hoisted__IdentData_2473->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__IdentData_2473->til_type = *_ca; free(_ca); }
    (void)hoisted__IdentData_2473;
    return hoisted__IdentData_2473;
}

void IdentData_delete(IdentData * self, Bool call_free) {
    Bool hoisted__Bool_2474 = 0;
    (void)hoisted__Bool_2474;
    Str_delete(&self->name, hoisted__Bool_2474);
    Bool hoisted__Bool_2475 = 0;
    (void)hoisted__Bool_2475;
    Type_delete(&self->til_type, hoisted__Bool_2475);
    if (call_free) {
        free(self);
    }
}

U64 IdentData_hash(IdentData * self, HashFn hasher) {
    U32 hoisted__U32_2476 = 0;
    (void)hoisted__U32_2476;
    U64 hoisted__U64_2477 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, IdentData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2476); });
    (void)hoisted__U64_2477;
    return hoisted__U64_2477;
}

U32 IdentData_size(void) {
    U32 hoisted__U32_2478 = 40;
    (void)hoisted__U32_2478;
    return hoisted__U32_2478;
}

FieldAccessData * FieldAccessData_clone(FieldAccessData * self) {
    FieldAccessData *hoisted__FieldAccessData_2485 = malloc(sizeof(FieldAccessData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAccessData_2485->name = *_ca; free(_ca); }
    { Type *_ca = Type_clone(&self->til_type); hoisted__FieldAccessData_2485->til_type = *_ca; free(_ca); }
    (void)hoisted__FieldAccessData_2485;
    return hoisted__FieldAccessData_2485;
}

void FieldAccessData_delete(FieldAccessData * self, Bool call_free) {
    Bool hoisted__Bool_2486 = 0;
    (void)hoisted__Bool_2486;
    Str_delete(&self->name, hoisted__Bool_2486);
    Bool hoisted__Bool_2487 = 0;
    (void)hoisted__Bool_2487;
    Type_delete(&self->til_type, hoisted__Bool_2487);
    if (call_free) {
        free(self);
    }
}

U64 FieldAccessData_hash(FieldAccessData * self, HashFn hasher) {
    U32 hoisted__U32_2488 = 0;
    (void)hoisted__U32_2488;
    U64 hoisted__U64_2489 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAccessData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2488); });
    (void)hoisted__U64_2489;
    return hoisted__U64_2489;
}

U32 FieldAccessData_size(void) {
    U32 hoisted__U32_2490 = 40;
    (void)hoisted__U32_2490;
    return hoisted__U32_2490;
}

StructDef * StructDef_clone(StructDef * self) {
    StructDef *hoisted__StructDef_2523 = malloc(sizeof(StructDef));
    { Vec *_ca = Vec_clone(&self->fields); hoisted__StructDef_2523->fields = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->ns_decls); hoisted__StructDef_2523->ns_decls = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->c_tag); hoisted__StructDef_2523->c_tag = *_ca; free(_ca); }
    hoisted__StructDef_2523->is_interface = self->is_interface;
    hoisted__StructDef_2523->interface_ns_marker = self->interface_ns_marker;
    { Str *_ca = Str_clone(&self->implements_name); hoisted__StructDef_2523->implements_name = *_ca; free(_ca); }
    (void)hoisted__StructDef_2523;
    return hoisted__StructDef_2523;
}

void StructDef_delete(StructDef * self, Bool call_free) {
    Bool hoisted__Bool_2524 = 0;
    (void)hoisted__Bool_2524;
    Vec_delete(&self->fields, hoisted__Bool_2524);
    Bool hoisted__Bool_2525 = 0;
    (void)hoisted__Bool_2525;
    Vec_delete(&self->ns_decls, hoisted__Bool_2525);
    Bool hoisted__Bool_2526 = 0;
    (void)hoisted__Bool_2526;
    Str_delete(&self->c_tag, hoisted__Bool_2526);
    Bool hoisted__Bool_2527 = 0;
    (void)hoisted__Bool_2527;
    Bool_delete(&self->is_interface, hoisted__Bool_2527);
    Bool hoisted__Bool_2528 = 0;
    (void)hoisted__Bool_2528;
    Bool_delete(&self->interface_ns_marker, hoisted__Bool_2528);
    Bool hoisted__Bool_2529 = 0;
    (void)hoisted__Bool_2529;
    Str_delete(&self->implements_name, hoisted__Bool_2529);
    if (call_free) {
        free(self);
    }
}

U64 StructDef_hash(StructDef * self, HashFn hasher) {
    U32 hoisted__U32_2530 = 0;
    (void)hoisted__U32_2530;
    U64 hoisted__U64_2531 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, StructDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2530); });
    (void)hoisted__U64_2531;
    return hoisted__U64_2531;
}

U32 StructDef_size(void) {
    U32 hoisted__U32_2532 = 120;
    (void)hoisted__U32_2532;
    return hoisted__U32_2532;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *hoisted__EnumDef_2537 = malloc(sizeof(EnumDef));
    { Vec *_ca = Vec_clone(&self->ns_decls); hoisted__EnumDef_2537->ns_decls = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->variants); hoisted__EnumDef_2537->variants = *_ca; free(_ca); }
    { Map *_ca = Map_clone(&self->payload_types); hoisted__EnumDef_2537->payload_types = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->payload_consts); hoisted__EnumDef_2537->payload_consts = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->implements_name); hoisted__EnumDef_2537->implements_name = *_ca; free(_ca); }
    (void)hoisted__EnumDef_2537;
    return hoisted__EnumDef_2537;
}

void EnumDef_delete(EnumDef * self, Bool call_free) {
    Bool hoisted__Bool_2538 = 0;
    (void)hoisted__Bool_2538;
    Vec_delete(&self->ns_decls, hoisted__Bool_2538);
    Bool hoisted__Bool_2539 = 0;
    (void)hoisted__Bool_2539;
    Vec_delete(&self->variants, hoisted__Bool_2539);
    Bool hoisted__Bool_2540 = 0;
    (void)hoisted__Bool_2540;
    Map_delete(&self->payload_types, hoisted__Bool_2540);
    Bool hoisted__Bool_2541 = 0;
    (void)hoisted__Bool_2541;
    Vec_delete(&self->payload_consts, hoisted__Bool_2541);
    Bool hoisted__Bool_2542 = 0;
    (void)hoisted__Bool_2542;
    Str_delete(&self->implements_name, hoisted__Bool_2542);
    if (call_free) {
        free(self);
    }
}

U64 EnumDef_hash(EnumDef * self, HashFn hasher) {
    U32 hoisted__U32_2543 = 0;
    (void)hoisted__U32_2543;
    U64 hoisted__U64_2544 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, EnumDef *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2543); });
    (void)hoisted__U64_2544;
    return hoisted__U64_2544;
}

U32 EnumDef_size(void) {
    U32 hoisted__U32_2545 = 224;
    (void)hoisted__U32_2545;
    return hoisted__U32_2545;
}

AssignData * AssignData_clone(AssignData * self) {
    AssignData *hoisted__AssignData_2659 = malloc(sizeof(AssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__AssignData_2659->name = *_ca; free(_ca); }
    hoisted__AssignData_2659->save_old_delete = self->save_old_delete;
    hoisted__AssignData_2659->is_payload_alias = self->is_payload_alias;
    hoisted__AssignData_2659->swap_replace = self->swap_replace;
    (void)hoisted__AssignData_2659;
    return hoisted__AssignData_2659;
}

void AssignData_delete(AssignData * self, Bool call_free) {
    Bool hoisted__Bool_2660 = 0;
    (void)hoisted__Bool_2660;
    Str_delete(&self->name, hoisted__Bool_2660);
    Bool hoisted__Bool_2661 = 0;
    (void)hoisted__Bool_2661;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2661);
    Bool hoisted__Bool_2662 = 0;
    (void)hoisted__Bool_2662;
    Bool_delete(&self->is_payload_alias, hoisted__Bool_2662);
    Bool hoisted__Bool_2663 = 0;
    (void)hoisted__Bool_2663;
    Bool_delete(&self->swap_replace, hoisted__Bool_2663);
    if (call_free) {
        free(self);
    }
}

U64 AssignData_hash(AssignData * self, HashFn hasher) {
    U32 hoisted__U32_2664 = 0;
    (void)hoisted__U32_2664;
    U64 hoisted__U64_2665 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, AssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2664); });
    (void)hoisted__U64_2665;
    return hoisted__U64_2665;
}

U32 AssignData_size(void) {
    U32 hoisted__U32_2666 = 24;
    (void)hoisted__U32_2666;
    return hoisted__U32_2666;
}

FieldAssignData * FieldAssignData_clone(FieldAssignData * self) {
    FieldAssignData *hoisted__FieldAssignData_2668 = malloc(sizeof(FieldAssignData));
    { Str *_ca = Str_clone(&self->name); hoisted__FieldAssignData_2668->name = *_ca; free(_ca); }
    hoisted__FieldAssignData_2668->save_old_delete = self->save_old_delete;
    (void)hoisted__FieldAssignData_2668;
    return hoisted__FieldAssignData_2668;
}

void FieldAssignData_delete(FieldAssignData * self, Bool call_free) {
    Bool hoisted__Bool_2669 = 0;
    (void)hoisted__Bool_2669;
    Str_delete(&self->name, hoisted__Bool_2669);
    Bool hoisted__Bool_2670 = 0;
    (void)hoisted__Bool_2670;
    Bool_delete(&self->save_old_delete, hoisted__Bool_2670);
    if (call_free) {
        free(self);
    }
}

U64 FieldAssignData_hash(FieldAssignData * self, HashFn hasher) {
    U32 hoisted__U32_2671 = 0;
    (void)hoisted__U32_2671;
    U64 hoisted__U64_2672 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, FieldAssignData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2671); });
    (void)hoisted__U64_2672;
    return hoisted__U64_2672;
}

U32 FieldAssignData_size(void) {
    U32 hoisted__U32_2673 = 24;
    (void)hoisted__U32_2673;
    return hoisted__U32_2673;
}

ForInData * ForInData_clone(ForInData * self) {
    ForInData *hoisted__ForInData_2675 = malloc(sizeof(ForInData));
    { Str *_ca = Str_clone(&self->name); hoisted__ForInData_2675->name = *_ca; free(_ca); }
    hoisted__ForInData_2675->is_mut = self->is_mut;
    { Type *_ca = Type_clone(&self->til_type); hoisted__ForInData_2675->til_type = *_ca; free(_ca); }
    (void)hoisted__ForInData_2675;
    return hoisted__ForInData_2675;
}

void ForInData_delete(ForInData * self, Bool call_free) {
    Bool hoisted__Bool_2676 = 0;
    (void)hoisted__Bool_2676;
    Str_delete(&self->name, hoisted__Bool_2676);
    Bool hoisted__Bool_2677 = 0;
    (void)hoisted__Bool_2677;
    Bool_delete(&self->is_mut, hoisted__Bool_2677);
    Bool hoisted__Bool_2678 = 0;
    (void)hoisted__Bool_2678;
    Type_delete(&self->til_type, hoisted__Bool_2678);
    if (call_free) {
        free(self);
    }
}

U64 ForInData_hash(ForInData * self, HashFn hasher) {
    U32 hoisted__U32_2679 = 0;
    (void)hoisted__U32_2679;
    U64 hoisted__U64_2680 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, ForInData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2679); });
    (void)hoisted__U64_2680;
    return hoisted__U64_2680;
}

U32 ForInData_size(void) {
    U32 hoisted__U32_2681 = 48;
    (void)hoisted__U32_2681;
    return hoisted__U32_2681;
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
    Bool hoisted__Bool_2711 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2711;
    if (hoisted__Bool_2711) {
        Str *hoisted__Str_2705 = get_payload(self);
        (void)hoisted__Str_2705;
        (void)hoisted__Str_2705;
        Bool hoisted__Bool_2706 = 0;
        (void)hoisted__Bool_2706;
        Str_delete(hoisted__Str_2705, hoisted__Bool_2706);
    }
    Bool hoisted__Bool_2712 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2712;
    if (hoisted__Bool_2712) {
        LiteralNumData *hoisted__LiteralNumData_2707 = get_payload(self);
        (void)hoisted__LiteralNumData_2707;
        (void)hoisted__LiteralNumData_2707;
        Bool hoisted__Bool_2708 = 0;
        (void)hoisted__Bool_2708;
        LiteralNumData_delete(hoisted__LiteralNumData_2707, hoisted__Bool_2708);
    }
    Bool hoisted__Bool_2713 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2713;
    if (hoisted__Bool_2713) {
        Bool *hoisted__Bool_2709 = get_payload(self);
        (void)hoisted__Bool_2709;
        (void)hoisted__Bool_2709;
        Bool hoisted__Bool_2710 = 0;
        (void)hoisted__Bool_2710;
        Bool_delete(hoisted__Bool_2709, hoisted__Bool_2710);
    }
    if (call_free) {
        free(self);
    }
}

Literal * Literal_clone(Literal * self) {
    Bool hoisted__Bool_2753 = is(self, &(Literal){.tag = Literal_TAG_Str});
    (void)hoisted__Bool_2753;
    if (hoisted__Bool_2753) {
        Str *_clone_payload_Str_0 = get_payload(self);
        (void)_clone_payload_Str_0;
        (void)_clone_payload_Str_0;
        Str *hoisted__Str_2748 = Str_clone(_clone_payload_Str_0);
        (void)hoisted__Str_2748;
        Literal *hoisted__Literal_2749 = Literal_Str(hoisted__Str_2748);
        (void)hoisted__Literal_2749;
        { Literal * _ret_val = hoisted__Literal_2749;
                return _ret_val; }
    }
    Bool hoisted__Bool_2754 = is(self, &(Literal){.tag = Literal_TAG_Num});
    (void)hoisted__Bool_2754;
    if (hoisted__Bool_2754) {
        LiteralNumData *_clone_payload_Num_1 = get_payload(self);
        (void)_clone_payload_Num_1;
        (void)_clone_payload_Num_1;
        LiteralNumData *hoisted__LiteralNumData_2750 = LiteralNumData_clone(_clone_payload_Num_1);
        (void)hoisted__LiteralNumData_2750;
        Literal *hoisted__Literal_2751 = Literal_Num(hoisted__LiteralNumData_2750);
        (void)hoisted__Literal_2751;
        { Literal * _ret_val = hoisted__Literal_2751;
                return _ret_val; }
    }
    Bool hoisted__Bool_2755 = is(self, &(Literal){.tag = Literal_TAG_Bool});
    (void)hoisted__Bool_2755;
    if (hoisted__Bool_2755) {
        Bool *_clone_payload_Bool_2 = get_payload(self);
        (void)_clone_payload_Bool_2;
        (void)_clone_payload_Bool_2;
        Literal *hoisted__Literal_2752 = Literal_Bool(_clone_payload_Bool_2);
        (void)hoisted__Literal_2752;
        { Literal * _ret_val = hoisted__Literal_2752;
                return _ret_val; }
    }
    Bool hoisted__Bool_2756 = is(self, &(Literal){.tag = Literal_TAG_Null});
    (void)hoisted__Bool_2756;
    if (hoisted__Bool_2756) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_Null;
                return _r; }
    }
    Bool hoisted__Bool_2757 = is(self, &(Literal){.tag = Literal_TAG_MapLit});
    (void)hoisted__Bool_2757;
    if (hoisted__Bool_2757) {
        { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_MapLit;
                return _r; }
    }
    { Literal *_r = malloc(sizeof(Literal)); _r->tag = Literal_TAG_SetLit;
    return _r; }
}

U32 Literal_size(void) {
    U32 hoisted__U32_2758 = 48;
    (void)hoisted__U32_2758;
    return hoisted__U32_2758;
}


MatchData * MatchData_clone(MatchData * self) {
    MatchData *hoisted__MatchData_2761 = malloc(sizeof(MatchData));
    { Type *_ca = Type_clone(&self->til_type); hoisted__MatchData_2761->til_type = *_ca; free(_ca); }
    { Str *_ca = Str_clone(&self->result_temp); hoisted__MatchData_2761->result_temp = *_ca; free(_ca); }
    (void)hoisted__MatchData_2761;
    return hoisted__MatchData_2761;
}

void MatchData_delete(MatchData * self, Bool call_free) {
    Bool hoisted__Bool_2762 = 0;
    (void)hoisted__Bool_2762;
    Type_delete(&self->til_type, hoisted__Bool_2762);
    Bool hoisted__Bool_2763 = 0;
    (void)hoisted__Bool_2763;
    Str_delete(&self->result_temp, hoisted__Bool_2763);
    if (call_free) {
        free(self);
    }
}

U64 MatchData_hash(MatchData * self, HashFn hasher) {
    U32 hoisted__U32_2764 = 0;
    (void)hoisted__U32_2764;
    U64 hoisted__U64_2765 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, MatchData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2764); });
    (void)hoisted__U64_2765;
    return hoisted__U64_2765;
}

U32 MatchData_size(void) {
    U32 hoisted__U32_2766 = 40;
    (void)hoisted__U32_2766;
    return hoisted__U32_2766;
}

CaptureBlockData * CaptureBlockData_clone(CaptureBlockData * self) {
    CaptureBlockData *hoisted__CaptureBlockData_2771 = malloc(sizeof(CaptureBlockData));
    { Vec *_ca = Vec_clone(&self->captures); hoisted__CaptureBlockData_2771->captures = *_ca; free(_ca); }
    (void)hoisted__CaptureBlockData_2771;
    return hoisted__CaptureBlockData_2771;
}

void CaptureBlockData_delete(CaptureBlockData * self, Bool call_free) {
    Bool hoisted__Bool_2772 = 0;
    (void)hoisted__Bool_2772;
    Vec_delete(&self->captures, hoisted__Bool_2772);
    if (call_free) {
        free(self);
    }
}

U64 CaptureBlockData_hash(CaptureBlockData * self, HashFn hasher) {
    U32 hoisted__U32_2773 = 0;
    (void)hoisted__U32_2773;
    U64 hoisted__U64_2774 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CaptureBlockData *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_2773); });
    (void)hoisted__U64_2774;
    return hoisted__U64_2774;
}

U32 CaptureBlockData_size(void) {
    U32 hoisted__U32_2775 = 40;
    (void)hoisted__U32_2775;
    return hoisted__U32_2775;
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
    Bool hoisted__Bool_2952 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_2952;
    if (hoisted__Bool_2952) {
        Literal *hoisted__Literal_2924 = get_payload(self);
        (void)hoisted__Literal_2924;
        (void)hoisted__Literal_2924;
        Bool hoisted__Bool_2925 = 0;
        (void)hoisted__Bool_2925;
        Literal_delete(hoisted__Literal_2924, hoisted__Bool_2925);
    }
    Bool hoisted__Bool_2953 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_2953;
    if (hoisted__Bool_2953) {
        IdentData *hoisted__IdentData_2926 = get_payload(self);
        (void)hoisted__IdentData_2926;
        (void)hoisted__IdentData_2926;
        Bool hoisted__Bool_2927 = 0;
        (void)hoisted__Bool_2927;
        IdentData_delete(hoisted__IdentData_2926, hoisted__Bool_2927);
    }
    Bool hoisted__Bool_2954 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_2954;
    if (hoisted__Bool_2954) {
        Declaration *hoisted__Declaration_2928 = get_payload(self);
        (void)hoisted__Declaration_2928;
        (void)hoisted__Declaration_2928;
        Bool hoisted__Bool_2929 = 0;
        (void)hoisted__Bool_2929;
        Declaration_delete(hoisted__Declaration_2928, hoisted__Bool_2929);
    }
    Bool hoisted__Bool_2955 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_2955;
    if (hoisted__Bool_2955) {
        AssignData *hoisted__AssignData_2930 = get_payload(self);
        (void)hoisted__AssignData_2930;
        (void)hoisted__AssignData_2930;
        Bool hoisted__Bool_2931 = 0;
        (void)hoisted__Bool_2931;
        AssignData_delete(hoisted__AssignData_2930, hoisted__Bool_2931);
    }
    Bool hoisted__Bool_2956 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_2956;
    if (hoisted__Bool_2956) {
        FCallData *hoisted__FCallData_2932 = get_payload(self);
        (void)hoisted__FCallData_2932;
        (void)hoisted__FCallData_2932;
        Bool hoisted__Bool_2933 = 0;
        (void)hoisted__Bool_2933;
        FCallData_delete(hoisted__FCallData_2932, hoisted__Bool_2933);
    }
    Bool hoisted__Bool_2957 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_2957;
    if (hoisted__Bool_2957) {
        FunctionDef *hoisted__FunctionDef_2934 = get_payload(self);
        (void)hoisted__FunctionDef_2934;
        (void)hoisted__FunctionDef_2934;
        Bool hoisted__Bool_2935 = 0;
        (void)hoisted__Bool_2935;
        FunctionDef_delete(hoisted__FunctionDef_2934, hoisted__Bool_2935);
    }
    Bool hoisted__Bool_2958 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_2958;
    if (hoisted__Bool_2958) {
        StructDef *hoisted__StructDef_2936 = get_payload(self);
        (void)hoisted__StructDef_2936;
        (void)hoisted__StructDef_2936;
        Bool hoisted__Bool_2937 = 0;
        (void)hoisted__Bool_2937;
        StructDef_delete(hoisted__StructDef_2936, hoisted__Bool_2937);
    }
    Bool hoisted__Bool_2959 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_2959;
    if (hoisted__Bool_2959) {
        EnumDef *hoisted__EnumDef_2938 = get_payload(self);
        (void)hoisted__EnumDef_2938;
        (void)hoisted__EnumDef_2938;
        Bool hoisted__Bool_2939 = 0;
        (void)hoisted__Bool_2939;
        EnumDef_delete(hoisted__EnumDef_2938, hoisted__Bool_2939);
    }
    Bool hoisted__Bool_2960 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_2960;
    if (hoisted__Bool_2960) {
        FieldAccessData *hoisted__FieldAccessData_2940 = get_payload(self);
        (void)hoisted__FieldAccessData_2940;
        (void)hoisted__FieldAccessData_2940;
        Bool hoisted__Bool_2941 = 0;
        (void)hoisted__Bool_2941;
        FieldAccessData_delete(hoisted__FieldAccessData_2940, hoisted__Bool_2941);
    }
    Bool hoisted__Bool_2961 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_2961;
    if (hoisted__Bool_2961) {
        FieldAssignData *hoisted__FieldAssignData_2942 = get_payload(self);
        (void)hoisted__FieldAssignData_2942;
        (void)hoisted__FieldAssignData_2942;
        Bool hoisted__Bool_2943 = 0;
        (void)hoisted__Bool_2943;
        FieldAssignData_delete(hoisted__FieldAssignData_2942, hoisted__Bool_2943);
    }
    Bool hoisted__Bool_2962 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_2962;
    if (hoisted__Bool_2962) {
        ForInData *hoisted__ForInData_2944 = get_payload(self);
        (void)hoisted__ForInData_2944;
        (void)hoisted__ForInData_2944;
        Bool hoisted__Bool_2945 = 0;
        (void)hoisted__Bool_2945;
        ForInData_delete(hoisted__ForInData_2944, hoisted__Bool_2945);
    }
    Bool hoisted__Bool_2963 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_2963;
    if (hoisted__Bool_2963) {
        Str *hoisted__Str_2946 = get_payload(self);
        (void)hoisted__Str_2946;
        (void)hoisted__Str_2946;
        Bool hoisted__Bool_2947 = 0;
        (void)hoisted__Bool_2947;
        Str_delete(hoisted__Str_2946, hoisted__Bool_2947);
    }
    Bool hoisted__Bool_2964 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_2964;
    if (hoisted__Bool_2964) {
        MatchData *hoisted__MatchData_2948 = get_payload(self);
        (void)hoisted__MatchData_2948;
        (void)hoisted__MatchData_2948;
        Bool hoisted__Bool_2949 = 0;
        (void)hoisted__Bool_2949;
        MatchData_delete(hoisted__MatchData_2948, hoisted__Bool_2949);
    }
    Bool hoisted__Bool_2965 = is(self, &(NodeType){.tag = NodeType_TAG_CaptureBlock});
    (void)hoisted__Bool_2965;
    if (hoisted__Bool_2965) {
        CaptureBlockData *hoisted__CaptureBlockData_2950 = get_payload(self);
        (void)hoisted__CaptureBlockData_2950;
        (void)hoisted__CaptureBlockData_2950;
        Bool hoisted__Bool_2951 = 0;
        (void)hoisted__Bool_2951;
        CaptureBlockData_delete(hoisted__CaptureBlockData_2950, hoisted__Bool_2951);
    }
    if (call_free) {
        free(self);
    }
}

NodeType * NodeType_clone(NodeType * self) {
    Bool hoisted__Bool_3143 = is(self, &(NodeType){.tag = NodeType_TAG_Body});
    (void)hoisted__Bool_3143;
    if (hoisted__Bool_3143) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Body;
                return _r; }
    }
    Bool hoisted__Bool_3144 = is(self, &(NodeType){.tag = NodeType_TAG_Literal});
    (void)hoisted__Bool_3144;
    if (hoisted__Bool_3144) {
        Literal *_clone_payload_Literal_1 = get_payload(self);
        (void)_clone_payload_Literal_1;
        (void)_clone_payload_Literal_1;
        Literal *hoisted__Literal_3117 = Literal_clone(_clone_payload_Literal_1);
        (void)hoisted__Literal_3117;
        NodeType *hoisted__NodeType_3118 = NodeType_Literal(hoisted__Literal_3117);
        (void)hoisted__NodeType_3118;
        { NodeType * _ret_val = hoisted__NodeType_3118;
                return _ret_val; }
    }
    Bool hoisted__Bool_3145 = is(self, &(NodeType){.tag = NodeType_TAG_Ident});
    (void)hoisted__Bool_3145;
    if (hoisted__Bool_3145) {
        IdentData *_clone_payload_Ident_2 = get_payload(self);
        (void)_clone_payload_Ident_2;
        (void)_clone_payload_Ident_2;
        IdentData *hoisted__IdentData_3119 = IdentData_clone(_clone_payload_Ident_2);
        (void)hoisted__IdentData_3119;
        NodeType *hoisted__NodeType_3120 = NodeType_Ident(hoisted__IdentData_3119);
        (void)hoisted__NodeType_3120;
        { NodeType * _ret_val = hoisted__NodeType_3120;
                return _ret_val; }
    }
    Bool hoisted__Bool_3146 = is(self, &(NodeType){.tag = NodeType_TAG_Decl});
    (void)hoisted__Bool_3146;
    if (hoisted__Bool_3146) {
        Declaration *_clone_payload_Decl_3 = get_payload(self);
        (void)_clone_payload_Decl_3;
        (void)_clone_payload_Decl_3;
        Declaration *hoisted__Declaration_3121 = Declaration_clone(_clone_payload_Decl_3);
        (void)hoisted__Declaration_3121;
        NodeType *hoisted__NodeType_3122 = NodeType_Decl(hoisted__Declaration_3121);
        (void)hoisted__NodeType_3122;
        { NodeType * _ret_val = hoisted__NodeType_3122;
                return _ret_val; }
    }
    Bool hoisted__Bool_3147 = is(self, &(NodeType){.tag = NodeType_TAG_Assign});
    (void)hoisted__Bool_3147;
    if (hoisted__Bool_3147) {
        AssignData *_clone_payload_Assign_4 = get_payload(self);
        (void)_clone_payload_Assign_4;
        (void)_clone_payload_Assign_4;
        AssignData *hoisted__AssignData_3123 = AssignData_clone(_clone_payload_Assign_4);
        (void)hoisted__AssignData_3123;
        NodeType *hoisted__NodeType_3124 = NodeType_Assign(hoisted__AssignData_3123);
        (void)hoisted__NodeType_3124;
        { NodeType * _ret_val = hoisted__NodeType_3124;
                return _ret_val; }
    }
    Bool hoisted__Bool_3148 = is(self, &(NodeType){.tag = NodeType_TAG_FCall});
    (void)hoisted__Bool_3148;
    if (hoisted__Bool_3148) {
        FCallData *_clone_payload_FCall_5 = get_payload(self);
        (void)_clone_payload_FCall_5;
        (void)_clone_payload_FCall_5;
        FCallData *hoisted__FCallData_3125 = FCallData_clone(_clone_payload_FCall_5);
        (void)hoisted__FCallData_3125;
        NodeType *hoisted__NodeType_3126 = NodeType_FCall(hoisted__FCallData_3125);
        (void)hoisted__NodeType_3126;
        { NodeType * _ret_val = hoisted__NodeType_3126;
                return _ret_val; }
    }
    Bool hoisted__Bool_3149 = is(self, &(NodeType){.tag = NodeType_TAG_FuncDef});
    (void)hoisted__Bool_3149;
    if (hoisted__Bool_3149) {
        FunctionDef *_clone_payload_FuncDef_6 = get_payload(self);
        (void)_clone_payload_FuncDef_6;
        (void)_clone_payload_FuncDef_6;
        FunctionDef *hoisted__FunctionDef_3127 = FunctionDef_clone(_clone_payload_FuncDef_6);
        (void)hoisted__FunctionDef_3127;
        NodeType *hoisted__NodeType_3128 = NodeType_FuncDef(hoisted__FunctionDef_3127);
        (void)hoisted__NodeType_3128;
        { NodeType * _ret_val = hoisted__NodeType_3128;
                return _ret_val; }
    }
    Bool hoisted__Bool_3150 = is(self, &(NodeType){.tag = NodeType_TAG_StructDef});
    (void)hoisted__Bool_3150;
    if (hoisted__Bool_3150) {
        StructDef *_clone_payload_StructDef_7 = get_payload(self);
        (void)_clone_payload_StructDef_7;
        (void)_clone_payload_StructDef_7;
        StructDef *hoisted__StructDef_3129 = StructDef_clone(_clone_payload_StructDef_7);
        (void)hoisted__StructDef_3129;
        NodeType *hoisted__NodeType_3130 = NodeType_StructDef(hoisted__StructDef_3129);
        (void)hoisted__NodeType_3130;
        { NodeType * _ret_val = hoisted__NodeType_3130;
                return _ret_val; }
    }
    Bool hoisted__Bool_3151 = is(self, &(NodeType){.tag = NodeType_TAG_EnumDef});
    (void)hoisted__Bool_3151;
    if (hoisted__Bool_3151) {
        EnumDef *_clone_payload_EnumDef_8 = get_payload(self);
        (void)_clone_payload_EnumDef_8;
        (void)_clone_payload_EnumDef_8;
        EnumDef *hoisted__EnumDef_3131 = EnumDef_clone(_clone_payload_EnumDef_8);
        (void)hoisted__EnumDef_3131;
        NodeType *hoisted__NodeType_3132 = NodeType_EnumDef(hoisted__EnumDef_3131);
        (void)hoisted__NodeType_3132;
        { NodeType * _ret_val = hoisted__NodeType_3132;
                return _ret_val; }
    }
    Bool hoisted__Bool_3152 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAccess});
    (void)hoisted__Bool_3152;
    if (hoisted__Bool_3152) {
        FieldAccessData *_clone_payload_FieldAccess_9 = get_payload(self);
        (void)_clone_payload_FieldAccess_9;
        (void)_clone_payload_FieldAccess_9;
        FieldAccessData *hoisted__FieldAccessData_3133 = FieldAccessData_clone(_clone_payload_FieldAccess_9);
        (void)hoisted__FieldAccessData_3133;
        NodeType *hoisted__NodeType_3134 = NodeType_FieldAccess(hoisted__FieldAccessData_3133);
        (void)hoisted__NodeType_3134;
        { NodeType * _ret_val = hoisted__NodeType_3134;
                return _ret_val; }
    }
    Bool hoisted__Bool_3153 = is(self, &(NodeType){.tag = NodeType_TAG_FieldAssign});
    (void)hoisted__Bool_3153;
    if (hoisted__Bool_3153) {
        FieldAssignData *_clone_payload_FieldAssign_10 = get_payload(self);
        (void)_clone_payload_FieldAssign_10;
        (void)_clone_payload_FieldAssign_10;
        FieldAssignData *hoisted__FieldAssignData_3135 = FieldAssignData_clone(_clone_payload_FieldAssign_10);
        (void)hoisted__FieldAssignData_3135;
        NodeType *hoisted__NodeType_3136 = NodeType_FieldAssign(hoisted__FieldAssignData_3135);
        (void)hoisted__NodeType_3136;
        { NodeType * _ret_val = hoisted__NodeType_3136;
                return _ret_val; }
    }
    Bool hoisted__Bool_3154 = is(self, &(NodeType){.tag = NodeType_TAG_Return});
    (void)hoisted__Bool_3154;
    if (hoisted__Bool_3154) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Return;
                return _r; }
    }
    Bool hoisted__Bool_3155 = is(self, &(NodeType){.tag = NodeType_TAG_If});
    (void)hoisted__Bool_3155;
    if (hoisted__Bool_3155) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_If;
                return _r; }
    }
    Bool hoisted__Bool_3156 = is(self, &(NodeType){.tag = NodeType_TAG_While});
    (void)hoisted__Bool_3156;
    if (hoisted__Bool_3156) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_While;
                return _r; }
    }
    Bool hoisted__Bool_3157 = is(self, &(NodeType){.tag = NodeType_TAG_ForIn});
    (void)hoisted__Bool_3157;
    if (hoisted__Bool_3157) {
        ForInData *_clone_payload_ForIn_14 = get_payload(self);
        (void)_clone_payload_ForIn_14;
        (void)_clone_payload_ForIn_14;
        ForInData *hoisted__ForInData_3137 = ForInData_clone(_clone_payload_ForIn_14);
        (void)hoisted__ForInData_3137;
        NodeType *hoisted__NodeType_3138 = NodeType_ForIn(hoisted__ForInData_3137);
        (void)hoisted__NodeType_3138;
        { NodeType * _ret_val = hoisted__NodeType_3138;
                return _ret_val; }
    }
    Bool hoisted__Bool_3158 = is(self, &(NodeType){.tag = NodeType_TAG_NamedArg});
    (void)hoisted__Bool_3158;
    if (hoisted__Bool_3158) {
        Str *_clone_payload_NamedArg_15 = get_payload(self);
        (void)_clone_payload_NamedArg_15;
        (void)_clone_payload_NamedArg_15;
        Str *hoisted__Str_3139 = Str_clone(_clone_payload_NamedArg_15);
        (void)hoisted__Str_3139;
        NodeType *hoisted__NodeType_3140 = NodeType_NamedArg(hoisted__Str_3139);
        (void)hoisted__NodeType_3140;
        { NodeType * _ret_val = hoisted__NodeType_3140;
                return _ret_val; }
    }
    Bool hoisted__Bool_3159 = is(self, &(NodeType){.tag = NodeType_TAG_Break});
    (void)hoisted__Bool_3159;
    if (hoisted__Bool_3159) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Break;
                return _r; }
    }
    Bool hoisted__Bool_3160 = is(self, &(NodeType){.tag = NodeType_TAG_Continue});
    (void)hoisted__Bool_3160;
    if (hoisted__Bool_3160) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Continue;
                return _r; }
    }
    Bool hoisted__Bool_3161 = is(self, &(NodeType){.tag = NodeType_TAG_Switch});
    (void)hoisted__Bool_3161;
    if (hoisted__Bool_3161) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Switch;
                return _r; }
    }
    Bool hoisted__Bool_3162 = is(self, &(NodeType){.tag = NodeType_TAG_Match});
    (void)hoisted__Bool_3162;
    if (hoisted__Bool_3162) {
        MatchData *_clone_payload_Match_19 = get_payload(self);
        (void)_clone_payload_Match_19;
        (void)_clone_payload_Match_19;
        MatchData *hoisted__MatchData_3141 = MatchData_clone(_clone_payload_Match_19);
        (void)hoisted__MatchData_3141;
        NodeType *hoisted__NodeType_3142 = NodeType_Match(hoisted__MatchData_3141);
        (void)hoisted__NodeType_3142;
        { NodeType * _ret_val = hoisted__NodeType_3142;
                return _ret_val; }
    }
    Bool hoisted__Bool_3163 = is(self, &(NodeType){.tag = NodeType_TAG_Case});
    (void)hoisted__Bool_3163;
    if (hoisted__Bool_3163) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Case;
                return _r; }
    }
    Bool hoisted__Bool_3164 = is(self, &(NodeType){.tag = NodeType_TAG_NoDefaultArg});
    (void)hoisted__Bool_3164;
    if (hoisted__Bool_3164) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_NoDefaultArg;
                return _r; }
    }
    Bool hoisted__Bool_3165 = is(self, &(NodeType){.tag = NodeType_TAG_Throw});
    (void)hoisted__Bool_3165;
    if (hoisted__Bool_3165) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Throw;
                return _r; }
    }
    Bool hoisted__Bool_3166 = is(self, &(NodeType){.tag = NodeType_TAG_Catch});
    (void)hoisted__Bool_3166;
    if (hoisted__Bool_3166) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_Catch;
                return _r; }
    }
    Bool hoisted__Bool_3167 = is(self, &(NodeType){.tag = NodeType_TAG_RestPattern});
    (void)hoisted__Bool_3167;
    if (hoisted__Bool_3167) {
        { NodeType *_r = malloc(sizeof(NodeType)); _r->tag = NodeType_TAG_RestPattern;
                return _r; }
    }
    CaptureBlockData *_clone_payload_CaptureBlock_25 = get_payload(self);
    (void)_clone_payload_CaptureBlock_25;
    (void)_clone_payload_CaptureBlock_25;
    CaptureBlockData *hoisted__CaptureBlockData_3168 = CaptureBlockData_clone(_clone_payload_CaptureBlock_25);
    (void)hoisted__CaptureBlockData_3168;
    NodeType *hoisted__NodeType_3169 = NodeType_CaptureBlock(hoisted__CaptureBlockData_3168);
    (void)hoisted__NodeType_3169;
    return hoisted__NodeType_3169;
}

U32 NodeType_size(void) {
    U32 hoisted__U32_3170 = 232;
    (void)hoisted__U32_3170;
    return hoisted__U32_3170;
}


void Expr_delete(Expr * self, Bool call_free) {
    Bool hoisted__Bool_3171 = is_null(self);
    (void)hoisted__Bool_3171;
    if (hoisted__Bool_3171) {
        return;
    }
    Bool hoisted__Bool_3172 = 0;
    (void)hoisted__Bool_3172;
    NodeType_delete(&self->node_type, hoisted__Bool_3172);
    Bool hoisted__Bool_3173 = 0;
    (void)hoisted__Bool_3173;
    Vec_delete(&self->children, hoisted__Bool_3173);
    if (call_free) {
        free(self);
    }
}

Expr * Expr_new(NodeType * data, U32 line, U32 col) {
    Type *hoisted__Type_3216 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Expr", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3216;
    Expr *hoisted__Expr_3217 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(data); hoisted__Expr_3217->node_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_new(hoisted__Type_3216); hoisted__Expr_3217->children = *_ca; free(_ca); }
    hoisted__Expr_3217->line = line;
    hoisted__Expr_3217->col = col;
    (void)hoisted__Expr_3217;
    Type_delete(hoisted__Type_3216, 1);
    return hoisted__Expr_3217;
}

Expr * Expr_clone(Expr * self) {
    Expr *hoisted__Expr_3225 = malloc(sizeof(Expr));
    { NodeType *_ca = NodeType_clone(&self->node_type); hoisted__Expr_3225->node_type = *_ca; free(_ca); }
    { Vec *_ca = Vec_clone(&self->children); hoisted__Expr_3225->children = *_ca; free(_ca); }
    hoisted__Expr_3225->line = self->line;
    hoisted__Expr_3225->col = self->col;
    (void)hoisted__Expr_3225;
    return hoisted__Expr_3225;
}

U64 Expr_hash(Expr * self, HashFn hasher) {
    U32 hoisted__U32_3226 = 0;
    (void)hoisted__U32_3226;
    U64 hoisted__U64_3227 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Expr *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_3226); });
    (void)hoisted__U64_3227;
    return hoisted__U64_3227;
}

U32 Expr_size(void) {
    U32 hoisted__U32_3228 = 280;
    (void)hoisted__U32_3228;
    return hoisted__U32_3228;
}

void panic(Str * loc_str, Array__Str * parts) {
    U32 hoisted__U32_4109 = 3;
    (void)hoisted__U32_4109;
    Array__Str *_va_Array_148 = Array__Str_new(hoisted__U32_4109);
    (void)_va_Array_148;
    U32 hoisted__U32_4110 = 0;
    (void)hoisted__U32_4110;
    Str *hoisted__Str_4111 = Str_clone(loc_str);
    (void)hoisted__Str_4111;
    Array__Str_set(_va_Array_148, hoisted__U32_4110, hoisted__Str_4111);
    U32 hoisted__U32_4112 = 1;
    (void)hoisted__U32_4112;
    Str hoisted__Str_4113 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4113;
    Array__Str_set(_va_Array_148, hoisted__U32_4112, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4113; _oa; }));
    Array__Str *hoisted__Array__Str_4114 = Array__Str_clone(parts);
    (void)hoisted__Array__Str_4114;
    U32 hoisted__U32_4115 = 2;
    (void)hoisted__U32_4115;
    Str *hoisted__Str_4116 = format(hoisted__Array__Str_4114);
    (void)hoisted__Str_4116;
    Array__Str_set(_va_Array_148, hoisted__U32_4115, hoisted__Str_4116);
    Array__Str_delete(parts, 1);
    println(_va_Array_148);
    I64 hoisted__I64_4117 = 1;
    (void)hoisted__I64_4117;
    exit(hoisted__I64_4117);
}

void UNREACHABLE(Str * loc_str) {
    U32 hoisted__U32_4124 = 1;
    (void)hoisted__U32_4124;
    Array__Str *_va_Array_150 = Array__Str_new(hoisted__U32_4124);
    (void)_va_Array_150;
    U32 hoisted__U32_4125 = 0;
    (void)hoisted__U32_4125;
    Str hoisted__Str_4126 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4126;
    Array__Str_set(_va_Array_150, hoisted__U32_4125, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4126; _oa; }));
    panic(loc_str, _va_Array_150);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4130 = not(cond);
    (void)hoisted__Bool_4130;
    if (hoisted__Bool_4130) {
        U32 hoisted__U32_4127 = 1;
        (void)hoisted__U32_4127;
        Array__Str *_va_Array_151 = Array__Str_new(hoisted__U32_4127);
        (void)_va_Array_151;
        U32 hoisted__U32_4128 = 0;
        (void)hoisted__U32_4128;
        Str hoisted__Str_4129 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4129;
        Array__Str_set(_va_Array_151, hoisted__U32_4128, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4129; _oa; }));
        panic(loc_str, _va_Array_151);
    }
    Bool hoisted__Bool_4131 = 1;
    (void)hoisted__Bool_4131;
    return hoisted__Bool_4131;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4150 = I64_neq(a, b);
    (void)hoisted__Bool_4150;
    if (hoisted__Bool_4150) {
        U32 hoisted__U32_4139 = 5;
        (void)hoisted__U32_4139;
        Array__Str *_va_Array_153 = Array__Str_new(hoisted__U32_4139);
        (void)_va_Array_153;
        U32 hoisted__U32_4140 = 0;
        (void)hoisted__U32_4140;
        Str hoisted__Str_4141 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4141;
        Array__Str_set(_va_Array_153, hoisted__U32_4140, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4141; _oa; }));
        U32 hoisted__U32_4142 = 1;
        (void)hoisted__U32_4142;
        Str *hoisted__Str_4143 = I64_to_str(a);
        (void)hoisted__Str_4143;
        Array__Str_set(_va_Array_153, hoisted__U32_4142, hoisted__Str_4143);
        U32 hoisted__U32_4144 = 2;
        (void)hoisted__U32_4144;
        Str hoisted__Str_4145 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4145;
        Array__Str_set(_va_Array_153, hoisted__U32_4144, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4145; _oa; }));
        U32 hoisted__U32_4146 = 3;
        (void)hoisted__U32_4146;
        Str *hoisted__Str_4147 = I64_to_str(b);
        (void)hoisted__Str_4147;
        Array__Str_set(_va_Array_153, hoisted__U32_4146, hoisted__Str_4147);
        U32 hoisted__U32_4148 = 4;
        (void)hoisted__U32_4148;
        Str hoisted__Str_4149 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4149;
        Array__Str_set(_va_Array_153, hoisted__U32_4148, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4149; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4162 = Str_eq(a, b);
    (void)hoisted__Bool_4162;
    Bool hoisted__Bool_4163 = not(hoisted__Bool_4162);
    (void)hoisted__Bool_4163;
    if (hoisted__Bool_4163) {
        U32 hoisted__U32_4151 = 5;
        (void)hoisted__U32_4151;
        Array__Str *_va_Array_154 = Array__Str_new(hoisted__U32_4151);
        (void)_va_Array_154;
        U32 hoisted__U32_4152 = 0;
        (void)hoisted__U32_4152;
        Str hoisted__Str_4153 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4153;
        Array__Str_set(_va_Array_154, hoisted__U32_4152, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4153; _oa; }));
        U32 hoisted__U32_4154 = 1;
        (void)hoisted__U32_4154;
        Str *hoisted__Str_4155 = Str_clone(a);
        (void)hoisted__Str_4155;
        Array__Str_set(_va_Array_154, hoisted__U32_4154, hoisted__Str_4155);
        U32 hoisted__U32_4156 = 2;
        (void)hoisted__U32_4156;
        Str hoisted__Str_4157 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4157;
        Array__Str_set(_va_Array_154, hoisted__U32_4156, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4157; _oa; }));
        U32 hoisted__U32_4158 = 3;
        (void)hoisted__U32_4158;
        Str *hoisted__Str_4159 = Str_clone(b);
        (void)hoisted__Str_4159;
        Array__Str_set(_va_Array_154, hoisted__U32_4158, hoisted__Str_4159);
        U32 hoisted__U32_4160 = 4;
        (void)hoisted__U32_4160;
        Str hoisted__Str_4161 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4161;
        Array__Str_set(_va_Array_154, hoisted__U32_4160, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4161; _oa; }));
        panic(loc_str, _va_Array_154);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_4164 = parts;
        (void)_fc_Array__Str_4164;
        (void)_fc_Array__Str_4164;
        U32 _fi_USize_4164 = 0;
        (void)_fi_USize_4164;
        I64 _forin_err_kind_4164 = 0;
        (void)_forin_err_kind_4164;
        OutOfBounds *_forin_OutOfBounds_4164 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4164->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4164;
        while (1) {
            U32 hoisted__U32_4170 = Array__Str_len(_fc_Array__Str_4164);
            (void)hoisted__U32_4170;
            Bool _wcond_Bool_4165 = U32_lt(_fi_USize_4164, hoisted__U32_4170);
            (void)_wcond_Bool_4165;
            if (_wcond_Bool_4165) {
            } else {
                break;
            }
            Str *s = Array__Str_get(_fc_Array__Str_4164, &_fi_USize_4164, &_forin_err_kind_4164, _forin_OutOfBounds_4164);
            I64 hoisted__I64_4171 = 0;
            (void)hoisted__I64_4171;
            Bool hoisted__Bool_4172 = I64_eq(_forin_err_kind_4164, hoisted__I64_4171);
            (void)hoisted__Bool_4172;
            Bool hoisted__Bool_4173 = not(hoisted__Bool_4172);
            (void)hoisted__Bool_4173;
            if (hoisted__Bool_4173) {
                U32 hoisted__U32_4166 = 1;
                (void)hoisted__U32_4166;
                Array__Str *_va_Array_155 = Array__Str_new(hoisted__U32_4166);
                (void)_va_Array_155;
                U32 hoisted__U32_4167 = 0;
                (void)hoisted__U32_4167;
                Str hoisted__Str_4168 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4168;
                Array__Str_set(_va_Array_155, hoisted__U32_4167, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4168; _oa; }));
                Str hoisted__Str_4169 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4169;
                panic(&hoisted__Str_4169, _va_Array_155);
                Str_delete(&hoisted__Str_4169, (Bool){0});
            }
            U32 hoisted__U32_4174 = 1;
            (void)hoisted__U32_4174;
            U32 hoisted__U32_4175 = U32_add(_fi_USize_4164, hoisted__U32_4174);
            (void)hoisted__U32_4175;
            _fi_USize_4164 = hoisted__U32_4175;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4164, 1);
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Bool is_null(void * p) {
    Bool hoisted__Bool_4213 = ptr_eq(p, NULL);
    (void)hoisted__Bool_4213;
    return hoisted__Bool_4213;
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

Range Range_clone(Range val) {
    Range hoisted__Range_4222 = (Range){.start = val.start, .end = val.end};
    (void)hoisted__Range_4222;
    return hoisted__Range_4222;
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range self, HashFn hasher) {
    U32 hoisted__U32_4223 = 0;
    (void)hoisted__U32_4223;
    U64 hoisted__U64_4224 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_4223); });
    (void)hoisted__U64_4224;
    return hoisted__U64_4224;
}

U32 Range_size(void) {
    U32 hoisted__U32_4225 = 2;
    (void)hoisted__U32_4225;
    return hoisted__U32_4225;
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_4463 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4463;
    I64 hoisted__I64_4464 = 3;
    (void)hoisted__I64_4464;
    assert_eq(&hoisted__Str_4463, result, hoisted__I64_4464);
    Str_delete(&hoisted__Str_4463, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4471 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4471;
    I64 hoisted__I64_4472 = 15;
    (void)hoisted__I64_4472;
    assert_eq(&hoisted__Str_4471, result, hoisted__I64_4472);
    Str_delete(&hoisted__Str_4471, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4479 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4479;
    I64 hoisted__I64_4480 = 26;
    (void)hoisted__I64_4480;
    assert_eq(&hoisted__Str_4479, result, hoisted__I64_4480);
    Str_delete(&hoisted__Str_4479, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4483 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4483;
    Str hoisted__Str_4484 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4484;
    assert_eq_str(&hoisted__Str_4483, &result, &hoisted__Str_4484);
    Str_delete(&hoisted__Str_4483, (Bool){0});
    Str_delete(&hoisted__Str_4484, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4815 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4815;
    assert_eq_str(&hoisted__Str_4815, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4815, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4816 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4816;
    assert_eq_str(&hoisted__Str_4816, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4816, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4818 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4818;
    I64 hoisted__I64_4819 = 8;
    (void)hoisted__I64_4819;
    assert_eq(&hoisted__Str_4818, result, hoisted__I64_4819);
    Str_delete(&hoisted__Str_4818, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4822 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4822;
    Bool hoisted__Bool_4823 = 1;
    (void)hoisted__Bool_4823;
    assert(&hoisted__Str_4822, hoisted__Bool_4823);
    Str_delete(&hoisted__Str_4822, (Bool){0});
    Str hoisted__Str_4826 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4826;
    Bool hoisted__Bool_4827 = 1;
    (void)hoisted__Bool_4827;
    assert(&hoisted__Str_4826, hoisted__Bool_4827);
    Str_delete(&hoisted__Str_4826, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4832 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4832;
    Str hoisted__Str_4833 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4833;
    Str hoisted__Str_4834 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4834;
    assert_eq_str(&hoisted__Str_4832, &hoisted__Str_4833, &hoisted__Str_4834);
    Str_delete(&hoisted__Str_4832, (Bool){0});
    Str_delete(&hoisted__Str_4833, (Bool){0});
    Str_delete(&hoisted__Str_4834, (Bool){0});
    Str hoisted__Str_4837 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4837;
    Str hoisted__Str_4838 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4838;
    Str hoisted__Str_4839 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4839;
    assert_eq_str(&hoisted__Str_4837, &hoisted__Str_4838, &hoisted__Str_4839);
    Str_delete(&hoisted__Str_4837, (Bool){0});
    Str_delete(&hoisted__Str_4838, (Bool){0});
    Str_delete(&hoisted__Str_4839, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4844 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4844;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4844;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_4845 = 0;
    (void)hoisted__U32_4845;
    U64 hoisted__U64_4846 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4845); });
    (void)hoisted__U64_4846;
    return hoisted__U64_4846;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4847 = 16;
    (void)hoisted__U32_4847;
    return hoisted__U32_4847;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4848 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4848;
    I64 hoisted__I64_4849 = 42;
    (void)hoisted__I64_4849;
    assert_eq(&hoisted__Str_4848, v.x, hoisted__I64_4849);
    Str_delete(&hoisted__Str_4848, (Bool){0});
    Str hoisted__Str_4850 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4850;
    I64 hoisted__I64_4851 = 99;
    (void)hoisted__I64_4851;
    assert_eq(&hoisted__Str_4850, v.y, hoisted__I64_4851);
    Str_delete(&hoisted__Str_4850, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4854 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4854;
    I64 hoisted__I64_4855 = 10;
    (void)hoisted__I64_4855;
    assert_eq(&hoisted__Str_4854, p.x, hoisted__I64_4855);
    Str_delete(&hoisted__Str_4854, (Bool){0});
    Str hoisted__Str_4856 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4856;
    I64 hoisted__I64_4857 = 20;
    (void)hoisted__I64_4857;
    assert_eq(&hoisted__Str_4856, p.y, hoisted__I64_4857);
    Str_delete(&hoisted__Str_4856, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4863 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4863;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4863;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_4864 = 0;
    (void)hoisted__U32_4864;
    U64 hoisted__U64_4865 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4864); });
    (void)hoisted__U64_4865;
    return hoisted__U64_4865;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4866 = 32;
    (void)hoisted__U32_4866;
    return hoisted__U32_4866;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4867 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4867;
    I64 hoisted__I64_4868 = 5;
    (void)hoisted__I64_4868;
    assert_eq(&hoisted__Str_4867, r.top_left.x, hoisted__I64_4868);
    Str_delete(&hoisted__Str_4867, (Bool){0});
    Str hoisted__Str_4869 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4869;
    I64 hoisted__I64_4870 = 10;
    (void)hoisted__I64_4870;
    assert_eq(&hoisted__Str_4869, r.top_left.y, hoisted__I64_4870);
    Str_delete(&hoisted__Str_4869, (Bool){0});
    Str hoisted__Str_4871 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4871;
    I64 hoisted__I64_4872 = 100;
    (void)hoisted__I64_4872;
    assert_eq(&hoisted__Str_4871, r.bottom_right.x, hoisted__I64_4872);
    Str_delete(&hoisted__Str_4871, (Bool){0});
    Str hoisted__Str_4873 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4873;
    I64 hoisted__I64_4874 = 200;
    (void)hoisted__I64_4874;
    assert_eq(&hoisted__Str_4873, r.bottom_right.y, hoisted__I64_4874);
    Str_delete(&hoisted__Str_4873, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_4876 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_4876;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_4876;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_4877 = 0;
    (void)hoisted__U32_4877;
    U64 hoisted__U64_4878 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_4877); });
    (void)hoisted__U64_4878;
    return hoisted__U64_4878;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_4879 = 12;
    (void)hoisted__U32_4879;
    return hoisted__U32_4879;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_4883 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4883;
    Str *hoisted__Str_4884 = F32_to_str(v.x);
    (void)hoisted__Str_4884;
    Str hoisted__Str_4885 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4885;
    assert_eq_str(&hoisted__Str_4883, hoisted__Str_4884, &hoisted__Str_4885);
    Str_delete(&hoisted__Str_4883, (Bool){0});
    Str_delete(hoisted__Str_4884, 1);
    Str_delete(&hoisted__Str_4885, (Bool){0});
    Str hoisted__Str_4886 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4886;
    Str *hoisted__Str_4887 = F32_to_str(v.y);
    (void)hoisted__Str_4887;
    Str hoisted__Str_4888 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4888;
    assert_eq_str(&hoisted__Str_4886, hoisted__Str_4887, &hoisted__Str_4888);
    Str_delete(&hoisted__Str_4886, (Bool){0});
    Str_delete(hoisted__Str_4887, 1);
    Str_delete(&hoisted__Str_4888, (Bool){0});
    Str hoisted__Str_4889 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4889;
    Str *hoisted__Str_4890 = F32_to_str(v.z);
    (void)hoisted__Str_4890;
    Str hoisted__Str_4891 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4891;
    assert_eq_str(&hoisted__Str_4889, hoisted__Str_4890, &hoisted__Str_4891);
    Str_delete(&hoisted__Str_4889, (Bool){0});
    Str_delete(hoisted__Str_4890, 1);
    Str_delete(&hoisted__Str_4891, (Bool){0});
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
    Bool hoisted__Bool_4896 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4896;
    if (hoisted__Bool_4896) {
        Bool hoisted__Bool_4893 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4893;
        { Bool _ret_val = hoisted__Bool_4893;
                return _ret_val; }
    }
    Bool hoisted__Bool_4897 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4897;
    if (hoisted__Bool_4897) {
        Bool hoisted__Bool_4894 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4894;
        { Bool _ret_val = hoisted__Bool_4894;
                return _ret_val; }
    }
    Bool hoisted__Bool_4898 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4898;
    if (hoisted__Bool_4898) {
        Bool hoisted__Bool_4895 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4895;
        { Bool _ret_val = hoisted__Bool_4895;
                return _ret_val; }
    }
    Bool hoisted__Bool_4899 = 0;
    (void)hoisted__Bool_4899;
    return hoisted__Bool_4899;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4907 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4907;
    if (hoisted__Bool_4907) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4908 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4908;
    if (hoisted__Bool_4908) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4909 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4909;
    if (hoisted__Bool_4909) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4910 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4910;
    UNREACHABLE(&hoisted__Str_4910);
    Str_delete(&hoisted__Str_4910, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4911 = 4;
    (void)hoisted__U32_4911;
    return hoisted__U32_4911;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4912 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4912;
    Bool hoisted__Bool_4913 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4913;
    assert(&hoisted__Str_4912, hoisted__Bool_4913);
    Str_delete(&hoisted__Str_4912, (Bool){0});
    Bool hoisted__Bool_4914 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4914;
    Str hoisted__Str_4915 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4915;
    Bool hoisted__Bool_4916 = not(hoisted__Bool_4914);
    (void)hoisted__Bool_4916;
    assert(&hoisted__Str_4915, hoisted__Bool_4916);
    Str_delete(&hoisted__Str_4915, (Bool){0});
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
    Bool hoisted__Bool_4917 = is(self, other);
    (void)hoisted__Bool_4917;
    return hoisted__Bool_4917;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4935 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4935;
    if (hoisted__Bool_4935) {
        I64 *hoisted__I64_4931 = get_payload(self);
        (void)hoisted__I64_4931;
        (void)hoisted__I64_4931;
        Bool hoisted__Bool_4932 = 0;
        (void)hoisted__Bool_4932;
        I64_delete(hoisted__I64_4931, hoisted__Bool_4932);
    }
    Bool hoisted__Bool_4936 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4936;
    if (hoisted__Bool_4936) {
        Str *hoisted__Str_4933 = get_payload(self);
        (void)hoisted__Str_4933;
        (void)hoisted__Str_4933;
        Bool hoisted__Bool_4934 = 0;
        (void)hoisted__Bool_4934;
        Str_delete(hoisted__Str_4933, hoisted__Bool_4934);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4961 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4961;
    if (hoisted__Bool_4961) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4958 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4958;
        { Token * _ret_val = hoisted__Token_4958;
                return _ret_val; }
    }
    Bool hoisted__Bool_4962 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4962;
    if (hoisted__Bool_4962) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4959 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4959;
        Token *hoisted__Token_4960 = Token_Name(hoisted__Str_4959);
        (void)hoisted__Token_4960;
        { Token * _ret_val = hoisted__Token_4960;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4963 = 24;
    (void)hoisted__U32_4963;
    return hoisted__U32_4963;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4965 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4965;
    Bool hoisted__Bool_4966 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4966;
    assert(&hoisted__Str_4965, hoisted__Bool_4966);
    Str_delete(&hoisted__Str_4965, (Bool){0});
    Bool hoisted__Bool_4967 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4967;
    Str hoisted__Str_4968 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4968;
    Bool hoisted__Bool_4969 = not(hoisted__Bool_4967);
    (void)hoisted__Bool_4969;
    assert(&hoisted__Str_4968, hoisted__Bool_4969);
    Str_delete(&hoisted__Str_4968, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_4970 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4970;
    Bool hoisted__Bool_4971 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4971;
    assert(&hoisted__Str_4970, hoisted__Bool_4971);
    Str_delete(&hoisted__Str_4970, (Bool){0});
    Bool hoisted__Bool_4972 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4972;
    Str hoisted__Str_4973 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4973;
    Bool hoisted__Bool_4974 = not(hoisted__Bool_4972);
    (void)hoisted__Bool_4974;
    assert(&hoisted__Str_4973, hoisted__Bool_4974);
    Str_delete(&hoisted__Str_4973, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4977 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4977;
    Bool hoisted__Bool_4978 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4978;
    assert(&hoisted__Str_4977, hoisted__Bool_4978);
    Str_delete(&hoisted__Str_4977, (Bool){0});
    Bool hoisted__Bool_4979 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4979;
    Str hoisted__Str_4980 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4980;
    Bool hoisted__Bool_4981 = not(hoisted__Bool_4979);
    (void)hoisted__Bool_4981;
    assert(&hoisted__Str_4980, hoisted__Bool_4981);
    Str_delete(&hoisted__Str_4980, (Bool){0});
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
void *Vec_new_type_name_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec_new_type_name(_a0);
}
static __attribute__((unused)) TilClosure Vec_new_type_name_dyn__til_closure = { (void *)Vec_new_type_name_dyn, NULL, NULL };
void *Vec_new_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec_new(_a0);
}
static __attribute__((unused)) TilClosure Vec_new_dyn__til_closure = { (void *)Vec_new_dyn, NULL, NULL };
void Vec_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Vec_clear(_a0);
}
static __attribute__((unused)) TilClosure Vec_clear_dyn__til_closure = { (void *)Vec_clear_dyn, NULL, NULL };
void Vec_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Vec_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Vec_delete_dyn__til_closure = { (void *)Vec_delete_dyn, NULL, NULL };
void *Vec_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Vec_clone(_a0);
}
static __attribute__((unused)) TilClosure Vec_clone_dyn__til_closure = { (void *)Vec_clone_dyn, NULL, NULL };
U32 Vec_size_dyn(void *til_env) {
    (void)til_env;
    return Vec_size();
}
static __attribute__((unused)) TilClosure Vec_size_dyn__til_closure = { (void *)Vec_size_dyn, NULL, NULL };
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
Bool Str_is_empty_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Str_is_empty(_a0);
}
static __attribute__((unused)) TilClosure Str_is_empty_dyn__til_closure = { (void *)Str_is_empty_dyn, NULL, NULL };
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
void *Map_new_type_names_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Map_new_type_names(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map_new_type_names_dyn__til_closure = { (void *)Map_new_type_names_dyn, NULL, NULL };
void *Map_new_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Map_new(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map_new_dyn__til_closure = { (void *)Map_new_dyn, NULL, NULL };
void Map_clear_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Map_clear(_a0);
}
static __attribute__((unused)) TilClosure Map_clear_dyn__til_closure = { (void *)Map_clear_dyn, NULL, NULL };
void Map_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Map_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map_delete_dyn__til_closure = { (void *)Map_delete_dyn, NULL, NULL };
void *Map_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Map_clone(_a0);
}
static __attribute__((unused)) TilClosure Map_clone_dyn__til_closure = { (void *)Map_clone_dyn, NULL, NULL };
U64 Map_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Map_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Map_hash_dyn__til_closure = { (void *)Map_hash_dyn, NULL, NULL };
U32 Map_size_dyn(void *til_env) {
    (void)til_env;
    return Map_size();
}
static __attribute__((unused)) TilClosure Map_size_dyn__til_closure = { (void *)Map_size_dyn, NULL, NULL };
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
void *Range_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Range *_r = malloc(sizeof(Range)); *_r = Range_clone(*(Range *)_a0); return _r;
}
static __attribute__((unused)) TilClosure Range_clone_dyn__til_closure = { (void *)Range_clone_dyn, NULL, NULL };
void Range_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Range_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Range_delete_dyn__til_closure = { (void *)Range_delete_dyn, NULL, NULL };
U64 Range_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Range_hash(*(Range *)_a0, _a1);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "new_type_name", 13ULL) == 0) return (void*)&Vec_new_type_name_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Vec_new_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Vec_clear_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Vec_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Vec_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Vec_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Str_len_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)&Str_get_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Str_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)&Str_with_capacity_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)&Str_push_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Str_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Str_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)&Str_is_empty_dyn__til_closure;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 14ULL && memcmp(method->c_str, "new_type_names", 14ULL) == 0) return (void*)&Map_new_type_names_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Map_new_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clear", 5ULL) == 0) return (void*)&Map_clear_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Map_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Map_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Map_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Map_size_dyn__til_closure;
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

Bool dyn_has_cmp(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return 1;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) return 1;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return 1;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return 1;
    return 0;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return sizeof(Vec);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) return sizeof(OutOfBounds);
    if (type_name->count == 10ULL && memcmp(type_name->c_str, "Array__Str", 10ULL) == 0) return sizeof(Array__Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return sizeof(I64);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return sizeof(Bool);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) return sizeof(Map);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) {
        return 7LL;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) {
        return 3LL;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_size", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_kind", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_clone", .count = 10ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_delete", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"keys", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"values", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"key_cmp", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CloneFn", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"DeleteFn", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CmpFn", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"OwnType", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Map", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Expr", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"NodeType", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Vec", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        return 1LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "CmpFn", 5ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 2LL;
    }
    fprintf(stderr, "func_sig_param_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_param_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "CmpFn", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "func_sig_param_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_return_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        return 1LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "CmpFn", 5ULL) == 0) {
        return 1LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 1LL;
    }
    fprintf(stderr, "func_sig_return_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_return_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "CmpFn", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "func_sig_return_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_throw_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "CmpFn", 5ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 0LL;
    }
    fprintf(stderr, "func_sig_throw_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_throw_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "CmpFn", 5ULL) == 0) {
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
    }
    fprintf(stderr, "func_sig_throw_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *dyn_type_to_str(Type *type) {
    static Str _dts_0 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_1 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_2 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_3 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_4 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_5 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_6 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_7 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_8 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_9 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_10 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_11 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_12 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_13 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_14 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_15 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_16 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_STATIC};
    switch (type->tag) {
    case Type_TAG_Unknown: return &_dts_0;
    case Type_TAG_None: return &_dts_0;
    case Type_TAG_Struct: return Str_clone(&type->data.Struct);
    case Type_TAG_StructDef: return &_dts_1;
    case Type_TAG_Enum: return Str_clone(&type->data.Enum);
    case Type_TAG_EnumDef: return &_dts_2;
    case Type_TAG_FuncDef: return &_dts_3;
    case Type_TAG_FuncPtr: return &_dts_4;
    case Type_TAG_Dynamic: return &_dts_5;
    case Type_TAG_Custom: return Str_clone(&type->data.Custom);
    case Type_TAG_Primitive:
        switch (type->data.Primitive.tag) {
        case Primitive_TAG_I16: return &_dts_6;
        case Primitive_TAG_U16: return &_dts_7;
        case Primitive_TAG_I8: return &_dts_8;
        case Primitive_TAG_U8: return &_dts_9;
        case Primitive_TAG_U32: return &_dts_10;
        case Primitive_TAG_I32: return &_dts_11;
        case Primitive_TAG_U64: return &_dts_12;
        case Primitive_TAG_I64: return &_dts_13;
        case Primitive_TAG_F32: return &_dts_14;
        case Primitive_TAG_Bool: return &_dts_15;
        }
        break;
    case Type_TAG_FuncPtrSig: return Str_clone(&type->data.FuncPtrSig);
    default: break;
    }
    return &_dts_16;
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
