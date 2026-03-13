#include "interpreter.h"
#include "dispatch.h"
#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    Str *s = Str_new(buf);
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
    { Map *_mp = Map_new(Str_new("Str"), &(U64){sizeof(Str)}, Str_new(""), &(U64){sizeof(Binding)}); s->bindings = *_mp; free(_mp); }
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
    Expr *body = expr_child(struct_def, 0);
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = expr_child(body, i);
        if (f->type.tag == NODE_DECL && !f->type.decl.is_namespace &&
            *Str_eq(f->type.decl.name, fname))
            return f;
    }
    return NULL;
}

// Read a Value from flat buffer at a field decl's offset
static Value read_field(StructInstance *inst, Expr *fdecl) {
    void *ptr = (char *)inst->data + fdecl->type.decl.field_offset;
    if (fdecl->type.decl.is_own) {
        void *owned = *(void **)ptr;
        // If the own field has a struct def, wrap in StructInstance for field access
        if (fdecl->type.decl.field_struct_def) {
            Expr *nested = fdecl->type.decl.field_struct_def;
            Str *ftype = fdecl->type.decl.explicit_type;
            StructInstance *sub = malloc(sizeof(StructInstance));
            sub->struct_name = ftype;
            sub->struct_def = nested;
            sub->data = owned; // borrowed — points into the owning struct's heap alloc
            sub->borrowed = 1;
            return (Value){.type = VAL_STRUCT, .instance = sub};
        }
        return (Value){.type = VAL_PTR, .ptr = owned};
    }
    if (fdecl->type.decl.is_ref) {
        void *ref_ptr = *(void **)ptr;
        if (!ref_ptr) return (Value){.type = VAL_PTR, .ptr = NULL};
        if (fdecl->type.decl.field_struct_def) {
            Expr *nested = fdecl->type.decl.field_struct_def;
            Str *ftype = fdecl->type.decl.explicit_type;
            StructInstance *sub = malloc(sizeof(StructInstance));
            sub->struct_name = ftype;
            sub->struct_def = nested;
            sub->data = ref_ptr;
            sub->borrowed = 1;
            return (Value){.type = VAL_STRUCT, .instance = sub};
        }
        return (Value){.type = VAL_PTR, .ptr = ref_ptr};
    }
    Str *ftype = fdecl->type.decl.explicit_type;
    if (ftype && Str_eq_c(ftype, "I64"))  return val_i64(*(I64 *)ptr);
    if (ftype && Str_eq_c(ftype, "U8"))   return val_u8(*(U8 *)ptr);
    if (ftype && Str_eq_c(ftype, "I16"))  return val_i16(*(I16 *)ptr);
    if (ftype && Str_eq_c(ftype, "I32"))  return val_i32(*(I32 *)ptr);
    if (ftype && Str_eq_c(ftype, "U32"))  return val_u32(*(U32 *)ptr);
    if (ftype && Str_eq_c(ftype, "U64"))  return val_u64(*(U64 *)ptr);
    if (ftype && Str_eq_c(ftype, "F32"))  return val_f32(*(F32 *)ptr);
    if (ftype && Str_eq_c(ftype, "Bool")) return val_bool(*(Bool *)ptr);
    // Enum field: tagged enums stored as pointer to EnumInstance, simple enums as I32
    if (fdecl->type.decl.field_struct_def &&
        fdecl->type.decl.field_struct_def->type.tag == NODE_ENUM_DEF) {
        if (enum_has_payloads(fdecl->type.decl.field_struct_def)) {
            EnumInstance *ei = *(EnumInstance **)ptr;
            if (ei) return val_enum(ei->enum_name, ei->tag, clone_value(ei->payload));
            return val_i32(0);
        }
        return val_i32(*(I32 *)ptr);
    }
    // Inline struct: borrow if parent is borrowed, copy otherwise
    if (fdecl->type.decl.field_struct_def) {
        Expr *nested = fdecl->type.decl.field_struct_def;
        StructInstance *sub = malloc(sizeof(StructInstance));
        sub->struct_name = ftype; // borrowed — set by initer for inferred struct types
        sub->struct_def = nested;
        sub->data = ptr;       // always point into parent buffer
        sub->borrowed = 1;     // always borrowed — field lives in parent
        return (Value){.type = VAL_STRUCT, .instance = sub};
    }
    // Fallback: treat as I64
    return val_i64(*(I64 *)ptr);
}

