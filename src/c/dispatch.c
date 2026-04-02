#include "../../boot/modes.h"
#include "ext.h"
#include <stdio.h>

extern Expr *cached_array_def;
extern Str *cached_array_name;
extern Expr *cached_vec_def;
extern Str *cached_vec_name;

// Forward declarations for value-param scalar functions (not in ext.h
// because boot redefines them with pointer-param signatures)
U8 U8_from_i64(I64 v);
I16 I16_from_i64(I64 v);
I32 I32_from_i64(I64 v);
F32 F32_from_i64(I64 v);
U32 U32_from_i64(I64 v);
U64 U64_from_i64(I64 v);

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <ffi.h>

#define PARAM_IS_SHALLOW(p) ((p)->own_type.tag == OwnType_TAG_Shallow)
#define RETURN_IS_SHALLOW(fd) ((fd)->return_own_type.tag == OwnType_TAG_Shallow)

// Codegen Str layout (matches ext.h Str: {U8 *data, U64 count, U64 cap})
// Distinct from compiler-internal Str (str.h: {char *c_str, U64 count, U64 cap})
// ExtStr defined in dispatch.til (generated into boot/modes.h)

typedef Bool (*DispatchFn)(Scope *, Expr *, Value *);

// Forward declaration
static ffi_type *build_struct_ffi_type(Expr *struct_def);

FFIType *ffi_type_pointer_ref(void) { return (FFIType *)&ffi_type_pointer; }
FFIType *ffi_type_sint64_ref(void) { return (FFIType *)&ffi_type_sint64; }
FFIType *ffi_type_uint8_ref(void) { return (FFIType *)&ffi_type_uint8; }
FFIType *ffi_type_sint16_ref(void) { return (FFIType *)&ffi_type_sint16; }
FFIType *ffi_type_sint32_ref(void) { return (FFIType *)&ffi_type_sint32; }
FFIType *ffi_type_uint32_ref(void) { return (FFIType *)&ffi_type_uint32; }
FFIType *ffi_type_uint64_ref(void) { return (FFIType *)&ffi_type_uint64; }
FFIType *ffi_type_float_ref(void) { return (FFIType *)&ffi_type_float; }

// Map a til type name to the appropriate ffi_type for shallow params
static ffi_type *shallow_ffi_type(Str *type_name) {
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0))  return &ffi_type_sint64;
    if ((type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0))   return &ffi_type_uint8;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0))  return &ffi_type_sint16;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0))  return &ffi_type_sint32;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0))  return &ffi_type_uint32;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "U64", 3) == 0))  return &ffi_type_uint64;
    if ((type_name->count == 5 && memcmp(type_name->c_str, "USize", 5) == 0)) return &ffi_type_uint32;
    if ((type_name->count == 3 && memcmp(type_name->c_str, "F32", 3) == 0))  return &ffi_type_float;
    if ((type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0)) return &ffi_type_uint8;
    // Struct type: look up def and build ffi_type
    if (Map_has(&ffi_struct_defs, type_name)) {
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
    if ((ftype->count == 5 && memcmp(ftype->c_str, "USize", 5) == 0)) return &ffi_type_uint32;
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
        { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"FFITypePtrBox", .count = 13, .cap = CAP_LIT}, &(USize){sizeof(FFITypePtrBox)}); ffi_type_cache = *_vp; free(_vp); }
        ffi_type_cache_inited = 1;
    }
    // Count instance fields
    Expr *body = Expr_child(struct_def, &(USize){(USize)(0)});
    U32 nfields = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(USize){(USize)(i)});
        if (f->data.tag == NodeType_TAG_Decl && !f->data.data.Decl.is_namespace) nfields++;
    }
    // Build elements array (NULL-terminated)
    ffi_type **elements = malloc(sizeof(ffi_type *) * (nfields + 1));
    U32 idx = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(USize){(USize)(i)});
        if (f->data.tag == NodeType_TAG_Decl && !f->data.data.Decl.is_namespace)
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
    { FFITypePtrBox *_p = malloc(sizeof(FFITypePtrBox)); _p->ptr = (FFIType *)st; Vec_push(&ffi_type_cache, _p); }
    return st;
}

// === Handler macros ===

// === Remaining handlers (name mismatch or local ext_func — can't use auto-FFI) ===

// === Print handlers ===

// === Misc handlers ===

