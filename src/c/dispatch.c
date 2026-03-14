#include "dispatch.h"
#include "ast.h"
#include "ext.h"
#include <stdio.h>

// Forward declarations for value-param scalar functions (not in ext.h
// because bootstrap redefines them with pointer-param signatures)
U8 U8_from_i64(I64 v);
I16 I16_from_i64(I64 v);
I32 I32_from_i64(I64 v);
F32 F32_from_i64(I64 v);
U32 U32_from_i64(I64 v);
U64 U64_from_i64(I64 v);
I64 *I64_new(I64 val);
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <ffi.h>

// Codegen Str layout (matches ext.h Str: {U8 *data, U64 count, U64 cap})
// Distinct from compiler-internal Str (str.h: {char *c_str, U64 count, U64 cap})
typedef struct { U8 *data; U64 count; U64 cap; } ExtStr;

typedef Bool (*DispatchFn)(Scope *, Expr *, Value *);

// --- Dispatch state ---
static Map dispatch_map;
static Bool dispatch_inited;

// --- FFI state ---
typedef struct {
    void *fn;           // dlsym'd function pointer
    Str *return_type;   // NULL for proc (void return)
    I32 nparam;
    bool *param_shallows; // per-param shallow flags (NULL if none)
    bool return_is_shallow; // true for `returns shallow Type`
    ffi_cif cif;
    ffi_type **arg_types;
} FFIEntry;

static Map ffi_map;          // name -> FFIEntry
static Map ffi_struct_defs;  // Str* name -> Expr* struct_def (for return type lookup)
static void *ffi_handle;     // dlopen handle
static Bool ffi_loaded;

// Cache for heap-allocated ffi_type structs (freed in ffi_cleanup)
static Vec ffi_type_cache; // Vec of ffi_type*
static Bool ffi_type_cache_inited;

// Forward declaration
static ffi_type *build_struct_ffi_type(Expr *struct_def);

// Map a til type name to the appropriate ffi_type for shallow params
static ffi_type *shallow_ffi_type(Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0))  return &ffi_type_sint64;
    if ((type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0))   return &ffi_type_uint8;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0))  return &ffi_type_sint16;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0))  return &ffi_type_sint32;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0))  return &ffi_type_uint32;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "U64", 3) == 0))  return &ffi_type_uint64;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "F32", 3) == 0))  return &ffi_type_float;
    if ((type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0)) return &ffi_type_uint8;
    // Struct type: look up def and build ffi_type
    if (*Map_has(&ffi_struct_defs, type_name)) {
        Expr **sdef = Map_get(&ffi_struct_defs, type_name);
        return build_struct_ffi_type(*sdef);
    }
    return &ffi_type_pointer; // fallback
}

// Map a field to its ffi_type (for building struct ffi_types)
static ffi_type *field_ffi_type(Expr *field) {
    if (field->data.data.Decl.is_own || field->data.data.Decl.is_ref)
        return &ffi_type_pointer;
    Str *ftype = &field->data.data.Decl.explicit_type;
    if (ftype->count == 0) return &ffi_type_sint64; // fallback (I64-sized)
    if ((ftype->count == 3 && memcmp(ftype->c_str, "I64", 3) == 0))  return &ffi_type_sint64;
    if ((ftype->count == 2 && memcmp(ftype->c_str, "U8", 2) == 0))   return &ffi_type_uint8;
    if ((ftype->count == 3 && memcmp(ftype->c_str, "I16", 3) == 0))  return &ffi_type_sint16;
    if ((ftype->count == 3 && memcmp(ftype->c_str, "I32", 3) == 0))  return &ffi_type_sint32;
    if ((ftype->count == 3 && memcmp(ftype->c_str, "U32", 3) == 0))  return &ffi_type_uint32;
    if ((ftype->count == 3 && memcmp(ftype->c_str, "U64", 3) == 0))  return &ffi_type_uint64;
    if ((ftype->count == 3 && memcmp(ftype->c_str, "F32", 3) == 0))  return &ffi_type_float;
    if ((ftype->count == 4 && memcmp(ftype->c_str, "Bool", 4) == 0)) return &ffi_type_uint8;
    // Inline struct field
    if (field->data.data.Decl.field_struct_def)
        return build_struct_ffi_type(field->data.data.Decl.field_struct_def);
    return &ffi_type_sint64; // fallback
}

// Build an ffi_type descriptor for a struct (heap-allocated, cached)
static ffi_type *build_struct_ffi_type(Expr *struct_def) {
    if (!ffi_type_cache_inited) {
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(ffi_type *)}); ffi_type_cache = *_vp; free(_vp); }
        ffi_type_cache_inited = 1;
    }
    // Count instance fields
    Expr *body = Expr_child(struct_def, &(I64){(I64)(0)});
    U32 nfields = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(I64){(I64)(i)});
        if (f->data.tag == ExprData_TAG_Decl && !f->data.data.Decl.is_namespace) nfields++;
    }
    // Build elements array (NULL-terminated)
    ffi_type **elements = malloc(sizeof(ffi_type *) * (nfields + 1));
    U32 idx = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(I64){(I64)(i)});
        if (f->data.tag == ExprData_TAG_Decl && !f->data.data.Decl.is_namespace)
            elements[idx++] = field_ffi_type(f);
    }
    elements[nfields] = NULL;
    // Build the ffi_type
    ffi_type *st = malloc(sizeof(ffi_type));
    st->size = 0;
    st->alignment = 0;
    st->type = FFI_TYPE_STRUCT;
    st->elements = elements;
    // Cache for cleanup
    { ffi_type **_p = malloc(sizeof(ffi_type *)); *_p = st; Vec_push(&ffi_type_cache, _p); }
    return st;
}

