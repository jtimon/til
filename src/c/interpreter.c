#include "interpreter.h"
#include "../../bootstrap/ast.h"
#include "pre70.h"
#include "dispatch.h"
#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations (defined in ast.c)


// --- Return value mechanism ---
static Bool has_return;
static Bool has_break;
static Bool has_continue;
static Value return_value;

// --- Namespace fields (static struct fields) ---

static Map ns_fields; // Str* "Type.field" → Value
static Vec ns_keys;   // owns the qualified-name Str*s

static Str *ns_qname(Str *sname, Str *fname) {
    U64 len = sname->count + 1 + fname->count;
    char *buf = malloc(len + 1);
    memcpy(buf, sname->c_str, sname->count);
    buf[sname->count] = '.';
    memcpy(buf + sname->count + 1, fname->c_str, fname->count);
    buf[len] = '\0';
    Str *s = Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
    free(buf);
    { Str **_p = malloc(sizeof(Str *)); *_p = s; Vec_push(&ns_keys, _p); }
    return s;
}

Value *ns_get(Str *sname, Str *fname) {
    Str *qn = ns_qname(sname, fname);
    if (!*Map_has(&ns_fields, qn)) return NULL;
    return Map_get(&ns_fields, qn);
}

static void ns_set(Str *sname, Str *fname, Value val) {
    Str *qn = ns_qname(sname, fname);
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){qn->c_str, qn->count, CAP_VIEW}; void *_v = malloc(sizeof(val)); memcpy(_v, &val, sizeof(val)); Map_set(&ns_fields, _k, _v); }
}

// --- Scope / environment ---

Scope *scope_new(Scope *parent) {
    Scope *s = malloc(sizeof(Scope));
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Binding)}); s->bindings = *_mp; free(_mp); }
    s->parent = parent;
    return s;
}

void scope_free(Scope *s) {
    for (U32 i = 0; i < s->bindings.count; i++) {
        Binding *b = (Binding *)(s->bindings.val_data + i * s->bindings.val_size);
        if (b->cell_is_local)
            free(b->cell);
    }
    Map_delete(&s->bindings, &(Bool){0});
    free(s);
}

void scope_set_owned(Scope *s, Str *name, Value val) {
    if (*Map_has(&s->bindings, name)) {
        Binding *b = Map_get(&s->bindings, name);
        b->cell->val = val;
        return;
    }
    Cell *cell = malloc(sizeof(Cell));
    cell->val = val;
    Binding nb = {name, cell, 1};
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW}; void *_v = malloc(sizeof(nb)); memcpy(_v, &nb, sizeof(nb)); Map_set(&s->bindings, _k, _v); }
}

static void scope_set_borrowed(Scope *s, Str *name, Cell *cell) {
    Binding b = {name, cell, 0};
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW}; void *_v = malloc(sizeof(b)); memcpy(_v, &b, sizeof(b)); Map_set(&s->bindings, _k, _v); }
}

Cell *scope_get(Scope *s, Str *name) {
    for (Scope *cur = s; cur; cur = cur->parent) {
        if (*Map_has(&cur->bindings, name)) {
            Binding *b = Map_get(&cur->bindings, name);
            return b->cell;
        }
    }
    return NULL;
}

// ext_function_dispatch is in dispatch.c

// --- Cached struct defs for C-side construction ---
Expr *cached_str_def;
Str *cached_str_name;
Expr *cached_array_def;
Str *cached_array_name;
Expr *cached_vec_def;
Str *cached_vec_name;

// Find a non-namespace field decl by name in a struct_def
Expr *find_field_decl(Expr *struct_def, Str *fname) {
    Expr *body = Expr_child(struct_def, &(I64){(I64)(0)});
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(I64){(I64)(i)});
        if (f->data.tag == ExprData_TAG_Decl && !f->data.data.Decl.is_namespace &&
            *Str_eq(&f->data.data.Decl.name, fname))
            return f;
    }
    return NULL;
}

// Read a Value from flat buffer at a field decl's offset
static Value read_field(StructInstance *inst, Expr *fdecl) {
    void *ptr = (char *)inst->data + fdecl->data.data.Decl.field_offset;
    if (fdecl->data.data.Decl.is_own) {
        void *owned = *(void **)ptr;
        // If the own field has a struct def, wrap in StructInstance for field access
        if (fdecl->data.data.Decl.field_struct_def) {
            Expr *nested = fdecl->data.data.Decl.field_struct_def;
            Str *ftype = &fdecl->data.data.Decl.explicit_type;
            StructInstance *sub = malloc(sizeof(StructInstance));
            sub->struct_name = ftype;
            sub->struct_def = nested;
            sub->data = owned; // borrowed — points into the owning struct's heap alloc
            sub->borrowed = 1;
            return (Value){.type = VAL_STRUCT, .instance = sub};
        }
        return (Value){.type = VAL_PTR, .ptr = owned};
    }
    if (fdecl->data.data.Decl.is_ref) {
        void *ref_ptr = *(void **)ptr;
        if (!ref_ptr) return (Value){.type = VAL_PTR, .ptr = NULL};
        if (fdecl->data.data.Decl.field_struct_def) {
            Expr *nested = fdecl->data.data.Decl.field_struct_def;
            Str *ftype = &fdecl->data.data.Decl.explicit_type;
            StructInstance *sub = malloc(sizeof(StructInstance));
            sub->struct_name = ftype;
            sub->struct_def = nested;
            sub->data = ref_ptr;
            sub->borrowed = 1;
            return (Value){.type = VAL_STRUCT, .instance = sub};
        }
        return (Value){.type = VAL_PTR, .ptr = ref_ptr};
    }
    Str *ftype = &fdecl->data.data.Decl.explicit_type;
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "I64", 3) == 0))  return val_i64(*(I64 *)ptr);
    if (ftype && (ftype->count == 2 && memcmp(ftype->c_str, "U8", 2) == 0))   return val_u8(*(U8 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "I16", 3) == 0))  return val_i16(*(I16 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "I32", 3) == 0))  return val_i32(*(I32 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "U32", 3) == 0))  return val_u32(*(U32 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "U64", 3) == 0))  return val_u64(*(U64 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "F32", 3) == 0))  return val_f32(*(F32 *)ptr);
    if (ftype && (ftype->count == 4 && memcmp(ftype->c_str, "Bool", 4) == 0)) return val_bool(*(Bool *)ptr);
    // Enum field: tagged enums stored as pointer to EnumInstance, simple enums as I32
    if (fdecl->data.data.Decl.field_struct_def &&
        fdecl->data.data.Decl.field_struct_def->data.tag == ExprData_TAG_EnumDef) {
        if (*enum_has_payloads(fdecl->data.data.Decl.field_struct_def)) {
            EnumInstance *ei = *(EnumInstance **)ptr;
            if (ei) return val_enum(ei->enum_name, ei->tag, clone_value(ei->payload));
            return val_i32(0);
        }
        return val_i32(*(I32 *)ptr);
    }
    // Inline struct: borrow if parent is borrowed, copy otherwise
    if (fdecl->data.data.Decl.field_struct_def) {
        Expr *nested = fdecl->data.data.Decl.field_struct_def;
        StructInstance *sub = malloc(sizeof(StructInstance));
        sub->struct_name = ftype; // borrowed — set by initer for inferred struct types
        sub->struct_def = nested;
        sub->data = ptr;       // always point into parent buffer
        sub->borrowed = 1;     // always borrowed — field lives in parent
        return (Value){.type = VAL_STRUCT, .instance = sub};
    }
    // FuncSig-typed field: stored as Expr * pointer (func ptr)
    if (ftype) {
        void *stored = *(void **)ptr;
        if (stored) return (Value){.type = VAL_FUNC, .func = (Expr *)stored};
    }
    // Fallback: treat as I64
    return val_i64(*(I64 *)ptr);
}

