// UFCS phase: Resolves Uniform Function Call Syntax into regular function calls
// and reorders named arguments to positional order.
// This phase runs after desugarer, before precomp.

use crate::rs::init::{Context, get_value_type, SymbolInfo, ScopeType};
use crate::rs::typer::func_proc_has_multi_arg;
use crate::rs::parser::{
    Expr, NodeType, ValueType, StructDef, EnumDef, FuncDef, FCallInfo, NamespaceDef, INFER_TYPE,
};

// ---------- Named argument reordering

/// Reorder named arguments to match function parameter order.
/// Transforms: func(b=3, a=10) -> func(10, 3) (for func(a, b))
/// This runs during precomp so both interpreter and builder share the work.
fn reorder_named_args(context: &Context, e: &Expr, func_def: &FuncDef) -> Result<Expr, String> {
    // params[0] is the function identifier, params[1..] are the arguments
    let call_args = if e.params.len() <= 1 {
        &[][..] // No arguments
    } else {
        &e.params[1..]
    };

    // Check if function is variadic - named args and default filling not supported
    let is_variadic = func_proc_has_multi_arg(func_def);

    // Check if there are any named args
    let mut has_named_args = false;
    for arg in call_args {
        if matches!(&arg.node_type, NodeType::NamedArg(_)) {
            has_named_args = true;
            break;
        }
    }

    // Named args are not supported for variadic functions
    if has_named_args && is_variadic {
        return Err(e.error(&context.path, "ufcs", "Named arguments are not supported for variadic functions"));
    }

    // Bug #61: Check if there are optional args before variadic that might need defaults
    // This happens when the provided arg type doesn't match the optional arg type
    let has_optional_before_variadic = is_variadic && func_def.sig.args.len() > 1 &&
        func_def.sig.args.iter().take(func_def.sig.args.len() - 1).any(|a| a.default_value.is_some());

    // Check if we need to fill in default values (fewer args than params)
    // Don't apply to variadic functions (unless they have optional args before the variadic)
    let needs_defaults = (!is_variadic && call_args.len() < func_def.sig.args.len()) || has_optional_before_variadic;

    // If no named args and no defaults needed, return unchanged
    if !has_named_args && !needs_defaults {
        return Ok(e.clone());
    }

    let mut result = vec![e.params.get(0).unwrap().clone()]; // Keep function identifier

    // Bug #61: Handle variadic functions with optional args before the variadic
    // Need to insert defaults for skipped optional args, then include all provided args
    if has_optional_before_variadic {
        let mut def_arg_idx: usize = 0;
        let mut call_arg_idx: usize = 0;

        // Process optional args before the variadic
        while def_arg_idx < func_def.sig.args.len() - 1 {  // -1 to stop before variadic
            let opt_def_arg = &func_def.sig.args[def_arg_idx];

            // Check if we have a provided arg that matches this def arg's type
            let mut matches = false;
            if call_arg_idx < call_args.len() {
                let provided_arg = &call_args[call_arg_idx];
                if let Ok(found_type) = get_value_type(&context, provided_arg) {
                    let expected = &opt_def_arg.value_type;
                    matches = match expected {
                        ValueType::TCustom(tn) if tn == "Dynamic" || tn == "Type" => true,
                        _ => expected == &found_type,
                    };
                }
            }

            if matches {
                // Use provided arg
                result.push(call_args[call_arg_idx].clone());
                call_arg_idx += 1;
            } else if let Some(opt_default_expr) = &opt_def_arg.default_value {
                // Use default
                result.push((**opt_default_expr).clone());
            } else {
                return Err(e.error(&context.path, "ufcs", &format!("Missing argument for non-optional parameter '{}'", opt_def_arg.name)));
            }
            def_arg_idx += 1;
        }

        // Add remaining provided args (for variadic)
        for i in call_arg_idx..call_args.len() {
            result.push(call_args[i].clone());
        }

        // Issue #132: Preserve does_throw flag from original FCall
        let fcall_info = if let NodeType::FCall(ref info) = e.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
        return Ok(Expr::new_clone(NodeType::FCall(fcall_info), e, result));
    }

    // Count positional args (before first named arg)
    let mut positional_count = 0;
    for arg in call_args {
        if let NodeType::NamedArg(_) = &arg.node_type {
            break;
        }
        positional_count += 1;
    }

    // Check that all named args come after positional args
    let mut seen_named = false;
    for arg in call_args {
        if let NodeType::NamedArg(_) = &arg.node_type {
            seen_named = true;
        } else if seen_named {
            return Err(e.error(&context.path, "ufcs", "Positional arguments cannot appear after named arguments"));
        }
    }

    // Build result: first positional args, then fill in from named args
    let mut final_args: Vec<Option<Expr>> = vec![None; func_def.sig.args.len()];

    // Place positional arguments
    for (i, arg) in call_args.iter().take(positional_count).enumerate() {
        if i >= func_def.sig.args.len() {
            return Err(e.error(&context.path, "ufcs", &format!("Too many positional arguments: expected at most {}", func_def.sig.args.len())));
        }
        final_args[i] = Some(arg.clone());
    }

    // Place named arguments
    for arg in call_args.iter().skip(positional_count) {
        if let NodeType::NamedArg(arg_name) = &arg.node_type {
            // Find the parameter index by name
            let mut param_idx: Option<usize> = None;
            for (i, p) in func_def.sig.args.iter().enumerate() {
                if &p.name == arg_name {
                    param_idx = Some(i);
                    break;
                }
            }
            match param_idx {
                Some(idx) => {
                    if final_args[idx].is_some() {
                        return Err(arg.error(&context.path, "ufcs", &format!("Argument '{}' specified multiple times", arg_name)));
                    }
                    // Extract the value from the NamedArg
                    if arg.params.is_empty() {
                        return Err(arg.error(&context.path, "ufcs", &format!("Named argument '{}' has no value", arg_name)));
                    }
                    final_args[idx] = Some(arg.params.get(0).unwrap().clone());
                },
                None => {
                    return Err(arg.error(&context.path, "ufcs", &format!("Unknown parameter name '{}'", arg_name)));
                }
            }
        }
    }

    // Check all required args are present and build final result
    for (i, maybe_arg) in final_args.into_iter().enumerate() {
        match maybe_arg {
            Some(arg) => result.push(arg),
            None => {
                // Check if this parameter has a default value
                if let Some(default_expr) = &func_def.sig.args[i].default_value {
                    result.push((**default_expr).clone());
                } else {
                    return Err(e.error(&context.path, "ufcs", &format!("Missing argument for parameter '{}'", func_def.sig.args[i].name)));
                }
            }
        }
    }

    // Issue #132: Preserve does_throw flag from original FCall
    let fcall_info = if let NodeType::FCall(ref info) = e.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
    Ok(Expr::new_clone(NodeType::FCall(fcall_info), e, result))
}