Bool h_free(Scope *s, Expr *e, Value *r) {
    if (Expr_child(e, &(USize){(USize)(1)})->data.tag != NodeType_TAG_Ident) {
        Value val = eval_expr(s, Expr_child(e, &(USize){(USize)(1)}));
        void *ptr = val.tag == Value_TAG_Ptr ? val.data.Ptr : val_to_ptr(&val);
        if (ptr) free(ptr);
        *r = val_none();
        return 1;
    }
    Cell *cell = scope_get(s, &Expr_child(e, &(USize){(USize)(1)})->data.data.Ident);
    if (cell->val.tag == Value_TAG_Struct) {
        if (!cell->val.data.Struct.borrowed)
            free(cell->val.data.Struct.data);
    } else if (cell->val.tag == Value_TAG_Enum) {
        free(cell->val.data.Enum.data);
    } else if (cell->val.tag == Value_TAG_Ptr) {
        free(cell->val.data.Ptr);
    }
    cell->val = val_none();
    *r = val_none();
    return 1;
}

// === Dynamic dispatch handler ===

// Shared helper for all dyn_call variants
static Bool h_dyn_call(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(USize){(USize)(1)}));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    Value method_val = eval_expr(s, Expr_child(e, &(USize){(USize)(2)}));
    Str _mn = str_view(method_val);
    Str *method = &_mn;

    Expr type_ident = {0};
    type_ident.data.tag = NodeType_TAG_Ident;
    type_ident.data.data.Ident = *type_name;
    type_ident.struct_name = *type_name;
    type_ident.line = e->line;
    type_ident.col = e->col;

    Expr field_access = {0};
    field_access.data.tag = NodeType_TAG_FieldAccess;
    field_access.data.data.FieldAccess = *method;
    field_access.is_ns_field = 1;
    field_access.line = e->line;
    field_access.col = e->col;
    field_access.children = (Vec){.data = malloc(sizeof(Expr)), .cap = 1, .elem_size = sizeof(Expr)};
    { Expr *_p = malloc(sizeof(Expr)); *_p = type_ident; Vec_push(&field_access.children, _p); }

    Expr fake_call = {0};
    fake_call.data.tag = NodeType_TAG_FCall;
    fake_call.line = e->line;
    fake_call.col = e->col;
    fake_call.children = (Vec){.data = malloc(sizeof(Expr)), .cap = 1, .elem_size = sizeof(Expr)};
    { Expr *_p = malloc(sizeof(Expr)); *_p = field_access; Vec_push(&fake_call.children, _p); }
    I32 nargs = (I32)atol((char *)Expr_child(e, &(USize){(USize)(3)})->data.data.Ident.c_str);
    // Skip child 3 (arity literal), actual args start at child 4.
    for (I32 ai = 0; ai < nargs; ai++) {
        Expr *arg = Expr_child(e, &(USize){(USize)(ai + 4)});
        Vec_push(&fake_call.children, Expr_clone(arg));
    }

    *r = eval_call(s, &fake_call);

    Vec_delete(&fake_call.children, &(Bool){0});
    Vec_delete(&field_access.children, &(Bool){0});
    return 1;
}

// === Collection builtin handlers ===

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
    type_ident.data.tag = NodeType_TAG_Ident;
    type_ident.data.data.Ident = *type_name;
    type_ident.struct_name = *type_name;
    type_ident.line = src->line; type_ident.col = src->col;
    type_ident.path = src->path;

    Expr field_access = {0};
    field_access.data.tag = NodeType_TAG_FieldAccess;
    field_access.data.data.FieldAccess = (Str){.c_str = (U8*)"size", .count = 4, .cap = CAP_LIT};
    field_access.is_ns_field = 1;
    field_access.line = src->line; field_access.col = src->col;
    field_access.path = src->path;
    field_access.children = (Vec){.data = malloc(sizeof(Expr)), .cap = 1, .elem_size = sizeof(Expr)};
    { Expr *_p = malloc(sizeof(Expr)); *_p = type_ident; Vec_push(&field_access.children, _p); }

    Expr fake_call = {0};
    fake_call.data.tag = NodeType_TAG_FCall;
    fake_call.line = src->line; fake_call.col = src->col;
    fake_call.path = src->path;
    fake_call.children = (Vec){.data = malloc(sizeof(Expr)), .cap = 1, .elem_size = sizeof(Expr)};
    { Expr *_p = malloc(sizeof(Expr)); *_p = field_access; Vec_push(&fake_call.children, _p); }


    Value result = eval_call(s, &fake_call);
    Vec_delete(&fake_call.children, &(Bool){0});
    Vec_delete(&field_access.children, &(Bool){0});
    { U64 *_hp = value_to_u64(&result); I32 out = (I32)*_hp; free(_hp); return out; }
}

