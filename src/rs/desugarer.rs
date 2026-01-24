// Desugarer phase: Desugars ForIn loops and Switch statements.
// This phase runs after typer, before precomp.

use crate::rs::init::{Context, get_value_type, SymbolInfo, ScopeType};
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

/// Helper: Build an FCall node (non-throwing, desugared form)
fn build_fcall(func_name: &str, args: Vec<Expr>, line: usize, col: usize) -> Expr {
    let mut params = vec![Expr::new_explicit(
        NodeType::Identifier(func_name.to_string()),
        vec![],
        line,
        col,
    )];
    params.extend(args);
    Expr::new_explicit(NodeType::FCall(false), params, line, col)
}

/// Helper: Build an identifier node
fn build_id(name: &str, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::Identifier(name.to_string()), vec![], line, col)
}

/// Helper: Build a string literal node
fn build_str_literal(s: &str, line: usize, col: usize) -> Expr {
    Expr::new_explicit(NodeType::LLiteral(Literal::Str(s.to_string())), vec![], line, col)
}

/// Get full variant string for enum comparisons (e.g., "Color.Green")
fn get_variant_string(case_pattern: &Expr, switch_type: &Option<ValueType>) -> String {
    match &case_pattern.node_type {
        NodeType::Pattern(pattern_info) => {
            // If variant_name already contains dot, use it directly
            if pattern_info.variant_name.contains('.') {
                pattern_info.variant_name.clone()
            } else if let Some(ValueType::TCustom(type_name)) = switch_type {
                format!("{}.{}", type_name, pattern_info.variant_name)
            } else {
                pattern_info.variant_name.clone()
            }
        },
        NodeType::Identifier(name) => {
            if name.contains('.') {
                name.clone()
            } else if !case_pattern.params.is_empty() {
                // Nested identifier: Color.Green (Color has child Green)
                if let NodeType::Identifier(variant) = &case_pattern.params[0].node_type {
                    if let Some(ValueType::TCustom(type_name)) = switch_type {
                        format!("{}.{}", type_name, variant)
                    } else {
                        format!("{}.{}", name, variant)
                    }
                } else {
                    name.clone()
                }
            } else if let Some(ValueType::TCustom(type_name)) = switch_type {
                // Shorthand syntax: just "Green" becomes "Color.Green"
                format!("{}.{}", type_name, name)
            } else {
                name.clone()
            }
        },
        NodeType::FCall(_) => {
            // FCall like ValueType.TType(TTypeDef.TEnumDef)
            // params[0] is the Type.Variant identifier
            // params[1+] are payload arguments (for nested enum patterns)
            // NOTE: We only return the outer variant string here.
            // Nested payload matching is handled via compound conditions in the condition builder.
            if !case_pattern.params.is_empty() {
                get_variant_string(&case_pattern.params[0], switch_type)
            } else {
                String::new()
            }
        },
        _ => String::new(),
    }
}

/// Get nested payload variant info from an FCall case pattern.
/// For `case ValueType.TType(TTypeDef.TStructDef):`, this returns Some("TTypeDef.TStructDef").
/// Returns None if there's no nested payload pattern or if the payload is just a binding variable.
fn get_nested_enum_variant(case_pattern: &Expr) -> Option<String> {
    if let NodeType::FCall(_) = &case_pattern.node_type {
        if case_pattern.params.len() > 1 {
            let payload_arg = &case_pattern.params[1];
            // Only return a nested variant if the payload is a specific variant (Identifier with params
            // or another FCall), not a simple binding variable
            match &payload_arg.node_type {
                NodeType::Identifier(name) => {
                    // If it has params like TTypeDef.TStructDef, it's a specific variant
                    if !payload_arg.params.is_empty() || name.contains('.') {
                        return Some(get_variant_string(payload_arg, &None));
                    }
                    // Otherwise it's just a binding variable like `x` - no nested match needed
                    None
                },
                NodeType::FCall(_) => {
                    // Nested FCall is always a specific variant pattern
                    Some(get_variant_string(payload_arg, &None))
                },
                _ => None,
            }
        } else {
            None
        }
    } else {
        None
    }
}

