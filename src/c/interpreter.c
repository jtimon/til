#include "interpreter.h"
#include "dispatch.h"
#include "map.h"
#include "ccore.h"
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
    I32 len = sname->cap + 1 + fname->cap;
    char *buf = malloc(len + 1);
    snprintf(buf, len + 1, "%s.%s", sname->c_str, fname->c_str);
    Str *s = Str_new(buf);
    free(buf);
    Vec_push(&ns_keys, &s);
    return s;
}

Value *ns_get(Str *sname, Str *fname) {
    Str *qn = ns_qname(sname, fname);
    return Map_get(&ns_fields, &qn);
}

static void ns_set(Str *sname, Str *fname, Value val) {
    Str *qn = ns_qname(sname, fname);
    Map_set(&ns_fields, &qn, &val);
}

// --- Scope / environment ---

Scope *scope_new(Scope *parent) {
    Scope *s = malloc(sizeof(Scope));
    s->bindings = Map_new(sizeof(Str *), sizeof(Binding), str_ptr_cmp);
    s->parent = parent;
    return s;
}

void scope_free(Scope *s) {
    for (I32 i = 0; i < Map_len(&s->bindings); i++) {
        Binding *b = (Binding *)Vec_get(&s->bindings.vals, i);
        if (b->cell_is_local)
            free(b->cell);
    }
    Map_delete(&s->bindings);
    free(s);
}

void scope_set_owned(Scope *s, Str *name, Value val) {
    Binding *b = Map_get(&s->bindings, &name);
    if (b) {
        b->cell->val = val;
        return;
    }
    Cell *cell = malloc(sizeof(Cell));
    cell->val = val;
    Binding nb = {name, cell, 1};
    Map_set(&s->bindings, &name, &nb);
}

static void scope_set_borrowed(Scope *s, Str *name, Cell *cell) {
    Binding b = {name, cell, 0};
    Map_set(&s->bindings, &name, &b);
}

Cell *scope_get(Scope *s, Str *name) {
    for (Scope *cur = s; cur; cur = cur->parent) {
        Binding *b = Map_get(&cur->bindings, &name);
        if (b) return b->cell;
    }
    return NULL;
}

// ext_function_dispatch is in dispatch.c

