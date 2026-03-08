#include "dispatch.h"
#include "ccore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <ffi.h>

// Codegen Str layout (matches ext.h Str: {U8 *data, I64 count, I64 cap})
// Distinct from compiler-internal Str (str.h: {char *c_str, I64 count, I64 cap})
typedef struct { U8 *data; I64 count; I64 cap; } ExtStr;

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
    ffi_cif cif;
    ffi_type **arg_types;
} FFIEntry;

static Map ffi_map;          // name -> FFIEntry
static Map ffi_struct_defs;  // Str* name -> Expr* struct_def (for return type lookup)
static void *ffi_handle;     // dlopen handle
static Bool ffi_loaded;

// Map a til type name to the appropriate ffi_type for shallow params
static ffi_type *shallow_ffi_type(Str *type_name) {
    if (Str_eq_c(type_name, "I64"))  return &ffi_type_sint64;
    if (Str_eq_c(type_name, "U8"))   return &ffi_type_uint8;
    if (Str_eq_c(type_name, "I16"))  return &ffi_type_sint16;
    if (Str_eq_c(type_name, "I32"))  return &ffi_type_sint32;
    if (Str_eq_c(type_name, "U32"))  return &ffi_type_uint32;
    if (Str_eq_c(type_name, "Bool")) return &ffi_type_uint8;
    return &ffi_type_pointer; // Dynamic or other
}

// === Eval helper for Dynamic narrowing ===
// When the typer narrows a Dynamic arg to a concrete type, the expression's
// til_type is the target. If the runtime value is VAL_PTR (from ptr_add/malloc),
// reinterpret it as the narrowed type so dispatch handlers see the right union field.
static Value eval_arg(Scope *s, Expr *e) {
    Value v = eval_expr(s, e);
    if (v.type == VAL_PTR && e->til_type != TIL_TYPE_DYNAMIC) {
        switch (e->til_type) {
            case TIL_TYPE_I64:    return (Value){.type = VAL_I64, .i64 = (I64 *)v.ptr};
            case TIL_TYPE_U8:    return (Value){.type = VAL_U8, .u8 = (U8 *)v.ptr};
            case TIL_TYPE_I16:   return (Value){.type = VAL_I16, .i16 = (I16 *)v.ptr};
            case TIL_TYPE_I32:   return (Value){.type = VAL_I32, .i32 = (I32 *)v.ptr};
            case TIL_TYPE_U32:   return (Value){.type = VAL_U32, .u32 = (U32 *)v.ptr};
            case TIL_TYPE_BOOL:  return (Value){.type = VAL_BOOL, .boolean = (Bool *)v.ptr};
            case TIL_TYPE_STRUCT:
                if (e->struct_name && Str_eq_c(e->struct_name, "Str")) {
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

// 2-arg handler: eval both args, call cfn(xa, xb), wrap result
#define H2(hname, cfn, xa, xb, w) \
static Bool h_##hname(Scope *s, Expr *e, Value *r) { \
    Value a = eval_arg(s, expr_child(e,1)); \
    Value b = eval_arg(s, expr_child(e,2)); \
    *r = w(cfn(xa, xb)); return 1; }

// 1-arg handler: eval one arg, call cfn(xv), wrap result
#define H1(hname, cfn, xv, w) \
static Bool h_##hname(Scope *s, Expr *e, Value *r) { \
    Value v = eval_arg(s, expr_child(e,1)); \
    *r = w(cfn(xv)); return 1; }

// Delete handler: check VAL_NONE, eval call_free flag, conditionally delete
#define HDEL(hname, dfn, xv) \
static Bool h_##hname(Scope *s, Expr *e, Value *r) { \
    Value v = eval_arg(s, expr_child(e,1)); \
    if (v.type == VAL_NONE) { *r = val_none(); return 1; } \
    Value cf = eval_arg(s, expr_child(e,2)); \
    if (*cf.boolean) dfn(xv); \
    *r = val_none(); return 1; }

// Clone handler: eval one arg, copy raw value
#define HCLONE(hname, xv, w) \
static Bool h_##hname(Scope *s, Expr *e, Value *r) { \
    Value v = eval_arg(s, expr_child(e,1)); \
    *r = w(xv); return 1; }