// === Eval helper for Dynamic narrowing ===
// When the typer narrows a Dynamic arg to a concrete type, the expression's
// til_type is the target. If the runtime value is VAL_PTR (from ptr_add/malloc),
// reinterpret it as the narrowed type so dispatch handlers see the right union field.
static Value eval_arg(Scope *s, Expr *e) {
    Value v = eval_expr(s, e);
    if (v.type == VAL_PTR && e->til_type.tag != TilType_TAG_Dynamic) {
        switch (e->til_type.tag) {
            case TilType_TAG_I64:    return (Value){.type = VAL_I64, .i64 = (I64 *)v.ptr};
            case TilType_TAG_U8:    return (Value){.type = VAL_U8, .u8 = (U8 *)v.ptr};
            case TilType_TAG_I16:   return (Value){.type = VAL_I16, .i16 = (I16 *)v.ptr};
            case TilType_TAG_I32:   return (Value){.type = VAL_I32, .i32 = (I32 *)v.ptr};
            case TilType_TAG_U32:   return (Value){.type = VAL_U32, .u32 = (U32 *)v.ptr};
            case TilType_TAG_U64:   return (Value){.type = VAL_U64, .u64 = (U64 *)v.ptr};
            case TilType_TAG_F32:   return (Value){.type = VAL_F32, .f32 = (F32 *)v.ptr};
            case TilType_TAG_Bool:  return (Value){.type = VAL_BOOL, .boolean = (Bool *)v.ptr};
            case TilType_TAG_Struct:
                if ((e->struct_name).count > 0 && (e->struct_name.count == 3 && memcmp(e->struct_name.c_str, "Str", 3) == 0)) {
                    ExtStr *sp = (ExtStr *)v.ptr;
                    return make_str_value_own((char *)sp->data, sp->count);
                }
                return (Value){.type = VAL_STRUCT, .instance = v.ptr};
            default: break;
        }
    }
    return v;
}

// === Handler macros ===

// === Remaining handlers (name mismatch or local ext_func — can't use auto-FFI) ===

static Bool h_Bool_and(Scope *s, Expr *e, Value *r) {
    Value a = eval_arg(s, Expr_child(e, &(I64){(I64)(1)}));
    Value b = eval_arg(s, Expr_child(e, &(I64){(I64)(2)}));
    *r = val_bool(Bool_and(*a.boolean, *b.boolean)); return 1;
}
static Bool h_Bool_or(Scope *s, Expr *e, Value *r) {
    Value a = eval_arg(s, Expr_child(e, &(I64){(I64)(1)}));
    Value b = eval_arg(s, Expr_child(e, &(I64){(I64)(2)}));
    *r = val_bool(Bool_or(*a.boolean, *b.boolean)); return 1;
}
static Bool h_Bool_not(Scope *s, Expr *e, Value *r) {
    Value v = eval_arg(s, Expr_child(e, &(I64){(I64)(1)}));
    *r = val_bool(Bool_not(*v.boolean)); return 1;
}

static Bool h_U8_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    *r = val_u8(U8_from_i64(*v.i64)); return 1;
}
static Bool h_I16_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    *r = val_i16(I16_from_i64(*v.i64)); return 1;
}
static Bool h_I32_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    *r = val_i32(I32_from_i64(*v.i64)); return 1;
}
static Bool h_F32_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    *r = val_f32(F32_from_i64(*v.i64)); return 1;
}
static Bool h_U32_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    *r = val_u32(U32_from_i64(*v.i64)); return 1;
}

static void *val_to_ptr(Value v);

// === Print handlers ===

static Bool h_print_single(Scope *s, Expr *e, Value *r) {
    Value arg = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str sv = str_view(arg);
    fwrite(sv.c_str, 1, sv.count, stdout);
    *r = val_none(); return 1;
}

static Bool h_print_flush(Scope *s, Expr *e, Value *r) {
    (void)s; (void)e;
    putchar('\n');
    *r = val_none(); return 1;
}

// === Misc handlers ===

static Bool h_exit(Scope *s, Expr *e, Value *r) {
    Value a = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    exit((int)*a.i64);
    *r = val_none(); return 1;
}

static Bool h_free(Scope *s, Expr *e, Value *r) {
    if (Expr_child(e, &(I64){(I64)(1)})->data.tag != ExprData_TAG_Ident) {
        Value val = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
        void *ptr = val_to_ptr(val);
        if (ptr) free(ptr);
        *r = val_none();
        return 1;
    }
    Cell *cell = scope_get(s, &Expr_child(e, &(I64){(I64)(1)})->data.data.Ident);
    if (cell->val.type == VAL_STRUCT && cell->val.instance) {
        if (!cell->val.instance->borrowed)
            free(cell->val.instance->data);
        free(cell->val.instance);
    } else if (cell->val.type == VAL_ENUM && cell->val.enum_inst) {
        Value payload = cell->val.enum_inst->payload;
        if (payload.type == VAL_I64)  free(payload.i64);
        else if (payload.type == VAL_U8)   free(payload.u8);
        else if (payload.type == VAL_I16)  free(payload.i16);
        else if (payload.type == VAL_I32)  free(payload.i32);
        else if (payload.type == VAL_U32)  free(payload.u32);
        else if (payload.type == VAL_F32)  free(payload.f32);
        else if (payload.type == VAL_BOOL) free(payload.boolean);
        free(cell->val.enum_inst);
    } else if (cell->val.type == VAL_I64) {
        free(cell->val.i64);
    } else if (cell->val.type == VAL_U8) {
        free(cell->val.u8);
    } else if (cell->val.type == VAL_I16) {
        free(cell->val.i16);
    } else if (cell->val.type == VAL_I32) {
        free(cell->val.i32);
    } else if (cell->val.type == VAL_U32) {
        free(cell->val.u32);
    } else if (cell->val.type == VAL_F32) {
        free(cell->val.f32);
    } else if (cell->val.type == VAL_BOOL) {
        free(cell->val.boolean);
    } else if (cell->val.type == VAL_PTR) {
        free(cell->val.ptr);
    }
    cell->val = val_none();
    *r = val_none();
    return 1;
}

// === Dynamic dispatch handler ===

