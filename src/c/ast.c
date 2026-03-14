#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// --- clone/delete for AST types ---
// Expr_clone does real deep cloning (typer shares AST nodes via no-op clone → broken codegen).
// Expr_delete is a no-op (typer inserts delete calls that can pass NULL; AST is never freed).
// TilType/Declaration/ExprData clone/delete: no-ops (only needed for FFI dispatch table).

TilType *TilType_clone(TilType *self) { return self; }
void TilType_delete(TilType *self, Bool *call_free) { (void)self; (void)call_free; }
Declaration *Declaration_clone(Declaration *self) { return self; }
void Declaration_delete(Declaration *self, Bool *call_free) { (void)self; (void)call_free; }
ExprData *ExprData_clone(ExprData *self) { return self; }
void ExprData_delete(ExprData *self, Bool *call_free) { (void)self; (void)call_free; }

Expr *Expr_clone(Expr *self) {
    if (!self) return NULL;
    Expr *c = calloc(1, sizeof(Expr));
    *c = *self;
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); c->children = *_vp; free(_vp); }
    for (U32 i = 0; i < self->children.count; i++) {
        Expr *cloned = Expr_clone(expr_child(self, i));
        Expr **_p = malloc(sizeof(Expr *)); *_p = cloned;
        Vec_push(&c->children, _p);
    }
    return c;
}

void Expr_delete(Expr *self, Bool *call_free) { (void)self; (void)call_free; }

// --- Functions matching ast.til signatures ---

Str *til_type_name_c(TilType *t) {
    switch (t->tag) {
    case TilType_TAG_Unknown: return Str_clone(&(Str){.c_str = (U8*)"unknown", .count = 7, .cap = CAP_LIT});
    case TilType_TAG_None:    return Str_clone(&(Str){.c_str = (U8*)"None", .count = 4, .cap = CAP_LIT});
    case TilType_TAG_I64:     return Str_clone(&(Str){.c_str = (U8*)"I64", .count = 3, .cap = CAP_LIT});
    case TilType_TAG_U8:      return Str_clone(&(Str){.c_str = (U8*)"U8", .count = 2, .cap = CAP_LIT});
    case TilType_TAG_I16:     return Str_clone(&(Str){.c_str = (U8*)"I16", .count = 3, .cap = CAP_LIT});
    case TilType_TAG_I32:     return Str_clone(&(Str){.c_str = (U8*)"I32", .count = 3, .cap = CAP_LIT});
    case TilType_TAG_U32:     return Str_clone(&(Str){.c_str = (U8*)"U32", .count = 3, .cap = CAP_LIT});
    case TilType_TAG_U64:     return Str_clone(&(Str){.c_str = (U8*)"U64", .count = 3, .cap = CAP_LIT});
    case TilType_TAG_F32:     return Str_clone(&(Str){.c_str = (U8*)"F32", .count = 3, .cap = CAP_LIT});
    case TilType_TAG_Bool:    return Str_clone(&(Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT});
    case TilType_TAG_Struct:      return Str_clone(&(Str){.c_str = (U8*)"Struct", .count = 6, .cap = CAP_LIT});
    case TilType_TAG_StructDef:  return Str_clone(&(Str){.c_str = (U8*)"StructDef", .count = 9, .cap = CAP_LIT});
    case TilType_TAG_Enum:        return Str_clone(&(Str){.c_str = (U8*)"Enum", .count = 4, .cap = CAP_LIT});
    case TilType_TAG_EnumDef:    return Str_clone(&(Str){.c_str = (U8*)"EnumDef", .count = 7, .cap = CAP_LIT});
    case TilType_TAG_FuncDef:    return Str_clone(&(Str){.c_str = (U8*)"FunctionDef", .count = 11, .cap = CAP_LIT});
    case TilType_TAG_FuncPtr:    return Str_clone(&(Str){.c_str = (U8*)"Fn", .count = 2, .cap = CAP_LIT});
    case TilType_TAG_Dynamic:     return Str_clone(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT});
    }
    return Str_clone(&(Str){.c_str = (U8*)"?", .count = 1, .cap = CAP_LIT});
}

