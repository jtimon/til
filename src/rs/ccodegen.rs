// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal, SFuncDef, SEnumDef, ValueType, INFER_TYPE};
use crate::rs::init::{Context, get_value_type, ScopeFrame, SymbolInfo, ScopeType, PrecomputedHeapValue};
use crate::rs::typer::get_func_def_for_fcall_with_expr;
use crate::rs::eval_arena::{EvalArena, VecContents};
use std::collections::{HashMap, HashSet};
use std::convert::TryInto;

// Prefix for all TIL-generated names in C code (structs, functions, types)
const TIL_PREFIX: &str = "til_";

// Codegen context for tracking function info
struct CodegenContext {
    // Counter for generating unique temp variable names (deterministic per-compilation)
    mangling_counter: usize,
    // Map function name -> variadic arg info
    func_variadic_args: HashMap<String, VariadicParamInfo>,
    // Currently generating function's throw types (if any)
    current_throw_types: Vec<ValueType>,
    // Currently generating function's return types (if any)
    current_return_types: Vec<ValueType>,
    // Set of declared variable names in current function (to avoid redefinition)
    declared_vars: HashSet<String>,
    // Set of by-ref param names in current function - for using -> instead of . for field access
    current_ref_params: HashSet<String>,
    // Map of variadic param names to their element type (e.g., "args" -> "Bool")
    // Passed as til_Array* so need dereference, and need type info for Array.get casting
    current_variadic_params: HashMap<String, String>,
    // All known type names for generating til_size_of function
    known_types: Vec<String>,
    // Map of locally-caught error types to catch label info
    // For explicit throw statements that have a local catch block
    local_catch_labels: HashMap<String, CatchLabelInfo>,
    // Current function name for nested function name mangling (empty at top-level)
    current_function_name: String,
    // C code for hoisted nested function definitions
    hoisted_functions: Vec<String>,
    // C code for hoisted nested function prototypes
    hoisted_prototypes: Vec<String>,
    // Map original function name -> mangled name for nested functions
    nested_func_names: HashMap<String, String>,
    // Bug #133 fix: Map var_name -> static array name for precomputed heap values
    // When emitting assignments in main(), Ptr fields will use these static pointers
    precomputed_static_arrays: HashMap<String, PrecomputedStaticInfo>,
}

// Bug #133: Info about a precomputed Vec's static array serialization
#[derive(Clone, Debug)]
struct PrecomputedStaticInfo {
    data_array_name: String,      // Name of the static array (e.g., "_precomp_chromatic_data")
    type_name_array_name: String, // Name of the type_name string (e.g., "_precomp_chromatic_type_name")
}

impl CodegenContext {
    fn new() -> Self {
        CodegenContext {
            mangling_counter: 0,
            func_variadic_args: HashMap::new(),
            current_throw_types: Vec::new(),
            current_return_types: Vec::new(),
            declared_vars: HashSet::new(),
            current_ref_params: HashSet::new(),
            current_variadic_params: HashMap::new(),
            known_types: Vec::new(),
            local_catch_labels: HashMap::new(),
            current_function_name: String::new(),
            hoisted_functions: Vec::new(),
            hoisted_prototypes: Vec::new(),
            nested_func_names: HashMap::new(),
            precomputed_static_arrays: HashMap::new(),
        }
    }
}

// Generate unique mangled name using context counter (deterministic)
// Includes function name prefix for uniqueness across functions
fn next_mangled(ctx: &mut CodegenContext) -> String {
    let n = ctx.mangling_counter;
    ctx.mangling_counter += 1;
    let func_name = &ctx.current_function_name;
    if !func_name.is_empty() {
        format!("_tmp_{}_{}", func_name, n)
    } else {
        format!("_tmp_{}", n)
    }
}

// Returns the C name for a TIL identifier - adds TIL_PREFIX
// Exceptions: C keywords (true, false), pointer deref (*name), and generated names (_ prefix)
fn til_name(name: &str) -> String {
    match name {
        "true" | "false" => name.to_string(),
        _ if name.starts_with('*') || name.starts_with('_') => name.to_string(),
        _ => format!("{}{}", TIL_PREFIX, name),
    }
}

// Bug #97: Returns the C name for a TIL variable with type prefix
// Format: til_{Type}_{name} - allows same variable name with different types (shadowing)
fn til_var_name(name: &str, type_name: &str) -> String {
    match name {
        "true" | "false" => name.to_string(),
        _ if name.starts_with('*') || name.starts_with('_') => name.to_string(),
        _ => format!("{}{}_{}", TIL_PREFIX, type_name, name),
    }
}

// Bug #97: Get the type-mangled C name for a variable by looking up its type
fn til_var_name_from_context(name: &str, context: &Context) -> String {
    if name == "true" || name == "false" || name.starts_with('*') || name.starts_with('_') {
        return name.to_string();
    }
    if let Some(sym) = context.scope_stack.lookup_symbol(name) {
        let type_str = value_type_to_c_prefix(&sym.value_type);
        return format!("{}{}_{}", TIL_PREFIX, type_str, name);
    }
    // Fallback to old behavior if not a known variable (could be a type name, etc.)
    til_name(name)
}

// Bug #97: Convert a ValueType to a short string for use in variable name mangling
fn value_type_to_c_prefix(vt: &ValueType) -> String {
    match vt {
        ValueType::TCustom(name) => name.clone(),
        ValueType::TFunction(_) => "Func".to_string(),
        ValueType::TType(_) => "Type".to_string(),
        ValueType::TMulti(elem_type) => format!("Multi_{}", elem_type),
    }
}

// Emit a struct literal, using compound literal syntax if already_declared
// e.g., " = {0}" vs " = (til_TypeName){0}"
fn emit_struct_literal_assign(output: &mut String, type_name: &str, already_declared: bool, literal_content: &str) {
    output.push_str(" = ");
    if already_declared {
        output.push_str("(");
        output.push_str(&til_name(type_name));
        output.push_str(")");
    }
    output.push_str(literal_content);
    output.push_str(";\n");
}

// Start a struct literal assignment - caller will emit content and closing brace
// e.g., " = " vs " = (til_TypeName)"
fn emit_struct_literal_start(output: &mut String, type_name: &str, already_declared: bool) {
    output.push_str(" = ");
    if already_declared {
        output.push_str("(");
        output.push_str(&til_name(type_name));
        output.push_str(")");
    }
}

// Returns the C name for a TIL function - adds TIL_PREFIX and converts dots to underscores
// Used for function names like Array.len -> til_Array_len
fn til_func_name(name: &str) -> String {
    format!("{}{}", TIL_PREFIX, name.replace('.', "_"))
}

// Issue #119: Check if a throw type refers to an empty struct (no fields)
// Empty struct errors don't need error parameters - only the status code matters
fn is_empty_error_struct(context: &Context, throw_type: &ValueType) -> bool {
    if let ValueType::TCustom(type_name) = throw_type {
        if let Some(struct_def) = context.scope_stack.lookup_struct(type_name) {
            return struct_def.members.is_empty();
        }
    }
    false
}

// Get function name from FCall's first param, handling both AST patterns:
// - Identifier("func") with params = [] -> "func"
// - Identifier("I64.inc") with params = [] -> "I64_inc" (from precomp)
// - Identifier("Vec") with params = [Identifier("new")] -> "Vec_new" (from parser)
// Returns the C-ready name with underscores (not dots)
fn get_func_name_string(first_param: &Expr) -> Option<String> {
    if let NodeType::Identifier(name) = &first_param.node_type {
        if first_param.params.is_empty() {
            Some(name.replace('.', "_"))
        } else {
            let mut parts = vec![name.clone()];
            for p in &first_param.params {
                if let NodeType::Identifier(part) = &p.node_type {
                    parts.push(part.clone());
                }
            }
            Some(parts.join("_"))
        }
    } else {
        None
    }
}

// Get TIL function name from FCall's first param (for scope lookups)
// Returns the dot-separated name like "Vec.new" or "I64.inc"
// This avoids the fragile .replacen('_', ".", 1) hack which breaks on type names with underscores
fn get_til_func_name_string(first_param: &Expr) -> Option<String> {
    if let NodeType::Identifier(name) = &first_param.node_type {
        if first_param.params.is_empty() {
            // Already has dots (from precomp) or is a simple name
            Some(name.clone())
        } else {
            // Build dotted name from nested identifiers
            let mut parts = vec![name.clone()];
            for p in &first_param.params {
                if let NodeType::Identifier(part) = &p.node_type {
                    parts.push(part.clone());
                }
            }
            Some(parts.join("."))
        }
    } else {
        None
    }
}

/// Check if an expression is a type identifier (a Type parameter at call site)
/// Returns the type name if it is, so it can be emitted as a string literal
/// Matches interpreter.rs behavior (line 1703-1713)
/// Only matches STANDALONE identifiers - not field access like Vec.INIT_CAP
fn get_type_arg_name(expr: &Expr, context: &Context) -> Option<String> {
    if let NodeType::Identifier(name) = &expr.node_type {
        // Only match standalone identifiers (no field access)
        if !expr.params.is_empty() {
            return None; // This is field access like Vec.INIT_CAP, not a type arg
        }
        // Check if this identifier is a type name (struct, enum, or builtin type)
        if let Some(sym) = context.scope_stack.lookup_symbol(name) {
            if let ValueType::TType(_) = &sym.value_type {
                return Some(name.clone());
            }
        }
    }
    None
}

// Get function definition for an FCall expression
// Uses get_func_def_for_fcall_with_expr from typer.rs which handles all cases correctly
// (regular functions, struct methods, UFCS - though UFCS is already resolved by precomp)
// Returns None for struct/enum constructors
fn get_fcall_func_def(context: &Context, fcall_expr: &Expr) -> Option<SFuncDef> {
    let mut expr_clone = fcall_expr.clone();
    match get_func_def_for_fcall_with_expr(&context, &mut expr_clone) {
        Ok(Some(fd)) => Some(fd),
        _ => None,
    }
}

/// Bug #60: Determine if a parameter should be passed by reference (pointer)
/// - copy params: pass by value (copy is made)
/// - Type params: already pointers (const char*), pass by value
/// - All other const/own/mut params (including Dynamic): pass by pointer
fn param_needs_by_ref(param: &crate::rs::parser::Declaration) -> bool {
    if param.is_copy {
        return false;
    }
    // Type is already a pointer type in C (const char*), no extra indirection needed
    match &param.value_type {
        ValueType::TCustom(name) if name == "Type" => false,
        _ => true,
    }
}

/// Extract struct field type dependencies for topological sorting
/// Returns the type name if it's a custom type that needs to be defined first
fn get_field_type_dependency(value_type: &ValueType) -> Option<String> {
    match value_type {
        ValueType::TCustom(name) => {
            // I64 and U8 are primitives, not struct dependencies
            match name.as_str() {
                "I64" | "U8" => None,
                s if s == INFER_TYPE => panic!("INFER_TYPE in ccodegen - should have been resolved by typer"),
                _ => Some(name.clone()),
            }
        },
        _ => None,
    }
}

/// Get struct dependencies (other struct types used as fields)
fn get_struct_dependencies(expr: &Expr) -> Vec<String> {
    let mut deps = Vec::new();
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                for member in &struct_def.members {
                    if member.is_mut {
                        if let Some(dep) = get_field_type_dependency(&member.value_type) {
                            deps.push(dep);
                        }
                    }
                }
            }
        }
    }
    deps
}

/// Get struct name from a struct declaration expression
fn get_struct_name(expr: &Expr) -> Option<String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(_) = &expr.params[0].node_type {
                return Some(decl.name.clone());
            }
        }
    }
    None
}

/// Get enum dependencies (types used in payloads) as a Vec
fn get_enum_dependencies(expr: &Expr) -> Vec<String> {
    let mut deps = Vec::new();
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(enum_def) = &expr.params[0].node_type {
                for v in &enum_def.variants {
                    if let Some(pt) = &v.payload_type {
                        if let ValueType::TCustom(type_name) = pt {
                            // Skip primitives (but NOT Str or Bool - they're structs)
                            if type_name != "I64" && type_name != "U8"
                                && type_name != "Dynamic" && type_name != "Type" {
                                deps.push(type_name.clone());
                            }
                        }
                    }
                }
            }
        }
    }
    deps
}

/// Get enum name from an enum-with-payloads declaration expression
fn get_enum_name(expr: &Expr) -> Option<String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(_) = &expr.params[0].node_type {
                return Some(decl.name.clone());
            }
        }
    }
    None
}

/// Get dependencies for a type (struct or enum-with-payloads)
fn get_type_dependencies(expr: &Expr) -> Vec<String> {
    if is_struct_declaration(expr) {
        get_struct_dependencies(expr)
    } else if is_enum_declaration(expr) && is_enum_with_payloads(expr) {
        get_enum_dependencies(expr)
    } else {
        Vec::new()
    }
}

/// Get name for a type (struct or enum-with-payloads)
fn get_type_name(expr: &Expr) -> Option<String> {
    if is_struct_declaration(expr) {
        get_struct_name(expr)
    } else if is_enum_declaration(expr) && is_enum_with_payloads(expr) {
        get_enum_name(expr)
    } else {
        None
    }
}

/// Topologically sort type declarations (structs and enums-with-payloads) by their dependencies
/// Returns indices into the original vector in sorted order
fn topological_sort_types(types: &[&Expr]) -> Vec<usize> {
    // Build name -> index map
    let mut name_to_idx: HashMap<String, usize> = HashMap::new();
    for (idx, expr) in types.iter().enumerate() {
        if let Some(name) = get_type_name(expr) {
            name_to_idx.insert(name, idx);
        }
    }

    // Build adjacency list (dependencies)
    let mut deps: Vec<Vec<usize>> = vec![Vec::new(); types.len()];
    for (idx, dep_expr) in types.iter().enumerate() {
        for dep_name in get_type_dependencies(dep_expr) {
            if let Some(&dep_idx) = name_to_idx.get(&dep_name) {
                if dep_idx != idx {
                    deps[idx].push(dep_idx);
                }
            }
        }
    }

    // Kahn's algorithm for topological sort
    // If A depends on B, B must come first, so reverse the edges
    let mut reverse_deps: Vec<Vec<usize>> = vec![Vec::new(); types.len()];
    for (idx, dep_list) in deps.iter().enumerate() {
        for &dep in dep_list {
            reverse_deps[dep].push(idx);
        }
    }

    // Calculate in-degree for reversed graph
    let mut in_degree: Vec<usize> = vec![0; types.len()];
    for dep_list in &reverse_deps {
        for &dep in dep_list {
            in_degree[dep] += 1;
        }
    }

    let mut queue: Vec<usize> = Vec::new();
    for (idx, &queue_degree) in in_degree.iter().enumerate() {
        if queue_degree == 0 {
            queue.push(idx);
        }
    }

    let mut result = Vec::new();
    while let Some(idx) = queue.pop() {
        result.push(idx);
        for &next in &reverse_deps[idx] {
            in_degree[next] -= 1;
            if in_degree[next] == 0 {
                queue.push(next);
            }
        }
    }

    // If we couldn't sort all (cycle), just append remaining in original order
    if result.len() < types.len() {
        for idx in 0..types.len() {
            if !result.contains(&idx) {
                result.push(idx);
            }
        }
    }

    result
}

/// Hoist variadic arguments into a til_Array
/// Returns the array variable name, or None if no variadic args
/// Also returns the element type for use in Array.delete
fn hoist_variadic_args(
    elem_type: &str,
    variadic_args: &[&Expr],
    already_hoisted: &std::collections::HashMap<usize, String>,
    regular_count: usize,  // Offset for indexing into already_hoisted
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<String, String> {
    let indent_str = "    ".repeat(indent);
    let arr_var = next_mangled(ctx);
    let err_suffix = next_mangled(ctx);
    let variadic_count = variadic_args.len();

    // Declare the array variable
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("Array ");
    output.push_str(&arr_var);
    output.push_str(";\n");

    // Declare error var for Array.set (IndexOutOfBoundsError)
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("IndexOutOfBoundsError __attribute__((unused)) _err_idx_");
    output.push_str(&err_suffix);
    output.push_str(";\n");

    // Hoist variadic args into temp vars (needed to pass address to Array.set)
    let mut arg_temps: Vec<String> = Vec::new();
    let c_elem_type = format!("{}{}", TIL_PREFIX, elem_type);
    for (i, arg) in variadic_args.iter().enumerate() {
        let hoisted_idx = regular_count + i;
        if let Some(temp) = already_hoisted.get(&hoisted_idx) {
            // Already hoisted, use that temp
            arg_temps.push(temp.clone());
        } else {
            // Need to hoist into a temp
            // Bug #143: Use emit_arg_string to properly handle nested FCalls that need by-ref
            let arg_str = emit_arg_string(arg, None, false, output, indent, ctx, context)?;
            let temp_var = next_mangled(ctx);
            output.push_str(&indent_str);
            output.push_str(&c_elem_type);
            output.push_str(" ");
            output.push_str(&temp_var);
            output.push_str(" = ");
            output.push_str(&arg_str);
            output.push_str(";\n");
            arg_temps.push(temp_var);
        }
    }

    // Bug #60: Hoist Type and I64 literals for Array.new call
    // Type param needs hoisting because we can't take address of string literal for const char* const*
    let type_temp = next_mangled(ctx);
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("Type ");
    output.push_str(&type_temp);
    output.push_str(" = \"");
    output.push_str(elem_type);
    output.push_str("\";\n");

    // Capacity param needs hoisting because we can't take address of integer literal
    let count_temp = next_mangled(ctx);
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("I64 ");
    output.push_str(&count_temp);
    output.push_str(" = ");
    output.push_str(&variadic_count.to_string());
    output.push_str(";\n");

    // Emit Array.new call (non-throwing, panics internally on malloc failure)
    // til_Array arr = til_Array_new(type_temp, &count_temp);
    output.push_str(&indent_str);
    output.push_str(&arr_var);
    output.push_str(" = ");
    output.push_str(TIL_PREFIX);
    output.push_str("Array_new(");
    output.push_str(&type_temp);
    output.push_str(", &");
    output.push_str(&count_temp);
    output.push_str(");\n");

    // Declare status variable for Array.set calls
    output.push_str(&indent_str);
    output.push_str("int __attribute__((unused)) _arr_status_");
    output.push_str(&err_suffix);
    output.push_str(";\n");

    // Emit Array.set for each variadic arg
    for (i, temp) in arg_temps.iter().enumerate() {
        // Bug #60: Hoist index literal because we can't take address of integer literal
        let idx_temp = next_mangled(ctx);
        output.push_str(&indent_str);
        output.push_str(TIL_PREFIX);
        output.push_str("I64 ");
        output.push_str(&idx_temp);
        output.push_str(" = ");
        output.push_str(&i.to_string());
        output.push_str(";\n");

        // int _status = til_Array_set(&_err_idx, &arr, &idx_temp, (til_Dynamic*)&temp);
        output.push_str(&indent_str);
        output.push_str("_arr_status_");
        output.push_str(&err_suffix);
        output.push_str(" = ");
        output.push_str(TIL_PREFIX);
        output.push_str("Array_set(&_err_idx_");
        output.push_str(&err_suffix);
        output.push_str(", &");
        output.push_str(&arr_var);
        output.push_str(", &");
        output.push_str(&idx_temp);
        output.push_str(", (");
        output.push_str(TIL_PREFIX);
        output.push_str("Dynamic*)&");
        output.push_str(temp);
        output.push_str(");\n");

        // Error check for Array.set (IndexOutOfBoundsError - shouldn't happen but propagate if thrown)
        output.push_str(&indent_str);
        output.push_str("if (_arr_status_");
        output.push_str(&err_suffix);
        output.push_str(" != 0) {\n");
        for (curr_idx, curr_throw) in ctx.current_throw_types.iter().enumerate() {
            if let ValueType::TCustom(curr_type_name) = curr_throw {
                if curr_type_name == "IndexOutOfBoundsError" {
                    output.push_str(&indent_str);
                    output.push_str("    *_err");
                    output.push_str(&(curr_idx + 1).to_string());
                    output.push_str(" = _err_idx_");
                    output.push_str(&err_suffix);
                    output.push_str("; return ");
                    output.push_str(&(curr_idx + 1).to_string());
                    output.push_str(";\n");
                    break;
                }
            }
        }
        output.push_str(&indent_str);
        output.push_str("}\n");
    }

    Ok(arr_var)
}

/// Detect if an expression is a variadic function call
/// Returns VariadicFCallInfo if it's a variadic call
fn detect_variadic_fcall(
    expr: &Expr,
    ctx: &CodegenContext,
) -> Option<VariadicFCallInfo> {
    if expr.params.is_empty() {
        return None;
    }

    // Get original TIL function name (with dots) for variadic map lookup
    let orig_func_name = get_til_func_name_string(&expr.params[0])?;

    ctx.func_variadic_args.get(&orig_func_name)
        .map(|info| VariadicFCallInfo { elem_type: info.elem_type.clone(), regular_count: info.regular_count })
}

/// Process an arg for use in a function call, returning the string to emit.
/// If the arg needs hoisting (throwing/variadic), emit hoisting code to `hoist_output`
/// and return the temp var name (with any needed prefix like & or cast).
/// Otherwise, build and return the expression string directly.
///
/// Check if an expression is a pure lvalue (simple identifier or field access chain)
/// A pure lvalue can use & directly without hoisting.
/// Returns false for FCall results, enum constructors, and struct constructors.
fn is_pure_lvalue(arg: &Expr, context: &Context) -> bool {
    match &arg.node_type {
        NodeType::Identifier(name) => {
            if arg.params.is_empty() {
                // Simple identifier is always an lvalue
                true
            } else {
                // Could be field access OR enum/struct constructor
                // Check if name.first_param is an enum constructor
                if let Some(first_param) = arg.params.first() {
                    if let NodeType::Identifier(variant) = &first_param.node_type {
                        let combined = format!("{}.{}", name, variant);
                        if context.scope_stack.is_enum_constructor(&combined) {
                            return false; // Enum constructor is NOT an lvalue
                        }
                        // Check if it's a struct type (struct constructor like Type.CONSTANT)
                        if context.scope_stack.has_struct(name) {
                            return false; // Struct constant access is NOT an lvalue (it's a global)
                        }
                    }
                }
                // Field access chain: all params must also be pure identifiers (field names)
                arg.params.iter().all(|p| matches!(&p.node_type, NodeType::Identifier(_) if p.params.is_empty()))
            }
        }
        _ => false,
    }
}

/// This is the core of the single-pass hoist+emit approach (Bug #143 fix).
/// By processing each arg once and returning the string directly, we avoid
/// the need for expression identity tracking.
fn emit_arg_string(
    arg: &Expr,
    param_type: Option<&ValueType>,
    param_by_ref: bool,
    hoist_output: &mut String,  // For emitting hoisting statements
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<String, String> {
    let _indent_str = "    ".repeat(indent);

    // Check if arg is a type identifier - emit as string literal
    if let Some(type_name) = get_type_arg_name(arg, context) {
        return Ok(format!("\"{}\"", type_name));
    }

    // Check if this is a throwing FCall - needs hoisting
    if let NodeType::FCall(_) = &arg.node_type {
        if let Some(fd) = get_fcall_func_def(context, arg) {
            if !fd.throw_types.is_empty() {
                // This is a throwing call - must hoist
                return emit_throwing_arg_string(arg, &fd, param_type, param_by_ref, hoist_output, indent, ctx, context);
            }
        }
    }

    // Check if this is a variadic FCall (even if not throwing) - needs hoisting
    if let NodeType::FCall(_) = &arg.node_type {
        if let Some(vi) = detect_variadic_fcall(arg, ctx) {
            return emit_variadic_arg_string(arg, &vi, param_type, param_by_ref, hoist_output, indent, ctx, context);
        }
    }

    // Check if param type is Dynamic - need special handling
    let is_dynamic = matches!(param_type, Some(ValueType::TCustom(name)) if name == "Dynamic");

    if is_dynamic {
        // For Dynamic params, need (til_Dynamic*)& prefix
        // Check if it's a pure lvalue (simple var or field access chain)
        if is_pure_lvalue(arg, context) {
            if let NodeType::Identifier(name) = &arg.node_type {
                if arg.params.is_empty() {
                    // Simple identifier - check if already a pointer
                    let is_already_pointer = ctx.current_ref_params.contains(name)
                        || ctx.current_variadic_params.contains_key(name)
                        || context.scope_stack.lookup_symbol(name)
                            .map(|sym| matches!(&sym.value_type, ValueType::TCustom(t) if t == "Dynamic"))
                            .unwrap_or(false);
                    if is_already_pointer {
                        // Bug #97: Use type-mangled name
                        return Ok(format!("({}Dynamic*){}", TIL_PREFIX, til_var_name_from_context(name, context)));
                    }
                }
            }
            // Pure lvalue (simple var or field access) - emit with & directly
            let mut lvalue_str = String::new();
            emit_expr(arg, &mut lvalue_str, 0, ctx, context)?;
            return Ok(format!("({}Dynamic*)&{}", TIL_PREFIX, lvalue_str));
        }
        // String literals (compound literals are lvalues in C99+, so &((til_Str){...}) works)
        // BUT integer literals are NOT lvalues, so they need hoisting
        if let NodeType::LLiteral(Literal::Str(_)) = &arg.node_type {
            let mut lit_str = String::new();
            emit_expr(arg, &mut lit_str, 0, ctx, context)?;
            return Ok(format!("({}Dynamic*)&{}", TIL_PREFIX, lit_str));
        }
        // Non-lvalue (FCall result, etc.) - need to hoist
        let expr_str = if let NodeType::FCall(_) = &arg.node_type {
            emit_fcall_arg_string(arg, hoist_output, indent, ctx, context)?
        } else {
            let mut s = String::new();
            emit_expr(arg, &mut s, 0, ctx, context)?;
            s
        };
        // Hoist to temp var and return pointer
        let c_type = get_c_type_for_expr(arg, context).unwrap_or_else(|_| format!("{}I64", TIL_PREFIX));
        let temp_var = next_mangled(ctx);
        hoist_output.push_str(&_indent_str);
        hoist_output.push_str(&c_type);
        hoist_output.push_str(" ");
        hoist_output.push_str(&temp_var);
        hoist_output.push_str(" = ");
        hoist_output.push_str(&expr_str);
        hoist_output.push_str(";\n");
        return Ok(format!("({}Dynamic*)&{}", TIL_PREFIX, temp_var));
    }

    // Check if param is by-ref (mut) - need & prefix
    if param_by_ref {
        // Check if it's a pure lvalue (simple var or field access chain)
        if is_pure_lvalue(arg, context) {
            if let NodeType::Identifier(name) = &arg.node_type {
                if arg.params.is_empty() {
                    // Simple identifier - check if already a pointer
                    let is_already_pointer = ctx.current_ref_params.contains(name)
                        || ctx.current_variadic_params.contains_key(name);
                    if is_already_pointer {
                        // Bug #97: Use type-mangled name
                        return Ok(til_var_name_from_context(name, context));
                    }
                }
            }
            // Pure lvalue - emit with & directly
            let mut lvalue_str = String::new();
            emit_expr(arg, &mut lvalue_str, 0, ctx, context)?;
            return Ok(format!("&{}", lvalue_str));
        }
        // String literals are also lvalues in C99+
        if let NodeType::LLiteral(Literal::Str(_)) = &arg.node_type {
            let mut s = String::new();
            emit_expr(arg, &mut s, 0, ctx, context)?;
            return Ok(format!("&{}", s));
        }
        // Non-lvalue (FCall result, etc.) - need to hoist
        let expr_str = if let NodeType::FCall(_) = &arg.node_type {
            emit_fcall_arg_string(arg, hoist_output, indent, ctx, context)?
        } else if let NodeType::Identifier(name) = &arg.node_type {
            // Handle UFCS chain: _[FCall, field...] - process FCall with emit_arg_string, append fields
            if name == "_" && !arg.params.is_empty() {
                if let NodeType::FCall(_) = &arg.params[0].node_type {
                    let base_str = emit_arg_string(&arg.params[0], None, false, hoist_output, indent, ctx, context)?;
                    let mut result = base_str;
                    for field_param in arg.params.iter().skip(1) {
                        if let NodeType::Identifier(field) = &field_param.node_type {
                            result.push('.');
                            result.push_str(field);
                        }
                    }
                    result
                } else {
                    let mut s = String::new();
                    emit_expr(arg, &mut s, 0, ctx, context)?;
                    s
                }
            } else {
                let mut s = String::new();
                emit_expr(arg, &mut s, 0, ctx, context)?;
                s
            }
        } else {
            let mut s = String::new();
            emit_expr(arg, &mut s, 0, ctx, context)?;
            s
        };
        let c_type = get_c_type_for_expr(arg, context).unwrap_or_else(|_| format!("{}I64", TIL_PREFIX));
        let temp_var = next_mangled(ctx);
        hoist_output.push_str(&_indent_str);
        hoist_output.push_str(&c_type);
        hoist_output.push_str(" ");
        hoist_output.push_str(&temp_var);
        hoist_output.push_str(" = ");
        hoist_output.push_str(&expr_str);
        hoist_output.push_str(";\n");
        return Ok(format!("&{}", temp_var));
    }

    // For non-throwing, non-variadic FCalls, recursively process nested args
    if let NodeType::FCall(_) = &arg.node_type {
        return emit_fcall_arg_string(arg, hoist_output, indent, ctx, context);
    }

    // Handle UFCS result chains: Identifier("_")[FCall, field1, field2, ...]
    // After UFCS desugaring, method chains like x.method().field become _[FCall, field]
    // We need to process the inner FCall with emit_arg_string to handle nested by-ref args
    if let NodeType::Identifier(name) = &arg.node_type {
        if name == "_" && !arg.params.is_empty() {
            if let NodeType::FCall(_) = &arg.params[0].node_type {
                // Process the inner FCall properly
                let base_str = emit_arg_string(&arg.params[0], None, false, hoist_output, indent, ctx, context)?;
                // Append field access chain
                let mut result = base_str;
                for field_param in arg.params.iter().skip(1) {
                    if let NodeType::Identifier(field) = &field_param.node_type {
                        result.push('.');
                        result.push_str(field);
                    }
                }
                return Ok(result);
            }
        }
    }

    // For other expressions, emit to a temp string and return
    let mut expr_str = String::new();
    emit_expr(arg, &mut expr_str, 0, ctx, context)?;
    Ok(expr_str)
}

/// Helper: Emit a throwing FCall arg, hoisting it and returning temp var string
fn emit_throwing_arg_string(
    arg: &Expr,
    fd: &SFuncDef,
    param_type: Option<&ValueType>,
    param_by_ref: bool,
    hoist_output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<String, String> {
    let indent_str = "    ".repeat(indent);

    // Check for variadic EARLY so we can use by_ref=false for variadic args
    let variadic_info = detect_variadic_fcall(arg, ctx);
    let variadic_regular_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(usize::MAX);

    // First, recursively process this call's arguments
    // For variadic args (i >= regular_count), use by_ref=false because they get stored in temp vars
    let mut nested_arg_strings = Vec::new();
    if arg.params.len() > 1 {
        for (i, nested_arg) in arg.params[1..].iter().enumerate() {
            let is_variadic_arg = i >= variadic_regular_count;
            let nested_param_type = fd.args.get(i).map(|a| &a.value_type);
            let nested_by_ref = if is_variadic_arg {
                false
            } else {
                fd.args.get(i).map(|a| param_needs_by_ref(a)).unwrap_or(false)
            };
            let nested_str = emit_arg_string(nested_arg, nested_param_type, nested_by_ref, hoist_output, indent, ctx, context)?;
            nested_arg_strings.push(nested_str);
        }
    }

    // Generate temp variable for result
    let temp_var = next_mangled(ctx);
    let temp_suffix = next_mangled(ctx);

    // Get return type
    let c_type = til_type_to_c(fd.return_types.first()
        .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Throwing call has no return type"))?)
        .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))?;

    // Declare temp variable
    hoist_output.push_str(&indent_str);
    hoist_output.push_str(&c_type);
    hoist_output.push_str(" ");
    hoist_output.push_str(&temp_var);
    hoist_output.push_str(";\n");

    // Declare error variables for each throw type (skip empty struct errors)
    for (err_idx, throw_type) in fd.throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if let ValueType::TCustom(type_name) = throw_type {
            hoist_output.push_str(&indent_str);
            hoist_output.push_str(&til_name(type_name));
            hoist_output.push_str(" _err");
            hoist_output.push_str(&err_idx.to_string());
            hoist_output.push_str("_");
            hoist_output.push_str(&temp_suffix);
            hoist_output.push_str(";\n");
        }
    }

    // Build variadic array if needed (variadic_info was computed earlier)
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        // Build variadic array using the nested arg strings
        Some(emit_variadic_array_with_strings(
            &vi.elem_type,
            &nested_arg_strings[vi.regular_count..],
            hoist_output, indent, ctx
        )?)
    } else {
        None
    };

    // Emit the function call with output pointers
    hoist_output.push_str(&indent_str);
    hoist_output.push_str("int __attribute__((unused)) _status_");
    hoist_output.push_str(&temp_suffix);
    hoist_output.push_str(" = ");

    // Get function name
    let func_name = get_func_name_string(&arg.params[0])
        .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Cannot determine function name"))?;
    let orig_func_name = get_til_func_name_string(&arg.params[0]).unwrap_or_else(|| func_name.clone());
    let mangled_name = ctx.nested_func_names.get(&orig_func_name).cloned().unwrap_or(func_name.clone());

    // Emit function name
    hoist_output.push_str(TIL_PREFIX);
    hoist_output.push_str(&mangled_name);
    hoist_output.push('(');

    // First arg: output pointer for return value
    hoist_output.push_str("&");
    hoist_output.push_str(&temp_var);

    // Error output pointers (skip empty error structs - they don't have a param slot)
    for (err_idx, throw_type) in fd.throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        hoist_output.push_str(", ");
        hoist_output.push_str("&_err");
        hoist_output.push_str(&err_idx.to_string());
        hoist_output.push_str("_");
        hoist_output.push_str(&temp_suffix);
    }

    // Regular arguments (using pre-computed strings)
    let regular_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(nested_arg_strings.len());
    for arg_str in nested_arg_strings.iter().take(regular_count) {
        hoist_output.push_str(", ");
        hoist_output.push_str(arg_str);
    }

    // Variadic array pointer if present
    if let Some(arr_var) = &variadic_arr_var {
        hoist_output.push_str(", &");
        hoist_output.push_str(arr_var);
    }

    hoist_output.push_str(");\n");

    // Emit error handling - check for local catches first, then propagate
    emit_error_handling(&fd.throw_types, &temp_suffix, hoist_output, indent, ctx, context)?;

    // Delete variadic array if constructed
    if let Some(arr_var) = &variadic_arr_var {
        hoist_output.push_str(&indent_str);
        hoist_output.push_str(TIL_PREFIX);
        hoist_output.push_str("Array_delete(&");
        hoist_output.push_str(arr_var);
        hoist_output.push_str(");\n");
    }

    // Return the temp var name with appropriate prefix
    format_hoisted_result(&temp_var, param_type, param_by_ref)
}

