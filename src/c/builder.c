#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARAM_IS_OWN(p) ((p)->own_type.tag == OwnType_TAG_Own)
#define PARAM_IS_SHALLOW(p) ((p)->own_type.tag == OwnType_TAG_Shallow)
#define RETURN_IS_REF(fd) ((fd)->return_own_type.tag == OwnType_TAG_Ref)
#define RETURN_IS_SHALLOW(fd) ((fd)->return_own_type.tag == OwnType_TAG_Shallow)
#define DECL_IS_OWN(d) ((d).own_type.tag == OwnType_TAG_Own)
#define DECL_IS_REF(d) ((d).own_type.tag == OwnType_TAG_Ref)
#define DECL_IS_SHALLOW(d) ((d).own_type.tag == OwnType_TAG_Shallow)
#define FIELD_IS_PTR(e) ((e)->field_own_type.tag != OwnType_TAG_Shallow)
#define FIELD_IS_SHALLOW(e) ((e)->field_own_type.tag == OwnType_TAG_Shallow)

// Helper macros for File-based emission (replacing fprintf)
#define EMIT(f, s) File_write_str(f, &(Str){.c_str=(U8*)(s), .count=(U64)strlen((const char*)(s)), .cap=CAP_VIEW})


__attribute__((unused)) static void emit_i64(File *f, I64 v) {
    char buf[32]; snprintf(buf, sizeof(buf), "%lld", (long long)v);
    EMIT(f, buf);
}
static void emit_u64(File *f, U64 v) {
    char buf[32]; snprintf(buf, sizeof(buf), "%llu", (unsigned long long)v);
    EMIT(f, buf);
}
__attribute__((unused)) static void emit_u32(File *f, U32 v) {
    char buf[16]; snprintf(buf, sizeof(buf), "%u", v);
    EMIT(f, buf);
}
static void emit_i32(File *f, I32 v) {
    char buf[16]; snprintf(buf, sizeof(buf), "%d", v);
    EMIT(f, buf);
}

static Expr *codegen_core_program;  // blocked by #132
static Expr *codegen_program;  // blocked by #132
static Expr *current_fdef = NULL;  // blocked by #132
// remaining globals defined in builder.til

// Collect unique array/vec builtin type names from AST
// CollectionInfo defined in builder.til

static void collect_collection_builtins(Expr *e, Vec *infos) {
    if (!e) return;
    if (e->data.tag == NodeType_TAG_FCall && Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_Ident &&
        e->children.count >= 2 && Expr_child(e, &(USize){(USize)(1)})->data.tag == NodeType_TAG_LiteralStr) {
        Str *name = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        I32 is_vec = -1;
        if ((name->count == 5 && memcmp(name->c_str, "array", 5) == 0)) is_vec = 0;
        else if ((name->count == 3 && memcmp(name->c_str, "vec", 3) == 0)) is_vec = 1;
        if (is_vec >= 0) {
            Str *type_name = &Expr_child(e, &(USize){(USize)(1)})->data.data.Ident;
            for (U32 i = 0; i < infos->count; i++) {
                CollectionInfo *existing = Vec_get(infos, &(USize){(USize)(i)});
                if (Str_eq(existing->type_name, type_name) && existing->is_vec == is_vec) return;
            }
            CollectionInfo info = {type_name, is_vec};
            { CollectionInfo *_p = malloc(sizeof(CollectionInfo)); *_p = info; Vec_push(infos, _p); }
        }
    }
    for (U32 i = 0; i < e->children.count; i++) {
        collect_collection_builtins(Expr_child(e, &(USize){(USize)(i)}), infos);
    }
}

// Collect unique dyn_call method literals from AST
// DynCallInfo defined in builder.til

// is_dyn_call_name: moved to builder.til

static void collect_dyn_methods(Expr *e, Vec *methods) {
    if (!e) return;
    if (e->data.tag == NodeType_TAG_FCall && Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_Ident &&
        e->children.count >= 3 && Expr_child(e, &(USize){(USize)(2)})->data.tag == NodeType_TAG_LiteralStr) {
        Bool returns;
        if (is_dyn_call_name(&Expr_child(e, &(USize){(USize)(0)})->data.data.Ident, &returns)) {
            Str *method = &Expr_child(e, &(USize){(USize)(2)})->data.data.Ident;
            // Read arity from 3rd arg (child 3) — a literal number
            I32 nargs = 1;
            if (e->children.count >= 4 && Expr_child(e, &(USize){(USize)(3)})->data.tag == NodeType_TAG_LiteralNum) {
                nargs = (I32)atol((char *)Expr_child(e, &(USize){(USize)(3)})->data.data.Ident.c_str);
            }
            for (U32 i = 0; i < methods->count; i++) {
                DynCallInfo *existing = Vec_get(methods, &(USize){(USize)(i)});
                if (Str_eq(existing->method, method)) return;
            }
            DynCallInfo info = {.method = method, .nargs = nargs, .has_return = returns};
            { DynCallInfo *_p = malloc(sizeof(DynCallInfo)); *_p = info; Vec_push(methods, _p); }
        }
    }
    for (U32 i = 0; i < e->children.count; i++) {
        collect_dyn_methods(Expr_child(e, &(USize){(USize)(i)}), methods);
    }
}

// Collect unique method names from dyn_has_method calls
static void collect_dyn_has_methods(Expr *e, Vec *methods) {
    if (!e) return;
    if (e->data.tag == NodeType_TAG_FCall && Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_Ident &&
        (Expr_child(e, &(USize){(USize)(0)})->data.data.Ident.count == 14 && memcmp(Expr_child(e, &(USize){(USize)(0)})->data.data.Ident.c_str, "dyn_has_method", 14) == 0) &&
        e->children.count >= 3 && Expr_child(e, &(USize){(USize)(2)})->data.tag == NodeType_TAG_LiteralStr) {
        Str *method = &Expr_child(e, &(USize){(USize)(2)})->data.data.Ident;
        for (U32 i = 0; i < methods->count; i++) {
            Str **existing = Vec_get(methods, &(USize){(USize)(i)});
            if (Str_eq(*existing, method)) return;
        }
        { Str **_p = malloc(sizeof(Str *)); *_p = method; Vec_push(methods, _p); }
    }
    for (U32 i = 0; i < e->children.count; i++) {
        collect_dyn_has_methods(Expr_child(e, &(USize){(USize)(i)}), methods);
    }
}

Expr *find_struct_body(Str *name) {
    if (!Map_has(&struct_bodies, name)) return NULL;
    Expr **p = Map_get(&struct_bodies, name);
    return *p;
}

// --- Emitter helpers ---

static void emit_indent(File *f, U32 depth) {
    for (U32 i = 0; i < depth; i++) EMIT(f, "    ");
}

// Emit expression dereferenced to a value: (*x) for IDENT, plain for literals/builtins
static void emit_deref(File *f, Expr *e, I32 depth);
// Emit expression as a pointer: wraps values in &(type){val}
static void emit_as_ptr(File *f, Expr *e, I32 depth);
static void emit_usize_ref(File *f, Expr *e, I32 depth);

// --- Forward declarations ---

static void emit_expr(File *f, Expr *e, I32 depth);
static void emit_stmt(File *f, Expr *e, I32 depth);
static void emit_body(File *f, Expr *body, I32 depth);
static void emit_body_scoped(File *f, Expr *body, I32 depth);
static void emit_ctor_fields(File *f, const char *var, Expr *ctor, I32 depth);
static Str *type_name_to_c_value(Str *name);

Expr *find_callee_fdef(Str *name);

// is_stack_local: moved to builder.til

// is_value_global: moved to builder.til

// is_ref_local: moved to builder.til

static void emit_field(File *f, const char *var, const char *field) {
    Str _var_s = {.c_str = (U8*)var, .count = (U64)strlen(var), .cap = CAP_VIEW};
    EMIT(f, var); EMIT(f, (is_stack_local(&_var_s) || is_value_global(&_var_s)) ? "." : "->"); EMIT(f, field);
}

// use_dot_access: moved to builder.til

static Str *get_stack_local_ctype(Str *name) {
    if (Map_has(&stack_local_types, name)) {
        Str **p = Map_get(&stack_local_types, name);
        return Str_clone(&(Str){.c_str = (*p)->c_str, .count = (*p)->count, .cap = CAP_VIEW});
    }
    return NULL;
}

// Block-scoped emit_body: clone stack_locals/ref_locals before
// entering a block, restore after. Inner declarations stay local to the block.
static void emit_body_scoped(File *f, Expr *body, I32 depth) {
    Set saved_sl = stack_locals;
    Set saved_rl = ref_locals;
    { Set *_c = Set_clone(&stack_locals); stack_locals = *_c; free(_c); }
    { Set *_c = Set_clone(&ref_locals); ref_locals = *_c; free(_c); }
    emit_body(f, body, depth);
    Set_delete(&stack_locals, &(Bool){0});
    Set_delete(&ref_locals, &(Bool){0});
    stack_locals = saved_sl;
    ref_locals = saved_rl;
}

// Scan function body to find variables whose address might escape via ref.
// A variable is unsafe to hoist if:
// - It appears in a ref declaration RHS: "ref y : T = x"
// - It's passed as arg to a ref-returning function
// Resolve the callee name from an fcall's first child
static Str *resolve_callee_name(Expr *fcall, Bool *allocated) {
    *allocated = 0;
    Expr *callee_node = Expr_child(fcall, &(USize){(USize)(0)});
    if (callee_node->data.tag == NodeType_TAG_FieldAccess) {
        Str *sname = &Expr_child(callee_node, &(USize){(USize)(0)})->struct_name;
        Str *mname = &callee_node->data.data.FieldAccess;
        if (sname->count == 0) return NULL;
        char buf[256];
        snprintf(buf, sizeof(buf), "%s_%s", sname->c_str, mname->c_str);
        *allocated = 1;
        return Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
    } else if (callee_node->data.tag == NodeType_TAG_Ident) {
        return &callee_node->data.data.Ident;
    }
    return NULL;
}

// fcall_fn_sig: moved to builder.til

// Check all fcalls in an expression tree and mark idents passed to mut params as unsafe
static void check_fcall_mut_args(Expr *e) {
    if (!e) return;
    if (e->data.tag == NodeType_TAG_FCall) {
        // Check fn_sig for function pointer calls
        Expr *fdef = fcall_fn_sig(e);
        if (!fdef) {
            Bool allocated = 0;
            Str *callee = resolve_callee_name(e, &allocated);
            if (callee) {
                fdef = find_callee_fdef(callee);
                if (allocated) Str_delete(callee, &(Bool){1});
            }
        }
        if (fdef && fdef->data.data.FuncDef.params.count > 0) {
            for (U32 a = 1; a < e->children.count; a++) {
                U32 pi = a - 1;
                if (pi < fdef->data.data.FuncDef.nparam && ((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)}))->is_mut) {
                    Expr *arg = Expr_child(e, &(USize){(USize)(a)});
                    if (arg->data.tag == NodeType_TAG_Ident) {
                        Set_add(&unsafe_to_hoist, Str_clone(&arg->data.data.Ident));
                    }
                }
            }
        }
    }
    for (U32 i = 0; i < e->children.count; i++) {
        check_fcall_mut_args(Expr_child(e, &(USize){(USize)(i)}));
    }
}

static void collect_unsafe_to_hoist(Expr *body) {
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});

        // Check all fcalls for mut param args
        check_fcall_mut_args(stmt);

        if (stmt->data.tag == NodeType_TAG_Decl && DECL_IS_REF(stmt->data.data.Decl)) {
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            if (rhs->data.tag == NodeType_TAG_Ident) {
                Set_add(&unsafe_to_hoist, Str_clone(&rhs->data.data.Ident));
            }
            if (rhs->data.tag == NodeType_TAG_FCall) {
                Bool allocated = 0;
                Str *callee = resolve_callee_name(rhs, &allocated);
                if (callee) {
                    Expr *fdef = find_callee_fdef(callee);
                    if (fdef && RETURN_IS_REF(&fdef->data.data.FuncDef)) {
                        for (U32 a = 1; a < rhs->children.count; a++) {
                            Expr *arg = Expr_child(rhs, &(USize){(USize)(a)});
                            if (arg->data.tag == NodeType_TAG_Ident) {
                                Set_add(&unsafe_to_hoist, Str_clone(&arg->data.data.Ident));
                            }
                        }
                    }
                    if (allocated) Str_delete(callee, &(Bool){1});
                }
            }
        }
        if (stmt->data.tag == NodeType_TAG_If) {
            for (U32 c = 1; c < stmt->children.count; c++)
                collect_unsafe_to_hoist(Expr_child(stmt, &(USize){(USize)(c)}));
        }
        if (stmt->data.tag == NodeType_TAG_While && stmt->children.count > 1) {
            collect_unsafe_to_hoist(Expr_child(stmt, &(USize){(USize)(1)}));
        }
        if (stmt->data.tag == NodeType_TAG_Body) {
            collect_unsafe_to_hoist(stmt);
        }
    }
}


static Bool is_shallow_param(Str *name) {
    if (!current_fdef) return 0;
    for (U32 i = 0; i < current_fdef->data.data.FuncDef.nparam; i++) {
        Param *_spi = (Param*)Vec_get(&current_fdef->data.data.FuncDef.params, &(USize){(USize)(i)});
        if (PARAM_IS_SHALLOW(_spi) && Str_eq(&_spi->name, name))
            return 1;
    }
    return 0;
}

// Check if callee's i-th parameter is shallow (for call site emission)
Expr *find_callee_fdef(Str *name) {
    if (!Map_has(&func_defs, name)) return NULL;
    Expr **p = Map_get(&func_defs, name);
    return *p;
}

// Get the C value type name for a callee's return type (e.g. "U64" for I64_size)
static Str *callee_return_ctype(Str *callee_name) {
    Expr *fdef = find_callee_fdef(callee_name);
    if (!fdef || fdef->data.data.FuncDef.return_type.count == 0) return NULL;
    return type_name_to_c_value(&fdef->data.data.FuncDef.return_type);
}

// Get the C value type for an fcall's return value
static Str *fcall_return_ctype(Expr *fcall) {
    if (fcall->data.tag != NodeType_TAG_FCall) return NULL;
    Bool allocated = 0;
    Str *callee = resolve_callee_name(fcall, &allocated);
    if (!callee) return NULL;
    Str *r = callee_return_ctype(callee);
    if (allocated) Str_delete(callee, &(Bool){1});
    return r;
}

// callee_returns_shallow: moved to builder.til

// callee_returns_dynamic: moved to builder.til

// fcall_is_shallow_return: moved to builder.til

// fcall_returns_dynamic: moved to builder.til

// callee_param_is_shallow: moved to builder.til

// callee_param_is_usize: moved to builder.til

// callee_param_is_own: moved to builder.til


// --- Expression emission ---

static void emit_expr(File *f, Expr *e, I32 depth) {
    (void)depth;
    switch (e->data.tag) {
    case NodeType_TAG_LiteralStr:
        EMIT(f, "Str_lit(\""); EMIT(f, (const char *)e->data.data.LiteralStr.c_str); EMIT(f, "\", "); emit_u64(f, e->data.data.LiteralStr.count); EMIT(f, "ULL)");
        break;
    case NodeType_TAG_LiteralNum:
        EMIT(f, (const char *)e->data.data.LiteralNum.c_str);
        break;
    case NodeType_TAG_LiteralBool:
        emit_i32(f, e->data.data.LiteralBool ? 1 : 0);
        break;
    case NodeType_TAG_LiteralNull:
        EMIT(f, "NULL");
        break;
    case NodeType_TAG_Ident:
        if (e->til_type.tag == TilType_TAG_FuncPtr) {
            // Function name used as value — cast to void* for function pointer storage
            EMIT(f, "(void *)"); { Str *_fc = func_to_c(&e->data.data.Ident); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); }
        } else {
            EMIT(f, (const char *)e->data.data.Ident.c_str);
        }
        break;
    case NodeType_TAG_FCall: {
        // Indirect call through FuncSig-typed struct field: h.on_click(3, 5)
        if (Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FieldAccess &&
            Expr_child(e, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_FuncPtr && fcall_fn_sig(e)) {
            // Use fn_sig to determine shallow params/return for correct cast
            Expr *sig = fcall_fn_sig(e);
            Bool ret_shallow = sig ? RETURN_IS_SHALLOW(&sig->data.data.FuncDef) : 0;
            Str ret_c = {.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT};
            if (e->til_type.tag != TilType_TAG_None && e->til_type.tag != TilType_TAG_Unknown &&
                e->til_type.tag != TilType_TAG_Dynamic) {
                { Str *_t = til_type_to_c(e->til_type); ret_c = *_t; free(_t); }
                if ((e->til_type.tag == TilType_TAG_Struct || e->til_type.tag == TilType_TAG_Enum) && e->struct_name.count > 0) {
                    static char ret_buf2[128];
                    snprintf(ret_buf2, sizeof(ret_buf2), "%s", e->struct_name.c_str);
                    ret_c = (Str){.c_str = (U8 *)ret_buf2, .count = strlen(ret_buf2), .cap = CAP_VIEW};
                }
                if (!ret_shallow) {
                    static char ret_ptr_buf2[256];
                    snprintf(ret_ptr_buf2, sizeof(ret_ptr_buf2), "%s *", ret_c.c_str);
                    ret_c = (Str){.c_str = (U8 *)ret_ptr_buf2, .count = strlen(ret_ptr_buf2), .cap = CAP_VIEW};
                }
            }
            EMIT(f, "(("); File_write_str(f, &ret_c); EMIT(f, " (*)(");
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) EMIT(f, ", ");
                Expr *arg = Expr_child(e, &(USize){(USize)(i)});
                Bool arg_shallow = 0;
                if (sig && i - 1 < sig->data.data.FuncDef.nparam) {
                    arg_shallow = PARAM_IS_SHALLOW(((Param*)Vec_get(&sig->data.data.FuncDef.params, &(USize){(USize)(i - 1)})));
                }
                Str arg_c = {.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT};
                if (arg->til_type.tag != TilType_TAG_Unknown && arg->til_type.tag != TilType_TAG_Dynamic) {
                    { Str *_t = til_type_to_c(arg->til_type); arg_c = *_t; free(_t); }
                    if ((arg->til_type.tag == TilType_TAG_Struct || arg->til_type.tag == TilType_TAG_Enum) && arg->struct_name.count > 0) {
                        static char arg_buf2[128];
                        snprintf(arg_buf2, sizeof(arg_buf2), "%s", arg->struct_name.c_str);
                        arg_c = (Str){.c_str = (U8 *)arg_buf2, .count = strlen(arg_buf2), .cap = CAP_VIEW};
                    }
                    if (!arg_shallow) {
                        static char arg_ptr_buf2[256];
                        snprintf(arg_ptr_buf2, sizeof(arg_ptr_buf2), "%s *", arg_c.c_str);
                        arg_c = (Str){.c_str = (U8 *)arg_ptr_buf2, .count = strlen(arg_ptr_buf2), .cap = CAP_VIEW};
                    }
                }
                File_write_str(f, &arg_c);
            }
            if (e->children.count == 1) EMIT(f, "void");
            EMIT(f, "))(");
            emit_expr(f, Expr_child(e, &(USize){(USize)(0)}), depth);
            EMIT(f, "))(");
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) EMIT(f, ", ");
                Bool arg_shallow = 0;
                if (sig && i - 1 < sig->data.data.FuncDef.nparam) {
                    arg_shallow = PARAM_IS_SHALLOW(((Param*)Vec_get(&sig->data.data.FuncDef.params, &(USize){(USize)(i - 1)})));
                }
                if (arg_shallow)
                    emit_deref(f, Expr_child(e, &(USize){(USize)(i)}), depth);
                else
                    emit_as_ptr(f, Expr_child(e, &(USize){(USize)(i)}), depth);
            }
            EMIT(f, ")");
            break;
        }
        // Namespace method call: Struct.method(args)
        if (Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FieldAccess) {
            Str *sname = &Expr_child(Expr_child(e, &(USize){(USize)(0)}), &(USize){0})->struct_name;
            Str *mname = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
            char flat_key[256];
            snprintf(flat_key, sizeof(flat_key), "%s_%s", sname->c_str, mname->c_str);
            Str *flat_str = Str_clone(&(Str){.c_str = (U8*)(flat_key), .count = (U64)strlen((const char*)(flat_key)), .cap = CAP_VIEW});
            EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, "(");
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) EMIT(f, ", ");
                if (callee_param_is_shallow(flat_str, i - 1))
                    emit_deref(f, Expr_child(e, &(USize){(USize)(i)}), depth);
                else if (callee_param_is_usize(flat_str, i - 1) && !callee_param_is_own(flat_str, i - 1))
                    emit_usize_ref(f, Expr_child(e, &(USize){(USize)(i)}), depth);
                else
                    emit_as_ptr(f, Expr_child(e, &(USize){(USize)(i)}), depth);
            }
            EMIT(f, ")");
            Str_delete(flat_str, &(Bool){1});
            break;
        }
        Str *name = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        if ((name->count == 8 && memcmp(name->c_str, "dyn_call", 8) == 0) || (name->count == 12 && memcmp(name->c_str, "dyn_call_ret", 12) == 0)) {
            // dyn_call(type_name, "method", arity, val, ...) → dyn_call_method(type_name, val, ...)
            Str *method = &Expr_child(e, &(USize){(USize)(2)})->data.data.Ident;
            I32 nargs = (I32)atol((char *)Expr_child(e, &(USize){(USize)(3)})->data.data.Ident.c_str);
            EMIT(f, "dyn_call_"); EMIT(f, (const char *)method->c_str); EMIT(f, "(");
            // Emit type_name as first arg
            emit_as_ptr(f, Expr_child(e, &(USize){(USize)(1)}), depth);
            // Emit exactly the declared dyn-call arity worth of args from child 4 onward.
            for (I32 ai = 0; ai < nargs; ai++) {
                EMIT(f, ", ");
                emit_as_ptr(f, Expr_child(e, &(USize){(USize)(ai + 4)}), depth);
            }
            EMIT(f, ")");
        } else if (name->count == 6 && memcmp(name->c_str, "dyn_fn", 6) == 0) {
            // dyn_fn(type_name, "method") → dyn_fn(type_name, &(Str){...})
            // Use stack-local Str instead of Str_lit() to avoid heap allocation leak
            EMIT(f, "dyn_fn(");
            emit_as_ptr(f, Expr_child(e, &(USize){(USize)(1)}), depth);
            EMIT(f, ", ");
            Expr *method_arg = Expr_child(e, &(USize){(USize)(2)});
            if (method_arg->data.tag == NodeType_TAG_LiteralStr) {
                EMIT(f, "&(Str){.c_str=(U8*)\""); EMIT(f, (const char *)method_arg->data.data.LiteralStr.c_str); EMIT(f, "\", .count="); emit_u64(f, method_arg->data.data.LiteralStr.count); EMIT(f, "ULL, .cap=TIL_CAP_LIT}");
            } else {
                emit_as_ptr(f, method_arg, depth);
            }
            EMIT(f, ")");
        } else if ((name->count == 5 && memcmp(name->c_str, "array", 5) == 0) || (name->count == 3 && memcmp(name->c_str, "vec", 3) == 0)) {
            // array("I64", 1, 2, 3) → array_of_I64(3, v1, v2, v3)
            // vec("I64", 1, 2, 3)   → vec_of_I64(3, v1, v2, v3)
            Str *elem_type = &Expr_child(e, &(USize){(USize)(1)})->data.data.Ident;
            I32 count = e->children.count - 2;
            const char *prefix = (name->count == 5 && memcmp(name->c_str, "array", 5) == 0) ? "array" : "vec";
            EMIT(f, (const char *)prefix); EMIT(f, "_of_"); EMIT(f, (const char *)elem_type->c_str); EMIT(f, "("); emit_i32(f, count);
            for (U32 i = 2; i < e->children.count; i++) {
                EMIT(f, ", ");
                emit_as_ptr(f, Expr_child(e, &(USize){(USize)(i)}), depth);
            }
            EMIT(f, ")");
        } else if ((name->count == 14 && memcmp(name->c_str, "dyn_has_method", 14) == 0)) {
            // dyn_has_method(type_name, "method") → dyn_has_method(type_name)
            Str *method = &Expr_child(e, &(USize){(USize)(2)})->data.data.Ident;
            EMIT(f, "dyn_has_"); EMIT(f, (const char *)method->c_str); EMIT(f, "(");
            emit_as_ptr(f, Expr_child(e, &(USize){(USize)(1)}), depth);
            EMIT(f, ")");
        } else if ((e->struct_name).count > 0 && Str_eq(name, &e->struct_name)) {
            // Struct constructor in expression context: hoist to temp via statement-expr
            Str *ctype = c_type_name(e->til_type, &e->struct_name);
            I32 id = _ctor_seq++;
            EMIT(f, "({ "); File_write_str(f, ctype); EMIT(f, " *_sc"); emit_i32(f, id); EMIT(f, " = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); ");
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_sc%d", id);
            emit_ctor_fields(f, tmp, e, depth);
            EMIT(f, " _sc"); emit_i32(f, id); EMIT(f, "; })");
        } else if (Expr_child(e, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_FuncPtr) {
            // Indirect call through function pointer variable
            // Use fn_sig to determine shallow params/return for correct cast
            Expr *sig = fcall_fn_sig(e);
            Bool ret_shallow = sig ? RETURN_IS_SHALLOW(&sig->data.data.FuncDef) : 0;
            Str ret_c = {.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT};
            if (e->til_type.tag != TilType_TAG_None && e->til_type.tag != TilType_TAG_Unknown &&
                e->til_type.tag != TilType_TAG_Dynamic) {
                { Str *_t = til_type_to_c(e->til_type); ret_c = *_t; free(_t); }
                if ((e->til_type.tag == TilType_TAG_Struct || e->til_type.tag == TilType_TAG_Enum) && e->struct_name.count > 0) {
                    static char ret_buf[128];
                    snprintf(ret_buf, sizeof(ret_buf), "%s", e->struct_name.c_str);
                    ret_c = (Str){.c_str = (U8 *)ret_buf, .count = strlen(ret_buf), .cap = CAP_VIEW};
                }
                if (!ret_shallow) {
                    static char ret_ptr_buf[256];
                    snprintf(ret_ptr_buf, sizeof(ret_ptr_buf), "%s *", ret_c.c_str);
                    ret_c = (Str){.c_str = (U8 *)ret_ptr_buf, .count = strlen(ret_ptr_buf), .cap = CAP_VIEW};
                }
            }
            EMIT(f, "(("); File_write_str(f, &ret_c); EMIT(f, " (*)(");
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) EMIT(f, ", ");
                Expr *arg = Expr_child(e, &(USize){(USize)(i)});
                Bool arg_shallow = 0;
                if (sig && i - 1 < sig->data.data.FuncDef.nparam) {
                    arg_shallow = PARAM_IS_SHALLOW(((Param*)Vec_get(&sig->data.data.FuncDef.params, &(USize){(USize)(i - 1)})));
                }
                Str arg_c = {.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT};
                if (arg->til_type.tag != TilType_TAG_Unknown && arg->til_type.tag != TilType_TAG_Dynamic) {
                    { Str *_t = til_type_to_c(arg->til_type); arg_c = *_t; free(_t); }
                    if ((arg->til_type.tag == TilType_TAG_Struct || arg->til_type.tag == TilType_TAG_Enum) && arg->struct_name.count > 0) {
                        static char arg_buf[128];
                        snprintf(arg_buf, sizeof(arg_buf), "%s", arg->struct_name.c_str);
                        arg_c = (Str){.c_str = (U8 *)arg_buf, .count = strlen(arg_buf), .cap = CAP_VIEW};
                    }
                    if (!arg_shallow) {
                        static char arg_ptr_buf[256];
                        snprintf(arg_ptr_buf, sizeof(arg_ptr_buf), "%s *", arg_c.c_str);
                        arg_c = (Str){.c_str = (U8 *)arg_ptr_buf, .count = strlen(arg_ptr_buf), .cap = CAP_VIEW};
                    }
                }
                File_write_str(f, &arg_c);
            }
            if (e->children.count == 1) EMIT(f, "void");
            if (is_ref_local(name)) {
                EMIT(f, "))(*"); EMIT(f, (const char *)name->c_str); EMIT(f, "))(");
            }
            else {
                EMIT(f, "))"); EMIT(f, (const char *)name->c_str); EMIT(f, ")(");
            }
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) EMIT(f, ", ");
                Bool arg_shallow2 = 0;
                if (sig && i - 1 < sig->data.data.FuncDef.nparam) {
                    arg_shallow2 = PARAM_IS_SHALLOW(((Param*)Vec_get(&sig->data.data.FuncDef.params, &(USize){(USize)(i - 1)})));
                }
                if (arg_shallow2)
                    emit_deref(f, Expr_child(e, &(USize){(USize)(i)}), depth);
                else
                    emit_as_ptr(f, Expr_child(e, &(USize){(USize)(i)}), depth);
            }
            EMIT(f, ")");
        } else {
            // User-defined function call
            { Str *_fc = func_to_c(name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) EMIT(f, ", ");
                if (callee_param_is_shallow(name, i - 1))
                    emit_deref(f, Expr_child(e, &(USize){(USize)(i)}), depth);
                else if (callee_param_is_usize(name, i - 1) && !callee_param_is_own(name, i - 1))
                    emit_usize_ref(f, Expr_child(e, &(USize){(USize)(i)}), depth);
                else
                    emit_as_ptr(f, Expr_child(e, &(USize){(USize)(i)}), depth);
            }
            EMIT(f, ")");
        }
        break;
    }
    case NodeType_TAG_FieldAccess: {
        Expr *obj = Expr_child(e, &(USize){(USize)(0)});
        Str *fname = &e->data.data.FieldAccess;
        if (e->is_ns_field) {
            if (e->til_type.tag == TilType_TAG_Enum) {
                // Bare variant ref: emit tag-only compound literal (no malloc)
                EMIT(f, "&("); EMIT(f, (const char *)obj->struct_name.c_str); EMIT(f, "){.tag = "); EMIT(f, (const char *)obj->struct_name.c_str); EMIT(f, "_TAG_"); EMIT(f, (const char *)fname->c_str); EMIT(f, "}");
            } else {
                EMIT(f, (const char *)obj->struct_name.c_str); EMIT(f, "_"); EMIT(f, (const char *)fname->c_str);
            }
        } else {
            emit_expr(f, obj, depth);
            EMIT(f, use_dot_access(obj) ? "." : "->"); EMIT(f, (const char *)fname->c_str);
        }
        break;
    }
    default:
        EMIT(f, "/* TODO: expr type "); emit_i32(f, e->data.tag); EMIT(f, " */");
        break;
    }
}

