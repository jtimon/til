#include "builder.h"
#include "map.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Expr *codegen_program; // set during codegen for ns_init lookups
static Map struct_bodies; // Str* name → Expr* body (NODE_BODY)
static Set script_globals; // names of top-level vars emitted as file-scope globals
static Bool has_script_globals; // whether script_globals is initialized
static Bool in_func_def; // true while emitting a function/proc body

// Collect unique array/vec builtin type names from AST
typedef struct { Str *type_name; I32 is_vec; } CollectionInfo;

static void collect_collection_builtins(Expr *e, Vec *infos) {
    if (!e) return;
    if (e->type == NODE_FCALL && expr_child(e, 0)->type == NODE_IDENT &&
        e->children.count >= 2 && expr_child(e, 1)->type == NODE_LITERAL_STR) {
        Str *name = expr_child(e, 0)->data.str_val;
        I32 is_vec = -1;
        if (Str_eq_c(name, "array")) is_vec = 0;
        else if (Str_eq_c(name, "vec")) is_vec = 1;
        if (is_vec >= 0) {
            Str *type_name = expr_child(e, 1)->data.str_val;
            for (U32 i = 0; i < infos->count; i++) {
                CollectionInfo *existing = Vec_get(infos, i);
                if (Str_eq(existing->type_name, type_name) && existing->is_vec == is_vec) return;
            }
            CollectionInfo info = {type_name, is_vec};
            Vec_push(infos, &info);
        }
    }
    for (U32 i = 0; i < e->children.count; i++) {
        collect_collection_builtins(expr_child(e, i), infos);
    }
}

// Collect unique dyn_call method literals from AST
typedef struct { Str *method; I32 nargs; Bool returns; } DynCallInfo;

static Bool is_dyn_call_name(Str *name, I32 *nargs, Bool *returns) {
    if (Str_eq_c(name, "dyn_call1"))     { *nargs = 1; *returns = 0; return 1; }
    if (Str_eq_c(name, "dyn_call2"))     { *nargs = 2; *returns = 0; return 1; }
    if (Str_eq_c(name, "dyn_call1_ret")) { *nargs = 1; *returns = 1; return 1; }
    if (Str_eq_c(name, "dyn_call2_ret")) { *nargs = 2; *returns = 1; return 1; }
    return 0;
}

static void collect_dyn_methods(Expr *e, Vec *methods) {
    if (!e) return;
    if (e->type == NODE_FCALL && expr_child(e, 0)->type == NODE_IDENT &&
        e->children.count >= 3 && expr_child(e, 2)->type == NODE_LITERAL_STR) {
        I32 nargs; Bool returns;
        if (is_dyn_call_name(expr_child(e, 0)->data.str_val, &nargs, &returns)) {
            Str *method = expr_child(e, 2)->data.str_val;
            for (U32 i = 0; i < methods->count; i++) {
                DynCallInfo *existing = Vec_get(methods, i);
                if (Str_eq(existing->method, method)) return;
            }
            DynCallInfo info = {method, nargs, returns};
            Vec_push(methods, &info);
        }
    }
    for (U32 i = 0; i < e->children.count; i++) {
        collect_dyn_methods(expr_child(e, i), methods);
    }
}

// Collect unique method names from dyn_has_method calls
static void collect_dyn_has_methods(Expr *e, Vec *methods) {
    if (!e) return;
    if (e->type == NODE_FCALL && expr_child(e, 0)->type == NODE_IDENT &&
        Str_eq_c(expr_child(e, 0)->data.str_val, "dyn_has_method") &&
        e->children.count >= 3 && expr_child(e, 2)->type == NODE_LITERAL_STR) {
        Str *method = expr_child(e, 2)->data.str_val;
        for (U32 i = 0; i < methods->count; i++) {
            Str **existing = Vec_get(methods, i);
            if (Str_eq(*existing, method)) return;
        }
        Vec_push(methods, &method);
    }
    for (U32 i = 0; i < e->children.count; i++) {
        collect_dyn_has_methods(expr_child(e, i), methods);
    }
}

static Expr *find_struct_body(Str *name) {
    Expr **p = Map_get(&struct_bodies, &name);
    return p ? *p : NULL;
}

// --- Emitter helpers ---

static void emit_indent(FILE *f, U32 depth) {
    for (U32 i = 0; i < depth; i++) fprintf(f, "    ");
}

// Emit expression dereferenced to a value: (*x) for IDENT, plain for literals/builtins
static void emit_deref(FILE *f, Expr *e, I32 depth);
// Emit expression as a pointer: wraps values in &(type){val}
static void emit_as_ptr(FILE *f, Expr *e, I32 depth);

// --- Forward declarations ---

static void emit_expr(FILE *f, Expr *e, I32 depth);
static void emit_stmt(FILE *f, Expr *e, I32 depth);
static void emit_body(FILE *f, Expr *body, I32 depth);

// Map til function names to C symbol names (handles stdlib collisions)
static const char *func_to_c(Str *name) {
    if (Str_eq_c(name, "exit")) return "exit_program";
    if (Str_eq_c(name, "sleep")) return "sleep_ms";
    if (Str_eq_c(name, "and")) return "Bool_and";
    if (Str_eq_c(name, "or")) return "Bool_or";
    if (Str_eq_c(name, "not")) return "Bool_not";
    // C keyword collision
    if (Str_eq_c(name, "double")) return "double_";
    // Keep til_ prefix for wrappers that have different signatures than C stdlib
    if (Str_eq_c(name, "malloc")) return "til_malloc";
    if (Str_eq_c(name, "realloc")) return "til_realloc";
    if (Str_eq_c(name, "memcpy")) return "til_memcpy";
    if (Str_eq_c(name, "memmove")) return "til_memmove";
    return name->c_str;
}

// --- Expression emission ---

