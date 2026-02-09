// Garbager phase: AST transformations for memory semantics.
// This phase runs after type checking, before UFCS.
// Issue #159: Insert clone() calls for deep copy semantics on struct assignments.

use std::collections::HashMap;
use std::collections::HashSet;
use crate::rs::init::Context;
use crate::rs::parser::{Expr, NodeType, ValueType, SFuncDef, SStructDef, SNamespaceDef, Declaration};

/// Result of resolving a function call, including UFCS detection.
struct ResolvedFCall {
    func_def: SFuncDef,
    is_ufcs: bool,
}

/// Garbager phase entry point: Transform AST for proper memory semantics.
pub fn garbager_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    garbager_recursive(context, e)
}

/// Recursively transform the AST.
fn garbager_recursive(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            // Step 1: Strip dont_delete calls, collect protected var names
            let mut new_body = Vec::new();
            let mut dont_delete_vars: HashSet<String> = HashSet::new();
            for stmt in &func_def.body {
                if is_dont_delete_call(stmt) {
                    if let Some(var_name) = get_dont_delete_var(stmt) {
                        dont_delete_vars.insert(var_name);
                    }
                    continue;
                }
                // Step 2: Collect create_alias var names
                if let Some(alias_var) = get_create_alias_var(stmt) {
                    dont_delete_vars.insert(alias_var);
                }
                new_body.push(garbager_recursive(context, stmt)?);
            }

            // Step 2.5: Collect catch error variable names (they shadow locals in ccodegen)
            for stmt in &new_body {
                if let NodeType::Catch = &stmt.node_type {
                    if !stmt.params.is_empty() {
                        if let NodeType::Identifier(err_var_name) = &stmt.params[0].node_type {
                            dont_delete_vars.insert(err_var_name.clone());
                        }
                    }
                }
            }

            // Step 3: Collect delete candidates
            let mut candidates: Vec<(String, String)> = Vec::new();

            // 3a: copy/own params with deletable types
            for arg_def in &func_def.args {
                if arg_def.is_copy || arg_def.is_own {
                    if let ValueType::TCustom(type_name) = &arg_def.value_type {
                        if is_deletable_type(type_name, context) {
                            candidates.push((arg_def.name.clone(), type_name.clone()));
                        }
                    }
                }
            }

            // 3b: Scan new_body for Declaration nodes with deletable types.
            // Skip if function has any catch blocks: throws can skip declarations,
            // making unconditional deletes at function end unsafe.
            let has_any_catch = new_body.iter().any(|stmt| {
                matches!(&stmt.node_type, NodeType::Catch)
            });
            if !has_any_catch {
                for stmt in &new_body {
                    if let NodeType::Declaration(decl) = &stmt.node_type {
                        if let ValueType::TCustom(type_name) = &decl.value_type {
                            if is_deletable_type(type_name, context) {
                                candidates.push((decl.name.clone(), type_name.clone()));
                            }
                        }
                    }
                }
            }

            // Step 4: Remove dont_delete_vars, own-transferred vars, and wildcards
            // Build local name->type map for UFCS resolution in collect_own_transfers
            let mut local_types: HashMap<String, String> = HashMap::new();
            for arg_def in &func_def.args {
                if let ValueType::TCustom(type_name) = &arg_def.value_type {
                    local_types.insert(arg_def.name.clone(), type_name.clone());
                }
            }
            for stmt in &new_body {
                if let NodeType::Declaration(decl) = &stmt.node_type {
                    if let ValueType::TCustom(type_name) = &decl.value_type {
                        local_types.insert(decl.name.clone(), type_name.clone());
                    }
                }
            }
            let own_transfers = collect_own_transfers(&new_body, context, &local_types);
            candidates.retain(|(var_name, _)| {
                var_name != "_"
                    && !dont_delete_vars.contains(var_name)
                    && !own_transfers.contains(var_name)
            });

            // Step 5: Append Type.delete(var) calls in reverse declaration order
            let last_line = new_body.last().map_or(e.line, |s| s.line);
            let last_col = new_body.last().map_or(e.col, |s| s.col);
            candidates.reverse();
            for (var_name, type_name) in &candidates {
                new_body.push(build_delete_call_expr(type_name, var_name, last_line, last_col));
            }

            let new_func_def = SFuncDef {
                function_type: func_def.function_type.clone(),
                args: func_def.args.clone(),
                return_types: func_def.return_types.clone(),
                throw_types: func_def.throw_types.clone(),
                body: new_body,
                source_path: func_def.source_path.clone(),
            };
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(NodeType::FuncDef(new_func_def), new_params, e.line, e.col))
        }
        // Recurse into StructDef default values
        NodeType::StructDef(struct_def) => {
            let mut new_default_values = HashMap::new();
            for (name, value_expr) in &struct_def.default_values {
                new_default_values.insert(name.clone(), garbager_recursive(context, value_expr)?);
            }
            let new_struct_def = SStructDef {
                members: struct_def.members.clone(),
                default_values: new_default_values,
            };
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(NodeType::StructDef(new_struct_def), new_params, e.line, e.col))
        }
        // Recurse into NamespaceDef default values
        NodeType::NamespaceDef(ns_def) => {
            let mut new_default_values = HashMap::new();
            for (name, value_expr) in &ns_def.default_values {
                new_default_values.insert(name.clone(), garbager_recursive(context, value_expr)?);
            }
            let new_ns_def = SNamespaceDef {
                type_name: ns_def.type_name.clone(),
                members: ns_def.members.clone(),
                default_values: new_default_values,
            };
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(NodeType::NamespaceDef(new_ns_def), new_params, e.line, e.col))
        }
        // Issue #159: Transform mut declarations with struct type where RHS is an identifier
        NodeType::Declaration(decl) => {
            // First, recursively transform children
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }

            // Check if this is a mut declaration with struct type and identifier RHS
            // Identifier can have field access (x.y.z), we clone any identifier-based RHS
            if decl.is_mut && !new_params.is_empty() {
                if let NodeType::Identifier(_) = &new_params[0].node_type {
                    if let ValueType::TCustom(type_name) = &decl.value_type {
                        // Exclude true primitive types - they don't need deep cloning
                        // Note: Bool is NOT excluded because true/false are global constants
                        // that would be corrupted if we just share offsets
                        if is_deletable_type(type_name, context) {
                            // Build clone call: Type.clone(rhs_expr)
                            let rhs_expr = new_params[0].clone();
                            let clone_call = build_clone_call_expr(type_name, rhs_expr, e.line, e.col);
                            let mut transformed_params = vec![clone_call];
                            transformed_params.extend(new_params.into_iter().skip(1));
                            return Ok(Expr::new_explicit(
                                e.node_type.clone(),
                                transformed_params,
                                e.line,
                                e.col,
                            ));
                        }
                    }
                }
            }
            // No transformation needed
            Ok(Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col))
        }
        // Issue #159: Transform FCall copy params with struct type where arg is an identifier
        NodeType::FCall(_) => {
            // First, recursively transform children
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }
            // Transform copy params: wrap struct identifier args in Type.clone()
            transform_fcall_copy_params(context, e, &mut new_params);
            // Issue #159 Step 5: Transform struct literal fields
            transform_struct_literal_fields(context, e, &mut new_params);
            Ok(Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col))
        }
        // Issue #159 Step 6: Transform assignments with struct type where RHS is an identifier
        NodeType::Assignment(_var_name) => {
            // First, recursively transform children
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }

            // Check if RHS is a bare identifier (no field access children)
            // Field access expressions (x.y.z) are skipped - they read from memory directly
            if !new_params.is_empty() {
                if let NodeType::Identifier(rhs_name) = &new_params[0].node_type {
                    if new_params[0].params.is_empty() {
                        // Look up identifier's symbol type
                        if let Some(sym) = context.scope_stack.lookup_symbol(rhs_name) {
                            if let ValueType::TCustom(type_name) = &sym.value_type {
                                if is_deletable_type(type_name, context) {
                                    // Build clone call: Type.clone(rhs_expr)
                                    let rhs_expr = new_params[0].clone();
                                    let clone_call = build_clone_call_expr(type_name, rhs_expr, e.line, e.col);
                                    let mut transformed_params = vec![clone_call];
                                    transformed_params.extend(new_params.into_iter().skip(1));
                                    return Ok(Expr::new_explicit(
                                        e.node_type.clone(),
                                        transformed_params,
                                        e.line,
                                        e.col,
                                    ));
                                }
                            }
                        }
                    }
                }
            }
            // No transformation needed
            Ok(Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col))
        }
        // Body: recurse into children
        NodeType::Body => {
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col))
        }
        // Default: recurse into children
        _ => {
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col))
        }
    }
}