// Write a Value into flat buffer at a field decl's offset
void write_field(StructInstance *inst, Expr *fdecl, Value val) {
    void *ptr = (char *)inst->data + fdecl->data.data.Decl.field_offset;
    I32 fsz = fdecl->data.data.Decl.field_size;
    if (fdecl->data.data.Decl.is_own) {
        *(void **)ptr = val.type == VAL_STRUCT ? val.instance->data : val.ptr;
        if (val.type == VAL_STRUCT) { free(val.instance); }
        return;
    }
    if (fdecl->data.data.Decl.is_ref) {
        // ref field: store pointer (don't own the data)
        if (val.type == VAL_PTR) *(void **)ptr = val.ptr;
        else if (val.type == VAL_STRUCT) {
            *(void **)ptr = val.instance->data;
            free(val.instance);
        }
        else *(void **)ptr = NULL;
        return;
    }
    switch (val.type) {
    case VAL_I64:  *(I64 *)ptr = *val.i64; free(val.i64); break;
    case VAL_U8:   *(U8 *)ptr = *val.u8; free(val.u8); break;
    case VAL_I16:  *(I16 *)ptr = *val.i16; free(val.i16); break;
    case VAL_I32:  *(I32 *)ptr = *val.i32; free(val.i32); break;
    case VAL_U32:  *(U32 *)ptr = *val.u32; free(val.u32); break;
    case VAL_U64:  *(U64 *)ptr = *val.u64; free(val.u64); break;
    case VAL_F32:  *(F32 *)ptr = *val.f32; free(val.f32); break;
    case VAL_BOOL: *(Bool *)ptr = *val.boolean; free(val.boolean); break;
    case VAL_STRUCT:
        if (val.instance->borrowed) {
            Value cloned = clone_value(val);
            memcpy(ptr, cloned.instance->data, fsz);
            free(cloned.instance->data);
            free(cloned.instance);
        } else {
            memcpy(ptr, val.instance->data, fsz);
            free(val.instance->data);
            free(val.instance);
        }
        break;
    case VAL_ENUM: {
        EnumInstance *existing = *(EnumInstance **)ptr;
        if (existing) { free_value(existing->payload); free(existing); }
        *(EnumInstance **)ptr = val.enum_inst;
        break;
    }
    case VAL_PTR:  *(void **)ptr = val.ptr; break;
    case VAL_FUNC: *(void **)ptr = (void *)val.func; break;
    default: break;
    }
}

// Build a Str StructInstance from C string data (copies data via strndup)
Value make_str_value(const char *data, U64 len) {
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = cached_str_name;
    inst->struct_def = cached_str_def;
    inst->data = malloc(24); // Str = {U8 *c_str, U64 count, U64 cap}
    inst->borrowed = 0;
    *(char **)inst->data = strndup(data, len);
    *(U64 *)((char *)inst->data + 8) = len;
    *(U64 *)((char *)inst->data + 16) = CAP_LIT;
    return (Value){.type = VAL_STRUCT, .instance = inst};
}

// Build a Str StructInstance taking ownership of buffer (no copy)
Value make_str_value_own(char *data, U64 len) {
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = cached_str_name;
    inst->struct_def = cached_str_def;
    inst->borrowed = 0;
    inst->data = malloc(24);
    *(char **)inst->data = data;
    *(U64 *)((char *)inst->data + 8) = len;
    *(U64 *)((char *)inst->data + 16) = len;
    return (Value){.type = VAL_STRUCT, .instance = inst};
}

// Extract a C Str view from a Str StructInstance (stack-local, don't free)
Str str_view(Value v) {
    char *data = *(char **)v.instance->data;
    U64 len = *(U64 *)((char *)v.instance->data + 8);
    return (Str){.c_str = (U8 *)data, .count = len};
}

// Deep-clone a Value (for payload enum operations and general use)
Value clone_value(Value v) {
    switch (v.type) {
    case VAL_I64:  return val_i64(*v.i64);
    case VAL_U8:   return val_u8(*v.u8);
    case VAL_I16:  return val_i16(*v.i16);
    case VAL_I32:  return val_i32(*v.i32);
    case VAL_U32:  return val_u32(*v.u32);
    case VAL_U64:  return val_u64(*v.u64);
    case VAL_F32:  return val_f32(*v.f32);
    case VAL_BOOL: return val_bool(*v.boolean);
    case VAL_ENUM: return val_enum(v.enum_inst->enum_name, v.enum_inst->tag,
                                    clone_value(v.enum_inst->payload));
    case VAL_STRUCT: {
        StructInstance *src = v.instance;
        StructInstance *dst = malloc(sizeof(StructInstance));
        dst->struct_name = src->struct_name; // borrowed
        dst->struct_def = src->struct_def;
        dst->borrowed = 0;
        I32 sz = src->struct_def->total_struct_size;
        dst->data = malloc(sz);
        memcpy(dst->data, src->data, sz);
        // Deep-clone Str's data pointer (Str is ext_struct, fields not walkable)
        if ((src->struct_name->count == 3 && memcmp(src->struct_name->c_str, "Str", 3) == 0)) {
            Str *s = (Str *)src->data;
            if (s->count > 0 && s->c_str)
                *(char **)dst->data = strndup((const char *)s->c_str, s->count);
            return (Value){.type = VAL_STRUCT, .instance = dst};
        }
        // Deep-clone fields that contain heap pointers
        Expr *body = Expr_child(src->struct_def, &(I64){(I64)(0)});
        for (U32 fi = 0; fi < body->children.count; fi++) {
            Expr *field = Expr_child(body, &(I64){(I64)(fi)});
            if (field->data.data.Decl.is_namespace) continue;
            I32 foff = field->data.data.Decl.field_offset;
            Str *ftype = &field->data.data.Decl.explicit_type;
            if (field->data.data.Decl.is_own) {
                // own fields are heap pointers — deep-clone recursively
                void *src_ptr = *(void **)((char *)src->data + foff);
                if (src_ptr && field->data.data.Decl.field_struct_def) {
                    Expr *nested = field->data.data.Decl.field_struct_def;
                    StructInstance tmp_src = {
                        .struct_name = ftype,
                        .struct_def = nested,
                        .data = src_ptr,
                        .borrowed = 1
                    };
                    Value tmp_val = {.type = VAL_STRUCT, .instance = &tmp_src};
                    Value cloned = clone_value(tmp_val);
                    *(void **)((char *)dst->data + foff) = cloned.instance->data;
                    free(cloned.instance);
                }
                continue;
            }
            if (field->data.data.Decl.is_ref) {
                // ref fields are non-owning pointers — copy pointer as-is
                continue;
            }
            // Str fields: deep-clone the char* data pointer
            if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "Str", 3) == 0)) {
                Str *s = (Str *)((char *)src->data + foff);
                if (s->count > 0 && s->c_str) {
                    *(char **)((char *)dst->data + foff) = strndup((const char *)s->c_str, s->count);
                }
                continue;
            }
            // Tagged enum fields: clone the EnumInstance pointer
            if (field->data.data.Decl.field_struct_def &&
                field->data.data.Decl.field_struct_def->data.tag == ExprData_TAG_EnumDef &&
                *enum_has_payloads(field->data.data.Decl.field_struct_def)) {
                EnumInstance *ei = *(EnumInstance **)((char *)src->data + foff);
                if (ei) {
                    EnumInstance *clone = malloc(sizeof(EnumInstance));
                    clone->enum_name = ei->enum_name;
                    clone->tag = ei->tag;
                    clone->payload = clone_value(ei->payload);
                    *(EnumInstance **)((char *)dst->data + foff) = clone;
                }
                continue;
            }
            // Inline struct fields: recursively deep-clone
            if (field->data.data.Decl.field_struct_def &&
                field->data.data.Decl.field_struct_def->data.tag != ExprData_TAG_EnumDef) {
                Expr *nested = field->data.data.Decl.field_struct_def;
                StructInstance tmp_src = {
                    .struct_name = ftype,
                    .struct_def = nested,
                    .data = (char *)src->data + foff,
                    .borrowed = 1
                };
                Value tmp_val = {.type = VAL_STRUCT, .instance = &tmp_src};
                Value cloned = clone_value(tmp_val);
                memcpy((char *)dst->data + foff, cloned.instance->data, nested->total_struct_size);
                free(cloned.instance->data);
                free(cloned.instance);
                continue;
            }
        }
        return (Value){.type = VAL_STRUCT, .instance = dst};
    }
    case VAL_PTR:
        return (Value){.type = VAL_PTR, .ptr = v.ptr};
    case VAL_FUNC:
        return (Value){.type = VAL_FUNC, .func = v.func};
    case VAL_NONE: return val_none();
    default:       return val_none();
    }
}