/// Helper: Emit error propagation code
fn emit_error_propagation(
    throw_types: &[ValueType],
    temp_suffix: &str,
    output: &mut String,
    indent: usize,
    ctx: &CodegenContext,
    context: &Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    output.push_str(&indent_str);
    output.push_str("if (_status_");
    output.push_str(temp_suffix);
    output.push_str(" != 0) {\n");

    for (err_idx, throw_type) in throw_types.iter().enumerate() {
        if let ValueType::TCustom(type_name) = throw_type {
            // Find matching throw type in current function
            for (curr_idx, curr_throw) in ctx.current_throw_types.iter().enumerate() {
                if let ValueType::TCustom(curr_type_name) = curr_throw {
                    if curr_type_name == type_name {
                        output.push_str(&indent_str);
                        output.push_str("    if (_status_");
                        output.push_str(temp_suffix);
                        output.push_str(" == ");
                        output.push_str(&(err_idx + 1).to_string());
                        output.push_str(") { ");
                        if !is_empty_error_struct(context, throw_type) {
                            output.push_str("*_err");
                            output.push_str(&(curr_idx + 1).to_string());
                            output.push_str(" = _err");
                            output.push_str(&err_idx.to_string());
                            output.push_str("_");
                            output.push_str(temp_suffix);
                            output.push_str("; ");
                        }
                        output.push_str("return ");
                        output.push_str(&(curr_idx + 1).to_string());
                        output.push_str("; }\n");
                        break;
                    }
                }
            }
        }
    }

    output.push_str(&indent_str);
    output.push_str("}\n");

    Ok(())
}

/// Helper: Emit error handling - checks for local catches first, then propagates
/// This replaces emit_error_propagation for throwing calls that need catch support
fn emit_error_handling(
    throw_types: &[ValueType],
    temp_suffix: &str,
    output: &mut String,
    indent: usize,
    ctx: &CodegenContext,
    context: &Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Check if there are local catch labels for any of these error types
    let mut has_local_catch = false;
    for throw_type in throw_types {
        if let ValueType::TCustom(type_name) = throw_type {
            if ctx.local_catch_labels.contains_key(type_name) {
                has_local_catch = true;
                break;
            }
        }
    }

    if has_local_catch {
        // Emit goto for each error type that has a local catch
        for (err_idx, throw_type) in throw_types.iter().enumerate() {
            if let ValueType::TCustom(type_name) = throw_type {
                if let Some(catch_info) = ctx.local_catch_labels.get(type_name) {
                    output.push_str(&indent_str);
                    output.push_str("if (_status_");
                    output.push_str(temp_suffix);
                    output.push_str(" == ");
                    output.push_str(&(err_idx + 1).to_string());
                    output.push_str(") { ");
                    // Issue #119: Skip copying empty struct errors
                    if !is_empty_error_struct(context, throw_type) {
                        output.push_str(&catch_info.temp_var);
                        output.push_str(" = _err");
                        output.push_str(&err_idx.to_string());
                        output.push_str("_");
                        output.push_str(temp_suffix);
                        output.push_str("; ");
                    }
                    output.push_str("goto ");
                    output.push_str(&catch_info.label);
                    output.push_str("; }\n");
                }
            }
        }
    } else {
        // No local catch - propagate errors
        emit_error_propagation(throw_types, temp_suffix, output, indent, ctx, context)?;
    }

    Ok(())
}

/// Helper: Format a hoisted temp var with appropriate prefix for param type
fn format_hoisted_result(
    temp_var: &str,
    param_type: Option<&ValueType>,
    param_by_ref: bool,
) -> Result<String, String> {
    let is_dynamic = matches!(param_type, Some(ValueType::TCustom(name)) if name == "Dynamic");
    if is_dynamic {
        return Ok(format!("({}Dynamic*)&{}", TIL_PREFIX, temp_var));
    }
    if param_by_ref {
        return Ok(format!("&{}", temp_var));
    }
    Ok(temp_var.to_string())
}

/// Helper: Emit a non-throwing variadic FCall arg
fn emit_variadic_arg_string(
    arg: &Expr,
    vi: &VariadicFCallInfo,
    param_type: Option<&ValueType>,
    param_by_ref: bool,
    hoist_output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<String, String> {
    let indent_str = "    ".repeat(indent);

    // Get function definition
    let fd = get_fcall_func_def(context, arg)
        .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Cannot find function definition for variadic call"))?;

    // First, recursively process this call's arguments
    // For variadic args (i >= regular_count), use by_ref=false because they get stored in temp vars
    let mut nested_arg_strings = Vec::new();
    if arg.params.len() > 1 {
        for (i, nested_arg) in arg.params[1..].iter().enumerate() {
            let is_variadic_arg = i >= vi.regular_count;
            let nested_param_type = fd.args.get(i).map(|a| &a.value_type);
            let nested_by_ref = if is_variadic_arg {
                false
            } else {
                fd.args.get(i).map(|a| param_needs_by_ref(a)).unwrap_or(false)
            };
            let nested_str = emit_arg_string(nested_arg, nested_param_type, nested_by_ref, hoist_output, indent, ctx, context)?;
            nested_arg_strings.push(nested_str);
        }
    }

    // Generate temp variable for result
    let temp_var = next_mangled(ctx);

    // Get return type
    let c_type = til_type_to_c(fd.return_types.first()
        .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Function has no return type"))?)
        .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))?;

    // Declare temp variable
    hoist_output.push_str(&indent_str);
    hoist_output.push_str(&c_type);
    hoist_output.push_str(" ");
    hoist_output.push_str(&temp_var);
    hoist_output.push_str(";\n");

    // Build variadic array using the nested arg strings
    let variadic_arr_var = emit_variadic_array_with_strings(
        &vi.elem_type,
        &nested_arg_strings[vi.regular_count..],
        hoist_output, indent, ctx
    )?;

    // Emit the function call
    hoist_output.push_str(&indent_str);
    hoist_output.push_str(&temp_var);
    hoist_output.push_str(" = ");

    // Get function name
    let func_name = get_func_name_string(&arg.params[0])
        .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Cannot determine function name"))?;
    let orig_func_name = get_til_func_name_string(&arg.params[0]).unwrap_or_else(|| func_name.clone());
    let mangled_name = ctx.nested_func_names.get(&orig_func_name).cloned().unwrap_or(func_name.clone());

    hoist_output.push_str(&til_func_name(&mangled_name));
    hoist_output.push('(');

    // Regular arguments
    let mut first = true;
    for arg_str in nested_arg_strings.iter().take(vi.regular_count) {
        if !first {
            hoist_output.push_str(", ");
        }
        first = false;
        hoist_output.push_str(arg_str);
    }

    // Variadic array pointer
    if !first {
        hoist_output.push_str(", ");
    }
    hoist_output.push_str("&");
    hoist_output.push_str(&variadic_arr_var);
    hoist_output.push_str(");\n");

    // Delete variadic array
    hoist_output.push_str(&indent_str);
    hoist_output.push_str(TIL_PREFIX);
    hoist_output.push_str("Array_delete(&");
    hoist_output.push_str(&variadic_arr_var);
    hoist_output.push_str(");\n");

    // Return the temp var name with appropriate prefix
    format_hoisted_result(&temp_var, param_type, param_by_ref)
}

/// Helper: Build variadic array using pre-computed arg strings
/// Mirrors hoist_variadic_args but uses pre-computed arg_strings instead of emit_expr
fn emit_variadic_array_with_strings(
    elem_type: &str,
    arg_strings: &[String],
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
) -> Result<String, String> {
    let indent_str = "    ".repeat(indent);
    let arr_var = next_mangled(ctx);
    let err_suffix = next_mangled(ctx);

    let elem_count = arg_strings.len();
    let c_elem_type = til_type_to_c(&ValueType::TCustom(elem_type.to_string()))
        .unwrap_or_else(|_| format!("{}I64", TIL_PREFIX));

    // Declare the array variable
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("Array ");
    output.push_str(&arr_var);
    output.push_str(";\n");

    // Declare error var for Array.set (IndexOutOfBoundsError)
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("IndexOutOfBoundsError __attribute__((unused)) _err_idx_");
    output.push_str(&err_suffix);
    output.push_str(";\n");

    // Hoist variadic args into temp vars (needed to pass address to Array.set)
    let mut arg_temps: Vec<String> = Vec::new();
    for arg_str in arg_strings.iter() {
        let temp_var = next_mangled(ctx);
        output.push_str(&indent_str);
        output.push_str(&c_elem_type);
        output.push_str(" ");
        output.push_str(&temp_var);
        output.push_str(" = ");
        output.push_str(arg_str);
        output.push_str(";\n");
        arg_temps.push(temp_var);
    }

    // Hoist Type param for Array.new
    let type_temp = next_mangled(ctx);
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("Type ");
    output.push_str(&type_temp);
    output.push_str(" = \"");
    output.push_str(elem_type);
    output.push_str("\";\n");

    // Hoist capacity param
    let count_temp = next_mangled(ctx);
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("I64 ");
    output.push_str(&count_temp);
    output.push_str(" = ");
    output.push_str(&elem_count.to_string());
    output.push_str(";\n");

    // Call Array.new (non-throwing)
    output.push_str(&indent_str);
    output.push_str(&arr_var);
    output.push_str(" = ");
    output.push_str(TIL_PREFIX);
    output.push_str("Array_new(");
    output.push_str(&type_temp);
    output.push_str(", &");
    output.push_str(&count_temp);
    output.push_str(");\n");

    // Declare status variable for Array.set calls
    output.push_str(&indent_str);
    output.push_str("int __attribute__((unused)) _arr_status_");
    output.push_str(&err_suffix);
    output.push_str(";\n");

    // Emit Array.set for each variadic arg
    for (i, temp) in arg_temps.iter().enumerate() {
        // Hoist index literal
        let idx_temp = next_mangled(ctx);
        output.push_str(&indent_str);
        output.push_str(TIL_PREFIX);
        output.push_str("I64 ");
        output.push_str(&idx_temp);
        output.push_str(" = ");
        output.push_str(&i.to_string());
        output.push_str(";\n");

        // int _status = til_Array_set(&_err_idx, &arr, &idx_temp, (til_Dynamic*)&temp);
        output.push_str(&indent_str);
        output.push_str("_arr_status_");
        output.push_str(&err_suffix);
        output.push_str(" = ");
        output.push_str(TIL_PREFIX);
        output.push_str("Array_set(&_err_idx_");
        output.push_str(&err_suffix);
        output.push_str(", &");
        output.push_str(&arr_var);
        output.push_str(", &");
        output.push_str(&idx_temp);
        output.push_str(", (");
        output.push_str(TIL_PREFIX);
        output.push_str("Dynamic*)&");
        output.push_str(temp);
        output.push_str(");\n");
    }

    Ok(arr_var)
}

/// Helper: Emit a non-throwing, non-variadic FCall, recursively processing args
fn emit_fcall_arg_string(
    arg: &Expr,
    hoist_output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<String, String> {
    // Check if this is a struct constructor - emit directly via emit_expr
    // (emit_expr handles struct constructors properly as compound literals)
    let func_name = get_func_name_string(&arg.params[0])
        .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Cannot determine function name"))?;

    // Struct constructors should be emitted as compound literals
    // But we need to recursively process named args in case they contain variadic/throwing calls
    if let Some(struct_def) = context.scope_stack.lookup_struct(&func_name).cloned() {
        // Process named args (field values) with emit_arg_string
        let mut field_values: std::collections::HashMap<String, String> = std::collections::HashMap::new();
        for named_arg in arg.params.iter().skip(1) {
            if let NodeType::NamedArg(field_name) = &named_arg.node_type {
                if let Some(value_expr) = named_arg.params.first() {
                    // Find the field's expected type
                    let field_type = struct_def.members.iter()
                        .find(|m| &m.name == field_name)
                        .map(|m| &m.value_type);
                    // Process the value with emit_arg_string
                    let value_str = emit_arg_string(value_expr, field_type, false, hoist_output, indent, ctx, context)?;
                    field_values.insert(field_name.clone(), value_str);
                }
            }
        }

        // Build the compound literal
        let mut result = format!("({}{})", TIL_PREFIX, func_name);
        if struct_def.members.is_empty() || struct_def.default_values.is_empty() {
            result.push_str("{}");
        } else {
            result.push('{');
            let mut first = true;
            for member in &struct_def.members {
                if !member.is_mut {
                    continue;  // Skip static members
                }
                if !first {
                    result.push_str(", ");
                }
                first = false;
                result.push('.');
                result.push_str(&member.name);
                result.push_str(" = ");
                if let Some(value_str) = field_values.get(&member.name) {
                    result.push_str(value_str);
                } else if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                    // Use emit_arg_string for defaults too (may contain variadic/throwing calls)
                    let default_str = emit_arg_string(default_expr, Some(&member.value_type), false, hoist_output, indent, ctx, context)?;
                    result.push_str(&default_str);
                } else {
                    // No value and no default - use zero
                    result.push('0');
                }
            }
            result.push('}');
        }
        return Ok(result);
    }

    let orig_func_name = get_til_func_name_string(&arg.params[0]).unwrap_or_else(|| func_name.clone());

    // Handle builtins that have inline codegen (don't use til_func_name prefix)
    match orig_func_name.as_str() {
        // to_ptr: generates (til_I64)&arg, not a function call
        "to_ptr" => {
            if arg.params.len() < 2 {
                return Err(arg.lang_error(&context.path, "ccodegen", "to_ptr requires 1 argument"));
            }
            let inner_arg = &arg.params[1];
            // Check if arg is a Dynamic parameter (already void*)
            let is_dynamic_param = if let NodeType::Identifier(name) = &inner_arg.node_type {
                if inner_arg.params.is_empty() {
                    if let Some(sym) = context.scope_stack.lookup_symbol(name) {
                        matches!(&sym.value_type, ValueType::TCustom(t) if t == "Dynamic")
                    } else {
                        false
                    }
                } else {
                    false
                }
            } else {
                false
            };
            if is_dynamic_param {
                if let NodeType::Identifier(name) = &inner_arg.node_type {
                    // Bug #97: Use type-mangled name
                    return Ok(format!("({}I64){}", TIL_PREFIX, til_var_name_from_context(name, context)));
                }
            }
            // Process the inner arg (may need hoisting if nested)
            let inner_str = emit_arg_string(inner_arg, None, false, hoist_output, indent, ctx, context)?;
            return Ok(format!("({}I64)&{}", TIL_PREFIX, inner_str));
        },

        // size_of: generates til_size_of(&Str), with special Str handling
        "size_of" => {
            if arg.params.len() < 2 {
                return Err(arg.lang_error(&context.path, "ccodegen", "size_of requires 1 argument"));
            }
            let type_arg = &arg.params[1];
            let mut result = String::new();
            result.push_str(TIL_PREFIX);
            result.push_str("size_of(&");
            if let NodeType::Identifier(type_name) = &type_arg.node_type {
                let is_type_var = if let Some(sym) = context.scope_stack.lookup_symbol(type_name) {
                    matches!(&sym.value_type, ValueType::TCustom(t) if t == "Type")
                } else {
                    false
                };
                if is_type_var {
                    // Bug #97: Use type-mangled name for Type variable reference
                    let c_var_name = til_var_name_from_context(type_name, context);
                    result.push_str(&format!("(({}Str){{(({}Ptr){{({}I64){}, 1}}), strlen({}), 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, c_var_name, c_var_name));
                } else {
                    // Literal type name
                    result.push_str(&format!("(({}Str){{(({}Ptr){{({}I64)\"{}\", 1}}), {}, 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, type_name, type_name.len()));
                }
            } else {
                return Err(arg.lang_error(&context.path, "ccodegen", "size_of requires type name argument"));
            }
            result.push(')');
            return Ok(result);
        },

        // enum_to_str: generates EnumType_to_str(&arg)
        "enum_to_str" => {
            if arg.params.len() < 2 {
                return Err(arg.lang_error(&context.path, "ccodegen", "enum_to_str requires 1 argument"));
            }
            let inner_arg = &arg.params[1];
            let value_type = get_value_type(context, inner_arg)?;
            if let ValueType::TCustom(enum_type_name) = value_type {
                if context.scope_stack.has_enum(&enum_type_name) {
                    // Pass Dynamic param type so enum constructors get hoisted properly
                    let dynamic_type = ValueType::TCustom("Dynamic".to_string());
                    let inner_str = emit_arg_string(inner_arg, Some(&dynamic_type), false, hoist_output, indent, ctx, context)?;
                    // inner_str will be "(til_Dynamic*)&x" for lvalues or "(til_Dynamic*)&_tmpX" for hoisted
                    // Strip the Dynamic prefix and keep just the &...
                    let dynamic_prefix = format!("({}Dynamic*)", TIL_PREFIX);
                    let ref_str = if inner_str.starts_with(&dynamic_prefix) {
                        inner_str[dynamic_prefix.len()..].to_string()
                    } else {
                        format!("&{}", inner_str)
                    };
                    return Ok(format!("{}_to_str({})", til_name(&enum_type_name), ref_str));
                }
            }
            // Fall through to emit_expr for non-enum case
            let mut expr_str = String::new();
            emit_expr(arg, &mut expr_str, 0, ctx, context)?;
            return Ok(expr_str);
        },

        // enum_get_payload_type: generates PayloadType_to_str(&enum_expr.payload.VariantName)
        // Args: enum_get_payload_type(enum_expr, VariantName, PayloadType)
        "enum_get_payload_type" => {
            if arg.params.len() < 4 {
                return Err(arg.lang_error(&context.path, "ccodegen", "enum_get_payload_type requires 3 arguments"));
            }
            let enum_arg = &arg.params[1];
            let variant_arg = &arg.params[2];
            let payload_type_arg = &arg.params[3];

            // Get variant name
            let variant_name = if let NodeType::Identifier(name) = &variant_arg.node_type {
                name.clone()
            } else {
                return Err(arg.lang_error(&context.path, "ccodegen", "enum_get_payload_type: variant must be identifier"));
            };

            // Get payload type name
            let payload_type_name = if let NodeType::Identifier(name) = &payload_type_arg.node_type {
                name.clone()
            } else {
                return Err(arg.lang_error(&context.path, "ccodegen", "enum_get_payload_type: payload type must be identifier"));
            };

            // Emit enum expression
            let mut enum_str = String::new();
            emit_expr(enum_arg, &mut enum_str, 0, ctx, context)?;

            // Generate: PayloadType_to_str(&enum_expr.payload.VariantName)
            return Ok(format!("{}_to_str(&{}.payload.{})",
                til_name(&payload_type_name), enum_str, variant_name));
        },

        // type_as_str: generates Str literal or Str from Type variable
        "type_as_str" => {
            if arg.params.len() < 2 {
                return Err(arg.lang_error(&context.path, "ccodegen", "type_as_str requires 1 argument"));
            }
            let type_arg = &arg.params[1];
            if let NodeType::Identifier(type_name) = &type_arg.node_type {
                // Check if this is a Type variable or a literal type name
                let is_type_var = if let Some(sym) = context.scope_stack.lookup_symbol(type_name) {
                    matches!(&sym.value_type, ValueType::TCustom(t) if t == "Type")
                } else {
                    false
                };
                if is_type_var {
                    // Type variable - already a const char*, wrap in Str struct literal
                    // Bug #97: Use type-mangled name for Type variable reference
                    let c_var_name = til_var_name_from_context(type_name, context);
                    return Ok(format!("(({}Str){{(({}Ptr){{({}I64){}, 1}}), strlen({}), 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, c_var_name, c_var_name));
                } else {
                    // Literal type name - create Str compound literal
                    return Ok(format!("(({}Str){{(({}Ptr){{({}I64)\"{}\", 1}}), {}, 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, type_name, type_name.len()));
                }
            } else {
                return Ok(format!("(({}Str){{(({}Ptr){{({}I64)\"unknown\", 1}}), 7, 0}})",
                    TIL_PREFIX, TIL_PREFIX, TIL_PREFIX));
            }
        },

        _ => {}  // Not a special builtin, continue below
    }

    // For non-throwing, non-variadic FCalls, we still need to recursively process args
    // to hoist any nested throwing/variadic calls

    let fd_opt = get_fcall_func_def(context, arg);

    // Process nested args
    let mut nested_arg_strings = Vec::new();
    if arg.params.len() > 1 {
        for (i, nested_arg) in arg.params[1..].iter().enumerate() {
            let nested_param_type = fd_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| &a.value_type));
            let nested_by_ref = fd_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| param_needs_by_ref(a))).unwrap_or(false);
            let nested_str = emit_arg_string(nested_arg, nested_param_type, nested_by_ref, hoist_output, indent, ctx, context)?;
            nested_arg_strings.push(nested_str);
        }
    }

    // Build the call string
    let mangled_name = ctx.nested_func_names.get(&orig_func_name).cloned().unwrap_or(func_name.clone());

    // Check if this is an enum constructor (Type_Variant) - need til_Type_make_Variant
    let is_enum_constructor = if func_name.contains('_') {
        let parts: Vec<&str> = func_name.splitn(2, '_').collect();
        if parts.len() == 2 {
            context.scope_stack.lookup_enum(parts[0])
                .map(|e| e.contains_key(parts[1]))
                .unwrap_or(false)
        } else {
            false
        }
    } else {
        false
    };

    let mut call_str = String::new();
    if is_enum_constructor {
        let parts: Vec<&str> = func_name.splitn(2, '_').collect();
        call_str.push_str(TIL_PREFIX);
        call_str.push_str(parts[0]);
        call_str.push_str("_make_");
        call_str.push_str(parts[1]);
    } else {
        call_str.push_str(&til_func_name(&mangled_name));
    }
    call_str.push('(');

    for (i, arg_str) in nested_arg_strings.iter().enumerate() {
        if i > 0 {
            call_str.push_str(", ");
        }
        call_str.push_str(arg_str);
    }

    call_str.push(')');

    Ok(call_str)
}

/// Helper: Get C type for an expression (for hoisting declarations)
fn get_c_type_for_expr(
    arg: &Expr,
    context: &Context,
) -> Result<String, String> {
    match &arg.node_type {
        NodeType::LLiteral(Literal::Str(_)) => Ok(format!("{}Str", TIL_PREFIX)),
        NodeType::LLiteral(Literal::Number(_)) => Ok(format!("{}I64", TIL_PREFIX)),
        NodeType::FCall(_) => {
            if let Some(fd) = get_fcall_func_def(context, arg) {
                if let Some(ret_type) = fd.return_types.first() {
                    return til_type_to_c(ret_type)
                        .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e));
                }
            }
            // Check for struct/enum constructor
            if let Some(func_name) = get_fcall_func_name(arg) {
                if context.scope_stack.has_struct(&func_name) {
                    return Ok(til_name(&func_name));
                }
                // Check enum constructor
                if func_name.contains('_') {
                    let parts: Vec<&str> = func_name.splitn(2, '_').collect();
                    if parts.len() == 2 && context.scope_stack.has_enum(parts[0]) {
                        return Ok(til_name(parts[0]));
                    }
                }
            }
            Err(arg.lang_error(&context.path, "ccodegen", "Cannot determine type for FCall"))
        }
        NodeType::Identifier(name) if !arg.params.is_empty() => {
            // Bug #143: Handle UFCS chain with field access: _[FCall, field1, field2, ...]
            // After UFCS desugaring, x.method().field1.field2 becomes _[FCall, field1, field2]
            if name == "_" {
                if let Some(first_param) = arg.params.first() {
                    if let NodeType::FCall(_) = &first_param.node_type {
                        // Get the return type of the FCall
                        let fcall_type = get_c_type_for_expr(first_param, context)?;
                        // Navigate through field access chain
                        if arg.params.len() == 1 {
                            return Ok(fcall_type);
                        }
                        // Get the struct name from the C type (strip til_ prefix)
                        let struct_name = fcall_type.strip_prefix(TIL_PREFIX).unwrap_or(&fcall_type);
                        let mut current_type = struct_name.to_string();
                        for field_param in arg.params.iter().skip(1) {
                            if let NodeType::Identifier(field_name) = &field_param.node_type {
                                if let Some(chain_struct_def) = context.scope_stack.lookup_struct(&current_type) {
                                    let mut found = false;
                                    for m in &chain_struct_def.members {
                                        if &m.name == field_name {
                                            if let ValueType::TCustom(next_struct) = &m.value_type {
                                                current_type = next_struct.clone();
                                            } else {
                                                // Final type is not a struct - convert and return
                                                return til_type_to_c(&m.value_type)
                                                    .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e));
                                            }
                                            found = true;
                                            break;
                                        }
                                    }
                                    if !found {
                                        return Err(arg.lang_error(&context.path, "ccodegen",
                                            &format!("Field '{}' not found on struct '{}'", field_name, current_type)));
                                    }
                                } else {
                                    return Err(arg.lang_error(&context.path, "ccodegen",
                                        &format!("Expected struct type for field access, got '{}'", current_type)));
                                }
                            }
                        }
                        // If we ended on a struct type, return it
                        return Ok(til_name(&current_type));
                    }
                }
            }
            // Type-qualified call or field access
            if let Some(typeq_first_param) = arg.params.first() {
                if let NodeType::Identifier(field_or_variant) = &typeq_first_param.node_type {
                    // Check enum constructor
                    if context.scope_stack.lookup_enum(name)
                        .map(|e| e.contains_key(field_or_variant))
                        .unwrap_or(false) {
                        return Ok(til_name(name));
                    }
                    // Check instance field access (variable.field)
                    if let Some(sym) = context.scope_stack.lookup_symbol(name) {
                        if let ValueType::TCustom(struct_name) = &sym.value_type {
                            if let Some(instance_struct_def) = context.scope_stack.lookup_struct(struct_name) {
                                for m in &instance_struct_def.members {
                                    if &m.name == field_or_variant {
                                        return til_type_to_c(&m.value_type)
                                            .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e));
                                    }
                                }
                            }
                        }
                    }
                    // Check static field access on struct/namespace (StructName.field)
                    if let Some(static_struct_def) = context.scope_stack.lookup_struct(name) {
                        for m in &static_struct_def.members {
                            if &m.name == field_or_variant {
                                return til_type_to_c(&m.value_type)
                                    .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e));
                            }
                        }
                    }
                }
            }
            Err(arg.lang_error(&context.path, "ccodegen", "Cannot determine type"))
        }
        _ => Err(arg.lang_error(&context.path, "ccodegen", "Cannot determine type for expression")),
    }
}

