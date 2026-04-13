#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARAM_IS_OWN(p) ((p)->own_type.tag == OwnType_TAG_Own)
#define PARAM_IS_SHALLOW(p) ((p)->own_type.tag == OwnType_TAG_Shallow)
#define RETURN_IS_REF(fd) ((fd)->return_own_type.tag == OwnType_TAG_Ref)
#define RETURN_IS_SHALLOW(fd) ((fd)->return_own_type.tag == OwnType_TAG_Shallow)
#define DECL_IS_OWN(d) ((d).own_type.tag == OwnType_TAG_Own)
#define DECL_IS_REF(d) ((d).own_type.tag == OwnType_TAG_Ref)
#define DECL_IS_SHALLOW(d) ((d).own_type.tag == OwnType_TAG_Shallow)
#define FIELD_IS_PTR(e) ((e)->field_own_type.tag != OwnType_TAG_Shallow)
#define FIELD_IS_SHALLOW(e) ((e)->field_own_type.tag == OwnType_TAG_Shallow)

// Helper macros for File-based emission (replacing fprintf)
#define EMIT(f, s) File_write_str(f, &(Str){.c_str=(U8*)(s), .count=(U64)strlen((const char*)(s)), .cap=CAP_VIEW})





// reset_current_fdef: moved to builder.til

// Collect unique array/vec builtin type names from AST
// CollectionInfo defined in builder.til


// Collect unique dyn_call method literals from AST
// DynCallInfo defined in builder.til

// is_dyn_call_name: moved to builder.til

// --- Emitter helpers ---



// is_stack_local: moved to builder.til

// is_value_global: moved to builder.til

// is_ref_local: moved to builder.til


// use_dot_access: moved to builder.til


// Block-scoped emit_body: clone stack_locals/ref_locals before
// entering a block, restore after. Inner declarations stay local to the block.

// Scan function body to find variables whose address might escape via ref.
// A variable is unsafe to hoist if:
// - It appears in a ref declaration RHS: "ref y : T = x"
// - It's passed as arg to a ref-returning function
// Resolve the callee name from an fcall's first child

// fcall_fn_sig: moved to builder.til





// Check if callee's i-th parameter is shallow (for call site emission)


// Get the C value type for an fcall's return value

// callee_returns_shallow: moved to builder.til

// callee_returns_dynamic: moved to builder.til

// fcall_is_shallow_return: moved to builder.til

// fcall_returns_dynamic: moved to builder.til

// callee_param_is_shallow: moved to builder.til

// callee_param_is_usize: moved to builder.til

// callee_param_is_own: moved to builder.til




// --- Top-level emission ---


// is_exported_top_level_global: moved to builder.til

// Topo-sort and emit struct/enum definitions from a single program.
// emitted set carries over between calls to handle cross-program deps.
// Derive basename from absolute path: "/abs/path/to/str.til" -> "str"

// Populate struct_bodies/func_defs maps and init auxiliary sets

// build: moved to builder.til






// --- Header emission helpers (shared by build_header and build_forward_header) ---

// Emit struct/enum forward declarations
// compile_lib: moved to builder.til


// emit_monolithic_header: moved to builder.til

// emit_all_forward_declarations: moved to builder.til

// emit_dyn_fn_wrappers: moved to builder.til






// --- Header emission helpers (shared by build_header and build_forward_header) ---

// Emit struct/enum forward declarations
// compile_lib: moved to builder.til

// compile_c: moved to builder.til
