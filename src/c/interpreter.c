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

// Forward declaration (defined in dispatch.c)
void ffi_init_scan_program(Expr *program);

// Forward declarations (defined in ast.c)

// free_value: moved to interpreter.til


#define ENUM_PAYLOAD_OFFSET ((I32)sizeof(I64))

// Check if a FieldAccess/FieldAssign accesses a namespace field.
static Bool interp_fa_is_ns(Scope *scope, Expr *e) {
    Expr *obj_expr = Expr_child(e, &(USize){(USize)(0)});
    Str *sname = &obj_expr->struct_name;
    if (!sname->count && obj_expr->data.tag == NodeType_TAG_Ident)
        sname = &obj_expr->data.data.Ident;
    Cell *tc = scope_get(scope, sname);
    if (!tc || tc->val.tag != Value_TAG_Func) return 0;
    Expr *sdef = (Expr*)tc->val.data.Func;
    if (sdef->data.tag != NodeType_TAG_StructDef && sdef->data.tag != NodeType_TAG_EnumDef) return 0;
    Str *fname = (e->data.tag == NodeType_TAG_FieldAccess)
        ? &e->data.data.FieldAccess : &e->data.data.FieldAssign;
    // Search body for namespace and instance fields with this name
    Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
    Bool has_ns = 0, has_inst = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(USize){(USize)(i)});
        if (Str_eq(&f->data.data.Decl.name, fname)) {
            if (f->data.data.Decl.is_namespace) has_ns = 1;
            else has_inst = 1;
        }
    }
    if (has_ns && !has_inst) return 1;
    if (!has_ns && !has_inst) {
        // No field found; namespace if object is a type name
        if (obj_expr->data.tag == NodeType_TAG_Ident &&
            (Str_eq(&obj_expr->data.data.Ident, sname) ||
             (obj_expr->data.data.Ident.count > 0 &&
              obj_expr->data.data.Ident.c_str[0] >= 'A' &&
              obj_expr->data.data.Ident.c_str[0] <= 'Z')))
            return 1;
        return 0;
    }
    if (has_ns && has_inst) {
        // Both exist: namespace if object is a type name
        if (obj_expr->data.tag != NodeType_TAG_Ident) return 0;
        if (Str_eq(&obj_expr->data.data.Ident, sname)) return 1;
        if (obj_expr->data.data.Ident.count > 0 &&
            obj_expr->data.data.Ident.c_str[0] >= 'A' &&
            obj_expr->data.data.Ident.c_str[0] <= 'Z')
            return 1;
    }
    return 0;
}

// --- Implicit numeric widening ---
// Extract raw integer from a numeric Value and re-create as target type.
// Returns the original value unchanged if no widening applies.
static Value *widen_numeric(Value *v, Str *ptype) {
    if (!ptype || ptype->count == 0) { Value *r = malloc(sizeof(Value)); *r = *v; return r; }
    // Extract source value as I64/U64
    I64 ival = 0; U64 uval = 0; Bool is_unsigned = 0;
    switch (v->tag) {
        case Value_TAG_Byte:  uval = v->data.Byte; is_unsigned = 1; break;
        case Value_TAG_Short: ival = v->data.Short; break;
        case Value_TAG_Int32: ival = v->data.Int32; break;
        case Value_TAG_Uint32: uval = v->data.Uint32; is_unsigned = 1; break;
        default: { Value *r = malloc(sizeof(Value)); *r = *v; return r; }
    }
    if (!is_unsigned) uval = (U64)ival;
    else ival = (I64)uval;
    // Check target type and widen
    Value *r = malloc(sizeof(Value));
    if (ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0) {
        *r = val_i64(is_unsigned ? (I64)uval : ival); return r;
    }
    if (ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0) {
        *r = val_u64(uval); return r;
    }
    if (ptype->count == 5 && memcmp(ptype->c_str, "USize", 5) == 0) {
        *r = val_u32((U32)uval); return r;
    }
    if (ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0 && v->tag == Value_TAG_Byte) {
        *r = val_u32((I64)uval); return r;
    }
    if (ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0) {
        if (v->tag == Value_TAG_Byte) { *r = val_i32(ival); return r; }
        if (v->tag == Value_TAG_Short) { *r = val_i32(ival); return r; }
    }
    if (ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0 && v->tag == Value_TAG_Byte) {
        *r = val_i16(ival); return r;
    }
    *r = *v; return r;
}

// needs_widen: moved to interpreter.til

// --- Scope / environment ---

Scope *scope_new(Scope *parent) {
    Scope *s = malloc(sizeof(Scope));
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Binding", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Binding)}); s->bindings = *_mp; free(_mp); }
    s->parent = parent;
    return s;
}

void scope_free(Scope *s) {
    for (U32 i = 0; i < s->bindings.count; i++) {
        Binding *b = (Binding *)(s->bindings.val_data + i * s->bindings.val_size);
        if (b->cell_is_local) {
            // Free Enum data (no aliasing risk -- enum data is always owned).
            // Struct data may be aliased via borrowed refs, so skip for now (#127).
            if (b->cell->val.tag == Value_TAG_Enum && b->cell->val.data.Enum.data)
                free(b->cell->val.data.Enum.data);
            free(b->cell);
        }
    }
    Map_delete(&s->bindings, &(Bool){0});
    free(s);
}

