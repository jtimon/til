// Scavenger phase: Removes unused function declarations from the AST.
// This phase runs after precomp (UFCS already resolved), before interpreter/builder.

use crate::rs::init::Context;
use crate::rs::parser::{Declaration, Expr, NodeType, StructDef, ValueType};
use std::collections::{HashMap, HashSet};

/// Result type for compute_reachable
pub struct ComputeReachableResult {
    pub reachable: HashSet<String>,
    pub used_types: HashSet<String>,
    pub needs_variadic_support: bool,
}

/// Types required by ext.c - these must be kept if ANY external function is reachable
const EXT_C_TYPES: &[&str] = &["Bool", "Str", "I64", "U8", "BadAlloc", "Array"];

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
fn collect_used_types_from_expr(context: &Context, e: &Expr, used_types: &mut HashSet<String>) -> Result<(), String> {
    match &e.node_type {
        NodeType::Declaration(decl) => {
            if let Some(type_name) = extract_type_name(&decl.value_type) {
                used_types.insert(type_name);
            }
        }
        NodeType::FCall(_) => {
            // Constructor calls - check if the function name is a known struct
            if !e.params.is_empty() {
                let name = get_combined_name_from_identifier(e.params.get(0).unwrap());
                if !name.is_empty() && !name.contains('.') {
                    // Check if this is a struct constructor
                    if context.scope_stack.has_struct(&name) {
                        used_types.insert(name);
                    }
                }
            }
        }
        NodeType::Identifier(name) => {
            // Type references - check if this is a known struct or enum
            if !name.is_empty() && e.params.is_empty() {
                if context.scope_stack.has_struct(name)
                    || context.scope_stack.has_enum(name) {
                    used_types.insert(name.clone());
                }
            }
        }
        _ => {}
    }
    // Recurse into all params
    for param in &e.params {
        collect_used_types_from_expr(context, param, used_types)?;
    }
    Ok(())
}

/// Collect all type names from a function definition (args, return types, throw types, body)
fn collect_used_types_from_func(context: &Context, func_def: &crate::rs::parser::FuncDef, used_types: &mut HashSet<String>) -> Result<(), String> {
    // Collect from arguments
    for arg in &func_def.sig.args {
        if let Some(type_name) = extract_type_name(&arg.value_type) {
            used_types.insert(type_name);
        }
    }
    // Collect from return types
    for ret_type in &func_def.sig.return_types {
        if let Some(ret_type_name) = extract_type_name(ret_type) {
            used_types.insert(ret_type_name);
        }
    }
    // Collect from throw types
    for throw_type in &func_def.sig.throw_types {
        if let Some(throw_type_name) = extract_type_name(throw_type) {
            used_types.insert(throw_type_name);
        }
    }
    // Collect from body
    for stmt in &func_def.body {
        collect_used_types_from_expr(context, stmt, used_types)?;
    }
    Ok(())
}

// ---------- Helper functions

