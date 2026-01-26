// Desugarer phase: Desugars ForIn loops to while loops with get() calls.
// This phase runs after typer, before precomp.

use crate::rs::init::{Context, ScopeType, SymbolInfo};
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, Literal,
    Declaration, str_to_value_type, transform_continue_with_step,
};

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
                                    NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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
                                NodeType::FCall(false),  // Issue #132: desugared calls don't throw
                                empty_enum_fcall_params,
                                line,
                                col,
                            )
                        }
                    } else {
                        // Not an enum - use struct-like constructor: TYPE()
                        let struct_fcall_params = vec![Expr::new_explicit(NodeType::Identifier(type_name.clone()), vec![], line, col)];
                        Expr::new_explicit(
                            NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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
fn desugar_forin(context: &mut Context, e: &Expr, var_type_name: &str) -> Result<Expr, String> {
    // Extract var_name from params[0]
    let var_name = match e.params.get(0) {
        Some(var_expr) => match &var_expr.node_type {
            NodeType::Identifier(name) => name.clone(),
            _ => return Err(e.lang_error(&context.path, "desugar", "ForIn: expected identifier for loop variable")),
        },
        None => return Err(e.lang_error(&context.path, "desugar", "ForIn: missing loop variable")),
    };

    // Get collection expression (params[1])
    let collection_expr = match e.params.get(1) {
        Some(expr) => desugar_expr(context, expr)?,
        None => return Err(e.lang_error(&context.path, "desugar", "ForIn: missing collection expression")),
    };

    // NOTE: We do NOT declare the loop variable in scope_stack here.
    // The desugarer just transforms AST; variable declaration will be handled
    // by the generated Declaration node in the desugared while loop.
    // Declaring here would leak variables across files during batch compilation.

    // Get body (params[2])
    let body_expr = match e.params.get(2) {
        Some(expr) => desugar_expr(context, expr)?,
        None => return Err(e.lang_error(&context.path, "desugar", "ForIn: missing body")),
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
        value_type: str_to_value_type("I64"),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    let zero_literal = Expr::new_explicit(NodeType::LLiteral(Literal::Number("0".to_string())), vec![], e.line, e.col);
    let index_decl_expr = Expr::new_explicit(NodeType::Declaration(index_decl), vec![zero_literal], e.line, e.col);

    // Build len(collection) - already desugared form
    let len_call_expr = Expr::new_explicit(
        NodeType::FCall(false),  // Issue #132: desugared calls don't throw
        vec![
            Expr::new_explicit(NodeType::Identifier("len".to_string()), vec![], e.line, e.col),
            collection_expr.clone(),
        ],
        e.line,
        e.col,
    );

    // Build lt(_for_i, len_result) - already desugared form
    let cond_expr = Expr::new_explicit(
        NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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
                    NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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
                NodeType::FCall(false),  // Issue #132: desugared calls don't throw
                vec![Expr::new_explicit(NodeType::Identifier(var_type_name.to_string()), vec![], e.line, e.col)],
                e.line,
                e.col,
            )
        }
    } else {
        // Not an enum - use struct-like constructor: TYPE()
        Expr::new_explicit(
            NodeType::FCall(false),  // Issue #132: desugared calls don't throw
            vec![Expr::new_explicit(NodeType::Identifier(var_type_name.to_string()), vec![], e.line, e.col)],
            e.line,
            e.col,
        )
    };
    let var_decl_expr = Expr::new_explicit(NodeType::Declaration(var_decl), vec![type_call], e.line, e.col);

    // Build: get(collection, _for_i, VAR) - already desugared form
    let get_call = Expr::new_explicit(
        NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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
        NodeType::FCall(false),  // Issue #132: desugared calls don't throw
        vec![
            Expr::new_explicit(NodeType::Identifier("panic".to_string()), vec![], e.line, e.col),
            Expr::new_explicit(
                NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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
        NodeType::FCall(false),  // Issue #132: desugared calls don't throw
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

/// Rename all occurrences of a variable in an expression tree.
/// Returns a new expression with all Identifier nodes matching old_name renamed to new_name.
/// Does NOT rename field names (identifiers that are params of other identifiers).
fn rename_identifier_in_expr(expr: &Expr, old_name: &str, new_name: &str) -> Expr {
    rename_identifier_in_expr_impl(expr, old_name, new_name, false)
}

/// Implementation of rename with flag to skip field names.
/// is_field_context indicates whether we're processing params of an Identifier (field access context).
fn rename_identifier_in_expr_impl(expr: &Expr, old_name: &str, new_name: &str, is_field_context: bool) -> Expr {
    // Handle the node type
    let new_node_type = match &expr.node_type {
        NodeType::Identifier(name) if name == old_name && !is_field_context => {
            // Only rename if not in field access context
            NodeType::Identifier(new_name.to_string())
        }
        NodeType::Declaration(decl) if decl.name == old_name => {
            NodeType::Declaration(Declaration {
                name: new_name.to_string(),
                value_type: decl.value_type.clone(),
                is_mut: decl.is_mut,
                is_copy: decl.is_copy,
                is_own: decl.is_own,
                default_value: decl.default_value.clone(),
            })
        }
        NodeType::Assignment(name) if name == old_name => {
            NodeType::Assignment(new_name.to_string())
        }
        _ => expr.node_type.clone(),
    };

    // Recursively process params
    // Check if this is an Identifier with params (field access like obj.field)
    let is_identifier_with_params = matches!(&expr.node_type, NodeType::Identifier(_)) && !expr.params.is_empty();

    let new_params: Vec<Expr> = expr.params.iter()
        .map(|p| {
            // If this is an Identifier with params, params[0+] are field names
            // So pass is_field_context=true for all params of an Identifier node
            if is_identifier_with_params {
                // For field access, params ARE the field names, don't rename them
                // But we still need to recursively process any nested expressions within them
                rename_identifier_in_expr_impl(p, old_name, new_name, true)
            } else {
                rename_identifier_in_expr_impl(p, old_name, new_name, false)
            }
        })
        .collect();

    Expr::new_explicit(new_node_type, new_params, expr.line, expr.col)
}

/// Extract variant info from a case pattern expression.
/// Returns (type_name, variant_name) e.g., ("Color", "Green") for Color.Green
fn get_case_variant_info(case_expr: &Expr) -> (String, String) {
    match &case_expr.node_type {
        NodeType::Identifier(name) => {
            // Check if it's "Type.Variant" format (with params) or "variant" shorthand
            if case_expr.params.is_empty() {
                // Could be "Type.Variant" string or just a literal value
                if name.contains('.') {
                    let parts: Vec<&str> = name.split('.').collect();
                    if parts.len() == 2 {
                        return (parts[0].to_string(), parts[1].to_string());
                    }
                }
                (String::new(), String::new())
            } else {
                // Identifier with params: Type -> Variant
                let type_name = name.clone();
                if let Some(variant_expr) = case_expr.params.first() {
                    if let NodeType::Identifier(variant_name) = &variant_expr.node_type {
                        return (type_name, variant_name.clone());
                    }
                }
                (type_name, String::new())
            }
        }
        NodeType::FCall(_) => {
            // FCall pattern like Type.Variant(payload_arg)
            // params[0] is Type.Variant identifier, params[1+] are arguments
            if let Some(func_expr) = case_expr.params.first() {
                let (type_name, variant_name) = get_case_variant_info(func_expr);
                return (type_name, variant_name);
            }
            (String::new(), String::new())
        }
        NodeType::Pattern(pattern_info) => {
            // Pattern already has variant_name in format "Type.Variant"
            if pattern_info.variant_name.contains('.') {
                let parts: Vec<&str> = pattern_info.variant_name.split('.').collect();
                if parts.len() == 2 {
                    return (parts[0].to_string(), parts[1].to_string());
                }
            }
            (String::new(), pattern_info.variant_name.clone())
        }
        _ => (String::new(), String::new()),
    }
}

/// Check if case pattern is a nested enum pattern like ValueType.TType(TTypeDef.TEnumDef)
/// Returns Some((outer_full_variant, inner_full_variant)) if it's a nested pattern
fn get_nested_pattern_info(case_expr: &Expr) -> Option<(String, String)> {
    if let NodeType::FCall(_) = &case_expr.node_type {
        // FCall pattern - check if it has a nested enum argument
        if case_expr.params.len() >= 2 {
            let func_expr = &case_expr.params[0];
            let arg_expr = &case_expr.params[1];

            // Get the outer variant name (e.g., "ValueType.TType")
            let (outer_type, outer_variant) = get_case_variant_info(func_expr);
            if outer_type.is_empty() || outer_variant.is_empty() {
                return None;
            }
            let outer_full = format!("{}.{}", outer_type, outer_variant);

            // Check if argument is also an enum pattern (not a simple binding variable)
            let (inner_type, inner_variant) = get_case_variant_info(arg_expr);
            if !inner_type.is_empty() && !inner_variant.is_empty() {
                let inner_full = format!("{}.{}", inner_type, inner_variant);
                return Some((outer_full, inner_full));
            }
        }
    }
    None
}

/// Check if the switch expression is an enum type and determine if any variant has payloads.
fn is_enum_switch(context: &Context, switch_expr: &Expr, cases: &[(Expr, Expr)]) -> (bool, String) {
    // First check if any case pattern looks like an enum pattern
    for (case_pattern, _) in cases {
        match &case_pattern.node_type {
            NodeType::Pattern(pattern_info) => {
                // Definitely an enum pattern with payload binding
                // Try to extract enum type from the pattern's variant_name (e.g., "Literal.Number" -> "Literal")
                if pattern_info.variant_name.contains('.') {
                    let parts: Vec<&str> = pattern_info.variant_name.split('.').collect();
                    if parts.len() >= 2 {
                        let type_name = parts[0].to_string();
                        if context.scope_stack.lookup_enum(&type_name).is_some() {
                            return (true, type_name);
                        }
                    }
                }
                // Fall back to getting type from switch expression
                if let Ok(ValueType::TCustom(enum_name)) = crate::rs::init::get_value_type(context, switch_expr) {
                    if context.scope_stack.lookup_enum(&enum_name).is_some() {
                        return (true, enum_name);
                    }
                }
                // Try to find enum containing this variant (shorthand pattern support)
                // Use find_enum_with_variant_payload if we have a binding (extracting payload)
                // to prefer enums where the variant actually has a payload
                if !pattern_info.variant_name.contains('.') {
                    let enum_name = if !pattern_info.binding_var.is_empty() {
                        // We're extracting a payload, so prefer enums with payloads
                        context.scope_stack.find_enum_with_variant_payload(&pattern_info.variant_name)
                    } else {
                        context.scope_stack.find_enum_with_variant(&pattern_info.variant_name)
                    };
                    if let Some(name) = enum_name {
                        return (true, name);
                    }
                }
                // If we still can't find the type, try to extract it from the variant name anyway
                if pattern_info.variant_name.contains('.') {
                    let parts: Vec<&str> = pattern_info.variant_name.split('.').collect();
                    if parts.len() >= 2 {
                        return (true, parts[0].to_string());
                    }
                }
                return (true, String::new());
            }
            NodeType::Identifier(name) => {
                // Check if it's Type.Variant format
                let (type_name, variant_name) = get_case_variant_info(case_pattern);
                if !variant_name.is_empty() && !type_name.is_empty() {
                    if context.scope_stack.lookup_enum(&type_name).is_some() {
                        return (true, type_name);
                    }
                }
                // Also check params for nested identifier
                if !case_pattern.params.is_empty() || name.contains('.') {
                    if let Ok(ValueType::TCustom(enum_name)) = crate::rs::init::get_value_type(context, switch_expr) {
                        if context.scope_stack.lookup_enum(&enum_name).is_some() {
                            return (true, enum_name);
                        }
                    }
                }
            }
            NodeType::FCall(_) => {
                // FCall like Type.Variant(payload) - definitely enum
                let (type_name, _variant_name) = get_case_variant_info(case_pattern);
                if !type_name.is_empty() && context.scope_stack.lookup_enum(&type_name).is_some() {
                    return (true, type_name);
                }
            }
            _ => {}
        }
    }

    // If no obvious enum patterns, check the switch expression type
    if let Ok(ValueType::TCustom(type_name)) = crate::rs::init::get_value_type(context, switch_expr) {
        if context.scope_stack.lookup_enum(&type_name).is_some() {
            return (true, type_name);
        }
    }

    (false, String::new())
}

/// Desugar Switch to if/else chain
/// For enum switches:
///   switch expr { case Type.Variant: body ... }
///   becomes:
///   { _switch_variant_N := enum_to_str(expr)
///     if eq(_switch_variant_N, "Type.Variant") { body }
///     else if ... }
/// For non-enum switches:
///   switch expr { case val: body ... }
///   becomes:
///   if eq(expr, val) { body } else if ...
fn desugar_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if e.params.is_empty() {
        return Err(e.lang_error(&context.path, "desugar", "Switch requires expression"));
    }

    let line = e.line;
    let col = e.col;

    // params[0] = switch expression
    // params[1..] = alternating (case_pattern, body) pairs
    // If params.len() is odd (> 1), the last element might be a default body
    let switch_expr = desugar_expr(context, &e.params[0])?;

    // Collect cases: (case_pattern, body) pairs, and optional default
    let mut cases: Vec<(Expr, Expr)> = Vec::new();
    let mut default_body: Option<Expr> = None;

    let mut i = 1;
    while i < e.params.len() {
        let case_pattern = &e.params[i];

        if matches!(case_pattern.node_type, NodeType::DefaultCase) {
            // Default case - next element is the body
            if i + 1 < e.params.len() {
                default_body = Some(desugar_expr(context, &e.params[i + 1])?);
            }
            i += 2;
            continue;
        }

        // Regular case - pattern and body
        if i + 1 < e.params.len() {
            let case_expr = desugar_expr(context, case_pattern)?;
            let body = desugar_expr(context, &e.params[i + 1])?;
            cases.push((case_expr, body));
        }
        i += 2;
    }

    // Check if this is an enum switch
    let (is_enum, enum_type_name) = is_enum_switch(context, &switch_expr, &cases);

    if is_enum {
        desugar_enum_switch(context, &switch_expr, &cases, default_body, &enum_type_name, line, col)
    } else {
        desugar_non_enum_switch(context, &switch_expr, &cases, default_body, line, col)
    }
}

/// Build an FCall expression: func_name(args...)
fn build_fcall(func_name: &str, args: Vec<Expr>, line: usize, col: usize) -> Expr {
    let mut params = vec![
        Expr::new_explicit(NodeType::Identifier(func_name.to_string()), vec![], line, col)
    ];
    params.extend(args);
    Expr::new_explicit(NodeType::FCall(false), params, line, col)
}

/// Build a qualified FCall expression: Type.method(args...)
/// This generates pre-resolved calls that don't need UFCS resolution.
fn build_qualified_fcall(type_name: &str, method_name: &str, args: Vec<Expr>, line: usize, col: usize) -> Expr {
    let qualified_name = format!("{}.{}", type_name, method_name);
    let mut params = vec![
        Expr::new_explicit(NodeType::Identifier(qualified_name), vec![], line, col)
    ];
    params.extend(args);
    Expr::new_explicit(NodeType::FCall(false), params, line, col)
}

/// Build a string literal expression
fn build_str_literal(s: &str, line: usize, col: usize) -> Expr {
    Expr::new_explicit(
        NodeType::LLiteral(Literal::Str(s.to_string())),
        vec![],
        line,
        col,
    )
}

/// Desugar an enum switch to if/else chain with enum_to_str comparisons
fn desugar_enum_switch(
    context: &mut Context,
    switch_expr: &Expr,
    cases: &[(Expr, Expr)],
    default_body: Option<Expr>,
    enum_type_name: &str,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    // Generate unique variable name for the variant string
    let forin_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = &context.current_precomp_func;
    let variant_var_name = if !func_name.is_empty() {
        format!("_switch_variant_{}_{}", func_name, forin_id)
    } else {
        format!("_switch_variant_{}", forin_id)
    };

    // Build: _switch_variant_N := enum_to_str(switch_expr)
    let enum_to_str_call = build_fcall("enum_to_str", vec![switch_expr.clone()], line, col);
    let variant_decl = Declaration {
        name: variant_var_name.clone(),
        value_type: str_to_value_type("Str"),
        is_mut: false,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    let variant_decl_expr = Expr::new_explicit(
        NodeType::Declaration(variant_decl),
        vec![enum_to_str_call],
        line,
        col,
    );

    // Pre-compute inner variant strings for nested patterns
    // This generates: _inner_variant_N := enum_to_str(enum_get_payload_result)
    // for each nested pattern case
    let (nested_pre_stmts, nested_inner_vars) = build_nested_pattern_pre_stmts(
        context, switch_expr, cases, line, col
    )?;

    // Build the if/else chain from the cases
    let if_chain = build_enum_if_chain(
        context, switch_expr, &variant_var_name, cases, default_body,
        enum_type_name, &nested_inner_vars, line, col
    )?;

    // Wrap in a Body node: { decl; nested_pre_stmts...; if_chain }
    let mut body_stmts = vec![variant_decl_expr];
    body_stmts.extend(nested_pre_stmts);
    body_stmts.push(if_chain);
    Ok(Expr::new_explicit(NodeType::Body, body_stmts, line, col))
}

/// Build pre-statements for nested patterns: extract inner payloads and get their variant strings
/// Returns (pre_statements, map from case_idx to inner_variant_var_name)
fn build_nested_pattern_pre_stmts(
    context: &mut Context,
    switch_expr: &Expr,
    cases: &[(Expr, Expr)],
    line: usize,
    col: usize,
) -> Result<(Vec<Expr>, std::collections::HashMap<usize, String>), String> {
    use std::collections::HashMap;
    let mut pre_stmts = Vec::new();
    let mut inner_vars: HashMap<usize, String> = HashMap::new();

    for (idx, (case_pattern, _)) in cases.iter().enumerate() {
        if let Some((_, inner_full)) = get_nested_pattern_info(case_pattern) {
            // Extract inner type name from "TTypeDef.TEnumDef" -> "TTypeDef"
            let inner_parts: Vec<&str> = inner_full.split('.').collect();
            let inner_type_name = if !inner_parts.is_empty() { inner_parts[0] } else { continue };

            let func_name = &context.current_precomp_func;
            let forin_id = context.precomp_forin_counter;
            context.precomp_forin_counter += 1;

            // Generate unique variable names
            let inner_payload_var = if !func_name.is_empty() {
                format!("_sw_inner_{}_{}", func_name, forin_id)
            } else {
                format!("_sw_inner_{}", forin_id)
            };
            let inner_variant_var = format!("{}_str", inner_payload_var);

            // 1. Declare inner payload variable: mut _sw_inner_N := InnerType.FirstVariant
            let inner_default = build_default_value(context, &ValueType::TCustom(inner_type_name.to_string()), line, col);
            let inner_decl = Declaration {
                name: inner_payload_var.clone(),
                value_type: ValueType::TCustom(inner_type_name.to_string()),
                is_mut: true,
                is_copy: false,
                is_own: false,
                default_value: None,
            };
            let inner_decl_expr = Expr::new_explicit(
                NodeType::Declaration(inner_decl),
                vec![inner_default],
                line,
                col,
            );
            pre_stmts.push(inner_decl_expr);

            // 2. Extract payload: enum_get_payload(switch_expr, InnerType, _sw_inner_N)
            let extract_call = build_fcall(
                "enum_get_payload",
                vec![
                    switch_expr.clone(),
                    Expr::new_explicit(NodeType::Identifier(inner_type_name.to_string()), vec![], line, col),
                    Expr::new_explicit(NodeType::Identifier(inner_payload_var.clone()), vec![], line, col),
                ],
                line,
                col,
            );
            pre_stmts.push(extract_call);

            // 3. Get inner variant string: _sw_inner_N_str := enum_to_str(_sw_inner_N)
            let inner_to_str = build_fcall(
                "enum_to_str",
                vec![Expr::new_explicit(NodeType::Identifier(inner_payload_var), vec![], line, col)],
                line,
                col,
            );
            let inner_str_decl = Declaration {
                name: inner_variant_var.clone(),
                value_type: str_to_value_type("Str"),
                is_mut: false,
                is_copy: false,
                is_own: false,
                default_value: None,
            };
            let inner_str_expr = Expr::new_explicit(
                NodeType::Declaration(inner_str_decl),
                vec![inner_to_str],
                line,
                col,
            );
            pre_stmts.push(inner_str_expr);

            inner_vars.insert(idx, inner_variant_var);
        }
    }

    Ok((pre_stmts, inner_vars))
}

/// Build the if/else chain for enum cases
fn build_enum_if_chain(
    context: &mut Context,
    switch_expr: &Expr,
    variant_var_name: &str,
    cases: &[(Expr, Expr)],
    default_body: Option<Expr>,
    enum_type_name: &str,
    nested_inner_vars: &std::collections::HashMap<usize, String>,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    // Build from end to beginning (reverse order) to construct the if/else chain
    // Start with the default case (else branch) or empty body
    let mut current_else = default_body.unwrap_or_else(|| {
        Expr::new_explicit(NodeType::Body, vec![], line, col)
    });

    // Process cases in reverse order, keeping track of case index for unique naming
    let total_cases = cases.len();
    for (rev_idx, (case_pattern, case_body)) in cases.iter().rev().enumerate() {
        // Calculate the original case index (forward order) for unique naming
        let case_idx = total_cases - 1 - rev_idx;
        let (condition, body_with_payload) = build_enum_case_condition_and_body(
            context,
            switch_expr,
            variant_var_name,
            case_pattern,
            case_body,
            enum_type_name,
            nested_inner_vars,
            case_idx,
            line,
            col,
        )?;

        // Build: if condition { body } else { current_else }
        current_else = Expr::new_explicit(
            NodeType::If,
            vec![condition, body_with_payload, current_else],
            line,
            col,
        );
    }

    Ok(current_else)
}

/// Build condition and body for a single enum case
fn build_enum_case_condition_and_body(
    context: &mut Context,
    switch_expr: &Expr,
    variant_var_name: &str,
    case_pattern: &Expr,
    case_body: &Expr,
    enum_type_name: &str,
    nested_inner_vars: &std::collections::HashMap<usize, String>,
    case_idx: usize,
    line: usize,
    col: usize,
) -> Result<(Expr, Expr), String> {
    let variant_var_expr = Expr::new_explicit(
        NodeType::Identifier(variant_var_name.to_string()),
        vec![],
        line,
        col,
    );

    match &case_pattern.node_type {
        NodeType::Pattern(pattern_info) => {
            // Enum pattern with payload binding: case Color.Green(is_olive)
            let variant_str = if pattern_info.variant_name.contains('.') {
                pattern_info.variant_name.clone()
            } else {
                // Shorthand form - prepend enum type
                format!("{}.{}", enum_type_name, pattern_info.variant_name)
            };

            // Condition: Str.eq(_switch_variant_N, "Type.Variant")
            let condition = build_qualified_fcall(
                "Str",
                "eq",
                vec![variant_var_expr, build_str_literal(&variant_str, line, col)],
                line,
                col,
            );

            // If binding var is "_", user doesn't care about payload - just use the body as-is
            if pattern_info.binding_var == "_" {
                return Ok((condition, case_body.clone()));
            }

            // Generate unique binding variable name to avoid conflicts with same-named
            // bindings in other cases (TIL has function-level scoping)
            let unique_binding_var = format!("_sw_{}_{}", pattern_info.binding_var, case_idx);

            // Body with payload extraction:
            // { mut _sw_binding_N := default; enum_get_payload(switch_expr, Type, _sw_binding_N); ...body with binding renamed... }
            let body_with_payload = build_payload_extraction_body(
                context,
                switch_expr,
                &unique_binding_var,
                enum_type_name,
                &pattern_info.variant_name,
                // Rename all references to the original binding var to use the unique name
                &rename_identifier_in_expr(case_body, &pattern_info.binding_var, &unique_binding_var),
                line,
                col,
            )?;

            Ok((condition, body_with_payload))
        }
        NodeType::Identifier(_) | NodeType::FCall(_) => {
            // Check for nested patterns like ValueType.TType(TTypeDef.TEnumDef)
            if let Some((outer_full, inner_full)) = get_nested_pattern_info(case_pattern) {
                // Nested pattern: build compound condition (outer AND inner)
                // The inner variant string was pre-computed in build_nested_pattern_pre_stmts

                // Outer check: Str.eq(_switch_variant, "ValueType.TType")
                let outer_condition = build_qualified_fcall(
                    "Str",
                    "eq",
                    vec![variant_var_expr.clone(), build_str_literal(&outer_full, line, col)],
                    line,
                    col,
                );

                // Inner check: use pre-computed inner variant string variable
                if let Some(inner_var_name) = nested_inner_vars.get(&case_idx) {
                    let inner_var_expr = Expr::new_explicit(
                        NodeType::Identifier(inner_var_name.clone()),
                        vec![],
                        line,
                        col,
                    );
                    let inner_condition = build_qualified_fcall(
                        "Str",
                        "eq",
                        vec![inner_var_expr, build_str_literal(&inner_full, line, col)],
                        line,
                        col,
                    );

                    // Compound condition: and(outer_check, inner_check)
                    let compound_condition = build_fcall(
                        "and",
                        vec![outer_condition, inner_condition],
                        line,
                        col,
                    );

                    return Ok((compound_condition, case_body.clone()));
                }

                // Fallback if inner var not found (shouldn't happen)
                return Ok((outer_condition, case_body.clone()));
            }

            // Simple enum variant without payload binding: case Color.Unknown
            let (type_name, variant_name) = get_case_variant_info(case_pattern);
            let full_variant = if !type_name.is_empty() {
                format!("{}.{}", type_name, variant_name)
            } else if !variant_name.is_empty() {
                format!("{}.{}", enum_type_name, variant_name)
            } else {
                // Not a clear enum pattern - fall back to direct comparison
                return build_non_enum_case_condition_and_body(switch_expr, case_pattern, case_body, false, line, col);
            };

            // Condition: Str.eq(_switch_variant_N, "Type.Variant")
            let condition = build_qualified_fcall(
                "Str",
                "eq",
                vec![variant_var_expr, build_str_literal(&full_variant, line, col)],
                line,
                col,
            );

            Ok((condition, case_body.clone()))
        }
        _ => {
            // Other case types - shouldn't happen for enum switch
            Err(case_pattern.lang_error(&context.path, "desugar", "Unexpected case pattern type in enum switch"))
        }
    }
}

/// Build body with payload extraction for enum patterns
fn build_payload_extraction_body(
    context: &Context,
    switch_expr: &Expr,
    binding_var: &str,
    enum_type_name: &str,
    variant_name: &str,
    original_body: &Expr,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    // If binding_var is "_", the user doesn't care about the payload - just return the original body
    if binding_var == "_" {
        return Ok(original_body.clone());
    }

    // Look up the enum definition to get the payload type for this variant
    // Extract variant name and type name from the full variant_name if needed
    let (actual_enum_type, variant_name_only) = if variant_name.contains('.') {
        let parts: Vec<&str> = variant_name.split('.').collect();
        if parts.len() >= 2 {
            (parts[0], parts[parts.len() - 1])
        } else {
            (enum_type_name, variant_name)
        }
    } else {
        (enum_type_name, variant_name)
    };

    // Try the extracted enum type first, then fall back to the provided one
    let mut payload_type = if let Some(enum_def) = context.scope_stack.lookup_enum(actual_enum_type) {
        enum_def.get(variant_name_only).cloned().flatten()
    } else if !enum_type_name.is_empty() && actual_enum_type != enum_type_name {
        // Try the original enum_type_name if different
        if let Some(enum_def) = context.scope_stack.lookup_enum(enum_type_name) {
            enum_def.get(variant_name_only).cloned().flatten()
        } else {
            None
        }
    } else {
        None
    };

    // If still not found, try to find the enum containing this variant (shorthand pattern support)
    // Use find_enum_with_variant_payload to prefer enums where the variant has a payload
    if payload_type.is_none() {
        if let Some(found_enum) = context.scope_stack.find_enum_with_variant_payload(variant_name_only) {
            if let Some(enum_def) = context.scope_stack.lookup_enum(&found_enum) {
                payload_type = enum_def.get(variant_name_only).cloned().flatten();
            }
        }
    }

    // If we couldn't find the payload type, use Dynamic as a fallback
    // This ensures the binding variable is always created
    let payload_type = payload_type.unwrap_or_else(|| ValueType::TCustom("Dynamic".to_string()));

    let payload_type_name = match &payload_type {
        ValueType::TCustom(name) => name.clone(),
        _ => return Ok(original_body.clone()),
    };

    // Build: mut binding := default_value
    let default_val = build_default_value(context, &payload_type, line, col);
    let binding_decl = Declaration {
        name: binding_var.to_string(),
        value_type: payload_type.clone(),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    let binding_decl_expr = Expr::new_explicit(
        NodeType::Declaration(binding_decl),
        vec![default_val],
        line,
        col,
    );

    // Build: enum_get_payload(switch_expr, PayloadType, binding)
    let type_expr = Expr::new_explicit(
        NodeType::Identifier(payload_type_name),
        vec![],
        line,
        col,
    );
    let binding_expr = Expr::new_explicit(
        NodeType::Identifier(binding_var.to_string()),
        vec![],
        line,
        col,
    );
    let get_payload_call = build_fcall(
        "enum_get_payload",
        vec![switch_expr.clone(), type_expr, binding_expr],
        line,
        col,
    );

    // Build body: { binding_decl; get_payload_call; ...original_body... }
    let mut body_params = vec![binding_decl_expr, get_payload_call];

    // Flatten the original body if it's a Body node
    match &original_body.node_type {
        NodeType::Body => {
            body_params.extend(original_body.params.clone());
        }
        _ => {
            body_params.push(original_body.clone());
        }
    }

    Ok(Expr::new_explicit(NodeType::Body, body_params, line, col))
}

/// Desugar a non-enum switch to if/else chain with eq() comparisons
fn desugar_non_enum_switch(
    context: &mut Context,
    switch_expr: &Expr,
    cases: &[(Expr, Expr)],
    default_body: Option<Expr>,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    // Check if the switch expression is an enum type (comparing enum values against variables)
    let switch_type_result = crate::rs::init::get_value_type(context, switch_expr);
    let is_enum_type = if let Ok(ValueType::TCustom(type_name)) = &switch_type_result {
        context.scope_stack.lookup_enum(type_name).is_some()
    } else {
        false
    };

    // Check if any case pattern identifier is definitely an enum type
    // This helps detect: switch token_type { case end_token: ... }
    // where end_token is a function parameter of type TokenType (enum)
    let has_enum_variable_pattern = cases.iter().any(|(p, _)| {
        if let NodeType::Identifier(_) = &p.node_type {
            // Try to get the type of this identifier
            if let Ok(ValueType::TCustom(type_name)) = crate::rs::init::get_value_type(context, p) {
                // It's an enum variable if we can look it up as an enum
                context.scope_stack.lookup_enum(&type_name).is_some()
            } else {
                false  // Can't determine - don't assume enum
            }
        } else {
            false
        }
    });

    // Use enum comparison only if we can POSITIVELY detect it's an enum type
    // Don't assume enum just because we can't prove it's a struct
    // This fixes: switch p { case _other: } where both are struct variables
    let use_enum_comparison = is_enum_type || has_enum_variable_pattern;

    // For non-enum switch, directly use switch_expr in each comparison.
    // This avoids type inference issues with temporary variables.
    // Note: If switch_expr has side effects, they will be evaluated multiple times.
    // This matches the behavior of the reference test_color_match_if implementation.
    build_non_enum_if_chain(switch_expr, cases, default_body, use_enum_comparison, line, col)
}

/// Build the if/else chain for non-enum cases
fn build_non_enum_if_chain(
    switch_expr: &Expr,
    cases: &[(Expr, Expr)],
    default_body: Option<Expr>,
    is_enum_type: bool,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    // Build from end to beginning
    let mut current_else = default_body.unwrap_or_else(|| {
        Expr::new_explicit(NodeType::Body, vec![], line, col)
    });

    for (case_pattern, case_body) in cases.iter().rev() {
        let (condition, body) = build_non_enum_case_condition_and_body(switch_expr, case_pattern, case_body, is_enum_type, line, col)?;

        current_else = Expr::new_explicit(
            NodeType::If,
            vec![condition, body, current_else],
            line,
            col,
        );
    }

    Ok(current_else)
}

/// Build condition and body for a single non-enum case
fn build_non_enum_case_condition_and_body(
    switch_expr: &Expr,
    case_pattern: &Expr,
    case_body: &Expr,
    is_enum_type: bool,
    line: usize,
    col: usize,
) -> Result<(Expr, Expr), String> {
    match &case_pattern.node_type {
        NodeType::Range => {
            // Range case: val.gteq(start) && val.lteq(end)
            if case_pattern.params.len() < 2 {
                return Err(case_pattern.error("", "desugar", "Range requires start and end values"));
            }
            let start = &case_pattern.params[0];
            let end = &case_pattern.params[1];

            // Build: gteq(switch_expr, start)
            let gteq_call = build_fcall("gteq", vec![switch_expr.clone(), start.clone()], line, col);

            // Build: lteq(switch_expr, end)
            let lteq_call = build_fcall("lteq", vec![switch_expr.clone(), end.clone()], line, col);

            // Build: and(gteq_result, lteq_result)
            let condition = build_fcall("and", vec![gteq_call, lteq_call], line, col);

            Ok((condition, case_body.clone()))
        }
        _ => {
            if is_enum_type {
                // Enum comparison (against variable): Str.eq(enum_to_str(switch_expr), enum_to_str(case_val))
                let switch_str = build_fcall("enum_to_str", vec![switch_expr.clone()], line, col);
                let case_str = build_fcall("enum_to_str", vec![case_pattern.clone()], line, col);
                let condition = build_qualified_fcall("Str", "eq", vec![switch_str, case_str], line, col);
                Ok((condition, case_body.clone()))
            } else {
                // Determine the appropriate eq method based on case pattern type
                let eq_type = match &case_pattern.node_type {
                    NodeType::LLiteral(Literal::Str(_)) => Some("Str"),
                    NodeType::LLiteral(Literal::Number(_)) => Some("I64"),
                    _ => None, // Unknown type - let UFCS resolve
                };

                let condition = if let Some(type_name) = eq_type {
                    build_qualified_fcall(type_name, "eq", vec![switch_expr.clone(), case_pattern.clone()], line, col)
                } else {
                    // Use unqualified eq and let UFCS resolve it
                    build_fcall("eq", vec![switch_expr.clone(), case_pattern.clone()], line, col)
                };
                Ok((condition, case_body.clone()))
            }
        }
    }
}

/// Desugarer phase entry point: Recursively desugar ForIn and Switch in the AST.
pub fn desugar_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        NodeType::ForIn(var_type_name) => {
            desugar_forin(context, e, var_type_name)
        },
        // Switch desugaring: switch expr { case val: body ... } -> if/else chain
        NodeType::Switch => {
            desugar_switch(context, e)
        },
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            // Bug #130 fix: Reset counter per-function for deterministic output
            let saved_counter = context.precomp_forin_counter;
            context.precomp_forin_counter = 0;

            // Push scope and register function parameters so get_value_type works for them
            // This helps distinguish enum parameters from struct variables in switch desugaring
            context.scope_stack.push(ScopeType::Function);
            for arg in &func_def.args {
                context.scope_stack.declare_symbol(arg.name.clone(), SymbolInfo {
                    value_type: arg.value_type.clone(),
                    is_mut: arg.is_mut,
                    is_copy: arg.is_copy,
                    is_own: arg.is_own,
                    is_comptime_const: false,
                });
            }

            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(desugar_expr(context, stmt)?);
            }

            let _ = context.scope_stack.pop();
            context.precomp_forin_counter = saved_counter;
            let new_func_def = SFuncDef {
                function_type: func_def.function_type.clone(),
                args: func_def.args.clone(),
                return_types: func_def.return_types.clone(),
                throw_types: func_def.throw_types.clone(),
                body: new_body,
                source_path: func_def.source_path.clone(),
            };
            Ok(Expr::new_clone(NodeType::FuncDef(new_func_def), e, e.params.clone()))
        },
        // Recurse into StructDef default values (which may contain function defs)
        NodeType::StructDef(struct_def) => {
            let mut new_default_values = std::collections::HashMap::new();
            for (name, value_expr) in &struct_def.default_values {
                new_default_values.insert(name.clone(), desugar_expr(context, value_expr)?);
            }
            let new_struct_def = SStructDef {
                members: struct_def.members.clone(),
                default_values: new_default_values,
            };
            Ok(Expr::new_clone(NodeType::StructDef(new_struct_def), e, e.params.clone()))
        },
        // For all other nodes, recurse into params
        _ => {
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let mut new_params = Vec::new();
                for p in &e.params {
                    new_params.push(desugar_expr(context, p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
            }
        }
    }
}