// --- Type to C type string ---



// Convert a type name string to C type string (handles struct types)
static Str *type_name_to_c(Str *name) {
    if ((name->count == 3 && memcmp(name->c_str, "I64", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"I64 *", .count = 5, .cap = CAP_LIT});
    if ((name->count == 2 && memcmp(name->c_str, "U8", 2) == 0))   return Str_clone(&(Str){.c_str = (U8 *)"U8 *", .count = 4, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "I16", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"I16 *", .count = 5, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "I32", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"I32 *", .count = 5, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "U32", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"U32 *", .count = 5, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "U64", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"U64 *", .count = 5, .cap = CAP_LIT});
    if ((name->count == 5 && memcmp(name->c_str, "USize", 5) == 0)) return Str_clone(&(Str){.c_str = (U8 *)"USize *", .count = 7, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "F32", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"F32 *", .count = 5, .cap = CAP_LIT});
    if ((name->count == 4 && memcmp(name->c_str, "Bool", 4) == 0)) return Str_clone(&(Str){.c_str = (U8 *)"Bool *", .count = 6, .cap = CAP_LIT});
    if ((name->count == 7 && memcmp(name->c_str, "Dynamic", 7) == 0)) return Str_clone(&(Str){.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT});
    if ((name->count == 2 && memcmp(name->c_str, "Fn", 2) == 0))      return Str_clone(&(Str){.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT}); // function pointer (opaque)
    // Named FuncSig type -> void * (opaque function pointer)
    if (has_funcsig_names) {
        Str key = {name->c_str, name->count, CAP_VIEW};
        if (Set_has(&funcsig_names, &key)) return Str_clone(&(Str){.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT});
    }
    // User-defined struct type -- pointer
    static char buf[128];
    snprintf(buf, sizeof(buf), "%s *", name->c_str);
    return Str_clone(&(Str){.c_str = (U8 *)buf, .count = strlen(buf), .cap = CAP_VIEW});
}

// Like type_name_to_c but without pointer -- for inline union fields
static Str *type_name_to_c_value(Str *name) {
    if ((name->count == 3 && memcmp(name->c_str, "I64", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"I64", .count = 3, .cap = CAP_LIT});
    if ((name->count == 2 && memcmp(name->c_str, "U8", 2) == 0))   return Str_clone(&(Str){.c_str = (U8 *)"U8", .count = 2, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "I16", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"I16", .count = 3, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "I32", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"I32", .count = 3, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "U32", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"U32", .count = 3, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "U64", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"U64", .count = 3, .cap = CAP_LIT});
    if ((name->count == 5 && memcmp(name->c_str, "USize", 5) == 0)) return Str_clone(&(Str){.c_str = (U8 *)"USize", .count = 5, .cap = CAP_LIT});
    if ((name->count == 3 && memcmp(name->c_str, "F32", 3) == 0))  return Str_clone(&(Str){.c_str = (U8 *)"F32", .count = 3, .cap = CAP_LIT});
    if ((name->count == 4 && memcmp(name->c_str, "Bool", 4) == 0)) return Str_clone(&(Str){.c_str = (U8 *)"Bool", .count = 4, .cap = CAP_LIT});
    if ((name->count == 7 && memcmp(name->c_str, "Dynamic", 7) == 0)) return Str_clone(&(Str){.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT});
    if ((name->count == 2 && memcmp(name->c_str, "Fn", 2) == 0))   return Str_clone(&(Str){.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT}); // function pointer (opaque)
    // Named FuncSig type -> void * (opaque function pointer)
    if (has_funcsig_names) {
        Str key = {name->c_str, name->count, CAP_VIEW};
        if (Set_has(&funcsig_names, &key)) return Str_clone(&(Str){.c_str = (U8 *)"void *", .count = 6, .cap = CAP_LIT});
    }
    static char buf2[128];
    snprintf(buf2, sizeof(buf2), "%s", name->c_str);
    return Str_clone(&(Str){.c_str = (U8 *)buf2, .count = strlen(buf2), .cap = CAP_VIEW});
}

// is_primitive_type: moved to builder.til

// is_funcsig_type: moved to builder.til

// Emit a function parameter list (with variadic support)
static void emit_param_list(File *f, Expr *fdef, Bool with_names) {
    U32 np = fdef->data.data.FuncDef.nparam;
    I32 fvi = fdef->data.data.FuncDef.variadic_index;
    if (np == 0) {
        EMIT(f, "void");
    } else {
        for (U32 i = 0; i < np; i++) {
            if (i > 0) EMIT(f, ", ");
            Str *ptype;
            I32 fkwi = fdef->data.data.FuncDef.kwargs_index;
            if ((I32)i == fvi) {
                ptype = Str_clone(&(Str){.c_str = (U8 *)"Array *", .count = 7, .cap = CAP_LIT});
            } else if ((I32)i == fkwi) {
                Param *_epi = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(i)});
                ptype = type_name_to_c(&_epi->ptype);
            } else {
                Param *_epi = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(i)});
                if (PARAM_IS_SHALLOW(_epi)) {
                    ptype = type_name_to_c_value(&_epi->ptype);
                } else {
                    ptype = type_name_to_c(&_epi->ptype);
                }
            }
            if (with_names) {
                File_write_str(f, ptype); EMIT(f, " "); EMIT(f, (const char *)((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(i)}))->name.c_str);
            }
            else
                File_write_str(f, ptype);
        }
    }
}

static void emit_deref(File *f, Expr *e, I32 depth) {
    if (e->til_type.tag == TilType_TAG_Dynamic) {
        // Dynamic (void *) IS the value — no dereference needed
        emit_expr(f, e, depth);
    } else if (e->til_type.tag == TilType_TAG_FuncPtr) {
        // Function pointer: cast to void *
        // ref locals need DEREF (pointer to fn-ptr -> fn-ptr)
        if (e->data.tag == NodeType_TAG_Ident && is_ref_local(&e->data.data.Ident)) {
            EMIT(f, "(void *)DEREF(");
            emit_expr(f, e, depth);
            EMIT(f, ")");
        } else {
            EMIT(f, "(void *)");
            emit_expr(f, e, depth);
        }
    } else if (e->data.tag == NodeType_TAG_Ident) {
        if (is_shallow_param(&e->data.data.Ident) ||
            is_stack_local(&e->data.data.Ident) ||
            is_value_global(&e->data.data.Ident)) {
            emit_expr(f, e, depth); // shallow param/local is already a value
        } else {
            EMIT(f, "DEREF(");
            emit_expr(f, e, depth);
            EMIT(f, ")");
        }
    } else if (e->data.tag == NodeType_TAG_LiteralStr) {
        EMIT(f, "(Str){.c_str=(U8*)\""); EMIT(f, (const char *)e->data.data.Ident.c_str); EMIT(f, "\", .count="); emit_u64(f, e->data.data.Ident.count); EMIT(f, "ULL, .cap=TIL_CAP_LIT}");
    } else if (e->data.tag == NodeType_TAG_FieldAccess && e->is_ns_field && e->til_type.tag == TilType_TAG_Enum) {
        // Auto-called constructor returns pointer; dereference it
        EMIT(f, "(*");
        emit_expr(f, e, depth);
        EMIT(f, ")");
    } else {
        emit_expr(f, e, depth);
    }
}

// Emit expression as a pointer — after hoisting, args are NodeType_TAG_Ident (already pointer)
// or NodeType_TAG_FieldAccess (value needing compound literal wrapping).
static void emit_as_ptr(File *f, Expr *e, I32 depth) {
    if (e->data.tag == NodeType_TAG_Ident &&
        (is_shallow_param(&e->data.data.Ident) ||
         is_stack_local(&e->data.data.Ident) ||
         is_value_global(&e->data.data.Ident))) {
        // Shallow params and stack locals are stable lvalues.
        if (e->is_own_arg) {
            // Callee will free() this pointer — must malloc a copy
            Str *ctype = get_stack_local_ctype(&e->data.data.Ident);
            if (!ctype) ctype = c_type_name(e->til_type, &e->struct_name);
            EMIT(f, "({ "); File_write_str(f, ctype); EMIT(f, " *_oa = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); *_oa = ");
            emit_expr(f, e, depth);
            EMIT(f, "; _oa; })");
        } else {
            EMIT(f, "&"); EMIT(f, (const char *)e->data.data.Ident.c_str);
        }
    } else if (e->data.tag == NodeType_TAG_FCall && e->struct_name.count > 0 && e->children.count > 0 &&
               Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_Ident &&
               Str_eq(&Expr_child(e, &(USize){(USize)(0)})->data.data.Ident, &e->struct_name)) {
        // Struct constructor in expression context: hoist to temp via statement-expr
        Str *ctype = c_type_name(e->til_type, &e->struct_name);
        I32 id = _ctor_seq++;
        EMIT(f, "({ "); File_write_str(f, ctype); EMIT(f, " *_sc"); emit_i32(f, id); EMIT(f, " = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); ");
        char tmp[32];
        snprintf(tmp, sizeof(tmp), "_sc%d", id);
        emit_ctor_fields(f, tmp, e, depth);
        EMIT(f, " _sc"); emit_i32(f, id); EMIT(f, "; })");
    } else if (e->data.tag == NodeType_TAG_Ident || e->data.tag == NodeType_TAG_FCall || e->data.tag == NodeType_TAG_LiteralStr) {
        emit_expr(f, e, depth);
    } else if (e->data.tag == NodeType_TAG_FieldAccess) {
        // Own field is already a pointer; enum ns_field constructor returns pointer;
        // Dynamic field is void* (already a pointer); inline field needs address-of
        if (FIELD_IS_PTR(e) || (e->is_ns_field && e->til_type.tag == TilType_TAG_Enum) ||
            e->til_type.tag == TilType_TAG_Dynamic) {
            emit_expr(f, e, depth);
        } else {
            EMIT(f, "&");
            emit_expr(f, e, depth);
        }
    } else if (e->data.tag == NodeType_TAG_LiteralNull) {
        EMIT(f, "NULL");
    } else {
        Str *ctype = c_type_name(e->til_type, &e->struct_name);
        EMIT(f, "&("); File_write_str(f, ctype); EMIT(f, "){");
        emit_expr(f, e, depth);
        EMIT(f, "}");
    }
}

static void emit_usize_ref(File *f, Expr *e, I32 depth) {
    EMIT(f, "USIZE_REF(");
    emit_deref(f, e, depth);
    EMIT(f, ")");
}

// Emit struct constructor field assignments into 'var' (already malloc'd).
static void emit_ctor_fields(File *f, const char *var, Expr *ctor, I32 depth) {
    Expr *sbody = find_struct_body(&ctor->struct_name);
    U32 fi = 0;
    for (U32 i = 1; i < ctor->children.count; i++) {
        OwnType_tag fld_own = OwnType_TAG_Shallow;
        TilType field_type = {0};
        const char *fname = NULL;
        if (sbody) {
            for (; fi < sbody->children.count; fi++) {
                if (!Expr_child(sbody, &(USize){(USize)(fi)})->data.data.Decl.is_namespace) {
                    Expr *fld = Expr_child(sbody, &(USize){(USize)(fi)});
                    fld_own = fld->data.data.Decl.own_type.tag;
                    field_type = fld->til_type;
                    fname = (const char *)fld->data.data.Decl.name.c_str;
                    fi++;
                    break;
                }
            }
        }
        Expr *arg = Expr_child(ctor, &(USize){(USize)(i)});
        emit_indent(f, depth);
        if (fld_own == OwnType_TAG_Ref) {
            // Ref field: store pointer directly (no deref)
            emit_field(f, var, fname); EMIT(f, " = ");
            emit_expr(f, arg, depth);
            EMIT(f, ";\n");
        } else if (fld_own == OwnType_TAG_Own && arg->data.tag == NodeType_TAG_FCall && arg->struct_name.count > 0 &&
            Str_eq(&Expr_child(arg, &(USize){(USize)(0)})->data.data.Ident, &arg->struct_name)) {
            // Nested struct constructor for own field: emit as temp, assign pointer
            Str *ct = c_type_name(arg->til_type, &arg->struct_name);
            I32 id = _ctor_seq++;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_cs%d", id);
            File_write_str(f, ct); EMIT(f, " *"); EMIT(f, (const char *)tmp); EMIT(f, " = malloc(sizeof("); File_write_str(f, ct); EMIT(f, "));\n");
            emit_ctor_fields(f, tmp, arg, depth);
            emit_indent(f, depth);
            emit_field(f, var, fname); EMIT(f, " = "); EMIT(f, (const char *)tmp); EMIT(f, ";\n");
        } else if (fld_own == OwnType_TAG_Own) {
            emit_field(f, var, fname); EMIT(f, " = ");
            arg->is_own_arg = true;
            emit_as_ptr(f, arg, depth);
            EMIT(f, ";\n");
        } else if (arg->data.tag == NodeType_TAG_FCall && arg->struct_name.count > 0 &&
                   Str_eq(&Expr_child(arg, &(USize){(USize)(0)})->data.data.Ident, &arg->struct_name)) {
            // Inline struct field: nested constructor -- build in-place
            Str *ct = c_type_name(arg->til_type, &arg->struct_name);
            I32 id = _ctor_seq++;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_cs%d", id);
            File_write_str(f, ct); EMIT(f, " *"); EMIT(f, (const char *)tmp); EMIT(f, " = malloc(sizeof("); File_write_str(f, ct); EMIT(f, "));\n");
            emit_ctor_fields(f, tmp, arg, depth);
            emit_indent(f, depth);
            emit_field(f, var, fname); EMIT(f, " = *"); EMIT(f, (const char *)tmp); EMIT(f, "; free("); EMIT(f, (const char *)tmp); EMIT(f, ");\n");
        } else if (arg->data.tag == NodeType_TAG_FCall) {
            // Non-ref fields that are really scalar/pointer-like should take the
            // call result directly, not through heap-wrapper unboxing.
            if (field_type.tag == TilType_TAG_FuncPtr ||
                field_type.tag == TilType_TAG_Dynamic ||
                fcall_is_shallow_return(arg) ||
                fcall_returns_dynamic(arg)) {
                emit_field(f, var, fname); EMIT(f, " = ");
                emit_expr(f, arg, depth);
                EMIT(f, ";\n");
            } else {
                // Heap-returning value field: unbox the returned wrapper.
                Str *ftype = c_type_name(arg->til_type, &arg->struct_name);
                EMIT(f, "{ "); File_write_str(f, ftype); EMIT(f, " *_ca = ");
                emit_expr(f, arg, depth);
                EMIT(f, "; "); emit_field(f, var, fname); EMIT(f, " = *_ca; free(_ca); }\n");
            }
        } else {
            emit_field(f, var, fname); EMIT(f, " = ");
            emit_deref(f, arg, depth);
            EMIT(f, ";\n");
        }
    }
}

// --- Statement emission ---