// Free a Value's heap memory
void free_value(Value v) {
    switch (v.type) {
    case VAL_I64:  free(v.i64); break;
    case VAL_U8:   free(v.u8); break;
    case VAL_I16:  free(v.i16); break;
    case VAL_I32:  free(v.i32); break;
    case VAL_U32:  free(v.u32); break;
    case VAL_U64:  free(v.u64); break;
    case VAL_F32:  free(v.f32); break;
    case VAL_BOOL: free(v.boolean); break;
    case VAL_ENUM:
        free_value(v.enum_inst->payload);
        free(v.enum_inst);
        break;
    case VAL_PTR:
        break; // borrowed pointer into buffer, nothing to free
    case VAL_FUNC:
        break; // function pointer: borrowed reference to AST, nothing to free
    default: break;
    }
}

// Compare two Values for equality
Bool values_equal(Value a, Value b) {
    if (a.type != b.type) return 0;
    switch (a.type) {
    case VAL_I64:  return *a.i64 == *b.i64;
    case VAL_I16:  return *a.i16 == *b.i16;
    case VAL_I32:  return *a.i32 == *b.i32;
    case VAL_U32:  return *a.u32 == *b.u32;
    case VAL_U64:  return *a.u64 == *b.u64;
    case VAL_F32:  return *a.f32 == *b.f32;
    case VAL_U8:   return *a.u8 == *b.u8;
    case VAL_BOOL: return *a.boolean == *b.boolean;
    case VAL_ENUM:
        if (a.enum_inst->tag != b.enum_inst->tag) return 0;
        return values_equal(a.enum_inst->payload, b.enum_inst->payload);
    case VAL_PTR:  return a.ptr == b.ptr;
    case VAL_FUNC: return a.func == b.func;
    case VAL_NONE:
        return 1;
    default:       return 0;
    }
}

// --- Eval ---

static void eval_body(Scope *scope, Expr *body);

