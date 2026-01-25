// Desugarer phase: Desugars ForIn loops to while loops with get() calls,
// and Switch statements to if/else chains with enum_to_str/enum_get_payload.
// This phase runs after typer, before precomp.

use crate::rs::init::{Context, get_value_type};
use crate::rs::parser::{
    Expr, NodeType, ValueType, SStructDef, SFuncDef, Literal,
    Declaration, str_to_value_type, transform_continue_with_step, value_type_to_str,
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

/// Helper struct for variant info extraction (mirrors ccodegen.rs VariantInfo)
struct VariantInfo {
    type_name: String,
    variant_name: String,
}

/// Extract type name and variant name from a case expression
/// Handles: Identifier with params (Type.Variant), FCall (Type.Variant() or Type.Variant(arg))
fn get_case_variant_info(expr: &Expr) -> VariantInfo {
    match &expr.node_type {
        NodeType::FCall(_) => {
            // FCall for Type.Variant (without payload extraction)
            if !expr.params.is_empty() {
                if let NodeType::Identifier(type_name) = &expr.params[0].node_type {
                    if !expr.params[0].params.is_empty() {
                        if let NodeType::Identifier(variant_name) = &expr.params[0].params[0].node_type {
                            return VariantInfo {
                                type_name: type_name.clone(),
                                variant_name: variant_name.clone(),
                            };
                        }
                    }
                }
            }
            VariantInfo { type_name: String::new(), variant_name: String::new() }
        },
        NodeType::Identifier(name) => {
            // Identifier with nested params: Type.Variant
            if !expr.params.is_empty() {
                if let NodeType::Identifier(variant_name) = &expr.params[0].node_type {
                    return VariantInfo {
                        type_name: name.clone(),
                        variant_name: variant_name.clone(),
                    };
                }
            }
            // Plain identifier without nested params - NOT an enum variant pattern
            VariantInfo { type_name: String::new(), variant_name: String::new() }
        },
        _ => VariantInfo { type_name: String::new(), variant_name: String::new() },
    }
}

/// Parse a Pattern's variant_name string (e.g., "Color.Green") into type and variant parts
fn parse_pattern_variant_name(variant_name: &str) -> VariantInfo {
    if let Some(dot_pos) = variant_name.rfind('.') {
        let type_name = variant_name[..dot_pos].to_string();
        let var_name = variant_name[dot_pos + 1..].to_string();
        VariantInfo { type_name, variant_name: var_name }
    } else {
        // No dot - just variant name (shorthand syntax)
        VariantInfo { type_name: String::new(), variant_name: variant_name.to_string() }
    }
}

/// Search all enums in scope for a variant with the given name
/// Returns the payload type if found, None otherwise
/// This handles shorthand pattern syntax like "Identifier(x)" without "NodeType." prefix
fn find_payload_type_for_variant(context: &Context, variant_name: &str) -> Option<ValueType> {
    // Iterate through all stack frames looking for enums with this variant
    for frame in context.scope_stack.frames.iter().rev() {
        for enum_def in frame.enums.values() {
            if let Some(payload_type) = enum_def.get(variant_name).cloned().flatten() {
                return Some(payload_type);
            }
        }
    }
    None
}

/// Search all enums in scope to find the enum name that contains the given variant
/// Returns the enum type name if found, None otherwise
/// This handles shorthand pattern syntax like "Identifier" without "NodeType." prefix
fn find_enum_name_for_variant(context: &Context, variant_name: &str) -> Option<String> {
    // Iterate through all stack frames looking for enums with this variant
    for frame in context.scope_stack.frames.iter().rev() {
        for (enum_name, enum_def) in &frame.enums {
            if enum_def.contains_key(variant_name) {
                return Some(enum_name.clone());
            }
        }
    }
    None
}

/// Desugar Switch to if/else chains
/// For enum switches:
///   switch e { case Type.Variant(x): body }
///   becomes:
///   { _switch_variant := enum_to_str(e)
///     if Str.eq(_switch_variant, "Type.Variant") { mut x := default; enum_get_payload(e, PayloadType, x); body }
///     else { default_body } }
/// For non-enum switches:
///   switch val { case x: body case lo..hi: body2 }
///   becomes:
///   if val.eq(x) { body } else if val.gteq(lo) && val.lteq(hi) { body2 }
/// Note: Switches with nested enum patterns (e.g., Type.Variant(Inner.Variant)) are NOT desugared
fn desugar_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    if e.params.is_empty() {
        return Err(e.lang_error(&context.path, "desugar", "Switch requires expression"));
    }

    let line = e.line;
    let col = e.col;

    // Determine the type of the switch expression BEFORE desugaring
    // This is important because the typer has already processed the original expression
    let switch_type = get_value_type(context, &e.params[0]).ok();

    // Get the switch expression and desugar it
    let switch_expr = desugar_expr(context, &e.params[0])?;

    // Determine if this is an enum switch
    // An enum switch is one where:
    // 1. The switch expression type is an enum, OR
    // 2. Any case pattern looks like an enum constructor (Type.Variant)
    let mut is_enum_switch = false;

    // Check if switch expression type is an enum
    if let Some(ValueType::TCustom(type_name)) = &switch_type {
        if context.scope_stack.lookup_enum(type_name).is_some() {
            is_enum_switch = true;
        }
    }

    // Also check case patterns for enum constructors
    if !is_enum_switch {
        let mut i = 1;
        while i < e.params.len() {
            if i + 1 >= e.params.len() {
                break;
            }
            let case_pattern = &e.params[i];
            match &case_pattern.node_type {
                NodeType::Pattern(_) => {
                    is_enum_switch = true;
                },
                NodeType::Identifier(name) => {
                    if !case_pattern.params.is_empty() || name.contains('.') {
                        is_enum_switch = true;
                    }
                },
                NodeType::FCall(_) => {
                    // Only mark as enum switch if this FCall looks like an enum constructor
                    // e.g., Type.Variant(payload) - not just any function call like add(1, 2)
                    let info = get_case_variant_info(case_pattern);
                    if !info.variant_name.is_empty() {
                        is_enum_switch = true;
                    }
                },
                _ => {}
            }
            i += 2;
        }
    }

    // Generate unique variable names using counter
    let switch_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = &context.current_precomp_func;
    let variant_var = if !func_name.is_empty() {
        format!("_switch_variant_{}_{}", func_name, switch_id)
    } else {
        format!("_switch_variant_{}", switch_id)
    };

    // Build the outer body that contains all generated code
    let mut outer_body_stmts: Vec<Expr> = Vec::new();

    // For enum switches, declare: _switch_variant := enum_to_str(switch_expr)
    if is_enum_switch {
        let enum_to_str_call = Expr::new_explicit(
            NodeType::FCall(false),
            vec![
                Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                switch_expr.clone(),
            ],
            line,
            col,
        );
        let variant_decl = Declaration {
            name: variant_var.clone(),
            value_type: ValueType::TCustom("Str".to_string()),
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
        outer_body_stmts.push(variant_decl_expr);
    }

    // Collect case/body pairs and group nested enum patterns by outer variant
    let mut cases: Vec<(&Expr, &Expr)> = Vec::new();
    let mut default_body: Option<&Expr> = None;
    let mut i = 1;
    while i + 1 < e.params.len() {
        let case_pattern = &e.params[i];
        let case_body = &e.params[i + 1];
        if matches!(case_pattern.node_type, NodeType::DefaultCase) {
            default_body = Some(case_body);
        } else {
            cases.push((case_pattern, case_body));
        }
        i += 2;
    }

    // Group cases by outer variant for nested enum patterns
    // This ensures cases like TType(TEnumDef) and TType(TStructDef) share one outer if-block
    let grouped_cases = group_nested_enum_cases(&cases);

    // Build if/else chain from end to beginning
    // Start with the default case (or empty body if no default)
    let mut current_else: Option<Expr> = if let Some(body) = default_body {
        Some(desugar_expr(context, body)?)
    } else {
        None
    };

    // Process case groups in reverse order to build the if chain
    for group in grouped_cases.into_iter().rev() {
        if group.len() == 1 {
            // Single case - process normally
            let (case_pattern, case_body) = group[0];
            let condition = build_case_condition(
                context,
                case_pattern,
                &switch_expr,
                &variant_var,
                is_enum_switch,
                &switch_type,
                line,
                col,
            )?;

            let body_expr = build_case_body(
                context,
                case_pattern,
                case_body,
                &switch_expr,
                &switch_type,
                line,
                col,
            )?;

            let if_params = if let Some(else_expr) = current_else {
                vec![condition, body_expr, else_expr]
            } else {
                vec![condition, body_expr]
            };

            current_else = Some(Expr::new_explicit(NodeType::If, if_params, line, col));
        } else {
            // Multiple cases with same outer variant - generate grouped structure
            // if (outer == "X") { extract_payload; if (inner == "A") {...} else if (inner == "B") {...} }
            let (first_pattern, _) = group[0];
            let outer_info = get_case_variant_info(first_pattern);
            let full_outer_variant = format!("{}.{}", outer_info.type_name, outer_info.variant_name);
            let outer_condition = build_str_eq_call(&variant_var, &full_outer_variant, line, col);

            // Build the inner if-else chain for all cases in this group
            let grouped_body = build_grouped_inner_if_chain(
                context,
                &group,
                &switch_expr,
                &switch_type,
                line,
                col,
            )?;

            let if_params = if let Some(else_expr) = current_else {
                vec![outer_condition, grouped_body, else_expr]
            } else {
                vec![outer_condition, grouped_body]
            };

            current_else = Some(Expr::new_explicit(NodeType::If, if_params, line, col));
        }
    }

    // Add the if chain to outer body
    if let Some(if_chain) = current_else {
        outer_body_stmts.push(if_chain);
    }

    Ok(Expr::new_explicit(NodeType::Body, outer_body_stmts, line, col))
}

/// Get the outer variant key for a case pattern (for grouping nested enum patterns)
/// Returns Some((type_name, variant_name)) for nested enum patterns, None otherwise
fn get_nested_outer_key(case_pattern: &Expr) -> Option<(String, String)> {
    if let NodeType::FCall(_) = &case_pattern.node_type {
        if case_pattern.params.len() > 1 {
            let payload_expr = &case_pattern.params[1];
            let nested_info = get_case_variant_info(payload_expr);
            // Only consider it nested if the payload looks like an enum constructor
            if !nested_info.variant_name.is_empty() && !nested_info.type_name.is_empty() {
                let outer_info = get_case_variant_info(case_pattern);
                if !outer_info.variant_name.is_empty() {
                    return Some((outer_info.type_name.clone(), outer_info.variant_name.clone()));
                }
            }
        }
    }
    None
}

/// Group consecutive cases that have the same outer variant (for nested enum patterns)
/// Cases like TType(TEnumDef) and TType(TStructDef) will be grouped together
fn group_nested_enum_cases<'a>(cases: &[(&'a Expr, &'a Expr)]) -> Vec<Vec<(&'a Expr, &'a Expr)>> {
    let mut groups: Vec<Vec<(&'a Expr, &'a Expr)>> = Vec::new();

    for case in cases {
        let outer_key = get_nested_outer_key(case.0);

        // Check if we can add to the previous group
        let should_merge = if let (Some(ref key), Some(last_group)) = (&outer_key, groups.last()) {
            // Check if the last case in the previous group has the same outer key
            if let Some((last_pattern, _)) = last_group.last() {
                if let Some(last_key) = get_nested_outer_key(last_pattern) {
                    key.0 == last_key.0 && key.1 == last_key.1
                } else {
                    false
                }
            } else {
                false
            }
        } else {
            false
        };

        if should_merge {
            groups.last_mut().unwrap().push(*case);
        } else {
            groups.push(vec![*case]);
        }
    }

    groups
}