static void emit_stmt(File *f, Expr *e, I32 depth) {
    emit_indent(f, depth);
    switch (e->data.tag) {
    case NodeType_TAG_Decl:
        if (e->til_type.tag == TilType_TAG_FuncPtr && !DECL_IS_REF(e->data.data.Decl) && Expr_child(e, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) {
            // Function pointer variable (non-ref): void *f = (void *)func_name;
            EMIT(f, "void *"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
            emit_expr(f, Expr_child(e, &(USize){(USize)(0)}), depth);
            EMIT(f, ";\n");
            emit_indent(f, depth);
            EMIT(f, "(void)"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, ";\n");
        } else if (Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
            EMIT(f, "/* TODO: nested func "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " */\n");
        } else if (Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                   Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
            EMIT(f, "/* "); EMIT(f, Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef ? "enum" : "struct"); EMIT(f, " "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " defined above */\n");
        } else if (e->til_type.tag == TilType_TAG_None && Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_Ident) {
            // Type alias: typer resolves all references to canonical name,
            // so no typedef needed in generated C
            ;
        } else {
            if (DECL_IS_REF(e->data.data.Decl)) {
                Set_add(&ref_locals, Str_clone(&e->data.data.Decl.name));
                Str *_sn = &e->struct_name;
                if (_sn->count == 0) _sn = &Expr_child(e, &(USize){(USize)(0)})->struct_name;
                if (_sn->count == 0) _sn = &e->data.data.Decl.explicit_type;
                Str *ctype = c_type_name(e->til_type, _sn);
                Expr *rhs = Expr_child(e, &(USize){(USize)(0)});
                File_write_str(f, ctype); EMIT(f, " *"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                emit_as_ptr(f, rhs, depth);
                EMIT(f, ";\n");
            } else {
                Str *_sn = &e->struct_name;
                if (_sn->count == 0) _sn = &Expr_child(e, &(USize){(USize)(0)})->struct_name;
                if (_sn->count == 0) _sn = &e->data.data.Decl.explicit_type;
                Str *ctype = c_type_name(e->til_type, _sn);
                Expr *rhs = Expr_child(e, &(USize){(USize)(0)});
                Bool is_global = has_script_globals && !in_func_def && Set_has(&script_globals, &e->data.data.Decl.name);
                if (e->til_type.tag == TilType_TAG_Dynamic) {
                    if (is_global) {
                        EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                    }
                    else {
                        { Str *_tc = til_type_to_c(e->til_type); File_write_str(f, _tc); Str_delete(_tc, &(Bool){1}); } EMIT(f, " "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                    }
                    emit_deref(f, rhs, depth);
                    EMIT(f, ";\n");
                } else {
                    Bool can_hoist = !is_global && !DECL_IS_OWN(e->data.data.Decl) &&
                                     e->til_type.tag != TilType_TAG_FuncPtr &&
                                     e->til_type.tag != TilType_TAG_Dynamic &&
                                     !(rhs->data.tag == NodeType_TAG_FCall && fcall_returns_dynamic(rhs));
                    if (rhs->data.tag == NodeType_TAG_FCall && rhs->struct_name.count > 0 &&
                        Str_eq(&Expr_child(rhs, &(USize){(USize)(0)})->data.data.Ident, &rhs->struct_name)) {
                    // Struct constructor
                    const char *var = (const char *)e->data.data.Decl.name.c_str;
                    if (is_global) {
                        EMIT(f, "memset(&"); EMIT(f, (const char *)var); EMIT(f, ", 0, sizeof("); File_write_str(f, ctype); EMIT(f, "));\n");
                    } else if (can_hoist) {
                        File_write_str(f, ctype); EMIT(f, " "); EMIT(f, (const char *)var); EMIT(f, "; memset(&"); EMIT(f, (const char *)var); EMIT(f, ", 0, sizeof("); File_write_str(f, ctype); EMIT(f, "));\n");
                        Set_add(&stack_locals, Str_clone(&e->data.data.Decl.name));
                        { Str *_k = Str_clone(&e->data.data.Decl.name); Str *_v = Str_clone(&(Str){.c_str = ctype->c_str, .count = ctype->count, .cap = CAP_VIEW}); void *_vp = malloc(sizeof(Str *)); memcpy(_vp, &_v, sizeof(Str *)); Map_set(&stack_local_types, _k, _vp); }
                    } else {
                        File_write_str(f, ctype); EMIT(f, " *"); EMIT(f, (const char *)var); EMIT(f, " = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, "));\n");
                    }
                    emit_ctor_fields(f, var, rhs, depth);
                    } else if (rhs->data.tag == NodeType_TAG_FCall || rhs->data.tag == NodeType_TAG_LiteralStr ||
                               (rhs->data.tag == NodeType_TAG_FieldAccess && rhs->is_ns_field && rhs->til_type.tag == TilType_TAG_Enum)) {
                    if (is_global) {
                        if (rhs->data.tag == NodeType_TAG_FCall && fcall_is_shallow_return(rhs)) {
                            EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                            emit_expr(f, rhs, depth);
                            EMIT(f, ";\n");
                        } else if (rhs->data.tag == NodeType_TAG_FCall) {
                            Str *htype = fcall_return_ctype(rhs);
                            if (!htype) htype = ctype;
                            EMIT(f, "{ "); File_write_str(f, htype); EMIT(f, " *_hp = ("); File_write_str(f, htype); EMIT(f, " *)");
                            emit_expr(f, rhs, depth);
                            EMIT(f, "; "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = *_hp; free(_hp); }\n");
                        } else {
                            EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                            emit_deref(f, rhs, depth);
                            EMIT(f, ";\n");
                        }
                    } else if (rhs->data.tag == NodeType_TAG_FCall && fcall_is_shallow_return(rhs)) {
                        if (can_hoist) {
                            // Shallow-return scalar fcall -- stack value directly
                            // Use callee's return type to avoid signedness mismatches
                            Str *htype = fcall_return_ctype(rhs);
                            if (!htype) htype = ctype;
                            File_write_str(f, htype); EMIT(f, " "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                            emit_expr(f, rhs, depth);
                            EMIT(f, ";\n");
                            Set_add(&stack_locals, Str_clone(&e->data.data.Decl.name));
                            { Str *_k = Str_clone(&e->data.data.Decl.name); Str *_v = Str_clone(&(Str){.c_str = htype->c_str, .count = htype->count, .cap = CAP_VIEW}); void *_vp = malloc(sizeof(Str *)); memcpy(_vp, &_v, sizeof(Str *)); Map_set(&stack_local_types, _k, _vp); }
                        } else {
                            // returns shallow: C function returns value, box into pointer
                            const char *var = (const char *)e->data.data.Decl.name.c_str;
                            File_write_str(f, ctype); EMIT(f, " *"); EMIT(f, (const char *)var); EMIT(f, " = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); *"); EMIT(f, (const char *)var); EMIT(f, " = ");
                            emit_expr(f, rhs, depth);
                            EMIT(f, ";\n");
                        }
                    } else if (can_hoist && rhs->data.tag == NodeType_TAG_FCall) {
                        // Non-shallow fcall returning scalar -- unbox heap pointer to stack
                        // Use callee's return type to avoid signedness mismatches
                        Str *htype = fcall_return_ctype(rhs);
                        if (!htype) htype = ctype;
                        File_write_str(f, htype); EMIT(f, " "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, "; { "); File_write_str(f, htype); EMIT(f, " *_hp = ("); File_write_str(f, htype); EMIT(f, " *)");
                        emit_expr(f, rhs, depth);
                        EMIT(f, "; "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = *_hp; free(_hp); }\n");
                        Set_add(&stack_locals, Str_clone(&e->data.data.Decl.name));
                        { Str *_k = Str_clone(&e->data.data.Decl.name); Str *_v = Str_clone(&(Str){.c_str = htype->c_str, .count = htype->count, .cap = CAP_VIEW}); void *_vp = malloc(sizeof(Str *)); memcpy(_vp, &_v, sizeof(Str *)); Map_set(&stack_local_types, _k, _vp); }
                    } else if (can_hoist) {
                        File_write_str(f, ctype); EMIT(f, " "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, "; { "); File_write_str(f, ctype); EMIT(f, " *_hp = ("); File_write_str(f, ctype); EMIT(f, " *)");
                        emit_expr(f, rhs, depth);
                        EMIT(f, "; "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = *_hp; free(_hp); }\n");
                        Set_add(&stack_locals, Str_clone(&e->data.data.Decl.name));
                        { Str *_k = Str_clone(&e->data.data.Decl.name); Str *_v = Str_clone(&(Str){.c_str = ctype->c_str, .count = ctype->count, .cap = CAP_VIEW}); void *_vp = malloc(sizeof(Str *)); memcpy(_vp, &_v, sizeof(Str *)); Map_set(&stack_local_types, _k, _vp); }
                    } else {
                        if (is_global) {
                            EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                        }
                        else {
                            File_write_str(f, ctype); EMIT(f, " *"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                        }
                        emit_expr(f, rhs, depth);
                        EMIT(f, ";\n");
                    }
                    } else {
                    if (is_global) {
                        EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                        emit_deref(f, rhs, depth);
                        EMIT(f, ";\n");
                    } else if (can_hoist) {
                        // Scalar literal/ident -- stack value
                        File_write_str(f, ctype); EMIT(f, " "); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                        emit_deref(f, rhs, depth);
                        EMIT(f, ";\n");
                        Set_add(&stack_locals, Str_clone(&e->data.data.Decl.name));
                        { Str *_k = Str_clone(&e->data.data.Decl.name); Str *_v = Str_clone(&(Str){.c_str = ctype->c_str, .count = ctype->count, .cap = CAP_VIEW}); void *_vp = malloc(sizeof(Str *)); memcpy(_vp, &_v, sizeof(Str *)); Map_set(&stack_local_types, _k, _vp); }
                    } else {
                        File_write_str(f, ctype); EMIT(f, " *"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, "));\n");
                        emit_indent(f, depth);
                        EMIT(f, "*"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, " = ");
                        emit_deref(f, rhs, depth);
                        EMIT(f, ";\n");
                    }
                }
                }
            }
            // Suppress unused-variable warnings for all declarations
            emit_indent(f, depth);
            EMIT(f, "(void)"); EMIT(f, (const char *)e->data.data.Decl.name.c_str); EMIT(f, ";\n");
        }
        break;
    case NodeType_TAG_Assign: {
        Expr *rhs = Expr_child(e, &(USize){(USize)(0)});
        if (e->save_old_delete) {
            Str *ctype = c_type_name(e->til_type, &e->struct_name);
            if (is_stack_local(&e->data.data.Assign)) {
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_new = ("); File_write_str(f, ctype); EMIT(f, " *)");
                emit_expr(f, rhs, depth);
                EMIT(f, "; "); File_write_str(f, ctype); EMIT(f, "_delete(&"); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, ", &(Bool){0}); "); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = *_new; free(_new); }\n");
            } else if (is_value_global(&e->data.data.Assign)) {
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_new = ("); File_write_str(f, ctype); EMIT(f, " *)");
                emit_expr(f, rhs, depth);
                EMIT(f, "; "); File_write_str(f, ctype); EMIT(f, "_delete(&"); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, ", &(Bool){0}); "); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = *_new; free(_new); }\n");
            } else {
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_old = "); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, "; "); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                emit_expr(f, rhs, depth);
                EMIT(f, "; "); File_write_str(f, ctype); EMIT(f, "_delete(_old, &(Bool){1}); }\n");
            }
            break;
        }
        Bool is_hoisted = is_stack_local(&e->data.data.Assign) ||
                          is_value_global(&e->data.data.Assign);
        if (e->til_type.tag == TilType_TAG_Dynamic) {
            EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
            emit_deref(f, rhs, depth);
            EMIT(f, ";\n");
            break;
        }
        if (is_hoisted) {
            if (rhs->data.tag == NodeType_TAG_FCall && fcall_is_shallow_return(rhs)) {
                EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                emit_expr(f, rhs, depth);
                EMIT(f, ";\n");
            } else if (rhs->data.tag == NodeType_TAG_FCall) {
                // Non-shallow fcall: unbox heap pointer
                Str *ctype = c_type_name(e->til_type, &e->struct_name);
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_hp = ("); File_write_str(f, ctype); EMIT(f, " *)");
                emit_expr(f, rhs, depth);
                EMIT(f, "; "); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = *_hp; free(_hp); }\n");
            } else {
                EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                emit_deref(f, rhs, depth);
                EMIT(f, ";\n");
            }
        } else {
            if (rhs->data.tag == NodeType_TAG_FCall || rhs->data.tag == NodeType_TAG_LiteralStr ||
                (rhs->data.tag == NodeType_TAG_FieldAccess && rhs->is_ns_field && rhs->til_type.tag == TilType_TAG_Enum)) {
                if (rhs->data.tag == NodeType_TAG_FCall && fcall_is_shallow_return(rhs)) {
                    EMIT(f, "*"); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                } else {
                    EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                }
                emit_expr(f, rhs, depth);
            } else if (e->til_type.tag == TilType_TAG_FuncPtr) {
                // Function pointer: assign opaque pointer directly (no deref)
                EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                emit_expr(f, rhs, depth);
            } else {
                EMIT(f, "*"); EMIT(f, (const char *)e->data.data.Assign.c_str); EMIT(f, " = ");
                emit_deref(f, rhs, depth);
            }
            EMIT(f, ";\n");
        }
        break;
    }
    case NodeType_TAG_FieldAssign: {
        Expr *obj = Expr_child(e, &(USize){(USize)(0)});
        Str *fname = &e->data.data.FieldAssign;
        if (Expr_child(e, &(USize){(USize)(1)})->data.tag == NodeType_TAG_FCall && FIELD_IS_SHALLOW(e) && !e->is_ns_field) {
            if (fcall_is_shallow_return(Expr_child(e, &(USize){(USize)(1)}))) {
                // Shallow-return fcall: value directly assigned to inline field
                emit_expr(f, obj, depth);
                EMIT(f, use_dot_access(obj) ? "." : "->"); EMIT(f, (const char *)fname->c_str); EMIT(f, " = ");
                emit_expr(f, Expr_child(e, &(USize){(USize)(1)}), depth);
                EMIT(f, ";\n");
            } else {
                // Non-shallow fcall for inline compound field: deref + free wrapper
                Str *ftype = c_type_name(Expr_child(e, &(USize){(USize)(1)})->til_type, &Expr_child(e, &(USize){(USize)(1)})->struct_name);
                EMIT(f, "{ "); File_write_str(f, ftype); EMIT(f, " *_fa = ");
                emit_expr(f, Expr_child(e, &(USize){(USize)(1)}), depth);
                EMIT(f, "; ");
                emit_expr(f, obj, depth);
                EMIT(f, use_dot_access(obj) ? "." : "->"); EMIT(f, (const char *)fname->c_str); EMIT(f, " = *_fa; free(_fa); }\n");
            }
        } else {
            if (e->is_ns_field) {
                EMIT(f, (const char *)obj->struct_name.c_str); EMIT(f, "_"); EMIT(f, (const char *)fname->c_str); EMIT(f, " = ");
            } else {
                emit_expr(f, obj, depth);
                EMIT(f, use_dot_access(obj) ? "." : "->"); EMIT(f, (const char *)fname->c_str); EMIT(f, " = ");
            }
            if (FIELD_IS_PTR(e)) {
                Expr_child(e, &(USize){(USize)(1)})->is_own_arg = true;
                emit_as_ptr(f, Expr_child(e, &(USize){(USize)(1)}), depth);
            } else {
                emit_deref(f, Expr_child(e, &(USize){(USize)(1)}), depth);
            }
            EMIT(f, ";\n");
        }
        break;
    }
    case NodeType_TAG_FCall:
        // Suppress delete for hoisted scalars (no-op, avoids pre-existing type mismatch)
        if (Expr_child(e, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FieldAccess &&
            (Expr_child(e, &(USize){(USize)(0)})->data.data.Ident.count == 6 && memcmp(Expr_child(e, &(USize){(USize)(0)})->data.data.Ident.c_str, "delete", 6) == 0) &&
            e->children.count >= 2 &&
            Expr_child(e, &(USize){(USize)(1)})->data.tag == NodeType_TAG_Ident &&
            is_stack_local(&Expr_child(e, &(USize){(USize)(1)})->data.data.Ident) &&
            Expr_child(e, &(USize){(USize)(1)})->til_type.tag != TilType_TAG_Struct &&
            Expr_child(e, &(USize){(USize)(1)})->til_type.tag != TilType_TAG_Enum) {
            EMIT(f, ";\n");
            break;
        }
        if ((e->struct_name).count > 0 && Str_eq(&Expr_child(e, &(USize){(USize)(0)})->data.data.Ident, &e->struct_name)) {
            // Bare struct constructor statement — discard result
            EMIT(f, "/* discarded struct constructor */;\n");
        } else {
            emit_expr(f, e, depth);
            EMIT(f, ";\n");
        }
        break;
    case NodeType_TAG_Return:
        if (e->children.count == 0) {
            if (in_main_func)
                EMIT(f, "return 0;\n");
            else
                EMIT(f, "return;\n");
        } else {
            Expr *rv = Expr_child(e, &(USize){(USize)(0)});
            if (rv->data.tag == NodeType_TAG_FCall && rv->struct_name.count > 0 &&
                Str_eq(&Expr_child(rv, &(USize){(USize)(0)})->data.data.Ident, &rv->struct_name)) {
                // Struct constructor return -- malloc + field-by-field
                Str *ctype = c_type_name(rv->til_type, &rv->struct_name);
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, "));\n");
                emit_ctor_fields(f, "_r", rv, depth);
                emit_indent(f, depth);
                EMIT(f, "return _r; }\n");
            } else if (current_fdef && RETURN_IS_REF(&current_fdef->data.data.FuncDef)) {
                EMIT(f, "return ");
                emit_as_ptr(f, rv, depth);
                EMIT(f, ";\n");
            } else if (current_fdef && RETURN_IS_SHALLOW(&current_fdef->data.data.FuncDef)) {
                // Shallow-return function — return value directly
                if (rv->data.tag == NodeType_TAG_FCall && fcall_is_shallow_return(rv)) {
                    EMIT(f, "return ");
                    emit_expr(f, rv, depth);
                    EMIT(f, ";\n");
                } else {
                    EMIT(f, "return ");
                    emit_deref(f, rv, depth);
                    EMIT(f, ";\n");
                }
            } else if (rv->data.tag == NodeType_TAG_FieldAccess && FIELD_IS_SHALLOW(rv) &&
                       !rv->is_ns_field && rv->til_type.tag != TilType_TAG_Dynamic) {
                // Inline field value -- must clone to heap pointer for return
                Str *ctype = (current_fdef && current_fdef->data.data.FuncDef.return_type.count > 0)
                    ? type_name_to_c_value(&current_fdef->data.data.FuncDef.return_type)
                    : c_type_name(rv->til_type, &rv->struct_name);
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); *_r = ");
                emit_expr(f, rv, depth);
                EMIT(f, "; return _r; }\n");
            } else if (rv->data.tag == NodeType_TAG_FCall && fcall_is_shallow_return(rv)) {
                // returns shallow: box value return into heap pointer
                Str *ctype = (current_fdef && current_fdef->data.data.FuncDef.return_type.count > 0)
                    ? type_name_to_c_value(&current_fdef->data.data.FuncDef.return_type)
                    : c_type_name(rv->til_type, &rv->struct_name);
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); *_r = ");
                emit_expr(f, rv, depth);
                EMIT(f, "; return _r; }\n");
            } else if (rv->data.tag == NodeType_TAG_Ident &&
                       is_stack_local(&rv->data.data.Ident) &&
                       !(current_fdef && RETURN_IS_SHALLOW(&current_fdef->data.data.FuncDef))) {
                // Hoisted local returned from non-shallow function: box to heap
                Str *ctype = (current_fdef && current_fdef->data.data.FuncDef.return_type.count > 0)
                    ? type_name_to_c_value(&current_fdef->data.data.FuncDef.return_type)
                    : c_type_name(rv->til_type, &rv->struct_name);
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); *_r = "); EMIT(f, (const char *)rv->data.data.Ident.c_str); EMIT(f, "; return _r; }\n");
            } else if (rv->data.tag == NodeType_TAG_Ident &&
                       has_script_globals && Set_has(&script_globals, &rv->data.data.Ident) &&
                       !(current_fdef && RETURN_IS_SHALLOW(&current_fdef->data.data.FuncDef))) {
                // Global returned from non-shallow function: copy to heap
                Str *ctype = (current_fdef && current_fdef->data.data.FuncDef.return_type.count > 0)
                    ? type_name_to_c_value(&current_fdef->data.data.FuncDef.return_type)
                    : c_type_name(rv->til_type, &rv->struct_name);
                EMIT(f, "{ "); File_write_str(f, ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ctype); EMIT(f, ")); *_r = "); EMIT(f, (const char *)rv->data.data.Ident.c_str); EMIT(f, "; return _r; }\n");
            } else if (rv->data.tag == NodeType_TAG_FieldAccess && rv->is_ns_field &&
                       rv->til_type.tag == TilType_TAG_Enum) {
                // Bare variant ref return: heap-allocate (compound literal is stack-only)
                Str *sn = &Expr_child(rv, &(USize){(USize)(0)})->struct_name;
                EMIT(f, "{ "); EMIT(f, (const char *)sn->c_str); EMIT(f, " *_r = malloc(sizeof("); EMIT(f, (const char *)sn->c_str); EMIT(f, ")); _r->tag = "); EMIT(f, (const char *)sn->c_str); EMIT(f, "_TAG_"); EMIT(f, (const char *)rv->data.data.FieldAccess.c_str); EMIT(f, "; return _r; }\n");
            } else {
                EMIT(f, "return ");
                emit_expr(f, rv, depth);
                EMIT(f, ";\n");
            }
        }
        break;
    case NodeType_TAG_Body:
        EMIT(f, "{\n");
        emit_body_scoped(f, e, depth + 1);
        emit_indent(f, depth);
        EMIT(f, "}\n");
        break;
    case NodeType_TAG_If:
        EMIT(f, "if (");
        emit_deref(f, Expr_child(e, &(USize){(USize)(0)}), depth);
        EMIT(f, ") {\n");
        emit_body_scoped(f, Expr_child(e, &(USize){(USize)(1)}), depth + 1);
        emit_indent(f, depth);
        if (e->children.count > 2) {
            EMIT(f, "} else {\n");
            emit_body_scoped(f, Expr_child(e, &(USize){(USize)(2)}), depth + 1);
            emit_indent(f, depth);
        }
        EMIT(f, "}\n");
        break;
    case NodeType_TAG_While:
        EMIT(f, "while (");
        emit_deref(f, Expr_child(e, &(USize){(USize)(0)}), depth);
        EMIT(f, ") {\n");
        emit_body_scoped(f, Expr_child(e, &(USize){(USize)(1)}), depth + 1);
        emit_indent(f, depth);
        EMIT(f, "}\n");
        break;
    case NodeType_TAG_Break:
        EMIT(f, "break;\n");
        break;
    case NodeType_TAG_Continue:
        EMIT(f, "continue;\n");
        break;
    default:
        EMIT(f, "/* TODO: stmt type "); emit_i32(f, e->data.tag); EMIT(f, " */\n");
        break;
    }
}

static void emit_body(File *f, Expr *body, I32 depth) {
    for (U32 i = 0; i < body->children.count; i++) {
        emit_stmt(f, Expr_child(body, &(USize){(USize)(i)}), depth);
    }
}

