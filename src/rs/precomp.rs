// Precomputation phase: Transforms UFCS calls into regular function calls
// and performs compile-time constant folding for pure functions.
// This phase runs after typer, before interpreter/builder.

use crate::rs::init::{Context, get_value_type, get_func_name_in_call, SymbolInfo, ScopeType};
use std::collections::HashMap;
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, Literal,
};
use crate::rs::interpreter::eval_expr;

// ---------- Main entry point

/// Precomputation phase: Transform UFCS calls into regular function calls.
/// Takes an AST that has already passed type checking and returns a semantically
/// equivalent AST with all UFCS calls resolved.
///
/// Examples:
///   a.add(b)         -> I64.add(a, b)     (where a is I64)
///   obj.items.len()  -> Vec.len(obj.items)
///   add(1, 2).mul(3) -> I64.mul(add(1, 2), 3)
pub fn precomp_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        NodeType::Body => precomp_body(context, e),
        NodeType::FCall => precomp_fcall(context, e),
        NodeType::If => precomp_params(context, e),
        NodeType::While => precomp_params(context, e),
        NodeType::Switch => precomp_params(context, e),
        NodeType::FuncDef(func_def) => precomp_func_def(context, e, func_def.clone()),
        NodeType::Declaration(decl) => precomp_declaration(context, e, decl),
        NodeType::Assignment(_) => precomp_params(context, e),
        NodeType::Return | NodeType::Throw => precomp_params(context, e),
        NodeType::Catch => precomp_params(context, e),
        NodeType::Range => precomp_params(context, e),
        // Struct/enum definitions - need to process default values (which may contain function defs)
        NodeType::StructDef(struct_def) => precomp_struct_def(context, e, struct_def),
        NodeType::EnumDef(_) => Ok(e.clone()),
        // Identifiers can have nested params (e.g., a.b.c for field access chains)
        NodeType::Identifier(_) => precomp_params(context, e),
        // Leaf nodes - no transformation needed
        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => Ok(e.clone()),
    }
}

// ---------- Compile-time constant folding

/// Check if an expression can be evaluated at compile time.
/// Currently only handles literals and pure function calls with literal arguments.
fn is_comptime_evaluable(context: &Context, e: &Expr) -> bool {
    match &e.node_type {
        NodeType::LLiteral(_) => true,
        NodeType::FCall => {
            let f_name = get_func_name_in_call(e);
            // Special case: these ext_funcs depend on runtime source location
            match f_name.as_str() {
                "loc" | "_file" | "_line" | "_col" | "exit" => return false,
                _ => {}
            }
            let func_def = match context.scope_stack.lookup_func(&f_name) {
                Some(f) => f,
                None => return false, // Unknown function (struct constructor, etc.)
            };
            // Must be pure function (not proc)
            if func_def.is_proc() {
                return false;
            }
            // Functions that can throw cannot be evaluated at compile time
            if !func_def.throw_types.is_empty() {
                return false;
            }
            // All arguments must be comptime-evaluable
            for i in 1..e.params.len() {
                if !is_comptime_evaluable(context, &e.params[i]) {
                    return false;
                }
            }
            true
        },
        // Future: handle constant identifiers (true, false, user constants)
        _ => false,
    }
}

/// Evaluate a comptime-evaluable expression and convert result back to AST literal.
fn eval_comptime(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let result = eval_expr(context, e)?;
    // EvalResult.value is a String representation of the value
    // Convert back to LLiteral based on the result type
    let value_type = get_value_type(context, e)?;
    match &value_type {
        ValueType::TCustom(ref t) if t == "I64" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Number(result.value.clone())), e, vec![]))
        },
        ValueType::TCustom(ref t) if t == "Str" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Str(result.value.clone())), e, vec![]))
        },
        // For other types, don't fold - return error to fall back
        _ => Err(format!("Cannot convert comptime result type: {:?}", value_type)),
    }
}

// ---------- AST transformation

/// Transform Body node - recursively transform all statements
fn precomp_body(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let mut new_params = Vec::new();
    for p in &e.params {
        new_params.push(precomp_expr(context, p)?);
    }
    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform node params - recursively transform all child expressions
fn precomp_params(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    let mut new_params = Vec::new();
    for p in &e.params {
        new_params.push(precomp_expr(context, p)?);
    }
    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform StructDef - recursively transform default values (which contain function defs)
fn precomp_struct_def(context: &mut Context, e: &Expr, struct_def: &SStructDef) -> Result<Expr, String> {
    let mut new_default_values = HashMap::new();
    for (name, value_expr) in &struct_def.default_values {
        new_default_values.insert(name.clone(), precomp_expr(context, value_expr)?);
    }
    let new_struct_def = SStructDef {
        members: struct_def.members.clone(),
        default_values: new_default_values,
    };
    Ok(Expr::new_clone(NodeType::StructDef(new_struct_def), e, e.params.clone()))
}

/// Transform FuncDef - push scope frame for function args, transform body, pop frame
fn precomp_func_def(context: &mut Context, e: &Expr, func_def: SFuncDef) -> Result<Expr, String> {
    // Push a new scope frame with the function's parameters
    context.scope_stack.push(ScopeType::Function);
    for arg in &func_def.args {
        context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
            value_type: arg.value_type.clone(),
            is_mut: arg.is_mut,
            is_copy: arg.is_copy,
            is_own: arg.is_own,
        });
    }

    // Transform the function body
    let mut new_body = Vec::new();
    for stmt in &func_def.body {
        new_body.push(precomp_expr(context, stmt)?);
    }

    // Pop the function scope frame
    let _ = context.scope_stack.pop();

    let new_func_def = SFuncDef {
        function_type: func_def.function_type.clone(),
        args: func_def.args.clone(),
        return_types: func_def.return_types.clone(),
        throw_types: func_def.throw_types.clone(),
        body: new_body,
        source_path: func_def.source_path.clone(),
    };
    Ok(Expr::new_clone(NodeType::FuncDef(new_func_def), e, e.params.clone()))
}