static void emit_expr(FILE *f, Expr *e, I32 depth) {
    (void)depth;
    switch (e->type) {
    case NODE_LITERAL_STR:
        fprintf(f, "Str_lit(\"%s\", %lld)", e->data.str_val->c_str, (long long)e->data.str_val->count);
        break;
    case NODE_LITERAL_NUM:
        fprintf(f, "%s", e->data.str_val->c_str);
        break;
    case NODE_LITERAL_BOOL:
        fprintf(f, "%d", Str_eq_c(e->data.str_val, "true") ? 1 : 0);
        break;
    case NODE_IDENT:
        fprintf(f, "%s", e->data.str_val->c_str);
        break;
    case NODE_FCALL: {
        // Namespace method call: Struct.method(args)
        if (expr_child(e, 0)->type == NODE_FIELD_ACCESS) {
            Str *sname = expr_child(expr_child(e, 0), 0)->struct_name;
            Str *mname = expr_child(e, 0)->data.str_val;
            fprintf(f, "%s_%s(", sname->c_str, mname->c_str);
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
            break;
        }
        Str *name = expr_child(e, 0)->data.str_val;
        if (Str_eq_c(name, "dyn_call1") || Str_eq_c(name, "dyn_call2") ||
                   Str_eq_c(name, "dyn_call1_ret") || Str_eq_c(name, "dyn_call2_ret")) {
            // dyn_call*(type_name, "method", val, ...) → dyn_call_method(type_name, val, ...)
            Str *method = expr_child(e, 2)->data.str_val;
            fprintf(f, "dyn_call_%s(", method->c_str);
            // Emit type_name as first arg
            emit_as_ptr(f, expr_child(e, 1), depth);
            // Emit remaining args (val, and any extra args like call_free)
            for (U32 i = 3; i < e->children.count; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        } else if (Str_eq_c(name, "array") || Str_eq_c(name, "vec")) {
            // array("I64", 1, 2, 3) → array_of_I64(3, v1, v2, v3)
            // vec("I64", 1, 2, 3)   → vec_of_I64(3, v1, v2, v3)
            Str *elem_type = expr_child(e, 1)->data.str_val;
            I32 count = e->children.count - 2;
            const char *prefix = Str_eq_c(name, "array") ? "array" : "vec";
            fprintf(f, "%s_of_%s(%d", prefix, elem_type->c_str, count);
            for (U32 i = 2; i < e->children.count; i++) {
                fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        } else if (Str_eq_c(name, "dyn_has_method")) {
            // dyn_has_method(type_name, "method") → dyn_has_method(type_name)
            Str *method = expr_child(e, 2)->data.str_val;
            fprintf(f, "dyn_has_%s(", method->c_str);
            emit_as_ptr(f, expr_child(e, 1), depth);
            fprintf(f, ")");
        } else if (e->struct_name && Str_eq(name, e->struct_name)) {
            // Struct constructor — compound literal (handled in emit_stmt)
            fprintf(f, "/* BUG: struct constructor in expr context */");
        } else {
            // User-defined function call
            fprintf(f, "%s(", func_to_c(name));
            for (U32 i = 1; i < e->children.count; i++) {
                if (i > 1) fprintf(f, ", ");
                emit_as_ptr(f, expr_child(e, i), depth);
            }
            fprintf(f, ")");
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        Expr *obj = expr_child(e, 0);
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            fprintf(f, "%s_%s", obj->struct_name->c_str, fname->c_str);
            // Auto-call enum variant constructors (Color.Red → Color_Red())
            if (e->til_type == TIL_TYPE_ENUM) fprintf(f, "()");
        } else {
            emit_expr(f, obj, depth);
            Bool use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
            fprintf(f, "%s%s", use_dot ? "." : "->", fname->c_str);
        }
        break;
    }
    default:
        fprintf(f, "/* TODO: expr type %d */", e->type);
        break;
    }
}

// --- Type to C type string ---

static const char *til_type_to_c(TilType t) {
    switch (t) {
    case TIL_TYPE_I64:  return "I64";
    case TIL_TYPE_U8:   return "U8";
    case TIL_TYPE_I16:  return "I16";
    case TIL_TYPE_I32:  return "I32";
    case TIL_TYPE_U32:  return "U32";
    case TIL_TYPE_BOOL: return "Bool";
    case TIL_TYPE_NONE:    return "void";
    case TIL_TYPE_DYNAMIC: return "void *";
    default:               return "I64"; // fallback
    }
}

// C type name without pointer — "Point" for structs, "I64" for I64, etc.
static const char *c_type_name(TilType t, Str *struct_name) {
    if ((t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM) && struct_name) {
        static char buf[128];
        snprintf(buf, sizeof(buf), "%s", struct_name->c_str);
        return buf;
    }
    if (t == TIL_TYPE_DYNAMIC) return "void";
    return til_type_to_c(t);
}

// Convert a type name string to C type string (handles struct types)
static const char *type_name_to_c(Str *name) {
    if (Str_eq_c(name, "I64"))  return "I64 *";
    if (Str_eq_c(name, "U8"))   return "U8 *";
    if (Str_eq_c(name, "I16"))  return "I16 *";
    if (Str_eq_c(name, "I32"))  return "I32 *";
    if (Str_eq_c(name, "U32"))  return "U32 *";
    if (Str_eq_c(name, "Bool")) return "Bool *";
    if (Str_eq_c(name, "Dynamic")) return "void *";
    // User-defined struct type — pointer
    static char buf[128];
    snprintf(buf, sizeof(buf), "%s *", name->c_str);
    return buf;
}

// Like type_name_to_c but without pointer — for inline union fields
static const char *type_name_to_c_value(Str *name) {
    if (Str_eq_c(name, "I64"))  return "I64";
    if (Str_eq_c(name, "U8"))   return "U8";
    if (Str_eq_c(name, "I16"))  return "I16";
    if (Str_eq_c(name, "I32"))  return "I32";
    if (Str_eq_c(name, "U32"))  return "U32";
    if (Str_eq_c(name, "Bool")) return "Bool";
    static char buf2[128];
    snprintf(buf2, sizeof(buf2), "%s", name->c_str);
    return buf2;
}

static Bool is_primitive_type(Str *name) {
    return Str_eq_c(name, "I64") || Str_eq_c(name, "U8") || Str_eq_c(name, "I16") ||
           Str_eq_c(name, "I32") || Str_eq_c(name, "U32") || Str_eq_c(name, "Bool");
}

// Emit a function parameter list (with variadic support)
static void emit_param_list(FILE *f, Expr *fdef, Bool with_names) {
    U32 np = fdef->data.func_def.nparam;
    I32 fvi = fdef->data.func_def.variadic_index;
    if (np == 0) {
        fprintf(f, "void");
    } else {
        for (U32 i = 0; i < np; i++) {
            if (i > 0) fprintf(f, ", ");
            const char *ptype = ((I32)i == fvi) ? "Array *"
                : type_name_to_c(fdef->data.func_def.param_types[i]);
            if (with_names)
                fprintf(f, "%s %s", ptype, fdef->data.func_def.param_names[i]->c_str);
            else
                fprintf(f, "%s", ptype);
        }
    }
}

static void emit_deref(FILE *f, Expr *e, I32 depth) {
    if (e->til_type == TIL_TYPE_DYNAMIC) {
        // Dynamic (void *) IS the value — no dereference needed
        emit_expr(f, e, depth);
    } else if (e->type == NODE_IDENT) {
        fprintf(f, "(*");
        emit_expr(f, e, depth);
        fprintf(f, ")");
    } else if (e->type == NODE_LITERAL_STR) {
        fprintf(f, "(Str){.data=(U8*)\"%s\", .count=%lld, .cap=TIL_CAP_LIT}",
                e->data.str_val->c_str, (long long)e->data.str_val->count);
    } else if (e->type == NODE_FIELD_ACCESS && e->is_ns_field && e->til_type == TIL_TYPE_ENUM) {
        // Auto-called constructor returns pointer; dereference it
        fprintf(f, "(*");
        emit_expr(f, e, depth);
        fprintf(f, ")");
    } else {
        emit_expr(f, e, depth);
    }
}

// Emit expression as a pointer — after hoisting, args are NODE_IDENT (already pointer)
// or NODE_FIELD_ACCESS (value needing compound literal wrapping).
static void emit_as_ptr(FILE *f, Expr *e, I32 depth) {
    if (e->type == NODE_IDENT || e->type == NODE_FCALL || e->type == NODE_LITERAL_STR) {
        emit_expr(f, e, depth);
    } else if (e->type == NODE_FIELD_ACCESS) {
        // Own field is already a pointer; enum ns_field constructor returns pointer;
        // Dynamic field is void* (already a pointer); inline field needs address-of
        if (e->is_own_field || (e->is_ns_field && e->til_type == TIL_TYPE_ENUM) ||
            e->til_type == TIL_TYPE_DYNAMIC) {
            emit_expr(f, e, depth);
        } else {
            fprintf(f, "&");
            emit_expr(f, e, depth);
        }
    } else {
        const char *ctype = c_type_name(e->til_type, e->struct_name);
        fprintf(f, "&(%s){", ctype);
        emit_expr(f, e, depth);
        fprintf(f, "}");
    }
}

// Emit struct constructor field assignments into 'var' (already malloc'd).
static I32 _ctor_seq = 0;
static void emit_ctor_fields(FILE *f, const char *var, Expr *ctor, I32 depth) {
    Expr *sbody = find_struct_body(ctor->struct_name);
    U32 fi = 0;
    for (U32 i = 1; i < ctor->children.count; i++) {
        Bool is_own = 0;
        const char *fname = NULL;
        if (sbody) {
            for (; fi < sbody->children.count; fi++) {
                if (!expr_child(sbody, fi)->data.decl.is_namespace) {
                    is_own = expr_child(sbody, fi)->data.decl.is_own;
                    fname = expr_child(sbody, fi)->data.decl.name->c_str;
                    fi++;
                    break;
                }
            }
        }
        Expr *arg = expr_child(ctor, i);
        emit_indent(f, depth);
        if (is_own && arg->type == NODE_FCALL && arg->struct_name &&
            Str_eq(expr_child(arg, 0)->data.str_val, arg->struct_name)) {
            // Nested struct constructor for own field: emit as temp, assign pointer
            const char *ct = c_type_name(arg->til_type, arg->struct_name);
            I32 id = _ctor_seq++;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_cs%d", id);
            fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ct, tmp, ct);
            emit_ctor_fields(f, tmp, arg, depth);
            emit_indent(f, depth);
            fprintf(f, "%s->%s = %s;\n", var, fname, tmp);
        } else if (is_own) {
            fprintf(f, "%s->%s = ", var, fname);
            emit_expr(f, arg, depth);
            fprintf(f, ";\n");
        } else if (arg->type == NODE_FCALL && arg->struct_name &&
                   Str_eq(expr_child(arg, 0)->data.str_val, arg->struct_name)) {
            // Inline struct field: nested constructor — build in-place
            const char *ct = c_type_name(arg->til_type, arg->struct_name);
            I32 id = _ctor_seq++;
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "_cs%d", id);
            fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ct, tmp, ct);
            emit_ctor_fields(f, tmp, arg, depth);
            emit_indent(f, depth);
            fprintf(f, "%s->%s = *%s; free(%s);\n", var, fname, tmp, tmp);
        } else if (arg->type == NODE_FCALL) {
            // Unhoisted fcall for inline compound field: deref + free wrapper
            const char *ftype = c_type_name(arg->til_type, arg->struct_name);
            fprintf(f, "{ %s *_ca = ", ftype);
            emit_expr(f, arg, depth);
            fprintf(f, "; %s->%s = *_ca; free(_ca); }\n", var, fname);
        } else {
            fprintf(f, "%s->%s = ", var, fname);
            emit_deref(f, arg, depth);
            fprintf(f, ";\n");
        }
    }
}

