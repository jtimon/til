#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../boot/modes.h"

// Forward declarations (defined in dispatch.c / dispatch.til)
void ffi_init_scan_program(Expr *program);
void ffi_init_struct_defs(Expr *program);




void precomp(Expr *core_program, Expr *program) {
    // 1. Collect macro and pure func names
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); macros = *_sp; free(_sp); }
    { Set *_sp = Set_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}); funcs = *_sp; free(_sp); }
    { Expr *_progs_mc[2] = { core_program, program };
    for (int _pmc = 0; _pmc < 2; _pmc++) {
        if (!_progs_mc[_pmc]) continue;
        for (U32 i = 0; i < _progs_mc[_pmc]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_mc[_pmc], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl && stmt->children.count > 0 && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                FuncType ft = Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
                if (ft.tag == FuncType_TAG_Macro) {
                    Str *_c = Str_clone(&stmt->data.data.Decl.name);
                    { Str *_p = malloc(sizeof(Str)); *_p = *_c; free(_c); Set_add(&macros, _p); }
                } else if (ft.tag == FuncType_TAG_Func) {
                    Str *_c = Str_clone(&stmt->data.data.Decl.name);
                    { Str *_p = malloc(sizeof(Str)); *_p = *_c; free(_c); Set_add(&funcs, _p); }
                }
            }
            // Register namespace funcs from struct/enum bodies
            if (stmt->data.tag == NodeType_TAG_Decl && stmt->children.count > 0 &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Str *sname = &stmt->data.data.Decl.name;
                Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){(USize)(0)});
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(j)});
                    if (field->data.data.Decl.is_namespace &&
                        Expr_child(field, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
                        FuncType ft = Expr_child(field, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
                        if (ft.tag == FuncType_TAG_Func) {
                            Str *prefix = Str_concat(sname, &(Str){.c_str = (U8*)"_", .count = 1, .cap = CAP_LIT});
                            Str *qname = Str_concat(prefix, &field->data.data.Decl.name);
                            Str_delete(prefix, &(Bool){1});
                            { Str *_p = malloc(sizeof(Str)); *_p = *qname; free(qname); Set_add(&funcs, _p); }
                        }
                    }
                }
            }
        }
    }}

    // Nothing to fold?
    if (macros.count == 0 && funcs.count == 0) {
        Set_delete(&macros, &(Bool){0});
        Set_delete(&funcs, &(Bool){0});
        return;
    }

    // 2. Set up interpreter scope (same as interpret() does)
    Scope *global = scope_new(NULL);
    { Expr *_progs_sc[2] = { core_program, program };
    for (int _psc = 0; _psc < 2; _psc++) {
        if (!_progs_sc[_psc]) continue;
        for (U32 i = 0; i < _progs_sc[_psc]->children.count; i++) {
            Expr *stmt = Expr_child(_progs_sc[_psc], &(USize){(USize)(i)});
            if (stmt->data.tag == NodeType_TAG_Decl &&
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                 Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
                Value val = {.tag = Value_TAG_Func, .data.Func = (void*)Expr_child(stmt, &(USize){(USize)(0)})};
                scope_set_owned(global, (&stmt->data.data.Decl.name), &val);
            }
        }
    }}
    if (core_program) interpreter_init_ns(global, core_program);
    interpreter_init_ns(global, program);

    // 2b. Init FFI so ext_func calls (e.g. auto-delete) work during folding
    ffi_init(program, NULL, NULL, NULL, NULL);
    if (core_program) {
        ffi_init_struct_defs(core_program);
        ffi_init_scan_program(core_program);
    }

    // 3. Process the program body (user only)
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Value", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Value)}); known = *_mp; free(_mp); }
    process_body(global, program);

    // Cleanup
    Map_delete(&known, &(Bool){0});
    scope_free(global);
    Set_delete(&macros, &(Bool){0});
    Set_delete(&funcs, &(Bool){0});
}
