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

typedef int (*DispatchFn)(Scope *, Expr *, Value *);

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
static int h_##hname(Scope *s, Expr *e, Value *r) { \
    Value a = eval_expr(s, expr_child(e,1)); \
    Value b = eval_expr(s, expr_child(e,2)); \
    *r = w(cfn(xa, xb)); return 1; }

// 1-arg handler: eval one arg, call cfn(xv), wrap result
#define H1(hname, cfn, xv, w) \
static int h_##hname(Scope *s, Expr *e, Value *r) { \
    Value v = eval_expr(s, expr_child(e,1)); \
    *r = w(cfn(xv)); return 1; }

// Delete handler: check VAL_NONE, eval call_free flag, conditionally delete
#define HDEL(hname, dfn, xv) \
static int h_##hname(Scope *s, Expr *e, Value *r) { \
    Value v = eval_expr(s, expr_child(e,1)); \
    if (v.type == VAL_NONE) { *r = val_none(); return 1; } \
    Value cf = eval_expr(s, expr_child(e,2)); \
    if (*cf.boolean) dfn(xv); \
    *r = val_none(); return 1; }

// Clone handler: eval one arg, copy raw value
#define HCLONE(hname, xv, w) \
static int h_##hname(Scope *s, Expr *e, Value *r) { \
    Value v = eval_expr(s, expr_child(e,1)); \
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

static int h_U8_from_i64(Scope *s, Expr *e, Value *r) {
    Value v = eval_expr(s, expr_child(e,1));
    *r = val_u8(U8_from_i64(*v.i64)); return 1;
}

// === Bool handlers ===
H2(Bool_eq,  Bool_eq,  *a.boolean, *b.boolean, val_bool)
H2(Bool_and, Bool_and, *a.boolean, *b.boolean, val_bool)
H2(Bool_or,  Bool_or,  *a.boolean, *b.boolean, val_bool)
H1(Bool_not, Bool_not, *v.boolean, val_bool)
HCLONE(Bool_clone, *v.boolean, val_bool)
HDEL(Bool_delete, Bool_delete, v.boolean)

static void *val_to_ptr(Value v);

// === Variadic handlers ===

static int h_println(Scope *s, Expr *e, Value *r) {
    for (int i = 1; i < e->children.count; i++) {
        Value arg = eval_expr(s, expr_child(e,i));
        fwrite(arg.str->c_str, 1, arg.str->cap, stdout);
    }
    putchar('\n');
    *r = val_none(); return 1;
}

static int h_print(Scope *s, Expr *e, Value *r) {
    for (int i = 1; i < e->children.count; i++) {
        Value arg = eval_expr(s, expr_child(e,i));
        fwrite(arg.str->c_str, 1, arg.str->cap, stdout);
    }
    *r = val_none(); return 1;
}

static int h_format(Scope *s, Expr *e, Value *r) {
    int nargs = e->children.count - 1;
    Str *strs[64];
    int total = 0;
    for (int i = 0; i < nargs; i++) {
        Value v = eval_expr(s, expr_child(e,i + 1));
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

static int h_exit(Scope *s, Expr *e, Value *r) {
    Value a = eval_expr(s, expr_child(e,1));
    til_exit(a.i64);
    *r = val_none(); return 1;
}

static int h_free(Scope *s, Expr *e, Value *r) {
    if (expr_child(e, 1)->type != NODE_IDENT) {
        // Non-identifier argument: evaluate and free the raw pointer
        // (matches codegen: til_free just calls C free on the pointer)
        Value val = eval_expr(s, expr_child(e,1));
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
static int h_dyn_call(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e,1));
    Str *type_name = type_name_val.str;
    Value method_val = eval_expr(s, expr_child(e,2));
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

    Value fn_val = eval_expr(s, &field_access);
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

    *r = eval_call(s, &fake_call);

    Vec_delete(&fake_call.children);
    Vec_delete(&field_access.children);
    return 1;
}

// dyn_has_method(type_name, "method") → Bool
static int h_dyn_has_method(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e,1));
    Value method_val = eval_expr(s, expr_child(e,2));
    Str *type_name = type_name_val.str;
    Str *method = method_val.str;
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
        case VAL_BOOL:   return v.boolean;
        case VAL_STR:    return v.str;
        case VAL_STRUCT: return v.instance;
        case VAL_PTR:    return v.ptr;
        default:         return NULL;
    }
}

