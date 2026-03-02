#include "typer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type scope (tracks variable types) ---

typedef struct {
    const char *name;
    TilType type;
    int is_proc; // -1 = not a function, 0 = func, 1 = proc
    int is_mut;
    int line;
    int col;
    int is_param; // 1 if this is a function parameter
    Expr *struct_def; // non-NULL if this is a struct type definition
    Expr *func_def;   // non-NULL if this is a func/proc definition
    int is_builtin;   // 1 if this is a builtin type (I64, Str, Bool, etc.)
    const char *struct_name; // for variables of struct type: which struct
} TypeBinding;

typedef struct TypeScope TypeScope;
struct TypeScope {
    TypeBinding *bindings;
    int len;
    int cap;
    TypeScope *parent;
};

static TypeScope *tscope_new(TypeScope *parent) {
    TypeScope *s = calloc(1, sizeof(TypeScope));
    s->parent = parent;
    return s;
}

static void tscope_free(TypeScope *s) {
    free(s->bindings);
    free(s);
}

static void tscope_set(TypeScope *s, const char *name, TilType type, int is_proc, int is_mut, int line, int col, int is_param) {
    for (int i = 0; i < s->len; i++) {
        if (strcmp(s->bindings[i].name, name) == 0) {
            s->bindings[i].type = type;
            s->bindings[i].is_proc = is_proc;
            s->bindings[i].is_mut = is_mut;
            s->bindings[i].line = line;
            s->bindings[i].col = col;
            s->bindings[i].is_param = is_param;
            return;
        }
    }
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(TypeBinding));
    }
    s->bindings[s->len++] = (TypeBinding){name, type, is_proc, is_mut, line, col, is_param, NULL, NULL, 0, NULL};
}

static TilType tscope_get(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].type;
            }
        }
    }
    return TIL_TYPE_UNKNOWN;
}

static int tscope_is_proc(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].is_proc;
            }
        }
    }
    return -1;
}

static TypeBinding *tscope_find(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return &cur->bindings[i];
            }
        }
    }
    return NULL;
}

static Expr *tscope_get_struct(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].struct_def;
            }
        }
    }
    return NULL;
}

static int tscope_is_mut(TypeScope *s, const char *name) {
    for (TypeScope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].is_mut;
            }
        }
    }
    return 0;
}

// --- Built-in function return types ---

static TilType builtin_return_type(const char *name) {
    if (strcmp(name, "add") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "sub") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "mul") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "div") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "mod") == 0)    return TIL_TYPE_I64;
    if (strcmp(name, "to_str") == 0) return TIL_TYPE_STR;
    if (strcmp(name, "println") == 0) return TIL_TYPE_NONE;
    if (strcmp(name, "print") == 0)   return TIL_TYPE_NONE;
    if (strcmp(name, "and") == 0)  return TIL_TYPE_BOOL;
    if (strcmp(name, "or") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "eq") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "lt") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "gt") == 0)   return TIL_TYPE_BOOL;
    if (strcmp(name, "not") == 0)  return TIL_TYPE_BOOL;
    if (strcmp(name, "exit") == 0) return TIL_TYPE_NONE;
    if (strcmp(name, "eq_str") == 0) return TIL_TYPE_BOOL;
    if (strcmp(name, "format") == 0) return TIL_TYPE_STR;
    return TIL_TYPE_UNKNOWN;
}

// Returns: 0 = func, 1 = proc, -1 = not a builtin
static int builtin_is_proc(const char *name) {
    if (strcmp(name, "println") == 0) return 1;
    if (strcmp(name, "print") == 0)   return 1;
    if (strcmp(name, "add") == 0)  return 0;
    if (strcmp(name, "sub") == 0)  return 0;
    if (strcmp(name, "mul") == 0)  return 0;
    if (strcmp(name, "div") == 0)  return 0;
    if (strcmp(name, "mod") == 0)  return 0;
    if (strcmp(name, "to_str") == 0) return 0;
    if (strcmp(name, "and") == 0)  return 0;
    if (strcmp(name, "or") == 0)   return 0;
    if (strcmp(name, "eq") == 0)   return 0;
    if (strcmp(name, "lt") == 0)   return 0;
    if (strcmp(name, "gt") == 0)   return 0;
    if (strcmp(name, "not") == 0)  return 0;
    if (strcmp(name, "exit") == 0) return 0;
    if (strcmp(name, "eq_str") == 0) return 0;
    if (strcmp(name, "format") == 0) return 0;
    return -1;
}

