// Scavenger phase: Removes unused function declarations from the AST.
// This phase runs after precomp (UFCS already resolved), before interpreter/builder.

use crate::rs::init::Context;
use crate::rs::parser::{Declaration, Expr, NodeType, SStructDef, ValueType};
use std::collections::{HashMap, HashSet};

/// Result type for compute_reachable
pub struct ComputeReachableResult {
    pub reachable: HashSet<String>,
    pub used_types: HashSet<String>,
    pub needs_variadic_support: bool,
}

/// Types required by ext.c - these must be kept if ANY external function is reachable
const EXT_C_TYPES: &[&str] = &["Bool", "Str", "I64", "U8", "AllocError", "Array"];

// ---------- Type collection helpers

/// Extract type name from a ValueType, if it's a custom or multi type
fn extract_type_name(vt: &ValueType) -> Option<String> {
    match vt {
        ValueType::TCustom(name) => Some(name.clone()),
        ValueType::TMulti(name) => Some(name.clone()),
        _ => None,
    }
}

/// Collect all type names used in an expression (declarations, constructors, etc.)
/// Uses context to look up whether names refer to structs/enums.
fn collect_used_types_from_expr(context: &Context, e: &Expr, used_types: &mut HashSet<String>) {
    match &e.node_type {
        NodeType::Declaration(decl) => {
            if let Some(type_name) = extract_type_name(&decl.value_type) {
                used_types.insert(type_name);
            }
        }
        NodeType::FCall => {
            // Constructor calls - check if the function name is a known struct
            if !e.params.is_empty() {
                let name = get_combined_name_from_identifier(&e.params[0]);
                if !name.is_empty() && !name.contains('.') {
                    // Check if this is a struct constructor
                    if context.scope_stack.lookup_struct(&name).is_some() {
                        used_types.insert(name);
                    }
                }
            }
        }
        NodeType::Identifier(name) => {
            // Type references - check if this is a known struct or enum
            if !name.is_empty() && e.params.is_empty() {
                if context.scope_stack.lookup_struct(name).is_some()
                    || context.scope_stack.lookup_enum(name).is_some() {
                    used_types.insert(name.clone());
                }
            }
        }
        _ => {}
    }
    // Recurse into all params
    for param in &e.params {
        collect_used_types_from_expr(context, param, used_types);
    }
}

/// Collect all type names from a function definition (args, return types, throw types, body)
fn collect_used_types_from_func(context: &Context, func_def: &crate::rs::parser::SFuncDef, used_types: &mut HashSet<String>) {
    // Collect from arguments
    for arg in &func_def.args {
        if let Some(type_name) = extract_type_name(&arg.value_type) {
            used_types.insert(type_name);
        }
    }
    // Collect from return types
    for ret_type in &func_def.return_types {
        if let Some(type_name) = extract_type_name(ret_type) {
            used_types.insert(type_name);
        }
    }
    // Collect from throw types
    for throw_type in &func_def.throw_types {
        if let Some(type_name) = extract_type_name(throw_type) {
            used_types.insert(type_name);
        }
    }
    // Collect from body
    for stmt in &func_def.body {
        collect_used_types_from_expr(context, stmt, used_types);
    }
}

// ---------- Helper functions