Value eval_call(Scope *scope, Expr *e) {
    // children[0] = callee ident or field access, children[1..] = args
    Expr *callee_expr = Expr_child(e, &(I64){(I64)(0)});

    // Namespace method call: Struct.method(args)
    if (callee_expr->data.tag == ExprData_TAG_FieldAccess) {
        Value fn_val = eval_expr(scope,callee_expr);
        if (fn_val.type != VAL_FUNC) {
            Expr_error(e, &(Str){.c_str = (U8*)"namespace field is not a function", .count = 37, .cap = CAP_LIT});
            exit(1);
        }
        Expr *func_def = fn_val.func;
        // Direct ext_func namespace method — dispatch by flat name
        FuncType fft = func_def->data.data.FuncDef.func_type;
        if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) {
            // Enum ext methods — delegated to dispatch.c
            Str *parent_sname = &Expr_child(callee_expr, &(I64){(I64)(0)})->struct_name;
            if (parent_sname) {
                Cell *tc = scope_get(scope, parent_sname);
                if (tc && tc->val.type == VAL_FUNC && tc->val.func->data.tag == ExprData_TAG_EnumDef) {
                    Value eresult;
                    if (enum_method_dispatch(&callee_expr->data.data.Ident, scope,
                            tc->val.func, parent_sname, e, &eresult)) {
                        // Null cells of own-arg idents
                        for (U32 i = 1; i < e->children.count; i++) {
                            if (Expr_child(e, &(I64){(I64)(i)})->data.tag == ExprData_TAG_Ident && Expr_child(e, &(I64){(I64)(i)})->is_own_arg) {
                                Cell *c = scope_get(scope, &Expr_child(e, &(I64){(I64)(i)})->data.data.Ident);
                                if (c) c->val = val_none();
                            }
                        }
                        return eresult;
                    }
                }
            }
            static char flat_name_buf[256];
            Str *sn = &Expr_child(callee_expr, &(I64){(I64)(0)})->struct_name;
            Str *fn = &callee_expr->data.data.Ident;
            U64 flen = sn->count + 1 + fn->count;
            memcpy(flat_name_buf, sn->c_str, sn->count);
            flat_name_buf[sn->count] = '_';
            memcpy(flat_name_buf + sn->count + 1, fn->c_str, fn->count);
            flat_name_buf[flen] = '\0';
            Str flat_str = {.c_str = (U8 *)flat_name_buf, .count = flen};
            Expr orig_callee_val = *Expr_child(e, &(I64){(I64)(0)});
            Expr flat_ident = orig_callee_val;
            flat_ident.data.tag = ExprData_TAG_Ident;
            flat_ident.data.data.Ident = flat_str;
            memcpy(Vec_get(&e->children, &(U64){(U64)(0)}), &flat_ident, sizeof(Expr));
            Value result = eval_call(scope, e);
            memcpy(Vec_get(&e->children, &(U64){(U64)(0)}), &orig_callee_val, sizeof(Expr));
            return result;
        }
        Expr *body = Expr_child(func_def, &(I64){(I64)(0)});

        // Guard: skip call if first 'own' param is val_none, borrowed struct, or VAL_PTR
        if (func_def->data.data.FuncDef.nparam > 0 &&
            func_def->data.data.FuncDef.param_owns.count > 0 &&
            (*(Bool*)Vec_get(&func_def->data.data.FuncDef.param_owns, &(U64){(U64)(0)})) &&
            e->children.count > 1 && Expr_child(e, &(I64){(I64)(1)})->data.tag == ExprData_TAG_Ident) {
            Cell *fc = scope_get(scope, &Expr_child(e, &(I64){(I64)(1)})->data.data.Ident);
            if (fc && fc->val.type == VAL_NONE) return val_none();
            if (fc && fc->val.type == VAL_STRUCT && fc->val.instance->borrowed) {
                fc->val = val_none();
                return val_none();
            }
            if (fc && fc->val.type == VAL_PTR) {
                fc->val = val_none();
                return val_none();
            }
        }

        Scope *call_scope = scope_new(scope);
        for (U32 i = 0; i < func_def->data.data.FuncDef.nparam; i++) {
            Expr *arg_expr = Expr_child(e, &(I64){(I64)(i + 1)});
            if (arg_expr->data.tag == ExprData_TAG_Ident) {
                Cell *arg_cell = scope_get(scope, &arg_expr->data.data.Ident);
                // Reinterpret VAL_PTR based on param type
                if (arg_cell->val.type == VAL_PTR && ((Str*)Vec_get(&func_def->data.data.FuncDef.param_types, &(U64){(U64)(i)}))) {
                    Str *ptype = ((Str*)Vec_get(&func_def->data.data.FuncDef.param_types, &(U64){(U64)(i)}));
                    Value arg = arg_cell->val;
                    if ((ptype->count == 3 && memcmp(ptype->c_str, "Str", 3) == 0)) {
                        Str *sp = (Str *)arg.ptr;
                        arg = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0))
                        arg = (Value){.type = VAL_I64, .i64 = (I64 *)arg.ptr};
                    else if ((ptype->count == 2 && memcmp(ptype->c_str, "U8", 2) == 0))
                        arg = (Value){.type = VAL_U8, .u8 = (U8 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0))
                        arg = (Value){.type = VAL_I16, .i16 = (I16 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0))
                        arg = (Value){.type = VAL_I32, .i32 = (I32 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0))
                        arg = (Value){.type = VAL_U32, .u32 = (U32 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0))
                        arg = (Value){.type = VAL_U64, .u64 = (U64 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "F32", 3) == 0))
                        arg = (Value){.type = VAL_F32, .f32 = (F32 *)arg.ptr};
                    else if ((ptype->count == 4 && memcmp(ptype->c_str, "Bool", 4) == 0))
                        arg = (Value){.type = VAL_BOOL, .boolean = (Bool *)arg.ptr};
                    scope_set_owned(call_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), arg);
                } else {
                    scope_set_borrowed(call_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), arg_cell);
                }
            } else {
                Value arg = eval_expr(scope,arg_expr);
                // Reinterpret VAL_PTR based on param type (same as ref decl)
                if (arg.type == VAL_PTR && ((Str*)Vec_get(&func_def->data.data.FuncDef.param_types, &(U64){(U64)(i)}))) {
                    Str *ptype = ((Str*)Vec_get(&func_def->data.data.FuncDef.param_types, &(U64){(U64)(i)}));
                    if ((ptype->count == 3 && memcmp(ptype->c_str, "Str", 3) == 0)) {
                        Str *sp = (Str *)arg.ptr;
                        arg = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0))
                        arg = (Value){.type = VAL_I64, .i64 = (I64 *)arg.ptr};
                    else if ((ptype->count == 2 && memcmp(ptype->c_str, "U8", 2) == 0))
                        arg = (Value){.type = VAL_U8, .u8 = (U8 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0))
                        arg = (Value){.type = VAL_I16, .i16 = (I16 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0))
                        arg = (Value){.type = VAL_I32, .i32 = (I32 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0))
                        arg = (Value){.type = VAL_U32, .u32 = (U32 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0))
                        arg = (Value){.type = VAL_U64, .u64 = (U64 *)arg.ptr};
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "F32", 3) == 0))
                        arg = (Value){.type = VAL_F32, .f32 = (F32 *)arg.ptr};
                    else if ((ptype->count == 4 && memcmp(ptype->c_str, "Bool", 4) == 0))
                        arg = (Value){.type = VAL_BOOL, .boolean = (Bool *)arg.ptr};
                }
                scope_set_owned(call_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), arg);
            }
        }
        has_return = 0;
        eval_body(call_scope, body);
        scope_free(call_scope);
        Value result = val_none();
        if (has_return) {
            result = return_value;
            has_return = 0;
        }
        return result;
    }

    Str *name = &callee_expr->data.data.Ident;

    // Ext function dispatch
    Value ext_result;
    if (ext_function_dispatch(name, scope, e, &ext_result)) {
        // Null cells of own-arg idents (ext dispatch evaluates by value, not borrowed cell)
        for (U32 i = 1; i < e->children.count; i++) {
            if (Expr_child(e, &(I64){(I64)(i)})->data.tag == ExprData_TAG_Ident && Expr_child(e, &(I64){(I64)(i)})->is_own_arg) {
                Cell *c = scope_get(scope, &Expr_child(e, &(I64){(I64)(i)})->data.data.Ident);
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
    if (fn_cell->val.type == VAL_FUNC && fn_cell->val.func->data.tag == ExprData_TAG_StructDef) {
        Expr *sdef = fn_cell->val.func;
        Expr *body = Expr_child(sdef, &(I64){(I64)(0)});

        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = name;   // borrowed from AST
        inst->struct_def = sdef;
        inst->borrowed = 0;
        inst->data = calloc(1, sdef->total_struct_size);
        I32 arg_idx = 1;
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *field = Expr_child(body, &(I64){(I64)(i)});
            if (field->data.data.Decl.is_namespace) continue;
            Expr *arg = Expr_child(e, &(I64){(I64)(arg_idx++)});
            Value val;
            if (arg->data.tag == ExprData_TAG_Ident) {
                Cell *src = scope_get(scope, &arg->data.data.Ident);
                val = src->val;
                if (val.type != VAL_FUNC)
                    src->val = val_none();
            } else {
                val = eval_expr(scope, arg);
            }
            write_field(inst, field, val);
        }
        return (Value){.type = VAL_STRUCT, .instance = inst};
    }

    if (fn_cell->val.type != VAL_FUNC) {
        char buf[128];
        snprintf(buf, sizeof(buf), "'%s' is not a function", name->c_str);
        Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
        exit(1);
    }

    Expr *func_def = fn_cell->val.func;
    Expr *body = Expr_child(func_def, &(I64){(I64)(0)});

    // Guard: skip call if first 'own' param is val_none, borrowed struct, or VAL_PTR
    if (func_def->data.data.FuncDef.nparam > 0 &&
        func_def->data.data.FuncDef.param_owns.count > 0 &&
        (*(Bool*)Vec_get(&func_def->data.data.FuncDef.param_owns, &(U64){(U64)(0)})) &&
        e->children.count > 1 && Expr_child(e, &(I64){(I64)(1)})->data.tag == ExprData_TAG_Ident) {
        Cell *fc = scope_get(scope, &Expr_child(e, &(I64){(I64)(1)})->data.data.Ident);
        if (fc && fc->val.type == VAL_NONE) return val_none();
        if (fc && fc->val.type == VAL_STRUCT && fc->val.instance->borrowed) {
            fc->val = val_none();
            return val_none();
        }
        if (fc && fc->val.type == VAL_PTR) {
            fc->val = val_none();
            return val_none();
        }
    }

    Scope *call_scope = scope_new(scope);
    // Bind arguments to parameters (borrowed refs for idents, owned for expressions)
    U32 nparam = func_def->data.data.FuncDef.nparam;
    for (U32 i = 0; i < nparam; i++) {
        Expr *arg_expr = Expr_child(e, &(I64){(I64)(i + 1)});
        if (arg_expr->data.tag == ExprData_TAG_Ident) {
            Cell *arg_cell = scope_get(scope, &arg_expr->data.data.Ident);
            scope_set_borrowed(call_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), arg_cell);
        } else {
            Value arg = eval_expr(scope, arg_expr);
            scope_set_owned(call_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), arg);
        }
    }

    has_return = 0;
    eval_body(call_scope, body);
    scope_free(call_scope);

    Value result = val_none();
    if (has_return) {
        result = return_value;
        has_return = 0;
    }
    return result;
}