void scope_set_owned(Scope *s, Str *name, Value *val) {
    if (Map_has(&s->bindings, name)) {
        Binding *b = Map_get(&s->bindings, name);
        free_value(b->cell->val);
        b->cell->val = *val;
        return;
    }
    Cell *cell = malloc(sizeof(Cell));
    cell->val = *val;
    Binding nb = {name, cell, 1};
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW}; void *_v = malloc(sizeof(nb)); memcpy(_v, &nb, sizeof(nb)); Map_set(&s->bindings, _k, _v); }
}

static void scope_set_borrowed(Scope *s, Str *name, Cell *cell) {
    Binding b = {name, cell, 0};
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW}; void *_v = malloc(sizeof(b)); memcpy(_v, &b, sizeof(b)); Map_set(&s->bindings, _k, _v); }
}

// scope_get: moved to interpreter.til

// ext_function_dispatch is in dispatch.c

// --- Cached struct defs for C-side construction ---
Expr *cached_str_def;
Str *cached_str_name;
Expr *cached_array_def;
Str *cached_array_name;
Expr *cached_vec_def;
Str *cached_vec_name;



// Read a Value from flat buffer at a field decl's offset
static Value read_field(StructInstance *inst, Expr *fdecl) {
    void *ptr = (char *)inst->data + fdecl->data.data.Decl.field_offset;
    if (DECL_IS_OWN(fdecl->data.data.Decl)) {
        void *owned = *(void **)ptr;
        // If the own field has a struct def, wrap in StructInstance for field access
        if (fdecl->data.data.Decl.field_struct_def) {
            Expr *nested = fdecl->data.data.Decl.field_struct_def;
            Str *ftype = &fdecl->data.data.Decl.explicit_type;
            Value result;
            result.tag = Value_TAG_Struct;
            result.data.Struct.struct_name = ftype;
            result.data.Struct.struct_def = nested;
            result.data.Struct.data = owned; // borrowed — points into the owning struct's heap alloc
            result.data.Struct.borrowed = 1;
            return result;
        }
        return (Value){.tag = Value_TAG_Ptr, .data.Ptr = owned};
    }
    if (DECL_IS_REF(fdecl->data.data.Decl)) {
        void *ref_ptr = *(void **)ptr;
        if (!ref_ptr) return (Value){.tag = Value_TAG_Ptr, .data.Ptr = NULL};
        if (fdecl->data.data.Decl.field_struct_def) {
            Expr *nested = fdecl->data.data.Decl.field_struct_def;
            Str *ftype = &fdecl->data.data.Decl.explicit_type;
            Value result;
            result.tag = Value_TAG_Struct;
            result.data.Struct.struct_name = ftype;
            result.data.Struct.struct_def = nested;
            result.data.Struct.data = ref_ptr;
            result.data.Struct.borrowed = 1;
            return result;
        }
        return (Value){.tag = Value_TAG_Ptr, .data.Ptr = ref_ptr};
    }
    Str *ftype = &fdecl->data.data.Decl.explicit_type;
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "I64", 3) == 0))  return val_i64(*(I64 *)ptr);
    if (ftype && (ftype->count == 2 && memcmp(ftype->c_str, "U8", 2) == 0))   return val_u8(*(U8 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "I16", 3) == 0))  return val_i16(*(I16 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "I32", 3) == 0))  return val_i32(*(I32 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "U32", 3) == 0))  return val_u32(*(U32 *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "U64", 3) == 0))  return val_u64(*(U64 *)ptr);
    if (ftype && (ftype->count == 5 && memcmp(ftype->c_str, "USize", 5) == 0)) return val_u32(*(USize *)ptr);
    if (ftype && (ftype->count == 3 && memcmp(ftype->c_str, "F32", 3) == 0))  return val_f32(*(F32 *)ptr);
    if (ftype && (ftype->count == 4 && memcmp(ftype->c_str, "Bool", 4) == 0)) return val_bool(*(Bool *)ptr);
    // Enum field: payload enums stored as EnumInstance *, simple enums as I32
    if (fdecl->data.data.Decl.field_struct_def &&
        fdecl->data.data.Decl.field_struct_def->data.tag == NodeType_TAG_EnumDef) {
        Expr *edef = fdecl->data.data.Decl.field_struct_def;
        if (enum_has_payloads(edef)) {
            EnumInstance *ei = *(EnumInstance **)ptr;
            if (!ei) return val_enum_simple(ftype, 0);
            // Clone: allocate new flat buffer, copy data
            I32 etag = *(I32 *)ei->data;
            I32 psz = ei->data_size - ENUM_PAYLOAD_OFFSET;
            if (psz < 0) psz = 0;
            return val_enum_flat(ei->enum_name, edef, etag,
                                 ei->data + ENUM_PAYLOAD_OFFSET, psz);
        }
        return val_i32(*(I32 *)ptr);
    }
    // Inline struct: borrow if parent is borrowed, copy otherwise
    if (fdecl->data.data.Decl.field_struct_def) {
        Expr *nested = fdecl->data.data.Decl.field_struct_def;
        Value result;
        result.tag = Value_TAG_Struct;
        result.data.Struct.struct_name = ftype; // borrowed — set by initer for inferred struct types
        result.data.Struct.struct_def = nested;
        result.data.Struct.data = ptr;       // always point into parent buffer
        result.data.Struct.borrowed = 1;     // always borrowed — field lives in parent
        return result;
    }
    // FuncSig-typed field: stored as Expr * pointer (func ptr)
    if (ftype) {
        void *stored = *(void **)ptr;
        if (stored) return (Value){.tag = Value_TAG_Func, .data.Func = stored};
    }
    // Fallback: treat as I64
    return val_i64(*(I64 *)ptr);
}