/// Check if this switch is on an enum type
fn is_enum_switch(context: &Context, switch_type: &Option<ValueType>) -> bool {
    if let Some(ValueType::TCustom(type_name)) = switch_type {
        context.scope_stack.lookup_enum(type_name).is_some()
    } else {
        false
    }
}

/// Check if any case pattern in a switch has an FCall with a nested enum variant.
/// For example: case ValueType.TType(TTypeDef.TStructDef): ...
/// These need to be handled by ccodegen natively, not desugared to string comparisons.
fn has_nested_fcall_variant(case_patterns: &[&Expr]) -> bool {
    for case_pattern in case_patterns {
        if let NodeType::FCall(_) = &case_pattern.node_type {
            if get_nested_enum_variant(case_pattern).is_some() {
                return true;
            }
        }
    }
    false
}

/// Check if an identifier is a variable reference (as opposed to a literal enum variant).
/// A variable reference is an identifier that:
/// - Has no params (not a Type.Variant or foo.bar pattern)
/// - Is not a known enum variant name
/// - Is a declared variable in scope OR is lowercase (variable naming convention)
fn is_variable_case_pattern(context: &Context, case_pattern: &Expr, switch_type: &Option<ValueType>) -> bool {
    match &case_pattern.node_type {
        NodeType::Identifier(name) => {
            // If it has params (like Color.Green), it's an enum variant, not a variable
            if !case_pattern.params.is_empty() {
                return false;
            }
            // If it contains a dot, it's a qualified name like TokenType.If
            if name.contains('.') {
                return false;
            }
            // Check if it's a known enum variant of the switch type
            if let Some(ValueType::TCustom(type_name)) = switch_type {
                if let Some(enum_def) = context.scope_stack.lookup_enum(type_name) {
                    for v in &enum_def.variants {
                        if &v.name == name {
                            // It's a known variant name - not a variable
                            return false;
                        }
                    }
                }
            }
            // Check if it's a declared variable in scope
            if context.scope_stack.lookup_var(name).is_some() {
                return true;
            }
            // Fallback: if it starts with lowercase, likely a variable
            // (enum variants typically start uppercase like TokenType.If)
            name.chars().next().map(|c| c.is_lowercase()).unwrap_or(false)
        },
        _ => false,
    }
}

/// Detect switch type from case patterns when get_value_type fails
/// Returns (is_enum, type_name) if detectable from patterns
fn detect_switch_type_from_patterns(context: &Context, cases: &[&Expr]) -> (bool, Option<String>) {
    for case_pattern in cases {
        match &case_pattern.node_type {
            NodeType::Pattern(pattern_info) => {
                // Pattern like "Color.Green(x)" or "Green(x)" (shorthand)
                // Patterns are only used with enums, so this is definitely an enum switch
                if let Some(dot_pos) = pattern_info.variant_name.find('.') {
                    let type_name = pattern_info.variant_name[..dot_pos].to_string();
                    if context.scope_stack.lookup_enum(&type_name).is_some() {
                        return (true, Some(type_name));
                    }
                }
                // Shorthand pattern without type prefix - still an enum switch but type unknown
                return (true, None);
            },
            NodeType::Identifier(name) => {
                // Could be "Color.Green" or nested identifier
                if let Some(dot_pos) = name.find('.') {
                    let type_name = name[..dot_pos].to_string();
                    if context.scope_stack.lookup_enum(&type_name).is_some() {
                        return (true, Some(type_name));
                    }
                } else if !case_pattern.params.is_empty() {
                    // Nested identifier: Color.Green (Color has child Green)
                    if context.scope_stack.lookup_enum(name).is_some() {
                        return (true, Some(name.clone()));
                    }
                }
            },
            NodeType::FCall(_) => {
                // FCall like Color.Green(x) - first param is identifier
                if !case_pattern.params.is_empty() {
                    if let NodeType::Identifier(name) = &case_pattern.params[0].node_type {
                        if let Some(dot_pos) = name.find('.') {
                            let type_name = name[..dot_pos].to_string();
                            if context.scope_stack.lookup_enum(&type_name).is_some() {
                                return (true, Some(type_name));
                            }
                        } else if !case_pattern.params[0].params.is_empty() {
                            // Nested: identifier with child
                            if context.scope_stack.lookup_enum(name).is_some() {
                                return (true, Some(name.clone()));
                            }
                        }
                    }
                }
            },
            NodeType::LLiteral(lit) => {
                // Literal cases indicate non-enum switch
                match lit {
                    Literal::Str(_) => return (false, Some("Str".to_string())),
                    Literal::Number(_) => return (false, Some("I64".to_string())),
                    Literal::List(_) => {} // List literals - type unknown
                }
            },
            _ => {}
        }
    }
    (false, None)
}