/// Rebuild a struct without unreachable methods
fn rebuild_struct_without_unreachable_methods(decl: &Declaration, struct_def: &StructDef, reachable: &HashSet<String>) -> Expr {
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

    // Also rebuild ns, pruning unreachable methods
    let new_ns = rebuild_namespace_without_unreachable_methods(&struct_def.ns, struct_name, reachable);

    let new_struct_def = StructDef {
        members: new_members,
        default_values: new_default_values,
        ns: new_ns,
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

/// Issue #108: Rebuild a namespace definition, keeping only reachable methods
fn rebuild_namespace_without_unreachable_methods(ns_def: &crate::rs::parser::NamespaceDef, type_name: &str, reachable: &HashSet<String>) -> crate::rs::parser::NamespaceDef {
    let mut new_members: Vec<Declaration> = Vec::new();
    let mut new_default_values: HashMap<String, Expr> = HashMap::new();

    for member_decl in &ns_def.members {
        let full_name = format!("{}.{}", type_name, member_decl.name);

        // Check if this member has a FuncDef default value (i.e., it's a method)
        if let Some(default_expr) = ns_def.default_values.get(&member_decl.name) {
            if let NodeType::FuncDef(func_def) = &default_expr.node_type {
                // Method - check if reachable or external
                if func_def.is_ext() || reachable.contains(&full_name) {
                    new_members.push(member_decl.clone());
                    new_default_values.insert(member_decl.name.clone(), default_expr.clone());
                }
            } else {
                // Not a FuncDef - keep it (regular constant)
                new_members.push(member_decl.clone());
                new_default_values.insert(member_decl.name.clone(), default_expr.clone());
            }
        } else {
            // No default value - keep the member
            new_members.push(member_decl.clone());
        }
    }

    crate::rs::parser::NamespaceDef {
        members: new_members,
        default_values: new_default_values,
    }
}

/// Issue #91: Recursively collect function names passed as FuncSig arguments.
/// When `apply_op(add2, 3, 5)` is called and `apply_op`'s first param is FuncSig-typed,
/// `add2` is a function reference that must be marked reachable.
/// Also handles `return add2` where the return type is FuncSig.
fn collect_func_ptr_references(e: &Expr, context: &Context, refs: &mut HashSet<String>) -> Result<(), String> {
    match &e.node_type {
        NodeType::FCall(_) => {
            if !e.params.is_empty() {
                let func_name = get_combined_name_from_identifier(e.params.get(0).unwrap());
                if !func_name.is_empty() {
                    if let Some(func_def) = context.scope_stack.lookup_func(&func_name) {
                        for (i, arg) in func_def.sig.args.iter().enumerate() {
                            if let crate::rs::parser::ValueType::TCustom(ref type_name) = arg.value_type {
                                if let Some(type_sym) = context.scope_stack.lookup_symbol(type_name) {
                                    if type_sym.value_type == crate::rs::parser::ValueType::TType(crate::rs::parser::TTypeDef::TFuncSig) {
                                        // This parameter is a function pointer - check if the argument is a function name
                                        if let Some(arg_expr) = e.params.get(i + 1) {
                                            let arg_name = get_combined_name_from_identifier(arg_expr);
                                            if !arg_name.is_empty() {
                                                refs.insert(arg_name);
                                            } else if let NodeType::FuncDef(ref _anon_fd) = arg_expr.node_type {
                                                // Issue #91: Anonymous inline function - look up temp name
                                                if let Some(temp_name) = context.anon_func_map.get(&(arg_expr.line, arg_expr.col)) {
                                                    refs.insert(temp_name.clone());
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // Recurse into arguments
            for param in &e.params[1..] {
                collect_func_ptr_references(param, context, refs)?;
            }
        }
        // Issue #91: `return add2` where add2 is a function name
        NodeType::Return => {
            if !e.params.is_empty() {
                let ret_expr = e.params.get(0).unwrap();
                let ret_name = get_combined_name_from_identifier(ret_expr);
                if !ret_name.is_empty() && context.scope_stack.has_func(&ret_name) {
                    refs.insert(ret_name);
                }
            }
        }
        // Issue #91: `op := get_op(0)` - declaration with FuncSig type where
        // the initializer is an FCall that returns a function
        NodeType::Declaration(_) => {
            for param in &e.params {
                collect_func_ptr_references(param, context, refs)?;
            }
        }
        NodeType::FuncDef(func_def) => {
            for stmt in &func_def.body {
                collect_func_ptr_references(stmt, context, refs)?;
            }
        }
        NodeType::Catch => {
            if e.params.len() >= 3 {
                collect_func_ptr_references(e.params.get(2).unwrap(), context, refs)?;
            }
        }
        _ => {
            for param in &e.params {
                collect_func_ptr_references(param, context, refs)?;
            }
        }
    }
    Ok(())
}

/// Recursively collect all function names called within an expression.
fn collect_called_functions(e: &Expr, called: &mut HashSet<String>) -> Result<(), String> {
    match &e.node_type {
        NodeType::FCall(_) => {
            // After precomp, function calls have params[0] as Identifier(function_name)
            if !e.params.is_empty() {
                let full_name = get_combined_name_from_identifier(e.params.get(0).unwrap());
                if !full_name.is_empty() {
                    called.insert(full_name);
                }
            }
            // Recurse into arguments
            for param in &e.params[1..] {
                collect_called_functions(param, called)?;
            }
        }
        NodeType::FuncDef(func_def) => {
            // Recurse into function body
            for stmt in &func_def.body {
                collect_called_functions(stmt, called)?;
            }
        }
        NodeType::Catch => {
            // Catch has params[0]=name, params[1]=type, params[2]=body
            // Only recurse into body - type is not a function call
            if e.params.len() >= 3 {
                collect_called_functions(e.params.get(2).unwrap(), called)?;
            }
        }
        _ => {
            // Recurse into all params
            for param in &e.params {
                collect_called_functions(param, called)?;
            }
        }
    }
    Ok(())
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
fn register_declarations_recursive(context: &mut Context, e: &Expr) -> Result<(), String> {
    match &e.node_type {
        NodeType::Declaration(decl) => {
            if !e.params.is_empty() {
                let inner = e.params.get(0).unwrap();
                match &inner.node_type {
                    NodeType::FuncDef(func_def) => {
                        // Function declaration
                        context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
                        // Recurse into function body for local declarations
                        for stmt in &func_def.body {
                            register_declarations_recursive(context, stmt)?;
                        }
                    }
                    NodeType::StructDef(struct_def) => {
                        // Struct declaration
                        // Issue #108: Don't overwrite if struct already exists with merged namespace members
                        if context.scope_stack.lookup_struct(&decl.name).is_none() {
                            context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
                        }
                        // Struct methods
                        for (member_name, default_expr) in &struct_def.default_values {
                            if let NodeType::FuncDef(func_def) = &default_expr.node_type {
                                let full_name = format!("{}.{}", decl.name, member_name);
                                context.scope_stack.declare_func(full_name, func_def.clone());
                                for stmt in &func_def.body {
                                    register_declarations_recursive(context, stmt)?;
                                }
                            }
                        }
                        // Namespace methods
                        for (member_name, ns_default_expr) in &struct_def.ns.default_values {
                            if let NodeType::FuncDef(func_def) = &ns_default_expr.node_type {
                                let ns_full_name = format!("{}.{}", decl.name, member_name);
                                context.scope_stack.declare_func(ns_full_name, func_def.clone());
                                for stmt in &func_def.body {
                                    register_declarations_recursive(context, stmt)?;
                                }
                            }
                        }
                    }
                    _ => {}
                }
            }
        }
        NodeType::FuncDef(func_def) => {
            // Anonymous function - recurse into body
            for stmt in &func_def.body {
                register_declarations_recursive(context, stmt)?;
            }
        }
        _ => {}
    }
    // Recurse into all params
    for param in &e.params {
        register_declarations_recursive(context, param)?;
    }
    Ok(())
}

/// Register all functions and structs from the AST into context.scope_stack.
fn register_declarations(context: &mut Context, e: &Expr) -> Result<(), String> {
    register_declarations_recursive(context, e)
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
            collect_used_types_from_func(context, &func_def, &mut used_types)?;

            // Check if this function has variadic parameters (TMulti)
            for arg in &func_def.sig.args {
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
                collect_called_functions(stmt, &mut called)?;
            }
            // Issue #91: Remove parameter names from called set - they're variables, not functions
            // This handles function-pointer parameters like `op` in `func(op: BinaryIntOp, ...)`
            for arg in &func_def.sig.args {
                if !arg.name.is_empty() {
                    called.remove(&arg.name);
                }
            }
            // Issue #91: Collect function references passed as FuncSig arguments
            for stmt in &func_def.body {
                collect_func_ptr_references(stmt, context, &mut called)?;
            }
            // Add newly discovered functions
            for called_func in called {
                mark_reachable(called_func, &mut reachable, &mut worklist);
            }
        } else if let Some(struct_def) = context.scope_stack.lookup_struct(&func_name) {
            // Bug #150: Struct constructor is called, so the struct type is used
            used_types.insert(func_name.clone());
            // Struct constructor - collect calls from field initializers only
            // (skip FuncDef values which are methods - their bodies should only be walked if the method itself is reachable)
            let mut struct_called: HashSet<String> = HashSet::new();
            for default_expr in struct_def.default_values.values() {
                if let NodeType::FuncDef(_) = &default_expr.node_type {
                    // Skip methods - they're handled separately via their qualified names
                    continue;
                }
                collect_called_functions(default_expr, &mut struct_called)?;
            }
            for called_func in struct_called {
                mark_reachable(called_func, &mut reachable, &mut worklist);
            }
        } else {
            // Check if this is an enum constructor (e.g., Color.Name) or enum type reference
            let parts: Vec<&str> = func_name.split('.').collect();
            if parts.len() == 2 && context.scope_stack.has_enum(parts[0]) {
                // Enum constructor - no body to walk
                continue;
            }
            // Check if this is just an enum type name (e.g., ValueType without variant)
            if parts.len() == 1 && context.scope_stack.has_enum(&func_name) {
                // Enum type reference - no body to walk
                continue;
            }

            // Issue #91: Check if this is a function pointer variable (e.g., op := get_op(0))
            // Function pointer variables are symbols with TFunction type but no func def
            if let Some(sym) = context.scope_stack.lookup_symbol(&func_name) {
                if let ValueType::TFunction(_) = sym.value_type {
                    // Function pointer variable - the actual function it points to
                    // should already be reachable through the assignment source
                    continue;
                }
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
                    let builtin_full_method = format!("{}.{}", builtin, method_name);
                    if context.scope_stack.has_func(&builtin_full_method) {
                        // Found a matching method - mark it reachable instead
                        mark_reachable(builtin_full_method, &mut reachable, &mut worklist);
                        found = true;
                        break;
                    }
                }
                // Also check user-defined structs for the method
                if !found {
                    for struct_name in context.scope_stack.get_all_struct_names() {
                        let user_full_method = format!("{}.{}", struct_name, method_name);
                        if context.scope_stack.has_func(&user_full_method) {
                            mark_reachable(user_full_method, &mut reachable, &mut worklist);
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

    // HeapState functions called by ext.c (til_malloc/til_free/til_exit) - not visible in TIL source
    for hs_func in &["HeapState.enable", "HeapState.disable", "HeapState.add", "HeapState.remove", "HeapState.report"] {
        mark_reachable(hs_func.to_string(), &mut reachable, &mut worklist);
    }
    used_types.insert("HeapState".to_string());
    used_types.insert("HeapEntry".to_string());

    // Add struct types when their methods are reachable (e.g., Foo.bar reachable -> Foo is used)
    for func_name in &reachable {
        if let Some(method_dot_pos) = func_name.find('.') {
            let struct_name = &func_name[..method_dot_pos];
            // Only add if this is actually a struct (not an enum)
            if context.scope_stack.has_struct(struct_name) {
                used_types.insert(struct_name.to_string());
            }
        }
    }

    // Bug #136: Mark struct eq() methods as reachable when the struct type is used
    // This is needed because switch comparisons on struct types call eq() implicitly
    // (the call is generated by the codegen, not present in the source)
    let used_types_snapshot: Vec<String> = used_types.iter().cloned().collect();
    for type_name in &used_types_snapshot {
        // Skip primitive types for eq method check (they don't need implicit eq for switch)
        // But continue processing for namespace functions below
        if type_name != "Str" && type_name != "I64" && type_name != "U8" && type_name != "Bool" {
            // Check if this is a struct with an eq method
            if context.scope_stack.has_struct(type_name) {
                let eq_method_name = format!("{}.eq", type_name);
                if context.scope_stack.has_func(&eq_method_name) {
                    mark_reachable(eq_method_name, &mut reachable, &mut worklist);
                }
            }
        }

        // Issue #108: Mark all namespace methods as reachable when their type is used
        // This ensures that dependencies of namespace functions are tracked
        // Walk the AST to find struct/enum declarations with ns for this type
        for stmt in &e.params {
            if let NodeType::Declaration(decl) = &stmt.node_type {
                if decl.name == *type_name {
                    if let Some(value_expr) = stmt.params.first() {
                        let ns_def = match &value_expr.node_type {
                            NodeType::StructDef(struct_def) => Some(&struct_def.ns),
                            NodeType::EnumDef(enum_def) => Some(&enum_def.ns),
                            _ => None,
                        };
                        if let Some(ns_def) = ns_def {
                            for (method_name, default_expr) in &ns_def.default_values {
                                if let NodeType::FuncDef(_) = &default_expr.node_type {
                                    let full_name = format!("{}.{}", type_name, method_name);
                                    mark_reachable(full_name, &mut reachable, &mut worklist);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Process any newly added eq methods and namespace methods
    while let Some(func_name) = worklist.pop() {
        if let Some(func_def) = context.scope_stack.lookup_func(&func_name) {
            collect_used_types_from_func(context, &func_def, &mut used_types)?;

            // Issue #108: Also check for variadic params in second loop
            for arg in &func_def.sig.args {
                if let crate::rs::parser::ValueType::TMulti(_) = &arg.value_type {
                    needs_variadic_support = true;
                    break;
                }
            }

            if func_def.is_ext() {
                continue;
            }
            let mut called: HashSet<String> = HashSet::new();
            for stmt in &func_def.body {
                collect_called_functions(stmt, &mut called)?;
            }
            for called_func in called {
                mark_reachable(called_func, &mut reachable, &mut worklist);
            }
        }
    }

    // Now compute transitive closure of used types (struct field types, enum payload types)
    let mut type_worklist: Vec<String> = used_types.iter().cloned().collect();
    while let Some(type_name) = type_worklist.pop() {
        // Check struct field types
        if let Some(closure_struct_def) = context.scope_stack.lookup_struct(&type_name) {
            for member in &closure_struct_def.members {
                if let Some(field_type) = extract_type_name(&member.value_type) {
                    if !used_types.contains(&field_type) {
                        used_types.insert(field_type.clone());
                        type_worklist.push(field_type);
                    }
                }
            }
        }
        // Check enum payload types
        if let Some(closure_enum_def) = context.scope_stack.lookup_enum(&type_name) {
            for variant in &closure_enum_def.variants {
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
        register_declarations(context, e)?;

        // Step 1: Determine root functions based on mode
        let mut roots: HashSet<String> = HashSet::new();

        if context.mode_def.needs_main_proc {
            // CLI mode: root is main plus global variable initializers
            roots.insert("main".to_string());
            // Global variable initializers are also executed in main(), so their calls are roots
            for stmt in &e.params {
                if let NodeType::Declaration(_decl) = &stmt.node_type {
                    if !stmt.params.is_empty() {
                        let inner = stmt.params.get(0).unwrap();
                        match &inner.node_type {
                            NodeType::FuncDef(_) => {
                                // Skip function declarations
                            }
                            _ => {
                                // Non-function declaration initializer - collect calls from it
                                collect_called_functions(inner, &mut roots)?;
                            }
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
                            let inner = stmt.params.get(0).unwrap();
                            match &inner.node_type {
                                NodeType::FuncDef(_) => {
                                    // Skip function declarations - they're not roots themselves
                                }
                                _ => {
                                    // Non-function declaration initializer - collect calls from it
                                    collect_called_functions(inner, &mut roots)?;
                                }
                            }
                        }
                    }
                    _ => {
                        // Non-declaration statement (function call, assignment, etc.)
                        collect_called_functions(stmt, &mut roots)?;
                    }
                }
            }
        } else {
            // lib/pure mode - globals are still initialized in main(), so include those calls
            for stmt in &e.params {
                if let NodeType::Declaration(_decl) = &stmt.node_type {
                    if !stmt.params.is_empty() {
                        let inner = stmt.params.get(0).unwrap();
                        match &inner.node_type {
                            NodeType::FuncDef(_) => {
                                // Skip function declarations
                            }
                            _ => {
                                // Non-function declaration initializer - collect calls from it
                                collect_called_functions(inner, &mut roots)?;
                            }
                        }
                    }
                }
            }
        }

        // Issue #91: Also collect function references passed as FuncSig arguments at top level
        for stmt in &e.params {
            collect_func_ptr_references(stmt, context, &mut roots)?;
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

        // Step 2b: Add enum payload types and their transitive dependencies to used_types
        // Bug #143: Enums are always kept, so their struct payload types must be kept too
        // We need to collect payload types AND compute transitive closure of those
        let mut enum_payload_types: Vec<String> = Vec::new();
        for stmt in &e.params {
            if let NodeType::Declaration(_) = &stmt.node_type {
                if !stmt.params.is_empty() {
                    if let NodeType::EnumDef(enum_def) = &stmt.params.get(0).unwrap().node_type {
                        for variant in &enum_def.variants {
                            if let Some(payload_type) = &variant.payload_type {
                                if let Some(payload_type_name) = extract_type_name(payload_type) {
                                    if !used_types.contains(&payload_type_name) {
                                        enum_payload_types.push(payload_type_name);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // Now compute transitive closure of enum payload types
        while let Some(type_name) = enum_payload_types.pop() {
            if used_types.contains(&type_name) {
                continue;
            }
            used_types.insert(type_name.clone());
            // Check struct field types
            if let Some(closure_struct_def) = context.scope_stack.lookup_struct(&type_name) {
                for member in &closure_struct_def.members {
                    if let Some(field_type) = extract_type_name(&member.value_type) {
                        if !used_types.contains(&field_type) {
                            enum_payload_types.push(field_type);
                        }
                    }
                }
            }
        }

        // Step 3: Build new AST - only include reachable function declarations
        // For structs, rebuild them without unreachable methods
        let mut new_params: Vec<Expr> = Vec::new();
        for stmt in &e.params {
            match &stmt.node_type {
                NodeType::Declaration(decl) => {
                    if !stmt.params.is_empty() {
                        let inner = stmt.params.get(0).unwrap();
                        match &inner.node_type {
                            NodeType::FuncDef(func_def) => {
                                // Issue #91: FuncSig declarations (empty body, unnamed args)
                                // are type definitions, not functions - always keep them
                                let is_func_sig = func_def.body.is_empty()
                                    && func_def.sig.args.iter().all(|a| a.name.is_empty())
                                    && matches!(func_def.sig.function_type, crate::rs::parser::FunctionType::FTFunc | crate::rs::parser::FunctionType::FTProc);
                                // Function declaration - keep if reachable, external, or FuncSig
                                if func_def.is_ext() || is_func_sig || reachable.contains(&decl.name) {
                                    new_params.push(stmt.clone());
                                }
                            }
                            NodeType::StructDef(struct_def) => {
                                // Struct - only keep if type is used, rebuild without unreachable methods
                                if used_types.contains(&decl.name) {
                                    let new_struct = rebuild_struct_without_unreachable_methods(decl, struct_def, &reachable);
                                    new_params.push(new_struct);
                                }
                            }
                            _ => {
                                // Non-function, non-struct declaration (including enums) - always keep
                                new_params.push(stmt.clone());
                            }
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