// --- Statement emission ---

static void emit_stmt(FILE *f, Expr *e, I32 depth) {
    emit_indent(f, depth);
    switch (e->type) {
    case NODE_DECL:
        if (expr_child(e, 0)->type == NODE_FUNC_DEF) {
            fprintf(f, "/* TODO: nested func %s */\n", e->data.decl.name->c_str);
        } else if (expr_child(e, 0)->type == NODE_STRUCT_DEF ||
                   expr_child(e, 0)->type == NODE_ENUM_DEF) {
            fprintf(f, "/* %s %s defined above */\n",
                    expr_child(e, 0)->type == NODE_ENUM_DEF ? "enum" : "struct",
                    e->data.decl.name->c_str);
        } else if (e->data.decl.is_ref) {
            const char *ctype = c_type_name(e->til_type, expr_child(e, 0)->struct_name);
            Expr *rhs = expr_child(e, 0);
            fprintf(f, "%s *%s = ", ctype, e->data.decl.name->c_str);
            emit_expr(f, rhs, depth);
            fprintf(f, ";\n");
        } else {
            const char *ctype = c_type_name(e->til_type, expr_child(e, 0)->struct_name);
            Expr *rhs = expr_child(e, 0);
            Bool is_global = has_script_globals && !in_func_def && Set_has(&script_globals, &e->data.decl.name);
            if (rhs->type == NODE_FCALL && rhs->struct_name &&
                Str_eq(expr_child(rhs, 0)->data.str_val, rhs->struct_name)) {
                // Struct constructor — malloc + field-by-field assignment
                const char *var = e->data.decl.name->c_str;
                if (is_global)
                    fprintf(f, "%s = malloc(sizeof(%s));\n", var, ctype);
                else
                    fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ctype, var, ctype);
                emit_ctor_fields(f, var, rhs, depth);
            } else if (rhs->type == NODE_FCALL || rhs->type == NODE_LITERAL_STR ||
                       (rhs->type == NODE_FIELD_ACCESS && rhs->is_ns_field && rhs->til_type == TIL_TYPE_ENUM)) {
                // Function calls / enum constructors already return a fresh heap pointer
                if (is_global)
                    fprintf(f, "%s = ", e->data.decl.name->c_str);
                else
                    fprintf(f, "%s *%s = ", ctype, e->data.decl.name->c_str);
                emit_expr(f, rhs, depth);
                fprintf(f, ";\n");
            } else {
                // Literals and idents: allocate new memory and copy the value
                if (is_global)
                    fprintf(f, "%s = malloc(sizeof(%s));\n", e->data.decl.name->c_str, ctype);
                else
                    fprintf(f, "%s *%s = malloc(sizeof(%s));\n", ctype, e->data.decl.name->c_str, ctype);
                emit_indent(f, depth);
                fprintf(f, "*%s = ", e->data.decl.name->c_str);
                emit_deref(f, rhs, depth);
                fprintf(f, ";\n");
            }
        }
        break;
    case NODE_ASSIGN: {
        Expr *rhs = expr_child(e, 0);
        if (rhs->type == NODE_FCALL || rhs->type == NODE_LITERAL_STR ||
            (rhs->type == NODE_FIELD_ACCESS && rhs->is_ns_field && rhs->til_type == TIL_TYPE_ENUM)) {
            fprintf(f, "%s = ", e->data.str_val->c_str);
            emit_expr(f, rhs, depth);
        } else {
            fprintf(f, "*%s = ", e->data.str_val->c_str);
            emit_deref(f, rhs, depth);
        }
        fprintf(f, ";\n");
        break;
    }
    case NODE_FIELD_ASSIGN: {
        Expr *obj = expr_child(e, 0);
        Str *fname = e->data.str_val;
        if (expr_child(e, 1)->type == NODE_FCALL && !e->is_own_field && !e->is_ns_field) {
            // Unhoisted fcall for inline compound field: deref + free wrapper
            const char *ftype = c_type_name(expr_child(e, 1)->til_type, expr_child(e, 1)->struct_name);
            fprintf(f, "{ %s *_fa = ", ftype);
            emit_expr(f, expr_child(e, 1), depth);
            fprintf(f, "; ");
            emit_expr(f, obj, depth);
            Bool use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
            fprintf(f, "%s%s = *_fa; free(_fa); }\n", use_dot ? "." : "->", fname->c_str);
        } else {
            if (e->is_ns_field) {
                fprintf(f, "%s_%s = ", obj->struct_name->c_str, fname->c_str);
            } else {
                emit_expr(f, obj, depth);
                Bool use_dot = (obj->type == NODE_FIELD_ACCESS && !obj->is_own_field);
                fprintf(f, "%s%s = ", use_dot ? "." : "->", fname->c_str);
            }
            if (e->is_own_field) {
                emit_expr(f, expr_child(e, 1), depth);
            } else {
                emit_deref(f, expr_child(e, 1), depth);
            }
            fprintf(f, ";\n");
        }
        break;
    }
    case NODE_FCALL:
        if (e->struct_name && Str_eq(expr_child(e, 0)->data.str_val, e->struct_name)) {
            // Bare struct constructor statement — discard result
            fprintf(f, "/* discarded struct constructor */;\n");
        } else {
            emit_expr(f, e, depth);
            fprintf(f, ";\n");
        }
        break;
    case NODE_RETURN:
        if (e->children.count == 0) {
            fprintf(f, "return;\n");
        } else {
            Expr *rv = expr_child(e, 0);
            if (rv->type == NODE_FCALL && rv->struct_name &&
                Str_eq(expr_child(rv, 0)->data.str_val, rv->struct_name)) {
                // Struct constructor return — malloc + field-by-field
                const char *ctype = c_type_name(rv->til_type, rv->struct_name);
                fprintf(f, "{ %s *_r = malloc(sizeof(%s));\n", ctype, ctype);
                emit_ctor_fields(f, "_r", rv, depth);
                emit_indent(f, depth);
                fprintf(f, "return _r; }\n");
            } else if (rv->type == NODE_FIELD_ACCESS && !rv->is_own_field &&
                       !rv->is_ns_field && rv->til_type != TIL_TYPE_DYNAMIC) {
                // Inline field value — must clone to heap pointer for return
                const char *ctype = c_type_name(rv->til_type, rv->struct_name);
                fprintf(f, "{ %s *_r = malloc(sizeof(%s)); *_r = ", ctype, ctype);
                emit_expr(f, rv, depth);
                fprintf(f, "; return _r; }\n");
            } else {
                fprintf(f, "return ");
                emit_expr(f, rv, depth);
                fprintf(f, ";\n");
            }
        }
        break;
    case NODE_BODY:
        fprintf(f, "{\n");
        emit_body(f, e, depth + 1);
        emit_indent(f, depth);
        fprintf(f, "}\n");
        break;
    case NODE_IF:
        fprintf(f, "if (");
        emit_deref(f, expr_child(e, 0), depth);
        fprintf(f, ") {\n");
        emit_body(f, expr_child(e, 1), depth + 1);
        emit_indent(f, depth);
        if (e->children.count > 2) {
            fprintf(f, "} else {\n");
            emit_body(f, expr_child(e, 2), depth + 1);
            emit_indent(f, depth);
        }
        fprintf(f, "}\n");
        break;
    case NODE_WHILE:
        fprintf(f, "while (");
        emit_deref(f, expr_child(e, 0), depth);
        fprintf(f, ") {\n");
        emit_body(f, expr_child(e, 1), depth + 1);
        emit_indent(f, depth);
        fprintf(f, "}\n");
        break;
    case NODE_BREAK:
        fprintf(f, "break;\n");
        break;
    case NODE_CONTINUE:
        fprintf(f, "continue;\n");
        break;
    default:
        fprintf(f, "/* TODO: stmt type %d */\n", e->type);
        break;
    }
}