/// Build AST for Type.clone(src_expr): FCall( Identifier("Type").Identifier("clone"), src_expr )
fn build_clone_call_expr(type_name: &str, src_expr: Expr, line: usize, col: usize) -> Expr {
    // Type.clone access: Identifier("Type") with child Identifier("clone")
    let clone_ident = Expr::new_explicit(
        NodeType::Identifier("clone".to_string()),
        vec![],
        line,
        col,
    );
    let type_clone_access = Expr::new_explicit(
        NodeType::Identifier(type_name.to_string()),
        vec![clone_ident],
        line,
        col,
    );

    // FCall node with the source expression as argument
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![type_clone_access, src_expr],
        line,
        col,
    )
}

/// Check if a type should have delete() calls inserted.
/// Excludes primitives: I64, U8, Type, Dynamic, Ptr. NOT Str (has heap data).
/// Also excludes structs with no mutable fields (no heap data to free).
fn is_deletable_type(type_name: &str, context: &Context) -> bool {
    let is_primitive = matches!(type_name, "I64" | "U8" | "Type" | "Dynamic" | "Ptr");
    if is_primitive { return false; }
    if let Some(struct_def) = context.scope_stack.lookup_struct(type_name) {
        struct_def.members.iter().any(|m| m.is_mut)
    } else {
        false
    }
}