// ---------- Main entry point

/// UFCS phase: Transform UFCS calls into regular function calls.
/// Takes an AST that has already passed type checking and desugaring.
///
/// Examples:
///   a.add(b)         -> I64.add(a, b)     (where a is I64)
///   obj.items.len()  -> Vec.len(obj.items)
///   add(1, 2).mul(3) -> I64.mul(add(1, 2), 3)
pub fn ufcs_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::Body => ufcs_body(context, e),
        NodeType::FCall(_) => ufcs_fcall(context, e),
        NodeType::If => ufcs_params(context, e),
        NodeType::While => ufcs_params(context, e),
        // Switch should have been desugared in desugarer phase
        NodeType::Switch => {
            panic!("Switch should have been desugared in desugarer phase");
        },
        NodeType::FuncDef(func_def) => ufcs_func_def(context, e, func_def.clone()),
        NodeType::Declaration(decl) => ufcs_declaration(context, e, decl),
        NodeType::Assignment(_) => ufcs_params(context, e),
        NodeType::Return | NodeType::Throw => ufcs_params(context, e),
        NodeType::Catch => ufcs_catch(context, e),
        NodeType::Range => ufcs_params(context, e),
        // Struct/enum definitions - need to process default values (which may contain function defs)
        NodeType::StructDef(struct_def) => ufcs_struct_def(context, e, struct_def),
        NodeType::EnumDef(enum_def) => {
            // Recurse into ns default values
            let mut ns_new_default_values = std::collections::HashMap::new();
            for (name, value_expr) in &enum_def.ns.default_values {
                ns_new_default_values.insert(name.clone(), ufcs_expr(context, value_expr)?);
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
            Ok(Expr::new_clone(NodeType::EnumDef(new_enum_def), e, e.params.clone()))
        },
        // Identifiers can have nested params (e.g., a.b.c for field access chains)
        NodeType::Identifier(_) => ufcs_params(context, e),
        // Leaf nodes - no transformation needed
        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => Ok(e.clone()),
        // Break and Continue are leaf nodes (no params) - no transformation needed
        NodeType::Break | NodeType::Continue => Ok(e.clone()),
        // Named arguments - transform the value expression
        NodeType::NamedArg(name) => {
            let mut new_params = Vec::new();
            for p in &e.params {
                new_params.push(ufcs_expr(context, p)?);
            }
            Ok(Expr::new_clone(NodeType::NamedArg(name.clone()), e, new_params))
        },
        // ForIn should have been desugared in desugarer phase
        NodeType::ForIn(_) => {
            panic!("ForIn should have been desugared in desugarer phase");
        },
        // Issue #188: Defer should have been desugared in desugarer phase
        NodeType::Defer => {
            panic!("Defer should have been desugared in desugarer phase");
        },
        // Issue #185: OwnArg should have been desugared in desugarer phase
        NodeType::OwnArg => {
            panic!("OwnArg should have been desugared in desugarer phase");
        },
    }
}

