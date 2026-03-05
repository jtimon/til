#include "dispatch.h"
#include "ccore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

typedef int (*DispatchFn)(Scope *, Expr *, const char *, Value *);

// --- Dispatch state ---
static Map dispatch_map;
static int dispatch_inited;

// --- FFI state ---
typedef struct {
    void *fn;           // dlsym'd function pointer
    Str *return_type;   // NULL for proc (void return)
    int nparam;
} FFIEntry;

static Map ffi_map;          // name -> FFIEntry
static void *ffi_handle;     // dlopen handle
static int ffi_loaded;

// === Handler macros ===

// 2-arg handler: eval both args, call cfn(xa, xb), wrap result
#define H2(hname, cfn, xa, xb, w) \
static int h_##hname(Scope *s, Expr *e, const char *p, Value *r) { \
    Value a = eval_expr(s, expr_child(e, 1), p); \
    Value b = eval_expr(s, expr_child(e, 2), p); \
    *r = w(cfn(xa, xb)); return 1; }

// 1-arg handler: eval one arg, call cfn(xv), wrap result
#define H1(hname, cfn, xv, w) \
static int h_##hname(Scope *s, Expr *e, const char *p, Value *r) { \
    Value v = eval_expr(s, expr_child(e, 1), p); \
    *r = w(cfn(xv)); return 1; }

// Delete handler: check VAL_NONE, eval call_free flag, conditionally delete
#define HDEL(hname, dfn, xv) \
static int h_##hname(Scope *s, Expr *e, const char *p, Value *r) { \
    Value v = eval_expr(s, expr_child(e, 1), p); \
    if (v.type == VAL_NONE) { *r = val_none(); return 1; } \
    Value cf = eval_expr(s, expr_child(e, 2), p); \
    if (*cf.boolean) dfn(xv); \
    *r = val_none(); return 1; }

// Clone handler: eval one arg, copy raw value
#define HCLONE(hname, xv, w) \
static int h_##hname(Scope *s, Expr *e, const char *p, Value *r) { \
    Value v = eval_expr(s, expr_child(e, 1), p); \
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
H2(I64_lt, I64_lt, *a.i64, *b.i64, val_bool)
H2(I64_gt, I64_gt, *a.i64, *b.i64, val_bool)
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
H2(U8_lt, U8_lt, *a.u8, *b.u8, val_bool)
H2(U8_gt, U8_gt, *a.u8, *b.u8, val_bool)
H1(U8_to_i64, U8_to_i64, *v.u8, val_i64)
HCLONE(U8_clone, *v.u8, val_u8)
HDEL(U8_delete, U8_delete, v.u8)

static int h_U8_from_i64(Scope *s, Expr *e, const char *p, Value *r) {
    Value v = eval_expr(s, expr_child(e, 1), p);
    *r = val_u8(U8_from_i64(*v.i64)); return 1;
}

// === Bool handlers ===
H2(Bool_and, Bool_and, *a.boolean, *b.boolean, val_bool)
H2(Bool_or,  Bool_or,  *a.boolean, *b.boolean, val_bool)
H1(Bool_not, Bool_not, *v.boolean, val_bool)
HCLONE(Bool_clone, *v.boolean, val_bool)
HDEL(Bool_delete, Bool_delete, v.boolean)

static void *val_to_ptr(Value v);

// === Variadic handlers ===

static int h_println(Scope *s, Expr *e, const char *p, Value *r) {
    for (int i = 1; i < e->children.count; i++) {
        Value arg = eval_expr(s, expr_child(e, i), p);
        fwrite(arg.str->c_str, 1, arg.str->cap, stdout);
    }
    putchar('\n');
    *r = val_none(); return 1;
}

static int h_print(Scope *s, Expr *e, const char *p, Value *r) {
    for (int i = 1; i < e->children.count; i++) {
        Value arg = eval_expr(s, expr_child(e, i), p);
        fwrite(arg.str->c_str, 1, arg.str->cap, stdout);
    }
    *r = val_none(); return 1;
}