/// Get the payload type from an enum variant
fn get_payload_type(context: &Context, enum_name: &str, variant_name: &str) -> Option<ValueType> {
    if let Some(enum_def) = context.scope_stack.lookup_enum(enum_name) {
        for v in &enum_def.variants {
            if v.name == variant_name {
                return v.payload_type.clone();
            }
        }
    }
    None
}

/// Rename an identifier throughout an expression tree.
/// Used to replace user-visible binding variable names with unique internal names.
/// Note: Only renames VARIABLE references, not struct field names.
/// In TIL, `foo.bar` is Identifier("foo") with params [Identifier("bar")].
/// The params of an Identifier are field/method names, not variable references,
/// so we should NOT recurse into them when renaming.
fn rename_identifier(e: &Expr, old_name: &str, new_name: &str) -> Expr {
    match &e.node_type {
        NodeType::Identifier(name) if name == old_name => {
            // Variable reference matches - rename it
            // DO NOT recurse into params - those are field names, not variables
            Expr::new_explicit(
                NodeType::Identifier(new_name.to_string()),
                e.params.clone(),  // Keep field chain unchanged
                e.line,
                e.col,
            )
        },
        NodeType::Identifier(_) => {
            // Different identifier - don't rename, but DO NOT recurse into params
            // (params are field names, not variable references)
            e.clone()
        },
        NodeType::Assignment(name) if name == old_name => {
            // Assignment target matches
            let new_params: Vec<Expr> = e.params.iter()
                .map(|p| rename_identifier(p, old_name, new_name))
                .collect();
            Expr::new_explicit(
                NodeType::Assignment(new_name.to_string()),
                new_params,
                e.line,
                e.col,
            )
        },
        _ => {
            // Recurse into params
            if e.params.is_empty() {
                e.clone()
            } else {
                let new_params: Vec<Expr> = e.params.iter()
                    .map(|p| rename_identifier(p, old_name, new_name))
                    .collect();
                Expr::new_clone(e.node_type.clone(), e, new_params)
            }
        }
    }
}