// --- Top-level emission ---

// Emit namespace field initializations for all structs in the program
static void emit_ns_inits(File *f, I32 depth) {
    { Expr *_progs_ni[2] = { codegen_core_program, codegen_program };
    for (int _pni = 0; _pni < 2; _pni++) {
        if (!_progs_ni[_pni]) continue;
        for (U32 i = 0; i < _progs_ni[_pni]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_ni[_pni], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                            Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Str *sname = &stmt->data.data.Decl.name;
                Expr *edef = Expr_child(stmt, &(USize){(USize)(0)});
                Expr *body = Expr_child(edef, &(USize){(USize)(0)});
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (!field->data.data.Decl.is_namespace) continue;
                    if (Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) continue;
                    // Skip enum variant literals — handled by constructor functions
                    if (edef->data.tag == NodeType_TAG_EnumDef) continue;
                    emit_indent(f, depth);
                    EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, " = ");
                    emit_deref(f, Expr_child(field, &(USize){(USize)(0)}), depth);
                    EMIT(f, ";\n");
                }
            }
        }
    }}
}

static void emit_func_def(File *f, Str *name, Expr *func_def, Mode *mode, Bool is_static) {
    (void)func_def->data.data.FuncDef.func_type;
    Expr *body = Expr_child(func_def, &(USize){(USize)(0)});

    // In needs_main mode, main proc becomes C main()
    Bool is_main = mode && mode->needs_main && (name->count == 4 && memcmp(name->c_str, "main", 4) == 0);

    if (is_main) {
        U32 nparam = func_def->data.data.FuncDef.nparam;
        I32 vi = func_def->data.data.FuncDef.variadic_index;
        if (nparam == 0) {
            EMIT(f, "int main(int argc, char **argv) {\n");
            EMIT(f, "    (void)argv;\n");
            EMIT(f, "    if (argc > 1) { fprintf(stderr, \"error: main expects no arguments, got %d\\n\", argc - 1); return 1; }\n");
        } else {
            EMIT(f, "int main(int argc, char **argv) {\n");
            I32 fixed = (vi >= 0) ? nparam - 1 : nparam;
            if (vi >= 0) {
                EMIT(f, "    if (argc - 1 < "); emit_i32(f, fixed); EMIT(f, ") { fprintf(stderr, \"error: main expects at least "); emit_i32(f, fixed); EMIT(f, " argument(s), got %d\\n\", argc - 1); return 1; }\n");
            } else {
                EMIT(f, "    if (argc - 1 != "); emit_i32(f, nparam); EMIT(f, ") { fprintf(stderr, \"error: main expects "); emit_i32(f, nparam); EMIT(f, " argument(s), got %d\\n\", argc - 1); return 1; }\n");
            }
        }
        // Initialize namespace fields and root-scope globals BEFORE CLI arg
        // parsing, because Str_delete (called during variadic arg cleanup) needs
        // CAP_VIEW to be initialized.
        emit_ns_inits(f, 1);
        if (has_script_globals) {
            { Expr *_progs_sm[2] = { codegen_core_program, codegen_program };
            for (int _psm = 0; _psm < 2; _psm++) {
                if (!_progs_sm[_psm]) continue;
                for (U32 i = 0; i < _progs_sm[_psm]->children.count; i++) {
                    Expr *gs = Expr_child(_progs_sm[_psm], &(USize){(USize)(i)});
                    if (gs->data.tag == NodeType_TAG_Decl) {
                        Expr *rhs = Expr_child(gs, &(USize){(USize)(0)});
                        if (rhs->data.tag == NodeType_TAG_FuncDef || rhs->data.tag == NodeType_TAG_StructDef ||
                            rhs->data.tag == NodeType_TAG_EnumDef) continue;
                        if (gs->til_type.tag == TilType_TAG_None && rhs->data.tag == NodeType_TAG_Ident) continue;
                    } else if (gs->data.tag != NodeType_TAG_FCall) {
                        continue;
                    }
                    emit_stmt(f, gs, 1);
                }
            }}
        }
        if (nparam > 0) {
            // Parse and bind each param
            I32 argi = 1; // argv[0] is program name, skip it
            for (U32 i = 0; i < nparam; i++) {
                Param *_bpi = (Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)});
                Str *pname = &_bpi->name;
                Str *ptype = &_bpi->ptype;
                if ((I32)i == vi) {
                    // Build Array[T] from remaining args
                    const char *et = (const char *)ptype->c_str;
                    EMIT(f, "    int _va_argc = argc - "); emit_i32(f, argi); EMIT(f, ";\n");
                    EMIT(f, "    USize _va_esz = sizeof("); EMIT(f, (const char *)et); EMIT(f, ");\n");
                    EMIT(f, "    USize _va_cap = _va_argc;\n");
                    EMIT(f, "    Array *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = Array_new(&(Str){.c_str = (U8 *)\""); EMIT(f, (const char *)et); EMIT(f, "\", .count = "); emit_u64(f, ptype->count); EMIT(f, "ULL, .cap = TIL_CAP_LIT}, &(USize){_va_esz}, &(USize){_va_cap});\n");
                    EMIT(f, "    for (int _i = 0; _i < _va_argc; _i++) {\n");
                    EMIT(f, "        USize _idx = _i;\n");
                    if ((ptype->count == 3 && memcmp(ptype->c_str, "Str", 3) == 0)) {
                        EMIT(f, "        Str *_val = Str_clone(&(Str){.c_str = (U8 *)argv["); emit_i32(f, argi); EMIT(f, " + _i], .count = strlen(argv["); emit_i32(f, argi); EMIT(f, " + _i]), .cap = TIL_CAP_LIT});\n");
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0)) {
                        EMIT(f, "        I64 *_val = cli_parse_i64(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 2 && memcmp(ptype->c_str, "U8", 2) == 0)) {
                        EMIT(f, "        U8 *_val = cli_parse_u8(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0)) {
                        EMIT(f, "        I16 *_val = cli_parse_i16(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0)) {
                        EMIT(f, "        I32 *_val = cli_parse_i32(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0)) {
                        EMIT(f, "        U32 *_val = cli_parse_u32(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0)) {
                        EMIT(f, "        U64 *_val = cli_parse_u64(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 5 && memcmp(ptype->c_str, "USize", 5) == 0)) {
                        EMIT(f, "        USize *_val = (USize *)cli_parse_u64(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    else if ((ptype->count == 4 && memcmp(ptype->c_str, "Bool", 4) == 0)) {
                        EMIT(f, "        Bool *_val = cli_parse_bool(argv["); emit_i32(f, argi); EMIT(f, " + _i]);\n");
                    }
                    EMIT(f, "        Array_set("); EMIT(f, (const char *)pname->c_str); EMIT(f, ", &(USize){_idx}, _val);\n");
                    EMIT(f, "    }\n");
                } else if ((ptype->count == 3 && memcmp(ptype->c_str, "Str", 3) == 0)) {
                    EMIT(f, "    Str *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = Str_clone(&(Str){.c_str = (U8 *)argv["); emit_i32(f, argi); EMIT(f, "], .count = strlen(argv["); emit_i32(f, argi); EMIT(f, "]), .cap = TIL_CAP_LIT});\n");
                    argi++;
                } else if ((ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0)) {
                    EMIT(f, "    I64 *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_i64(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 2 && memcmp(ptype->c_str, "U8", 2) == 0)) {
                    EMIT(f, "    U8 *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_u8(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0)) {
                    EMIT(f, "    I16 *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_i16(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0)) {
                    EMIT(f, "    I32 *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_i32(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0)) {
                    EMIT(f, "    U32 *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_u32(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0)) {
                    EMIT(f, "    U64 *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_u64(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 5 && memcmp(ptype->c_str, "USize", 5) == 0)) {
                    EMIT(f, "    USize *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = (USize *)cli_parse_u64(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else if ((ptype->count == 4 && memcmp(ptype->c_str, "Bool", 4) == 0)) {
                    EMIT(f, "    Bool *"); EMIT(f, (const char *)pname->c_str); EMIT(f, " = cli_parse_bool(argv["); emit_i32(f, argi); EMIT(f, "]);\n");
                    argi++;
                } else {
                    EMIT(f, "    // unsupported CLI arg type: "); EMIT(f, (const char *)ptype->c_str); EMIT(f, "\n");
                    EMIT(f, "    fprintf(stderr, \"error: unsupported CLI argument type '"); EMIT(f, (const char *)ptype->c_str); EMIT(f, "'\\n\"); return 1;\n");
                    argi++;
                }
            }
        }
        {
            Set saved_stack = stack_locals;
            Map saved_stack_types = stack_local_types;
            Set saved_unsafe = unsafe_to_hoist;
            Set saved_refs = ref_locals;
            { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); stack_locals = *_sp; free(_sp); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); stack_local_types = *_mp; free(_mp); }
            { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); unsafe_to_hoist = *_sp; free(_sp); }
            { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); ref_locals = *_sp; free(_sp); }
            collect_unsafe_to_hoist(body);
            in_main_func = 1;
            emit_body(f, body, 1);
            in_main_func = 0;
            Set_delete(&stack_locals, &(Bool){0});
            Map_delete(&stack_local_types, &(Bool){0});
            Set_delete(&unsafe_to_hoist, &(Bool){0});
            Set_delete(&ref_locals, &(Bool){0});
            stack_locals = saved_stack;
            stack_local_types = saved_stack_types;
            unsafe_to_hoist = saved_unsafe;
            ref_locals = saved_refs;
        }
        EMIT(f, "    return 0;\n");
        EMIT(f, "}\n");
    } else {
        // Return type
        Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
        if (func_def->data.data.FuncDef.return_type.count > 0) {
            ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                : type_name_to_c(&func_def->data.data.FuncDef.return_type);
        }
        // Signature
        EMIT(f, is_static ? "static __attribute__((unused)) " : ""); File_write_str(f, ret); EMIT(f, " "); { Str *_fc = func_to_c(name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
        emit_param_list(f, func_def, 1);
        EMIT(f, ") {\n");
        for (U32 i = 0; i < func_def->data.data.FuncDef.nparam; i++) {
            EMIT(f, "    (void)"); EMIT(f, (const char *)((Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)}))->name.c_str); EMIT(f, ";\n");
        }
        // NULL guard for struct delete methods (self may be NULL)
        if (name->count > 7 && memcmp(name->c_str + name->count - 7, "_delete", 7) == 0 &&
            func_def->data.data.FuncDef.nparam >= 1 &&
            ((Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){0}))->name.count == 4 &&
            memcmp(((Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){0}))->name.c_str, "self", 4) == 0)
            EMIT(f, "    if (!self) return;\n");
        in_func_def = 1;
        current_fdef = func_def;
        // Save/restore stack_locals, ref_locals, and unsafe_to_hoist per function
        Set saved_stack = stack_locals;
        Map saved_stack_types = stack_local_types;
        Set saved_unsafe = unsafe_to_hoist;
        Set saved_refs = ref_locals;
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); stack_locals = *_sp; free(_sp); }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); stack_local_types = *_mp; free(_mp); }
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); unsafe_to_hoist = *_sp; free(_sp); }
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); ref_locals = *_sp; free(_sp); }
        collect_unsafe_to_hoist(body);
        emit_body(f, body, 1);
        Set_delete(&stack_locals, &(Bool){0});
        Map_delete(&stack_local_types, &(Bool){0});
        Set_delete(&unsafe_to_hoist, &(Bool){0});
        Set_delete(&ref_locals, &(Bool){0});
        stack_locals = saved_stack;
        stack_local_types = saved_stack_types;
        unsafe_to_hoist = saved_unsafe;
        ref_locals = saved_refs;
        current_fdef = NULL;
        in_func_def = 0;
        EMIT(f, "}\n");
    }
}

// Types already defined by ext.h/aliases.h — skip emitting typedefs/forward-decls
// is_ext_h_type: moved to builder.til

// ext_func/ext_proc names that conflict with libc or builder-emitted statics
// is_skip_ext_decl: moved to builder.til

// Scalar types whose methods should be emitted as static in core.c
// (avoids duplicate symbol conflicts with ext.c)
// is_scalar_method_type: moved to builder.til


static void emit_struct_typedef(File *f, Str *name, Expr *struct_def) {
    Expr *body = Expr_child(struct_def, &(USize){(USize)(0)});
    if (is_ext_h_type(name)) return; // defined by ext.h/aliases.h
    Bool has_instance_fields = 0;
    for (U32 i = 0; i < body->children.count; i++)
        if (!Expr_child(body, &(USize){(USize)(i)})->data.data.Decl.is_namespace) { has_instance_fields = 1; break; }
    EMIT(f, "typedef struct "); EMIT(f, (const char *)name->c_str); EMIT(f, " {\n");
    if (!has_instance_fields) {
        EMIT(f, "    char _;\n"); // padding for empty structs
    }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = Expr_child(body, &(USize){(USize)(i)});
        if (field->data.data.Decl.is_namespace) continue;
        if (!DECL_IS_SHALLOW(field->data.data.Decl) && (field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) && (Expr_child(field, &(USize){(USize)(0)})->struct_name.count > 0)) {
            EMIT(f, "    "); EMIT(f, (const char *)Expr_child(field, &(USize){(USize)(0)})->struct_name.c_str); EMIT(f, " *"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, ";\n");
        } else if (!DECL_IS_SHALLOW(field->data.data.Decl)) {
            EMIT(f, "    "); { Str *_tc = til_type_to_c(field->til_type); File_write_str(f, _tc); Str_delete(_tc, &(Bool){1}); } EMIT(f, " *"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, ";\n");
        } else if ((field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) && (Expr_child(field, &(USize){(USize)(0)})->struct_name.count > 0)) {
            EMIT(f, "    "); EMIT(f, (const char *)Expr_child(field, &(USize){(USize)(0)})->struct_name.c_str); EMIT(f, " "); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, ";\n");
        } else {
            EMIT(f, "    "); { Str *_tc = til_type_to_c(field->til_type); File_write_str(f, _tc); Str_delete(_tc, &(Bool){1}); } EMIT(f, " "); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, ";\n");
        }
    }
    EMIT(f, "} "); EMIT(f, (const char *)name->c_str); EMIT(f, ";\n\n");
    // Emit namespace fields as globals (skip func defs -- emitted separately)
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = Expr_child(body, &(USize){(USize)(i)});
        if (!field->data.data.Decl.is_namespace) continue;
        if (Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) continue;
        if ((field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) && (Expr_child(field, &(USize){(USize)(0)})->struct_name.count > 0)) {
            EMIT(f, (const char *)Expr_child(field, &(USize){(USize)(0)})->struct_name.c_str); EMIT(f, " "); EMIT(f, (const char *)name->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, ";\n");
        } else {
            { Str *_tc = til_type_to_c(field->til_type); File_write_str(f, _tc); Str_delete(_tc, &(Bool){1}); } EMIT(f, " "); EMIT(f, (const char *)name->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, ";\n");
        }
    }
}

static void emit_struct_funcs(File *f, Str *name, Expr *struct_def, Bool is_lib) {
    (void)is_lib;
    Expr *body = Expr_child(struct_def, &(USize){(USize)(0)});
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = Expr_child(body, &(USize){(USize)(i)});
        if (!field->data.data.Decl.is_namespace) continue;
        if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
        Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
        FuncType fft = fdef->data.data.FuncDef.func_type;
        if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
        // Emit size() as sizeof — the initer's computed sum doesn't account for
        // C alignment padding or union semantics in tagged enums
        if ((field->data.data.Decl.name.count == 4 && memcmp(field->data.data.Decl.name.c_str, "size", 4) == 0) &&
            fdef->data.data.FuncDef.nparam == 0 &&
            (fdef->data.data.FuncDef.return_type).count > 0 &&
            ((fdef->data.data.FuncDef.return_type.count == 5 && memcmp(fdef->data.data.FuncDef.return_type.c_str, "USize", 5) == 0) ||
             (fdef->data.data.FuncDef.return_type.count == 3 && memcmp(fdef->data.data.FuncDef.return_type.c_str, "U32", 3) == 0) ||
             (fdef->data.data.FuncDef.return_type.count == 3 && memcmp(fdef->data.data.FuncDef.return_type.c_str, "U64", 3) == 0))) {
            Str *ret_ctype = type_name_to_c_value(&fdef->data.data.FuncDef.return_type);
            if (RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)) {
                File_write_str(f, ret_ctype); EMIT(f, " "); EMIT(f, (const char *)name->c_str); EMIT(f, "_size(void) {\n");
                EMIT(f, "    return ("); File_write_str(f, ret_ctype); EMIT(f, ")sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, ");\n");
            } else {
                File_write_str(f, ret_ctype); EMIT(f, " *"); EMIT(f, (const char *)name->c_str); EMIT(f, "_size(void) {\n");
                EMIT(f, "    "); File_write_str(f, ret_ctype); EMIT(f, " *r = malloc(sizeof("); File_write_str(f, ret_ctype); EMIT(f, "));\n");
                EMIT(f, "    *r = ("); File_write_str(f, ret_ctype); EMIT(f, ")sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, ");\n");
                EMIT(f, "    return r;\n");
            }
            EMIT(f, "}\n\n");
            continue;
        }
        Bool make_static = 0;
        char full_name_buf[256];
        snprintf(full_name_buf, sizeof(full_name_buf), "%s_%s", name->c_str, field->data.data.Decl.name.c_str);
        Str *full_name = Str_clone(&(Str){.c_str = (U8*)(full_name_buf), .count = (U64)strlen((const char*)(full_name_buf)), .cap = CAP_VIEW});
        emit_func_def(f, full_name, fdef, NULL, make_static);
        Str_delete(full_name, &(Bool){1});
        EMIT(f, "\n");
    }
}

static void emit_enum_def(File *f, Str *name, Expr *enum_def) {
    Expr *body = Expr_child(enum_def, &(USize){(USize)(0)});
    Bool hp = enum_has_payloads(enum_def);

    if (!hp) {
        // === SIMPLE ENUM ===

        // Collect variant names from non-namespace entries
        Vec vnames;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); vnames = *_vp; free(_vp); }
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *v = Expr_child(body, &(USize){(USize)(i)});
            if (v->data.data.Decl.is_namespace) continue;
            { Str **_p = malloc(sizeof(Str *)); *_p = &v->data.data.Decl.name; Vec_push(&vnames, _p); }
        }

        // Zero-arg constructors
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, &(USize){(USize)(i)});
            EMIT(f, (const char *)name->c_str); EMIT(f, " *"); EMIT(f, (const char *)name->c_str); EMIT(f, "_"); EMIT(f, (const char *)vn->c_str); EMIT(f, "() {\n");
            EMIT(f, "    "); EMIT(f, (const char *)name->c_str); EMIT(f, " *r = malloc(sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, "));\n");
            EMIT(f, "    *r = ("); EMIT(f, (const char *)name->c_str); EMIT(f, "){ .tag = "); EMIT(f, (const char *)name->c_str); EMIT(f, "_TAG_"); EMIT(f, (const char *)vn->c_str); EMIT(f, " };\n");
            EMIT(f, "    return r;\n");
            EMIT(f, "}\n");
        }

        Vec_delete(&vnames, &(Bool){0});
    } else {
        // === PAYLOAD ENUM ===

        // Collect variant info from non-namespace entries
        Vec vnames;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); vnames = *_vp; free(_vp); }
        Vec vtypes;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); vtypes = *_vp; free(_vp); }
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *v = Expr_child(body, &(USize){(USize)(i)});
            if (v->data.data.Decl.is_namespace) continue;
            { Str **_p = malloc(sizeof(Str *)); *_p = &v->data.data.Decl.name; Vec_push(&vnames, _p); }
            { Str **_p = malloc(sizeof(Str *)); *_p = &v->data.data.Decl.explicit_type; Vec_push(&vtypes, _p); }
        }

        // Constructor functions for all variants
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, &(USize){(USize)(i)});
            Str *vt = *(Str **)Vec_get(&vtypes, &(USize){(USize)(i)});
            if (vt->count == 0) {
                // Zero-arg constructor for no-payload variant
                EMIT(f, (const char *)name->c_str); EMIT(f, " *"); EMIT(f, (const char *)name->c_str); EMIT(f, "_"); EMIT(f, (const char *)vn->c_str); EMIT(f, "() {\n");
                EMIT(f, "    "); EMIT(f, (const char *)name->c_str); EMIT(f, " *r = malloc(sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, "));\n");
                EMIT(f, "    r->tag = "); EMIT(f, (const char *)name->c_str); EMIT(f, "_TAG_"); EMIT(f, (const char *)vn->c_str); EMIT(f, ";\n");
                EMIT(f, "    return r;\n");
                EMIT(f, "}\n");
                continue;
            }
            Str *ptype = type_name_to_c(vt);
            EMIT(f, (const char *)name->c_str); EMIT(f, " *"); EMIT(f, (const char *)name->c_str); EMIT(f, "_"); EMIT(f, (const char *)vn->c_str); EMIT(f, "("); File_write_str(f, ptype); EMIT(f, " val) {\n");
            EMIT(f, "    "); EMIT(f, (const char *)name->c_str); EMIT(f, " *r = malloc(sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, "));\n");
            EMIT(f, "    r->tag = "); EMIT(f, (const char *)name->c_str); EMIT(f, "_TAG_"); EMIT(f, (const char *)vn->c_str); EMIT(f, ";\n");
            // Store payload inline (by value)
            if (is_primitive_type(vt)) {
                EMIT(f, "    r->data."); EMIT(f, (const char *)vn->c_str); EMIT(f, " = *val;\n");
            } else if (is_funcsig_type(vt) ||
                       (vt->count == 7 && memcmp(vt->c_str, "Dynamic", 7) == 0)) {
                // FuncSig/Dynamic: store pointer directly
                EMIT(f, "    r->data."); EMIT(f, (const char *)vn->c_str); EMIT(f, " = val;\n");
            } else {
                // Struct/enum: clone into inline storage
                EMIT(f, "    { "); { Str *_tnc = type_name_to_c(vt); File_write_str(f, _tnc); Str_delete(_tnc, &(Bool){1}); } EMIT(f, " _tmp = "); EMIT(f, (const char *)vt->c_str); EMIT(f, "_clone(val); r->data."); EMIT(f, (const char *)vn->c_str); EMIT(f, " = *_tmp; free(_tmp); }\n");
            }
            EMIT(f, "    return r;\n");
            EMIT(f, "}\n");
        }

        Vec_delete(&vnames, &(Bool){0});
        Vec_delete(&vtypes, &(Bool){0});
    }

    // Emit namespace func/proc methods (to_str, user methods)
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = Expr_child(body, &(USize){(USize)(i)});
        if (!field->data.data.Decl.is_namespace) continue;
        if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
        Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
        FuncType fft = fdef->data.data.FuncDef.func_type;
        if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
        // Emit size() as sizeof (same as struct_funcs)
        if ((field->data.data.Decl.name.count == 4 && memcmp(field->data.data.Decl.name.c_str, "size", 4) == 0) &&
            fdef->data.data.FuncDef.nparam == 0 &&
            (fdef->data.data.FuncDef.return_type).count > 0 &&
            ((fdef->data.data.FuncDef.return_type.count == 5 && memcmp(fdef->data.data.FuncDef.return_type.c_str, "USize", 5) == 0) ||
             (fdef->data.data.FuncDef.return_type.count == 3 && memcmp(fdef->data.data.FuncDef.return_type.c_str, "U32", 3) == 0) ||
             (fdef->data.data.FuncDef.return_type.count == 3 && memcmp(fdef->data.data.FuncDef.return_type.c_str, "U64", 3) == 0))) {
            Str *ret_ctype = type_name_to_c_value(&fdef->data.data.FuncDef.return_type);
            if (RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)) {
                File_write_str(f, ret_ctype); EMIT(f, " "); EMIT(f, (const char *)name->c_str); EMIT(f, "_size(void) {\n");
                EMIT(f, "    return ("); File_write_str(f, ret_ctype); EMIT(f, ")sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, ");\n");
            } else {
                File_write_str(f, ret_ctype); EMIT(f, " *"); EMIT(f, (const char *)name->c_str); EMIT(f, "_size(void) {\n");
                EMIT(f, "    "); File_write_str(f, ret_ctype); EMIT(f, " *r = malloc(sizeof("); File_write_str(f, ret_ctype); EMIT(f, "));\n");
                EMIT(f, "    *r = ("); File_write_str(f, ret_ctype); EMIT(f, ")sizeof("); EMIT(f, (const char *)name->c_str); EMIT(f, ");\n");
                EMIT(f, "    return r;\n");
            }
            EMIT(f, "}\n\n");
            continue;
        }
        char full_name_buf[256];
        snprintf(full_name_buf, sizeof(full_name_buf), "%s_%s", name->c_str, field->data.data.Decl.name.c_str);
        Str *full_name = Str_clone(&(Str){.c_str = (U8*)(full_name_buf), .count = (U64)strlen((const char*)(full_name_buf)), .cap = CAP_VIEW});
        emit_func_def(f, full_name, fdef, NULL, 0);
        Str_delete(full_name, &(Bool){1});
        EMIT(f, "\n");
    }
}

