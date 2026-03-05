#include "dispatch.h"
#include "ccore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>

// --- FFI state ---
typedef struct {
    void *fn;           // dlsym'd function pointer
    Str *return_type;   // NULL for proc (void return)
    int nparam;
} FFIEntry;

static Map ffi_map;          // name -> FFIEntry
static void *ffi_handle;     // dlopen handle
static int ffi_loaded;

int ext_function_dispatch(Str *name, Scope *scope, Expr *e, const char *path, Value *result) {
    // Variadic builtins
    if (Str_eq_c(name, "println")) {
        for (int i = 1; i < e->children.len; i++) {
            Value arg = eval_expr(scope, expr_child(e, i), path);
            printf("%s", arg.str->c_str);
        }
        printf("\n");
        *result = val_none();
        return 1;
    }
    if (Str_eq_c(name, "print")) {
        for (int i = 1; i < e->children.len; i++) {
            Value arg = eval_expr(scope, expr_child(e, i), path);
            printf("%s", arg.str->c_str);
        }
        *result = val_none();
        return 1;
    }
    if (Str_eq_c(name, "format")) {
        int nargs = e->children.len - 1;
        Str *strs[64];
        int total = 0;
        for (int i = 0; i < nargs; i++) {
            Value v = eval_expr(scope, expr_child(e, i + 1), path);
            strs[i] = v.str;
            total += v.str->len;
        }
        char *buf = malloc(total + 1);
        int off = 0;
        for (int i = 0; i < nargs; i++) {
            memcpy(buf + off, strs[i]->c_str, strs[i]->len);
            off += strs[i]->len;
        }
        buf[off] = '\0';
        Str *s = malloc(sizeof(Str));
        s->c_str = buf;
        s->len = total;
        *result = val_str(s);
        return 1;
    }

    // I64 arithmetic
    if (Str_eq_c(name, "I64_add")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_add(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_sub")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_sub(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_mul")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_mul(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_div")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_div(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_mod")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_mod(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_and")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_and(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_or"))  { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_or(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_xor")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_i64(I64_xor(*a.i64, *b.i64)); return 1; }

    // I64 comparisons
    if (Str_eq_c(name, "I64_eq")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(I64_eq(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_lt")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(I64_lt(*a.i64, *b.i64)); return 1; }
    if (Str_eq_c(name, "I64_gt")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(I64_gt(*a.i64, *b.i64)); return 1; }

    // I64 conversion
    if (Str_eq_c(name, "I64_to_str")) { Value v = eval_expr(scope, expr_child(e, 1), path); *result = val_str(I64_to_str(*v.i64)); return 1; }
    if (Str_eq_c(name, "I64_clone")) { Value v = eval_expr(scope, expr_child(e, 1), path); *result = val_i64(*v.i64); return 1; }
    if (Str_eq_c(name, "I64_delete")) { Value v = eval_expr(scope, expr_child(e, 1), path); if (v.type == VAL_NONE) { *result = val_none(); return 1; } Value cf = eval_expr(scope, expr_child(e, 2), path); if (*cf.boolean) I64_delete(v.i64); *result = val_none(); return 1; }

    // U8 arithmetic
    if (Str_eq_c(name, "U8_add")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_add(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_sub")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_sub(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_mul")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_mul(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_div")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_div(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_mod")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_mod(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_and")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_and(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_or"))  { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_or(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_xor")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_u8(U8_xor(*a.u8, *b.u8)); return 1; }

    // U8 comparisons
    if (Str_eq_c(name, "U8_eq")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(U8_eq(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_lt")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(U8_lt(*a.u8, *b.u8)); return 1; }
    if (Str_eq_c(name, "U8_gt")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(U8_gt(*a.u8, *b.u8)); return 1; }

    // U8 conversions
    if (Str_eq_c(name, "U8_to_str"))  { Value v = eval_expr(scope, expr_child(e, 1), path); *result = val_str(U8_to_str(*v.u8)); return 1; }
    if (Str_eq_c(name, "U8_to_i64"))  { Value v = eval_expr(scope, expr_child(e, 1), path); *result = val_i64(U8_to_i64(*v.u8)); return 1; }
    if (Str_eq_c(name, "U8_from_i64") || Str_eq_c(name, "U8_from_i64_ext")) {
        Value v = eval_expr(scope, expr_child(e, 1), path);
        *result = val_u8(U8_from_i64(*v.i64));
        return 1;
    }
    if (Str_eq_c(name, "U8_clone")) { Value v = eval_expr(scope, expr_child(e, 1), path); *result = val_u8(*v.u8); return 1; }
    if (Str_eq_c(name, "U8_delete")) { Value v = eval_expr(scope, expr_child(e, 1), path); if (v.type == VAL_NONE) { *result = val_none(); return 1; } Value cf = eval_expr(scope, expr_child(e, 2), path); if (*cf.boolean) U8_delete(v.u8); *result = val_none(); return 1; }

    // Bool ops
    if (Str_eq_c(name, "Bool_and")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(Bool_and(*a.boolean, *b.boolean)); return 1; }
    if (Str_eq_c(name, "Bool_or"))  { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(Bool_or(*a.boolean, *b.boolean)); return 1; }
    if (Str_eq_c(name, "Bool_not")) { Value a = eval_expr(scope, expr_child(e, 1), path); *result = val_bool(Bool_not(*a.boolean)); return 1; }
    if (Str_eq_c(name, "Bool_clone")) { Value v = eval_expr(scope, expr_child(e, 1), path); *result = val_bool(*v.boolean); return 1; }
    if (Str_eq_c(name, "Bool_delete")) { Value v = eval_expr(scope, expr_child(e, 1), path); if (v.type == VAL_NONE) { *result = val_none(); return 1; } Value cf = eval_expr(scope, expr_child(e, 2), path); if (*cf.boolean) Bool_delete(v.boolean); *result = val_none(); return 1; }

    // Str ops
    if (Str_eq_c(name, "Str_eq")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(Str_eq(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_concat")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_str(Str_concat(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_clone")) { Value a = eval_expr(scope, expr_child(e, 1), path); *result = val_str(Str_clone(a.str)); return 1; }
    if (Str_eq_c(name, "Str_delete")) {
        Value s = eval_expr(scope, expr_child(e, 1), path);
        if (s.type == VAL_NONE) { *result = val_none(); return 1; }
        Value cf = eval_expr(scope, expr_child(e, 2), path);
        if (*cf.boolean) Str_delete(s.str);
        *result = val_none(); return 1;
    }
    if (Str_eq_c(name, "Str_to_str")) { Value a = eval_expr(scope, expr_child(e, 1), path); *result = val_str(Str_clone(a.str)); return 1; }
    if (Str_eq_c(name, "Str_len")) { Value a = eval_expr(scope, expr_child(e, 1), path); *result = val_i64(Str_len(a.str)); return 1; }
    if (Str_eq_c(name, "Str_substr")) { Value s = eval_expr(scope, expr_child(e, 1), path); Value start = eval_expr(scope, expr_child(e, 2), path); Value n = eval_expr(scope, expr_child(e, 3), path); *result = val_str(Str_substr(s.str, (int)*start.i64, (int)*n.i64)); return 1; }
    if (Str_eq_c(name, "Str_contains")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(Str_contains(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_starts_with")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(Str_starts_with(a.str, b.str)); return 1; }
    if (Str_eq_c(name, "Str_ends_with")) { Value a = eval_expr(scope, expr_child(e, 1), path); Value b = eval_expr(scope, expr_child(e, 2), path); *result = val_bool(Str_ends_with(a.str, b.str)); return 1; }

    // Misc
    if (Str_eq_c(name, "exit")) { Value a = eval_expr(scope, expr_child(e, 1), path); til_exit(a.i64); *result = val_none(); return 1; }

    // free — accesses scope directly; requires identifier argument
    if (Str_eq_c(name, "free")) {
        if (expr_child(e, 1)->type != NODE_IDENT) {
            fprintf(stderr, "free() requires identifier argument\n"); exit(1);
        }
        Cell *cell = scope_get(scope, expr_child(e, 1)->data.str_val);
        if (cell->val.type == VAL_STRUCT && cell->val.instance) {
            til_free(cell->val.instance->field_names);
            til_free(cell->val.instance->field_muts);
            til_free(cell->val.instance->field_values);
            til_free(cell->val.instance);
        } else if (cell->val.type == VAL_ENUM && cell->val.enum_inst) {
            // Free payload if present, then the instance
            Value p = cell->val.enum_inst->payload;
            if (p.type == VAL_I64)  til_free(p.i64);
            else if (p.type == VAL_U8)   til_free(p.u8);
            else if (p.type == VAL_BOOL) til_free(p.boolean);
            else if (p.type == VAL_STR)  Str_delete(p.str);
            til_free(cell->val.enum_inst);
        } else if (cell->val.type == VAL_I64) {
            til_free(cell->val.i64);
        } else if (cell->val.type == VAL_U8) {
            til_free(cell->val.u8);
        } else if (cell->val.type == VAL_BOOL) {
            til_free(cell->val.boolean);
        } else if (cell->val.type == VAL_STR) {
            Str_delete(cell->val.str);
        }
        cell->val = val_none();
        *result = val_none();
        return 1;
    }

    // FFI trampoline
    if (ffi_loaded) {
        FFIEntry *fe = Map_get(&ffi_map, &name);
        if (fe) {
            int nargs = e->children.len - 1;
            void *args[8];
            for (int i = 0; i < nargs; i++) {
                Value v = eval_expr(scope, expr_child(e, i + 1), path);
                switch (v.type) {
                    case VAL_I64:  args[i] = v.i64; break;
                    case VAL_U8:   args[i] = v.u8; break;
                    case VAL_STR:  args[i] = v.str; break;
                    case VAL_BOOL: args[i] = v.boolean; break;
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
        // Variant access handled by interpreter field_access (copy-on-access)
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
                // Payload constructor: Token.Num(val)
                Value payload = eval_expr(scope, expr_child(e, 1), path);
                *result = val_enum(enum_name, ctor_tag, clone_value(payload));
            } else {
                // Zero-arg constructor: Token.Eof()
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
        if (method->len > 3 && memcmp(method->c_str, "is_", 3) == 0) {
            Str var_name = {.c_str = method->c_str + 3, .len = method->len - 3};
            int tag = enum_variant_tag(enum_def, &var_name);
            Value v = eval_expr(scope, expr_child(e, 1), path);
            if (v.type == VAL_ENUM)
                *result = val_bool(v.enum_inst->tag == tag);
            else
                *result = val_bool((int)*v.i64 == tag);
            return 1;
        }
        if (method->len > 4 && memcmp(method->c_str, "get_", 4) == 0) {
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
    for (int i = 0; i < program->children.len; i++) {
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