// Emit C code from AST (multi-pass architecture)
pub fn emit(ast: &Expr, context: &mut Context) -> Result<String, String> {
    std::fs::write("tmp/debug_ccodegen.txt", "emit called\n").ok();
    let mut output = String::new();
    let mut ctx = CodegenContext::new();

    // C boilerplate
    output.push_str("#include <stdio.h>\n");
    output.push_str("#include <stdlib.h>\n");
    output.push_str("#include <string.h>\n\n");
    output.push_str(&format!("typedef unsigned char {}U8;\n", TIL_PREFIX));
    output.push_str(&format!("typedef long long {}I64;\n", TIL_PREFIX));
    output.push_str(&format!("typedef struct {}Bool {{ {}U8 data; }} {}Bool;\n", TIL_PREFIX, TIL_PREFIX, TIL_PREFIX));
    // Dynamic and Type are special placeholder types
    output.push_str(&format!("typedef void* {}Dynamic;\n", TIL_PREFIX));
    output.push_str(&format!("typedef const char* {}Type;\n\n", TIL_PREFIX));

    // Pass 0: collect function info (throw types, return types) for call-site generation
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            collect_func_info(child, &mut ctx);
        }
    }

    // Pass 0a: collect nested function info for hoisting (populates hoisted_prototypes and nested_func_names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            collect_nested_func_info(child, &mut ctx, context, None)?;
        }
    }

    // Pass 0b: emit forward declarations for all structs and enums-with-payloads
    // (enums with payloads are implemented as structs in C, so they need forward declarations too)
    // Skip I64, U8, Bool, Dynamic, Type - these are primitive typedefs defined in boilerplate
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                if let NodeType::Declaration(decl) = &child.node_type {
                    if decl.name == "I64" || decl.name == "U8" || decl.name == "Bool"
                        || decl.name == "Dynamic" || decl.name == "Type" {
                        continue; // Skip - these are primitive typedefs
                    }
                    let struct_name = til_name(&decl.name);
                    output.push_str("typedef struct ");
                    output.push_str(&struct_name);
                    output.push_str(" ");
                    output.push_str(&struct_name);
                    output.push_str(";\n");
                }
            }
            // Also forward-declare enums with payloads (they're implemented as structs)
            if is_enum_declaration(child) && is_enum_with_payloads(child) {
                if let NodeType::Declaration(decl) = &child.node_type {
                    let enum_name = til_name(&decl.name);
                    output.push_str("typedef struct ");
                    output.push_str(&enum_name);
                    output.push_str(" ");
                    output.push_str(&enum_name);
                    output.push_str(";\n");
                }
            }
        }
        output.push_str("\n");
    }

    // Pass 1a: emit simple enums (no payloads) - safe to emit early, structs may use them as fields
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) && !is_enum_with_payloads(child) {
                emit_enum_declaration(child, &mut output)?;
            }
        }
    }

    // Pass 1b: emit all structs and enums-with-payloads in topologically sorted order
    // Both are "complex types" that can depend on each other
    if let NodeType::Body = &ast.node_type {
        let type_decls: Vec<&Expr> = ast.params.iter()
            .filter(|child| {
                is_struct_declaration(child) ||
                (is_enum_declaration(child) && is_enum_with_payloads(child))
            })
            .collect();
        let sorted_indices = topological_sort_types(&type_decls);
        for idx in sorted_indices {
            let child = type_decls[idx];
            if is_struct_declaration(child) {
                emit_struct_declaration(child, &mut output)?;
            } else {
                emit_enum_declaration(child, &mut output)?;
            }
        }
    }

    // Pass 2: emit function prototypes (forward declarations)
    // 2a: top-level functions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_prototype(child, context, &mut output)?;
            }
        }
    }
    // 2b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_prototypes(child, context, &mut output)?;
            }
        }
    }
    // 2b2: Issue #108 - namespace functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_namespace_definition(child) {
                emit_namespace_func_prototypes(child, context, &mut output)?;
            }
        }
    }
    // 2c: hoisted nested function prototypes (collected in Pass 0a)
    if !ctx.hoisted_prototypes.is_empty() {
        output.push_str("\n// Nested function prototypes (hoisted)\n");
        for proto in &ctx.hoisted_prototypes {
            output.push_str(proto);
        }
    }
    output.push_str("\n");

    // Pass 3: include external C interface (after structs and forward decls)
    // Use angle brackets to search only -I paths (src/), not the current directory
    // This avoids including generated c/self/ext.c instead of the hand-written src/ext.c
    output.push_str("#include <ext.c>\n\n");

    // Pass 4: emit struct constants (non-mut, non-function fields with mangled names)
    // Also emits size_of constants for each struct
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_constants(child, &mut output, &mut ctx, context)?;
            }
        }
    }

    // Pass 4a: emit size_of constants for enums
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) {
                emit_enum_size_of_constant(child, &mut output, &mut ctx)?;
            }
        }
    }

    // Pass 4a2: emit enum_to_str functions for all enums
    // This must come after structs are defined (Str is needed for return type)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) {
                emit_enum_to_str_for_declaration(child, &mut output, context)?;
            }
        }
    }

    // Pass 4b: emit top-level constants (non-mut declarations with literal values)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_constant_declaration(child) {
                emit_constant_declaration(child, &mut output, &mut ctx, context)?;
            }
        }
    }

    // Pass 4c: emit global declarations (non-constant, non-func/struct/enum declarations)
    // These need to be file-scope statics so functions can access them
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_global_declaration(child) {
                emit_global_declaration(child, &mut output, &mut ctx, context)?;
            }
        }
    }

    // Pass 4c2 (Bug #133 fix): emit static arrays for precomputed heap values
    // This serializes Vec/List contents to static arrays so Ptr fields can reference them
    emit_precomputed_static_arrays(&mut output, &mut ctx, context)?;

    // Pass 4d: emit til_size_of function (runtime type size lookup)
    emit_size_of_function(&mut output, &ctx);

    output.push_str("\n");

    // Pass 5: emit function definitions
    // 5a: top-level functions
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_func_declaration(child) {
                emit_func_declaration(child, &mut output, &mut ctx, context)?;
            }
        }
    }
    // 5b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_bodies(child, &mut output, &mut ctx, context)?;
            }
        }
    }
    // 5b2: Issue #108 - namespace functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_namespace_definition(child) {
                emit_namespace_func_bodies(child, &mut output, &mut ctx, context)?;
            }
        }
    }

    // 5c: hoisted nested function definitions
    // These were collected during emit_func_declaration when encountering nested functions
    // (prototypes were already emitted in Pass 2c)
    if !ctx.hoisted_functions.is_empty() {
        output.push_str("\n// Hoisted nested function definitions\n");
        for func_code in &ctx.hoisted_functions {
            output.push_str(func_code);
        }
    }

    // Check if main has variadic args (needs argc/argv)
    let main_has_variadic = if context.mode_def.needs_main_proc {
        match context.scope_stack.lookup_func("main") {
            Some(fd) => fd.args.iter().any(|a| matches!(&a.value_type, ValueType::TMulti(_))),
            None => false,
        }
    } else {
        false
    };

    // Main function - always name params (unnamed triggers -Wc23-extensions on clang)
    output.push_str("int main(int argc, char** argv) {\n");
    if !main_has_variadic {
        // Suppress -Wunused-parameter when argc/argv not used
        output.push_str("    (void)argc; (void)argv;\n");
    }

    // Re-populate declared_vars with global declarations (functions clear declared_vars)
    // This ensures global declarations emit only assignments in main(), not redeclarations
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_global_declaration(child) {
                if let NodeType::Declaration(decl) = &child.node_type {
                    // Bug #97: Use type-mangled name
                    let type_prefix = value_type_to_c_prefix(&decl.value_type);
                    ctx.declared_vars.insert(til_var_name(&decl.name, &type_prefix));
                }
            }
        }
    }

    // Pass 6: emit non-struct, non-function, non-enum, non-constant statements
    // Collect them into a Vec and use emit_stmts for proper variadic/throwing call handling
    // Note: global declarations are still included but will emit only assignments since they're already declared
    if let NodeType::Body = &ast.node_type {
        let main_stmts: Vec<Expr> = ast.params.iter()
            .filter(|child| {
                // Skip true/false declarations - they're now #defines
                if let NodeType::Declaration(decl) = &child.node_type {
                    if decl.name == "true" || decl.name == "false" {
                        return false;
                    }
                }
                !is_func_declaration(child) && !is_struct_declaration(child) && !is_enum_declaration(child) && !is_constant_declaration(child)
            })
            .cloned()
            .collect();
        emit_stmts(&main_stmts, &mut output, 1, &mut ctx, context)?;
    }

    // Call til_main() for modes that require a main proc (like cli)
    if context.mode_def.needs_main_proc {
        if main_has_variadic {
            // Convert argc/argv to til_Array and pass to til_main
            // Skip argv[0] (exe path) to match interpreter behavior
            output.push_str("    til_Array _main_args = til_Array_new(\"Str\", &(til_I64){argc - 1});\n");
            output.push_str("    for (int i = 1; i < argc; i++) {\n");
            output.push_str("        til_Str _arg = {((til_Ptr){(til_I64)argv[i], 1}), strlen(argv[i]), 0};\n");
            output.push_str("        til_IndexOutOfBoundsError _set_err;\n");
            output.push_str("        til_Array_set(&_set_err, &_main_args, &(til_I64){i - 1}, (til_Dynamic*)&_arg);\n");
            output.push_str("    }\n");
            output.push_str("    til_main(&_main_args);\n");
        } else {
            output.push_str("    til_main();\n");
        }
    }

    output.push_str("    return 0;\n");
    output.push_str("}\n");

    Ok(output)
}

// Check if an expression is a struct declaration (Name := struct {...})
fn is_struct_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(_) = &expr.params[0].node_type {
                return true;
            }
        }
    }
    false
}

// Check if an expression is an enum declaration (Name := enum {...})
fn is_enum_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(_) = &expr.params[0].node_type {
                return true;
            }
        }
    }
    false
}

// Check if an expression is a top-level constant declaration (name := literal)
// Constants are non-mut declarations with literal values (numbers, strings, bools)
fn is_constant_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(decl) = &expr.node_type {
        // Must not be mutable
        if decl.is_mut {
            return false;
        }
        if !expr.params.is_empty() {
            match &expr.params[0].node_type {
                // Literal values are constants
                NodeType::LLiteral(_) => return true,
                // Bool identifiers (true/false) are constants
                NodeType::Identifier(name) if name == "true" || name == "false" => return true,
                // Skip struct, enum, and function definitions
                NodeType::StructDef(_) | NodeType::EnumDef(_) | NodeType::FuncDef(_) => return false,
                _ => return false,
            }
        }
    }
    false
}

// Emit a top-level constant declaration at file scope
fn emit_constant_declaration(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            // Bug #35: Use unique name for "_" declarations to avoid C redefinition errors
            // Bug #97: Use type-mangled names for shadowing support
            let var_name = if decl.name == "_" {
                next_mangled(ctx)
            } else {
                let type_prefix = value_type_to_c_prefix(&decl.value_type);
                til_var_name(&decl.name, &type_prefix)
            };

            // Handle literal constants (numbers, strings)
            if let NodeType::LLiteral(lit) = &expr.params[0].node_type {
                let has_str = context.scope_stack.has_struct("Str");
                // Use the declaration's explicit type if available, otherwise infer from literal
                let c_type = match lit {
                    Literal::Number(_) => {
                        // Check if declaration has explicit type annotation
                        if let ValueType::TCustom(type_name) = &decl.value_type {
                            if type_name == INFER_TYPE {
                                return Err(expr.lang_error(&context.path, "ccodegen", &format!("Declaration '{}' has INFER_TYPE - should have been resolved by typer", decl.name)));
                            }
                            format!("{}{}", TIL_PREFIX, type_name)
                        } else {
                            format!("{}I64", TIL_PREFIX)
                        }
                    },
                    Literal::Str(_) => if has_str { format!("{}Str", TIL_PREFIX) } else { "const char*".to_string() },
                    Literal::List(_) => return Ok(()), // Skip list literals for now
                };
                // Non-mut declarations are constants
                if !decl.is_mut {
                    output.push_str("const ");
                }
                output.push_str(&c_type);
                output.push_str(" ");
                output.push_str(&var_name);
                output.push_str(" = ");
                emit_literal(lit, output, context)?;
                output.push_str(";\n");
            }
            // Handle Bool constants (true/false identifiers)
            else if let NodeType::Identifier(name) = &expr.params[0].node_type {
                if name == "true" || name == "false" {
                    if !decl.is_mut {
                        output.push_str("const ");
                    }
                    output.push_str(&format!("{}Bool ", TIL_PREFIX));
                    output.push_str(&var_name);
                    output.push_str(" = ");
                    // Use struct literal instead of macro (valid constant initializer)
                    if name == "true" {
                        output.push_str(&format!("(({}Bool){{1}})", TIL_PREFIX));
                    } else {
                        output.push_str(&format!("(({}Bool){{0}})", TIL_PREFIX));
                    }
                    output.push_str(";\n");
                }
            }
        }
    }
    Ok(())
}

// Check if an expression is a non-constant top-level declaration that needs to be a global
// These are declarations that are NOT: functions, structs, enums, or literal constants
// but are still non-mut and could be referenced from function bodies
fn is_global_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(decl) = &expr.node_type {
        // Skip true/false declarations - they're handled specially
        if decl.name == "true" || decl.name == "false" {
            return false;
        }
        if !expr.params.is_empty() {
            match &expr.params[0].node_type {
                // Skip these - they have their own handling
                NodeType::StructDef(_) | NodeType::EnumDef(_) | NodeType::FuncDef(_) => return false,
                // Skip literal constants - they're handled by is_constant_declaration
                // (only non-mut literals are constants)
                NodeType::LLiteral(_) if !decl.is_mut => return false,
                // Skip true/false RHS - they're handled by is_constant_declaration
                // (only non-mut booleans are constants)
                NodeType::Identifier(name) if (name == "true" || name == "false") && !decl.is_mut => return false,
                // Everything else (function calls like EvalArena.new(), etc.) is a global
                _ => return true,
            }
        }
    }
    false
}

// Emit a global declaration as a static variable at file scope (type only, no initializer)
// The initializer will be emitted in main()
fn emit_global_declaration(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            // Bug #35: Use unique name for "_" declarations to avoid C redefinition errors
            // Bug #97: Use type-mangled names for shadowing support
            let var_name = if decl.name == "_" {
                next_mangled(ctx)
            } else {
                let type_prefix = value_type_to_c_prefix(&decl.value_type);
                til_var_name(&decl.name, &type_prefix)
            };

            // Determine the type from the initializer expression using get_value_type
            let c_type = match get_value_type(context, &expr.params[0]) {
                Ok(vt) => til_type_to_c(&vt).unwrap_or("int".to_string()),
                Err(_) => til_type_to_c(&decl.value_type).unwrap_or("int".to_string()),
            };

            // Emit static declaration (no initializer - will be set in main)
            output.push_str("static ");
            output.push_str(&c_type);
            output.push_str(" ");
            output.push_str(&var_name);
            output.push_str(";\n");

            // Track that this variable has been declared globally
            ctx.declared_vars.insert(var_name);
        }
    }
    Ok(())
}

// Collect function info (throw types, return types, names) from AST into context
// Handles both top-level functions and struct methods
fn collect_func_info(expr: &Expr, ctx: &mut CodegenContext) {
    match &expr.node_type {
        NodeType::Declaration(decl) => {
            if !expr.params.is_empty() {
                match &expr.params[0].node_type {
                    NodeType::FuncDef(func_def) => {
                        // Top-level function - check for variadic args (TMulti)
                        for (idx, func_def_arg) in func_def.args.iter().enumerate() {
                            if let ValueType::TMulti(elem_type) = &func_def_arg.value_type {
                                ctx.func_variadic_args.insert(
                                    decl.name.clone(),
                                    VariadicParamInfo {
                                        elem_type: elem_type.clone(),
                                        regular_count: idx,
                                    }
                                );
                                break; // Only one variadic arg per function
                            }
                        }
                    },
                    NodeType::StructDef(struct_def) => {
                        // Struct methods - use mangled names (StructName_methodName)
                        let struct_name = &decl.name;
                        for (member_name, default_expr) in &struct_def.default_values {
                            if let NodeType::FuncDef(func_def) = &default_expr.node_type {
                                let mangled_name = format!("{}_{}", struct_name, member_name);
                                // Check for variadic args (TMulti) in struct methods
                                for (idx, func_def_arg) in func_def.args.iter().enumerate() {
                                    if let ValueType::TMulti(elem_type) = &func_def_arg.value_type {
                                        ctx.func_variadic_args.insert(
                                            mangled_name.clone(),
                                            VariadicParamInfo {
                                                elem_type: elem_type.clone(),
                                                regular_count: idx,
                                            }
                                        );
                                        break;
                                    }
                                }
                            }
                        }
                    },
                    _ => {}
                }
            }
        },
        _ => {}
    }
}

// Collect nested function info (for hoisting): scan function bodies for nested FuncDef declarations
// This populates ctx.nested_func_names and ctx.hoisted_prototypes before we emit function bodies
fn collect_nested_func_info(expr: &Expr, ctx: &mut CodegenContext, context: &Context, parent_func_name: Option<&str>) -> Result<(), String> {
    match &expr.node_type {
        NodeType::Declaration(decl) => {
            if !expr.params.is_empty() {
                if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                    if let Some(parent) = parent_func_name {
                        // This is a nested function - record it for hoisting
                        let mangled_name = format!("{}_{}", parent, decl.name);
                        ctx.nested_func_names.insert(decl.name.clone(), mangled_name.clone());

                        // Generate prototype using emit_func_signature (handles throwing functions properly)
                        let mut proto = String::new();
                        emit_func_signature(&til_name(&mangled_name), func_def, context, &mut proto)?;
                        proto.push_str(";\n");
                        ctx.hoisted_prototypes.push(proto);

                        // Recursively check for nested functions within this nested function
                        let new_parent = mangled_name.clone();
                        for body_expr in &func_def.body {
                            collect_nested_func_info(body_expr, ctx, context, Some(&new_parent))?;
                        }
                    } else {
                        // Top-level function - scan its body for nested functions
                        for body_expr in &func_def.body {
                            collect_nested_func_info(body_expr, ctx, context, Some(&decl.name))?;
                        }
                    }
                }
            }
        },
        NodeType::Body => {
            for child in &expr.params {
                collect_nested_func_info(child, ctx, context, parent_func_name)?;
            }
        },
        NodeType::If => {
            // Check then and else branches (params[0] = condition, params[1] = then, params[2] = else)
            if expr.params.len() > 1 {
                collect_nested_func_info(&expr.params[1], ctx, context, parent_func_name)?;
            }
            if expr.params.len() > 2 {
                collect_nested_func_info(&expr.params[2], ctx, context, parent_func_name)?;
            }
        },
        NodeType::While => {
            // Check loop body (params[0] = condition, params[1] = body)
            if expr.params.len() > 1 {
                collect_nested_func_info(&expr.params[1], ctx, context, parent_func_name)?;
            }
        },
        _ => {
            // Recursively check all params for other node types
            for child in &expr.params {
                collect_nested_func_info(child, ctx, context, parent_func_name)?;
            }
        }
    }
    Ok(())
}

// Emit a struct declaration as a C struct (only mut fields become struct fields)
// Forward declarations are emitted separately, so we use "struct Name { ... };" here
fn emit_struct_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        // Skip I64, U8, Bool, Dynamic, Type - these are primitive typedefs defined in boilerplate
        if decl.name == "I64" || decl.name == "U8" || decl.name == "Bool"
            || decl.name == "Dynamic" || decl.name == "Type" {
            return Ok(());
        }
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                output.push_str("struct ");
                output.push_str(&til_name(&decl.name));
                output.push_str(" {\n");
                for member in &struct_def.members {
                    // Only emit mut fields as struct members
                    // Skip functions and non-mut fields (constants)
                    if member.is_mut {
                        if let Ok(c_type) = til_type_to_c(&member.value_type) {
                            output.push_str("    ");
                            output.push_str(&c_type);
                            output.push_str(" ");
                            output.push_str(&member.name);
                            output.push_str(";\n");
                        }
                    }
                }
                output.push_str("};\n\n");
                return Ok(());
            }
        }
    }
    Err("emit_struct_declaration: not a struct declaration".to_string())
}

// Emit struct constants (non-mut, non-function fields) with mangled names: StructName_constant
// Also emits size_of constant: til_size_of_StructName = sizeof(til_StructName)
fn emit_struct_constants(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = til_name(&decl.name);
                for member in &struct_def.members {
                    // Only emit non-mut, non-function fields as constants
                    if !member.is_mut {
                        if let Ok(c_type) = til_type_to_c(&member.value_type) {
                            // Get the default value
                            if let Some(default_val) = struct_def.default_values.get(&member.name) {
                                output.push_str("const ");
                                output.push_str(&c_type);
                                output.push_str(" ");
                                output.push_str(&struct_name);
                                output.push_str("_");
                                output.push_str(&member.name);
                                output.push_str(" = ");
                                emit_expr(default_val, output, 0, ctx, context)?;
                                output.push_str(";\n");
                            }
                        }
                    }
                }
                // Emit size_of constant for this struct
                output.push_str("const ");
                output.push_str(TIL_PREFIX);
                output.push_str("I64 ");
                output.push_str(TIL_PREFIX);
                output.push_str("size_of_");
                output.push_str(&decl.name);
                output.push_str(" = sizeof(");
                output.push_str(&struct_name);
                output.push_str(");\n");
                // Track this type for til_size_of function generation
                ctx.known_types.push(decl.name.clone());
                return Ok(());
            }
        }
    }
    Ok(()) // Not a struct, nothing to emit
}

// Emit size_of constant for an enum: til_size_of_EnumName = sizeof(til_EnumName)
fn emit_enum_size_of_constant(expr: &Expr, output: &mut String, ctx: &mut CodegenContext) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(_) = &expr.params[0].node_type {
                let enum_name = til_name(&decl.name);
                output.push_str("const ");
                output.push_str(TIL_PREFIX);
                output.push_str("I64 ");
                output.push_str(TIL_PREFIX);
                output.push_str("size_of_");
                output.push_str(&decl.name);
                output.push_str(" = sizeof(");
                output.push_str(&enum_name);
                output.push_str(");\n");
                // Track this type for til_size_of function generation
                ctx.known_types.push(decl.name.clone());
            }
        }
    }
    Ok(())
}

// Bug #133 fix: Emit static arrays for precomputed heap values (Vec, List, etc.)
// This serializes interpreter heap contents to static C arrays so Ptr fields can reference them
fn emit_precomputed_static_arrays(output: &mut String, ctx: &mut CodegenContext, context: &Context) -> Result<(), String> {
    if context.precomputed_heap_values.is_empty() {
        return Ok(());
    }

    output.push_str("\n// Bug #133: Static arrays for precomputed heap values\n");

    for phv in &context.precomputed_heap_values {
        if phv.type_name == "Vec" {
            emit_precomputed_vec_static(output, ctx, context, phv)?;
        }
        // TODO: Add List, Map support as needed
    }

    Ok(())
}

// Emit static arrays for a single precomputed Vec
fn emit_precomputed_vec_static(
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &Context,
    phv: &PrecomputedHeapValue,
) -> Result<(), String> {
    // Extract Vec contents from EvalArena
    let contents = EvalArena::extract_vec_contents(context, &phv.instance_name)
        .map_err(|e| format!("emit_precomputed_vec_static: {}", e))?;

    let var_name = &phv.var_name;

    // Use recursive helper to emit static arrays
    emit_precomputed_vec_recursive(output, ctx, context, var_name, &contents)?;

    Ok(())
}

// Recursive helper to emit static arrays for Vec contents
// Handles nested types by recursively emitting inner elements first
fn emit_precomputed_vec_recursive(
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &Context,
    var_name: &str,
    contents: &VecContents,
) -> Result<(), String> {
    let elem_type = &contents.element_type_name;
    let elem_count = contents.element_bytes.len();

    // Generate static array names
    let data_array_name = format!("_precomp_{}_data", var_name);
    let type_name_array_name = format!("_precomp_{}_type_name", var_name);

    // Emit type_name string literal
    output.push_str("static const char ");
    output.push_str(&type_name_array_name);
    output.push_str("[] = \"");
    output.push_str(elem_type);
    output.push_str("\";\n");

    // Handle different element types
    if elem_type == "Str" {
        // Vec<Str> needs two-level serialization: string data + Str structs
        emit_precomputed_vec_str_static(output, ctx, context, var_name, contents)?;
    } else if elem_type == "I64" {
        // Vec<I64> - emit array of I64 values
        output.push_str("static ");
        output.push_str(TIL_PREFIX);
        output.push_str("I64 ");
        output.push_str(&data_array_name);
        output.push_str("[");
        output.push_str(&elem_count.to_string());
        output.push_str("] = {");
        for (i, bytes) in contents.element_bytes.iter().enumerate() {
            if i > 0 {
                output.push_str(", ");
            }
            let val = i64::from_ne_bytes(bytes[..8].try_into().unwrap_or([0; 8]));
            output.push_str(&val.to_string());
        }
        output.push_str("};\n");
    } else if elem_type == "U8" {
        // Vec<U8> - emit array of U8 values
        output.push_str("static ");
        output.push_str(TIL_PREFIX);
        output.push_str("U8 ");
        output.push_str(&data_array_name);
        output.push_str("[");
        output.push_str(&elem_count.to_string());
        output.push_str("] = {");
        for (i, bytes) in contents.element_bytes.iter().enumerate() {
            if i > 0 {
                output.push_str(", ");
            }
            let val: u8 = bytes.first().copied().unwrap_or(0);
            output.push_str(&val.to_string());
        }
        output.push_str("};\n");
    } else if EvalArena::type_needs_heap_serialization(context, elem_type) {
        // Nested type that needs heap serialization (Vec, List, etc.)
        // Recursively emit inner elements first, then emit outer array
        emit_precomputed_nested_vec_static(output, ctx, context, var_name, contents)?;
    } else {
        // Other struct types - emit raw bytes as array (fallback)
        let total_bytes: usize = contents.element_bytes.iter().map(|b: &Vec<u8>| b.len()).sum();
        output.push_str("static unsigned char ");
        output.push_str(&data_array_name);
        output.push_str("[");
        output.push_str(&total_bytes.to_string());
        output.push_str("] = {");
        let mut first = true;
        for bytes in &contents.element_bytes {
            for b in bytes.iter() {
                if !first {
                    output.push_str(", ");
                }
                first = false;
                output.push_str(&(*b as u8).to_string());
            }
        }
        output.push_str("};\n");
    }

    // Store info for later use when emitting assignments in main()
    ctx.precomputed_static_arrays.insert(var_name.to_string(), PrecomputedStaticInfo {
        data_array_name,
        type_name_array_name,
    });

    Ok(())
}