static int h_format(Scope *s, Expr *e, const char *p, Value *r) {
    int nargs = e->children.count - 1;
    Str *strs[64];
    int total = 0;
    for (int i = 0; i < nargs; i++) {
        Value v = eval_expr(s, expr_child(e, i + 1), p);
        strs[i] = v.str;
        total += v.str->cap;
    }
    char *buf = malloc(total);
    int off = 0;
    for (int i = 0; i < nargs; i++) {
        memcpy(buf + off, strs[i]->c_str, strs[i]->cap);
        off += strs[i]->cap;
    }
    Str *out = malloc(sizeof(Str));
    out->c_str = buf;
    out->cap = total;
    *r = val_str(out);
    return 1;
}

// === Misc handlers ===

static int h_exit(Scope *s, Expr *e, const char *p, Value *r) {
    Value a = eval_expr(s, expr_child(e, 1), p);
    til_exit(a.i64);
    *r = val_none(); return 1;
}

static int h_free(Scope *s, Expr *e, const char *p, Value *r) {
    (void)p;
    if (expr_child(e, 1)->type != NODE_IDENT) {
        // Non-identifier argument: evaluate and free the raw pointer
        // (matches codegen: til_free just calls C free on the pointer)
        Value val = eval_expr(s, expr_child(e, 1), p);
        void *ptr = val_to_ptr(val);
        if (ptr) free(ptr);
        *r = val_none();
        return 1;
    }
    Cell *cell = scope_get(s, expr_child(e, 1)->data.str_val);
    if (cell->val.type == VAL_STRUCT && cell->val.instance) {
        til_free(cell->val.instance->field_names);
        til_free(cell->val.instance->field_muts);
        til_free(cell->val.instance->field_values);
        til_free(cell->val.instance);
    } else if (cell->val.type == VAL_ENUM && cell->val.enum_inst) {
        Value payload = cell->val.enum_inst->payload;
        if (payload.type == VAL_I64)  til_free(payload.i64);
        else if (payload.type == VAL_U8)   til_free(payload.u8);
        else if (payload.type == VAL_BOOL) til_free(payload.boolean);
        else if (payload.type == VAL_STR)  Str_delete(payload.str);
        til_free(cell->val.enum_inst);
    } else if (cell->val.type == VAL_I64) {
        til_free(cell->val.i64);
    } else if (cell->val.type == VAL_U8) {
        til_free(cell->val.u8);
    } else if (cell->val.type == VAL_BOOL) {
        til_free(cell->val.boolean);
    } else if (cell->val.type == VAL_STR) {
        free(cell->val.str);
    } else if (cell->val.type == VAL_PTR) {
        free(cell->val.ptr);
    }
    cell->val = val_none();
    *r = val_none();
    return 1;
}

// === Dynamic dispatch handler ===

// Shared helper for all dyn_call variants
static int h_dyn_call(Scope *s, Expr *e, const char *p, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e, 1), p);
    Str *type_name = type_name_val.str;
    Value method_val = eval_expr(s, expr_child(e, 2), p);
    Str *method = method_val.str;

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
    for (int i = 3; i < e->children.count; i++) {
        Expr *arg = expr_child(e, i);
        Vec_push(&fake_call.children, &arg);
    }

    Value fn_val = eval_expr(s, &field_access, p);
    if (fn_val.type == VAL_FUNC && fn_val.func->type == NODE_FUNC_DEF) {
        Expr *fdef = fn_val.func;
        int nparam = fdef->data.func_def.nparam;
        int nargs = fake_call.children.count - 1;
        for (int i = nargs; i < nparam; i++) {
            if (fdef->data.func_def.param_defaults &&
                fdef->data.func_def.param_defaults[i]) {
                Expr *def_arg = fdef->data.func_def.param_defaults[i];
                Vec_push(&fake_call.children, &def_arg);
            }
        }
    }

    *r = eval_call(s, &fake_call, p);

    Vec_delete(&fake_call.children);
    Vec_delete(&field_access.children);
    return 1;
}

