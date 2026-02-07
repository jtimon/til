// Garbager phase: AST transformations for memory semantics.
// This phase runs after type checking, before UFCS.
// Issue #159: Insert clone() calls for deep copy semantics on struct assignments.

use std::collections::HashMap;
use crate::rs::init::Context;
use crate::rs::parser::{Expr, NodeType, ValueType, SFuncDef, SStructDef, SNamespaceDef, Declaration};

/// Garbager phase entry point: Transform AST for proper memory semantics.
pub fn garbager_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    garbager_recursive(context, e)
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
                    if let ValueType::TCustom(type_name) = &decl.value_type {
                        // Exclude true primitive types - they don't need deep cloning
                        // Note: Bool is NOT excluded because true/false are global constants
                        // that would be corrupted if we just share offsets
                        let is_primitive = matches!(type_name.as_str(), "I64" | "U8" | "Str" | "Type" | "Dynamic");
                        if !is_primitive && context.scope_stack.has_struct(type_name) {
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
            let is_primitive = matches!(type_name.as_str(), "I64" | "U8" | "Str" | "Type" | "Dynamic");
            if !is_primitive && context.scope_stack.has_struct(type_name) {
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
                let is_primitive = matches!(type_name.as_str(), "I64" | "U8" | "Str" | "Type" | "Dynamic");
                if is_primitive || !context.scope_stack.has_struct(type_name) {
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