// Emit static arrays for Vec containing nested types (Vec<Vec<T>>, Vec<List<T>>, etc.)
// First recursively emits inner element data, then emits outer array with patched pointers
fn emit_precomputed_nested_vec_static(
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &Context,
    var_name: &str,
    contents: &VecContents,
) -> Result<(), String> {
    let elem_type = &contents.element_type_name;
    let elem_count = contents.element_bytes.len();

    // First pass: recursively emit static arrays for each inner element
    let mut inner_data_names: Vec<String> = Vec::new();
    let mut inner_type_names: Vec<String> = Vec::new();

    for (idx, elem_bytes) in contents.element_bytes.iter().enumerate() {
        let inner_var_name = format!("{}_{}", var_name, idx);

        if elem_type == "Vec" {
            // Get the ptr field from the inner Vec struct bytes
            // Vec layout: type_name (Str), type_size (I64), ptr (Ptr), _len (I64), cap (I64)
            let str_size = context.get_type_size("Str")?;
            let ptr_offset = str_size + 8; // after type_name and type_size
            let ptr_bytes: [u8; 8] = elem_bytes[ptr_offset..ptr_offset+8].try_into()
                .map_err(|_| "emit_precomputed_nested_vec_static: failed to read inner Vec ptr")?;
            let inner_data_ptr = i64::from_ne_bytes(ptr_bytes) as usize;

            // Extract inner Vec contents from its memory location
            // We need to reconstruct VecContents from the raw bytes
            let inner_type_name = EvalArena::extract_str_from_bytes(context, elem_bytes)?;
            let inner_type_size_bytes: [u8; 8] = elem_bytes[str_size..str_size+8].try_into()
                .map_err(|_| "emit_precomputed_nested_vec_static: failed to read inner type_size")?;
            let inner_type_size = i64::from_ne_bytes(inner_type_size_bytes) as usize;

            let ptr_size = context.get_type_size("Ptr")?;
            let len_offset = ptr_offset + ptr_size;
            let inner_len_bytes: [u8; 8] = elem_bytes[len_offset..len_offset+8].try_into()
                .map_err(|_| "emit_precomputed_nested_vec_static: failed to read inner _len")?;
            let inner_len = i64::from_ne_bytes(inner_len_bytes) as usize;

            // Extract inner element bytes
            let mut inner_element_bytes = Vec::new();
            for i in 0..inner_len {
                let elem_offset = inner_data_ptr + (i * inner_type_size);
                let bytes = EvalArena::g().get(elem_offset, inner_type_size).to_vec();
                inner_element_bytes.push(bytes);
            }

            let inner_contents = VecContents {
                element_type_name: inner_type_name,
                type_size: inner_type_size,
                element_bytes: inner_element_bytes,
            };

            // Recursively emit static arrays for inner Vec
            emit_precomputed_vec_recursive(output, ctx, context, &inner_var_name, &inner_contents)?;
        }
        // TODO: Handle List and other nested types

        inner_data_names.push(format!("_precomp_{}_data", inner_var_name));
        inner_type_names.push(format!("_precomp_{}_type_name", inner_var_name));
    }

    // Second pass: emit the outer array of structs with patched pointers
    let data_array_name = format!("_precomp_{}_data", var_name);
    output.push_str("static ");
    output.push_str(TIL_PREFIX);
    output.push_str(elem_type);
    output.push_str(" ");
    output.push_str(&data_array_name);
    output.push_str("[");
    output.push_str(&elem_count.to_string());
    output.push_str("] = {\n");

    for (idx, elem_bytes) in contents.element_bytes.iter().enumerate() {
        if elem_type == "Vec" {
            // Emit Vec struct with patched pointers
            // Vec layout: type_name (Str), type_size (I64), ptr (Ptr), _len (I64), cap (I64)
            let str_size = context.get_type_size("Str")?;
            let ptr_size = context.get_type_size("Ptr")?;

            // Extract type_size
            let type_size_bytes: [u8; 8] = elem_bytes[str_size..str_size+8].try_into()
                .map_err(|_| "emit_precomputed_nested_vec_static: failed to read type_size")?;
            let type_size = i64::from_ne_bytes(type_size_bytes);

            // Extract _len
            let len_offset = str_size + 8 + ptr_size;
            let len_bytes: [u8; 8] = elem_bytes[len_offset..len_offset+8].try_into()
                .map_err(|_| "emit_precomputed_nested_vec_static: failed to read _len")?;
            let len = i64::from_ne_bytes(len_bytes);

            // Extract cap
            let cap_offset = len_offset + 8;
            let cap_bytes: [u8; 8] = elem_bytes[cap_offset..cap_offset+8].try_into()
                .map_err(|_| "emit_precomputed_nested_vec_static: failed to read cap")?;
            let cap = i64::from_ne_bytes(cap_bytes);

            output.push_str("    {.type_name = (");
            output.push_str(TIL_PREFIX);
            output.push_str("Str){.c_string = (");
            output.push_str(TIL_PREFIX);
            output.push_str("Ptr){(");
            output.push_str(TIL_PREFIX);
            output.push_str("I64)");
            output.push_str(&inner_type_names[idx]);
            output.push_str(", 1}, ._len = ");
            // Get inner type name length
            let inner_type_name = EvalArena::extract_str_from_bytes(context, elem_bytes)?;
            output.push_str(&inner_type_name.len().to_string());
            output.push_str(", .cap = 0}, .type_size = ");
            output.push_str(&type_size.to_string());
            output.push_str(", .ptr = (");
            output.push_str(TIL_PREFIX);
            output.push_str("Ptr){(");
            output.push_str(TIL_PREFIX);
            output.push_str("I64)");
            output.push_str(&inner_data_names[idx]);
            output.push_str(", 1}, ._len = ");
            output.push_str(&len.to_string());
            output.push_str(", .cap = ");
            output.push_str(&cap.to_string());
            output.push_str("}");
        }
        // TODO: Handle List and other nested types

        if idx + 1 < elem_count {
            output.push_str(",");
        }
        output.push_str("\n");
    }

    output.push_str("};\n");

    Ok(())
}

// Emit static arrays for Vec<Str> - two-level: string literals + Str structs
fn emit_precomputed_vec_str_static(
    output: &mut String,
    _ctx: &mut CodegenContext,
    context: &Context,
    var_name: &str,
    contents: &VecContents,
) -> Result<(), String> {
    let elem_count = contents.element_bytes.len();
    let ptr_size = context.get_type_size("Ptr")?;

    // First, emit the individual string literals
    for (idx, bytes) in contents.element_bytes.iter().enumerate() {
        // Extract string data from Str struct bytes
        // Str layout: c_string (Ptr with data+is_borrowed), _len (I64), cap (I64)
        // We need to read c_string.data (ptr to string) and _len
        let c_string_ptr = i64::from_ne_bytes(bytes[..8].try_into().unwrap_or([0; 8])) as usize;
        let len = i64::from_ne_bytes(bytes[ptr_size..ptr_size+8].try_into().unwrap_or([0; 8])) as usize;

        // Read the actual string bytes from arena
        let string_bytes = if c_string_ptr > 0 && len > 0 {
            EvalArena::g().get(c_string_ptr, len)
        } else {
            &[]
        };
        let string_data = String::from_utf8_lossy(string_bytes);

        output.push_str("static const char _precomp_");
        output.push_str(var_name);
        output.push_str("_str_");
        output.push_str(&idx.to_string());
        output.push_str("[] = \"");
        // Escape special characters in the string
        for ch in string_data.chars() {
            match ch {
                '"' => output.push_str("\\\""),
                '\\' => output.push_str("\\\\"),
                '\n' => output.push_str("\\n"),
                '\r' => output.push_str("\\r"),
                '\t' => output.push_str("\\t"),
                c if c.is_ascii_control() => {
                    output.push_str(&format!("\\x{:02x}", c as u8));
                }
                c => output.push(c),
            }
        }
        output.push_str("\";\n");
    }

    // Now emit the Str struct array
    let data_array_name = format!("_precomp_{}_data", var_name);
    output.push_str("static ");
    output.push_str(TIL_PREFIX);
    output.push_str("Str ");
    output.push_str(&data_array_name);
    output.push_str("[");
    output.push_str(&elem_count.to_string());
    output.push_str("] = {\n");

    for (idx, bytes) in contents.element_bytes.iter().enumerate() {
        // Extract _len from Str struct bytes
        let len = i64::from_ne_bytes(bytes[ptr_size..ptr_size+8].try_into().unwrap_or([0; 8]));

        output.push_str("    {.c_string = (");
        output.push_str(TIL_PREFIX);
        output.push_str("Ptr){(");
        output.push_str(TIL_PREFIX);
        output.push_str("I64)_precomp_");
        output.push_str(var_name);
        output.push_str("_str_");
        output.push_str(&idx.to_string());
        output.push_str(", 1}, ._len = ");  // is_borrowed = 1 (static string)
        output.push_str(&len.to_string());
        output.push_str(", .cap = 0}");
        if idx + 1 < elem_count {
            output.push_str(",");
        }
        output.push_str("\n");
    }

    output.push_str("};\n");

    Ok(())
}

// Bug #133 fix: Emit assignment for a precomputed Vec with patched Ptr fields
fn emit_precomputed_vec_assignment(
    var_name: &str,
    is_mut: bool,
    static_info: &PrecomputedStaticInfo,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    // Bug #133: Use type-mangled name (til_Vec_data, not til_data)
    let c_var_name = til_var_name(var_name, "Vec");
    let already_declared = ctx.declared_vars.contains(&c_var_name);

    // Extract Vec contents to get element count and type info
    let contents = EvalArena::extract_vec_contents(context, var_name)
        .map_err(|e| format!("emit_precomputed_vec_assignment: {}", e))?;

    let elem_count = contents.element_bytes.len() as i64;
    let type_size = contents.type_size as i64;
    let elem_type = &contents.element_type_name;

    output.push_str(&indent_str);
    if !already_declared {
        if !is_mut {
            output.push_str("const ");
        }
        output.push_str(TIL_PREFIX);
        output.push_str("Vec ");
        ctx.declared_vars.insert(c_var_name.clone());
    }
    output.push_str(&c_var_name);
    output.push_str(" = (");
    output.push_str(TIL_PREFIX);
    output.push_str("Vec){\n");

    // type_name field - point to static string
    output.push_str(&indent_str);
    output.push_str("    .type_name = (");
    output.push_str(TIL_PREFIX);
    output.push_str("Str){(");
    output.push_str(TIL_PREFIX);
    output.push_str("Ptr){(");
    output.push_str(TIL_PREFIX);
    output.push_str("I64)");
    output.push_str(&static_info.type_name_array_name);
    output.push_str(", 1}, ");  // is_borrowed = 1
    output.push_str(&elem_type.len().to_string());
    output.push_str(", 0},\n");

    // type_size field
    output.push_str(&indent_str);
    output.push_str("    .type_size = ");
    output.push_str(&type_size.to_string());
    output.push_str(",\n");

    // ptr field - point to static data array
    output.push_str(&indent_str);
    output.push_str("    .ptr = (");
    output.push_str(TIL_PREFIX);
    output.push_str("Ptr){(");
    output.push_str(TIL_PREFIX);
    output.push_str("I64)");
    output.push_str(&static_info.data_array_name);
    output.push_str(", 1},\n");  // is_borrowed = 1 (static data, don't free)

    // _len field
    output.push_str(&indent_str);
    output.push_str("    ._len = ");
    output.push_str(&elem_count.to_string());
    output.push_str(",\n");

    // cap field
    output.push_str(&indent_str);
    output.push_str("    .cap = ");
    output.push_str(&elem_count.to_string());
    output.push_str("\n");

    output.push_str(&indent_str);
    output.push_str("};\n");

    Ok(())
}

// Emit til_size_of function for runtime type size lookup
fn emit_size_of_function(output: &mut String, ctx: &CodegenContext) {
    output.push_str("\n");
    output.push_str("static inline ");
    output.push_str(TIL_PREFIX);
    output.push_str("I64 ");
    output.push_str(TIL_PREFIX);
    output.push_str("size_of(const ");
    output.push_str(TIL_PREFIX);
    output.push_str("Str* type_name) {\n");

    // All known types from structs and enums
    for type_name in &ctx.known_types {
        output.push_str("    if (strcmp((char*)type_name->c_string.data, \"");
        output.push_str(type_name);
        output.push_str("\") == 0) return ");
        output.push_str(TIL_PREFIX);
        output.push_str("size_of_");
        output.push_str(type_name);
        output.push_str(";\n");
    }

    output.push_str("    fprintf(stderr, \"size_of: unknown type %s\\n\", (char*)type_name->c_string.data);\n");
    output.push_str("    exit(1);\n");
    output.push_str("}\n");
}

// Check if an enum has any payloads
fn enum_has_payloads(enum_def: &SEnumDef) -> bool {
    for v in &enum_def.variants {
        if v.payload_type.is_some() {
            return true;
        }
    }
    false
}

// Check if an expression is an enum declaration with payloads
fn is_enum_with_payloads(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(enum_def) = &expr.params[0].node_type {
                return enum_has_payloads(enum_def);
            }
        }
    }
    false
}

// Emit an enum with payloads as a tagged union
fn emit_enum_with_payloads(enum_name: &str, enum_def: &SEnumDef, output: &mut String) -> Result<(), String> {
    // Sort variants by name for deterministic output
    let mut variants: Vec<_> = enum_def.variants.iter().collect();
    variants.sort_by_key(|v| &v.name);

    // 1. Emit tag enum: typedef enum { Color_Unknown = 0, ... } Color_Tag;
    output.push_str("typedef enum {\n");
    for (index, v) in variants.iter().enumerate() {
        let variant_name = &v.name;
        output.push_str("    ");
        output.push_str(enum_name);
        output.push_str("_");
        output.push_str(variant_name);
        output.push_str(" = ");
        output.push_str(&index.to_string());
        output.push_str(",\n");
    }
    output.push_str("} ");
    output.push_str(enum_name);
    output.push_str("_Tag;\n\n");

    // 2. Emit payload union (only for variants that have payloads)
    // typedef union { unsigned char Green; long long Number; } Color_Payload;
    let mut has_any_payload = false;
    for v in &variants {
        if v.payload_type.is_some() {
            has_any_payload = true;
            break;
        }
    }
    if has_any_payload {
        output.push_str("typedef union {\n");
        for v in &variants {
            if let Some(pt) = &v.payload_type {
                if let Ok(c_type) = til_type_to_c(pt) {
                    output.push_str("    ");
                    output.push_str(&c_type);
                    output.push_str(" ");
                    output.push_str(&v.name);
                    output.push_str(";\n");
                }
            }
        }
        output.push_str("} ");
        output.push_str(enum_name);
        output.push_str("_Payload;\n\n");
    }

    // 3. Emit wrapper struct: struct Color { til_I64 tag; Color_Payload payload; };
    // Note: typedef is already forward-declared, so we just define the struct body
    // Bug #137: Use til_I64 for tag to ensure consistent 8-byte offset for payload
    output.push_str("struct ");
    output.push_str(enum_name);
    output.push_str(" {\n");
    output.push_str("    ");
    output.push_str(TIL_PREFIX);
    output.push_str("I64 tag;\n");
    if has_any_payload {
        output.push_str("    ");
        output.push_str(enum_name);
        output.push_str("_Payload payload;\n");
    }
    output.push_str("};\n\n");

    // 4. Emit constructor functions for ALL variants (including no-payload ones)
    // This ensures consistent calling convention: Color_make_Red(42), Color_make_Unknown()
    for v in &variants {
        let variant_name = &v.name;
        let payload_type = &v.payload_type;
        output.push_str("static inline ");
        output.push_str(enum_name);
        output.push_str(" ");
        output.push_str(enum_name);
        output.push_str("_make_");
        output.push_str(variant_name);
        output.push_str("(");

        // Parameter for payload (if any)
        if let Some(pt) = payload_type {
            if let Ok(c_type) = til_type_to_c(pt) {
                output.push_str(&c_type);
                output.push_str(" value");
            }
        } else {
            output.push_str("void");
        }
        output.push_str(") {\n");

        // Constructor body
        output.push_str("    ");
        output.push_str(enum_name);
        output.push_str(" result = { .tag = ");
        output.push_str(enum_name);
        output.push_str("_");
        output.push_str(variant_name);
        output.push_str(" };\n");

        // Set payload if present
        if payload_type.is_some() {
            output.push_str("    result.payload.");
            output.push_str(variant_name);
            output.push_str(" = value;\n");
        }

        output.push_str("    return result;\n");
        output.push_str("}\n\n");
    }

    Ok(())
}

// Emit an enum declaration as a C typedef enum (for simple enums without payloads)
// or as a tagged union struct (for enums with payloads)
fn emit_enum_declaration(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(enum_def) = &expr.params[0].node_type {
                let enum_name = til_name(&decl.name);

                if enum_has_payloads(enum_def) {
                    // Phase 2: Enums with payloads - tagged union
                    return emit_enum_with_payloads(&enum_name, enum_def, output);
                }

                // Phase 1: Simple enum without payloads
                // typedef enum { EnumName_Variant1 = 0, ... } EnumName;
                output.push_str("typedef enum {\n");

                // Sort variants by name for deterministic output
                let mut variants: Vec<_> = enum_def.variants.iter().map(|v| &v.name).collect();
                variants.sort();

                for (index, variant_name) in variants.iter().enumerate() {
                    output.push_str("    ");
                    output.push_str(&enum_name);
                    output.push_str("_");
                    output.push_str(variant_name);
                    output.push_str(" = ");
                    output.push_str(&index.to_string());
                    output.push_str(",\n");
                }

                output.push_str("} ");
                output.push_str(&enum_name);
                output.push_str(";\n\n");

                // Generate constructor functions for consistency with payload enums
                // static inline EnumName EnumName_make_Variant(void) { return EnumName_Variant; }
                for variant_name in &variants {
                    output.push_str("static inline ");
                    output.push_str(&enum_name);
                    output.push_str(" ");
                    output.push_str(&enum_name);
                    output.push_str("_make_");
                    output.push_str(variant_name);
                    output.push_str("(void) { return ");
                    output.push_str(&enum_name);
                    output.push_str("_");
                    output.push_str(variant_name);
                    output.push_str("; }\n");
                }
                output.push_str("\n");

                return Ok(());
            }
        }
    }
    Err("emit_enum_declaration: not an enum declaration".to_string())
}

// Emit a _to_str function for an enum type
// Takes a const pointer since we only read the enum
// For simple enums: til_Str til_EnumName_to_str(const til_EnumName* e)
// For enums with payloads: til_Str til_EnumName_to_str(const til_EnumName* e)
fn emit_enum_to_str_function(enum_name: &str, enum_def: &SEnumDef, output: &mut String) {
    let has_payloads = enum_has_payloads(enum_def);
    let mut variants: Vec<_> = enum_def.variants.iter().map(|v| &v.name).collect();
    variants.sort();

    // Function signature - takes const pointer since we only read the enum
    output.push_str("static inline til_Str ");
    output.push_str(enum_name);
    output.push_str("_to_str(const ");
    output.push_str(enum_name);
    output.push_str("* e) {\n    switch(");
    if has_payloads {
        output.push_str("e->tag");
    } else {
        output.push_str("*e");
    }
    output.push_str(") {\n");

    // Cases - need the original (non-prefixed) enum name for the string
    let original_name = if enum_name.starts_with(TIL_PREFIX) {
        &enum_name[TIL_PREFIX.len()..]
    } else {
        enum_name
    };

    for variant in &variants {
        let full_name = format!("{}.{}", original_name, variant);
        output.push_str("        case ");
        output.push_str(enum_name);
        output.push_str("_");
        output.push_str(variant);
        // Use new Str format with Ptr { data, is_borrowed=1 }, len, cap=0
        output.push_str(": return ((til_Str){((til_Ptr){(til_I64)\"");
        output.push_str(&full_name);
        output.push_str("\", 1}), ");
        output.push_str(&full_name.len().to_string());
        output.push_str(", 0});\n");
    }

    // Default case (shouldn't happen but good for safety)
    let unknown_name = format!("{}.?", original_name);
    // Use new Str format with Ptr { data, is_borrowed=1 }, len, cap=0
    output.push_str("    }\n    return ((til_Str){((til_Ptr){(til_I64)\"");
    output.push_str(&unknown_name);
    output.push_str("\", 1}), ");
    output.push_str(&unknown_name.len().to_string());
    output.push_str(", 0});\n}\n\n");
}

// Emit _to_str function for an enum declaration node
fn emit_enum_to_str_for_declaration(
    expr: &Expr,
    output: &mut String,
    context: &mut Context,
) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        let enum_name = &decl.name;
        if let Some(enum_def) = context.scope_stack.lookup_enum(enum_name) {
            let c_enum_name = til_name(enum_name);
            emit_enum_to_str_function(&c_enum_name, &enum_def, output);
            return Ok(());
        }
    }
    Err("emit_enum_to_str_for_declaration: not an enum declaration".to_string())
}

// Emit struct function prototypes for all functions in a struct
fn emit_struct_func_prototypes(expr: &Expr, context: &Context, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = til_name(&decl.name);
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            let mangled_name = format!("{}_{}", struct_name, member.name);
                            emit_func_signature(&mangled_name, func_def, context, output)?;
                            output.push_str(";\n");
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Emit a struct function body with mangled name: StructName_funcname
fn emit_struct_func_body(struct_name: &str, member: &crate::rs::parser::Declaration, func_def: &SFuncDef, output: &mut String, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // Skip external functions
    if func_def.is_ext() {
        return Ok(());
    }

    // Set current function context
    ctx.current_throw_types = func_def.throw_types.clone();
    ctx.current_return_types = func_def.return_types.clone();
    // Track mut params for pointer dereference (-> vs .)
    ctx.current_ref_params.clear();
    // Track variadic params - they're passed as til_Array* so need dereference
    ctx.current_variadic_params.clear();
    for func_def_arg in &func_def.args {
        // Bug #60: All non-copy args are passed by pointer (mut, own, and const/default)
        if !func_def_arg.is_copy {
            ctx.current_ref_params.insert(func_def_arg.name.clone());
        }
        if let ValueType::TMulti(elem_type) = &func_def_arg.value_type {
            // elem_type is the type name string like "Bool"
            ctx.current_variadic_params.insert(func_def_arg.name.clone(), til_name(elem_type));
        }
    }

    // Push a new scope frame for this function (like interpreter does)
    let mut function_frame = ScopeFrame {
        arena_index: HashMap::new(),
        symbols: HashMap::new(),
        funcs: HashMap::new(),
        enums: HashMap::new(),
        structs: HashMap::new(),
        scope_type: ScopeType::Function,
    };
    // Register function parameters in the frame
    for func_def_arg in &func_def.args {
        function_frame.symbols.insert(func_def_arg.name.clone(), SymbolInfo {
            value_type: func_def_arg.value_type.clone(),
            is_mut: func_def_arg.is_mut,
            is_copy: func_def_arg.is_copy,
            is_own: func_def_arg.is_own,
            is_comptime_const: false,
        });
    }
    context.scope_stack.frames.push(function_frame);

    // Clear declared_vars for new function scope
    ctx.declared_vars.clear();

    let mangled_name = format!("{}_{}", struct_name, member.name);

    // Save and set current function name for deterministic temp naming (Bug #42 fix)
    let prev_function_name = ctx.current_function_name.clone();
    let prev_mangling_counter = ctx.mangling_counter;
    ctx.current_function_name = mangled_name.clone();
    ctx.mangling_counter = 0;

    emit_func_signature(&mangled_name, func_def, context, output)?;
    output.push_str(" {\n");

    // Emit function body with catch pattern detection
    emit_stmts(&func_def.body, output, 1, ctx, context)?;

    // Add implicit return at end to silence gcc -Wreturn-type warnings
    // when all paths return inside branches but gcc can't prove exhaustiveness
    if !func_def.throw_types.is_empty() {
        // Throwing functions return int (0=success, 1+=error)
        output.push_str("    return 0;\n");
    } else if !func_def.return_types.is_empty() {
        // Non-throwing functions with return type - add zero-initialized fallback
        let ret_type = til_type_to_c(&func_def.return_types[0])?;
        output.push_str(&format!("    return ({}){{0}};\n", ret_type));
    }

    output.push_str("}\n\n");

    // Restore previous function name and counter
    ctx.current_function_name = prev_function_name;
    ctx.mangling_counter = prev_mangling_counter;

    // Pop the function scope frame
    context.scope_stack.frames.pop();

    // Clear current function context
    ctx.current_throw_types.clear();
    ctx.current_return_types.clear();

    Ok(())
}

// Emit struct function bodies for all functions in a struct
fn emit_struct_func_bodies(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = til_name(&decl.name);
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            emit_struct_func_body(&struct_name, member, func_def, output, ctx, context)?;
                        }
                    }
                }
            }
        }
    }
    Ok(())
}

// Issue #108: Check if expression is a namespace definition
fn is_namespace_definition(expr: &Expr) -> bool {
    matches!(&expr.node_type, NodeType::NamespaceDef(_))
}

// Issue #108: Emit namespace function prototypes (forward declarations)
fn emit_namespace_func_prototypes(expr: &Expr, context: &Context, output: &mut String) -> Result<(), String> {
    if let NodeType::NamespaceDef(ns_def) = &expr.node_type {
        let type_name = til_name(&ns_def.type_name);
        for member in &ns_def.members {
            if let Some(func_expr) = ns_def.default_values.get(&member.name) {
                if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                    let mangled_name = format!("{}_{}", type_name, member.name);
                    emit_func_signature(&mangled_name, func_def, context, output)?;
                    output.push_str(";\n");
                }
            }
        }
    }
    Ok(())
}

// Issue #108: Emit namespace function bodies
fn emit_namespace_func_bodies(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    if let NodeType::NamespaceDef(ns_def) = &expr.node_type {
        let type_name = til_name(&ns_def.type_name);
        for member in &ns_def.members {
            if let Some(func_expr) = ns_def.default_values.get(&member.name) {
                if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                    emit_struct_func_body(&type_name, member, func_def, output, ctx, context)?;
                }
            }
        }
    }
    Ok(())
}

// Convert TIL type to C type. Returns Err if the type can't be represented in C (e.g., functions, infer)
fn til_type_to_c(til_type: &crate::rs::parser::ValueType) -> Result<String, String> {
    match til_type {
        crate::rs::parser::ValueType::TCustom(name) => {
            if name == INFER_TYPE {
                Err(format!("Cannot convert inferred type to C"))
            } else {
                // All types get TIL_PREFIX
                Ok(format!("{}{}", TIL_PREFIX, name))
            }
        },
        crate::rs::parser::ValueType::TFunction(_) => Err("Cannot convert function type to C".to_string()),
        crate::rs::parser::ValueType::TType(_) => Err("Cannot convert Type to C".to_string()),
        crate::rs::parser::ValueType::TMulti(_) => Err("Cannot convert multi-type to C".to_string()),
    }
}

// Helper to get C type name for a ValueType (for error struct definitions)
fn value_type_to_c_name(vt: &ValueType) -> Result<String, String> {
    match vt {
        ValueType::TCustom(name) => {
            // All types get TIL_PREFIX
            Ok(format!("{}{}", TIL_PREFIX, name))
        },
        _ => Err(format!("Cannot convert {:?} to C type name", vt)),
    }
}

// Emit function signature (used by both prototype and definition)
// For throwing functions:
//   int func_name(RetType* _ret, Error1* _err1, Error2* _err2, args...)
// For non-throwing:
//   RetType func_name(args...)
// Issue #119: Empty struct errors don't get error parameters - only status code matters
fn emit_func_signature(func_name: &str, func_def: &SFuncDef, context: &Context, output: &mut String) -> Result<(), String> {
    let is_throwing = !func_def.throw_types.is_empty();

    if is_throwing {
        // Throwing function returns int status code
        output.push_str("int ");
    } else {
        // Non-throwing function returns its actual type
        if func_def.return_types.is_empty() {
            output.push_str("void ");
        } else {
            let ret_type = til_type_to_c(&func_def.return_types[0])?;
            output.push_str(&ret_type);
            output.push_str(" ");
        }
    }

    output.push_str(func_name);
    output.push_str("(");

    let mut param_count = 0;

    if is_throwing {
        // Output params first: return value pointer, then error pointers
        if !func_def.return_types.is_empty() {
            let ret_type = til_type_to_c(&func_def.return_types[0])?;
            output.push_str(&ret_type);
            output.push_str("* _ret");
            param_count += 1;
        }

        for (i, throw_type) in func_def.throw_types.iter().enumerate() {
            // Issue #119: Skip empty struct errors - only status code matters
            if is_empty_error_struct(context, throw_type) {
                continue;
            }
            if param_count > 0 {
                output.push_str(", ");
            }
            let err_type = value_type_to_c_name(throw_type)?;
            output.push_str(&err_type);
            output.push_str("* _err");
            output.push_str(&(i + 1).to_string());
            param_count += 1;
        }
    }

    // Input parameters
    for func_def_arg in func_def.args.iter() {
        if param_count > 0 {
            output.push_str(", ");
        }
        // Check for variadic arg (TMulti)
        if let ValueType::TMulti(_elem_type) = &func_def_arg.value_type {
            // Variadic args are passed as til_Array* - Bug #97: use type-mangled name
            output.push_str(TIL_PREFIX);
            output.push_str("Array* ");
            // Variadic params have effective type Array in scope_stack
            output.push_str(&til_var_name(&func_def_arg.name, "Array"));
            param_count += 1;
            break; // Variadic must be last
        } else {
            let arg_type = til_type_to_c(&func_def_arg.value_type)?;

            // Bug #60: Type is already const char*, don't add extra indirection
            let is_type_param = matches!(&func_def_arg.value_type, ValueType::TCustom(name) if name == "Type");
            if func_def_arg.is_mut {
                // mut: pass by pointer so mutations are visible to caller
                output.push_str(&arg_type);
                output.push_str("* ");
            } else if func_def_arg.is_own {
                // own: pass by pointer, caller transfers ownership
                // Type is already a pointer, so pass by value
                if is_type_param {
                    output.push_str(&arg_type);
                    output.push_str(" ");
                } else {
                    output.push_str(&arg_type);
                    output.push_str("* ");
                }
            } else if func_def_arg.is_copy {
                // copy: pass by value, caller's copy is made
                output.push_str(&arg_type);
                output.push_str(" ");
            } else {
                // const (default): pass by const pointer, read-only
                // Type is already a pointer, so pass by value
                if is_type_param {
                    output.push_str(&arg_type);
                    output.push_str(" ");
                } else {
                    output.push_str("const ");
                    output.push_str(&arg_type);
                    output.push_str("* ");
                }
            }
            // Bug #97: Use type-mangled parameter name
            let type_prefix = value_type_to_c_prefix(&func_def_arg.value_type);
            output.push_str(&til_var_name(&func_def_arg.name, &type_prefix));
            param_count += 1;
        }
    }

    if param_count == 0 {
        output.push_str("void");
    }

    output.push_str(")");
    Ok(())
}

