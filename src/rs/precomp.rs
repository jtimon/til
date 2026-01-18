// Precomputation phase: Transforms UFCS calls into regular function calls
// and performs compile-time constant folding for pure functions.
// This phase runs after typer, before interpreter/builder.

use crate::rs::init::{Context, get_value_type, get_func_name_in_call, SymbolInfo, ScopeType};
use crate::rs::typer::{func_proc_has_multi_arg, get_func_def_for_fcall_with_expr};
use std::collections::HashMap;
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, Literal, TTypeDef, PatternInfo,
    Declaration, str_to_value_type, value_type_to_str, INFER_TYPE,
};
use crate::rs::interpreter::{eval_expr, eval_declaration, insert_struct_instance, create_default_instance};
use crate::rs::eval_arena::EvalArena;
use crate::rs::precomp_ext::try_replace_comptime_intrinsic;

/// Build the full dotted name from an identifier chain expression.
/// For example, for an Identifier("ValueType") with params [Identifier("TType")],
/// this returns "ValueType.TType".
fn build_identifier_chain_name(expr: &Expr) -> String {
    match &expr.node_type {
        NodeType::Identifier(name) => {
            if expr.params.is_empty() {
                name.clone()
            } else {
                // Build full name from nested identifiers
                let mut full_name = name.clone();
                for p in &expr.params {
                    if let NodeType::Identifier(sub) = &p.node_type {
                        full_name.push('.');
                        full_name.push_str(sub);
                        // Recursively add any deeper nested names
                        for pp in &p.params {
                            if let NodeType::Identifier(subsub) = &pp.node_type {
                                full_name.push('.');
                                full_name.push_str(subsub);
                            }
                        }
                    }
                }
                full_name
            }
        }
        _ => String::new()
    }
}

/// Rename all occurrences of an identifier in an expression tree.
/// Used by switch desugaring to rename binding variables to mangled names.
/// IMPORTANT: Don't rename field access params - those are field names, not variables.
fn rename_identifier(expr: &Expr, old_name: &str, new_name: &str) -> Expr {
    match &expr.node_type {
        NodeType::Identifier(name) if name == old_name => {
            // Replace this identifier with the new name
            // DON'T recurse into params - those are field accesses (e.g., var.field.subfield)
            // and field names should NOT be renamed
            Expr::new_explicit(
                NodeType::Identifier(new_name.to_string()),
                expr.params.clone(), // Keep field names as-is
                expr.line,
                expr.col,
            )
        }
        NodeType::Identifier(_) => {
            // Different identifier - don't rename, but DO recurse into params
            // because params might contain field access chains that start with our variable
            // e.g., for "other_var.something.binding_var", we need to check deeper
            // Actually, params in identifiers are field names, not expressions
            // So we should NOT recurse here either
            expr.clone()
        }
        NodeType::Declaration(decl) if decl.name == old_name => {
            // Don't rename declaration names - those create new bindings that shadow
            // Just recurse into params (the initializer expression)
            Expr {
                node_type: expr.node_type.clone(),
                params: expr.params.iter().map(|p| rename_identifier(p, old_name, new_name)).collect(),
                line: expr.line,
                col: expr.col,
            }
        }
        NodeType::Assignment(name) if name == old_name => {
            // Rename assignment target
            Expr::new_explicit(
                NodeType::Assignment(new_name.to_string()),
                expr.params.iter().map(|p| rename_identifier(p, old_name, new_name)).collect(),
                expr.line,
                expr.col,
            )
        }
        _ => {
            // Recurse into all params
            Expr {
                node_type: expr.node_type.clone(),
                params: expr.params.iter().map(|p| rename_identifier(p, old_name, new_name)).collect(),
                line: expr.line,
                col: expr.col,
            }
        }
    }
}

// Bug #57 fix: Transform continue statements to include the step expression before continue.
// This ensures the loop variable is incremented even when continue is used in for-in loops.
fn transform_continue_with_step(expr: &Expr, step_expr: &Expr) -> Expr {
    match &expr.node_type {
        NodeType::Continue => {
            // Replace continue with { step_expr; continue }
            Expr::new_explicit(
                NodeType::Body,
                vec![step_expr.clone(), expr.clone()],
                expr.line,
                expr.col,
            )
        }
        // Don't recurse into nested loops - their continues are for their own loop
        NodeType::While | NodeType::ForIn(_) => expr.clone(),
        // Recurse into other nodes
        _ => {
            let new_params: Vec<Expr> = expr.params.iter()
                .map(|p| transform_continue_with_step(p, step_expr))
                .collect();
            Expr {
                node_type: expr.node_type.clone(),
                params: new_params,
                line: expr.line,
                col: expr.col,
            }
        }
    }
}

// ---------- Named argument reordering

/// Reorder named arguments to match function parameter order.
/// Transforms: func(b=3, a=10) -> func(10, 3) (for func(a, b))
/// This runs during precomp so both interpreter and builder share the work.
fn reorder_named_args(context: &Context, e: &Expr, func_def: &SFuncDef) -> Result<Expr, String> {
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
        return Err(e.error(&context.path, "precomp", "Named arguments are not supported for variadic functions"));
    }

    // Bug #61: Check if there are optional args before variadic that might need defaults
    // This happens when the provided arg type doesn't match the optional arg type
    let has_optional_before_variadic = is_variadic && func_def.args.len() > 1 &&
        func_def.args.iter().take(func_def.args.len() - 1).any(|a| a.default_value.is_some());

    // Check if we need to fill in default values (fewer args than params)
    // Don't apply to variadic functions (unless they have optional args before the variadic)
    let needs_defaults = (!is_variadic && call_args.len() < func_def.args.len()) || has_optional_before_variadic;

    // If no named args and no defaults needed, return unchanged
    if !has_named_args && !needs_defaults {
        return Ok(e.clone());
    }

    let mut result = vec![e.params[0].clone()]; // Keep function identifier

    // Bug #61: Handle variadic functions with optional args before the variadic
    // Need to insert defaults for skipped optional args, then include all provided args
    if has_optional_before_variadic {
        let mut def_arg_idx: usize = 0;
        let mut call_arg_idx: usize = 0;

        // Process optional args before the variadic
        while def_arg_idx < func_def.args.len() - 1 {  // -1 to stop before variadic
            let opt_def_arg = &func_def.args[def_arg_idx];

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
                return Err(e.error(&context.path, "precomp", &format!("Missing argument for non-optional parameter '{}'", opt_def_arg.name)));
            }
            def_arg_idx += 1;
        }

        // Add remaining provided args (for variadic)
        for i in call_arg_idx..call_args.len() {
            result.push(call_args[i].clone());
        }

        return Ok(Expr::new_clone(NodeType::FCall, e, result));
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
            return Err(e.error(&context.path, "precomp", "Positional arguments cannot appear after named arguments"));
        }
    }

    // Build result: first positional args, then fill in from named args
    let mut final_args: Vec<Option<Expr>> = vec![None; func_def.args.len()];

    // Place positional arguments
    for (i, arg) in call_args.iter().take(positional_count).enumerate() {
        if i >= func_def.args.len() {
            return Err(e.error(&context.path, "precomp", &format!("Too many positional arguments: expected at most {}", func_def.args.len())));
        }
        final_args[i] = Some(arg.clone());
    }

    // Place named arguments
    for arg in call_args.iter().skip(positional_count) {
        if let NodeType::NamedArg(arg_name) = &arg.node_type {
            // Find the parameter index by name
            let mut param_idx: Option<usize> = None;
            for (i, p) in func_def.args.iter().enumerate() {
                if &p.name == arg_name {
                    param_idx = Some(i);
                    break;
                }
            }
            match param_idx {
                Some(idx) => {
                    if final_args[idx].is_some() {
                        return Err(arg.error(&context.path, "precomp", &format!("Argument '{}' specified multiple times", arg_name)));
                    }
                    // Extract the value from the NamedArg
                    if arg.params.is_empty() {
                        return Err(arg.error(&context.path, "precomp", &format!("Named argument '{}' has no value", arg_name)));
                    }
                    final_args[idx] = Some(arg.params[0].clone());
                },
                None => {
                    return Err(arg.error(&context.path, "precomp", &format!("Unknown parameter name '{}'", arg_name)));
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
                if let Some(default_expr) = &func_def.args[i].default_value {
                    result.push((**default_expr).clone());
                } else {
                    return Err(e.error(&context.path, "precomp", &format!("Missing argument for parameter '{}'", func_def.args[i].name)));
                }
            }
        }
    }

    Ok(Expr::new_clone(NodeType::FCall, e, result))
}

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
        NodeType::FCall => {
            let mut const_folded = precomp_fcall(context, e)?;
            // Try compile-time constant folding for pure functions with literal args.
            // Only fold at global scope - inside function definitions, values from other
            // modules may not be available yet (import ordering). Interpreter doesn't
            // evaluate function bodies during import either.
            let at_global_scope = context.scope_stack.frames.len() == 1;
            if at_global_scope && is_comptime_evaluable(context, &const_folded) {
                const_folded = eval_comptime(context, &const_folded)?;
            }
            return Ok(const_folded);
        },
        NodeType::If => precomp_params(context, e),
        NodeType::While => precomp_params(context, e),
        NodeType::Switch => precomp_switch(context, e),
        NodeType::FuncDef(func_def) => precomp_func_def(context, e, func_def.clone()),
        NodeType::Declaration(decl) => precomp_declaration(context, e, decl),
        NodeType::Assignment(_) => precomp_params(context, e),
        NodeType::Return | NodeType::Throw => precomp_params(context, e),
        NodeType::Catch => precomp_catch(context, e),
        NodeType::Range => precomp_params(context, e),
        // Struct/enum definitions - need to process default values (which may contain function defs)
        NodeType::StructDef(struct_def) => precomp_struct_def(context, e, struct_def),
        NodeType::EnumDef(_) => Ok(e.clone()),
        // Identifiers can have nested params (e.g., a.b.c for field access chains)
        NodeType::Identifier(_) => precomp_params(context, e),
        // Leaf nodes - no transformation needed
        NodeType::LLiteral(_) | NodeType::DefaultCase | NodeType::Pattern(_) => Ok(e.clone()),
        // Break and Continue are leaf nodes (no params) - no transformation needed
        NodeType::Break | NodeType::Continue => Ok(e.clone()),
        // Named arguments - transform the value expression
        NodeType::NamedArg(name) => {
            let mut new_params = Vec::new();
            for p in &e.params {
                new_params.push(precomp_expr(context, p)?);
            }
            Ok(Expr::new_clone(NodeType::NamedArg(name.clone()), e, new_params))
        },
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        // After desugaring, recursively precomp the result to resolve UFCS and loc()
        NodeType::ForIn(var_type_name) => {
            let desugared = precomp_forin(context, e, var_type_name)?;
            precomp_expr(context, &desugared)
        },
    }
}

