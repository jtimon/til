// Killer phase: Removes unused function declarations from the AST.
// This phase runs after precomp (UFCS already resolved), before interpreter/builder.

use crate::rs::init::Context;
use crate::rs::parser::{Declaration, Expr, NodeType, SStructDef};
use std::collections::{HashMap, HashSet};

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
/// Returns (reachable_set, needs_variadic_support).
fn compute_reachable(
    context: &Context,
    roots: &HashSet<String>,
    e: &Expr,
) -> Result<(HashSet<String>, bool), String> {
    let mut reachable: HashSet<String> = HashSet::new();
    let mut worklist: Vec<String> = Vec::new();
    let mut needs_variadic_support = false;

    // Add all roots
    for root in roots {
        mark_reachable(root.clone(), &mut reachable, &mut worklist);
    }

    while let Some(func_name) = worklist.pop() {
        // Find what this function calls using scope_stack
        if let Some(func_def) = context.scope_stack.lookup_func(&func_name) {
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
            // Struct constructor - collect calls from default values
            let mut called: HashSet<String> = HashSet::new();
            for default_expr in struct_def.default_values.values() {
                collect_called_functions(default_expr, &mut called);
            }
            for called_func in called {
                mark_reachable(called_func, &mut reachable, &mut worklist);
            }
        } else if context.scope_stack.lookup_enum(&func_name).is_some() {
            // Enum constructor - no body to walk
        } else {
            return Err(e.lang_error(&context.path, "killer", &format!("no body found for '{}'", func_name)));
        }
    }

    Ok((reachable, needs_variadic_support))
}

// ---------- Main entry point

/// Remove unused function declarations from the AST.
/// This runs after precomp, so UFCS is already resolved.
pub fn killer_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Only process Body nodes at the top level
    if let NodeType::Body = &e.node_type {
        // Step 0: Register all functions and structs from the transformed AST into scope_stack
        // This mirrors what the interpreter does - it builds scope_stack as it walks the AST
        register_declarations(context, e);

        // Step 1: Determine root functions based on mode
        let mut roots: HashSet<String> = HashSet::new();

        if context.mode_def.needs_main_proc {
            // CLI mode: root is main
            roots.insert("main".to_string());
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
        }
        // else: lib/pure mode - no roots, all user functions get removed

        // Step 2: Compute reachable functions (transitive closure)
        // First pass: compute reachable and detect if variadic support is needed
        let (mut reachable, needs_variadic_support) = compute_reachable(context, &roots, e)?;

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
            let (new_reachable, _) = compute_reachable(context, &extended_roots, e)?;
            reachable = new_reachable;
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
                            // Struct - rebuild without unreachable methods
                            let new_struct = rebuild_struct_without_unreachable_methods(decl, struct_def, &reachable);
                            new_params.push(new_struct);
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
