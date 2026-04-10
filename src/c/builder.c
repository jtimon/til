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

Expr *find_struct_body(Str *name) {
    if (!Map_has(&struct_bodies, name)) return NULL;
    Expr **p = Map_get(&struct_bodies, name);
    return *p;
}


Expr *find_callee_fdef(Str *name) {
    if (!Map_has(&func_defs, name)) return NULL;
    Expr **p = Map_get(&func_defs, name);
    return *p;
}

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


I32 build_forward_header(Expr *core_program, Expr *program, Str *fwd_path);
static void emit_header_forward_decls(File *f, Expr *core_program, Expr *program);
static void emit_header_global_decls(File *f, Expr *core_program, Expr *program);
// is_exported_top_level_global: moved to builder.til

// Topo-sort and emit struct/enum definitions from a single program.
// emitted set carries over between calls to handle cross-program deps.
static void topo_emit_struct_enum_defs(File *f, Expr *prog, Set *emitted) {
    Vec to_emit; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(U32)}); to_emit = *_vp; free(_vp); }
    for (U32 i = 0; i < prog->children.count; i++) {
        Expr *stmt = Expr_child(prog, &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl &&
            (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
             Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
            { U32 *_p = malloc(sizeof(U32)); *_p = i; Vec_push(&to_emit, _p); }
        }
    }
    U32 remaining = to_emit.count;
    Bool *done = calloc(to_emit.count, sizeof(Bool));
    while (remaining > 0) {
        Bool progress = 0;
        for (U32 ei = 0; ei < to_emit.count; ei++) {
            if (done[ei]) continue;
            U32 idx = *(U32 *)Vec_get(&to_emit, &(USize){(USize)(ei)});
            Expr *stmt = Expr_child(prog, &(USize){(USize)(idx)});
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
                        if (!Set_has(emitted, &Expr_child(field, &(USize){(USize)(0)})->struct_name)) {
                            deps_ok = 0; break;
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
                        if (!Set_has(emitted, &v->data.data.Decl.explicit_type)) {
                            deps_ok = 0; break;
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
            { Str *_p = Str_clone(name); Set_add(emitted, _p); }
            done[ei] = 1;
            remaining--;
            progress = 1;
        }
        if (!progress) {
            // Emit remaining in order (circular deps)
            for (U32 ei = 0; ei < to_emit.count; ei++) {
                if (done[ei]) continue;
                U32 idx = *(U32 *)Vec_get(&to_emit, &(USize){(USize)(ei)});
                Expr *stmt = Expr_child(prog, &(USize){(USize)(idx)});
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
    free(done);
    Vec_delete(&to_emit, &(Bool){0});
}

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
                // Register namespace methods
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
        Set emitted_h; { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); emitted_h = *_sp; free(_sp); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U8", .count = 2, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I16", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"U64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"F32", .count = 3, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        { Str *_p; _p = Str_clone(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}); Set_add(&emitted_h, _p); }
        if (core_program) topo_emit_struct_enum_defs(f, core_program, &emitted_h);
        topo_emit_struct_enum_defs(f, program, &emitted_h);
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
                Str void_h = {.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT};
                Str *ret = &void_h;
                if (fdef->data.data.FuncDef.return_type.count > 0)
                    ret = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef)
                        ? type_name_to_c_value(&fdef->data.data.FuncDef.return_type)
                        : type_name_to_c(&fdef->data.data.FuncDef.return_type);
                File_write_str(f, ret); EMIT(f, " "); EMIT(f, (const char *)sname->c_str); EMIT(f, "_"); EMIT(f, (const char *)field->data.data.Decl.name.c_str); EMIT(f, "(");
                emit_param_list(f, fdef, 1);
                EMIT(f, ");\n");
                if (ret != &void_h) Str_delete(ret, &(Bool){1});
            }
        } else if (stmt->data.tag == NodeType_TAG_Decl && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
            Expr *func_def = Expr_child(stmt, &(USize){(USize)(0)});
            if (func_def->children.count == 0) continue;
            FuncType fft = func_def->data.data.FuncDef.func_type;
            if ((fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) && _is_core_pass_ffd) continue;
            Str void_h2 = {.c_str = (U8 *)"void", .count = 4, .cap = CAP_LIT};
            Str *ret = &void_h2;
            if (func_def->data.data.FuncDef.return_type.count > 0)
                ret = RETURN_IS_SHALLOW(&func_def->data.data.FuncDef)
                    ? type_name_to_c_value(&func_def->data.data.FuncDef.return_type)
                    : type_name_to_c(&func_def->data.data.FuncDef.return_type);
            File_write_str(f, ret); EMIT(f, " "); { Str *_fc = func_to_c(&stmt->data.data.Decl.name); File_write_str(f, _fc); Str_delete(_fc, &(Bool){1}); } EMIT(f, "(");
            emit_param_list(f, func_def, 1);
            EMIT(f, ");\n");
            if (ret != &void_h2) Str_delete(ret, &(Bool){1});
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
        if (DECL_IS_REF(stmt->data.data.Decl)) {
            EMIT(f, "extern "); File_write_str(f, ctype); Str_delete(ctype, &(Bool){1}); EMIT(f, " *"); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
        } else {
            EMIT(f, "extern "); File_write_str(f, ctype); Str_delete(ctype, &(Bool){1}); EMIT(f, " "); EMIT(f, (const char *)stmt->data.data.Decl.name.c_str); EMIT(f, ";\n");
        }
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
