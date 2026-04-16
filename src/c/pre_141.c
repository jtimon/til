// pre_141: libffi thin wrappers (see issue #141)
// These isolate libffi typedefs so ext_dispatch_ffi and ffi_register
// can be translated to til without exposing ffi_type/ffi_cif directly.
// Only linked by til.til (the compiler), not by user programs.

#include "../../boot/modes.h"
#include "ext.h"
#include <stdlib.h>
#include <ffi.h>

// ffi_type accessors (already declared as ext_func in dispatch.til)
FFIType *ffi_type_pointer_ref(void) { return (FFIType *)&ffi_type_pointer; }
FFIType *ffi_type_sint64_ref(void) { return (FFIType *)&ffi_type_sint64; }
FFIType *ffi_type_uint8_ref(void) { return (FFIType *)&ffi_type_uint8; }
FFIType *ffi_type_sint16_ref(void) { return (FFIType *)&ffi_type_sint16; }
FFIType *ffi_type_sint32_ref(void) { return (FFIType *)&ffi_type_sint32; }
FFIType *ffi_type_uint32_ref(void) { return (FFIType *)&ffi_type_uint32; }
FFIType *ffi_type_uint64_ref(void) { return (FFIType *)&ffi_type_uint64; }
FFIType *ffi_type_float_ref(void) { return (FFIType *)&ffi_type_float; }
void *ffi_type_void_ref(void) { return (void *)&ffi_type_void; }

// Allocate a ffi_cif (opaque to til)
void *ffi_alloc_cif(void) { return malloc(sizeof(ffi_cif)); }

// Prepare a CIF for calling
void ffi_prep_cif_wrap(void *cif, U32 nargs, void *rtype, void *atypes) {
    ffi_prep_cif((ffi_cif *)cif, FFI_DEFAULT_ABI, nargs,
                 (ffi_type *)rtype, (ffi_type **)atypes);
}

// Perform the FFI call
void ffi_call_wrap(void *cif, void *fn, void *ret, void *args) {
    ffi_call((ffi_cif *)cif, FFI_FN(fn), ret,
             args ? (void **)args : NULL);
}

// Check if the CIF's return type is a struct
Bool ffi_cif_rtype_is_struct(void *cif) {
    return ((ffi_cif *)cif)->rtype->type == FFI_TYPE_STRUCT;
}