// Write a Value into flat buffer at a field decl's offset
void write_field(StructInstance *inst, Expr *fdecl, Value *val) {
    void *ptr = (char *)inst->data + fdecl->data.data.Decl.field_offset;
    I32 fsz = fdecl->data.data.Decl.field_size;
    if (DECL_IS_OWN(fdecl->data.data.Decl)) {
        *(void **)ptr = val->tag == Value_TAG_Struct ? val->data.Struct.data : val->data.Ptr;
        return;
    }
    if (DECL_IS_REF(fdecl->data.data.Decl)) {
        // ref field: store pointer (don't own the data)
        if (val->tag == Value_TAG_Ptr) *(void **)ptr = val->data.Ptr;
        else if (val->tag == Value_TAG_Struct) {
            *(void **)ptr = val->data.Struct.data;
        }
        else *(void **)ptr = NULL;
        return;
    }
    switch (val->tag) {
    case Value_TAG_Int:  *(I64 *)ptr = val->data.Int; break;
    case Value_TAG_Byte:   *(U8 *)ptr = val->data.Byte; break;
    case Value_TAG_Short:  *(I16 *)ptr = val->data.Short; break;
    case Value_TAG_Int32:  *(I32 *)ptr = val->data.Int32; break;
    case Value_TAG_Uint32:  *(U32 *)ptr = val->data.Uint32; break;
    case Value_TAG_Uint64:  *(U64 *)ptr = val->data.Uint64; break;
    case Value_TAG_Float:  *(F32 *)ptr = val->data.Float; break;
    case Value_TAG_Boolean: *(Bool *)ptr = val->data.Boolean; break;
    case Value_TAG_Struct:
        if (val->data.Struct.borrowed) {
            Value *cloned = Value_clone(val);
            memcpy(ptr, cloned->data.Struct.data, fsz);
            free(cloned->data.Struct.data);
            free(cloned);
        } else {
            memcpy(ptr, val->data.Struct.data, fsz);
            free(val->data.Struct.data);
        }
        break;
    case Value_TAG_Enum: {
        EnumInstance *existing = *(EnumInstance **)ptr;
        if (existing) { free(existing->data); free(existing); }
        EnumInstance *ei = malloc(sizeof(EnumInstance));
        *ei = val->data.Enum;
        // Deep-copy the flat data buffer
        I32 total = val->data.Enum.data_size;
        if (total < (I32)sizeof(I64)) total = sizeof(I64);
        ei->data = malloc(total);
        memcpy(ei->data, val->data.Enum.data, total);
        *(EnumInstance **)ptr = ei;
        break;
    }
    case Value_TAG_Ptr:  *(void **)ptr = val->data.Ptr; break;
    case Value_TAG_Func: *(void **)ptr = val->data.Func; break;
    default: break;
    }
}

// Build a Str StructInstance from C string data (copies data via strndup)
Value make_str_value(void *data, U64 len) {
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = cached_str_name;
    inst->struct_def = cached_str_def;
    inst->data = malloc(sizeof(Str));
    inst->borrowed = 0;
    *(char **)inst->data = strndup(data, len);
    *(USize *)((char *)inst->data + sizeof(U8 *)) = (USize)len;
    *(USize *)((char *)inst->data + sizeof(U8 *) + sizeof(USize)) = CAP_LIT;
    Value result;
    result.tag = Value_TAG_Struct;
    result.data.Struct = *inst;
    free(inst);
    return result;
}

// Build a Str StructInstance taking ownership of buffer (no copy)
Value make_str_value_own(void *data, U64 len) {
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = cached_str_name;
    inst->struct_def = cached_str_def;
    inst->borrowed = 0;
    inst->data = malloc(sizeof(Str));
    *(char **)inst->data = data;
    *(USize *)((char *)inst->data + sizeof(U8 *)) = (USize)len;
    *(USize *)((char *)inst->data + sizeof(U8 *) + sizeof(USize)) = (USize)len;
    Value result;
    result.tag = Value_TAG_Struct;
    result.data.Struct = *inst;
    free(inst);
    return result;
}

// Extract a C Str view from a Str StructInstance (stack-local, don't free)
Str str_view(Value v) {
    char *data = *(char **)v.data.Struct.data;
    USize len = *(USize *)((char *)v.data.Struct.data + sizeof(U8 *));
    return (Str){.c_str = (U8 *)data, .count = len, .cap = CAP_VIEW};
}

