#include "ccore.h"
#include "lexer.h"
#include "ast.h"
#include "initer.h"
#include "modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Opaque type no-ops (for ext_struct FFI) ---
Token *Token_clone(Token *t) { return t; }
void Token_delete(Token *t, Bool *call_free) { (void)t; (void)call_free; }
Expr *Expr_clone(Expr *e) { return e; }
void Expr_delete(Expr *e, Bool *call_free) { (void)e; (void)call_free; }
TypeScope *TypeScope_clone(TypeScope *s) { return s; }
void TypeScope_delete(TypeScope *s, Bool *call_free) { (void)s; (void)call_free; }
Mode *Mode_clone(Mode *m) { return m; }
void Mode_delete(Mode *m, Bool *call_free) { (void)m; (void)call_free; }

// --- I64 ---

I64 I64_add(I64 a, I64 b) { return a + b; }
I64 I64_sub(I64 a, I64 b) { return a - b; }
I64 I64_mul(I64 a, I64 b) { return a * b; }
I64 I64_div(I64 a, I64 b) { return (b == 0) ? 0 : a / b; }
I64 I64_mod(I64 a, I64 b) { return (b == 0) ? 0 : a % b; }
I64 I64_and(I64 a, I64 b) { return a & b; }
I64 I64_or(I64 a, I64 b) { return a | b; }
I64 I64_xor(I64 a, I64 b) { return a ^ b; }
I64 I64_inc(I64 a) { return a + 1; }
I64 I64_dec(I64 a) { return a - 1; }

Bool I64_eq(I64 a, I64 b) { return a == b; }
I64 I64_cmp(I64 a, I64 b) { return a < b ? -1 : (a > b ? 1 : 0); }

Str *I64_to_str(I64 v) {
    char buf[32];
    snprintf(buf, 32, "%lld", v);
    return Str_new(buf);
}

I64 *I64_new(I64 val) {
    I64 *p = malloc(sizeof(I64));
    *p = val;
    return p;
}

I64 *I64_clone(I64 *v) { return I64_new(*v); }
void I64_delete(I64 *v, Bool *call_free) { if (*call_free) free(v); }

// --- U8 ---

U8 U8_add(U8 a, U8 b) { return (U8)(a + b); }
U8 U8_sub(U8 a, U8 b) { return (U8)(a - b); }
U8 U8_mul(U8 a, U8 b) { return (U8)(a * b); }
U8 U8_div(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a / b); }
U8 U8_mod(U8 a, U8 b) { return (b == 0) ? 0 : (U8)(a % b); }
U8 U8_and(U8 a, U8 b) { return a & b; }
U8 U8_or(U8 a, U8 b) { return a | b; }
U8 U8_xor(U8 a, U8 b) { return a ^ b; }
U8 U8_inc(U8 a) { return a + 1; }
U8 U8_dec(U8 a) { return a - 1; }

Bool U8_eq(U8 a, U8 b) { return a == b; }
I64 U8_cmp(U8 a, U8 b) { return a < b ? -1 : (a > b ? 1 : 0); }

Str *U8_to_str(U8 v) {
    char buf[4];
    snprintf(buf, 4, "%u", (unsigned)v);
    return Str_new(buf);
}

I64 U8_to_i64(U8 v) { return (I64)v; }
U8 U8_from_i64(I64 v) { return (U8)v; }

U8 *U8_new(U8 val) {
    U8 *p = malloc(sizeof(U8));
    *p = val;
    return p;
}

U8 *U8_clone(U8 *v) { return U8_new(*v); }
void U8_delete(U8 *v, Bool *call_free) { if (*call_free) free(v); }

// --- I16 ---

I16 I16_add(I16 a, I16 b) { return (I16)(a + b); }
I16 I16_sub(I16 a, I16 b) { return (I16)(a - b); }
I16 I16_mul(I16 a, I16 b) { return (I16)(a * b); }
I16 I16_div(I16 a, I16 b) { return (b == 0) ? 0 : (I16)(a / b); }
I16 I16_mod(I16 a, I16 b) { return (b == 0) ? 0 : (I16)(a % b); }
I16 I16_and(I16 a, I16 b) { return a & b; }
I16 I16_or(I16 a, I16 b) { return a | b; }
I16 I16_xor(I16 a, I16 b) { return a ^ b; }
I16 I16_inc(I16 a) { return a + 1; }
I16 I16_dec(I16 a) { return a - 1; }

Bool I16_eq(I16 a, I16 b) { return a == b; }
I64 I16_cmp(I16 a, I16 b) { return a < b ? -1 : (a > b ? 1 : 0); }

I64 I16_to_i64(I16 v) { return (I64)v; }
I16 I16_from_i64(I64 v) { return (I16)v; }

I16 *I16_new(I16 val) {
    I16 *p = malloc(sizeof(I16));
    *p = val;
    return p;
}

I16 *I16_clone(I16 *v) { return I16_new(*v); }
void I16_delete(I16 *v, Bool *call_free) { if (*call_free) free(v); }

// --- I32 ---

I32 I32_add(I32 a, I32 b) { return a + b; }
I32 I32_sub(I32 a, I32 b) { return a - b; }
I32 I32_mul(I32 a, I32 b) { return a * b; }
I32 I32_div(I32 a, I32 b) { return (b == 0) ? 0 : a / b; }
I32 I32_mod(I32 a, I32 b) { return (b == 0) ? 0 : a % b; }
I32 I32_and(I32 a, I32 b) { return a & b; }
I32 I32_or(I32 a, I32 b) { return a | b; }
I32 I32_xor(I32 a, I32 b) { return a ^ b; }
I32 I32_inc(I32 a) { return a + 1; }
I32 I32_dec(I32 a) { return a - 1; }