// Deep-clone a Value (for payload enum operations and general use)
Value clone_value(Value v) {
    switch (v.type) {
    case VAL_I64:  return val_i64(*v.i64);
    case VAL_U8:   return val_u8(*v.u8);
    case VAL_STR:  return val_str(Str_clone(v.str));
    case VAL_BOOL: return val_bool(*v.boolean);
    case VAL_ENUM: return val_enum(v.enum_inst->enum_name, v.enum_inst->tag,
                                    clone_value(v.enum_inst->payload));
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
    case VAL_STR:  Str_delete(v.str); break;
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
    case VAL_U8:   return *a.u8 == *b.u8;
    case VAL_STR:  return Str_eq(a.str, b.str);
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
    if (callee_expr->type == NODE_FIELD_ACCESS) {
        Value fn_val = eval_expr(scope,callee_expr);
        if (fn_val.type != VAL_FUNC) {
            expr_error(e, "namespace field is not a function");
            exit(1);
        }
        Expr *func_def = fn_val.func;
        // Direct ext_func namespace method — dispatch by flat name
        FuncType fft = func_def->data.func_def.func_type;
        if (fft == FUNC_EXT_FUNC || fft == FUNC_EXT_PROC) {
            // Enum ext methods — delegated to dispatch.c
            Str *parent_sname = expr_child(callee_expr, 0)->struct_name;
            if (parent_sname) {
                Cell *tc = scope_get(scope, parent_sname);
                if (tc && tc->val.type == VAL_FUNC && tc->val.func->type == NODE_ENUM_DEF) {
                    Value eresult;
                    if (enum_method_dispatch(callee_expr->data.str_val, scope,
                            tc->val.func, parent_sname, e, &eresult)) {
                        // Null cells of own-arg idents
                        for (I32 i = 1; i < e->children.count; i++) {
                            if (expr_child(e, i)->type == NODE_IDENT && expr_child(e, i)->is_own_arg) {
                                Cell *c = scope_get(scope, expr_child(e, i)->data.str_val);
                                if (c) c->val = val_none();
                            }
                        }
                        return eresult;
                    }
                }
            }
            static char flat_name_buf[256];
            int flen = snprintf(flat_name_buf, sizeof(flat_name_buf), "%s_%s",
                     expr_child(callee_expr, 0)->struct_name->c_str, callee_expr->data.str_val->c_str);
            Str flat_str = {.c_str = flat_name_buf, .cap = flen};
            Expr *orig_callee = expr_child(e, 0);
            Expr flat_ident = *orig_callee;
            flat_ident.type = NODE_IDENT;
            flat_ident.data.str_val = &flat_str;
            expr_child(e, 0) = &flat_ident;
            Value result = eval_call(scope, e);
            expr_child(e, 0) = orig_callee;
            return result;
        }
        Expr *body = expr_child(func_def, 0);

        // Guard: skip call if first 'own' param is val_none (already moved/deleted)
        if (func_def->data.func_def.nparam > 0 &&
            func_def->data.func_def.param_owns &&
            func_def->data.func_def.param_owns[0] &&
            e->children.count > 1 && expr_child(e, 1)->type == NODE_IDENT) {
            Cell *fc = scope_get(scope, expr_child(e, 1)->data.str_val);
            if (fc && fc->val.type == VAL_NONE) return val_none();
        }

        Scope *call_scope = scope_new(scope);
        for (I32 i = 0; i < func_def->data.func_def.nparam; i++) {
            Expr *arg_expr = expr_child(e, i + 1);
            if (arg_expr->type == NODE_IDENT) {
                Cell *arg_cell = scope_get(scope, arg_expr->data.str_val);
                // Reinterpret VAL_PTR based on param type
                if (arg_cell->val.type == VAL_PTR && func_def->data.func_def.param_types[i]) {
                    Str *ptype = func_def->data.func_def.param_types[i];
                    Value arg = arg_cell->val;
                    if (Str_eq_c(ptype, "Str"))
                        arg = val_str((Str *)arg.ptr);
                    else if (Str_eq_c(ptype, "I64"))
                        arg = (Value){.type = VAL_I64, .i64 = (til_I64 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U8"))
                        arg = (Value){.type = VAL_U8, .u8 = (til_U8 *)arg.ptr};
                    else if (Str_eq_c(ptype, "Bool"))
                        arg = (Value){.type = VAL_BOOL, .boolean = (til_Bool *)arg.ptr};
                    scope_set_owned(call_scope, func_def->data.func_def.param_names[i], arg);
                } else {
                    scope_set_borrowed(call_scope, func_def->data.func_def.param_names[i], arg_cell);
                }
            } else {
                Value arg = eval_expr(scope,arg_expr);
                // Reinterpret VAL_PTR based on param type (same as ref decl)
                if (arg.type == VAL_PTR && func_def->data.func_def.param_types[i]) {
                    Str *ptype = func_def->data.func_def.param_types[i];
                    if (Str_eq_c(ptype, "Str"))
                        arg = val_str((Str *)arg.ptr);
                    else if (Str_eq_c(ptype, "I64"))
                        arg = (Value){.type = VAL_I64, .i64 = (til_I64 *)arg.ptr};
                    else if (Str_eq_c(ptype, "U8"))
                        arg = (Value){.type = VAL_U8, .u8 = (til_U8 *)arg.ptr};
                    else if (Str_eq_c(ptype, "Bool"))
                        arg = (Value){.type = VAL_BOOL, .boolean = (til_Bool *)arg.ptr};
                }
                scope_set_owned(call_scope, func_def->data.func_def.param_names[i], arg);
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

    Str *name = callee_expr->data.str_val;

    // Ext function dispatch
    Value ext_result;
    if (ext_function_dispatch(name, scope, e, &ext_result)) {
        // Null cells of own-arg idents (ext dispatch evaluates by value, not borrowed cell)
        for (I32 i = 1; i < e->children.count; i++) {
            if (expr_child(e, i)->type == NODE_IDENT && expr_child(e, i)->is_own_arg) {
                Cell *c = scope_get(scope, expr_child(e, i)->data.str_val);
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
    if (fn_cell->val.type == VAL_FUNC && fn_cell->val.func->type == NODE_STRUCT_DEF) {
        Expr *sdef = fn_cell->val.func;
        Expr *body = expr_child(sdef, 0);

        // Str() constructor: create VAL_STR from data + cap args
        if (Str_eq_c(name, "Str")) {
            // Str has 2 non-namespace fields: data, cap
            // arg 1 = data (VAL_PTR), arg 2 = cap (VAL_I64)
            Value data_val, cap_val;
            Expr *data_arg = expr_child(e, 1);
            Expr *cap_arg = expr_child(e, 2);
            if (data_arg->type == NODE_IDENT) {
                Cell *src = scope_get(scope, data_arg->data.str_val);
                data_val = src->val;
                src->val = val_none();
            } else {
                data_val = eval_expr(scope,data_arg);
            }
            if (cap_arg->type == NODE_IDENT) {
                Cell *src = scope_get(scope, cap_arg->data.str_val);
                cap_val = src->val;
                src->val = val_none();
            } else {
                cap_val = eval_expr(scope,cap_arg);
            }
            Str *s = malloc(sizeof(Str));
            // Extract raw pointer from data_val (could be VAL_PTR or reinterpreted VAL_U8 etc)
            switch (data_val.type) {
                case VAL_PTR:  s->c_str = (char *)data_val.ptr; break;
                case VAL_U8:   s->c_str = (char *)data_val.u8; break;
                case VAL_I64:  s->c_str = (char *)data_val.i64; break;
                default:       s->c_str = NULL; break;
            }
            s->cap = (I32)*cap_val.i64;
            return val_str(s);
        }

        I32 nfields = 0;
        for (I32 i = 0; i < body->children.count; i++)
            if (!expr_child(body, i)->data.decl.is_namespace) nfields++;
        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = name;
        inst->nfields = nfields;
        inst->field_names = malloc(nfields * sizeof(Str *));
        inst->field_muts = malloc(nfields * sizeof(I32));
        inst->field_values = malloc(nfields * sizeof(Value));
        I32 arg_idx = 1;
        I32 fi = 0;
        for (I32 i = 0; i < body->children.count; i++) {
            Expr *field = expr_child(body, i);
            if (field->data.decl.is_namespace) continue;
            inst->field_names[fi] = field->data.decl.name;
            inst->field_muts[fi] = field->data.decl.is_mut;
            Expr *arg = expr_child(e, arg_idx++);
            if (arg->type == NODE_IDENT) {
                // Move semantics: struct takes ownership of ident's value
                Cell *src = scope_get(scope, arg->data.str_val);
                inst->field_values[fi] = src->val;
                src->val = val_none();
            } else {
                inst->field_values[fi] = eval_expr(scope,arg);
            }
            fi++;
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

    // Guard: skip call if first 'own' param is val_none (already moved/deleted)
    if (func_def->data.func_def.nparam > 0 &&
        func_def->data.func_def.param_owns &&
        func_def->data.func_def.param_owns[0] &&
        e->children.count > 1 && expr_child(e, 1)->type == NODE_IDENT) {
        Cell *fc = scope_get(scope, expr_child(e, 1)->data.str_val);
        if (fc && fc->val.type == VAL_NONE) return val_none();
    }

    Scope *call_scope = scope_new(scope);
    // Bind arguments to parameters (borrowed refs for idents, owned for expressions)
    I32 nparam = func_def->data.func_def.nparam;
    for (I32 i = 0; i < nparam; i++) {
        Expr *arg_expr = expr_child(e, i + 1);
        if (arg_expr->type == NODE_IDENT) {
            Cell *arg_cell = scope_get(scope, arg_expr->data.str_val);
            scope_set_borrowed(call_scope, func_def->data.func_def.param_names[i], arg_cell);
        } else {
            Value arg = eval_expr(scope, arg_expr);
            scope_set_owned(call_scope, func_def->data.func_def.param_names[i], arg);
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
    switch (e->type) {
    case NODE_LITERAL_STR:
        return val_str(Str_clone(e->data.str_val));
    case NODE_LITERAL_NUM:
        if (e->til_type == TIL_TYPE_U8)
            return val_u8(atoll(e->data.str_val->c_str));
        return val_i64(atoll(e->data.str_val->c_str));
    case NODE_LITERAL_BOOL:
        return val_bool(Str_eq_c(e->data.str_val, "true"));
    case NODE_IDENT: {
        Cell *cell = scope_get(scope, e->data.str_val);
        if (!cell) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined variable '%s'", e->data.str_val->c_str);
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
        Str *fname = e->data.str_val;
        if (e->is_ns_field) {
            Str *sname = obj.type == VAL_STRUCT
                ? obj.instance->struct_name : expr_child(e, 0)->data.str_val;
            Value *nsv = ns_get(sname, fname);
            if (nsv) {
                // Fresh copy of scalar values (simple enum variant safety)
                if (nsv->type == VAL_I64) return val_i64(*nsv->i64);
                // Auto-call zero-arg enum constructors (Token.Eof without parens)
                if (nsv->type == VAL_FUNC && nsv->func &&
                    nsv->func->type == NODE_FUNC_DEF &&
                    nsv->func->data.func_def.func_type == FUNC_EXT_FUNC &&
                    nsv->func->data.func_def.nparam == 0) {
                    Cell *tc = scope_get(scope, sname);
                    if (tc && tc->val.type == VAL_FUNC && tc->val.func->type == NODE_ENUM_DEF) {
                        I32 tag = enum_variant_tag(tc->val.func, fname);
                        if (tag >= 0) {
                            if (enum_has_payloads(tc->val.func))
                                return val_enum(sname, tag, val_none());
                            else
                                return val_i64(tag);
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
        // VAL_STR field access: .data → VAL_PTR, .cap → VAL_I64
        if (obj.type == VAL_STR) {
            if (Str_eq_c(fname, "data"))
                return (Value){.type = VAL_PTR, .ptr = obj.str->c_str};
            if (Str_eq_c(fname, "cap"))
                return val_i64(obj.str->cap);
            char buf[128];
            snprintf(buf, sizeof(buf), "Str has no field '%s'", fname->c_str);
            expr_error(e, buf);
            exit(1);
        }
        if (obj.type != VAL_STRUCT) {
            expr_error(e, "field access on non-struct");
            exit(1);
        }
        for (I32 i = 0; i < obj.instance->nfields; i++) {
            if (Str_eq(obj.instance->field_names[i], fname)) {
                Value fv = obj.instance->field_values[i];
                // Clone primitives to avoid shared heap pointers;
                // structs/ptrs must stay as-is for chained access
                if (fv.type == VAL_I64 || fv.type == VAL_U8 ||
                    fv.type == VAL_BOOL || fv.type == VAL_STR)
                    return clone_value(fv);
                return fv;
            }
        }
        char buf[128];
        snprintf(buf, sizeof(buf), "no field '%s'", fname->c_str);
        expr_error(e, buf);
        exit(1);
    }
    default:
        char buf[128];
        snprintf(buf, sizeof(buf), "cannot evaluate node type %d as expression", e->type);
        expr_lang_error(e, buf);
        exit(1);
    }
}

static void eval_body(Scope *scope, Expr *body) {
    for (I32 i = 0; i < body->children.count; i++) {
        if (has_return || has_break || has_continue) return;
        Expr *stmt = expr_child(body, i);
        switch (stmt->type) {
        case NODE_DECL: {
            Expr *rhs = expr_child(stmt, 0);
            if (stmt->data.decl.is_ref && rhs->type == NODE_IDENT) {
                // Ref decl from ident: borrow the same cell (no move, no free)
                Cell *src = scope_get(scope, rhs->data.str_val);
                scope_set_borrowed(scope, stmt->data.decl.name, src);
            } else {
                Value val;
                if (rhs->type == NODE_IDENT) {
                    // Move semantics: transfer value from source, null source
                    Cell *src = scope_get(scope, rhs->data.str_val);
                    if (!src) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "undefined variable '%s'", rhs->data.str_val->c_str);
                        expr_error(rhs, buf);
                        exit(1);
                    }
                    val = src->val;
                    src->val = val_none();
                } else {
                    val = eval_expr(scope,rhs);
                }
                // Reinterpret VAL_PTR based on declared type (ref a : I64 = ptr_add(...))
                if (val.type == VAL_PTR && stmt->data.decl.explicit_type) {
                    Str *etype = stmt->data.decl.explicit_type;
                    if (Str_eq_c(etype, "I64"))
                        val = (Value){.type = VAL_I64, .i64 = (til_I64 *)val.ptr};
                    else if (Str_eq_c(etype, "U8"))
                        val = (Value){.type = VAL_U8, .u8 = (til_U8 *)val.ptr};
                    else if (Str_eq_c(etype, "Bool"))
                        val = (Value){.type = VAL_BOOL, .boolean = (til_Bool *)val.ptr};
                    else if (Str_eq_c(etype, "Str"))
                        val = (Value){.type = VAL_STR, .str = (Str *)val.ptr};
                }
                scope_set_owned(scope, stmt->data.decl.name, val);
            }
            break;
        }
        case NODE_ASSIGN: {
            Expr *rhs = expr_child(stmt, 0);
            Cell *cell = scope_get(scope, stmt->data.str_val);
            if (!cell) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined variable '%s'", stmt->data.str_val->c_str);
                expr_error(stmt, buf);
                exit(1);
            }
            if (rhs->type == NODE_IDENT) {
                // Move semantics: transfer value from source, null source
                Cell *src = scope_get(scope, rhs->data.str_val);
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
            if (val_expr->type == NODE_IDENT) {
                // Move semantics: transfer value from source
                move_src = scope_get(scope, val_expr->data.str_val);
                val = move_src->val;
            } else {
                val = eval_expr(scope,val_expr);
            }
            Str *fname = stmt->data.str_val;
            if (stmt->is_ns_field) {
                Value obj = eval_expr(scope,expr_child(stmt, 0));
                Str *sname = obj.type == VAL_STRUCT
                    ? obj.instance->struct_name : expr_child(stmt, 0)->data.str_val;
                ns_set(sname, fname, val);
                if (move_src) move_src->val = val_none();
            } else {
                // Resolve the object to a mutable StructInstance without copying
                StructInstance *inst = NULL;
                Expr *obj_expr = expr_child(stmt, 0);
                if (obj_expr->type == NODE_IDENT) {
                    Cell *cell = scope_get(scope, obj_expr->data.str_val);
                    if (cell && cell->val.type == VAL_STRUCT) inst = cell->val.instance;
                } else if (obj_expr->type == NODE_FIELD_ACCESS) {
                    // Chained: e.g. l1.start.x — resolve l1.start to its StructInstance
                    // Walk the chain: find root ident, then follow fields
                    Expr *chain[32]; I32 depth = 0;
                    Expr *cur = obj_expr;
                    while (cur->type == NODE_FIELD_ACCESS) {
                        chain[depth++] = cur;
                        cur = expr_child(cur, 0);
                    }
                    Cell *cell = scope_get(scope, cur->data.str_val);
                    if (cell && cell->val.type == VAL_STRUCT) {
                        inst = cell->val.instance;
                        for (I32 d = depth - 1; d >= 0; d--) {
                            Str *fn = chain[d]->data.str_val;
                            StructInstance *next = NULL;
                            for (I32 j = 0; j < inst->nfields; j++) {
                                if (Str_eq(inst->field_names[j], fn) &&
                                    inst->field_values[j].type == VAL_STRUCT) {
                                    next = inst->field_values[j].instance;
                                    break;
                                }
                            }
                            inst = next;
                            if (!inst) break;
                        }
                    }
                }
                if (!inst) {
                    expr_error(stmt, "field assign on non-struct");
                    exit(1);
                }
                for (I32 i = 0; i < inst->nfields; i++) {
                    if (Str_eq(inst->field_names[i], fname)) {
                        free_value(inst->field_values[i]);
                        inst->field_values[i] = val;
                        if (move_src) move_src->val = val_none();
                        break;
                    }
                }
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
            snprintf(buf, sizeof(buf), "unexpected statement type %d", stmt->type);
            expr_lang_error(stmt, buf);
            exit(1);
        }
    }
}

void interpreter_init_ns(Scope *global, Expr *program) {
    ns_fields = Map_new(sizeof(Str *), sizeof(Value), str_ptr_cmp);
    ns_keys = Vec_new(sizeof(Str *));
    for (I32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                                        expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Str *sname = stmt->data.decl.name;
            Expr *body = expr_child(expr_child(stmt, 0), 0);
            for (I32 j = 0; j < body->children.count; j++) {
                Expr *field = expr_child(body, j);
                if (field->data.decl.is_namespace) {
                    Value fval = eval_expr(global, expr_child(field, 0));
                    ns_set(sname, field->data.decl.name, fval);
                }
            }
        }
    }
}

static Value parse_cli_arg(const char *s, Str *type_name) {
    if (Str_eq_c(type_name, "Str")) return val_str(Str_new(s));
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
    if (Str_eq_c(type_name, "I64")) return (I32)sizeof(til_I64);
    if (Str_eq_c(type_name, "U8"))  return (I32)sizeof(til_U8);
    if (Str_eq_c(type_name, "Bool")) return (I32)sizeof(til_Bool);
    if (Str_eq_c(type_name, "Str")) return (I32)sizeof(Str);
    return 8;
}

static void value_to_buf(void *dest, Value v, Str *type_name) {
    if (Str_eq_c(type_name, "I64"))       { memcpy(dest, v.i64, sizeof(til_I64)); free(v.i64); }
    else if (Str_eq_c(type_name, "U8"))   { memcpy(dest, v.u8, sizeof(til_U8)); free(v.u8); }
    else if (Str_eq_c(type_name, "Bool")) { memcpy(dest, v.boolean, sizeof(til_Bool)); free(v.boolean); }
    else if (Str_eq_c(type_name, "Str"))  { memcpy(dest, v.str, sizeof(Str)); free(v.str); }
}

static Value build_argv_array(I32 argc, char **argv, Str *elem_type) {
    I32 esz = elem_size_for_type(elem_type);
    void *data = calloc(argc > 0 ? argc : 1, esz);
    for (I32 i = 0; i < argc; i++) {
        Value v = parse_cli_arg(argv[i], elem_type);
        value_to_buf((char *)data + i * esz, v, elem_type);
    }
    StructInstance *inst = malloc(sizeof(StructInstance));
    inst->struct_name = Str_new("Array");
    inst->nfields = 4;
    inst->field_names = malloc(4 * sizeof(Str *));
    inst->field_names[0] = Str_new("data");
    inst->field_names[1] = Str_new("cap");
    inst->field_names[2] = Str_new("elem_size");
    inst->field_names[3] = Str_new("elem_type");
    inst->field_muts = malloc(4 * sizeof(I32));
    inst->field_muts[0] = 1;
    inst->field_muts[1] = 0;
    inst->field_muts[2] = 0;
    inst->field_muts[3] = 0;
    inst->field_values = malloc(4 * sizeof(Value));
    inst->field_values[0] = (Value){.type = VAL_PTR, .ptr = data};
    inst->field_values[1] = val_i64(argc);
    inst->field_values[2] = val_i64(esz);
    inst->field_values[3] = val_str(Str_clone(elem_type));
    return (Value){.type = VAL_STRUCT, .instance = inst};
}

I32 interpret(Expr *program, Str *mode, const char *path, const char *user_c_path, const char *ext_c_path, I32 user_argc, char **user_argv) {
    // Load user FFI library if provided
    if (user_c_path) {
        I32 rc = ffi_init(program, user_c_path, ext_c_path);
        if (rc != 0) return rc;
    }

    Scope *global = scope_new(NULL);

    // Pre-register all top-level func/proc/struct definitions for forward references
    for (I32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL &&
            (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
             expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
             expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Value val = {.type = VAL_FUNC, .func = expr_child(stmt, 0)};
            scope_set_owned(global, stmt->data.decl.name, val);
        }
    }

    // Initialize namespace fields for all structs
    interpreter_init_ns(global, program);

    // Evaluate top-level declarations
    eval_body(global, program);

    // In cli mode, call main()
    if (mode && Str_eq_c(mode, "cli")) {
        Str main_name = {.c_str = (char *)"main", .cap = 4};
        Cell *main_cell = scope_get(global, &main_name);
        if (!main_cell || main_cell->val.type != VAL_FUNC) {
            fprintf(stderr, "%s: error: mode 'cli' requires a 'main' proc\n", path);
            scope_free(global);
            return 1;
        }
        Expr *func_def = main_cell->val.func;
        I32 nparam = func_def->data.func_def.nparam;
        I32 vi = func_def->data.func_def.variadic_index;
        Expr *body = expr_child(func_def, 0);
        Scope *main_scope = scope_new(global);

        // Bind CLI args to main params
        if (nparam > 0) {
            I32 fixed = (vi >= 0) ? nparam - 1 : nparam;
            if (vi >= 0) {
                // Variadic: need at least 'fixed' args
                if (user_argc < fixed) {
                    fprintf(stderr, "error: main expects at least %d argument(s), got %d\n", fixed, user_argc);
                    scope_free(main_scope);
                    scope_free(global);
                    return 1;
                }
            } else {
                if (user_argc != nparam) {
                    fprintf(stderr, "error: main expects %d argument(s), got %d\n", nparam, user_argc);
                    scope_free(main_scope);
                    scope_free(global);
                    return 1;
                }
            }
            I32 argi = 0;
            for (I32 i = 0; i < nparam; i++) {
                if (i == vi) {
                    I32 va_count = user_argc - fixed;
                    Value arr = build_argv_array(va_count, user_argv + argi, func_def->data.func_def.param_types[vi]);
                    scope_set_owned(main_scope, func_def->data.func_def.param_names[i], arr);
                    argi += va_count;
                } else {
                    Value v = parse_cli_arg(user_argv[argi], func_def->data.func_def.param_types[i]);
                    scope_set_owned(main_scope, func_def->data.func_def.param_names[i], v);
                    argi++;
                }
            }
        } else if (user_argc > 0) {
            fprintf(stderr, "error: main expects no arguments, got %d\n", user_argc);
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
