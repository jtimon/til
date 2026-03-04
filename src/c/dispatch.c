#include "dispatch.h"
#include "ccore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ext_function_dispatch(Str *name, Scope *scope, Expr *e, const char *path, Value *result) {
    // Variadic builtins
    if (Str_eq_c(name, "println")) {
        for (int i = 1; i < e->nchildren; i++) {
            Value arg = eval_expr(scope, e->children[i], path);
            printf("%s", arg.str->c_str);
        }
        printf("\n");
        *result = val_none();
        return 1;
    }
    if (Str_eq_c(name, "print")) {
        for (int i = 1; i < e->nchildren; i++) {
            Value arg = eval_expr(scope, e->children[i], path);
            printf("%s", arg.str->c_str);
        }
        *result = val_none();
        return 1;
    }
    if (Str_eq_c(name, "format")) {
        int nargs = e->nchildren - 1;
        Str *strs[64];
        int total = 0;
        for (int i = 0; i < nargs; i++) {
            Value v = eval_expr(scope, e->children[i + 1], path);
            strs[i] = v.str;
            total += v.str->len;
        }
        char *buf = malloc(total + 1);
        int off = 0;
        for (int i = 0; i < nargs; i++) {
            memcpy(buf + off, strs[i]->c_str, strs[i]->len);
            off += strs[i]->len;
        }
        buf[off] = '\0';
        Str *s = malloc(sizeof(Str));
        s->c_str = buf;
        s->len = total;
        *result = val_str(s);
        return 1;
    }

    // I64 arithmetic
    if (Str_eq_c(name, "I64_add")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_add(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_sub")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_sub(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_mul")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_mul(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_div")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_div(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_mod")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_mod(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_and")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_and(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_or"))  { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_or(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_xor")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_i64(I64_xor(*a.i64, *b.i64)); return 1; }

    // I64 comparisons
    if (Str_eq_c(name, "I64_eq")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(I64_eq(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_lt")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(I64_lt(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_gt")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(I64_gt(*a.i64, *b.i64)); return 1; }

    // I64 conversion
    if (Str_eq_c(name, "I64_to_str")) { Value v = eval_expr(scope, e->children[1], path); *result = val_str(I64_to_str(*v.i64)); return 1; }
    if (Str_eq_c(name, "I64_clone")) { Value v = eval_expr(scope, e->children[1], path); *result = val_i64(*v.i64); return 1; }
    if (Str_eq_c(name, "I64_delete")) { Value v = eval_expr(scope, e->children[1], path); if (v.type == VAL_NONE) { *result = val_none(); return 1; } Value cf = eval_expr(scope, e->children[2], path); if (*cf.boolean) I64_delete(v.i64); *result = val_none(); return 1; }

    // U8 arithmetic
    if (Str_eq_c(name, "U8_add")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_add(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_sub")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_sub(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_mul")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_mul(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_div")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_div(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_mod")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_mod(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_and")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_and(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_or"))  { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_or(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_xor")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_u8(U8_xor(*a.u8, *b.u8)); return 1; }

    // U8 comparisons
    if (Str_eq_c(name, "U8_eq")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(U8_eq(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_lt")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(U8_lt(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_gt")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(U8_gt(*a.u8, *b.u8)); return 1; }

    // U8 conversions
    if (Str_eq_c(name, "U8_to_str"))  { Value v = eval_expr(scope, e->children[1], path); *result = val_str(U8_to_str(*v.u8)); return 1; }
    if (Str_eq_c(name, "U8_to_i64"))  { Value v = eval_expr(scope, e->children[1], path); *result = val_i64(U8_to_i64(*v.u8)); return 1; }
    if (Str_eq_c(name, "U8_from_i64") || Str_eq_c(name, "U8_from_i64_ext")) {
        Value v = eval_expr(scope, e->children[1], path);
        *result = val_u8(U8_from_i64(*v.i64));
        return 1;
    }
    if (Str_eq_c(name, "U8_clone")) { Value v = eval_expr(scope, e->children[1], path); *result = val_u8(*v.u8); return 1; }
    if (Str_eq_c(name, "U8_delete")) { Value v = eval_expr(scope, e->children[1], path); if (v.type == VAL_NONE) { *result = val_none(); return 1; } Value cf = eval_expr(scope, e->children[2], path); if (*cf.boolean) U8_delete(v.u8); *result = val_none(); return 1; }

    // Bool ops
    if (Str_eq_c(name, "Bool_and")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(Bool_and(*a.boolean, *b.boolean)); return 1; }
    if (Str_eq_c(name, "Bool_or"))  { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(Bool_or(*a.boolean, *b.boolean)); return 1; }
    if (Str_eq_c(name, "Bool_not")) { Value a = eval_expr(scope, e->children[1], path); *result = val_bool(Bool_not(*a.boolean)); return 1; }
    if (Str_eq_c(name, "Bool_clone")) { Value v = eval_expr(scope, e->children[1], path); *result = val_bool(*v.boolean); return 1; }
    if (Str_eq_c(name, "Bool_delete")) { Value v = eval_expr(scope, e->children[1], path); if (v.type == VAL_NONE) { *result = val_none(); return 1; } Value cf = eval_expr(scope, e->children[2], path); if (*cf.boolean) Bool_delete(v.boolean); *result = val_none(); return 1; }

    // Str ops
    if (Str_eq_c(name, "Str_eq")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(Str_eq(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_concat")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_str(Str_concat(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_clone")) { Value a = eval_expr(scope, e->children[1], path); *result = val_str(Str_clone(a.str)); return 1; }
    if (Str_eq_c(name, "Str_delete")) {
        Value s = eval_expr(scope, e->children[1], path);
        if (s.type == VAL_NONE) { *result = val_none(); return 1; }
        Value cf = eval_expr(scope, e->children[2], path);
        if (*cf.boolean) Str_delete(s.str);
        *result = val_none(); return 1;
    }
    if (Str_eq_c(name, "Str_to_str")) { Value a = eval_expr(scope, e->children[1], path); *result = val_str(Str_clone(a.str)); return 1; }
    if (Str_eq_c(name, "Str_len")) { Value a = eval_expr(scope, e->children[1], path); *result = val_i64(Str_len(a.str)); return 1; }
    if (Str_eq_c(name, "Str_substr")) { Value s = eval_expr(scope, e->children[1], path); Value start = eval_expr(scope, e->children[2], path); Value n = eval_expr(scope, e->children[3], path); *result = val_str(Str_substr(s.str, (int)*start.i64, (int)*n.i64)); return 1; }
    if (Str_eq_c(name, "Str_contains")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(Str_contains(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_starts_with")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(Str_starts_with(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_ends_with")) { Value a = eval_expr(scope, e->children[1], path); Value b = eval_expr(scope, e->children[2], path); *result = val_bool(Str_ends_with(a.str, b.str)); return 1; }

    // Misc
    if (Str_eq_c(name, "exit")) { Value a = eval_expr(scope, e->children[1], path); til_exit(a.i64); *result = val_none(); return 1; }

    // free — accesses scope directly; requires identifier argument
    if (Str_eq_c(name, "free")) {
        if (e->children[1]->type != NODE_IDENT) {
            fprintf(stderr, "free() requires identifier argument\n"); exit(1);
        }
        Cell *cell = scope_get(scope, e->children[1]->data.str_val);
        if (cell->val.type == VAL_STRUCT && cell->val.instance) {
            til_free(cell->val.instance->field_names);
            til_free(cell->val.instance->field_muts);
            til_free(cell->val.instance->field_values);
            til_free(cell->val.instance);
        } else if (cell->val.type == VAL_ENUM && cell->val.enum_inst) {
            // Free payload if present, then the instance
            Value p = cell->val.enum_inst->payload;
            if (p.type == VAL_I64)  til_free(p.i64);
            else if (p.type == VAL_U8)   til_free(p.u8);
            else if (p.type == VAL_BOOL) til_free(p.boolean);
            else if (p.type == VAL_STR)  Str_delete(p.str);
            til_free(cell->val.enum_inst);
        } else if (cell->val.type == VAL_I64) {
            til_free(cell->val.i64);
        } else if (cell->val.type == VAL_U8) {
            til_free(cell->val.u8);
        } else if (cell->val.type == VAL_BOOL) {
            til_free(cell->val.boolean);
        } else if (cell->val.type == VAL_STR) {
            Str_delete(cell->val.str);
        }
        cell->val = val_none();
        *result = val_none();
        return 1;
    }

    return 0;
}
