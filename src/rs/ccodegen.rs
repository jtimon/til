// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal, SFuncDef, SEnumDef, ValueType, Declaration, INFER_TYPE};
use crate::rs::init::{Context, get_value_type, ScopeFrame, SymbolInfo, ScopeType};
use crate::rs::typer::get_func_def_for_fcall_with_expr;
use std::collections::{HashMap, HashSet};

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
    // Map of hoisted expression addresses to their temp variable names
    // Used to track deeply nested variadic/throwing calls that have been hoisted
    hoisted_exprs: HashMap<usize, String>,
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
    // Map of hoisted struct default expressions ("struct_name:member_name" -> temp var name)
    // Used to track which struct literal defaults were hoisted as temp vars
    hoisted_struct_defaults: HashMap<String, String>,
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
            hoisted_exprs: HashMap::new(),
            local_catch_labels: HashMap::new(),
            current_function_name: String::new(),
            hoisted_functions: Vec::new(),
            hoisted_prototypes: Vec::new(),
            nested_func_names: HashMap::new(),
            hoisted_struct_defaults: HashMap::new(),
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
                s if s == INFER_TYPE => None,
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

/// Hoist a single expression if it's a throwing call, or recursively hoist throwing calls within it.
/// Returns Some(temp_var_name) if the expression itself was hoisted, None otherwise.
/// The hoisted_exprs map in ctx is updated with any sub-expressions that were hoisted.
fn hoist_throwing_expr(
    expr: &Expr,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<Option<String>, String> {
    let indent_str = "    ".repeat(indent);

    // Check if this expression itself is a throwing call
    if let NodeType::FCall = &expr.node_type {
    if let Some(throwing_fd) = get_fcall_func_def(context, expr) {
    if !throwing_fd.throw_types.is_empty() {
        // First, recursively hoist any throwing calls in this call's arguments
        let nested_hoisted: std::collections::HashMap<usize, String> = if expr.params.len() > 1 {
            let nested_args = &expr.params[1..];
            let nested_vec = hoist_throwing_args(nested_args, output, indent, ctx, context)?;
            nested_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
        } else {
            std::collections::HashMap::new()
        };

        let temp_var = next_mangled(ctx);

        // Determine the C type for the temp variable
        let c_type = if !throwing_fd.return_types.is_empty() {
            til_type_to_c(throwing_fd.return_types.first().unwrap()).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?
        } else {
            return Err(expr.lang_error(&context.path, "ccodegen", "Cannot hoist throwing call with no return type"));
        };

        // Declare temp variable
        output.push_str(&indent_str);
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(&temp_var);
        output.push_str(";\n");

        // Declare error variables for each throw type
        let temp_suffix = next_mangled(ctx);
        for (decl_err_idx, decl_throw_type) in throwing_fd.throw_types.iter().enumerate() {
            if let ValueType::TCustom(type_name) = decl_throw_type {
                output.push_str(&indent_str);
                output.push_str(&til_name(type_name));
                output.push_str(" _err");
                output.push_str(&decl_err_idx.to_string());
                output.push_str("_");
                output.push_str(&temp_suffix);
                output.push_str(";\n");
            }
        }

        // Detect and construct variadic array if needed
        let variadic_info = detect_variadic_fcall(expr, ctx);
        let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
            let variadic_args: Vec<_> = expr.params.iter().skip(1 + vi.regular_count).collect();
            if !variadic_args.is_empty() {
                Some(hoist_variadic_args(&vi.elem_type, &variadic_args, &nested_hoisted, vi.regular_count, output, indent, ctx, context)?)
            } else {
                Some(hoist_variadic_args(&vi.elem_type, &[], &nested_hoisted, vi.regular_count, output, indent, ctx, context)?)
            }
        } else {
            None
        };

        // Emit the function call with output pointers
        output.push_str(&indent_str);
        output.push_str("int _status_");
        output.push_str(&temp_suffix);
        output.push_str(" = ");

        // Emit the function name and args (using nested hoisted temps)
        emit_fcall_name_and_args_for_throwing(expr, &temp_var, &temp_suffix, &throwing_fd.throw_types, &nested_hoisted, variadic_arr_var.as_deref(), output, ctx, context)?;

        output.push_str(";\n");

        // Emit error checking - propagate or goto based on context
        // Check if there are local catch labels for these error types
        let mut has_local_catch = false;
        for check_throw_type in &throwing_fd.throw_types {
            if let ValueType::TCustom(type_name) = check_throw_type {
                if ctx.local_catch_labels.contains_key(type_name) {
                    has_local_catch = true;
                    break;
                }
            }
        }

        if has_local_catch {
            // Use goto for local catches
            for (local_err_idx, local_throw_type) in throwing_fd.throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = local_throw_type {
                    if let Some(catch_info) = ctx.local_catch_labels.get(type_name) {
                        output.push_str(&indent_str);
                        output.push_str("if (_status_");
                        output.push_str(&temp_suffix);
                        output.push_str(" == ");
                        output.push_str(&(local_err_idx + 1).to_string());
                        output.push_str(") { ");
                        output.push_str(&catch_info.temp_var);
                        output.push_str(" = _err");
                        output.push_str(&local_err_idx.to_string());
                        output.push_str("_");
                        output.push_str(&temp_suffix);
                        output.push_str("; goto ");
                        output.push_str(&catch_info.label);
                        output.push_str("; }\n");
                    }
                }
            }
        } else {
            // Propagate errors
            output.push_str(&indent_str);
            output.push_str("if (_status_");
            output.push_str(&temp_suffix);
            output.push_str(" != 0) {\n");

            for (prop_err_idx, prop_throw_type) in throwing_fd.throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = prop_throw_type {
                    for (curr_idx, curr_throw) in ctx.current_throw_types.iter().enumerate() {
                        if let ValueType::TCustom(curr_type_name) = curr_throw {
                            if curr_type_name == type_name {
                                output.push_str(&indent_str);
                                output.push_str("    if (_status_");
                                output.push_str(&temp_suffix);
                                output.push_str(" == ");
                                output.push_str(&(prop_err_idx + 1).to_string());
                                output.push_str(") { *_err");
                                output.push_str(&(curr_idx + 1).to_string());
                                output.push_str(" = _err");
                                output.push_str(&prop_err_idx.to_string());
                                output.push_str("_");
                                output.push_str(&temp_suffix);
                                output.push_str("; return ");
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
        }

        // Emit Array.delete if variadic array was constructed
        if let Some(arr_var) = &variadic_arr_var {
            output.push_str(&indent_str);
            output.push_str(TIL_PREFIX);
            output.push_str("Array_delete(&");
            output.push_str(arr_var);
            output.push_str(");\n");
        }

        // Record in hoisted_exprs map using expression address
        let expr_addr = expr as *const Expr as usize;
        ctx.hoisted_exprs.insert(expr_addr, temp_var.clone());

        return Ok(Some(temp_var));
    }}}

    // Check if this is a non-throwing variadic call - also needs hoisting
    if let NodeType::FCall = &expr.node_type {
        if let Some(variadic_fcall_info) = detect_variadic_fcall(expr, ctx) {
            // Recursively hoist any throwing/variadic calls in this call's arguments first
            let ntv_nested_hoisted: std::collections::HashMap<usize, String> = if expr.params.len() > 1 {
                let ntv_nested_args = &expr.params[1..];
                let ntv_nested_vec = hoist_throwing_args(ntv_nested_args, output, indent, ctx, context)?;
                ntv_nested_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
            } else {
                std::collections::HashMap::new()
            };

            let ntv_temp_var = next_mangled(ctx);

            // Determine return type from function
            let ntv_func_name = get_fcall_func_name(expr)
                .ok_or_else(|| expr.lang_error(&context.path, "ccodegen", "Cannot determine function name"))?;
            let ntv_fd = get_fcall_func_def(context, expr)
                .ok_or_else(|| expr.lang_error(&context.path, "ccodegen", &format!("Function not found: {}", ntv_func_name)))?;
            let ntv_ret_type = ntv_fd.return_types.first()
                .ok_or_else(|| expr.lang_error(&context.path, "ccodegen", "Function has no return type"))?;
            let ntv_c_type = til_type_to_c(ntv_ret_type)
                .map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?;

            // Declare temp variable
            output.push_str(&indent_str);
            output.push_str(&ntv_c_type);
            output.push_str(" ");
            output.push_str(&ntv_temp_var);
            output.push_str(";\n");

            // Construct variadic array
            let ntv_variadic_args: Vec<_> = expr.params.iter().skip(1 + variadic_fcall_info.regular_count).collect();
            let ntv_variadic_arr_var = if !ntv_variadic_args.is_empty() {
                hoist_variadic_args(&variadic_fcall_info.elem_type, &ntv_variadic_args, &ntv_nested_hoisted, variadic_fcall_info.regular_count, output, indent, ctx, context)?
            } else {
                hoist_variadic_args(&variadic_fcall_info.elem_type, &[], &ntv_nested_hoisted, variadic_fcall_info.regular_count, output, indent, ctx, context)?
            };

            // Calculate param_by_ref and param_types for proper by-ref handling
            let ntv_param_by_ref: Vec<bool> = expr.params.iter().skip(1).enumerate()
                .map(|(ntv_pi, _)| ntv_fd.args.get(ntv_pi).map(|a| param_needs_by_ref(a)).unwrap_or(false))
                .collect();
            let ntv_param_types: Vec<Option<ValueType>> = expr.params.iter().skip(1).enumerate()
                .map(|(ntv_pi, _)| ntv_fd.args.get(ntv_pi).map(|a| a.value_type.clone()))
                .collect();

            // Emit the function call (non-throwing, so direct assignment)
            output.push_str(&indent_str);
            output.push_str(&ntv_temp_var);
            output.push_str(" = ");

            // Emit function name
            let ntv_fcall_func_name = get_fcall_func_name(expr);
            if let Some(fcall_name) = &ntv_fcall_func_name {
                output.push_str(&til_func_name(fcall_name));
            }
            output.push('(');

            // Emit regular args (using nested hoisted temps)
            let mut ntv_first = true;
            for (ntv_i, ntv_param) in expr.params.iter().skip(1).take(variadic_fcall_info.regular_count).enumerate() {
                if !ntv_first {
                    output.push_str(", ");
                }
                ntv_first = false;
                let ntv_ptype_val = ntv_param_types.get(ntv_i).and_then(|p| p.as_ref());
                let ntv_by_ref = ntv_param_by_ref.get(ntv_i).copied().unwrap_or(false);
                emit_arg_with_param_type(ntv_param, ntv_i, &ntv_nested_hoisted, ntv_ptype_val, ntv_by_ref, output, ctx, context)?;
            }

            // Emit variadic array pointer
            if !ntv_first {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(&ntv_variadic_arr_var);
            output.push_str(");\n");

            // Emit Array.delete for the variadic array
            output.push_str(&indent_str);
            output.push_str(TIL_PREFIX);
            output.push_str("Array_delete(&");
            output.push_str(&ntv_variadic_arr_var);
            output.push_str(");\n");

            // Record in hoisted_exprs map using expression address
            let ntv_expr_addr = expr as *const Expr as usize;
            ctx.hoisted_exprs.insert(ntv_expr_addr, ntv_temp_var.clone());

            return Ok(Some(ntv_temp_var));
        }
    }

    // Check if this is a struct literal with throwing default values
    if let NodeType::FCall = &expr.node_type {
        if let Some(sl_func_name) = get_func_name_string(&expr.params[0]) {
            let has_named_args = expr.params.iter().skip(1).any(|sl_arg| matches!(&sl_arg.node_type, NodeType::NamedArg(_)));
            if let Some(sl_struct_def) = context.scope_stack.lookup_struct(&sl_func_name).cloned() {
                if expr.params.len() == 1 || has_named_args {
                    // This is a struct literal - check for throwing defaults
                    // Build map of named arg names that are provided
                    let mut provided_names: std::collections::HashSet<String> = std::collections::HashSet::new();
                    for sl_na_arg in expr.params.iter().skip(1) {
                        if let NodeType::NamedArg(field_name) = &sl_na_arg.node_type {
                            provided_names.insert(field_name.clone());
                        }
                    }

                    // For each member with a default that's a throwing call and not overridden, emit temp var
                    for member in &sl_struct_def.members {
                        if !member.is_mut {
                            continue;
                        }
                        if provided_names.contains(&member.name) {
                            continue; // Named arg overrides default
                        }
                        if let Some(sl_default_expr) = sl_struct_def.default_values.get(&member.name) {
                            if is_throwing_fcall(sl_default_expr, context) {
                                // Get the function's throw types
                                let sl_throw_types = if let Some(sl_first_param) = sl_default_expr.params.first() {
                                    if let Some(lookup_name) = get_til_func_name_string(sl_first_param) {
                                        context.scope_stack.lookup_func(&lookup_name)
                                            .map(|fd| fd.throw_types.clone())
                                            .unwrap_or_default()
                                    } else {
                                        Vec::new()
                                    }
                                } else {
                                    Vec::new()
                                };

                                let sl_temp_name = next_mangled(ctx);
                                // Emit the function call with out-param using emit_throwing_call_propagate
                                emit_throwing_call_propagate(sl_default_expr, &sl_throw_types, Some(&sl_temp_name), None, output, indent, ctx, context)?;
                                // Record that this struct default was hoisted using "struct_name:member_name" key
                                let sl_key = format!("{}:{}", sl_func_name, member.name);
                                ctx.hoisted_struct_defaults.insert(sl_key, sl_temp_name);
                            } else {
                                // Also recursively hoist any throwing expressions in the default
                                // This handles nested struct constructors with throwing defaults
                                hoist_throwing_expr(sl_default_expr, output, indent, ctx, context)?;
                            }
                        }
                    }
                }
            }
        }
    }

    // Not a throwing call or variadic call - recursively check sub-expressions
    // For FCall, check all arguments
    if let NodeType::FCall = &expr.node_type {
        if expr.params.len() > 1 {
            for arg in &expr.params[1..] {
                hoist_throwing_expr(arg, output, indent, ctx, context)?;
            }
        }
    }
    // For other expression types with sub-expressions, recurse into them
    else {
        for param in &expr.params {
            hoist_throwing_expr(param, output, indent, ctx, context)?;
        }
    }

    Ok(None)
}

/// Hoist throwing function calls from arguments (recursively)
/// Returns a vector of HoistedArg for arguments that were hoisted
fn hoist_throwing_args(
    args: &[Expr],  // The arguments (skip first param which is function name)
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<Vec<HoistedArg>, String> {
    let mut hoisted = Vec::new();
    let indent_str = "    ".repeat(indent);

    for (idx, arg) in args.iter().enumerate() {
        // Check if it's a throwing call
        let throwing_fd_opt = if let NodeType::FCall = &arg.node_type {
            get_fcall_func_def(context, arg).filter(|fd| !fd.throw_types.is_empty())
        } else {
            None
        };
        // Check if it's a variadic call (even if not throwing)
        let variadic_info = detect_variadic_fcall(arg, ctx);

        // Handle throwing calls (may also be variadic)
        if let Some(thr_fd) = throwing_fd_opt {
            // RECURSIVELY hoist any throwing calls in this call's arguments first
            let thr_nested_hoisted: std::collections::HashMap<usize, String> = if arg.params.len() > 1 {
                let thr_nested_args = &arg.params[1..];
                let thr_nested_vec = hoist_throwing_args(thr_nested_args, output, indent, ctx, context)?;
                thr_nested_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
            } else {
                std::collections::HashMap::new()
            };

            let temp_var = next_mangled(ctx);

            // Determine the C type for the temp variable
            let thr_c_type = if !thr_fd.return_types.is_empty() {
                til_type_to_c(thr_fd.return_types.first().unwrap()).map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))?
            } else {
                return Err(arg.lang_error(&context.path, "ccodegen", "Cannot hoist throwing call with no return type"));
            };

            // Declare temp variable
            output.push_str(&indent_str);
            output.push_str(&thr_c_type);
            output.push_str(" ");
            output.push_str(&temp_var);
            output.push_str(";\n");

            // Declare error variables for each throw type
            let thr_temp_suffix = next_mangled(ctx);
            for (thr_decl_err_idx, thr_decl_throw_type) in thr_fd.throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = thr_decl_throw_type {
                    output.push_str(&indent_str);
                    output.push_str(&til_name(type_name));
                    output.push_str(" _err");
                    output.push_str(&thr_decl_err_idx.to_string());
                    output.push_str("_");
                    output.push_str(&thr_temp_suffix);
                    output.push_str(";\n");
                }
            }

            // Detect and construct variadic array if needed
            let thr_variadic_arr_var: Option<String> = if let Some(ref thr_vi) = variadic_info {
                let thr_variadic_args: Vec<_> = arg.params.iter().skip(1 + thr_vi.regular_count).collect();
                if !thr_variadic_args.is_empty() {
                    Some(hoist_variadic_args(&thr_vi.elem_type, &thr_variadic_args, &thr_nested_hoisted, thr_vi.regular_count, output, indent, ctx, context)?)
                } else {
                    // Empty variadic - still need an array (with 0 elements)
                    Some(hoist_variadic_args(&thr_vi.elem_type, &[], &thr_nested_hoisted, thr_vi.regular_count, output, indent, ctx, context)?)
                }
            } else {
                None
            };

            // Emit the function call with output pointers
            output.push_str(&indent_str);
            output.push_str("int _status_");
            output.push_str(&thr_temp_suffix);
            output.push_str(" = ");

            // Emit the function name and args (using nested hoisted temps)
            emit_fcall_name_and_args_for_throwing(arg, &temp_var, &thr_temp_suffix, &thr_fd.throw_types, &thr_nested_hoisted, thr_variadic_arr_var.as_deref(), output, ctx, context)?;

            output.push_str(";\n");

            // Emit error checking - propagate if any error occurred
            output.push_str(&indent_str);
            output.push_str("if (_status_");
            output.push_str(&thr_temp_suffix);
            output.push_str(" != 0) {\n");

            // Propagate error based on status value
            // For now, propagate to corresponding error pointer in current function
            for (thr_prop_err_idx, thr_prop_throw_type) in thr_fd.throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = thr_prop_throw_type {
                    // Find matching throw type in current function
                    for (thr_curr_idx, thr_curr_throw) in ctx.current_throw_types.iter().enumerate() {
                        if let ValueType::TCustom(curr_type_name) = thr_curr_throw {
                            if curr_type_name == type_name {
                                output.push_str(&indent_str);
                                output.push_str("    if (_status_");
                                output.push_str(&thr_temp_suffix);
                                output.push_str(" == ");
                                output.push_str(&(thr_prop_err_idx + 1).to_string());
                                output.push_str(") { *_err");
                                output.push_str(&(thr_curr_idx + 1).to_string());
                                output.push_str(" = _err");
                                output.push_str(&thr_prop_err_idx.to_string());
                                output.push_str("_");
                                output.push_str(&thr_temp_suffix);
                                output.push_str("; return ");
                                output.push_str(&(thr_curr_idx + 1).to_string());
                                output.push_str("; }\n");
                                break;
                            }
                        }
                    }
                }
            }

            output.push_str(&indent_str);
            output.push_str("}\n");

            // Emit Array.delete if variadic array was constructed
            if let Some(thr_arr_var) = &thr_variadic_arr_var {
                output.push_str(&indent_str);
                output.push_str(TIL_PREFIX);
                output.push_str("Array_delete(&");
                output.push_str(thr_arr_var);
                output.push_str(");\n");
            }

            // Record in hoisted_exprs map using expression address
            let thr_expr_addr = arg as *const Expr as usize;
            ctx.hoisted_exprs.insert(thr_expr_addr, temp_var.clone());
            hoisted.push(HoistedArg { index: idx, temp_var });
        }
        // Handle non-throwing variadic calls
        else if let Some(ntv_vi) = variadic_info {
            // RECURSIVELY hoist any throwing/variadic calls in this call's arguments first
            let ntv_nested_hoisted: std::collections::HashMap<usize, String> = if arg.params.len() > 1 {
                let ntv_nested_args = &arg.params[1..];
                let ntv_nested_vec = hoist_throwing_args(ntv_nested_args, output, indent, ctx, context)?;
                ntv_nested_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
            } else {
                std::collections::HashMap::new()
            };

            let ntv_temp_var = next_mangled(ctx);

            // Determine return type from function
            let ntv_func_name = get_fcall_func_name(arg)
                .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Cannot determine function name"))?;
            let ntv_fd = get_fcall_func_def(context, arg)
                .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", &format!("Function not found: {}", ntv_func_name)))?;
            let ntv_ret_type = ntv_fd.return_types.first()
                .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Function has no return type"))?;
            let ntv_c_type = til_type_to_c(ntv_ret_type)
                .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))?;

            // Declare temp variable
            output.push_str(&indent_str);
            output.push_str(&ntv_c_type);
            output.push_str(" ");
            output.push_str(&ntv_temp_var);
            output.push_str(";\n");

            // Construct variadic array
            let ntv_variadic_args: Vec<_> = arg.params.iter().skip(1 + ntv_vi.regular_count).collect();
            let ntv_variadic_arr_var = if !ntv_variadic_args.is_empty() {
                hoist_variadic_args(&ntv_vi.elem_type, &ntv_variadic_args, &ntv_nested_hoisted, ntv_vi.regular_count, output, indent, ctx, context)?
            } else {
                hoist_variadic_args(&ntv_vi.elem_type, &[], &ntv_nested_hoisted, ntv_vi.regular_count, output, indent, ctx, context)?
            };

            // Calculate param_by_ref and param_types for proper by-ref handling
            let ntv_param_by_ref: Vec<bool> = arg.params.iter().skip(1).enumerate()
                .map(|(ntv_pi, _)| ntv_fd.args.get(ntv_pi).map(|a| param_needs_by_ref(a)).unwrap_or(false))
                .collect();
            let ntv_param_types: Vec<Option<ValueType>> = arg.params.iter().skip(1).enumerate()
                .map(|(ntv_pi, _)| ntv_fd.args.get(ntv_pi).map(|a| a.value_type.clone()))
                .collect();

            // Emit the function call (non-throwing, so direct assignment)
            output.push_str(&indent_str);
            output.push_str(&ntv_temp_var);
            output.push_str(" = ");

            // Emit function name
            let ntv_fcall_func_name = get_fcall_func_name(arg);
            if let Some(fcall_name) = &ntv_fcall_func_name {
                output.push_str(&til_func_name(fcall_name));
            }
            output.push('(');

            // Emit regular args with proper by-ref handling
            let mut ntv_first = true;
            for (ntv_i, ntv_param) in arg.params.iter().skip(1).take(ntv_vi.regular_count).enumerate() {
                if !ntv_first {
                    output.push_str(", ");
                }
                ntv_first = false;
                let ntv_ptype_val = ntv_param_types.get(ntv_i).and_then(|p| p.as_ref());
                let ntv_by_ref = ntv_param_by_ref.get(ntv_i).copied().unwrap_or(false);
                emit_arg_with_param_type(ntv_param, ntv_i, &ntv_nested_hoisted, ntv_ptype_val, ntv_by_ref, output, ctx, context)?;
            }

            // Emit variadic array pointer
            if !ntv_first {
                output.push_str(", ");
            }
            output.push('&');
            output.push_str(&ntv_variadic_arr_var);

            output.push_str(");\n");

            // Delete the variadic array
            output.push_str(&indent_str);
            output.push_str(TIL_PREFIX);
            output.push_str("Array_delete(&");
            output.push_str(&ntv_variadic_arr_var);
            output.push_str(");\n");

            // Record in hoisted_exprs map using expression address
            let ntv_expr_addr = arg as *const Expr as usize;
            ctx.hoisted_exprs.insert(ntv_expr_addr, ntv_temp_var.clone());
            hoisted.push(HoistedArg { index: idx, temp_var: ntv_temp_var });
        }
        // Handle non-throwing, non-variadic FCalls - still need to recurse into their arguments
        // to find deeply nested variadic/throwing calls (e.g., not(or(false)))
        // and also to hoist Dynamic params (e.g., Vec.contains(v, "bar"))
        else if matches!(arg.node_type, NodeType::FCall) && arg.params.len() > 1 {
            let nested_args = &arg.params[1..];
            // Recurse to hoist any nested throwing/variadic calls
            let _ = hoist_throwing_args(nested_args, output, indent, ctx, context)?;

            // Also hoist Dynamic params for this nested FCall
            if let Some(fd) = get_fcall_func_def(context, arg) {
                let param_types: Vec<Option<ValueType>> = fd.args.iter()
                    .map(|a| Some(a.value_type.clone()))
                    .collect();
                let empty_hoisted = std::collections::HashMap::new();
                let dynamic_hoisted = hoist_for_dynamic_params(nested_args, &param_types, &empty_hoisted, output, indent, ctx, context)?;
                // Record hoisted Dynamic params in hoisted_exprs with & prefix
                // (needed because emit_expr won't know to add & for Dynamic params)
                for h in dynamic_hoisted {
                    if let Some(nested_arg) = nested_args.get(h.index) {
                        let expr_addr = nested_arg as *const Expr as usize;
                        ctx.hoisted_exprs.insert(expr_addr, format!("&{}", h.temp_var));
                    }
                }
            }
        }
        // Handle struct literal arguments (no args, or only named args) - need to hoist their throwing defaults
        // For struct literals like Expr() passed as arguments, their throwing default field values
        // (e.g., params = Vec.new(Expr)) need to be hoisted BEFORE the struct literal is created
        else if matches!(arg.node_type, NodeType::FCall) {
            if let Some(func_name) = get_fcall_func_name(arg) {
                if context.scope_stack.lookup_struct(&func_name).is_some() {
                    // This is a struct literal - hoist its throwing defaults
                    hoist_throwing_expr(arg, output, indent, ctx, context)?;
                }
            }
        }
        // Bug #55 fix: Handle non-FCall arguments (like NamedArg) by recursing via hoist_throwing_expr
        // This ensures throwing calls inside named args are hoisted properly
        else {
            hoist_throwing_expr(arg, output, indent, ctx, context)?;
        }
    }

    Ok(hoisted)
}

