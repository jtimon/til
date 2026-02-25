// Garbager phase: AST transformations for memory semantics.
// This phase runs after type checking, before UFCS.
// Issue #159: Insert clone() calls for deep copy semantics on struct assignments.

use std::collections::HashMap;
#[allow(unused_imports)]
use std::collections::HashSet;
use crate::rs::init::{Context, get_value_type};
use crate::rs::parser::{Expr, NodeType, ValueType, TTypeDef, FuncDef, FCallInfo, StructDef, EnumDef, NamespaceDef, Declaration};
#[allow(unused_imports)]
use crate::rs::typer::is_cast_call;

/// Result of resolving a function call, including UFCS detection.
struct ResolvedFCall {
    func_def: FuncDef,
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
            // Step 1: Strip dont_delete calls from the AST
            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                if is_dont_delete_call(stmt)? {
                    continue;
                }
                new_body.push(garbager_recursive(context, stmt)?);
            }

            // Build local name->type map for clone-after-get and own-transfer detection
            let mut local_types: HashMap<String, String> = HashMap::new();
            for arg_def in &func_def.sig.args {
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

            // Step 2.7: Insert clone-after-get for container methods with shallow out-params.
            let new_body = insert_clone_after_get(&new_body, &local_types, context)?;

            // Issue #191: Delete old value before reassignment of struct-typed locals.
            // Disabled: depends on Bug #192 (own through by-ref intermediary causes use-after-free).
            // let mut declared_types: HashMap<String, String> = HashMap::new();
            // let mut cast_vars: HashSet<String> = HashSet::new();
            // for stmt in &new_body {
            //     if let NodeType::Declaration(decl) = &stmt.node_type {
            //         if let ValueType::TCustom(type_name) = &decl.value_type {
            //             if !stmt.params.is_empty() && is_cast_call(&stmt.params[0]) {
            //                 cast_vars.insert(decl.name.clone());
            //             } else {
            //                 declared_types.insert(decl.name.clone(), type_name.clone());
            //             }
            //         }
            //     }
            // }
            // let new_body = insert_delete_before_reassignment(&new_body, &declared_types, &cast_vars);

            let new_func_def = FuncDef {
                sig: func_def.sig.clone(),
                arg_names: func_def.arg_names.clone(),
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
            // Recurse into ns default values
            let mut ns_new_default_values = HashMap::new();
            for (name, ns_value_expr) in &struct_def.ns.default_values {
                ns_new_default_values.insert(name.clone(), garbager_recursive(context, ns_value_expr)?);
            }
            let new_ns = NamespaceDef {
                members: struct_def.ns.members.clone(),
                default_values: ns_new_default_values,
            };
            let new_struct_def = StructDef {
                members: struct_def.members.clone(),
                default_values: new_default_values,
                ns: new_ns,
            };
            let mut struct_new_params = Vec::new();
            for param in &e.params {
                struct_new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(NodeType::StructDef(new_struct_def), struct_new_params, e.line, e.col))
        }
        // Recurse into EnumDef ns default values
        NodeType::EnumDef(enum_def) => {
            let mut ns_new_default_values = HashMap::new();
            for (name, ns_value_expr) in &enum_def.ns.default_values {
                ns_new_default_values.insert(name.clone(), garbager_recursive(context, ns_value_expr)?);
            }
            let new_ns = NamespaceDef {
                members: enum_def.ns.members.clone(),
                default_values: ns_new_default_values,
            };
            let new_enum_def = EnumDef {
                variants: enum_def.variants.clone(),
                methods: enum_def.methods.clone(),
                ns: new_ns,
            };
            Ok(Expr::new_explicit(NodeType::EnumDef(new_enum_def), e.params.clone(), e.line, e.col))
        }
        // Issue #159: Transform mut declarations with struct type where RHS is an identifier
        NodeType::Declaration(decl) => {
            // First, recursively transform children
            let mut decl_new_params = Vec::new();
            for param in &e.params {
                decl_new_params.push(garbager_recursive(context, param)?);
            }

            // Check if this is a mut declaration with struct type and identifier RHS
            // Identifier can have field access (x.y.z), we clone any identifier-based RHS
            if decl.is_mut && !decl_new_params.is_empty() {
                if let NodeType::Identifier(_) = &decl_new_params[0].node_type {
                    if let ValueType::TCustom(type_name) = &decl.value_type {
                        // Build clone call: Type.clone(rhs_expr)
                        let decl_rhs_expr = decl_new_params[0].clone();
                        let decl_clone_call = build_clone_call_expr(type_name, decl_rhs_expr, e.line, e.col);
                        let mut decl_transformed_params = vec![decl_clone_call];
                        decl_transformed_params.extend(decl_new_params.into_iter().skip(1));
                        return Ok(Expr::new_explicit(
                            e.node_type.clone(),
                            decl_transformed_params,
                            e.line,
                            e.col,
                        ));
                    }
                }
            }
            // No transformation needed
            Ok(Expr::new_explicit(e.node_type.clone(), decl_new_params, e.line, e.col))
        }
        // Issue #159: Transform FCall copy params with struct type where arg is an identifier
        NodeType::FCall(_) => {
            // First, recursively transform children
            let mut fcall_new_params = Vec::new();
            for param in &e.params {
                fcall_new_params.push(garbager_recursive(context, param)?);
            }
            // Transform copy params: wrap struct identifier args in Type.clone()
            transform_fcall_copy_params(context, e, &mut fcall_new_params)?;
            // Issue #159 Step 5: Transform struct literal fields
            transform_struct_literal_fields(context, e, &mut fcall_new_params)?;
            Ok(Expr::new_explicit(e.node_type.clone(), fcall_new_params, e.line, e.col))
        }
        // Issue #159 Step 6: Transform assignments with struct type where RHS is an identifier
        // Issue #191: Use get_value_type to infer RHS type (works for bare ids AND field access)
        NodeType::Assignment(_var_name) => {
            // First, recursively transform children
            let mut assign_new_params = Vec::new();
            for param in &e.params {
                assign_new_params.push(garbager_recursive(context, param)?);
            }

            // Clone identifier-based RHS (including field access like token.token_str)
            if !assign_new_params.is_empty() {
                if let NodeType::Identifier(_) = &assign_new_params[0].node_type {
                    // Use get_value_type to infer RHS type (works for bare ids AND field access)
                    if let Ok(ValueType::TCustom(type_name)) = get_value_type(context, &assign_new_params[0]) {
                        // Issue #91: Skip clone for FuncSig types (function pointers are just names)
                        let is_func_sig = context.scope_stack.lookup_symbol(&type_name)
                            .map(|s| s.value_type == ValueType::TType(TTypeDef::TFuncSig))
                            .unwrap_or(false);
                        if !is_func_sig {
                            let assign_rhs_expr = assign_new_params[0].clone();
                            let assign_clone_call = build_clone_call_expr(&type_name, assign_rhs_expr, e.line, e.col);
                            let mut assign_transformed_params = vec![assign_clone_call];
                            assign_transformed_params.extend(assign_new_params.into_iter().skip(1));
                            return Ok(Expr::new_explicit(
                                e.node_type.clone(),
                                assign_transformed_params,
                                e.line,
                                e.col,
                            ));
                        }
                    }
                }
            }
            // No transformation needed
            Ok(Expr::new_explicit(e.node_type.clone(), assign_new_params, e.line, e.col))
        }
        // Body: recurse into children, stripping dont_delete calls
        NodeType::Body => {
            let mut body_new_params = Vec::new();
            for param in &e.params {
                if is_dont_delete_call(param)? {
                    continue;
                }
                body_new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(e.node_type.clone(), body_new_params, e.line, e.col))
        }
        // Desugared-away node types: reject with lang_error
        NodeType::Switch => Err(e.lang_error(&context.path, "garbager", "Switch should have been desugared to if/else by desugarer phase")),
        NodeType::DefaultCase => Err(e.lang_error(&context.path, "garbager", "DefaultCase should have been desugared with Switch")),
        NodeType::Pattern(_) => Err(e.lang_error(&context.path, "garbager", "Pattern should have been desugared with Switch")),
        NodeType::ForIn(_) => Err(e.lang_error(&context.path, "garbager", "ForIn should have been desugared before garbager phase")),
        // Default: recurse into children
        _ => {
            let mut default_new_params = Vec::new();
            for param in &e.params {
                default_new_params.push(garbager_recursive(context, param)?);
            }
            Ok(Expr::new_explicit(e.node_type.clone(), default_new_params, e.line, e.col))
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
        NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
        vec![type_clone_access, src_expr],
        line,
        col,
    )
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

/// Build AST for Type.delete(var): FCall( Identifier("Type").Identifier("delete"), Identifier(var) )
/// Issue #191: Used to free old value before reassignment.
#[allow(dead_code)]
fn build_delete_call_expr(type_name: &str, var_name: &str, line: usize, col: usize) -> Expr {
    let delete_ident = Expr::new_explicit(
        NodeType::Identifier("delete".to_string()), vec![], line, col);
    let type_delete_access = Expr::new_explicit(
        NodeType::Identifier(type_name.to_string()), vec![delete_ident], line, col);
    let var_expr = Expr::new_explicit(
        NodeType::Identifier(var_name.to_string()), vec![], line, col);
    Expr::new_explicit(
        NodeType::FCall(FCallInfo { does_throw: false, is_bang: false }),
        vec![type_delete_access, var_expr], line, col)
}


/// Check if stmt is a container get/pop call with a shallow-copy out-param.
/// Returns (var_name, type_name) if the out-param is a local with deletable type.
fn detect_shallow_copy_outparam(stmt: &Expr, local_types: &HashMap<String, String>, context: &Context) -> Result<Option<(String, String)>, String> {
    if !matches!(&stmt.node_type, NodeType::FCall(_)) {
        return Ok(None);
    }
    let chain = get_fcall_identifier_chain(stmt);
    if chain.is_empty() {
        return Ok(None);
    }
    let resolved = match resolve_fcall_from_chain(&chain, local_types, context) {
        Some(r) => r,
        None => return Ok(None),
    };
    let func_def = &resolved.func_def;

    // Build "Type.method" name from resolved func_def's first arg type
    if func_def.sig.args.is_empty() {
        return Ok(None);
    }
    let self_type = match &func_def.sig.args[0].value_type {
        ValueType::TCustom(t) => t.clone(),
        _ => return Ok(None),
    };
    let method_name = &chain[chain.len() - 1];
    let qualified = format!("{}.{}", self_type, method_name);

    // Check against whitelist
    let whitelist = [
        "Vec.pop",
        "List.pop",
    ];
    if !whitelist.contains(&qualified.as_str()) {
        return Ok(None);
    }

    // Find last mut arg (the out-param)
    let last_arg_idx = func_def.sig.args.len() - 1;
    if !func_def.sig.args[last_arg_idx].is_mut {
        return Ok(None);
    }

    // Map to call-site param index
    let param_idx = if resolved.is_ufcs { last_arg_idx } else { last_arg_idx + 1 };
    if param_idx >= stmt.params.len() {
        return Ok(None);
    }

    // Check if call-site param is a bare identifier
    let param_expr = stmt.params.get(param_idx).unwrap();
    if let NodeType::Identifier(var_name) = &param_expr.node_type {
        if param_expr.params.is_empty() {
            // Look up type in local_types
            if let Some(type_name) = local_types.get(var_name) {
                return Ok(Some((var_name.clone(), type_name.clone())));
            }
        }
    }
    Ok(None)
}

/// Insert clone assignments after container get/pop calls in a statement list.
/// Recurses into nested Body nodes but not into FuncDef bodies.
fn insert_clone_after_get(stmts: &[Expr], local_types: &HashMap<String, String>, context: &Context) -> Result<Vec<Expr>, String> {
    let mut result = Vec::new();
    for stmt in stmts {
        // Recurse into nested bodies within this statement
        let processed = process_stmt_for_clone_after_get(stmt, local_types, context)?;
        result.push(processed.clone());
        // Check if this statement itself is a get/pop call
        if let Some((var_name, type_name)) = detect_shallow_copy_outparam(&processed, local_types, context)? {
            result.push(build_clone_assignment_expr(&type_name, &var_name, processed.line, processed.col));
        }
    }
    Ok(result)
}

/// Process a single statement: recurse into Body children, leave FuncDef alone.
fn process_stmt_for_clone_after_get(e: &Expr, local_types: &HashMap<String, String>, context: &Context) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::FuncDef(_) => Ok(e.clone()), // separate scope, don't touch
        NodeType::Body => {
            let new_children = insert_clone_after_get(&e.params, local_types, context)?;
            Ok(Expr::new_explicit(e.node_type.clone(), new_children, e.line, e.col))
        }
        _ => {
            // Recurse into params (covers if/while/for/switch which store bodies as params)
            let mut new_params = Vec::new();
            for param in &e.params {
                new_params.push(process_stmt_for_clone_after_get(param, local_types, context)?);
            }
            Ok(Expr::new_explicit(e.node_type.clone(), new_params, e.line, e.col))
        }
    }
}

