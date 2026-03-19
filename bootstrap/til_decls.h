#pragma once
#include "aliases.h"
#include <stdbool.h>

typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef struct Dynamic Dynamic;
typedef struct Range Range;
typedef struct Array Array;
typedef struct Map Map;
typedef struct Set Set;
typedef struct Str Str;
typedef struct Vec Vec;
typedef struct Tuple Tuple;
typedef enum {
    TilType_TAG_Unknown,
    TilType_TAG_None,
    TilType_TAG_I64,
    TilType_TAG_U8,
    TilType_TAG_I16,
    TilType_TAG_I32,
    TilType_TAG_U32,
    TilType_TAG_U64,
    TilType_TAG_F32,
    TilType_TAG_Bool,
    TilType_TAG_Struct,
    TilType_TAG_StructDef,
    TilType_TAG_Enum,
    TilType_TAG_EnumDef,
    TilType_TAG_FuncDef,
    TilType_TAG_FuncPtr,
    TilType_TAG_Dynamic
} TilType_tag;
typedef struct TilType TilType;
typedef struct Declaration Declaration;
typedef enum {
    FuncType_TAG_Func,
    FuncType_TAG_Proc,
    FuncType_TAG_Test,
    FuncType_TAG_Macro,
    FuncType_TAG_ExtFunc,
    FuncType_TAG_ExtProc
} FuncType_tag;
typedef struct FuncType FuncType;
typedef struct Param Param;
typedef struct FunctionDef FunctionDef;
typedef enum {
    ExprData_TAG_Body,
    ExprData_TAG_LiteralStr,
    ExprData_TAG_LiteralNum,
    ExprData_TAG_LiteralBool,
    ExprData_TAG_LiteralNull,
    ExprData_TAG_Ident,
    ExprData_TAG_Decl,
    ExprData_TAG_Assign,
    ExprData_TAG_FCall,
    ExprData_TAG_FuncDef,
    ExprData_TAG_StructDef,
    ExprData_TAG_EnumDef,
    ExprData_TAG_FieldAccess,
    ExprData_TAG_FieldAssign,
    ExprData_TAG_Return,
    ExprData_TAG_If,
    ExprData_TAG_While,
    ExprData_TAG_ForIn,
    ExprData_TAG_NamedArg,
    ExprData_TAG_Break,
    ExprData_TAG_Continue,
    ExprData_TAG_MapLit,
    ExprData_TAG_SetLit,
    ExprData_TAG_Switch,
    ExprData_TAG_Case
} ExprData_tag;
typedef struct ExprData ExprData;
typedef struct Expr Expr;
typedef struct Mode Mode;
typedef struct TypeScope TypeScope;