// === I64 handlers ===
H2(I64_add, I64_add, *a.i64, *b.i64, val_i64)
H2(I64_sub, I64_sub, *a.i64, *b.i64, val_i64)
H2(I64_mul, I64_mul, *a.i64, *b.i64, val_i64)
H2(I64_div, I64_div, *a.i64, *b.i64, val_i64)
H2(I64_mod, I64_mod, *a.i64, *b.i64, val_i64)
H2(I64_and, I64_and, *a.i64, *b.i64, val_i64)
H2(I64_or,  I64_or,  *a.i64, *b.i64, val_i64)
H2(I64_xor, I64_xor, *a.i64, *b.i64, val_i64)
H2(I64_eq, I64_eq, *a.i64, *b.i64, val_bool)
H2(I64_cmp, I64_cmp, *a.i64, *b.i64, val_i64)
HCLONE(I64_clone, *v.i64, val_i64)
HDEL(I64_delete, I64_delete, v.i64)

// === U8 handlers ===
H2(U8_add, U8_add, *a.u8, *b.u8, val_u8)
H2(U8_sub, U8_sub, *a.u8, *b.u8, val_u8)
H2(U8_mul, U8_mul, *a.u8, *b.u8, val_u8)
H2(U8_div, U8_div, *a.u8, *b.u8, val_u8)
H2(U8_mod, U8_mod, *a.u8, *b.u8, val_u8)
H2(U8_and, U8_and, *a.u8, *b.u8, val_u8)
H2(U8_or,  U8_or,  *a.u8, *b.u8, val_u8)
H2(U8_xor, U8_xor, *a.u8, *b.u8, val_u8)
H2(U8_eq, U8_eq, *a.u8, *b.u8, val_bool)
H2(U8_cmp, U8_cmp, *a.u8, *b.u8, val_i64)
H1(U8_to_i64, U8_to_i64, *v.u8, val_i64)
HCLONE(U8_clone, *v.u8, val_u8)
HDEL(U8_delete, U8_delete, v.u8)

static Bool h_U8_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, expr_child(e,1));
    *r = val_u8(U8_from_i64(*v.i64)); return 1;
}

// === I16 handlers ===
H2(I16_add, I16_add, *a.i16, *b.i16, val_i16)
H2(I16_sub, I16_sub, *a.i16, *b.i16, val_i16)
H2(I16_mul, I16_mul, *a.i16, *b.i16, val_i16)
H2(I16_div, I16_div, *a.i16, *b.i16, val_i16)
H2(I16_mod, I16_mod, *a.i16, *b.i16, val_i16)
H2(I16_and, I16_and, *a.i16, *b.i16, val_i16)
H2(I16_or,  I16_or,  *a.i16, *b.i16, val_i16)
H2(I16_xor, I16_xor, *a.i16, *b.i16, val_i16)
H2(I16_eq, I16_eq, *a.i16, *b.i16, val_bool)
H2(I16_cmp, I16_cmp, *a.i16, *b.i16, val_i64)
H1(I16_to_i64, I16_to_i64, *v.i16, val_i64)
HCLONE(I16_clone, *v.i16, val_i16)
HDEL(I16_delete, I16_delete, v.i16)

static Bool h_I16_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, expr_child(e,1));
    *r = val_i16(I16_from_i64(*v.i64)); return 1;
}

// === I32 handlers ===
H2(I32_add, I32_add, *a.i32, *b.i32, val_i32)
H2(I32_sub, I32_sub, *a.i32, *b.i32, val_i32)
H2(I32_mul, I32_mul, *a.i32, *b.i32, val_i32)
H2(I32_div, I32_div, *a.i32, *b.i32, val_i32)
H2(I32_mod, I32_mod, *a.i32, *b.i32, val_i32)
H2(I32_and, I32_and, *a.i32, *b.i32, val_i32)
H2(I32_or,  I32_or,  *a.i32, *b.i32, val_i32)
H2(I32_xor, I32_xor, *a.i32, *b.i32, val_i32)
H2(I32_eq, I32_eq, *a.i32, *b.i32, val_bool)
H2(I32_cmp, I32_cmp, *a.i32, *b.i32, val_i64)
H1(I32_to_i64, I32_to_i64, *v.i32, val_i64)
HCLONE(I32_clone, *v.i32, val_i32)
HDEL(I32_delete, I32_delete, v.i32)

static Bool h_I32_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, expr_child(e,1));
    *r = val_i32(I32_from_i64(*v.i64)); return 1;
}