I32 build_forward_header(Expr *core_program, Expr *program, Str *fwd_path);
static void emit_header_forward_decls(File *f, Expr *core_program, Expr *program);
static void emit_header_global_decls(File *f, Expr *core_program, Expr *program);
// is_exported_top_level_global: moved to builder.til

// Derive basename from absolute path: "/abs/path/to/str.til" -> "str"
I32 build(Expr *core_program, Expr *program, Mode *mode, Bool run_tests, Str *path, Str *c_output_path) {
    codegen_core_program = core_program;
    codegen_program = program;
    (void)path;
    Bool is_lib = mode && mode->is_library;

    // Build struct body lookup map
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); struct_bodies = *_mp; free(_mp); }
    // Build func_def lookup map (for shallow param lookup at call sites)
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); func_defs = *_mp; free(_mp); }
    // Initialize stack_locals, ref_locals, and unsafe_to_hoist sets
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); stack_locals = *_sp; free(_sp); }
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); stack_local_types = *_mp; free(_mp); }
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); unsafe_to_hoist = *_sp; free(_sp); }
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); ref_locals = *_sp; free(_sp); }
    { Expr *_progs_reg[2] = { core_program, program };
    for (int _preg = 0; _preg < 2; _preg++) {
        if (!_progs_reg[_preg]) continue;
        for (U32 i = 0; i < _progs_reg[_preg]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_reg[_preg], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                                         Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Str *sname = &stmt->data.data.Decl.name;
                Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
                { Str *_k = malloc(sizeof(Str)); *_k = (Str){sname->c_str, sname->count, CAP_VIEW}; void *_v = malloc(sizeof(body)); memcpy(_v, &body, sizeof(body)); Map_set(&struct_bodies, _k, _v); }
                // Register namespace methods
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (!field->data.data.Decl.is_namespace) continue;
                    if (field->children.count == 0 || Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                    Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                    char flat[256];
                    snprintf(flat, sizeof(flat), "%s_%s", sname->c_str, field->data.data.Decl.name.c_str);
                    Str *key = Str_clone(&(Str){.c_str = (U8*)(flat), .count = (U64)strlen((const char*)(flat)), .cap = CAP_VIEW});
                    { Str *_k = malloc(sizeof(Str)); *_k = (Str){key->c_str, key->count, CAP_VIEW}; void *_v = malloc(sizeof(fdef)); memcpy(_v, &fdef, sizeof(fdef)); Map_set(&func_defs, _k, _v); }
                    // Also register nested ext_funcs inside this namespace method
                    // (names are already flattened by precomp, e.g. "U8_from_i64_ext")
                    if (fdef->children.count > 0) {
                        Expr *fbody = Expr_child(fdef, &(USize){(USize)(0)});
                        for (U32 k = 0; k < fbody->children.count; k++) {
                            Expr *nested = Expr_child(fbody, &(USize){(USize)(k)});
                            if (nested->data.tag != NodeType_TAG_Decl) continue;
                            if (nested->children.count == 0 || Expr_child(nested, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                            Expr *nfdef = Expr_child(nested, &(USize){(USize)(0)});
                            Str *nkey = Str_clone(&nested->data.data.Decl.name);
                            { Str *_k2 = malloc(sizeof(Str)); *_k2 = (Str){nkey->c_str, nkey->count, CAP_VIEW}; void *_v2 = malloc(sizeof(nfdef)); memcpy(_v2, &nfdef, sizeof(nfdef)); Map_set(&func_defs, _k2, _v2); }
                        }
                    }
                }
            }
            if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                Str *fname = &stmt->data.data.Decl.name;
                Expr *fdef = Expr_child(stmt, &(USize){(USize)(0)});
                { Str *_k = malloc(sizeof(Str)); *_k = (Str){fname->c_str, fname->count, CAP_VIEW}; void *_v = malloc(sizeof(fdef)); memcpy(_v, &fdef, sizeof(fdef)); Map_set(&func_defs, _k, _v); }
            }
        }
    }}
    // Collect FuncSig names (bodyless func/proc definitions)
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); funcsig_names = *_sp; free(_sp); }
    has_funcsig_names = 1;
    { Expr *_progs_fs[2] = { core_program, program };
    for (int _pfs = 0; _pfs < 2; _pfs++) {
        if (!_progs_fs[_pfs]) continue;
        for (U32 i = 0; i < _progs_fs[_pfs]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_fs[_pfs], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef &&
                Expr_child(stmt, &(USize){(USize)(0)})->children.count == 0) {
                Str *n = &stmt->data.data.Decl.name;
                { Str *_p = malloc(sizeof(Str)); *_p = (Str){n->c_str, n->count, CAP_VIEW}; Set_add(&funcsig_names, _p); }
            }
            // FuncSig type aliases: Callback := BinaryOp (Decl where RHS is Ident, til_type=None,
            // and RHS refers to a FuncSig)
            if (stmt->data.tag == NodeType_TAG_Decl && stmt->til_type.tag == TilType_TAG_None &&
                Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_Ident) {
                Str *rhs_name = &Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident;
                if (Set_has(&funcsig_names, rhs_name)) {
                    Str *n = &stmt->data.data.Decl.name;
                    { Str *_p = malloc(sizeof(Str)); *_p = (Str){n->c_str, n->count, CAP_VIEW}; Set_add(&funcsig_names, _p); }
                }
            }
        }
    }}
    File *f = File_new(c_output_path, 1);
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", (const char *)c_output_path->c_str);
        return 1;
    }

    EMIT(f, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdarg.h>\n#include <limits.h>\n\n");

    Bool is_script = !mode || !mode->decls_only;

    // === Monolithic .h emission (#89: reverted per-module splitting from #74) ===
    // Single .h file with forward decls, struct/enum defs, and function declarations.
    {
        File *hf = f;  // emit directly into main .c
        EMIT(hf, "#include \"ext.h\"\n\n");
        emit_header_forward_decls(hf, core_program, program);

        // Topo-sort struct/enum defs into header
        {
            // Collect indices from both programs, storing (prog_idx << 24 | child_idx) pairs
            Vec to_emit_mh; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(U32)}); to_emit_mh = *_vp; free(_vp); }
            Expr *_progs_ts[2] = { core_program, program };
            Vec _prog_refs_mh; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); _prog_refs_mh = *_vp; free(_vp); }
            for (int _pts = 0; _pts < 2; _pts++) {
                if (!_progs_ts[_pts]) continue;
                for (U32 i = 0; i < _progs_ts[_pts]->children.count; i++) {
                    Expr *stmt = Expr_child(_progs_ts[_pts], &(USize){(USize)(i)});
                    if (stmt->data.tag == NodeType_TAG_Decl &&
                        (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                         Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                        U32 idx = to_emit_mh.count;
                        { U32 *_p = malloc(sizeof(U32)); *_p = idx; Vec_push(&to_emit_mh, _p); }
                        { Expr **_p = malloc(sizeof(Expr *)); *_p = stmt; Vec_push(&_prog_refs_mh, _p); }
                    }
                }
            }
            Set emitted_mh; { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); emitted_mh = *_sp; free(_sp); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U8", .count = 2, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I16", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"F32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }

            U32 remaining_mh = _prog_refs_mh.count;
            Bool *done_mh = calloc(_prog_refs_mh.count, sizeof(Bool));
            while (remaining_mh > 0) {
                Bool progress_mh = 0;
                for (U32 ei = 0; ei < _prog_refs_mh.count; ei++) {
                    if (done_mh[ei]) continue;
                    Expr *stmt = *(Expr **)Vec_get(&_prog_refs_mh, &(USize){(USize)(ei)});
                    Str *name = &stmt->data.data.Decl.name;
                    Expr *def = Expr_child(stmt, &(USize){(USize)(0)});

                    Bool deps_ok = 1;
                    if (def->data.tag == NodeType_TAG_StructDef) {
                        Expr *body = Expr_child(def, &(USize){(USize)(0)});
                        for (U32 fi = 0; fi < body->children.count; fi++) {
                            Expr *field = Expr_child(body, &(USize){(USize)(fi)});
                            if (field->data.data.Decl.is_namespace) continue;
                            if (DECL_IS_SHALLOW(field->data.data.Decl) &&
                                (field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) &&
                                (Expr_child(field, &(USize){(USize)(0)})->struct_name.count > 0)) {
                                if (!Set_has(&emitted_mh, &Expr_child(field, &(USize){(USize)(0)})->struct_name)) {
                                    deps_ok = 0;
                                    break;
                                }
                            }
                        }
                    } else if (def->data.tag == NodeType_TAG_EnumDef) {
                        Expr *body = Expr_child(def, &(USize){(USize)(0)});
                        for (U32 fi = 0; fi < body->children.count; fi++) {
                            Expr *v = Expr_child(body, &(USize){(USize)(fi)});
                            if (v->data.data.Decl.is_namespace) continue;
                            if ((v->data.data.Decl.explicit_type).count > 0 &&
                                !is_primitive_type(&v->data.data.Decl.explicit_type) &&
                                !is_funcsig_type(&v->data.data.Decl.explicit_type)) {
                                if (!Set_has(&emitted_mh, &v->data.data.Decl.explicit_type)) {
                                    deps_ok = 0;
                                    break;
                                }
                            }
                        }
                    }

                    if (!deps_ok) continue;

                    if (def->data.tag == NodeType_TAG_StructDef) {
                        emit_struct_typedef(hf, name, def);
                        EMIT(hf, "\n");
                    } else {
                        Str *ename = name;
                        Expr *ebody = Expr_child(def, &(USize){(USize)(0)});
                        Bool hp = enum_has_payloads(def);
                        EMIT(hf, "struct "); EMIT(hf, (const char *)ename->c_str); EMIT(hf, " {\n");
                        EMIT(hf, "    "); EMIT(hf, (const char *)ename->c_str); EMIT(hf, "_tag tag;\n");
                        if (hp) {
                            EMIT(hf, "    union {\n");
                            for (U32 j = 0; j < ebody->children.count; j++) {
                                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                                if (v->data.data.Decl.is_namespace) continue;
                                if (v->data.data.Decl.explicit_type.count > 0) {
                                    EMIT(hf, "        "); { Str *_tnv = type_name_to_c_value(&v->data.data.Decl.explicit_type); File_write_str(hf, _tnv); Str_delete(_tnv, &(Bool){1}); }; EMIT(hf, " "); EMIT(hf, (const char *)v->data.data.Decl.name.c_str); EMIT(hf, ";\n");
                                }
                            }
                            EMIT(hf, "    } data;\n");
                        }
                        EMIT(hf, "};\n\n");
                    }
                    { Str *_p = Str_clone(name); Set_add(&emitted_mh, _p); }
                    done_mh[ei] = 1;
                    remaining_mh--;
                    progress_mh = 1;
                }
                if (!progress_mh) {
                    for (U32 ei = 0; ei < _prog_refs_mh.count; ei++) {
                        if (done_mh[ei]) continue;
                        Expr *stmt = *(Expr **)Vec_get(&_prog_refs_mh, &(USize){(USize)(ei)});
                        Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
                        if (def->data.tag == NodeType_TAG_StructDef) {
                            emit_struct_typedef(hf, &stmt->data.data.Decl.name, def);
                            EMIT(hf, "\n");
                        } else {
                            Str *ename = &stmt->data.data.Decl.name;
                            Expr *ebody = Expr_child(def, &(USize){(USize)(0)});
                            Bool hp = enum_has_payloads(def);
                            EMIT(hf, "struct "); EMIT(hf, (const char *)ename->c_str); EMIT(hf, " {\n");
                            EMIT(hf, "    "); EMIT(hf, (const char *)ename->c_str); EMIT(hf, "_tag tag;\n");
                            if (hp) {
                                EMIT(hf, "    union {\n");
                                for (U32 j = 0; j < ebody->children.count; j++) {
                                    Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                                    if (v->data.data.Decl.is_namespace) continue;
                                    if (v->data.data.Decl.explicit_type.count > 0) {
                                        EMIT(hf, "        "); { Str *_tnv = type_name_to_c_value(&v->data.data.Decl.explicit_type); File_write_str(hf, _tnv); Str_delete(_tnv, &(Bool){1}); }; EMIT(hf, " "); EMIT(hf, (const char *)v->data.data.Decl.name.c_str); EMIT(hf, ";\n");
                                    }
                                }
                                EMIT(hf, "    } data;\n");
                            }
                            EMIT(hf, "};\n\n");
                        }
                    }
                    break;
                }
            }
            free(done_mh);
            Vec_delete(&to_emit_mh, &(Bool){0});
            Vec_delete(&_prog_refs_mh, &(Bool){0});
            Set_delete(&emitted_mh, &(Bool){0});
        }

        // Emit function declarations to header
        { Expr *_progs_hd[2] = { core_program, program };
        for (int _phd = 0; _phd < 2; _phd++) {
            if (!_progs_hd[_phd]) continue;
        for (U32 i = 0; i < _progs_hd[_phd]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_hd[_phd], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Str *sname = &stmt->data.data.Decl.name;
                if (is_scalar_method_type(sname)) continue;
                Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (!field->data.data.Decl.is_namespace) continue;
                    if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                    Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                    FuncType fft = fdef->data.data.FuncDef.func_type;
                    if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                    Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
                    if (fdef->data.data.FuncDef.return_type.count > 0)
                        ret = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                            ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                            : type_name_to_c(&fdef->data.data.FuncDef.return_type);
                    File_write_str(hf, ret); EMIT(hf, " "); EMIT(hf, (const char *)sname->c_str); EMIT(hf, "_"); EMIT(hf, (const char *)field->data.data.Decl.name.c_str); EMIT(hf, "(");
                    emit_param_list(hf, fdef, 1);
                    EMIT(hf, ");\n");
                }
            } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                Expr *func_def = Expr_child(stmt, &(USize){(USize)(0)});
                if (func_def->children.count == 0) continue;
                FuncType fft = func_def->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                Str *fname = &stmt->data.data.Decl.name;
                Bool fis_main = mode && mode->needs_main && (fname->count == 4 && memcmp(fname->c_str, "main", 4) == 0);
                if (fis_main) continue;
                Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
                if (func_def->data.data.FuncDef.return_type.count > 0)
                    ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                        ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                        : type_name_to_c(&func_def->data.data.FuncDef.return_type);
                File_write_str(hf, ret); EMIT(hf, " "); { Str *_fc = func_to_c(&stmt->data.data.Decl.name); File_write_str(hf, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(hf, "(");
                emit_param_list(hf, func_def, 1);
                EMIT(hf, ");\n");
            }
        }
        }}
        // Enum auto-helper declarations (user program only)
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
                Str *sname = &stmt->data.data.Decl.name;
                Expr *ebody = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
                Expr *eq_fdef = NULL;
                for (U32 j = 0; j < ebody->children.count; j++) {
                    Expr *field = Expr_child(ebody, &(USize){(USize)(j)});
                    if (field->data.data.Decl.is_namespace && (field->data.data.Decl.name.count == 2 && memcmp(field->data.data.Decl.name.c_str, "eq", 2) == 0) &&
                        Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                        eq_fdef = Expr_child(field, &(USize){(USize)(0)});
                        break;
                    }
                }
                const char *eq_ret = (eq_fdef && RETURN_IS_SHALLOW(&eq_fdef->data.data.FuncDef)) ? "Bool" : "Bool *";
                EMIT(hf, (const char *)eq_ret); EMIT(hf, " "); EMIT(hf, (const char *)sname->c_str); EMIT(hf, "_eq("); EMIT(hf, (const char *)sname->c_str); EMIT(hf, " *, "); EMIT(hf, (const char *)sname->c_str); EMIT(hf, " *);\n");
                for (U32 j = 0; j < ebody->children.count; j++) {
                    Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                    if (v->data.data.Decl.is_namespace) continue;
                    if (v->data.data.Decl.explicit_type.count > 0) {
                        EMIT(hf, (const char *)sname->c_str); EMIT(hf, " *"); EMIT(hf, (const char *)sname->c_str); EMIT(hf, "_"); EMIT(hf, (const char *)v->data.data.Decl.name.c_str); EMIT(hf, "("); { Str *_tnc = type_name_to_c(&v->data.data.Decl.explicit_type); File_write_str(hf, _tnc); Str_delete(_tnc, &(Bool){1}); }; EMIT(hf, ");\n");
                    } else {
                        EMIT(hf, (const char *)sname->c_str); EMIT(hf, " *"); EMIT(hf, (const char *)sname->c_str); EMIT(hf, "_"); EMIT(hf, (const char *)v->data.data.Decl.name.c_str); EMIT(hf, "();\n");
                    }
                }
            }
        }

        // hf == f, no separate file to close
    }
    EMIT(f, "#include \"ext.h\"\n\n");

    // Forward-declare user-defined ext_func/ext_proc (user program only, skip libc conflicts)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != NodeType_TAG_Decl || Expr_child(stmt, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
        Expr *fdef = Expr_child(stmt, &(USize){(USize)(0)});
        FuncType fft = fdef->data.data.FuncDef.func_type;
        if (fft.tag != FuncType_TAG_ExtFunc && fft.tag != FuncType_TAG_ExtProc) continue;
        if (is_skip_ext_decl(&stmt->data.data.Decl.name)) continue;
        if (fdef->data.data.FuncDef.return_type.count > 0) {
            Str *rt = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                : type_name_to_c(&fdef->data.data.FuncDef.return_type);
            File_write_str(f, rt); Str_delete(rt, &(Bool){1}); EMIT(f, " "); { Str *_fc = func_to_c(&stmt->data.data.Decl.name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
        }
        else {
            EMIT(f, "void "); { Str *_fc = func_to_c(&stmt->data.data.Decl.name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
        }
        emit_param_list(f, fdef, 0);
        EMIT(f, ");\n");
    }
    EMIT(f, "\n");

    // Forward-declare helper functions (implementations after struct defs)
    EMIT(f, "Str *Str_lit(const char *s, unsigned long long len);\n");
    EMIT(f, "void print_single(Str *s);\n");
    EMIT(f, "void print_flush();\n\n");

    // Forward-declare all functions (namespace methods + top-level)
    { Expr *_progs_fwd[2] = { core_program, program };
    for (int _pfwd = 0; _pfwd < 2; _pfwd++) {
        if (!_progs_fwd[_pfwd]) continue;
        Bool _is_core_pass = (_pfwd == 0 && core_program != NULL);
        for (U32 i = 0; i < _progs_fwd[_pfwd]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_fwd[_pfwd], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Str *sname = &stmt->data.data.Decl.name;
                Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (!field->data.data.Decl.is_namespace) continue;
                    if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                    Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                    FuncType fft = fdef->data.data.FuncDef.func_type;
                    if ((fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) && _is_core_pass) continue;
                    Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
                    if (fdef->data.data.FuncDef.return_type.count > 0) {
                        ret = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                            ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                            : type_name_to_c(&fdef->data.data.FuncDef.return_type);
                    }
                    File_write_str(f, ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, "(");
                    emit_param_list(f, fdef, 1);
                    EMIT(f, ");\n");
                }
            } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                Expr *func_def = Expr_child(stmt, &(USize){(USize)(0)});
                FuncType fft = func_def->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                Str *name = &stmt->data.data.Decl.name;
                Bool is_main = mode && mode->needs_main && (name->count == 4 && memcmp(name->c_str, "main", 4) == 0);
                if (is_main) continue;
                Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
                if (func_def->data.data.FuncDef.return_type.count > 0)
                    ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                        ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                        : type_name_to_c(&func_def->data.data.FuncDef.return_type);
                File_write_str(f, ret); EMIT(f, " "); { Str *_fc = func_to_c(name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
                emit_param_list(f, func_def, 1);
                EMIT(f, ");\n");
            }
        }
    }}
    // Forward-declare enum ext methods (eq, constructors + payload methods)
    { Expr *_progs_ee[2] = { core_program, program };
    for (int _pee = 0; _pee < 2; _pee++) {
        if (!_progs_ee[_pee]) continue;
    for (U32 i = 0; i < _progs_ee[_pee]->children.count; i++) {
        Expr *stmt = Expr_child(_progs_ee[_pee], &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *ebody = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
            // Find eq fdef to check return_is_shallow
            Expr *eq_fdef = NULL;
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *field = Expr_child(ebody, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace && (field->data.data.Decl.name.count == 2 && memcmp(field->data.data.Decl.name.c_str, "eq", 2) == 0) &&
                    Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                    eq_fdef = Expr_child(field, &(USize){(USize)(0)});
                    break;
                }
            }
            const char *eq_ret = (eq_fdef && RETURN_IS_SHALLOW(&eq_fdef->data.data.FuncDef)) ? "Bool" : "Bool *";
            EMIT(f, (const char *)eq_ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_eq("); EMIT(f, (const char *)sname->c_str); EMIT(f, " *, "); EMIT(f, (const char *)sname->c_str); EMIT(f, " *);\n");
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                if (v->data.data.Decl.is_namespace) continue;
                if (v->data.data.Decl.explicit_type.count > 0) {
                    // Payload constructor
                    EMIT(f, (const char *)sname->c_str); EMIT(f, " *"); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, "("); { Str *_tnc = type_name_to_c(&v->data.data.Decl.explicit_type); File_write_str(f, _tnc); Str_delete(_tnc, &(Bool){1}); }; EMIT(f, ");\n");
                } else {
                    // Zero-arg constructor
                    EMIT(f, (const char *)sname->c_str); EMIT(f, " *"); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, "();\n");
                }
            }
        }
    }
    }}
    EMIT(f, "\n");

    // Forward declarations for dyn_call dispatch functions
    {
        Vec dyn_methods;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"DynCallInfo", .count = 11, .cap = CAP_LIT}, &(USize){sizeof(DynCallInfo)}); dyn_methods = *_vp; free(_vp); }
        if (core_program) collect_dyn_methods(core_program, &dyn_methods);
        collect_dyn_methods(program, &dyn_methods);
        for (U32 m = 0; m < dyn_methods.count; m++) {
            DynCallInfo *info = Vec_get(&dyn_methods, &(USize){(USize)(m)});
            if (info->has_return) {
                if (info->nargs == 1) {
                    EMIT(f, "void *dyn_call_"); EMIT(f, (const char *)info->method->c_str); EMIT(f, "(Str *type_name, void *val);\n");
                }
                else {
                    EMIT(f, "void *dyn_call_"); EMIT(f, (const char *)info->method->c_str); EMIT(f, "(Str *type_name, void *val, void *arg2);\n");
                }
            } else {
                if (info->nargs == 1) {
                    EMIT(f, "void dyn_call_"); EMIT(f, (const char *)info->method->c_str); EMIT(f, "(Str *type_name, void *val);\n");
                }
                else {
                    EMIT(f, "void dyn_call_"); EMIT(f, (const char *)info->method->c_str); EMIT(f, "(Str *type_name, void *val, void *arg2);\n");
                }
            }
        }
        EMIT(f, "void *dyn_fn(Str *type_name, Str *method);\n");
        EMIT(f, "\n");
        Vec_delete(&dyn_methods, &(Bool){0});
    }

    // Forward declarations for dyn_has_method dispatch functions
    {
        // Find dyn_has_method to check return_is_shallow
        Bool dyn_has_shallow = 0;
        { Expr *_progs_dh[2] = { core_program, program };
        for (int _pdh = 0; _pdh < 2 && !dyn_has_shallow; _pdh++) {
            if (!_progs_dh[_pdh]) continue;
            for (U32 i = 0; i < _progs_dh[_pdh]->children.count; i++) {
                Expr *stmt = Expr_child(_progs_dh[_pdh], &(USize){(USize)(i)});
                if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef &&
                    (stmt->data.data.Decl.name.count == 14 && memcmp(stmt->data.data.Decl.name.c_str, "dyn_has_method", 14) == 0)) {
                    dyn_has_shallow = RETURN_IS_SHALLOW(&Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef);
                    break;
                }
            }
        }}
        const char *dyn_has_ret = dyn_has_shallow ? "Bool" : "Bool *";
        Vec has_methods;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); has_methods = *_vp; free(_vp); }
        if (core_program) collect_dyn_has_methods(core_program, &has_methods);
        collect_dyn_has_methods(program, &has_methods);
        for (U32 m = 0; m < has_methods.count; m++) {
            Str **method = Vec_get(&has_methods, &(USize){(USize)(m)});
            EMIT(f, (const char *)dyn_has_ret); EMIT(f, " dyn_has_"); EMIT(f, (const char *)(*method)->c_str); EMIT(f, "(Str *type_name);\n");
        }
        if (has_methods.count) EMIT(f, "\n");
        Vec_delete(&has_methods, &(Bool){0});
    }

    // Forward declarations for array/vec builtin helpers
    {
        Vec coll_infos;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"CollectionInfo", .count = 14, .cap = CAP_LIT}, &(USize){sizeof(CollectionInfo)}); coll_infos = *_vp; free(_vp); }
        if (core_program) collect_collection_builtins(core_program, &coll_infos);
        collect_collection_builtins(program, &coll_infos);
        for (U32 i = 0; i < coll_infos.count; i++) {
            CollectionInfo *ci = Vec_get(&coll_infos, &(USize){(USize)(i)});
            const char *prefix = ci->is_vec ? "vec" : "array";
            const char *ret = ci->is_vec ? "Vec" : "Array";
            EMIT(f, (const char *)ret); EMIT(f, " *"); EMIT(f, (const char *)prefix); EMIT(f, "_of_"); EMIT(f, (const char *)ci->type_name->c_str); EMIT(f, "(int count, ...);\n");
        }
        if (coll_infos.count) EMIT(f, "\n");
        Vec_delete(&coll_infos, &(Bool){0});
    }

    // Struct/enum definitions emitted in monolithic .h file above

    // Runtime NULL check for shallow deref
    EMIT(f, "#define DEREF(p) (*(p ? p : (fprintf(stderr, \"panic: null deref\\n\"), exit(1), p)))\n");

    // String helper functions (after all struct typedefs so Str is complete)
    EMIT(f, "#define TIL_CAP_LIT ((USize)-1)\n");
    EMIT(f, "Str *Str_lit(const char *s, unsigned long long len) {\n");
    EMIT(f, "    (void)len;\n");
    EMIT(f, "    Str *r = malloc(sizeof(Str));\n");
    EMIT(f, "    r->c_str = (U8 *)s;\n");
    EMIT(f, "    r->count = (USize)strlen(s);\n");
    EMIT(f, "    r->cap = TIL_CAP_LIT;\n");
    EMIT(f, "    return r;\n");
    EMIT(f, "}\n");
    EMIT(f, "void print_single(Str *s) {\n");
    EMIT(f, "    fwrite(s->c_str, 1, (size_t)s->count, stdout);\n");
    EMIT(f, "}\n");
    EMIT(f, "void print_flush() {\n");
    EMIT(f, "    putchar('\\n');\n");
    EMIT(f, "}\n\n");

    // Emit top-level variable declarations as file-scope globals
    // so they're accessible from functions/procs defined at the same level
    {
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); script_globals = *_sp; free(_sp); }
        has_script_globals = 1;
        { Expr *_progs_gl[2] = { core_program, program };
        for (int _pgl = 0; _pgl < 2; _pgl++) {
            if (!_progs_gl[_pgl]) continue;
            for (U32 i = 0; i < _progs_gl[_pgl]->children.count; i++) {
                Expr *stmt = Expr_child(_progs_gl[_pgl], &(USize){(USize)(i)});
                if (!is_exported_top_level_global(stmt)) continue;
                Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
                Str *ctype = stmt->til_type.tag == TilType_TAG_Dynamic
                    ? til_type_to_c(stmt->til_type)
                    : c_type_name(stmt->til_type, &rhs->struct_name);
                File_write_str(f, ctype); Str_delete(ctype, &(Bool){1}); EMIT(f, " "); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
                { Str *_p = malloc(sizeof(Str)); *_p = (Str){stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.count, CAP_VIEW}; Set_add(&script_globals, _p); }
            }
        }}
        EMIT(f, "\n");
    }

    // Emit function bodies -- all into main .c (#89: monolithic)
    { Expr *_progs_fb[2] = { core_program, program };
    for (int _pfb = 0; _pfb < 2; _pfb++) {
        if (!_progs_fb[_pfb]) continue;
        for (U32 i = 0; i < _progs_fb[_pfb]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_fb[_pfb], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef) {
                emit_struct_funcs(f, &stmt->data.data.Decl.name, Expr_child(stmt, &(USize){(USize)(0)}), is_lib);
            } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
                emit_enum_def(f, &stmt->data.data.Decl.name, Expr_child(stmt, &(USize){(USize)(0)}));
                EMIT(f, "\n");
            } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                FuncType fft2 = Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
                if (fft2.tag == FuncType_TAG_ExtFunc || fft2.tag == FuncType_TAG_ExtProc) continue;
                if (Expr_child(stmt, &(USize){(USize)(0)})->children.count == 0) continue;
                emit_func_def(f, &stmt->data.data.Decl.name, Expr_child(stmt, &(USize){(USize)(0)}), mode, 0);
                EMIT(f, "\n");
            }
        }
    }}

    // Emit dyn_call dispatch function bodies
    {
        Vec dyn_methods;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"DynCallInfo", .count = 11, .cap = CAP_LIT}, &(USize){sizeof(DynCallInfo)}); dyn_methods = *_vp; free(_vp); }
        if (core_program) collect_dyn_methods(core_program, &dyn_methods);
        collect_dyn_methods(program, &dyn_methods);
        for (U32 m = 0; m < dyn_methods.count; m++) {
            DynCallInfo *info = Vec_get(&dyn_methods, &(USize){(USize)(m)});
            Str *method = info->method;
            const char *ret_type = info->has_return ? "void *" : "void ";
            if (info->nargs == 1) {
                EMIT(f, (const char *)ret_type); EMIT(f, "dyn_call_"); EMIT(f, (const char *)method->c_str); EMIT(f, "(Str *type_name, void *val) {\n");
            }
            else {
                EMIT(f, (const char *)ret_type); EMIT(f, "dyn_call_"); EMIT(f, (const char *)method->c_str); EMIT(f, "(Str *type_name, void *val, void *arg2) {\n");
            }
            // Iterate all struct/type defs in AST
            { Expr *_progs_dc[2] = { core_program, program };
            for (int _pdc = 0; _pdc < 2; _pdc++) {
                if (!_progs_dc[_pdc]) continue;
            for (U32 i = 0; i < _progs_dc[_pdc]->children.count; i++) {
                Expr *stmt = Expr_child(_progs_dc[_pdc], &(USize){(USize)(i)});
                if (stmt->data.tag != NodeType_TAG_Decl) continue;
                Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
                if (def->data.tag != NodeType_TAG_StructDef && def->data.tag != NodeType_TAG_EnumDef) continue;
                Str *tname = &stmt->data.data.Decl.name;
                // Check if this type has the method in its namespace
                Expr *body = Expr_child(def, &(USize){(USize)(0)});
                Expr *method_fdef = NULL;
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (field->data.data.Decl.is_namespace &&
                        Str_eq(&field->data.data.Decl.name, method) &&
                        field->children.count > 0 &&
                        Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                        method_fdef = Expr_child(field, &(USize){(USize)(0)});
                        break;
                    }
                }
                if (!method_fdef) continue;
                // Build arg expressions with shallow dereference where needed
                char arg1[64], arg2_str[64];
                Vec *ps = &method_fdef->data.data.FuncDef.params;
                if (ps->count > 0 && PARAM_IS_SHALLOW(((Param*)Vec_get(ps, &(USize){(USize)(0)}))))
                    snprintf(arg1, sizeof(arg1), "*(%s *)val", tname->c_str);
                else
                    snprintf(arg1, sizeof(arg1), "val");
                if (info->nargs == 2) {
                    if (ps->count > 1 && method_fdef->data.data.FuncDef.nparam > 1 && PARAM_IS_SHALLOW(((Param*)Vec_get(ps, &(USize){(USize)(1)}))))
                        snprintf(arg2_str, sizeof(arg2_str), "*(%s *)arg2", tname->c_str);
                    else
                        snprintf(arg2_str, sizeof(arg2_str), "arg2");
                }
                Bool ret_shallow = RETURN_IS_SHALLOW(&method_fdef->data.data.FuncDef);
                Str *ret_ctype = (info->has_return && ret_shallow && method_fdef->data.data.FuncDef.return_type.count > 0)
                    ? type_name_to_c_value(&method_fdef->data.data.FuncDef.return_type) : NULL;
                if (info->nargs == 2) {
                    if (info->has_return && ret_shallow) {
                        EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) { "); File_write_str(f, ret_ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ret_ctype); EMIT(f, ")); *_r = "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)method->c_str); EMIT(f, "("); EMIT(f, (const char *)arg1); EMIT(f, ", "); EMIT(f, (const char *)arg2_str); EMIT(f, "); return _r; }\n");
                    }
                    else if (info->has_return) {
                        EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) return (void *)"); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)method->c_str); EMIT(f, "("); EMIT(f, (const char *)arg1); EMIT(f, ", "); EMIT(f, (const char *)arg2_str); EMIT(f, ");\n");
                    }
                    else {
                        EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) { "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)method->c_str); EMIT(f, "("); EMIT(f, (const char *)arg1); EMIT(f, ", "); EMIT(f, (const char *)arg2_str); EMIT(f, "); return; }\n");
                    }
                } else {
                    if (info->has_return && ret_shallow) {
                        EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) { "); File_write_str(f, ret_ctype); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, ret_ctype); EMIT(f, ")); *_r = "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)method->c_str); EMIT(f, "("); EMIT(f, (const char *)arg1); EMIT(f, "); return _r; }\n");
                    }
                    else if (info->has_return) {
                        EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) return (void *)"); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)method->c_str); EMIT(f, "("); EMIT(f, (const char *)arg1); EMIT(f, ");\n");
                    }
                    else {
                        EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) { "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)method->c_str); EMIT(f, "("); EMIT(f, (const char *)arg1); EMIT(f, "); return; }\n");
                    }
                }
            }
            }}
            EMIT(f, "    fprintf(stderr, \"dyn_call: unknown type for "); EMIT(f, (const char *)method->c_str); EMIT(f, "\\n\");\n");
            EMIT(f, "    exit(1);\n");
            EMIT(f, "}\n\n");
        }
        Vec_delete(&dyn_methods, &(Bool){0});
    }

    // Emit dyn_fn wrappers + dispatch
    {
        // First emit wrapper functions that normalize calling convention
        // Wrappers take (void*, ...) and deref shallow params, box shallow returns
        { Expr *_progs_df[2] = { core_program, program };
        for (int _pdf = 0; _pdf < 2; _pdf++) {
            if (!_progs_df[_pdf]) continue;
        for (U32 i = 0; i < _progs_df[_pdf]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_df[_pdf], &(USize){(USize)(i)});
            if (stmt->data.tag != NodeType_TAG_Decl) continue;
            Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
            if (def->data.tag != NodeType_TAG_StructDef && def->data.tag != NodeType_TAG_EnumDef) continue;
            Str *tname = &stmt->data.data.Decl.name;
            Expr *body = Expr_child(def, &(USize){(USize)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace || field->children.count == 0) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                Str *mname = &field->data.data.Decl.name;
                U32 np = fdef->data.data.FuncDef.nparam;
                Bool ret_shallow = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef);
                Str *ret_type = &fdef->data.data.FuncDef.return_type;
                Bool has_return = ret_type->count > 0;
                Bool any_shallow = ret_shallow;
                for (U32 p = 0; p < np; p++) {
                    if (PARAM_IS_SHALLOW(((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(p)}))))
                        any_shallow = 1;
                }
                if (!any_shallow) continue; // no wrapper needed
                // void* Type_method_dyn(void *a, void *b) { ... }
                if (has_return) {
                    EMIT(f, "void *"); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, "_dyn(");
                } else {
                    EMIT(f, "void "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, "_dyn(");
                }
                for (U32 p = 0; p < np; p++) {
                    if (p > 0) EMIT(f, ", ");
                    EMIT(f, "void *_a"); emit_i32(f, p);
                }
                if (np == 0) EMIT(f, "void");
                EMIT(f, ") {\n");
                // Call real function with deref for shallow params
                if (has_return && ret_shallow) {
                    Str *rc = type_name_to_c_value(ret_type);
                    EMIT(f, "    "); File_write_str(f, rc); EMIT(f, " *_r = malloc(sizeof("); File_write_str(f, rc); EMIT(f, ")); *_r = "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, "(");
                } else if (has_return) {
                    EMIT(f, "    return (void *)"); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, "(");
                } else {
                    EMIT(f, "    "); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, "(");
                }
                for (U32 p = 0; p < np; p++) {
                    if (p > 0) EMIT(f, ", ");
                    Param *param = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(p)});
                    if (PARAM_IS_SHALLOW(param)) {
                        Str *pc = type_name_to_c_value(&param->ptype);
                        EMIT(f, "*("); File_write_str(f, pc); EMIT(f, " *)_a"); emit_i32(f, p);
                    } else {
                        EMIT(f, "_a"); emit_i32(f, p);
                    }
                }
                EMIT(f, ");");
                if (has_return && ret_shallow) {
                    EMIT(f, " return _r;");
                }
                EMIT(f, "\n}\n");
            }
        }
        }}
        // Now emit dyn_fn dispatch returning wrappers (or raw for non-shallow)
        EMIT(f, "void *dyn_fn(Str *type_name, Str *method) {\n    (void)type_name; (void)method;\n");
        { Expr *_progs_fd[2] = { core_program, program };
        for (int _pfd = 0; _pfd < 2; _pfd++) {
            if (!_progs_fd[_pfd]) continue;
        for (U32 i = 0; i < _progs_fd[_pfd]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_fd[_pfd], &(USize){(USize)(i)});
            if (stmt->data.tag != NodeType_TAG_Decl) continue;
            Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
            if (def->data.tag != NodeType_TAG_StructDef && def->data.tag != NodeType_TAG_EnumDef) continue;
            Str *tname = &stmt->data.data.Decl.name;
            Expr *body = Expr_child(def, &(USize){(USize)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace || field->children.count == 0) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                Str *mname = &field->data.data.Decl.name;
                Bool any_shallow = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef);
                for (U32 p = 0; p < fdef->data.data.FuncDef.nparam; p++) {
                    if (PARAM_IS_SHALLOW(((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(p)}))))
                        any_shallow = 1;
                }
                const char *suffix = any_shallow ? "_dyn" : "";
                EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0 && method->count == "); emit_u64(f, mname->count); EMIT(f, "ULL && memcmp(method->c_str, \""); EMIT(f, (const char *)mname->c_str); EMIT(f, "\", "); emit_u64(f, mname->count); EMIT(f, "ULL) == 0) return (void*)"); EMIT(f, (const char *)tname->c_str); EMIT(f, "_"); EMIT(f, (const char *)mname->c_str); EMIT(f, (const char *)suffix); EMIT(f, ";\n");
            }
        }
        }}
        EMIT(f, "    fprintf(stderr, \"dyn_fn: unknown %s.%s\\n\", (char*)type_name->c_str, (char*)method->c_str);\n");
        EMIT(f, "    exit(1);\n");
        EMIT(f, "}\n\n");
    }

    // Emit dyn_has_method dispatch function bodies
    {
        // Find dyn_has_method to check return_is_shallow
        Bool dyn_has_shallow = 0;
        { Expr *_progs_dhi[2] = { core_program, program };
        for (int _pdhi = 0; _pdhi < 2 && !dyn_has_shallow; _pdhi++) {
            if (!_progs_dhi[_pdhi]) continue;
            for (U32 i = 0; i < _progs_dhi[_pdhi]->children.count; i++) {
                Expr *stmt = Expr_child(_progs_dhi[_pdhi], &(USize){(USize)(i)});
                if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef &&
                    (stmt->data.data.Decl.name.count == 14 && memcmp(stmt->data.data.Decl.name.c_str, "dyn_has_method", 14) == 0)) {
                    dyn_has_shallow = RETURN_IS_SHALLOW(&Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef);
                    break;
                }
            }
        }}
        const char *dyn_has_ret = dyn_has_shallow ? "Bool" : "Bool *";
        Vec has_methods;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); has_methods = *_vp; free(_vp); }
        if (core_program) collect_dyn_has_methods(core_program, &has_methods);
        collect_dyn_has_methods(program, &has_methods);
        for (U32 m = 0; m < has_methods.count; m++) {
            Str **method_ptr = Vec_get(&has_methods, &(USize){(USize)(m)});
            Str *method = *method_ptr;
            EMIT(f, (const char *)dyn_has_ret); EMIT(f, " dyn_has_"); EMIT(f, (const char *)method->c_str); EMIT(f, "(Str *type_name) {\n    (void)type_name;\n");
            { Expr *_progs_di[2] = { core_program, program };
            for (int _pdi = 0; _pdi < 2; _pdi++) {
                if (!_progs_di[_pdi]) continue;
            for (U32 i = 0; i < _progs_di[_pdi]->children.count; i++) {
                Expr *stmt = Expr_child(_progs_di[_pdi], &(USize){(USize)(i)});
                if (stmt->data.tag != NodeType_TAG_Decl) continue;
                Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
                if (def->data.tag != NodeType_TAG_StructDef && def->data.tag != NodeType_TAG_EnumDef) continue;
                Str *tname = &stmt->data.data.Decl.name;
                Expr *body = Expr_child(def, &(USize){(USize)(0)});
                Bool found = 0;
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (field->data.data.Decl.is_namespace &&
                        Str_eq(&field->data.data.Decl.name, method)) {
                        found = 1;
                        break;
                    }
                }
                if (!found) continue;
                if (dyn_has_shallow) {
                    EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) return 1;\n");
                }
                else {
                    EMIT(f, "    if (type_name->count == "); emit_u64(f, tname->count); EMIT(f, "ULL && memcmp(type_name->c_str, \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\", "); emit_u64(f, tname->count); EMIT(f, "ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }\n");
                }
            }
            }}
            if (dyn_has_shallow)
                EMIT(f, "    return 0;\n");
            else
                EMIT(f, "    Bool *r = malloc(sizeof(Bool)); *r = 0; return r;\n");
            EMIT(f, "}\n\n");
        }
        Vec_delete(&has_methods, &(Bool){0});
    }

    // Emit array/vec builtin helper function bodies
    {
        Vec coll_infos;
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"CollectionInfo", .count = 14, .cap = CAP_LIT}, &(USize){sizeof(CollectionInfo)}); coll_infos = *_vp; free(_vp); }
        if (core_program) collect_collection_builtins(core_program, &coll_infos);
        collect_collection_builtins(program, &coll_infos);
        for (U32 i = 0; i < coll_infos.count; i++) {
            CollectionInfo *ci = Vec_get(&coll_infos, &(USize){(USize)(i)});
            const char *et = (const char *)ci->type_name->c_str;
            U64 et_len = ci->type_name->count;
            if (ci->is_vec) {
                EMIT(f, "Vec *vec_of_"); EMIT(f, (const char *)et); EMIT(f, "(int count, ...) {\n");
                EMIT(f, "    USize _esz = sizeof("); EMIT(f, (const char *)et); EMIT(f, ");\n");
                EMIT(f, "    Vec *_v = Vec_new(&(Str){.c_str = (U8 *)\""); EMIT(f, (const char *)et); EMIT(f, "\", .count = "); emit_u64(f, et_len); EMIT(f, "ULL, .cap = TIL_CAP_LIT}, &(USize){_esz});\n");
                EMIT(f, "    va_list ap; va_start(ap, count);\n");
                EMIT(f, "    for (int _i = 0; _i < count; _i++) {\n");
                {
                    char clone_name[256];
                    snprintf(clone_name, sizeof(clone_name), "%s_clone", et);
                    Str *cn = Str_clone(&(Str){.c_str = (U8*)(clone_name), .count = (U64)strlen((const char*)(clone_name)), .cap = CAP_VIEW});
                    Bool shallow = callee_returns_shallow(cn);
                    Str_delete(cn, &(Bool){1});
                    if (shallow) {
                        EMIT(f, "        "); EMIT(f, (const char *)et); EMIT(f, " *_val = malloc(sizeof("); EMIT(f, (const char *)et); EMIT(f, ")); *_val = "); EMIT(f, (const char *)et); EMIT(f, "_clone(va_arg(ap, "); EMIT(f, (const char *)et); EMIT(f, " *));\n");
                    } else {
                        EMIT(f, "        "); EMIT(f, (const char *)et); EMIT(f, " *_val = "); EMIT(f, (const char *)et); EMIT(f, "_clone(va_arg(ap, "); EMIT(f, (const char *)et); EMIT(f, " *));\n");
                    }
                }
                EMIT(f, "        Vec_push(_v, _val);\n");
                EMIT(f, "    }\n");
                EMIT(f, "    va_end(ap);\n");
                EMIT(f, "    return _v;\n");
                EMIT(f, "}\n\n");
            } else {
                EMIT(f, "Array *array_of_"); EMIT(f, (const char *)et); EMIT(f, "(int count, ...) {\n");
                EMIT(f, "    USize _esz = sizeof("); EMIT(f, (const char *)et); EMIT(f, ");\n");
                EMIT(f, "    USize _cap = count;\n");
                EMIT(f, "    Array *_a = Array_new(&(Str){.c_str = (U8 *)\""); EMIT(f, (const char *)et); EMIT(f, "\", .count = "); emit_u64(f, et_len); EMIT(f, "ULL, .cap = TIL_CAP_LIT}, &(USize){_esz}, &(USize){_cap});\n");
                EMIT(f, "    va_list ap; va_start(ap, count);\n");
                EMIT(f, "    for (int _i = 0; _i < count; _i++) {\n");
                EMIT(f, "        USize _idx = _i;\n");
                {
                    char clone_name[256];
                    snprintf(clone_name, sizeof(clone_name), "%s_clone", et);
                    Str *cn = Str_clone(&(Str){.c_str = (U8*)(clone_name), .count = (U64)strlen((const char*)(clone_name)), .cap = CAP_VIEW});
                    Bool shallow = callee_returns_shallow(cn);
                    Str_delete(cn, &(Bool){1});
                    if (shallow) {
                        EMIT(f, "        "); EMIT(f, (const char *)et); EMIT(f, " *_val = malloc(sizeof("); EMIT(f, (const char *)et); EMIT(f, ")); *_val = "); EMIT(f, (const char *)et); EMIT(f, "_clone(va_arg(ap, "); EMIT(f, (const char *)et); EMIT(f, " *));\n");
                    } else {
                        EMIT(f, "        "); EMIT(f, (const char *)et); EMIT(f, " *_val = "); EMIT(f, (const char *)et); EMIT(f, "_clone(va_arg(ap, "); EMIT(f, (const char *)et); EMIT(f, " *));\n");
                    }
                }
                EMIT(f, "        Array_set(_a, &(USize){_idx}, _val);\n");
                EMIT(f, "    }\n");
                EMIT(f, "    va_end(ap);\n");
                EMIT(f, "    return _a;\n");
                EMIT(f, "}\n\n");
            }
        }
        Vec_delete(&coll_infos, &(Bool){0});
    }

    // Test runner: emit main() that calls all test functions
    if (run_tests) {
        EMIT(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        // Initialize top-level core variables (e.g. CAP_VIEW)
        if (has_script_globals) {
            { Expr *_progs_tr[2] = { codegen_core_program, codegen_program };
            for (int _ptr = 0; _ptr < 2; _ptr++) {
                if (!_progs_tr[_ptr]) continue;
                for (U32 i = 0; i < _progs_tr[_ptr]->children.count; i++) {
                    Expr *gs = Expr_child(_progs_tr[_ptr], &(USize){(USize)(i)});
                    if (gs->data.tag == NodeType_TAG_Decl) {
                        Expr *rhs = Expr_child(gs, &(USize){(USize)(0)});
                        if (rhs->data.tag == NodeType_TAG_FuncDef || rhs->data.tag == NodeType_TAG_StructDef ||
                            rhs->data.tag == NodeType_TAG_EnumDef) continue;
                        if (gs->til_type.tag == TilType_TAG_None && rhs->data.tag == NodeType_TAG_Ident) continue;
                    } else if (gs->data.tag != NodeType_TAG_FCall) {
                        continue;
                    }
                    emit_stmt(f, gs, 1);
                }
            }}
        }
        I32 test_count = 0;
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag != NodeType_TAG_Decl) continue;
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            if (rhs->data.tag != NodeType_TAG_FuncDef) continue;
            if (rhs->data.data.FuncDef.func_type.tag != FuncType_TAG_Test) continue;
            Str *tname = &stmt->data.data.Decl.name;
            EMIT(f, "    "); EMIT(f, (const char *)tname->c_str); EMIT(f, "();\n");
            EMIT(f, "    fprintf(stderr, \"  pass: %s\\n\", \""); EMIT(f, (const char *)tname->c_str); EMIT(f, "\");\n");
            test_count++;
        }
        if (test_count == 0) {
            EMIT(f, "    fprintf(stderr, \"no tests found\\n\");\n");
        } else {
            EMIT(f, "    fprintf(stderr, \""); emit_i32(f, test_count); EMIT(f, "/"); emit_i32(f, test_count); EMIT(f, " tests passed\\n\");\n");
        }
        EMIT(f, "    return 0;\n");
        EMIT(f, "}\n");
    }

    // Lib mode: emit constructor to initialize top-level globals
    if (!run_tests && !is_script && is_lib && has_script_globals) {
        EMIT(f, "__attribute__((constructor))\nstatic void _til_lib_init(void) {\n");
        emit_ns_inits(f, 1);
        { Expr *_progs_li[2] = { codegen_core_program, codegen_program };
        for (int _pli = 0; _pli < 2; _pli++) {
            if (!_progs_li[_pli]) continue;
            for (U32 i = 0; i < _progs_li[_pli]->children.count; i++) {
                Expr *gs = Expr_child(_progs_li[_pli], &(USize){(USize)(i)});
                if (gs->data.tag == NodeType_TAG_Decl) {
                    Expr *rhs = Expr_child(gs, &(USize){(USize)(0)});
                    if (rhs->data.tag == NodeType_TAG_FuncDef || rhs->data.tag == NodeType_TAG_StructDef ||
                        rhs->data.tag == NodeType_TAG_EnumDef) continue;
                } else if (gs->data.tag != NodeType_TAG_FCall) {
                    continue;
                }
                emit_stmt(f, gs, 1);
            }
        }}
        EMIT(f, "}\n\n");
    }

    // Script mode: wrap top-level statements in main()
    if (!run_tests && is_script && !(mode && mode->needs_main)) {
        EMIT(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        // Collect unsafe-to-hoist for script-level statements
        Set_delete(&unsafe_to_hoist, &(Bool){0});
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); unsafe_to_hoist = *_sp; free(_sp); }
        collect_unsafe_to_hoist(program);
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            // Skip func/proc/struct defs (already emitted above)
            if (stmt->data.tag == NodeType_TAG_Decl &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef))
                continue;
            emit_stmt(f, stmt, 1);
        }
        EMIT(f, "    return 0;\n");
        EMIT(f, "}\n");
        Set_delete(&script_globals, &(Bool){0});
        has_script_globals = 0;
    }

    File_close(f);
    Map_delete(&struct_bodies, &(Bool){0});
    Map_delete(&func_defs, &(Bool){0});
    Set_delete(&stack_locals, &(Bool){0});
    Map_delete(&stack_local_types, &(Bool){0});
    Set_delete(&unsafe_to_hoist, &(Bool){0});
    return 0;
}