// === Pointer primitive handlers ===

// Extract raw void* from any Value type
static void *val_to_ptr(Value v) {
    switch (v.type) {
        case VAL_PTR:    return v.ptr;
        case VAL_I64:    return v.i64;
        case VAL_U8:     return v.u8;
        case VAL_BOOL:   return v.boolean;
        case VAL_STR:    return v.str;
        case VAL_STRUCT: return v.instance;
        default:         return NULL;
    }
}

static int h_malloc(Scope *s, Expr *e, const char *p, Value *r) {
    Value count = eval_expr(s, expr_child(e, 1), p);
    int nbytes = (int)*count.i64;
    *r = (Value){.type = VAL_PTR, .ptr = calloc(1, nbytes)};
    return 1;
}

static int h_realloc(Scope *s, Expr *e, const char *p, Value *r) {
    Value buf = eval_expr(s, expr_child(e, 1), p);
    Value count = eval_expr(s, expr_child(e, 2), p);
    int nbytes = (int)*count.i64;
    *r = (Value){.type = VAL_PTR, .ptr = realloc(buf.ptr, nbytes)};
    return 1;
}

static int h_ptr_add(Scope *s, Expr *e, const char *p, Value *r) {
    Value buf = eval_expr(s, expr_child(e, 1), p);
    Value offset = eval_expr(s, expr_child(e, 2), p);
    *r = (Value){.type = VAL_PTR, .ptr = (char *)buf.ptr + (int)*offset.i64};
    return 1;
}

static int h_memcpy(Scope *s, Expr *e, const char *p, Value *r) {
    Value dest = eval_expr(s, expr_child(e, 1), p);
    Value src = eval_expr(s, expr_child(e, 2), p);
    Value len = eval_expr(s, expr_child(e, 3), p);
    memcpy(val_to_ptr(dest), val_to_ptr(src), (size_t)*len.i64);
    *r = val_none();
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

    // Variadic
    REG("println", h_println);
    REG("print", h_print);
    REG("format", h_format);

    // I64
    REG("I64_add", h_I64_add); REG("I64_sub", h_I64_sub);
    REG("I64_mul", h_I64_mul); REG("I64_div", h_I64_div);
    REG("I64_mod", h_I64_mod);
    REG("I64_and", h_I64_and); REG("I64_or", h_I64_or); REG("I64_xor", h_I64_xor);
    REG("I64_eq", h_I64_eq); REG("I64_lt", h_I64_lt); REG("I64_gt", h_I64_gt);
    REG("I64_clone", h_I64_clone);
    REG("I64_delete", h_I64_delete);

    // U8
    REG("U8_add", h_U8_add); REG("U8_sub", h_U8_sub);
    REG("U8_mul", h_U8_mul); REG("U8_div", h_U8_div);
    REG("U8_mod", h_U8_mod);
    REG("U8_and", h_U8_and); REG("U8_or", h_U8_or); REG("U8_xor", h_U8_xor);
    REG("U8_eq", h_U8_eq); REG("U8_lt", h_U8_lt); REG("U8_gt", h_U8_gt);
    REG("U8_to_i64", h_U8_to_i64);
    REG("U8_from_i64", h_U8_from_i64);
    REG("U8_from_i64_ext", h_U8_from_i64);
    REG("U8_clone", h_U8_clone);
    REG("U8_delete", h_U8_delete);

    // Bool
    REG("Bool_and", h_Bool_and); REG("Bool_or", h_Bool_or);
    REG("Bool_not", h_Bool_not);
    REG("Bool_clone", h_Bool_clone);
    REG("Bool_delete", h_Bool_delete);

    // Misc
    REG("exit", h_exit);
    REG("free", h_free);

    // Pointer primitives
    REG("malloc", h_malloc);
    REG("realloc", h_realloc);
    REG("ptr_add", h_ptr_add);
    REG("memcpy", h_memcpy);

    // Dynamic dispatch
    REG("dyn_call1", h_dyn_call);
    REG("dyn_call2", h_dyn_call);
    REG("dyn_call1_ret", h_dyn_call);
    REG("dyn_call2_ret", h_dyn_call);


    #undef REG
    dispatch_inited = 1;
}