// array("I64", 1, 2, 3)
static Bool h_array(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(USize){(USize)(1)}));
    Str _tn = str_view(type_name_val);
    Str *type_name = &_tn;
    U32 count = e->children.count - 2;
    I32 elem_size = get_elem_size(s, type_name, e);

    // Allocate array data
    void *data = malloc(count * elem_size);
    memset(data, 0, count * elem_size);

    // Evaluate each element and copy into data buffer
    for (U32 i = 0; i < count; i++) {
        Value elem = eval_expr(s, Expr_child(e, &(USize){(USize)(i + 2)}));
        void *src = elem.tag == Value_TAG_Ptr ? elem.data.Ptr : val_to_ptr(&elem);
        if (src) {
            if (elem.tag == Value_TAG_Struct && (elem.data.Struct.struct_name->count == 3 && memcmp(elem.data.Struct.struct_name->c_str, "Str", 3) == 0)) {
                // Deep-copy Str: copy flat bytes then strndup the data pointer
                memcpy((char *)data + i * elem_size, src, elem_size);
                char **dp = (char **)((char *)data + i * elem_size);
                USize slen = *(USize *)((char *)data + i * elem_size + sizeof(U8 *));
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
    si->data = calloc(1, cached_array_def->data.data.StructDef.total_struct_size);
    Str fn_data = {.c_str = (U8 *)"data", .count = 4};
    Str fn_cap = {.c_str = (U8 *)"cap", .count = 3};
    Str fn_esz = {.c_str = (U8 *)"elem_size", .count = 9};
    Str fn_et = {.c_str = (U8 *)"elem_type", .count = 9};
    write_field(si, find_field_decl(cached_array_def, &fn_data), (Value){.tag = Value_TAG_Ptr, .data.Ptr = data});
    write_field(si, find_field_decl(cached_array_def, &fn_cap), val_u32(count));
    write_field(si, find_field_decl(cached_array_def, &fn_esz), val_u32((U32)elem_size));
    write_field(si, find_field_decl(cached_array_def, &fn_et), make_str_value((void *)type_name->c_str, type_name->count));
    // Populate FuncPtr fields (#91)
    Str fn_ec = {.c_str = (U8 *)"elem_clone", .count = 10};
    Str fn_ed = {.c_str = (U8 *)"elem_delete", .count = 11};
    Value *clone_fn = ns_get(type_name, &(Str){.c_str = (U8 *)"clone", .count = 5});
    Value *delete_fn = ns_get(type_name, &(Str){.c_str = (U8 *)"delete", .count = 6});
    if (clone_fn) write_field(si, find_field_decl(cached_array_def, &fn_ec), *clone_fn);
    if (delete_fn) write_field(si, find_field_decl(cached_array_def, &fn_ed), *delete_fn);

    r->tag = Value_TAG_Struct;
    r->data.Struct = *si; free(si);
    return 1;
}

// vec("I64", 1, 2, 3)
static Bool h_vec(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, Expr_child(e, &(USize){(USize)(1)}));
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
        Value elem = eval_expr(s, Expr_child(e, &(USize){(USize)(i + 2)}));
        void *src = elem.tag == Value_TAG_Ptr ? elem.data.Ptr : val_to_ptr(&elem);
        if (src) {
            if (elem.tag == Value_TAG_Struct && (elem.data.Struct.struct_name->count == 3 && memcmp(elem.data.Struct.struct_name->c_str, "Str", 3) == 0)) {
                memcpy((char *)data + i * elem_size, src, elem_size);
                char **dp = (char **)((char *)data + i * elem_size);
                USize slen = *(USize *)((char *)data + i * elem_size + sizeof(U8 *));
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
    si->data = calloc(1, cached_vec_def->data.data.StructDef.total_struct_size);
    Str fn_data = {.c_str = (U8 *)"data", .count = 4};
    Str fn_count = {.c_str = (U8 *)"count", .count = 5};
    Str fn_cap = {.c_str = (U8 *)"cap", .count = 3};
    Str fn_esz = {.c_str = (U8 *)"elem_size", .count = 9};
    Str fn_et = {.c_str = (U8 *)"elem_type", .count = 9};
    write_field(si, find_field_decl(cached_vec_def, &fn_data), (Value){.tag = Value_TAG_Ptr, .data.Ptr = data});
    write_field(si, find_field_decl(cached_vec_def, &fn_count), val_u32(count));
    write_field(si, find_field_decl(cached_vec_def, &fn_cap), val_u32(cap));
    write_field(si, find_field_decl(cached_vec_def, &fn_esz), val_u32((U32)elem_size));
    write_field(si, find_field_decl(cached_vec_def, &fn_et), make_str_value((void *)type_name->c_str, type_name->count));
    // Populate FuncPtr fields (#91)
    Str fn_ec = {.c_str = (U8 *)"elem_clone", .count = 10};
    Str fn_ed = {.c_str = (U8 *)"elem_delete", .count = 11};
    Value *clone_fn = ns_get(type_name, &(Str){.c_str = (U8 *)"clone", .count = 5});
    Value *delete_fn = ns_get(type_name, &(Str){.c_str = (U8 *)"delete", .count = 6});
    if (clone_fn) write_field(si, find_field_decl(cached_vec_def, &fn_ec), *clone_fn);
    if (delete_fn) write_field(si, find_field_decl(cached_vec_def, &fn_ed), *delete_fn);

    r->tag = Value_TAG_Struct;
    r->data.Struct = *si; free(si);
    return 1;
}

// === Pointer primitive handlers ===

static Bool h_ptr_add(Scope *s, Expr *e, Value *r) {
    Value buf = eval_expr(s, Expr_child(e, &(USize){(USize)(1)}));
    Value offset = eval_expr(s, Expr_child(e, &(USize){(USize)(2)}));
    void *base = buf.tag == Value_TAG_Ptr ? buf.data.Ptr : val_to_ptr(&buf);
    { U64 *_hp = value_to_u64(&offset); *r = (Value){.tag = Value_TAG_Ptr, .data.Ptr = (char *)base + *_hp}; free(_hp); }
    return 1;
}


// === System primitive handlers ===

// === Dispatch init ===

static void dispatch_init(void) {
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(DispatchFn)}); dispatch_map = *_mp; free(_mp); }

    #define REG(n, fn) do { Str *k = Str_clone(&(Str){.c_str = (U8*)(n), .count = (U64)strlen((const char*)(n)), .cap = CAP_VIEW}); DispatchFn f = fn; \
        Str *_k = malloc(sizeof(Str)); *_k = (Str){k->c_str, k->count, CAP_VIEW}; \
        DispatchFn *_v = malloc(sizeof(DispatchFn)); *_v = f; \
        Map_set(&dispatch_map, _k, _v); } while(0)

    // Print
    REG("print_single", h_print_single);
    REG("print_flush", h_print_flush);

    // Bool standalone
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
    REG("dyn_fn", h_dyn_fn);

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

