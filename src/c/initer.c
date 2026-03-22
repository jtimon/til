#include "../../boot/modes.h"
#include "pre70.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type scope implementation ---



// --- Vec helper used by typer ---

void *Vec_take(Vec *v) {
    void *ptr = v->data;
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
    return ptr;
}


TypeBinding *tscope_find(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        if (*Map_has(&cur->bindings, name)) return Map_get(&cur->bindings, name);
    }
    return NULL;
}

TilType tscope_get(TypeScope *s, Str *name) {
    TypeBinding *b = tscope_find(s, name);
    return b ? b->type : (TilType){TilType_TAG_Unknown};
}



Expr *tscope_get_struct(TypeScope *s, Str *name) {
    TypeBinding *b = tscope_find(s, name);
    return b ? b->struct_def : NULL;
}

Bool tscope_is_mut(TypeScope *s, Str *name) {
    TypeBinding *b = tscope_find(s, name);
    return b ? b->is_mut : 0;
}

// --- Resolve type name (simplified, for init phase) ---

static TilType type_from_name_init(Str *name, TypeScope *scope) {
    if ((name->count == 3 && memcmp(name->c_str, "I64", 3) == 0))  return (TilType){TilType_TAG_I64};
    if ((name->count == 2 && memcmp(name->c_str, "U8", 2) == 0))   return (TilType){TilType_TAG_U8};
    if ((name->count == 3 && memcmp(name->c_str, "I16", 3) == 0))  return (TilType){TilType_TAG_I16};
    if ((name->count == 3 && memcmp(name->c_str, "I32", 3) == 0))  return (TilType){TilType_TAG_I32};
    if ((name->count == 3 && memcmp(name->c_str, "U32", 3) == 0))  return (TilType){TilType_TAG_U32};
    if ((name->count == 3 && memcmp(name->c_str, "U64", 3) == 0))  return (TilType){TilType_TAG_U64};
    if ((name->count == 5 && memcmp(name->c_str, "USize", 5) == 0)) return (TilType){TilType_TAG_U32};
    if ((name->count == 3 && memcmp(name->c_str, "Str", 3) == 0))  return (TilType){TilType_TAG_Struct};
    if ((name->count == 4 && memcmp(name->c_str, "Bool", 4) == 0)) return (TilType){TilType_TAG_Bool};
    if ((name->count == 9 && memcmp(name->c_str, "StructDef", 9) == 0))    return (TilType){TilType_TAG_StructDef};
    // FunctionDef: regular struct (like Str), not builtin
    if ((name->count == 7 && memcmp(name->c_str, "Dynamic", 7) == 0))     return (TilType){TilType_TAG_Dynamic};
    if (scope) {
        // Check for builtin aliases first (e.g. USize := U64 has struct_def but type is U64)
        TypeBinding *b = tscope_find(scope, name);
        if (b && b->is_builtin && b->struct_def) return b->type;
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return (sdef->data.tag == ExprData_TAG_EnumDef) ? (TilType){TilType_TAG_Enum} : (TilType){TilType_TAG_Struct};
        // Named FuncSig type (bodyless func/proc)
        if (b && b->func_def && b->func_def->children.count == 0)
            return (TilType){TilType_TAG_FuncPtr};
    }
    return (TilType){TilType_TAG_Unknown};
}

// --- Flat struct layout computation ---

static I32 align_up(I32 offset, I32 align) {
    return (offset + align - 1) & ~(align - 1);
}