// Shared helper for all dyn_call variants
static Bool h_dyn_call(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    Value method_val = eval_expr(s, Expr_child(e, &(I64){(I64)(2)}));
    Str _mn = str_view(method_val);
    Str *method = &_mn;

    Expr type_ident = {0};
    type_ident.data.tag = ExprData_TAG_Ident;
    type_ident.data.data.Ident = *type_name;
    type_ident.struct_name = *type_name;
    type_ident.line = e->line;
    type_ident.col = e->col;

    Expr field_access = {0};
    field_access.data.tag = ExprData_TAG_FieldAccess;
    field_access.data.data.FieldAccess = *method;
    field_access.is_ns_field = 1;
    field_access.line = e->line;
    field_access.col = e->col;
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); field_access.children = *_vp; free(_vp); }
    Expr *ti_ptr = &type_ident;
    { Expr **_p = malloc(sizeof(Expr *)); *_p = ti_ptr; Vec_push(&field_access.children, _p); }

    Expr fake_call = {0};
    fake_call.data.tag = ExprData_TAG_FCall;
    fake_call.line = e->line;
    fake_call.col = e->col;
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); fake_call.children = *_vp; free(_vp); }
    Expr *fa_ptr = &field_access;
    { Expr **_p = malloc(sizeof(Expr *)); *_p = fa_ptr; Vec_push(&fake_call.children, _p); }
    // Skip child 3 (arity literal), actual args start at child 4
    for (U32 i = 4; i < e->children.count; i++) {
        Expr *arg = Expr_child(e, &(I64){(I64)(i)});
        { Expr **_p = malloc(sizeof(Expr *)); *_p = arg; Vec_push(&fake_call.children, _p); }
    }

    Value fn_val = eval_expr(s, &field_access);
    if (fn_val.type == VAL_FUNC && fn_val.func->data.tag == ExprData_TAG_FuncDef) {
        Expr *fdef = fn_val.func;
        U32 nparam = fdef->data.data.FuncDef.nparam;
        U32 nargs = fake_call.children.count - 1;
        for (U32 i = nargs; i < nparam; i++) {
            if (VEC_SET(fdef->data.data.FuncDef.param_defaults) &&
                (*(Expr**)Vec_get(&fdef->data.data.FuncDef.param_defaults, &(U64){(U64)(i)}))) {
                Expr *def_arg = (*(Expr**)Vec_get(&fdef->data.data.FuncDef.param_defaults, &(U64){(U64)(i)}));
                { Expr **_p = malloc(sizeof(Expr *)); *_p = def_arg; Vec_push(&fake_call.children, _p); }
            }
        }
    }

    *r = eval_call(s, &fake_call);

    Vec_delete(&fake_call.children, &(Bool){0});
    Vec_delete(&field_access.children, &(Bool){0});
    return 1;
}

// dyn_has_method(type_name, "method") → Bool
static Bool h_dyn_has_method(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Value method_val = eval_expr(s, Expr_child(e, &(I64){(I64)(2)}));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    Str _mn = str_view(method_val);
    Str *method = &_mn;
    Value *nsv = ns_get(type_name, method);
    *r = val_bool(nsv != NULL);
    return 1;
}

// === Collection builtin handlers ===

// Get raw pointer from a Value (for memcpy into Array/Vec data buffer)
static void *val_raw_ptr(Value v) {
    switch (v.type) {
        case VAL_I64:    return v.i64;
        case VAL_U8:     return v.u8;
        case VAL_I16:    return v.i16;
        case VAL_I32:    return v.i32;
        case VAL_U32:    return v.u32;
        case VAL_F32:    return v.f32;
        case VAL_BOOL:   return v.boolean;
        case VAL_STRUCT: return v.instance->data;
        case VAL_PTR:    return v.ptr;
        default:         return NULL;
    }
}

// Get element size via dyn_call to Type.size()
// Workaround: the scavenger may remove Type.size() if not directly referenced
// in user code (see issue #15). Users must reference Type.size() explicitly.
static I32 get_elem_size(Scope *s, Str *type_name, Expr *src) {
    Value *size_fn = ns_get(type_name, &(Str){.c_str = (U8*)"size", .count = 4, .cap = CAP_LIT});
    if (!size_fn) {
        fprintf(stderr, "%s:%u:%u: error: array/vec: type '%s' has no size() method "
                "(hint: add %s.size() somewhere to prevent scavenger removal, see #15)\n",
                src->path.c_str, src->line, src->col, type_name->c_str, type_name->c_str);
        exit(1);
    }
    // Build fake call: Type.size()
    Expr type_ident = {0};
    type_ident.data.tag = ExprData_TAG_Ident;
    type_ident.data.data.Ident = *type_name;
    type_ident.struct_name = *type_name;
    type_ident.line = src->line; type_ident.col = src->col;
    type_ident.path = src->path;

    Expr field_access = {0};
    field_access.data.tag = ExprData_TAG_FieldAccess;
    field_access.data.data.FieldAccess = (Str){.c_str = (U8*)"size", .count = 4, .cap = CAP_LIT};
    field_access.is_ns_field = 1;
    field_access.line = src->line; field_access.col = src->col;
    field_access.path = src->path;
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); field_access.children = *_vp; free(_vp); }
    Expr *ti = &type_ident;
    { Expr **_p = malloc(sizeof(Expr *)); *_p = ti; Vec_push(&field_access.children, _p); }

    Expr fake_call = {0};
    fake_call.data.tag = ExprData_TAG_FCall;
    fake_call.line = src->line; fake_call.col = src->col;
    fake_call.path = src->path;
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); fake_call.children = *_vp; free(_vp); }
    Expr *fa = &field_access;
    { Expr **_p = malloc(sizeof(Expr *)); *_p = fa; Vec_push(&fake_call.children, _p); }

    Value result = eval_call(s, &fake_call);
    Vec_delete(&fake_call.children, &(Bool){0});
    Vec_delete(&field_access.children, &(Bool){0});
    return (I32)*result.u64;
}

