#pragma once
#include "til_decls.h"


typedef struct CollectionInfo {
    Str *type_name;
    I32 is_vec;
} CollectionInfo;


typedef struct DynCallInfo {
    Str *method;
    I32 nargs;
    Bool has_return;
} DynCallInfo;


CollectionInfo * CollectionInfo_clone(CollectionInfo * self);
void CollectionInfo_delete(CollectionInfo * self, Bool * call_free);
U64 * CollectionInfo_size(void);
DynCallInfo * DynCallInfo_clone(DynCallInfo * self);
void DynCallInfo_delete(DynCallInfo * self, Bool * call_free);
U64 * DynCallInfo_size(void);