/// Build a grouped inner if-else chain for cases with the same outer variant
/// Generates: { extract_payload; if (inner == "A") {...} else if (inner == "B") {...} }
fn build_grouped_inner_if_chain(
    context: &mut Context,
    cases: &[(&Expr, &Expr)],
    switch_expr: &Expr,
    switch_type: &Option<ValueType>,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    let mut body_stmts: Vec<Expr> = Vec::new();

    // Get payload type from the first case
    let (first_pattern, _) = cases[0];
    let outer_info = get_case_variant_info(first_pattern);

    let outer_enum_name = if !outer_info.type_name.is_empty() {
        outer_info.type_name.clone()
    } else if let Some(ValueType::TCustom(name)) = switch_type {
        name.clone()
    } else {
        return Err(first_pattern.lang_error(&context.path, "desugar", "Cannot determine enum type for nested pattern"));
    };

    let payload_type_opt: Option<ValueType> = context.scope_stack.lookup_enum(&outer_enum_name)
        .and_then(|enum_def| enum_def.get(&outer_info.variant_name).cloned())
        .flatten();

    let payload_type = match payload_type_opt {
        Some(pt) => pt,
        None => return Err(first_pattern.lang_error(&context.path, "desugar", "Cannot determine payload type for nested pattern")),
    };

    // Generate unique name for extracted payload (shared by all cases in group)
    let func_name = &context.current_precomp_func;
    let payload_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let unique_payload_name = if !func_name.is_empty() {
        format!("_switch_payload_{}_{}", func_name, payload_id)
    } else {
        format!("_switch_payload_{}", payload_id)
    };

    // Declare payload variable: mut _switch_payload_N := PayloadType.default()
    let binding_decl = Declaration {
        name: unique_payload_name.clone(),
        value_type: payload_type.clone(),
        is_mut: true,
        is_copy: false,
        is_own: false,
        default_value: None,
    };
    let default_val = build_default_value(context, &payload_type, line, col);
    let binding_decl_expr = Expr::new_explicit(
        NodeType::Declaration(binding_decl),
        vec![default_val],
        line,
        col,
    );
    body_stmts.push(binding_decl_expr);

    // Build: enum_get_payload(switch_expr, PayloadType, _switch_payload_N)
    let payload_type_name = value_type_to_str(&payload_type);
    let get_payload_call = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
            switch_expr.clone(),
            Expr::new_explicit(NodeType::Identifier(payload_type_name), vec![], line, col),
            Expr::new_explicit(NodeType::Identifier(unique_payload_name.clone()), vec![], line, col),
        ],
        line,
        col,
    );
    body_stmts.push(get_payload_call);

    // Build inner if-else chain (process in reverse to build from end)
    let mut inner_else: Option<Expr> = None;

    for (case_pattern, case_body) in cases.iter().rev() {
        let payload_expr = &case_pattern.params[1];
        let nested_info = get_case_variant_info(payload_expr);

        // Build inner condition: enum_to_str(_switch_payload_N).eq("InnerType.InnerVariant")
        let inner_full_variant = format!("{}.{}", nested_info.type_name, nested_info.variant_name);
        let enum_to_str_call = Expr::new_explicit(
            NodeType::FCall(false),
            vec![
                Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                Expr::new_explicit(NodeType::Identifier(unique_payload_name.clone()), vec![], line, col),
            ],
            line,
            col,
        );
        let inner_condition = Expr::new_explicit(
            NodeType::FCall(false),
            vec![
                Expr::new_explicit(
                    NodeType::Identifier("Str".to_string()),
                    vec![Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col)],
                    line,
                    col,
                ),
                enum_to_str_call,
                Expr::new_explicit(NodeType::LLiteral(Literal::Str(inner_full_variant)), vec![], line, col),
            ],
            line,
            col,
        );

        // Desugar the case body
        let desugared_body = desugar_expr(context, case_body)?;

        // Build inner if (or if-else)
        let inner_if_params = if let Some(else_expr) = inner_else {
            vec![inner_condition, desugared_body, else_expr]
        } else {
            vec![inner_condition, desugared_body]
        };

        inner_else = Some(Expr::new_explicit(NodeType::If, inner_if_params, line, col));
    }

    // Add the inner if chain to body
    if let Some(inner_if) = inner_else {
        body_stmts.push(inner_if);
    }

    Ok(Expr::new_explicit(NodeType::Body, body_stmts, line, col))
}