// array("I64", 1, 2, 3)
static Bool h_array(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    U32 count = e->children.count - 2;
    I32 elem_size = get_elem_size(s, type_name, e);

    // Allocate array data
    void *data = malloc(count * elem_size);
    memset(data, 0, count * elem_size);

    // Evaluate each element and copy into data buffer
    for (U32 i = 0; i < count; i++) {
        Value elem = eval_expr(s, Expr_child(e, &(I64){(I64)(i + 2)}));
        void *src = val_raw_ptr(elem);
        if (src) {
            if (elem.type == VAL_STRUCT && (elem.instance->struct_name->count == 3 && memcmp(elem.instance->struct_name->c_str, "Str", 3) == 0)) {
                // Deep-copy Str: copy flat bytes then strndup the data pointer
                memcpy((char *)data + i * elem_size, src, elem_size);
                char **dp = (char **)((char *)data + i * elem_size);
                U64 slen = *(U64 *)((char *)data + i * elem_size + 8);
                *dp = strndup(*dp, slen);
            } else {
                memcpy((char *)data + i * elem_size, src, elem_size);
            }
        }
    }

    // Build Array struct: {data, cap, elem_size, elem_type}
    StructInstance *si = malloc(sizeof(StructInstance));
    si->struct_name = cached_array_name;
    si->struct_def = cached_array_def;
    si->borrowed = 0;
    si->data = calloc(1, cached_array_def->total_struct_size);
    Str fn_data = {.c_str = (U8 *)"data", .count = 4};
    Str fn_cap = {.c_str = (U8 *)"cap", .count = 3};
    Str fn_esz = {.c_str = (U8 *)"elem_size", .count = 9};
    Str fn_et = {.c_str = (U8 *)"elem_type", .count = 9};
    write_field(si, find_field_decl(cached_array_def, &fn_data), (Value){.type = VAL_PTR, .ptr = data});
    write_field(si, find_field_decl(cached_array_def, &fn_cap), val_u64(count));
    write_field(si, find_field_decl(cached_array_def, &fn_esz), val_u64(elem_size));
    write_field(si, find_field_decl(cached_array_def, &fn_et), make_str_value((const char *)type_name->c_str, type_name->count));

    r->type = VAL_STRUCT;
    r->instance = si;
    return 1;
}

// vec("I64", 1, 2, 3)
static Bool h_vec(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    U32 count = e->children.count - 2;
    I32 elem_size = get_elem_size(s, type_name, e);

    // Allocate vec data with exact capacity
    U32 cap = count > 0 ? count : 1;
    void *data = malloc(cap * elem_size);
    memset(data, 0, cap * elem_size);

    // Evaluate each element and copy into data buffer
    for (U32 i = 0; i < count; i++) {
        Value elem = eval_expr(s, Expr_child(e, &(I64){(I64)(i + 2)}));
        void *src = val_raw_ptr(elem);
        if (src) {
            if (elem.type == VAL_STRUCT && (elem.instance->struct_name->count == 3 && memcmp(elem.instance->struct_name->c_str, "Str", 3) == 0)) {
                memcpy((char *)data + i * elem_size, src, elem_size);
                char **dp = (char **)((char *)data + i * elem_size);
                U64 slen = *(U64 *)((char *)data + i * elem_size + 8);
                *dp = strndup(*dp, slen);
            } else {
                memcpy((char *)data + i * elem_size, src, elem_size);
            }
        }
    }

    // Build Vec struct: {data, count, cap, elem_size, elem_type}
    StructInstance *si = malloc(sizeof(StructInstance));
    si->struct_name = cached_vec_name;
    si->struct_def = cached_vec_def;
    si->borrowed = 0;
    si->data = calloc(1, cached_vec_def->total_struct_size);
    Str fn_data = {.c_str = (U8 *)"data", .count = 4};
    Str fn_count = {.c_str = (U8 *)"count", .count = 5};
    Str fn_cap = {.c_str = (U8 *)"cap", .count = 3};
    Str fn_esz = {.c_str = (U8 *)"elem_size", .count = 9};
    Str fn_et = {.c_str = (U8 *)"elem_type", .count = 9};
    write_field(si, find_field_decl(cached_vec_def, &fn_data), (Value){.type = VAL_PTR, .ptr = data});
    write_field(si, find_field_decl(cached_vec_def, &fn_count), val_u64(count));
    write_field(si, find_field_decl(cached_vec_def, &fn_cap), val_u64(cap));
    write_field(si, find_field_decl(cached_vec_def, &fn_esz), val_u64(elem_size));
    write_field(si, find_field_decl(cached_vec_def, &fn_et), make_str_value((const char *)type_name->c_str, type_name->count));

    r->type = VAL_STRUCT;
    r->instance = si;
    return 1;
}

// === Pointer primitive handlers ===

// Extract raw void* from any Value type
static void *val_to_ptr(Value v) {
    switch (v.type) {
        case VAL_PTR:    return v.ptr;
        case VAL_I64:    return v.i64;
        case VAL_U8:     return v.u8;
        case VAL_I16:    return v.i16;
        case VAL_I32:    return v.i32;
        case VAL_U32:    return v.u32;
        case VAL_F32:    return v.f32;
        case VAL_BOOL:   return v.boolean;
        case VAL_STRUCT: return v.instance->data;
        default:         return NULL;
    }
}


static Bool h_ptr_add(Scope *s, Expr *e, Value *r) {
    Value buf = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Value offset = eval_expr(s, Expr_child(e, &(I64){(I64)(2)}));
    *r = (Value){.type = VAL_PTR, .ptr = (char *)buf.ptr + *offset.u64};
    return 1;
}


// === System primitive handlers ===

static Bool h_readfile(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str sv = str_view(path);
    char *p = strndup((const char *)sv.c_str, sv.count);
    FILE *f = fopen(p, "rb");
    if (!f) {
        fprintf(stderr, "readfile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len);
    fread(buf, 1, len, f);
    fclose(f);
    *r = make_str_value_own(buf, (U64)len);
    return 1;
}

static Bool h_writefile(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Value content = eval_expr(s, Expr_child(e, &(I64){(I64)(2)}));
    Str pv = str_view(path);
    Str cv = str_view(content);
    char *p = strndup((const char *)pv.c_str, pv.count);
    FILE *f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "writefile: could not open '%s'\n", p);
        free(p);
        exit(1);
    }
    free(p);
    fwrite(cv.c_str, 1, cv.count, f);
    fclose(f);
    *r = val_none();
    return 1;
}

static Bool h_spawn_cmd(Scope *s, Expr *e, Value *r) {
    Value cmd = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str sv = str_view(cmd);
    char *c = strndup((const char *)sv.c_str, sv.count);
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", c, NULL);
        _exit(127);
    }
    free(c);
    if (pid < 0) {
        fprintf(stderr, "spawn_cmd: fork failed\n");
        exit(1);
    }
    *r = val_i64((I64)pid);
    return 1;
}

