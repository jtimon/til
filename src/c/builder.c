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





// reset_current_fdef: moved to builder.til

// Collect unique array/vec builtin type names from AST
// CollectionInfo defined in builder.til


// Collect unique dyn_call method literals from AST
// DynCallInfo defined in builder.til

// is_dyn_call_name: moved to builder.til

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

// Forward declarations for extracted build() sections
void emit_monolithic_header(File *, Expr *, Expr *, Mode *);

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

    emit_monolithic_header(f, core_program, program, mode);
    EMIT(f, "#include \"ext.h\"\n\n");

    emit_ext_func_declarations(f, program);

    // Forward-declare helper functions (implementations after struct defs)
    EMIT(f, "Str *Str_lit(const char *s, unsigned long long len);\n");
    EMIT(f, "void print_single(Str *s);\n");
    EMIT(f, "void print_flush();\n\n");

    emit_all_forward_declarations(f, core_program, program, mode);

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

    emit_global_declarations(f, core_program, program);
    emit_function_bodies(f, core_program, program, mode, is_lib);

    // Emit dyn_call dispatch function bodies
    emit_dyn_call_bodies(f, core_program, program);

    // Emit dyn_fn wrappers + dispatch
    emit_dyn_fn_wrappers(f, core_program, program);

    // Emit dyn_has_method dispatch function bodies
    emit_dyn_has_bodies(f, core_program, program);

    // Emit array/vec builtin helper function bodies
    emit_collection_helpers(f, core_program, program);

    if (run_tests) emit_test_main(f, program);
    if (!run_tests && !is_script && is_lib && has_script_globals) emit_lib_init(f);
    if (!run_tests && is_script && !(mode && mode->needs_main)) emit_script_main(f, program);

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
// compile_lib: moved to builder.til


// --- Extracted build() sections ---

void emit_monolithic_header(File *f, Expr *core_program, Expr *program, Mode *mode) {
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
}


// emit_all_forward_declarations: moved to builder.til

// emit_dyn_fn_wrappers: moved to builder.til






// --- Header emission helpers (shared by build_header and build_forward_header) ---

// Emit struct/enum forward declarations
// compile_lib: moved to builder.til

// compile_c: moved to builder.til
