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

    // Check if we need to fill in default values (fewer args than params)
    // Don't apply to variadic functions
    let needs_defaults = !is_variadic && call_args.len() < func_def.args.len();

    // If no named args and no defaults needed, return unchanged
    if !has_named_args && !needs_defaults {
        return Ok(e.clone());
    }

    let mut result = vec![e.params[0].clone()]; // Keep function identifier

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
                    let parts: Vec<&str> = combined_name.split('.').collect();
                    if parts.len() == 2 {
                        let enum_type = parts[0];
                        if context.scope_stack.lookup_enum(enum_type).is_some() {
                            // It's an enum constructor - check all args are comptime
                            for i in 1..e.params.len() {
                                if !is_comptime_evaluable(context, &e.params[i]) {
                                    return false;
                                }
                            }
                            return true;
                        }
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
        let thrown_type = result.thrown_type.as_deref().unwrap_or("unknown");
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
fn build_default_value(vt: &ValueType, line: usize, col: usize) -> Expr {
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
                // For other types (structs, other enums), use the default constructor
                _ => Expr::new_explicit(
                    NodeType::FCall,
                    vec![Expr::new_explicit(NodeType::Identifier(type_name.clone()), vec![], line, col)],
                    line,
                    col,
                ),
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
    let index_var_name = match &context.current_precomp_func {
        Some(func_name) => format!("_for_i_{}_{}", func_name, forin_id),
        None => format!("_for_i_{}", forin_id),
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
        if let Some((first_variant, payload_type)) = enum_def.iter().next() {
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
                let default_arg = build_default_value(payload_vt, e.line, e.col);
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
    // Add original body statements
    match &body_expr.node_type {
        NodeType::Body => {
            while_body_params.extend(body_expr.params.clone());
        },
        _ => {
            while_body_params.push(body_expr);
        }
    }
    while_body_params.push(inc_stmt);
    let while_body = Expr::new_explicit(NodeType::Body, while_body_params, e.line, e.col);

    // Build while: while _for_i.lt(collection.len()) { ... }
    let while_expr = Expr::new_explicit(NodeType::While, vec![cond_expr, while_body], e.line, e.col);

    // Build outer body: index_decl, while
    Ok(Expr::new_explicit(NodeType::Body, vec![index_decl_expr, while_expr], e.line, e.col))
}

/// Transform Switch - handle pattern binding variables by adding them to scope
/// before processing the case body. This mirrors the typer's handling of Bug #28.
fn precomp_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Switch structure: params[0] is switch expression, then pairs of (case, body)
    if e.params.is_empty() {
        return Ok(e.clone());
    }

    let mut new_params = Vec::new();

    // Transform switch expression
    let switch_expr = &e.params[0];
    new_params.push(precomp_expr(context, switch_expr)?);

    // Get the type of the switch expression for pattern binding resolution
    let switch_expr_type = get_value_type(context, switch_expr).ok();

    // Process case/body pairs
    let mut i = 1;
    while i + 1 < e.params.len() {
        let case_expr = &e.params[i];
        let body_expr = &e.params[i + 1];

        // Transform case expression (no scope change needed for case itself)
        new_params.push(precomp_expr(context, case_expr)?);

        // For pattern matching with binding variable, add binding to scope before processing body
        if let NodeType::Pattern(PatternInfo { variant_name, binding_var }) = &case_expr.node_type {
            if let Some(ValueType::TCustom(ref enum_name)) = switch_expr_type {
                // Extract variant name (after the last dot)
                let variant = if let Some(dot_pos) = variant_name.rfind('.') {
                    &variant_name[dot_pos + 1..]
                } else {
                    variant_name.as_str()
                };

                // Get payload type from enum definition
                let payload_type = context.scope_stack.lookup_enum(enum_name)
                    .and_then(|e| e.get(variant).cloned())
                    .flatten();

                if let Some(payload_type) = payload_type {
                    // Push block scope, declare binding variable, transform body, pop scope
                    context.scope_stack.push(ScopeType::Block);
                    context.scope_stack.declare_symbol(
                        binding_var.clone(),
                        SymbolInfo {
                            value_type: payload_type,
                            is_mut: false,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        }
                    );
                    new_params.push(precomp_expr(context, body_expr)?);
                    let _ = context.scope_stack.pop();
                } else {
                    // No payload type found, transform body without binding
                    new_params.push(precomp_expr(context, body_expr)?);
                }
            } else {
                // Switch type not found, transform body without binding
                new_params.push(precomp_expr(context, body_expr)?);
            }
        } else {
            // Not a pattern, transform body normally
            new_params.push(precomp_expr(context, body_expr)?);
        }

        i += 2;
    }

    // Handle odd trailing element (default case body without case expression)
    if i < e.params.len() {
        new_params.push(precomp_expr(context, &e.params[i])?);
    }

    Ok(Expr::new_clone(NodeType::Switch, e, new_params))
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
            context.current_precomp_func = Some(name.clone());
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
        context.current_precomp_func = Some(decl.name.clone());
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
    if !combined_name.is_empty() {
        let parts: Vec<&str> = combined_name.split('.').collect();
        if parts.len() == 2 {
            let enum_type = parts[0];
            if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type) {
                let variant_name = parts[1];
                if enum_def.contains_key(variant_name) {
                    // Transform arguments for enum constructor
                    let mut transformed_params = Vec::new();
                    for p in &e.params {
                        transformed_params.push(precomp_expr(context, p)?);
                    }
                    return Ok(Expr::new_clone(e.node_type.clone(), &e, transformed_params));
                }
            }
        }
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
                        // Type could not be determined - fall through to standalone function check
                    }
                }

                // Fall back to standalone function
                if context.scope_stack.lookup_func(&ufcs_func_name.to_string()).is_some() {
                    let new_e = Expr::new_clone(NodeType::Identifier(ufcs_func_name.clone()), e.get(0)?, Vec::new());
                    let mut new_args = Vec::new();
                    new_args.push(new_e);
                    new_args.push(receiver_expr);
                    new_args.extend(e.params[1..].to_vec());
                    return Ok(Expr::new_clone(NodeType::FCall, e.get(0)?, new_args));
                }
            }
        }
    }

    // No transformation needed
    Ok(e)
}
