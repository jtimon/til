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
            // Rule A: Only declarations whose initializer is a CONSTRUCTOR or
            // allocating static method (Type(), Type.new(), Type.clone()).
            // Regular function calls may return aliased (shallow-copied) data.
            for stmt in &new_body {
                if let NodeType::Declaration(decl) = &stmt.node_type {
                    if let ValueType::TCustom(type_name) = &decl.value_type {
                        if is_deletable_type(type_name, context)
                            && !stmt.params.is_empty()
                            && matches!(&stmt.params[0].node_type, NodeType::FCall(_))
                            && is_owned_return_fcall(&stmt.params[0], context)
                        {
                            candidates.push((decl.name.clone(), type_name.clone()));
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

            // Step 4b: Rule B — exclude reassigned candidates
            let reassigned = collect_reassigned_vars(&new_body, &candidates);
            candidates.retain(|(var_name, _)| !reassigned.contains(var_name));

            // Step 4c: Rule C — exclude escaped candidates
            let candidate_names: HashSet<String> = candidates.iter().map(|(n,_)| n.clone()).collect();
            let escaped = collect_escaped_vars(&new_body, &candidate_names, context, &local_types);
            candidates.retain(|(var_name, _)| !escaped.contains(var_name));

            // Step 5: ASAP delete after last use for all candidates
            let body_len = new_body.len();
            let mut inserts: HashMap<usize, Vec<Expr>> = HashMap::new();
            candidates.reverse();
            for (var_name, type_name) in &candidates {
                let insert_pos = match find_last_use_index(&new_body, var_name) {
                    Some(idx) => idx + 1,
                    None => body_len,
                };
                let line = if insert_pos > 0 && insert_pos <= body_len {
                    new_body[insert_pos - 1].line
                } else {
                    new_body.last().map_or(e.line, |s| s.line)
                };
                let col = if insert_pos > 0 && insert_pos <= body_len {
                    new_body[insert_pos - 1].col
                } else {
                    new_body.last().map_or(e.col, |s| s.col)
                };
                inserts.entry(insert_pos).or_insert_with(Vec::new)
                    .push(build_delete_call_expr(type_name, var_name, line, col));
            }

            // Build final_body: original statements with ASAP deletes interleaved
            let mut final_body: Vec<Expr> = Vec::new();
            for i in 0..body_len {
                final_body.push(new_body[i].clone());
                if let Some(delete_calls) = inserts.get(&(i + 1)) {
                    for dc in delete_calls {
                        final_body.push(dc.clone());
                    }
                }
            }

            // TODO Bug #165: Process nested bodies for ASAP deletion within
            // if/while/for/switch blocks. Currently disabled because switch arm
            // payload variables and other complex aliasing patterns cause
            // double-frees. The function-level ASAP deletion already handles
            // the main memory leak cases.
            // let final_body = process_nested_bodies(&final_body, context, &local_types);
            let new_body = final_body;

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

/// Check if an FCall expression returns owned (freshly-allocated) data safe to
/// ASAP-delete. In TIL/C, function returns are shallow memcpy — the caller
/// gets a copy that may share heap pointers with data owned by someone else.
/// Only constructors, allocating static methods, and known-allocating instance
/// methods return truly owned data.
fn is_owned_return_fcall(fcall_expr: &Expr, context: &Context) -> bool {
    let chain = get_fcall_identifier_chain(fcall_expr);
    if chain.is_empty() { return false; }

    // Single-element chain: constructor call like SFuncDef() or Vec()
    if chain.len() == 1 {
        return context.scope_stack.has_struct(&chain[0]);
    }

    // Two-element chain: static method like Vec.new(T) or Type.clone(x)
    if chain.len() == 2 && context.scope_stack.has_struct(&chain[0]) {
        let method = &chain[1];
        return method == "new" || method.starts_with("new_") || method == "clone";
    }

    // Known instance methods that always return freshly-allocated data.
    // These allocate new heap memory for their return value.
    let last = &chain[chain.len() - 1];
    if last == "to_str" || last == "to_str_with_indent"
        || last == "lang_error" || last == "lang_error_with_path"
        || last == "format"
        || last == "concat"
        || last == "split"
        || last == "replace"
        || last == "trim" || last == "trim_start" || last == "trim_end"
        || last == "substring" || last == "substr"
        || last == "repeat"
        || last == "to_lower" || last == "to_upper"
        || last == "join"
        || last == "slice"
    {
        return true;
    }

    false
}

/// Recursively check if any Identifier node in the expression tree matches var_name.
/// Recurses into e.params (covers if/while/for/switch bodies stored as params).
/// Does NOT recurse into nested FuncDef bodies (separate scope).
fn expr_references_var(e: &Expr, var_name: &str) -> bool {
    if let NodeType::Identifier(name) = &e.node_type {
        if name == var_name {
            return true;
        }
    }
    // Recurse into params (but not into nested FuncDef bodies)
    for param in &e.params {
        if expr_references_var(param, var_name) {
            return true;
        }
    }
    // For FuncDef nodes, do NOT recurse into body (separate scope).
    // e.params on a FuncDef are only default arg values, already checked above.
    false
}

/// Scan body from end to start, return index of last statement referencing the variable.
fn find_last_use_index(body: &[Expr], var_name: &str) -> Option<usize> {
    for i in (0..body.len()).rev() {
        if expr_references_var(&body[i], var_name) {
            return Some(i);
        }
    }
    None
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

/// Rule B: Collect variables that are reassigned after declaration.
/// B1: candidate appears as last arg of .get() or .pop() (out-param overwrite)
/// B2: candidate is target of Assignment (no dot in target name)
fn collect_reassigned_vars(body: &[Expr], candidates: &[(String, String)]) -> HashSet<String> {
    let candidate_names: HashSet<String> = candidates.iter().map(|(n,_)| n.clone()).collect();
    let mut result = HashSet::new();
    for stmt in body {
        collect_reassigned_vars_recursive(stmt, &candidate_names, &mut result);
    }
    result
}

fn collect_reassigned_vars_recursive(e: &Expr, candidate_names: &HashSet<String>, result: &mut HashSet<String>) {
    // B1: FCall where method chain ends with "get" or "pop"
    if let NodeType::FCall(_) = &e.node_type {
        let chain = get_fcall_identifier_chain(e);
        if !chain.is_empty() {
            let last_method = &chain[chain.len() - 1];
            if last_method == "get" || last_method == "pop" || last_method == "enum_get_payload" {
                // Last param (the out-param) is the one that gets overwritten
                if e.params.len() >= 2 {
                    let last_param = &e.params[e.params.len() - 1];
                    if let NodeType::Identifier(var_name) = &last_param.node_type {
                        if last_param.params.is_empty() && candidate_names.contains(var_name) {
                            result.insert(var_name.clone());
                        }
                    }
                }
            }
        }
    }
    // B2: Assignment(target) where target has no dot
    if let NodeType::Assignment(target) = &e.node_type {
        if !target.contains('.') && candidate_names.contains(target) {
            result.insert(target.clone());
        }
    }
    // Recurse into params but NOT into FuncDef bodies
    for param in &e.params {
        collect_reassigned_vars_recursive(param, candidate_names, result);
    }
    // Do NOT recurse into FuncDef bodies (separate scope)
}

/// Rule C: Collect variables whose data escapes to other variables.
/// C1: candidate passed as non-receiver arg to push/set/insert
/// C2: candidate referenced in initializer of a declaration with deletable type
/// C3: candidate is RHS of a field assignment (Assignment with dot in target)
fn collect_escaped_vars(
    body: &[Expr],
    candidate_names: &HashSet<String>,
    context: &Context,
    local_types: &HashMap<String, String>,
) -> HashSet<String> {
    let mut result = HashSet::new();
    for stmt in body {
        collect_escaped_vars_recursive(stmt, candidate_names, context, local_types, &mut result);
    }
    result
}

fn collect_escaped_vars_recursive(
    e: &Expr,
    candidate_names: &HashSet<String>,
    context: &Context,
    local_types: &HashMap<String, String>,
    result: &mut HashSet<String>,
) {
    // C1: FCall where method chain ends with "push"/"set"/"insert"
    // C4: FCall where method chain ends with "get_by_ref" — receiver's data is referenced externally
    if let NodeType::FCall(_) = &e.node_type {
        let chain = get_fcall_identifier_chain(e);
        if !chain.is_empty() {
            let last_method = &chain[chain.len() - 1];
            if last_method == "push" || last_method == "set" || last_method == "insert" {
                // Determine data arg start index:
                // If chain[0] is a struct type name, it's a direct call: data args start at params[2]
                // Otherwise method-style: data args start at params[1]
                let data_start = if context.scope_stack.has_struct(&chain[0]) { 2 } else { 1 };
                for i in data_start..e.params.len() {
                    if let NodeType::Identifier(var_name) = &e.params[i].node_type {
                        if e.params[i].params.is_empty() && candidate_names.contains(var_name) {
                            result.insert(var_name.clone());
                        }
                    }
                }
            }
            // C4: get_by_ref returns a pointer into the receiver's storage
            if last_method == "get_by_ref" && chain.len() >= 2 {
                if !context.scope_stack.has_struct(&chain[0]) && candidate_names.contains(&chain[0]) {
                    result.insert(chain[0].clone());
                }
            }
        }
    }
    // C2: Declaration with deletable type — check if initializer references any candidate
    if let NodeType::Declaration(decl) = &e.node_type {
        if let ValueType::TCustom(type_name) = &decl.value_type {
            if is_deletable_type(type_name, context) {
                if !e.params.is_empty() {
                    for cand_name in candidate_names {
                        if expr_references_var(&e.params[0], cand_name) {
                            result.insert(cand_name.clone());
                        }
                    }
                }
            }
        }
    }
    // C3: Assignment(target) where target has a dot — RHS is bare Identifier candidate
    if let NodeType::Assignment(target) = &e.node_type {
        if target.contains('.') && !e.params.is_empty() {
            if let NodeType::Identifier(var_name) = &e.params[0].node_type {
                if e.params[0].params.is_empty() && candidate_names.contains(var_name) {
                    result.insert(var_name.clone());
                }
            }
        }
    }
    // Recurse into params but NOT into FuncDef bodies
    for param in &e.params {
        collect_escaped_vars_recursive(param, candidate_names, context, local_types, result);
    }
    // Do NOT recurse into FuncDef bodies (separate scope)
}

/// Process a Body node's params: collect candidates, apply rules, insert ASAP deletes.
/// Returns the processed statements (does NOT recurse into nested bodies).
#[allow(dead_code)]
fn process_body_params(
    body_stmts: &[Expr],
    context: &Context,
    local_types: &HashMap<String, String>,
    default_line: usize,
    default_col: usize,
) -> (Vec<Expr>, HashMap<String, String>) {
    // Update local_types with declarations from this body
    let mut nested_local_types = local_types.clone();
    for stmt in body_stmts {
        if let NodeType::Declaration(decl) = &stmt.node_type {
            if let ValueType::TCustom(type_name) = &decl.value_type {
                nested_local_types.insert(decl.name.clone(), type_name.clone());
            }
        }
    }

    // Collect dont_delete vars from this body
    let mut dont_delete_vars: HashSet<String> = HashSet::new();
    let mut filtered_stmts: Vec<Expr> = Vec::new();
    for stmt in body_stmts {
        if is_dont_delete_call(stmt) {
            if let Some(var_name) = get_dont_delete_var(stmt) {
                dont_delete_vars.insert(var_name);
            }
            continue;
        }
        if let Some(alias_var) = get_create_alias_var(stmt) {
            dont_delete_vars.insert(alias_var);
        }
        filtered_stmts.push(stmt.clone());
    }

    // Rule A: Collect candidates (constructor/allocating FCall + deletable type)
    let mut candidates: Vec<(String, String)> = Vec::new();
    for stmt in &filtered_stmts {
        if let NodeType::Declaration(decl) = &stmt.node_type {
            if let ValueType::TCustom(type_name) = &decl.value_type {
                if is_deletable_type(type_name, context)
                    && !stmt.params.is_empty()
                    && matches!(&stmt.params[0].node_type, NodeType::FCall(_))
                    && is_owned_return_fcall(&stmt.params[0], context)
                {
                    candidates.push((decl.name.clone(), type_name.clone()));
                }
            }
        }
    }

    // Filter: _, dont_delete_vars, own_transfers
    let own_transfers = collect_own_transfers(&filtered_stmts, context, &nested_local_types);
    candidates.retain(|(var_name, _)| {
        var_name != "_"
            && !dont_delete_vars.contains(var_name)
            && !own_transfers.contains(var_name)
    });

    // Rule B: exclude reassigned
    let reassigned = collect_reassigned_vars(&filtered_stmts, &candidates);
    candidates.retain(|(var_name, _)| !reassigned.contains(var_name));

    // Rule C: exclude escaped
    let candidate_names: HashSet<String> = candidates.iter().map(|(n,_)| n.clone()).collect();
    let escaped = collect_escaped_vars(&filtered_stmts, &candidate_names, context, &nested_local_types);
    candidates.retain(|(var_name, _)| !escaped.contains(var_name));

    // ASAP insert delete calls
    let body_len = filtered_stmts.len();
    let mut inserts: HashMap<usize, Vec<Expr>> = HashMap::new();
    candidates.reverse();
    for (var_name, type_name) in &candidates {
        let insert_pos = match find_last_use_index(&filtered_stmts, var_name) {
            Some(idx) => idx + 1,
            None => body_len,
        };
        let line = if insert_pos > 0 && insert_pos <= body_len {
            filtered_stmts[insert_pos - 1].line
        } else {
            filtered_stmts.last().map_or(default_line, |s| s.line)
        };
        let col = if insert_pos > 0 && insert_pos <= body_len {
            filtered_stmts[insert_pos - 1].col
        } else {
            filtered_stmts.last().map_or(default_col, |s| s.col)
        };
        inserts.entry(insert_pos).or_insert_with(Vec::new)
            .push(build_delete_call_expr(type_name, var_name, line, col));
    }

    let mut final_stmts: Vec<Expr> = Vec::new();
    for i in 0..body_len {
        final_stmts.push(filtered_stmts[i].clone());
        if let Some(delete_calls) = inserts.get(&(i + 1)) {
            for dc in delete_calls {
                final_stmts.push(dc.clone());
            }
        }
    }

    (final_stmts, nested_local_types)
}

/// Process nested Body nodes for ASAP deletion within if/while/for/switch blocks.
/// Walks each statement's params. For Body nodes, processes them (candidates + ASAP)
/// then recurses. For non-Body nodes, recurses into their params.
#[allow(dead_code)]
fn process_nested_bodies(
    stmts: &[Expr],
    context: &Context,
    local_types: &HashMap<String, String>,
) -> Vec<Expr> {
    let mut result = Vec::new();
    for stmt in stmts {
        let mut new_params = Vec::new();
        for param in &stmt.params {
            if let NodeType::Body = &param.node_type {
                // Process this Body: candidates + ASAP deletes
                let (processed_stmts, nested_local_types) =
                    process_body_params(&param.params, context, local_types, param.line, param.col);
                // Recurse into the processed body's statements
                let recursed_stmts = process_nested_bodies(&processed_stmts, context, &nested_local_types);
                new_params.push(Expr::new_explicit(NodeType::Body, recursed_stmts, param.line, param.col));
            } else {
                // Recurse into non-Body params to find deeper nested bodies
                let inner_result = process_nested_bodies(&param.params, context, local_types);
                new_params.push(Expr::new_explicit(param.node_type.clone(), inner_result, param.line, param.col));
            }
        }
        result.push(Expr::new_explicit(stmt.node_type.clone(), new_params, stmt.line, stmt.col));
    }
    result
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