/// Desugar Switch to if/else chains
/// For enum switches: use enum_to_str + Str.eq for comparison
/// For non-enum switches: use val.eq(case_val) calls
fn desugar_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Switch: params[0] = switch expression
    // params[1..] = alternating (case_pattern, body) pairs
    if e.params.is_empty() {
        return Err(e.lang_error(&context.path, "desugar", "Switch requires expression"));
    }

    let line = e.line;
    let col = e.col;

    // Get the switch expression and desugar it recursively
    let switch_expr = desugar_expr(context, &e.params[0])?;
    // Collect case patterns first (we need them to detect type if get_value_type fails)
    let mut case_patterns: Vec<&Expr> = Vec::new();
    let mut i = 1;
    while i + 1 < e.params.len() {
        let case_pattern = &e.params[i];
        if !matches!(case_pattern.node_type, NodeType::DefaultCase) {
            case_patterns.push(case_pattern);
        }
        i += 2;
    }

    // Determine switch type - first try get_value_type, then fall back to pattern detection
    let mut switch_type = get_value_type(context, &switch_expr).ok();
    let mut is_enum = is_enum_switch(context, &switch_type);

    // If get_value_type failed, try detecting from case patterns
    if switch_type.is_none() {
        let (detected_is_enum, detected_type_name) = detect_switch_type_from_patterns(context, &case_patterns);
        is_enum = detected_is_enum;
        if let Some(type_name) = detected_type_name {
            switch_type = Some(ValueType::TCustom(type_name));
        }
    }

    // If switch has FCall patterns with nested enum variants, pass through to ccodegen
    // without desugaring to if/else. ccodegen handles these natively with tag + payload comparison.
    if is_enum && has_nested_fcall_variant(&case_patterns) {
        // Desugar children (switch expr and case bodies) but keep switch structure
        let mut new_params = vec![switch_expr];
        let mut i = 1;
        while i + 1 < e.params.len() {
            // Case pattern - pass through as-is (don't desugar enum patterns)
            new_params.push(e.params[i].clone());
            // Case body - desugar recursively
            let desugared_body = desugar_expr(context, &e.params[i + 1])?;
            new_params.push(desugared_body);
            i += 2;
        }
        return Ok(Expr::new_explicit(NodeType::Switch, new_params, line, col));
    }

    // Generate unique temp var names for switch expression
    let forin_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = &context.current_precomp_func;
    let base_name = if !func_name.is_empty() {
        format!("_switch_{}_{}", func_name, forin_id)
    } else {
        format!("_switch_{}", forin_id)
    };

    // For enum switches, we need TWO temp variables:
    // 1. _switch_enum_N: holds the original enum value (for enum_get_payload)
    // 2. _switch_str_N: holds enum_to_str() result (for string comparison)
    // This avoids passing complex expressions (like Identifier("_") patterns) directly to enum_to_str
    //
    // For non-enum switches, we only need one temp variable

    let mut decl_stmts: Vec<Expr> = Vec::new();
    let switch_var_name: String;  // The variable name used for comparisons
    let switch_enum_var_name: String;  // The variable name used for enum_get_payload (only for enums)

    if is_enum {
        // Enum switch: create two temp variables
        switch_enum_var_name = format!("{}_enum", base_name);
        switch_var_name = format!("{}_str", base_name);

        // 1. _switch_enum := switch_expr (holds the enum value)
        let enum_var_type = if let Some(ref t) = switch_type {
            t.clone()
        } else {
            return Err(e.lang_error(&context.path, "desugar", "Cannot determine switch expression type"));
        };
        let enum_var_decl = Declaration {
            name: switch_enum_var_name.clone(),
            value_type: enum_var_type,
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let enum_var_decl_expr = Expr::new_explicit(
            NodeType::Declaration(enum_var_decl),
            vec![switch_expr.clone()],
            line,
            col,
        );
        decl_stmts.push(enum_var_decl_expr);

        // 2. _switch_str := enum_to_str(_switch_enum) (holds the string for comparison)
        let str_var_decl = Declaration {
            name: switch_var_name.clone(),
            value_type: str_to_value_type("Str"),
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let str_var_init = build_fcall("enum_to_str", vec![build_id(&switch_enum_var_name, line, col)], line, col);
        let str_var_decl_expr = Expr::new_explicit(
            NodeType::Declaration(str_var_decl),
            vec![str_var_init],
            line,
            col,
        );
        decl_stmts.push(str_var_decl_expr);
    } else {
        // Non-enum switch: create one temp variable
        switch_var_name = base_name.clone();
        switch_enum_var_name = String::new(); // Not used for non-enum

        let switch_var_type = if let Some(ref t) = switch_type {
            t.clone()
        } else {
            return Err(e.lang_error(&context.path, "desugar", "Cannot determine switch expression type"));
        };
        let switch_var_decl = Declaration {
            name: switch_var_name.clone(),
            value_type: switch_var_type,
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let switch_var_decl_expr = Expr::new_explicit(
            NodeType::Declaration(switch_var_decl),
            vec![switch_expr.clone()],
            line,
            col,
        );
        decl_stmts.push(switch_var_decl_expr);
    }

    // Collect cases: (case_pattern, case_body) pairs
    // Default case (if present) is guaranteed to be last by parser
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

    // Build if/else chain from the end backwards
    // Start with the default case (or empty body if no default)
    let mut else_branch: Option<Expr> = if let Some(default_b) = default_body {
        Some(desugar_expr(context, default_b)?)
    } else {
        None
    };

    // Process cases in reverse order to build nested if/else
    // Use enumerate to get case index for unique binding variable names
    for (case_index, (case_pattern, case_body)) in cases.into_iter().rev().enumerate() {
        // Build the condition based on case type
        let condition = match &case_pattern.node_type {
            NodeType::Pattern(_pattern_info) => {
                // Enum pattern with payload binding: compare variant string
                let variant_str = get_variant_string(case_pattern, &switch_type);
                // Str.eq(switch_var, "EnumName.Variant")
                build_fcall(
                    "eq",
                    vec![
                        build_id(&switch_var_name, line, col),
                        build_str_literal(&variant_str, line, col),
                    ],
                    line,
                    col,
                )
            },
            NodeType::Range => {
                // Range: switch_val.gteq(start).and(switch_val.lteq(end))
                if case_pattern.params.len() < 2 {
                    return Err(e.lang_error(&context.path, "desugar", "Range requires start and end values"));
                }
                let start = desugar_expr(context, &case_pattern.params[0])?;
                let end = desugar_expr(context, &case_pattern.params[1])?;
                // gteq(switch_var, start)
                let gteq_call = build_fcall(
                    "gteq",
                    vec![build_id(&switch_var_name, line, col), start],
                    line,
                    col,
                );
                // lteq(switch_var, end)
                let lteq_call = build_fcall(
                    "lteq",
                    vec![build_id(&switch_var_name, line, col), end],
                    line,
                    col,
                );
                // and(gteq_result, lteq_result)
                build_fcall("and", vec![gteq_call, lteq_call], line, col)
            },
            NodeType::Identifier(_) | NodeType::FCall(_) | NodeType::LLiteral(_) => {
                if is_enum {
                    // Check if this is a variable reference (dynamic case) or literal variant
                    if is_variable_case_pattern(context, case_pattern, &switch_type) {
                        // Variable case: compare with enum_to_str(var)
                        // e.g., `case expected:` where expected is a variable holding an enum value
                        let case_val = desugar_expr(context, case_pattern)?;
                        // eq(_switch_str, enum_to_str(var))
                        build_fcall(
                            "eq",
                            vec![
                                build_id(&switch_var_name, line, col),
                                build_fcall("enum_to_str", vec![case_val], line, col),
                            ],
                            line,
                            col,
                        )
                    } else {
                        // Literal enum variant: compare with string literal
                        // Note: Nested FCall variants are handled by passing through to ccodegen,
                        // so we only need simple string comparison here.
                        let variant_str = get_variant_string(case_pattern, &switch_type);
                        build_fcall(
                            "eq",
                            vec![
                                build_id(&switch_var_name, line, col),
                                build_str_literal(&variant_str, line, col),
                            ],
                            line,
                            col,
                        )
                    }
                } else {
                    // Non-enum: use eq(switch_var, case_val)
                    let case_val = desugar_expr(context, case_pattern)?;
                    build_fcall(
                        "eq",
                        vec![build_id(&switch_var_name, line, col), case_val],
                        line,
                        col,
                    )
                }
            },
            _ => {
                // Generic case: use eq
                let case_val = desugar_expr(context, case_pattern)?;
                build_fcall(
                    "eq",
                    vec![build_id(&switch_var_name, line, col), case_val],
                    line,
                    col,
                )
            }
        };

        // Build case body, possibly with payload extraction for patterns
        let body_stmts = match &case_pattern.node_type {
            NodeType::Pattern(pattern_info) => {
                // Need to extract payload before body
                let mut stmts: Vec<Expr> = Vec::new();

                // Get payload type
                let enum_name = if let Some(ValueType::TCustom(name)) = &switch_type {
                    name.clone()
                } else {
                    return Err(e.lang_error(&context.path, "desugar", "Pattern in non-enum switch"));
                };

                // Extract just the variant name (after the dot)
                let variant_name = if let Some(dot_pos) = pattern_info.variant_name.rfind('.') {
                    pattern_info.variant_name[dot_pos + 1..].to_string()
                } else {
                    pattern_info.variant_name.clone()
                };

                if let Some(payload_type) = get_payload_type(context, &enum_name, &variant_name) {
                    // Generate unique binding variable name to avoid conflicts when multiple
                    // cases use the same binding name with different types (e.g., case Foo(val), case Bar(val))
                    let unique_binding_name = format!("{}_payload_{}", base_name, case_index);

                    // Build: mut _unique_binding := default_value
                    let binding_decl = Declaration {
                        name: unique_binding_name.clone(),
                        value_type: payload_type.clone(),
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        default_value: None,
                    };
                    let default_val = build_default_value(context, &payload_type, line, col);
                    let decl_expr = Expr::new_explicit(
                        NodeType::Declaration(binding_decl),
                        vec![default_val],
                        line,
                        col,
                    );
                    stmts.push(decl_expr);

                    // Register binding variable in scope for nested switch type detection
                    // Register BOTH the unique name AND the original name (for lookups in body)
                    // The original name is needed because nested code (like inner switches) will
                    // reference the original name during desugaring, before renaming happens.
                    context.scope_stack.declare_symbol(
                        unique_binding_name.clone(),
                        SymbolInfo {
                            value_type: payload_type.clone(),
                            is_mut: true,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        }
                    );
                    context.scope_stack.declare_symbol(
                        pattern_info.binding_var.clone(),
                        SymbolInfo {
                            value_type: payload_type.clone(),
                            is_mut: true,
                            is_copy: false,
                            is_own: false,
                            is_comptime_const: false,
                        }
                    );

                    // Build: enum_get_payload(_switch_enum, PayloadType, unique_binding_var)
                    // Use the temp variable that holds the enum value, not the original expression
                    let type_id = if let ValueType::TCustom(type_name) = &payload_type {
                        build_id(type_name, line, col)
                    } else {
                        build_id("I64", line, col) // fallback
                    };
                    let payload_call = build_fcall(
                        "enum_get_payload",
                        vec![
                            build_id(&switch_enum_var_name, line, col),
                            type_id,
                            build_id(&unique_binding_name, line, col),
                        ],
                        line,
                        col,
                    );
                    stmts.push(payload_call);

                    // Desugar and rename: Replace original binding var name with unique name in body
                    let desugared_body = desugar_expr(context, case_body)?;
                    let renamed_body = rename_identifier(&desugared_body, &pattern_info.binding_var, &unique_binding_name);
                    match renamed_body.node_type {
                        NodeType::Body => stmts.extend(renamed_body.params),
                        _ => stmts.push(renamed_body),
                    }
                } else {
                    // No payload - just add body statements
                    let desugared_body = desugar_expr(context, case_body)?;
                    match desugared_body.node_type {
                        NodeType::Body => stmts.extend(desugared_body.params),
                        _ => stmts.push(desugared_body),
                    }
                }

                Expr::new_explicit(NodeType::Body, stmts, line, col)
            },
            _ => {
                // Regular case body
                desugar_expr(context, case_body)?
            }
        };

        // Build if node
        let if_expr = if let Some(else_body) = else_branch {
            // if cond { body } else { else_body }
            Expr::new_explicit(
                NodeType::If,
                vec![condition, body_stmts, else_body],
                line,
                col,
            )
        } else {
            // if cond { body }
            Expr::new_explicit(NodeType::If, vec![condition, body_stmts], line, col)
        };

        else_branch = Some(if_expr);
    }

    // Wrap in a body with the switch variable declaration(s)
    let mut result_stmts = decl_stmts;
    if let Some(if_chain) = else_branch {
        result_stmts.push(if_chain);
    }

    Ok(Expr::new_explicit(NodeType::Body, result_stmts, line, col))
}

/// Desugarer phase entry point: Recursively desugar ForIn loops and Switch statements in the AST.
pub fn desugar_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        NodeType::ForIn(var_type_name) => {
            desugar_forin(context, e, var_type_name)
        },
        // Switch desugaring: switch expr { cases } -> if/else chain
        NodeType::Switch => {
            desugar_switch(context, e)
        },
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            // Bug #130 fix: Reset counter per-function for deterministic output
            let saved_counter = context.precomp_forin_counter;
            context.precomp_forin_counter = 0;

            // Push a function scope and declare args (like precomp does)
            // This enables get_value_type to work inside the function body
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
        // Handle Declaration - register variable in scope for later lookups
        NodeType::Declaration(decl) => {
            // First, desugar the value expression
            let new_params = if !e.params.is_empty() {
                let mut new_params = Vec::new();
                for p in &e.params {
                    new_params.push(desugar_expr(context, p)?);
                }
                new_params
            } else {
                Vec::new()
            };

            // Register the variable in scope (for switch type detection)
            context.scope_stack.declare_symbol(decl.name.clone(), SymbolInfo {
                value_type: decl.value_type.clone(),
                is_mut: decl.is_mut,
                is_copy: decl.is_copy,
                is_own: decl.is_own,
                is_comptime_const: false,
            });

            Ok(Expr::new_clone(e.node_type.clone(), e, new_params))
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
