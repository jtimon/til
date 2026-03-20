#pragma once
#include "til_decls.h"

#include "til_ast.h"

typedef struct LocalInfo {
    Str *name;
    TilType type;
    Str *struct_name;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;
    Bool skip_delete;
} LocalInfo;


LocalInfo * LocalInfo_clone(LocalInfo * self);
void LocalInfo_delete(LocalInfo * self, Bool * call_free);
U64 * LocalInfo_size(void);