// Emit a function prototype (forward declaration)
fn emit_func_prototype(expr: &Expr, context: &Context, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                let func_name = til_name(&decl.name);
                emit_func_signature(&func_name, func_def, context, output)?;
                output.push_str(";\n");
                return Ok(());
            }
        }
    }
    Err("emit_func_prototype: not a function declaration".to_string())
}

// Check if an expression is a function declaration (name := proc/func)
fn is_func_declaration(expr: &Expr) -> bool {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(_) = &expr.params[0].node_type {
                return true;
            }
        }
    }
    false
}

// Emit a function declaration as a C function
fn emit_func_declaration(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                // Set current function context for return/throw generation
                ctx.current_throw_types = func_def.throw_types.clone();
                ctx.current_return_types = func_def.return_types.clone();
                // Track ref params for pointer dereference (-> vs .)
                ctx.current_ref_params.clear();
                // Track variadic params - they're passed as til_Array* so need dereference
                ctx.current_variadic_params.clear();
                for func_def_arg in &func_def.args {
                    // Bug #60: All non-copy args are passed by pointer (mut, own, and const/default)
                    if !func_def_arg.is_copy {
                        ctx.current_ref_params.insert(func_def_arg.name.clone());
                    }
                    if let ValueType::TMulti(elem_type) = &func_def_arg.value_type {
                        // elem_type is the type name string like "Bool"
                        ctx.current_variadic_params.insert(func_def_arg.name.clone(), til_name(elem_type));
                    }
                }

                // Push a new scope frame for this function (like interpreter does)
                let mut function_frame = ScopeFrame {
                    arena_index: HashMap::new(),
                    symbols: HashMap::new(),
                    funcs: HashMap::new(),
                    enums: HashMap::new(),
                    structs: HashMap::new(),
                    scope_type: ScopeType::Function,
                };
                // Register function parameters in the frame
                // For variadic params (TMulti), register as Array type
                for func_def_arg in &func_def.args {
                    let value_type = if let ValueType::TMulti(_) = &func_def_arg.value_type {
                        ValueType::TCustom("Array".to_string())
                    } else {
                        func_def_arg.value_type.clone()
                    };
                    function_frame.symbols.insert(func_def_arg.name.clone(), SymbolInfo {
                        value_type,
                        is_mut: func_def_arg.is_mut,
                        is_copy: func_def_arg.is_copy,
                        is_own: func_def_arg.is_own,
                        is_comptime_const: false,
                    });
                }
                context.scope_stack.frames.push(function_frame);

                // Clear declared_vars for new function scope
                ctx.declared_vars.clear();

                let func_name = til_name(&decl.name);

                // Save and set current function name for nested function mangling
                let prev_function_name = ctx.current_function_name.clone();
                let prev_mangling_counter = ctx.mangling_counter;
                ctx.current_function_name = decl.name.clone();
                ctx.mangling_counter = 0;  // Reset counter per-function for determinism

                emit_func_signature(&func_name, func_def, context, output)?;
                output.push_str(" {\n");

                // Emit function body with catch pattern detection
                emit_stmts(&func_def.body, output, 1, ctx, context)?;

                // Add implicit return at end to silence gcc -Wreturn-type warnings
                if !func_def.throw_types.is_empty() {
                    output.push_str("    return 0;\n");
                } else if !func_def.return_types.is_empty() {
                    let ret_type = til_type_to_c(&func_def.return_types[0])?;
                    output.push_str(&format!("    return ({}){{0}};\n", ret_type));
                }

                output.push_str("}\n\n");

                // Pop the function scope frame
                context.scope_stack.frames.pop();

                // Restore previous function name and counter
                ctx.current_function_name = prev_function_name;
                ctx.mangling_counter = prev_mangling_counter;

                // Clear current function context
                ctx.current_throw_types.clear();
                ctx.current_return_types.clear();

                return Ok(());
            }
        }
    }
    Err("emit_func_declaration: not a function declaration".to_string())
}

fn emit_expr(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    match &expr.node_type {
        NodeType::Body => emit_body(expr, output, indent, ctx, context),
        NodeType::FCall(_) => emit_fcall(expr, output, indent, ctx, context),
        NodeType::LLiteral(lit) => emit_literal(lit, output, context),
        NodeType::Declaration(decl) => emit_declaration(decl, expr, output, indent, ctx, context),
        NodeType::Identifier(name) => {
            // Bug #32 fix: Handle field access on expression results
            // When name is "_", params[0] is an expression to emit first,
            // then params[1..] are the field chain
            if name == "_" && !expr.params.is_empty() {
                // Emit the base expression (params[0])
                emit_expr(&expr.params[0], output, indent, ctx, context)?;
                // Then emit the field chain
                for i in 1..expr.params.len() {
                    if let NodeType::Identifier(field) = &expr.params[i].node_type {
                        output.push_str(".");
                        output.push_str(field);
                    }
                }
                return Ok(());
            }

            // Check for type-qualified access (Type.field or Type.Variant)
            if !expr.params.is_empty() {
                if let NodeType::Identifier(field) = &expr.params[0].node_type {
                    // Check if this is an enum variant by looking up in context
                    if let Some(enum_def) = context.scope_stack.lookup_enum(name) {
                        if enum_def.contains_key(field) {
                            // Enum variant: Type.Variant -> til_Type_make_Variant()
                            output.push_str(TIL_PREFIX);
                            output.push_str(name);
                            output.push_str("_make_");
                            output.push_str(field);
                            output.push_str("()");
                            return Ok(());
                        }
                    }
                    // Check if this is a struct constant access
                    if context.scope_stack.has_struct(name) {
                        // Struct constant: Type.constant -> til_Type_constant
                        output.push_str(&til_name(name));
                        output.push_str("_");
                        output.push_str(field);
                        return Ok(());
                    }
                }
            }
            // Regular identifier or field access (b.val -> til_b.val)
            // For ref params (which are pointers in C), use -> for field access
            let is_ref_param = ctx.current_ref_params.contains(name);
            // Bug #97: Use type-mangled name for variables
            let c_var_name = til_var_name_from_context(name, context);
            if is_ref_param && !expr.params.is_empty() {
                // Ref param with field access: til_self->field1.field2.field3
                // First field uses -> (self is a pointer), rest use . (struct values)
                output.push_str(&c_var_name);
                for (i, param) in expr.params.iter().enumerate() {
                    if let NodeType::Identifier(field) = &param.node_type {
                        if i == 0 {
                            output.push_str("->");
                        } else {
                            output.push_str(".");
                        }
                        output.push_str(field);
                    }
                }
            } else if is_ref_param {
                // Ref param used as value: dereference with *
                output.push_str("(*");
                output.push_str(&c_var_name);
                output.push_str(")");
            } else {
                // Regular identifier or field access
                output.push_str(&c_var_name);
                for param in &expr.params {
                    if let NodeType::Identifier(field) = &param.node_type {
                        output.push_str(".");
                        output.push_str(field);  // Field names stay as-is (C struct fields)
                    }
                }
            }
            Ok(())
        },
        NodeType::FuncDef(func_def) => emit_funcdef(func_def, expr, output, indent, ctx, context),
        NodeType::Assignment(name) => emit_assignment(name, expr, output, indent, ctx, context),
        NodeType::Return => emit_return(expr, output, indent, ctx, context),
        NodeType::If => emit_if(expr, output, indent, ctx, context),
        NodeType::While => emit_while(expr, output, indent, ctx, context),
        NodeType::Break => emit_break(expr, output, indent),
        NodeType::Continue => emit_continue(expr, output, indent),
        NodeType::Catch => Ok(()), // Catch blocks handled at call site
        NodeType::Throw => emit_throw(expr, output, indent, ctx, context),
        NodeType::StructDef(_) => Err("ccodegen: StructDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::EnumDef(_) => Err("ccodegen: EnumDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::Switch => Err(expr.lang_error(&context.path, "ccodegen", "Switch should have been desugared to if/else by desugarer phase")),
        NodeType::DefaultCase => Err(expr.lang_error(&context.path, "ccodegen", "DefaultCase should have been desugared with Switch")),
        NodeType::Range => Err("ccodegen: Range not yet supported".to_string()),
        NodeType::Pattern(_) => Err(expr.lang_error(&context.path, "ccodegen", "Pattern should have been desugared with Switch")),
        NodeType::NamedArg(_) => Err(expr.error(&context.path, "ccodegen", "NamedArg should be reordered before reaching emit_expr")),
        // Issue #108: NamespaceDef already processed by init - members merged into type
        NodeType::NamespaceDef(_ns_def) => Ok(()),
        NodeType::ForIn(_) => Err(expr.lang_error(&context.path, "ccodegen", "ForIn should be desugared in precomp before reaching ccodegen")),
    }
}

fn emit_body(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // Bug #44 fix: Save and restore local_catch_labels around nested blocks
    // Without this, nested blocks clear the outer catches when processing their
    // own throwing calls, causing missing status checks for outer throwing calls.
    let saved_catch_labels = ctx.local_catch_labels.clone();
    let result = emit_stmts(&expr.params, output, indent, ctx, context);
    ctx.local_catch_labels = saved_catch_labels;
    result
}

/// Emit a sequence of statements with catch pattern detection
/// This is the core logic shared between emit_body and emit_func_declaration
fn emit_stmts(stmts: &[Expr], output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    let mut i = 0;
    let indent_str = "    ".repeat(indent);

    // Pre-scan for function-level catches (at the end of the block)
    let func_level_catches = prescan_func_level_catches(stmts);

    // Hoist declarations from catch blocks to function level
    // (TIL has function-level scoping, not block-level scoping)
    for catch_block in &func_level_catches {
        if catch_block.params.len() >= 3 {
            // Temporarily add the catch error variable to scope for type inference
            // catch (err: ErrType) { body } -> err_var=params[0], err_type=params[1], body=params[2]
            if let NodeType::Identifier(err_var_name) = &catch_block.params[0].node_type {
                if let NodeType::Identifier(err_type_name) = &catch_block.params[1].node_type {
                    context.scope_stack.declare_symbol(
                        err_var_name.clone(),
                        SymbolInfo {
                            value_type: crate::rs::parser::ValueType::TCustom(err_type_name.clone()),
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        }
                    );
                }
            }

            // Bug #97: Use type-mangled names for shadowing support
            let catch_body = &catch_block.params[2];
            let decls = collect_declarations_in_body(catch_body, context);
            for decl in decls {
                let type_prefix = value_type_to_c_prefix(&decl.value_type);
                let c_var_name = til_var_name(&decl.name, &type_prefix);
                if !ctx.declared_vars.contains(&c_var_name) {
                    if let Ok(c_type) = til_type_to_c(&decl.value_type) {
                        output.push_str(&indent_str);
                        output.push_str(&c_type);
                        output.push_str(" ");
                        output.push_str(&c_var_name);
                        output.push_str(";\n");
                        ctx.declared_vars.insert(c_var_name);
                        // Also register in scope_stack so get_value_type can find it
                        context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                            value_type: decl.value_type.clone(),
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        });
                    }
                }
            }
        }
    }

    // Bug #39 fix: Give each catch block its own unique label using the global counter
    // Store catch info with statement index so we can match calls to their NEXT catch
    let mut all_catch_info: Vec<CatchLabelInfoEntry> = Vec::new();
    for (scan_idx, scan_stmt) in stmts.iter().enumerate() {
        if let NodeType::Catch = scan_stmt.node_type {
            if scan_stmt.params.len() >= 3 {
                if let NodeType::Identifier(err_type_name) = &scan_stmt.params[1].node_type {
                    let catch_suffix = next_mangled(ctx); // Unique suffix for EACH catch
                    all_catch_info.push(CatchLabelInfoEntry {
                        stmt_index: scan_idx,
                        type_name: err_type_name.clone(),
                        label: format!("_catch_{}_{}", err_type_name, catch_suffix),
                        temp_var: format!("_thrown_{}_{}", err_type_name, catch_suffix),
                    });
                }
            }
        }
    }

    // Declare temp variables for all catches at the start
    for catch_entry in &all_catch_info {
        output.push_str(&indent_str);
        output.push_str(&til_name(&catch_entry.type_name));
        output.push_str(" ");
        output.push_str(&catch_entry.temp_var);
        output.push_str(";\n");
    }

    // For backward compatibility, also populate local_catch_labels with first catch of each type
    // This is used by throw statements and nested blocks
    let mut registered_types: std::collections::HashSet<String> = std::collections::HashSet::new();
    for catch_entry in &all_catch_info {
        if !registered_types.contains(&catch_entry.type_name) {
            registered_types.insert(catch_entry.type_name.clone());
            ctx.local_catch_labels.insert(catch_entry.type_name.clone(), CatchLabelInfo {
                label: catch_entry.label.clone(),
                temp_var: catch_entry.temp_var.clone(),
            });
        }
    }

    // Track which catch labels have been emitted to avoid duplicates
    // (when multiple catches of same type exist, only emit the label once)
    let mut emitted_catch_labels: std::collections::HashSet<String> = std::collections::HashSet::new();

    // Process all statements
    while i < stmts.len() {
        let stmt = &stmts[i];
        let effective_indent = indent; // Use same indent for all statements (no if-block nesting)

        // Bug #39 fix: Handle catch blocks inline with if(0) { label: ... }
        // This keeps catches where they appear in source, and execution falls through after
        if let NodeType::Catch = stmt.node_type {
            // Get the error type this catch handles
            if stmt.params.len() >= 3 {
                if let NodeType::Identifier(err_type_name) = &stmt.params[1].node_type {
                    // Look up this specific catch's label from all_catch_info by statement index
                    let mut catch_entry_opt: Option<&CatchLabelInfoEntry> = None;
                    for e in &all_catch_info {
                        if e.stmt_index == i {
                            catch_entry_opt = Some(e);
                            break;
                        }
                    }
                    if let Some(catch_entry) = catch_entry_opt {
                        // Only emit if we haven't already emitted this label
                        if !emitted_catch_labels.contains(&catch_entry.label) {
                            emitted_catch_labels.insert(catch_entry.label.clone());
                            let label = catch_entry.label.clone();
                            let temp_var = catch_entry.temp_var.clone();

                            output.push_str(&indent_str);
                            output.push_str("if (0) { ");
                            output.push_str(&label);
                            // Add empty statement after label - C11 requires statement after label, not declaration
                            output.push_str(":;\n");

                            // Bind error variable
                            if let NodeType::Identifier(err_var_name) = &stmt.params[0].node_type {
                                let inner_indent = "    ".repeat(indent + 1);
                                output.push_str(&inner_indent);
                                output.push_str(&til_name(err_type_name));
                                output.push_str(" ");
                                // Bug #97: Use type-mangled name for catch variable
                                output.push_str(&til_var_name(err_var_name, err_type_name));
                                output.push_str(" = ");
                                output.push_str(&temp_var);
                                output.push_str(";\n");

                                // Add error variable to scope for type resolution in catch body
                                context.scope_stack.declare_symbol(
                                    err_var_name.clone(),
                                    SymbolInfo {
                                        value_type: crate::rs::parser::ValueType::TCustom(err_type_name.clone()),
                                        is_mut: false,
                                        is_copy: false,
                                        is_own: false,
                                        is_comptime_const: false,
                                    }
                                );
                            }

                            // Emit catch body
                            // IMPORTANT: Temporarily clear local_catch_labels so throwing calls inside
                            // the catch body don't try to jump to catches - catches shouldn't catch
                            // errors from their own body, only from code before them
                            let saved_catch_labels = std::mem::take(&mut ctx.local_catch_labels);
                            emit_expr(&stmt.params[2], output, indent + 1, ctx, context)?;
                            ctx.local_catch_labels = saved_catch_labels;

                            // Close the if(0) block - execution falls through to code after
                            output.push_str(&indent_str);
                            output.push_str("}\n");

                            // Bug #46 fix: Remove this catch from local_catch_labels
                            // Catches should only handle throws from BEFORE them, not after.
                            // This mirrors the interpreter's behavior where pending_throw is
                            // set by statements and only subsequent catches can handle it.
                            ctx.local_catch_labels.remove(err_type_name);
                        }
                    }
                }
            }
            i += 1;
            continue;
        }

        // Check if this statement is followed by catch blocks
        // And if it's a call to a throwing function (FCall, Declaration with FCall, or Assignment with FCall)
        let (maybe_fcall, maybe_decl_name, maybe_assign_name) = match &stmt.node_type {
            NodeType::FCall(_) => (Some(stmt), None, None),
            NodeType::Declaration(decl) => {
                // Check if declaration has an FCall as initializer
                if !stmt.params.is_empty() {
                    if let NodeType::FCall(_) = stmt.params[0].node_type {
                        (Some(&stmt.params[0]), Some(decl.name.clone()), None)
                    } else {
                        (None, None, None)
                    }
                } else {
                    (None, None, None)
                }
            }
            NodeType::Assignment(name) => {
                // Check if assignment has an FCall as RHS
                if !stmt.params.is_empty() {
                    if let NodeType::FCall(_) = stmt.params[0].node_type {
                        (Some(&stmt.params[0]), None, Some(name.clone()))
                    } else {
                        (None, None, None)
                    }
                } else {
                    (None, None, None)
                }
            }
            _ => (None, None, None),
        };

        if let Some(fcall) = maybe_fcall {
            // eval functions from std.meta are only available in interpret mode
            if let Some(func_name) = get_til_func_name_string(&fcall.params[0]) {
                if func_name == "eval_file" || func_name == "eval_to_str" || func_name == "eval_to_ast_str" || func_name == "eval_to_expr" {
                    return Err(fcall.error(&context.path, "ccodegen", &format!("{}() is only available in interpret mode, not in build/run", func_name)));
                }
            }

            // Get function name from the FCall
            // Check if this function is a throwing function
            if let Some(throw_types) = get_fcall_func_def(context, fcall).map(|fd| fd.throw_types).filter(|t| !t.is_empty()) {
                // Collect subsequent catch blocks
                let mut catch_blocks = Vec::new();
                let mut j = i + 1;
                while j < stmts.len() {
                    if let NodeType::Catch = stmts[j].node_type {
                        catch_blocks.push(&stmts[j]);
                        j += 1;
                    } else {
                        break;
                    }
                }

                if !catch_blocks.is_empty() && func_level_catches.is_empty() {
                    // Immediate catches AND no function-level catches - handle inline
                    // Only use this optimization if there are no earlier throwing calls that
                    // need the catch labels (func_level_catches tracks all catches in the block)
                    emit_throwing_call(fcall, &throw_types, &catch_blocks, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, effective_indent, ctx, context)?;
                    i = j; // Skip past catch blocks
                    continue;
                } else if !ctx.current_throw_types.is_empty() && ctx.local_catch_labels.is_empty() && func_level_catches.is_empty() {
                    // Bug #68 fix: Also check func_level_catches.is_empty()
                    // Without this check, we might propagate even when there are catches in the block
                    // just because local_catch_labels was cleared after processing an earlier catch
                    // No catch blocks, we're inside a throwing function, and no catches in this block
                    // Emit error propagation pattern
                    emit_throwing_call_propagate(fcall, &throw_types, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, effective_indent, ctx, context)?;
                    i += 1;
                    continue;
                } else if !func_level_catches.is_empty() || !ctx.local_catch_labels.is_empty() {
                    // Has function-level catches or outer catches registered
                    // Bug #39 fix: Update local_catch_labels to point to NEXT catch for each type
                    // This ensures each call jumps to the correct catch, not always the first one
                    // Build map with only catches AFTER current position
                    let mut next_catches: std::collections::HashMap<String, CatchLabelInfo> = std::collections::HashMap::new();
                    for catch_entry in &all_catch_info {
                        if catch_entry.stmt_index > i && !next_catches.contains_key(&catch_entry.type_name) {
                            // First catch of this type after current position
                            next_catches.insert(catch_entry.type_name.clone(), CatchLabelInfo {
                                label: catch_entry.label.clone(),
                                temp_var: catch_entry.temp_var.clone(),
                            });
                        }
                    }
                    // Replace local_catch_labels with only the next catches
                    // This removes entries for types that have no more catches after this point
                    ctx.local_catch_labels.clear();
                    for (type_name, catch_info) in &next_catches {
                        ctx.local_catch_labels.insert(type_name.clone(), CatchLabelInfo {
                            label: catch_info.label.clone(),
                            temp_var: catch_info.temp_var.clone(),
                        });
                    }
                    emit_throwing_call_with_goto(fcall, &throw_types, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, effective_indent, ctx, context)?;
                    i += 1;
                    continue;
                } else {
                    // No catches - typer should have caught this if we're in non-throwing context
                    // Just use propagate (will silently succeed on error if we're not throwing)
                    emit_throwing_call_propagate(fcall, &throw_types, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, effective_indent, ctx, context)?;
                    i += 1;
                    continue;
                }
            }
        }

        // Check for non-throwing variadic calls in declarations/assignments
        // These need special handling because variadic array must be constructed first
        if let Some(fcall) = maybe_fcall {
            if let Some(variadic_fcall_info) = detect_variadic_fcall(fcall, ctx) {
                // Check that this is NOT a throwing function (those are handled above)
                let is_throwing = get_fcall_func_def(context, fcall)
                    .map(|fd| !fd.throw_types.is_empty())
                    .unwrap_or(false);

                if !is_throwing {
                    emit_variadic_call(fcall, &variadic_fcall_info.elem_type, variadic_fcall_info.regular_count, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, effective_indent, ctx, context)?;
                    i += 1;
                    continue;
                }
            }
        }

        // Regular statement handling
        emit_expr(stmt, output, effective_indent, ctx, context)?;
        i += 1;
    }

    // Clean up local_catch_labels for this block
    for catch_entry in &all_catch_info {
        ctx.local_catch_labels.remove(&catch_entry.type_name);
    }

    Ok(())
}

/// Get the function name from an FCall expression (returns underscore format like Type_method)
/// This returns the name WITHOUT til_ prefix.
/// For C output, use til_name() on the result.
fn get_fcall_func_name(expr: &Expr) -> Option<String> {
    // get_func_name_string already handles both nested identifiers (Type.method)
    // and precomp'd strings ("Type.method"), returning "Type_method" format
    get_func_name_string(expr.params.first()?)
}

/// Pre-scan function body to collect all catch blocks
/// Returns all catch blocks found in the statements
fn prescan_func_level_catches<'a>(stmts: &'a [Expr]) -> Vec<&'a Expr> {
    let mut catches = Vec::new();

    // Collect ALL catch blocks - we'll register them all for local throw handling
    // The emit_throwing_call handles immediate catch chains for function calls,
    // but we need labels for throw statements that jump to these catches
    for stmt in stmts.iter() {
        if let NodeType::Catch = stmt.node_type {
            catches.push(stmt);
        }
    }

    catches
}

/// Emit a non-throwing variadic function call at statement level
/// Handles constructing the variadic array and cleaning it up after the call
fn emit_variadic_call(
    fcall: &Expr,
    elem_type: &str,
    regular_count: usize,
    decl_name: Option<&str>,
    assign_name: Option<&str>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Get function name
    let func_name = get_fcall_func_name(fcall)
        .ok_or_else(|| "emit_variadic_call: could not get function name".to_string())?;

    // Calculate param info for by-ref param handling
    let func_def_opt = get_fcall_func_def(context, fcall);

    // Bug #143: Use emit_arg_string for each arg
    // For variadic args (i >= regular_count), use by_ref=false
    let mut arg_strings = Vec::new();
    if fcall.params.len() > 1 {
        for (i, arg) in fcall.params.iter().skip(1).enumerate() {
            let is_variadic_arg = i >= regular_count;
            let param_type = func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| &a.value_type));
            let by_ref = if is_variadic_arg {
                false
            } else {
                func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| param_needs_by_ref(a))).unwrap_or(false)
            };
            let arg_str = emit_arg_string(arg, param_type, by_ref, output, indent, ctx, context)?;
            arg_strings.push(arg_str);
        }
    }

    // Construct variadic array using pre-computed arg_strings
    let variadic_arg_strings: Vec<String> = arg_strings.iter().skip(regular_count).cloned().collect();
    let variadic_arr_var = emit_variadic_array_with_strings(elem_type, &variadic_arg_strings, output, indent, ctx)?;

    // Determine return type if we need to declare a variable
    let ret_type = if decl_name.is_some() || assign_name.is_some() {
        get_fcall_func_def(context, fcall)
            .and_then(|fd| fd.return_types.first().cloned())
            .map(|t| til_type_to_c(&t).unwrap_or("int".to_string()))
            .unwrap_or("int".to_string())
    } else {
        "int".to_string()
    };

    // Helper to emit the function call with pre-computed arg_strings
    let emit_call = |out: &mut String| {
        out.push_str(TIL_PREFIX);
        out.push_str(&func_name.replace('.', "_"));
        out.push_str("(");
        // Emit regular args using pre-computed arg_strings
        for (vret_arg_i, vret_arg_str) in arg_strings.iter().take(regular_count).enumerate() {
            if vret_arg_i > 0 {
                out.push_str(", ");
            }
            out.push_str(vret_arg_str);
        }
        // Emit variadic array pointer
        if regular_count > 0 {
            out.push_str(", ");
        }
        out.push_str("&");
        out.push_str(&variadic_arr_var);
        out.push_str(")");
    };

    // For declarations: declare the variable (skip for "_" - Bug #35)
    if let Some(var_name) = decl_name {
        if var_name == "_" {
            // Bug #35: For underscore, just call the function (discard result)
            output.push_str(&indent_str);
            emit_call(output);
            output.push_str(";\n");
        } else {
            // Bug #97: Register in scope FIRST so we can get the type-mangled name
            if let Some(fd) = get_fcall_func_def(context, fcall) {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
            let c_var_name = til_var_name_from_context(var_name, context);
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&c_var_name);
            output.push_str(" = ");
            emit_call(output);
            output.push_str(";\n");

            ctx.declared_vars.insert(c_var_name);
        }
    } else if let Some(var_name) = assign_name {
        // Assignment
        output.push_str(&indent_str);
        // Bug #97: Use type-mangled names for variables
        // Check if assignment target is a field access on a mut param (self.field)
        // If so, emit with -> instead of .
        if let Some(dot_pos) = var_name.find('.') {
            let base = &var_name[..dot_pos];
            let rest = &var_name[dot_pos + 1..];
            if ctx.current_ref_params.contains(base) {
                // Mut param field access: til_Type_self->field
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str(".");
                output.push_str(rest);
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_Type_self = value
            output.push_str("*");
            output.push_str(&til_var_name_from_context(var_name, context));
        } else {
            output.push_str(&til_var_name_from_context(var_name, context));
        }
        output.push_str(" = ");
        emit_call(output);
        output.push_str(";\n");
    } else {
        // Standalone variadic call (no return value used)
        output.push_str(&indent_str);
        emit_call(output);
        output.push_str(";\n");
    }

    // Clean up variadic array
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("Array_delete(&");
    output.push_str(&variadic_arr_var);
    output.push_str(");\n");

    Ok(())
}

