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
