// C code generator for TIL
// Translates TIL AST to C source code

use crate::rs::parser::{Expr, NodeType, Literal, SFuncDef, SEnumDef, ValueType, INFER_TYPE};
use crate::rs::init::{Context, get_value_type, ScopeFrame, SymbolInfo, ScopeType};
use std::collections::{HashMap, HashSet};
use std::sync::atomic::{AtomicUsize, Ordering};

// Global counter for generating unique mangled names
static MANGLING_COUNTER: AtomicUsize = AtomicUsize::new(0);

// Prefix for all TIL-generated names in C code (structs, functions, types)
const TIL_PREFIX: &str = "til_";

// Codegen context for tracking function info
struct CodegenContext {
    // Map function name -> variadic arg info (arg_name, element_type, regular_arg_count)
    func_variadic_args: HashMap<String, (String, String, usize)>,
    // Currently generating function's throw types (if any)
    current_throw_types: Vec<ValueType>,
    // Currently generating function's return types (if any)
    current_return_types: Vec<ValueType>,
    // Set of declared variable names in current function (to avoid redefinition)
    declared_vars: HashSet<String>,
    // Set of mut param names in current function - for using -> instead of . for field access
    current_mut_params: HashSet<String>,
    // Map of variadic param names to their element type (e.g., "args" -> "Bool")
    // Passed as til_Array* so need dereference, and need type info for Array.get casting
    current_variadic_params: HashMap<String, String>,
    // All known type names for generating til_size_of function
    known_types: Vec<String>,
}

impl CodegenContext {
    fn new() -> Self {
        CodegenContext {
            func_variadic_args: HashMap::new(),
            current_throw_types: Vec::new(),
            current_return_types: Vec::new(),
            declared_vars: HashSet::new(),
            current_mut_params: HashSet::new(),
            current_variadic_params: HashMap::new(),
            known_types: Vec::new(),
        }
    }

}

// Generate unique mangled name using global counter
fn next_mangled() -> String {
    let n = MANGLING_COUNTER.fetch_add(1, Ordering::SeqCst);
    format!("_tmp{}", n)
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

// Lookup function in scope_stack, trying both underscore and dot notation
// get_fcall_func_name returns underscore format (Str_clone) but scope_stack uses dots (Str.clone)
fn lookup_func_by_name<'a>(context: &'a Context, func_name: &str) -> Option<&'a SFuncDef> {
    // Try exact name first (for regular functions)
    if let Some(fd) = context.scope_stack.lookup_func(func_name) {
        return Some(fd);
    }
    // Try converting first underscore to dot (for struct methods)
    if let Some(idx) = func_name.find('_') {
        let dot_name = format!("{}.{}", &func_name[..idx], &func_name[idx+1..]);
        if let Some(fd) = context.scope_stack.lookup_func(&dot_name) {
            return Some(fd);
        }
    }
    None
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

/// Collect type names used in enum payloads
fn collect_enum_payload_types(expr: &Expr, types: &mut HashSet<String>) {
    if let NodeType::Declaration(_) = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::EnumDef(enum_def) = &expr.params[0].node_type {
                for (_variant_name, payload_type) in &enum_def.enum_map {
                    if let Some(pt) = payload_type {
                        if let ValueType::TCustom(type_name) = pt {
                            // Skip primitives
                            if type_name != "I64" && type_name != "U8" && type_name != "Bool"
                                && type_name != "Dynamic" && type_name != "Type" {
                                types.insert(type_name.clone());
                            }
                        }
                    }
                }
            }
        }
    }
}