// Get element size via dyn_call to Type.size()
// Workaround: the scavenger may remove Type.size() if not directly referenced
// in user code (see issue #15). Users must reference Type.size() explicitly.
static int get_elem_size(Scope *s, Str *type_name, Expr *src) {
    Value *size_fn = ns_get(type_name, Str_new("size"));
    if (!size_fn) {
        fprintf(stderr, "%s:%d:%d: error: array/vec: type '%s' has no size() method "
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
    return (int)*result.i64;
}

// array("I64", 1, 2, 3)
static int h_array(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e, 1));
    Str *type_name = type_name_val.str;
    int count = e->children.count - 2;
    int elem_size = get_elem_size(s, type_name, e);

    // Allocate array data
    void *data = malloc(count * elem_size);
    memset(data, 0, count * elem_size);

    // Evaluate each element and copy into data buffer
    for (int i = 0; i < count; i++) {
        Value elem = eval_expr(s, expr_child(e, i + 2));
        void *src = val_raw_ptr(elem);
        if (src) {
            if (elem.type == VAL_STR) {
                // Deep copy: clone the Str so the array owns its own data
                Str *cloned = Str_clone(elem.str);
                memcpy((char *)data + i * elem_size, cloned, elem_size);
                free(cloned); // free the Str shell, array buffer owns the contents
            } else {
                memcpy((char *)data + i * elem_size, src, elem_size);
            }
        }
    }

    // Build Array struct: {data, cap, elem_size, elem_type}
    StructInstance *si = malloc(sizeof(StructInstance));
    si->struct_name = Str_new("Array");
    si->nfields = 4;
    si->field_names = malloc(4 * sizeof(Str *));
    si->field_muts = calloc(4, sizeof(int));
    si->field_muts[0] = 1; // data is mut
    si->field_values = malloc(4 * sizeof(Value));
    si->field_names[0] = Str_new("data");
    si->field_names[1] = Str_new("cap");
    si->field_names[2] = Str_new("elem_size");
    si->field_names[3] = Str_new("elem_type");
    si->field_values[0] = (Value){.type = VAL_PTR, .ptr = data};
    si->field_values[1] = val_i64(count);
    si->field_values[2] = val_i64(elem_size);
    si->field_values[3] = val_str(Str_clone(type_name));

    r->type = VAL_STRUCT;
    r->instance = si;
    return 1;
}

// vec("I64", 1, 2, 3)
static int h_vec(Scope *s, Expr *e, Value *r) {
    Value type_name_val = eval_expr(s, expr_child(e, 1));
    Str *type_name = type_name_val.str;
    int count = e->children.count - 2;
    int elem_size = get_elem_size(s, type_name, e);

    // Allocate vec data with exact capacity
    int cap = count > 0 ? count : 1;
    void *data = malloc(cap * elem_size);
    memset(data, 0, cap * elem_size);

    // Evaluate each element and copy into data buffer
    for (int i = 0; i < count; i++) {
        Value elem = eval_expr(s, expr_child(e, i + 2));
        void *src = val_raw_ptr(elem);
        if (src) {
            if (elem.type == VAL_STR) {
                Str *cloned = Str_clone(elem.str);
                memcpy((char *)data + i * elem_size, cloned, elem_size);
                free(cloned);
            } else {
                memcpy((char *)data + i * elem_size, src, elem_size);
            }
        }
    }

    // Build Vec struct: {data, count, cap, elem_size, elem_type}
    StructInstance *si = malloc(sizeof(StructInstance));
    si->struct_name = Str_new("Vec");
    si->nfields = 5;
    si->field_names = malloc(5 * sizeof(Str *));
    si->field_muts = calloc(5, sizeof(int));
    si->field_muts[0] = 1; // data is mut
    si->field_muts[1] = 1; // count is mut
    si->field_muts[2] = 1; // cap is mut
    si->field_values = malloc(5 * sizeof(Value));
    si->field_names[0] = Str_new("data");
    si->field_names[1] = Str_new("count");
    si->field_names[2] = Str_new("cap");
    si->field_names[3] = Str_new("elem_size");
    si->field_names[4] = Str_new("elem_type");
    si->field_values[0] = (Value){.type = VAL_PTR, .ptr = data};
    si->field_values[1] = val_i64(count);
    si->field_values[2] = val_i64(cap);
    si->field_values[3] = val_i64(elem_size);
    si->field_values[4] = val_str(Str_clone(type_name));

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
        case VAL_BOOL:   return v.boolean;
        case VAL_STR:    return v.str;
        case VAL_STRUCT: return v.instance;
        default:         return NULL;
    }
}

