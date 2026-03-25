#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../boot/modes.h"
#include "pre70.h"
#include "interpreter.h"
#include "dispatch.h"

// Forward declaration (defined in ast.c)

static Set macros, funcs;
static Map known;

// --- Value → Expr conversion ---

static Expr *value_to_expr(Value val, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = &src->path;
    Expr *e;
    switch (val.tag) {
    case Value_TAG_Int: {
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
        char buf[32];
        snprintf(buf, sizeof(buf), "%lld", (long long)val.data.Int);
        e->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
        e->til_type = (TilType){TilType_TAG_I64};
        return e;
    }
    case Value_TAG_Byte: {
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
        char buf[32];
        snprintf(buf, sizeof(buf), "%u", (unsigned)val.data.Byte);
        e->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
        e->til_type = (TilType){TilType_TAG_U8};
        return e;
    }
    case Value_TAG_Struct: {
        if ((val.data.Struct.struct_name->count == 3 && memcmp(val.data.Struct.struct_name->c_str, "Str", 3) == 0)) {
            Str sv = str_view(val);
            e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
            e->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(const char *)sv.c_str, .count = sv.count, .cap = CAP_VIEW});
            e->til_type = (TilType){TilType_TAG_Struct};
            e->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
            return e;
        }
        return NULL; // other struct types not supported in precomp
    }
    case Value_TAG_Boolean: {
        e = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
        e->data.data.LiteralBool = (val.data.Boolean ? (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT} : (Str){.c_str = (U8*)"false", .count = 5, .cap = CAP_LIT});
        e->til_type = (TilType){TilType_TAG_Bool};
        return e;
    }
    default:
        return NULL;
    }
}

// --- Expr → Value conversion (for building args to pass to interpreter) ---

static Value expr_to_value(Expr *e) {
    switch (e->data.tag) {
    case ExprData_TAG_LiteralNum:
        if (e->til_type.tag == TilType_TAG_U8)
            return val_u8(atoll((const char *)e->data.data.LiteralNum.c_str));
        return val_i64(atoll((const char *)e->data.data.LiteralNum.c_str));
    case ExprData_TAG_LiteralStr:
        return make_str_value((const char *)e->data.data.LiteralStr.c_str, e->data.data.LiteralStr.count);
    case ExprData_TAG_LiteralBool:
        return val_bool(strcmp((const char *)e->data.data.LiteralBool.c_str, "true") == 0);
    default:
        return val_none();
    }
}

// Check if an expression is compile-time known and return its value
static Bool is_known(Expr *e, Value *out) {
    if (e->data.tag == ExprData_TAG_LiteralNum || e->data.tag == ExprData_TAG_LiteralStr ||
        e->data.tag == ExprData_TAG_LiteralBool) {
        *out = expr_to_value(e);
        return 1;
    }
    if (e->data.tag == ExprData_TAG_Ident) {
        if (Map_has(&known, &e->data.data.Ident)) { *out = *(Value *)Map_get(&known, &e->data.data.Ident); return 1; }
    }
    return 0;
}

// Check if a ExprData_TAG_FCall is a macro call
Bool is_macro_call(Expr *e) {
    return e->data.tag == ExprData_TAG_FCall &&
           e->children.count > 0 &&
           Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident &&
           Set_has(&macros, &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident);
}

// Check if a ExprData_TAG_FCall is a pure func call
Bool is_func_call(Expr *e) {
    return e->data.tag == ExprData_TAG_FCall &&
           e->children.count > 0 &&
           Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident &&
           Set_has(&funcs, &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident);
}

// Check if a func body references identifiers not available at precomp time.
// Something is available if it's a parameter, in the known map, or in the precomp scope
// (funcs, structs, enums are pre-registered there).
static Bool func_uses_unknown_globals(Expr *e, Expr *func_def, Scope *precomp_scope) {
    if (e->data.tag == ExprData_TAG_FuncDef) return 0; // don't recurse into nested funcs
    if (e->data.tag == ExprData_TAG_Ident) {
        Str *name = &e->data.data.Ident;
        for (U32 i = 0; i < func_def->data.data.FuncDef.nparam; i++) {
            if (Str_eq(&((Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)}))->name, name)) return 0;
        }
        if (Map_has(&known, name)) return 0;
        if (scope_get(precomp_scope, name)) return 0;
        return 1;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        if (func_uses_unknown_globals(Expr_child(e, &(USize){(USize)(i)}), func_def, precomp_scope)) return 1;
    }
    return 0;
}