/// Issue #191: Check if an expression tree contains a reference to a specific variable.
/// Used to avoid delete-before-reassignment when the RHS references the variable
/// being reassigned (would cause use-after-free).
#[allow(dead_code)]
fn expr_references_var(e: &Expr, var_name: &str) -> bool {
    if let NodeType::Identifier(name) = &e.node_type {
        if name == var_name {
            return true;
        }
    }
    for param in &e.params {
        if expr_references_var(param, var_name) {
            return true;
        }
    }
    false
}

/// Issue #191: Insert Type.delete(var) before reassignment of struct-typed locals.
/// Only processes top-level statements, no recursion into sub-bodies.
/// Skips variables in cast_vars (initialized from cast, hold borrowed values).
/// Skips when the RHS references the variable being reassigned (use-after-free).
#[allow(dead_code)]
fn insert_delete_before_reassignment(stmts: &[Expr], local_types: &HashMap<String, String>, cast_vars: &HashSet<String>) -> Vec<Expr> {
    let mut result = Vec::new();
    for stmt in stmts {
        // Only check top-level assignments, no recursion into sub-bodies for now
        if let NodeType::Assignment(var_name) = &stmt.node_type {
            if !cast_vars.contains(var_name) {
                if let Some(type_name) = local_types.get(var_name) {
                    // Skip if the RHS references the variable being reassigned
                    let rhs_references_var = if !stmt.params.is_empty() {
                        expr_references_var(&stmt.params[0], var_name)
                    } else {
                        false
                    };
                    if !rhs_references_var {
                        result.push(build_delete_call_expr(type_name, var_name, stmt.line, stmt.col));
                    }
                }
            }
        }
        result.push(stmt.clone());
    }
    result
}