/// Topologically sort struct declarations by their field dependencies
/// Returns indices into the original vector in sorted order
fn topological_sort_structs(structs: &[&Expr]) -> Vec<usize> {
    // Build name -> index map
    let mut name_to_idx: HashMap<String, usize> = HashMap::new();
    for (idx, expr) in structs.iter().enumerate() {
        if let Some(name) = get_struct_name(expr) {
            name_to_idx.insert(name, idx);
        }
    }

    // Build adjacency list (dependencies)
    let mut deps: Vec<Vec<usize>> = vec![Vec::new(); structs.len()];
    for (idx, expr) in structs.iter().enumerate() {
        for dep_name in get_struct_dependencies(expr) {
            if let Some(&dep_idx) = name_to_idx.get(&dep_name) {
                if dep_idx != idx {
                    deps[idx].push(dep_idx);
                }
            }
        }
    }

    // Kahn's algorithm for topological sort
    let mut in_degree: Vec<usize> = vec![0; structs.len()];
    for dep_list in &deps {
        for &dep in dep_list {
            in_degree[dep] += 1;
        }
    }

    // Actually we need reverse - if A depends on B, B must come first
    // So reverse the edges
    let mut reverse_deps: Vec<Vec<usize>> = vec![Vec::new(); structs.len()];
    for (idx, dep_list) in deps.iter().enumerate() {
        for &dep in dep_list {
            reverse_deps[dep].push(idx);
        }
    }

    // Recalculate in-degree for reversed graph
    let mut in_degree: Vec<usize> = vec![0; structs.len()];
    for dep_list in &reverse_deps {
        for &dep in dep_list {
            in_degree[dep] += 1;
        }
    }

    let mut queue: Vec<usize> = Vec::new();
    for (idx, &degree) in in_degree.iter().enumerate() {
        if degree == 0 {
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
    if result.len() < structs.len() {
        for idx in 0..structs.len() {
            if !result.contains(&idx) {
                result.push(idx);
            }
        }
    }

    result
}

/// Check if an expression is a throwing function call
/// Returns Some((func_name, throw_types, return_type)) if it is, None otherwise
fn check_throwing_fcall(expr: &Expr, _ctx: &CodegenContext, context: &Context) -> Option<(String, Vec<ValueType>, Option<ValueType>)> {
    if let NodeType::FCall = &expr.node_type {
        if let Some(func_name) = get_fcall_func_name(expr, context) {
            if let Some(fd) = lookup_func_by_name(context, &func_name) {
                if !fd.throw_types.is_empty() {
                    let return_type = fd.return_types.first().cloned();
                    return Some((func_name, fd.throw_types.clone(), return_type));
                }
            }
        }
    }
    None
}

/// Hoist throwing function calls from arguments (recursively)
/// Returns a vector of (arg_index, temp_var_name) for arguments that were hoisted
fn hoist_throwing_args(
    args: &[Expr],  // The arguments (skip first param which is function name)
    output: &mut String,
    indent: usize,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<Vec<(usize, String)>, String> {
    let mut hoisted = Vec::new();
    let indent_str = "    ".repeat(indent);

    for (idx, arg) in args.iter().enumerate() {
        // Check if it's a throwing call
        let throwing_info = check_throwing_fcall(arg, ctx, context);
        // Check if it's a variadic call (even if not throwing)
        let variadic_info = detect_variadic_fcall(arg, ctx, context);

        // Handle throwing calls (may also be variadic)
        if let Some((_func_name, throw_types, return_type)) = throwing_info {
            // RECURSIVELY hoist any throwing calls in this call's arguments first
            let nested_hoisted: std::collections::HashMap<usize, String> = if arg.params.len() > 1 {
                let nested_args = &arg.params[1..];
                let nested_vec = hoist_throwing_args(nested_args, output, indent, ctx, context)?;
                nested_vec.into_iter().collect()
            } else {
                std::collections::HashMap::new()
            };

            let temp_var = next_mangled();

            // Determine the C type for the temp variable
            let c_type = if let Some(ret_type) = &return_type {
                til_type_to_c(ret_type).unwrap_or_else(|| "int".to_string())
            } else {
                "int".to_string()
            };

            // Declare temp variable
            output.push_str(&indent_str);
            output.push_str(&c_type);
            output.push_str(" ");
            output.push_str(&temp_var);
            output.push_str(";\n");

            // Declare error variables for each throw type
            let temp_suffix = next_mangled();
            for (err_idx, throw_type) in throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = throw_type {
                    output.push_str(&indent_str);
                    output.push_str(&til_name(type_name));
                    output.push_str(" _err");
                    output.push_str(&err_idx.to_string());
                    output.push_str("_");
                    output.push_str(&temp_suffix);
                    output.push_str(";\n");
                }
            }

            // Detect and construct variadic array if needed
            let variadic_arr_var: Option<String> = if let Some((elem_type, regular_count)) = variadic_info.clone() {
                let variadic_args: Vec<_> = arg.params.iter().skip(1 + regular_count).collect();
                if !variadic_args.is_empty() {
                    Some(hoist_variadic_args(&elem_type, &variadic_args, &nested_hoisted, regular_count, output, indent, ctx, context)?)
                } else {
                    // Empty variadic - still need an array (with 0 elements)
                    Some(hoist_variadic_args(&elem_type, &[], &nested_hoisted, regular_count, output, indent, ctx, context)?)
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
            emit_fcall_name_and_args_for_throwing(arg, &temp_var, &temp_suffix, &throw_types, &nested_hoisted, variadic_arr_var.as_deref(), output, ctx, context)?;

            output.push_str(";\n");

            // Emit error checking - propagate if any error occurred
            output.push_str(&indent_str);
            output.push_str("if (_status_");
            output.push_str(&temp_suffix);
            output.push_str(" != 0) {\n");

            // Propagate error based on status value
            // For now, propagate to corresponding error pointer in current function
            for (err_idx, throw_type) in throw_types.iter().enumerate() {
                if let ValueType::TCustom(type_name) = throw_type {
                    // Find matching throw type in current function
                    for (curr_idx, curr_throw) in ctx.current_throw_types.iter().enumerate() {
                        if let ValueType::TCustom(curr_type_name) = curr_throw {
                            if curr_type_name == type_name {
                                output.push_str(&indent_str);
                                output.push_str("    if (_status_");
                                output.push_str(&temp_suffix);
                                output.push_str(" == ");
                                output.push_str(&(err_idx + 1).to_string());
                                output.push_str(") { *_err");
                                output.push_str(&(curr_idx + 1).to_string());
                                output.push_str(" = _err");
                                output.push_str(&err_idx.to_string());
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

            // Emit Array.delete if variadic array was constructed
            if let Some(arr_var) = &variadic_arr_var {
                output.push_str(&indent_str);
                output.push_str(TIL_PREFIX);
                output.push_str("Array_delete(&");
                output.push_str(arr_var);
                output.push_str(");\n");
            }

            hoisted.push((idx, temp_var));
        }
        // Handle non-throwing variadic calls
        else if let Some((elem_type, regular_count)) = variadic_info {
            // RECURSIVELY hoist any throwing/variadic calls in this call's arguments first
            let nested_hoisted: std::collections::HashMap<usize, String> = if arg.params.len() > 1 {
                let nested_args = &arg.params[1..];
                let nested_vec = hoist_throwing_args(nested_args, output, indent, ctx, context)?;
                nested_vec.into_iter().collect()
            } else {
                std::collections::HashMap::new()
            };

            let temp_var = next_mangled();

            // Determine return type from function
            let c_type = if let Some(func_name) = get_fcall_func_name(arg, context) {
                if let Some(fd) = lookup_func_by_name(context, &func_name) {
                    if let Some(ret_type) = fd.return_types.first() {
                        til_type_to_c(ret_type).unwrap_or_else(|| "int".to_string())
                    } else {
                        "int".to_string()
                    }
                } else {
                    "int".to_string()
                }
            } else {
                "int".to_string()
            };

            // Declare temp variable
            output.push_str(&indent_str);
            output.push_str(&c_type);
            output.push_str(" ");
            output.push_str(&temp_var);
            output.push_str(";\n");

            // Construct variadic array
            let variadic_args: Vec<_> = arg.params.iter().skip(1 + regular_count).collect();
            let variadic_arr_var = if !variadic_args.is_empty() {
                hoist_variadic_args(&elem_type, &variadic_args, &nested_hoisted, regular_count, output, indent, ctx, context)?
            } else {
                hoist_variadic_args(&elem_type, &[], &nested_hoisted, regular_count, output, indent, ctx, context)?
            };

            // Emit the function call (non-throwing, so direct assignment)
            output.push_str(&indent_str);
            output.push_str(&temp_var);
            output.push_str(" = ");

            // Emit function name
            if let Some(func_name) = get_fcall_func_name(arg, context) {
                output.push_str(&til_func_name(&func_name));
            }
            output.push('(');

            // Emit regular args (using nested hoisted temps)
            let mut first = true;
            for (i, param) in arg.params.iter().skip(1).take(regular_count).enumerate() {
                if !first {
                    output.push_str(", ");
                }
                first = false;
                if let Some(temp) = nested_hoisted.get(&i) {
                    output.push_str(temp);
                } else {
                    emit_expr(param, output, 0, ctx, context)?;
                }
            }

            // Emit variadic array pointer
            if !first {
                output.push_str(", ");
            }
            output.push('&');
            output.push_str(&variadic_arr_var);

            output.push_str(");\n");

            // Delete the variadic array
            output.push_str(&indent_str);
            output.push_str(TIL_PREFIX);
            output.push_str("Array_delete(&");
            output.push_str(&variadic_arr_var);
            output.push_str(");\n");

            hoisted.push((idx, temp_var));
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
) -> Result<Vec<(usize, String)>, String> {
    let mut hoisted = Vec::new();
    let indent_str = "    ".repeat(indent);

    for (idx, arg) in args.iter().enumerate() {
        // Skip if already hoisted by throwing args hoister
        if already_hoisted.contains_key(&idx) {
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

        // Determine the C type of the arg - for string literals it's til_Str
        let c_type = match &arg.node_type {
            NodeType::LLiteral(Literal::Str(_)) => format!("{}Str", TIL_PREFIX),
            _ => {
                // For function calls, try to determine return type
                if let Some((_func_name, _throw_types, return_type)) = check_throwing_fcall(arg, ctx, context) {
                    if let Some(ret) = return_type {
                        til_type_to_c(&ret).unwrap_or_else(|| format!("{}Str", TIL_PREFIX))
                    } else {
                        format!("{}Str", TIL_PREFIX)
                    }
                } else {
                    // Non-throwing function call or other expression - assume Str for string literals context
                    format!("{}Str", TIL_PREFIX)
                }
            }
        };

        let temp_var = next_mangled();

        // Emit: til_Str _tmpXX = <expression>;
        output.push_str(&indent_str);
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(&temp_var);
        output.push_str(" = ");
        emit_expr(arg, output, 0, ctx, context)?;
        output.push_str(";\n");

        hoisted.push((idx, temp_var));
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
    let arr_var = next_mangled();
    let err_suffix = next_mangled();
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
            let temp_var = next_mangled();
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

    // Emit Array.new call with error handling
    // int _status = til_Array_new(&arr, &_err_alloc, "ElemType", count);
    output.push_str(&indent_str);
    output.push_str("int _arr_status_");
    output.push_str(&err_suffix);
    output.push_str(" = ");
    output.push_str(TIL_PREFIX);
    output.push_str("Array_new(&");
    output.push_str(&arr_var);
    output.push_str(", &_err_alloc_");
    output.push_str(&err_suffix);
    output.push_str(", \"");
    output.push_str(elem_type);
    output.push_str("\", ");
    output.push_str(&variadic_count.to_string());
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
        // int _status = til_Array_set(&_err_idx, &arr, i, &temp);
        output.push_str(&indent_str);
        output.push_str("_arr_status_");
        output.push_str(&err_suffix);
        output.push_str(" = ");
        output.push_str(TIL_PREFIX);
        output.push_str("Array_set(&_err_idx_");
        output.push_str(&err_suffix);
        output.push_str(", &");
        output.push_str(&arr_var);
        output.push_str(", ");
        output.push_str(&i.to_string());
        output.push_str(", &");
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
/// Returns (elem_type, regular_count) if it's a variadic call
fn detect_variadic_fcall(
    expr: &Expr,
    ctx: &CodegenContext,
    context: &Context,
) -> Option<(String, usize)> {
    if expr.params.is_empty() {
        return None;
    }

    let func_name = match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                name.clone()
            } else if let Some((method_name, _)) = extract_type_method_and_depth(&expr.params[0]) {
                method_name
            } else {
                return None;
            }
        }
        _ => return None,
    };

    // Build mangled name for lookup
    let mangled_name = {
        let mut name = String::new();
        if !expr.params[0].params.is_empty() {
            if let NodeType::Identifier(receiver_name) = &expr.params[0].node_type {
                let receiver_type: Option<ValueType> = context.scope_stack.lookup_symbol(receiver_name)
                    .map(|s| s.value_type.clone());
                if let Some(ValueType::TCustom(type_name)) = receiver_type {
                    let candidate = format!("{}.{}", type_name, func_name);
                    if context.scope_stack.lookup_func(&candidate).is_some() {
                        name.push_str(&type_name);
                        name.push('_');
                    }
                } else if receiver_type.is_none() {
                    name.push_str(receiver_name);
                    name.push('_');
                }
            }
        } else if expr.params.len() > 1 {
            if let NodeType::Identifier(first_arg_name) = &expr.params[1].node_type {
                let arg_type: Option<ValueType> = context.scope_stack.lookup_symbol(first_arg_name)
                    .map(|s| s.value_type.clone());
                if let Some(ValueType::TCustom(type_name)) = arg_type {
                    let candidate = format!("{}.{}", type_name, func_name);
                    if context.scope_stack.lookup_func(&candidate).is_some() {
                        name.push_str(&type_name);
                        name.push('_');
                    }
                }
            }
        }
        name.push_str(&func_name);
        name
    };

    ctx.func_variadic_args.get(&mangled_name)
        .map(|(_, elem_type, regular_count)| (elem_type.clone(), *regular_count))
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

    // Determine function name and type receiver (for type-qualified calls like I64.to_str)
    let (func_name, type_receiver, type_depth) = match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                (name.clone(), None, 0)
            } else {
                if let Some((method_name, depth)) = extract_type_method_and_depth(&expr.params[0]) {
                    (method_name, Some(&expr.params[0]), depth)
                } else {
                    return Err("emit_fcall_name_and_args_for_throwing: type-qualified method name not Identifier".to_string());
                }
            }
        },
        _ => return Err("emit_fcall_name_and_args_for_throwing: FCall first param not Identifier".to_string()),
    };

    // Emit function name with potential type-qualified mangling (e.g., I64.to_str -> til_I64_to_str)
    // Track if we emitted a struct prefix (to avoid double til_ on method name)
    let mut is_struct_method = false;
    if let Some(receiver) = type_receiver {
        if let NodeType::Identifier(receiver_name) = &receiver.node_type {
            // Create receiver expression without method to get its type
            let receiver_without_method = clone_without_deepest_method(receiver, type_depth);

            // Use get_value_type to resolve the full receiver chain type
            let receiver_type = get_value_type(context, &receiver_without_method).ok();

            // Determine type name from receiver type
            let type_name_opt: Option<String> = match &receiver_type {
                Some(ValueType::TCustom(name)) if name != INFER_TYPE => Some(name.clone()),
                // Type-qualified call: receiver IS a type name (struct/enum)
                Some(ValueType::TType(_)) => Some(receiver_name.to_string()),
                _ => None,
            };

            if let Some(type_name) = type_name_opt {
                let mangled_name = format!("{}.{}", type_name, func_name);
                if context.scope_stack.lookup_func(&mangled_name).is_some() {
                    output.push_str(&til_name(&type_name));
                    output.push_str("_");
                    is_struct_method = true;
                }
            } else if receiver_type.is_none() {
                // Not a known symbol - treat as Type.func (type-qualified call)
                output.push_str(&til_name(receiver_name));
                output.push_str("_");
                is_struct_method = true;
            }
        }
    } else {
        // Check for type-qualified method via first argument type
        if expr.params.len() > 1 {
            if let NodeType::Identifier(first_arg_name) = &expr.params[1].node_type {
                let arg_type: Option<ValueType> = context.scope_stack.lookup_symbol(first_arg_name)
                    .map(|s| s.value_type.clone());
                if let Some(ValueType::TCustom(type_name)) = arg_type {
                    let mangled_name = format!("{}.{}", type_name, func_name);
                    if context.scope_stack.lookup_func(&mangled_name).is_some() {
                        output.push_str(&til_name(&type_name));
                        output.push_str("_");
                        is_struct_method = true;
                    }
                }
            }
        }
    }

    // For struct methods, we already emitted til_Type_, so just add method name
    // For top-level functions, add til_ prefix via til_func_name
    if is_struct_method {
        output.push_str(&func_name);
    } else {
        output.push_str(&til_func_name(&func_name));
    }
    output.push_str("(&");
    output.push_str(temp_var);

    // Add error output pointers
    for (idx, _) in throw_types.iter().enumerate() {
        output.push_str(", &_err");
        output.push_str(&idx.to_string());
        output.push_str("_");
        output.push_str(temp_suffix);
    }

    // Build mangled function name for variadic lookup
    let mangled_name = {
        let mut name = String::new();
        if let Some(receiver) = type_receiver {
            if let NodeType::Identifier(receiver_name) = &receiver.node_type {
                let receiver_type: Option<ValueType> = context.scope_stack.lookup_symbol(receiver_name)
                    .map(|s| s.value_type.clone());
                // Get type name for mangling - TMulti becomes Array
                let type_name_opt = match &receiver_type {
                    Some(ValueType::TCustom(type_name)) => Some(type_name.clone()),
                    Some(ValueType::TMulti(_)) => Some("Array".to_string()),
                    _ => None,
                };
                if let Some(type_name) = type_name_opt {
                    let candidate = format!("{}.{}", type_name, func_name);
                    if context.scope_stack.lookup_func(&candidate).is_some() {
                        name.push_str(&type_name);
                        name.push('_');
                    }
                } else if receiver_type.is_none() {
                    // Type-qualified call
                    name.push_str(receiver_name);
                    name.push('_');
                }
            }
        } else if expr.params.len() > 1 {
            if let NodeType::Identifier(first_arg_name) = &expr.params[1].node_type {
                let arg_type: Option<ValueType> = context.scope_stack.lookup_symbol(first_arg_name)
                    .map(|s| s.value_type.clone());
                if let Some(ValueType::TCustom(type_name)) = arg_type {
                    let candidate = format!("{}.{}", type_name, func_name);
                    if context.scope_stack.lookup_func(&candidate).is_some() {
                        name.push_str(&type_name);
                        name.push('_');
                    }
                }
            }
        }
        name.push_str(&func_name);
        name
    };

    // Check if this is a variadic function call
    if let Some((_variadic_name, _elem_type, regular_count)) = ctx.func_variadic_args.get(&mangled_name).cloned() {
        // Emit regular args first (skip first param which is function name)
        let args: Vec<_> = expr.params.iter().skip(1).collect();
        for (arg_idx, arg) in args.iter().take(regular_count).enumerate() {
            output.push_str(", ");
            if let Some(temp) = nested_hoisted.get(&arg_idx) {
                output.push_str(temp);
            } else {
                emit_expr(arg, output, 0, ctx, context)?;
            }
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
        let found_func = lookup_func_by_name(context, &mangled_name);
        if found_func.is_none() && !mangled_name.is_empty() {
            eprintln!("DEBUG emit_fcall: lookup FAILED for mangled_name={}", mangled_name);
        }
        let param_info: Vec<(Option<ValueType>, bool)> = found_func
            .map(|fd| {
                fd.args.iter()
                    .map(|p| (Some(p.value_type.clone()), p.is_mut))
                    .collect()
            })
            .unwrap_or_default();

        // Emit remaining arguments (using hoisted temps where available)
        for (arg_idx, arg) in expr.params.iter().skip(1).enumerate() {
            output.push_str(", ");

            // Get expected param type and mutability
            let (param_type, param_is_mut) = param_info.get(arg_idx)
                .map(|(t, m)| (t.as_ref(), *m))
                .unwrap_or((None, false));

            emit_arg_with_param_type(arg, arg_idx, nested_hoisted, param_type, param_is_mut, output, ctx, context)?;
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

/// Emit an argument with knowledge of expected parameter type and mutability
/// Handles: Type args as string literals, Dynamic args with &, mut args with &
fn emit_arg_with_param_type(
    arg: &Expr,
    arg_idx: usize,
    hoisted: &std::collections::HashMap<usize, String>,
    param_type: Option<&ValueType>,
    param_is_mut: bool,
    output: &mut String,
    ctx: &mut CodegenContext,
    context: &mut Context,
) -> Result<(), String> {
    if let Some(temp_var) = hoisted.get(&arg_idx) {
        // Hoisted temp var is an lvalue - add & if param is Dynamic or mut
        if param_is_mut {
            output.push_str("&");
        } else if let Some(ValueType::TCustom(param_type_name)) = param_type {
            if param_type_name == "Dynamic" {
                output.push_str("&");
            }
        }
        output.push_str(temp_var);
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
                // Simple variable - cast to til_Dynamic* (void**)
                output.push_str("(");
                output.push_str(TIL_PREFIX);
                output.push_str("Dynamic*)&");
                output.push_str(&til_name(name));
                return Ok(());
            }
        }
        // For non-identifier args (function calls, literals), they should have
        // been hoisted already. If not, just emit without & and let C handle it.
        emit_expr(arg, output, 0, ctx, context)?;
        return Ok(());
    }

    // Check if param is mut (but not Dynamic) - emit &arg for pointer
    if param_is_mut {
        if let NodeType::Identifier(name) = &arg.node_type {
            if arg.params.is_empty() {
                // Simple variable - emit &var
                output.push_str("&");
                output.push_str(&til_name(name));
                return Ok(());
            }
        }
        // For non-identifier args, emit as-is (may cause compile error, but that's a user error)
        emit_expr(arg, output, 0, ctx, context)?;
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
    output.push_str(&format!("#define true (({}Bool){{1}})\n", TIL_PREFIX));
    output.push_str(&format!("#define false (({}Bool){{0}})\n", TIL_PREFIX));
    // Dynamic and Type are special placeholder types
    output.push_str(&format!("typedef void* {}Dynamic;\n", TIL_PREFIX));
    output.push_str(&format!("typedef const char* {}Type;\n\n", TIL_PREFIX));

    // Pass 0: collect function info (throw types, return types) for call-site generation
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            collect_func_info(child, &mut ctx);
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

    // Build a map of struct name -> struct dependencies for transitive closure
    let mut struct_deps_map: HashMap<String, Vec<String>> = HashMap::new();
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                if let Some(name) = get_struct_name(child) {
                    let deps = get_struct_dependencies(child);
                    struct_deps_map.insert(name, deps);
                }
            }
        }
    }

    // Collect types needed by enum payloads (these structs must be emitted before enums)
    let mut enum_payload_deps: HashSet<String> = HashSet::new();
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) && is_enum_with_payloads(child) {
                collect_enum_payload_types(child, &mut enum_payload_deps);
            }
        }
    }

    // Expand to include transitive dependencies
    let mut to_process: Vec<String> = enum_payload_deps.iter().cloned().collect();
    while let Some(type_name) = to_process.pop() {
        if let Some(deps) = struct_deps_map.get(&type_name) {
            for dep in deps {
                if !enum_payload_deps.contains(dep) {
                    enum_payload_deps.insert(dep.clone());
                    to_process.push(dep.clone());
                }
            }
        }
    }

    // Collect names of enums with payloads (structs using these must be emitted after)
    let mut enums_with_payloads_names: HashSet<String> = HashSet::new();
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) && is_enum_with_payloads(child) {
                if let NodeType::Declaration(decl) = &child.node_type {
                    enums_with_payloads_names.insert(decl.name.clone());
                }
            }
        }
    }

    // Pass 1b: emit struct definitions that are needed by enum payloads
    // These must be complete before enum unions can use them
    // BUT: exclude structs that use enums-with-payloads as fields (they go in pass 1d)
    if let NodeType::Body = &ast.node_type {
        let struct_decls: Vec<&Expr> = ast.params.iter()
            .filter(|child| is_struct_declaration(child))
            .filter(|child| {
                if let Some(name) = get_struct_name(child) {
                    if !enum_payload_deps.contains(&name) {
                        return false;
                    }
                    // Check if this struct uses any enums-with-payloads as fields
                    let deps = get_struct_dependencies(child);
                    for dep in &deps {
                        if enums_with_payloads_names.contains(dep) {
                            return false; // Has dependency on enum-with-payloads, defer to pass 1d
                        }
                    }
                    true
                } else {
                    false
                }
            })
            .collect();
        let sorted_indices = topological_sort_structs(&struct_decls);
        for idx in sorted_indices {
            emit_struct_declaration(struct_decls[idx], &mut output)?;
        }
    }

    // Pass 1c: emit enums with payloads (after their payload dependencies are defined)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_enum_declaration(child) && is_enum_with_payloads(child) {
                emit_enum_declaration(child, &mut output)?;
            }
        }
    }

    // Pass 1d: emit remaining struct definitions (those not emitted in 1b)
    // These may use enums with payloads
    // This includes: structs NOT in enum_payload_deps, OR structs that use enums-with-payloads as fields
    if let NodeType::Body = &ast.node_type {
        let struct_decls: Vec<&Expr> = ast.params.iter()
            .filter(|child| is_struct_declaration(child))
            .filter(|child| {
                if let Some(name) = get_struct_name(child) {
                    if !enum_payload_deps.contains(&name) {
                        return true; // Not needed by enum payloads, emit now
                    }
                    // Check if this struct uses any enums-with-payloads as fields
                    let deps = get_struct_dependencies(child);
                    for dep in &deps {
                        if enums_with_payloads_names.contains(dep) {
                            return true; // Has dependency on enum-with-payloads, emit now (after 1c)
                        }
                    }
                    false // Was emitted in pass 1b
                } else {
                    true
                }
            })
            .collect();
        let sorted_indices = topological_sort_structs(&struct_decls);
        for idx in sorted_indices {
            emit_struct_declaration(struct_decls[idx], &mut output)?;
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
    output.push_str("\n");

    // Pass 3: include external C interface (after structs and forward decls)
    output.push_str("#include \"ext.c\"\n\n");

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

    // Pass 4b: emit top-level constants (non-mut declarations with literal values)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_constant_declaration(child) {
                emit_constant_declaration(child, &mut output, context)?;
            }
        }
    }

    // Pass 4c: emit til_size_of function (runtime type size lookup)
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
    // 4b: struct functions (with mangled names)
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            if is_struct_declaration(child) {
                emit_struct_func_bodies(child, &mut output, &mut ctx, context)?;
            }
        }
    }

    // Main function
    output.push_str("int main() {\n");

    // Pass 5: emit non-struct, non-function, non-enum, non-constant statements
    if let NodeType::Body = &ast.node_type {
        for child in &ast.params {
            // Skip true/false declarations - they're now #defines
            if let NodeType::Declaration(decl) = &child.node_type {
                if decl.name == "true" || decl.name == "false" {
                    continue;
                }
            }
            if !is_func_declaration(child) && !is_struct_declaration(child) && !is_enum_declaration(child) && !is_constant_declaration(child) {
                emit_expr(child, &mut output, 1, &mut ctx, context)?;
            }
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
                // Skip struct, enum, and function definitions
                NodeType::StructDef(_) | NodeType::EnumDef(_) | NodeType::FuncDef(_) => return false,
                _ => return false,
            }
        }
    }
    false
}