static void emit_body(FILE *f, Expr *body, I32 depth) {
    for (U32 i = 0; i < body->children.count; i++) {
        emit_stmt(f, expr_child(body, i), depth);
    }
}

// --- Top-level emission ---

// Emit namespace field initializations for all structs in the program
static void emit_ns_inits(FILE *f, I32 depth) {
    for (U32 i = 0; i < codegen_program->children.count; i++) {
        Expr *stmt = expr_child(codegen_program, i);
        if (stmt->type == NODE_DECL && (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                                        expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *edef = expr_child(stmt, 0);
            Expr *body = expr_child(edef, 0);
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = expr_child(body, j);
                if (!field->data.decl.is_namespace) continue;
                if (expr_child(field, 0)->type == NODE_FUNC_DEF) continue;
                // Skip enum variant literals — handled by constructor functions
                if (edef->type == NODE_ENUM_DEF) continue;
                emit_indent(f, depth);
                fprintf(f, "%s_%s = ", sname->c_str, field->data.decl.name->c_str);
                emit_deref(f, expr_child(field, 0), depth);
                fprintf(f, ";\n");
            }
        }
    }
}

static void emit_func_def(FILE *f, Str *name, Expr *func_def, const Mode *mode) {
    (void)func_def->data.func_def.func_type;
    Expr *body = expr_child(func_def, 0);

    // In needs_main mode, main proc becomes C main()
    Bool is_main = mode && mode->needs_main && Str_eq_c(name, "main");

    if (is_main) {
        U32 nparam = func_def->data.func_def.nparam;
        I32 vi = func_def->data.func_def.variadic_index;
        if (nparam == 0) {
            fprintf(f, "int main(int argc, char **argv) {\n");
            fprintf(f, "    (void)argv;\n");
            fprintf(f, "    if (argc > 1) { fprintf(stderr, \"error: main expects no arguments, got %%d\\n\", argc - 1); return 1; }\n");
        } else {
            fprintf(f, "int main(int argc, char **argv) {\n");
            I32 fixed = (vi >= 0) ? nparam - 1 : nparam;
            if (vi >= 0) {
                fprintf(f, "    if (argc - 1 < %d) { fprintf(stderr, \"error: main expects at least %d argument(s), got %%d\\n\", argc - 1); return 1; }\n", fixed, fixed);
            } else {
                fprintf(f, "    if (argc - 1 != %d) { fprintf(stderr, \"error: main expects %d argument(s), got %%d\\n\", argc - 1); return 1; }\n", nparam, nparam);
            }
            // Parse and bind each param
            I32 argi = 1; // argv[0] is program name, skip it
            for (U32 i = 0; i < nparam; i++) {
                Str *pname = func_def->data.func_def.param_names[i];
                Str *ptype = func_def->data.func_def.param_types[i];
                if ((I32)i == vi) {
                    // Build Array[T] from remaining args
                    const char *et = ptype->c_str;
                    fprintf(f, "    int _va_argc = argc - %d;\n", argi);
                    fprintf(f, "    Str *_va_et = Str_lit(\"%s\", %lld);\n", et, (long long)ptype->count);
                    fprintf(f, "    I64 *_va_esz = malloc(sizeof(I64)); *_va_esz = sizeof(%s);\n", et);
                    fprintf(f, "    I64 *_va_cap = malloc(sizeof(I64)); *_va_cap = _va_argc;\n");
                    fprintf(f, "    Array *%s = Array_new(_va_et, _va_esz, _va_cap);\n", pname->c_str);
                    fprintf(f, "    Str_delete(_va_et, &(Bool){1});\n");
                    fprintf(f, "    I64_delete(_va_esz, &(Bool){1});\n");
                    fprintf(f, "    I64_delete(_va_cap, &(Bool){1});\n");
                    fprintf(f, "    for (int _i = 0; _i < _va_argc; _i++) {\n");
                    fprintf(f, "        I64 *_idx = malloc(sizeof(I64)); *_idx = _i;\n");
                    if (Str_eq_c(ptype, "Str"))
                        fprintf(f, "        Str *_val = Str_lit(argv[%d + _i], strlen(argv[%d + _i]));\n", argi, argi);
                    else if (Str_eq_c(ptype, "I64"))
                        fprintf(f, "        I64 *_val = cli_parse_i64(argv[%d + _i]);\n", argi);
                    else if (Str_eq_c(ptype, "U8"))
                        fprintf(f, "        U8 *_val = cli_parse_u8(argv[%d + _i]);\n", argi);
                    else if (Str_eq_c(ptype, "I16"))
                        fprintf(f, "        I16 *_val = cli_parse_i16(argv[%d + _i]);\n", argi);
                    else if (Str_eq_c(ptype, "I32"))
                        fprintf(f, "        I32 *_val = cli_parse_i32(argv[%d + _i]);\n", argi);
                    else if (Str_eq_c(ptype, "U32"))
                        fprintf(f, "        U32 *_val = cli_parse_u32(argv[%d + _i]);\n", argi);
                    else if (Str_eq_c(ptype, "Bool"))
                        fprintf(f, "        Bool *_val = cli_parse_bool(argv[%d + _i]);\n", argi);
                    fprintf(f, "        Array_set(%s, _idx, _val);\n", pname->c_str);
                    fprintf(f, "        I64_delete(_idx, &(Bool){1});\n");
                    fprintf(f, "    }\n");
                } else if (Str_eq_c(ptype, "Str")) {
                    fprintf(f, "    Str *%s = Str_lit(argv[%d], strlen(argv[%d]));\n", pname->c_str, argi, argi);
                    argi++;
                } else if (Str_eq_c(ptype, "I64")) {
                    fprintf(f, "    I64 *%s = cli_parse_i64(argv[%d]);\n", pname->c_str, argi);
                    argi++;
                } else if (Str_eq_c(ptype, "U8")) {
                    fprintf(f, "    U8 *%s = cli_parse_u8(argv[%d]);\n", pname->c_str, argi);
                    argi++;
                } else if (Str_eq_c(ptype, "I16")) {
                    fprintf(f, "    I16 *%s = cli_parse_i16(argv[%d]);\n", pname->c_str, argi);
                    argi++;
                } else if (Str_eq_c(ptype, "I32")) {
                    fprintf(f, "    I32 *%s = cli_parse_i32(argv[%d]);\n", pname->c_str, argi);
                    argi++;
                } else if (Str_eq_c(ptype, "U32")) {
                    fprintf(f, "    U32 *%s = cli_parse_u32(argv[%d]);\n", pname->c_str, argi);
                    argi++;
                } else if (Str_eq_c(ptype, "Bool")) {
                    fprintf(f, "    Bool *%s = cli_parse_bool(argv[%d]);\n", pname->c_str, argi);
                    argi++;
                } else {
                    fprintf(f, "    // unsupported CLI arg type: %s\n", ptype->c_str);
                    fprintf(f, "    fprintf(stderr, \"error: unsupported CLI argument type '%s'\\n\"); return 1;\n", ptype->c_str);
                    argi++;
                }
            }
        }
        emit_ns_inits(f, 1);
        // Initialize root-scope globals before main body
        if (has_script_globals) {
            for (U32 i = 0; i < codegen_program->children.count; i++) {
                Expr *gs = expr_child(codegen_program, i);
                if (gs->type != NODE_DECL) continue;
                Expr *rhs = expr_child(gs, 0);
                if (rhs->type == NODE_FUNC_DEF || rhs->type == NODE_STRUCT_DEF ||
                    rhs->type == NODE_ENUM_DEF) continue;
                emit_stmt(f, gs, 1);
            }
        }
        emit_body(f, body, 1);
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    } else {
        // Return type
        const char *ret = "void";
        if (func_def->data.func_def.return_type) {
            ret = type_name_to_c(func_def->data.func_def.return_type);
        }
        // Signature
        fprintf(f, "%s %s(", ret, func_to_c(name));
        emit_param_list(f, func_def, 1);
        fprintf(f, ") {\n");
        in_func_def = 1;
        emit_body(f, body, 1);
        in_func_def = 0;
        fprintf(f, "}\n");
    }
}

