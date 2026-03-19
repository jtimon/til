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
typedef enum {
    TokenType_TAG_Eof,
    TokenType_TAG_LParen,
    TokenType_TAG_RParen,
    TokenType_TAG_LBrace,
    TokenType_TAG_RBrace,
    TokenType_TAG_LBracket,
    TokenType_TAG_RBracket,
    TokenType_TAG_Comma,
    TokenType_TAG_Colon,
    TokenType_TAG_Question,
    TokenType_TAG_Bang,
    TokenType_TAG_Minus,
    TokenType_TAG_Plus,
    TokenType_TAG_Star,
    TokenType_TAG_Slash,
    TokenType_TAG_Dot,
    TokenType_TAG_DotDot,
    TokenType_TAG_DotDotDot,
    TokenType_TAG_Eq,
    TokenType_TAG_EqEq,
    TokenType_TAG_Neq,
    TokenType_TAG_Lt,
    TokenType_TAG_LtEq,
    TokenType_TAG_Gt,
    TokenType_TAG_GtEq,
    TokenType_TAG_ColonEq,
    TokenType_TAG_Ident,
    TokenType_TAG_StringTok,
    TokenType_TAG_Number,
    TokenType_TAG_Char,
    TokenType_TAG_KwMode,
    TokenType_TAG_KwMut,
    TokenType_TAG_KwOwn,
    TokenType_TAG_KwRef,
    TokenType_TAG_KwShallow,
    TokenType_TAG_KwStruct,
    TokenType_TAG_KwExtStruct,
    TokenType_TAG_KwEnum,
    TokenType_TAG_KwNamespace,
    TokenType_TAG_KwFunc,
    TokenType_TAG_KwProc,
    TokenType_TAG_KwTest,
    TokenType_TAG_KwMacro,
    TokenType_TAG_KwExtFunc,
    TokenType_TAG_KwExtProc,
    TokenType_TAG_KwReturns,
    TokenType_TAG_KwThrows,
    TokenType_TAG_KwIf,
    TokenType_TAG_KwElse,
    TokenType_TAG_KwWhile,
    TokenType_TAG_KwFor,
    TokenType_TAG_KwIn,
    TokenType_TAG_KwSwitch,
    TokenType_TAG_KwMatch,
    TokenType_TAG_KwCase,
    TokenType_TAG_KwDefault,
    TokenType_TAG_KwReturn,
    TokenType_TAG_KwThrow,
    TokenType_TAG_KwCatch,
    TokenType_TAG_KwBreak,
    TokenType_TAG_KwContinue,
    TokenType_TAG_KwDefer,
    TokenType_TAG_KwTrue,
    TokenType_TAG_KwFalse,
    TokenType_TAG_KwNull,
    TokenType_TAG_Error
} TokenType_tag;
typedef struct TokenType TokenType;
typedef struct Token Token;
typedef struct Parser Parser;
typedef struct Mode Mode;