// Emit a top-level constant declaration at file scope
fn emit_constant_declaration(expr: &Expr, output: &mut String, context: &Context) -> Result<(), String> {
    if let NodeType::Declaration(decl) = &expr.node_type {
        if !expr.params.is_empty() {
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
                output.push_str(&til_name(&decl.name));
                output.push_str(" = ");
                emit_literal(lit, output, context)?;
                output.push_str(";\n");
            }
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
                        for (idx, arg) in func_def.args.iter().enumerate() {
                            if let ValueType::TMulti(elem_type) = &arg.value_type {
                                // Track: (arg_name, element_type, count of regular args before variadic)
                                ctx.func_variadic_args.insert(
                                    decl.name.clone(),
                                    (arg.name.clone(), elem_type.clone(), idx)
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
                                for (idx, arg) in func_def.args.iter().enumerate() {
                                    if let ValueType::TMulti(elem_type) = &arg.value_type {
                                        ctx.func_variadic_args.insert(
                                            mangled_name.clone(),
                                            (arg.name.clone(), elem_type.clone(), idx)
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
                        if let Some(c_type) = til_type_to_c(&member.value_type) {
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
                        if let Some(c_type) = til_type_to_c(&member.value_type) {
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
    output.push_str("size_of(");
    output.push_str(TIL_PREFIX);
    output.push_str("Str type_name) {\n");

    // All known types from structs and enums
    for type_name in &ctx.known_types {
        output.push_str("    if (strcmp((char*)type_name.c_string, \"");
        output.push_str(type_name);
        output.push_str("\") == 0) return ");
        output.push_str(TIL_PREFIX);
        output.push_str("size_of_");
        output.push_str(type_name);
        output.push_str(";\n");
    }

    output.push_str("    fprintf(stderr, \"size_of: unknown type %s\\n\", (char*)type_name.c_string);\n");
    output.push_str("    exit(1);\n");
    output.push_str("}\n");
}

// Check if an enum has any payloads
fn enum_has_payloads(enum_def: &SEnumDef) -> bool {
    for (_variant_name, payload_type) in &enum_def.enum_map {
        if payload_type.is_some() {
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
    let mut variants: Vec<_> = enum_def.enum_map.iter().collect();
    variants.sort_by_key(|(name, _)| *name);

    // 1. Emit tag enum: typedef enum { Color_Unknown = 0, ... } Color_Tag;
    output.push_str("typedef enum {\n");
    for (index, (variant_name, _)) in variants.iter().enumerate() {
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
    let has_any_payload = variants.iter().any(|(_, payload)| payload.is_some());
    if has_any_payload {
        output.push_str("typedef union {\n");
        for (variant_name, payload_type) in &variants {
            if let Some(pt) = payload_type {
                if let Some(c_type) = til_type_to_c(pt) {
                    output.push_str("    ");
                    output.push_str(&c_type);
                    output.push_str(" ");
                    output.push_str(variant_name);
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
    for (variant_name, payload_type) in &variants {
        output.push_str("static inline ");
        output.push_str(enum_name);
        output.push_str(" ");
        output.push_str(enum_name);
        output.push_str("_make_");
        output.push_str(variant_name);
        output.push_str("(");

        // Parameter for payload (if any)
        if let Some(pt) = payload_type {
            if let Some(c_type) = til_type_to_c(pt) {
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
                let mut variants: Vec<_> = enum_def.enum_map.keys().collect();
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
                            emit_func_signature(&mangled_name, func_def, output);
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
    ctx.current_mut_params.clear();
    // Track variadic params - they're passed as til_Array* so need dereference
    ctx.current_variadic_params.clear();
    for arg in &func_def.args {
        if arg.is_mut {
            ctx.current_mut_params.insert(arg.name.clone());
        }
        if let ValueType::TMulti(elem_type) = &arg.value_type {
            // elem_type is the type name string like "Bool"
            ctx.current_variadic_params.insert(arg.name.clone(), til_name(elem_type));
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
    for arg in &func_def.args {
        function_frame.symbols.insert(arg.name.clone(), SymbolInfo {
            value_type: arg.value_type.clone(),
            is_mut: arg.is_mut,
            is_copy: arg.is_copy,
            is_own: arg.is_own,
        });
    }
    context.scope_stack.frames.push(function_frame);

    // Clear declared_vars for new function scope
    ctx.declared_vars.clear();

    let mangled_name = format!("{}_{}", struct_name, member.name);
    emit_func_signature(&mangled_name, func_def, output);
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

// Convert TIL type to C type. Returns None if the type can't be represented in C (e.g., functions)
fn til_type_to_c(til_type: &crate::rs::parser::ValueType) -> Option<String> {
    match til_type {
        crate::rs::parser::ValueType::TCustom(name) => {
            if name == INFER_TYPE {
                None // Skip inferred types
            } else {
                // All types get TIL_PREFIX
                Some(format!("{}{}", TIL_PREFIX, name))
            }
        },
        crate::rs::parser::ValueType::TFunction(_) => None,
        crate::rs::parser::ValueType::TType(_) => None,
        crate::rs::parser::ValueType::TMulti(_) => None,
    }
}

// Helper to get C type name for a ValueType (for error struct definitions)
fn value_type_to_c_name(vt: &ValueType) -> String {
    match vt {
        ValueType::TCustom(name) => {
            // All types get TIL_PREFIX
            format!("{}{}", TIL_PREFIX, name)
        },
        _ => "int".to_string(),
    }
}

// Emit function signature (used by both prototype and definition)
// For throwing functions:
//   int func_name(RetType* _ret, Error1* _err1, Error2* _err2, args...)
// For non-throwing:
//   RetType func_name(args...)
fn emit_func_signature(func_name: &str, func_def: &SFuncDef, output: &mut String) {
    let is_throwing = !func_def.throw_types.is_empty();

    if is_throwing {
        // Throwing function returns int status code
        output.push_str("int ");
    } else {
        // Non-throwing function returns its actual type
        if func_def.return_types.is_empty() {
            output.push_str("void ");
        } else {
            let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
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
            let ret_type = til_type_to_c(&func_def.return_types[0]).unwrap_or("int".to_string());
            output.push_str(&ret_type);
            output.push_str("* _ret");
            param_count += 1;
        }

        for (i, throw_type) in func_def.throw_types.iter().enumerate() {
            if param_count > 0 {
                output.push_str(", ");
            }
            let err_type = value_type_to_c_name(throw_type);
            output.push_str(&err_type);
            output.push_str("* _err");
            output.push_str(&(i + 1).to_string());
            param_count += 1;
        }
    }

    // Input parameters
    for arg in func_def.args.iter() {
        if param_count > 0 {
            output.push_str(", ");
        }
        // Check for variadic arg (TMulti)
        if let ValueType::TMulti(_elem_type) = &arg.value_type {
            // Variadic args are passed as til_Array*
            output.push_str(TIL_PREFIX);
            output.push_str("Array* ");
            output.push_str(TIL_PREFIX);
            output.push_str(&arg.name);
            param_count += 1;
            break; // Variadic must be last
        } else {
            let arg_type = til_type_to_c(&arg.value_type).unwrap_or("int".to_string());

            if arg.is_mut {
                // mut: use pointer so mutations are visible to caller
                output.push_str(&arg_type);
                output.push_str("* ");
            } else {
                // const or copy: pass by value
                output.push_str("const ");
                output.push_str(&arg_type);
                output.push_str(" ");
            }
            output.push_str(TIL_PREFIX);
            output.push_str(&arg.name);
            param_count += 1;
        }
    }

    if param_count == 0 {
        output.push_str("void");
    }

    output.push_str(")");
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
                emit_func_signature(&func_name, func_def, output);
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
                // Track mut params for pointer dereference (-> vs .)
                ctx.current_mut_params.clear();
                // Track variadic params - they're passed as til_Array* so need dereference
                ctx.current_variadic_params.clear();
                for arg in &func_def.args {
                    if arg.is_mut {
                        ctx.current_mut_params.insert(arg.name.clone());
                    }
                    if let ValueType::TMulti(elem_type) = &arg.value_type {
                        // elem_type is the type name string like "Bool"
                        ctx.current_variadic_params.insert(arg.name.clone(), til_name(elem_type));
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
                for arg in &func_def.args {
                    let value_type = if let ValueType::TMulti(_) = &arg.value_type {
                        ValueType::TCustom("Array".to_string())
                    } else {
                        arg.value_type.clone()
                    };
                    function_frame.symbols.insert(arg.name.clone(), SymbolInfo {
                        value_type,
                        is_mut: arg.is_mut,
                        is_copy: arg.is_copy,
                        is_own: arg.is_own,
                    });
                }
                context.scope_stack.frames.push(function_frame);

                // Clear declared_vars for new function scope
                ctx.declared_vars.clear();

                let func_name = til_name(&decl.name);
                emit_func_signature(&func_name, func_def, output);
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
        NodeType::FCall => emit_fcall(expr, output, indent, ctx, context),
        NodeType::LLiteral(lit) => emit_literal(lit, output, context),
        NodeType::Declaration(decl) => emit_declaration(decl, expr, output, indent, ctx, context),
        NodeType::Identifier(name) => {
            // Check for type-qualified access (Type.field)
            if !expr.params.is_empty() {
                let first_char = name.chars().next().unwrap_or('a');
                // TODO: Use proper type info from AST instead of uppercase hack (see interpreter.rs)
                if first_char.is_uppercase() {
                    if let NodeType::Identifier(field) = &expr.params[0].node_type {
                        // Check if this is an enum variant by looking up in context
                        let is_enum_variant = if let Some(enum_def) = context.scope_stack.lookup_enum(name) {
                            enum_def.enum_map.contains_key(field)
                        } else {
                            false
                        };

                        if is_enum_variant {
                            // Enum variant: Type.Variant -> til_Type_make_Variant()
                            output.push_str(TIL_PREFIX);
                            output.push_str(name);
                            output.push_str("_make_");
                            output.push_str(field);
                            output.push_str("()");
                            return Ok(());
                        } else {
                            // Struct constant: Type.constant -> til_Type_constant
                            output.push_str(&til_name(name));
                            output.push_str("_");
                            output.push_str(field);
                            return Ok(());
                        }
                    }
                }
            }
            // Regular identifier or field access (b.val -> til_b.val)
            // For mut params (which are pointers in C), use -> for field access
            let is_mut_param = ctx.current_mut_params.contains(name);
            if is_mut_param && !expr.params.is_empty() {
                // Mut param with field access: (*til_self).field or til_self->field
                output.push_str(&til_name(name));
                for param in &expr.params {
                    if let NodeType::Identifier(field) = &param.node_type {
                        output.push_str("->");
                        output.push_str(field);
                    }
                }
            } else if is_mut_param {
                // Mut param used as value: dereference with *
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
        NodeType::Catch => Ok(()), // Catch blocks handled at call site
        NodeType::Throw => emit_throw(expr, output, indent, ctx, context),
        NodeType::StructDef(_) => Err("ccodegen: StructDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::EnumDef(_) => Err("ccodegen: EnumDef should be handled at top level, not in emit_expr".to_string()),
        NodeType::Switch => emit_switch(expr, output, indent, ctx, context),
        NodeType::DefaultCase => Err("ccodegen: DefaultCase should be handled inside emit_switch".to_string()),
        NodeType::Range => Err("ccodegen: Range not yet supported".to_string()),
        NodeType::Pattern(_) => Err("ccodegen: Pattern should be handled inside emit_switch".to_string()),
    }
}

fn emit_body(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    emit_stmts(&expr.params, output, indent, ctx, context)
}

/// Emit a sequence of statements with catch pattern detection
/// This is the core logic shared between emit_body and emit_func_declaration
fn emit_stmts(stmts: &[Expr], output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    let mut i = 0;

    // Pre-scan for function-level catches (at the end of the block)
    let func_level_catches = prescan_func_level_catches(stmts);

    while i < stmts.len() {
        let stmt = &stmts[i];

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
            // Get function name from the FCall
            let func_name = get_fcall_func_name(fcall, context);

            // Check if this function is a throwing function
            if let Some(func_name) = func_name {
                if let Some(throw_types) = lookup_func_by_name(context, &func_name).map(|fd| fd.throw_types.clone()).filter(|t| !t.is_empty()) {
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

                    if !catch_blocks.is_empty() {
                        // Emit throwing call with catch handling
                        emit_throwing_call(fcall, &throw_types, &catch_blocks, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, indent, ctx, context)?;
                        i = j; // Skip past catch blocks
                        continue;
                    } else if !ctx.current_throw_types.is_empty() {
                        // No catch blocks, but we're inside a throwing function
                        // Emit error propagation pattern
                        emit_throwing_call_propagate(fcall, &throw_types, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, indent, ctx, context)?;
                        i += 1;
                        continue;
                    } else if !func_level_catches.is_empty() {
                        // No immediate catch, not a throwing function, but has function-level catches
                        // Use those catches for error handling
                        emit_throwing_call(fcall, &throw_types, &func_level_catches, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, indent, ctx, context)?;
                        i += 1;
                        continue;
                    } else {
                        // No catches - typer should have caught this if we're in non-throwing context
                        // Just use propagate (will silently succeed on error if we're not throwing)
                        emit_throwing_call_propagate(fcall, &throw_types, maybe_decl_name.as_deref(), maybe_assign_name.as_deref(), output, indent, ctx, context)?;
                        i += 1;
                        continue;
                    }
                }
            }
        }

        // Regular statement handling
        emit_expr(stmt, output, indent, ctx, context)?;
        i += 1;
    }
    Ok(())
}

/// Get the function name from an FCall expression (returns ORIGINAL name for lookup)
/// This returns the name for scope_stack lookup, WITHOUT til_ prefix.
/// For C output, use til_name() on the result.
fn get_fcall_func_name(expr: &Expr, context: &Context) -> Option<String> {
    if expr.params.is_empty() {
        return None;
    }

    match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                // Regular function call - return original name
                Some(name.clone())
            } else {
                // Type-qualified call: Type.method() - use extract helper to get method name
                let (method_name, depth) = extract_type_method_and_depth(&expr.params[0])?;

                // Create receiver expression without method to get its type
                let receiver_without_method = clone_without_deepest_method(&expr.params[0], depth);

                // Use get_value_type to resolve the full receiver chain type
                let receiver_type = get_value_type(context, &receiver_without_method).ok();

                // Determine type name from receiver type
                let type_name_opt: Option<String> = match &receiver_type {
                    Some(ValueType::TCustom(type_name)) if type_name != INFER_TYPE => Some(type_name.clone()),
                    // Type-qualified call: receiver IS a type name (struct/enum)
                    Some(ValueType::TType(_)) => Some(name.to_string()),
                    _ => None,
                };

                if let Some(type_name) = type_name_opt {
                    let mangled_name = format!("{}.{}", type_name, method_name);
                    // Check if it's a known struct method
                    if context.scope_stack.lookup_func(&mangled_name).is_some() {
                        return Some(format!("{}_{}", type_name, method_name));
                    }
                    // Otherwise it's a top-level function, use plain method name
                    return Some(method_name.clone());
                }
                // Not found in scope - treat as Type.method (type-qualified call)
                Some(format!("{}_{}", name, method_name))
            }
        }
        _ => None,
    }
}

/// Pre-scan function body to collect function-level catch blocks
/// These are catch blocks that aren't immediately after a throwing call but at the end of the function
/// Returns a map of error type name -> catch block expressions
fn prescan_func_level_catches<'a>(stmts: &'a [Expr]) -> Vec<&'a Expr> {
    let mut catches = Vec::new();
    let mut i = stmts.len();

    // Scan backwards from end to find catch blocks at the function level
    while i > 0 {
        i -= 1;
        if let NodeType::Catch = stmts[i].node_type {
            catches.push(&stmts[i]);
        } else if let NodeType::Return = stmts[i].node_type {
            // Return statements can be interleaved with catches at function end
            continue;
        } else {
            // Stop scanning when we hit a non-catch, non-return statement
            break;
        }
    }

    catches
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
    let func_name = get_fcall_func_name(fcall, context)
        .ok_or_else(|| "emit_throwing_call: could not get function name".to_string())?;

    // Generate unique temp names for this call
    let temp_suffix = next_mangled();

    // Determine if we need a return value temp variable
    let needs_ret = decl_name.is_some() || assign_name.is_some();

    // Calculate param_types early for Dynamic hoisting
    let param_types: Vec<Option<ValueType>> = {
        let func_def = lookup_func_by_name(context, &func_name);
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def.and_then(|fd| fd.args.get(i)).map(|a| a.value_type.clone()))
            .collect()
    };
    // Calculate param_is_mut for pointer passing
    let param_is_mut: Vec<bool> = {
        let func_def = lookup_func_by_name(context, &func_name);
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def.and_then(|fd| fd.args.get(i)).map(|a| a.is_mut).unwrap_or(false))
            .collect()
    };

    // Hoist any throwing function calls in arguments BEFORE emitting this call
    let mut hoisted: std::collections::HashMap<usize, String> = if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hoist non-lvalue args (string literals, function calls) when param type is Dynamic
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &hoisted, output, indent, ctx, context)?;
        for (idx, temp_var) in dynamic_hoisted {
            hoisted.insert(idx, temp_var);
        }
    }

    // Declare local variables for return value and errors
    // Look up the actual return type from scope_stack
    let ret_type = if needs_ret {
        lookup_func_by_name(context, &func_name)
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
    if let Some(var_name) = decl_name {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" ");
        output.push_str(&til_name(var_name));
        output.push_str(";\n");
        ctx.declared_vars.insert(til_name(var_name));
        // Add to scope_stack for type resolution
        if let Some(fd) = lookup_func_by_name(context, &func_name) {
            if let Some(first_type) = fd.return_types.first() {
                context.scope_stack.declare_symbol(
                    var_name.to_string(),
                    SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false }
                );
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

    // Emit arguments
    let mut args_started = false;
    for (arg_idx, arg) in fcall.params.iter().skip(1).enumerate() {
        if needs_ret || !throw_types.is_empty() || args_started {
            output.push_str(", ");
        }
        // Get parameter type and mutability for this argument
        let param_type = param_types.get(arg_idx).and_then(|p| p.as_ref());
        let is_mut = param_is_mut.get(arg_idx).copied().unwrap_or(false);
        emit_arg_with_param_type(arg, arg_idx, &hoisted, param_type, is_mut, output, ctx, context)?;
        args_started = true;
    }

    output.push_str(");\n");

    // Generate if/else chain for error handling
    output.push_str(&indent_str);
    output.push_str("if (_status_");
    output.push_str(&temp_suffix.to_string());
    output.push_str(" == 0) {\n");

    // Success case: assign return value to target variable
    if let Some(var_name) = decl_name {
        // Declaration: assign to newly declared variable (declared before if block)
        let inner_indent = "    ".repeat(indent + 1);
        output.push_str(&inner_indent);
        output.push_str(&til_name(var_name));
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix.to_string());
        output.push_str(";\n");
    } else if let Some(var_name) = assign_name {
        // Assignment: assign to existing variable
        let inner_indent = "    ".repeat(indent + 1);
        output.push_str(&inner_indent);
        output.push_str(&til_name(var_name));
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
                let err_idx = throw_types.iter().position(|vt| {
                    if let crate::rs::parser::ValueType::TCustom(name) = vt {
                        name == err_type_name
                    } else {
                        false
                    }
                });

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
    let func_name = get_fcall_func_name(fcall, context)
        .ok_or_else(|| "emit_throwing_call_propagate: could not get function name".to_string())?;

    // Generate unique temp names for this call
    let temp_suffix = next_mangled();

    // Determine if we need a return value temp variable
    let needs_ret = decl_name.is_some() || assign_name.is_some();

    // Calculate param_types early for Dynamic hoisting
    let param_types: Vec<Option<ValueType>> = {
        let func_def = lookup_func_by_name(context, &func_name);
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def.and_then(|fd| fd.args.get(i)).map(|a| a.value_type.clone()))
            .collect()
    };
    // Calculate param_is_mut for pointer passing
    let param_is_mut: Vec<bool> = {
        let func_def = lookup_func_by_name(context, &func_name);
        fcall.params.iter().skip(1).enumerate()
            .map(|(i, _)| func_def.and_then(|fd| fd.args.get(i)).map(|a| a.is_mut).unwrap_or(false))
            .collect()
    };

    // Hoist any throwing function calls in arguments BEFORE emitting this call
    let mut hoisted: std::collections::HashMap<usize, String> = if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hoist non-lvalue args (string literals, function calls) when param type is Dynamic
    if fcall.params.len() > 1 {
        let args = &fcall.params[1..];
        let dynamic_hoisted = hoist_for_dynamic_params(args, &param_types, &hoisted, output, indent, ctx, context)?;
        for (idx, temp_var) in dynamic_hoisted {
            hoisted.insert(idx, temp_var);
        }
    }

    // Look up the actual return type from scope_stack
    let ret_type = if needs_ret {
        lookup_func_by_name(context, &func_name)
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
    if let Some(var_name) = decl_name {
        output.push_str(&indent_str);
        output.push_str(&ret_type);
        output.push_str(" ");
        output.push_str(&til_name(var_name));
        output.push_str(";\n");
        ctx.declared_vars.insert(til_name(var_name));
        // Add to scope_stack for type resolution
        if let Some(fd) = lookup_func_by_name(context, &func_name) {
            if let Some(first_type) = fd.return_types.first() {
                context.scope_stack.declare_symbol(
                    var_name.to_string(),
                    SymbolInfo { value_type: first_type.clone(), is_mut: true, is_copy: false, is_own: false }
                );
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
    for (arg_idx, arg) in fcall.params.iter().skip(1).enumerate() {
        if needs_ret || !throw_types.is_empty() || args_started {
            output.push_str(", ");
        }
        // Get parameter type and mutability for this argument
        let param_type = param_types.get(arg_idx).and_then(|p| p.as_ref());
        let is_mut = param_is_mut.get(arg_idx).copied().unwrap_or(false);
        emit_arg_with_param_type(arg, arg_idx, &hoisted, param_type, is_mut, output, ctx, context)?;
        args_started = true;
    }

    output.push_str(");\n");

    // Generate error propagation: if status != 0, copy error to caller's error param and return
    // Map error types from called function to current function's error params
    for (called_idx, called_throw_type) in throw_types.iter().enumerate() {
        if let crate::rs::parser::ValueType::TCustom(called_type_name) = called_throw_type {
            // Find matching error type in current function's throw types
            let current_idx = ctx.current_throw_types.iter().position(|vt| {
                if let crate::rs::parser::ValueType::TCustom(name) = vt {
                    name == called_type_name
                } else {
                    false
                }
            });

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
    if let Some(var_name) = decl_name {
        output.push_str(&indent_str);
        output.push_str(&til_name(var_name));
        output.push_str(" = _ret_");
        output.push_str(&temp_suffix);
        output.push_str(";\n");
    } else if let Some(var_name) = assign_name {
        output.push_str(&indent_str);
        output.push_str(&til_name(var_name));
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
        }
    }

    let indent_str = "    ".repeat(indent);
    let name = &decl.name;
    let is_mut = decl.is_mut;

    // Check if this is a struct construction (TypeName())
    let struct_type = if !expr.params.is_empty() {
        get_struct_construction_type(&expr.params[0])
    } else {
        None
    };

    // Check if this is an enum construction (Type.Variant or Type.Variant(value))
    let enum_type = if !expr.params.is_empty() {
        get_enum_construction_type(&expr.params[0])
    } else {
        None
    };

    // Track variable type for method mangling
    // Use the inferred type from struct/enum construction if available,
    // or use get_value_type to get return type of function calls like Vec.new(Str)
    let var_type = if let Some(ref type_name) = struct_type {
        ValueType::TCustom(type_name.clone())
    } else if let Some(ref type_name) = enum_type {
        ValueType::TCustom(type_name.clone())
    } else if let ValueType::TCustom(type_name) = &decl.value_type {
        if type_name == INFER_TYPE && !expr.params.is_empty() {
            // Try get_value_type first (handles function calls like Vec.new)
            // then fall back to literal inference
            get_value_type(context, &expr.params[0]).ok()
                .or_else(|| infer_type_from_expr(&expr.params[0], context))
                .unwrap_or_else(|| decl.value_type.clone())
        } else {
            decl.value_type.clone()
        }
    } else {
        decl.value_type.clone()
    };
    // Add to scope_stack so get_value_type can find it
    context.scope_stack.declare_symbol(
        name.clone(),
        SymbolInfo { value_type: var_type, is_mut: decl.is_mut, is_copy: false, is_own: false }
    );

    // Check if variable already declared in this function (avoid C redefinition errors)
    let already_declared = ctx.declared_vars.contains(name);

    if let Some(type_name) = struct_type {
        // Struct variable declaration
        output.push_str(&indent_str);
        if !already_declared {
            if !is_mut {
                output.push_str("const ");
            }
            output.push_str(&til_name(&type_name));
            output.push_str(" ");
            ctx.declared_vars.insert(name.clone());
        }
        output.push_str(&til_name(name));
        output.push_str(" = {0};\n");
    } else if let Some(type_name) = enum_type {
        // Enum variable declaration
        output.push_str(&indent_str);
        if !already_declared {
            if !is_mut {
                output.push_str("const ");
            }
            output.push_str(&til_name(&type_name));
            output.push_str(" ");
            ctx.declared_vars.insert(name.clone());
        }
        output.push_str(&til_name(name));
        output.push_str(" = ");
        emit_expr(&expr.params[0], output, 0, ctx, context)?;
        output.push_str(";\n");
    } else if is_mut {
        output.push_str(&indent_str);
        if !already_declared {
            // Determine C type from inferred type or fall back to int
            let c_type = if !expr.params.is_empty() {
                if let Some(inferred) = infer_type_from_expr(&expr.params[0], context) {
                    til_type_to_c(&inferred).unwrap_or("int".to_string())
                } else {
                    til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
                }
            } else {
                til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
            };
            output.push_str(&c_type);
            output.push_str(" ");
            ctx.declared_vars.insert(name.clone());
        }
        output.push_str(&til_name(name));
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
        }
        output.push_str(";\n");
    } else {
        // const declaration
        output.push_str(&indent_str);
        // Determine C type from inferred type or fall back to int
        let c_type = if !expr.params.is_empty() {
            if let Some(inferred) = infer_type_from_expr(&expr.params[0], context) {
                til_type_to_c(&inferred).unwrap_or("int".to_string())
            } else {
                til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
            }
        } else {
            til_type_to_c(&decl.value_type).unwrap_or("int".to_string())
        };
        output.push_str("const ");
        output.push_str(&c_type);
        output.push_str(" ");
        output.push_str(&til_name(name));
        if !expr.params.is_empty() {
            output.push_str(" = ");
            emit_expr(&expr.params[0], output, 0, ctx, context)?;
        }
        output.push_str(";\n");
    }
    Ok(())
}

// Check if an expression is a struct construction call (TypeName())
// Returns the type name if it is, None otherwise
fn get_struct_construction_type(expr: &Expr) -> Option<String> {
    if let NodeType::FCall = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(name) = &expr.params[0].node_type {
                // If it's a PascalCase identifier with no nested params and no other args, assume struct
                // TODO: Use proper type info from AST instead of uppercase hack (see interpreter.rs)
                if name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false)
                    && expr.params.len() == 1
                    && expr.params[0].params.is_empty() {
                    return Some(name.clone());
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
fn get_enum_construction_type(expr: &Expr) -> Option<String> {
    // Check FCall case: Type.Variant(value) or Type.Variant()
    if let NodeType::FCall = &expr.node_type {
        if !expr.params.is_empty() {
            if let NodeType::Identifier(type_name) = &expr.params[0].node_type {
                // Check if the type name is PascalCase
                // TODO: Use proper type info from AST instead of uppercase hack (see interpreter.rs)
                if type_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
                    // Check if there's a nested identifier (the variant) that's also PascalCase
                    if !expr.params[0].params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &expr.params[0].params[0].node_type {
                            if variant_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
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
        // TODO: Use proper type info from AST instead of uppercase hack (see interpreter.rs)
        if type_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.params[0].node_type {
                    if variant_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false) {
                        return Some(type_name.clone());
                    }
                }
            }
        }
    }

    None
}

// Infer type from a literal expression
// Returns Some(ValueType) if type can be inferred, None otherwise
fn infer_type_from_expr(expr: &Expr, context: &Context) -> Option<ValueType> {
    match &expr.node_type {
        NodeType::LLiteral(lit) => {
            match lit {
                Literal::Number(_) => Some(ValueType::TCustom("I64".to_string())),
                Literal::Str(_) => Some(ValueType::TCustom("Str".to_string())),
                Literal::List(_) => None, // Can't infer list element type from literal
            }
        },
        NodeType::FCall => {
            // Look up function return type from scope_stack
            if let Some(func_name) = get_fcall_func_name(expr, context) {
                if let Some(fd) = lookup_func_by_name(context, &func_name) {
                    return fd.return_types.first().cloned();
                }
            }
            None
        },
        NodeType::Identifier(name) => {
            // Look up variable type from scope_stack
            context.scope_stack.lookup_symbol(name).map(|s| s.value_type.clone())
        },
        _ => None
    }
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
            if let Some(func_name) = get_fcall_func_name(rhs_expr, context) {
                if let Some(throw_types) = lookup_func_by_name(context, &func_name).map(|fd| fd.throw_types.clone()).filter(|t| !t.is_empty()) {
                    // RHS is a throwing function call - emit with error propagation
                    // (typer should ensure non-throwing context doesn't call throwing functions without catch)
                    emit_throwing_call_propagate(rhs_expr, &throw_types, None, Some(&til_name(name)), output, indent, ctx, context)?;
                    return Ok(());
                }
            }
        }
    }

    // Regular assignment
    output.push_str(&indent_str);
    // Check if assignment target is a field access on a mut param (self.field)
    // If so, emit with -> instead of .
    if let Some(dot_pos) = name.find('.') {
        let base = &name[..dot_pos];
        let rest = &name[dot_pos + 1..];
        if ctx.current_mut_params.contains(base) {
            // Mut param field access: til_self->field
            output.push_str(&til_name(base));
            output.push_str("->");
            output.push_str(rest);
        } else {
            output.push_str(&til_name(name));
        }
    } else if ctx.current_mut_params.contains(name) {
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
                if let Some(func_name) = get_fcall_func_name(return_expr, context) {
                    if let Some(throw_types) = lookup_func_by_name(context, &func_name).map(|fd| fd.throw_types.clone()).filter(|t| !t.is_empty()) {
                        // Return expression is a throwing function call - emit with error propagation
                        // The result will be stored via the assign_name "*_ret"
                        emit_throwing_call_propagate(return_expr, &throw_types, None, Some("*_ret"), output, indent, ctx, context)?;
                        output.push_str(&indent_str);
                        output.push_str("return 0;\n");
                        return Ok(());
                    }
                }
            }

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
                if let Some((elem_type, regular_count)) = detect_variadic_fcall(return_expr, ctx, context) {
                    // Variadic call in return - need to hoist it
                    // First, hoist any nested throwing/variadic calls in the arguments
                    let all_args: Vec<_> = return_expr.params.iter().skip(1).collect();
                    let hoisted_vec = hoist_throwing_args(&all_args.iter().map(|a| (*a).clone()).collect::<Vec<_>>(), output, indent, ctx, context)?;
                    let hoisted: std::collections::HashMap<usize, String> = hoisted_vec.into_iter().collect();
                    let variadic_args: Vec<_> = return_expr.params.iter().skip(1 + regular_count).collect();
                    let arr_var = hoist_variadic_args(&elem_type, &variadic_args, &hoisted, regular_count, output, indent, ctx, context)?;

                    // Emit the function call storing result
                    let temp_var = next_mangled();
                    let ret_type = get_value_type(context, return_expr).ok()
                        .map(|t| til_type_to_c(&t).unwrap_or_else(|| "int".to_string()))
                        .unwrap_or_else(|| "int".to_string());
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
                    let args: Vec<_> = return_expr.params.iter().skip(1).collect();
                    for (i, arg) in args.iter().take(regular_count).enumerate() {
                        if i > 0 {
                            output.push_str(", ");
                        }
                        emit_expr(arg, output, 0, ctx, context)?;
                    }
                    // Emit variadic array pointer
                    if regular_count > 0 {
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

    // Get the thrown type name from the expression
    // For FCall, we need to determine if it's:
    // 1. A constructor like DivideByZero() - use the type name
    // 2. A function that returns an error type like format() - use the return type
    let thrown_type_name = match &thrown_expr.node_type {
        NodeType::FCall => {
            if !thrown_expr.params.is_empty() {
                if let NodeType::Identifier(name) = &thrown_expr.params[0].node_type {
                    // Check if this is a constructor (struct/enum) or a function call
                    // If it's a function that returns a type, use the return type
                    if let Some(func_name) = get_fcall_func_name(thrown_expr, context) {
                        if let Some(fd) = lookup_func_by_name(context, &func_name) {
                            // It's a function - use its return type as the thrown type
                            if let Some(ret_type) = fd.return_types.first() {
                                if let crate::rs::parser::ValueType::TCustom(type_name) = ret_type {
                                    type_name.clone()
                                } else {
                                    // Return type is a primitive (like Str) - convert to name
                                    crate::rs::parser::value_type_to_str(ret_type)
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
            if let Ok(value_type) = get_value_type(context, thrown_expr) {
                if let crate::rs::parser::ValueType::TCustom(type_name) = value_type {
                    type_name
                } else {
                    crate::rs::parser::value_type_to_str(&value_type)
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

    // Find the index of this type in current_throw_types
    // Note: Str is represented as TCustom("Str") in the type system
    let error_index = ctx.current_throw_types.iter().position(|vt| {
        match vt {
            crate::rs::parser::ValueType::TCustom(name) => name == &thrown_type_name,
            _ => false,
        }
    });

    match error_index {
        Some(idx) => {
            // Hoist throwing function calls from arguments of the thrown expression
            // E.g., throw Error.new(format(...)) needs to hoist format() first
            let hoisted: std::collections::HashMap<usize, String> = if let NodeType::FCall = &thrown_expr.node_type {
                if thrown_expr.params.len() > 1 {
                    let args = &thrown_expr.params[1..];
                    let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
                    hoisted_vec.into_iter().collect()
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
                emit_fcall_with_hoisted(thrown_expr, &hoisted, output, ctx, context)?;
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
            thrown_type_name, ctx.current_throw_types
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

    // Check for struct construction: TypeName() -> (til_TypeName){}
    // Struct names are PascalCase, no nested identifiers, no args
    if func_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false)
        && !func_name.contains('_')  // Not a Type_method call
        && expr.params.len() == 1    // No constructor args
    {
        output.push_str("(");
        output.push_str(TIL_PREFIX);
        output.push_str(&func_name);
        output.push_str("){}");
        return Ok(());
    }

    // Function call: til_func_name(args...)
    // func_name already has underscores (from get_func_name_string), just add prefix
    output.push_str(TIL_PREFIX);
    output.push_str(&func_name);
    output.push_str("(");

    // Look up param types for mut handling
    let param_info: Vec<(Option<ValueType>, bool)> = {
        // Convert underscore back to dot for lookup (e.g., "I64_inc" -> "I64.inc")
        let lookup_name = func_name.replacen('_', ".", 1);
        if let Some(fd) = lookup_func_by_name(context, &lookup_name) {
            fd.args.iter().map(|a| (Some(a.value_type.clone()), a.is_mut)).collect()
        } else {
            Vec::new()
        }
    };

    for (i, arg) in expr.params.iter().skip(1).enumerate() {
        if i > 0 {
            output.push_str(", ");
        }
        // Check if arg is a type identifier - emit as string literal
        if let Some(type_name) = get_type_arg_name(arg, context) {
            output.push_str("\"");
            output.push_str(&type_name);
            output.push_str("\"");
        } else if !param_info.is_empty() {
            let (param_type, is_mut) = param_info.get(i)
                .map(|(t, m)| (t.as_ref(), *m))
                .unwrap_or((None, false));
            emit_arg_with_param_type(arg, i, hoisted, param_type, is_mut, output, ctx, context)?;
        } else {
            emit_arg_or_hoisted(arg, i, hoisted, output, ctx, context)?;
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

    // Then body - save/restore declared_vars for proper C scope handling
    let saved_declared_vars = ctx.declared_vars.clone();
    emit_body(&expr.params[1], output, indent + 1, ctx, context)?;
    ctx.declared_vars = saved_declared_vars.clone();

    output.push_str(&indent_str);
    output.push_str("}");

    // Else branch (optional)
    if expr.params.len() > 2 {
        // Check if it's an else-if (nested If) or else block
        if let NodeType::If = &expr.params[2].node_type {
            output.push_str(" else ");
            // Emit nested if without extra indentation (it handles its own)
            emit_if(&expr.params[2], output, indent, ctx, context)?;
        } else {
            output.push_str(" else {\n");
            emit_body(&expr.params[2], output, indent + 1, ctx, context)?;
            ctx.declared_vars = saved_declared_vars;
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

    // Save declared_vars before entering new scope (C allows redeclaration in new blocks)
    let saved_declared_vars = ctx.declared_vars.clone();
    emit_body(&expr.params[1], output, indent + 1, ctx, context)?;
    // Restore declared_vars after exiting scope
    ctx.declared_vars = saved_declared_vars;

    output.push_str(&indent_str);
    output.push_str("}\n");

    Ok(())
}

// Result struct for variant info extraction
struct VariantInfo {
    type_name: String,
    variant_name: String,
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
            VariantInfo { type_name: String::new(), variant_name: name.clone() }
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

fn emit_switch(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // Switch: params[0] = switch expression
    // params[1..] = alternating (case_pattern, body) pairs
    if expr.params.is_empty() {
        return Err("ccodegen: Switch requires expression".to_string());
    }

    let indent_str = "    ".repeat(indent);
    let case_indent = "    ".repeat(indent + 1);
    let body_indent = "    ".repeat(indent + 2);

    // Get the switch expression - we need to reference it for payload extraction
    let switch_expr = &expr.params[0];

    // Determine if this is an enum switch or a primitive switch
    // by scanning case patterns for Range or Pattern types
    let mut is_enum_switch = false;
    let mut has_ranges = false;
    let mut i = 1;
    while i < expr.params.len() {
        let case_pattern = &expr.params[i];
        match &case_pattern.node_type {
            NodeType::Range => {
                has_ranges = true;
            },
            NodeType::Pattern(_) => {
                is_enum_switch = true;
            },
            NodeType::Identifier(name) => {
                // Check if it has nested params (Type.Variant pattern like Color.Unknown)
                if !case_pattern.params.is_empty() {
                    is_enum_switch = true;
                }
                // Or check if it looks like an enum variant (contains a dot)
                else if name.contains('.') {
                    is_enum_switch = true;
                }
            },
            _ => {
                // DefaultCase and other patterns (literals) don't change detection
            }
        }
        i += 2;
    }

    // Emit: switch (expr) { or switch (expr.tag) {
    output.push_str(&indent_str);
    output.push_str("switch (");
    emit_expr(switch_expr, output, 0, ctx, context)?;
    if is_enum_switch && !has_ranges {
        output.push_str(".tag");
    }
    output.push_str(") {\n");

    // Process case patterns and bodies in pairs
    let mut i = 1;
    while i < expr.params.len() {
        let case_pattern = &expr.params[i];
        let case_body = if i + 1 < expr.params.len() {
            Some(&expr.params[i + 1])
        } else {
            None
        };

        match &case_pattern.node_type {
            NodeType::DefaultCase => {
                // default: { ... break; }
                output.push_str(&case_indent);
                output.push_str("default: {\n");
                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx, context)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
            NodeType::Pattern(pattern_info) => {
                // case Type_Variant: { PayloadType binding = expr.payload.Variant; ... break; }
                let info = parse_pattern_variant_name(&pattern_info.variant_name);

                output.push_str(&case_indent);
                output.push_str("case ");
                output.push_str(&info.type_name);
                output.push_str("_");
                output.push_str(&info.variant_name);
                output.push_str(": {\n");

                // Emit payload extraction: PayloadType binding_var = expr.payload.VariantName;
                // TODO: Replace __auto_type with actual type by looking up enum definition
                // This would require passing a CodegenContext with enum defs through emit functions
                output.push_str(&body_indent);
                output.push_str("__auto_type ");
                output.push_str(&pattern_info.binding_var);
                output.push_str(" = ");
                emit_expr(switch_expr, output, 0, ctx, context)?;
                output.push_str(".payload.");
                output.push_str(&info.variant_name);
                output.push_str(";\n");

                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx, context)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
            NodeType::Range => {
                // Range case: case low ... high: { ... break; }
                // Uses GCC extension for case ranges
                if case_pattern.params.len() < 2 {
                    return Err("ccodegen: Range requires start and end values".to_string());
                }

                output.push_str(&case_indent);
                output.push_str("case ");
                emit_expr(&case_pattern.params[0], output, 0, ctx, context)?;
                output.push_str(" ... ");
                emit_expr(&case_pattern.params[1], output, 0, ctx, context)?;
                output.push_str(": {\n");

                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx, context)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
            _ => {
                // Regular case: Type.Variant -> case Type_Variant: { ... break; }
                let info = get_case_variant_info(case_pattern);

                output.push_str(&case_indent);
                output.push_str("case ");
                if !info.type_name.is_empty() {
                    output.push_str(&info.type_name);
                    output.push_str("_");
                }
                output.push_str(&info.variant_name);
                output.push_str(": {\n");

                if let Some(body) = case_body {
                    emit_body(body, output, indent + 2, ctx, context)?;
                }
                output.push_str(&body_indent);
                output.push_str("break;\n");
                output.push_str(&case_indent);
                output.push_str("}\n");
            },
        }

        i += 2; // Move to next case pattern
    }

    output.push_str(&indent_str);
    output.push_str("}\n");

    Ok(())
}

fn emit_fcall(expr: &Expr, output: &mut String, indent: usize, ctx: &mut CodegenContext, context: &mut Context) -> Result<(), String> {
    // First param is the function name (or Type.method for type-qualified calls)
    if expr.params.is_empty() {
        return Err("ccodegen: FCall with no params".to_string());
    }

    // Check for type-qualified call: first param is Identifier with nested params (method name)
    // For chained access like self._len.eq(...), we need to find the deepest method name
    let (func_name, type_receiver) = match &expr.params[0].node_type {
        NodeType::Identifier(name) => {
            if expr.params[0].params.is_empty() {
                // Regular function call
                (name.clone(), None)
            } else {
                // Type-qualified call: use helper to extract method from potentially chained access
                if let Some((method_name, _depth)) = extract_type_method_and_depth(&expr.params[0]) {
                    (method_name, Some(&expr.params[0]))
                } else {
                    return Err("ccodegen: type-qualified method name not Identifier".to_string());
                }
            }
        },
        _ => return Err("ccodegen: FCall first param not Identifier".to_string()),
    };

    let indent_str = "    ".repeat(indent);

    // Hoist throwing function calls from arguments (only at statement level)
    // When indent > 0, we're at statement level and can emit hoisted calls
    let hoisted: std::collections::HashMap<usize, String> = if indent > 0 && expr.params.len() > 1 {
        let args = &expr.params[1..];
        let hoisted_vec = hoist_throwing_args(args, output, indent, ctx, context)?;
        hoisted_vec.into_iter().collect()
    } else {
        std::collections::HashMap::new()
    };

    // Hardcoded builtins (compile-time intrinsics that can't be implemented in TIL)
    match func_name.as_str() {
        // loc() - just emit empty string for now
        "loc" => {
            if context.scope_stack.lookup_struct("Str").is_some() {
                output.push_str(TIL_PREFIX);
                output.push_str("Str_from_literal(\"\")");
            } else {
                output.push_str("\"\"");
            }
            Ok(())
        },
        // type_as_str(T) - compile-time intrinsic to get type name as string
        // TODO: This doesn't work correctly for Type parameters (T: Type) because
        // we emit a single generic function, not monomorphized versions per type.
        // For now it just emits the identifier name literally.
        "type_as_str" => {
            if expr.params.len() < 2 {
                return Err("ccodegen: type_as_str requires 1 argument".to_string());
            }
            // Get the type name from the argument
            if let NodeType::Identifier(type_name) = &expr.params[1].node_type {
                if context.scope_stack.lookup_struct("Str").is_some() {
                    output.push_str(TIL_PREFIX);
                    output.push_str("Str_from_literal(\"");
                    output.push_str(type_name);
                    output.push_str("\")");
                } else {
                    output.push_str("\"");
                    output.push_str(type_name);
                    output.push_str("\"");
                }
            } else {
                output.push_str(TIL_PREFIX);
                output.push_str("Str_from_literal(\"unknown\")");
            }
            Ok(())
        },
        // size_of(T) - runtime type size lookup via til_size_of function
        // Can be called with a literal type name (size_of(Str)) or a Type variable (size_of(T))
        "size_of" => {
            if expr.params.len() < 2 {
                return Err("ccodegen: size_of requires 1 argument".to_string());
            }
            output.push_str(TIL_PREFIX);
            output.push_str("size_of(");
            // If it's a literal type name, wrap it in Str_from_literal
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
                    // Type variable - already a const char*, wrap in Str
                    output.push_str(TIL_PREFIX);
                    output.push_str("Str_from_literal(");
                    output.push_str(TIL_PREFIX);
                    output.push_str(type_name);
                    output.push_str(")");
                } else {
                    // Literal type name - create Str from the name
                    output.push_str(TIL_PREFIX);
                    output.push_str("Str_from_literal(\"");
                    output.push_str(type_name);
                    output.push_str("\")");
                }
            } else {
                // Not an identifier - emit as expression and hope it's a Type
                output.push_str(TIL_PREFIX);
                output.push_str("Str_from_literal(");
                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                output.push_str(")");
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
                output.push_str("&");
                emit_arg_or_hoisted(arg, 0, &hoisted, output, ctx, context)?;
            }
            Ok(())
        },
        // User-defined function call
        _ => {
            output.push_str(&indent_str);

            // Check for type-qualified call on FCall result: func_name(fcall_result, args...)
            // This happens for chained method calls like delimiter.len().eq(0)
            // Parser produces: FCall { params: [Identifier("eq"), FCall { ... }, LLiteral(0)] }
            if type_receiver.is_none() && expr.params.len() >= 2 {
                if let NodeType::FCall = &expr.params[1].node_type {
                    // The second param is an FCall result - use get_value_type to get its return type
                    if let Ok(fcall_ret_type) = get_value_type(context, &expr.params[1]) {
                        if let ValueType::TCustom(type_name) = &fcall_ret_type {
                            let candidate = format!("{}.{}", type_name, func_name);
                            if context.scope_stack.lookup_func(&candidate).is_some() {
                                // Emit as Type_method(fcall_result, args...)
                                output.push_str(TIL_PREFIX);
                                output.push_str(type_name);
                                output.push_str("_");
                                output.push_str(&func_name);
                                output.push_str("(");
                                // First arg is the fcall result
                                emit_expr(&expr.params[1], output, 0, ctx, context)?;
                                // Remaining args
                                for arg in expr.params.iter().skip(2) {
                                    output.push_str(", ");
                                    emit_expr(arg, output, 0, ctx, context)?;
                                }
                                output.push_str(")");
                                if indent > 0 {
                                    output.push_str(";\n");
                                }
                                return Ok(());
                            }
                        }
                    }
                }
            }

            // Check if this is a type-qualified call (Type.func(...))
            // After precomp, instance calls like i.inc() are normalized to I64.inc(i) which
            // goes through PATH C below. This path handles explicit Type.method() in source.
            if let Some(receiver) = type_receiver {
                if let NodeType::Identifier(receiver_name) = &receiver.node_type {
                    // For Type.method(), receiver_name is the type name (e.g., "I64")
                    // Look up the mangled function name
                    let mangled = format!("{}.{}", receiver_name, func_name);
                    if context.scope_stack.lookup_func(&mangled).is_some() {
                        // Emit: til_Type_method(args...)
                        output.push_str(TIL_PREFIX);
                        output.push_str(receiver_name);
                        output.push_str("_");
                        output.push_str(&func_name);
                        output.push_str("(");

                        // Get param info for mut handling
                        let param_info: Vec<(Option<ValueType>, bool)> =
                            if let Some(fd) = lookup_func_by_name(context, &mangled) {
                                fd.args.iter().map(|a| (Some(a.value_type.clone()), a.is_mut)).collect()
                            } else {
                                Vec::new()
                            };

                        // Emit arguments (skip first param which is the Type.method identifier)
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
                                let (param_type, is_mut) = param_info.get(i)
                                    .map(|(t, m)| (t.as_ref(), *m))
                                    .unwrap_or((None, false));
                                emit_arg_with_param_type(arg, i, &hoisted, param_type, is_mut, output, ctx, context)?;
                            } else {
                                emit_arg_or_hoisted(arg, i, &hoisted, output, ctx, context)?;
                            }
                        }
                        output.push_str(")");
                        if indent > 0 {
                            output.push_str(";\n");
                        }
                        return Ok(());
                    }
                }
            }

            // Check for struct construction: TypeName() -> (til_TypeName){}
            // Struct names are PascalCase, no nested identifiers, no args
            // TODO: Use proper type info from AST instead of uppercase hack (see interpreter.rs)
            if func_name.chars().next().map(|c| c.is_uppercase()).unwrap_or(false)
                && expr.params[0].params.is_empty()  // No nested params (not Type.Variant)
                && expr.params.len() == 1            // No constructor args
            {
                output.push_str("(");
                output.push_str(&til_func_name(&func_name));
                output.push_str("){}");
                if indent > 0 {
                    output.push_str(";\n");
                }
                return Ok(());
            }

            // Regular function call (not type-qualified)
            // After precomp, instance method calls like i.inc() are normalized to I64.inc(i),
            // which go through the type_receiver path above. This path is only for
            // truly non-qualified calls like add(a, b), memcpy(...), etc.
            let output_name = til_func_name(&func_name);

            // Detect and construct variadic array if needed (only at statement level)
            // At expression level (indent == 0), variadic calls are not supported directly
            let variadic_arr_var: Option<String> = if indent > 0 {
                if let Some((elem_type, regular_count)) = ctx.func_variadic_args.get(&func_name).map(|(_, e, r)| (e.clone(), *r)) {
                    let variadic_args: Vec<_> = expr.params.iter().skip(1 + regular_count).collect();
                    Some(hoist_variadic_args(&elem_type, &variadic_args, &hoisted, regular_count, output, indent, ctx, context)?)
                } else {
                    None
                }
            } else {
                None
            };

            output.push_str(&output_name);
            output.push_str("(");

            // Check if this is a variadic function call
            if let Some((_variadic_name, _elem_type, regular_count)) = ctx.func_variadic_args.get(&func_name).cloned() {
                // Emit regular args first (skip first param which is function name)
                let args: Vec<_> = expr.params.iter().skip(1).collect();
                for (i, arg) in args.iter().take(regular_count).enumerate() {
                    if i > 0 {
                        output.push_str(", ");
                    }
                    emit_arg_or_hoisted(arg, i, &hoisted, output, ctx, context)?;
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
                // After precomp, Type.method(args) calls have func_name containing a dot (e.g., "I64.inc")
                // We need to handle mut params for these.
                let param_info: Vec<(Option<ValueType>, bool)> = if func_name.contains('.') {
                    if let Some(fd) = lookup_func_by_name(context, &func_name) {
                        fd.args.iter().map(|a| (Some(a.value_type.clone()), a.is_mut)).collect()
                    } else {
                        Vec::new()
                    }
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
                        let (param_type, is_mut) = param_info.get(i)
                            .map(|(t, m)| (t.as_ref(), *m))
                            .unwrap_or((None, false));
                        emit_arg_with_param_type(arg, i, &hoisted, param_type, is_mut, output, ctx, context)?;
                    } else {
                        emit_arg_or_hoisted(arg, i, &hoisted, output, ctx, context)?;
                    }
                }
            }

            output.push_str(")");
            // Only add statement terminator if this is a statement (indent > 0)
            if indent > 0 {
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

/// Extract method name and receiver depth from a type-qualified expression.
/// For `self._len.eq(...)`, returns ("eq", 2) meaning method is "eq" and receiver has 2 levels.
/// For `self.method(...)`, returns ("method", 1).
fn extract_type_method_and_depth(first_param: &Expr) -> Option<(String, usize)> {
    if let NodeType::Identifier(_) = &first_param.node_type {
        // AST structure for chained access is FLAT: a.b.c becomes
        // Identifier("a") { params: [Identifier("b"), Identifier("c")] }
        // The method is the LAST param in the list
        let depth = first_param.params.len();
        if depth > 0 {
            if let NodeType::Identifier(method_name) = &first_param.params[depth - 1].node_type {
                return Some((method_name.clone(), depth));
            }
        }
    }
    None
}

/// Create a clone of an expression with the deepest nested identifier removed.
/// For `self._len.eq`, returns `self._len` (with eq removed from the chain).
fn clone_without_deepest_method(expr: &Expr, depth: usize) -> Expr {
    // AST structure is FLAT: a.b.c is Identifier("a") { params: [Identifier("b"), Identifier("c")] }
    // To remove the method (last param), we just pop the last element from params
    let mut result = expr.clone();
    if depth > 0 && !result.params.is_empty() {
        result.params.pop();  // Remove the last (method) identifier
    }
    result
}

fn emit_literal(lit: &Literal, output: &mut String, context: &Context) -> Result<(), String> {
    match lit {
        Literal::Str(s) => {
            let has_str = context.scope_stack.lookup_struct("Str").is_some();
            if has_str {
                output.push_str(TIL_PREFIX);
                output.push_str("Str_from_literal(\"");
            } else {
                output.push('"');
            }
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
            if has_str {
                output.push_str("\")");
            } else {
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