// === Main dispatch ===

int ext_function_dispatch(Str *name, Scope *scope, Expr *e, const char *path, Value *result) {
    if (!dispatch_inited) dispatch_init();

    DispatchFn *fn = Map_get(&dispatch_map, &name);
    if (fn) return (*fn)(scope, e, path, result);

    // FFI trampoline
    if (ffi_loaded) {
        FFIEntry *fe = Map_get(&ffi_map, &name);
        if (fe) {
            int nargs = e->children.count - 1;
            void *args[8];
            for (int i = 0; i < nargs; i++) {
                Value v = eval_expr(scope, expr_child(e, i + 1), path);
                switch (v.type) {
                    case VAL_I64:  args[i] = v.i64; break;
                    case VAL_U8:   args[i] = v.u8; break;
                    case VAL_STR:  args[i] = v.str; break;
                    case VAL_BOOL: args[i] = v.boolean; break;
                    case VAL_PTR:  args[i] = v.ptr; break;
                    default:       args[i] = NULL; break;
                }
            }
            void *raw = NULL;
            switch (nargs) {
                case 0: raw = ((void *(*)(void))fe->fn)(); break;
                case 1: raw = ((void *(*)(void *))fe->fn)(args[0]); break;
                case 2: raw = ((void *(*)(void *, void *))fe->fn)(args[0], args[1]); break;
                case 3: raw = ((void *(*)(void *, void *, void *))fe->fn)(args[0], args[1], args[2]); break;
                case 4: raw = ((void *(*)(void *, void *, void *, void *))fe->fn)(args[0], args[1], args[2], args[3]); break;
            }
            if (!fe->return_type) {
                *result = val_none();
            } else if (Str_eq_c(fe->return_type, "Str")) {
                *result = val_str((Str *)raw);
            } else if (Str_eq_c(fe->return_type, "I64")) {
                *result = (Value){.type = VAL_I64, .i64 = (til_I64 *)raw};
            } else if (Str_eq_c(fe->return_type, "U8")) {
                *result = (Value){.type = VAL_U8, .u8 = (til_U8 *)raw};
            } else if (Str_eq_c(fe->return_type, "Bool")) {
                *result = (Value){.type = VAL_BOOL, .boolean = (til_Bool *)raw};
            } else {
                *result = val_none();
            }
            return 1;
        }
    }

    return 0;
}

int enum_method_dispatch(Str *method, Scope *scope, Expr *enum_def,
                         Str *enum_name, Expr *e, const char *path,
                         Value *result) {
    int hp = enum_has_payloads(enum_def);

    if (!hp) {
        // Simple enum: stored as I64
        if (Str_eq_c(method, "eq")) {
            Value a = eval_expr(scope, expr_child(e, 1), path);
            Value b = eval_expr(scope, expr_child(e, 2), path);
            *result = val_bool(*a.i64 == *b.i64);
            return 1;
        }
    } else {
        // Payload enum: constructor, eq, clone, delete, is_Variant, get_Variant
        int ctor_tag = enum_variant_tag(enum_def, method);
        if (ctor_tag >= 0) {
            if (enum_variant_type(enum_def, ctor_tag)) {
                Value payload = eval_expr(scope, expr_child(e, 1), path);
                *result = val_enum(enum_name, ctor_tag, clone_value(payload));
            } else {
                *result = val_enum(enum_name, ctor_tag, val_none());
            }
            return 1;
        }
        if (Str_eq_c(method, "eq")) {
            Value a = eval_expr(scope, expr_child(e, 1), path);
            Value b = eval_expr(scope, expr_child(e, 2), path);
            *result = val_bool(values_equal(a, b));
            return 1;
        }
        if (method->cap > 3 && memcmp(method->c_str, "is_", 3) == 0) {
            Str var_name = {.c_str = method->c_str + 3, .cap = method->cap - 3};
            int tag = enum_variant_tag(enum_def, &var_name);
            Value v = eval_expr(scope, expr_child(e, 1), path);
            if (v.type == VAL_ENUM)
                *result = val_bool(v.enum_inst->tag == tag);
            else
                *result = val_bool((int)*v.i64 == tag);
            return 1;
        }
        if (method->cap > 4 && memcmp(method->c_str, "get_", 4) == 0) {
            Value v = eval_expr(scope, expr_child(e, 1), path);
            *result = clone_value(v.enum_inst->payload);
            return 1;
        }
    }
    return 0;
}