// ---------- Compile-time constant folding

/// Check if an expression can be evaluated at compile time.
/// Currently only handles literals and pure function calls with literal arguments.
fn is_comptime_evaluable(context: &Context, e: &Expr) -> bool {
    match &e.node_type {
        NodeType::LLiteral(_) => true,
        // Type definitions and function definitions are static metadata - always comptime
        NodeType::StructDef(_) => true,
        NodeType::EnumDef(_) => true,
        NodeType::FuncDef(_) => true,
        NodeType::Identifier(name) => {
            // Check if this is a simple identifier (no field access chain)
            if !e.params.is_empty() {
                return false;  // Field access chains not supported
            }
            // Look up the symbol and check if it's a comptime const
            if let Some(symbol) = context.scope_stack.lookup_symbol(name) {
                return symbol.is_comptime_const;
            }
            false
        }
        NodeType::FCall => {
            let f_name = get_func_name_in_call(e);
            // Special case: exit terminates the program
            if f_name == "exit" {
                return false;
            }
            // TODO: Properly detect ext_funcs and functions with side effects.
            // For now, hardcode malloc exclusion since it's an ext_func with side effects.
            if f_name == "malloc" {
                return false;
            }
            // Use get_func_def_for_fcall_with_expr like interpreter does
            let mut e_clone = e.clone();
            let func_def = match get_func_def_for_fcall_with_expr(context, &mut e_clone) {
                Ok(Some(f)) => f,
                Ok(None) => {
                    // Could be a struct constructor - check if all args are comptime
                    let combined_name = crate::rs::parser::get_combined_name(&context.path, e.params.first().unwrap()).unwrap_or_default();
                    if context.scope_stack.lookup_struct(&combined_name).is_some() {
                        // It's a struct constructor - check all args are comptime
                        for i in 1..e.params.len() {
                            // Handle named args - check the value inside
                            let arg = &e.params[i];
                            let arg_to_check = if let NodeType::NamedArg(_) = &arg.node_type {
                                arg.params.first().unwrap_or(arg)
                            } else {
                                arg
                            };
                            if !is_comptime_evaluable(context, arg_to_check) {
                                return false;
                            }
                        }
                        return true; // Struct constructor with all comptime args
                    }
                    // Check if it's an enum constructor (e.g., Color.Green(true))
                    if context.scope_stack.is_enum_constructor(&combined_name) {
                        // It's an enum constructor - check all args are comptime
                        for i in 1..e.params.len() {
                            if !is_comptime_evaluable(context, &e.params[i]) {
                                return false;
                            }
                        }
                        return true;
                    }
                    return false;
                },
                Err(_) => {
                    return false; // Unknown function
                }
            };
            // Must be pure function (not proc) that returns a value
            if func_def.is_proc() {
                return false;
            }
            // Funcs with no return type can't be folded (nothing to fold to)
            if func_def.return_types.is_empty() {
                return false;
            }
            // Functions that can throw are allowed - if they actually throw,
            // we'll report the error in eval_comptime.
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
    // Save and restore context.path - interpreter may change it during function calls
    let saved_path = context.path.clone();
    let result = eval_expr(context, e);
    context.path = saved_path;
    let result = result?;

    // Check if the function threw an exception during evaluation
    if result.is_throw {
        let thrown_type = if result.thrown_type.is_empty() { "unknown" } else { &result.thrown_type };
        return Err(e.error(&context.path, "precomp",
            &format!("Exception '{}' thrown during precomputation: {}", thrown_type, result.value)));
    }

    // EvalResult.value is a String representation of the value
    // Convert back to LLiteral based on the result type
    let value_type = get_value_type(context, e)?;
    match &value_type {
        ValueType::TCustom(ref t) if t == "I64" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Number(result.value.clone())), e, vec![]))
        },
        ValueType::TCustom(ref t) if t == "U8" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Number(result.value.clone())), e, vec![]))
        },
        ValueType::TCustom(ref t) if t == "Str" => {
            Ok(Expr::new_clone(NodeType::LLiteral(Literal::Str(result.value.clone())), e, vec![]))
        },
        ValueType::TCustom(ref type_name) => {
            // Check if it's a struct type - result.value is the instance name
            if context.scope_stack.lookup_struct(type_name).is_some() {
                // Try to convert struct back to literal, fall back to original expr if unsupported
                return EvalArena::to_struct_literal(context, &result.value, type_name, e)
                    .or_else(|_| Ok(e.clone()));
            }
            // For enums and other types: eval_expr was called (catching any errors),
            // but we can't convert the result back to AST literal, so return original
            Ok(e.clone())
        },
        // For other types, eval was done (errors caught), return original (no folding)
        _ => Ok(e.clone()),
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