/// Build the condition expression for a case
fn build_case_condition(
    context: &mut Context,
    case_pattern: &Expr,
    switch_expr: &Expr,
    variant_var: &str,
    is_enum_switch: bool,
    switch_type: &Option<ValueType>,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    match &case_pattern.node_type {
        NodeType::Pattern(pattern_info) => {
            // Enum pattern with payload binding: compare variant string
            let info = parse_pattern_variant_name(&pattern_info.variant_name);
            let full_variant = if !info.type_name.is_empty() {
                // Full type name provided in pattern (e.g., "NodeType.Identifier")
                format!("{}.{}", info.type_name, info.variant_name)
            } else if let Some(ValueType::TCustom(enum_name)) = switch_type {
                // Get type from switch expression type
                format!("{}.{}", enum_name, info.variant_name)
            } else if let Some(enum_name) = find_enum_name_for_variant(context, &info.variant_name) {
                // Search all enums for this variant (shorthand syntax)
                format!("{}.{}", enum_name, info.variant_name)
            } else {
                // Fallback to just variant name (will likely fail comparison)
                info.variant_name.clone()
            };

            // Build: Str.eq(_switch_variant, "Type.Variant")
            Ok(build_str_eq_call(variant_var, &full_variant, line, col))
        },
        NodeType::Range => {
            // Range case: val.gteq(start) && val.lteq(end)
            if case_pattern.params.len() < 2 {
                return Err(case_pattern.lang_error(&context.path, "desugar", "Range requires start and end values"));
            }

            let start_expr = desugar_expr(context, &case_pattern.params[0])?;
            let end_expr = desugar_expr(context, &case_pattern.params[1])?;

            // Build: switch_expr.gteq(start)
            let gteq_call = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(
                        NodeType::Identifier("gteq".to_string()),
                        vec![],
                        line,
                        col,
                    ),
                    switch_expr.clone(),
                    start_expr,
                ],
                line,
                col,
            );

            // Build: switch_expr.lteq(end)
            let lteq_call = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(
                        NodeType::Identifier("lteq".to_string()),
                        vec![],
                        line,
                        col,
                    ),
                    switch_expr.clone(),
                    end_expr,
                ],
                line,
                col,
            );

            // Build: gteq_call && lteq_call using and()
            Ok(Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(NodeType::Identifier("and".to_string()), vec![], line, col),
                    gteq_call,
                    lteq_call,
                ],
                line,
                col,
            ))
        },
        NodeType::Identifier(name) => {
            let info = get_case_variant_info(case_pattern);
            if !info.variant_name.is_empty() && is_enum_switch {
                // Enum variant without payload: compare variant string
                let full_variant = format!("{}.{}", info.type_name, info.variant_name);
                Ok(build_str_eq_call(variant_var, &full_variant, line, col))
            } else if is_enum_switch {
                // Enum switch with variable case value: compare using enum_to_str on both
                // Build: Str.eq(_switch_variant, enum_to_str(case_val))
                let desugared_case = desugar_expr(context, case_pattern)?;
                Ok(build_enum_var_eq_call(variant_var, &desugared_case, line, col))
            } else {
                // Check if BOTH switch expression and case value are enum variables
                // This handles the case: switch token_type { case end_token: ... }
                // where both are enum variables but is_enum_switch wasn't detected

                // First check if the switch expression type is an enum
                let switch_is_enum = match switch_type {
                    Some(ValueType::TCustom(type_name)) => {
                        context.scope_stack.lookup_enum(type_name).is_some()
                    },
                    _ => false,
                };

                // Then check if the case value is an enum variable
                let case_is_enum = context.scope_stack.lookup_symbol(name)
                    .map(|sym| {
                        if let ValueType::TCustom(type_name) = &sym.value_type {
                            context.scope_stack.lookup_enum(type_name).is_some()
                        } else {
                            false
                        }
                    })
                    .unwrap_or(false);

                if switch_is_enum && case_is_enum {
                    // Both are enum variables - use enum_to_str comparison
                    let desugared_case = desugar_expr(context, case_pattern)?;
                    // Generate: enum_to_str(switch_expr).eq(enum_to_str(case_val))
                    Ok(build_enum_to_str_eq_call(switch_expr, &desugared_case, line, col))
                } else {
                    // Non-enum switch or type mismatch: use val.eq(case_val)
                    let desugared_case = desugar_expr(context, case_pattern)?;
                    Ok(build_eq_call(switch_expr, &desugared_case, line, col))
                }
            }
        },
        NodeType::FCall(_) => {
            // FCall pattern: Type.Variant(payload) - enum variant with payload argument
            let info = get_case_variant_info(case_pattern);
            if !info.variant_name.is_empty() && is_enum_switch {
                // Build: Str.eq(_switch_variant, "Type.Variant")
                // Note: For nested enum patterns (e.g., Type.Variant(Inner.Variant)),
                // the inner check is handled in build_case_body which wraps the body
                // in an inner if-check
                let full_variant = format!("{}.{}", info.type_name, info.variant_name);
                Ok(build_str_eq_call(variant_var, &full_variant, line, col))
            } else {
                // Not an enum pattern - fall through to generic comparison
                let desugared_case = desugar_expr(context, case_pattern)?;
                Ok(build_eq_call(switch_expr, &desugared_case, line, col))
            }
        },
        NodeType::LLiteral(_) => {
            // Literal comparison: val.eq(literal)
            let desugared_case = desugar_expr(context, case_pattern)?;
            Ok(build_eq_call(switch_expr, &desugared_case, line, col))
        },
        _ => {
            // Generic case: val.eq(case_val)
            let desugared_case = desugar_expr(context, case_pattern)?;
            Ok(build_eq_call(switch_expr, &desugared_case, line, col))
        },
    }
}

