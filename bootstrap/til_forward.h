#pragma once
#include "aliases.h"
#include <stdbool.h>

typedef struct Dynamic Dynamic;
typedef struct Range Range;
typedef struct Array Array;
typedef struct Set Set;
typedef struct Str Str;
typedef struct Vec Vec;
typedef struct Expr Expr;
typedef struct Token Token;
typedef struct Mode Mode;
typedef struct TypeScope TypeScope;

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


typedef struct Expr {
    char _;
} Expr;


typedef struct Token {
    char _;
} Token;


typedef struct Mode {
    char _;
} Mode;


typedef struct TypeScope {
    char _;
} TypeScope;


typedef struct Array {
    U8 *data;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Array;


typedef struct Set {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Set;


Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
void println(Array * parts);
Str * format(Array * parts);
void panic(Str * loc_str, Array * parts);
Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U64 * Set_size(void);
U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_rfind(Str * self, Str * needle);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
Expr * Expr_clone(Expr * self);
void Expr_delete(Expr * self, Bool * call_free);
U64 * Expr_size(void);
Token * Token_clone(Token * self);
void Token_delete(Token * self, Bool * call_free);
U64 * Token_size(void);
Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
Vec * extract_imports(void * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir);
void usage(void);
void mark_core(void * e);
void main(Array * args);