/// Rebuild a struct without unreachable methods
fn rebuild_struct_without_unreachable_methods(decl: &Declaration, struct_def: &SStructDef, reachable: &HashSet<String>) -> Expr {
    let struct_name = &decl.name;
    let mut new_members: Vec<Declaration> = Vec::new();
    let mut new_default_values: HashMap<String, Expr> = HashMap::new();

    for member_decl in &struct_def.members {
        let full_name = format!("{}.{}", struct_name, member_decl.name);

        // Check if this member has a FuncDef default value (i.e., it's a method)
        if let Some(default_expr) = struct_def.default_values.get(&member_decl.name) {
            if let NodeType::FuncDef(func_def) = &default_expr.node_type {
                // Method - check if reachable or external
                if func_def.is_ext() || reachable.contains(&full_name) {
                    new_members.push(member_decl.clone());
                    new_default_values.insert(member_decl.name.clone(), default_expr.clone());
                }
            } else {
                // Not a FuncDef - keep it (regular field with default value)
                new_members.push(member_decl.clone());
                new_default_values.insert(member_decl.name.clone(), default_expr.clone());
            }
        } else {
            // No default value - keep the member
            new_members.push(member_decl.clone());
        }
    }

    let new_struct_def = SStructDef {
        members: new_members,
        default_values: new_default_values,
    };

    let new_struct_expr = Expr {
        node_type: NodeType::StructDef(new_struct_def),
        params: vec![],
        line: 0,
        col: 0,
    };

    Expr {
        node_type: NodeType::Declaration(decl.clone()),
        params: vec![new_struct_expr],
        line: 0,
        col: 0,
    }
}

/// Recursively collect all function names called within an expression.
fn collect_called_functions(e: &Expr, called: &mut HashSet<String>) {
    match &e.node_type {
        NodeType::FCall => {
            // After precomp, function calls have params[0] as Identifier(function_name)
            if !e.params.is_empty() {
                let full_name = get_combined_name_from_identifier(&e.params[0]);
                if !full_name.is_empty() {
                    called.insert(full_name);
                }
            }
            // Recurse into arguments
            for param in &e.params[1..] {
                collect_called_functions(param, called);
            }
        }
        NodeType::FuncDef(func_def) => {
            // Recurse into function body
            for stmt in &func_def.body {
                collect_called_functions(stmt, called);
            }
        }
        NodeType::Catch => {
            // Catch has params[0]=name, params[1]=type, params[2]=body
            // Only recurse into body - type is not a function call
            if e.params.len() >= 3 {
                collect_called_functions(&e.params[2], called);
            }
        }
        _ => {
            // Recurse into all params
            for param in &e.params {
                collect_called_functions(param, called);
            }
        }
    }
}

/// Get combined name from an identifier expression (handles a.b.c chains)
fn get_combined_name_from_identifier(e: &Expr) -> String {
    match &e.node_type {
        NodeType::Identifier(name) => {
            if e.params.is_empty() {
                name.clone()
            } else {
                // Has nested params like a.b.c
                let mut parts = vec![name.clone()];
                for param in &e.params {
                    let nested = get_combined_name_from_identifier(param);
                    if !nested.is_empty() {
                        parts.push(nested);
                    }
                }
                parts.join(".")
            }
        }
        _ => String::new(),
    }
}

/// Helper to add a function to both reachable and worklist at the same time
fn mark_reachable(
    func_name: String,
    reachable: &mut HashSet<String>,
    worklist: &mut Vec<String>
) {
    if !reachable.contains(&func_name) {
        reachable.insert(func_name.clone());
        worklist.push(func_name);
    }
}

/// Recursively register all functions and structs from the AST into context.scope_stack.
/// This mirrors what the interpreter does - it registers declarations as it walks the AST.
fn register_declarations_recursive(context: &mut Context, e: &Expr) {
    match &e.node_type {
        NodeType::Declaration(decl) => {
            if !e.params.is_empty() {
                if let NodeType::FuncDef(func_def) = &e.params[0].node_type {
                    // Function declaration
                    context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
                    // Recurse into function body for local declarations
                    for stmt in &func_def.body {
                        register_declarations_recursive(context, stmt);
                    }
                } else if let NodeType::StructDef(struct_def) = &e.params[0].node_type {
                    // Struct declaration
                    context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
                    // Struct methods
                    for (member_name, default_expr) in &struct_def.default_values {
                        if let NodeType::FuncDef(func_def) = &default_expr.node_type {
                            let full_name = format!("{}.{}", decl.name, member_name);
                            context.scope_stack.declare_func(full_name, func_def.clone());
                            // Recurse into method body for local declarations
                            for stmt in &func_def.body {
                                register_declarations_recursive(context, stmt);
                            }
                        }
                    }
                }
            }
        }
        NodeType::FuncDef(func_def) => {
            // Anonymous function - recurse into body
            for stmt in &func_def.body {
                register_declarations_recursive(context, stmt);
            }
        }
        _ => {}
    }
    // Recurse into all params
    for param in &e.params {
        register_declarations_recursive(context, param);
    }
}