/// Build a Str.eq call for comparing variant strings
fn build_str_eq_call(variant_var: &str, expected_variant: &str, line: usize, col: usize) -> Expr {
    // Build: Str.eq(_switch_variant, "Type.Variant")
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(
                NodeType::Identifier("Str".to_string()),
                vec![Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col)],
                line,
                col,
            ),
            Expr::new_explicit(NodeType::Identifier(variant_var.to_string()), vec![], line, col),
            Expr::new_explicit(NodeType::LLiteral(Literal::Str(expected_variant.to_string())), vec![], line, col),
        ],
        line,
        col,
    )
}

/// Build an eq call for comparing values (UFCS style: val.eq(other))
fn build_eq_call(switch_expr: &Expr, case_val: &Expr, line: usize, col: usize) -> Expr {
    // Build: eq(switch_expr, case_val) - UFCS will transform this
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
            switch_expr.clone(),
            case_val.clone(),
        ],
        line,
        col,
    )
}

/// Build an eq call comparing variant_var with enum_to_str(case_val)
/// Used when comparing enum values where case is a variable (not a constructor)
fn build_enum_var_eq_call(variant_var: &str, case_val: &Expr, line: usize, col: usize) -> Expr {
    // Build: Str.eq(_switch_variant, enum_to_str(case_val))
    let enum_to_str_case = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
            case_val.clone(),
        ],
        line,
        col,
    );
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(
                NodeType::Identifier("Str".to_string()),
                vec![Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col)],
                line,
                col,
            ),
            Expr::new_explicit(NodeType::Identifier(variant_var.to_string()), vec![], line, col),
            enum_to_str_case,
        ],
        line,
        col,
    )
}