static void emit_struct_typedef(FILE *f, Str *name, Expr *struct_def, Bool is_core) {
    Expr *body = expr_child(struct_def, 0);
    if (struct_def->is_ext && is_core) return; // core ext_structs defined in ext.h
    if (Str_eq_c(name, "Str") || Str_eq_c(name, "Array")) return; // typedefs provided by ext.h
    Bool has_instance_fields = 0;
    for (U32 i = 0; i < body->children.count; i++)
        if (!expr_child(body, i)->data.decl.is_namespace) { has_instance_fields = 1; break; }
    fprintf(f, "typedef struct %s {\n", name->c_str);
    if (!has_instance_fields) {
        fprintf(f, "    char _;\n"); // padding for empty structs
    }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = expr_child(body, i);
        if (field->data.decl.is_namespace) continue;
        if (field->data.decl.is_own && (field->til_type == TIL_TYPE_STRUCT || field->til_type == TIL_TYPE_ENUM) && expr_child(field, 0)->struct_name) {
            fprintf(f, "    %s *%s;\n", expr_child(field, 0)->struct_name->c_str, field->data.decl.name->c_str);
        } else if (field->data.decl.is_own) {
            fprintf(f, "    %s *%s;\n", til_type_to_c(field->til_type), field->data.decl.name->c_str);
        } else if ((field->til_type == TIL_TYPE_STRUCT || field->til_type == TIL_TYPE_ENUM) && expr_child(field, 0)->struct_name) {
            fprintf(f, "    %s %s;\n", expr_child(field, 0)->struct_name->c_str, field->data.decl.name->c_str);
        } else {
            fprintf(f, "    %s %s;\n", til_type_to_c(field->til_type), field->data.decl.name->c_str);
        }
    }
    fprintf(f, "} %s;\n\n", name->c_str);
    // Emit namespace fields as globals (skip func defs — emitted separately)
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = expr_child(body, i);
        if (!field->data.decl.is_namespace) continue;
        if (expr_child(field, 0)->type == NODE_FUNC_DEF) continue;
        if ((field->til_type == TIL_TYPE_STRUCT || field->til_type == TIL_TYPE_ENUM) && expr_child(field, 0)->struct_name) {
            fprintf(f, "%s %s_%s;\n", expr_child(field, 0)->struct_name->c_str, name->c_str, field->data.decl.name->c_str);
        } else {
            fprintf(f, "%s %s_%s;\n", til_type_to_c(field->til_type), name->c_str, field->data.decl.name->c_str);
        }
    }
}

static void emit_struct_funcs(FILE *f, Str *name, Expr *struct_def) {
    Expr *body = expr_child(struct_def, 0);
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = expr_child(body, i);
        if (!field->data.decl.is_namespace) continue;
        if (expr_child(field, 0)->type != NODE_FUNC_DEF) continue;
        Expr *fdef = expr_child(field, 0);
        FuncType fft = fdef->data.func_def.func_type;
        if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
        // Emit size() as sizeof — the initer's computed sum doesn't account for
        // C alignment padding or union semantics in tagged enums
        if (Str_eq_c(field->data.decl.name, "size") &&
            fdef->data.func_def.nparam == 0 &&
            fdef->data.func_def.return_type &&
            Str_eq_c(fdef->data.func_def.return_type, "I64")) {
            fprintf(f, "I64 *%s_size(void) {\n", name->c_str);
            fprintf(f, "    I64 *r = malloc(sizeof(I64));\n");
            fprintf(f, "    *r = (I64)sizeof(%s);\n", name->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n\n");
            continue;
        }
        char full_name_buf[256];
        snprintf(full_name_buf, sizeof(full_name_buf), "%s_%s", name->c_str, field->data.decl.name->c_str);
        Str *full_name = Str_new(full_name_buf);
        emit_func_def(f, full_name, fdef, NULL);
        Str_delete(full_name);
        fprintf(f, "\n");
    }
}

static void emit_enum_def(FILE *f, Str *name, Expr *enum_def) {
    Expr *body = expr_child(enum_def, 0);
    Bool hp = enum_has_payloads(enum_def);

    if (!hp) {
        // === SIMPLE ENUM ===

        // Collect variant names from non-namespace entries
        Vec vnames = Vec_new(sizeof(Str *));
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *v = expr_child(body, i);
            if (v->data.decl.is_namespace) continue;
            Vec_push(&vnames, &v->data.decl.name);
        }

        // Zero-arg constructors
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, i);
            fprintf(f, "%s *%s_%s() {\n", name->c_str, name->c_str, vn->c_str);
            fprintf(f, "    %s *r = malloc(sizeof(%s));\n", name->c_str, name->c_str);
            fprintf(f, "    *r = (%s){ .tag = %s_TAG_%s };\n", name->c_str, name->c_str, vn->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // is_Variant functions
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, i);
            fprintf(f, "Bool *%s_is_%s(%s *self) {\n", name->c_str, vn->c_str, name->c_str);
            fprintf(f, "    Bool *r = malloc(sizeof(Bool));\n");
            fprintf(f, "    *r = (self->tag == %s_TAG_%s);\n", name->c_str, vn->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        Vec_delete(&vnames);
    } else {
        // === PAYLOAD ENUM ===

        // Collect variant info from non-namespace entries
        Vec vnames = Vec_new(sizeof(Str *));
        Vec vtypes = Vec_new(sizeof(Str *));
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *v = expr_child(body, i);
            if (v->data.decl.is_namespace) continue;
            Vec_push(&vnames, &v->data.decl.name);
            Vec_push(&vtypes, &v->data.decl.explicit_type);
        }

        // Constructor functions for all variants
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, i);
            Str *vt = *(Str **)Vec_get(&vtypes, i);
            if (!vt) {
                // Zero-arg constructor for no-payload variant
                fprintf(f, "%s *%s_%s() {\n", name->c_str, name->c_str, vn->c_str);
                fprintf(f, "    %s *r = malloc(sizeof(%s));\n", name->c_str, name->c_str);
                fprintf(f, "    r->tag = %s_TAG_%s;\n", name->c_str, vn->c_str);
                fprintf(f, "    return r;\n");
                fprintf(f, "}\n");
                continue;
            }
            const char *ptype = type_name_to_c(vt);
            fprintf(f, "%s *%s_%s(%s val) {\n", name->c_str, name->c_str, vn->c_str, ptype);
            fprintf(f, "    %s *r = malloc(sizeof(%s));\n", name->c_str, name->c_str);
            fprintf(f, "    r->tag = %s_TAG_%s;\n", name->c_str, vn->c_str);
            // Store payload inline (by value)
            if (is_primitive_type(vt)) {
                fprintf(f, "    r->data.%s = *val;\n", vn->c_str);
            } else {
                // Struct/enum: clone into inline storage
                fprintf(f, "    { %s _tmp = %s_clone(val); r->data.%s = *_tmp; free(_tmp); }\n",
                        type_name_to_c(vt), vt->c_str, vn->c_str);
            }
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // is_Variant functions
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, i);
            fprintf(f, "Bool *%s_is_%s(%s *self) {\n", name->c_str, vn->c_str, name->c_str);
            fprintf(f, "    Bool *r = malloc(sizeof(Bool));\n");
            fprintf(f, "    *r = (self->tag == %s_TAG_%s);\n", name->c_str, vn->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n");
        }

        // get_Variant functions (payload variants only)
        for (U32 i = 0; i < vnames.count; i++) {
            Str *vn = *(Str **)Vec_get(&vnames, i);
            Str *vt = *(Str **)Vec_get(&vtypes, i);
            if (!vt) continue;
            const char *ptype = type_name_to_c(vt);
            fprintf(f, "%s %s_get_%s(%s *self) {\n", ptype, name->c_str, vn->c_str, name->c_str);
            // Read from inline storage
            if (is_primitive_type(vt)) {
                fprintf(f, "    %s r = malloc(sizeof(%s)); *r = self->data.%s; return r;\n",
                        ptype, type_name_to_c_value(vt), vn->c_str);
            } else {
                // Struct/enum: clone from inline address
                fprintf(f, "    return %s_clone(&self->data.%s);\n", vt->c_str, vn->c_str);
            }
            fprintf(f, "}\n");
        }

        Vec_delete(&vnames);
        Vec_delete(&vtypes);
    }

    // Emit namespace func/proc methods (to_str, user methods)
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *field = expr_child(body, i);
        if (!field->data.decl.is_namespace) continue;
        if (expr_child(field, 0)->type != NODE_FUNC_DEF) continue;
        Expr *fdef = expr_child(field, 0);
        FuncType fft = fdef->data.func_def.func_type;
        if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
        // Emit size() as sizeof (same as struct_funcs)
        if (Str_eq_c(field->data.decl.name, "size") &&
            fdef->data.func_def.nparam == 0 &&
            fdef->data.func_def.return_type &&
            Str_eq_c(fdef->data.func_def.return_type, "I64")) {
            fprintf(f, "I64 *%s_size(void) {\n", name->c_str);
            fprintf(f, "    I64 *r = malloc(sizeof(I64));\n");
            fprintf(f, "    *r = (I64)sizeof(%s);\n", name->c_str);
            fprintf(f, "    return r;\n");
            fprintf(f, "}\n\n");
            continue;
        }
        char full_name_buf[256];
        snprintf(full_name_buf, sizeof(full_name_buf), "%s_%s", name->c_str, field->data.decl.name->c_str);
        Str *full_name = Str_new(full_name_buf);
        emit_func_def(f, full_name, fdef, NULL);
        Str_delete(full_name);
        fprintf(f, "\n");
    }
}

