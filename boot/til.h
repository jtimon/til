#pragma once
#include "ext.h"
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
typedef struct TypeBinding TypeBinding;
typedef struct TypeScope TypeScope;
typedef struct LocalInfo LocalInfo;
typedef struct CollectionInfo CollectionInfo;
typedef struct DynCallInfo DynCallInfo;
typedef struct ExtStr ExtStr;
typedef struct Mode Mode;

typedef struct StructDef {
    char _;
} StructDef;


typedef struct EnumDef {
    char _;
} EnumDef;


typedef struct Dynamic {
    char _;
} Dynamic;









typedef struct Range {
    U64 start;
    U64 end;
} Range;



typedef struct Str {
    U8 *c_str;
    U64 count;
    U64 cap;
} Str;


typedef struct Vec {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Vec;


typedef struct Tuple {
    U8 *data;
    U64 total_size;
    U64 cap;
    Vec type_names;
    Vec type_sizes;
} Tuple;


struct TilType {
    TilType_tag tag;
};

typedef struct Declaration {
    Str name;
    Str explicit_type;
    Bool is_mut;
    Bool is_namespace;
    Bool is_ref;
    Bool is_own;
    I32 field_offset;
    I32 field_size;
    Expr *field_struct_def;
    Expr *fn_sig;
} Declaration;


struct FuncType {
    FuncType_tag tag;
};

typedef struct Param {
    Str name;
    Str ptype;
    Bool is_mut;
    Bool is_own;
    Bool is_shallow;
} Param;


struct TokenType {
    TokenType_tag tag;
};

typedef struct Token {
    TokenType type;
    Str text;
    U32 line;
    U32 col;
} Token;


typedef struct Parser {
    Vec tokens;
    U64 pos;
    Str path;
    Vec fn_sig_decls;
} Parser;


typedef struct TypeBinding {
    Str *name;
    TilType type;
    I32 is_proc;
    Bool is_mut;
    U32 line;
    U32 col;
    Bool is_param;
    Bool is_own;
    Bool is_ref;
    Bool is_alias;
    Bool is_type_alias;
    Str *alias_target;
    Expr *struct_def;
    Expr *func_def;
    Bool is_builtin;
    Bool is_ext;
    Str *struct_name;
} TypeBinding;


typedef struct LocalInfo {
    Str *name;
    TilType type;
    Str *struct_name;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_delete;
} LocalInfo;


typedef struct CollectionInfo {
    Str *type_name;
    I32 is_vec;
} CollectionInfo;


typedef struct DynCallInfo {
    Str *method;
    I32 nargs;
    Bool has_return;
} DynCallInfo;


typedef struct ExtStr {
    U8 *data;
    U64 count;
    U64 cap;
} ExtStr;


typedef struct Mode {
    Str name;
    Bool needs_main;
    Bool decls_only;
    Str auto_import;
    Bool is_pure;
    Bool debug_prints;
} Mode;


typedef struct Array {
    U8 *data;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Array;


typedef struct Map {
    U8 *key_data;
    U8 *val_data;
    U64 count;
    U64 cap;
    U64 key_size;
    Str key_type;
    U64 val_size;
    Str val_type;
} Map;


typedef struct Set {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Set;


typedef struct FunctionDef {
    FuncType func_type;
    Vec params;
    U32 nparam;
    Map param_defaults;
    Str return_type;
    I32 variadic_index;
    I32 kwargs_index;
    Bool return_is_ref;
    Bool return_is_shallow;
} FunctionDef;


struct ExprData {
    ExprData_tag tag;
    union {
        Str LiteralStr;
        Str LiteralNum;
        Str LiteralBool;
        Str Ident;
        Declaration Decl;
        Str Assign;
        FunctionDef FuncDef;
        Str FieldAccess;
        Str FieldAssign;
        Str ForIn;
        Str NamedArg;
    } data;
};

typedef struct Expr {
    ExprData data;
    TilType til_type;
    Str struct_name;
    Bool is_own_arg;
    Bool is_splat;
    Bool is_own_field;
    Bool is_ref_field;
    Bool is_ns_field;
    Bool is_ext;
    Bool is_core;
    Bool save_old_delete;
    I32 total_struct_size;
    I32 variadic_index;
    U32 variadic_count;
    I32 kwargs_index;
    U32 kwargs_count;
    Expr *fn_sig;
    Vec children;
    U32 line;
    U32 col;
    Str path;
} Expr;


typedef struct TypeScope {
    Map bindings;
    TypeScope *parent;
} TypeScope;


EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U64 * EnumDef_size(void);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
void println(Array * parts);
void print(Array * parts);
Str * format(Array * parts);
void * default_clone(void * v);
void default_delete(void * v, Bool * cf);
I64 * default_cmp(void * a, void * b);
void swap(void * a, void * b, U64 size);
void move(void * dest, void * src, U64 size);
I64 * wait_cmd(I64 * pid);
I64 * run_cmd(Str * output, Array * args);
void panic(Str * loc_str, Array * parts);
void TODO(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool * assert(Str * loc_str, Bool * cond);
void expect(Str * loc_str, Bool * cond, Array * parts);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size);
U64 * Map_len(Map * self);
Bool * Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U64 * Map_size(void);
Set * Set_new(Str * elem_type, U64 * elem_size);
U64 * Set_len(Set * self);
Bool * Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U64 * Set_size(void);
U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
U8 * Str_byte_at(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(U64 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_contains(Str * a, Str * b);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_find(Str * self, Str * needle);
I64 * Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, U64 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 * Str_to_i64(Str * self);
Vec * Str_split(Str * self, Str * delim);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Bool * Str_lt(Str * a, Str * b);
Bool * Str_gt(Str * a, Str * b);
Bool * Str_neq(Str * a, Str * b);
Bool * Str_lte(Str * a, Str * b);
Bool * Str_gte(Str * a, Str * b);
Str * join(Vec * parts, Str * sep);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
Tuple * Tuple_new(void);
U64 * Tuple_len(Tuple * self);
void Tuple_push(Tuple * self, Str * elem_type, U64 * elem_size, void * val);
void * Tuple_get(Tuple * self, U64 * i);
Str * Tuple_type_at(Tuple * self, U64 * i);
U64 * Tuple_size_at(Tuple * self, U64 * i);
void Tuple_delete(Tuple * self, Bool * call_free);
Tuple * Tuple_clone(Tuple * self);
U64 * Tuple_size(void);
Bool * TilType_eq(TilType * self, TilType * other);
TilType * TilType_clone(TilType * self);
void TilType_delete(TilType * self, Bool * call_free);
Str * TilType_to_str(TilType * self);
U64 * TilType_size(void);
Str * til_type_name_c(TilType * t);
Bool * Declaration_eq(Declaration * a, Declaration * b);
Str * Declaration_to_str(Declaration * self);
Declaration * Declaration_clone(Declaration * self);
void Declaration_delete(Declaration * self, Bool * call_free);
U64 * Declaration_size(void);
Bool * FuncType_eq(FuncType * self, FuncType * other);
FuncType * FuncType_clone(FuncType * self);
void FuncType_delete(FuncType * self, Bool * call_free);
Str * FuncType_to_str(FuncType * self);
U64 * FuncType_size(void);
Param * Param_clone(Param * self);
void Param_delete(Param * self, Bool * call_free);
U64 * Param_size(void);
Bool * FunctionDef_eq(FunctionDef * a, FunctionDef * b);
Str * FunctionDef_to_str(FunctionDef * self);
FunctionDef * FunctionDef_clone(FunctionDef * self);
void FunctionDef_delete(FunctionDef * self, Bool * call_free);
U64 * FunctionDef_size(void);
Bool * ExprData_eq(ExprData * self, ExprData * other);
ExprData * ExprData_clone(ExprData * self);
void ExprData_delete(ExprData * self, Bool * call_free);
Str * ExprData_to_str(ExprData * self);
U64 * ExprData_size(void);
void Expr_error(Expr * self, Str * msg);
void Expr_todo_error(Expr * self, Str * msg);
void Expr_lang_error(Expr * self, Str * msg);
void Expr_add_child(Expr * self, Expr * child);
Expr * Expr_child(Expr * parent, I64 * i);
I64 * Expr_child_count(Expr * parent);
Expr * Expr_new(ExprData * data, U32 line, U32 col, Str * path);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U64 * Expr_size(void);
Str * node_name(ExprData * data);
Str * func_type_name(FuncType * ft);
void ast_print(Expr * e, U32 indent);
Bool * enum_has_payloads(Expr * enum_def);
I32 * enum_variant_tag(Expr * enum_def, Str * variant_name);
Str * enum_variant_type(Expr * enum_def, I32 tag);
Bool * TokenType_eq(TokenType * self, TokenType * other);
TokenType * TokenType_clone(TokenType * self);
void TokenType_delete(TokenType * self, Bool * call_free);
Str * TokenType_to_str(TokenType * self);
U64 * TokenType_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U64 * Token_size(void);
Bool * is_digit(U8 * c);
Bool * is_alpha(U8 * c);
Bool * is_alnum(U8 * c);
Str * tok_name(TokenType * type);
TokenType * lookup_keyword(Str * word);
Vec * tokenize(Str * src, Str * path);
Parser * Parser_clone(Parser * self);
void Parser_delete(Parser * self, Bool * call_free);
U64 * Parser_size(void);
Token * peek(Parser * p);
Token * advance(Parser * p);
Bool check(Parser * p, TokenType * type);
Token * expect_token(Parser * p, TokenType * type);
Str * expect_text(Parser * p, TokenType * type);
U32 peek_line(Parser * p);
U32 peek_col(Parser * p);
Str * parse_fn_signature(Parser * p, U32 line, U32 col);
Expr * parse_block(Parser * p);
Expr * parse_func_def(Parser * p);
Expr * parse_struct_def(Parser * p);
Expr * parse_enum_def(Parser * p);
Expr * parse_call(Parser * p, Str * name, U32 call_line, U32 call_col);
Expr * parse_expression(Parser * p);
Expr * parse_statement_ident(Parser * p, Bool is_mut, Bool is_own);
Expr * parse_statement(Parser * p);
Expr * parse(Vec * tokens, Str * path, Str * mode_out);
TypeBinding * TypeBinding_clone(TypeBinding * self);
void TypeBinding_delete(TypeBinding * self, Bool * call_free);
U64 * TypeBinding_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
LocalInfo * LocalInfo_clone(LocalInfo * self);
void LocalInfo_delete(LocalInfo * self, Bool * call_free);
U64 * LocalInfo_size(void);
CollectionInfo * CollectionInfo_clone(CollectionInfo * self);
void CollectionInfo_delete(CollectionInfo * self, Bool * call_free);
U64 * CollectionInfo_size(void);
DynCallInfo * DynCallInfo_clone(DynCallInfo * self);
void DynCallInfo_delete(DynCallInfo * self, Bool * call_free);
U64 * DynCallInfo_size(void);
ExtStr * ExtStr_clone(ExtStr * self);
void ExtStr_delete(ExtStr * self, Bool * call_free);
U64 * ExtStr_size(void);
Bool * Mode_eq(Mode * a, Mode * b);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
Mode * mode_resolve(Str * name);
Bool * mode_is_lib(Mode * m);
Bool * mode_is_lib_output(Mode * m);
Vec * extract_imports(void * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir);
void usage(void);
void mark_core(Expr * e);
Bool * TokenType_eq(TokenType *, TokenType *);
TokenType *TokenType_Eof();
TokenType *TokenType_LParen();
TokenType *TokenType_RParen();
TokenType *TokenType_LBrace();
TokenType *TokenType_RBrace();
TokenType *TokenType_LBracket();
TokenType *TokenType_RBracket();
TokenType *TokenType_Comma();
TokenType *TokenType_Colon();
TokenType *TokenType_Question();
TokenType *TokenType_Bang();
TokenType *TokenType_Minus();
TokenType *TokenType_Plus();
TokenType *TokenType_Star();
TokenType *TokenType_Slash();
TokenType *TokenType_Dot();
TokenType *TokenType_DotDot();
TokenType *TokenType_DotDotDot();
TokenType *TokenType_Eq();
TokenType *TokenType_EqEq();
TokenType *TokenType_Neq();
TokenType *TokenType_Lt();
TokenType *TokenType_LtEq();
TokenType *TokenType_Gt();
TokenType *TokenType_GtEq();
TokenType *TokenType_ColonEq();
TokenType *TokenType_Ident();
TokenType *TokenType_StringTok();
TokenType *TokenType_Number();
TokenType *TokenType_Char();
TokenType *TokenType_KwMode();
TokenType *TokenType_KwMut();
TokenType *TokenType_KwOwn();
TokenType *TokenType_KwRef();
TokenType *TokenType_KwShallow();
TokenType *TokenType_KwStruct();
TokenType *TokenType_KwExtStruct();
TokenType *TokenType_KwEnum();
TokenType *TokenType_KwNamespace();
TokenType *TokenType_KwFunc();
TokenType *TokenType_KwProc();
TokenType *TokenType_KwTest();
TokenType *TokenType_KwMacro();
TokenType *TokenType_KwExtFunc();
TokenType *TokenType_KwExtProc();
TokenType *TokenType_KwReturns();
TokenType *TokenType_KwThrows();
TokenType *TokenType_KwIf();
TokenType *TokenType_KwElse();
TokenType *TokenType_KwWhile();
TokenType *TokenType_KwFor();
TokenType *TokenType_KwIn();
TokenType *TokenType_KwSwitch();
TokenType *TokenType_KwMatch();
TokenType *TokenType_KwCase();
TokenType *TokenType_KwDefault();
TokenType *TokenType_KwReturn();
TokenType *TokenType_KwThrow();
TokenType *TokenType_KwCatch();
TokenType *TokenType_KwBreak();
TokenType *TokenType_KwContinue();
TokenType *TokenType_KwDefer();
TokenType *TokenType_KwTrue();
TokenType *TokenType_KwFalse();
TokenType *TokenType_KwNull();
TokenType *TokenType_Error();