// Deep-clone a StructInstance: walks struct_def fields for Str, own, enum, inline structs.
// Called from StructInstance.clone in til (ext_func).
StructInstance *clone_struct_instance(StructInstance *src) {
    StructInstance *dst = malloc(sizeof(StructInstance));
    dst->struct_name = src->struct_name;
    dst->struct_def = src->struct_def;
    dst->borrowed = 0;
    I32 sz = src->struct_def->data.data.StructDef.total_struct_size;
    dst->data = malloc(sz);
    memcpy(dst->data, src->data, sz);
    if ((src->struct_name->count == 3 && memcmp(src->struct_name->c_str, "Str", 3) == 0)) {
        Str *s = (Str *)src->data;
        if (s->count > 0 && s->c_str)
            *(char **)dst->data = strndup((const char *)s->c_str, s->count);
        return dst;
    }
    Expr *body = Expr_child(src->struct_def, &(USize){(USize)(0)});
    for (U32 fi = 0; fi < body->children.count; fi++) {
        Expr *field = Expr_child(body, &(USize){(USize)(fi)});
        if (field->data.data.Decl.is_namespace) continue;
        I32 foff = field->data.data.Decl.field_offset;
        Str *ftype = &field->data.data.Decl.explicit_type;
        if (DECL_IS_OWN(field->data.data.Decl)) {
            void *src_ptr = *(void **)((char *)src->data + foff);
            if (src_ptr && field->data.data.Decl.field_struct_def) {
                StructInstance tmp = {ftype, field->data.data.Decl.field_struct_def, src_ptr, 1};
                StructInstance *cloned = clone_struct_instance(&tmp);
                *(void **)((char *)dst->data + foff) = cloned->data;
                free(cloned);
            }
            continue;
        }
        if (DECL_IS_REF(field->data.data.Decl)) continue;
        if (ftype && ftype->count == 3 && memcmp(ftype->c_str, "Str", 3) == 0) {
            Str *s = (Str *)((char *)src->data + foff);
            if (s->count > 0 && s->c_str)
                *(char **)((char *)dst->data + foff) = strndup((const char *)s->c_str, s->count);
            continue;
        }
        if (field->data.data.Decl.field_struct_def &&
            field->data.data.Decl.field_struct_def->data.tag == NodeType_TAG_EnumDef &&
            enum_has_payloads(field->data.data.Decl.field_struct_def)) {
            EnumInstance *ei = *(EnumInstance **)((char *)src->data + foff);
            if (ei) {
                EnumInstance *clone = EnumInstance_clone(ei);
                *(EnumInstance **)((char *)dst->data + foff) = clone;
            }
            continue;
        }
        if (field->data.data.Decl.field_struct_def &&
            field->data.data.Decl.field_struct_def->data.tag != NodeType_TAG_EnumDef) {
            Expr *nested = field->data.data.Decl.field_struct_def;
            StructInstance tmp = {ftype, nested, (U8 *)src->data + foff, 1};
            StructInstance *cloned = clone_struct_instance(&tmp);
            memcpy((char *)dst->data + foff, cloned->data, nested->data.data.StructDef.total_struct_size);
            free(cloned->data); free(cloned);
            continue;
        }
    }
    return dst;
}



// values_equal: dead code, deleted

// --- Eval ---