/// Build AST for Type.delete(var): FCall( Identifier("Type").Identifier("delete"), Identifier("var") )
fn build_delete_call_expr(type_name: &str, var_name: &str, line: usize, col: usize) -> Expr {
    let delete_ident = Expr::new_explicit(
        NodeType::Identifier("delete".to_string()), vec![], line, col);
    let type_delete_access = Expr::new_explicit(
        NodeType::Identifier(type_name.to_string()), vec![delete_ident], line, col);
    let var_expr = Expr::new_explicit(
        NodeType::Identifier(var_name.to_string()), vec![], line, col);
    Expr::new_explicit(NodeType::FCall(false), vec![type_delete_access, var_expr], line, col)
}

/// Extract function name from FCall's first param (the name expression).
/// Returns "foo" for foo(x) or "Type.method" for Type.method(x).
fn get_func_name(e: &Expr) -> Option<String> {
    if e.params.is_empty() {
        return None;
    }
    let name_expr = &e.params[0];
    match &name_expr.node_type {
        NodeType::Identifier(name) => {
            // Check for Type.method pattern: Identifier("Type") with child Identifier("method")
            if !name_expr.params.is_empty() {
                if let NodeType::Identifier(method) = &name_expr.params[0].node_type {
                    return Some(format!("{}.{}", name, method));
                }
            }
            Some(name.clone())
        }
        _ => None,
    }
}

/// Check if an expression is an Identifier node.
fn is_identifier_expr(e: &Expr) -> bool {
    matches!(&e.node_type, NodeType::Identifier(_))
}