static int h_malloc(Scope *s, Expr *e, Value *r) {
    Value count = eval_expr(s, expr_child(e,1));
    int nbytes = (int)*count.i64;
    *r = (Value){.type = VAL_PTR, .ptr = calloc(1, nbytes)};
    return 1;
}

static int h_realloc(Scope *s, Expr *e, Value *r) {
    Value buf = eval_expr(s, expr_child(e,1));
    Value count = eval_expr(s, expr_child(e,2));
    int nbytes = (int)*count.i64;
    *r = (Value){.type = VAL_PTR, .ptr = realloc(buf.ptr, nbytes)};
    return 1;
}

static int h_ptr_add(Scope *s, Expr *e, Value *r) {
    Value buf = eval_expr(s, expr_child(e,1));
    Value offset = eval_expr(s, expr_child(e,2));
    *r = (Value){.type = VAL_PTR, .ptr = (char *)buf.ptr + (int)*offset.i64};
    return 1;
}

static int h_memcpy(Scope *s, Expr *e, Value *r) {
    Value dest = eval_expr(s, expr_child(e,1));
    Value src = eval_expr(s, expr_child(e,2));
    Value len = eval_expr(s, expr_child(e,3));
    memcpy(val_to_ptr(dest), val_to_ptr(src), (size_t)*len.i64);
    *r = val_none();
    return 1;
}

static int h_memmove(Scope *s, Expr *e, Value *r) {
    Value dest = eval_expr(s, expr_child(e,1));
    Value src = eval_expr(s, expr_child(e,2));
    Value len = eval_expr(s, expr_child(e,3));
    memmove(val_to_ptr(dest), val_to_ptr(src), (size_t)*len.i64);
    *r = val_none();
    return 1;
}

// === System primitive handlers ===

static int h_readfile(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, expr_child(e,1));
    FILE *f = fopen(path.str->c_str, "rb");
    if (!f) {
        fprintf(stderr, "readfile: could not open '%.*s'\n", path.str->cap, path.str->c_str);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len);
    fread(buf, 1, len, f);
    fclose(f);
    *r = val_str(Str_new_len(buf, (int)len));
    free(buf);
    return 1;
}

static int h_writefile(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, expr_child(e,1));
    Value content = eval_expr(s, expr_child(e,2));
    FILE *f = fopen(path.str->c_str, "wb");
    if (!f) {
        fprintf(stderr, "writefile: could not open '%.*s'\n", path.str->cap, path.str->c_str);
        exit(1);
    }
    fwrite(content.str->c_str, 1, content.str->cap, f);
    fclose(f);
    *r = val_none();
    return 1;
}

static int h_spawn_cmd(Scope *s, Expr *e, Value *r) {
    Value cmd = eval_expr(s, expr_child(e,1));
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd.str->c_str, NULL);
        _exit(127);
    }
    if (pid < 0) {
        fprintf(stderr, "spawn_cmd: fork failed\n");
        exit(1);
    }
    *r = val_i64((I64)pid);
    return 1;
}

static int h_check_cmd_status(Scope *s, Expr *e, Value *r) {
    Value pidv = eval_expr(s, expr_child(e,1));
    int status;
    pid_t result = waitpid((pid_t)*pidv.i64, &status, WNOHANG);
    if (result == 0) { *r = val_i64(-1); return 1; }
    if (WIFEXITED(status)) { *r = val_i64(WEXITSTATUS(status)); return 1; }
    *r = val_i64(-1);
    return 1;
}

static int h_sleep(Scope *s, Expr *e, Value *r) {
    Value ms = eval_expr(s, expr_child(e,1));
    usleep((useconds_t)(*ms.i64 * 1000));
    *r = val_none();
    return 1;
}