I32 build(Expr *program, const Mode *mode, Bool run_tests, const char *path, const char *c_output_path) {
    (void)path;

    codegen_program = program;

    // Build struct body lookup map
    struct_bodies = Map_new(sizeof(Str *), sizeof(Expr *), str_ptr_cmp);
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            Map_set(&struct_bodies, &sname, &body);
        }
    }
    FILE *f = fopen(c_output_path, "w");
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", c_output_path);
        return 1;
    }

    fprintf(f, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdarg.h>\n#include \"ext.h\"\n\n");

    Bool is_script = !mode || !mode->decls_only;

    // Forward-declare all structs (skip core ext_structs and Str — ext.h provides)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            if (expr_child(stmt, 0)->is_ext && stmt->is_core) continue;
            if (Str_eq_c(stmt->data.decl.name, "Str") || Str_eq_c(stmt->data.decl.name, "Array")) continue;
            fprintf(f, "typedef struct %s %s;\n", stmt->data.decl.name->c_str, stmt->data.decl.name->c_str);
        }
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            Str *ename = stmt->data.decl.name;
            // Emit tag enum only; struct definition deferred to after struct typedefs
            Expr *ebody = expr_child(expr_child(stmt, 0), 0);
            fprintf(f, "typedef enum {\n");
            I32 tag = 0;
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *v = expr_child(ebody, j);
                if (v->data.decl.is_namespace) continue;
                if (tag > 0) fprintf(f, ",\n");
                fprintf(f, "    %s_TAG_%s", ename->c_str, v->data.decl.name->c_str);
                tag++;
            }
            fprintf(f, "\n} %s_tag;\n", ename->c_str);
            // Forward-declare enum struct
            fprintf(f, "typedef struct %s %s;\n", ename->c_str, ename->c_str);
        }
    }
    fprintf(f, "\n");

    // Forward-declare user-defined ext_func/ext_proc (skip core.til builtins)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->is_core) continue;
        if (stmt->type != NODE_DECL || expr_child(stmt, 0)->type != NODE_FUNC_DEF) continue;
        Expr *fdef = expr_child(stmt, 0);
        FuncType fft = fdef->data.func_def.func_type;
        if (fft != FUNC_EXT_FUNC && fft != FUNC_EXT_PROC) continue;
        if (fdef->data.func_def.return_type)
            fprintf(f, "%s%s(", type_name_to_c(fdef->data.func_def.return_type), func_to_c(stmt->data.decl.name));
        else
            fprintf(f, "void %s(", func_to_c(stmt->data.decl.name));
        emit_param_list(f, fdef, 0);
        fprintf(f, ");\n");
    }
    fprintf(f, "\n");

    // Forward-declare string/print helper functions (implementations after struct defs)
    fprintf(f, "static Str *Str_lit(const char *s, long long cap);\n");
    fprintf(f, "static void print_single(Str *s);\n");
    fprintf(f, "static void print_flush();\n\n");

    // Forward-declare all functions (namespace methods + top-level)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                                         expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            for (U32 j = 0; j < body->children.count; j++) {
                Expr *field = expr_child(body, j);
                if (!field->data.decl.is_namespace) continue;
                if (expr_child(field, 0)->type != NODE_FUNC_DEF) continue;
                Expr *fdef = expr_child(field, 0);
                FuncType fft = fdef->data.func_def.func_type;
                if ((fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) && stmt->is_core) continue;
                const char *ret = "void";
                if (fdef->data.func_def.return_type)
                    ret = type_name_to_c(fdef->data.func_def.return_type);
                fprintf(f, "%s %s_%s(", ret, sname->c_str, field->data.decl.name->c_str);
                emit_param_list(f, fdef, 1);
                fprintf(f, ");\n");
            }
        } else if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
            Expr *func_def = expr_child(stmt, 0);
            FuncType fft = func_def->data.func_def.func_type;
            if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) continue;
            Str *name = stmt->data.decl.name;
            Bool is_main = mode && mode->needs_main && Str_eq_c(name, "main");
            if (is_main) continue;
            const char *ret = "void";
            if (func_def->data.func_def.return_type)
                ret = type_name_to_c(func_def->data.func_def.return_type);
            fprintf(f, "%s %s(", ret, func_to_c(name));
            emit_param_list(f, func_def, 1);
            fprintf(f, ");\n");
        }
    }
    // Forward-declare enum ext methods (eq, constructors + payload methods)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            Str *sname = stmt->data.decl.name;
            Bool hp = enum_has_payloads(expr_child(stmt, 0));
            fprintf(f, "Bool *%s_eq(%s *, %s *);\n", sname->c_str, sname->c_str, sname->c_str);
            Expr *ebody = expr_child(expr_child(stmt, 0), 0);
            for (U32 j = 0; j < ebody->children.count; j++) {
                Expr *v = expr_child(ebody, j);
                if (v->data.decl.is_namespace) continue;
                if (hp) {
                    // is_Variant
                    fprintf(f, "Bool *%s_is_%s(%s *);\n", sname->c_str, v->data.decl.name->c_str, sname->c_str);
                }
                if (v->data.decl.explicit_type) {
                    // Payload constructor
                    fprintf(f, "%s *%s_%s(%s);\n", sname->c_str, sname->c_str,
                            v->data.decl.name->c_str, type_name_to_c(v->data.decl.explicit_type));
                    // get_Variant
                    fprintf(f, "%s %s_get_%s(%s *);\n",
                            type_name_to_c(v->data.decl.explicit_type),
                            sname->c_str, v->data.decl.name->c_str, sname->c_str);
                } else {
                    // Zero-arg constructor
                    fprintf(f, "%s *%s_%s();\n", sname->c_str, sname->c_str,
                            v->data.decl.name->c_str);
                }
            }
        }
    }
    fprintf(f, "\n");

    // Forward declarations for dyn_call dispatch functions
    {
        Vec dyn_methods = Vec_new(sizeof(DynCallInfo));
        collect_dyn_methods(program, &dyn_methods);
        for (U32 m = 0; m < dyn_methods.count; m++) {
            DynCallInfo *info = Vec_get(&dyn_methods, m);
            if (info->returns) {
                if (info->nargs == 1)
                    fprintf(f, "void *dyn_call_%s(Str *type_name, void *val);\n", info->method->c_str);
                else
                    fprintf(f, "void *dyn_call_%s(Str *type_name, void *val, void *arg2);\n", info->method->c_str);
            } else {
                if (info->nargs == 1)
                    fprintf(f, "void dyn_call_%s(Str *type_name, void *val);\n", info->method->c_str);
                else
                    fprintf(f, "void dyn_call_%s(Str *type_name, void *val, void *arg2);\n", info->method->c_str);
            }
        }
        fprintf(f, "\n");
        Vec_delete(&dyn_methods);
    }

    // Forward declarations for dyn_has_method dispatch functions
    {
        Vec has_methods = Vec_new(sizeof(Str *));
        collect_dyn_has_methods(program, &has_methods);
        for (U32 m = 0; m < has_methods.count; m++) {
            Str **method = Vec_get(&has_methods, m);
            fprintf(f, "Bool *dyn_has_%s(Str *type_name);\n", (*method)->c_str);
        }
        if (has_methods.count) fprintf(f, "\n");
        Vec_delete(&has_methods);
    }

    // Forward declarations for array/vec builtin helpers
    {
        Vec coll_infos = Vec_new(sizeof(CollectionInfo));
        collect_collection_builtins(program, &coll_infos);
        for (U32 i = 0; i < coll_infos.count; i++) {
            CollectionInfo *ci = Vec_get(&coll_infos, i);
            const char *prefix = ci->is_vec ? "vec" : "array";
            const char *ret = ci->is_vec ? "Vec" : "Array";
            fprintf(f, "%s *%s_of_%s(int count, ...);\n",
                    ret, prefix, ci->type_name->c_str);
        }
        if (coll_infos.count) fprintf(f, "\n");
        Vec_delete(&coll_infos);
    }

    // Emit struct + enum struct typedefs in source order (so payload types are defined first)
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            emit_struct_typedef(f, stmt->data.decl.name, expr_child(stmt, 0), stmt->is_core);
            fprintf(f, "\n");
        }
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            Str *ename = stmt->data.decl.name;
            Expr *ebody = expr_child(expr_child(stmt, 0), 0);
            Bool hp = enum_has_payloads(expr_child(stmt, 0));
            fprintf(f, "struct %s {\n", ename->c_str);
            fprintf(f, "    %s_tag tag;\n", ename->c_str);
            if (hp) {
                fprintf(f, "    union {\n");
                for (U32 j = 0; j < ebody->children.count; j++) {
                    Expr *v = expr_child(ebody, j);
                    if (v->data.decl.is_namespace) continue;
                    if (v->data.decl.explicit_type) {
                        fprintf(f, "        %s %s;\n",
                                type_name_to_c_value(v->data.decl.explicit_type),
                                v->data.decl.name->c_str);
                    }
                }
                fprintf(f, "    } data;\n");
            }
            fprintf(f, "};\n\n");
        }
    }

    // String helper functions (after all struct typedefs so Str is complete)
    fprintf(f, "__attribute__((unused))\n");
    fprintf(f, "#define TIL_CAP_LIT (-1LL)\n");
    fprintf(f, "static Str *Str_lit(const char *s, long long len) {\n");
    fprintf(f, "    Str *r = malloc(sizeof(Str));\n");
    fprintf(f, "    r->data = (U8 *)s;\n");
    fprintf(f, "    r->count = len;\n");
    fprintf(f, "    r->cap = TIL_CAP_LIT;\n");
    fprintf(f, "    return r;\n");
    fprintf(f, "}\n");
    fprintf(f, "__attribute__((unused))\n");
    fprintf(f, "static void print_single(Str *s) {\n");
    fprintf(f, "    fwrite(s->data, 1, (size_t)s->count, stdout);\n");
    fprintf(f, "}\n");
    fprintf(f, "__attribute__((unused))\n");
    fprintf(f, "static void print_flush() {\n");
    fprintf(f, "    putchar('\\n');\n");
    fprintf(f, "}\n\n");

    // Emit top-level variable declarations as file-scope globals
    // so they're accessible from functions/procs defined at the same level
    {
        script_globals = Set_new(sizeof(Str *), str_ptr_cmp);
        has_script_globals = 1;
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = expr_child(program, i);
            if (stmt->type != NODE_DECL) continue;
            Expr *rhs = expr_child(stmt, 0);
            if (rhs->type == NODE_FUNC_DEF || rhs->type == NODE_STRUCT_DEF ||
                rhs->type == NODE_ENUM_DEF) continue;
            if (stmt->data.decl.is_ref) continue;
            const char *ctype = c_type_name(stmt->til_type, rhs->struct_name);
            fprintf(f, "static %s *%s;\n", ctype, stmt->data.decl.name->c_str);
            Set_add(&script_globals, &stmt->data.decl.name);
        }
        fprintf(f, "\n");
    }

    // Emit all function bodies: struct namespace, enum, top-level
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_STRUCT_DEF) {
            emit_struct_funcs(f, stmt->data.decl.name, expr_child(stmt, 0));
        } else if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
            emit_enum_def(f, stmt->data.decl.name, expr_child(stmt, 0));
            fprintf(f, "\n");
        } else if (stmt->type == NODE_DECL && expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
            FuncType fft2 = expr_child(stmt, 0)->data.func_def.func_type;
            if (fft2 == FUNC_EXT_FUNC || fft2 == FUNC_EXT_PROC) continue;
            emit_func_def(f, stmt->data.decl.name, expr_child(stmt, 0), mode);
            fprintf(f, "\n");
        }
    }

    // Emit dyn_call dispatch function bodies
    {
        Vec dyn_methods = Vec_new(sizeof(DynCallInfo));
        collect_dyn_methods(program, &dyn_methods);
        for (U32 m = 0; m < dyn_methods.count; m++) {
            DynCallInfo *info = Vec_get(&dyn_methods, m);
            Str *method = info->method;
            const char *ret_type = info->returns ? "void *" : "void ";
            if (info->nargs == 1)
                fprintf(f, "%sdyn_call_%s(Str *type_name, void *val) {\n", ret_type, method->c_str);
            else
                fprintf(f, "%sdyn_call_%s(Str *type_name, void *val, void *arg2) {\n", ret_type, method->c_str);
            // Iterate all struct/type defs in AST
            for (U32 i = 0; i < program->children.count; i++) {
                Expr *stmt = expr_child(program, i);
                if (stmt->type != NODE_DECL) continue;
                Expr *def = expr_child(stmt, 0);
                if (def->type != NODE_STRUCT_DEF && def->type != NODE_ENUM_DEF) continue;
                Str *tname = stmt->data.decl.name;
                // Check if this type has the method in its namespace
                Expr *body = expr_child(def, 0);
                Bool has_method = 0;
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = expr_child(body, j);
                    if (field->data.decl.is_namespace &&
                        Str_eq(field->data.decl.name, method)) {
                        has_method = 1;
                        break;
                    }
                }
                if (!has_method) continue;
                if (info->nargs == 2) {
                    if (info->returns)
                        fprintf(f, "    if (type_name->count == %lld && memcmp(type_name->data, \"%s\", %lld) == 0) return (void *)%s_%s(val, arg2);\n",
                                (long long)tname->count, tname->c_str, (long long)tname->count, tname->c_str, method->c_str);
                    else
                        fprintf(f, "    if (type_name->count == %lld && memcmp(type_name->data, \"%s\", %lld) == 0) { %s_%s(val, arg2); return; }\n",
                                (long long)tname->count, tname->c_str, (long long)tname->count, tname->c_str, method->c_str);
                } else {
                    if (info->returns)
                        fprintf(f, "    if (type_name->count == %lld && memcmp(type_name->data, \"%s\", %lld) == 0) return (void *)%s_%s(val);\n",
                                (long long)tname->count, tname->c_str, (long long)tname->count, tname->c_str, method->c_str);
                    else
                        fprintf(f, "    if (type_name->count == %lld && memcmp(type_name->data, \"%s\", %lld) == 0) { %s_%s(val); return; }\n",
                                (long long)tname->count, tname->c_str, (long long)tname->count, tname->c_str, method->c_str);
                }
            }
            fprintf(f, "    fprintf(stderr, \"dyn_call: unknown type for %s\\n\");\n", method->c_str);
            fprintf(f, "    exit(1);\n");
            fprintf(f, "}\n\n");
        }
        Vec_delete(&dyn_methods);
    }

    // Emit dyn_has_method dispatch function bodies
    {
        Vec has_methods = Vec_new(sizeof(Str *));
        collect_dyn_has_methods(program, &has_methods);
        for (U32 m = 0; m < has_methods.count; m++) {
            Str **method_ptr = Vec_get(&has_methods, m);
            Str *method = *method_ptr;
            fprintf(f, "Bool *dyn_has_%s(Str *type_name) {\n    (void)type_name;\n", method->c_str);
            for (U32 i = 0; i < program->children.count; i++) {
                Expr *stmt = expr_child(program, i);
                if (stmt->type != NODE_DECL) continue;
                Expr *def = expr_child(stmt, 0);
                if (def->type != NODE_STRUCT_DEF && def->type != NODE_ENUM_DEF) continue;
                Str *tname = stmt->data.decl.name;
                Expr *body = expr_child(def, 0);
                Bool found = 0;
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *field = expr_child(body, j);
                    if (field->data.decl.is_namespace &&
                        Str_eq(field->data.decl.name, method)) {
                        found = 1;
                        break;
                    }
                }
                if (!found) continue;
                fprintf(f, "    if (type_name->count == %lld && memcmp(type_name->data, \"%s\", %lld) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }\n",
                        (long long)tname->count, tname->c_str, (long long)tname->count);
            }
            fprintf(f, "    Bool *r = malloc(sizeof(Bool)); *r = 0; return r;\n");
            fprintf(f, "}\n\n");
        }
        Vec_delete(&has_methods);
    }

    // Emit array/vec builtin helper function bodies
    {
        Vec coll_infos = Vec_new(sizeof(CollectionInfo));
        collect_collection_builtins(program, &coll_infos);
        for (U32 i = 0; i < coll_infos.count; i++) {
            CollectionInfo *ci = Vec_get(&coll_infos, i);
            const char *et = ci->type_name->c_str;
            I64 et_len = ci->type_name->count;
            if (ci->is_vec) {
                fprintf(f, "Vec *vec_of_%s(int count, ...) {\n", et);
                fprintf(f, "    Str *_et = Str_lit(\"%s\", %lld);\n", et, (long long)et_len);
                fprintf(f, "    I64 *_esz = malloc(sizeof(I64)); *_esz = sizeof(%s);\n", et);
                fprintf(f, "    Vec *_v = Vec_new(_et, _esz);\n");
                fprintf(f, "    Str_delete(_et, &(Bool){1});\n");
                fprintf(f, "    I64_delete(_esz, &(Bool){1});\n");
                fprintf(f, "    va_list ap; va_start(ap, count);\n");
                fprintf(f, "    for (int _i = 0; _i < count; _i++) {\n");
                fprintf(f, "        %s *_val = %s_clone(va_arg(ap, %s *));\n", et, et, et);
                fprintf(f, "        Vec_push(_v, _val);\n");
                fprintf(f, "    }\n");
                fprintf(f, "    va_end(ap);\n");
                fprintf(f, "    return _v;\n");
                fprintf(f, "}\n\n");
            } else {
                fprintf(f, "Array *array_of_%s(int count, ...) {\n", et);
                fprintf(f, "    Str *_et = Str_lit(\"%s\", %lld);\n", et, (long long)et_len);
                fprintf(f, "    I64 *_esz = malloc(sizeof(I64)); *_esz = sizeof(%s);\n", et);
                fprintf(f, "    I64 *_cap = malloc(sizeof(I64)); *_cap = count;\n");
                fprintf(f, "    Array *_a = Array_new(_et, _esz, _cap);\n");
                fprintf(f, "    Str_delete(_et, &(Bool){1});\n");
                fprintf(f, "    I64_delete(_esz, &(Bool){1});\n");
                fprintf(f, "    I64_delete(_cap, &(Bool){1});\n");
                fprintf(f, "    va_list ap; va_start(ap, count);\n");
                fprintf(f, "    for (int _i = 0; _i < count; _i++) {\n");
                fprintf(f, "        I64 *_idx = malloc(sizeof(I64)); *_idx = _i;\n");
                fprintf(f, "        %s *_val = %s_clone(va_arg(ap, %s *));\n", et, et, et);
                fprintf(f, "        Array_set(_a, _idx, _val);\n");
                fprintf(f, "        I64_delete(_idx, &(Bool){1});\n");
                fprintf(f, "    }\n");
                fprintf(f, "    va_end(ap);\n");
                fprintf(f, "    return _a;\n");
                fprintf(f, "}\n\n");
            }
        }
        Vec_delete(&coll_infos);
    }

    // Test runner: emit main() that calls all test functions
    if (run_tests) {
        fprintf(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        // Initialize top-level core variables (e.g. CAP_VIEW)
        if (has_script_globals) {
            for (U32 i = 0; i < codegen_program->children.count; i++) {
                Expr *gs = expr_child(codegen_program, i);
                if (gs->type != NODE_DECL) continue;
                Expr *rhs = expr_child(gs, 0);
                if (rhs->type == NODE_FUNC_DEF || rhs->type == NODE_STRUCT_DEF ||
                    rhs->type == NODE_ENUM_DEF) continue;
                emit_stmt(f, gs, 1);
            }
        }
        I32 test_count = 0;
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = expr_child(program, i);
            if (stmt->type != NODE_DECL) continue;
            Expr *rhs = expr_child(stmt, 0);
            if (rhs->type != NODE_FUNC_DEF) continue;
            if (rhs->data.func_def.func_type != FUNC_TEST) continue;
            Str *tname = stmt->data.decl.name;
            fprintf(f, "    %s();\n", tname->c_str);
            fprintf(f, "    fprintf(stderr, \"  pass: %%s\\n\", \"%s\");\n", tname->c_str);
            test_count++;
        }
        if (test_count == 0) {
            fprintf(f, "    fprintf(stderr, \"no tests found\\n\");\n");
        } else {
            fprintf(f, "    fprintf(stderr, \"%d/%d tests passed\\n\");\n",
                    test_count, test_count);
        }
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
    }

    // Script mode: wrap top-level statements in main()
    if (!run_tests && is_script) {
        fprintf(f, "int main(void) {\n");
        emit_ns_inits(f, 1);
        for (U32 i = 0; i < program->children.count; i++) {
            Expr *stmt = expr_child(program, i);
            // Skip func/proc/struct defs (already emitted above)
            if (stmt->type == NODE_DECL &&
                (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
                 expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                 expr_child(stmt, 0)->type == NODE_ENUM_DEF))
                continue;
            emit_stmt(f, stmt, 1);
        }
        fprintf(f, "    return 0;\n");
        fprintf(f, "}\n");
        Set_delete(&script_globals);
        has_script_globals = 0;
    }

    fclose(f);
    Map_delete(&struct_bodies);
    return 0;
}