static Bool h_check_cmd_status(Scope *s, Expr *e, Value *r) {
    Value pidv = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    int status;
    pid_t result = waitpid((pid_t)*pidv.i64, &status, WNOHANG);
    if (result == 0) { *r = val_i64(-1); return 1; }
    if (WIFEXITED(status)) { *r = val_i64(WEXITSTATUS(status)); return 1; }
    *r = val_i64(-1);
    return 1;
}

static Bool h_sleep(Scope *s, Expr *e, Value *r) {
    Value ms = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    usleep((useconds_t)(*ms.i64 * 1000));
    *r = val_none();
    return 1;
}

static Bool h_file_mtime(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, Expr_child(e, &(I64){(I64)(1)}));
    Str sv = str_view(path);
    char *p = strndup((const char *)sv.c_str, sv.count);
    struct stat st;
    int rc = stat(p, &st);
    free(p);
    if (rc != 0) { *r = val_i64(-1); return 1; }
    *r = val_i64((I64)st.st_mtime);
    return 1;
}

static Bool h_clock_ms(Scope *s, Expr *e, Value *r) {
    (void)s; (void)e;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    *r = val_i64((I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000);
    return 1;
}

static Bool h_get_thread_count(Scope *s, Expr *e, Value *r) {
    (void)s; (void)e;
    long count = sysconf(_SC_NPROCESSORS_ONLN);
    *r = val_i64(count > 0 ? (I64)count : 1);
    return 1;
}

// === Dispatch init ===

static void dispatch_init(void) {
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(DispatchFn)}); dispatch_map = *_mp; free(_mp); }

    #define REG(n, fn) do { Str *k = Str_clone(&(Str){.c_str = (U8*)(n), .count = (U64)strlen((const char*)(n)), .cap = CAP_VIEW}); DispatchFn f = fn; \
        Str *_k = malloc(sizeof(Str)); *_k = (Str){k->c_str, k->count, CAP_VIEW}; \
        DispatchFn *_v = malloc(sizeof(DispatchFn)); *_v = f; \
        Map_set(&dispatch_map, _k, _v); } while(0)

    // Print
    REG("print_single", h_print_single);
    REG("print_flush", h_print_flush);

    // Bool standalone (name mismatch: "and" → Bool_and in C)
    REG("and", h_Bool_and); REG("or", h_Bool_or);
    REG("not", h_Bool_not);

    // from_i64 (local ext_func inside func body — not scanned by ffi_init)
    REG("U8_from_i64", h_U8_from_i64);
    REG("U8_from_i64_ext", h_U8_from_i64);
    REG("I16_from_i64", h_I16_from_i64);
    REG("I16_from_i64_ext", h_I16_from_i64);
    REG("I32_from_i64", h_I32_from_i64);
    REG("I32_from_i64_ext", h_I32_from_i64);
    REG("F32_from_i64", h_F32_from_i64);
    REG("F32_from_i64_ext", h_F32_from_i64);
    REG("U32_from_i64", h_U32_from_i64);
    REG("U32_from_i64_ext", h_U32_from_i64);

    // Misc
    REG("exit", h_exit);
    REG("free", h_free);

    // Pointer primitives
    REG("ptr_add", h_ptr_add);

    // Collection builtins
    REG("array", h_array);
    REG("vec", h_vec);

    // Dynamic dispatch
    REG("dyn_call", h_dyn_call);
    REG("dyn_call_ret", h_dyn_call);
    REG("dyn_has_method", h_dyn_has_method);

    // System primitives
    REG("readfile", h_readfile);
    REG("writefile", h_writefile);
    REG("spawn_cmd", h_spawn_cmd);
    REG("check_cmd_status", h_check_cmd_status);
    REG("sleep", h_sleep);
    REG("file_mtime", h_file_mtime);
    REG("clock_ms", h_clock_ms);
    REG("get_thread_count", h_get_thread_count);

    #undef REG
    dispatch_inited = 1;
}

// === Main dispatch ===