/// Emit a call to a throwing function with catch handling
fn emit_throwing_call(
    fcall: &Expr,
    throw_types: &[crate::rs::parser::ValueType],
    catch_blocks: &[&Expr],
    decl_name: Option<&str>,
    assign_name: Option<&str>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Get function name
    let mut func_name = get_fcall_func_name(fcall)
        .ok_or_else(|| "emit_throwing_call: could not get function name".to_string())?;

    // Check if this is a call to a nested (hoisted) function - use mangled name
    if let Some(mangled_name) = ctx.nested_func_names.get(&func_name) {
        func_name = mangled_name.clone();
    }

    // Generate unique temp names for this call
    let temp_suffix = next_mangled(ctx);

    // Determine if we need a return value temp variable
    // Only if function actually returns something AND we're capturing it
    let func_def_opt = get_fcall_func_def(context, fcall);
    let func_has_return = func_def_opt.as_ref()
        .map(|fd| !fd.return_types.is_empty())
        .unwrap_or(false);
    let needs_ret = func_has_return && (decl_name.is_some() || assign_name.is_some());

    // Check if this is a variadic function call
    let variadic_info = detect_variadic_fcall(fcall, ctx);
    let variadic_regular_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(usize::MAX);

    // Bug #143: Use emit_arg_string for each arg
    let mut arg_strings = Vec::new();
    if fcall.params.len() > 1 {
        for (i, arg) in fcall.params.iter().skip(1).enumerate() {
            let is_variadic_arg = i >= variadic_regular_count;
            let param_type = func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| &a.value_type));
            let by_ref = if is_variadic_arg {
                false
            } else {
                func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| param_needs_by_ref(a))).unwrap_or(false)
            };
            let arg_str = emit_arg_string(arg, param_type, by_ref, output, indent, ctx, context)?;
            arg_strings.push(arg_str);
        }
    }

    // Declare local variables for return value and errors
    // Look up the actual return type from scope_stack
    let ret_type = if needs_ret {
        func_def_opt.as_ref()
            .and_then(|fd| fd.return_types.first())
            .map(|t| til_type_to_c(t).unwrap_or("int".to_string()))
            .unwrap_or("int".to_string())
    } else {
        "int".to_string()
    };

    if needs_ret {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" _ret_");
        output.push_str(&temp_suffix.to_string());
        output.push_str(";\n");
    }

    // For declarations: declare the variable BEFORE the if block so it's visible after
    // Skip for underscore _ which is just a discard
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            // Bug #97: Add to scope_stack FIRST so we can get the type-mangled name
            if let Some(fd) = func_def_opt.as_ref() {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
            let c_var_name = til_var_name_from_context(var_name, context);
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&c_var_name);
            output.push_str(";\n");
            ctx.declared_vars.insert(c_var_name);
        }
    }

    // Declare error structs for each throw type (Issue #119: skip empty struct errors)
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if let crate::rs::parser::ValueType::TCustom(type_name) = throw_type {
            output.push_str(&indent_str);
            output.push_str(&til_name(type_name));
            output.push_str(" _err");
            output.push_str(&idx.to_string());
            output.push_str("_");
            output.push_str(&temp_suffix.to_string());
            // Use = {} for empty structs to avoid warning
            output.push_str(" = {};\n");
        }
    }

    // Construct variadic array if needed, using pre-computed arg_strings
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        let variadic_arg_strings: Vec<String> = arg_strings.iter().skip(vi.regular_count).cloned().collect();
        Some(emit_variadic_array_with_strings(&vi.elem_type, &variadic_arg_strings, output, indent, ctx)?)
    } else {
        None
    };

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int __attribute__((unused)) _status_");
    output.push_str(&temp_suffix.to_string());
    output.push_str(" = ");
    output.push_str(&til_func_name(&func_name));
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix.to_string());
    }

    // Then: error pointers (Issue #119: skip empty struct errors)
    let mut has_emitted_params = needs_ret;
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if has_emitted_params {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix.to_string());
        has_emitted_params = true;
    }

    // Emit arguments using pre-computed arg_strings
    if let Some(ref vi) = variadic_info {
        // Variadic call: emit regular args first, then variadic array pointer
        for (i, arg_str) in arg_strings.iter().take(vi.regular_count).enumerate() {
            if has_emitted_params || i > 0 {
                output.push_str(", ");
            }
            output.push_str(arg_str);
        }

        // Emit variadic array pointer
        if let Some(ref arr_var) = variadic_arr_var {
            if has_emitted_params || vi.regular_count > 0 {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(arr_var);
        }
    } else {
        // Non-variadic: emit all args directly
        for (i, arg_str) in arg_strings.iter().enumerate() {
            if has_emitted_params || i > 0 {
                output.push_str(", ");
            }
            output.push_str(arg_str);
        }
    }

    output.push_str(");\n");

    // Generate if/else chain for error handling
    output.push_str(&indent_str);
    output.push_str("if (_status_");
    output.push_str(&temp_suffix.to_string());
    output.push_str(" == 0) {\n");

    // Success case: assign return value to target variable
    // Skip for underscore _ which is just a discard
    // Bug #97: Use type-mangled names
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            // Declaration: assign to newly declared variable (declared before if block)
            let inner_indent = "    ".repeat(indent + 1);
            output.push_str(&inner_indent);
            output.push_str(&til_var_name_from_context(var_name, context));
            output.push_str(" = _ret_");
            output.push_str(&temp_suffix.to_string());
            output.push_str(";\n");
        }
    } else if let Some(var_name) = assign_name {
        // Assignment: assign to existing variable
        let inner_indent = "    ".repeat(indent + 1);
        output.push_str(&inner_indent);
        // Check if assignment target is a field access on a mut param (self.field)
        // If so, emit with -> instead of .
        if let Some(dot_pos) = var_name.find('.') {
            let base = &var_name[..dot_pos];
            let rest = &var_name[dot_pos + 1..];
            if ctx.current_ref_params.contains(base) {
                // Mut param field access: til_Type_self->field
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str(".");
                output.push_str(rest);
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_Type_var = value
            output.push_str("*");
            output.push_str(&til_var_name_from_context(var_name, context));
        } else {
            output.push_str(&til_var_name_from_context(var_name, context));
        }
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix.to_string());
        output.push_str(";\n");
    }

    output.push_str(&indent_str);
    output.push_str("}");

    // Generate else-if branches for each catch block
    for catch_block in catch_blocks {
        if catch_block.params.len() >= 3 {
            // Get error type name from catch block
            if let NodeType::Identifier(err_type_name) = &catch_block.params[1].node_type {
                // Find index of this error type
                let mut err_idx: Option<usize> = None;
                for (i, vt) in throw_types.iter().enumerate() {
                    if let crate::rs::parser::ValueType::TCustom(name) = vt {
                        if name == err_type_name {
                            err_idx = Some(i);
                            break;
                        }
                    }
                }

                if let Some(idx) = err_idx {
                    output.push_str(" else if (_status_");
                    output.push_str(&temp_suffix.to_string());
                    output.push_str(" == ");
                    output.push_str(&(idx + 1).to_string());
                    output.push_str(") {\n");

                    // Bind error variable and add to scope for type resolution
                    if let NodeType::Identifier(err_var_name) = &catch_block.params[0].node_type {
                        let inner_indent = "    ".repeat(indent + 1);
                        output.push_str(&inner_indent);
                        output.push_str(&til_name(err_type_name));
                        output.push_str(" ");
                        output.push_str(&til_name(err_var_name));
                        // Issue #119: For empty struct errors, use empty initializer since _err var doesn't exist
                        let throw_type = &throw_types[idx];
                        if is_empty_error_struct(context, throw_type) {
                            output.push_str(" = {};\n");
                        } else {
                            output.push_str(" = _err");
                            output.push_str(&idx.to_string());
                            output.push_str("_");
                            output.push_str(&temp_suffix.to_string());
                            output.push_str(";\n");
                        }

                        // Add error variable to scope for type resolution in catch body
                        context.scope_stack.declare_symbol(
                            err_var_name.clone(),
                            SymbolInfo {
                                value_type: crate::rs::parser::ValueType::TCustom(err_type_name.clone()),
                                is_mut: false,
                                is_copy: false,
                                is_own: false,
                                is_comptime_const: false,
                            }
                        );
                    }

                    // Emit catch body
                    emit_expr(&catch_block.params[2], output, indent + 1, ctx, context)?;

                    output.push_str(&indent_str);
                    output.push_str("}");
                }
            }
        }
    }

    output.push_str("\n");
    Ok(())
}

/// Emit a throwing function call that propagates errors to the caller (no catch blocks)
/// This is used when a throwing function calls another throwing function without catching
fn emit_throwing_call_propagate(
    fcall: &Expr,
    throw_types: &[crate::rs::parser::ValueType],
    decl_name: Option<&str>,
    assign_name: Option<&str>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Get function name
    let mut func_name = get_fcall_func_name(fcall)
        .ok_or_else(|| "emit_throwing_call_propagate: could not get function name".to_string())?;

    // Check if this is a call to a nested (hoisted) function - use mangled name
    if let Some(mangled_name) = ctx.nested_func_names.get(&func_name) {
        func_name = mangled_name.clone();
    }

    // Generate unique temp names for this call
    let temp_suffix = next_mangled(ctx);

    // Determine if we need a return value temp variable
    // Only if function actually returns something AND we're capturing it
    let func_def_opt = get_fcall_func_def(context, fcall);
    let func_has_return = func_def_opt.as_ref()
        .map(|fd| !fd.return_types.is_empty())
        .unwrap_or(false);
    let needs_ret = func_has_return && (decl_name.is_some() || assign_name.is_some());

    // Check if this is a variadic function call
    let variadic_info = detect_variadic_fcall(fcall, ctx);
    let variadic_regular_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(usize::MAX);

    // Bug #143: Use emit_arg_string for each arg
    let mut arg_strings = Vec::new();
    if fcall.params.len() > 1 {
        for (i, arg) in fcall.params.iter().skip(1).enumerate() {
            let is_variadic_arg = i >= variadic_regular_count;
            let param_type = func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| &a.value_type));
            let by_ref = if is_variadic_arg {
                false
            } else {
                func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| param_needs_by_ref(a))).unwrap_or(false)
            };
            let arg_str = emit_arg_string(arg, param_type, by_ref, output, indent, ctx, context)?;
            arg_strings.push(arg_str);
        }
    }

    // Look up the actual return type from scope_stack
    let ret_type = if needs_ret {
        func_def_opt.as_ref()
            .and_then(|fd| fd.return_types.first())
            .map(|t| til_type_to_c(t).unwrap_or("int".to_string()))
            .unwrap_or("int".to_string())
    } else {
        "int".to_string()
    };

    // Declare temp for return value if needed
    if needs_ret {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" _ret_");
        output.push_str(&temp_suffix);
        output.push_str(";\n");
    }

    // For declarations: declare the variable BEFORE the if block so it's visible after
    // Skip for underscore _ which is just a discard
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            // Bug #97: Add to scope_stack FIRST so we can get the type-mangled name
            if let Some(fd) = func_def_opt.as_ref() {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
            let c_var_name = til_var_name_from_context(var_name, context);
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&c_var_name);
            output.push_str(";\n");
            ctx.declared_vars.insert(c_var_name);
        }
    }

    // Declare error structs for each throw type of the called function
    // Issue #119: Skip empty struct errors - only status code matters
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if let crate::rs::parser::ValueType::TCustom(type_name) = throw_type {
            output.push_str(&indent_str);
            output.push_str(&til_name(type_name));
            output.push_str(" _err");
            output.push_str(&idx.to_string());
            output.push_str("_");
            output.push_str(&temp_suffix);
            output.push_str(" = {};\n");
        }
    }

    // Construct variadic array if needed, using pre-computed arg_strings
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        let variadic_arg_strings: Vec<String> = arg_strings.iter().skip(vi.regular_count).cloned().collect();
        Some(emit_variadic_array_with_strings(&vi.elem_type, &variadic_arg_strings, output, indent, ctx)?)
    } else {
        None
    };

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int __attribute__((unused)) _status_");
    output.push_str(&temp_suffix);
    output.push_str(" = ");
    output.push_str(&til_func_name(&func_name));
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix);
    }

    // Then: error pointers (Issue #119: skip empty struct errors)
    let mut has_emitted_params = needs_ret;
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if has_emitted_params {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix);
        has_emitted_params = true;
    }

    // Emit arguments using pre-computed arg_strings
    if let Some(ref vi) = variadic_info {
        // Variadic call: emit regular args first, then variadic array pointer
        for (i, arg_str) in arg_strings.iter().take(vi.regular_count).enumerate() {
            if has_emitted_params || i > 0 {
                output.push_str(", ");
            }
            output.push_str(arg_str);
        }

        // Emit variadic array pointer
        if let Some(ref arr_var) = variadic_arr_var {
            if has_emitted_params || vi.regular_count > 0 {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(arr_var);
        }
    } else {
        // Non-variadic: emit all args directly
        for (i, arg_str) in arg_strings.iter().enumerate() {
            if has_emitted_params || i > 0 {
                output.push_str(", ");
            }
            output.push_str(arg_str);
        }
    }

    output.push_str(");\n");

    // Generate error propagation: if status != 0, copy error to caller's error param and return
    // Map error types from called function to current function's error params
    for (called_idx, called_throw_type) in throw_types.iter().enumerate() {
        if let crate::rs::parser::ValueType::TCustom(called_type_name) = called_throw_type {
            // Find matching error type in current function's throw types
            let mut current_idx: Option<usize> = None;
            for (i, vt) in ctx.current_throw_types.iter().enumerate() {
                if let crate::rs::parser::ValueType::TCustom(name) = vt {
                    if name == called_type_name {
                        current_idx = Some(i);
                        break;
                    }
                }
            }

            if let Some(cur_idx) = current_idx {
                // Issue #119: For empty struct errors, don't copy - just return status
                let is_empty = is_empty_error_struct(context, called_throw_type);
                output.push_str(&indent_str);
                output.push_str("if (_status_");
                output.push_str(&temp_suffix);
                output.push_str(" == ");
                output.push_str(&(called_idx + 1).to_string());
                output.push_str(") { ");
                if !is_empty {
                    output.push_str("*_err");
                    output.push_str(&(cur_idx + 1).to_string());
                    output.push_str(" = _err");
                    output.push_str(&called_idx.to_string());
                    output.push_str("_");
                    output.push_str(&temp_suffix);
                    output.push_str("; ");
                }
                output.push_str("return ");
                output.push_str(&(cur_idx + 1).to_string());
                output.push_str("; }\n");
            }
        }
    }

    // Success case: assign return value to target variable if needed
    // Skip for underscore _ which is just a discard
    // Bug #97: Use type-mangled names
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            output.push_str(&indent_str);
            output.push_str(&til_var_name_from_context(var_name, context));
            output.push_str(" = _ret_");
            output.push_str(&temp_suffix);
            output.push_str(";\n");
        }
    } else if let Some(var_name) = assign_name {
        output.push_str(&indent_str);
        // Check if assignment target is a field access on a mut param (self.field)
        // If so, emit with -> instead of .
        if let Some(dot_pos) = var_name.find('.') {
            let base = &var_name[..dot_pos];
            let rest = &var_name[dot_pos + 1..];
            if ctx.current_ref_params.contains(base) {
                // Mut param field access: til_Type_self->field
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str(".");
                output.push_str(rest);
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_Type_var = value
            output.push_str("*");
            output.push_str(&til_var_name_from_context(var_name, context));
        } else {
            output.push_str(&til_var_name_from_context(var_name, context));
        }
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix);
        output.push_str(";\n");
    }

    Ok(())
}

/// Emit a throwing function call that uses goto for error handling
/// Used when there are outer catch blocks registered in ctx.local_catch_labels
fn emit_throwing_call_with_goto(
    fcall: &Expr,
    throw_types: &[crate::rs::parser::ValueType],
    decl_name: Option<&str>,
    assign_name: Option<&str>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Get function name
    let mut func_name = get_fcall_func_name(fcall)
        .ok_or_else(|| "emit_throwing_call_with_goto: could not get function name".to_string())?;

    // Check if this is a call to a nested (hoisted) function - use mangled name
    if let Some(mangled_name) = ctx.nested_func_names.get(&func_name) {
        func_name = mangled_name.clone();
    }

    // Generate unique temp names for this call
    let temp_suffix = next_mangled(ctx);

    // Determine if we need a return value temp variable
    // Only if function actually returns something AND we're capturing it
    let func_def_opt = get_fcall_func_def(context, fcall);
    let func_has_return = func_def_opt.as_ref()
        .map(|fd| !fd.return_types.is_empty())
        .unwrap_or(false);
    let needs_ret = func_has_return && (decl_name.is_some() || assign_name.is_some());

    // Check if this is a variadic function call
    let variadic_info = detect_variadic_fcall(fcall, ctx);
    let variadic_regular_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(usize::MAX);

    // Bug #143: Use emit_arg_string for each arg
    let mut arg_strings = Vec::new();
    if fcall.params.len() > 1 {
        for (i, arg) in fcall.params.iter().skip(1).enumerate() {
            let is_variadic_arg = i >= variadic_regular_count;
            let param_type = func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| &a.value_type));
            let by_ref = if is_variadic_arg {
                false
            } else {
                func_def_opt.as_ref().and_then(|fd| fd.args.get(i).map(|a| param_needs_by_ref(a))).unwrap_or(false)
            };
            let arg_str = emit_arg_string(arg, param_type, by_ref, output, indent, ctx, context)?;
            arg_strings.push(arg_str);
        }
    }

    // Look up the actual return type
    let ret_type = if needs_ret {
        func_def_opt.as_ref()
            .and_then(|fd| fd.return_types.first())
            .map(|t| til_type_to_c(t).unwrap_or("int".to_string()))
            .unwrap_or("int".to_string())
    } else {
        "int".to_string()
    };

    // Declare temp for return value if needed
    if needs_ret {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" _ret_");
        output.push_str(&temp_suffix);
        output.push_str(";\n");
    }

    // For declarations: declare the variable BEFORE the if block so it's visible after
    // Skip for underscore _ which is just a discard
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            // Bug #97: Add to scope_stack FIRST so we can get the type-mangled name
            if let Some(fd) = func_def_opt.as_ref() {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
            let c_var_name = til_var_name_from_context(var_name, context);
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&c_var_name);
            output.push_str(";\n");
            ctx.declared_vars.insert(c_var_name);
        }
    }

    // Declare error structs for each throw type of the called function
    // Issue #119: Skip empty struct errors - only status code matters
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if let crate::rs::parser::ValueType::TCustom(type_name) = throw_type {
            output.push_str(&indent_str);
            output.push_str(&til_name(type_name));
            output.push_str(" _err");
            output.push_str(&idx.to_string());
            output.push_str("_");
            output.push_str(&temp_suffix);
            output.push_str(" = {};\n");
        }
    }

    // Construct variadic array if needed, using pre-computed arg_strings
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        let variadic_arg_strings: Vec<String> = arg_strings.iter().skip(vi.regular_count).cloned().collect();
        Some(emit_variadic_array_with_strings(&vi.elem_type, &variadic_arg_strings, output, indent, ctx)?)
    } else {
        None
    };

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int __attribute__((unused)) _status_");
    output.push_str(&temp_suffix);
    output.push_str(" = ");
    output.push_str(&til_func_name(&func_name));
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix);
    }

    // Then: error pointers (Issue #119: skip empty struct errors)
    let mut has_emitted_params = needs_ret;
    for (idx, throw_type) in throw_types.iter().enumerate() {
        if is_empty_error_struct(context, throw_type) {
            continue;
        }
        if has_emitted_params {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix);
        has_emitted_params = true;
    }

    // Emit arguments using pre-computed arg_strings
    let regular_arg_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(usize::MAX);
    for (i, arg_str) in arg_strings.iter().take(regular_arg_count).enumerate() {
        if has_emitted_params || i > 0 {
            output.push_str(", ");
        }
        output.push_str(arg_str);
    }

    // Add variadic array if present
    if let Some(arr_var) = &variadic_arr_var {
        if has_emitted_params || !arg_strings.is_empty() {
            output.push_str(", ");
        }
        output.push_str("&");
        output.push_str(arr_var);
    }

    output.push_str(");\n");

    // Bug #39 fix: Use simple status checks with goto, not if-block nesting
    // For each error type, emit a check that either jumps to local catch or propagates
    for (err_idx, throw_type) in throw_types.iter().enumerate() {
        if let crate::rs::parser::ValueType::TCustom(type_name) = throw_type {
            let is_empty = is_empty_error_struct(context, throw_type);
            // Check if there's a local catch for this error type
            if let Some(catch_info) = ctx.local_catch_labels.get(type_name) {
                // Jump to local catch: copy error to temp var (if not empty), then goto label
                output.push_str(&indent_str);
                output.push_str("if (_status_");
                output.push_str(&temp_suffix);
                output.push_str(" == ");
                output.push_str(&(err_idx + 1).to_string());
                output.push_str(") { ");
                // Issue #119: Skip copy for empty struct errors
                if !is_empty {
                    output.push_str(&catch_info.temp_var);
                    output.push_str(" = _err");
                    output.push_str(&err_idx.to_string());
                    output.push_str("_");
                    output.push_str(&temp_suffix);
                    output.push_str("; ");
                }
                output.push_str("goto ");
                output.push_str(&catch_info.label);
                output.push_str("; }\n");
            } else {
                // Check if this error type is in current_throw_types (propagate to caller)
                let mut prop_idx: Option<usize> = None;
                for (i, t) in ctx.current_throw_types.iter().enumerate() {
                    if let crate::rs::parser::ValueType::TCustom(n) = t {
                        if n == type_name {
                            prop_idx = Some(i);
                            break;
                        }
                    }
                }
                if let Some(prop_idx) = prop_idx {
                    // Propagate to caller: copy error to output param (if not empty) and return
                    output.push_str(&indent_str);
                    output.push_str("if (_status_");
                    output.push_str(&temp_suffix);
                    output.push_str(" == ");
                    output.push_str(&(err_idx + 1).to_string());
                    output.push_str(") { ");
                    // Issue #119: Skip copy for empty struct errors
                    if !is_empty {
                        output.push_str("*_err");
                        output.push_str(&(prop_idx + 1).to_string());
                        output.push_str(" = _err");
                        output.push_str(&err_idx.to_string());
                        output.push_str("_");
                        output.push_str(&temp_suffix);
                        output.push_str("; ");
                    }
                    output.push_str("return ");
                    output.push_str(&(prop_idx + 1).to_string());
                    output.push_str("; }\n");
                }
            }
        }
    }

    // Success case: assign return value to target variable if needed
    // This runs unconditionally after error checks - if we get here, status was 0
    // Skip for underscore _ which is just a discard
    // Bug #97: Use type-mangled names
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            output.push_str(&indent_str);
            output.push_str(&til_var_name_from_context(var_name, context));
            output.push_str(" = _ret_");
            output.push_str(&temp_suffix);
            output.push_str(";\n");
        }
    } else if let Some(var_name) = assign_name {
        output.push_str(&indent_str);
        // Check if assignment target is a field access on a mut param (self.field)
        // If so, emit with -> instead of .
        if let Some(dot_pos) = var_name.find('.') {
            let base = &var_name[..dot_pos];
            let rest = &var_name[dot_pos + 1..];
            if ctx.current_ref_params.contains(base) {
                // Mut param field access: til_Type_self->field
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_var_name_from_context(base, context));
                output.push_str(".");
                output.push_str(rest);
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_Type_var = value
            output.push_str("*");
            output.push_str(&til_var_name_from_context(var_name, context));
        } else {
            output.push_str(&til_var_name_from_context(var_name, context));
        }
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix);
        output.push_str(";\n");
    }

    Ok(())
}

fn emit_declaration(decl: &crate::rs::parser::Declaration, expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // Skip inline ext_func/ext_proc declarations - they're just declaring external functions exist
    if !expr.params.is_empty() {
        if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
            if func_def.is_ext() {
                return Ok(());
            }

            // Handle nested function declarations - hoist to top level with mangled name
            if !ctx.current_function_name.is_empty() {
                let parent_name = &ctx.current_function_name;
                let mangled_name = format!("{}_{}", parent_name, decl.name);

                // Register the name mapping so function calls can find it
                ctx.nested_func_names.insert(decl.name.clone(), mangled_name.clone());

                // Register function definition so get_value_type can resolve return types
                context.scope_stack.declare_func(decl.name.clone(), func_def.clone());

                // Generate the hoisted function prototype
                let mut proto_output = String::new();
                emit_func_signature(&til_name(&mangled_name), func_def, context, &mut proto_output)?;
                proto_output.push_str(";\n");
                ctx.hoisted_prototypes.push(proto_output);

                // Generate the hoisted function definition
                let mut func_output = String::new();

                // Save and set context for nested function
                let prev_throw_types = std::mem::take(&mut ctx.current_throw_types);
                let prev_return_types = std::mem::take(&mut ctx.current_return_types);
                let prev_declared_vars = std::mem::take(&mut ctx.declared_vars);
                let prev_mut_params = std::mem::take(&mut ctx.current_ref_params);
                let prev_variadic_params = std::mem::take(&mut ctx.current_variadic_params);
                let prev_function_name = ctx.current_function_name.clone();
                let prev_mangling_counter = ctx.mangling_counter;

                ctx.current_throw_types = func_def.throw_types.clone();
                ctx.current_return_types = func_def.return_types.clone();
                ctx.current_function_name = mangled_name.clone();
                ctx.mangling_counter = 0;  // Reset counter per-function for determinism

                // Bug #60: Track ref and variadic params - all non-copy args are by pointer
                for func_def_arg in &func_def.args {
                    if !func_def_arg.is_copy {
                        ctx.current_ref_params.insert(func_def_arg.name.clone());
                    }
                    if let ValueType::TMulti(elem_type) = &func_def_arg.value_type {
                        ctx.current_variadic_params.insert(func_def_arg.name.clone(), til_name(elem_type));
                    }
                }

                // Push scope frame for function
                let mut function_frame = ScopeFrame {
                    arena_index: HashMap::new(),
                    symbols: HashMap::new(),
                    funcs: HashMap::new(),
                    enums: HashMap::new(),
                    structs: HashMap::new(),
                    scope_type: ScopeType::Function,
                };
                for func_def_arg in &func_def.args {
                    let value_type = if let ValueType::TMulti(_) = &func_def_arg.value_type {
                        ValueType::TCustom("Array".to_string())
                    } else {
                        func_def_arg.value_type.clone()
                    };
                    function_frame.symbols.insert(func_def_arg.name.clone(), SymbolInfo {
                        value_type,
                        is_mut: func_def_arg.is_mut,
                        is_copy: func_def_arg.is_copy,
                        is_own: func_def_arg.is_own,
                        is_comptime_const: false,
                    });
                }
                context.scope_stack.frames.push(function_frame);

                // Emit the function
                emit_func_signature(&til_name(&mangled_name), func_def, context, &mut func_output)?;
                func_output.push_str(" {\n");
                emit_stmts(&func_def.body, &mut func_output, 1, ctx, context)?;
                // Add implicit return at end to silence gcc -Wreturn-type warnings
                if !func_def.throw_types.is_empty() {
                    func_output.push_str("    return 0;\n");
                } else if !func_def.return_types.is_empty() {
                    let ret_type = til_type_to_c(&func_def.return_types[0])?;
                    func_output.push_str(&format!("    return ({}){{0}};\n", ret_type));
                }
                func_output.push_str("}\n\n");

                // Pop scope frame
                context.scope_stack.frames.pop();

                // Restore context
                ctx.current_throw_types = prev_throw_types;
                ctx.current_return_types = prev_return_types;
                ctx.declared_vars = prev_declared_vars;
                ctx.current_ref_params = prev_mut_params;
                ctx.current_variadic_params = prev_variadic_params;
                ctx.current_function_name = prev_function_name;
                ctx.mangling_counter = prev_mangling_counter;

                ctx.hoisted_functions.push(func_output);

                // Don't emit anything at the declaration site - the function is hoisted
                return Ok(());
            }
        }
    }

    // Bug #133 fix: Check if this is a precomputed heap value that needs patching
    if let Some(static_info) = ctx.precomputed_static_arrays.get(&decl.name).cloned() {
        return emit_precomputed_vec_assignment(&decl.name, decl.is_mut, &static_info, output, indent, ctx, context);
    }

    let indent_str = "    ".repeat(indent);

    // Bug #143: Process RHS FCall with emit_arg_string
    // This handles builtins (to_ptr, size_of, etc.), throwing calls, by-ref params, and Dynamic params properly
    // Bug #157: Also handle field access on throwing calls (e.g., get_wrapper()?.value)
    let rhs_string: Option<String> = if !expr.params.is_empty() {
        let rhs = &expr.params[0];
        if let NodeType::FCall(_) = &rhs.node_type {
            Some(emit_arg_string(rhs, None, false, output, indent, ctx, context)?)
        } else if let NodeType::Identifier(name) = &rhs.node_type {
            // Bug #157: Check for UFCS field access on throwing call
            // Pattern: Identifier("_") with params[0] = throwing FCall, params[1..] = field chain
            if name == "_" && !rhs.params.is_empty() {
                if let NodeType::FCall(_) = &rhs.params[0].node_type {
                    if let Some(fd) = get_fcall_func_def(context, &rhs.params[0]) {
                        if !fd.throw_types.is_empty() {
                            // Hoist the throwing call
                            let base_temp = emit_arg_string(&rhs.params[0], None, false, output, indent, ctx, context)?;
                            // Append field chain: temp.field1.field2...
                            let mut result = base_temp;
                            for field_expr in &rhs.params[1..] {
                                if let NodeType::Identifier(field) = &field_expr.node_type {
                                    result.push('.');
                                    result.push_str(field);
                                }
                            }
                            Some(result)
                        } else {
                            None
                        }
                    } else {
                        None
                    }
                } else {
                    None
                }
            } else {
                None
            }
        } else {
            None
        }
    } else {
        None
    };

    // Bug #35: For underscore declarations, just emit the expression (discard result)
    // This avoids C redeclaration errors and matches the semantics of discarding
    if decl.name == "_" {
        if !expr.params.is_empty() {
            output.push_str(&indent_str);
            // FCall at statement level (indent > 0) adds ";\n" itself
            // Other expressions need semicolon added explicitly
            let is_fcall = matches!(&expr.params[0].node_type, NodeType::FCall(_));
            if is_fcall {
                emit_expr(&expr.params[0], output, indent, ctx, context)?;
            } else {
                emit_expr(&expr.params[0], output, 0, ctx, context)?;
                output.push_str(";\n");
            }
        }
        return Ok(());
    }

    let name = &decl.name;
    let is_mut = decl.is_mut;

    // Check if this is a struct construction (TypeName())
    let struct_type = if !expr.params.is_empty() {
        get_struct_construction_type(&expr.params[0], context)
    } else {
        None
    };

    // Check if this is an enum construction (Type.Variant or Type.Variant(value))
    let enum_type = if !expr.params.is_empty() {
        get_enum_construction_type(&expr.params[0], context)
    } else {
        None
    };

    // Track variable type for method mangling
    // Bug #97: Use declared type for the variable name to match C type declaration
    // Only fall back to RHS type inference when declared type is INFER_TYPE
    let var_type = if let Some(ref type_name) = struct_type {
        ValueType::TCustom(type_name.clone())
    } else if let Some(ref type_name) = enum_type {
        ValueType::TCustom(type_name.clone())
    } else if matches!(&decl.value_type, ValueType::TCustom(s) if s == INFER_TYPE) {
        // INFER_TYPE: need to infer from RHS
        if !expr.params.is_empty() {
            get_value_type(context, &expr.params[0]).ok()
                .unwrap_or_else(|| decl.value_type.clone())
        } else {
            decl.value_type.clone()
        }
    } else {
        // Declared type is explicit - use it for consistency with C type declaration
        decl.value_type.clone()
    };
    // Add to scope_stack so get_value_type can find it
    context.scope_stack.declare_symbol(
        name.clone(),
        SymbolInfo { value_type: var_type.clone(), is_mut: decl.is_mut, is_copy: false, is_own: false, is_comptime_const: false }
    );

    // Bug #97: Compute type-mangled C variable name
    let type_prefix = value_type_to_c_prefix(&var_type);
    let c_var_name = til_var_name(name, &type_prefix);

    // Check if variable already declared in this function (avoid C redefinition errors)
    // Bug #97: Use type-mangled name so same name with different types are different variables
    let already_declared = ctx.declared_vars.contains(&c_var_name);

    if let Some(type_name) = struct_type {
        // Struct variable declaration with values (defaults or named args)

        // Build map of named arg values from struct literal
        let mut named_values: std::collections::HashMap<String, &Expr> = std::collections::HashMap::new();
        if !expr.params.is_empty() {
            for arg in expr.params[0].params.iter().skip(1) {
                if let NodeType::NamedArg(field_name) = &arg.node_type {
                    if let Some(value_expr) = arg.params.first() {
                        named_values.insert(field_name.clone(), value_expr);
                    }
                }
            }
        }

        // Look up struct definition to get default values
        // Clone to avoid borrow issues with emit_expr
        let struct_def_opt = context.scope_stack.lookup_struct(&type_name).cloned();
        if let Some(struct_def) = struct_def_opt {
            if struct_def.members.is_empty() {
                // Empty struct - use empty initializer
                output.push_str(&indent_str);
                if !already_declared {
                    if !is_mut {
                        output.push_str("const ");
                    }
                    output.push_str(&til_name(&type_name));
                    output.push_str(" ");
                    ctx.declared_vars.insert(c_var_name.clone());
                }
                output.push_str(&c_var_name);
                emit_struct_literal_assign(output, &type_name, already_declared, "{}");
            } else if struct_def.default_values.is_empty() && named_values.is_empty() {
                // No defaults and no named args - zero initialize
                output.push_str(&indent_str);
                if !already_declared {
                    if !is_mut {
                        output.push_str("const ");
                    }
                    output.push_str(&til_name(&type_name));
                    output.push_str(" ");
                    ctx.declared_vars.insert(c_var_name.clone());
                }
                output.push_str(&c_var_name);
                emit_struct_literal_assign(output, &type_name, already_declared, "{0}");
            } else {
                // Has default values or named args - emit designated initializer
                output.push_str(&indent_str);
                if !already_declared {
                    if !is_mut {
                        output.push_str("const ");
                    }
                    output.push_str(&til_name(&type_name));
                    output.push_str(" ");
                    ctx.declared_vars.insert(c_var_name.clone());
                }
                output.push_str(&c_var_name);
                emit_struct_literal_start(output, &type_name, already_declared);
                output.push_str("{");
                let mut first = true;
                for member in &struct_def.members {
                    // Only include mut fields (actual struct data members)
                    // Skip functions, constants, and non-mut fields
                    if !member.is_mut {
                        continue;
                    }
                    if !first {
                        output.push_str(", ");
                    }
                    first = false;
                    output.push_str(".");
                    output.push_str(&member.name);
                    output.push_str(" = ");
                    // Use named arg value if provided, otherwise use default
                    if let Some(value_expr) = named_values.get(&member.name) {
                        emit_expr(value_expr, output, 0, ctx, context)?;
                    } else if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                        emit_expr(default_expr, output, 0, ctx, context)?;
                    } else {
                        // No default - use zero
                        output.push_str("0");
                    }
                }
                output.push_str("};\n");
            }
        } else {
            // Struct not found - fall back to zero init
            output.push_str(&indent_str);
            if !already_declared {
                if !is_mut {
                    output.push_str("const ");
                }
                output.push_str(&til_name(&type_name));
                output.push_str(" ");
                ctx.declared_vars.insert(c_var_name.clone());
            }
            output.push_str(&c_var_name);
            emit_struct_literal_assign(output, &type_name, already_declared, "{0}");
        }
    } else if let Some(type_name) = enum_type {
        // Enum variable declaration - Bug #143: Use rhs_string if available
        output.push_str(&indent_str);
        if !already_declared {
            if !is_mut {
                output.push_str("const ");
            }
            output.push_str(&til_name(&type_name));
            output.push_str(" ");
            ctx.declared_vars.insert(c_var_name.clone());
        }
        output.push_str(&c_var_name);
        output.push_str(" = ");
        if let Some(ref call_str) = rhs_string {
            output.push_str(call_str);
        } else {
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
        }
        output.push_str(";\n");
    } else if is_mut {
        // Bug #143: Use rhs_string if available (already hoisted args)
        output.push_str(&indent_str);
        if !already_declared {
            // INFER_TYPE should have been resolved by typer
            if matches!(&decl.value_type, ValueType::TCustom(s) if s == INFER_TYPE) {
                return Err(expr.lang_error(&context.path, "ccodegen", &format!("Declaration '{}' has INFER_TYPE - should have been resolved by typer", decl.name)));
            }
            let c_type = til_type_to_c(&decl.value_type).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?;
            output.push_str(&c_type);
            output.push_str(" ");
            ctx.declared_vars.insert(c_var_name.clone());
        }
        output.push_str(&c_var_name);
        if !expr.params.is_empty() {
            output.push_str(" = ");
            if let Some(ref call_str) = rhs_string {
                output.push_str(call_str);
            } else {
                emit_expr(&expr.params[0], output, 0, ctx, context)?;
            }
        }
        output.push_str(";\n");
    } else {
        // const declaration - Bug #143: Use rhs_string if available (already hoisted args)
        output.push_str(&indent_str);
        if !already_declared {
            // INFER_TYPE should have been resolved by typer
            if matches!(&decl.value_type, ValueType::TCustom(s) if s == INFER_TYPE) {
                return Err(expr.lang_error(&context.path, "ccodegen", &format!("Declaration '{}' has INFER_TYPE - should have been resolved by typer", decl.name)));
            }
            let c_type = til_type_to_c(&decl.value_type).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?;
            output.push_str("const ");
            output.push_str(&c_type);
            output.push_str(" ");
            ctx.declared_vars.insert(c_var_name.clone());
        }
        output.push_str(&c_var_name);
        if !expr.params.is_empty() {
            output.push_str(" = ");
            if let Some(ref call_str) = rhs_string {
                output.push_str(call_str);
            } else {
                emit_expr(&expr.params[0], output, 0, ctx, context)?;
            }
        }
        output.push_str(";\n");
    }
    Ok(())
}

