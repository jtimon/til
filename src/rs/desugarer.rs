// Desugarer phase: Desugars ForIn loops to while loops with get() calls,
// and Switch statements to if/else chains.
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

    // Build: catch (_err_forin_N: IndexOutOfBoundsError) { panic(loc(), _err_forin_N.msg) }
    // Bug #97: Use unique name to avoid shadowing loop variable if it's also named "err"
    // Catch structure: params[0]=error type identifier, params[1]=error var name, params[2]=body
    let catch_err_var = format!("_err_forin_{}", forin_id);
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
                NodeType::Identifier(catch_err_var.clone()),
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
            Expr::new_explicit(NodeType::Identifier(catch_err_var), vec![], e.line, e.col),
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

/// Helper struct for variant info extraction
struct VariantInfo {
    type_name: String,
    variant_name: String,
}

/// Parse variant name from Pattern's variant_name field (e.g., "Color.Green" -> ("Color", "Green"))
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

/// Extract variant info from a case pattern expression (Identifier with nested params)
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

/// Get the payload type from an enum definition for a given variant
fn get_payload_type_for_variant(context: &Context, enum_name: &str, variant_name: &str) -> Option<ValueType> {
    if let Some(enum_def) = context.scope_stack.lookup_enum(enum_name) {
        for v in &enum_def.variants {
            if v.name == variant_name {
                return v.payload_type.clone();
            }
        }
    }
    None
}

/// Check if an expression is a field access on a throwing FCall
/// Returns (needs_split, base_fcall, field_names) if it needs splitting
/// This is needed to work around ccodegen's inability to handle throwing calls
/// with field access in declaration initializers (Bug #143 workaround)
fn check_throwing_field_access(expr: &Expr) -> (bool, Option<Expr>, Vec<String>) {
    // Check if this is an Identifier (field access) with params
    if let NodeType::Identifier(name) = &expr.node_type {
        if !expr.params.is_empty() {
            // Handle UFCS form: Identifier("_") with params[0] = FCall, params[1..] = fields
            // This is what typer produces for expr.field when expr is a call result
            if name == "_" {
                if let NodeType::FCall(throws) = &expr.params[0].node_type {
                    if *throws {
                        // UFCS field access on a throwing FCall - needs splitting
                        // Field names are in params[1..]
                        let mut field_names = Vec::new();
                        for i in 1..expr.params.len() {
                            if let NodeType::Identifier(field_name) = &expr.params[i].node_type {
                                field_names.push(field_name.clone());
                            }
                        }
                        if !field_names.is_empty() {
                            return (true, Some(expr.params[0].clone()), field_names);
                        }
                    }
                }
            }

            // Non-UFCS form: Identifier(field_name) with params[0] = base expression
            // Check if the first param is a throwing FCall
            if let NodeType::FCall(throws) = &expr.params[0].node_type {
                if *throws {
                    // Field access on a throwing FCall - needs splitting
                    return (true, Some(expr.params[0].clone()), vec![name.clone()]);
                }
            }
            // Check if the first param is ANOTHER field access on a throwing FCall (nested)
            let (needs_split, base_fcall, mut field_names) = check_throwing_field_access(&expr.params[0]);
            if needs_split {
                field_names.push(name.clone());
                return (true, base_fcall, field_names);
            }
        }
    }
    (false, None, vec![])
}

