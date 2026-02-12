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

            // Build local name->type map for clone-after-get and own-transfer detection
            let mut local_types: HashMap<String, String> = HashMap::new();
            for arg_def in &func_def.args {
                if let ValueType::TCustom(type_name) = &arg_def.value_type {
                    local_types.insert(arg_def.name.clone(), type_name.clone());
                }
            }
            // Also collect declarations from nested scopes (if/while/for bodies)
            collect_local_types_recursive(&new_body, &mut local_types);

            // Step 2.7: Insert clone-after-get for container methods with shallow out-params.
            let new_body = insert_clone_after_get(&new_body, &local_types, context);

            // Step 2.8: Insert scope-exit deletes for inner-scope declarations.
            let new_body = insert_scope_exit_deletes(&new_body, &local_types, context);

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
            let own_transfers = collect_own_transfers(&new_body, context, &local_types);
            candidates.retain(|(var_name, _)| {
                var_name != "_"
                    && !dont_delete_vars.contains(var_name)
                    && !own_transfers.contains(var_name)
            });

            // Step 5: Insert Type.delete(var) calls.
            // copy/own params: ASAP after last use (deep copies, no aliasing).
            // locals: at function end (shared offsets mean locals can alias).
            let mut param_names: HashSet<String> = HashSet::new();
            for arg_def in &func_def.args {
                if arg_def.is_copy || arg_def.is_own {
                    param_names.insert(arg_def.name.clone());
                }
            }

            // Separate params (ASAP) from locals (end-of-function)
            let mut asap_candidates: Vec<(String, String)> = Vec::new();
            let mut end_candidates: Vec<(String, String)> = Vec::new();
            for (var_name, type_name) in &candidates {
                if param_names.contains(var_name) {
                    asap_candidates.push((var_name.clone(), type_name.clone()));
                } else {
                    end_candidates.push((var_name.clone(), type_name.clone()));
                }
            }

            // ASAP: insert after last use for copy/own params
            let body_len = new_body.len();
            let mut inserts: HashMap<usize, Vec<Expr>> = HashMap::new();
            asap_candidates.reverse();
            for (var_name, type_name) in &asap_candidates {
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

            // End-of-function: append locals in reverse declaration order
            let last_line = final_body.last().map_or(e.line, |s| s.line);
            let last_col = final_body.last().map_or(e.col, |s| s.col);
            end_candidates.reverse();
            for (var_name, type_name) in &end_candidates {
                final_body.push(build_delete_call_expr(type_name, var_name, last_line, last_col));
            }
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

/// Recursively collect Declaration nodes with TCustom types from a statement list.
/// Only recurses into Body nodes (if/while/for bodies), not into all AST children.
/// Skips nested FuncDef bodies (separate scope).
fn collect_local_types_recursive(stmts: &[Expr], local_types: &mut HashMap<String, String>) {
    for stmt in stmts {
        if let NodeType::Declaration(decl) = &stmt.node_type {
            if let ValueType::TCustom(type_name) = &decl.value_type {
                if type_name == "auto" {
                    // Infer type from RHS: for FCall like Vec.new() or Expr(),
                    // the first element of the identifier chain is the type.
                    if !stmt.params.is_empty() {
                        let rhs = &stmt.params[0];
                        let chain = get_fcall_identifier_chain(rhs);
                        if !chain.is_empty() {
                            let first = &chain[0];
                            let first_char = first.chars().next().unwrap_or('a');
                            if first_char.is_uppercase() {
                                local_types.insert(decl.name.clone(), first.clone());
                            }
                        }
                    }
                } else {
                    local_types.insert(decl.name.clone(), type_name.clone());
                }
            }
        }
        // Only recurse into Body children (if/while/for blocks), not every param.
        // Deep recursion into all params causes OOM in TIL due to for-in leak (Bug #144).
        match &stmt.node_type {
            NodeType::FuncDef(_) => {} // separate scope, skip
            _ => {
                for param in &stmt.params {
                    if let NodeType::Body = &param.node_type {
                        collect_local_types_recursive(&param.params, local_types);
                    }
                }
            }
        }
    }
}

/// Insert scope-exit deletes for declarations in inner-scope Body nodes.
/// Recurses into nested Body nodes but not into FuncDef bodies.
fn insert_scope_exit_deletes(stmts: &[Expr], local_types: &HashMap<String, String>, context: &Context) -> Vec<Expr> {
    let mut result = Vec::new();
    for stmt in stmts {
        result.push(process_stmt_for_scope_exit(stmt, local_types, context));
    }
    result
}

fn process_stmt_for_scope_exit(e: &Expr, local_types: &HashMap<String, String>, context: &Context) -> Expr {
    match &e.node_type {
        NodeType::FuncDef(_) => e.clone(), // separate scope, don't touch
        NodeType::Body => {
            // First recurse into children (handles nested Body nodes)
            let recursed = insert_scope_exit_deletes(&e.params, local_types, context);

            // Strip dont_delete, collect protected vars
            let mut final_stmts = Vec::new();
            let mut dont_delete_vars: HashSet<String> = HashSet::new();
            for stmt in &recursed {
                if is_dont_delete_call(stmt) {
                    if let Some(var_name) = get_dont_delete_var(stmt) {
                        dont_delete_vars.insert(var_name);
                    }
                    continue; // strip from AST
                }
                if let Some(alias_var) = get_create_alias_var(stmt) {
                    dont_delete_vars.insert(alias_var);
                }
                final_stmts.push(stmt.clone());
            }

            // Collect catch error var names
            for stmt in &final_stmts {
                if let NodeType::Catch = &stmt.node_type {
                    if !stmt.params.is_empty() {
                        if let NodeType::Identifier(err_var) = &stmt.params[0].node_type {
                            dont_delete_vars.insert(err_var.clone());
                        }
                    }
                }
            }

            // Check for catch blocks -- skip deletion if any
            let has_any_catch = final_stmts.iter().any(|s|
                matches!(&s.node_type, NodeType::Catch));

            if !has_any_catch {
                // Whitelist approach: only collect declarations whose RHS is a
                // known-allocating expression (constructor, format, concat, to_str,
                // clone, new, split, etc.). Variables from container get/pop,
                // field access, or other sources may be aliased and unsafe to delete.
                let mut candidates: Vec<(String, String)> = Vec::new();
                for stmt in &final_stmts {
                    if let NodeType::Declaration(decl) = &stmt.node_type {
                        if let ValueType::TCustom(type_name) = &decl.value_type {
                            if is_deletable_type(type_name, context) {
                                // Check if RHS is a known-allocating call
                                if !stmt.params.is_empty() && is_owned_rhs(&stmt.params[0]) {
                                    candidates.push((decl.name.clone(), type_name.clone()));
                                }
                            }
                        }
                    }
                }

                // Collect own transfers
                let own_transfers = collect_own_transfers(&final_stmts, context, local_types);

                // Collect vars used as function arguments (shallow-copy alias risk)
                let mut func_arg_vars: HashSet<String> = HashSet::new();
                collect_func_arg_vars(&final_stmts, &mut func_arg_vars);

                // Filter
                candidates.retain(|(var_name, _)| {
                    var_name != "_"
                        && !dont_delete_vars.contains(var_name)
                        && !own_transfers.contains(var_name)
                        && !func_arg_vars.contains(var_name)
                });

                // Append deletes at end of scope in reverse declaration order
                if !candidates.is_empty() {
                    let last_line = final_stmts.last().map_or(e.line, |s| s.line);
                    let last_col = final_stmts.last().map_or(e.col, |s| s.col);
                    candidates.reverse();
                    for (var_name, type_name) in &candidates {
                        final_stmts.push(build_delete_call_expr(
                            type_name, var_name, last_line, last_col));
                    }
                }
            }

            Expr::new_explicit(e.node_type.clone(), final_stmts, e.line, e.col)
        }
        _ => {
            let mut new_params = Vec::new();
            for param in &e.params {
                if let NodeType::Body = &param.node_type {
                    new_params.push(process_stmt_for_scope_exit(param, local_types, context));
                } else {
                    new_params.push(param.clone());
                }
            }
            Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col)
        }
    }
}

