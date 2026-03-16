#ifndef TIL_AST_H
#define TIL_AST_H

#include "../../bootstrap/ast.h"

// Convenience macros for hand-written C code
#define STR_FIELD(expr, field) (&(expr)->data.data.field)
#define STR_SNAME(expr)       (&(expr)->struct_name)
#define STR_PATH(expr)        (&(expr)->path)
#define DECL_NAME(expr)       (&(expr)->data.data.Decl.name)
#define DECL_ETYPE(expr)      (&(expr)->data.data.Decl.explicit_type)
#define FDEF_RTYPE(expr)      (&(expr)->data.data.FuncDef.return_type)
#define VEC_SET(v)   ((v).count > 0)
#define expr_child(e, i) ((Expr *)Vec_get(&(e)->children, &(U64){(U64)(i)}))

// Vec helper (in initer.c)
void *Vec_take(Vec *v);

#endif