/// Rename all occurrences of an identifier in an expression tree
/// Used to rename payload binding variables to unique names to avoid conflicts
/// Stops at shadowing constructs (inner Patterns, Declarations with same name)
/// IMPORTANT: Does NOT rename inside an Identifier's params - those are field names, not variable refs
fn rename_identifier_in_expr(e: &Expr, old_name: &str, new_name: &str) -> Expr {
    match &e.node_type {
        NodeType::Identifier(name) if name == old_name => {
            // Identifier reference - rename it but DON'T recurse into params
            // Params of an Identifier are field names (e.g., x.field) or method calls,
            // NOT variable references. Renaming them would break field access.
            Expr::new_clone(
                NodeType::Identifier(new_name.to_string()),
                e,
                e.params.clone(), // Keep params unchanged - they're field names
            )
        },
        NodeType::Identifier(_) => {
            // Different identifier - recurse into params to find nested expressions
            // But be careful: direct children that are Identifiers are likely field names
            // We need to check if params contain expressions that use the old_name
            if e.params.is_empty() {
                e.clone()
            } else {
                // For field access like x.field.subfield, params are [Identifier("field"), Identifier("subfield")]
                // These are field names, not variable references, so we should NOT rename them
                // But params could also contain FCall for method calls like x.method(arg)
                // The FCall's arguments COULD contain variable references
                let new_params: Vec<Expr> = e.params.iter()
                    .map(|p| {
                        // Only recurse into non-Identifier params (like FCall, etc.)
                        // Direct Identifier children of an Identifier are field names
                        if matches!(p.node_type, NodeType::Identifier(_)) {
                            p.clone()
                        } else {
                            rename_identifier_in_expr(p, old_name, new_name)
                        }
                    })
                    .collect();
                Expr::new_clone(e.node_type.clone(), e, new_params)
            }
        },
        NodeType::Assignment(name) if name == old_name => {
            // Assignment to the variable - rename it
            let new_params: Vec<Expr> = e.params.iter()
                .map(|p| rename_identifier_in_expr(p, old_name, new_name))
                .collect();
            Expr::new_clone(
                NodeType::Assignment(new_name.to_string()),
                e,
                new_params,
            )
        },
        NodeType::Pattern(pattern_info) if pattern_info.binding_var == old_name => {
            // Inner Pattern with same binding name - this shadows our variable
            // Don't rename anything inside (the body after this Pattern will use the new binding)
            e.clone()
        },
        NodeType::Declaration(decl) if decl.name == old_name => {
            // Declaration shadows our variable - stop renaming in this scope
            // But we still need to rename in the initializer (params[0]) since it runs
            // BEFORE the declaration takes effect
            if e.params.is_empty() {
                e.clone()
            } else {
                // Only rename in the initializer (first param), not in nested bodies
                let mut new_params = Vec::new();
                if !e.params.is_empty() {
                    // The initializer is evaluated before the declaration, so rename in it
                    new_params.push(rename_identifier_in_expr(&e.params[0], old_name, new_name));
                    // Any remaining params (shouldn't exist for Declaration) - don't rename
                    for p in e.params.iter().skip(1) {
                        new_params.push(p.clone());
                    }
                }
                Expr::new_clone(e.node_type.clone(), e, new_params)
            }
        },
        _ => {
            // Recurse into params
            if e.params.is_empty() {
                e.clone()
            } else {
                let new_params: Vec<Expr> = e.params.iter()
                    .map(|p| rename_identifier_in_expr(p, old_name, new_name))
                    .collect();
                Expr::new_clone(e.node_type.clone(), e, new_params)
            }
        }
    }
}

/// Search all enums in scope to find which one contains a variant with the given name
/// Returns the enum type name if found, empty string if not found or ambiguous
fn find_enum_for_variant(context: &Context, variant_name: &str) -> String {
    let mut found_type = String::new();
    for frame in context.scope_stack.frames.iter().rev() {
        for (enum_name, enum_def) in &frame.enums {
            if enum_def.contains_key(variant_name) {
                if found_type.is_empty() {
                    found_type = enum_name.clone();
                }
                // If we find the same variant in multiple enums, we have ambiguity
                // Just return the first match - caller should use qualified names for clarity
            }
        }
    }
    found_type
}

/// Detect if a switch is an enum switch by looking at case patterns
/// Returns (is_enum, enum_type_name) if we can determine it from patterns
fn detect_enum_switch_from_cases(context: &Context, e: &Expr) -> (bool, String) {
    // Look at case patterns (params[1], params[3], params[5], ...)
    let mut i = 1;
    while i < e.params.len() {
        let case_pattern = &e.params[i];
        match &case_pattern.node_type {
            NodeType::DefaultCase => {
                // Skip default case
            },
            NodeType::Pattern(pattern_info) => {
                // Pattern with payload binding is definitely enum
                let info = parse_pattern_variant_name(&pattern_info.variant_name);
                if !info.type_name.is_empty() {
                    return (true, info.type_name);
                }
                // Shorthand pattern (just variant name) - search all enums for this variant
                let found_type = find_enum_for_variant(context, &info.variant_name);
                return (true, found_type);
            },
            NodeType::Identifier(name) => {
                // Identifier with nested params like Type.Variant
                if !case_pattern.params.is_empty() {
                    if let NodeType::Identifier(_variant_name) = &case_pattern.params[0].node_type {
                        // This looks like Type.Variant - check if Type is an enum
                        if context.scope_stack.lookup_enum(name.as_str()).is_some() {
                            return (true, name.clone());
                        }
                    }
                } else {
                    // Plain identifier - could be a variable of enum type
                    // Try to look up the variable's type
                    if let Some(symbol_info) = context.scope_stack.lookup_symbol(name) {
                        if let ValueType::TCustom(type_name) = &symbol_info.value_type {
                            if context.scope_stack.lookup_enum(type_name.as_str()).is_some() {
                                return (true, type_name.clone());
                            }
                        }
                    }
                }
            },
            NodeType::FCall(_) => {
                // FCall pattern might be Type.Variant(...) for enum with payload
                let info = get_case_variant_info(case_pattern);
                if !info.type_name.is_empty() {
                    if context.scope_stack.lookup_enum(&info.type_name).is_some() {
                        return (true, info.type_name);
                    }
                }
            },
            _ => {},
        }
        i += 2; // Skip body to get next case pattern
    }
    (false, String::new())
}