static Bool ext_dispatch_builtin(Str *name, Scope *scope, Expr *e, Value *result) {
    if (Map_has(&dispatch_map, name)) {
        DispatchFn *fn = Map_get(&dispatch_map, name);
        return (*fn)(scope, e, result);
    }
    return 0;
}

static Bool ext_dispatch_ffi(Str *name, Scope *scope, Expr *e, Value *result) {
    if (!ffi_loaded) return 0;
    if (!Map_has(&ffi_map, name)) return 0;

    FFIEntry *fe = Map_get(&ffi_map, name);
    bool *param_shallows = (bool *)fe->param_shallows;
    ffi_type **arg_types = (ffi_type **)fe->arg_types;
    ffi_cif *cif = (ffi_cif *)fe->cif;
    U32 nargs = e->children.count - 1;
    void *args[nargs > 0 ? nargs : 1];
    void *arg_ptrs[nargs > 0 ? nargs : 1];
    for (U32 i = 0; i < nargs; i++) {
        Value v = eval_expr(scope, Expr_child(e, &(USize){(USize)(i + 1)}));
        if (param_shallows && i < (U32)fe->nparam && param_shallows[i]) {
            // Shallow: store dereferenced value directly for ffi
            if (v.tag == Value_TAG_Struct) {
                // Struct by value: point arg_ptrs directly at struct data
                arg_ptrs[i] = v.data.Struct.data;
                continue;
            }
            if (arg_types[i] == &ffi_type_sint64) {
                I64 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(I64 *)v.data.Ptr;
                else { I64 *_hp = value_to_i64(&v); tmp = *_hp; free(_hp); }
                *(I64 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_uint8) {
                U8 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(U8 *)v.data.Ptr;
                else { U64 *_hp = value_to_u64(&v); tmp = (U8)*_hp; free(_hp); }
                *(U8 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_sint16) {
                I16 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(I16 *)v.data.Ptr;
                else { I64 *_hp = value_to_i64(&v); tmp = (I16)*_hp; free(_hp); }
                *(I16 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_sint32) {
                I32 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(I32 *)v.data.Ptr;
                else { I64 *_hp = value_to_i64(&v); tmp = (I32)*_hp; free(_hp); }
                *(I32 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_uint32) {
                U32 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(U32 *)v.data.Ptr;
                else { U64 *_hp = value_to_u64(&v); tmp = (U32)*_hp; free(_hp); }
                *(U32 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_uint64) {
                U64 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(U64 *)v.data.Ptr;
                else { U64 *_hp = value_to_u64(&v); tmp = *_hp; free(_hp); }
                *(U64 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_float) {
                F32 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(F32 *)v.data.Ptr;
                else { F32 *_hp = value_to_f32(&v); tmp = *_hp; free(_hp); }
                *(F32 *)&args[i] = tmp;
            } else {
                args[i] = v.data.Ptr;
            }
        } else {
            // Deep: pass heap-allocated pointer (FFI callee may free it)
            switch (v.tag) {
                case Value_TAG_Int:    { I64 *p = malloc(sizeof(I64)); *p = v.data.Int; args[i] = p; break; }
                case Value_TAG_Byte:   { U8 *p = malloc(sizeof(U8)); *p = v.data.Byte; args[i] = p; break; }
                case Value_TAG_Short:  { I16 *p = malloc(sizeof(I16)); *p = v.data.Short; args[i] = p; break; }
                case Value_TAG_Int32:  { I32 *p = malloc(sizeof(I32)); *p = v.data.Int32; args[i] = p; break; }
                case Value_TAG_Uint32: { U32 *p = malloc(sizeof(U32)); *p = v.data.Uint32; args[i] = p; break; }
                case Value_TAG_Uint64: { U64 *p = malloc(sizeof(U64)); *p = v.data.Uint64; args[i] = p; break; }
                case Value_TAG_Float:  { F32 *p = malloc(sizeof(F32)); *p = v.data.Float; args[i] = p; break; }
                case Value_TAG_Boolean: { Bool *p = malloc(sizeof(Bool)); *p = v.data.Boolean; args[i] = p; break; }
                case Value_TAG_Ptr:    args[i] = v.data.Ptr; break;
                case Value_TAG_Struct: args[i] = v.data.Struct.data; break;
                case Value_TAG_Enum:  args[i] = v.data.Enum.data; break;
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
        cif->rtype->type == FFI_TYPE_STRUCT &&
        Map_has(&ffi_struct_defs, fe->return_type))
        ret_sdef = Map_get(&ffi_struct_defs, fe->return_type);
    union {
        void *ptr;
        I64 i64;
        U64 u64;
        I32 i32;
        U32 u32;
        I16 i16;
        U8 u8;
        F32 f32;
        Bool boolean;
    } raw = {0};
    void *ret_buf = NULL;
    if (ret_sdef) {
        // Struct return: allocate buffer of struct size
        ret_buf = malloc((*ret_sdef)->data.data.StructDef.total_struct_size);
        ffi_call(cif, FFI_FN(fe->fn), ret_buf, nargs > 0 ? arg_ptrs : NULL);
    } else {
        ffi_call(cif, FFI_FN(fe->fn), &raw, nargs > 0 ? arg_ptrs : NULL);
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
        result->tag = Value_TAG_Struct;
        result->data.Struct = *inst; free(inst);
    } else if (fe->return_is_shallow) {
        // Shallow return: C function returned a primitive by value.
        if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I64", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Int, .data.Int = raw.i64};
        } else if ((fe->return_type->count == 2 && memcmp(fe->return_type->c_str, "U8", 2) == 0)) {
            *result = (Value){.tag = Value_TAG_Byte, .data.Byte = raw.u8};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I16", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Short, .data.Short = raw.i16};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I32", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Int32, .data.Int32 = raw.i32};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U32", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = raw.u32};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U64", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Uint64, .data.Uint64 = raw.u64};
        } else if ((fe->return_type->count == 5 && memcmp(fe->return_type->c_str, "USize", 5) == 0)) {
            *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = raw.u32};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "F32", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Float, .data.Float = raw.f32};
        } else if ((fe->return_type->count == 4 && memcmp(fe->return_type->c_str, "Bool", 4) == 0)) {
            *result = (Value){.tag = Value_TAG_Boolean, .data.Boolean = raw.boolean};
        } else {
            *result = val_none();
        }
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "Str", 3) == 0)) {
        ExtStr *sp = (ExtStr *)raw.ptr;
        *result = make_str_value_own((char *)sp->data, sp->count);
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I64", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Int, .data.Int = *(I64 *)raw.ptr};
    } else if ((fe->return_type->count == 2 && memcmp(fe->return_type->c_str, "U8", 2) == 0)) {
        *result = (Value){.tag = Value_TAG_Byte, .data.Byte = *(U8 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I16", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Short, .data.Short = *(I16 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I32", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Int32, .data.Int32 = *(I32 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U32", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = *(U32 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U64", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Uint64, .data.Uint64 = *(U64 *)raw.ptr};
    } else if ((fe->return_type->count == 5 && memcmp(fe->return_type->c_str, "USize", 5) == 0)) {
        *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = *(U32 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "F32", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Float, .data.Float = *(F32 *)raw.ptr};
    } else if ((fe->return_type->count == 4 && memcmp(fe->return_type->c_str, "Bool", 4) == 0)) {
        *result = (Value){.tag = Value_TAG_Boolean, .data.Boolean = *(Bool *)raw.ptr};
    } else if ((fe->return_type->count == 7 && memcmp(fe->return_type->c_str, "Dynamic", 7) == 0)) {
        *result = (Value){.tag = Value_TAG_Ptr, .data.Ptr = raw.ptr};
    } else {
        // Struct return -- look up struct def by return type name
        if (Map_has(&ffi_struct_defs, fe->return_type)) {
            Expr **sdef = Map_get(&ffi_struct_defs, fe->return_type);
            StructInstance *inst = malloc(sizeof(StructInstance));
            inst->struct_name = fe->return_type;
            inst->struct_def = *sdef;
            inst->borrowed = 0;
            inst->data = raw.ptr;
            result->tag = Value_TAG_Struct;
            result->data.Struct = *inst; free(inst);
        } else {
            *result = val_none();
        }
    }
    return 1;
}

Bool ext_function_dispatch(Str *name, Scope *scope, Expr *e, Value *result) {
    if (!dispatch_inited) dispatch_init();

    if (ext_dispatch_builtin(name, scope, e, result)) return 1;
    return ext_dispatch_ffi(name, scope, e, result);
}

Bool enum_method_dispatch(Str *method, Scope *scope, Expr *enum_def,
                         Str *enum_name, Expr *e,
                         Value *result) {
    Bool hp = enum_has_payloads(enum_def);

    if (hp) {
        // Payload enum: constructor, get_Variant
        I32 ctor_tag = *enum_variant_tag(enum_def, method);
        if (ctor_tag >= 0) {
            Str *vtype = enum_variant_type(enum_def, ctor_tag);
            if (vtype->count > 0) {
                // Payload constructor: eval arg, write into flat buffer
                Value payload = eval_expr(scope, Expr_child(e, &(USize){(USize)(1)}));
                void *pdata = NULL;
                I32 psz = 0;
                switch (payload.tag) {
                case Value_TAG_Int:    pdata = &payload.data.Int; psz = sizeof(I64); break;
                case Value_TAG_Byte:   pdata = &payload.data.Byte; psz = sizeof(U8); break;
                case Value_TAG_Short:  pdata = &payload.data.Short; psz = sizeof(I16); break;
                case Value_TAG_Int32:  pdata = &payload.data.Int32; psz = sizeof(I32); break;
                case Value_TAG_Uint32: pdata = &payload.data.Uint32; psz = sizeof(U32); break;
                case Value_TAG_Uint64: pdata = &payload.data.Uint64; psz = sizeof(U64); break;
                case Value_TAG_Float:  pdata = &payload.data.Float; psz = sizeof(F32); break;
                case Value_TAG_Boolean: pdata = &payload.data.Boolean; psz = sizeof(Bool); break;
                case Value_TAG_Struct: pdata = payload.data.Struct.data;
                    psz = payload.data.Struct.struct_def ? payload.data.Struct.struct_def->data.data.StructDef.total_struct_size : 0;
                    break;
                case Value_TAG_Enum:   pdata = payload.data.Enum.data;
                    psz = payload.data.Enum.data_size;
                    break;
                case Value_TAG_Ptr:    pdata = &payload.data.Ptr; psz = sizeof(void *); break;
                case Value_TAG_Func:   pdata = &payload.data.Func; psz = sizeof(void *); break;
                default: break;
                }
                *result = val_enum_flat(enum_name, enum_def, ctor_tag, pdata, psz);
            } else {
                // No-payload variant of a payload enum (e.g. Token.Eof)
                *result = val_enum_flat(enum_name, enum_def, ctor_tag, NULL, 0);
            }
            return 1;
        }
    }

    return 0;
}

// Register an ext_func/ext_proc in ffi_map
static void ffi_register(Str *name, void *fn, Expr *fdef) {
    U32 np = fdef->data.data.FuncDef.nparam;
    ffi_type **atypes = malloc(sizeof(ffi_type *) * (np > 0 ? np : 1));
    bool *pshallows = NULL;
    bool has_shallow = false;
    for (U32 k = 0; k < np; k++) {
        Param *_pk = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(k)});
        if (PARAM_IS_SHALLOW(_pk)) {
            atypes[k] = shallow_ffi_type(&_pk->ptype);
            has_shallow = true;
        } else {
            atypes[k] = &ffi_type_pointer;
        }
    }
    if (has_shallow) {
        pshallows = malloc(sizeof(bool) * np);
        for (U32 k = 0; k < np; k++)
            pshallows[k] = PARAM_IS_SHALLOW(((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(k)})));
    }
    bool ret_shallow = RETURN_IS_SHALLOW(&fdef->data.data.FuncDef);
    ffi_cif *cif = malloc(sizeof(ffi_cif));
    FFIEntry entry = {
        .fn = (U8 *)fn,
        .return_type = (fdef->data.data.FuncDef.return_type).count > 0 ? (&fdef->data.data.FuncDef.return_type) : NULL,
        .nparam = np,
        .param_shallows = (U8 *)pshallows,
        .return_is_shallow = ret_shallow,
        .cif = (U8 *)cif,
        .arg_types = (U8 *)atypes,
    };
    ffi_type *rtype = &ffi_type_void;
    if (entry.return_type) {
        rtype = ret_shallow ? shallow_ffi_type(entry.return_type) : &ffi_type_pointer;
    }
    ffi_prep_cif(cif, FFI_DEFAULT_ABI, np, rtype, atypes);
    { Str *_k = malloc(sizeof(Str)); *_k = (Str){name->c_str, name->count, CAP_VIEW};
      FFIEntry *_v = malloc(sizeof(FFIEntry)); *_v = entry;
      Map_set(&ffi_map, _k, _v); }
}