/// Extract function name from FCall's first param (the name expression).
/// Returns "foo" for foo(x) or "Type.method" for Type.method(x).
fn get_func_name(e: &Expr) -> Result<String, String> {
    if e.params.is_empty() {
        return Ok(String::new());
    }
    let name_expr = e.params.get(0).unwrap();
    match &name_expr.node_type {
        NodeType::Identifier(name) => {
            // Check for Type.method pattern: Identifier("Type") with child Identifier("method")
            if !name_expr.params.is_empty() {
                if let NodeType::Identifier(method) = &name_expr.params.get(0).unwrap().node_type {
                    return Ok(format!("{}.{}", name, method));
                }
            }
            Ok(name.clone())
        }
        _ => Ok(String::new()),
    }
}

/// Check if an expression is an Identifier node.
fn is_identifier_expr(e: &Expr) -> bool {
    matches!(&e.node_type, NodeType::Identifier(_))
}

/// Transform FCall copy params: for each arg that is_copy, struct-typed, and an identifier,
/// wrap in Type.clone().
fn transform_fcall_copy_params(context: &Context, e: &Expr, new_params: &mut Vec<Expr>) -> Result<(), String> {
    let func_name = get_func_name(e)?;
    if func_name.is_empty() {
        return Ok(());
    }

    // Skip .clone and .delete calls to avoid infinite recursion / double-free
    if func_name.ends_with(".clone") || func_name.ends_with(".delete") {
        return Ok(());
    }

    // Early out: check if any args (params[1..]) are identifiers
    let has_identifier_arg = new_params.iter().skip(1).any(|p| is_identifier_expr(p));
    if !has_identifier_arg {
        return Ok(());
    }

    // Look up function definition to get arg metadata
    let func_def = match context.scope_stack.lookup_func(&func_name) {
        Some(fd) => fd,
        None => return Ok(()),
    };

    // For each arg: if is_copy AND struct type AND identifier, wrap in Type.clone()
    let arg_defs: &Vec<Declaration> = &func_def.sig.args;
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
            let arg_expr = new_params[param_idx].clone();
            let clone_call = build_clone_call_expr(type_name, arg_expr, e.line, e.col);
            new_params[param_idx] = clone_call;
        }
    }
    Ok(())
}