// --- Header emission helpers (shared by build_header and build_forward_header) ---

// Emit struct/enum forward declarations
static void emit_header_forward_decls(File *f, Expr *core_program, Expr *program) {
    { Expr *_progs_hfd[2] = { core_program, program };
    for (int _phfd = 0; _phfd < 2; _phfd++) {
        if (!_progs_hfd[_phfd]) continue;
    for (U32 i = 0; i < _progs_hfd[_phfd]->children.count; i++) {
        Expr *stmt = Expr_child(_progs_hfd[_phfd], &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef) {
            if (is_ext_h_type(&stmt->data.data.Decl.name)) continue;
            EMIT(f, "typedef struct "); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, " "); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
        }
        if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
            Str *ename = &stmt->data.data.Decl.name;
            Expr *ebody = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
            EMIT(f, "typedef enum {\n");
            I32 tag = 0;
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                if (v->data.data.Decl.is_namespace) continue;
                if (tag > 0) EMIT(f, ",\n");
                EMIT(f, "    "); EMIT(f, (const char *)ename->c_str); EMIT(f, "_TAG_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str);
                tag++;
            }
            EMIT(f, "\n} "); EMIT(f, (const char *)ename->c_str); EMIT(f, "_tag;\n");
            EMIT(f, "typedef struct "); EMIT(f, (const char *)ename->c_str); EMIT(f, " "); EMIT(f, (const char *)ename->c_str); EMIT(f, ";\n");
        }
    }
    }}
    EMIT(f, "\n");
}