/// Transform FCall copy params: for each arg that is_copy, struct-typed, and an identifier,
/// wrap in Type.clone().
fn transform_fcall_copy_params(context: &Context, e: &Expr, new_params: &mut Vec<Expr>) {
    let func_name = match get_func_name(e) {
        Some(name) => name,
        None => return,
    };

    // Skip .clone and .delete calls to avoid infinite recursion / double-free
    if func_name.ends_with(".clone") || func_name.ends_with(".delete") {
        return;
    }

    // Early out: check if any args (params[1..]) are identifiers
    let has_identifier_arg = new_params.iter().skip(1).any(|p| is_identifier_expr(p));
    if !has_identifier_arg {
        return;
    }

    // Look up function definition to get arg metadata
    let func_def = match context.scope_stack.lookup_func(&func_name) {
        Some(fd) => fd,
        None => return,
    };

    // For each arg: if is_copy AND struct type AND identifier, wrap in Type.clone()
    let arg_defs: &Vec<Declaration> = &func_def.args;
    for (i, arg_def) in arg_defs.iter().enumerate() {
        let param_idx = i + 1; // params[0] is the function name
        if param_idx >= new_params.len() {
            break;
        }
        if !arg_def.is_copy {
            continue;
        }
        if !is_identifier_expr(&new_params[param_idx]) {
            continue;
        }
        if let ValueType::TCustom(type_name) = &arg_def.value_type {
            if is_deletable_type(type_name, context) {
                let arg_expr = new_params[param_idx].clone();
                let clone_call = build_clone_call_expr(type_name, arg_expr, e.line, e.col);
                new_params[param_idx] = clone_call;
            }
        }
    }
}

/// Check if an expression is an FCall to `dont_delete`.
fn is_dont_delete_call(e: &Expr) -> bool {
    if let NodeType::FCall(_) = &e.node_type {
        if let Some(name) = get_func_name(e) {
            return name == "dont_delete";
        }
    }
    false
}

/// Extract variable name from dont_delete(var) call.
/// The variable is params[1] (params[0] is the function name).
fn get_dont_delete_var(e: &Expr) -> Option<String> {
    if e.params.len() < 2 {
        return None;
    }
    if let NodeType::Identifier(var_name) = &e.params[1].node_type {
        return Some(var_name.clone());
    }
    None
}

/// Extract variable name from create_alias(var, type, addr) call.
fn get_create_alias_var(e: &Expr) -> Option<String> {
    if let NodeType::FCall(_) = &e.node_type {
        if let Some(name) = get_func_name(e) {
            if name == "create_alias" && e.params.len() >= 3 {
                if let NodeType::Identifier(var_name) = &e.params[1].node_type {
                    return Some(var_name.clone());
                }
            }
        }
    }
    None
}

/// Walk an FCall's name expression to extract the full identifier chain.
/// e.g., for `self.frames.push(frame)`, returns ["self", "frames", "push"]
fn get_fcall_identifier_chain(e: &Expr) -> Vec<String> {
    let mut chain = Vec::new();
    if let NodeType::FCall(_) = &e.node_type {
        if let Some(first) = e.params.first() {
            collect_identifier_chain(first, &mut chain);
        }
    }
    chain
}

fn collect_identifier_chain(e: &Expr, chain: &mut Vec<String>) {
    if let NodeType::Identifier(name) = &e.node_type {
        chain.push(name.clone());
        for child in &e.params {
            collect_identifier_chain(child, chain);
        }
    }
}

/// Resolve a function call from its identifier chain, handling UFCS and chained field access.
/// For UFCS calls, self is implicit so arg-to-param mapping differs.
fn resolve_fcall_from_chain(chain: &[String], local_types: &HashMap<String, String>, context: &Context) -> Option<ResolvedFCall> {
    if chain.is_empty() { return None; }

    // Plain function call (no dots)
    if chain.len() == 1 {
        return context.scope_stack.lookup_func(&chain[0]).cloned()
            .map(|fd| ResolvedFCall { func_def: fd, is_ufcs: false });
    }

    // Try direct lookup of the joined name (works for Type.method)
    let full_name = chain.join(".");
    if let Some(fd) = context.scope_stack.lookup_func(&full_name) {
        return Some(ResolvedFCall { func_def: fd.clone(), is_ufcs: false });
    }

    // UFCS resolution: resolve type through the chain, last part is the method
    let method_name = &chain[chain.len() - 1];
    let first = &chain[0];

    // Get initial type from struct name or local_types
    let mut current_type = if context.scope_stack.has_struct(first) {
        first.clone()
    } else if let Some(t) = local_types.get(first) {
        t.clone()
    } else {
        return None;
    };

    // Walk intermediate parts (chain[1..n-1]) via struct field type lookups
    for i in 1..chain.len()-1 {
        let field_name = &chain[i];
        let struct_def = context.scope_stack.lookup_struct(&current_type)?;
        let member = struct_def.get_member(field_name)?;
        if let ValueType::TCustom(next_type) = &member.value_type {
            current_type = next_type.clone();
        } else {
            return None;
        }
    }

    let resolved = format!("{}.{}", current_type, method_name);
    context.scope_stack.lookup_func(&resolved).cloned()
        .map(|fd| ResolvedFCall { func_def: fd, is_ufcs: true })
}