Value eval_expr(Scope *scope, Expr *e) {
    switch (e->data.tag) {
    case ExprData_TAG_LiteralStr:
        return make_str_value((const char *)e->data.data.LiteralStr.c_str, e->data.data.LiteralStr.count);
    case ExprData_TAG_LiteralNum:
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
    case ExprData_TAG_LiteralBool:
        return val_bool((e->data.data.LiteralBool.count == 4 && memcmp(e->data.data.LiteralBool.c_str, "true", 4) == 0));
    case ExprData_TAG_LiteralNull:
        return (Value){.type = VAL_PTR, .ptr = NULL};
    case ExprData_TAG_Ident: {
        Cell *cell = scope_get(scope, &e->data.data.Ident);
        if (!cell) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined variable '%s'", e->data.data.Ident.c_str);
            Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
            exit(1);
        }
        return cell->val;
    }
    case ExprData_TAG_FCall:
        return eval_call(scope, e);
    case ExprData_TAG_FuncDef:
        return (Value){.type = VAL_FUNC, .func = e};
    case ExprData_TAG_StructDef:
    case ExprData_TAG_EnumDef:
        return (Value){.type = VAL_FUNC, .func = e};
    case ExprData_TAG_FieldAccess: {
        Value obj = eval_expr(scope,Expr_child(e, &(I64){(I64)(0)}));
        Str *fname = &e->data.data.FieldAccess;
        if (e->is_ns_field) {
            Str *sname = obj.type == VAL_STRUCT
                ? obj.instance->struct_name : &Expr_child(e, &(I64){(I64)(0)})->data.data.Ident;
            Value *nsv = ns_get(sname, fname);
            if (nsv) {
                // Fresh copy of scalar values (prevents alias to namespace map)
                if (nsv->type == VAL_I64) return val_i64(*nsv->i64);
                if (nsv->type == VAL_I32) return val_i32(*nsv->i32);
                // Auto-call zero-arg enum constructors (Token.Eof without parens)
                if (nsv->type == VAL_FUNC && nsv->func &&
                    nsv->func->data.tag == ExprData_TAG_FuncDef &&
                    nsv->func->data.data.FuncDef.func_type.tag == FuncType_TAG_ExtFunc &&
                    nsv->func->data.data.FuncDef.nparam == 0) {
                    Cell *tc = scope_get(scope, sname);
                    if (tc && tc->val.type == VAL_FUNC && tc->val.func->data.tag == ExprData_TAG_EnumDef) {
                        I32 tag = *enum_variant_tag(tc->val.func, fname);
                        if (tag >= 0) {
                            if (*enum_has_payloads(tc->val.func))
                                return val_enum(sname, tag, val_none());
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
        if (obj.type == VAL_PTR) {
            Expr *obj_expr = Expr_child(e, &(I64){(I64)(0)});
            if (obj_expr->struct_name.count > 0) {
                Cell *tc = scope_get(scope, &obj_expr->struct_name);
                if (tc && tc->val.type == VAL_FUNC && tc->val.func->data.tag == ExprData_TAG_StructDef) {
                    StructInstance *inst = malloc(sizeof(StructInstance));
                    inst->struct_name = &obj_expr->struct_name;
                    inst->struct_def = tc->val.func;
                    inst->data = obj.ptr;
                    inst->borrowed = 1;
                    obj = (Value){.type = VAL_STRUCT, .instance = inst};
                }
            }
        }
        if (obj.type != VAL_STRUCT) {
            Expr_error(e, &(Str){.c_str = (U8*)"field access on non-struct", .count = 27, .cap = CAP_LIT});
            exit(1);
        }
        Expr *fdecl = find_field_decl(obj.instance->struct_def, fname);
        if (!fdecl) {
            char buf[128];
            snprintf(buf, sizeof(buf), "no field '%s'", fname->c_str);
            Expr_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
            exit(1);
        }
        return read_field(obj.instance, fdecl);
    }
    default:
        char buf[128];
        snprintf(buf, sizeof(buf), "cannot evaluate node type %d as expression", e->data.tag);
        Expr_lang_error(e, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
        exit(1);
    }
}

static void eval_body(Scope *scope, Expr *body) {
    for (U32 i = 0; i < body->children.count; i++) {
        if (has_return || has_break || has_continue) return;
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        switch (stmt->data.tag) {
        case ExprData_TAG_Decl: {
            Expr *rhs = Expr_child(stmt, &(I64){(I64)(0)});
            if (stmt->data.data.Decl.is_ref && rhs->data.tag == ExprData_TAG_Ident) {
                // Ref decl from ident: borrow the same cell (no move, no free)
                Cell *src = scope_get(scope, &rhs->data.data.Ident);
                scope_set_borrowed(scope, (&stmt->data.data.Decl.name), src);
            } else {
                Value val;
                if (rhs->data.tag == ExprData_TAG_Ident) {
                    // Move semantics: transfer value from source, null source
                    Cell *src = scope_get(scope, &rhs->data.data.Ident);
                    if (!src) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "undefined variable '%s'", rhs->data.data.Ident.c_str);
                        Expr_error(rhs, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
                        exit(1);
                    }
                    val = src->val;
                    if (val.type != VAL_FUNC)
                        src->val = val_none();
                } else {
                    val = eval_expr(scope,rhs);
                }
                // Reinterpret VAL_PTR based on declared type (ref a : I64 = ptr_add(...))
                // Only for ref decls — own decls keep VAL_PTR (they own a buffer, not a single element)
                // Skip narrowing for NULL pointers (null literal)
                if (val.type == VAL_PTR && val.ptr != NULL && (stmt->data.data.Decl.explicit_type).count > 0 && stmt->data.data.Decl.is_ref) {
                    Str *etype = &stmt->data.data.Decl.explicit_type;
                    if ((etype->count == 3 && memcmp(etype->c_str, "I64", 3) == 0))
                        val = (Value){.type = VAL_I64, .i64 = (I64 *)val.ptr};
                    else if ((etype->count == 2 && memcmp(etype->c_str, "U8", 2) == 0))
                        val = (Value){.type = VAL_U8, .u8 = (U8 *)val.ptr};
                    else if ((etype->count == 3 && memcmp(etype->c_str, "I16", 3) == 0))
                        val = (Value){.type = VAL_I16, .i16 = (I16 *)val.ptr};
                    else if ((etype->count == 3 && memcmp(etype->c_str, "I32", 3) == 0))
                        val = (Value){.type = VAL_I32, .i32 = (I32 *)val.ptr};
                    else if ((etype->count == 3 && memcmp(etype->c_str, "U32", 3) == 0))
                        val = (Value){.type = VAL_U32, .u32 = (U32 *)val.ptr};
                    else if ((etype->count == 3 && memcmp(etype->c_str, "U64", 3) == 0))
                        val = (Value){.type = VAL_U64, .u64 = (U64 *)val.ptr};
                    else if ((etype->count == 3 && memcmp(etype->c_str, "F32", 3) == 0))
                        val = (Value){.type = VAL_F32, .f32 = (F32 *)val.ptr};
                    else if ((etype->count == 4 && memcmp(etype->c_str, "Bool", 4) == 0))
                        val = (Value){.type = VAL_BOOL, .boolean = (Bool *)val.ptr};
                    else if ((etype->count == 3 && memcmp(etype->c_str, "Str", 3) == 0)) {
                        Str *sp = (Str *)val.ptr;
                        val = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else {
                        // User-defined struct: wrap ptr in borrowed StructInstance
                        Cell *tc = scope_get(scope, etype);
                        if (tc && tc->val.type == VAL_FUNC && tc->val.func->data.tag == ExprData_TAG_StructDef) {
                            StructInstance *inst = malloc(sizeof(StructInstance));
                            inst->struct_name = etype;
                            inst->struct_def = tc->val.func;
                            inst->data = val.ptr;
                            inst->borrowed = stmt->data.data.Decl.is_mut ? 1 : 0;
                            val = (Value){.type = VAL_STRUCT, .instance = inst};
                        }
                    }
                }
                scope_set_owned(scope, (&stmt->data.data.Decl.name), val);
            }
            break;
        }
        case ExprData_TAG_Assign: {
            Expr *rhs = Expr_child(stmt, &(I64){(I64)(0)});
            Cell *cell = scope_get(scope, &stmt->data.data.Assign);
            if (!cell) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined variable '%s'", stmt->data.data.Assign.c_str);
                Expr_error(stmt, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
                exit(1);
            }
            if (rhs->data.tag == ExprData_TAG_Ident) {
                // Move semantics: transfer value from source, null source
                Cell *src = scope_get(scope, &rhs->data.data.Ident);
                free_value(cell->val);
                cell->val = src->val;
                if (src->val.type != VAL_FUNC)
                    src->val = val_none();
            } else {
                Value new_val = eval_expr(scope,rhs);
                free_value(cell->val);
                cell->val = new_val;
            }
            break;
        }
        case ExprData_TAG_FieldAssign: {
            Expr *val_expr = Expr_child(stmt, &(I64){(I64)(1)});
            Value val;
            Cell *move_src = NULL;
            if (val_expr->data.tag == ExprData_TAG_Ident) {
                move_src = scope_get(scope, &val_expr->data.data.Ident);
                val = move_src->val;
            } else {
                val = eval_expr(scope, val_expr);
            }
            Str *fname = &stmt->data.data.FieldAssign;
            if (stmt->is_ns_field) {
                Value obj = eval_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}));
                Str *sname = obj.type == VAL_STRUCT
                    ? obj.instance->struct_name : &Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident;
                ns_set(sname, fname, val);
                if (move_src) move_src->val = val_none();
            } else {
                // Resolve to the flat buffer + struct_def where the field lives
                void *base = NULL;
                Expr *cur_sdef = NULL;
                Expr *obj_expr = Expr_child(stmt, &(I64){(I64)(0)});
                if (obj_expr->data.tag == ExprData_TAG_Ident) {
                    Cell *cell = scope_get(scope, &obj_expr->data.data.Ident);
                    if (cell && cell->val.type == VAL_STRUCT) {
                        base = cell->val.instance->data;
                        cur_sdef = cell->val.instance->struct_def;
                    }
                } else if (obj_expr->data.tag == ExprData_TAG_FieldAccess) {
                    // Chained: e.g. l1.start.x — walk chain to compute offset
                    Expr *chain[32]; I32 depth = 0;
                    Expr *cur = obj_expr;
                    while (cur->data.tag == ExprData_TAG_FieldAccess) {
                        chain[depth++] = cur;
                        cur = Expr_child(cur, &(I64){(I64)(0)});
                    }
                    Cell *cell = scope_get(scope, &cur->data.data.Ident);
                    if (cell && cell->val.type == VAL_STRUCT) {
                        base = cell->val.instance->data;
                        cur_sdef = cell->val.instance->struct_def;
                        for (I32 d = depth - 1; d >= 0; d--) {
                            Expr *fd = find_field_decl(cur_sdef, &chain[d]->data.data.FieldAccess);
                            if (!fd) { base = NULL; break; }
                            if (fd->data.data.Decl.is_own || fd->data.data.Decl.is_ref) {
                                base = *(void **)((char *)base + fd->data.data.Decl.field_offset);
                            } else {
                                base = (char *)base + fd->data.data.Decl.field_offset;
                            }
                            cur_sdef = fd->data.data.Decl.field_struct_def;
                            if (!cur_sdef) { base = NULL; break; }
                        }
                    }
                }
                if (!base || !cur_sdef) {
                    Expr_error(stmt, &(Str){.c_str = (U8*)"field assign on non-struct", .count = 27, .cap = CAP_LIT});
                    exit(1);
                }
                Expr *fdecl = find_field_decl(cur_sdef, fname);
                void *ptr = (char *)base + fdecl->data.data.Decl.field_offset;
                // Write value directly at computed address
                I32 fsz = fdecl->data.data.Decl.field_size;
                if (fdecl->data.data.Decl.is_own) {
                    *(void **)ptr = val.type == VAL_STRUCT ? val.instance->data : val.ptr;
                    if (val.type == VAL_STRUCT) free(val.instance);
                } else if (fdecl->data.data.Decl.is_ref) {
                    if (val.type == VAL_PTR) *(void **)ptr = val.ptr;
                    else if (val.type == VAL_STRUCT) {
                        *(void **)ptr = val.instance->data;
                        free(val.instance);
                    }
                    else *(void **)ptr = NULL;
                } else {
                    switch (val.type) {
                    case VAL_I64:  *(I64 *)ptr = *val.i64; free(val.i64); break;
                    case VAL_U8:   *(U8 *)ptr = *val.u8; free(val.u8); break;
                    case VAL_I16:  *(I16 *)ptr = *val.i16; free(val.i16); break;
                    case VAL_I32:  *(I32 *)ptr = *val.i32; free(val.i32); break;
                    case VAL_U32:  *(U32 *)ptr = *val.u32; free(val.u32); break;
                    case VAL_U64:  *(U64 *)ptr = *val.u64; free(val.u64); break;
                    case VAL_BOOL: *(Bool *)ptr = *val.boolean; free(val.boolean); break;
                    case VAL_STRUCT:
                        if (val.instance->borrowed) {
                            Value cloned = clone_value(val);
                            memcpy(ptr, cloned.instance->data, fsz);
                            free(cloned.instance->data);
                            free(cloned.instance);
                        } else {
                            memcpy(ptr, val.instance->data, fsz);
                            free(val.instance->data);
                            free(val.instance);
                        }
                        break;
                    case VAL_ENUM: {
                        EnumInstance *existing = *(EnumInstance **)ptr;
                        if (existing) { free_value(existing->payload); free(existing); }
                        *(EnumInstance **)ptr = val.enum_inst;
                        break;
                    }
                    case VAL_PTR: *(void **)ptr = val.ptr; break;
                    case VAL_FUNC: *(void **)ptr = (void *)val.func; break;
                    default: break;
                    }
                }
                if (move_src && move_src->val.type != VAL_FUNC) move_src->val = val_none();
            }
            break;
        }
        case ExprData_TAG_FCall:
            eval_call(scope, stmt);
            break;
        case ExprData_TAG_Body: {
            Scope *block_scope = scope_new(scope);
            eval_body(block_scope, stmt);
            scope_free(block_scope);
            break;
        }
        case ExprData_TAG_If: {
            Value cond = eval_expr(scope,Expr_child(stmt, &(I64){(I64)(0)}));
            if (*cond.boolean) {
                Scope *then_scope = scope_new(scope);
                eval_body(then_scope, Expr_child(stmt, &(I64){(I64)(1)}));
                scope_free(then_scope);
            } else if (stmt->children.count > 2) {
                Scope *else_scope = scope_new(scope);
                eval_body(else_scope, Expr_child(stmt, &(I64){(I64)(2)}));
                scope_free(else_scope);
            }
            break;
        }
        case ExprData_TAG_While: {
            while (1) {
                if (has_return) break;
                Value cond = eval_expr(scope,Expr_child(stmt, &(I64){(I64)(0)}));
                if (!*cond.boolean) break;
                Scope *while_scope = scope_new(scope);
                eval_body(while_scope, Expr_child(stmt, &(I64){(I64)(1)}));
                scope_free(while_scope);
                if (has_break) { has_break = 0; break; }
                if (has_continue) { has_continue = 0; }
            }
            break;
        }
        case ExprData_TAG_Break:
            has_break = 1;
            return;
        case ExprData_TAG_Continue:
            has_continue = 1;
            return;
        case ExprData_TAG_Return:
            if (stmt->children.count > 0) {
                return_value = eval_expr(scope,Expr_child(stmt, &(I64){(I64)(0)}));
            } else {
                return_value = val_none();
            }
            has_return = 1;
            return;
        default:
            char buf[128];
            snprintf(buf, sizeof(buf), "unexpected statement type %d", stmt->data.tag);
            Expr_lang_error(stmt, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
            exit(1);
        }
    }
}

void interpreter_init_ns(Scope *global, Expr *program) {
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Value)}); ns_fields = *_mp; free(_mp); }
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Str *)}); ns_keys = *_vp; free(_vp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(I64){(I64)(i)});
        if (stmt->data.tag == ExprData_TAG_Decl && (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_StructDef ||
                                        Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_EnumDef)) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *sdef = Expr_child(stmt, &(I64){(I64)(0)});
            // Cache struct defs for C-side construction
            if (sdef->data.tag == ExprData_TAG_StructDef) {
                if ((sname->count == 3 && memcmp(sname->c_str, "Str", 3) == 0))   { cached_str_def = sdef; cached_str_name = sname; }
                if ((sname->count == 5 && memcmp(sname->c_str, "Array", 5) == 0)) { cached_array_def = sdef; cached_array_name = sname; }
                if ((sname->count == 3 && memcmp(sname->c_str, "Vec", 3) == 0))   { cached_vec_def = sdef; cached_vec_name = sname; }
            }
            Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(I64){(I64)(j)});
                if (field->data.data.Decl.is_namespace) {
                    Value fval = eval_expr(global, Expr_child(field, &(I64){(I64)(0)}));
                    // Simple enum variant tags: convert I64 literal to I32 (matching C enum)
                    if (sdef->data.tag == ExprData_TAG_EnumDef && !*enum_has_payloads(sdef) &&
                        fval.type == VAL_I64) {
                        I32 tag = (I32)*fval.i64;
                        free(fval.i64);
                        fval = val_i32(tag);
                    }
                    ns_set(sname, (&field->data.data.Decl.name), fval);
                }
            }
        }
    }
}