/// Infer the type of a switch expression from its case patterns
/// This is used as a fallback when get_value_type fails
/// For non-enum switches, returns the type based on literals (I64, Str, Bool)
/// For enum switches, returns None (caller should use enum_type_name from detect_enum_switch_from_cases)
fn infer_switch_type_from_cases(e: &Expr) -> Option<ValueType> {
    // Look at case patterns (params[1], params[3], params[5], ...)
    let mut i = 1;
    while i < e.params.len() {
        let case_pattern = &e.params[i];
        match &case_pattern.node_type {
            NodeType::DefaultCase => {
                // Skip default case
            },
            NodeType::LLiteral(lit) => {
                match lit {
                    Literal::Number(_) => return Some(ValueType::TCustom("I64".to_string())),
                    Literal::Str(_) => return Some(ValueType::TCustom("Str".to_string())),
                    _ => {},
                }
            },
            NodeType::Range => {
                // Check range bounds for type
                if !case_pattern.params.is_empty() {
                    if let NodeType::LLiteral(lit) = &case_pattern.params[0].node_type {
                        match lit {
                            Literal::Number(_) => return Some(ValueType::TCustom("I64".to_string())),
                            Literal::Str(_) => return Some(ValueType::TCustom("Str".to_string())),
                            _ => {},
                        }
                    }
                }
            },
            NodeType::Identifier(name) => {
                // Could be a variable or enum variant
                // If it's "true" or "false", it's Bool
                if name == "true" || name == "false" {
                    return Some(ValueType::TCustom("Bool".to_string()));
                }
                // If it has nested params (Type.Variant), it's an enum
                // Return the enum type name directly
                if !case_pattern.params.is_empty() {
                    // name is the enum type name (e.g., "TokenType" in "TokenType.Eof")
                    return Some(ValueType::TCustom(name.clone()));
                }
            },
            NodeType::Pattern(pattern_info) => {
                // Pattern is always enum - try to get the enum type from the variant name
                let info = parse_pattern_variant_name(&pattern_info.variant_name);
                if !info.type_name.is_empty() {
                    return Some(ValueType::TCustom(info.type_name));
                }
                // Shorthand pattern - can't infer type here (no context available)
                // Keep searching other case patterns
            },
            _ => {},
        }
        i += 2; // Skip body to get next case pattern
    }
    None
}