/// Transform Declaration - register the declared variable in scope, then transform value
fn precomp_declaration(context: &mut Context, e: &Expr, decl: &crate::rs::parser::Declaration) -> Result<Expr, String> {
    // First transform the value expression (if any)
    let new_params = if !e.params.is_empty() {
        let mut new_params = Vec::new();
        for p in &e.params {
            new_params.push(precomp_expr(context, p)?);
        }
        new_params
    } else {
        Vec::new()
    };

    // Determine the type from the value if it's 'auto'
    let value_type = if decl.value_type == ValueType::TCustom("auto".to_string()) && !new_params.is_empty() {
        get_value_type(context, &new_params[0]).unwrap_or(decl.value_type.clone())
    } else {
        decl.value_type.clone()
    };

    // Register the declared variable in scope
    context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
        value_type,
        is_mut: decl.is_mut,
        is_copy: decl.is_copy,
        is_own: decl.is_own,
    });

    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform FCall node - this is where UFCS resolution happens
fn precomp_fcall(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // First, recursively transform all arguments
    let mut transformed_params = Vec::new();
    for p in &e.params {
        transformed_params.push(precomp_expr(context, p)?);
    }
    let e = Expr::new_clone(e.node_type.clone(), e, transformed_params);

    // Now check if this is a UFCS call and transform it
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Ok(e), // Empty FCall, shouldn't happen but just return as-is
    };

    if let NodeType::Identifier(_id_name) = &func_expr.node_type {
        let combined_name = crate::rs::parser::get_combined_name(&context.path, func_expr)?;

        // Case 1: UFCS call on a function/expression result
        // e.g., add(1, 2).mul(3) where first arg is the result to call method on
        if e.params.len() >= 2 {
            let first_arg = e.get(1)?;
            if let Ok(target_type) = get_value_type(context, first_arg) {
                if let ValueType::TCustom(custom_type_name) = target_type {
                    let method_name = format!("{}.{}", custom_type_name, combined_name);
                    if context.scope_stack.lookup_func(&method_name).is_some() {
                        // Transform: method(target, args...) -> Type.method(target, args...)
                        let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), e.get(0)?, Vec::new());
                        let mut new_args = Vec::new();
                        new_args.push(new_e);
                        new_args.extend(e.params[1..].to_vec());
                        return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, new_args));
                    }
                }
            }
        }

        // Case 2: Already a regular function call - check if it exists
        if context.scope_stack.lookup_func(&combined_name).is_some() {
            // Try compile-time constant folding for pure functions with literal args
            if is_comptime_evaluable(context, &e) {
                if let Ok(folded) = eval_comptime(context, &e) {
                    return Ok(folded);
                }
                // If folding fails, fall through to return original expression
            }
            return Ok(e);
        }

        // Case 3: Struct/enum constructor - no transformation needed
        if context.scope_stack.lookup_struct(&combined_name).is_some() {
            return Ok(e);
        }

        // Check for enum constructors (e.g., Color.Green(true))
        let parts: Vec<&str> = combined_name.split('.').collect();
        if parts.len() == 2 {
            let enum_type = parts[0];
            if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type) {
                let variant_name = parts[1];
                if enum_def.enum_map.contains_key(variant_name) {
                    return Ok(e);
                }
            }
        }

        // Case 4: UFCS with dot notation (e.g., a.method(b) or a.field.method())
        if let Some(func_name_expr) = func_expr.params.last() {
            if let NodeType::Identifier(ufcs_func_name) = &func_name_expr.node_type {
                let mut parts: Vec<&str> = combined_name.split('.').collect();
                parts.pop(); // Remove the method name
                let _new_combined_name = parts.join(".");

                // Create identifier expression for the receiver (everything except the method name)
                let mut id_params = func_expr.params.clone();
                id_params.pop(); // Remove the method name
                let receiver_expr = Expr::new_clone(func_expr.node_type.clone(), &e, id_params);

                // Try as a regular standalone function first
                if context.scope_stack.lookup_func(&ufcs_func_name.to_string()).is_some() {
                    let new_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), e.get(0)?, Vec::new());
                    let mut new_args = Vec::new();
                    new_args.push(new_e);
                    new_args.push(receiver_expr);
                    new_args.extend(e.params[1..].to_vec());
                    return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, new_args));
                }

                // Try as an associated method (Type.method)
                match get_value_type(context, &receiver_expr) {
                    Ok(value_type) => {
                        // Get type name from value_type - TCustom or TMulti (variadic params become Array)
                        let custom_type_name = match &value_type {
                            ValueType::TCustom(name) => Some(name.clone()),
                            ValueType::TMulti(_) => Some("Array".to_string()),
                            _ => None,
                        };
                        if let Some(ref type_name) = custom_type_name {
                            let method_name = format!("{}.{}", type_name, ufcs_func_name);
                            if context.scope_stack.lookup_func(&method_name).is_some() {
                                let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), e.get(0)?, Vec::new());
                                let mut new_args = Vec::new();
                                new_args.push(new_e);
                                new_args.push(receiver_expr);
                                new_args.extend(e.params[1..].to_vec());
                                return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, new_args));
                            }
                        }
                    }
                    Err(_err) => {
                        // Type could not be determined - leave unchanged
                    }
                }
            }
        }
    }

    // No transformation needed
    Ok(e)
}