/// Build an eq call comparing enum_to_str(switch_expr) with enum_to_str(case_val)
/// Used when switch expression type wasn't detected as enum but case value is an enum variable
fn build_enum_to_str_eq_call(switch_expr: &Expr, case_val: &Expr, line: usize, col: usize) -> Expr {
    // Build: Str.eq(enum_to_str(switch_expr), enum_to_str(case_val))
    let enum_to_str_switch = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
            switch_expr.clone(),
        ],
        line,
        col,
    );
    let enum_to_str_case = Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
            case_val.clone(),
        ],
        line,
        col,
    );
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(
                NodeType::Identifier("Str".to_string()),
                vec![Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col)],
                line,
                col,
            ),
            enum_to_str_switch,
            enum_to_str_case,
        ],
        line,
        col,
    )
}

/// Replace all Identifier nodes matching old_name with new_name in an expression tree
fn replace_identifier(expr: &Expr, old_name: &str, new_name: &str) -> Expr {
    match &expr.node_type {
        NodeType::Identifier(name) if name == old_name => {
            // Replace this identifier. Params are field/method names, NOT variable references,
            // so we DON'T recurse into them - they belong to a different namespace.
            // For example, s.clone() should become _payload_0.clone(), not _payload_0._payload_1()
            Expr::new_explicit(
                NodeType::Identifier(new_name.to_string()),
                expr.params.clone(),  // Keep original params unchanged
                expr.line,
                expr.col,
            )
        },
        NodeType::Identifier(_) => {
            // This Identifier doesn't match our target. Its params are field/method names,
            // NOT variable references, so we should NOT recurse into them.
            // For example, foo.name should stay as foo.name, not foo._payload_0 even if
            // "name" is a binding variable we're trying to replace elsewhere.
            expr.clone()
        },
        NodeType::Assignment(name) if name == old_name => {
            // Replace assignment target, recurse into value expression
            let new_params: Vec<Expr> = expr.params.iter()
                .map(|p| replace_identifier(p, old_name, new_name))
                .collect();
            Expr::new_explicit(
                NodeType::Assignment(new_name.to_string()),
                new_params,
                expr.line,
                expr.col,
            )
        },
        NodeType::Assignment(_) => {
            // Different assignment target, but still need to recurse into value expression
            let new_params: Vec<Expr> = expr.params.iter()
                .map(|p| replace_identifier(p, old_name, new_name))
                .collect();
            Expr::new_clone(expr.node_type.clone(), expr, new_params)
        },
        _ => {
            // Recurse into params for all other node types
            if expr.params.is_empty() {
                expr.clone()
            } else {
                let new_params: Vec<Expr> = expr.params.iter()
                    .map(|p| replace_identifier(p, old_name, new_name))
                    .collect();
                Expr::new_clone(expr.node_type.clone(), expr, new_params)
            }
        }
    }
}

