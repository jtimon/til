#include "../../boot/modes.h"
#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PARAM_IS_OWN(p) ((p)->own_type.tag == OwnType_TAG_Own)
#define DECL_IS_OWN(d) ((d).own_type.tag == OwnType_TAG_Own)
#define DECL_IS_REF(d) ((d).own_type.tag == OwnType_TAG_Ref)
#define DECL_IS_SHALLOW(d) ((d).own_type.tag == OwnType_TAG_Shallow)

void ffi_init_scan_program(Expr *program);

#define ENUM_PAYLOAD_OFFSET ((I32)sizeof(I64))

// Deep-clone a StructInstance: walks struct_def fields for Str, own, enum, inline structs.
// Called from StructInstance.clone in til (ext_func).



// values_equal: dead code, deleted

// --- Eval ---



Value eval_call(Scope *scope, Expr *e) {
    // children[0] = callee ident or field access, children[1..] = args
    Expr *callee_expr = Expr_child(e, &(USize){(USize)(0)});

    // Namespace method call: Struct.method(args)
    if (callee_expr->data.tag == NodeType_TAG_FieldAccess) {
        Value fn_val = eval_expr(scope,callee_expr);
        if (fn_val.tag != Value_TAG_Func) {
            Expr_error(e, &(Str){.c_str = (U8*)"namespace field is not a function", .count = 37, .cap = CAP_LIT});
            exit(1);
        }
        Expr *func_def = (Expr*)fn_val.data.Func;
        // FuncPtr field: stored function may be ext_func from another type.
        // Find the real flat name by reverse-looking-up the Expr* in ns_fields.
        if (callee_expr->til_type.tag == TilType_TAG_FuncPtr) {
            FuncType fp_fft = func_def->data.data.FuncDef.func_type;
            if (fp_fft.tag == FuncType_TAG_ExtFunc || fp_fft.tag == FuncType_TAG_ExtProc) {
                // Search ns_fields for the entry whose Value.func matches func_def
                for (U32 ki = 0; ki < ns_fields.count; ki++) {
                    Str *qn = (Str *)((char *)ns_fields.key_data + ki * ns_fields.key_size);
                    Value *nsv = (Value *)((char *)ns_fields.val_data + ki * ns_fields.val_size);
                    if (nsv->tag == Value_TAG_Func && nsv->data.Func == func_def) {
                        // qn is "Type.method" — build flat name "Type_method"
                        char fp_flat_buf[256];
                        memcpy(fp_flat_buf, qn->c_str, qn->count);
                        fp_flat_buf[qn->count] = '\0';
                        for (U64 fi = 0; fi < qn->count; fi++)
                            if (fp_flat_buf[fi] == '.') fp_flat_buf[fi] = '_';
                        Str fp_flat = {.c_str = (U8 *)fp_flat_buf, .count = qn->count};
                        Expr orig_callee = *Expr_child(e, &(USize){(USize)(0)});
                        Expr flat_ident = orig_callee;
                        flat_ident.data.tag = NodeType_TAG_Ident;
                        flat_ident.data.data.Ident = fp_flat;
                        memcpy(Vec_get(&e->children, &(USize){(USize)(0)}), &flat_ident, sizeof(Expr));
                        Value result = eval_call(scope, e);
                        memcpy(Vec_get(&e->children, &(USize){(USize)(0)}), &orig_callee, sizeof(Expr));
                        return result;
                    }
                }
            }
            // Non-ext FuncPtr: fall through to regular func body call below
        }
        // Direct ext_func namespace method — dispatch by flat name
        FuncType fft = func_def->data.data.FuncDef.func_type;
        if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) {
            // Enum ext methods — delegated to dispatch.c
            Str *parent_sname = &Expr_child(callee_expr, &(USize){(USize)(0)})->struct_name;
            if (parent_sname) {
                Cell *tc = scope_get(scope, parent_sname);
                if (tc && tc->val.tag == Value_TAG_Func && ((Expr*)tc->val.data.Func)->data.tag == NodeType_TAG_EnumDef) {
                    Value eresult;
                    if (enum_method_dispatch(&callee_expr->data.data.Ident, scope,
                            ((Expr*)tc->val.data.Func), parent_sname, e, &eresult)) {
                        // Null cells of own-arg idents
                        for (U32 i = 1; i < e->children.count; i++) {
                            if (Expr_child(e, &(USize){(USize)(i)})->data.tag == NodeType_TAG_Ident && Expr_child(e, &(USize){(USize)(i)})->is_own_arg) {
                                Cell *c = scope_get(scope, &Expr_child(e, &(USize){(USize)(i)})->data.data.Ident);
                                if (c) c->val = val_none();
                            }
                        }
                        return eresult;
                    }
                }
            }
            char flat_name_buf[256];
            Str *sn = &Expr_child(callee_expr, &(USize){(USize)(0)})->struct_name;
            Str *fn = &callee_expr->data.data.Ident;
            U64 flen = sn->count + 1 + fn->count;
            memcpy(flat_name_buf, sn->c_str, sn->count);
            flat_name_buf[sn->count] = '_';
            memcpy(flat_name_buf + sn->count + 1, fn->c_str, fn->count);
            flat_name_buf[flen] = '\0';
            Str flat_str = {.c_str = (U8 *)flat_name_buf, .count = flen};
            Expr orig_callee_val = *Expr_child(e, &(USize){(USize)(0)});
            Expr flat_ident = orig_callee_val;
            flat_ident.data.tag = NodeType_TAG_Ident;
            flat_ident.data.data.Ident = flat_str;
            memcpy(Vec_get(&e->children, &(USize){(USize)(0)}), &flat_ident, sizeof(Expr));
            Value result = eval_call(scope, e);
            memcpy(Vec_get(&e->children, &(USize){(USize)(0)}), &orig_callee_val, sizeof(Expr));
            return result;
        }
        Expr *body = Expr_child(func_def, &(USize){(USize)(0)});

        if (guard_own_param_skip(scope, e, func_def)) return val_none();

        Scope *call_scope = scope_new(scope);
        for (U32 i = 0; i < func_def->data.data.FuncDef.nparam; i++) {
            Param *_ipi = (Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)});
            Expr *arg_expr = Expr_child(e, &(USize){(USize)(i + 1)});
            if (arg_expr->data.tag == NodeType_TAG_Ident) {
                Cell *arg_cell = scope_get(scope, &arg_expr->data.data.Ident);
                if (arg_cell->val.tag == Value_TAG_Ptr && _ipi->ptype.count > 0) {
                    Value arg; { Value *_r = reinterpret_ptr_value(&arg_cell->val, &_ipi->ptype, scope); arg = *_r; free(_r); }
                    { Value *_w = widen_numeric(&arg, &_ipi->ptype); arg = *_w; free(_w); }
                    scope_set_owned(call_scope, &_ipi->name, &arg);
                } else if (needs_widen(&arg_cell->val, &_ipi->ptype)) {
                    Value *_cv = Value_clone(&arg_cell->val); Value arg = *_cv; free(_cv);
                    { Value *_w = widen_numeric(&arg, &_ipi->ptype); arg = *_w; free(_w); }
                    scope_set_owned(call_scope, &_ipi->name, &arg);
                } else {
                    scope_set_borrowed(call_scope, &_ipi->name, arg_cell);
                }
            } else {
                Value arg = eval_expr(scope,arg_expr);
                if (arg.tag == Value_TAG_Ptr && _ipi->ptype.count > 0) {
                    { Value *_r = reinterpret_ptr_value(&arg, &_ipi->ptype, scope); arg = *_r; free(_r); }
                }
                { Value *_w = widen_numeric(&arg, &_ipi->ptype); arg = *_w; free(_w); }
                scope_set_owned(call_scope, &_ipi->name, &arg);
            }
        }
        has_return = 0;
        eval_body(call_scope, body);
        // Clone return value before freeing scope -- return_value may
        // alias data in scope cells (eval_expr returns cell->val directly)
        Value result = val_none();
        if (has_return) {
            Value *_cv = Value_clone(&return_value); result = *_cv; free(_cv);
            has_return = 0;
        }
        scope_free(call_scope);
        return result;
    }

    Str *name = &callee_expr->data.data.Ident;

    // Ext function dispatch
    Value ext_result;
    if (ext_function_dispatch(name, scope, e, &ext_result)) {
        // Null cells of own-arg idents (ext dispatch evaluates by value, not borrowed cell)
        for (U32 i = 1; i < e->children.count; i++) {
            if (Expr_child(e, &(USize){(USize)(i)})->data.tag == NodeType_TAG_Ident && Expr_child(e, &(USize){(USize)(i)})->is_own_arg) {
                Cell *c = scope_get(scope, &Expr_child(e, &(USize){(USize)(i)})->data.data.Ident);
                if (c) c->val = val_none();
            }
        }
        return ext_result;
    }

    // User-defined function or struct instantiation
    Cell *fn_cell = scope_get(scope, name);
    if (!fn_cell) {
        char buf[128];
        snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
        Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
        exit(1);
    }

    // Struct instantiation — typer already desugared named args to positional
    if (fn_cell->val.tag == Value_TAG_Func && ((Expr*)fn_cell->val.data.Func)->data.tag == NodeType_TAG_StructDef) {
        Expr *sdef = ((Expr*)fn_cell->val.data.Func);
        Expr *body = Expr_child(sdef, &(USize){(USize)(0)});

        StructInstance *inst = malloc(sizeof(StructInstance));
        // Use typer's resolved struct_name (handles aliases like Point2 → Point)
        inst->struct_name = (e->struct_name.count > 0) ? &e->struct_name : name;
        inst->struct_def = sdef;
        inst->borrowed = 0;
        inst->data = calloc(1, sdef->data.data.StructDef.total_struct_size);
        I32 arg_idx = 1;
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *field = Expr_child(body, &(USize){(USize)(i)});
            if (field->data.data.Decl.is_namespace) continue;
            Expr *arg = Expr_child(e, &(USize){(USize)(arg_idx++)});
            Value val;
            if (arg->data.tag == NodeType_TAG_Ident) {
                Cell *src = scope_get(scope, &arg->data.data.Ident);
                val = src->val;
                if (arg->is_own_arg && val.tag != Value_TAG_Func)
                    src->val = val_none();
            } else {
                val = eval_expr(scope, arg);
            }
            write_field(inst, field, &val);
        }
        Value result;
        result.tag = Value_TAG_Struct;
        result.data.Struct = *inst;
        free(inst);
        return result;
    }

    if (fn_cell->val.tag != Value_TAG_Func) {
        char buf[128];
        snprintf(buf, sizeof(buf), "'%s' is not a function", name->c_str);
        Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
        exit(1);
    }

    Expr *func_def = ((Expr*)fn_cell->val.data.Func);
    Expr *body = Expr_child(func_def, &(USize){(USize)(0)});

    // Guard: skip call if first 'own' param is val_none, borrowed struct, or Value_TAG_Ptr
    if (func_def->data.data.FuncDef.nparam > 0 &&
        func_def->data.data.FuncDef.params.count > 0 &&
        PARAM_IS_OWN(((Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(0)}))) &&
        e->children.count > 1 && Expr_child(e, &(USize){(USize)(1)})->data.tag == NodeType_TAG_Ident) {
        Cell *fc = scope_get(scope, &Expr_child(e, &(USize){(USize)(1)})->data.data.Ident);
        if (fc && fc->val.tag == Value_TAG_None) return val_none();
        if (fc && fc->val.tag == Value_TAG_Struct && fc->val.data.Struct.borrowed) {
            fc->val = val_none();
            return val_none();
        }
        if (fc && fc->val.tag == Value_TAG_Ptr) {
            fc->val = val_none();
            return val_none();
        }
    }

    Scope *call_scope = scope_new(scope);
    // Bind arguments to parameters (borrowed refs for idents, owned for expressions)
    U32 nparam = func_def->data.data.FuncDef.nparam;
    for (U32 i = 0; i < nparam; i++) {
        Expr *arg_expr = Expr_child(e, &(USize){(USize)(i + 1)});
        Param *_rpi = (Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)});
        if (arg_expr->data.tag == NodeType_TAG_Ident) {
            Cell *arg_cell = scope_get(scope, &arg_expr->data.data.Ident);
            if (needs_widen(&arg_cell->val, &_rpi->ptype)) {
                Value *_cv = Value_clone(&arg_cell->val); Value arg = *_cv; free(_cv);
                { Value *_w = widen_numeric(&arg, &_rpi->ptype); arg = *_w; free(_w); }
                scope_set_owned(call_scope, &_rpi->name, &arg);
            } else {
                scope_set_borrowed(call_scope, &_rpi->name, arg_cell);
            }
        } else {
            Value arg = eval_expr(scope, arg_expr);
            { Value *_w = widen_numeric(&arg, &_rpi->ptype); arg = *_w; free(_w); }
            scope_set_owned(call_scope, &_rpi->name, &arg);
        }
    }

    has_return = 0;
    eval_body(call_scope, body);
    Value result = val_none();
    if (has_return) {
        Value *_cv = Value_clone(&return_value); result = *_cv; free(_cv);
        has_return = 0;
    }
    scope_free(call_scope);
    return result;
}