/// Desugar a Switch statement to an if/else chain
/// Issue #110: Switch is desugared to if/else to simplify interpreter, ccodegen, and precomp
///
/// For enum switches:
///   switch expr { case Type.Variant(x): body }
///   ->
///   { _switch_variant := enum_to_str(expr)
///     if Str.eq(_switch_variant, "Type.Variant") { mut x := default; enum_get_payload(expr, T, x); body }
///     else { default_body } }
///
/// For non-enum switches:
///   switch val { case 1: body1  case 2..5: body2  case: default }
///   ->
///   { _switch_val := val
///     if eq(_switch_val, 1) { body1 }
///     else if and(gteq(_switch_val, 2), lteq(_switch_val, 5)) { body2 }
///     else { default } }
fn desugar_switch(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    // Switch: params[0] = switch expression
    // params[1..] = alternating [case_pattern, body, case_pattern, body, ...]
    if e.params.is_empty() {
        return Err(e.lang_error(&context.path, "desugar", "Switch requires expression"));
    }

    let switch_expr = &e.params[0];
    let line = e.line;
    let col = e.col;

    // Determine if this is an enum switch by checking the switch expression's type
    let switch_type = get_value_type(context, switch_expr).ok();
    let (mut is_enum_switch, mut enum_type_name) = match &switch_type {
        Some(ValueType::TCustom(type_name)) => {
            let is_enum = context.scope_stack.lookup_enum(type_name.as_str()).is_some();
            (is_enum, if is_enum { type_name.clone() } else { String::new() })
        },
        _ => (false, String::new()),
    };

    // If get_value_type failed, try to detect enum switch from case patterns
    if !is_enum_switch && switch_type.is_none() {
        let (detected_enum, detected_type) = detect_enum_switch_from_cases(context, e);
        if detected_enum {
            is_enum_switch = true;
            enum_type_name = detected_type;
        }
    }

    // If we detected an enum switch but don't know the type, try harder
    if is_enum_switch && enum_type_name.is_empty() {
        // Try get_value_type result again - it might have the custom type name even if lookup_enum failed
        if let Some(ValueType::TCustom(name)) = &switch_type {
            enum_type_name = name.clone();
        }
    }

    // Generate unique temp var name
    let switch_id = context.precomp_forin_counter;
    context.precomp_forin_counter += 1;
    let func_name = context.current_precomp_func.clone();
    let switch_var_name = if !func_name.is_empty() {
        if is_enum_switch {
            format!("_switch_variant_{}_{}", func_name, switch_id)
        } else {
            format!("_switch_val_{}_{}", func_name, switch_id)
        }
    } else {
        if is_enum_switch {
            format!("_switch_variant_{}", switch_id)
        } else {
            format!("_switch_val_{}", switch_id)
        }
    };

    // Desugar the switch expression
    let desugared_switch_expr = desugar_expr(context, switch_expr)?;

    // Build declarations for switch variables
    // For enum switches, we need TWO temp vars to avoid ccodegen bug with throwing calls in func args:
    //   _switch_expr := switch_expr     (captures the enum value, handles ?)
    //   _switch_variant := enum_to_str(_switch_expr)  (simple identifier, no ?)
    // For non-enum switches: _switch_val := switch_expr
    let mut decl_exprs: Vec<Expr> = Vec::new();

    // Name for the expression temp (for enum switches) or value temp (for non-enum)
    let switch_expr_var_name = if is_enum_switch {
        if !func_name.is_empty() {
            format!("_switch_expr_{}_{}", func_name, switch_id)
        } else {
            format!("_switch_expr_{}", switch_id)
        }
    } else {
        switch_var_name.clone()
    };

    // Type for the expression temp (enum type or value type)
    // First try get_value_type on the original expression, then fall back to other methods
    let switch_expr_var_type: ValueType = match &switch_type {
        Some(vt) => vt.clone(),
        None => {
            // Try get_value_type on the desugared expression (might work better after desugaring)
            if let Ok(vt) = get_value_type(context, &desugared_switch_expr) {
                vt
            } else if is_enum_switch && !enum_type_name.is_empty() {
                // For enum switches, use the detected enum type name
                ValueType::TCustom(enum_type_name.clone())
            } else {
                // Try to infer type from case patterns
                match infer_switch_type_from_cases(e) {
                    Some(vt) => vt,
                    None => str_to_value_type("I64"), // Default to I64 if all inference fails
                }
            }
        }
    };

    // First declaration: capture the switch expression
    // Check if the expression is a field access on a throwing FCall - if so, split it
    // This works around ccodegen's inability to handle throwing calls with field access
    // in declaration initializers (generates invalid C code)
    let (needs_split, base_fcall_opt, field_names) = check_throwing_field_access(&desugared_switch_expr);

    if needs_split {
        if let Some(base_fcall) = base_fcall_opt {
            // Generate temp name for the FCall result
            let fcall_temp_name = if !func_name.is_empty() {
                format!("_switch_temp_{}_{}", func_name, switch_id)
            } else {
                format!("_switch_temp_{}", switch_id)
            };

            // Get the type of the FCall result
            let fcall_result_type = get_value_type(context, &base_fcall)
                .unwrap_or_else(|_| str_to_value_type("I64"));

            // First declaration: _switch_temp := throwing_fcall()
            let fcall_decl = Declaration {
                name: fcall_temp_name.clone(),
                value_type: fcall_result_type,
                is_mut: false,
                is_copy: false,
                is_own: false,
                default_value: None,
            };
            let fcall_decl_expr = Expr::new_explicit(
                NodeType::Declaration(fcall_decl),
                vec![base_fcall],
                line,
                col,
            );
            decl_exprs.push(fcall_decl_expr);

            // Build the field access chain on the temp variable
            // TIL field access structure for variable.field: Identifier("var") with params = [Identifier("field")]
            // So "x.field1.field2" is Identifier("x") with params[0] = Identifier("field1"), params[1] = Identifier("field2")
            // field_names contains fields in reverse order (innermost first), so we reverse to get field1, field2, etc.
            let mut field_params = Vec::new();
            for field_name in field_names.into_iter().rev() {
                field_params.push(Expr::new_explicit(
                    NodeType::Identifier(field_name),
                    vec![],
                    line,
                    col,
                ));
            }
            let field_access_expr = Expr::new_explicit(
                NodeType::Identifier(fcall_temp_name),
                field_params,
                line,
                col,
            );

            // Second declaration: _switch_expr := _switch_temp.field1.field2...
            let switch_expr_decl = Declaration {
                name: switch_expr_var_name.clone(),
                value_type: switch_expr_var_type.clone(),
                is_mut: false,
                is_copy: false,
                is_own: false,
                default_value: None,
            };
            let switch_expr_decl_expr = Expr::new_explicit(
                NodeType::Declaration(switch_expr_decl),
                vec![field_access_expr],
                line,
                col,
            );
            decl_exprs.push(switch_expr_decl_expr);
        }
    } else {
        // Normal case: directly capture the switch expression
        let switch_expr_decl = Declaration {
            name: switch_expr_var_name.clone(),
            value_type: switch_expr_var_type.clone(),
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let switch_expr_decl_expr = Expr::new_explicit(
            NodeType::Declaration(switch_expr_decl),
            vec![desugared_switch_expr.clone()],
            line,
            col,
        );
        decl_exprs.push(switch_expr_decl_expr);
    }

    // For enum switches, add second declaration: _switch_variant := enum_to_str(_switch_expr)
    if is_enum_switch {
        let enum_to_str_call = Expr::new_explicit(
            NodeType::FCall(false),
            vec![
                Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                Expr::new_explicit(NodeType::Identifier(switch_expr_var_name.clone()), vec![], line, col),
            ],
            line,
            col,
        );
        let switch_variant_decl = Declaration {
            name: switch_var_name.clone(),
            value_type: str_to_value_type("Str"),
            is_mut: false,
            is_copy: false,
            is_own: false,
            default_value: None,
        };
        let switch_variant_decl_expr = Expr::new_explicit(
            NodeType::Declaration(switch_variant_decl),
            vec![enum_to_str_call],
            line,
            col,
        );
        decl_exprs.push(switch_variant_decl_expr);
    }

    // Build the if/else chain from cases
    // Process cases in pairs: [case_pattern, body, case_pattern, body, ...]
    let mut cases: Vec<(Expr, Expr)> = Vec::new();
    let mut default_body: Option<Expr> = None;

    let mut i = 1;
    while i + 1 < e.params.len() {
        let case_pattern = &e.params[i];
        let case_body = &e.params[i + 1];

        // If the case pattern has a payload binding, declare it in scope before desugaring body
        // This allows nested switches in the body to see the payload variable's type
        let mut pushed_scope = false;
        if let NodeType::Pattern(pattern_info) = &case_pattern.node_type {
            let info = parse_pattern_variant_name(&pattern_info.variant_name);
            let actual_type_name = if !info.type_name.is_empty() {
                info.type_name.clone()
            } else if !enum_type_name.is_empty() {
                enum_type_name.clone()
            } else {
                find_enum_for_variant(context, &info.variant_name)
            };
            if let Some(payload_type) = get_payload_type_for_variant(context, &actual_type_name, &info.variant_name) {
                // Push a scope and declare the payload variable
                context.scope_stack.push(ScopeType::Block);
                context.scope_stack.declare_symbol(
                    pattern_info.binding_var.clone(),
                    SymbolInfo {
                        value_type: payload_type,
                        is_mut: true,
                        is_copy: false,
                        is_own: false,
                        is_comptime_const: false,
                    },
                );
                pushed_scope = true;
            }
        }

        // Desugar the case body (now with payload variable in scope if applicable)
        let desugared_body = desugar_expr(context, case_body)?;

        // Pop the scope if we pushed one
        if pushed_scope {
            let _ = context.scope_stack.pop();
        }

        if matches!(case_pattern.node_type, NodeType::DefaultCase) {
            default_body = Some(desugared_body);
        } else {
            cases.push((case_pattern.clone(), desugared_body));
        }
        i += 2;
    }

    // Build if/else chain from cases (in reverse order to nest properly)
    // Start with the default/else branch
    let mut result_expr = match default_body {
        Some(body) => body,
        None => Expr::new_explicit(NodeType::Body, vec![], line, col), // Empty body if no default
    };

    // Process cases in reverse to build nested if/else
    // Keep track of case index for unique naming (count from end since we reverse)
    let total_cases = cases.len();
    for (idx, (case_pattern, case_body)) in cases.into_iter().rev().enumerate() {
        let case_index = total_cases - 1 - idx;  // Original order index
        let (condition, body_prefix, rename_pair) = build_case_condition(
            context,
            &case_pattern,
            &switch_var_name,
            is_enum_switch,
            &enum_type_name,
            &switch_expr_var_name,  // For enum_get_payload
            switch_id,  // Global switch ID for unique naming
            case_index,
            &func_name,
            line,
            col,
        )?;

        // If there's a rename pair, rename references to the original binding in the DESUGARED case body
        let renamed_case_body = if let Some((old_name, new_name)) = &rename_pair {
            rename_identifier_in_expr(&case_body, old_name, new_name)
        } else {
            case_body
        };

        // Build the case body with any prefix (e.g., payload extraction)
        let full_case_body = if body_prefix.is_empty() {
            renamed_case_body
        } else {
            // Prepend prefix statements to body
            let mut body_params = body_prefix;
            match &renamed_case_body.node_type {
                NodeType::Body => body_params.extend(renamed_case_body.params.clone()),
                _ => body_params.push(renamed_case_body.clone()),
            }
            Expr::new_explicit(NodeType::Body, body_params, line, col)
        };

        // Build: if (condition) { full_case_body } else { result_expr }
        result_expr = Expr::new_explicit(
            NodeType::If,
            vec![condition, full_case_body, result_expr],
            line,
            col,
        );
    }

    // Wrap in outer body with declarations and if/else chain
    let mut body_params = decl_exprs;
    body_params.push(result_expr);
    Ok(Expr::new_explicit(
        NodeType::Body,
        body_params,
        line,
        col,
    ))
}

/// Build the condition expression and any body prefix for a case pattern
/// Returns (condition_expr, body_prefix_statements, optional_rename_pair)
/// switch_expr_var_name: name of the temp variable holding the switch expression value (for enum_get_payload)
/// switch_id: global unique ID for this switch statement
/// case_index: index of this case within the switch (for generating unique payload names)
/// func_name: current function name for generating unique names
fn build_case_condition(
    context: &Context,
    case_pattern: &Expr,
    switch_var_name: &str,
    is_enum_switch: bool,
    enum_type_name: &str,
    switch_expr_var_name: &str,
    switch_id: usize,
    case_index: usize,
    func_name: &str,
    line: usize,
    col: usize,
) -> Result<(Expr, Vec<Expr>, Option<(String, String)>), String> {
    match &case_pattern.node_type {
        NodeType::Pattern(pattern_info) => {
            // Enum pattern with payload binding: case Type.Variant(x):
            let info = parse_pattern_variant_name(&pattern_info.variant_name);
            let actual_type_name = if !info.type_name.is_empty() {
                info.type_name.clone()
            } else if !enum_type_name.is_empty() {
                enum_type_name.to_string()
            } else {
                // Try to find the enum type by looking up which enum has this variant
                let mut found_type = String::new();
                for frame in context.scope_stack.frames.iter().rev() {
                    for (enum_name, enum_def) in &frame.enums {
                        if enum_def.contains_key(&info.variant_name) {
                            found_type = enum_name.clone();
                            break;
                        }
                    }
                    if !found_type.is_empty() {
                        break;
                    }
                }
                found_type
            };

            // Condition: Str.eq(_switch_variant, "Type.Variant")
            let variant_str = format!("{}.{}", actual_type_name, info.variant_name);
            let condition = build_str_eq_call(switch_var_name, &variant_str, line, col);

            // Body prefix: extract payload
            // Generate unique name to avoid conflicts with outer scope variables
            // mut _payload_binding_N := default_value
            // enum_get_payload(_switch_expr, PayloadType, _payload_binding_N)
            let mut body_prefix = Vec::new();
            let mut rename_pair: Option<(String, String)> = None;
            let payload_type = get_payload_type_for_variant(context, &actual_type_name, &info.variant_name);
            if let Some(vt) = payload_type {
                // Generate unique payload variable name to avoid conflicts
                // Include switch_id for global uniqueness across multiple switches
                let original_name = pattern_info.binding_var.clone();
                let unique_name = if !func_name.is_empty() {
                    format!("_payload_{}_{}_{}_{}", original_name, func_name, switch_id, case_index)
                } else {
                    format!("_payload_{}_{}_{}", original_name, switch_id, case_index)
                };

                // Build default value for the payload type
                let default_val = build_default_value(context, &vt, line, col);

                // Build: mut _payload_binding_N := default_value
                let binding_decl = Declaration {
                    name: unique_name.clone(),
                    value_type: vt.clone(),
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
                body_prefix.push(binding_decl_expr);

                // Build: enum_get_payload(_switch_expr, PayloadType, _payload_binding_N)
                // The type argument is passed as a Type identifier
                let payload_type_name = match &vt {
                    ValueType::TCustom(name) => name.clone(),
                    _ => "I64".to_string(), // Shouldn't happen
                };
                let get_payload_call = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_get_payload".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_expr_var_name.to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(payload_type_name), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(unique_name.clone()), vec![], line, col),
                    ],
                    line,
                    col,
                );
                body_prefix.push(get_payload_call);

                // Return rename pair so caller can rename references in the case body
                rename_pair = Some((original_name, unique_name));
            }

            Ok((condition, body_prefix, rename_pair))
        },
        NodeType::Range => {
            // Range case: case low..high:
            // Condition: and(gteq(_switch_val, low), lteq(_switch_val, high))
            if case_pattern.params.len() < 2 {
                return Err("desugar: Range case requires start and end values".to_string());
            }
            let low = &case_pattern.params[0];
            let high = &case_pattern.params[1];

            // Build: gteq(_switch_val, low)
            let gteq_call = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(NodeType::Identifier("gteq".to_string()), vec![], line, col),
                    Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                    low.clone(),
                ],
                line,
                col,
            );

            // Build: lteq(_switch_val, high)
            let lteq_call = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(NodeType::Identifier("lteq".to_string()), vec![], line, col),
                    Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                    high.clone(),
                ],
                line,
                col,
            );

            // Build: and(gteq_call, lteq_call)
            let condition = Expr::new_explicit(
                NodeType::FCall(false),
                vec![
                    Expr::new_explicit(NodeType::Identifier("and".to_string()), vec![], line, col),
                    gteq_call,
                    lteq_call,
                ],
                line,
                col,
            );

            Ok((condition, vec![], None))
        },
        NodeType::Identifier(_) | NodeType::LLiteral(_) => {
            // Simple value case or enum variant without payload
            let info = get_case_variant_info(case_pattern);

            if is_enum_switch && !info.variant_name.is_empty() {
                // Enum variant without payload: case Type.Variant:
                let actual_type_name = if info.type_name.is_empty() {
                    enum_type_name.to_string()
                } else {
                    info.type_name.clone()
                };
                let variant_str = format!("{}.{}", actual_type_name, info.variant_name);
                let condition = build_str_eq_call(switch_var_name, &variant_str, line, col);
                Ok((condition, vec![], None))
            } else if is_enum_switch {
                // Enum switch with variable case: case some_var:
                // Need to compare using enum_to_str on the case value too
                // Build: eq(_switch_variant, enum_to_str(case_val))
                let case_val_str = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                        case_pattern.clone(),
                    ],
                    line,
                    col,
                );
                let condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                        case_val_str,
                    ],
                    line,
                    col,
                );
                Ok((condition, vec![], None))
            } else {
                // Non-enum value comparison: case val:
                // Condition: eq(_switch_val, case_val)
                let condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                        case_pattern.clone(),
                    ],
                    line,
                    col,
                );
                Ok((condition, vec![], None))
            }
        },
        NodeType::FCall(_) => {
            // FCall pattern: Type.Variant() or computed value
            let info = get_case_variant_info(case_pattern);

            if is_enum_switch && !info.variant_name.is_empty() {
                // Enum variant (possibly with payload comparison, but we only check tag)
                let actual_type_name = if info.type_name.is_empty() {
                    enum_type_name.to_string()
                } else {
                    info.type_name.clone()
                };
                let variant_str = format!("{}.{}", actual_type_name, info.variant_name);
                let condition = build_str_eq_call(switch_var_name, &variant_str, line, col);
                Ok((condition, vec![], None))
            } else if is_enum_switch {
                // Enum switch with computed case value (returns enum)
                // Build: eq(_switch_variant, enum_to_str(case_val))
                let case_val_str = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                        case_pattern.clone(),
                    ],
                    line,
                    col,
                );
                let condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                        case_val_str,
                    ],
                    line,
                    col,
                );
                Ok((condition, vec![], None))
            } else {
                // Computed case value: case func():
                // Condition: eq(_switch_val, case_val)
                let condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                        case_pattern.clone(),
                    ],
                    line,
                    col,
                );
                Ok((condition, vec![], None))
            }
        },
        _ => {
            // Fallback: depends on whether it's an enum switch
            if is_enum_switch {
                // Enum switch - wrap case value in enum_to_str
                let case_val_str = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("enum_to_str".to_string()), vec![], line, col),
                        case_pattern.clone(),
                    ],
                    line,
                    col,
                );
                let condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                        case_val_str,
                    ],
                    line,
                    col,
                );
                Ok((condition, vec![], None))
            } else {
                // Non-enum: simple equality comparison
                let condition = Expr::new_explicit(
                    NodeType::FCall(false),
                    vec![
                        Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
                        Expr::new_explicit(NodeType::Identifier(switch_var_name.to_string()), vec![], line, col),
                        case_pattern.clone(),
                    ],
                    line,
                    col,
                );
                Ok((condition, vec![], None))
            }
        },
    }
}