/// Scan statements for variables passed as `own` args to function calls.
fn collect_own_transfers(stmts: &[Expr], context: &Context, local_types: &HashMap<String, String>) -> HashSet<String> {
    let mut result = HashSet::new();
    for stmt in stmts {
        collect_own_transfers_recursive(stmt, context, local_types, &mut result);
    }
    result
}

fn collect_own_transfers_recursive(e: &Expr, context: &Context, local_types: &HashMap<String, String>, result: &mut HashSet<String>) {
    if let NodeType::FCall(_) = &e.node_type {
        let chain = get_fcall_identifier_chain(e);
        if !chain.is_empty() {
            let last = &chain[chain.len() - 1];
            if last != "clone" && last != "delete" {
                if let Some(resolved) = resolve_fcall_from_chain(&chain, local_types, context) {
                    let func_def = &resolved.func_def;
                    let is_ufcs = resolved.is_ufcs;
                    // For UFCS calls (tokens.push(t)), self is implicit in the name,
                    // so skip args[0] (self) and map args[k] -> params[k] for k >= 1.
                    // For direct calls (Vec.push(tokens, t)), map args[i] -> params[i+1].
                    let arg_start: usize = if is_ufcs { 1 } else { 0 };
                    for (i, arg_def) in func_def.args.iter().enumerate() {
                        if i < arg_start { continue; }
                        let param_idx = if is_ufcs { i } else { i + 1 };
                        if param_idx < e.params.len() && arg_def.is_own {
                            if let NodeType::Identifier(var_name) = &e.params[param_idx].node_type {
                                if e.params[param_idx].params.is_empty() {
                                    result.insert(var_name.clone());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for param in &e.params {
        collect_own_transfers_recursive(param, context, local_types, result);
    }
    if let NodeType::FuncDef(func_def) = &e.node_type {
        for stmt in &func_def.body {
            collect_own_transfers_recursive(stmt, context, local_types, result);
        }
    }
}

/// Issue #159 Step 5: Transform struct literal fields.
/// For struct literal constructors like Point(inner=some_var), if a NamedArg value
/// is an identifier pointing to a struct type, wrap it in Type.clone().
fn transform_struct_literal_fields(context: &Context, e: &Expr, new_params: &mut Vec<Expr>) {
    // Extract the struct name from the original FCall (before child transforms)
    let struct_name = match get_func_name(e) {
        Some(name) => name,
        None => return,
    };

    // Must be a plain struct name (no dots - not a method call)
    if struct_name.contains('.') {
        return;
    }

    // Check if it's a struct
    let struct_def = match context.scope_stack.lookup_struct(&struct_name) {
        Some(sd) => sd.clone(),
        None => return,
    };

    // For each child in new_params[1..] that is a NamedArg
    for param_idx in 1..new_params.len() {
        if let NodeType::NamedArg(field_name) = &new_params[param_idx].node_type {
            // Find matching field in struct def members
            let field_decl = match struct_def.get_member(field_name) {
                Some(decl) => decl,
                None => continue,
            };
            // Check if field type is a non-primitive struct
            if let ValueType::TCustom(type_name) = &field_decl.value_type {
                if !is_deletable_type(type_name, context) {
                    continue;
                }
                // Check if the NamedArg's value (params[0]) is an identifier
                if !new_params[param_idx].params.is_empty() && is_identifier_expr(&new_params[param_idx].params[0]) {
                    let arg_expr = new_params[param_idx].params[0].clone();
                    let clone_call = build_clone_call_expr(type_name, arg_expr, e.line, e.col);
                    new_params[param_idx].params[0] = clone_call;
                }
            }
        }
    }
}