/// Register all functions and structs from the AST into context.scope_stack.
fn register_declarations(context: &mut Context, e: &Expr) {
    register_declarations_recursive(context, e);
}

/// Compute the transitive closure of reachable functions starting from roots.
/// Uses context.scope_stack.lookup_func() to find function bodies.
/// Returns ComputeReachableResult with reachable set and needs_variadic_support flag.
fn compute_reachable(
    context: &Context,
    roots: &HashSet<String>,
    e: &Expr,
) -> Result<ComputeReachableResult, String> {
    let mut reachable: HashSet<String> = HashSet::new();
    let mut used_types: HashSet<String> = HashSet::new();
    let mut worklist: Vec<String> = Vec::new();
    let mut needs_variadic_support = false;

    // Add all roots
    for root in roots {
        mark_reachable(root.clone(), &mut reachable, &mut worklist);
    }

    while let Some(func_name) = worklist.pop() {
        // Find what this function calls using scope_stack
        if let Some(func_def) = context.scope_stack.lookup_func(&func_name) {
            // Collect types used by this function
            collect_used_types_from_func(context, &func_def, &mut used_types);

            // Check if this function has variadic parameters (TMulti)
            for arg in &func_def.args {
                if let crate::rs::parser::ValueType::TMulti(_) = &arg.value_type {
                    needs_variadic_support = true;
                    break;
                }
            }

            if func_def.is_ext() {
                // External function - no body to walk
                continue;
            }
            let mut called: HashSet<String> = HashSet::new();
            for stmt in &func_def.body {
                collect_called_functions(stmt, &mut called);
            }
            // Add newly discovered functions
            for called_func in called {
                mark_reachable(called_func, &mut reachable, &mut worklist);
            }
        } else if let Some(struct_def) = context.scope_stack.lookup_struct(&func_name) {
            // Struct constructor - collect calls from field initializers only
            // (skip FuncDef values which are methods - their bodies should only be walked if the method itself is reachable)
            let mut called: HashSet<String> = HashSet::new();
            for default_expr in struct_def.default_values.values() {
                if let NodeType::FuncDef(_) = &default_expr.node_type {
                    // Skip methods - they're handled separately via their qualified names
                    continue;
                }
                collect_called_functions(default_expr, &mut called);
            }
            for called_func in called {
                mark_reachable(called_func, &mut reachable, &mut worklist);
            }
        } else {
            // Check if this is an enum constructor (e.g., Color.Name) or enum type reference
            let parts: Vec<&str> = func_name.split('.').collect();
            if parts.len() == 2 && context.scope_stack.lookup_enum(parts[0]).is_some() {
                // Enum constructor - no body to walk
                continue;
            }
            // Check if this is just an enum type name (e.g., ValueType without variant)
            if parts.len() == 1 && context.scope_stack.lookup_enum(&func_name).is_some() {
                // Enum type reference - no body to walk
                continue;
            }

            // Check if this is an unresolved UFCS call (e.g., s.len or obj.field.len where s/obj is a variable)
            // This happens when precomp couldn't determine the type (e.g., pattern bindings in switch)
            // In this case, parts[0] is a variable name, not a type name
            let method_name = parts.last().unwrap(); // Last part is the method name
            let is_unresolved_ufcs = if parts.len() >= 2 {
                let maybe_var = parts[0];
                // If first part is NOT a known struct/enum, it's likely a variable
                context.scope_stack.lookup_struct(maybe_var).is_none()
                    && context.scope_stack.lookup_enum(maybe_var).is_none()
            } else {
                // Single name - could be a method that precomp couldn't resolve
                // (e.g., "eq" when called on a value whose type wasn't known)
                true
            };

            if is_unresolved_ufcs {
                // Try to find the method on built-in types first
                let builtin_types = ["Str", "I64", "Bool", "U8", "F64", "Array", "Vec", "List", "Map", "Set"];
                let mut found = false;
                for builtin in &builtin_types {
                    let full_method = format!("{}.{}", builtin, method_name);
                    if context.scope_stack.lookup_func(&full_method).is_some() {
                        // Found a matching method - mark it reachable instead
                        mark_reachable(full_method, &mut reachable, &mut worklist);
                        found = true;
                        break;
                    }
                }
                // Also check user-defined structs for the method
                if !found {
                    for struct_name in context.scope_stack.get_all_struct_names() {
                        let full_method = format!("{}.{}", struct_name, method_name);
                        if context.scope_stack.lookup_func(&full_method).is_some() {
                            mark_reachable(full_method, &mut reachable, &mut worklist);
                            found = true;
                            break;
                        }
                    }
                }
                if found {
                    continue;
                }
            }

            return Err(e.lang_error(&context.path, "scavenger", &format!("no body found for '{}'", func_name)));
        }
    }

    // Always add ext.c required types since ext.c is always included in generated C
    for ext_type in EXT_C_TYPES {
        used_types.insert(ext_type.to_string());
    }

    // Add struct types when their methods are reachable (e.g., Foo.bar reachable -> Foo is used)
    for func_name in &reachable {
        if let Some(dot_pos) = func_name.find('.') {
            let struct_name = &func_name[..dot_pos];
            // Only add if this is actually a struct (not an enum)
            if context.scope_stack.lookup_struct(struct_name).is_some() {
                used_types.insert(struct_name.to_string());
            }
        }
    }

    // Now compute transitive closure of used types (struct field types, enum payload types)
    let mut type_worklist: Vec<String> = used_types.iter().cloned().collect();
    while let Some(type_name) = type_worklist.pop() {
        // Check struct field types
        if let Some(struct_def) = context.scope_stack.lookup_struct(&type_name) {
            for member in &struct_def.members {
                if let Some(field_type) = extract_type_name(&member.value_type) {
                    if !used_types.contains(&field_type) {
                        used_types.insert(field_type.clone());
                        type_worklist.push(field_type);
                    }
                }
            }
        }
        // Check enum payload types
        if let Some(enum_def) = context.scope_stack.lookup_enum(&type_name) {
            for variant in &enum_def.variants {
                if let Some(payload_type) = &variant.payload_type {
                    if let Some(payload_type_name) = extract_type_name(payload_type) {
                        if !used_types.contains(&payload_type_name) {
                            used_types.insert(payload_type_name.clone());
                            type_worklist.push(payload_type_name);
                        }
                    }
                }
            }
        }
    }

    Ok(ComputeReachableResult { reachable, used_types, needs_variadic_support })
}