/// Build: Str.eq(var_name, literal_str)
/// This is UFCS form that will be resolved to Str.eq(_switch_variant, "Type.Variant")
fn build_str_eq_call(var_name: &str, literal_str: &str, line: usize, col: usize) -> Expr {
    // Build: eq(_switch_variant, "Type.Variant")
    // The UFCS phase will transform this to Str.eq if needed
    Expr::new_explicit(
        NodeType::FCall(false),
        vec![
            Expr::new_explicit(NodeType::Identifier("eq".to_string()), vec![], line, col),
            Expr::new_explicit(NodeType::Identifier(var_name.to_string()), vec![], line, col),
            Expr::new_explicit(NodeType::LLiteral(Literal::Str(literal_str.to_string())), vec![], line, col),
        ],
        line,
        col,
    )
}

/// Desugarer phase entry point: Recursively desugar ForIn loops and Switch statements.
pub fn desugar_expr(context: &mut Context, e: &Expr) -> Result<Expr, String> {
    match &e.node_type {
        // ForIn desugaring: for VAR: TYPE in COLLECTION { body } -> while loop
        NodeType::ForIn(var_type_name) => {
            desugar_forin(context, e, var_type_name)
        },
        // Switch desugaring: switch expr { case x: body } -> if/else chain
        // Issue #110: Simplifies interpreter, ccodegen, and precomp
        NodeType::Switch => {
            desugar_switch(context, e)
        },
        // Recurse into FuncDef bodies
        NodeType::FuncDef(func_def) => {
            // Bug #130 fix: Reset counter per-function for deterministic output
            let saved_counter = context.precomp_forin_counter;
            context.precomp_forin_counter = 0;

            // Issue #110: Push function scope with parameters so switch desugaring can look them up
            context.scope_stack.push(ScopeType::Function);
            for arg in &func_def.args {
                context.scope_stack.declare_symbol(
                    arg.name.clone(),
                    SymbolInfo {
                        value_type: arg.value_type.clone(),
                        is_mut: arg.is_mut,
                        is_copy: arg.is_copy,
                        is_own: arg.is_own,
                        is_comptime_const: false,
                    },
                );
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
        // Track declarations in scope_stack so get_value_type can find local variables
        // This is needed for switch desugaring to determine the type of expressions like var.field
        NodeType::Declaration(decl) => {
            // First desugar the initializer expression (if any)
            let new_params = if e.params.is_empty() {
                Vec::new()
            } else {
                let mut params = Vec::new();
                for p in &e.params {
                    params.push(desugar_expr(context, p)?);
                }
                params
            };

            // Track this declaration in scope_stack for get_value_type lookups
            context.scope_stack.declare_symbol(
                decl.name.clone(),
                SymbolInfo {
                    value_type: decl.value_type.clone(),
                    is_mut: decl.is_mut,
                    is_copy: decl.is_copy,
                    is_own: decl.is_own,
                    is_comptime_const: false,
                },
            );

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