/// Build a default value expression for a given ValueType.
/// Used when generating placeholder values for enum variant payloads in for-in loops.
/// Bug #33: for-in loops don't work with enum collections
/// Bug #86: Handle enum payload types recursively
fn build_default_value(context: &Context, vt: &ValueType, line: usize, col: usize) -> Expr {
    match vt {
        ValueType::TCustom(type_name) => {
            match type_name.as_str() {
                "I64" => Expr::new_explicit(
                    NodeType::LLiteral(Literal::Number("0".to_string())),
                    vec![],
                    line,
                    col,
                ),
                "U8" => Expr::new_explicit(
                    NodeType::LLiteral(Literal::Number("0".to_string())),
                    vec![],
                    line,
                    col,
                ),
                "Bool" => Expr::new_explicit(
                    NodeType::Identifier("false".to_string()),
                    vec![],
                    line,
                    col,
                ),
                "Str" => Expr::new_explicit(
                    NodeType::LLiteral(Literal::Str(String::new())),
                    vec![],
                    line,
                    col,
                ),
                // For other types (structs, other enums), check if it's an enum
                _ => {
                    // Bug #86: Check if this type is an enum - enums need special constructor syntax
                    if let Some(enum_def) = context.scope_stack.lookup_enum(type_name) {
                        // Build proper enum constructor: EnumType.FirstVariant or EnumType.FirstVariant(payload)
                        if let Some(first_v) = enum_def.variants.first() {
                            let first_variant = &first_v.name;
                            let payload_type = &first_v.payload_type;
                            let variant_id = Expr::new_explicit(
                                NodeType::Identifier(first_variant.clone()),
                                vec![],
                                line,
                                col,
                            );
                            let enum_id = Expr::new_explicit(
                                NodeType::Identifier(type_name.clone()),
                                vec![variant_id],
                                line,
                                col,
                            );
                            if let Some(payload_vt) = payload_type {
                                // Variant has a payload - need FCall with default value (recursive)
                                let default_arg = build_default_value(context, payload_vt, line, col);
                                let enum_payload_fcall_params = vec![enum_id, default_arg];
                                Expr::new_explicit(
                                    NodeType::FCall,
                                    enum_payload_fcall_params,
                                    line,
                                    col,
                                )
                            } else {
                                // Variant has no payload - just the identifier chain
                                enum_id
                            }
                        } else {
                            // Empty enum - fall back to struct-like constructor (shouldn't happen)
                            let empty_enum_fcall_params = vec![Expr::new_explicit(NodeType::Identifier(type_name.clone()), vec![], line, col)];
                            Expr::new_explicit(
                                NodeType::FCall,
                                empty_enum_fcall_params,
                                line,
                                col,
                            )
                        }
                    } else {
                        // Not an enum - use struct-like constructor: TYPE()
                        let struct_fcall_params = vec![Expr::new_explicit(NodeType::Identifier(type_name.clone()), vec![], line, col)];
                        Expr::new_explicit(
                            NodeType::FCall,
                            struct_fcall_params,
                            line,
                            col,
                        )
                    }
                }
            }
        }
        // For function types and other types, use a placeholder (shouldn't typically happen)
        _ => Expr::new_explicit(
            NodeType::LLiteral(Literal::Number("0".to_string())),
            vec![],
            line,
            col,
        ),
    }
}

/// Desugar ForIn to a range-based for loop with get() calls
/// for VAR: TYPE in COLLECTION { body }
/// becomes:
/// for _for_i in 0..collection.len() {
///     mut VAR := TYPE()
///     collection.get(_for_i, VAR)
///     catch (err: IndexOutOfBoundsError) { panic(loc(), err.msg) }
///     body
/// }
fn precomp_forin(context: &mut Context, e: &Expr, var_type_name: &str) -> Result<Expr, String> {
    // Extract var_name from params[0]
    let var_name = match e.params.get(0) {
        Some(var_expr) => match &var_expr.node_type {
            NodeType::Identifier(name) => name.clone(),
            _ => return Err(e.lang_error(&context.path, "precomp", "ForIn: expected identifier for loop variable")),
        },
        None => return Err(e.lang_error(&context.path, "precomp", "ForIn: missing loop variable")),
    };

    // Get collection expression (params[1])
    let collection_expr = match e.params.get(1) {
        Some(expr) => precomp_expr(context, expr)?,
        None => return Err(e.lang_error(&context.path, "precomp", "ForIn: missing collection expression")),
    };

    // Declare loop variable in scope BEFORE processing body (body references it)
    context.scope_stack.declare_symbol(var_name.clone(), SymbolInfo {
        value_type: ValueType::TCustom(var_type_name.to_string()),
        is_mut: true,
        is_copy: false,
        is_own: false,
        is_comptime_const: false,
    });

    // Get body (params[2])
    let body_expr = match e.params.get(2) {
        Some(expr) => precomp_expr(context, expr)?,
        None => return Err(e.lang_error(&context.path, "precomp", "ForIn: missing body")),
    };

    // Build: mut _for_i_funcname_N := 0 (unique name to avoid conflicts with nested loops)
    // Bug #40 fix: Use per-function counter and include function name for deterministic output
    let forin_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = &context.current_precomp_func;
    let index_var_name = if !func_name.is_empty() {
        format!("_for_i_{}_{}", func_name, forin_id)
    } else {
        format!("_for_i_{}", forin_id)
    };
    let index_decl = Declaration {
        name: index_var_name.clone(),
        value_type: str_to_value_type(INFER_TYPE),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    let zero_literal = Expr::new_explicit(NodeType::LLiteral(Literal::Number("0".to_string())), vec![], e.line, e.col);
    let index_decl_expr = Expr::new_explicit(NodeType::Declaration(index_decl), vec![zero_literal], e.line, e.col);

    // Build len(collection) - already desugared form
    let len_call_expr = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_explicit(NodeType::Identifier("len".to_string()), vec![], e.line, e.col),
            collection_expr.clone(),
        ],
        e.line,
        e.col,
    );

    // Build lt(_for_i, len_result) - already desugared form
    let cond_expr = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_explicit(NodeType::Identifier("lt".to_string()), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::Identifier(index_var_name.clone()), vec![], e.line, e.col),
            len_call_expr,
        ],
        e.line,
        e.col,
    );

    // Build: mut VAR := TYPE() or EnumType.FirstVariant(...) for enums
    let var_decl = Declaration {
        name: var_name.clone(),
        value_type: ValueType::TCustom(var_type_name.to_string()),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };

    // Check if this is an enum type - enums need special handling since they don't have
    // a parameterless constructor. We need to use the first variant as a placeholder.
    // Bug #33: for-in loops don't work with enum collections
    let type_call = if let Some(enum_def) = context.scope_stack.lookup_enum(var_type_name) {
        // Get the first variant from the enum (arbitrary choice - value will be overwritten by get())
        if let Some(first_v) = enum_def.variants.first() {
            let first_variant = &first_v.name;
            let payload_type = &first_v.payload_type;
            // Build the enum constructor:
            // - For variants WITHOUT payload: EnumType.Variant (just identifier chain)
            // - For variants WITH payload: EnumType.Variant(default_payload) (FCall)
            let variant_id = Expr::new_explicit(
                NodeType::Identifier(first_variant.clone()),
                vec![],
                e.line,
                e.col,
            );
            let enum_id = Expr::new_explicit(
                NodeType::Identifier(var_type_name.to_string()),
                vec![variant_id],
                e.line,
                e.col,
            );

            if let Some(payload_vt) = payload_type {
                // Variant has a payload - need FCall with default value
                let default_arg = build_default_value(context, payload_vt, e.line, e.col);
                Expr::new_explicit(
                    NodeType::FCall,
                    vec![enum_id, default_arg],
                    e.line,
                    e.col,
                )
            } else {
                // Variant has no payload - just the identifier chain (NOT an FCall)
                enum_id
            }
        } else {
            // Empty enum - shouldn't happen, fall back to struct-like constructor
            Expr::new_explicit(
                NodeType::FCall,
                vec![Expr::new_explicit(NodeType::Identifier(var_type_name.to_string()), vec![], e.line, e.col)],
                e.line,
                e.col,
            )
        }
    } else {
        // Not an enum - use struct-like constructor: TYPE()
        Expr::new_explicit(
            NodeType::FCall,
            vec![Expr::new_explicit(NodeType::Identifier(var_type_name.to_string()), vec![], e.line, e.col)],
            e.line,
            e.col,
        )
    };
    let var_decl_expr = Expr::new_explicit(NodeType::Declaration(var_decl), vec![type_call], e.line, e.col);

    // Build: get(collection, _for_i, VAR) - already desugared form
    let get_call = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_explicit(NodeType::Identifier("get".to_string()), vec![], e.line, e.col),
            collection_expr.clone(),
            Expr::new_explicit(NodeType::Identifier(index_var_name.clone()), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::Identifier(var_name.clone()), vec![], e.line, e.col),
        ],
        e.line,
        e.col,
    );

    // Build: catch (err: IndexOutOfBoundsError) { panic(loc(), err.msg) }
    // Catch structure: params[0]=error type identifier, params[1]=error var name, params[2]=body
    let panic_call = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_explicit(NodeType::Identifier("panic".to_string()), vec![], e.line, e.col),
            Expr::new_explicit(
                NodeType::FCall,
                vec![Expr::new_explicit(NodeType::Identifier("loc".to_string()), vec![], e.line, e.col)],
                e.line,
                e.col,
            ),
            Expr::new_explicit(
                NodeType::Identifier("err".to_string()),
                vec![Expr::new_explicit(NodeType::Identifier("msg".to_string()), vec![], e.line, e.col)],
                e.line,
                e.col,
            ),
        ],
        e.line,
        e.col,
    );
    let catch_body = Expr::new_explicit(NodeType::Body, vec![panic_call], e.line, e.col);
    // Catch structure: [name_expr, type_expr, body_expr]
    let catch_expr = Expr::new_explicit(
        NodeType::Catch,
        vec![
            Expr::new_explicit(NodeType::Identifier("err".to_string()), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::Identifier("IndexOutOfBoundsError".to_string()), vec![], e.line, e.col),
            catch_body,
        ],
        e.line,
        e.col,
    );

    // Build: _for_i = add(_for_i, 1)
    // Already desugared form - no UFCS resolution needed
    let add_call = Expr::new_explicit(
        NodeType::FCall,
        vec![
            Expr::new_explicit(NodeType::Identifier("add".to_string()), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::Identifier(index_var_name.clone()), vec![], e.line, e.col),
            Expr::new_explicit(NodeType::LLiteral(Literal::Number("1".to_string())), vec![], e.line, e.col),
        ],
        e.line,
        e.col,
    );
    let inc_stmt = Expr::new_explicit(
        NodeType::Assignment(index_var_name.clone()),
        vec![add_call],
        e.line,
        e.col,
    );

    // Build while body: var_decl, get_call + catch (together), original body statements, inc
    // The catch must be right after get_call so it only catches IndexOutOfBoundsError from get,
    // not from user code in the loop body
    let mut while_body_params = vec![var_decl_expr, get_call, catch_expr];
    // Bug #57 fix: Transform continue statements to include increment before continue
    let transformed_body = transform_continue_with_step(&body_expr, &inc_stmt);
    // Add original body statements (transformed)
    match &transformed_body.node_type {
        NodeType::Body => {
            while_body_params.extend(transformed_body.params.clone());
        },
        _ => {
            while_body_params.push(transformed_body);
        }
    }
    while_body_params.push(inc_stmt.clone());
    let while_body = Expr::new_explicit(NodeType::Body, while_body_params, e.line, e.col);

    // Build while: while _for_i.lt(collection.len()) { ... }
    let while_expr = Expr::new_explicit(NodeType::While, vec![cond_expr, while_body], e.line, e.col);

    // Build outer body: index_decl, while
    Ok(Expr::new_explicit(NodeType::Body, vec![index_decl_expr, while_expr], e.line, e.col))
}