// ---------- AST transformation

/// Transform Body node - recursively transform all statements
fn ufcs_body(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let mut new_params = Vec::new();
    for p in &e.params {
        new_params.push(ufcs_expr(context, p)?);
    }
    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform node params - recursively transform all child expressions
fn ufcs_params(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let mut new_params = Vec::new();
    for p in &e.params {
        new_params.push(ufcs_expr(context, p)?);
    }
    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform StructDef - recursively transform default values (which contain function defs)
fn ufcs_struct_def(context: &mut Context, e: &Expr, struct_def: &StructDef) -> Result<Expr, String> {
    let mut new_default_values = std::collections::HashMap::new();
    for (name, value_expr) in &struct_def.default_values {
        new_default_values.insert(name.clone(), ufcs_expr(context, value_expr)?);
    }
    // Recurse into ns default values
    let mut ns_new_default_values = std::collections::HashMap::new();
    for (name, value_expr) in &struct_def.ns.default_values {
        ns_new_default_values.insert(name.clone(), ufcs_expr(context, value_expr)?);
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
    Ok(Expr::new_clone(NodeType::StructDef(new_struct_def), e, e.params.clone()))
}

/// Transform FuncDef - push scope frame for function args, transform body, pop frame
fn ufcs_func_def(context: &mut Context, e: &Expr, func_def: FuncDef) -> Result<Expr, String> {
    // Push a new scope frame with the function's parameters
    context.scope_stack.push(ScopeType::Function);
    for arg in &func_def.sig.args {
        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
            value_type: arg.value_type.clone(),
            is_mut: arg.is_mut,
            is_copy: arg.is_copy,
            is_own: arg.is_own,
            is_comptime_const: false,  // Function args are not comptime constants
        });
    }

    // Transform the function body
    let mut new_body = Vec::new();
    for stmt in &func_def.body {
        new_body.push(ufcs_expr(context, stmt)?);
    }

    // Pop the function scope frame
    let _ = context.scope_stack.pop();

    let new_func_def = FuncDef {
        sig: func_def.sig.clone(),
        arg_names: func_def.arg_names.clone(),
        body: new_body,
        source_path: func_def.source_path.clone(),
    };
    Ok(Expr::new_clone(NodeType::FuncDef(new_func_def), e, e.params.clone()))
}

/// Transform Declaration - register the declared variable in scope, then transform value
fn ufcs_declaration(context: &mut Context, e: &Expr, decl: &crate::rs::parser::Declaration) -> Result<Expr, String> {
    // Get value type for the declared variable
    let inner_e = e.params.get(0).unwrap();
    let mut value_type = match get_value_type(context, &inner_e) {
        Ok(val_type) => val_type,
        Err(_) => ValueType::TCustom("Dynamic".to_string()), // Fallback for unresolved types
    };
    // Handle explicit type annotation (e.g., `mut val : U8 = 41`)
    // When declaration has explicit type and it differs from inferred type, use the explicit type
    if decl.value_type != ValueType::TCustom(INFER_TYPE.to_string()) {
        if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
            value_type = decl.value_type.clone();
        }
    }

    // For struct definitions, register the struct so methods can be resolved
    // Issue #108: Don't overwrite if struct already exists with merged namespace members
    if let NodeType::StructDef(struct_def) = &inner_e.node_type {
        if context.scope_stack.lookup_struct(&decl.name).is_none() {
            context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
        }
    }

    // For enum definitions, register the enum
    if let NodeType::EnumDef(enum_def) = &inner_e.node_type {
        context.scope_stack.declare_enum(decl.name.clone(), enum_def.clone());
    }

    // Bug #123: For function definitions, pre-register the function BEFORE transforming its body
    // This allows recursive nested functions to resolve UFCS on their own return type
    if let NodeType::FuncDef(func_def) = &inner_e.node_type {
        context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
    }

    // Transform the value expression
    let new_params = if !e.params.is_empty() {
        let mut new_params = Vec::new();
        for p in &e.params {
            new_params.push(ufcs_expr(context, p)?);
        }
        new_params
    } else {
        Vec::new()
    };

    // Register the declared variable in scope
    context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
        value_type: value_type.clone(),
        is_mut: decl.is_mut,
        is_copy: decl.is_copy,
        is_own: decl.is_own,
        is_comptime_const: false,  // Determined later in precomp
    });

    // Also register function definitions so UFCS can resolve their return types
    if !new_params.is_empty() {
        if let NodeType::FuncDef(func_def) = &new_params[0].node_type {
            context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
        }
    }

    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform Catch node - register the catch variable in scope before processing body