/* eval_expr: moved to interpreter.til
#if 0
    switch (e->data.tag) {
    case NodeType_TAG_LiteralStr: {
        // Process C escape sequences (\n, \t, \\, \", \0)
        const char *raw = (const char *)e->data.data.LiteralStr.c_str;
        U64 raw_len = e->data.data.LiteralStr.count;
        char *buf = malloc(raw_len + 1);
        U64 j = 0;
        for (U64 i = 0; i < raw_len; i++) {
            if (raw[i] == '\\' && i + 1 < raw_len) {
                switch (raw[i + 1]) {
                case 'n':  buf[j++] = '\n'; i++; break;
                case 't':  buf[j++] = '\t'; i++; break;
                case '\\': buf[j++] = '\\'; i++; break;
                case '"':  buf[j++] = '"';  i++; break;
                case '0':  buf[j++] = '\0'; i++; break;
                default:   buf[j++] = raw[i]; break;
                }
            } else {
                buf[j++] = raw[i];
            }
        }
        buf[j] = '\0';
        Value v = make_str_value(buf, j);
        free(buf);
        return v;
    }
    case NodeType_TAG_LiteralNum:
        if (e->til_type.tag == TilType_TAG_U8)
            return val_u8(atoll((const char *)e->data.data.LiteralNum.c_str));
        if (e->til_type.tag == TilType_TAG_U32)
            return val_u32(atoll((const char *)e->data.data.LiteralNum.c_str));
        if (e->til_type.tag == TilType_TAG_U64)
            return val_u64((U64)strtoull((const char *)e->data.data.LiteralNum.c_str, NULL, 10));
        if (e->til_type.tag == TilType_TAG_I16)
            return val_i16(atoll((const char *)e->data.data.LiteralNum.c_str));
        if (e->til_type.tag == TilType_TAG_I32)
            return val_i32(atoll((const char *)e->data.data.LiteralNum.c_str));
        if (e->til_type.tag == TilType_TAG_F32)
            return val_f32((F32)atof((const char *)e->data.data.LiteralNum.c_str));
        return val_i64(atoll((const char *)e->data.data.LiteralNum.c_str));
    case NodeType_TAG_LiteralBool:
        return val_bool(e->data.data.LiteralBool);
    case NodeType_TAG_LiteralNull:
        return (Value){.tag = Value_TAG_Ptr, .data.Ptr = NULL};
    case NodeType_TAG_Ident: {
        Cell *cell = scope_get(scope, &e->data.data.Ident);
        if (!cell) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined variable '%s'", e->data.data.Ident.c_str);
            Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
            exit(1);
        }
        return cell->val;
    }
    case NodeType_TAG_FCall:
        return eval_call(scope, e);
    case NodeType_TAG_FuncDef:
        return (Value){.tag = Value_TAG_Func, .data.Func = (void*)e};
    case NodeType_TAG_StructDef:
    case NodeType_TAG_EnumDef:
        return (Value){.tag = Value_TAG_Func, .data.Func = (void*)e};
    case NodeType_TAG_FieldAccess: {
        Value obj = eval_expr(scope,Expr_child(e, &(USize){(USize)(0)}));
        Str *fname = &e->data.data.FieldAccess;
        if (interp_fa_is_ns(scope, e)) {
            Str *sname = obj.tag == Value_TAG_Struct
                ? obj.data.Struct.struct_name : &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
            Value *nsv = ns_get(sname, fname);
            if (nsv) {
                // Fresh copy of scalar values (prevents alias to namespace map)
                if (nsv->tag == Value_TAG_Int) return val_i64(nsv->data.Int);
                if (nsv->tag == Value_TAG_Int32) return val_i32(nsv->data.Int32);
                // Auto-call enum variant constructors used bare (without parens)
                // Check til_type == Enum to distinguish bare refs from FCall callees
                if (nsv->tag == Value_TAG_Func && nsv->data.Func &&
                    ((Expr*)nsv->data.Func)->data.tag == NodeType_TAG_FuncDef &&
                    ((Expr*)nsv->data.Func)->data.data.FuncDef.func_type.tag == FuncType_TAG_ExtFunc &&
                    e->til_type.tag == TilType_TAG_Enum) {
                    Cell *tc = scope_get(scope, sname);
                    if (tc && tc->val.tag == Value_TAG_Func && ((Expr*)tc->val.data.Func)->data.tag == NodeType_TAG_EnumDef) {
                        I32 tag = *enum_variant_tag(((Expr*)tc->val.data.Func), fname);
                        if (tag >= 0) {
                            Expr *edef = (Expr*)tc->val.data.Func;
                            if (enum_has_payloads(edef))
                                return val_enum_flat(sname, edef, tag, NULL, 0);
                            else
                                return val_i32(tag);
                        }
                    }
                }
                return *nsv;
            }
            char buf[128];
            snprintf(buf, sizeof(buf), "no namespace field '%s'", fname->c_str);
            Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
            exit(1);
        }
        if (obj.tag == Value_TAG_Ptr) {
            Expr *obj_expr = Expr_child(e, &(USize){(USize)(0)});
            if (obj_expr->struct_name.count > 0) {
                Cell *tc = scope_get(scope, &obj_expr->struct_name);
                if (tc && tc->val.tag == Value_TAG_Func && ((Expr*)tc->val.data.Func)->data.tag == NodeType_TAG_StructDef) {
                    void *saved_ptr = obj.data.Ptr;
                    obj.tag = Value_TAG_Struct;
                    obj.data.Struct.struct_name = &obj_expr->struct_name;
                    obj.data.Struct.struct_def = ((Expr*)tc->val.data.Func);
                    obj.data.Struct.data = saved_ptr;
                    obj.data.Struct.borrowed = 1;
                }
            }
        }
        if (obj.tag != Value_TAG_Struct) {
            Expr_error(e, &(Str){.c_str = (U8*)"field access on non-struct", .count = 27, .cap = CAP_LIT});
            exit(1);
        }
        Expr *fdecl = find_field_decl(obj.data.Struct.struct_def, fname);
        if (!fdecl) {
            char buf[128];
            snprintf(buf, sizeof(buf), "no field '%s'", fname->c_str);
            Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
            exit(1);
        }
        return read_field(&obj.data.Struct, fdecl);
    }
    default:
        char buf[128];
        snprintf(buf, sizeof(buf), "cannot evaluate node type %d as expression", e->data.tag);
        Expr_lang_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
        exit(1);
    }
#endif
*/