/// Desugar Switch to if/else chain (Issue #110)
/// Before precomp:
///   switch my_enum {
///       case Foo(x) { use(x) }
///       case Bar(y) { use(y) }
///       default { fallback() }
///   }
///
/// After precomp:
///   if enum_to_str(my_enum).eq("MyEnum.Foo") {
///       mut x: PayloadType = default
///       enum_get_payload(my_enum, "Foo", x)
///       use(x)
///   } else if enum_to_str(my_enum).eq("MyEnum.Bar") {
///       mut y: PayloadType = default
///       enum_get_payload(my_enum, "Bar", y)
///       use(y)
///   } else {
///       fallback()
///   }
fn precomp_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Switch structure: params[0] is switch expression, then pairs of (case, body)
    if e.params.is_empty() {
        return Ok(e.clone());
    }

    let switch_expr = &e.params[0];
    let switch_expr_type = get_value_type(context, switch_expr).ok();
    let line = e.line;
    let col = e.col;

    // Collect all case/body pairs
    let mut cases: Vec<(&Expr, &Expr)> = Vec::new();
    let mut default_body: Option<&Expr> = None;

    let mut i = 1;
    while i < e.params.len() {
        let case_expr = &e.params[i];
        if matches!(case_expr.node_type, NodeType::DefaultCase) {
            // Default case - next param is the body
            if i + 1 < e.params.len() {
                default_body = Some(&e.params[i + 1]);
            }
            i += 2;
        } else if i + 1 < e.params.len() {
            // Regular case - case/body pair
            cases.push((case_expr, &e.params[i + 1]));
            i += 2;
        } else {
            break;
        }
    }

    // Build if/else chain from bottom up (starting with default/else, then wrapping with if/else if)
    let mut current_else: Option<Expr> = default_body.map(|body| precomp_expr(context, body)).transpose()?;

    for (case_expr, body_expr) in cases.into_iter().rev() {
        let (condition, body_prefix, rename_mapping) = build_case_condition(
            context, switch_expr, case_expr, &switch_expr_type, line, col
        )?;

        // Build the body with optional prefix (for payload extraction)
        let body = build_case_body(context, body_expr, body_prefix, rename_mapping)?;

        // Build if expression
        let mut if_params = vec![condition, body];
        if let Some(else_expr) = current_else.take() {
            if_params.push(else_expr);
        }
        current_else = Some(Expr::new_explicit(NodeType::If, if_params, line, col));
    }

    // If there were no cases, return the default body or empty body
    match current_else {
        Some(if_chain) => {
            // Recursively precomp the generated if/else chain
            precomp_expr(context, &if_chain)
        }
        None => Ok(Expr::new_explicit(NodeType::Body, vec![], line, col)),
    }
}