Str *node_name(ExprData *data) {
    switch (data->tag) {
    case ExprData_TAG_Body:        return Str_clone(&(Str){.c_str = (U8*)"body", .count = 4, .cap = CAP_LIT});
    case ExprData_TAG_LiteralStr: return Str_clone(&(Str){.c_str = (U8*)"str", .count = 3, .cap = CAP_LIT});
    case ExprData_TAG_LiteralNum: return Str_clone(&(Str){.c_str = (U8*)"num", .count = 3, .cap = CAP_LIT});
    case ExprData_TAG_LiteralBool: return Str_clone(&(Str){.c_str = (U8*)"bool", .count = 4, .cap = CAP_LIT});
    case ExprData_TAG_LiteralNull: return Str_clone(&(Str){.c_str = (U8*)"null", .count = 4, .cap = CAP_LIT});
    case ExprData_TAG_Ident:       return Str_clone(&(Str){.c_str = (U8*)"ident", .count = 5, .cap = CAP_LIT});
    case ExprData_TAG_Decl:        return Str_clone(&(Str){.c_str = (U8*)"decl", .count = 4, .cap = CAP_LIT});
    case ExprData_TAG_Assign:      return Str_clone(&(Str){.c_str = (U8*)"assign", .count = 6, .cap = CAP_LIT});
    case ExprData_TAG_FCall:       return Str_clone(&(Str){.c_str = (U8*)"fcall", .count = 5, .cap = CAP_LIT});
    case ExprData_TAG_FuncDef:    return Str_clone(&(Str){.c_str = (U8*)"func_def", .count = 8, .cap = CAP_LIT});
    case ExprData_TAG_StructDef:  return Str_clone(&(Str){.c_str = (U8*)"struct_def", .count = 10, .cap = CAP_LIT});
    case ExprData_TAG_EnumDef:    return Str_clone(&(Str){.c_str = (U8*)"enum_def", .count = 8, .cap = CAP_LIT});
    case ExprData_TAG_FieldAccess: return Str_clone(&(Str){.c_str = (U8*)"field_access", .count = 12, .cap = CAP_LIT});
    case ExprData_TAG_FieldAssign: return Str_clone(&(Str){.c_str = (U8*)"field_assign", .count = 12, .cap = CAP_LIT});
    case ExprData_TAG_Return:      return Str_clone(&(Str){.c_str = (U8*)"return", .count = 6, .cap = CAP_LIT});
    case ExprData_TAG_If:          return Str_clone(&(Str){.c_str = (U8*)"if", .count = 2, .cap = CAP_LIT});
    case ExprData_TAG_While:       return Str_clone(&(Str){.c_str = (U8*)"while", .count = 5, .cap = CAP_LIT});
    case ExprData_TAG_ForIn:      return Str_clone(&(Str){.c_str = (U8*)"for_in", .count = 6, .cap = CAP_LIT});
    case ExprData_TAG_NamedArg:   return Str_clone(&(Str){.c_str = (U8*)"named_arg", .count = 9, .cap = CAP_LIT});
    case ExprData_TAG_Break:       return Str_clone(&(Str){.c_str = (U8*)"break", .count = 5, .cap = CAP_LIT});
    case ExprData_TAG_Continue:    return Str_clone(&(Str){.c_str = (U8*)"continue", .count = 8, .cap = CAP_LIT});
    case ExprData_TAG_MapLit:     return Str_clone(&(Str){.c_str = (U8*)"map_lit", .count = 7, .cap = CAP_LIT});
    case ExprData_TAG_SetLit:     return Str_clone(&(Str){.c_str = (U8*)"set_lit", .count = 7, .cap = CAP_LIT});
    case ExprData_TAG_Switch:      return Str_clone(&(Str){.c_str = (U8*)"switch", .count = 6, .cap = CAP_LIT});
    case ExprData_TAG_Case:        return Str_clone(&(Str){.c_str = (U8*)"case", .count = 4, .cap = CAP_LIT});
    }
    return Str_clone(&(Str){.c_str = (U8*)"?", .count = 1, .cap = CAP_LIT});
}

Str *func_type_name(FuncType *ft) {
    switch (ft->tag) {
    case FuncType_TAG_Func:     return Str_clone(&(Str){.c_str = (U8*)"func", .count = 4, .cap = CAP_LIT});
    case FuncType_TAG_Proc:     return Str_clone(&(Str){.c_str = (U8*)"proc", .count = 4, .cap = CAP_LIT});
    case FuncType_TAG_Test:     return Str_clone(&(Str){.c_str = (U8*)"test", .count = 4, .cap = CAP_LIT});
    case FuncType_TAG_Macro:    return Str_clone(&(Str){.c_str = (U8*)"macro", .count = 5, .cap = CAP_LIT});
    case FuncType_TAG_ExtFunc: return Str_clone(&(Str){.c_str = (U8*)"ext_func", .count = 8, .cap = CAP_LIT});
    case FuncType_TAG_ExtProc: return Str_clone(&(Str){.c_str = (U8*)"ext_proc", .count = 8, .cap = CAP_LIT});
    }
    return Str_clone(&(Str){.c_str = (U8*)"?", .count = 1, .cap = CAP_LIT});
}