/// Hoist non-lvalue args (string literals, function calls) when the param type is Dynamic
/// Returns additional hoisted (arg_idx, temp_var_name) pairs to merge with throwing hoists
fn hoist_for_dynamic_params(
    args: &[Expr],
    param_types: &[Option<ValueType>],
    already_hoisted: &std::collections::HashMap<usize, String>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<Vec<HoistedArg>, String> {
    let mut hoisted = Vec::new();
    let indent_str = "    ".repeat(indent);

    for (idx, arg) in args.iter().enumerate() {
        // Skip if already hoisted by throwing args hoister or by a previous function call
        let arg_addr = arg as *const Expr as usize;
        if already_hoisted.contains_key(&idx) || ctx.hoisted_exprs.contains_key(&arg_addr) {
            continue;
        }

        // Check if param type is Dynamic
        let is_dynamic = param_types.get(idx)
            .and_then(|p| p.as_ref())
            .map(|p| matches!(p, ValueType::TCustom(name) if name == "Dynamic"))
            .unwrap_or(false);

        if !is_dynamic {
            continue;
        }

        // Check if arg is NOT a simple identifier (i.e., needs hoisting)
        let needs_hoisting = match &arg.node_type {
            NodeType::Identifier(_) => {
                // Simple identifier with no params is an lvalue, doesn't need hoisting
                // But identifier with params (type-qualified call like I64.to_str) does need hoisting
                !arg.params.is_empty()
            },
            NodeType::LLiteral(Literal::Str(_)) => true,  // String literals need hoisting
            NodeType::FCall => true,    // Function calls need hoisting
            _ => true,  // Default to hoisting for safety
        };

        if !needs_hoisting {
            continue;
        }

        // Determine the C type of the arg based on what it is
        let c_type: Result<String, String> = match &arg.node_type {
            NodeType::LLiteral(Literal::Str(_)) => Ok(format!("{}Str", TIL_PREFIX)),
            NodeType::LLiteral(Literal::Number(_)) => Ok("int64_t".to_string()),
            NodeType::LLiteral(Literal::List(_)) => Ok("int64_t".to_string()), // TODO: proper list type
            NodeType::Identifier(var_name) if !arg.params.is_empty() => {
                // Could be: enum constructor (Type.Variant), field access (var.field), or method call
                let first_param = arg.params.first()
                    .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Expected param"))?;
                if let NodeType::Identifier(field_or_variant) = &first_param.node_type {
                    // Check if this is an enum constructor
                    if context.scope_stack.lookup_enum(var_name)
                        .map(|e| e.contains_key(field_or_variant))
                        .unwrap_or(false) {
                        // Enum constructor returns the enum type
                        Ok(til_name(var_name))
                    } else if let Some(sym) = context.scope_stack.lookup_symbol(var_name) {
                        // Field access - look up variable's type, then field's type
                        if let ValueType::TCustom(struct_name) = &sym.value_type {
                            let struct_def = context.scope_stack.lookup_struct(struct_name)
                                .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", &format!("Struct not found: {}", struct_name)))?;
                            let mut member_opt: Option<&Declaration> = None;
                            for m in &struct_def.members {
                                if &m.name == field_or_variant {
                                    member_opt = Some(m);
                                    break;
                                }
                            }
                            let member = member_opt.ok_or_else(|| arg.lang_error(&context.path, "ccodegen", &format!("Field not found: {}", field_or_variant)))?;
                            til_type_to_c(&member.value_type)
                                .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))
                        } else {
                            Err(arg.lang_error(&context.path, "ccodegen", &format!("Expected struct type for field access on {}", var_name)))
                        }
                    } else {
                        Err(arg.lang_error(&context.path, "ccodegen", &format!("Symbol not found: {}", var_name)))
                    }
                } else {
                    Err(arg.lang_error(&context.path, "ccodegen", "Expected identifier for field/variant"))
                }
            }
            NodeType::Identifier(type_name) if arg.params.is_empty() => {
                // Struct constructor like Ptr() - identifier with no params
                if context.scope_stack.lookup_struct(type_name).is_some() {
                    Ok(til_name(type_name))
                } else {
                    Err(arg.lang_error(&context.path, "ccodegen", &format!("Unknown type: {}", type_name)))
                }
            }
            NodeType::FCall => {
                // For function calls, try to determine return type
                if let Some(fd) = get_fcall_func_def(context, arg) {
                    if !fd.throw_types.is_empty() {
                        // Throwing call
                        if fd.return_types.is_empty() {
                            return Err(arg.lang_error(&context.path, "ccodegen", "Throwing call has no return type"));
                        }
                        til_type_to_c(fd.return_types.first().unwrap()).map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))
                    } else {
                        // Non-throwing call
                        let ret_type = fd.return_types.first()
                            .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Function has no return type"))?;
                        til_type_to_c(ret_type).map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))
                    }
                } else if let Some(func_name) = get_fcall_func_name(arg) {
                    // get_fcall_func_def returned None - check for constructors
                    if func_name.contains('_') {
                        // Check if this is an enum constructor (Type_Variant)
                        let parts: Vec<&str> = func_name.splitn(2, '_').collect();
                        if parts.len() == 2 {
                            let type_name = parts[0];
                            if context.scope_stack.lookup_enum(type_name)
                                .map(|e| e.contains_key(parts[1]))
                                .unwrap_or(false) {
                                // Enum constructor returns the enum type
                                Ok(til_name(type_name))
                            } else {
                                Err(arg.lang_error(&context.path, "ccodegen", &format!("Unknown enum variant: {}", func_name)))
                            }
                        } else {
                            Err(arg.lang_error(&context.path, "ccodegen", &format!("Unknown function: {}", func_name)))
                        }
                    } else if context.scope_stack.lookup_struct(&func_name).is_some() {
                        // Struct constructor like Ptr() - returns the struct type
                        Ok(til_name(&func_name))
                    } else {
                        Err(arg.lang_error(&context.path, "ccodegen", &format!("Unknown function: {}", func_name)))
                    }
                } else {
                    Err(arg.lang_error(&context.path, "ccodegen", "Cannot determine function name"))
                }
            }
            _ => Err(arg.lang_error(&context.path, "ccodegen", "Cannot determine type for dynamic param")),
        };
        let c_type = c_type?;

        let temp_var = next_mangled(ctx);

        // Emit: til_Str _tmpXX = <expression>;
        output.push_str(&indent_str);
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(&temp_var);
        output.push_str(" = ");
        emit_expr(arg, output, 0, ctx, context)?;
        output.push_str(";\n");

        hoisted.push(HoistedArg { index: idx, temp_var });
    }

    Ok(hoisted)
}