/// Build the condition expression and optional body prefix for a switch case
/// Returns: (condition, body_prefix, optional rename mapping (old_name, new_name))
fn build_case_condition(
    context: &mut Context,
    switch_expr: &Expr,
    case_expr: &Expr,
    switch_expr_type: &Option<ValueType>,
    line: usize,
    col: usize,
) -> Result<(Expr, Vec<Expr>, Option<(String, String)>), String> {
    match &case_expr.node_type {
        NodeType::Pattern(PatternInfo { variant_name, binding_var }) => {
            // Enum pattern with payload binding
            // Condition: enum_to_str(switch_expr).eq("EnumType.Variant")
            let (enum_type_name, variant_short) = if let Some(dot_pos) = variant_name.rfind('.') {
                (variant_name[..dot_pos].to_string(), variant_name[dot_pos + 1..].to_string())
            } else if let Some(ValueType::TCustom(enum_name)) = switch_expr_type {
                (enum_name.clone(), variant_name.clone())
            } else {
                return Err(case_expr.lang_error("", "precomp", "Pattern without type context"));
            };

            let full_variant = format!("{}.{}", enum_type_name, variant_short);

            // Build: enum_to_str(switch_expr)
            let enum_to_str_call = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                    switch_expr.clone(),
                ],
                line, col,
            );

            // Build: enum_to_str(switch_expr).eq("EnumType.Variant")
            // After UFCS resolution this becomes: Str.eq(enum_to_str(switch_expr), "...")
            let str_literal = Expr::new_explicit(
                NodeType::LLiteral(Literal::Str(full_variant)),
                vec![], line, col,
            );
            let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
            let condition = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier("Str".to_string()), vec![eq_id], line, col),
                    enum_to_str_call,
                    str_literal,
                ],
                line, col,
            );

            // Build body prefix for payload extraction
            let mut body_prefix = Vec::new();
            let mut rename_mapping: Option<(String, String)> = None;

            // Get payload type from enum definition
            let payload_type = context.scope_stack.lookup_enum(&enum_type_name)
                .and_then(|e| e.get(&variant_short).cloned())
                .flatten();

            // Skip payload extraction if binding_var is "_" (discard pattern)
            // Also handle nested enum patterns where binding_var is itself an enum value (contains a dot)
            if let Some(payload_type) = payload_type {
                // Check if binding_var is an enum value (contains a dot) rather than a variable name
                let is_enum_value_pattern = binding_var.contains('.');

                if is_enum_value_pattern {
                    // Nested enum pattern like TType(TTypeDef.TStructDef)
                    // The binding_var is itself an enum value, not a variable name
                    // We need to check BOTH the outer variant AND the inner payload value
                    //
                    // Strategy: Use only the outer condition, but add a nested if statement
                    // inside the body that checks the payload value. The nested if wraps
                    // the actual case body.
                    //
                    // Generated structure:
                    //   if outer_condition {
                    //       temp_var := default
                    //       enum_get_payload(switch_expr, "Variant", temp_var)
                    //       if enum_to_str(temp_var).eq("InnerEnumValue") {
                    //           // actual case body
                    //       }
                    //   }
                    //
                    // This is stored in body_prefix and the nested_body_condition.
                    // The build_case_body function will wrap the body with this nested if.

                    let temp_name = format!("_sw{}_{}payload", case_expr.line, case_expr.col);

                    // Declare temp variable for payload
                    let var_decl = Declaration {
                        name: temp_name.clone(),
                        value_type: payload_type.clone(),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        default_value: None,
                    };
                    let default_val = build_default_value(context, &payload_type, line, col);
                    let decl_expr = Expr::new_explicit(
                        NodeType::Declaration(var_decl),
                        vec![default_val],
                        line, col,
                    );
                    body_prefix.push(decl_expr);

                    // Extract payload
                    let payload_call = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                            switch_expr.clone(),
                            Expr::new_explicit(NodeType::LLiteral(Literal::Str(variant_short.clone())), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(temp_name.clone()), vec![], line, col),
                        ],
                        line, col,
                    );
                    body_prefix.push(payload_call);

                    // Build nested condition check: enum_to_str(temp_var).eq(binding_var)
                    let nested_enum_to_str = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(temp_name), vec![], line, col),
                        ],
                        line, col,
                    );
                    let nested_str_literal = Expr::new_explicit(
                        NodeType::LLiteral(Literal::Str(binding_var.clone())),
                        vec![], line, col,
                    );
                    let nested_eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
                    let nested_condition = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("Str".to_string()), vec![nested_eq_id], line, col),
                            nested_enum_to_str,
                            nested_str_literal,
                        ],
                        line, col,
                    );

                    // Store the nested condition as the last element of body_prefix
                    // It will be extracted by build_case_body and used to wrap the actual body
                    // We use NodeType::If with empty params as a marker
                    let nested_if_marker = Expr::new_explicit(
                        NodeType::If,
                        vec![nested_condition],  // Just the condition, body will be added later
                        line, col,
                    );
                    body_prefix.push(nested_if_marker);

                    // Return ONLY the outer condition - the inner check happens in the body
                    return Ok((condition, body_prefix, None));
                } else if binding_var != "_" {
                    // Generate unique mangled name to avoid conflicts with outer scope variables
                    // This is needed because TIL hoists declarations to function level
                    // Use case_expr's line/col (not switch's) to ensure each case gets unique name
                    let mangled_name = format!("_sw{}_{}{}", case_expr.line, case_expr.col, binding_var);

                    // Declare binding variable: mut binding_var: PayloadType = default
                    let var_decl = Declaration {
                        name: mangled_name.clone(),
                        value_type: payload_type.clone(),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        default_value: None,
                    };
                    let default_val = build_default_value(context, &payload_type, line, col);
                    let decl_expr = Expr::new_explicit(
                        NodeType::Declaration(var_decl),
                        vec![default_val],
                        line, col,
                    );
                    body_prefix.push(decl_expr);

                    // Call enum_get_payload(switch_expr, "Variant", mangled_name)
                    let payload_call = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                            switch_expr.clone(),
                            Expr::new_explicit(NodeType::LLiteral(Literal::Str(variant_short.clone())), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(mangled_name.clone()), vec![], line, col),
                        ],
                        line, col,
                    );
                    body_prefix.push(payload_call);

                    // Record rename mapping so body can be transformed
                    rename_mapping = Some((binding_var.clone(), mangled_name.clone()));

                    // Push a block scope and declare the mangled name for precomp processing
                    // (needed for get_value_type lookups during build_case_body)
                    // This scope will be popped in build_case_body
                    context.scope_stack.push(ScopeType::Block);
                    context.scope_stack.declare_symbol(
                        mangled_name.clone(),
                        SymbolInfo {
                            value_type: payload_type,
                            is_mut: true,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        }
                    );
                }
            }

            Ok((condition, body_prefix, rename_mapping))
        }
        NodeType::Range => {
            // Range case: val >= start && val <= end
            if case_expr.params.len() < 2 {
                return Err(case_expr.lang_error("", "precomp", "Range requires start and end"));
            }
            let start = &case_expr.params[0];
            let end = &case_expr.params[1];

            // Determine the comparison method based on type
            let type_prefix = match switch_expr_type {
                Some(ValueType::TCustom(t)) if t == "Str" => "Str",
                Some(ValueType::TCustom(t)) if t == "U8" => "U8",
                _ => "I64", // Default to I64
            };

            // Build: switch_expr.gteq(start).and(switch_expr.lteq(end))
            // After UFCS: Type.gteq(switch_expr, start) and Type.lteq(switch_expr, end)

            // Build: Type.gteq(switch_expr, start)
            let gteq_id = Expr::new_explicit(NodeType::Identifier("gteq".to_string()), vec![], line, col);
            let gteq_call = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier(type_prefix.to_string()), vec![gteq_id], line, col),
                    switch_expr.clone(),
                    start.clone(),
                ],
                line, col,
            );

            // Build: Type.lteq(switch_expr, end)
            let lteq_id = Expr::new_explicit(NodeType::Identifier("lteq".to_string()), vec![], line, col);
            let lteq_call = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier(type_prefix.to_string()), vec![lteq_id], line, col),
                    switch_expr.clone(),
                    end.clone(),
                ],
                line, col,
            );

            // Build: and(gteq_call, lteq_call)
            let condition = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier("and".to_string()), vec![], line, col),
                    gteq_call,
                    lteq_call,
                ],
                line, col,
            );

            Ok((condition, vec![], None))
        }
        NodeType::Identifier(name) => {
            // Enum variant without payload or simple value comparison
            // Check if this looks like an enum variant:
            // 1. Has dots (e.g., EnumType.Variant)
            // 2. Has nested identifier params (e.g., EnumType.Variant parsed as identifier chain)
            // 3. Switch expression is an enum type AND name is NOT a variable in scope
            //    (so simple names like "Bar" are variants, but "expected" is a variable)
            let switch_is_enum = match switch_expr_type {
                Some(ValueType::TCustom(ref type_name)) => {
                    context.scope_stack.lookup_enum(type_name).is_some()
                }
                _ => false
            };
            // Check if this identifier is a variable in scope holding an enum VALUE
            // (not a type name or enum variant constant).
            // Type names have value_type: TType(...), while variables have value_type: TCustom(...)
            let is_enum_value_variable = match context.scope_stack.lookup_symbol(name) {
                Some(sym_info) => {
                    // It's a variable if it has TCustom type (actual value), not TType (type definition)
                    matches!(sym_info.value_type, ValueType::TCustom(_))
                }
                None => false
            };

            // If it's a variable holding enum value and switch type is enum, compare enum_to_str values
            if is_enum_value_variable && switch_is_enum {
                // Runtime enum comparison: enum_to_str(switch_expr).eq(enum_to_str(case_expr))
                let enum_to_str_switch = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                        switch_expr.clone(),
                    ],
                    line, col,
                );
                let enum_to_str_case = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                        case_expr.clone(),
                    ],
                    line, col,
                );
                let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
                let condition = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier("Str".to_string()), vec![eq_id], line, col),
                        enum_to_str_switch,
                        enum_to_str_case,
                    ],
                    line, col,
                );
                return Ok((condition, vec![], None));
            }

            let is_enum_variant = name.contains('.') || !case_expr.params.is_empty() || switch_is_enum;

            if is_enum_variant {
                // Enum variant: compare using enum_to_str
                let variant_str = if name.contains('.') {
                    name.clone()
                } else if let Some(ValueType::TCustom(enum_name)) = switch_expr_type {
                    // Build full variant name from nested identifiers
                    let mut full_name = name.clone();
                    for p in &case_expr.params {
                        if let NodeType::Identifier(sub) = &p.node_type {
                            full_name.push('.');
                            full_name.push_str(sub);
                        }
                    }
                    if !full_name.contains('.') {
                        format!("{}.{}", enum_name, full_name)
                    } else {
                        full_name
                    }
                } else {
                    name.clone()
                };

                // Build: enum_to_str(switch_expr).eq("variant_str")
                let enum_to_str_call = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                        switch_expr.clone(),
                    ],
                    line, col,
                );
                let str_literal = Expr::new_explicit(
                    NodeType::LLiteral(Literal::Str(variant_str)),
                    vec![], line, col,
                );
                let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
                let condition = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier("Str".to_string()), vec![eq_id], line, col),
                        enum_to_str_call,
                        str_literal,
                    ],
                    line, col,
                );
                Ok((condition, vec![], None))
            } else {
                // Simple value comparison using eq
                let type_prefix = match switch_expr_type {
                    Some(ValueType::TCustom(t)) => t.clone(),
                    _ => "I64".to_string(),
                };
                let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
                let condition = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier(type_prefix), vec![eq_id], line, col),
                        switch_expr.clone(),
                        case_expr.clone(),
                    ],
                    line, col,
                );
                Ok((condition, vec![], None))
            }
        }
        NodeType::LLiteral(_) => {
            // Literal value comparison
            let type_prefix = match switch_expr_type {
                Some(ValueType::TCustom(t)) => t.clone(),
                _ => "I64".to_string(),
            };
            let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
            let condition = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier(type_prefix), vec![eq_id], line, col),
                    switch_expr.clone(),
                    case_expr.clone(),
                ],
                line, col,
            );
            Ok((condition, vec![], None))
        }
        NodeType::FCall => {
            // FCall case can be either:
            // 1. Enum variant with payload: Variant(payload_pattern) - when switch_expr is an enum
            // 2. Computed value: add(40, 2) - when switch_expr is not an enum
            //
            // Check if switch expression is an enum type
            let is_enum_switch = if let Some(ValueType::TCustom(ref type_name)) = switch_expr_type {
                context.scope_stack.lookup_enum(type_name).is_some()
            } else {
                false
            };

            // If not an enum switch, treat as computed value comparison
            if !is_enum_switch {
                // Fall through to default: compare values using eq
                let type_prefix = match switch_expr_type {
                    Some(ValueType::TCustom(t)) => t.clone(),
                    _ => "I64".to_string(),
                };
                let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
                let condition = Expr::new_explicit(
                    NodeType::FCall,
                    vec![
                        Expr::new_explicit(NodeType::Identifier(type_prefix), vec![eq_id], line, col),
                        switch_expr.clone(),
                        case_expr.clone(),
                    ],
                    line, col,
                );
                return Ok((condition, vec![], None));
            }

            // Enum variant with payload in shorthand form: Variant(payload_pattern)
            // This handles nested patterns like ValueType.TType(TTypeDef.TEnumDef)
            //
            // Build the full variant name including nested identifiers
            let variant_name_expr = &case_expr.params[0]; // Function name part (e.g., ValueType.TType)
            let full_variant_name = build_identifier_chain_name(variant_name_expr);

            // Check if there's a payload argument (the inner pattern)
            let has_nested_pattern = case_expr.params.len() > 1;

            // Build outer condition: enum_to_str(switch_expr).eq("FullVariantName")
            let enum_to_str_call = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                    switch_expr.clone(),
                ],
                line, col,
            );
            let str_literal = Expr::new_explicit(
                NodeType::LLiteral(Literal::Str(full_variant_name.clone())),
                vec![], line, col,
            );
            let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
            let outer_condition = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier("Str".to_string()), vec![eq_id], line, col),
                    enum_to_str_call,
                    str_literal,
                ],
                line, col,
            );

            if has_nested_pattern {
                // Get the inner pattern (e.g., TTypeDef.TEnumDef)
                let inner_pattern_expr = &case_expr.params[1];
                let inner_variant_name = build_identifier_chain_name(inner_pattern_expr);

                // For nested patterns, we need to extract the outer payload and check the inner
                // Get the variant short name for enum_get_payload
                let variant_short = if let Some(dot_pos) = full_variant_name.rfind('.') {
                    full_variant_name[dot_pos + 1..].to_string()
                } else {
                    full_variant_name.clone()
                };

                // Get payload type from enum definition
                let (enum_type_name, _) = if let Some(dot_pos) = full_variant_name.rfind('.') {
                    (full_variant_name[..dot_pos].to_string(), full_variant_name[dot_pos + 1..].to_string())
                } else if let Some(ValueType::TCustom(enum_name)) = switch_expr_type {
                    (enum_name.clone(), full_variant_name.clone())
                } else {
                    return Err(case_expr.lang_error("", "precomp", "FCall pattern without type context"));
                };

                let payload_type = context.scope_stack.lookup_enum(&enum_type_name)
                    .and_then(|e| e.get(&variant_short).cloned())
                    .flatten();

                if let Some(payload_type) = payload_type {
                    let temp_name = format!("_sw{}_{}payload", case_expr.line, case_expr.col);

                    // Declare temp variable for payload
                    let var_decl = Declaration {
                        name: temp_name.clone(),
                        value_type: payload_type.clone(),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        default_value: None,
                    };
                    let default_val = build_default_value(context, &payload_type, line, col);
                    let decl_expr = Expr::new_explicit(
                        NodeType::Declaration(var_decl),
                        vec![default_val],
                        line, col,
                    );

                    // Extract payload
                    let payload_call = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                            switch_expr.clone(),
                            Expr::new_explicit(NodeType::LLiteral(Literal::Str(variant_short)), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(temp_name.clone()), vec![], line, col),
                        ],
                        line, col,
                    );

                    // Build inner condition: enum_to_str(temp_var).eq("InnerVariantName")
                    let inner_enum_to_str = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(temp_name), vec![], line, col),
                        ],
                        line, col,
                    );
                    let inner_str_literal = Expr::new_explicit(
                        NodeType::LLiteral(Literal::Str(inner_variant_name)),
                        vec![], line, col,
                    );
                    let inner_eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
                    let inner_condition = Expr::new_explicit(
                        NodeType::FCall,
                        vec![
                            Expr::new_explicit(NodeType::Identifier("Str".to_string()), vec![inner_eq_id], line, col),
                            inner_enum_to_str,
                            inner_str_literal,
                        ],
                        line, col,
                    );

                    // Build combined condition as if-expression:
                    // if outer { decl; payload_extract; inner_check } else { false }
                    // This ensures each case has an independent condition that does both checks
                    let if_body = Expr::new_explicit(
                        NodeType::Body,
                        vec![decl_expr, payload_call, inner_condition],
                        line, col,
                    );
                    let false_literal = Expr::new_explicit(
                        NodeType::Identifier("false".to_string()),
                        vec![], line, col,
                    );
                    let combined_condition = Expr::new_explicit(
                        NodeType::If,
                        vec![outer_condition, if_body, false_literal],
                        line, col,
                    );

                    return Ok((combined_condition, vec![], None));
                }

                return Ok((outer_condition, vec![], None));
            }

            // Simple case - no nested pattern
            Ok((outer_condition, vec![], None))
        }
        _ => {
            // Fallback: treat as value comparison
            let type_prefix = match switch_expr_type {
                Some(ValueType::TCustom(t)) => t.clone(),
                _ => "I64".to_string(),
            };
            let eq_id = Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col);
            let condition = Expr::new_explicit(
                NodeType::FCall,
                vec![
                    Expr::new_explicit(NodeType::Identifier(type_prefix), vec![eq_id], line, col),
                    switch_expr.clone(),
                    case_expr.clone(),
                ],
                line, col,
            );
            Ok((condition, vec![], None))
        }
    }
}