Bool ext_function_dispatch(Str *name, Scope *scope, Expr *e, Value *result) {
    if (!dispatch_inited) dispatch_init();

    if (*Map_has(&dispatch_map, name)) {
        DispatchFn *fn = Map_get(&dispatch_map, name);
        return (*fn)(scope, e, result);
    }

    // FFI dispatch via libffi
    if (ffi_loaded) {
        if (*Map_has(&ffi_map, name)) {
            FFIEntry *fe = Map_get(&ffi_map, name);
            U32 nargs = e->children.count - 1;
            void *args[nargs > 0 ? nargs : 1];
            void *arg_ptrs[nargs > 0 ? nargs : 1];
            for (U32 i = 0; i < nargs; i++) {
                Value v = eval_expr(scope, Expr_child(e, &(I64){(I64)(i + 1)}));
                if (fe->param_shallows && i < (U32)fe->nparam && fe->param_shallows[i]) {
                    // Shallow: store dereferenced value directly for ffi
                    if (v.type == VAL_STRUCT) {
                        // Struct by value: point arg_ptrs directly at struct data
                        arg_ptrs[i] = v.instance->data;
                        continue;
                    }
                    // Check for NULL before shallow dereference
                    void *shallow_ptr = NULL;
                    switch (v.type) {
                        case VAL_I64:  shallow_ptr = v.i64; break;
                        case VAL_U8:   shallow_ptr = v.u8; break;
                        case VAL_I16:  shallow_ptr = v.i16; break;
                        case VAL_I32:  shallow_ptr = v.i32; break;
                        case VAL_U32:  shallow_ptr = v.u32; break;
                        case VAL_U64:  shallow_ptr = v.u64; break;
                        case VAL_F32:  shallow_ptr = v.f32; break;
                        case VAL_BOOL: shallow_ptr = v.boolean; break;
                        case VAL_PTR:  shallow_ptr = v.ptr; break;
                        default:       shallow_ptr = v.ptr; break;
                    }
                    if (!shallow_ptr) {
                        fprintf(stderr, "panic: null deref\n");
                        exit(1);
                    }
                    switch (v.type) {
                        case VAL_I64:  *(I64 *)&args[i] = *v.i64; break;
                        case VAL_U8:   *(U8 *)&args[i] = *v.u8; break;
                        case VAL_I16:  *(I16 *)&args[i] = *v.i16; break;
                        case VAL_I32:  *(I32 *)&args[i] = *v.i32; break;
                        case VAL_U32:  *(U32 *)&args[i] = *v.u32; break;
                        case VAL_U64:  *(U64 *)&args[i] = *v.u64; break;
                        case VAL_F32:  *(F32 *)&args[i] = *v.f32; break;
                        case VAL_BOOL: *(U8 *)&args[i] = *v.boolean ? 1 : 0; break;
                        case VAL_PTR:
                            // Dynamic/ptr arg to shallow param: dereference as expected type
                            if (fe->arg_types[i] == &ffi_type_sint64)
                                *(I64 *)&args[i] = *(I64 *)v.ptr;
                            else if (fe->arg_types[i] == &ffi_type_uint8)
                                *(U8 *)&args[i] = *(U8 *)v.ptr;
                            else if (fe->arg_types[i] == &ffi_type_sint16)
                                *(I16 *)&args[i] = *(I16 *)v.ptr;
                            else if (fe->arg_types[i] == &ffi_type_sint32)
                                *(I32 *)&args[i] = *(I32 *)v.ptr;
                            else if (fe->arg_types[i] == &ffi_type_uint32)
                                *(U32 *)&args[i] = *(U32 *)v.ptr;
                            else if (fe->arg_types[i] == &ffi_type_uint64)
                                *(U64 *)&args[i] = *(U64 *)v.ptr;
                            else if (fe->arg_types[i] == &ffi_type_float)
                                *(F32 *)&args[i] = *(F32 *)v.ptr;
                            else
                                args[i] = v.ptr;
                            break;
                        default:       args[i] = v.ptr; break;
                    }
                } else {
                    // Deep: pass pointer (existing behavior)
                    switch (v.type) {
                        case VAL_I64:    args[i] = v.i64; break;
                        case VAL_U8:     args[i] = v.u8; break;
                        case VAL_I16:    args[i] = v.i16; break;
                        case VAL_I32:    args[i] = v.i32; break;
                        case VAL_U32:    args[i] = v.u32; break;
                        case VAL_U64:    args[i] = v.u64; break;
                        case VAL_F32:    args[i] = v.f32; break;
                        case VAL_BOOL:   args[i] = v.boolean; break;
                        case VAL_PTR:    args[i] = v.ptr; break;
                        case VAL_STRUCT: args[i] = v.instance->data; break;
                        default:         args[i] = NULL; break;
                    }
                }
                arg_ptrs[i] = &args[i];
            }
            // Check if return is a shallow struct (needs larger buffer)
            // Only treat as struct if the CIF return type is FFI_TYPE_STRUCT —
            // scalar types like Bool are ext_structs in til but scalars in FFI.
            Expr **ret_sdef = NULL;
            if (fe->return_is_shallow && fe->return_type &&
                fe->cif.rtype->type == FFI_TYPE_STRUCT &&
                *Map_has(&ffi_struct_defs, fe->return_type))
                ret_sdef = Map_get(&ffi_struct_defs, fe->return_type);
            void *raw = NULL;
            void *ret_buf = NULL;
            if (ret_sdef) {
                // Struct return: allocate buffer of struct size
                ret_buf = malloc((*ret_sdef)->total_struct_size);
                ffi_call(&fe->cif, FFI_FN(fe->fn), ret_buf, nargs > 0 ? arg_ptrs : NULL);
            } else {
                ffi_call(&fe->cif, FFI_FN(fe->fn), &raw, nargs > 0 ? arg_ptrs : NULL);
            }
            if (!fe->return_type) {
                *result = val_none();
            } else if (ret_sdef) {
                // Shallow struct return: wrap buffer in StructInstance
                StructInstance *inst = malloc(sizeof(StructInstance));
                inst->struct_name = fe->return_type;
                inst->struct_def = *ret_sdef;
                inst->data = ret_buf;
                inst->borrowed = 0;
                *result = (Value){.type = VAL_STRUCT, .instance = inst};
            } else if (fe->return_is_shallow) {
                // Shallow return: C function returned a primitive by value.
                // 'raw' contains the value in its low bits — box it.
                if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I64", 3) == 0)) {
                    *result = (Value){.type = VAL_I64, .i64 = I64_new((I64)(intptr_t)raw)};
                } else if ((fe->return_type->count == 2 && memcmp(fe->return_type->c_str, "U8", 2) == 0)) {
                    U8 *p = malloc(sizeof(U8)); *p = (U8)(intptr_t)raw;
                    *result = (Value){.type = VAL_U8, .u8 = p};
                } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I16", 3) == 0)) {
                    I16 *p = malloc(sizeof(I16)); *p = (I16)(intptr_t)raw;
                    *result = (Value){.type = VAL_I16, .i16 = p};
                } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I32", 3) == 0)) {
                    I32 *p = malloc(sizeof(I32)); *p = (I32)(intptr_t)raw;
                    *result = (Value){.type = VAL_I32, .i32 = p};
                } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U32", 3) == 0)) {
                    U32 *p = malloc(sizeof(U32)); *p = (U32)(intptr_t)raw;
                    *result = (Value){.type = VAL_U32, .u32 = p};
                } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U64", 3) == 0)) {
                    U64 *p = malloc(sizeof(U64)); *p = (U64)(intptr_t)raw;
                    *result = (Value){.type = VAL_U64, .u64 = p};
                } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "F32", 3) == 0)) {
                    F32 *p = malloc(sizeof(F32)); *p = *(F32 *)&raw;
                    *result = (Value){.type = VAL_F32, .f32 = p};
                } else if ((fe->return_type->count == 4 && memcmp(fe->return_type->c_str, "Bool", 4) == 0)) {
                    Bool *p = malloc(sizeof(Bool)); *p = (Bool)(intptr_t)raw;
                    *result = (Value){.type = VAL_BOOL, .boolean = p};
                } else {
                    *result = val_none();
                }
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "Str", 3) == 0)) {
                ExtStr *sp = (ExtStr *)raw;
                *result = make_str_value_own((char *)sp->data, sp->count);
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I64", 3) == 0)) {
                *result = (Value){.type = VAL_I64, .i64 = (I64 *)raw};
            } else if ((fe->return_type->count == 2 && memcmp(fe->return_type->c_str, "U8", 2) == 0)) {
                *result = (Value){.type = VAL_U8, .u8 = (U8 *)raw};
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I16", 3) == 0)) {
                *result = (Value){.type = VAL_I16, .i16 = (I16 *)raw};
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I32", 3) == 0)) {
                *result = (Value){.type = VAL_I32, .i32 = (I32 *)raw};
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U32", 3) == 0)) {
                *result = (Value){.type = VAL_U32, .u32 = (U32 *)raw};
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U64", 3) == 0)) {
                *result = (Value){.type = VAL_U64, .u64 = (U64 *)raw};
            } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "F32", 3) == 0)) {
                *result = (Value){.type = VAL_F32, .f32 = (F32 *)raw};
            } else if ((fe->return_type->count == 4 && memcmp(fe->return_type->c_str, "Bool", 4) == 0)) {
                *result = (Value){.type = VAL_BOOL, .boolean = (Bool *)raw};
            } else if ((fe->return_type->count == 7 && memcmp(fe->return_type->c_str, "Dynamic", 7) == 0)) {
                *result = (Value){.type = VAL_PTR, .ptr = raw};
            } else {
                // Struct return — look up struct def by return type name
                if (*Map_has(&ffi_struct_defs, fe->return_type)) {
                    Expr **sdef = Map_get(&ffi_struct_defs, fe->return_type);
                    StructInstance *inst = malloc(sizeof(StructInstance));
                    inst->struct_name = fe->return_type;
                    inst->struct_def = *sdef;
                    inst->borrowed = 0;
                    inst->data = raw;
                    *result = (Value){.type = VAL_STRUCT, .instance = inst};
                } else {
                    *result = val_none();
                }
            }
            return 1;
        }
    }

    return 0;
}