/// Build the case body with payload extraction if needed
fn build_case_body(
    context: &mut Context,
    case_pattern: &Expr,
    case_body: &Expr,
    switch_expr: &Expr,
    switch_type: &Option<ValueType>,
    line: usize,
    col: usize,
) -> Result<Expr, String> {
    // Check if this is a pattern with payload binding
    if let NodeType::Pattern(pattern_info) = &case_pattern.node_type {
        // Get the payload type from the enum definition
        let info = parse_pattern_variant_name(&pattern_info.variant_name);

        // Try to get enum name from switch_type first, fallback to pattern's type name
        let enum_name = match switch_type {
            Some(ValueType::TCustom(name)) => name.clone(),
            _ => info.type_name.clone(),
        };

        // Search for the payload type
        let payload_type_opt: Option<ValueType> = if !enum_name.is_empty() {
            // Known enum type - look it up directly
            context.scope_stack.lookup_enum(&enum_name)
                .and_then(|enum_def| enum_def.get(&info.variant_name).cloned())
                .flatten()
        } else {
            // Unknown enum type (shorthand syntax like "Identifier(x)" without "NodeType." prefix)
            // Search all enums in scope for a variant with this name
            find_payload_type_for_variant(context, &info.variant_name)
        };

        if let Some(payload_type) = payload_type_opt {
            // Generate unique name for payload variable to avoid name collisions
            // with existing variables in scope (e.g., for-in loop variables)
            let func_name = &context.current_precomp_func;
            let payload_id = context.precomp_forin_counter;
            context.precomp_forin_counter += 1;
            let unique_payload_name = if !func_name.is_empty() {
                format!("_switch_payload_{}_{}", func_name, payload_id)
            } else {
                format!("_switch_payload_{}", payload_id)
            };

            // Build body with payload extraction:
            // { mut _unique := default; enum_get_payload(switch_var, PayloadType, _unique); ...body with renames... }
            let mut body_stmts: Vec<Expr> = Vec::new();

            // Declare payload variable with unique name
            let binding_decl = Declaration {
                name: unique_payload_name.clone(),
                value_type: payload_type.clone(),
                is_mut: true,
                is_copy: false,
                is_own: false,
                default_value: None,
            };
            let default_val = build_default_value(context, &payload_type, line, col);
            let binding_decl_expr = Expr::new_explicit(
                NodeType::Declaration(binding_decl),
                vec![default_val],
                line,
                col,
            );
            body_stmts.push(binding_decl_expr);

            // Build: enum_get_payload(switch_expr, PayloadType, _unique)
            let payload_type_name = value_type_to_str(&payload_type);
            let get_payload_call = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                    switch_expr.clone(),
                    Expr::new_explicit(NodeType::Identifier(payload_type_name), vec![], line, col),
                    Expr::new_explicit(NodeType::Identifier(unique_payload_name.clone()), vec![], line, col),
                ],
                line,
                col,
            );
            body_stmts.push(get_payload_call);

            // Desugar the body THEN rename references from binding_var to unique_payload_name
            let desugared_body = desugar_expr(context, case_body)?;
            let renamed_body = replace_identifier(&desugared_body, &pattern_info.binding_var, &unique_payload_name);

            // Add renamed body statements
            match &renamed_body.node_type {
                NodeType::Body => {
                    body_stmts.extend(renamed_body.params.clone());
                },
                _ => {
                    body_stmts.push(renamed_body);
                }
            }

            return Ok(Expr::new_explicit(NodeType::Body, body_stmts, line, col));
        }
    }

    // Handle FCall patterns with nested enum payloads (e.g., ValueType.TType(TTypeDef.TStructDef))
    // or binding variables (e.g., ValueType.TMulti(type_name))
    if let NodeType::FCall(_) = &case_pattern.node_type {
        if case_pattern.params.len() > 1 {
            let payload_expr = &case_pattern.params[1];
            let nested_info = get_case_variant_info(payload_expr);
            if !nested_info.variant_name.is_empty() && !nested_info.type_name.is_empty() {
                // This is a nested enum pattern - payload is an enum constructor, not a binding
                // The outer && inner condition is already handled in build_case_condition
                // Here we just need to extract the payload and run the body
                let outer_info = get_case_variant_info(case_pattern);

                // Get the outer enum's payload type for this variant
                let outer_enum_name = if !outer_info.type_name.is_empty() {
                    outer_info.type_name.clone()
                } else if let Some(ValueType::TCustom(name)) = switch_type {
                    name.clone()
                } else {
                    String::new()
                };

                let payload_type_opt: Option<ValueType> = if !outer_enum_name.is_empty() {
                    context.scope_stack.lookup_enum(&outer_enum_name)
                        .and_then(|enum_def| enum_def.get(&outer_info.variant_name).cloned())
                        .flatten()
                } else {
                    None
                };

                if let Some(payload_type) = payload_type_opt {
                    // Generate unique name for extracted payload
                    // This must match the name used in build_case_condition
                    let func_name = &context.current_precomp_func;
                    let payload_id = context.precomp_forin_counter;
                    context.precomp_forin_counter += 1;
                    let unique_payload_name = if !func_name.is_empty() {
                        format!("_switch_payload_{}_{}", func_name, payload_id)
                    } else {
                        format!("_switch_payload_{}", payload_id)
                    };

                    let mut body_stmts: Vec<Expr> = Vec::new();

                    // Declare payload variable: mut _switch_payload_N := PayloadType.default()
                    let binding_decl = Declaration {
                        name: unique_payload_name.clone(),
                        value_type: payload_type.clone(),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        default_value: None,
                    };
                    let default_val = build_default_value(context, &payload_type, line, col);
                    let binding_decl_expr = Expr::new_explicit(
                        NodeType::Declaration(binding_decl),
                        vec![default_val],
                        line,
                        col,
                    );
                    body_stmts.push(binding_decl_expr);

                    // Build: enum_get_payload(switch_expr, PayloadType, _switch_payload_N)
                    let payload_type_name = value_type_to_str(&payload_type);
                    let get_payload_call = Expr::new_explicit(
                        NodeType::FCall(false),
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                            switch_expr.clone(),
                            Expr::new_explicit(NodeType::Identifier(payload_type_name), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(unique_payload_name.clone()), vec![], line, col),
                        ],
                        line,
                        col,
                    );
                    body_stmts.push(get_payload_call);

                    // Build inner condition: enum_to_str(_switch_payload_N).eq("InnerType.InnerVariant")
                    let inner_full_variant = format!("{}.{}", nested_info.type_name, nested_info.variant_name);
                    let enum_to_str_call = Expr::new_explicit(
                        NodeType::FCall(false),
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(unique_payload_name.clone()), vec![], line, col),
                        ],
                        line,
                        col,
                    );
                    let inner_condition = Expr::new_explicit(
                        NodeType::FCall(false),
                        vec![
                            Expr::new_explicit(
                                NodeType::Identifier("Str".to_string()),
                                vec![Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col)],
                                line,
                                col,
                            ),
                            enum_to_str_call,
                            Expr::new_explicit(NodeType::LLiteral(Literal::Str(inner_full_variant)), vec![], line, col),
                        ],
                        line,
                        col,
                    );

                    // Desugar the actual body
                    let desugared_body = desugar_expr(context, case_body)?;

                    // Wrap body in inner if: if inner_condition { body }
                    let inner_if = Expr::new_explicit(
                        NodeType::If,
                        vec![inner_condition, desugared_body],
                        line,
                        col,
                    );
                    body_stmts.push(inner_if);

                    return Ok(Expr::new_explicit(NodeType::Body, body_stmts, line, col));
                }
            } else if let NodeType::Identifier(binding_var) = &payload_expr.node_type {
                // FCall pattern with simple binding variable: Type.Variant(binding_var)
                // This is NOT a nested enum pattern - we need to extract the payload into binding_var
                let outer_info = get_case_variant_info(case_pattern);

                // Get the outer enum's payload type for this variant
                let outer_enum_name = if !outer_info.type_name.is_empty() {
                    outer_info.type_name.clone()
                } else if let Some(ValueType::TCustom(name)) = switch_type {
                    name.clone()
                } else {
                    String::new()
                };

                let payload_type_opt: Option<ValueType> = if !outer_enum_name.is_empty() {
                    context.scope_stack.lookup_enum(&outer_enum_name)
                        .and_then(|enum_def| enum_def.get(&outer_info.variant_name).cloned())
                        .flatten()
                } else {
                    None
                };

                if let Some(payload_type) = payload_type_opt {
                    // Generate unique name for payload variable
                    let func_name = &context.current_precomp_func;
                    let payload_id = context.precomp_forin_counter;
                    context.precomp_forin_counter += 1;
                    let unique_payload_name = if !func_name.is_empty() {
                        format!("_switch_payload_{}_{}", func_name, payload_id)
                    } else {
                        format!("_switch_payload_{}", payload_id)
                    };

                    let mut body_stmts: Vec<Expr> = Vec::new();

                    // Declare payload variable: mut _switch_payload_N := PayloadType.default()
                    let binding_decl = Declaration {
                        name: unique_payload_name.clone(),
                        value_type: payload_type.clone(),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        default_value: None,
                    };
                    let default_val = build_default_value(context, &payload_type, line, col);
                    let binding_decl_expr = Expr::new_explicit(
                        NodeType::Declaration(binding_decl),
                        vec![default_val],
                        line,
                        col,
                    );
                    body_stmts.push(binding_decl_expr);

                    // Build: enum_get_payload(switch_expr, PayloadType, _switch_payload_N)
                    let payload_type_name = value_type_to_str(&payload_type);
                    let get_payload_call = Expr::new_explicit(
                        NodeType::FCall(false),
                        vec![
                            Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                            switch_expr.clone(),
                            Expr::new_explicit(NodeType::Identifier(payload_type_name), vec![], line, col),
                            Expr::new_explicit(NodeType::Identifier(unique_payload_name.clone()), vec![], line, col),
                        ],
                        line,
                        col,
                    );
                    body_stmts.push(get_payload_call);

                    // Desugar the body THEN rename references from binding_var to unique_payload_name
                    let desugared_body = desugar_expr(context, case_body)?;
                    let renamed_body = replace_identifier(&desugared_body, binding_var, &unique_payload_name);

                    // Add renamed body statements
                    match &renamed_body.node_type {
                        NodeType::Body => {
                            body_stmts.extend(renamed_body.params.clone());
                        },
                        _ => {
                            body_stmts.push(renamed_body);
                        }
                    }

                    return Ok(Expr::new_explicit(NodeType::Body, body_stmts, line, col));
                }
            }
        }
    }

    // No payload extraction needed - desugar and return as-is
    let desugared_body = desugar_expr(context, case_body)?;
    Ok(desugared_body)
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