I32 compile_c(const char *c_path, const char *bin_path, const char *ext_c_path, const char *user_c_path, const char *link_flags) {
    // Extract directory from ext_c_path for -I flag
    char ext_dir[256];
    const char *last_slash = strrchr(ext_c_path, '/');
    if (last_slash) {
        I32 dlen = (I32)(last_slash - ext_c_path);
        snprintf(ext_dir, sizeof(ext_dir), "%.*s", dlen, ext_c_path);
    } else {
        snprintf(ext_dir, sizeof(ext_dir), ".");
    }

    // Build the cc command
    const char *user_part = user_c_path ? user_c_path : "";
    const char *lf = link_flags ? link_flags : "";
    int len = snprintf(NULL, 0, "cc -Wall -Wextra -I%s -o %s %s %s %s%s",
                       ext_dir, bin_path, c_path, ext_c_path, user_part, lf);
    char *cmd = malloc(len + 1);
    snprintf(cmd, len + 1, "cc -Wall -Wextra -I%s -o %s %s %s %s%s",
             ext_dir, bin_path, c_path, ext_c_path, user_part, lf);

    int result = system(cmd);
    free(cmd);

    if (result != 0) {
        fprintf(stderr, "error: C compilation failed\n");
        return 1;
    }
    return 0;
}
