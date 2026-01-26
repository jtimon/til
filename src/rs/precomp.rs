// Precomputation phase: Transforms UFCS calls into regular function calls
// and performs compile-time constant folding for pure functions.
// This phase runs after typer, before interpreter/builder.

use crate::rs::init::{Context, get_value_type, get_func_name_in_call, SymbolInfo, ScopeType};
use crate::rs::typer::get_func_def_for_fcall_with_expr;
use std::collections::HashMap;
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, Literal, TTypeDef,
    value_type_to_str, INFER_TYPE,
};
use crate::rs::interpreter::{eval_expr, eval_declaration, insert_struct_instance, create_default_instance};
use crate::rs::eval_arena::EvalArena;
use crate::rs::precomp_ext::try_replace_comptime_intrinsic;

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
        NodeType::FCall(_) => {
            let mut const_folded = precomp_fcall(context, e)?;

            // Try compile-time constant folding for pure functions with literal args.
            // Only fold at global scope - inside function definitions, values from other
            // modules may not be available yet (import ordering). Interpreter doesn't
            // evaluate function bodies during import either.
            let at_global_scope = context.scope_stack.frames.len() == 1;

            // Check if this is a macro call - macros MUST be evaluated at compile-time
            // but only when called at global scope with comptime args (same as funcs,
            // just with an error if args aren't comptime instead of silent skip)
            let is_macro_call = is_macro_fcall(context, &const_folded);
            if at_global_scope && is_macro_call {
                // Macros require all arguments to be compile-time evaluable
                if !is_comptime_evaluable(context, &const_folded) {
                    let f_name = get_func_name_in_call(&const_folded);
                    return Err(const_folded.error(&context.path, "precomp",
                        &format!("Macro '{}' requires all arguments to be compile-time constants", f_name)));
                }
                // Force compile-time evaluation
                const_folded = eval_comptime(context, &const_folded)?;
                return Ok(const_folded);
            }

            if at_global_scope && is_comptime_evaluable(context, &const_folded) {
                const_folded = eval_comptime(context, &const_folded)?;
            }
            return Ok(const_folded);
        },
        NodeType::If => precomp_params(context, e),
        NodeType::While => precomp_params(context, e),
        // Switch should have been desugared in desugarer phase
        NodeType::Switch => {
            panic!("Switch should have been desugared in desugarer phase");
        },
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
        // ForIn should have been desugared in desugarer phase
        NodeType::ForIn(_) => {
            panic!("ForIn should have been desugared in desugarer phase");
        },
    }
}

// ---------- Compile-time constant folding

/// Check if an FCall is a macro call.
fn is_macro_fcall(context: &Context, e: &Expr) -> bool {
    let mut e_clone = e.clone();
    match get_func_def_for_fcall_with_expr(context, &mut e_clone) {
        Ok(Some(func_def)) => func_def.is_macro(),
        Ok(None) | Err(_) => false,
    }
}

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
        NodeType::FCall(_) => {
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
    // Error if INFER_TYPE reaches precomp - typer should have resolved all types
    if decl.value_type == ValueType::TCustom(INFER_TYPE.to_string()) {
        return Err(e.lang_error(&context.path, "precomp", &format!("Declaration '{}' has INFER_TYPE - should have been resolved by typer", decl.name)));
    }
    // Type checking
    if decl.value_type == ValueType::TCustom("U8".to_string()) && value_type == ValueType::TCustom("I64".to_string()) {
        value_type = decl.value_type.clone();
    } else if value_type != decl.value_type {
        return Err(e.lang_error(&context.path, "precomp", &format!("'{}' declared of type {} but initialized to type {:?}.", decl.name, value_type_to_str(&decl.value_type), value_type_to_str(&value_type))));
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

/// Transform FCall node - handles comptime intrinsics, struct/enum constructors, and import()
/// UFCS resolution and named argument reordering happen in the ufcs phase (before precomp)
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

    // 2. Struct constructor - create instance like eval does (before arg transform)
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

    // 3. Enum constructor (e.g., Color.Green(true)) - before arg transform
    if context.scope_stack.is_enum_constructor(&combined_name) {
        // Transform arguments for enum constructor
        let mut transformed_params = Vec::new();
        for p in &e.params {
            transformed_params.push(precomp_expr(context, p)?);
        }
        return Ok(Expr::new_clone(e.node_type.clone(), &e, transformed_params));
    }

    // 4. Transform all arguments
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

        // 5. Handle ext functions and import()
        if let Some(func_def) = context.scope_stack.lookup_func(&combined_name) {
            // Ext functions: evaluation happens through eval_comptime path (see doc/precomp.org)
            // Exception: import() must run during precomp to load code
            if func_def.is_ext() {
                let parts: Vec<&str> = combined_name.split('.').collect();
                if let Some(&"import") = parts.last() {
                    eval_expr(context, &e)?;
                }
            }
        }
    }

    // No transformation needed (UFCS already resolved in ufcs phase)
    Ok(e)
}