// parse_cli_arg: moved to interpreter.til




I32 interpret(Expr *core_program, Expr *program, Mode *mode, Bool run_tests, Str *path, Str *user_c_path, Str *ext_c_path, Str *link_flags, Vec *user_argv, Str *fwd_path) {
    if (user_c_path && user_c_path->count == 0) user_c_path = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
    U32 user_argc = user_argv ? (U32)user_argv->count : 0;
    // Initialize FFI: load user .c library (if provided) and auto-discover C functions
    I32 ffi_rc = ffi_init(program, fwd_path, user_c_path, ext_c_path, link_flags);
    if (ffi_rc != 0) return ffi_rc;
    if (core_program) ffi_init_scan_program(core_program);

    Scope *global = scope_new(NULL);

    // Pre-register all top-level func/proc/struct definitions for forward references
    { Expr *_progs_pr[2] = { core_program, program };
    for (int _ppr = 0; _ppr < 2; _ppr++) {
        if (!_progs_pr[_ppr]) continue;
        for (U32 i = 0; i < _progs_pr[_ppr]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_pr[_ppr], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Value val = {.tag = Value_TAG_Func, .data.Func = (void*)Expr_child(stmt, &(USize){(USize)(0)})};
                scope_set_owned(global, (&stmt->data.data.Decl.name), &val);
            }
        }
    }}

    // Pre-register type aliases (Name := ExistingType where RHS is Ident and is a type)
    { Expr *_progs_ta[2] = { core_program, program };
    for (int _pta = 0; _pta < 2; _pta++) {
        if (!_progs_ta[_pta]) continue;
        for (U32 i = 0; i < _progs_ta[_pta]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_ta[_pta], &(USize){(USize)(i)});
            if (stmt->data.tag != NodeType_TAG_Decl) continue;
            if (stmt->til_type.tag != TilType_TAG_None) continue; // type defs have None
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            if (rhs->data.tag != NodeType_TAG_Ident) continue;
            Cell *src = scope_get(global, &rhs->data.data.Ident);
            if (src && src->val.tag == Value_TAG_Func &&
                (((Expr*)src->val.data.Func)->data.tag == NodeType_TAG_StructDef ||
                 ((Expr*)src->val.data.Func)->data.tag == NodeType_TAG_EnumDef)) {
                Value val = {.tag = Value_TAG_Func, .data.Func = src->val.data.Func};
                scope_set_owned(global, &stmt->data.data.Decl.name, &val);
            }
        }
    }}

    // Initialize namespace fields for all structs
    if (core_program) interpreter_init_ns(global, core_program);
    interpreter_init_ns(global, program);

    // Copy namespace entries for type aliases
    { Expr *_progs_ac[2] = { core_program, program };
    for (int _pac = 0; _pac < 2; _pac++) {
        if (!_progs_ac[_pac]) continue;
        for (U32 i = 0; i < _progs_ac[_pac]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_ac[_pac], &(USize){(USize)(i)});
            if (stmt->data.tag != NodeType_TAG_Decl) continue;
            if (stmt->til_type.tag != TilType_TAG_None) continue;
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            if (rhs->data.tag != NodeType_TAG_Ident) continue;
            Str *alias_name = &stmt->data.data.Decl.name;
            Str *target_name = &rhs->data.data.Ident;
            Cell *tc = scope_get(global, target_name);
            if (!tc || tc->val.tag != Value_TAG_Func) continue;
            Expr *sdef = ((Expr*)tc->val.data.Func);
            if (sdef->data.tag != NodeType_TAG_StructDef && sdef->data.tag != NodeType_TAG_EnumDef) continue;
            Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace) {
                    Value *v = ns_get(target_name, &field->data.data.Decl.name);
                    if (v) ns_set(alias_name, &field->data.data.Decl.name, *v);
                }
            }
        }
    }}

    // Evaluate top-level declarations
    if (core_program) eval_body(global, core_program);
    eval_body(global, program);

    // Run test functions if requested
    if (run_tests) {
        I32 test_count = 0, pass_count = 0;
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
            if (stmt->data.tag != NodeType_TAG_Decl) continue;
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            if (rhs->data.tag != NodeType_TAG_FuncDef) continue;
            if (rhs->data.data.FuncDef.func_type.tag != FuncType_TAG_Test) continue;
            Str *tname = &stmt->data.data.Decl.name;
            test_count++;
            Scope *test_scope = scope_new(global);
            eval_body(test_scope, Expr_child(rhs, &(USize){(USize)(0)}));
            if (has_return) {
                Value *_cv = Value_clone(&return_value); return_value = *_cv; free(_cv);
            }
            scope_free(test_scope);
            pass_count++;
            fprintf(stderr, "  pass: %s\n", tname->c_str);
        }
        if (test_count == 0) {
            fprintf(stderr, "no tests found\n");
        } else {
            fprintf(stderr, "%d/%d tests passed\n", pass_count, test_count);
        }
        scope_free(global);
        ffi_cleanup();
        return (pass_count == test_count) ? 0 : 1;
    }

    // In needs_main mode, call main()
    if (mode && mode->needs_main) {
        Str main_name = {.c_str = (U8 *)"main", .count = 4};
        Cell *main_cell = scope_get(global, &main_name);
        if (!main_cell || main_cell->val.tag != Value_TAG_Func) {
            fprintf(stderr, "%s: error: this mode requires a 'main' proc\n", path->c_str);
            scope_free(global);
            return 1;
        }
        Expr *func_def = (Expr*)main_cell->val.data.Func;
        U32 nparam = func_def->data.data.FuncDef.nparam;
        I32 vi = func_def->data.data.FuncDef.variadic_index;
        Expr *body = Expr_child(func_def, &(USize){(USize)(0)});
        Scope *main_scope = scope_new(global);

        // Bind CLI args to main params
        if (nparam > 0) {
            U32 fixed = (vi >= 0) ? nparam - 1 : nparam;
            if (vi >= 0) {
                // Variadic: need at least 'fixed' args
                if (user_argc < fixed) {
                    fprintf(stderr, "error: main expects at least %u argument(s), got %u\n", fixed, user_argc);
                    scope_free(main_scope);
                    scope_free(global);
                    return 1;
                }
            } else {
                if (user_argc != nparam) {
                    fprintf(stderr, "error: main expects %u argument(s), got %u\n", nparam, user_argc);
                    scope_free(main_scope);
                    scope_free(global);
                    return 1;
                }
            }
            I32 argi = 0;
            for (U32 i = 0; i < nparam; i++) {
                if ((I32)i == vi) {
                    U32 va_count = user_argc - fixed;
                    Param *_mpi = (Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)});
                    Value arr = build_argv_array(user_argv, argi, va_count, &((Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(vi)}))->ptype);
                    scope_set_owned(main_scope, &_mpi->name, &arr);
                    argi += va_count;
                } else {
                    Param *_mpi = (Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)});
                    Str *arg_s = (Str *)Vec_get(user_argv, &(USize){(USize)argi});
                    Value v = parse_cli_arg(arg_s, &_mpi->ptype);
                    scope_set_owned(main_scope, &_mpi->name, &v);
                    argi++;
                }
            }
        } else if (user_argc > 0) {
            fprintf(stderr, "error: main expects no arguments, got %u\n", user_argc);
            scope_free(main_scope);
            scope_free(global);
            return 1;
        }

        eval_body(main_scope, body);
        scope_free(main_scope);
    }

    scope_free(global);
    ffi_cleanup();
    ns_inited = 0;
    return 0;
}
