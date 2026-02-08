// Garbager phase: AST transformations for memory semantics.
// This phase runs after type checking, before UFCS.
// Issue #159: Insert clone() calls for deep copy semantics on struct assignments.
// Issue #117: Insert delete() calls for automatic memory management.

use std::collections::{HashMap, HashSet};
use crate::rs::init::Context;
use crate::rs::parser::{Expr, NodeType, ValueType, SFuncDef, SStructDef, SNamespaceDef, Declaration};

/// Garbager phase entry point: Transform AST for proper memory semantics.
pub fn garbager_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    garbager_recursive(context, e)
}

/// Check if a type is deletable (non-primitive struct type).
/// Used for both clone insertion and delete insertion.
fn is_deletable_type(value_type: &ValueType, context: &Context) -> bool {
    if let ValueType::TCustom(type_name) = value_type {
        let is_primitive = matches!(type_name.as_str(), "I64" | "U8" | "Type" | "Dynamic" | "Ptr");
        !is_primitive && context.scope_stack.has_struct(type_name)
    } else {
        false
    }
}

/// Recursively transform the AST.
fn garbager_recursive(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(garbager_recursive(context, stmt)?);
            }

            // Issue #117: Collect param candidates for delete insertion
            let mut param_candidates: Vec<(String, String)> = Vec::new();
            for arg in &func_def.args {
                if (arg.is_copy || arg.is_own) && arg.name != "_" {
                    if let ValueType::TCustom(type_name) = &arg.value_type {
                        if is_deletable_type(&arg.value_type, context) {
                            param_candidates.push((arg.name.clone(), type_name.clone()));
                        }
                    }
                }
            }

            // Issue #117: Collect own-transfers and remove from candidates
            let own_transferred = collect_own_transfers(&new_body, context);
            param_candidates.retain(|(name, _)| !own_transferred.contains(name));

            // Issue #117: Insert delete calls
            new_body = insert_deletes_in_stmts(&new_body, &param_candidates, &own_transferred, context);

            let new_func_def = SFuncDef {
                function_type: func_def.function_type.clone(),
                args: func_def.args.clone(),
                return_types: func_def.return_types.clone(),
                throw_types: func_def.throw_types.clone(),
                body: new_body,
                source_path: func_def.source_path.clone(),
            };
            // Also recurse into params (e.g., default argument values)
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
                    if is_deletable_type(&decl.value_type, context) {
                        if let ValueType::TCustom(type_name) = &decl.value_type {
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
                            if is_deletable_type(&sym.value_type, context) {
                                if let ValueType::TCustom(type_name) = &sym.value_type {
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

/// Build AST for Type.delete(var): FCall( Identifier("Type").Identifier("delete"), Identifier(var) )
fn build_delete_call_expr(type_name: &str, var_name: &str, line: usize, col: usize) -> Expr {
    // Type.delete access: Identifier("Type") with child Identifier("delete")
    let delete_ident = Expr::new_explicit(
        NodeType::Identifier("delete".to_string()),
        vec![],
        line,
        col,
    );
    let type_delete_access = Expr::new_explicit(
        NodeType::Identifier(type_name.to_string()),
        vec![delete_ident],
        line,
        col,
    );

    // Variable identifier
    let var_ident = Expr::new_explicit(
        NodeType::Identifier(var_name.to_string()),
        vec![],
        line,
        col,
    );

    // FCall node
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![type_delete_access, var_ident],
        line,
        col,
    )
}

/// Recursively collect all variable names referenced in an expression.
/// Used to avoid deleting variables that are still used in return/throw expressions.
fn collect_referenced_vars(e: &Expr, result: &mut HashSet<String>) {
    if let NodeType::Identifier(name) = &e.node_type {
        result.insert(name.clone());
    }
    for param in &e.params {
        collect_referenced_vars(param, result);
    }
}

/// Recursively scan all FCalls in stmts. For each FCall, look up the function
/// definition and collect variables that should NOT be auto-deleted:
/// - Variables passed as `own` params (ownership transferred to callee)
/// - Variables passed as non-self `mut` params (may be overwritten with aliased data,
///   e.g. Vec.get writes shallow-copied data into the mut dest param)
fn collect_own_transfers(stmts: &[Expr], context: &Context) -> HashSet<String> {
    let mut result = HashSet::new();
    for stmt in stmts {
        collect_own_transfers_recursive(stmt, context, &mut result);
    }
    result
}

fn collect_own_transfers_recursive(e: &Expr, context: &Context, result: &mut HashSet<String>) {
    if let NodeType::FCall(_) = &e.node_type {
        // Look up function to check for own/mut params
        if let Some(func_name) = get_func_name(e) {
            if let Some(func_def) = context.scope_stack.lookup_func(&func_name) {
                let func_def = func_def.clone();
                for (i, arg_def) in func_def.args.iter().enumerate() {
                    let param_idx = i + 1; // params[0] is the function name
                    if param_idx >= e.params.len() {
                        break;
                    }
                    // own params: ownership transferred
                    // mut params (non-self, i > 0): may be overwritten with aliased data
                    let dominated = arg_def.is_own || (arg_def.is_mut && i > 0);
                    if dominated {
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
    // Recurse into all children
    for param in &e.params {
        collect_own_transfers_recursive(param, context, result);
    }
    // Recurse into FuncDef body if present
    if let NodeType::FuncDef(func_def) = &e.node_type {
        for stmt in &func_def.body {
            collect_own_transfers_recursive(stmt, context, result);
        }
    }
}

/// Insert delete calls into a statement list.
/// inherited: candidates from outer scope (param candidates or parent block locals)
/// own_transferred: variables that were own-transferred (excluded from delete)
fn insert_deletes_in_stmts(
    stmts: &[Expr],
    inherited: &[(String, String)],
    own_transferred: &HashSet<String>,
    context: &Context,
) -> Vec<Expr> {
    let mut local_candidates: Vec<(String, String)> = Vec::new();
    let mut result: Vec<Expr> = Vec::new();

    // Pre-scan: collect catch variable names in this scope.
    // Catch variables shadow outer variables of the same name, and the C codegen
    // uses a flat function scope for name mangling, so we must exclude shadowed names.
    let mut catch_var_names: HashSet<String> = HashSet::new();
    for stmt in stmts {
        if let NodeType::Catch = &stmt.node_type {
            if let Some(name_expr) = stmt.params.first() {
                if let NodeType::Identifier(catch_var_name) = &name_expr.node_type {
                    catch_var_names.insert(catch_var_name.clone());
                }
            }
        }
    }

    // Filter inherited candidates that are shadowed by catch variables in this scope
    let inherited: Vec<(String, String)> = inherited.iter()
        .filter(|(name, _)| !catch_var_names.contains(name))
        .cloned()
        .collect();
    let inherited = &inherited[..];

    for stmt_idx in 0..stmts.len() {
        let stmt = &stmts[stmt_idx];
        match &stmt.node_type {
            NodeType::Declaration(decl) => {
                // Skip _ wildcard variables and variables shadowed by catch params
                if decl.name != "_"
                    && !catch_var_names.contains(&decl.name)
                    && is_deletable_type(&decl.value_type, context)
                    && !own_transferred.contains(&decl.name)
                {
                    // Issue #117: Only add if the value is owned, not an alias.
                    // For const declarations with identifier RHS, no clone was inserted
                    // by garbager_recursive, so the local aliases the source data.
                    // Deleting both would cause a double free.
                    let is_alias = !decl.is_mut && stmt.params.first().map_or(false, |rhs| {
                        matches!(&rhs.node_type, NodeType::Identifier(_))
                    });
                    if !is_alias {
                        if let ValueType::TCustom(type_name) = &decl.value_type {
                            local_candidates.push((decl.name.clone(), type_name.clone()));
                        }
                    }
                }
                result.push(stmt.clone());
            }

            NodeType::Return => {
                // Collect all variable names referenced from here to end of body
                // (desugared ? creates temp vars that reference candidates in preceding stmts)
                let mut referenced = HashSet::new();
                for s in &stmts[stmt_idx..] {
                    collect_referenced_vars(s, &mut referenced);
                }
                // Delete all candidates in reverse order (locals then inherited)
                let mut all: Vec<(String, String)> = inherited.to_vec();
                all.extend(local_candidates.iter().cloned());
                for (var_name, type_name) in all.iter().rev() {
                    if referenced.contains(var_name) {
                        continue;
                    }
                    result.push(build_delete_call_expr(type_name, var_name, stmt.line, stmt.col));
                }
                result.push(stmt.clone());
            }

            NodeType::Throw => {
                // Collect all variable names referenced from here to end of body
                let mut referenced = HashSet::new();
                for s in &stmts[stmt_idx..] {
                    collect_referenced_vars(s, &mut referenced);
                }
                // Delete all candidates in reverse order before throw
                let mut all: Vec<(String, String)> = inherited.to_vec();
                all.extend(local_candidates.iter().cloned());
                for (var_name, type_name) in all.iter().rev() {
                    if referenced.contains(var_name) {
                        continue;
                    }
                    result.push(build_delete_call_expr(type_name, var_name, stmt.line, stmt.col));
                }
                result.push(stmt.clone());
            }

            NodeType::Assignment(var_name) => {
                // Issue #117: Field assignment (e.g. l.tokens = tokens) transfers ownership.
                // If RHS is a local candidate, remove it - the struct now owns the value.
                if var_name.contains('.') {
                    if let Some(rhs) = stmt.params.first() {
                        if let NodeType::Identifier(rhs_name) = &rhs.node_type {
                            if rhs.params.is_empty() {
                                local_candidates.retain(|(name, _)| name != rhs_name);
                            }
                        }
                    }
                }

                // Check if we're reassigning a tracked variable - delete old value first
                let mut all: Vec<(String, String)> = inherited.to_vec();
                all.extend(local_candidates.iter().cloned());
                for (cand_name, cand_type) in &all {
                    if cand_name == var_name {
                        result.push(build_delete_call_expr(cand_type, var_name, stmt.line, stmt.col));
                        break;
                    }
                }
                result.push(stmt.clone());
            }

            NodeType::If => {
                // Process then-body and else-body with combined inherited + local candidates
                let mut child_inherited: Vec<(String, String)> = inherited.to_vec();
                child_inherited.extend(local_candidates.iter().cloned());

                let mut new_if_params: Vec<Expr> = Vec::new();
                // params[0] = condition (pass through)
                new_if_params.push(stmt.params[0].clone());
                // params[1] = then body (Body node)
                if stmt.params.len() > 1 {
                    let then_body = &stmt.params[1];
                    let new_then_stmts = insert_deletes_in_stmts(
                        &then_body.params, &child_inherited, own_transferred, context,
                    );
                    new_if_params.push(Expr::new_explicit(
                        then_body.node_type.clone(), new_then_stmts, then_body.line, then_body.col,
                    ));
                }
                // params[2] = else body or else-if (optional)
                if stmt.params.len() > 2 {
                    let else_part = &stmt.params[2];
                    match &else_part.node_type {
                        NodeType::Body => {
                            let new_else_stmts = insert_deletes_in_stmts(
                                &else_part.params, &child_inherited, own_transferred, context,
                            );
                            new_if_params.push(Expr::new_explicit(
                                else_part.node_type.clone(), new_else_stmts, else_part.line, else_part.col,
                            ));
                        }
                        NodeType::If => {
                            // Nested else-if: wrap in a slice and process
                            let new_else_stmts = insert_deletes_in_stmts(
                                &[else_part.clone()], &child_inherited, own_transferred, context,
                            );
                            if !new_else_stmts.is_empty() {
                                new_if_params.push(new_else_stmts[0].clone());
                            }
                        }
                        _ => {
                            new_if_params.push(else_part.clone());
                        }
                    }
                }
                result.push(Expr::new_explicit(
                    stmt.node_type.clone(), new_if_params, stmt.line, stmt.col,
                ));
            }

            NodeType::While => {
                // Process while body with combined inherited + local candidates
                let mut child_inherited: Vec<(String, String)> = inherited.to_vec();
                child_inherited.extend(local_candidates.iter().cloned());

                let mut new_while_params: Vec<Expr> = Vec::new();
                // params[0] = condition (pass through)
                new_while_params.push(stmt.params[0].clone());
                // params[1] = body (Body node)
                if stmt.params.len() > 1 {
                    let body = &stmt.params[1];
                    let new_body_stmts = insert_deletes_in_stmts(
                        &body.params, &child_inherited, own_transferred, context,
                    );
                    new_while_params.push(Expr::new_explicit(
                        body.node_type.clone(), new_body_stmts, body.line, body.col,
                    ));
                }
                result.push(Expr::new_explicit(
                    stmt.node_type.clone(), new_while_params, stmt.line, stmt.col,
                ));
            }

            NodeType::Catch => {
                // Process catch body with combined inherited + local candidates
                let mut child_inherited: Vec<(String, String)> = inherited.to_vec();
                child_inherited.extend(local_candidates.iter().cloned());

                // Remove any candidate shadowed by the catch variable
                if let NodeType::Identifier(catch_var_name) = &stmt.params[0].node_type {
                    child_inherited.retain(|(name, _)| name != catch_var_name);
                }

                let mut new_catch_params: Vec<Expr> = Vec::new();
                // params[0] = error variable name (pass through)
                new_catch_params.push(stmt.params[0].clone());
                // params[1] = error type (pass through)
                new_catch_params.push(stmt.params[1].clone());
                // params[2] = catch body (Body node)
                if stmt.params.len() > 2 {
                    let body = &stmt.params[2];
                    let new_body_stmts = insert_deletes_in_stmts(
                        &body.params, &child_inherited, own_transferred, context,
                    );
                    new_catch_params.push(Expr::new_explicit(
                        body.node_type.clone(), new_body_stmts, body.line, body.col,
                    ));
                }
                result.push(Expr::new_explicit(
                    stmt.node_type.clone(), new_catch_params, stmt.line, stmt.col,
                ));
            }

            _ => {
                result.push(stmt.clone());
            }
        }
    }

    // End of body: delete LOCAL candidates only (not inherited)
    // Only if last stmt is not Return or Throw
    let last_is_exit = stmts.last().map_or(false, |s| {
        matches!(&s.node_type, NodeType::Return | NodeType::Throw)
    });
    if !last_is_exit {
        for (var_name, type_name) in local_candidates.iter().rev() {
            let line = stmts.last().map_or(0, |s| s.line);
            let col = stmts.last().map_or(0, |s| s.col);
            result.push(build_delete_call_expr(type_name, var_name, line, col));
        }
    }

    result
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
            if is_deletable_type(&arg_def.value_type, context) {
                let arg_expr = new_params[param_idx].clone();
                let clone_call = build_clone_call_expr(type_name, arg_expr, e.line, e.col);
                new_params[param_idx] = clone_call;
            }
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
                if !is_deletable_type(&field_decl.value_type, context) {
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