static I32 ffi_init_user_so(Str *fwd_path, Str *user_c_path, Str *ext_c_path, Str *link_flags, Str **so_path_out) {
    *so_path_out = NULL;
    if (!user_c_path) return 0;

    Str *ext_dir;
    Str _dot_str = {.c_str = (U8*)".", .count = 1, .cap = CAP_LIT};
    {
        I64 slash = Str_rfind(ext_c_path, &(Str){.c_str = (U8*)"/", .count = 1, .cap = CAP_LIT});
        ext_dir = slash >= 0 ? Str_substr(ext_c_path, &(USize){(USize)(0)}, &(USize){(USize)(slash)}) : &_dot_str;
    }
    char pid_buf[32];
    snprintf(pid_buf, sizeof(pid_buf), "tmp/ffi_%d.so", (int)process_id());
    *so_path_out = Str_clone(&(Str){.c_str = (U8*)(pid_buf), .count = (U64)strlen((const char*)(pid_buf)), .cap = CAP_VIEW});
    system_cmd(&(Str){.c_str = (U8*)"mkdir -p tmp", .count = 12, .cap = CAP_LIT});
    Str *lf = link_flags ? link_flags : &(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
    Str *cmd = Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(Str_concat(
        &(Str){.c_str = (U8*)"cc -Wall -Wextra -shared -fPIC -I", .count = 33, .cap = CAP_LIT}, ext_dir),
        &(Str){.c_str = (U8*)" -include ", .count = 10, .cap = CAP_LIT}), fwd_path),
        &(Str){.c_str = (U8*)" -o ", .count = 4, .cap = CAP_LIT}), *so_path_out),
        &(Str){.c_str = (U8*)" ", .count = 1, .cap = CAP_LIT}), user_c_path), lf);
    int rc = system((const char *)cmd->c_str);
    if (rc != 0) {
        fprintf(stderr, "error: failed to compile FFI library '%s'\n", user_c_path->c_str);
        return 1;
    }
    if (!ffi_open_user_so(*so_path_out)) {
        Str *err = ffi_last_error();
        fprintf(stderr, "error: dlopen failed: %s\n", err->c_str);
        return 1;
    }
    return 0;
}