// === U32 handlers ===
H2(U32_add, U32_add, *a.u32, *b.u32, val_u32)
H2(U32_sub, U32_sub, *a.u32, *b.u32, val_u32)
H2(U32_mul, U32_mul, *a.u32, *b.u32, val_u32)
H2(U32_div, U32_div, *a.u32, *b.u32, val_u32)
H2(U32_mod, U32_mod, *a.u32, *b.u32, val_u32)
H2(U32_and, U32_and, *a.u32, *b.u32, val_u32)
H2(U32_or,  U32_or,  *a.u32, *b.u32, val_u32)
H2(U32_xor, U32_xor, *a.u32, *b.u32, val_u32)
H2(U32_eq, U32_eq, *a.u32, *b.u32, val_bool)
H2(U32_cmp, U32_cmp, *a.u32, *b.u32, val_i64)
H1(U32_to_i64, U32_to_i64, *v.u32, val_i64)
HCLONE(U32_clone, *v.u32, val_u32)
HDEL(U32_delete, U32_delete, v.u32)

static Bool h_U32_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, expr_child(e,1));
    *r = val_u32(U32_from_i64(*v.i64)); return 1;
}

// === Bool handlers ===
H2(Bool_eq,  Bool_eq,  *a.boolean, *b.boolean, val_bool)
H2(Bool_and, Bool_and, *a.boolean, *b.boolean, val_bool)
H2(Bool_or,  Bool_or,  *a.boolean, *b.boolean, val_bool)
H1(Bool_not, Bool_not, *v.boolean, val_bool)
HCLONE(Bool_clone, *v.boolean, val_bool)
HDEL(Bool_delete, Bool_delete, v.boolean)

static void *val_to_ptr(Value v);

// === Print handlers ===

static Bool h_print_single(Scope *s, Expr *e, Value *r) {
    Value arg = eval_expr(s, expr_child(e, 1));
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
    Value a = eval_expr(s, expr_child(e,1));
    exit((int)*a.i64);
    *r = val_none(); return 1;
}

static Bool h_free(Scope *s, Expr *e, Value *r) {
    if (expr_child(e, 1)->type != NODE_IDENT) {
        Value val = eval_expr(s, expr_child(e,1));
        void *ptr = val_to_ptr(val);
        if (ptr) free(ptr);
        *r = val_none();
        return 1;
    }
    Cell *cell = scope_get(s, expr_child(e, 1)->data.str_val);
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
    Value type_name_val = eval_expr(s, expr_child(e,1));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    Value method_val = eval_expr(s, expr_child(e,2));
    Str _mn = str_view(method_val);
    Str *method = &_mn;

    Expr type_ident = {0};
    type_ident.type = NODE_IDENT;
    type_ident.data.str_val = type_name;
    type_ident.struct_name = type_name;
    type_ident.line = e->line;
    type_ident.col = e->col;

    Expr field_access = {0};
    field_access.type = NODE_FIELD_ACCESS;
    field_access.data.str_val = method;
    field_access.is_ns_field = 1;
    field_access.line = e->line;
    field_access.col = e->col;
    field_access.children = Vec_new(sizeof(Expr *));
    Expr *ti_ptr = &type_ident;
    Vec_push(&field_access.children, &ti_ptr);

    Expr fake_call = {0};
    fake_call.type = NODE_FCALL;
    fake_call.line = e->line;
    fake_call.col = e->col;
    fake_call.children = Vec_new(sizeof(Expr *));
    Expr *fa_ptr = &field_access;
    Vec_push(&fake_call.children, &fa_ptr);
    for (U32 i = 3; i < e->children.count; i++) {
        Expr *arg = expr_child(e, i);
        Vec_push(&fake_call.children, &arg);
    }

    Value fn_val = eval_expr(s, &field_access);
    if (fn_val.type == VAL_FUNC && fn_val.func->type == NODE_FUNC_DEF) {
        Expr *fdef = fn_val.func;
        U32 nparam = fdef->data.func_def.nparam;
        U32 nargs = fake_call.children.count - 1;
        for (U32 i = nargs; i < nparam; i++) {
            if (fdef->data.func_def.param_defaults &&
                fdef->data.func_def.param_defaults[i]) {
                Expr *def_arg = fdef->data.func_def.param_defaults[i];
                Vec_push(&fake_call.children, &def_arg);
            }
        }
    }

    *r = eval_call(s, &fake_call);

    Vec_delete(&fake_call.children);
    Vec_delete(&field_access.children);
    return 1;
}

