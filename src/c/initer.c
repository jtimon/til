#include "initer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type scope implementation ---

TypeScope *tscope_new(TypeScope *parent) {
    TypeScope *s = malloc(sizeof(TypeScope));
    { Map *_mp = Map_new(Str_new("Str"), &(U64){sizeof(Str)}, Str_new(""), &(U64){sizeof(TypeBinding)}); s->bindings = *_mp; free(_mp); }
    s->parent = parent;
    return s;
}

void tscope_free(TypeScope *s) {
    Map_delete(&s->bindings, &(Bool){0});
    free(s);
}

void tscope_set(TypeScope *s, Str *name, TilType type, I32 is_proc, Bool is_mut, U32 line, U32 col, Bool is_param, Bool is_own) {
    if (*Map_has(&s->bindings, name)) {
        TypeBinding *b = Map_get(&s->bindings, name);
        b->type = type;
        b->is_proc = is_proc;
        b->is_mut = is_mut;
        b->line = line;
        b->col = col;
        b->is_param = is_param;
        b->is_own = is_own;
        return;
    }
    TypeBinding nb = {name, type, is_proc, is_mut, line, col, is_param, is_own, 0, NULL, NULL, 0, 0, NULL};
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW}; void *_v = malloc(sizeof(nb)); memcpy(_v, &nb, sizeof(nb)); Map_set(&s->bindings, _k, _v); }
}

TypeBinding *tscope_find(TypeScope *s, Str *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        if (*Map_has(&cur->bindings, name)) return Map_get(&cur->bindings, name);
    }
    return NULL;
}

TilType tscope_get(TypeScope *s, Str *name) {
    TypeBinding *b = tscope_find(s, name);
    return b ? b->type : TIL_TYPE_UNKNOWN;
}

I32 tscope_is_proc(TypeScope *s, Str *name) {
    TypeBinding *b = tscope_find(s, name);
    return b ? b->is_proc : -1;
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
    if (Str_eq_c(name, "I64"))  return TIL_TYPE_I64;
    if (Str_eq_c(name, "U8"))   return TIL_TYPE_U8;
    if (Str_eq_c(name, "I16"))  return TIL_TYPE_I16;
    if (Str_eq_c(name, "I32"))  return TIL_TYPE_I32;
    if (Str_eq_c(name, "U32"))  return TIL_TYPE_U32;
    if (Str_eq_c(name, "U64"))  return TIL_TYPE_U64;
    if (Str_eq_c(name, "Str"))  return TIL_TYPE_STRUCT;
    if (Str_eq_c(name, "Bool")) return TIL_TYPE_BOOL;
    if (Str_eq_c(name, "StructDef"))    return TIL_TYPE_STRUCT_DEF;
    if (Str_eq_c(name, "FunctionDef"))  return TIL_TYPE_FUNC_DEF;
    if (Str_eq_c(name, "Dynamic"))     return TIL_TYPE_DYNAMIC;
    if (scope) {
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return (sdef->type.tag == NODE_ENUM_DEF) ? TIL_TYPE_ENUM : TIL_TYPE_STRUCT;
    }
    return TIL_TYPE_UNKNOWN;
}

// --- Flat struct layout computation ---

static I32 align_up(I32 offset, I32 align) {
    return (offset + align - 1) & ~(align - 1);
}

// Compute field offsets and total size for a struct def.
// Recursive: if a field is an inline struct, compute its layout first.
static void compute_struct_layout(Expr *struct_def, TypeScope *scope) {
    if (struct_def->total_struct_size > 0) return; // already computed

    Expr *body = expr_child(struct_def, 0);
    I32 offset = 0;
    I32 max_align = 1;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = expr_child(body, i);
        if (field->type.tag != NODE_DECL || field->type.decl.is_namespace) continue;

        I32 fsz, falign;

        if (field->type.decl.is_own || field->type.decl.is_ref) {
            // own/ref fields are pointers
            fsz = 8; falign = 8;
            // Resolve the pointed-to struct for field access
            Str *ftype = field->type.decl.explicit_type;
            if (!ftype && field->children.count > 0) {
                Expr *def_val = expr_child(field, 0);
                if (def_val->type.tag == NODE_FCALL && def_val->children.count > 0 &&
                    expr_child(def_val, 0)->type.tag == NODE_IDENT)
                    ftype = expr_child(def_val, 0)->type.str_val;
                if (ftype) field->type.decl.explicit_type = ftype;
            }
            if (ftype && !Str_eq_c(ftype, "I64") && !Str_eq_c(ftype, "U8") && !Str_eq_c(ftype, "I16") && !Str_eq_c(ftype, "I32") && !Str_eq_c(ftype, "U32") && !Str_eq_c(ftype, "Bool")) {
                Expr *nested_def = tscope_get_struct(scope, ftype);
                if (nested_def && !nested_def->is_ext) {
                    // Skip recursive layout for self-referential own/ref fields
                    if (nested_def != struct_def)
                        compute_struct_layout(nested_def, scope);
                    field->type.decl.field_struct_def = nested_def;
                }
            }
        } else {
            // Determine type name
            Str *ftype = field->type.decl.explicit_type;
            if (!ftype && field->children.count > 0) {
                Expr *def_val = expr_child(field, 0);
                if (def_val->type.tag == NODE_LITERAL_NUM) ftype = Str_new("I64");
                else if (def_val->type.tag == NODE_LITERAL_STR) ftype = Str_new("Str");
                else if (def_val->type.tag == NODE_LITERAL_BOOL) ftype = Str_new("Bool");
                else if (def_val->struct_name) ftype = def_val->struct_name;
                // FCALL default (e.g. Point()): callee ident is the struct name
                else if (def_val->type.tag == NODE_FCALL && def_val->children.count > 0 &&
                         expr_child(def_val, 0)->type.tag == NODE_IDENT)
                    ftype = expr_child(def_val, 0)->type.str_val;
                // Namespace FCALL default (e.g. Vec.new(...)): struct name is in field access child
                else if (def_val->type.tag == NODE_FCALL && def_val->children.count > 0 &&
                         expr_child(def_val, 0)->type.tag == NODE_FIELD_ACCESS &&
                         expr_child(expr_child(def_val, 0), 0)->type.tag == NODE_IDENT)
                    ftype = expr_child(expr_child(def_val, 0), 0)->type.str_val;
                // Namespace field access default (e.g. MyEnum.C): type is the parent ident
                else if (def_val->type.tag == NODE_FIELD_ACCESS && def_val->children.count > 0 &&
                         expr_child(def_val, 0)->type.tag == NODE_IDENT)
                    ftype = expr_child(def_val, 0)->type.str_val;
                // Store resolved type for interpreter's read_field
                if (ftype) field->type.decl.explicit_type = ftype;
            }
            if (!ftype) { fsz = 8; falign = 8; } // fallback
            else if (Str_eq_c(ftype, "I64"))  { fsz = 8; falign = 8; }
            else if (Str_eq_c(ftype, "U8"))   { fsz = 1; falign = 1; }
            else if (Str_eq_c(ftype, "I16"))  { fsz = 2; falign = 2; }
            else if (Str_eq_c(ftype, "I32"))  { fsz = 4; falign = 4; }
            else if (Str_eq_c(ftype, "U32"))  { fsz = 4; falign = 4; }
            else if (Str_eq_c(ftype, "Bool")) { fsz = 1; falign = 1; }
            else {
                // Inline struct/enum field
                Expr *nested_def = tscope_get_struct(scope, ftype);
                if (nested_def && nested_def->type.tag == NODE_ENUM_DEF) {
                    if (enum_has_payloads(nested_def)) {
                        fsz = 8; falign = 8; // tagged enum: pointer to EnumInstance
                    } else {
                        fsz = 4; falign = 4; // simple enum: I32 tag (matches C enum)
                    }
                    field->type.decl.field_struct_def = nested_def;
                } else if (nested_def) {
                    compute_struct_layout(nested_def, scope);
                    fsz = nested_def->total_struct_size;
                    falign = 8; // structs are 8-aligned
                    field->type.decl.field_struct_def = nested_def;
                } else {
                    fsz = 8; falign = 8; // unknown — treat as pointer
                }
            }
        }

        offset = align_up(offset, falign);
        field->type.decl.field_offset = offset;
        field->type.decl.field_size = fsz;
        if (falign > max_align) max_align = falign;
        offset += fsz;
    }

    struct_def->total_struct_size = align_up(offset, max_align);
    if (struct_def->total_struct_size == 0)
        struct_def->total_struct_size = 1; // empty structs need at least 1 byte
}