/// Bug #60: Hoist function call results and number literals when passed to by-ref params
/// These are rvalues that can't have & taken directly
fn hoist_for_ref_params(
    args: &[Expr],
    param_by_ref: &[bool],
    already_hoisted: &std::collections::HashMap<usize, String>,
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<Vec<HoistedArg>, String> {
    let mut hoisted = Vec::new();
    let indent_str = "    ".repeat(indent);

    for (idx, arg) in args.iter().enumerate() {
        // Skip if already hoisted
        let arg_addr = arg as *const Expr as usize;
        if already_hoisted.contains_key(&idx) || ctx.hoisted_exprs.contains_key(&arg_addr) {
            continue;
        }

        // Check if param is by-ref
        let is_by_ref = param_by_ref.get(idx).copied().unwrap_or(false);
        if !is_by_ref {
            continue;
        }

        // Check if arg needs hoisting (rvalues that can't have & taken)
        let needs_hoisting = match &arg.node_type {
            NodeType::Identifier(name) => {
                // Simple identifier is lvalue - doesn't need hoisting
                // But type-qualified calls like I64.to_str need hoisting
                if arg.params.is_empty() {
                    false
                } else {
                    // Check if this is a type-qualified method call (not field access)
                    // e.g., Str.len(s) is a method call, but s.len is field access
                    // Also check if it's a function call followed by field access (e.g., get_foo().bar)
                    // Function call results with field access ARE lvalues, don't need hoisting
                    // Also check for UFCS placeholder "_" which is a chained expression
                    if name == "_" {
                        // UFCS placeholder - this is a chained expression like get_foo().bar
                        // The result is an lvalue, doesn't need hoisting
                        false
                    } else {
                        let is_variable = context.scope_stack.lookup_symbol(name).is_some();
                        let is_function = context.scope_stack.lookup_func(name).is_some();
                        // Only needs hoisting if it's not a variable AND not a function call
                        // (i.e., it's a Type.method call like I64.to_str)
                        !is_variable && !is_function
                    }
                }
            },
            NodeType::LLiteral(Literal::Str(_)) => false,  // Compound literal, can use &
            NodeType::LLiteral(Literal::Number(_)) => true,  // Can't take address of integer literal
            NodeType::FCall => {
                // Check if this is an enum or struct constructor - those become compound literals
                // which CAN have & taken directly, so no hoisting needed
                if let Some(first) = arg.params.first() {
                    let combined = crate::rs::parser::get_combined_name(&context.path, first).unwrap_or_default();
                    !context.scope_stack.is_type_constructor(&combined)
                } else {
                    true
                }
            }
            _ => false,
        };

        if !needs_hoisting {
            continue;
        }

        // Determine the C type based on what the arg evaluates to
        let c_type: Result<String, String> = match &arg.node_type {
            NodeType::LLiteral(Literal::Number(_)) => Ok(format!("{}I64", TIL_PREFIX)),
            NodeType::FCall => {
                // Look up the function's return type
                if let Some(fd) = get_fcall_func_def(context, arg) {
                    if let Some(ret_type) = fd.return_types.first() {
                        til_type_to_c(ret_type)
                            .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))
                    } else {
                        Err(arg.lang_error(&context.path, "ccodegen", "Function has no return type"))
                    }
                } else {
                    Err(arg.lang_error(&context.path, "ccodegen", &format!("Cannot find function definition for: {:?}", arg)))
                }
            }
            NodeType::Identifier(var_name) if !arg.params.is_empty() => {
                // Type-qualified method call like I64.to_str(x) - look up return type
                let first_param = arg.params.first()
                    .ok_or_else(|| arg.lang_error(&context.path, "ccodegen", "Expected param"))?;
                if let NodeType::Identifier(method_name) = &first_param.node_type {
                    // Look up Type.method function
                    let func_name = format!("{}.{}", var_name, method_name);
                    if let Some(fd) = context.scope_stack.lookup_func(&func_name) {
                        if let Some(ret_type) = fd.return_types.first() {
                            til_type_to_c(ret_type)
                                .map_err(|e| arg.lang_error(&context.path, "ccodegen", &e))
                        } else {
                            Err(arg.lang_error(&context.path, "ccodegen", &format!("Function {} has no return type", func_name)))
                        }
                    } else {
                        Err(arg.lang_error(&context.path, "ccodegen", &format!("Cannot find function: {}", func_name)))
                    }
                } else {
                    Err(arg.lang_error(&context.path, "ccodegen", "Expected method name"))
                }
            }
            _ => Err(arg.lang_error(&context.path, "ccodegen", "Cannot determine type for ref param hoisting")),
        };
        let c_type = c_type?;

        let temp_var = next_mangled(ctx);

        // Emit: Type _tmpXX = <expression>;
        output.push_str(&indent_str);
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(&temp_var);
        output.push_str(" = ");
        emit_expr(arg, output, 0, ctx, context)?;
        output.push_str(";\n");

        hoisted.push(HoistedArg { index: idx, temp_var });
    }

    Ok(hoisted)
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

    // Declare error vars for Array.new (AllocError) and Array.set (IndexOutOfBoundsError)
    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("AllocError _err_alloc_");
    output.push_str(&err_suffix);
    output.push_str(";\n");

    output.push_str(&indent_str);
    output.push_str(TIL_PREFIX);
    output.push_str("IndexOutOfBoundsError _err_idx_");
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
            let temp_var = next_mangled(ctx);
            output.push_str(&indent_str);
            output.push_str(&c_elem_type);
            output.push_str(" ");
            output.push_str(&temp_var);
            output.push_str(" = ");
            emit_expr(arg, output, 0, ctx, context)?;
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

    // Emit Array.new call with error handling
    // int _status = til_Array_new(&arr, &_err_alloc, &type_temp, &count_temp);
    output.push_str(&indent_str);
    output.push_str("int _arr_status_");
    output.push_str(&err_suffix);
    output.push_str(" = ");
    output.push_str(TIL_PREFIX);
    output.push_str("Array_new(&");
    output.push_str(&arr_var);
    output.push_str(", &_err_alloc_");
    output.push_str(&err_suffix);
    // Bug #60: Type is already const char*, pass by value (no &)
    output.push_str(", ");
    output.push_str(&type_temp);
    output.push_str(", &");
    output.push_str(&count_temp);
    output.push_str(");\n");

    // Emit error check for Array.new (AllocError -> propagate if current function throws it)
    output.push_str(&indent_str);
    output.push_str("if (_arr_status_");
    output.push_str(&err_suffix);
    output.push_str(" != 0) {\n");
    // Propagate AllocError if current function throws it
    for (curr_idx, curr_throw) in ctx.current_throw_types.iter().enumerate() {
        if let ValueType::TCustom(curr_type_name) = curr_throw {
            if curr_type_name == "AllocError" {
                output.push_str(&indent_str);
                output.push_str("    *_err");
                output.push_str(&(curr_idx + 1).to_string());
                output.push_str(" = _err_alloc_");
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

/// Emit a throwing function call's name and arguments for hoisting
/// Outputs: func_name(&temp_var, &err1, &err2, ..., args...)
/// If variadic_arr_var is Some, use that pre-constructed array instead of building one
fn emit_fcall_name_and_args_for_throwing(
    expr: &Expr,
    temp_var: &str,
    temp_suffix: &str,
    throw_types: &[ValueType],
    nested_hoisted: &std::collections::HashMap<usize, String>,  // Hoisted temps for nested args
    variadic_arr_var: Option<&str>,  // Pre-constructed variadic array var
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    if expr.params.is_empty() {
        return Err("emit_fcall_name_and_args_for_throwing: FCall with no params".to_string());
    }

    // Get function name (handles both nested identifiers and precomp'd "Type.method" strings)
    let mut func_name = match get_func_name_string(&expr.params[0]) {
        Some(name) => name,
        None => return Err("emit_fcall_name_and_args_for_throwing: FCall first param not Identifier".to_string()),
    };

    // For lookups, we need the original name with dots
    let orig_func_name = get_til_func_name_string(&expr.params[0])
        .unwrap_or_else(|| func_name.clone());

    // Check if this is a call to a nested (hoisted) function - use mangled name
    if let Some(mangled_name) = ctx.nested_func_names.get(&orig_func_name) {
        func_name = mangled_name.clone();
    }

    // Emit function name (func_name already has underscores for type-qualified calls)
    output.push_str(TIL_PREFIX);
    output.push_str(&func_name);
    output.push_str("(&");
    output.push_str(temp_var);

    // Add error output pointers
    for (idx, _) in throw_types.iter().enumerate() {
        output.push_str(", &_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(temp_suffix);
    }

    // Check if this is a variadic function call
    if let Some(variadic_info) = ctx.func_variadic_args.get(&orig_func_name) {
        let regular_count = variadic_info.regular_count;

        // Bug #60: Get function param info for proper by-ref handling of regular args
        let found_func = get_fcall_func_def(context, expr);
        let param_info: Vec<ParamTypeInfo> = found_func
            .map(|fd| {
                fd.args.iter()
                    .map(|p| ParamTypeInfo { value_type: Some(p.value_type.clone()), by_ref: param_needs_by_ref(p) })
                    .collect()
            })
            .unwrap_or_default();

        // Emit regular args first (skip first param which is function name)
        let args: Vec<_> = expr.params.iter().skip(1).collect();
        for (arg_idx, arg) in args.iter().take(regular_count).enumerate() {
            output.push_str(", ");
            // Bug #60: Use emit_arg_with_param_type for proper by-ref handling
            let (param_type, param_by_ref) = param_info.get(arg_idx)
                .map(|info| (info.value_type.as_ref(), info.by_ref))
                .unwrap_or((None, false));
            emit_arg_with_param_type(arg, arg_idx, nested_hoisted, param_type, param_by_ref, output, ctx, context)?;
        }

        // Emit variadic array pointer
        if let Some(arr_var) = variadic_arr_var {
            output.push_str(", &");
            output.push_str(arr_var);
        } else {
            // No pre-constructed array - this shouldn't happen for throwing calls
            return Err("emit_fcall_name_and_args_for_throwing: variadic call without pre-constructed array".to_string());
        }
    } else {
        // Get function param info for Dynamic casting, mut handling
        let found_func = get_fcall_func_def(context, expr);
        let param_info: Vec<ParamTypeInfo> = found_func
            .map(|fd| {
                fd.args.iter()
                    .map(|p| ParamTypeInfo { value_type: Some(p.value_type.clone()), by_ref: param_needs_by_ref(p) })
                    .collect()
            })
            .unwrap_or_default();

        // Emit remaining arguments (using hoisted temps where available)
        for (arg_idx, arg) in expr.params.iter().skip(1).enumerate() {
            output.push_str(", ");

            // Get expected param type and mutability
            let (param_type, param_by_ref) = param_info.get(arg_idx)
                .map(|info| (info.value_type.as_ref(), info.by_ref))
                .unwrap_or((None, false));

            emit_arg_with_param_type(arg, arg_idx, nested_hoisted, param_type, param_by_ref, output, ctx, context)?;
        }
    }

    output.push_str(")");
    Ok(())
}

/// Emit an argument, using hoisted temp var if available
/// Also handles Type arguments by emitting them as string literals
fn emit_arg_or_hoisted(
    arg: &Expr,
    arg_idx: usize,
    hoisted: &std::collections::HashMap<usize, String>,
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    emit_arg_with_param_type(arg, arg_idx, hoisted, None, false, output, ctx, context)
}

/// Emit an argument with knowledge of expected parameter type and by-ref flag
/// Handles: Type args as string literals, Dynamic args with &, by-ref args with &
fn emit_arg_with_param_type(
    arg: &Expr,
    arg_idx: usize,
    hoisted: &std::collections::HashMap<usize, String>,
    param_type: Option<&ValueType>,
    param_by_ref: bool,
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    if let Some(temp_var) = hoisted.get(&arg_idx) {
        // Hoisted temp var is an lvalue - add & if param is Dynamic or by-ref
        if param_by_ref {
            output.push_str("&");
        } else if let Some(ValueType::TCustom(param_type_name)) = param_type {
            if param_type_name == "Dynamic" {
                output.push_str("&");
            }
        }
        output.push_str(temp_var);
        return Ok(());
    }

    // Also check ctx.hoisted_exprs for expressions hoisted via other mechanisms
    let arg_addr = arg as *const Expr as usize;
    if let Some(temp_expr) = ctx.hoisted_exprs.get(&arg_addr) {
        // hoisted_exprs may store just the temp var name or with & prefix
        // Add & if param is by-ref and temp_expr doesn't already start with &
        if param_by_ref && !temp_expr.starts_with("&") {
            output.push_str("&");
        }
        output.push_str(temp_expr);
        return Ok(());
    }

    // Check if arg is a type identifier - emit as string literal (matches interpreter.rs)
    if let Some(type_name) = get_type_arg_name(arg, context) {
        output.push_str("\"");
        output.push_str(&type_name);
        output.push_str("\"");
        return Ok(());
    }

    // Check if parameter type is Dynamic (including mut Dynamic)
    // Must check BEFORE the general mut check since Dynamic needs casting
    let is_dynamic = matches!(param_type, Some(ValueType::TCustom(name)) if name == "Dynamic");
    if is_dynamic {
        // Check if arg is a simple identifier (can take address directly)
        if let NodeType::Identifier(name) = &arg.node_type {
            if arg.params.is_empty() {
                // Check if this identifier is already a pointer:
                // - mut params are passed as pointers
                // - variadic params are passed as Array pointers
                // - Dynamic params are already void* (no need to take address)
                let is_already_pointer = ctx.current_ref_params.contains(name)
                    || ctx.current_variadic_params.contains_key(name)
                    || context.scope_stack.lookup_symbol(name)
                        .map(|sym| matches!(&sym.value_type, ValueType::TCustom(t) if t == "Dynamic"))
                        .unwrap_or(false);
                if is_already_pointer {
                    // Already a pointer - just cast without &
                    output.push_str("(");
                    output.push_str(TIL_PREFIX);
                    output.push_str("Dynamic*)");
                    output.push_str(&til_name(name));
                } else {
                    // Simple variable - cast to til_Dynamic* (void**) and take address
                    output.push_str("(");
                    output.push_str(TIL_PREFIX);
                    output.push_str("Dynamic*)&");
                    output.push_str(&til_name(name));
                }
                return Ok(());
            } else {
                // Check if this is an enum constructor (Type.Variant) - need temp variable
                if let Some(first_param) = arg.params.first() {
                    if let NodeType::Identifier(field_name) = &first_param.node_type {
                        let combined = format!("{}.{}", name, field_name);
                        if context.scope_stack.is_enum_constructor(&combined) {
                            // Enum constructor passed as Dynamic - need temp variable
                            let c_type = format!("{}{}", TIL_PREFIX, name);
                            let temp_var = next_mangled(ctx);
                            output.push_str("(");
                            output.push_str(TIL_PREFIX);
                            output.push_str("Dynamic*)({ ");
                            output.push_str(&c_type);
                            output.push_str(" ");
                            output.push_str(&temp_var);
                            output.push_str(" = ");
                            emit_expr(arg, output, 0, ctx, context)?;
                            output.push_str("; &");
                            output.push_str(&temp_var);
                            output.push_str("; })");
                            return Ok(());
                        }
                    }
                }
                // Field access like member.name - need (til_Dynamic*)&(var.field)
                // Check if base is a mut param (pointer) or regular variable
                let base_is_pointer = ctx.current_ref_params.contains(name);
                output.push_str("(");
                output.push_str(TIL_PREFIX);
                output.push_str("Dynamic*)&");
                output.push_str(&til_name(name));
                for (i, param) in arg.params.iter().enumerate() {
                    if let NodeType::Identifier(field) = &param.node_type {
                        if base_is_pointer && i == 0 {
                            output.push_str("->");
                        } else {
                            output.push_str(".");
                        }
                        // Field names don't get til_ prefix
                        output.push_str(field);
                    }
                }
                return Ok(());
            }
        }
        // For non-identifier args (literals, compound literals), emit with (til_Dynamic*)&
        // But first check if already hoisted (hoisted_exprs already includes & prefix)
        let dyn_arg_addr = arg as *const Expr as usize;
        if ctx.hoisted_exprs.contains_key(&dyn_arg_addr) {
            // Already hoisted with & prefix - just emit it
            emit_expr(arg, output, 0, ctx, context)?;
        } else if matches!(&arg.node_type, NodeType::LLiteral(_)) {
            // Compound literals are lvalues in C99+, so &((til_Str){...}) works
            output.push_str("(");
            output.push_str(TIL_PREFIX);
            output.push_str("Dynamic*)&");
            emit_expr(arg, output, 0, ctx, context)?;
        } else {
            // Other non-identifier args (function calls, etc.) - emit as-is
            emit_expr(arg, output, 0, ctx, context)?;
        }
        return Ok(());
    }

    // Check if param is mut (but not Dynamic) - emit &arg for pointer
    if param_by_ref {
        if let NodeType::Identifier(name) = &arg.node_type {
            if arg.params.is_empty() {
                // Check if this identifier is already a mut param (already a pointer)
                // or a variadic param (also a pointer) - don't add & again
                let is_already_pointer = ctx.current_ref_params.contains(name)
                    || ctx.current_variadic_params.contains_key(name);
                if is_already_pointer {
                    // Already a pointer - just emit the name
                    output.push_str(&til_name(name));
                } else {
                    // Simple variable - emit &var
                    output.push_str("&");
                    output.push_str(&til_name(name));
                }
                return Ok(());
            } else {
                // Check if this is a struct constant access (Type.CONSTANT) vs field access (var.field)
                if let Some(first_param) = arg.params.first() {
                    if let NodeType::Identifier(field_name) = &first_param.node_type {
                        // Check if 'name' is a struct type and 'field_name' is a constant
                        if let Some(struct_def) = context.scope_stack.lookup_struct(name) {
                            // Check if this field is a constant (in default_values and not mut)
                            if struct_def.default_values.contains_key(field_name) {
                                // Struct constant - emit &til_StructName_constant
                                output.push_str("&");
                                output.push_str(&til_name(name));
                                output.push_str("_");
                                output.push_str(field_name);
                                return Ok(());
                            }
                        }
                        // Bug #60: Check if this is an enum constructor (Type.Variant)
                        // Enum constructors need a temp variable to take address
                        let combined = format!("{}.{}", name, field_name);
                        if context.scope_stack.is_enum_constructor(&combined) {
                            // Get the enum type for C type name
                            let c_type = format!("{}{}", TIL_PREFIX, name);
                            let temp_var = next_mangled(ctx);
                            output.push_str("({ ");
                            output.push_str(&c_type);
                            output.push_str(" ");
                            output.push_str(&temp_var);
                            output.push_str(" = ");
                            emit_expr(arg, output, 0, ctx, context)?;
                            output.push_str("; &");
                            output.push_str(&temp_var);
                            output.push_str("; })");
                            return Ok(());
                        }
                    }
                }
                // Handle UFCS placeholder "_" - chained expression like get_foo().bar
                // The base expression (params[0]) may be an rvalue (function call), so use temp var
                if name == "_" && !arg.params.is_empty() {
                    // Get the type of the full expression for the temp var
                    let c_type = if let Ok(vt) = get_value_type(context, arg) {
                        til_type_to_c(&vt).unwrap_or_else(|_| "int".to_string())
                    } else {
                        "int".to_string()
                    };
                    let temp_var = next_mangled(ctx);
                    output.push_str("({ ");
                    output.push_str(&c_type);
                    output.push_str(" ");
                    output.push_str(&temp_var);
                    output.push_str(" = ");
                    emit_expr(arg, output, 0, ctx, context)?;
                    output.push_str("; &");
                    output.push_str(&temp_var);
                    output.push_str("; })");
                    return Ok(());
                }
                // Field access like self.type_names - need &(self->field) or &(var.field)
                // Check if base is a mut param (pointer) or regular variable
                let base_is_pointer = ctx.current_ref_params.contains(name);
                output.push_str("&");
                output.push_str(&til_name(name));
                for (i, param) in arg.params.iter().enumerate() {
                    if let NodeType::Identifier(field) = &param.node_type {
                        if base_is_pointer && i == 0 {
                            output.push_str("->");
                        } else {
                            output.push_str(".");
                        }
                        output.push_str(field);
                    }
                }
                return Ok(());
            }
        }
        // For non-identifier args that need by-ref passing:
        // - Str literals become compound literals, can use &((til_Str){...})
        // - FCall results are rvalues, use compound literal: &(Type){fcall()}
        // - I64 literals use compound literal: &(til_I64){42}
        if matches!(&arg.node_type, NodeType::LLiteral(Literal::Str(_))) {
            output.push_str("&");
            emit_expr(arg, output, 0, ctx, context)?;
        } else if matches!(&arg.node_type, NodeType::FCall) {
            // Bug #60: FCall result is rvalue, can't take address directly
            // For simple typedefs like I64: use compound literal &(Type){fcall()}
            // For struct types: use GCC statement expression ({ Type _t = fcall(); &_t; })
            if let Some(fd) = get_fcall_func_def(context, arg) {
                if let Some(ret_type) = fd.return_types.first() {
                    if let Ok(c_type) = til_type_to_c(ret_type) {
                        // Check if return type is a simple typedef (I64) vs struct
                        // I64 is the only simple typedef - all others are structs
                        let is_simple_type = matches!(ret_type, ValueType::TCustom(name) if name == "I64");
                        if is_simple_type {
                            output.push_str("&(");
                            output.push_str(&c_type);
                            output.push_str("){");
                            emit_expr(arg, output, 0, ctx, context)?;
                            output.push_str("}");
                        } else {
                            // Struct type - use GCC statement expression
                            let temp_var = next_mangled(ctx);
                            output.push_str("({ ");
                            output.push_str(&c_type);
                            output.push_str(" ");
                            output.push_str(&temp_var);
                            output.push_str(" = ");
                            emit_expr(arg, output, 0, ctx, context)?;
                            output.push_str("; &");
                            output.push_str(&temp_var);
                            output.push_str("; })");
                        }
                    } else {
                        emit_expr(arg, output, 0, ctx, context)?;
                    }
                } else {
                    emit_expr(arg, output, 0, ctx, context)?;
                }
            } else {
                // Bug #60: No function def found - might be enum/struct constructor FCall
                // Use get_value_type to infer the result type
                if let Ok(ValueType::TCustom(type_name)) = get_value_type(context, arg) {
                    // Custom type constructor - use statement expression
                    let c_type = format!("{}{}", TIL_PREFIX, type_name);
                    let temp_var = next_mangled(ctx);
                    output.push_str("({ ");
                    output.push_str(&c_type);
                    output.push_str(" ");
                    output.push_str(&temp_var);
                    output.push_str(" = ");
                    emit_expr(arg, output, 0, ctx, context)?;
                    output.push_str("; &");
                    output.push_str(&temp_var);
                    output.push_str("; })");
                } else {
                    emit_expr(arg, output, 0, ctx, context)?;
                }
            }
        } else if matches!(&arg.node_type, NodeType::LLiteral(Literal::Number(_))) {
            // Bug #60: Number literal, use compound literal: &(til_I64){42}
            output.push_str("&(");
            output.push_str(TIL_PREFIX);
            output.push_str("I64){");
            emit_expr(arg, output, 0, ctx, context)?;
            output.push_str("}");
        } else {
            emit_expr(arg, output, 0, ctx, context)?;
        }
        return Ok(());
    }

    // Check if arg is a variadic param (which is til_Array*) but expected param is NOT mut
    // In this case we need to dereference: (*til_args) to get til_Array by value
    if let NodeType::Identifier(name) = &arg.node_type {
        if arg.params.is_empty() && ctx.current_variadic_params.contains_key(name) {
            output.push_str("(*");
            output.push_str(&til_name(name));
            output.push_str(")");
            return Ok(());
        }
    }

    emit_expr(arg, output, 0, ctx, context)
}

// Emit C code from AST (multi-pass architecture)
pub fn emit(ast: &Expr, context: &mut Context) -> Result<String, String> {
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
            collect_nested_func_info(child, &mut ctx, None)?;
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
                emit_func_prototype(child, &mut output)?;
            }
        }
    }
    // 2b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_prototypes(child, &mut output)?;
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

    // 5c: hoisted nested function definitions
    // These were collected during emit_func_declaration when encountering nested functions
    // (prototypes were already emitted in Pass 2c)
    if !ctx.hoisted_functions.is_empty() {
        output.push_str("\n// Hoisted nested function definitions\n");
        for func_code in &ctx.hoisted_functions {
            output.push_str(func_code);
        }
    }

    // Main function
    output.push_str("int main(int argc, char** argv) {\n");

    // Clear hoisted_exprs to avoid cross-contamination from function passes
    ctx.hoisted_exprs.clear();

    // Re-populate declared_vars with global declarations (functions clear declared_vars)
    // This ensures global declarations emit only assignments in main(), not redeclarations
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_global_declaration(child) {
                if let NodeType::Declaration(decl) = &child.node_type {
                    ctx.declared_vars.insert(til_name(&decl.name));
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
        // Check if main has variadic args by looking up the function
        // Variadic params have ValueType::TMulti as their type
        let main_has_variadic = match context.scope_stack.lookup_func("main") {
            Some(fd) => {
                let mut has_multi = false;
                for fd_arg in &fd.args {
                    if matches!(&fd_arg.value_type, ValueType::TMulti(_)) {
                        has_multi = true;
                        break;
                    }
                }
                has_multi
            },
            None => false,
        };

        if main_has_variadic {
            // Convert argc/argv to til_Array and pass to til_main
            // Skip argv[0] (exe path) to match interpreter behavior
            output.push_str("    til_Array _main_args;\n");
            output.push_str("    til_AllocError _main_args_err;\n");
            output.push_str("    til_Array_new(&_main_args, &_main_args_err, \"Str\", &(til_I64){argc - 1});\n");
            output.push_str("    for (int i = 1; i < argc; i++) {\n");
            output.push_str("        til_Str _arg = {(til_I64)argv[i], strlen(argv[i])};\n");
            output.push_str("        til_IndexOutOfBoundsError _set_err;\n");
            output.push_str("        til_Array_set(&_set_err, &_main_args, &(til_I64){i - 1}, &_arg);\n");
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

// Check if an expression is a function call that uses out-params (i.e., the function throws)
// Such calls cannot be used inline in struct initializers - they need separate statements
fn is_throwing_fcall(expr: &Expr, context: &Context) -> bool {
    if let NodeType::FCall = &expr.node_type {
        if let Some(fd) = get_fcall_func_def(context, expr) {
            return !fd.throw_types.is_empty();
        }
    }
    false
}

// Emit a top-level constant declaration at file scope
fn emit_constant_declaration(expr: &Expr, output: &mut String, ctx: &mut CodegenContext, context: &Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            // Bug #35: Use unique name for "_" declarations to avoid C redefinition errors
            let var_name = if decl.name == "_" {
                next_mangled(ctx)
            } else {
                til_name(&decl.name)
            };

            // Handle literal constants (numbers, strings)
            if let NodeType::LLiteral(lit) = &expr.params[0].node_type {
                let has_str = context.scope_stack.lookup_struct("Str").is_some();
                let c_type = match lit {
                    Literal::Number(_) => format!("{}I64", TIL_PREFIX),
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
            let var_name = if decl.name == "_" {
                next_mangled(ctx)
            } else {
                til_name(&decl.name)
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
fn collect_nested_func_info(expr: &Expr, ctx: &mut CodegenContext, parent_func_name: Option<&str>) -> Result<(), String> {
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
                        emit_func_signature(&til_name(&mangled_name), func_def, &mut proto)?;
                        proto.push_str(";\n");
                        ctx.hoisted_prototypes.push(proto);

                        // Recursively check for nested functions within this nested function
                        let new_parent = mangled_name.clone();
                        for body_expr in &func_def.body {
                            collect_nested_func_info(body_expr, ctx, Some(&new_parent))?;
                        }
                    } else {
                        // Top-level function - scan its body for nested functions
                        for body_expr in &func_def.body {
                            collect_nested_func_info(body_expr, ctx, Some(&decl.name))?;
                        }
                    }
                }
            }
        },
        NodeType::Body => {
            for child in &expr.params {
                collect_nested_func_info(child, ctx, parent_func_name)?;
            }
        },
        NodeType::If => {
            // Check then and else branches (params[0] = condition, params[1] = then, params[2] = else)
            if expr.params.len() > 1 {
                collect_nested_func_info(&expr.params[1], ctx, parent_func_name)?;
            }
            if expr.params.len() > 2 {
                collect_nested_func_info(&expr.params[2], ctx, parent_func_name)?;
            }
        },
        NodeType::While => {
            // Check loop body (params[0] = condition, params[1] = body)
            if expr.params.len() > 1 {
                collect_nested_func_info(&expr.params[1], ctx, parent_func_name)?;
            }
        },
        NodeType::Switch => {
            // Check all case bodies (params[0] = value, rest are cases)
            for i in 1..expr.params.len() {
                collect_nested_func_info(&expr.params[i], ctx, parent_func_name)?;
            }
        },
        _ => {
            // Recursively check all params for other node types
            for child in &expr.params {
                collect_nested_func_info(child, ctx, parent_func_name)?;
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
        output.push_str("    if (strcmp((char*)type_name->c_string, \"");
        output.push_str(type_name);
        output.push_str("\") == 0) return ");
        output.push_str(TIL_PREFIX);
        output.push_str("size_of_");
        output.push_str(type_name);
        output.push_str(";\n");
    }

    output.push_str("    fprintf(stderr, \"size_of: unknown type %s\\n\", (char*)type_name->c_string);\n");
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

    // 3. Emit wrapper struct: struct Color { Color_Tag tag; Color_Payload payload; };
    // Note: typedef is already forward-declared, so we just define the struct body
    output.push_str("struct ");
    output.push_str(enum_name);
    output.push_str(" {\n");
    output.push_str("    ");
    output.push_str(enum_name);
    output.push_str("_Tag tag;\n");
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
// Takes a pointer because enum_to_str(e: Dynamic) passes by reference
// For simple enums: til_Str til_EnumName_to_str(til_EnumName* e)
// For enums with payloads: til_Str til_EnumName_to_str(til_EnumName* e)
fn emit_enum_to_str_function(enum_name: &str, enum_def: &SEnumDef, output: &mut String) {
    let has_payloads = enum_has_payloads(enum_def);
    let mut variants: Vec<_> = enum_def.variants.iter().map(|v| &v.name).collect();
    variants.sort();

    // Function signature - takes pointer since Dynamic params are passed by reference
    output.push_str("static inline til_Str ");
    output.push_str(enum_name);
    output.push_str("_to_str(");
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
        output.push_str(": return (til_Str){(til_I64)\"");
        output.push_str(&full_name);
        output.push_str("\", ");
        output.push_str(&full_name.len().to_string());
        output.push_str("};\n");
    }

    // Default case (shouldn't happen but good for safety)
    let unknown_name = format!("{}.?", original_name);
    output.push_str("    }\n    return (til_Str){(til_I64)\"");
    output.push_str(&unknown_name);
    output.push_str("\", ");
    output.push_str(&unknown_name.len().to_string());
    output.push_str("};\n}\n\n");
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
fn emit_struct_func_prototypes(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::StructDef(struct_def) = &expr.params[0].node_type {
                let struct_name = til_name(&decl.name);
                for member in &struct_def.members {
                    // Check if default_value is a function definition
                    if let Some(func_expr) = struct_def.default_values.get(&member.name) {
                        if let NodeType::FuncDef(func_def) = &func_expr.node_type {
                            let mangled_name = format!("{}_{}", struct_name, member.name);
                            emit_func_signature(&mangled_name, func_def, output)?;
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

    // Clear declared_vars and hoisted_struct_defaults for new function scope
    ctx.declared_vars.clear();
    ctx.hoisted_struct_defaults.clear();

    let mangled_name = format!("{}_{}", struct_name, member.name);

    // Save and set current function name for deterministic temp naming (Bug #42 fix)
    let prev_function_name = ctx.current_function_name.clone();
    let prev_mangling_counter = ctx.mangling_counter;
    ctx.current_function_name = mangled_name.clone();
    ctx.mangling_counter = 0;

    emit_func_signature(&mangled_name, func_def, output)?;
    output.push_str(" {\n");

    // Emit function body with catch pattern detection
    emit_stmts(&func_def.body, output, 1, ctx, context)?;

    // For throwing void functions, add implicit return 0 at end
    if !func_def.throw_types.is_empty() && func_def.return_types.is_empty() {
        output.push_str("    return 0;\n");
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
fn emit_func_signature(func_name: &str, func_def: &SFuncDef, output: &mut String) -> Result<(), String> {
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
            // Variadic args are passed as til_Array*
            output.push_str(TIL_PREFIX);
            output.push_str("Array* ");
            output.push_str(TIL_PREFIX);
            output.push_str(&func_def_arg.name);
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
            output.push_str(TIL_PREFIX);
            output.push_str(&func_def_arg.name);
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
fn emit_func_prototype(expr: &Expr, output: &mut String) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::FuncDef(func_def) = &expr.params[0].node_type {
                // Skip external functions (ext_proc/ext_func) - they're just declarations
                if func_def.is_ext() {
                    return Ok(());
                }

                let func_name = til_name(&decl.name);
                emit_func_signature(&func_name, func_def, output)?;
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

                // Clear declared_vars and hoisted_struct_defaults for new function scope
                ctx.declared_vars.clear();
                ctx.hoisted_struct_defaults.clear();

                let func_name = til_name(&decl.name);

                // Save and set current function name for nested function mangling
                let prev_function_name = ctx.current_function_name.clone();
                let prev_mangling_counter = ctx.mangling_counter;
                ctx.current_function_name = decl.name.clone();
                ctx.mangling_counter = 0;  // Reset counter per-function for determinism

                emit_func_signature(&func_name, func_def, output)?;
                output.push_str(" {\n");

                // Emit function body with catch pattern detection
                emit_stmts(&func_def.body, output, 1, ctx, context)?;

                // For throwing void functions, add implicit return 0 at end
                if !func_def.throw_types.is_empty() && func_def.return_types.is_empty() {
                    output.push_str("    return 0;\n");
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
    // Check if this expression has been hoisted (for nested variadic/throwing calls)
    let expr_addr = expr as *const Expr as usize;
    if let Some(temp_var) = ctx.hoisted_exprs.get(&expr_addr) {
        output.push_str(temp_var);
        return Ok(());
    }

    match &expr.node_type {
        NodeType::Body => emit_body(expr, output, indent, ctx, context),
        NodeType::FCall => emit_fcall(expr, output, indent, ctx, context),
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
                    if context.scope_stack.lookup_struct(name).is_some() {
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
            if is_ref_param && !expr.params.is_empty() {
                // Ref param with field access: til_self->field1.field2.field3
                // First field uses -> (self is a pointer), rest use . (struct values)
                output.push_str(&til_name(name));
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
                output.push_str(&til_name(name));
                output.push_str(")");
            } else {
                // Regular identifier or field access
                output.push_str(&til_name(name));
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
        NodeType::Switch => emit_switch(expr, output, indent, ctx, context),
        NodeType::DefaultCase => Err("ccodegen: DefaultCase should be handled inside emit_switch".to_string()),
        NodeType::Range => Err("ccodegen: Range not yet supported".to_string()),
        NodeType::Pattern(_) => Err("ccodegen: Pattern should be handled inside emit_switch".to_string()),
        NodeType::NamedArg(_) => Err(expr.error(&context.path, "ccodegen", "NamedArg should be reordered before reaching emit_expr")),
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

            let catch_body = &catch_block.params[2];
            let decls = collect_declarations_in_body(catch_body, context);
            for decl in decls {
                let c_var_name = til_name(&decl.name);
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
                            output.push_str(":\n");

                            // Bind error variable
                            if let NodeType::Identifier(err_var_name) = &stmt.params[0].node_type {
                                let inner_indent = "    ".repeat(indent + 1);
                                output.push_str(&inner_indent);
                                output.push_str(&til_name(err_type_name));
                                output.push_str(" ");
                                output.push_str(&til_name(err_var_name));
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
            NodeType::FCall => (Some(stmt), None, None),
            NodeType::Declaration(decl) => {
                // Check if declaration has an FCall as initializer
                if !stmt.params.is_empty() {
                    if let NodeType::FCall = stmt.params[0].node_type {
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
                    if let NodeType::FCall = stmt.params[0].node_type {
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
#[allow(dead_code)]
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
    let param_by_ref: Vec<bool> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| param_needs_by_ref(a)).unwrap_or(false))
            .collect()
    };
    let param_types: Vec<Option<ValueType>> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| a.value_type.clone()))
            .collect()
    };

    // Hoist any throwing function calls in arguments BEFORE constructing variadic array
    let hoisted: std::collections::HashMap<usize, String> = if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
    } else {
        std::collections::HashMap::new()
    };

    // Construct variadic array
    let variadic_args: Vec<_> = fcall.params.iter().skip(1 + regular_count).collect();
    let variadic_arr_var = hoist_variadic_args(elem_type, &variadic_args, &hoisted, regular_count, output, indent, ctx, context)?;

    // Determine return type if we need to declare a variable
    let ret_type = if decl_name.is_some() || assign_name.is_some() {
        get_fcall_func_def(context, fcall)
            .and_then(|fd| fd.return_types.first().cloned())
            .map(|t| til_type_to_c(&t).unwrap_or("int".to_string()))
            .unwrap_or("int".to_string())
    } else {
        "int".to_string()
    };

    // For declarations: declare the variable (skip for "_" - Bug #35)
    if let Some(var_name) = decl_name {
        if var_name == "_" {
            // Bug #35: For underscore, just call the function (discard result)
            output.push_str(&indent_str);
            output.push_str(TIL_PREFIX);
            output.push_str(&func_name.replace('.', "_"));
            output.push_str("(");

            let args: Vec<_> = fcall.params.iter().skip(1).collect();
            for (i, arg) in args.iter().take(regular_count).enumerate() {
                if i > 0 {
                    output.push_str(", ");
                }
                let param_type = param_types.get(i).and_then(|p| p.as_ref());
                let by_ref = param_by_ref.get(i).copied().unwrap_or(false);
                emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
            }

            if regular_count > 0 {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(&variadic_arr_var);
            output.push_str(");\n");
        } else {
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&til_name(var_name));
            output.push_str(" = ");

            // Emit function call
            output.push_str(TIL_PREFIX);
            output.push_str(&func_name.replace('.', "_"));
            output.push_str("(");

            // Emit regular args first
            let args: Vec<_> = fcall.params.iter().skip(1).collect();
            for (i, arg) in args.iter().take(regular_count).enumerate() {
                if i > 0 {
                    output.push_str(", ");
                }
                let param_type = param_types.get(i).and_then(|p| p.as_ref());
                let by_ref = param_by_ref.get(i).copied().unwrap_or(false);
                emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
            }

            // Emit variadic array pointer
            if regular_count > 0 {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(&variadic_arr_var);

            output.push_str(");\n");

            // Add variable to scope
            if let Some(fd) = get_fcall_func_def(context, fcall) {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
            ctx.declared_vars.insert(til_name(var_name));
        }
    } else if let Some(var_name) = assign_name {
        // Assignment
        output.push_str(&indent_str);
        // Check if assignment target is a field access on a mut param (self.field)
        // If so, emit with -> instead of .
        if let Some(dot_pos) = var_name.find('.') {
            let base = &var_name[..dot_pos];
            let rest = &var_name[dot_pos + 1..];
            if ctx.current_ref_params.contains(base) {
                // Mut param field access: til_self->field
                output.push_str(&til_name(base));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_name(var_name));
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_self = value
            output.push_str("*");
            output.push_str(&til_name(var_name));
        } else {
            output.push_str(&til_name(var_name));
        }
        output.push_str(" = ");

        // Emit function call
        output.push_str(TIL_PREFIX);
        output.push_str(&func_name.replace('.', "_"));
        output.push_str("(");

        // Emit regular args first
        let args: Vec<_> = fcall.params.iter().skip(1).collect();
        for (i, arg) in args.iter().take(regular_count).enumerate() {
            if i > 0 {
                output.push_str(", ");
            }
            let param_type = param_types.get(i).and_then(|p| p.as_ref());
            let by_ref = param_by_ref.get(i).copied().unwrap_or(false);
            emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
        }

        // Emit variadic array pointer
        if regular_count > 0 {
            output.push_str(", ");
        }
        output.push_str("&");
        output.push_str(&variadic_arr_var);

        output.push_str(");\n");
    } else {
        // Standalone variadic call (no return value used)
        output.push_str(&indent_str);
        output.push_str(TIL_PREFIX);
        output.push_str(&func_name.replace('.', "_"));
        output.push_str("(");

        // Emit regular args first
        let args: Vec<_> = fcall.params.iter().skip(1).collect();
        for (i, arg) in args.iter().take(regular_count).enumerate() {
            if i > 0 {
                output.push_str(", ");
            }
            let param_type = param_types.get(i).and_then(|p| p.as_ref());
            let by_ref = param_by_ref.get(i).copied().unwrap_or(false);
            emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
        }

        // Emit variadic array pointer
        if regular_count > 0 {
            output.push_str(", ");
        }
        output.push_str("&");
        output.push_str(&variadic_arr_var);

        output.push_str(");\n");
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

    // Calculate param_types early for Dynamic hoisting
    let param_types: Vec<Option<ValueType>> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| a.value_type.clone()))
            .collect()
    };
    // Calculate param_by_ref for pointer passing
    let param_by_ref: Vec<bool> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| param_needs_by_ref(a)).unwrap_or(false))
            .collect()
    };

    // Hoist any throwing function calls in arguments BEFORE emitting this call
    let mut hoisted: std::collections::HashMap<usize, String> = if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hoist non-lvalue args (string literals, function calls) when param type is Dynamic
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &hoisted, output, indent, ctx, context)?;
        for h in dynamic_hoisted {
            hoisted.insert(h.index, h.temp_var);
        }
    }

    // Hoist struct-returning FCall args when param is by-ref (can't use compound literal for structs)
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let ref_hoisted = hoist_for_ref_params(args, &param_by_ref, &hoisted, output, indent, ctx, context)?;
        for h in ref_hoisted {
            hoisted.insert(h.index, h.temp_var);
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
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&til_name(var_name));
            output.push_str(";\n");
            ctx.declared_vars.insert(til_name(var_name));
            // Add to scope_stack for type resolution
            if let Some(fd) = func_def_opt.as_ref() {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
        }
    }

    // Declare error structs for each throw type
    // Check if struct is empty to avoid {0} warning
    for (idx, throw_type) in throw_types.iter().enumerate() {
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

    // Check if this is a variadic function call and construct array BEFORE the call
    let variadic_info = detect_variadic_fcall(fcall, ctx);
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        let variadic_args: Vec<_> = fcall.params.iter().skip(1 + vi.regular_count).collect();
        Some(hoist_variadic_args(&vi.elem_type, &variadic_args, &hoisted, vi.regular_count, output, indent, ctx, context)?)
    } else {
        None
    };

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int _status_");
    output.push_str(&temp_suffix.to_string());
    output.push_str(" = ");
    output.push_str(&til_func_name(&func_name));
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix.to_string());
    }

    // Then: error pointers
    for idx in 0..throw_types.len() {
        if needs_ret || idx > 0 {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix.to_string());
    }

    // Emit arguments - handle variadic separately from regular args
    if let Some(ref vi) = variadic_info {
        // Variadic call: emit regular args first, then variadic array pointer
        for (vi_arg_idx, vi_arg) in fcall.params.iter().skip(1).take(vi.regular_count).enumerate() {
            if needs_ret || !throw_types.is_empty() || vi_arg_idx > 0 {
                output.push_str(", ");
            }
            let vi_param_type = param_types.get(vi_arg_idx).and_then(|p| p.as_ref());
            let vi_by_ref = param_by_ref.get(vi_arg_idx).copied().unwrap_or(false);
            emit_arg_with_param_type(vi_arg, vi_arg_idx, &hoisted, vi_param_type, vi_by_ref, output, ctx, context)?;
        }

        // Emit variadic array pointer
        if let Some(ref arr_var) = variadic_arr_var {
            if needs_ret || !throw_types.is_empty() || vi.regular_count > 0 {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(arr_var);
        }
    } else {
        // Non-variadic: emit all args directly
        let mut nv_args_started = false;
        for (nv_arg_idx, nv_arg) in fcall.params.iter().skip(1).enumerate() {
            if needs_ret || !throw_types.is_empty() || nv_args_started {
                output.push_str(", ");
            }
            // Get parameter type and mutability for this argument
            let nv_param_type = param_types.get(nv_arg_idx).and_then(|p| p.as_ref());
            let nv_by_ref = param_by_ref.get(nv_arg_idx).copied().unwrap_or(false);
            emit_arg_with_param_type(nv_arg, nv_arg_idx, &hoisted, nv_param_type, nv_by_ref, output, ctx, context)?;
            nv_args_started = true;
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
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            // Declaration: assign to newly declared variable (declared before if block)
            let inner_indent = "    ".repeat(indent + 1);
            output.push_str(&inner_indent);
            output.push_str(&til_name(var_name));
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
                // Mut param field access: til_self->field
                output.push_str(&til_name(base));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_name(var_name));
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_var = value
            output.push_str("*");
            output.push_str(&til_name(var_name));
        } else {
            output.push_str(&til_name(var_name));
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
                        output.push_str(" = _err");
                        output.push_str(&idx.to_string());
                        output.push_str("_");
                        output.push_str(&temp_suffix.to_string());
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

    // Calculate param_types early for Dynamic hoisting
    let param_types: Vec<Option<ValueType>> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| a.value_type.clone()))
            .collect()
    };
    // Calculate param_by_ref for pointer passing
    let param_by_ref: Vec<bool> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| param_needs_by_ref(a)).unwrap_or(false))
            .collect()
    };

    // Hoist any throwing function calls in arguments BEFORE emitting this call
    let mut hoisted: std::collections::HashMap<usize, String> = if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hoist non-lvalue args (string literals, function calls) when param type is Dynamic
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &hoisted, output, indent, ctx, context)?;
        for h in dynamic_hoisted {
            hoisted.insert(h.index, h.temp_var);
        }
    }

    // Hoist struct-returning FCall args when param is by-ref
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let ref_hoisted = hoist_for_ref_params(args, &param_by_ref, &hoisted, output, indent, ctx, context)?;
        for h in ref_hoisted {
            hoisted.insert(h.index, h.temp_var);
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
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&til_name(var_name));
            output.push_str(";\n");
            ctx.declared_vars.insert(til_name(var_name));
            // Add to scope_stack for type resolution
            if let Some(fd) = func_def_opt.as_ref() {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
        }
    }

    // Declare error structs for each throw type of the called function
    for (idx, throw_type) in throw_types.iter().enumerate() {
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

    // Check if this is a variadic function call and construct array BEFORE the call
    let variadic_info = detect_variadic_fcall(fcall, ctx);
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        let variadic_args: Vec<_> = fcall.params.iter().skip(1 + vi.regular_count).collect();
        Some(hoist_variadic_args(&vi.elem_type, &variadic_args, &hoisted, vi.regular_count, output, indent, ctx, context)?)
    } else {
        None
    };

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int _status_");
    output.push_str(&temp_suffix);
    output.push_str(" = ");
    output.push_str(&til_func_name(&func_name));
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix);
    }

    // Then: error pointers
    for idx in 0..throw_types.len() {
        if needs_ret || idx > 0 {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix);
    }

    // Emit arguments - handle variadic separately from regular args
    if let Some(ref vi) = variadic_info {
        // Variadic call: emit regular args first, then variadic array pointer
        for (arg_idx, arg) in fcall.params.iter().skip(1).take(vi.regular_count).enumerate() {
            if needs_ret || !throw_types.is_empty() || arg_idx > 0 {
                output.push_str(", ");
            }
            let param_type = param_types.get(arg_idx).and_then(|p| p.as_ref());
            let by_ref = param_by_ref.get(arg_idx).copied().unwrap_or(false);
            emit_arg_with_param_type(arg, arg_idx, &hoisted, param_type, by_ref, output, ctx, context)?;
        }

        // Emit variadic array pointer
        if let Some(ref arr_var) = variadic_arr_var {
            if needs_ret || !throw_types.is_empty() || vi.regular_count > 0 {
                output.push_str(", ");
            }
            output.push_str("&");
            output.push_str(arr_var);
        }
    } else {
        // Non-variadic: emit all args directly
        let mut args_started = false;
        for (arg_idx, arg) in fcall.params.iter().skip(1).enumerate() {
            if needs_ret || !throw_types.is_empty() || args_started {
                output.push_str(", ");
            }
            // Get parameter type and mutability for this argument
            let param_type = param_types.get(arg_idx).and_then(|p| p.as_ref());
            let by_ref = param_by_ref.get(arg_idx).copied().unwrap_or(false);
            emit_arg_with_param_type(arg, arg_idx, &hoisted, param_type, by_ref, output, ctx, context)?;
            args_started = true;
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
                output.push_str(&indent_str);
                output.push_str("if (_status_");
                output.push_str(&temp_suffix);
                output.push_str(" == ");
                output.push_str(&(called_idx + 1).to_string());
                output.push_str(") { *_err");
                output.push_str(&(cur_idx + 1).to_string());
                output.push_str(" = _err");
                output.push_str(&called_idx.to_string());
                output.push_str("_");
                output.push_str(&temp_suffix);
                output.push_str("; return ");
                output.push_str(&(cur_idx + 1).to_string());
                output.push_str("; }\n");
            }
        }
    }

    // Success case: assign return value to target variable if needed
    // Skip for underscore _ which is just a discard
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            output.push_str(&indent_str);
            output.push_str(&til_name(var_name));
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
                // Mut param field access: til_self->field
                output.push_str(&til_name(base));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_name(var_name));
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_var = value
            output.push_str("*");
            output.push_str(&til_name(var_name));
        } else {
            output.push_str(&til_name(var_name));
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

    // Calculate param_types and param_by_ref
    let param_types: Vec<Option<ValueType>> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| a.value_type.clone()))
            .collect()
    };
    let param_by_ref: Vec<bool> = {
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def_opt.as_ref().and_then(|fd| fd.args.get(i)).map(|a| param_needs_by_ref(a)).unwrap_or(false))
            .collect()
    };

    // Hoist any throwing function calls in arguments BEFORE emitting this call
    let mut hoisted: std::collections::HashMap<usize, String> = if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hoist non-lvalue args when param type is Dynamic
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &hoisted, output, indent, ctx, context)?;
        for h in dynamic_hoisted {
            hoisted.insert(h.index, h.temp_var);
        }
    }

    // Hoist struct-returning FCall args when param is by-ref
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let ref_hoisted = hoist_for_ref_params(args, &param_by_ref, &hoisted, output, indent, ctx, context)?;
        for h in ref_hoisted {
            hoisted.insert(h.index, h.temp_var);
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
            output.push_str(&indent_str);
            output.push_str(&ret_type);
            output.push_str(" ");
            output.push_str(&til_name(var_name));
            output.push_str(";\n");
            ctx.declared_vars.insert(til_name(var_name));
            if let Some(fd) = func_def_opt.as_ref() {
                if let Some(first_type) = fd.return_types.first() {
                    context.scope_stack.declare_symbol(
                        var_name.to_string(),
                        SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false, is_comptime_const: false }
                    );
                }
            }
        }
    }

    // Declare error structs for each throw type of the called function
    for (idx, throw_type) in throw_types.iter().enumerate() {
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

    // Check for variadic function call
    let variadic_info = detect_variadic_fcall(fcall, ctx);
    let variadic_arr_var: Option<String> = if let Some(ref vi) = variadic_info {
        let variadic_args: Vec<_> = fcall.params.iter().skip(1 + vi.regular_count).collect();
        Some(hoist_variadic_args(&vi.elem_type, &variadic_args, &hoisted, vi.regular_count, output, indent, ctx, context)?)
    } else {
        None
    };

    // Generate the function call with output parameters
    output.push_str(&indent_str);
    output.push_str("int _status_");
    output.push_str(&temp_suffix);
    output.push_str(" = ");
    output.push_str(&til_func_name(&func_name));
    output.push_str("(");

    // First: return value pointer (if function returns something)
    if needs_ret {
        output.push_str("&_ret_");
        output.push_str(&temp_suffix);
    }

    // Then: error pointers
    for idx in 0..throw_types.len() {
        if needs_ret || idx > 0 {
            output.push_str(", ");
        }
        output.push_str("&_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(&temp_suffix);
    }

    // Emit arguments
    let mut args_started = false;
    let regular_arg_count = variadic_info.as_ref().map(|vi| vi.regular_count).unwrap_or(usize::MAX);
    for (arg_idx, arg) in fcall.params.iter().skip(1).enumerate() {
        if arg_idx >= regular_arg_count {
            break;
        }
        if needs_ret || !throw_types.is_empty() || args_started {
            output.push_str(", ");
        }
        let param_type = param_types.get(arg_idx).and_then(|p| p.as_ref());
        let by_ref = param_by_ref.get(arg_idx).copied().unwrap_or(false);
        emit_arg_with_param_type(arg, arg_idx, &hoisted, param_type, by_ref, output, ctx, context)?;
        args_started = true;
    }

    // Add variadic array if present
    if let Some(arr_var) = &variadic_arr_var {
        if needs_ret || !throw_types.is_empty() || args_started {
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
            // Check if there's a local catch for this error type
            if let Some(catch_info) = ctx.local_catch_labels.get(type_name) {
                // Jump to local catch: copy error to temp var, then goto label
                output.push_str(&indent_str);
                output.push_str("if (_status_");
                output.push_str(&temp_suffix);
                output.push_str(" == ");
                output.push_str(&(err_idx + 1).to_string());
                output.push_str(") { ");
                output.push_str(&catch_info.temp_var);
                output.push_str(" = _err");
                output.push_str(&err_idx.to_string());
                output.push_str("_");
                output.push_str(&temp_suffix);
                output.push_str("; goto ");
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
                // Propagate to caller: copy error to output param and return
                output.push_str(&indent_str);
                output.push_str("if (_status_");
                output.push_str(&temp_suffix);
                output.push_str(" == ");
                output.push_str(&(err_idx + 1).to_string());
                output.push_str(") { *_err");
                output.push_str(&(prop_idx + 1).to_string());
                output.push_str(" = _err");
                output.push_str(&err_idx.to_string());
                output.push_str("_");
                output.push_str(&temp_suffix);
                output.push_str("; return ");
                output.push_str(&(prop_idx + 1).to_string());
                output.push_str("; }\n");
                }
            }
        }
    }

    // Success case: assign return value to target variable if needed
    // This runs unconditionally after error checks - if we get here, status was 0
    // Skip for underscore _ which is just a discard
    if let Some(var_name) = decl_name {
        if var_name != "_" {
            output.push_str(&indent_str);
            output.push_str(&til_name(var_name));
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
                // Mut param field access: til_self->field
                output.push_str(&til_name(base));
                output.push_str("->");
                output.push_str(rest);
            } else {
                output.push_str(&til_name(var_name));
            }
        } else if ctx.current_ref_params.contains(var_name) {
            // Direct assignment to mut param: *til_var = value
            output.push_str("*");
            output.push_str(&til_name(var_name));
        } else {
            output.push_str(&til_name(var_name));
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
                emit_func_signature(&til_name(&mangled_name), func_def, &mut proto_output)?;
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
                emit_func_signature(&til_name(&mangled_name), func_def, &mut func_output)?;
                func_output.push_str(" {\n");
                emit_stmts(&func_def.body, &mut func_output, 1, ctx, context)?;
                if !func_def.throw_types.is_empty() && func_def.return_types.is_empty() {
                    func_output.push_str("    return 0;\n");
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

    let indent_str = "    ".repeat(indent);

    // Hoist any throwing function calls in the RHS expression before emitting the declaration
    // This ensures throwing calls are properly handled with error checking
    if !expr.params.is_empty() {
        hoist_throwing_expr(&expr.params[0], output, indent, ctx, context)?;
    }

    // Bug #35: For underscore declarations, just emit the expression (discard result)
    // This avoids C redeclaration errors and matches the semantics of discarding
    if decl.name == "_" {
        if !expr.params.is_empty() {
            output.push_str(&indent_str);
            // FCall at statement level (indent > 0) adds ";\n" itself
            // Other expressions need semicolon added explicitly
            let is_fcall = matches!(&expr.params[0].node_type, NodeType::FCall);
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
    // Prioritize struct/enum constructor types, then use get_value_type for other cases
    let var_type = if let Some(ref type_name) = struct_type {
        ValueType::TCustom(type_name.clone())
    } else if let Some(ref type_name) = enum_type {
        ValueType::TCustom(type_name.clone())
    } else if !expr.params.is_empty() {
        get_value_type(context, &expr.params[0]).ok()
            .unwrap_or_else(|| decl.value_type.clone())
    } else {
        decl.value_type.clone()
    };
    // Add to scope_stack so get_value_type can find it
    context.scope_stack.declare_symbol(
        name.clone(),
        SymbolInfo { value_type: var_type, is_mut: decl.is_mut, is_copy: false, is_own: false, is_comptime_const: false }
    );

    // Check if variable already declared in this function (avoid C redefinition errors)
    // Use til_name() since that's what hoisting code uses when inserting into declared_vars
    let already_declared = ctx.declared_vars.contains(&til_name(name));

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
                    ctx.declared_vars.insert(til_name(name));
                }
                output.push_str(&til_name(name));
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
                    ctx.declared_vars.insert(til_name(name));
                }
                output.push_str(&til_name(name));
                emit_struct_literal_assign(output, &type_name, already_declared, "{0}");
            } else {
                // Has default values or named args - emit designated initializer
                // First check if any default value is a throwing function call
                let mut throwing_defaults: Vec<ThrowingDefault> = Vec::new();
                for member in &struct_def.members {
                    if !member.is_mut {
                        continue;
                    }
                    if named_values.contains_key(&member.name) {
                        continue; // Named arg overrides default
                    }
                    if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                        if is_throwing_fcall(default_expr, context) {
                            throwing_defaults.push(ThrowingDefault { member_name: &member.name, default_expr });
                        }
                    }
                }

                // If we have throwing defaults, emit them as separate statements first
                for td in &throwing_defaults {
                    // Get the function's throw types
                    let throw_types = if let Some(first_param) = td.default_expr.params.first() {
                        if let Some(lookup_name) = get_til_func_name_string(first_param) {
                            context.scope_stack.lookup_func(&lookup_name)
                                .map(|fd| fd.throw_types.clone())
                                .unwrap_or_default()
                        } else {
                            Vec::new()
                        }
                    } else {
                        Vec::new()
                    };

                    let temp_name = format!("_default_{}_{}", td.member_name, next_mangled(ctx));
                    // Emit the function call with out-param using emit_throwing_call_propagate
                    emit_throwing_call_propagate(td.default_expr, &throw_types, Some(&temp_name), None, output, indent, ctx, context)?;
                    // Record that this struct default was hoisted using "struct_name:member_name" key
                    let key = format!("{}:{}", type_name, td.member_name);
                    ctx.hoisted_struct_defaults.insert(key, temp_name);
                }

                output.push_str(&indent_str);
                if !already_declared {
                    if !is_mut {
                        output.push_str("const ");
                    }
                    output.push_str(&til_name(&type_name));
                    output.push_str(" ");
                    ctx.declared_vars.insert(til_name(name));
                }
                output.push_str(&til_name(name));
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
                        // Check if this was a throwing default - use temp var instead
                        let key = format!("{}:{}", type_name, member.name);
                        if let Some(temp_name) = ctx.hoisted_struct_defaults.get(&key) {
                            output.push_str(temp_name);
                        } else if is_throwing_fcall(default_expr, context) {
                            // Shouldn't happen - throwing defaults should be hoisted
                            output.push_str("/* ERROR: unhoisted throwing default */");
                        } else {
                            emit_expr(default_expr, output, 0, ctx, context)?;
                        }
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
                ctx.declared_vars.insert(til_name(name));
            }
            output.push_str(&til_name(name));
            emit_struct_literal_assign(output, &type_name, already_declared, "{0}");
        }
    } else if let Some(type_name) = enum_type {
        // Enum variable declaration
        output.push_str(&indent_str);
        if !already_declared {
            if !is_mut {
                output.push_str("const ");
            }
            output.push_str(&til_name(&type_name));
            output.push_str(" ");
            ctx.declared_vars.insert(til_name(name));
        }
        output.push_str(&til_name(name));
        output.push_str(" = ");
        emit_expr(&expr.params[0], output, 0, ctx, context)?;
        output.push_str(";\n");
    } else if is_mut {
        // Hoist Dynamic and ref params in RHS if it's an FCall
        if !expr.params.is_empty() {
            if let NodeType::FCall = &expr.params[0].node_type {
                let rhs_fcall = &expr.params[0];
                if rhs_fcall.params.len() > 1 {
                    if let Some(fd) = get_fcall_func_def(context, rhs_fcall) {
                        let param_types: Vec<Option<ValueType>> = fd.args.iter()
                            .map(|fd_arg| Some(fd_arg.value_type.clone()))
                            .collect();
                        let param_by_ref: Vec<bool> = fd.args.iter()
                            .map(|fd_arg| param_needs_by_ref(fd_arg))
                            .collect();
                        let args = &rhs_fcall.params[1..];
                        let empty_hoisted = std::collections::HashMap::new();
                        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &empty_hoisted, output, indent, ctx, context)?;
                        for h in &dynamic_hoisted {
                            if let Some(hoisted_arg) = args.get(h.index) {
                                let expr_addr = hoisted_arg as *const Expr as usize;
                                ctx.hoisted_exprs.insert(expr_addr, format!("&{}", h.temp_var));
                            }
                        }
                        let mut hoisted_map: std::collections::HashMap<usize, String> = dynamic_hoisted.into_iter().map(|h| (h.index, h.temp_var)).collect();
                        let ref_hoisted = hoist_for_ref_params(args, &param_by_ref, &hoisted_map, output, indent, ctx, context)?;
                        for h in ref_hoisted {
                            if let Some(ref_arg) = args.get(h.index) {
                                let expr_addr = ref_arg as *const Expr as usize;
                                ctx.hoisted_exprs.insert(expr_addr, format!("&{}", h.temp_var));
                            }
                            hoisted_map.insert(h.index, h.temp_var);
                        }
                    }
                }
            }
        }
        output.push_str(&indent_str);
        if !already_declared {
            // Determine C type - use explicit type annotation if present, otherwise infer
            let is_infer = matches!(&decl.value_type, ValueType::TCustom(s) if s == INFER_TYPE);
            let c_type = if is_infer {
                // INFER_TYPE - infer from RHS
                let vt = get_value_type(context, &expr.params[0]).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?;
                til_type_to_c(&vt).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?
            } else {
                // Explicit type annotation - use it
                til_type_to_c(&decl.value_type).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?
            };
            output.push_str(&c_type);
            output.push_str(" ");
            ctx.declared_vars.insert(til_name(name));
        }
        output.push_str(&til_name(name));
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
        }
        output.push_str(";\n");
    } else {
        // const declaration
        // Hoist Dynamic and ref params in RHS if it's an FCall
        if !expr.params.is_empty() {
            if let NodeType::FCall = &expr.params[0].node_type {
                let rhs_fcall = &expr.params[0];
                if rhs_fcall.params.len() > 1 {
                    if let Some(fd) = get_fcall_func_def(context, rhs_fcall) {
                        let param_types: Vec<Option<ValueType>> = fd.args.iter()
                            .map(|fd_arg| Some(fd_arg.value_type.clone()))
                            .collect();
                        let param_by_ref: Vec<bool> = fd.args.iter()
                            .map(|fd_arg| param_needs_by_ref(fd_arg))
                            .collect();
                        let args = &rhs_fcall.params[1..];
                        let empty_hoisted = std::collections::HashMap::new();
                        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &empty_hoisted, output, indent, ctx, context)?;
                        for h in &dynamic_hoisted {
                            if let Some(hoisted_arg) = args.get(h.index) {
                                let expr_addr = hoisted_arg as *const Expr as usize;
                                ctx.hoisted_exprs.insert(expr_addr, format!("&{}", h.temp_var));
                            }
                        }
                        let mut hoisted_map: std::collections::HashMap<usize, String> = dynamic_hoisted.into_iter().map(|h| (h.index, h.temp_var)).collect();
                        let ref_hoisted = hoist_for_ref_params(args, &param_by_ref, &hoisted_map, output, indent, ctx, context)?;
                        for h in ref_hoisted {
                            if let Some(ref_arg) = args.get(h.index) {
                                let expr_addr = ref_arg as *const Expr as usize;
                                ctx.hoisted_exprs.insert(expr_addr, format!("&{}", h.temp_var));
                            }
                            hoisted_map.insert(h.index, h.temp_var);
                        }
                    }
                }
            }
        }
        output.push_str(&indent_str);
        if !already_declared {
            // Determine C type - use explicit type annotation if present, otherwise infer
            let is_infer = matches!(&decl.value_type, ValueType::TCustom(s) if s == INFER_TYPE);
            let c_type = if is_infer {
                // INFER_TYPE - infer from RHS
                let vt = get_value_type(context, &expr.params[0]).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?;
                til_type_to_c(&vt).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?
            } else {
                // Explicit type annotation - use it
                til_type_to_c(&decl.value_type).map_err(|e| expr.lang_error(&context.path, "ccodegen", &e))?
            };
            output.push_str("const ");
            output.push_str(&c_type);
            output.push_str(" ");
            ctx.declared_vars.insert(til_name(name));
        }
        output.push_str(&til_name(name));
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
        }
        output.push_str(";\n");
    }
    Ok(())
}