static int h_file_mtime(Scope *s, Expr *e, Value *r) {
    Value path = eval_expr(s, expr_child(e,1));
    struct stat st;
    if (stat(path.str->c_str, &st) != 0) { *r = val_i64(-1); return 1; }
    *r = val_i64((I64)st.st_mtime);
    return 1;
}

static int h_clock_ms(Scope *s, Expr *e, Value *r) {
    (void)s; (void)e;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    *r = val_i64((I64)ts.tv_sec * 1000 + (I64)ts.tv_nsec / 1000000);
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
    REG("Bool_eq", h_Bool_eq);
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
    REG("memmove", h_memmove);

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

    #undef REG
    dispatch_inited = 1;
}

// === Main dispatch ===

int ext_function_dispatch(Str *name, Scope *scope, Expr *e, Value *result) {
    if (!dispatch_inited) dispatch_init();

    DispatchFn *fn = Map_get(&dispatch_map, &name);
    if (fn) return (*fn)(scope, e, result);

    // FFI trampoline
    if (ffi_loaded) {
        FFIEntry *fe = Map_get(&ffi_map, &name);
        if (fe) {
            int nargs = e->children.count - 1;
            void *args[8];
            for (int i = 0; i < nargs; i++) {
                Value v = eval_expr(scope, expr_child(e, i + 1));
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
                         Str *enum_name, Expr *e,
                         Value *result) {
    int hp = enum_has_payloads(enum_def);

    if (!hp) {
        // Simple enum: stored as I64
        if (Str_eq_c(method, "eq")) {
            Value a = eval_expr(scope, expr_child(e, 1));
            Value b = eval_expr(scope, expr_child(e, 2));
            *result = val_bool(*a.i64 == *b.i64);
            return 1;
        }
    } else {
        // Payload enum: constructor, eq, clone, delete, is_Variant, get_Variant
        int ctor_tag = enum_variant_tag(enum_def, method);
        if (ctor_tag >= 0) {
            if (enum_variant_type(enum_def, ctor_tag)) {
                Value payload = eval_expr(scope, expr_child(e, 1));
                *result = val_enum(enum_name, ctor_tag, clone_value(payload));
            } else {
                *result = val_enum(enum_name, ctor_tag, val_none());
            }
            return 1;
        }
        if (Str_eq_c(method, "eq")) {
            Value a = eval_expr(scope, expr_child(e, 1));
            Value b = eval_expr(scope, expr_child(e, 2));
            *result = val_bool(values_equal(a, b));
            return 1;
        }
        if (method->cap > 3 && memcmp(method->c_str, "is_", 3) == 0) {
            Str var_name = {.c_str = method->c_str + 3, .cap = method->cap - 3};
            int tag = enum_variant_tag(enum_def, &var_name);
            Value v = eval_expr(scope, expr_child(e, 1));
            if (v.type == VAL_ENUM)
                *result = val_bool(v.enum_inst->tag == tag);
            else
                *result = val_bool((int)*v.i64 == tag);
            return 1;
        }
        if (method->cap > 4 && memcmp(method->c_str, "get_", 4) == 0) {
            Value v = eval_expr(scope, expr_child(e, 1));
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
        if (stmt->type != NODE_DECL || stmt->children.count == 0) continue;

        // Top-level ext_func/ext_proc
        if (expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
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

        // ext_struct namespace methods
        if (expr_child(stmt, 0)->type == NODE_STRUCT_DEF && expr_child(stmt, 0)->is_ext) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            for (int j = 0; j < body->children.count; j++) {
                Expr *field = expr_child(body, j);
                if (!field->data.decl.is_namespace) continue;
                if (field->children.count == 0) continue;
                Expr *fdef = expr_child(field, 0);
                if (fdef->type != NODE_FUNC_DEF) continue;
                FuncType fft = fdef->data.func_def.func_type;
                if (fft != FUNC_EXT_FUNC && fft != FUNC_EXT_PROC) continue;

                char flat_name[256], sym_name[264];
                snprintf(flat_name, sizeof(flat_name), "%s_%s", sname->c_str, field->data.decl.name->c_str);
                snprintf(sym_name, sizeof(sym_name), "til_%s", flat_name);
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
                Str *key = Str_new(flat_name);
                Map_set(&ffi_map, &key, &entry);
            }
        }
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