/// Collect identifiers used as arguments to function calls in a list of statements.
/// Shallow scan only: checks each statement's top-level FCall, plus FCall in
/// Assignment RHS and Declaration RHS. Does NOT recurse into nested expressions
/// to avoid OOM from for-in leak (Bug #144).
/// Any variable passed as a function argument gets shallow-copied (memcpy) in TIL/C,
/// creating an alias that makes it unsafe to delete.
fn collect_func_arg_vars(stmts: &[Expr], result: &mut HashSet<String>) {
    for stmt in stmts {
        collect_fcall_arg_identifiers(stmt, result);
        // Also check one level deeper: Assignment RHS and Declaration RHS
        match &stmt.node_type {
            NodeType::Assignment(_) | NodeType::Declaration(_) => {
                if !stmt.params.is_empty() {
                    collect_fcall_arg_identifiers(&stmt.params[0], result);
                }
            }
            _ => {}
        }
    }
}

/// Collect bare identifiers from FCall arguments (params[1..]).
/// Only collects from this single FCall node, no recursion.
fn collect_fcall_arg_identifiers(e: &Expr, result: &mut HashSet<String>) {
    if let NodeType::FCall(_) = &e.node_type {
        for i in 1..e.params.len() {
            if let NodeType::Identifier(var_name) = &e.params[i].node_type {
                if e.params[i].params.is_empty() {
                    result.insert(var_name.clone());
                }
            }
        }
    }
}