/// Build the case body with optional prefix statements (for payload extraction)
/// rename_mapping: optional (old_name, new_name) for renaming binding variable references
fn build_case_body(
    context: &mut Context,
    body_expr: &Expr,
    body_prefix: Vec<Expr>,
    rename_mapping: Option<(String, String)>,
) -> Result<Expr, String> {
    if body_prefix.is_empty() {
        precomp_expr(context, body_expr)
    } else {
        // Check if the last element is a nested condition marker (NodeType::If with 1 param)
        // This is used for nested enum patterns like TType(TTypeDef.TStructDef)
        let (actual_prefix, nested_condition) = {
            let mut prefix = body_prefix;
            let nested_cond = if let Some(last) = prefix.last() {
                if matches!(&last.node_type, NodeType::If) && last.params.len() == 1 {
                    let cond = prefix.pop().unwrap();
                    Some(cond.params[0].clone())
                } else {
                    None
                }
            } else {
                None
            };
            (prefix, nested_cond)
        };

        // Apply rename transformation if needed (for mangled binding variable names)
        let renamed_body = if let Some((old_name, new_name)) = &rename_mapping {
            rename_identifier(body_expr, old_name, new_name)
        } else {
            body_expr.clone()
        };

        // Combine prefix with body into a new body
        let transformed_body = precomp_expr(context, &renamed_body)?;

        // Pop the scope that was pushed for pattern binding (only if scope was pushed)
        if rename_mapping.is_some() {
            let _ = context.scope_stack.pop();
        }

        // Extract statements from the original body (if it's a Body node)
        let body_statements: Vec<Expr> = if matches!(transformed_body.node_type, NodeType::Body) {
            transformed_body.params
        } else {
            vec![transformed_body]
        };

        // If there's a nested condition, wrap the body in an if statement
        let final_body = if let Some(nested_cond) = nested_condition {
            // Wrap body in: if nested_cond { body }
            let inner_body = Expr::new_explicit(
                NodeType::Body,
                body_statements,
                body_expr.line, body_expr.col,
            );
            vec![Expr::new_explicit(
                NodeType::If,
                vec![nested_cond, inner_body],
                body_expr.line, body_expr.col,
            )]
        } else {
            body_statements
        };

        // Combine prefix with final body
        let mut all_statements = actual_prefix;
        all_statements.extend(final_body);

        Ok(Expr::new_explicit(NodeType::Body, all_statements, body_expr.line, body_expr.col))
    }
}