// dyn_has_method(type_name, "method") → Bool
static Bool h_dyn_has_method(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e,1));
    Value method_val = eval_expr(s, expr_child(e,2));
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
    Value *size_fn = ns_get(type_name, Str_new("size"));
    if (!size_fn) {
        fprintf(stderr, "%s:%u:%u: error: array/vec: type '%s' has no size() method "
                "(hint: add %s.size() somewhere to prevent scavenger removal, see #15)\n",
                src->path->c_str, src->line, src->col, type_name->c_str, type_name->c_str);
        exit(1);
    }
    // Build fake call: Type.size()
    Expr type_ident = {0};
    type_ident.type = NODE_IDENT;
    type_ident.data.str_val = type_name;
    type_ident.struct_name = type_name;
    type_ident.line = src->line; type_ident.col = src->col;
    type_ident.path = src->path;

    Expr field_access = {0};
    field_access.type = NODE_FIELD_ACCESS;
    field_access.data.str_val = Str_new("size");
    field_access.is_ns_field = 1;
    field_access.line = src->line; field_access.col = src->col;
    field_access.path = src->path;
    field_access.children = Vec_new(sizeof(Expr *));
    Expr *ti = &type_ident;
    Vec_push(&field_access.children, &ti);

    Expr fake_call = {0};
    fake_call.type = NODE_FCALL;
    fake_call.line = src->line; fake_call.col = src->col;
    fake_call.path = src->path;
    fake_call.children = Vec_new(sizeof(Expr *));
    Expr *fa = &field_access;
    Vec_push(&fake_call.children, &fa);

    Value result = eval_call(s, &fake_call);
    Vec_delete(&fake_call.children);
    Vec_delete(&field_access.children);
    return (I32)*result.i64;
}

// array("I64", 1, 2, 3)
static Bool h_array(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e, 1));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    U32 count = e->children.count - 2;
    I32 elem_size = get_elem_size(s, type_name, e);

    // Allocate array data
    void *data = malloc(count * elem_size);
    memset(data, 0, count * elem_size);

    // Evaluate each element and copy into data buffer
    for (U32 i = 0; i < count; i++) {
        Value elem = eval_expr(s, expr_child(e, i + 2));
        void *src = val_raw_ptr(elem);
        if (src) {
            if (elem.type == VAL_STRUCT && Str_eq_c(elem.instance->struct_name, "Str")) {
                // Deep-copy Str: copy flat bytes then strndup the data pointer
                memcpy((char *)data + i * elem_size, src, elem_size);
                char **dp = (char **)((char *)data + i * elem_size);
                I64 slen = *(I64 *)((char *)data + i * elem_size + 8);
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
    Str fn_data = {.c_str = "data", .count = 4};
    Str fn_cap = {.c_str = "cap", .count = 3};
    Str fn_esz = {.c_str = "elem_size", .count = 9};
    Str fn_et = {.c_str = "elem_type", .count = 9};
    write_field(si, find_field_decl(cached_array_def, &fn_data), (Value){.type = VAL_PTR, .ptr = data});
    write_field(si, find_field_decl(cached_array_def, &fn_cap), val_i64(count));
    write_field(si, find_field_decl(cached_array_def, &fn_esz), val_i64(elem_size));
    write_field(si, find_field_decl(cached_array_def, &fn_et), make_str_value(type_name->c_str, type_name->count));

    r->type = VAL_STRUCT;
    r->instance = si;
    return 1;
}

// vec("I64", 1, 2, 3)
static Bool h_vec(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e, 1));
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
        Value elem = eval_expr(s, expr_child(e, i + 2));
        void *src = val_raw_ptr(elem);
        if (src) {
            if (elem.type == VAL_STRUCT && Str_eq_c(elem.instance->struct_name, "Str")) {
                memcpy((char *)data + i * elem_size, src, elem_size);
                char **dp = (char **)((char *)data + i * elem_size);
                I64 slen = *(I64 *)((char *)data + i * elem_size + 8);
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
    Str fn_data = {.c_str = "data", .count = 4};
    Str fn_count = {.c_str = "count", .count = 5};
    Str fn_cap = {.c_str = "cap", .count = 3};
    Str fn_esz = {.c_str = "elem_size", .count = 9};
    Str fn_et = {.c_str = "elem_type", .count = 9};
    write_field(si, find_field_decl(cached_vec_def, &fn_data), (Value){.type = VAL_PTR, .ptr = data});
    write_field(si, find_field_decl(cached_vec_def, &fn_count), val_i64(count));
    write_field(si, find_field_decl(cached_vec_def, &fn_cap), val_i64(cap));
    write_field(si, find_field_decl(cached_vec_def, &fn_esz), val_i64(elem_size));
    write_field(si, find_field_decl(cached_vec_def, &fn_et), make_str_value(type_name->c_str, type_name->count));

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
        case VAL_BOOL:   return v.boolean;
        case VAL_STRUCT: return v.instance->data;
        default:         return NULL;
    }
}


static Bool h_ptr_add(Scope *s, Expr *e, Value *r) {
    Value buf = eval_expr(s, expr_child(e,1));
    Value offset = eval_expr(s, expr_child(e,2));
    *r = (Value){.type = VAL_PTR, .ptr = (char *)buf.ptr + (I32)*offset.i64};
    return 1;
}


// === System primitive handlers ===

static Bool h_readfile(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, expr_child(e,1));
    Str sv = str_view(path);
    char *p = strndup(sv.c_str, sv.count);
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
    *r = make_str_value_own(buf, (I64)len);
    return 1;
}