// Check if an expression is a struct construction call (TypeName() or TypeName(x=1, y=2))
// Returns the type name if it is, None otherwise
fn get_struct_construction_type(expr: &Expr, context: &Context) -> Option<String> {
    if let NodeType::FCall(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(name) = &expr.params[0].node_type {
                // Use lookup_struct to check if this is a known struct type
                if expr.params[0].params.is_empty()
                    && context.scope_stack.has_struct(name) {
                    let only_named_args = expr.params.len() == 1 ||
                        expr.params.iter().skip(1).all(|arg| matches!(&arg.node_type, NodeType::NamedArg(_)));
                    if only_named_args {
                        return Some(name.clone());
                    }
                }
            }
        }
    }
    None
}

// Check if an expression is an enum construction (Type.Variant or Type.Variant(value))
// Returns the type name if it is, None otherwise
// AST structure for Color.Red(42): FCall -> [Identifier("Color") -> [Identifier("Red")], Literal(42)]
// AST structure for Color.Unknown: Identifier("Color") -> [Identifier("Unknown")]
fn get_enum_construction_type(expr: &Expr, context: &Context) -> Option<String> {
    // Check FCall case: Type.Variant(value) or Type.Variant()
    if let NodeType::FCall(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(type_name) = &expr.params[0].node_type {
                // Use lookup_enum to check if this is a known enum type
                if let Some(enum_def) = context.scope_stack.lookup_enum(type_name) {
                    // Check if there's a nested identifier (the variant)
                    if !expr.params[0].params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &expr.params[0].params[0].node_type {
                            // Verify the variant exists in the enum
                            if enum_def.contains_key(variant_name) {
                                return Some(type_name.clone());
                            }
                        }
                    }
                }
            }
        }
    }

    // Check Identifier case: Type.Variant (no parentheses, no payload)
    if let NodeType::Identifier(type_name) = &expr.node_type {
        // Use lookup_enum to check if this is a known enum type
        if let Some(enum_def) = context.scope_stack.lookup_enum(type_name) {
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.params[0].node_type {
                    // Verify the variant exists in the enum
                    if enum_def.contains_key(variant_name) {
                        return Some(type_name.clone());
                    }
                }
            }
        }
    }

    None
}

fn emit_funcdef(_func_def: &SFuncDef, expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // For now, just inline the function body (we're inside main anyway)
    // TODO: proper function generation with prototypes
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("{\n");
    for stmt in &expr.params {
        emit_expr(stmt, output, indent + 1, ctx, context)?;
    }
    output.push_str(&indent_str);
    output.push_str("}\n");
    Ok(())
}

fn emit_assignment(name: &str, expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);

    // Bug #143: Use emit_arg_string to handle RHS hoisting
    let rhs_str: Option<String> = if !expr.params.is_empty() {
        let rhs_expr = &expr.params[0];

        // Check if RHS is a call to a throwing function
        if let NodeType::FCall(_) = rhs_expr.node_type {
            if let Some(throw_types) = get_fcall_func_def(context, rhs_expr).map(|fd| fd.throw_types).filter(|t| !t.is_empty()) {
                // RHS is a throwing function call - emit with error propagation
                // (typer should ensure non-throwing context doesn't call throwing functions without catch)
                // Pass raw name so function can properly handle field access on mut params
                emit_throwing_call_propagate(rhs_expr, &throw_types, None, Some(name), output, indent, ctx, context)?;
                return Ok(());
            }
        }

        // Process RHS with emit_arg_string (handles hoisting)
        Some(emit_arg_string(rhs_expr, None, false, output, indent, ctx, context)?)
    } else {
        None
    };

    // Regular assignment
    output.push_str(&indent_str);
    // Check if assignment target is a field access on a mut param (self.field)
    // If so, emit with -> instead of .
    // Bug #97: Use type-mangled variable names
    if let Some(dot_pos) = name.find('.') {
        let base = &name[..dot_pos];
        let rest = &name[dot_pos + 1..];
        if ctx.current_ref_params.contains(base) {
            // Mut param field access: til_Type_self->field
            output.push_str(&til_var_name_from_context(base, context));
            output.push_str("->");
            output.push_str(rest);
        } else {
            // Regular field access: til_Type_var.field
            output.push_str(&til_var_name_from_context(base, context));
            output.push_str(".");
            output.push_str(rest);
        }
    } else if ctx.current_ref_params.contains(name) {
        // Direct assignment to mut param: *til_Type_self = value
        output.push_str("*");
        output.push_str(&til_var_name_from_context(name, context));
    } else {
        output.push_str(&til_var_name_from_context(name, context));
    }
    output.push_str(" = ");

    // Check if LHS is Dynamic type - need to cast RHS to avoid int-to-pointer warning
    let is_dynamic_target = context.scope_stack.lookup_symbol(name)
        .map(|sym| matches!(&sym.value_type, ValueType::TCustom(t) if t == "Dynamic"))
        .unwrap_or(false);

    if let Some(ref rhs) = rhs_str {
        if is_dynamic_target {
            output.push_str("(");
            output.push_str(TIL_PREFIX);
            output.push_str("Dynamic)");
        }
        output.push_str(rhs);
    }
    output.push_str(";\n");
    Ok(())
}

fn emit_return(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    let is_throwing = !ctx.current_throw_types.is_empty();

    if is_throwing {
        // Throwing function: store value through _ret pointer and return 0 (success)
        if !expr.params.is_empty() {
            let return_expr = &expr.params[0];

            // Check if return expression is a call to a throwing function
            if let NodeType::FCall(_) = return_expr.node_type {
                if let Some(throw_types) = get_fcall_func_def(context, return_expr).map(|fd| fd.throw_types).filter(|t| !t.is_empty()) {
                    // Return expression is a throwing function call - emit with error propagation
                    // The result will be stored via the assign_name "*_ret"
                    emit_throwing_call_propagate(return_expr, &throw_types, None, Some("*_ret"), output, indent, ctx, context)?;
                    output.push_str(&indent_str);
                    output.push_str("return 0;\n");
                    return Ok(());
                }
            }

            // Bug #143: Use emit_arg_string to handle hoisting
            let return_str = emit_arg_string(return_expr, None, false, output, indent, ctx, context)?;

            // Regular return value - just emit it
            output.push_str(&indent_str);
            output.push_str("*_ret = ");
            output.push_str(&return_str);
            output.push_str(";\n");
        }
        output.push_str(&indent_str);
        output.push_str("return 0;\n");
    } else {
        // Non-throwing function: normal return
        // Check if return expression is a variadic function call
        if !expr.params.is_empty() {
            let return_expr = &expr.params[0];
            if let NodeType::FCall(_) = return_expr.node_type {
                if let Some(variadic_fcall_info) = detect_variadic_fcall(return_expr, ctx) {
                    // Variadic call in return - need to hoist it
                    // Bug #143: Use emit_arg_string for regular args, pass empty map to hoist_variadic_args
                    // (hoist_variadic_args already uses emit_arg_string internally)
                    let variadic_args: Vec<_> = return_expr.params.iter().skip(1 + variadic_fcall_info.regular_count).collect();
                    let empty_hoisted: std::collections::HashMap<usize, String> = std::collections::HashMap::new();
                    let arr_var = hoist_variadic_args(&variadic_fcall_info.elem_type, &variadic_args, &empty_hoisted, variadic_fcall_info.regular_count, output, indent, ctx, context)?;

                    // Bug #143: Get regular arg strings using emit_arg_string
                    let regular_args: Vec<_> = return_expr.params.iter().skip(1).take(variadic_fcall_info.regular_count).collect();
                    let param_info: Vec<ParamTypeInfo> = if let Some(fd) = get_fcall_func_def(context, return_expr) {
                        fd.args.iter().map(|fd_arg| ParamTypeInfo { value_type: Some(fd_arg.value_type.clone()), by_ref: param_needs_by_ref(fd_arg) }).collect()
                    } else {
                        Vec::new()
                    };
                    let mut regular_arg_strings: Vec<String> = Vec::new();
                    for (i, arg) in regular_args.iter().enumerate() {
                        let (param_type, by_ref) = param_info.get(i)
                            .map(|info| (info.value_type.as_ref(), info.by_ref))
                            .unwrap_or((None, true));
                        regular_arg_strings.push(emit_arg_string(arg, param_type, by_ref, output, indent, ctx, context)?);
                    }

                    // Emit the function call storing result
                    let temp_var = next_mangled(ctx);
                    let ret_type = match get_value_type(context, return_expr) {
                        Ok(t) => til_type_to_c(&t).map_err(|e| return_expr.lang_error(&context.path, "ccodegen", &e))?,
                        Err(e) => return Err(return_expr.lang_error(&context.path, "ccodegen", &e)),
                    };
                    output.push_str(&indent_str);
                    output.push_str(&ret_type);
                    output.push_str(" ");
                    output.push_str(&temp_var);
                    output.push_str(" = ");
                    // Emit the function call
                    if let NodeType::Identifier(func_name) = &return_expr.params[0].node_type {
                        output.push_str(&til_func_name(func_name));
                    }
                    output.push_str("(");
                    // Emit regular args
                    for (i, arg_str) in regular_arg_strings.iter().enumerate() {
                        if i > 0 {
                            output.push_str(", ");
                        }
                        output.push_str(arg_str);
                    }
                    // Emit variadic array pointer
                    if variadic_fcall_info.regular_count > 0 {
                        output.push_str(", ");
                    }
                    output.push_str("&");
                    output.push_str(&arr_var);
                    output.push_str(");\n");

                    // Delete array
                    output.push_str(&indent_str);
                    output.push_str(TIL_PREFIX);
                    output.push_str("Array_delete(&");
                    output.push_str(&arr_var);
                    output.push_str(");\n");

                    // Return the result
                    output.push_str(&indent_str);
                    output.push_str("return ");
                    output.push_str(&temp_var);
                    output.push_str(";\n");
                    return Ok(());
                }
            }
        }

        // Bug #143: Use emit_arg_string to handle hoisting
        let return_str = if !expr.params.is_empty() {
            Some(emit_arg_string(&expr.params[0], None, false, output, indent, ctx, context)?)
        } else {
            None
        };

        // Regular non-variadic return
        output.push_str(&indent_str);
        output.push_str("return");
        if let Some(ref ret_str) = return_str {
            output.push_str(" ");
            output.push_str(ret_str);
        }
        output.push_str(";\n");
    }
    Ok(())
}

fn emit_throw(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // Throw: params[0] = the value to throw (typically a struct constructor like DivideByZero())
    if expr.params.is_empty() {
        return Err("ccodegen: throw requires a value".to_string());
    }

    let indent_str = "    ".repeat(indent);
    let thrown_expr = &expr.params[0];

    // Bug #143: Use emit_arg_string to handle hoisting of thrown expression
    let thrown_str = emit_arg_string(thrown_expr, None, false, output, indent, ctx, context)?;

    // Get the thrown type name from the expression
    // For FCall, we need to determine if it's:
    // 1. A constructor like DivideByZero() - use the type name
    // 2. A function that returns an error type like format() - use the return type
    let nh_thrown_type_name = match &thrown_expr.node_type {
        NodeType::FCall(_) => {
            if !thrown_expr.params.is_empty() {
                if let NodeType::Identifier(name) = &thrown_expr.params[0].node_type {
                    // Check if this is a constructor (struct/enum) or a function call
                    // If it's a function that returns a type, use the return type
                    if let Some(func_def) = get_fcall_func_def(context, thrown_expr) {
                        // It's a function - use its return type as the thrown type
                        if let Some(nh_ret_type) = func_def.return_types.first() {
                            if let crate::rs::parser::ValueType::TCustom(type_name) = nh_ret_type {
                                type_name.clone()
                            } else {
                                // Return type is a primitive (like Str) - convert to name
                                crate::rs::parser::value_type_to_str(nh_ret_type)
                            }
                        } else {
                            // No return type, assume it's a constructor
                            name.clone()
                        }
                    } else {
                        // Not a function, assume it's a constructor
                        name.clone()
                    }
                } else {
                    return Err("ccodegen: throw FCall must have identifier as first param".to_string());
                }
            } else {
                return Err("ccodegen: throw FCall has no params".to_string());
            }
        }
        NodeType::Identifier(name) => {
            // Look up the type of the identifier (could be a variable or type name)
            if let Ok(nh_value_type) = get_value_type(context, thrown_expr) {
                if let crate::rs::parser::ValueType::TCustom(type_name) = nh_value_type {
                    type_name
                } else {
                    crate::rs::parser::value_type_to_str(&nh_value_type)
                }
            } else {
                // Fallback: assume identifier is a type name (for struct constructors without args)
                name.clone()
            }
        },
        NodeType::LLiteral(lit) => {
            // Literal values - determine their type
            match lit {
                Literal::Str(_) => "Str".to_string(),
                Literal::Number(_) => "I64".to_string(),
                Literal::List(_) => return Err("ccodegen: cannot throw a list literal".to_string()),
            }
        },
        _ => return Err(format!("ccodegen: throw expression must be a constructor, got {:?}", thrown_expr.node_type)),
    };

    // Check if this type is locally caught (has a catch block at function level)
    if let Some(nh_catch_info) = ctx.local_catch_labels.get(&nh_thrown_type_name) {
        let nh_label = nh_catch_info.label.clone();
        let nh_temp_var = nh_catch_info.temp_var.clone();

        // Issue #119: Check if this is an empty struct error
        let is_empty_local_err = if let Some(struct_def) = context.scope_stack.lookup_struct(&nh_thrown_type_name) {
            struct_def.members.is_empty()
        } else {
            false
        };

        // Issue #119: Skip storing value for empty struct errors - just goto
        if is_empty_local_err {
            output.push_str(&indent_str);
            output.push_str("goto ");
            output.push_str(&nh_label);
            output.push_str(";\n");
            return Ok(());
        }

        // Bug #143: Use thrown_str (already hoisted by emit_arg_string)
        output.push_str(&indent_str);
        output.push_str(&nh_temp_var);
        output.push_str(" = ");
        output.push_str(&thrown_str);
        output.push_str(";\n");

        // Jump to the catch block
        output.push_str(&indent_str);
        output.push_str("goto ");
        output.push_str(&nh_label);
        output.push_str(";\n");
        return Ok(());
    }

    // Find the index of this type in current_throw_types
    // Note: Str is represented as TCustom("Str") in the type system
    let mut nh_error_index: Option<usize> = None;
    for (nh_i, nh_vt) in ctx.current_throw_types.iter().enumerate() {
        if let crate::rs::parser::ValueType::TCustom(name) = nh_vt {
            if name == &nh_thrown_type_name {
                nh_error_index = Some(nh_i);
                break;
            }
        }
    }

    match nh_error_index {
        Some(idx) => {
            // Issue #119: Check if this is an empty struct error
            let nh_prop_err_type = &ctx.current_throw_types[idx];
            let is_empty_err = is_empty_error_struct(context, nh_prop_err_type);

            // Issue #119: Skip storing error value for empty struct errors
            if !is_empty_err {
                // Bug #143: Use thrown_str (already hoisted by emit_arg_string)
                output.push_str(&indent_str);
                output.push_str(&format!("*_err{} = ", idx + 1));
                output.push_str(&thrown_str);
                output.push_str(";\n");
            }

            // Return the error index (1-based, since 0 = success)
            output.push_str(&indent_str);
            output.push_str(&format!("return {};\n", idx + 1));
            Ok(())
        }
        None => Err(format!(
            "ccodegen: thrown type '{}' not found in function's throw types: {:?}",
            nh_thrown_type_name, ctx.current_throw_types
        )),
    }
}

fn emit_if(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // If: params[0] = condition, params[1] = then-body, params[2] = else-body (optional)
    if expr.params.len() < 2 {
        return Err("ccodegen: If requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);

    // Hoist declarations from both branches to before the if statement
    // (TIL has function-level scoping, not block-level scoping)
    // Bug #97: Use type-mangled names for shadowing support
    let then_decls = collect_declarations_in_body(&expr.params[1], context);
    for decl in then_decls {
        let type_prefix = value_type_to_c_prefix(&decl.value_type);
        let c_var_name = til_var_name(&decl.name, &type_prefix);
        if !ctx.declared_vars.contains(&c_var_name) {
            if let Ok(c_type) = til_type_to_c(&decl.value_type) {
                output.push_str(&indent_str);
                output.push_str(&c_type);
                output.push_str(" ");
                output.push_str(&c_var_name);
                output.push_str(";\n");
                ctx.declared_vars.insert(c_var_name);
                // Also register in scope_stack so get_value_type can find it
                context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut: false,
                    is_copy: false,
                    is_own: false,
                    is_comptime_const: false,
                });
            }
        }
    }
    if expr.params.len() > 2 {
        let hoist_else_decls = collect_declarations_in_body(&expr.params[2], context);
        for else_decl in hoist_else_decls {
            let else_type_prefix = value_type_to_c_prefix(&else_decl.value_type);
            let else_c_var_name = til_var_name(&else_decl.name, &else_type_prefix);
            if !ctx.declared_vars.contains(&else_c_var_name) {
                if let Ok(else_c_type) = til_type_to_c(&else_decl.value_type) {
                    output.push_str(&indent_str);
                    output.push_str(&else_c_type);
                    output.push_str(" ");
                    output.push_str(&else_c_var_name);
                    output.push_str(";\n");
                    ctx.declared_vars.insert(else_c_var_name);
                    // Also register in scope_stack so get_value_type can find it
                    context.scope_stack.declare_symbol(else_decl.name.clone(), SymbolInfo {
                        value_type: else_decl.value_type.clone(),
                        is_mut: false,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    });
                }
            }
        }
    }

    // Bug #143: Use emit_arg_string to handle hoisting in condition
    let cond_str = emit_arg_string(&expr.params[0], None, false, output, indent, ctx, context)?;
    output.push_str(&indent_str);
    output.push_str("if (");
    output.push_str(&cond_str);
    // Bool is a struct with .data field - extract for C truthiness
    if let Ok(crate::rs::parser::ValueType::TCustom(type_name)) = crate::rs::init::get_value_type(context, &expr.params[0]) {
        if type_name == "Bool" {
            output.push_str(".data");
        }
    }
    output.push_str(") {\n");

    // Don't save/restore declared_vars - TIL has function-level scoping
    // Variables declared in if branches stay declared for the rest of the function
    emit_body(&expr.params[1], output, indent + 1, ctx, context)?;

    output.push_str(&indent_str);
    output.push_str("}");

    // Else branch (optional)
    if expr.params.len() > 2 {
        // Check if it's an else-if (nested If) or else block
        if let NodeType::If = &expr.params[2].node_type {
            // Always wrap else-if in braces to ensure hoisted temp vars
            // from nested if conditions have proper scope
            output.push_str(" else {\n");
            emit_if(&expr.params[2], output, indent + 1, ctx, context)?;
            output.push_str(&indent_str);
            output.push_str("}\n");
        } else {
            output.push_str(" else {\n");
            emit_body(&expr.params[2], output, indent + 1, ctx, context)?;
            output.push_str(&indent_str);
            output.push_str("}\n");
        }
    } else {
        output.push_str("\n");
    }

    Ok(())
}

fn emit_while(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // While: params[0] = condition, params[1] = body
    if expr.params.len() < 2 {
        return Err("ccodegen: While requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);

    // Hoist declarations from loop body to before the while statement
    // (TIL has function-level scoping, not block-level scoping)
    // Bug #97: Use type-mangled names for shadowing support
    let body_decls = collect_declarations_in_body(&expr.params[1], context);
    for decl in body_decls {
        let type_prefix = value_type_to_c_prefix(&decl.value_type);
        let c_var_name = til_var_name(&decl.name, &type_prefix);
        if !ctx.declared_vars.contains(&c_var_name) {
            if let Ok(c_type) = til_type_to_c(&decl.value_type) {
                output.push_str(&indent_str);
                output.push_str(&c_type);
                output.push_str(" ");
                output.push_str(&c_var_name);
                output.push_str(";\n");
                ctx.declared_vars.insert(c_var_name);
                // Also register in scope_stack so get_value_type can find it
                context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut: false,
                    is_copy: false,
                    is_own: false,
                    is_comptime_const: false,
                });
            }
        }
    }

    // Bug #143: Use emit_arg_string to process condition (handles hoisting for by-ref/throwing)
    // Emit hoisting to a separate buffer first to detect if needed
    let mut hoist_buffer = String::new();
    let cond_str = emit_arg_string(&expr.params[0], None, false, &mut hoist_buffer, indent + 1, ctx, context)?;

    if hoist_buffer.is_empty() {
        // No hoisting needed - use simple while
        output.push_str(&indent_str);
        output.push_str("while (");
        output.push_str(&cond_str);
        // Bool is a struct with .data field - extract for C truthiness
        if let Ok(crate::rs::parser::ValueType::TCustom(type_name)) = crate::rs::init::get_value_type(context, &expr.params[0]) {
            if type_name == "Bool" {
                output.push_str(".data");
            }
        }
        output.push_str(") {\n");
    } else {
        // Hoisting needed in condition - transform to while(1) with hoisted calls and break
        output.push_str(&indent_str);
        output.push_str("while (1) {\n");

        // Emit hoisted statements inside the loop
        output.push_str(&hoist_buffer);

        // Emit condition check with break
        let inner_indent_str = "    ".repeat(indent + 1);
        output.push_str(&inner_indent_str);
        output.push_str("if (!(");
        output.push_str(&cond_str);
        // Bool is a struct with .data field - extract for C truthiness
        if let Ok(crate::rs::parser::ValueType::TCustom(type_name)) = crate::rs::init::get_value_type(context, &expr.params[0]) {
            if type_name == "Bool" {
                output.push_str(".data");
            }
        }
        output.push_str(")) break;\n");
    }

    // Don't save/restore declared_vars - TIL has function-level scoping
    // Variables declared in loops stay declared for the rest of the function
    emit_body(&expr.params[1], output, indent + 1, ctx, context)?;

    output.push_str(&indent_str);
    output.push_str("}\n");

    Ok(())
}

fn emit_break(_expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("break;\n");
    Ok(())
}

fn emit_continue(_expr: &Expr, output: &mut String, indent: usize) -> Result<(), String> {
    let indent_str = "    ".repeat(indent);
    output.push_str(&indent_str);
    output.push_str("continue;\n");
    Ok(())
}

// Info about a variadic parameter
struct VariadicParamInfo {
    elem_type: String,
    regular_count: usize,
}

// Info about a catch label for local throw/catch
#[derive(Clone)]
struct CatchLabelInfo {
    label: String,
    temp_var: String,
}

// Info about a catch block for code generation
// Note: TIL version also has catch_block field, but Rust accesses stmts[i] directly
struct CatchLabelInfoEntry {
    stmt_index: usize,      // Index in stmts array
    type_name: String,      // Error type being caught (e.g., "Str", "IndexOutOfBoundsError")
    label: String,          // Goto label for this catch
    temp_var: String,       // Temp variable holding the thrown value
}