// Write a Value into flat buffer at a field decl's offset
void write_field(StructInstance *inst, Expr *fdecl, Value val) {
    void *ptr = (char *)inst->data + fdecl->type.decl.field_offset;
    I32 fsz = fdecl->type.decl.field_size;
    if (fdecl->type.decl.is_own) {
        *(void **)ptr = val.type == VAL_STRUCT ? val.instance->data : val.ptr;
        if (val.type == VAL_STRUCT) { free(val.instance); }
        return;
    }
    if (fdecl->type.decl.is_ref) {
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
        if (Str_eq_c(src->struct_name, "Str")) {
            Str *s = (Str *)src->data;
            if (s->count > 0 && s->c_str)
                *(char **)dst->data = strndup((const char *)s->c_str, s->count);
            return (Value){.type = VAL_STRUCT, .instance = dst};
        }
        // Deep-clone fields that contain heap pointers
        Expr *body = expr_child(src->struct_def, 0);
        for (U32 fi = 0; fi < body->children.count; fi++) {
            Expr *field = expr_child(body, fi);
            if (field->type.decl.is_namespace) continue;
            I32 foff = field->type.decl.field_offset;
            Str *ftype = field->type.decl.explicit_type;
            if (field->type.decl.is_own) {
                // own fields are heap pointers — deep-clone recursively
                void *src_ptr = *(void **)((char *)src->data + foff);
                if (src_ptr && field->type.decl.field_struct_def) {
                    Expr *nested = field->type.decl.field_struct_def;
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
            if (field->type.decl.is_ref) {
                // ref fields are non-owning pointers — copy pointer as-is
                continue;
            }
            // Str fields: deep-clone the char* data pointer
            if (ftype && Str_eq_c(ftype, "Str")) {
                Str *s = (Str *)((char *)src->data + foff);
                if (s->count > 0 && s->c_str) {
                    *(char **)((char *)dst->data + foff) = strndup((const char *)s->c_str, s->count);
                }
                continue;
            }
            // Tagged enum fields: clone the EnumInstance pointer
            if (field->type.decl.field_struct_def &&
                field->type.decl.field_struct_def->type.tag == NODE_ENUM_DEF &&
                enum_has_payloads(field->type.decl.field_struct_def)) {
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
            if (field->type.decl.field_struct_def &&
                field->type.decl.field_struct_def->type.tag != NODE_ENUM_DEF) {
                Expr *nested = field->type.decl.field_struct_def;
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
    case VAL_NONE:
        return 1;
    default:       return 0;
    }
}

// --- Eval ---

static void eval_body(Scope *scope, Expr *body);

Value eval_call(Scope *scope, Expr *e) {
    // children[0] = callee ident or field access, children[1..] = args
    Expr *callee_expr = expr_child(e, 0);

    // Namespace method call: Struct.method(args)
    if (callee_expr->type.tag == NODE_FIELD_ACCESS) {
        Value fn_val = eval_expr(scope,callee_expr);
        if (fn_val.type != VAL_FUNC) {
            expr_error(e, "namespace field is not a function");
            exit(1);
        }
        Expr *func_def = fn_val.func;
        // Direct ext_func namespace method — dispatch by flat name
        FuncType fft = func_def->type.func_def.func_type;
        if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) {
            // Enum ext methods — delegated to dispatch.c
            Str *parent_sname = expr_child(callee_expr, 0)->struct_name;
            if (parent_sname) {
                Cell *tc = scope_get(scope, parent_sname);
                if (tc && tc->val.type == VAL_FUNC && tc->val.func->type.tag == NODE_ENUM_DEF) {
                    Value eresult;
                    if (enum_method_dispatch(callee_expr->type.str_val, scope,
                            tc->val.func, parent_sname, e, &eresult)) {
                        // Null cells of own-arg idents
                        for (U32 i = 1; i < e->children.count; i++) {
                            if (expr_child(e, i)->type.tag == NODE_IDENT && expr_child(e, i)->is_own_arg) {
                                Cell *c = scope_get(scope, expr_child(e, i)->type.str_val);
                                if (c) c->val = val_none();
                            }
                        }
                        return eresult;
                    }
                }
            }
            static char flat_name_buf[256];
            Str *sn = expr_child(callee_expr, 0)->struct_name;
            Str *fn = callee_expr->type.str_val;
            U64 flen = sn->count + 1 + fn->count;
            memcpy(flat_name_buf, sn->c_str, sn->count);
            flat_name_buf[sn->count] = '_';
            memcpy(flat_name_buf + sn->count + 1, fn->c_str, fn->count);
            flat_name_buf[flen] = '\0';
            Str flat_str = {.c_str = (U8 *)flat_name_buf, .count = flen};
            Expr *orig_callee = expr_child(e, 0);
            Expr flat_ident = *orig_callee;
            flat_ident.type.tag = NODE_IDENT;
            flat_ident.type.str_val = &flat_str;
            expr_child(e, 0) = &flat_ident;
            Value result = eval_call(scope, e);
            expr_child(e, 0) = orig_callee;
            return result;
        }
        Expr *body = expr_child(func_def, 0);

        // Guard: skip call if first 'own' param is val_none, borrowed struct, or VAL_PTR
        if (func_def->type.func_def.nparam > 0 &&
            func_def->type.func_def.param_owns &&
            func_def->type.func_def.param_owns[0] &&
            e->children.count > 1 && expr_child(e, 1)->type.tag == NODE_IDENT) {
            Cell *fc = scope_get(scope, expr_child(e, 1)->type.str_val);
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
        for (U32 i = 0; i < func_def->type.func_def.nparam; i++) {
            Expr *arg_expr = expr_child(e, i + 1);
            if (arg_expr->type.tag == NODE_IDENT) {
                Cell *arg_cell = scope_get(scope, arg_expr->type.str_val);
                // Reinterpret VAL_PTR based on param type
                if (arg_cell->val.type == VAL_PTR && func_def->type.func_def.param_types[i]) {
                    Str *ptype = func_def->type.func_def.param_types[i];
                    Value arg = arg_cell->val;
                    if (Str_eq_c(ptype, "Str")) {
                        Str *sp = (Str *)arg.ptr;
                        arg = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else if (Str_eq_c(ptype, "I64"))
                        arg = (Value){.type = VAL_I64, .i64 = (I64 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U8"))
                        arg = (Value){.type = VAL_U8, .u8 = (U8 *)arg.ptr};
                    else if (Str_eq_c(ptype, "I16"))
                        arg = (Value){.type = VAL_I16, .i16 = (I16 *)arg.ptr};
                    else if (Str_eq_c(ptype, "I32"))
                        arg = (Value){.type = VAL_I32, .i32 = (I32 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U32"))
                        arg = (Value){.type = VAL_U32, .u32 = (U32 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U64"))
                        arg = (Value){.type = VAL_U64, .u64 = (U64 *)arg.ptr};
                    else if (Str_eq_c(ptype, "F32"))
                        arg = (Value){.type = VAL_F32, .f32 = (F32 *)arg.ptr};
                    else if (Str_eq_c(ptype, "Bool"))
                        arg = (Value){.type = VAL_BOOL, .boolean = (Bool *)arg.ptr};
                    scope_set_owned(call_scope, func_def->type.func_def.param_names[i], arg);
                } else {
                    scope_set_borrowed(call_scope, func_def->type.func_def.param_names[i], arg_cell);
                }
            } else {
                Value arg = eval_expr(scope,arg_expr);
                // Reinterpret VAL_PTR based on param type (same as ref decl)
                if (arg.type == VAL_PTR && func_def->type.func_def.param_types[i]) {
                    Str *ptype = func_def->type.func_def.param_types[i];
                    if (Str_eq_c(ptype, "Str")) {
                        Str *sp = (Str *)arg.ptr;
                        arg = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else if (Str_eq_c(ptype, "I64"))
                        arg = (Value){.type = VAL_I64, .i64 = (I64 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U8"))
                        arg = (Value){.type = VAL_U8, .u8 = (U8 *)arg.ptr};
                    else if (Str_eq_c(ptype, "I16"))
                        arg = (Value){.type = VAL_I16, .i16 = (I16 *)arg.ptr};
                    else if (Str_eq_c(ptype, "I32"))
                        arg = (Value){.type = VAL_I32, .i32 = (I32 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U32"))
                        arg = (Value){.type = VAL_U32, .u32 = (U32 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U64"))
                        arg = (Value){.type = VAL_U64, .u64 = (U64 *)arg.ptr};
                    else if (Str_eq_c(ptype, "F32"))
                        arg = (Value){.type = VAL_F32, .f32 = (F32 *)arg.ptr};
                    else if (Str_eq_c(ptype, "Bool"))
                        arg = (Value){.type = VAL_BOOL, .boolean = (Bool *)arg.ptr};
                }
                scope_set_owned(call_scope, func_def->type.func_def.param_names[i], arg);
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

    Str *name = callee_expr->type.str_val;

    // Ext function dispatch
    Value ext_result;
    if (ext_function_dispatch(name, scope, e, &ext_result)) {
        // Null cells of own-arg idents (ext dispatch evaluates by value, not borrowed cell)
        for (U32 i = 1; i < e->children.count; i++) {
            if (expr_child(e, i)->type.tag == NODE_IDENT && expr_child(e, i)->is_own_arg) {
                Cell *c = scope_get(scope, expr_child(e, i)->type.str_val);
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
        expr_error(e, buf);
        exit(1);
    }

    // Struct instantiation — typer already desugared named args to positional
    if (fn_cell->val.type == VAL_FUNC && fn_cell->val.func->type.tag == NODE_STRUCT_DEF) {
        Expr *sdef = fn_cell->val.func;
        Expr *body = expr_child(sdef, 0);

        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = name;   // borrowed from AST
        inst->struct_def = sdef;
        inst->borrowed = 0;
        inst->data = calloc(1, sdef->total_struct_size);
        I32 arg_idx = 1;
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *field = expr_child(body, i);
            if (field->type.decl.is_namespace) continue;
            Expr *arg = expr_child(e, arg_idx++);
            Value val;
            if (arg->type.tag == NODE_IDENT) {
                Cell *src = scope_get(scope, arg->type.str_val);
                val = src->val;
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
        expr_error(e, buf);
        exit(1);
    }

    Expr *func_def = fn_cell->val.func;
    Expr *body = expr_child(func_def, 0);

    // Guard: skip call if first 'own' param is val_none, borrowed struct, or VAL_PTR
    if (func_def->type.func_def.nparam > 0 &&
        func_def->type.func_def.param_owns &&
        func_def->type.func_def.param_owns[0] &&
        e->children.count > 1 && expr_child(e, 1)->type.tag == NODE_IDENT) {
        Cell *fc = scope_get(scope, expr_child(e, 1)->type.str_val);
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
    U32 nparam = func_def->type.func_def.nparam;
    for (U32 i = 0; i < nparam; i++) {
        Expr *arg_expr = expr_child(e, i + 1);
        if (arg_expr->type.tag == NODE_IDENT) {
            Cell *arg_cell = scope_get(scope, arg_expr->type.str_val);
            scope_set_borrowed(call_scope, func_def->type.func_def.param_names[i], arg_cell);
        } else {
            Value arg = eval_expr(scope, arg_expr);
            scope_set_owned(call_scope, func_def->type.func_def.param_names[i], arg);
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
    switch (e->type.tag) {
    case NODE_LITERAL_STR:
        return make_str_value((const char *)e->type.str_val->c_str, e->type.str_val->count);
    case NODE_LITERAL_NUM:
        if (e->til_type == TIL_TYPE_U8)
            return val_u8(atoll((const char *)e->type.str_val->c_str));
        if (e->til_type == TIL_TYPE_U32)
            return val_u32(atoll((const char *)e->type.str_val->c_str));
        if (e->til_type == TIL_TYPE_U64)
            return val_u64((U64)strtoull((const char *)e->type.str_val->c_str, NULL, 10));
        if (e->til_type == TIL_TYPE_I16)
            return val_i16(atoll((const char *)e->type.str_val->c_str));
        if (e->til_type == TIL_TYPE_I32)
            return val_i32(atoll((const char *)e->type.str_val->c_str));
        if (e->til_type == TIL_TYPE_F32)
            return val_f32((F32)atof((const char *)e->type.str_val->c_str));
        return val_i64(atoll((const char *)e->type.str_val->c_str));
    case NODE_LITERAL_BOOL:
        return val_bool(Str_eq_c(e->type.str_val, "true"));
    case NODE_LITERAL_NULL:
        return (Value){.type = VAL_PTR, .ptr = NULL};
    case NODE_IDENT: {
        Cell *cell = scope_get(scope, e->type.str_val);
        if (!cell) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined variable '%s'", e->type.str_val->c_str);
            expr_error(e, buf);
            exit(1);
        }
        return cell->val;
    }
    case NODE_FCALL:
        return eval_call(scope, e);
    case NODE_FUNC_DEF:
        return (Value){.type = VAL_FUNC, .func = e};
    case NODE_STRUCT_DEF:
    case NODE_ENUM_DEF:
        return (Value){.type = VAL_FUNC, .func = e};
    case NODE_FIELD_ACCESS: {
        Value obj = eval_expr(scope,expr_child(e, 0));
        Str *fname = e->type.str_val;
        if (e->is_ns_field) {
            Str *sname = obj.type == VAL_STRUCT
                ? obj.instance->struct_name : expr_child(e, 0)->type.str_val;
            Value *nsv = ns_get(sname, fname);
            if (nsv) {
                // Fresh copy of scalar values (prevents alias to namespace map)
                if (nsv->type == VAL_I64) return val_i64(*nsv->i64);
                if (nsv->type == VAL_I32) return val_i32(*nsv->i32);
                // Auto-call zero-arg enum constructors (Token.Eof without parens)
                if (nsv->type == VAL_FUNC && nsv->func &&
                    nsv->func->type.tag == NODE_FUNC_DEF &&
                    nsv->func->type.func_def.func_type == FUNC_EXT_FUNC &&
                    nsv->func->type.func_def.nparam == 0) {
                    Cell *tc = scope_get(scope, sname);
                    if (tc && tc->val.type == VAL_FUNC && tc->val.func->type.tag == NODE_ENUM_DEF) {
                        I32 tag = enum_variant_tag(tc->val.func, fname);
                        if (tag >= 0) {
                            if (enum_has_payloads(tc->val.func))
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
            expr_error(e, buf);
            exit(1);
        }
        if (obj.type == VAL_PTR) {
            Expr *obj_expr = expr_child(e, 0);
            if (obj_expr->struct_name) {
                Cell *tc = scope_get(scope, obj_expr->struct_name);
                if (tc && tc->val.type == VAL_FUNC && tc->val.func->type.tag == NODE_STRUCT_DEF) {
                    StructInstance *inst = malloc(sizeof(StructInstance));
                    inst->struct_name = obj_expr->struct_name;
                    inst->struct_def = tc->val.func;
                    inst->data = obj.ptr;
                    inst->borrowed = 1;
                    obj = (Value){.type = VAL_STRUCT, .instance = inst};
                }
            }
        }
        if (obj.type != VAL_STRUCT) {
            expr_error(e, "field access on non-struct");
            exit(1);
        }
        Expr *fdecl = find_field_decl(obj.instance->struct_def, fname);
        if (!fdecl) {
            char buf[128];
            snprintf(buf, sizeof(buf), "no field '%s'", fname->c_str);
            expr_error(e, buf);
            exit(1);
        }
        return read_field(obj.instance, fdecl);
    }
    default:
        char buf[128];
        snprintf(buf, sizeof(buf), "cannot evaluate node type %d as expression", e->type.tag);
        expr_lang_error(e, buf);
        exit(1);
    }
}

static void eval_body(Scope *scope, Expr *body) {
    for (U32 i = 0; i < body->children.count; i++) {
        if (has_return || has_break || has_continue) return;
        Expr *stmt = expr_child(body, i);
        switch (stmt->type.tag) {
        case NODE_DECL: {
            Expr *rhs = expr_child(stmt, 0);
            if (stmt->type.decl.is_ref && rhs->type.tag == NODE_IDENT) {
                // Ref decl from ident: borrow the same cell (no move, no free)
                Cell *src = scope_get(scope, rhs->type.str_val);
                scope_set_borrowed(scope, stmt->type.decl.name, src);
            } else {
                Value val;
                if (rhs->type.tag == NODE_IDENT) {
                    // Move semantics: transfer value from source, null source
                    Cell *src = scope_get(scope, rhs->type.str_val);
                    if (!src) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "undefined variable '%s'", rhs->type.str_val->c_str);
                        expr_error(rhs, buf);
                        exit(1);
                    }
                    val = src->val;
                    src->val = val_none();
                } else {
                    val = eval_expr(scope,rhs);
                }
                // Reinterpret VAL_PTR based on declared type (ref a : I64 = ptr_add(...))
                // Only for ref decls — own decls keep VAL_PTR (they own a buffer, not a single element)
                // Skip narrowing for NULL pointers (null literal)
                if (val.type == VAL_PTR && val.ptr != NULL && stmt->type.decl.explicit_type && stmt->type.decl.is_ref) {
                    Str *etype = stmt->type.decl.explicit_type;
                    if (Str_eq_c(etype, "I64"))
                        val = (Value){.type = VAL_I64, .i64 = (I64 *)val.ptr};
                    else if (Str_eq_c(etype, "U8"))
                        val = (Value){.type = VAL_U8, .u8 = (U8 *)val.ptr};
                    else if (Str_eq_c(etype, "I16"))
                        val = (Value){.type = VAL_I16, .i16 = (I16 *)val.ptr};
                    else if (Str_eq_c(etype, "I32"))
                        val = (Value){.type = VAL_I32, .i32 = (I32 *)val.ptr};
                    else if (Str_eq_c(etype, "U32"))
                        val = (Value){.type = VAL_U32, .u32 = (U32 *)val.ptr};
                    else if (Str_eq_c(etype, "U64"))
                        val = (Value){.type = VAL_U64, .u64 = (U64 *)val.ptr};
                    else if (Str_eq_c(etype, "F32"))
                        val = (Value){.type = VAL_F32, .f32 = (F32 *)val.ptr};
                    else if (Str_eq_c(etype, "Bool"))
                        val = (Value){.type = VAL_BOOL, .boolean = (Bool *)val.ptr};
                    else if (Str_eq_c(etype, "Str")) {
                        Str *sp = (Str *)val.ptr;
                        val = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else {
                        // User-defined struct: wrap ptr in borrowed StructInstance
                        Cell *tc = scope_get(scope, etype);
                        if (tc && tc->val.type == VAL_FUNC && tc->val.func->type.tag == NODE_STRUCT_DEF) {
                            StructInstance *inst = malloc(sizeof(StructInstance));
                            inst->struct_name = etype;
                            inst->struct_def = tc->val.func;
                            inst->data = val.ptr;
                            inst->borrowed = stmt->type.decl.is_mut ? 1 : 0;
                            val = (Value){.type = VAL_STRUCT, .instance = inst};
                        }
                    }
                }
                scope_set_owned(scope, stmt->type.decl.name, val);
            }
            break;
        }
        case NODE_ASSIGN: {
            Expr *rhs = expr_child(stmt, 0);
            Cell *cell = scope_get(scope, stmt->type.str_val);
            if (!cell) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined variable '%s'", stmt->type.str_val->c_str);
                expr_error(stmt, buf);
                exit(1);
            }
            if (rhs->type.tag == NODE_IDENT) {
                // Move semantics: transfer value from source, null source
                Cell *src = scope_get(scope, rhs->type.str_val);
                free_value(cell->val);
                cell->val = src->val;
                src->val = val_none();
            } else {
                Value new_val = eval_expr(scope,rhs);
                free_value(cell->val);
                cell->val = new_val;
            }
            break;
        }
        case NODE_FIELD_ASSIGN: {
            Expr *val_expr = expr_child(stmt, 1);
            Value val;
            Cell *move_src = NULL;
            if (val_expr->type.tag == NODE_IDENT) {
                move_src = scope_get(scope, val_expr->type.str_val);
                val = move_src->val;
            } else {
                val = eval_expr(scope, val_expr);
            }
            Str *fname = stmt->type.str_val;
            if (stmt->is_ns_field) {
                Value obj = eval_expr(scope, expr_child(stmt, 0));
                Str *sname = obj.type == VAL_STRUCT
                    ? obj.instance->struct_name : expr_child(stmt, 0)->type.str_val;
                ns_set(sname, fname, val);
                if (move_src) move_src->val = val_none();
            } else {
                // Resolve to the flat buffer + struct_def where the field lives
                void *base = NULL;
                Expr *cur_sdef = NULL;
                Expr *obj_expr = expr_child(stmt, 0);
                if (obj_expr->type.tag == NODE_IDENT) {
                    Cell *cell = scope_get(scope, obj_expr->type.str_val);
                    if (cell && cell->val.type == VAL_STRUCT) {
                        base = cell->val.instance->data;
                        cur_sdef = cell->val.instance->struct_def;
                    }
                } else if (obj_expr->type.tag == NODE_FIELD_ACCESS) {
                    // Chained: e.g. l1.start.x — walk chain to compute offset
                    Expr *chain[32]; I32 depth = 0;
                    Expr *cur = obj_expr;
                    while (cur->type.tag == NODE_FIELD_ACCESS) {
                        chain[depth++] = cur;
                        cur = expr_child(cur, 0);
                    }
                    Cell *cell = scope_get(scope, cur->type.str_val);
                    if (cell && cell->val.type == VAL_STRUCT) {
                        base = cell->val.instance->data;
                        cur_sdef = cell->val.instance->struct_def;
                        for (I32 d = depth - 1; d >= 0; d--) {
                            Expr *fd = find_field_decl(cur_sdef, chain[d]->type.str_val);
                            if (!fd) { base = NULL; break; }
                            if (fd->type.decl.is_own || fd->type.decl.is_ref) {
                                base = *(void **)((char *)base + fd->type.decl.field_offset);
                            } else {
                                base = (char *)base + fd->type.decl.field_offset;
                            }
                            cur_sdef = fd->type.decl.field_struct_def;
                            if (!cur_sdef) { base = NULL; break; }
                        }
                    }
                }
                if (!base || !cur_sdef) {
                    expr_error(stmt, "field assign on non-struct");
                    exit(1);
                }
                Expr *fdecl = find_field_decl(cur_sdef, fname);
                void *ptr = (char *)base + fdecl->type.decl.field_offset;
                // Write value directly at computed address
                I32 fsz = fdecl->type.decl.field_size;
                if (fdecl->type.decl.is_own) {
                    *(void **)ptr = val.type == VAL_STRUCT ? val.instance->data : val.ptr;
                    if (val.type == VAL_STRUCT) free(val.instance);
                } else if (fdecl->type.decl.is_ref) {
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
                    default: break;
                    }
                }
                if (move_src) move_src->val = val_none();
            }
            break;
        }
        case NODE_FCALL:
            eval_call(scope, stmt);
            break;
        case NODE_BODY: {
            Scope *block_scope = scope_new(scope);
            eval_body(block_scope, stmt);
            scope_free(block_scope);
            break;
        }
        case NODE_IF: {
            Value cond = eval_expr(scope,expr_child(stmt, 0));
            if (*cond.boolean) {
                Scope *then_scope = scope_new(scope);
                eval_body(then_scope, expr_child(stmt, 1));
                scope_free(then_scope);
            } else if (stmt->children.count > 2) {
                Scope *else_scope = scope_new(scope);
                eval_body(else_scope, expr_child(stmt, 2));
                scope_free(else_scope);
            }
            break;
        }
        case NODE_WHILE: {
            while (1) {
                if (has_return) break;
                Value cond = eval_expr(scope,expr_child(stmt, 0));
                if (!*cond.boolean) break;
                Scope *while_scope = scope_new(scope);
                eval_body(while_scope, expr_child(stmt, 1));
                scope_free(while_scope);
                if (has_break) { has_break = 0; break; }
                if (has_continue) { has_continue = 0; }
            }
            break;
        }
        case NODE_BREAK:
            has_break = 1;
            return;
        case NODE_CONTINUE:
            has_continue = 1;
            return;
        case NODE_RETURN:
            if (stmt->children.count > 0) {
                return_value = eval_expr(scope,expr_child(stmt, 0));
            } else {
                return_value = val_none();
            }
            has_return = 1;
            return;
        default:
            char buf[128];
            snprintf(buf, sizeof(buf), "unexpected statement type %d", stmt->type.tag);
            expr_lang_error(stmt, buf);
            exit(1);
        }
    }
}

void interpreter_init_ns(Scope *global, Expr *program) {
    { Map *_mp = Map_new(Str_new("Str"), &(U64){sizeof(Str)}, Str_new(""), &(U64){sizeof(Value)}); ns_fields = *_mp; free(_mp); }
    { Vec *_vp = Vec_new(Str_new(""), &(U64){sizeof(Str *)}); ns_keys = *_vp; free(_vp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag == NODE_DECL && (expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
                                        expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF)) {
            Str *sname = stmt->type.decl.name;
            Expr *sdef = expr_child(stmt, 0);
            // Cache struct defs for C-side construction
            if (sdef->type.tag == NODE_STRUCT_DEF) {
                if (Str_eq_c(sname, "Str"))   { cached_str_def = sdef; cached_str_name = sname; }
                if (Str_eq_c(sname, "Array")) { cached_array_def = sdef; cached_array_name = sname; }
                if (Str_eq_c(sname, "Vec"))   { cached_vec_def = sdef; cached_vec_name = sname; }
            }
            Expr *body = expr_child(sdef, 0);
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = expr_child(body, j);
                if (field->type.decl.is_namespace) {
                    Value fval = eval_expr(global, expr_child(field, 0));
                    // Simple enum variant tags: convert I64 literal to I32 (matching C enum)
                    if (sdef->type.tag == NODE_ENUM_DEF && !enum_has_payloads(sdef) &&
                        fval.type == VAL_I64) {
                        I32 tag = (I32)*fval.i64;
                        free(fval.i64);
                        fval = val_i32(tag);
                    }
                    ns_set(sname, field->type.decl.name, fval);
                }
            }
        }
    }
}

static Value parse_cli_arg(const char *s, Str *type_name) {
    if (Str_eq_c(type_name, "Str")) return make_str_value(s, strlen(s));
    if (Str_eq_c(type_name, "I64")) {
        char *end;
        I64 v = strtoll(s, &end, 10);
        if (*end != '\0') {
            fprintf(stderr, "error: cannot parse '%s' as I64\n", s);
            exit(1);
        }
        return val_i64(v);
    }
    if (Str_eq_c(type_name, "U8")) {
        char *end;
        long v = strtol(s, &end, 10);
        if (*end != '\0' || v < 0 || v > 255) {
            fprintf(stderr, "error: cannot parse '%s' as U8\n", s);
            exit(1);
        }
        return val_u8(v);
    }
    if (Str_eq_c(type_name, "I16")) {
        char *end;
        long v = strtol(s, &end, 10);
        if (*end != '\0' || v < -32768 || v > 32767) {
            fprintf(stderr, "error: cannot parse '%s' as I16\n", s);
            exit(1);
        }
        return val_i16(v);
    }
    if (Str_eq_c(type_name, "I32")) {
        char *end;
        long v = strtol(s, &end, 10);
        if (*end != '\0' || v < -2147483648L || v > 2147483647L) {
            fprintf(stderr, "error: cannot parse '%s' as I32\n", s);
            exit(1);
        }
        return val_i32(v);
    }
    if (Str_eq_c(type_name, "U32")) {
        char *end;
        unsigned long v = strtoul(s, &end, 10);
        if (*end != '\0' || v > 0xFFFFFFFF) {
            fprintf(stderr, "error: cannot parse '%s' as U32\n", s);
            exit(1);
        }
        return val_u32(v);
    }
    if (Str_eq_c(type_name, "Bool")) {
        if (strcmp(s, "true") == 0) return val_bool(1);
        if (strcmp(s, "false") == 0) return val_bool(0);
        fprintf(stderr, "error: cannot parse '%s' as Bool (expected true/false)\n", s);
        exit(1);
    }
    fprintf(stderr, "error: unsupported CLI argument type '%s'\n", type_name->c_str);
    exit(1);
}

static I32 elem_size_for_type(Str *type_name) {
    if (Str_eq_c(type_name, "I64")) return (I32)sizeof(I64);
    if (Str_eq_c(type_name, "U8"))  return (I32)sizeof(U8);
    if (Str_eq_c(type_name, "I16")) return (I32)sizeof(I16);
    if (Str_eq_c(type_name, "I32")) return (I32)sizeof(I32);
    if (Str_eq_c(type_name, "U32")) return (I32)sizeof(U32);
    if (Str_eq_c(type_name, "Bool")) return (I32)sizeof(Bool);
    if (Str_eq_c(type_name, "Str")) return 24; // til Str = {U8*, I64 len, I64 cap}
    return 8;
}

static void value_to_buf(void *dest, Value v, Str *type_name) {
    if (Str_eq_c(type_name, "I64"))       { memcpy(dest, v.i64, sizeof(I64)); free(v.i64); }
    else if (Str_eq_c(type_name, "U8"))   { memcpy(dest, v.u8, sizeof(U8)); free(v.u8); }
    else if (Str_eq_c(type_name, "I16"))  { memcpy(dest, v.i16, sizeof(I16)); free(v.i16); }
    else if (Str_eq_c(type_name, "I32"))  { memcpy(dest, v.i32, sizeof(I32)); free(v.i32); }
    else if (Str_eq_c(type_name, "U32"))  { memcpy(dest, v.u32, sizeof(U32)); free(v.u32); }
    else if (Str_eq_c(type_name, "Bool")) { memcpy(dest, v.boolean, sizeof(Bool)); free(v.boolean); }
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
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag == NODE_DECL &&
            (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF ||
             expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
             expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF)) {
            Value val = {.type = VAL_FUNC, .func = expr_child(stmt, 0)};
            scope_set_owned(global, stmt->type.decl.name, val);
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
            Expr *stmt = expr_child(program, i);
            if (stmt->type.tag != NODE_DECL) continue;
            Expr *rhs = expr_child(stmt, 0);
            if (rhs->type.tag != NODE_FUNC_DEF) continue;
            if (rhs->type.func_def.func_type != FUNC_TEST) continue;
            Str *tname = stmt->type.decl.name;
            test_count++;
            Scope *test_scope = scope_new(global);
            eval_body(test_scope, expr_child(rhs, 0));
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
            fprintf(stderr, "%s: error: mode '%s' requires a 'main' proc\n", path->c_str, mode->name);
            scope_free(global);
            return 1;
        }
        Expr *func_def = main_cell->val.func;
        U32 nparam = func_def->type.func_def.nparam;
        I32 vi = func_def->type.func_def.variadic_index;
        Expr *body = expr_child(func_def, 0);
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
                    Value arr = build_argv_array(va_count, user_argv + argi, func_def->type.func_def.param_types[vi]);
                    scope_set_owned(main_scope, func_def->type.func_def.param_names[i], arr);
                    argi += va_count;
                } else {
                    Value v = parse_cli_arg(user_argv[argi], func_def->type.func_def.param_types[i]);
                    scope_set_owned(main_scope, func_def->type.func_def.param_names[i], v);
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