static void eval_body(Scope *scope, Expr *body);

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
        for (U32 i = 0; i < func_def->data.data.FuncDef.nparam; i++) {
            Param *_ipi = (Param*)Vec_get(&func_def->data.data.FuncDef.params, &(USize){(USize)(i)});
            Expr *arg_expr = Expr_child(e, &(USize){(USize)(i + 1)});
            if (arg_expr->data.tag == NodeType_TAG_Ident) {
                Cell *arg_cell = scope_get(scope, &arg_expr->data.data.Ident);
                // Reinterpret Value_TAG_Ptr based on param type
                if (arg_cell->val.tag == Value_TAG_Ptr && _ipi->ptype.count > 0) {
                    Str *ptype = &_ipi->ptype;
                    Value arg = arg_cell->val;
                    if ((ptype->count == 3 && memcmp(ptype->c_str, "Str", 3) == 0)) {
                        Str *sp = (Str *)arg.data.Ptr;
                        arg = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0))
                        arg = val_i64(*(I64 *)arg.data.Ptr);
                    else if ((ptype->count == 2 && memcmp(ptype->c_str, "U8", 2) == 0))
                        arg = val_u8(*(U8 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0))
                        arg = val_i16(*(I16 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0))
                        arg = val_i32(*(I32 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0))
                        arg = val_u32(*(U32 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0))
                        arg = val_u64(*(U64 *)arg.data.Ptr);
                    else if ((ptype->count == 5 && memcmp(ptype->c_str, "USize", 5) == 0))
                        arg = val_u32(*(USize *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "F32", 3) == 0))
                        arg = val_f32(*(F32 *)arg.data.Ptr);
                    else if ((ptype->count == 4 && memcmp(ptype->c_str, "Bool", 4) == 0))
                        arg = val_bool(*(Bool *)arg.data.Ptr);
                    { Value *_w = widen_numeric(&arg, ptype); arg = *_w; free(_w); }
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
                // Reinterpret Value_TAG_Ptr based on param type (same as ref decl)
                if (arg.tag == Value_TAG_Ptr && _ipi->ptype.count > 0) {
                    Str *ptype = &_ipi->ptype;
                    if ((ptype->count == 3 && memcmp(ptype->c_str, "Str", 3) == 0)) {
                        Str *sp = (Str *)arg.data.Ptr;
                        arg = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I64", 3) == 0))
                        arg = val_i64(*(I64 *)arg.data.Ptr);
                    else if ((ptype->count == 2 && memcmp(ptype->c_str, "U8", 2) == 0))
                        arg = val_u8(*(U8 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I16", 3) == 0))
                        arg = val_i16(*(I16 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "I32", 3) == 0))
                        arg = val_i32(*(I32 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U32", 3) == 0))
                        arg = val_u32(*(U32 *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "U64", 3) == 0))
                        arg = val_u64(*(U64 *)arg.data.Ptr);
                    else if ((ptype->count == 5 && memcmp(ptype->c_str, "USize", 5) == 0))
                        arg = val_u32(*(USize *)arg.data.Ptr);
                    else if ((ptype->count == 3 && memcmp(ptype->c_str, "F32", 3) == 0))
                        arg = val_f32(*(F32 *)arg.data.Ptr);
                    else if ((ptype->count == 4 && memcmp(ptype->c_str, "Bool", 4) == 0))
                        arg = val_bool(*(Bool *)arg.data.Ptr);
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

Value eval_expr(Scope *scope, Expr *e) {
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
}

static void eval_body(Scope *scope, Expr *body) {
    for (U32 i = 0; i < body->children.count; i++) {
        if (has_return || has_break || has_continue) return;
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        switch (stmt->data.tag) {
        case NodeType_TAG_Decl: {
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            // Skip type aliases (already pre-registered; typer sets til_type=None, RHS is Ident)
            if (stmt->til_type.tag == TilType_TAG_None && rhs->data.tag == NodeType_TAG_Ident) {
                break;
            }
            if (DECL_IS_REF(stmt->data.data.Decl) && rhs->data.tag == NodeType_TAG_Ident) {
                // Ref decl from ident: borrow the same cell (no move, no free)
                Cell *src = scope_get(scope, &rhs->data.data.Ident);
                scope_set_borrowed(scope, (&stmt->data.data.Decl.name), src);
            } else {
                Value val;
                if (rhs->data.tag == NodeType_TAG_Ident) {
                    // Move semantics: transfer value from source, null source
                    Cell *src = scope_get(scope, &rhs->data.data.Ident);
                    if (!src) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "undefined variable '%s'", rhs->data.data.Ident.c_str);
                        Expr_error(rhs, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
                        exit(1);
                    }
                    val = src->val;
                    if (val.tag != Value_TAG_Func)
                        src->val = val_none();
                } else {
                    val = eval_expr(scope,rhs);
                }
                // Reinterpret Value_TAG_Ptr based on declared type (ref a : I64 = ptr_add(...))
                // Only for ref decls — own decls keep Value_TAG_Ptr (they own a buffer, not a single element)
                // Skip narrowing for NULL pointers (null literal)
                if (val.tag == Value_TAG_Ptr && val.data.Ptr != NULL && (stmt->data.data.Decl.explicit_type).count > 0 && DECL_IS_REF(stmt->data.data.Decl)) {
                    Str *etype = &stmt->data.data.Decl.explicit_type;
                    if ((etype->count == 3 && memcmp(etype->c_str, "I64", 3) == 0))
                        val = val_i64(*(I64 *)val.data.Ptr);
                    else if ((etype->count == 2 && memcmp(etype->c_str, "U8", 2) == 0))
                        val = val_u8(*(U8 *)val.data.Ptr);
                    else if ((etype->count == 3 && memcmp(etype->c_str, "I16", 3) == 0))
                        val = val_i16(*(I16 *)val.data.Ptr);
                    else if ((etype->count == 3 && memcmp(etype->c_str, "I32", 3) == 0))
                        val = val_i32(*(I32 *)val.data.Ptr);
                    else if ((etype->count == 3 && memcmp(etype->c_str, "U32", 3) == 0))
                        val = val_u32(*(U32 *)val.data.Ptr);
                    else if ((etype->count == 3 && memcmp(etype->c_str, "U64", 3) == 0))
                        val = val_u64(*(U64 *)val.data.Ptr);
                    else if ((etype->count == 5 && memcmp(etype->c_str, "USize", 5) == 0))
                        val = val_u32(*(USize *)val.data.Ptr);
                    else if ((etype->count == 3 && memcmp(etype->c_str, "F32", 3) == 0))
                        val = val_f32(*(F32 *)val.data.Ptr);
                    else if ((etype->count == 4 && memcmp(etype->c_str, "Bool", 4) == 0))
                        val = val_bool(*(Bool *)val.data.Ptr);
                    else if ((etype->count == 3 && memcmp(etype->c_str, "Str", 3) == 0)) {
                        Str *sp = (Str *)val.data.Ptr;
                        val = make_str_value_own((char *)sp->c_str, sp->count);
                    }
                    else {
                        // Check for FuncSig type: dereference to get function pointer
                        Cell *tc = scope_get(scope, etype);
                        if (tc && tc->val.tag == Value_TAG_Func &&
                            ((Expr*)tc->val.data.Func)->data.tag == NodeType_TAG_FuncDef &&
                            ((Expr*)tc->val.data.Func)->children.count == 0) {
                            // FuncSig: payload is a function pointer (void *)
                            void *fp = *(void **)val.data.Ptr;
                            val = (Value){.tag = Value_TAG_Func, .data.Func = fp};
                        }
                        // EnumDef: wrap in EnumInstance
                        else if (tc && tc->val.tag == Value_TAG_Func && ((Expr*)tc->val.data.Func)->data.tag == NodeType_TAG_EnumDef) {
                            Expr *edef = (Expr*)tc->val.data.Func;
                            I32 esz = (I32)sizeof(I64);
                            U8 *ecopy = malloc(esz);
                            memcpy(ecopy, val.data.Ptr, esz);
                            val.tag = Value_TAG_Enum;
                            val.data.Enum.enum_name = etype;
                            val.data.Enum.enum_def = edef;
                            val.data.Enum.data = ecopy;
                            val.data.Enum.data_size = esz;
                        }
                        // User-defined struct: wrap ptr in borrowed StructInstance
                        else if (tc && tc->val.tag == Value_TAG_Func && ((Expr*)tc->val.data.Func)->data.tag == NodeType_TAG_StructDef) {
                            void *saved_ptr = val.data.Ptr;
                            val.tag = Value_TAG_Struct;
                            val.data.Struct.struct_name = etype;
                            val.data.Struct.struct_def = ((Expr*)tc->val.data.Func);
                            val.data.Struct.data = saved_ptr;
                            val.data.Struct.borrowed = stmt->data.data.Decl.is_mut ? 1 : 0;
                        }
                    }
                }
                scope_set_owned(scope, (&stmt->data.data.Decl.name), &val);
            }
            break;
        }
        case NodeType_TAG_Assign: {
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
            Cell *cell = scope_get(scope, &stmt->data.data.Assign);
            if (!cell) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined variable '%s'", stmt->data.data.Assign.c_str);
                Expr_error(stmt, &(Str){.c_str = (U8*)buf, .count = (U64)strlen(buf), .cap = CAP_VIEW});
                exit(1);
            }
            if (stmt->til_type.tag == TilType_TAG_Dynamic && rhs->data.tag == NodeType_TAG_Ident) {
                // Move semantics: transfer value from source, null source
                Cell *src = scope_get(scope, &rhs->data.data.Ident);
                cell->val = src->val;
                if (src->val.tag != Value_TAG_Func)
                    src->val = val_none();
            } else {
                Value new_val = eval_expr(scope,rhs);
                cell->val = new_val;
            }
            break;
        }
        case NodeType_TAG_FieldAssign: {
            Expr *val_expr = Expr_child(stmt, &(USize){(USize)(1)});
            Value val;
            Cell *move_src = NULL;
            if (val_expr->til_type.tag == TilType_TAG_Dynamic && val_expr->data.tag == NodeType_TAG_Ident) {
                move_src = scope_get(scope, &val_expr->data.data.Ident);
                val = move_src->val;
            } else {
                val = eval_expr(scope, val_expr);
            }
            Str *fname = &stmt->data.data.FieldAssign;
            if (interp_fa_is_ns(scope, stmt)) {
                Value obj = eval_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}));
                Str *sname = obj.tag == Value_TAG_Struct
                    ? obj.data.Struct.struct_name : &Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident;
                ns_set(sname, fname, val);
                if (move_src) move_src->val = val_none();
            } else {
                // Resolve to the flat buffer + struct_def where the field lives
                void *base = NULL;
                Expr *cur_sdef = NULL;
                Expr *obj_expr = Expr_child(stmt, &(USize){(USize)(0)});
                if (obj_expr->data.tag == NodeType_TAG_Ident) {
                    Cell *cell = scope_get(scope, &obj_expr->data.data.Ident);
                    if (cell && cell->val.tag == Value_TAG_Struct) {
                        base = cell->val.data.Struct.data;
                        cur_sdef = cell->val.data.Struct.struct_def;
                    }
                } else if (obj_expr->data.tag == NodeType_TAG_FieldAccess) {
                    // Chained: e.g. l1.start.x — walk chain to compute offset
                    Expr *chain[32]; I32 depth = 0;
                    Expr *cur = obj_expr;
                    while (cur->data.tag == NodeType_TAG_FieldAccess) {
                        chain[depth++] = cur;
                        cur = Expr_child(cur, &(USize){(USize)(0)});
                    }
                    Cell *cell = scope_get(scope, &cur->data.data.Ident);
                    if (cell && cell->val.tag == Value_TAG_Struct) {
                        base = cell->val.data.Struct.data;
                        cur_sdef = cell->val.data.Struct.struct_def;
                        for (I32 d = depth - 1; d >= 0; d--) {
                            Expr *fd = find_field_decl(cur_sdef, &chain[d]->data.data.FieldAccess);
                            if (!fd) { base = NULL; break; }
                            if (!DECL_IS_SHALLOW(fd->data.data.Decl)) {
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
                if (DECL_IS_OWN(fdecl->data.data.Decl)) {
                    *(void **)ptr = val.tag == Value_TAG_Struct ? val.data.Struct.data : val.data.Ptr;
                } else if (DECL_IS_REF(fdecl->data.data.Decl)) {
                    if (val.tag == Value_TAG_Ptr) *(void **)ptr = val.data.Ptr;
                    else if (val.tag == Value_TAG_Struct) {
                        *(void **)ptr = val.data.Struct.data;
                    }
                    else *(void **)ptr = NULL;
                } else {
                    switch (val.tag) {
                    case Value_TAG_Int:  *(I64 *)ptr = val.data.Int; break;
                    case Value_TAG_Byte:   *(U8 *)ptr = val.data.Byte; break;
                    case Value_TAG_Short:  *(I16 *)ptr = val.data.Short; break;
                    case Value_TAG_Int32:  *(I32 *)ptr = val.data.Int32; break;
                    case Value_TAG_Uint32:  *(U32 *)ptr = val.data.Uint32; break;
                    case Value_TAG_Uint64:  *(U64 *)ptr = val.data.Uint64; break;
                    case Value_TAG_Boolean: *(Bool *)ptr = val.data.Boolean; break;
                    case Value_TAG_Struct:
                        if (val.data.Struct.borrowed) {
                            Value *cloned = Value_clone(&val);
                            memcpy(ptr, cloned->data.Struct.data, fsz);
                            free(cloned->data.Struct.data);
                            free(cloned);
                        } else {
                            memcpy(ptr, val.data.Struct.data, fsz);
                            free(val.data.Struct.data);
                        }
                        break;
                    case Value_TAG_Enum: {
                        EnumInstance *existing = *(EnumInstance **)ptr;
                        if (existing) { free(existing->data); free(existing); }
                        EnumInstance *ei = malloc(sizeof(EnumInstance));
                        *ei = val.data.Enum;
                        I32 etotal = val.data.Enum.data_size;
                        if (etotal < (I32)sizeof(I64)) etotal = sizeof(I64);
                        ei->data = malloc(etotal);
                        memcpy(ei->data, val.data.Enum.data, etotal);
                        *(EnumInstance **)ptr = ei;
                        break;
                    }
                    case Value_TAG_Ptr: *(void **)ptr = val.data.Ptr; break;
                    case Value_TAG_Func: *(void **)ptr = val.data.Func; break;
                    default: break;
                    }
                }
                if (move_src && move_src->val.tag != Value_TAG_Func) move_src->val = val_none();
            }
            break;
        }
        case NodeType_TAG_FCall:
            eval_call(scope, stmt);
            break;
        case NodeType_TAG_Body: {
            Scope *block_scope = scope_new(scope);
            eval_body(block_scope, stmt);
            if (has_return) {
                Value *_cv = Value_clone(&return_value); return_value = *_cv; free(_cv);
            }
            scope_free(block_scope);
            break;
        }
        case NodeType_TAG_If: {
            Value cond = eval_expr(scope,Expr_child(stmt, &(USize){(USize)(0)}));
            if (cond.data.Boolean) {
                Scope *then_scope = scope_new(scope);
                eval_body(then_scope, Expr_child(stmt, &(USize){(USize)(1)}));
                if (has_return) {
                    Value *_cv = Value_clone(&return_value); return_value = *_cv; free(_cv);
                }
                scope_free(then_scope);
            } else if (stmt->children.count > 2) {
                Scope *else_scope = scope_new(scope);
                eval_body(else_scope, Expr_child(stmt, &(USize){(USize)(2)}));
                if (has_return) {
                    Value *_cv = Value_clone(&return_value); return_value = *_cv; free(_cv);
                }
                scope_free(else_scope);
            }
            break;
        }
        case NodeType_TAG_While: {
            while (1) {
                if (has_return) break;
                Value cond = eval_expr(scope,Expr_child(stmt, &(USize){(USize)(0)}));
                if (!cond.data.Boolean) break;
                Scope *while_scope = scope_new(scope);
                eval_body(while_scope, Expr_child(stmt, &(USize){(USize)(1)}));
                if (has_return) {
                    Value *_cv = Value_clone(&return_value); return_value = *_cv; free(_cv);
                }
                scope_free(while_scope);
                if (has_break) { has_break = 0; break; }
                if (has_continue) { has_continue = 0; }
            }
            break;
        }
        case NodeType_TAG_Break:
            has_break = 1;
            return;
        case NodeType_TAG_Continue:
            has_continue = 1;
            return;
        case NodeType_TAG_Return:
            if (stmt->children.count > 0) {
                return_value = eval_expr(scope,Expr_child(stmt, &(USize){(USize)(0)}));
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

static Bool ns_inited = 0;
void interpreter_init_ns(Scope *global, Expr *program) {
    if (!ns_inited) {
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Value", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Value)}); ns_fields = *_mp; free(_mp); }
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); ns_keys = *_vp; free(_vp); }
        ns_inited = 1;
    }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag == NodeType_TAG_Decl && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef ||
                                        Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_EnumDef)) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *sdef = Expr_child(stmt, &(USize){(USize)(0)});
            // Cache struct defs for C-side construction
            if (sdef->data.tag == NodeType_TAG_StructDef) {
                if ((sname->count == 3 && memcmp(sname->c_str, "Str", 3) == 0))   { cached_str_def = sdef; cached_str_name = sname; }
                if ((sname->count == 5 && memcmp(sname->c_str, "Array", 5) == 0)) { cached_array_def = sdef; cached_array_name = sname; }
                if ((sname->count == 3 && memcmp(sname->c_str, "Vec", 3) == 0))   { cached_vec_def = sdef; cached_vec_name = sname; }
            }
            Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (field->data.data.Decl.is_namespace) {
                    Value fval = eval_expr(global, Expr_child(field, &(USize){(USize)(0)}));
                    // Simple enum variant tags: convert I64 literal to I32 (matching C enum)
                    if (sdef->data.tag == NodeType_TAG_EnumDef && !enum_has_payloads(sdef) &&
                        fval.tag == Value_TAG_Int) {
                        I32 tag = (I32)fval.data.Int;
                        fval = val_i32(tag);
                    }
                    ns_set(sname, (&field->data.data.Decl.name), fval);
                }
            }
        }
    }
}

static Value parse_cli_arg(const char *s, Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0)) return make_str_value((void *)s, strlen(s));
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