int ffi_init(Expr *program, const char *user_c_path, const char *ext_c_path) {
    // Extract include dir from ext_c_path
    char ext_dir[256];
    const char *last_slash = strrchr(ext_c_path, '/');
    if (last_slash) {
        int dlen = (int)(last_slash - ext_c_path);
        snprintf(ext_dir, sizeof(ext_dir), "%.*s", dlen, ext_c_path);
    } else {
        snprintf(ext_dir, sizeof(ext_dir), ".");
    }

    // Compile user .c to shared library
    char so_path[256];
    snprintf(so_path, sizeof(so_path), "tmp/ffi_%d.so", (int)getpid());
    system("mkdir -p tmp");
    int cmdlen = snprintf(NULL, 0, "cc -shared -fPIC -I%s -o %s %s", ext_dir, so_path, user_c_path);
    char *cmd = malloc(cmdlen + 1);
    snprintf(cmd, cmdlen + 1, "cc -shared -fPIC -I%s -o %s %s", ext_dir, so_path, user_c_path);
    int rc = system(cmd);
    free(cmd);
    if (rc != 0) {
        fprintf(stderr, "error: failed to compile FFI library '%s'\n", user_c_path);
        return 1;
    }

    // dlopen
    ffi_handle = dlopen(so_path, RTLD_NOW);
    if (!ffi_handle) {
        fprintf(stderr, "error: dlopen failed: %s\n", dlerror());
        return 1;
    }

    // Scan program for non-core ext_func/ext_proc, dlsym each
    ffi_map = Map_new(sizeof(Str *), sizeof(FFIEntry), str_ptr_cmp);
    for (int i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->is_core) continue;
        if (stmt->type != NODE_DECL || expr_child(stmt, 0)->type != NODE_FUNC_DEF) continue;
        Expr *fdef = expr_child(stmt, 0);
        FuncType fft = fdef->data.func_def.func_type;
        if (fft != FUNC_EXT_FUNC && fft != FUNC_EXT_PROC) continue;

        char sym_name[256];
        snprintf(sym_name, sizeof(sym_name), "til_%s", stmt->data.decl.name->c_str);
        void *fn = dlsym(ffi_handle, sym_name);
        if (!fn) {
            fprintf(stderr, "error: FFI symbol '%s' not found: %s\n", sym_name, dlerror());
            dlclose(ffi_handle);
            ffi_handle = NULL;
            return 1;
        }
        FFIEntry entry = {
            .fn = fn,
            .return_type = fdef->data.func_def.return_type,
            .nparam = fdef->data.func_def.nparam,
        };
        Map_set(&ffi_map, &stmt->data.decl.name, &entry);
    }

    ffi_loaded = 1;
    // Clean up .so file
    unlink(so_path);
    return 0;
}

void ffi_cleanup(void) {
    if (ffi_handle) {
        dlclose(ffi_handle);
        ffi_handle = NULL;
    }
    if (ffi_loaded) {
        Map_delete(&ffi_map);
        ffi_loaded = 0;
    }
}