// ---------- Main entry point

/// Remove unused function declarations from the AST.
/// This runs after precomp, so UFCS is already resolved.
pub fn scavenger_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Only process Body nodes at the top level
    if let NodeType::Body = &e.node_type {
        // Step 0: Register all functions and structs from the transformed AST into scope_stack
        // This mirrors what the interpreter does - it builds scope_stack as it walks the AST
        register_declarations(context, e);

        // Step 1: Determine root functions based on mode
        let mut roots: HashSet<String> = HashSet::new();

        if context.mode_def.needs_main_proc {
            // CLI mode: root is main plus global variable initializers
            roots.insert("main".to_string());
            // Global variable initializers are also executed in main(), so their calls are roots
            for stmt in &e.params {
                if let NodeType::Declaration(_decl) = &stmt.node_type {
                    if !stmt.params.is_empty() {
                        if let NodeType::FuncDef(_) = &stmt.params[0].node_type {
                            // Skip function declarations
                        } else {
                            // Non-function declaration initializer - collect calls from it
                            collect_called_functions(&stmt.params[0], &mut roots);
                        }
                    }
                }
            }
        } else if context.mode_def.allows_base_calls || context.mode_def.allows_base_anything {
            // script/safe_script/test: all top-level non-declaration statements are roots
            // Walk them to find called functions
            for stmt in &e.params {
                match &stmt.node_type {
                    NodeType::Declaration(_decl) => {
                        // Skip declarations - only their initializers matter if not functions
                        if !stmt.params.is_empty() {
                            if let NodeType::FuncDef(_) = &stmt.params[0].node_type {
                                // Skip function declarations - they're not roots themselves
                            } else {
                                // Non-function declaration initializer - collect calls from it
                                collect_called_functions(&stmt.params[0], &mut roots);
                            }
                        }
                    }
                    _ => {
                        // Non-declaration statement (function call, assignment, etc.)
                        collect_called_functions(stmt, &mut roots);
                    }
                }
            }
        } else {
            // lib/pure mode - globals are still initialized in main(), so include those calls
            for stmt in &e.params {
                if let NodeType::Declaration(_decl) = &stmt.node_type {
                    if !stmt.params.is_empty() {
                        if let NodeType::FuncDef(_) = &stmt.params[0].node_type {
                            // Skip function declarations
                        } else {
                            // Non-function declaration initializer - collect calls from it
                            collect_called_functions(&stmt.params[0], &mut roots);
                        }
                    }
                }
            }
        }

        // Step 2: Compute reachable functions (transitive closure)
        // First pass: compute reachable and detect if variadic support is needed
        let cr_result = compute_reachable(context, &roots, e)?;
        let mut reachable = cr_result.reachable;
        let mut used_types = cr_result.used_types;
        let needs_variadic_support = cr_result.needs_variadic_support;

        // If any variadic function was found, add Array methods and recompute closure
        // to include their dependencies (like U8.from_i64)
        if needs_variadic_support {
            let array_methods = vec![
                "Array.new".to_string(),
                "Array.set".to_string(),
                "Array.get".to_string(),
                "Array.delete".to_string(),
                "Array.len".to_string(),
            ];
            // Add Array methods to roots and recompute
            let mut extended_roots = roots.clone();
            for method in &array_methods {
                extended_roots.insert(method.clone());
            }
            let new_cr_result = compute_reachable(context, &extended_roots, e)?;
            reachable = new_cr_result.reachable;
            used_types = new_cr_result.used_types;
            // Ignore needs_variadic_support on second pass
        }

        // Step 3: Build new AST - only include reachable function declarations
        // For structs, rebuild them without unreachable methods
        let mut new_params: Vec<Expr> = Vec::new();
        for stmt in &e.params {
            match &stmt.node_type {
                NodeType::Declaration(decl) => {
                    if !stmt.params.is_empty() {
                        if let NodeType::FuncDef(func_def) = &stmt.params[0].node_type {
                            // Function declaration - keep if reachable or external
                            if func_def.is_ext() || reachable.contains(&decl.name) {
                                new_params.push(stmt.clone());
                            }
                        } else if let NodeType::StructDef(struct_def) = &stmt.params[0].node_type {
                            // Struct - only keep if type is used, rebuild without unreachable methods
                            if used_types.contains(&decl.name) {
                                let new_struct = rebuild_struct_without_unreachable_methods(decl, struct_def, &reachable);
                                new_params.push(new_struct);
                            }
                        } else {
                            // Non-function, non-struct declaration - always keep
                            new_params.push(stmt.clone());
                        }
                    } else {
                        // Declaration without initializer - always keep
                        new_params.push(stmt.clone());
                    }
                }
                _ => {
                    // Non-declaration - always keep
                    new_params.push(stmt.clone());
                }
            }
        }

        return Ok(Expr::new_clone(e.node_type.clone(), e, new_params));
    }

    // Not a Body node - return unchanged
    Ok(e.clone())
}