Bool enum_method_dispatch(Str *method, Scope *scope, Expr *enum_def,
                         Str *enum_name, Expr *e,
                         Value *result) {
    Bool hp = *enum_has_payloads(enum_def);

    if (hp) {
        // Payload enum: constructor, get_Variant
        I32 ctor_tag = *enum_variant_tag(enum_def, method);
        if (ctor_tag >= 0) {
            if (enum_variant_type(enum_def, ctor_tag)->count > 0) {
                Value payload = eval_expr(scope, Expr_child(e, &(I64){(I64)(1)}));
                *result = val_enum(enum_name, ctor_tag, clone_value(payload));
            } else {
                *result = val_enum(enum_name, ctor_tag, val_none());
            }
            return 1;
        }
        if (method->count > 4 && memcmp(method->c_str, "get_", 4) == 0) {
            Value v = eval_expr(scope, Expr_child(e, &(I64){(I64)(1)}));
            *result = clone_value(v.enum_inst->payload);
            return 1;
        }
    }

    // is_Variant: works for both simple and payload enums
    if (method->count > 3 && memcmp(method->c_str, "is_", 3) == 0) {
        Str var_name = {.c_str = method->c_str + 3, .count = method->count - 3};
        I32 tag = *enum_variant_tag(enum_def, &var_name);
        Value v = eval_expr(scope, Expr_child(e, &(I64){(I64)(1)}));
        if (v.type == VAL_ENUM)
            *result = val_bool(v.enum_inst->tag == tag);
        else
            *result = val_bool(*v.i32 == tag);
        return 1;
    }

    return 0;
}

// Try to dlsym a name, using ffi_handle first (if available), then RTLD_DEFAULT
static void *ffi_dlsym(const char *name) {
    void *fn = NULL;
    if (ffi_handle)
        fn = dlsym(ffi_handle, name);
    if (!fn)
        fn = dlsym(RTLD_DEFAULT, name);
    return fn;
}

// Register an ext_func/ext_proc in ffi_map
static void ffi_register(Str *name, void *fn, Expr *fdef) {
    U32 np = fdef->data.data.FuncDef.nparam;
    ffi_type **atypes = malloc(sizeof(ffi_type *) * (np > 0 ? np : 1));
    bool *pshallows = NULL;
    bool has_shallow = false;
    for (U32 k = 0; k < np; k++) {
        if (fdef->data.data.FuncDef.param_shallows.count > 0 && (*(Bool*)Vec_get(&fdef->data.data.FuncDef.param_shallows, &(U64){(U64)(k)}))) {
            atypes[k] = shallow_ffi_type(((Str*)Vec_get(&fdef->data.data.FuncDef.param_types, &(U64){(U64)(k)})));
            has_shallow = true;
        } else {
            atypes[k] = &ffi_type_pointer;
        }
    }
    if (has_shallow) {
        pshallows = malloc(sizeof(bool) * np);
        for (U32 k = 0; k < np; k++)
            pshallows[k] = VEC_SET(fdef->data.data.FuncDef.param_shallows) && (*(Bool*)Vec_get(&fdef->data.data.FuncDef.param_shallows, &(U64){(U64)(k)}));
    }
    bool ret_shallow = fdef->data.data.FuncDef.return_is_shallow;
    FFIEntry entry = {
        .fn = fn,
        .return_type = (fdef->data.data.FuncDef.return_type).count > 0 ? FDEF_RTYPE(fdef) : NULL,
        .nparam = np,
        .param_shallows = pshallows,
        .return_is_shallow = ret_shallow,
        .arg_types = atypes,
    };
    ffi_type *rtype = &ffi_type_void;
    if (entry.return_type) {
        rtype = ret_shallow ? shallow_ffi_type(entry.return_type) : &ffi_type_pointer;
    }
    ffi_prep_cif(&entry.cif, FFI_DEFAULT_ABI, np, rtype, atypes);
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW};
      FFIEntry *_v = malloc(sizeof(FFIEntry)); *_v = entry;
      Map_set(&ffi_map, _k, _v); }
}