// Check if an expression is a struct construction call (TypeName() or TypeName(x=1, y=2))
// Returns the type name if it is, None otherwise
fn get_struct_construction_type(expr: &Expr, context: &Context) -> Option<String> {
    if let NodeType::FCall = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(name) = &expr.params[0].node_type {
                // Use lookup_struct to check if this is a known struct type
                if expr.params[0].params.is_empty()
                    && context.scope_stack.lookup_struct(name).is_some() {
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
    if let NodeType::FCall = &expr.node_type {
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

    if !expr.params.is_empty() {
        let rhs_expr = &expr.params[0];

        // Check if RHS is a call to a throwing function
        if let NodeType::FCall = rhs_expr.node_type {
            if let Some(throw_types) = get_fcall_func_def(context, rhs_expr).map(|fd| fd.throw_types).filter(|t| !t.is_empty()) {
                // RHS is a throwing function call - emit with error propagation
                // (typer should ensure non-throwing context doesn't call throwing functions without catch)
                // Pass raw name so function can properly handle field access on mut params
                emit_throwing_call_propagate(rhs_expr, &throw_types, None, Some(name), output, indent, ctx, context)?;
                return Ok(());
            }
        }

        // Hoist any throwing function calls nested in the RHS expression
        hoist_throwing_expr(rhs_expr, output, indent, ctx, context)?;
    }

    // Regular assignment
    output.push_str(&indent_str);
    // Check if assignment target is a field access on a mut param (self.field)
    // If so, emit with -> instead of .
    if let Some(dot_pos) = name.find('.') {
        let base = &name[..dot_pos];
        let rest = &name[dot_pos + 1..];
        if ctx.current_ref_params.contains(base) {
            // Mut param field access: til_self->field
            output.push_str(&til_name(base));
            output.push_str("->");
            output.push_str(rest);
        } else {
            output.push_str(&til_name(name));
        }
    } else if ctx.current_ref_params.contains(name) {
        // Direct assignment to mut param: *til_self = value
        output.push_str("*");
        output.push_str(&til_name(name));
    } else {
        output.push_str(&til_name(name));
    }
    output.push_str(" = ");
    if !expr.params.is_empty() {
        emit_expr(&expr.params[0], output, 0, ctx, context)?;
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
            if let NodeType::FCall = return_expr.node_type {
                if let Some(throw_types) = get_fcall_func_def(context, return_expr).map(|fd| fd.throw_types).filter(|t| !t.is_empty()) {
                    // Return expression is a throwing function call - emit with error propagation
                    // The result will be stored via the assign_name "*_ret"
                    emit_throwing_call_propagate(return_expr, &throw_types, None, Some("*_ret"), output, indent, ctx, context)?;
                    output.push_str(&indent_str);
                    output.push_str("return 0;\n");
                    return Ok(());
                }
            }

            // Hoist any throwing function calls nested in the return expression
            hoist_throwing_expr(return_expr, output, indent, ctx, context)?;

            // Regular return value - just emit it
            output.push_str(&indent_str);
            output.push_str("*_ret = ");
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
            output.push_str(";\n");
        }
        output.push_str(&indent_str);
        output.push_str("return 0;\n");
    } else {
        // Non-throwing function: normal return
        // Check if return expression is a variadic function call
        if !expr.params.is_empty() {
            let return_expr = &expr.params[0];
            if let NodeType::FCall = return_expr.node_type {
                if let Some(variadic_fcall_info) = detect_variadic_fcall(return_expr, ctx) {
                    // Variadic call in return - need to hoist it
                    // First, hoist any nested throwing/variadic calls in the arguments
                    let all_args: Vec<_> = return_expr.params.iter().skip(1).collect();
                    let hoisted_vec = hoist_throwing_args(&all_args.iter().map(|a| (*a).clone()).collect::<Vec<_>>(), output, indent, ctx, context)?;
                    let hoisted: std::collections::HashMap<usize, String> = hoisted_vec.into_iter().map(|h| (h.index, h.temp_var)).collect();
                    let variadic_args: Vec<_> = return_expr.params.iter().skip(1 + variadic_fcall_info.regular_count).collect();
                    let arr_var = hoist_variadic_args(&variadic_fcall_info.elem_type, &variadic_args, &hoisted, variadic_fcall_info.regular_count, output, indent, ctx, context)?;

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
                    // Emit regular args with proper by-ref handling
                    let args: Vec<_> = return_expr.params.iter().skip(1).collect();
                    // Look up function param info for by-ref handling
                    let param_info: Vec<ParamTypeInfo> = if let Some(fd) = get_fcall_func_def(context, return_expr) {
                        fd.args.iter().map(|fd_arg| ParamTypeInfo { value_type: Some(fd_arg.value_type.clone()), by_ref: param_needs_by_ref(fd_arg) }).collect()
                    } else {
                        Vec::new()
                    };
                    for (i, arg) in args.iter().take(variadic_fcall_info.regular_count).enumerate() {
                        if i > 0 {
                            output.push_str(", ");
                        }
                        let (param_type, by_ref) = param_info.get(i)
                            .map(|info| (info.value_type.as_ref(), info.by_ref))
                            .unwrap_or((None, true));
                        emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
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

        // Hoist any throwing function calls nested in the return expression
        if !expr.params.is_empty() {
            hoist_throwing_expr(&expr.params[0], output, indent, ctx, context)?;
        }

        // Regular non-variadic return
        output.push_str(&indent_str);
        output.push_str("return");
        if !expr.params.is_empty() {
            output.push_str(" ");
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
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

    // Check if the thrown expression itself is a throwing function call (e.g., throw format(...))
    // If so, we need to hoist it first to ensure proper error handling
    if let Some(hoisted_temp) = hoist_throwing_expr(thrown_expr, output, indent, ctx, context)? {
        // The thrown expression was hoisted to a temp variable
        // Now we just need to throw the temp variable value
        // Get the type of the hoisted value
        let thrown_type_name = if let Some(fd) = get_fcall_func_def(context, thrown_expr) {
            if let Some(ret_type) = fd.return_types.first() {
                if let crate::rs::parser::ValueType::TCustom(type_name) = ret_type {
                    type_name.clone()
                } else {
                    crate::rs::parser::value_type_to_str(ret_type)
                }
            } else {
                return Err("ccodegen: throwing function has no return type".to_string());
            }
        } else {
            return Err("ccodegen: could not find throwing function definition".to_string());
        };

        // Check if this type is locally caught
        if let Some(catch_info) = ctx.local_catch_labels.get(&thrown_type_name) {
            let label = catch_info.label.clone();
            let temp_var = catch_info.temp_var.clone();
            output.push_str(&indent_str);
            output.push_str(&temp_var);
            output.push_str(" = ");
            output.push_str(&hoisted_temp);
            output.push_str(";\n");
            output.push_str(&indent_str);
            output.push_str("goto ");
            output.push_str(&label);
            output.push_str(";\n");
            return Ok(());
        }

        // Find the index of this type in current_throw_types
        let mut error_index: Option<usize> = None;
        for (i, vt) in ctx.current_throw_types.iter().enumerate() {
            if let crate::rs::parser::ValueType::TCustom(name) = vt {
                if name == &thrown_type_name {
                    error_index = Some(i);
                    break;
                }
            }
        }

        match error_index {
            Some(idx) => {
                output.push_str(&indent_str);
                output.push_str(&format!("*_err{} = ", idx + 1));
                output.push_str(&hoisted_temp);
                output.push_str(";\n");
                output.push_str(&indent_str);
                output.push_str(&format!("return {};\n", idx + 1));
                return Ok(());
            }
            None => return Err(format!(
                "ccodegen: thrown type '{}' not found in function's throw types: {:?}",
                thrown_type_name, ctx.current_throw_types
            )),
        }
    }

    // Get the thrown type name from the expression
    // For FCall, we need to determine if it's:
    // 1. A constructor like DivideByZero() - use the type name
    // 2. A function that returns an error type like format() - use the return type
    let nh_thrown_type_name = match &thrown_expr.node_type {
        NodeType::FCall => {
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
        // Hoist any throwing function calls in the thrown expression
        let nh_hoisted: std::collections::HashMap<usize, String> = if let NodeType::FCall = &thrown_expr.node_type {
            if thrown_expr.params.len() > 1 {
                let nh_args = &thrown_expr.params[1..];
                let nh_hoisted_vec = hoist_throwing_args(nh_args, output, indent, ctx, context)?;
                nh_hoisted_vec.into_iter().map(|nh_h| (nh_h.index, nh_h.temp_var)).collect()
            } else {
                std::collections::HashMap::new()
            }
        } else {
            std::collections::HashMap::new()
        };

        // Store the error value in temp variable
        output.push_str(&indent_str);
        output.push_str(&nh_temp_var);
        output.push_str(" = ");

        // Emit the thrown expression
        if let NodeType::FCall = &thrown_expr.node_type {
            emit_fcall_with_hoisted(thrown_expr, &nh_hoisted, output, ctx, context)?;
        } else {
            emit_expr(thrown_expr, output, 0, ctx, context)?;
        }
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
            // Hoist throwing function calls from arguments of the thrown expression
            // E.g., throw Error.new(format(...)) needs to hoist format() first
            let nh_prop_hoisted: std::collections::HashMap<usize, String> = if let NodeType::FCall = &thrown_expr.node_type {
                if thrown_expr.params.len() > 1 {
                    let nh_prop_args = &thrown_expr.params[1..];
                    let nh_prop_hoisted_vec = hoist_throwing_args(nh_prop_args, output, indent, ctx, context)?;
                    nh_prop_hoisted_vec.into_iter().map(|nh_prop_h| (nh_prop_h.index, nh_prop_h.temp_var)).collect()
                } else {
                    std::collections::HashMap::new()
                }
            } else {
                std::collections::HashMap::new()
            };

            // Store the error value in the appropriate error pointer
            // Note: error params are 1-based (_err1, _err2, etc.)
            output.push_str(&indent_str);
            output.push_str(&format!("*_err{} = ", idx + 1));

            // Emit the thrown expression, using hoisted temp vars for arguments
            if let NodeType::FCall = &thrown_expr.node_type {
                emit_fcall_with_hoisted(thrown_expr, &nh_prop_hoisted, output, ctx, context)?;
            } else {
                emit_expr(thrown_expr, output, 0, ctx, context)?;
            }
            output.push_str(";\n");

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

/// Emit an FCall expression using pre-hoisted temp vars for arguments
fn emit_fcall_with_hoisted(
    expr: &Expr,
    hoisted: &std::collections::HashMap<usize, String>,
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    if expr.params.is_empty() {
        return Err("emit_fcall_with_hoisted: FCall with no params".to_string());
    }

    // Get function name (handles both nested identifiers and precomp'd "Type.method" strings)
    let func_name = match get_func_name_string(&expr.params[0]) {
        Some(name) => name,
        None => return Err("emit_fcall_with_hoisted: FCall first param not Identifier".to_string()),
    };

    // Check for struct construction: TypeName() or TypeName(x=10, y=20)
    // Use lookup_struct to verify this is a known struct type
    let has_named_args = expr.params.iter().skip(1).any(|arg| matches!(&arg.node_type, NodeType::NamedArg(_)));
    let struct_def_opt = context.scope_stack.lookup_struct(&func_name).cloned();
    if struct_def_opt.is_some()
        && (expr.params.len() == 1 || has_named_args)  // No args OR only named args (struct literal)
    {
        output.push_str("(");
        output.push_str(TIL_PREFIX);
        output.push_str(&func_name);
        output.push_str(")");

        // Use the struct definition to get default values
        if let Some(struct_def) = struct_def_opt {
            if struct_def.members.is_empty() || struct_def.default_values.is_empty() {
                output.push_str("{}");
            } else {
                // Build map of named arg values
                let mut named_values: std::collections::HashMap<String, &Expr> = std::collections::HashMap::new();
                for arg in expr.params.iter().skip(1) {
                    if let NodeType::NamedArg(field_name) = &arg.node_type {
                        if let Some(value_expr) = arg.params.first() {
                            named_values.insert(field_name.clone(), value_expr);
                        }
                    }
                }

                // Check if any default value is a throwing function call
                // Such calls need out-params and can't be inlined in struct initializers
                let mut throwing_defaults: Vec<ThrowingDefault> = Vec::new();
                for member in &struct_def.members {
                    if !member.is_mut {
                        continue;
                    }
                    if named_values.contains_key(&member.name) {
                        continue; // Named arg overrides default
                    }
                    if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                        if is_throwing_fcall(default_expr, context) {
                            throwing_defaults.push(ThrowingDefault { member_name: &member.name, default_expr });
                        }
                    }
                }

                // If we have throwing defaults, emit them as separate statements first
                // This only works when we're in a statement context (not inline expression)
                // For now, emit temp variables before the struct literal
                for td in &throwing_defaults {
                    // Get the function's throw types
                    let throw_types = if let Some(first_param) = td.default_expr.params.first() {
                        if let Some(lookup_name) = get_til_func_name_string(first_param) {
                            context.scope_stack.lookup_func(&lookup_name)
                                .map(|fd| fd.throw_types.clone())
                                .unwrap_or_default()
                        } else {
                            Vec::new()
                        }
                    } else {
                        Vec::new()
                    };

                    let temp_name = format!("_default_{}_{}", td.member_name, next_mangled(ctx));
                    // Emit the function call with out-param using emit_throwing_call_propagate
                    emit_throwing_call_propagate(td.default_expr, &throw_types, Some(&temp_name), None, output, 0, ctx, context)?;
                    // Record that this struct default was hoisted using "struct_name:member_name" key
                    let key = format!("{}:{}", func_name, td.member_name);
                    ctx.hoisted_struct_defaults.insert(key, temp_name);
                }

                // Build set of throwing default member names for quick lookup
                let throwing_default_names: std::collections::HashSet<&String> =
                    throwing_defaults.iter().map(|td| td.member_name).collect();

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
                    if let Some(member_value_expr) = named_values.get(&member.name) {
                        emit_expr(member_value_expr, output, 0, ctx, context)?;
                    } else if let Some(member_default_expr) = struct_def.default_values.get(&member.name) {
                        // Check if this was a throwing default - use temp var instead
                        let lookup_key = format!("{}:{}", func_name, member.name);
                        if let Some(hoisted_temp_name) = ctx.hoisted_struct_defaults.get(&lookup_key) {
                            output.push_str(hoisted_temp_name);
                        } else if throwing_default_names.contains(&member.name) || is_throwing_fcall(member_default_expr, context) {
                            // Shouldn't happen - throwing defaults should be hoisted
                            output.push_str("/* ERROR: unhoisted throwing default */");
                        } else {
                            emit_expr(member_default_expr, output, 0, ctx, context)?;
                        }
                    } else {
                        output.push_str("0");
                    }
                }
                output.push_str("}");
            }
        } else {
            output.push_str("{}");
        }
        return Ok(());
    }

    // Function call: til_func_name(args...)
    // func_name already has underscores (from get_func_name_string), just add prefix
    output.push_str(TIL_PREFIX);
    output.push_str(&func_name);
    output.push_str("(");

    // Look up param types for by-ref handling
    let param_info: Vec<ParamTypeInfo> = {
        if let Some(fd) = get_fcall_func_def(context, expr) {
            fd.args.iter().map(|fd_arg| ParamTypeInfo { value_type: Some(fd_arg.value_type.clone()), by_ref: param_needs_by_ref(fd_arg) }).collect()
        } else {
            Vec::new()
        }
    };

    for (emit_i, emit_arg) in expr.params.iter().skip(1).enumerate() {
        if emit_i > 0 {
            output.push_str(", ");
        }
        // Check if arg is a type identifier - emit as string literal
        if let Some(type_name) = get_type_arg_name(emit_arg, context) {
            output.push_str("\"");
            output.push_str(&type_name);
            output.push_str("\"");
        } else if !param_info.is_empty() {
            let (loop_param_type, loop_by_ref) = param_info.get(emit_i)
                .map(|loop_pi| (loop_pi.value_type.as_ref(), loop_pi.by_ref))
                .unwrap_or((None, false));
            emit_arg_with_param_type(emit_arg, emit_i, hoisted, loop_param_type, loop_by_ref, output, ctx, context)?;
        } else {
            emit_arg_or_hoisted(emit_arg, emit_i, hoisted, output, ctx, context)?;
        }
    }
    output.push_str(")");
    Ok(())
}

fn emit_if(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // If: params[0] = condition, params[1] = then-body, params[2] = else-body (optional)
    if expr.params.len() < 2 {
        return Err("ccodegen: If requires condition and body".to_string());
    }

    let indent_str = "    ".repeat(indent);

    // Hoist declarations from both branches to before the if statement
    // (TIL has function-level scoping, not block-level scoping)
    let then_decls = collect_declarations_in_body(&expr.params[1], context);
    for decl in then_decls {
        let c_var_name = til_name(&decl.name);
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
            let else_c_var_name = til_name(&else_decl.name);
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

    // Hoist any throwing function calls in the condition
    hoist_throwing_expr(&expr.params[0], output, indent, ctx, context)?;
    output.push_str(&indent_str);
    output.push_str("if (");
    emit_expr(&expr.params[0], output, 0, ctx, context)?;
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
    let body_decls = collect_declarations_in_body(&expr.params[1], context);
    for decl in body_decls {
        let c_var_name = til_name(&decl.name);
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

    // Check if condition contains throwing calls by trying to hoist to a temp buffer
    let mut hoist_output = String::new();
    hoist_throwing_expr(&expr.params[0], &mut hoist_output, indent + 1, ctx, context)?;

    if hoist_output.is_empty() {
        // No throwing calls in condition - use simple while
        output.push_str(&indent_str);
        output.push_str("while (");
        emit_expr(&expr.params[0], output, 0, ctx, context)?;
        // Bool is a struct with .data field - extract for C truthiness
        if let Ok(crate::rs::parser::ValueType::TCustom(type_name)) = crate::rs::init::get_value_type(context, &expr.params[0]) {
            if type_name == "Bool" {
                output.push_str(".data");
            }
        }
        output.push_str(") {\n");
    } else {
        // Throwing calls in condition - transform to while(1) with hoisted calls and break
        output.push_str(&indent_str);
        output.push_str("while (1) {\n");

        // Emit hoisted throwing calls inside the loop
        output.push_str(&hoist_output);

        // Emit condition check with break
        let inner_indent_str = "    ".repeat(indent + 1);
        output.push_str(&inner_indent_str);
        output.push_str("if (!(");
        emit_expr(&expr.params[0], output, 0, ctx, context)?;
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

// Result type for hoisted arguments
struct HoistedArg {
    index: usize,
    temp_var: String,
}

// Result struct for variant info extraction
struct VariantInfo {
    type_name: String,
    variant_name: String,
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

// Info about a struct member with a throwing default value
struct ThrowingDefault<'a> {
    member_name: &'a String,
    default_expr: &'a Expr,
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

// Extract enum type and variant names from a case pattern expression
// For FCall: Type.Variant -> VariantInfo { type_name: "Type", variant_name: "Variant" }
fn get_case_variant_info(expr: &Expr) -> VariantInfo {
    match &expr.node_type {
        NodeType::FCall => {
            // FCall for Type.Variant (without payload extraction)
            if !expr.params.is_empty() {
                if let NodeType::Identifier(type_name) = &expr.params[0].node_type {
                    if !expr.params[0].params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &expr.params[0].params[0].node_type {
                            return VariantInfo {
                                type_name: type_name.clone(),
                                variant_name: variant_name.clone(),
                            };
                        }
                    }
                }
            }
            VariantInfo { type_name: String::new(), variant_name: String::new() }
        },
        NodeType::Identifier(name) => {
            // Identifier with nested params: Type.Variant
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.params[0].node_type {
                    return VariantInfo {
                        type_name: name.clone(),
                        variant_name: variant_name.clone(),
                    };
                }
            }
            // Plain identifier without nested params - NOT an enum variant pattern
            // Return empty to let emit_switch fall through to regular value comparison
            VariantInfo { type_name: String::new(), variant_name: String::new() }
        },
        _ => VariantInfo { type_name: String::new(), variant_name: String::new() },
    }
}

// Extract type name and variant name from a Pattern's variant_name (e.g., "Color.Green")
fn parse_pattern_variant_name(variant_name: &str) -> VariantInfo {
    if let Some(dot_pos) = variant_name.rfind('.') {
        let type_name = variant_name[..dot_pos].to_string();
        let var_name = variant_name[dot_pos + 1..].to_string();
        VariantInfo { type_name, variant_name: var_name }
    } else {
        // No dot - just variant name (shouldn't happen in practice)
        VariantInfo { type_name: String::new(), variant_name: variant_name.to_string() }
    }
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
            // Add this declaration
            // If type is INFER_TYPE, try to infer from the expression
            let value_type = if let ValueType::TCustom(name) = &decl.value_type {
                if name == INFER_TYPE && !expr.params.is_empty() {
                    get_value_type(context, &expr.params[0]).ok().unwrap_or(decl.value_type.clone())
                } else {
                    decl.value_type.clone()
                }
            } else {
                decl.value_type.clone()
            };
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
        NodeType::Switch => {
            // Recurse into switch case bodies
            let mut i = 1;
            while i + 1 < expr.params.len() {
                collect_declarations_recursive(&expr.params[i + 1], decls, collected, context);
                i += 2;
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

fn emit_switch(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // Switch: params[0] = switch expression
    // params[1..] = alternating (case_pattern, body) pairs
    // We emit if/else chains instead of C switch because:
    // 1. C switch only works with integer types, not Str
    // 2. Avoids GCC-specific case range extension
    // 3. More portable and easier to handle all TIL switch patterns
    if expr.params.is_empty() {
        return Err("ccodegen: Switch requires expression".to_string());
    }

    let indent_str = "    ".repeat(indent);
    let body_indent = "    ".repeat(indent + 1);

    // Get the switch expression
    let switch_expr = &expr.params[0];

    // Hoist any throwing function calls in the switch expression
    hoist_throwing_expr(switch_expr, output, indent, ctx, context)?;

    // Determine the type of the switch expression for proper comparison
    // Type inference may fail - that's okay, we'll use None (default)
    let switch_type = get_value_type(context, switch_expr).ok();
    let is_str_switch = matches!(&switch_type, Some(ValueType::TCustom(t)) if t == "Str");

    // Determine if this is an enum switch and if it has payloads
    let mut is_enum_switch = false;
    let mut enum_has_payloads_flag = false;
    let mut i = 1;
    while i < expr.params.len() {
        let case_pattern = &expr.params[i];
        match &case_pattern.node_type {
            NodeType::Pattern(_) => {
                is_enum_switch = true;
            },
            NodeType::Identifier(name) => {
                if !case_pattern.params.is_empty() || name.contains('.') {
                    is_enum_switch = true;
                }
            },
            NodeType::FCall => {
                is_enum_switch = true;
                // FCall with arguments (e.g., ValueType.TType(TTypeDef.TEnumDef))
                // implies the enum has payloads
                if case_pattern.params.len() > 1 {
                    enum_has_payloads_flag = true;
                }
            },
            _ => {}
        }
        i += 2;
    }
    if is_enum_switch {
        if let Some(ValueType::TCustom(enum_name)) = &switch_type {
            if let Some(enum_def) = context.scope_stack.lookup_enum(enum_name) {
                enum_has_payloads_flag = enum_has_payloads(&enum_def);
            }
        }
    }

    // Store switch expression in a temp variable to avoid re-evaluation
    let switch_var = next_mangled(ctx);
    output.push_str(&indent_str);
    output.push_str("__auto_type ");
    output.push_str(&switch_var);
    output.push_str(" = ");
    emit_expr(switch_expr, output, 0, ctx, context)?;
    output.push_str(";\n");

    // Hoist declarations from all case bodies to before the if/else chain
    // This ensures variables declared in switch cases are visible after the switch
    // (TIL has function-level scoping, not block-level scoping)
    let mut i = 1;
    while i + 1 < expr.params.len() {
        let body = &expr.params[i + 1];
        let decls = collect_declarations_in_body(body, context);
        for decl in decls {
            let c_var_name = til_name(&decl.name);
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
        i += 2;
    }

    // Emit if/else if chain for cases
    // Default case (if present) is guaranteed to be last by parser
    let mut i = 1;
    let mut first_case = true;
    let mut has_cases = false;
    while i + 1 < expr.params.len() {
        let case_pattern = &expr.params[i];
        let case_body = &expr.params[i + 1];
        has_cases = true;

        // Check if this is the default case (guaranteed last by parser)
        if matches!(case_pattern.node_type, NodeType::DefaultCase) {
            // Default case - emit as else block
            if !first_case {
                output.push_str(&indent_str);
                output.push_str("} else {\n");
            }
            let saved_declared_vars = ctx.declared_vars.clone();
            emit_body(case_body, output, indent + 1, ctx, context)?;
            ctx.declared_vars = saved_declared_vars;
            i += 2;
            continue;
        }

        // Regular case - emit if/else if
        output.push_str(&indent_str);
        if first_case {
            output.push_str("if (");
            first_case = false;
        } else {
            output.push_str("} else if (");
        }

        // Emit the condition based on pattern type
        match &case_pattern.node_type {
            NodeType::Pattern(pattern_info) => {
                // Enum pattern with payload binding: compare tag
                let mut info = parse_pattern_variant_name(&pattern_info.variant_name);
                // If no type prefix (shorthand syntax), use the switch expression's type
                if info.type_name.is_empty() {
                    if let Some(ValueType::TCustom(enum_name)) = &switch_type {
                        info.type_name = enum_name.clone();
                    }
                }
                output.push_str(&switch_var);
                output.push_str(".tag == til_");
                output.push_str(&info.type_name);
                output.push_str("_");
                output.push_str(&info.variant_name);
                output.push_str(") {\n");

                // Extract payload into binding variable
                output.push_str(&body_indent);
                output.push_str("__auto_type ");
                output.push_str(&til_name(&pattern_info.binding_var));
                output.push_str(" = ");
                output.push_str(&switch_var);
                output.push_str(".payload.");
                output.push_str(&info.variant_name);
                output.push_str(";\n");
            },
            NodeType::Range => {
                // Range: low <= val && val <= high
                if case_pattern.params.len() < 2 {
                    return Err("ccodegen: Range requires start and end values".to_string());
                }
                if is_str_switch {
                    // For string ranges, use strcmp: strcmp(low, val) <= 0 && strcmp(val, high) <= 0
                    output.push_str("strcmp((char*)");
                    emit_expr(&case_pattern.params[0], output, 0, ctx, context)?;
                    output.push_str(".c_string, (char*)");
                    output.push_str(&switch_var);
                    output.push_str(".c_string) <= 0 && strcmp((char*)");
                    output.push_str(&switch_var);
                    output.push_str(".c_string, (char*)");
                    emit_expr(&case_pattern.params[1], output, 0, ctx, context)?;
                    output.push_str(".c_string) <= 0");
                } else {
                    emit_expr(&case_pattern.params[0], output, 0, ctx, context)?;
                    output.push_str(" <= ");
                    output.push_str(&switch_var);
                    output.push_str(" && ");
                    output.push_str(&switch_var);
                    output.push_str(" <= ");
                    emit_expr(&case_pattern.params[1], output, 0, ctx, context)?;
                }
                output.push_str(") {\n");
            },
            NodeType::Identifier(_name) => {
                let info = get_case_variant_info(case_pattern);
                if !info.variant_name.is_empty() {
                    // Enum variant without payload
                    output.push_str(&switch_var);
                    if enum_has_payloads_flag {
                        output.push_str(".tag");
                    }
                    output.push_str(" == ");
                    if !info.type_name.is_empty() {
                        output.push_str("til_");
                        output.push_str(&info.type_name);
                        output.push_str("_");
                    }
                    output.push_str(&info.variant_name);
                } else if is_str_switch {
                    // String comparison - pass by pointer
                    output.push_str("til_Str_eq(&");
                    output.push_str(&switch_var);
                    output.push_str(", &");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                    output.push_str(").data");
                } else {
                    // Regular value comparison
                    output.push_str(&switch_var);
                    output.push_str(" == ");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                }
                output.push_str(") {\n");
            },
            NodeType::LLiteral(_) => {
                if is_str_switch {
                    // String literal comparison - pass by pointer
                    output.push_str("til_Str_eq(&");
                    output.push_str(&switch_var);
                    output.push_str(", &");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                    output.push_str(").data");
                } else {
                    // Regular literal comparison
                    output.push_str(&switch_var);
                    output.push_str(" == ");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                }
                output.push_str(") {\n");
            },
            NodeType::FCall => {
                // FCall pattern: Type.Variant(payload) - enum variant with payload argument
                // For example: ValueType.TType(TTypeDef.TEnumDef)
                let info = get_case_variant_info(case_pattern);
                if !info.variant_name.is_empty() && enum_has_payloads_flag {
                    // Compare tag first
                    output.push_str(&switch_var);
                    output.push_str(".tag == til_");
                    output.push_str(&info.type_name);
                    output.push_str("_");
                    output.push_str(&info.variant_name);

                    // Check if there's a payload argument to compare
                    // params[0] is Type.Variant identifier, params[1+] are arguments
                    if case_pattern.params.len() > 1 {
                        let payload_expr = &case_pattern.params[1];
                        // Check if payload is also an enum variant (Type.Variant pattern)
                        let payload_info = get_case_variant_info(payload_expr);
                        if !payload_info.variant_name.is_empty() {
                            // Payload is an enum variant - compare payload field
                            output.push_str(" && ");
                            output.push_str(&switch_var);
                            output.push_str(".payload.");
                            output.push_str(&info.variant_name);
                            output.push_str(" == til_");
                            output.push_str(&payload_info.type_name);
                            output.push_str("_");
                            output.push_str(&payload_info.variant_name);
                        }
                        // TODO: handle non-enum payloads if needed
                    }
                    output.push_str(") {\n");
                } else if !info.variant_name.is_empty() {
                    // Enum without payloads - simple tag comparison
                    output.push_str(&switch_var);
                    output.push_str(" == til_");
                    output.push_str(&info.type_name);
                    output.push_str("_");
                    output.push_str(&info.variant_name);
                    output.push_str(") {\n");
                } else {
                    // Not an enum pattern - fall through to generic comparison
                    output.push_str(&switch_var);
                    output.push_str(" == ");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                    output.push_str(") {\n");
                }
            },
            _ => {
                // Generic case: emit equality comparison
                // TODO: Should emit proper FCall through normal path instead of hardcoding
                if is_str_switch {
                    output.push_str("til_Str_eq(&");
                    output.push_str(&switch_var);
                    output.push_str(", &");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                    output.push_str(").data");
                } else {
                    output.push_str(&switch_var);
                    output.push_str(" == ");
                    emit_expr(case_pattern, output, 0, ctx, context)?;
                }
                output.push_str(") {\n");
            },
        }

        // Emit case body
        // For pattern matching with binding variables, we need to add the binding to scope
        // so that get_value_type can resolve it during body emission
        // Save declared_vars for block scope - variables declared in this case body
        // should not affect other case bodies
        let saved_declared_vars = ctx.declared_vars.clone();

        if let NodeType::Pattern(pattern_info) = &case_pattern.node_type {
            // Get the payload type from the enum definition
            let info = parse_pattern_variant_name(&pattern_info.variant_name);
            let payload_type_opt: Option<ValueType> = if let Some(ValueType::TCustom(ref enum_name)) = switch_type {
                context.scope_stack.lookup_enum(enum_name)
                    .and_then(|enum_def| enum_def.get(&info.variant_name).cloned())
                    .flatten()
            } else {
                None
            };

            if let Some(payload_type) = payload_type_opt {
                // Push scope and declare binding variable
                context.scope_stack.push(ScopeType::Block);
                context.scope_stack.declare_symbol(
                    pattern_info.binding_var.clone(),
                    SymbolInfo {
                        value_type: payload_type,
                        is_mut: false,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    }
                );
                emit_body(case_body, output, indent + 1, ctx, context)?;
                context.scope_stack.pop().ok();
            } else {
                emit_body(case_body, output, indent + 1, ctx, context)?;
            }
        } else {
            emit_body(case_body, output, indent + 1, ctx, context)?;
        }

        // Restore declared_vars after case body
        ctx.declared_vars = saved_declared_vars;
        i += 2;
    }

    // Close the if/else chain
    if has_cases {
        output.push_str(&indent_str);
        output.push_str("}\n");
    }

    Ok(())
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
                        // Check if this was a throwing default - use temp var instead
                        let key = format!("{}:{}", func_name, member.name);
                        if let Some(temp_name) = ctx.hoisted_struct_defaults.get(&key) {
                            output.push_str(temp_name);
                        } else if is_throwing_fcall(default_expr, context) {
                            // Shouldn't happen - throwing defaults should be hoisted
                            output.push_str("/* ERROR: unhoisted throwing default */");
                        } else {
                            emit_expr(default_expr, output, 0, ctx, context)?;
                        }
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

    // Hoist throwing function calls from arguments (only at statement level)
    let mut hoisted: std::collections::HashMap<usize, String> = if is_stmt_level && expr.params.len() > 1 {
        let args = &expr.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().map(|h| (h.index, h.temp_var)).collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hoist non-lvalue args when param type is Dynamic (only at statement level)
    // Need to look up param types first
    if is_stmt_level && expr.params.len() > 1 {
        if let Some(fd) = get_fcall_func_def(context, expr) {
            let param_types: Vec<Option<ValueType>> = fd.args.iter()
                .map(|a| Some(a.value_type.clone()))
                .collect();
            let param_by_ref: Vec<bool> = fd.args.iter()
                .map(|a| param_needs_by_ref(a))
                .collect();
            let args = &expr.params[1..];
            let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &hoisted, output, indent, ctx, context)?;
            for h in dynamic_hoisted {
                hoisted.insert(h.index, h.temp_var);
            }
            // Hoist struct-returning FCall args when param is by-ref
            let ref_hoisted = hoist_for_ref_params(args, &param_by_ref, &hoisted, output, indent, ctx, context)?;
            for h in ref_hoisted {
                hoisted.insert(h.index, h.temp_var);
            }
        }
    }

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
                    output.push_str(&format!("(({}Str){{({}I64){}{}, strlen({}{})}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, type_name, TIL_PREFIX, type_name));
                } else {
                    // Literal type name - create Str compound literal
                    if context.scope_stack.lookup_struct("Str").is_some() {
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
                if context.scope_stack.lookup_enum(&enum_type_name).is_some() {
                    output.push_str(&til_name(&enum_type_name));
                    output.push_str("_to_str(");
                    // Check if the argument was already hoisted (hoisted exprs include & for Dynamic params)
                    let arg_addr = arg as *const Expr as usize;
                    if ctx.hoisted_exprs.contains_key(&arg_addr) {
                        // Already hoisted with & prefix
                        emit_expr(arg, output, 0, ctx, context)?;
                    } else {
                        // Need to add & for pointer parameter
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
                    output.push_str(&format!("(({}Str){{({}I64){}{}, strlen({}{})}})",
                        TIL_PREFIX, TIL_PREFIX, TIL_PREFIX, type_name, TIL_PREFIX, type_name));
                } else {
                    // Literal type name - create Str compound literal
                    emit_str_literal(type_name, output);
                }
            } else {
                // Not an identifier - emit as expression (should be Type/const char*)
                // Bug #60: emit_expr will dereference Type params via (*til_name)
                output.push_str(&format!("(({}Str){{({}I64)", TIL_PREFIX, TIL_PREFIX));
                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                output.push_str(", strlen(");
                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                output.push_str(")})");
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
            // Both mut Dynamic (void**) and non-mut Dynamic (void*) don't need &
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
            output.push_str("(");
            output.push_str(TIL_PREFIX);
            output.push_str("I64)");
            if is_dynamic_param {
                // Dynamic param: just output the variable name (it's already a pointer)
                if let NodeType::Identifier(name) = &arg.node_type {
                    output.push_str(&til_name(name));
                }
            } else {
                // Check if arg was hoisted with & prefix already
                let arg_addr = arg as *const Expr as usize;
                if let Some(temp_var) = ctx.hoisted_exprs.get(&arg_addr) {
                    if temp_var.starts_with('&') {
                        // Already has & prefix, just emit it
                        output.push_str(temp_var);
                    } else {
                        output.push_str("&");
                        output.push_str(temp_var);
                    }
                } else {
                    output.push_str("&");
                    emit_arg_or_hoisted(arg, 0, &hoisted, output, ctx, context)?;
                }
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
                if let NodeType::FCall = &expr.params[1].node_type {
                    // The second param is an FCall result - use get_value_type to get its return type
                    if let Ok(fcall_ret_type) = get_value_type(context, &expr.params[1]) {
                        if let ValueType::TCustom(type_name) = &fcall_ret_type {
                            let candidate = format!("{}.{}", type_name, orig_func_name);
                            if context.scope_stack.lookup_func(&candidate).is_some() {
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
                        // Check if any default value is a throwing function call
                        // Such calls need out-params and can't be inlined in struct initializers
                        let mut throwing_defaults: Vec<ThrowingDefault> = Vec::new();
                        for member in &struct_def.members {
                            if !member.is_mut {
                                continue;
                            }
                            if let Some(default_expr) = struct_def.default_values.get(&member.name) {
                                if is_throwing_fcall(default_expr, context) {
                                    throwing_defaults.push(ThrowingDefault { member_name: &member.name, default_expr });
                                }
                            }
                        }

                        // If we have throwing defaults, emit them as separate statements first
                        // Only do inline hoisting at statement level
                        // At expression level, hoisting was already done by hoist_throwing_expr
                        if is_stmt_level {
                            for td in &throwing_defaults {
                                // Get the function's throw types
                                let throw_types = if let Some(first_param) = td.default_expr.params.first() {
                                    if let Some(lookup_name) = get_til_func_name_string(first_param) {
                                        context.scope_stack.lookup_func(&lookup_name)
                                            .map(|fd| fd.throw_types.clone())
                                            .unwrap_or_default()
                                    } else {
                                        Vec::new()
                                    }
                                } else {
                                    Vec::new()
                                };

                                let temp_name = format!("_default_{}_{}", td.member_name, next_mangled(ctx));
                                // Emit the function call with out-param using emit_throwing_call_propagate
                                emit_throwing_call_propagate(td.default_expr, &throw_types, Some(&temp_name), None, output, indent, ctx, context)?;
                                // Record that this struct default was hoisted using "struct_name:member_name" key
                                let key = format!("{}:{}", func_name, td.member_name);
                                ctx.hoisted_struct_defaults.insert(key, temp_name);
                            }
                        }

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
                                // Check if this was a throwing default - use temp var instead
                                let key = format!("{}:{}", func_name, member.name);
                                if let Some(temp_name) = ctx.hoisted_struct_defaults.get(&key) {
                                    output.push_str(temp_name);
                                } else if is_throwing_fcall(default_expr, context) {
                                    // Shouldn't happen - throwing defaults should be hoisted
                                    output.push_str("/* ERROR: unhoisted throwing default */");
                                } else {
                                    emit_expr(default_expr, output, 0, ctx, context)?;
                                }
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
                    let variadic_args: Vec<_> = expr.params.iter().skip(1 + regular_count).collect();
                    Some(hoist_variadic_args(&elem_type, &variadic_args, &hoisted, regular_count, output, indent, ctx, context)?)
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
                // Bug #60: Look up function param info for proper by-ref handling of regular args
                let param_info: Vec<ParamTypeInfo> = if let Some(fd) = get_fcall_func_def(context, expr) {
                    fd.args.iter().map(|fd_arg| ParamTypeInfo { value_type: Some(fd_arg.value_type.clone()), by_ref: param_needs_by_ref(fd_arg) }).collect()
                } else if let Some(fd) = context.scope_stack.lookup_func(&orig_func_name) {
                    // Fallback: lookup via scope_stack directly
                    fd.args.iter().map(|fd_arg| ParamTypeInfo { value_type: Some(fd_arg.value_type.clone()), by_ref: param_needs_by_ref(fd_arg) }).collect()
                } else {
                    Vec::new()
                };
                // Emit regular args first (skip first param which is function name)
                let args: Vec<_> = expr.params.iter().skip(1).collect();
                for (i, arg) in args.iter().take(regular_count).enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    // Bug #60: If we couldn't find param info, default to by_ref=true
                    // (all non-copy params are by-ref, and we can't determine copy without param info)
                    let (param_type, by_ref) = param_info.get(i)
                        .map(|info| (info.value_type.as_ref(), info.by_ref))
                        .unwrap_or((None, true));
                    emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
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
                // Look up function to get parameter info (by_ref flags)
                let param_info: Vec<ParamTypeInfo> = if let Some(fd) = get_fcall_func_def(context, expr) {
                    fd.args.iter().map(|fd_arg| ParamTypeInfo { value_type: Some(fd_arg.value_type.clone()), by_ref: param_needs_by_ref(fd_arg) }).collect()
                } else {
                    Vec::new()
                };

                let mut first_arg = true;
                for (i, arg) in expr.params.iter().skip(1).enumerate() {
                    if !first_arg {
                        output.push_str(", ");
                    }
                    first_arg = false;
                    // Check if arg is a type identifier - emit as string literal
                    if let Some(type_name) = get_type_arg_name(arg, context) {
                        output.push_str("\"");
                        output.push_str(&type_name);
                        output.push_str("\"");
                    } else if !param_info.is_empty() {
                        let (param_type, by_ref) = param_info.get(i)
                            .map(|info| (info.value_type.as_ref(), info.by_ref))
                            .unwrap_or((None, false));
                        emit_arg_with_param_type(arg, i, &hoisted, param_type, by_ref, output, ctx, context)?;
                    } else {
                        emit_arg_or_hoisted(arg, i, &hoisted, output, ctx, context)?;
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

// Helper to emit a Str compound literal: ((til_Str){(til_I64)"...", len})
// This is valid in both constant initializers and expressions (unlike til_Str_from_literal)
fn emit_str_literal(s: &str, output: &mut String) {
    output.push_str(&format!("(({}Str){{({}I64)\"", TIL_PREFIX, TIL_PREFIX));
    // Escape special characters for C string literals
    for c in s.chars() {
        match c {
            '\n' => output.push_str("\\n"),
            '\r' => output.push_str("\\r"),
            '\t' => output.push_str("\\t"),
            '\\' => output.push_str("\\\\"),
            '"' => output.push_str("\\\""),
            _ => output.push(c),
        }
    }
    output.push_str(&format!("\", {}}})", s.len()));
}

fn emit_literal(lit: &Literal, output: &mut String, context: &Context) -> Result<(), String> {
    match lit {
        Literal::Str(s) => {
            let has_str = context.scope_stack.lookup_struct("Str").is_some();
            if has_str {
                emit_str_literal(s, output);
            } else {
                output.push('"');
                // Escape special characters for C string literals
                for c in s.chars() {
                    match c {
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