// --- Type inference/checking pass ---

static int errors;

static void type_error(const char *path, Expr *e, const char *msg) {
    fprintf(stderr, "%s:%d:%d: type error: %s\n", path, e->line, e->col, msg);
    errors++;
}

// Parse a type name string to TilType (scope-aware for user-defined struct types)
static TilType type_from_name(const char *name, TypeScope *scope) {
    if (strcmp(name, "I64") == 0)  return TIL_TYPE_I64;
    if (strcmp(name, "Str") == 0)  return TIL_TYPE_STR;
    if (strcmp(name, "Bool") == 0) return TIL_TYPE_BOOL;
    if (strcmp(name, "StructDef") == 0)    return TIL_TYPE_STRUCT_DEF;
    if (strcmp(name, "FunctionDef") == 0)  return TIL_TYPE_FUNC_DEF;
    // Check scope for user-defined struct types
    if (scope) {
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return TIL_TYPE_STRUCT;
    }
    return TIL_TYPE_UNKNOWN;
}

static void infer_expr(TypeScope *scope, Expr *e, const char *path, int in_func);
static void infer_body(TypeScope *scope, Expr *body, const char *path, int in_func);

static void infer_expr(TypeScope *scope, Expr *e, const char *path, int in_func) {
    switch (e->type) {
    case NODE_LITERAL_STR:
        e->til_type = TIL_TYPE_STR;
        break;
    case NODE_LITERAL_NUM:
        e->til_type = TIL_TYPE_I64;
        break;
    case NODE_LITERAL_BOOL:
        e->til_type = TIL_TYPE_BOOL;
        break;
    case NODE_IDENT: {
        TilType t = tscope_get(scope, e->data.str_val);
        if (t == TIL_TYPE_UNKNOWN) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined symbol '%s'", e->data.str_val);
            type_error(path, e, buf);
        }
        e->til_type = t;
        if (t == TIL_TYPE_STRUCT) {
            TypeBinding *b = tscope_find(scope, e->data.str_val);
            if (b) e->struct_name = b->struct_name;
        }
        break;
    }
    case NODE_FUNC_DEF:
        e->til_type = TIL_TYPE_NONE;
        // Type the body
        {
            int is_func = (e->data.func_def.func_type == FUNC_FUNC);
            TypeScope *func_scope = tscope_new(scope);
            // Bind parameters
            for (int i = 0; i < e->data.func_def.nparam; i++) {
                const char *ptn = e->data.func_def.param_types[i];
                TilType pt = type_from_name(ptn, scope);
                if (pt == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", ptn);
                    type_error(path, e, buf);
                }
                tscope_set(func_scope, e->data.func_def.param_names[i], pt, -1, 0, e->line, e->col, 1);
                // For struct-typed params, store struct_name
                if (pt == TIL_TYPE_STRUCT) {
                    TypeBinding *pb = tscope_find(func_scope, e->data.func_def.param_names[i]);
                    if (pb) pb->struct_name = ptn;
                }
            }
            infer_body(func_scope, e->children[0], path, is_func);
            // Check: func must have a return type
            if (is_func && !e->data.func_def.return_type) {
                type_error(path, e, "func must declare a return type");
            }
            tscope_free(func_scope);
        }
        break;
    case NODE_STRUCT_DEF:
        e->til_type = TIL_TYPE_NONE;
        // Type-check field declarations
        infer_body(scope, e->children[0], path, 0);
        break;
    case NODE_FCALL: {
        // Resolve callee
        const char *name = e->children[0]->data.str_val;
        // Struct instantiation: Point() or Point(x=1, y=2)
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) {
            TypeBinding *sb = tscope_find(scope, name);
            if (sb && sb->is_builtin) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name);
                type_error(path, e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            Expr *body = sdef->children[0];
            int nfields = body->nchildren;
            // Desugar named args into positional (one per field)
            Expr **field_vals = calloc(nfields, sizeof(Expr *));
            for (int i = 1; i < e->nchildren; i++) {
                Expr *arg = e->children[i];
                if (arg->type != NODE_NAMED_ARG) {
                    type_error(path, arg, "struct instantiation requires named arguments");
                    continue;
                }
                const char *aname = arg->data.str_val;
                int slot = -1;
                for (int j = 0; j < nfields; j++) {
                    if (strcmp(body->children[j]->data.decl.name, aname) == 0) {
                        slot = j;
                        break;
                    }
                }
                if (slot < 0) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'", name, aname);
                    type_error(path, arg, buf);
                } else if (field_vals[slot]) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "duplicate argument for field '%s'", aname);
                    type_error(path, arg, buf);
                } else {
                    field_vals[slot] = arg->children[0]; // unwrap NODE_NAMED_ARG
                }
            }
            // Fill remaining from struct field defaults
            for (int i = 0; i < nfields; i++) {
                if (!field_vals[i]) {
                    field_vals[i] = body->children[i]->children[0];
                }
            }
            // Rebuild children: callee + field values
            Expr **new_children = malloc((nfields + 1) * sizeof(Expr *));
            new_children[0] = e->children[0]; // callee
            for (int i = 0; i < nfields; i++) {
                new_children[i + 1] = field_vals[i];
            }
            free(e->children);
            e->children = new_children;
            e->nchildren = nfields + 1;
            free(field_vals);
            // Type-check args
            for (int i = 1; i < e->nchildren; i++) {
                infer_expr(scope, e->children[i], path, in_func);
            }
            e->til_type = TIL_TYPE_STRUCT;
            e->struct_name = name;
            break;
        }
        // Desugar named/optional args for user-defined functions
        TypeBinding *callee_bind = tscope_find(scope, name);
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            int nparam = fdef->data.func_def.nparam;
            // Build new args array (slot per param)
            Expr **new_args = calloc(nparam, sizeof(Expr *));
            int pos_idx = 0;
            int seen_named = 0;
            for (int i = 1; i < e->nchildren; i++) {
                Expr *arg = e->children[i];
                if (arg->type == NODE_NAMED_ARG) {
                    seen_named = 1;
                    const char *aname = arg->data.str_val;
                    int slot = -1;
                    for (int j = 0; j < nparam; j++) {
                        if (strcmp(fdef->data.func_def.param_names[j], aname) == 0) {
                            slot = j;
                            break;
                        }
                    }
                    if (slot < 0) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' has no parameter '%s'", name, aname);
                        type_error(path, arg, buf);
                    } else if (new_args[slot]) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname);
                        type_error(path, arg, buf);
                    } else {
                        new_args[slot] = arg->children[0]; // unwrap NODE_NAMED_ARG
                    }
                } else {
                    if (seen_named) {
                        type_error(path, arg, "positional argument after named argument");
                    }
                    if (pos_idx < nparam) {
                        new_args[pos_idx] = arg;
                    }
                    pos_idx++;
                }
            }
            // Fill defaults for missing args
            for (int i = 0; i < nparam; i++) {
                if (!new_args[i]) {
                    if (fdef->data.func_def.param_defaults &&
                        fdef->data.func_def.param_defaults[i]) {
                        new_args[i] = fdef->data.func_def.param_defaults[i];
                    } else {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                 fdef->data.func_def.param_names[i]);
                        type_error(path, e, buf);
                    }
                }
            }
            if (pos_idx > nparam) {
                char buf[128];
                snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d",
                         nparam, pos_idx);
                type_error(path, e, buf);
            }
            // Rebuild children: callee + desugared args
            Expr **new_children = malloc((nparam + 1) * sizeof(Expr *));
            new_children[0] = e->children[0]; // callee
            for (int i = 0; i < nparam; i++) {
                new_children[i + 1] = new_args[i];
            }
            free(e->children);
            e->children = new_children;
            e->nchildren = nparam + 1;
            free(new_args);
        }
        // Infer types of all arguments
        for (int i = 1; i < e->nchildren; i++) {
            infer_expr(scope, e->children[i], path, in_func);
        }
        TilType ret = builtin_return_type(name);
        if (ret != TIL_TYPE_UNKNOWN) {
            e->til_type = ret;
            // Check: func cannot call a builtin proc (panic is exempt)
            if (in_func && builtin_is_proc(name) == 1 && strcmp(name, "panic") != 0) {
                char buf[128];
                snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name);
                type_error(path, e, buf);
            }
        } else {
            // User-defined function — look up in scope
            TilType fn_type = tscope_get(scope, name);
            if (fn_type == TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined function '%s'", name);
                type_error(path, e, buf);
            }
            e->til_type = fn_type;
            // Check: func cannot call a user-defined proc (panic is exempt)
            if (in_func && tscope_is_proc(scope, name) == 1 && strcmp(name, "panic") != 0) {
                char buf[128];
                snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name);
                type_error(path, e, buf);
            }
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        infer_expr(scope, e->children[0], path, in_func);
        Expr *obj = e->children[0];
        if (obj->til_type == TIL_TYPE_STRUCT && obj->struct_name) {
            Expr *sdef = tscope_get_struct(scope, obj->struct_name);
            if (sdef) {
                Expr *body = sdef->children[0];
                const char *fname = e->data.str_val;
                int found = 0;
                for (int i = 0; i < body->nchildren; i++) {
                    Expr *field = body->children[i];
                    if (strcmp(field->data.decl.name, fname) == 0) {
                        e->til_type = field->til_type;
                        e->struct_name = obj->struct_name;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                             obj->struct_name, fname);
                    type_error(path, e, buf);
                    e->til_type = TIL_TYPE_UNKNOWN;
                }
            }
        } else {
            type_error(path, e, "field access on non-struct value");
            e->til_type = TIL_TYPE_UNKNOWN;
        }
        break;
    }
    default:
        e->til_type = TIL_TYPE_UNKNOWN;
        break;
    }
}