Bool I32_eq(I32 a, I32 b) { return a == b; }
I64 I32_cmp(I32 a, I32 b) { return a < b ? -1 : (a > b ? 1 : 0); }

I64 I32_to_i64(I32 v) { return (I64)v; }
I32 I32_from_i64(I64 v) { return (I32)v; }

I32 *I32_new(I32 val) {
    I32 *p = malloc(sizeof(I32));
    *p = val;
    return p;
}

I32 *I32_clone(I32 *v) { return I32_new(*v); }
void I32_delete(I32 *v, Bool *call_free) { if (*call_free) free(v); }

// --- F32 ---

F32 F32_add(F32 a, F32 b) { return a + b; }
F32 F32_sub(F32 a, F32 b) { return a - b; }
F32 F32_mul(F32 a, F32 b) { return a * b; }
F32 F32_div(F32 a, F32 b) { return (b == 0) ? 0 : a / b; }

Bool F32_eq(F32 a, F32 b) { return a == b; }
I64 F32_cmp(F32 a, F32 b) { return a < b ? -1 : (a > b ? 1 : 0); }

I64 F32_to_i64(F32 v) { return (I64)v; }
F32 F32_from_i64(I64 v) { return (F32)v; }

Str *F32_to_str(F32 v) {
    char buf[32];
    snprintf(buf, 32, "%g", (double)v);
    return Str_new(buf);
}

F32 *F32_new(F32 val) {
    F32 *p = malloc(sizeof(F32));
    *p = val;
    return p;
}

F32 *F32_clone(F32 *v) { return F32_new(*v); }
void F32_delete(F32 *v, Bool *call_free) { if (*call_free) free(v); }

// --- U32 ---

U32 U32_add(U32 a, U32 b) { return a + b; }
U32 U32_sub(U32 a, U32 b) { return a - b; }
U32 U32_mul(U32 a, U32 b) { return a * b; }
U32 U32_div(U32 a, U32 b) { return (b == 0) ? 0 : a / b; }
U32 U32_mod(U32 a, U32 b) { return (b == 0) ? 0 : a % b; }
U32 U32_and(U32 a, U32 b) { return a & b; }
U32 U32_or(U32 a, U32 b) { return a | b; }
U32 U32_xor(U32 a, U32 b) { return a ^ b; }
U32 U32_inc(U32 a) { return a + 1; }
U32 U32_dec(U32 a) { return a - 1; }

Bool U32_eq(U32 a, U32 b) { return a == b; }
I64 U32_cmp(U32 a, U32 b) { return a < b ? -1 : (a > b ? 1 : 0); }

I64 U32_to_i64(U32 v) { return (I64)v; }
U32 U32_from_i64(I64 v) { return (U32)v; }

U32 *U32_new(U32 val) {
    U32 *p = malloc(sizeof(U32));
    *p = val;
    return p;
}

U32 *U32_clone(U32 *v) { return U32_new(*v); }
void U32_delete(U32 *v, Bool *call_free) { if (*call_free) free(v); }

// --- U64 ---

U64 U64_add(U64 a, U64 b) { return a + b; }
U64 U64_sub(U64 a, U64 b) { return a - b; }
U64 U64_mul(U64 a, U64 b) { return a * b; }
U64 U64_div(U64 a, U64 b) { return (b == 0) ? 0 : a / b; }
U64 U64_mod(U64 a, U64 b) { return (b == 0) ? 0 : a % b; }
U64 U64_and(U64 a, U64 b) { return a & b; }
U64 U64_or(U64 a, U64 b) { return a | b; }
U64 U64_xor(U64 a, U64 b) { return a ^ b; }
U64 U64_inc(U64 a) { return a + 1; }
U64 U64_dec(U64 a) { return a - 1; }

Bool U64_eq(U64 a, U64 b) { return a == b; }
I64 U64_cmp(U64 a, U64 b) { return a < b ? -1 : (a > b ? 1 : 0); }

I64 U64_to_i64(U64 v) { return (I64)v; }
U64 U64_from_i64(I64 v) { return (U64)v; }

// Pointer-adapter versions for interpreter FFI (nested ext_func in core.til)
U8 U8_from_i64_ext(I64 *a) { return (U8)*a; }
I16 *I16_from_i64_ext(I64 *a) { return I16_new((I16)*a); }
I32 *I32_from_i64_ext(I64 *a) { return I32_new((I32)*a); }
F32 *F32_from_i64_ext(I64 *a) { return F32_new((F32)*a); }
U32 *U32_from_i64_ext(I64 *a) { return U32_new((U32)*a); }
U64 *U64_from_i64_ext(I64 *a) { return U64_new((U64)*a); }

Str *U64_to_str(U64 v) {
    char buf[32];
    snprintf(buf, 32, "%llu", v);
    return Str_new(buf);
}
Str *U64_to_str_ext(U64 v) { return U64_to_str(v); }

U64 *U64_new(U64 val) {
    U64 *p = malloc(sizeof(U64));
    *p = val;
    return p;
}

U64 *U64_clone(U64 *v) { return U64_new(*v); }
void U64_delete(U64 *v, Bool *call_free) { if (*call_free) free(v); }

// --- Bool ---

Bool Bool_eq(Bool a, Bool b) { return a == b; }
Bool Bool_and(Bool a, Bool b) { return a && b; }
Bool Bool_or(Bool a, Bool b) { return a || b; }
Bool Bool_not(Bool a) { return !a; }

Bool *Bool_new(Bool val) {
    Bool *p = malloc(sizeof(Bool));
    *p = val;
    return p;
}

Bool *Bool_clone(Bool *v) { return Bool_new(*v); }
void Bool_delete(Bool *v, Bool *call_free) { if (*call_free) free(v); }

// Pointer primitives
Bool is_null(void *p) { return p == NULL; }