// Emit full struct/enum definitions (topo-sorted) and function declarations
static void emit_header_defs_and_funcs(File *f, Expr *core_program, Expr *program) {
    // Struct definitions with fields in dependency order (topo sorted)
    {
        Vec to_emit_h; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(U32)}); to_emit_h = *_vp; free(_vp); }
        Vec _prog_refs_h; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); _prog_refs_h = *_vp; free(_vp); }
        { Expr *_progs_ht[2] = { core_program, program };
        for (int _pht = 0; _pht < 2; _pht++) {
            if (!_progs_ht[_pht]) continue;
            for (U32 i = 0; i < _progs_ht[_pht]->children.count; i++) {
                Expr *stmt = Expr_child(_progs_ht[_pht], &(USize){(USize)(i)});
                if (stmt->data.tag == NodeType_TAG_Decl &&
                    (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                     Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                    U32 idx = _prog_refs_h.count;
                    { U32 *_p = malloc(sizeof(U32)); *_p = idx; Vec_push(&to_emit_h, _p); }
                    { Expr **_p = malloc(sizeof(Expr *)); *_p = stmt; Vec_push(&_prog_refs_h, _p); }
                }
            }
        }}
        Set emitted_h; { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); emitted_h = *_sp; free(_sp); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U8", .count = 2, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I16", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"F32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }

        U32 remaining_h = _prog_refs_h.count;
        Bool *done_h = calloc(_prog_refs_h.count, sizeof(Bool));
        while (remaining_h > 0) {
            Bool progress_h = 0;
            for (U32 ei = 0; ei < _prog_refs_h.count; ei++) {
                if (done_h[ei]) continue;
                Expr *stmt = *(Expr **)Vec_get(&_prog_refs_h, &(USize){(USize)(ei)});
                Str *name = &stmt->data.data.Decl.name;
                Expr *def = Expr_child(stmt, &(USize){(USize)(0)});

                Bool deps_ok = 1;
                if (def->data.tag == NodeType_TAG_StructDef) {
                    Expr *body = Expr_child(def, &(USize){(USize)(0)});
                    for (U32 fi = 0; fi < body->children.count; fi++) {
                        Expr *field = Expr_child(body, &(USize){(USize)(fi)});
                        if (field->data.data.Decl.is_namespace) continue;
                        if (DECL_IS_SHALLOW(field->data.data.Decl) &&
                            (field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) &&
                            (Expr_child(field, &(USize){(USize)(0)})->struct_name.count > 0)) {
                            if (!Set_has(&emitted_h, &Expr_child(field, &(USize){(USize)(0)})->struct_name)) {
                                deps_ok = 0;
                                break;
                            }
                        }
                    }
                } else if (def->data.tag == NodeType_TAG_EnumDef) {
                    Expr *body = Expr_child(def, &(USize){(USize)(0)});
                    for (U32 fi = 0; fi < body->children.count; fi++) {
                        Expr *v = Expr_child(body, &(USize){(USize)(fi)});
                        if (v->data.data.Decl.is_namespace) continue;
                        if ((v->data.data.Decl.explicit_type).count > 0 &&
                            !is_primitive_type(&v->data.data.Decl.explicit_type) &&
                            !is_funcsig_type(&v->data.data.Decl.explicit_type)) {
                            if (!Set_has(&emitted_h, &v->data.data.Decl.explicit_type)) {
                                deps_ok = 0;
                                break;
                            }
                        }
                    }
                }

                if (!deps_ok) continue;

                if (def->data.tag == NodeType_TAG_StructDef) {
                    emit_struct_typedef(f, name, def);
                    EMIT(f, "\n");
                } else {
                    Str *ename = name;
                    Expr *ebody = Expr_child(def, &(USize){(USize)(0)});
                    Bool hp = enum_has_payloads(def);
                    EMIT(f, "struct "); EMIT(f, (const char *)ename->c_str); EMIT(f, " {\n");
                    EMIT(f, "    "); EMIT(f, (const char *)ename->c_str); EMIT(f, "_tag tag;\n");
                    if (hp) {
                        EMIT(f, "    union {\n");
                        for (U32 j = 0; j < ebody->children.count; j++) {
                            Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                            if (v->data.data.Decl.is_namespace) continue;
                            if (v->data.data.Decl.explicit_type.count > 0) {
                                EMIT(f, "        "); { Str *_tnv = type_name_to_c_value(&v->data.data.Decl.explicit_type); File_write_str(f, _tnv); Str_delete(_tnv, &(Bool){1}); }; EMIT(f, " "); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, ";\n");
                            }
                        }
                        EMIT(f, "    } data;\n");
                    }
                    EMIT(f, "};\n\n");
                }
                { Str *_p = Str_clone(name); Set_add(&emitted_h, _p); }
                done_h[ei] = 1;
                remaining_h--;
                progress_h = 1;
            }
            if (!progress_h) {
                for (U32 ei = 0; ei < to_emit_h.count; ei++) {
                    if (done_h[ei]) continue;
                    U32 idx = *(U32 *)Vec_get(&to_emit_h, &(USize){(USize)(ei)});
                    Expr *stmt = Expr_child(program, &(USize){(USize)(idx)});
                    Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
                    if (def->data.tag == NodeType_TAG_StructDef) {
                        emit_struct_typedef(f, &stmt->data.data.Decl.name, def);
                        EMIT(f, "\n");
                    } else {
                        Str *ename = &stmt->data.data.Decl.name;
                        Expr *ebody = Expr_child(def, &(USize){(USize)(0)});
                        Bool hp = enum_has_payloads(def);
                        EMIT(f, "struct "); EMIT(f, (const char *)ename->c_str); EMIT(f, " {\n");
                        EMIT(f, "    "); EMIT(f, (const char *)ename->c_str); EMIT(f, "_tag tag;\n");
                        if (hp) {
                            EMIT(f, "    union {\n");
                            for (U32 j = 0; j < ebody->children.count; j++) {
                                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                                if (v->data.data.Decl.is_namespace) continue;
                                if (v->data.data.Decl.explicit_type.count > 0) {
                                    EMIT(f, "        "); { Str *_tnv = type_name_to_c_value(&v->data.data.Decl.explicit_type); File_write_str(f, _tnv); Str_delete(_tnv, &(Bool){1}); }; EMIT(f, " "); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, ";\n");
                                }
                            }
                            EMIT(f, "    } data;\n");
                        }
                        EMIT(f, "};\n\n");
                    }
                }
                break;
            }
        }
        free(done_h);
        Vec_delete(&to_emit_h, &(Bool){0});
        Vec_delete(&_prog_refs_h, &(Bool){0});
        Set_delete(&emitted_h, &(Bool){0});
    }

    // Function forward declarations (namespace methods + top-level)
    { Expr *_progs_ffd[2] = { core_program, program };
    for (int _pffd = 0; _pffd < 2; _pffd++) {
        if (!_progs_ffd[_pffd]) continue;
        Bool _is_core_pass_ffd = (_pffd == 0 && core_program != NULL);
    for (U32 i = 0; i < _progs_ffd[_pffd]->children.count; i++) {
        Expr *stmt = Expr_child(_progs_ffd[_pffd], &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                         Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
            Str *sname = &stmt->data.data.Decl.name;
            if (is_scalar_method_type(sname)) continue;
            Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                FuncType fft = fdef->data.data.FuncDef.func_type;
                if ((fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) && _is_core_pass_ffd) continue;
                Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
                if (fdef->data.data.FuncDef.return_type.count > 0)
                    ret = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                        ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                        : type_name_to_c(&fdef->data.data.FuncDef.return_type);
                File_write_str(f, ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, "(");
                emit_param_list(f, fdef, 1);
                EMIT(f, ");\n");
            }
        } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
            Expr *func_def = Expr_child(stmt, &(USize){(USize)(0)});
            if (func_def->children.count == 0) continue;
            FuncType fft = func_def->data.data.FuncDef.func_type;
            if ((fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) && _is_core_pass_ffd) continue;
            Str *ret = Str_clone(&(Str){.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT});
            if (func_def->data.data.FuncDef.return_type.count > 0)
                ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                    ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                    : type_name_to_c(&func_def->data.data.FuncDef.return_type);
            File_write_str(f, ret); EMIT(f, " "); { Str *_fc = func_to_c(&stmt->data.data.Decl.name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
            emit_param_list(f, func_def, 1);
            EMIT(f, ");\n");
        }
    }
    }}

    // Enum auto-helper forward declarations (user only)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *ebody = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
            Expr *eq_fdef = NULL;
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *field = Expr_child(ebody, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace && (field->data.data.Decl.name.count == 2 && memcmp(field->data.data.Decl.name.c_str, "eq", 2) == 0) &&
                    Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                    eq_fdef = Expr_child(field, &(USize){(USize)(0)});
                    break;
                }
            }
            const char *eq_ret = (eq_fdef && RETURN_IS_SHALLOW(&eq_fdef->data.data.FuncDef)) ? "Bool" : "Bool *";
            EMIT(f, (const char *)eq_ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_eq("); EMIT(f, (const char *)sname->c_str); EMIT(f, " *, "); EMIT(f, (const char *)sname->c_str); EMIT(f, " *);\n");
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                if (v->data.data.Decl.is_namespace) continue;
                if (v->data.data.Decl.explicit_type.count > 0) {
                    EMIT(f, (const char *)sname->c_str); EMIT(f, " *"); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, "("); { Str *_tnc = type_name_to_c(&v->data.data.Decl.explicit_type); File_write_str(f, _tnc); Str_delete(_tnc, &(Bool){1}); }; EMIT(f, ");\n");
                } else {
                    EMIT(f, (const char *)sname->c_str); EMIT(f, " *"); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, "();\n");
                }
            }
        }
    }
    EMIT(f, "\n");
}

// is_exported_top_level_global: moved to builder.til

static void emit_header_global_decls(File *f, Expr *core_program, Expr *program) {
    { Expr *_progs_gd[2] = { core_program, program };
    for (int _pgd = 0; _pgd < 2; _pgd++) {
        if (!_progs_gd[_pgd]) continue;
    for (U32 i = 0; i < _progs_gd[_pgd]->children.count; i++) {
        Expr *stmt = Expr_child(_progs_gd[_pgd], &(USize){(USize)(i)});
        if (!is_exported_top_level_global(stmt)) continue;
        Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
        Str *ctype = stmt->til_type.tag == TilType_TAG_Dynamic
            ? til_type_to_c(stmt->til_type)
            : c_type_name(stmt->til_type, &rhs->struct_name);
        EMIT(f, "extern "); File_write_str(f, ctype); Str_delete(ctype, &(Bool){1}); EMIT(f, " "); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
    }
    }}
    EMIT(f, "\n");
}

// Emit forward.h -- all forward declarations + full struct definitions + function declarations.
// Used by link_c files via -include. NOT visible to ctil build.
I32 build_forward_header(Expr *core_program, Expr *program, Str *fwd_path) {
    File *f = File_new(fwd_path, 1);
    if (!f) return 1;
    EMIT(f, "#pragma once\n#include \"ext.h\"\n\n");
    emit_header_forward_decls(f, core_program, program);
    emit_header_defs_and_funcs(f, core_program, program);
    emit_header_global_decls(f, core_program, program);
    File_close(f);
    return 0;
}

I32 build_header(Expr *core_program, Expr *program, Str *h_path) {
    // Collect FuncSig names for type_name_to_c
    if (!has_funcsig_names) {
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); funcsig_names = *_sp; free(_sp); }
        has_funcsig_names = 1;
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef &&
                Expr_child(stmt, &(USize){(USize)(0)})->children.count == 0) {
                Str *n = &stmt->data.data.Decl.name;
                { Str *_p = malloc(sizeof(Str)); *_p = (Str){n->c_str, n->count, CAP_VIEW}; Set_add(&funcsig_names, _p); }
            }
        }
    }
    File *f = File_new(h_path, 1);
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", (const char *)h_path->c_str);
        return 1;
    }

    EMIT(f, "#pragma once\n#include \"ext.h\"\n\n");
    emit_header_forward_decls(f, core_program, program);
    emit_header_defs_and_funcs(f, core_program, program);
    emit_header_global_decls(f, core_program, program);
    EMIT(f, "#include \"ext.h\"\n\n");

    File_close(f);
    return 0;
}