// Try to evaluate a call at compile time.
// require_known=1 (macro): error if arg not known. require_known=0 (func): return NULL silently.
Expr *try_eval_call(Scope *scope, Expr *fcall, Bool require_known) {
    // Check if the function body references unknown globals
    Str *callee_name = &Expr_child(fcall, &(USize){(USize)(0)})->data.data.Ident;
    Cell *fn_cell = scope_get(scope, callee_name);
    if (fn_cell && fn_cell->val.tag == Value_TAG_Func && ((Expr*)fn_cell->val.data.Func)->data.tag == ExprData_TAG_FuncDef) {
        Expr *fdef = (Expr*)fn_cell->val.data.Func;
        if (fdef->children.count > 0 && func_uses_unknown_globals(Expr_child(fdef, &(USize){(USize)(0)}), fdef, scope)) {
            return NULL;
        }
    }

    // Build a call with literal args for the interpreter
    U32 nargs = fcall->children.count - 1;
    Expr *eval_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, fcall->line, fcall->col, &fcall->path);
    eval_call->til_type = fcall->til_type;
    eval_call->struct_name = fcall->struct_name;
    Expr_add_child(eval_call, Expr_clone(Expr_child(fcall, &(USize){(USize)(0)}))); // callee ident (clone — borrowed ref)

    for (U32 i = 0; i < nargs; i++) {
        Expr *arg = Expr_child(fcall, &(USize){(USize)(i + 1)});
        Value arg_val;
        if (!is_known(arg, &arg_val)) {
            if (require_known) {
                Expr_error(arg, &(Str){.c_str = (U8*)"macro argument must be known at compile time", .count = 44, .cap = CAP_LIT});
            }
            // Clean up: detach callee so it's not double-freed
            memset(Vec_get(&eval_call->children, &(USize){(USize)(0)}), 0, sizeof(Expr));
            eval_call->children.count = 0;
            Expr_delete(eval_call, &(Bool){1});
            return NULL;
        }
        // Create a literal expression from the value
        Expr *lit = value_to_expr(arg_val, arg);
        Expr_add_child(eval_call, lit);
    }

    // Evaluate the call using the interpreter
    Value result = eval_expr(scope, eval_call);

    // Clean up eval_call (detach callee ident first — it's shared with original)
    memset(Vec_get(&eval_call->children, &(USize){(USize)(0)}), 0, sizeof(Expr));
    for (U32 i = 1; i < eval_call->children.count; i++)
        Expr_delete(Expr_child(eval_call, &(USize){(USize)(i)}), &(Bool){0});
    Vec_delete(&eval_call->children, &(Bool){0});
    free(eval_call);

    // Convert result to AST
    Expr *lit = value_to_expr(result, fcall);
    if (!lit) {
        if (require_known) {
            Expr_error(fcall, &(Str){.c_str = (U8*)"macro returned non-primitive type", .count = 33, .cap = CAP_LIT});
        }
    }
    return lit;
}

// Track a literal value from a declaration — also add to precomp scope
// so the interpreter can find it when folding func calls
void track_literal(Scope *scope, Str *name, Expr *rhs) {
    Value v;
    if (is_known(rhs, &v)) {
        { Str *_k = Str_clone(name); void *_v = malloc(sizeof(v)); memcpy(_v, &v, sizeof(v)); Map_set(&known, _k, _v); }
        scope_set_owned(scope, name, v);
    }
}


void precomp(Expr *program) {
    // 1. Collect macro and pure func names
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); macros = *_sp; free(_sp); }
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); funcs = *_sp; free(_sp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == ExprData_TAG_Decl && stmt->children.count > 0 && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
            FuncType ft = Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
            if (ft.tag == FuncType_TAG_Macro)
                { Str *_p = malloc(sizeof(Str)); *_p = (Str){Str_clone(&stmt->data.data.Decl.name)->c_str, stmt->data.data.Decl.name.count, stmt->data.data.Decl.name.count}; Set_add(&macros, _p); }
            else if (ft.tag == FuncType_TAG_Func)
                { Str *_p = malloc(sizeof(Str)); *_p = (Str){Str_clone(&stmt->data.data.Decl.name)->c_str, stmt->data.data.Decl.name.count, stmt->data.data.Decl.name.count}; Set_add(&funcs, _p); }
        }
        // Register namespace funcs from struct/enum bodies
        if (stmt->data.tag == ExprData_TAG_Decl && stmt->children.count > 0 &&
            (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef)) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){(USize)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace &&
                    Expr_child(field, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
                    FuncType ft = Expr_child(field, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
                    if (ft.tag == FuncType_TAG_Func) {
                        Str *qname = Str_concat(Str_concat(sname, &(Str){.c_str = (U8*)"_", .count = 1, .cap = CAP_LIT}), &field->data.data.Decl.name);
                        { Str *_p = malloc(sizeof(Str)); *_p = (Str){Str_clone(qname)->c_str, qname->count, qname->count}; Set_add(&funcs, _p); }
                    }
                }
            }
        }
    }

    // Nothing to fold?
    if (macros.count == 0 && funcs.count == 0) {
        Set_delete(&macros, &(Bool){0});
        Set_delete(&funcs, &(Bool){0});
        return;
    }

    // 2. Set up interpreter scope (same as interpret() does)
    Scope *global = scope_new(NULL);
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == ExprData_TAG_Decl &&
            (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef ||
             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef)) {
            Value val = {.tag = Value_TAG_Func, .data.Func = (void*)Expr_child(stmt, &(USize){(USize)(0)})};
            scope_set_owned(global, (&stmt->data.data.Decl.name), val);
        }
    }
    interpreter_init_ns(global, program);

    // 2b. Init FFI so ext_func calls (e.g. auto-delete) work during folding
    ffi_init(program, NULL, NULL, NULL);

    // 3. Process the program body
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Value)}); known = *_mp; free(_mp); }
    process_body(global, program);

    // Cleanup
    Map_delete(&known, &(Bool){0});
    scope_free(global);
    Set_delete(&macros, &(Bool){0});
    Set_delete(&funcs, &(Bool){0});
}