static void ffi_init_link_libs(Str *link_flags) {
    if (!link_flags) return;
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

static void ffi_init_scan_program(Expr *program) {
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"FFIEntry", .count = 8, .cap = CAP_LIT}, &(USize){sizeof(FFIEntry)}); ffi_map = *_mp; free(_mp); }
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != NodeType_TAG_Decl || stmt->children.count == 0) continue;

        // Top-level ext_func/ext_proc
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_FuncDef) {
            Expr *fdef = Expr_child(stmt, &(USize){(USize)(0)});
            FuncType fft = fdef->data.data.FuncDef.func_type;
            if (fft.tag != FuncType_TAG_ExtFunc && fft.tag != FuncType_TAG_ExtProc) continue;

            void *fn = ffi_dlsym(&stmt->data.data.Decl.name);
            if (!fn) continue;
            ffi_register((&stmt->data.data.Decl.name), fn, fdef);
        }

        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == NodeType_TAG_StructDef) {
            Str *sname = &stmt->data.data.Decl.name;
            Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){(USize)(0)});
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = Expr_child(body, &(USize){(USize)(j)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (field->children.count == 0) continue;
                Expr *fdef = Expr_child(field, &(USize){(USize)(0)});
                if (fdef->data.tag != NodeType_TAG_FuncDef) continue;
                FuncType fft = fdef->data.data.FuncDef.func_type;
                if (fft.tag == FuncType_TAG_ExtFunc || fft.tag == FuncType_TAG_ExtProc) {
                    char flat_name[256];
                    snprintf(flat_name, sizeof(flat_name), "%s_%s", sname->c_str, field->data.data.Decl.name.c_str);
                    Str flat_name_str = {.c_str = (U8 *)flat_name, .count = (U64)strlen(flat_name), .cap = CAP_VIEW};
                    void *fn = ffi_dlsym(&flat_name_str);
                    if (fn) {
                        Str *key = Str_clone(&(Str){.c_str = (U8*)(flat_name), .count = (U64)strlen((const char*)(flat_name)), .cap = CAP_VIEW});
                        ffi_register(key, fn, fdef);
                    }
                } else if (fft.tag == FuncType_TAG_Func || fft.tag == FuncType_TAG_Proc) {
                    // Scan function body for nested ext_func/ext_proc declarations
                    Expr *fbody = Expr_child(fdef, &(USize){(USize)(0)});
                    for (U32 k = 0; k < fbody->children.count; k++) {
                        Expr *inner = Expr_child(fbody, &(USize){(USize)(k)});
                        if (inner->data.tag != NodeType_TAG_Decl || inner->children.count == 0) continue;
                        Expr *idef = Expr_child(inner, &(USize){(USize)(0)});
                        if (idef->data.tag != NodeType_TAG_FuncDef) continue;
                        FuncType ift = idef->data.data.FuncDef.func_type;
                        if (ift.tag != FuncType_TAG_ExtFunc && ift.tag != FuncType_TAG_ExtProc) continue;
                        void *fn = ffi_dlsym(&inner->data.data.Decl.name);
                        if (fn) ffi_register((&inner->data.data.Decl.name), fn, idef);
                    }
                }
            }
        }
    }
}