// Info about a function parameter's type and whether passed by reference
struct ParamTypeInfo {
    value_type: Option<ValueType>,
    by_ref: bool,
}

// Info about a collected variable declaration for hoisting
struct CollectedDeclaration {
    name: String,
    value_type: ValueType,
}



// Info about a variadic function call
#[derive(Clone)]
struct VariadicFCallInfo {
    elem_type: String,
    regular_count: usize,
}

/// Collect all variable declarations in a body (recursively) for hoisting
/// Returns Vec of CollectedDeclaration structs
fn collect_declarations_in_body(body: &Expr, context: &mut Context) -> Vec<CollectedDeclaration> {
    let mut decls = Vec::new();
    // Track collected declarations for lookups during type inference
    let mut collected: std::collections::HashMap<String, ValueType> = std::collections::HashMap::new();

    if let NodeType::Body = &body.node_type {
        for stmt in &body.params {
            collect_declarations_recursive(stmt, &mut decls, &mut collected, context);
        }
    } else {
        collect_declarations_recursive(body, &mut decls, &mut collected, context);
    }

    decls
}

fn collect_declarations_recursive(expr: &Expr, decls: &mut Vec<CollectedDeclaration>, collected: &mut std::collections::HashMap<String, ValueType>, context: &mut Context) {
    match &expr.node_type {
        NodeType::Declaration(decl) => {
            // INFER_TYPE should have been resolved by typer
            if let ValueType::TCustom(name) = &decl.value_type {
                if name == INFER_TYPE {
                    panic!("Declaration '{}' has INFER_TYPE in ccodegen - should have been resolved by typer", decl.name);
                }
            }
            let value_type = decl.value_type.clone();
            // Track this declaration for future lookups (both in collected and scope_stack)
            collected.insert(decl.name.clone(), value_type.clone());
            // Also add to scope_stack so get_value_type can find it for subsequent declarations
            context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                value_type: value_type.clone(),
                is_mut: decl.is_mut,
                is_copy: false,
                is_own: false,
                is_comptime_const: false,
            });
            decls.push(CollectedDeclaration { name: decl.name.clone(), value_type });
        }
        NodeType::Body => {
            for stmt in &expr.params {
                collect_declarations_recursive(stmt, decls, collected, context);
            }
        }
        NodeType::If => {
            // Recurse into if branches
            if expr.params.len() >= 2 {
                collect_declarations_recursive(&expr.params[1], decls, collected, context);
            }
            if expr.params.len() >= 3 {
                collect_declarations_recursive(&expr.params[2], decls, collected, context);
            }
        }
        NodeType::While => {
            // Recurse into while body
            if expr.params.len() >= 2 {
                collect_declarations_recursive(&expr.params[1], decls, collected, context);
            }
        }
        NodeType::Catch => {
            // Recurse into catch body (params[2] is catch body)
            // params[0] = err_var, params[1] = err_type, params[2] = body
            if expr.params.len() >= 3 {
                collect_declarations_recursive(&expr.params[2], decls, collected, context);
            }
        }
        _ => {}
    }
}

fn emit_fcall(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // First param is the function name (or Type.method for type-qualified calls)
    if expr.params.is_empty() {
        return Err("ccodegen: FCall with no params".to_string());
    }

    // Get function name (handles both nested identifiers and precomp'd "Type.method" strings)
    let mut func_name = match get_func_name_string(&expr.params[0]) {
        Some(name) => name,
        None => return Err("ccodegen: FCall first param not Identifier".to_string()),
    };

    // For builtins, we need the original name with dots
    let orig_func_name = get_til_func_name_string(&expr.params[0])
        .unwrap_or_else(|| func_name.clone());

    // Check if this is a call to a nested (hoisted) function - use mangled name
    if let Some(mangled_name) = ctx.nested_func_names.get(&orig_func_name) {
        func_name = mangled_name.clone();
    }

    // Named args are already reordered by precomp, so no reordering needed here

    // Check for struct literal: TypeName(field=value, ...) -> (til_TypeName){.field = value, ...}
    // Uses lookup_struct to properly identify struct types (like interpreter.rs)
    let has_named_args = expr.params.iter().skip(1).any(|arg| matches!(&arg.node_type, NodeType::NamedArg(_)));
    if has_named_args {
        if let Some(struct_def) = context.scope_stack.lookup_struct(&func_name).cloned() {
            // Emit C compound literal: (til_TypeName){.field1 = val1, .field2 = val2, ...}
            output.push_str("(");
            output.push_str(TIL_PREFIX);
            output.push_str(&func_name);
            output.push_str(")");

            // Build map of named arg values
            let mut named_values: std::collections::HashMap<String, &Expr> = std::collections::HashMap::new();
            for arg in expr.params.iter().skip(1) {
                if let NodeType::NamedArg(field_name) = &arg.node_type {
                    if let Some(value_expr) = arg.params.first() {
                        named_values.insert(field_name.clone(), value_expr);
                    }
                }
            }

            if struct_def.members.is_empty() || struct_def.default_values.is_empty() {
                output.push_str("{}");
            } else {
                output.push_str("{");
                let mut first = true;
                for member in &struct_def.members {
                    if !member.is_mut {
                        continue;
                    }
                    if !first {
                        output.push_str(", ");
                    }
                    first = false;
                    output.push_str(".");
                    output.push_str(&member.name);
                    output.push_str(" = ");
                    // Use named arg value if provided, otherwise use default
                    if let Some(value_expr) = named_values.get(&member.name) {
                        emit_expr(value_expr, output, 0, ctx, context)?;
                    } else if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                        emit_expr(default_expr, output, 0, ctx, context)?;
                    } else {
                        output.push_str("0");
                    }
                }
                output.push_str("}");
            }
            return Ok(());
        }
    }

    let indent_str = "    ".repeat(indent);

    // Statement level vs expression level:
    // - indent > 0: statement level (can emit hoisting statements, adds semicolon)
    // - indent == 0: expression level (nested in larger expression, no hoisting, no semicolons)
    let is_stmt_level = indent > 0;

    // Get variadic info to know which args are variadic (need different handling)
    let variadic_regular_count = ctx.func_variadic_args.get(&orig_func_name)
        .map(|vi| vi.regular_count)
        .unwrap_or(usize::MAX);

    // Bug #143: Process ALL args upfront using single-pass emit_arg_string
    let arg_strings: Vec<String> = if is_stmt_level && expr.params.len() > 1 {
        let param_info: Vec<ParamTypeInfo> = if let Some(fd) = get_fcall_func_def(context, expr) {
            fd.args.iter().map(|fd_arg| ParamTypeInfo {
                value_type: Some(fd_arg.value_type.clone()),
                by_ref: param_needs_by_ref(fd_arg)
            }).collect()
        } else {
            // Handle builtins that don't have function definitions
            match orig_func_name.as_str() {
                "enum_to_str" | "type_as_str" => {
                    // These builtins take Dynamic arg - need proper hoisting
                    vec![ParamTypeInfo {
                        value_type: Some(ValueType::TCustom("Dynamic".to_string())),
                        by_ref: false,
                    }]
                }
                _ => Vec::new()
            }
        };
        let mut strings = Vec::new();
        for (i, arg) in expr.params.iter().skip(1).enumerate() {
            // For variadic args (i >= regular_count), use by_ref=false because
            // they get stored in temp vars, not passed directly to the function.
            // The temp vars are then passed via &temp_var to Array.set.
            let is_variadic_arg = i >= variadic_regular_count;
            let (param_type, by_ref) = param_info.get(i)
                .map(|info| (info.value_type.as_ref(), if is_variadic_arg { false } else { info.by_ref }))
                .unwrap_or((None, false));
            let arg_str = emit_arg_string(arg, param_type, by_ref, output, indent, ctx, context)?;
            strings.push(arg_str);
        }
        strings
    } else {
        Vec::new()
    };

    // For statement-level calls, we use arg_strings. For expression-level, we use direct emit.

    // Hardcoded builtins (compile-time intrinsics that can't be implemented in TIL)
    match orig_func_name.as_str() {
        // loc() is now resolved in precomp phase, so it never reaches here
        // type_as_str(T) - get type name as string
        // Can be called with a literal type name (type_as_str(Str)) or a Type variable (type_as_str(T))
        // Type variables are passed as const char* at runtime
        "type_as_str" => {
            if expr.params.len() < 2 {
                return Err("ccodegen: type_as_str requires 1 argument".to_string());
            }
            // Get the type name from the argument
            if let NodeType::Identifier(type_name) = &expr.params[1].node_type {
                // Check if this is a Type variable or a literal type name
                // Type variables are declared with value_type TCustom("Type")
                let is_type_var = if let Some(sym) = context.scope_stack.lookup_symbol(type_name) {
                    matches!(&sym.value_type, ValueType::TCustom(t) if t == "Type")
                } else {
                    false
                };
                if is_type_var {
                    // Type variable - already a const char*, wrap in Str struct literal
                    // Bug #60: Type is special - passed by value since it's already a pointer
                    // Bug #97: Use type-mangled name for Type variable reference
                    // Use new Str format with Ptr { data, is_borrowed=1 }, len, cap=0
                    let c_var_name = til_var_name_from_context(type_name, context);
                    output.push_str(&format!("(({}Str){{(({}Ptr){{({}I64){}, 1}}), strlen({}), 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, c_var_name, c_var_name));
                } else {
                    // Literal type name - create Str compound literal
                    if context.scope_stack.has_struct("Str") {
                        emit_str_literal(type_name, output);
                    } else {
                        output.push_str("\"");
                        output.push_str(type_name);
                        output.push_str("\"");
                    }
                }
            } else {
                emit_str_literal("unknown", output);
            }
            Ok(())
        },
        // enum_to_str(e) - get enum variant name as string
        // Emits call to til_EnumType_to_str(&e) which was generated during enum emission
        // The _to_str function takes a pointer because enum_to_str(e: Dynamic) passes by reference
        "enum_to_str" => {
            if expr.params.len() < 2 {
                return Err("ccodegen: enum_to_str requires 1 argument".to_string());
            }
            let arg = &expr.params[1];
            // Get the enum type from the argument
            let value_type = get_value_type(context, arg)?;
            if let ValueType::TCustom(enum_type_name) = value_type {
                // Verify it's an enum type
                if context.scope_stack.has_enum(&enum_type_name) {
                    output.push_str(&til_name(&enum_type_name));
                    output.push_str("_to_str(");
                    // Bug #143: Use pre-computed arg_strings when available
                    if is_stmt_level && !arg_strings.is_empty() {
                        // arg_strings[0] already has the proper (til_Dynamic*)& prefix
                        // But enum_to_str expects just &arg, so strip the Dynamic cast if present
                        let arg_str = &arg_strings[0];
                        let dynamic_prefix = format!("({}Dynamic*)", TIL_PREFIX);
                        if arg_str.starts_with(&dynamic_prefix) {
                            // Strip (til_Dynamic*) and keep &...
                            output.push_str(&arg_str[dynamic_prefix.len()..]);
                        } else {
                            output.push_str("&");
                            output.push_str(arg_str);
                        }
                    } else {
                        output.push_str("&");
                        emit_expr(arg, output, 0, ctx, context)?;
                    }
                    output.push_str(")");
                    Ok(())
                } else {
                    Err(format!("ccodegen: enum_to_str argument '{}' is not an enum type", enum_type_name))
                }
            } else {
                Err(format!("ccodegen: enum_to_str argument has non-custom type: {:?}", value_type))
            }
        },
        // enum_get_payload(e, payload_type, out) - extract enum payload into out parameter
        // Emits call to til_enum_get_payload runtime function
        "enum_get_payload" => {
            if expr.params.len() < 4 {
                return Err("ccodegen: enum_get_payload requires 3 arguments".to_string());
            }
            let payload_enum_arg = &expr.params[1];
            let payload_type_arg = &expr.params[2];
            let payload_out_arg = &expr.params[3];

            output.push_str(TIL_PREFIX);
            output.push_str("enum_get_payload((");
            output.push_str(TIL_PREFIX);
            output.push_str("Dynamic*)&");
            emit_expr(payload_enum_arg, output, 0, ctx, context)?;
            output.push_str(", &");
            // Emit type argument as Str (similar to size_of handling)
            if let NodeType::Identifier(payload_type_name) = &payload_type_arg.node_type {
                // Check if this is a Type variable or a literal type name
                let payload_is_type_var = if let Some(payload_sym) = context.scope_stack.lookup_symbol(payload_type_name) {
                    matches!(&payload_sym.value_type, ValueType::TCustom(t) if t == "Type")
                } else {
                    false
                };
                if payload_is_type_var {
                    // Type variable - wrap in Str struct literal
                    // Bug #97: Use type-mangled name for Type variable reference
                    // Use new Str format with Ptr { data, is_borrowed=1 }, len, cap=0
                    let c_var_name = til_var_name_from_context(payload_type_name, context);
                    output.push_str(&format!("(({}Str){{(({}Ptr){{({}I64){}, 1}}), strlen({}), 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, c_var_name, c_var_name));
                } else {
                    // Literal type name - create Str compound literal
                    emit_str_literal(payload_type_name, output);
                }
            } else {
                return Err("ccodegen: enum_get_payload type argument must be a type name".to_string());
            }
            output.push_str(", (");
            output.push_str(TIL_PREFIX);
            output.push_str("Dynamic*)&");
            emit_expr(payload_out_arg, output, 0, ctx, context)?;
            output.push_str(");");
            Ok(())
        },
        // size_of(T) - runtime type size lookup via til_size_of function
        // Can be called with a literal type name (size_of(Str)) or a Type variable (size_of(T))
        "size_of" => {
            if expr.params.len() < 2 {
                return Err("ccodegen: size_of requires 1 argument".to_string());
            }
            output.push_str(TIL_PREFIX);
            output.push_str("size_of(&");  // Bug #60: til_size_of now takes const til_Str*
            // If it's a literal type name, emit compound literal
            // If it's a variable, the variable already holds a Type (which is const char*)
            if let NodeType::Identifier(type_name) = &expr.params[1].node_type {
                // Check if this is a Type variable or a literal type name
                // Type variables are declared with value_type TCustom("Type")
                let is_type_var = if let Some(sym) = context.scope_stack.lookup_symbol(type_name) {
                    matches!(&sym.value_type, ValueType::TCustom(t) if t == "Type")
                } else {
                    false
                };
                if is_type_var {
                    // Type variable - already a const char*, wrap in Str struct literal
                    // Bug #60: Type is special - passed by value since it's already a pointer
                    // Bug #97: Use type-mangled name for Type variable reference
                    // Use new Str format with Ptr { data, is_borrowed=1 }, len, cap=0
                    let c_var_name = til_var_name_from_context(type_name, context);
                    output.push_str(&format!("(({}Str){{(({}Ptr){{({}I64){}, 1}}), strlen({}), 0}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, c_var_name, c_var_name));
                } else {
                    // Literal type name - create Str compound literal
                    emit_str_literal(type_name, output);
                }
            } else {
                // Not an identifier - emit as expression (should be Type/const char*)
                // Bug #60: emit_expr will dereference Type params via (*til_name)
                // Use new Str format with Ptr { data, is_borrowed=1 }, len, cap=0
                output.push_str(&format!("(({}Str){{(({}Ptr){{({}I64)", TIL_PREFIX, TIL_PREFIX, TIL_PREFIX));
                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                output.push_str(", 1}), strlen(");
                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                output.push_str("), 0})");
            }
            output.push_str(")");
            Ok(())
        },
        // to_ptr(var) - get address of variable
        // For Dynamic params (already void*), just cast without taking address
        "to_ptr" => {
            if expr.params.len() < 2 {
                return Err("ccodegen: to_ptr requires 1 argument".to_string());
            }
            let arg = &expr.params[1];
            // Check if arg is a Dynamic parameter (void*) - just use the pointer directly
            let is_dynamic_param = if let NodeType::Identifier(name) = &arg.node_type {
                if arg.params.is_empty() {
                    if let Some(sym) = context.scope_stack.lookup_symbol(name) {
                        matches!(&sym.value_type, ValueType::TCustom(t) if t == "Dynamic")
                    } else {
                        false
                    }
                } else {
                    false
                }
            } else {
                false
            };

            // Bug #143: Use pre-computed arg_strings when available (statement-level)
            if is_stmt_level && !arg_strings.is_empty() {
                // arg_strings[0] is like "(til_Dynamic*)&x" or just "x"
                // to_ptr wants (til_I64)&x, so convert the cast
                let arg_str = &arg_strings[0];
                let dynamic_prefix = format!("({}Dynamic*)", TIL_PREFIX);
                output.push_str("(");
                output.push_str(TIL_PREFIX);
                output.push_str("I64)");
                if arg_str.starts_with(&dynamic_prefix) {
                    // Strip (til_Dynamic*) and keep the rest (which includes &)
                    output.push_str(&arg_str[dynamic_prefix.len()..]);
                } else {
                    // No Dynamic cast present - add & if not already there
                    if !arg_str.starts_with('&') {
                        output.push_str("&");
                    }
                    output.push_str(arg_str);
                }
                return Ok(());
            }

            // Expression-level: emit directly
            output.push_str("(");
            output.push_str(TIL_PREFIX);
            output.push_str("I64)");
            if is_dynamic_param {
                if let NodeType::Identifier(name) = &arg.node_type {
                    // Bug #97: Use type-mangled name
                    output.push_str(&til_var_name_from_context(name, context));
                }
            } else {
                output.push_str("&");
                emit_expr(arg, output, 0, ctx, context)?;
            }
            Ok(())
        },
        // User-defined function call
        _ => {
            output.push_str(&indent_str);

            // Check for type-qualified call on FCall result: func_name(fcall_result, args...)
            // This happens for chained method calls like delimiter.len().eq(0)
            // Parser produces: FCall { params: [Identifier("eq"), FCall { ... }, LLiteral(0)] }
            // Only check this for simple func names (no nested identifiers)
            if expr.params[0].params.is_empty() && expr.params.len() >= 2 {
                if let NodeType::FCall(_) = &expr.params[1].node_type {
                    // The second param is an FCall result - use get_value_type to get its return type
                    if let Ok(fcall_ret_type) = get_value_type(context, &expr.params[1]) {
                        if let ValueType::TCustom(type_name) = &fcall_ret_type {
                            let candidate = format!("{}.{}", type_name, orig_func_name);
                            if context.scope_stack.has_func(&candidate) {
                                // Emit as Type_method(fcall_result, args...)
                                output.push_str(TIL_PREFIX);
                                output.push_str(type_name);
                                output.push_str("_");
                                output.push_str(&orig_func_name);
                                output.push_str("(");
                                // First arg is the fcall result
                                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                                // Remaining args
                                for arg in expr.params.iter().skip(2) {
                                    output.push_str(", ");
                                    emit_expr(arg, output, 0, ctx, context)?;
                                }
                                output.push_str(")");
                                if is_stmt_level {
                                    output.push_str(";\n");
                                }
                                return Ok(());
                            }
                        }
                    }
                }
            }

            // Check for struct construction: TypeName() -> (til_TypeName){defaults...}
            // Use lookup_struct to verify this is a known struct type
            let struct_def_opt = context.scope_stack.lookup_struct(&func_name).cloned();
            if struct_def_opt.is_some()
                && expr.params.len() == 1    // No constructor args
            {
                // Use the struct definition to get default values
                if let Some(struct_def) = struct_def_opt {
                    if struct_def.members.is_empty() || struct_def.default_values.is_empty() {
                        output.push_str("(");
                        output.push_str(TIL_PREFIX);
                        output.push_str(&func_name);
                        output.push_str("){}");
                    } else {
                        // Has default values - emit designated initializer
                        output.push_str(&indent_str);
                        output.push_str("(");
                        output.push_str(TIL_PREFIX);
                        output.push_str(&func_name);
                        output.push_str("){");
                        let mut first = true;
                        for member in &struct_def.members {
                            if !member.is_mut {
                                continue;
                            }
                            if !first {
                                output.push_str(", ");
                            }
                            first = false;
                            output.push_str(".");
                            output.push_str(&member.name);
                            output.push_str(" = ");
                            if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                                emit_expr(default_expr, output, 0, ctx, context)?;
                            } else {
                                output.push_str("0");
                            }
                        }
                        output.push_str("}");
                    }
                } else {
                    output.push_str("(");
                    output.push_str(TIL_PREFIX);
                    output.push_str(&func_name);
                    output.push_str("){}");
                }

                if is_stmt_level {
                    output.push_str(";\n");
                }
                return Ok(());
            }

            // Regular function call
            // func_name already has underscores from get_func_name_string
            // Detect and construct variadic array if needed (only at statement level)
            // At expression level, variadic calls are not supported directly
            let variadic_arr_var: Option<String> = if is_stmt_level {
                if let Some(variadic_info) = ctx.func_variadic_args.get(&orig_func_name) {
                    let elem_type = variadic_info.elem_type.clone();
                    let regular_count = variadic_info.regular_count;
                    // Bug #143: Use pre-computed arg_strings
                    let variadic_arg_strings = &arg_strings[regular_count..];
                    Some(emit_variadic_array_with_strings(&elem_type, variadic_arg_strings, output, indent, ctx)?)
                } else {
                    None
                }
            } else {
                None
            };

            // Check if this is an enum variant constructor (Type.Variant or Type_Variant)
            // Need to emit til_Type_make_Variant instead of til_Type_Variant
            let is_enum_constructor = if func_name.contains('_') {
                // Check if Type_Variant where Type is an enum and Variant is a variant
                let parts: Vec<&str> = func_name.splitn(2, '_').collect();
                if parts.len() == 2 {
                    let type_name = parts[0];
                    let variant_name = parts[1];
                    context.scope_stack.lookup_enum(type_name)
                        .map(|e| e.contains_key(variant_name))
                        .unwrap_or(false)
                } else {
                    false
                }
            } else {
                false
            };

            output.push_str(TIL_PREFIX);
            if is_enum_constructor {
                // Emit til_Type_make_Variant
                let parts: Vec<&str> = func_name.splitn(2, '_').collect();
                output.push_str(parts[0]);
                output.push_str("_make_");
                output.push_str(parts[1]);
            } else {
                output.push_str(&func_name);
            }
            output.push_str("(");

            // Check if this is a variadic function call
            if let Some(variadic_info) = ctx.func_variadic_args.get(&orig_func_name) {
                let regular_count = variadic_info.regular_count;
                // Bug #143: Use pre-computed arg_strings
                if is_stmt_level {
                    // Emit regular args from arg_strings
                    for (vstmt_arg_i, vstmt_arg_str) in arg_strings.iter().take(regular_count).enumerate() {
                        if vstmt_arg_i > 0 {
                            output.push_str(", ");
                        }
                        output.push_str(vstmt_arg_str);
                    }
                } else {
                    // Expression-level variadic calls - emit regular args with by-ref handling
                    let vexpr_param_info: Vec<(Option<ValueType>, bool)> = if let Some(fd) = get_fcall_func_def(context, expr) {
                        fd.args.iter().map(|fd_arg| (Some(fd_arg.value_type.clone()), param_needs_by_ref(fd_arg))).collect()
                    } else {
                        Vec::new()
                    };
                    for (vexpr_arg_i, vexpr_arg) in expr.params.iter().skip(1).take(regular_count).enumerate() {
                        if vexpr_arg_i > 0 {
                            output.push_str(", ");
                        }
                        let vexpr_by_ref = vexpr_param_info.get(vexpr_arg_i).map(|(_, b)| *b).unwrap_or(false);
                        if vexpr_by_ref && is_pure_lvalue(vexpr_arg, context) {
                            if let NodeType::Identifier(name) = &vexpr_arg.node_type {
                                if vexpr_arg.params.is_empty() && (ctx.current_ref_params.contains(name) || ctx.current_variadic_params.contains_key(name)) {
                                    // Already a pointer - emit name directly without dereference
                                    // Bug #97: Use type-mangled name
                                    output.push_str(&til_var_name_from_context(name, context));
                                } else {
                                    output.push_str("&");
                                    emit_expr(vexpr_arg, output, 0, ctx, context)?;
                                }
                            } else {
                                output.push_str("&");
                                emit_expr(vexpr_arg, output, 0, ctx, context)?;
                            }
                        } else {
                            emit_expr(vexpr_arg, output, 0, ctx, context)?;
                        }
                    }
                }

                // Emit variadic array pointer
                if let Some(ref arr_var) = variadic_arr_var {
                    if regular_count > 0 {
                        output.push_str(", ");
                    }
                    output.push_str("&");
                    output.push_str(arr_var);
                }
            } else {
                // Regular non-variadic function call
                // Bug #143: Use pre-computed arg_strings
                if is_stmt_level {
                    for (nstmt_arg_i, nstmt_arg_str) in arg_strings.iter().enumerate() {
                        if nstmt_arg_i > 0 {
                            output.push_str(", ");
                        }
                        output.push_str(nstmt_arg_str);
                    }
                } else {
                    // Expression-level call: emit args with by-ref handling
                    // Bug #143: Need to hoist non-lvalue args that require by-ref
                    // Look up function to get param info for by-ref handling
                    let param_info: Vec<(Option<ValueType>, bool)> = if let Some(fd) = get_fcall_func_def(context, expr) {
                        fd.args.iter().map(|fd_arg| (Some(fd_arg.value_type.clone()), param_needs_by_ref(fd_arg))).collect()
                    } else {
                        Vec::new()
                    };

                    // Bug #143: Process all args through emit_arg_string to handle hoisting
                    // Collect hoisting code and arg strings
                    let mut nexpr_arg_hoist = String::new();
                    let mut nexpr_arg_strings: Vec<String> = Vec::new();
                    for (nexpr_arg_i, nexpr_arg) in expr.params.iter().skip(1).enumerate() {
                        if let Some(nexpr_type_name) = get_type_arg_name(nexpr_arg, context) {
                            nexpr_arg_strings.push(format!("\"{}\"", nexpr_type_name));
                        } else {
                            let nexpr_param_type = param_info.get(nexpr_arg_i).and_then(|(t, _)| t.as_ref());
                            let nexpr_by_ref = param_info.get(nexpr_arg_i).map(|(_, b)| *b).unwrap_or(false);
                            let nexpr_arg_str = emit_arg_string(nexpr_arg, nexpr_param_type, nexpr_by_ref, &mut nexpr_arg_hoist, indent, ctx, context)?;
                            nexpr_arg_strings.push(nexpr_arg_str);
                        }
                    }

                    // If there's hoisting code, we need to use a GNU statement expression
                    // But we're already in the middle of emitting the call!
                    // This is problematic - we'd need to restructure the entire call
                    // For now, emit args normally and hope the hoisting was handled elsewhere
                    // TODO: Proper fix would require emit_fcall to return a string, not write to output
                    if !nexpr_arg_hoist.is_empty() {
                        // WORKAROUND: Can't properly hoist mid-expression
                        // This shouldn't happen for common cases where calls are at statement level
                        // For now, just emit what we have (may cause compilation errors)
                        // A proper fix would require restructuring emit_fcall
                    }

                    for (nexpr_out_i, nexpr_out_str) in nexpr_arg_strings.iter().enumerate() {
                        if nexpr_out_i > 0 {
                            output.push_str(", ");
                        }
                        output.push_str(nexpr_out_str);
                    }
                }
            }

            output.push_str(")");
            // Only add statement terminator if this is a statement
            if is_stmt_level {
                output.push_str(";\n");
            }

            // Emit Array.delete if variadic array was constructed
            if let Some(arr_var) = &variadic_arr_var {
                output.push_str(&indent_str);
                output.push_str(TIL_PREFIX);
                output.push_str("Array_delete(&");
                output.push_str(arr_var);
                output.push_str(");\n");
            }

            Ok(())
        },
    }
}

// Emit a Str literal as a compound literal
// is_borrowed=1 for string literals (they point to static .rodata, don't free)
fn emit_str_literal(s: &str, output: &mut String) {
    // Str { c_string: Ptr { data: I64, is_borrowed: I64 }, _len: I64, cap: I64 }
    output.push_str(&format!("(({}Str){{(({}Ptr){{({}I64)\"", TIL_PREFIX, TIL_PREFIX, TIL_PREFIX));
    // Escape special characters for C string literals
    for c in s.chars() {
        match c {
            '\0' => output.push_str("\\0"),
            '\n' => output.push_str("\\n"),
            '\r' => output.push_str("\\r"),
            '\t' => output.push_str("\\t"),
            '\\' => output.push_str("\\\\"),
            '"' => output.push_str("\\\""),
            _ => output.push(c),
        }
    }
    // Close Ptr (data, is_borrowed=1), then Str (c_string, _len, cap=0 for literals)
    output.push_str(&format!("\", 1}}), {}, 0}})", s.len()));
}

fn emit_literal(lit: &Literal, output: &mut String, context: &Context) -> Result<(), String> {
    match lit {
        Literal::Str(s) => {
            let has_str = context.scope_stack.has_struct("Str");
            if has_str {
                emit_str_literal(s, output);
            } else {
                output.push('"');
                // Escape special characters for C string literals
                for c in s.chars() {
                    match c {
                        '\0' => output.push_str("\\0"),
                        '\n' => output.push_str("\\n"),
                        '\r' => output.push_str("\\r"),
                        '\t' => output.push_str("\\t"),
                        '\\' => output.push_str("\\\\"),
                        '"' => output.push_str("\\\""),
                        _ => output.push(c),
                    }
                }
                output.push('"');
            }
            Ok(())
        },
        Literal::Number(n) => {
            output.push_str(n);
            Ok(())
        },
        Literal::List(_) => Err("ccodegen: List literals not yet supported".to_string()),
    }
}
