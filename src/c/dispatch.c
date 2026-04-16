#include "../../boot/modes.h"
#include "ext.h"
#include <stdio.h>

extern Expr *cached_array_def;
extern Str *cached_array_name;
extern Expr *cached_vec_def;
extern Str *cached_vec_name;

// Forward declarations for value-param scalar functions (not in ext.h
// because boot redefines them with pointer-param signatures)
U8 U8_from_i64(I64 v);
I16 I16_from_i64(I64 v);
I32 I32_from_i64(I64 v);
F32 F32_from_i64(I64 v);
U32 U32_from_i64(I64 v);
U64 U64_from_i64(I64 v);

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <ffi.h>

#define PARAM_IS_SHALLOW(p) ((p)->own_type.tag == OwnType_TAG_Shallow)
#define RETURN_IS_SHALLOW(fd) ((fd)->return_own_type.tag == OwnType_TAG_Shallow)
#define DECL_IS_SHALLOW(d) ((d).own_type.tag == OwnType_TAG_Shallow)

// Codegen Str layout (matches ext.h Str: {U8 *data, U64 count, U64 cap})
// Distinct from compiler-internal Str (str.h: {char *c_str, U64 count, U64 cap})
// ExtStr defined in dispatch.til (generated into boot/modes.h)

typedef Bool (*DispatchFn)(Scope *, Expr *, Value *);

FFIType *ffi_type_pointer_ref(void) { return (FFIType *)&ffi_type_pointer; }
FFIType *ffi_type_sint64_ref(void) { return (FFIType *)&ffi_type_sint64; }
FFIType *ffi_type_uint8_ref(void) { return (FFIType *)&ffi_type_uint8; }
FFIType *ffi_type_sint16_ref(void) { return (FFIType *)&ffi_type_sint16; }
FFIType *ffi_type_sint32_ref(void) { return (FFIType *)&ffi_type_sint32; }
FFIType *ffi_type_uint32_ref(void) { return (FFIType *)&ffi_type_uint32; }
FFIType *ffi_type_uint64_ref(void) { return (FFIType *)&ffi_type_uint64; }
FFIType *ffi_type_float_ref(void) { return (FFIType *)&ffi_type_float; }

// === Handler macros ===

// === Remaining handlers (name mismatch or local ext_func — can't use auto-FFI) ===

// === Print handlers ===

// === Misc handlers ===


// === Dynamic dispatch handler ===

// h_dyn_call, get_elem_size, h_array, h_vec: moved to dispatch.til

// === Pointer primitive handlers ===



// === System primitive handlers ===

// File handle I/O handlers



// === Dispatch init ===


// === Main dispatch ===