/// Check if a Declaration RHS is a known-allocating expression.
/// Only these expressions produce truly owned data safe to delete:
/// - Constructor calls: Type(...), Type.new(...), Type.clone(...)
/// - String-allocating calls: format(...), concat(...), to_str(), to_lowercase()
/// - Collection constructors: Vec.new(...), Set.new(...), Map.new(...)
/// Variables from get/pop, field access, or other sources may be aliased.
fn is_owned_rhs(rhs: &Expr) -> bool {
    match &rhs.node_type {
        NodeType::FCall(_) => {
            let chain = get_fcall_identifier_chain(rhs);
            if chain.is_empty() {
                return false;
            }
            let last = &chain[chain.len() - 1];
            // Known-allocating function names (last in chain)
            let allocating_funcs = [
                "new", "clone", "format", "concat", "to_str", "to_lowercase",
                "split", "read_file", "Str", "Vec", "Set", "Map", "Array",
            ];
            if allocating_funcs.contains(&last.as_str()) {
                return true;
            }
            // Constructor calls: single identifier matching a type name (e.g., MyStruct(...))
            // Skip namespace-qualified calls like "Lexer.peek" (contains dot).
            if chain.len() == 1 && !chain[0].contains('.') {
                let first_char = chain[0].chars().next().unwrap_or('a');
                if first_char.is_uppercase() {
                    return true;
                }
            }
            false
        }
        _ => false,
    }
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

/// Build AST for var = Type.clone(var): Assignment with RHS = clone FCall.
/// Used to break shallow-copy aliasing after container get/pop calls.
fn build_clone_assignment_expr(type_name: &str, var_name: &str, line: usize, col: usize) -> Expr {
    let var_expr = Expr::new_explicit(
        NodeType::Identifier(var_name.to_string()), vec![], line, col);
    let clone_call = build_clone_call_expr(type_name, var_expr, line, col);
    Expr::new_explicit(
        NodeType::Assignment(var_name.to_string()), vec![clone_call], line, col)
}

/// Check if stmt is a container get/pop call with a shallow-copy out-param.
/// Returns (var_name, type_name) if the out-param is a local with deletable type.
fn detect_shallow_copy_outparam(stmt: &Expr, local_types: &HashMap<String, String>, context: &Context) -> Option<(String, String)> {
    if !matches!(&stmt.node_type, NodeType::FCall(_)) {
        return None;
    }
    let chain = get_fcall_identifier_chain(stmt);
    if chain.is_empty() {
        return None;
    }
    let resolved = resolve_fcall_from_chain(&chain, local_types, context)?;
    let func_def = &resolved.func_def;

    // Build "Type.method" name from resolved func_def's first arg type
    if func_def.args.is_empty() {
        return None;
    }
    let self_type = match &func_def.args[0].value_type {
        ValueType::TCustom(t) => t.clone(),
        _ => return None,
    };
    let method_name = &chain[chain.len() - 1];
    let qualified = format!("{}.{}", self_type, method_name);

    // Check against whitelist
    let whitelist = [
        "Vec.get", "Vec.pop", "Array.get", "Set.get",
        "Map.get", "HashMap.get", "List.get", "List.pop",
    ];
    if !whitelist.contains(&qualified.as_str()) {
        return None;
    }

    // Find last mut arg (the out-param)
    let last_arg_idx = func_def.args.len() - 1;
    if !func_def.args[last_arg_idx].is_mut {
        return None;
    }

    // Map to call-site param index
    let param_idx = if resolved.is_ufcs { last_arg_idx } else { last_arg_idx + 1 };
    if param_idx >= stmt.params.len() {
        return None;
    }

    // Check if call-site param is a bare identifier
    let param_expr = &stmt.params[param_idx];
    if let NodeType::Identifier(var_name) = &param_expr.node_type {
        if param_expr.params.is_empty() {
            // Look up type in local_types
            if let Some(type_name) = local_types.get(var_name) {
                if is_deletable_type(type_name, context) {
                    return Some((var_name.clone(), type_name.clone()));
                }
            }
        }
    }
    None
}

/// Insert clone assignments after container get/pop calls in a statement list.
/// Recurses into nested Body nodes but not into FuncDef bodies.
fn insert_clone_after_get(stmts: &[Expr], local_types: &HashMap<String, String>, context: &Context) -> Vec<Expr> {
    let mut result = Vec::new();
    for stmt in stmts {
        // Recurse into nested bodies within this statement
        let processed = process_stmt_for_clone_after_get(stmt, local_types, context);
        result.push(processed.clone());
        // Check if this statement itself is a get/pop call
        if let Some((var_name, type_name)) = detect_shallow_copy_outparam(&processed, local_types, context) {
            result.push(build_clone_assignment_expr(&type_name, &var_name, processed.line, processed.col));
        }
    }
    result
}

/// Process a single statement: recurse into Body children, leave FuncDef alone.
fn process_stmt_for_clone_after_get(e: &Expr, local_types: &HashMap<String, String>, context: &Context) -> Expr {
    match &e.node_type {
        NodeType::FuncDef(_) => e.clone(), // separate scope, don't touch
        NodeType::Body => {
            let new_children = insert_clone_after_get(&e.params, local_types, context);
            Expr::new_explicit(e.node_type.clone(), new_children, e.line, e.col)
        }
        _ => {
            // Recurse into params (covers if/while/for/switch which store bodies as params)
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(process_stmt_for_clone_after_get(param, local_types, context));
            }
            Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col)
        }
    }
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