static Bool h_writefile(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, expr_child(e,1));
    Value content = eval_expr(s, expr_child(e,2));
    Str pv = str_view(path);
    Str cv = str_view(content);
    char *p = strndup(pv.c_str, pv.count);
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
    Value cmd = eval_expr(s, expr_child(e,1));
    Str sv = str_view(cmd);
    char *c = strndup(sv.c_str, sv.count);
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
    Value pidv = eval_expr(s, expr_child(e,1));
    int status;
    pid_t result = waitpid((pid_t)*pidv.i64, &status, WNOHANG);
    if (result == 0) { *r = val_i64(-1); return 1; }
    if (WIFEXITED(status)) { *r = val_i64(WEXITSTATUS(status)); return 1; }
    *r = val_i64(-1);
    return 1;
}

static Bool h_sleep(Scope *s, Expr *e, Value *r) {
    Value ms = eval_expr(s, expr_child(e,1));
    usleep((useconds_t)(*ms.i64 * 1000));
    *r = val_none();
    return 1;
}

static Bool h_file_mtime(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, expr_child(e,1));
    Str sv = str_view(path);
    char *p = strndup(sv.c_str, sv.count);
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

#undef H1
#undef H2
#undef HDEL
#undef HCLONE

// === Dispatch init ===

static void dispatch_init(void) {
    dispatch_map = Map_new(sizeof(Str *), sizeof(DispatchFn), str_ptr_cmp);

    #define REG(n, fn) do { Str *k = Str_new(n); DispatchFn f = fn; Map_set(&dispatch_map, &k, &f); } while(0)

    // Print
    REG("print_single", h_print_single);
    REG("print_flush", h_print_flush);

    // I64
    REG("I64_add", h_I64_add); REG("I64_sub", h_I64_sub);
    REG("I64_mul", h_I64_mul); REG("I64_div", h_I64_div);
    REG("I64_mod", h_I64_mod);
    REG("I64_and", h_I64_and); REG("I64_or", h_I64_or); REG("I64_xor", h_I64_xor);
    REG("I64_eq", h_I64_eq); REG("I64_cmp", h_I64_cmp);
    REG("I64_clone", h_I64_clone);
    REG("I64_delete", h_I64_delete);

    // U8
    REG("U8_add", h_U8_add); REG("U8_sub", h_U8_sub);
    REG("U8_mul", h_U8_mul); REG("U8_div", h_U8_div);
    REG("U8_mod", h_U8_mod);
    REG("U8_and", h_U8_and); REG("U8_or", h_U8_or); REG("U8_xor", h_U8_xor);
    REG("U8_eq", h_U8_eq); REG("U8_cmp", h_U8_cmp);
    REG("U8_to_i64", h_U8_to_i64);
    REG("U8_from_i64", h_U8_from_i64);
    REG("U8_from_i64_ext", h_U8_from_i64);
    REG("U8_clone", h_U8_clone);
    REG("U8_delete", h_U8_delete);

    // I16
    REG("I16_add", h_I16_add); REG("I16_sub", h_I16_sub);
    REG("I16_mul", h_I16_mul); REG("I16_div", h_I16_div);
    REG("I16_mod", h_I16_mod);
    REG("I16_and", h_I16_and); REG("I16_or", h_I16_or); REG("I16_xor", h_I16_xor);
    REG("I16_eq", h_I16_eq); REG("I16_cmp", h_I16_cmp);
    REG("I16_to_i64", h_I16_to_i64);
    REG("I16_from_i64", h_I16_from_i64);
    REG("I16_from_i64_ext", h_I16_from_i64);
    REG("I16_clone", h_I16_clone);
    REG("I16_delete", h_I16_delete);

    // I32
    REG("I32_add", h_I32_add); REG("I32_sub", h_I32_sub);
    REG("I32_mul", h_I32_mul); REG("I32_div", h_I32_div);
    REG("I32_mod", h_I32_mod);
    REG("I32_and", h_I32_and); REG("I32_or", h_I32_or); REG("I32_xor", h_I32_xor);
    REG("I32_eq", h_I32_eq); REG("I32_cmp", h_I32_cmp);
    REG("I32_to_i64", h_I32_to_i64);
    REG("I32_from_i64", h_I32_from_i64);
    REG("I32_from_i64_ext", h_I32_from_i64);
    REG("I32_clone", h_I32_clone);
    REG("I32_delete", h_I32_delete);

    // U32
    REG("U32_add", h_U32_add); REG("U32_sub", h_U32_sub);
    REG("U32_mul", h_U32_mul); REG("U32_div", h_U32_div);
    REG("U32_mod", h_U32_mod);
    REG("U32_and", h_U32_and); REG("U32_or", h_U32_or); REG("U32_xor", h_U32_xor);
    REG("U32_eq", h_U32_eq); REG("U32_cmp", h_U32_cmp);
    REG("U32_to_i64", h_U32_to_i64);
    REG("U32_from_i64", h_U32_from_i64);
    REG("U32_from_i64_ext", h_U32_from_i64);
    REG("U32_clone", h_U32_clone);
    REG("U32_delete", h_U32_delete);

    // Bool
    REG("Bool_eq", h_Bool_eq);
    REG("and", h_Bool_and); REG("or", h_Bool_or);
    REG("not", h_Bool_not);
    REG("Bool_clone", h_Bool_clone);
    REG("Bool_delete", h_Bool_delete);

    // Misc
    REG("exit", h_exit);
    REG("free", h_free);

    // Pointer primitives
    REG("ptr_add", h_ptr_add);

    // Collection builtins
    REG("array", h_array);
    REG("vec", h_vec);

    // Dynamic dispatch
    REG("dyn_call1", h_dyn_call);
    REG("dyn_call2", h_dyn_call);
    REG("dyn_call1_ret", h_dyn_call);
    REG("dyn_call2_ret", h_dyn_call);
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

    DispatchFn *fn = Map_get(&dispatch_map, &name);
    if (fn) return (*fn)(scope, e, result);

    // FFI dispatch via libffi
    if (ffi_loaded) {
        FFIEntry *fe = Map_get(&ffi_map, &name);
        if (fe) {
            U32 nargs = e->children.count - 1;
            void *args[nargs > 0 ? nargs : 1];
            void *arg_ptrs[nargs > 0 ? nargs : 1];
            for (U32 i = 0; i < nargs; i++) {
                Value v = eval_expr(scope, expr_child(e, i + 1));
                if (fe->param_shallows && i < (U32)fe->nparam && fe->param_shallows[i]) {
                    // Shallow: store dereferenced value directly for ffi
                    switch (v.type) {
                        case VAL_I64:  *(I64 *)&args[i] = *v.i64; break;
                        case VAL_U8:   *(U8 *)&args[i] = *v.u8; break;
                        case VAL_I16:  *(I16 *)&args[i] = *v.i16; break;
                        case VAL_I32:  *(I32 *)&args[i] = *v.i32; break;
                        case VAL_U32:  *(U32 *)&args[i] = *v.u32; break;
                        case VAL_BOOL: *(U8 *)&args[i] = *v.boolean ? 1 : 0; break;
                        default:       args[i] = v.ptr; break; // Dynamic stays as pointer
                    }
                } else {
                    // Deep: pass pointer (existing behavior)
                    switch (v.type) {
                        case VAL_I64:    args[i] = v.i64; break;
                        case VAL_U8:     args[i] = v.u8; break;
                        case VAL_I16:    args[i] = v.i16; break;
                        case VAL_I32:    args[i] = v.i32; break;
                        case VAL_U32:    args[i] = v.u32; break;
                        case VAL_BOOL:   args[i] = v.boolean; break;
                        case VAL_PTR:    args[i] = v.ptr; break;
                        case VAL_STRUCT: args[i] = v.instance->data; break;
                        default:         args[i] = NULL; break;
                    }
                }
                arg_ptrs[i] = &args[i];
            }
            void *raw = NULL;
            ffi_call(&fe->cif, FFI_FN(fe->fn), &raw, nargs > 0 ? arg_ptrs : NULL);
            if (!fe->return_type) {
                *result = val_none();
            } else if (Str_eq_c(fe->return_type, "Str")) {
                ExtStr *sp = (ExtStr *)raw;
                *result = make_str_value_own((char *)sp->data, sp->count);
            } else if (Str_eq_c(fe->return_type, "I64")) {
                *result = (Value){.type = VAL_I64, .i64 = (I64 *)raw};
            } else if (Str_eq_c(fe->return_type, "U8")) {
                *result = (Value){.type = VAL_U8, .u8 = (U8 *)raw};
            } else if (Str_eq_c(fe->return_type, "I16")) {
                *result = (Value){.type = VAL_I16, .i16 = (I16 *)raw};
            } else if (Str_eq_c(fe->return_type, "I32")) {
                *result = (Value){.type = VAL_I32, .i32 = (I32 *)raw};
            } else if (Str_eq_c(fe->return_type, "U32")) {
                *result = (Value){.type = VAL_U32, .u32 = (U32 *)raw};
            } else if (Str_eq_c(fe->return_type, "Bool")) {
                *result = (Value){.type = VAL_BOOL, .boolean = (Bool *)raw};
            } else if (Str_eq_c(fe->return_type, "Dynamic")) {
                *result = (Value){.type = VAL_PTR, .ptr = raw};
            } else {
                // Struct return — look up struct def by return type name
                Expr **sdef = Map_get(&ffi_struct_defs, &fe->return_type);
                if (sdef) {
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
    Bool hp = enum_has_payloads(enum_def);

    if (hp) {
        // Payload enum: constructor, get_Variant
        I32 ctor_tag = enum_variant_tag(enum_def, method);
        if (ctor_tag >= 0) {
            if (enum_variant_type(enum_def, ctor_tag)) {
                Value payload = eval_expr(scope, expr_child(e, 1));
                *result = val_enum(enum_name, ctor_tag, clone_value(payload));
            } else {
                *result = val_enum(enum_name, ctor_tag, val_none());
            }
            return 1;
        }
        if (method->count > 4 && memcmp(method->c_str, "get_", 4) == 0) {
            Value v = eval_expr(scope, expr_child(e, 1));
            *result = clone_value(v.enum_inst->payload);
            return 1;
        }
    }

    // is_Variant: works for both simple and payload enums
    if (method->count > 3 && memcmp(method->c_str, "is_", 3) == 0) {
        Str var_name = {.c_str = method->c_str + 3, .count = method->count - 3};
        I32 tag = enum_variant_tag(enum_def, &var_name);
        Value v = eval_expr(scope, expr_child(e, 1));
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
    U32 np = fdef->data.func_def.nparam;
    ffi_type **atypes = malloc(sizeof(ffi_type *) * (np > 0 ? np : 1));
    bool *pshallows = NULL;
    bool has_shallow = false;
    for (U32 k = 0; k < np; k++) {
        if (fdef->data.func_def.param_shallows && fdef->data.func_def.param_shallows[k]) {
            atypes[k] = shallow_ffi_type(fdef->data.func_def.param_types[k]);
            has_shallow = true;
        } else {
            atypes[k] = &ffi_type_pointer;
        }
    }
    if (has_shallow) {
        pshallows = malloc(sizeof(bool) * np);
        for (U32 k = 0; k < np; k++)
            pshallows[k] = fdef->data.func_def.param_shallows && fdef->data.func_def.param_shallows[k];
    }
    FFIEntry entry = {
        .fn = fn,
        .return_type = fdef->data.func_def.return_type,
        .nparam = np,
        .param_shallows = pshallows,
        .arg_types = atypes,
    };
    ffi_type *rtype = entry.return_type ? &ffi_type_pointer : &ffi_type_void;
    ffi_prep_cif(&entry.cif, FFI_DEFAULT_ABI, np, rtype, atypes);
    Map_set(&ffi_map, &name, &entry);
}

I32 ffi_init(Expr *program, const char *user_c_path, const char *ext_c_path, const char *link_flags) {
    char so_path[256] = "";

    // Compile user .c to shared library (if provided)
    if (user_c_path) {
        char ext_dir[256];
        const char *last_slash = strrchr(ext_c_path, '/');
        if (last_slash) {
            I32 dlen = (I32)(last_slash - ext_c_path);
            snprintf(ext_dir, sizeof(ext_dir), "%.*s", dlen, ext_c_path);
        } else {
            snprintf(ext_dir, sizeof(ext_dir), ".");
        }
        snprintf(so_path, sizeof(so_path), "tmp/ffi_%d.so", (int)getpid());
        system("mkdir -p tmp");
        const char *lf = link_flags ? link_flags : "";
        int cmdlen = snprintf(NULL, 0, "cc -shared -fPIC -I%s -o %s %s%s", ext_dir, so_path, user_c_path, lf);
        char *cmd = malloc(cmdlen + 1);
        snprintf(cmd, cmdlen + 1, "cc -shared -fPIC -I%s -o %s %s%s", ext_dir, so_path, user_c_path, lf);
        int rc = system(cmd);
        free(cmd);
        if (rc != 0) {
            fprintf(stderr, "error: failed to compile FFI library '%s'\n", user_c_path);
            return 1;
        }
        ffi_handle = dlopen(so_path, RTLD_NOW);
        if (!ffi_handle) {
            fprintf(stderr, "error: dlopen failed: %s\n", dlerror());
            return 1;
        }
    }

    // dlopen linked libraries so their symbols are available via RTLD_DEFAULT
    if (link_flags) {
        const char *p = link_flags;
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
    ffi_struct_defs = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type != NODE_DECL || stmt->children.count == 0) continue;
        if (expr_child(stmt, 0)->type != NODE_STRUCT_DEF) continue;
        Expr *sdef = expr_child(stmt, 0);
        Map_set(&ffi_struct_defs, &stmt->data.decl.name, &sdef);
    }

    // Scan program for ext_func/ext_proc, dlsym each
    ffi_map = Map_new(sizeof(Str *), sizeof(FFIEntry), str_ptr_cmp);
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type != NODE_DECL || stmt->children.count == 0) continue;

        // Top-level ext_func/ext_proc
        if (expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
            Expr *fdef = expr_child(stmt, 0);
            FuncType fft = fdef->data.func_def.func_type;
            if (fft != FUNC_EXT_FUNC && fft != FUNC_EXT_PROC) continue;

            void *fn = ffi_dlsym(stmt->data.decl.name->c_str);
            if (!fn) continue;
            ffi_register(stmt->data.decl.name, fn, fdef);
        }

        // ext_struct namespace methods
        if (expr_child(stmt, 0)->type == NODE_STRUCT_DEF && expr_child(stmt, 0)->is_ext) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = expr_child(body, j);
                if (!field->data.decl.is_namespace) continue;
                if (field->children.count == 0) continue;
                Expr *fdef = expr_child(field, 0);
                if (fdef->type != NODE_FUNC_DEF) continue;
                FuncType fft = fdef->data.func_def.func_type;
                if (fft != FUNC_EXT_FUNC && fft != FUNC_EXT_PROC) continue;

                char flat_name[256];
                snprintf(flat_name, sizeof(flat_name), "%s_%s", sname->c_str, field->data.decl.name->c_str);
                void *fn = ffi_dlsym(flat_name);
                if (!fn) continue;
                Str *key = Str_new(flat_name);
                ffi_register(key, fn, fdef);
            }
        }
    }

    ffi_loaded = 1;
    if (so_path[0]) unlink(so_path);
    return 0;
}

void ffi_cleanup(void) {
    if (ffi_handle) {
        dlclose(ffi_handle);
        ffi_handle = NULL;
    }
    if (ffi_loaded) {
        Map_delete(&ffi_map);
        Map_delete(&ffi_struct_defs);
        ffi_loaded = 0;
    }
}