static void infer_body(TypeScope *scope, Expr *body, const char *path, int in_func) {
    body->til_type = TIL_TYPE_NONE;
    for (int i = 0; i < body->nchildren; i++) {
        Expr *stmt = body->children[i];
        switch (stmt->type) {
        case NODE_DECL:
            infer_expr(scope, stmt->children[0], path, in_func);
            // For struct defs, register struct type in scope
            if (stmt->children[0]->type == NODE_STRUCT_DEF) {
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    if (declared != TIL_TYPE_STRUCT_DEF) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is StructDef",
                                 stmt->data.decl.name, stmt->data.decl.explicit_type);
                        type_error(path, stmt, buf);
                    }
                }
                stmt->til_type = TIL_TYPE_NONE;
                const char *sname = stmt->data.decl.name;
                // Check if this is a builtin type
                TilType builtin_type = TIL_TYPE_STRUCT;
                int is_builtin = 0;
                if (strcmp(sname, "I64") == 0)  { builtin_type = TIL_TYPE_I64;  is_builtin = 1; }
                else if (strcmp(sname, "Str") == 0)  { builtin_type = TIL_TYPE_STR;  is_builtin = 1; }
                else if (strcmp(sname, "Bool") == 0) { builtin_type = TIL_TYPE_BOOL; is_builtin = 1; }
                else if (strcmp(sname, "StructDef") == 0)    { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
                else if (strcmp(sname, "FunctionDef") == 0)  { builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }
                tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0);
                // Store struct def pointer and builtin flag in the binding
                TypeBinding *b = tscope_find(scope, sname);
                b->struct_def = stmt->children[0];
                b->is_builtin = is_builtin;
                break;
            }
            // For func/proc defs, store return type and func/proc-ness in scope
            if (stmt->children[0]->type == NODE_FUNC_DEF) {
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    if (declared != TIL_TYPE_FUNC_DEF) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is FunctionDef",
                                 stmt->data.decl.name, stmt->data.decl.explicit_type);
                        type_error(path, stmt, buf);
                    }
                }
                int callee_is_proc = (stmt->children[0]->data.func_def.func_type != FUNC_FUNC);
                TilType rt = TIL_TYPE_NONE;
                if (stmt->children[0]->data.func_def.return_type) {
                    rt = type_from_name(stmt->children[0]->data.func_def.return_type, scope);
                }
                stmt->til_type = rt;
                tscope_set(scope, stmt->data.decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0);
                // Store func_def pointer for named/optional arg desugaring
                TypeBinding *fb = tscope_find(scope, stmt->data.decl.name);
                if (fb) fb->func_def = stmt->children[0];
                break;
            }
            if (stmt->data.decl.explicit_type) {
                const char *etn = stmt->data.decl.explicit_type;
                TilType declared = type_from_name(etn, scope);
                if (declared == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", etn);
                    type_error(path, stmt, buf);
                } else if (stmt->children[0]->til_type != declared) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name, til_type_name(declared),
                             til_type_name(stmt->children[0]->til_type));
                    type_error(path, stmt, buf);
                } else if (declared == TIL_TYPE_STRUCT &&
                           stmt->children[0]->struct_name &&
                           strcmp(etn, stmt->children[0]->struct_name) != 0) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name, etn, stmt->children[0]->struct_name);
                    type_error(path, stmt, buf);
                }
                stmt->til_type = declared;
                // For struct types, propagate struct_name from explicit type
                if (declared == TIL_TYPE_STRUCT) {
                    stmt->children[0]->struct_name = etn;
                }
            } else {
                stmt->til_type = stmt->children[0]->til_type;
            }
            tscope_set(scope, stmt->data.decl.name, stmt->til_type, -1, stmt->data.decl.is_mut, stmt->line, stmt->col, 0);
            if (stmt->til_type == TIL_TYPE_STRUCT && stmt->children[0]->struct_name) {
                TypeBinding *b = tscope_find(scope, stmt->data.decl.name);
                if (b) b->struct_name = stmt->children[0]->struct_name;
            }
            break;
        case NODE_ASSIGN: {
            infer_expr(scope, stmt->children[0], path, in_func);
            stmt->til_type = stmt->children[0]->til_type;
            const char *aname = stmt->data.str_val;
            TilType existing = tscope_get(scope, aname);
            if (existing == TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined symbol '%s'", aname);
                type_error(path, stmt, buf);
            } else if (!tscope_is_mut(scope, aname)) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot assign to immutable variable '%s'", aname);
                type_error(path, stmt, buf);
                TypeBinding *b = tscope_find(scope, aname);
                if (b && b->is_param) {
                    fprintf(stderr, "%s:%d:%d: note: '%s' is a function parameter\n",
                            path, b->line, b->col, aname);
                } else if (b) {
                    fprintf(stderr, "%s:%d:%d: note: '%s' declared here, consider adding 'mut'\n",
                            path, b->line, b->col, aname);
                }
            } else if (stmt->children[0]->til_type != existing &&
                       stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'%s' is %s but assigned %s",
                         aname, til_type_name(existing),
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            break;
        }
        case NODE_FIELD_ASSIGN: {
            infer_expr(scope, stmt->children[0], path, in_func); // object
            infer_expr(scope, stmt->children[1], path, in_func); // value
            Expr *obj = stmt->children[0];
            const char *fname = stmt->data.str_val;
            if (obj->til_type == TIL_TYPE_STRUCT && obj->struct_name) {
                Expr *sdef = tscope_get_struct(scope, obj->struct_name);
                if (sdef) {
                    Expr *body = sdef->children[0];
                    int found = 0;
                    for (int i = 0; i < body->nchildren; i++) {
                        Expr *field = body->children[i];
                        if (strcmp(field->data.decl.name, fname) == 0) {
                            found = 1;
                            if (!field->data.decl.is_mut) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "cannot assign to immutable field '%s'", fname);
                                type_error(path, stmt, buf);
                            }
                            if (stmt->children[1]->til_type != field->til_type &&
                                stmt->children[1]->til_type != TIL_TYPE_UNKNOWN) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "field '%s' is %s but assigned %s",
                                         fname, til_type_name(field->til_type),
                                         til_type_name(stmt->children[1]->til_type));
                                type_error(path, stmt, buf);
                            }
                            break;
                        }
                    }
                    if (!found) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                                 obj->struct_name, fname);
                        type_error(path, stmt, buf);
                    }
                }
            } else {
                type_error(path, stmt, "field assignment on non-struct value");
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        }
        case NODE_FCALL:
            infer_expr(scope, stmt, path, in_func);
            break;
        case NODE_RETURN:
            if (stmt->nchildren > 0) {
                infer_expr(scope, stmt->children[0], path, in_func);
                stmt->til_type = stmt->children[0]->til_type;
            } else {
                stmt->til_type = TIL_TYPE_NONE;
            }
            break;
        case NODE_IF:
            infer_expr(scope, stmt->children[0], path, in_func); // condition
            if (stmt->children[0]->til_type != TIL_TYPE_BOOL &&
                stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            infer_body(scope, stmt->children[1], path, in_func); // then
            if (stmt->nchildren > 2) {
                infer_body(scope, stmt->children[2], path, in_func); // else
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_BODY: {
            TypeScope *block_scope = tscope_new(scope);
            infer_body(block_scope, stmt, path, in_func);
            tscope_free(block_scope);
            break;
        }
        case NODE_WHILE:
            infer_expr(scope, stmt->children[0], path, in_func); // condition
            if (stmt->children[0]->til_type != TIL_TYPE_BOOL &&
                stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            infer_body(scope, stmt->children[1], path, in_func); // body
            stmt->til_type = TIL_TYPE_NONE;
            break;
        default:
            stmt->til_type = TIL_TYPE_NONE;
            break;
        }
    }
}

int type_check(Expr *program, const char *path) {
    errors = 0;
    TypeScope *global = tscope_new(NULL);
    infer_body(global, program, path, 0);
    tscope_free(global);
    return errors;
}