// Dead code — replaced by emit_header_defs_and_funcs. Kept in #if 0 until verified.
#if 0
    {
        Vec to_emit_h; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(U32)}); to_emit_h = *_vp; free(_vp); }
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                { U32 *_p = malloc(sizeof(U32)); *_p = i; Vec_push(&to_emit_h, _p); }
            }
        }
        Set emitted_h; { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); emitted_h = *_sp; free(_sp); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U8", .count = 2, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I16", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"F32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }

        U32 remaining_h = to_emit_h.count;
        Bool *done_h = calloc(to_emit_h.count, sizeof(Bool));
        while (remaining_h > 0) {
            Bool progress_h = 0;
            for (U32 ei = 0; ei < to_emit_h.count; ei++) {
                if (done_h[ei]) continue;
                U32 idx = *(U32 *)Vec_get(&to_emit_h, &(USize){(USize)(ei)});
                Expr *stmt = Expr_child(program, &(USize){(USize)(idx)});
                Str *name = &stmt->data.data.Decl.name;
                Expr *def = Expr_child(stmt, &(USize){(USize)(0)});

                Bool deps_ok = 1;
                if (def->data.tag == NodeType_TAG_StructDef) {
                    Expr *body = Expr_child(def, &(USize){(USize)(0)});
                    for (U32 fi = 0; fi < body->children.count; fi++) {
                        Expr *field = Expr_child(body, &(USize){(USize)(fi)});
                        if (field->data.data.Decl.is_namespace) continue;
                        if (DECL_IS_SHALLOW(field->data.data.Decl) &&
                            (field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) &&
                            (Expr_child(field, &(USize){(USize)(0)})->struct_name.count > 0)) {
                            if (!Set_has(&emitted_h, &Expr_child(field, &(USize){(USize)(0)})->struct_name)) {
                                deps_ok = 0;
                                break;
                            }
                        }
                    }
                } else if (def->data.tag == NodeType_TAG_EnumDef) {
                    Expr *body = Expr_child(def, &(USize){(USize)(0)});
                    for (U32 fi = 0; fi < body->children.count; fi++) {
                        Expr *v = Expr_child(body, &(USize){(USize)(fi)});
                        if (v->data.data.Decl.is_namespace) continue;
                        if ((v->data.data.Decl.explicit_type).count > 0 &&
                            !is_primitive_type(&v->data.data.Decl.explicit_type) &&
                            !is_funcsig_type(&v->data.data.Decl.explicit_type)) {
                            if (!Set_has(&emitted_h, &v->data.data.Decl.explicit_type)) {
                                deps_ok = 0;
                                break;
                            }
                        }
                    }
                }

                if (!deps_ok) continue;

                if (def->data.tag == NodeType_TAG_StructDef) {
                    emit_struct_typedef(f, name, def);
                    EMIT(f, "\n");
                } else {
                    Str *ename = name;
                    Expr *ebody = Expr_child(def, &(USize){(USize)(0)});
                    Bool hp = enum_has_payloads(def);
                    EMIT(f, "struct "); EMIT(f, (const char *)ename->c_str); EMIT(f, " {\n");
                    EMIT(f, "    "); EMIT(f, (const char *)ename->c_str); EMIT(f, "_tag tag;\n");
                    if (hp) {
                        EMIT(f, "    union {\n");
                        for (U32 j = 0; j < ebody->children.count; j++) {
                            Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                            if (v->data.data.Decl.is_namespace) continue;
                            if (v->data.data.Decl.explicit_type.count > 0) {
                                EMIT(f, "        "); { Str *_tnv = type_name_to_c_value(&v->data.data.Decl.explicit_type); File_write_str(f, _tnv); Str_delete(_tnv, &(Bool){1}); }; EMIT(f, " "); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, ";\n");
                            }
                        }
                        EMIT(f, "    } data;\n");
                    }
                    EMIT(f, "};\n\n");
                }
                { Str *_p = Str_clone(name); Set_add(&emitted_h, _p); }
                done_h[ei] = 1;
                remaining_h--;
                progress_h = 1;
            }
            if (!progress_h) {
                for (U32 ei = 0; ei < to_emit_h.count; ei++) {
                    if (done_h[ei]) continue;
                    U32 idx = *(U32 *)Vec_get(&to_emit_h, &(USize){(USize)(ei)});
                    Expr *stmt = Expr_child(program, &(USize){(USize)(idx)});
                    Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
                    if (def->data.tag == NodeType_TAG_StructDef) {
                        emit_struct_typedef(f, &stmt->data.data.Decl.name, def);
                        EMIT(f, "\n");
                    } else {
                        Str *ename = &stmt->data.data.Decl.name;
                        Expr *ebody = Expr_child(def, &(USize){(USize)(0)});
                        Bool hp = enum_has_payloads(def);
                        EMIT(f, "struct "); EMIT(f, (const char *)ename->c_str); EMIT(f, " {\n");
                        EMIT(f, "    "); EMIT(f, (const char *)ename->c_str); EMIT(f, "_tag tag;\n");
                        if (hp) {
                            EMIT(f, "    union {\n");
                            for (U32 j = 0; j < ebody->children.count; j++) {
                                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                                if (v->data.data.Decl.is_namespace) continue;
                                if (v->data.data.Decl.explicit_type.count > 0) {
                                    EMIT(f, "        "); { Str *_tnv = type_name_to_c_value(&v->data.data.Decl.explicit_type); File_write_str(f, _tnv); Str_delete(_tnv, &(Bool){1}); }; EMIT(f, " "); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, ";\n");
                                }
                            }
                            EMIT(f, "    } data;\n");
                        }
                        EMIT(f, "};\n\n");
                    }
                }
                break;
            }
        }
        free(done_h);
        Vec_delete(&to_emit_h, &(Bool){0});
        Set_delete(&emitted_h, &(Bool){0});
    }

    // Function forward declarations (namespace methods + top-level)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                         Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
            Str *sname = &stmt->data.data.Decl.name;
            if (is_scalar_method_type(sname)) continue;
            Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                FuncType fft = fdef->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                const char *ret = "void";
                if (fdef->data.data.FuncDef.return_type.count > 0)
                    ret = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                        ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                        : type_name_to_c(&fdef->data.data.FuncDef.return_type);
                EMIT(f, (const char *)ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, "(");
                emit_param_list(f, fdef, 1);
                EMIT(f, ");\n");
            }
        } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
            Expr *func_def = Expr_child(stmt, &(USize){(USize)(0)});
            if (func_def->children.count == 0) continue;  // FuncSig: skip
            FuncType fft = func_def->data.data.FuncDef.func_type;
            if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
            const char *ret = "void";
            if (func_def->data.data.FuncDef.return_type.count > 0)
                ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                    ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                    : type_name_to_c(&func_def->data.data.FuncDef.return_type);
            EMIT(f, (const char *)ret); EMIT(f, " "); EMIT(f, (const char *)func_to_c(&stmt->data.data.Decl.name)); EMIT(f, "(");
            emit_param_list(f, func_def, 1);
            EMIT(f, ");\n");
        }
    }

    // Enum auto-helper forward declarations (eq, constructors, is_Variant, get_Variant)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *ebody = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){0});
            // Find eq fdef to check return_is_shallow
            Expr *eq_fdef = NULL;
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *field = Expr_child(ebody, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace && (field->data.data.Decl.name.count == 2 && memcmp(field->data.data.Decl.name.c_str, "eq", 2) == 0) &&
                    Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                    eq_fdef = Expr_child(field, &(USize){(USize)(0)});
                    break;
                }
            }
            const char *eq_ret = (eq_fdef && RETURN_IS_SHALLOW(&eq_fdef->data.data.FuncDef)) ? "Bool" : "Bool *";
            EMIT(f, (const char *)eq_ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_eq("); EMIT(f, (const char *)sname->c_str); EMIT(f, " *, "); EMIT(f, (const char *)sname->c_str); EMIT(f, " *);\n");
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *v = Expr_child(ebody, &(USize){(USize)(j)});
                if (v->data.data.Decl.is_namespace) continue;
                if (v->data.data.Decl.explicit_type.count > 0) {
                    EMIT(f, (const char *)sname->c_str); EMIT(f, " *"); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, "("); { Str *_tnc = type_name_to_c(&v->data.data.Decl.explicit_type); File_write_str(f, _tnc); Str_delete(_tnc, &(Bool){1}); }; EMIT(f, ");\n");
                } else {
                    EMIT(f, (const char *)sname->c_str); EMIT(f, " *"); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)v->data.data.Decl.name.c_str); EMIT(f, "();\n");
                }
            }
        }
    }
    EMIT(f, "\n");

    File_close(f);
    return 0;
#endif

// Emit a til type default value for binding generation
static void emit_til_default(File *f, TilType t, Str *struct_name) {
    switch (t.tag) {
    case TilType_TAG_I64: case TilType_TAG_I16: case TilType_TAG_I32:
    case TilType_TAG_U32: case TilType_TAG_U64: case TilType_TAG_F32: EMIT(f, "0"); break;
    case TilType_TAG_U8:   EMIT(f, "0"); break;
    case TilType_TAG_Bool: EMIT(f, "false"); break;
    case TilType_TAG_Struct:
    case TilType_TAG_Enum:
        if (struct_name && strcmp((const char *)struct_name->c_str, "Str") == 0)
            EMIT(f, "\"\"");
        else if (struct_name) {
            EMIT(f, (const char *)struct_name->c_str); EMIT(f, "()");
        }
        else
            EMIT(f, "0");
        break;
    default: EMIT(f, "0"); break;
    }
}

I32 build_til_binding(Expr *core_program, Expr *program, Str *til_path, Str *lib_name) {
    (void)core_program;
    File *f = File_new(til_path, 1);
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", (const char *)til_path->c_str);
        return 1;
    }

    EMIT(f, "// Auto-generated FFI binding for "); EMIT(f, (const char *)lib_name->c_str); EMIT(f, "\n");
    EMIT(f, "link(\""); EMIT(f, (const char *)lib_name->c_str); EMIT(f, "\")\n\n");

    // Only emit user program bindings (not core)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != NodeType_TAG_Decl) continue;
        Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
        Str *name = &stmt->data.data.Decl.name;

        if (rhs->data.tag == NodeType_TAG_StructDef) {
            Expr *body = Expr_child(rhs, &(USize){(USize)(0)});
            EMIT(f, (const char *)name->c_str); EMIT(f, " := struct {\n");
            // Instance fields
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace) continue;
                EMIT(f, "    ");
                if (field->data.data.Decl.is_mut) EMIT(f, "mut ");
                if (DECL_IS_OWN(field->data.data.Decl)) EMIT(f, "own ");
                EMIT(f, (const char *)field->data.data.Decl.name.c_str);
                if (field->data.data.Decl.explicit_type.count > 0) {
                    EMIT(f, " : "); EMIT(f, (const char *)field->data.data.Decl.explicit_type.c_str);
                }
                EMIT(f, " := ");
                emit_til_default(f, field->til_type, &Expr_child(field, &(USize){(USize)(0)})->struct_name);
                EMIT(f, "\n");
            }
            // Namespace methods
            Bool has_ns = 0;
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                FuncType fft = fdef->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                if (!has_ns) { EMIT(f, "    namespace:\n"); has_ns = 1; }
                const char *kw = (fft.tag == FuncType_TAG_Proc || fft.tag == FuncType_TAG_Test) ? "ext_proc" : "ext_func";
                EMIT(f, "    "); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, " := "); EMIT(f, (const char *)kw); EMIT(f, "(");
                for (U32 p = 0; p < fdef->data.data.FuncDef.nparam; p++) {
                    if (p > 0) EMIT(f, ", ");
                    Param *_sp = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(p)});
                    if (PARAM_IS_OWN(_sp))
                        EMIT(f, "own ");
                    EMIT(f, (const char *)_sp->name.c_str); EMIT(f, ": "); EMIT(f, (const char *)_sp->ptype.c_str);
                }
                EMIT(f, ")");
                if (fdef->data.data.FuncDef.return_type.count > 0) {
                    EMIT(f, " returns ");
                    if (RETURN_IS_REF(&fdef->data.data.FuncDef)) EMIT(f, "ref ");
                    if (RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)) EMIT(f, "shallow ");
                    EMIT(f, (const char *)fdef->data.data.FuncDef.return_type.c_str);
                }
                EMIT(f, " {}\n");
            }
            EMIT(f, "}\n\n");

        } else if (rhs->data.tag == NodeType_TAG_EnumDef) {
            Expr *body = Expr_child(rhs, &(USize){(USize)(0)});
            EMIT(f, (const char *)name->c_str); EMIT(f, " := enum {\n");
            // Variants
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *v = Expr_child(body, &(USize){(USize)(j)});
                if (v->data.data.Decl.is_namespace) continue;
                EMIT(f, "    "); EMIT(f, (const char *)v->data.data.Decl.name.c_str);
                if (v->data.data.Decl.explicit_type.count > 0) {
                    EMIT(f, ": "); EMIT(f, (const char *)v->data.data.Decl.explicit_type.c_str);
                }
                EMIT(f, ",\n");
            }
            // Namespace methods (user-defined, not auto-generated)
            Bool has_ns = 0;
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                FuncType fft = fdef->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                if (!has_ns) { EMIT(f, "    namespace:\n"); has_ns = 1; }
                const char *kw = (fft.tag == FuncType_TAG_Proc || fft.tag == FuncType_TAG_Test) ? "ext_proc" : "ext_func";
                EMIT(f, "    "); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, " := "); EMIT(f, (const char *)kw); EMIT(f, "(");
                for (U32 p = 0; p < fdef->data.data.FuncDef.nparam; p++) {
                    if (p > 0) EMIT(f, ", ");
                    Param *_ep = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(p)});
                    if (PARAM_IS_OWN(_ep))
                        EMIT(f, "own ");
                    EMIT(f, (const char *)_ep->name.c_str); EMIT(f, ": "); EMIT(f, (const char *)_ep->ptype.c_str);
                }
                EMIT(f, ")");
                if (fdef->data.data.FuncDef.return_type.count > 0) {
                    EMIT(f, " returns ");
                    if (RETURN_IS_REF(&fdef->data.data.FuncDef)) EMIT(f, "ref ");
                    if (RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)) EMIT(f, "shallow ");
                    EMIT(f, (const char *)fdef->data.data.FuncDef.return_type.c_str);
                }
                EMIT(f, " {}\n");
            }
            EMIT(f, "}\n\n");

        } else if (rhs->data.tag == NodeType_TAG_FuncDef) {
            FuncType fft = rhs->data.data.FuncDef.func_type;
            if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
            if (fft.tag == FuncType_TAG_Test) continue;
            const char *kw = (fft.tag == FuncType_TAG_Proc) ? "ext_proc" : "ext_func";
            EMIT(f, (const char *)name->c_str); EMIT(f, " := "); EMIT(f, (const char *)kw); EMIT(f, "(");
            for (U32 p = 0; p < rhs->data.data.FuncDef.nparam; p++) {
                if (p > 0) EMIT(f, ", ");
                Param *_fp = (Param*)Vec_get(&rhs->data.data.FuncDef.params, &(USize){(USize)(p)});
                if (PARAM_IS_OWN(_fp))
                    EMIT(f, "own ");
                I32 vi = rhs->data.data.FuncDef.variadic_index;
                I32 kwi = rhs->data.data.FuncDef.kwargs_index;
                if ((I32)p == vi) EMIT(f, "..");
                if ((I32)p == kwi) {
                    EMIT(f, (const char *)_fp->name.c_str); EMIT(f, ": ...");
                } else {
                    EMIT(f, (const char *)_fp->name.c_str); EMIT(f, ": "); EMIT(f, (const char *)_fp->ptype.c_str);
                }
            }
            EMIT(f, ")");
            if (rhs->data.data.FuncDef.return_type.count > 0) {
                EMIT(f, " returns ");
                if (RETURN_IS_REF(&rhs->data.data.FuncDef)) EMIT(f, "ref ");
                if (RETURN_IS_SHALLOW(&rhs->data.data.FuncDef)) EMIT(f, "shallow ");
                EMIT(f, (const char *)rhs->data.data.FuncDef.return_type.c_str);
            }
            EMIT(f, " {}\n\n");
        }
    }

    File_close(f);
    return 0;
}

I32 compile_lib(Str *c_path, Str *lib_name,
                Str *ext_c_path, Str *user_c_path,
                Str *link_flags, Str *include_flags) {
    if (user_c_path && user_c_path->count == 0) user_c_path = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
    if (include_flags && include_flags->count == 0) include_flags = NULL;
    // Extract directory from ext_c_path for -I flag
    Str *ext_dir;
    Str _dot_str = {.c_str = (U8*)".", .count = 1, .cap = CAP_LIT};
    {
        I64 slash = Str_rfind(ext_c_path, &(Str){.c_str = (U8*)"/", .count = 1, .cap = CAP_LIT});
        ext_dir = slash >= 0 ? Str_substr(ext_c_path, &(USize){(USize)(0)}, &(USize){(USize)(slash)}) : &_dot_str;
    }

    Str *lf = link_flags ? link_flags : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};

    // Compile library .c to object
    Str *obj_path = Str_concat(Str_concat(&(Str){.c_str = (U8*)"gen/lib/", .count = 8, .cap = CAP_LIT}, lib_name), &(Str){.c_str = (U8*)".o", .count = 2, .cap = CAP_LIT});
    Str *cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
        &(Str){.c_str = (U8*)"cc -Wall -Wextra -Werror -fPIC -I", .count = 33, .cap = CAP_LIT}, ext_dir),
        &(Str){.c_str = (U8*)" -c ", .count = 4, .cap = CAP_LIT}), c_path), &(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}), obj_path);
    int result = system((const char *)cmd->c_str);
    if (result != 0) {
        fprintf(stderr, "error: library compilation failed\n");
        return 1;
    }

    // Compile ext.c to object
    Str *ext_obj = &(Str){.c_str = (U8*)"gen/lib/ext.o", .count = 13, .cap = CAP_LIT};
    cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
        &(Str){.c_str = (U8*)"cc -Wall -Wextra -Werror -fPIC -I", .count = 33, .cap = CAP_LIT}, ext_dir),
        &(Str){.c_str = (U8*)" -c ", .count = 4, .cap = CAP_LIT}), ext_c_path), &(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}), ext_obj);
    result = system((const char *)cmd->c_str);
    if (result != 0) {
        fprintf(stderr, "error: ext.c compilation failed\n");
        return 1;
    }

    // Compile user .c to object if present
    Str *ifl = include_flags ? include_flags : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    Str *user_obj = &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    if (user_c_path) {
        user_obj = &(Str){.c_str = (U8*)"gen/lib/user.o", .count = 14, .cap = CAP_LIT};
        cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
            &(Str){.c_str = (U8*)"cc -Wall -Wextra -Werror -fPIC -I", .count = 33, .cap = CAP_LIT}, ext_dir),
            ifl),
            &(Str){.c_str = (U8*)" -c ", .count = 4, .cap = CAP_LIT}), user_c_path), &(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}), user_obj);
        result = system((const char *)cmd->c_str);
        if (result != 0) {
            fprintf(stderr, "error: user .c compilation failed\n");
            return 1;
        }
    }

    // Create shared library
    Str *so_path = Str_concat(Str_concat(&(Str){.c_str = (U8*)"gen/lib/lib", .count = 11, .cap = CAP_LIT}, lib_name), &(Str){.c_str = (U8*)".so", .count = 3, .cap = CAP_LIT});
    cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
        &(Str){.c_str = (U8*)"cc -shared -Wl,--allow-multiple-definition -o ", .count = 46, .cap = CAP_LIT}, so_path),
        &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), obj_path), &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), ext_obj),
        Str_concat(Str_concat(&(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}, user_obj), lf));
    result = system((const char *)cmd->c_str);
    if (result != 0) {
        fprintf(stderr, "error: shared library creation failed\n");
        return 1;
    }

    // Create static library
    Str *a_path = Str_concat(Str_concat(&(Str){.c_str = (U8*)"gen/lib/lib", .count = 11, .cap = CAP_LIT}, lib_name), &(Str){.c_str = (U8*)".a", .count = 2, .cap = CAP_LIT});
    cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
        &(Str){.c_str = (U8*)"ar rcs ", .count = 7, .cap = CAP_LIT}, a_path),
        &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), obj_path), &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), ext_obj),
        Str_concat(&(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}, user_obj));
    result = system((const char *)cmd->c_str);
    if (result != 0) {
        fprintf(stderr, "error: static library creation failed\n");
        return 1;
    }

    return 0;
}

I32 compile_c(Str *c_path, Str *bin_path, Str *ext_c_path, Str *user_c_path, Str *link_flags, Str *include_flags) {
    // Normalize empty strings to NULL for optional params
    if (user_c_path && user_c_path->count == 0) user_c_path = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
    if (include_flags && include_flags->count == 0) include_flags = NULL;
    Str *ifl = include_flags ? include_flags : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    // Extract directory from ext_c_path for -I flag
    Str *ext_dir;
    Str _dot_str = {.c_str = (U8*)".", .count = 1, .cap = CAP_LIT};
    {
        I64 slash = Str_rfind(ext_c_path, &(Str){.c_str = (U8*)"/", .count = 1, .cap = CAP_LIT});
        ext_dir = slash >= 0 ? Str_substr(ext_c_path, &(USize){(USize)(0)}, &(USize){(USize)(slash)}) : &_dot_str;
    }

    Str *lf = link_flags ? link_flags : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};

    // If link_c files present, compile each to .o separately with -include forward.h
    Str *user_part = &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    if (user_c_path) {
        I64 c_slash = Str_rfind(c_path, &(Str){.c_str = (U8*)"/", .count = 1, .cap = CAP_LIT});
        Str *c_dir = c_slash >= 0 ? Str_substr(c_path, &(USize){0}, &(USize){(USize)c_slash}) : &_dot_str;
        I64 c_dot = Str_rfind(c_path, &(Str){.c_str = (U8*)".", .count = 1, .cap = CAP_LIT});
        Str *c_base = (c_dot > c_slash) ? Str_substr(c_path, &(USize){0}, &(USize){(USize)c_dot}) : c_path;
        Str *fwd_path = Str_concat(c_base, &(Str){.c_str = (U8*)"_forward.h", .count = 10, .cap = CAP_LIT});

        // Split space-separated link_c files and compile each individually
        Vec *files = Str_split(user_c_path, &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT});
        Str *all_objs = &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
        for (U32 fi = 0; fi < files->count; fi++) {
            Str *file = (Str *)Vec_get(files, &(USize){(USize)fi});
            if (file->count == 0) continue;
            char obj_name[32];
            snprintf(obj_name, sizeof(obj_name), "/user_%u.o", fi);
            Str *user_obj = Str_concat(c_dir, &(Str){.c_str = (U8*)obj_name, .count = (U64)strlen(obj_name), .cap = CAP_VIEW});

            // Skip -include forward.h for src/c/ files — they have their own
            // headers (boot/ast.h etc.) which define the same types
            // Skip -include forward.h for src/c/ files — they have their own
            // headers (boot/ast.h etc.) which define the same types
            Bool skip_fwd = (file->count > 6 && memcmp(file->c_str, "src/c/", 6) == 0);
            Str *fwd_flag = skip_fwd
                ? &(Str){.c_str = (U8*)" -Isrc/c -Iboot", .count = 15, .cap = CAP_LIT}
                : Str_concat(&(Str){.c_str = (U8*)" -include ", .count = 10, .cap = CAP_LIT}, fwd_path);
            Str *obj_cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
                &(Str){.c_str = (U8*)"cc -Wall -Wextra -Werror -I", .count = 27, .cap = CAP_LIT}, ext_dir),
                fwd_flag),
                ifl),
                &(Str){.c_str = (U8*)" -c ", .count = 4, .cap = CAP_LIT}), file),
                Str_concat(&(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}, user_obj));

            int obj_result = system((const char *)obj_cmd->c_str);
            if (obj_result != 0) {
                fprintf(stderr, "error: link_c compilation failed for %s\n", file->c_str);
                return 1;
            }
            all_objs = Str_concat(Str_concat(all_objs, &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), user_obj);
        }
        user_part = all_objs;
    }

    Str *cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
        &(Str){.c_str = (U8*)"cc -Wall -Wextra -Werror -g -rdynamic -Wl,--allow-multiple-definition -I", .count = 72, .cap = CAP_LIT}, ext_dir),
        &(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}), bin_path),
        &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), c_path),
        &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), Str_concat(Str_concat(ext_c_path, user_part), lf));

    int result = system((const char *)cmd->c_str);

    if (result != 0) {
        fprintf(stderr, "error: C compilation failed\n");
        return 1;
    }
    return 0;
}
