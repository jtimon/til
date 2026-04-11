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





void reset_current_fdef(void) { current_fdef = NULL; }

// Collect unique array/vec builtin type names from AST
// CollectionInfo defined in builder.til


// Collect unique dyn_call method literals from AST
// DynCallInfo defined in builder.til

// is_dyn_call_name: moved to builder.til

// find_struct_body: moved to builder.til

// find_callee_fdef: moved to builder.til

// --- Emitter helpers ---



// is_stack_local: moved to builder.til

// is_value_global: moved to builder.til

// is_ref_local: moved to builder.til


// use_dot_access: moved to builder.til


// Block-scoped emit_body: clone stack_locals/ref_locals before
// entering a block, restore after. Inner declarations stay local to the block.

// Scan function body to find variables whose address might escape via ref.
// A variable is unsafe to hoist if:
// - It appears in a ref declaration RHS: "ref y : T = x"
// - It's passed as arg to a ref-returning function
// Resolve the callee name from an fcall's first child

// fcall_fn_sig: moved to builder.til





// Check if callee's i-th parameter is shallow (for call site emission)


// Get the C value type for an fcall's return value

// callee_returns_shallow: moved to builder.til

// callee_returns_dynamic: moved to builder.til

// fcall_is_shallow_return: moved to builder.til

// fcall_returns_dynamic: moved to builder.til

// callee_param_is_shallow: moved to builder.til

// callee_param_is_usize: moved to builder.til

// callee_param_is_own: moved to builder.til




// --- Top-level emission ---


// is_exported_top_level_global: moved to builder.til

// Topo-sort and emit struct/enum definitions from a single program.
// emitted set carries over between calls to handle cross-program deps.
// Derive basename from absolute path: "/abs/path/to/str.til" -> "str"

// Populate struct_bodies/func_defs maps and init auxiliary sets
void build_register_lookups(Expr *, Expr *);
// Populate funcsig_names set from AST
void build_register_funcsig_names(Expr *, Expr *);
// Emit top-level global initializers (shared by test/lib/script main)
void emit_global_inits(File *);

I32 build(Expr *core_program, Expr *program, Mode *mode, Bool run_tests, Str *path, Str *c_output_path) {
    codegen_core_program = core_program;
    codegen_program = program;
    (void)path;
    Bool is_lib = mode && mode->is_library;

    build_register_lookups(core_program, program);
    build_register_funcsig_names(core_program, program);
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
            Set emitted_mh; { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); emitted_mh = *_sp; free(_sp); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U8", .count = 2, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I16", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"F32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}); Set_add(&emitted_mh, _p); }
            if (core_program) topo_emit_struct_enum_defs(hf, core_program, &emitted_mh);
            topo_emit_struct_enum_defs(hf, program, &emitted_mh);
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
                    Str void_s = {.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT};
                    Str *ret = &void_s;
                    if (fdef->data.data.FuncDef.return_type.count > 0) {
                        ret = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                            ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                            : type_name_to_c(&fdef->data.data.FuncDef.return_type);
                    }
                    File_write_str(f, ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, "(");
                    emit_param_list(f, fdef, 1);
                    EMIT(f, ");\n");
                    if (ret != &void_s) Str_delete(ret, &(Bool){1});
                }
            } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                Expr *func_def = Expr_child(stmt, &(USize){(USize)(0)});
                FuncType fft = func_def->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) continue;
                Str *name = &stmt->data.data.Decl.name;
                Bool is_main = mode && mode->needs_main && (name->count == 4 && memcmp(name->c_str, "main", 4) == 0);
                if (is_main) continue;
                Str void_s2 = {.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT};
                Str *ret = &void_s2;
                if (func_def->data.data.FuncDef.return_type.count > 0)
                    ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                        ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                        : type_name_to_c(&func_def->data.data.FuncDef.return_type);
                File_write_str(f, ret); EMIT(f, " "); { Str *_fc = func_to_c(name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
                emit_param_list(f, func_def, 1);
                EMIT(f, ");\n");
                if (ret != &void_s2) Str_delete(ret, &(Bool){1});
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
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); has_methods = *_vp; free(_vp); }
        if (core_program) collect_dyn_has_methods(core_program, &has_methods);
        collect_dyn_has_methods(program, &has_methods);
        for (U32 m = 0; m < has_methods.count; m++) {
            Str *method = Vec_get(&has_methods, &(USize){(USize)(m)});
            EMIT(f, (const char *)dyn_has_ret); EMIT(f, " dyn_has_"); EMIT(f, (const char *)method->c_str); EMIT(f, "(Str *type_name);\n");
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
        { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); ref_globals = *_sp; free(_sp); }
        has_ref_globals = 1;
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
                if (DECL_IS_REF(stmt->data.data.Decl)) {
                    File_write_str(f, ctype); Str_delete(ctype, &(Bool){1}); EMIT(f, " *"); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
                    { Str *_p = malloc(sizeof(Str)); *_p = (Str){stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.count, CAP_VIEW}; Set_add(&ref_globals, _p); }
                } else {
                    File_write_str(f, ctype); Str_delete(ctype, &(Bool){1}); EMIT(f, " "); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
                    { Str *_p = malloc(sizeof(Str)); *_p = (Str){stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.count, CAP_VIEW}; Set_add(&script_globals, _p); }
                }
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
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); has_methods = *_vp; free(_vp); }
        if (core_program) collect_dyn_has_methods(core_program, &has_methods);
        collect_dyn_has_methods(program, &has_methods);
        for (U32 m = 0; m < has_methods.count; m++) {
            Str *method = Vec_get(&has_methods, &(USize){(USize)(m)});
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
        emit_global_inits(f);
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
        emit_global_inits(f);
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

// --- Extracted build() helpers ---

void build_register_lookups(Expr *core_program, Expr *program) {
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); struct_bodies = *_mp; free(_mp); }
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); func_defs = *_mp; free(_mp); }
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); stack_locals = *_sp; free(_sp); }
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); stack_local_types = *_mp; free(_mp); }
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
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (!field->data.data.Decl.is_namespace) continue;
                    if (field->children.count == 0 || Expr_child(field, &(USize){(USize)(0)})->data.tag != NodeType_TAG_FuncDef) continue;
                    Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                    char flat[256];
                    snprintf(flat, sizeof(flat), "%s_%s", sname->c_str, field->data.data.Decl.name.c_str);
                    Str *key = Str_clone(&(Str){.c_str = (U8*)(flat), .count = (U64)strlen((const char*)(flat)), .cap = CAP_VIEW});
                    { Str *_k = malloc(sizeof(Str)); *_k = *key; void *_v = malloc(sizeof(fdef)); memcpy(_v, &fdef, sizeof(fdef)); Map_set(&func_defs, _k, _v); }
                    free(key);
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
}

void build_register_funcsig_names(Expr *core_program, Expr *program) {
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
}

void emit_global_inits(File *f) {
    if (!has_script_globals) return;
    { Expr *_progs_gi[2] = { codegen_core_program, codegen_program };
    for (int _pgi = 0; _pgi < 2; _pgi++) {
        if (!_progs_gi[_pgi]) continue;
        for (U32 i = 0; i < _progs_gi[_pgi]->children.count; i++) {
            Expr *gs = Expr_child(_progs_gi[_pgi], &(USize){(USize)(i)});
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

// --- Header emission helpers (shared by build_header and build_forward_header) ---

// Emit struct/enum forward declarations
// compile_lib: moved to builder.til

// compile_c: moved to builder.til
