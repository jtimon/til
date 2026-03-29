#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LIT(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)(sizeof(s) - 1), .cap=CAP_LIT})
#define STR_VIEW(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)strlen((const char *)(s)), .cap=CAP_VIEW})

// --- Type inference/checking pass ---

void infer_fcall_expr(TypeScope *scope, Expr *e, I32 in_func) {
        if (Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess) {
            if (infer_field_access_fcall(scope, e, in_func)) return;
        }
        Str _name_val = Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        Str *name = &_name_val;
        Str *resolved_name = resolve_type_alias(scope, name);
        if (resolved_name != name) {
            Expr_child(e, &(USize){(USize)(0)})->data.data.Ident = *resolved_name;
            _name_val = *resolved_name;
        }
        if (infer_struct_constructor_fcall(scope, e, name, in_func)) return;
        ScopeFind *_sf_cb = TypeScope_find(scope, name);
        TypeBinding *callee_bind = _sf_cb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_cb) : NULL;
        if (callee_bind && callee_bind->func_def &&
            (!callee_bind->is_builtin || !callee_bind->func_def->is_core)) {
            desugar_user_func_fcall_args(e, name, callee_bind);
        }
        infer_and_validate_fcall_args(scope, e, callee_bind, in_func);
        validate_fcall_own_args(scope, e, callee_bind);
        resolve_fcall_return_type(scope, e, name, callee_bind, in_func);
        return;
}

// --- Collection literal helpers ---

// --- Set literal desugaring ---
// Transforms s := {v1, v2, v3} into:
//   mut s := Set.new(elem_type, elem_size)
//   Set.add(s, own v1)
//   Set.add(s, own v2)
//   Set.add(s, own v3)

// --- Map literal desugaring ---
// Transforms m := {k1: v1, k2: v2} into:
//   mut m := Map.new(key_type, key_size, val_type, val_size)
//   Map.set(m, own k1, own v1)
//   Map.set(m, own k2, own v2)

// --- Variadic call desugaring ---
// Transforms variadic function calls into Array.new + Array.set + normal call.
// Must run before hoisting so that synthetic Array calls get hoisted too.

// Create a namespace method call: StructName.method(args...)
// --- Kwargs call desugaring ---
// Transforms kwargs function calls into Map.new + Map.set + normal call.

// --- Argument hoisting ---


// Check if a function call returns ref

// --- Delete call insertion ---