/// Transform StructDef - recursively transform default values (which contain function defs)
fn precomp_struct_def(context: &mut Context, e: &Expr, struct_def: &SStructDef) -> Result<Expr, String> {
    let mut new_default_values = HashMap::new();
    for (name, value_expr) in &struct_def.default_values {
        // Bug #40 fix: For method definitions, set function name context
        let is_func = matches!(&value_expr.node_type, NodeType::FuncDef(_));
        let saved_func = context.current_precomp_func.clone();
        let saved_counter = context.precomp_forin_counter;
        if is_func {
            context.current_precomp_func = name.clone();
            context.precomp_forin_counter = 0;
        }

        new_default_values.insert(name.clone(), precomp_expr(context, value_expr)?);

        // Bug #40 fix: Restore previous function context
        if is_func {
            context.current_precomp_func = saved_func;
            context.precomp_forin_counter = saved_counter;
        }
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
            is_comptime_const: false,  // Function args are not comptime constants
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
    // Eagerly create default instance template for this struct type
    let inner_e = e.get(0)?;
    let mut value_type = match get_value_type(context, &inner_e) {
        Ok(val_type) => val_type,
        Err(error_string) => {
            return Err(e.lang_error(&context.path, "precomp", &error_string));
        },
    };
    if decl.value_type != ValueType::TCustom(INFER_TYPE.to_string()) {
        if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
            value_type = decl.value_type.clone();
        } else if value_type != decl.value_type {
            return Err(e.lang_error(&context.path, "precomp", &format!("'{}' declared of type {} but initialized to type {:?}.", decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type))));
        }
    }
    if let ValueType::TType(TTypeDef::TEnumDef) = value_type {
        match &inner_e.node_type {
            NodeType::EnumDef(enum_def) => {
                context.scope_stack.declare_enum(decl.name.clone(), enum_def.clone());
                context.scope_stack.declare_symbol(decl.name.to_string(), SymbolInfo{value_type: value_type.clone(), is_mut: decl.is_mut, is_copy: decl.is_copy, is_own: decl.is_own, is_comptime_const: false });
                return Ok(e.clone());
            },
            _ => return Err(e.lang_error(&context.path, "precomp", &format!("Cannot declare '{}' of type '{}', expected enum definition.",
                                                          &decl.name, value_type_to_str(&decl.value_type)))),
        }
    }
    if let ValueType::TType(TTypeDef::TStructDef) = value_type {
        if let NodeType::StructDef(struct_def) = &inner_e.node_type {
            context.scope_stack.declare_struct(decl.name.clone(), struct_def.clone());
            let saved_path = context.path.clone();
            eval_declaration(decl, context, e)?;
            context.path = saved_path;
        }
    }

    // Bug #40 fix: For function declarations, set the function name and reset counter
    // BEFORE processing the body so for-in loops get deterministic names
    let is_func_decl = !e.params.is_empty() && matches!(&e.params[0].node_type, NodeType::FuncDef(_));
    let saved_func = context.current_precomp_func.clone();
    let saved_counter = context.precomp_forin_counter;
    if is_func_decl {
        context.current_precomp_func = decl.name.clone();
        context.precomp_forin_counter = 0;
    }

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

    // Bug #40 fix: Restore previous function context
    if is_func_decl {
        context.current_precomp_func = saved_func;
        context.precomp_forin_counter = saved_counter;
    }

    // REM: Declarations currently always require an initialization value,
    // so new_params should never be empty.
    if e.params.len() != 1 {
        return Err(e.lang_error(&context.path, "precomp", "Declarations can have only one child expression"));
    }

    // Determine if this is a compile-time constant
    // Only mut matters for constantness - copy/own are about ownership, orthogonal to comptime.
    // Any type can be comptime - the type doesn't matter, only how the value is computed.
    let is_comptime_const = !decl.is_mut
        && is_comptime_evaluable(context, &new_params[0]);

    // Register the declared variable in scope
    context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
        value_type: value_type.clone(),
        is_mut: decl.is_mut,
        is_copy: decl.is_copy,
        is_own: decl.is_own,
        is_comptime_const,
    });

    // Also register function definitions so UFCS can resolve their return types
    if let ValueType::TFunction(_) = &value_type {
        if let NodeType::FuncDef(func_def) = &new_params[0].node_type {
            context.scope_stack.declare_func(decl.name.clone(), func_def.clone());
        }
    }

    // Store I64/U8/Str declarations in arena when their initializer is comptime-evaluable.
    // Unlike the is_comptime_const flag (which also requires !is_mut for folding identifiers),
    // we store ALL comptime-evaluable values including mut ones, just like interpreter does.
    // This is needed for eval_expr to work during constant folding (e.g., mut loop variables).
    // Only do this at global scope - inside function bodies, evaluating could cause side effects
    // to run at compile time AND runtime (e.g., print_debug func in mode liba).
    let at_global_scope = context.scope_stack.frames.len() == 1;
    if at_global_scope {
        if let ValueType::TCustom(ref custom_type_name) = &value_type {
            match custom_type_name.as_str() {
                "I64" | "U8" | "Str" => {
                    if is_comptime_evaluable(context, &new_params[0]) {
                        let inner_e = &new_params[0];
                        let result = eval_expr(context, inner_e)?;
                        if !result.is_throw {
                            EvalArena::insert_primitive(context, &decl.name, &value_type, &result.value, e)?;
                        }
                    }
                },
                _ => {},
            }
        }
    }

    // For non-mut struct instance declarations (like `true := Bool.from_i64(1)`),
    // run eval_declaration to store the instance in EvalArena so ccodegen can find it.
    // Only do this at global scope (same reason as above - avoid side effects inside func bodies).
    if at_global_scope && !decl.is_mut && !decl.is_copy && !decl.is_own && is_comptime_evaluable(context, &new_params[0]) {
        if let ValueType::TCustom(ref custom_type_name) = &value_type {
            // Skip primitives (I64, U8) - handled above. Skip Str - needs special handling.
            if custom_type_name != "I64" && custom_type_name != "U8" && custom_type_name != "Str" {
                // Check if this is a struct type (not a struct definition)
                if let Some(sym) = context.scope_stack.lookup_symbol(custom_type_name) {
                    if sym.value_type == ValueType::TType(TTypeDef::TStructDef) {
                        let saved_path = context.path.clone();
                        eval_declaration(decl, context, e)?;
                        context.path = saved_path;
                    }
                }
            }
        }
    }

    Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
}