/// Desugarer phase entry point: Recursively desugar ForIn loops in the AST.
pub fn desugar_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        NodeType::ForIn(var_type_name) => {
            desugar_forin(context, e, var_type_name)
        },
        // Switch desugaring: switch expr { case pattern: body } -> if/else chain
        NodeType::Switch => {
            desugar_switch(context, e)
        },
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            // Bug #130 fix: Reset counter per-function for deterministic output
            let saved_counter = context.precomp_forin_counter;
            context.precomp_forin_counter = 0;

            // Issue #110: Push function scope with parameters for switch desugaring
            // This allows lookup_symbol to find function parameters when determining
            // if a switch case value is an enum variable
            context.scope_stack.push(crate::rs::init::ScopeType::Function);
            for arg in &func_def.args {
                let symbol = crate::rs::init::SymbolInfo {
                    value_type: arg.value_type.clone(),
                    is_mut: arg.is_mut,
                    is_copy: arg.is_copy,
                    is_own: arg.is_own,
                    is_comptime_const: false,
                };
                context.scope_stack.declare_symbol(arg.name.clone(), symbol);
            }

            let mut new_body = Vec::new();
            for stmt in &func_def.body {
                new_body.push(desugar_expr(context, stmt)?);
            }

            // Pop the function scope
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
        // Track declarations in scope for switch type detection
        NodeType::Declaration(decl) => {
            // Add this declaration to scope so switch desugaring can look up types
            let symbol = crate::rs::init::SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut: decl.is_mut,
                is_copy: decl.is_copy,
                is_own: decl.is_own,
                is_comptime_const: false,
            };
            context.scope_stack.declare_symbol(decl.name.clone(), symbol);

            // Desugar the initialization expression (if any)
            if e.params.is_empty() {
                Ok(e.clone())
            } else {
                let mut new_params = Vec::new();
                for p in &e.params {
                    new_params.push(desugar_expr(context, p)?);
                }
                Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
            }
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