I32 ffi_init(Expr *program, Str *fwd_path, Str *user_c_path, Str *ext_c_path, Str *link_flags) {
    if (ffi_loaded) ffi_cleanup();  // re-init (e.g. precomp then interpret)
    Str *so_path = NULL;

    if (ffi_init_user_so(fwd_path, user_c_path, ext_c_path, link_flags, &so_path) != 0)
        return 1;

    ffi_init_link_libs(link_flags);
    ffi_init_struct_defs(program);
    ffi_init_scan_program(program);

    ffi_loaded = 1;
    if (so_path) unlink((const char *)so_path->c_str);
    return 0;
}

void ffi_cleanup(void) {
    ffi_close_user_so();
    if (ffi_loaded) {
        for (U32 i = 0; i < ffi_map.count; i++) {
            FFIEntry *fe = (FFIEntry *)((char *)ffi_map.val_data + (i * ffi_map.val_size));
            free((void *)fe->param_shallows);
            free((void *)fe->arg_types);
            free((void *)fe->cif);
        }
        Map_delete(&ffi_map, &(Bool){0});
        Map_delete(&ffi_struct_defs, &(Bool){0});
        ffi_loaded = 0;
    }
    if (ffi_type_cache_inited) {
        for (U32 i = 0; i < ffi_type_cache.count; i++) {
            FFITypePtrBox *box = Vec_get(&ffi_type_cache, &(USize){(USize)(i)});
            ffi_type *t = (ffi_type *)box->ptr;
            free(t->elements);
            free(t);
        }
        Vec_delete(&ffi_type_cache, &(Bool){0});
        ffi_type_cache_inited = 0;
    }
}
