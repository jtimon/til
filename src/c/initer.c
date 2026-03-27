#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_enum_clone_method_for_body(Expr *body, Str *ename, I32 line, I32 col, Str *path) {
    Vec variant_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_names = *_vp; free(_vp); }
    Vec variant_types; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_types = *_vp; free(_vp); }
    Bool has_payloads = 0;
    collect_enum_variants(body, &variant_names, &variant_types, &has_payloads);
    generate_enum_clone_method(body, ename, line, col, path, &variant_names, &variant_types, has_payloads);
    Vec_delete(&variant_names, &(Bool){0});
    Vec_delete(&variant_types, &(Bool){0});
}

I32 init_declarations(Expr *program, TypeScope *scope) {
    I32 errors = 0;

    // Pass 1: register all struct definitions
    errors += register_struct_definitions(program, scope);

    // Pass 1.1: pre-register FuncSig type aliases (bodyless func/proc defs)
    // Needed before struct layout/clone/delete so FuncSig-typed struct fields are recognized
    register_funcsig_aliases(program, scope);

    // Pass 1.5: auto-generate clone methods for all structs
    generate_missing_struct_clones(program, scope);

    // Pass 1.7: auto-generate delete methods for all structs
    generate_missing_struct_deletes(program, scope);

    // Pass 1.8: register enum definitions, generate variants + non-clone methods
    errors += register_enums_and_generate_nonclone_methods(program, scope);

    // Pass 1.82: auto-generate clone methods for enums
    generate_missing_enum_clones(program);

    // Pass 1.85: register type aliases (Name := ExistingType where RHS is a known type name)
    // Must run after Pass 1 (structs), Pass 1.1 (FuncSigs), and Pass 1.8 (enums)
    register_type_aliases(program, scope);

    // Pass 1.9: compute flat struct layout (field offsets and sizes)
    // Must run BEFORE size method synthesis so total_struct_size is available
    compute_all_struct_layouts(program, scope);

    // Pass 1.92: auto-generate size methods for structs and enums
    // Uses total_struct_size computed above for correct values (includes alignment padding)
    generate_size_methods(program, scope);

    // Pass 1.95: auto-generate derived methods
    // From cmp: eq, neq, lt, gt, lte, gte (if missing)
    // From add+unity: inc (if missing). From sub+unity: dec (if missing)
    generate_derived_methods(program, scope);

    // Pass 2: register all func/proc definitions
    register_function_definitions(program, scope);

    // Pass 3: pre-register top-level value declarations so functions can
    // reference module globals before their declaration appears.
    register_top_level_values(program, scope);

    return errors;
}