static void value_to_buf(void *dest, Value *v, Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0))       { memcpy(dest, &v->data.Int, sizeof(I64)); }
    else if ((type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0))   { memcpy(dest, &v->data.Byte, sizeof(U8)); }
    else if ((type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0))  { memcpy(dest, &v->data.Short, sizeof(I16)); }
    else if ((type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0))  { memcpy(dest, &v->data.Int32, sizeof(I32)); }
    else if ((type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0))  { memcpy(dest, &v->data.Uint32, sizeof(U32)); }
    else if ((type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0)) { memcpy(dest, &v->data.Boolean, sizeof(Bool)); }
    else if (v->tag == Value_TAG_Struct) {
        I32 sz = v->data.Struct.struct_def->data.data.StructDef.total_struct_size;
        if (v->data.Struct.borrowed) {
            Value *cloned = Value_clone(v);
            memcpy(dest, cloned->data.Struct.data, sz);
            free(cloned->data.Struct.data);
            free(cloned);
        } else {
            memcpy(dest, v->data.Struct.data, sz);
            free(v->data.Struct.data);
        }
    }
}

static Value build_argv_array(Vec *argv, U32 offset, U32 count, Str *elem_type) {
    I32 esz = elem_size_for_type(elem_type);
    void *data = calloc(count > 0 ? count : 1, esz);
    for (U32 i = 0; i < count; i++) {
        Str *s = (Str *)Vec_get(argv, &(USize){(USize)(offset + i)});
        Value v = parse_cli_arg((char *)s->c_str, elem_type);
        value_to_buf((char *)data + i * esz, &v, elem_type);
    }
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = cached_array_name;
    inst->struct_def = cached_array_def;
    inst->borrowed = 0;
    inst->data = calloc(1, cached_array_def->data.data.StructDef.total_struct_size);
    // Write fields: data, cap, elem_size, elem_type
    Str fn_data = {.c_str = (U8 *)"data", .count = 4};
    Str fn_cap = {.c_str = (U8 *)"cap", .count = 3};
    Str fn_esz = {.c_str = (U8 *)"elem_size", .count = 9};
    Str fn_et = {.c_str = (U8 *)"elem_type", .count = 9};
    write_field(inst, find_field_decl(cached_array_def, &fn_data), &(Value){.tag = Value_TAG_Ptr, .data.Ptr = data});
    { Value _t = val_u32((U32)count); write_field(inst, find_field_decl(cached_array_def, &fn_cap), &_t); }
    { Value _t = val_u32((U32)esz); write_field(inst, find_field_decl(cached_array_def, &fn_esz), &_t); }
    // Populate FuncPtr fields (#91)
    Str fn_ec = {.c_str = (U8 *)"elem_clone", .count = 10};
    Str fn_ed = {.c_str = (U8 *)"elem_delete", .count = 11};
    Value *clone_fn = ns_get(elem_type, &(Str){.c_str = (U8 *)"clone", .count = 5});
    Value *delete_fn = ns_get(elem_type, &(Str){.c_str = (U8 *)"delete", .count = 6});
    if (clone_fn) write_field(inst, find_field_decl(cached_array_def, &fn_ec), clone_fn);
    if (delete_fn) write_field(inst, find_field_decl(cached_array_def, &fn_ed), delete_fn);
    { Value _t = make_str_value((void *)elem_type->c_str, elem_type->count); write_field(inst, find_field_decl(cached_array_def, &fn_et), &_t); }
    Value result;
    result.tag = Value_TAG_Struct;
    result.data.Struct = *inst;
    free(inst);
    return result;
}

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
                    Value v = parse_cli_arg((char *)arg_s->c_str, &_mpi->ptype);
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