/// Check if an expression is an FCall to `dont_delete`.
fn is_dont_delete_call(e: &Expr) -> Result<bool, String> {
    if let NodeType::FCall(_) = &e.node_type {
        let name = get_func_name(e)?;
        if !name.is_empty() {
            return Ok(name == "dont_delete");
        }
    }
    Ok(false)
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

/// Issue #159 Step 5: Transform struct literal fields.
/// For struct literal constructors like Point(inner=some_var), if a NamedArg value
/// is an identifier pointing to a struct type, wrap it in Type.clone().
fn transform_struct_literal_fields(context: &Context, e: &Expr, new_params: &mut Vec<Expr>) -> Result<(), String> {
    // Extract the struct name from the original FCall (before child transforms)
    let struct_name = get_func_name(e)?;
    if struct_name.is_empty() {
        return Ok(());
    }

    // Must be a plain struct name (no dots - not a method call)
    if struct_name.contains('.') {
        return Ok(());
    }

    // Check if it's a struct
    let struct_def = match context.scope_stack.lookup_struct(&struct_name) {
        Some(sd) => sd.clone(),
        None => return Ok(()),
    };

    // For each child in new_params[1..] that is a NamedArg
    for param_idx in 1..new_params.len() {
        if let NodeType::NamedArg(field_name) = &new_params[param_idx].node_type {
            // Find matching field in struct def members
            let field_decl = match struct_def.get_member(field_name) {
                Some(decl) => decl,
                None => continue,
            };
            if let ValueType::TCustom(type_name) = &field_decl.value_type {
                // Issue #91: Skip FuncSig types (function pointers don't need clone)
                let is_func_sig = context.scope_stack.lookup_symbol(type_name)
                    .map(|s| s.value_type == ValueType::TType(TTypeDef::TFuncSig))
                    .unwrap_or(false);
                if is_func_sig {
                    continue;
                }
                // Check if the NamedArg's value (params[0]) is an identifier
                if !new_params[param_idx].params.is_empty() && is_identifier_expr(new_params[param_idx].params.get(0).unwrap()) {
                    let arg_expr = new_params[param_idx].params.get(0).unwrap().clone();
                    let clone_call = build_clone_call_expr(type_name, arg_expr, e.line, e.col);
                    new_params[param_idx].params[0] = clone_call;
                }
            }
        }
    }
    Ok(())
}