static Value parse_cli_arg(const char *s, Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0)) return make_str_value(s, strlen(s));
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0)) {
        char *end;
        I64 v = strtoll(s, &end, 10);
        if (*end != '\0') {
            fprintf(stderr, "error: cannot parse '%s' as I64\n", s);
            exit(1);
        }
        return val_i64(v);
    }
    if ((type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0)) {
        char *end;
        long v = strtol(s, &end, 10);
        if (*end != '\0' || v < 0 || v > 255) {
            fprintf(stderr, "error: cannot parse '%s' as U8\n", s);
            exit(1);
        }
        return val_u8(v);
    }
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0)) {
        char *end;
        long v = strtol(s, &end, 10);
        if (*end != '\0' || v < -32768 || v > 32767) {
            fprintf(stderr, "error: cannot parse '%s' as I16\n", s);
            exit(1);
        }
        return val_i16(v);
    }
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0)) {
        char *end;
        long v = strtol(s, &end, 10);
        if (*end != '\0' || v < -2147483648L || v > 2147483647L) {
            fprintf(stderr, "error: cannot parse '%s' as I32\n", s);
            exit(1);
        }
        return val_i32(v);
    }
    if ((type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0)) {
        char *end;
        unsigned long v = strtoul(s, &end, 10);
        if (*end != '\0' || v > 0xFFFFFFFF) {
            fprintf(stderr, "error: cannot parse '%s' as U32\n", s);
            exit(1);
        }
        return val_u32(v);
    }
    if ((type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0)) {
        if (strcmp(s, "true") == 0) return val_bool(1);
        if (strcmp(s, "false") == 0) return val_bool(0);
        fprintf(stderr, "error: cannot parse '%s' as Bool (expected true/false)\n", s);
        exit(1);
    }
    fprintf(stderr, "error: unsupported CLI argument type '%s'\n", type_name->c_str);
    exit(1);
}