void ast_print(Expr *e, U32 indent) {
    if (!e) return;
    for (U32 i = 0; i < indent; i++) printf("  ");
    Str *nn = node_name(&e->data);
    printf("(%s", nn->c_str);
    if (e->til_type.tag != TilType_TAG_Unknown) {
        Str *tn = til_type_name_c(&e->til_type);
        printf(":%s", tn->c_str);
    }
    switch (e->data.tag) {
    case ExprData_TAG_Ident:
    case ExprData_TAG_LiteralStr:
    case ExprData_TAG_LiteralNum:
    case ExprData_TAG_LiteralBool:
    case ExprData_TAG_ForIn:
        printf(" \"%s\"", e->data.data.Ident.c_str);
        break;
    case ExprData_TAG_LiteralNull:
        break;
    case ExprData_TAG_Decl:
        printf(" %s%s", e->data.data.Decl.is_mut ? "mut " : "", e->data.data.Decl.name.c_str);
        break;
    case ExprData_TAG_Assign:
    case ExprData_TAG_NamedArg:
        printf(" %s", e->data.data.Assign.c_str);
        break;
    case ExprData_TAG_FuncDef: {
        Str *ftn = func_type_name(&e->data.data.FuncDef.func_type);
        printf(" %s", ftn->c_str);
        break;
    }
    default:
        break;
    }
    if (e->children.count > 0) {
        printf("\n");
        for (U32 i = 0; i < e->children.count; i++) {
            ast_print(expr_child(e, i), indent + 1);
        }
        for (U32 i = 0; i < indent; i++) printf("  ");
    }
    printf(")\n");
}

Bool *enum_has_payloads(Expr *enum_def) {
    Expr *body = expr_child(enum_def, 0);
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = expr_child(body, i);
        if (f->data.tag == ExprData_TAG_Decl && !f->data.data.Decl.is_namespace && (f->data.data.Decl.explicit_type).count > 0) {
            Bool *r = malloc(sizeof(Bool)); *r = 1; return r;
        }
    }
    Bool *r = malloc(sizeof(Bool)); *r = 0; return r;
}

I32 *enum_variant_tag(Expr *enum_def, Str *variant_name) {
    Expr *body = expr_child(enum_def, 0);
    I32 tag = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = expr_child(body, i);
        if (f->data.tag == ExprData_TAG_Decl && !f->data.data.Decl.is_namespace) {
            if (*Str_eq(&f->data.data.Decl.name, variant_name)) {
                I32 *r = malloc(sizeof(I32)); *r = tag; return r;
            }
            tag++;
        }
    }
    I32 *r = malloc(sizeof(I32)); *r = -1; return r;
}

Str *enum_variant_type(Expr *enum_def, I32 tag) {
    Expr *body = expr_child(enum_def, 0);
    I32 idx = 0;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = expr_child(body, i);
        if (f->data.tag == ExprData_TAG_Decl && !f->data.data.Decl.is_namespace) {
            if (idx == tag) return &f->data.data.Decl.explicit_type;
            idx++;
        }
    }
    return Str_clone(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT});
}

// --- Expr namespace methods ---

void Expr_error(Expr *self, Str *msg) {
    printf("%s:%u:%u: error: %s\n", self->path.c_str, self->line, self->col, msg->c_str);
}

void Expr_todo_error(Expr *self, Str *msg) {
    Expr_error(self, msg);
    printf("  note: this language feature is not implemented yet\n");
}

void Expr_lang_error(Expr *self, Str *msg) {
    Expr_error(self, msg);
    printf("  note: this is a bug in the language, please report it\n");
}

void Expr_add_child(Expr *self, Expr *child) {
    Expr **_p = malloc(sizeof(Expr *)); *_p = child;
    Vec_push(&self->children, _p);
}

Expr *Expr_new(ExprData *data, U32 line, U32 col, Str *path) {
    Expr *e = calloc(1, sizeof(Expr));
    e->data = *data;
    { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); e->children = *_vp; free(_vp); }
    e->line = line;
    e->col = col;
    if (path) e->path = *path;
    e->variadic_index = -1;
    e->kwargs_index = -1;
    return e;
}