/// Transform Catch node - register the catch variable in scope before processing body
/// This enables UFCS resolution for methods called on the error variable
/// Catch structure: [var_name_expr, type_expr, body_expr]
fn precomp_catch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if e.params.len() < 3 {
        // Malformed catch - just use default handling
        return precomp_params(context, e);
    }

    // Get the catch variable name and type
    let var_name = match &e.params[0].node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return precomp_params(context, e), // Not a simple identifier, use default handling
    };
    let type_name = match &e.params[1].node_type {
        NodeType::Identifier(name) => name.clone(),
        _ => return precomp_params(context, e), // Not a simple type, use default handling
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
    let new_body = precomp_expr(context, &e.params[2])?;

    // Pop the scope frame
    let _ = context.scope_stack.pop();

    // Return the transformed catch with original var_name, type, and new body
    Ok(Expr::new_clone(
        NodeType::Catch,
        e,
        vec![e.params[0].clone(), e.params[1].clone(), new_body],
    ))
}

/// Transform FCall node - this is where UFCS resolution happens
fn precomp_fcall(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // 1. Check for compile-time intrinsics (loc, _file, _line, _col)
    if let Some(replaced) = try_replace_comptime_intrinsic(context, e) {
        return Ok(replaced);
    }

    // Get func_expr and combined_name before any transformation
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Ok(e.clone()), // Empty FCall, shouldn't happen but just return as-is
    };

    let combined_name = if let NodeType::Identifier(_) = &func_expr.node_type {
        crate::rs::parser::get_combined_name(&context.path, func_expr)?
    } else {
        String::new()
    };

    // 3. Struct constructor - create instance like eval does (before arg transform)
    if !combined_name.is_empty() && context.scope_stack.lookup_struct(&combined_name).is_some() {
        create_default_instance(context, &combined_name, &e)?;
        if let NodeType::Identifier(id_name) = &func_expr.node_type {
            if func_expr.params.is_empty() {
                insert_struct_instance(context, id_name, &combined_name, &e)?;
            }
        }
        // Transform arguments for struct constructor
        let mut transformed_params = Vec::new();
        for p in &e.params {
            transformed_params.push(precomp_expr(context, p)?);
        }
        return Ok(Expr::new_clone(e.node_type.clone(), &e, transformed_params));
    }

    // 4. Enum constructor (e.g., Color.Green(true)) - before arg transform
    if context.scope_stack.is_enum_constructor(&combined_name) {
        // Transform arguments for enum constructor
        let mut transformed_params = Vec::new();
        for p in &e.params {
            transformed_params.push(precomp_expr(context, p)?);
        }
        return Ok(Expr::new_clone(e.node_type.clone(), &e, transformed_params));
    }

    // 5. Transform all arguments
    let mut transformed_params = Vec::new();
    for p in &e.params {
        transformed_params.push(precomp_expr(context, p)?);
    }
    let e = Expr::new_clone(e.node_type.clone(), &e, transformed_params);

    // Get func_expr again from transformed expression
    let func_expr = match e.params.first() {
        Some(expr) => expr,
        None => return Ok(e),
    };

    if let NodeType::Identifier(_id_name) = &func_expr.node_type {
        let combined_name = crate::rs::parser::get_combined_name(&context.path, func_expr)?;

        // 6. Regular function call - check if it exists
        if let Some(func_def) = context.scope_stack.lookup_func(&combined_name) {
            // Ext functions: evaluation happens through eval_comptime path (see doc/precomp.org)
            // Exception: import() must run during precomp to load code
            if func_def.is_ext() {
                let parts: Vec<&str> = combined_name.split('.').collect();
                if let Some(&"import") = parts.last() {
                    eval_expr(context, &e)?;
                }
                return Ok(e.clone());
            }
            // Reorder named arguments to positional order before constant folding
            let e = reorder_named_args(context, &e, &func_def)?;
            return Ok(e);
        }

        // UFCS for chained calls: func(result, args) -> Type.func(result, args)
        // e.g., add(1, 2).mul(3) becomes mul(add(1,2), 3) which transforms to I64.mul(add(1,2), 3)
        // This only applies when no standalone function with this name exists (checked above).
        if e.params.len() >= 2 {
            let first_arg = e.get(1)?;
            if let Ok(target_type) = get_value_type(context, first_arg) {
                // Get type name from value_type - TCustom or TMulti (variadic params become Array)
                let custom_type_name = match &target_type {
                    ValueType::TCustom(name) => Some(name.clone()),
                    ValueType::TMulti(_) => Some("Array".to_string()),
                    _ => None,
                };
                if let Some(type_name) = custom_type_name {
                    let method_name = format!("{}.{}", type_name, combined_name);
                    if context.scope_stack.lookup_func(&method_name).is_some() {
                        // Transform: func(target, args...) -> Type.func(target, args...)
                        let new_e = Expr::new_clone(NodeType::Identifier(method_name.clone()), e.get(0)?, Vec::new());
                        let mut new_args = Vec::new();
                        new_args.push(new_e);
                        new_args.extend(e.params[1..].to_vec());
                        return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, new_args));
                    }
                }
            }
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
                            if context.scope_stack.lookup_func(&assoc_method_name).is_some() {
                                let assoc_new_id_e = Expr::new_clone(NodeType::Identifier(assoc_method_name.clone()), e.get(0)?, Vec::new());
                                let mut assoc_new_args = Vec::new();
                                assoc_new_args.push(assoc_new_id_e);
                                assoc_new_args.push(receiver_expr);
                                assoc_new_args.extend(e.params[1..].to_vec());
                                return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, assoc_new_args));
                            }
                        }
                    }
                    Err(_err) => {
                        // Type could not be determined - fall through to standalone function check
                    }
                }

                // Fall back to standalone function
                if context.scope_stack.lookup_func(&ufcs_func_name.to_string()).is_some() {
                    let standalone_new_id_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), e.get(0)?, Vec::new());
                    let mut standalone_new_args = Vec::new();
                    standalone_new_args.push(standalone_new_id_e);
                    standalone_new_args.push(receiver_expr);
                    standalone_new_args.extend(e.params[1..].to_vec());
                    return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, standalone_new_args));
                }
            }
        }
    }

    // No transformation needed
    Ok(e)
}