static I32 elem_size_for_type(Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0)) return (I32)sizeof(I64);
    if ((type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0))  return (I32)sizeof(U8);
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0)) return (I32)sizeof(I16);
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0)) return (I32)sizeof(I32);
    if ((type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0)) return (I32)sizeof(U32);
    if ((type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0)) return (I32)sizeof(Bool);
    if ((type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0)) return 24; // til Str = {U8*, I64 len, I64 cap}
    return 8;
}

static void value_to_buf(void *dest, Value v, Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0))       { memcpy(dest, v.i64, sizeof(I64)); free(v.i64); }
    else if ((type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0))   { memcpy(dest, v.u8, sizeof(U8)); free(v.u8); }
    else if ((type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0))  { memcpy(dest, v.i16, sizeof(I16)); free(v.i16); }
    else if ((type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0))  { memcpy(dest, v.i32, sizeof(I32)); free(v.i32); }
    else if ((type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0))  { memcpy(dest, v.u32, sizeof(U32)); free(v.u32); }
    else if ((type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0)) { memcpy(dest, v.boolean, sizeof(Bool)); free(v.boolean); }
    else if (v.type == VAL_STRUCT) {
        I32 sz = v.instance->struct_def->total_struct_size;
        if (v.instance->borrowed) {
            Value cloned = clone_value(v);
            memcpy(dest, cloned.instance->data, sz);
            free(cloned.instance->data);
            free(cloned.instance);
        } else {
            memcpy(dest, v.instance->data, sz);
            free(v.instance->data);
            free(v.instance);
        }
    }
}