fn ufcs_catch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if e.params.len() < 3 {
        // Malformed catch - just use default handling
        return ufcs_params(context, e);
    }

    // Get the catch variable name and type
    let var_name = match &e.params.get(0).unwrap().node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return ufcs_params(context, e), // Not a simple identifier, use default handling
    };
    let type_name = match &e.params.get(1).unwrap().node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return ufcs_params(context, e), // Not a simple type, use default handling
    };

    // Push a scope frame for the catch block
    context.scope_stack.push(ScopeType::Catch);

    // Register the catch variable in the scope
    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(type_name),
        is_mut: false,
        is_copy: false,
        is_own: false,
        is_comptime_const: false,
    });

    // Transform the catch body (params[2])
    let new_body = ufcs_expr(context, e.params.get(2).unwrap())?;

    // Pop the scope frame
    let _ = context.scope_stack.pop();

    // Return the transformed catch with original var_name, type, and new body
    Ok(Expr::new_clone(
        NodeType::Catch,
        e,
        vec![e.params.get(0).unwrap().clone(), e.params.get(1).unwrap().clone(), new_body],
    ))
}

/// Transform FCall node - this is where UFCS resolution happens
fn ufcs_fcall(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Transform all arguments first
    let mut transformed_params = Vec::new();
    for p in &e.params {
        transformed_params.push(ufcs_expr(context, p)?);
    }
    let e = Expr::new_clone(e.node_type.clone(), &e, transformed_params);

    // Get func_expr from transformed expression
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Ok(e),
    };

    if let NodeType::Identifier(_id_name) = &func_expr.node_type {
        let combined_name = crate::rs::parser::get_combined_name(&context.path, func_expr)?;

        // UFCS for chained calls: func(result, args) -> Type.func(result, args)
        // e.g., or(a.and(b), c) becomes Bool.or(a.and(b), c) when Bool.or exists
        // Associated methods take priority over standalone functions (checked below)
        // because x.and(y) should resolve to Bool.and(x, y) not and(x, y) when both exist
        if e.params.len() >= 2 {
            let first_arg = e.params.get(1).unwrap();
            if let Ok(target_type) = get_value_type(context, first_arg) {
                // Get type name from value_type - TCustom or TMulti (variadic params become Array)
                let custom_type_name = match &target_type {
                    ValueType::TCustom(name) => Some(name.clone()),
                    ValueType::TMulti(_) => Some("Array".to_string()),
                    _ => None,
                };
                if let Some(type_name) = custom_type_name {
                    let method_name = format!("{}.{}", type_name, combined_name);
                    if let Some(method_def) = context.scope_stack.lookup_func(&method_name) {
                        // Only transform if argument count matches
                        // e.params includes func name at [0], so actual args are params.len() - 1
                        let call_arg_count = e.params.len() - 1;
                        let method_arg_count = method_def.sig.args.len();
                        // Check if method has variadic args (marked with TMulti value type)
                        let method_is_variadic = method_def.sig.args.iter().any(|arg| matches!(arg.value_type, ValueType::TMulti(_)));
                        if call_arg_count == method_arg_count || method_is_variadic {
                            // Transform: func(target, args...) -> Type.func(target, args...)
                            let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), e.params.get(0).unwrap(), Vec::new());
                            let mut new_args = Vec::new();
                            new_args.push(new_e);
                            new_args.extend(e.params[1..].to_vec());
                            // Issue #132: Preserve does_throw flag from original FCall
                            let fcall_info = if let NodeType::FCall(ref info) = e.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
                            return Ok(Expr::new_clone(NodeType::FCall(fcall_info), e.params.get(0).unwrap(), new_args));
                        }
                    }
                }
            }
        }

        // Regular function call - check if it exists (after associated method check)
        if let Some(func_def) = context.scope_stack.lookup_func(&combined_name) {
            // Reorder named arguments to positional order
            let e = reorder_named_args(context, &e, &func_def)?;
            return Ok(e);
        }

        // UFCS with dot notation (e.g., a.method(b) or a.field.method())
        if let Some(func_name_expr) = func_expr.params.last() {
            if let NodeType::Identifier(ufcs_func_name) = &func_name_expr.node_type {
                let mut parts: Vec<&str> = combined_name.split('.').collect();
                parts.pop(); // Remove the method name
                let _new_combined_name = parts.join(".");

                // Create identifier expression for the receiver (everything except the method name)
                let mut id_params = func_expr.params.clone();
                id_params.pop(); // Remove the method name
                let receiver_expr = Expr::new_clone(func_expr.node_type.clone(), &e, id_params);

                // Try as an associated method (Type.method) first - this takes priority over standalone functions
                // because x.and(y) should resolve to Bool.and(x, y) not and(x, y) when both exist
                match get_value_type(context, &receiver_expr) {
                    Ok(value_type) => {
                        // Get type name from value_type - TCustom or TMulti (variadic params become Array)
                        let custom_type_name = match &value_type {
                            ValueType::TCustom(name) => Some(name.clone()),
                            ValueType::TMulti(_) => Some("Array".to_string()),
                            _ => None,
                        };
                        if let Some(ref type_name) = custom_type_name {
                            let assoc_method_name = format!("{}.{}", type_name, ufcs_func_name);
                            if context.scope_stack.has_func(&assoc_method_name) {
                                let assoc_new_id_e = Expr::new_clone(NodeType::Identifier(assoc_method_name.clone()), e.params.get(0).unwrap(), Vec::new());
                                let mut assoc_new_args = Vec::new();
                                assoc_new_args.push(assoc_new_id_e);
                                assoc_new_args.push(receiver_expr);
                                assoc_new_args.extend(e.params[1..].to_vec());
                                // Issue #132: Preserve does_throw flag from original FCall
                                let fcall_info = if let NodeType::FCall(ref info) = e.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
                                return Ok(Expr::new_clone(NodeType::FCall(fcall_info), e.params.get(0).unwrap(), assoc_new_args));
                            }
                        }
                    }
                    Err(_err) => {
                        // Type could not be determined - fall through to standalone function check
                    }
                }

                // Fall back to standalone function
                if context.scope_stack.has_func(&ufcs_func_name.to_string()) {
                    let standalone_new_id_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), e.params.get(0).unwrap(), Vec::new());
                    let mut standalone_new_args = Vec::new();
                    standalone_new_args.push(standalone_new_id_e);
                    standalone_new_args.push(receiver_expr);
                    standalone_new_args.extend(e.params[1..].to_vec());
                    // Issue #132: Preserve does_throw flag from original FCall
                    let fcall_info = if let NodeType::FCall(ref info) = e.node_type { info.clone() } else { FCallInfo { does_throw: false, is_bang: false } };
                    return Ok(Expr::new_clone(NodeType::FCall(fcall_info), e.params.get(0).unwrap(), standalone_new_args));
                }
            }
        }
    }

    // No transformation needed
    Ok(e)
}