Bool ext_dispatch_ffi(Str *name, Scope *scope, Expr *e, Value *result) {
    if (!ffi_loaded) return 0;
    if (!Map_has(&ffi_map, name)) return 0;

    FFIEntry *fe = Map_get(&ffi_map, name);
    Bool *param_shallows = (Bool *)fe->param_shallows;
    ffi_type **arg_types = (ffi_type **)fe->arg_types;
    ffi_cif *cif = (ffi_cif *)fe->cif;
    U32 nargs = e->children.count - 1;
    U32 alloc_n = nargs > 0 ? nargs : 1;
    void **args = malloc(sizeof(void *) * alloc_n);
    void **arg_ptrs = malloc(sizeof(void *) * alloc_n);
    for (U32 i = 0; i < nargs; i++) {
        Value v = eval_expr(scope, Expr_child(e, &(USize){(USize)(i + 1)}));
        if (param_shallows && i < (U32)fe->nparam && param_shallows[i]) {
            // Shallow: store dereferenced value directly for ffi
            if (v.tag == Value_TAG_Struct) {
                // Struct by value: point arg_ptrs directly at struct data
                arg_ptrs[i] = v.data.Struct.data;
                continue;
            }
            if (arg_types[i] == &ffi_type_sint64) {
                I64 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(I64 *)v.data.Ptr;
                else { I64 *_hp = value_to_i64(&v); tmp = *_hp; free(_hp); }
                *(I64 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_uint8) {
                U8 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(U8 *)v.data.Ptr;
                else { U64 *_hp = value_to_u64(&v); tmp = (U8)*_hp; free(_hp); }
                *(U8 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_sint16) {
                I16 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(I16 *)v.data.Ptr;
                else { I64 *_hp = value_to_i64(&v); tmp = (I16)*_hp; free(_hp); }
                *(I16 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_sint32) {
                I32 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(I32 *)v.data.Ptr;
                else { I64 *_hp = value_to_i64(&v); tmp = (I32)*_hp; free(_hp); }
                *(I32 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_uint32) {
                U32 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(U32 *)v.data.Ptr;
                else { U64 *_hp = value_to_u64(&v); tmp = (U32)*_hp; free(_hp); }
                *(U32 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_uint64) {
                U64 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(U64 *)v.data.Ptr;
                else { U64 *_hp = value_to_u64(&v); tmp = *_hp; free(_hp); }
                *(U64 *)&args[i] = tmp;
            } else if (arg_types[i] == &ffi_type_float) {
                F32 tmp;
                if (v.tag == Value_TAG_Ptr) tmp = *(F32 *)v.data.Ptr;
                else { F32 *_hp = value_to_f32(&v); tmp = *_hp; free(_hp); }
                *(F32 *)&args[i] = tmp;
            } else {
                args[i] = v.data.Ptr;
            }
        } else {
            // Deep: pass heap-allocated pointer (FFI callee may free it)
            switch (v.tag) {
                case Value_TAG_Int:    { I64 *p = malloc(sizeof(I64)); *p = v.data.Int; args[i] = p; break; }
                case Value_TAG_Byte:   { U8 *p = malloc(sizeof(U8)); *p = v.data.Byte; args[i] = p; break; }
                case Value_TAG_Short:  { I16 *p = malloc(sizeof(I16)); *p = v.data.Short; args[i] = p; break; }
                case Value_TAG_Int32:  { I32 *p = malloc(sizeof(I32)); *p = v.data.Int32; args[i] = p; break; }
                case Value_TAG_Uint32: { U32 *p = malloc(sizeof(U32)); *p = v.data.Uint32; args[i] = p; break; }
                case Value_TAG_Uint64: { U64 *p = malloc(sizeof(U64)); *p = v.data.Uint64; args[i] = p; break; }
                case Value_TAG_Float:  { F32 *p = malloc(sizeof(F32)); *p = v.data.Float; args[i] = p; break; }
                case Value_TAG_Boolean: { Bool *p = malloc(sizeof(Bool)); *p = v.data.Boolean; args[i] = p; break; }
                case Value_TAG_Ptr:    args[i] = v.data.Ptr; break;
                case Value_TAG_Struct: args[i] = v.data.Struct.data; break;
                case Value_TAG_Enum:  args[i] = v.data.Enum.data; break;
                default:         args[i] = NULL; break;
            }
        }
        arg_ptrs[i] = &args[i];
    }
    // Check if return is a shallow struct (needs larger buffer)
    // Only treat as struct if the CIF return type is FFI_TYPE_STRUCT —
    // scalar types like Bool are ext_structs in til but scalars in FFI.
    Expr **ret_sdef = NULL;
    if (fe->return_is_shallow && fe->return_type &&
        cif->rtype->type == FFI_TYPE_STRUCT &&
        Map_has(&ffi_struct_defs, fe->return_type))
        ret_sdef = Map_get(&ffi_struct_defs, fe->return_type);
    union {
        void *ptr;
        I64 i64;
        U64 u64;
        I32 i32;
        U32 u32;
        I16 i16;
        U8 u8;
        F32 f32;
        Bool boolean;
    } raw = {0};
    void *ret_buf = NULL;
    if (ret_sdef) {
        // Struct return: allocate buffer of struct size
        ret_buf = malloc((*ret_sdef)->data.data.StructDef.total_struct_size);
        ffi_call(cif, FFI_FN(fe->fn), ret_buf, nargs > 0 ? arg_ptrs : NULL);
    } else {
        ffi_call(cif, FFI_FN(fe->fn), &raw, nargs > 0 ? arg_ptrs : NULL);
    }
    if (!fe->return_type) {
        *result = val_none();
    } else if (ret_sdef) {
        // Shallow struct return: wrap buffer in StructInstance
        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = fe->return_type;
        inst->struct_def = *ret_sdef;
        inst->data = ret_buf;
        inst->borrowed = 0;
        result->tag = Value_TAG_Struct;
        result->data.Struct = *inst; free(inst);
    } else if (fe->return_is_shallow) {
        // Shallow return: C function returned a primitive by value.
        if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I64", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Int, .data.Int = raw.i64};
        } else if ((fe->return_type->count == 2 && memcmp(fe->return_type->c_str, "U8", 2) == 0)) {
            *result = (Value){.tag = Value_TAG_Byte, .data.Byte = raw.u8};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I16", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Short, .data.Short = raw.i16};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I32", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Int32, .data.Int32 = raw.i32};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U32", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = raw.u32};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U64", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Uint64, .data.Uint64 = raw.u64};
        } else if ((fe->return_type->count == 5 && memcmp(fe->return_type->c_str, "USize", 5) == 0)) {
            *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = raw.u32};
        } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "F32", 3) == 0)) {
            *result = (Value){.tag = Value_TAG_Float, .data.Float = raw.f32};
        } else if ((fe->return_type->count == 4 && memcmp(fe->return_type->c_str, "Bool", 4) == 0)) {
            *result = (Value){.tag = Value_TAG_Boolean, .data.Boolean = raw.boolean};
        } else {
            *result = val_none();
        }
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "Str", 3) == 0)) {
        ExtStr *sp = (ExtStr *)raw.ptr;
        *result = make_str_value_own((char *)sp->data, sp->count);
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I64", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Int, .data.Int = *(I64 *)raw.ptr};
    } else if ((fe->return_type->count == 2 && memcmp(fe->return_type->c_str, "U8", 2) == 0)) {
        *result = (Value){.tag = Value_TAG_Byte, .data.Byte = *(U8 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I16", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Short, .data.Short = *(I16 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "I32", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Int32, .data.Int32 = *(I32 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U32", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = *(U32 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "U64", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Uint64, .data.Uint64 = *(U64 *)raw.ptr};
    } else if ((fe->return_type->count == 5 && memcmp(fe->return_type->c_str, "USize", 5) == 0)) {
        *result = (Value){.tag = Value_TAG_Uint32, .data.Uint32 = *(U32 *)raw.ptr};
    } else if ((fe->return_type->count == 3 && memcmp(fe->return_type->c_str, "F32", 3) == 0)) {
        *result = (Value){.tag = Value_TAG_Float, .data.Float = *(F32 *)raw.ptr};
    } else if ((fe->return_type->count == 4 && memcmp(fe->return_type->c_str, "Bool", 4) == 0)) {
        *result = (Value){.tag = Value_TAG_Boolean, .data.Boolean = *(Bool *)raw.ptr};
    } else if ((fe->return_type->count == 7 && memcmp(fe->return_type->c_str, "Dynamic", 7) == 0)) {
        *result = (Value){.tag = Value_TAG_Ptr, .data.Ptr = raw.ptr};
    } else {
        // Struct return -- look up struct def by return type name
        if (Map_has(&ffi_struct_defs, fe->return_type)) {
            Expr **sdef = Map_get(&ffi_struct_defs, fe->return_type);
            StructInstance *inst = malloc(sizeof(StructInstance));
            inst->struct_name = fe->return_type;
            inst->struct_def = *sdef;
            inst->borrowed = 0;
            inst->data = raw.ptr;
            result->tag = Value_TAG_Struct;
            result->data.Struct = *inst; free(inst);
        } else {
            *result = val_none();
        }
    }
    free(args);
    free(arg_ptrs);
    return 1;
}


// ffi_register: moved to dispatch.til

// ffi_init_scan_program: moved to dispatch.til

// ffi_init: moved to dispatch.til
