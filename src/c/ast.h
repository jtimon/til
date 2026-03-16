#ifndef TIL_AST_H
#define TIL_AST_H

#include "../../bootstrap/ast.h"

#define DECL_NAME(expr)       (&(expr)->data.data.Decl.name)
#define FDEF_RTYPE(expr)      (&(expr)->data.data.FuncDef.return_type)
#define VEC_SET(v)   ((v).count > 0)

// Vec helper (in initer.c)
void *Vec_take(Vec *v);

#endif