static Value build_argv_array(U32 argc, char **argv, Str *elem_type) {
    I32 esz = elem_size_for_type(elem_type);
    void *data = calloc(argc > 0 ? argc : 1, esz);
    for (U32 i = 0; i < argc; i++) {
        Value v = parse_cli_arg(argv[i], elem_type);
        value_to_buf((char *)data + i * esz, v, elem_type);
    }
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = cached_array_name;
    inst->struct_def = cached_array_def;
    inst->borrowed = 0;
    inst->data = calloc(1, cached_array_def->total_struct_size);
    // Write fields: data, cap, elem_size, elem_type
    Str fn_data = {.c_str = (U8 *)"data", .count = 4};
    Str fn_cap = {.c_str = (U8 *)"cap", .count = 3};
    Str fn_esz = {.c_str = (U8 *)"elem_size", .count = 9};
    Str fn_et = {.c_str = (U8 *)"elem_type", .count = 9};
    write_field(inst, find_field_decl(cached_array_def, &fn_data), (Value){.type = VAL_PTR, .ptr = data});
    write_field(inst, find_field_decl(cached_array_def, &fn_cap), val_u64(argc));
    write_field(inst, find_field_decl(cached_array_def, &fn_esz), val_u64(esz));
    write_field(inst, find_field_decl(cached_array_def, &fn_et), make_str_value((const char *)elem_type->c_str, elem_type->count));
    return (Value){.type = VAL_STRUCT, .instance = inst};
}

I32 interpret(Expr *program, const Mode *mode, Bool run_tests, Str *path, Str *user_c_path, Str *ext_c_path, Str *link_flags, U32 user_argc, char **user_argv) {
    // Initialize FFI: load user .c library (if provided) and auto-discover C functions
    I32 ffi_rc = ffi_init(program, user_c_path, ext_c_path, link_flags);
    if (ffi_rc != 0) return ffi_rc;

    Scope *global = scope_new(NULL);

    // Pre-register all top-level func/proc/struct definitions for forward references
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(I64){(I64)(i)});
        if (stmt->data.tag == ExprData_TAG_Decl &&
            (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef ||
             Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_StructDef ||
             Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_EnumDef)) {
            Value val = {.type = VAL_FUNC, .func = Expr_child(stmt, &(I64){(I64)(0)})};
            scope_set_owned(global, (&stmt->data.data.Decl.name), val);
        }
    }

    // Initialize namespace fields for all structs
    interpreter_init_ns(global, program);

    // Evaluate top-level declarations
    eval_body(global, program);

    // Run test functions if requested
    if (run_tests) {
        I32 test_count = 0, pass_count = 0;
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = Expr_child(program, &(I64){(I64)(i)});
            if (stmt->data.tag != ExprData_TAG_Decl) continue;
            Expr *rhs = Expr_child(stmt, &(I64){(I64)(0)});
            if (rhs->data.tag != ExprData_TAG_FuncDef) continue;
            if (rhs->data.data.FuncDef.func_type.tag != FuncType_TAG_Test) continue;
            Str *tname = &stmt->data.data.Decl.name;
            test_count++;
            Scope *test_scope = scope_new(global);
            eval_body(test_scope, Expr_child(rhs, &(I64){(I64)(0)}));
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
        if (!main_cell || main_cell->val.type != VAL_FUNC) {
            fprintf(stderr, "%s: error: mode '%.*s' requires a 'main' proc\n", path->c_str, (int)mode->name.count, (const char *)mode->name.c_str);
            scope_free(global);
            return 1;
        }
        Expr *func_def = main_cell->val.func;
        U32 nparam = func_def->data.data.FuncDef.nparam;
        I32 vi = func_def->data.data.FuncDef.variadic_index;
        Expr *body = Expr_child(func_def, &(I64){(I64)(0)});
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
                    Value arr = build_argv_array(va_count, user_argv + argi, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_types, &(U64){(U64)(vi)})));
                    scope_set_owned(main_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), arr);
                    argi += va_count;
                } else {
                    Value v = parse_cli_arg(user_argv[argi], ((Str*)Vec_get(&func_def->data.data.FuncDef.param_types, &(U64){(U64)(i)})));
                    scope_set_owned(main_scope, ((Str*)Vec_get(&func_def->data.data.FuncDef.param_names, &(U64){(U64)(i)})), v);
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
    return 0;
}

I32 interpret_v(Expr *program, const Mode *mode, Bool run_tests,
                Str *path, Str *user_c_path, Str *ext_c_path,
                Str *link_flags, Vec *user_argv) {
    if (user_c_path && user_c_path->count == 0) user_c_path = NULL;
    if (link_flags && link_flags->count == 0) link_flags = NULL;
    char **argv = NULL;
    U32 argc = user_argv ? (U32)user_argv->count : 0;
    if (argc > 0) {
        argv = malloc(argc * sizeof(char *));
        for (U32 i = 0; i < argc; i++) {
            Str *s = (Str *)Vec_get(user_argv, &(U64){(U64)i});
            argv[i] = (char *)s->c_str;
        }
    }
    I32 r = interpret(program, mode, run_tests, path, user_c_path,
                      ext_c_path, link_flags, argc, argv);
    free(argv);
    return r;
}
