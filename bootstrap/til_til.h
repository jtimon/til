#pragma once
#include "til_decls.h"


typedef struct Mode {
    char _;
} Mode;


typedef struct TypeScope {
    char _;
} TypeScope;


Mode * Mode_clone(Mode * self);
void Mode_delete(Mode * self, Bool * call_free);
U64 * Mode_size(void);
TypeScope * TypeScope_clone(TypeScope * self);
void TypeScope_delete(TypeScope * self, Bool * call_free);
U64 * TypeScope_size(void);
Vec * extract_imports(void * body);
I32 * resolve_imports(Vec * import_paths, Str * base_dir, void * resolved_set, void * stack, void * merged, Str * lib_dir);
void usage(void);
void mark_core(Expr * e);