I32 ffi_init(Expr *program, Str *user_c_path, Str *ext_c_path, Str *link_flags) {
    if (ffi_loaded) ffi_cleanup();  // re-init (e.g. precomp then interpret)
    Str *so_path = NULL;

    // Compile user .c to shared library (if provided)
    if (user_c_path) {
        Str *ext_dir;
        Str _dot_str = {.c_str = (U8*)".", .count = 1, .cap = CAP_LIT};
        {
            I64 slash = *Str_rfind(ext_c_path, &(Str){.c_str = (U8*)"/", .count = 1, .cap = CAP_LIT});
            ext_dir = slash >= 0 ? Str_substr(ext_c_path, &(U64){(U64)(0)}, &(U64){(U64)(slash)}) : &_dot_str;
        }
        char pid_buf[32];
        snprintf(pid_buf, sizeof(pid_buf), "tmp/ffi_%d.so", (int)getpid());
        so_path = Str_clone(&(Str){.c_str = (U8*)(pid_buf), .count = (U64)strlen((const char*)(pid_buf)), .cap = CAP_VIEW});
        system("mkdir -p tmp");
        Str *lf = link_flags ? link_flags : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
        Str *cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
            &(Str){.c_str = (U8*)"cc -Wall -Wextra -shared -fPIC -I", .count = 33, .cap = CAP_LIT}, ext_dir),
            &(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}), so_path),
            &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), user_c_path), lf);
        int rc = system((const char *)cmd->c_str);
        if (rc != 0) {
            fprintf(stderr, "error: failed to compile FFI library '%s'\n", user_c_path->c_str);
            return 1;
        }
        ffi_handle = dlopen((const char *)so_path->c_str, RTLD_NOW);
        if (!ffi_handle) {
            fprintf(stderr, "error: dlopen failed: %s\n", dlerror());
            return 1;
        }
    }

    // dlopen linked libraries so their symbols are available via RTLD_DEFAULT
    if (link_flags) {
        const char *p = (const char *)link_flags->c_str;
        while ((p = strstr(p, "-l")) != NULL) {
            p += 2;
            char lib[256];
            int i = 0;
            while (*p && *p != ' ' && i < 255)
                lib[i++] = *p++;
            lib[i] = '\0';
            if (i > 0) {
                char soname[280];
                snprintf(soname, sizeof(soname), "lib%s.so", lib);
                dlopen(soname, RTLD_NOW | RTLD_GLOBAL);
            }
        }
    }

    // Build struct def map for return type lookup
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); ffi_struct_defs = *_mp; free(_mp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(I64){(I64)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl || stmt->children.count == 0) continue;
        if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag != ExprData_TAG_StructDef) continue;
        Expr *sdef = Expr_child(stmt, &(I64){(I64)(0)});
        { Str *_k = malloc(sizeof(Str)); *_k = (Str){stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.count, CAP_VIEW};
          Expr **_v = malloc(sizeof(Expr *)); *_v = sdef;
          Map_set(&ffi_struct_defs, _k, _v); }
    }

    // Scan program for ext_func/ext_proc, dlsym each
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(U64){sizeof(Str)}, &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(FFIEntry)}); ffi_map = *_mp; free(_mp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(I64){(I64)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl || stmt->children.count == 0) continue;

        // Top-level ext_func/ext_proc
        if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef) {
            Expr *fdef = Expr_child(stmt, &(I64){(I64)(0)});
            FuncType fft = fdef->data.data.FuncDef.func_type;
            if (fft.tag != FuncType_TAG_ExtFunc && fft.tag != FuncType_TAG_ExtProc) continue;

            void *fn = ffi_dlsym((const char *)stmt->data.data.Decl.name.c_str);
            if (!fn) continue;
            ffi_register(DECL_NAME(stmt), fn, fdef);
        }

        // ext_struct namespace methods
        if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_StructDef && Expr_child(stmt, &(I64){(I64)(0)})->is_ext) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *body = Expr_child(Expr_child(stmt, &(I64){(I64)(0)}), &(I64){(I64)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(I64){(I64)(j)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (field->children.count == 0) continue;
                Expr *fdef = Expr_child(field, &(I64){(I64)(0)});
                if (fdef->data.tag != ExprData_TAG_FuncDef) continue;
                FuncType fft = fdef->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) {
                    char flat_name[256];
                    snprintf(flat_name, sizeof(flat_name), "%s_%s", sname->c_str, field->data.data.Decl.name.c_str);
                    void *fn = ffi_dlsym(flat_name);
                    if (fn) {
                        Str *key = Str_clone(&(Str){.c_str = (U8*)(flat_name), .count = (U64)strlen((const char*)(flat_name)), .cap = CAP_VIEW});
                        ffi_register(key, fn, fdef);
                    }
                } else if (fft.tag == FuncType_TAG_Func || fft.tag == FuncType_TAG_Proc) {
                    // Scan function body for nested ext_func/ext_proc declarations
                    Expr *fbody = Expr_child(fdef, &(I64){(I64)(0)});
                    for (U32 k = 0; k < fbody->children.count; k++) {
                        Expr *inner = Expr_child(fbody, &(I64){(I64)(k)});
                        if (inner->data.tag != ExprData_TAG_Decl || inner->children.count == 0) continue;
                        Expr *idef = Expr_child(inner, &(I64){(I64)(0)});
                        if (idef->data.tag != ExprData_TAG_FuncDef) continue;
                        FuncType ift = idef->data.data.FuncDef.func_type;
                        if (ift.tag != FuncType_TAG_ExtFunc && ift.tag != FuncType_TAG_ExtProc) continue;
                        void *fn = ffi_dlsym((const char *)inner->data.data.Decl.name.c_str);
                        if (fn) ffi_register(DECL_NAME(inner), fn, idef);
                    }
                }
            }
        }
    }

    ffi_loaded = 1;
    if (so_path) unlink((const char *)so_path->c_str);
    return 0;
}

void ffi_cleanup(void) {
    if (ffi_handle) {
        dlclose(ffi_handle);
        ffi_handle = NULL;
    }
    if (ffi_loaded) {
        Map_delete(&ffi_map, &(Bool){0});
        Map_delete(&ffi_struct_defs, &(Bool){0});
        ffi_loaded = 0;
    }
    if (ffi_type_cache_inited) {
        for (U32 i = 0; i < ffi_type_cache.count; i++) {
            ffi_type *t = *(ffi_type **)Vec_get(&ffi_type_cache, &(U64){(U64)(i)});
            free(t->elements);
            free(t);
        }
        Vec_delete(&ffi_type_cache, &(Bool){0});
        ffi_type_cache_inited = 0;
    }
}