static void compute_all_struct_layouts(Expr *program, TypeScope *scope) {
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        if (expr_child(stmt, 0)->type.tag != NODE_STRUCT_DEF) continue;

        Str *sname = stmt->type.decl.name;
        if (Str_eq_c(sname, "StructDef") ||
            Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        compute_struct_layout(expr_child(stmt, 0), scope);
    }
}

// --- Init phase: pre-scan top-level declarations ---

I32 init_declarations(Expr *program, TypeScope *scope) {
    // Pass 1: register all struct definitions
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        if (expr_child(stmt, 0)->type.tag != NODE_STRUCT_DEF) continue;

        Str *sname = stmt->type.decl.name;
        TilType builtin_type = TIL_TYPE_STRUCT;
        Bool is_builtin = 0;
        if (Str_eq_c(sname, "I64"))             { builtin_type = TIL_TYPE_I64;        is_builtin = 1; }
        else if (Str_eq_c(sname, "U8"))         { builtin_type = TIL_TYPE_U8;         is_builtin = 1; }
        else if (Str_eq_c(sname, "I16"))        { builtin_type = TIL_TYPE_I16;        is_builtin = 1; }
        else if (Str_eq_c(sname, "I32"))        { builtin_type = TIL_TYPE_I32;        is_builtin = 1; }
        else if (Str_eq_c(sname, "U32"))        { builtin_type = TIL_TYPE_U32;        is_builtin = 1; }
        else if (Str_eq_c(sname, "U64"))        { builtin_type = TIL_TYPE_U64;        is_builtin = 1; }
        else if (Str_eq_c(sname, "Str"))        { is_builtin = 0; } // Str is a regular struct
        else if (Str_eq_c(sname, "Bool"))       { builtin_type = TIL_TYPE_BOOL;       is_builtin = 1; }
        else if (Str_eq_c(sname, "StructDef"))  { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
        else if (Str_eq_c(sname, "FunctionDef")){ builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }
        else if (Str_eq_c(sname, "Dynamic"))   { builtin_type = TIL_TYPE_DYNAMIC;    is_builtin = 1; }

        tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *b = tscope_find(scope, sname);
        b->struct_def = expr_child(stmt, 0);
        b->is_builtin = is_builtin;
        b->is_ext = expr_child(stmt, 0)->is_ext;
    }

    // Pass 1.5: auto-generate clone methods for all structs
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        if (expr_child(stmt, 0)->type.tag != NODE_STRUCT_DEF) continue;

        Str *sname = stmt->type.decl.name;

        // Skip meta-types and core ext_structs (C side provides clone)
        if (Str_eq_c(sname, "StructDef") ||
            Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        Expr *sdef = expr_child(stmt, 0);
        if (sdef->is_ext && stmt->is_core) continue;

        Expr *body = expr_child(sdef, 0); // NODE_BODY

        // Check if clone already exists in namespace
        Bool has_clone = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (field->type.tag == NODE_DECL && field->type.decl.is_namespace &&
                Str_eq_c(field->type.decl.name, "clone")) {
                has_clone = 1;
                break;
            }
        }
        if (has_clone) continue;

        // Collect instance field names and ref flags
        Vec field_names; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); field_names = *_vp; free(_vp); }
        Vec field_refs; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(I32)}); field_refs = *_vp; free(_vp); }
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (field->type.tag == NODE_DECL && !field->type.decl.is_namespace) {
                { Str **_p = malloc(sizeof(Str *)); *_p = field->type.decl.name; Vec_push(&field_names, _p); }
                I32 ref_flag = field->type.decl.is_ref ? 1 : 0;
                { I32 *_p = malloc(sizeof(I32)); *_p = ref_flag; Vec_push(&field_refs, _p); }
            }
        }

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = stmt->path;
        Expr *func_body = expr_new(NODE_BODY, line, col, path);

        if (field_names.count == 0) {
            // No instance fields: return Type()
            Expr *ctor = expr_new(NODE_FCALL, line, col, path);
            Expr *ctor_name = expr_new(NODE_IDENT, line, col, path);
            ctor_name->type.str_val = sname;
            expr_add_child(ctor, ctor_name);

            Expr *ret = expr_new(NODE_RETURN, line, col, path);
            expr_add_child(ret, ctor);
            expr_add_child(func_body, ret);
        } else {
            // With fields: return StructName(f1=self.f1.clone(), ...)
            Expr *ctor = expr_new(NODE_FCALL, line, col, path);
            Expr *ctor_name = expr_new(NODE_IDENT, line, col, path);
            ctor_name->type.str_val = sname;
            expr_add_child(ctor, ctor_name);

            for (U32 j = 0; j < field_names.count; j++) {
                Str *fname = *(Str **)Vec_get(&field_names, &(U64){(U64)(j)});
                I32 fref = *(I32 *)Vec_get(&field_refs, &(U64){(U64)(j)});
                // self.field_name
                Expr *self_id = expr_new(NODE_IDENT, line, col, path);
                self_id->type.str_val = Str_new("self");
                Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                field_acc->type.str_val = fname;
                expr_add_child(field_acc, self_id);

                Expr *val_expr;
                if (fref) {
                    // ref field: copy pointer, don't clone
                    val_expr = field_acc;
                } else {
                    // self.field_name.clone()
                    Expr *clone_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    clone_acc->type.str_val = Str_new("clone");
                    expr_add_child(clone_acc, field_acc);
                    Expr *clone_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(clone_call, clone_acc);
                    val_expr = clone_call;
                }

                // Named arg: field_name=value
                Expr *named = expr_new(NODE_NAMED_ARG, line, col, path);
                named->type.str_val = fname;
                expr_add_child(named, val_expr);
                expr_add_child(ctor, named);
            }

            Expr *ret = expr_new(NODE_RETURN, line, col, path);
            expr_add_child(ret, ctor);
            expr_add_child(func_body, ret);
        }

        // func def
        Expr *func_def = expr_new(NODE_FUNC_DEF, line, col, path);
        func_def->type.func_def.func_type = FUNC_FUNC;
        func_def->type.func_def.nparam = 1;
        func_def->type.func_def.param_names = malloc(sizeof(Str *));
        func_def->type.func_def.param_names[0] = Str_new("self");
        func_def->type.func_def.param_types = malloc(sizeof(Str *));
        func_def->type.func_def.param_types[0] = sname;
        func_def->type.func_def.param_muts = calloc(1, sizeof(bool));
        func_def->type.func_def.param_owns = calloc(1, sizeof(bool));
        func_def->type.func_def.param_defaults = calloc(1, sizeof(Expr *));
        func_def->type.func_def.return_type = sname;
        func_def->type.func_def.variadic_index = -1;
        expr_add_child(func_def, func_body);

        // clone := func(...)  (namespace decl)
        Expr *decl = expr_new(NODE_DECL, line, col, path);
        decl->type.decl.name = Str_new("clone");
        decl->type.decl.is_namespace = true;
        decl->type.decl.is_mut = false;
        decl->type.decl.explicit_type = NULL;
        expr_add_child(decl, func_def);

        // Add to struct body
        expr_add_child(body, decl);
        Vec_delete(&field_names, &(Bool){0});
        Vec_delete(&field_refs, &(Bool){0});
    }

    // Pass 1.7: auto-generate delete methods for all structs
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        if (expr_child(stmt, 0)->type.tag != NODE_STRUCT_DEF) continue;

        Str *sname = stmt->type.decl.name;

        // Skip meta-types and core ext_structs (C side provides delete)
        if (Str_eq_c(sname, "StructDef") ||
            Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        Expr *sdef = expr_child(stmt, 0);
        if (sdef->is_ext && stmt->is_core) continue;

        Expr *body = expr_child(sdef, 0); // NODE_BODY

        // Check if delete already exists in namespace
        Bool has_delete = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (field->type.tag == NODE_DECL && field->type.decl.is_namespace &&
                Str_eq_c(field->type.decl.name, "delete")) {
                has_delete = 1;
                break;
            }
        }
        if (has_delete) continue;

        // Collect instance field names and own flags
        Vec field_names; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); field_names = *_vp; free(_vp); }
        Vec field_owns; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(I32)}); field_owns = *_vp; free(_vp); }
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (field->type.tag == NODE_DECL && !field->type.decl.is_namespace &&
                !field->type.decl.is_ref) {
                { Str **_p = malloc(sizeof(Str *)); *_p = field->type.decl.name; Vec_push(&field_names, _p); }
                { I32 *_p = malloc(sizeof(I32)); *_p = field->type.decl.is_own; Vec_push(&field_owns, _p); }
            }
        }

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = stmt->path;
        Expr *proc_body = expr_new(NODE_BODY, line, col, path);

        // For each field: self.field.delete(call_free=<true for own, false for inline>)
        for (U32 j = 0; j < field_names.count; j++) {
            Str *fname = *(Str **)Vec_get(&field_names, &(U64){(U64)(j)});
            I32 fown = *(I32 *)Vec_get(&field_owns, &(U64){(U64)(j)});
            Expr *self_id = expr_new(NODE_IDENT, line, col, path);
            self_id->type.str_val = Str_new("self");
            Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
            field_acc->type.str_val = fname;
            field_acc->is_own_arg = true; // delete takes own self
            expr_add_child(field_acc, self_id);

            Expr *del_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
            del_acc->type.str_val = Str_new("delete");
            expr_add_child(del_acc, field_acc);
            Expr *del_call = expr_new(NODE_FCALL, line, col, path);
            expr_add_child(del_call, del_acc);

            // call_free=true for own fields (separate allocation), false for inline
            Expr *cf_lit = expr_new(NODE_LITERAL_BOOL, line, col, path);
            cf_lit->type.str_val = Str_new(fown ? "true" : "false");
            expr_add_child(del_call, cf_lit);

            expr_add_child(proc_body, del_call);
        }

        // if call_free { free(own self) }
        Expr *cond = expr_new(NODE_IDENT, line, col, path);
        cond->type.str_val = Str_new("call_free");
        Expr *then_body = expr_new(NODE_BODY, line, col, path);
        Expr *free_call = expr_new(NODE_FCALL, line, col, path);
        Expr *free_id = expr_new(NODE_IDENT, line, col, path);
        free_id->type.str_val = Str_new("free");
        expr_add_child(free_call, free_id);
        Expr *self_arg = expr_new(NODE_IDENT, line, col, path);
        self_arg->type.str_val = Str_new("self");
        self_arg->is_own_arg = true;
        expr_add_child(free_call, self_arg);
        expr_add_child(then_body, free_call);
        Expr *if_node = expr_new(NODE_IF, line, col, path);
        expr_add_child(if_node, cond);
        expr_add_child(if_node, then_body);
        expr_add_child(proc_body, if_node);

        // proc def: delete(own self: Type, call_free: Bool = true)
        Expr *default_true = expr_new(NODE_LITERAL_BOOL, line, col, path);
        default_true->type.str_val = Str_new("true");

        Expr *proc_def = expr_new(NODE_FUNC_DEF, line, col, path);
        proc_def->is_core = true; // auto-generated, not user code
        proc_def->type.func_def.func_type = FUNC_PROC;
        proc_def->type.func_def.nparam = 2;
        proc_def->type.func_def.param_names = malloc(2 * sizeof(Str *));
        proc_def->type.func_def.param_names[0] = Str_new("self");
        proc_def->type.func_def.param_names[1] = Str_new("call_free");
        proc_def->type.func_def.param_types = malloc(2 * sizeof(Str *));
        proc_def->type.func_def.param_types[0] = sname;
        proc_def->type.func_def.param_types[1] = Str_new("Bool");
        proc_def->type.func_def.param_muts = calloc(2, sizeof(bool));
        proc_def->type.func_def.param_owns = calloc(2, sizeof(bool));
        proc_def->type.func_def.param_owns[0] = true;
        proc_def->type.func_def.param_defaults = calloc(2, sizeof(Expr *));
        proc_def->type.func_def.param_defaults[1] = default_true;
        proc_def->type.func_def.return_type = NULL;
        proc_def->type.func_def.variadic_index = -1;
        expr_add_child(proc_def, proc_body);

        // delete := proc(...)  (namespace decl)
        Expr *decl = expr_new(NODE_DECL, line, col, path);
        decl->type.decl.name = Str_new("delete");
        decl->type.decl.is_namespace = true;
        decl->type.decl.is_mut = false;
        decl->type.decl.explicit_type = NULL;
        expr_add_child(decl, proc_def);

        // Add to struct body
        expr_add_child(body, decl);
        Vec_delete(&field_names, &(Bool){0});
        Vec_delete(&field_owns, &(Bool){0});
    }

    // Pass 1.8: register enum definitions, generate variants + methods
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        if (expr_child(stmt, 0)->type.tag != NODE_ENUM_DEF) continue;

        Str *ename = stmt->type.decl.name;
        I32 line = stmt->line, col = stmt->col;
        Str *path = stmt->path;

        // Register in type scope
        tscope_set(scope, ename, TIL_TYPE_ENUM, -1, 0, line, col, 0, 0);
        TypeBinding *b = tscope_find(scope, ename);
        b->struct_def = expr_child(stmt, 0);

        Expr *body = expr_child(expr_child(stmt, 0), 0); // NODE_BODY

        // Collect variant info (names + optional payload types)
        Vec variant_names; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); variant_names = *_vp; free(_vp); }
        Vec variant_types; { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); variant_types = *_vp; free(_vp); } // NULL entries for no-payload
        Bool has_payloads = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            if (expr_child(body, j)->type.decl.is_namespace) continue;
            { Str **_p = malloc(sizeof(Str *)); *_p = expr_child(body, j)->type.decl.name; Vec_push(&variant_names, _p); }
            { Str **_p = malloc(sizeof(Str *)); *_p = expr_child(body, j)->type.decl.explicit_type; Vec_push(&variant_types, _p); }
            if (expr_child(body, j)->type.decl.explicit_type) has_payloads = 1;
        }

        if (!has_payloads) {
            // === SIMPLE ENUM (Phase 1 path — no payloads) ===
            // Keep original variant markers as registry (don't compact)

            // Add I64 namespace fields for each variant
            for (U32 j = 0; j < variant_names.count; j++) {
                Expr *lit = expr_new(NODE_LITERAL_NUM, line, col, path);
                char buf[16];
                snprintf(buf, sizeof(buf), "%d", j);
                lit->type.str_val = Str_new(buf);
                Expr *decl = expr_new(NODE_DECL, line, col, path);
                decl->type.decl.name = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                decl->type.decl.is_namespace = true;
                expr_add_child(decl, lit);
                expr_add_child(body, decl);
            }
        } else {
            // === PAYLOAD ENUM (Phase 2 path) ===
            // Keep original variant markers as registry (don't compact)

            for (U32 j = 0; j < variant_names.count; j++) {
                if (*(Str **)Vec_get(&variant_types, &(U64){(U64)(j)})) {
                    // Payload variant: ext_func constructor
                    // e.g. Num := ext_func(val: I64) returns Token {}
                    Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
                    fdef->type.func_def.func_type = FUNC_EXT_FUNC;
                    fdef->type.func_def.nparam = 1;
                    fdef->type.func_def.param_names = malloc(sizeof(Str *));
                    fdef->type.func_def.param_names[0] = Str_new("val");
                    fdef->type.func_def.param_types = malloc(sizeof(Str *));
                    fdef->type.func_def.param_types[0] = *(Str **)Vec_get(&variant_types, &(U64){(U64)(j)});
                    fdef->type.func_def.param_muts = calloc(1, sizeof(bool));
                    fdef->type.func_def.param_owns = calloc(1, sizeof(bool));
                    fdef->type.func_def.param_defaults = calloc(1, sizeof(Expr *));
                    fdef->type.func_def.return_type = ename;
                    fdef->type.func_def.variadic_index = -1;
                    expr_add_child(fdef, expr_new(NODE_BODY, line, col, path));
                    Expr *decl = expr_new(NODE_DECL, line, col, path);
                    decl->type.decl.name = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                    decl->type.decl.is_namespace = true;
                    expr_add_child(decl, fdef);
                    expr_add_child(body, decl);
                } else {
                    // No-payload variant: zero-arg ext_func constructor
                    // e.g. Eof := ext_func() returns Token {}
                    Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
                    fdef->type.func_def.func_type = FUNC_EXT_FUNC;
                    fdef->type.func_def.nparam = 0;
                    fdef->type.func_def.param_names = NULL;
                    fdef->type.func_def.param_types = NULL;
                    fdef->type.func_def.param_muts = NULL;
                    fdef->type.func_def.param_owns = NULL;
                    fdef->type.func_def.param_defaults = NULL;
                    fdef->type.func_def.return_type = ename;
                    fdef->type.func_def.variadic_index = -1;
                    expr_add_child(fdef, expr_new(NODE_BODY, line, col, path));
                    Expr *decl = expr_new(NODE_DECL, line, col, path);
                    decl->type.decl.name = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                    decl->type.decl.is_namespace = true;
                    expr_add_child(decl, fdef);
                    expr_add_child(body, decl);
                }
            }

            // Generate get_Variant ext_func for payload variants
            for (U32 j = 0; j < variant_names.count; j++) {
                if (!*(Str **)Vec_get(&variant_types, &(U64){(U64)(j)})) continue;
                char name_buf[256];
                snprintf(name_buf, sizeof(name_buf), "get_%s", (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
                fdef->type.func_def.func_type = FUNC_EXT_FUNC;
                fdef->type.func_def.nparam = 1;
                fdef->type.func_def.param_names = malloc(sizeof(Str *));
                fdef->type.func_def.param_names[0] = Str_new("self");
                fdef->type.func_def.param_types = malloc(sizeof(Str *));
                fdef->type.func_def.param_types[0] = ename;
                fdef->type.func_def.param_muts = calloc(1, sizeof(bool));
                fdef->type.func_def.param_owns = calloc(1, sizeof(bool));
                fdef->type.func_def.param_defaults = calloc(1, sizeof(Expr *));
                fdef->type.func_def.return_type = *(Str **)Vec_get(&variant_types, &(U64){(U64)(j)});
                fdef->type.func_def.variadic_index = -1;
                expr_add_child(fdef, expr_new(NODE_BODY, line, col, path));
                Expr *decl = expr_new(NODE_DECL, line, col, path);
                decl->type.decl.name = Str_new(name_buf);
                decl->type.decl.is_namespace = true;
                expr_add_child(decl, fdef);
                expr_add_child(body, decl);
            }
        }

        // Generate is_Variant ext_func for every variant (all enums)
        for (U32 j = 0; j < variant_names.count; j++) {
            char name_buf[256];
            snprintf(name_buf, sizeof(name_buf), "is_%s", (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
            Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
            fdef->type.func_def.func_type = FUNC_EXT_FUNC;
            fdef->type.func_def.nparam = 1;
            fdef->type.func_def.param_names = malloc(sizeof(Str *));
            fdef->type.func_def.param_names[0] = Str_new("self");
            fdef->type.func_def.param_types = malloc(sizeof(Str *));
            fdef->type.func_def.param_types[0] = ename;
            fdef->type.func_def.param_muts = calloc(1, sizeof(bool));
            fdef->type.func_def.param_owns = calloc(1, sizeof(bool));
            fdef->type.func_def.param_defaults = calloc(1, sizeof(Expr *));
            fdef->type.func_def.return_type = Str_new("Bool");
            fdef->type.func_def.variadic_index = -1;
            expr_add_child(fdef, expr_new(NODE_BODY, line, col, path));
            Expr *decl = expr_new(NODE_DECL, line, col, path);
            decl->type.decl.name = Str_new(name_buf);
            decl->type.decl.is_namespace = true;
            expr_add_child(decl, fdef);
            expr_add_child(body, decl);
        }

        // Check existing methods
        Bool has_eq = 0, has_clone = 0, has_delete = 0, has_to_str = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = expr_child(body, j);
            if (f->type.tag != NODE_DECL || !f->type.decl.is_namespace) continue;
            if (f->children.count == 0 || expr_child(f, 0)->type.tag != NODE_FUNC_DEF) continue;
            if (Str_eq_c(f->type.decl.name, "eq")) has_eq = 1;
            if (Str_eq_c(f->type.decl.name, "clone")) has_clone = 1;
            if (Str_eq_c(f->type.decl.name, "delete")) has_delete = 1;
            if (Str_eq_c(f->type.decl.name, "to_str")) has_to_str = 1;
        }

        // Auto-generate eq := func(self: E, other: E) returns Bool { if-chain }
        // Uses is_Variant() for all variants, get_Variant().eq() for payloads
        if (!has_eq) {
            Expr *func_body = expr_new(NODE_BODY, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                // Build self.is_Vj() call
                Expr *self_id = expr_new(NODE_IDENT, line, col, path);
                self_id->type.str_val = Str_new("self");
                char is_buf[256];
                snprintf(is_buf, sizeof(is_buf), "is_%s",
                         (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                Expr *is_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                is_acc->type.str_val = Str_new(is_buf);
                expr_add_child(is_acc, self_id);
                Expr *is_call = expr_new(NODE_FCALL, line, col, path);
                expr_add_child(is_call, is_acc);

                Expr *then_body = expr_new(NODE_BODY, line, col, path);

                if (*(Str **)Vec_get(&variant_types, &(U64){(U64)(j)})) {
                    // Payload variant:
                    //   if other.is_Vj().not() { return false }
                    //   return self.get_Vj().eq(other.get_Vj())
                    Expr *other_id = expr_new(NODE_IDENT, line, col, path);
                    other_id->type.str_val = Str_new("other");
                    Expr *is_acc2 = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    is_acc2->type.str_val = Str_new(is_buf);
                    expr_add_child(is_acc2, other_id);
                    Expr *is_call2 = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(is_call2, is_acc2);
                    Expr *not_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    not_acc->type.str_val = Str_new("not");
                    expr_add_child(not_acc, is_call2);
                    Expr *not_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(not_call, not_acc);

                    Expr *ret_false = expr_new(NODE_RETURN, line, col, path);
                    Expr *false_lit = expr_new(NODE_LITERAL_BOOL, line, col, path);
                    false_lit->type.str_val = Str_new("false");
                    expr_add_child(ret_false, false_lit);
                    Expr *guard_body = expr_new(NODE_BODY, line, col, path);
                    expr_add_child(guard_body, ret_false);
                    Expr *guard_if = expr_new(NODE_IF, line, col, path);
                    expr_add_child(guard_if, not_call);
                    expr_add_child(guard_if, guard_body);
                    expr_add_child(then_body, guard_if);

                    // return self.get_Vj().eq(other.get_Vj())
                    char get_buf[256];
                    snprintf(get_buf, sizeof(get_buf), "get_%s",
                             (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                    Expr *self2 = expr_new(NODE_IDENT, line, col, path);
                    self2->type.str_val = Str_new("self");
                    Expr *get_acc1 = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    get_acc1->type.str_val = Str_new(get_buf);
                    expr_add_child(get_acc1, self2);
                    Expr *get_call1 = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(get_call1, get_acc1);

                    Expr *eq_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    eq_acc->type.str_val = Str_new("eq");
                    expr_add_child(eq_acc, get_call1);

                    Expr *other2 = expr_new(NODE_IDENT, line, col, path);
                    other2->type.str_val = Str_new("other");
                    Expr *get_acc2 = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    get_acc2->type.str_val = Str_new(get_buf);
                    expr_add_child(get_acc2, other2);
                    Expr *get_call2 = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(get_call2, get_acc2);

                    Expr *eq_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(eq_call, eq_acc);
                    expr_add_child(eq_call, get_call2);

                    Expr *ret_eq = expr_new(NODE_RETURN, line, col, path);
                    expr_add_child(ret_eq, eq_call);
                    expr_add_child(then_body, ret_eq);
                } else {
                    // No-payload variant: return other.is_Vj()
                    Expr *other_id = expr_new(NODE_IDENT, line, col, path);
                    other_id->type.str_val = Str_new("other");
                    Expr *is_acc2 = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    is_acc2->type.str_val = Str_new(is_buf);
                    expr_add_child(is_acc2, other_id);
                    Expr *is_call2 = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(is_call2, is_acc2);
                    Expr *ret = expr_new(NODE_RETURN, line, col, path);
                    expr_add_child(ret, is_call2);
                    expr_add_child(then_body, ret);
                }

                Expr *if_node = expr_new(NODE_IF, line, col, path);
                expr_add_child(if_node, is_call);
                expr_add_child(if_node, then_body);
                expr_add_child(func_body, if_node);
            }
            // return false
            Expr *ret_false = expr_new(NODE_RETURN, line, col, path);
            Expr *false_lit = expr_new(NODE_LITERAL_BOOL, line, col, path);
            false_lit->type.str_val = Str_new("false");
            expr_add_child(ret_false, false_lit);
            expr_add_child(func_body, ret_false);

            Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
            fdef->type.func_def.func_type = FUNC_FUNC;
            fdef->type.func_def.nparam = 2;
            fdef->type.func_def.param_names = malloc(2 * sizeof(Str *));
            fdef->type.func_def.param_names[0] = Str_new("self");
            fdef->type.func_def.param_names[1] = Str_new("other");
            fdef->type.func_def.param_types = malloc(2 * sizeof(Str *));
            fdef->type.func_def.param_types[0] = ename;
            fdef->type.func_def.param_types[1] = ename;
            fdef->type.func_def.param_muts = calloc(2, sizeof(bool));
            fdef->type.func_def.param_owns = calloc(2, sizeof(bool));
            fdef->type.func_def.param_defaults = calloc(2, sizeof(Expr *));
            fdef->type.func_def.return_type = Str_new("Bool");
            fdef->type.func_def.variadic_index = -1;
            expr_add_child(fdef, func_body);

            Expr *decl = expr_new(NODE_DECL, line, col, path);
            decl->type.decl.name = Str_new("eq");
            decl->type.decl.is_namespace = true;
            expr_add_child(decl, fdef);
            expr_add_child(body, decl);
        }

        // Auto-generate clone := func(self: E) returns E { if-chain }
        // Payload: if self.is_V() { return E.V(self.get_V()) } ... return E.Vn()
        // Simple:  if self.eq(E.V()) { return E.V() } ... return E.Vn()
        if (!has_clone) {
            Expr *func_body = expr_new(NODE_BODY, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                // Build variant expression: E.V(self.get_V()) for payload, E.V for no-payload
                Expr *ename_id = expr_new(NODE_IDENT, line, col, path);
                ename_id->type.str_val = ename;
                Expr *ctor_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                ctor_acc->type.str_val = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                expr_add_child(ctor_acc, ename_id);

                Expr *ctor_expr;
                if (*(Str **)Vec_get(&variant_types, &(U64){(U64)(j)})) {
                    // Payload variant: E.V(self.get_V())
                    Expr *ctor_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(ctor_call, ctor_acc);
                    Expr *self_g = expr_new(NODE_IDENT, line, col, path);
                    self_g->type.str_val = Str_new("self");
                    char get_buf[256];
                    snprintf(get_buf, sizeof(get_buf), "get_%s",
                             (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                    Expr *get_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    get_acc->type.str_val = Str_new(get_buf);
                    expr_add_child(get_acc, self_g);
                    Expr *get_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(get_call, get_acc);
                    expr_add_child(ctor_call, get_call);
                    ctor_expr = ctor_call;
                } else {
                    // No-payload variant: bare E.V (auto-called at runtime)
                    ctor_expr = ctor_acc;
                }

                Expr *ret = expr_new(NODE_RETURN, line, col, path);
                expr_add_child(ret, ctor_expr);

                if (j < variant_names.count - 1) {
                    // Condition: payload uses is_V(), simple uses eq(E.V())
                    Expr *cond;
                    if (has_payloads) {
                        Expr *self_id = expr_new(NODE_IDENT, line, col, path);
                        self_id->type.str_val = Str_new("self");
                        char is_buf[256];
                        snprintf(is_buf, sizeof(is_buf), "is_%s",
                                 (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                        Expr *is_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                        is_acc->type.str_val = Str_new(is_buf);
                        expr_add_child(is_acc, self_id);
                        cond = expr_new(NODE_FCALL, line, col, path);
                        expr_add_child(cond, is_acc);
                    } else {
                        // self.eq(E.V) — bare field access as eq arg
                        Expr *self_id = expr_new(NODE_IDENT, line, col, path);
                        self_id->type.str_val = Str_new("self");
                        Expr *eq_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                        eq_acc->type.str_val = Str_new("eq");
                        expr_add_child(eq_acc, self_id);

                        Expr *en2 = expr_new(NODE_IDENT, line, col, path);
                        en2->type.str_val = ename;
                        Expr *va2 = expr_new(NODE_FIELD_ACCESS, line, col, path);
                        va2->type.str_val = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                        expr_add_child(va2, en2);

                        cond = expr_new(NODE_FCALL, line, col, path);
                        expr_add_child(cond, eq_acc);
                        expr_add_child(cond, va2);
                    }

                    Expr *then_body = expr_new(NODE_BODY, line, col, path);
                    expr_add_child(then_body, ret);

                    Expr *if_node = expr_new(NODE_IF, line, col, path);
                    expr_add_child(if_node, cond);
                    expr_add_child(if_node, then_body);
                    expr_add_child(func_body, if_node);
                } else {
                    // Last variant: bare return
                    expr_add_child(func_body, ret);
                }
            }

            Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
            fdef->type.func_def.func_type = FUNC_FUNC;
            fdef->type.func_def.nparam = 1;
            fdef->type.func_def.param_names = malloc(sizeof(Str *));
            fdef->type.func_def.param_names[0] = Str_new("self");
            fdef->type.func_def.param_types = malloc(sizeof(Str *));
            fdef->type.func_def.param_types[0] = ename;
            fdef->type.func_def.param_muts = calloc(1, sizeof(bool));
            fdef->type.func_def.param_owns = calloc(1, sizeof(bool));
            fdef->type.func_def.param_defaults = calloc(1, sizeof(Expr *));
            fdef->type.func_def.return_type = ename;
            fdef->type.func_def.variadic_index = -1;
            expr_add_child(fdef, func_body);

            Expr *decl = expr_new(NODE_DECL, line, col, path);
            decl->type.decl.name = Str_new("clone");
            decl->type.decl.is_namespace = true;
            expr_add_child(decl, fdef);
            expr_add_child(body, decl);
        }

        // Auto-generate delete for all enums (same pattern):
        // delete := proc(own self: E, call_free: Bool = true) {
        //     if call_free { free(own self) }
        // }
        // free() builtin handles payload cleanup for VAL_ENUM
        if (!has_delete) {
            Expr *proc_body = expr_new(NODE_BODY, line, col, path);
            Expr *cond = expr_new(NODE_IDENT, line, col, path);
            cond->type.str_val = Str_new("call_free");
            Expr *then_body = expr_new(NODE_BODY, line, col, path);
            Expr *free_call = expr_new(NODE_FCALL, line, col, path);
            Expr *free_id = expr_new(NODE_IDENT, line, col, path);
            free_id->type.str_val = Str_new("free");
            expr_add_child(free_call, free_id);
            Expr *self_arg = expr_new(NODE_IDENT, line, col, path);
            self_arg->type.str_val = Str_new("self");
            self_arg->is_own_arg = true;
            expr_add_child(free_call, self_arg);
            expr_add_child(then_body, free_call);
            Expr *if_node = expr_new(NODE_IF, line, col, path);
            expr_add_child(if_node, cond);
            expr_add_child(if_node, then_body);
            expr_add_child(proc_body, if_node);

            Expr *default_true = expr_new(NODE_LITERAL_BOOL, line, col, path);
            default_true->type.str_val = Str_new("true");
            Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
            fdef->is_core = true; // auto-generated, not user code
            fdef->type.func_def.func_type = FUNC_PROC;
            fdef->type.func_def.nparam = 2;
            fdef->type.func_def.param_names = malloc(2 * sizeof(Str *));
            fdef->type.func_def.param_names[0] = Str_new("self");
            fdef->type.func_def.param_names[1] = Str_new("call_free");
            fdef->type.func_def.param_types = malloc(2 * sizeof(Str *));
            fdef->type.func_def.param_types[0] = ename;
            fdef->type.func_def.param_types[1] = Str_new("Bool");
            fdef->type.func_def.param_muts = calloc(2, sizeof(bool));
            fdef->type.func_def.param_owns = calloc(2, sizeof(bool));
            fdef->type.func_def.param_owns[0] = true;
            fdef->type.func_def.param_defaults = calloc(2, sizeof(Expr *));
            fdef->type.func_def.param_defaults[1] = default_true;
            fdef->type.func_def.return_type = NULL;
            fdef->type.func_def.variadic_index = -1;
            expr_add_child(fdef, proc_body);
            Expr *decl = expr_new(NODE_DECL, line, col, path);
            decl->type.decl.name = Str_new("delete");
            decl->type.decl.is_namespace = true;
            expr_add_child(decl, fdef);
            expr_add_child(body, decl);
        }

        // Auto-generate to_str := func(self: E) returns Str { if-chain }
        if (!has_to_str) {
            Expr *func_body = expr_new(NODE_BODY, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                if (has_payloads) {
                    // Payload enum to_str uses is_/get_ methods
                    // if self.is_Variant() { ... }
                    Expr *self_id = expr_new(NODE_IDENT, line, col, path);
                    self_id->type.str_val = Str_new("self");
                    char is_buf[256];
                    snprintf(is_buf, sizeof(is_buf), "is_%s", (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                    Expr *is_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    is_acc->type.str_val = Str_new(is_buf);
                    expr_add_child(is_acc, self_id);
                    Expr *is_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(is_call, is_acc);

                    Expr *then_body = expr_new(NODE_BODY, line, col, path);
                    if (*(Str **)Vec_get(&variant_types, &(U64){(U64)(j)})) {
                        // return format("Variant(", self.get_Variant().to_str(), ")")
                        Expr *fmt_call = expr_new(NODE_FCALL, line, col, path);
                        Expr *fmt_id = expr_new(NODE_IDENT, line, col, path);
                        fmt_id->type.str_val = Str_new("format");
                        expr_add_child(fmt_call, fmt_id);

                        char prefix_buf[256];
                        snprintf(prefix_buf, sizeof(prefix_buf), "%s(", (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                        Expr *prefix = expr_new(NODE_LITERAL_STR, line, col, path);
                        prefix->type.str_val = Str_new(prefix_buf);
                        expr_add_child(fmt_call, prefix);

                        // self.get_Variant().to_str()
                        Expr *self2 = expr_new(NODE_IDENT, line, col, path);
                        self2->type.str_val = Str_new("self");
                        char get_buf[256];
                        snprintf(get_buf, sizeof(get_buf), "get_%s", (*(Str **)Vec_get(&variant_names, &(U64){(U64)(j)}))->c_str);
                        Expr *get_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                        get_acc->type.str_val = Str_new(get_buf);
                        expr_add_child(get_acc, self2);
                        Expr *get_call = expr_new(NODE_FCALL, line, col, path);
                        expr_add_child(get_call, get_acc);
                        Expr *tostr_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                        tostr_acc->type.str_val = Str_new("to_str");
                        expr_add_child(tostr_acc, get_call);
                        Expr *tostr_call = expr_new(NODE_FCALL, line, col, path);
                        expr_add_child(tostr_call, tostr_acc);
                        expr_add_child(fmt_call, tostr_call);

                        Expr *suffix = expr_new(NODE_LITERAL_STR, line, col, path);
                        suffix->type.str_val = Str_new(")");
                        expr_add_child(fmt_call, suffix);

                        Expr *ret = expr_new(NODE_RETURN, line, col, path);
                        expr_add_child(ret, fmt_call);
                        expr_add_child(then_body, ret);
                    } else {
                        // return "VariantName"
                        Expr *ret_str = expr_new(NODE_LITERAL_STR, line, col, path);
                        ret_str->type.str_val = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                        Expr *ret = expr_new(NODE_RETURN, line, col, path);
                        expr_add_child(ret, ret_str);
                        expr_add_child(then_body, ret);
                    }

                    Expr *if_node = expr_new(NODE_IF, line, col, path);
                    expr_add_child(if_node, is_call);
                    expr_add_child(if_node, then_body);
                    expr_add_child(func_body, if_node);
                } else {
                    // Simple enum: if self.eq(EnumName.VariantName) { return "VariantName" }
                    Expr *self_id = expr_new(NODE_IDENT, line, col, path);
                    self_id->type.str_val = Str_new("self");
                    Expr *eq_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    eq_acc->type.str_val = Str_new("eq");
                    expr_add_child(eq_acc, self_id);

                    // EnumName.VariantName (bare field access)
                    Expr *ename_id = expr_new(NODE_IDENT, line, col, path);
                    ename_id->type.str_val = ename;
                    Expr *var_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
                    var_acc->type.str_val = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                    expr_add_child(var_acc, ename_id);

                    Expr *eq_call = expr_new(NODE_FCALL, line, col, path);
                    expr_add_child(eq_call, eq_acc);
                    expr_add_child(eq_call, var_acc);

                    Expr *ret_str = expr_new(NODE_LITERAL_STR, line, col, path);
                    ret_str->type.str_val = *(Str **)Vec_get(&variant_names, &(U64){(U64)(j)});
                    Expr *ret = expr_new(NODE_RETURN, line, col, path);
                    expr_add_child(ret, ret_str);
                    Expr *then_body = expr_new(NODE_BODY, line, col, path);
                    expr_add_child(then_body, ret);

                    Expr *if_node = expr_new(NODE_IF, line, col, path);
                    expr_add_child(if_node, eq_call);
                    expr_add_child(if_node, then_body);
                    expr_add_child(func_body, if_node);
                }
            }
            // return "unknown"
            Expr *unk = expr_new(NODE_LITERAL_STR, line, col, path);
            unk->type.str_val = Str_new("unknown");
            Expr *ret_unk = expr_new(NODE_RETURN, line, col, path);
            expr_add_child(ret_unk, unk);
            expr_add_child(func_body, ret_unk);

            Expr *fdef = expr_new(NODE_FUNC_DEF, line, col, path);
            fdef->type.func_def.func_type = FUNC_FUNC;
            fdef->type.func_def.nparam = 1;
            fdef->type.func_def.param_names = malloc(sizeof(Str *));
            fdef->type.func_def.param_names[0] = Str_new("self");
            fdef->type.func_def.param_types = malloc(sizeof(Str *));
            fdef->type.func_def.param_types[0] = ename;
            fdef->type.func_def.param_muts = calloc(1, sizeof(bool));
            fdef->type.func_def.param_owns = calloc(1, sizeof(bool));
            fdef->type.func_def.param_defaults = calloc(1, sizeof(Expr *));
            fdef->type.func_def.return_type = Str_new("Str");
            fdef->type.func_def.variadic_index = -1;
            expr_add_child(fdef, func_body);

            Expr *decl = expr_new(NODE_DECL, line, col, path);
            decl->type.decl.name = Str_new("to_str");
            decl->type.decl.is_namespace = true;
            expr_add_child(decl, fdef);
            expr_add_child(body, decl);
        }

        Vec_delete(&variant_names, &(Bool){0});
        Vec_delete(&variant_types, &(Bool){0});
    }

    // Pass 1.9: compute flat struct layout (field offsets and sizes)
    // Must run BEFORE size method synthesis so total_struct_size is available
    compute_all_struct_layouts(program, scope);

    // Pass 1.92: auto-generate size methods for structs and enums
    // Uses total_struct_size computed above for correct values (includes alignment padding)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        Expr *def = expr_child(stmt, 0);
        if (def->type.tag != NODE_STRUCT_DEF && def->type.tag != NODE_ENUM_DEF) continue;

        Str *sname = stmt->type.decl.name;

        // Skip meta-types
        if (Str_eq_c(sname, "StructDef") ||
            Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        // Skip core ext_structs (they define size in core.til)
        if (def->is_ext && stmt->is_core) continue;

        Expr *body = expr_child(def, 0); // NODE_BODY

        // Check if size already exists in namespace
        Bool has_size = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = expr_child(body, j);
            if (field->type.tag == NODE_DECL && field->type.decl.is_namespace &&
                Str_eq_c(field->type.decl.name, "size")) {
                has_size = 1;
                break;
            }
        }
        if (has_size) continue;

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = stmt->path;

        // Use computed total_struct_size for structs, 8 for enums (I64 or pointer)
        I32 sz = def->type.tag == NODE_ENUM_DEF
            ? (enum_has_payloads(def) ? 8 : 4)
            : def->total_struct_size;
        char sz_buf[16];
        snprintf(sz_buf, sizeof(sz_buf), "%d", sz);

        // size := func() returns U64 { return <literal> }
        Expr *func_body = expr_new(NODE_BODY, line, col, path);
        Expr *size_expr = expr_new(NODE_LITERAL_NUM, line, col, path);
        size_expr->type.str_val = Str_new(sz_buf);
        Expr *ret = expr_new(NODE_RETURN, line, col, path);
        expr_add_child(ret, size_expr);
        expr_add_child(func_body, ret);

        Expr *func_def = expr_new(NODE_FUNC_DEF, line, col, path);
        func_def->type.func_def.func_type = FUNC_FUNC;
        func_def->type.func_def.nparam = 0;
        func_def->type.func_def.param_names = NULL;
        func_def->type.func_def.param_types = NULL;
        func_def->type.func_def.param_muts = NULL;
        func_def->type.func_def.param_owns = NULL;
        func_def->type.func_def.param_defaults = NULL;
        func_def->type.func_def.return_type = Str_new("U64");
        func_def->type.func_def.variadic_index = -1;
        expr_add_child(func_def, func_body);

        Expr *decl = expr_new(NODE_DECL, line, col, path);
        decl->type.decl.name = Str_new("size");
        decl->type.decl.is_namespace = true;
        decl->type.decl.is_mut = false;
        decl->type.decl.explicit_type = NULL;
        expr_add_child(decl, func_def);

        expr_add_child(body, decl);
    }

    // Pass 1.95: auto-generate comparison methods from cmp
    // Any struct/enum with cmp gets: eq, neq, lt, gt, lte, gte (if missing)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        Expr *def = expr_child(stmt, 0);
        if (def->type.tag != NODE_STRUCT_DEF && def->type.tag != NODE_ENUM_DEF) continue;

        Str *sname = stmt->type.decl.name;
        if (Str_eq_c(sname, "StructDef") || Str_eq_c(sname, "FunctionDef") ||
            Str_eq_c(sname, "Dynamic")) continue;

        Expr *body = expr_child(def, 0);
        Bool has_cmp = 0, has_eq = 0, has_neq = 0;
        Bool has_lt = 0, has_gt = 0, has_lte = 0, has_gte = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = expr_child(body, j);
            if (f->type.tag != NODE_DECL || !f->type.decl.is_namespace) continue;
            if (f->children.count == 0 || expr_child(f, 0)->type.tag != NODE_FUNC_DEF) continue;
            if (Str_eq_c(f->type.decl.name, "cmp")) has_cmp = 1;
            if (Str_eq_c(f->type.decl.name, "eq")) has_eq = 1;
            if (Str_eq_c(f->type.decl.name, "neq")) has_neq = 1;
            if (Str_eq_c(f->type.decl.name, "lt")) has_lt = 1;
            if (Str_eq_c(f->type.decl.name, "gt")) has_gt = 1;
            if (Str_eq_c(f->type.decl.name, "lte")) has_lte = 1;
            if (Str_eq_c(f->type.decl.name, "gte")) has_gte = 1;
        }
        if (!has_cmp) continue;

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = stmt->path;

        // Helper macros for building AST nodes inline
        #define MK(type) expr_new(type, line, col, path)
        #define ID(s) ({ Expr *_e = MK(NODE_IDENT); _e->type.str_val = Str_new(s); _e; })
        #define NUM(s) ({ Expr *_e = MK(NODE_LITERAL_NUM); _e->type.str_val = Str_new(s); _e; })
        #define ACC(obj, field) ({ Expr *_e = MK(NODE_FIELD_ACCESS); _e->type.str_val = Str_new(field); expr_add_child(_e, obj); _e; })
        #define CALL0(callee) ({ Expr *_e = MK(NODE_FCALL); expr_add_child(_e, callee); _e; })
        #define CALL1(callee, arg1) ({ Expr *_e = MK(NODE_FCALL); expr_add_child(_e, callee); expr_add_child(_e, arg1); _e; })
        #define RET(val) ({ Expr *_e = MK(NODE_RETURN); expr_add_child(_e, val); _e; })

        // a.cmp(b).eq(N) — build: call(acc(call(acc(id("a"), "cmp"), id("b")), "eq"), N)
        #define CMP_EQ(n) RET(CALL1(ACC(CALL1(ACC(ID("a"), "cmp"), ID("b")), "eq"), n))
        // 0.sub(1) for -1
        #define NEG1() CALL1(ACC(NUM("0"), "sub"), NUM("1"))

        // Generate a 2-param func decl in namespace
        #define GEN_CMP_FUNC(method_name, body_expr) do { \
            Expr *fb = MK(NODE_BODY); \
            expr_add_child(fb, body_expr); \
            Expr *fd = MK(NODE_FUNC_DEF); \
            fd->type.func_def.func_type = FUNC_FUNC; \
            fd->type.func_def.nparam = 2; \
            fd->type.func_def.param_names = malloc(2 * sizeof(Str *)); \
            fd->type.func_def.param_names[0] = Str_new("a"); \
            fd->type.func_def.param_names[1] = Str_new("b"); \
            fd->type.func_def.param_types = malloc(2 * sizeof(Str *)); \
            fd->type.func_def.param_types[0] = sname; \
            fd->type.func_def.param_types[1] = sname; \
            fd->type.func_def.param_muts = calloc(2, sizeof(bool)); \
            fd->type.func_def.param_owns = calloc(2, sizeof(bool)); \
            fd->type.func_def.param_defaults = calloc(2, sizeof(Expr *)); \
            fd->type.func_def.return_type = Str_new("Bool"); \
            fd->type.func_def.variadic_index = -1; \
            expr_add_child(fd, fb); \
            Expr *dc = MK(NODE_DECL); \
            dc->type.decl.name = Str_new(method_name); \
            dc->type.decl.is_namespace = true; \
            expr_add_child(dc, fd); \
            expr_add_child(body, dc); \
        } while(0)

        // eq(a, b) → a.cmp(b).eq(0)
        if (!has_eq) {
            GEN_CMP_FUNC("eq", CMP_EQ(NUM("0")));
        }

        // lt(a, b) → a.cmp(b).eq(0.sub(1))
        if (!has_lt) {
            GEN_CMP_FUNC("lt", CMP_EQ(NEG1()));
        }

        // gt(a, b) → a.cmp(b).eq(1)
        if (!has_gt) {
            GEN_CMP_FUNC("gt", CMP_EQ(NUM("1")));
        }

        // neq(a, b) → a.eq(b).not()
        if (!has_neq) {
            GEN_CMP_FUNC("neq", RET(CALL0(ACC(CALL1(ACC(ID("a"), "eq"), ID("b")), "not"))));
        }

        // lte(a, b) → a.gt(b).not()
        if (!has_lte) {
            GEN_CMP_FUNC("lte", RET(CALL0(ACC(CALL1(ACC(ID("a"), "gt"), ID("b")), "not"))));
        }

        // gte(a, b) → a.lt(b).not()
        if (!has_gte) {
            GEN_CMP_FUNC("gte", RET(CALL0(ACC(CALL1(ACC(ID("a"), "lt"), ID("b")), "not"))));
        }

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
    }

    // Pass 2: register all func/proc definitions
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag != NODE_DECL) continue;
        if (expr_child(stmt, 0)->type.tag != NODE_FUNC_DEF) continue;

        FuncType ft = expr_child(stmt, 0)->type.func_def.func_type;
        I32 callee_is_proc = (ft == FUNC_TEST) ? 2 : (ft == FUNC_PROC || ft == FUNC_EXT_PROC) ? 1 : 0;
        TilType rt = TIL_TYPE_NONE;
        if (expr_child(stmt, 0)->type.func_def.return_type) {
            rt = type_from_name_init(expr_child(stmt, 0)->type.func_def.return_type, scope);
        }
        tscope_set(scope, stmt->type.decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
        TypeBinding *fb = tscope_find(scope, stmt->type.decl.name);
        if (fb) {
            fb->func_def = expr_child(stmt, 0);
            if (ft == FUNC_EXT_FUNC || ft == FUNC_EXT_PROC)
                fb->is_builtin = 1;
        }
    }

    return 0;
}