// Compute field offsets and total size for a struct def.
// Recursive: if a field is an inline struct, compute its layout first.
static void compute_struct_layout(Expr *struct_def, TypeScope *scope) {
    if (struct_def->total_struct_size > 0) return; // already computed

    Expr *body = Expr_child(struct_def, &(USize){(USize)(0)});
    I32 offset = 0;
    I32 max_align = 1;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = Expr_child(body, &(USize){(USize)(i)});
        if (field->data.tag != ExprData_TAG_Decl || field->data.data.Decl.is_namespace) continue;

        I32 fsz, falign;

        if (field->data.data.Decl.is_own || field->data.data.Decl.is_ref) {
            // own/ref fields are pointers
            fsz = 8; falign = 8;
            // Resolve the pointed-to struct for field access
            Str *ftype = &field->data.data.Decl.explicit_type;
            if (ftype->count == 0 && field->children.count > 0) {
                Expr *def_val = Expr_child(field, &(USize){(USize)(0)});
                if (def_val->data.tag == ExprData_TAG_FCall && def_val->children.count > 0 &&
                    Expr_child(def_val, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident)
                    ftype = &Expr_child(def_val, &(USize){(USize)(0)})->data.data.Ident;
                if (ftype->count > 0) field->data.data.Decl.explicit_type = *ftype;
            }
            if (ftype->count > 0 && !(ftype->count == 3 && memcmp(ftype->c_str, "I64", 3) == 0) && !(ftype->count == 2 && memcmp(ftype->c_str, "U8", 2) == 0) && !(ftype->count == 3 && memcmp(ftype->c_str, "I16", 3) == 0) && !(ftype->count == 3 && memcmp(ftype->c_str, "I32", 3) == 0) && !(ftype->count == 3 && memcmp(ftype->c_str, "U32", 3) == 0) && !(ftype->count == 4 && memcmp(ftype->c_str, "Bool", 4) == 0)) {
                Expr *nested_def = tscope_get_struct(scope, ftype);
                if (nested_def && !nested_def->is_ext) {
                    // Don't recurse — own/ref fields are pointer-sized regardless.
                    // Avoids infinite recursion on indirect cycles (e.g. EnumInstance <-> Value).
                    // Nested type's layout is computed when processed as a top-level definition.
                    field->data.data.Decl.field_struct_def = nested_def;
                }
            }
        } else {
            // Determine type name
            Str _I64_s = {.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT};
            Str _Str_s = {.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
            Str _Bool_s = {.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
            Str *ftype = &field->data.data.Decl.explicit_type;
            if (ftype->count == 0 && field->children.count > 0) {
                Expr *def_val = Expr_child(field, &(USize){(USize)(0)});
                if (def_val->data.tag == ExprData_TAG_LiteralNum) ftype = &_I64_s;
                else if (def_val->data.tag == ExprData_TAG_LiteralStr) ftype = &_Str_s;
                else if (def_val->data.tag == ExprData_TAG_LiteralBool) ftype = &_Bool_s;
                else if (def_val->struct_name.count > 0) ftype = &def_val->struct_name;
                // FCALL default (e.g. Point()): callee ident is the struct name
                else if (def_val->data.tag == ExprData_TAG_FCall && def_val->children.count > 0 &&
                         Expr_child(def_val, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident)
                    ftype = &Expr_child(def_val, &(USize){(USize)(0)})->data.data.Ident;
                // Namespace FCALL default (e.g. Vec.new(...)): struct name is in field access child
                else if (def_val->data.tag == ExprData_TAG_FCall && def_val->children.count > 0 &&
                         Expr_child(def_val, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                         Expr_child(Expr_child(def_val, &(USize){(USize)(0)}), &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident)
                    ftype = &Expr_child(Expr_child(def_val, &(USize){(USize)(0)}), &(USize){(USize)(0)})->data.data.Ident;
                // Namespace field access default (e.g. MyEnum.C): type is the parent ident
                else if (def_val->data.tag == ExprData_TAG_FieldAccess && def_val->children.count > 0 &&
                         Expr_child(def_val, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident)
                    ftype = &Expr_child(def_val, &(USize){(USize)(0)})->data.data.Ident;
                // Store resolved type for interpreter's read_field
                if (ftype->count > 0) field->data.data.Decl.explicit_type = *ftype;
            }
            // Resolve type alias (e.g. USize → U64) for both size computation and interpreter
            {
                TypeBinding *ab = tscope_find(scope, ftype);
                if (ab && ab->is_type_alias && ab->alias_target) {
                    ftype = ab->alias_target;
                    field->data.data.Decl.explicit_type = *ftype;
                }
            }
            if (ftype->count == 0) { fsz = 8; falign = 8; } // fallback
            else if ((ftype->count == 3 && memcmp(ftype->c_str, "I64", 3) == 0))  { fsz = 8; falign = 8; }
            else if ((ftype->count == 2 && memcmp(ftype->c_str, "U8", 2) == 0))   { fsz = 1; falign = 1; }
            else if ((ftype->count == 3 && memcmp(ftype->c_str, "I16", 3) == 0))  { fsz = 2; falign = 2; }
            else if ((ftype->count == 3 && memcmp(ftype->c_str, "I32", 3) == 0))  { fsz = 4; falign = 4; }
            else if ((ftype->count == 3 && memcmp(ftype->c_str, "U32", 3) == 0))  { fsz = 4; falign = 4; }
            else if ((ftype->count == 4 && memcmp(ftype->c_str, "Bool", 4) == 0)) { fsz = 1; falign = 1; }
            else if (type_from_name_init(ftype, scope).tag == TilType_TAG_FuncPtr) {
                // FuncSig-typed field: function pointer (void *)
                fsz = 8; falign = 8;
            } else {
                // Inline struct/enum field
                Expr *nested_def = tscope_get_struct(scope, ftype);
                if (nested_def && nested_def->data.tag == ExprData_TAG_EnumDef) {
                    if (*enum_has_payloads(nested_def)) {
                        fsz = 8; falign = 8; // tagged enum: pointer to EnumInstance
                    } else {
                        fsz = 4; falign = 4; // simple enum: I32 tag (matches C enum)
                    }
                    field->data.data.Decl.field_struct_def = nested_def;
                } else if (nested_def) {
                    compute_struct_layout(nested_def, scope);
                    fsz = nested_def->total_struct_size;
                    falign = 8; // structs are 8-aligned
                    field->data.data.Decl.field_struct_def = nested_def;
                } else {
                    fsz = 8; falign = 8; // unknown — treat as pointer
                }
            }
        }

        offset = align_up(offset, falign);
        field->data.data.Decl.field_offset = offset;
        field->data.data.Decl.field_size = fsz;
        if (falign > max_align) max_align = falign;
        offset += fsz;
    }

    struct_def->total_struct_size = align_up(offset, max_align);
    if (struct_def->total_struct_size == 0)
        struct_def->total_struct_size = 1; // empty structs need at least 1 byte
}

static void compute_all_struct_layouts(Expr *program, TypeScope *scope) {
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef) continue;

        Str *sname = &stmt->data.data.Decl.name;
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        compute_struct_layout(Expr_child(stmt, &(USize){(USize)(0)}), scope);
    }
}

// --- Init phase: pre-scan top-level declarations ---

I32 init_declarations(Expr *program, TypeScope *scope) {
    I32 errors = 0;

    // Pass 1: register all struct definitions
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef) continue;

        Str *sname = &stmt->data.data.Decl.name;

        // Check for redeclaration: if a struct/ext_struct with this name already exists, error
        TypeBinding *existing = tscope_find(scope, sname);
        if (existing && existing->struct_def) {
            fprintf(stderr, "%s:%u:%u: error: struct '%s' already declared at %s:%u:%u\n",
                    stmt->path.c_str, stmt->line, stmt->col, sname->c_str,
                    existing->struct_def->path.c_str, existing->line, existing->col);
            errors++;
            continue;
        }

        TilType builtin_type = (TilType){TilType_TAG_Struct};
        Bool is_builtin = 0;
        if ((sname->count == 3 && memcmp(sname->c_str, "I64", 3) == 0))             { builtin_type = (TilType){TilType_TAG_I64};        is_builtin = 1; }
        else if ((sname->count == 2 && memcmp(sname->c_str, "U8", 2) == 0))         { builtin_type = (TilType){TilType_TAG_U8};         is_builtin = 1; }
        else if ((sname->count == 3 && memcmp(sname->c_str, "I16", 3) == 0))        { builtin_type = (TilType){TilType_TAG_I16};        is_builtin = 1; }
        else if ((sname->count == 3 && memcmp(sname->c_str, "I32", 3) == 0))        { builtin_type = (TilType){TilType_TAG_I32};        is_builtin = 1; }
        else if ((sname->count == 3 && memcmp(sname->c_str, "U32", 3) == 0))        { builtin_type = (TilType){TilType_TAG_U32};        is_builtin = 1; }
        else if ((sname->count == 3 && memcmp(sname->c_str, "U64", 3) == 0))        { builtin_type = (TilType){TilType_TAG_U64};        is_builtin = 1; }
        else if ((sname->count == 5 && memcmp(sname->c_str, "USize", 5) == 0))      { builtin_type = (TilType){TilType_TAG_U32};        is_builtin = 1; }
        else if ((sname->count == 3 && memcmp(sname->c_str, "Str", 3) == 0))        { is_builtin = 0; } // Str is a regular struct
        else if ((sname->count == 4 && memcmp(sname->c_str, "Bool", 4) == 0))       { builtin_type = (TilType){TilType_TAG_Bool};       is_builtin = 1; }
        else if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0))  { builtin_type = (TilType){TilType_TAG_StructDef}; is_builtin = 1; }
        else if ((sname->count == 11 && memcmp(sname->c_str, "FunctionDef", 11) == 0)){ is_builtin = 0; } // regular struct like Str
        else if ((sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0))   { builtin_type = (TilType){TilType_TAG_Dynamic};    is_builtin = 1; }

        TypeScope_set(scope, sname, &builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *b = tscope_find(scope, sname);
        b->struct_def = Expr_child(stmt, &(USize){(USize)(0)});
        b->is_builtin = is_builtin;
        b->is_ext = Expr_child(stmt, &(USize){(USize)(0)})->is_ext;
    }

    // Pass 1.1: pre-register FuncSig type aliases (bodyless func/proc defs)
    // Needed before struct layout/clone/delete so FuncSig-typed struct fields are recognized
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_FuncDef) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->children.count != 0) continue; // bodyless = FuncSig
        TypeScope_set(scope, &stmt->data.data.Decl.name, &(TilType){TilType_TAG_FuncPtr}, -1, 0,
                   stmt->line, stmt->col, 0, 0);
        TypeBinding *fb = tscope_find(scope, &stmt->data.data.Decl.name);
        if (fb) fb->func_def = Expr_child(stmt, &(USize){(USize)(0)});
    }

    // Pass 1.5: auto-generate clone methods for all structs
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef) continue;

        Str *sname = &stmt->data.data.Decl.name;

        // Skip meta-types and core ext_structs (C side provides clone)
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        Expr *sdef = Expr_child(stmt, &(USize){(USize)(0)});
        if (sdef->is_ext && stmt->is_core) continue;

        Expr *body = Expr_child(sdef, &(USize){(USize)(0)}); // ExprData_TAG_Body

        // Check if clone already exists in namespace
        Bool has_clone = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
                (field->data.data.Decl.name.count == 5 && memcmp(field->data.data.Decl.name.c_str, "clone", 5) == 0)) {
                has_clone = 1;
                break;
            }
        }
        if (has_clone) continue;

        // Collect instance field names and ref/funcptr flags
        Vec field_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); field_names = *_vp; free(_vp); }
        Vec field_refs; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(I32)}); field_refs = *_vp; free(_vp); }
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && !field->data.data.Decl.is_namespace) {
                { Str **_p = malloc(sizeof(Str *)); *_p = &field->data.data.Decl.name; Vec_push(&field_names, _p); }
                I32 ref_flag = field->data.data.Decl.is_ref ? 1 : 0;
                // FuncSig-typed fields are just pointers — treat like ref for clone (no .clone())
                if (!ref_flag && field->data.data.Decl.explicit_type.count > 0 &&
                    type_from_name_init(&field->data.data.Decl.explicit_type, scope).tag == TilType_TAG_FuncPtr)
                    ref_flag = 1;
                { I32 *_p = malloc(sizeof(I32)); *_p = ref_flag; Vec_push(&field_refs, _p); }
            }
        }

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = &stmt->path;
        Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

        if (field_names.count == 0) {
            // No instance fields: return Type()
            Expr *ctor = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr *ctor_name = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            ctor_name->data.data.Ident = *sname;
            Expr_add_child(ctor, ctor_name);

            Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret, ctor);
            Expr_add_child(func_body, ret);
        } else {
            // With fields: return StructName(f1=self.f1.clone(), ...)
            Expr *ctor = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr *ctor_name = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            ctor_name->data.data.Ident = *sname;
            Expr_add_child(ctor, ctor_name);

            for (U32 j = 0; j < field_names.count; j++) {
                Str *fname = *(Str **)Vec_get(&field_names, &(USize){(USize)(j)});
                I32 fref = *(I32 *)Vec_get(&field_refs, &(USize){(USize)(j)});
                // self.field_name
                Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                Expr *field_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                field_acc->data.data.FieldAccess = *fname;
                Expr_add_child(field_acc, self_id);

                Expr *val_expr;
                if (fref) {
                    // ref field: copy pointer, don't clone
                    val_expr = field_acc;
                } else {
                    // self.field_name.clone()
                    Expr *clone_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    clone_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
                    Expr_add_child(clone_acc, field_acc);
                    Expr *clone_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(clone_call, clone_acc);
                    val_expr = clone_call;
                }

                // Named arg: field_name=value
                Expr *named = Expr_new(&(ExprData){.tag = ExprData_TAG_NamedArg}, line, col, path);
                named->data.data.NamedArg = *fname;
                Expr_add_child(named, val_expr);
                Expr_add_child(ctor, named);
            }

            Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret, ctor);
            Expr_add_child(func_body, ret);
        }

        // func def
        Expr *func_def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
        func_def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
        func_def->data.data.FuncDef.nparam = 1;
        { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); func_def->data.data.FuncDef.params = *_v; free(_v); }
        { Param *_p = calloc(1, sizeof(Param));
          _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
          _p->ptype = *sname;
          Vec_push(&func_def->data.data.FuncDef.params, _p); }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); func_def->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
        func_def->data.data.FuncDef.return_type = *sname;
        func_def->data.data.FuncDef.variadic_index = -1;
        func_def->data.data.FuncDef.kwargs_index = -1;
        Expr_add_child(func_def, func_body);

        // clone := func(...)  (namespace decl)
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        decl->data.data.Decl.name = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
        decl->data.data.Decl.is_namespace = true;
        decl->data.data.Decl.is_mut = false;
        decl->data.data.Decl.explicit_type = (Str){0};
        Expr_add_child(decl, func_def);

        // Add to struct body
        Expr_add_child(body, decl);
        Vec_delete(&field_names, &(Bool){0});
        Vec_delete(&field_refs, &(Bool){0});
    }

    // Pass 1.7: auto-generate delete methods for all structs
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef) continue;

        Str *sname = &stmt->data.data.Decl.name;

        // Skip meta-types and core ext_structs (C side provides delete)
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        Expr *sdef = Expr_child(stmt, &(USize){(USize)(0)});
        if (sdef->is_ext && stmt->is_core) continue;

        Expr *body = Expr_child(sdef, &(USize){(USize)(0)}); // ExprData_TAG_Body

        // Check if delete already exists in namespace
        Bool has_delete = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
                (field->data.data.Decl.name.count == 6 && memcmp(field->data.data.Decl.name.c_str, "delete", 6) == 0)) {
                has_delete = 1;
                break;
            }
        }
        if (has_delete) continue;

        // Collect instance field names and own flags (skip ref and func ptr fields)
        Vec field_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); field_names = *_vp; free(_vp); }
        Vec field_owns; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(I32)}); field_owns = *_vp; free(_vp); }
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && !field->data.data.Decl.is_namespace &&
                !field->data.data.Decl.is_ref) {
                // Skip FuncSig-typed fields — func ptrs don't need delete
                if ((field->data.data.Decl.explicit_type).count > 0 &&
                    type_from_name_init(&field->data.data.Decl.explicit_type, scope).tag == TilType_TAG_FuncPtr)
                    continue;
                { Str **_p = malloc(sizeof(Str *)); *_p = &field->data.data.Decl.name; Vec_push(&field_names, _p); }
                { I32 *_p = malloc(sizeof(I32)); *_p = field->data.data.Decl.is_own; Vec_push(&field_owns, _p); }
            }
        }

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = &stmt->path;
        Expr *proc_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

        // For each field: self.field.delete(call_free=<true for own, false for inline>)
        for (U32 j = 0; j < field_names.count; j++) {
            Str *fname = *(Str **)Vec_get(&field_names, &(USize){(USize)(j)});
            I32 fown = *(I32 *)Vec_get(&field_owns, &(USize){(USize)(j)});
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
            Expr *field_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            field_acc->data.data.FieldAccess = *fname;
            field_acc->is_own_arg = true; // delete takes own self
            Expr_add_child(field_acc, self_id);

            Expr *del_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            del_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
            Expr_add_child(del_acc, field_acc);
            Expr *del_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(del_call, del_acc);

            // call_free=true for own fields (separate allocation), false for inline
            Expr *cf_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
            cf_lit->data.data.LiteralBool = (fown  ? (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT} : (Str){.c_str = (U8*)"false", .count = 5, .cap = CAP_LIT});
            Expr_add_child(del_call, cf_lit);

            Expr_add_child(proc_body, del_call);
        }

        // if call_free { free(own self) }
        Expr *cond = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        cond->data.data.Ident = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
        Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
        Expr *free_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
        Expr *free_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        free_id->data.data.Ident = (Str){.c_str = (U8*)"free", .count = 4, .cap = CAP_LIT};
        Expr_add_child(free_call, free_id);
        Expr *self_arg = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        self_arg->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
        self_arg->is_own_arg = true;
        Expr_add_child(free_call, self_arg);
        Expr_add_child(then_body, free_call);
        Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
        Expr_add_child(if_node, cond);
        Expr_add_child(if_node, then_body);
        Expr_add_child(proc_body, if_node);

        // func def: delete(own self: Type, call_free: Bool = true)
        Expr *default_true = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
        default_true->data.data.LiteralBool = (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT};

        Expr *proc_def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
        // Note: is_core NOT set — auto-generated delete goes to per-module
        // file (same as clone), not to main file
        proc_def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
        proc_def->data.data.FuncDef.nparam = 2;
        { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); proc_def->data.data.FuncDef.params = *_v; free(_v); }
        { Param *_p = calloc(1, sizeof(Param));
          _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
          _p->ptype = *sname;
          _p->is_own = true;
          Vec_push(&proc_def->data.data.FuncDef.params, _p); }
        { Param *_p = calloc(1, sizeof(Param));
          _p->name = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
          _p->ptype = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
          Vec_push(&proc_def->data.data.FuncDef.params, _p); }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); proc_def->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
        { Str *_k = Str_clone(&(Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT}); Expr *_v = Expr_clone(default_true); Map_set(&proc_def->data.data.FuncDef.param_defaults, _k, _v); }
        proc_def->data.data.FuncDef.return_type = (Str){0};
        proc_def->data.data.FuncDef.variadic_index = -1;
        proc_def->data.data.FuncDef.kwargs_index = -1;
        Expr_add_child(proc_def, proc_body);

        // delete := func(...)  (namespace decl)
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        decl->data.data.Decl.name = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
        decl->data.data.Decl.is_namespace = true;
        decl->data.data.Decl.is_mut = false;
        decl->data.data.Decl.explicit_type = (Str){0};
        Expr_add_child(decl, proc_def);

        // Add to struct body
        Expr_add_child(body, decl);
        Vec_delete(&field_names, &(Bool){0});
        Vec_delete(&field_owns, &(Bool){0});
    }

    // Pass 1.8: register enum definitions, generate variants + methods
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_EnumDef) continue;

        Str *ename = &stmt->data.data.Decl.name;
        I32 line = stmt->line, col = stmt->col;
        Str *path = &stmt->path;

        // Check for redeclaration
        TypeBinding *existing = tscope_find(scope, ename);
        if (existing && existing->struct_def) {
            fprintf(stderr, "%s:%u:%u: error: enum '%s' already declared at %s:%u:%u\n",
                    path->c_str, line, col, ename->c_str,
                    existing->struct_def->path.c_str, existing->line, existing->col);
            errors++;
            continue;
        }

        // Register in type scope
        TypeScope_set(scope, ename, &(TilType){TilType_TAG_Enum}, -1, 0, line, col, 0, 0);
        TypeBinding *b = tscope_find(scope, ename);
        b->struct_def = Expr_child(stmt, &(USize){(USize)(0)});

        Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){(USize)(0)}); // ExprData_TAG_Body

        // Collect variant info (names + optional payload types)
        Vec variant_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_names = *_vp; free(_vp); }
        Vec variant_types; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_types = *_vp; free(_vp); }
        Bool has_payloads = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            if (Expr_child(body, &(USize){(USize)(j)})->data.data.Decl.is_namespace) continue;
            { Str *_p = Str_clone(&Expr_child(body, &(USize){(USize)(j)})->data.data.Decl.name); Vec_push(&variant_names, _p); }
            { Str *_p = Str_clone(&Expr_child(body, &(USize){(USize)(j)})->data.data.Decl.explicit_type); Vec_push(&variant_types, _p); }
            if ((Expr_child(body, &(USize){(USize)(j)})->data.data.Decl.explicit_type.count > 0)) has_payloads = 1;
        }

        if (!has_payloads) {
            // === SIMPLE ENUM (Phase 1 path — no payloads) ===
            // Keep original variant markers as registry (don't compact)

            // Add I64 namespace fields for each variant
            for (U32 j = 0; j < variant_names.count; j++) {
                Expr *lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
                char buf[16];
                snprintf(buf, sizeof(buf), "%d", j);
                lit->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
                Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                decl->data.data.Decl.name = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                decl->data.data.Decl.is_namespace = true;
                Expr_add_child(decl, lit);
                Expr_add_child(body, decl);
            }
        } else {
            // === PAYLOAD ENUM (Phase 2 path) ===
            // Keep original variant markers as registry (don't compact)

            for (U32 j = 0; j < variant_names.count; j++) {
                if (((Str *)Vec_get(&variant_types, &(USize){(USize)(j)}))->count > 0) {
                    // Payload variant: ext_func constructor
                    // e.g. Num := ext_func(val: I64) returns Token {}
                    Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
                    fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_ExtFunc};
                    fdef->data.data.FuncDef.nparam = 1;
                    { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
                    { Param *_p = calloc(1, sizeof(Param));
                      _p->name = (Str){.c_str = (U8*)"val", .count = 3, .cap = CAP_LIT};
                      _p->ptype = *(Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
                      Vec_push(&fdef->data.data.FuncDef.params, _p); }
                    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
                    fdef->data.data.FuncDef.return_type = *ename;
                    fdef->data.data.FuncDef.variadic_index = -1;
                    fdef->data.data.FuncDef.kwargs_index = -1;
                    Expr_add_child(fdef, Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path));
                    Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                    decl->data.data.Decl.name = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    decl->data.data.Decl.is_namespace = true;
                    Expr_add_child(decl, fdef);
                    Expr_add_child(body, decl);
                } else {
                    // No-payload variant: zero-arg ext_func constructor
                    // e.g. Eof := ext_func() returns Token {}
                    Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
                    fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_ExtFunc};
                    fdef->data.data.FuncDef.nparam = 0;
                    { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
                    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
                    fdef->data.data.FuncDef.return_type = *ename;
                    fdef->data.data.FuncDef.variadic_index = -1;
                    fdef->data.data.FuncDef.kwargs_index = -1;
                    Expr_add_child(fdef, Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path));
                    Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                    decl->data.data.Decl.name = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    decl->data.data.Decl.is_namespace = true;
                    Expr_add_child(decl, fdef);
                    Expr_add_child(body, decl);
                }
            }

            // Generate get_Variant ext_func for payload variants
            for (U32 j = 0; j < variant_names.count; j++) {
                if (((Str *)Vec_get(&variant_types, &(USize){(USize)(j)}))->count == 0) continue;
                char name_buf[256];
                snprintf(name_buf, sizeof(name_buf), "get_%s", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
                fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_ExtFunc};
                fdef->data.data.FuncDef.nparam = 1;
                { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
                { Param *_p = calloc(1, sizeof(Param));
                  _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                  _p->ptype = *ename;
                  Vec_push(&fdef->data.data.FuncDef.params, _p); }
                { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
                fdef->data.data.FuncDef.return_type = *(Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
                fdef->data.data.FuncDef.variadic_index = -1;
                fdef->data.data.FuncDef.kwargs_index = -1;
                Expr_add_child(fdef, Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path));
                Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                decl->data.data.Decl.name = *Str_clone(&(Str){.c_str = (U8*)(name_buf), .count = (U64)strlen((const char*)(name_buf)), .cap = CAP_VIEW});
                decl->data.data.Decl.is_namespace = true;
                Expr_add_child(decl, fdef);
                Expr_add_child(body, decl);
            }
        }

        // Generate is_Variant ext_func for every variant (all enums)
        for (U32 j = 0; j < variant_names.count; j++) {
            char name_buf[256];
            snprintf(name_buf, sizeof(name_buf), "is_%s", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_ExtFunc};
            fdef->data.data.FuncDef.nparam = 1;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path));
            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = *Str_clone(&(Str){.c_str = (U8*)(name_buf), .count = (U64)strlen((const char*)(name_buf)), .cap = CAP_VIEW});
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Check existing methods
        Bool has_eq = 0, has_clone = 0, has_delete = 0, has_to_str = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = Expr_child(body, &(USize){(USize)(j)});
            if (f->data.tag != ExprData_TAG_Decl || !f->data.data.Decl.is_namespace) continue;
            if (f->children.count == 0 || Expr_child(f, &(USize){(USize)(0)})->data.tag != ExprData_TAG_FuncDef) continue;
            if ((f->data.data.Decl.name.count == 2 && memcmp(f->data.data.Decl.name.c_str, "eq", 2) == 0)) has_eq = 1;
            if ((f->data.data.Decl.name.count == 5 && memcmp(f->data.data.Decl.name.c_str, "clone", 5) == 0)) has_clone = 1;
            if ((f->data.data.Decl.name.count == 6 && memcmp(f->data.data.Decl.name.c_str, "delete", 6) == 0)) has_delete = 1;
            if ((f->data.data.Decl.name.count == 6 && memcmp(f->data.data.Decl.name.c_str, "to_str", 6) == 0)) has_to_str = 1;
        }

        // Auto-generate eq := func(self: E, other: E) returns Bool { if-chain }
        // Uses is_Variant() for all variants, get_Variant().eq() for payloads
        if (!has_eq) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                // Build self.is_Vj() call
                Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                char is_buf[256];
                snprintf(is_buf, sizeof(is_buf), "is_%s",
                         ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                Expr *is_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                is_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                Expr_add_child(is_acc, self_id);
                Expr *is_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                Expr_add_child(is_call, is_acc);

                Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

                if (((Str *)Vec_get(&variant_types, &(USize){(USize)(j)}))->count > 0) {
                    Str *vtype = (Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
                    Bool is_funcsig = type_from_name_init(vtype, scope).tag == TilType_TAG_FuncPtr;

                    // Payload variant:
                    //   if other.is_Vj().not() { return false }
                    //   FuncSig: return true (tag-only eq)
                    //   Other:   return self.get_Vj().eq(other.get_Vj())
                    Expr *other_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    other_id->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
                    Expr *is_acc2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    is_acc2->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                    Expr_add_child(is_acc2, other_id);
                    Expr *is_call2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(is_call2, is_acc2);
                    Expr *not_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    not_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"not", .count = 3, .cap = CAP_LIT};
                    Expr_add_child(not_acc, is_call2);
                    Expr *not_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(not_call, not_acc);

                    Expr *ret_false = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                    Expr *false_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
                    false_lit->data.data.LiteralBool = (Str){.c_str = (U8*)"false", .count = 5, .cap = CAP_LIT};
                    Expr_add_child(ret_false, false_lit);
                    Expr *guard_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Expr_add_child(guard_body, ret_false);
                    Expr *guard_if = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(guard_if, not_call);
                    Expr_add_child(guard_if, guard_body);
                    Expr_add_child(then_body, guard_if);

                    if (is_funcsig) {
                        // FuncSig payload: tag-only equality (return true)
                        Expr *ret_true = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr *true_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
                        true_lit->data.data.LiteralBool = (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT};
                        Expr_add_child(ret_true, true_lit);
                        Expr_add_child(then_body, ret_true);
                    } else {
                        // return self.get_Vj().eq(other.get_Vj())
                        char get_buf[256];
                        snprintf(get_buf, sizeof(get_buf), "get_%s",
                                 ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *self2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self2->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        Expr *get_acc1 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        get_acc1->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(get_buf), .count = (U64)strlen((const char*)(get_buf)), .cap = CAP_VIEW});
                        Expr_add_child(get_acc1, self2);
                        Expr *get_call1 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(get_call1, get_acc1);

                        Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                        Expr_add_child(eq_acc, get_call1);

                        Expr *other2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        other2->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
                        Expr *get_acc2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        get_acc2->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(get_buf), .count = (U64)strlen((const char*)(get_buf)), .cap = CAP_VIEW});
                        Expr_add_child(get_acc2, other2);
                        Expr *get_call2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(get_call2, get_acc2);

                        Expr *eq_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(eq_call, eq_acc);
                        Expr_add_child(eq_call, get_call2);

                        Expr *ret_eq = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret_eq, eq_call);
                        Expr_add_child(then_body, ret_eq);
                    }
                } else {
                    // No-payload variant: return other.is_Vj()
                    Expr *other_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    other_id->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
                    Expr *is_acc2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    is_acc2->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                    Expr_add_child(is_acc2, other_id);
                    Expr *is_call2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(is_call2, is_acc2);
                    Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                    Expr_add_child(ret, is_call2);
                    Expr_add_child(then_body, ret);
                }

                Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                Expr_add_child(if_node, is_call);
                Expr_add_child(if_node, then_body);
                Expr_add_child(func_body, if_node);
            }
            // return false
            Expr *ret_false = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr *false_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
            false_lit->data.data.LiteralBool = (Str){.c_str = (U8*)"false", .count = 5, .cap = CAP_LIT};
            Expr_add_child(ret_false, false_lit);
            Expr_add_child(func_body, ret_false);

            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 2;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, func_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Auto-generate clone := func(self: E) returns E { if-chain }
        // Payload: if self.is_V() { return E.V(self.get_V()) } ... return E.Vn()
        // Simple:  if self.eq(E.V()) { return E.V() } ... return E.Vn()
        if (!has_clone) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                // Build variant expression: E.V(self.get_V()) for payload, E.V for no-payload
                Expr *ename_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                ename_id->data.data.Ident = *ename;
                Expr *ctor_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                ctor_acc->data.data.FieldAccess = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                Expr_add_child(ctor_acc, ename_id);

                Expr *ctor_expr;
                if (((Str *)Vec_get(&variant_types, &(USize){(USize)(j)}))->count > 0) {
                    // Payload variant: E.V(self.get_V())
                    Expr *ctor_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(ctor_call, ctor_acc);
                    Expr *self_g = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    self_g->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                    char get_buf[256];
                    snprintf(get_buf, sizeof(get_buf), "get_%s",
                             ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                    Expr *get_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    get_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(get_buf), .count = (U64)strlen((const char*)(get_buf)), .cap = CAP_VIEW});
                    Expr_add_child(get_acc, self_g);
                    Expr *get_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(get_call, get_acc);
                    Expr_add_child(ctor_call, get_call);
                    ctor_expr = ctor_call;
                } else {
                    // No-payload variant: bare E.V (auto-called at runtime)
                    ctor_expr = ctor_acc;
                }

                Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                Expr_add_child(ret, ctor_expr);

                if (j < variant_names.count - 1) {
                    // Condition: payload uses is_V(), simple uses eq(E.V())
                    Expr *cond;
                    if (has_payloads) {
                        Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        char is_buf[256];
                        snprintf(is_buf, sizeof(is_buf), "is_%s",
                                 ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *is_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        is_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                        Expr_add_child(is_acc, self_id);
                        cond = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(cond, is_acc);
                    } else {
                        // self.eq(E.V) — bare field access as eq arg
                        Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                        Expr_add_child(eq_acc, self_id);

                        Expr *en2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        en2->data.data.Ident = *ename;
                        Expr *va2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        va2->data.data.FieldAccess = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                        Expr_add_child(va2, en2);

                        cond = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(cond, eq_acc);
                        Expr_add_child(cond, va2);
                    }

                    Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Expr_add_child(then_body, ret);

                    Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(if_node, cond);
                    Expr_add_child(if_node, then_body);
                    Expr_add_child(func_body, if_node);
                } else {
                    // Last variant: bare return
                    Expr_add_child(func_body, ret);
                }
            }

            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 1;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = *ename;
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, func_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Auto-generate delete for all enums (same pattern):
        // delete := func(own self: E, call_free: Bool = true) {
        //     if call_free { free(own self) }
        // }
        // free() builtin handles payload cleanup for Value_TAG_Enum
        if (!has_delete) {
            Expr *proc_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            Expr *cond = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            cond->data.data.Ident = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
            Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            Expr *free_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr *free_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            free_id->data.data.Ident = (Str){.c_str = (U8*)"free", .count = 4, .cap = CAP_LIT};
            Expr_add_child(free_call, free_id);
            Expr *self_arg = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_arg->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
            self_arg->is_own_arg = true;
            Expr_add_child(free_call, self_arg);
            Expr_add_child(then_body, free_call);
            Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
            Expr_add_child(if_node, cond);
            Expr_add_child(if_node, then_body);
            Expr_add_child(proc_body, if_node);

            Expr *default_true = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
            default_true->data.data.LiteralBool = (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT};
            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            // Note: is_core NOT set — auto-generated delete goes to per-module
            // file (same as clone), not to main file
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 2;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              _p->is_own = true;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
              _p->ptype = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            { Str *_k = Str_clone(&(Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT}); Expr *_v = Expr_clone(default_true); Map_set(&fdef->data.data.FuncDef.param_defaults, _k, _v); }
            fdef->data.data.FuncDef.return_type = (Str){0};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, proc_body);
            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Auto-generate to_str := func(self: E) returns Str { if-chain }
        if (!has_to_str) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                if (has_payloads) {
                    // Payload enum to_str uses is_/get_ methods
                    // if self.is_Variant() { ... }
                    Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                    char is_buf[256];
                    snprintf(is_buf, sizeof(is_buf), "is_%s", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                    Expr *is_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    is_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                    Expr_add_child(is_acc, self_id);
                    Expr *is_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(is_call, is_acc);

                    Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Str *vtype = (Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
                    if (vtype && (*vtype).count > 0 && type_from_name_init(vtype, scope).tag == TilType_TAG_FuncPtr) {
                        // FuncSig payload: return "Variant(func)"
                        char buf[256];
                        snprintf(buf, sizeof(buf), "%s(func)", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *ret_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        ret_str->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
                        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret, ret_str);
                        Expr_add_child(then_body, ret);
                    } else if (vtype->count > 0) {
                        // return format("Variant(", self.get_Variant().to_str(), ")")
                        Expr *fmt_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr *fmt_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        fmt_id->data.data.Ident = (Str){.c_str = (U8*)"format", .count = 6, .cap = CAP_LIT};
                        Expr_add_child(fmt_call, fmt_id);

                        char prefix_buf[256];
                        snprintf(prefix_buf, sizeof(prefix_buf), "%s(", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *prefix = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        prefix->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(prefix_buf), .count = (U64)strlen((const char*)(prefix_buf)), .cap = CAP_VIEW});
                        Expr_add_child(fmt_call, prefix);

                        // self.get_Variant().to_str()
                        Expr *self2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self2->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        char get_buf[256];
                        snprintf(get_buf, sizeof(get_buf), "get_%s", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *get_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        get_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(get_buf), .count = (U64)strlen((const char*)(get_buf)), .cap = CAP_VIEW});
                        Expr_add_child(get_acc, self2);
                        Expr *get_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(get_call, get_acc);
                        Expr *tostr_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        tostr_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"to_str", .count = 6, .cap = CAP_LIT};
                        Expr_add_child(tostr_acc, get_call);
                        Expr *tostr_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(tostr_call, tostr_acc);
                        Expr_add_child(fmt_call, tostr_call);

                        Expr *suffix = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        suffix->data.data.LiteralStr = (Str){.c_str = (U8*)")", .count = 1, .cap = CAP_LIT};
                        Expr_add_child(fmt_call, suffix);

                        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret, fmt_call);
                        Expr_add_child(then_body, ret);
                    } else {
                        // return "VariantName"
                        Expr *ret_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        ret_str->data.data.LiteralStr = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret, ret_str);
                        Expr_add_child(then_body, ret);
                    }

                    Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(if_node, is_call);
                    Expr_add_child(if_node, then_body);
                    Expr_add_child(func_body, if_node);
                } else {
                    // Simple enum: if self.eq(EnumName.VariantName) { return "VariantName" }
                    Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                    Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                    Expr_add_child(eq_acc, self_id);

                    // EnumName.VariantName (bare field access)
                    Expr *ename_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    ename_id->data.data.Ident = *ename;
                    Expr *var_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    var_acc->data.data.FieldAccess = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    Expr_add_child(var_acc, ename_id);

                    Expr *eq_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(eq_call, eq_acc);
                    Expr_add_child(eq_call, var_acc);

                    Expr *ret_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                    ret_str->data.data.LiteralStr = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                    Expr_add_child(ret, ret_str);
                    Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Expr_add_child(then_body, ret);

                    Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(if_node, eq_call);
                    Expr_add_child(if_node, then_body);
                    Expr_add_child(func_body, if_node);
                }
            }
            // return "unknown"
            Expr *unk = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
            unk->data.data.LiteralStr = (Str){.c_str = (U8*)"unknown", .count = 7, .cap = CAP_LIT};
            Expr *ret_unk = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret_unk, unk);
            Expr_add_child(func_body, ret_unk);

            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 1;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, func_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"to_str", .count = 6, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        Vec_delete(&variant_names, &(Bool){0});
        Vec_delete(&variant_types, &(Bool){0});
    }

    // Pass 1.85: register type aliases (Name := ExistingType where RHS is a known type name)
    // Must run after Pass 1 (structs), Pass 1.1 (FuncSigs), and Pass 1.8 (enums)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
        if (rhs->data.tag != ExprData_TAG_Ident) continue;
        // RHS is a simple identifier — check if it refers to a known type
        Str *target_name = &rhs->data.data.Ident;
        TypeBinding *target = tscope_find(scope, target_name);
        if (!target) continue;
        // Must be a type definition: struct_def (struct/enum) or builtin or funcSig
        if (!target->struct_def && !target->is_builtin &&
            !(target->func_def && target->func_def->children.count == 0)) continue;
        // Already registered (e.g. by Pass 1 or 1.1) — skip
        if (tscope_find(scope, &stmt->data.data.Decl.name)) continue;
        // Register alias with same type info as target
        TypeScope_set(scope, &stmt->data.data.Decl.name, &target->type, target->is_proc, 0,
                   stmt->line, stmt->col, 0, 0);
        TypeBinding *ab = tscope_find(scope, &stmt->data.data.Decl.name);
        if (ab) {
            ab->struct_def = target->struct_def;
            ab->func_def = target->func_def;
            ab->is_builtin = target->is_builtin;
            ab->is_ext = target->is_ext;
            ab->is_type_alias = 1;
            // Resolve canonical name: if target is itself an alias, follow the chain
            ab->alias_target = target->alias_target ? target->alias_target : target_name;
            if (target->struct_name) ab->struct_name = target->struct_name;
        }
    }

    // Pass 1.9: compute flat struct layout (field offsets and sizes)
    // Must run BEFORE size method synthesis so total_struct_size is available
    compute_all_struct_layouts(program, scope);

    // Pass 1.92: auto-generate size methods for structs and enums
    // Uses total_struct_size computed above for correct values (includes alignment padding)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
        if (def->data.tag != ExprData_TAG_StructDef && def->data.tag != ExprData_TAG_EnumDef) continue;

        Str *sname = &stmt->data.data.Decl.name;

        // Skip meta-types
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        // Skip core ext_structs (they define size in core.til)
        if (def->is_ext && stmt->is_core) continue;

        Expr *body = Expr_child(def, &(USize){(USize)(0)}); // ExprData_TAG_Body

        // Check if size already exists in namespace
        Bool has_size = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
                (field->data.data.Decl.name.count == 4 && memcmp(field->data.data.Decl.name.c_str, "size", 4) == 0)) {
                has_size = 1;
                break;
            }
        }
        if (has_size) continue;

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = &stmt->path;

        // Use computed total_struct_size for structs, 8 for enums (I64 or pointer)
        I32 sz = def->data.tag == ExprData_TAG_EnumDef
            ? (*enum_has_payloads(def) ? 8 : 4)
            : def->total_struct_size;
        char sz_buf[16];
        snprintf(sz_buf, sizeof(sz_buf), "%d", sz);

        // size := func() returns USize { return <literal> }
        Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
        Expr *size_expr = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
        size_expr->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(sz_buf), .count = (U64)strlen((const char*)(sz_buf)), .cap = CAP_VIEW});
        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
        Expr_add_child(ret, size_expr);
        Expr_add_child(func_body, ret);

        Expr *func_def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
        func_def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
        func_def->data.data.FuncDef.nparam = 0;
        { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); func_def->data.data.FuncDef.params = *_v; free(_v); }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); func_def->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
        func_def->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"USize", .count = 5, .cap = CAP_LIT};
        func_def->data.data.FuncDef.variadic_index = -1;
        func_def->data.data.FuncDef.kwargs_index = -1;
        Expr_add_child(func_def, func_body);

        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        decl->data.data.Decl.name = (Str){.c_str = (U8*)"size", .count = 4, .cap = CAP_LIT};
        decl->data.data.Decl.is_namespace = true;
        decl->data.data.Decl.is_mut = false;
        decl->data.data.Decl.explicit_type = (Str){0};
        Expr_add_child(decl, func_def);

        Expr_add_child(body, decl);
    }

    // Pass 1.95: auto-generate derived methods
    // From cmp: eq, neq, lt, gt, lte, gte (if missing)
    // From add+unity: inc (if missing). From sub+unity: dec (if missing)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
        if (def->data.tag != ExprData_TAG_StructDef && def->data.tag != ExprData_TAG_EnumDef) continue;

        Str *sname = &stmt->data.data.Decl.name;
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        Expr *body = Expr_child(def, &(USize){(USize)(0)});
        Bool has_cmp = 0, has_eq = 0, has_neq = 0;
        Bool has_lt = 0, has_gt = 0, has_lte = 0, has_gte = 0;
        Bool has_add = 0, has_sub = 0, has_unity = 0, has_inc = 0, has_dec = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = Expr_child(body, &(USize){(USize)(j)});
            if (f->data.tag != ExprData_TAG_Decl || !f->data.data.Decl.is_namespace) continue;
            if (f->children.count == 0 || Expr_child(f, &(USize){(USize)(0)})->data.tag != ExprData_TAG_FuncDef) continue;
            Str *fn = &f->data.data.Decl.name;
            if ((fn->count == 3 && memcmp(fn->c_str, "cmp", 3) == 0)) has_cmp = 1;
            if ((fn->count == 2 && memcmp(fn->c_str, "eq", 2) == 0)) has_eq = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "neq", 3) == 0)) has_neq = 1;
            if ((fn->count == 2 && memcmp(fn->c_str, "lt", 2) == 0)) has_lt = 1;
            if ((fn->count == 2 && memcmp(fn->c_str, "gt", 2) == 0)) has_gt = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "lte", 3) == 0)) has_lte = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "gte", 3) == 0)) has_gte = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "add", 3) == 0)) has_add = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "sub", 3) == 0)) has_sub = 1;
            if ((fn->count == 5 && memcmp(fn->c_str, "unity", 5) == 0)) has_unity = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "inc", 3) == 0)) has_inc = 1;
            if ((fn->count == 3 && memcmp(fn->c_str, "dec", 3) == 0)) has_dec = 1;
        }
        if (!has_cmp && !has_unity) continue;

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = &stmt->path;

        if (has_cmp) {
        // Helper macros for building AST nodes inline
        #define MK(type) Expr_new(&(ExprData){.tag = type}, line, col, path)
        #define ID(s) ({ Expr *_e = MK(ExprData_TAG_Ident); _e->data.data.Ident = *Str_clone(&(Str){.c_str = (U8*)(s), .count = (U64)strlen((const char*)(s)), .cap = CAP_VIEW}); _e; })
        #define NUM(s) ({ Expr *_e = MK(ExprData_TAG_LiteralNum); _e->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(s), .count = (U64)strlen((const char*)(s)), .cap = CAP_VIEW}); _e; })
        #define ACC(obj, field) ({ Expr *_e = MK(ExprData_TAG_FieldAccess); _e->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(field), .count = (U64)strlen((const char*)(field)), .cap = CAP_VIEW}); Expr_add_child(_e, obj); _e; })
        #define CALL0(callee) ({ Expr *_e = MK(ExprData_TAG_FCall); Expr_add_child(_e, callee); _e; })
        #define CALL1(callee, arg1) ({ Expr *_e = MK(ExprData_TAG_FCall); Expr_add_child(_e, callee); Expr_add_child(_e, arg1); _e; })
        #define RET(val) ({ Expr *_e = MK(ExprData_TAG_Return); Expr_add_child(_e, val); _e; })

        // a.cmp(b).eq(N) — build: call(acc(call(acc(id("a"), "cmp"), id("b")), "eq"), N)
        #define CMP_EQ(n) RET(CALL1(ACC(CALL1(ACC(ID("a"), "cmp"), ID("b")), "eq"), n))
        // 0.sub(1) for -1
        #define NEG1() CALL1(ACC(NUM("0"), "sub"), NUM("1"))

        // Generate a 2-param func decl in namespace
        #define GEN_CMP_FUNC(method_name, body_expr) do { \
            Expr *fb = MK(ExprData_TAG_Body); \
            Expr_add_child(fb, body_expr); \
            Expr *fd = MK(ExprData_TAG_FuncDef); \
            fd->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func}; \
            fd->data.data.FuncDef.nparam = 2; \
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fd->data.data.FuncDef.params = *_v; free(_v); } \
            { Param *_p = calloc(1, sizeof(Param)); \
              _p->name = (Str){.c_str = (U8*)"a", .count = 1, .cap = CAP_LIT}; \
              _p->ptype = *sname; \
              Vec_push(&fd->data.data.FuncDef.params, _p); } \
            { Param *_p = calloc(1, sizeof(Param)); \
              _p->name = (Str){.c_str = (U8*)"b", .count = 1, .cap = CAP_LIT}; \
              _p->ptype = *sname; \
              Vec_push(&fd->data.data.FuncDef.params, _p); } \
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fd->data.data.FuncDef.param_defaults = *_mp; free(_mp); } \
            fd->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT}; \
            fd->data.data.FuncDef.variadic_index = -1; \
            fd->data.data.FuncDef.kwargs_index = -1; \
            Expr_add_child(fd, fb); \
            Expr *dc = MK(ExprData_TAG_Decl); \
            dc->data.data.Decl.name = *Str_clone(&(Str){.c_str = (U8*)(method_name), .count = (U64)strlen((const char*)(method_name)), .cap = CAP_VIEW}); \
            dc->data.data.Decl.is_namespace = true; \
            Expr_add_child(dc, fd); \
            Expr_add_child(body, dc); \
        } while(0)

        if (!has_eq)  { GEN_CMP_FUNC("eq", CMP_EQ(NUM("0"))); }
        if (!has_lt)  { GEN_CMP_FUNC("lt", CMP_EQ(NEG1())); }
        if (!has_gt)  { GEN_CMP_FUNC("gt", CMP_EQ(NUM("1"))); }
        if (!has_neq) { GEN_CMP_FUNC("neq", RET(CALL0(ACC(CALL1(ACC(ID("a"), "eq"), ID("b")), "not")))); }
        if (!has_lte) { GEN_CMP_FUNC("lte", RET(CALL0(ACC(CALL1(ACC(ID("a"), "gt"), ID("b")), "not")))); }
        if (!has_gte) { GEN_CMP_FUNC("gte", RET(CALL0(ACC(CALL1(ACC(ID("a"), "lt"), ID("b")), "not")))); }

        #undef MK
        #undef ID
        #undef NUM
        #undef ACC
        #undef CALL0
        #undef CALL1
        #undef RET
        #undef CMP_EQ
        #undef NEG1
        #undef GEN_CMP_FUNC
        } // end if (has_cmp)

        // Auto-generate inc/dec from add/sub + unity
        // inc(mut self: T) { self = self.add(self.unity()) }
        // dec(mut self: T) { self = self.sub(self.unity()) }
        for (int pass = 0; pass < 2; pass++) {
            // pass 0 = inc (needs add), pass 1 = dec (needs sub)
            const char *method = pass == 0 ? "inc" : "dec";
            U64 method_len = pass == 0 ? 3 : 3;
            const char *op = pass == 0 ? "add" : "sub";
            U64 op_len = 3;
            Bool already_has = pass == 0 ? has_inc : has_dec;
            Bool has_op = pass == 0 ? has_add : has_sub;
            if (already_has || !has_op || !has_unity) continue;

            // self = self.OP(self.unity())
            // Build: Assign("self", FCall(FieldAccess(Ident("self"), OP), FCall(FieldAccess(Ident("self"), "unity"))))
            Expr *self1 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self1->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};

            Expr *self2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self2->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};

            Expr *self3 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self3->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};

            // self.unity()
            Expr *unity_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            unity_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"unity", .count = 5, .cap = CAP_LIT};
            Expr_add_child(unity_acc, self2);
            Expr *unity_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(unity_call, unity_acc);

            // self.add(unity_call) or self.sub(unity_call)
            Expr *op_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            op_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)op, .count = op_len, .cap = CAP_VIEW});
            Expr_add_child(op_acc, self1);
            Expr *op_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(op_call, op_acc);
            Expr_add_child(op_call, unity_call);

            // self = ...
            Expr *assign = Expr_new(&(ExprData){.tag = ExprData_TAG_Assign}, line, col, path);
            assign->data.data.Assign = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
            Expr_add_child(assign, op_call);

            Expr *proc_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            Expr_add_child(proc_body, assign);

            // proc(mut self: T) { ... }
            Expr *fd = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fd->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fd->data.data.FuncDef.nparam = 1;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fd->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *sname;
              _p->is_mut = true;
              Vec_push(&fd->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fd->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fd->data.data.FuncDef.return_type = (Str){0};
            fd->data.data.FuncDef.variadic_index = -1;
            fd->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fd, proc_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = *Str_clone(&(Str){.c_str = (U8*)method, .count = method_len, .cap = CAP_VIEW});
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fd);
            Expr_add_child(body, decl);
        }
    }

    // Pass 2: register all func/proc definitions
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_FuncDef) continue;

        // Bodyless func/proc = FuncSig type definition
        if (Expr_child(stmt, &(USize){(USize)(0)})->children.count == 0) {
            TypeScope_set(scope, &stmt->data.data.Decl.name, &(TilType){TilType_TAG_FuncPtr}, -1, 0,
                       stmt->line, stmt->col, 0, 0);
            TypeBinding *fb = tscope_find(scope, &stmt->data.data.Decl.name);
            if (fb) fb->func_def = Expr_child(stmt, &(USize){(USize)(0)});
            continue;
        }

        // Named FuncSig form: name : Type = (names) { body }
        // Fill types from the named FuncSig before normal processing
        if (stmt->data.data.Decl.explicit_type.count > 0) {
            TypeBinding *fsb = tscope_find(scope, &stmt->data.data.Decl.explicit_type);
            if (fsb && fsb->func_def && fsb->func_def->children.count == 0) {
                Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
                Expr *sig = fsb->func_def;
                if (def->data.data.FuncDef.nparam != sig->data.data.FuncDef.nparam) {
                    fprintf(stderr, "%s:%u:%u: error: '%s' expects %u params but FuncSig '%s' has %u\n",
                            stmt->path.c_str, stmt->line, stmt->col,
                            stmt->data.data.Decl.name.c_str, def->data.data.FuncDef.nparam,
                            stmt->data.data.Decl.explicit_type.c_str, sig->data.data.FuncDef.nparam);
                    exit(1);
                }
                def->data.data.FuncDef.func_type = sig->data.data.FuncDef.func_type;
                for (U32 j = 0; j < sig->data.data.FuncDef.nparam; j++) {
                    Param *dp = (Param*)Vec_get(&def->data.data.FuncDef.params, &(USize){(USize)(j)});
                    Param *sp = (Param*)Vec_get(&sig->data.data.FuncDef.params, &(USize){(USize)(j)});
                    dp->ptype = sp->ptype;
                    dp->is_mut = sp->is_mut;
                    dp->is_own = sp->is_own;
                    dp->is_shallow = sp->is_shallow;
                }
                def->data.data.FuncDef.return_type = sig->data.data.FuncDef.return_type;
                def->data.data.FuncDef.return_is_ref = sig->data.data.FuncDef.return_is_ref;
                def->data.data.FuncDef.return_is_shallow = sig->data.data.FuncDef.return_is_shallow;
                stmt->data.data.Decl.explicit_type = (Str){0}; // now a normal FuncDef
            }
        }

        FuncType ft = Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
        I32 callee_is_proc = (ft.tag == FuncType_TAG_Test) ? 2 : (ft.tag == FuncType_TAG_Proc || ft.tag == FuncType_TAG_ExtProc) ? 1 : 0;
        TilType rt = (TilType){TilType_TAG_None};
        if ((Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.return_type.count > 0)) {
            rt = type_from_name_init(&Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.return_type, scope);
        }
        TypeScope_set(scope, &stmt->data.data.Decl.name, &rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *fb = tscope_find(scope, &stmt->data.data.Decl.name);
        if (fb) {
            fb->func_def = Expr_child(stmt, &(USize){(USize)(0)});
            if (ft.tag == FuncType_TAG_ExtFunc || ft.tag == FuncType_TAG_ExtProc)
                fb->is_builtin = 1;
        }
    }

    return errors;
}
